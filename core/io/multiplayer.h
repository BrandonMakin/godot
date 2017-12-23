#ifndef MULTIPLAYER_PROTOCOL_H
#define MULTIPLAYER_PROTOCOL_H

#include "core/io/networked_multiplayer_peer.h"

class MultiplayerProtocol {

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

	static void network_poll(MultiplayerState &state);
	static void _network_process_packet(MultiplayerState &state, int p_from, const uint8_t *p_packet, int p_packet_len);
	static void _rpc(MultiplayerState &state, Node *p_from, int p_to, bool p_unreliable, bool p_set, const StringName &p_name, const Variant **p_arg, int p_argcount);
	static void add_peer(MultiplayerState &state, int p_id);
	static void del_peer(MultiplayerState &state, int p_id);

	static void rpcp(Node *p_node, int p_peer_id, bool p_unreliable, const StringName &p_method, const Variant **p_arg, int p_argcount);
	static void rsetp(Node *p_node, int p_peer_id, bool p_unreliable, const StringName &p_property, const Variant &p_value);
};

#endif // MULTIPLAYER_PROTOCOL_H
