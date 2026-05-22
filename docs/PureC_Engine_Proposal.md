# 纯 C (C11-C23) 跨平台游戏引擎方案

> 本文档为头脑风暴阶段的设计方案，将随讨论深入持续更新。

## 1. 为什么选择纯 C？

| 优势 | 说明 |
|------|------|
| **极致可移植** | C 编译器存在于几乎所有平台 — 主机、嵌入式、WebAssembly、裸机 |
| **ABI 稳定** | 无 name mangling，C ABI 是事实上的跨语言互操作标准 |
| **零隐式开销** | 无虚函数表、RTTI、异常处理的隐式成本 |
| **内存确定性** | 没有构造/析构的隐式调用，完全掌控分配时机 |
| **调试透明** | 无内联展开噩梦，gdb/lldb 直接可读 |
| **FFI 友好** | 任何语言（Rust/Zig/Swift/Python/Lua/WASM）都能直接调用 |

### 与 C++ 方案的对比

| 维度 | 纯 C | C++ |
|------|------|-----|
| 编译速度 | 快 2-5x | 慢 (模板展开) |
| ABI 稳定性 | 天然稳定 | 脆弱 (需 C 接口层) |
| 调试体验 | 透明，无隐藏调用 | 构造/析构/异常不可见 |
| 互操作 | 任何语言可直接调用 | 需 `extern "C"` 包装 |
| 表达力 | 宏 + `_Generic` 够用但不优雅 | 模板/概念/constraints 更优雅 |
| 生态 | 较小，但质量高 (stb 系列) | 极大 (STL, Boost, etc.) |
| 代码量 | 多 20-30% (显式管理) | 较少 (RAII/构造/析构) |
| 适用场景 | 底层/引擎/工具库 | 游戏逻辑/工具/编辑器 |

---

## 2. C11-C23 可用的关键特性

### 2.1 C11

```c
// 泛型选择 — 类型安全的多态
#define vec_len(v) _Generic((v), \
    float*:  vec_len_f, \
    double*: vec_len_d, \
    int*:    vec_len_i   \
)(v)

// 原子操作 — 无需平台特定 intrinsic
_Atomic uint32_t ref_count;

// 线程支持 — 标准化线程 (部分编译器)
#include <threads.h>
mtx_t lock;

// 匿名结构体/联合体
struct Transform {
    union {
        struct { float x, y, z; };
        float e[3];
    };
};

// 指定初始化器
Vec3 up = {.x = 0.0f, .y = 1.0f, .z = 0.0f};

// 复合字面量
void draw_line(Vec3 from, Vec3 to);
draw_line((Vec3){0,0,0}, (Vec3){1,1,1});

// 编译期断言
_Static_assert(sizeof(Mat4) == 64, "Mat4 must be 64 bytes");

// 灵活数组成员 (FAM)
struct VertexBuffer {
    size_t count;
    Vertex data[];
};
```

### 2.2 C17

C17 主要是缺陷修复和清理，无重大新特性。

### 2.3 C23 (核心新特性)

```c
// nullptr — 类型安全的空指针
typeof(nullptr) np = nullptr;  // nullptr_t, 不能隐式转为 int

// typeof / typeof_unqual
typeof(x) y = x;                // 推断类型
typeof_unqual(expr) *ptr;       // 去掉 cv 限定符

// auto 类型推断
auto mat = mat4_identity();     // 编译器推导类型

// constexpr
constexpr float PI = 3.14159265f;
constexpr int MAX_ENTITIES = 4096;
constexpr Vec3 WORLD_UP = {.x = 0, .y = 1, .z = 0};

// bool/true/false 成为关键字 (不再需要 stdbool.h)
bool is_visible(Entity* e);

// [[attributes]] 标准化属性语法
[[nodiscard]] int init(void);
[[maybe_unused]] static int backup;
[[deprecated("use new_func")]] void old_func(void);

// #embed — 直接嵌入二进制文件
const unsigned char shader[] = #embed "shader.spv"
const unsigned char shader_len = sizeof(shader);  // 自动计算

// 改进的位域
bool is_active : 1;

// 空初始化器
Vec3 origin = {};  // 零初始化
```

---

## 3. 架构总览

```
┌─────────────────────────────────────────────────────────────┐
│                      Game Layer                             │
│  (Lua/自定义脚本 + C 回调)                                   │
├─────────────────────────────────────────────────────────────┤
│                   Engine Framework                          │
│  ┌──────────┐ ┌──────────┐ ┌──────────┐ ┌───────────────┐  │
│  │   ECS    │ │  Scene   │ │   UI     │ │  Animation    │  │
│  │ Registry │ │  Graph   │ │  System  │ │    System     │  │
│  └──────────┘ └──────────┘ └──────────┘ └───────────────┘  │
├─────────────────────────────────────────────────────────────┤
│                    Core Systems                             │
│  ┌────────┐ ┌────────┐ ┌────────┐ ┌────────┐ ┌─────────┐  │
│  │Renderer│ │Physics │ │  Audio │ │Network │ │  Input  │  │
│  └────────┘ └────────┘ └────────┘ └────────┘ └─────────┘  │
├─────────────────────────────────────────────────────────────┤
│                   Platform Abstraction                      │
│  ┌──────────┐ ┌──────────┐ ┌──────────┐ ┌──────────────┐  │
│  │  Window  │ │   File   │ │  Thread  │ │    Memory    │  │
│  │  System  │ │  System  │ │  System  │ │   Allocator  │  │
│  └──────────┘ └──────────┘ └──────────┘ └──────────────┘  │
├─────────────────────────────────────────────────────────────┤
│                     RHI Backend                             │
│  ┌──────┐ ┌──────┐ ┌───────┐ ┌──────┐ ┌──────┐           │
│  │Vulkan│ │Metal │ │D3D12  │ │ GL   │ │WebGPU│           │
│  └──────┘ └──────┘ └───────┘ └──────┘ └──────┘           │
├─────────────────────────────────────────────────────────────┤
│                  OS / Hardware                              │
│  Win32 / POSIX / macOS / Console / WASM                    │
└─────────────────────────────────────────────────────────────┘
```

---

## 4. 项目目录结构

```
engine/
├── src/
│   ├── core/                 # 核心基础设施
│   │   ├── alloc.c/h         # 内存分配器
│   │   ├── array.c/h         # 动态数组 (泛型)
│   │   ├── hashmap.c/h       # 哈希表
│   │   ├── string.c/h        # 字符串 (slice 而非 \0)
│   │   ├── log.c/h           # 日志
│   │   └── assert.c/h        # 断言 (带上下文)
│   │
│   ├── platform/             # 平台抽象层
│   │   ├── platform.c/h      # 公共接口
│   │   ├── window_win32.c    # Windows
│   │   ├── window_cocoa.c    # macOS (ObjC runtime bridge)
│   │   ├── window_x11.c      # Linux X11
│   │   ├── window_wasm.c     # WASM (HTML5)
│   │   ├── filesystem.c/h    # 文件系统
│   │   ├── thread.c/h        # 线程抽象
│   │   └── time.c/h          # 高精度计时
│   │
│   ├── math/                 # 数学库
│   │   ├── vec.c/h           # 向量 (SSE/NEON/标量)
│   │   ├── mat.c/h           # 矩阵
│   │   ├── quat.c/h          # 四元数
│   │   ├── simd_sse.c        # SSE 实现
│   │   ├── simd_neon.c       # NEON 实现
│   │   └── simd_scalar.c     # 标量回退
│   │
│   ├── rhi/                  # 渲染硬件接口
│   │   ├── rhi.c/h           # 公共接口 + 后端选择
│   │   ├── rhi_vulkan.c      # Vulkan 后端
│   │   ├── rhi_metal.c       # Metal 后端 (C ↔ ObjC)
│   │   ├── rhi_d3d12.c       # DirectX 12 后端
│   │   ├── rhi_gl.c          # OpenGL 后端
│   │   └── rhi_webgpu.c      # WebGPU 后端
│   │
│   ├── renderer/             # 高级渲染器
│   │   ├── render_graph.c/h  # 渲染图
│   │   ├── scene.c/h         # 场景管理
│   │   ├── camera.c/h        # 相机
│   │   ├── material.c/h      # 材质系统
│   │   ├── mesh.c/h          # 网格管理
│   │   ├── texture.c/h       # 纹理管理
│   │   └── shader.c/h        # 着色器编译/转译
│   │
│   ├── ecs/                  # 实体组件系统
│   │   ├── world.c/h         # World (Archetype 存储)
│   │   ├── query.c/h         # 查询系统
│   │   └── system.c/h        # 系统调度
│   │
│   ├── physics/              # 物理引擎
│   │   ├── physics.c/h       # 公共接口
│   │   ├── broadphase.c/h    # 宽相碰撞
│   │   ├── narrowphase.c/h   # 窄相碰撞
│   │   ├── solver.c/h        # 约束求解
│   │   └── collision.c/h     # 碰撞检测
│   │
│   ├── audio/                # 音频系统
│   │   ├── audio.c/h         # 公共接口
│   │   ├── audio_miniaudio.c # miniaudio 后端
│   │   └── mixer.c/h         # 音频混合器
│   │
│   ├── asset/                # 资源管理
│   │   ├── asset.c/h         # 资源管理器
│   │   ├── loader_mesh.c     # 网格加载 (glTF/OBJ)
│   │   ├── loader_texture.c  # 纹理加载 (PNG/JPEG/KTX)
│   │   └── loader_audio.c    # 音频加载 (WAV/OGG)
│   │
│   ├── ui/                   # UI 系统
│   │   ├── ui.c/h            # 即时模式 GUI
│   │   └── text.c/h          # 文本渲染
│   │
│   ├── task/                 # 任务系统
│   │   ├── task.c/h          # 线程池 + Job 图
│   │   └── lockfree.c/h      # 无锁数据结构
│   │
│   └── engine.c/h            # 引擎入口/主循环
│
├── include/
│   └── engine/               # 公共头文件 (对外 API)
│       ├── engine.h
│       ├── rhi.h
│       ├── ecs.h
│       ├── math.h
│       └── ...
│
├── shaders/                  # 着色器源码
│   ├── common.glsl
│   ├── pbr.vert / pbr.frag
│   └── ...
│
├── external/                 # 第三方库 (单头文件优先)
│   ├── stb_image.h
│   ├── stb_truetype.h
│   ├── cgltf.h               # glTF 解析
│   ├── miniaudio.h           # 音频
│   ├── sv.h                  # 字符串视图
│   └── ...
│
├── tools/                    # 工具
│   ├── shader_compiler/      # 着色器编译 (glslang/SPIRV-Cross)
│   └── asset_packager/       # 资源打包
│
├── CMakeLists.txt            # 构建
├── Makefile                  # 备选构建
└── README.md
```

---

## 5. 核心子系统设计

### 5.1 内存管理 — 自定义分配器

```c
// alloc.h — 分配器接口
typedef struct Alloc {
    void* (*alloc)(struct Alloc* self, size_t size, size_t align);
    void  (*free)(struct Alloc* self, void* ptr, size_t size);
    void* (*realloc)(struct Alloc* self, void* ptr, size_t old, size_t new_size);
} Alloc;

// 利用 C23 typeof 实现类型安全的分配宏
#define alloc_new(a, T, ...)       ((T*)(a)->alloc((a), sizeof(T), alignof(T)))
#define alloc_array(a, T, count)   ((T*)(a)->alloc((a), sizeof(T)*(count), alignof(T)))
#define alloc_free(a, ptr, T)      ((a)->free((a), (ptr), sizeof(T)))

// 内置分配器实现
Alloc* alloc_heap(void);                          // 堆分配 (malloc/free)
Alloc* alloc_pool(size_t obj_size, size_t cap);    // 对象池
Alloc* alloc_arena(size_t size);                   // 线性竞技场
Alloc* alloc_frame(void);                          // 帧分配器 (每帧重置)
Alloc* alloc_stack(size_t size);                   // 栈式分配器
```

### 5.2 ECS (Entity Component System) — 数据导向

```c
// ecs.h — 核心类型
typedef uint32_t Entity;
typedef uint64_t ComponentMask;

// 组件 — 纯数据 POD，利用 C23 指定初始化
typedef struct {
    float position[3];
    float rotation[4]; // quaternion
    float scale[3];
} CTransform;

typedef struct {
    uint32_t mesh_id;
    uint32_t material_id;
    bool     cast_shadow;
    bool     visible;
} CMeshRenderer;

typedef struct {
    float velocity[3];
    float mass;
    float restitution;
} CRigidBody;

typedef struct {
    float fov;
    float near_plane;
    float far_plane;
    bool  active;
} CCamera;

// 组件注册 — C11 _Generic + X-Macro 实现
#define COMPONENT_LIST \
    X(CTransform,     Transform)     \
    X(CMeshRenderer,  MeshRenderer)  \
    X(CRigidBody,     RigidBody)     \
    X(CCamera,        Camera)

// 查询 — 位掩码匹配
typedef struct QueryResult {
    Entity*  entities;
    size_t   count;
} QueryResult;

QueryResult ecs_query(World* w, ComponentMask mask);
void* ecs_get(World* w, Entity e, ComponentType type);
void  ecs_set(World* w, Entity e, ComponentType type, void* data);

// 迭代 — 零开销
void update_physics(World* w, float dt) {
    auto view = ecs_view(w, CRigidBody | CTransform);
    while (ecs_view_next(&view)) {
        CTransform* t = ecs_view_get(&view, CTransform);
        CRigidBody* r = ecs_view_get(&view, CRigidBody);
        t->position[0] += r->velocity[0] * dt;
        t->position[1] += r->velocity[1] * dt;
        t->position[2] += r->velocity[2] * dt;
    }
}
```

### 5.3 RHI — 渲染硬件接口

```c
// rhi.h — 跨 API 抽象，句柄式设计
typedef struct { uint64_t id; } RHIBuffer;
typedef struct { uint64_t id; } RHITexture;
typedef struct { uint64_t id; } RHIPipeline;
typedef struct { uint64_t id; } RHIShader;
typedef struct { uint64_t id; } RHIFramebuffer;
typedef struct { uint64_t id; } RHIRenderPass;
typedef struct { uint64_t id; } RHIDescriptorSet;

// 后端枚举
typedef enum {
    RHI_BACKEND_VULKAN,
    RHI_BACKEND_METAL,      // via C bridge to ObjC runtime
    RHI_BACKEND_D3D12,
    RHI_BACKEND_OPENGL,
    RHI_BACKEND_WEBGPU,
} RHIBackend;

// 初始化配置
typedef struct {
    RHIBackend backend;
    bool       validation;
    bool       vsync;
    struct { uint32_t width, height; } resolution;
} RHIConfig;

// 核心接口 — 函数指针表 (vtable 替代)
typedef struct RHI {
    // Device
    bool     (*init)(RHIConfig cfg);
    void     (*shutdown)(void);

    // Command Buffer
    void     (*begin_frame)(void);
    void     (*end_frame)(void);
    void     (*begin_render_pass)(RHIRenderPass pass, RHIFramebuffer fb);
    void     (*end_render_pass)(void);

    // Resources
    RHIBuffer   (*create_buffer)(const RHIBufferDesc* desc);
    RHITexture  (*create_texture)(const RHITextureDesc* desc);
    RHIPipeline (*create_pipeline)(const RHIPipelineDesc* desc);
    RHIShader   (*create_shader)(const void* spirv, size_t size);
    void        (*destroy_buffer)(RHIBuffer buf);
    void        (*destroy_texture)(RHITexture tex);

    // Draw
    void     (*bind_pipeline)(RHIPipeline pipe);
    void     (*bind_descriptor_sets)(RHIDescriptorSet* sets, uint32_t count);
    void     (*bind_vertex_buffers)(RHIBuffer* bufs, uint32_t count);
    void     (*bind_index_buffer)(RHIBuffer buf, uint32_t offset);
    void     (*draw_indexed)(uint32_t index_count, uint32_t instance_count);
    void     (*dispatch)(uint32_t x, uint32_t y, uint32_t z);

    // Sync
    void     (*submit)(void);

    // Backend-specific
    void*    (*get_native_device)(void);  // VkDevice / id<MTLDevice> / ID3D12Device*
} RHI;

// 获取当前 RHI 后端
RHI* rhi_get(void);
```

### 5.4 平台抽象层

```c
// platform.h — 不透明结构 + 函数指针
typedef struct Platform Platform;

typedef enum {
    PLATFORM_WINDOWS,
    PLATFORM_MACOS,
    PLATFORM_LINUX,
    PLATFORM_ANDROID,
    PLATFORM_WASM,
} PlatformType;

typedef struct {
    PlatformType type;
    void (*on_resize)(uint32_t w, uint32_t h);
    void (*on_key)(int key, int action);
    void (*on_mouse)(float x, float y, int button, int action);
    void (*on_touch)(float x, float y, int action);
} PlatformConfig;

Platform* platform_create(PlatformConfig cfg);
void      platform_destroy(Platform* p);
bool      platform_poll(Platform* p);     // false = quit
double    platform_time(Platform* p);
void*     platform_window_native(Platform* p); // HWND / NSWindow / Window
void      platform_set_cursor(Platform* p, int cursor);
```

### 5.5 SIMD 数学库

```c
// math.h — 利用 _Generic 实现类型安全的 SIMD
#include <immintrin.h>  // SSE/AVX (x86)
// ARM: #include <arm_neon.h>

typedef struct { float e[4]; } Vec4;
typedef struct { float e[4][4]; } Mat4;
typedef struct { float e[4]; } Quat;

// 运行时 SIMD 分派 (检测 CPU 特性)
typedef struct MathOps {
    void  (*mat4_mul)(Mat4* out, const Mat4* a, const Mat4* b);
    void  (*mat4_proj)(Mat4* out, float fov, float aspect, float near, float far);
    void  (*mat4_lookat)(Mat4* out, Vec3 eye, Vec3 target, Vec3 up);
    float (*vec3_dot)(Vec3 a, Vec3 b);
    Vec3  (*vec3_cross)(Vec3 a, Vec3 b);
    Vec3  (*vec3_normalize)(Vec3 v);
} MathOps;

// 编译期选择最优实现
#if defined(__SSE2__)
    // SSE2 实现
#elif defined(__ARM_NEON)
    // NEON 实现
#else
    // 标量回退
#endif
```

### 5.6 线程 / 任务系统

```c
// task.h — 基于 C11 threads.h 或平台特定实现
typedef void (*TaskFunc)(void* data);

typedef struct {
    uint32_t worker_count;
    size_t   stack_size;
} TaskSystemConfig;

typedef struct TaskSystem TaskSystem;

// 并行 for — 分块执行
void task_parallel_for(
    TaskSystem* ts,
    size_t count,
    size_t chunk_size,
    void (*func)(size_t begin, size_t end, void* ctx),
    void* ctx
);

// Job 图 — 依赖链
typedef struct { uint64_t id; } JobHandle;
JobHandle task_submit(TaskSystem* ts, TaskFunc fn, void* data);
JobHandle task_submit_with_deps(TaskSystem* ts, TaskFunc fn, void* data,
                                JobHandle* deps, uint32_t dep_count);
void      task_wait(TaskSystem* ts, JobHandle handle);

// 无锁队列 (利用 _Atomic)
typedef struct {
    _Atomic uint64_t head;
    _Atomic uint64_t tail;
    void**   buffer;
    size_t   capacity;
} MPSCQueue; // Multi-Producer Single-Consumer
```

### 5.7 资源管线

```c
// asset.h — 类型擦除的资源句柄
typedef struct { uint64_t id; } AssetHandle;

typedef enum {
    ASSET_MESH,
    ASSET_TEXTURE,
    ASSET_SHADER,
    ASSET_AUDIO,
    ASSET_SCENE,
    ASSET_FONT,
} AssetType;

typedef struct {
    const char* path;
    AssetType   type;
    void*       (*loader)(const void* data, size_t size, void* ctx);
    void        (*unloader)(void* asset);
} AssetDesc;

typedef struct AssetManager {
    // Hash Map: path -> AssetHandle
    // 引用计数
    // 异步加载队列
    // 热重载监听
} AssetManager;

AssetHandle asset_load(AssetManager* am, const char* path);
void*       asset_get(AssetManager* am, AssetHandle h);
void        asset_release(AssetManager* am, AssetHandle h);
bool        asset_hot_reload(AssetManager* am, AssetHandle h);
```

---

## 6. 关键技术决策

| 领域 | 决策 | 理由 |
|------|------|------|
| **多态** | 函数指针表 (vtable) | C 的 OOP — 不依赖编译器特性 |
| **泛型** | `_Generic` + 宏 | C11 类型安全多态，替代 C++ 模板 |
| **封装** | 不透明指针 (`typedef struct X X`) | 零 ABI 耦合，真正的信息隐藏 |
| **错误处理** | 返回值 + error code enum | 无异常开销，调用者必须处理 |
| **字符串** | string slice (`ptr + len`) | 避免分配，零拷贝解析 |
| **容器** | 宏生成泛型容器 (vec_##T) | 零开销，编译期特化 |
| **SIMD** | 运行时分派 + 编译期分支 | 支持 SSE/AVX/NEON/标量回退 |
| **GPU API** | Vulkan-first + SPIR-V | 一次编译，Vulkan/D3D12/Metal(MoltenVK) 共用 |
| **构建** | CMake + compile_commands.json | 最大兼容性，支持 clangd |
| **第三方库** | 单头文件库优先 (stb, cgltf, miniaudio) | 零构建复杂度，直接 `#include` |
| **Metal 桥接** | C runtime 调用 ObjC (`objc_msgSend`) | 纯 C 编译，无需 ObjC 编译器 |

---

## 7. 实际挑战与应对

| 挑战 | 应对方案 |
|------|----------|
| **无构造/析构** | 显式 `init/destroy` 函数 + `defer` 宏模拟 RAII |
| **无命名空间** | 前缀约定 (`vec3_`, `mat4_`, `ecs_`, `rhi_`) |
| **无模板** | X-Macro + `_Generic` + 复合字面量 |
| **无异常** | Result 类型 `(T + error)` 或 error code 出参 |
| **无标准容器** | 自实现泛型动态数组/哈希表 (宏生成) |
| **ObjC 互操作** | `objc_getClass` + `objc_msgSend` 纯 C 调用 |
| **构建复杂度** | Unity Build 单编译单元 + 头文件分离 |
| **反射缺失** | 描述符系统 (手动注册字段偏移/类型) |
| **测试** | 自定义测试框架 (宏) 或 Unity 测试框架 |

---

## 8. 结论

纯 C 做引擎**完全可行且有价值**。

**适合场景**：
- 需要极致跨平台 (主机/嵌入式/WASM)
- 引擎作为库被多种语言绑定
- 追求编译速度和调试透明
- 团队偏好显式控制而非隐式魔法

**不适合场景**：
- 需要快速迭代的游戏逻辑层 — 建议引擎核心用 C，上层用 Lua/脚本驱动

---

> **变更日志**:
> - 初版 — 架构总览、子系统设计、技术决策
