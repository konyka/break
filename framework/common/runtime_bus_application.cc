#include "runtime_bus_application.h"

#include <memory>

namespace bk {

RuntimeBusApplication::~RuntimeBusApplication() { DeInit(); }

BreakRuntimeError RuntimeBusApplication::AttachRuntimeBus(BreakRuntimeBus* bus) {
  if (!bus) return BREAK_RUNTIME_INVALID;
  if (initialized_ || runtime_bus_) return BREAK_RUNTIME_REJECTED;
  runtime_bus_ = bus;
  return BREAK_RUNTIME_OK;
}

void RuntimeBusApplication::DetachRuntimeBus() {
  if (runtime_bus_ && subscriber_id_ != 0u) {
    (void)break_runtime_bus_unsubscribe(runtime_bus_, subscriber_id_);
  }
  subscriber_id_ = 0u;
  break_runtime_queue_destroy(runtime_queue_);
  runtime_queue_ = nullptr;
  runtime_bus_ = nullptr;
}

int RuntimeBusApplication::Init() {
  if (initialized_) return BREAK_RUNTIME_REJECTED;
  stats_ = {};

  const int base_result = BaseApplication::Init();
  if (base_result != 0) {
    BaseApplication::DeInit();
    return base_result;
  }
  if (!runtime_bus_) {
    initialized_ = true;
    return 0;
  }

  const BreakRuntimeQueueConfig config{64u, 16u};
  BreakRuntimeError result = break_runtime_queue_create(&config, &runtime_queue_);
  if (result == BREAK_RUNTIME_OK) {
    const u16 kind = BREAK_RUNTIME_IO_NOTICE_KIND;
    result = break_runtime_bus_subscribe(runtime_bus_, "framework.application.io",
                                         runtime_queue_, &kind, 1u, &subscriber_id_);
  }
  if (result != BREAK_RUNTIME_OK) {
    if (subscriber_id_ != 0u) {
      (void)break_runtime_bus_unsubscribe(runtime_bus_, subscriber_id_);
      subscriber_id_ = 0u;
    }
    break_runtime_queue_destroy(runtime_queue_);
    runtime_queue_ = nullptr;
    initialized_ = false;
    BaseApplication::DeInit();
    return result;
  }

  initialized_ = true;
  return 0;
}

void RuntimeBusApplication::DeInit() {
  DetachRuntimeBus();
  initialized_ = false;
  BaseApplication::DeInit();
}

void RuntimeBusApplication::Tick() {
  BaseApplication::Tick();
  if (!initialized_ || !runtime_queue_) return;

  for (;;) {
    BreakRuntimeOwnedMessage* raw_message = nullptr;
    const BreakRuntimeError result =
        break_runtime_queue_poll(runtime_queue_, &raw_message);
    if (result != BREAK_RUNTIME_OK || !raw_message) return;

    std::unique_ptr<BreakRuntimeOwnedMessage, void (*)(BreakRuntimeOwnedMessage*)>
        message(raw_message, break_runtime_message_release);
    BreakRuntimeIoNotice notice{};
    if (break_runtime_io_notice_view(message.get(), &notice) != BREAK_RUNTIME_OK) {
      ++stats_.malformed_notices;
      continue;
    }
    ++stats_.io_notices;
    OnRuntimeIoNotice(notice);
  }
}

RuntimeBusApplicationStats RuntimeBusApplication::runtime_bus_stats() const {
  return stats_;
}

void RuntimeBusApplication::OnRuntimeIoNotice(const BreakRuntimeIoNotice&) {}

}  // namespace bk
