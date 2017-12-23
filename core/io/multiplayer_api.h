#ifndef MULTIPLAYER_PROTOCOL_H
#define MULTIPLAYER_PROTOCOL_H

#include "core/io/networked_multiplayer_peer.h"
#include "core/reference.h"

class MultiplayerAPI : public Reference {

	GDCLASS(MultiplayerAPI, Reference);

private:
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
	int rpc_sender_id;
	Set<int> connected_peers;
	HashMap<NodePath, PathSentCache> path_send_cache;
	Map<int, PathGetCache> path_get_cache;
	int last_send_cache_id;
	Vector<uint8_t> packet_cache;
	Node *root_node;

protected:
	static void _bind_methods();

	void _process_packet(int p_from, const uint8_t *p_packet, int p_packet_len);
	void _process_simplify_path(int p_from, const uint8_t *p_packet, int p_packet_len);
	void _process_confirm_path(int p_from, const uint8_t *p_packet, int p_packet_len);
	Node *_process_get_node(int p_from, const uint8_t *p_packet, int p_packet_len);
	void _process_rpc(Node *p_node, const StringName &p_name, int p_from, const uint8_t *p_packet, int p_packet_len, int p_offset);
	void _process_rset(Node *p_node, const StringName &p_name, int p_from, const uint8_t *p_packet, int p_packet_len, int p_offset);

	void _send_rpc(Node *p_from, int p_to, bool p_unreliable, bool p_set, const StringName &p_name, const Variant **p_arg, int p_argcount);
	bool _send_confirm_path(NodePath p_path, PathSentCache *psc, int p_from);

public:
	enum NetworkCommands {
		NETWORK_COMMAND_REMOTE_CALL,
		NETWORK_COMMAND_REMOTE_SET,
		NETWORK_COMMAND_SIMPLIFY_PATH,
		NETWORK_COMMAND_CONFIRM_PATH,
	};

	void clear() {
		connected_peers.clear();
		path_get_cache.clear();
		path_send_cache.clear();
		last_send_cache_id = 1;
	}

	void set_root_node(Node *p_node) {
		root_node = p_node;
	}

	void set_network_peer(const Ref<NetworkedMultiplayerPeer> &p_peer) {
		network_peer = p_peer;
	}

	Ref<NetworkedMultiplayerPeer> get_network_peer() const {
		return network_peer;
	}

	void poll();
	// Called by Node.rpc
	void rpcp(Node *p_node, int p_peer_id, bool p_unreliable, const StringName &p_method, const Variant **p_arg, int p_argcount);
	// Called by Node.rset
	void rsetp(Node *p_node, int p_peer_id, bool p_unreliable, const StringName &p_property, const Variant &p_value);

	void add_peer(int p_id);
	void del_peer(int p_id);

	bool has_network_peer() const { return network_peer.is_valid(); }
	const Set<int> get_connected_peers() const { return connected_peers; }
	int get_rpc_sender_id() const { return rpc_sender_id; }
	int get_network_unique_id() const;
	bool is_server() const;

	MultiplayerAPI();
	~MultiplayerAPI();
};

#endif // MULTIPLAYER_PROTOCOL_H
