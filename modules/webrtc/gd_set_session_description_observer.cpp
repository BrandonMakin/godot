#include "webrtc_peer.h"

void WebRTCPeer::GD_SSDO::OnSuccess() {
  std::string message = "SetSessionDescriptionObserver::OnSuccess";
  // parent->emit_signal("notify", "WebRTCPeer:: hosting call");
  std::cout << message << std::endl;
};

void WebRTCPeer::GD_SSDO::OnFailure(const std::string& error) {
  std::string message = "SetSessionDescriptionObserver::OnFailure: error = ";
  message += error;
  // parent->emit_signal("notify", "WebRTCPeer:: hosting call");
  std::cout << message << std::endl;
};
