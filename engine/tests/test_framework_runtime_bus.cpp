#include "runtime_bus_application.h"

#include <array>
#include <atomic>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <set>
#include <thread>
#include <type_traits>
#include <utility>
#include <vector>

static_assert(__cplusplus >= 202002L, "the framework bridge test requires C++20");
static_assert(!std::is_copy_constructible_v<bk::RuntimeBusApplication>);
static_assert(!std::is_copy_assignable_v<bk::RuntimeBusApplication>);
static_assert(!std::is_move_constructible_v<bk::RuntimeBusApplication>);
static_assert(!std::is_move_assignable_v<bk::RuntimeBusApplication>);

namespace {

#define CHECK(condition)                                                        \
  do {                                                                          \
    if (!(condition)) {                                                          \
      std::fprintf(stderr, "%s:%d: CHECK failed: %s\n", __FILE__, __LINE__,     \
                   #condition);                                                  \
      return false;                                                              \
    }                                                                            \
  } while (false)

class RecordingApplication : public bk::RuntimeBusApplication {
 public:
  void MarkQuitForTest() { is_quit_ = true; }

  std::vector<BreakRuntimeIoNotice> notices;
  std::vector<std::thread::id> callback_threads;

 protected:
  void OnRuntimeIoNotice(const BreakRuntimeIoNotice& notice) override {
    notices.push_back(notice);
    callback_threads.push_back(std::this_thread::get_id());
  }
};

class BusFixture {
 public:
  explicit BusFixture(bool attach_production_io = true) {
    valid_ = break_runtime_bus_create(&bus_) == BREAK_RUNTIME_OK;
    if (valid_ && attach_production_io) {
      valid_ = break_runtime_io_attach_bus(bus_) == BREAK_RUNTIME_OK;
    }
  }

  ~BusFixture() {
    if (bus_) {
      (void)break_runtime_io_attach_bus(nullptr);
      break_runtime_bus_destroy(bus_);
    }
  }

  BusFixture(const BusFixture&) = delete;
  BusFixture& operator=(const BusFixture&) = delete;

  bool valid() const { return valid_; }
  BreakRuntimeBus* bus() const { return bus_; }

  BreakRuntimeError AttachProductionIo() {
    return break_runtime_io_attach_bus(bus_);
  }

 private:
  BreakRuntimeBus* bus_{nullptr};
  bool valid_{false};
};

std::array<u8, BREAK_RUNTIME_IO_NOTICE_SIZE> NoticeBytes(
    const BreakRuntimeIoNotice& notice) {
  std::array<u8, BREAK_RUNTIME_IO_NOTICE_SIZE> bytes{};
  for (u32 i = 0; i < 8u; ++i) {
    bytes[i] = static_cast<u8>(notice.request_id >> (8u * i));
    bytes[16u + i] = static_cast<u8>(notice.byte_size >> (8u * i));
  }
  for (u32 i = 0; i < 4u; ++i) {
    bytes[8u + i] = static_cast<u8>(notice.state >> (8u * i));
    bytes[12u + i] = static_cast<u8>(notice.error >> (8u * i));
  }
  return bytes;
}

BreakRuntimeError PublishPayload(BreakRuntimeBus* bus, const void* data,
                                 usize size, u16 version,
                                 u32* delivered = nullptr) {
  BreakRuntimeMessageView view{};
  view.kind = BREAK_RUNTIME_IO_NOTICE_KIND;
  view.version = version;
  view.data = data;
  view.size = size;
  return break_runtime_bus_publish(bus, &view, delivered);
}

BreakRuntimeError PublishNotice(BreakRuntimeBus* bus,
                                const BreakRuntimeIoNotice& notice,
                                u16 version = BREAK_RUNTIME_IO_NOTICE_VERSION,
                                u32* delivered = nullptr) {
  const auto bytes = NoticeBytes(notice);
  return PublishPayload(bus, bytes.data(), bytes.size(), version, delivered);
}

bool NoticeEquals(const BreakRuntimeIoNotice& actual, std::uint64_t request_id,
                  std::uint32_t state, std::uint32_t error,
                  std::uint64_t byte_size) {
  return actual.request_id == request_id && actual.state == state &&
         actual.error == error && actual.byte_size == byte_size;
}

bool default_lifecycle_is_unchanged() {
  RecordingApplication app;
  const auto initial_stats = app.runtime_bus_stats();
  CHECK(initial_stats.io_notices == 0u);
  CHECK(initial_stats.malformed_notices == 0u);
  CHECK(!app.IsQuit());
  app.MarkQuitForTest();
  CHECK(app.IsQuit());
  CHECK(app.Init() == 0);
  CHECK(!app.IsQuit());
  CHECK(app.notices.empty());
  app.Tick();
  app.DeInit();
  app.DeInit();
  CHECK(app.notices.empty());
  CHECK(app.runtime_bus_stats().io_notices == 0u);
  CHECK(app.runtime_bus_stats().malformed_notices == 0u);
  return true;
}

bool attachment_and_initialization_reject_invalid_transitions() {
  BusFixture fixture;
  CHECK(fixture.valid());
  RecordingApplication app;
  CHECK(app.AttachRuntimeBus(nullptr) == BREAK_RUNTIME_INVALID);
  CHECK(app.AttachRuntimeBus(fixture.bus()) == BREAK_RUNTIME_OK);
  CHECK(app.AttachRuntimeBus(fixture.bus()) == BREAK_RUNTIME_REJECTED);
  app.DetachRuntimeBus();
  app.DetachRuntimeBus();
  CHECK(app.AttachRuntimeBus(fixture.bus()) == BREAK_RUNTIME_OK);
  CHECK(app.Init() == 0);
  CHECK(app.Init() == BREAK_RUNTIME_REJECTED);
  CHECK(app.AttachRuntimeBus(fixture.bus()) == BREAK_RUNTIME_REJECTED);
  app.DetachRuntimeBus();
  CHECK(app.AttachRuntimeBus(fixture.bus()) == BREAK_RUNTIME_REJECTED);
  app.DeInit();
  CHECK(app.AttachRuntimeBus(fixture.bus()) == BREAK_RUNTIME_OK);
  app.DeInit();
  return true;
}

class SubscriptionTable {
 public:
  ~SubscriptionTable() {
    for (usize i = 0; i < queues_.size(); ++i) {
      if (bus_ && ids_[i] != 0u) {
        (void)break_runtime_bus_unsubscribe(bus_, ids_[i]);
      }
      break_runtime_queue_destroy(queues_[i]);
    }
  }

  bool Fill(BreakRuntimeBus* bus) {
    bus_ = bus;
    const u16 kind = BREAK_RUNTIME_IO_NOTICE_KIND;
    for (usize i = 0; i < queues_.size(); ++i) {
      const BreakRuntimeQueueConfig config{4u, 0u};
      if (break_runtime_queue_create(&config, &queues_[i]) != BREAK_RUNTIME_OK) {
        return false;
      }
      if (break_runtime_bus_subscribe(bus_, "framework.test.filler", queues_[i],
                                      &kind, 1u, &ids_[i]) != BREAK_RUNTIME_OK) {
        return false;
      }
    }
    return true;
  }

  bool RemoveOne() {
    if (ids_[0] == 0u ||
        break_runtime_bus_unsubscribe(bus_, ids_[0]) != BREAK_RUNTIME_OK) {
      return false;
    }
    ids_[0] = 0u;
    break_runtime_queue_destroy(queues_[0]);
    queues_[0] = nullptr;
    return true;
  }

 private:
  BreakRuntimeBus* bus_{nullptr};
  std::array<BreakRuntimeQueue*, BREAK_RUNTIME_BUS_MAX_SUBSCRIBERS> queues_{};
  std::array<u32, BREAK_RUNTIME_BUS_MAX_SUBSCRIBERS> ids_{};
};

bool missing_kind_and_full_subscriber_table_allow_retry() {
  {
    BusFixture fixture(false);
    CHECK(fixture.valid());
    RecordingApplication app;
    CHECK(app.AttachRuntimeBus(fixture.bus()) == BREAK_RUNTIME_OK);
    CHECK(app.Init() == BREAK_RUNTIME_REJECTED);
    CHECK(fixture.AttachProductionIo() == BREAK_RUNTIME_OK);
    const BreakRuntimeIoNotice notice{77u, BREAK_RUNTIME_IO_COMPLETED,
                                      BREAK_RUNTIME_OK, 12u};
    u32 delivered = 99u;
    CHECK(PublishNotice(fixture.bus(), notice, BREAK_RUNTIME_IO_NOTICE_VERSION,
                        &delivered) == BREAK_RUNTIME_OK);
    CHECK(delivered == 0u);
    CHECK(app.Init() == 0);
    app.DeInit();
  }

  BusFixture fixture;
  CHECK(fixture.valid());
  SubscriptionTable table;
  CHECK(table.Fill(fixture.bus()));
  RecordingApplication app;
  CHECK(app.AttachRuntimeBus(fixture.bus()) == BREAK_RUNTIME_OK);
  CHECK(app.Init() == BREAK_RUNTIME_OVERLOAD);
  CHECK(table.RemoveOne());
  CHECK(app.Init() == 0);
  app.DeInit();
  return true;
}

bool valid_notices_dispatch_in_order_on_the_tick_thread() {
  BusFixture fixture;
  CHECK(fixture.valid());
  RecordingApplication app;
  CHECK(app.AttachRuntimeBus(fixture.bus()) == BREAK_RUNTIME_OK);
  CHECK(app.Init() == 0);

  const BreakRuntimeIoNotice completed{0x0102030405060708ULL,
                                       BREAK_RUNTIME_IO_COMPLETED,
                                       BREAK_RUNTIME_OK,
                                       0x1122334455667788ULL};
  const BreakRuntimeIoNotice failed{99u, BREAK_RUNTIME_IO_FAILED,
                                    BREAK_RUNTIME_UNAVAILABLE, 0u};
  const BreakRuntimeIoNotice cancelled{100u, BREAK_RUNTIME_IO_CANCELLED,
                                       BREAK_RUNTIME_OK, 1234u};
  CHECK(PublishNotice(fixture.bus(), completed) == BREAK_RUNTIME_OK);
  CHECK(PublishNotice(fixture.bus(), failed) == BREAK_RUNTIME_OK);
  CHECK(PublishNotice(fixture.bus(), cancelled) == BREAK_RUNTIME_OK);
  CHECK(app.notices.empty());

  app.Tick();
  CHECK(app.notices.size() == 3u);
  CHECK(app.callback_threads.size() == 3u);
  CHECK(NoticeEquals(app.notices[0], 0x0102030405060708ULL,
                     BREAK_RUNTIME_IO_COMPLETED, BREAK_RUNTIME_OK,
                     0x1122334455667788ULL));
  CHECK(NoticeEquals(app.notices[1], 99u, BREAK_RUNTIME_IO_FAILED,
                     BREAK_RUNTIME_UNAVAILABLE, 0u));
  CHECK(NoticeEquals(app.notices[2], 100u, BREAK_RUNTIME_IO_CANCELLED,
                     BREAK_RUNTIME_OK, 1234u));
  for (const auto& callback_thread : app.callback_threads) {
    CHECK(callback_thread == std::this_thread::get_id());
  }
  CHECK(app.runtime_bus_stats().io_notices == 3u);
  CHECK(app.runtime_bus_stats().malformed_notices == 0u);
  app.Tick();
  CHECK(app.notices.size() == 3u);
  app.DeInit();
  return true;
}

bool malformed_notices_are_counted_and_released() {
  BusFixture fixture(false);
  CHECK(fixture.valid());
  const BreakRuntimeBusKind wrong_version_kind{
      BREAK_RUNTIME_IO_NOTICE_KIND, 2u, BREAK_RUNTIME_IO_NOTICE_SIZE,
      "runtime.io.notice.test", true, 0u};
  CHECK(break_runtime_bus_register_kind(fixture.bus(), &wrong_version_kind) ==
        BREAK_RUNTIME_OK);
  RecordingApplication app;
  CHECK(app.AttachRuntimeBus(fixture.bus()) == BREAK_RUNTIME_OK);
  CHECK(app.Init() == 0);

  const BreakRuntimeIoNotice notice{1u, BREAK_RUNTIME_IO_COMPLETED,
                                    BREAK_RUNTIME_OK, 8u};
  const auto bytes = NoticeBytes(notice);
  CHECK(PublishNotice(fixture.bus(), notice, 2u) == BREAK_RUNTIME_OK);
  CHECK(PublishPayload(fixture.bus(), bytes.data(), bytes.size() - 1u, 1u) ==
        BREAK_RUNTIME_OK);
  CHECK(PublishPayload(fixture.bus(), nullptr, 0u, 1u) == BREAK_RUNTIME_OK);

  BreakRuntimeMessageView wrong_kind_view{};
  wrong_kind_view.kind = BREAK_RUNTIME_IO_COMPLETION_KIND;
  wrong_kind_view.version = BREAK_RUNTIME_IO_NOTICE_VERSION;
  wrong_kind_view.data = bytes.data();
  wrong_kind_view.size = bytes.size();
  BreakRuntimeOwnedMessage* wrong_kind_message = nullptr;
  CHECK(break_runtime_message_copy(&wrong_kind_view, &wrong_kind_message) ==
        BREAK_RUNTIME_OK);
  BreakRuntimeIoNotice parsed{};
  const BreakRuntimeError wrong_kind_result =
      break_runtime_io_notice_view(wrong_kind_message, &parsed);
  break_runtime_message_release(wrong_kind_message);
  CHECK(wrong_kind_result == BREAK_RUNTIME_INVALID);
  CHECK(break_runtime_io_notice_view(nullptr, &parsed) == BREAK_RUNTIME_INVALID);

  app.Tick();
  CHECK(app.notices.empty());
  CHECK(app.runtime_bus_stats().io_notices == 0u);
  CHECK(app.runtime_bus_stats().malformed_notices == 3u);
  app.Tick();
  CHECK(app.runtime_bus_stats().malformed_notices == 3u);
  app.DeInit();
  return true;
}

bool detach_deinit_and_destructor_unsubscribe() {
  BusFixture fixture;
  CHECK(fixture.valid());
  const BreakRuntimeIoNotice notice{10u, BREAK_RUNTIME_IO_COMPLETED,
                                    BREAK_RUNTIME_OK, 20u};
  RecordingApplication app;
  CHECK(app.AttachRuntimeBus(fixture.bus()) == BREAK_RUNTIME_OK);
  CHECK(app.Init() == 0);
  CHECK(PublishNotice(fixture.bus(), notice) == BREAK_RUNTIME_OK);
  app.Tick();
  CHECK(app.runtime_bus_stats().io_notices == 1u);

  app.DetachRuntimeBus();
  app.DetachRuntimeBus();
  u32 delivered = 99u;
  CHECK(PublishNotice(fixture.bus(), notice, BREAK_RUNTIME_IO_NOTICE_VERSION,
                      &delivered) == BREAK_RUNTIME_OK);
  CHECK(delivered == 0u);
  app.Tick();
  CHECK(app.runtime_bus_stats().io_notices == 1u);
  app.DeInit();
  app.DeInit();
  CHECK(PublishNotice(fixture.bus(), notice, BREAK_RUNTIME_IO_NOTICE_VERSION,
                      &delivered) == BREAK_RUNTIME_OK);
  CHECK(delivered == 0u);

  CHECK(app.AttachRuntimeBus(fixture.bus()) == BREAK_RUNTIME_OK);
  CHECK(app.Init() == 0);
  CHECK(app.runtime_bus_stats().io_notices == 0u);
  CHECK(PublishNotice(fixture.bus(), notice) == BREAK_RUNTIME_OK);
  app.Tick();
  CHECK(app.runtime_bus_stats().io_notices == 1u);
  app.DeInit();

  {
    RecordingApplication scoped_app;
    CHECK(scoped_app.AttachRuntimeBus(fixture.bus()) == BREAK_RUNTIME_OK);
    CHECK(scoped_app.Init() == 0);
    CHECK(PublishNotice(fixture.bus(), notice) == BREAK_RUNTIME_OK);
  }
  CHECK(PublishNotice(fixture.bus(), notice, BREAK_RUNTIME_IO_NOTICE_VERSION,
                      &delivered) == BREAK_RUNTIME_OK);
  CHECK(delivered == 0u);
  return true;
}

bool a_full_queue_reports_drops_without_blocking() {
  BusFixture fixture;
  CHECK(fixture.valid());
  RecordingApplication app;
  CHECK(app.AttachRuntimeBus(fixture.bus()) == BREAK_RUNTIME_OK);
  CHECK(app.Init() == 0);

  BreakRuntimeIoNotice notice{0u, BREAK_RUNTIME_IO_COMPLETED,
                              BREAK_RUNTIME_OK, 0u};
  for (u32 i = 0; i < 64u; ++i) {
    notice.request_id = i + 1u;
    CHECK(PublishNotice(fixture.bus(), notice) == BREAK_RUNTIME_OK);
  }
  notice.request_id = 65u;
  u32 delivered = 99u;
  CHECK(PublishNotice(fixture.bus(), notice, BREAK_RUNTIME_IO_NOTICE_VERSION,
                      &delivered) == BREAK_RUNTIME_OVERLOAD);
  CHECK(delivered == 0u);

  BreakRuntimeBusKindStats kind_stats{};
  CHECK(break_runtime_bus_kind_stats(fixture.bus(), BREAK_RUNTIME_IO_NOTICE_KIND,
                                     &kind_stats) == BREAK_RUNTIME_OK);
  CHECK(kind_stats.published == 65u);
  CHECK(kind_stats.delivered == 64u);
  CHECK(kind_stats.dropped == 1u);
  app.Tick();
  CHECK(app.runtime_bus_stats().io_notices == 64u);
  CHECK(app.notices.size() == 64u);

  notice.request_id = 1000u;
  CHECK(PublishNotice(fixture.bus(), notice) == BREAK_RUNTIME_OK);
  app.Tick();
  CHECK(app.runtime_bus_stats().io_notices == 65u);
  CHECK(app.notices.back().request_id == 1000u);
  CHECK(app.runtime_bus_stats().malformed_notices == 0u);
  app.DeInit();
  return true;
}

bool production_io_attachment_and_parser_link_from_cpp20() {
  BusFixture fixture;
  CHECK(fixture.valid());
  const BreakRuntimeIoNotice expected{0xF1E2D3C4B5A69788ULL,
                                      BREAK_RUNTIME_IO_FAILED,
                                      BREAK_RUNTIME_FAILED, 4096u};
  const auto bytes = NoticeBytes(expected);
  BreakRuntimeMessageView view{};
  view.kind = BREAK_RUNTIME_IO_NOTICE_KIND;
  view.version = BREAK_RUNTIME_IO_NOTICE_VERSION;
  view.data = bytes.data();
  view.size = bytes.size();
  BreakRuntimeOwnedMessage* message = nullptr;
  CHECK(break_runtime_message_copy(&view, &message) == BREAK_RUNTIME_OK);
  BreakRuntimeIoNotice parsed{};
  const BreakRuntimeError parse_result =
      break_runtime_io_notice_view(message, &parsed);
  break_runtime_message_release(message);
  CHECK(parse_result == BREAK_RUNTIME_OK);
  CHECK(NoticeEquals(parsed, 0xF1E2D3C4B5A69788ULL, BREAK_RUNTIME_IO_FAILED,
                     BREAK_RUNTIME_FAILED, 4096u));

  RecordingApplication app;
  CHECK(app.AttachRuntimeBus(fixture.bus()) == BREAK_RUNTIME_OK);
  CHECK(app.Init() == 0);
  CHECK(PublishNotice(fixture.bus(), expected) == BREAK_RUNTIME_OK);
  app.Tick();
  CHECK(app.notices.size() == 1u);
  CHECK(NoticeEquals(app.notices[0], 0xF1E2D3C4B5A69788ULL,
                     BREAK_RUNTIME_IO_FAILED, BREAK_RUNTIME_FAILED, 4096u));
  app.DeInit();
  CHECK(break_runtime_io_attach_bus(nullptr) == BREAK_RUNTIME_OK);
  return true;
}

struct PublisherResult {
  std::uint64_t accepted{0};
  std::uint64_t overload{0};
  std::uint64_t unexpected{0};
};

bool concurrent_publish_and_tick_are_race_free() {
  constexpr std::uint64_t kPublisherCount = 2u;
  constexpr std::uint64_t kNoticesPerPublisher = 512u;
  constexpr std::uint64_t kTotalNotices =
      kPublisherCount * kNoticesPerPublisher;

  BusFixture fixture;
  CHECK(fixture.valid());
  RecordingApplication app;
  CHECK(app.AttachRuntimeBus(fixture.bus()) == BREAK_RUNTIME_OK);
  CHECK(app.Init() == 0);

  std::atomic<std::uint32_t> ready{0u};
  std::atomic<bool> start{false};
  std::atomic<bool> publishing_done{false};
  auto announce_ready_and_wait = [&ready, &start]() {
    ready.fetch_add(1u, std::memory_order_release);
    while (!start.load(std::memory_order_acquire)) {
      std::this_thread::yield();
    }
  };

  std::thread tick_thread([&]() {
    announce_ready_and_wait();
    while (!publishing_done.load(std::memory_order_acquire)) {
      app.Tick();
    }
    app.Tick();
  });
  const std::thread::id tick_thread_id = tick_thread.get_id();

  std::array<PublisherResult, kPublisherCount> results;
  std::array<std::thread, kPublisherCount> publishers;
  for (std::uint64_t publisher = 0; publisher < kPublisherCount; ++publisher) {
    publishers[publisher] = std::thread([&, publisher]() {
      announce_ready_and_wait();
      auto& result = results[publisher];
      for (std::uint64_t i = 0; i < kNoticesPerPublisher; ++i) {
        const BreakRuntimeIoNotice notice{
            ((publisher + 1u) << 32u) | (i + 1u),
            BREAK_RUNTIME_IO_COMPLETED, BREAK_RUNTIME_OK, i};
        const BreakRuntimeError error = PublishNotice(fixture.bus(), notice);
        if (error == BREAK_RUNTIME_OK) {
          ++result.accepted;
        } else if (error == BREAK_RUNTIME_OVERLOAD) {
          ++result.overload;
        } else {
          ++result.unexpected;
        }
      }
    });
  }

  while (ready.load(std::memory_order_acquire) != kPublisherCount + 1u) {
    std::this_thread::yield();
  }
  start.store(true, std::memory_order_release);
  for (auto& publisher : publishers) {
    publisher.join();
  }
  publishing_done.store(true, std::memory_order_release);
  tick_thread.join();

  for (const auto& result : results) {
    CHECK(result.unexpected == 0u);
    CHECK(result.accepted + result.overload == kNoticesPerPublisher);
  }
  BreakRuntimeBusKindStats kind_stats{};
  CHECK(break_runtime_bus_kind_stats(fixture.bus(), BREAK_RUNTIME_IO_NOTICE_KIND,
                                     &kind_stats) == BREAK_RUNTIME_OK);
  CHECK(kind_stats.delivered > 0u);
  CHECK(kind_stats.published == kTotalNotices);
  CHECK(kind_stats.delivered + kind_stats.dropped == kTotalNotices);
  const auto app_stats = app.runtime_bus_stats();
  CHECK(app_stats.malformed_notices == 0u);
  CHECK(!app.notices.empty());
  CHECK(app_stats.io_notices == kind_stats.delivered);
  CHECK(app.notices.size() == app_stats.io_notices);
  CHECK(app.callback_threads.size() == app.notices.size());

  std::set<std::uint64_t> request_ids;
  for (usize i = 0; i < app.notices.size(); ++i) {
    const auto& notice = app.notices[i];
    CHECK(notice.state == BREAK_RUNTIME_IO_COMPLETED);
    CHECK(notice.error == BREAK_RUNTIME_OK);
    const std::uint64_t publisher = notice.request_id >> 32u;
    const std::uint64_t sequence = notice.request_id & 0xFFFFFFFFu;
    CHECK(publisher >= 1u && publisher <= kPublisherCount);
    CHECK(sequence >= 1u && sequence <= kNoticesPerPublisher);
    CHECK(request_ids.insert(notice.request_id).second);
    CHECK(app.callback_threads[i] == tick_thread_id);
  }
  CHECK(request_ids.size() == app.notices.size());
  app.DeInit();
  return true;
}

struct TestCase {
  const char* name;
  bool (*run)();
};

}  // namespace

int main() {
  const std::array<TestCase, 9> tests{{
      {"default_lifecycle_is_unchanged", default_lifecycle_is_unchanged},
      {"attachment_and_initialization_reject_invalid_transitions",
       attachment_and_initialization_reject_invalid_transitions},
      {"missing_kind_and_full_subscriber_table_allow_retry",
       missing_kind_and_full_subscriber_table_allow_retry},
      {"valid_notices_dispatch_in_order_on_the_tick_thread",
       valid_notices_dispatch_in_order_on_the_tick_thread},
      {"malformed_notices_are_counted_and_released",
       malformed_notices_are_counted_and_released},
      {"detach_deinit_and_destructor_unsubscribe",
       detach_deinit_and_destructor_unsubscribe},
      {"a_full_queue_reports_drops_without_blocking",
       a_full_queue_reports_drops_without_blocking},
      {"production_io_attachment_and_parser_link_from_cpp20",
       production_io_attachment_and_parser_link_from_cpp20},
      {"concurrent_publish_and_tick_are_race_free",
       concurrent_publish_and_tick_are_race_free},
  }};

  std::uint32_t failures = 0u;
  for (const auto& test : tests) {
    std::fprintf(stderr, "[ RUN      ] %s\n", test.name);
    if (test.run()) {
      std::fprintf(stderr, "[       OK ] %s\n", test.name);
    } else {
      ++failures;
      std::fprintf(stderr, "[  FAILED  ] %s\n", test.name);
    }
  }
  std::fprintf(stderr, "%zu tests, %u failures\n", tests.size(), failures);
  return failures == 0u ? 0 : 1;
}
