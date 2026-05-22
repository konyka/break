# GameEngineFromScratch 架构文档

## 1. 项目概述

**GameEngineFromScratch** (GEFS) 是知乎专栏《从零开始手敲次世代游戏引擎》的配套教学项目。它是一个从零构建的现代游戏引擎，采用 C++20 编写，跨平台支持多个图形 API。

- **语言**: C++20 (核心), CUDA (可选), ISPC (可选)
- **构建系统**: CMake 3.20+
- **许可证**: MIT
- **源文件规模**: ~205+ (Framework+RHI), 全项目含 Asset、Game、Viewer 等

## 2. 支持的平台和图形 API

### 平台支持

| 平台 | 状态 |
|------|------|
| Windows 10/11 | 支持 |
| macOS Catalina-Monterey | 支持 |
| Linux (Ubuntu 20.04-22.04, CentOS 7) | 支持 |
| FreeBSD | 部分支持 |
| Android | 部分支持 |
| WebAssembly (Emscripten) | 部分支持 |
| PlayStation 4/Vita | NDA 限制未公开 |

### 图形 API 支持

| API | 状态 |
|-----|------|
| OpenGL | 完整支持 |
| OpenGL ES | 部分支持 |
| Metal 2 | 完整支持 |
| DirectX 12 | 开发中 |
| Vulkan | 开发中 |

## 3. 顶层目录结构

```
GameEngineFromScratch/
├── Framework/        # 引擎核心框架 (接口、场景图、算法、渲染管线)
├── RHI/              # 渲染硬件接口抽象 (多图形 API 后端)
├── Physics/          # 物理引擎集成
├── Platform/         # 平台抽象层
├── Asset/            # 引擎资源 (模型、纹理、着色器等)
├── Game/             # 游戏示例 (台球)
├── Viewer/           # 模型查看器工具
├── Utility/          # 通用工具库
├── Test/             # 测试
├── External/         # 第三方依赖源码和预编译库
│   ├── src/          # 第三方源码 (bullet, opengex, glad, glm, imgui 等)
│   ├── Darwin/       # macOS 预编译库
│   ├── Linux/        # Linux 预编译库
│   └── FreeBSD/      # FreeBSD 预编译库
├── cmake/            # CMake 模块
├── scripts/          # 构建脚本
├── CMakeLists.txt    # 主 CMake 配置
└── config.h.in       # 配置模板
```

## 4. 核心框架层 (`Framework/`)

Framework 是引擎的核心层，定义了所有抽象接口和基础实现。

### 4.1 接口层 (`Framework/Interface/`)

引擎采用**纯接口设计**，所有子系统通过 `I` 前缀的纯虚接口类定义:

```
Interface/
├── IAllocator.hpp           # 内存分配器
├── IAnimationManager.hpp    # 动画管理
├── IApplication.hpp         # 应用生命周期
├── IAssetLoader.hpp         # 资源加载
├── IAudioClipParser.hpp     # 音频解析
├── IDebugManager.hpp        # 调试管理
├── IDispatchPass.hpp        # 分发通道
├── IDrawPass.hpp            # 绘制通道
├── IDrawSubPass.hpp         # 绘制子通道
├── IGameLogic.hpp           # 游戏逻辑接口
├── IGraphicsManager.hpp     # 图形管理器
├── IImageEncoder.hpp        # 图像编码
├── IImageParser.hpp         # 图像解析
├── IInputManager.hpp        # 输入管理
├── IMemoryManager.hpp       # 内存管理
├── IPass.hpp                # 渲染通道基类
├── IPhysicsManager.hpp      # 物理管理
├── IPipelineStateManager.hpp # 管线状态管理
├── IRuntimeModule.hpp       # 运行时模块基类
├── ISceneManager.hpp        # 场景管理
├── ISceneParser.hpp         # 场景解析
├── ISubPass.hpp             # 子通道基类
└── Interface.hpp            # 统一包含头文件
```

### 4.2 场景图 (`Framework/SceneGraph/`)

基于**对象-节点分离**的场景图设计:

**SceneObject (数据对象)**:
```
SceneObject.hpp              # 场景对象基类
SceneObjectGeometry.hpp      # 几何体数据
SceneObjectMaterial.hpp      # 材质数据
SceneObjectTexture.hpp       # 纹理数据 (JPEG/PNG/TGA/HDR/DDS/BMP/PVR/ASTC)
SceneObjectMesh.hpp          # 网格数据 (顶点/索引缓冲)
SceneObjectLight.hpp         # 光源数据
SceneObjectCamera.hpp        # 相机数据
SceneObjectTransform.hpp     # 变换数据
SceneObjectSkyBox.hpp        # 天空盒数据
SceneObjectTerrain.hpp       # 地形数据
SceneObjectIndexArray.hpp    # 索引数组
SceneObjectVertexArray.hpp   # 顶点数组
SceneObjectAnimation.hpp     # 动画数据
SceneObjectTrack.hpp         # 动画轨道
SceneObjectTypeDef.hpp       # 类型定义
```

**SceneNode (场景节点)**:
```
SceneNode.hpp                # 场景节点基类 (树结构)
SceneGeometryNode.hpp        # 几何体节点
SceneLightNode.hpp           # 光源节点
SceneCameraNode.hpp          # 相机节点
SceneBoneNode.hpp            # 骨骼节点
```

**Scene (场景容器)**:
```
Scene.cpp/hpp                # 场景根容器，管理所有节点
```

### 4.3 算法库 (`Framework/Algorism/`)

引擎内置的数学和算法库:

| 文件 | 算法 |
|------|------|
| `AaBb.hpp` | AABB 包围盒 |
| `BVH.hpp` | 层次包围体 (加速结构) |
| `Bezier.hpp` | 贝塞尔曲线 |
| `Bresenham.hpp` | Bresenham 光栅化 |
| `Color.hpp` | 颜色数学 |
| `ColorSpaceConversion.hpp` | 色彩空间转换 |
| `Curve.hpp` | 曲线插值 |
| `Gjk.hpp` | GJK 碰撞检测算法 |
| `Hit.hpp` / `HitableList.hpp` | 光线追踪命中检测 |
| `HuffmanTree.hpp` | 哈夫曼编码 |
| `Linear.hpp` | 线性代数 |
| `MatrixComposeDecompose.hpp` | 矩阵分解合成 |
| `Ray.hpp` | 射线 |
| `quickhull.hpp` | 快速凸包算法 |
| `Tree.hpp` | 通用树结构 |
| `TriangleRasterization.hpp` | 三角形光栅化 |
| `numerical.hpp` | 数值计算 |
| `AST.hpp` | 抽象语法树 |

### 4.4 渲染管线 (`Framework/DrawPass/`, `Framework/DrawSubPass/`, `Framework/DispatchPass/`, `Framework/RenderGraph/`)

引擎采用**可编程渲染管线**设计:

```
DrawPass/           # 渲染通道实现 (如前向渲染、延迟渲染通道)
DrawSubPass/        # 渲染子通道 (阴影、不透明、透明等)
DispatchPass/       # 计算分发通道 (GPGPU)
RenderGraph/        # 渲染图 (现代渲染管线架构)
└── RenderPipeline/ # 渲染管线组合
```

### 4.5 其他框架模块

| 模块 | 职责 |
|------|------|
| `Ability/` | 对象能力接口 (Animatable, Hitable, MaterialContainer) |
| `CodeGen/` | 代码生成 (着色器代码生成) |
| `Common/` | 通用工具 (Buffer, Image, AudioClip, GfxConfiguration, portable types) |
| `Encoder/` | 数据编码器 |
| `Geometries/` | 几何体生成 (球体、立方体、平面等基础几何) |
| `GeomMath/` | 几何数学 (含 ISPC 优化版本) |
| `Manager/` | 管理器实现 (场景管理、内存管理、动画管理等) |
| `Parser/` | 解析器 (OpenGEX 场景解析) |

## 5. RHI 层 (`RHI/`)

渲染硬件接口 (RHI) 层实现了**多图形 API 后端**的抽象:

```
RHI/
├── OpenGL/                # OpenGL 后端
│   ├── OpenGLGraphicsManager.hpp       # OpenGL 图形管理器
│   ├── OpenGLPipelineStateManager.hpp  # OpenGL 管线状态
│   ├── OpenGLESGraphicsManager.hpp     # OpenGL ES 变体
│   ├── imgui_impl_opengl3.h           # ImGui OpenGL 集成
│   └── *Config.hpp                    # 配置
│
├── Metal/                 # Metal 后端 (macOS/iOS)
│   ├── Metal2GraphicsManager.h        # Metal 2 图形管理器
│   ├── Metal2Renderer.h               # Metal 渲染器
│   ├── MetalPipelineState.h           # 管线状态
│   ├── MetalPipelineStateManager.h    # 管线状态管理
│   └── imgui_impl_metal.h             # ImGui Metal 集成
│
├── D3d/                   # DirectX 12 后端
│   ├── D3d12GraphicsManager.hpp       # D3D12 图形管理器
│   ├── D3d12RHI.hpp                   # D3D12 RHI 核心
│   ├── D3d12PipelineStateManager.hpp  # 管线状态管理
│   ├── D3d12Utility.hpp               # D3D12 工具
│   ├── D3d12Config.hpp                # 配置
│   └── imgui_impl_dx12.h             # ImGui D3D12 集成
│
├── Vulkan/                # Vulkan 后端
│   ├── VulkanGraphicsManager.hpp      # Vulkan 图形管理器
│   ├── VulkanPipelineStateManager.hpp # 管线状态管理
│   └── VulkanRHI.hpp                  # Vulkan RHI 核心
│
├── D2d/                   # Direct2D 后端 (2D 渲染)
│   └── D2dRHI.hpp
│
└── Empty/                 # 空实现 (测试/无头模式)
    ├── EmptyConfig.hpp
    └── EmptyPipelineStateManager.hpp
```

**设计模式**: 每个 RHI 后端实现 `IGraphicsManager` 和 `IPipelineStateManager` 接口，提供:
- 缓冲创建和管理
- 着色器编译和加载
- 管线状态管理
- 绘制调用
- 纹理管理

## 6. 物理引擎 (`Physics/`)

```
Physics/
├── Bullet/     # Bullet Physics 库集成
└── My/         # 自研物理引擎 (开发中)
```

支持:
- 刚体动力学
- 碰撞检测
- 物理模拟

## 7. 平台层 (`Platform/`)

```
Platform/
├── Windows/    # Windows 平台 (Win32 API)
├── Darwin/     # macOS 平台 (Cocoa)
├── Linux/      # Linux 平台 (X11)
├── Android/    # Android 平台
├── Sdl/        # SDL 跨平台封装
└── Empty/      # 空实现
```

平台层负责:
- 窗口创建和管理
- 消息/事件循环
- 输入设备处理
- 文件系统路径
- 线程和时间

## 8. 游戏层和工具

### 8.1 Game (`Game/`)

```
Game/
└── Billiard/                # 台球游戏示例
    ├── main.cpp             # 入口
    ├── BilliardGameLogic.cpp/hpp   # 游戏逻辑
    └── BilliardGameConfig.cpp      # 游戏配置
```

### 8.2 Viewer (`Viewer/`)

模型/场景查看器工具:
```
Viewer/
├── main.cpp          # 入口
└── ViewerLogic.cpp/hpp  # 查看器逻辑
```

## 9. 资源管线

### 支持的场景格式
- **OpenGEX** - 开源游戏引擎交换格式
- **Collada** - 规划中，未实现

### 支持的纹理格式
- JPEG, PNG, TGA, HDR, DDS, BMP
- PVR (BC1-BC7 压缩纹理)
- ASTC (自适应可缩放纹理压缩)

### 着色器
- **HLSL** 作为主要着色器语言
- 自动转换为 GLSL / Metal Performance Shader

## 10. 第三方依赖 (`External/`)

| 依赖 | 用途 |
|------|------|
| bullet | 物理引擎 |
| opengex | OpenGFX 场景格式解析 |
| glm | 数学库 |
| glad | OpenGL 加载器 |
| imgui | 即时模式 GUI |
| crossguid | UUID 生成 |
| cmft | 立方体贴图过滤 |
| astc-encoder | ASTC 纹理压缩 |
| bison | 解析器生成器 |
| glslang | GLSL 着色器编译 |
| zlib | 数据压缩 |
| cef | Chromium Embedded Framework |
| emsdk | Emscripten SDK |

## 11. 架构关系图

```
┌────────────────────────────────────────────────────────┐
│                    Game / Viewer                       │
│  (IGameLogic 实现 - 台球游戏、模型查看器)                │
├────────────────────────────────────────────────────────┤
│              Framework / Interface                     │
│  ┌──────────┐ ┌──────────┐ ┌──────────┐ ┌───────────┐ │
│  │ SceneGraph│ │ RenderPass│ │ Algorism │ │ Manager   │ │
│  │ (场景图)  │ │ (渲染管线)│ │ (算法库) │ │ (管理器)  │ │
│  └──────────┘ └──────────┘ └──────────┘ └───────────┘ │
├────────────────────────────────────────────────────────┤
│                       RHI                              │
│  ┌────────┐ ┌───────┐ ┌──────┐ ┌────────┐ ┌───────┐  │
│  │OpenGL  │ │Metal 2│ │D3D12 │ │Vulkan  │ │Empty  │  │
│  └────────┘ └───────┘ └──────┘ └────────┘ └───────┘  │
├────────────────────────────────────────────────────────┤
│                     Physics                            │
│           ┌──────────┐  ┌──────────┐                   │
│           │  Bullet  │  │   My     │                   │
│           └──────────┘  └──────────┘                   │
├────────────────────────────────────────────────────────┤
│                     Platform                           │
│  ┌────────┐ ┌───────┐ ┌──────┐ ┌────────┐ ┌───────┐  │
│  │Windows │ │Darwin │ │Linux │ │Android │ │  SDL  │  │
│  └────────┘ └───────┘ └──────┘ └────────┘ └───────┘  │
├────────────────────────────────────────────────────────┤
│                    External                            │
│  (glm, glad, imgui, bullet, opengex, zlib, ...)       │
└────────────────────────────────────────────────────────┘
```

## 12. 关键设计模式

1. **纯接口设计**: 所有子系统通过 `I` 前缀纯虚类定义接口，实现完全解耦
2. **RHI 抽象**: 统一的渲染硬件接口层，使上层代码无需关心底层图形 API
3. **对象-节点分离**: 场景图采用 SceneObject (数据) + SceneNode (结构) 分离设计
4. **可编程渲染管线**: DrawPass → DrawSubPass → DispatchPass 的分层渲染管线 + RenderGraph
5. **平台抽象**: 通过 Platform 层隔离操作系统差异
6. **Ability 混入**: 使用 Ability (Animatable, Hitable 等) 作为能力混入，而非继承
7. **着色器转译**: HLSL 作为源着色器语言，自动转译为各 API 原生着色器
8. **ISPC/CUDA 加速**: 支持通过 ISPC 或 CUDA 进行几何数学的并行计算
