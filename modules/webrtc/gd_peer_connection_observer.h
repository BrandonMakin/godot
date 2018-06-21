#ifndef GD_PEER_CONNECTION_OBSERVER_H
#define GD_PEER_CONNECTION_OBSERVER_H

#include "api/peerconnectioninterface.h"


// class GodotPeerConnectionObserver {
class GodotPeerConnectionObserver : public webrtc::PeerConnectionObserver {
 // private:
  // Connection& parent;

 public:
   int test();
   GodotPeerConnectionObserver();
  // GodotPeerConnectionObserver(Connection& parent) : parent(parent) {

  // Triggered when the SignalingState changes.
  void OnSignalingChange(webrtc::PeerConnectionInterface::SignalingState new_state) override;

  // Triggered when media is received on a new stream from remote peer.
  void OnAddStream(rtc::scoped_refptr<webrtc::MediaStreamInterface> stream) override;

  // Triggered when a remote peer closes a stream.
  void OnRemoveStream(rtc::scoped_refptr<webrtc::MediaStreamInterface> stream) override;

  // Triggered when a remote peer opens a data channel.
  void OnDataChannel(rtc::scoped_refptr<webrtc::DataChannelInterface> data_channel) override;

  // Triggered when renegotiation is needed. For example, an ICE restart
  // has begun.
  void OnRenegotiationNeeded() override;

  // Called any time the IceConnectionState changes.
  void OnIceConnectionChange(webrtc::PeerConnectionInterface::IceConnectionState new_state) override;

  // Called any time the IceGatheringState changes.
  void OnIceGatheringChange(webrtc::PeerConnectionInterface::IceGatheringState new_state) override;

  // A new ICE candidate has been gathered.
  void OnIceCandidate(const webrtc::IceCandidateInterface* candidate) override;
};

#endif
