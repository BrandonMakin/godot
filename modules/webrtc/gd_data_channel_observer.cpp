#include "webrtc_peer.h"

//debug output was temporarily taken from that main.cpp file
WebRTCPeer::GD_DCO::GD_DCO()
{
  std::cout << "DataChannelObserver::Constructor\n";
}

void WebRTCPeer::GD_DCO::OnStateChange() {
  std::cout << "DataChannelObserver::StateChange" << std::endl;
};

void WebRTCPeer::GD_DCO::OnMessage(const webrtc::DataBuffer& buffer) {
  std::cout << "DataChannelObserver::Message" << std::endl;
  std::cout << std::string(buffer.data.data<char>(), buffer.data.size()) << std::endl;
};

void WebRTCPeer::GD_DCO::OnBufferedAmountChange(uint64_t previous_amount) {
  std::cout << "DataChannelObserver::BufferedAmountChange(" << previous_amount << ")" << std::endl;
};
