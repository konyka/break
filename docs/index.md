# Break — 纯 C 跨平台游戏引擎

## 项目概述

从零构建的纯 C (C11-C23) 游戏引擎，支持 Vulkan 和 OpenGL 双后端渲染。

**当前进度**: Phase 0-8Y 全部完成，~188 FPS (Intel UHD TGL GT1)，17/17 测试通过。

## 渲染管线

```
Scene (POM) → SSAO → ContactShadow → VolumetricFog → LensFlare
→ SSR → SSGI → TAA → FXAA → Sharpen → MotionBlur
→ DOF → SSS → Bloom → Tonemap+ColorGrade → UI
```

## 模块总览

| 模块 | 路径 | 说明 |
|------|------|------|
| **RHI** | `src/rhi/` | Vulkan/OpenGL 双后端抽象：shader、pipeline、FBO、texture、sampler、uniform |
| **Renderer** | `src/renderer/` | 26 个渲染子系统 (见下方详细列表) |
| **Math** | `src/math/` | vec2/vec3/vec4/mat4/quaternion，SIMD-ready |
| **Platform** | `src/platform/` | X11 窗口、输入、时间、文件监控 |
| **Asset** | `src/asset/` | 资源加载、热重载、虚拟文件系统 |
| **Animation** | `src/animation/` | 骨骼动画、GPU skinning |
| **Audio** | `src/audio/` | miniaudio 封装 |
| **Physics** | `src/physics/` | 角色控制器、碰撞检测 |
| **ECS** | `src/ecs/` | 实体-组件系统 |
| **Script** | `src/script/` | Lua 脚本绑定 |
| **Task** | `src/task/` | 任务调度器 |
| **UI** | `src/ui/` | 调试 UI、TrueType 字体渲染 |
| **Core** | `src/core/` | 类型、日志、断言、内存分配、性能分析 |

## 渲染子系统详解

### 材质与几何

| 系统 | 文件 | 说明 |
|------|------|------|
| PBR Material | `shaders/pbr_clustered_vk.frag` | Cook-Torrance BRDF + parallax occlusion mapping (16层) |
| Clustered Lighting | `lighting.c` | 16×8×24 网格，支持点光 + 方向光 |
| Cascaded Shadow | `shaders/pbr_clustered_vk.frag` | 4 级联 PCF (5×5) shadow map |
| Terrain | `terrain.c` | 程序化地形网格 |
| Skybox | `skybox.c` | 渐变天穹 |
| GPU Particles | `particles.c` | Compute-based 粒子系统 |
| Instanced Rendering | `shaders/instanced_vk.*` | 实例化绘制 |
| Skinned Mesh | `shaders/skinned_vk.*` | GPU 骨骼蒙皮 |

### 后处理管线 (按执行顺序)

| # | 系统 | 文件 | 分辨率 | 关键技术 |
|---|------|------|--------|----------|
| 1 | SSAO | `ssao.c` | 半分辨率 | 16 采样半球核，blur pass |
| 2 | Contact Shadow | `contact_shadow.c` | 半分辨率 | 8 步 view-space 光线步进 |
| 3 | Volumetric Fog | `volumetric.c` | 半分辨率 | 16 步 ray march，基于高度密度 |
| 4 | Lens Flare | `lens_flare.c` | 半分辨率 | 星爆 + 条纹 + 鬼影 + 光环 |
| 5 | SSR | `ssr.c` | 半分辨率 | Hi-Z ray march，线性搜索 |
| 6 | SSGI | `ssgi.c` | 半分辨率 | 8 采样半球探针，法线加权 |
| 7 | TAA | `taa.c` | 全分辨率 | 历史帧重投影，velocity buffer |
| 8 | FXAA | `fxaa.c` | 全分辨率 | 9 抽头亮度边缘检测 |
| 9 | Sharpen | `sharpen.c` | 全分辨率 | 对比度自适应 unsharp mask |
| 10 | Motion Blur | `motion_blur.c` | 全分辨率 | 深度速度重建，triangle-weighted |
| 11 | DOF | `dof.c` | 全分辨率 | 散景盘模糊，CoC 半径 |
| 12 | SSS | `sss.c` | 全分辨率 | 3-lobe 扩散剖面，9×9 核 |
| 13 | Bloom | `post_process.c` | 1/4 分辨率 | 柔和提取 + 双 pass 模糊 + 合成 |
| 14 | Tonemap + ColorGrade | `tonemap.c` | 直出 | ACES + 色差 + 暗角 + 颗粒 + 饱和度/对比度/亮度/色温/色调 |

### GPU Compute

| 系统 | 文件 | 说明 |
|------|------|------|
| Frustum Culling | `gpucull.c`, `shaders/cull.comp` | GPU 视锥剔除 |
| Particle Update | `shaders/particle_update.comp` | GPU 粒子更新 |
| Particle Culling | `shaders/particle_cull.comp` | GPU 粒子排序剔除 |

## 构建

```bash
# Vulkan 构建
cd engine && cmake -B build -DENGINE_VULKAN=ON && cmake --build build

# OpenGL 构建
cd engine && cmake -B build-gl && cmake --build build-gl

# 运行
./build/engine_demo

# 测试
./build/test_vulkan
```

## 性能

| 指标 | 数值 |
|------|------|
| GPU | Intel UHD Graphics (TGL GT1) |
| 分辨率 | 1280×720 |
| FPS | ~188 |
| 测试 | 17/17 通过 |
| Push Constants | 最大 256 字节 |
| 编译警告 | -Wall -Wextra -Werror -pedantic |

## 文档索引

### 设计阶段

- [纯 C 引擎方案](./PureC_Engine_Proposal.md) — 初始设计提案
- [深度模块审查](./PureC_Engine_DeepDive.md) — 10 个模块的缺陷分析 + 替代方案对比 + 最优选择

### 执行与进度

- [执行计划](./PureC_Engine_ExecutionPlan.md) — Phase 0 到 8Y 完整进度追踪

### 参考架构

- [BW191 (BigWorld) 引擎架构](./BW191_Architecture.md) — 商用 MMO 引擎
- [CryENGINE v3.1.2 架构](./CryENGINE_Architecture.md) — AAA 游戏引擎
- [GameEngineFromScratch 架构](./GEFS_Architecture.md) — 教学引擎
- [T3DGameR1 架构](./T3DGameR1_Architecture.md) — 《Windows 游戏编程大师技巧》

### 技术专题

- [Clustered Lighting 设计](./Phase5B_ClusteredLighting.md) — 光源聚类方案设计

## 目录结构

```
engine/
├── CMakeLists.txt              # 构建配置
├── external/                   # 第三方库 (cgltf, glad, miniaudio, stb)
├── shaders/                    # GLSL 着色器 (Vulkan _vk 后缀 + OpenGL)
│   ├── pbr_clustered_vk.*      # PBR + 聚类光照 + POM
│   ├── *_vk.frag / *.frag      # 后处理着色器 (双后端)
│   └── *.comp                  # Compute 着色器
├── src/
│   ├── main.c                  # 入口 + 完整渲染管线
│   ├── engine.c                # 引擎生命周期
│   ├── test_vulkan.c           # 17 项单元测试
│   ├── rhi/                    # 渲染硬件接口
│   ├── renderer/               # 26 个渲染子系统
│   ├── math/                   # 数学库
│   ├── platform/               # 平台层
│   ├── asset/                  # 资源管理
│   ├── animation/              # 骨骼动画
│   ├── audio/                  # 音频
│   ├── physics/                # 物理
│   ├── ecs/                    # 实体组件
│   ├── script/                 # Lua 脚本
│   ├── task/                   # 任务调度
│   ├── ui/                     # 调试 UI
│   └── core/                   # 基础设施
└── tools/
    └── packer.c                # 资源打包工具

docs/                           # 技术文档 (本目录)
```
