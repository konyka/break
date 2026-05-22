# BW191 - BigWorld Technology MMO 引擎架构

## 1. 项目概述

**BigWorld Technology** 是一款专为大型多人在线游戏 (MMO) 设计的商用游戏引擎中间件，版本号 1.9.1。该引擎曾被用于《魔兽世界》(World of Warcraft) 等知名 MMO 游戏。BW191 提供了从服务端集群到客户端渲染的完整 MMO 解决方案。

- **语言**: C++ (核心) + Python (脚本/工具)
- **构建系统**: Visual Studio 2005 项目文件 (.vcproj) + Makefile (Linux)
- **目标平台**: Windows (客户端), Linux (服务端)
- **源文件规模**: ~1,306 个 .cpp 文件

## 2. 顶层目录结构

```
BW191/
├── bigworld/          # 引擎核心代码和资源
│   ├── src/           # C++ 源码 (client / server / common / egclient*)
│   ├── res/           # 引擎资源 (脚本、着色器、配置)
│   ├── bin/           # 编译输出和命令脚本
│   ├── doc/           # 技术文档 (HTML + 训练资料)
│   └── lib/           # 引擎库文件
├── fantasydemo/       # FantasyDemo 示例游戏
│   ├── src/           # 示例游戏源码 (client / web)
│   ├── res/           # 游戏资源 (角色、环境、地图、粒子等)
│   ├── audio/         # 音频资源
│   └── tools/         # 内容创建工具
├── lib/               # 第三方预编译库
├── directx-redist/    # DirectX 运行时
├── fmod-redist/       # FMOD 音频引擎运行时
└── vc80-redist/       # Visual C++ 2005 运行时
```

## 3. 核心源码架构 (`bigworld/src/`)

### 3.1 客户端 (`src/client/`)

客户端模块是引擎的前端，约 59 个 .cpp 文件，负责渲染、实体管理和用户交互。

**核心子系统**:

| 子系统 | 关键文件 | 职责 |
|--------|----------|------|
| **应用框架** | `app.cpp`, `camera_app.cpp`, `device_app.cpp`, `gui_app.cpp` | 应用生命周期管理，设备初始化 |
| **实体系统** | `entity.cpp`, `entity_manager.cpp`, `entity_type.cpp`, `entity_picker.cpp` | 实体创建、销毁、查询、类型管理 |
| **网络连接** | `connection_control.cpp`, `servconn.cpp` (common) | 与服务端通信、连接管理 |
| **相机系统** | `client_camera.cpp`, `camera_app.cpp` | 第一/第三人称相机控制 |
| **过滤器系统** | `filter.cpp`, `avatar_filter.cpp`, `boids_filter.cpp`, `dumb_filter.cpp` | 实体位置/状态同步过滤 (客户端预测/插值) |
| **LOD 控制** | `adaptive_lod_controller.cpp` | 自适应细节层次控制 |
| **VoIP** | `bwvoip.cpp` | 语音通信 |
| **动作匹配** | `action_matcher.cpp` | 动画状态机 / 动作选择 |

### 3.2 服务端 (`src/server/`)

BigWorld 的服务端采用**分布式微服务架构**，每个组件作为独立进程运行，这是 MMO 引擎的典型设计。

```
server/
├── baseapp/          # Base App - 玩家持久化实体服务
├── baseappmgr/       # Base App Manager - Base App 集群管理器
├── cellapp/          # Cell App - 空间分区实体计算服务
├── cellappmgr/       # Cell App Manager - Cell App 集群管理器
├── dbmgr/            # Database Manager - 数据库持久化管理
├── loginapp/         # Login App - 登录认证服务
├── reviver/          # Reviver - 故障恢复服务
├── common/           # 服务端共享代码
├── egextra/          # 额外扩展
├── web/              # Web 接口 (PHP / Python)
│   ├── php/
│   └── python/
└── tools/            # 运维工具集
    ├── bots/            # 机器人测试工具
    ├── bwmachined/      # 机器守护进程
    ├── consolidate_dbs/ # 数据库合并工具
    ├── eload/           # 负载测试工具
    ├── message_logger/  # 消息日志工具
    ├── mls/             # MLS 工具
    ├── runscript/       # 脚本运行器
    ├── snapshot_helper/ # 快照辅助工具
    └── watcher/         # 系统监控工具
```

**服务端架构模式**:

```
                    ┌─────────────┐
                    │  LoginApp   │  ← 客户端登录入口
                    └──────┬──────┘
                           │
                    ┌──────▼──────┐
                    │ BaseAppMgr  │  ← BaseApp 集群协调器
                    └──────┬──────┘
              ┌────────────┼────────────┐
         ┌────▼────┐  ┌────▼────┐  ┌───▼─────┐
         │ BaseApp │  │ BaseApp │  │ BaseApp │  ← 每个玩家一个 BaseApp 实体
         └────┬────┘  └────┬────┘  └───┬─────┘
              │              │           │
                    ┌───────▼────────┐
                    │  CellAppMgr    │  ← CellApp 集群协调器
                    └───────┬────────┘
              ┌────────────┼────────────┐
         ┌────▼────┐  ┌────▼────┐  ┌───▼─────┐
         │ CellApp │  │ CellApp │  │ CellApp │  ← 空间分区 (Cell) 计算
         └────┬────┘  └────┬────┘  └───┬─────┘
              └────────────┼────────────┘
                    ┌──────▼──────┐
                    │   DBMgr     │  ← 数据库持久化
                    └─────────────┘
```

### 3.3 公共模块 (`src/common/`)

客户端和服务端共享的基础设施代码:

| 组件 | 职责 |
|------|------|
| `chunk_portal.cpp/hpp` | 空间分块与入口/出口管理 (室内场景) |
| `client_interface.cpp/hpp` | 客户端接口定义 |
| `login_interface.cpp/hpp` | 登录协议接口 |
| `servconn.cpp/hpp` | 服务端连接管理 |
| `py_moo.cpp` / `py_network.cpp` / `py_physics2.cpp` | Python 绑定 (实体、网络、物理) |
| `shared_data.cpp/hpp` | 共享数据管理 |
| `doc_watcher.cpp/hpp` | 文档/配置热重载监听 |

### 3.4 精简客户端 (`src/egclient*`)

引擎提供了 4 个逐步递进的客户端变体 (egclient ~ egclient4)，用于教学和快速集成:

| 变体 | 特点 |
|------|------|
| `egclient` | 最简客户端入口，仅 `main.cpp` + `pch` |
| `egclient2` | 添加 entity / entity_type 管理 |
| `egclient3` | 进一步精简版 |
| `egclient4` | 完整版，含 Python 绑定 (`py_entities`, `py_server`) |

## 4. FantasyDemo 示例游戏

`fantasydemo/` 是一个完整的奇幻风格 MMO 示例游戏，展示了引擎的全部功能:

```
fantasydemo/
├── src/
│   ├── client/       # 游戏客户端逻辑
│   └── web/          # Web 集成 (账号管理等)
├── res/
│   ├── characters/   # 角色模型和动画
│   ├── environments/ # 环境场景
│   ├── flora/        # 植被系统
│   ├── gui/          # UI 资源
│   ├── maps/         # 地图数据
│   ├── materials/    # 材质定义
│   ├── objects/      # 静态物体
│   ├── particles/    # 粒子效果
│   ├── scripts/      # Python 游戏脚本
│   ├── server/       # 服务端配置
│   ├── shaders/      # 着色器
│   ├── spaces/       # 空间定义
│   ├── speedtree/    # SpeedTree 植被数据
│   └── system/       # 系统配置文件
├── audio/
│   ├── atmos/        # 环境音
│   ├── fx/           # 音效
│   └── ui/           # UI 音效
└── tools/
    └── cat/          # 资源查看/处理工具
```

## 5. 脚本系统

BigWorld 大量使用 **Python** 作为脚本语言:

- **客户端脚本**: `bigworld/res/scripts/client/` - UI 交互、图形预设、键位绑定、过滤器工具
- **公共脚本**: `bigworld/res/scripts/common/` - 包含完整 Python 标准库子集 + 自定义工具
- **服务端脚本**: 通过 Python 实现游戏逻辑，C++ 核心通过 `py_moo`, `py_network`, `py_physics2` 暴露接口

## 6. 文档体系

`bigworld/doc/` 包含完整的引擎文档:

| 文档 | 内容 |
|------|------|
| `client_programming_guide/` | 客户端编程指南 |
| `server_programming_guide/` | 服务端编程指南 |
| `server_operations_guide/` | 服务端运维指南 |
| `server_overview/` | 服务端架构概述 |
| `content_tools_reference_guide/` | 内容工具参考 |
| `file_grammar_guide/` | 文件格式说明 |
| `glossary_of_terms/` | 术语表 |
| `bigworld_tutorial/` | 入门教程 |
| `web_integration/` | Web 集成指南 |
| `howto_*` | 各种操作指南 (构建载具、移动平台、内存泄漏检测等) |
| `api_cpp/` / `api_python/` | C++ / Python API 参考 |

## 7. 关键设计模式

1. **分布式服务架构**: 服务端采用多进程微服务设计，支持水平扩展
2. **Cell 分区**: 游戏世界按空间划分为 Cell，由不同 CellApp 管理
3. **BaseApp 实体管理**: 每个玩家实体绑定到特定 BaseApp，保证状态一致性
4. **客户端过滤系统**: 多种过滤器 (AvatarFilter, BoidsFilter, DumbFilter) 处理网络延迟下的实体位置插值和预测
5. **Python 脚本驱动**: 游戏逻辑通过 Python 脚本实现，C++ 核心提供高性能计算
6. **自适应 LOD**: 根据性能指标动态调整渲染细节
