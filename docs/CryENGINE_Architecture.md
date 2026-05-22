# CryENGINE v3.1.2 架构文档

## 1. 项目概述

**CryENGINE** 是由 Crytek 开发的商用 AAA 级游戏引擎，本仓库包含 PC 平台 v3.1.2 (Build 1742) 的完整源码。该引擎被用于《孤岛危机》(Crysis) 系列等知名游戏，以其先进的实时渲染技术和 sandbox 编辑器著称。

- **语言**: C++
- **构建系统**: Visual Studio 解决方案 (.sln / .vcproj)
- **目标平台**: Windows PC (32-bit)
- **源文件规模**: ~2,991 个 .cpp 文件

## 2. 顶层目录结构

```
CryENGINE_FullCode_PC_v3_1_2_1742/
├── Code/             # 引擎和工具源码
│   └── CryEngine/    # 引擎核心 (16个子系统)
├── Game/             # 游戏逻辑层 (Lua 脚本 + C++)
├── Bin32/            # 编译输出、DLL、资源编译器 (rc/)
├── BinTemp/          # 临时编译中间文件
└── Tools/            # 开发工具集
```

## 3. 引擎核心模块 (`Code/CryEngine/`)

CryENGINE 采用**模块化 DLL 架构**，每个子系统作为独立的 DLL 编译。共有 16 个核心模块:

```
CryEngine/
├── Cry3DEngine/       # 3D 渲染引擎
├── CryAction/         # 游戏框架 (Gameplay 框架)
├── CryAISystem/       # AI 系统
├── CryAnimation/      # 骨骼动画系统
├── CryCommon/         # 公共接口和类型定义
├── CryEntitySystem/   # 实体系统
├── CryFont/           # 字体渲染
├── CryInput/          # 输入管理
├── CryMovie/          # 过场动画 (CG)
├── CryNetwork/        # 网络通信
├── CryPhysics/        # 物理引擎
├── CryScriptSystem/   # 脚本系统 (Lua)
├── CrySoundSystem/    # 音频系统
├── CrySystem/         # 引擎系统核心 (初始化、主循环)
└── RenderDLL/         # 渲染后端 (D3D9 / NULL)
```

### 3.1 Cry3DEngine - 3D 渲染引擎

3D 引擎是 CryENGINE 最庞大的子系统，负责场景管理、可见性裁剪、光照、阴影、地形渲染等。

**关键组件**:

| 组件 | 关键文件 | 职责 |
|------|----------|------|
| **核心渲染** | `3dEngine.cpp`, `3DEngineRender.cpp`, `3dEngineLoad.cpp` | 主渲染循环、帧调度、场景加载 |
| **光照** | `3DEngineLight.cpp` | 动态/静态光照管理 |
| **渲染节点** | `Brush.cpp`, `DecalRenderNode.cpp`, `CloudRenderNode.cpp`, `AutoCubeMapRenderNode.cpp` | 各类可渲染对象 |
| **遮挡剔除** | `COcclusionCuller.cpp`, `COcclusionCullerClipper.cpp`, `COcclusionCullerPoly.cpp` | 软件遮挡剔除 |
| **Z-Buffer 裁剪** | `CZBufferCuller.cpp` | 基于深度缓冲的裁剪 |
| **体素数据** | `CVoxDataNode.cpp`, `CVoxMeshNode.cpp` | 体素化场景表示 |
| **贴花系统** | `Decal.cpp`, `DecalManager.cpp` | 动态贴花 |
| **云系统** | `CloudsManager.cpp`, `CloudRenderNode.cpp` | 体积云渲染 |
| **颜色溢出** | `ColorBleeding.cpp` | 全局光照近似 |
| **场景合并** | `3dEngineMerge.cpp` | 静态网格合并优化 |
| **CGF 模型** | `CGF/` | Crytek 几何格式加载 |
| **网格编译** | `MeshCompiler/` | 网格数据离线编译 |
| **等值面八叉树** | `IsoOctree/` | 等值面提取 (地形) |

### 3.2 RenderDLL - 渲染后端

渲染后端实现了底层图形 API 的抽象，支持可插拔的渲染器:

```
RenderDLL/
├── Common/            # 渲染器公共代码
│   ├── PostProcess/   # 后处理效果 (HDR, Bloom, SSAO, DOF 等)
│   ├── RendElements/  # 渲染元素 (各种渲染特性的实现)
│   ├── Shaders/       # 着色器代码
│   ├── Textures/      # 纹理管理
│   ├── ATI/           # AMD GPU 特定优化
│   └── NVAPI/         # NVIDIA GPU 特定优化
├── XRenderD3D9/      # DirectX 9 渲染器 (主要渲染后端)
│   ├── DeviceManager/ # D3D 设备管理
│   ├── DXPS/          # D3D 像素着色器工具
│   ├── DXUT/          # DirectX UI 工具包
│   └── Profiler/      # 渲染性能分析
└── XRenderNULL/      # 空渲染器 (用于服务端/测试)
```

### 3.3 CryAction - 游戏框架

CryAction 是连接引擎底层系统与游戏逻辑的桥梁，提供了完整的游戏开发框架:

| 子系统 | 职责 |
|--------|------|
| **AI** | AI 代理集成 |
| **Animation** | 角色动画控制 |
| **AnimationGraph** | 动画状态图 (混合树) |
| **FlowSystem** | 可视化流程脚本系统 (类似蓝图) |
| **GameObjects** | 游戏对象系统 (实体扩展) |
| **DialogSystem** | NPC 对话系统 |
| **EffectSystem** | 视觉效果管理 |
| **ForceFeedbackSystem** | 力反馈 (手柄震动) |
| **MaterialEffects** | 材质交互效果 (碰撞火花等) |
| **MusicLogic** | 动态音乐系统 |
| **GameTokens** | 游戏状态变量系统 |
| **GameplayRecorder** | 游戏过程录制/回放 |
| **CheckPoint** | 存档/检查点系统 |
| **Network** | 网络同步 |
| **LivePreview** | 实时预览 (编辑器) |

### 3.4 CryAISystem - AI 系统

完整的 AI 系统，包含:
- 导航网格 (NavMesh) 生成和路径搜索
- 行为树 / 有限状态机
- 感知系统 (视觉、听觉)
- 群组 AI
- 集群操作 (Formation, Tactical Point)

### 3.5 CryAnimation - 骨骼动画系统

- 骨骼动画混合
- IK (反向动力学)
- 表情动画
- 动画数据压缩
- CAF/CBA 动画格式支持

### 3.6 CryPhysics - 物理引擎

Crytek 自研物理引擎:
- 刚体动力学
- 碰撞检测
- 角色控制器
- 载具物理
- 布料模拟
- 破坏系统

### 3.7 CryEntitySystem - 实体系统

基于组件的实体管理:
- 实体创建/销毁/查询
- 组件注册 (RenderMesh, Physics, Script 等)
- 实体池 (Entity Pool) 优化
- 区域 (Sector) 管理

### 3.8 CryNetwork - 网络系统

- 客户端/服务端架构
- 远程调用 (RMI)
- 状态同步
- 网络预测和回滚
- 带宽优化

### 3.9 CryScriptSystem - 脚本系统

基于 **Lua** 的脚本系统:
- Lua 5.x 集成
- C++ 到 Lua 的绑定
- 脚本化实体行为
- 调试和性能分析支持

### 3.10 其他模块

| 模块 | 职责 |
|------|------|
| **CryCommon** | 引擎接口定义 (I3DEngine, ISystem, IRenderer 等) |
| **CryFont** | TrueType 字体渲染 |
| **CryInput** | 键盘、鼠标、手柄输入 |
| **CryMovie** | 实时过场动画序列器 |
| **CrySoundSystem** | 音频播放、3D 音效 |
| **CrySystem** | 引擎初始化、主循环、CVars (控制台变量)、内存管理 |

## 4. 游戏层 (`Game/`)

Game 目录包含用 CryAction 框架开发的游戏逻辑:

```
Game/
├── Entities/         # C++ 实体定义
└── Scripts/          # Lua 游戏脚本
    ├── AI/           # AI 行为脚本
    ├── BehaviorTree/ # 行为树定义
    ├── Entities/     # 实体脚本
    ├── FlowNodes/    # 流程脚本节点
    ├── GameRules/    # 游戏规则
    ├── Network/      # 网络逻辑
    ├── UI/           # 用户界面
    └── Utils/        # 工具函数
```

## 5. 架构关系图

```
┌─────────────────────────────────────────────────────────────┐
│                        Game Layer                           │
│  (Lua Scripts + C++ Entities)                               │
├─────────────────────────────────────────────────────────────┤
│                      CryAction                              │
│  (Game Framework: FlowSystem, GameObjects, AnimationGraph)  │
├──────────┬──────────┬──────────┬──────────┬─────────────────┤
│Cry3D     │CryPhysics│CryAI     │CryNetwork│CryAnimation     │
│Engine    │          │System    │          │                 │
├──────────┴──────────┴──────────┴──────────┴─────────────────┤
│  CryEntitySystem  │  CryScriptSystem  │  CrySoundSystem    │
├───────────────────┴───────────────────┴─────────────────────┤
│  CryFont  │  CryInput  │  CryMovie  │  CrySystem           │
├─────────────────────────────────────────────────────────────┤
│                   CryCommon (接口层)                         │
├─────────────────────────────────────────────────────────────┤
│               RenderDLL (D3D9 / NULL)                       │
└─────────────────────────────────────────────────────────────┘
```

## 6. 关键设计模式

1. **接口驱动设计**: CryCommon 定义所有子系统的纯虚接口，模块间通过接口解耦
2. **模块化 DLL**: 每个子系统编译为独立 DLL，支持热替换
3. **CVar 系统**: 全局控制台变量系统，运行时可调参数 (调试/优化利器)
4. **渲染节点 (RenderNode)**: 场景中的可渲染对象统一抽象为 RenderNode
5. **Flow System**: 可视化脚本系统，非程序员可通过流程图定义游戏逻辑
6. **Lua 脚本层**: 游戏逻辑主要用 Lua 实现，C++ 提供高性能核心
7. **GPU 厂商特定优化**: 通过 ATI/NVAPI 针对不同 GPU 进行优化
