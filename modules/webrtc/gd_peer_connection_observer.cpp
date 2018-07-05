#include "webrtc_peer.h"

WebRTCPeer::GD_PCO::GD_PCO(WebRTCPeer* parent)
{
  this->parent = parent;
}

void WebRTCPeer::GD_PCO::OnSignalingChange(webrtc::PeerConnectionInterface::SignalingState new_state)
{
  // parent->emit_signal("notify", "PeerConnectionObserver::OnSignalingChange");
  std::cout << "OnSignalingChange" << std::endl;
}

void WebRTCPeer::GD_PCO::OnAddStream(rtc::scoped_refptr<webrtc::MediaStreamInterface> stream)
{
  // parent->emit_signal("notify", "PeerConnectionObserver::OnSignalingChange");
  std::cout << "OnAddStream " << std::endl;
}

void WebRTCPeer::GD_PCO::OnRemoveStream(rtc::scoped_refptr<webrtc::MediaStreamInterface> stream)
{
  // parent->emit_signal("notify", "PeerConnectionObserver::OnSignalingChange");
  std::cout << "PeerConnectionObserver::OnRemoveStream " << std::endl;
}

void WebRTCPeer::GD_PCO::OnDataChannel(rtc::scoped_refptr<webrtc::DataChannelInterface> data_channel)
{
  // parent->emit_signal("notify", "PeerConnectionObserver::OnSignalingChange");
  std::cout << "PeerConnectionObserver::OnDataChannel " << std::endl;
}

void WebRTCPeer::GD_PCO::OnRenegotiationNeeded()
{
  // parent->emit_signal("notify", "PeerConnectionObserver::OnSignalingChange");
  std::cout << "PeerConnectionObserver::OnRenegotiationNeeded" << std::endl;

  // parent->peer_connection->CreateOffer(
  //   parent->ptr_csdo, // CreateSessionDescriptionObserver* observer,
  //   webrtc::PeerConnectionInterface::RTCOfferAnswerOptions() // const MediaConstraintsInterface* constraints
  // );
  // std::cout << "Trying to create offer from GD_PCO\n";

}

void WebRTCPeer::GD_PCO::OnIceConnectionChange(webrtc::PeerConnectionInterface::IceConnectionState new_state)
{
  // parent->emit_signal("notify", "PeerConnectionObserver::OnSignalingChange");
  std::cout << "OnIceConnectionChange " << std::endl;
}

void WebRTCPeer::GD_PCO::OnIceGatheringChange(webrtc::PeerConnectionInterface::IceGatheringState new_state)
{
  // parent->emit_signal("notify", "PeerConnectionObserver::OnSignalingChange");
  std::cout << "OnIceGatheringChange " << std::endl;
}

void WebRTCPeer::GD_PCO::OnIceCandidate(const webrtc::IceCandidateInterface* candidate)
{
  // parent->emit_signal("notify", "PeerConnectionObserver::OnSignalingChange");
  std::cout << "OnIceCandidate " << std::endl;
}
