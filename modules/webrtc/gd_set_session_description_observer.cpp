#include "webrtc_peer.h"

WebRTCPeer::GD_SSDO::GD_SSDO(WebRTCPeer* parent)
{
  this->parent = parent;
}

void WebRTCPeer::GD_SSDO::OnSuccess() {
  std::string message = "SetSessionDescriptionObserver::OnSuccess - doing nothing";
  parent->emit_signal("notify", message.c_str());
  // std::cout << message << std::endl;
};

void WebRTCPeer::GD_SSDO::OnFailure(const std::string& error) {
  std::string message = "SetSessionDescriptionObserver::OnFailure: error = ";
  message += error;
  parent->emit_signal("notify", message.c_str());
  // std::cout << message << std::endl;
};
