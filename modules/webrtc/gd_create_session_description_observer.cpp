#include "webrtc_peer_connection_creator.h"

// WebRTCPeerConnectionCreator::GD_CSDO::GD_CSDO(WebRTCPeerConnectionCreator* parent)
// {
//   this->parent = parent;
// }

void WebRTCPeerConnectionCreator::GD_CSDO::OnSuccess(webrtc::SessionDescriptionInterface* desc) {
  // parent->emit_signal("notify", "CreateSessionDescriptionObserver::OnSuccess");
};

void WebRTCPeerConnectionCreator::GD_CSDO::OnFailure(const std::string& error) {
  // parent->emit_signal("notify", "CreateSessionDescriptionObserver::OnFailure");
};
