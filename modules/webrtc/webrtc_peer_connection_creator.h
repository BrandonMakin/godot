#ifndef WEBRTC_PEER_CONNECTION_CREATOR_H
#define WEBRTC_PEER_CONNECTION_CREATOR_H

#include "reference.h"
#include "api/peerconnectioninterface.h"
// #include "thirdparty/webrtc/api/peerconnectioninterface.h"

class WebRTCPeerConnectionCreator : public Reference {
  GDCLASS(WebRTCPeerConnectionCreator, Reference);

protected:
    static void _bind_methods();

public:
  rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory;
  // talk_base::scoped_refptr<PeerConnectionFactoryInterface> peerConnectionFactory;
  // PeerConnectionFactory peerConnectionFactory;
  void test();

  WebRTCPeerConnectionCreator();
  ~WebRTCPeerConnectionCreator();
};

#endif //WEBRTC_PEER_CONNECTION_CREATOR
