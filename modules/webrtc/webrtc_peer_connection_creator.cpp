#include "webrtc_peer_connection_creator.h"
#include "media/base/mediaengine.h"

// #include "api/audio_codecs/builtin_audio_decoder_factory.h"
// #include "api/audio_codecs/builtin_audio_encoder_factory.h"
// #include "test/mock_audio_decoder_factory.h"
// #include "test/mock_audio_encoder_factory.h"
// #include "api/video_codecs/builtin_video_decoder_factory.h"
// #include "api/video_codecs/builtin_video_encoder_factory.h"


void WebRTCPeerConnectionCreator::_bind_methods()
{

  ClassDB::bind_method(D_METHOD("test"), &WebRTCPeerConnectionCreator::test);
  ClassDB::bind_method(D_METHOD("host_call"), &WebRTCPeerConnectionCreator::host_call);
  ADD_SIGNAL(MethodInfo("notify", PropertyInfo(Variant::STRING, "secret message")));
}

WebRTCPeerConnectionCreator::WebRTCPeerConnectionCreator()
{
  // pco.parent = this;
  // ptr_csdo->parent = this;  // CAUSES AN ERROR WHEN UNCOMMENTED - Freezes Godot - Idk why.
}

int WebRTCPeerConnectionCreator::host_call() {
  emit_signal("notify", "WebRTCPeerConnectionCreator:: hosting call");
  // 1. Create a PeerConnectionFactoryInterface. Check constructors for more
  // information about input parameters.

  rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> pc_factory;
  pc_factory = webrtc::CreateModularPeerConnectionFactory(
    nullptr, // rtc::Thread* network_thread,
    nullptr, // rtc::Thread* worker_thread,
    nullptr, // rtc::Thread* signaling_thread,
    nullptr, // std::unique_ptr<cricket::MediaEngineInterface> media_engine,
    nullptr, // std::unique_ptr<CallFactoryInterface> call_factory,
    nullptr  // std::unique_ptr<RtcEventLogFactoryInterface> event_log_factory
  );
  if (pc_factory.get() == nullptr)
    std::cout << "[FAILURE]: "; else std::cout << "[success]: ";
  std::cout << "peer connection factory\n";
    // return 0xBADFAC; // "bad factory" -> the factory isn't created correctly

  // 2. Create a PeerConnection object. Provide a configuration struct which
  // points to STUN and/or TURN servers used to generate ICE candidates, and
  // provide an object that implements the PeerConnectionObserver interface,
  // which is used to receive callbacks from the PeerConnection.

  webrtc::PeerConnectionInterface::RTCConfiguration configuration; // default configuration
  // GodotPeerConnectionObserver pco;

  // rtc::scoped_refptr<webrtc::PeerConnectionInterface> peer_connection;
  peer_connection = pc_factory->CreatePeerConnection(
    configuration, nullptr, nullptr, &pco);

  if (peer_connection.get() == nullptr)
  std::cout << "[FAILURE]: "; else std::cout << "[success]: ";
  std::cout << "peer connection\n";
    // return 0xBADC; // "bad connection" -> the peer connection isn't created correctly

  // 3. Create local MediaStreamTracks using the PeerConnectionFactory and add
  // them to PeerConnection by calling AddTrack (or legacy method, AddStream).

  // Do I need to do step #3 for data channels?
  // CreateDataChannel(

  webrtc::DataChannelInit dc_config;
  data_channel = peer_connection->CreateDataChannel("channel", &dc_config);

  // 4. Create an offer, call SetLocalDescription with it, serialize it, and send
  // it to the remote peer

  peer_connection->CreateOffer(
    ptr_csdo, // CreateSessionDescriptionObserver* observer,
    webrtc::PeerConnectionInterface::RTCOfferAnswerOptions() // const MediaConstraintsInterface* constraints
  );
  // std::cout << "[FAILURE]: "; else std::cout << "[success]: ";
  // std::cout << "create offer\n";

  // 5. Once an ICE candidate has been gathered, the PeerConnection will call the
  // observer function OnIceCandidate. The candidates must also be serialized and
  // sent to the remote peer.
  //
  // 6. Once an answer is received from the remote peer, call
  // SetRemoteDescription with the remote answer.
  //
  // 7. Once a remote candidate is received from the remote peer, provide it to
  // the PeerConnection by calling AddIceCandidate.
  //
  return 0;
}

WebRTCPeerConnectionCreator::~WebRTCPeerConnectionCreator()
{
  // delete peerConnectionFactory;
}

void WebRTCPeerConnectionCreator::test()
{
  int just_some_value = 1337;
}
