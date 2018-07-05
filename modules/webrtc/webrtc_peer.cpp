#include "webrtc_peer.h"
#include "media/base/mediaengine.h"

// #include "api/audio_codecs/builtin_audio_decoder_factory.h"
// #include "api/audio_codecs/builtin_audio_encoder_factory.h"
// #include "test/mock_audio_decoder_factory.h"
// #include "test/mock_audio_encoder_factory.h"
// #include "api/video_codecs/builtin_video_decoder_factory.h"
// #include "api/video_codecs/builtin_video_encoder_factory.h"


void WebRTCPeer::_bind_methods()
{

  ClassDB::bind_method(D_METHOD("test"), &WebRTCPeer::test);
  ClassDB::bind_method(D_METHOD("host_call"), &WebRTCPeer::host_call);
  ClassDB::bind_method(D_METHOD("set_remote_description", "sdp"), &WebRTCPeer::set_remote_description);

  ADD_SIGNAL(MethodInfo("notify", PropertyInfo(Variant::STRING, "secret message")));
  ADD_SIGNAL(MethodInfo("offer_created", PropertyInfo(Variant::STRING, "sdp")));
  // ADD_SIGNAL(MethodInfo("new_ice_candidate", PropertyInfo(Variant::STRING, "candidate")));
}

WebRTCPeer::WebRTCPeer() :  pco(this)
                            , ptr_csdo(new rtc::RefCountedObject<GD_CSDO>(this))
                            , ptr_ssdo(new rtc::RefCountedObject<GD_SSDO>())
                            // , signalling_thread(new rtc::Thread)
{
  // 1. Create a PeerConnectionFactoryInterface.
  signaling_thread = new rtc::Thread;
  signaling_thread->Start();
  pc_factory = webrtc::CreateModularPeerConnectionFactory(
    nullptr, // rtc::Thread* network_thread,
    nullptr, // rtc::Thread* worker_thread,
    signaling_thread,
    nullptr, // std::unique_ptr<cricket::MediaEngineInterface> media_engine,
    nullptr, // std::unique_ptr<CallFactoryInterface> call_factory,
    nullptr  // std::unique_ptr<RtcEventLogFactoryInterface> event_log_factory
  );
  if (pc_factory.get() == nullptr)
    emit_signal("notify", "[FAILURE]: peer connection factory");
  else
    emit_signal("notify", "[success]: peer connection factory");
    // return 0xBADFAC; // "bad factory" -> the factory isn't created correctly

  // 2. Create a PeerConnection object. Provide a configuration struct which
  // points to STUN and/or TURN servers used to generate ICE candidates, and
  // provide an object that implements the PeerConnectionObserver interface,
  // which is used to receive callbacks from the PeerConnection.

  webrtc::PeerConnectionInterface::RTCConfiguration configuration; // default configuration

  webrtc::PeerConnectionInterface::IceServer ice_server;

  configuration.sdp_semantics = webrtc::SdpSemantics::kUnifiedPlan;  // Temporary @TODO look this line up
  configuration.enable_dtls_srtp = true;                             // Temporary @TODO look this line up

  ice_server.uri = "stun:stun.l.google.com:19302";
  configuration.servers.push_back(ice_server); // add ice_server to configuration

  peer_connection = pc_factory->CreatePeerConnection(
    configuration, nullptr, nullptr, &pco);

  if (peer_connection.get() == nullptr)
    emit_signal("notify", "[FAILURE]: peer connection");
  else
    emit_signal("notify", "[success]: peer connection");
  // return 0xBADC; // "bad connection" -> the peer connection isn't created correctly

  // 3. Create local MediaStreamTracks using the PeerConnectionFactory and add
  // them to PeerConnection by calling AddTrack (or legacy method, AddStream).
  data_channel = peer_connection->CreateDataChannel("channel", &data_channel_config);
}

int WebRTCPeer::host_call() {
  emit_signal("notify", "WebRTCPeer::host_call");

  // 4. Create an offer, call SetLocalDescription with it, serialize it, and send
  // it to the remote peer

  // Should I do step 4 in GD_PCO::OnRenegotiationNeeded?
  // I'm not sure. The example client doesn't even use OnRenegotiationNeeded

  //Create an offer - the rest of step 4 should be in CSDO::OnSuccess
  peer_connection->CreateOffer(
    ptr_csdo, // CreateSessionDescriptionObserver* observer,
    nullptr // webrtc::PeerConnectionInterface::RTCOfferAnswerOptions() // const MediaConstraintsInterface* constraints
  );
  //
  // 7. Once a remote candidate is received from the remote peer, provide it to
  // the PeerConnection by calling AddIceCandidate.
  //
  return 0;
}

void WebRTCPeer::set_remote_description(String sdp)
{
  // 6. Once an answer is received from the remote peer, call
  // SetRemoteDescription with the remote answer.

  //set the remote description to sdp
  emit_signal("notify", "WebRTCPeer::SetRemoteDescription - setting");
}

// void WebRTCPeer::add_ice_candidate

WebRTCPeer::~WebRTCPeer()
{
  // delete peerConnectionFactory;
}

void WebRTCPeer::test()
{
  int just_some_value = 1337;
}
