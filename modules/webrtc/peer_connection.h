#ifndef peer_connection_h
#define peer_connection_h

#include "reference.h"
#include "core/ustring.h"

// #include <iostream>
// #include <memory>
// #include <mutex>
// #include <queue>
// #include <string>
// #include <thread>

#include "thirdparty/webrtc/api/audio_codecs/builtin_audio_decoder_factory.h"
#include "thirdparty/webrtc/api/audio_codecs/builtin_audio_encoder_factory.h"
#include "thirdparty/webrtc/api/peerconnectioninterface.h"
#include "thirdparty/webrtc/rtc_base/flags.h"
#include "thirdparty/webrtc/rtc_base/physicalsocketserver.h"
#include "thirdparty/webrtc/rtc_base/ssladapter.h"
#include "thirdparty/webrtc/rtc_base/thread.h"

class PeerConnection : public Reference {
  GDCLASS(PeerConnection, Reference);

  webrtc::PeerConnectionInterface *peer_connection;
  // webrtc::DataChannelInterface *data_channel;

  String sdp_type;
protected:
      static void _bind_methods();
public:
  class PeerConnectionObserver : public webrtc::PeerConnectionObserver
  {
  public:
    void OnSignalingChange(webrtc::PeerConnectionInterface::SignalingState new_state) override;
    void OnAddStream(rtc::scoped_refptr<webrtc::MediaStreamInterface> stream) override;
    void OnRemoveStream(rtc::scoped_refptr<webrtc::MediaStreamInterface> stream) override;
    void OnDataChannel(rtc::scoped_refptr<webrtc::DataChannelInterface> data_channel) override;
    void OnRenegotiationNeeded() override;
    void OnIceConnectionChange(webrtc::PeerConnectionInterface::IceConnectionState new_state) override;
    void OnIceGatheringChange(webrtc::PeerConnectionInterface::IceGatheringState new_state) override;
    void OnIceCandidate(const webrtc::IceCandidateInterface* candidate) override;
  };

  //////////////////////////////////////////////////////////////////////
  class DataChannelObserver : public webrtc::DataChannelObserver
  {
  public:
    void OnStateChange() override;
    void OnMessage(const webrtc::DataBuffer& buffer) override;
    void OnBufferedAmountChange(uint64_t previous_amount) override;
  };

  // //////////////////////////////////////////////////////////////////////
  // class CreateSessionDescriptionObserver : public webrtc::CreateSessionDescriptionObserver
  // {
  // public:
  //   void OnSuccess(webrtc::SessionDescriptionInterface* desc) override;
  //   void OnFailure(const std::string& error) override;
  // };
  //
  // //////////////////////////////////////////////////////////////////////
  // class SetSessionDescriptionObserver : public webrtc::SetSessionDescriptionObserver {
  // public:
  //   void OnSuccess() override;
  //   void OnFailure(const std::string& error) override;
  // };

  DataChannelObserver dco;

};

#endif
