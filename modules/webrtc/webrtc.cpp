#include "webrtc.h"

WebRTC::WebRTC()
{
}

// WebRTC::~WebRTC()
// {
// }

void WebRTC::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("test"), &WebRTC::test);
  ADD_SIGNAL(MethodInfo("test_signal", PropertyInfo(Variant::INT, "secret message")));
}

void WebRTC::test()
{
  int just_some_value = 1337;
	emit_signal("test_signal", just_some_value);
}
