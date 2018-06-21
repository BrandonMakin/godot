#include "gd_peer_connection_observer.h"

GodotPeerConnectionObserver::GodotPeerConnectionObserver()
{

}

void GodotPeerConnectionObserver::OnSignalingChange(webrtc::PeerConnectionInterface::SignalingState new_state)
{

}

void GodotPeerConnectionObserver::OnAddStream(rtc::scoped_refptr<webrtc::MediaStreamInterface> stream)
{

}

void GodotPeerConnectionObserver::OnRemoveStream(rtc::scoped_refptr<webrtc::MediaStreamInterface> stream)
{

}

void GodotPeerConnectionObserver::OnDataChannel(rtc::scoped_refptr<webrtc::DataChannelInterface> data_channel)
{

}

void GodotPeerConnectionObserver::OnRenegotiationNeeded()
{

}

void GodotPeerConnectionObserver::OnIceConnectionChange(webrtc::PeerConnectionInterface::IceConnectionState new_state)
{

}

void GodotPeerConnectionObserver::OnIceGatheringChange(webrtc::PeerConnectionInterface::IceGatheringState new_state)
{

}

void GodotPeerConnectionObserver::OnIceCandidate(const webrtc::IceCandidateInterface* candidate)
{

}


int GodotPeerConnectionObserver::test()
{
  return 0xbeef;
}
