#include "webrtc_test.h"

WebRTCTest::WebRTCTest()
{
}

// WebRTCTest::~WebRTCTest()
// {
// }

void WebRTCTest::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("test"), &WebRTCTest::test);
  ADD_SIGNAL(MethodInfo("test_signal", PropertyInfo(Variant::INT, "secret message")));
}

void WebRTCTest::test()
{
  int just_some_value = 1337;
	emit_signal("test_signal", just_some_value);
}
