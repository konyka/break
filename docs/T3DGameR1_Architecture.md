# T3DGameR1 架构文档

## 1. 项目概述

**T3DGameR1** 是 Andre' LaMothe 所著《Tricks of Windows Game Programming Gurus - Vol. I, Revision I》(Windows 游戏编程大师技巧) 的配套光盘资源。这是一本经典的 DirectX 游戏编程入门教材的完整配套代码库，包含 15 章教学源码、第三方引擎、示例游戏和大量参考资料。

- **语言**: C / 汇编 (x86)
- **图形 API**: DirectX 7/8
- **时代**: 1999-2002 年
- **许可证**: Sams Publishing / Pearson Education 版权，各程序保留各自许可

## 2. 顶层目录结构

```
T3DGameR1/T3DGameR1/
├── Source/           # 15 章教学源码 (T3DCHAP01 ~ T3DCHAP15)
├── Engines/          # 第三方引擎 (Genesis3D, PowerRender)
├── Games/            # 示例游戏
├── DirectX/          # DirectX SDK
├── Applications/     # 辅助应用程序
├── Articles/         # 技术文章集
├── Onlinebooks/      # 在线电子书
├── Artwork/          # 美术素材
├── Sound/            # 音频素材
└── Readme.txt        # 说明文件
```

## 3. 教学源码 (`Source/`)

全书 15 章，每章对应一个目录，包含从基础到进阶的渐进式教学:

### 章节内容概述

| 章节 | 关键文件 | 主题 |
|------|----------|------|
| **T3DCHAP01** | `blackbox.cpp`, `freakout.cpp` | Windows 编程基础、第一个游戏 |
| **T3DCHAP02-03** | | Windows 高级编程、GDI 绘图 |
| **T3DCHAP04-05** | | DirectX 基础、DirectDraw |
| **T3DCHAP06** | | 位图操作和精灵 |
| **T3DCHAP07** | | 输入处理 (DirectInput) |
| **T3DCHAP08** | | 声音和音乐 (DirectSound / DirectMusic) |
| **T3DCHAP09** | | 2D 动画和物理 |
| **T3DCHAP10** | | 高级 2D 图形 |
| **T3DCHAP11** | | 数学基础 (向量、矩阵、变换) |
| **T3DCHAP12** | | 3D 渲染基础 |
| **T3DCHAP13** | | 光照和纹理映射 |
| **T3DCHAP14** | | 高级 3D 渲染 |
| **T3DCHAP15** | `outpost.cpp`, `t3dlib1.cpp~t3dlib3.cpp` | 综合示例 - 完整 3D 游戏 |

### 核心库文件

教学源码附带了一套自研的 2D/3D 游戏开发库:

| 库文件 | 功能 |
|--------|------|
| `t3dlib1.cpp/.h` | T3D 核心库 - 窗口管理、DirectDraw 初始化、基础图形 |
| `t3dlib2.cpp/.h` | T3D 扩展库 - 位图操作、精灵、动画 |
| `t3dlib3.cpp/.h` | T3D 3D 库 - 3D 数学、软件光栅化、3D 渲染 |

## 4. 第三方引擎 (`Engines/`)

### 4.1 Genesis3D

```
Engines/Genesis3D/
└── Genesis3D/       # Eclipse Software 的开源 3D 引擎
```

Genesis3D 是 90 年代末流行的开源 3D 游戏引擎，由 Eclipse Software 开发，支持:
- 实时 3D 渲染 (软件/D3D)
- BSP 场景管理
- 基本物理碰撞
- 脚本系统

### 4.2 PowerRender

```
Engines/PowerRender/
├── prsdk40/         # PowerRender SDK 4.0
└── prsdk40.zip      # SDK 压缩包
```

PowerRender 是 Egerter Software 的商用 3D 渲染引擎 SDK，提供:
- 高性能 3D 渲染
- 多种文件格式导入
- 粒子系统
- 骨骼动画

## 5. 示例游戏 (`Games/`)

| 游戏 | 安装文件 | 说明 |
|------|----------|------|
| AI 2000 | `ai2000installsw.exe` | AI 展示游戏 |
| Columns Demo | `columnsdemoinstall.EXE` | 消除类游戏 |
| Electro Balz | `electrobalzdemo.EXE` | 弹珠类游戏 |
| Neo Dragoon | `neodragoondemo.exe` | 动作游戏 |

## 6. 辅助应用程序 (`Applications/`)

| 应用 | 用途 |
|------|------|
| ACROBAT/ | Adobe Acrobat Reader (查看 PDF 文档) |
| MSWordView/ | Word 文档查看器 |
| PaintShopPro/ | Paint Shop Pro 图像编辑器 |
| SForge/ | Sound Forge 音频编辑器 |
| TrueSpace/ | Caligari TrueSpace 3D 建模工具 |
| WINZIP/ | WinZip 压缩工具 |

## 7. 技术文章 (`Articles/`)

30+ 篇游戏开发技术文章:

| 主题 | 文章目录 |
|------|----------|
| 3D 技术 | `3DTechSeries/`, `3DViewing/`, `PolySorting/` |
| AI | `AIandBeyond/`, `AppliedAI/`, `ArtificialPersonalities/` |
| 渲染效果 | `ArtOfLensFlares/`, `D3DTransparency/`, `TextureMapMania/` |
| 动画 | `Dynamic3DAnimation/`, `HumanCharacters/` |
| 网络 | `LinkingUpDirectPlay/`, `Netware/`, `NetworkTrafficReduction/` |
| 优化 | `OptimizingWithMMX/`, `PentiumSecrets/` |
| 游戏设计 | `DesigningThePuzzle/`, `IntoTheGreyzone/` |
| 数据结构 | `KDTrees/`, `TileGraphics/` |
| 音频 | `MusicalContentFundamentals/` |
| 调试 | `XtremeDebugging/` |
| 开发 | `SmallGroupGameDev/`, `WebGamesOnAShoeString/`, `GPMegaSiteArticles/` |

## 8. 其他资源

### 美术素材 (`Artwork/`)
- 3D 模型
- 2D 图像素材

### 音频素材 (`Sound/`)
- MIDI 音乐
- 音效文件

### 在线书籍 (`Onlinebooks/`)
- 3D 图形编程电子书
- Direct3D 参考手册

## 9. 技术栈总结

```
┌──────────────────────────────────────┐
│        示例游戏 (Games/)             │
├──────────────────────────────────────┤
│    T3D 教学库 (t3dlib1~3)            │
├──────────────────────────────────────┤
│   DirectX 7/8 SDK                    │
│   (DirectDraw, DirectInput,          │
│    DirectSound, DirectMusic)         │
├──────────────────────────────────────┤
│   第三方引擎                          │
│   (Genesis3D, PowerRender)           │
├──────────────────────────────────────┤
│   Windows API / C Runtime            │
└──────────────────────────────────────┘
```

## 10. 历史意义

T3DGameR1 是 90 年代末到 2000 年代初游戏编程教育的典型代表:
- 教授了 DirectX 底层编程而非封装
- 包含软件光栅化实现 (理解 GPU 渲染原理的基础)
- 涵盖了从 Windows 编程到 3D 渲染的完整学习路径
- 附带了当时主流的第三方引擎供学习参考
