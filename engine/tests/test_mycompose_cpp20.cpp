#include "test_framework.h"
#include "compose_parity_fixture.h"

#include <myui/mycompose/my_compose.hpp>

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <optional>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace compose = breakxx::compose;

namespace {

MyComposeValue IntValue(int32_t value) {
    MyComposeValue result{};
    result.type = MY_COMPOSE_VALUE_INT32;
    result.as.int32_value = value;
    return result;
}

MyComposeValue ColorValue(uint32_t value) {
    MyComposeValue result{};
    result.type = MY_COMPOSE_VALUE_COLOR;
    result.as.color = value;
    return result;
}

compose::Intent PayloadIntent(uint32_t type, const uint32_t &payload) {
    compose::Intent intent{};
    intent.type = type;
    intent.payload_size = sizeof(payload);
    intent.payload = reinterpret_cast<const uint8_t *>(&payload);
    return intent;
}

MyComposeStatus BuildCppView(compose::Builder &builder, uint32_t state,
    bool second, MyComposeNodeHandle *out_a) {
    auto root = builder.Node("@root");
    auto row = root.Row("row");
    auto column = row.Column("column");
    auto stack = column.Stack("stack");
    MyComposeNodeHandle a{};
    if (second) {
        auto b = stack.Key("b").Element("label");
        auto item = stack.Key("a").Element("edit");
        a = item.Handle();
        (void)item.Property("count", IntValue(static_cast<int32_t>(state)))
            .Style("bg_color", ColorValue(0x11223344u))
            .OnClick(PayloadIntent(COMPOSE_PARITY_EVENT_TYPE, state));
    } else {
        auto item = stack.Key("a").Element("button");
        a = item.Handle();
        (void)item.Property("count", IntValue(static_cast<int32_t>(state)))
            .Style("bg_color", ColorValue(0x11223344u))
            .OnClick(PayloadIntent(COMPOSE_PARITY_EVENT_TYPE, state));
        auto b = stack.Key("b").Element("label");
        (void)b;
    }
    *out_a = a;
    return builder.Status();
}

MyComposeStatus RunCppParity(ComposeParityResult &result) {
    std::memset(&result, 0, sizeof(result));
    auto builder = compose::Builder::Create();
    if (!builder.has_value()) return MY_COMPOSE_OVERLOAD;
    auto store = compose::Store<uint32_t>::Create(0u,
        [](const uint32_t &current, uint32_t &candidate,
            const compose::Intent &intent, compose::EffectBatch &batch) {
            if (intent.type != COMPOSE_PARITY_INTENT_TYPE ||
                intent.payload_size != sizeof(uint32_t) ||
                intent.payload == nullptr) {
                return MY_COMPOSE_INVALID;
            }
            uint32_t amount = 0u;
            std::memcpy(&amount, intent.payload, sizeof(amount));
            candidate = current + amount;
            return batch.Append(COMPOSE_PARITY_EFFECT_TYPE, amount);
        },
        [&result](const MyComposeEffect &effect) {
            result.effect_calls++;
            result.effect_type = effect.type;
            result.effect_payload_size = effect.payload_size;
            if (effect.payload_size != sizeof(result.effect_payload) ||
                effect.payload == nullptr) {
                return MY_COMPOSE_INVALID;
            }
            std::memcpy(result.effect_payload, effect.payload,
                sizeof(result.effect_payload));
            return MY_COMPOSE_OK;
        });
    if (!store.has_value()) return MY_COMPOSE_OVERLOAD;
    MyComposeNodeHandle a{};
    result.status = builder->Begin();
    if (result.status == MY_COMPOSE_OK) {
        result.status = BuildCppView(*builder, 0u, false, &a);
    }
    if (result.status == MY_COMPOSE_OK) result.status = builder->End();
    if (result.status == MY_COMPOSE_OK) result.status = builder->Finalize();
    if (result.status == MY_COMPOSE_OK) {
        ComposeParityCanonicalDiff(&result, builder->Diff());
        result.status = store->Dispatch(
            PayloadIntent(COMPOSE_PARITY_INTENT_TYPE, COMPOSE_PARITY_AMOUNT));
    }
    if (result.status == MY_COMPOSE_OK) result.status = store->Reduce();
    if (result.status == MY_COMPOSE_OK) result.status = store->DispatchEffects();
    const uint32_t *state = store->CurrentState();
    if (result.status == MY_COMPOSE_OK && state != nullptr) {
        result.state_count = *state;
        result.status = builder->Begin();
    } else if (result.status == MY_COMPOSE_OK) {
        result.status = MY_COMPOSE_FAILED;
    }
    if (result.status == MY_COMPOSE_OK) {
        result.status = BuildCppView(*builder, *state, true, &a);
    }
    if (result.status == MY_COMPOSE_OK) result.status = builder->End();
    if (result.status == MY_COMPOSE_OK) result.status = builder->Finalize();
    if (result.status == MY_COMPOSE_OK) {
        ComposeParityCanonicalDiff(&result, builder->Diff());
        MyComposeValue value{};
        result.status = builder->GetProperty(a, "count", value);
        result.property_value = value.as.int32_value;
    }
    if (result.status == MY_COMPOSE_OK) {
        MyComposeValue value{};
        result.status = builder->GetProperty(a, "style:bg_color", value);
        result.style_value = value.as.color;
    }
    if (result.status == MY_COMPOSE_OK) {
        compose::Intent event{};
        result.status = builder->GetEvent(a, "click", event);
        result.event_type = event.type;
        result.event_payload_size = event.payload_size;
        if (event.payload_size != sizeof(result.event_payload) ||
            event.payload == nullptr) {
            result.status = MY_COMPOSE_INVALID;
        } else {
            std::memcpy(result.event_payload, event.payload,
                sizeof(result.event_payload));
        }
    }
    return result.status;
}

struct Counter {
    explicit Counter(int value) : count(value) {}
    Counter() = delete;
    Counter(const Counter &) = default;
    Counter(Counter &&) noexcept = default;
    Counter &operator=(const Counter &) = delete;
    Counter &operator=(Counter &&) = delete;
    int count;
};

struct Selection {
    Selection(int first, int last) : start(first), end(last) {}
    Selection() = delete;
    int start;
    int end;
};

struct TrackedState {
    static inline int live = 0;
    static inline int copy_constructions = 0;
    static inline int destructions = 0;
    static inline int dispose_calls = 0;
    static inline bool throw_copy = false;

    explicit TrackedState(int value) : value(value) { live++; }
    TrackedState(const TrackedState &other) : value(other.value) {
        if (throw_copy) throw std::runtime_error("copy");
        copy_constructions++;
        live++;
    }
    TrackedState(TrackedState &&other) noexcept : value(other.value) { live++; }
    TrackedState &operator=(const TrackedState &) = delete;
    TrackedState &operator=(TrackedState &&) = delete;
    ~TrackedState() {
        destructions++;
        live--;
    }
    int value;
};

struct MoveOnlyState {
    static inline int live = 0;
    static inline int clone_calls = 0;
    static inline int dispose_calls = 0;

    explicit MoveOnlyState(int value) : value(value) { live++; }
    MoveOnlyState(const MoveOnlyState &) = delete;
    MoveOnlyState(MoveOnlyState &&other) noexcept : value(other.value) { live++; }
    MoveOnlyState &operator=(const MoveOnlyState &) = delete;
    MoveOnlyState &operator=(MoveOnlyState &&) = delete;
    ~MoveOnlyState() { live--; }
    int value;
};

struct Remembered {
    static inline int live = 0;
    static inline int destructions = 0;

    explicit Remembered(int value) : value(value) { live++; }
    Remembered(const Remembered &) = delete;
    Remembered(Remembered &&other) noexcept : value(other.value) { live++; }
    Remembered &operator=(const Remembered &) = delete;
    Remembered &operator=(Remembered &&) = delete;
    ~Remembered() {
        destructions++;
        live--;
    }
    int value;
};

struct RuntimeLog {
    uint32_t stage_calls = 0;
    uint32_t commit_calls = 0;
    uint32_t rollback_calls = 0;
    uint32_t last_diff_count = 0;
};

MyComposeStatus RuntimeStage(void *opaque, const MyComposeDiff *diff) {
    auto *log = static_cast<RuntimeLog *>(opaque);
    log->stage_calls++;
    log->last_diff_count = diff->count;
    return MY_COMPOSE_OK;
}

void RuntimeCommit(void *opaque) {
    static_cast<RuntimeLog *>(opaque)->commit_calls++;
}

void RuntimeRollback(void *opaque) {
    static_cast<RuntimeLog *>(opaque)->rollback_calls++;
}

} // namespace

namespace breakxx::compose {

template <>
struct StateOps<TrackedState> {
    static MyComposeStatus Clone(const TrackedState &source,
        std::optional<TrackedState> &destination) {
        destination.emplace(source);
        return MY_COMPOSE_OK;
    }

    static void Dispose(TrackedState &) noexcept {
        TrackedState::dispose_calls++;
    }
};

template <>
struct StateOps<MoveOnlyState> {
    static MyComposeStatus Clone(const MoveOnlyState &source,
        std::optional<MoveOnlyState> &destination) {
        MoveOnlyState::clone_calls++;
        destination.emplace(source.value);
        return MY_COMPOSE_OK;
    }

    static void Dispose(MoveOnlyState &) noexcept {
        MoveOnlyState::dispose_calls++;
    }
};

} // namespace breakxx::compose

TEST(c_and_cpp_parity_uses_canonical_bytes_and_real_cross_language_link) {
    ComposeParityResult c_result;
    ComposeParityResult cpp_result;
    uint32_t payload = 0u;
    ASSERT_EQ(ComposeParityRunC(&c_result), MY_COMPOSE_OK);
    ASSERT_EQ(RunCppParity(cpp_result), MY_COMPOSE_OK);
    ASSERT_EQ(cpp_result.diff_frames, 2u);
    ASSERT_EQ(cpp_result.diff_counts[0], 6u);
    ASSERT_EQ(cpp_result.diff_counts[1], 2u);
    ASSERT_EQ(cpp_result.state_count, COMPOSE_PARITY_AMOUNT);
    ASSERT_EQ(cpp_result.effect_calls, 1u);
    ASSERT_EQ(cpp_result.effect_type, COMPOSE_PARITY_EFFECT_TYPE);
    std::memcpy(&payload, cpp_result.effect_payload, sizeof(payload));
    ASSERT_EQ(payload, COMPOSE_PARITY_AMOUNT);
    ASSERT_EQ(cpp_result.property_value, (int32_t)COMPOSE_PARITY_AMOUNT);
    ASSERT_EQ(cpp_result.style_value, 0x11223344u);
    ASSERT_EQ(cpp_result.event_type, COMPOSE_PARITY_EVENT_TYPE);
    std::memcpy(&payload, cpp_result.event_payload, sizeof(payload));
    ASSERT_EQ(payload, COMPOSE_PARITY_AMOUNT);
    ASSERT_NOT_NULL(strstr(cpp_result.diff, "1:3,"));
    ASSERT_NOT_NULL(strstr(cpp_result.diff, "1:0,"));
    ASSERT_EQ(cpp_result.diff_size, c_result.diff_size);
    ASSERT_EQ(std::memcmp(cpp_result.diff, c_result.diff, c_result.diff_size), 0);
    ASSERT_EQ(std::memcmp(&cpp_result, &c_result, sizeof(c_result)), 0);
}

TEST(node_scope_covers_dsl_moves_and_closes_only_live_scopes) {
    auto builder = compose::Builder::Create();
    ASSERT_TRUE(builder.has_value());
    ASSERT_EQ(builder->Begin(), MY_COMPOSE_OK);
    MyComposeNodeHandle element_handle{};
    {
        auto root = builder->Node("@root");
        auto row = root.Row("row");
        auto column = row.Column("column");
        auto stack = column.Stack("stack");
        auto element = stack.Key("item").Element("button");
        element_handle = element.Handle();
        (void)element.Property("count", IntValue(3))
            .Style("bg_color", ColorValue(0x01020304u))
            .OnEvent("changed", PayloadIntent(55u, element_handle.index));
        auto moved = std::move(element);
        ASSERT_FALSE(element.Valid());
        ASSERT_TRUE(moved.Valid());
        moved.Close();
        moved.Close();
        ASSERT_EQ(builder->Status(), MY_COMPOSE_OK);
    }
    ASSERT_EQ(builder->End(), MY_COMPOSE_OK);
    ASSERT_EQ(builder->Finalize(), MY_COMPOSE_OK);
    ASSERT_EQ(builder->CurrentNodeCount(), 5u);
    MyComposeValue value{};
    ASSERT_EQ(builder->GetProperty(element_handle, "count", value), MY_COMPOSE_OK);
    ASSERT_EQ(value.as.int32_value, 3);
    ASSERT_EQ(builder->GetProperty(element_handle, "style:bg_color", value),
        MY_COMPOSE_OK);
    ASSERT_EQ(value.as.color, 0x01020304u);
    compose::Intent event{};
    ASSERT_EQ(builder->GetEvent(element_handle, "changed", event), MY_COMPOSE_OK);
    ASSERT_EQ(event.type, 55u);
    ASSERT_EQ(event.owner.index, element_handle.index);
}

TEST(remember_constructs_once_reuses_and_rejects_local_type_change) {
    Remembered::live = 0;
    Remembered::destructions = 0;
    uint32_t factory_calls = 0;
    {
        auto builder = compose::Builder::Create();
        ASSERT_TRUE(builder.has_value());
        ASSERT_EQ(builder->Begin(), MY_COMPOSE_OK);
        auto root = builder->Node("@root");
        auto *slot = builder->Remember<Remembered>(0u, [&factory_calls] {
            factory_calls++;
            return Remembered(42);
        });
        ASSERT_NOT_NULL(slot);
        ASSERT_EQ(slot->value, 42);
        ASSERT_EQ(factory_calls, 1u);
        auto *same = builder->Remember<Remembered>(0u, [&factory_calls] {
            factory_calls++;
            return Remembered(99);
        });
        ASSERT_EQ(same, slot);
        ASSERT_EQ(factory_calls, 1u);
        auto *wrong = builder->Remember<Selection>(0u,
            [] { return Selection(1, 2); });
        ASSERT_EQ(wrong, nullptr);
        ASSERT_EQ(builder->Status(), MY_COMPOSE_TYPE_MISMATCH);
        ASSERT_EQ(slot->value, 42);
        ASSERT_EQ(Remembered::live, 1);
        root.Close();
    }
    ASSERT_EQ(Remembered::destructions, 1);
    ASSERT_EQ(Remembered::live, 0);
}

TEST(remember_constructor_exception_is_sticky_without_false_destruction) {
    Remembered::live = 0;
    Remembered::destructions = 0;
    {
        auto builder = compose::Builder::Create();
        ASSERT_TRUE(builder.has_value());
        ASSERT_EQ(builder->Begin(), MY_COMPOSE_OK);
        auto root = builder->Node("@root");
        auto *slot = builder->Remember<Remembered>(0u, []() -> Remembered {
            throw std::runtime_error("constructor");
        });
        ASSERT_EQ(slot, nullptr);
        ASSERT_EQ(builder->Status(), MY_COMPOSE_FAILED);
        ASSERT_EQ(Remembered::live, 0);
        root.Close();
    }
    ASSERT_EQ(Remembered::destructions, 0);
    ASSERT_EQ(Remembered::live, 0);
}

TEST(remember_without_an_open_scope_is_sticky_and_moved_builder_is_inert) {
    auto builder = compose::Builder::Create();
    ASSERT_TRUE(builder.has_value());
    auto *slot = builder->Remember<Selection>(0u, [] { return Selection(2, 4); });
    ASSERT_EQ(slot, nullptr);
    ASSERT_EQ(builder->Status(), MY_COMPOSE_INVALID);
    auto moved = std::move(*builder);
    ASSERT_EQ(builder->Status(), MY_COMPOSE_INVALID);
    ASSERT_EQ(builder->Begin(), MY_COMPOSE_INVALID);
    ASSERT_EQ(builder->Remember<Selection>(0u, [] { return Selection(2, 4); }),
        nullptr);
    ASSERT_EQ(moved.Status(), MY_COMPOSE_INVALID);
}

TEST(store_supports_non_default_non_copy_assignable_state_and_moves) {
    auto store = compose::Store<Counter>::Create(Counter{0},
        [](const Counter &current, Counter &candidate, const compose::Intent &,
            compose::EffectBatch &) {
            candidate.count = current.count + 1;
            return MY_COMPOSE_OK;
        });
    ASSERT_TRUE(store.has_value());
    auto moved = std::move(*store);
    ASSERT_FALSE(store->Valid());
    ASSERT_EQ(store->Dispatch(compose::Intent{.type = 1u}), MY_COMPOSE_INVALID);
    ASSERT_EQ(store->Reduce(), MY_COMPOSE_INVALID);
    ASSERT_EQ(store->CurrentState(), nullptr);
    ASSERT_EQ(moved.Dispatch(compose::Intent{.type = 1u}), MY_COMPOSE_OK);
    ASSERT_EQ(moved.Reduce(), MY_COMPOSE_OK);
    ASSERT_NOT_NULL(moved.CurrentState());
    ASSERT_EQ(moved.CurrentState()->count, 1);
    auto move_assigned = std::move(moved);
    ASSERT_FALSE(moved.Valid());
    ASSERT_EQ(move_assigned.Dispatch(compose::Intent{.type = 1u}), MY_COMPOSE_OK);
    ASSERT_EQ(move_assigned.Reduce(), MY_COMPOSE_OK);
    ASSERT_EQ(move_assigned.CurrentState()->count, 2);
}

TEST(move_only_state_uses_custom_clone_and_disposes_each_live_slot_once) {
    MoveOnlyState::live = 0;
    MoveOnlyState::clone_calls = 0;
    MoveOnlyState::dispose_calls = 0;
    {
        auto store = compose::Store<MoveOnlyState>::Create(MoveOnlyState{3},
            [](const MoveOnlyState &current, MoveOnlyState &candidate,
                const compose::Intent &, compose::EffectBatch &) {
                candidate.value = current.value + 2;
                return MY_COMPOSE_OK;
            });
        ASSERT_TRUE(store.has_value());
        ASSERT_EQ(store->Dispatch(compose::Intent{.type = 1u}), MY_COMPOSE_OK);
        ASSERT_EQ(store->Reduce(), MY_COMPOSE_OK);
        ASSERT_EQ(store->CurrentState()->value, 5);
        ASSERT_EQ(MoveOnlyState::clone_calls, 2);
        ASSERT_EQ(MoveOnlyState::live, 2);
        ASSERT_EQ(store->Dispatch(compose::Intent{.type = 1u}), MY_COMPOSE_OK);
        ASSERT_EQ(store->Reduce(), MY_COMPOSE_OK);
        ASSERT_EQ(store->CurrentState()->value, 7);
        ASSERT_EQ(MoveOnlyState::clone_calls, 3);
        ASSERT_EQ(MoveOnlyState::dispose_calls, 1);
        ASSERT_EQ(MoveOnlyState::live, 2);
    }
    ASSERT_EQ(MoveOnlyState::live, 0);
    ASSERT_EQ(MoveOnlyState::dispose_calls, 3);
}

TEST(clone_exception_preserves_atom_state_and_fifo) {
    TrackedState::live = 0;
    TrackedState::copy_constructions = 0;
    TrackedState::destructions = 0;
    TrackedState::dispose_calls = 0;
    TrackedState::throw_copy = false;
    {
        auto store = compose::Store<TrackedState>::Create(TrackedState{4},
            [](const TrackedState &, TrackedState &candidate,
                const compose::Intent &, compose::EffectBatch &) {
                candidate.value = 100;
                return MY_COMPOSE_OK;
            });
        ASSERT_TRUE(store.has_value());
        ASSERT_EQ(TrackedState::copy_constructions, 1);
        TrackedState::throw_copy = true;
        ASSERT_EQ(store->Dispatch(compose::Intent{.type = 1u}), MY_COMPOSE_OK);
        ASSERT_EQ(store->Reduce(), MY_COMPOSE_FAILED);
        ASSERT_EQ(store->CurrentState()->value, 4);
        ASSERT_EQ(store->Diagnostics()->pending_intents, 1u);
        ASSERT_EQ(TrackedState::live, 1);
        ASSERT_EQ(TrackedState::dispose_calls, 0);
        TrackedState::throw_copy = false;
    }
    ASSERT_EQ(TrackedState::live, 0);
    ASSERT_EQ(TrackedState::dispose_calls, 1);
    ASSERT_EQ(TrackedState::destructions, 2);
}

TEST(reducer_exception_disposes_candidate_and_never_publishes_it) {
    TrackedState::live = 0;
    TrackedState::copy_constructions = 0;
    TrackedState::destructions = 0;
    TrackedState::dispose_calls = 0;
    TrackedState::throw_copy = false;
    {
        auto store = compose::Store<TrackedState>::Create(TrackedState{4},
            [](const TrackedState &, TrackedState &candidate,
                const compose::Intent &, compose::EffectBatch &)
                -> MyComposeStatus {
                candidate.value = 999;
                throw std::runtime_error("reducer");
            });
        ASSERT_TRUE(store.has_value());
        ASSERT_EQ(store->Dispatch(compose::Intent{.type = 1u}), MY_COMPOSE_OK);
        ASSERT_EQ(store->Reduce(), MY_COMPOSE_FAILED);
        ASSERT_EQ(store->CurrentState()->value, 4);
        ASSERT_EQ(store->Diagnostics()->pending_intents, 1u);
        ASSERT_EQ(TrackedState::live, 1);
        ASSERT_EQ(TrackedState::dispose_calls, 1);
    }
    ASSERT_EQ(TrackedState::live, 0);
    ASSERT_EQ(TrackedState::dispose_calls, 2);
    ASSERT_EQ(TrackedState::destructions, 3);
}

TEST(initial_state_construction_exception_returns_empty_without_leaks) {
    TrackedState::live = 0;
    TrackedState::copy_constructions = 0;
    TrackedState::destructions = 0;
    TrackedState::dispose_calls = 0;
    TrackedState::throw_copy = true;
    auto store = compose::Store<TrackedState>::Create(TrackedState{8},
        [](const TrackedState &, TrackedState &, const compose::Intent &,
            compose::EffectBatch &) {
            return MY_COMPOSE_OK;
        });
    ASSERT_FALSE(store.has_value());
    TrackedState::throw_copy = false;
    ASSERT_EQ(TrackedState::live, 0);
    ASSERT_EQ(TrackedState::destructions, 1);
}

TEST(effect_batch_uses_fixed_capacity_and_sticky_checked_append) {
    uint32_t reducer_calls = 0;
    auto store = compose::Store<uint32_t>::Create(0u,
        [&reducer_calls](const uint32_t &, uint32_t &candidate,
            const compose::Intent &, compose::EffectBatch &batch) {
            reducer_calls++;
            candidate = 123u;
            for (uint32_t i = 0u; i < compose::kMaxEffectsPerIntent; ++i) {
                if (batch.Append(500u + i, i) != MY_COMPOSE_OK) {
                    return MY_COMPOSE_FAILED;
                }
            }
            if (batch.Count() != compose::kMaxEffectsPerIntent ||
                batch.Append(999u, 9u) != MY_COMPOSE_OVERLOAD ||
                batch.Append(1000u, 10u) != MY_COMPOSE_OVERLOAD ||
                batch.Count() != compose::kMaxEffectsPerIntent) {
                return MY_COMPOSE_FAILED;
            }
            return MY_COMPOSE_OK;
        });
    ASSERT_TRUE(store.has_value());
    ASSERT_EQ(store->Dispatch(compose::Intent{.type = 1u}), MY_COMPOSE_OK);
    ASSERT_EQ(store->Reduce(), MY_COMPOSE_OVERLOAD);
    ASSERT_EQ(*store->CurrentState(), 0u);
    ASSERT_EQ(reducer_calls, 1u);
}

TEST(executor_exception_crosses_c_abi_as_a_status) {
    auto store = compose::Store<uint32_t>::Create(0u,
        [](const uint32_t &, uint32_t &candidate, const compose::Intent &,
            compose::EffectBatch &batch) {
            candidate = 1u;
            return batch.Append(700u, candidate);
        },
        [](const MyComposeEffect &) -> MyComposeStatus {
            throw std::runtime_error("executor");
        });
    ASSERT_TRUE(store.has_value());
    ASSERT_EQ(store->Dispatch(compose::Intent{.type = 1u}), MY_COMPOSE_OK);
    ASSERT_EQ(store->Reduce(), MY_COMPOSE_OK);
    ASSERT_EQ(store->DispatchEffects(), MY_COMPOSE_FAILED);
    ASSERT_EQ(*store->CurrentState(), 1u);
}

TEST(runtime_and_store_moves_keep_stable_core_binding) {
    RuntimeLog log;
    auto store = compose::Store<Counter>::Create(Counter{0},
        [](const Counter &current, Counter &candidate, const compose::Intent &,
            compose::EffectBatch &) {
            candidate.count = current.count + 1;
            return MY_COMPOSE_OK;
        });
    ASSERT_TRUE(store.has_value());
    MyComposeSinkOps sink{};
    sink.context = &log;
    sink.stage = RuntimeStage;
    sink.commit = RuntimeCommit;
    sink.rollback = RuntimeRollback;
    auto runtime = compose::Runtime::Create(*store,
        [](compose::Builder &builder, const Counter &state) {
            auto root = builder.Node("@root");
            auto item = root.Key("counter").Element("label");
            (void)item.Property("count", IntValue(state.count));
            return builder.Status();
        }, sink);
    ASSERT_TRUE(runtime.has_value());
    auto moved_store = std::move(*store);
    auto moved_runtime = std::move(*runtime);
    ASSERT_FALSE(runtime->Valid());
    ASSERT_EQ(runtime->Pump(), MY_COMPOSE_INVALID);
    ASSERT_EQ(runtime->Restart(), MY_COMPOSE_INVALID);
    ASSERT_EQ(moved_runtime.Pump(), MY_COMPOSE_OK);
    ASSERT_EQ(log.stage_calls, 1u);
    ASSERT_EQ(log.commit_calls, 1u);
    ASSERT_EQ(moved_store.Dispatch(compose::Intent{.type = 1u}), MY_COMPOSE_OK);
    ASSERT_EQ(moved_runtime.Pump(), MY_COMPOSE_OK);
    ASSERT_EQ(moved_store.CurrentState()->count, 1);
    ASSERT_EQ(log.stage_calls, 2u);
    ASSERT_EQ(moved_runtime.Restart(), MY_COMPOSE_OK);
    ASSERT_EQ(moved_store.CurrentState()->count, 1);
}

TEST(runtime_view_exception_becomes_pending_view_status) {
    RuntimeLog log;
    auto store = compose::Store<uint32_t>::Create(0u,
        [](const uint32_t &, uint32_t &, const compose::Intent &,
            compose::EffectBatch &) {
            return MY_COMPOSE_OK;
        });
    ASSERT_TRUE(store.has_value());
    MyComposeSinkOps sink{};
    sink.context = &log;
    sink.stage = RuntimeStage;
    sink.commit = RuntimeCommit;
    sink.rollback = RuntimeRollback;
    uint32_t view_calls = 0;
    auto runtime = compose::Runtime::Create(*store,
        [&view_calls](compose::Builder &builder, const uint32_t &) -> MyComposeStatus {
            view_calls++;
            if (view_calls == 1u) throw std::runtime_error("view");
            auto root = builder.Node("@root");
            return builder.Status();
        }, sink);
    ASSERT_TRUE(runtime.has_value());
    ASSERT_EQ(runtime->Pump(), MY_COMPOSE_FAILED);
    ASSERT_EQ(runtime->Pump(), MY_COMPOSE_OK);
    ASSERT_EQ(view_calls, 2u);
    ASSERT_EQ(log.stage_calls, 1u);
    ASSERT_EQ(log.commit_calls, 1u);
    ASSERT_EQ(log.rollback_calls, 0u);
}

int main() {
    RUN_TEST(c_and_cpp_parity_uses_canonical_bytes_and_real_cross_language_link);
    RUN_TEST(node_scope_covers_dsl_moves_and_closes_only_live_scopes);
    RUN_TEST(remember_constructs_once_reuses_and_rejects_local_type_change);
    RUN_TEST(remember_constructor_exception_is_sticky_without_false_destruction);
    RUN_TEST(remember_without_an_open_scope_is_sticky_and_moved_builder_is_inert);
    RUN_TEST(store_supports_non_default_non_copy_assignable_state_and_moves);
    RUN_TEST(move_only_state_uses_custom_clone_and_disposes_each_live_slot_once);
    RUN_TEST(clone_exception_preserves_atom_state_and_fifo);
    RUN_TEST(reducer_exception_disposes_candidate_and_never_publishes_it);
    RUN_TEST(initial_state_construction_exception_returns_empty_without_leaks);
    RUN_TEST(effect_batch_uses_fixed_capacity_and_sticky_checked_append);
    RUN_TEST(executor_exception_crosses_c_abi_as_a_status);
    RUN_TEST(runtime_and_store_moves_keep_stable_core_binding);
    RUN_TEST(runtime_view_exception_becomes_pending_view_status);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
        g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
}
