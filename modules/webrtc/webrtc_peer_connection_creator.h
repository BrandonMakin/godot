#ifndef WEBRTC_PEER_CONNECTION_CREATOR_H
#define WEBRTC_PEER_CONNECTION_CREATOR_H

#include "reference.h"
#include "api/peerconnectioninterface.h"
#include "gd_peer_connection_observer.h"
// #include "thirdparty/webrtc/api/peerconnectioninterface.h"

class WebRTCPeerConnectionCreator : public Reference {
  GDCLASS(WebRTCPeerConnectionCreator, Reference);

protected:
    static void _bind_methods();

public:
  // enum WebRTCError {
  //  CANNOT_CREATE_PEER_CONNECTION_FACTORY,
  //  MODE_SECOND
  // };

  // rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory;
  void test();
  int host_call();

  WebRTCPeerConnectionCreator();
  ~WebRTCPeerConnectionCreator();
};

// VARIANT_ENUM_CAST(WebRTCPeerConnectionCreator::WebRTCError); // now functions that take WebRTCError can be bound.

#endif //WEBRTC_PEER_CONNECTION_CREATOR
