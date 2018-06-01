#include "webrtc_peer_connection_creator.h"

// #include "api/audio_codecs/builtin_audio_decoder_factory.h"
// #include "api/audio_codecs/builtin_audio_encoder_factory.h"
// #include "test/mock_audio_decoder_factory.h"
// #include "test/mock_audio_encoder_factory.h"
// #include "api/video_codecs/builtin_video_decoder_factory.h"
// #include "api/video_codecs/builtin_video_encoder_factory.h"

void WebRTCPeerConnectionCreator::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("test"), &WebRTCPeerConnectionCreator::test);
}

WebRTCPeerConnectionCreator::WebRTCPeerConnectionCreator()
{
  /** Version 1 **/
  // webrtc::CreatePeerConnectionFactory(
  //   webrtc::MockAudioEncoderFactory::CreateUnusedFactory();
  //   webrtc::MockAudioDecoderFactory::CreateUnusedFactory();
  // );

  /** Version 2 **/
  // webrtc::CreatePeerConnectionFactory(
  //   nullptr, // rtc::Thread* network_thread,
  //   nullptr, // rtc::Thread* worker_thread,
  //   nullptr, // rtc::Thread* signaling_thread,
  //   nullptr, // rtc::scoped_refptr<AudioDeviceModule> default_adm,
  //   webrtc::CreateBuiltinAudioEncoderFactory(),
  //   webrtc::CreateBuiltinAudioDecoderFactory(),
  //   nullptr // VideoDecoderFactory
  //   nullptr, // rtc::scoped_refptr<AudioMixer> audio_mixer,
  //   nullptr  // rtc::scoped_refptr<AudioProcessing> audio_processing);
  // );

  /** Version 3 **/
  webrtc::CreateModularPeerConnectionFactory
  (
    nullptr, // rtc::Thread* network_thread,
    nullptr, // rtc::Thread* worker_thread,
    nullptr, // rtc::Thread* signaling_thread,
    nullptr, // std::unique_ptr<cricket::MediaEngineInterface> media_engine,
    nullptr, // std::unique_ptr<CallFactoryInterface> call_factory,
    nullptr  // std::unique_ptr<RtcEventLogFactoryInterface> event_log_factory
    // // For native C++, depend on "peerconnection" without media instead of "libjingle_peerconnection"
    // deps = [ "pc:peerconnection" ]
  );
}

WebRTCPeerConnectionCreator::~WebRTCPeerConnectionCreator()
{
  // delete peerConnectionFactory;
}

void WebRTCPeerConnectionCreator::test()
{
  int just_some_value = 1337;
}
