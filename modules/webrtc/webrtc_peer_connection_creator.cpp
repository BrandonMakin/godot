#include "webrtc_peer_connection_creator.h"

// #include "api/audio_codecs/builtin_audio_decoder_factory.h"
// #include "api/audio_codecs/builtin_audio_encoder_factory.h"

void WebRTCPeerConnectionCreator::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("test"), &WebRTCPeerConnectionCreator::test);
}

WebRTCPeerConnectionCreator::WebRTCPeerConnectionCreator()
{
  webrtc::CreatePeerConnectionFactory
  (
    nullptr, nullptr
    // webrtc::CreateBuiltinAudioEncoderFactory(),
    // webrtc::CreateBuiltinAudioDecoderFactory()
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
