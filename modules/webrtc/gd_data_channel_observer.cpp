#include "webrtc_peer_connection_creator.h"

//debug output was temporarily taken from that main.cpp file
WebRTCPeerConnectionCreator::GD_DCO::GD_DCO()
{
  std::cout << "DataChannelObserver::Constructor\n";
}

void WebRTCPeerConnectionCreator::GD_DCO::OnStateChange() {
  std::cout << "DataChannelObserver::StateChange" << std::endl;
};

void WebRTCPeerConnectionCreator::GD_DCO::OnMessage(const webrtc::DataBuffer& buffer) {
  std::cout << "DataChannelObserver::Message" << std::endl;
  std::cout << std::string(buffer.data.data<char>(), buffer.data.size()) << std::endl;
};

void WebRTCPeerConnectionCreator::GD_DCO::OnBufferedAmountChange(uint64_t previous_amount) {
  std::cout << "DataChannelObserver::BufferedAmountChange(" << previous_amount << ")" << std::endl;
};
