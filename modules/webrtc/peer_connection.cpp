#include "peer_connection.h"

void PeerConnection::PeerConnectionObserver::OnSignalingChange(webrtc::PeerConnectionInterface::SignalingState new_state) {

}
void PeerConnection::PeerConnectionObserver::OnAddStream(rtc::scoped_refptr<webrtc::MediaStreamInterface> stream) {

}
void PeerConnection::PeerConnectionObserver::OnRemoveStream(rtc::scoped_refptr<webrtc::MediaStreamInterface> stream) {

}
void PeerConnection::PeerConnectionObserver::OnDataChannel(rtc::scoped_refptr<webrtc::DataChannelInterface> data_channel) {

}
void PeerConnection::PeerConnectionObserver::OnRenegotiationNeeded() {
  // emit_signal("state_changed");
}
void PeerConnection::PeerConnectionObserver::OnIceConnectionChange(webrtc::PeerConnectionInterface::IceConnectionState new_state) {

}
void PeerConnection::PeerConnectionObserver::OnIceGatheringChange(webrtc::PeerConnectionInterface::IceGatheringState new_state) {

}
void PeerConnection::PeerConnectionObserver::OnIceCandidate(const webrtc::IceCandidateInterface* candidate) {

}

//////////////////////////////////////////////////////////////////////

void PeerConnection::DataChannelObserver::OnStateChange()  {
	// emit_signal("state_changed");
}
void PeerConnection::DataChannelObserver::OnMessage(const webrtc::DataBuffer& buffer)  {
  // emit_signal("message_received", /*I'm not sure what to send as an argument*/);
}
void PeerConnection::DataChannelObserver::OnBufferedAmountChange(uint64_t previous_amount)  {
  // emit_signal("buffer_amount_changed", /* How do I pass a uint64_t? */);
}
