# Break Engine 渲染管线

## 1. 管线概述

Break Engine 采用现代前向渲染架构，结合聚类光照（Clustered Lighting）技术实现高性能多光源场景渲染。

**核心特性：**

- **渲染架构**：前向渲染 + 聚类光照（Clustered Forward Rendering）
- **图形后端**：支持 OpenGL 4.5+ 和 Vulkan 双后端
- **后处理系统**：26 个后处理子系统，完整电影级画面处理
- **材质模型**：PBR (Cook-Torrance BRDF) 基于物理的材质系统
- **环境光照**：IBL (Image Based Lighting) split-sum 预计算（BRDF LUT + Irradiance + Prefilter）
- **几何系统**：地形、水面、粒子、天空盒、实例化渲染、骨骼蒙皮
- **优化技术**：视锥剔除、GPU 剔除、实例化、动态分辨率

---

## 2. 渲染帧结构

### 2.1 主循环

引擎每帧的执行流程遵循以下结构：

```c
while (engine_frame(engine)) {
    rhi_frame_begin(device);

    // 1. 阴影传递 — 级联阴影 + 接触阴影
    shadow_pass_execute(renderer);

    // 2. 主渲染传递（聚类 PBR）
    //    - 视锥剔除
    //    - 灯光聚类分配
    //    - 几何提交（地形/水面/粒子/实例化/蒙皮）
    //    - PBR 光照计算
    main_pass_execute(renderer);

    // 3. 后处理管线
    post_process_execute(renderer);

    rhi_frame_end(device);
    rhi_present(device);
}
```

### 2.2 完整帧流程图

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                           Frame Begin                                        │
├─────────────────────────────────────────────────────────────────────────────┤
│                                                                              │
│  ┌──────────────┐    ┌────────────────────┐    ┌───────────────────┐        │
│  │ Shadow Pass  │───▶│ Main Geometry Pass │───▶│ Post Processing   │        │
│  └──────────────┘    └────────────────────┘    └───────────────────┘        │
│        │                      │                         │                    │
│        ▼                      ▼                         ▼                    │
│  ┌──────────┐         ┌─────────────┐          ┌─────────────┐             │
│  │CSM 4级联 │         │ 视锥剔除     │          │ 26个子系统   │             │
│  │深度缓冲  │         │ 聚类灯光分配 │          │ 链式处理     │             │
│  └──────────┘         │ PBR 着色     │          └─────────────┘             │
│                       │ 几何渲染     │                  │                    │
│                       └─────────────┘                  ▼                    │
│                                                  ┌──────────┐               │
│                                                  │ Present  │               │
│                                                  └──────────┘               │
├─────────────────────────────────────────────────────────────────────────────┤
│                            Frame End                                         │
└─────────────────────────────────────────────────────────────────────────────┘
```

**各阶段输入/输出：**

| 阶段 | 输入 | 输出 |
|------|------|------|
| Shadow Pass | 场景几何体、光源方向 | 级联阴影深度图 (4×1024×1024) |
| Main Geometry Pass | 顶点数据、材质纹理、灯光数据、阴影图 | HDR 颜色缓冲、深度缓冲、法线缓冲、速度缓冲 |
| Post Processing | HDR 颜色缓冲、深度缓冲、法线缓冲、速度缓冲 | LDR 最终帧缓冲 |
| Present | 最终帧缓冲 | 屏幕显示 |

---

## 3. 阴影系统

### 3.1 级联阴影映射 (CSM)

引擎实现了 4 级联的级联阴影映射系统，为方向光提供高质量阴影覆盖。

**参数配置：**

| 参数 | 值 |
|------|-----|
| 级联数量 | 4 |
| 每级分辨率 | 1024×1024 |
| 过滤方式 | PCF 5×5 软阴影 |
| 深度偏移 | 动态计算 |
| 级联分割方案 | 对数/线性混合 |

**工作流程：**
1. 根据相机视锥体计算各级联的裁剪空间
2. 为每个级联生成正交投影矩阵
3. 从光源视角渲染场景深度到对应级联纹理
4. 主渲染阶段采样阴影图，使用 PCF 5×5 核做软阴影过滤

**GPU Indirect Draw 优化：** 当 Mega-Buffer 可用时，每个级联的场景 mesh 渲染使用单次间接绘制调用替代逐个 mesh 绘制，将 4×(N+1) 次 draw call 压缩为 4 次（详见 §9.7）。

### 3.2 接触阴影 (Contact Shadow)

**实现文件：** `renderer/contact_shadow.c` (4.5KB), `shaders/contact_shadow.frag`

屏幕空间接触阴影为近距离物体提供精细的阴影细节，补充 CSM 无法覆盖的小尺度遮挡。

**参数配置：**

| 参数 | 值 |
|------|-----|
| 光线步进步数 | 8 步 |
| 计算空间 | 屏幕空间 |
| 最大追踪距离 | 可配置 |
| 采样策略 | 深度缓冲光线步进 |

**算法流程：**
1. 从着色点沿光照方向在屏幕空间步进
2. 每步比较当前光线深度与深度缓冲
3. 检测遮挡并生成接触阴影遮罩
4. 与主阴影结果合并

---

## 4. 聚类光照系统

### 4.1 设计参数

聚类光照系统将视锥体空间划分为三维网格，每个聚类维护影响它的灯光列表，实现 O(1) 灯光查询。

| 参数 | 值 |
|------|-----|
| 网格划分 | 16×8×24 (X×Y×Z) |
| 总聚类数 | 3072 |
| 最大点光源 | 256 |
| 最大方向光 | 4 |
| 每聚类最大灯光 | 128 |
| Z 轴划分方式 | 对数深度 |

### 4.2 工作流程

```
┌─────────────────┐     ┌──────────────────┐     ┌─────────────────┐
│ 1. CPU 聚类分配 │────▶│ 2. 上传灯光数据  │────▶│ 3. GPU 着色     │
│ light_system_cull│     │ UBO/SSBO 更新    │     │ 查询 light_grid │
└─────────────────┘     └──────────────────┘     └─────────────────┘
```

**详细步骤：**

1. **CPU 端聚类分配** (`light_system_cull`)
   - 遍历所有活跃灯光
   - 计算每个灯光的影响范围（球体/锥体）
   - 确定灯光与哪些聚类相交
   - 将灯光索引写入对应聚类的灯光列表

2. **上传灯光数据和网格索引**
   - 更新 `light_data_buf`（灯光属性数据）
   - 更新 `light_grid_buf`（聚类索引表）
   - 通过 UBO/SSBO 传递到 GPU

3. **着色器读取 light_grid 查询灯光列表**
   - 片段着色器根据片段的屏幕坐标和深度计算所在聚类
   - 从 `light_grid` 中读取该聚类的灯光偏移和数量

4. **逐灯光 PBR 计算**
   - 遍历聚类内所有灯光
   - 对每个灯光执行 Cook-Torrance BRDF 计算
   - 累加光照贡献

### 4.3 数据缓冲

| 缓冲名称 | 用途 | 数据格式 |
|----------|------|----------|
| `light_data_buf` | 灯光颜色、位置、方向、衰减参数 | `vec4 position_radius + vec4 color_intensity + vec4 direction_angle` |
| `light_grid_buf` | 聚类灯光索引表（offset + count） | `uvec2 per cluster (offset, count)` |
| `light_index_buf` | 灯光索引列表（全局连续数组） | `uint[] light_indices` |

---

## 5. PBR 材质系统

### 5.1 材质属性

引擎采用金属度-粗糙度工作流（Metallic-Roughness Workflow），与 glTF 2.0 标准兼容。

| 属性 | 类型 | 说明 |
|------|------|------|
| Albedo (基色) | `vec4` / Texture2D | 表面基础颜色，含 Alpha |
| Metallic (金属度) | `float` / Texture2D (B通道) | 0=电介质，1=金属 |
| Roughness (粗糙度) | `float` / Texture2D (G通道) | 0=光滑镜面，1=完全粗糙 |
| Normal Map (法线贴图) | Texture2D | 切线空间法线扰动 |
| Emissive (自发光) | `vec3` / Texture2D | HDR 自发光颜色 |
| AO (环境遮蔽) | `float` / Texture2D (R通道) | 预烘焙环境遮蔽 |

### 5.2 光照模型

引擎使用业界标准的 Cook-Torrance 微表面 BRDF 模型：

```
f(l,v) = f_diffuse + f_specular
f_specular = D(h) · F(v,h) · G(l,v,h) / (4 · (n·l) · (n·v))
```

**各项实现：**

| 组件 | 函数 | 说明 |
|------|------|------|
| **D — 法线分布函数** | GGX/Trowbridge-Reitz | 控制高光形状，α = roughness² |
| **F — 菲涅尔项** | Fresnel-Schlick 近似 | `F0 + (1-F0)·(1-cosθ)^5` |
| **G — 几何遮蔽函数** | Smith GGX | 联合遮蔽-阴影函数 |
| **Diffuse** | Lambertian | `albedo / π` (非金属部分) |

**GGX 法线分布：**
```
D(h) = α² / (π · ((n·h)² · (α² - 1) + 1)²)
```

**Smith GGX 几何函数：**
```
G(l,v) = G1(l) · G1(v)
G1(x) = (n·x) / ((n·x)·(1-k) + k)
k = (roughness + 1)² / 8  (直接光照)
```

**Fresnel-Schlick：**
```
F(v,h) = F0 + (1 - F0) · (1 - v·h)^5
```

### 5.3 视差遮蔽映射

**参数配置：**

| 参数 | 值 |
|------|-----|
| 层数 | 16 层 |
| 算法 | Parallax Occlusion Mapping (POM) |
| 自阴影 | 支持 |

视差遮蔽映射通过多层采样高度图模拟表面凹凸的深度位移效果，无需增加几何复杂度。

---

## 6. IBL 环境光照系统

### 6.1 概述

**实现文件：** `renderer/ibl.c`, `renderer/ibl.h`
**着色器：** `brdf_lut.comp`, `irradiance_env.comp`, `prefilter_env.comp`

IBL (Image Based Lighting) 系统为 PBR 渲染提供环境光照的 split-sum 近似预计算，生成三个核心资源：

| 资源 | 尺寸 | 格式 | 用途 |
|------|------|------|------|
| BRDF LUT | 512×512 | RGBA16F (RG) | Fresnel 缩放/偏移查找表 (NdotV, roughness) |
| Irradiance Map | 64×64 ×6面 | Cubemap | 漫反射环境光照（半球余弦卷积） |
| Prefilter Map | 256×256 ×6面 ×5 mip | Cubemap | 镜面反射预积分（mip 编码 roughness） |

### 6.2 预计算流程

```
┌──────────────────┐     ┌───────────────────┐     ┌────────────────────┐
│ 1. BRDF LUT      │───▶│ 2. Irradiance Map  │───▶│ 3. Prefilter Map   │
│ brdf_lut.comp    │     │ irradiance_env.comp│     │ prefilter_env.comp │
│ 纯解析计算       │     │ 环境 cubemap 卷积  │     │ GGX 重要性采样    │
└──────────────────┘     └───────────────────┘     └────────────────────┘
```

**详细步骤：**

1. **BRDF LUT** (`brdf_lut.comp`)
   - 纯解析计算，不依赖环境贴图
   - GGX 重要性采样积分 NdotV 和 roughness 的 Fresnel 响应
   - R 通道 = scale，G 通道 = bias

2. **Irradiance Map** (`irradiance_env.comp`)
   - 对每个 cubemap face 执行半球余弦卷积
   - 通过 `rhi_cmd_bind_image_cubemap_face` 绑定写入面
   - 通过 `rhi_cmd_bind_cubemap_sampler` 采样源环境贴图
   - Push Constants: `u_face`, `u_face_size`
   - Dispatch: `(64/16) × (64/16) × 1` = 4×4 workgroup

3. **Prefilter Map** (`prefilter_env.comp`)
   - 5 个 mip 级别，每个 mip 对应不同 roughness
   - 每个 mip 的每个 face 单独 dispatch
   - Push Constants: `u_roughness`, `u_face`, `u_face_size`/`u_mip_size`
   - Dispatch: `(mip_size/16) × (mip_size/16) × 1`

### 6.3 RHI 接口依赖

IBL 系统依赖以下 RHI cubemap 计算接口：

```c
/* 绑定 cubemap 单面为可写 storage image */
void rhi_cmd_bind_image_cubemap_face(RHICmdBuffer *cmd, RHICubemap cm,
                                      u32 face, u32 unit, bool write_only);

/* 绑定 cubemap 采样器到计算管线 */
void rhi_cmd_bind_cubemap_sampler(RHICmdBuffer *cmd, RHICubemap cm,
                                   RHISampler sampler, u32 unit);
```

- GL 后端: `glBindImageTexture` 的 `layer` 参数选择 cubemap face
- VK 后端: cubemap 创建时包含 `VK_IMAGE_USAGE_STORAGE_BIT`，通过懒创建的 per-face `VkImageView` + storage_image descriptor set 绑定

### 6.4 接口

```c
typedef struct {
    RHIDevice  *device;
    RHITexture  brdf_lut;        /* 512x512 BRDF 查找表 */
    RHICubemap  irradiance_map;  /* 64x64 漫反射 irradiance cubemap */
    RHICubemap  prefilter_map;   /* 256x256 镜面 prefilter cubemap, 5 mip */
    RHISampler  cubemap_sampler; /* 卷积采样器 */
    RHIPipeline brdf_lut_pipeline;
    RHIPipeline irradiance_pipeline;
    RHIPipeline prefilter_pipeline;
    bool        ready;
} IBLSystem;

void ibl_init(IBLSystem *sys, RHIDevice *dev);
void ibl_destroy(IBLSystem *sys, RHIDevice *dev);
void ibl_generate(IBLSystem *sys, RHIDevice *dev, RHICubemap env_map);
```

### 6.5 主渲染循环集成

IBL 纹理通过 `rhi_cmd_bind_material_textures_ibl` 与材质纹理一起绑定到 PBR 着色器：

| 纹理单元 (GL) | Descriptor Binding (VK) | 纹理 | 类型 |
|------|------|------|------|
| 7 | 6 | `brdf_lut` | sampler2D |
| 8 | 7 | `irradiance_map` | samplerCube |
| 9 | 8 | `prefilter_map` | samplerCube |

**流程**：
1. `render_init` 中调用 `ibl_init` + `ibl_generate(dev, RHI_HANDLE_NULL)` 生成 BRDF LUT（纯解析，无环境贴图依赖）
2. 每帧 PBR 渲染时，`rhi_cmd_bind_material_textures_ibl` 将材质纹理 (0-5) 和 IBL 纹理 (7-9) 一起绑定
3. 如果有环境 cubemap，调用 `ibl_generate(dev, env_map)` 会额外生成 irradiance + prefilter cubemap

**VK 后端**：描述符集布局 (`desc_layout`) 已扩展为 9 个绑定 (0-8)，材质和 IBL 在同一个 descriptor set 中，避免多次绑定替换。

### 6.6 延迟渲染路径 (Deferred Rendering)

**实现文件：** `renderer/deferred.c`, `renderer/deferred.h`

引擎同时支持前向渲染（默认）和延迟渲染（可选）路径，通过 `RenderPath` 枚举在运行时切换。

**G-Buffer 布局 (MRT)**：
| RT | 格式 | 内容 |
|---|---|---|
| RT0 | RGBA8 | rgb=albedo, a=metallic |
| RT1 | RG16F | 八面体编码法线 |
| RT2 | RGBA8 | r=roughness, g=ao, b=emissive |
| Depth | D32F | 场景深度 |

**命令缓冲设计**：延迟渲染 API (`deferred_begin_gbuffer`、`deferred_end_gbuffer`、`deferred_lighting_pass`) 接受调用方传入的 `RHICmdBuffer *cmd` 参数（来自 `rhi_frame_begin`），确保 GL/VK 后端的一致性。

---

## 7. 后处理管线

### 7.1 执行顺序

后处理系统按固定顺序链式执行，每个效果读取前一阶段的输出作为输入：

```
HDR Color Buffer
    │
    ▼
┌────────────────┐
│     SSAO       │ ← 深度 + 法线
├────────────────┤
│ Contact Shadow │ ← 深度 + 光方向
├────────────────┤
│  Volumetric    │ ← 深度 + 光方向
├────────────────┤
│  Lens Flare    │ ← 亮区提取
├────────────────┤
│     SSR        │ ← 深度 + 法线 + 颜色
├────────────────┤
│     SSGI       │ ← 深度 + 法线 + 颜色
├────────────────┤
│     TAA        │ ← 当前帧 + 历史帧 + 速度缓冲
├────────────────┤
│     FXAA       │ ← 当前帧
├────────────────┤
│    Sharpen     │ ← 当前帧
├────────────────┤
│  Motion Blur   │ ← 当前帧 + 速度缓冲
├────────────────┤
│     DOF        │ ← 当前帧 + 深度
├────────────────┤
│     SSS        │ ← 当前帧 + 深度
├────────────────┤
│    Bloom       │ ← HDR 颜色
├────────────────┤
│   Tonemap      │ ← HDR → LDR
├────────────────┤
│  Color Grade   │ ← LDR 颜色
├────────────────┤
│  Cinematic    │ ← LDR 颜色 (色差+暗角+胶片颗粒)
├────────────────┤
│   God Rays     │ ← 深度 + 太阳位置
├────────────────┤
│    Output      │
└────────────────┘
```

### 7.2 各效果详解

| 效果 | 实现文件 | 着色器 | 算法 | 分辨率 |
|------|----------|--------|------|--------|
| SSAO | `ssao.c` (5.7KB) | `ssao.frag` / `ssao_vk.frag` | 16采样半球核，半分辨率计算 + 双边模糊 | 1/2 |
| SSGI | `ssgi.c` (6.1KB) | `ssgi.frag` / `ssgi_vk.frag` | 8采样半球探针，全局光照近似 | Full |
| SSR | `ssr.c` (5.2KB) | `ssr.frag` / `ssr_vk.frag` | Hi-Z ray march 屏幕空间反射 | Full |
| TAA | `taa.c` (5.9KB) | `taa.frag` / `taa_vk.frag` | 历史帧重投影 + velocity buffer + 邻域裁剪 | Full |
| FXAA | `fxaa.c` (4.2KB) | `fxaa.frag` / `fxaa_vk.frag` | 9抽头亮度边缘检测抗锯齿 | Full |
| Bloom | `post_process.c` (7.2KB) | `bloom_extract.frag` / `bloom_blur.frag` / `bloom_composite.frag` | 亮度提取 + 双 pass 高斯模糊 + 加法合成 | 1/2 |
| Tonemap | `tonemap.c` (6.5KB) | `tonemap.frag` / `tonemap_vk.frag` | ACES 色调映射 (Academy Color Encoding System) | Full |
| DOF | `dof.c` (4.9KB) | `dof.frag` / `dof_vk.frag` | Circle of Confusion 散景模拟 | Full |
| Motion Blur | `motion_blur.c` (4.4KB) | `motion_blur.frag` / `motion_blur_vk.frag` | 深度感知速度重建模糊 | Full |
| Volumetric | `volumetric.c` (6.7KB) | `volumetric.frag` / `volumetric_vk.frag` | 16步 ray march 体积光散射 | Full |
| God Rays | `god_rays.c` (4.2KB) | `god_rays.frag` / `god_rays_vk.frag` | 径向模糊（Radial Blur）光束效果 | Full |
| Color Grade | `color_grade.c` (4.4KB) | `color_grade.frag` / `color_grade_vk.frag` | 色差 + 暗角 + 胶片颗粒 | Full |
| Sharpen | `sharpen.c` (3.8KB) | `sharpen.frag` / `sharpen_vk.frag` | 对比度自适应 unsharp mask 锐化 | Full |
| Cinematic | `cinematic.c` (4.5KB) | `cinematic.frag` / `cinematic_vk.frag` | 色散 + 暗角 + 胶片颗粒（电影级后处理） | Full |
| Lens Flare | `lens_flare.c` (6.3KB) | `lens_flare.frag` / `lens_flare_vk.frag` | 星爆 + 条纹 + 鬼影 + 光环 复合效果 | Full |
| Lens Effects | `lens_effects.c` (4.3KB) | `lens_effects.frag` / `lens_effects_vk.frag` | 复合镜头效果（畸变 + 色散） | Full |
| SSS | `sss.c` (5.7KB) | `sss.frag` / `sss_vk.frag` | 3-lobe 扩散剖面次表面散射 | Full |
| Upscale | `upscale.c` (6.5KB) | `upscale.frag` / `upscale_vk.frag` | 动态分辨率缩放（时域超采样） | Variable |
| Contact Shadow | `contact_shadow.c` (4.5KB) | `contact_shadow.frag` / `contact_shadow_vk.frag` | 8步屏幕空间光线步进 | Full |

### 7.3 SSAO 模糊处理

SSAO 系统包含专用的模糊子 pass：

- **文件：** `shaders/ssao_blur.frag` / `ssao_blur_vk.frag`
- **算法：** 双边滤波（保边模糊）
- **目的：** 消除半分辨率采样产生的噪声，同时保持边缘锐利

---

## 8. 几何渲染系统

### 8.1 地形系统

**实现文件：** `renderer/terrain.c` (20.4KB), `renderer/terrain.h` (1.5KB)
**着色器：** `terrain.vert` / `terrain.frag` / `terrain_vk.vert` / `terrain_vk.frag`

| 特性 | 说明 |
|------|------|
| 网格生成 | 程序化高度图网格 |
| LOD 系统 | 基于距离的分段 LOD |
| 纹理 | 多层纹理混合 (Splatmap) |
| 法线 | 实时法线计算 |

### 8.2 水面系统

**实现文件：** `renderer/water.c` (5.0KB), `renderer/water.h` (0.9KB)
**着色器：** `water.vert` / `water.frag` / `water_vk.vert` / `water_vk.frag`

| 特性 | 说明 |
|------|------|
| 波动仿真 | 实时正弦波叠加 |
| 反射 | 屏幕空间反射 (SSR) |
| 折射 | 深度感知折射 |
| 泡沫 | 基于深度的泡沫生成 |

### 8.3 粒子系统

**实现文件：** `renderer/particles.c` (6.8KB), `renderer/particles.h` (0.9KB)
**着色器：** `particle.vert` / `particle.frag` / `particle_update.comp` / `particle_cull.comp`

| 特性 | 说明 |
|------|------|
| 驱动方式 | GPU Compute 驱动 |
| 更新着色器 | `particle_update.comp` — 物理仿真、生命周期管理 |
| 剔除着色器 | `particle_cull.comp` — 视锥剔除不可见粒子 |
| 排序 | GPU 排序实现透明度正确混合 |
| 发射器 | 支持点/球/锥/框发射器 |

### 8.4 天空盒

**实现文件：** `renderer/skybox.c` (3.5KB), `renderer/skybox.h` (0.5KB)
**着色器：** `skybox.vert` / `skybox.frag` / `skybox_vk.vert` / `skybox_vk.frag`

| 特性 | 说明 |
|------|------|
| 渲染方式 | 渐变天穹渲染 |
| 深度技巧 | 深度写入 1.0，最后渲染 |
| 时间变化 | 支持日夜循环颜色渐变 |

### 8.5 实例化渲染

**着色器：** `instanced.vert` / `instanced.frag` / `instanced_vk.vert` / `instanced_vk.frag`

| 特性 | 说明 |
|------|------|
| 目标 | 批处理同类几何体，减少 draw call |
| 实现 | 实例化缓冲传递变换矩阵 |
| 适用场景 | 植被、岩石、建筑等重复物体 |

### 8.6 蒙皮渲染

**着色器：** `skinned.vert` / `skinned.frag` / `skinned_vk.vert` / `skinned_vk.frag`

| 特性 | 说明 |
|------|------|
| 骨骼动画 | GPU 蒙皮计算 |
| 骨骼数量 | 每顶点最多 4 骨骼影响 |
| 数据传递 | 骨骼矩阵通过 UBO 上传 |
| 混合 | 支持动画混合与过渡 |

---

## 9. GPU 优化

### 9.1 视锥剔除

**实现文件：** `renderer/cull.c` (2.1KB), `renderer/cull.h` (0.3KB)

| 参数 | 说明 |
|------|------|
| 算法 | CPU 端 AABB-视锥体相交测试 |
| 测试平面 | 6 个视锥平面 |
| 输出 | 可见对象列表 |

### 9.2 GPU 剔除

**实现文件：** `renderer/gpucull.c` (3.9KB), `renderer/gpucull.h` (0.7KB)
**着色器：** `cull.comp`

| 参数 | 说明 |
|------|------|
| 算法 | Compute Shader 并行剔除 |
| 输入 | 对象包围盒 + 视锥/遮挡信息 |
| 输出 | Indirect Draw Buffer |
| 优势 | GPU 并行处理大量对象 |

### 9.3 实例化优化

- 相同网格 + 相同材质的对象合并为单次 instanced draw call
- 显著减少 CPU-GPU 通信开销和状态切换
- 配合 GPU 剔除使用，剔除后直接生成 indirect draw 命令

### 9.4 动态分辨率

**实现文件：** `renderer/upscale.c` (6.5KB)

| 参数 | 说明 |
|------|------|
| 策略 | 基于帧时间动态调整渲染分辨率 |
| 最低比例 | 可配置 (如 50%) |
| 上采样 | 时域超采样重建 |
| 目标 | 维持目标帧率 |

### 9.5 LOD 距离剔除

**实现文件：** `renderer/lod.c` (9.2KB), `renderer/lod.h` (2.4KB)

| 参数 | 说明 |
|------|------|
| 策略 | 基于距离的多级 LOD 选择 + 滞后防抖动 |
| 最大层级 | 4 级 (`LOD_MAX_LEVELS`) |
| 最大组数 | 4096 (`LOD_MAX_GROUPS`) |
| 模式 | 距离策略 / 屏幕占比策略 |
| 集成 | 场景 mesh 注册为单级 LOD 组，超过阈值 2x 距离自动剔除 |

**工作流程：**

1. 初始化时将场景节点注册为 LOD 组（`lod_register`）
2. 每帧渲染时调用 `lod_select` 计算当前 LOD 级别
3. 距离超过 `threshold[0] * 2` 的对象被跳过（距离剔除）
4. 滞后机制防止 LOD 快速切换（`LOD_HYSTERESIS = 0.1`）

### 9.6 GPU Hi-Z 遮挡剔除

**实现文件：** `renderer/occlusion_cull.c` (13.7KB), `renderer/occlusion_cull.h` (1.7KB)
**着色器：** `hi_z_generate.comp`, `occlusion_cull.comp`

| 参数 | 说明 |
|------|------|
| Hi-Z 纹理 | R32F 深度金字塔，半分辨率起步 |
| 最大对象 | 16384 (`OCCLUSION_MAX_OBJECTS`) |
| 工作流 | 深度缓冲 → Hi-Z 生成 → AABB 遮挡测试 → 可见性读回 |
| 流水线 | 当前帧生成 Hi-Z，下一帧使用遮挡结果（延迟一帧） |

**帧流程：**

```
场景深度渲染
    │
    ▼
Hi-Z 金字塔生成 (compute: hi_z_generate.comp)
    │
    ▼
上传 AABB 缓冲 (SSBO)
    │
    ▼
遮挡剔除 dispatch (compute: occlusion_cull.comp)
    │
    ▼
可见性读回 (下一帧使用)
```

### 9.7 Mega-Buffer + GPU Indirect Draw 管线

**实现文件：** `renderer/indirect_draw.c` (6.6KB), `renderer/indirect_draw.h` (2.1KB)
**着色器：** `compact_draws.comp`

| 参数 | 说明 |
|------|------|
| 最大 draw cmds | 16384 |
| 压缩策略 | GPU compute stream-compaction (`atomicAdd`) |
| 可见性来源 | CPU 视锥剔除 / GPU 视锥剔除 (`gpucull`) |
| 输出 | 单次 `glMultiDrawElementsIndirectCount` / `vkCmdDrawIndexedIndirectCount` |

**Mega-Buffer 构建：**

在场景加载后，将所有场景 mesh 的几何数据合并为单一 VBO/IBO：
- 顶点预变换到世界空间（`world_transform`），消除每对象 `u_model` 矩阵更新
- 索引偏移重映射，保证 mega-buffer 内索引正确引用
- 每个场景节点生成一个 `DrawIndexedIndirectCmd` 条目
- 按材质分组：相同 `material_idx` 的 draw commands 收集到独立的 `IndirectDrawSystem` 实例

**间接绘制流水线：**

```
CPU 构建 DrawIndexedIndirectCmd[N]  (初始化时一次)
    │
    ▼
上传可见性标志 [N×u32]  (每帧)
    │  ├─ CPU 视锥剔除: frustum_test_sphere
    │  └─ GPU 视锥剔除: gpucull_dispatch
    │
    ▼
GPU compact (compute: compact_draws.comp)
    │  原子计数 + 可见命令压缩
    │
    ▼
单次 Indirect Draw  (1 draw call 替代 N 次)
```

**Per-Material 批量间接绘制（G-Buffer / 前向渲染）：**

前向渲染和 Deferred G-Buffer 通道需要逐 mesh 材质绑定，无法在单次间接绘制中切换材质。
解决方案：按材质分组，每个材质组拥有独立的 `IndirectDrawSystem`：

```
MegaBuffer
  ├─ mat_systems[0] → material_idx=0 → N₀ draw cmds
  ├─ mat_systems[1] → material_idx=1 → N₁ draw cmds
  └─ ...
```

渲染时：
1. 预计算所有节点的视锥/LOD 可见性
2. 对每个材质组：bind_material → upload_visibility → compact → execute
3. 总 draw calls = 材质组数 M（通常 1–10）

**性能影响：**

| 场景 | 优化前 draw calls | 优化后 draw calls |
|------|------------------|------------------|
| CSM 阴影 (4 级联) | 4 × (N+1) | 4 (每级联 1 次) |
| 点光源阴影 (6 面 × L) | 6L × (N+1) | 6L (每面 1 次) |
| Deferred G-Buffer | N+1 | M+1 (M=材质组数) |
| 前向场景 | N | M (M=材质组数) |

**切换按键：** F14 切换 GPU Indirect Draw，F15 切换 GPU 视锥剔除

### 9.8 异步资源加载

引擎集成了多线程异步 I/O 加载器（2 个 I/O 线程 + VFS）：

- **启动时：** `vfs_create()` + `async_loader_init(2, vfs)` 初始化 I/O 线程池
- **每帧：** `async_loader_tick()` 在主线程分发完成回调
- **关闭时：** `async_loader_shutdown()` + `vfs_destroy(vfs)` 回收线程

支持 `async_loader_request()` 提交文件加载请求，通过回调在主线程创建 GPU 资源（纹理/缓冲区）。适用于纹理流式加载、场景异步切换、资源热重载等场景。

### 9.9 预计算包围球缓存 + 任务并行视锥剔除

**预计算包围球缓存：**
- 构建 mega-buffer 后，一次性计算每个场景节点的包围球 `(cx, cy, cz, r)`
- 无效节点（无 mesh、skinned、空几何）标记 `r = -1.0f`
- 所有视锥剔除循环直接从缓存读取，避免重复计算 AABB 差值和 `vec3_len`

**任务并行视锥剔除：**
- 利用 `TaskSystem` 的 work-stealing 线程池将可见性计算并行化
- 将 N 个节点分为 `worker_count` 个 chunk，每个 worker 处理一个 chunk
- 前向渲染和 Deferred G-Buffer 的可见性循环均使用 `task_submit + task_wait` 并行
- 对于大型场景（>1000 节点），多核利用率显著提升

**性能影响：**

| 场景 | 优化前 | 优化后 |
|------|--------|--------|
| 每帧 AABB 计算 | N × (sub + len) | 0（缓存） |
| 可见性并行度 | 单核 | worker_count 核 |

### 9.10 音频监听者同步

主循环每帧调用 `audio_system_update()` 将相机位置和朝向同步到音频系统：

- `listener_pos` = `camera.position`
- `listener_forward` = 相机前方向量（从 yaw/pitch 计算）
- `listener_up` = (0, 1, 0)

### 9.11 帧内临时缓冲区预分配

为消除渲染循环中的每帧 `malloc/free` 开销，以下缓冲区在启动时一次性分配：

| 缓冲区 | 容量 | 用途 |
|---------|------|------|
| `instance_data` | 10000 × 64B | 实例数据上传 |
| `cull_node_map_buf` | 16384 × 4B | 剔除节点索引映射 |
| `cull_aabbs_buf` | 16384 × 32B | 剔除 AABB 数组 |
| `cull_visible_buf` | 16384 × 4B | 剔除可见性结果 |

关闭时统一 `free()`，避免每帧 3 次 `malloc` + 3 次 `free` 的系统调用开销。

---

## 10. 着色器组织

### 10.1 命名约定

| 后缀 | 用途 | API |
|------|------|-----|
| `*.vert` | 顶点着色器 | OpenGL GLSL |
| `*.frag` | 片段着色器 | OpenGL GLSL |
| `*_vk.vert` | 顶点着色器 | Vulkan GLSL (需 SPIR-V 编译) |
| `*_vk.frag` | 片段着色器 | Vulkan GLSL (需 SPIR-V 编译) |
| `*.comp` | 计算着色器 | Compute Shader |

### 10.2 着色器分类

#### 几何着色器

| 文件 | 功能 |
|------|------|
| `blinn_phong.vert/frag` | Blinn-Phong 基础光照 |
| `blinn_phong_clustered.vert/frag` | 聚类光照 Blinn-Phong |
| `pbr_clustered.vert/frag` | 聚类光照 PBR |
| `instanced.vert/frag` | 实例化渲染 |
| `skinned.vert/frag` | 骨骼蒙皮 |
| `terrain.vert/frag` | 地形渲染 |
| `water.vert/frag` | 水面渲染 |
| `skybox.vert/frag` | 天空盒 |
| `particle.vert/frag` | 粒子渲染 |
| `triangle.vert/frag` | 基础三角形（测试） |

#### 阴影着色器

| 文件 | 功能 |
|------|------|
| `shadow_depth.vert/frag` | CSM 深度渲染 |
| `depth_only.vert/frag` | 纯深度 pass |

#### 后处理着色器

| 文件 | 功能 |
|------|------|
| `post.vert` / `post_vk.vert` | 全屏四边形顶点着色器 |
| `ssao.frag` | 屏幕空间环境遮蔽 |
| `ssao_blur.frag` | SSAO 模糊 |
| `ssgi.frag` | 屏幕空间全局光照 |
| `ssr.frag` | 屏幕空间反射 |
| `taa.frag` | 时间抗锯齿 |
| `fxaa.frag` | 快速近似抗锯齿 |
| `bloom_extract.frag` | Bloom 亮度提取 |
| `bloom_blur.frag` | Bloom 高斯模糊 |
| `bloom_composite.frag` | Bloom 合成 |
| `tonemap.frag` | 色调映射 |
| `color_grade.frag` | 颜色分级 |
| `dof.frag` | 景深 |
| `motion_blur.frag` | 运动模糊 |
| `volumetric.frag` | 体积光 |
| `god_rays.frag` | 上帝光线 |
| `sharpen.frag` | 锐化 |
| `cinematic.frag` | 电影效果 |
| `lens_flare.frag` | 镜头光斑 |
| `lens_effects.frag` | 镜头效果 |
| `sss.frag` / `sss_vertical.frag` | 次表面散射 |
| `upscale.frag` | 动态分辨率上采样 |
| `contact_shadow.frag` | 接触阴影 |
| `post_tex.frag` | 纹理后处理 |
| `luminance.frag` | 亮度计算 |

#### 计算着色器

| 文件 | 功能 |
|------|------|
| `cull.comp` | GPU 视锥剔除 |
| `particle_update.comp` | 粒子物理更新 |
| `particle_cull.comp` | 粒子剔除 |
| `brdf_lut.comp` | IBL BRDF LUT 生成（GGX 重要性采样积分） |
| `irradiance_env.comp` | IBL 漫反射 irradiance cubemap 生成（半球余弦卷积） |
| `prefilter_env.comp` | IBL 镜面 prefilter cubemap 生成（多 mip GGX 预积分） |

#### 字体渲染

| 文件 | 功能 |
|------|------|
| `font.vert/frag` | 文字渲染 (OpenGL) |
| `font_vk.vert/frag` | 文字渲染 (Vulkan) |

#### 调试着色器

| 文件 | 功能 |
|------|------|
| `debug_viz.frag` / `debug_viz_vk.frag` | 调试可视化 |

---

## 11. 调试工具

### 11.1 调试可视化

**实现文件：** `renderer/debug_viz.c` (4.7KB), `renderer/debug_viz.h` (0.7KB)
**着色器：** `debug_viz.frag` / `debug_viz_vk.frag`

支持的可视化模式：

| 模式 | 说明 |
|------|------|
| 线框模式 | 显示网格线框 |
| 法线可视化 | 将世界空间法线映射为 RGB |
| 深度可视化 | 线性深度灰度显示 |
| UV 可视化 | 纹理坐标映射为 RG |
| 聚类可视化 | 显示光照聚类网格分布 |
| 阴影级联 | 用颜色区分 CSM 各级联覆盖范围 |

### 11.2 性能分析

| 功能 | 说明 |
|------|------|
| Profiler 集成 | GPU/CPU 时间戳查询 |
| 帧时间统计 | 每帧各阶段耗时 |
| Draw Call 计数 | 渲染调用统计 |
| 内存监控 | GPU 显存使用追踪 |

---

## 附录：源文件索引

| 目录 | 文件数 | 功能 |
|------|--------|------|
| `engine/src/renderer/` | 54 文件 | 渲染器核心实现 |
| `engine/shaders/` | 90+ 着色器 | GLSL 着色器 (GL + VK) |
| `engine/src/rhi/` | 4 文件 | 渲染硬件接口抽象层 |
| `engine/src/core/` | 11 文件 | 引擎核心框架 |
| `engine/src/math/` | 2 文件 | 数学库 |
