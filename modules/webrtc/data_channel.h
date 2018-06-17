#ifndef data_channel_h
#define data_channel_h

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

class DataChannel : public Reference {
  GDCLASS(DataChannel, Reference);

};

#endif
