#ifndef WEBRTC_QUEUED_SIGNAL_H
#define WEBRTC_QUEUED_SIGNAL_H

#include "object.h"

class QueuedSignal
{
  Object *parent;

  int arg_c;
  const StringName &p_name;
  const Variant *args[VARIANT_ARG_MAX];

public:
  QueuedSignal(Object* parent_, const StringName &p_name_, VARIANT_ARG_LIST);
  Error emit_signal();
};

#endif
