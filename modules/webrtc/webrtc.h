#ifndef WEBRTC_H
#define WEBRTC_H

#include "core/ustring.h"
#include "reference.h"

#include "thirdparty/webrtc/api/audio_codecs/builtin_audio_decoder_factory.h"
#include "thirdparty/webrtc/api/audio_codecs/builtin_audio_encoder_factory.h"
#include "thirdparty/webrtc/api/peerconnectioninterface.h"
#include "thirdparty/webrtc/rtc_base/flags.h"
#include "thirdparty/webrtc/rtc_base/physicalsocketserver.h"
#include "thirdparty/webrtc/rtc_base/ssladapter.h"
#include "thirdparty/webrtc/rtc_base/thread.h"

class WebRTC : public Reference {
  GDCLASS(WebRTC, Reference);

protected:
    static void _bind_methods();

public:

	void test();

	WebRTC();
	// ~WebRTC();
};

#endif
