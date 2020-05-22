#include <ruby.h>
#include <os/signpost.h>

#define EVENT_NAME "duration"

static VALUE cOsLog;
static VALUE cOsLogContext;

void chariot_core_log_free(struct os_log_s *os_log) {
  free(os_log);
}

VALUE chariot_core_log_id(VALUE self, VALUE subsystem, VALUE category)
{
  Check_Type(subsystem, T_STRING);
  Check_Type(category, T_STRING);

  struct os_log_s *os_log = os_log_create(
    StringValuePtr(subsystem),
    StringValuePtr(category)
  );

  return Data_Wrap_Struct(cOsLogContext, 0, &chariot_core_log_free, os_log);
}

VALUE chariot_core_topic_id(VALUE self, VALUE log)
{
  struct os_log_s *os_log;
  Data_Get_Struct(log, struct os_log_s, os_log);

  unsigned long long os_signpost_id = os_signpost_id_generate(os_log);
  return INT2NUM(os_signpost_id);
}

VALUE chariot_core_emit(VALUE self, VALUE log, VALUE event_id)
{
  struct os_log_s *os_log;
  Data_Get_Struct(log, struct os_log_s, os_log);

  unsigned long long os_event_id = NUM2INT(event_id);
  os_signpost_event_emit(os_log, os_event_id, EVENT_NAME);

  return Qnil;
}

VALUE chariot_core_start(VALUE self, VALUE log, VALUE event_id)
{
  struct os_log_s *os_log;
  Data_Get_Struct(log, struct os_log_s, os_log);

  unsigned long long os_event_id = NUM2INT(event_id);
  os_signpost_interval_begin(os_log, os_event_id, EVENT_NAME, "size: 1, pid: 71283");

  return Qnil;
}

VALUE chariot_core_stop(VALUE self, VALUE log, VALUE event_id)
{
  struct os_log_s *os_log;
  Data_Get_Struct(log, struct os_log_s, os_log);

  unsigned long long os_event_id = NUM2INT(event_id);
  os_signpost_interval_end(os_log, os_event_id, EVENT_NAME, "size: 2, pid: 71283");

  return Qnil;
}

void Init_chariot_core()
{
  VALUE mChariot = rb_define_module("Chariot");
  cOsLog = rb_define_class_under(mChariot, "Log", rb_cObject);
  cOsLogContext = rb_define_class_under(cOsLog, "Context", rb_cObject);

  rb_define_singleton_method(mChariot, "log_id", chariot_core_log_id, 2);
  rb_define_singleton_method(mChariot, "topic_id", chariot_core_topic_id, 1);
  rb_define_singleton_method(mChariot, "emit", chariot_core_emit, 2);
  rb_define_singleton_method(mChariot, "start", chariot_core_start, 2);
  rb_define_singleton_method(mChariot, "stop", chariot_core_stop, 2);
}
