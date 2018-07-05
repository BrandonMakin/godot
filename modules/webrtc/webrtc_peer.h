#ifndef WEBRTC_PEER_H
#define WEBRTC_PEER_H

#include <iostream> //remove eventually
#include "core/ustring.h"
#include "reference.h"
#include "api/peerconnectioninterface.h"
// #include "gd_peer_connection_observer.h"
// #include "thirdparty/webrtc/api/peerconnectioninterface.h"

// class GodotPeerConnectionObserver;

class WebRTCPeer : public Reference {
                                    // public webrtc::PeerConnectionObserver,
                                    // public webrtc::CreateSessionDescriptionObserver {
  GDCLASS(WebRTCPeer, Reference);

protected:
    static void _bind_methods();

public:


  void test();
  int host_call();
  void set_remote_description(String sdp);

  WebRTCPeer();
  ~WebRTCPeer();
// };

/** PeerConnectionObserver callback functions **/
  class GD_PCO : public webrtc::PeerConnectionObserver {
  public:
    WebRTCPeer* parent;

    GD_PCO(WebRTCPeer* parent);

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

  /** CreateSessionDescriptionObserver callback functions **/
  class GD_CSDO : public webrtc::CreateSessionDescriptionObserver {
  public:
    WebRTCPeer* parent;

    GD_CSDO(WebRTCPeer* parent);

    void OnSuccess(webrtc::SessionDescriptionInterface* desc) override;

    void OnFailure(const std::string& error) override;

    // void AddRef()
  };
  /** DataChannelObserver callback functions **/
  class GD_DCO : public webrtc::DataChannelObserver {
  public:
    GD_DCO();
    void OnStateChange() override;
    void OnMessage(const webrtc::DataBuffer& buffer) override;

    void OnBufferedAmountChange(uint64_t previous_amount) override;
  };

  /** SetSessionDescriptionObserver callback functions **/
  class GD_SSDO : public webrtc::SetSessionDescriptionObserver {
  // public:
    void OnSuccess() override;
    void OnFailure(const std::string& error) override;
  };

  rtc::scoped_refptr<webrtc::PeerConnectionInterface> peer_connection;
  rtc::scoped_refptr<webrtc::DataChannelInterface> data_channel;

  rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> pc_factory;

  // std::unique_ptr<rtc::Thread> signaling_thread;
  rtc::Thread* signaling_thread;
  webrtc::DataChannelInit data_channel_config;


  GD_PCO pco;
  GD_DCO dco;
  rtc::scoped_refptr<GD_SSDO> ptr_ssdo;
  rtc::scoped_refptr<GD_CSDO> ptr_csdo;


};
#endif //WEBRTC_PEER_CONNECTION_CREATOR
