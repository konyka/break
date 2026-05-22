# Game Engine 代码仓库架构总览

源路径 `/home/timeshift/opensource/game_engine`，包含四个独立的游戏引擎/学习项目，涵盖了从商用级 MMO 引擎到教学示例引擎的不同层次。

## 项目概览

| 项目 | 类型 | 语言 | 规模 (cpp文件数) | 定位 |
|------|------|------|------------------|------|
| **BW191** (BigWorld) | 商用 MMO 引擎 | C++/Python | ~1,306 | 大型多人在线游戏服务端+客户端完整方案 |
| **CryENGINE v3.1.2** | 商用 AAA 游戏引擎 | C++ | ~2,991 | Crytek 的 AAA 级游戏引擎完整源码 |
| **GameEngineFromScratch** | 自研教学引擎 | C++20 | ~205+ (Framework+RHI) | 知乎专栏配套的"从零手敲次世代游戏引擎" |
| **T3DGameR1** | 教学配套资源 | C/DirectX | ~15 章节 | 《Windows游戏编程大师技巧》书籍配套源码和工具 |

## 目录结构

```
game_engine/
├── BW191/                          # BigWorld Technology MMO 引擎 v1.9.1
│   ├── bigworld/                   # 引擎核心 (src/client, src/server, src/common)
│   ├── fantasydemo/                # FantasyDemo 示例游戏
│   ├── lib/                        # 预编译第三方库
│   ├── directx-redist/             # DirectX 运行时
│   ├── fmod-redist/                # FMOD 音频运行时
│   └── vc80-redist/                # VS2005 VC++ 运行时
│
├── CryENGINE_FullCode_PC_v3_1_2_1742/  # CryENGINE 完整源码
│   ├── Code/CryEngine/             # 引擎核心模块 (16个子系统)
│   ├── Game/                       # 游戏逻辑层 (Lua脚本 + C++)
│   ├── Bin32/                      # 编译输出 & 资源编译器
│   └── Tools/                      # 开发工具集
│
├── GameEngineFromScratch/          # 从零构建的游戏引擎
│   ├── Framework/                  # 引擎框架层 (接口、场景图、算法、渲染管线)
│   ├── RHI/                        # 渲染硬件接口抽象 (OpenGL/Metal/D3D12/Vulkan)
│   ├── Physics/                    # 物理引擎 (Bullet + 自研)
│   ├── Platform/                   # 平台抽象层 (Win/Mac/Linux/Android)
│   ├── Asset/                      # 资源文件 (模型/纹理/着色器)
│   ├── Game/                       # 游戏示例 (台球游戏)
│   ├── Viewer/                     # 模型查看器
│   └── External/                   # 第三方依赖源码
│
├── T3DGameR1/                      # 《Tricks of Windows Game Programming Gurus》
│   └── T3DGameR1/
│       ├── Source/                 # 15 章教学源码 (T3DCHAP01 ~ T3DCHAP15)
│       ├── Engines/                # Genesis3D + PowerRender 引擎
│       ├── Games/                  # 示例游戏
│       ├── DirectX/                # DirectX SDK
│       ├── Applications/           # 辅助工具
│       ├── Articles/               # 技术文章
│       └── Onlinebooks/            # 在线电子书
│
└── docs/                           # 架构文档 (本文档所在目录，位于 break/docs/)
    ├── index.md                    # 总览 (本文档)
    ├── BW191_Architecture.md       # BigWorld 引擎架构
    ├── CryENGINE_Architecture.md   # CryENGINE 架构
    ├── GEFS_Architecture.md        # GameEngineFromScratch 架构
    ├── T3DGameR1_Architecture.md   # T3DGameR1 架构
    └── PureC_Engine_Proposal.md    # 纯 C (C11-C23) 跨平台游戏引擎方案
```

## 详细文档索引

### 现有代码库分析

- [BW191 (BigWorld) 引擎架构](./BW191_Architecture.md)
- [CryENGINE v3.1.2 架构](./CryENGINE_Architecture.md)
- [GameEngineFromScratch 架构](./GEFS_Architecture.md)
- [T3DGameR1 架构](./T3DGameR1_Architecture.md)

### 新引擎方案

- [纯 C (C11-C23) 跨平台游戏引擎方案](./PureC_Engine_Proposal.md) — 设计提案，持续更新
- [深度模块审查与方案优选](./PureC_Engine_DeepDive.md) — 10 个模块的缺陷分析 + 替代方案对比 + 最优选择
- [执行计划](./PureC_Engine_ExecutionPlan.md) — 4 Phase 路线图 + 依赖图 + 风险矩阵 + 时间线
