#include "webrtc_peer.h"

WebRTCPeer::GD_CSDO::GD_CSDO(WebRTCPeer* parent)
{
  this->parent = parent;
}

void WebRTCPeer::GD_CSDO::OnSuccess(webrtc::SessionDescriptionInterface* desc) {
  std::string message = "CreateSessionDescriptionObserver::OnSuccess";
  parent->emit_signal("notify", "WebRTCPeer:: hosting call");
  std::cout << message << std::endl;

  // now that you have your offer, call SetLocalDescription with it,
  // serialize it, and send it to the remote peer

  // peer_connection_->SetLocalDescription(
  //     DummySetSessionDescriptionObserver::Create(), desc);
};

void WebRTCPeer::GD_CSDO::OnFailure(const std::string& error) {
  std::string message = "CreateSessionDescriptionObserver::OnFailure: error = ";
  message += error;
  parent->emit_signal("notify", "WebRTCPeer:: hosting call");
  std::cout << message << std::endl;
};
