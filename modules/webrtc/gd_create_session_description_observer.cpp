#include "webrtc_peer.h"

WebRTCPeer::GD_CSDO::GD_CSDO(WebRTCPeer* parent)
{
  this->parent = parent;
}

void WebRTCPeer::GD_CSDO::OnSuccess(webrtc::SessionDescriptionInterface* desc) {
  std::string message = "CreateSessionDescriptionObserver::OnSuccess";
  parent->emit_signal("notify", message.c_str());

  // now that you have your offer, call SetLocalDescription with it,
  // serialize it, and send it to the remote peer

  //call SetLocalDescription:
  parent->peer_connection->SetLocalDescription(parent->ptr_ssdo, desc);  // if an ssdo isn't needed, you can use DummySetSessionDescriptionObserver::Create()

  //Serialize:
  std::string sdp; // sdp = session description protocol
  desc->ToString(&sdp);
  parent->emit_signal("offer_created", sdp.c_str());

};

void WebRTCPeer::GD_CSDO::OnFailure(const std::string& error) {
  std::string message = "CreateSessionDescriptionObserver::OnFailure: error = ";
  message += error;
  parent->emit_signal("notify", message.c_str());
};
