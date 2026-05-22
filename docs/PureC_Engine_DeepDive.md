# 纯 C 引擎方案 — 深度模块审查与方案优选

> 本文档对 `PureC_Engine_Proposal.md` 中每个模块进行：
> 1. **缺陷与遗漏分析** — 原方案有什么问题
> 2. **替代方案对比** — 可行方案的性能/复杂度权衡
> 3. **最优方案选择** — 最终推荐及理由
>
> 将随讨论持续更新。

---

## 模块 1: 内存管理 (alloc)

### 1.1 原方案缺陷

| # | 缺陷 | 严重度 | 说明 |
|---|------|--------|------|
| 1 | **函数指针间接调用** | 高 | 每次分配都经过 vtable 间接跳转，破坏分支预测，热路径上代价显著 |
| 2 | **无线程安全策略** | 高 | 未指定分配器是否线程安全，多线程场景下需外部加锁——性能灾难 |
| 3 | **alloc_frame() 无状态存储** | 中 | 帧分配器需要持久状态（水位指针），但接口未体现如何管理多帧状态 |
| 4 | **缺少调试/追踪分配器** | 中 | 无 memory tracking、leak detection、use-after-free 检测能力 |
| 5 | **alloc_free 需要传 T 类型** | 低 | 宏 `alloc_free(a, ptr, T)` 要求调用者记住类型，API 不够人机工程 |
| 6 | **无对齐保证** | 中 | 虽然 alignof(T) 正确，但未考虑 GPU 缓冲区的特殊对齐需求 (256B+) |
| 7 | **realloc 接口不完整** | 低 | 缺少对齐参数，且未处理 realloc 可能的地址变更通知 |

### 1.2 替代方案对比

#### 方案 A: VTable 函数指针 (原方案)

```c
typedef struct Alloc {
    void* (*alloc)(struct Alloc* self, size_t size, size_t align);
    void  (*free)(struct Alloc* self, void* ptr, size_t size);
} Alloc;
```

- **性能**: 每次调用 1 次间接跳转 (~3-5ns 开销)
- **灵活性**: 运行时可切换分配器
- **内联**: 不可能内联
- **复杂度**: 低

#### 方案 B: 内联静态分配器 (每分配器类型独立函数)

```c
// arena.h — 每种分配器是独立的头文件，全部 inline
static inline void* arena_alloc(Arena* a, size_t size, size_t align) {
    // 直接实现，无间接调用
    size_t aligned = (a->offset + align - 1) & ~(align - 1);
    a->offset = aligned + size;
    return (char*)a->buffer + aligned;
}
```

- **性能**: 零开销，完全内联
- **灵活性**: 编译期确定分配器类型
- **内联**: 完全内联
- **复杂度**: 中 (每个分配器独立 API)

#### 方案 C: 宏多态 + 编译期分派

```c
#define alloc(a, size, align) _Generic((a), \
    Arena*:   arena_alloc, \
    Pool*:    pool_alloc, \
    Heap*:    heap_alloc   \
)((a), (size), (align))
```

- **性能**: 编译期分派，零间接调用
- **灵活性**: 添加新分配器需修改宏
- **内联**: 可能内联
- **复杂度**: 中

#### 方案 D: Scratch Pad 线性分配 + 双缓冲

```c
// 每帧两个 buffer 交替使用，当前帧分配，上一帧释放
typedef struct {
    void* buffers[2];
    size_t offset[2];
    size_t capacity;
    _Atomic int current;  // 当前帧索引
} ScratchPad;
```

### 1.3 最优方案: B + A 混合 (推荐)

**核心原则**: 热路径内联，冷路径 vtable。

```
热路径 (每帧数千次调用):
  - Arena/Frame/ScratchPad → 方案 B (头文件 inline 函数)
  - 这些分配器逻辑极简 (移动指针)，内联后 1-2 条指令

冷路径 (低频调用):
  - Heap/Pool/自定义 → 方案 A (vtable)
  - 复杂分配器逻辑不值得内联膨胀
```

**补充设计**:

```c
// === 线程安全策略 ===
// 每线程持有独立的 Arena/Frame 分配器，无锁
// 全局分配器 (Heap) 通过内部 mutex 保护

// === 调试分配器 ===
typedef struct {
    Alloc    base;           // 可嵌入 vtable
    Alloc*   inner;          // 包装的真实分配器
    uint64_t total_allocated;
    uint64_t peak_allocated;
    uint64_t alloc_count;
    uint64_t free_count;
    // 可选: 记录每次分配的 callstack
} DebugAlloc;

// === GPU 对齐工具 ===
#define GPU_ALIGN 256
static inline void* arena_alloc_gpu(Arena* a, size_t size) {
    return arena_alloc(a, size, GPU_ALIGN);
}
```

---

## 模块 2: ECS (Entity Component System)

### 2.1 原方案缺陷

| # | 缺陷 | 严重度 | 说明 |
|---|------|--------|------|
| 1 | **ComponentMask = uint64_t → 最多 64 种组件** | 致命 | 实际引擎轻松超过 64 种。需要更大的掩码或改用 Archetype 模式 |
| 2 | **无 Archetype 存储** | 致命 | 原方案暗示"位掩码匹配"但未说明组件数据如何物理布局。无 Archetype 意味着遍历性能差 |
| 3 | **无组件添加/删除策略** | 高 | 从 Entity 添加/删除组件时，需要将实体在 Archetype 间移动，原方案完全未提及 |
| 4 | **无 SOA 布局** | 高 | 连续内存遍历的关键——组件应该按列存储，而非按行 |
| 5 | **无查询缓存** | 中 | 每次查询都遍历所有实体代价太大。需要预编译查询 + 增量更新 |
| 6 | **无组件生命周期** | 中 | 缺少 OnAdd/OnRemove/OnDestroy 回调 (用于绑定物理体、初始化状态等) |
| 7 | **无世界切分** | 低 | 没有 World/Scene 的概念分离，难以支持多场景或场景流式加载 |
| 8 | **ecs_view_next/get 无类型安全** | 中 | 返回 void* 需要手动转型，C23 auto 在此场景也救不了 |

### 2.2 替代方案对比

#### 方案 A: 稀疏集 (Sparse Set, EnTT 风格)

```
每个组件类型独立一个 SparseSet:
  Entity → 索引映射 (稀疏数组)
  组件数据连续存储 (密集数组)

查询: 交叉多个 SparseSet 的 entity 列表
```

- **添加/删除**: O(1) swap-and-pop
- **遍历**: 连续内存，但交叉查询需要分支
- **单个组件访问**: O(1) 直接索引
- **内存**: 每个稀疏集独立，有额外开销
- **复杂度**: 中

#### 方案 B: Archetype + Chunk (Flecs/ECS-backward 风格, 推荐)

```
World → Archetype Table
  每个 Archetype = 一组固定的组件组合
  每个 Archetype 包含多个 Chunk (16KB 固定块)
  Chunk 内: SOA 布局, 组件列式存储

Entity = { archetype_index, chunk_index, index_in_chunk }

查询: 匹配 Archetype (非逐实体匹配) → 遍历匹配的 Archetype 的所有 Chunk
```

- **添加/删除**: 需要在 Archetype 间迁移实体 (代价较高)
- **遍历**: 最优 — 完全连续内存，零分支，SIMD 友好
- **单个组件访问**: 两次间接 (archetype → chunk → component)
- **内存**: Chunk 粒度分配，浪费少
- **复杂度**: 高

#### 方案 C: 位掩码 + 组件池 (原方案改进)

```
ComponentMask 扩展为 uint64_t[4] (256 种组件)
每个组件类型一个 Pool (连续数组)
Entity 是数组索引

查询: 遍历所有 entity，检查 mask 是否匹配
```

- **添加/删除**: O(1) 设置位
- **遍历**: 差 — 需要遍历所有实体检查掩码
- **内存**: 简单，但缓存不友好
- **复杂度**: 低

### 2.3 最优方案: B (Archetype + Chunk)

**理由**: 游戏引擎 90% 的性能瓶颈在遍历，Archetype 的遍历性能碾压其他方案。添加/删除的开销在帧预算中可忽略 (每帧通常 < 100 次添加/删除 vs 数万次遍历)。

**改进设计**:

```c
// === 句柄使用代际计数器防止悬垂引用 ===
typedef struct {
    uint32_t index;     // 实体索引
    uint32_t generation; // 代际 (回收后递增)
} Entity;

// === Archetype 键 — 用排序后的组件 ID 数组标识 ===
typedef struct {
    ComponentType* types;  // 排序后的组件类型数组
    uint32_t       count;
} ArchetypeKey;

// === Chunk — 固定 16KB, SOA 布局 ===
#define CHUNK_SIZE (16 * 1024)
typedef struct Chunk {
    struct Chunk* next;          // 链表
    uint32_t      count;         // 已用槽位数
    uint32_t      capacity;      // 最大槽位数 (由组件大小决定)
    uint32_t      entities[];    // Entity 列表 (代际验证)
    // 紧随其后: 各组件列 (SOA)
    // 偏移量由 Archetype 的 layout 描述
} Chunk;

// === Archetype ===
typedef struct {
    ArchetypeKey    key;
    Chunk*          chunks;          // Chunk 链表
    uint32_t*       offsets;         // 每个组件在 Chunk 中的字节偏移
    uint32_t        chunk_capacity;  // 每个 Chunk 的实体容量
    uint32_t        total_count;     // 所有 Chunk 中实体总数
    // Archetype Graph 边: 添加/删除组件后的目标 Archetype
    struct {
        ComponentType component;
        struct Archetype* target;
    }* edges_add;
    struct {
        ComponentType component;
        struct Archetype* target;
    }* edges_remove;
} Archetype;

// === 查询 — 预编译，带缓存 ===
typedef struct {
    Archetype** matching;     // 匹配的 Archetype 列表
    uint32_t    match_count;
    // 可选: 迭代器缓存
} Query;

// === 迭代 — 高效的 chunk 级遍历 ===
typedef struct {
    Query*     query;
    uint32_t   arch_index;    // 当前 Archetype 索引
    Chunk*     chunk;         // 当前 Chunk
    uint32_t   index;         // Chunk 内索引
} QueryIter;

// 创建迭代器
QueryIter ecs_query_begin(World* w, ComponentMask mask);
bool      ecs_query_next(QueryIter* it);   // false = 结束

// 类型安全的组件获取 — 编译期通过宏检查类型
#define ECS_GET(it, T) ((T*)chunk_get_component((it).chunk, (it).index, component_id(T)))

// 使用示例:
void update_transforms(World* w, float dt) {
    QueryIter it = ecs_query_begin(w, CTransform | CRigidBody);
    while (ecs_query_next(&it)) {
        CTransform* t = ECS_GET(it, CTransform);
        CRigidBody* r = ECS_GET(it, CRigidBody);
        t->position[0] += r->velocity[0] * dt;
        // ...
    }
}
```

**Archetype Graph 优化**: 预计算所有 add/remove 边，使组件操作变为 O(1) 查表:

```
[Transform] ──add RigidBody──→ [Transform, RigidBody]
[Transform, RigidBody] ──remove RigidBody──→ [Transform]
[Transform, RigidBody] ──add MeshRenderer──→ [Transform, RigidBody, MeshRenderer]
```

---

## 模块 3: RHI (渲染硬件接口)

### 3.1 原方案缺陷

| # | 缺陷 | 严重度 | 说明 |
|---|------|--------|------|
| 1 | **全局单例 (rhi_get)** | 高 | 无法支持多 GPU、多窗口渲染；隐式状态难以调试 |
| 2 | **句柄无代际计数** | 高 | uint64_t id 无 generation，释放后复用可能引用到错误资源 |
| 3 | **无 Command Buffer 抽象** | 致命 | 现代 GPU API (Vulkan/D3D12/Metal) 都是命令缓冲区模型，原方案的全局 begin/end 不够 |
| 4 | **无同步原语** | 致命 | 缺少 Fence/Semaphore，无法实现 CPU-GPU 同步 |
| 5 | **无描述符管理** | 高 | 缺少 DescriptorSet 分配/池化策略，这是 Vulkan/D3D12 最复杂的部分 |
| 6 | **无 Swapchain 抽象** | 高 | 缺少交换链/表面管理 |
| 7 | **无内存预算** | 中 | GPU 显存管理未提及 |
| 8 | **init/shutdown 在 vtable 中** | 低 | 初始化应该只调用一次，不应在每次 API 调用的 vtable 中 |

### 3.2 替代方案对比

#### 方案 A: 全局 VTable (原方案)

- 优点: 简单
- 缺点: 隐式状态、单例、无多设备

#### 方案 B: 上下文传递 (Context-Passed)

```c
typedef struct RHIDevice RHIDevice;
typedef struct RHIContext RHIContext;

// Device 代表物理 GPU
RHIDevice* rhi_create_device(RHIBackend backend, RHIConfig cfg);
void       rhi_destroy_device(RHIDevice* dev);

// Context = 命令录制上下文 (可多线程并行录制)
RHIContext* rhi_create_context(RHIDevice* dev);
void        rhi_destroy_context(RHIContext* ctx);

// 所有操作通过 context 进行
void rhi_begin_render_pass(RHIContext* ctx, ...);
void rhi_draw_indexed(RHIContext* ctx, ...);
```

- 优点: 显式状态、多设备、多线程录制
- 缺点: 每个函数多一个参数

#### 方案 C: bgfx 风格 (命令提交模型)

```c
// 跨平台编码为内部命令缓冲区
void bgfx_set_vertex_buffer(uint8_t stream, BGFXHandle hb, ...);
void bgfx_submit(uint16_t view, BGFXHandle program);
```

- 优点: 极简 API，自动处理同步
- 缺点: 框架化程度高，灵活性低

### 3.3 最优方案: B (上下文传递) + 代际句柄

```c
// === 代际句柄 — 防止悬垂引用 ===
typedef struct {
    uint32_t index;       // 资源池索引
    uint32_t generation;  // 代际 (释放后递增)
} RHIHandle;

_Static_assert(sizeof(RHIHandle) == 8, "RHIHandle must be 8 bytes");

// 每种资源类型是不同的 typedef (类型安全)
typedef RHIHandle RHIBuffer;
typedef RHIHandle RHITexture;
typedef RHIHandle RHIPipeline;
// ...

// === Device — 物理设备抽象 ===
typedef struct RHIDevice {
    const struct RHIDeviceVTable* vtable;
    void* backend_data;  // VkDevice / id<MTLDevice> / ID3D12Device*
    
    // 资源池
    struct {
        RHIHandle*       handles;
        void**           resources;    // 实际资源对象
        uint32_t*        generations;
        uint32_t         capacity;
        _Atomic uint32_t count;
    } pools[RHI_RESOURCE_TYPE_COUNT];
} RHIDevice;

// === Command Buffer — 命令录制 ===
typedef struct {
    RHIDevice* device;
    void*      backend_cmd;  // VkCommandBuffer / id<MTLCommandBuffer> / ID3D12GraphicsCommandList*
    bool       recording;
} RHICommandBuffer;

// === 同步原语 ===
typedef RHIHandle RHIFence;
typedef RHIHandle RHISemaphore;

// === 核心接口 (非 vtable，直接函数) ===
// Device
RHIDevice* rhi_device_create(RHIBackend backend, const RHIConfig* cfg);
void       rhi_device_destroy(RHIDevice* dev);
void       rhi_device_wait_idle(RHIDevice* dev);

// Swapchain
typedef RHIHandle RHISwapchain;
RHISwapchain rhi_swapchain_create(RHIDevice* dev, void* window_native, uint32_t w, uint32_t h);
RHITexture  rhi_swapchain_acquire(RHIDevice* dev, RHISwapchain sc, RHISemaphore signal);
void        rhi_swapchain_present(RHIDevice* dev, RHISwapchain sc, RHISemaphore wait);

// Command Buffer
RHICommandBuffer rhi_cmd_begin(RHIDevice* dev);
void             rhi_cmd_end(RHICommandBuffer cmd);
void             rhi_cmd_begin_render_pass(RHICommandBuffer cmd, const RHIRenderPassInfo* info);
void             rhi_cmd_end_render_pass(RHICommandBuffer cmd);
void             rhi_cmd_bind_pipeline(RHICommandBuffer cmd, RHIPipeline pipe);
void             rhi_cmd_bind_descriptor_set(RHICommandBuffer cmd, RHIDescriptorSet set);
void             rhi_cmd_draw_indexed(RHICommandBuffer cmd, uint32_t index_count, uint32_t instance_count);

// Resource creation
RHIBuffer   rhi_buffer_create(RHIDevice* dev, const RHIBufferDesc* desc);
RHITexture  rhi_texture_create(RHIDevice* dev, const RHITextureDesc* desc);
RHIPipeline rhi_pipeline_create(RHIDevice* dev, const RHIPipelineDesc* desc);
RHIShader   rhi_shader_create(RHIDevice* dev, const void* spirv, size_t size);

// Descriptor management
typedef RHIHandle RHIDescriptorPool;
RHIDescriptorPool rhi_descriptor_pool_create(RHIDevice* dev, const RHIDescriptorPoolDesc* desc);
RHIDescriptorSet  rhi_descriptor_set_alloc(RHIDevice* dev, RHIDescriptorPool pool, RHIDescriptorSetLayout layout);
void              rhi_descriptor_set_write(RHIDevice* dev, RHIDescriptorSet set, ...);

// Sync
RHIFence     rhi_fence_create(RHIDevice* dev);
void         rhi_fence_wait(RHIDevice* dev, RHIFence fence);
RHISemaphore rhi_semaphore_create(RHIDevice* dev);

// Submit
void rhi_queue_submit(RHIDevice* dev, RHICommandBuffer* cmds, uint32_t count,
                      RHISemaphore* wait, uint32_t wait_count,
                      RHISemaphore* signal, uint32_t signal_count,
                      RHIFence fence);

// Destroy
void rhi_buffer_destroy(RHIDevice* dev, RHIBuffer buf);
void rhi_texture_destroy(RHIDevice* dev, RHITexture tex);
// ...
```

**关键设计决策**:
1. **Device 为中心**，非全局单例 — 支持多 GPU
2. **代际句柄** — 安全的资源引用
3. **Command Buffer 独立** — 支持多线程命令录制
4. **显式同步** — Semaphore/Fence 完整暴露
5. **Descriptor Pool** — 显式池化管理
6. **VTable 仅在 Device 内部** — 外部 API 是直接函数调用，内部通过 vtable 分派到后端

---

## 模块 4: SIMD 数学库

### 4.1 原方案缺陷

| # | 缺陷 | 严重度 | 说明 |
|---|------|--------|------|
| 1 | **运行时函数指针分派** | 致命 | 每帧数万次数学调用，每次间接跳转 = 缓存 miss + 分支预测失败。实测性能损失可达 3-10x |
| 2 | **vtable 包含所有数学函数** | 高 | 结构体巨大 (几十个函数指针)，首次访问触发整块 cache line 加载 |
| 3 | **无 SoA (Structure of Arrays) 数学** | 高 | 批量变换 (骨骼动画、粒子) 需要 SoA 布局的 SIMD 运算，原方案全是 AoS |
| 4 | **矩阵存储惯例未指定** | 高 | 行主序 vs 列主序直接决定 SIMD 运算能否高效进行 |
| 5 | **无定点数/Q15/Q31 支持** | 低 | 某些平台 (低端嵌入式) 可能需要 |
| 6 | **无 SIMD 宽度抽象** | 中 | SSE=4 float, AVX=8 float, NEON=4 float — 统一为 4 浪费 AVX |

### 4.2 替代方案对比

#### 方案 A: 运行时 VTable (原方案) — 否决

- 性能: 差 (间接调用开销)
- 适用: 需要运行时切换 SIMD 级别时

#### 方案 B: 编译期 `#ifdef` + `static inline` (推荐)

```c
// math_simd.h — 编译期选择, 全部 static inline

#if defined(__AVX2__)
    #define SIMDX 8
    typedef __m256  simdf;
    // ...
#elif defined(__SSE2__)
    #define SIMDX 4
    typedef __m128  simdf;
    // ...
#elif defined(__ARM_NEON)
    #define SIMDX 4
    typedef float32x4_t simdf;
    // ...
#else
    #define SIMDX 4
    typedef struct { float e[4]; } simdf;
#endif

// 核心操作 — 全部 inline
static inline simdf simdf_load(const float* p) {
#if defined(__SSE2__)
    return _mm_loadu_ps(p);
#elif defined(__ARM_NEON)
    return vld1q_f32(p);
#else
    simdf r; for(int i=0;i<4;i++) r.e[i]=p[i]; return r;
#endif
}

static inline simdf simdf_mul(simdf a, simdf b) {
#if defined(__SSE2__)
    return _mm_mul_ps(a, b);
#elif defined(__ARM_NEON)
    return vmulq_f32(a, b);
#else
    simdf r; for(int i=0;i<4;i++) r.e[i]=a.e[i]*b.e[i]; return r;
#endif
}

// 高级数学 — 基于 simdf 原语构建，不直接使用平台 intrinsic
static inline Mat4 mat4_mul(Mat4 a, Mat4 b) {
    Mat4 out;
    for (int i = 0; i < 4; i++) {
        simdf row = simdf_load(&b.e[i][0]);
        simdf col0 = simdf_broadcast(a.e[0][i]);
        simdf col1 = simdf_broadcast(a.e[1][i]);
        simdf col2 = simdf_broadcast(a.e[2][i]);
        simdf col3 = simdf_broadcast(a.e[3][i]);
        simdf result = simdf_add(simdf_add(
            simdf_mul(col0, simdf_shuffle(row,0,0,0,0)),
            simdf_mul(col1, simdf_shuffle(row,1,1,1,1))),
            simdf_add(
            simdf_mul(col2, simdf_shuffle(row,2,2,2,2)),
            simdf_mul(col3, simdf_shuffle(row,3,3,3,3))));
        simdf_store(&out.e[i][0], result);
    }
    return out;
}
```

- 性能: 最优 (完全内联, 零间接)
- 灵活性: 编译期确定

#### 方案 C: GCC IFUNC (间接函数)

```c
// 运行时解析一次，之后直接调用，零间接开销
__attribute__((ifunc("resolve_mat4_mul")))
void mat4_mul(Mat4* out, const Mat4* a, const Mat4* b);

static void* resolve_mat4_mul(void) {
    if (__builtin_cpu_supports("avx2")) return mat4_mul_avx2;
    if (__builtin_cpu_supports("sse2")) return mat4_mul_sse2;
    return mat4_mul_scalar;
}
```

- 性能: 接近方案 B (仅首次调用有开销)
- 缺点: 仅 GCC/Clang 支持，不可移植

### 4.3 最优方案: B (编译期 `#ifdef` + `static inline`)

**补充设计 — SoA 批量运算**:

```c
// === 批量变换 — SoA 布局用于粒子/骨骼等 ===
typedef struct {
    simdf x;  // 4 个实体的 x 分量
    simdf y;
    simdf z;
} SoaVec3;

static inline SoaVec3 soa_vec3_add(SoaVec3 a, SoaVec3 b) {
    return (SoaVec3){
        .x = simdf_add(a.x, b.x),
        .y = simdf_add(a.y, b.y),
        .z = simdf_add(a.z, b.z),
    };
}

// 批量矩阵变换 — 一次处理 SIMDX 个顶点
void mat4_transform_points_soar(const Mat4* m, const float* in, float* out, uint32_t count);
```

**矩阵惯例**: 列主序 (Column-Major)，与 OpenGL/Vulkan/Metal/DirectX (via transpose) 一致。

---

## 模块 5: 任务系统

### 5.1 原方案缺陷

| # | 缺陷 | 严重度 | 说明 |
|---|------|--------|------|
| 1 | **MPSC 而非 MPMC** | 高 | 工作窃取需要 MPMC (多生产者多消费者) 队列 |
| 2 | **无工作窃取** | 致命 | 无窃取 = 负载不均衡 = 线程空转。这是现代任务系统的核心 |
| 3 | **无 Fiber/协程考虑** | 中 | 等待任务完成时，当前线程阻塞而非切换。高延迟场景效率低 |
| 4 | **无优先级** | 中 | 渲染任务和后台加载任务混在一起 |
| 5 | **无主线程亲和性** | 高 | 平台调用 (窗口消息、输入) 必须在主线程，无调度保证 |
| 6 | **Job Handle 无代际** | 低 | 复用可能等待到错误的 job |

### 5.2 替代方案对比

#### 方案 A: 简单线程池 + 全局队列 (原方案)

- 优点: 简单
- 缺点: 锁竞争严重，无负载均衡

#### 方案 B: Work-Stealing Deque (Chase-Lev, 推荐)

```
每个 Worker 线程有自己的双端队列:
  - 本线程 push/pop 从尾部操作 (LIFO, 无锁)
  - 其他线程从头部窃取 (FIFO, CAS)

全局队列: 用于非亲和性任务
```

- 性能: 最优 — 无锁操作，缓存友好
- 负载均衡: 自动窃取
- 复杂度: 高

#### 方案 C: Fiber-Based (Naughty Dog 风格)

- 性能: 等待时不阻塞 OS 线程，切换到其他 job
- 缺点: 依赖平台 fiber API (或 ucontext)，WASM 不支持

### 5.3 最优方案: B (Work-Stealing Deque)

```c
// === Chase-Lev 无锁双端队列 ===
typedef struct {
    _Atomic uint64_t    top;
    _Atomic uint64_t    bottom;
    _Atomic void**      buffer;    // 环形缓冲区
    uint64_t            capacity;  // 必须是 2 的幂
} WorkStealingDeque;

void   ws_deque_push(WorkStealingDeque* q, void* job);    // 仅 owner 调用
void*  ws_deque_pop(WorkStealingDeque* q);                 // 仅 owner 调用
void*  ws_deque_steal(WorkStealingDeque* q);               // 其他线程调用

// === Task System ===
typedef struct {
    // 每 worker 一个 deque
    WorkStealingDeque*  worker_queues;   // [worker_count]
    thrd_t*             worker_threads;  // [worker_count]
    _Atomic bool        running;
    
    // 全局低优先级队列
    MPSCQueue           global_queue;
    
    // 主线程索引 (固定为 0)
    uint32_t            main_thread_id;
} TaskSystem;

// === Job 定义 ===
typedef struct {
    TaskFunc    fn;
    void*       data;
    _Atomic int unfinished_count;  // 用于依赖计数
    JobHandle*  parent;            // 父 job (用于嵌套等待)
} Job;

// === API ===
TaskSystem* task_system_create(uint32_t worker_count);
void        task_system_destroy(TaskSystem* ts);

// 提交 job
JobHandle task_submit(TaskSystem* ts, TaskFunc fn, void* data);
JobHandle task_submit_n(TaskSystem* ts, TaskFunc fn, void** datas, uint32_t count);

// 带依赖
JobHandle task_submit_after(TaskSystem* ts, TaskFunc fn, void* data,
                            const JobHandle* deps, uint32_t dep_count);

// Parallel for — 自动分块到 worker
void task_parallel_for(TaskSystem* ts,
                       uint32_t count, uint32_t chunk_size,
                       void (*fn)(uint32_t begin, uint32_t end, void* ctx),
                       void* ctx);

// 等待 — 当前线程参与执行 job (而非空转)
void task_wait(TaskSystem* ts, JobHandle handle);
// wait 内部循环: 检查目标 job 是否完成 → 否则从自己/别人的队列偷一个 job 执行 → 重复

// 主线程帧同步
void task_frame_start(TaskSystem* ts);  // 标记帧开始
void task_frame_end(TaskSystem* ts);    // 等待所有帧内 job 完成
```

**关键设计点**:
1. **wait 时参与工作** — 不会阻塞，而是帮助完成其他 job
2. **自动分块** — parallel_for 根据核心数自动计算 chunk_size
3. **主线程亲和** — 主线程的 deque 可以放入必须在主线程执行的任务

---

## 模块 6: 平台抽象

### 6.1 原方案缺陷

| # | 缺陷 | 严重度 | 说明 |
|---|------|--------|------|
| 1 | **回调事件模型** | 高 | 回调在平台线程触发，引擎状态可能不一致。需要事件队列 |
| 2 | **无输入状态快照** | 高 | 缺少"本帧按键状态"查询 (key_down_this_frame vs key_held) |
| 3 | **无手柄/控制器支持** | 高 | 现代游戏必备 |
| 4 | **无剪贴板/拖拽/IME** | 中 | 编辑器和 UI 需要这些功能 |
| 5 | **window_native 返回 void*** | 低 | 类型不安全 |
| 6 | **无多显示器支持** | 低 | |
| 7 | **无全屏/窗口模式切换** | 中 | |

### 6.2 最优方案: 事件队列 + 输入状态快照 (双模式)

```c
// === 事件队列 — 平台线程推入，主线程消费 ===
typedef enum {
    EVENT_KEY,
    EVENT_MOUSE_BUTTON,
    EVENT_MOUSE_MOVE,
    EVENT_MOUSE_SCROLL,
    EVENT_TOUCH,
    EVENT_GAMEPAD,
    EVENT_WINDOW_RESIZE,
    EVENT_WINDOW_FOCUS,
    EVENT_QUIT,
} EventType;

typedef struct {
    EventType type;
    uint64_t  timestamp;  // 微秒
    union {
        struct { int key; int action; int mods; } key;
        struct { float x, y; int button; int action; } mouse_button;
        struct { float x, y; } mouse_move;
        struct { float dx, dy; } scroll;
        struct { float x, y; int action; int finger_id; } touch;
        struct { int gamepad_id; int button; int action; float axis[6]; } gamepad;
        struct { uint32_t w, h; } resize;
        struct { bool focused; } focus;
    };
} PlatformEvent;

typedef struct {
    PlatformEvent* events;
    _Atomic uint64_t write_head;  // 平台线程写入
    uint64_t        read_head;    // 主线程读取
    size_t          capacity;
} EventRingBuffer;  // SPSC 无锁环形缓冲区

// === 输入状态快照 — 每帧一份 ===
typedef struct {
    uint8_t  keys[512];           // 当前帧: 0=释放, 1=按下, 2=按住, 3=本帧按下
    float    mouse_x, mouse_y;
    float    mouse_dx, mouse_dy;
    float    scroll_dx, scroll_dy;
    
    // 手柄
    struct {
        bool     connected;
        float    axes[6];        // 左XY, 右XY, 左右trigger
        uint8_t  buttons[16];
    } gamepads[4];
    
    uint64_t frame_number;       // 快照的帧号
} InputState;

// === Platform API ===
typedef struct Platform Platform;

Platform* platform_create(const PlatformConfig* cfg);
void      platform_destroy(Platform* p);

// 主循环:
// 1. platform_poll() — 处理平台消息，推送事件到队列
// 2. platform_process_events() — 主线程消费事件，更新 InputState
// 3. 使用 input_state 查询

bool      platform_poll(Platform* p);
void      platform_process_events(Platform* p);
const InputState* platform_input(Platform* p);  // 只读快照

// 便捷查询宏
#define input_key_down(state, key)    ((state)->keys[key] & 1)
#define input_key_pressed(state, key) ((state)->keys[key] == 3)
#define input_key_held(state, key)    ((state)->keys[key] == 2)

// 窗口操作
void   platform_set_title(Platform* p, const char* title);
void   platform_set_size(Platform* p, uint32_t w, uint32_t h);
void   platform_set_fullscreen(Platform* p, bool fullscreen);
double platform_time(Platform* p);  // 高精度计时
void*  platform_window_native(Platform* p);

// 文件系统
typedef struct { /* ... */ } FileHandle;
bool      file_read(const char* path, void** out_data, size_t* out_size);
bool      file_write(const char* path, const void* data, size_t size);
bool      file_exists(const char* path);
```

---

## 模块 7: 资源管线

### 7.1 原方案缺陷

| # | 缺陷 | 严重度 | 说明 |
|---|------|--------|------|
| 1 | **无依赖追踪** | 致命 | Mesh 引用 Material 引用 Texture — 必须拓扑排序加载 |
| 2 | **无异步加载** | 高 | 原方案 asset_load 看起来是同步的 |
| 3 | **无优先级** | 中 | 前景资源应优先于背景加载 |
| 4 | **无格式版本控制** | 中 | 资源格式变更后的迁移策略 |
| 5 | **无资源引用计数** | 中 | 何时释放资源不明确 |
| 6 | **无虚拟文件系统** | 中 | 无法从包文件/pak/zip 加载 |
| 7 | **无热重载实现策略** | 低 | 仅声明了 API，未说明如何实现 |

### 7.2 最优方案: VFS + 依赖图 + 异步加载

```c
// === 虚拟文件系统 ===
typedef struct VFS VFS;

VFS*   vfs_create(void);
void   vfs_destroy(VFS* vfs);
void   vfs_mount(VFS* vfs, const char* mount_point, const char* archive_path);
       // 支持挂载: 目录、.pak、.zip

typedef struct {
    const uint8_t* data;  // 内存映射或缓冲区指针
    size_t         size;
} VFSFile;

bool    vfs_open(VFS* vfs, const char* path, VFSFile* out_file);
void    vfs_close(VFSFile* file);

// === 资源句柄 — 带代际和状态 ===
typedef struct {
    uint32_t index;
    uint32_t generation;
} AssetHandle;

typedef enum {
    ASSET_STATE_EMPTY,
    ASSET_STATE_LOADING,
    ASSET_STATE_LOADED,
    ASSET_STATE_FAILED,
    ASSET_STATE_UNLOADING,
} AssetState;

// === 资源加载请求 ===
typedef struct {
    const char*     path;
    AssetType       type;
    AssetHandle*    out_handle;      // 输出句柄 (异步填充)
    int             priority;        // 0=最高, 越大越低
    AssetHandle*    dependencies;    // 依赖的资源
    uint32_t        dep_count;
} AssetRequest;

// === Asset Manager ===
typedef struct AssetManager {
    VFS*            vfs;
    
    // 资源池
    struct {
        void**        slots;       // 实际资源指针
        AssetState*   states;
        uint32_t*     generations;
        int32_t*      ref_counts;
        uint32_t      capacity;
    } pool;
    
    // 加载器注册表 (按 AssetType)
    struct {
        void* (*load)(VFS* vfs, const char* path, void* ctx);
        void  (*unload)(void* resource);
        void* ctx;
    } loaders[ASSET_TYPE_COUNT];
    
    // 异步加载队列 (优先级队列)
    // 后台线程消费
} AssetManager;

// === API ===
AssetManager* am_create(VFS* vfs);
void          am_destroy(AssetManager* am);

// 注册加载器
void am_register_loader(AssetManager* am, AssetType type,
                        void* (*load)(VFS*, const char*, void*),
                        void  (*unload)(void*),
                        void* ctx);

// 同步加载 (阻塞)
AssetHandle am_load_sync(AssetManager* am, const char* path, AssetType type);

// 异步加载 (非阻塞)
void        am_load_async(AssetManager* am, const AssetRequest* req);

// 查询状态
AssetState  am_get_state(AssetManager* am, AssetHandle h);
void*       am_get_data(AssetManager* am, AssetHandle h);  // 返回 NULL 如果未加载完成

// 引用计数
void        am_retain(AssetManager* am, AssetHandle h);
void        am_release(AssetManager* am, AssetHandle h);  // ref=0 时卸载

// 热重载 — 文件监听 + 版本号
void        am_watch(AssetManager* am, AssetHandle h);  // 注册监视
bool        am_poll_reloads(AssetManager* am);           // 检查是否有资源变更
```

---

## 模块 8: 渲染器 (Render Graph + 高级渲染)

### 8.1 原方案缺陷

| # | 缺陷 | 严重度 | 说明 |
|---|------|--------|------|
| 1 | **Render Graph 仅提及名称** | 致命 | 无任何实现细节 |
| 2 | **无剔除策略** | 高 | 视锥剔除、遮挡剔除未提及 |
| 3 | **无光照策略** | 致命 | Forward vs Deferred vs Clustered — 决定整个渲染架构 |
| 4 | **无阴影策略** | 高 | CSM / VSM / Ray-Traced? |
| 5 | **无材质系统** | 高 | Shader 变体管理、材质排序 |
| 6 | **无纹理流式加载** | 中 | 大世界必须 |

### 8.2 最优方案: Clustered Forward + Render Graph

#### Render Graph

```c
// === 渲染通道描述 ===
typedef struct {
    const char* name;
    
    // 输入资源 (读取)
    struct {
        RHIHandle       handle;      // Texture/Buffer 句柄
        RHITextureUsage usage;       // ShaderRead / DepthRead
    } *reads;
    uint32_t read_count;
    
    // 输出资源 (写入)
    struct {
        RHIHandle       handle;
        RHITextureUsage usage;       // ColorTarget / DepthTarget / Storage
        RHIClearValue   clear;       // 清除值 (如果需要)
        bool            need_clear;
    } *writes;
    uint32_t write_count;
    
    // 执行回调
    void (*execute)(RHICommandBuffer cmd, void* ctx);
    void* ctx;
} RenderPass;

// === Render Graph ===
typedef struct RenderGraph RenderGraph;

RenderGraph* rg_create(void);
void         rg_destroy(RenderGraph* rg);

// 添加通道
typedef struct { uint32_t id; } PassHandle;
PassHandle rg_add_pass(RenderGraph* rg, const RenderPass* desc);

// 声明资源 (虚拟资源，编译时映射到真实资源)
typedef struct { uint32_t id; } RGResource;
RGResource rg_create_texture(RenderGraph* rg, const RHITextureDesc* desc);
RGResource rg_import_texture(RenderGraph* rg, RHITexture external);  // 外部资源 (如 swapchain)

// 编译 — 自动剔除未使用的通道，计算屏障，复用资源
bool rg_compile(RenderGraph* rg);

// 执行 — 按拓扑排序执行通道，自动插入屏障
void rg_execute(RenderGraph* rg, RHIDevice* dev, RHICommandBuffer cmd);

// 重置 — 帧结束
void rg_reset(RenderGraph* rg);
```

#### 光照策略: Clustered Forward

```
选择理由:
- Forward+: 需要原子计数器，某些平台不支持
- Deferred: 带宽消耗大，MSAA 困难，透明物体需要额外 pass
- Clustered Forward: 将视锥体分为 3D 网格 (cluster)，每个 cluster 存储影响它的光源列表
  - 支持 MSAA
  - 带宽可控
  - 透明物体自然处理
  - 实现复杂度中等
```

```c
// Clustered Forward 数据结构
#define CLUSTER_X 16
#define CLUSTER_Y 16
#define CLUSTER_Z 24
#define CLUSTER_COUNT (CLUSTER_X * CLUSTER_Y * CLUSTER_Z)
#define MAX_LIGHTS_PER_CLUSTER 256

typedef struct {
    uint32_t offset;  // 在全局光源索引列表中的偏移
    uint32_t count;   // 本 cluster 的光源数量
} Cluster;

typedef struct {
    // 构建 (每帧一次, Compute Shader)
    RHIBuffer cluster_buffer;        // Cluster[CLUSTER_COUNT]
    RHIBuffer light_index_buffer;    // 全局光源索引列表
    RHIBuffer light_data_buffer;     // Light[] (位置、颜色、范围)
    
    // 参数
    uint32_t screen_x, screen_y;
    float    near_plane, far_plane;
} ClusteredLighting;
```

#### 材质系统

```c
// 材质 = shader + 参数集
typedef struct {
    RHIPipeline   pipeline;       // 编译后的渲染管线
    RHIShader     vertex_shader;
    RHIShader     fragment_shader;
    
    // 材质参数
    struct {
        const char*    name;
        MaterialParamType type;   // Float, Float2, Float3, Float4, Texture
        union {
            float    f[4];
            RHITexture tex;
        } value;
    } *params;
    uint32_t param_count;
} Material;

// 材质排序 — 减少管线切换
// 按: Pipeline > Material > Texture 分组排序
typedef struct {
    uint32_t material_id;
    uint32_t mesh_id;
    float    distance;    // 到相机距离 (透明物体按距离排序)
    uint32_t submesh_index;
} DrawCommand;

void renderer_sort_draws(DrawCommand* cmds, uint32_t count);
```

---

## 模块 9: 物理引擎

### 9.1 原方案缺陷

| # | 缺陷 | 严重度 | 说明 |
|---|------|--------|------|
| 1 | **无物理管线描述** | 致命 | integrate → broadphase → narrowphase → solver 的流水线未提及 |
| 2 | **无宽相算法选择** | 高 | BVH? Sweep-and-Prune? Spatial Hash? |
| 3 | **无窄相算法选择** | 高 | GJK? SAT? |
| 4 | **无 CCD** | 中 | 连续碰撞检测防止隧穿 |
| 5 | **无角色控制器** | 中 | 游戏引擎必备 |
| 6 | **无场景查询** | 高 | 射线检测、形状投射、重叠检测 |
| 7 | **未考虑固定时间步** | 中 | 物理需要确定性 |

### 9.2 最优方案

```c
// === 物理管线 (固定时间步, 通常 60Hz) ===
// 每帧:
// 1. 积分速度 → 位置 (半隐式欧拉)
// 2. 宽相碰撞检测 (Sweep-and-Prune + AABB)
// 3. 窄相碰撞检测 (GJK + EPA)
// 4. 约束求解 (Sequential Impulse, 多次迭代)
// 5. 应用修正后位置/速度

// === 宽相: Sweep-and-Prune (SAP) ===
// 对 AABB 在 3 个轴上排序，检测重叠对
typedef struct {
    float    min[3], max[3];  // AABB
    uint32_t entity_id;
    uint32_t proxy_id;
} BroadphaseProxy;

typedef struct {
    BroadphaseProxy* proxies;
    uint32_t         proxy_count;
    // 3 个轴的排序端点列表
    struct { float value; uint16_t proxy_id; bool is_min; } *axis[3];
} BroadphaseSAP;

// === 窄相: GJK + EPA ===
typedef struct {
    Vec3    normal;
    float   depth;
    Vec3    point;
} ContactInfo;

bool narrowphase_gjk(const ColliderShape* a, const Transform* ta,
                     const ColliderShape* b, const Transform* tb,
                     ContactInfo* out_contact);

// === 物理世界 ===
typedef struct {
    // 刚体数据 (SOA)
    Vec3*   positions;
    Vec3*   velocities;
    Quat*   rotations;
    Vec3*   angular_velocities;
    float*  masses;
    float*  inverse_masses;
    // ...
    uint32_t body_count;
    
    BroadphaseSAP broadphase;
    
    // 约束
    struct {
        uint32_t body_a, body_b;
        // 约束参数
    } *constraints;
    uint32_t constraint_count;
    
    // 物理参数
    Vec3    gravity;
    float   fixed_timestep;
    uint32_t solver_iterations;
} PhysicsWorld;

// === API ===
PhysicsWorld* physics_create(float gravity_y, float timestep);
void          physics_destroy(PhysicsWorld* pw);

uint32_t physics_add_body(PhysicsWorld* pw, Vec3 pos, Quat rot,
                          ColliderShape shape, float mass);
void     physics_remove_body(PhysicsWorld* pw, uint32_t body_id);

void     physics_step(PhysicsWorld* pw);  // 固定步进
void     physics_interpolate(PhysicsWorld* pw, float alpha);  // 渲染插值

// 场景查询
typedef struct { uint32_t body_id; float t; Vec3 point; Vec3 normal; } RayHit;
bool     physics_raycast(PhysicsWorld* pw, Vec3 origin, Vec3 dir, float max_dist, RayHit* out);
uint32_t physics_overlap_sphere(PhysicsWorld* pw, Vec3 center, float radius, uint32_t* out_ids);
uint32_t physics_overlap_box(PhysicsWorld* pw, Vec3 center, Vec3 half_extents, uint32_t* out_ids);
```

---

## 模块 10: 音频 + UI

### 10.1 音频 — 原方案缺陷

| # | 缺陷 | 严重度 |
|---|------|--------|------|
| 1 | 无 3D 空间音频 | 高 |
| 2 | 无音频流式 (大文件) | 中 |
| 3 | 无 Voice 管理 (限制同时播放) | 中 |
| 4 | 无混响/阻隔效果 | 低 |

**最优方案**: 基于 miniaudio 封装

```c
typedef struct {
    miniaudio_engine* backend;
    
    // Voice 池
    struct {
        bool     active;
        uint32_t source_id;
        Vec3     position;
        float    volume;
        float    pitch;
    } voices[MAX_VOICES];
    uint32_t voice_count;
    
    // 监听者
    struct {
        Vec3 position;
        Vec3 forward;
        Vec3 up;
    } listener;
} AudioSystem;

AudioSystem* audio_create(void);
void         audio_destroy(AudioSystem* as);
void         audio_update(AudioSystem* as, float dt);  // 更新 3D 空间

uint32_t audio_play(AudioSystem* as, AssetHandle clip, Vec3 position, float volume);
void     audio_stop(AudioSystem* as, uint32_t voice_id);
void     audio_set_listener(AudioSystem* as, Vec3 pos, Vec3 fwd, Vec3 up);
```

### 10.2 UI — 原方案缺陷

| # | 缺陷 | 严重度 |
|---|------|--------|------|
| 1 | 仅提及"即时模式"，无细节 | 高 |
| 2 | 无布局系统 | 高 |
| 3 | 无文字输入/IME | 中 |
| 4 | 无样式/主题 | 低 |

**最优方案**: Dear ImGui 风格即时模式 + 自定义渲染后端

```c
// UI 核心概念:
// 1. 每帧重建 UI 状态 (即时模式)
// 2. 通过 RHI 渲染 (非固定管线)
// 3. 输入事件自动路由

typedef struct {
    RHICommandBuffer* cmd;
    RHIPipeline       ui_pipeline;
    RHIBuffer         vertex_buffer;
    RHIBuffer         index_buffer;
    RHITexture        font_texture;
    InputState*       input;
    float             width, height;
} UIContext;

UIContext* ui_create(RHIDevice* dev, InputState* input);
void       ui_destroy(UIContext* ui);

// 每帧调用
void ui_begin(UIContext* ui);
void ui_end(UIContext* ui);  // 自动提交渲染命令

// 控件
bool ui_button(UIContext* ui, const char* label, float x, float y, float w, float h);
void ui_text(UIContext* ui, const char* text, float x, float y);
bool ui_slider(UIContext* ui, const char* label, float* value, float min, float max);
void ui_image(UIContext* ui, RHITexture tex, float x, float y, float w, float h);
bool ui_checkbox(UIContext* ui, const char* label, bool* checked);
void ui_begin_window(UIContext* ui, const char* title, float x, float y, float w, float h);
void ui_end_window(UIContext* ui);
```

---

## 总结: 各模块最优方案速查

| 模块 | 原方案问题 | 最优方案 | 核心理由 |
|------|-----------|----------|----------|
| **内存管理** | 函数指针间接开销 | inline + vtable 混合 | 热路径零开销，冷路径灵活 |
| **ECS** | 64组件上限，无 Archetype | Archetype + Chunk (SOA) | 遍历性能碾压，SIMD 友好 |
| **RHI** | 全局单例，缺同步/命令缓冲 | Device 中心 + 代际句柄 + CmdBuffer | 多 GPU，多线程录制，安全 |
| **SIMD 数学** | 运行时 vtable 致命开销 | 编译期 `#ifdef` + `static inline` | 零间接调用，完全内联 |
| **任务系统** | 无工作窃取，负载不均衡 | Chase-Lev Work-Stealing Deque | 自动负载均衡，wait 时参与 |
| **平台** | 回调事件不安全 | SPSC 事件队列 + InputState 快照 | 线程安全，确定性输入 |
| **资源管线** | 无依赖，无异步 | VFS + 依赖图 + 异步优先级队列 | 拓扑排序加载，不阻塞主线程 |
| **渲染器** | 无实现细节 | Clustered Forward + Render Graph | 现代 GPU 友好，自动资源管理 |
| **物理** | 无管线描述 | SAP + GJK/EPA + Sequential Impulse | 经典可靠方案 |
| **音频** | 无 3D 音频 | miniaudio + 3D Voice 池 | 简单有效 |
| **UI** | 无细节 | 即时模式 (ImGui 风格) | 简单，调试友好 |

---

> **变更日志**:
> - v1 — 10 个模块的缺陷分析 + 方案对比 + 最优选择
