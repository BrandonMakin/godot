#ifndef WEBRTC_TEST_H
#define WEBRTC_TEST_H

#include "core/ustring.h"
#include "reference.h"

class WebRTCTest : public Reference {
  GDCLASS(WebRTCTest, Reference);

protected:
    static void _bind_methods();

public:

	void test();

	WebRTCTest();
	// ~WebRTCTest();
};

#endif
