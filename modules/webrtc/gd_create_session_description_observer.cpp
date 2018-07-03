#include "webrtc_peer_connection_creator.h"

// WebRTCPeerConnectionCreator::GD_CSDO::GD_CSDO(WebRTCPeerConnectionCreator* parent)
// {
//   this->parent = parent;
//   std::cout << "GD_CSDO::Constructor\n";
// }

void WebRTCPeerConnectionCreator::GD_CSDO::OnSuccess(webrtc::SessionDescriptionInterface* desc) {
  std::cout << "CreateSessionDescriptionObserver::OnSuccess" << std::endl;
  // peer_connection_->SetLocalDescription(
  //     DummySetSessionDescriptionObserver::Create(), desc);
};

void WebRTCPeerConnectionCreator::GD_CSDO::OnFailure(const std::string& error) {
  std::cout << "CreateSessionDescriptionObserver::OnFailure: error = " << error << std::endl;
};
