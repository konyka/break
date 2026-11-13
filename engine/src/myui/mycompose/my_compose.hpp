#pragma once

#include <myui/mycompose/my_compose_runtime.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <functional>
#include <memory>
#include <new>
#include <optional>
#include <span>
#include <string_view>
#include <type_traits>
#include <utility>

#if defined(__cpp_exceptions) || defined(__EXCEPTIONS) || defined(_CPPUNWIND)
#define MY_COMPOSE_HPP_HAS_EXCEPTIONS 1
#else
#define MY_COMPOSE_HPP_HAS_EXCEPTIONS 0
#endif

namespace breakxx::compose {

struct Intent {
    uint32_t type = 0u;
    uint32_t payload_size = 0u;
    const uint8_t *payload = nullptr;
    MyComposeNodeHandle owner{};
    uint32_t result = 0u;

    [[nodiscard]] MyComposeIntent Raw() const noexcept {
        MyComposeIntent raw{};
        raw.type = type;
        raw.payload_size = payload_size;
        raw.payload = payload;
        raw.owner = owner;
        raw.result = result;
        return raw;
    }

    [[nodiscard]] static Intent FromC(const MyComposeIntent &raw) noexcept {
        Intent intent{};
        intent.type = raw.type;
        intent.payload_size = raw.payload_size;
        intent.payload = raw.payload;
        intent.owner = raw.owner;
        intent.result = raw.result;
        return intent;
    }
};

using Effect = MyComposeEffect;
using Diff = MyComposeDiff;
using NodeHandle = MyComposeNodeHandle;
using Value = MyComposeValue;
using Diagnostics = MyComposeDiagnostics;

namespace detail {
template <typename>
class StoreCore;
template <typename>
class RuntimeCore;
} // namespace detail

inline constexpr std::size_t kMaxDepth = MY_COMPOSE_MAX_DEPTH;
inline constexpr std::size_t kMaxRememberSlots = MY_COMPOSE_MAX_REMEMBER_SLOTS;
inline constexpr std::size_t kRememberBytes = MY_COMPOSE_REMEMBER_BYTES;
inline constexpr std::size_t kMaxStateBytes = MY_COMPOSE_STATE_BYTES;
inline constexpr std::size_t kMessageBytes = MY_COMPOSE_MESSAGE_BYTES;
inline constexpr std::size_t kMaxEffectsPerIntent =
    MY_COMPOSE_MAX_EFFECTS_PER_INTENT;
inline constexpr std::size_t kKeyBytes = MY_COMPOSE_KEY_BYTES;
inline constexpr std::size_t kNameBytes = MY_COMPOSE_NAME_BYTES;

class EffectBatch {
  public:
    EffectBatch() = default;
    EffectBatch(const EffectBatch &) = delete;
    EffectBatch &operator=(const EffectBatch &) = delete;
    EffectBatch(EffectBatch &&) = delete;
    EffectBatch &operator=(EffectBatch &&) = delete;

    [[nodiscard]] MyComposeStatus Append(uint32_t type,
        std::span<const uint8_t> payload) noexcept {
        if (status_ != MY_COMPOSE_OK) return status_;
        if (payload.size() > kMessageBytes || count_ >= kMaxEffectsPerIntent) {
            status_ = MY_COMPOSE_OVERLOAD;
            return status_;
        }
        if (!payload.empty() && payload.data() == nullptr) {
            status_ = MY_COMPOSE_INVALID;
            return status_;
        }
        Effect &effect = effects_[count_];
        effect = Effect{};
        effect.type = type;
        effect.payload_size = static_cast<uint32_t>(payload.size());
        effect.payload = payload_storage_[count_].data();
        if (!payload.empty()) {
            std::memcpy(payload_storage_[count_].data(), payload.data(),
                payload.size());
        }
        count_++;
        return MY_COMPOSE_OK;
    }

    [[nodiscard]] MyComposeStatus Append(uint32_t type, const void *payload,
        uint32_t payload_size) noexcept {
        return Append(type, std::span<const uint8_t>(
            static_cast<const uint8_t *>(payload), payload_size));
    }

    template <typename T>
        requires std::is_trivially_copyable_v<T>
    [[nodiscard]] MyComposeStatus Append(uint32_t type, const T &payload) noexcept {
        return Append(type, &payload, static_cast<uint32_t>(sizeof(T)));
    }

    [[nodiscard]] MyComposeStatus Append(uint32_t type) noexcept {
        return Append(type, std::span<const uint8_t>());
    }

    [[nodiscard]] uint32_t Count() const noexcept { return count_; }
    [[nodiscard]] MyComposeStatus Status() const noexcept { return status_; }

    [[nodiscard]] const Effect *At(uint32_t index) const noexcept {
        return index < count_ ? &effects_[index] : nullptr;
    }

  private:
    [[nodiscard]] MyComposeStatus Export(MyComposeEffectBatch &out) const noexcept {
        if (status_ != MY_COMPOSE_OK) return status_;
        for (uint32_t i = 0u; i < count_; ++i) {
            const MyComposeStatus status = my_compose_effect_batch_append(&out,
                effects_[i].type, payload_storage_[i].data(),
                effects_[i].payload_size);
            if (status != MY_COMPOSE_OK) return status;
        }
        return MY_COMPOSE_OK;
    }

    template <typename>
    friend class detail::StoreCore;

    std::array<Effect, kMaxEffectsPerIntent> effects_{};
    std::array<std::array<uint8_t, kMessageBytes>, kMaxEffectsPerIntent>
        payload_storage_{};
    uint32_t count_ = 0u;
    MyComposeStatus status_ = MY_COMPOSE_OK;
};

template <typename State>
struct StateOps {
    [[nodiscard]] static MyComposeStatus Clone(const State &source,
        std::optional<State> &destination)
        noexcept(std::is_nothrow_copy_constructible_v<State>) {
        destination.emplace(source);
        return MY_COMPOSE_OK;
    }

    static void Dispose(State &) noexcept {}
};

namespace detail {

struct DefaultExecutor {
    [[nodiscard]] MyComposeStatus operator()(const Effect &) const noexcept {
        return MY_COMPOSE_OK;
    }
};

template <typename T>
[[nodiscard]] consteval uint64_t TypeTag() {
#if defined(_MSC_VER) && !defined(__clang__)
    constexpr std::string_view name = __FUNCSIG__;
#else
    constexpr std::string_view name = __PRETTY_FUNCTION__;
#endif
    uint64_t hash = 14695981039346656037ull;
    for (const char value : name) {
        hash ^= static_cast<unsigned char>(value);
        hash *= 1099511628211ull;
    }
    return hash;
}

class StoreCoreBase {
  public:
    virtual ~StoreCoreBase() = default;
    [[nodiscard]] virtual MyComposeStore *RawStore() const noexcept = 0;
};

template <typename State>
class StoreCore final : public StoreCoreBase {
  public:
    using Reducer = std::function<MyComposeStatus(const State &, State &,
        const Intent &, EffectBatch &)>;
    using Executor = std::function<MyComposeStatus(const Effect &)>;

    StoreCore(Reducer reducer, Executor executor)
        : reducer_(std::move(reducer)), executor_(std::move(executor)) {}

    ~StoreCore() override {
        if (raw_ != nullptr) my_compose_store_destroy(raw_);
        raw_ = nullptr;
        for (std::size_t i = 0u; i < states_.size(); ++i) ResetSlot(i);
    }

    StoreCore(const StoreCore &) = delete;
    StoreCore &operator=(const StoreCore &) = delete;

    [[nodiscard]] MyComposeStore *RawStore() const noexcept override {
        return raw_;
    }

    [[nodiscard]] bool Create(State &initial) noexcept {
        MyComposeStateOps ops{};
        ops.context = this;
        ops.clone = CloneThunk;
        ops.dispose = DisposeThunk;
        raw_ = my_compose_store_create(&initial, sizeof(State), &ops, this,
            ReducerThunk, this, ExecutorThunk);
        return raw_ != nullptr;
    }

    [[nodiscard]] const State *StateFromRaw(const void *storage,
        uint32_t size) const noexcept {
        if (size != sizeof(State)) return nullptr;
        const std::size_t slot = FindSlot(storage);
        return slot < states_.size() && states_[slot].has_value()
            ? &*states_[slot]
            : nullptr;
    }

    [[nodiscard]] const State *CurrentState() const noexcept {
        if (raw_ == nullptr) return nullptr;
        const void *storage = nullptr;
        uint32_t size = 0u;
        if (my_compose_store_state(raw_, &storage, &size) != MY_COMPOSE_OK) {
            return nullptr;
        }
        return StateFromRaw(storage, size);
    }

  private:
    static constexpr std::size_t kInvalidSlot = 2u;

    [[nodiscard]] std::size_t FindSlot(const void *storage) const noexcept {
        for (std::size_t i = 0u; i < raw_slots_.size(); ++i) {
            if (raw_slots_[i] == storage) return i;
        }
        return kInvalidSlot;
    }

    void ResetSlot(std::size_t slot) noexcept {
        if (slot >= states_.size() || !states_[slot].has_value()) return;
#if MY_COMPOSE_HPP_HAS_EXCEPTIONS
        try {
            StateOps<State>::Dispose(*states_[slot]);
            states_[slot].reset();
        } catch (...) {
        }
#else
        StateOps<State>::Dispose(*states_[slot]);
        states_[slot].reset();
#endif
    }

    [[nodiscard]] MyComposeStatus Clone(const void *source,
        uint32_t source_size, void *destination, uint32_t destination_size,
        uint32_t *out_size) noexcept {
        if (source == nullptr || destination == nullptr || out_size == nullptr ||
            source_size != sizeof(State) || destination_size < sizeof(State)) {
            return MY_COMPOSE_INVALID;
        }
        std::size_t destination_slot = FindSlot(destination);
        if (destination_slot == kInvalidSlot) {
            const std::size_t source_slot = FindSlot(source);
            if (raw_slots_[0] == nullptr) {
                destination_slot = 0u;
            } else if (source_slot < states_.size() &&
                       raw_slots_[1u - source_slot] == nullptr) {
                destination_slot = 1u - source_slot;
            } else {
                return MY_COMPOSE_FAILED;
            }
            raw_slots_[destination_slot] = destination;
        }
        const std::size_t source_slot = FindSlot(source);
        const State *typed_source = source_slot < states_.size()
            ? StateFromRaw(source, source_size)
            : static_cast<const State *>(source);
        if (typed_source == nullptr) return MY_COMPOSE_FAILED;
        ResetSlot(destination_slot);
#if MY_COMPOSE_HPP_HAS_EXCEPTIONS
        try {
            const MyComposeStatus status = StateOps<State>::Clone(*typed_source,
                states_[destination_slot]);
            if (status != MY_COMPOSE_OK) {
                ResetSlot(destination_slot);
                return status;
            }
        } catch (...) {
            ResetSlot(destination_slot);
            return MY_COMPOSE_FAILED;
        }
#else
        const MyComposeStatus status = StateOps<State>::Clone(*typed_source,
            states_[destination_slot]);
        if (status != MY_COMPOSE_OK) {
            ResetSlot(destination_slot);
            return status;
        }
#endif
        if (!states_[destination_slot].has_value()) return MY_COMPOSE_FAILED;
        *out_size = sizeof(State);
        return MY_COMPOSE_OK;
    }

    [[nodiscard]] MyComposeStatus Reduce(const Intent &intent,
        const void *current, uint32_t current_size, void *candidate,
        uint32_t *candidate_size, MyComposeEffectBatch &batch) noexcept {
        const State *typed_current = StateFromRaw(current, current_size);
        const std::size_t candidate_slot = FindSlot(candidate);
        if (typed_current == nullptr || candidate_slot >= states_.size() ||
            candidate_size == nullptr || *candidate_size != sizeof(State) ||
            !states_[candidate_slot].has_value()) {
            return MY_COMPOSE_FAILED;
        }
        EffectBatch typed_batch;
#if MY_COMPOSE_HPP_HAS_EXCEPTIONS
        try {
            const MyComposeStatus status = reducer_(*typed_current,
                *states_[candidate_slot], intent, typed_batch);
            if (status != MY_COMPOSE_OK) return status;
        } catch (...) {
            return MY_COMPOSE_FAILED;
        }
#else
        const MyComposeStatus status = reducer_(*typed_current,
            *states_[candidate_slot], intent, typed_batch);
        if (status != MY_COMPOSE_OK) return status;
#endif
        return typed_batch.Export(batch);
    }

    [[nodiscard]] MyComposeStatus Execute(const Effect &effect) noexcept {
#if MY_COMPOSE_HPP_HAS_EXCEPTIONS
        try {
            return executor_(effect);
        } catch (...) {
            return MY_COMPOSE_FAILED;
        }
#else
        return executor_(effect);
#endif
    }

    static MyComposeStatus CloneThunk(void *context, const void *source,
        uint32_t source_size, void *destination, uint32_t destination_size,
        uint32_t *out_size) noexcept {
        return static_cast<StoreCore *>(context)->Clone(source, source_size,
            destination, destination_size, out_size);
    }

    static void DisposeThunk(void *context, void *storage, uint32_t size) noexcept {
        auto *core = static_cast<StoreCore *>(context);
        if (size != sizeof(State)) return;
        const std::size_t slot = core->FindSlot(storage);
        if (slot < core->states_.size()) core->ResetSlot(slot);
    }

    static MyComposeStatus ReducerThunk(void *context, const MyComposeIntent *intent,
        const void *current, uint32_t current_size, void *candidate,
        uint32_t *candidate_size, MyComposeEffectBatch *batch) noexcept {
        if (intent == nullptr || batch == nullptr) return MY_COMPOSE_INVALID;
        const Intent typed_intent = Intent::FromC(*intent);
        return static_cast<StoreCore *>(context)->Reduce(typed_intent, current,
            current_size, candidate, candidate_size, *batch);
    }

    static MyComposeStatus ExecutorThunk(void *context,
        const Effect *effect) noexcept {
        if (effect == nullptr) return MY_COMPOSE_INVALID;
        return static_cast<StoreCore *>(context)->Execute(*effect);
    }

    std::array<std::optional<State>, 2u> states_{};
    std::array<void *, 2u> raw_slots_{};
    MyComposeStore *raw_ = nullptr;
    Reducer reducer_;
    Executor executor_;
};

struct RememberContext {
    NodeHandle owner{};
    uint32_t local_slot = 0u;
    void *storage = nullptr;
    bool used = false;
    bool engaged = false;
    void (*destroy)(void *) = nullptr;
};

class BuilderCore {
  public:
    BuilderCore() : raw_(my_compose_tree_builder_create()) {}
    ~BuilderCore() {
        if (raw_ != nullptr) my_compose_tree_builder_destroy(raw_);
    }

    BuilderCore(const BuilderCore &) = delete;
    BuilderCore &operator=(const BuilderCore &) = delete;

    MyComposeStatus Fail(MyComposeStatus status) noexcept {
        if (status != MY_COMPOSE_OK && status_ == MY_COMPOSE_OK) status_ = status;
        return status_;
    }

    [[nodiscard]] MyComposeStatus Ready() const noexcept { return status_; }

    [[nodiscard]] MyComposeStatus Begin() noexcept {
        if (status_ != MY_COMPOSE_OK || raw_ == nullptr) return Fail(MY_COMPOSE_INVALID);
        const MyComposeStatus status = my_compose_tree_builder_begin(raw_);
        if (status == MY_COMPOSE_OK) {
            depth_ = 0u;
            epoch_++;
        }
        return Fail(status);
    }

    [[nodiscard]] MyComposeStatus Open(NodeHandle parent, const char *key,
        const char *type, NodeHandle &out, uint64_t &epoch) noexcept {
        if (status_ != MY_COMPOSE_OK || raw_ == nullptr) return Fail(MY_COMPOSE_INVALID);
        MyComposeNodeDesc desc{};
        desc.parent = parent;
        desc.key = key;
        desc.type = type;
        const MyComposeStatus status = my_compose_tree_builder_node(raw_, &desc, &out);
        if (status != MY_COMPOSE_OK) return Fail(status);
        if (depth_ >= scopes_.size()) return Fail(MY_COMPOSE_OVERLOAD);
        scopes_[depth_++] = out;
        epoch = epoch_;
        return MY_COMPOSE_OK;
    }

    void Close(NodeHandle node, uint64_t epoch) noexcept {
        if (epoch != epoch_) return;
        if (depth_ == 0u || scopes_[depth_ - 1u].index != node.index ||
            scopes_[depth_ - 1u].generation != node.generation) {
            Fail(MY_COMPOSE_INVALID);
            return;
        }
        depth_--;
    }

    [[nodiscard]] NodeHandle Current() const noexcept {
        return depth_ == 0u ? NodeHandle{} : scopes_[depth_ - 1u];
    }

    [[nodiscard]] MyComposeStatus End() noexcept {
        if (status_ != MY_COMPOSE_OK || raw_ == nullptr) return Fail(MY_COMPOSE_INVALID);
        if (depth_ != 0u) return Fail(MY_COMPOSE_INVALID);
        return Fail(my_compose_tree_builder_end(raw_));
    }

    [[nodiscard]] MyComposeStatus Finalize() noexcept {
        if (status_ != MY_COMPOSE_OK || raw_ == nullptr) return Fail(MY_COMPOSE_INVALID);
        if (depth_ != 0u) return Fail(MY_COMPOSE_INVALID);
        return Fail(my_compose_tree_builder_finalize(raw_));
    }

    static void DisposeRemember(void *opaque, void *, uint32_t) noexcept {
        auto *context = static_cast<RememberContext *>(opaque);
        if (context->engaged && context->destroy != nullptr) {
#if MY_COMPOSE_HPP_HAS_EXCEPTIONS
            try {
                context->destroy(context->storage);
            } catch (...) {
            }
#else
            context->destroy(context->storage);
#endif
        }
        context->engaged = false;
        context->destroy = nullptr;
        context->used = false;
        context->storage = nullptr;
        context->owner = NodeHandle{};
        context->local_slot = 0u;
    }

    MyComposeTreeBuilder *raw_ = nullptr;
    MyComposeStatus status_ = MY_COMPOSE_OK;
    std::array<NodeHandle, kMaxDepth + 1u> scopes_{};
    std::size_t depth_ = 0u;
    uint64_t epoch_ = 0u;
    std::array<RememberContext, kMaxRememberSlots> remember_{};
};

class RuntimeCoreBase {
  public:
    virtual ~RuntimeCoreBase() = default;
    MyComposeRuntime *raw_ = nullptr;
};

} // namespace detail

class NodeScope;

class Builder {
  public:
    Builder() = default;
    ~Builder() = default;
    Builder(const Builder &) = delete;
    Builder &operator=(const Builder &) = delete;
    Builder(Builder &&) noexcept = default;
    Builder &operator=(Builder &&) noexcept = default;

    [[nodiscard]] static std::optional<Builder> Create() {
#if MY_COMPOSE_HPP_HAS_EXCEPTIONS
        try {
            auto core = std::make_shared<detail::BuilderCore>();
            if (core->raw_ == nullptr) return std::nullopt;
            return Builder(std::move(core));
        } catch (...) {
            return std::nullopt;
        }
#else
        auto core = std::make_shared<detail::BuilderCore>();
        if (core->raw_ == nullptr) return std::nullopt;
        return Builder(std::move(core));
#endif
    }

    [[nodiscard]] bool Valid() const noexcept {
        return core_ != nullptr && core_->raw_ != nullptr;
    }

    [[nodiscard]] MyComposeStatus Status() const noexcept {
        return core_ == nullptr ? MY_COMPOSE_INVALID : core_->status_;
    }

    [[nodiscard]] MyComposeStatus Begin() noexcept {
        return core_ == nullptr ? MY_COMPOSE_INVALID : core_->Begin();
    }

    [[nodiscard]] MyComposeStatus End() noexcept {
        return core_ == nullptr ? MY_COMPOSE_INVALID : core_->End();
    }

    [[nodiscard]] MyComposeStatus Finalize() noexcept {
        return core_ == nullptr ? MY_COMPOSE_INVALID : core_->Finalize();
    }

    [[nodiscard]] NodeScope Node(const char *type);
    [[nodiscard]] NodeScope Node(const char *key, const char *type);

    template <typename T, typename Factory>
    [[nodiscard]] T *Remember(uint32_t local_slot, Factory &&factory) {
        if (core_ == nullptr) return nullptr;
        if (core_->depth_ == 0u) {
            core_->Fail(MY_COMPOSE_INVALID);
            return nullptr;
        }
        return RememberAt<T>(core_, core_->Current(), local_slot,
            std::forward<Factory>(factory));
    }

    [[nodiscard]] const MyComposeDiff *Diff() const noexcept {
        return core_ == nullptr ? nullptr : my_compose_tree_builder_diff(core_->raw_);
    }

    [[nodiscard]] uint32_t CurrentNodeCount() const noexcept {
        return core_ == nullptr ? 0u
            : my_compose_tree_builder_current_node_count(core_->raw_);
    }

    [[nodiscard]] uint32_t NextNodeCount() const noexcept {
        return core_ == nullptr ? 0u
            : my_compose_tree_builder_next_node_count(core_->raw_);
    }

    [[nodiscard]] MyComposeStatus GetProperty(NodeHandle owner,
        const char *name, Value &out) const noexcept {
        return core_ == nullptr ? MY_COMPOSE_INVALID
            : my_compose_tree_builder_get_property(core_->raw_, owner, name, &out);
    }

    [[nodiscard]] MyComposeStatus GetEvent(NodeHandle owner, const char *name,
        Intent &out) const noexcept {
        if (core_ == nullptr) return MY_COMPOSE_INVALID;
        MyComposeIntent raw{};
        const MyComposeStatus status = my_compose_tree_builder_get_event(core_->raw_,
            owner, name, &raw);
        if (status == MY_COMPOSE_OK) out = Intent::FromC(raw);
        return status;
    }

  private:
    friend class NodeScope;
    template <typename>
    friend class detail::RuntimeCore;

    explicit Builder(std::shared_ptr<detail::BuilderCore> core)
        : core_(std::move(core)) {}

    [[nodiscard]] MyComposeTreeBuilder *Raw() const noexcept {
        return core_ == nullptr ? nullptr : core_->raw_;
    }

    template <typename T, typename Factory>
    [[nodiscard]] static T *RememberAt(
        const std::shared_ptr<detail::BuilderCore> &core, NodeHandle owner,
        uint32_t local_slot, Factory &&factory) {
        static_assert(sizeof(T) <= kRememberBytes, "Remember<T> exceeds slot bytes");
        static_assert(alignof(T) <= MY_COMPOSE_MAX_ALIGNMENT,
            "Remember<T> exceeds slot alignment");
#if !MY_COMPOSE_HPP_HAS_EXCEPTIONS
        static_assert(std::is_nothrow_invocable_v<Factory>,
            "Remember factories must be noexcept without exceptions");
#endif
        if (core == nullptr || core->Ready() != MY_COMPOSE_OK) return nullptr;
        detail::RememberContext *context = nullptr;
        for (auto &candidate : core->remember_) {
            if (candidate.used && candidate.owner.index == owner.index &&
                candidate.owner.generation == owner.generation &&
                candidate.local_slot == local_slot) {
                context = &candidate;
                break;
            }
        }
        const bool existing = context != nullptr;
        if (context == nullptr) {
            for (auto &candidate : core->remember_) {
                if (!candidate.used) {
                    context = &candidate;
                    break;
                }
            }
        }
        if (context == nullptr) {
            core->Fail(MY_COMPOSE_OVERLOAD);
            return nullptr;
        }
        context->used = true;
        context->owner = owner;
        context->local_slot = local_slot;
        MyComposeRememberOps ops{};
        ops.context = context;
        ops.dispose = detail::BuilderCore::DisposeRemember;
        void *storage = nullptr;
        const MyComposeStatus status = my_compose_tree_builder_remember(core->raw_,
            owner, local_slot, detail::TypeTag<T>(), sizeof(T), alignof(T), &ops,
            &storage);
        if (status != MY_COMPOSE_OK || storage == nullptr) {
            if (!existing) {
                context->used = false;
                context->owner = NodeHandle{};
                context->local_slot = 0u;
            }
            core->Fail(status == MY_COMPOSE_OK ? MY_COMPOSE_FAILED : status);
            return nullptr;
        }
        context->storage = storage;
        if (context->engaged) return static_cast<T *>(storage);
        context->destroy = [](void *object) { static_cast<T *>(object)->~T(); };
#if MY_COMPOSE_HPP_HAS_EXCEPTIONS
        try {
            ::new (storage) T(std::invoke(std::forward<Factory>(factory)));
        } catch (...) {
            context->destroy = nullptr;
            core->Fail(MY_COMPOSE_FAILED);
            return nullptr;
        }
#else
        ::new (storage) T(std::invoke(std::forward<Factory>(factory)));
#endif
        context->engaged = true;
        return static_cast<T *>(storage);
    }

    std::shared_ptr<detail::BuilderCore> core_;
};

class NodeScope {
  public:
    NodeScope() = default;
    ~NodeScope() { Close(); }
    NodeScope(const NodeScope &) = delete;
    NodeScope &operator=(const NodeScope &) = delete;

    NodeScope(NodeScope &&other) noexcept
        : core_(std::move(other.core_)), node_(other.node_), epoch_(other.epoch_),
          open_(other.open_), pending_key_(other.pending_key_),
          pending_has_key_(other.pending_has_key_) {
        other.node_ = NodeHandle{};
        other.epoch_ = 0u;
        other.open_ = false;
        other.pending_has_key_ = false;
    }

    NodeScope &operator=(NodeScope &&other) noexcept {
        if (this != &other) {
            Close();
            core_ = std::move(other.core_);
            node_ = other.node_;
            epoch_ = other.epoch_;
            open_ = other.open_;
            pending_key_ = other.pending_key_;
            pending_has_key_ = other.pending_has_key_;
            other.node_ = NodeHandle{};
            other.epoch_ = 0u;
            other.open_ = false;
            other.pending_has_key_ = false;
        }
        return *this;
    }

    [[nodiscard]] bool Valid() const noexcept { return open_ && core_ != nullptr; }
    [[nodiscard]] NodeHandle Handle() const noexcept { return node_; }

    void Close() noexcept {
        if (!open_) return;
        if (core_ != nullptr) core_->Close(node_, epoch_);
        open_ = false;
        core_.reset();
    }

    [[nodiscard]] NodeScope &Key(const char *key) noexcept {
        if (!Valid()) return *this;
        if (key == nullptr) {
            pending_key_[0] = '\0';
            pending_has_key_ = true;
            return *this;
        }
        std::size_t size = 0u;
        while (size < kKeyBytes && key[size] != '\0') size++;
        if (size == kKeyBytes) {
            core_->Fail(MY_COMPOSE_OVERLOAD);
            return *this;
        }
        std::memcpy(pending_key_.data(), key, size + 1u);
        pending_has_key_ = true;
        return *this;
    }

    [[nodiscard]] NodeScope Row() { return Open("@row", ConsumeKey()); }
    [[nodiscard]] NodeScope Row(const char *key) { return Open("@row", key); }
    [[nodiscard]] NodeScope Column() { return Open("@column", ConsumeKey()); }
    [[nodiscard]] NodeScope Column(const char *key) { return Open("@column", key); }
    [[nodiscard]] NodeScope Stack() { return Open("@stack", ConsumeKey()); }
    [[nodiscard]] NodeScope Stack(const char *key) { return Open("@stack", key); }
    [[nodiscard]] NodeScope Element(const char *type) {
        return Open(type, ConsumeKey());
    }
    [[nodiscard]] NodeScope Element(const char *key, const char *type) {
        return Open(type, key);
    }

    [[nodiscard]] NodeScope &Property(const char *name, const Value &value) noexcept {
        if (Valid()) {
            core_->Fail(my_compose_tree_builder_property(core_->raw_, node_, name,
                &value));
        }
        return *this;
    }

    template <typename T>
        requires std::is_arithmetic_v<T>
    [[nodiscard]] NodeScope &Property(const char *name, T input) noexcept {
        Value value{};
        if constexpr (std::is_same_v<T, bool>) {
            value.type = MY_COMPOSE_VALUE_BOOL;
            value.as.bool_value = input;
        } else if constexpr (std::is_floating_point_v<T> && sizeof(T) <= sizeof(float)) {
            value.type = MY_COMPOSE_VALUE_FLOAT;
            value.as.float_value = static_cast<float>(input);
        } else if constexpr (std::is_floating_point_v<T>) {
            value.type = MY_COMPOSE_VALUE_DOUBLE;
            value.as.double_value = static_cast<double>(input);
        } else if constexpr (std::is_signed_v<T> && sizeof(T) <= sizeof(int32_t)) {
            value.type = MY_COMPOSE_VALUE_INT32;
            value.as.int32_value = static_cast<int32_t>(input);
        } else if constexpr (std::is_signed_v<T>) {
            value.type = MY_COMPOSE_VALUE_INT64;
            value.as.int64_value = static_cast<int64_t>(input);
        } else if constexpr (sizeof(T) <= sizeof(uint32_t)) {
            value.type = MY_COMPOSE_VALUE_UINT32;
            value.as.uint32_value = static_cast<uint32_t>(input);
        } else {
            value.type = MY_COMPOSE_VALUE_INT64;
            value.as.int64_value = static_cast<int64_t>(input);
        }
        return Property(name, value);
    }

    [[nodiscard]] NodeScope &Property(const char *name, const char *input) noexcept {
        if (input == nullptr) {
            if (Valid()) core_->Fail(MY_COMPOSE_INVALID);
            return *this;
        }
        Value value{};
        value.type = MY_COMPOSE_VALUE_STRING;
        value.as.string.data = input;
        value.as.string.size = static_cast<uint32_t>(std::char_traits<char>::length(input));
        return Property(name, value);
    }

    template <typename T>
    [[nodiscard]] NodeScope &Style(const char *name, const T &value) noexcept {
        return Style(nullptr, name, value);
    }

    template <typename T>
    [[nodiscard]] NodeScope &Style(const char *state, const char *name,
        const T &value) noexcept {
        if (!Valid()) return *this;
        std::array<char, kNameBytes> full{};
        std::size_t offset = 0u;
        const auto append = [&full, &offset](std::string_view part) {
            if (part.size() >= full.size() - offset) return false;
            std::memcpy(full.data() + offset, part.data(), part.size());
            offset += part.size();
            full[offset] = '\0';
            return true;
        };
        if (name == nullptr || !append("style:") ||
            (state != nullptr && (!append(state) || !append(":"))) ||
            !append(name)) {
            core_->Fail(name == nullptr ? MY_COMPOSE_INVALID : MY_COMPOSE_OVERLOAD);
            return *this;
        }
        return Property(full.data(), value);
    }

    [[nodiscard]] NodeScope &OnEvent(const char *name, Intent intent) noexcept {
        if (Valid()) {
            const MyComposeIntent raw = intent.Raw();
            core_->Fail(my_compose_tree_builder_event(core_->raw_, node_, name,
                &raw));
        }
        return *this;
    }

    [[nodiscard]] NodeScope &OnClick(Intent intent) noexcept {
        return OnEvent("click", intent);
    }

    template <typename T, typename Factory>
    [[nodiscard]] T *Remember(uint32_t local_slot, Factory &&factory) {
        return Builder::RememberAt<T>(core_, node_, local_slot,
            std::forward<Factory>(factory));
    }

  private:
    friend class Builder;

    NodeScope(std::shared_ptr<detail::BuilderCore> core, NodeHandle node,
        uint64_t epoch, bool open)
        : core_(std::move(core)), node_(node), epoch_(epoch), open_(open) {}

    [[nodiscard]] NodeScope Open(const char *type, const char *key) {
        if (!Valid()) return NodeScope();
        NodeHandle child{};
        uint64_t child_epoch = 0u;
        if (core_->Open(node_, key, type, child, child_epoch) != MY_COMPOSE_OK) {
            return NodeScope();
        }
        return NodeScope(core_, child, child_epoch, true);
    }

    [[nodiscard]] const char *ConsumeKey() noexcept {
        if (!pending_has_key_) return nullptr;
        pending_has_key_ = false;
        return pending_key_.data();
    }

    std::shared_ptr<detail::BuilderCore> core_;
    NodeHandle node_{};
    uint64_t epoch_ = 0u;
    bool open_ = false;
    std::array<char, kKeyBytes> pending_key_{};
    bool pending_has_key_ = false;
};

inline NodeScope Builder::Node(const char *type) {
    return Node(nullptr, type);
}

inline NodeScope Builder::Node(const char *key, const char *type) {
    if (core_ == nullptr) return NodeScope();
    NodeHandle node{};
    uint64_t epoch = 0u;
    if (core_->Open(core_->Current(), key, type, node, epoch) != MY_COMPOSE_OK) {
        return NodeScope();
    }
    return NodeScope(core_, node, epoch, true);
}

template <typename State>
class Store {
  public:
    using Reducer = typename detail::StoreCore<State>::Reducer;
    using Executor = typename detail::StoreCore<State>::Executor;

    Store() = default;
    ~Store() = default;
    Store(const Store &) = delete;
    Store &operator=(const Store &) = delete;
    Store(Store &&) noexcept = default;
    Store &operator=(Store &&) noexcept = default;

    template <typename ReducerFn, typename ExecutorFn = detail::DefaultExecutor>
    [[nodiscard]] static std::optional<Store> Create(State initial,
        ReducerFn &&reducer, ExecutorFn &&executor = ExecutorFn{}) {
        static_assert(sizeof(State) <= kMaxStateBytes, "State exceeds C storage");
#if !MY_COMPOSE_HPP_HAS_EXCEPTIONS
        static_assert(std::is_nothrow_invocable_r_v<MyComposeStatus, ReducerFn,
            const State &, State &, const Intent &, EffectBatch &>,
            "Reducers must be noexcept without exceptions");
        static_assert(std::is_nothrow_invocable_r_v<MyComposeStatus, ExecutorFn,
            const Effect &>, "Executors must be noexcept without exceptions");
        static_assert(noexcept(StateOps<State>::Clone(initial,
            std::declval<std::optional<State> &>())),
            "StateOps::Clone must be noexcept without exceptions");
#endif
#if MY_COMPOSE_HPP_HAS_EXCEPTIONS
        try {
            auto core = std::make_shared<detail::StoreCore<State>>(
                Reducer(std::forward<ReducerFn>(reducer)),
                Executor(std::forward<ExecutorFn>(executor)));
            if (!core->Create(initial)) return std::nullopt;
            return Store(std::move(core));
        } catch (...) {
            return std::nullopt;
        }
#else
        auto core = std::make_shared<detail::StoreCore<State>>(
            Reducer(std::forward<ReducerFn>(reducer)),
            Executor(std::forward<ExecutorFn>(executor)));
        if (!core->Create(initial)) return std::nullopt;
        return Store(std::move(core));
#endif
    }

    [[nodiscard]] bool Valid() const noexcept {
        return core_ != nullptr && core_->RawStore() != nullptr;
    }

    [[nodiscard]] MyComposeStatus Dispatch(const Intent &intent) noexcept {
        if (!Valid()) return MY_COMPOSE_INVALID;
        const MyComposeIntent raw = intent.Raw();
        return my_compose_store_dispatch(core_->RawStore(), &raw);
    }

    [[nodiscard]] MyComposeStatus Reduce() noexcept {
        return Valid() ? my_compose_store_reduce(core_->RawStore())
            : MY_COMPOSE_INVALID;
    }

    [[nodiscard]] MyComposeStatus DispatchEffects() noexcept {
        return Valid() ? my_compose_store_dispatch_effects(core_->RawStore())
            : MY_COMPOSE_INVALID;
    }

    [[nodiscard]] MyComposeStatus Restart() noexcept {
        return Valid() ? my_compose_store_restart(core_->RawStore())
            : MY_COMPOSE_INVALID;
    }

    void Close() noexcept {
        if (Valid()) my_compose_store_close(core_->RawStore());
    }

    [[nodiscard]] const State *CurrentState() const noexcept {
        return core_ == nullptr ? nullptr : core_->CurrentState();
    }

    [[nodiscard]] const MyComposeDiagnostics *Diagnostics() const noexcept {
        return Valid() ? my_compose_store_diagnostics(core_->RawStore()) : nullptr;
    }

  private:
    friend class Runtime;

    explicit Store(std::shared_ptr<detail::StoreCore<State>> core)
        : core_(std::move(core)) {}

    std::shared_ptr<detail::StoreCore<State>> core_;
};

namespace detail {

template <typename State>
class RuntimeCore final : public RuntimeCoreBase {
  public:
    using View = std::function<MyComposeStatus(Builder &, const State &)>;

    RuntimeCore(std::shared_ptr<StoreCore<State>> store, Builder builder,
        View view)
        : store_(std::move(store)), builder_(std::move(builder)),
          view_(std::move(view)) {}

    ~RuntimeCore() override {
        if (raw_ != nullptr) my_compose_runtime_destroy(raw_);
        raw_ = nullptr;
    }

    RuntimeCore(const RuntimeCore &) = delete;
    RuntimeCore &operator=(const RuntimeCore &) = delete;

    [[nodiscard]] MyComposeTreeBuilder *RawBuilder() noexcept {
        return builder_.Raw();
    }

    static MyComposeStatus ViewThunk(void *opaque, MyComposeTreeBuilder *,
        const void *state, uint32_t state_size) noexcept {
        auto *core = static_cast<RuntimeCore *>(opaque);
        const State *typed_state = core->store_->StateFromRaw(state, state_size);
        if (typed_state == nullptr) return MY_COMPOSE_FAILED;
#if MY_COMPOSE_HPP_HAS_EXCEPTIONS
        try {
            return core->view_(core->builder_, *typed_state);
        } catch (...) {
            return MY_COMPOSE_FAILED;
        }
#else
        return core->view_(core->builder_, *typed_state);
#endif
    }

    std::shared_ptr<StoreCore<State>> store_;
    Builder builder_;
    View view_;
};

} // namespace detail

class Runtime {
  public:
    Runtime() = default;
    ~Runtime() = default;
    Runtime(const Runtime &) = delete;
    Runtime &operator=(const Runtime &) = delete;
    Runtime(Runtime &&) noexcept = default;
    Runtime &operator=(Runtime &&) noexcept = default;

    template <typename State, typename View>
    [[nodiscard]] static std::optional<Runtime> Create(Store<State> &store,
        View &&view, MyComposeSinkOps sink) {
#if !MY_COMPOSE_HPP_HAS_EXCEPTIONS
        static_assert(std::is_nothrow_invocable_r_v<MyComposeStatus, View,
            Builder &, const State &>, "Views must be noexcept without exceptions");
#endif
        if (!store.Valid() || sink.stage == nullptr || sink.commit == nullptr ||
            sink.rollback == nullptr ||
            (sink.store != nullptr && sink.store != store.core_->RawStore())) {
            return std::nullopt;
        }
        auto builder = Builder::Create();
        if (!builder.has_value()) return std::nullopt;
#if MY_COMPOSE_HPP_HAS_EXCEPTIONS
        try {
            using Core = detail::RuntimeCore<State>;
            auto core = std::make_shared<Core>(store.core_, std::move(*builder),
                typename Core::View(std::forward<View>(view)));
            sink.store = store.core_->RawStore();
            MyComposeRuntimeConfig config{};
            config.store = store.core_->RawStore();
            config.view = Core::ViewThunk;
            config.view_context = core.get();
            config.sink = sink;
            core->raw_ = my_compose_runtime_create(core->RawBuilder(), &config);
            if (core->raw_ == nullptr) return std::nullopt;
            return Runtime(std::move(core));
        } catch (...) {
            return std::nullopt;
        }
#else
        using Core = detail::RuntimeCore<State>;
        auto core = std::make_shared<Core>(store.core_, std::move(*builder),
            typename Core::View(std::forward<View>(view)));
        sink.store = store.core_->RawStore();
        MyComposeRuntimeConfig config{};
        config.store = store.core_->RawStore();
        config.view = Core::ViewThunk;
        config.view_context = core.get();
        config.sink = sink;
        core->raw_ = my_compose_runtime_create(core->RawBuilder(), &config);
        if (core->raw_ == nullptr) return std::nullopt;
        return Runtime(std::move(core));
#endif
    }

    [[nodiscard]] bool Valid() const noexcept {
        return core_ != nullptr && core_->raw_ != nullptr;
    }

    [[nodiscard]] MyComposeStatus Pump() noexcept {
        return Valid() ? my_compose_runtime_pump(core_->raw_) : MY_COMPOSE_INVALID;
    }

    [[nodiscard]] MyComposeStatus Restart() noexcept {
        return Valid() ? my_compose_runtime_restart(core_->raw_) : MY_COMPOSE_INVALID;
    }

  private:
    explicit Runtime(std::shared_ptr<detail::RuntimeCoreBase> core)
        : core_(std::move(core)) {}

    std::shared_ptr<detail::RuntimeCoreBase> core_;
};

} // namespace breakxx::compose
