#include "webrtc_peer.h"

WebRTCPeer::GD_CSDO::GD_CSDO(WebRTCPeer* parent)
{
  this->parent = parent;
}

void WebRTCPeer::GD_CSDO::OnSuccess(webrtc::SessionDescriptionInterface* desc) {
  std::cout << "CreateSessionDescriptionObserver::OnSuccess" << std::endl;
  // peer_connection_->SetLocalDescription(
  //     DummySetSessionDescriptionObserver::Create(), desc);
};

void WebRTCPeer::GD_CSDO::OnFailure(const std::string& error) {
  std::cout << "CreateSessionDescriptionObserver::OnFailure: error = " << error << std::endl;
};
