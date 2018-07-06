#include "webrtc_peer.h"

WebRTCPeer::GD_PCO::GD_PCO(WebRTCPeer* parent)
{
  this->parent = parent;
}

void WebRTCPeer::GD_PCO::OnSignalingChange(webrtc::PeerConnectionInterface::SignalingState new_state)
{
  parent->emit_signal("notify", "PeerConnectionObserver::OnSignalingChange - doing nothing");
  // std::cout << "OnSignalingChange" << std::endl;
}

void WebRTCPeer::GD_PCO::OnAddStream(rtc::scoped_refptr<webrtc::MediaStreamInterface> stream)
{
  parent->emit_signal("notify", "PeerConnectionObserver::OnAddStream");
  // std::cout << "OnAddStream " << std::endl;
}

void WebRTCPeer::GD_PCO::OnRemoveStream(rtc::scoped_refptr<webrtc::MediaStreamInterface> stream)
{
  parent->emit_signal("notify", "PeerConnectionObserver::OnRemoveStream");
  // std::cout << "PeerConnectionObserver::OnRemoveStream " << std::endl;
}

void WebRTCPeer::GD_PCO::OnDataChannel(rtc::scoped_refptr<webrtc::DataChannelInterface> data_channel)
{
  parent->emit_signal("notify", "PeerConnectionObserver::OnDataChannel");
  // std::cout << "PeerConnectionObserver::OnDataChannel " << std::endl;
}

void WebRTCPeer::GD_PCO::OnRenegotiationNeeded()
{
  parent->emit_signal("notify", "PeerConnectionObserver::OnRenegotiationNeeded");
  // std::cout << "PeerConnectionObserver::OnRenegotiationNeeded" << std::endl;

  // parent->peer_connection->CreateOffer(
  //   parent->ptr_csdo, // CreateSessionDescriptionObserver* observer,
  //   webrtc::PeerConnectionInterface::RTCOfferAnswerOptions() // const MediaConstraintsInterface* constraints
  // );
  // std::cout << "Trying to create offer from GD_PCO\n";

}

void WebRTCPeer::GD_PCO::OnIceConnectionChange(webrtc::PeerConnectionInterface::IceConnectionState new_state)
{
  parent->emit_signal("notify", "PeerConnectionObserver::OnIceConnectionChange");
  // std::cout << "OnIceConnectionChange " << std::endl;
}

void WebRTCPeer::GD_PCO::OnIceGatheringChange(webrtc::PeerConnectionInterface::IceGatheringState new_state)
{
  parent->emit_signal("notify", "PeerConnectionObserver::OnIceGatheringChange");
  // std::cout << "OnIceGatheringChange " << std::endl;
}

void WebRTCPeer::GD_PCO::OnIceCandidate(const webrtc::IceCandidateInterface* candidate)
{
  parent->emit_signal("notify", "PeerConnectionObserver::OnIceCandidate [warning: won't send ice candidates]");
  // std::cout << "OnIceCandidate " << std::endl;

  // 5. Once an ICE candidate has been gathered, the PeerConnection will call the
  // observer function OnIceCandidate. The candidates must also be serialized and
  // sent to the remote peer.


}
