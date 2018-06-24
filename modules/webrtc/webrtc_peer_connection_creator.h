#ifndef WEBRTC_PEER_CONNECTION_CREATOR_H
#define WEBRTC_PEER_CONNECTION_CREATOR_H

#include "reference.h"
#include "api/peerconnectioninterface.h"
// #include "gd_peer_connection_observer.h"
// #include "thirdparty/webrtc/api/peerconnectioninterface.h"

// class GodotPeerConnectionObserver;

class WebRTCPeerConnectionCreator : public Reference {
                                    // public webrtc::PeerConnectionObserver,
                                    // public webrtc::CreateSessionDescriptionObserver {
  GDCLASS(WebRTCPeerConnectionCreator, Reference);

protected:
    static void _bind_methods();

public:
  // enum WebRTCError {
  //  CANNOT_CREATE_PEER_CONNECTION_FACTORY,
  //  MODE_SECOND
  // };

  // rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory;
  void test();
  int host_call();

  // GodotPeerConnectionObserver pco;

  WebRTCPeerConnectionCreator();
  ~WebRTCPeerConnectionCreator();
// };

/** PeerConnectionObserver callback functions **/

  // Triggered when the SignalingState changes.
  class GD_PCO : public webrtc::PeerConnectionObserver {
    // friend class WebRTCPeerConnectionCreator;
  public:
    WebRTCPeerConnectionCreator* parent;

    // GD_PCO(WebRTCPeerConnectionCreator* parent);

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
      WebRTCPeerConnectionCreator* parent;

    // GD_CSDO(WebRTCPeerConnectionCreator* parent);

    void OnSuccess(webrtc::SessionDescriptionInterface* desc) override;

    void OnFailure(const std::string& error) override;

    // void AddRef()
  };

  GD_PCO pco;
  rtc::scoped_refptr<GD_CSDO> ptr_csdo;


};
#endif //WEBRTC_PEER_CONNECTION_CREATOR
