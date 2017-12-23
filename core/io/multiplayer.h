#ifndef MULTIPLAYER_PROTOCOL_H
#define MULTIPLAYER_PROTOCOL_H

#include "core/io/networked_multiplayer_peer.h"
#include "core/reference.h"

class MultiplayerProtocol : public Reference {

	GDCLASS(MultiplayerProtocol, Reference);

protected:
	static void _bind_methods() {
	}

	void _network_process_packet(int p_from, const uint8_t *p_packet, int p_packet_len);
	void _network_process_call(int p_from, const uint8_t *p_packet, int p_packet_len);
	void _network_simplify_path(int p_from, const uint8_t *p_packet, int p_packet_len);
	void _network_confirm_path(int p_from, const uint8_t *p_packet, int p_packet_len);

public:
	enum NetworkCommands {
		NETWORK_COMMAND_REMOTE_CALL,
		NETWORK_COMMAND_REMOTE_SET,
		NETWORK_COMMAND_SIMPLIFY_PATH,
		NETWORK_COMMAND_CONFIRM_PATH,
	};

	//path sent caches
	struct PathSentCache {
		Map<int, bool> confirmed_peers;
		int id;
	};

	//path get caches
	struct PathGetCache {
		struct NodeInfo {
			NodePath path;
			ObjectID instance;
		};

		Map<int, NodeInfo> nodes;
	};

	Ref<NetworkedMultiplayerPeer> network_peer;

	struct MultiplayerState {
		Ref<NetworkedMultiplayerPeer> peer;
		int rpc_sender_id;
		Set<int> connected_peers;
		HashMap<NodePath, PathSentCache> path_send_cache;
		Map<int, PathGetCache> path_get_cache;
		int last_send_cache_id;
		Vector<uint8_t> packet_cache;
		Node *root;

		MultiplayerState() {
			clear();
		}

		void clear() {
			connected_peers.clear();
			path_get_cache.clear();
			path_send_cache.clear();
			last_send_cache_id = 1;
		}
	};

	MultiplayerState network_state;

	void clear() { network_state.clear(); }

	void set_root(Node *p_node) {
		network_state.root = p_node;
	}

	void set_network_peer(const Ref<NetworkedMultiplayerPeer> &p_peer) {
		network_state.peer = p_peer;
	}

	Ref<NetworkedMultiplayerPeer> get_network_peer() const {
		return network_state.peer;
	}

	void poll();
	void rpcp(Node *p_node, int p_peer_id, bool p_unreliable, const StringName &p_method, const Variant **p_arg, int p_argcount);
	void rsetp(Node *p_node, int p_peer_id, bool p_unreliable, const StringName &p_property, const Variant &p_value);
	void rpc(Node *p_from, int p_to, bool p_unreliable, bool p_set, const StringName &p_name, const Variant **p_arg, int p_argcount);

	void add_peer(int p_id);
	void del_peer(int p_id);

	bool has_network_peer() const { return network_state.peer.is_valid(); }
	const Set<int> get_connected_peers() const { return network_state.connected_peers; }
	int get_rpc_sender_id() const { return network_state.rpc_sender_id; }
};

#endif // MULTIPLAYER_PROTOCOL_H
