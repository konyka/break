# 24(续)模块 → Build.cs 依赖 → 附录索引总表(24.13)

本文件列出第 24 章范围 348 个插件中全部 774 条 `Modules` 声明(774 个唯一模块名),按插件路径排序。"Public/Private 依赖"取自附录 `appendix/modules.json` 中该模块的 `deps`(该文件由工具从 `<Module>.Build.cs` 的 `PublicDependencyModuleNames`/`PrivateDependencyModuleNames` 静态抽取;每列至多列 8 项,超出以"等 N 个"表示);附录路径相对本文件所在 `design/` 目录。附录未收录的 35 个模块标注"(附录未收录)",其依赖未在此给出(原因见主文件 24.10)。


### 2D(5 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| Paper2D | Paper2D | R | PreDefault | Core, CoreUObject, Engine, NavigationSystem, RHI, RenderCore, Slate, SlateCore | EditorFramework, Renderer, UnrealEd | ../appendix/api/Plugins/Paper2D.md |
| Paper2D | Paper2DEditor | E | Default | Json | ApplicationCore, AssetTools, ContentBrowser, Core, CoreUObject, EditorFramework, EditorWidgets, Engine 等 24 个 | ../appendix/api/Plugins/Paper2DEditor.md |
| Paper2D | PaperSpriteSheetImporter | E | Default | — | AssetTools, ContentBrowser, Core, CoreUObject, Engine, Json, Paper2D, Paper2DEditor 等 12 个 | ../appendix/api/Plugins/PaperSpriteSheetImporter.md |
| Paper2D | PaperTiledImporter | E | Default | — | Core, CoreUObject, Engine, Json, Paper2D, Paper2DEditor, UnrealEd | ../appendix/api/Plugins/PaperTiledImporter.md |
| Paper2D | SmartSnapping | E | PostEngineInit | — | Core, CoreUObject, LevelEditor, Slate, SlateCore, ViewportSnapping | ../appendix/api/Plugins/SmartSnapping.md |

### AI(16 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| AISupport | AISupportModule | R | PostConfigInit | AIModule, Core, CoreUObject, Engine, NavigationSystem | — | ../appendix/api/Plugins/AISupportModule.md |
| EnvironmentQueryEditor | EnvironmentQueryEditor | U | PreDefault | — | AIGraph, AIModule, AssetDefinition, Core, CoreUObject, Engine, GraphEditor, InputCore 等 13 个 | ../appendix/api/Plugins/EnvironmentQueryEditor.md |
| HTNPlanner | HTNPlanner | R | PreDefault | AIModule, Core, CoreUObject, Engine, GameplayTags, GameplayTasks | EditorFramework, UnrealEd | ../appendix/api/Plugins/HTNPlanner.md |
| HTNPlanner | HTNTestSuite | U | PreDefault | AIModule, AITestSuite, Core, CoreUObject, Engine, HTNPlanner | EditorFramework, UnrealEd | ../appendix/api/Plugins/HTNTestSuite.md |
| MassAI | MassNavigation | R | Default | AIModule, Core, CoreUObject, DeveloperSettings, Engine, MassCommon, MassCore, MassEntity 等 13 个 | EditorFramework, UnrealEd | ../appendix/api/Plugins/MassNavigation.md |
| MassAI | MassNavMeshNavigation | R | Default | AIModule, Core, CoreUObject, Engine, MassCommon, MassCore, MassEntity, MassLOD 等 13 个 | — | ../appendix/api/Plugins/MassNavMeshNavigation.md |
| MassAI | MassZoneGraphNavigation | R | Default | AIModule, Core, CoreUObject, DeveloperSettings, Engine, MassCommon, MassCore, MassEntity 等 17 个 | EditorFramework, UnrealEd | ../appendix/api/Plugins/MassZoneGraphNavigation.md |
| MassAI | MassNavigationEditor | E | PostEngineInit | AssetTools, Core, CoreUObject, DetailCustomizations, EditorFramework, Engine, InputCore, MassCommon 等 18 个 | AppFramework, KismetWidgets, Projects, RenderCore, ToolMenus | ../appendix/api/Plugins/MassNavigationEditor.md |
| MassAI | MassAIBehavior | R | Default | Core, CoreUObject, DeveloperSettings, Engine, GameplayTags, MassActors, MassCommon, MassCore 等 26 个 | EditorFramework, PropertyBindingUtils, UnrealEd | ../appendix/api/Plugins/MassAIBehavior.md |
| MassAI | MassAIBehaviorEditor | E | Default | — | AIModule, AppFramework, Core, CoreUObject, Engine, InputCore, MassAIBehavior, MassCore 等 12 个 | ../appendix/api/Plugins/MassAIBehaviorEditor.md |
| MassAI | MassAIReplication | R | Default | AIModule, Core, CoreUObject, Engine, MassCommon, MassCore, MassEntity, MassLOD 等 15 个 | EditorFramework, UnrealEd | ../appendix/api/Plugins/MassAIReplication.md |
| MassAI | MassAIDebug | R | Default | Core, CoreUObject, Engine, InputCore, MassAIBehavior, MassAIReplication, MassActors, MassCommon 等 25 个 | UnrealEd | ../appendix/api/Plugins/MassAIDebug.md |
| MassAI | MassAITestSuite | U | Default | AIModule, AITestSuite, Core, CoreUObject, Engine, MassAIBehavior, MassAIReplication, MassActors 等 13 个 | UnrealEd | ../appendix/api/Plugins/MassAITestSuite.md |
| MassCrowd | MassCrowd | R | Default | AIModule, Core, CoreUObject, Engine, MassAIBehavior, MassAIReplication, MassActors, MassCommon 等 24 个 | — | ../appendix/api/Plugins/MassCrowd.md |
| MLAdapter | MLAdapter | R | PreDefault | AIModule, Core, CoreUObject, Engine, EnhancedInput, GameplayAbilities, GameplayTags, InputCore 等 11 个 | DeveloperSettings, EditorFramework, RPCLib, UnrealEd | ../appendix/api/Plugins/MLAdapter.md |
| MLAdapter | MLAdapterTestSuite | DT | PreDefault | AIModule, AITestSuite, Core, CoreUObject, Engine, JsonUtilities, MLAdapter | EditorFramework, RPCLib, UnrealEd | ../appendix/api/Plugins/MLAdapterTestSuite.md |

### AudioGameplay(2 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| AudioGameplay | AudioGameplay | R | Default | AudioExtensions, Core, GameplayTags | AudioMixerCore, CoreUObject, Engine | ../appendix/api/Plugins/AudioGameplay.md |
| AudioGameplay | AudioGameplayTests | E | Default | AudioExtensions, AudioGameplay, Core, GameplayTags | CoreUObject, Engine | ../appendix/api/Plugins/AudioGameplayTests.md |

### AudioGameplayVolume(2 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| AudioGameplayVolume | AudioGameplayVolume | R | Default | Core | AudioGameplay, CoreUObject, Engine | ../appendix/api/Plugins/AudioGameplayVolume.md |
| AudioGameplayVolume | AudioGameplayVolumeEditor | E | PostEngineInit | AudioGameplayVolume, Core, ToolMenus | AudioGameplay, CoreUObject, Engine, PropertyEditor, Slate, SlateCore, UnrealEd | ../appendix/api/Plugins/AudioGameplayVolumeEditor.md |

### AudioInsights(2 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| AudioInsights | AudioInsights | E+P | Default | Core, Engine, RewindDebuggerRuntimeInterface, ToolWidgets, TraceInsights, TraceServices | AudioMixerCore, AudioWidgetsCore, BuildSettings, CoreUObject, DeveloperSettings, InputCore, OutputLog, SessionServices 等 15 个 | ../appendix/api/Plugins/AudioInsights.md |
| AudioInsights | AudioInsightsEditor | EnC | Default | AudioMixerCore, Core | AudioInsights, AudioMixer, AudioWidgets, AudioWidgetsCore, CoreUObject, DeveloperSettings, Engine, InputCore 等 17 个 | ../appendix/api/Plugins/AudioInsightsEditor.md |

### AudioInsightsRuntime(1 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| AudioInsightsRuntime | AudioInsightsRuntime | R | Default | Core | AudioMixerCore, CoreUObject, Engine, SlateCore | ../appendix/api/Plugins/AudioInsightsRuntime.md |

### AudioModulationInsights(1 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| AudioModulationInsights | AudioModulationInsights | E+P | Default | Core | AudioInsights, AudioInsightsEditor, AudioMixerCore, CoreUObject, Engine, InputCore, Projects, Slate 等 10 个 | ../appendix/api/Plugins/AudioModulationInsights.md |

### AutomationControllerRpc(1 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| AutomationControllerRpc | AutomationControllerRpc | R | PostEngineInit | — | AutomationController, Core, CoreUObject, ExternalRpcRegistry, HTTP, HTTPServer, Json, SessionServices | ../appendix/api/Plugins/AutomationControllerRpc.md |

### BlueprintFileUtils(1 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| BlueprintFileUtils | BlueprintFileUtils | R | Default | Core | CoreUObject, Engine, Slate, SlateCore | ../appendix/api/Plugins/BlueprintFileUtils.md |

### Bridge(2 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| Bridge | Bridge | E | PostDefault | ApplicationCore, ContentBrowserData, Core, CoreUObject, Engine, InputCore, Json, MegascansPlugin 等 21 个 | — | ../appendix/api/Plugins/Bridge.md |
| Bridge | MegascansPlugin | E | PostDefault | — | ApplicationCore, AssetRegistry, ContentBrowser, Core, CoreUObject, EditorScriptingUtilities, EditorStyle, Engine 等 26 个 | ../appendix/api/Plugins/MegascansPlugin.md |

### Cameras(5 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| CameraShakePreviewer | CameraShakePreviewer | E | PostEngineInit | Core, CoreUObject, Engine, InputCore | AppFramework, ApplicationCore, EditorFramework, GameplayCameras, LevelEditor, MovieScene, MovieSceneTracks, PropertyEditor 等 12 个 | ../appendix/api/Plugins/CameraShakePreviewer.md |
| EngineCameras | EngineCameras | R | PreDefault | CinematicCamera, Core, CoreUObject, Engine, HeadMountedDisplay, MovieScene, MovieSceneTracks, TemplateSequence 等 9 个 | — | ../appendix/api/Plugins/EngineCameras.md |
| GameplayCameras | GameplayCameras | R | PreDefault | CinematicCamera, Core, CoreUObject, DeveloperSettings, Engine, EnhancedInput, GameplayTags, HeadMountedDisplay 等 14 个 | UnrealEd | ../appendix/api/Plugins/GameplayCameras.md |
| GameplayCameras | GameplayCamerasUncookedOnly | U | Default | GameplayCameras | BlueprintGraph, Core, CoreUObject, Engine, Kismet, KismetCompiler, SlateCore, UnrealEd | ../appendix/api/Plugins/GameplayCamerasUncookedOnly.md |
| GameplayCameras | GameplayCamerasEditor | E | PostEngineInit | — | ApplicationCore, AssetDefinition, AssetRegistry, AssetTools, BlueprintGraph, CinematicCamera, ContentBrowser, Core 等 42 个 | ../appendix/api/Plugins/GameplayCamerasEditor.md |

### ChaosCloth(2 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| ChaosCloth | ChaosCloth | R | PostConfigInit | Buoyancy, Chaos, ChaosCaching, ClothingSystemRuntimeCommon, ClothingSystemRuntimeInterface, Core, CoreUObject, Engine 等 9 个 | — | ../appendix/api/Plugins/ChaosCloth.md |
| ChaosCloth | ChaosClothEditor | E | Default | — | ChaosCloth, ClothingSystemEditorInterface, Core, CoreUObject, DetailCustomizations, EditorFramework, Engine, InputCore 等 12 个 | ../appendix/api/Plugins/ChaosClothEditor.md |

### ChaosClothAsset(3 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| ChaosClothAsset | ChaosClothAsset | R | Default | — | ClothingSystemRuntimeCommon, Core, CoreUObject, GeometryCore, MeshConversion, RenderCore | ../appendix/api/Plugins/ChaosClothAsset.md |
| ChaosClothAsset | ChaosClothAssetEngine | R | Default | ClothingSystemRuntimeCommon, DataflowCore, DataflowEngine, DataflowSimulation | ChaosCaching, ChaosCloth, ChaosClothAsset, Cloth Sim, ClothingSystemRuntimeInterface, Core, CoreUObject, Engine 等 13 个 | ../appendix/api/Plugins/ChaosClothAssetEngine.md |
| ChaosClothAsset | ChaosClothAssetTools | E | Default | MeshConversion | Chaos, ChaosCloth, ChaosClothAsset, ChaosClothAssetEngine, ChaosClothEditor, ClothPainter, ClothingSystemEditorInterface, ClothingSystemRuntimeCommon 等 25 个 | ../appendix/api/Plugins/ChaosClothAssetTools.md |

### ChaosClothAssetDataflowNodes(1 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| ChaosClothAssetDataflowNodes | ChaosClothAssetDataflowNodes | E | Default | Core, MeshResizingCore | AnimationCore, AssetTools, ChaosCaching, ChaosCloth, ChaosClothAsset, ChaosClothAssetEngine, ChaosClothAssetTools, ClothingSystemRuntimeCommon 等 32 个 | ../appendix/api/Plugins/ChaosClothAssetDataflowNodes.md |

### ChaosClothAssetEditorCore(2 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| ChaosClothAssetEditorCore | ChaosClothAssetEditor | E | Default | — | AdvancedPreviewScene, AnimGraph, ApplicationCore, AssetDefinition, BaseCharacterFXEditor, Chaos, ChaosCloth, ChaosClothAsset 等 54 个 | ../appendix/api/Plugins/ChaosClothAssetEditor.md |
| ChaosClothAssetEditorCore | ChaosClothAssetEditorTools | E | Default | Core, InputCore, InteractiveToolsFramework, UnrealEd | AdvancedPreviewScene, Chaos, ChaosCloth, ChaosClothAsset, ChaosClothAssetDataflowNodes, ChaosClothAssetEngine, ChaosClothAssetTools, ClothingSystemEditor 等 40 个 | ../appendix/api/Plugins/ChaosClothAssetEditorTools.md |

### ChaosClothAssetUsdDataflowNodes(1 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| ChaosClothAssetUsdDataflowNodes | ChaosClothAssetUsdDataflowNodes | E | Default | — | AssetTools, Chaos, ChaosClothAsset, ChaosClothAssetDataflowNodes, ChaosClothAssetEngine, ChaosClothAssetTools, Core, CoreUObject 等 23 个 | ../appendix/api/Plugins/ChaosClothAssetUsdDataflowNodes.md |

### ChaosInsights(2 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| ChaosInsights | ChaosInsightsAnalysis | E+P | Default | Core | CoreUObject, TraceAnalysis, TraceLog, TraceServices | ../appendix/api/Plugins/ChaosInsightsAnalysis.md |
| ChaosInsights | ChaosInsightsUI | E+P | Default | — | ChaosInsightsAnalysis, Core, CoreUObject, InputCore, Slate, SlateCore, TraceInsights, TraceInsightsCore 等 9 个 | ../appendix/api/Plugins/ChaosInsightsUI.md |

### ChaosOutfitAsset(3 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| ChaosOutfitAsset | ChaosOutfitAssetDataflowNodes | R | Default | — | AssetRegistry, Chaos, ChaosClothAsset, ChaosClothAssetEngine, ChaosOutfitAssetEngine, Core, CoreUObject, DataflowCore 等 10 个 | ../appendix/api/Plugins/ChaosOutfitAssetDataflowNodes.md |
| ChaosOutfitAsset | ChaosOutfitAssetEngine | R | Default | ChaosClothAssetEngine | Chaos, ChaosClothAsset, Core, CoreUObject, DataflowEngine, Engine, MeshResizingCore, RHI 等 9 个 | ../appendix/api/Plugins/ChaosOutfitAssetEngine.md |
| ChaosOutfitAsset | ChaosOutfitAssetEditor | E | Default | — | AssetDefinition, BaseCharacterFXEditor, ChaosClothAsset, ChaosClothAssetEngine, ChaosClothAssetTools, ChaosOutfitAssetEngine, ContentBrowser, Core 等 23 个 | ../appendix/api/Plugins/ChaosOutfitAssetEditor.md |

### ChaosVD(3 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| ChaosVD | ChaosVD | E+P | Default | Core | ApplicationCore, ChaosSolverEngine, ChaosVDData, ChaosVDRuntime, CommonMenuExtensions, CoreUObject, DesktopPlatform, DynamicMesh 等 40 个 | ../appendix/api/Plugins/ChaosVD.md |
| ChaosVD | ChaosVDBlueprint | R+P | Default | Chaos, Core, CoreUObject, Engine | — | ../appendix/api/Plugins/ChaosVDBlueprint.md |
| ChaosVD | ChaosVDBuiltInExtensions | E+P | Default | ChaosVD | AppFramework, ChaosVDData, ChaosVDRuntime, Core, CoreUObject, EditorWidgets, Engine, InputCore 等 14 个 | ../appendix/api/Plugins/ChaosVDBuiltInExtensions.md |

### Chooser(6 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| Chooser | Chooser | R | Default | — | AnimGraphRuntime, AnimationCore, BlendStack, Core, CoreUObject, Engine, GameplayTags, RewindDebuggerRuntimeInterface 等 9 个 | ../appendix/api/Plugins/Chooser.md |
| Chooser | ChooserUncooked | U | PreDefault | Chooser | AnimGraph, AnimGraphRuntime, AssetDefinition, AssetTools, BlendStack, BlendStackEditor, BlueprintGraph, Core 等 13 个 | ../appendix/api/Plugins/ChooserUncooked.md |
| Chooser | ChooserEditor | E | Default | Chooser | ApplicationCore, AssetDefinition, AssetTools, BlendStack, BlueprintGraph, Core, CoreUObject, DeveloperSettings 等 29 个 | ../appendix/api/Plugins/ChooserEditor.md |
| Chooser | ProxyTable | R | Default | Chooser | Core, CoreUObject, Engine | ../appendix/api/Plugins/ProxyTable.md |
| Chooser | ProxyTableUncooked | U | Default | ProxyTable | AssetDefinition, AssetTools, BlueprintGraph, Chooser, Core, CoreUObject, Engine, GameplayTags 等 10 个 | ../appendix/api/Plugins/ProxyTableUncooked.md |
| Chooser | ProxyTableEditor | E | Default | — | AssetDefinition, AssetTools, BlendStack, BlueprintGraph, Chooser, ChooserEditor, Core, CoreUObject 等 23 个 | ../appendix/api/Plugins/ProxyTableEditor.md |

### CmdLinkServer(1 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| CmdLinkServer | CmdLinkServer | E | PostDefault | Core | CoreUObject, Engine, UnrealEd | ../appendix/api/Plugins/CmdLinkServer.md |

### Compositing(11 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| Composite | Composite | R | PostConfigInit | CompositeCore, Core, CoreUObject, Engine, GameplayTags, MediaAssets, OpenColorIO | CQTest, CameraCalibrationCore, ConcertSyncCore, GeometryCore, LevelEditor, LevelSequence, MediaFrameworkUtilities, MediaProfile 等 20 个 | ../appendix/api/Plugins/Composite.md |
| Composite | CompositeEditor | E | Default | Composite, Core | AppFramework, ApplicationCore, ColorGradingEditor, CompositeCore, ConcertSyncClient, ContentBrowserData, CoreUObject, DetailCustomizations 等 31 个 | ../appendix/api/Plugins/CompositeEditor.md |
| CompositeCore | CompositeCore | R | PostConfigInit | Core, CoreUObject, DeveloperSettings, Engine | Projects, RHI, RenderCore, Renderer, SettingsEditor, Slate, SlateCore, SourceControl 等 9 个 | ../appendix/api/Plugins/CompositeCore.md |
| Composure | Composure | R | Default | CameraCalibrationCore, CinematicCamera, Core, CoreUObject, Engine, LensComponent, MediaIOCore, MovieScene 等 11 个 | ActorLayerUtilities, EditorFramework, ImageWriteQueue, MediaAssets, MediaFrameworkUtilities, MovieSceneCapture, RHI, Slate 等 10 个 | ../appendix/api/Plugins/Composure.md |
| Composure | ComposureEditor | E | Default | Core, CoreUObject, Engine, InputCore | Composure, DesktopWidgets, EditorFramework, EditorWidgets, Layers, MovieScene, MovieSceneTools, MovieSceneTracks 等 13 个 | ../appendix/api/Plugins/ComposureEditor.md |
| Composure | ComposureLayersEditor | E | PostEngineInit | — | AppFramework, BlueprintMaterialTextureNodes, ClassViewer, Composure, ContentBrowser, Core, CoreUObject, DetailCustomizations 等 20 个 | ../appendix/api/Plugins/ComposureLayersEditor.md |
| LensDistortion | LensDistortion | R | PostConfigInit | Core, CoreUObject, Engine, RHI, RenderCore | Projects | ../appendix/api/Plugins/LensDistortion.md |
| OpenColorIO | OpenColorIO | R | PostConfigInit | Core, CoreUObject, DeveloperSettings, Engine, OpenColorIOWrapper | DerivedDataCache, EditorFramework, ImageCore, Projects, RHI, RenderCore, Renderer, Slate 等 11 个 | ../appendix/api/Plugins/OpenColorIO.md |
| OpenColorIO | OpenColorIOEditor | E | PreDefault | — | AssetDefinition, Core, CoreUObject, DesktopWidgets, EditorFramework, Engine, ImageCore, InputCore 等 21 个 | ../appendix/api/Plugins/OpenColorIOEditor.md |
| OpenCVLensDistortion | OpenCVLensCalibration | R | PostConfigInit | — | Core, CoreUObject, Engine, OpenCV, OpenCVHelper, OpenCVLensDistortion | ../appendix/api/Plugins/OpenCVLensCalibration.md |
| OpenCVLensDistortion | OpenCVLensDistortion | R | PostConfigInit | OpenCV, OpenCVHelper | Core, CoreUObject, Engine, Projects, RHI, RenderCore | ../appendix/api/Plugins/OpenCVLensDistortion.md |

### Compression(1 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| OodleNetwork | OodleNetworkHandlerComponent | R | Default | Analytics, Core, CoreUObject, Engine, NetCore, PacketHandler | — | ../appendix/api/Plugins/OodleNetworkHandlerComponent.md |

### Dataflow(3 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| Dataflow | DataflowEditor | E | PostDefault | AdvancedPreviewScene, AnimGraph, AppFramework, ApplicationCore, AssetDefinition, AssetRegistry, AssetTools, BaseCharacterFXEditor 等 72 个 | ContentBrowser, SkeletalMeshModelingTools, TedsOutliner | ../appendix/api/Plugins/DataflowEditor.md |
| Dataflow | DataflowEnginePlugin | R | Default | Core, CoreUObject, GeometryFramework | Chaos, DataflowCore, DataflowEngine, DynamicMesh, Engine, GeometryCore, RHI, RenderCore | ../appendix/api/Plugins/DataflowEnginePlugin.md |
| Dataflow | DataflowNodes | R | Default | Chaos, ChaosCore, Core, CoreUObject, DataflowCore, DataflowEngine, DataflowEnginePlugin, Engine 等 12 个 | DynamicMesh, GeometryFramework, ImageCore, InputCore, ModelingComponents, PropertyEditor, SkeletalMeshUtilitiesCommon, Slate 等 10 个 | ../appendix/api/Plugins/DataflowNodes.md |

### DataflowVolumetricPlugin(2 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| DataflowVolumetricPlugin | DataflowVolumeCore | E | Default | — | Chaos, ChaosCore, Core, CoreUObject, DataflowCore, DataflowEditor, DataflowEngine, DataflowEnginePlugin 等 18 个 | ../appendix/api/Plugins/DataflowVolumeCore.md |
| DataflowVolumetricPlugin | DataflowVolumeNodes | E | Default | — | Chaos, ChaosCore, Core, CoreUObject, DataflowCore, DataflowEditor, DataflowEngine, DataflowEnginePlugin 等 19 个 | ../appendix/api/Plugins/DataflowVolumeNodes.md |

### DerivedDataBuildController(1 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| DerivedDataBuildController | DerivedDataBuildController | E | EarliestPossible | — | — | (附录未收录) |

### DiscoveryBeaconReceiver(1 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| DiscoveryBeaconReceiver | DiscoveryBeaconReceiver | R | Default | Core, CoreUObject, Serialization | Engine, Networking, Sockets | ../appendix/api/Plugins/DiscoveryBeaconReceiver.md |

### EnhancedInput(3 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| EnhancedInput | EnhancedInput | R | PreDefault | — | ApplicationCore, Core, CoreUObject, DeveloperSettings, Engine, GameplayTags, InputCore, Slate 等 9 个 | ../appendix/api/Plugins/EnhancedInput.md |
| EnhancedInput | InputBlueprintNodes | U | PreDefault | InputEditor | BlueprintGraph, Core, CoreUObject, DataValidation, Engine, EnhancedInput, GraphEditor, InputCore 等 15 个 | ../appendix/api/Plugins/InputBlueprintNodes.md |
| EnhancedInput | InputEditor | E | Default | EnhancedInput | ApplicationCore, AssetDefinition, AssetTools, BlueprintGraph, ContentBrowser, Core, CoreUObject, DetailCustomizations 等 22 个 | ../appendix/api/Plugins/InputEditor.md |

### Fab(1 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| Fab | Fab | E | PostDefault | Core | ApplicationCore, AssetTools, BuildPatchServices, ContentBrowser, CoreUObject, DesktopWidgets, DeveloperSettings, EOSSDK 等 39 个 | ../appendix/api/Plugins/Fab.md |

### FastBuildController(1 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| FastBuildController | FastBuildController | U | EarliestPossible | — | — | (附录未收录) |

### GameInputWindows(1 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| GameInputWindows | GameInputWindows | RnC | Default | — | ApplicationCore, Core, CoreUObject, DeveloperSettings, Engine, GameInputBase, InputCore, InputDevice | ../appendix/api/Plugins/GameInputWindows.md |

### Interchange(21 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| InterchangeAssets | InterchangeAssets | R | PostConfigInit | — | — | (附录未收录) |
| InterchangeEditor | InterchangeEditor | E | Default | Core, CoreUObject, Engine, UnrealEd | AssetDefinition, AssetTools, ContentBrowser, EditorSubsystem, InputCore, InterchangeCommonParser, InterchangeCore, InterchangeEngine 等 18 个 | ../appendix/api/Plugins/InterchangeEditor.md |
| InterchangeEditor | InterchangeEditorPipelines | E | Default | Core, CoreUObject, Engine, InterchangeCore, InterchangeEngine | AssetDefinition, AssetTools, EngineAssetDefinitions, InputCore, InterchangeNodes, InterchangePipelines, MainFrame, Projects 等 13 个 | ../appendix/api/Plugins/InterchangeEditorPipelines.md |
| InterchangeEditor | InterchangeEditorUtilities | E | Default | Core, CoreUObject, Engine, InterchangeCore, InterchangeEngine | DesktopPlatform, Slate, SlateCore, UnrealEd | ../appendix/api/Plugins/InterchangeEditorUtilities.md |
| InterchangeChaosClothAsset | InterchangeChaosClothAssetImport | E | Default | Core, CoreUObject, Engine | Chaos, ChaosClothAsset, ChaosClothAssetDataflowNodes, ChaosClothAssetEngine, DataflowEngine, InterchangeAnalytics, InterchangeCore, InterchangeEngine 等 13 个 | ../appendix/api/Plugins/InterchangeChaosClothAssetImport.md |
| InterchangeOpenUSD | InterchangeOpenUSDImport | R | Default | Core, CoreUObject, Engine, InterchangeCommon, InterchangeCommonParser, InterchangeCore, InterchangeImport, USDUtilities 等 9 个 | DynamicMesh, GeometryCore, HairStrandsCore, InterchangeEngine, InterchangeFactoryNodes, InterchangeNodes, InterchangeOpenVDBImport, InterchangePipelines 等 15 个 | ../appendix/api/Plugins/InterchangeOpenUSDImport.md |
| InterchangeOpenUSD | InterchangeOpenUSDEditor | E | Default | Core, CoreUObject, Engine | InputCore, InterchangeEditor, InterchangeEngine, InterchangeOpenUSDImport, Slate, SlateCore, USDClasses, UnrealEd 等 9 个 | ../appendix/api/Plugins/InterchangeOpenUSDEditor.md |
| InterchangeOpenUSDChaosClothAsset | InterchangeOpenUSDChaosClothAssetImport | E | Default | Core, CoreUObject, Engine | Chaos, ChaosClothAsset, ChaosClothAssetDataflowNodes, ChaosClothAssetEngine, InterchangeChaosClothAssetImport, InterchangeCore, InterchangeEngine, InterchangeFactoryNodes 等 16 个 | ../appendix/api/Plugins/InterchangeOpenUSDChaosClothAssetImport.md |
| InterchangeOpenVDB | InterchangeOpenVDBImport | E | Default | Core, CoreUObject, Engine | InterchangeCore, InterchangeEngine, InterchangeImport, InterchangeNodes, SparseVolumeTexture | ../appendix/api/Plugins/InterchangeOpenVDBImport.md |
| Interchange | GLTFCore | R | Default | — | — | ../appendix/api/Plugins/GLTFCore.md |
| Interchange | InterchangeNodes | R | PreDefault | Core, CoreUObject, InterchangeCore | — | ../appendix/api/Plugins/InterchangeNodes.md |
| Interchange | InterchangeFactoryNodes | R | PreDefault | CinematicCamera, Core, CoreUObject, Engine, InterchangeCommon, InterchangeCore, InterchangeEngine, InterchangeNodes 等 10 个 | GeometryCache, HairStrandsCore, LevelSequence | ../appendix/api/Plugins/InterchangeFactoryNodes.md |
| Interchange | InterchangeImport | R | PreDefault | ClothingSystemRuntimeCommon, Core, CoreUObject, Engine, HairStrandsCore, InterchangeCommon, InterchangeCore, InterchangeDispatcher 等 18 个 | AssetRegistry, AudioMixer, BSPUtils, CinematicCamera, ClothingSystemRuntimeCommon, GLTFCore, GeometryCache, HairStrandsEditor 等 23 个 | ../appendix/api/Plugins/InterchangeImport.md |
| Interchange | InterchangeMessages | R | Default | Core, CoreUObject, Engine, InterchangeCore | — | ../appendix/api/Plugins/InterchangeMessages.md |
| Interchange | InterchangeExport | R | Default | Core, CoreUObject, Engine, InterchangeCore, InterchangeEngine | — | ../appendix/api/Plugins/InterchangeExport.md |
| Interchange | InterchangePipelines | R | PreDefault | Core, CoreUObject, Engine, InterchangeCommon, InterchangeCore, InterchangeEngine, InterchangeFactoryNodes, InterchangeNodes | ApplicationCore, CinematicCamera, DeveloperSettings, Foliage, GLTFCore, GeometryCache, HairStrandsCore, ImageCore 等 18 个 | ../appendix/api/Plugins/InterchangePipelines.md |
| Interchange | InterchangeDispatcher | R | Default | Core, Sockets | Json | ../appendix/api/Plugins/InterchangeDispatcher.md |
| Interchange | InterchangeCommon | R | Default | Core, CoreUObject | — | ../appendix/api/Plugins/InterchangeCommon.md |
| Interchange | InterchangeAnalytics | R | Default | Core, CoreUObject, Engine, InterchangeCommon, InterchangeCore, InterchangeEngine, InterchangeFactoryNodes, InterchangeNodes | GeometryCache, HairStrandsCore, LevelSequence | ../appendix/api/Plugins/InterchangeAnalytics.md |
| Interchange | InterchangeCommonParser | R | Default | Core, CoreUObject, InterchangeCore, InterchangeNodes | Engine, Json | ../appendix/api/Plugins/InterchangeCommonParser.md |
| Interchange | InterchangeFbxParser | R | Default | Core, CoreUObject, InterchangeCore | DeveloperSettings, Engine, ImageCore, ImageWrapper, InterchangeCommonParser, InterchangeEngine, InterchangeMessages, InterchangeNodes 等 12 个 | ../appendix/api/Plugins/InterchangeFbxParser.md |

### IoStoreInsights(1 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| IoStoreInsights | IoStoreInsights | E+P | Default | — | Core, InputCore, Slate, SlateCore, TraceAnalysis, TraceInsights, TraceInsightsCore, TraceServices | ../appendix/api/Plugins/IoStoreInsights.md |

### JsonBlueprintUtilities(2 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| JsonBlueprintUtilities | JsonBlueprintUtilities | R | Default | Core, CoreUObject, Engine | Json, JsonUtilities | ../appendix/api/Plugins/JsonBlueprintUtilities.md |
| JsonBlueprintUtilities | JsonBlueprintGraph | U | Default | — | ApplicationCore, AssetRegistry, AssetTools, BlueprintGraph, Core, CoreUObject, Engine, GraphEditor 等 19 个 | ../appendix/api/Plugins/JsonBlueprintGraph.md |

### LightWeightInstancesEditor(1 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| LightWeightInstancesEditor | LightWeightInstancesEditor | R | Default | Core | CoreUObject, DataLayerEditor, Engine, Slate, SlateCore | ../appendix/api/Plugins/LightWeightInstancesEditor.md |

### MassInsights(2 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| MassInsights | MassInsightsAnalysis | E+P | Default | Core | CoreUObject, MassDeveloper, TraceAnalysis, TraceLog, TraceServices | ../appendix/api/Plugins/MassInsightsAnalysis.md |
| MassInsights | MassInsightsUI | E+P | Default | — | Core, CoreUObject, InputCore, MassDeveloper, MassInsightsAnalysis, Slate, SlateCore, TraceInsights 等 10 个 | ../appendix/api/Plugins/MassInsightsUI.md |

### MemoryUsageQueries(1 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| MemoryUsageQueries | MemoryUsageQueries | R | EarliestPossible | Core, CoreUObject | AssetRegistry, Engine, EngineSettings, PakFile | ../appendix/api/Plugins/MemoryUsageQueries.md |

### MeshPainting(2 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| MeshPainting | MeshPaintEditorMode | E | Default | EditorSubsystem, Slate, SlateCore | Core, CoreUObject, DesktopPlatform, DynamicMesh, EditorFramework, EditorInteractiveToolsFramework, EditorWidgets, Engine 等 24 个 | ../appendix/api/Plugins/MeshPaintEditorMode.md |
| MeshPainting | MeshPaintingToolset | E | Default | EditorInteractiveToolsFramework, GeometryCore, InteractiveToolsFramework | Chaos, Core, CoreUObject, Engine, GeometryCollectionEngine, ImageCore, InterchangeEngine, InterchangePipelines 等 15 个 | ../appendix/api/Plugins/MeshPaintingToolset.md |

### Messaging(4 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| MessagingDebugger | MessagingDebugger | U | Default | — | Core, CoreUObject, InputCore, PropertyEditor, Serialization, Slate, SlateCore, WorkspaceMenuStructure | ../appendix/api/Plugins/MessagingDebugger.md |
| MessagingInsights | UdpMessagingInsights | E+P | Default | — | ApplicationCore, Core, CoreUObject, Engine, Messaging, Networking, Slate, SlateCore 等 14 个 | ../appendix/api/Plugins/UdpMessagingInsights.md |
| TcpMessaging | TcpMessaging | R | PreDefault | Core | CoreUObject, Networking, Serialization, Sockets | ../appendix/api/Plugins/TcpMessaging.md |
| UdpMessaging | UdpMessaging | R+P | PreDefault | AtomicQueue, Core, Networking | ApplicationCore, Cbor, CoreUObject, EditorStyle, Engine, InputCore, Json, Messaging 等 16 个 | ../appendix/api/Plugins/UdpMessaging.md |

### MovieScene(23 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| ActorSequence | ActorSequence | R | PreDefault | Core, CoreUObject, Engine, MovieScene, MovieSceneTracks, TimeManagement | — | ../appendix/api/Plugins/ActorSequence.md |
| ActorSequence | ActorSequenceEditor | E | PostEngineInit | — | ActorSequence, BlueprintGraph, ClassViewer, Core, CoreUObject, EditorFramework, Engine, InputCore 等 19 个 | ../appendix/api/Plugins/ActorSequenceEditor.md |
| CinematicPrestreaming | CinematicPrestreaming | R | Default | Core, MovieScene | CoreUObject, Engine, RHI, RenderCore | ../appendix/api/Plugins/CinematicPrestreaming.md |
| CinematicPrestreaming | CinematicPrestreamingEditor | U | Default | CinematicPrestreaming, Core, EditorSubsystem, LevelSequence, MovieRenderPipelineCore, MovieRenderPipelineEditor, MovieRenderPipelineRenderPasses, MovieScene 等 11 个 | CoreUObject, Engine, RenderCore, Slate, SlateCore | ../appendix/api/Plugins/CinematicPrestreamingEditor.md |
| CustomizableSequencerTracks | CustomizableSequencerTracks | R | Default | Core, CoreUObject, MovieScene, SlateCore | — | ../appendix/api/Plugins/CustomizableSequencerTracks.md |
| CustomizableSequencerTracks | CustomizableSequencerTracksEditor | E | PostEngineInit | — | AssetRegistry, Core, CoreUObject, CustomizableSequencerTracks, EditorFramework, MovieScene, Sequencer, SequencerCore 等 11 个 | ../appendix/api/Plugins/CustomizableSequencerTracksEditor.md |
| LevelSequenceEditor | LevelSequenceEditor | E | PostEngineInit | SequencerScripting, SequencerScriptingEditor | AppFramework, ApplicationCore, AssetDefinition, BlueprintGraph, CinematicCamera, ClassViewer, Constraints, ContentBrowser 等 35 个 | ../appendix/api/Plugins/LevelSequenceEditor.md |
| MoviePipelineMaskRenderPass | MoviePipelineMaskRenderPass | U | Default | ActorLayerUtilities, MovieRenderPipelineCore, MovieRenderPipelineRenderPasses, OpenColorIO, RHI, RenderCore, SlateCore, UnrealEd | Core, CoreUObject, Engine, ImageCore, Json, MovieScene | ../appendix/api/Plugins/MoviePipelineMaskRenderPass.md |
| MovieRenderPipeline | MovieRenderPipelineCore | R | Default | CinematicCamera, Engine, ImageWriteQueue, LevelSequence, MovieScene, MovieSceneTools, MovieSceneTracks, NamingTokens 等 10 个 | AudioMixer, ChaosClothAssetEngine, ClassViewer, ClothingSystemRuntimeInterface, ContentBrowserData, Core, CoreUObject, DataLayerEditor 等 28 个 | ../appendix/api/Plugins/MovieRenderPipelineCore.md |
| MovieRenderPipeline | MovieRenderPipelineSettings | R | Default | ConsoleVariablesEditor, Engine, LevelSequence, MovieRenderPipelineCore, MovieScene, MovieSceneTracks, OpenColorIO, SlateCore | ApplicationCore, AudioMixer, Core, CoreUObject, NonRealtimeAudioRenderer, RHI, RenderCore, Slate 等 9 个 | ../appendix/api/Plugins/MovieRenderPipelineSettings.md |
| MovieRenderPipeline | MovieRenderPipelineRenderPasses | R | Default | ActorLayerUtilities, MovieRenderPipelineCore, OpenColorIO, RHI, RenderCore, Renderer | AudioMixer, CinematicCamera, Core, CoreUObject, Engine, ImageCore, ImageWrapper, ImageWriteQueue 等 17 个 | ../appendix/api/Plugins/MovieRenderPipelineRenderPasses.md |
| MovieRenderPipeline | MovieRenderPipelineEditor | E | Default | ContentBrowser, Core, EditorSubsystem, EditorWidgets, FunctionalTesting, MovieRenderPipelineCore, MovieRenderPipelineRenderPasses, MovieRenderPipelineSettings 等 14 个 | ApplicationCore, AssetDefinition, AutomationMessages, BlueprintGraph, CinematicCamera, ConsoleVariablesEditor, CoreUObject, DeveloperSettings 等 37 个 | ../appendix/api/Plugins/MovieRenderPipelineEditor.md |
| MovieRenderPipeline | MovieRenderPipelineMP4Encoder | R | Default | MovieRenderPipelineCore, MovieRenderPipelineSettings, OpenColorIO, SlateCore | Core, CoreUObject, Engine | ../appendix/api/Plugins/MovieRenderPipelineMP4Encoder.md |
| MovieRenderPipeline | UEOpenExrRTTI | R | Default | Imath, UEOpenExr | Core | ../appendix/api/Plugins/UEOpenExrRTTI.md |
| MovieSceneTextTrack | MovieSceneTextTrack | R | Default | Core, CoreUObject, Engine, MovieScene, MovieSceneTracks | — | ../appendix/api/Plugins/MovieSceneTextTrack.md |
| MovieSceneTextTrack | MovieSceneTextTrackEditor | E | Default | — | — | (附录未收录) |
| ReplayTracks | ReplayTracks | R | Default | Core, CoreUObject, Engine, MovieScene, MovieSceneTracks, TimeManagement | — | ../appendix/api/Plugins/ReplayTracks.md |
| ReplayTracks | ReplayTracksEditor | E | PostEngineInit | — | Core, CoreUObject, Engine, InputCore, MovieScene, MovieSceneTools, MovieSceneTracks, ReplayTracks 等 13 个 | ../appendix/api/Plugins/ReplayTracksEditor.md |
| SequencerScripting | SequencerScripting | R | Default | Core, MovieScene, MovieSceneTracks, TimeManagement | CoreUObject, Engine, LevelSequence, Slate, SlateCore, UniversalObjectLocator | ../appendix/api/Plugins/SequencerScripting.md |
| SequencerScripting | SequencerScriptingEditor | E | Default | CinematicCamera, Core, MovieScene, MovieSceneCaptureDialog, MovieSceneTools, MovieSceneTracks, SequencerScripting, TimeManagement | BlueprintGraph, CoreUObject, CurveEditor, EditorFramework, Engine, Kismet, LevelSequence, MovieSceneCapture 等 14 个 | ../appendix/api/Plugins/SequencerScriptingEditor.md |
| SequenceValidator | SequenceValidator | E | PostEngineInit | — | ApplicationCore, AssetRegistry, ContentBrowser, Core, CoreUObject, Engine, InputCore, LevelSequence 等 20 个 | ../appendix/api/Plugins/SequenceValidator.md |
| TemplateSequence | TemplateSequence | R | Default | CinematicCamera, Core, CoreUObject, Engine, LevelSequence, MovieScene, MovieSceneTracks, TimeManagement | — | ../appendix/api/Plugins/TemplateSequence.md |
| TemplateSequence | TemplateSequenceEditor | E | PostEngineInit | — | AssetDefinition, BlueprintGraph, CinematicCamera, Core, CoreUObject, EditorFramework, Engine, InputCore 等 21 个 | ../appendix/api/Plugins/TemplateSequenceEditor.md |

### NetcodeUnitTest(2 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| NetcodeUnitTest | NetcodeUnitTest | U | Default | Core, CoreUObject, Engine, Sockets | ApplicationCore, EngineSettings, InputCore, NetCore, PacketHandler, RenderCore, Slate, SlateCore 等 9 个 | ../appendix/api/Plugins/NetcodeUnitTest.md |
| NUTUnrealEngine | NUTUnrealEngine | U | Default | Core, CoreUObject, Engine, NetcodeUnitTest | — | ../appendix/api/Plugins/NUTUnrealEngine.md |

### PCG(3 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| PCG | PCG | R | Default | ComputeFramework, Core, CoreUObject, DeveloperSettings, Engine, Foliage, GeometryAlgorithms, GeometryCore 等 14 个 | DataHierarchyEditor, InteractiveToolsFramework, Json, PCGCompute, Renderer, Settings, SourceControl, UnrealEd 等 9 个 | ../appendix/api/Plugins/PCG.md |
| PCG | PCGEditor | E | Default | Core, CoreUObject, DataHierarchyEditor, Engine, LevelEditor, PCG, PlacementMode, Projects 等 9 个 | AdvancedPreviewScene, AppFramework, ApplicationCore, AssetDefinition, AssetRegistry, AssetTools, BlueprintGraph, ClassViewer 等 48 个 | ../appendix/api/Plugins/PCGEditor.md |
| PCG | PCGCompute | R | PostConfigInit | Core, CoreUObject, Projects, RHI, RenderCore, Renderer | Engine | ../appendix/api/Plugins/PCGCompute.md |

### PCGInterops(4 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| PCGExternalDataInterop | PCGExternalDataInterop | R | Default | Core, CoreUObject, Engine, PCG, Projects | AlembicLib, AlembicLibrary, UnrealEd | ../appendix/api/Plugins/PCGExternalDataInterop.md |
| PCGExternalDataInterop | PCGExternalDataInteropEditor | E | Default | Core, CoreUObject, Engine, PCG, Projects | AlembicLib, AlembicLibrary, PCGEditor, PCGExternalDataInterop, UnrealEd | ../appendix/api/Plugins/PCGExternalDataInteropEditor.md |
| PCGGeometryScriptInterop | PCGGeometryScriptInterop | R | Default | Core, CoreUObject, Engine, GeometryScriptingCore, ModelingOperators, PCG, Projects, RHI 等 9 个 | AdvancedPreviewScene, DynamicMesh, GeometryAlgorithms, GeometryCore, GeometryFramework, ModelingComponents, PCGEditor, UnrealEd | ../appendix/api/Plugins/PCGGeometryScriptInterop.md |
| PCGPythonInterop | PCGPythonInteropEditor | E | Default | Core, CoreUObject, Engine, PCG, Projects | AssetDefinition, PCGEditor, PythonScriptPlugin, Slate, UnrealEd | ../appendix/api/Plugins/PCGPythonInteropEditor.md |

### Performance(3 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| AutomatedPerfTesting | AutomatedPerfTesting | R | Default | Core, Gauntlet | CoreUObject, DeveloperSettings, Engine, Json, JsonUtilities, LevelSequence, MovieScene, Slate 等 9 个 | ../appendix/api/Plugins/AutomatedPerfTesting.md |
| AutomatedPerfTestTools | AutomatedPerfTestLaunchExtension | E | Default | — | — | ../appendix/api/Plugins/AutomatedPerfTestLaunchExtension.md |
| PerformanceMonitor | PerformanceMonitor | R | Default | Core, CoreUObject, Engine, InputCore, RHI, RenderCore | — | ../appendix/api/Plugins/PerformanceMonitor.md |

### Portal(1 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| LauncherChunkInstaller | LauncherChunkInstaller | R | PostConfigInit | — | Core, PakFile | ../appendix/api/Plugins/LauncherChunkInstaller.md |

### Protocols(2 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| MQTT | MQTTCore | R | Default | — | — | ../appendix/api/Plugins/MQTTCore.md |
| MQTT | MQTTCoreEditor | E | Default | — | — | ../appendix/api/Plugins/MQTTCoreEditor.md |

### RenderGraphInsights(1 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| RenderGraphInsights | RenderGraphInsights | E+P | Default | — | Core, CoreUObject, InputCore, RHI, RenderCore, Slate, SlateCore, TraceAnalysis 等 12 个 | ../appendix/api/Plugins/RenderGraphInsights.md |

### RenderTraceInsights(1 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| RenderTraceInsights | RenderTraceInsights | E+P | Default | — | ApplicationCore, Core, CoreUObject, InputCore, RHI, RenderCore, Slate, SlateCore 等 13 个 | ../appendix/api/Plugins/RenderTraceInsights.md |

### RPCBase(1 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| RPCBase | RPCBase | R | Default | ExternalRpcRegistry, HTTPServer | — | ../appendix/api/Plugins/RPCBase.md |

### Runtime(308 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| ActorLayerUtilities | ActorLayerUtilities | R | Default | Core, CoreUObject | Engine | ../appendix/api/Plugins/ActorLayerUtilities.md |
| ActorLayerUtilities | ActorLayerUtilitiesEditor | E | Default | — | ActorLayerUtilities, Core, CoreUObject, EditorStyle, EditorWidgets, Engine, Layers, LevelEditor 等 12 个 | ../appendix/api/Plugins/ActorLayerUtilitiesEditor.md |
| ADM | ADMSpatialization | R | Default | AudioExtensions, Core, CoreUObject, DeveloperSettings, Engine, Networking, OSC | AudioMixer, AudioMixerCore, SignalProcessing | ../appendix/api/Plugins/ADMSpatialization.md |
| IOSTapJoy | IOSTapJoy | R | Default | — | — | (附录未收录) |
| Adjust | AdjustEditor | E | Default | — | Analytics, AnalyticsVisualEditing, Core, CoreUObject, DeveloperSettings, Engine, Projects | ../appendix/api/Plugins/AdjustEditor.md |
| Adjust | AndroidAdjust | R | PreDefault | Core | Analytics, ApplicationCore | ../appendix/api/Plugins/AndroidAdjust.md |
| Adjust | IOSAdjust | R | PreDefault | Core | Analytics | ../appendix/api/Plugins/IOSAdjust.md |
| AnalyticsBlueprintLibrary | AnalyticsBlueprintLibrary | R | PreDefault | Core, CoreUObject, Engine | Analytics | ../appendix/api/Plugins/AnalyticsBlueprintLibrary.md |
| AnalyticsMulticast | AnalyticsMulticastEditor | E | Default | — | Analytics, AnalyticsVisualEditing, Core, CoreUObject, DeveloperSettings, EditorFramework, EditorWidgets, Engine 等 14 个 | ../appendix/api/Plugins/AnalyticsMulticastEditor.md |
| AnalyticsMulticast | AnalyticsMulticast | R | PreDefault | Core, CoreUObject, Engine | Analytics, DeveloperSettings | ../appendix/api/Plugins/AnalyticsMulticast.md |
| FileLogging | FileLogging | R | PreDefault | Core, CoreUObject, Engine | Analytics | ../appendix/api/Plugins/FileLogging.md |
| AndroidBackgroundService | AndroidBackgroundService | RnC | PreEarlyLoadingScreen | — | Core, CoreUObject, Engine, Launch | ../appendix/api/Plugins/AndroidBackgroundService.md |
| AndroidDeviceProfileSelector | AndroidDeviceProfileSelector | E | None | Core, CoreUObject, Json, JsonUtilities | AndroidDeviceDetection, ApplicationCore, Engine, PIEPreviewDeviceSpecification, RHI | ../appendix/api/Plugins/AndroidDeviceProfileSelector.md |
| AndroidDeviceProfileSelector | AndroidDeviceProfileCommandlets | E | None | Core, CoreUObject | AndroidDeviceProfileSelector, Engine, Json, JsonUtilities, PIEPreviewDeviceSpecification | ../appendix/api/Plugins/AndroidDeviceProfileCommandlets.md |
| AndroidDeviceProfileSelector | AndroidDeviceProfileSelectorRuntime | RnC | PostConfigInit | Core, CoreUObject | AndroidDeviceProfileSelector, Core, CoreUObject, Engine, HeadMountedDisplay | ../appendix/api/Plugins/AndroidDeviceProfileSelectorRuntime.md |
| AndroidFileServer | AndroidFileServer | R | PreLoadingScreen | Core | CoreUObject, Engine, Launch, Slate, SlateCore | ../appendix/api/Plugins/AndroidFileServer.md |
| AndroidFileServer | AndroidFileServerEditor | E | PostEngineInit | — | Core, CoreUObject, UnrealEd | ../appendix/api/Plugins/AndroidFileServerEditor.md |
| AndroidMoviePlayer | AndroidMoviePlayer | RnC | PreLoadingScreen | Core, CoreUObject, Engine, MoviePlayer, OpenGLDrv, RHI, RenderCore, Slate | OpenGL | ../appendix/api/Plugins/AndroidMoviePlayer.md |
| AndroidPermission | AndroidPermission | R | Default | Core, Engine | CoreUObject, Slate, SlateCore | ../appendix/api/Plugins/AndroidPermission.md |
| AnimationBudgetAllocator | AnimationBudgetAllocator | R | PreDefault | — | Core, CoreUObject, Engine | ../appendix/api/Plugins/AnimationBudgetAllocator.md |
| ApexDestruction | ApexDestruction | R | PreDefault | — | APEX, ApexDestructionLib, Core, CoreUObject, EditorFramework, Engine, NavigationSystem, PhysX 等 11 个 | ../appendix/api/Plugins/ApexDestruction.md |
| ApexDestruction | ApexDestructionEditor | U | PreDefault | — | APEX, ApexDestruction, ApexDestructionLib, AssetRegistry, AssetTools, ContentBrowser, Core, CoreUObject 等 20 个 | ../appendix/api/Plugins/ApexDestructionEditor.md |
| AppleImageUtils | AppleImageUtils | R | Default | Core, Engine | CoreUObject | ../appendix/api/Plugins/AppleImageUtils.md |
| AppleImageUtils | AppleImageUtilsBlueprintSupport | U | Default | AppleImageUtils, BlueprintGraph, Core, Engine | CoreUObject | ../appendix/api/Plugins/AppleImageUtilsBlueprintSupport.md |
| AppleMoviePlayer | AppleMoviePlayer | RnC | PreLoadingScreen | ApplicationCore, Core, CoreUObject, Engine, MetalRHI, MoviePlayer, RHI, RenderCore 等 9 个 | SlateCore | ../appendix/api/Plugins/AppleMoviePlayer.md |
| AppleARKit | AppleARKit | R | PostConfigInit | Core, Engine, EyeTracker, MRMesh | ARUtilities, AppleImageUtils, AugmentedReality, CoreUObject, HeadMountedDisplay, IOSRuntimeSettings, MetalRHI, Projects 等 14 个 | ../appendix/api/Plugins/AppleARKit.md |
| AppleARKit | AppleARKitPoseTrackingLiveLink | R | PostConfigInit | Core, Engine | ARUtilities, AppleARKit, AppleImageUtils, CoreUObject, HeadMountedDisplay, LiveLinkAnimationCore, LiveLinkInterface, XRBase | ../appendix/api/Plugins/AppleARKitPoseTrackingLiveLink.md |
| AppleARKitFaceSupport | AppleARKitFaceSupport | R | PostConfigInit | Core, Engine | AppleARKit, AppleImageUtils, AugmentedReality, CoreUObject, HeadMountedDisplay, LiveLinkInterface, OnlineSubsystem, ProceduralMeshComponent 等 13 个 | ../appendix/api/Plugins/AppleARKitFaceSupport.md |
| ARUtilities | ARUtilities | R | Default | Core, LiveLinkAnimationCore | AugmentedReality, CoreUObject, Engine, MRMesh, Slate, SlateCore | ../appendix/api/Plugins/ARUtilities.md |
| GoogleARCore | GoogleARCoreBase | R | Default | AugmentedReality, HeadMountedDisplay | AndroidPermission, Core, CoreUObject, Engine, EngineSettings, GoogleARCoreRendering, GoogleARCoreSDK, Launch 等 21 个 | ../appendix/api/Plugins/GoogleARCoreBase.md |
| GoogleARCore | GoogleARCoreRendering | R | PostConfigInit | — | ARUtilities, Core, CoreUObject, Engine, Json, RHI, RenderCore, Renderer | ../appendix/api/Plugins/GoogleARCoreRendering.md |
| GoogleARCoreServices | GoogleARCoreServices | R | Default | AugmentedReality, HeadMountedDisplay | Core, CoreUObject, Engine, GoogleARCoreSDK, XRBase | ../appendix/api/Plugins/GoogleARCoreServices.md |
| ArchVisCharacter | ArchVisCharacter | R | Default | Core, CoreUObject, Engine, RHI, RenderCore | — | ../appendix/api/Plugins/ArchVisCharacter.md |
| AssetTags | AssetTags | R | Default | Core, CoreUObject, Engine | AssetRegistry, CollectionManager, UnrealEd | ../appendix/api/Plugins/AssetTags.md |
| AudioCapture | AudioCapture | R | Default | AudioCaptureCore, AudioMixer, Core, CoreUObject, Engine | AudioCaptureAndroid, AudioCaptureAudioUnit, AudioCaptureRtAudio, AudioCaptureWasapi | ../appendix/api/Plugins/AudioCapture.md |
| AudioCapture | AudioCaptureEditor | U | PostEngineInit | — | AudioCapture, AudioCaptureCore, AudioCaptureRtAudio, AudioCaptureWasapi, AudioEditor, Core, CoreUObject, EditorFramework 等 10 个 | ../appendix/api/Plugins/AudioCaptureEditor.md |
| AudioModulation | AudioModulation | R | PreDefault | AudioExtensions, AudioMixer, Core, LevelSequence, MovieScene, MovieSceneTracks, WaveTable | AudioMixer, AudioMixerCore, CoreUObject, DeveloperSettings, Engine, MetasoundEngine, MetasoundFrontend, MetasoundGraphCore 等 13 个 | ../appendix/api/Plugins/AudioModulation.md |
| AudioModulation | AudioModulationEditor | E | PostEngineInit | MovieSceneTools, Sequencer | AssetDefinition, AudioEditor, AudioExtensions, AudioModulation, Core, CoreUObject, CurveEditor, EditorFramework 等 28 个 | ../appendix/api/Plugins/AudioModulationEditor.md |
| AudioMotorSim | AudioMotorSim | R | PreDefault | Core, CoreUObject, Engine | — | ../appendix/api/Plugins/AudioMotorSim.md |
| AudioMotorSim | AudioMotorSimStandardComponents | R | Default | AudioMotorSim, Core, CoreUObject, Engine | — | ../appendix/api/Plugins/AudioMotorSimStandardComponents.md |
| AudioMotorSim | AudioMotorSimDebug | R | Default | — | AudioMotorSim, Core, CoreUObject, Engine, SlateCore, SlateIM, UnrealEd | ../appendix/api/Plugins/AudioMotorSimDebug.md |
| AudioSynesthesia | AudioSynesthesiaCore | R | PreDefault | Core, CoreUObject, SignalProcessing | AudioMixerCore | ../appendix/api/Plugins/AudioSynesthesiaCore.md |
| AudioSynesthesia | AudioSynesthesia | R | PreDefault | AudioAnalyzer, AudioMixer, AudioMixerCore, AudioSynesthesiaCore, Core, CoreUObject, Engine, SignalProcessing | — | ../appendix/api/Plugins/AudioSynesthesia.md |
| AudioSynesthesia | AudioSynesthesiaEditor | E | PostDefault | AudioAnalyzer, AudioEditor, AudioSynesthesia, Core, CoreUObject, EditorFramework, EditorStyle, Engine 等 12 个 | AssetDefinition | ../appendix/api/Plugins/AudioSynesthesiaEditor.md |
| AudioWidgets | AudioWidgetsCore | R+P | Default | Core | AppFramework, AudioMixerCore, CoreUObject, InputCore, Slate, SlateCore | ../appendix/api/Plugins/AudioWidgetsCore.md |
| AudioWidgets | AudioWidgets | R | Default | AudioAnalyzer, AudioSynesthesia, AudioWidgetsCore, Core, UMG | AdvancedWidgets, AppFramework, AudioMixer, CoreUObject, Engine, InputCore, SignalProcessing, Slate 等 10 个 | ../appendix/api/Plugins/AudioWidgets.md |
| AudioWidgets | AudioWidgetsEditor | E | Default | AudioExtensions, Core, CoreUObject, Engine, PropertyEditor | — | ../appendix/api/Plugins/AudioWidgetsEditor.md |
| CableComponent | CableComponent | R | PreDefault | Core, CoreUObject, Engine, RHI, RenderCore | — | ../appendix/api/Plugins/CableComponent.md |
| CelestialVault | CelestialVault | R | Default | Core, DaySequence | CoreUObject, Engine, Slate, SlateCore | ../appendix/api/Plugins/CelestialVault.md |
| CelestialVault | CelestialVaultEditor | E | Default | Core | CelestialVault, CoreUObject, Engine, Slate, SlateCore, UnrealEd | ../appendix/api/Plugins/CelestialVaultEditor.md |
| ChunkDownloader | ChunkDownloader | R | PostConfigInit | — | ApplicationCore, Core, CoreUObject, HTTP | ../appendix/api/Plugins/ChunkDownloader.md |
| CommonUI | CommonUI | R | Default | ApplicationCore, CommonInput, Core, CoreUObject, EditorFramework, Engine, EnhancedInput, GameplayTags 等 14 个 | Analytics, AnalyticsET, AudioMixer, DeveloperSettings, EngineSettings, SlateCore | ../appendix/api/Plugins/CommonUI.md |
| CommonUI | CommonUIEditor | E | Default | — | ApplicationCore, AssetDefinition, AssetRegistry, CommonUI, Core, CoreUObject, EditorWidgets, Engine 等 18 个 | ../appendix/api/Plugins/CommonUIEditor.md |
| CommonUI | CommonInput | R | Default | Core, CoreUObject, DeveloperSettings, EditorFramework, Engine, EnhancedInput, InputCore, UnrealEd | ApplicationCore, EngineSettings, Slate, SlateCore | ../appendix/api/Plugins/CommonInput.md |
| ComputeFramework | ComputeFramework | R | PostConfigInit | RHI | Core, CoreUObject, Engine, Projects, RenderCore, Renderer | ../appendix/api/Plugins/ComputeFramework.md |
| ComputeFramework | ComputeFrameworkEditor | E | Default | — | ComputeFramework, Core, Engine, UnrealEd | ../appendix/api/Plugins/ComputeFrameworkEditor.md |
| ComputeFramework | ComputeDataInterface | R | Default | ComputeFramework, Core, CoreUObject, Engine | RHI, RenderCore | ../appendix/api/Plugins/ComputeDataInterface.md |
| ComputeFramework | EditableComputeGraph | R | Default | ComputeFramework, Core, CoreUObject, Engine | ComputeDataInterface, RHI, RenderCore | ../appendix/api/Plugins/EditableComputeGraph.md |
| ComputeFramework | EditableComputeGraphEditor | E | Default | — | AssetDefinition, ComputeDataInterface, ComputeFramework, Core, CoreUObject, EditableComputeGraph, Engine, InputCore 等 13 个 | ../appendix/api/Plugins/EditableComputeGraphEditor.md |
| CustomMeshComponent | CustomMeshComponent | R | PreDefault | Core, CoreUObject, Engine, RHI, RenderCore | — | ../appendix/api/Plugins/CustomMeshComponent.md |
| DatabaseSupport | DatabaseSupport | R | Default | Core | — | ../appendix/api/Plugins/DatabaseSupport.md |
| RemoteDatabaseSupport | RemoteDatabaseSupport | R | Default | Core, DatabaseSupport | Sockets | ../appendix/api/Plugins/RemoteDatabaseSupport.md |
| SQLiteCore | SQLiteCore | R | PreDefault | Core, TraceLog | — | ../appendix/api/Plugins/SQLiteCore.md |
| SQLiteSupport | SQLiteSupport | R | Default | Core, DatabaseSupport, SQLiteCore | — | ../appendix/api/Plugins/SQLiteSupport.md |
| DataRegistry | DataRegistry | R | PreDefault | Core, CoreUObject, DeveloperSettings, Engine, GameplayTags | UnrealEd | ../appendix/api/Plugins/DataRegistry.md |
| DataRegistry | DataRegistryEditor | U | PreDefault | — | ApplicationCore, AssetDefinition, BlueprintGraph, ContentBrowser, Core, CoreUObject, DataRegistry, DataTableEditor 等 21 个 | ../appendix/api/Plugins/DataRegistryEditor.md |
| ExampleDeviceProfileSelector | ExampleDeviceProfileSelector | RnC | PostConfigInit | Core | Core, CoreUObject, Engine | ../appendix/api/Plugins/ExampleDeviceProfileSelector.md |
| ExternalGPUStatistics | ExternalGPUStatistics | R | PostEngineInit | Core | Engine, NVML, RHI, RenderCore, oneAPILevelZero | ../appendix/api/Plugins/ExternalGPUStatistics.md |
| Firebase | Firebase | R | PreDefault | — | Core, CoreUObject, Engine, Launch, Swift | ../appendix/api/Plugins/Firebase.md |
| GameFeatures | GameFeatures | R | PreDefault | Core, CoreUObject, DataRegistry, DeveloperSettings, Engine, ModularGameplay | AssetRegistry, GameplayTags, InstallBundleManager, IoStoreOnDemandCore, IrisCore, Json, JsonUtilities, PakFile 等 14 个 | ../appendix/api/Plugins/GameFeatures.md |
| GameFeatures | GameFeaturesEditor | E | Default | Core, CoreUObject, GameFeatures, UnrealEd | AssetRegistry, AssetTools, DataLayerEditor, DataValidation, DeveloperSettings, EditorFramework, EditorSubsystem, Engine 等 15 个 | ../appendix/api/Plugins/GameFeaturesEditor.md |
| GameInput | GameInputBase | R | Default | ApplicationCore, AudioExtensions, Core, CoreUObject, DeveloperSettings, Engine, InputCore, InputDevice 等 10 个 | AudioMixer, AudioMixerCore, WindowsMMDeviceEnumeration | ../appendix/api/Plugins/GameInputBase.md |
| GameInput | GameInputBaseEditor | E | Default | — | — | (附录未收录) |
| GameplayAbilities | GameplayAbilities | R | PreDefault | Core, CoreUObject, DataRegistry, DeveloperSettings, Engine, GameplayTags, GameplayTasks, MovieScene 等 10 个 | EditorFramework, Niagara, SequenceRecorder, Slate, UnrealEd | ../appendix/api/Plugins/GameplayAbilities.md |
| GameplayAbilities | GameplayAbilitiesEditor | U | PreDefault | GameplayTasks | ApplicationCore, AssetDefinition, AssetTools, BlueprintGraph, ClassViewer, ContentBrowser, Core, CoreUObject 等 35 个 | ../appendix/api/Plugins/GameplayAbilitiesEditor.md |
| GameplayBehaviorSmartObjects | GameplayBehaviorSmartObjectsModule | R | PreDefault | AIModule, Core, GameplayBehaviorsModule, GameplayTags, GameplayTasks, SmartObjectsModule | CoreUObject, Engine | ../appendix/api/Plugins/GameplayBehaviorSmartObjectsModule.md |
| GameplayInteractions | GameplayInteractionsModule | R | PreDefault | AIModule, ContextualAnimation, Core, CoreUObject, Engine, GameplayStateTreeModule, GameplayTags, GameplayTasks 等 12 个 | — | ../appendix/api/Plugins/GameplayInteractionsModule.md |
| GameplayStateTree | GameplayStateTreeModule | R | PreDefault | AIModule, Core, CoreUObject, Engine, GameplayTags, GameplayTasks, NavigationSystem, PropertyBindingUtils 等 9 个 | — | ../appendix/api/Plugins/GameplayStateTreeModule.md |
| GeometryCache | GeometryCacheEd | E | Default | AdvancedPreviewScene, AssetDefinition, AssetTools, Core, CoreUObject, EditorFramework, EditorWidgets, Engine 等 19 个 | — | ../appendix/api/Plugins/GeometryCacheEd.md |
| GeometryCache | GeometryCacheSequencer | E | Default | — | Core, CoreUObject, Engine, GeometryCache, GeometryCacheTracks, LevelSequence, MovieScene, MovieSceneTracks 等 13 个 | ../appendix/api/Plugins/GeometryCacheSequencer.md |
| GeometryCache | GeometryCacheStreamer | E | Default | — | Core, CoreUObject, DeveloperSettings, GeometryCache, Slate | ../appendix/api/Plugins/GeometryCacheStreamer.md |
| GeometryCache | GeometryCache | R | Default | Core, CoreUObject, Engine, InputCore, Niagara, NiagaraCore, RHI, RenderCore 等 10 个 | GeometryCore, MeshConversion, MeshDescription, MeshUtilitiesCommon, StaticMeshDescription, TraceLog, UnrealEd | ../appendix/api/Plugins/GeometryCache.md |
| GeometryCache | GeometryCacheTracks | R | Default | Core, CoreUObject, Engine, GeometryCache, MovieScene, MovieSceneTracks | AnimGraphRuntime, Slate, SlateCore, TimeManagement | ../appendix/api/Plugins/GeometryCacheTracks.md |
| GeometryProcessing | GeometryAlgorithms | R | Default | Core, GeometryCore | Eigen | ../appendix/api/Plugins/GeometryAlgorithms.md |
| GeometryProcessing | DynamicMesh | R | Default | Core, GeometryAlgorithms, GeometryCore | Eigen, MeshConversion | ../appendix/api/Plugins/DynamicMesh.md |
| GeometryProcessing | MeshFileUtils | DT | Default | Core, GeometryCore | — | ../appendix/api/Plugins/MeshFileUtils.md |
| GeometryScripting | GeometryScriptingCore | R | PreDefault | Core, DynamicMesh, GeometryCore, GeometryFramework, PhysicsCore, RenderCore | Chaos, CoreUObject, EditorFramework, Engine, GeometryAlgorithms, GeometryCollectionEngine, MeshConversion, MeshConversionEngineTypes 等 17 个 | ../appendix/api/Plugins/GeometryScriptingCore.md |
| GeometryScripting | GeometryScriptingEditor | E | Default | Core, CoreUObject, DynamicMesh, EditorSubsystem, GeometryCore, GeometryFramework, GeometryScriptingCore, PhysicsCore 等 9 个 | BSPUtils, EditorFramework, Engine, GeometryAlgorithms, ImageCore, MeshConversion, MeshDescription, ModelingComponents 等 12 个 | ../appendix/api/Plugins/GeometryScriptingEditor.md |
| GeoReferencing | GeoReferencing | R | Default | Core, Engine | CoreUObject, Engine, InputCore, PROJ, Projects, RHI, SQLiteCore, Slate | ../appendix/api/Plugins/GeoReferencing.md |
| GeoReferencing | GeoReferencingEditor | E | Default | — | Core, CoreUObject, Engine, GeoReferencing, InputCore, Projects, Slate, SlateCore 等 9 个 | ../appendix/api/Plugins/GeoReferencingEditor.md |
| GoogleCloudMessaging | GoogleCloudMessaging | R | PreDefault | — | Core, CoreUObject, EditorFramework, Engine, Launch, UnrealEd | ../appendix/api/Plugins/GoogleCloudMessaging.md |
| GooglePAD | GooglePAD | R | Default | Core | CoreUObject, Engine, Slate, SlateCore | ../appendix/api/Plugins/GooglePAD.md |
| GooglePAD | GooglePADEditor | E | PostEngineInit | — | Core, CoreUObject, EditorFramework, UnrealEd | ../appendix/api/Plugins/GooglePADEditor.md |
| HairStrands | HairStrandsCore | R | PostConfigInit | ChaosCaching, Niagara | Chaos, ChaosCore, Core, CoreUObject, DataflowCore, DataflowEngine, DerivedDataCache, Eigen 等 24 个 | ../appendix/api/Plugins/HairStrandsCore.md |
| HairStrands | HairStrandsDeformer | R | PreDefault | — | Chaos, ComputeFramework, Core, CoreUObject, Engine, HairStrandsCore, HairStrandsSolver, Niagara 等 13 个 | ../appendix/api/Plugins/HairStrandsDeformer.md |
| HairStrands | HairStrandsRuntime | R | Default | — | — | (附录未收录) |
| HairStrands | HairStrandsEditor | E | Default | — | AdvancedPreviewScene, ApplicationCore, AssetDefinition, AssetTools, CommonMenuExtensions, ContentBrowser, Core, CoreUObject 等 36 个 | ../appendix/api/Plugins/HairStrandsEditor.md |
| HairStrands | HairCardGeneratorFramework | E | Default | Core, CoreUObject, Engine | — | ../appendix/api/Plugins/HairCardGeneratorFramework.md |
| HairStrands | HairStrandsDataflow | E | Default | Chaos, ChaosCore, Core, CoreUObject, DataflowCore, DataflowEditor, DataflowEngine, DataflowEnginePlugin 等 23 个 | — | ../appendix/api/Plugins/HairStrandsDataflow.md |
| HairStrands | HairStrandsSolver | R | PreDefault | ChaosCaching, ComputeFramework, Core, CoreUObject, DataflowCore, DataflowEngine, DataflowSimulation, Engine 等 12 个 | — | ../appendix/api/Plugins/HairStrandsSolver.md |
| Harmonix | Harmonix | R | Default | AudioExtensions, Core, DeveloperSettings | CoreUObject, Engine, Slate, SlateCore | ../appendix/api/Plugins/Harmonix.md |
| Harmonix | HarmonixEditor | U | Default | Core, CoreUObject | EditorWidgets, Engine, Harmonix, InputCore, PropertyEditor, Settings, Slate, SlateCore 等 9 个 | ../appendix/api/Plugins/HarmonixEditor.md |
| Harmonix | HarmonixDsp | R | Default | AudioExtensions, Core, CoreUObject, DeveloperSettings, Engine, Harmonix, HarmonixMidi | AssetRegistry, SignalProcessing, UnrealEd | ../appendix/api/Plugins/HarmonixDsp.md |
| Harmonix | HarmonixDspTests | U | Default | — | Core, Engine, HarmonixDsp, HarmonixDspEditor, HarmonixMidi, Json, Projects, SignalProcessing 等 9 个 | ../appendix/api/Plugins/HarmonixDspTests.md |
| Harmonix | HarmonixDspEditor | U | Default | Core, CoreUObject, DeveloperSettings | AssetDefinition, AssetRegistry, AssetTools, AudioEditor, ContentBrowser, CurveEditor, DetailCustomizations, EditorScriptingUtilities 等 22 个 | ../appendix/api/Plugins/HarmonixDspEditor.md |
| Harmonix | HarmonixMidi | R | Default | Core, CoreUObject, MusicEnvironment, TimeManagement | AssetRegistry, AudioExtensions, Engine, Harmonix, UnrealEd | ../appendix/api/Plugins/HarmonixMidi.md |
| Harmonix | HarmonixMidiEditor | U | Default | BlueprintGraph, Core, CoreUObject, EditorFramework, EditorStyle, GraphEditor, PropertyEditor, Settings 等 10 个 | AssetDefinition, AssetTools, ContentBrowser, DetailCustomizations, Engine, HarmonixMidi, InputCore, ToolMenus 等 9 个 | ../appendix/api/Plugins/HarmonixMidiEditor.md |
| Harmonix | HarmonixMidiTests | U | Default | — | Core, CoreUObject, Engine, HarmonixMidi, UnrealEd | ../appendix/api/Plugins/HarmonixMidiTests.md |
| Harmonix | HarmonixMetasound | R | Default | Core, CoreUObject, Engine, Harmonix, HarmonixDsp, HarmonixMidi, MetasoundStandardNodes, MovieScene 等 10 个 | AssetRegistry, AudioExtensions, MetasoundEngine, MetasoundFrontend, MetasoundGenerator, MetasoundGraphCore, SignalProcessing, UnrealEd | ../appendix/api/Plugins/HarmonixMetasound.md |
| Harmonix | HarmonixMetasoundEditor | U | Default | Core, CoreUObject, PropertyEditor, Slate, SlateCore | AssetDefinition, DetailCustomizations, Engine, HarmonixMetasound, HarmonixMidi, MetasoundEditor, MetasoundFrontend, MetasoundGraphCore 等 10 个 | ../appendix/api/Plugins/HarmonixMetasoundEditor.md |
| Harmonix | HarmonixMetasoundTests | U | Default | — | AudioExtensions, Core, CoreUObject, Engine, FunctionalTesting, HarmonixDsp, HarmonixMetasound, HarmonixMidi 等 17 个 | ../appendix/api/Plugins/HarmonixMetasoundTests.md |
| HDRIBackdrop | HDRIBackdrop | E | PostEngineInit | Core | CoreUObject, EditorFramework, Engine, PlacementMode, Projects, Slate, SlateCore, UnrealEd | ../appendix/api/Plugins/HDRIBackdrop.md |
| HPMotionController | HPMotionController | R | PostConfigInit | — | Core, CoreUObject, Engine, InputCore, OpenXRHMD | ../appendix/api/Plugins/HPMotionController.md |
| HTTPChunkInstaller | HTTPChunkInstaller | R | PostConfigInit | — | ApplicationCore, BuildPatchServices, Core, Engine, HTTP, Json, PakFile | ../appendix/api/Plugins/HTTPChunkInstaller.md |
| InputDebugging | InputDebugging | R | Default | UnrealEd | ApplicationCore, Core, CoreUObject, Engine, InputCore, Slate, SlateCore | ../appendix/api/Plugins/InputDebugging.md |
| InputDebugging | InputDebuggingEditor | E | Default | — | ApplicationCore, Core, Engine, MainFrame, Slate, SlateCore | ../appendix/api/Plugins/InputDebuggingEditor.md |
| InstancedActors | InstancedActors | R | Default | Core, CoreUObject, DataRegistry, DeveloperSettings, Engine, GameFeatures, GameplayTags, MassActors 等 17 个 | InputCore, MassGameplayDebug, UnrealEd | ../appendix/api/Plugins/InstancedActors.md |
| InstancedActors | InstancedActorsTestSuite | U | Default | AITestSuite, Core, CoreUObject, Engine, InstancedActors | — | ../appendix/api/Plugins/InstancedActorsTestSuite.md |
| InstancedActors | InstancedActorsEditor | E | Default | Core, CoreUObject, EditorSubsystem, Engine, InstancedActors, LevelEditor, MassCore, MassEntity 等 11 个 | — | ../appendix/api/Plugins/InstancedActorsEditor.md |
| IOSDeviceProfileSelector | IOSPreviewDeviceProfileSelector | E | None | Core, RHI | Core, CoreUObject, Engine, IOSTargetPlatformControls, Json, JsonUtilities, PIEPreviewDeviceSpecification, Projects | ../appendix/api/Plugins/IOSPreviewDeviceProfileSelector.md |
| IOSDeviceProfileSelector | IOSDeviceProfileSelector | RnC | PostConfigInit | Core | Core, CoreUObject, Engine | ../appendix/api/Plugins/IOSDeviceProfileSelector.md |
| IOSReplayKit | IOSReplayKit | R | PreDefault | — | Core, CoreUObject, EditorFramework, Engine, UnrealEd | ../appendix/api/Plugins/IOSReplayKit.md |
| LevelStreamingPersistence | LevelStreamingPersistence | R | PreLoadingScreen | Core, CoreUObject, Engine | DeveloperSettings, PropertyPath | ../appendix/api/Plugins/LevelStreamingPersistence.md |
| LinuxDeviceProfileSelector | LinuxDeviceProfileSelector | RnC | PostConfigInit | Core | Core, CoreUObject, Engine, HeadMountedDisplay | ../appendix/api/Plugins/LinuxDeviceProfileSelector.md |
| LiveLinkOverNDisplay | LiveLinkOverNDisplay | R | Default | Core, CoreUObject | DisplayCluster, Engine, LiveLinkInterface, Settings | ../appendix/api/Plugins/LiveLinkOverNDisplay.md |
| LocationServicesAndroidImpl | LocationServicesAndroidEditor | E | Default | AndroidPermission, Core | Core, CoreUObject, Engine | ../appendix/api/Plugins/LocationServicesAndroidEditor.md |
| LocationServicesAndroidImpl | LocationServicesAndroidImpl | R | Default | Core, CoreUObject, Engine, LocationServicesBPLibrary | Launch, LocationServicesBPLibrary | ../appendix/api/Plugins/LocationServicesAndroidImpl.md |
| LocationServicesBPLibrary | LocationServicesBPLibrary | R | PreDefault | Core, CoreUObject, Engine | — | ../appendix/api/Plugins/LocationServicesBPLibrary.md |
| LocationServicesIOSImpl | LocationServicesIOSEditor | E | Default | Core | Core, CoreUObject, Engine | ../appendix/api/Plugins/LocationServicesIOSEditor.md |
| LocationServicesIOSImpl | LocationServicesIOSImpl | R | Default | Core, CoreUObject, Engine, LocationServicesBPLibrary | Launch, LocationServicesBPLibrary | ../appendix/api/Plugins/LocationServicesIOSImpl.md |
| MassGameplay | MassCommon | R | Default | AIModule, Core, CoreUObject, Engine, MassCore, MassEngine, MassEntity | UnrealEd | ../appendix/api/Plugins/MassCommon.md |
| MassGameplay | MassActors | R | Default | AIModule, Core, CoreUObject, Engine, MassCommon, MassCore, MassEntity, MassMovement 等 13 个 | EditorFramework, UnrealEd | ../appendix/api/Plugins/MassActors.md |
| MassGameplay | MassEQS | R | Default | AIModule, Core, CoreUObject, Engine, MassCommon, MassCore, MassEntity, MassSignals | — | ../appendix/api/Plugins/MassEQS.md |
| MassGameplay | MassSpawner | R | Default | AIModule, Core, CoreUObject, Engine, MassCommon, MassCore, MassEntity, MassEntityEditor 等 10 个 | Slate, UnrealEd | ../appendix/api/Plugins/MassSpawner.md |
| MassGameplay | MassSmartObjects | R | Default | Core, CoreUObject, Engine, GameplayTags, MassCommon, MassCore, MassEntity, MassGameplayExternalTraits 等 16 个 | MassActors | ../appendix/api/Plugins/MassSmartObjects.md |
| MassGameplay | MassSimulation | R | Default | Core, CoreUObject, Engine, MassCommon, MassCore, MassEntity, NavigationSystem | MassEntityEditor, UnrealEd | ../appendix/api/Plugins/MassSimulation.md |
| MassGameplay | MassLOD | R | Default | AIModule, Core, CoreUObject, Engine, MassCommon, MassCore, MassEntity, MassSimulation 等 9 个 | UnrealEd | ../appendix/api/Plugins/MassLOD.md |
| MassGameplay | MassMovement | R | Default | AIModule, Core, CoreUObject, Engine, MassCommon, MassCore, MassEntity, MassLOD 等 13 个 | EditorFramework, UnrealEd | ../appendix/api/Plugins/MassMovement.md |
| MassGameplay | MassCharacterTrajectory | R | Default | Core, CoreUObject, Engine, MassCommon, MassCore, MassEntity, MassMovement, PoseSearch | MassSpawner | ../appendix/api/Plugins/MassCharacterTrajectory.md |
| MassGameplay | MassReplication | R | Default | AIModule, Core, CoreUObject, Engine, MassCommon, MassCore, MassEntity, MassLOD 等 13 个 | EditorFramework, UnrealEd | ../appendix/api/Plugins/MassReplication.md |
| MassGameplay | MassRepresentation | R | Default | AIModule, Core, CoreUObject, Engine, MassActors, MassCommon, MassCore, MassEntity 等 16 个 | EditorFramework, UnrealEd | ../appendix/api/Plugins/MassRepresentation.md |
| MassGameplay | MassGameplayDebug | R | Default | Core, CoreUObject, Engine, InputCore, MassActors, MassCommon, MassCore, MassEntity 等 17 个 | UnrealEd | ../appendix/api/Plugins/MassGameplayDebug.md |
| MassGameplay | MassGameplayEditor | E | Default | AssetTools, ComponentVisualizers, Core, CoreUObject, DetailCustomizations, EditorSubsystem, Engine, InputCore 等 18 个 | AIGraph, DataValidation, GraphEditor, KismetWidgets, PropertyEditor, RenderCore, ToolMenus | ../appendix/api/Plugins/MassGameplayEditor.md |
| MassGameplay | MassMovementEditor | E | PostEngineInit | AssetTools, Core, CoreUObject, DetailCustomizations, EditorFramework, Engine, InputCore, MassCommon 等 16 个 | AppFramework, KismetWidgets, Projects, RenderCore, ToolMenus | ../appendix/api/Plugins/MassMovementEditor.md |
| MassGameplay | MassGameplayExternalTraits | R | Default | Core, MassCore, MassEntity | — | ../appendix/api/Plugins/MassGameplayExternalTraits.md |
| MassGameplay | MassGameplayTestSuite | U | Default | AITestSuite, Core, CoreUObject, Engine, MassCharacterTrajectory, MassCore, MassEntity, MassEntityTestSuite 等 12 个 | — | ../appendix/api/Plugins/MassGameplayTestSuite.md |
| MeshModelingToolset | MeshModelingTools | R | Default | Core, DynamicMesh, GeometryAlgorithms, GeometryCore, GeometryFramework, InputCore, InteractiveToolsFramework, MeshConversion 等 12 个 | CoreUObject, Engine, SlateCore | ../appendix/api/Plugins/MeshModelingTools.md |
| MeshModelingToolset | MeshModelingToolsEditorOnly | E | Default | Core, DynamicMesh, GeometryCore, GeometryFramework, InteractiveToolsFramework, MeshConversion, MeshDescription, MeshModelingTools 等 17 个 | AdvancedPreviewScene, ApplicationCore, CoreUObject, Engine, InputCore, Json, Persona, RenderCore 等 13 个 | ../appendix/api/Plugins/MeshModelingToolsEditorOnly.md |
| MeshModelingToolset | ModelingComponents | R | Default | Core, DeveloperSettings, DynamicMesh, GeometryAlgorithms, GeometryCore, GeometryFramework, InteractiveToolsFramework, MeshConversion 等 12 个 | Chaos, CoreUObject, Engine, GeometryCache, GeometryCollectionEngine, ImageCore, ImageWriteQueue, MeshConversionEngineTypes 等 15 个 | ../appendix/api/Plugins/ModelingComponents.md |
| MeshModelingToolset | ModelingComponentsEditorOnly | E | Default | Core, DynamicMesh, GeometryAlgorithms, GeometryCore, GeometryFramework, InteractiveToolsFramework, MeshConversion, MeshDescription 等 12 个 | AssetTools, BSPUtils, CoreUObject, Engine, InputCore, OpenSubdiv, PhysicsCore, RHI 等 13 个 | ../appendix/api/Plugins/ModelingComponentsEditorOnly.md |
| MeshModelingToolset | ModelingOperators | R | Default | Core, DynamicMesh, GeometryAlgorithms, GeometryCore, InteractiveToolsFramework, MeshConversion, SkeletalMeshDescription, TextureUtilitiesCommon | CoreUObject, Engine | ../appendix/api/Plugins/ModelingOperators.md |
| MeshModelingToolset | ModelingOperatorsEditorOnly | E | Default | Core, DynamicMesh, GeometryAlgorithms, GeometryCore, InteractiveToolsFramework, MeshConversion, MeshDescription, MeshUtilitiesCommon 等 10 个 | CoreUObject, Engine, MeshBuilder, MeshReductionInterface, MeshUtilities, ProxyLODMeshReduction | ../appendix/api/Plugins/ModelingOperatorsEditorOnly.md |
| MeshModelingToolset | SkeletalMeshModifiers | E | Default | Core | ApplicationCore, CoreUObject, Engine, GeometryCore, GeometryFramework, MeshDescription, RenderCore, SkeletalMeshDescription 等 13 个 | ../appendix/api/Plugins/SkeletalMeshModifiers.md |
| DummyMeshReconstructor | DummyMeshReconstructor | R | PostConfigInit | Core, CoreUObject, Engine, MRMesh | — | ../appendix/api/Plugins/DummyMeshReconstructor.md |
| Metasound | MetasoundGraphCore | R | PreDefault | AudioExtensions, Core, CoreUObject, SignalProcessing | MathCore, TraceLog | ../appendix/api/Plugins/MetasoundGraphCore.md |
| Metasound | MetasoundGenerator | R | PreDefault | AudioMixer, Core, CoreUObject, MetasoundFrontend, MetasoundGraphCore, MetasoundStandardNodes | AudioChannelAgnosticCore, AudioExtensions, Engine, SignalProcessing, TraceLog | ../appendix/api/Plugins/MetasoundGenerator.md |
| Metasound | MetasoundFrontend | R | PreDefault | AudioChannelAgnosticCore, AudioExtensions, Core, CoreUObject, Json, JsonUtilities, MetasoundGraphCore, Serialization 等 11 个 | Projects | ../appendix/api/Plugins/MetasoundFrontend.md |
| Metasound | MetasoundStandardNodes | R | PreDefault | AudioExtensions, Core, MetasoundFrontend, Serialization, SignalProcessing | CoreUObject, MetasoundGraphCore | ../appendix/api/Plugins/MetasoundStandardNodes.md |
| Metasound | MetasoundEngine | R | PreDefault | AudioPlatformConfiguration, Core, CoreUObject, DeveloperSettings, Engine, MetasoundFrontend, MetasoundStandardNodes, Serialization 等 9 个 | AssetRegistry, AudioChannelAgnosticCore, AudioExtensions, AudioMixer, MetasoundGenerator, MetasoundGraphCore, Projects, SignalProcessing | ../appendix/api/Plugins/MetasoundEngine.md |
| Metasound | MetasoundEngineTest | U | PreDefault | MetasoundEngine, MetasoundFrontend, MetasoundGenerator, MetasoundGraphCore, MetasoundStandardNodes | AudioChannelAgnosticCore, AudioExtensions, AudioMixer, AutomationDriver, CQTest, Core, CoreUObject, Engine 等 16 个 | ../appendix/api/Plugins/MetasoundEngineTest.md |
| Metasound | MetasoundEditor | U | PreDefault | ApplicationCore, AssetDefinition, AudioAnalyzer, AudioEditor, AudioMixer, AudioWidgets, ClassViewer, ContentBrowser 等 25 个 | AppFramework, AssetTools, AudioExtensions, AudioSynesthesia, ContentBrowser, ContentBrowserAssetDataSource, ContentBrowserData, EditorWidgets 等 22 个 | ../appendix/api/Plugins/MetasoundEditor.md |
| GDKPackageChunkInstall | GDKPackageChunkInstall | RnC | PostConfigInit | — | Core, GDKPackageManifest, GDKRuntime, GRDK | ../appendix/api/Plugins/GDKPackageChunkInstall.md |
| GDKVirtualKeyboard | GDKVirtualKeyboard | RnC | Default | — | — | ../appendix/api/Plugins/GDKVirtualKeyboard.md |
| MicroSoftSpatialSound | MicrosoftSpatialSound | R | PreDefault | AudioExtensions, Core | CoreUObject, Engine | ../appendix/api/Plugins/MicrosoftSpatialSound.md |
| MIDIDevice | MIDIDevice | R | Default | Core, CoreUObject, Engine | — | ../appendix/api/Plugins/MIDIDevice.md |
| MixedRealityCaptureFramework | MixedRealityCaptureFramework | R | PostEngineInit | MediaAssets | Core, CoreUObject, EditorFramework, Engine, HeadMountedDisplay, InputCore, Media, MediaUtils 等 13 个 | ../appendix/api/Plugins/MixedRealityCaptureFramework.md |
| MobilePatchingUtils | MobilePatchingUtils | R | Default | Core, CoreUObject, Engine | BuildPatchServices, HTTP, PakFile | ../appendix/api/Plugins/MobilePatchingUtils.md |
| ModelViewViewModel | ModelViewViewModel | R | Default | Core, CoreUObject, Engine, FieldNotification | Slate, SlateCore, UMG, UnrealEd | ../appendix/api/Plugins/ModelViewViewModel.md |
| ModelViewViewModel | ModelViewViewModelBlueprint | U | Default | Core, CoreUObject, DeveloperSettings, Engine, FieldNotification, ModelViewViewModel | BlueprintGraph, EnhancedInput, Kismet, KismetCompiler, PropertyEditor, PropertyPath, Slate, SlateCore 等 11 个 | ../appendix/api/Plugins/ModelViewViewModelBlueprint.md |
| ModelViewViewModel | ModelViewViewModelEditor | E | Default | BlueprintGraph, Core, CoreUObject, EditorSubsystem, Engine, EnhancedInput, FieldNotification, KismetCompiler 等 11 个 | AdvancedWidgets, ApplicationCore, AssetTools, EditorWidgets, GraphEditor, InputCore, Kismet, MessageLog 等 18 个 | ../appendix/api/Plugins/ModelViewViewModelEditor.md |
| ModelViewViewModel | ModelViewViewModelDebugger | U | Default | Core, CoreUObject, FieldNotification, ModelViewViewModel | Slate, SlateCore, UMG | ../appendix/api/Plugins/ModelViewViewModelDebugger.md |
| ModelViewViewModel | ModelViewViewModelDebuggerEditor | E | Default | Core, CoreUObject, ModelViewViewModel, ModelViewViewModelDebugger | InputCore, LevelEditor, MessageLog, Projects, Slate, SlateCore, ToolMenus, ToolWidgets 等 9 个 | ../appendix/api/Plugins/ModelViewViewModelDebuggerEditor.md |
| ModularGameplay | ModularGameplay | R | PreDefault | Core, Engine, GameplayTags | CoreUObject | ../appendix/api/Plugins/ModularGameplay.md |
| ModularViewports | ModularViewports | R | Default | — | UnrealEd | ../appendix/api/Plugins/ModularViewports.md |
| MsQuic | MsQuicRuntime | R | PreDefault | Core, MsQuic | — | ../appendix/api/Plugins/MsQuicRuntime.md |
| MultiServerReplication | MultiServerReplication | R | Default | OnlineSubsystemUtils | Core, CoreOnline, CoreUObject, Engine, IrisCore, MultiServerConfiguration, NetCore, Sockets | ../appendix/api/Plugins/MultiServerReplication.md |
| MultiServerReplication | MultiServerConfiguration | R | Default | — | Core, CoreUObject | ../appendix/api/Plugins/MultiServerConfiguration.md |
| MusicEnvironment | MusicEnvironment | R | PreDefault | Core, CoreUObject, Engine, GameplayTags, MovieScene, TimeManagement | — | ../appendix/api/Plugins/MusicEnvironment.md |
| MusicEnvironment | MusicEnvironmentEditor | E | Default | — | Core, CoreUObject, MusicEnvironment, PropertyEditor, Slate, SlateCore | ../appendix/api/Plugins/MusicEnvironmentEditor.md |
| MusicEnvironment | MusicEnvironmentTests | U | Default | — | — | (附录未收录) |
| NavCorridor | NavCorridor | R | PreDefault | AIModule, Core, CoreUObject, Engine, NavigationSystem | — | ../appendix/api/Plugins/NavCorridor.md |
| nDisplay | DisplayCluster | R | Default | CinematicCamera, Core, CoreUObject, DisplayClusterConfiguration, DisplayClusterLightCardEditorShaders, DisplayClusterLightCardExtender, Engine, EngineSettings 等 10 个 | CompositeCore, ConcertSyncClient, D3D11RHI, D3D12RHI, EditorWidgets, HeadMountedDisplay, InputCore, Json 等 26 个 | ../appendix/api/Plugins/DisplayCluster.md |
| nDisplay | DisplayClusterFillDerivedDataCache | E | Default | Core, OutputLog, UnrealEd | AssetRegistry, AssetTools, ContentBrowser, CoreUObject, EditorStyle, EditorWidgets, Engine, InputCore 等 19 个 | ../appendix/api/Plugins/DisplayClusterFillDerivedDataCache.md |
| nDisplay | DisplayClusterEditor | E | Default | — | Core, CoreUObject, DisplayCluster, DisplayClusterConfiguration, Engine, EngineSettings, EnhancedInput, UnrealEd | ../appendix/api/Plugins/DisplayClusterEditor.md |
| nDisplay | DisplayClusterProjection | R | Default | CinematicCamera, Core, CoreUObject, DisplayCluster, Engine, Projects, Slate, SlateCore | D3D11RHI, D3D12RHI, DisplayCluster, ProceduralMeshComponent, Projects, RHI, RenderCore, UnrealEd | ../appendix/api/Plugins/DisplayClusterProjection.md |
| nDisplay | DisplayClusterWarp | R | Default | CinematicCamera, Core, CoreUObject, DisplayCluster, Engine, Projects | DisplayCluster, ProceduralMeshComponent, RHI, RenderCore, Renderer, ScalableMPCDI, UnrealEd | ../appendix/api/Plugins/DisplayClusterWarp.md |
| nDisplay | DisplayClusterShaders | R | PostConfigInit | Core, CoreUObject, Engine, Projects, RenderCore | DisplayCluster, DisplayClusterWarp, RHI, Renderer, UnrealEd | ../appendix/api/Plugins/DisplayClusterShaders.md |
| nDisplay | DisplayClusterMessageInterception | R | Default | — | Concert, ConcertSyncClient, ConcertSyncCore, ConcertTransport, Core, CoreUObject, DisplayCluster, Engine 等 9 个 | ../appendix/api/Plugins/DisplayClusterMessageInterception.md |
| nDisplay | DisplayClusterConfiguration | R | PostConfigInit | ActorLayerUtilities, CinematicCamera, MediaAssets, MediaIOCore, OpenColorIO | Core, CoreUObject, Engine, Json, JsonUtilities | ../appendix/api/Plugins/DisplayClusterConfiguration.md |
| nDisplay | DisplayClusterOperator | E | Default | — | Core, CoreUObject, DisplayCluster, EditorStyle, Engine, InputCore, Kismet, Projects 等 16 个 | ../appendix/api/Plugins/DisplayClusterOperator.md |
| nDisplay | DisplayClusterConfigurator | E | Default | — | AdvancedPreviewScene, AppFramework, ApplicationCore, AssetDefinition, AssetTools, BlueprintGraph, CinematicCamera, ClassViewer 等 46 个 | ../appendix/api/Plugins/DisplayClusterConfigurator.md |
| nDisplay | DisplayClusterLightCardEditor | E | Default | — | AdvancedPreviewScene, AppFramework, ApplicationCore, Core, CoreUObject, DisplayCluster, DisplayClusterConfiguration, DisplayClusterLightCardEditorShaders 等 29 个 | ../appendix/api/Plugins/DisplayClusterLightCardEditor.md |
| nDisplay | DisplayClusterLightCardEditorShaders | R | PostConfigInit | — | Core, CoreUObject, Engine, Projects, RHI, RenderCore, Renderer | ../appendix/api/Plugins/DisplayClusterLightCardEditorShaders.md |
| nDisplay | DisplayClusterScenePreview | R | Default | DisplayCluster, DisplayClusterLightCardEditorShaders, DisplayClusterLightCardExtender, RHI | Core, CoreUObject, DisplayClusterConfiguration, Engine, ProceduralMeshComponent, RenderCore, UnrealEd | ../appendix/api/Plugins/DisplayClusterScenePreview.md |
| nDisplay | DisplayClusterColorGrading | E | Default | — | AppFramework, ApplicationCore, ColorCorrectRegions, ColorGradingEditor, Core, CoreUObject, DetailCustomizations, DisplayCluster 等 22 个 | ../appendix/api/Plugins/DisplayClusterColorGrading.md |
| nDisplay | DisplayClusterDetails | E | Default | — | AppFramework, ApplicationCore, ColorCorrectRegions, ColorGradingEditor, Core, CoreUObject, DetailCustomizations, DisplayCluster 等 21 个 | ../appendix/api/Plugins/DisplayClusterDetails.md |
| nDisplay | DisplayClusterStageMonitoring | R | Default | — | Core, CoreUObject, DeveloperSettings, DisplayCluster, DisplayClusterConfiguration, Engine, RHI, RenderCore 等 9 个 | ../appendix/api/Plugins/DisplayClusterStageMonitoring.md |
| nDisplay | DisplayClusterRemoteControlInterceptor | R | Default | — | Core, CoreUObject, DisplayCluster, Engine, RemoteControlInterception, Serialization, UnrealEd | ../appendix/api/Plugins/DisplayClusterRemoteControlInterceptor.md |
| nDisplay | DisplayClusterMedia | R | Default | DisplayClusterConfiguration, Media, MediaAssets, MediaIOCore | Core, CoreUObject, D3D12RHI, DisplayCluster, DisplayClusterShaders, Engine, OpenColorIO, RHI 等 11 个 | ../appendix/api/Plugins/DisplayClusterMedia.md |
| nDisplay | DisplayClusterMediaEditor | E | Default | — | AssetDefinition, Core, CoreUObject, DisplayClusterMedia, Engine, MediaIOCore, MediaIOEditor, SharedMemoryMedia 等 9 个 | ../appendix/api/Plugins/DisplayClusterMediaEditor.md |
| nDisplay | DisplayClusterMonitor | R | Default | Core, CoreUObject, Messaging, MessagingCommon | DisplayCluster, DisplayClusterConfiguration, DisplayClusterShaders, Engine, MediaIOCore, NDIMedia, RHI, RenderCore 等 9 个 | ../appendix/api/Plugins/DisplayClusterMonitor.md |
| nDisplay | DisplayClusterMonitorEditor | E | Default | — | Core, CoreUObject, DisplayClusterMedia, DisplayClusterMonitor, EditorStyle, EditorWidgets, InputCore, LevelEditor 等 20 个 | ../appendix/api/Plugins/DisplayClusterMonitorEditor.md |
| nDisplay | DisplayClusterMultiUser | U | PostEngineInit | — | ConcertSyncClient, Core, CoreUObject, DisplayClusterConfiguration, Engine, MediaAssets | ../appendix/api/Plugins/DisplayClusterMultiUser.md |
| nDisplay | DisplayClusterTests | U | Default | — | Core, CoreUObject, DisplayCluster, DisplayClusterConfiguration, DisplayClusterConfigurator, Engine, OpenColorIO, SlateCore 等 10 个 | ../appendix/api/Plugins/DisplayClusterTests.md |
| nDisplay | DisplayClusterMoviePipeline | U | Default | ActorLayerUtilities, CinematicCamera, DisplayCluster, DisplayClusterConfiguration, ImageWriteQueue, LevelSequence, MovieRenderPipelineCore, MovieRenderPipelineRenderPasses 等 12 个 | Core, CoreUObject, DisplayCluster, Engine, Imath, Json, UEOpenExr, UEOpenExrRTTI | ../appendix/api/Plugins/DisplayClusterMoviePipeline.md |
| nDisplay | DisplayClusterMoviePipelineEditor | E | Default | — | AppFramework, ApplicationCore, AssetTools, BlueprintGraph, Core, CoreUObject, DesktopPlatform, DisplayCluster 等 34 个 | ../appendix/api/Plugins/DisplayClusterMoviePipelineEditor.md |
| nDisplay | SharedMemoryMedia | R | Default | MediaIOCore | Core, CoreUObject, D3D12RHI, Engine, Media, MediaAssets, RHI, RenderCore 等 9 个 | ../appendix/api/Plugins/SharedMemoryMedia.md |
| nDisplay | SharedMemoryMediaEditor | E | Default | — | AssetDefinition, Core, CoreUObject, DisplayClusterModularFeaturesEditor, Engine, MediaPlayerEditor, SharedMemoryMedia, UnrealEd | ../appendix/api/Plugins/SharedMemoryMediaEditor.md |
| nDisplay | DisplayClusterReplication | R | Default | Core, CoreUObject, DisplayCluster, DisplayClusterConfiguration, Engine | Core, CoreUObject, Engine, NetCore, OnlineSubsystem, OnlineSubsystemUtils, Sockets | ../appendix/api/Plugins/DisplayClusterReplication.md |
| nDisplayModularFeatures | DisplayClusterLightCardExtender | R | Default | Core, CoreUObject, Engine | Sequencer, UnrealEd | ../appendix/api/Plugins/DisplayClusterLightCardExtender.md |
| nDisplayModularFeatures | DisplayClusterModularFeaturesEditor | E | Default | Core, CoreUObject, Engine | UnrealEd | ../appendix/api/Plugins/DisplayClusterModularFeaturesEditor.md |
| NetworkPrediction | NetworkPrediction | R | Default | Chaos, Core, CoreUObject, Engine, NetCore, PhysicsCore, RenderCore, TraceLog | UnrealEd | ../appendix/api/Plugins/NetworkPrediction.md |
| NetworkPredictionExtras | NetworkPredictionExtras | R | Default | Chaos, Core, CoreUObject, Engine, InputCore, NetworkPrediction, PhysicsCore, RenderCore | Engine, NetCore, TraceLog, UnrealEd | ../appendix/api/Plugins/NetworkPredictionExtras.md |
| NetworkPredictionExtras | NetworkPredictionExtrasLatentLoad | R | None | Chaos, Core, CoreUObject, Engine, InputCore, NetworkPrediction, PhysicsCore, RenderCore | Engine, TraceLog, UnrealEd | ../appendix/api/Plugins/NetworkPredictionExtrasLatentLoad.md |
| NetworkPredictionInsights | NetworkPredictionInsights | E+P | Default | — | ApplicationCore, AssetRegistry, Core, CoreUObject, EditorFramework, EditorWidgets, Engine, InputCore 等 16 个 | ../appendix/api/Plugins/NetworkPredictionInsights.md |
| GeForceNOWWrapper | GeForceNOWWrapper | CnC | EarliestPossible | GeForceNOW, Slate | Core, SlateCore | ../appendix/api/Plugins/GeForceNOWWrapper.md |
| Reflex | Reflex | C | Default | — | — | ../appendix/api/Plugins/Reflex.md |
| OpenCV | OpenCVHelper | R | PostConfigInit | Core, CoreUObject, Engine | OpenCV, Projects | ../appendix/api/Plugins/OpenCVHelper.md |
| OpenXR | OpenXRHMD | R | PostConfigInit | D3D11RHI, D3D12RHI, DX11, DX12, HeadMountedDisplay, OpenGL, OpenGLDrv, Vulkan 等 10 个 | AugmentedReality, BuildSettings, Core, CoreUObject, DeveloperSettings, EditorFramework, Engine, EngineSettings 等 15 个 | ../appendix/api/Plugins/OpenXRHMD.md |
| OpenXR | OpenXRInput | R | PostEngineInit | EnhancedInput | ApplicationCore, Core, CoreUObject, EditorFramework, Engine, HeadMountedDisplay, InputCore, InputDevice 等 13 个 | ../appendix/api/Plugins/OpenXRInput.md |
| OpenXR | OpenXRAR | R | PostConfigInit | Core, Engine, MRMesh | ApplicationCore, AugmentedReality, CoreUObject, HeadMountedDisplay, OpenXRHMD, Projects, RHI, RenderCore 等 10 个 | ../appendix/api/Plugins/OpenXRAR.md |
| OpenXR | OpenXREditor | E | Default | — | Core, CoreUObject, EditorFramework, OpenXRHMD, OpenXRInput, UnrealEd | ../appendix/api/Plugins/OpenXREditor.md |
| OpenXREyeTracker | OpenXREyeTracker | R | PostConfigInit | EyeTracker | ApplicationCore, Core, CoreUObject, Engine, HeadMountedDisplay, InputCore, InputDevice, OpenXRHMD 等 11 个 | ../appendix/api/Plugins/OpenXREyeTracker.md |
| OpenXRHandTracking | OpenXRHandTracking | R | PostConfigInit | InputDevice | ApplicationCore, Core, CoreUObject, EditorFramework, Engine, HeadMountedDisplay, InputCore, InputEditor 等 16 个 | ../appendix/api/Plugins/OpenXRHandTracking.md |
| OpenXRHandTracking | OpenXRHandTrackingEditor | E | Default | — | — | (附录未收录) |
| OpenXRMsftHandInteraction | OpenXRMsftHandInteraction | R | PostConfigInit | — | Core, CoreUObject, Engine, InputCore, OpenXRHMD | ../appendix/api/Plugins/OpenXRMsftHandInteraction.md |
| OpenXRViveTracker | OpenXRViveTracker | R | PostConfigInit | InputDevice | ApplicationCore, Core, CoreUObject, Engine, HeadMountedDisplay, InputCore, OpenXRHMD, OpenXRInput 等 12 个 | ../appendix/api/Plugins/OpenXRViveTracker.md |
| OptionalMobileFeaturesBPLibrary | OptionalMobileFeaturesBPLibrary | R | PreDefault | Core, CoreUObject, Engine | ApplicationCore | ../appendix/api/Plugins/OptionalMobileFeaturesBPLibrary.md |
| OSC | OSC | R | Default | Core, CoreUObject, Engine | InputCore, Networking, Sockets | ../appendix/api/Plugins/OSC.md |
| AESGCMHandlerComponent | AESGCMHandlerComponent | R | Default | Core, CoreUObject, NetCore, PacketHandler, PlatformCrypto, PlatformCryptoContext | — | ../appendix/api/Plugins/AESGCMHandlerComponent.md |
| AESHandlerComponent | AESHandlerComponent | R | Default | Core, PacketHandler, PlatformCrypto, PlatformCryptoContext | — | ../appendix/api/Plugins/AESHandlerComponent.md |
| DTLSHandlerComponent | DTLSHandlerComponent | R | Default | SSL | Core, CoreUObject, Engine, NetCore, PacketHandler | ../appendix/api/Plugins/DTLSHandlerComponent.md |
| PICOController | PICOController | R | PostConfigInit | — | Core, CoreUObject, Engine, InputCore, OpenXRHMD | ../appendix/api/Plugins/PICOController.md |
| PreLoadScreenMoviePlayer | PreLoadScreenMoviePlayer | RnC | PreEarlyLoadingScreen | — | Analytics, AnalyticsET, ApplicationCore, BuildPatchServices, Core, CoreUObject, Engine, HTTP 等 17 个 | ../appendix/api/Plugins/PreLoadScreenMoviePlayer.md |
| ProceduralMeshComponent | ProceduralMeshComponent | R | PreDefault | Core, CoreUObject, Engine, MeshDescription, PhysicsCore, RHI, RenderCore, StaticMeshDescription | — | ../appendix/api/Plugins/ProceduralMeshComponent.md |
| ProceduralMeshComponent | ProceduralMeshComponentEditor | E | Default | AssetRegistry, AssetTools, Core, CoreUObject, EditorFramework, Engine, MeshDescription, ProceduralMeshComponent 等 15 个 | — | ../appendix/api/Plugins/ProceduralMeshComponentEditor.md |
| PropertyAccessEditor | PropertyAccessEditor | U | PreDefault | Core, CoreUObject, Slate | AnimGraph, BlueprintGraph, Engine, GraphEditor, InputCore, KismetWidgets, PropertyPath, SlateCore 等 9 个 | ../appendix/api/Plugins/PropertyAccessEditor.md |
| PropertyBindingUtils | PropertyBindingUtils | R | PreDefault | BlueprintGraph, Core, CoreUObject, Engine, UnrealEd | DeveloperSettings, InputCore, RenderCore | ../appendix/api/Plugins/PropertyBindingUtils.md |
| PropertyBindingUtils | PropertyBindingUtilsEditor | E | Default | BlueprintGraph, Core, CoreUObject, EditorFramework, Engine, InputCore, PropertyBindingUtils, Slate 等 10 个 | StructUtilsEditor | ../appendix/api/Plugins/PropertyBindingUtilsEditor.md |
| PropertyBindingUtils | PropertyBindingUtilsTestSuite | U | PreDefault | AITestSuite, Core, CoreUObject, Engine, PropertyBindingUtils | EditorFramework, UnrealEd | ../appendix/api/Plugins/PropertyBindingUtilsTestSuite.md |
| RenderTrace | RenderTrace | R | PostConfigInit | — | ApplicationCore, Core, CoreUObject, DeveloperSettings, EditorFramework, Engine, MaterialUtilities, Projects 等 14 个 | ../appendix/api/Plugins/RenderTrace.md |
| ReplicationGraph | ReplicationGraph | R | PreDefault | — | Core, CoreUObject, Engine, EngineSettings, NetCore, PerfCounters | ../appendix/api/Plugins/ReplicationGraph.md |
| ReplicationSystemTestPlugin | ReplicationSystemTestPlugin | U | Default | Core, Projects | Catch2, CoreUObject, Engine, LowLevelTestsRunner, NetCore | ../appendix/api/Plugins/ReplicationSystemTestPlugin.md |
| ResonanceAudio | ResonanceAudio | R | PreDefault | AudioMixer, Core, CoreUObject, Engine, ProceduralMeshComponent, SoundFieldRendering | AudioExtensions, EditorFramework, InputCore, Landscape, ProceduralMeshComponent, Projects, UnrealEd | ../appendix/api/Plugins/ResonanceAudio.md |
| ResonanceAudio | ResonanceAudioEditor | E | PostEngineInit | AudioEditor, AudioMixer, Core, CoreUObject, Engine, InputCore, LevelEditor, RHI 等 11 个 | AssetDefinition, EditorFramework, Eigen, Landscape, Projects, PropertyEditor, Slate, SlateCore | ../appendix/api/Plugins/ResonanceAudioEditor.md |
| RigVM | RigVM | R | PreDefault | AnimGraphRuntime, AnimationCore, Core, CoreUObject, DeveloperSettings, Engine, Projects, RewindDebuggerRuntimeInterface 等 9 个 | AssetTools, BlueprintGraph, StructUtilsEditor, UnrealEd | ../appendix/api/Plugins/RigVM.md |
| RigVM | RigVMDeveloper | U | PreDefault | AnimationCore, AssetTools, Core, CoreUObject, Engine, Json, KismetCompiler, Projects 等 11 个 | ApplicationCore, BlueprintGraph, EditorFramework, GraphEditor, Kismet, MessageLog, Slate, SlateCore 等 9 个 | ../appendix/api/Plugins/RigVMDeveloper.md |
| RigVM | RigVMEditor | E | PostEngineInit | AnimationCore, AnimationEditorWidgets, AnimationWidgets, AppFramework, ApplicationCore, BlueprintGraph, ContentBrowser, ContentBrowserData 等 39 个 | ApplicationCore, FieldNotification, InputCore, Json, JsonUtilities, ToolWidgets, TraceLog, WorkspaceMenuStructure | ../appendix/api/Plugins/RigVMEditor.md |
| ScriptableToolsFramework | ScriptableToolsFramework | R | PreDefault | Core, CoreUObject, GeometryCore, InputCore, InteractiveToolsFramework, ModelingComponents, PhysicsCore, RenderCore 等 9 个 | Engine, Slate, SlateCore | ../appendix/api/Plugins/ScriptableToolsFramework.md |
| ScriptableToolsFramework | EditorScriptableToolsFramework | E | Default | Core, CoreUObject, GeometryCore, InteractiveToolsFramework, PhysicsCore, RenderCore, ScriptableToolsFramework | Engine, UnrealEd | ../appendix/api/Plugins/EditorScriptableToolsFramework.md |
| SignificanceManager | SignificanceManager | R | PreDefault | — | Core, CoreUObject, Engine, EngineSettings | ../appendix/api/Plugins/SignificanceManager.md |
| SkeletalMerging | SkeletalMerging | R | Default | — | Core, CoreUObject, Engine | ../appendix/api/Plugins/SkeletalMerging.md |
| SmartObjects | SmartObjectsModule | R | PreDefault | AIModule, BlueprintGraph, Core, CoreUObject, DeveloperSettings, Engine, GameplayAbilities, GameplayTags 等 16 个 | InputCore, RenderCore | ../appendix/api/Plugins/SmartObjectsModule.md |
| SmartObjects | SmartObjectsTestSuite | U | PreDefault | — | EditorFramework, UnrealEd | ../appendix/api/Plugins/SmartObjectsTestSuite.md |
| SmartObjects | SmartObjectsEditorModule | E | PostEngineInit | AdvancedPreviewScene, Core, CoreUObject, Engine, GameplayTags, SmartObjectsModule, SourceControl, UnrealEd 等 9 个 | ApplicationCore, AssetDefinition, BlueprintGraph, ComponentVisualizers, InputCore, PropertyAccessEditor, PropertyBindingUtils, PropertyBindingUtilsEditor 等 15 个 | ../appendix/api/Plugins/SmartObjectsEditorModule.md |
| SoundCueTemplates | SoundCueTemplates | R | Default | Core | CoreUObject, DeveloperSettings, Engine, Slate, SlateCore | ../appendix/api/Plugins/SoundCueTemplates.md |
| SoundCueTemplates | SoundCueTemplatesEditor | E | PostDefault | AssetDefinition, AudioEditor, Core, SoundCueTemplates, ToolMenus | ContentBrowser, CoreUObject, Engine, GameProjectGeneration, Slate, SlateCore, UnrealEd | ../appendix/api/Plugins/SoundCueTemplatesEditor.md |
| SoundFields | SoundFields | R | PreDefault | Core | AudioExtensions, CoreUObject, Engine, SignalProcessing, SoundFieldRendering | ../appendix/api/Plugins/SoundFields.md |
| SoundMod | SoundMod | R | Default | AudioExtensions, Core, CoreUObject, Engine | — | ../appendix/api/Plugins/SoundMod.md |
| SoundMod | SoundModImporter | E | Default | — | Core, CoreUObject, EditorFramework, Engine, Slate, SlateCore, SoundMod, ToolMenus 等 9 个 | ../appendix/api/Plugins/SoundModImporter.md |
| Soundscape | Soundscape | R | PreDefault | — | — | (附录未收录) |
| Soundscape | SoundscapeEditor | E | Default | — | — | (附录未收录) |
| SoundUtilities | SoundUtilities | R | PreDefault | AudioMixer, Core, CoreUObject, Engine, InputCore, Projects, Slate, SlateCore 等 9 个 | — | ../appendix/api/Plugins/SoundUtilities.md |
| SoundUtilities | SoundUtilitiesEditor | E | Default | AssetDefinition, AudioEditor, AudioMixer, ContentBrowser, Core, CoreUObject, EditorFramework, Engine 等 13 个 | — | ../appendix/api/Plugins/SoundUtilitiesEditor.md |
| Spatialization | Spatialization | R | PreDefault | Core | AudioExtensions, CoreUObject, Engine, SignalProcessing | ../appendix/api/Plugins/Spatialization.md |
| Spatialization | SpatializationEditor | E | PostEngineInit | AudioEditor, Core | AssetDefinition, AudioMixer, CoreUObject, EditorFramework, Engine, LevelEditor, Spatialization, UnrealEd | ../appendix/api/Plugins/SpatializationEditor.md |
| StateTree | StateTreeModule | R | PreDefault | — | — | ../appendix/api/Plugins/StateTreeModule.md |
| StateTree | StateTreeTestSuite | U | PreDefault | AIModule, AITestSuite, Core, CoreUObject, Engine, GameplayTags, PropertyBindingUtils, PropertyBindingUtilsEditor 等 10 个 | EditorFramework, UnrealEd | ../appendix/api/Plugins/StateTreeTestSuite.md |
| StateTree | StateTreeDeveloper | DT | Default | Core, SlateCore | CoreUObject, InputCore, Slate, StateTreeModule | ../appendix/api/Plugins/StateTreeDeveloper.md |
| StateTree | StateTreeEditorModule | U | Default | AssetTools, BlueprintGraph, Core, CoreUObject, EditorFramework, EditorStyle, EditorSubsystem, Engine 等 22 个 | AppFramework, ApplicationCore, AssetDefinition, DetailCustomizations, DeveloperSettings, EditorInteractiveToolsFramework, EditorWidgets, GameplayInsights 等 21 个 | ../appendix/api/Plugins/StateTreeEditorModule.md |
| SteamAudio | SteamAudio | R | PreDefault | AudioMixer, Core, CoreUObject, Engine, InputCore, RHI, RenderCore | AudioExtensions, AudioMixer, Core, CoreUObject, EditorFramework, Engine, InputCore, Landscape 等 10 个 | ../appendix/api/Plugins/SteamAudio.md |
| SteamController | SteamController | R | Default | InputCore, InputDevice | ApplicationCore, Core, CoreUObject, Engine, SteamShared | ../appendix/api/Plugins/SteamController.md |
| SteamShared | SteamShared | R | PreDefault | — | Core, Sockets | ../appendix/api/Plugins/SteamShared.md |
| SteamSockets | SteamSockets | R | Default | — | Core, CoreUObject, Engine, NetCore, OnlineSubsystem, OnlineSubsystemSteam, PacketHandler, Sockets 等 9 个 | ../appendix/api/Plugins/SteamSockets.md |
| SunPosition | SunPosition | R | PostEngineInit | — | Core, CoreUObject, EditorFramework, Engine, PlacementMode, Projects, Slate, SlateCore 等 9 个 | ../appendix/api/Plugins/SunPosition.md |
| Synthesis | Synthesis | R | PreDefault | AudioExtensions, Core, CoreUObject, Engine | AudioMixer, AudioSynesthesiaCore, InputCore, Projects, SignalProcessing, Slate, SlateCore, UMG | ../appendix/api/Plugins/Synthesis.md |
| Synthesis | SynthesisEditor | E | Default | AudioEditor, AudioMixer, ContentBrowser, Core, CoreUObject, EditorFramework, Engine, Slate 等 12 个 | AssetDefinition, AudioSynesthesiaCore, DeveloperSettings, SignalProcessing, UMG, UMGEditor | ../appendix/api/Plugins/SynthesisEditor.md |
| USDCore | UnrealUSDWrapper | R | Default | CinematicCamera, Core, CoreUObject, Engine, IntelTBB, Projects, Python3, USDClasses | — | ../appendix/api/Plugins/UnrealUSDWrapper.md |
| USDCore | USDUtilities | R | Default | Core, CoreUObject, HairStrandsCore, MaterialX, USDClasses, UnrealUSDWrapper | CinematicCamera, ControlRig, DesktopPlatform, DeveloperSettings, Engine, Foliage, GeometryCache, HairStrandsCore 等 28 个 | ../appendix/api/Plugins/USDUtilities.md |
| USDCore | USDClasses | R | Default | Analytics, Core, CoreUObject, Engine, Slate, SlateCore | DeveloperSettings, GeometryCache, GeometryFramework, HairStrandsCore, Json, LevelSequence, MaterialEditor, MeshDescription 等 11 个 | ../appendix/api/Plugins/USDClasses.md |
| WarpUtils | PFMExporter | R | PostConfigInit | Core, CoreUObject, Engine | Core, CoreUObject, EditorFramework, Engine, Projects, RHI, RenderCore, UnrealEd | ../appendix/api/Plugins/PFMExporter.md |
| WarpUtils | WarpUtils | R | Default | Core | CoreUObject, Engine, Slate, SlateCore | ../appendix/api/Plugins/WarpUtils.md |
| WaveTable | WaveTable | R | Default | AudioExtensions, Core, CoreUObject, Engine | SignalProcessing | ../appendix/api/Plugins/WaveTable.md |
| WaveTable | WaveTableEditor | E | PostEngineInit | AssetTools, SlateCore | AssetDefinition, AudioEditor, AudioExtensions, Core, CoreUObject, CurveEditor, EditorFramework, EditorWidgets 等 17 个 | ../appendix/api/Plugins/WaveTableEditor.md |
| WebBrowserNativeProxy | WebBrowserNativeProxy | R | PreDefault | Core, CoreUObject, WebBrowser | Slate, SlateCore | ../appendix/api/Plugins/WebBrowserNativeProxy.md |
| WebBrowserWidget | WebBrowserWidget | R | PreDefault | Core, CoreUObject, Engine, Slate, SlateCore, UMG, WebBrowser | EditorFramework, UnrealEd, WebBrowserTexture | ../appendix/api/Plugins/WebBrowserWidget.md |
| WebMMoviePlayer | WebMMoviePlayer | RnC | PreLoadingScreen | — | Core, Engine, MediaUtils, MoviePlayer, RHI, RenderCore, SDL3, Slate 等 10 个 | ../appendix/api/Plugins/WebMMoviePlayer.md |
| MSGameOSSSelector | MSGameOSSSelector | RnC | PostConfigInit | — | — | ../appendix/api/Plugins/MSGameOSSSelector.md |
| MSGameStore | MSGameStore | RnC | PostConfigInit | — | Core | ../appendix/api/Plugins/MSGameStore.md |
| MSGamingRuntime | MSGamingRuntime | RnC | PostConfigInit | — | UnrealEd | ../appendix/api/Plugins/MSGamingRuntime.md |
| MSGamingSupport | MSGamingSupportEditor | E | PostEngineInit | — | Core, CoreUObject, Engine, GDKPlatformEditor, Projects, Settings, Slate, SlateCore | ../appendix/api/Plugins/MSGamingSupportEditor.md |
| WinDualShock | WinDualShock | RnC | Default | ApplicationCore, AudioExtensions, AudioMixer, AudioMixerCore, Core, CoreUObject, Engine, InputDevice 等 10 个 | — | ../appendix/api/Plugins/WinDualShock.md |
| WinVirtualKeyboard | WinVirtualKeyboard | RnC | Default | — | — | (附录未收录) |
| XInputDevice | XInputDevice | R | Default | ApplicationCore, Core, Engine, InputDevice | — | ../appendix/api/Plugins/XInputDevice.md |
| WindowsDeviceProfileSelector | WindowsDeviceProfileSelector | RnC | PostConfigInit | Core | Engine, RHI | ../appendix/api/Plugins/WindowsDeviceProfileSelector.md |
| WindowsMoviePlayer | WindowsMoviePlayer | RnC | PreLoadingScreen | — | Core, CoreUObject, Engine, InputCore, MoviePlayer, RHI, RenderCore, Slate 等 9 个 | ../appendix/api/Plugins/WindowsMoviePlayer.md |
| WorldConditions | WorldConditions | R | Default | — | — | ../appendix/api/Plugins/WorldConditions.md |
| WorldConditions | WorldConditionsEditor | E | PostEngineInit | — | — | ../appendix/api/Plugins/WorldConditionsEditor.md |
| WorldConditions | WorldConditionsTestSuite | U | Default | — | EditorFramework, UnrealEd | ../appendix/api/Plugins/WorldConditionsTestSuite.md |
| XRScribe | XRScribe | R | PostConfigInit | Core, CoreUObject, Engine, OpenXR, OpenXRHMD, RHI | DeveloperSettings, Projects | ../appendix/api/Plugins/XRScribe.md |
| XRVisualization | XRVisualization | R | Default | — | Core, CoreUObject, Engine, EngineSettings, HeadMountedDisplay, ProceduralMeshComponent, RHI, RenderCore 等 9 个 | ../appendix/api/Plugins/XRVisualization.md |
| XRBase | XRBase | R | PostConfigInit | AugmentedReality, HeadMountedDisplay | Core, CoreUObject, EditorFramework, Engine, EngineSettings, InputCore, RHI, RenderCore 等 12 个 | ../appendix/api/Plugins/XRBase.md |
| XRBase | XRBaseEditor | E | Default | — | Core, CoreUObject, HeadMountedDisplay, InputCore, PropertyEditor, Slate, SlateCore, XRBase | ../appendix/api/Plugins/XRBaseEditor.md |
| ZoneGraph | ZoneGraph | R | Default | Core, CoreUObject, DeveloperSettings, Engine, MassCore, MassEntity, RHI, RenderCore | EditorFramework, UnrealEd | ../appendix/api/Plugins/ZoneGraph.md |
| ZoneGraph | ZoneGraphEditor | E | PostEngineInit | AssetTools, ComponentVisualizers, Core, CoreUObject, DetailCustomizations, EditorFramework, Engine, InputCore 等 14 个 | AIGraph, AppFramework, GraphEditor, KismetWidgets, Projects, PropertyEditor, RenderCore, ToolMenus | ../appendix/api/Plugins/ZoneGraphEditor.md |
| ZoneGraph | ZoneGraphTestSuite | U | Default | AIModule, AITestSuite, Core, CoreUObject, Engine, ZoneGraph | EditorFramework, UnrealEd | ../appendix/api/Plugins/ZoneGraphTestSuite.md |
| ZoneGraph | ZoneGraphDebug | R | Default | AIModule, Core, CoreUObject, Engine, GameplayTags, GameplayTasks, ZoneGraph | EditorFramework, UnrealEd | ../appendix/api/Plugins/ZoneGraphDebug.md |
| ZoneGraphAnnotations | ZoneGraphAnnotations | R | Default | Core, CoreUObject, Engine, MassCore, MassEntity, RHI, ZoneGraph, ZoneGraphDebug | EditorFramework, UnrealEd | ../appendix/api/Plugins/ZoneGraphAnnotations.md |

### ScriptPlugin(2 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| ScriptPlugin | ScriptPlugin | R | PreDefault | Core, CoreUObject, EditorFramework, Engine, InputCore, SlateCore, UnrealEd | — | ../appendix/api/Plugins/ScriptPlugin.md |
| ScriptPlugin | ScriptEditorPlugin | E | Default | AssetTools, BlueprintGraph, ClassViewer, Core, CoreUObject, EditorFramework, Engine, InputCore 等 12 个 | — | ../appendix/api/Plugins/ScriptEditorPlugin.md |

### Slate(2 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| SlateInsights | SlateInsights | E+P | Default | — | ApplicationCore, AssetRegistry, Core, CoreUObject, Engine, InputCore, Slate, SlateCore 等 14 个 | ../appendix/api/Plugins/SlateInsights.md |
| SlateScripting | SlateScriptingCommands | R | Default | Core, CoreUObject, Engine, Slate, SlateCore | InputCore | ../appendix/api/Plugins/SlateScriptingCommands.md |

### SubtitlesAndClosedCaptions(2 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| SubtitlesAndClosedCaptions | SubtitlesAndClosedCaptions | R | Default | Core, CoreUObject, DeveloperSettings, Engine, InputCore, MovieScene, MovieSceneTracks, UMG 等 9 个 | Slate, SlateCore | ../appendix/api/Plugins/SubtitlesAndClosedCaptions.md |
| SubtitlesAndClosedCaptions | SubtitlesAndClosedCaptionsEditor | U | Default | AssetDefinition, Core, CoreUObject, Engine, UnrealEd | AssetTools, Blutility, LevelSequence, MovieScene, MovieSceneTools, Overlay, Sequencer, SequencerCore 等 11 个 | ../appendix/api/Plugins/SubtitlesAndClosedCaptionsEditor.md |

### Tests(17 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| AudioCQTests | AudioCQTests | DT | Default | — | — | (附录未收录) |
| AutomationDriverTests | AutomationDriverTests | U | PreDefault | — | — | (附录未收录) |
| CQTest | CQTestTests | DT | Default | — | — | (附录未收录) |
| CQTestEnhancedInput | CQTestEnhancedInput | DT | Default | — | — | (附录未收录) |
| CQTestEnhancedInput | CQTestEnhancedInputTests | DT | Default | — | — | (附录未收录) |
| CQTestExperimental | CQTestExperimentalTests | DT | Default | — | — | (附录未收录) |
| EditorTests | EditorTests | E | Default | — | — | (附录未收录) |
| FbxAutomationTestBuilder | FbxAutomationTestBuilder | E | Default | — | — | (附录未收录) |
| FunctionalTestingEditor | FunctionalTestingEditor | E | Default | — | — | (附录未收录) |
| InterchangeTests | InterchangeTests | E | Default | — | — | (附录未收录) |
| InterchangeTests | InterchangeTestEditor | E | Default | — | — | (附录未收录) |
| PythonAutomationTest | PythonAutomationTest | E | Default | — | — | (附录未收录) |
| RHITests | RHITests | R | PostConfigInit | — | — | (附录未收录) |
| RuntimeTests | RuntimeTests | R | PreDefault | — | — | (附录未收录) |
| TestFramework | TestFramework | DT | Default | — | — | (附录未收录) |
| TestSamples | TestSamples | E | Default | — | — | (附录未收录) |
| WidgetAutomationTests | WidgetAutomationTests | E | Default | — | — | (附录未收录) |

### TextureGraph(5 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| TextureGraph | TextureGraphEngine | R | PostConfigInit | AssetTools, Continuable, Core, CoreUObject, DeveloperSettings, Engine, Function2, HTTP 等 25 个 | MutableRuntime, Slate, SlateCore, UMG | ../appendix/api/Plugins/TextureGraphEngine.md |
| TextureGraph | TextureGraphInsight | E | Default | Core, CoreUObject, Engine, InputCore, RHI, RenderCore | Continuable, FreeImage, Function2, Slate, SlateCore, TextureGraphEngine, UMG | ../appendix/api/Plugins/TextureGraphInsight.md |
| TextureGraph | TextureGraphInsightEditor | E | Default | Core | AdvancedPreviewScene, Blutility, Continuable, CoreUObject, DeveloperSettings, Engine, InputCore, Projects 等 17 个 | ../appendix/api/Plugins/TextureGraphInsightEditor.md |
| TextureGraph | TextureGraph | R | Default | Core, ImageCore, MutableRuntime, RHI, RenderCore, Renderer, TextureGraphEngine | CoreUObject, Engine, Slate, SlateCore | ../appendix/api/Plugins/TextureGraph.md |
| TextureGraph | TextureGraphEditor | E | PostEngineInit | AdvancedPreviewScene, AssetTools, ContentBrowser, ContentBrowserData, Core, EditorFramework, Engine, KismetWidgets 等 19 个 | ApplicationCore, AssetDefinition, CoreUObject, EditorWidgets, Engine, GraphEditor, ImageWidgets, InputCore 等 11 个 | ../appendix/api/Plugins/TextureGraphEditor.md |

### TraceUtilities(3 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| TraceUtilities | TraceUtilities | R | Default | Core | CoreUObject, Engine, TraceLog | ../appendix/api/Plugins/TraceUtilities.md |
| TraceUtilities | EditorTraceUtilities | EnC | Default | Core | Engine, InputCore, Slate, SlateCore, ToolMenus, TraceAnalysis, TraceInsightsFrontend, TraceLog 等 10 个 | ../appendix/api/Plugins/EditorTraceUtilities.md |
| TraceUtilities | InsightsEditor | EnC | Default | Core, TraceInsights | Engine, InputCore, Slate, SlateCore, ToolMenus, TraceLog | ../appendix/api/Plugins/InsightsEditor.md |

### UbaController(1 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| UbaController | UbaController | E | EarliestPossible | — | Core, DistributedBuildInterface, HTTP, Horde, Json, Projects, RenderCore, Sockets 等 10 个 | ../appendix/api/Plugins/UbaController.md |

### VirtualProduction(265 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| AccumulationDOF | AccumulationDOF | R | PostConfigInit | CinematicCamera, Core, Engine, MovieRenderPipelineCore, Slate, SlateCore | CoreUObject, Engine, ImageWriteQueue, MovieRenderPipelineRenderPasses, Projects, PropertyEditor, RHI, RenderCore 等 9 个 | ../appendix/api/Plugins/AccumulationDOF.md |
| AccumulationDOF | AccumulationDOFEditor | E | Default | — | AccumulationDOF, CinematicCamera, Core, CoreUObject, Engine, InputCore, LevelEditor, RHI 等 14 个 | ../appendix/api/Plugins/AccumulationDOFEditor.md |
| ActorModifier | ActorModifier | R | Default | ActorModifierCore, Core | CoreUObject, Engine, Slate, SlateCore | ../appendix/api/Plugins/ActorModifier.md |
| ActorModifier | ActorModifierEditor | E | Default | Core | ActorModifier, ActorModifierCore, ActorModifierLayout, ClonerEffectorEditor, CoreUObject, Engine, Projects, Slate 等 9 个 | ../appendix/api/Plugins/ActorModifierEditor.md |
| ActorModifier | ActorModifierLayout | R | Default | ActorModifier, ActorModifierCore, Core | CoreUObject, Engine | ../appendix/api/Plugins/ActorModifierLayout.md |
| ActorModifier | ActorModifierRendering | R | Default | ActorModifier, ActorModifierCore, Core | CompositeCore, CoreUObject, Engine | ../appendix/api/Plugins/ActorModifierRendering.md |
| ActorModifierCore | ActorModifierCore | R | Default | Core, CoreUObject, Engine | Engine, Slate, SlateCore, TraceLog, UnrealEd | ../appendix/api/Plugins/ActorModifierCore.md |
| ActorModifierCore | ActorModifierCoreBlueprint | U | Default | BlueprintGraph, Core, CoreUObject, Engine, SlateCore | ActorModifierCore | ../appendix/api/Plugins/ActorModifierCoreBlueprint.md |
| ActorModifierCore | ActorModifierCoreEditor | E | Default | ActorModifierCore, Core | ActorModifierCore, ActorModifierCoreBlueprint, ApplicationCore, AssetDefinition, CoreUObject, CustomDetailsView, EditorSubsystem, Engine 等 20 个 | ../appendix/api/Plugins/ActorModifierCoreEditor.md |
| Avalanche | Avalanche | R+P | Default | AvalancheAttribute, AvalancheCore, AvalancheRemoteControl, AvalancheSceneTree, AvalancheSequence, AvalancheTag, AvalancheTransition, CinematicCamera 等 18 个 | ActorModifierCore, ApplicationCore, AvalancheCamera, AvalancheOutliner, AvalancheRemoteControl, CinematicCamera, CoreUObject, DynamicMaterial 等 33 个 | ../appendix/api/Plugins/Avalanche.md |
| Avalanche | AvalancheCore | R | Default | Core, CoreUObject, Engine | — | ../appendix/api/Plugins/AvalancheCore.md |
| Avalanche | AvalancheCamera | R | Default | ActorModifierCore, AvalancheTransition, Core, StateTreeModule | CoreUObject, Engine, SlateCore | ../appendix/api/Plugins/AvalancheCamera.md |
| Avalanche | AvalancheEditor | E | Default | Avalanche, Core, CoreUObject, Engine | ActorModifier, ActorModifierCore, ActorModifierCoreEditor, AdvancedPreviewScene, AdvancedRenamer, AppFramework, ApplicationCore, AssetRegistry 等 94 个 | ../appendix/api/Plugins/AvalancheEditor.md |
| Avalanche | AvalancheEditorCore | E | Default | AvalancheCore, Core, InputCore, Slate, SlateCore, UnrealEd | ApplicationCore, CoreUObject, EditorFramework, Engine, LevelEditor, Projects, StatusBar, ToolMenus 等 11 个 | ../appendix/api/Plugins/AvalancheEditorCore.md |
| Avalanche | AvalancheComponentVisualizers | E | Default | ComponentVisualizers, Core, CoreUObject, Engine, SlateCore | Avalanche, AvalancheViewport, CustomDetailsView, DeveloperSettings, EditorFramework, GeometryFramework, Slate, UnrealEd | ../appendix/api/Plugins/AvalancheComponentVisualizers.md |
| Avalanche | AvalancheEffectors | R+P | Default | — | Avalanche, AvalancheCore, AvalancheOutliner, AvalancheSceneTree, ClonerEffector, Core, CoreUObject, Engine 等 9 个 | ../appendix/api/Plugins/AvalancheEffectors.md |
| Avalanche | AvalancheEffectorsEditor | E | Default | — | AvalancheComponentVisualizers, AvalancheCore, AvalancheEffectors, AvalancheInteractiveTools, AvalancheOutliner, AvalancheShapes, ClonerEffector, ClonerEffectorEditor 等 18 个 | ../appendix/api/Plugins/AvalancheEffectorsEditor.md |
| Avalanche | AvalancheInteractiveTools | E | Default | Core, CoreUObject, Engine, Slate, SlateCore | Avalanche, AvalancheInteractiveToolsRuntime, AvalancheText, AvalancheViewport, DeveloperSettings, EditorFramework, EditorInteractiveToolsFramework, InputCore 等 15 个 | ../appendix/api/Plugins/AvalancheInteractiveTools.md |
| Avalanche | AvalancheInteractiveToolsRuntime | R | Default | Core, CoreUObject | — | ../appendix/api/Plugins/AvalancheInteractiveToolsRuntime.md |
| Avalanche | AvalancheLevelViewport | E | Default | AvalancheViewport, Core, CoreUObject, Engine, Slate, SlateCore, UnrealEd | ApplicationCore, Avalanche, AvalancheComponentVisualizers, AvalancheEditorCore, AvalancheFunctionalTest, AvalancheInteractiveTools, AvalancheViewport, CinematicCamera 等 18 个 | ../appendix/api/Plugins/AvalancheLevelViewport.md |
| Avalanche | AvalancheOutliner | E | Default | AvalancheCore, Core, CoreUObject, DeveloperSettings, Engine, Slate, SlateCore, UnrealEd | AvalancheEditorCore, AvalancheSceneTree, BlueprintGraph, EditorWidgets, InputCore, Projects, ToolMenus, ToolWidgets 等 9 个 | ../appendix/api/Plugins/AvalancheOutliner.md |
| Avalanche | AvalancheMask | R | Default | AvalancheMaterial, AvalancheModifiers, AvalancheShapes, Core, CoreUObject, GeometryMask | ActorModifier, ActorModifierCore, AssetRegistry, AssetTools, Avalanche, AvalancheCore, AvalancheText, DeveloperSettings 等 18 个 | ../appendix/api/Plugins/AvalancheMask.md |
| Avalanche | AvalancheMaskEditor | E | Default | Core | ActorModifierCore, Avalanche, AvalancheEditorCore, AvalancheMask, AvalancheModifiers, AvalancheShapes, CoreUObject, DynamicMaterialEditor 等 23 个 | ../appendix/api/Plugins/AvalancheMaskEditor.md |
| Avalanche | AvalancheMedia | R | PostConfigInit | Avalanche, AvalancheSequence, AvalancheTag, AvalancheTransition, Core, CoreUObject, DeveloperSettings, Engine 等 11 个 | ApplicationCore, AssetRegistry, AvalancheCore, AvalancheMaterial, AvalancheRemoteControl, GraphEditor, HTTPServer, HeadMountedDisplay 等 24 个 | ../appendix/api/Plugins/AvalancheMedia.md |
| Avalanche | AvalancheMediaEditor | E | Default | AvalancheCore, AvalancheMedia, Core, CoreUObject, DeveloperSettings, Engine, MediaIOCore | ApplicationCore, AssetDefinition, AssetTools, Avalanche, AvalancheEditorCore, AvalancheRemoteControl, AvalancheTag, ContentBrowser 等 31 个 | ../appendix/api/Plugins/AvalancheMediaEditor.md |
| Avalanche | AvalancheModifiers | R | Default | ActorModifier, ActorModifierCore, ActorModifierLayout, Avalanche, AvalancheSequence, Core, CoreUObject, DynamicMesh 等 10 个 | AssetRegistry, AssetTools, Avalanche, AvalancheOutliner, AvalancheSceneTree, AvalancheShapes, ClonerEffectorMeshBuilder, DynamicMaterial 等 19 个 | ../appendix/api/Plugins/AvalancheModifiers.md |
| Avalanche | AvalancheModifiersEditor | E | Default | AvalancheModifiers, AvalancheOutliner, Core, SlateCore | ActorModifier, ActorModifierCore, ActorModifierCoreEditor, ActorModifierEditor, CoreUObject, Engine, Projects, Slate 等 10 个 | ../appendix/api/Plugins/AvalancheModifiersEditor.md |
| Avalanche | AvalanchePropertyAnimator | R | Default | — | — | (附录未收录) |
| Avalanche | AvalanchePropertyAnimatorEditor | E | Default | — | AvalancheOutliner, Core, CoreUObject, Engine, PropertyAnimator, PropertyAnimatorCore, PropertyAnimatorCoreEditor, Slate 等 9 个 | ../appendix/api/Plugins/AvalanchePropertyAnimatorEditor.md |
| Avalanche | AvalancheRemoteControl | R | Default | Core, CoreUObject, Engine, RemoteControl | RemoteControlComponents, RemoteControlLogic, Slate, SlateCore | ../appendix/api/Plugins/AvalancheRemoteControl.md |
| Avalanche | AvalancheRemoteControlEditor | E | Default | — | AvalancheEditorCore, AvalancheOutliner, AvalancheRemoteControl, Core, CoreUObject, Engine, InputCore, RemoteControl 等 15 个 | ../appendix/api/Plugins/AvalancheRemoteControlEditor.md |
| Avalanche | AvalancheSequence | R | Default | AvalancheTag, AvalancheTransition, Core, CoreUObject, Engine, LevelSequence, MovieScene, MovieSceneTracks | AvalancheCore, BlueprintGraph, Sequencer, StateTreeModule | ../appendix/api/Plugins/AvalancheSequence.md |
| Avalanche | AvalancheSequencer | E | Default | AvalancheSequence, AvalancheTag, Core, CoreUObject, MovieScene, Sequencer, SlateCore, UnrealEd | ApplicationCore, Avalanche, AvalancheCore, AvalancheEditorCore, AvalancheOutliner, AvalancheTransition, AvalancheTransitionEditor, BlueprintGraph 等 36 个 | ../appendix/api/Plugins/AvalancheSequencer.md |
| Avalanche | AvalancheShapes | R+P | Default | Avalanche, AvalancheCore, AvalancheInteractiveToolsRuntime, AvalancheMaterial, Core, CoreUObject, Engine | ActorModifierCore, AvalancheEditorCore, DeveloperSettings, DynamicMaterial, DynamicMaterialEditor, DynamicMesh, GeometryAlgorithms, GeometryCore 等 15 个 | ../appendix/api/Plugins/AvalancheShapes.md |
| Avalanche | AvalancheShapesEditor | E | Default | Core | Avalanche, AvalancheComponentVisualizers, AvalancheEditorCore, AvalancheInteractiveTools, AvalancheLevelViewport, AvalancheShapes, AvalancheViewport, ComponentVisualizers 等 26 个 | ../appendix/api/Plugins/AvalancheShapesEditor.md |
| Avalanche | AvalancheText | R+P | Default | AvalancheCore, AvalancheMaterial, Core, CoreUObject, Engine, SlateCore, Text3D | ActorModifierCore, Avalanche, UnrealEd | ../appendix/api/Plugins/AvalancheText.md |
| Avalanche | AvalancheTextEditor | E | Default | — | Avalanche, AvalancheComponentVisualizers, AvalancheEditorCore, AvalancheInteractiveTools, AvalancheLevelViewport, AvalancheText, ComponentVisualizers, Core 等 20 个 | ../appendix/api/Plugins/AvalancheTextEditor.md |
| Avalanche | AvalancheViewport | E | Default | Avalanche, AvalancheCore, Core, CoreUObject, DeveloperSettings, Engine, SlateCore, UnrealEd | AvalancheEditorCore, AvalancheShapes, InputCore, Json, Projects, SettingsEditor, Slate | ../appendix/api/Plugins/AvalancheViewport.md |
| Avalanche | AvalancheSceneTree | R | Default | Core, CoreUObject | Engine | ../appendix/api/Plugins/AvalancheSceneTree.md |
| Avalanche | AvalancheTransition | R | Default | AvalancheTag, Core, CoreUObject, Engine, StateTreeModule | StateTreeEditorModule, UnrealEd | ../appendix/api/Plugins/AvalancheTransition.md |
| Avalanche | AvalancheTransitionEditor | U | Default | AvalancheTag, Core, CoreUObject, StateTreeEditorModule | ApplicationCore, AssetDefinition, AssetTools, AvalancheCore, AvalancheTransition, DeveloperSettings, EditorStyle, Engine 等 19 个 | ../appendix/api/Plugins/AvalancheTransitionEditor.md |
| Avalanche | AvalancheMRQ | R | Default | AvalancheMedia, Core, MovieRenderPipelineCore, RemoteControl | Avalanche, AvalancheRemoteControl, CoreUObject, Engine, Slate, SlateCore | ../appendix/api/Plugins/AvalancheMRQ.md |
| Avalanche | AvalancheMRQEditor | E | Default | — | Avalanche, AvalancheMRQ, AvalancheMedia, AvalancheMediaEditor, AvalancheSequence, AvalancheSequencer, Core, CoreUObject 等 17 个 | ../appendix/api/Plugins/AvalancheMRQEditor.md |
| Avalanche | AvalancheSVGEditor | E | Default | — | ActorModifierCore, AvalancheInteractiveTools, AvalancheModifiers, Core, CoreUObject, Engine, InteractiveToolsFramework, SVGImporter 等 12 个 | ../appendix/api/Plugins/AvalancheSVGEditor.md |
| Avalanche | AvalancheTag | R | Default | Core, CoreUObject, Engine | — | ../appendix/api/Plugins/AvalancheTag.md |
| Avalanche | AvalancheTagEditor | E | Default | — | AssetDefinition, AvalancheTag, Core, CoreUObject, Engine, InputCore, PropertyEditor, Slate 等 11 个 | ../appendix/api/Plugins/AvalancheTagEditor.md |
| Avalanche | AvalancheAttribute | R | Default | AvalancheTag, Core, CoreUObject | Engine, Slate, SlateCore | ../appendix/api/Plugins/AvalancheAttribute.md |
| Avalanche | AvalancheAttributeEditor | E | Default | Core | AvalancheAttribute, CoreUObject, Engine, PropertyEditor, Slate, SlateCore, UnrealEd | ../appendix/api/Plugins/AvalancheAttributeEditor.md |
| Avalanche | AvalancheSceneRig | R | Default | Core, CoreUObject | AssetRegistry, Engine | ../appendix/api/Plugins/AvalancheSceneRig.md |
| Avalanche | AvalancheSceneRigEditor | E | Default | Core, CoreUObject | AssetRegistry, AssetTools, Avalanche, AvalancheOutliner, AvalancheSceneRig, Engine, PropertyEditor, Slate 等 11 个 | ../appendix/api/Plugins/AvalancheSceneRigEditor.md |
| Avalanche | AvalancheMaterial | R | Default | AvalancheCore, Core, CoreUObject, DeveloperSettings, Engine | RHI, RenderCore | ../appendix/api/Plugins/AvalancheMaterial.md |
| Avalanche | AvalancheFunctionalTest | DT | Default | Avalanche, Core, CoreUObject, Engine, FunctionalTesting, Niagara, RenderCore | LevelEditor, Slate, SlateCore, UnrealEd | ../appendix/api/Plugins/AvalancheFunctionalTest.md |
| AvalancheDataLink | AvalancheDataLink | R | Default | AvalancheRemoteControl, Core, CoreUObject, DataLink | Avalanche, DataLinkJson, Engine, Json, JsonUtilities, PropertyBindingUtils, RemoteControl, RemoteControlLogic | ../appendix/api/Plugins/AvalancheDataLink.md |
| AvalancheDataLink | AvalancheDataLinkEditor | E | Default | — | AvalancheDataLink, AvalancheInteractiveTools, Core, CoreUObject, Engine, InteractiveToolsFramework, PropertyEditor, Slate 等 10 个 | ../appendix/api/Plugins/AvalancheDataLinkEditor.md |
| AvalancheSceneState | AvalancheSceneState | R | Default | AvalancheRemoteControl, AvalancheSequence, AvalancheTag, Core, CoreUObject, SceneState, SceneStateBinding, SceneStateGameplay 等 9 个 | Avalanche, Engine, PropertyBindingUtils, RemoteControl, RemoteControlLogic, SceneStateBlueprint, SceneStateBlueprintEditor, SceneStateEvent | ../appendix/api/Plugins/AvalancheSceneState.md |
| AvalancheSceneState | AvalancheSceneStateBlueprint | U | Default | Core, Engine, PropertyBindingUtils, SceneStateBlueprint | AvalancheSceneState, CoreUObject, SceneState | ../appendix/api/Plugins/AvalancheSceneStateBlueprint.md |
| AvalancheSceneState | AvalancheSceneStateEditor | E | Default | — | AvalancheEditorCore, AvalancheSceneState, AvalancheSceneStateBlueprint, BlueprintGraph, Core, CoreUObject, Engine, KismetWidgets 等 19 个 | ../appendix/api/Plugins/AvalancheSceneStateEditor.md |
| CameraCalibration | CameraCalibrationEditor | E | Default | — | AppFramework, ApplicationCore, AssetDefinition, AssetRegistry, AssetTools, CameraCalibrationCore, CinematicCamera, ContentBrowserData 等 37 个 | ../appendix/api/Plugins/CameraCalibrationEditor.md |
| CameraCalibration | TrackingAlignment | R | Default | Core, CoreUObject, Engine, OpenCV, OpenCVHelper | — | ../appendix/api/Plugins/TrackingAlignment.md |
| CameraCalibration | TrackingAlignmentEditor | E | Default | — | — | (附录未收录) |
| CameraCalibrationCore | CameraCalibrationCore | R | PostConfigInit | CinematicCamera, Core, CoreUObject, DeveloperSettings, Engine, GameplayCameras, ProceduralMeshComponent, RHI 等 11 个 | Json, LiveLinkInterface, Projects, Renderer, UnrealEd | ../appendix/api/Plugins/CameraCalibrationCore.md |
| CameraCalibrationCore | CameraCalibrationCoreEditor | E | Default | — | CameraCalibrationCore, Core, CoreUObject, Engine, PlacementMode, PropertyEditor, Slate, SlateCore 等 9 个 | ../appendix/api/Plugins/CameraCalibrationCoreEditor.md |
| CameraCalibrationML | CameraCalibrationML | E | Default | — | — | (附录未收录) |
| CaptureData | CaptureDataCore | R | Default | Media | CameraCalibrationCore, CaptureDataUtils, Core, CoreUObject, Engine, ImgMedia, MeshDescription, StaticMeshDescription | ../appendix/api/Plugins/CaptureDataCore.md |
| CaptureData | CaptureDataEditor | E | Default | — | AssetDefinition, CaptureDataCore, Core, CoreUObject, EditorScriptingUtilities, Engine, InputCore, PropertyEditor 等 11 个 | ../appendix/api/Plugins/CaptureDataEditor.md |
| CaptureData | CaptureDataUtils | R | Default | Core, CoreUObject, Engine, ImgMedia | EditorScriptingUtilities, UnrealEd | ../appendix/api/Plugins/CaptureDataUtils.md |
| CaptureManagerApp | CaptureManagerEditor | E | Default | Core, CoreUObject, EditorStyle | CaptureDataConverter, CaptureDataCore, CaptureManagerSettings, CaptureManagerStyle, CaptureManagerTakeMetadata, CaptureManagerUnrealEndpoint, CaptureUtils, ContentBrowser 等 24 个 | ../appendix/api/Plugins/CaptureManagerEditor.md |
| CaptureManagerApp | CaptureManagerUnrealEndpoint | E | Default | Core, CoreUObject | CaptureManagerSettings, CaptureManagerTakeMetadata, CaptureUtils, Engine, LiveLinkHubCaptureMessaging, MessagingCommon | ../appendix/api/Plugins/CaptureManagerUnrealEndpoint.md |
| CaptureManagerApp | CaptureManagerSettings | E | Default | Core, CoreUObject | CaptureDataConverter, CaptureUtils, Engine, NamingTokens, PropertyEditor, Settings, Slate, SlateCore 等 9 个 | ../appendix/api/Plugins/CaptureManagerSettings.md |
| CaptureManagerApp | LiveLinkCapabilities | E | Default | CaptureDataConverter, CaptureManagerTakeMetadata, CaptureManagerUnrealEndpoint, CaptureUtils, Core | CaptureManagerMediaRW, CoreUObject, Engine, Json, LiveLinkDevice, LiveLinkHubCaptureMessaging, Media, MediaAssets 等 13 个 | ../appendix/api/Plugins/LiveLinkCapabilities.md |
| CaptureManagerApp | IngestLiveLinkDevice | E | Default | CaptureUtils, Core, MediaAssets | CaptureDataConverter, CaptureDataUtils, CaptureManagerMediaRW, CaptureManagerSettings, CaptureManagerTakeMetadata, CaptureManagerUnrealEndpoint, CaptureProtocolStack, CaptureUtils 等 23 个 | ../appendix/api/Plugins/IngestLiveLinkDevice.md |
| CaptureManagerCore | CaptureUtils | R | PreDefault | Core, Engine, Networking, Sockets | — | ../appendix/api/Plugins/CaptureUtils.md |
| CaptureManagerCore | CaptureProtocolStack | R | Default | CaptureUtils, Core | CoreUObject, Engine, Json, JsonUtilities, Networking, Sockets | ../appendix/api/Plugins/CaptureProtocolStack.md |
| CaptureManagerCore | CaptureManagerCPSClient | R | Default | CaptureProtocolStack, CaptureUtils, Core | — | ../appendix/api/Plugins/CaptureManagerCPSClient.md |
| CaptureManagerCore | CaptureManagerPipeline | E | Default | CaptureManagerTakeMetadata | CaptureUtils, ControlFlows, Core, CoreUObject, ImageWrapper, Projects | ../appendix/api/Plugins/CaptureManagerPipeline.md |
| CaptureManagerCore | CaptureManagerMediaRW | E | Default | Core, Media | CaptureDataUtils, DataIngestCore, Engine, ImageCore, ImageWriteQueue, Json, JsonUtilities, OodleDataCompression 等 9 个 | ../appendix/api/Plugins/CaptureManagerMediaRW.md |
| CaptureManagerCore | CaptureDataConverter | E | Default | CaptureManagerMediaRW, CaptureManagerPipeline, CaptureManagerTakeMetadata, CaptureUtils, Core | CaptureDataUtils, CoreUObject, DataIngestCore, Engine, ImageWrapper, Json, Media, NamingTokens | ../appendix/api/Plugins/CaptureDataConverter.md |
| CaptureManagerCore | DataIngestCore | E | Default | CaptureUtils, Core, Engine, Media | CaptureDataCore, CoreUObject, InputCore, Json, PropertyEditor | ../appendix/api/Plugins/DataIngestCore.md |
| CaptureManagerCore | LiveLinkHubCaptureMessaging | E | Default | CaptureProtocolStack, CaptureUtils, Core, CoreUObject, Engine | MessagingCommon | ../appendix/api/Plugins/LiveLinkHubCaptureMessaging.md |
| CaptureManagerCore | CaptureManagerStyle | E | Default | Core, EditorStyle | Projects, Slate, SlateCore, UnrealEd | ../appendix/api/Plugins/CaptureManagerStyle.md |
| CaptureManagerCore | CaptureManagerTakeMetadata | E | Default | ImageCore | Core, Projects, RapidJSON | ../appendix/api/Plugins/CaptureManagerTakeMetadata.md |
| CaptureManagerCore | CaptureMetadataExtraction | E | Default | CaptureManagerTakeMetadata, Core, CoreUObject, Engine | CaptureDataCore, CaptureDataUtils, CaptureManagerMediaRW, CaptureUtils, DataIngestCore, ElectraPlayerPlugin, Json, Media 等 9 个 | ../appendix/api/Plugins/CaptureMetadataExtraction.md |
| CaptureManagerDevices | MonoVideoIngestDevice | E | Default | CaptureUtils, Core | CaptureManagerMediaRW, CaptureManagerSettings, CaptureManagerTakeMetadata, CaptureMetadataExtraction, CoreUObject, Engine, IngestLiveLinkDevice, Json 等 18 个 | ../appendix/api/Plugins/MonoVideoIngestDevice.md |
| CaptureManagerDevices | CPSLiveLinkDevice | E | Default | CaptureManagerCPSClient, CaptureProtocolStack, CaptureUtils, Core | CaptureManagerMediaRW, CaptureManagerSettings, CaptureManagerTakeMetadata, CaptureMetadataExtraction, CoreUObject, DataIngestCore, Engine, IngestLiveLinkDevice 等 19 个 | ../appendix/api/Plugins/CPSLiveLinkDevice.md |
| CaptureManagerDevices | TakeArchiveIngestDevice | E | Default | CaptureUtils, Core | CaptureManagerMediaRW, CaptureManagerSettings, CaptureManagerTakeMetadata, CaptureMetadataExtraction, CoreUObject, DataIngestCore, Engine, IngestLiveLinkDevice 等 18 个 | ../appendix/api/Plugins/TakeArchiveIngestDevice.md |
| CaptureManagerDevices | StereoVideoIngestDevice | E | Default | CaptureUtils, Core | CaptureManagerMediaRW, CaptureManagerSettings, CaptureManagerTakeMetadata, CaptureMetadataExtraction, CoreUObject, DataIngestCore, Engine, IngestLiveLinkDevice 等 19 个 | ../appendix/api/Plugins/StereoVideoIngestDevice.md |
| CaptureManagerDevices | VideoLiveLinkDeviceCommon | E | Default | CaptureManagerTakeMetadata, Core, ImageCore | CaptureManagerMediaRW, CaptureManagerSettings, CaptureUtils, CoreUObject, Engine, Slate, SlateCore, UnrealEd | ../appendix/api/Plugins/VideoLiveLinkDeviceCommon.md |
| CaptureManagerEditor | CaptureManagerEditorSettings | E | Default | CaptureUtils, Core, CoreUObject, Engine | CaptureDataConverter, CaptureManagerStyle, ContentBrowser, ContentBrowserData, DeveloperSettings, LiveLinkHubCaptureMessaging, LiveLinkHubExportServer, LiveLinkHubMessaging 等 16 个 | ../appendix/api/Plugins/CaptureManagerEditorSettings.md |
| CaptureManagerEditor | LiveLinkHubWorkerManager | E | Default | CaptureUtils, Core, CoreUObject, Engine | CaptureDataCore, CaptureDataUtils, CaptureManagerEditorSettings, CaptureManagerTakeMetadata, ContentBrowserData, DataIngestCore, DataIngestCoreEditor, DeveloperSettings 等 14 个 | ../appendix/api/Plugins/LiveLinkHubWorkerManager.md |
| CaptureManagerEditor | LiveLinkHubExportServer | E | Default | CaptureUtils, Core, CoreUObject, Engine | LiveLinkHubCaptureMessaging, Sockets | ../appendix/api/Plugins/LiveLinkHubExportServer.md |
| CaptureManagerEditor | DataIngestCoreEditor | E | Default | CaptureDataCore, CaptureUtils, Core, Engine | AssetDefinition, CameraCalibrationCore, CaptureDataCore, CaptureDataEditor, CaptureManagerEditorSettings, CoreUObject, DataIngestCore, ImgMedia 等 19 个 | ../appendix/api/Plugins/DataIngestCoreEditor.md |
| CaptureManagerEditor | LiveLinkHubDiscoveryEditor | E | Default | — | CaptureUtils, Core, CoreUObject, LiveLinkHubCaptureMessaging, LiveLinkHubExportServer, LiveLinkHubWorkerManager, Messaging, Sockets | ../appendix/api/Plugins/LiveLinkHubDiscoveryEditor.md |
| CaptureManagerEditor | CaptureManagerIngestBlueprint | E | Default | CaptureDataCore, Core, CoreUObject, Engine | CaptureDataConverter, CaptureManagerEditorSettings, CaptureManagerTakeMetadata, CaptureMetadataExtraction, CaptureUtils, DataIngestCore, DataIngestCoreEditor, NamingTokens | ../appendix/api/Plugins/CaptureManagerIngestBlueprint.md |
| CaptureManagerEditor | CaptureManagerDeviceBlueprint | E | Default | Core, CoreUObject, Engine | CaptureManagerCPSClient, CaptureProtocolStack, CaptureUtils | ../appendix/api/Plugins/CaptureManagerDeviceBlueprint.md |
| CinematicAssemblyTools | CineAssemblyTools | R | Default | Engine, LevelSequence, NamingTokens | Core, CoreUObject, Json, JsonUtilities, MovieScene, MovieSceneTools, MovieSceneTracks, SlateCore 等 9 个 | ../appendix/api/Plugins/CineAssemblyTools.md |
| CinematicAssemblyTools | CineAssemblyToolsEditor | E | Default | — | ApplicationCore, AssetDefinition, AssetRegistry, AssetTools, CineAssemblyTools, CinematicCamera, ClassViewer, ContentBrowser 等 45 个 | ../appendix/api/Plugins/CineAssemblyToolsEditor.md |
| ClonerEffector | ClonerEffector | R | Default | ClonerEffectorMeshBuilder, Core, CoreUObject, Engine, Niagara | DeveloperSettings, GeometryCore, GeometryFramework, GeometryScriptingCore, NiagaraCore, Slate, SlateCore, UnrealEd | ../appendix/api/Plugins/ClonerEffector.md |
| ClonerEffector | ClonerEffectorEditor | E | Default | Core, CoreUObject, EditorSubsystem, Engine, PropertyEditor, UnrealEd | ClonerEffector, InputCore, MovieScene, Niagara, NiagaraEditor, NiagaraSimCaching, Projects, Sequencer 等 11 个 | ../appendix/api/Plugins/ClonerEffectorEditor.md |
| ClonerEffector | ClonerEffectorMeshBuilder | R | Default | Core | CoreUObject, DynamicMesh, Engine, GeometryCore, GeometryFramework, GeometryScriptingCore, MeshConversion, MeshDescription 等 13 个 | ../appendix/api/Plugins/ClonerEffectorMeshBuilder.md |
| CompositePlane | CompositePlane | E | PostEngineInit | — | Core, CoreUObject, EditorFramework, Engine, PlacementMode, Projects, Slate, SlateCore 等 9 个 | ../appendix/api/Plugins/CompositePlane.md |
| CustomDetailsView | CustomDetailsView | E | PostDefault | Core, CoreUObject, InputCore, Slate, SlateCore | Engine, PropertyEditor, ToolMenus, UnrealEd | ../appendix/api/Plugins/CustomDetailsView.md |
| DataCharts | DataCharts | R | Default | — | Core, CoreUObject, Engine, Projects, Slate, SlateCore | ../appendix/api/Plugins/DataCharts.md |
| DataCharts | DataChartsEditor | E | PostEngineInit | — | Core, CoreUObject, EditorFramework, Engine, PlacementMode, Projects, Slate, SlateCore 等 9 个 | ../appendix/api/Plugins/DataChartsEditor.md |
| DataLink | DataLink | R | Default | Core, CoreUObject | Engine | ../appendix/api/Plugins/DataLink.md |
| DataLink | DataLinkEdGraph | U | Default | Core, CoreUObject, DataLink, Engine | BlueprintGraph, KismetCompiler, UnrealEd | ../appendix/api/Plugins/DataLinkEdGraph.md |
| DataLink | DataLinkEditor | E | Default | Core, CoreUObject | ApplicationCore, AssetDefinition, DataLink, DataLinkEdGraph, Engine, GraphEditor, PropertyEditor, Slate 等 12 个 | ../appendix/api/Plugins/DataLinkEditor.md |
| DataLink | DataLinkHttp | R | Default | Core, CoreUObject, DataLink | HTTP | ../appendix/api/Plugins/DataLinkHttp.md |
| DataLink | DataLinkJson | R | Default | Core, CoreUObject, DataLink | Engine, Json, JsonUtilities | ../appendix/api/Plugins/DataLinkJson.md |
| DataLink | DataLinkJsonEditor | E | Default | Json | AssetTools, BlueprintGraph, ContentBrowser, Core, CoreUObject, DataLinkEditor, Engine, JsonUtilities 等 12 个 | ../appendix/api/Plugins/DataLinkJsonEditor.md |
| DataLink | DataLinkDataTable | R | Default | Core, CoreUObject, DataLink, Engine | — | ../appendix/api/Plugins/DataLinkDataTable.md |
| DataLink | DataLinkWebSocket | R | Default | Core, CoreUObject, DataLink, Engine | WebSockets | ../appendix/api/Plugins/DataLinkWebSocket.md |
| DataLinkOAuth | DataLinkOAuth | R | Default | Core, CoreUObject, DataLink, DataLinkHttp | Engine, HTTP, HTTPServer, Json, Sockets | ../appendix/api/Plugins/DataLinkOAuth.md |
| DataLinkOAuth | DataLinkOAuthEditor | E | Default | — | AssetDefinition, AssetTools, ClassViewer, Core, CoreUObject, DataLinkOAuth, Engine, UnrealEd | ../appendix/api/Plugins/DataLinkOAuthEditor.md |
| DatasmithMVR | DatasmithMVRTranslator | E | Default | — | AssetRegistry, Core, CoreUObject, DMXEditor, DMXRuntime, DatasmithContent, DatasmithCore, DatasmithNativeTranslator 等 11 个 | ../appendix/api/Plugins/DatasmithMVRTranslator.md |
| DMXControlConsole | DMXControlConsole | R | Default | Core | CoreUObject, DMXGDTF, DMXProtocol, DMXRuntime, Engine | ../appendix/api/Plugins/DMXControlConsole.md |
| DMXControlConsole | DMXControlConsoleEditor | E | Default | Core | AppFramework, AssetDefinition, AssetRegistry, ContentBrowser, CoreUObject, DMXControlConsole, DMXEditor, DMXProtocol 等 20 个 | ../appendix/api/Plugins/DMXControlConsoleEditor.md |
| DMXDisplayCluster | DMXDisplayCluster | R | Default | — | Core, CoreUObject, DMXProtocol, DMXRuntime, DisplayCluster, Engine | ../appendix/api/Plugins/DMXDisplayCluster.md |
| DMXDisplayCluster | DMXDisplayClusterLightCard | R | PostConfigInit | DMXProtocol, DMXRuntime, DisplayCluster, DisplayClusterLightCardExtender | Core, CoreUObject, Engine | ../appendix/api/Plugins/DMXDisplayClusterLightCard.md |
| DMXEngine | DMXBlueprintGraph | U | Default | Core, DMXProtocol, DMXRuntime | ApplicationCore, AssetRegistry, AssetTools, BlueprintGraph, CoreUObject, DMXEditor, EditorFramework, Engine 等 19 个 | ../appendix/api/Plugins/DMXBlueprintGraph.md |
| DMXEngine | DMXEditor | E | Default | Core, DMXProtocol, DMXProtocolEditor, DMXRuntime, Sequencer, ToolMenus | ApplicationCore, AssetDefinition, AssetRegistry, AssetTools, ContentBrowser, CoreUObject, DMXGDTF, DMXZip 等 32 个 | ../appendix/api/Plugins/DMXEditor.md |
| DMXEngine | DMXRuntime | R | Default | Core, CoreUObject, DMXGDTF, DMXProtocol, DatasmithContent, Engine, JsonUtilities | AssetRegistry, DMXFixtureActorInterface, Json, MovieScene, Projects, UnrealEd, XmlParser | ../appendix/api/Plugins/DMXRuntime.md |
| DMXFixtures | DMXFixtures | R | Default | Core, CoreUObject, DMXFixtureActorInterface, DMXProtocol, DMXRuntime, Engine, ProceduralMeshComponent, RHI 等 9 个 | — | ../appendix/api/Plugins/DMXFixtures.md |
| DMXGDTF | DMXGDTF | R | Default | Core, CoreUObject | DMXZip, Engine, XmlParser | ../appendix/api/Plugins/DMXGDTF.md |
| DMXGDTF | DMXGDTFTests | E | Default | — | Core, CoreUObject, DMXGDTF, DMXZip, DesktopPlatform, Projects, Slate, SlateCore 等 9 个 | ../appendix/api/Plugins/DMXGDTFTests.md |
| DMXGDTF | DMXZip | R | Default | Core | — | ../appendix/api/Plugins/DMXZip.md |
| DMXModularFeatures | DMXFixtureActorInterface | R | Default | Core, CoreUObject | — | ../appendix/api/Plugins/DMXFixtureActorInterface.md |
| DMXPixelMapping | DMXPixelMappingCore | R | Default | Core | Core, CoreUObject, DMXProtocol, DMXRuntime | ../appendix/api/Plugins/DMXPixelMappingCore.md |
| DMXPixelMapping | DMXPixelMappingRuntime | R | Default | Core, CoreUObject, DMXPixelMappingRenderer, DMXRuntime, RHI | DMXPixelMappingCore, DMXPixelMappingEditorWidgets, DMXProtocol, DMXRuntime, Engine, Slate, SlateCore, UMG 等 9 个 | ../appendix/api/Plugins/DMXPixelMappingRuntime.md |
| DMXPixelMapping | DMXPixelMappingEditor | E | Default | — | AppFramework, ApplicationCore, AssetDefinition, Core, CoreUObject, DMXEditor, DMXPixelMappingBlueprintGraph, DMXPixelMappingCore 等 25 个 | ../appendix/api/Plugins/DMXPixelMappingEditor.md |
| DMXPixelMapping | DMXPixelMappingEditorWidgets | E | Default | Core, CoreUObject, Slate, SlateCore | Core, DMXPixelMappingCore, DMXProtocol, DMXRuntime, Slate, SlateCore | ../appendix/api/Plugins/DMXPixelMappingEditorWidgets.md |
| DMXPixelMapping | DMXPixelMappingBlueprintGraph | U | Default | BlueprintGraph, Core, CoreUObject | BlueprintGraph, Core, CoreUObject, DMXPixelMappingRuntime, Engine, GraphEditor, InputCore, KismetCompiler 等 11 个 | ../appendix/api/Plugins/DMXPixelMappingBlueprintGraph.md |
| DMXPixelMapping | DMXPixelMappingRenderer | R | PostConfigInit | Core, CoreUObject | Core, CoreUObject, DMXRuntime, Engine, Projects, RHI, RenderCore, Slate 等 10 个 | ../appendix/api/Plugins/DMXPixelMappingRenderer.md |
| DMXProtocol | DMXProtocol | R | PreDefault | Core, Projects | CoreUObject, Engine, InputCore, Json, Networking, Serialization, Slate, SlateCore 等 9 个 | ../appendix/api/Plugins/DMXProtocol.md |
| DMXProtocol | DMXProtocolArtNet | R | PreDefault | Core, DMXProtocol | CoreUObject, Engine, Json, Networking, Sockets | ../appendix/api/Plugins/DMXProtocolArtNet.md |
| DMXProtocol | DMXProtocolSACN | R | PreDefault | — | — | (附录未收录) |
| DMXProtocol | DMXProtocolEditor | E | Default | Core, DMXProtocol, Networking, PropertyEditor, Sockets | CoreUObject, Engine, InputCore, Projects, Slate, SlateCore, TimeManagement, UnrealEd | ../appendix/api/Plugins/DMXProtocolEditor.md |
| DMXProtocol | DMXProtocolBlueprintGraph | U | Default | Core, DMXProtocol | ApplicationCore, AssetRegistry, AssetTools, BlueprintGraph, CoreUObject, DMXProtocolEditor, Engine, GraphEditor 等 18 个 | ../appendix/api/Plugins/DMXProtocolBlueprintGraph.md |
| DynamicMaterial | DynamicMaterial | R+P | Default | Core, CoreUObject, DynamicMaterialTextureSet, Slate, SlateCore, UMG | Engine, Json, JsonUtilities, RenderCore, UnrealEd | ../appendix/api/Plugins/DynamicMaterial.md |
| DynamicMaterial | DynamicMaterialTextureSet | R+P | Default | CoreUObject, Engine | Core | ../appendix/api/Plugins/DynamicMaterialTextureSet.md |
| DynamicMaterial | DynamicMaterialEditor | E | Default | Core, CoreUObject, DynamicMaterial, Engine, MaterialEditor | AdvancedPreviewScene, AppFramework, ApplicationCore, AssetDefinition, ContentBrowser, ContentBrowserData, CustomDetailsView, DeveloperSettings 等 29 个 | ../appendix/api/Plugins/DynamicMaterialEditor.md |
| DynamicMaterial | DynamicMaterialTextureSetEditor | E | Default | CoreUObject, UnrealEd | AssetDefinition, Core, DeveloperSettings, DynamicMaterialTextureSet, EditorWidgets, Engine, InputCore, PropertyEditor 等 10 个 | ../appendix/api/Plugins/DynamicMaterialTextureSetEditor.md |
| DynamicMaterial | DynamicMaterialShaders | R | PostConfigInit | Core, CoreUObject, RenderCore | Engine, Projects, RHI, Renderer | ../appendix/api/Plugins/DynamicMaterialShaders.md |
| EpicStageApp | EpicStageApp | R | Default | Core, CoreUObject, Serialization | DeveloperSettings, DiscoveryBeaconReceiver, DisplayCluster, DisplayClusterLightCardEditor, DisplayClusterLightCardEditorShaders, DisplayClusterLightCardExtender, DisplayClusterScenePreview, Engine 等 16 个 | ../appendix/api/Plugins/EpicStageApp.md |
| GeometryMask | GeometryMask | R | PostConfigInit | Core, CoreUObject, Engine | DeveloperSettings, GeometryCore, GeometryFramework, LevelEditor, Projects, RHI, RenderCore, Renderer 等 9 个 | ../appendix/api/Plugins/GeometryMask.md |
| GeometryMask | GeometryMaskEditor | E | Default | CoreUObject, GeometryMask, SlateCore | Core, Engine, InputCore, Slate, UnrealEd, WorkspaceMenuStructure | ../appendix/api/Plugins/GeometryMaskEditor.md |
| ICVFXTesting | ICVFXTesting | R | Default | Core, CoreUObject, Engine, Gauntlet | CinematicCamera, DisplayCluster, Engine, LiveLink, LiveLinkComponents, LiveLinkInterface, RenderCore | ../appendix/api/Plugins/ICVFXTesting.md |
| LensComponent | LensComponent | R | Default | LiveLinkComponents, LiveLinkInterface | CameraCalibrationCore, CinematicCamera, Core, CoreUObject, Engine | ../appendix/api/Plugins/LensComponent.md |
| LensComponent | LensComponentEditor | E | Default | — | CameraCalibrationCore, CameraCalibrationCoreEditor, Core, CoreUObject, Engine, LensComponent, LevelSequence, MovieScene 等 14 个 | ../appendix/api/Plugins/LensComponentEditor.md |
| LevelSnapshots | LevelSnapshots | U | Default | Core, TraceLog | Core, CoreUObject, Engine, Landscape, LevelSnapshotFilters, Projects, Settings, UnrealEd | ../appendix/api/Plugins/LevelSnapshots.md |
| LevelSnapshots | LevelSnapshotFilters | U | Default | Core | CoreUObject, Engine | ../appendix/api/Plugins/LevelSnapshotFilters.md |
| LevelSnapshots | LevelSnapshotsEditor | U | Default | Core | ApplicationCore, AssetDefinition, AssetRegistry, AssetTools, BlueprintGraph, ContentBrowser, CoreUObject, EditorFramework 等 25 个 | ../appendix/api/Plugins/LevelSnapshotsEditor.md |
| LevelSnapshots | FoliageSupport | U | PostDefault | Core | CoreUObject, Engine, Foliage, FoliageEdit, LevelSnapshots | ../appendix/api/Plugins/FoliageSupport.md |
| LevelSnapshots | nDisplaySupport | U | PostDefault | Core | CoreUObject, Engine, LevelSnapshots | ../appendix/api/Plugins/nDisplaySupport.md |
| LiveLinkCamera | LiveLinkCamera | R | PreDefault | CameraCalibrationCore, CinematicCamera, Core, CoreUObject, Engine, LiveLink, LiveLinkComponents, LiveLinkInterface | LensComponent | ../appendix/api/Plugins/LiveLinkCamera.md |
| LiveLinkCamera | LiveLinkCameraEditor | E | Default | — | CameraCalibrationCore, Core, CoreUObject, DetailCustomizations, LiveLinkCamera, LiveLinkComponents, LiveLinkInterface, PropertyEditor 等 10 个 | ../appendix/api/Plugins/LiveLinkCameraEditor.md |
| LiveLinkCamera | LiveLinkCameraRecording | U | Default | — | CameraCalibrationCore, CinematicCamera, Core, CoreUObject, Engine, LevelSequence, LiveLinkCamera, LiveLinkComponents 等 19 个 | ../appendix/api/Plugins/LiveLinkCameraRecording.md |
| LiveLinkFreeD | LiveLinkFreeD | R | Default | Core, LiveLinkInterface, Messaging, Networking, Sockets, UdpMessaging | CoreUObject, Engine, Slate, SlateCore | ../appendix/api/Plugins/LiveLinkFreeD.md |
| LiveLinkInputDevice | LiveLinkInputDevice | R | Default | Core, LiveLinkInterface | ApplicationCore, CoreUObject, Engine, InputDevice, Slate, SlateCore | ../appendix/api/Plugins/LiveLinkInputDevice.md |
| LiveLinkKiProDevice | LiveLinkKiProDevice | E | Default | Core | CoreUObject, Engine, HTTP, Json, JsonUtilities, LiveLinkDevice, LiveLinkInterface, Networking 等 11 个 | ../appendix/api/Plugins/LiveLinkKiProDevice.md |
| LiveLinkLens | LiveLinkLens | R | Default | CameraCalibrationCore, CinematicCamera, LiveLinkComponents, LiveLinkInterface | Core, CoreUObject, Engine, LensComponent, LiveLinkMovieScene, MovieScene, MovieSceneTracks | ../appendix/api/Plugins/LiveLinkLens.md |
| LiveLinkMasterLockit | LiveLinkMasterLockit | R | Default | LiveLinkInterface | Core, CoreUObject, Json, Networking, Sockets | ../appendix/api/Plugins/LiveLinkMasterLockit.md |
| LiveLinkMasterLockit | LiveLinkMasterLockitEditor | E | Default | — | Core, CoreUObject, LiveLinkMasterLockit, PropertyEditor, Slate, SlateCore | ../appendix/api/Plugins/LiveLinkMasterLockitEditor.md |
| LiveLinkOBSDevice | LiveLinkOBSDevice | E | Default | — | CaptureManagerSettings, CaptureManagerTakeMetadata, CaptureUtils, Core, CoreUObject, Engine, IngestLiveLinkDevice, Json 等 19 个 | ../appendix/api/Plugins/LiveLinkOBSDevice.md |
| LiveLinkOpenTrackIO | LiveLinkOpenTrackIO | R | Default | Core, LiveLinkInterface | ApplicationCore, Cbor, CoreUObject, Engine, Json, JsonUtilities, LiveLinkLens, Networking 等 13 个 | ../appendix/api/Plugins/LiveLinkOpenTrackIO.md |
| LiveLinkPrestonMDR | LiveLinkPrestonMDR | R | Default | LiveLinkInterface | Core, CoreUObject, Json, Networking, Sockets | ../appendix/api/Plugins/LiveLinkPrestonMDR.md |
| LiveLinkPrestonMDR | LiveLinkPrestonMDREditor | E | Default | — | Core, CoreUObject, LiveLinkPrestonMDR, PropertyEditor, Slate, SlateCore | ../appendix/api/Plugins/LiveLinkPrestonMDREditor.md |
| LiveLinkSoundDevice | LiveLinkSoundDevice | E | Default | Core | CoreUObject, Engine, HTTP, Json, JsonUtilities, LiveLinkDevice, LiveLinkInterface, Networking 等 11 个 | ../appendix/api/Plugins/LiveLinkSoundDevice.md |
| LiveLinkVRPN | LiveLinkVRPN | R | Default | Core, LiveLinkInterface, Messaging, Networking, Sockets | CoreUObject, Engine, Slate, SlateCore | ../appendix/api/Plugins/LiveLinkVRPN.md |
| LiveLinkXR | LiveLinkXR | R | Default | Core, LiveLinkInterface | CoreUObject, Engine, HeadMountedDisplay, LiveLinkXROpenXRExt, OpenXRHMD, Slate, SlateCore | ../appendix/api/Plugins/LiveLinkXR.md |
| LiveLinkXR | LiveLinkXROpenXRExt | R | PostConfigInit | Core | CoreUObject, Engine, HeadMountedDisplay, InputCore, OpenXRHMD | ../appendix/api/Plugins/LiveLinkXROpenXRExt.md |
| MultiUserTakes | ConcertTakeRecorder | U | PostEngineInit | Core, CoreUObject | Concert, ConcertSyncClient, ConcertSyncCore, ConcertTransport, EditorStyle, Engine, InputCore, LevelSequence 等 14 个 | ../appendix/api/Plugins/ConcertTakeRecorder.md |
| OperatorStack | OperatorStackEditor | E | Default | Core, CoreUObject | ApplicationCore, CoreUObject, CustomDetailsView, EditorSubsystem, Engine, InputCore, LevelEditor, Projects 等 16 个 | ../appendix/api/Plugins/OperatorStackEditor.md |
| PerformanceCaptureWorkflow | PerformanceCaptureWorkflow | E | Default | CommonUI, Core, PlacementMode | AnimationCore, AssetDefinition, Blutility, CinematicCamera, CoreUObject, DataTableEditor, DeveloperSettings, EditorFramework 等 35 个 | ../appendix/api/Plugins/PerformanceCaptureWorkflow.md |
| PerformanceCaptureWorkflow | PerformanceCaptureWorkflowRuntime | R | Default | Core | CoreUObject, Engine, IKRig, LiveLink, LiveLinkAnimationCore, LiveLinkInterface, PerformanceCaptureCore, Slate 等 9 个 | ../appendix/api/Plugins/PerformanceCaptureWorkflowRuntime.md |
| PropertyAnimator | PropertyAnimator | R | Default | Core, MovieScene, PropertyAnimatorCore | ApplicationCore, AudioSynesthesia, CoreUObject, DeveloperSettings, Engine, Json, MovieSceneTracks, Text3D | ../appendix/api/Plugins/PropertyAnimator.md |
| PropertyAnimator | PropertyAnimatorEditor | E | Default | — | Core, CoreUObject, Engine, MovieScene, MovieSceneTools, Projects, PropertyAnimator, PropertyAnimatorCore 等 15 个 | ../appendix/api/Plugins/PropertyAnimatorEditor.md |
| PropertyAnimatorCore | PropertyAnimatorCore | R | Default | Core, CoreUObject, MovieScene | ApplicationCore, CoreUObject, DeveloperSettings, Engine, Json, UnrealEd | ../appendix/api/Plugins/PropertyAnimatorCore.md |
| PropertyAnimatorCore | PropertyAnimatorCoreEditor | E | Default | Core | ApplicationCore, AssetDefinition, CoreUObject, EditorSubsystem, EditorWidgets, Engine, InputCore, LevelSequence 等 19 个 | ../appendix/api/Plugins/PropertyAnimatorCoreEditor.md |
| RemoteControl | RemoteControl | R | Default | Core, CoreUObject, Engine, RemoteControlCommon | AssetTools, Cbor, DeveloperSettings, Engine, MessageLog, RemoteControlInterception, Serialization, SharedSettingsWidgets 等 9 个 | ../appendix/api/Plugins/RemoteControl.md |
| RemoteControl | RemoteControlLogic | R | Default | Core, CoreUObject | AssetRegistry, Cbor, Engine, HTTP, ImageCore, RHI, RemoteControl, RemoteControlCommon 等 11 个 | ../appendix/api/Plugins/RemoteControlLogic.md |
| RemoteControl | WebRemoteControl | R | Default | Core, CoreUObject, HTTPServer, Serialization | AssetRegistry, DeveloperSettings, Engine, HTTP, ImageWrapper, Networking, RemoteControl, RemoteControlCommon 等 18 个 | ../appendix/api/Plugins/WebRemoteControl.md |
| RemoteControl | RemoteControlCommon | R | Default | PropertyEditor | ApplicationCore, AssetRegistry, AssetTools, BlueprintGraph, Core, CoreUObject, DeveloperSettings, EditorSubsystem 等 16 个 | ../appendix/api/Plugins/RemoteControlCommon.md |
| RemoteControl | RemoteControlUI | E | Default | — | ApplicationCore, AssetDefinition, AssetRegistry, AssetTools, BlueprintGraph, ClassViewer, ContentBrowser, Core 等 38 个 | ../appendix/api/Plugins/RemoteControlUI.md |
| RemoteControl | RemoteControlProtocol | R | Default | Core, CoreUObject | Engine, RemoteControl, RemoteControlCommon | ../appendix/api/Plugins/RemoteControlProtocol.md |
| RemoteControl | RemoteControlProtocolWidgets | E | Default | — | Core, CoreUObject, EditorStyle, EditorSubsystem, EditorWidgets, Engine, GraphEditor, InputCore 等 17 个 | ../appendix/api/Plugins/RemoteControlProtocolWidgets.md |
| RemoteControl | RemoteControlMultiUser | U | PostEngineInit | — | ConcertSyncClient, Core, CoreUObject, RemoteControl | ../appendix/api/Plugins/RemoteControlMultiUser.md |
| RemoteControlInterception | RemoteControlInterception | R | Default | — | Cbor, Core, CoreUObject, Engine, Serialization | ../appendix/api/Plugins/RemoteControlInterception.md |
| RemoteControlProtocolDMX | RemoteControlProtocolDMX | R | Default | Core, CoreUObject, DMXRuntime | DMXProtocol, Engine, RemoteControl, RemoteControlProtocol | ../appendix/api/Plugins/RemoteControlProtocolDMX.md |
| RemoteControlProtocolDMX | RemoteControlProtocolDMXEditor | E | Default | — | Core, CoreUObject, DMXEditor, DMXProtocol, DMXProtocolEditor, DMXRuntime, Engine, InputCore 等 18 个 | ../appendix/api/Plugins/RemoteControlProtocolDMXEditor.md |
| RemoteControlProtocolMIDI | RemoteControlProtocolMIDI | R | Default | Core, CoreUObject, MIDIDevice | InputCore, RemoteControl, RemoteControlProtocol, RemoteControlProtocolWidgets | ../appendix/api/Plugins/RemoteControlProtocolMIDI.md |
| RemoteControlProtocolMIDI | RemoteControlProtocolMIDIEditor | E | Default | Core, CoreUObject, MIDIDevice | Core, CoreUObject, EditorStyle, EditorWidgets, InputCore, PropertyEditor, RemoteControl, RemoteControlProtocol 等 11 个 | ../appendix/api/Plugins/RemoteControlProtocolMIDIEditor.md |
| RemoteControlProtocolOSC | RemoteControlProtocolOSC | R | Default | Core, CoreUObject | InputCore, Networking, OSC, RemoteControl, RemoteControlProtocol, RemoteControlProtocolWidgets, Settings | ../appendix/api/Plugins/RemoteControlProtocolOSC.md |
| RemoteControlWebInterface | RemoteControlWebInterface | R | Default | Core, CoreUObject, Engine, Projects, RemoteControl, Slate, SlateCore, Sockets 等 10 个 | DeveloperSettings, EditorStyle, EditorWidgets, PropertyEditor, RemoteControl, RemoteControlCommon, RemoteControlLogic, RemoteControlUI 等 12 个 | ../appendix/api/Plugins/RemoteControlWebInterface.md |
| RivermaxCore | RivermaxCore | R | Default | Core, CoreUObject, DeveloperSettings, MediaAssets, RHI, RivermaxLib, TimeManagement | D3D12RHI, Engine, Json, Networking, RenderCore, Slate, UnrealEd | ../appendix/api/Plugins/RivermaxCore.md |
| RivermaxCore | RivermaxEditor | E | Default | Core, PropertyEditor, RivermaxCore | CoreUObject, EditorStyle, InputCore, Slate, SlateCore, UnrealEd | ../appendix/api/Plugins/RivermaxEditor.md |
| RivermaxCore | RivermaxRendering | R | PostConfigInit | — | Core, Projects, RHI, RenderCore | ../appendix/api/Plugins/RivermaxRendering.md |
| RivermaxMedia | RivermaxMedia | R | Default | Core, CoreUObject, MediaAssets, MediaIOCore, RivermaxCore, TimeManagement | Engine, OpenColorIO, RHI, RenderCore, RivermaxRendering | ../appendix/api/Plugins/RivermaxMedia.md |
| RivermaxMedia | RivermaxMediaEditor | E | Default | — | AssetDefinition, AssetTools, Core, CoreUObject, DisplayClusterModularFeaturesEditor, EditorStyle, Engine, InputCore 等 18 个 | ../appendix/api/Plugins/RivermaxMediaEditor.md |
| RivermaxMedia | RivermaxMediaFactory | RnC | PostEngineInit | — | — | (附录未收录) |
| RivermaxSync | RivermaxSync | R | Default | DisplayCluster, DisplayClusterMedia, RivermaxCore, StageDataCore | Core, CoreUObject, RivermaxMedia, UnrealEd | ../appendix/api/Plugins/RivermaxSync.md |
| RivermaxSync | RivermaxSyncEditor | E | Default | — | Core, CoreUObject, Engine, RivermaxSync, UnrealEd | ../appendix/api/Plugins/RivermaxSyncEditor.md |
| SceneState | SceneState | R | Default | Core, CoreUObject, Engine, SceneStateBinding, SceneStateEvent | PropertyBindingUtils, StructUtilsEditor | ../appendix/api/Plugins/SceneState.md |
| SceneState | SceneStateBinding | R | Default | Core, CoreUObject, PropertyBindingUtils | BlueprintGraph, Engine | ../appendix/api/Plugins/SceneStateBinding.md |
| SceneState | SceneStateEvent | R | Default | Core, CoreUObject | Engine, Slate, SlateCore | ../appendix/api/Plugins/SceneStateEvent.md |
| SceneState | SceneStateTasks | R | Default | Core, CoreUObject, Engine, SceneState, SceneStateBinding | UnrealEd | ../appendix/api/Plugins/SceneStateTasks.md |
| SceneState | SceneStateGameplay | R | Default | Core, CoreUObject, Engine, SceneState | — | ../appendix/api/Plugins/SceneStateGameplay.md |
| SceneState | SceneStateBlueprint | U | Default | BlueprintGraph, Core, CoreUObject, Engine, PropertyBindingUtils, SceneStateBinding, SceneStateMachineGraph, SlateCore | SceneState, SceneStateEvent, StructUtilsEditor, UnrealEd | ../appendix/api/Plugins/SceneStateBlueprint.md |
| SceneState | SceneStateEventGraph | U | Default | — | BlueprintGraph, Core, CoreUObject, Engine, KismetCompiler, SceneStateEvent, UnrealEd | ../appendix/api/Plugins/SceneStateEventGraph.md |
| SceneState | SceneStateMachineGraph | U | Default | Core, CoreUObject, Engine, SceneState, SceneStateBinding, SceneStateEvent, SceneStateTransitionGraph | BlueprintGraph, GraphEditor, SceneStateEditor, Slate, SlateCore, StructUtilsEditor, ToolMenus, UnrealEd | ../appendix/api/Plugins/SceneStateMachineGraph.md |
| SceneState | SceneStateTransitionGraph | U | Default | BlueprintGraph, Core, CoreUObject, Engine, SceneState | GraphEditor, UnrealEd | ../appendix/api/Plugins/SceneStateTransitionGraph.md |
| SceneState | SceneStateBlueprintEditor | E | Default | Core, CoreUObject, SceneStateEditor, UnrealEd | AssetDefinition, BlueprintGraph, DetailCustomizations, Engine, GraphEditor, InputCore, Kismet, KismetCompiler 等 24 个 | ../appendix/api/Plugins/SceneStateBlueprintEditor.md |
| SceneState | SceneStateEditor | E | Default | Core, CoreUObject, SceneState | Engine | ../appendix/api/Plugins/SceneStateEditor.md |
| SceneState | SceneStateEventEditor | E | Default | — | AssetDefinition, AssetTools, BlueprintGraph, Core, CoreUObject, DetailCustomizations, Engine, GraphEditor 等 16 个 | ../appendix/api/Plugins/SceneStateEventEditor.md |
| SceneState | SceneStateMachineEditor | E | Default | Core, CoreUObject, Engine, SceneStateMachineGraph | GraphEditor, Projects, PropertyEditor, SceneState, SceneStateTransitionGraph, Slate, SlateCore, ToolMenus 等 9 个 | ../appendix/api/Plugins/SceneStateMachineEditor.md |
| SceneState | SceneStateGameplayEditor | E | Default | — | Core, CoreUObject, Engine, LevelEditor, SceneState, SceneStateBlueprint, SceneStateBlueprintEditor, SceneStateGameplay 等 13 个 | ../appendix/api/Plugins/SceneStateGameplayEditor.md |
| SceneStateDataLink | SceneStateDataLink | R | Default | Core, CoreUObject, DataLink, Engine, SceneState, SceneStateBinding | — | ../appendix/api/Plugins/SceneStateDataLink.md |
| SceneStateDataLink | SceneStateDataLinkEditor | E | Default | — | Core, CoreUObject, DataLink, Engine, PropertyEditor, SceneStateBlueprintEditor, SceneStateDataLink | ../appendix/api/Plugins/SceneStateDataLinkEditor.md |
| SequencerPlaylists | SequencerPlaylists | E | Default | Core | ConcertClient, ConcertSyncClient, ConcertSyncCore, CoreUObject, EditorFramework, EditorStyle, EditorSubsystem, Engine 等 23 个 | ../appendix/api/Plugins/SequencerPlaylists.md |
| StageMonitoring | StageMonitor | U | Default | Core, StageDataCore | CoreUObject, Engine, GameplayTags, Json, JsonUtilities, Serialization, StageMonitorCommon, VPRoles 等 9 个 | ../appendix/api/Plugins/StageMonitor.md |
| StageMonitoring | StageMonitorEditor | E | Default | — | Core, CoreUObject, DesktopPlatform, EditorStyle, Engine, GameplayTags, InputCore, Json 等 17 个 | ../appendix/api/Plugins/StageMonitorEditor.md |
| StageMonitoring | StageDataProvider | R | Default | Core | CoreUObject, DeveloperSettings, Engine, GameplayTags, LevelSequence, RHI, RenderCore, StageDataCore 等 13 个 | ../appendix/api/Plugins/StageDataProvider.md |
| StageMonitoring | StageMonitorCommon | R | Default | Core, DeveloperSettings, StageDataCore | CoreUObject, Engine, GameplayTags, VPRoles, VPUtilities | ../appendix/api/Plugins/StageMonitorCommon.md |
| StormSync | StormSyncCore | R | Default | Core | AssetRegistry, CoreUObject, DeveloperSettings, Engine, Projects, Serialization | ../appendix/api/Plugins/StormSyncCore.md |
| StormSync | StormSyncDrives | R | Default | Core | CoreUObject, DeveloperSettings, Engine, MessageLog, Slate, SlateCore, UnrealEd | ../appendix/api/Plugins/StormSyncDrives.md |
| StormSync | StormSyncEditor | E | Default | Core | AppFramework, AssetTools, ContentBrowserAssetDataSource, ContentBrowserData, CoreUObject, DesktopPlatform, EditorFramework, EditorSubsystem 等 22 个 | ../appendix/api/Plugins/StormSyncEditor.md |
| StormSync | StormSyncTests | U | Default | — | — | (附录未收录) |
| StormSync | StormSyncTransportCore | R | Default | Core, CoreUObject | DeveloperSettings, Engine, MessagingCommon, Networking, Sockets, StormSyncCore | ../appendix/api/Plugins/StormSyncTransportCore.md |
| StormSync | StormSyncTransportClient | R | Default | Core, CoreUObject, StormSyncTransportCore | Engine, Json, JsonUtilities, Networking, Sockets, StormSyncCore | ../appendix/api/Plugins/StormSyncTransportClient.md |
| StormSync | StormSyncTransportServer | R | Default | Core, CoreUObject | Engine, Json, JsonUtilities, Networking, Slate, Sockets, StormSyncCore, StormSyncTransportCore | ../appendix/api/Plugins/StormSyncTransportServer.md |
| StormSync | StormSyncImport | R | Default | — | Core, CoreUObject, EditorFramework, Engine, MessageLog, RenderCore, Slate, SlateCore 等 13 个 | ../appendix/api/Plugins/StormSyncImport.md |
| StormSyncAvalancheBridge | StormSyncAvaBridgeEditor | E | Default | Core | AvalancheMedia, AvalancheMediaEditor, CoreUObject, EditorFramework, Engine, Slate, SlateCore, StormSyncAvaBridge 等 13 个 | ../appendix/api/Plugins/StormSyncAvaBridgeEditor.md |
| StormSyncAvalancheBridge | StormSyncAvaBridge | R | Default | Core | AvalancheMedia, CoreUObject, Engine, Slate, SlateCore, StormSyncCore, StormSyncTransportClient, StormSyncTransportCore 等 9 个 | ../appendix/api/Plugins/StormSyncAvaBridge.md |
| SVGImporter | SVGImporter | R | Default | Core, GeometryFramework, GeometryScriptingEditor, LevelEditor, UnrealEd | Core, CoreUObject, DeveloperSettings, Engine, GeometryAlgorithms, GeometryCore, GeometryFramework, GeometryScriptingCore 等 12 个 | ../appendix/api/Plugins/SVGImporter.md |
| SVGImporter | SVGImporterEditor | E | Default | Core | ApplicationCore, AssetDefinition, AssetTools, ContentBrowser, CoreUObject, DetailCustomizations, EditorFramework, Engine 等 22 个 | ../appendix/api/Plugins/SVGImporterEditor.md |
| Switchboard | SwitchboardCommon | R | Default | Core | — | ../appendix/api/Plugins/SwitchboardCommon.md |
| Switchboard | SwitchboardEditor | E | PostEngineInit | — | AssetRegistry, Blutility, Core, CoreUObject, DesktopPlatform, Engine, InputCore, Json 等 19 个 | ../appendix/api/Plugins/SwitchboardEditor.md |
| Takes | TakesCore | R | PostDefault | AssetRegistry, Engine, LevelSequence, LevelSequenceEditor, MovieScene, MovieSceneTools, MovieSceneTracks, SerializedRecorderInterface 等 9 个 | Core, CoreUObject, EditorFramework, NamingTokens, TakeMovieScene, UnrealEd | ../appendix/api/Plugins/TakesCore.md |
| Takes | TakeTrackRecorders | R | PostDefault | SequenceRuntimeRecorder | Core, CoreUObject, Engine, LevelSequence, MovieScene, MovieSceneTracks, SequenceRecorder, SequenceRuntimeRecorder 等 13 个 | ../appendix/api/Plugins/TakeTrackRecorders.md |
| Takes | TakeRecorderSources | R | PostDefault | Core, TakeTrackRecorders | AudioCaptureEditor, CinematicCamera, Core, CoreUObject, EditorFramework, Engine, InputCore, LevelEditor 等 22 个 | ../appendix/api/Plugins/TakeRecorderSources.md |
| Takes | TakeRecorder | R | PostDefault | EditorSubsystem, Sequencer, SerializedRecorderInterface, TakeTrackRecorders, TraceLog, UMG | Analytics, AppFramework, AssetDefinition, AssetRegistry, ClassViewer, ContentBrowser, Core, CoreUObject 等 30 个 | ../appendix/api/Plugins/TakeRecorder.md |
| Takes | TakeRecorderEditor | U | PostDefault | EditorSubsystem, Sequencer | AppFramework, AssetDefinition, AssetRegistry, ClassViewer, ContentBrowser, Core, CoreUObject, EditorFramework 等 34 个 | ../appendix/api/Plugins/TakeRecorderEditor.md |
| Takes | TakeMovieScene | R | Default | Engine, MovieScene, MovieSceneTracks | Core, CoreUObject | ../appendix/api/Plugins/TakeMovieScene.md |
| Takes | TakeSequencer | E | Default | Engine, MovieScene, MovieSceneTools, MovieSceneTracks, Sequencer, TakeMovieScene | Core, CoreUObject, Slate, SlateCore, UnrealEd | ../appendix/api/Plugins/TakeSequencer.md |
| Takes | CacheTrackRecorder | U | PostDefault | — | — | ../appendix/api/Plugins/CacheTrackRecorder.md |
| Takes | TakeRecorderNamingTokens | R | PostDefault | Engine, NamingTokens, TakeRecorder, TakesCore | Core, CoreUObject, MovieSceneTools, UnrealEd | ../appendix/api/Plugins/TakeRecorderNamingTokens.md |
| Text3D | Text3D | R | Default | Core, CoreUObject, Engine | DeveloperSettings, FreeType2, GeometryAlgorithms, GeometryCore, GeometryFramework, GeometryScriptingCore, HarfBuzz, ICU 等 14 个 | ../appendix/api/Plugins/Text3D.md |
| Text3D | Text3DEditor | E | Default | — | AssetDefinition, Core, CoreUObject, DeveloperSettings, DirectX, EditorFramework, EditorSubsystem, Engine 等 17 个 | ../appendix/api/Plugins/Text3DEditor.md |
| TextureShare | TextureShareCore | R | PostConfigInit | Core | VulkanRHI | ../appendix/api/Plugins/TextureShareCore.md |
| TextureShare | TextureShare | R | PostConfigInit | Core, CoreUObject, Engine, Projects | Core, D3D11RHI, D3D12RHI, Engine, RHI, RHICore, RenderCore, Renderer 等 13 个 | ../appendix/api/Plugins/TextureShare.md |
| TextureShare | TextureShareDisplayCluster | R | PostDefault | Core, CoreUObject, DisplayCluster, DisplayClusterConfiguration, DisplayClusterShaders | Engine, RHI, RenderCore, Renderer, TextureShare, TextureShareCore | ../appendix/api/Plugins/TextureShareDisplayCluster.md |
| TimedDataMonitor | TimedDataMonitor | U | Default | Core, CoreUObject, StageDataCore, TimeManagement | Engine | ../appendix/api/Plugins/TimedDataMonitor.md |
| TimedDataMonitor | TimedDataMonitorEditor | E | Default | — | AssetRegistry, AssetTools, ContentBrowser, Core, CoreUObject, EditorFramework, EditorStyle, EditorWidgets 等 21 个 | ../appendix/api/Plugins/TimedDataMonitorEditor.md |
| ViewportWidgetOverlay | ViewportWidgetOverlay | R | PostConfigInit | Core, CoreUObject, Engine, UMG | ApplicationCore, LevelEditor, Projects, RHI, RenderCore, Renderer, Slate, SlateCore 等 10 个 | ../appendix/api/Plugins/ViewportWidgetOverlay.md |
| VirtualCamera | VCamExtensions | R | Default | CinematicCamera, Core, VCamCore | CoreUObject, DecoupledOutputProvider, Engine, InputCore, Projects, Slate, SlateCore | ../appendix/api/Plugins/VCamExtensions.md |
| VirtualCamera | VCamExtensionsEditor | E | Default | Core | AssetDefinition, AssetTools, CoreUObject, Engine, UnrealEd, VCamCore, VCamCoreEditor, VCamExtensions | ../appendix/api/Plugins/VCamExtensionsEditor.md |
| VirtualCamera | VirtualCamera | R | Default | AssetRegistry, AugmentedReality, CinematicCamera, Core, CoreUObject, Engine, InputCore, LevelSequence 等 19 个 | AdvancedWidgets, AnimationCore, ConcertTakeRecorder, Constraints, EditorFramework, EditorScriptingUtilities, LevelEditor, MediaIOCore 等 14 个 | ../appendix/api/Plugins/VirtualCamera.md |
| VirtualCamera | VirtualCameraEditor | E | PostEngineInit | — | CinematicCamera, Core, CoreUObject, EditorWidgets, Engine, PlacementMode, Settings, TakeRecorderSources 等 12 个 | ../appendix/api/Plugins/VirtualCameraEditor.md |
| VirtualCameraCore | DecoupledOutputProvider | R | Default | VCamCore | Core, CoreUObject, Engine | ../appendix/api/Plugins/DecoupledOutputProvider.md |
| VirtualCameraCore | PixelStreamingVCam | U | PostDefault | InputDevice, MediaIOCore, PixelStreaming, PixelStreamingServers, VCamCore | ApplicationCore, Core, CoreUObject, DecoupledOutputProvider, DiscoveryBeaconReceiver, Engine, InputCore, Json 等 22 个 | ../appendix/api/Plugins/PixelStreamingVCam.md |
| VirtualCameraCore | VCamBlueprintNodes | U | Default | Core | BlueprintGraph, CoreUObject, Engine, InputCore, Slate, SlateCore, VCamCore | ../appendix/api/Plugins/VCamBlueprintNodes.md |
| VirtualCameraCore | VCamCore | R | Default | ApplicationCore, CinematicCamera, Core, DeveloperSettings, EnhancedInput, LiveLinkInterface, RemoteSession, VPUtilities 等 9 个 | Concert, ConcertSyncClient, CoreUObject, EditorFramework, Engine, GameplayTags, InputCore, InputEditor 等 20 个 | ../appendix/api/Plugins/VCamCore.md |
| VirtualCameraCore | VCamCoreEditor | E | Default | Core | AssetDefinition, CinematicCamera, ConcertSyncClient, ConcertSyncCore, CoreUObject, EditorFramework, Engine, EngineAssetDefinitions 等 22 个 | ../appendix/api/Plugins/VCamCoreEditor.md |
| VirtualScouting | VirtualScoutingOpenXR | R | PostConfigInit | Core, CoreUObject, Engine, InputCore, OpenXRHMD, VREditor | — | ../appendix/api/Plugins/VirtualScoutingOpenXR.md |
| VirtualScouting | VirtualScouting | R | Default | CommonUI, Core, XRCreative | ConcertSyncClient, ConcertSyncCore, CoreUObject, DeveloperSettings, Engine, EnhancedInput, HeadMountedDisplay, InputCore 等 21 个 | ../appendix/api/Plugins/VirtualScouting.md |
| VirtualScouting | VirtualScoutingEditor | E | Default | Core, CoreUObject, Engine | EnhancedInput, HeadMountedDisplay, InputCore, InputEditor, InteractiveToolsFramework, LevelEditor, OpenXRHMD, OpenXRInput 等 17 个 | ../appendix/api/Plugins/VirtualScoutingEditor.md |

### Web(2 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| HttpBlueprint | HttpBlueprint | R | Default | Core, CoreUObject, Engine | HTTP, Slate, SlateCore | ../appendix/api/Plugins/HttpBlueprint.md |
| HttpBlueprint | HttpBlueprintGraph | U | Default | — | ApplicationCore, AssetRegistry, AssetTools, BlueprintGraph, Core, CoreUObject, EditorStyle, Engine 等 22 个 | ../appendix/api/Plugins/HttpBlueprintGraph.md |

### WorldMetrics(3 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| WorldMetrics | WorldMetricsCore | R+P | Default | CoreUObject | Core, Engine | ../appendix/api/Plugins/WorldMetricsCore.md |
| WorldMetrics | WorldMetricsTest | R+P | Default | CoreUObject, WorldMetricsCore | Core, Engine | ../appendix/api/Plugins/WorldMetricsTest.md |
| WorldMetrics | CsvMetrics | R+P | Default | CoreUObject, WorldMetricsCore | Core, Engine | ../appendix/api/Plugins/CsvMetrics.md |

### WorldStreamingInsights(1 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| WorldStreamingInsights | WorldStreamingInsights | E+P | Default | — | ApplicationCore, Core, CoreUObject, InputCore, Slate, SlateCore, TraceAnalysis, TraceInsights 等 10 个 | ../appendix/api/Plugins/WorldStreamingInsights.md |

### XGEController(1 个模块声明)

| 插件 | 模块 | 类型 | 阶段 | Public 依赖 | Private 依赖 | 附录文件 |
|---|---|---|---|---|---|---|
| XGEController | XGEController | U | EarliestPossible | — | Core, Engine, RHI, RenderCore, Slate | ../appendix/api/Plugins/XGEController.md |

返回主文件:[24_plugins_catalog_runtime.md](24_plugins_catalog_runtime.md)
