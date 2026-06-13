# Break Engine 核心模块详解

本文档详细描述 Break Engine 各模块的职责、核心接口、数据结构及模块间关系。引擎采用纯 C 编写（C11 标准），模块化设计，通过头文件暴露最小化接口。

---

## 1. Core 基础设施 (`engine/src/core/`)

核心模块为整个引擎提供底层原语，所有其他模块均依赖此模块。

### 1.1 类型系统 (`types.h`)

定义统一的固定宽度类型别名，避免平台差异：

```c
typedef float  f32;
typedef double f64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef size_t    usize;
typedef ptrdiff_t isize;
```

**设计意图**：所有模块统一使用这些类型，保证跨平台一致性，杜绝隐式宽度假设。

### 1.2 内存管理 (`alloc.h` / `alloc.c`)

#### 三层分级分配器

| 分配器 | 用途 | 性能 |
|--------|------|------|
| **Heap Allocator** | 通用分配，包装 `malloc/free` | 冷路径，vtable 间接调用 |
| **Arena Allocator** | 帧/阶段级批量分配，线性增长 | 热路径，内联零开销 |
| **Debug Allocator** | 包装任意分配器，跟踪峰值/泄漏 | 仅调试构建 |

#### vtable 接口设计

```c
struct Alloc {
    void *(*alloc)(Alloc *self, usize size, usize align);
    void  (*free)(Alloc *self, void *ptr, usize size);
    void *(*realloc)(Alloc *self, void *ptr, usize old_size, usize new_size, usize align);
};
```

所有分配器共享此接口，可在运行时替换，支持依赖注入。

#### 类型安全宏

```c
#define alloc_new(a, T)        ((T *)(a)->alloc((a), sizeof(T), alignof(T)))
#define alloc_array(a, T, n)   ((T *)(a)->alloc((a), sizeof(T) * (n), alignof(T)))
#define alloc_free(a, p, T)    ((a)->free((a), (p), sizeof(T)))
#define alloc_free_array(a, p, T, n) ((a)->free((a), (p), sizeof(T) * (n)))
```

#### Arena 使用示例

```c
// 初始化 Arena（使用外部缓冲区，零堆分配）
u8 buffer[1024 * 1024]; // 1MB 栈/静态缓冲
Arena arena;
arena_init(&arena, buffer, sizeof(buffer));

// 通过 Alloc 接口分配
Alloc *a = &arena.base;
Vec3 *positions = alloc_array(a, Vec3, 1000);

// 帧末尾一次性释放所有
arena_free_all(&arena);
```

#### 模块关系
- 被所有模块依赖
- Debug Allocator 可包装任意分配器用于泄漏检测

**单元测试：** `tests/test_alloc.c` (15 测试用例，覆盖 Heap/Arena/Debug 分配器、NULL 安全、零大小分配、重分配)

覆盖：Heap alloc/free/realloc/alignment、Arena basic/free_all/overflow/alignment/realloc、DebugAlloc 跟踪。

### 1.3 日志系统 (`log.h` / `log.c`)

#### 6 级日志

```c
typedef enum {
    LOG_TRACE,  // 最详细追踪信息
    LOG_DEBUG,  // 调试信息
    LOG_INFO,   // 常规运行信息
    LOG_WARN,   // 非致命警告
    LOG_ERROR,  // 可恢复错误
    LOG_FATAL,  // 不可恢复，通常触发退出
} LogLevel;
```

#### 基于文件行号的宏封装

```c
// 自动注入 __FILE__ 和 __LINE__
#define LOG_TRACE(...) log_write(LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_DEBUG(...) log_write(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...)  log_write(LOG_INFO,  __FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARN(...)  log_write(LOG_WARN,  __FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) log_write(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_FATAL(...) log_write(LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)
```

#### 核心 API

```c
void log_set_level(LogLevel level);  // 设置最低输出级别（默认 LOG_INFO）
void log_write(LogLevel level, const char *file, int line, const char *fmt, ...);
```

#### 模块关系
- 被所有模块使用
- 依赖 Core 类型系统

### 1.4 其他核心组件

| 文件 | 职责 |
|------|------|
| `profiler.h/c` | 作用域性能计时器，基于 `time_microseconds()` |

**单元测试：** `tests/test_profiler.c` (13 测试用例，覆盖初始化状态、启用/禁用、帧环形缓冲区、溢出环绕、region push/pop、region 溢出钳制、空 pop 安全、计时验证)
| `string.h/c` | 安全字符串操作（copy、format、hash） |

**单元测试：** `tests/test_string.c` (19 测试用例)

覆盖：Str 构造/比较/切片/查找/哈希/复制。
| `assert.h/c` | 条件断言，失败时输出文件/行号并中止 |

---

## 2. Platform 平台抽象层 (`engine/src/platform/`)

将操作系统差异封装在统一接口之后，使上层模块无需关心底层平台细节。

### 2.1 平台接口设计 (`platform.h`)

```c
typedef struct {
    u32 width;
    u32 height;
    const char *title;
} PlatformConfig;

typedef enum {
    PLATFORM_EVENT_NONE,
    PLATFORM_EVENT_QUIT,
} PlatformEventResult;

Platform           *platform_create(const PlatformConfig *cfg);
void                platform_destroy(Platform *p);
PlatformEventResult platform_poll(Platform *p);
InputState         *platform_input(Platform *p);
void               *platform_window_native(Platform *p);   // 返回原生窗口句柄
void               *platform_display_native(Platform *p);  // 返回原生显示连接
void               *platform_surface_native(Platform *p);  // Wayland surface / 其他平台 surface
void                platform_get_size(Platform *p, u32 *w, u32 *h);
void                platform_toggle_fullscreen(Platform *p);

/* 鼠标控制 */
void                platform_mouse_capture(Platform *p, bool capture);
void                platform_mouse_set_visible(Platform *p, bool visible);
void                platform_mouse_set_relative(Platform *p, bool relative);

/* 高 DPI 与多显示器 */
f32                 platform_get_dpi(Platform *p);
i32                 platform_get_scale_factor(Platform *p);
u32                 platform_get_monitor_count(Platform *p);
bool                platform_get_monitor_info(Platform *p, u32 index, MonitorInfo *out);
```

**设计意图**：`platform_window_native` / `platform_display_native` / `platform_surface_native` 返回 `void*`，由 RHI 后端自行转换为具体类型（如 X11 的 `Window`/`Display*`、Wayland 的 `wl_surface*`/`wl_display*`、Win32 的 `HWND`/`HINSTANCE`）。

### 2.2 输入系统 (`input.h` / `input.c`)

```c
#define INPUT_MAX_KEYS        512
#define INPUT_MAX_GAMEPADS    4
#define INPUT_MAX_AXES        6
#define INPUT_MAX_PAD_BUTTONS 16

/* 鼠标按键（复用 keys[] 数组槽位）*/
#define INPUT_MOUSE_LEFT    300
#define INPUT_MOUSE_RIGHT   301
#define INPUT_MOUSE_MIDDLE  302
#define INPUT_MOUSE_4       303  /* 侧键后退 */
#define INPUT_MOUSE_5       304  /* 侧键前进 */

typedef struct {
    f32  axes[INPUT_MAX_AXES];           /* 归一化 -1.0 ~ 1.0 */
    u8   buttons[INPUT_MAX_PAD_BUTTONS]; /* bit0=当前, bit1=上帧 */
    bool connected;
    char name[128];
} GamepadState;

typedef struct {
    u8  keys[INPUT_MAX_KEYS];      // 512 键位状态（bit0=当前, bit1=上帧）
    f32 mouse_x, mouse_y;          // 鼠标绝对位置
    f32 mouse_dx, mouse_dy;        // 鼠标帧间偏移
    f32 scroll_dx, scroll_dy;      // 滚轮偏移
    u64 frame_number;              // 当前帧号
    GamepadState gamepads[INPUT_MAX_GAMEPADS];
} InputState;
```

#### 便捷查询宏

```c
#define input_key_down(s, k)     ((s)->keys[(k)] & 1)       // 当前按下
#define input_key_pressed(s, k)  (((s)->keys[(k)] & 3) == 3) // 本帧刚按下
#define input_key_released(s, k) (((s)->keys[(k)] & 3) == 1) // 本帧刚释放

#define input_pad_button_down(s, p, b)     ((s)->gamepads[(p)].buttons[(b)] & 1)
#define input_pad_button_pressed(s, p, b)  (((s)->gamepads[(p)].buttons[(b)] & 3) == 3)
```

#### 游戏手柄轴与按键常量

按键：`GAMEPAD_BTN_SOUTH/EAST/WEST/NORTH`、`LB/RB`、`BACK/START/GUIDE`、`LSTICK/RSTICK`、`DPAD_UP/DOWN/LEFT/RIGHT`。
轴：`GAMEPAD_AXIS_LEFT_X/Y`、`RIGHT_X/Y`、`LTRIGGER`、`RTRIGGER`。

### 2.3 时间系统 (`time.h` / `time.c`)

```c
void  time_init(void);                  // 初始化高精度时钟基准
f64   time_seconds(void);               // 自初始化以来的秒数
u64   time_microseconds(void);          // 微秒级时间戳
f64   time_delta_since(u64 last_us);    // 计算距 last_us 的秒数
void  time_sleep_us(u64 microseconds);  // 高精度休眠
```

基于 `clock_gettime(CLOCK_MONOTONIC)` 实现，精度达纳秒级。

### 2.4 文件监视 (`filewatch.h` / `filewatch.c`)

```c
#define FILEWATCH_MAX_PATH    256
#define FILEWATCH_MAX_ENTRIES 64

typedef enum {
    FILEWATCH_EVENT_MODIFIED,
    FILEWATCH_EVENT_CREATED,
    FILEWATCH_EVENT_DELETED,
} FileWatchEventType;

typedef struct {
    FileWatchEventType type;
    char               path[FILEWATCH_MAX_PATH];
} FileWatchEvent;

typedef struct {
    FileWatchEntry entries[FILEWATCH_MAX_ENTRIES];
    u32            count;
    i32            inotify_fd;   // Linux: inotify 文件描述符
} FileWatcher;

/* 兼容 API：单文件/单目录监视（回调风格）*/
void filewatch_init(FileWatcher *fw);
void filewatch_shutdown(FileWatcher *fw);
void filewatch_add(FileWatcher *fw, const char *path,
                   void (*callback)(const char *path, void *user), void *user);
void filewatch_poll(FileWatcher *fw);

/* 增强 API：递归目录监视 + 结构化事件 */
bool filewatch_create_dir(FileWatcher *fw, const char *dir_path, bool recursive);
bool filewatch_poll_event(FileWatcher *fw, FileWatchEvent *out);
```

- **Linux**: 基于 `inotify` 内核子系统，支持递归挂载子目录与新建目录的自动追加监视；事件解析为 MODIFIED/CREATED/DELETED 三类，环形队列消费
- **Windows**: 基于 `ReadDirectoryChangesW`（`bWatchSubtree=TRUE`），递归监视目录树
- **用途**: 驱动 Shader/纹理/脚本热重载
- **兼容性**: 增强 API 与原有回调 API 共存，已有调用方零改动

### 2.5 窗口后端实现

窗口层通过 CMake 选项在编译时选择具体后端实现，统一暴露 `Platform *` 抽象。

#### 2.5.1 X11 后端 (`window_x11.c`)

Linux 默认后端，实现要点：
- 通过 Xlib 创建窗口与事件循环
- GLX 上下文管理（用于 OpenGL 后端）
- 键盘/鼠标事件转换为 `InputState`，鼠标支持捕获/隐藏/相对模式（`XGrabPointer` + 窗口中心 warp）
- 全屏切换通过 `_NET_WM_STATE_FULLSCREEN` Atom
- 通过 Xrandr/RROutputInfo 枚举多显示器与 DPI

#### 2.5.2 Wayland 后端 (`window_wayland.c`)

Linux 上的现代窗口后端，通过 `cmake -DENGINE_ENABLE_WAYLAND=ON` 启用（与 X11 编译时互斥）。实现要点：
- 核心对象：`wl_display` / `wl_compositor` / `wl_surface` / `xdg_surface` / `xdg_toplevel` / `wl_seat` / `wl_output`
- 注册表回调按需绑定 compositor、xdg_wm_base、seat、output
- XDG Shell 生命周期：`configure` 确认、`close` 退出、`ping/pong` 心跳
- 键盘：`xkbcommon` 通过 mmap 加载 keymap，处理按键事件与修饰键状态
- 指针：`motion` / `button` / `axis` 事件，侧键映射至 `INPUT_MOUSE_4/5`
- OpenGL 上下文：通过 EGL（`mesa-libEGL`）创建
- Vulkan：使用 `VK_KHR_wayland_surface` 扩展
- 协议代码：CMake 通过 `wayland-scanner` 自动从 `wayland-protocols` 生成 `xdg-shell` 客户端代码

#### 2.5.3 Win32 后端 (`window_win32.c`)

Windows 平台实现要点：
- 通过 `RegisterClassEx` + `CreateWindowEx` 创建窗口
- WGL 上下文管理（OpenGL）/ `VK_KHR_win32_surface`（Vulkan）
- 高 DPI：动态加载 `SetProcessDpiAwarenessContext` 启用 Per-Monitor V2，`WM_DPICHANGED` 中按建议矩形 `SetWindowPos` 并刷新尺寸缓存
- 鼠标：`SetCapture` + `ShowCursor` + 相对模式桩

### 2.6 游戏手柄 (Linux: `gamepad_linux.c` / `gamepad_linux.h`)

Linux 平台基于 evdev 的游戏手柄输入实现。

```c
bool gamepad_linux_init(void);
void gamepad_linux_poll(InputState *state);
void gamepad_linux_shutdown(void);
```

**特性**：
- 扫描 `/dev/input/event*`，通过 `EVIOCGBIT` 过滤具备摇杆/扳机/按键能力的设备
- 通过 `EVIOCGABS` 读取轴的最小/最大/死区，并归一化到 -1.0 ~ 1.0
- 基于 `inotify` 监听 `/dev/input` 实现热插拔（设备插入/移除自动追加/释放）
- 按键映射至统一抽象常量（XBox/SDL 风格的 `GAMEPAD_BTN_*` 与 `GAMEPAD_AXIS_*`）
- 权限/设备异常仅日志告警，不崩溃；最多支持 `INPUT_MAX_GAMEPADS = 4` 个手柄
- D-Pad 来自 `ABS_HAT0X/Y`，分解为四个独立按钮事件

#### 模块关系
- **被依赖**: Engine、RHI
- **依赖**: Core（类型、日志）

---

## 3. RHI 渲染硬件接口 (`engine/src/rhi/`)

RHI (Rendering Hardware Interface) 是对 OpenGL/Vulkan 的统一抽象，上层渲染器通过该接口操作 GPU 资源，无需关心具体图形 API。

### 3.1 句柄系统

```c
typedef struct { u32 index; u32 generation; } RHIHandle;

#define RHI_HANDLE_NULL ((RHIHandle){0, 0})
#define rhi_handle_valid(h) ((h).generation != 0)
```

**特性**：
- **代际计数（Generation）**: 每次资源销毁后 generation 递增，防止 use-after-free
- **4096 槽位资源池**: 固定大小池分配，O(1) 创建/销毁
- **强类型别名**: `RHIBuffer`, `RHIShader`, `RHIPipeline`, `RHITexture`, `RHIFramebuffer` 等

### 3.2 资源类型

| 资源类型 | 句柄类型 | 描述符结构 | 主要属性 |
|----------|----------|-----------|---------|
| **Buffer** | `RHIBuffer` | `RHIBufferDesc` | usage(Vertex/Index/Uniform/Storage/Texel), size, initial_data |
| **Shader** | `RHIShader` | — | source, len, is_fragment/is_compute |
| **Pipeline** | `RHIPipeline` | `RHIPipelineDesc` | vert/frag shader, vertex_stride, 深度/混合/剔除状态 |
| **Texture** | `RHITexture` | `RHITextureDesc` | width, height, format, mip_levels, data |
| **Sampler** | `RHISampler` | `RHISamplerDesc` | min/mag filter, wrap mode (U/V/W) |
| **Framebuffer** | `RHIFramebuffer` | — | 离屏渲染目标(color + depth) |
| **Cubemap** | `RHICubemap` | `RHICubemapDesc` | size, faces[6] |

### 3.3 命令缓冲

#### 帧生命周期

```c
RHICmdBuffer *rhi_frame_begin(RHIDevice *dev);  // 获取本帧命令缓冲
void          rhi_frame_end(RHIDevice *dev);    // 提交命令
void          rhi_present(RHIDevice *dev);      // 交换链呈现
```

#### 渲染命令

```c
void rhi_cmd_begin_render_pass(RHICmdBuffer *cmd);
void rhi_cmd_end_render_pass(RHICmdBuffer *cmd);
void rhi_cmd_bind_pipeline(RHICmdBuffer *cmd, RHIPipeline pipe);
void rhi_cmd_bind_vertex_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset);
void rhi_cmd_bind_index_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset);
void rhi_cmd_set_viewport(RHICmdBuffer *cmd, f32 x, f32 y, f32 w, f32 h);
void rhi_cmd_draw(RHICmdBuffer *cmd, u32 vertex_count, u32 instance_count);
void rhi_cmd_draw_indexed(RHICmdBuffer *cmd, u32 index_count, u32 instance_count);
```

#### 计算着色器

```c
RHIShader rhi_shader_create_compute(RHIDevice *dev, const char *source, usize len);
void      rhi_cmd_dispatch(RHICmdBuffer *cmd, u32 x, u32 y, u32 z);
void      rhi_cmd_bind_storage_buffer(RHICmdBuffer *cmd, RHIBuffer buf, u32 binding);
void      rhi_cmd_memory_barrier(RHICmdBuffer *cmd);
```

#### Cubemap Image Binding（IBL 计算用）

```c
/* 绑定 cubemap 单面为可写 image（用于 compute shader 写入）*/
void rhi_cmd_bind_image_cubemap_face(RHICmdBuffer *cmd, RHICubemap cm,
                                      u32 face, u32 unit, bool write_only);

/* 绑定 cubemap 采样器到计算管线（用于 compute shader 读取）*/
void rhi_cmd_bind_cubemap_sampler(RHICmdBuffer *cmd, RHICubemap cm,
                                   RHISampler sampler, u32 unit);
```

**用途**: IBL split-sum 预计算 — irradiance cubemap 和 prefilter cubemap 的逐面 compute dispatch。
- GL 后端: `glBindImageTexture` 使用 `layer` 参数选择 cubemap face
- VK 后端: cubemap 创建时包含 `VK_IMAGE_USAGE_STORAGE_BIT`，通过 per-face `VkImageView` + descriptor set 绑定

#### 材质 + IBL 纹理绑定

```c
/* 材质纹理绑定 (0-5): albedo, shadow, mr, normal, emissive, ssao */
void rhi_cmd_bind_material_textures(RHICmdBuffer *cmd,
    RHITexture albedo, RHITexture mr, RHITexture normal, RHITexture emissive,
    RHITexture shadow, RHITexture ssao, RHISampler sampler);

/* 材质 + IBL 纹理绑定 (0-5 + 7-9): 在一次调用中绑定材质和 IBL 纹理 */
void rhi_cmd_bind_material_textures_ibl(RHICmdBuffer *cmd,
    RHITexture albedo, RHITexture mr, RHITexture normal, RHITexture emissive,
    RHITexture shadow, RHITexture ssao, RHISampler sampler,
    RHITexture brdf_lut, RHICubemap irradiance_map, RHICubemap prefilter_map);
```

**设计意图**: PBR 着色器需要同时访问材质纹理和 IBL 纹理。VK 后端的描述符集是不可变绑定，因此必须在单次 `vkCmdBindDescriptorSets` 中提交所有 9 个绑定。`_ibl` 变体避免多次描述符集替换的开销。

#### GPU 性能计时

```c
RHIGPUTimer *rhi_gpu_timer_create(RHIDevice *dev);
void         rhi_gpu_timer_begin(RHIGPUTimer *t);
void         rhi_gpu_timer_end(RHIGPUTimer *t);
f64          rhi_gpu_timer_elapsed_ms(RHIGPUTimer *t);
```

### 3.4 后端实现

#### OpenGL 后端 (`rhi_gl.c`, ~1647 行)

- GLX 上下文初始化与交换链
- VAO/VBO/IBO 管理
- Uniform Buffer Object 绑定
- 纹理单元管理（最多 16 个纹理单元）
- FBO 离屏渲染（MRT 深度缓冲使用纹理 + `glBindImageTexture` 格式追踪）
- 计算着色器 (GL 4.3+)
- GPU 实例化渲染 (`glDrawArraysInstanced` / `glDrawElementsInstanced`)
- Cubemap face image binding（`glBindImageTexture` layer 参数）

#### Vulkan 后端 (`rhi_vk.c`, ~4037 行)

- Instance/Physical Device/Logical Device 创建
- 交换链（Swapchain）管理与重建
- 描述符集（Descriptor Set）布局与池（storage_image_layout + sampler_mip_layout）
- 内存屏障（Pipeline Barrier）与同步
- 命令池（Command Pool）与命令缓冲
- 动态 UBO 偏移
- 多帧飞行（Frames in Flight）
- Cubemap `VK_IMAGE_USAGE_STORAGE_BIT` + per-face `VkImageView` 懒创建
- IBL compute push constants 映射（u_roughness/u_face/u_face_size/u_mip_size）
- 截图功能（`rhi_screenshot`）

#### 模块关系
- **被依赖**: Renderer、Asset、Animation、UI
- **依赖**: Platform（原生窗口句柄）、Core

---

## 4. Math 数学库 (`engine/src/math/`)

纯数学运算库，零外部依赖（仅标准 `<math.h>`）。

### 4.1 数据结构

```c
typedef struct { f32 e[2]; }    Vec2;
typedef struct { f32 e[3]; }    Vec3;
typedef struct { f32 e[4]; }    Vec4;
typedef struct { f32 e[4][4]; } Mat4;  // 列主序 4×4 矩阵
typedef struct { f32 e[4]; }    Quat;  // 四元数 (x, y, z, w)

_Static_assert(sizeof(Vec4) == 16, "Vec4 must be 16 bytes");
_Static_assert(sizeof(Mat4) == 64, "Mat4 must be 64 bytes");
```

### 4.2 内联向量操作 (`math.h`)

高频操作内联于头文件：

```c
static inline Vec3 vec3_add(Vec3 a, Vec3 b);
static inline Vec3 vec3_sub(Vec3 a, Vec3 b);
static inline Vec3 vec3_scale(Vec3 v, f32 s);
static inline f32  vec3_dot(Vec3 a, Vec3 b);
static inline Vec3 vec3_cross(Vec3 a, Vec3 b);
static inline f32  vec3_len(Vec3 v);
static inline Vec3 vec3_normalize(Vec3 v);
```

### 4.3 矩阵操作 (`math.c`)

较复杂的矩阵运算放在 `.c` 文件中：

```c
Mat4 mat4_identity(void);
Mat4 mat4_perspective(f32 fov_rad, f32 aspect, f32 near, f32 far);
Mat4 mat4_ortho(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far);
Mat4 mat4_lookat(Vec3 eye, Vec3 target, Vec3 up);
Mat4 mat4_mul(Mat4 a, Mat4 b);
Mat4 mat4_inverse(Mat4 m);
Mat4 mat4_translation(f32 x, f32 y, f32 z);
Mat4 mat4_scaling(f32 x, f32 y, f32 z);
Mat4 mat4_from_quat(Quat q);
```

#### 模块关系
- **被依赖**: Renderer、Physics、Animation、Audio、Asset
- **依赖**: Core 类型系统

**单元测试：** `tests/test_math.c` (36 测试用例，覆盖 Vec3/Mat4/Quat 运算、插值、归一化、零向量、奇异矩阵、四元数乘法/旋转、结合律)

---

## 5. ECS 实体组件系统 (`engine/src/ecs/`)

基于 Archetype 的实体组件系统，SoA (Structure of Arrays) 布局，高缓存命中率。

### 5.1 Archetype 存储设计

```c
#define ECS_CHUNK_SIZE     (16 * 1024)  // 16KB 块大小
#define ECS_MAX_ARCHETYPES 1024

struct Archetype {
    ArchetypeKey    key;           // 组件类型集合
    Chunk          *chunks;        // 链表头
    Chunk          *chunk_tail;    // 链表尾
    u32            *offsets;       // 各组件在块内的偏移
    u32             chunk_capacity;// 每块可容纳的实体数
    u32             entity_offset; // Entity ID 在块内的偏移
    u32             total_count;   // 总实体数
    u32             stride;        // 单实体总字节数
    ArchetypeEdge  *edges_add;     // 添加组件时的原型转移边
    ArchetypeEdge  *edges_remove;  // 移除组件时的原型转移边
};
```

**关键设计**：
- **16KB 块（Chunk）**: 对齐 L1 缓存行，链表串联
- **SoA 布局**: 同类组件连续存储，SIMD 友好
- **原型转移图（ArchetypeEdge）**: 缓存组件增删后的目标原型，避免重复查找

### 5.2 系统限制

| 限制项 | 值 |
|--------|-----|
| 最大组件类型 | 128 |
| 最大实体数 | 64K (65,536) |
| 最大原型数 | 1,024 |
| 块大小 | 16KB |

### 5.3 实体管理

```c
typedef struct {
    u32 index;
    u32 generation;
} Entity;

#define ENTITY_NULL ((Entity){0, 0})
#define entity_valid(e) ((e).generation != 0)

Entity world_create_entity(World *w);
void   world_destroy_entity(World *w, Entity e);
```

实体采用与 RHI 相同的 index + generation 模式，销毁后通过 free stack 回收槽位。

### 5.4 组件操作

```c
void  world_register_component(World *w, ComponentType id, u32 size);
void *world_add_component(World *w, Entity e, ComponentType id);
void *world_get_component(World *w, Entity e, ComponentType id);
void  world_remove_component(World *w, Entity e, ComponentType id);
```

### 5.5 查询迭代接口

```c
// 创建查询（匹配包含指定组件集的所有原型）
Query *world_query(World *w, const ComponentType *types, u32 count);

// 迭代
QueryIter it = query_begin(q);
while (query_next(&it)) {
    Vec3 *pos = chunk_get_component(it.chunk, it.index, pos_offset, sizeof(Vec3));
    // 处理组件数据...
}
query_done(q);
```

**注意**: `chunk_get_component` 需要 `component_size` 参数用于计算正确的 SoA 偏移：`(u8 *)chunk + component_offset + index * component_size`。

#### 模块关系
- **被依赖**: 游戏逻辑层
- **依赖**: Core（类型、内存）

**单元测试：** `tests/test_ecs.c` (16 测试用例，覆盖实体创建/销毁/回收、generation 安全句柄、组件增删/数据完整性、并发查询、多组件迁移周期)

> **修复记录**: `world_query()` 原先始终使用 `queries[0]` 槽位，导致多次并发查询相互覆盖。已改为轮转槽位索引 (`query_next_slot`)，支持最多 256 个并发查询。

---

## 6. Asset 资源管理 (`engine/src/asset/`)

负责外部资源的加载、管理与热重载，连接文件系统与 RHI。

### 6.1 架构

```c
typedef struct {
    RHIDevice *device;  // GPU 资源上传目标
    VFS       *vfs;     // 虚拟文件系统
} AssetCtx;

void       asset_ctx_init(AssetCtx *ctx, RHIDevice *dev);
RHITexture asset_load_texture(AssetCtx *ctx, const char *path);
bool       asset_load_gltf(AssetCtx *ctx, const char *path, Scene *out_scene);
```

**支持格式**：
- **模型**: glTF 2.0（通过 cgltf 解析）
- **纹理**: PNG / JPG（通过 stb_image 解码）
- **字体**: TTF（通过 stb_truetype 光栅化）

### 6.2 Scene 数据结构

```c
typedef struct {
    RHITexture albedo;
    RHITexture metallic_roughness;
    RHITexture normal_map;
    RHITexture emissive;
    float      base_color[4];
    float      metallic_factor;
    float      roughness_factor;
    float      emissive_strength;
    AlphaMode  alpha_mode;       // OPAQUE / MASK / BLEND
    float      alpha_cutoff;
} Material;

typedef struct {
    RHIBuffer vertex_buf;
    RHIBuffer index_buf;
    u32       index_count;
    u32       material_idx;
    Vec3      aabb_min, aabb_max;  // 包围盒
} Mesh;

typedef struct {
    Mat4    local_transform;
    Mat4    world_transform;
    u32     parent_index;
    u32     mesh_index;
    u32     material_idx;
    bool    has_mesh;
    bool    skinned;
} SceneNode;

typedef struct {
    Material     *materials;      u32 material_count;
    Mesh         *meshes;         u32 mesh_count;
    SkinnedMesh  *skinned_meshes; u32 skinned_mesh_count;
    SceneNode    *nodes;          u32 node_count;
    AnimClip     *anim_clips;     u32 anim_clip_count;
    u32          *joint_parents;
    Mat4         *inverse_bind;
} Scene;
```

### 6.3 场景序列化 (`scene_serial.h` / `scene_serial.c`)

场景支持二进制和 JSON 两种序列化格式，以及 prefab 实例化：

```c
/* 二进制格式 — 快速加载，用于运行时资源 */
bool scene_save_binary(const World *w, const Scene *s, const char *path);
bool scene_load_binary(World *w, Scene *s, const char *path);

/* JSON 格式 — 可读可编辑，用于编辑器/调试 */
bool scene_save_json(const World *w, const Scene *s, const char *path);
bool scene_load_json(World *w, Scene *s, const char *path);

/* Prefab 实例化 — 加载 prefab 并应用位置偏移 */
bool scene_instantiate_prefab(World *w, Scene *s, const char *path, Vec3 position);
```

**特性**：
- JSON 反序列化支持 materials、meshes、skinned_meshes、nodes、anim_clips 全字段解析
- `scene_instantiate_prefab` 加载后自动对新节点应用 `position` 偏移（修改 `local_transform` 平移列）
- 二进制格式与 JSON 格式数据对称，保证 save/load 往返一致性

### 6.4 VFS 虚拟文件系统 (`vfs.h` / `vfs.c`)

```c
#define VFS_MAX_MOUNTS  16
#define VFS_PAK_MAGIC   0x54415045  // 'TAPE'

VFS    *vfs_create(void);
bool    vfs_mount_dir(VFS *vfs, const char *dir_path);  // 挂载目录
bool    vfs_mount_pak(VFS *vfs, const char *pak_path);  // 挂载打包文件

VFSFile *vfs_open(VFS *vfs, const char *path);
u8      *vfs_read_all(VFS *vfs, const char *path, usize *out_size);
void     vfs_close(VFSFile *f);
```

**特性**：
- 多挂载点优先级查找（后挂载的优先）
- PAK 打包格式（自定义，含 FNV-1a 哈希索引）
- 统一接口，上层无需区分目录/PAK 来源

**单元测试：** `tests/test_vfs.c` (18 测试用例，覆盖目录挂载、文件读写、PAK 二进制格式、挂载优先级、边界条件)

### 6.5 热重载 (`hotreload.h` / `hotreload.c`)

```c
typedef struct {
    RHIDevice  *device;
    RHIPipeline pipeline;
    char        vert_path[256];
    char        frag_path[256];
    FileWatcher watcher;
} HotReloadPipeline;

bool  hotreload_pipeline_init(HotReloadPipeline *hr, RHIDevice *dev,
                               const char *vert_path, const char *frag_path,
                               RHIPipelineDesc *out_desc);
void  hotreload_pipeline_poll(HotReloadPipeline *hr);
```

- 基于 FileWatcher 监控 Shader/纹理文件变更
- 自动重编译管线或重新加载纹理

#### 模块关系
- **被依赖**: Renderer、Animation
- **依赖**: RHI、VFS、Core、Platform（FileWatch）

---

## 7. Animation 动画系统 (`engine/src/animation/`)

骨骼动画系统，支持 glTF 骨骼导入与实时播放。

### 7.1 骨骼（Skeleton）

```c
#define SKELETON_MAX_JOINTS    128
#define SKELETON_MAX_CHANNELS  64
#define SKELETON_MAX_KEYFRAMES 256

typedef struct {
    u32       joint_count;
    u32       joint_parents[SKELETON_MAX_JOINTS];    // 父关节索引
    Mat4      inverse_bind[SKELETON_MAX_JOINTS];     // 逆绑定姿态矩阵
    Mat4      current_pose[SKELETON_MAX_JOINTS];     // 当前变换（CPU 端）
    RHIBuffer joint_buf;                             // GPU 缓冲（上传用）
    RHIDevice *device;
} Skeleton;
```

### 7.2 动画片段（AnimClip）

```c
typedef enum {
    ANIM_PATH_TRANSLATION,
    ANIM_PATH_ROTATION,
    ANIM_PATH_SCALE,
} AnimPathType;

typedef struct {
    AnimPathType path;
    u32          joint_index;
    u32          keyframe_count;
    f32          times[SKELETON_MAX_KEYFRAMES];
    f32          values[SKELETON_MAX_KEYFRAMES][4];  // 平移3/旋转4/缩放3
} AnimChannel;

typedef struct {
    f32         duration;
    f32         time;
    bool        playing;
    bool        loop;
    u32         channel_count;
    AnimChannel channels[SKELETON_MAX_CHANNELS];
} AnimClip;
```

### 7.3 工作流

```c
// 1. 初始化骨骼
skeleton_init(&sk, dev);
skeleton_set_joints(&sk, count, parents, inv_bind);

// 2. 配置动画
anim_clip_init(&clip, duration, true);
anim_clip_add_channel(&clip, joint_idx, ANIM_PATH_ROTATION,
                       keyframe_count, times, values);

// 3. 每帧更新
skeleton_evaluate(&sk, &clip, dt);  // 插值计算当前姿态
skeleton_upload(&sk);               // 上传 joint 矩阵到 GPU
```

### 7.4 动画混合系统 (`animation.h` / `animation.c`)

多层动画混合引擎，支持 Override/Additive 模式、骨骼遮罩与交叉淡入淡出：

```c
#define ANIM_MAX_LAYERS  8
#define ANIM_MAX_JOINTS  128

typedef enum { ANIM_LAYER_OVERRIDE, ANIM_LAYER_ADDITIVE } AnimLayerMode;

typedef struct {
    bool   active;
    u32    clip_index;
    f32    time, speed, weight;
    bool   loop;
    u64    bone_mask;   /* 0 = 不过滤（包含所有骨骼），非 0 则按位过滤 */
    AnimLayerMode mode;
} AnimationLayer;

typedef struct {
    u32          layer_count;
    AnimationLayer layers[ANIM_MAX_LAYERS];
    Vec4         local_positions[ANIM_MAX_JOINTS];
    Quat         local_rotations[ANIM_MAX_JOINTS];
    /* ... */
} AnimBlendState;
```

**重要语义：** `bone_mask = 0` 表示「不过滤」= 包含所有骨骼。多层混合时必须显式设置 `bone_mask`，否则上层会覆盖下层未动画化的骨骼为绑定姿态。

**IK 系统：** 内置 Two-Bone IK 解析求解器（余弦定理），支持 `weight` 渐变与 `pole_vector` 方向控制。

**单元测试：** `tests/test_animation.c` (16 测试用例，覆盖 AnimBlendState 层级混合、bone_mask 过滤、交叉淡入淡出、Two-Bone IK 求解)

#### 模块关系
- **被依赖**: Renderer（蒙皮渲染）
- **依赖**: RHI（GPU Buffer）、Math（矩阵/四元数）

---

## 8. Physics 物理系统 (`engine/src/physics/`)

轻量级刚体物理引擎，聚焦游戏常见场景。

### 8.1 刚体（RigidBody）

```c
typedef struct {
    Vec3  position;
    Vec3  velocity;
    Vec3  acceleration;
    Vec3  half_extent;      // AABB 半尺寸
    f32   mass;
    f32   restitution;      // 弹性系数
    bool  is_static;
    u32   rest_frames;      // 静止帧计数（休眠优化）
} RigidBody;
```

### 8.2 碰撞检测

```c
typedef struct {
    Vec3  point;
    Vec3  normal;
    f32   depth;
    u32   body_a;
    u32   body_b;
} Contact;

AABB  aabb_from_body(const RigidBody *b);
bool  aabb_overlap(AABB a, AABB b);
Vec3  aabb_overlap_depth(AABB a, AABB b);
```

- **宽相**: AABB-AABB 重叠检测
- **窄相**: 接触约束求解
- **射线检测**: `physics_raycast()` 支持最大距离与命中体返回

### 8.3 物理世界

```c
PhysicsWorld *physics_world_create(u32 max_bodies);
u32           physics_body_create(PhysicsWorld *pw, Vec3 pos, Vec3 half_ext,
                                   f32 mass, bool is_static, u32 frame);
void          physics_body_apply_impulse(PhysicsWorld *pw, u32 body_id, Vec3 impulse);
void          physics_step(PhysicsWorld *pw, f32 dt);
bool          physics_raycast(const PhysicsWorld *pw, Vec3 origin, Vec3 dir,
                               f32 max_dist, u32 *out_body, f32 *out_t);
```

### 8.4 角色控制器 (`character.h` / `character.c`)

```c
typedef struct {
    Vec3  position;
    Vec3  velocity;
    f32   radius;
    f32   height;
    f32   slope_limit;    // 最大可行走坡度
    f32   step_height;    // 自动上阶高度
    bool  grounded;       // 是否在地面
    bool  jump_requested;
} CharacterController;

CharacterController character_create(Vec3 pos, f32 radius, f32 height);
void    character_update(CharacterController *cc, PhysicsWorld *pw, f32 dt,
                          Vec3 move_input, bool jump);
bool    character_is_grounded(const CharacterController *cc);
```

**特性**：
- 自动地面检测（sweep test）
- 跳跃请求与空中状态管理
- 坡度限制与阶梯攀登

### 8.5 BVH 宽相加速 (`bvh.h` / `bvh.c`)

BVH (Bounding Volume Hierarchy) 用于物理碰撞的宽相检测：

- **SAH 构建**: `bvh_build()` 使用 Surface Area Heuristic 优化树结构
- **增量更新**: `bvh_refit()` 仅更新移动的叶节点，避免重建
- **碰撞对查询**: `bvh_query_pairs()` 通过回调返回所有重叠对
- **射线检测**: `bvh_raycast()` 返回最近命中的对象和距离
- **AABB 查询**: `bvh_query_aabb()` 返回与给定 AABB 重叠的所有对象

`PhysicsWorld` 内部使用 BVH：首次 `physics_step()` 时构建，后续帧仅 refit。

**单元测试：** `tests/test_physics.c` (16 测试用例)

覆盖：AABB 计算/重叠/接触、World 创建/销毁、刚体创建/静态、重力下落、冲量/静态忽略、碰撞检测、地面重生、射线检测命中/未中、BVH 构建查询/射线。

**角色控制器测试：** `tests/test_character.c` (10 测试用例)

覆盖：创建基本属性、重力下落、移动输入、地面碰撞、跳跃、位置查询、初始状态、sweep test 命中/未中/忽略。

#### 模块关系
- **被依赖**: 游戏逻辑
- **依赖**: Math

---

## 9. Audio 音频系统 (`engine/src/audio/`)

基于 miniaudio 的跨平台音频播放。

### 9.1 核心结构

```c
typedef struct {
    void       *engine;          // miniaudio engine 实例
    AudioSource *sources;        // 活跃音源列表
    u32         source_count;
    u32         source_cap;
    Vec3        listener_pos;    // 监听器位置
    Vec3        listener_forward;
    Vec3        listener_up;
} AudioSystem;
```

### 9.2 接口

```c
AudioSystem *audio_system_create(void);
void         audio_system_destroy(AudioSystem *as);
void         audio_system_update(AudioSystem *as, Vec3 listener_pos,
                                  Vec3 forward, Vec3 up);

u32          audio_play(AudioSystem *as, const char *path, f32 volume, bool looping);
void         audio_play_3d(AudioSystem *as, const char *path, Vec3 position,
                            f32 volume, bool looping);
void         audio_stop(AudioSystem *as, u32 source_id);
void         audio_set_listener(AudioSystem *as, Vec3 pos, Vec3 forward, Vec3 up);
```

**特性**：
- 2D 播放（背景音乐、UI 音效）
- 3D 空间音效（基于监听器位置的距离衰减与声像定位）
- 支持循环播放

### 9.3 设备枚举与选择

基于 miniaudio `ma_context` 的设备发现，Linux 平台递归枚举 ALSA/PulseAudio 设备。

```c
#define AUDIO_MAX_DEVICES 16

typedef struct {
    char  name[256];
    bool  is_default;
} AudioDeviceInfo;

u32              audio_get_device_count(AudioSystem *as);
bool             audio_get_device_info(AudioSystem *as, u32 index, AudioDeviceInfo *out);
u32              audio_get_current_device(AudioSystem *as);
bool             audio_set_device(AudioSystem *as, u32 index);
```

**设计**：
- 采用 index-as-id 策略，最多缓存 16 个播放设备
- `audio_set_device` 返回 `false`（miniaudio 不支持运行时热切换），仅记录设备名供下次 `audio_system_create` 重初始化时生效
- 完全向后兼容原有初始化路径（默认设备路径未变）

#### 模块关系
- **被依赖**: 游戏逻辑
- **依赖**: Math（Vec3）、Core

---

## 10. Task 任务系统 (`engine/src/task/`)

多线程任务调度，用于并行化计算密集工作。

### 10.1 核心结构

```c
typedef void (*TaskFn)(void *ctx);

typedef struct {
    TaskQueue  queues[64];       // 64 条无锁任务队列
    i32        worker_count;     // 工作线程数
    bool       running;
    void     **threads;          // 线程句柄数组
    TaskQueue *local_queues;     // 每线程本地队列
    i32       *worker_ids;
    u64        completed_tasks;  // 已完成任务计数
} TaskSystem;
```

### 10.2 接口

```c
TaskSystem *task_system_create(i32 worker_count);
void        task_system_destroy(TaskSystem *ts);
void        task_submit(TaskSystem *ts, TaskFn fn, void *ctx);        // 提交单任务
void        task_submit_n(TaskSystem *ts, TaskFn fn, void **ctxs, i32 count); // 批提交
void        task_wait(TaskSystem *ts);                                 // 等待所有完成
i32         task_worker_id(TaskSystem *ts);                            // 获取当前 worker ID
```

**特性**：
- **64 条队列**: 减少锁竞争
- **工作窃取**: 空闲线程从其他队列偷取任务
- **批提交**: `task_submit_n` 一次性提交多任务，减少调度开销

#### 模块关系
- **被依赖**: Renderer（视锥剔除、粒子更新）、Physics
- **依赖**: Core、Platform（线程原语）

---

## 11. Script 脚本系统 (`engine/src/script/`)

自定义轻量脚本语言，用于快速迭代游戏逻辑。

### 11.1 核心结构

```c
#define SCRIPT_MAX_CALLBACKS 64
#define SCRIPT_MAX_GLOBALS   128

typedef enum {
    SCRIPT_OP_SET,    // 设置变量
    SCRIPT_OP_ADD,    // 累加变量
    SCRIPT_OP_SPAWN,  // 生成实体
    SCRIPT_OP_PRINT,  // 调试输出
} ScriptOpType;

typedef struct {
    ScriptOpType type;
    char         target[64];
    f32          value;
    f32          args[3];
} ScriptOp;

typedef struct {
    ScriptFunc    funcs[SCRIPT_MAX_CALLBACKS];
    u32           func_count;
    ScriptGlobal  globals[SCRIPT_MAX_GLOBALS];
    u32           global_count;
    char         *source;
    bool          loaded;
} ScriptEngine;
```

### 11.2 接口

```c
void  script_engine_init(ScriptEngine *se);
void  script_engine_shutdown(ScriptEngine *se);
bool  script_load(ScriptEngine *se, const char *path);
void  script_set_global(ScriptEngine *se, const char *name, f32 value);
f32   script_get_global(ScriptEngine *se, const char *name);
void  script_call(ScriptEngine *se, const char *func_name);
void  script_reload_if_changed(ScriptEngine *se, const char *path);
```

### 11.3 使用示例（脚本文件）

```
# init.script 示例
on_update:
  SET speed 5.0
  ADD score 1.0
  PRINT "frame updated"

on_spawn:
  SPAWN enemy 10.0 0.0 5.0
```

**特性**：
- **热重载**: `script_reload_if_changed` 检测文件变更并重新解析
- **事件钩子**: `on_update`, `on_spawn` 等命名函数绑定引擎事件
- **全局变量**: 引擎与脚本间双向数据传递

**单元测试：** `tests/test_script.c` (9 测试用例)

覆盖：init/shutdown、set/get global、global 覆盖、缺失 global、多 global、文件加载+函数执行、不存在函数调用、不存在文件、注释忽略。

#### 模块关系
- **被依赖**: 游戏逻辑
- **依赖**: Core（IO、字符串）

---

## 12. UI 系统 (`engine/src/ui/`)

调试界面与文本渲染。

### 12.1 FontRenderer (`font.h` / `font.c`)

```c
#define FONT_ATLAS_SIZE  512   // 512×512 像素纹理图集
#define FONT_GLYPH_COUNT 96   // ASCII 32-127

typedef struct {
    RHIDevice  *device;
    RHITexture  atlas_tex;       // 字形图集纹理
    RHISampler  sampler;
    RHIPipeline pipeline;        // 字体渲染管线
    RHIBuffer   vbo;             // 动态顶点缓冲
    f32         font_size;
    f32         ascent, descent, line_gap;
    GlyphInfo   glyphs[FONT_GLYPH_COUNT];
    u8         *quad_data;       // CPU 端四边形缓存
    u32         quad_count;
    u32         quad_capacity;
} FontRenderer;

bool font_renderer_init(FontRenderer *fr, RHIDevice *dev, const char *ttf_path, f32 font_size);
void font_renderer_begin(FontRenderer *fr);
void font_renderer_draw(FontRenderer *fr, const char *text, f32 x, f32 y,
                         f32 screen_w, f32 screen_h, f32 r, f32 g, f32 b, f32 a);
void font_renderer_end(FontRenderer *fr, RHICmdBuffer *cmd, f32 screen_w, f32 screen_h);
```

**工作流**：TTF 加载 → stb_truetype 光栅化 → 512×512 图集上传 GPU → 逐帧批量提交四边形

### 12.2 DebugUI (`debug_ui.h` / `debug_ui.c`)

```c
typedef struct {
    char   lines[32][128];   // 32 行文本缓冲，每行 128 字符
    u32    line_count;
    bool   visible;          // 运行时切换显隐
    bool   initialized;
    FontRenderer font;
    RHIDevice   *device;
} DebugUI;

void debug_ui_init(DebugUI *ui);
void debug_ui_init_renderer(DebugUI *ui, RHIDevice *dev);
void debug_ui_begin(DebugUI *ui);
void debug_ui_text(DebugUI *ui, const char *fmt, ...);   // printf 风格写入
void debug_ui_end(DebugUI *ui);
void debug_ui_render(DebugUI *ui, RHICmdBuffer *cmd, u32 screen_w, u32 screen_h);
void debug_ui_toggle(DebugUI *ui);   // 热键切换显隐
```

**特性**：
- 即时模式（Immediate Mode）文本 UI
- 32 行滚动缓冲区
- 用于显示 FPS、内存使用、ECS 统计等

#### 模块关系
- **被依赖**: Engine 主循环（调试覆盖层）
- **依赖**: RHI、Font 渲染器

---

## 13. 引擎入口 (`engine/src/engine.c` / `engine.h`)

顶层生命周期管理，集成各子系统。

### 13.1 配置与状态

```c
typedef struct {
    u32         width;
    u32         height;
    const char *title;
    f64         target_fps;    // 0 = 不限帧率
} EngineConfig;

typedef struct {
    Platform *platform;       // 平台抽象
    f64       delta_time;     // 帧间隔（秒）
    u64       frame_count;    // 累计帧数
    f64       fps;            // 当前 FPS
    f64       target_fps;     // 目标帧率
    u64       last_frame_us;  // 上帧时间戳
    f64       fps_accum;      // FPS 计算累积器
    u64       fps_frames;     // FPS 帧数累积
} Engine;
```

### 13.2 生命周期

```c
bool engine_init(Engine *e, const EngineConfig *cfg);
// → time_init() → platform_create() → 初始化帧计时

bool engine_frame(Engine *e);
// → platform_poll() → 输入检测 → delta_time 计算 → FPS 统计 → 帧率限制

void engine_shutdown(Engine *e);
// → platform_destroy() → 清理
```

### 13.3 典型主循环

```c
int main(void) {
    Engine engine;
    EngineConfig cfg = { .width = 1280, .height = 720,
                          .title = "Break Engine", .target_fps = 60.0 };

    if (!engine_init(&engine, &cfg)) return 1;

    while (engine_frame(&engine)) {
        // 游戏逻辑更新
        // 渲染提交
    }

    engine_shutdown(&engine);
    return 0;
}
```

#### 模块关系
- **依赖**: Platform、Core（日志、时间、内存）
- **集成**: 作为顶层入口协调所有子系统

---

## 11. Scene 场景序列化 (`engine/src/scene/`)

**实现文件：** `scene_serial.c` (893行), `scene_serial.h`

### 11.1 BSCN 二进制格式

场景序列化采用自定义分块二进制格式（BSCN），支持 ECS World + Scene 场景图的完整保存与加载。

| 块类型 | 说明 |
|----------|------|
| `BSCN_CHUNK_ENTITIES` | ECS 实体列表（generation + 组件类型） |
| `BSCN_CHUNK_COMPONENTS` | 组件实例数据（按类型分组） |
| `BSCN_CHUNK_HIERARCHY` | 场景层级结构（父子关系） |
| `BSCN_CHUNK_RESOURCES` | 资源引用表（网格/纹理/材质） |
| `BSCN_CHUNK_SCENE_NODES` | 场景节点变换 + 网格引用 |

**核心 API：**

```c
/* 保存为 BSCN 二进制 */
bool scene_save_binary(const World *w, const Scene *s,
                       const char *path, const SerializeOptions *opts);

/* 加载 BSCN 二进制 */
bool scene_load_binary(World *w, Scene *s, const char *path);

/* 导出为 JSON（调试用） */
bool scene_save_json(const World *w, const Scene *s,
                     const char *path, const SerializeOptions *opts);

/* 加载 JSON */
bool scene_load_json(World *w, Scene *s, const char *path);

/* Prefab 保存 + 实例化 */
bool scene_save_prefab(const World *w, const Entity *entities,
                       u32 count, const char *path);
bool scene_instantiate_prefab(World *w, Scene *s,
                              const char *path, Vec3 position);
```

### 11.2 集成策略

主循环中的场景存储采用双文件策略：

| 文件 | 格式 | 内容 |
|------|------|------|
| `scene_save.bscn` | BSCN 二进制 | ECS 实体 + 组件 + 场景图 |
| `scene_state.bin` | 原始二进制 | 相机/太阳/曝光/物理体状态 |

快捷键：`B` 保存 / `N` 加载 / `Shift+B` 导出 JSON

**单元测试：** `tests/test_scene_serial.c` (14 测试用例，覆盖 BSCN 魔数/版本验证、加载错误处理、截断/溢出边界条件、JSON 格式)

---

## 12. GPU-Driven 渲染管线 (`engine/src/renderer/`)

### 12.0 Camera 与 CPU 视锥剔除 (`camera.c` / `cull.c` / `frustum_cull.c`)

Camera 模块提供视角/投影矩阵计算；CPU 视锥剔除提供 Gribb-Hartmann 平面提取、AABB/球体/点测试以及批量剔除 API：

```c
typedef struct { Vec4 planes[6]; } Frustum;
typedef struct { Vec3 min, max; } CullAABB;

Frustum frustum_from_vp(Mat4 vp);
bool    frustum_test_aabb(const Frustum *f, Vec3 mn, Vec3 mx);
u32     frustum_cull_batch(const Frustum *f, const CullAABB *aabbs, u32 count, u32 *vis);
```

**单元测试：** `tests/test_camera_frustum.c` (14 测试用例，覆盖 Camera 初始化/投影矩阵、Frustum 平面提取、点/AABB/球体测试、批量剔除)

**单元测试：** `tests/test_lighting.c` (11 测试用例，覆盖点光/方向光添加、溢出钳制、清除、空场景剔除、单光可见性、背后相机剔除、多光可见性筛选、网格偏移结构验证)

### 12.1 Indirect Draw (`indirect_draw.c` / `indirect_draw.h`)

GPU 驱动的间接绘制系统，通过单次 GPU 调用执行所有可见对象的绘制。

**核心结构：**

```c
typedef struct {
    u32 index_count;
    u32 instance_count;
    u32 first_index;
    i32 vertex_offset;
    u32 first_instance;
} DrawIndexedIndirectCmd;

typedef struct {
    RHIBuffer   all_draws_buf;      /* 全部 draw 命令 */
    RHIBuffer   visible_draws_buf;  /* 压缩后可见 draw 命令 */
    RHIBuffer   draw_count_buf;     /* 原子计数器 */
    RHIBuffer   visibility_buf;     /* 每对象可见性标志 */
    RHIPipeline compact_pipeline;   /* 压缩 compute shader */
    u32         max_draws;
    u32         current_draw_count;
    bool        ready;
} IndirectDrawSystem;
```

**API：**

| 函数 | 说明 |
|------|------|
| `indirect_draw_init(sys, dev, max)` | 初始化缓冲区 + compact 管线 |
| `indirect_draw_upload(sys, dev, cmds, n)` | 上传 draw 命令到 GPU |
| `indirect_draw_upload_visibility(sys, dev, flags, n)` | 上传可见性标志 |
| `indirect_draw_compact(sys, dev, cmd)` | dispatch 压缩 shader |
| `indirect_draw_execute(sys, dev)` | 单次间接绘制 |
| `indirect_draw_destroy(sys, dev)` | 释放资源 |

### 12.2 GPU Frustum Culling (`gpucull.c` / `gpucull.h`)

GPU 视锥剔除系统，使用 compute shader 并行测试对象可见性。

**核心结构：**

```c
typedef struct {
    RHIDevice  *device;
    RHIPipeline cull_pipe;       /* 视锥剔除 compute 管线 */
    RHIBuffer   object_ssbo;     /* 对象位置 + 包围球半径 */
    RHIBuffer   visible_ssbo;    /* 可见对象索引输出 */
    RHIBuffer   count_buf;       /* 可见对象计数 */
    u32         object_count;
    bool        ready;
} GPUCullSystem;
```

| 常量 | 值 |
|------|------|
| `GPUCULL_MAX_OBJECTS` | 4096 |

**API：**

| 函数 | 说明 |
|------|------|
| `gpucull_init(gc, dev)` | 初始化 compute 管线 + 缓冲区 |
| `gpucull_update_objects(gc, pos, radii, n)` | 上传对象位置 + 半径 |
| `gpucull_dispatch(gc, cmd, vp)` | dispatch 视锥剔除 compute |
| `gpucull_get_results(gc, &count)` | 获取可见对象数 |
| `gpucull_shutdown(gc)` | 释放资源 |

### 12.3 Mega-Buffer 构建

主循环初始化时将场景 mesh 合并为单一 VBO/IBO：

1. 遍历所有场景节点，统计总顶点数 / 索引数
2. 映射每个 mesh 的 VBO/IBO，变换顶点到世界空间
3. 重映射索引（加顶点偏移）
4. 生成 `DrawIndexedIndirectCmd` 条目
5. 创建组合 GPU 缓冲区 + 初始化 IndirectDraw 系统
6. **按材质分组：** 相同 `material_idx` 的 draw commands 收集到独立的 `IndirectDrawSystem` 实例（最多 64 个材质组）

**优势：** 消除每对象 `u_model` 矩阵更新，配合间接绘制实现单 draw call 渲染全部场景 mesh。

**Per-Material 批量应用范围：**

| 渲染通道 | 优化方式 |
|------|------|
| CSM 阴影 | 单次间接绘制（全场景共享深度管线） |
| 点光源阴影 | 每面单次间接绘制（6L 次 draw call） |
| Deferred G-Buffer | 每材质单次间接绘制（M 次 draw call） |
| 前向场景 | 每材质单次间接绘制（M 次 draw call） |

### 12.4 Occlusion Culling 遮挡剔除 (`occlusion_cull.c` / `occlusion_cull.h`)

Hi-Z 遮挡剔除系统，通过深度金字塔纹理实现 GPU 端对象可见性查询，CPU 端提供 1 帧延迟的可见性读back。

**核心结构：**

```c
#define OCCLUSION_MAX_OBJECTS 16384

typedef struct {
    Vec3 min;
    f32  _pad0;
    Vec3 max;
    f32  _pad1;
} ObjectAABB;

typedef struct {
    RHITexture  hi_z_texture;       /* Hi-Z 深度金字塔纹理 (R32F, mipchain) */
    u32         hi_z_width;
    u32         hi_z_height;
    u32         hi_z_levels;
    RHIBuffer   aabb_buffer;        /* SSBO: ObjectAABB[max_objects] */
    RHIBuffer   visibility_buffer;  /* SSBO: u32[max_objects] (0=occluded, 1=visible) */
    RHIPipeline hi_z_pipeline;      /* Hi-Z 生成 compute 管线 */
    RHIPipeline cull_pipeline;      /* 遮挡剔除 compute 管线 */
    RHISampler  hi_z_sampler;
    RHIDevice  *device;
    u32         object_count;
    bool        enabled;
    u32        *visibility_readback; /* CPU 读back（上一帧结果） */
} OcclusionCullSystem;
```

**API：**

| 函数 | 说明 |
|------|------|
| `occlusion_cull_init(sys, dev, w, h)` | 初始化 Hi-Z 纹理 + compute 管线 |
| `occlusion_cull_upload_aabbs(sys, aabbs, n)` | 上传对象 AABB 到 GPU |
| `occlusion_cull_generate_hi_z(sys, cmd, depth)` | 生成 Hi-Z 深度金字塔 |
| `occlusion_cull_dispatch(sys, cmd, vp, n)` | dispatch 遮挡剔除 compute |
| `occlusion_cull_is_visible(sys, idx)` | CPU 端查询对象可见性（1 帧延迟） |
| `occlusion_cull_visible_count(sys)` | 统计可见对象数量 |
| `occlusion_cull_shutdown(sys)` | 释放资源 |

**单元测试：** `tests/test_occlusion_visibility.c` (13 测试用例，覆盖可见性查询边界条件：全可见、部分遮挡、全遮挡、越界返回可见、禁用返回可见、NULL readback 返回可见、可见对象计数)

### 12.5 Terrain 地形系统 (`terrain.c` / `terrain.h`)

程序化地形生成、高度查询、编辑与侵蚀系统。

**核心结构：**

```c
typedef struct {
    RHIDevice  *device;
    RHIPipeline pipeline;
    RHIBuffer   vbo;
    RHIBuffer   ibo;
    u32         index_count;
    u32         grid_size;        /* 网格分辨率（正方形） */
    f32         scale;            /* 世界空间尺寸 */
    f32         height_scale;     /* 高度缩放 */
    f32        *heightmap;        /* CPU 高度图 (grid_size²) */
    u32         modify_count;     /* 编辑计数 */
    f32         total_delta;      /* 累计变化量 */
    u32         edit_quadrant[4]; /* 象限编辑计数 */
} Terrain;
```

**CPU API（可独立测试）：**

| 函数 | 说明 |
|------|------|
| `terrain_get_height(t, x, z)` | 双线性插值高度查询 |
| `terrain_modify_height(t, x, z, r, s)` | 半径内高度修改（二次衰减） |
| `terrain_flatten(t, x, z, r)` | 半径内平均化平坦 |
| `terrain_erode(t, x, z, r, iter)` | 水力侵蚀模拟 |
| `terrain_noise_stamp(t, x, z, r, s, seed)` | 程序化噪声图章 |
| `terrain_generate(t, preset)` | 5 种预设地形生成 |

**单元测试：** `tests/test_terrain.c` (18 测试用例，覆盖 NULL 安全、中心采样、均匀高度图、双线性插值、角点铗位、高度修改/衰减、平坦化、侵蚀峰值削减、5 种预设生成、噪声图章、象限跟踪)

### 12.6 Input 输入状态机 (`engine/src/platform/input.c` / `input.h`)

跨平台输入状态管理，支持键盘、鼠标、滚轮、手柄的边沿检测（just pressed / just released / held）。

**状态编码：**

| 值 | 含义 | `key_down` | `key_pressed` | `key_released` |
|------|------|------------|--------------|----------------|
| 0 | 抬起 | ✖ | ✖ | ✖ |
| 1 | 刚释放 | ✖ | ✖ | ✔ |
| 2 | 持续按住 | ✔ | ✖ | ✖ |
| 3 | 刚按下 | ✔ | ✔ | ✖ |

**API：**

| 函数 | 说明 |
|------|------|
| `input_init(s)` | 零初始化 |
| `input_new_frame(s)` | 帧状态衰减 + 增量清除 |
| `input_set_key(s, key, pressed)` | 设置按键状态 |
| `input_set_mouse(s, x, y)` | 更新鼠标位置 + 增量 |
| `input_set_scroll(s, dx, dy)` | 累积滚轮增量 |
| `input_set_pad_button(s, pad, btn, pressed)` | 手柄按键状态 |

**单元测试：** `tests/test_input.c` (20 测试用例，覆盖初始化、状态转换全周期、宏检测、帧衰减、鼠标位置/增量、滚轮累积、越界安全、手柄按键、多键同时)

---

## 13. Render Graph 声明式渲染管线 (`engine/src/renderer/`)

### 13.1 概述

声明式渲染管线图，支持自动依赖推导、死路径剔除、拓扑排序和生命周期别名。

**核心特性：**
- 声明式 pass/resource 图构建
- 自动依赖推导（通过资源读写关系）
- 死路径剔除（未消费的输出对应的 pass 被自动裁剪）
- Kahn 拓扑排序保证执行顺序
- 纹理池生命周期别名（相同尺寸/格式的纹理可复用同一 GPU 资源）

**单元测试：** `tests/test_render_graph.c` (12 测试用例)

覆盖：创建/销毁、pass/resource 声明、依赖推导与执行顺序、死路径剔除、执行回调、Reset 复用、资源查找、统计信息。

---

## 14. Command Buffer 命令缓冲区 (`engine/src/renderer/cmd_buffer.c`)

多线程渲染命令录制系统，支持并行录制、排序和 RHI replay。

**核心结构：**

```c
#define CMD_BUFFER_MAX_COMMANDS 4096
#define PARALLEL_RENDERER_MAX_THREADS 16

typedef struct {
    RHICmdBuffer  cmds[CMD_BUFFER_MAX_COMMANDS];
    u32           count;
} CmdBuffer;

typedef struct {
    CmdBuffer thread_buffers[PARALLEL_RENDERER_MAX_THREADS];
    u32       thread_count;
    u32       sort_key_counter;
} ParallelRenderer;
```

**API：**

| 函数 | 说明 |
|------|------|
| `parallel_renderer_init(pr, thread_count)` | 初始化并行录制器 |
| `parallel_renderer_get_buffer(pr, thread_idx)` | 获取线程专属命令缓冲 |
| `parallel_renderer_record_draw/pr/bind_*/push_*` | 录制各类渲染命令 |
| `parallel_renderer_submit(pr, cmd)` | 合并、排序并提交到 RHI |
| `parallel_renderer_frame_reset(pr)` | 帧结束时重置所有缓冲 |

**设计要点：**
- 每线程独立的 `CmdBuffer`，无锁录制
- 命令使用 `sort_key` 排序（插入排序），保证透明对象正确顺序
- 溢出时静默丢弃（`CMD_BUFFER_MAX_COMMANDS = 4096`）
- `ParallelRenderer` 约 9MB，必须堆分配（栈分配会溢出）

**单元测试：** `tests/test_cmd_buffer.c` (20 测试用例，覆盖生命周期、init 参数钳制、null 安全、draw/draw_indexed/bind_pipeline/bind_buffers/bind_uniform_and_texture 录制、scissor/viewport、push_constants、溢出丢弃、混合命令序列、sort_key 分配)

---

## 15. 异步资源加载器 (`engine/src/asset/async_loader.c/h`)

多线程异步 I/O 系统，支持文件加载回调和请求取消。

**核心 API：**
- `async_loader_init(thread_count, vfs)` — 初始化 I/O 线程池
- `async_loader_request(path, callback, user_data)` — 提交异步加载请求
- `async_loader_tick()` — 主线程回调分发，每帧调用
- `async_loader_shutdown()` — 关闭线程池

**生命周期：**
1. 启动时创建 VFS 并初始化 loader（2 个 I/O 线程）
2. 主循环每帧 `tick()` 处理完成回调
3. 关闭时 `shutdown()` 等待所有请求完成并回收线程

---

## 15. 任务并行视锥剔除 (`engine/src/task/task.c/h` + `main.c`)

TaskSystem 提供 Chase-Lev work-stealing 线程池，支持任务依赖和优先级。主循环集成了并行可见性计算：

**NodeSphere 缓存：**
- 启动时预计算每个场景节点的包围球 `(cx, cy, cz, r)`
- 无效节点标记 `r = -1.0f`，跳过计算

**VisTaskCtx + vis_task_fn：**
- 将节点范围分为 `worker_count` 个 chunk
- 每个 chunk 执行视锥测试 + LOD 距离剔除
- 写入 `node_vis[]`（线程安全，每个索引独立）

**应用：** 前向渲染 + Deferred G-Buffer 的可见性循环

**音频监听者更新：** 主循环每帧调用 `audio_system_update` 同步相机位置和朝向到音频系统

**单元测试：** `tests/test_task.c` (6 测试用例)

覆盖：单任务、批量任务(100)、上下文传递、句柄提交、优先级、worker 计数查询。

---

## 16. 网络包序列化 (`engine/src/network/packet.c/h`)

小端序二进制包序列化协议，用于网络通信。

**包头布局（12 字节）：**
```
[sequence:4 LE][ack:4 LE][size:2 LE][type:1][flags:1]
```

**支持的类型：** `u8`, `u16`, `u32`, `f32`, 原始字节流

**特性：**
- 显式小端编码（主机字节序无关）
- 写边界检查（溢出保护）
- `PACKET_RELIABLE | PACKET_ORDERED` 标志位
- MTU 安全载荷（最大 1400 字节）

**单元测试：** `tests/test_packet.c` (15 测试用例，覆盖序列化/反序列化、边界检查、NULL 安全、截断处理)

覆盖：header 序列化/反序列化、各类型往返正确性、混合类型、溢出保护、空载荷。

---

## 17. 网络套接字模块 (`engine/src/network/network.c/h`)

跨平台 UDP/TCP 网络层（Linux: BSD sockets + poll, Windows: Winsock2 + WSAPoll）。

**核心 API：**
- `net_init()` / `net_shutdown()` — 平台初始化（Windows WSAStartup）
- `net_udp_create(bind_port)` — 创建 UDP 套接字
- `net_tcp_connect(host, port)` / `net_tcp_listen(port, backlog)` — TCP 连接/监听
- `net_tcp_accept(listener, out_addr)` — TCP 接受连接
- `net_send()` / `net_recv()` — TCP 收发
- `net_sendto()` / `net_recvfrom()` — UDP 收发（带地址）
- `net_set_nonblocking(s, nonblock)` — 非阻塞模式
- `net_poll(fds, count, timeout_ms)` — I/O 多路复用
- `net_address_resolve(hostname, port, out)` — DNS 解析

**特性：**
- 统一跨平台 API（`NetSocket` 不透明句柄）
- 非阻塞模式支持
- poll/WSAPoll 多路复用（小数组栈分配，大数组堆分配）
- IPv4 地址解析（getaddrinfo）

**单元测试：** `tests/test_network.c` (7 测试用例)

覆盖：init/shutdown、UDP 创建/关闭、地址解析、localhost 解析、UDP 回环收发、poll 超时、poll 可读检测。

---

## 模块依赖总览

```
┌─────────────────────────────────────────────────────┐
│                    Game Logic                         │
├─────────┬──────────┬──────────┬──────────┬──────────┤
│ Script  │  ECS     │ Physics  │  Audio   │  Task    │
├─────────┴──────────┴──────────┴──────────┴──────────┤
│              Renderer (56 files)                      │
├──────────────┬───────────────────────────────────────┤
│  Animation   │   Asset / VFS / Async Loader         │
├──────────────┴───────────────────────────────────────┤
│              Audio (miniaudio + 3D Spatial)          │
├──────────────────────────────────────────────────────┤
│              UI (Font + DebugUI)                      │
├──────────────────────────────────────────────────────┤
│              RHI (OpenGL / Vulkan)                    │
├──────────────────────────────────────────────────────┤
│              Network (UDP/TCP + Packet Serialization) │
├──────────────────────────────────────────────────────┤
│              Task System (Work-Stealing Pool)        │
├──────────────────────────────────────────────────────┤
│              Math                                     │
├──────────────────────────────────────────────────────┤
│              Platform (Window / Input / Time / FS)    │
├──────────────────────────────────────────────────────┤
│              Core (Types / Alloc / Log / Assert)      │
└──────────────────────────────────────────────────────┘
```
