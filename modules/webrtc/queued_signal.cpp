#include "queued_signal.h"

QueuedSignal::QueuedSignal(Object* parent_, const StringName &p_name_, VARIANT_ARG_DECLARE) : // parent(parent_),
                                                                                        p_name(p_name_)
{
  this->parent = parent;

  VARIANT_ARGPTRS;


  // The following is based off of Object.emit_signal(const StringName &p_name, VARIANT_ARG_DECLARE)
  // and is designed to get this Signal to a state where it can call Object.emit_signal(const StringName &p_name, const Variant **p_args, int p_argcount);
  arg_c = 0;
  bool moreArguments = true;
  int i;
  for (i = 0; i < VARIANT_ARG_MAX; ++i)
  {
    this->args[i] = argptr[i];

    if (moreArguments && (argptr[i]->get_type() != Variant::NIL))
      ++arg_c;
    else
      moreArguments = false;
  }
}

Error QueuedSignal::emit_signal()
{
  // return parent->emit_signal(p_name, VARIANT_ARGS_FROM_ARRAY(args));
  return parent->emit_signal(p_name, args, arg_c);
}
