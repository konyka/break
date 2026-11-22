#ifndef BREAK_FRAMEWORK_COMMON_RUNTIME_BUS_APPLICATION_H_
#define BREAK_FRAMEWORK_COMMON_RUNTIME_BUS_APPLICATION_H_

#include <cstdint>

#include "base_application.h"

extern "C" {
#include <runtime/runtime_io.h>
}

namespace bk {

struct RuntimeBusApplicationStats {
  std::uint64_t io_notices{0};
  std::uint64_t malformed_notices{0};
};

class RuntimeBusApplication : public BaseApplication {
 public:
  RuntimeBusApplication() = default;
  ~RuntimeBusApplication() override;

  RuntimeBusApplication(const RuntimeBusApplication&) = delete;
  RuntimeBusApplication& operator=(const RuntimeBusApplication&) = delete;
  RuntimeBusApplication(RuntimeBusApplication&&) = delete;
  RuntimeBusApplication& operator=(RuntimeBusApplication&&) = delete;

  BreakRuntimeError AttachRuntimeBus(BreakRuntimeBus* bus);
  void DetachRuntimeBus();

  int Init() override;
  void DeInit() override;
  void Tick() override;

  RuntimeBusApplicationStats runtime_bus_stats() const;

 protected:
  virtual void OnRuntimeIoNotice(const BreakRuntimeIoNotice& notice);

 private:
  BreakRuntimeBus* runtime_bus_{nullptr};
  BreakRuntimeQueue* runtime_queue_{nullptr};
  std::uint32_t subscriber_id_{0};
  bool initialized_{false};
  RuntimeBusApplicationStats stats_{};
};

}  // namespace bk

#endif  // BREAK_FRAMEWORK_COMMON_RUNTIME_BUS_APPLICATION_H_
