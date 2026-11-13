/* Compose + MVI on the real BreakUI frame path (Vulkan or OpenGL, chosen at
 * compile time, created with rhi_device_create: no fallback chain).
 *
 * Each frame (test_mycompose_image.c) runs platform_poll -> break_ui_pump ->
 * my_compose_myui_pump -> break_ui_frame_begin/render -> rhi_frame_end ->
 * rhi_screenshot -> rhi_present.
 *
 * Evidence grades printed by this test:
 *  - pointer/key: SYNTHETIC_INPUTSTATE. Edges are written into the platform
 *    InputState after platform_poll and before break_ui_pump; BreakUI's
 *    production pump turns them into myui events. No compositor injected
 *    them, so this is not native Wayland seat evidence.
 *  - text: DIRECT_DISPATCH. platform.h has no text-queue injection, so the
 *    committed text is a MY_EVENT_IME_COMMIT sent to the window manager.
 *    The test asserts platform_poll_text stayed empty, so it is never
 *    counted as text-input protocol evidence.
 * Exit 77 only without a Wayland display or device. */
#include "test_mycompose_image.h"

extern "C" {
#include <editor/editor_i18n.h>
}

#include <myui/mycompose/my_compose.hpp>
#include <myui/mycompose/my_compose_tree.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <new>

#ifndef MYCOMPOSE_GPU_VULKAN
#define MYCOMPOSE_GPU_VULKAN 1
#endif
#ifndef MYCOMPOSE_GPU_BACKEND
#define MYCOMPOSE_GPU_BACKEND 1
#endif

namespace compose = breakxx::compose;

/* ---- allocation counting ----------------------------------------------
 * MYCOMPOSE_ALLOC_WRAP links with -Wl,--wrap=malloc/calloc/realloc, so
 * every malloc from the statically linked engine, myui and Compose code
 * lands here; operator new covers the C++ DSL. Shared drivers (Mesa,
 * loader) are not wrapped. */
static uint64_t g_c_allocs = 0u;
static uint64_t g_cxx_allocs = 0u;

#if MYCOMPOSE_ALLOC_WRAP
extern "C" {
void *__real_malloc(size_t size);
void *__real_calloc(size_t count, size_t size);
void *__real_realloc(void *ptr, size_t size);
void *__wrap_malloc(size_t size) {
    g_c_allocs++;
    return __real_malloc(size);
}
void *__wrap_calloc(size_t count, size_t size) {
    g_c_allocs++;
    return __real_calloc(count, size);
}
void *__wrap_realloc(void *ptr, size_t size) {
    g_c_allocs++;
    return __real_realloc(ptr, size);
}
}
#endif

void *operator new(std::size_t size) {
    g_cxx_allocs++;
    if (void *p = std::malloc(size == 0u ? 1u : size)) return p;
    throw std::bad_alloc();
}
void operator delete(void *p) noexcept { std::free(p); }
void operator delete(void *p, std::size_t) noexcept { std::free(p); }

extern "C" uint64_t compose_gpu_alloc_count(void) {
    return g_c_allocs + g_cxx_allocs;
}

extern "C" int compose_gpu_alloc_counting(void) { return MYCOMPOSE_ALLOC_WRAP; }

static int g_fail = 0;
#define CHECK(cond, ...) do { if (!(cond)) { \
    std::printf("FAIL %s:%d: ", __FILE__, __LINE__); std::printf(__VA_ARGS__); \
    std::printf("\n"); g_fail++; } } while (0)

namespace {

constexpr uint32_t kIntentClickItem = 1u;
constexpr uint32_t kIntentToggleLang = 2u;
constexpr uint32_t kIntentReorder = 3u;
constexpr uint32_t kIntentTextChanged = 4u;
constexpr uint32_t kItems = 3u;

/* The UI language and the list order are State. The view reads them; the
 * reducer only writes State and never calls break_editor_i18n_set_lang. */
struct ComposeState {
    BreakEditorLang lang;
    uint32_t order[kItems];
    uint32_t clicks[kItems];
    uint32_t text_changes;
    uint32_t reduced;
};

const char *const kItemKeys[kItems] = {"item_a", "item_b", "item_c"};
const char *const kItemText[kItems] = {"A", "B", "C"};
const uint32_t kItemColor[kItems] = {0xD02020FFu, 0x20B020FFu, 0x2040D0FFu};
const uint32_t kItemPayload[kItems] = {0u, 1u, 2u};

MyComposeStatus reduce(void *, const MyComposeIntent *intent,
    const void *current, uint32_t current_size, void *candidate,
    uint32_t *candidate_size, MyComposeEffectBatch *) {
    if (intent == nullptr || current_size != sizeof(ComposeState) ||
        candidate_size == nullptr || *candidate_size < sizeof(ComposeState)) {
        return MY_COMPOSE_INVALID;
    }
    ComposeState next;
    std::memcpy(&next, current, sizeof(next));
    switch (intent->type) {
        case kIntentClickItem: {
            uint32_t id = 0u;
            if (intent->payload_size != sizeof(id)) return MY_COMPOSE_INVALID;
            std::memcpy(&id, intent->payload, sizeof(id));
            if (id >= kItems) return MY_COMPOSE_INVALID;
            next.clicks[id]++;
            break;
        }
        case kIntentToggleLang:
            next.lang = next.lang == BREAK_EDITOR_LANG_EN_US
                ? BREAK_EDITOR_LANG_ZH_CN : BREAK_EDITOR_LANG_EN_US;
            break;
        case kIntentReorder: {
            const uint32_t first = next.order[0];
            for (uint32_t i = 0u; i + 1u < kItems; ++i) next.order[i] = next.order[i + 1u];
            next.order[kItems - 1u] = first;
            break;
        }
        case kIntentTextChanged:
            next.text_changes++;
            break;
        default:
            return MY_COMPOSE_INVALID;
    }
    next.reduced++;
    std::memcpy(candidate, &next, sizeof(next));
    *candidate_size = sizeof(next);
    return MY_COMPOSE_OK;
}

MyComposeStatus execute(void *, const MyComposeEffect *) { return MY_COMPOSE_OK; }

struct ViewOut {
    MyComposeNodeHandle row;
    MyComposeNodeHandle items[kItems];
    MyComposeNodeHandle lang;
    MyComposeNodeHandle reorder;
    MyComposeNodeHandle edit;
    MyComposeNodeHandle title;
    uint32_t renders;
};

MyComposeValue i32_value(int32_t v) {
    MyComposeValue value{};
    value.type = MY_COMPOSE_VALUE_INT32;
    value.as.int32_value = v;
    return value;
}

MyComposeValue str_value(const char *s) {
    MyComposeValue value{};
    value.type = MY_COMPOSE_VALUE_STRING;
    value.as.string.data = s;
    value.as.string.size = static_cast<uint32_t>(std::strlen(s));
    return value;
}

MyComposeValue color_value(uint32_t rgba) {
    MyComposeValue value{};
    value.type = MY_COMPOSE_VALUE_COLOR;
    value.as.color = rgba;
    return value;
}

struct ViewBuilder {
    MyComposeTreeBuilder *b;
    MyComposeStatus status = MY_COMPOSE_OK;

    MyComposeNodeHandle Node(MyComposeNodeHandle parent, const char *key,
        const char *type) {
        MyComposeNodeHandle out{};
        if (status != MY_COMPOSE_OK) return out;
        MyComposeNodeDesc desc{};
        desc.parent = parent;
        desc.key = key;
        desc.type = type;
        status = my_compose_tree_builder_node(b, &desc, &out);
        return out;
    }
    void Prop(MyComposeNodeHandle n, const char *name, const MyComposeValue &v) {
        if (status == MY_COMPOSE_OK) status = my_compose_tree_builder_property(b, n, name, &v);
    }
    void Rect(MyComposeNodeHandle n, int32_t x, int32_t y, int32_t w, int32_t h) {
        Prop(n, "x", i32_value(x));
        Prop(n, "y", i32_value(y));
        Prop(n, "w", i32_value(w));
        Prop(n, "h", i32_value(h));
    }
    void Event(MyComposeNodeHandle n, const char *name, uint32_t type,
        const uint32_t *payload) {
        if (status != MY_COMPOSE_OK) return;
        MyComposeIntent intent{};
        intent.type = type;
        if (payload != nullptr) {
            intent.payload = reinterpret_cast<const uint8_t *>(payload);
            intent.payload_size = sizeof(*payload);
        }
        status = my_compose_tree_builder_event(b, n, name, &intent);
    }
};

/* Logical layout inside the adapter root. */
constexpr int32_t kItemW = 70, kRowH = 40;

MyComposeStatus view(void *context, MyComposeTreeBuilder *b,
    const void *raw_state, uint32_t size) {
    ViewOut *out = static_cast<ViewOut *>(context);
    if (size != sizeof(ComposeState)) return MY_COMPOSE_INVALID;
    const ComposeState *state = static_cast<const ComposeState *>(raw_state);
    const BreakEditorLang lang = state->lang;
    ViewBuilder v{b};
    const MyComposeNodeHandle root = v.Node(MyComposeNodeHandle{}, nullptr, "@root");
    out->row = v.Node(root, "row", "@row");
    v.Rect(out->row, 10, 10, kItemW * static_cast<int32_t>(kItems), kRowH);
    for (uint32_t slot = 0u; slot < kItems; ++slot) {
        const uint32_t id = state->order[slot];
        const MyComposeNodeHandle item = v.Node(out->row, kItemKeys[id], "button");
        v.Prop(item, "layout", str_value("w:70"));
        v.Prop(item, "text", str_value(kItemText[id]));
        v.Prop(item, "style:bg_color", color_value(kItemColor[id]));
        v.Event(item, "click", kIntentClickItem, &kItemPayload[id]);
        out->items[id] = item;
    }
    out->lang = v.Node(root, "lang", "button");
    v.Rect(out->lang, 10, 60, 150, 40);
    v.Prop(out->lang, "text", str_value(break_editor_tr_lang(lang, BREAK_EDITOR_TR_ADD)));
    v.Event(out->lang, "click", kIntentToggleLang, nullptr);
    out->reorder = v.Node(root, "reorder", "button");
    v.Rect(out->reorder, 170, 60, 150, 40);
    v.Prop(out->reorder, "text",
        str_value(break_editor_tr_lang(lang, BREAK_EDITOR_TR_TOOL_ROTATE)));
    v.Event(out->reorder, "click", kIntentReorder, nullptr);
    out->edit = v.Node(root, "edit", "edit");
    v.Rect(out->edit, 10, 110, 310, 36);
    v.Prop(out->edit, "hint",
        str_value(break_editor_tr_lang(lang, BREAK_EDITOR_TR_ENTITY_NAME_HINT)));
    v.Event(out->edit, "changed", kIntentTextChanged, nullptr);
    /* label.text has no transactional capture hook, so the adapter rejects
     * it with NOT_SUPPORTED; the title is a button with a flat style. */
    out->title = v.Node(root, "title", "button");
    v.Rect(out->title, 10, 160, 310, 40);
    v.Prop(out->title, "text", str_value(break_editor_tr_lang(lang, BREAK_EDITOR_TR_OUTLINER)));
    v.Prop(out->title, "style:bg_color", color_value(0xFFFFFFFFu));
    v.Prop(out->title, "style:fg_color", color_value(0x000000FFu));
    v.Prop(out->title, "style:font_size", i32_value(24));
    v.Prop(out->title, "style:border_width", i32_value(0));
    if (v.status == MY_COMPOSE_OK) out->renders++;
    return v.status;
}

const ComposeState *state_of(MyComposeStore *store) {
    const void *raw = nullptr;
    uint32_t size = 0u;
    if (my_compose_store_state(store, &raw, &size) != MY_COMPOSE_OK ||
        size != sizeof(ComposeState)) {
        return nullptr;
    }
    return static_cast<const ComposeState *>(raw);
}

} // namespace

namespace {

struct PhaseAllocs {
    uint64_t compose = UINT64_MAX;
    uint64_t myui = UINT64_MAX;
};

/* One click Intent per frame, so reduce/view/diff/stage/finalize/commit
 * all run inside my_compose_myui_pump on every measured frame. */
PhaseAllocs phase_allocs(ComposeGpu *gpu, MyComposeStore *store, unsigned count) {
    PhaseAllocs out;
    ComposeGpuCounters before{}, after{};
    compose_gpu_counters(gpu, &before);
    for (unsigned i = 0u; i < count; ++i) {
        MyComposeIntent intent{};
        intent.type = kIntentClickItem;
        intent.payload = reinterpret_cast<const uint8_t *>(&kItemPayload[1]);
        intent.payload_size = sizeof(kItemPayload[1]);
        if (my_compose_store_dispatch(store, &intent) != MY_COMPOSE_OK ||
            compose_gpu_frame(gpu, nullptr, nullptr, 0, nullptr) != 0) {
            return PhaseAllocs{};
        }
    }
    compose_gpu_counters(gpu, &after);
    out.compose = after.compose_allocs - before.compose_allocs;
    out.myui = after.myui_allocs - before.myui_allocs;
    return out;
}

/* C++ DSL hot path: Builder/NodeScope/Property/OnClick/Finalize over the
 * same keyed shape, after warm-up. */
uint64_t dsl_allocs(unsigned warm, unsigned measured) {
    auto builder = compose::Builder::Create();
    if (!builder.has_value()) return UINT64_MAX;
    uint64_t before = 0u;
    for (unsigned i = 0u; i < warm + measured; ++i) {
        if (i == warm) before = compose_gpu_alloc_count();
        if (builder->Begin() != MY_COMPOSE_OK) return UINT64_MAX;
        {
            auto root = builder->Node("@root");
            auto row = root.Row("row");
            for (uint32_t k = 0u; k < kItems; ++k) {
                const uint32_t id = (k + i) % kItems;
                auto item = row.Element(kItemKeys[id], "button");
                (void)item.Property("text", kItemText[id])
                    .Style("bg_color", color_value(kItemColor[id]))
                    .OnClick(compose::Intent{.type = kIntentClickItem});
            }
        }
        if (builder->End() != MY_COMPOSE_OK || builder->Finalize() != MY_COMPOSE_OK) {
            return UINT64_MAX;
        }
    }
    return compose_gpu_alloc_count() - before;
}

bool font_path(const char *rel, char *out, size_t cap) {
    const char *env = std::getenv("BREAK_ASSET_DIR");
    if (env != nullptr && env[0] != '\0') {
        std::snprintf(out, cap, "%s/assets/fonts/%s", env, rel);
    } else {
        std::snprintf(out, cap, "assets/fonts/%s", rel);
    }
    FILE *f = std::fopen(out, "rb");
    if (f == nullptr) return false;
    std::fclose(f);
    return true;
}

} // namespace

int main(void) {
    const bool vulkan = MYCOMPOSE_GPU_VULKAN != 0;
    const char *backend = vulkan ? "vulkan" : "opengl";
    const char *evidence = "SYNTHETIC_INPUTSTATE+DIRECT_DISPATCH";
    std::printf("compose-gpu: backend=%s evidence=%s\n", backend, evidence);
    char mono[768], cjk[768];
    CHECK(font_path("JetBrainsMono-Regular.ttf", mono, sizeof(mono)),
        "missing bundled font assets/fonts/JetBrainsMono-Regular.ttf");
    CHECK(font_path("NotoSansSC-VF.ttf", cjk, sizeof(cjk)),
        "missing bundled font assets/fonts/NotoSansSC-VF.ttf");
    if (g_fail != 0) return 1;

    ComposeGpu *gpu = nullptr;
    ComposeGpuDevice device{};
    ComposeGpuFonts fonts{};
    const int opened = compose_gpu_open(&gpu, MYCOMPOSE_GPU_BACKEND, mono, cjk, &device, &fonts);
    if (opened == 77) return 77;
    CHECK(opened == 0, "compose_gpu_open returned %d", opened);
    if (g_fail != 0) {
        compose_gpu_close(gpu);
        return 1;
    }
    std::printf("device: backend=%s name=\"%s\" vendor=0x%x device=0x%x type=%s "
                "api=%u driver=%u\n",
        backend, device.name, device.vendor_id, device.device_id,
        device.device_type_name != nullptr ? device.device_type_name : "?",
        device.api_version, device.driver_version);
    {
        const char *require = std::getenv("MYCOMPOSE_GPU_REQUIRE_HARDWARE");
        const int hardware = compose_gpu_device_is_hardware(&device);
        std::printf("device_class: %s\n", hardware ? "hardware-gpu" : "software");
        if (require != nullptr && require[0] != '\0' && require[0] != '0' && !hardware) {
            std::printf("FAIL: MYCOMPOSE_GPU_REQUIRE_HARDWARE set, device \"%s\" type=%s "
                        "is not a GPU\n",
                device.name, device.device_type_name != nullptr ? device.device_type_name : "?");
            compose_gpu_close(gpu);
            return 1;
        }
    }
    std::printf("fonts: JetBrainsMono 'A'=%dx%d NotoSansSC U+5927=%dx%d "
                "chain_uses_cjk=%d (both loaded)\n",
        fonts.mono_w, fonts.mono_h, fonts.cjk_w, fonts.cjk_h, fonts.chain_uses_cjk);

    ComposeState initial{};
    initial.lang = BREAK_EDITOR_LANG_EN_US;
    initial.order[0] = 0u;
    initial.order[1] = 1u;
    initial.order[2] = 2u;
    MyComposeStore *store = my_compose_store_create(&initial, sizeof(initial), nullptr,
        nullptr, reduce, nullptr, execute);
    ViewOut out{};
    CHECK(store != nullptr && compose_gpu_bind(gpu, store, view, &out) == 0,
        "compose bind failed");
    if (g_fail != 0) return 1;

    CHECK(compose_gpu_settle(gpu, 2u) == 0, "initial settle failed");
    const ComposeState *st = state_of(store);
    CHECK(st != nullptr && st->lang == BREAK_EDITOR_LANG_EN_US, "initial lang");
    CHECK(break_editor_i18n_lang() == BREAK_EDITOR_LANG_EN_US,
        "reducer must not touch the process-wide editor language");
    char text[128];
    CHECK(compose_gpu_text(gpu, out.title, text, sizeof(text)) == 0 &&
        std::strcmp(text, "Outliner") == 0, "en title '%s'", text);
    CHECK(compose_gpu_text(gpu, out.lang, text, sizeof(text)) == 0 &&
        std::strcmp(text, "Add") == 0, "en button '%s'", text);
    ComposeGpuRect rect{};
    CHECK(compose_gpu_rect(gpu, out.title, &rect) == 0, "title rect");
    ComposeGpuRegion title_en = compose_gpu_inspect(gpu, rect, 0xFFFFFFFFu, 24);
    CHECK(title_en.total > 100u && title_en.match * 100u / title_en.total >= 70u,
        "title coverage %u/%u", title_en.match, title_en.total);
    CHECK(title_en.dark >= 8u, "title text ink %u", title_en.dark);

    CHECK(compose_gpu_click(gpu, out.lang) == 0, "lang click");
    st = state_of(store);
    CHECK(st->lang == BREAK_EDITOR_LANG_ZH_CN && st->clicks[0] == 0u, "lang state");
    CHECK(break_editor_i18n_lang() == BREAK_EDITOR_LANG_EN_US, "global lang leaked");
    CHECK(compose_gpu_text(gpu, out.title, text, sizeof(text)) == 0 &&
        std::strcmp(text, "大纲") == 0, "zh title '%s'", text);
    CHECK(compose_gpu_rect(gpu, out.title, &rect) == 0, "zh title rect");
    ComposeGpuRegion title_zh = compose_gpu_inspect(gpu, rect, 0xFFFFFFFFu, 24);
    CHECK(title_zh.dark >= 8u, "zh title ink %u", title_zh.dark);
    CHECK(title_zh.signature != title_en.signature,
        "language switch did not change the rendered text");

    ComposeGpuRect before{};
    CHECK(compose_gpu_rect(gpu, out.items[0], &before) == 0, "item A rect");
    const void *item_a = compose_gpu_widget(gpu, out.items[0]);
    ComposeGpuRegion red_before = compose_gpu_inspect(gpu, before, kItemColor[0], 32);
    CHECK(red_before.total > 100u && red_before.match * 100u / red_before.total >= 60u,
        "item A red coverage %u/%u", red_before.match, red_before.total);
    CHECK(compose_gpu_click(gpu, out.reorder) == 0, "reorder click");
    ComposeGpuRect after{};
    CHECK(compose_gpu_rect(gpu, out.items[0], &after) == 0, "item A rect after");
    CHECK(after.x != before.x, "keyed reorder did not move item A (%d -> %d)",
        before.x, after.x);
    CHECK(compose_gpu_widget(gpu, out.items[0]) == item_a,
        "keyed reorder changed the widget identity");
    ComposeGpuRegion red_after = compose_gpu_inspect(gpu, after, kItemColor[0], 32);
    CHECK(red_after.total > 0u && red_after.match * 100u / red_after.total >= 60u,
        "item A lost its colour after reorder");

    CHECK(compose_gpu_click(gpu, out.edit) == 0, "edit click");
    CHECK(compose_gpu_focused(gpu, out.edit) != 0, "edit did not take focus");
    CHECK(compose_gpu_text(gpu, out.edit, text, sizeof(text)) == 0 && text[0] == '\0',
        "edit starts empty");
    CHECK(compose_gpu_frame(gpu, nullptr, "你好", 0, nullptr) == 0, "direct commit frame");
    CHECK(compose_gpu_settle(gpu, 2u) == 0, "post-commit settle");
    CHECK(compose_gpu_text(gpu, out.edit, text, sizeof(text)) == 0 &&
        std::strcmp(text, "你好") == 0, "direct IME commit text '%s'", text);
    CHECK(state_of(store)->text_changes == 1u, "changed intent count");
    CHECK(compose_gpu_rect(gpu, out.edit, &rect) == 0, "edit rect");
    ComposeGpuRegion edit_region = compose_gpu_inspect(gpu, rect, 0xFFFFFFFFu, 48);
    CHECK(edit_region.dark >= 4u, "committed text ink %u", edit_region.dark);

    /* Negative case: an IME commit while the edit is not focused must not
     * change the text, and the platform text queue stays empty either way. */
    CHECK(compose_gpu_tap_key(gpu, 259) == 0, "tab");
    CHECK(compose_gpu_focused(gpu, out.edit) == 0, "edit still focused after tab");
    CHECK(compose_gpu_frame(gpu, nullptr, "ZZ", 0, nullptr) == 0, "unfocused commit");
    CHECK(compose_gpu_settle(gpu, 1u) == 0, "negative settle");
    CHECK(compose_gpu_text(gpu, out.edit, text, sizeof(text)) == 0 &&
        std::strcmp(text, "你好") == 0, "unfocused direct commit changed the edit");

    CHECK(compose_gpu_click(gpu, out.items[2]) == 0, "item click");
    CHECK(state_of(store)->clicks[2] == 1u, "click intent reached the store");

    (void)phase_allocs(gpu, store, 4u); /* warm-up */
    const PhaseAllocs hot = phase_allocs(gpu, store, 8u);
    const uint64_t dsl = dsl_allocs(4u, 16u);
    const int counting = compose_gpu_alloc_counting();
    std::printf("allocations: counting=%d compose_pump=%llu (8 frames) "
                "cxx_dsl=%llu (16 builds) myui_pump_render=%llu (separate, not asserted)\n",
        counting, static_cast<unsigned long long>(hot.compose),
        static_cast<unsigned long long>(dsl), static_cast<unsigned long long>(hot.myui));
    CHECK(hot.compose == 0u, "Compose pump allocated %llu times after warm-up",
        static_cast<unsigned long long>(hot.compose));
    CHECK(dsl == 0u, "C++ DSL allocated %llu times after warm-up",
        static_cast<unsigned long long>(dsl));
    CHECK(state_of(store)->clicks[1] == 12u, "hot-path intents reduced");
    const uint64_t idle_allocs = hot.compose;

    char shot_path[256];
    const char *out_dir = std::getenv("MYCOMPOSE_GPU_OUT_DIR");
    std::snprintf(shot_path, sizeof(shot_path), "%s%scompose_gpu_%s.ppm",
        out_dir != nullptr ? out_dir : "", out_dir != nullptr ? "/" : "", backend);
    CHECK(compose_gpu_write_ppm(gpu, shot_path) == 0, "ppm");
    ComposeGpuCounters counters{};
    compose_gpu_counters(gpu, &counters);
    CHECK(counters.queue_text_events == 0u,
        "platform text queue delivered %u events; direct dispatch would be mislabelled",
        counters.queue_text_events);
    const uint32_t validation = compose_gpu_vk_validation_messages();
    CHECK(!vulkan || validation == 0u, "VK VALIDATION messages: %u", validation);
    std::printf("frames=%u rendered=%u skipped=%u shots=%u presents=%u "
                "synthetic_pointer=%u synthetic_key=%u direct_text=%u queue_text=%u "
                "vk_validation=%u idle_allocs=%llu shot=%s\n",
        counters.frames, counters.rendered, counters.skipped, counters.shots,
        counters.presents, counters.synthetic_pointer_edges, counters.synthetic_key_edges,
        counters.direct_text_commits, counters.queue_text_events, validation,
        static_cast<unsigned long long>(idle_allocs), shot_path);
    std::printf("evidence: backend=%s device=\"%s\" type=%s input=%s "
                "(not compositor-injected; software devices are not hardware GPU evidence)\n",
        backend, device.name, device.device_type_name != nullptr ? device.device_type_name : "?",
        evidence);
    compose_gpu_close(gpu);
    my_compose_store_destroy(store);
    std::printf("%s\n", g_fail == 0 ? "compose-gpu: PASS" : "compose-gpu: FAIL");
    return g_fail == 0 ? 0 : 1;
}
