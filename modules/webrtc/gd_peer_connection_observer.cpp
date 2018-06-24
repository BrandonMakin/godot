#include "webrtc_peer_connection_creator.h"

// WebRTCPeerConnectionCreator::GD_PCO::GD_PCO(WebRTCPeerConnectionCreator* parent)
// {
//   this->parent = parent;
// }

void WebRTCPeerConnectionCreator::GD_PCO::OnSignalingChange(webrtc::PeerConnectionInterface::SignalingState new_state)
{
  parent->emit_signal("notify", "PeerConnectionObserver::OnSignalingChange");
}

void WebRTCPeerConnectionCreator::GD_PCO::OnAddStream(rtc::scoped_refptr<webrtc::MediaStreamInterface> stream)
{
  parent->emit_signal("notify", "PeerConnectionObserver::OnSignalingChange");
}

void WebRTCPeerConnectionCreator::GD_PCO::OnRemoveStream(rtc::scoped_refptr<webrtc::MediaStreamInterface> stream)
{
  parent->emit_signal("notify", "PeerConnectionObserver::OnSignalingChange");
}

void WebRTCPeerConnectionCreator::GD_PCO::OnDataChannel(rtc::scoped_refptr<webrtc::DataChannelInterface> data_channel)
{
  parent->emit_signal("notify", "PeerConnectionObserver::OnSignalingChange");
}

void WebRTCPeerConnectionCreator::GD_PCO::OnRenegotiationNeeded()
{
  parent->emit_signal("notify", "PeerConnectionObserver::OnSignalingChange");
}

void WebRTCPeerConnectionCreator::GD_PCO::OnIceConnectionChange(webrtc::PeerConnectionInterface::IceConnectionState new_state)
{
  parent->emit_signal("notify", "PeerConnectionObserver::OnSignalingChange");
}

void WebRTCPeerConnectionCreator::GD_PCO::OnIceGatheringChange(webrtc::PeerConnectionInterface::IceGatheringState new_state)
{
  parent->emit_signal("notify", "PeerConnectionObserver::OnSignalingChange");
}

void WebRTCPeerConnectionCreator::GD_PCO::OnIceCandidate(const webrtc::IceCandidateInterface* candidate)
{
  parent->emit_signal("notify", "PeerConnectionObserver::OnSignalingChange");
}
