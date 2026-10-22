# 12 物理(续):接口清单续、线程模型、配置与扩展点

本文件是 `12_physics_chaos.md` 的续篇,承接其 12.5 接口清单与 12.8~12.10 小节。路径与行号约定同主文件。

## 12.5 接口清单(续)

### 12.5.7 约束数据与容器

| 原型(去 *_API) | 功能 | 线程 | 位置 |
|---|---|---|---|
| `class FPBDJointConstraints : public TPBDIndexedConstraintContainer<FPBDJointConstraints>`(Linear/NonLinear 两份,组合进 `FPBDJointCombinedConstraints`) | 关节约束容器(位置迭代/速度迭代/投影迭代) | PT | Chaos/PBDJointConstraints.h;组合见 PBDRigidsSolver.h:121 |
| `class FPBDSuspensionConstraints : public TPBDIndexedConstraintContainer<FPBDSuspensionConstraints>` | 悬挂约束容器(车辆轮悬挂) | PT | Chaos/PBDSuspensionConstraints.h:63 |
| `void FPBDRigidsSolver::SetSuspensionTarget(Chaos::FSuspensionConstraint* GTConstraint, const FVector& TargetPos, const FVector& Normal, bool Enabled, const IPhysicsProxyBase* GroundProxy = nullptr)` | GT 设置悬挂目标 | GT | PBDRigidsSolver.h:240 |
| `enum class EJointMotionType : int32` | 关节自由度类型(Locked/Limited/Free) | — | Chaos/PBDJointConstraintTypes.h:22 |
| `TSet<FPBDRigidParticleHandle*> FRigidClustering::DeactivateClusterParticle(FPBDRigidClusteredParticleHandle* ClusteredParticle)` | 碎裂:解散簇粒子返回释放的孩子 | PT | Chaos/PBDRigidClustering.h:145 |
| `void FRigidClustering::AdvanceClustering(const FReal dt, FPBDCollisionConstraints& CollisionRule)` | 每步簇状态机(连通性/破碎/层级) | PT | PBDRigidClustering.h:216 |
| `FClusterUnionManager`(Chaos/ClusterUnionManager.h) | ClusterUnion(手工簇)管理 | PT | Public/Chaos/ClusterUnionManager.h |
| `FCharacterGroundConstraintContainer`(Chaos/Character/CharacterGroundConstraintContainer.h) | 角色地面约束容器(Kinematic 角色与物理地面交互) | PT | 见 PBDRigidsEvolutionGBF.h:159 |

### 12.5.8 FieldSystem(场系统)

| 原型(去 *_API) | 功能 | 线程 | 位置 |
|---|---|---|---|
| `class FFieldSystemCommand` | 一条场求值命令(meta+node 树+目标),GT 构建后入队 PT | GT 构建/PT 求值 | Chaos/Public/Field/FieldSystem.h:522 |
| `class FFieldSystemMetaData`(及 ProcessingResolution/Filter/Results/Iteration/Culling 派生,:155-218) | 命令元数据(求值分辨率、目标过滤、迭代) | — | FieldSystem.h |
| `FFieldSystemNodes.h` 中的节点类(UniformVector/RadialIntMask/Operators 等) | 场节点求值拓扑 | — | Chaos/Public/Field/FieldSystemNodes.h |
| `FPerSolverFieldSystem & FPBDRigidsSolver::GetPerSolverField()` | solver 侧场求值上下文 | PT | PBDRigidsSolver.h:315 |
| `void FPBDRigidsSolver::FieldForcesUpdateCallback()` / `FieldParameterUpdateCallback(Chaos::FPBDPositionConstraints&, TMap<int32,int32>&)` | 场求值→粒子力/目标更新 | PT | PBDRigidsSolver.h:345/350 |
| UFieldSystemComponent / UFieldSystemActor / UFieldSystemAsset | 引擎侧场组件/actor/资产 | GT | FieldSystem/Source/FieldSystemEngine/Public/Field/FieldSystemComponent.h 等 |

### 12.5.9 GeometryCollection(破碎)

| 原型(去 *_API) | 功能 | 线程 | 位置 |
|---|---|---|---|
| `class UGeometryCollectionComponent : public UMeshComponent, public IChaosNotifyHandlerInterface` | 破碎组件:创建 FGeometryCollectionPhysicsProxy、接收 Chaos 事件 | GT | GeometryCollectionEngine/Public/GeometryCollection/GeometryCollectionComponent.h:577 |
| `class FGeometryCollectionPhysicsProxy : public TPhysicsProxy<FGeometryCollectionPhysicsProxy, FStubGeometryCollectionData, FGeometryCollectionProxyTimestamp>` | 破碎集合 Proxy(GT 资产 ↔ PT 粒子簇) | GT/PT | Chaos/Public/PhysicsProxy/GeometryCollectionPhysicsProxy.h:142 |
| `void FGeometryCollectionPhysicsProxy::PushStateOnGameThread(Chaos::FPBDRigidsSolver* InSolver)` | GT→PT 推送 | GT | :236 |
| `void FGeometryCollectionPhysicsProxy::BufferPhysicsResults_Internal(Chaos::FPBDRigidsSolver* CurrentSolver, Chaos::FDirtyGeometryCollectionData& BufferData)` | PT 回写载荷 | PT | :230 |
| `class AChaosSolverActor : public AActor, public IDataflowPhysicsSolverInterface` | 独立 solver 的 Actor 封装(每 Actor 一个 FPhysScene_Chaos/solver) | GT | ChaosSolverEngine/Public/Chaos/ChaosSolverActor.h:107 |
| `UChaosSolverSettings : UDeveloperSettings`(ChaosSolverSettings.h:14,config=Engine)与 `FChaosSolverConfiguration`(ChaosSolverConfiguration.h) | solver 全局设置(默认 Solver Actor 类)与传给 `FPBDRigidsSolver::ApplyConfig` 的配置(迭代数、余量、事件开关) | GT | ChaosSolverEngine/Public/Chaos/ChaosSolverSettings.h;Chaos/Public/ChaosSolverConfiguration.h |
| FChaosBreakingEventFilter/FChaosCollisionEventFilter/FChaosRemovalEventFilter/FChaosTrailingEventFilter | 事件过滤(阈值/感兴趣组件) | GT/PT | GeometryCollectionEngine/Public/Chaos*EventFilter.h |
| `UGeometryCollectionCache`(GeometryCollectionCache.h)+ ChaosCaching | 破碎记录/回放缓存 | GT | GeometryCollectionEngine/Public/GeometryCollection/GeometryCollectionCache.h |
| FractureEngine 算法族(FractureEngineFracturing/Clustering/Convex/Embed/Sampling/Selection) | 编辑器破碎几何(调用 PlanarCut/Voronoi) | 编辑器 GT | Plugins/Experimental/Fracture/Source/FractureEngine/Public |
| `PlanarCut.h`(PlanarCutPlugin) | 平面切割网格 | 工具线程 | Plugins/Experimental/PlanarCutPlugin/Source/PlanarCut/Public/PlanarCut.h |
| Voronoi 模块(Voronoi/...) | Voronoi 单元与剖分 | 工具线程 | Runtime/Experimental/Voronoi/Public |

### 12.5.10 RewindData(网络重模拟)

| 原型(去 *_API) | 功能 | 线程 | 位置 |
|---|---|---|---|
| `FRewindData(FPBDRigidsSolver* InSolver, int32 NumFrames, bool InRewindDataOptimization, int32 InCurrentFrame)` | 构造 rewind 历史(容量 NumFrames) | GT | RewindData.h:1778 |
| `void AdvanceFrame(FReal DeltaTime, const CreateCache& CreateCacheFunc)` | 每步前推进帧指针/准备 resim 缓存 | PT | RewindData.h:1867 |
| `void FinishFrame()` | 步末提交(LatestFrame 前进) | PT | RewindData.h:1904 |
| `void RewindToFrame(int32 RewindFrame)` | 回退到指定帧(重模拟) | PT | RewindData.h:2269 |
| `void MarkDirtyFromPT(FGeometryParticleHandle& Handle)` | PT 修改粒子时缓存旧值(PostPushData 相位) | PT | RewindData.h:1930 |
| `void PushGTDirtyData(const FDirtyPropertiesManager& SrcManager, const int32 SrcDataIdx, const FDirtyProxy& Dirty, const FShapeDirtyData* ShapeDirtyData)` | GT 脏数据进历史 | GT(PT 消费时调) | RewindData.h:1924 |
| `FGeometryParticleState GetPastStateAtFrame(const FGeometryParticleHandle& Handle, int32 Frame, FFrameAndPhase::EParticleHistoryPhase Phase = ...PostPushData) const` | 查询历史状态 | PT | RewindData.h:1850 |
| `void AddInputHistory/AddStateHistory(const TSharedPtr<FBaseRewindHistory>&, ...)` | 外部输入/状态历史注册(网络预测输入) | GT | RewindData.h:1940/1972 |
| `bool IsResim() const { return CurFrame < LatestFrame; }` | 是否处于重模拟 | PT | RewindData.h:1910 |

### 12.5.11 插件族接口要点

| 系统 | 关键类型 | 说明 | 位置($UE/Engine/Plugins 下) |
|---|---|---|---|
| ChaosVehiclesPlugin | `UChaosVehicleMovementComponent : UPawnMovementComponent`(:721)、`UWheeledVehiclePawn`、`UChaosWheeledVehicleMovementComponent`、`FChaosVehicleManager`(:17)、`FChaosVehicleManagerAsyncCallback`(:475) | 完整车辆模型(引擎/传动/轮胎/悬挂),模拟在 PT 回调 | Experimental/ChaosVehiclesPlugin/Source/ChaosVehicles/Public |
| ChaosModularVehicle | `UModularVehicleBaseComponent`(ModularVehicleBaseComponent.h)、`FChaosSimModuleManagerAsyncCallback`(ChaosSimModuleManagerAsyncCallback.h)、SimModule 组件族 `UVehicleSimWheelComponent/SuspensionSimModule.h` 等 | 可组合模块化车辆(每轮/发动机/扰流板独立 SimModule),基于 ClusterUnion | Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEngine/Public/ChaosModularVehicle |
| Mover + ChaosMover | `UMoverSimulation`(MoverSimulation.h:24)、`UMoverComponent`(Mover/Public)、`UChaosMoverSimulation : UMoverSimulation`(ChaosMoverSimulation.h:36)、`UMovementModeStateMachine`(MovementModeStateMachine.h:27) | 角色移动框架;ChaosMover 提供 Chaos 侧执行器与移动模式 | Experimental/Mover、Experimental/ChaosMover |
| ChaosCaching | `AChaosCacheManager : AActor`(CacheManagerActor.h:188)、`AChaosCachePlayer`(同文件 :491)、`UChaosCache`(ChaosCache.h)、CacheCollection/CacheEvents | 物理/破碎过程缓存回放(配合 IndexedCacheStorage/DDC) | Experimental/ChaosCaching/Source/ChaosCaching/Public/Chaos |
| ChaosCloth 家族 | `UChaosClothComponent`(ChaosClothAssetEngine/Public/ChaosClothAsset/ClothComponent.h:86)、ChaosCloth 模块的 `ChaosClothConstraints.h`/`ChaosClothingSimulation.h`、`UChaosClothAsset`(ChaosClothAsset)、Dataflow 节点集 | XPBD 布料(拉伸/弯曲/自碰/风场);注意该家族在 Plugins/ChaosCloth、Plugins/ChaosClothAsset(非 Experimental) | ChaosCloth/Source/ChaosCloth、ChaosClothAsset/Source/* |
| ChaosFlesh | `FFleshCollection : FTetrahedralCollection`(ChaosFlesh/Public/ChaosFlesh/FleshCollection.h:17)、XPBDCorotated/XPBDVolume tet 约束节点(ChaosFleshNodes) | 软组织 FEM/XPBD,Dataflow 构建 | Experimental/ChaosFlesh/Source |
| ChaosRigidAsset | ChaosRigidAssetNodes 的 Dataflow 节点(BoneSelection.h、Private/Generators/BoneGeometryGenerators.h、ConstraintGenerators.h 等)、ChaosRigidAssetEngine 的 PhysicsAssetDataflowAttachment | Dataflow 图构建物理资产刚体数据(cook 输入) | Experimental/ChaosRigidAsset/Source |
| ChaosRigidPhysicsAsync | RigidPhysics 抽象的 PT 桥(SimCallbackObject) | 新刚体接口在物理线程的执行 | Experimental/ChaosRigidPhysicsAsync/Source |
| ChaosNiagara | `UNiagaraDataInterfaceGeometryCollection`(NiagaraDataInterfaceGeometryCollection.h) | Niagara 直接读取 GC 模拟数据做特效 | Experimental/ChaosNiagara/Source/ChaosNiagara/Public |
| ChaosUserDataPT | ChaosUserDataPT.h 的用户数据容器 | GT/PT 双侧用户数据镜像与回调 | Experimental/ChaosUserDataPT/Source |
| Buoyancy | `UBuoyancySubsystem`、`FBuoyancyField`、`FBuoyancyAlgorithms`、`IBuoyancyEventInterface` | 浮力波场/事件;PT 侧逐格浮力在 Chaos 的 PerCellBuoyancy.h | Experimental/Buoyancy/Source/Runtime/Public |
| PhysicsControl | `UPhysicsControlComponent/UPhysicsControlAsset`、`UAnimNode_RigidBodyWithControl`、`FPhysicsControlData` | 肌肉式物理控制(目标驱动+增益),AnimGraph 集成 | Animation/PhysicsControl/Source/PhysicsControl/Public |
| HeadlessChaos | `IMPLEMENT_APPLICATION(HeadlessChaos, "HeadlessChaos")`(HeadlessChaosApp.cpp:69) | 无引擎 Chaos 测试宿主(gtest 集成、缓存 merge 工具) | Source/Programs/HeadlessChaos |

## 12.8 线程模型与同步

### 12.8.1 谁在哪个线程

| 执行体 | 线程 | 判定依据 |
|---|---|---|
| `FStartPhysicsTickFunction`/`FEndPhysicsTickFunction` | Game Thread,TG_StartPhysics/TG_EndPhysics | `StartPhysicsTickFunction.TickGroup = TG_StartPhysics`(PhysLevel.cpp:160-167);`FEndPhysicsTickFunction::ExecuteTick` 内 `ENamedThreads::GameThread` 派发 FinishPhysicsSim(PhysLevel.cpp:280) |
| `FPBDRigidsSolver::PushPhysicsState` | Game Thread(内部 `ParallelForEachProxy` 走 TaskGraph 并行) | `AdvanceAndDispatch_External` 由 `FChaosScene::StartFrame`(GT)调用(ChaosScene.cpp:379) |
| `FPhysicsSolverProcessPushDataTask`/`FPhysicsSolverAdvanceTask`/`FPhysicsSolverRewindTask` | TaskGraph 工作线程 | `GetDesiredThread()` 返回 `CPrio_FPhysicsTickTask.Get()`(PhysicsSolverBase.cpp:111-124);优先级 cvar `TaskGraph.TaskPriorities.PhysicsTickTask`(HighThreadPriority/NormalTaskPriority) |
| `p.PhysicsRunsOnGT=1` 时 Advance/Rewind 任务 | Game Thread | `PhysicsRunsOnGT == 0 ? CPrio : ENamedThreads::GameThread`(PhysicsSolverBase.cpp:118) |
| `FPhysicsSolverFrozenGTPreSimCallbacks` | Game Thread 高优先级 | `ENamedThreads::SetTaskPriority(ENamedThreads::GameThread, ENamedThreads::HighTaskPriority)`(PhysicsSolverBase.h:138) |
| Evolution 内部并行(Integrate/NarrowPhase/BufferResults) | TaskGraph(Chaos 自有 TaskDispatcher:Private/TaskDispatcherSolver.cpp) | `TaskDispatcher->Initialize(DirtyParticles)`(PBDRigidsSolver.cpp:3010)、`PhysicsParallelFor`(Chaos/ParallelFor.h) |
| SimCallbackObject(车辆/布料等) | 物理线程上下文 | `FPhysicsThreadContextScope Scope(true)` 包裹(PhysicsSolverBase.cpp:137-139/240-242);`PHYSICS_THREAD_CONTEXT` 宏(Framework/Threading.h:21-27) |
| 事件派发 `SyncEvents_GameThread` | Game Thread | 由 `FChaosScene::EndFrame` 调用(ChaosScene.cpp:567),EndFrame 只在 GT tick |
| SQ 查询 | Game Thread(读外部拷贝)或物理线程(内部接口) | GT 版经 `FPhysicsSceneGuardScopedRead`;PT 版 `FGenericPhysicsInterface_Internal`(GenericPhysicsInterface.h:108-156) |
| 专用物理线程(DedicatedThread) | **5.8.3 中未实际启用** | `FPersistentPhysicsTask` 仅有前向声明(PhysicsSolverBase.h:255);`bPersistentTaskSpawned` 恒 false(ChaosSolversModule.cpp:71),`SyncTask` 实现为 `#if 0`(ChaosSolversModule.cpp:164-177) |

### 12.8.2 队列与锁

| 同步原语 | 保护对象 | 说明 |
|---|---|---|
| `FChaosMarshallingManager` 双 SPSC 队列 | `ExternalQueue`(GT→PT PushData)、`PullDataQueue`(PT→GT 结果) | `TPhysicsSpscQueue`(Threading.h:1204-1210;AutoRTFM 时用事务安全版) |
| `MarshallingManagerLock`(FRWLock) | ProducerData 的脏集/命令列表 | `UE_CHAOS_ASYNC_INITBODY_WRITESCOPELOCK`(ChaosMarshallingManager.h:338-434);`p.Chaos.EnableAsyncInitBody=1` 时允许非 GT 线程注册 body |
| `FPhysSceneLock`(FPhysSceneLockRemoteObject/FPhysSceneLockTransactionallySafe) | solver 外部数据(GT 侧粒子、外部加速结构) | 递归 RW;编辑器配置 `CHAOS_SCENE_LOCK_RWFIFO_CRITICALSECTION`,非编辑器 `CHAOS_SCENE_LOCK_FRWLOCK`(Threading.h:41-50);`GetExternalDataLock_External()`(PhysicsSolverBase.h:1027) |
| `InternalDataLock` | UE_WITH_REMOTE_OBJECT_HANDLE 时的 PT 内部数据 | `FPhysicsSceneGuardScopedWrite`(PhysicsSolverBase.cpp:245) |
| `SimMaterialLock`(FRWLock) | `SimMaterials/SimMaterialMasks` | `TSolverSimMaterialScope<ELockType>`(PBDRigidsSolver.h:512-552) |
| `SolverLock`(FCriticalSection) | FChaosSolversModule::AllSolvers/SolverMap | `FChaosScopeSolverLock`(ChaosSolversModule.h:356) |
| `NumPendingSolverAdvanceTasks`(TAtomic) | 在途 Advance 任务计数(DoNoBlock 丢步判定) | PhysicsSolverBase.h:976;cpp:209/259 |
| `FPhysicsThreadContext`(TLS 单例) | 线程上下文调试标记(GT 上下文/物理上下文/冻结 GT) | Framework/Threading.h:171-309;`VerifyContext()` 消费(SingleParticlePhysicsProxy.h:1109) |

### 12.8.3 数据所有权(GT/PT 双缓冲)

| 数据 | GT 份 | PT 份 | 同步机制 |
|---|---|---|---|
| 单粒子状态 | `FGeometryParticle`(TUniquePtr,Proxy 持有) | `FGeometryParticleHandle`(SOA/Handle) | GT 写:属性标脏→`FDirtyChaosProperties`/`FDirtyPropertiesManager`(ParticleDirtyFlags.h:1227/1137)→PushData;PT 写:每步 `BufferPhysicsResults`→PullData→`PullFromPhysicsState`(可插值) |
| 物理材质 | `QueryMaterials_External` | `SimMaterials` | `FPhysicalMaterialManager` 委托→`FPBDRigidsSolver::UpdateMaterial/CreateMaterial`(PBDRigidsSolver.h:293-298);`SyncQueryMaterials_External()`(:307)把 sim 份拷给 SQ 份 |
| 加速结构 | solver 外部拷贝(`SolverAccelerationStructure`) | `InternalAccelerationStructure` | EndFrame `CopySolverAccelerationStructure()`(ChaosScene.h:128);GT 立即操作走 `UpdateParticleInAccelerationStructure_External`(PhysicsSolverBase.h:688) |
| 几何(cook 后 FImplicitObject) | 共享只读(RefCounted) | 同一对象 | `Particle->LockGeometry()`(PBDRigidsSolver.cpp:1604)防中途释放 |
| 输入(力/冲量/kinematic 目标) | GT 粒子累积字段 | PushData 应用 | `ClearAccumulatedData()`(PhysicsProxy.h:108)推送后清零防重复累积 |
| 事件 | 三缓冲读端 | 写端 | `FEventManager`/`FlipEventManagerBuffer`(PBDRigidsSolver.h:259) |

## 12.9 配置与扩展点

### 12.9.1 Console 变量(CVar)

| CVar | 默认 | 作用 | 源码位置 |
|---|---|---|---|
| `p.Chaos.DedicatedThreadEnabled` | 1 | 名义上的专用线程开关(5.8.3 未实际派生线程,见 12.10) | ChaosSolversModule.cpp:21 |
| `p.Chaos.Thread.DesiredHz` / `p.Chaos.Thread.WaitThreshold` | 60 / 0 | 专用线程频率/等待阈值(当前死代码) | ChaosSolversModule.cpp:28/33 |
| `p.PhysicsRunsOnGT` | 0 | 物理解算任务跑 Game Thread | PhysicsSolverBase.cpp:108-109 |
| `p.UseAsyncInterpolation` | 1 | 异步结果插值开关(`UseAsyncInterpolation`) | PhysicsSolverBase.cpp:262-263 |
| `p.ForceDisableAsyncPhysics` | 0 | 强制关闭异步物理 | PhysicsSolverBase.cpp:265-266 |
| `p.AsyncInterpolationMultiplier` | 2 | 插值回看倍数 | PhysicsSolverBase.cpp:284-285 |
| `p.AsyncPhysicsBlockMode` | 0 | EAsyncBlockMode | PhysicsSolverBase.cpp:291-294 |
| `p.MaxPhysicsStepsPerGameTick` | 3 | DoNoBlock 模式最大在途步数 | PhysicsSolverBase.cpp:578-579 |
| `P.Chaos.Simulation.Enable` | 1 | 总开关(=0 时 StartFrame/EndFrame 直接 return) | ChaosScene.cpp:55 |
| `p.Chaos.Simulation.ApplySolverProjectSettings` | 1 | 创建 solver 时应用项目设置 | ChaosScene.cpp:56 |
| `p.Chaos.Solver.Sleep.Defaults.SleepCounterThreshold` | 20 | 睡眠计数阈值 | Private/Chaos/Island/IslandManager.cpp:122-123 |
| `p.Chaos.Solver.Sleep.IsolatedParticle.CounterMultiplier` | 1 | 无约束粒子睡眠阈值倍数 | IslandManager.cpp:141-142 |
| `p.Chaos.Solver.CollisionSolverType` | -1 | GaussSeidel/GaussSeidelSimd/PartialJacobi | PBDRigidsEvolutionGBF.cpp:503-527 |
| `TaskGraph.TaskPriorities.PhysicsTickTask` | High/Normal | 物理任务优先级 | PhysicsSolverBase.cpp:100-106 |
| `p.Chaos.EnableAsyncInitBody` | false | 允许 body 创建/销毁在 worker 线程执行(ReadOnly,须在 DefaultEngine.ini 预设) | Chaos/Private/Chaos/AsyncInitBodyHelper.cpp:10-17 |
| `p.Resim.RewindBeforeAdvance` | 1 | rewind 任务前置于 advance(变量 RewindBeforeAdvance) | PhysicsSolverBase.cpp:31-32 |

### 12.9.2 项目设置(ini/config)

- `UPhysicsSettings`(/Script/Engine.PhysicsSettings,DefaultEngine.ini `[SystemSettings]`/`[/Script/Engine.PhysicsSettings]`):`bTickPhysicsAsync`+`AsyncFixedTimeStepSize`(异步固定步长)、`bSubstepping`+`MaxSubstepDeltaTime`+`MaxSubsteps`(同步子步)、`MaxPhysicsDeltaTime`、`MinPhysicsDeltaTime`、`PhysicsPrediction`(bEnablePhysicsPrediction/重模拟误差阈值/MaxSupportedLatencyPrediction)(PhysicsSettings.h:193-345)。
- `UPhysicsSettingsCore`(PhysicsCore 模块,支持无 Engine 环境):`SolverOptions(FChaosSolverConfiguration)`、`bEnableEnhancedDeterminism`(ChaosScene.cpp:92-94 应用于 solver)。
- `EChaosSolverTickMode`(Fixed/Variable/VariableCapped/VariableCappedWithTarget,PhysicsCoreTypes.h:10)在 solver 配置对象上选择步长策略。

### 12.9.3 委托与事件

| 委托 | 时机 | 位置 |
|---|---|---|
| `FSolverPreAdvance/FSolverPreBuffer/FSolverPostAdvance/FSolverTeardown` | 每步前/缓冲前/全部完成后/销毁 | PhysicsSolverBase.h:30-33;注册 API :284-297(注意:线程不安全,见头文件注释) |
| `FSolverParticleUnregisteredGT` | GT 注销粒子 Proxy 时 | PBDRigidsSolver.h:44;注册 :152 |
| `FOnPhysScenePreTick/FOnPhysSceneStep/FOnPhysScenePostTick` | 场景 tick 各阶段 | PhysScene_Chaos.h:267-270;ChaosScene.h:144 |
| `FPhysicalMaterialManager::OnMaterialCreated/Updated/Destroyed`(及 Mask) | 材质管理器变化 | ChaosSolversModule.cpp:117-123 绑定 |
| UPrimitiveComponent 的 `OnComponentHit/OnComponentWake/Sleep/BreakingHits` 等 | GT 事件派发(12.7.3) | Engine/Classes/Components/PrimitiveComponent.h |

### 12.9.4 模块与插件扩展点

- **创建自定义 solver**:`FChaosSolversModule::CreateSolver(UObject* InOwner, Chaos::FReal InAsyncDt, Chaos::EThreadingMode ThreadingMode = Chaos::EThreadingMode::SingleThread, const FName& DebugName = NAME_None)`(ChaosSolversModule.h:191);`AChaosSolverActor` 即封装每 Actor 独立场景。
- **PT 逻辑扩展**:`CreateAndRegisterSimCallbackObject_External<TSimCallbackObject>(...)`(PhysicsSolverBase.h:412),选项位 `ESimCallbackOptions`(Presimulate/MidPhaseModification/CCDModification/ContactModification/StrainModification/ParticleRegister/ParticleUnregister/RunOnFrozenGameThread/Rewind/PhysicsObjectUnregister/PreIntegrate/PostIntegrate/PreSolve/PostSolve/InjectInputsExternal/ProcessInputsExternal/ProcessInputsInternal,Chaos/SimCallbackObject.h:32-50);车辆与 ChaosRigidPhysicsAsync 均以该机制接入。
- **求解器回调注入**:`FPBDRigidsEvolutionGBF::SetPreIntegrateCallback/SetPostIntegrateCallback/SetPreSolveCallback/SetPostSolveCallback/SetPostDetectCollisionsCallback`(PBDRigidsEvolutionGBF.h:88-111)。
- **碰撞修饰**:SimCallback 带 `ContactModification` 选项 → `FPBDRigidsSolver` 的 ContactModifiers 列表(PhysicsSolverBase.h:936),演化步中 `CollisionConstraints.ApplyCollisionModifier`(PBDRigidsEvolutionGBF.cpp:671-675/688-692)。
- **设置提供者**:`IChaosSettingsProvider`(ChaosSolversModule.h:29)由 Engine 通过 `SetSettingsProvider` 注入,供 NetworkPhysics 阈值查询(PhysicsSolverBase.h:813-879)。
- **Solver Actor 类提供者**:`IChaosSolverActorClassProvider`(:22)供插件替换默认 AChaosSolverActor。
- **查询扩展**:`FCollisionQueryFilterCallbackCore`(PhysicsCore)与 `ChaosInterface::FSceneQueryCommonParams`(SceneQueryCommonParams.h)自定义过滤;`DefaultPhysicsQueryHandler`/`IPhysicsQueryHandler`(Engine/Public/Physics/PhysicsQueryHandler.h:45)可替换查询实现。
- **CVD 调试**:`WITH_CHAOS_VISUAL_DEBUGGER` 编译开关 + `FChaosVDRuntimeModule`(ChaosVisualDebugger)记录 trace;编辑器 ChaosVD 插件回放。

## 12.10 已知限制/未确认项

1. **专用物理线程(DedicatedThread)未启用**:`EThreadingMode::DedicatedThread` 枚举与 `p.Chaos.DedicatedThreadEnabled`(默认 1)仍存在,但 5.8.3 源码中 `FPersistentPhysicsTask` 只有前向声明(PhysicsSolverBase.h:255 等),`FChaosSolversModule` 从不把 `bPersistentTaskSpawned` 置 true,`SyncTask` 实现被 `#if 0` 注释(ChaosSolversModule.cpp:164-177)。实际默认线程模式是 TaskGraph(`FChaosScene` 构造,ChaosScene.cpp:75)。
2. **PhysX 遗留头仍在但不可用**:Engine/Public/Physics 下的 `PhysScene_PhysX.h`、`PhysicsInterfacePhysX.h`、`PhysXIncludes` 等保留编译开关包裹的空壳;本章按 Chaos 路径描述,未逐一验证 PhysX 分支行为。
3. **ChaosVisualDebugger/ChaosVDData 细节**:仅确认模块边界(Recording/DataWrappers/Trace 目录)与 FChaosVDRecording 存在,未深入 trace 帧格式;附录 ChaosVDRuntime.md/ChaosVDData.md 可补充。
4. **Mover/ChaosMover**:仅梳理了模块结构与 `UChaosMoverSimulation : UMoverSimulation`(ChaosMoverSimulation.h:36)存在性;未验证其与 FPBDRigidsSolver 的完整交互(其主循环在 Mover 框架内)。
5. **RigidPhysics / ChaosRigidPhysicsAsync**:新抽象层(AnyGeometry/IJointConstraint 等)存在,未确认 5.8.3 中是否已有引擎路径默认走该层(更像未来迁移方向)。
6. **ChaosCloth 家族位置**:任务描述将其列在 Plugins/Experimental,实际位于 `Plugins/ChaosCloth` 与 `Plugins/ChaosClothAsset`(无 Experimental 前缀),模块清单已按实际路径标注。
7. **Engine/Public/Physics 71 头**:任务描述称 71 个头文件,实测 `ls | wc -l` 为 26(不含子目录 Experimental/ImmediatePhysics/Tests;含子目录总计约 71)——本章按"含子目录全量"口径覆盖。
8. **GJK/EPA 数值细节**:GJKIntersection 的双精度自动切换已确认(GJK.h:189-200);EPA 的 `EPAComputeVisibilityBorder` 等展开算法未逐行验证。
9. **FChaosScene::Flush/WaitPhysScenes 与 PIE 缓存逻辑**(PieModifiedObjects)未展开;与编辑器交互相关,超出本章主线。
10. **HeadlessChaos**:确认 `IMPLEMENT_APPLICATION(HeadlessChaos, "HeadlessChaos")`(HeadlessChaosApp.cpp:69)与测试文件布局;各测试用例语义未逐一阅读。

