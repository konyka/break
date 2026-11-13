# Compose + MVI（myui 声明式 UI）

本文是 `engine/src/myui/mycompose`（C11 核心）、`mycompose_myui`（myui adapter）与 `my_compose.hpp`（C++20 DSL）的当前使用说明。设计取舍见 `docs/superpowers/specs/2026-11-11-compose-mvi-design.md`，逐任务证据见 `docs/Implementation_Status.md`。

## 分层与 CMake target

| target | 内容 | 依赖 |
|---|---|---|
| `mycompose` | 描述树/keyed diff、remember、Store、Runtime（C11） | Threads |
| `mycompose_myui` | myui sink：stage/commit/rollback、listener、async bridge | `mycompose`、`myui_core` |
| `mycompose_cpp20` | header-only `breakxx::compose` DSL | `mycompose` |

`mycompose` 不链接 myui 或 RHI。应用在 `break_ui_pump()` 之后显式调用 `my_compose_myui_pump()`，BreakUI ABI 不变。

## 帧顺序

生产路径每帧：

```
platform_poll → break_ui_pump → my_compose_myui_pump → break_ui_frame_begin
→ break_ui_render → rhi_frame_end → (rhi_screenshot) → rhi_present
```

`my_compose_myui_pump` 内部对每个 State revision 固定执行：

```
reaper → reduce → view → tree.end → sink.stage → tree.finalize → sink.commit → dispatch_effects
```

`sink.stage → tree.finalize → sink.commit` 是唯一结构发布顺序。tree finalize 独占 remember dispose 与节点 generation；adapter commit 只处理 listener lease、owner 表、removed notify、widget unref 与快照，绝不再 dispose remember。

## C 示例

```c
static MyComposeStatus view(void *ctx, MyComposeTreeBuilder *b,
                            const void *raw, uint32_t size) {
    const AppState *s = raw;            /* size == sizeof(AppState) */
    MyComposeNodeDesc d = {0};
    MyComposeNodeHandle root, add;
    MyComposeValue text = {.type = MY_COMPOSE_VALUE_STRING};
    MyComposeIntent click = {.type = INTENT_ADD};
    d.type = "@root";
    if (my_compose_tree_builder_node(b, &d, &root) != MY_COMPOSE_OK) return MY_COMPOSE_FAILED;
    d.parent = root; d.key = "add"; d.type = "button";
    if (my_compose_tree_builder_node(b, &d, &add) != MY_COMPOSE_OK) return MY_COMPOSE_FAILED;
    text.as.string.data = break_editor_tr_lang(s->lang, BREAK_EDITOR_TR_ADD);
    text.as.string.size = (uint32_t)strlen(text.as.string.data);
    (void)my_compose_tree_builder_property(b, add, "text", &text);
    return my_compose_tree_builder_event(b, add, "click", &click);
}

MyComposeStore *store = my_compose_store_create(&initial, sizeof initial, NULL,
                                                NULL, reduce, NULL, execute);
MyComposeTreeBuilder *builder = my_compose_tree_builder_create();
MyComposeMyui *adapter = my_compose_myui_create(window, builder, store);
MyComposeRuntimeConfig cfg = {.store = store, .view = view,
                              .sink = my_compose_myui_sink(adapter)};
MyComposeRuntime *rt = my_compose_runtime_create(builder, &cfg);
/* 每帧，在 break_ui_pump 之后： */
(void)my_compose_myui_pump(adapter, rt);
/* 销毁顺序（UI 线程）：Runtime → adapter → builder → Store。 */
```

reducer 签名为 `(ctx, intent, current, current_size, candidate, &candidate_size, batch)`：只读 `current`，写 `candidate`，Effect 只能经 `my_compose_effect_batch_append` 加入，不做 I/O。

## C++20 示例

```cpp
namespace compose = breakxx::compose;
auto store = compose::Store<AppState>::Create(AppState{},
    [](const AppState &cur, AppState &next, const compose::Intent &in,
       compose::EffectBatch &) {
        next = cur;
        if (in.type == kToggleLang) next.lang = Toggle(cur.lang);
        return MY_COMPOSE_OK;
    });
if (!store.has_value()) return;
auto runtime = compose::Runtime::Create(*store,
    [](compose::Builder &b, const AppState &s) {
        auto root = b.Node("@root");
        auto row = root.Row("row");
        for (uint32_t id : s.order) {
            auto item = row.Element(kKeys[id], "button");
            (void)item.Property("text", kText[id])
                .OnClick(compose::Intent{.type = kClick});
        }
        return b.Status();
    }, my_compose_myui_sink(adapter));
if (!runtime.has_value()) return;
(void)runtime->Pump();  /* 每帧在 break_ui_pump 之后调用 */
```

C++ 对象均为 move-only RAII；callback 异常在 trampoline 内变为 `MY_COMPOSE_FAILED`，不跨 C ABI。无异常构建要求 callback `noexcept`。

## 固定容量

所有上限都是编译期常量（`my_compose.h`、`my_compose_remember.h`），超限返回 `MY_COMPOSE_OVERLOAD`，不静默截断。

| 资源 | 上限 | 常量 |
|---|---|---|
| 节点 / 子链接 / 深度 | 256 / 255 / 32 | `MY_COMPOSE_MAX_NODES`、`_MAX_CHILD_LINKS`、`_MAX_DEPTH` |
| 属性（总 / 每节点） | 512 / 64 | `_MAX_PROPERTIES`、`_MAX_PROPERTIES_PER_NODE` |
| 事件（总 / 每节点） | 256 / 32 | `_MAX_EVENTS`、`_MAX_EVENTS_PER_NODE` |
| diff 操作 | 1024 | `_MAX_DIFF_OPS` |
| remember | 64 槽 × 256 字节，每节点 4 槽 | `_MAX_REMEMBER_SLOTS`、`_REMEMBER_BYTES`、`_REMEMBER_SLOTS_PER_NODE` |
| 字符串 arena / State | 64 KiB / 16 KiB | `_STRING_BYTES`、`_STATE_BYTES` |
| Intent 队列 / request slot / completion | 64 / 32 / 32 | `_INTENT_CAPACITY`、`_EFFECT_CAPACITY`、`_COMPLETION_CAPACITY` |
| 消息 payload / 每 Intent Effect | 256 字节 / 8 | `_MESSAGE_BYTES`、`_MAX_EFFECTS_PER_INTENT` |
| key / type / name | 64 字节 | `_KEY_BYTES`、`_TYPE_BYTES`、`_NAME_BYTES` |

node/store generation 到 `UINT32_MAX` 时退休该 slot 或返回 `OVERLOAD`；request id 到 `UINT64_MAX` 返回 `OVERLOAD`，均不回绕。C++ 侧以 `kMaxDepth`、`kMaxRememberSlots`、`kMaxStateBytes`、`kMaxEffectsPerIntent` 暴露同一组值，`State` 超过 16 KiB 时 `static_assert` 失败。

## 节点身份

keyed 节点身份为 `(parent, key, type)`；unkeyed 节点按其在直接父节点下的绝对位置。同一 key 换 type 视为替换（DELETE 旧节点、CREATE 新节点）；跨 parent 不保留身份。同 parent 内的 keyed 重排产生 MOVE，不会退化为 DELETE+CREATE，因此 widget、focus 与 remember 状态随节点移动。

## MVI 原子边界

reducer 只读 `current`、写 `candidate`，不做 I/O。State 发布前预检 `outbox + outstanding + 本批 Effect <= 32`（outbox 与 outstanding 共用 32 个 request slot）；预检失败或 reducer 失败时，原 State、outbox、outstanding 与 Intent FIFO 全部不变。executor 返回 OK 后只做不会失败的 outbox → outstanding 移动。

listener 写入的 owner 是当前节点；reducer 运行前再次核对 owner，过期节点的事件不进入 reducer。事件回调只 enqueue Intent，worker 不直接访问 Store 或 myui。
## pending-view

view、tree 或 stage 失败时保留已提交的新 State 和最后一次有效 UI，并设置 pending-view。恢复之前不 reduce 新 Intent、不转换 completion、不 dispatch Effect；下一次 pump 先运行 reaper，再对同一 State revision 重建 view，成功后才 dispatch 旧 outbox 并继续消费 FIFO。stage detach 不调用 removed hook，只有 commit 才 notify；回滚不提前清理 focus、grab、IME 或 selection。

## Effect 与 completion

executor 返回 PENDING 时 Effect 留在 outbox，下次 pump 重试，request id 不变、不重复执行。completion 归 Store 拥有的 async bridge：32 个预分配 context，各带原子状态（PENDING/ACCEPTING/ACCEPTED/RETRY/CANCELLED/STALE）与引用计数。completion 携带进程内单调的 64 位 `store_id`、request id、generation 与 owner；任一项不匹配即为 STALE，不修改 State。completion 队列满时写 OVERLOAD 并回到 RETRY，不消费 outstanding。

## lease 与销毁

Runtime 不拥有 Store 和 sink。worker 和 UI command 只持 completion 引用和 lease，不持裸 Store/Runtime 指针；UI 回调经 lease 取 Store，lease 失效即放弃。销毁顺序在 UI 线程：Runtime → adapter → builder → Store。window close 和 Runtime destroy 都先失效 lease、关闭 scope、推进代际，再幂等 close + reaper；Store 销毁后 bridge 仍等最后一个 worker/UI command 释放。

## I18N 与 IME

语言是 State 的一部分（例如 `BreakEditorLang lang`）。view 用 `break_editor_tr_lang(lang, key)` 取文本；reducer 只改 `lang` 字段，不调用全局 `break_editor_i18n_set_lang`。切换语言是一次普通的 Intent → reduce → view → diff，只更新受影响的 `text` 属性。

文本输入沿用 myui edit 的 IME 路径：pointer-down 使 edit 获得 focus 并启用 IME，提交文本以 `MY_EVENT_IME_COMMIT` 到达；IME 启用时可打印按键被抑制。中文显示依赖字体链同时含 `JetBrainsMono-Regular.ttf` 与 `NotoSansSC-VF.ttf`。

## myui 边界

Compose 只通过 `mycompose_myui` sink 操作 myui，应用不应再直接修改由 Compose 管理的 widget。adapter 支持 button、edit、Row/Column/Stack 等内置类型；`label.text` 当前没有事务捕获钩子，adapter 返回 `MY_COMPOSE_NOT_SUPPORTED`，需要可回滚文本的位置用 button 代替。root 绑定按 `state->root` 比较，因为 root widget 的实际父节点是 CSD 容器。

## 验证与证据等级

| CTest | 内容 | 证据等级 |
|---|---|---|
| `test_mycompose_tree/remember/store/runtime/async/myui` | C11 核心与 adapter | CPU，dummy/headless PAL |
| `test_mycompose_cpp20*`（4 项） | C++20 DSL、C parity、头文件自包含、无异常 | CPU |
| `test_mycompose_gpu_vulkan` | 真实 Wayland 窗口 + Vulkan 设备、截图像素与 State | 本机 Intel UHD (TGL GT1) 为硬件 GPU 证据 |
| `test_mycompose_gpu_opengl` | 同一 fixture 的 OpenGL 对照 | 本机 `Mesa Intel(R) UHD Graphics (TGL GT1)`；`RHIDeviceInfo` 报告 `GL_RENDERER`，类型为 OTHER（GL 无设备类型查询）；llvmpipe/softpipe/SwiftShader 报告为 CPU，其它平台的软件 GL（GDI Generic、WARP、Apple Software Renderer）目前也会显示为 OTHER |
| `fuzz_mycompose_tree_smoke`、`fuzz_mycompose_intent_smoke` | 长度前缀 node/property/intent 流 | 健壮性，不替代行为断言 |

GPU 测试的输入不是合成器注入：pointer/key 为 `SYNTHETIC_INPUTSTATE`（在 `platform_poll` 之后、`break_ui_pump` 之前写入 `InputState`），文本为 `DIRECT_DISPATCH`（直接派发 `MY_EVENT_IME_COMMIT`），并断言 `platform_poll_text` 为空；另有未聚焦 edit 的提交不改变文本的负例。像素断言只比较关键区域颜色与覆盖率，不做跨硬件整帧逐字节比较。无 Wayland 显示或设备时退出 77；CI 的 lavapipe/llvmpipe 运行是软件渲染，不是硬件 GPU 证据。

预热后的分配计数：`my_compose_myui_pump` 8 帧 0 次、C++ DSL 16 次构建 0 次；myui 自身 pump/render 的分配单独打印，不计入新层断言。
