#include <myui/mycompose/my_compose.hpp>

static_assert(__cplusplus >= 202002L, "C++20 is required");

int main() {
    namespace compose = breakxx::compose;
    auto store = compose::Store<uint32_t>::Create(0u,
        [](const uint32_t &current, uint32_t &candidate,
            const compose::Intent &, compose::EffectBatch &batch) noexcept {
            candidate = current + 1u;
            return batch.Append(1u);
        },
        [](const MyComposeEffect &) noexcept {
            return MY_COMPOSE_OK;
        });
    if (!store.has_value()) return 1;
    if (store->Dispatch(compose::Intent{.type = 1u}) != MY_COMPOSE_OK) return 2;
    if (store->Reduce() != MY_COMPOSE_OK) return 3;
    if (store->DispatchEffects() != MY_COMPOSE_OK) return 4;
    const uint32_t *state = store->CurrentState();
    if (state == nullptr || *state != 1u) return 5;

    auto builder = compose::Builder::Create();
    if (!builder.has_value()) return 6;
    if (builder->Begin() != MY_COMPOSE_OK) return 7;
    {
        auto root = builder->Node("@root");
        auto item = root.Key("item").Element("label");
        auto *remembered = builder->Remember<uint32_t>(0u,
            []() noexcept { return 9u; });
        if (remembered == nullptr || *remembered != 9u) return 8;
    }
    if (builder->End() != MY_COMPOSE_OK) return 9;
    if (builder->Finalize() != MY_COMPOSE_OK) return 10;
    if (builder->Diff() == nullptr) return 11;
    return 0;
}
