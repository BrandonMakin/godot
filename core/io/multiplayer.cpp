#include "core/io/multiplayer.h"
#include "core/io/marshalls.h"
#include "scene/main/node.h"

void MultiplayerProtocol::network_poll(MultiplayerState &state) {

	if (!state.peer.is_valid() || state.peer->get_connection_status() == NetworkedMultiplayerPeer::CONNECTION_DISCONNECTED)
		return;

	state.peer->poll();

	if (!state.peer.is_valid()) //it's possible that polling might have resulted in a disconnection, so check here
		return;

	while (state.peer->get_available_packet_count()) {

		int sender = state.peer->get_packet_peer();
		const uint8_t *packet;
		int len;

		Error err = state.peer->get_packet(&packet, len);
		if (err != OK) {
			ERR_PRINT("Error getting packet!");
		}

		state.rpc_sender_id = sender;
		_network_process_packet(state, sender, packet, len);
		state.rpc_sender_id = 0;

		if (!state.peer.is_valid()) {
			break; //it's also possible that a packet or RPC caused a disconnection, so also check here
		}
	}
}

void MultiplayerProtocol::_network_process_packet(MultiplayerState &state, int p_from, const uint8_t *p_packet, int p_packet_len) {

	ERR_FAIL_COND(p_packet_len < 5);

	uint8_t packet_type = p_packet[0];

	switch (packet_type) {

		case NETWORK_COMMAND_REMOTE_CALL:
		case NETWORK_COMMAND_REMOTE_SET: {

			ERR_FAIL_COND(p_packet_len < 5);
			uint32_t target = decode_uint32(&p_packet[1]);

			Node *node = NULL;

			if (target & 0x80000000) {
				//use full path (not cached yet)

				int ofs = target & 0x7FFFFFFF;
				ERR_FAIL_COND(ofs >= p_packet_len);

				String paths;
				paths.parse_utf8((const char *)&p_packet[ofs], p_packet_len - ofs);

				NodePath np = paths;

				node = state.root->get_node(np);
				if (node == NULL) {
					ERR_EXPLAIN("Failed to get path from RPC: " + String(np));
					ERR_FAIL_COND(node == NULL);
				}
			} else {
				//use cached path
				int id = target;

				Map<int, PathGetCache>::Element *E = state.path_get_cache.find(p_from);
				ERR_FAIL_COND(!E);

				Map<int, PathGetCache::NodeInfo>::Element *F = E->get().nodes.find(id);
				ERR_FAIL_COND(!F);

				PathGetCache::NodeInfo *ni = &F->get();
				//do proper caching later

				node = state.root->get_node(ni->path);
				if (node == NULL) {
					ERR_EXPLAIN("Failed to get cached path from RPC: " + String(ni->path));
					ERR_FAIL_COND(node == NULL);
				}
			}

			ERR_FAIL_COND(p_packet_len < 6);

			//detect cstring end
			int len_end = 5;
			for (; len_end < p_packet_len; len_end++) {
				if (p_packet[len_end] == 0) {
					break;
				}
			}

			ERR_FAIL_COND(len_end >= p_packet_len);

			StringName name = String::utf8((const char *)&p_packet[5]);

			if (packet_type == NETWORK_COMMAND_REMOTE_CALL) {

				if (!node->can_call_rpc(name, p_from))
					return;

				int ofs = len_end + 1;

				ERR_FAIL_COND(ofs >= p_packet_len);

				int argc = p_packet[ofs];
				Vector<Variant> args;
				Vector<const Variant *> argp;
				args.resize(argc);
				argp.resize(argc);

				ofs++;

				for (int i = 0; i < argc; i++) {

					ERR_FAIL_COND(ofs >= p_packet_len);
					int vlen;
					Error err = decode_variant(args[i], &p_packet[ofs], p_packet_len - ofs, &vlen);
					ERR_FAIL_COND(err != OK);
					//args[i]=p_packet[3+i];
					argp[i] = &args[i];
					ofs += vlen;
				}

				Variant::CallError ce;

				node->call(name, (const Variant **)argp.ptr(), argc, ce);
				if (ce.error != Variant::CallError::CALL_OK) {
					String error = Variant::get_call_error_text(node, name, (const Variant **)argp.ptr(), argc, ce);
					error = "RPC - " + error;
					ERR_PRINTS(error);
				}

			} else {

				if (!node->can_call_rset(name, p_from))
					return;

				int ofs = len_end + 1;

				ERR_FAIL_COND(ofs >= p_packet_len);

				Variant value;
				decode_variant(value, &p_packet[ofs], p_packet_len - ofs);

				bool valid;

				node->set(name, value, &valid);
				if (!valid) {
					String error = "Error setting remote property '" + String(name) + "', not found in object of type " + node->get_class();
					ERR_PRINTS(error);
				}
			}

		} break;
		case NETWORK_COMMAND_SIMPLIFY_PATH: {

			ERR_FAIL_COND(p_packet_len < 5);
			int id = decode_uint32(&p_packet[1]);

			String paths;
			paths.parse_utf8((const char *)&p_packet[5], p_packet_len - 5);

			NodePath path = paths;

			if (!state.path_get_cache.has(p_from)) {
				state.path_get_cache[p_from] = PathGetCache();
			}

			PathGetCache::NodeInfo ni;
			ni.path = path;
			ni.instance = 0;

			state.path_get_cache[p_from].nodes[id] = ni;

			{
				//send ack

				//encode path
				CharString pname = String(path).utf8();
				int len = encode_cstring(pname.get_data(), NULL);

				Vector<uint8_t> packet;

				packet.resize(1 + len);
				packet[0] = NETWORK_COMMAND_CONFIRM_PATH;
				encode_cstring(pname.get_data(), &packet[1]);

				state.peer->set_transfer_mode(NetworkedMultiplayerPeer::TRANSFER_MODE_RELIABLE);
				state.peer->set_target_peer(p_from);
				state.peer->put_packet(packet.ptr(), packet.size());
			}
		} break;
		case NETWORK_COMMAND_CONFIRM_PATH: {

			String paths;
			paths.parse_utf8((const char *)&p_packet[1], p_packet_len - 1);

			NodePath path = paths;

			PathSentCache *psc = state.path_send_cache.getptr(path);
			ERR_FAIL_COND(!psc);

			Map<int, bool>::Element *E = psc->confirmed_peers.find(p_from);
			ERR_FAIL_COND(!E);
			E->get() = true;
		} break;
	}
}

void MultiplayerProtocol::_rpc(MultiplayerState &state, Node *p_from, int p_to, bool p_unreliable, bool p_set, const StringName &p_name, const Variant **p_arg, int p_argcount) {

	if (state.peer.is_null()) {
		ERR_EXPLAIN("Attempt to remote call/set when networking is not active in SceneTree.");
		ERR_FAIL();
	}

	if (state.peer->get_connection_status() == NetworkedMultiplayerPeer::CONNECTION_CONNECTING) {
		ERR_EXPLAIN("Attempt to remote call/set when networking is not connected yet in SceneTree.");
		ERR_FAIL();
	}

	if (state.peer->get_connection_status() == NetworkedMultiplayerPeer::CONNECTION_DISCONNECTED) {
		ERR_EXPLAIN("Attempt to remote call/set when networking is disconnected.");
		ERR_FAIL();
	}

	if (p_argcount > 255) {
		ERR_EXPLAIN("Too many arguments >255.");
		ERR_FAIL();
	}

	if (p_to != 0 && !state.connected_peers.has(ABS(p_to))) {
		if (p_to == state.peer->get_unique_id()) {
			ERR_EXPLAIN("Attempt to remote call/set yourself! unique ID: " + itos(state.peer->get_unique_id()));
		} else {
			ERR_EXPLAIN("Attempt to remote call unexisting ID: " + itos(p_to));
		}

		ERR_FAIL();
	}

	NodePath from_path = p_from->get_path();
	ERR_FAIL_COND(from_path.is_empty());

	//see if the path is cached
	PathSentCache *psc = state.path_send_cache.getptr(from_path);
	if (!psc) {
		//path is not cached, create
		state.path_send_cache[from_path] = PathSentCache();
		psc = state.path_send_cache.getptr(from_path);
		psc->id = state.last_send_cache_id++;
	}

	//create base packet, lots of harcode because it must be tight

	int ofs = 0;

#define MAKE_ROOM(m_amount) \
	if (state.packet_cache.size() < m_amount) state.packet_cache.resize(m_amount);

	//encode type
	MAKE_ROOM(1);
	state.packet_cache[0] = p_set ? NETWORK_COMMAND_REMOTE_SET : NETWORK_COMMAND_REMOTE_CALL;
	ofs += 1;

	//encode ID
	MAKE_ROOM(ofs + 4);
	encode_uint32(psc->id, &(state.packet_cache[ofs]));
	ofs += 4;

	//encode function name
	CharString name = String(p_name).utf8();
	int len = encode_cstring(name.get_data(), NULL);
	MAKE_ROOM(ofs + len);
	encode_cstring(name.get_data(), &(state.packet_cache[ofs]));
	ofs += len;

	if (p_set) {
		//set argument
		Error err = encode_variant(*p_arg[0], NULL, len);
		ERR_FAIL_COND(err != OK);
		MAKE_ROOM(ofs + len);
		encode_variant(*p_arg[0], &(state.packet_cache[ofs]), len);
		ofs += len;

	} else {
		//call arguments
		MAKE_ROOM(ofs + 1);
		state.packet_cache[ofs] = p_argcount;
		ofs += 1;
		for (int i = 0; i < p_argcount; i++) {
			Error err = encode_variant(*p_arg[i], NULL, len);
			ERR_FAIL_COND(err != OK);
			MAKE_ROOM(ofs + len);
			encode_variant(*p_arg[i], &(state.packet_cache[ofs]), len);
			ofs += len;
		}
	}

	//see if all peers have cached path (is so, call can be fast)
	bool has_all_peers = true;

	List<int> peers_to_add; //if one is missing, take note to add it

	for (Set<int>::Element *E = state.connected_peers.front(); E; E = E->next()) {

		if (p_to < 0 && E->get() == -p_to)
			continue; //continue, excluded

		if (p_to > 0 && E->get() != p_to)
			continue; //continue, not for this peer

		Map<int, bool>::Element *F = psc->confirmed_peers.find(E->get());

		if (!F || F->get() == false) {
			//path was not cached, or was cached but is unconfirmed
			if (!F) {
				//not cached at all, take note
				peers_to_add.push_back(E->get());
			}

			has_all_peers = false;
		}
	}

	//those that need to be added, send a message for this

	for (List<int>::Element *E = peers_to_add.front(); E; E = E->next()) {

		//encode function name
		CharString pname = String(from_path).utf8();
		int len = encode_cstring(pname.get_data(), NULL);

		Vector<uint8_t> packet;

		packet.resize(1 + 4 + len);
		packet[0] = NETWORK_COMMAND_SIMPLIFY_PATH;
		encode_uint32(psc->id, &packet[1]);
		encode_cstring(pname.get_data(), &packet[5]);

		state.peer->set_target_peer(E->get()); //to all of you
		state.peer->set_transfer_mode(NetworkedMultiplayerPeer::TRANSFER_MODE_RELIABLE);
		state.peer->put_packet(packet.ptr(), packet.size());

		psc->confirmed_peers.insert(E->get(), false); //insert into confirmed, but as false since it was not confirmed
	}

	//take chance and set transfer mode, since all send methods will use it
	state.peer->set_transfer_mode(p_unreliable ? NetworkedMultiplayerPeer::TRANSFER_MODE_UNRELIABLE : NetworkedMultiplayerPeer::TRANSFER_MODE_RELIABLE);

	if (has_all_peers) {

		//they all have verified paths, so send fast
		state.peer->set_target_peer(p_to); //to all of you
		state.peer->put_packet(state.packet_cache.ptr(), ofs); //a message with love
	} else {
		//not all verified path, so send one by one

		//apend path at the end, since we will need it for some packets
		CharString pname = String(from_path).utf8();
		int path_len = encode_cstring(pname.get_data(), NULL);
		MAKE_ROOM(ofs + path_len);
		encode_cstring(pname.get_data(), &(state.packet_cache[ofs]));

		for (Set<int>::Element *E = state.connected_peers.front(); E; E = E->next()) {

			if (p_to < 0 && E->get() == -p_to)
				continue; //continue, excluded

			if (p_to > 0 && E->get() != p_to)
				continue; //continue, not for this peer

			Map<int, bool>::Element *F = psc->confirmed_peers.find(E->get());
			ERR_CONTINUE(!F); //should never happen

			state.peer->set_target_peer(E->get()); //to this one specifically

			if (F->get() == true) {
				//this one confirmed path, so use id
				encode_uint32(psc->id, &(state.packet_cache[1]));
				state.peer->put_packet(state.packet_cache.ptr(), ofs);
			} else {
				//this one did not confirm path yet, so use entire path (sorry!)
				encode_uint32(0x80000000 | ofs, &(state.packet_cache[1])); //offset to path and flag
				state.peer->put_packet(state.packet_cache.ptr(), ofs + path_len);
			}
		}
	}
}

void MultiplayerProtocol::add_peer(MultiplayerState &state, int p_id) {
	state.connected_peers.insert(p_id);
	state.path_get_cache.insert(p_id, PathGetCache());
}

void MultiplayerProtocol::del_peer(MultiplayerState &state, int p_id) {
	state.connected_peers.erase(p_id);
	state.path_get_cache.erase(p_id); //I no longer need your cache, sorry
}

bool _should_call_native(Node::RPCMode mode, bool is_master, bool &r_skip_rpc) {

	switch (mode) {

		case Node::RPC_MODE_DISABLED: {
			//do nothing
		} break;
		case Node::RPC_MODE_REMOTE: {
			//do nothing also, no need to call local
		} break;
		case Node::RPC_MODE_SYNC: {
			//call it, sync always results in call
			return true;
		} break;
		case Node::RPC_MODE_MASTER: {
			if (is_master)
				r_skip_rpc = true; //no other master so..
			return is_master;
		} break;
		case Node::RPC_MODE_SLAVE: {
			return !is_master;
		} break;
	}
	return false;
}

bool _should_call_script(ScriptInstance::RPCMode mode, bool is_master, bool &r_skip_rpc) {
	switch (mode) {

		case ScriptInstance::RPC_MODE_DISABLED: {
			//do nothing
		} break;
		case ScriptInstance::RPC_MODE_REMOTE: {
			//do nothing also, no need to call local
		} break;
		case ScriptInstance::RPC_MODE_SYNC: {
			//call it, sync always results in call
			return true;
		} break;
		case ScriptInstance::RPC_MODE_MASTER: {
			if (is_master)
				r_skip_rpc = true; //no other master so..
			return is_master;
		} break;
		case ScriptInstance::RPC_MODE_SLAVE: {
			return !is_master;
		} break;
	}
	return false;
}

void MultiplayerProtocol::rpcp(Node *p_node, int p_peer_id, bool p_unreliable, const StringName &p_method, const Variant **p_arg, int p_argcount) {

	ERR_FAIL_COND(!p_node->is_inside_tree());

	int node_id = p_node->get_tree()->get_network_unique_id();
	bool skip_rpc = false;
	bool call_local_native = false;
	bool call_local_script = false;
	bool is_master = p_node->is_network_master();

	if (p_peer_id == 0 || p_peer_id == node_id || (p_peer_id < 0 && p_peer_id != -node_id)) {
		//check that send mode can use local call

		const Map<StringName, Node::RPCMode>::Element *E = p_node->get_node_rpc_mode(p_method);
		if (E) {
			call_local_native = _should_call_native(E->get(), is_master, skip_rpc);
		}

		if (call_local_native) {
			// done below
		} else if (p_node->get_script_instance()) {
			//attempt with script
			ScriptInstance::RPCMode rpc_mode = p_node->get_script_instance()->get_rpc_mode(p_method);
			call_local_script = _should_call_script(rpc_mode, is_master, skip_rpc);
		}
	}

	if (!skip_rpc) {
		p_node->get_tree()->_rpc(p_node, p_peer_id, p_unreliable, false, p_method, p_arg, p_argcount);
	}

	if (call_local_native) {
		Variant::CallError ce;
		p_node->call(p_method, p_arg, p_argcount, ce);
		if (ce.error != Variant::CallError::CALL_OK) {
			String error = Variant::get_call_error_text(p_node, p_method, p_arg, p_argcount, ce);
			error = "rpc() aborted in local call:  - " + error;
			ERR_PRINTS(error);
			return;
		}
	}

	if (call_local_script) {
		Variant::CallError ce;
		ce.error = Variant::CallError::CALL_OK;
		p_node->get_script_instance()->call(p_method, p_arg, p_argcount, ce);
		if (ce.error != Variant::CallError::CALL_OK) {
			String error = Variant::get_call_error_text(p_node, p_method, p_arg, p_argcount, ce);
			error = "rpc() aborted in script local call:  - " + error;
			ERR_PRINTS(error);
			return;
		}
	}
}

void MultiplayerProtocol::rsetp(Node *p_node, int p_peer_id, bool p_unreliable, const StringName &p_property, const Variant &p_value) {

	ERR_FAIL_COND(!p_node->is_inside_tree());

	int node_id = p_node->get_tree()->get_network_unique_id();
	bool is_master = p_node->is_network_master();
	bool skip_rset = false;

	if (p_peer_id == 0 || p_peer_id == node_id || (p_peer_id < 0 && p_peer_id != -node_id)) {
		//check that send mode can use local call

		bool set_local = false;

		const Map<StringName, Node::RPCMode>::Element *E = p_node->get_node_rset_mode(p_property);
		if (E) {

			set_local = _should_call_native(E->get(), is_master, skip_rset);
		}

		if (set_local) {
			bool valid;
			p_node->set(p_property, p_value, &valid);

			if (!valid) {
				String error = "rset() aborted in local set, property not found:  - " + String(p_property);
				ERR_PRINTS(error);
				return;
			}
		} else if (p_node->get_script_instance()) {
			//attempt with script
			ScriptInstance::RPCMode rpc_mode = p_node->get_script_instance()->get_rset_mode(p_property);

			set_local = _should_call_script(rpc_mode, is_master, skip_rset);

			if (set_local) {

				bool valid = p_node->get_script_instance()->set(p_property, p_value);

				if (!valid) {
					String error = "rset() aborted in local script set, property not found:  - " + String(p_property);
					ERR_PRINTS(error);
					return;
				}
			}
		}
	}

	if (skip_rset)
		return;

	const Variant *vptr = &p_value;

	p_node->get_tree()->_rpc(p_node, p_peer_id, p_unreliable, true, p_property, &vptr, 1);
}
