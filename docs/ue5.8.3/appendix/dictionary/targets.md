# Target dictionary (*.Target.cs)

- Target.cs files: 160 (Engine: 137); target classes: 163; parse failures: 0
- by Type: (unset/inherited)=71, Client=2, Editor=11, Game=10, Program=67, Server=2

Every assignment/call of the constructor is listed under the table (`targets.tsv` column *statements*).


## Engine/Plugins/Animation (1)

| target | base | Type | LinkType | BuildEnvironment | LaunchModule | ExtraModuleNames | file |
|---|---|---|---|---|---|---|---|
| `AnimationWarpingRuntimeTestsTarget` | TestTargetRules |  |  |  |  |  | `Engine/Plugins/Animation/AnimationWarping/Tests/AnimationWarpingRuntimeTests.Target.cs` |

## Engine/Plugins/Experimental (17)

| target | base | Type | LinkType | BuildEnvironment | LaunchModule | ExtraModuleNames | file |
|---|---|---|---|---|---|---|---|
| `ChaosRigidPhysicsAsyncTestsTarget` | TestTargetRules |  |  |  |  |  | `Engine/Plugins/Experimental/ChaosRigidPhysicsAsync/Tests/ChaosRigidPhysicsAsyncTests.Target.cs` |
| `GameplayGraphTestsTarget` | TestTargetRules |  |  |  |  |  | `Engine/Plugins/Experimental/GameplayGraph/Tests/GameplayGraphTests.Target.cs` |
| `GlobalConfigurationDataTestsTarget` | TestTargetRules |  |  |  |  |  | `Engine/Plugins/Experimental/GlobalConfigurationData/Tests/GlobalConfigurationDataTests.Target.cs` |
| `SpatialReadinessTestsTarget` | TestTargetRules |  |  |  |  |  | `Engine/Plugins/Experimental/SpatialReadiness/Tests/SpatialReadinessTests.Target.cs` |
| `StateGraphTestsTarget` | TestTargetRules |  |  |  |  |  | `Engine/Plugins/Experimental/StateGraph/Tests/StateGraphTests/StateGraphTests.Target.cs` |
| `UAFAllTestsTarget` | TestTargetRules |  |  |  | "UAFTests" | UAFAnimNodeTests, UAFAnimGraphTests, UAFChooserTests, UAFControlRigTests, UAFLayeringTests, UAFMassTests, UAFMirroringTests, UAFPoseSearchTests, UAFStateTreeTests, UAFWarpingTests | `Engine/Plugins/Experimental/UAF/UAF/Tests/UAFAllTests.Target.cs` |
| `UAFAnimGraphTestsTarget` | TestTargetRules |  |  |  |  |  | `Engine/Plugins/Experimental/UAF/UAFAnimGraph/Tests/UAFAnimGraphTests.Target.cs` |
| `UAFAnimNodeTestsTarget` | TestTargetRules |  |  |  |  |  | `Engine/Plugins/Experimental/UAF/UAFAnimNode/Tests/UAFAnimNodeTests.Target.cs` |
| `UAFChooserTestsTarget` | TestTargetRules |  |  |  |  |  | `Engine/Plugins/Experimental/UAF/UAFChooser/Tests/UAFChooserTests.Target.cs` |
| `UAFControlRigTestsTarget` | TestTargetRules |  |  |  |  |  | `Engine/Plugins/Experimental/UAF/UAFControlRig/Tests/UAFControlRigTests.Target.cs` |
| `UAFLayeringTestsTarget` | TestTargetRules |  |  |  |  |  | `Engine/Plugins/Experimental/UAF/UAFLayering/Tests/UAFLayeringTests.Target.cs` |
| `UAFMassTestsTarget` | TestTargetRules |  |  |  |  |  | `Engine/Plugins/Experimental/UAF/UAFMass/Tests/UAFMassTests.Target.cs` |
| `UAFMirroringTestsTarget` | TestTargetRules |  |  |  |  |  | `Engine/Plugins/Experimental/UAF/UAFMirroring/Tests/UAFMirroringTests.Target.cs` |
| `UAFPoseSearchTestsTarget` | TestTargetRules |  |  |  |  |  | `Engine/Plugins/Experimental/UAF/UAFPoseSearch/Tests/UAFPoseSearchTests.Target.cs` |
| `UAFStateTreeTestsTarget` | TestTargetRules |  |  |  |  |  | `Engine/Plugins/Experimental/UAF/UAFStateTree/Tests/UAFStateTreeTests.Target.cs` |
| `UAFTestsTarget` | TestTargetRules |  |  |  |  |  | `Engine/Plugins/Experimental/UAF/UAF/Tests/UAFTests.Target.cs` |
| `UAFWarpingTestsTarget` | TestTargetRules |  |  |  |  |  | `Engine/Plugins/Experimental/UAF/UAFWarping/Tests/UAFWarpingTests.Target.cs` |

## Engine/Plugins/PCG (1)

| target | base | Type | LinkType | BuildEnvironment | LaunchModule | ExtraModuleNames | file |
|---|---|---|---|---|---|---|---|
| `PCGTestsTarget` | TestTargetRules |  |  |  |  |  | `Engine/Plugins/PCG/Tests/PCGTests.Target.cs` |

## Engine/Source/Developer (1)

| target | base | Type | LinkType | BuildEnvironment | LaunchModule | ExtraModuleNames | file |
|---|---|---|---|---|---|---|---|
| `ChaosTestHarnessTarget` | TestTargetRules |  |  |  |  |  | `Engine/Source/Developer/ChaosTestHarness/ChaosTestHarness.Target.cs` |

## Engine/Source/Programs (111)

| target | base | Type | LinkType | BuildEnvironment | LaunchModule | ExtraModuleNames | file |
|---|---|---|---|---|---|---|---|
| `ASDToolTarget` | TargetRules | Program | Monolithic |  | "ASDTool" |  | `Engine/Source/Programs/Windows/ASDTool/ASDTool.Target.cs` |
| `AutoRTFMTestsTarget` | TargetRules | Program | Monolithic |  | "AutoRTFMTests" |  | `Engine/Source/Programs/AutoRTFMTests/AutoRTFMTests.Target.cs` |
| `AutoRTFMTestsWithExceptionsTarget` | AutoRTFMTestsTarget |  |  |  |  |  | `Engine/Source/Programs/AutoRTFMTests/AutoRTFMTestsWithExceptions.Target.cs` |
| `AutoRTFMTestsWithICUTarget` | AutoRTFMTestsTarget |  |  |  |  |  | `Engine/Source/Programs/AutoRTFMTests/AutoRTFMTestsWithICU.Target.cs` |
| `AutoRTFMTestsWithMergeModulesTarget` | AutoRTFMTestsTarget |  |  |  |  |  | `Engine/Source/Programs/AutoRTFMTests/AutoRTFMTestsWithMergeModules.Target.cs` |
| `AutoRTFMTestsWithModularTarget` | AutoRTFMTestsTarget |  | Modular |  |  |  | `Engine/Source/Programs/AutoRTFMTests/AutoRTFMTestsWithModular.Target.cs` |
| `AutoRTFMTestsWithSTATSTarget` | AutoRTFMTestsTarget |  |  |  |  |  | `Engine/Source/Programs/AutoRTFMTests/AutoRTFMTestsWithSTATS.Target.cs` |
| `BaseTextureBuildWorkerTarget` | TextureBuildWorkerTarget |  |  |  | "BaseTextureBuildWorker" |  | `Engine/Source/Programs/BaseTextureBuildWorker/BaseTextureBuildWorker.Target.cs` |
| `BenchmarkToolTarget` | TargetRules | Program | Monolithic |  | "BenchmarkTool" |  | `Engine/Source/Programs/BenchmarkTool/BenchmarkTool.Target.cs` |
| `BlankProgramTarget` | TargetRules | Program | Monolithic |  | "BlankProgram" |  | `Engine/Source/Programs/BlankProgram/BlankProgram.Target.cs` |
| `BootstrapPackagedGameTarget` | TargetRules | Program | Monolithic |  | "BootstrapPackagedGame" |  | `Engine/Source/Programs/Windows/BootstrapPackagedGame/BootstrapPackagedGame.Target.cs` |
| `BreakpadSymbolEncoderTarget` | TargetRules | Program | Monolithic |  | "BreakpadSymbolEncoder" |  | `Engine/Source/Programs/BreakpadSymbolEncoder/BreakpadSymbolEncoder.Target.cs` |
| `BuildPatchToolTarget` | TargetRules | Program | Monolithic |  | "BuildPatchTool" |  | `Engine/Source/Programs/BuildPatchTool/BuildPatchTool.Target.cs` |
| `BuildStorageToolTarget` | TargetRules | Program | Monolithic |  | "BuildStorageTool" |  | `Engine/Source/Programs/BuildStorageTool/BuildStorageTool.Target.cs` |
| `ChaosPhysicsTestsTarget` | ChaosTestHarnessTarget |  |  |  |  |  | `Engine/Source/Programs/ChaosPhysicsTests/ChaosPhysicsTests.Target.cs` |
| `ChaosSpatialPartitionsTestsTarget` | ChaosTestHarnessTarget |  |  |  |  |  | `Engine/Source/Programs/ChaosSpatialPartitionsTests/ChaosSpatialPartitionsTests.Target.cs` |
| `ChaosUserDataPTTestsTarget` | TestTargetRules |  |  |  |  |  | `Engine/Source/Programs/ChaosUserDataPTTests/ChaosUserDataPTTests.Target.cs` |
| `ChaosVisualDebuggerTarget` | TargetRules | Program | Monolithic | Unique | "ChaosVisualDebugger" |  | `Engine/Source/Programs/ChaosVisualDebugger/ChaosVisualDebugger.Target.cs` |
| `CmdLinkTarget` | TargetRules | Program | Monolithic |  | "CmdLink" |  | `Engine/Source/Programs/CmdLink/CmdLink.Target.cs` |
| `CrashReportClientEditorTarget` | CrashReportClientTarget |  |  |  | "CrashReportClientEditor" |  | `Engine/Source/Programs/CrashReportClient/CrashReportClientEditor.Target.cs` |
| `CrashReportClientTarget` | TargetRules | Program | Monolithic |  | "CrashReportClient" |  | `Engine/Source/Programs/CrashReportClient/CrashReportClient.Target.cs` |
| `CSVToTelemetryTarget` | TargetRules | Program | Modular |  | "CSVToTelemetry" |  | `Engine/Source/Programs/CSVTools/CSVToTelemetry/CSVToTelemetry.Target.cs` |
| `DatasmithCADWorkerTarget` | TargetRules | Program | Monolithic |  | "DatasmithCADWorker" |  | `Engine/Source/Programs/Enterprise/Datasmith/DatasmithCADWorker/DatasmithCADWorker.Target.cs` |
| `DatasmithFacadeCSharpTarget` | TargetRules | Program | Monolithic |  | "DatasmithFacadeCSharp" |  | `Engine/Source/Programs/Enterprise/Datasmith/DatasmithFacadeCSharp/DatasmithFacadeCSharp.Target.cs` |
| `DatasmithMax2022Target` | DatasmithMaxBaseTarget |  |  |  | "DatasmithMax2022" |  | `Engine/Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/DatasmithMax2022.Target.cs` |
| `DatasmithMax2023Target` | DatasmithMaxBaseTarget |  |  |  | "DatasmithMax2023" |  | `Engine/Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/DatasmithMax2023.Target.cs` |
| `DatasmithMax2024Target` | DatasmithMaxBaseTarget |  |  |  | "DatasmithMax2024" |  | `Engine/Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/DatasmithMax2024.Target.cs` |
| `DatasmithMax2025Target` | DatasmithMaxBaseTarget |  |  |  | "DatasmithMax2025" |  | `Engine/Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/DatasmithMax2025.Target.cs` |
| `DatasmithMax2026Target` | DatasmithMaxBaseTarget |  |  |  | "DatasmithMax2026" |  | `Engine/Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/DatasmithMax2026.Target.cs` |
| `DatasmithMax2027Target` | DatasmithMaxBaseTarget |  |  |  | "DatasmithMax2027" |  | `Engine/Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/DatasmithMax2027.Target.cs` |
| `DatasmithMaxBaseTarget` | TargetRules | Program | Monolithic |  |  |  | `Engine/Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/DatasmithMax2022.Target.cs` |
| `DatasmithSDKTarget` | TargetRules | Program | Monolithic |  | "DatasmithSDK" | DatasmithCore, DatasmithExporter | `Engine/Source/Programs/Enterprise/Datasmith/DatasmithSDK/DatasmithSDK.Target.cs` |
| `DerivedDataBuildWorkerTarget` | TargetRules | Program | Monolithic |  |  |  | `Engine/Source/Programs/DerivedDataBuildWorker/DerivedDataBuildWorker.Build.cs` |
| `DerivedDataToolTarget` | TargetRules | Program | Monolithic |  | "DerivedDataTool" |  | `Engine/Source/Programs/DerivedDataTool/DerivedDataTool.Target.cs` |
| `DiffAssetBulkDataTarget` | TargetRules | Program | Modular |  | "DiffAssetBulkData" |  | `Engine/Source/Programs/DiffAssetBulkData/DiffAssetBulkData.Target.cs` |
| `DotNetPerforceLibTarget` | TargetRules | Program | Monolithic |  | "DotNetPerforceLib" |  | `Engine/Source/Programs/Shared/EpicGames.Perforce.Native/DotNetPerforceLib.Target.cs` |
| `DsymExporterTarget` | TargetRules | Program | Monolithic |  | "DsymExporter" |  | `Engine/Source/Programs/Mac/DsymExporter/DsymExporter.Target.cs` |
| `DumpSymsTarget` | TargetRules | Program | Monolithic |  | "DumpSyms" |  | `Engine/Source/Programs/DumpSyms/DumpSyms.Target.cs` |
| `EpicWebHelperTarget` | TargetRules | Program | Monolithic |  | "EpicWebHelper" |  | `Engine/Source/Programs/EpicWebHelper/EpicWebHelper.Target.cs` |
| `FoundationTestsTarget` | TestTargetRules |  |  |  |  |  | `Engine/Source/Programs/LowLevelTests/FoundationTests/FoundationTests.Target.cs` |
| `GeometryProcessingTarget` | TargetRules | Program | Monolithic |  | "GeometryProcessing" |  | `Engine/Source/Programs/GeometryProcessing/GeometryProcessing.Target.cs` |
| `GPUReshapeBootstrapperTarget` | TargetRules | Program | Monolithic |  | "GPUReshapeBootstrapper" |  | `Engine/Source/Programs/GPUReshape/Source/GPUReshapeBootstrapper.Target.cs` |
| `HeadlessChaosPerfTarget` | TargetRules | Program | Monolithic |  | "HeadlessChaosPerf" |  | `Engine/Source/Programs/HeadlessChaosPerf/HeadlessChaosPerf.Target.cs` |
| `HeadlessChaosTarget` | TestTargetRules |  |  | Unique |  |  | `Engine/Source/Programs/HeadlessChaos/HeadlessChaos.Target.cs` |
| `HordeTestTarget` | TargetRules | Program | Monolithic |  | "HordeTest" |  | `Engine/Source/Programs/Horde/Samples/HordeTest/HordeTest.Target.cs` |
| `IasToolTarget` | TargetRules | Program | Monolithic |  | "IasTool" |  | `Engine/Source/Programs/IoStoreOnDemand/IasTool.Target.cs` |
| `InterchangeWorkerTarget` | TargetRules | Program | Monolithic |  | "InterchangeWorker" |  | `Engine/Source/Programs/InterchangeWorker/InterchangeWorker.Target.cs` |
| `IoStoreDependencyViewerTarget` | TargetRules | Program | Monolithic |  | "IoStoreDependencyViewer" |  | `Engine/Source/Programs/IoStoreDependencyViewer/IoStoreDependencyViewer.Target.cs` |
| `LiveCodingConsoleTarget` | TargetRules | Program | Monolithic |  | "LiveCodingConsole" |  | `Engine/Source/Programs/LiveCodingConsole/LiveCodingConsole.Target.cs` |
| `LiveLinkFbxProviderTarget` | TargetRules | Program | Monolithic |  | "LiveLinkFbxProvider" |  | `Engine/Source/Programs/LiveLinkFbxProvider/Source/LiveLinkFbxProvider.Target.cs` |
| `LiveLinkHubTarget` | TargetRules | Editor |  |  | "LiveLinkHubLauncher" |  | `Engine/Source/Programs/LiveLinkHub/Source/LiveLinkHub.Target.cs` |
| `MassTestsTarget` | TestTargetRules |  |  |  |  |  | `Engine/Source/Programs/MassTests/MassTests.Target.cs` |
| `MathCoreTestsTarget` | TestTargetRules |  |  |  |  |  | `Engine/Source/Programs/LowLevelTests/MathCoreTests/MathCoreTests.Target.cs` |
| `NetworkPredictionTestsTarget` | TestTargetRules |  |  |  |  |  | `Engine/Source/Programs/NetworkPredictionTests/NetworkPredictionTests.Target.cs` |
| `PlainPropsTestsTarget` | TestTargetRules |  |  |  |  |  | `Engine/Source/Programs/PlainPropsTests/PlainPropsTests.Target.cs` |
| `ReplicationSystemLowLevelTestsTarget` | TestTargetRules |  |  |  |  |  | `Engine/Source/Programs/ReplicationSystemLowLevelTests/ReplicationSystemLowLevelTests.Target.cs` |
| `ShaderAuditViewerTarget` | TargetRules | Program | Monolithic |  | "ShaderAuditViewer" |  | `Engine/Source/Programs/ShaderAuditViewer/ShaderAuditViewer.Target.cs` |
| `ShaderBuildWorkerTarget` | DerivedDataBuildWorkerTarget |  | Modular | UniqueIfNeeded | "ShaderBuildWorker" |  | `Engine/Source/Programs/ShaderBuildWorker/ShaderBuildWorker.Target.cs` |
| `ShaderCompileWorkerTarget` | TargetRules | Program | Modular | UniqueIfNeeded | "ShaderCompileWorker" |  | `Engine/Source/Programs/ShaderCompileWorker/ShaderCompileWorker.Target.cs` |
| `SlateTestsTarget` | TestTargetRules |  |  |  |  |  | `Engine/Source/Programs/SlateTests/SlateTests.Target.cs` |
| `SlateUGSTarget` | TargetRules | Program | Monolithic |  | "SlateUGS" |  | `Engine/Source/Programs/SlateUGS/SlateUGS.Target.cs` |
| `SlateViewerTarget` | TargetRules | Program | Monolithic |  | "SlateViewer" |  | `Engine/Source/Programs/SlateViewer/SlateViewer.Target.cs` |
| `StateStreamTestsTarget` | TestTargetRules |  |  |  |  |  | `Engine/Source/Programs/LowLevelTests/StateStreamTests/StateStreamTests.Target.cs` |
| `SubmitToolTarget` | TargetRules | Program | Monolithic |  | "SubmitTool" |  | `Engine/Source/Programs/SubmitTool/SubmitTool.Target.cs` |
| `SwitchboardListenerCmdTarget` | SwitchboardListenerTargetBase |  |  |  | "SwitchboardListenerCmd" |  | `Engine/Source/Programs/SwitchboardListener/SwitchboardListenerCmd.Target.cs` |
| `SwitchboardListenerHelperTarget` | TargetRules | Program | Monolithic |  | "SwitchboardListenerHelper" |  | `Engine/Source/Programs/SwitchboardListenerHelper/SwitchboardListenerHelper.Target.cs` |
| `SwitchboardListenerTarget` | SwitchboardListenerTargetBase |  |  |  | "SwitchboardListener" |  | `Engine/Source/Programs/SwitchboardListener/SwitchboardListener.Target.cs` |
| `SwitchboardListenerTargetBase` | TargetRules | Program | Monolithic |  |  |  | `Engine/Source/Programs/SwitchboardListener/SwitchboardListener.Target.cs` |
| `SwitchboardListenerTestsTarget` | TestTargetRules |  |  |  | "SwitchboardListenerTests" | LaunchModuleName | `Engine/Source/Programs/SwitchboardListener/SwitchboardListenerTests.Target.cs` |
| `SymsLibDumpTarget` | TargetRules | Program | Monolithic |  | "SymsLibDump" |  | `Engine/Source/Programs/SymsLibDump/SymsLibDump.Target.cs` |
| `TestPALTarget` | TargetRules | Program | Monolithic |  | "TestPAL" |  | `Engine/Source/Programs/TestPAL/TestPAL.Target.cs` |
| `TextureShareSDKTarget` | TargetRules | Program | Monolithic |  | "TextureShareSDK" |  | `Engine/Source/Programs/VirtualProduction/TextureShare/TextureShareSDK.Target.cs` |
| `ToolMenusTestsTarget` | TestTargetRules |  |  |  |  |  | `Engine/Source/Programs/ToolMenusTests/ToolMenusTests.Target.cs` |
| `TraceAnalyzerTarget` | TargetRules | Program | Monolithic |  | "TraceAnalyzer" |  | `Engine/Source/Programs/TraceAnalyzer/TraceAnalyzer.Target.cs` |
| `TraceQueryTarget` | TargetRules | Program | Monolithic |  | "TraceQuery" |  | `Engine/Source/Programs/TraceQuery/TraceQuery.Target.cs` |
| `TraceTrimmerTarget` | TargetRules | Program | Monolithic |  | "TraceTrimmer" |  | `Engine/Source/Programs/TraceTrimmer/TraceTrimmer.Target.cs` |
| `UbaAgentTarget` | TargetRules |  |  |  | "UbaAgent" |  | `Engine/Source/Programs/UnrealBuildAccelerator/UbaAgent.Target.cs` |
| `UbaCacheServiceTarget` | TargetRules |  |  |  | "UbaCacheService" |  | `Engine/Source/Programs/UnrealBuildAccelerator/UbaCacheService.Target.cs` |
| `UbaCliTarget` | TargetRules |  |  |  | "UbaCli" |  | `Engine/Source/Programs/UnrealBuildAccelerator/UbaCli.Target.cs` |
| `UbaCommonTarget` | TargetRules |  |  |  | "UbaCommon" |  | `Engine/Source/Programs/UnrealBuildAccelerator/UbaCommon.Target.cs` |
| `UbaCoordinatorHordeTarget` | TargetRules | Program | Monolithic |  | "UbaCoordinatorHorde" |  | `Engine/Source/Programs/UnrealBuildAccelerator/UbaCoordinatorHorde.Target.cs` |
| `UbaCoreTarget` | TargetRules |  |  |  | "UbaCore" |  | `Engine/Source/Programs/UnrealBuildAccelerator/UbaCore.Target.cs` |
| `UbaDetoursTarget` | TargetRules |  |  |  | "UbaDetours" |  | `Engine/Source/Programs/UnrealBuildAccelerator/UbaDetours.Target.cs` |
| `UbaHostTarget` | TargetRules |  |  |  | "UbaHost" |  | `Engine/Source/Programs/UnrealBuildAccelerator/UbaHost.Target.cs` |
| `UbaNinjaTarget` | TargetRules |  |  |  | "UbaNinja" |  | `Engine/Source/Programs/UnrealBuildAccelerator/UbaNinja.Target.cs` |
| `UbaObjToolTarget` | TargetRules |  |  |  | "UbaObjTool" |  | `Engine/Source/Programs/UnrealBuildAccelerator/UbaObjTool.Target.cs` |
| `UbaTestAppTarget` | TargetRules |  |  |  | "UbaTestApp" |  | `Engine/Source/Programs/UnrealBuildAccelerator/UbaTestApp.Target.cs` |
| `UbaTestTarget` | TargetRules |  |  |  | "UbaTest" |  | `Engine/Source/Programs/UnrealBuildAccelerator/UbaTest.Target.cs` |
| `UbaVisualizerTarget` | TargetRules |  |  |  | "UbaVisualizer" |  | `Engine/Source/Programs/UnrealBuildAccelerator/UbaVisualizer.Target.cs` |
| `UninstallHelperTarget` | TargetRules | Program | Monolithic |  | "UninstallHelper" |  | `Engine/Source/Programs/UninstallHelper/UninstallHelper.Target.cs` |
| `UnrealAssetStringifyTarget` | TargetRules | Program | Monolithic |  | "UnrealAssetStringify" |  | `Engine/Source/Programs/UnrealAssetStringify/UnrealAssetStringify.Target.cs` |
| `UnrealAtoSTarget` | TargetRules | Program | Monolithic |  | "UnrealAtoS" |  | `Engine/Source/Programs/Mac/UnrealAtoS/UnrealAtoS.Target.cs` |
| `UnrealEditorServicesTarget` | TargetRules | Program | Monolithic |  | "UnrealEditorServices" |  | `Engine/Source/Programs/Mac/UnrealEditorServices/UnrealEditorServices.Target.cs` |
| `UnrealFrontendTarget` | TargetRules | Program | Modular |  | "UnrealFrontend" |  | `Engine/Source/Programs/UnrealFrontend/UnrealFrontend.Target.cs` |
| `UnrealInsightsTarget` | TargetRules | Program | bMonolithic ? TargetLinkType.Monolithic : TargetLinkType.Modular |  | "UnrealInsights" |  | `Engine/Source/Programs/UnrealInsights/UnrealInsights.Target.cs` |
| `UnrealLaunchDaemonTarget` | TargetRules | Program | Monolithic |  | "UnrealLaunchDaemon" |  | `Engine/Source/Programs/IOS/UnrealLaunchDaemon/UnrealLaunchDaemon.Target.cs` |
| `UnrealLightmassTarget` | TargetRules | Program | Modular |  | "UnrealLightmass" |  | `Engine/Source/Programs/UnrealLightmass/UnrealLightmass.Target.cs` |
| `UnrealMultiUserServerTarget` | TargetRules | Program | Modular |  | "UnrealMultiUserServer" |  | `Engine/Source/Programs/UnrealMultiUserServer/UnrealMultiUserServer.Target.cs` |
| `UnrealMultiUserSlateServerTarget` | TargetRules | Program | Modular |  | "UnrealMultiUserSlateServer" |  | `Engine/Source/Programs/UnrealMultiUserSlateServer/UnrealMultiUserSlateServer.Target.cs` |
| `UnrealObjectPtrToolTarget` | TargetRules | Program | Modular |  | "UnrealObjectPtrTool" |  | `Engine/Source/Programs/UnrealObjectPtrTool/UnrealObjectPtrTool.Target.cs` |
| `UnrealPackageToolTarget` | TargetRules | Program | Monolithic |  | "UnrealPackageTool" |  | `Engine/Source/Programs/UnrealPackageTool/UnrealPackageTool.Target.cs` |
| `UnrealPakTarget` | TargetRules | Program | Modular |  | "UnrealPak" |  | `Engine/Source/Programs/UnrealPak/UnrealPak.Target.cs` |
| `UnrealRecoverySvcTarget` | TargetRules | Program | Monolithic |  | "UnrealRecoverySvc" |  | `Engine/Source/Programs/UnrealRecoverySvc/UnrealRecoverySvc.Target.cs` |
| `UnrealVersionSelectorTarget` | TargetRules | Program | Monolithic |  | "UnrealVersionSelector" |  | `Engine/Source/Programs/UnrealVersionSelector/UnrealVersionSelector.Target.cs` |
| `UnrealVirtualizationToolTarget` | TargetRules | Program | Monolithic |  | "UnrealVirtualizationTool" |  | `Engine/Source/Programs/UnrealVirtualizationTool/UnrealVirtualizationTool.Target.cs` |
| `UnsyncTarget` | TargetRules | Program | Monolithic |  | "Unsync" |  | `Engine/Source/Programs/Unsync/Unsync.Target.cs` |
| `WebTestsServerCppTarget` | TargetRules | Program | Monolithic |  | "WebTestsServerCpp" |  | `Engine/Source/Programs/WebTestsServerCpp/WebTestsServerCpp.Target.cs` |
| `WebTestsTarget` | TestTargetRules |  |  |  |  |  | `Engine/Source/Programs/WebTests/WebTests.Target.cs` |
| `ZenDashboardTarget` | TargetRules | Program | Monolithic |  | "ZenDashboard" |  | `Engine/Source/Programs/ZenDashboard/ZenDashboard.Target.cs` |
| `ZenLaunchTarget` | TargetRules | Program | Monolithic |  | "ZenLaunch" |  | `Engine/Source/Programs/ZenLaunch/ZenLaunch.Target.cs` |
| `ZenOplogDiffToolTarget` | TargetRules | Program | Modular |  | "ZenOplogDiffTool" |  | `Engine/Source/Programs/ZenOplogDiffTool/ZenOplogDiffTool.Target.cs` |

## Engine/Source/Runtime (2)

| target | base | Type | LinkType | BuildEnvironment | LaunchModule | ExtraModuleNames | file |
|---|---|---|---|---|---|---|---|
| `EventLoopUnitTestsTarget` | TestTargetRules |  |  |  |  |  | `Engine/Source/Runtime/Online/EventLoopTests/EventLoopUnitTests.Target.cs` |
| `IoStoreOnDemandTestsTarget` | TestTargetRules |  |  |  |  |  | `Engine/Source/Runtime/Experimental/IoStore/Tests/IoStoreOnDemandTests.Target.cs` |

## Engine/Source/UnrealClient.Target.cs (1)

| target | base | Type | LinkType | BuildEnvironment | LaunchModule | ExtraModuleNames | file |
|---|---|---|---|---|---|---|---|
| `UnrealClientTarget` | TargetRules | Client |  | Shared |  | UnrealGame | `Engine/Source/UnrealClient.Target.cs` |

## Engine/Source/UnrealEditor.Target.cs (1)

| target | base | Type | LinkType | BuildEnvironment | LaunchModule | ExtraModuleNames | file |
|---|---|---|---|---|---|---|---|
| `UnrealEditorTarget` | TargetRules | Editor |  | Shared |  | UnrealGame | `Engine/Source/UnrealEditor.Target.cs` |

## Engine/Source/UnrealGame.Target.cs (1)

| target | base | Type | LinkType | BuildEnvironment | LaunchModule | ExtraModuleNames | file |
|---|---|---|---|---|---|---|---|
| `UnrealGameTarget` | TargetRules | Game |  | Shared |  | UnrealGame | `Engine/Source/UnrealGame.Target.cs` |

## Engine/Source/UnrealServer.Target.cs (1)

| target | base | Type | LinkType | BuildEnvironment | LaunchModule | ExtraModuleNames | file |
|---|---|---|---|---|---|---|---|
| `UnrealServerTarget` | TargetRules | Server |  | Shared |  | UnrealGame | `Engine/Source/UnrealServer.Target.cs` |

## Samples/Games (10)

| target | base | Type | LinkType | BuildEnvironment | LaunchModule | ExtraModuleNames | file |
|---|---|---|---|---|---|---|---|
| `LyraClientTarget` | TargetRules | Client |  |  |  | LyraGame | `Samples/Games/Lyra/Source/LyraClient.Target.cs` |
| `LyraEditorTarget` | TargetRules | Editor |  |  |  | LyraGame, LyraEditor | `Samples/Games/Lyra/Source/LyraEditor.Target.cs` |
| `LyraGameEOSTarget` | LyraGameTarget |  |  |  |  |  | `Samples/Games/Lyra/Source/LyraGameEOS.Target.cs` |
| `LyraGameSteamEOSTarget` | LyraGameTarget |  |  |  |  |  | `Samples/Games/Lyra/Source/LyraGameSteamEOS.Target.cs` |
| `LyraGameSteamTarget` | LyraGameTarget |  |  |  |  |  | `Samples/Games/Lyra/Source/LyraGameSteam.Target.cs` |
| `LyraGameTarget` | TargetRules | Game |  |  |  | LyraGame | `Samples/Games/Lyra/Source/LyraGame.Target.cs` |
| `LyraServerEOSTarget` | LyraServerTarget |  |  |  |  |  | `Samples/Games/Lyra/Source/LyraServerEOS.Target.cs` |
| `LyraServerSteamEOSTarget` | LyraServerTarget |  |  |  |  |  | `Samples/Games/Lyra/Source/LyraServerSteamEOS.Target.cs` |
| `LyraServerSteamTarget` | LyraServerTarget |  |  |  |  |  | `Samples/Games/Lyra/Source/LyraServerSteam.Target.cs` |
| `LyraServerTarget` | TargetRules | Server |  |  |  | LyraGame | `Samples/Games/Lyra/Source/LyraServer.Target.cs` |

## Templates/TP_Blank (2)

| target | base | Type | LinkType | BuildEnvironment | LaunchModule | ExtraModuleNames | file |
|---|---|---|---|---|---|---|---|
| `TP_BlankEditorTarget` | TargetRules | Editor |  |  |  | TP_Blank | `Templates/TP_Blank/Source/TP_BlankEditor.Target.cs` |
| `TP_BlankTarget` | TargetRules | Game |  |  |  | TP_Blank | `Templates/TP_Blank/Source/TP_Blank.Target.cs` |

## Templates/TP_FirstPerson (2)

| target | base | Type | LinkType | BuildEnvironment | LaunchModule | ExtraModuleNames | file |
|---|---|---|---|---|---|---|---|
| `TP_FirstPersonEditorTarget` | TargetRules | Editor |  |  |  | TP_FirstPerson | `Templates/TP_FirstPerson/Source/TP_FirstPersonEditor.Target.cs` |
| `TP_FirstPersonTarget` | TargetRules | Game |  |  |  | TP_FirstPerson | `Templates/TP_FirstPerson/Source/TP_FirstPerson.Target.cs` |

## Templates/TP_Puzzle (2)

| target | base | Type | LinkType | BuildEnvironment | LaunchModule | ExtraModuleNames | file |
|---|---|---|---|---|---|---|---|
| `TP_PuzzleEditorTarget` | TargetRules | Editor |  |  |  | TP_Puzzle | `Templates/TP_Puzzle/Source/TP_PuzzleEditor.Target.cs` |
| `TP_PuzzleTarget` | TargetRules | Game |  |  |  | TP_Puzzle | `Templates/TP_Puzzle/Source/TP_Puzzle.Target.cs` |

## Templates/TP_SIM_Blank (2)

| target | base | Type | LinkType | BuildEnvironment | LaunchModule | ExtraModuleNames | file |
|---|---|---|---|---|---|---|---|
| `TP_SIM_BlankEditorTarget` | TargetRules | Editor |  |  |  | TP_SIM_Blank | `Templates/TP_SIM_Blank/Source/TP_SIM_BlankEditor.Target.cs` |
| `TP_SIM_BlankTarget` | TargetRules | Game |  |  |  | TP_SIM_Blank | `Templates/TP_SIM_Blank/Source/TP_SIM_Blank.Target.cs` |

## Templates/TP_SIM_Sandbox (2)

| target | base | Type | LinkType | BuildEnvironment | LaunchModule | ExtraModuleNames | file |
|---|---|---|---|---|---|---|---|
| `TP_SIM_SandboxEditorTarget` | TargetRules | Editor |  |  |  | TP_SIM_Sandbox | `Templates/TP_SIM_Sandbox/Source/TP_SIM_SandboxEditor.Target.cs` |
| `TP_SIM_SandboxTarget` | TargetRules | Game |  |  |  | TP_SIM_Sandbox | `Templates/TP_SIM_Sandbox/Source/TP_SIM_Sandbox.Target.cs` |

## Templates/TP_ThirdPerson (2)

| target | base | Type | LinkType | BuildEnvironment | LaunchModule | ExtraModuleNames | file |
|---|---|---|---|---|---|---|---|
| `TP_ThirdPersonEditorTarget` | TargetRules | Editor |  |  |  | TP_ThirdPerson | `Templates/TP_ThirdPerson/Source/TP_ThirdPersonEditor.Target.cs` |
| `TP_ThirdPersonTarget` | TargetRules | Game |  |  |  | TP_ThirdPerson | `Templates/TP_ThirdPerson/Source/TP_ThirdPerson.Target.cs` |

## Templates/TP_TopDown (2)

| target | base | Type | LinkType | BuildEnvironment | LaunchModule | ExtraModuleNames | file |
|---|---|---|---|---|---|---|---|
| `TP_TopDownEditorTarget` | TargetRules | Editor |  |  |  | TP_TopDown | `Templates/TP_TopDown/Source/TP_TopDownEditor.Target.cs` |
| `TP_TopDownTarget` | TargetRules | Game |  |  |  | TP_TopDown | `Templates/TP_TopDown/Source/TP_TopDown.Target.cs` |

## Templates/TP_VehicleAdv (2)

| target | base | Type | LinkType | BuildEnvironment | LaunchModule | ExtraModuleNames | file |
|---|---|---|---|---|---|---|---|
| `TP_VehicleAdvEditorTarget` | TargetRules | Editor |  |  |  | TP_VehicleAdv | `Templates/TP_VehicleAdv/Source/TP_VehicleAdvEditor.Target.cs` |
| `TP_VehicleAdvTarget` | TargetRules | Game |  |  |  | TP_VehicleAdv | `Templates/TP_VehicleAdv/Source/TP_VehicleAdv.Target.cs` |

## Constructor statements


### `AnimationWarpingRuntimeTestsTarget` — `Engine/Plugins/Animation/AnimationWarping/Tests/AnimationWarpingRuntimeTests.Target.cs`

- `L10 bUsePlatformFileStub = true`
- `L11 bMockEngineDefaults = true`
- `L13 bCompileAgainstEngine = true`
- `L14 bCompileAgainstApplicationCore = true`
- `L16 bTestsRequireEngine = true`

### `ChaosRigidPhysicsAsyncTestsTarget` — `Engine/Plugins/Experimental/ChaosRigidPhysicsAsync/Tests/ChaosRigidPhysicsAsyncTests.Target.cs`

- `L13 bTestsRequireEngine = true`
- `L14 bTestsRequireCoreUObject = true`
- `L16 bCompileAgainstEngine = true`
- `L17 bCompileAgainstCoreUObject = true`
- `L18 bMockEngineDefaults = true`
- `L19 bUsePlatformFileStub = true`
- `L21 bWithLowLevelTestsOverride = true`
- `L24 GlobalDefinitions.Add () "UE_RIGIDPHYSICS_API_ENABLED=1"`
- `L29 GlobalDefinitions.Add () "CHAOS_CONSTRAINTHANDLE_DEBUG_ENABLED=1" [if if (!(bIsShipping \|\| bIsTest))]`
- `L32 GlobalDefinitions.Add () "CATCH_CONFIG_ENABLE_BENCHMARKING=1"`
- `L34 bWarningsAsErrors = true`

### `GameplayGraphTestsTarget` — `Engine/Plugins/Experimental/GameplayGraph/Tests/GameplayGraphTests.Target.cs`

- `_(no statements parsed)_`

### `GlobalConfigurationDataTestsTarget` — `Engine/Plugins/Experimental/GlobalConfigurationData/Tests/GlobalConfigurationDataTests.Target.cs`

- `_(no statements parsed)_`

### `SpatialReadinessTestsTarget` — `Engine/Plugins/Experimental/SpatialReadiness/Tests/SpatialReadinessTests.Target.cs`

- `L10 bUsePlatformFileStub = true`
- `L11 bMockEngineDefaults = true`
- `L12 TestTargetRules.bTestsRequireEngine = true`

### `StateGraphTestsTarget` — `Engine/Plugins/Experimental/StateGraph/Tests/StateGraphTests/StateGraphTests.Target.cs`

- `L9 bForceEnableExceptions = true`
- `L10 EnablePlugins.Add () "StateGraph"`

### `UAFAllTestsTarget` — `Engine/Plugins/Experimental/UAF/UAF/Tests/UAFAllTests.Target.cs`

- `L10 bUsePlatformFileStub = true`
- `L11 bMockEngineDefaults = true`
- `L13 bCompileAgainstEngine = true`
- `L14 bCompileAgainstApplicationCore = true`
- `L16 bTestsRequireEngine = true`
- `L18 bWarningsAsErrors = true`
- `L20 GlobalDefinitions.Add () "CATCH_CONFIG_ENABLE_BENCHMARKING=1"`
- `L22 LaunchModuleName = "UAFTests"`
- `L25 EnablePlugins.AddRange () new string[] { "UAFAnimNode", "UAFAnimGraph", "UAFChooser", "UAFControlRig", "UAFLayering", "UAFMass", "UAFMirroring", "UAFPoseSearch", "UAFStateTree", "UAFWarp`
- `L39 ExtraModuleNames.AddRange () new string[] { "UAFAnimNodeTests", "UAFAnimGraphTests", "UAFChooserTests", "UAFControlRigTests", "UAFLayeringTests", "UAFMassTests", "UAFMirroringTests", "UAFPo`

### `UAFTestsTarget` — `Engine/Plugins/Experimental/UAF/UAF/Tests/UAFTests.Target.cs`

- `L10 bUsePlatformFileStub = true`
- `L11 bMockEngineDefaults = true`
- `L13 bCompileAgainstEngine = true`
- `L14 bCompileAgainstApplicationCore = true`
- `L16 bTestsRequireEngine = true`
- `L18 bWarningsAsErrors = true`
- `L21 GlobalDefinitions.Add () "CATCH_CONFIG_ENABLE_BENCHMARKING=1"`

### `UAFAnimGraphTestsTarget` — `Engine/Plugins/Experimental/UAF/UAFAnimGraph/Tests/UAFAnimGraphTests.Target.cs`

- `L10 bUsePlatformFileStub = true`
- `L11 bMockEngineDefaults = true`
- `L13 bCompileAgainstEngine = true`
- `L14 bCompileAgainstApplicationCore = true`
- `L16 bTestsRequireEngine = true`
- `L18 bWarningsAsErrors = true`
- `L21 GlobalDefinitions.Add () "CATCH_CONFIG_ENABLE_BENCHMARKING=1"`

### `UAFAnimNodeTestsTarget` — `Engine/Plugins/Experimental/UAF/UAFAnimNode/Tests/UAFAnimNodeTests.Target.cs`

- `L10 bUsePlatformFileStub = true`
- `L11 bMockEngineDefaults = true`
- `L13 bCompileAgainstEngine = true`
- `L14 bCompileAgainstApplicationCore = true`
- `L16 bTestsRequireEngine = true`
- `L18 bWarningsAsErrors = true`
- `L21 GlobalDefinitions.Add () "CATCH_CONFIG_ENABLE_BENCHMARKING=1"`

### `UAFChooserTestsTarget` — `Engine/Plugins/Experimental/UAF/UAFChooser/Tests/UAFChooserTests.Target.cs`

- `L10 bUsePlatformFileStub = true`
- `L11 bMockEngineDefaults = true`
- `L13 bCompileAgainstEngine = true`
- `L14 bCompileAgainstApplicationCore = true`
- `L16 bTestsRequireEngine = true`
- `L18 bWarningsAsErrors = true`
- `L21 GlobalDefinitions.Add () "CATCH_CONFIG_ENABLE_BENCHMARKING=1"`

### `UAFControlRigTestsTarget` — `Engine/Plugins/Experimental/UAF/UAFControlRig/Tests/UAFControlRigTests.Target.cs`

- `L10 bUsePlatformFileStub = true`
- `L11 bMockEngineDefaults = true`
- `L13 bCompileAgainstEngine = true`
- `L14 bCompileAgainstApplicationCore = true`
- `L16 bTestsRequireEngine = true`
- `L18 bWarningsAsErrors = true`
- `L21 GlobalDefinitions.Add () "CATCH_CONFIG_ENABLE_BENCHMARKING=1"`

### `UAFLayeringTestsTarget` — `Engine/Plugins/Experimental/UAF/UAFLayering/Tests/UAFLayeringTests.Target.cs`

- `L10 bUsePlatformFileStub = true`
- `L11 bMockEngineDefaults = true`
- `L13 bCompileAgainstEngine = true`
- `L14 bCompileAgainstApplicationCore = true`
- `L16 bTestsRequireEngine = true`
- `L18 bWarningsAsErrors = true`
- `L21 GlobalDefinitions.Add () "CATCH_CONFIG_ENABLE_BENCHMARKING=1"`

### `UAFMassTestsTarget` — `Engine/Plugins/Experimental/UAF/UAFMass/Tests/UAFMassTests.Target.cs`

- `L10 bUsePlatformFileStub = true`
- `L11 bMockEngineDefaults = true`
- `L13 bCompileAgainstEngine = true`
- `L14 bCompileAgainstApplicationCore = true`
- `L16 bTestsRequireEngine = true`
- `L18 bWarningsAsErrors = true`
- `L21 GlobalDefinitions.Add () "CATCH_CONFIG_ENABLE_BENCHMARKING=1"`

### `UAFMirroringTestsTarget` — `Engine/Plugins/Experimental/UAF/UAFMirroring/Tests/UAFMirroringTests.Target.cs`

- `L10 bUsePlatformFileStub = true`
- `L11 bMockEngineDefaults = true`
- `L13 bCompileAgainstEngine = true`
- `L14 bCompileAgainstApplicationCore = true`
- `L16 bTestsRequireEngine = true`
- `L18 bWarningsAsErrors = true`
- `L21 GlobalDefinitions.Add () "CATCH_CONFIG_ENABLE_BENCHMARKING=1"`

### `UAFPoseSearchTestsTarget` — `Engine/Plugins/Experimental/UAF/UAFPoseSearch/Tests/UAFPoseSearchTests.Target.cs`

- `L10 bUsePlatformFileStub = true`
- `L11 bMockEngineDefaults = true`
- `L13 bCompileAgainstEngine = true`
- `L14 bCompileAgainstApplicationCore = true`
- `L16 bTestsRequireEngine = true`
- `L18 bWarningsAsErrors = true`
- `L21 GlobalDefinitions.Add () "CATCH_CONFIG_ENABLE_BENCHMARKING=1"`

### `UAFStateTreeTestsTarget` — `Engine/Plugins/Experimental/UAF/UAFStateTree/Tests/UAFStateTreeTests.Target.cs`

- `L10 bUsePlatformFileStub = true`
- `L11 bMockEngineDefaults = true`
- `L13 bCompileAgainstEngine = true`
- `L14 bCompileAgainstApplicationCore = true`
- `L16 bTestsRequireEngine = true`
- `L18 bWarningsAsErrors = true`
- `L21 GlobalDefinitions.Add () "CATCH_CONFIG_ENABLE_BENCHMARKING=1"`

### `UAFWarpingTestsTarget` — `Engine/Plugins/Experimental/UAF/UAFWarping/Tests/UAFWarpingTests.Target.cs`

- `L10 bUsePlatformFileStub = true`
- `L11 bMockEngineDefaults = true`
- `L13 bCompileAgainstEngine = true`
- `L14 bCompileAgainstApplicationCore = true`
- `L16 bTestsRequireEngine = true`
- `L18 bWarningsAsErrors = true`
- `L21 GlobalDefinitions.Add () "CATCH_CONFIG_ENABLE_BENCHMARKING=1"`

### `PCGTestsTarget` — `Engine/Plugins/PCG/Tests/PCGTests.Target.cs`

- `L10 bCompileAgainstApplicationCore = true`
- `L11 bCompileAgainstEngine = true`
- `L12 bCompileAgainstCoreUObject = true`
- `L14 bMockEngineDefaults = true`
- `L15 bTestsRequireEngine = true`
- `L18 bCompileICU = true`
- `L19 bUsePlatformFileStub = false`
- `L26 bWarningsAsErrors = true`

### `ChaosTestHarnessTarget` — `Engine/Source/Developer/ChaosTestHarness/ChaosTestHarness.Target.cs`

- `L10 bCompileAgainstEngine = true`
- `L11 bCompileAgainstCoreUObject = true`
- `L12 bCompileAgainstApplicationCore = true`
- `L13 bMockEngineDefaults = true`
- `L14 bUsePlatformFileStub = true`
- `L16 bWithLowLevelTestsOverride = true`
- `L18 GlobalDefinitions.Add () "CATCH_CONFIG_ENABLE_BENCHMARKING=1"`
- `L20 bWarningsAsErrors = true`

### `AutoRTFMTestsTarget` — `Engine/Source/Programs/AutoRTFMTests/AutoRTFMTests.Target.cs`

- `L20 DefaultBuildSettings = BuildSettingsVersion.Latest`
- `L21 Type = TargetType.Program`
- `L22 LinkType = TargetLinkType.Monolithic`
- `L23 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L25 LaunchModuleName = "AutoRTFMTests"`
- `L27 bCompileAgainstEngine = false`
- `L28 bCompileAgainstCoreUObject = true`
- `L31 bUseLoggingInShipping = true`
- `L34 bIsBuildingConsoleApplication = true`
- `L37 bUseUnityBuild = false`
- `L40 bCompileICU = false`
- `L45 bUseAutoRTFMCompiler = true [if if (!bGenerateProjectFiles)]`
- `L49 bFNameOutlineNumber = true`
- `L54 GlobalDefinitions.Add () "UE_USE_VIRTUAL_STACK_ALLOCATOR_FOR_SCRIPT_VM=1" [if if (!bForceNoVirtualStackAllocator)]`
- `L57 MinCpuArchX64 = MinimumCpuArchitectureX64.AVX`
- `L59 bCompileWithStatsWithoutEngine = true`
- `L60 GlobalDefinitions.Add () "ENABLE_STATNAMEDEVENTS=1"`
- `L61 GlobalDefinitions.Add () "ENABLE_STATNAMEDEVENTS_UOBJECT=1"`
- `L67 GlobalDefinitions.Add () "ALLOW_LOG_FILE=0" [if if (!bAllowLogFile)]`
- `L71 GlobalDefinitions.Add () "ALLOW_LOG_FILE=1" [if else]`
- `L74 GlobalDefinitions.Add () "PLATFORM_USES_FIXED_GMalloc_CLASS=0"`
- `L76 GlobalDefinitions.Add () "UNIX_PLATFORM_FILE_SPEEDUP_FILE_OPERATIONS=1"`
- `L79 GlobalDefinitions.Add () "NOINITCRASHREPORTER=1"`
- `L82 GlobalDefinitions.Add () "UE_AUTORTFM_ENABLED_RUNTIME_BY_DEFAULT=0"`
- `L85 GlobalDefinitions.Add () "CSV_PROFILER=1"`
- `L86 GlobalDefinitions.Add () "CSV_PROFILER_ENABLE_IN_SHIPPING=1"`
- `L91 GlobalDefinitions.Add () "UE_CALLSTACK_TRACE_ENABLED=1" [if if (Target.Configuration != UnrealTargetConfiguration.Shipping)]`
- `L95 GlobalDefinitions.Add () "USE_HITCH_DETECTION=1"`
- `L101 bEnableTrace = true`

### `AutoRTFMTestsWithExceptionsTarget` — `Engine/Source/Programs/AutoRTFMTests/AutoRTFMTestsWithExceptions.Target.cs`

- `L13 bForceEnableExceptions = true`

### `AutoRTFMTestsWithICUTarget` — `Engine/Source/Programs/AutoRTFMTests/AutoRTFMTestsWithICU.Target.cs`

- `L14 bCompileICU = true`

### `AutoRTFMTestsWithMergeModulesTarget` — `Engine/Source/Programs/AutoRTFMTests/AutoRTFMTestsWithMergeModules.Target.cs`

- `L13 bMergeModules = true`

### `AutoRTFMTestsWithModularTarget` — `Engine/Source/Programs/AutoRTFMTests/AutoRTFMTestsWithModular.Target.cs`

- `L13 LinkType = TargetLinkType.Modular`
- `L14 GlobalDefinitions.Add () "AUTORTFMTESTS_NO_PEEKING_AT_PRIVATES=1"`

### `AutoRTFMTestsWithSTATSTarget` — `Engine/Source/Programs/AutoRTFMTests/AutoRTFMTestsWithSTATS.Target.cs`

- `L13 GlobalDefinitions.Remove () "ENABLE_STATNAMEDEVENTS=1"`
- `L14 GlobalDefinitions.Remove () "ENABLE_STATNAMEDEVENTS_UOBJECT=1"`
- `L15 GlobalDefinitions.Add () "FORCE_USE_STATS=1"`

### `BaseTextureBuildWorkerTarget` — `Engine/Source/Programs/BaseTextureBuildWorker/BaseTextureBuildWorker.Target.cs`

- `L11 LaunchModuleName = "BaseTextureBuildWorker"`

### `BenchmarkToolTarget` — `Engine/Source/Programs/BenchmarkTool/BenchmarkTool.Target.cs`

- `L11 Type = TargetType.Program`
- `L12 LinkType = TargetLinkType.Monolithic`
- `L13 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L14 LaunchModuleName = "BenchmarkTool"`
- `L16 bBuildDeveloperTools = false`
- `L17 bBuildWithEditorOnlyData = false`
- `L18 bCompileAgainstEngine = false`
- `L19 bCompileAgainstCoreUObject = false`
- `L20 bCompileAgainstApplicationCore = false`
- `L21 bIsBuildingConsoleApplication = true`

### `BlankProgramTarget` — `Engine/Source/Programs/BlankProgram/BlankProgram.Target.cs`

- `L11 Type = TargetType.Program`
- `L12 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L13 DefaultBuildSettings = BuildSettingsVersion.Latest`
- `L14 LinkType = TargetLinkType.Monolithic`
- `L15 LaunchModuleName = "BlankProgram"`
- `L18 bBuildDeveloperTools = false`
- `L23 bBuildWithEditorOnlyData = Target.Platform.IsInGroup(UnrealPlatformGroup.Desktop) && bDebugOrDevelopment`
- `L26 bCompileAgainstEngine = false`
- `L27 bCompileAgainstCoreUObject = false`
- `L28 bCompileAgainstApplicationCore = false`
- `L29 bCompileICU = false`
- `L38 bIsBuildingConsoleApplication = true`

### `BreakpadSymbolEncoderTarget` — `Engine/Source/Programs/BreakpadSymbolEncoder/BreakpadSymbolEncoder.Target.cs`

- `L11 Type = TargetType.Program`
- `L12 LinkType = TargetLinkType.Monolithic`
- `L13 LaunchModuleName = "BreakpadSymbolEncoder"`
- `L16 UndecoratedConfiguration = UnrealTargetConfiguration.Shipping`
- `L19 bBuildDeveloperTools = false`
- `L22 bCompileAgainstEngine = false`
- `L23 bCompileAgainstCoreUObject = false`
- `L26 bUseLoggingInShipping = true`
- `L29 bIsBuildingConsoleApplication = true`
- `L31 bUseUnityBuild = false`

### `BuildPatchToolTarget` — `Engine/Source/Programs/BuildPatchTool/BuildPatchTool.Target.cs`

- `L12 Type = TargetType.Program`
- `L13 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L14 DefaultBuildSettings = BuildSettingsVersion.Latest`
- `L15 LinkType = TargetLinkType.Monolithic`
- `L17 LaunchModuleName = "BuildPatchTool"`
- `L18 bLegalToDistributeBinary = true`
- `L19 UndecoratedConfiguration = UnrealTargetConfiguration.Shipping`
- `L21 bCompileAgainstEngine = false`
- `L22 bCompileAgainstCoreUObject = false`
- `L23 bCompileAgainstApplicationCore = false`
- `L24 bBuildDeveloperTools = false`
- `L25 bUseLoggingInShipping = true`
- `L26 bUseChecksInShipping = true`
- `L27 bIsBuildingConsoleApplication = true`
- `L28 bHasExports = false`
- `L29 bWithServerCode = false`
- `L30 bForceDisableAutomationTests = true`
- `L32 GlobalDefinitions.Add () "DISABLE_CWD_CHANGES=1"`
- `L33 GlobalDefinitions.Add () "UE_DONT_USE_DEFAULT_OUTPUT_DEVICES=1"`
- `L36 GlobalDefinitions.Add () "NOINITCRASHREPORTER=1"`
- `L39 GlobalDefinitions.Add () "DISABLE_AUDIO_MCP_MODULES=1"`
- `L42 GlobalDefinitions.Add () string.Format("PORTAL_CHANGELIST={0}", Target.Version.Changelist)`
- `L43 GlobalDefinitions.Add () string.Format("PORTAL_BRANCH_NAME=\"{0}\"", Target.Version.BranchName)`

### `BuildStorageToolTarget` — `Engine/Source/Programs/BuildStorageTool/BuildStorageTool.Target.cs`

- `L11 Type = TargetType.Program`
- `L12 LinkType = TargetLinkType.Monolithic`
- `L13 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L14 LaunchModuleName = "BuildStorageTool"`
- `L16 bUseXGEController = false`
- `L17 bLoggingToMemoryEnabled = true`
- `L18 bUseLoggingInShipping = true`
- `L19 bCompileWithAccessibilitySupport = false`
- `L20 bWithServerCode = false`
- `L21 bCompileNavmeshClusterLinks = false`
- `L22 bCompileNavmeshSegmentLinks = false`
- `L23 bCompileRecast = false`
- `L24 bCompileICU = true`
- `L25 bWithLiveCoding = false`
- `L26 bBuildDeveloperTools = false`
- `L27 bBuildWithEditorOnlyData = false`
- `L28 bCompileAgainstEngine = false`
- `L29 bCompileAgainstCoreUObject = true`
- `L30 bCompileAgainstApplicationCore = true`
- `L31 bUsesSlate = true`
- `L32 bForceDisableAutomationTests = true`
- `L34 bIsBuildingConsoleApplication = false`
- `L36 WindowsPlatform.bUseBundledDbgHelp = false`
- `L37 WindowsPlatform.bPixProfilingEnabled = false`
- `L38 WindowsPlatform.bMergeIdenticalCOMDATs = true`
- `L39 WindowsPlatform.bStripUnreferencedSymbols = true`
- `L41 GlobalDefinitions.Add () "WITH_AUTOMATION_TESTS=0"`
- `L42 GlobalDefinitions.Add () "WITH_AUTOMATION_WORKER=0"`

### `CSVToTelemetryTarget` — `Engine/Source/Programs/CSVTools/CSVToTelemetry/CSVToTelemetry.Target.cs`

- `L10 Type = TargetType.Program`
- `L11 LinkType = TargetLinkType.Modular`
- `L12 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L13 LaunchModuleName = "CSVToTelemetry"`
- `L15 bUseXGEController = false`
- `L16 bCompileFreeType = false`
- `L17 bLoggingToMemoryEnabled = false`
- `L18 bUseLoggingInShipping = true`
- `L19 bCompileWithAccessibilitySupport = false`
- `L20 bCompileWithPluginSupport = true`
- `L21 bIncludePluginsForTargetPlatforms = true`
- `L22 bWithServerCode = false`
- `L23 bCompileNavmeshClusterLinks = false`
- `L24 bCompileNavmeshSegmentLinks = false`
- `L25 bCompileRecast = false`
- `L26 bCompileICU = false`
- `L27 bWithLiveCoding = false`
- `L28 bBuildDeveloperTools = false`
- `L29 bBuildWithEditorOnlyData = true`
- `L30 bCompileAgainstEngine = false`
- `L31 bCompileAgainstCoreUObject = true`
- `L32 bCompileAgainstApplicationCore = true`
- `L33 bUsesSlate = false`
- `L34 bIsBuildingConsoleApplication = true`
- `L35 bForceBuildTargetPlatforms = true`
- `L36 bNeedsExtraShaderFormats = true`
- `L37 bAreTargetSDKVersionsRelevantOverride = false`
- `L39 WindowsPlatform.bUseBundledDbgHelp = false`
- `L40 WindowsPlatform.bPixProfilingEnabled = false`
- `L41 WindowsPlatform.bMergeIdenticalCOMDATs = true`
- `L42 WindowsPlatform.bStripUnreferencedSymbols = true`
- `L44 bEnableTrace = true`
- `L45 GlobalDefinitions.Add () "UE_EXTERNAL_PROFILING_ENABLED=0"`

### `ChaosPhysicsTestsTarget` — `Engine/Source/Programs/ChaosPhysicsTests/ChaosPhysicsTests.Target.cs`

- `L10 TestTargetRules.bTestsRequireEngine = true`

### `ChaosSpatialPartitionsTestsTarget` — `Engine/Source/Programs/ChaosSpatialPartitionsTests/ChaosSpatialPartitionsTests.Target.cs`

- `L10 TestTargetRules.bTestsRequireEngine = true`
- `L11 bWithLowLevelTestsOverride = true`

### `ChaosUserDataPTTestsTarget` — `Engine/Source/Programs/ChaosUserDataPTTests/ChaosUserDataPTTests.Target.cs`

- `_(no statements parsed)_`

### `ChaosVisualDebuggerTarget` — `Engine/Source/Programs/ChaosVisualDebugger/ChaosVisualDebugger.Target.cs`

- `L11 Type = TargetType.Program`
- `L12 LinkType = TargetLinkType.Monolithic`
- `L13 LaunchModuleName = "ChaosVisualDebugger"`
- `L14 BuildEnvironment = TargetBuildEnvironment.Unique`
- `L16 DefaultBuildSettings = BuildSettingsVersion.Latest`
- `L17 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L19 bIsBuildingConsoleApplication = false`
- `L21 bCompileAgainstCoreUObject = true`
- `L22 bCompileAgainstEngine = true`
- `L23 bCompileAgainstEditor = true`
- `L24 bBuildWithEditorOnlyData = true`
- `L25 bUsesSlate = true`
- `L26 bEnableTrace = true`
- `L27 bUseLoggingInShipping = true`
- `L29 bCompileWithPluginSupport = true`
- `L30 bBuildDeveloperTools = true`
- `L33 bCompilePython = false`
- `L34 bCompileICU = true`
- `L35 bCompileRecast = false`
- `L36 bUseGameplayDebugger = false`
- `L37 bCompileNavmeshClusterLinks = false`
- `L38 bCompileNavmeshSegmentLinks = false`
- `L39 bWithLiveCoding = false`
- `L40 bIncludePluginsForTargetPlatforms = false`
- `L42 bCompileChaosVisualDebuggerSupport = true`
- `L44 OptedInModulePlatforms = new UnrealTargetPlatform[] { UnrealTargetPlatform.Win64 }`
- `L46 AdditionalPlugins.AddRange () new string[] { "ChaosVD", "GeometryProcessing", "PropertyAccessEditor" }`
- `L53 EnablePlugins.Add () "GeometryProcessing"`
- `L54 EnablePlugins.Add () "ChaosVD"`
- `L55 EnablePlugins.Add () "PropertyAccessEditor"`
- `L57 GlobalDefinitions.Add () "AUTOSDKS_ENABLED=0"`
- `L58 GlobalDefinitions.Add () "ASSETREGISTRY_FORCE_PREMADE_REGISTRY_IN_EDITOR=1"`
- `L59 GlobalDefinitions.Add () "UE_IS_COOKED_EDITOR=1"`
- `L60 GlobalDefinitions.Add () "UE_FORCE_USE_PAKS=1"`
- `L61 GlobalDefinitions.Add () "UE_FORCE_USE_IOSTORE=0"`
- `L65 GlobalDefinitions.Add () "UE_ALLOW_SHADER_COMPILING_BASED_ON_SHADER_DIRECTORY_EXISTENCE=1"`
- `L67 GlobalDefinitions.Add () "UE_TRACE_SERVER_LAUNCH_ENABLED=1"`
- `L68 GlobalDefinitions.Add () "UE_TRACE_SERVER_CONTROLS_ENABLED=1"`

### `CmdLinkTarget` — `Engine/Source/Programs/CmdLink/CmdLink.Target.cs`

- `L12 Type = TargetType.Program`
- `L13 LinkType = TargetLinkType.Monolithic`
- `L14 LaunchModuleName = "CmdLink"`
- `L15 bLegalToDistributeBinary = true`
- `L20 bBuildDeveloperTools = false`
- `L23 bCompileICU = false`
- `L26 bCompileAgainstEngine = false`
- `L27 bCompileAgainstCoreUObject = false`
- `L28 bCompileAgainstApplicationCore = false`
- `L29 bBuildWithEditorOnlyData = false`
- `L30 bCompileCEF3 = false`
- `L33 bIsBuildingConsoleApplication = true`

### `CrashReportClientTarget` — `Engine/Source/Programs/CrashReportClient/CrashReportClient.Target.cs`

- `L31 Type = TargetType.Program`
- `L32 LinkType = TargetLinkType.Monolithic`
- `L33 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L34 UndecoratedConfiguration = UnrealTargetConfiguration.Shipping`
- `L36 LaunchModuleName = "CrashReportClient"`
- `L40 ExtraModuleNames.Add () "EditorStyle" [if if (bBuildEditor == true && Target.Platform != UnrealTargetPlatform.Linux)]`
- `L43 bLegalToDistributeBinary = true`
- `L45 bBuildDeveloperTools = false`
- `L48 bCompileAgainstEngine = false`
- `L49 bCompileAgainstCoreUObject = true`
- `L50 bUseLoggingInShipping = true`
- `L54 bHasExports = false`
- `L56 bUseChecksInShipping = true`
- `L59 bEnableOSX109Support = true`
- `L62 WindowsPlatform.bUseBundledDbgHelp = false`
- `L65 GlobalDefinitions.Add () "UE_TASKGRAPH_THREAD_LIMIT=5"`
- `L67 GlobalDefinitions.Add () "NOINITCRASHREPORTER=1"`
- `L73 GlobalDefinitions.AddRange () SetupConfiguredDefines( DefaultUrl, DefaultCompanyName, TelemetryUrl, TelemetryKey) [if if (bSetConfiguredDefinitions)]`
- `L87 Definitions.Add () $"CRC_DEFAULT_URL=\"{DefaultUrl}\"" [if if (!string.IsNullOrEmpty(DefaultUrl))]`
- `L92 Definitions.Add () $"CRC_DEFAULT_COMPANY_NAME=\"{DefaultCompanyName}\"" [if if (!string.IsNullOrEmpty(DefaultCompanyName))]`
- `L97 Definitions.Add () $"CRC_TELEMETRY_URL=\"{TelemetryUrl}\"" [if if(!string.IsNullOrWhiteSpace(TelemetryUrl))]`
- `L102 Definitions.Add () $"CRC_TELEMETRY_KEY=\"{TelemetryKey}\"" [if if (!string.IsNullOrWhiteSpace(TelemetryKey))]`

### `CrashReportClientEditorTarget` — `Engine/Source/Programs/CrashReportClient/CrashReportClientEditor.Target.cs`

- `L27 LaunchModuleName = "CrashReportClientEditor"`
- `L32 bBuildWithEditorOnlyData = false`
- `L33 bBuildDeveloperTools = true`
- `L37 AdditionalPlugins.Add () "UdpMessaging" [if if (bHostRecoverySvc)]`
- `L38 AdditionalPlugins.Add () "ConcertSyncServer" [if if (bHostRecoverySvc)]`
- `L39 bCompileWithPluginSupport = true [if if (bHostRecoverySvc)]`
- `L45 GlobalDefinitions.Add () "PLATFORM_SUPPORTS_MESSAGEBUS=1" [if if (bHostRecoverySvc) && if (Target.Configuration == UnrealTargetConfiguration.Shipping && LinkType == TargetLinkType.Monolithic)]`
- `L50 GlobalDefinitions.AddRange () SetupConfiguredDefines( DefaultUrl, DefaultCompanyName, TelemetryUrl, TelemetryKey)`

### `DerivedDataBuildWorkerTarget` — `Engine/Source/Programs/DerivedDataBuildWorker/DerivedDataBuildWorker.Build.cs`

- `L11 Type = TargetType.Program`
- `L12 LinkType = TargetLinkType.Monolithic`
- `L14 SolutionDirectory = "Programs/BuildWorker"`
- `L16 bLoggingToMemoryEnabled = true`
- `L17 bUseLoggingInShipping = true`
- `L19 bCompileCEF3 = false`
- `L20 bCompileFreeType = false`
- `L21 bCompileICU = false`
- `L22 bCompileWithAccessibilitySupport = false`
- `L23 bCompileWithPluginSupport = false`
- `L24 bEnableConfigSystem = false`
- `L25 bUsesSlate = false`
- `L26 bUseXGEController = false`
- `L27 bWithLiveCoding = false`
- `L28 bWithServerCode = false`
- `L30 bForceDisableAutomationTests = true`
- `L32 bIsBuildingConsoleApplication = true`
- `L33 bBuildWithEditorOnlyData = true`
- `L34 bBuildDeveloperTools = false`
- `L35 bCompileAgainstEngine = false`
- `L36 bCompileAgainstCoreUObject = false`
- `L37 bCompileAgainstApplicationCore = false`
- `L41 WindowsPlatform.bUseBundledDbgHelp = false`
- `L42 WindowsPlatform.bPixProfilingEnabled = false`
- `L43 WindowsPlatform.bMergeIdenticalCOMDATs = true`
- `L44 WindowsPlatform.bStripUnreferencedSymbols = true`
- `L47 GlobalDefinitions.Add () "ALLOW_LOG_FILE=0"`
- `L50 GlobalDefinitions.Add () "ALLOW_WINDOWS_ERROR_REPORT_LIB=0"`
- `L52 GlobalDefinitions.Add () "NOINITCRASHREPORTER=1"`
- `L54 GlobalDefinitions.Add () "UE_EXTERNAL_PROFILING_ENABLED=0"`

### `DerivedDataToolTarget` — `Engine/Source/Programs/DerivedDataTool/DerivedDataTool.Target.cs`

- `L10 Type = TargetType.Program`
- `L11 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L12 LinkType = TargetLinkType.Monolithic`
- `L13 LaunchModuleName = "DerivedDataTool"`
- `L15 bBuildDeveloperTools = false`
- `L16 bCompileAgainstApplicationCore = true`
- `L17 bCompileAgainstCoreUObject = false`
- `L18 bCompileAgainstEngine = false`
- `L19 bCompileICU = false`
- `L20 bForceDisableAutomationTests = true`
- `L21 bIsBuildingConsoleApplication = true`
- `L22 bUseLoggingInShipping = true`
- `L27 GlobalDefinitions.Add () "LLM_ENABLED_IN_CONFIG=1" [if if (Target.Configuration == UnrealTargetConfiguration.Debug \|\| Target.Configuration == UnrealTargetConfiguration.Development)]`
- `L28 GlobalDefinitions.Add () "UE_MEMORY_TAGS_TRACE_ENABLED=1" [if if (Target.Configuration == UnrealTargetConfiguration.Debug \|\| Target.Configuration == UnrealTargetConfiguration.Development)]`
- `L29 bEnableTrace = true [if if (Target.Configuration == UnrealTargetConfiguration.Debug \|\| Target.Configuration == UnrealTargetConfiguration.Development)]`

### `DiffAssetBulkDataTarget` — `Engine/Source/Programs/DiffAssetBulkData/DiffAssetBulkData.Target.cs`

- `L10 Type = TargetType.Program`
- `L11 LinkType = TargetLinkType.Modular`
- `L12 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L13 LaunchModuleName = "DiffAssetBulkData"`
- `L15 bUseXGEController = false`
- `L16 bCompileFreeType = false`
- `L17 bLoggingToMemoryEnabled = false`
- `L18 bUseLoggingInShipping = true`
- `L19 bCompileWithAccessibilitySupport = false`
- `L20 bCompileWithPluginSupport = false`
- `L21 bIncludePluginsForTargetPlatforms = false`
- `L22 bWithServerCode = false`
- `L23 bCompileNavmeshClusterLinks = false`
- `L24 bCompileNavmeshSegmentLinks = false`
- `L25 bCompileRecast = false`
- `L26 bCompileICU = false`
- `L27 bWithLiveCoding = false`
- `L28 bBuildDeveloperTools = false`
- `L29 bBuildWithEditorOnlyData = true`
- `L30 bCompileAgainstEngine = false`
- `L31 bCompileAgainstCoreUObject = true`
- `L32 bCompileAgainstApplicationCore = true`
- `L33 bUsesSlate = false`
- `L34 bIsBuildingConsoleApplication = true`
- `L35 bForceBuildTargetPlatforms = true`
- `L36 bNeedsExtraShaderFormats = false`
- `L37 bAreTargetSDKVersionsRelevantOverride = false`
- `L39 WindowsPlatform.bUseBundledDbgHelp = false`
- `L40 WindowsPlatform.bPixProfilingEnabled = false`
- `L41 WindowsPlatform.bMergeIdenticalCOMDATs = true`
- `L42 WindowsPlatform.bStripUnreferencedSymbols = true`
- `L44 bEnableTrace = true`
- `L45 GlobalDefinitions.Add () "UE_EXTERNAL_PROFILING_ENABLED=0"`

### `DumpSymsTarget` — `Engine/Source/Programs/DumpSyms/DumpSyms.Target.cs`

- `L13 Type = TargetType.Program`
- `L14 LinkType = TargetLinkType.Monolithic`
- `L15 LaunchModuleName = "DumpSyms"`
- `L18 UndecoratedConfiguration = UnrealTargetConfiguration.Shipping`
- `L21 bBuildDeveloperTools = false`
- `L24 bCompileAgainstEngine = false`
- `L25 bCompileAgainstCoreUObject = false`
- `L28 bUseLoggingInShipping = true`
- `L31 bIsBuildingConsoleApplication = true`
- `L33 bUseUnityBuild = false`
- `L37 OutputFile = Path.Combine("Binaries", "Linux", $"dump_syms{BinaryExt}")`

### `DatasmithCADWorkerTarget` — `Engine/Source/Programs/Enterprise/Datasmith/DatasmithCADWorker/DatasmithCADWorker.Target.cs`

- `L11 Type = TargetType.Program`
- `L12 LinkType = TargetLinkType.Monolithic`
- `L13 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L14 LaunchModuleName = "DatasmithCADWorker"`
- `L15 SolutionDirectory = "Programs/Datasmith"`
- `L18 bBuildDeveloperTools = false`
- `L21 bBuildWithEditorOnlyData = false`
- `L24 bCompileAgainstEngine = false`
- `L25 bCompileAgainstCoreUObject = false`
- `L26 bCompileAgainstApplicationCore = true`
- `L29 bIsBuildingConsoleApplication = true`
- `L31 bLegalToDistributeBinary = true`
- `L33 bCompileICU = false`
- `L34 bCompileCEF3 = false`
- `L37 ExeBinariesSubFolder = EngineDir + @"\Plugins\Enterprise\DatasmithCADImporter\Binaries\Win64\"`

### `DatasmithFacadeCSharpTarget` — `Engine/Source/Programs/Enterprise/Datasmith/DatasmithFacadeCSharp/DatasmithFacadeCSharp.Target.cs`

- `L13 Type = TargetType.Program`
- `L14 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L15 SolutionDirectory = Path.Combine("Programs","Datasmith")`
- `L16 bBuildInSolutionByDefault = false`
- `L18 LaunchModuleName = "DatasmithFacadeCSharp"`
- `L19 ExeBinariesSubFolder = "DatasmithFacadeCSharp"`
- `L21 bShouldCompileAsDLL = true`
- `L22 LinkType = TargetLinkType.Monolithic`
- `L24 bBuildDeveloperTools = false`
- `L25 bBuildWithEditorOnlyData = true`
- `L26 bCompileAgainstEngine = false`
- `L27 bCompileAgainstCoreUObject = true`
- `L28 bCompileICU = false`
- `L30 bUsesSlate = true`
- `L31 bHasExports = true`
- `L32 bForceEnableExceptions = true`
- `L38 GlobalDefinitions.Add () "UE_EXTERNAL_PROFILING_ENABLED=0"`
- `L41 GlobalDefinitions.Add () "NOINITCRASHREPORTER=1"`
- `L43 AddPreBuildSteps () Target.Platform`
- `L44 AddPostBuildSteps () Target.Platform`
- `L52 PreBuildSteps.Add () "echo Environment variable SWIG_DIR is not defined." [if if (string.IsNullOrEmpty(System.Environment.GetEnvironmentVariable("SWIG_DIR")))]`
- `L56 PreBuildSteps.Add () "echo Using SWIG_DIR env. variable: %SWIG_DIR%"`
- `L76 CleanCommand = string.Format("rm -f \"{0}\"", CleanupPath) [if if (TargetPlatform == UnrealTargetPlatform.Mac)]`
- `L80 PreBuildSteps.Add () CleanCommand`
- `L83 PreBuildSteps.Add () SwigCommand`
- `L89 PreBuildSteps.Add () string.Format("\"{0}\" \"{1}\"", Path.Combine(PythonDir, "Mac", "bin", "python"), Path.Combine(ProjectPath, "FacadeHeaderHelper.py")) [if if (TargetPlatform == UnrealTargetPlatform.Mac)]`
- `L93 PreBuildSteps.Add () string.Format("\"{0}\" \"{1}\"", Path.Combine(PythonDir, "Win64", "python.exe"), Path.Combine(ProjectPath, "FacadeHeaderHelper.py")) [if else]`
- `L104 PostBuildSteps.Add () string.Format("echo \"Replace {1} with {0}\"", SrcPathFiles, DstPath)`
- `L107 PostBuildSteps.Add () string.Format("del /S /Q \"{0}\"", Path.Combine(DstPath, "*.cs")) [if if (TargetPlatform == UnrealTargetPlatform.Win64)]`
- `L108 PostBuildSteps.Add () string.Format("xcopy \"{0}\" \"{1}\" /R /S /Y", SrcPathFiles, DstPath + Path.DirectorySeparatorChar) [if if (TargetPlatform == UnrealTargetPlatform.Win64)]`
- `L112 PostBuildSteps.Add () string.Format("mkdir -p \"{0}\"", DstPath) [if else if (TargetPlatform == UnrealTargetPlatform.Mac)]`
- `L113 PostBuildSteps.Add () string.Format("rm -f \"{0}\"*.cs", DstPath + Path.DirectorySeparatorChar) [if else if (TargetPlatform == UnrealTargetPlatform.Mac)]`
- `L114 PostBuildSteps.Add () string.Format("cp -R \"{0}\"*.cs \"{1}\"", SrcPath + Path.DirectorySeparatorChar, DstPath) [if else if (TargetPlatform == UnrealTargetPlatform.Mac)]`

### `DatasmithMaxBaseTarget` — `Engine/Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/DatasmithMax2022.Target.cs`

- `L14 Type = TargetType.Program`
- `L15 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L16 SolutionDirectory = "Programs/Datasmith"`
- `L17 bBuildInSolutionByDefault = false`
- `L18 bLegalToDistributeBinary = true`
- `L20 bShouldCompileAsDLL = true`
- `L21 LinkType = TargetLinkType.Monolithic`
- `L23 WindowsPlatform.ModuleDefinitionFile = "Programs/Enterprise/Datasmith/DatasmithMaxExporter/DatasmithMaxExporterWithDirectLink.def"`
- `L31 MaxSDKLocation = Path.Combine(SDKRootEnvVar, "HostWin64", "Win64", "3dsMax") [if if(StaticAnalyzer != StaticAnalyzer.None) && if (SDKRootEnvVar != null && SDKRootEnvVar != "")]`
- `L38 WindowsPlatform.Compiler = WindowsCompiler.Clang [if if(StaticAnalyzer != StaticAnalyzer.None)]`
- `L39 Console.WriteLine () "Skipping " + MaxSDKLocation [if if(StaticAnalyzer != StaticAnalyzer.None)]`
- `L40 AdditionalCompilerArguments = "-Xanalyzer,-isystem-after" + MaxSDKLocation [if if(StaticAnalyzer != StaticAnalyzer.None)]`
- `L44 WindowsPlatform.Compiler = WindowsCompiler.VisualStudio [if else]`
- `L47 bBuildDeveloperTools = false`
- `L48 bBuildWithEditorOnlyData = true`
- `L49 bCompileAgainstEngine = false`
- `L50 bCompileAgainstCoreUObject = true`
- `L51 bCompileICU = false`
- `L52 bUsesSlate = false`
- `L54 bHasExports = true`
- `L55 bForceEnableExceptions = true`
- `L58 GlobalDefinitions.Add () "UE_EXTERNAL_PROFILING_ENABLED=0"`
- `L59 GlobalDefinitions.Add () "NO_INIUTIL_USING"`
- `L62 GlobalDefinitions.Add () "NOINITCRASHREPORTER=1"`
- `L74 OutputName = string.Format("{0}-{1}-{2}", OutputName, Target.Platform, Target.Configuration) [if if (Target.Configuration != UnrealTargetConfiguration.Development)]`
- `L80 PostBuildSteps.Add () string.Format("echo Copying {0} to {1}...", SrcOutputFileName, DstOutputFileName)`
- `L81 PostBuildSteps.Add () string.Format("copy /Y \"{0}\" \"{1}\" 1>nul", SrcOutputFileName, DstOutputFileName)`
- `L83 PostBuildSteps.Add () string.Format("echo Copying {0} to {1}...", SrcOutputFileName, DstOutputFileName)`
- `L84 PostBuildSteps.Add () string.Format("copy /Y \"{0}\" \"{1}\" 1>nul", SrcOutputFileName, DstOutputFileName)`

### `DatasmithMax2022Target` — `Engine/Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/DatasmithMax2022.Target.cs`

- `L92 LaunchModuleName = "DatasmithMax2022"`
- `L93 ExeBinariesSubFolder = @"3DSMax\2022"`
- `L97 AddCopyPostBuildStep () Target`

### `DatasmithMax2023Target` — `Engine/Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/DatasmithMax2023.Target.cs`

- `L10 LaunchModuleName = "DatasmithMax2023"`
- `L11 ExeBinariesSubFolder = @"3DSMax\2023"`
- `L13 AddCopyPostBuildStep () Target`

### `DatasmithMax2024Target` — `Engine/Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/DatasmithMax2024.Target.cs`

- `L10 LaunchModuleName = "DatasmithMax2024"`
- `L11 ExeBinariesSubFolder = @"3DSMax\2024"`
- `L13 AddCopyPostBuildStep () Target`

### `DatasmithMax2025Target` — `Engine/Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/DatasmithMax2025.Target.cs`

- `L10 LaunchModuleName = "DatasmithMax2025"`
- `L11 ExeBinariesSubFolder = @"3DSMax\2025"`
- `L13 AddCopyPostBuildStep () Target`

### `DatasmithMax2026Target` — `Engine/Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/DatasmithMax2026.Target.cs`

- `L10 LaunchModuleName = "DatasmithMax2026"`
- `L11 ExeBinariesSubFolder = @"3DSMax\2026"`
- `L13 AddCopyPostBuildStep () Target`

### `DatasmithMax2027Target` — `Engine/Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/DatasmithMax2027.Target.cs`

- `L10 LaunchModuleName = "DatasmithMax2027"`
- `L11 ExeBinariesSubFolder = @"3DSMax\2027"`
- `L13 AddCopyPostBuildStep () Target`

### `DatasmithSDKTarget` — `Engine/Source/Programs/Enterprise/Datasmith/DatasmithSDK/DatasmithSDK.Target.cs`

- `L18 Type = TargetType.Program`
- `L19 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L20 DefaultBuildSettings = BuildSettingsVersion.Latest`
- `L21 SolutionDirectory = "Programs/Datasmith"`
- `L22 bBuildInSolutionByDefault = false`
- `L24 LaunchModuleName = "DatasmithSDK"`
- `L25 ExeBinariesSubFolder = "DatasmithSDK"`
- `L27 ExtraModuleNames.AddRange () new string[] { "DatasmithCore", "DatasmithExporter" }`
- `L29 LinkType = TargetLinkType.Monolithic`
- `L30 bShouldCompileAsDLL = true`
- `L32 bBuildDeveloperTools = false`
- `L33 bBuildWithEditorOnlyData = true`
- `L34 bCompileAgainstEngine = false`
- `L35 bCompileAgainstCoreUObject = true`
- `L36 bCompileICU = false`
- `L37 bUsesSlate = false`
- `L38 DebugInfo = DebugInfoMode.Full`
- `L39 bUsePDBFiles = true`
- `L40 bHasExports = true`
- `L41 bIsBuildingConsoleApplication = true`
- `L63 PostBuildSteps.Add () string.Format("echo Creating directories to export to\n") [if if (Platform != UnrealTargetPlatform.Win64)]`
- `L66 PostBuildSteps.Add () string.Format("mkdir -p {0}\n", Directory) [if if (Platform != UnrealTargetPlatform.Win64) && foreach (string Directory in Directories)]`
- `L69 PostBuildCopy = PostBuildCopyUnix [if if (Platform != UnrealTargetPlatform.Win64)]`
- `L72 AddPostBuildSteps () `
- `L77 GlobalDefinitions.Add () "ALLOW_UDP_MESSAGING_SHIPPING=1" [if if (BuildEnvironment == TargetBuildEnvironment.Unique)]`
- `L78 GlobalDefinitions.Add () "PLATFORM_SUPPORTS_MESSAGEBUS=1" [if if (BuildEnvironment == TargetBuildEnvironment.Unique)]`
- `L83 PostBuildSteps.Add () string.Format("echo Copying {0}{2} to {1}", SrcPath, DestPath, Files)`
- `L84 PostBuildSteps.Add () string.Format(@"call $(EngineDir)\Source\Programs\Enterprise\Datasmith\DatasmithSDK\CopyCmd.bat {0} {1} {2}", SrcPath, DestPath, Files)`
- `L89 SrcPath = SrcPath.Replace("\\", "/")`
- `L90 DestPath = DestPath.Replace("\\", "/")`
- `L91 PostBuildSteps.Add () string.Format("echo Copying \"{0}\" to {1}\n", SrcPath, DestPath)`
- `L93 PostBuildSteps.Add () string.Format("cp -R -f {0}/{2} {1} \|\| true\n", SrcPath, DestPath, Files)`
- `L98 SrcPath = SrcPath.Replace("\\", "/")`
- `L99 DestPath = DestPath.Replace("\\", "/")`
- `L100 PostBuildSteps.Add () string.Format("echo Copying \"{0}\" to {1}\n", SrcPath, DestPath)`
- `L102 PostBuildSteps.Add () string.Format("cp -R -f {0} {1} \|\| true\n", SrcPath, DestPath)`
- `L126 PostBuildSteps.Add () string.Format("echo Creating directories to export to\n") [if if (Platform != UnrealTargetPlatform.Win64)]`
- `L129 PostBuildSteps.Add () string.Format("mkdir -p {0}\n", Directory) [if if (Platform != UnrealTargetPlatform.Win64) && foreach (string Directory in Directories)]`
- `L132 PostBuildCopy = PostBuildCopyUnix [if if (Platform != UnrealTargetPlatform.Win64)]`
- `L134 PostBuildCopyUnix () @"$(EngineDir)/Content/Slate", Path.Combine(DstDatasmithSDK, "Engine/Content/") [if if (Platform != UnrealTargetPlatform.Win64)]`
- `L135 PostBuildCopyUnix () @"$(EngineDir)/Shaders/StandaloneRenderer/OpenGL", Path.Combine(DstDatasmithSDK, "Engine/Shaders/StandaloneRenderer") [if if (Platform != UnrealTargetPlatform.Win64)]`
- `L139 PostBuildSteps.Add () string.Format("mkdir {0}\n", Path.Combine(DstDatasmithSDK, "Engine\\Content\\Binary")) [if else]`
- `L140 PostBuildCopyWin64 () @"$(EngineDir)\Content\Slate\", Path.Combine(DstDatasmithSDK, "Engine\\Content\\"), "" [if else]`
- `L141 PostBuildCopyWin64 () @"$(EngineDir)\Shaders\StandaloneRenderer\D3D\", Path.Combine(DstDatasmithSDK, "Engine\\Shaders\\StandaloneRenderer\\D3D\\"), "" [if else]`
- `L167 PostBuildCopy () ToCopy.Item1, ToCopy.Item2, ToCopy.Item3 [if foreach ((string, string, string) ToCopy in FilesToCopy)]`

### `EpicWebHelperTarget` — `Engine/Source/Programs/EpicWebHelper/EpicWebHelper.Target.cs`

- `L13 Type = TargetType.Program`
- `L14 LinkType = TargetLinkType.Monolithic`
- `L15 LaunchModuleName = "EpicWebHelper"`
- `L17 DefaultBuildSettings = BuildSettingsVersion.Latest`
- `L18 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L21 UndecoratedConfiguration = UnrealTargetConfiguration.Shipping`
- `L27 PostBuildSteps.Add () string.Format("echo Creating helper syminks") [if if (Target.Platform == UnrealTargetPlatform.Mac)]`
- `L31 PostBuildSteps.Add () string.Format("cd $(EngineDir)/Binaries/$(TargetPlatform); if [ ! -h \"EpicWebHelper ({0})\" ]; then ln -s \"EpicWebHelper\" \"EpicWebHelper ({1})\"; fi", Helpe [if if (Target.Platform == UnrealTargetPlatform.Mac) && foreach( string HelperType in HelperTypes)]`
- `L38 bBuildDeveloperTools = false`
- `L41 bCompileAgainstEngine = false`
- `L42 bCompileAgainstCoreUObject = false`
- `L43 bBuildWithEditorOnlyData = true`
- `L51 bIsBuildingConsoleApplication = true [if if (Target.Platform == UnrealTargetPlatform.Mac)]`
- `L56 bIsBuildingConsoleApplication = false [if else]`
- `L60 GlobalDefinitions.Add () "ALLOW_LOG_FILE=0"`
- `L63 bEnableOSX109Support = true`

### `GPUReshapeBootstrapperTarget` — `Engine/Source/Programs/GPUReshape/Source/GPUReshapeBootstrapper.Target.cs`

- `L10 Type = TargetType.Program`
- `L12 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L13 LinkType = TargetLinkType.Monolithic`
- `L15 bCompileICU = false`
- `L16 bBuildDeveloperTools = false`
- `L17 bCompileAgainstEngine = false`
- `L18 bCompileAgainstCoreUObject = false`
- `L19 bCompileAgainstApplicationCore = false`
- `L20 bIsBuildingConsoleApplication = true`
- `L22 SolutionDirectory = "Programs/GPUReshape"`
- `L23 LaunchModuleName = "GPUReshapeBootstrapper"`

### `GeometryProcessingTarget` — `Engine/Source/Programs/GeometryProcessing/GeometryProcessing.Target.cs`

- `L11 Type = TargetType.Program`
- `L12 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L13 LinkType = TargetLinkType.Monolithic`
- `L14 LaunchModuleName = "GeometryProcessing"`
- `L17 bBuildDeveloperTools = false`
- `L19 bBuildWithEditorOnlyData = true`
- `L22 bCompileAgainstEngine = false`
- `L23 bCompileAgainstCoreUObject = false`
- `L24 bCompileAgainstApplicationCore = false`
- `L25 bCompileICU = false`
- `L31 bIsBuildingConsoleApplication = true`

### `HeadlessChaosTarget` — `Engine/Source/Programs/HeadlessChaos/HeadlessChaos.Target.cs`

- `L10 bHasExports = false`
- `L12 GlobalDefinitions.Add () "CHAOS_SERIALIZE_OUT=1"`
- `L15 bDebugBuildsActuallyUseDebugCRT = false`
- `L18 GlobalDefinitions.Add () "CHAOS_CONSTRAINTHANDLE_DEBUG_ENABLED=1"`
- `L19 BuildEnvironment = TargetBuildEnvironment.Unique`
- `L20 bWarningsAsErrors = true`

### `HeadlessChaosPerfTarget` — `Engine/Source/Programs/HeadlessChaosPerf/HeadlessChaosPerf.Target.cs`

- `L11 Type = TargetType.Program`
- `L12 LinkType = TargetLinkType.Monolithic`
- `L14 ExeBinariesSubFolder = "NotForLicensees"`
- `L15 LaunchModuleName = "HeadlessChaosPerf"`
- `L17 bBuildDeveloperTools = false`
- `L20 bCompileAgainstEngine = false`
- `L21 bCompileAgainstCoreUObject = true`
- `L23 bHasExports = false`
- `L25 bUseLoggingInShipping = true`
- `L28 bIsBuildingConsoleApplication = true`
- `L30 GlobalDefinitions.Add () "CHAOS_SERIALIZE_OUT=1"`
- `L31 GlobalDefinitions.Add () "CSV_PROFILER=1"`

### `HordeTestTarget` — `Engine/Source/Programs/Horde/Samples/HordeTest/HordeTest.Target.cs`

- `L11 Type = TargetType.Program`
- `L12 LinkType = TargetLinkType.Monolithic`
- `L13 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L14 LaunchModuleName = "HordeTest"`
- `L16 bCompileICU = false`
- `L19 bBuildDeveloperTools = false`
- `L22 bCompileAgainstEngine = false`
- `L23 bCompileAgainstCoreUObject = false`
- `L26 bUseLoggingInShipping = true`
- `L29 bIsBuildingConsoleApplication = true`
- `L31 WindowsPlatform.bPixProfilingEnabled = false`

### `UnrealLaunchDaemonTarget` — `Engine/Source/Programs/IOS/UnrealLaunchDaemon/UnrealLaunchDaemon.Target.cs`

- `L11 Type = TargetType.Program`
- `L12 LinkType = TargetLinkType.Monolithic`
- `L13 bUsesSlate = false`
- `L16 AdditionalPlugins.Add () "UdpMessaging"`
- `L18 LaunchModuleName = "UnrealLaunchDaemon"`
- `L20 bBuildDeveloperTools = false`
- `L21 bCompileAgainstEngine = false`
- `L23 bHasExports = false`

### `InterchangeWorkerTarget` — `Engine/Source/Programs/InterchangeWorker/InterchangeWorker.Target.cs`

- `L12 Type = TargetType.Program`
- `L13 LinkType = TargetLinkType.Monolithic`
- `L14 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L15 LaunchModuleName = "InterchangeWorker"`
- `L16 SolutionDirectory = "Programs/InterchangeWorker"`
- `L19 bBuildDeveloperTools = false`
- `L22 bBuildWithEditorOnlyData = false`
- `L25 bCompileAgainstEngine = false`
- `L26 bCompileAgainstCoreUObject = true`
- `L27 bCompileAgainstApplicationCore = true`
- `L30 bIsBuildingConsoleApplication = true`
- `L32 bLegalToDistributeBinary = true`
- `L34 bCompileICU = false`
- `L35 bCompileCEF3 = false`
- `L37 GlobalDefinitions.Add () "USE_LOCALIZED_PACKAGE_CACHE=0"`

### `IoStoreDependencyViewerTarget` — `Engine/Source/Programs/IoStoreDependencyViewer/IoStoreDependencyViewer.Target.cs`

- `L11 Type = TargetType.Program`
- `L12 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L13 LinkType = TargetLinkType.Monolithic`
- `L14 LaunchModuleName = "IoStoreDependencyViewer"`
- `L17 bCompileAgainstEngine = false`
- `L18 bCompileAgainstCoreUObject = true`
- `L19 bCompileAgainstApplicationCore = true`
- `L22 bIsBuildingConsoleApplication = true`
- `L25 bUseLoggingInShipping = true`
- `L28 bCompileWithPluginSupport = false`
- `L29 bIncludePluginsForTargetPlatforms = false`
- `L32 bForceEnableExceptions = true`

### `IasToolTarget` — `Engine/Source/Programs/IoStoreOnDemand/IasTool.Target.cs`

- `L10 Type = TargetType.Program`
- `L11 LinkType = TargetLinkType.Monolithic`
- `L12 LaunchModuleName = "IasTool"`
- `L13 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L15 bBuildDeveloperTools = false`
- `L16 bBuildWithEditorOnlyData = false`
- `L17 bCompileAgainstApplicationCore = false`
- `L18 bCompileAgainstCoreUObject = false`
- `L19 bCompileAgainstEngine = false`
- `L20 bCompileICU = false`
- `L21 bCompileNavmeshClusterLinks = false`
- `L22 bCompileNavmeshSegmentLinks = false`
- `L23 bCompileRecast = false`
- `L24 bCompileWithPluginSupport = true`
- `L25 bForceEnableExceptions = true`
- `L26 bIsBuildingConsoleApplication = true`
- `L27 bUsesSlate = false`
- `L28 bWithLiveCoding = false`
- `L29 bWithServerCode = false`
- `L31 bEnableTrace = true`

### `LiveCodingConsoleTarget` — `Engine/Source/Programs/LiveCodingConsole/LiveCodingConsole.Target.cs`

- `L17 Type = TargetType.Program`
- `L18 LinkType = TargetLinkType.Monolithic`
- `L19 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L20 LaunchModuleName = "LiveCodingConsole"`
- `L22 bBuildDeveloperTools = false`
- `L23 bCompileWithPluginSupport = true`
- `L24 bIncludePluginsForTargetPlatforms = true`
- `L25 bWithLiveCoding = true`
- `L28 bBuildWithEditorOnlyData = true`
- `L31 bCompileAgainstApplicationCore = true`
- `L32 bCompileAgainstCoreUObject = true`
- `L33 bCompileAgainstEngine = false`
- `L36 bCompileICU = true`

### `LiveLinkFbxProviderTarget` — `Engine/Source/Programs/LiveLinkFbxProvider/Source/LiveLinkFbxProvider.Target.cs`

- `L11 Type = TargetType.Program`
- `L12 LinkType = TargetLinkType.Monolithic`
- `L14 DefaultBuildSettings = BuildSettingsVersion.Latest`
- `L15 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L17 SolutionDirectory = "Programs/LiveLink"`
- `L18 AdditionalPlugins.Add () "UdpMessaging"`
- `L20 LaunchModuleName = "LiveLinkFbxProvider"`
- `L23 bCompileAgainstCoreUObject = true`
- `L24 bCompileAgainstEngine = false`
- `L25 bBuildDeveloperTools = false`
- `L26 bCompileWithPluginSupport = false`
- `L29 bBuildWithEditorOnlyData = true`
- `L32 bIsBuildingConsoleApplication = true`

### `LiveLinkHubTarget` — `Engine/Source/Programs/LiveLinkHub/Source/LiveLinkHub.Target.cs`

- `L23 Type = TargetType.Editor`
- `L24 bExplicitTargetForType = true`
- `L25 bGenerateProgramProject = true`
- `L27 SolutionDirectory = "Programs/LiveLink"`
- `L28 LaunchModuleName = "LiveLinkHubLauncher"`
- `L30 DefaultBuildSettings = BuildSettingsVersion.Latest`
- `L31 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L33 MacPlatform.bForceTargetNameAsExeName = true`
- `L37 EnablePlugins.AddRange () new string[] { "ACLPlugin", "AudioCaptureTimecodeProvider", "LiveLink", "LiveLinkHub", "PluginBrowser", "LiveLinkCamera", "LiveLinkLens", "LensComponent", "Live`
- `L80 EnablePlugins.AddRange () new string[] { "MetaHumanLiveLink", "WmfMedia", "AvfMedia", "StreamingADA" } [if if (bEnableMetaHumanLiveLinkPlugin)]`
- `L93 OptedInModulePlatforms = new UnrealTargetPlatform[] { Target.Platform } [if if (bSingleModulePlatform)]`
- `L96 bAllowEnginePluginsEnabledByDefault = false`
- `L97 bBuildAdditionalConsoleApp = false`
- `L101 OutputFile = "Binaries/" + Platform.ToString() + "/" + BaseExeName`
- `L104 OutputFile += "-" + Platform.ToString() + "-" + Configuration.ToString() [if if (Configuration != UndecoratedConfiguration)]`
- `L108 OutputFile += ".exe" [if if (Platform == UnrealTargetPlatform.Win64)]`
- `L124 DirectoryReference.CreateDirectory () ReceiptDestPath.Directory`
- `L126 PostBuildSteps.Add () $"echo Copying \"{ReceiptSrcPath}\" to \"{ReceiptDestPath}\""`
- `L130 PostBuildSteps.Add () $"copy /Y \"{ReceiptSrcPath}\" \"{ReceiptDestPath}\"" [if if (Platform == UnrealTargetPlatform.Win64)]`
- `L134 PostBuildSteps.Add () $"cp -a \"{ReceiptSrcPath}\" \"{ReceiptDestPath}\"" [if else]`

### `FoundationTestsTarget` — `Engine/Source/Programs/LowLevelTests/FoundationTests/FoundationTests.Target.cs`

- `L12 bWithLowLevelTestsOverride = true`
- `L13 bCompileWithPluginSupport = true`
- `L15 bCompileAgainstCoreUObject = true`
- `L17 bCompileAgainstApplicationCore = true`
- `L20 bBuildWithEditorOnlyData = bIsEditorPlatform && (Target.Configuration == UnrealTargetConfiguration.Debug \|\| Target.Configuration == UnrealTargetConfiguration.Development)`

### `MathCoreTestsTarget` — `Engine/Source/Programs/LowLevelTests/MathCoreTests/MathCoreTests.Target.cs`

- `_(no statements parsed)_`

### `StateStreamTestsTarget` — `Engine/Source/Programs/LowLevelTests/StateStreamTests/StateStreamTests.Target.cs`

- `L10 bCompileWithPluginSupport = false`
- `L11 bCompileAgainstCoreUObject = true`
- `L13 bBuildWithEditorOnlyData = Target.Platform.IsInGroup(UnrealPlatformGroup.Desktop) && (Target.Configuration == UnrealTargetConfiguration.Debug \|\| Target.Configuration == UnrealTargetConfig`
- `L16 GlobalDefinitions.Add () "UE_STATESTREAM_TIME_TYPE=int64"`

### `DsymExporterTarget` — `Engine/Source/Programs/Mac/DsymExporter/DsymExporter.Target.cs`

- `L11 Type = TargetType.Program`
- `L12 LinkType = TargetLinkType.Monolithic`
- `L13 LaunchModuleName = "DsymExporter"`
- `L15 bBuildDeveloperTools = false`
- `L18 bCompileAgainstEngine = false`
- `L21 bHasExports = false`
- `L23 bCompileAgainstCoreUObject = false`
- `L26 bIsBuildingConsoleApplication = true`

### `UnrealAtoSTarget` — `Engine/Source/Programs/Mac/UnrealAtoS/UnrealAtoS.Target.cs`

- `L11 Type = TargetType.Program`
- `L12 LinkType = TargetLinkType.Monolithic`
- `L13 LaunchModuleName = "UnrealAtoS"`
- `L15 bBuildDeveloperTools = false`
- `L18 bCompileAgainstEngine = false`
- `L21 bHasExports = false`
- `L23 bCompileAgainstCoreUObject = false`
- `L26 bIsBuildingConsoleApplication = true`

### `UnrealEditorServicesTarget` — `Engine/Source/Programs/Mac/UnrealEditorServices/UnrealEditorServices.Target.cs`

- `L11 Type = TargetType.Program`
- `L12 LinkType = TargetLinkType.Monolithic`
- `L13 LaunchModuleName = "UnrealEditorServices"`
- `L15 bBuildDeveloperTools = false`
- `L17 bCompileICU = false`
- `L19 bBuildWithEditorOnlyData = false`
- `L22 bCompileAgainstEngine = false`
- `L23 bCompileAgainstCoreUObject = false`
- `L26 bEnableOSX109Support = true`

### `MassTestsTarget` — `Engine/Source/Programs/MassTests/MassTests.Target.cs`

- `L10 bUsePlatformFileStub = true`
- `L11 bMockEngineDefaults = true`
- `L13 bCompileAgainstEngine = true`
- `L14 bCompileAgainstApplicationCore = true`
- `L16 bTestsRequireEngine = true`

### `NetworkPredictionTestsTarget` — `Engine/Source/Programs/NetworkPredictionTests/NetworkPredictionTests.Target.cs`

- `L10 bTestsRequireEngine = true`
- `L11 bTestsRequireApplicationCore = true`
- `L12 bUsePlatformFileStub = true`
- `L13 bMockEngineDefaults = true`
- `L15 bUsesSlate = false`
- `L17 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`

### `PlainPropsTestsTarget` — `Engine/Source/Programs/PlainPropsTests/PlainPropsTests.Target.cs`

- `L11 bWithLowLevelTestsOverride = true`
- `L12 bCompileWithPluginSupport = true`
- `L13 bCompileAgainstCoreUObject = false`
- `L20 bBuildWithEditorOnlyData = Target.Platform.IsInGroup(UnrealPlatformGroup.Desktop) && (Target.Configuration == UnrealTargetConfiguration.Debug \|\| Target.Configuration == UnrealTargetConfig`

### `ReplicationSystemLowLevelTestsTarget` — `Engine/Source/Programs/ReplicationSystemLowLevelTests/ReplicationSystemLowLevelTests.Target.cs`

- `L10 bTestsRequireEngine = true`
- `L11 bTestsRequireApplicationCore = true`
- `L12 bTestsRequireCoreUObject = true`
- `L13 bUsePlatformFileStub = true`
- `L14 bMockEngineDefaults = true`
- `L16 bUsesSlate = false`
- `L18 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L21 bWithPushModel = true`
- `L23 bEnableTrace = true`
- `L30 GlobalDefinitions.Add () "UE_NET_TEST_FAKE_REP_TAGS=1"`
- `L32 GlobalDefinitions.Add () "LOADTIMEPROFILERTRACE_ENABLED=0"`
- `L33 GlobalDefinitions.Add () "UE_WITH_REMOTE_OBJECT_HANDLE=0"`

### `ShaderAuditViewerTarget` — `Engine/Source/Programs/ShaderAuditViewer/ShaderAuditViewer.Target.cs`

- `L10 Type = TargetType.Program`
- `L11 LinkType = TargetLinkType.Monolithic`
- `L12 LaunchModuleName = "ShaderAuditViewer"`
- `L13 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L14 DefaultBuildSettings = BuildSettingsVersion.Latest`
- `L17 bCompileAgainstEngine = false`
- `L18 bCompileAgainstCoreUObject = true`
- `L19 bBuildDeveloperTools = true`
- `L20 bBuildWithEditorOnlyData = true`
- `L21 bCompileICU = false`
- `L22 bIsBuildingConsoleApplication = true`
- `L23 bHasExports = false`

### `ShaderBuildWorkerTarget` — `Engine/Source/Programs/ShaderBuildWorker/ShaderBuildWorker.Target.cs`

- `L12 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L13 BuildEnvironment = TargetBuildEnvironment.UniqueIfNeeded`
- `L14 LinkType = TargetLinkType.Modular`
- `L15 LaunchModuleName = "ShaderBuildWorker"`
- `L17 bCompileAgainstApplicationCore = true`
- `L20 bForceBuildShaderFormats = true`
- `L24 GlobalDefinitions.Add () "LLM_ENABLED_IN_CONFIG=1" [if if (bShaderCompilerWorkerTrace)]`
- `L25 GlobalDefinitions.Add () "UE_MEMORY_TAGS_TRACE_ENABLED=1" [if if (bShaderCompilerWorkerTrace)]`
- `L26 bEnableTrace = true [if if (bShaderCompilerWorkerTrace)]`

### `ShaderCompileWorkerTarget` — `Engine/Source/Programs/ShaderCompileWorker/ShaderCompileWorker.Target.cs`

- `L12 Type = TargetType.Program`
- `L13 LinkType = TargetLinkType.Modular`
- `L14 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L15 BuildEnvironment = TargetBuildEnvironment.UniqueIfNeeded`
- `L17 LaunchModuleName = "ShaderCompileWorker"`
- `L30 PostBuildSteps.Add () string.Format("echo Copying {0} to {1}", SrcPath, DestPath) [if if (bUseXGEController && (Target.Platform == UnrealTargetPlatform.Win64) && Configuration == UnrealTargetConfiguration.Development) && foreach (UnrealArch Arch in Target.Architectures.Architectures)]`
- `L31 PostBuildSteps.Add () string.Format("copy /Y /B \"{0}\" /B \"{1}\" >nul:", SrcPath, DestPath) [if if (bUseXGEController && (Target.Platform == UnrealTargetPlatform.Win64) && Configuration == UnrealTargetConfiguration.Development) && foreach (UnrealArch Arch in Target.Architectures.Architectures)]`
- `L33 AdditionalBuildProducts.Add () DestPath [if if (bUseXGEController && (Target.Platform == UnrealTargetPlatform.Win64) && Configuration == UnrealTargetConfiguration.Development) && foreach (UnrealArch Arch in Target.Architectures.Architectures)]`
- `L40 bBuildDeveloperTools = false`
- `L43 bCompileICU = false`
- `L46 bCompileAgainstEngine = false`
- `L47 bCompileAgainstCoreUObject = false`
- `L48 bBuildWithEditorOnlyData = true`
- `L49 bCompileCEF3 = false`
- `L52 bForceBuildShaderFormats = true`
- `L55 bIsBuildingConsoleApplication = true`
- `L58 GlobalDefinitions.Add () "ALLOW_LOG_FILE=0"`
- `L62 bLoggingToMemoryEnabled = true`
- `L63 bUseLoggingInShipping = true`
- `L66 GlobalDefinitions.Add () "ALLOW_WINDOWS_ERROR_REPORT_LIB=0"`
- `L69 GlobalDefinitions.Add () "UE_EXTERNAL_PROFILING_ENABLED=0"`
- `L72 GlobalDefinitions.Add () "NOINITCRASHREPORTER=1"`
- `L76 GlobalDefinitions.Add () "LLM_ENABLED_IN_CONFIG=1" [if if (bShaderCompilerWorkerTrace)]`
- `L77 GlobalDefinitions.Add () "UE_MEMORY_TAGS_TRACE_ENABLED=1" [if if (bShaderCompilerWorkerTrace)]`
- `L78 bEnableTrace = true [if if (bShaderCompilerWorkerTrace)]`

### `DotNetPerforceLibTarget` — `Engine/Source/Programs/Shared/EpicGames.Perforce.Native/DotNetPerforceLib.Target.cs`

- `L11 Type = TargetType.Program`
- `L12 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L13 LinkType = TargetLinkType.Monolithic`
- `L14 LaunchModuleName = "DotNetPerforceLib"`
- `L16 bShouldCompileAsDLL = true`
- `L18 bBuildDeveloperTools = false`
- `L19 bCompileICU = false`
- `L20 bBuildWithEditorOnlyData = false`
- `L21 bCompileAgainstEngine = false`
- `L22 bCompileAgainstCoreUObject = false`
- `L27 OutputFile = $"Binaries/DotNET/EpicGames.Perforce.Native/win-x64/{configFolder}/EpicGames.Perforce.Native.dll" [if if (target.Platform == UnrealTargetPlatform.Win64)]`
- `L31 OutputFile = $"Binaries/DotNET/EpicGames.Perforce.Native/mac-x64/{configFolder}/EpicGames.Perforce.Native.dylib" [if else if (target.Platform == UnrealTargetPlatform.Mac)]`
- `L35 OutputFile = $"Binaries/DotNET/EpicGames.Perforce.Native/linux-x64/{configFolder}/EpicGames.Perforce.Native.so" [if else if (target.Platform == UnrealTargetPlatform.Linux)]`

### `SlateTestsTarget` — `Engine/Source/Programs/SlateTests/SlateTests.Target.cs`

- `L10 bTestsRequireApplicationCore = true`
- `L11 bTestsRequireCoreUObject = true`
- `L13 bBuildWithEditorOnlyData = Target.Platform.IsInGroup(UnrealPlatformGroup.Desktop) && (Target.Configuration == UnrealTargetConfiguration.Debug \|\| Target.Configuration == UnrealTargetConfig`

### `SlateUGSTarget` — `Engine/Source/Programs/SlateUGS/SlateUGS.Target.cs`

- `L11 Type = TargetType.Program`
- `L12 LinkType = TargetLinkType.Monolithic`
- `L13 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L15 LaunchModuleName = "SlateUGS"`
- `L17 bBuildDeveloperTools = false`
- `L20 bCompileAgainstEngine = false`
- `L23 bCompileAgainstCoreUObject = true`
- `L27 bHasExports = false`
- `L30 bBuildDeveloperTools = true`

### `SlateViewerTarget` — `Engine/Source/Programs/SlateViewer/SlateViewer.Target.cs`

- `L13 Type = TargetType.Program`
- `L14 LinkType = TargetLinkType.Monolithic`
- `L16 LaunchModuleName = "SlateViewer"`
- `L19 ExtraModuleNames.Add () "EditorStyle" [if if (bBuildEditor)]`
- `L22 bBuildDeveloperTools = false`
- `L25 bCompileAgainstEngine = false`
- `L28 bCompileAgainstCoreUObject = true`
- `L32 bHasExports = false`
- `L35 bBuildDeveloperTools = true`

### `SubmitToolTarget` — `Engine/Source/Programs/SubmitTool/SubmitTool.Target.cs`

- `L10 Type = TargetType.Program`
- `L11 LinkType = TargetLinkType.Monolithic`
- `L12 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L13 LaunchModuleName = "SubmitTool"`
- `L16 bUseXGEController = false`
- `L17 bLoggingToMemoryEnabled = true`
- `L18 bUseLoggingInShipping = true`
- `L19 bCompileWithAccessibilitySupport = false`
- `L20 bWithServerCode = false`
- `L21 bCompileNavmeshClusterLinks = false`
- `L22 bCompileNavmeshSegmentLinks = false`
- `L23 bCompileRecast = false`
- `L24 bCompileICU = true`
- `L25 bWithLiveCoding = false`
- `L26 bBuildDeveloperTools = false`
- `L27 bBuildWithEditorOnlyData = false`
- `L28 bCompileAgainstEngine = false`
- `L29 bCompileAgainstCoreUObject = true`
- `L30 bUsesSlate = true`
- `L31 bIsBuildingConsoleApplication = false`
- `L32 bCompileWithPluginSupport = true`
- `L33 bBuildRequiresCookedData = false`
- `L34 bEnableTrace = true`
- `L35 bForceDisableAutomationTests = true`
- `L37 bHasExports = false`
- `L39 WindowsPlatform.bStripUnreferencedSymbols = true`
- `L40 WindowsPlatform.bMergeIdenticalCOMDATs = true`
- `L41 WindowsPlatform.bUseBundledDbgHelp = false`
- `L42 WindowsPlatform.bPixProfilingEnabled = false`
- `L44 GlobalDefinitions.Add () "UE_TASK_TRACE_ENABLED=1"`
- `L45 GlobalDefinitions.Add () "AUTOSDKS_ENABLED=0"`
- `L46 GlobalDefinitions.Add () "EXCLUDE_NONPAK_UE_EXTENSIONS=0"`
- `L47 GlobalDefinitions.Add () "WITH_AUTOMATION_WORKER=0"`
- `L48 GlobalDefinitions.Add () "UE_EXTERNAL_PROFILING_ENABLED=0"`
- `L49 GlobalDefinitions.Add () "STATS=0"`
- `L50 GlobalDefinitions.Add () "ENABLE_STATNAMEDEVENTS=0"`
- `L51 GlobalDefinitions.Add () "ALLOW_HITCH_DETECTION=0"`
- `L52 GlobalDefinitions.Add () "UE_USE_MALLOC_FILL_BYTES=0"`
- `L54 OptedInModulePlatforms = new UnrealTargetPlatform[] { UnrealTargetPlatform.Win64, UnrealTargetPlatform.Mac, UnrealTargetPlatform.Linux, UnrealTargetPlatform.LinuxArm64 }`

### `SwitchboardListenerTargetBase` — `Engine/Source/Programs/SwitchboardListener/SwitchboardListener.Target.cs`

- `L10 SolutionDirectory = "Programs/Switchboard"`
- `L12 Type = TargetType.Program`
- `L13 LinkType = TargetLinkType.Monolithic`
- `L15 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L18 bCompileAgainstCoreUObject = true`
- `L19 bCompileAgainstEngine = false`
- `L20 bBuildWithEditorOnlyData = false`
- `L23 bCompileICU = false`
- `L25 bEnableTrace = true`

### `SwitchboardListenerTarget` — `Engine/Source/Programs/SwitchboardListener/SwitchboardListener.Target.cs`

- `L34 LaunchModuleName = "SwitchboardListener"`

### `SwitchboardListenerCmdTarget` — `Engine/Source/Programs/SwitchboardListener/SwitchboardListenerCmd.Target.cs`

- `L10 LaunchModuleName = "SwitchboardListenerCmd"`
- `L14 bIsBuildingConsoleApplication = Target.Platform != UnrealTargetPlatform.Mac`

### `SwitchboardListenerTestsTarget` — `Engine/Source/Programs/SwitchboardListener/SwitchboardListenerTests.Target.cs`

- `L11 SolutionDirectory = "Programs/Switchboard"`
- `L12 LaunchModuleName = "SwitchboardListenerTests"`
- `L15 GlobalDefinitions.Add () "SWITCHBOARD_LISTENER_EXCLUDE_MAIN=1"`
- `L17 ExtraModuleNames.Add () LaunchModuleName`

### `SwitchboardListenerHelperTarget` — `Engine/Source/Programs/SwitchboardListenerHelper/SwitchboardListenerHelper.Target.cs`

- `L12 Type = TargetType.Program`
- `L13 LinkType = TargetLinkType.Monolithic`
- `L14 LaunchModuleName = "SwitchboardListenerHelper"`
- `L15 SolutionDirectory = "Programs/Switchboard"`
- `L17 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L20 bCompileAgainstCoreUObject = true`
- `L21 bCompileAgainstEngine = false`
- `L22 bBuildWithEditorOnlyData = false`
- `L25 bCompileICU = false`
- `L28 bIsBuildingConsoleApplication = Target.Platform != UnrealTargetPlatform.Mac`
- `L30 bEnableTrace = true`
- `L36 AdditionalLinkerArguments = "/MANIFESTUAC:NO" [if if (Target.Platform == UnrealTargetPlatform.Win64)]`
- `L37 WindowsPlatform.ManifestFile = FileReference.Combine(Unreal.EngineDirectory, "Source", "Programs", "SwitchboardListenerHelper", "Resources", "Windows", "SBLHelper.manifest.xml").ToString() [if if (Target.Platform == UnrealTargetPlatform.Win64)]`

### `SymsLibDumpTarget` — `Engine/Source/Programs/SymsLibDump/SymsLibDump.Target.cs`

- `L11 Type = TargetType.Program`
- `L12 LinkType = TargetLinkType.Monolithic`
- `L13 LaunchModuleName = "SymsLibDump"`
- `L16 UndecoratedConfiguration = UnrealTargetConfiguration.Shipping`
- `L19 bBuildDeveloperTools = false`
- `L22 bCompileAgainstEngine = false`
- `L23 bCompileAgainstCoreUObject = false`
- `L26 bUseLoggingInShipping = true`
- `L29 bIsBuildingConsoleApplication = true`
- `L34 GlobalDefinitions.Add () "COMPILED_IN_MINIMUM_VERBOSITY=Error" [if if (Target.Configuration == UnrealTargetConfiguration.Shipping)]`

### `TestPALTarget` — `Engine/Source/Programs/TestPAL/TestPAL.Target.cs`

- `L11 Type = TargetType.Program`
- `L12 LinkType = TargetLinkType.Monolithic`
- `L13 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L14 LaunchModuleName = "TestPAL"`
- `L17 bBuildDeveloperTools = false`
- `L20 bCompileAgainstEngine = false`
- `L21 bCompileAgainstCoreUObject = false`
- `L24 bUseLoggingInShipping = true`
- `L27 bIsBuildingConsoleApplication = true`
- `L31 GlobalDefinitions.Add () "COMPILE_FORK_PAGE_PROTECTOR=1" [if if (Target.Platform == UnrealTargetPlatform.Linux && Target.Configuration != UnrealTargetConfiguration.Shipping)]`

### `ToolMenusTestsTarget` — `Engine/Source/Programs/ToolMenusTests/ToolMenusTests.Target.cs`

- `L10 bTestsRequireApplicationCore = true`
- `L11 bTestsRequireCoreUObject = true`
- `L13 bBuildWithEditorOnlyData = Target.Platform.IsInGroup(UnrealPlatformGroup.Desktop) && (Target.Configuration == UnrealTargetConfiguration.Debug \|\| Target.Configuration == UnrealTargetConfig`

### `TraceAnalyzerTarget` — `Engine/Source/Programs/TraceAnalyzer/TraceAnalyzer.Target.cs`

- `L11 Type = TargetType.Program`
- `L12 LaunchModuleName = "TraceAnalyzer"`
- `L13 LinkType = TargetLinkType.Monolithic`
- `L15 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L18 bIsBuildingConsoleApplication = true`
- `L21 bBuildDeveloperTools = false`
- `L23 bBuildWithEditorOnlyData = false`
- `L28 bCompileAgainstEngine = false`
- `L29 bCompileAgainstCoreUObject = false`
- `L30 bCompileAgainstApplicationCore = false`
- `L31 bCompileICU = false`
- `L34 bEnableTrace = false`
- `L35 GlobalDefinitions.Add () "CPUPROFILERTRACE_ENABLED=0"`
- `L36 GlobalDefinitions.Add () "LOADTIMEPROFILERTRACE_ENABLED=0"`
- `L37 GlobalDefinitions.Add () "STATSTRACE_ENABLED=0"`
- `L38 GlobalDefinitions.Add () "COUNTERSTRACE_ENABLED=0"`
- `L39 GlobalDefinitions.Add () "LOGTRACE_ENABLED=0"`
- `L40 GlobalDefinitions.Add () "MISCTRACE_ENABLED=0"`
- `L41 GlobalDefinitions.Add () "UE_TASK_TRACE_ENABLED=0"`
- `L42 GlobalDefinitions.Add () "UE_NET_TRACE_ENABLED=0"`
- `L43 GlobalDefinitions.Add () "UE_MEMORY_TAGS_TRACE_ENABLED=0"`
- `L44 GlobalDefinitions.Add () "UE_MEMORY_TRACE_ENABLED=0"`
- `L45 GlobalDefinitions.Add () "UE_CALLSTACK_TRACE_ENABLED=0"`
- `L48 GlobalDefinitions.Add () "UE_TRACE_ANALYSIS_DEBUG_API=1"`
- `L49 GlobalDefinitions.Add () "UE_TRACE_ANALYSIS_DEBUG=1"`
- `L50 GlobalDefinitions.Add () "UE_TRACE_ANALYSIS_DEBUG_LOG_IMPL=1"`

### `TraceQueryTarget` — `Engine/Source/Programs/TraceQuery/TraceQuery.Target.cs`

- `L11 Type = TargetType.Program`
- `L12 LaunchModuleName = "TraceQuery"`
- `L13 LinkType = TargetLinkType.Monolithic`
- `L15 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L18 bIsBuildingConsoleApplication = true`
- `L21 bBuildDeveloperTools = false`
- `L23 bBuildWithEditorOnlyData = false`
- `L26 bCompileAgainstEngine = false`
- `L27 bCompileAgainstCoreUObject = false`
- `L28 bCompileAgainstApplicationCore = false`
- `L29 bCompileICU = false`
- `L31 bEnableTrace = false`
- `L32 GlobalDefinitions.Add () "CPUPROFILERTRACE_ENABLED=0"`
- `L33 GlobalDefinitions.Add () "GPUPROFILERTRACE_ENABLED=0"`
- `L34 GlobalDefinitions.Add () "LOADTIMEPROFILERTRACE_ENABLED=0"`
- `L35 GlobalDefinitions.Add () "STATSTRACE_ENABLED=0"`
- `L36 GlobalDefinitions.Add () "COUNTERSTRACE_ENABLED=0"`
- `L37 GlobalDefinitions.Add () "LOGTRACE_ENABLED=0"`
- `L38 GlobalDefinitions.Add () "MISCTRACE_ENABLED=0"`
- `L39 GlobalDefinitions.Add () "UE_TASK_TRACE_ENABLED=0"`
- `L40 GlobalDefinitions.Add () "UE_NET_TRACE_ENABLED=0"`
- `L41 GlobalDefinitions.Add () "UE_MEMORY_TAGS_TRACE_ENABLED=0"`
- `L42 GlobalDefinitions.Add () "UE_MEMORY_TRACE_ENABLED=0"`
- `L43 GlobalDefinitions.Add () "UE_CALLSTACK_TRACE_ENABLED=0"`
- `L46 GlobalDefinitions.Add () "UE_TRACE_ANALYSIS_DEBUG_API=0"`
- `L47 GlobalDefinitions.Add () "UE_TRACE_ANALYSIS_DEBUG=0"`
- `L48 GlobalDefinitions.Add () "UE_TRACE_ANALYSIS_DEBUG_LOG_IMPL=1"`
- `L49 GlobalDefinitions.Add () "UE_TRACE_ANALYSIS_DEBUG_LEVEL=2"`

### `TraceTrimmerTarget` — `Engine/Source/Programs/TraceTrimmer/TraceTrimmer.Target.cs`

- `L11 Type = TargetType.Program`
- `L12 LaunchModuleName = "TraceTrimmer"`
- `L13 LinkType = TargetLinkType.Monolithic`
- `L15 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L18 bIsBuildingConsoleApplication = true`
- `L21 bBuildDeveloperTools = false`
- `L23 bBuildWithEditorOnlyData = false`
- `L28 bCompileAgainstEngine = false`
- `L29 bCompileAgainstCoreUObject = false`
- `L30 bCompileAgainstApplicationCore = false`
- `L31 bCompileICU = false`
- `L34 bEnableTrace = false`
- `L35 GlobalDefinitions.Add () "CPUPROFILERTRACE_ENABLED=0"`
- `L36 GlobalDefinitions.Add () "GPUPROFILERTRACE_ENABLED=0"`
- `L37 GlobalDefinitions.Add () "LOADTIMEPROFILERTRACE_ENABLED=0"`
- `L38 GlobalDefinitions.Add () "STATSTRACE_ENABLED=0"`
- `L39 GlobalDefinitions.Add () "COUNTERSTRACE_ENABLED=0"`
- `L40 GlobalDefinitions.Add () "LOGTRACE_ENABLED=0"`
- `L41 GlobalDefinitions.Add () "MISCTRACE_ENABLED=0"`
- `L42 GlobalDefinitions.Add () "UE_TASK_TRACE_ENABLED=0"`
- `L43 GlobalDefinitions.Add () "UE_NET_TRACE_ENABLED=0"`
- `L44 GlobalDefinitions.Add () "UE_MEMORY_TAGS_TRACE_ENABLED=0"`
- `L45 GlobalDefinitions.Add () "UE_MEMORY_TRACE_ENABLED=0"`
- `L46 GlobalDefinitions.Add () "UE_CALLSTACK_TRACE_ENABLED=0"`
- `L49 GlobalDefinitions.Add () "UE_TRACE_ANALYSIS_DEBUG_API=0"`
- `L50 GlobalDefinitions.Add () "UE_TRACE_ANALYSIS_DEBUG=0"`
- `L51 GlobalDefinitions.Add () "UE_TRACE_ANALYSIS_DEBUG_LOG_IMPL=1"`

### `UninstallHelperTarget` — `Engine/Source/Programs/UninstallHelper/UninstallHelper.Target.cs`

- `L12 Type = TargetType.Program`
- `L13 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L14 LinkType = TargetLinkType.Monolithic`
- `L15 LaunchModuleName = "UninstallHelper"`
- `L18 bBuildDeveloperTools = false`
- `L21 bCompileAgainstEngine = false`
- `L22 bCompileAgainstCoreUObject = false`
- `L23 bCompileAgainstApplicationCore = false`
- `L24 bBuildWithEditorOnlyData = false`
- `L25 bCompileICU = false`
- `L28 bIsBuildingConsoleApplication = true`

### `UnrealAssetStringifyTarget` — `Engine/Source/Programs/UnrealAssetStringify/UnrealAssetStringify.Target.cs`

- `L10 Type = TargetType.Program`
- `L11 LinkType = TargetLinkType.Monolithic`
- `L12 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L13 LaunchModuleName = "UnrealAssetStringify"`
- `L14 DefaultBuildSettings = BuildSettingsVersion.Latest`
- `L18 bCompileAgainstEngine = false`
- `L19 bBuildDeveloperTools = false`
- `L20 bCompileAgainstApplicationCore = false`
- `L21 bBuildWithEditorOnlyData = true`
- `L22 bCompileAgainstEditor = true`
- `L23 bCompileAgainstCoreUObject = true`
- `L25 bIsBuildingConsoleApplication = true`
- `L26 bEnableTrace = true`
- `L29 GlobalDefinitions.Add () "UE_SUPPORT_FULL_PACKAGEPATH=1"`
- `L30 GlobalDefinitions.Add () "ALLOW_OTHER_PLATFORM_CONFIG=1"`
- `L31 GlobalDefinitions.Add () "UE_INTERNAL_UNIVERSAL_PLACEHOLDERS=1"`
- `L33 GlobalDefinitions.Add () "NOINITCRASHREPORTER=1"`
- `L35 GlobalDefinitions.Add () "UE_TASKGRAPH_THREAD_LIMIT=5"`
- `L39 GlobalDefinitions.Add () "UE_WITH_OBJECT_HANDLE_LATE_RESOLVE=0"`

### `UbaAgentTarget` — `Engine/Source/Programs/UnrealBuildAccelerator/UbaAgent.Target.cs`

- `L196 LaunchModuleName = "UbaAgent"`
- `L197 CommonUbaSettings () this, Target`
- `L13 Rules.Type = TargetType.Program`
- `L14 Rules.IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L15 Rules.LinkType = TargetLinkType.Monolithic`
- `L16 Rules.bDeterministic = true`
- `L17 Rules.bWarningsAsErrors = true`
- `L19 Rules.UndecoratedConfiguration = UnrealTargetConfiguration.Shipping`
- `L20 Rules.bHasExports = false`
- `L22 Rules.bRetainFramePointers = true`
- `L25 Rules.bBuildDeveloperTools = false`
- `L29 Rules.bBuildWithEditorOnlyData = false`
- `L32 Rules.bCompileAgainstEngine = false`
- `L33 Rules.bCompileAgainstCoreUObject = false`
- `L34 Rules.bCompileAgainstApplicationCore = false`
- `L35 Rules.bCompileICU = false`
- `L37 Rules.GlobalDefinitions.Add () "UBA_BUILD=1"`
- `L46 Rules.bIsBuildingConsoleApplication = true`
- `L48 Rules.WindowsPlatform.TargetWindowsVersion = 0x0A00`
- `L49 Rules.WindowsPlatform.TargetWindowsMinorVersion = 0x0A000005`
- `L50 Rules.bUseStaticCRT = true`
- `L52 Rules.SolutionDirectory = "Programs/UnrealBuildAccelerator"`
- `L61 Rules.AdditionalLinkerArguments += " /NODEFAULTLIB:kernel32.lib" [if if (Target.Platform.IsInGroup(UnrealPlatformGroup.Windows))]`
- `L62 Rules.AdditionalLinkerArguments += " mincore.lib" [if if (Target.Platform.IsInGroup(UnrealPlatformGroup.Windows))]`
- `L65 BinaryName = $"{Rules.LaunchModuleName}{BinaryExt}" [if if (Target.Platform.IsInGroup(UnrealPlatformGroup.Windows))]`
- `L66 Rules.OutputFile = Path.Combine(BinariesFolder, Target.Architectures.SingleArchitecture.bIsX64 ? "x64" : "arm64", BinaryName) [if if (Target.Platform.IsInGroup(UnrealPlatformGroup.Windows))]`
- `L68 Rules.GlobalDefinitions.AddRange () new string[] { "UBA_DETOURS_LIBRARY=L\"UbaDetours.dll\"", "UBA_AGENT_EXECUTABLE=L\"UbaAgent.exe\"", "UBA_DETOURS_LIBRARY_ANSI=\"UbaDetours.dll\"", "UBA_DETOURS_ [if if (Target.Platform.IsInGroup(UnrealPlatformGroup.Windows))]`
- `L74 usingSanitizer = Rules.WindowsPlatform.bEnableAddressSanitizer [if if (Target.Platform.IsInGroup(UnrealPlatformGroup.Windows))]`
- `L78 Rules.GlobalDefinitions.Add () "PLATFORM_WINDOWS=0" [if else]`
- `L85 BinaryName = $"{BinaryPrefix}{Rules.LaunchModuleName}{BinaryExt}" [if if (Target.Platform.IsInGroup(UnrealPlatformGroup.Linux))]`
- `L86 Rules.OutputFile = Path.Combine(BinariesFolder, BinaryName) [if if (Target.Platform.IsInGroup(UnrealPlatformGroup.Linux))]`
- `L88 Rules.GlobalDefinitions.AddRange () new string[] { "UBA_DETOURS_LIBRARY=\"libUbaDetours.so\"", "UBA_AGENT_EXECUTABLE=\"UbaAgent\"", "__NO_INLINE__", } [if if (Target.Platform.IsInGroup(UnrealPlatformGroup.Linux))]`
- `L98 Rules.AdditionalLinkerArguments += " -Wl,--no-export-dynamic" [if if (Target.Platform.IsInGroup(UnrealPlatformGroup.Linux)) && if (!Rules.bShouldCompileAsDLL)]`
- `L100 usingSanitizer = Rules.LinuxPlatform.bEnableAddressSanitizer \|\| Rules.LinuxPlatform.bEnableThreadSanitizer [if if (Target.Platform.IsInGroup(UnrealPlatformGroup.Linux))]`
- `L104 Rules.GlobalDefinitions.Add () "PLATFORM_LINUX=0" [if else]`
- `L111 Rules.Architectures.Architectures.Add () UnrealArch.X64 [if if (Target.Platform.IsInGroup(UnrealPlatformGroup.Apple)) && if (!Rules.Architectures.Contains(UnrealArch.X64))]`
- `L115 Rules.Architectures.Architectures.Add () UnrealArch.Arm64 [if if (Target.Platform.IsInGroup(UnrealPlatformGroup.Apple)) && if (!Rules.Architectures.Contains(UnrealArch.Arm64))]`
- `L121 BinaryName = $"{BinaryPrefix}{Rules.LaunchModuleName}{BinaryExt}" [if if (Target.Platform.IsInGroup(UnrealPlatformGroup.Apple)) && if (Rules.LaunchModuleName != "UbaVisualizer")]`
- `L122 Rules.OutputFile = Path.Combine(BinariesFolder, BinaryName) [if if (Target.Platform.IsInGroup(UnrealPlatformGroup.Apple)) && if (Rules.LaunchModuleName != "UbaVisualizer")]`
- `L126 Rules.ExeBinariesSubFolder = "UnrealBuildAccelerator" [if if (Target.Platform.IsInGroup(UnrealPlatformGroup.Apple)) && else]`
- `L129 Rules.GlobalDefinitions.AddRange () new string[] { "UBA_DETOURS_LIBRARY=\"libUbaDetours.dylib\"", "UBA_AGENT_EXECUTABLE=\"UbaAgent\"", "UBA_DETOURS_LIBRARY_LINUX=\"libUbaDetours.so\"", } [if if (Target.Platform.IsInGroup(UnrealPlatformGroup.Apple))]`
- `L137 Rules.GlobalDefinitions.Add () "PLATFORM_MAC=0" [if else]`
- `L140 Rules.GlobalDefinitions.Add () $"UBA_BINARY=\"{BinaryName}\""`
- `L147 useMiMalloc = 1 [if if (Target.Platform.IsInGroup(UnrealPlatformGroup.Windows) \|\| (!Rules.bShouldCompileAsDLL && Target.Platform.IsInGroup(UnrealPlatformGroup.Linux))) && if (Rules.bUsePCHFiles && !usingSanitizer)]`
- `L150 Rules.GlobalDefinitions.Add () $"UBA_USE_MIMALLOC={useMiMalloc}"`
- `L157 Rules.GlobalDefinitions.Add () "UBA_API=__declspec(dllexport)" [if if (Target.Platform.IsInGroup(UnrealPlatformGroup.Windows)) && if (ShouldExport)]`
- `L164 Rules.GlobalDefinitions.Add () "UBA_API=__attribute__ ((visibility(\"default\")))" [if else && if (ShouldExport)]`
- `L170 Rules.GlobalDefinitions.Add () "UBA_API=" [if if (!ShouldExport)]`
- `L175 Rules.GlobalDefinitions.Add () "UBA_DEBUG=1" [if if (Target.Configuration == UnrealTargetConfiguration.Debug)]`
- `L180 Rules.GlobalDefinitions.Add () "UBA_DEBUG=0" [if else]`
- `L185 Rules.bAllowLTCG = true [if if (Target.Configuration == UnrealTargetConfiguration.Shipping)]`
- `L188 Rules.WindowsPlatform.bSetResourceVersions = true`
- `L189 Rules.BuildVersion = $"{UbaVersion}-{Rules.Version.Changelist}"`
- `L191 Rules.CppCompileWarningSettings.CastFunctionTypeMismatchWarningLevel = WarningLevel.Off`

### `UbaCacheServiceTarget` — `Engine/Source/Programs/UnrealBuildAccelerator/UbaCacheService.Target.cs`

- `L10 LaunchModuleName = "UbaCacheService"`
- `L11 UbaAgentTarget.CommonUbaSettings () this, Target`

### `UbaCliTarget` — `Engine/Source/Programs/UnrealBuildAccelerator/UbaCli.Target.cs`

- `L10 LaunchModuleName = "UbaCli"`
- `L11 UbaAgentTarget.CommonUbaSettings () this, Target`

### `UbaCommonTarget` — `Engine/Source/Programs/UnrealBuildAccelerator/UbaCommon.Target.cs`

- `L10 LaunchModuleName = "UbaCommon"`
- `L11 bShouldCompileAsDLL = true`
- `L12 UbaAgentTarget.CommonUbaSettings () this, Target`

### `UbaCoordinatorHordeTarget` — `Engine/Source/Programs/UnrealBuildAccelerator/UbaCoordinatorHorde.Target.cs`

- `L11 LaunchModuleName = "UbaCoordinatorHorde"`
- `L12 bShouldCompileAsDLL = true`
- `L14 Type = TargetType.Program`
- `L15 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L16 LinkType = TargetLinkType.Monolithic`
- `L17 bDeterministic = true`
- `L18 bWarningsAsErrors = true`
- `L20 UndecoratedConfiguration = UnrealTargetConfiguration.Shipping`
- `L21 bHasExports = false`
- `L24 bBuildDeveloperTools = false`
- `L28 bBuildWithEditorOnlyData = false`
- `L31 bCompileAgainstEngine = false`
- `L32 bCompileAgainstCoreUObject = false`
- `L34 bCompileICU = false`
- `L36 bIsBuildingConsoleApplication = true`
- `L38 WindowsPlatform.TargetWindowsVersion = 0x0A00`
- `L41 SolutionDirectory = "Programs/UnrealBuildAccelerator"`
- `L47 OutputFile = Path.Combine(BinariesFolder, Target.Architectures.SingleArchitecture.bIsX64 ? "x64" : "arm64", $"{LaunchModuleName}{".dll"}") [if if (Target.Platform.IsInGroup(UnrealPlatformGroup.Windows))]`
- `L51 GlobalDefinitions.Add () "PLATFORM_WINDOWS=0" [if else]`
- `L56 OutputFile = Path.Combine(BinariesFolder, $"lib{LaunchModuleName}.dylib") [if if (Target.Platform.IsInGroup(UnrealPlatformGroup.Apple))]`
- `L60 GlobalDefinitions.Add () "PLATFORM_MAC=0" [if else]`
- `L65 OutputFile = Path.Combine(BinariesFolder, $"lib{LaunchModuleName}.so") [if if (Target.Platform.IsInGroup(UnrealPlatformGroup.Linux))]`
- `L69 GlobalDefinitions.Add () "PLATFORM_LINUX=0" [if else]`
- `L72 GlobalDefinitions.Add () "UE_EXTERNAL_PROFILING_ENABLED=0"`
- `L73 GlobalDefinitions.Add () "STATS=0"`
- `L74 GlobalDefinitions.Add () "ENABLE_STATNAMEDEVENTS=0"`
- `L75 GlobalDefinitions.Add () "ALLOW_HITCH_DETECTION=0"`
- `L76 GlobalDefinitions.Add () "UE_USE_MALLOC_FILL_BYTES=0"`
- `L77 GlobalDefinitions.Add () "DISABLE_CWD_CHANGES=1"`
- `L78 GlobalDefinitions.Add () "UE_NO_ENGINE_OIDC=0"`
- `L80 GlobalDefinitions.Add () "UBA_COORDINATOR_HORDE_DLL"`

### `UbaCoreTarget` — `Engine/Source/Programs/UnrealBuildAccelerator/UbaCore.Target.cs`

- `L10 LaunchModuleName = "UbaCore"`
- `L11 bShouldCompileAsDLL = true`
- `L12 UbaAgentTarget.CommonUbaSettings () this, Target`
- `L13 bDisableLinking = true`

### `UbaDetoursTarget` — `Engine/Source/Programs/UnrealBuildAccelerator/UbaDetours.Target.cs`

- `L10 LaunchModuleName = "UbaDetours"`
- `L11 bShouldCompileAsDLL = true`
- `L12 UbaAgentTarget.CommonUbaSettings () this, Target`
- `L13 GlobalDefinitions.Add () "_CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES=0"`
- `L18 bAllowLTCG = false [if if (Target.Platform.IsInGroup(UnrealPlatformGroup.Apple))]`
- `L36 AdditionalLinkerArguments = "-Wl,-z,now" [if if (Target.Platform.IsInGroup(UnrealPlatformGroup.Linux))]`

### `UbaHostTarget` — `Engine/Source/Programs/UnrealBuildAccelerator/UbaHost.Target.cs`

- `L10 LaunchModuleName = "UbaHost"`
- `L11 bShouldCompileAsDLL = true`
- `L12 UbaAgentTarget.CommonUbaSettings () this, Target, true`

### `UbaNinjaTarget` — `Engine/Source/Programs/UnrealBuildAccelerator/UbaNinja.Target.cs`

- `L10 LaunchModuleName = "UbaNinja"`
- `L11 UbaAgentTarget.CommonUbaSettings () this, Target`

### `UbaObjToolTarget` — `Engine/Source/Programs/UnrealBuildAccelerator/UbaObjTool.Target.cs`

- `L10 LaunchModuleName = "UbaObjTool"`
- `L11 UbaAgentTarget.CommonUbaSettings () this, Target`

### `UbaTestTarget` — `Engine/Source/Programs/UnrealBuildAccelerator/UbaTest.Target.cs`

- `L10 LaunchModuleName = "UbaTest"`
- `L11 UbaAgentTarget.CommonUbaSettings () this, Target`
- `L13 GlobalDefinitions.Add () "UBA_TEST_TARGET=1"`
- `L15 GlobalDefinitions.Add () $"UBA_BUILD_MACHINE={(AdditionalProperties.GetProperty("IsBuildMachine") == "1" ? "1" : "0")}"`

### `UbaTestAppTarget` — `Engine/Source/Programs/UnrealBuildAccelerator/UbaTestApp.Target.cs`

- `L10 LaunchModuleName = "UbaTestApp"`
- `L11 UbaAgentTarget.CommonUbaSettings () this, Target`

### `UbaVisualizerTarget` — `Engine/Source/Programs/UnrealBuildAccelerator/UbaVisualizer.Target.cs`

- `L9 LaunchModuleName = "UbaVisualizer"`
- `L10 UbaAgentTarget.CommonUbaSettings () this, Target`
- `L11 bIsBuildingConsoleApplication = false`
- `L12 WindowsPlatform.ApplicationIcon = "Programs/UnrealBuildAccelerator/Visualizer/Resources/Windows/UbaVisualizer.ico"`

### `UnrealFrontendTarget` — `Engine/Source/Programs/UnrealFrontend/UnrealFrontend.Target.cs`

- `L9 Type = TargetType.Program`
- `L10 LinkType = TargetLinkType.Modular`
- `L11 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L12 AdditionalPlugins.Add () "UdpMessaging"`
- `L13 LaunchModuleName = "UnrealFrontend"`
- `L16 GlobalDefinitions.Add () "FORCE_USE_STATS=1"`
- `L18 bCompileAgainstEngine = false`
- `L19 bCompileAgainstCoreUObject = true`
- `L20 bForceBuildTargetPlatforms = true`
- `L21 bCompileWithStatsWithoutEngine = true`
- `L22 bCompileWithPluginSupport = true`
- `L25 bBuildDeveloperTools = true`
- `L27 bHasExports = false`
- `L29 bEnableTrace = true`
- `L35 AdditionalPlugins.Add () "ProjectLauncher"`

### `UnrealInsightsTarget` — `Engine/Source/Programs/UnrealInsights/UnrealInsights.Target.cs`

- `L21 Type = TargetType.Program`
- `L22 LinkType = bMonolithic ? TargetLinkType.Monolithic : TargetLinkType.Modular`
- `L23 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L25 LaunchModuleName = "UnrealInsights"`
- `L28 ExtraModuleNames.Add () "EditorStyle" [if if (bBuildEditor)]`
- `L30 bCompileAgainstEngine = false`
- `L31 bCompileAgainstCoreUObject = true`
- `L32 bForceBuildTargetPlatforms = true`
- `L33 bCompileWithStatsWithoutEngine = true`
- `L34 bCompileWithPluginSupport = true`
- `L35 bCompileAsioSSLSupport = true`
- `L38 bIncludePluginsForTargetPlatforms = true`
- `L39 bCompileICU = true`
- `L42 bBuildDeveloperTools = true`
- `L51 bHasExports = false`
- `L54 GlobalDefinitions.Add () "UE_TRACE_SERVER_CONTROLS_ENABLED=1"`
- `L56 GlobalDefinitions.Add () "UE_TRACE_SERVER_LAUNCH_ENABLED=1"`
- `L59 bEnableTrace = bCmdLineTrace`
- `L64 GlobalDefinitions.Add () "UE_MEMORY_TRACE_AVAILABLE=1" [if if (bEnableTrace)]`
- `L65 GlobalDefinitions.Add () "UE_MEMORY_TAGS_TRACE_ENABLED=1" [if if (bEnableTrace)]`
- `L69 GlobalDefinitions.Add () "LLM_ENABLED_IN_CONFIG=1" [if if (bEnableTrace)]`
- `L88 GlobalDefinitions.Add () "UE_TRACE_ANALYSIS_DEBUG_API=1" [if if (bTraceAnalysisDebug)]`
- `L89 GlobalDefinitions.Add () "UE_TRACE_ANALYSIS_DEBUG=1" [if if (bTraceAnalysisDebug)]`
- `L90 GlobalDefinitions.Add () "UE_TRACE_ANALYSIS_DEBUG_LOG_IMPL=4" [if if (bTraceAnalysisDebug)]`
- `L91 GlobalDefinitions.Add () "UE_TRACE_ANALYSIS_DEBUG_LEVEL=1" [if if (bTraceAnalysisDebug)]`

### `UnrealLightmassTarget` — `Engine/Source/Programs/UnrealLightmass/UnrealLightmass.Target.cs`

- `L12 Type = TargetType.Program`
- `L13 LinkType = TargetLinkType.Modular`
- `L14 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L15 AdditionalPlugins.Add () "UdpMessaging"`
- `L16 LaunchModuleName = "UnrealLightmass"`
- `L19 bBuildDeveloperTools = false`
- `L22 bBuildWithEditorOnlyData = true`
- `L25 bCompileAgainstEngine = false`
- `L32 bCompileWithPluginSupport = true [if if (Target.Platform == UnrealTargetPlatform.Mac \|\| Target.Platform == UnrealTargetPlatform.Linux)]`
- `L33 bBuildDeveloperTools = true [if if (Target.Platform == UnrealTargetPlatform.Mac \|\| Target.Platform == UnrealTargetPlatform.Linux)]`
- `L37 bIsBuildingConsoleApplication = true`
- `L40 GlobalDefinitions.Add () "ALLOW_LOG_FILE=0"`

### `UnrealMultiUserServerTarget` — `Engine/Source/Programs/UnrealMultiUserServer/UnrealMultiUserServer.Target.cs`

- `L10 Type = TargetType.Program`
- `L11 LinkType = TargetLinkType.Modular`
- `L12 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L13 LaunchModuleName = "UnrealMultiUserServer"`
- `L14 AdditionalPlugins.Add () "UdpMessaging"`
- `L15 AdditionalPlugins.Add () "QuicMessaging"`
- `L16 AdditionalPlugins.Add () "ConcertSyncServer"`
- `L19 bCompileAgainstCoreUObject = true`
- `L20 bCompileAgainstEngine = false`
- `L21 bBuildWithEditorOnlyData = false`
- `L24 bCompileWithPluginSupport = true`
- `L25 bBuildDeveloperTools = true`
- `L28 bIsBuildingConsoleApplication = Target.Platform != UnrealTargetPlatform.Mac`
- `L30 GlobalDefinitions.Add () "UE_LOG_CONCERT_DEBUG_VERBOSITY_LEVEL=Log"`
- `L31 bEnableTrace = true`

### `UnrealMultiUserSlateServerTarget` — `Engine/Source/Programs/UnrealMultiUserSlateServer/UnrealMultiUserSlateServer.Target.cs`

- `L10 Type = TargetType.Program`
- `L11 LinkType = TargetLinkType.Modular`
- `L12 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L13 LaunchModuleName = "UnrealMultiUserSlateServer"`
- `L14 AdditionalPlugins.Add () "UdpMessaging"`
- `L15 AdditionalPlugins.Add () "QuicMessaging"`
- `L16 AdditionalPlugins.Add () "ConcertSyncServer"`
- `L17 AdditionalPlugins.Add () "MultiUserServer"`
- `L20 bCompileAgainstCoreUObject = true`
- `L21 bCompileAgainstEngine = false`
- `L22 bBuildWithEditorOnlyData = false`
- `L25 bCompileWithPluginSupport = true`
- `L26 bBuildDeveloperTools = true`
- `L27 bIsBuildingConsoleApplication = false`
- `L29 GlobalDefinitions.Add () "UE_LOG_CONCERT_DEBUG_VERBOSITY_LEVEL=Log"`
- `L30 bEnableTrace = true`

### `UnrealObjectPtrToolTarget` — `Engine/Source/Programs/UnrealObjectPtrTool/UnrealObjectPtrTool.Target.cs`

- `L11 Type = TargetType.Program`
- `L12 LinkType = TargetLinkType.Modular`
- `L13 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L14 LaunchModuleName = "UnrealObjectPtrTool"`
- `L16 bBuildDeveloperTools = false`
- `L17 bBuildWithEditorOnlyData = false`
- `L18 bCompileAgainstEngine = false`
- `L19 bCompileAgainstCoreUObject = false`
- `L20 bCompileAgainstApplicationCore = false`
- `L21 bUsesSlate = false`
- `L22 bIsBuildingConsoleApplication = true`

### `UnrealPackageToolTarget` — `Engine/Source/Programs/UnrealPackageTool/UnrealPackageTool.Target.cs`

- `L10 Type = TargetType.Program`
- `L11 LinkType = TargetLinkType.Monolithic`
- `L12 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L13 LaunchModuleName = "UnrealPackageTool"`
- `L14 DefaultBuildSettings = BuildSettingsVersion.Latest`
- `L17 bForceEnableRTTI = true`
- `L18 bForceEnableExceptions = true`
- `L20 bBuildDeveloperTools = false`
- `L21 bBuildWithEditorOnlyData = true`
- `L24 bCompileAgainstApplicationCore = true`
- `L25 bCompileAgainstCoreUObject = true`
- `L26 bCompileAgainstEngine = false`
- `L27 bCompileICU = false`
- `L29 bIsBuildingConsoleApplication = true`
- `L31 bEnableTrace = true`

### `UnrealPakTarget` — `Engine/Source/Programs/UnrealPak/UnrealPak.Target.cs`

- `L10 Type = TargetType.Program`
- `L11 LinkType = TargetLinkType.Modular`
- `L12 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L13 LaunchModuleName = "UnrealPak"`
- `L15 bUseXGEController = false`
- `L16 bCompileFreeType = false`
- `L17 bLoggingToMemoryEnabled = false`
- `L18 bUseLoggingInShipping = true`
- `L19 bCompileWithAccessibilitySupport = false`
- `L20 bCompileWithPluginSupport = true`
- `L21 bIncludePluginsForTargetPlatforms = true`
- `L22 bWithServerCode = false`
- `L23 bCompileNavmeshClusterLinks = false`
- `L24 bCompileNavmeshSegmentLinks = false`
- `L25 bCompileRecast = false`
- `L26 bCompileICU = false`
- `L27 bWithLiveCoding = false`
- `L28 bBuildDeveloperTools = false`
- `L29 bBuildWithEditorOnlyData = true`
- `L30 bCompileAgainstEngine = false`
- `L31 bCompileAgainstCoreUObject = true`
- `L32 bCompileAgainstApplicationCore = true`
- `L33 bUsesSlate = false`
- `L34 bIsBuildingConsoleApplication = true`
- `L35 bForceBuildTargetPlatforms = true`
- `L36 bNeedsExtraShaderFormats = true`
- `L37 bAreTargetSDKVersionsRelevantOverride = false`
- `L39 WindowsPlatform.bUseBundledDbgHelp = false`
- `L40 WindowsPlatform.bPixProfilingEnabled = false`
- `L41 WindowsPlatform.bMergeIdenticalCOMDATs = true`
- `L42 WindowsPlatform.bStripUnreferencedSymbols = true`
- `L44 bEnableTrace = true`
- `L45 GlobalDefinitions.Add () "UE_EXTERNAL_PROFILING_ENABLED=0"`
- `L46 GlobalDefinitions.Add () "ALLOW_OTHER_PLATFORM_CONFIG=1"`

### `UnrealRecoverySvcTarget` — `Engine/Source/Programs/UnrealRecoverySvc/UnrealRecoverySvc.Target.cs`

- `L10 Type = TargetType.Program`
- `L11 LinkType = TargetLinkType.Monolithic`
- `L12 LaunchModuleName = "UnrealRecoverySvc"`
- `L15 bCompileAgainstCoreUObject = true`
- `L16 bCompileAgainstEngine = false`
- `L17 bBuildWithEditorOnlyData = false`
- `L20 bCompileWithPluginSupport = true`
- `L21 bBuildDeveloperTools = true`
- `L24 bIsBuildingConsoleApplication = true`

### `UnrealVersionSelectorTarget` — `Engine/Source/Programs/UnrealVersionSelector/UnrealVersionSelector.Target.cs`

- `L10 Type = TargetType.Program`
- `L11 LinkType = TargetLinkType.Monolithic`
- `L12 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L13 LaunchModuleName = "UnrealVersionSelector"`
- `L15 bBuildDeveloperTools = false`
- `L21 ExtraModuleNames.Add () "EditorStyle" [if if (bUsingSlate && bBuildEditor)]`
- `L24 bCompileICU = false`
- `L26 bBuildWithEditorOnlyData = bUsingSlate`
- `L29 bCompileAgainstEngine = false`
- `L30 bCompileAgainstCoreUObject = bUsingSlate`

### `UnrealVirtualizationToolTarget` — `Engine/Source/Programs/UnrealVirtualizationTool/UnrealVirtualizationTool.Target.cs`

- `L10 Type = TargetType.Program`
- `L11 LinkType = TargetLinkType.Monolithic`
- `L12 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L14 LaunchModuleName = "UnrealVirtualizationTool"`
- `L16 bBuildDeveloperTools = false`
- `L18 bCompileAgainstEditor = false`
- `L19 bBuildWithEditorOnlyData = true`
- `L22 bCompileAgainstApplicationCore = true`
- `L23 bCompileAgainstCoreUObject = true`
- `L24 bCompileAgainstEngine = false`
- `L25 bUsesSlate = false`
- `L28 bCompileFreeType = false`
- `L29 bCompileICU = false`
- `L32 bIsBuildingConsoleApplication = true`
- `L35 bCompileWithPluginSupport = true`
- `L38 WindowsPlatform.bStripUnreferencedSymbols = true`
- `L39 WindowsPlatform.bMergeIdenticalCOMDATs = true`
- `L40 WindowsPlatform.bUseBundledDbgHelp = false`
- `L41 WindowsPlatform.bPixProfilingEnabled = false`
- `L43 bEnableTrace = true`
- `L44 GlobalDefinitions.Add () "UE_SUPPORT_FULL_PACKAGEPATH=1"`

### `UnsyncTarget` — `Engine/Source/Programs/Unsync/Unsync.Target.cs`

- `L10 Name = "unsync"`
- `L11 Type = TargetType.Program`
- `L12 LinkType = TargetLinkType.Monolithic`
- `L13 LaunchModuleName = "Unsync"`
- `L14 bBuildDeveloperTools = false`
- `L15 bCompileICU = false`
- `L16 bBuildWithEditorOnlyData = false`
- `L17 bCompileAgainstEngine = false`
- `L18 bCompileAgainstCoreUObject = false`
- `L19 bEnforceIWYU = false`
- `L20 GlobalDefinitions.Add () "_CRT_SECURE_NO_WARNINGS"`
- `L21 WindowsPlatform.TargetWindowsVersion = 0x0603`
- `L22 bUseStaticCRT = true`
- `L23 bIsBuildingConsoleApplication = true`

### `TextureShareSDKTarget` — `Engine/Source/Programs/VirtualProduction/TextureShare/TextureShareSDK.Target.cs`

- `L50 DefaultBuildSettings = BuildSettingsVersion.Latest`
- `L51 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L53 Type = TargetType.Program`
- `L54 LinkType = TargetLinkType.Monolithic`
- `L57 bShouldCompileAsDLL = true`
- `L59 ExeBinariesSubFolder = @"TextureShareSDK"`
- `L61 SolutionDirectory = "Programs/VirtualProduction/TextureShare"`
- `L62 LaunchModuleName = "TextureShareSDK"`
- `L65 bBuildDeveloperTools = false`
- `L67 bBuildWithEditorOnlyData = false`
- `L70 bCompileAgainstEngine = false`
- `L71 bCompileAgainstCoreUObject = false`
- `L74 bUseLoggingInShipping = true`
- `L75 bUseChecksInShipping = true`
- `L78 bCompileICU = false`
- `L80 bUsesSlate = false`
- `L83 bHasExports = true`
- `L86 bBuildInSolutionByDefault = false`
- `L90 AddWindowsPostBuildSteps ()  [if if (Platform == UnrealTargetPlatform.Win64)]`
- `L13 PostBuildSteps.Add () string.Format("echo Copying {0} to {1}", SrcPath, DestPath)`
- `L14 PostBuildSteps.Add () string.Format("xcopy /y /i /v \"{0}\" \"{1}\" 1>nul", SrcPath, DestPath)`
- `L26 ImplPostBuildCopy () Path.Combine(SDKSrcPath, "Public", "*.h"), Path.Combine(SDKHeadersDestPath)`
- `L27 ImplPostBuildCopy () Path.Combine(SDKSrcPath, "Public", "Serialize", "*.h"), Path.Combine(SDKHeadersDestPath, "Serialize")`
- `L28 ImplPostBuildCopy () Path.Combine(SDKSrcPath, "Public", "Containers", "*.h"), Path.Combine(SDKHeadersDestPath, "Containers")`
- `L29 ImplPostBuildCopy () Path.Combine(SDKSrcPath, "Public", "Containers/UnrealEngine", "*.h"), Path.Combine(SDKHeadersDestPath, "Containers", "UnrealEngine")`
- `L33 ImplPostBuildCopy () Path.Combine(MainPluginSrcPath, "Source/TextureShare/Private", "Misc", "*.h"), Path.Combine(SDKHeadersDestPath, "Misc")`
- `L34 ImplPostBuildCopy () Path.Combine(MainPluginSrcPath, "Source/TextureShareCore/Private", "Misc", "*.h"), Path.Combine(SDKHeadersDestPath, "Misc")`
- `L35 ImplPostBuildCopy () Path.Combine(MainPluginSrcPath, "Source/TextureShareCore/Private", "Containers", "*.h"), Path.Combine(SDKHeadersDestPath, "Containers")`
- `L36 ImplPostBuildCopy () Path.Combine(MainPluginSrcPath, "Source/TextureShareCore/Private", "Serialize", "*.h"), Path.Combine(SDKHeadersDestPath, "Serialize")`
- `L38 ImplPostBuildCopy () Path.Combine(MainPluginSrcPath, "Source/TextureShareDisplayCluster/Private", "Misc", "*.h"), Path.Combine(SDKHeadersDestPath, "Misc")`
- `L44 ImplPostBuildCopy () Path.Combine(SDKBinariesSrcPath, "*.*"), SDKBinariesDestPath`

### `WebTestsTarget` — `Engine/Source/Programs/WebTests/WebTests.Target.cs`

- `L10 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L11 bCompileAgainstCoreUObject = true`
- `L12 bCompileAgainstApplicationCore = true`

### `WebTestsServerCppTarget` — `Engine/Source/Programs/WebTestsServerCpp/WebTestsServerCpp.Target.cs`

- `L10 Type = TargetType.Program`
- `L11 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L12 LinkType = TargetLinkType.Monolithic`
- `L13 LaunchModuleName = "WebTestsServerCpp"`
- `L15 bBuildDeveloperTools = false`
- `L16 bCompileAgainstEngine = false`
- `L17 bCompileAgainstCoreUObject = false`
- `L18 bCompileAgainstApplicationCore = true`
- `L19 bCompileICU = false`
- `L20 bIsBuildingConsoleApplication = true`

### `ASDToolTarget` — `Engine/Source/Programs/Windows/ASDTool/ASDTool.Target.cs`

- `L10 Type = TargetType.Program`
- `L11 LinkType = TargetLinkType.Monolithic`
- `L12 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L13 LaunchModuleName = "ASDTool"`
- `L15 bBuildDeveloperTools = false`
- `L18 bBuildWithEditorOnlyData = Target.Platform.IsInGroup(UnrealPlatformGroup.Desktop) && bDebugOrDevelopment`
- `L20 bCompileAgainstEngine = false`
- `L21 bCompileAgainstCoreUObject = false`
- `L22 bCompileAgainstApplicationCore = true`
- `L23 bCompileICU = false`
- `L25 bIsBuildingConsoleApplication = true`
- `L27 bForceCompileDevelopmentAutomationTests = false`
- `L28 bCompileWithStatsWithoutEngine = false`
- `L30 bUseLoggingInShipping = true`
- `L31 bLegalToDistributeBinary = true`
- `L33 WindowsPlatform.bUseBundledDbgHelp = false`
- `L34 WindowsPlatform.bPixProfilingEnabled = false`
- `L35 WindowsPlatform.bMergeIdenticalCOMDATs = true`
- `L36 WindowsPlatform.bStripUnreferencedSymbols = true`
- `L39 bCompileCustomSQLitePlatform = false`
- `L40 GlobalDefinitions.Add () "SQLITE_OS_OTHER=0"`
- `L41 GlobalDefinitions.Add () "SQLITE_OS_WIN=1"`
- `L43 GlobalDefinitions.Add () "AUTOSDKS_ENABLED=0"`

### `BootstrapPackagedGameTarget` — `Engine/Source/Programs/Windows/BootstrapPackagedGame/BootstrapPackagedGame.Target.cs`

- `L12 Type = TargetType.Program`
- `L13 LinkType = TargetLinkType.Monolithic`
- `L14 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L15 LaunchModuleName = "BootstrapPackagedGame"`
- `L17 bUseStaticCRT = true`
- `L19 bUseSharedPCHs = false`
- `L22 bBuildDeveloperTools = false`
- `L23 bCompileICU = false`
- `L24 bBuildWithEditorOnlyData = false`
- `L25 bCompileAgainstEngine = false`
- `L26 bCompileAgainstCoreUObject = false`

### `ZenDashboardTarget` — `Engine/Source/Programs/ZenDashboard/ZenDashboard.Target.cs`

- `L11 Type = TargetType.Program`
- `L12 LinkType = TargetLinkType.Monolithic`
- `L13 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L14 LaunchModuleName = "ZenDashboard"`
- `L16 bUseXGEController = false`
- `L17 bLoggingToMemoryEnabled = true`
- `L18 bUseLoggingInShipping = true`
- `L19 bCompileWithAccessibilitySupport = false`
- `L20 bWithServerCode = false`
- `L21 bCompileNavmeshClusterLinks = false`
- `L22 bCompileNavmeshSegmentLinks = false`
- `L23 bCompileRecast = false`
- `L24 bCompileICU = false`
- `L25 bWithLiveCoding = false`
- `L26 bBuildDeveloperTools = false`
- `L27 bBuildWithEditorOnlyData = false`
- `L28 bCompileAgainstEngine = false`
- `L29 bCompileAgainstCoreUObject = true`
- `L30 bCompileAgainstApplicationCore = true`
- `L31 bUsesSlate = true`
- `L32 bForceDisableAutomationTests = true`
- `L34 bIsBuildingConsoleApplication = false`
- `L36 WindowsPlatform.bUseBundledDbgHelp = false`
- `L37 WindowsPlatform.bPixProfilingEnabled = false`
- `L38 WindowsPlatform.bMergeIdenticalCOMDATs = true`
- `L39 WindowsPlatform.bStripUnreferencedSymbols = true`
- `L41 GlobalDefinitions.Add () "WITH_AUTOMATION_TESTS=0"`
- `L42 GlobalDefinitions.Add () "WITH_AUTOMATION_WORKER=0"`

### `ZenLaunchTarget` — `Engine/Source/Programs/ZenLaunch/ZenLaunch.Target.cs`

- `L11 Type = TargetType.Program`
- `L12 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L13 LinkType = TargetLinkType.Monolithic`
- `L14 LaunchModuleName = "ZenLaunch"`
- `L17 bBuildDeveloperTools = false`
- `L20 bBuildWithEditorOnlyData = true`
- `L23 bCompileAgainstEngine = false`
- `L24 bCompileAgainstCoreUObject = false`
- `L25 bCompileAgainstApplicationCore = false`
- `L26 bCompileICU = false`
- `L35 bIsBuildingConsoleApplication = true`

### `ZenOplogDiffToolTarget` — `Engine/Source/Programs/ZenOplogDiffTool/ZenOplogDiffTool.Target.cs`

- `L10 Type = TargetType.Program`
- `L11 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L12 LinkType = TargetLinkType.Modular`
- `L13 LaunchModuleName = "ZenOplogDiffTool"`
- `L15 bBuildDeveloperTools = false`
- `L16 bCompileAgainstApplicationCore = true`
- `L17 bCompileAgainstCoreUObject = false`
- `L18 bCompileAgainstEngine = false`
- `L19 bCompileICU = false`
- `L20 bForceDisableAutomationTests = true`
- `L21 bIsBuildingConsoleApplication = true`
- `L22 bUseLoggingInShipping = true`
- `L27 GlobalDefinitions.Add () "LLM_ENABLED_IN_CONFIG=1" [if if (Target.Configuration == UnrealTargetConfiguration.Debug \|\| Target.Configuration == UnrealTargetConfiguration.Development)]`
- `L28 GlobalDefinitions.Add () "UE_MEMORY_TAGS_TRACE_ENABLED=1" [if if (Target.Configuration == UnrealTargetConfiguration.Debug \|\| Target.Configuration == UnrealTargetConfiguration.Development)]`
- `L29 bEnableTrace = true [if if (Target.Configuration == UnrealTargetConfiguration.Debug \|\| Target.Configuration == UnrealTargetConfiguration.Development)]`

### `IoStoreOnDemandTestsTarget` — `Engine/Source/Runtime/Experimental/IoStore/Tests/IoStoreOnDemandTests.Target.cs`

- `L10 bCompileAgainstCoreUObject = true`
- `L11 bCompileAgainstApplicationCore = true`
- `L12 bAdaptiveUnityDisablesOptimizations = true`
- `L14 GlobalDefinitions.Add () "CATCH_CONFIG_ENABLE_BENCHMARKING=1"`
- `L15 GlobalDefinitions.Add () "WITH_IOSTORE_ONDEMAND_TESTS=1"`

### `EventLoopUnitTestsTarget` — `Engine/Source/Runtime/Online/EventLoopTests/EventLoopUnitTests.Target.cs`

- `L9 bCompileAgainstCoreUObject = true`
- `L10 bCompileAgainstApplicationCore = true`
- `L13 GlobalDefinitions.Add () "CATCH_CONFIG_ENABLE_BENCHMARKING=1"`

### `UnrealClientTarget` — `Engine/Source/UnrealClient.Target.cs`

- `L10 Type = TargetType.Client`
- `L11 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L12 BuildEnvironment = TargetBuildEnvironment.Shared`
- `L13 ExtraModuleNames.Add () "UnrealGame"`

### `UnrealEditorTarget` — `Engine/Source/UnrealEditor.Target.cs`

- `L10 Type = TargetType.Editor`
- `L11 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L12 BuildEnvironment = TargetBuildEnvironment.Shared`
- `L13 bBuildAllModules = true`
- `L14 ExtraModuleNames.Add () "UnrealGame"`

### `UnrealGameTarget` — `Engine/Source/UnrealGame.Target.cs`

- `L11 Type = TargetType.Game`
- `L12 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L13 BuildEnvironment = TargetBuildEnvironment.Shared`
- `L15 ExtraModuleNames.Add () "UnrealGame"`

### `UnrealServerTarget` — `Engine/Source/UnrealServer.Target.cs`

- `L11 Type = TargetType.Server`
- `L12 IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L13 BuildEnvironment = TargetBuildEnvironment.Shared`
- `L14 ExtraModuleNames.Add () "UnrealGame"`

### `LyraClientTarget` — `Samples/Games/Lyra/Source/LyraClient.Target.cs`

- `L10 Type = TargetType.Client`
- `L12 ExtraModuleNames.AddRange () new string[] { "LyraGame" }`
- `L14 LyraGameTarget.ApplySharedLyraTargetSettings () this`

### `LyraEditorTarget` — `Samples/Games/Lyra/Source/LyraEditor.Target.cs`

- `L10 DefaultBuildSettings = BuildSettingsVersion.V7`
- `L12 Type = TargetType.Editor`
- `L13 ExtraModuleNames.AddRange () new string[] { "LyraGame", "LyraEditor" }`
- `L17 NativePointerMemberBehaviorOverride = PointerMemberBehavior.Disallow [if if (!bBuildAllModules)]`
- `L20 LyraGameTarget.ApplySharedLyraTargetSettings () this`
- `L23 EnablePlugins.Add () "RemoteSession"`

### `LyraGameTarget` — `Samples/Games/Lyra/Source/LyraGame.Target.cs`

- `L15 Type = TargetType.Game`
- `L17 ExtraModuleNames.AddRange () new string[] { "LyraGame" }`
- `L19 LyraGameTarget.ApplySharedLyraTargetSettings () this`
- `L28 Target.DefaultBuildSettings = BuildSettingsVersion.V7`
- `L29 Target.IncludeOrderVersion = EngineIncludeOrderVersion.Latest`
- `L36 Target.CppCompileWarningSettings.ShadowVariableWarningLevel = WarningLevel.Error [if if (Target.BuildEnvironment == TargetBuildEnvironment.Unique)]`
- `L38 Target.bUseLoggingInShipping = true [if if (Target.BuildEnvironment == TargetBuildEnvironment.Unique)]`
- `L39 Target.bTrackRHIResourceInfoForTest = true [if if (Target.BuildEnvironment == TargetBuildEnvironment.Unique)]`
- `L44 Target.bDisableUnverifiedCertificates = true [if if (Target.BuildEnvironment == TargetBuildEnvironment.Unique) && if (bIsShipping && !bIsDedicatedServer)]`
- `L59 Target.bAllowGeneratedIniWhenCooked = false [if if (Target.BuildEnvironment == TargetBuildEnvironment.Unique) && if (bIsShipping \|\| bIsTest)]`
- `L60 Target.bAllowNonUFSIniWhenCooked = false [if if (Target.BuildEnvironment == TargetBuildEnvironment.Unique) && if (bIsShipping \|\| bIsTest)]`
- `L66 Target.DisablePlugins.Add () "OpenImageDenoise" [if if (Target.BuildEnvironment == TargetBuildEnvironment.Unique) && if (Target.Type != TargetType.Editor)]`
- `L69 Target.GlobalDefinitions.Add () "UE_ASSETREGISTRY_INDIRECT_ASSETDATA_POINTERS=1" [if if (Target.BuildEnvironment == TargetBuildEnvironment.Unique) && if (Target.Type != TargetType.Editor)]`
- `L72 LyraGameTarget.ConfigureGameFeaturePlugins () Target [if if (Target.BuildEnvironment == TargetBuildEnvironment.Unique)]`
- `L83 LyraGameTarget.ConfigureGameFeaturePlugins () Target [if else && if (Target.Type == TargetType.Editor)]`
- `L90 bHasWarnedAboutShared = true [if else && else && if (!bHasWarnedAboutShared)]`
- `L91 Logger.LogWarning () "LyraGameEOS and dynamic target options are disabled when packaging from an installed version of the engine" [if else && else && if (!bHasWarnedAboutShared)]`
- `L127 Log.TraceInformationOnce () "Compiling GameFeaturePlugins in branch {0}", Target.Version.BranchName`
- `L137 CombinedPluginList.AddRange () PluginsBase.EnumeratePlugins(SearchDir) [if foreach (DirectoryReference SearchDir in GameFeaturePluginRoots)]`
- `L157 RawObject = JsonObject.Read(PluginFile) [if if (CombinedPluginList.Count > 0) && foreach (FileReference PluginFile in CombinedPluginList) && if (PluginFile != null && FileReference.Exists(PluginFile)) && try && lock (AllPluginRootJsonObjectsByName) && if (!AllPluginRootJsonObjectsByName.TryGetValue(PluginFile.GetFileNameWithoutExtension(), ou]`
- `L158 AllPluginRootJsonObjectsByName.Add () PluginFile.GetFileNameWithoutExtension(), RawObject [if if (CombinedPluginList.Count > 0) && foreach (FileReference PluginFile in CombinedPluginList) && if (PluginFile != null && FileReference.Exists(PluginFile)) && try && lock (AllPluginRootJsonObjectsByName) && if (!AllPluginRootJsonObjectsByName.TryGetValue(PluginFile.GetFileNameWithoutExtension(), ou]`
- `L176 Logger.LogWarning () "GameFeaturePlugin {0}, does not set ExplicitlyLoaded to true. This is required for GameFeaturePlugins.", PluginFile.GetFileNameWithoutExtension() [if if (CombinedPluginList.Count > 0) && foreach (FileReference PluginFile in CombinedPluginList) && if (PluginFile != null && FileReference.Exists(PluginFile)) && try && if (!RawObject.TryGetBoolField("ExplicitlyLoaded", out bExplicitlyLoaded) \|\| bExplicitlyLoaded == false)]`
- `L189 bEnabled = true [if if (CombinedPluginList.Count > 0) && foreach (FileReference PluginFile in CombinedPluginList) && if (PluginFile != null && FileReference.Exists(PluginFile)) && try && if (bBuildAllGameFeaturePlugins)]`
- `L199 bForceDisabled = true [if if (CombinedPluginList.Count > 0) && foreach (FileReference PluginFile in CombinedPluginList) && if (PluginFile != null && FileReference.Exists(PluginFile)) && try && if (RawObject.TryGetBoolField("EditorOnly", out bEditorOnly)) && if (bEditorOnly && (Target.Type != TargetType.Editor) && !bBuildAllG]`
- `L214 bForceDisabled = true [if if (CombinedPluginList.Count > 0) && foreach (FileReference PluginFile in CombinedPluginList) && if (PluginFile != null && FileReference.Exists(PluginFile)) && try && if (RawObject.TryGetStringField("RestrictToBranch", out RestrictToBranch)) && if (!Target.Version.BranchName.Equals(RestrictToBranch,]`
- `L215 Logger.LogDebug () "GameFeaturePlugin {Name} was marked as restricted to other branches. Disabling.", PluginFile.GetFileNameWithoutExtension() [if if (CombinedPluginList.Count > 0) && foreach (FileReference PluginFile in CombinedPluginList) && if (PluginFile != null && FileReference.Exists(PluginFile)) && try && if (RawObject.TryGetStringField("RestrictToBranch", out RestrictToBranch)) && if (!Target.Version.BranchName.Equals(RestrictToBranch,]`
- `L219 Logger.LogDebug () "GameFeaturePlugin {Name} was marked as restricted to this branch. Leaving enabled.", PluginFile.GetFileNameWithoutExtension() [if if (CombinedPluginList.Count > 0) && foreach (FileReference PluginFile in CombinedPluginList) && if (PluginFile != null && FileReference.Exists(PluginFile)) && try && if (RawObject.TryGetStringField("RestrictToBranch", out RestrictToBranch)) && else]`
- `L228 bForceDisabled = true [if if (CombinedPluginList.Count > 0) && foreach (FileReference PluginFile in CombinedPluginList) && if (PluginFile != null && FileReference.Exists(PluginFile)) && try && if (RawObject.TryGetBoolField("NeverBuild", out bNeverBuild) && bNeverBuild)]`
- `L229 Logger.LogDebug () "GameFeaturePlugin {Name} was marked as NeverBuild, disabling.", PluginFile.GetFileNameWithoutExtension() [if if (CombinedPluginList.Count > 0) && foreach (FileReference PluginFile in CombinedPluginList) && if (PluginFile != null && FileReference.Exists(PluginFile)) && try && if (RawObject.TryGetBoolField("NeverBuild", out bNeverBuild) && bNeverBuild)]`
- `L247 AllPluginReferencesByName[ReferencerName] = new List<string>() [if if (CombinedPluginList.Count > 0) && foreach (FileReference PluginFile in CombinedPluginList) && if (PluginFile != null && FileReference.Exists(PluginFile)) && try && if (RawObject.TryGetObjectArrayField("Plugins", out PluginReferencesArray)) && foreach (JsonObject ReferenceObject in PluginReference]`
- `L257 Logger.LogWarning () "Failed to parse GameFeaturePlugin file {Name}, disabling. Exception: {1}", PluginFile.GetFileNameWithoutExtension(), ParseException.Message [if if (CombinedPluginList.Count > 0) && foreach (FileReference PluginFile in CombinedPluginList) && if (PluginFile != null && FileReference.Exists(PluginFile)) && catch (Exception ParseException)]`
- `L258 bForceDisabled = true [if if (CombinedPluginList.Count > 0) && foreach (FileReference PluginFile in CombinedPluginList) && if (PluginFile != null && FileReference.Exists(PluginFile)) && catch (Exception ParseException)]`
- `L264 bEnabled = false [if if (CombinedPluginList.Count > 0) && foreach (FileReference PluginFile in CombinedPluginList) && if (PluginFile != null && FileReference.Exists(PluginFile)) && if (bForceDisabled)]`
- `L268 Logger.LogDebug () "ConfigureGameFeaturePlugins() has decided to {Action} feature {Name}", bEnabled ? "enable" : (bForceDisabled ? "disable" : "ignore"), PluginFile.GetFileNameWit [if if (CombinedPluginList.Count > 0) && foreach (FileReference PluginFile in CombinedPluginList) && if (PluginFile != null && FileReference.Exists(PluginFile))]`
- `L273 Target.EnablePlugins.Add () PluginFile.GetFileNameWithoutExtension() [if if (CombinedPluginList.Count > 0) && foreach (FileReference PluginFile in CombinedPluginList) && if (PluginFile != null && FileReference.Exists(PluginFile)) && if (bEnabled)]`
- `L277 Target.DisablePlugins.Add () PluginFile.GetFileNameWithoutExtension() [if if (CombinedPluginList.Count > 0) && foreach (FileReference PluginFile in CombinedPluginList) && if (PluginFile != null && FileReference.Exists(PluginFile)) && else if (bForceDisabled)]`

### `LyraGameEOSTarget` — `Samples/Games/Lyra/Source/LyraGameEOS.Target.cs`

- `L10 CustomConfig = "EOS"`
- `L12 EnablePlugins.AddRange () new string[] { "OnlineServicesEOS", "OnlineSubsystemEOS" }`
- `L20 OptionalPlugins.Add () "EOSReservedHooks"`

### `LyraGameSteamTarget` — `Samples/Games/Lyra/Source/LyraGameSteam.Target.cs`

- `L10 CustomConfig = "Steam"`

### `LyraGameSteamEOSTarget` — `Samples/Games/Lyra/Source/LyraGameSteamEOS.Target.cs`

- `L12 CustomConfig = "SteamEOS"`
- `L14 EnablePlugins.AddRange () new string[] { "OnlineServicesEOS", "OnlineSubsystemEOS" }`
- `L22 OptionalPlugins.Add () "EOSReservedHooks"`

### `LyraServerTarget` — `Samples/Games/Lyra/Source/LyraServer.Target.cs`

- `L11 Type = TargetType.Server`
- `L13 ExtraModuleNames.AddRange () new string[] { "LyraGame" }`
- `L15 LyraGameTarget.ApplySharedLyraTargetSettings () this`
- `L17 bUseChecksInShipping = true`

### `LyraServerEOSTarget` — `Samples/Games/Lyra/Source/LyraServerEOS.Target.cs`

- `L10 CustomConfig = "EOS"`
- `L12 EnablePlugins.AddRange () new string[] { "OnlineServicesEOS", "OnlineSubsystemEOS" }`
- `L20 OptionalPlugins.Add () "EOSReservedHooks"`

### `LyraServerSteamTarget` — `Samples/Games/Lyra/Source/LyraServerSteam.Target.cs`

- `L10 CustomConfig = "Steam"`

### `LyraServerSteamEOSTarget` — `Samples/Games/Lyra/Source/LyraServerSteamEOS.Target.cs`

- `L10 CustomConfig = "SteamEOS"`
- `L12 EnablePlugins.AddRange () new string[] { "OnlineServicesEOS", "OnlineSubsystemEOS" }`
- `L20 OptionalPlugins.Add () "EOSReservedHooks"`

### `TP_BlankTarget` — `Templates/TP_Blank/Source/TP_Blank.Target.cs`

- `L10 Type = TargetType.Game`
- `L11 DefaultBuildSettings = BuildSettingsVersion.V7`
- `L12 IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_8`
- `L13 ExtraModuleNames.Add () "TP_Blank"`

### `TP_BlankEditorTarget` — `Templates/TP_Blank/Source/TP_BlankEditor.Target.cs`

- `L10 Type = TargetType.Editor`
- `L11 DefaultBuildSettings = BuildSettingsVersion.V7`
- `L12 IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_8`
- `L13 ExtraModuleNames.Add () "TP_Blank"`

### `TP_FirstPersonTarget` — `Templates/TP_FirstPerson/Source/TP_FirstPerson.Target.cs`

- `L10 Type = TargetType.Game`
- `L11 DefaultBuildSettings = BuildSettingsVersion.V7`
- `L12 IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_8`
- `L13 ExtraModuleNames.Add () "TP_FirstPerson"`

### `TP_FirstPersonEditorTarget` — `Templates/TP_FirstPerson/Source/TP_FirstPersonEditor.Target.cs`

- `L10 Type = TargetType.Editor`
- `L11 DefaultBuildSettings = BuildSettingsVersion.V7`
- `L12 IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_8`
- `L13 ExtraModuleNames.Add () "TP_FirstPerson"`

### `TP_PuzzleTarget` — `Templates/TP_Puzzle/Source/TP_Puzzle.Target.cs`

- `L10 Type = TargetType.Game`
- `L11 DefaultBuildSettings = BuildSettingsVersion.V7`
- `L12 IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_8`
- `L13 ExtraModuleNames.Add () "TP_Puzzle"`

### `TP_PuzzleEditorTarget` — `Templates/TP_Puzzle/Source/TP_PuzzleEditor.Target.cs`

- `L10 Type = TargetType.Editor`
- `L11 DefaultBuildSettings = BuildSettingsVersion.V7`
- `L12 IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_8`
- `L13 ExtraModuleNames.Add () "TP_Puzzle"`

### `TP_SIM_BlankTarget` — `Templates/TP_SIM_Blank/Source/TP_SIM_Blank.Target.cs`

- `L10 Type = TargetType.Game`
- `L11 DefaultBuildSettings = BuildSettingsVersion.V7`
- `L12 IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_8`
- `L13 ExtraModuleNames.AddRange () new string[] { "TP_SIM_Blank" }`

### `TP_SIM_BlankEditorTarget` — `Templates/TP_SIM_Blank/Source/TP_SIM_BlankEditor.Target.cs`

- `L10 Type = TargetType.Editor`
- `L11 DefaultBuildSettings = BuildSettingsVersion.V7`
- `L12 IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_8`
- `L13 ExtraModuleNames.AddRange () new string[] { "TP_SIM_Blank" }`

### `TP_SIM_SandboxTarget` — `Templates/TP_SIM_Sandbox/Source/TP_SIM_Sandbox.Target.cs`

- `L10 Type = TargetType.Game`
- `L11 DefaultBuildSettings = BuildSettingsVersion.V7`
- `L12 IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_8`
- `L13 ExtraModuleNames.AddRange () new string[] { "TP_SIM_Sandbox" }`

### `TP_SIM_SandboxEditorTarget` — `Templates/TP_SIM_Sandbox/Source/TP_SIM_SandboxEditor.Target.cs`

- `L10 Type = TargetType.Editor`
- `L11 DefaultBuildSettings = BuildSettingsVersion.V7`
- `L12 IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_8`
- `L13 ExtraModuleNames.AddRange () new string[] { "TP_SIM_Sandbox" }`

### `TP_ThirdPersonTarget` — `Templates/TP_ThirdPerson/Source/TP_ThirdPerson.Target.cs`

- `L10 Type = TargetType.Game`
- `L11 DefaultBuildSettings = BuildSettingsVersion.V7`
- `L12 IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_8`
- `L13 ExtraModuleNames.Add () "TP_ThirdPerson"`

### `TP_ThirdPersonEditorTarget` — `Templates/TP_ThirdPerson/Source/TP_ThirdPersonEditor.Target.cs`

- `L10 Type = TargetType.Editor`
- `L11 DefaultBuildSettings = BuildSettingsVersion.V7`
- `L12 IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_8`
- `L13 ExtraModuleNames.Add () "TP_ThirdPerson"`

### `TP_TopDownTarget` — `Templates/TP_TopDown/Source/TP_TopDown.Target.cs`

- `L10 Type = TargetType.Game`
- `L11 DefaultBuildSettings = BuildSettingsVersion.V7`
- `L12 IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_8`
- `L13 ExtraModuleNames.Add () "TP_TopDown"`

### `TP_TopDownEditorTarget` — `Templates/TP_TopDown/Source/TP_TopDownEditor.Target.cs`

- `L10 Type = TargetType.Editor`
- `L11 DefaultBuildSettings = BuildSettingsVersion.V7`
- `L12 IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_8`
- `L13 ExtraModuleNames.Add () "TP_TopDown"`

### `TP_VehicleAdvTarget` — `Templates/TP_VehicleAdv/Source/TP_VehicleAdv.Target.cs`

- `L10 Type = TargetType.Game`
- `L11 DefaultBuildSettings = BuildSettingsVersion.V7`
- `L12 IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_8`
- `L13 ExtraModuleNames.Add () "TP_VehicleAdv"`

### `TP_VehicleAdvEditorTarget` — `Templates/TP_VehicleAdv/Source/TP_VehicleAdvEditor.Target.cs`

- `L10 Type = TargetType.Editor`
- `L11 DefaultBuildSettings = BuildSettingsVersion.V7`
- `L12 IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_8`
- `L13 ExtraModuleNames.Add () "TP_VehicleAdv"`
