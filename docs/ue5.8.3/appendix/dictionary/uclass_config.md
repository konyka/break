# UCLASS(config=...) dictionary

- headers scanned: 46494; UCLASSes with config=: 1330; Config/GlobalConfig UPROPERTYs: 1641; scan problems: 0
- by config file: Engine=476, EditorPerProjectUserSettings=270, Editor=239, Game=114, EditorSettings=60, Input=22, ChaosVD=17, Mass=14, DeviceProfiles=6, Plugins=6, DMXEditor=4, Interchange=4, MultiUserServerUserSettings=4, Niagara=4, CommonUI=3, Camera=2, EditorKeyBindings=2, GameUserSettings=2, GameplayTags=2, MaterialExpressions=2, MetaHumanCharacter=2, MetaHumanSDK=2, ObjectMixer=2, OpenColorIO=2, RemoteControl=2, SmartObjects=2, VirtualProductionUtilities=2, ADM=1, AccumulationDOF=1, AjaMedia=1, AnimNext=1, AnimNextAnimGraph=1, AudioInsights=1, AudioModulation=1, CineCameraRigs=1, Composure=1, ConcertSyncCore=1, ConfigSettingsToolsetTest=1, Crypto=1, DMXPixelMappingEditor=1, DeformerGraph=1, DisplayClusterLaunch=1, Fab=1, FastGeoStreaming=1, GameplayCameras=1, GameplayTagsList=1, GuidedTutorials=1, InstancedActors=1, LocalizationServiceSettings=1, MQTT=1, MemoryUsageQueries=1, MeshPartition=1, MetaHumanCharacterUAF=1, MetaSound=1, ModelViewViewModel=1, MotionDesign=1, MovieRenderPipeline=1, MultiUserClient=1, Mutable=1, NamingTokens=1, NetworkPrediction=1, NiagaraToolsets=1, ObjectMixerSerializedData=1, PIEPreviewSettings=1, PerformanceCaptureWorkflow=1, PixelStreaming=1, RemoteControlProtocolWidgets=1, RewindDebugger=1, RuntimeOptions=1, StateTree=1, TemplateCategories=1, TemplateDefs=1, Text3D=1, TraceSourceFilters=1, TranslationPickerSettings=1, USDCore=1, USDImporter=1, USDPregen=1, UnitTest=1, UnitTestStats=1, UnrealEd=1, UserVPRoles=1, UserWorldBookmarks=1, VirtualCameraCore=1, VirtualScoutingSettings=1, VisualLogger=1, WidgetEditorToolPalette=1, XRCreativeSettings=1, ZoneGraph=1, game=1

Section name in ini is `[/Script/<Module>.<ClassWithoutPrefix>]` (PerObjectConfig: `[<ObjName> <Class>]`). `G` marks GlobalConfig properties.


## config=Engine (476)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `AActor` | `/Script/Engine.Actor` |  | UObject | uint8 bReplicateUsingRegisteredSubObjectList : 1; EActorUpdateOverlapsMethod DefaultUpdateOverlapsMethodDuringLevelStreaming | `Source/Runtime/Engine/Classes/GameFramework/Actor.h:281` |
| `AComposurePipelineBaseActor` | `/Script/Composure.ComposurePipelineBaseActor` |  | AActor |  | `Plugins/Compositing/Composure/Source/Composure/Classes/ComposurePipelineBaseActor.h:14` |
| `ALobbyBeaconClient` | `/Script/Lobby.LobbyBeaconClient` |  | AOnlineBeaconClient |  | `Plugins/Online/OnlineFramework/Source/Lobby/Public/LobbyBeaconClient.h:57` |
| `ALobbyBeaconHost` | `/Script/Lobby.LobbyBeaconHost` |  | AOnlineBeaconHostObject |  | `Plugins/Online/OnlineFramework/Source/Lobby/Public/LobbyBeaconHost.h:23` |
| `AMixedRealityCaptureActor` | `/Script/MixedRealityCaptureFramework.MixedRealityCaptureActor` |  | AActor |  | `Plugins/Runtime/MixedRealityCaptureFramework/Source/MixedRealityCaptureFramework/Public/MixedRealityCaptureActor.h:18` |
| `AMultiServerBeaconClient` | `/Script/MultiServerReplication.MultiServerBeaconClient` |  | AOnlineBeaconClient |  | `Plugins/Runtime/MultiServerReplication/Source/MultiServerReplication/Public/MultiServerBeaconClient.h:20` |
| `AMultiServerBeaconHost` | `/Script/MultiServerReplication.MultiServerBeaconHost` |  | AOnlineBeaconHost |  | `Plugins/Runtime/MultiServerReplication/Source/MultiServerReplication/Private/MultiServerBeaconHost.h:12` |
| `AMultiServerBeaconHostObject` | `/Script/MultiServerReplication.MultiServerBeaconHostObject` |  | AOnlineBeaconHostObject |  | `Plugins/Runtime/MultiServerReplication/Source/MultiServerReplication/Private/MultiServerBeaconHostObject.h:13` |
| `ANavigationData` | `/Script/NavigationSystem.NavigationData` |  | AActor, INavigationDataInterface |  | `Source/Runtime/NavigationSystem/Public/NavigationData.h:539` |
| `ANavigationGraph` | `/Script/NavigationSystem.NavigationGraph` |  | ANavigationData |  | `Source/Runtime/NavigationSystem/Public/NavGraph/NavigationGraph.h:57` |
| `ANavigationGraphNode` | `/Script/NavigationSystem.NavigationGraphNode` |  | AActor |  | `Source/Runtime/NavigationSystem/Public/NavGraph/NavigationGraphNode.h:10` |
| `AOnlineBeacon` | `/Script/OnlineSubsystemUtils.OnlineBeacon` |  | AActor, FNetworkNotify | float BeaconConnectionInitialTimeout; float BeaconConnectionTimeout | `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Public/OnlineBeacon.h:66` |
| `AOnlineBeaconClient` | `/Script/OnlineSubsystemUtils.OnlineBeaconClient` |  | AOnlineBeacon |  | `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Public/OnlineBeaconClient.h:51` |
| `AOnlineBeaconHost` | `/Script/OnlineSubsystemUtils.OnlineBeaconHost` |  | AOnlineBeacon | int32 ListenPort; bool bReuseAddressAndPort; bool bAuthRequired; uint32 MaxAuthTokenSize | `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Public/OnlineBeaconHost.h:27` |
| `AOnlineBeaconHostObject` | `/Script/OnlineSubsystemUtils.OnlineBeaconHostObject` |  | AActor |  | `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Public/OnlineBeaconHostObject.h:19` |
| `APartyBeaconClient` | `/Script/OnlineSubsystemUtils.PartyBeaconClient` |  | AOnlineBeaconClient |  | `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Public/PartyBeaconClient.h:93` |
| `APartyBeaconHost` | `/Script/OnlineSubsystemUtils.PartyBeaconHost` |  | AOnlineBeaconHostObject | bool bLogoutOnSessionTimeout; bool bIsValidationStrRequired; float SessionTimeoutSecs; float TravelSessionTimeoutSecs | `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Public/PartyBeaconHost.h:53` |
| `APlayerCameraManager` | `/Script/Engine.PlayerCameraManager` |  | AActor | float ServerUpdateCameraTimeout | `Source/Runtime/Engine/Classes/Camera/PlayerCameraManager.h:187` |
| `AQosBeaconClient` | `/Script/Qos.QosBeaconClient` |  | AOnlineBeaconClient |  | `Plugins/Online/OnlineFramework/Source/Qos/Public/QosBeaconClient.h:37` |
| `AQosBeaconHost` | `/Script/Qos.QosBeaconHost` |  | AOnlineBeaconHostObject |  | `Plugins/Online/OnlineFramework/Source/Qos/Public/QosBeaconHost.h:15` |
| `ARecastNavMesh` | `/Script/NavigationSystem.RecastNavMesh` |  | ANavigationData |  | `Source/Runtime/NavigationSystem/Public/NavMesh/RecastNavMesh.h:570` |
| `ASpectatorBeaconClient` | `/Script/OnlineSubsystemUtils.SpectatorBeaconClient` |  | AOnlineBeaconClient |  | `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Public/SpectatorBeaconClient.h:85` |
| `ASpectatorBeaconHost` | `/Script/OnlineSubsystemUtils.SpectatorBeaconHost` |  | AOnlineBeaconHostObject | bool bLogoutOnSessionTimeout; bool bIsValidationStrRequired; float SessionTimeoutSecs; float TravelSessionTimeoutSecs | `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Public/SpectatorBeaconHost.h:53` |
| `ATestBeaconClient` | `/Script/OnlineSubsystemUtils.TestBeaconClient` |  | AOnlineBeaconClient |  | `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Classes/TestBeaconClient.h:13` |
| `ATestBeaconHost` | `/Script/OnlineSubsystemUtils.TestBeaconHost` |  | AOnlineBeaconHostObject |  | `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Classes/TestBeaconHost.h:15` |
| `AVLogRenderingActor` | `/Script/RewindDebuggerVLog.VLogRenderingActor` |  | AVisualLoggerRenderingActorBase |  | `Plugins/Animation/GameplayInsights/Source/RewindDebuggerVLog/Private/VLogRenderingActor.h:16` |
| `AVisualLoggerRenderingActor` | `/Script/LogVisualizer.VisualLoggerRenderingActor` |  | AVisualLoggerRenderingActorBase |  | `Source/Developer/LogVisualizer/Private/VisualLoggerRenderingActor.h:22` |
| `AVisualLoggerRenderingActorBase` | `/Script/LogVisualizer.VisualLoggerRenderingActorBase` |  | AActor |  | `Source/Developer/LogVisualizer/Public/VisualLoggerRenderingActorBase.h:21` |
| `AWaterBody` | `/Script/Water.WaterBody` | Abstract | AActor, IWaterBrushActorInterface | TSubclassOf<UWaterBodyRiverComponent> WaterBodyRiverComponentClass; TSubclassOf<UWaterBodyLakeComponent> WaterBodyLakeComponentClass; TSubclassOf<UWaterBodyOceanComponent> WaterBodyOceanComponentClass; TSubclassOf<UWaterBodyCustomComponent> WaterBodyCustomComponentClass | `Plugins/Experimental/Water/Source/Runtime/Public/WaterBodyActor.h:46` |
| `AWaterBrushManager` | `/Script/WaterEditor.WaterBrushManager` |  | AWaterLandscapeBrush |  | `Plugins/Experimental/Water/Source/Editor/Private/WaterBrushManager.h:27` |
| `UAISense` | `/Script/AIModule.AISense` |  | UObject |  | `Source/Runtime/AIModule/Classes/Perception/AISense.h:19` |
| `UAISubsystem` | `/Script/AIModule.AISubsystem` |  | UObject, FTickableGameObject |  | `Source/Runtime/AIModule/Classes/AISubsystem.h:14` |
| `UAISystem` | `/Script/AIModule.AISystem` |  | UAISystemBase |  | `Source/Runtime/AIModule/Classes/AISystem.h:25` |
| `UAISystemBase` | `/Script/Engine.AISystemBase` |  | UObject |  | `Source/Runtime/Engine/Classes/AI/AISystemBase.h:13` |
| `UActorComponent` | `/Script/Engine.ActorComponent` |  | UObject, IInterface_AssetUserData, IAsyncPhysicsStateProcessor | uint8 bReplicateUsingRegisteredSubObjectList : 1 | `Source/Runtime/Engine/Classes/Components/ActorComponent.h:159` |
| `UAimOffsetBlendSpace` | `/Script/Engine.AimOffsetBlendSpace` |  | UBlendSpace |  | `Source/Runtime/Engine/Classes/Animation/AimOffsetBlendSpace.h:19` |
| `UAimOffsetBlendSpace1D` | `/Script/Engine.AimOffsetBlendSpace1D` |  | UBlendSpace1D |  | `Source/Runtime/Engine/Classes/Animation/AimOffsetBlendSpace1D.h:18` |
| `UAmbisonicsEncodingSettings` | `/Script/SoundFields.AmbisonicsEncodingSettings` |  | USoundfieldEncodingSettingsBase |  | `Plugins/Runtime/SoundFields/Source/SoundFields/Public/SoundFields.h:10` |
| `UAnalysisProperties` | `/Script/Engine.AnalysisProperties` |  | UObject |  | `Source/Runtime/Engine/Classes/Animation/BlendSpace.h:29` |
| `UAndroidCameraRuntimeSettings` | `/Script/AndroidCameraEditor.AndroidCameraRuntimeSettings` | DefaultConfig | UObject |  | `Plugins/Media/AndroidCamera/Source/AndroidCameraEditor/Public/AndroidCameraRuntimeSettings.h:14` |
| `UAndroidCameraSettings` | `/Script/AndroidCameraFactory.AndroidCameraSettings` |  | UObject |  | `Plugins/Media/AndroidCamera/Source/AndroidCameraFactory/Public/AndroidCameraSettings.h:15` |
| `UAndroidFileServerRuntimeSettings` | `/Script/AndroidFileServerEditor.AndroidFileServerRuntimeSettings` | DefaultConfig | UObject |  | `Plugins/Runtime/AndroidFileServer/Source/AndroidFileServerEditor/Public/AndroidFileServerRuntimeSettings.h:23` |
| `UAndroidMediaSettings` | `/Script/AndroidMediaFactory.AndroidMediaSettings` |  | UObject |  | `Plugins/Media/AndroidMedia/Source/AndroidMediaFactory/Public/AndroidMediaSettings.h:15` |
| `UAndroidRuntimeSettings` | `/Script/AndroidRuntimeSettings.AndroidRuntimeSettings` |  | UObject | G FString PackageName; G int32 StoreVersion; G int32 StoreVersionOffsetArm64; G int32 StoreVersionOffsetX8664; G FString ApplicationDisplayName; G FString VersionDisplayName; G int32 MinSDKVersion; G int32 TargetSDKVersion; G TEnumAsByte<EAndroidInstallLocation::Type> InstallLocation; G bool bEnableLint; G bool bPackageDataInsideApk; G bool bCreateAllPlatformsInstall; G bool bDisableVerifyOBBOnStartUp; G bool bForceSmallOBBFiles; G bool bAllowLargeOBBFiles; G bool bAllowPatchOBBFile; G bool bAllowOverflowOBBFiles; G bool bDontBundleLibrariesInAPK; G bool bUseExternalFilesDir; G bool bPublicLogFiles; G TEnumAsByte<EAndroidScreenOrientation::Type> Orientation; G float MinAspectRatio; G float MaxAspectRatio; G bool bUseDisplayCutout; G TEnumAsByte<EAndroidRoundedEdgeSafeZoneDirection::Type> RoundedEdgeSafeZone; G bool bAllowResizing; G bool bSupportSizeChanges; G bool bRestoreNotificationsOnReboot; G bool bFullScreen; G bool bEnableNewKeyboard; G TEnumAsByte<EAndroidDepthBufferPreference::Type> DepthBufferPreference; G bool bValidateTextureFormats; G bool bForceCompressNativeLibs; G bool bEnableAdvancedBinaryCompression; G bool bEnableBundle; G bool bEnableUniversalAPK; G bool bBundleABISplit; G bool bBundleLanguageSplit; G bool bBundleDensitySplit; G TArray<FString> ExtraManifestNodeTags; G TArray<FString> ExtraApplicationNodeTags; G FString ExtraApplicationSettings; G TArray<FString> ExtraActivityNodeTags; G FString ExtraActivitySettings; G TArray<FString> ExtraPermissions; G bool bAndroidVoiceEnabled; G bool bRecordPermissionAtStartupEnabled; G bool bEnableMulticastSupport; G bool bPackageForOpenXRImmersive; G bool bPackageForMetaQuest; G bool bRemoveOSIG; G FString KeyStore; G FString KeyAlias; G FString KeyStorePassword; G FString KeyPassword; G FString DebugKeyStore; G FString DebugKeyAlias; G FString DebugKeyStorePassword; G FString DebugKeyPassword; G bool bBuildForArm64 … (+53) | `Source/Runtime/Android/AndroidRuntimeSettings/Classes/AndroidRuntimeSettings.h:206` |
| `UAndroidSDKSettings` | `/Script/AndroidPlatformEditor.AndroidSDKSettings` |  | UObject | G FDirectoryPath SDKPath; G FDirectoryPath NDKPath; G FDirectoryPath JavaPath; G FString SDKAPILevel; G FString NDKAPILevel | `Source/Developer/Android/AndroidPlatformEditor/Private/AndroidSDKSettings.h:19` |
| `UAnimBankData` | `/Script/Engine.AnimBankData` |  | UTransformProviderData |  | `Source/Runtime/Engine/Classes/Animation/AnimBank.h:773` |
| `UAnimBoneCompressionCodec_ACL` | `/Script/ACLPlugin.AnimBoneCompressionCodec_ACL` |  | UAnimBoneCompressionCodec_ACLBase |  | `Plugins/Animation/ACLPlugin/Source/ACLPlugin/Classes/AnimBoneCompressionCodec_ACL.h:13` |
| `UAnimBoneCompressionCodec_ACLCustom` | `/Script/ACLPlugin.AnimBoneCompressionCodec_ACLCustom` |  | UAnimBoneCompressionCodec_ACLBase |  | `Plugins/Animation/ACLPlugin/Source/ACLPlugin/Classes/AnimBoneCompressionCodec_ACLCustom.h:12` |
| `UAnimBoneCompressionCodec_ACLDatabase` | `/Script/ACLPlugin.AnimBoneCompressionCodec_ACLDatabase` |  | UAnimBoneCompressionCodec_ACLBase |  | `Plugins/Animation/ACLPlugin/Source/ACLPlugin/Classes/AnimBoneCompressionCodec_ACLDatabase.h:59` |
| `UAnimBoneCompressionCodec_ACLSafe` | `/Script/ACLPlugin.AnimBoneCompressionCodec_ACLSafe` |  | UAnimBoneCompressionCodec_ACLBase |  | `Plugins/Animation/ACLPlugin/Source/ACLPlugin/Classes/AnimBoneCompressionCodec_ACLSafe.h:12` |
| `UAnimComposite` | `/Script/Engine.AnimComposite` |  | UAnimCompositeBase |  | `Source/Runtime/Engine/Classes/Animation/AnimComposite.h:22` |
| `UAnimCurveCompressionCodec_ACL` | `/Script/ACLPlugin.AnimCurveCompressionCodec_ACL` |  | UAnimCurveCompressionCodec |  | `Plugins/Animation/ACLPlugin/Source/ACLPlugin/Classes/AnimCurveCompressionCodec_ACL.h:14` |
| `UAnimMontage` | `/Script/Engine.AnimMontage` |  | UAnimCompositeBase |  | `Source/Runtime/Engine/Classes/Animation/AnimMontage.h:634` |
| `UAnimRuntimeTransformProviderData` | `/Script/Engine.AnimRuntimeTransformProviderData` |  | UTransformProviderData |  | `Source/Runtime/Engine/Classes/Animation/AnimRuntimeTransformProviderData.h:163` |
| `UAnimSequence` | `/Script/Engine.AnimSequence` |  | UAnimSequenceBase |  | `Source/Runtime/Engine/Classes/Animation/AnimSequence.h:201` |
| `UAnimSequenceTransformProviderData` | `/Script/Engine.AnimSequenceTransformProviderData` |  | UTransformProviderData |  | `Source/Runtime/Engine/Classes/Animation/AnimSequenceTransformProviderData.h:871` |
| `UAnimSequenceTransformProviderDataInstance` | `/Script/Engine.AnimSequenceTransformProviderDataInstance` |  | UAnimSequenceTransformProviderData |  | `Source/Runtime/Engine/Classes/Animation/AnimSequenceTransformProviderData.h:1037` |
| `UAnimStreamable` | `/Script/Engine.AnimStreamable` |  | UAnimSequenceBase |  | `Source/Runtime/Engine/Classes/Animation/AnimStreamable.h:89` |
| `UAnimationCompressionLibraryDatabase` | `/Script/ACLPlugin.AnimationCompressionLibraryDatabase` |  | UObject |  | `Plugins/Animation/ACLPlugin/Source/ACLPlugin/Classes/AnimationCompressionLibraryDatabase.h:50` |
| `UAnimationModifierSettings` | `/Script/AnimationModifiers.AnimationModifierSettings` |  | UDeveloperSettings |  | `Source/Editor/AnimationModifiers/Private/AnimationModifierSettings.h:12` |
| `UAnimationSettings` | `/Script/Engine.AnimationSettings` |  | UDeveloperSettings |  | `Source/Runtime/Engine/Classes/Animation/AnimationSettings.h:20` |
| `UAnimationSharingManager` | `/Script/AnimationSharing.AnimationSharingManager` |  | UObject |  | `Plugins/Developer/AnimationSharing/Source/AnimationSharing/Public/AnimationSharingManager.h:509` |
| `UAnimationSharingSetup` | `/Script/AnimationSharing.AnimationSharingSetup` |  | UObject |  | `Plugins/Developer/AnimationSharing/Source/AnimationSharing/Public/AnimationSharingSetup.h:12` |
| `UAppleARKitSettings` | `/Script/AppleARKit.AppleARKitSettings` |  | UObject, FSelfRegisteringExec | bool bRequireARKitSupport; FString FaceTrackingLogDir; TArray<ELivelinkTrackingType> LivelinkTrackingTypes; bool bFaceTrackingLogData; bool bFaceTrackingWriteEachFrame; EARFaceTrackingFileWriterType FaceTrackingFileWriterType; bool bShouldWriteCameraImagePerFrame; float WrittenCameraImageScale; int32 WrittenCameraImageQuality; ETextureRotationDirection WrittenCameraImageRotation; int32 LiveLinkPublishingPort; FName DefaultFaceTrackingLiveLinkSubjectName; FName DefaultPoseTrackingLiveLinkSubjectName; EARFaceTrackingDirection DefaultFaceTrackingDirection; bool bAdjustThreadPrioritiesDuringARSession; int32 GameThreadPriorityOverride; int32 RenderThreadPriorityOverride; FString ARKitTimecodeProvider | `Plugins/Runtime/AR/AppleAR/AppleARKit/Source/AppleARKit/Public/AppleARKitSettings.h:35` |
| `UAppleProResMediaSettings` | `/Script/AppleProResMedia.AppleProResMediaSettings` |  | UObject |  | `Plugins/Media/AppleProResMedia/Source/AppleProResMedia/Private/AppleProResMediaSettings.h:14` |
| `UApvMediaSettings` | `/Script/ApvMedia.ApvMediaSettings` |  | UDeveloperSettings |  | `Plugins/Media/TmvMedia/Source/ApvMedia/Private/ApvMediaSettings.h:9` |
| `UArrayProperty` | `/Script/CoreUObject.ArrayProperty` |  | UProperty |  | `Source/Runtime/CoreUObject/Public/UObject/UnrealTypePrivate.h:811` |
| `UAudioEndpointSettingsBase` | `/Script/AudioExtensions.AudioEndpointSettingsBase` |  | UObject |  | `Source/Runtime/AudioExtensions/Public/IAudioEndpoint.h:52` |
| `UAudioLinkSettingsAbstract` | `/Script/AudioLinkCore.AudioLinkSettingsAbstract` |  | UObject |  | `Source/Runtime/AudioLink/AudioLinkCore/Public/AudioLinkSettingsAbstract.h:30` |
| `UAudioModulationDestination` | `/Script/AudioModulation.AudioModulationDestination` |  | UObject |  | `Plugins/Runtime/AudioModulation/Source/AudioModulation/Public/AudioModulationDestination.h:14` |
| `UAudioPlatformSettings` | `/Script/Engine.AudioPlatformSettings` |  | UPlatformSettings |  | `Source/Runtime/Engine/Classes/Sound/AudioPlatformSettings.h:33` |
| `UAudioSettings` | `/Script/Engine.AudioSettings` |  | UDeveloperSettings |  | `Source/Runtime/Engine/Classes/Sound/AudioSettings.h:125` |
| `UAutomatedMaterialPerfTestProjectSettings` | `/Script/AutomatedPerfTesting.AutomatedMaterialPerfTestProjectSettings` | DefaultConfig | UDeveloperSettings | TArray<FSoftObjectPath> MaterialsToTest; bool bCaptureScreenshots; float WarmUpTime; float SoakTime; float CooldownTime; FSoftObjectPath MaterialPerformanceTestMap; FString GameModeOverride; TEnumAsByte<ECameraProjectionMode::Type> CameraProjectionMode; float PlateDistanceFromCamera; FSoftObjectPath MaterialPlate | `Plugins/Performance/AutomatedPerfTesting/Source/AutomatedPerfTesting/Public/AutomatedMaterialPerfTest.h:18` |
| `UAutomatedPerfTestProjectSettings` | `/Script/AutomatedPerfTesting.AutomatedPerfTestProjectSettings` |  | UDeveloperSettings | float TeardownToExitDelay | `Plugins/Performance/AutomatedPerfTesting/Source/AutomatedPerfTesting/Public/AutomatedPerfTestProjectSettings.h:13` |
| `UAutomatedProfileGoTestProjectSettings` | `/Script/AutomatedPerfTesting.AutomatedProfileGoTestProjectSettings` | DefaultConfig | UDeveloperSettings | TArray<FProfileGoScenarioAPT> Scenarios; TArray<FProfileGoCollectionAPT> Collections; TArray<FProfileGoCommandAPT> Commands; TArray<FProfileGoGeneratedScenarioAPT> GeneratedScenarios | `Plugins/Performance/AutomatedPerfTesting/Source/AutomatedPerfTesting/Public/AutomatedProfileGoTest.h:67` |
| `UAutomatedReplayPerfTestProjectSettings` | `/Script/AutomatedPerfTesting.AutomatedReplayPerfTestProjectSettings` | DefaultConfig | UDeveloperSettings | TArray<FFilePath> ReplaysToTest | `Plugins/Performance/AutomatedPerfTesting/Source/AutomatedPerfTesting/Public/AutomatedReplayPerfTest.h:19` |
| `UAutomatedSequencePerfTestProjectSettings` | `/Script/AutomatedPerfTesting.AutomatedSequencePerfTestProjectSettings` | DefaultConfig | UDeveloperSettings | TArray<FAutomatedPerfTestMapSequenceCombo> MapsAndSequencesToTest; float SequenceStartDelay | `Plugins/Performance/AutomatedPerfTesting/Source/AutomatedPerfTesting/Public/AutomatedSequencePerfTest.h:47` |
| `UAutomatedStaticCameraPerfTestProjectSettings` | `/Script/AutomatedPerfTesting.AutomatedStaticCameraPerfTestProjectSettings` | DefaultConfig | UDeveloperSettings | TArray<FSoftObjectPath> MapsToTest; FString GameModeOverride; bool bCaptureScreenshots; float WarmUpTime; float SoakTime; float CooldownTime | `Plugins/Performance/AutomatedPerfTesting/Source/AutomatedPerfTesting/Public/StaticCameraTests/AutomatedStaticCameraPerfTestBase.h:12` |
| `UAutomationControllerSettings` | `/Script/AutomationController.AutomationControllerSettings` |  | UObject | TArray<FAutomatedTestGroup> Groups; bool bSuppressLogErrors; bool bSuppressLogWarnings; bool bElevateLogWarningsToErrors; TArray<FString> SuppressedLogCategories; bool bKeepPIEOpen; bool bAutoExpandSingleItemSubgroups; bool bSortTestsByFailure; bool bPruneLogsOnSuccess; bool bTreatLogWarningsAsTestErrors; float CheckTestIntervalSeconds; float GameInstanceLostTimerSeconds; FString TelemetryDirectory; bool bResetTelemetryStorageOnNewSession | `Source/Developer/AutomationController/Public/AutomationControllerSettings.h:207` |
| `UAutomationTestExcludelistConfig` | `/Script/AutomationTest.AutomationTestExcludelistConfig` |  | UAutomationTestPlatformSettings | TArray<FAutomationTestExcludelistEntry> ExcludeTest | `Source/Runtime/AutomationTest/Public/AutomationTestExcludelist.h:322` |
| `UAutomationTestExcludelistSettings` | `/Script/AutomationTest.AutomationTestExcludelistSettings` |  | UAutomationTestPlatformSettings | TArray<FName> SupportedRHIs | `Source/Runtime/AutomationTest/Public/AutomationTestExcludelist.h:89` |
| `UAutomationTestSettings` | `/Script/Engine.AutomationTestSettings` |  | UObject |  | `Source/Runtime/Engine/Classes/Tests/AutomationTestSettings.h:339` |
| `UAvaMaskSettings` | `/Script/AvalancheMask.AvaMaskSettings` |  | UDeveloperSettings | TSoftObjectPtr<UMaterialFunctionInterface> MaterialFunction | `Plugins/VirtualProduction/Avalanche/Source/AvalancheMask/Private/AvaMaskSettings.h:17` |
| `UAvaMaterialCacheSettings` | `/Script/AvalancheMaterial.AvaMaterialCacheSettings` |  | UDeveloperSettings | FName RealtimeProfile; FName OfflineProfile; TArray<FAvaShaderProfile> ShaderProfiles | `Plugins/VirtualProduction/Avalanche/Source/AvalancheMaterial/Internal/MaterialCache/AvaMaterialCacheSettings.h:85` |
| `UAvaMediaSettings` | `/Script/AvalancheMedia.AvaMediaSettings` |  | UDeveloperSettings | bool bKeepPagesLoaded; FAvaInstanceSettings AvaInstanceSettings; FAvaPlayableSettings PlayableSettings; int32 ManagedInstanceCacheMaximumSize | `Plugins/VirtualProduction/Avalanche/Source/AvalancheMedia/Public/AvaMediaSettings.h:87` |
| `UAvaShapeSettings` | `/Script/AvalancheShapes.AvaShapeSettings` |  | UDeveloperSettings | bool bForceDisableShapeCollision | `Plugins/VirtualProduction/Avalanche/Source/AvalancheShapes/Public/AvaShapeSettings.h:10` |
| `UAvfMediaSettings` | `/Script/AvfMediaFactory.AvfMediaSettings` |  | UObject |  | `Plugins/Media/AvfMedia/Source/AvfMediaFactory/Public/AvfMediaSettings.h:16` |
| `UAvoidanceManager` | `/Script/Engine.AvoidanceManager` |  | UObject, FSelfRegisteringExec |  | `Source/Runtime/Engine/Classes/AI/Navigation/AvoidanceManager.h:86` |
| `UAxFImporterOptions` | `/Script/AxFImporter.AxFImporterOptions` |  | UObject |  | `Plugins/Enterprise/AxFImporter/Source/AxFImporter/Private/AxFImporterOptions.h:12` |
| `UBasicReplicationGraph` | `/Script/ReplicationGraph.BasicReplicationGraph` |  | UReplicationGraph |  | `Plugins/Runtime/ReplicationGraph/Source/Public/BasicReplicationGraph.h:38` |
| `UBehaviorTreeManager` | `/Script/AIModule.BehaviorTreeManager` |  | UObject |  | `Source/Runtime/AIModule/Classes/BehaviorTree/BehaviorTreeManager.h:32` |
| `UBlendSpace` | `/Script/Engine.BlendSpace` |  | UAnimationAsset, IInterpolationIndexProvider |  | `Source/Runtime/Engine/Classes/Animation/BlendSpace.h:469` |
| `UBlendSpace1D` | `/Script/Engine.BlendSpace1D` |  | UBlendSpace |  | `Source/Runtime/Engine/Classes/Animation/BlendSpace1D.h:18` |
| `UBlueprint` | `/Script/Engine.Blueprint` |  | UBlueprintCore, IBlueprintPropertyGuidProvider |  | `Source/Runtime/Engine/Classes/Engine/Blueprint.h:401` |
| `UBlueprintRuntimeSettings` | `/Script/BlueprintRuntime.BlueprintRuntimeSettings` |  | UObject |  | `Source/Runtime/BlueprintRuntime/Public/BlueprintRuntimeSettings.h:44` |
| `UBoolProperty` | `/Script/CoreUObject.BoolProperty` |  | UProperty |  | `Source/Runtime/CoreUObject/Public/UObject/UnrealTypePrivate.h:430` |
| `UBuoyancyRuntimeSettings` | `/Script/Buoyancy.BuoyancyRuntimeSettings` | DefaultConfig | UDeveloperSettings | bool bBuoyancyEnabled; bool bKeepFloatingObjectsAwake; float WaterDensity; float WaterDrag; float WaterLift; TEnumAsByte<ECollisionChannel> CollisionChannelForWaterObjects; int32 MaxNumBoundsSubdivisions; float MinBoundsSubdivisionVol; uint8 SurfaceTouchCallbackFlags; float MinVelocityForSurfaceTouchCallback; bool bEnableSplineKeyCacheGrid; float SplineKeyCacheGridSize; uint32 SplineKeyCacheLimit | `Plugins/Experimental/Buoyancy/Source/Runtime/Public/BuoyancyRuntimeSettings.h:14` |
| `UByteProperty` | `/Script/CoreUObject.ByteProperty` |  | UNumericProperty |  | `Source/Runtime/CoreUObject/Public/UObject/UnrealTypePrivate.h:204` |
| `UCEClonerEffectorSettings` | `/Script/ClonerEffector.CEClonerEffectorSettings` |  | UDeveloperSettings | FLinearColor VisualizerInnerColor; FLinearColor VisualizerOuterColor; bool bSpawnDefaultActorAttached; TSoftObjectPtr<UStaticMesh> DefaultStaticMesh; TSoftObjectPtr<UMaterialInterface> DefaultMaterial; bool bReduceMotionGhosting | `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Private/Settings/CEClonerEffectorSettings.h:14` |
| `UCQTestSettings` | `/Script/CQTest.CQTestSettings` |  | UDeveloperSettingsBackedByCVars |  | `Source/Developer/CQTest/Public/CQTestSettings.h:28` |
| `UChaosSolverSettings` | `/Script/ChaosSolverEngine.ChaosSolverSettings` |  | UDeveloperSettings, IChaosSolverActorClassProvider |  | `Source/Runtime/Experimental/ChaosSolverEngine/Public/Chaos/ChaosSolverSettings.h:13` |
| `UChaosVDCoreSettings` | `/Script/ChaosVD.ChaosVDCoreSettings` |  | UChaosVDSettingsObjectBase | TSoftObjectPtr<UMaterial> QueryOnlyMeshesMaterial; TSoftObjectPtr<UMaterial> SimOnlyMeshesMaterial; TSoftObjectPtr<UMaterial> InstancedMeshesMaterial; TSoftObjectPtr<UMaterial> InstancedMeshesQueryOnlyMaterial; FSoftClassPath SkySphereActorClass; TSoftObjectPtr<UTextureCube> AmbientCubeMapTexture; TSoftObjectPtr<UStaticMesh> BoxMesh; TSoftObjectPtr<UStaticMesh> SphereMesh | `Plugins/ChaosVD/Source/ChaosVD/Public/Settings/ChaosVDCoreSettings.h:80` |
| `UChildConnection` | `/Script/Engine.ChildConnection` |  | UNetConnection |  | `Source/Runtime/Engine/Classes/Engine/ChildConnection.h:25` |
| `UChunkDependencyInfo` | `/Script/CoreUObject.ChunkDependencyInfo` |  | UObject |  | `Source/Runtime/CoreUObject/Public/Misc/ChunkDependencyInfo.h:58` |
| `UCineCameraComponent` | `/Script/CinematicCamera.CineCameraComponent` |  | UCameraComponent |  | `Source/Runtime/CinematicCamera/Public/CineCameraComponent.h:20` |
| `UCineCameraSettings` | `/Script/CinematicCamera.CineCameraSettings` |  | UDeveloperSettings |  | `Source/Runtime/CinematicCamera/Public/CineCameraSettings.h:299` |
| `UClass` | `/Script/CoreUObject.Class` |  | UStruct |  | `Source/Runtime/CoreUObject/Public/UObject/Class.h:3892` |
| `UClassProperty` | `/Script/CoreUObject.ClassProperty` |  | UObjectProperty |  | `Source/Runtime/CoreUObject/Public/UObject/UnrealTypePrivate.h:622` |
| `UClassViewerProjectSettings` | `/Script/ClassViewer.ClassViewerProjectSettings` |  | UObject |  | `Source/Editor/ClassViewer/Public/ClassViewerProjectSettings.h:23` |
| `UCollisionProfile` | `/Script/Engine.CollisionProfile` |  | UDeveloperSettings |  | `Source/Runtime/Engine/Classes/Engine/CollisionProfile.h:159` |
| `UCommonGameViewportClient` | `/Script/CommonUI.CommonGameViewportClient` |  | UGameViewportClient |  | `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonGameViewportClient.h:23` |
| `UCompositeCorePluginSettings` | `/Script/CompositeCore.CompositeCorePluginSettings` |  | UDeveloperSettings |  | `Plugins/Compositing/CompositeCore/Source/CompositeCore/Public/CompositeCoreSettings.h:26` |
| `UConcertCVarConfig` | `/Script/ConsoleVariablesEditor.ConcertCVarConfig` |  | UObject |  | `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditor/Private/MultiUser/ConsoleVariableSyncData.h:49` |
| `UConcertCVarSynchronization` | `/Script/ConsoleVariablesEditor.ConcertCVarSynchronization` |  | UObject |  | `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditor/Private/MultiUser/ConsoleVariableSyncData.h:14` |
| `UConcertClientConfig` | `/Script/ConcertClient.ConcertClientConfig` |  | UObject |  | `Plugins/Developer/Concert/ConcertMain/Source/ConcertClient/Public/ConcertClientSettings.h:145` |
| `UConcertEndpointConfig` | `/Script/ConcertTransport.ConcertEndpointConfig` |  | UObject |  | `Plugins/Developer/Concert/ConcertMain/Source/ConcertTransport/Public/ConcertTransportSettings.h:34` |
| `UConcertServerConfig` | `/Script/ConcertServer.ConcertServerConfig` |  | UObject |  | `Plugins/Developer/Concert/ConcertMain/Source/ConcertServer/Public/ConcertServerSettings.h:31` |
| `UConcertSessionRecordSettings` | `/Script/ConcertTakeRecorder.ConcertSessionRecordSettings` |  | UObject |  | `Plugins/VirtualProduction/MultiUserTakes/Source/ConcertTakeRecorder/Private/ConcertTakeRecorderMessages.h:51` |
| `UConcertTakeSynchronization` | `/Script/ConcertTakeRecorder.ConcertTakeSynchronization` |  | UObject |  | `Plugins/VirtualProduction/MultiUserTakes/Source/ConcertTakeRecorder/Private/ConcertTakeRecorderMessages.h:11` |
| `UConsoleVariablesEditorProjectSettings` | `/Script/ConsoleVariablesEditor.ConsoleVariablesEditorProjectSettings` |  | UObject | EConsoleVariablesEditorRowDisplayType UncheckedRowDisplayType; EConsoleVariablesEditorPresetImportMode PresetImportMode; bool bAddAllChangedConsoleVariablesToCurrentPreset; TSet<FString> ChangedConsoleVariableSkipList | `Plugins/Editor/ConsoleVariablesEditor/Source/ConsoleVariablesEditor/Public/ConsoleVariablesEditorProjectSettings.h:35` |
| `UContentBundleEngineSubsystem` | `/Script/Engine.ContentBundleEngineSubsystem` |  | UEngineSubsystem | TSoftClassPtr<UContentBundleTypeFactory> ContentBundleTypeFactoryClass | `Source/Runtime/Engine/Public/WorldPartition/ContentBundle/ContentBundleEngineSubsystem.h:17` |
| `UControlRigSettings` | `/Script/ControlRig.ControlRigSettings` |  | UDeveloperSettings |  | `Plugins/Animation/ControlRig/Source/ControlRig/Public/Settings/ControlRigSettings.h:58` |
| `UCookerSettings` | `/Script/DeveloperToolSettings.CookerSettings` |  | UDeveloperSettings | G bool bEnableCookOnTheSide; G bool bEnableBuildDDCInBackground; G bool bIterativeCookingForLaunchOn; G bool bIterativeCookingForFileCookContent; G bool bCookOnTheFlyForLaunchOn; G ECookProgressDisplayMode CookProgressDisplayMode; G bool bIgnoreIniSettingsOutOfDateForIteration; G bool bIgnoreScriptPackagesOutOfDateForIteration; G bool bCompileBlueprintsInDevelopmentMode; G EBlueprintComponentDataCookingMethod BlueprintComponentDataCookingMethod; G EBlueprintPropertyGuidsCookingMethod BlueprintPropertyGuidsCookingMethod; G TArray<FString> ClassesExcludedOnDedicatedServer; G TArray<FString> ModulesExcludedOnDedicatedServer; G TArray<FString> ClassesExcludedOnDedicatedClient; G TArray<FString> ModulesExcludedOnDedicatedClient; G TArray<FString> VersionedIntRValues; G int32 DefaultASTCQualityBySpeed; G int32 DefaultASTCQualityBySize; G int32 DefaultASTCQualityBySizeHQ; G uint32 bAllowASTCHDRProfile : 1; G bool bCookBlueprintComponentTemplateData | `Source/Developer/DeveloperToolSettings/Classes/CookerSettings.h:89` |
| `UCrowdManager` | `/Script/AIModule.CrowdManager` |  | UCrowdManagerBase | TArray<FCrowdAvoidanceConfig> AvoidanceConfig; TArray<FCrowdAvoidanceSamplingPattern> SamplingPatterns; int32 MaxAgents; float MaxAgentRadius; int32 MaxAvoidedAgents; int32 MaxAvoidedWalls; float NavmeshCheckInterval; float PathOptimizationInterval; float SeparationDirClamp; float PathOffsetRadiusMultiplier; uint32 bResolveCollisions : 1 | `Source/Runtime/AIModule/Classes/Navigation/CrowdManager.h:178` |
| `UCsvMetricsSubsystem` | `/Script/CsvMetrics.CsvMetricsSubsystem` | DefaultConfig | UWorldSubsystem | TArray<TSubclassOf<UWorldMetricInterface>> MetricClasses | `Plugins/WorldMetrics/Source/CsvMetrics/Public/CsvMetricsSubsystem.h:16` |
| `UCustomizableObject` | `/Script/CustomizableObject.CustomizableObject` |  | UObject |  | `Plugins/Mutable/Source/CustomizableObject/Public/MuCO/CustomizableObject.h:172` |
| `UDEPRECATED_DataLayer` | `/Script/Engine.DEPRECATED_DataLayer` | PerObjectConfig | UObject |  | `Source/Runtime/Engine/Public/WorldPartition/DataLayer/Deprecated/DeprecatedDataLayer.h:59` |
| `UDEPRECATED_GeometryCacheTrack_FlipbookAnimation` | `/Script/GeometryCache.DEPRECATED_GeometryCacheTrack_FlipbookAnimation` |  | UGeometryCacheTrack |  | `Plugins/Runtime/GeometryCache/Source/GeometryCache/Classes/GeometryCacheTrackFlipbookAnimation.h:11` |
| `UDEPRECATED_GeometryCacheTrack_TransformAnimation` | `/Script/GeometryCache.DEPRECATED_GeometryCacheTrack_TransformAnimation` |  | UGeometryCacheTrack |  | `Plugins/Runtime/GeometryCache/Source/GeometryCache/Classes/GeometryCacheTrackTransformAnimation.h:12` |
| `UDEPRECATED_GeometryCacheTrack_TransformGroupAnimation` | `/Script/GeometryCache.DEPRECATED_GeometryCacheTrack_TransformGroupAnimation` |  | UGeometryCacheTrack |  | `Plugins/Runtime/GeometryCache/Source/GeometryCache/Classes/GeometryCacheTrackTransformGroupAnimation.h:12` |
| `UDEPRECATED_MetaData` | `/Script/CoreUObject.DEPRECATED_MetaData` |  | UObject |  | `Source/Runtime/CoreUObject/Public/UObject/MetaData.h:33` |
| `UDMXProtocolSettings` | `/Script/DMXProtocol.DMXProtocolSettings` | DefaultConfig | UObject | TArray<FDMXInputPortConfig> InputPortConfigs; TArray<FDMXOutputPortConfig> OutputPortConfigs; uint32 SendingRefreshRate; TSet<FName> FixtureCategories; TSet<FDMXAttribute> Attributes; bool bDefaultSendDMXEnabled; bool bDefaultReceiveDMXEnabled; bool bAllFixturePatchesReceiveDMXInEditor; FString InterfaceIPAddress_DEPRECATED; int32 GlobalArtNetUniverseOffset_DEPRECATED; int32 GlobalSACNUniverseOffset_DEPRECATED | `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocol/Public/DMXProtocolSettings.h:21` |
| `UDataDrivenConsoleVariableSettings` | `/Script/Engine.DataDrivenConsoleVariableSettings` |  | UDeveloperSettings |  | `Source/Runtime/Engine/Classes/DataDrivenCVars/DataDrivenCVars.h:86` |
| `UDataLayerInstance` | `/Script/Engine.DataLayerInstance` | PerObjectConfig | UObject |  | `Source/Runtime/Engine/Public/WorldPartition/DataLayer/DataLayerInstance.h:58` |
| `UDataLayerInstancePrivate` | `/Script/Engine.DataLayerInstancePrivate` | PerObjectConfig | UDataLayerInstance |  | `Source/Runtime/Engine/Public/WorldPartition/DataLayer/DataLayerInstancePrivate.h:9` |
| `UDataLayerInstanceWithAsset` | `/Script/Engine.DataLayerInstanceWithAsset` | PerObjectConfig | UDataLayerInstance |  | `Source/Runtime/Engine/Public/WorldPartition/DataLayer/DataLayerInstanceWithAsset.h:9` |
| `UDataLayerManager` | `/Script/Engine.DataLayerManager` |  | UObject | TSoftClassPtr<UDataLayerLoadingPolicy> DataLayerLoadingPolicyClass; TSoftClassPtr<UDataLayerInstanceWithAsset> DataLayerInstanceWithAssetClass | `Source/Runtime/Engine/Public/WorldPartition/DataLayer/DataLayerManager.h:45` |
| `UDataLayerSubsystem` | `/Script/Engine.DataLayerSubsystem` |  | UWorldSubsystem | TSoftClassPtr<UDataLayerLoadingPolicy> DataLayerLoadingPolicyClass | `Source/Runtime/Engine/Public/WorldPartition/DataLayer/DataLayerSubsystem.h:25` |
| `UDataLayerToAssetCommandlet` | `/Script/UnrealEd.DataLayerToAssetCommandlet` |  | UCommandlet | FString DestinationFolder; bool bPerformSavePackages; bool bIgnoreActorLoadingErrors | `Source/Editor/UnrealEd/Classes/Commandlets/WorldPartitionDataLayerToAssetCommandLet.h:137` |
| `UDataStreamDefinitions` | `/Script/IrisCore.DataStreamDefinitions` |  | UObject | TArray<FDataStreamDefinition> DataStreamDefinitions | `Source/Runtime/Net/Iris/Private/Iris/DataStream/DataStreamDefinitions.h:47` |
| `UDaySequenceProjectSettings` | `/Script/DaySequence.DaySequenceProjectSettings` |  | UDeveloperSettings |  | `Plugins/Experimental/DaySequence/Source/DaySequence/Private/DaySequenceProjectSettings.h:11` |
| `UDebugCameraControllerSettings` | `/Script/Engine.DebugCameraControllerSettings` |  | UDeveloperSettings |  | `Source/Runtime/Engine/Classes/Engine/DebugCameraControllerSettings.h:31` |
| `UDebugDrawService` | `/Script/Engine.DebugDrawService` |  | UBlueprintFunctionLibrary |  | `Source/Runtime/Engine/Classes/Debug/DebugDrawService.h:20` |
| `UDelegateProperty` | `/Script/CoreUObject.DelegateProperty` |  | UProperty |  | `Source/Runtime/CoreUObject/Public/UObject/UnrealTypePrivate.h:913` |
| `UDemoNetConnection` | `/Script/Engine.DemoNetConnection` |  | UNetConnection |  | `Source/Runtime/Engine/Classes/Engine/DemoNetConnection.h:18` |
| `UDemoNetDriver` | `/Script/Engine.DemoNetDriver` |  | UNetDriver | float CheckpointSaveMaxMSPerFrame | `Source/Runtime/Engine/Classes/Engine/DemoNetDriver.h:150` |
| `UDemoPendingNetGame` | `/Script/Engine.DemoPendingNetGame` |  | UPendingNetGame |  | `Source/Runtime/Engine/Classes/Engine/DemoPendingNetGame.h:13` |
| `UDeprecatedDataLayerInstance` | `/Script/Engine.DeprecatedDataLayerInstance` | PerObjectConfig | UDataLayerInstance |  | `Source/Runtime/Engine/Public/WorldPartition/DataLayer/Deprecated/DeprecatedDataLayer.h:148` |
| `UDestructibleComponent` | `/Script/ApexDestruction.DestructibleComponent` |  | USkinnedMeshComponent, IDestructibleInterface |  | `Plugins/Runtime/ApexDestruction/Source/ApexDestruction/Public/DestructibleComponent.h:30` |
| `UDisasterRecoverClientConfig` | `/Script/DisasterRecoveryClient.DisasterRecoverClientConfig` |  | UObject |  | `Plugins/Developer/Concert/ConcertApp/DisasterRecoveryClient/Source/DisasterRecoveryClient/Private/DisasterRecoverySettings.h:7` |
| `UDisplayClusterEditorSettings` | `/Script/DisplayClusterEditor.DisplayClusterEditorSettings` |  | UObject |  | `Plugins/Runtime/nDisplay/Source/DisplayClusterEditor/Private/Settings/DisplayClusterEditorSettings.h:13` |
| `UDisplayClusterMessageInterceptionSettings` | `/Script/DisplayClusterMessageInterception.DisplayClusterMessageInterceptionSettings` |  | UObject |  | `Plugins/Runtime/nDisplay/Source/DisplayClusterMessageInterceptor/Public/DisplayClusterMessageInterceptionSettings.h:34` |
| `UDisplayClusterNetConnection` | `/Script/DisplayClusterReplication.DisplayClusterNetConnection` |  | UIpConnection |  | `Plugins/Runtime/nDisplay/Source/DisplayClusterReplication/Public/DisplayClusterNetConnection.h:18` |
| `UDisplayClusterNetDriver` | `/Script/DisplayClusterReplication.DisplayClusterNetDriver` |  | UIpNetDriver |  | `Plugins/Runtime/nDisplay/Source/DisplayClusterReplication/Public/DisplayClusterNetDriver.h:49` |
| `UDoubleProperty` | `/Script/CoreUObject.DoubleProperty` |  | UNumericProperty |  | `Source/Runtime/CoreUObject/Public/UObject/UnrealTypePrivate.h:408` |
| `UDownlinkBandwidthManagerConfig` | `/Script/DownlinkBandwidthManager.DownlinkBandwidthManagerConfig` |  | UObject | int32 RolloutPercentage; bool EnforceDistributionAllocation | `Source/Runtime/Online/Experimental/DownlinkBandwidthManager/Public/DownlinkBandwidthManagerConfig.h:10` |
| `UEOSSettings` | `/Script/OnlineSubsystemEOS.EOSSettings` | DefaultConfig | URuntimeOptionsBase | FString CacheDir; FString DefaultArtifactName; FString PlatformConfigName; FString RTCBackgroundMode; int32 TickBudgetInMilliseconds; bool bEnableOverlay; bool bEnableSocialOverlay; bool bEnableEditorOverlay; bool bPreferPersistentAuth; TArray<FString> TitleStorageTags; int32 TitleStorageReadChunkLength; TArray<FArtifactSettings> Artifacts; TArray<FString> AuthScopeFlags; bool bUseEAS; bool bUseEOSConnect; bool bUseEOSRTC; bool bUseNamedPlatformConfig; bool bUseNewEcomFlow; bool bUseNewLoginFlow; FString SteamTokenType; FString NintendoTokenType | `Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS/Public/EOSSettings.h:103` |
| `UEditorEngine` | `/Script/UnrealEd.EditorEngine` |  | UEngine |  | `Source/Editor/UnrealEd/Classes/Editor/EditorEngine.h:399` |
| `UElectraProtronFactorySettings` | `/Script/ElectraProtronFactory.ElectraProtronFactorySettings` |  | UObject |  | `Plugins/Media/ElectraPlayer/Source/ElectraProtronFactory/Private/ElectraProtronFactorySettings.h:10` |
| `UEndpointSubmix` | `/Script/Engine.EndpointSubmix` |  | USoundSubmixBase |  | `Source/Runtime/Engine/Classes/Sound/SoundSubmix.h:572` |
| `UEngine` | `/Script/Engine.Engine` |  | UObject , FExec | FSoftClassPath NavigationSystemConfigClassName; uint32 GlobalNetTravelCount; TArray<FNetDriverDefinition> NetDriverDefinitions; TArray<FIrisNetDriverConfig> IrisNetDriverConfigs | `Source/Runtime/Engine/Classes/Engine/Engine.h:725` |
| `UEngineBaseTypes` | `/Script/Engine.EngineBaseTypes` |  | UObject |  | `Source/Runtime/Engine/Classes/Engine/EngineBaseTypes.h:1178` |
| `UEngineReplicationBridge` | `/Script/Engine.EngineReplicationBridge` |  | UObjectReplicationBridge | FName ActorFactoryName; FName SubObjectFactoryName | `Source/Runtime/Engine/Public/Net/Iris/ReplicationSystem/EngineReplicationBridge.h:89` |
| `UEngineTypes` | `/Script/Engine.EngineTypes` |  | UObject |  | `Source/Runtime/Engine/Classes/Engine/EngineTypes.h:4059` |
| `UEnum` | `/Script/CoreUObject.Enum` |  | UField |  | `Source/Runtime/CoreUObject/Public/UObject/Class.h:2876` |
| `UEnumProperty` | `/Script/CoreUObject.EnumProperty` |  | UProperty |  | `Source/Runtime/CoreUObject/Public/UObject/UnrealTypePrivate.h:1021` |
| `UEscalationManagerConfig` | `/Script/NetCore.EscalationManagerConfig` | PerObjectConfig | UStatePerObjectConfig |  | `Source/Runtime/Net/Core/Public/Net/Core/Connection/EscalationStates.h:754` |
| `UExternalDataLayerEngineSubsystem` | `/Script/Engine.ExternalDataLayerEngineSubsystem` |  | UEngineSubsystem, FTickableGameObject | TSubclassOf<UExternalDataLayerInjectionPolicy> InjectionPolicyClass | `Source/Runtime/Engine/Public/WorldPartition/DataLayer/ExternalDataLayerEngineSubsystem.h:24` |
| `UExternalDataLayerInstance` | `/Script/Engine.ExternalDataLayerInstance` | PerObjectConfig | UDataLayerInstanceWithAsset |  | `Source/Runtime/Engine/Public/WorldPartition/DataLayer/ExternalDataLayerInstance.h:12` |
| `UField` | `/Script/CoreUObject.Field` | Abstract | UObject |  | `Source/Runtime/CoreUObject/Public/UObject/Class.h:170` |
| `UFieldOfViewNetObjectPrioritizerConfig` | `/Script/IrisCore.FieldOfViewNetObjectPrioritizerConfig` |  | UNetObjectPrioritizerConfig | float InnerSphereRadius; float InnerSpherePriority; float OuterSphereRadius; float OuterSpherePriority; float ConeFieldOfViewDegrees; float InnerConeLength; float ConeLength; float MinConePriority; float MaxConePriority; float LineOfSightWidth; float LineOfSightPriority; float OutsidePriority | `Source/Runtime/Net/Iris/Public/Iris/ReplicationSystem/Prioritization/FieldOfViewNetObjectPrioritizer.h:13` |
| `UFloatProperty` | `/Script/CoreUObject.FloatProperty` |  | UNumericProperty |  | `Source/Runtime/CoreUObject/Public/UObject/UnrealTypePrivate.h:386` |
| `UFunction` | `/Script/CoreUObject.Function` |  | UStruct |  | `Source/Runtime/CoreUObject/Public/UObject/Class.h:2561` |
| `UFusionSamplerConfig` | `/Script/HarmonixDsp.FusionSamplerConfig` |  | UHarmonixDeveloperSettings |  | `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/FusionSampler/FusionSamplerConfig.h:12` |
| `UGDKNetDriver` | `/Script/GDKNetDriver.GDKNetDriver` |  | UIpNetDriver |  | `Plugins/Online/Microsoft/GDKNetDriver/Source/Public/GDKNetDriver.h:12` |
| `UGDKTargetSettings` | `/Script/GDKPlatformEditor.GDKTargetSettings` | Abstract | UObject | EGDKForegroundColor ApplicationForegroundColor; FColor ApplicationBackgroundColor; FGDKPackageStringResources CultureStringResources; TArray<FGDKLocalizedPackageResources> PerCultureResources; TMap<FString,FString> StageIdOverrides; bool bUseSimplifiedUserModel; TArray<FGDKUriActivationProtocol> UriActivationProtocols; FString DefaultDisplayName; FString PackageName; FString PublisherName; FString PublisherDisplayName; FString StoreId; FString TitleId; FString PrimaryServiceConfigId; FString MSAAppId; FString ProductId; FString PackageVersion; bool bIncludeEngineVersionInPackageVersion; TArray<FGDKCustomChunkMapping> CustomChunkMapping; bool bUseFeaturesAndRecipes; TArray<FGDKIntelligentDeliveryChunk> IntelligentDeliveryChunks; TArray<FGDKIntelligentDeliveryFeature> IntelligentDeliveryFeatures; TArray<FGDKIntelligentDeliveryRecipe> IntelligentDeliveryRecipes; TArray<FGDKDLCPackage> DLCPackages; bool bAutoCreateDLCPackages; TArray<FGDKDLCChunk> DLCChunks; TArray<FGDKDLCPlugins> DLCPlugins | `Source/Developer/Microsoft/GDKPlatformEditor/Public/GDKTargetSettings.h:333` |
| `UGameEngine` | `/Script/Engine.GameEngine` |  | UEngine |  | `Source/Runtime/Engine/Classes/Engine/GameEngine.h:23` |
| `UGameFeatureAction_AddActorFactory` | `/Script/GameFeatures.GameFeatureAction_AddActorFactory` |  | UGameFeatureAction |  | `Plugins/Runtime/GameFeatures/Source/GameFeatures/Public/GameFeatureAction_AddActorFactory.h:18` |
| `UGameFeatureAction_AddChunkOverride` | `/Script/GameFeatures.GameFeatureAction_AddChunkOverride` |  | UGameFeatureAction |  | `Plugins/Runtime/GameFeatures/Source/GameFeatures/Public/GameFeatureAction_AddChunkOverride.h:18` |
| `UGameMapsSettings` | `/Script/EngineSettings.GameMapsSettings` |  | UObject |  | `Source/Runtime/EngineSettings/Classes/GameMapsSettings.h:100` |
| `UGameViewportClient` | `/Script/Engine.GameViewportClient` |  | UScriptViewportClient, FExec | int32 MaxSplitscreenPlayers | `Source/Runtime/Engine/Classes/Engine/GameViewportClient.h:70` |
| `UGameplayDebuggerConfig` | `/Script/GameplayDebugger.GameplayDebuggerConfig` |  | UObject |  | `Source/Runtime/GameplayDebugger/Public/GameplayDebuggerConfig.h:112` |
| `UGameplayTagsManager` | `/Script/GameplayTags.GameplayTagsManager` |  | UObject |  | `Source/Runtime/GameplayTags/Classes/GameplayTagsManager.h:335` |
| `UGarbageCollectionSettings` | `/Script/Engine.GarbageCollectionSettings` |  | UDeveloperSettings |  | `Source/Runtime/Engine/Classes/Engine/CoreSettings.h:172` |
| `UGeneralEngineSettings` | `/Script/EngineSettings.GeneralEngineSettings` |  | UObject |  | `Source/Runtime/EngineSettings/Classes/GeneralEngineSettings.h:11` |
| `UGeometryCache` | `/Script/GeometryCache.GeometryCache` |  | UObject, IInterface_AssetUserData |  | `Plugins/Runtime/GeometryCache/Source/GeometryCache/Classes/GeometryCache.h:22` |
| `UGeometryCacheStreamerSettings` | `/Script/GeometryCacheStreamer.GeometryCacheStreamerSettings` |  | UDeveloperSettings |  | `Plugins/Runtime/GeometryCache/Source/GeometryCacheStreamer/Public/GeometryCacheStreamerSettings.h:12` |
| `UGeometryCacheTrack` | `/Script/GeometryCache.GeometryCacheTrack` |  | UObject |  | `Plugins/Runtime/GeometryCache/Source/GeometryCache/Classes/GeometryCacheTrack.h:16` |
| `UGeometryCacheTrackAbcFile` | `/Script/GeometryCacheAbcFile.GeometryCacheTrackAbcFile` |  | UGeometryCacheTrack |  | `Plugins/Experimental/GeometryCacheAbcFile/Source/GeometryCacheAbcFile/Public/GeometryCacheTrackAbcFile.h:14` |
| `UGeometryCacheTrackStreamable` | `/Script/GeometryCache.GeometryCacheTrackStreamable` |  | UGeometryCacheTrack |  | `Plugins/Runtime/GeometryCache/Source/GeometryCache/Classes/GeometryCacheTrackStreamable.h:94` |
| `UGeometryCacheTrackUsd` | `/Script/GeometryCacheUSD.GeometryCacheTrackUsd` |  | UGeometryCacheTrack |  | `Plugins/Importers/USDImporter/Source/GeometryCacheUSD/Public/GeometryCacheTrackUSD.h:20` |
| `UGoogleARCoreEditorSettings` | `/Script/GoogleARCoreBase.GoogleARCoreEditorSettings` |  | UObject |  | `Plugins/Runtime/AR/Google/GoogleARCore/Source/GoogleARCoreBase/Public/GoogleARCoreTypes.h:424` |
| `UGoogleARCoreServicesEditorSettings` | `/Script/GoogleARCoreServices.GoogleARCoreServicesEditorSettings` |  | UObject |  | `Plugins/Runtime/AR/Google/GoogleARCoreServices/Source/GoogleARCoreServices/Private/GoogleARCoreServicesEditorSettings.h:9` |
| `UGooglePADRuntimeSettings` | `/Script/GooglePADEditor.GooglePADRuntimeSettings` | DefaultConfig | UObject |  | `Plugins/Runtime/GooglePAD/Source/GooglePADEditor/Public/GooglePADRuntimeSettings.h:14` |
| `UGroomPluginSettings` | `/Script/HairStrandsCore.GroomPluginSettings` |  | UObject |  | `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomPluginSettings.h:13` |
| `UHLODBuilderCustomHLODActorSettings` | `/Script/WorldPartitionHLODUtilities.HLODBuilderCustomHLODActorSettings` | PerObjectConfig | UHLODBuilderSettings |  | `Plugins/Editor/WorldPartitionHLODUtilities/Source/Public/WorldPartition/HLOD/Builders/HLODBuilderCustomHLODActor.h:9` |
| `UHLODBuilderInstancingSettings` | `/Script/WorldPartitionHLODUtilities.HLODBuilderInstancingSettings` | PerObjectConfig | UHLODBuilderSettings |  | `Plugins/Editor/WorldPartitionHLODUtilities/Source/Public/WorldPartition/HLOD/Builders/HLODBuilderInstancing.h:20` |
| `UHardwareTargetingSettings` | `/Script/HardwareTargeting.HardwareTargetingSettings` |  | UObject |  | `Source/Editor/HardwareTargeting/Public/HardwareTargetingSettings.h:45` |
| `UHarmonixPluginSettings` | `/Script/Harmonix.HarmonixPluginSettings` |  | UDeveloperSettings |  | `Plugins/Runtime/Harmonix/Source/Harmonix/Public/Harmonix/HarmonixPluginSettings.h:11` |
| `UHierarchicalLODSettings` | `/Script/UnrealEd.HierarchicalLODSettings` |  | UDeveloperSettings |  | `Source/Editor/UnrealEd/Public/HierarchicalLOD.h:27` |
| `UIKRetargetBoneDetails` | `/Script/IKRigEditor.IKRetargetBoneDetails` |  | UObject |  | `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/IKRetargetDetails.h:24` |
| `UIKRigBoneDetails` | `/Script/IKRigEditor.IKRigBoneDetails` |  | UObject |  | `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RigEditor/IKRigEditorController.h:37` |
| `UIOSRuntimeSettings` | `/Script/IOSRuntimeSettings.IOSRuntimeSettings` |  | UObject | G bool bEnableStoreKitSupport; G bool bEnableGameCenterSupport; G bool bEnableCloudKitSupport; G EIOSCloudKitSyncStrategy IOSCloudKitSyncStrategy; G bool bEnableRemoteNotificationsSupport; G bool bEnableBackgroundFetch; G bool bSupportsMetal; G bool bSupportsMetalMobileSM5; G bool bSupportsMetalMobileSM6; G bool bEnableRayTracing; G bool bSupportHighRefreshRates; G bool bStreamLandscapeMeshLODs; G EIOSVersion MinimumiOSVersion; G FIOSBuildResourceDirectory WindowsMetalToolchainOverride; G bool bGeneratedSYMFile; G bool bGeneratedSYMBundle; G bool bGenerateCrashReportSymbols; G bool bGenerateXCArchive; G bool bUsesNonExemptEncryption; G FString ITSEncryptionExportComplianceCode; G bool bEnableAdvertisingIdentifier; G FString AdditionalLinkerFlags; G FString AdditionalShippingLinkerFlags; G FString AdditionalPlistData; G TArray<FString> RequiredEntitlements; G bool bSupportsIPad; G bool bSupportsIPhone; G bool bEnableSplitView; G bool bEnableIOS16DynLinkerBugWAR; G bool bUseSceneBasedLifecycle; G EPowerUsageFrameRateLock FrameRateLock; G bool bEnableDynamicMaxFPS; G bool bUseRSync; G FString RemoteServerName; G FString RSyncUsername; G FString RemoteServerOverrideBuildPath; G FIOSBuildResourceDirectory CwRsyncInstallPath; G FIOSBuildResourceFilePath SSHPrivateKeyOverridePath; G bool bSupportSecondaryMac; G FString SecondaryRemoteServerName; G FString SecondaryRSyncUsername; G FString SecondaryRemoteServerOverrideBuildPath; G FIOSBuildResourceDirectory SecondaryCwRsyncInstallPath; G FIOSBuildResourceFilePath SecondarySSHPrivateKeyOverridePath; G bool bUserSwitching; G bool bGameSupportsMultipleActiveControllers; G bool bAllowRemoteRotation; G bool bAllowControllers; G bool bControllersBlockDeviceFeedback; G bool bDisableMotionData; G int32 ScreenEdgesDeferredGestures; G uint32 bSupportsPortraitOrientation : 1; G uint32 bSupportsUpsideDownOrientation : 1; G uint32 bSupportsLandscapeLeftOrientation : 1; G uint32 bSupportsLandscapeRightOrientation : 1; G uint32 bSupportsITunesFileSharing : 1; G uint32 bSupportsFilesApp : 1; G EIOSLandscapeOrientation PreferredLandscapeOrientation; G FString BundleDisplayName; G FString BundleName … (+19) | `Source/Runtime/IOS/IOSRuntimeSettings/Classes/IOSRuntimeSettings.h:193` |
| `UImagePlateSettings` | `/Script/ImagePlate.ImagePlateSettings` |  | UObject | G FString ProxyName | `Plugins/Experimental/ImagePlate/Source/ImagePlate/Public/ImagePlateFileSequence.h:21` |
| `UImgMediaSettings` | `/Script/ImgMediaFactory.ImgMediaSettings` |  | UObject |  | `Plugins/Media/ImgMedia/Source/ImgMediaFactory/Public/ImgMediaSettings.h:19` |
| `UInt16Property` | `/Script/CoreUObject.Int16Property` |  | UNumericProperty |  | `Source/Runtime/CoreUObject/Public/UObject/UnrealTypePrivate.h:259` |
| `UInt64Property` | `/Script/CoreUObject.Int64Property` |  | UNumericProperty |  | `Source/Runtime/CoreUObject/Public/UObject/UnrealTypePrivate.h:303` |
| `UInt8Property` | `/Script/CoreUObject.Int8Property` |  | UNumericProperty |  | `Source/Runtime/CoreUObject/Public/UObject/UnrealTypePrivate.h:237` |
| `UIntProperty` | `/Script/CoreUObject.IntProperty` |  | UNumericProperty |  | `Source/Runtime/CoreUObject/Public/UObject/UnrealTypePrivate.h:281` |
| `UInterchangeImportTestSettings` | `/Script/InterchangeTests.InterchangeImportTestSettings` |  | UObject |  | `Plugins/Tests/InterchangeTests/Source/InterchangeTests/Public/InterchangeImportTestSettings.h:11` |
| `UInterchangeProjectSettings` | `/Script/InterchangeEngine.InterchangeProjectSettings` |  | UDeveloperSettings |  | `Source/Runtime/Interchange/Engine/Public/InterchangeProjectSettings.h:167` |
| `UInterfaceProperty` | `/Script/CoreUObject.InterfaceProperty` |  | UProperty |  | `Source/Runtime/CoreUObject/Public/UObject/UnrealTypePrivate.h:718` |
| `UIpConnection` | `/Script/OnlineSubsystemUtils.IpConnection` |  | UNetConnection | float SocketErrorDisconnectDelay | `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Classes/IpConnection.h:25` |
| `UIpNetDriver` | `/Script/OnlineSubsystemUtils.IpNetDriver` |  | UNetDriver | uint32 LogPortUnreach:1; uint32 AllowPlayerPortUnreach:1; uint32 bExitOnBindFailure:1; uint32 MaxPortCountToTry; uint32 ServerDesiredSocketReceiveBufferBytes; uint32 ServerDesiredSocketSendBufferBytes; uint32 ClientDesiredSocketReceiveBufferBytes; uint32 ClientDesiredSocketSendBufferBytes; double MaxSecondsInReceive; int32 NbPacketsBetweenReceiveTimeTest; float ResolutionConnectionTimeout | `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Classes/IpNetDriver.h:64` |
| `UIrisCreationFlowLogConfig` | `/Script/IrisCore.IrisCreationFlowLogConfig` |  | UObject | TArray<FCreationFlowLogClassConfig> ClassFilters | `Source/Runtime/Net/Iris/Public/Iris/ReplicationSystem/IrisCreationFlowLogConfig.h:31` |
| `UJumpFloodComponent2D` | `/Script/WaterEditor.JumpFloodComponent2D` |  | UActorComponent |  | `Plugins/Experimental/Water/Source/Editor/Private/JumpFloodComponent2D.h:12` |
| `ULandscapeSettings` | `/Script/Landscape.LandscapeSettings` |  | UDeveloperSettings | ELandscapeDirtyingMode LandscapeDirtyingMode; ELandscapeTargetLayerBlendMethod TargetLayerDefaultBlendMethod | `Source/Runtime/Landscape/Public/LandscapeSettings.h:45` |
| `ULazyObjectProperty` | `/Script/CoreUObject.LazyObjectProperty` |  | UObjectPropertyBase |  | `Source/Runtime/CoreUObject/Public/UObject/UnrealTypePrivate.h:580` |
| `ULearningAgentsDepthMapComponent` | `/Script/LearningAgents.LearningAgentsDepthMapComponent` |  | UActorComponent | bool bDrawDepthFrustum; FDepthMapConfig DepthMapConfig; int32 DepthRaysBatchSize; TEnumAsByte<ECollisionChannel> CollisionChannel | `Plugins/Experimental/LearningAgents/Source/LearningAgents/Public/LearningAgentsDepthMapComponent.h:39` |
| `ULevelInstanceSettings` | `/Script/Engine.LevelInstanceSettings` |  | UObject |  | `Source/Runtime/Engine/Public/LevelInstance/LevelInstanceSettings.h:12` |
| `ULevelSequenceProjectSettings` | `/Script/LevelSequence.LevelSequenceProjectSettings` |  | UDeveloperSettings |  | `Source/Runtime/LevelSequence/Public/LevelSequenceProjectSettings.h:15` |
| `ULevelSnapshotsEditorSettings` | `/Script/LevelSnapshotsEditor.LevelSnapshotsEditorSettings` |  | UObject |  | `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshotsEditor/Private/LevelSnapshotsEditorSettings.h:14` |
| `ULevelSnapshotsSettings` | `/Script/LevelSnapshots.LevelSnapshotsSettings` |  | UObject | float FloatComparisonPrecision; double DoubleComparisonPrecision; FHashSettings HashSettings; FSnapshotCompressionSettings CompressionSettings | `Plugins/VirtualProduction/LevelSnapshots/Source/LevelSnapshots/Public/Settings/LevelSnapshotsSettings.h:10` |
| `ULevelStreamingPersistenceSettings` | `/Script/LevelStreamingPersistence.LevelStreamingPersistenceSettings` | DefaultConfig | UDeveloperSettings | bool bIncludePersistentLevel; TArray<FSoftClassPath> RuntimeRespawnedActorClasses; bool bPersistAllActorDestruction; TArray<FSoftClassPath> PersistedActorDestructionAllowList; bool bCanRemoveActorsBeforeBeginPlay; TSet<FSoftClassPath> PropertyOwningClassFilter; TArray<FLevelStreamingPersistentProperty> Properties | `Plugins/Runtime/LevelStreamingPersistence/Source/LevelStreamingPersistence/Public/LevelStreamingPersistenceSettings.h:39` |
| `ULidarPointCloudSettings` | `/Script/LidarPointCloudRuntime.LidarPointCloudSettings` |  | UObject |  | `Plugins/Enterprise/LidarPointCloud/Source/LidarPointCloudRuntime/Public/LidarPointCloudSettings.h:20` |
| `ULinuxTargetSettings` | `/Script/LinuxTargetPlatformSettings.LinuxTargetSettings` |  | UObject | G bool bMultiTargetFormat_DXT; G bool bMultiTargetFormat_ASTC; G bool bMultiTargetFormat_ETC2; G float TextureFormatPriority_ETC2; G float TextureFormatPriority_DXT; G float TextureFormatPriority_ASTC | `Source/Developer/Linux/LinuxTargetPlatformSettings/Classes/LinuxTargetSettings.h:19` |
| `ULiveLinkCurveRemapSettings` | `/Script/LiveLinkInterface.LiveLinkCurveRemapSettings` |  | ULiveLinkSourceSettings |  | `Source/Runtime/LiveLinkInterface/Public/LiveLinkCurveRemapSettings.h:27` |
| `ULiveLinkDebuggerSettings` | `/Script/LiveLinkCurveDebugUI.LiveLinkDebuggerSettings` |  | UObject |  | `Plugins/Animation/LiveLinkCurveDebugUI/Source/LiveLinkCurveDebugUI/Public/LiveLinkDebuggerSettings.h:14` |
| `ULiveLinkDefaultSourceSettings` | `/Script/LiveLinkInterface.LiveLinkDefaultSourceSettings` |  | UObject |  | `Source/Runtime/LiveLinkInterface/Public/LiveLinkSourceSettings.h:23` |
| `ULiveLinkDefaultSubjectSettings` | `/Script/LiveLinkInterface.LiveLinkDefaultSubjectSettings` |  | UObject |  | `Source/Runtime/LiveLinkInterface/Public/LiveLinkSubjectSettings.h:29` |
| `ULiveLinkHubSettings` | `/Script/LiveLinkHub.LiveLinkHubSettings` |  | UObject | bool bAllowModifyingSourceSettingsInPlayback | `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Settings/LiveLinkHubSettings.h:23` |
| `ULiveLinkOverNDisplaySettings` | `/Script/LiveLinkOverNDisplay.LiveLinkOverNDisplaySettings` |  | UObject |  | `Plugins/Runtime/LiveLinkOvernDisplay/Source/LiveLinkOverNDisplay/Public/LiveLinkOverNDisplaySettings.h:9` |
| `ULiveLinkTimecodeProvider` | `/Script/LiveLink.LiveLinkTimecodeProvider` |  | UTimecodeProvider |  | `Plugins/Animation/LiveLink/Source/LiveLink/Public/LiveLinkTimecodeProvider.h:34` |
| `ULocalPlayer` | `/Script/Engine.LocalPlayer` |  | UPlayer |  | `Source/Runtime/Engine/Classes/Engine/LocalPlayer.h:168` |
| `ULocalTraceFilterPresetContainer` | `/Script/TraceTools.LocalTraceFilterPresetContainer` |  | UObject | TArray<FTraceFilterData> UserPresets | `Source/Developer/TraceTools/Private/Models/TraceFilterPresets.h:41` |
| `ULocationServicesAndroidSettings` | `/Script/LocationServicesAndroidEditor.LocationServicesAndroidSettings` |  | UObject |  | `Plugins/Runtime/LocationServicesAndroidImpl/Source/LocationServicesAndroidEditor/Classes/LocationServicesAndroidSettings.h:8` |
| `ULocationServicesIOSSettings` | `/Script/LocationServicesIOSEditor.LocationServicesIOSSettings` |  | UObject |  | `Plugins/Runtime/LocationServicesIOSImpl/Source/LocationServicesIOSEditor/Classes/LocationServicesIOSSettings.h:8` |
| `UMDLImporterOptions` | `/Script/MDLImporter.MDLImporterOptions` |  | UObject |  | `Plugins/Enterprise/MDLImporter/Source/MDLImporter/Public/MDLImporterOptions.h:12` |
| `UMSGamingSettings` | `/Script/MSGamingSupportEditor.MSGamingSettings` |  | UGDKTargetSettings | bool bAutoGeneratePackage; bool bAlwaysIncludeDX11Dependency; bool bAlwaysIncludeGameInputDependency; TArray<FGDKCustomInstallAction> CustomInstallActions; FString CustomInstallStagingRoot; FString RequiredMinimumWindowsVersion; FString SuggestedMinimumWindowsVersion; FString RecommendedWindowsVersion; bool bRestartRuntimeForPIE; bool bLazyInitialize | `Plugins/Runtime/Windows/MSGamingSupport/Source/MSGamingSupportEditor/Private/MSGamingSettings.h:12` |
| `UMacTargetSettings` | `/Script/MacTargetPlatformSettings.MacTargetSettings` |  | UObject | G int32 SoundCueCookQualityIndex | `Source/Developer/Mac/MacTargetPlatformSettings/Classes/MacTargetSettings.h:49` |
| `UMapProperty` | `/Script/CoreUObject.MapProperty` |  | UProperty |  | `Source/Runtime/CoreUObject/Public/UObject/UnrealTypePrivate.h:842` |
| `UMeshApproximationSettingsObject` | `/Script/MergeActors.MeshApproximationSettingsObject` |  | UObject |  | `Source/Editor/MergeActors/Private/MeshApproximationTool/MeshApproximationTool.h:14` |
| `UMeshBudgetProjectSettings` | `/Script/Engine.MeshBudgetProjectSettings` |  | UDeveloperSettings |  | `Source/Runtime/Engine/Public/MeshBudgetProjectSettings.h:30` |
| `UMeshDrawCommandStatsSettings` | `/Script/Engine.MeshDrawCommandStatsSettings` |  | UDeveloperSettings |  | `Source/Runtime/Engine/Public/MeshDrawCommandStatsSettings.h:54` |
| `UMeshInstancingSettingsObject` | `/Script/MergeActors.MeshInstancingSettingsObject` |  | UObject |  | `Source/Editor/MergeActors/Private/MeshInstancingTool/MeshInstancingTool.h:16` |
| `UMeshMergingSettingsObject` | `/Script/MergeActors.MeshMergingSettingsObject` |  | UObject |  | `Source/Editor/MergeActors/Private/MeshMergingTool/MeshMergingTool.h:16` |
| `UMeshProxySettingsObject` | `/Script/MergeActors.MeshProxySettingsObject` |  | UObject |  | `Source/Editor/MergeActors/Private/MeshProxyTool/MeshProxyTool.h:14` |
| `UMeshSimplificationSettings` | `/Script/Engine.MeshSimplificationSettings` |  | UDeveloperSettings |  | `Source/Runtime/Engine/Classes/Engine/MeshSimplificationSettings.h:10` |
| `UMessageBusTesterSettings` | `/Script/MessageBusTester.MessageBusTesterSettings` |  | UDeveloperSettings |  | `Plugins/Experimental/MessageBusTester/Source/MessageBusTester/Public/MessageBusTesterSettings.h:15` |
| `UMixedRealityCaptureComponent` | `/Script/MixedRealityCaptureFramework.MixedRealityCaptureComponent` |  | USceneCaptureComponent2D | int32 TrackingLatency; bool bAutoLoadConfiguration; float ProjectionDepthOffset; bool bProjectionDepthTracking | `Plugins/Runtime/MixedRealityCaptureFramework/Source/MixedRealityCaptureFramework/Public/MixedRealityCaptureComponent.h:34` |
| `UModularViewportsSettings` | `/Script/ModularViewports.ModularViewportsSettings` |  | UDeveloperSettings |  | `Plugins/Runtime/ModularViewports/Source/ModularViewports/Public/ModularViewportsSettings.h:15` |
| `UMoverDeveloperSettings` | `/Script/Mover.MoverDeveloperSettings` |  | UDeveloperSettingsBackedByCVars |  | `Plugins/Experimental/Mover/Source/Mover/Public/MoverDeveloperSettings.h:12` |
| `UMoviePipelineCommandLineEncoderSettings` | `/Script/MovieRenderPipelineCore.MoviePipelineCommandLineEncoderSettings` |  | UDeveloperSettings |  | `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelineCommandLineEncoderSettings.h:7` |
| `UMoviePipelineInProcessExecutorSettings` | `/Script/MovieRenderPipelineCore.MoviePipelineInProcessExecutorSettings` |  | UDeveloperSettings |  | `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelineInProcessExecutorSettings.h:12` |
| `UMovieSceneAnimMixerSettings` | `/Script/MovieSceneAnimMixer.MovieSceneAnimMixerSettings` |  | UDeveloperSettings | FName DefaultInjectionSite; TSoftObjectPtr<UUAFSystem> DefaultUAFModule | `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/MovieSceneAnimMixerSettings.h:11` |
| `UMovieSceneSequence` | `/Script/MovieScene.MovieSceneSequence` |  | UMovieSceneSignedObject |  | `Source/Runtime/MovieScene/Public/MovieSceneSequence.h:70` |
| `UMrcCalibrationData` | `/Script/MixedRealityCaptureFramework.MrcCalibrationData` |  | USaveGame |  | `Plugins/Runtime/MixedRealityCaptureFramework/Source/MixedRealityCaptureFramework/Public/MrcCalibrationData.h:84` |
| `UMrcCalibrationSaveGame` | `/Script/MixedRealityCaptureFramework.MrcCalibrationSaveGame` |  | UMrcCalibrationData |  | `Plugins/Runtime/MixedRealityCaptureFramework/Source/MixedRealityCaptureFramework/Public/MrcCalibrationData.h:106` |
| `UMrcFrameworkSettings` | `/Script/MixedRealityCaptureFramework.MrcFrameworkSettings` |  | UObject | FSoftObjectPath DefaulVideoSource; FSoftObjectPath DefaultVideoProcessingMat; FSoftObjectPath DefaultRenderTarget; FSoftObjectPath DefaultDistortionDisplacementMap; FSoftObjectPath DefaulGarbageMatteMesh; FSoftObjectPath DefaulGarbageMatteMaterial; FSoftObjectPath DefaulGarbageMatteTarget | `Plugins/Runtime/MixedRealityCaptureFramework/Source/MixedRealityCaptureFramework/Private/MrcFrameworkSettings.h:7` |
| `UMrcGarbageMatteCaptureComponent` | `/Script/MixedRealityCaptureFramework.MrcGarbageMatteCaptureComponent` |  | USceneCaptureComponent2D | TSubclassOf<AMrcGarbageMatteActor> GarbageMatteActorClass | `Plugins/Runtime/MixedRealityCaptureFramework/Source/MixedRealityCaptureFramework/Public/MrcGarbageMatteCaptureComponent.h:17` |
| `UMultiServerNetRefHandleGenerator` | `/Script/IrisCore.MultiServerNetRefHandleGenerator` | DefaultConfig | UNetRefHandleGenerator | uint64 NumServerIdBits; uint32 ServerId; uint32 InitialSerial | `Source/Runtime/Net/Iris/Public/Iris/ReplicationSystem/NetRefHandleGenerator.h:61` |
| `UMultiServerNode` | `/Script/MultiServerReplication.MultiServerNode` |  | UObject | float RetryConnectDelay; float RetryConnectMaxDelay | `Plugins/Runtime/MultiServerReplication/Source/MultiServerReplication/Public/MultiServerNode.h:64` |
| `UMulticastDelegateProperty` | `/Script/CoreUObject.MulticastDelegateProperty` | Abstract | UProperty |  | `Source/Runtime/CoreUObject/Public/UObject/UnrealTypePrivate.h:947` |
| `UMulticastInlineDelegateProperty` | `/Script/CoreUObject.MulticastInlineDelegateProperty` |  | UMulticastDelegateProperty |  | `Source/Runtime/CoreUObject/Public/UObject/UnrealTypePrivate.h:975` |
| `UMulticastSparseDelegateProperty` | `/Script/CoreUObject.MulticastSparseDelegateProperty` |  | UMulticastDelegateProperty |  | `Source/Runtime/CoreUObject/Public/UObject/UnrealTypePrivate.h:997` |
| `UNDIMediaSettings` | `/Script/NDIMedia.NDIMediaSettings` |  | UDeveloperSettings |  | `Plugins/Media/NDIMedia/Source/NDIMedia/Public/NDIMediaSettings.h:9` |
| `UNNEDenoiserSettings` | `/Script/NNEDenoiser.NNEDenoiserSettings` |  | UDeveloperSettingsBackedByCVars | TSoftObjectPtr<UNNEDenoiserAsset> DenoiserAsset; int32 MaximumTileSizeOverride; TEnumAsByte<EDenoiserRuntimeType> RuntimeType; FString RuntimeName | `Plugins/NNE/NNEDenoiser/Source/NNEDenoiser/Public/NNEDenoiserSettings.h:23` |
| `UNNERuntimeIREESettings` | `/Script/NNERuntimeIREE.NNERuntimeIREESettings` |  | UDeveloperSettings | FNNERuntimeIREEThreadingOptions EditThreadingOptions{}; FNNERuntimeIREEThreadingOptions GameThreadingOptions{} | `Plugins/Experimental/NNERuntimeIREE/Source/NNERuntimeIREE/Private/NNERuntimeIREESettings.h:78` |
| `UNNERuntimeORTSettings` | `/Script/NNERuntimeORT.NNERuntimeORTSettings` |  | UDeveloperSettings | FThreadingOptions EditorThreadingOptions{true, 0, 0, EExecutionMode::SEQUENTIAL}; FThreadingOptions GameThreadingOptions{false, 1, 1, EExecutionMode::SEQUENTIAL} | `Plugins/NNE/NNERuntimeORT/Source/NNERuntimeORT/Private/NNERuntimeORTSettings.h:49` |
| `UNameProperty` | `/Script/CoreUObject.NameProperty` |  | UProperty |  | `Source/Runtime/CoreUObject/Public/UObject/UnrealTypePrivate.h:767` |
| `UNamedInterfaces` | `/Script/OnlineSubsystem.NamedInterfaces` |  | UObject |  | `Plugins/Online/OnlineSubsystem/Source/Public/NamedInterfaces.h:53` |
| `UNavArea` | `/Script/NavigationSystem.NavArea` |  | UNavAreaBase |  | `Source/Runtime/NavigationSystem/Public/NavAreas/NavArea.h:13` |
| `UNavAreaBase` | `/Script/Engine.NavAreaBase` |  | UObject |  | `Source/Runtime/Engine/Classes/AI/Navigation/NavAreaBase.h:12` |
| `UNavArea_Default` | `/Script/NavigationSystem.NavArea_Default` |  | UNavArea |  | `Source/Runtime/NavigationSystem/Public/NavAreas/NavArea_Default.h:14` |
| `UNavArea_LowHeight` | `/Script/NavigationSystem.NavArea_LowHeight` |  | UNavArea |  | `Source/Runtime/NavigationSystem/Public/NavAreas/NavArea_LowHeight.h:16` |
| `UNavArea_Null` | `/Script/NavigationSystem.NavArea_Null` |  | UNavArea |  | `Source/Runtime/NavigationSystem/Public/NavAreas/NavArea_Null.h:14` |
| `UNavArea_Obstacle` | `/Script/NavigationSystem.NavArea_Obstacle` |  | UNavArea |  | `Source/Runtime/NavigationSystem/Public/NavAreas/NavArea_Obstacle.h:14` |
| `UNavCollision` | `/Script/NavigationSystem.NavCollision` |  | UNavCollisionBase |  | `Source/Runtime/NavigationSystem/Public/NavCollision.h:45` |
| `UNavCollisionBase` | `/Script/Engine.NavCollisionBase` |  | UObject |  | `Source/Runtime/Engine/Classes/AI/Navigation/NavCollisionBase.h:18` |
| `UNavLinkDefinition` | `/Script/Engine.NavLinkDefinition` |  | UObject |  | `Source/Runtime/Engine/Classes/AI/Navigation/NavLinkDefinition.h:306` |
| `UNavModifierComponent` | `/Script/NavigationSystem.NavModifierComponent` |  | UNavRelevantComponent |  | `Source/Runtime/NavigationSystem/Public/NavModifierComponent.h:15` |
| `UNavMovementComponent` | `/Script/Engine.NavMovementComponent` |  | UMovementComponent, INavMovementInterface | G uint8 bUseAccelerationForPaths_DEPRECATED : 1 | `Source/Runtime/Engine/Classes/GameFramework/NavMovementComponent.h:25` |
| `UNavigationGraphNodeComponent` | `/Script/NavigationSystem.NavigationGraphNodeComponent` |  | USceneComponent |  | `Source/Runtime/NavigationSystem/Public/NavGraph/NavigationGraphNodeComponent.h:10` |
| `UNavigationSystemBase` | `/Script/Engine.NavigationSystemBase` | Abstract | UObject |  | `Source/Runtime/Engine/Classes/AI/NavigationSystemBase.h:243` |
| `UNavigationSystemConfig` | `/Script/Engine.NavigationSystemConfig` |  | UObject |  | `Source/Runtime/Engine/Classes/AI/NavigationSystemConfig.h:13` |
| `UNavigationSystemV1` | `/Script/NavigationSystem.NavigationSystemV1` |  | UNavigationSystemBase |  | `Source/Runtime/NavigationSystem/Public/NavigationSystem.h:290` |
| `UNetAnalyticsAggregatorConfig` | `/Script/NetCore.NetAnalyticsAggregatorConfig` | PerObjectConfig | UObject |  | `Source/Runtime/Net/Core/Classes/Net/Core/Analytics/NetAnalyticsAggregatorConfig.h:32` |
| `UNetBlobHandlerDefinitions` | `/Script/IrisCore.NetBlobHandlerDefinitions` |  | UObject | TArray<FNetBlobHandlerDefinition> NetBlobHandlerDefinitions | `Source/Runtime/Net/Iris/Private/Iris/ReplicationSystem/NetBlob/NetBlobHandlerDefinitions.h:28` |
| `UNetConnection` | `/Script/Engine.NetConnection` | Abstract | UPlayer |  | `Source/Runtime/Engine/Classes/Engine/NetConnection.h:283` |
| `UNetConnectionEOS` | `/Script/SocketSubsystemEOS.NetConnectionEOS` |  | UIpConnection |  | `Plugins/Online/SocketSubsystemEOS/Source/SocketSubsystemEOS/Private/NetConnectionEOS.h:10` |
| `UNetDriver` | `/Script/Engine.NetDriver` | Abstract | UObject, FExec | FString NetConnectionClassName; FString ReplicationDriverClassName; FString ReplicationBridgeClassName; FNetDriverReplicationSystemConfig ReplicationSystemConfigServer; FNetDriverReplicationSystemConfig ReplicationSystemConfigClient; int32 MaxDownloadSize; uint32 bClampListenServerTickRate:1; int32 NetServerMaxTickRate; int32 MaxNetTickRate; int32 MaxInternetClientRate; int32 MaxClientRate; float ServerTravelPause; float SpawnPrioritySeconds; float RelevantTimeout; float KeepAliveTime; float InitialConnectTimeout; float ConnectionTimeout; float GracefulCloseConnectionTimeout; float TimeoutMultiplierForUnoptimizedBuilds; int32 RecentlyDisconnectedTrackingTime; FName NetDriverName; TArray<FChannelDefinition> ChannelDefinitions; uint8 bNoTimeouts : 1; uint8 bNeverApplyNetworkEmulationSettings : 1; bool bSendImmediateAcks | `Source/Runtime/Engine/Classes/Engine/NetDriver.h:809` |
| `UNetDriverEOS` | `/Script/SocketSubsystemEOS.NetDriverEOS` |  | UIpNetDriver | bool bIsUsingP2PSockets | `Plugins/Online/SocketSubsystemEOS/Source/SocketSubsystemEOS/Public/NetDriverEOS.h:13` |
| `UNetDriverEOSBase` | `/Script/SocketSubsystemEOS.NetDriverEOSBase` |  | UNetDriverEOS |  | `Plugins/Online/SocketSubsystemEOS/Source/SocketSubsystemEOS/Public/NetDriverEOSBase.h:11` |
| `UNetFaultConfig` | `/Script/Engine.NetFaultConfig` | PerObjectConfig | UEscalationManagerConfig |  | `Source/Runtime/Engine/Public/Net/NetConnectionFaultRecovery.h:19` |
| `UNetObjectCountLimiterConfig` | `/Script/IrisCore.NetObjectCountLimiterConfig` |  | UNetObjectPrioritizerConfig | uint32 MaxObjectCount; float Priority; float OwningConnectionPriority; bool bEnableOwnedObjectsFastLane | `Source/Runtime/Net/Iris/Public/Iris/ReplicationSystem/Prioritization/NetObjectCountLimiter.h:27` |
| `UNetObjectFilterConfig` | `/Script/IrisCore.NetObjectFilterConfig` |  | UObject |  | `Source/Runtime/Net/Iris/Public/Iris/ReplicationSystem/Filtering/NetObjectFilter.h:129` |
| `UNetObjectFilterDefinitions` | `/Script/IrisCore.NetObjectFilterDefinitions` |  | UObject | TArray<FNetObjectFilterDefinition> NetObjectFilterDefinitions | `Source/Runtime/Net/Iris/Public/Iris/ReplicationSystem/Filtering/NetObjectFilterDefinitions.h:35` |
| `UNetObjectGridFilterConfig` | `/Script/IrisCore.NetObjectGridFilterConfig` |  | UNetObjectFilterConfig | uint32 ViewPosRelevancyFrameCount; uint16 DefaultFrameCountBeforeCulling; float CellSizeX; float CellSizeY; float DefaultCullDistance; bool bUseExactCullDistance; TArray<FNetObjectGridFilterProfile> FilterProfiles | `Source/Runtime/Net/Iris/Public/Iris/ReplicationSystem/Filtering/NetObjectGridFilter.h:49` |
| `UNetObjectParentRelevancyGridFilterConfig` | `/Script/IrisCore.NetObjectParentRelevancyGridFilterConfig` |  | UNetObjectGridFilterConfig | uint32 MaxParentChainDepth | `Source/Runtime/Net/Iris/Public/Iris/ReplicationSystem/Filtering/NetObjectParentRelevancyGridFilter.h:18` |
| `UNetObjectPrioritizerDefinitions` | `/Script/IrisCore.NetObjectPrioritizerDefinitions` |  | UObject | TArray<FNetObjectPrioritizerDefinition> NetObjectPrioritizerDefinitions | `Source/Runtime/Net/Iris/Private/Iris/ReplicationSystem/Prioritization/NetObjectPrioritizerDefinitions.h:42` |
| `UNetTokenTypeIdConfig` | `/Script/IrisCore.NetTokenTypeIdConfig` |  | UObject | TArray<FNetTokenStoreTypeIdPair> ReservedTypeIds | `Source/Runtime/Net/Iris/Public/Iris/ReplicationSystem/NetTokenStore.h:74` |
| `UNetworkMetricsBaseListener` | `/Script/Engine.NetworkMetricsBaseListener` |  | UObject | double IntervalSeconds | `Source/Runtime/Engine/Public/Net/NetworkMetricsDatabase.h:160` |
| `UNetworkMetricsConfig` | `/Script/Engine.NetworkMetricsConfig` |  | UObject | TArray<FNetworkMetricConfig> Listeners | `Source/Runtime/Engine/Public/Net/NetworkMetricsConfig.h:42` |
| `UNetworkSettings` | `/Script/Engine.NetworkSettings` |  | UDeveloperSettings |  | `Source/Runtime/Engine/Classes/Engine/NetworkSettings.h:27` |
| `UNumericProperty` | `/Script/CoreUObject.NumericProperty` | Abstract | UProperty |  | `Source/Runtime/CoreUObject/Public/UObject/UnrealTypePrivate.h:184` |
| `UOXRVisionOSRuntimeSettings` | `/Script/OXRVisionOSSettings.OXRVisionOSRuntimeSettings` |  | UDeveloperSettings |  | `Platforms/VisionOS/Plugins/Runtime/OpenXRVisionOS/Source/OXRVisionOSSettings/Public/OXRVisionOSRuntimeSettings.h:11` |
| `UObject` | `/Script/CoreUObject.Object` | Abstract | UObjectBaseUtility |  | `Source/Runtime/CoreUObject/Public/UObject/Object.h:97` |
| `UObjectProperty` | `/Script/CoreUObject.ObjectProperty` |  | UObjectPropertyBase |  | `Source/Runtime/CoreUObject/Public/UObject/UnrealTypePrivate.h:536` |
| `UObjectPropertyBase` | `/Script/CoreUObject.ObjectPropertyBase` | Abstract | UProperty |  | `Source/Runtime/CoreUObject/Public/UObject/UnrealTypePrivate.h:498` |
| `UObjectReplicationBridgeConfig` | `/Script/IrisCore.ObjectReplicationBridgeConfig` |  | UObject | TArray<FObjectReplicationBridgePollConfig> PollConfigs; TArray<FObjectReplicationBridgeFilterConfig> FilterConfigs; TArray<FObjectReplicationBridgePrioritizerConfig> PrioritizerConfigs; TArray<FObjectReplicationBridgeDeltaCompressionConfig> DeltaCompressionConfigs; TArray<FObjectReplicatedBridgeCriticalClassConfig> CriticalClassConfigs; bool bAllClassesCritical; TArray<FObjectReplicationBridgeTypeStatsConfig> TypeStatsConfigs; FName DefaultSpatialFilterName; TArray<FObjectReplicationBridgeAsyncLoadingClassConfig> AsyncLoadingClassConfigs; FName RequiredNetDriverChannelClassName; TArray<FName> CriticalActorClasses; TSubclassOf<UNetRefHandleGenerator> NetRefHandleGeneratorClass | `Source/Runtime/Net/Iris/Public/Iris/ReplicationSystem/ObjectReplicationBridgeConfig.h:141` |
| `UOcclusionPluginSourceSettingsBase` | `/Script/AudioExtensions.OcclusionPluginSourceSettingsBase` |  | UObject |  | `Source/Runtime/AudioExtensions/Public/IAudioExtensionPlugin.h:473` |
| `UOnlineBeaconUnitTestNetConnection` | `/Script/OnlineSubsystemUtils.OnlineBeaconUnitTestNetConnection` |  | UIpConnection |  | `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Private/Tests/OnlineBeaconUnitTestNetConnection.h:9` |
| `UOnlineEngineInterface` | `/Script/Engine.OnlineEngineInterface` |  | UObject |  | `Source/Runtime/Engine/Public/Net/OnlineEngineInterface.h:40` |
| `UOnlineEngineInterfaceImpl` | `/Script/OnlineSubsystemUtils.OnlineEngineInterfaceImpl` |  | UOnlineEngineInterface |  | `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Private/OnlineEngineInterfaceImpl.h:17` |
| `UOnlineHotfixManager` | `/Script/Hotfix.OnlineHotfixManager` |  | UObject | FString OSSName; FString HotfixManagerClassName; FString DebugPrefix; TArray<FSoftClassPath> HotfixableAssetClasses | `Plugins/Online/OnlineFramework/Source/Hotfix/Public/OnlineHotfixManager.h:92` |
| `UOnlineServicesEngineInterfaceImpl` | `/Script/OnlineSubsystemUtils.OnlineServicesEngineInterfaceImpl` |  | UOnlineEngineInterface |  | `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Private/OnlineServicesEngineInterfaceImpl.h:20` |
| `UOpenColorIOSettings` | `/Script/OpenColorIO.OpenColorIOSettings` |  | UDeveloperSettings |  | `Plugins/Compositing/OpenColorIO/Source/OpenColorIO/Public/OpenColorIOSettings.h:17` |
| `UOpenXRHMDSettings` | `/Script/OpenXRHMD.OpenXRHMDSettings` |  | UDeveloperSettingsBackedByCVars |  | `Plugins/Runtime/OpenXR/Source/OpenXRHMD/Public/OpenXRHMDSettings.h:12` |
| `UPCGEngineSettings` | `/Script/PCG.PCGEngineSettings` |  | UDeveloperSettingsBackedByCVars | FVector VolumeScale; bool bGenerateOnDrop; bool bDisplayCullingStateWhenDebugging; bool bGlobalDisableRefresh; bool bLandscapeDisableRefreshTracking; bool bLandscapeDisableRefreshTrackingInLandscapeEditingMode; int32 LandscapeRefreshTimeDelayMS | `Plugins/PCG/Source/PCG/Public/PCGEngineSettings.h:12` |
| `UPSOPrecacheSettingsManager` | `/Script/Engine.PSOPrecacheSettingsManager` |  | UObject |  | `Source/Runtime/Engine/Public/PSOPrecacheSettings.h:145` |
| `UPackage` | `/Script/CoreUObject.Package` |  | UObject |  | `Source/Runtime/CoreUObject/Public/UObject/Package.h:215` |
| `UPackageMap` | `/Script/CoreUObject.PackageMap` | Abstract | UObject |  | `Source/Runtime/CoreUObject/Public/UObject/CoreNet.h:189` |
| `UPacketHandlerProfileConfig` | `/Script/PacketHandler.PacketHandlerProfileConfig` | PerObjectConfig | UObject |  | `Source/Runtime/PacketHandlers/PacketHandler/Classes/PacketHandlerProfileConfig.h:13` |
| `UPaperRuntimeSettings` | `/Script/Paper2D.PaperRuntimeSettings` |  | UObject |  | `Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperRuntimeSettings.h:10` |
| `UPartyBeaconState` | `/Script/OnlineSubsystemUtils.PartyBeaconState` |  | UObject | bool bRestrictCrossConsole; TArray<FString> PlatformCrossplayRestrictions; TArray<FPartyBeaconCrossplayPlatformMapping> PlatformTypeMapping | `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Public/PartyBeaconState.h:239` |
| `UPathFollowingComponent` | `/Script/AIModule.PathFollowingComponent` |  | UActorComponent, IAIResourceInterface, IPathFollowingAgentInterface |  | `Source/Runtime/AIModule/Classes/Navigation/PathFollowingComponent.h:215` |
| `UPhysicsSettings` | `/Script/Engine.PhysicsSettings` |  | UPhysicsSettingsCore | FPhysicsPredictionSettings PhysicsPrediction | `Source/Runtime/Engine/Classes/PhysicsEngine/PhysicsSettings.h:260` |
| `UPhysicsSettingsCore` | `/Script/PhysicsCore.PhysicsSettingsCore` |  | UDeveloperSettings |  | `Source/Runtime/PhysicsCore/Public/PhysicsSettingsCore.h:18` |
| `UPlayFabPartyNetConnection` | `/Script/PlayFabParty.PlayFabPartyNetConnection` |  | UIpConnection |  | `Plugins/Online/Microsoft/PlayFabParty/Source/Private/PlayFabPartyNetConnection.h:11` |
| `UPlayFabPartyNetDriver` | `/Script/PlayFabParty.PlayFabPartyNetDriver` |  | UIpNetDriver |  | `Plugins/Online/Microsoft/PlayFabParty/Source/Private/PlayFabPartyNetDriver.h:13` |
| `UPlayer` | `/Script/Engine.Player` |  | UObject, FExec |  | `Source/Runtime/Engine/Classes/Engine/Player.h:16` |
| `UPlayerStateCountLimiterConfig` | `/Script/Engine.PlayerStateCountLimiterConfig` |  | UNetObjectCountLimiterConfig |  | `Source/Runtime/Engine/Public/GameFramework/PlayerStateCountLimiterConfig.h:17` |
| `UPoseSearchSettings` | `/Script/PoseSearch.PoseSearchSettings` |  | UDeveloperSettings |  | `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchSettings.h:9` |
| `UPoseableMeshComponent` | `/Script/Engine.PoseableMeshComponent` |  | USkinnedMeshComponent |  | `Source/Runtime/Engine/Classes/Components/PoseableMeshComponent.h:16` |
| `UProductionSettings` | `/Script/CineAssemblyToolsEditor.ProductionSettings` |  | UDeveloperSettings |  | `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Public/ProductionSettings.h:202` |
| `UProperty` | `/Script/CoreUObject.Property` | Abstract | UField |  | `Source/Runtime/CoreUObject/Public/UObject/UnrealTypePrivate.h:16` |
| `UPropertyAnimatorCoreSettings` | `/Script/PropertyAnimatorCore.PropertyAnimatorCoreSettings` |  | UDeveloperSettings | FName DefaultTimeSourceName | `Plugins/VirtualProduction/PropertyAnimatorCore/Source/PropertyAnimatorCore/Private/Settings/PropertyAnimatorCoreSettings.h:9` |
| `UPropertyAnimatorSettings` | `/Script/PropertyAnimator.PropertyAnimatorSettings` |  | UDeveloperSettings | TSet<FPropertyAnimatorCounterFormat> CounterFormatPresets | `Plugins/VirtualProduction/PropertyAnimator/Source/PropertyAnimator/Private/Settings/PropertyAnimatorSettings.h:10` |
| `UPropertyBindingSettings` | `/Script/PropertyBindingUtils.PropertyBindingSettings` |  | UDeveloperSettings |  | `Plugins/Runtime/PropertyBindingUtils/Source/PropertyBindingUtils/Private/PropertyBindingSettings.h:8` |
| `UProxyLODMeshSimplificationSettings` | `/Script/Engine.ProxyLODMeshSimplificationSettings` |  | UDeveloperSettings |  | `Source/Runtime/Engine/Classes/Engine/ProxyLODMeshSimplificationSettings.h:13` |
| `UPythonScriptPluginSettings` | `/Script/PythonScriptPlugin.PythonScriptPluginSettings` |  | UDeveloperSettings |  | `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PythonScriptPluginSettings.h:48` |
| `UQosEvaluator` | `/Script/Qos.QosEvaluator` |  | UObject |  | `Plugins/Online/OnlineFramework/Source/Qos/Private/QosEvaluator.h:51` |
| `UQosRegionManager` | `/Script/Qos.QosRegionManager` |  | UObject | int32 NumTestsPerRegion; float PingTimeout; bool bEnableSubspaceBiasOrder; FString SubspaceDelimiter; FQosSubspaceComparisonParams SubspaceBiasParams; TArray<FQosRegionInfo> RegionDefinitions; TArray<FQosDatacenterInfo> DatacenterDefinitions | `Plugins/Online/OnlineFramework/Source/Qos/Public/QosRegionManager.h:454` |
| `UQuicMessagingSettings` | `/Script/QuicMessaging.QuicMessagingSettings` |  | UObject |  | `Plugins/Experimental/QuicMessaging/Source/QuicMessaging/Public/Shared/QuicMessagingSettings.h:39` |
| `URPCDoSDetectionConfig` | `/Script/NetCore.RPCDoSDetectionConfig` | PerObjectConfig | UObject |  | `Source/Runtime/Net/Core/Private/Net/Core/Connection/RPCDoSDetectionConfig.h:37` |
| `URejoinCheck` | `/Script/Rejoin.RejoinCheck` |  | UObject | bool bShouldRecheckIfRejoinCheckUnsuccessful | `Plugins/Online/OnlineFramework/Source/Rejoin/Public/RejoinCheck.h:76` |
| `URemoteControlProtocolDMXSettings` | `/Script/RemoteControlProtocolDMX.RemoteControlProtocolDMXSettings` | DefaultConfig | UObject |  | `Plugins/VirtualProduction/RemoteControlProtocolDMX/Source/RemoteControlProtocolDMX/Public/RemoteControlProtocolDMXSettings.h:14` |
| `URemoteControlProtocolMIDISettings` | `/Script/RemoteControlProtocolMIDI.RemoteControlProtocolMIDISettings` | DefaultConfig | UObject | FRemoteControlMIDIDevice DefaultDevice | `Plugins/VirtualProduction/RemoteControlProtocolMIDI/Source/RemoteControlProtocolMIDI/Public/RemoteControlProtocolMIDISettings.h:15` |
| `URemoteControlProtocolOSCSettings` | `/Script/RemoteControlProtocolOSC.RemoteControlProtocolOSCSettings` | DefaultConfig | UObject | TArray<FRemoteControlOSCServerSettings> ServersSettings | `Plugins/VirtualProduction/RemoteControlProtocolOSC/Source/RemoteControlProtocolOSC/Private/RemoteControlProtocolOSCSettings.h:41` |
| `URemoteSessionSettings` | `/Script/RemoteSession.RemoteSessionSettings` |  | UObject |  | `Plugins/Experimental/RemoteSession/Source/RemoteSession/Public/RemoteSessionTypes.h:62` |
| `URenderDocPluginSettings` | `/Script/RenderDocPlugin.RenderDocPluginSettings` |  | UDeveloperSettings |  | `Plugins/Developer/RenderDocPlugin/Source/RenderDocPlugin/Public/RenderDocPluginSettings.h:10` |
| `URendererOverrideSettings` | `/Script/Engine.RendererOverrideSettings` |  | UDeveloperSettings |  | `Source/Runtime/Engine/Classes/Engine/RendererSettings.h:1635` |
| `URendererSettings` | `/Script/Engine.RendererSettings` |  | UDeveloperSettings |  | `Source/Runtime/Engine/Classes/Engine/RendererSettings.h:333` |
| `UReplayNetConnection` | `/Script/Engine.ReplayNetConnection` |  | UNetConnection |  | `Source/Runtime/Engine/Public/ReplayNetConnection.h:11` |
| `UReplicationDriver` | `/Script/Engine.ReplicationDriver` |  | UObject |  | `Source/Runtime/Engine/Classes/Engine/ReplicationDriver.h:47` |
| `UReplicationFilteringConfig` | `/Script/IrisCore.ReplicationFilteringConfig` |  | UObject | bool bEnableObjectScopeHysteresis; uint8 DefaultHysteresisFrameCount; uint8 HysteresisUpdateConnectionThrottling; TArray<FObjectScopeHysteresisProfile> HysteresisProfiles | `Source/Runtime/Net/Iris/Public/Iris/ReplicationSystem/Filtering/ReplicationFilteringConfig.h:46` |
| `UReplicationGraph` | `/Script/ReplicationGraph.ReplicationGraph` |  | UReplicationDriver | TSubclassOf<UNetReplicationGraphConnection> ReplicationConnectionManagerClass | `Plugins/Runtime/ReplicationGraph/Source/Public/ReplicationGraph.h:919` |
| `UReplicationGraphNode` | `/Script/ReplicationGraph.ReplicationGraphNode` |  | UObject |  | `Plugins/Runtime/ReplicationGraph/Source/Public/ReplicationGraph.h:68` |
| `UReplicationStateDescriptorConfig` | `/Script/IrisCore.ReplicationStateDescriptorConfig` |  | UObject | TArray<FSupportsStructNetSerializerConfig> SupportsStructNetSerializerList; TArray<FReplicationStateDescriptorClassPushModelConfig> EnsureFullyPushModelClassNames; bool bEnsureAllClassesAreFullyPushModel | `Source/Runtime/Net/Iris/Public/Iris/ReplicationState/ReplicationStateDescriptorConfig.h:33` |
| `UResonanceAudioSettings` | `/Script/ResonanceAudio.ResonanceAudioSettings` |  | UObject | G FSoftObjectPath OutputSubmix; G ERaQualityMode QualityMode; G FSoftObjectPath GlobalReverbPreset; G FSoftObjectPath GlobalSourcePreset | `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioSettings.h:12` |
| `UReverbPluginSourceSettingsBase` | `/Script/AudioExtensions.ReverbPluginSourceSettingsBase` |  | UObject |  | `Source/Runtime/AudioExtensions/Public/IAudioExtensionPlugin.h:582` |
| `URivermaxSettings` | `/Script/RivermaxCore.RivermaxSettings` |  | UDeveloperSettings |  | `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxCore/Public/RivermaxSettings.h:21` |
| `USVGImporterSettings` | `/Script/SVGImporter.SVGImporterSettings` |  | UDeveloperSettings | ESVGSplineConversionQuality SplineConversionQuality | `Plugins/VirtualProduction/SVGImporter/Source/SVGImporter/Private/SVGImporterSettings.h:9` |
| `USandboxedEditingSettings` | `/Script/SandboxedEditing.SandboxedEditingSettings` |  | UObject |  | `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/SandboxedEditingSettings.h:33` |
| `UScaleBox` | `/Script/UMG.ScaleBox` |  | UContentWidget |  | `Source/Runtime/UMG/Public/Components/ScaleBox.h:20` |
| `UScreenShotComparisonSettings` | `/Script/ScreenShotComparisonTools.ScreenShotComparisonSettings` |  | UObject | bool bUseConfidentialPlatformPathsForSavedResults; TArray<FScreenshotFallbackEntry> ScreenshotFallbackPlatforms | `Source/Developer/ScreenShotComparisonTools/Public/ScreenShotComparisonSettings.h:38` |
| `UScriptStruct` | `/Script/CoreUObject.ScriptStruct` |  | UStruct |  | `Source/Runtime/CoreUObject/Public/UObject/Class.h:1773` |
| `USecuritySandboxSettings` | `/Script/SecuritySandbox.SecuritySandboxSettings` |  | UDeveloperSettings |  | `Plugins/Experimental/SecuritySandbox/Source/SecuritySandbox/Public/SecuritySandboxSettings.h:10` |
| `USequentialPartialNetBlobHandlerConfig` | `/Script/IrisCore.SequentialPartialNetBlobHandlerConfig` |  | UObject | uint32 MaxPartBitCount; uint32 MaxPartCount | `Source/Runtime/Net/Iris/Public/Iris/ReplicationSystem/NetBlob/SequentialPartialNetBlobHandler.h:22` |
| `USetProperty` | `/Script/CoreUObject.SetProperty` |  | UProperty |  | `Source/Runtime/CoreUObject/Public/UObject/UnrealTypePrivate.h:867` |
| `UShaderPlatformConfigSettings` | `/Script/ShaderPlatformConfigEditor.ShaderPlatformConfigSettings` | DefaultConfig PerObjectConfig | UObject |  | `Source/Developer/ShaderPlatformConfigEditor/Private/ShaderPlatformConfigSettings.h:20` |
| `UShaderPlatformQualitySettings` | `/Script/MaterialShaderQualitySettings.ShaderPlatformQualitySettings` |  | UObject | FMaterialQualityOverrides QualityOverrides[EMaterialQualityLevel::Num] | `Source/Runtime/MaterialShaderQualitySettings/Classes/ShaderPlatformQualitySettings.h:77` |
| `UShallowWaterSettings` | `/Script/WaterAdvanced.ShallowWaterSettings` |  | UDeveloperSettings | TSoftObjectPtr<UNiagaraSystem> DefaultShallowWaterNiagaraSimulation; TSoftObjectPtr<UNiagaraDataChannelAsset> DefaultShallowWaterCollisionNDC; TSoftObjectPtr<UNiagaraSystem> DefaultOceanPatchNiagaraSystem; FShallowWaterSimParameters ShallowWaterSimParameters; TSoftObjectPtr<UMaterialParameterCollection> WaterMPC; FName GridCenterMPCName; FName WorldGridSizeMPCName; FName ResolutionMaxAxisMPCName; FName NormalRTMaterialName; FName VelocityRTMaterialName; FName NormalRTNiagaraName; FName VelocityRTNiagaraName; bool UseDefaultShallowWaterSubsystem; bool OutputVelocity; int32 MaxActivePawnNum; int32 MaxImpulseForceNum; TSoftObjectPtr<UShallowWaterPhysicsAssetOverridesDataAsset> PhysicsAssetProxiesDataAsset; bool bVisualizeActivePawn | `Plugins/Experimental/WaterAdvanced/Source/WaterAdvanced/Public/ShallowWaterSettings.h:16` |
| `USharedTraceFilterPresetContainer` | `/Script/TraceTools.SharedTraceFilterPresetContainer` | DefaultConfig | UObject | TArray<FTraceFilterData> SharedPresets | `Source/Developer/TraceTools/Private/Models/TraceFilterPresets.h:58` |
| `USignificanceManager` | `/Script/SignificanceManager.SignificanceManager` |  | UObject |  | `Plugins/Runtime/SignificanceManager/Source/SignificanceManager/Public/SignificanceManager.h:29` |
| `USimulatedClientNetConnection` | `/Script/Engine.SimulatedClientNetConnection` |  | UNetConnection |  | `Source/Runtime/Engine/Classes/Engine/NetConnection.h:2126` |
| `USkeletalMeshComponent` | `/Script/Engine.SkeletalMeshComponent` |  | USkinnedMeshComponent, IInterface_CollisionDataProvider |  | `Source/Runtime/Engine/Classes/Components/SkeletalMeshComponent.h:340` |
| `USkeletalMeshLODSettings` | `/Script/Engine.SkeletalMeshLODSettings` |  | UDataAsset |  | `Source/Runtime/Engine/Classes/Engine/SkeletalMeshLODSettings.h:122` |
| `USkeletalMeshSimplificationSettings` | `/Script/Engine.SkeletalMeshSimplificationSettings` |  | UDeveloperSettings |  | `Source/Runtime/Engine/Classes/Engine/SkeletalMeshSimplificationSettings.h:13` |
| `USkinnedAsset` | `/Script/Engine.SkinnedAsset` |  | UStreamableRenderAsset, IInterface_AsyncCompilation |  | `Source/Runtime/Engine/Classes/Engine/SkinnedAsset.h:45` |
| `USkinnedMeshComponent` | `/Script/Engine.SkinnedMeshComponent` |  | UMeshComponent, ILODSyncInterface, IClothSimulationDataProvider | EVisibilityBasedAnimTickOption VisibilityBasedAnimTickOption | `Source/Runtime/Engine/Classes/Components/SkinnedMeshComponent.h:266` |
| `USlateSettings` | `/Script/Slate.SlateSettings` |  | UObject |  | `Source/Runtime/Slate/Public/SlateSettings.h:15` |
| `USoftClassProperty` | `/Script/CoreUObject.SoftClassProperty` |  | USoftObjectProperty |  | `Source/Runtime/CoreUObject/Public/UObject/UnrealTypePrivate.h:671` |
| `USoftObjectProperty` | `/Script/CoreUObject.SoftObjectProperty` |  | UObjectPropertyBase |  | `Source/Runtime/CoreUObject/Public/UObject/UnrealTypePrivate.h:602` |
| `USoundBase` | `/Script/Engine.SoundBase` |  | UObject, IAudioPropertiesSheetAssetUserInterface, IInterface_AssetUserData |  | `Source/Runtime/Engine/Classes/Sound/SoundBase.h:107` |
| `USoundClass` | `/Script/Engine.SoundClass` |  | UObject, IInterface_AssetUserData |  | `Source/Runtime/Engine/Classes/Sound/SoundClass.h:207` |
| `USoundControlBusMix` | `/Script/AudioModulation.SoundControlBusMix` |  | UObject | uint32 ProfileIndex; double Duration; bool bRetriggerOnActivation | `Plugins/Runtime/AudioModulation/Source/AudioModulation/Public/SoundControlBusMix.h:36` |
| `USoundEffectPreset` | `/Script/Engine.SoundEffectPreset` |  | UObject |  | `Source/Runtime/Engine/Classes/Sound/SoundEffectPreset.h:22` |
| `USoundEffectSourcePreset` | `/Script/Engine.SoundEffectSourcePreset` |  | USoundEffectPreset |  | `Source/Runtime/Engine/Classes/Sound/SoundEffectSource.h:18` |
| `USoundEffectSubmixPreset` | `/Script/Engine.SoundEffectSubmixPreset` |  | USoundEffectPreset |  | `Source/Runtime/Engine/Classes/Sound/SoundEffectSubmix.h:24` |
| `USoundGroups` | `/Script/Engine.SoundGroups` |  | UObject |  | `Source/Runtime/Engine/Classes/Sound/SoundGroups.h:74` |
| `USoundModulationPatch` | `/Script/AudioModulation.SoundModulationPatch` |  | USoundModulatorBase |  | `Plugins/Runtime/AudioModulation/Source/AudioModulation/Public/SoundModulationPatch.h:71` |
| `USoundModulatorBase` | `/Script/AudioExtensions.SoundModulatorBase` |  | UObject, IAudioProxyDataFactory |  | `Source/Runtime/AudioExtensions/Public/IAudioModulation.h:239` |
| `USoundSubmix` | `/Script/Engine.SoundSubmix` |  | USoundSubmixWithParentBase |  | `Source/Runtime/Engine/Classes/Sound/SoundSubmix.h:338` |
| `USoundSubmixBase` | `/Script/Engine.SoundSubmixBase` |  | UObject |  | `Source/Runtime/Engine/Classes/Sound/SoundSubmix.h:172` |
| `USoundSubmixWithParentBase` | `/Script/Engine.SoundSubmixWithParentBase` |  | USoundSubmixBase |  | `Source/Runtime/Engine/Classes/Sound/SoundSubmix.h:277` |
| `USoundfieldEffectBase` | `/Script/AudioExtensions.SoundfieldEffectBase` |  | UObject |  | `Source/Runtime/AudioExtensions/Public/ISoundfieldFormat.h:380` |
| `USoundfieldEffectSettingsBase` | `/Script/AudioExtensions.SoundfieldEffectSettingsBase` |  | UObject |  | `Source/Runtime/AudioExtensions/Public/ISoundfieldFormat.h:348` |
| `USoundfieldEncodingSettingsBase` | `/Script/AudioExtensions.SoundfieldEncodingSettingsBase` |  | UObject |  | `Source/Runtime/AudioExtensions/Public/ISoundfieldFormat.h:122` |
| `USoundfieldEndpointSettingsBase` | `/Script/AudioExtensions.SoundfieldEndpointSettingsBase` |  | UObject |  | `Source/Runtime/AudioExtensions/Public/ISoundfieldEndpoint.h:50` |
| `USoundfieldEndpointSubmix` | `/Script/Engine.SoundfieldEndpointSubmix` |  | USoundSubmixBase |  | `Source/Runtime/Engine/Classes/Sound/SoundSubmix.h:603` |
| `USoundfieldSubmix` | `/Script/Engine.SoundfieldSubmix` |  | USoundSubmixWithParentBase |  | `Source/Runtime/Engine/Classes/Sound/SoundSubmix.h:525` |
| `USourceDataOverridePluginSourceSettingsBase` | `/Script/AudioExtensions.SourceDataOverridePluginSourceSettingsBase` |  | UObject |  | `Source/Runtime/AudioExtensions/Public/IAudioExtensionPlugin.h:392` |
| `USparseVolumeTextureMaterialInstanceFactoryNew` | `/Script/UnrealEd.SparseVolumeTextureMaterialInstanceFactoryNew` |  | UMaterialInstanceConstantFactoryNew |  | `Source/Editor/UnrealEd/Classes/Factories/SparseVolumeTextureMaterialFactory.h:30` |
| `USpatializationPluginSourceSettingsBase` | `/Script/AudioExtensions.SpatializationPluginSourceSettingsBase` |  | UObject |  | `Source/Runtime/AudioExtensions/Public/IAudioExtensionPlugin.h:183` |
| `USpectatorBeaconState` | `/Script/OnlineSubsystemUtils.SpectatorBeaconState` |  | UObject | bool bRestrictCrossConsole | `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Public/SpectatorBeaconState.h:189` |
| `USphereNetObjectPrioritizerConfig` | `/Script/IrisCore.SphereNetObjectPrioritizerConfig` |  | UNetObjectPrioritizerConfig | float InnerRadius; float OuterRadius; float InnerPriority; float OuterPriority; float OutsidePriority | `Source/Runtime/Net/Iris/Public/Iris/ReplicationSystem/Prioritization/SphereNetObjectPrioritizer.h:13` |
| `USphereWithOwnerBoostNetObjectPrioritizerConfig` | `/Script/IrisCore.SphereWithOwnerBoostNetObjectPrioritizerConfig` |  | USphereNetObjectPrioritizerConfig | float OwnerPriorityBoost | `Source/Runtime/Net/Iris/Public/Iris/ReplicationSystem/Prioritization/SphereWithOwnerBoostNetObjectPrioritizer.h:9` |
| `UStageAppSettings` | `/Script/EpicStageApp.StageAppSettings` |  | UDeveloperSettings |  | `Plugins/VirtualProduction/EpicStageApp/Source/EpicStageApp/Public/StageAppSettings.h:12` |
| `UStatePerObjectConfig` | `/Script/NetCore.StatePerObjectConfig` | PerObjectConfig | UObject |  | `Source/Runtime/Net/Core/Public/Net/Core/Connection/StateStruct.h:201` |
| `UStaticMesh` | `/Script/Engine.StaticMesh` |  | UStreamableRenderAsset, IInterface_CollisionDataProvider, IInterface_AssetUserData, IInterface_AsyncCompilation |  | `Source/Runtime/Engine/Classes/Engine/StaticMesh.h:601` |
| `USteamNetConnection` | `/Script/SocketSubsystemSteamIP.SteamNetConnection` |  | UIpConnection |  | `Plugins/Online/SocketSubsystemSteamIP/Source/SocketSubsystemSteamIP/Public/SteamNetConnection.h:14` |
| `USteamNetDriver` | `/Script/SocketSubsystemSteamIP.SteamNetDriver` |  | UIpNetDriver |  | `Plugins/Online/SocketSubsystemSteamIP/Source/SocketSubsystemSteamIP/Public/SteamNetDriver.h:17` |
| `USteamSocketsNetConnection` | `/Script/SteamSockets.SteamSocketsNetConnection` |  | UNetConnection |  | `Plugins/Runtime/Steam/SteamSockets/Source/SteamSockets/Public/SteamSocketsNetConnection.h:16` |
| `USteamSocketsNetDriver` | `/Script/SteamSockets.SteamSocketsNetDriver` |  | UNetDriver |  | `Plugins/Runtime/Steam/SteamSockets/Source/SteamSockets/Public/SteamSocketsNetDriver.h:16` |
| `UStrProperty` | `/Script/CoreUObject.StrProperty` |  | UProperty |  | `Source/Runtime/CoreUObject/Public/UObject/UnrealTypePrivate.h:789` |
| `UStreamingSettings` | `/Script/Engine.StreamingSettings` |  | UDeveloperSettings |  | `Source/Runtime/Engine/Classes/Engine/CoreSettings.h:16` |
| `UStretcherAndPitchShifterConfig` | `/Script/HarmonixDsp.StretcherAndPitchShifterConfig` | Abstract | UObject |  | `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/StretcherAndPitchShifterConfig.h:10` |
| `UStretcherAndPitchShifterFactoryConfig` | `/Script/HarmonixDsp.StretcherAndPitchShifterFactoryConfig` |  | UHarmonixDeveloperSettings |  | `Plugins/Runtime/Harmonix/Source/HarmonixDsp/Public/HarmonixDsp/StretcherAndPitchShifterFactoryConfig.h:31` |
| `UStruct` | `/Script/CoreUObject.Struct` |  | UField #if CPP , private FStructBaseChain #endif |  | `Source/Runtime/CoreUObject/Public/UObject/Class.h:494` |
| `UStructProperty` | `/Script/CoreUObject.StructProperty` |  | UProperty |  | `Source/Runtime/CoreUObject/Public/UObject/UnrealTypePrivate.h:890` |
| `UStructViewerProjectSettings` | `/Script/StructViewer.StructViewerProjectSettings` |  | UObject |  | `Source/Editor/StructViewer/Public/StructViewerProjectSettings.h:22` |
| `USurfaceEffectsSettings` | `/Script/SurfaceEffects.SurfaceEffectsSettings` |  | UDeveloperSettings |  | `Plugins/Experimental/SurfaceEffects/Source/SurfaceEffects/Public/SurfaceEffectsSettings.h:8` |
| `USwitchboardEditorSettings` | `/Script/SwitchboardEditor.SwitchboardEditorSettings` |  | UObject | FDirectoryPath VirtualEnvironmentPath; FString ListenerCommandlineArguments | `Plugins/VirtualProduction/Switchboard/Source/SwitchboardEditor/Public/SwitchboardEditorSettings.h:14` |
| `USystemTimeTimecodeProvider` | `/Script/Engine.SystemTimeTimecodeProvider` |  | UTimecodeProvider |  | `Source/Runtime/Engine/Classes/Engine/SystemTimeTimecodeProvider.h:11` |
| `UTaskSyncManagerSettings` | `/Script/Engine.TaskSyncManagerSettings` |  | UDeveloperSettings |  | `Source/Runtime/Engine/Public/TaskSyncManager.h:109` |
| `UTcpMessagingSettings` | `/Script/TcpMessaging.TcpMessagingSettings` |  | UObject |  | `Plugins/Messaging/TcpMessaging/Source/TcpMessaging/Private/Settings/TcpMessagingSettings.h:8` |
| `UTextProperty` | `/Script/CoreUObject.TextProperty` |  | UProperty |  | `Source/Runtime/CoreUObject/Public/UObject/UnrealTypePrivate.h:1044` |
| `UTextureEncodingProjectSettings` | `/Script/Engine.TextureEncodingProjectSettings` |  | UDeveloperSettings |  | `Source/Runtime/Engine/Private/TextureEncodingSettingsPrivate.h:12` |
| `UTextureShareSettings` | `/Script/TextureShare.TextureShareSettings` |  | UObject |  | `Plugins/VirtualProduction/TextureShare/Source/TextureShare/Private/Game/Settings/TextureShareSettings.h:31` |
| `UTimecodeSynchronizerProjectSettings` | `/Script/TimecodeSynchronizer.TimecodeSynchronizerProjectSettings` |  | UObject | bool bDisplayInToolbar | `Plugins/Media/TimecodeSynchronizer/Source/TimecodeSynchronizer/Public/TimecodeSynchronizerProjectSettings.h:17` |
| `UTraceSourceFilteringProjectSettings` | `/Script/SourceFilteringTrace.TraceSourceFilteringProjectSettings` |  | UDeveloperSettings |  | `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringTrace/Public/TraceSourceFilteringProjectSettings.h:13` |
| `UTransformProviderData` | `/Script/Engine.TransformProviderData` | Abstract | UObject |  | `Source/Runtime/Engine/Public/Animation/TransformProviderData.h:28` |
| `UTwitterIntegrationBase` | `/Script/Engine.TwitterIntegrationBase` |  | UPlatformInterfaceBase |  | `Source/Runtime/Engine/Classes/Engine/TwitterIntegrationBase.h:36` |
| `UUInt16Property` | `/Script/CoreUObject.UInt16Property` |  | UNumericProperty |  | `Source/Runtime/CoreUObject/Public/UObject/UnrealTypePrivate.h:325` |
| `UUInt32Property` | `/Script/CoreUObject.UInt32Property` |  | UNumericProperty |  | `Source/Runtime/CoreUObject/Public/UObject/UnrealTypePrivate.h:347` |
| `UUInt64Property` | `/Script/CoreUObject.UInt64Property` |  | UNumericProperty |  | `Source/Runtime/CoreUObject/Public/UObject/UnrealTypePrivate.h:364` |
| `UUdpMessagingSettings` | `/Script/UdpMessaging.UdpMessagingSettings` |  | UObject |  | `Plugins/Messaging/UdpMessaging/Source/UdpMessaging/Public/Shared/UdpMessagingSettings.h:34` |
| `UUnrealEdEngine` | `/Script/UnrealEd.UnrealEdEngine` |  | UEditorEngine, FNotifyHook |  | `Source/Editor/UnrealEd/Classes/Editor/UnrealEdEngine.h:86` |
| `UUpdateManager` | `/Script/Hotfix.UpdateManager` |  | UObject | float UpdateCheckStartDelay; float UpdateCheckCachedResponseDelay; float HotfixCheckCompleteDelay; float UpdateCheckCompleteDelay; float HotfixAvailabilityCheckCompleteDelay; float UpdateCheckAvailabilityCompleteDelay; int32 AppSuspendedUpdateCheckTimeSeconds; FUpdateContextDefinition UpdateContextDefinitionUnknown; TArray<FUpdateContextDefinition> UpdateContextDefinitions | `Plugins/Online/OnlineFramework/Source/Hotfix/Public/UpdateManager.h:174` |
| `UUserGeneratedContentLocalizationSettings` | `/Script/Localization.UserGeneratedContentLocalizationSettings` |  | UObject |  | `Source/Developer/Localization/Public/UserGeneratedContentLocalization.h:28` |
| `UUserInterfaceSettings` | `/Script/Engine.UserInterfaceSettings` |  | UDeveloperSettings |  | `Source/Runtime/Engine/Classes/Engine/UserInterfaceSettings.h:116` |
| `UVerseClass` | `/Script/CoreUObject.VerseClass` |  | UClass |  | `Source/Runtime/CoreUObject/Public/VerseVM/VVMVerseClass.h:134` |
| `UViewModeUtils` | `/Script/Engine.ViewModeUtils` |  | UObject |  | `Source/Runtime/Engine/Classes/Engine/EngineBaseTypes.h:1122` |
| `UVirtualTexturePoolConfig` | `/Script/Engine.VirtualTexturePoolConfig` |  | UDeveloperSettings |  | `Source/Runtime/Engine/Classes/VT/VirtualTexturePoolConfig.h:57` |
| `UVirtualizationFilterSettings` | `/Script/Virtualization.VirtualizationFilterSettings` |  | UObject | TArray<FString> ExcludePackagePaths; TArray<FString> IncludePackagePaths | `Source/Developer/Virtualization/Private/VirtualizationFilterSettings.h:12` |
| `UVisionOSRuntimeSettings` | `/Script/VisionOSRuntimeSettings.VisionOSRuntimeSettings` |  | UObject |  | `Platforms/VisionOS/Source/Runtime/VisionOSRuntimeSettings/Classes/VisionOSRuntimeSettings.h:16` |
| `UWaterBodyBrushCacheContainer` | `/Script/WaterEditor.WaterBodyBrushCacheContainer` |  | UObject |  | `Plugins/Experimental/Water/Source/Editor/Private/WaterBrushCacheContainer.h:23` |
| `UWaterEditorSettings` | `/Script/WaterEditor.WaterEditorSettings` |  | UDeveloperSettings |  | `Plugins/Experimental/Water/Source/Editor/Public/WaterEditorSettings.h:188` |
| `UWaterRuntimeSettings` | `/Script/Water.WaterRuntimeSettings` |  | UDeveloperSettings | TSubclassOf<UWaterBodyRiverComponent> WaterBodyRiverComponentClass_DEPRECATED; TSubclassOf<UWaterBodyLakeComponent> WaterBodyLakeComponentClass_DEPRECATED; TSubclassOf<UWaterBodyOceanComponent> WaterBodyOceanComponentClass_DEPRECATED; TSubclassOf<UWaterBodyCustomComponent> WaterBodyCustomComponentClass_DEPRECATED | `Plugins/Experimental/Water/Source/Runtime/Public/WaterRuntimeSettings.h:24` |
| `UWaveTableBank` | `/Script/WaveTable.WaveTableBank` |  | UObject, IAudioProxyDataFactory |  | `Plugins/Runtime/WaveTable/Source/WaveTable/Public/WaveTableBank.h:29` |
| `UWeakObjectProperty` | `/Script/CoreUObject.WeakObjectProperty` |  | UObjectPropertyBase |  | `Source/Runtime/CoreUObject/Public/UObject/UnrealTypePrivate.h:558` |
| `UWebAPIAuthenticationSettings` | `/Script/WebAPI.WebAPIAuthenticationSettings` | Abstract | UDeveloperSettings |  | `Plugins/Experimental/Web/WebAPI/Source/WebAPI/Public/Security/WebAPIAuthentication.h:19` |
| `UWebAPIDeveloperSettings` | `/Script/WebAPI.WebAPIDeveloperSettings` | DefaultConfig Abstract | UDeveloperSettings , FWebAPIHttpResponseHandlerInterface | FString Host; FString BaseUrl; FString UserAgent; FString DateTimeFormat; bool bOverrideScheme; FString URISchemeOverride; bool bLogRequests | `Plugins/Experimental/Web/WebAPI/Source/WebAPI/Public/WebAPIDeveloperSettings.h:18` |
| `UWebAPIEditorSettings` | `/Script/WebAPIEditor.WebAPIEditorSettings` | DefaultConfig | UDeveloperSettings |  | `Plugins/Experimental/Web/WebAPI/Source/WebAPIEditor/Public/WebAPIEditorSettings.h:12` |
| `UWebAPILiquidJSSettings` | `/Script/WebAPILiquidJS.WebAPILiquidJSSettings` | DefaultConfig | UDeveloperSettings | uint32 Port; bool bForceWebAppBuildAtStartup; FString ServiceUrl | `Plugins/Experimental/Web/WebAPI/Source/WebAPILiquidJS/Private/WebAPILiquidJSSettings.h:9` |
| `UWebAPIOAuthSettings` | `/Script/WebAPI.WebAPIOAuthSettings` | PerObjectConfig | UWebAPIAuthenticationSettings | FString ClientId; FString ClientSecret; FString TokenType; FString AccessToken; FDateTime ExpiresOn; FString AuthenticationServer; TMap<FString, FString> AdditionalRequestQueryParameters; TMap<FString, FString> AdditionalRequestBodyParameters | `Plugins/Experimental/Web/WebAPI/Source/WebAPI/Public/Security/WebAPIAuthentication.h:33` |
| `UWebSocketConnection` | `/Script/WebSocketNetworking.WebSocketConnection` |  | UNetConnection |  | `Plugins/Experimental/WebSocketNetworking/Source/WebSocketNetworking/Public/WebSocketConnection.h:11` |
| `UWebSocketMessagingSettings` | `/Script/WebSocketMessaging.WebSocketMessagingSettings` |  | UObject | EWebSocketMessagingTransportFormat ServerTransportFormat; bool bMessageSerializationStandardizeCase; EWebSocketMessagingTransportFormat DiscoveryPayloadFormat | `Plugins/Experimental/WebSocketMessaging/Source/WebSocketMessaging/Private/WebSocketMessagingSettings.h:18` |
| `UWebSocketNetDriver` | `/Script/WebSocketNetworking.WebSocketNetDriver` |  | UNetDriver | int32 WebSocketPort | `Plugins/Experimental/WebSocketNetworking/Source/WebSocketNetworking/Public/WebSocketNetDriver.h:17` |
| `UWindowsTargetSettings` | `/Script/WindowsTargetPlatformSettings.WindowsTargetSettings` |  | UObject | G FPlatformRuntimeAudioCompressionOverrides CompressionOverrides; G int32 CacheSizeKB; G int32 MaxChunkSizeOverrideKB; G bool bResampleForDevice; G float MaxSampleRate; G float HighSampleRate; G float MedSampleRate; G float LowSampleRate; G float MinSampleRate; G float CompressionQualityModifier; G float AutoStreamingThreshold; G int32 SoundCueCookQualityIndex | `Source/Developer/Windows/WindowsTargetPlatformSettings/Classes/WindowsTargetSettings.h:44` |
| `UWmfMediaSettings` | `/Script/WmfMediaFactory.WmfMediaSettings` |  | UObject |  | `Plugins/Media/WmfMedia/Source/WmfMediaFactory/Public/WmfMediaSettings.h:14` |
| `UWorld` | `/Script/Engine.World` |  | UObject, FNetworkNotify |  | `Source/Runtime/Engine/Classes/Engine/World.h:930` |
| `UWorldComposition` | `/Script/Engine.WorldComposition` |  | UObject |  | `Source/Runtime/Engine/Classes/Engine/WorldComposition.h:71` |
| `UWorldLocationsConfig` | `/Script/IrisCore.WorldLocationsConfig` |  | UObject | FVector MinPos; FVector MaxPos; float MaxNetCullDistance | `Source/Runtime/Net/Iris/Public/Iris/ReplicationSystem/WorldLocations.h:28` |
| `UWorldMetricsSubsystem` | `/Script/WorldMetricsCore.WorldMetricsSubsystem` | DefaultConfig | UWorldSubsystem | float UpdateRateInSeconds; int32 WarmUpFrames | `Plugins/WorldMetrics/Source/WorldMetricsCore/Public/WorldMetricsSubsystem.h:28` |
| `UWorldPartitionBuilder` | `/Script/UnrealEd.WorldPartitionBuilder` | Abstract | UObject |  | `Source/Editor/UnrealEd/Public/WorldPartition/WorldPartitionBuilder.h:37` |
| `UWorldPartitionBuilderCommandlet` | `/Script/UnrealEd.WorldPartitionBuilderCommandlet` |  | UCommandlet |  | `Source/Editor/UnrealEd/Classes/Commandlets/WorldPartitionBuilderCommandlet.h:13` |
| `UWorldPartitionConvertCommandlet` | `/Script/UnrealEd.WorldPartitionConvertCommandlet` |  | UCommandlet | TSubclassOf<UWorldPartitionEditorHash> EditorHashClass; TSubclassOf<UWorldPartitionRuntimeHash> RuntimeHashClass; TArray<FString> ExcludedLevels; bool bConvertActorsNotReferencedByLevelScript; FVector WorldOrigin; FVector WorldExtent; FTopLevelAssetPath DefaultHLODLayerAsset; FString FoliageTypePath; TArray<FHLODLayerActorMapping> HLODLayersForActorClasses; uint32 LandscapeGridSize; FString DataLayerAssetFolder | `Source/Editor/UnrealEd/Classes/Commandlets/WorldPartitionConvertCommandlet.h:34` |
| `UWorldPartitionEditorHash` | `/Script/Engine.WorldPartitionEditorHash` | Abstract | UObject |  | `Source/Runtime/Engine/Public/WorldPartition/WorldPartitionEditorHash.h:11` |
| `UWorldPartitionMiniMapBuilder` | `/Script/UnrealEd.WorldPartitionMiniMapBuilder` |  | UWorldPartitionBuilder |  | `Source/Editor/UnrealEd/Public/WorldPartition/WorldPartitionMiniMapBuilder.h:13` |
| `UWorldPartitionRuntimeCellTransformerSettings` | `/Script/Engine.WorldPartitionRuntimeCellTransformerSettings` |  | UObject | TArray<TSubclassOf<UActorComponent>> IgnoredComponentClasses; TArray<TSubclassOf<UActorComponent>> IgnoredExactComponentClasses | `Source/Runtime/Engine/Public/WorldPartition/WorldPartitionRuntimeCellTransformer.h:12` |
| `UWorldPartitionRuntimeHash` | `/Script/Engine.WorldPartitionRuntimeHash` | Abstract | UObject |  | `Source/Runtime/Engine/Public/WorldPartition/WorldPartitionRuntimeHash.h:208` |
| `UWorldPartitionSettings` | `/Script/Engine.WorldPartitionSettings` |  | UDeveloperSettings | EWorldPartitionDataLayersLogicOperator NewMapsDataLayersLogicOperator; bool bNewMapsEnableWorldPartition; bool bNewMapsEnableWorldPartitionStreaming; TSubclassOf<UWorldPartitionEditorHash> EditorHashDefaultClass; TSubclassOf<UWorldPartitionRuntimeHash> RuntimeHashDefaultClass; TMap<EHLODLayerType, FHLODLayerTypeUnsupportedActorClasses> UnsupportedActorClassesPerHLODLayerType; bool bShouldEDLPackagesInheritWorldChunkAssignmentsDuringCook; TSet<TSoftObjectPtr<UExternalDataLayerAsset>> EDLCookFilters | `Source/Runtime/Engine/Public/WorldPartition/WorldPartitionSettings.h:22` |
| `UXRScribeDeveloperSettings` | `/Script/XRScribe.XRScribeDeveloperSettings` |  | UDeveloperSettings |  | `Plugins/Runtime/XR/XRScribe/Source/XRScribe/Public/XRScribeDeveloperSettings.h:27` |
| `UXcodeProjectSettings` | `/Script/MacTargetPlatformSettings.XcodeProjectSettings` |  | UObject |  | `Source/Developer/Mac/MacTargetPlatformSettings/Classes/XcodeProjectSettings.h:16` |

## config=EditorPerProjectUserSettings (270)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UAIAssistantContextUser` | `/Script/AIAssistant.AIAssistantContextUser` |  | UDeveloperSettings | FString Prompt | `Plugins/Experimental/AIAssistant/Source/AIAssistant/Private/AIAssistantToolset.h:14` |
| `UActorPaletteSettings` | `/Script/ActorPalette.ActorPaletteSettings` |  | UDeveloperSettings |  | `Plugins/Experimental/ActorPalette/Source/ActorPalette/Private/ActorPaletteSettings.h:28` |
| `UAnimBlueprintSettings` | `/Script/UnrealEd.AnimBlueprintSettings` |  | UObject | bool bSupportInputEventsForBackwardsCompatibility | `Source/Editor/UnrealEd/Classes/Settings/AnimBlueprintSettings.h:12` |
| `UAnimDetailsSettings` | `/Script/ControlRigEditor.AnimDetailsSettings` |  | UObject |  | `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/AnimDetails/AnimDetailsSettings.h:8` |
| `UAnimGraphAttributes` | `/Script/AnimGraph.AnimGraphAttributes` |  | UObject |  | `Source/Editor/AnimGraph/Public/AnimGraphAttributes.h:94` |
| `UAnimNextVariableSettings` | `/Script/UAFEditor.AnimNextVariableSettings` |  | UDeveloperSettings | uint32 VariablesViewPinSelectorType | `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Variables/AnimNextVariableSettings.h:10` |
| `UAnimationAuthoringSettings` | `/Script/ControlRigEditor.AnimationAuthoringSettings` |  | UDeveloperSettings |  | `Plugins/Animation/ControlRig/Source/ControlRigEditor/Public/Sequencer/AnimationAuthoringSettings.h:12` |
| `UAnimationBlueprintEditorOptions` | `/Script/UnrealEd.AnimationBlueprintEditorOptions` |  | UObject |  | `Source/Editor/UnrealEd/Classes/Preferences/AnimationBlueprintEditorOptions.h:15` |
| `UAnimationBlueprintEditorSettings` | `/Script/AnimationBlueprintEditor.AnimationBlueprintEditorSettings` |  | UObject |  | `Source/Editor/AnimationBlueprintEditor/Public/AnimationBlueprintEditorSettings.h:18` |
| `UAnimationRecordingParameters` | `/Script/SequenceRecorder.AnimationRecordingParameters` |  | UObject |  | `Source/Editor/SequenceRecorder/Private/AnimationRecorderParameters.h:14` |
| `UAnimatorKitSettings` | `/Script/AnimatorKitSettings.AnimatorKitSettings` |  | UDeveloperSettings |  | `Plugins/Animation/AnimatorKit/Source/AnimatorKitSettings/Public/AnimatorKitSettings.h:12` |
| `UAudioEditorPerProjectUserSettings` | `/Script/AudioEditor.AudioEditorPerProjectUserSettings` |  | UDeveloperSettings |  | `Source/Editor/AudioEditor/Classes/AudioEditorPerProjectUserSettings.h:17` |
| `UAudioInsightsEditorSettings` | `/Script/AudioInsightsEditor.AudioInsightsEditorSettings` |  | UDeveloperSettings | bool bWorldFilterDefaultsToFirstClient; bool bOnlyTraceAudioChannels | `Plugins/AudioInsights/Source/AudioInsightsEditor/Public/AudioInsightsEditorSettings.h:17` |
| `UAutomatedLevelSequenceCapture` | `/Script/MovieSceneTools.AutomatedLevelSequenceCapture` | PerObjectConfig | UMovieSceneCapture |  | `Source/Editor/MovieSceneTools/Public/AutomatedLevelSequenceCapture.h:20` |
| `UAvaComponentVisualizersSettings` | `/Script/AvalancheComponentVisualizers.AvaComponentVisualizersSettings` |  | UDeveloperSettings, IAvaComponentVisualizersSettings | float SpriteSize; TMap<FName, TSoftObjectPtr<UTexture2D>> VisualizerSprites | `Plugins/VirtualProduction/Avalanche/Source/AvalancheComponentVisualizers/Private/AvaComponentVisualizersSettings.h:9` |
| `UAvaEditorSettings` | `/Script/AvalancheEditor.AvaEditorSettings` |  | UDeveloperSettings | bool bEnableLevelContextSwitching; bool bAutoIncludeAttachedActorsInEditActions; bool bKeepRelativeTransformWhenGrouping; float CameraDistance; bool bAutoActivateMotionDesignViewport; FAvaViewportQualitySettings DefaultViewportQualitySettings; TArray<FAvaViewportQualitySettingsPreset> ViewportQualitySettingsPresets | `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/AvaEditorSettings.h:18` |
| `UAvaInteractiveToolsSettings` | `/Script/AvalancheInteractiveTools.AvaInteractiveToolsSettings` |  | UDeveloperSettings | float CameraDistance; EAvaInteractiveToolsDefaultActionAlignment DefaultActionActorAlignment; EAvaInteractiveToolsViewportToolbarPosition ViewportToolbarPosition; bool bViewportToolbarLabelEnabled | `Plugins/VirtualProduction/Avalanche/Source/AvalancheInteractiveTools/Public/AvaInteractiveToolsSettings.h:30` |
| `UAvaMRQEditorSettings` | `/Script/AvalancheMRQEditor.AvaMRQEditorSettings` |  | UDeveloperSettings | TSoftObjectPtr<UMoviePipelinePrimaryConfig> PresetConfig | `Plugins/VirtualProduction/Avalanche/Source/AvalancheMRQEditor/Private/AvaMRQEditorSettings.h:11` |
| `UAvaMediaEditorSettings` | `/Script/AvalancheMediaEditor.AvaMediaEditorSettings` |  | UDeveloperSettings | bool bBroadcastEnforceMaxChannelCount; int32 BroadcastMaxChannelCount; bool bBroadcastShowAllMediaOutputClasses; FLinearColor PlaybackDefaultNodeColor; FLinearColor PlaybackChannelsNodeColor; FLinearColor PlaybackPlayerNodeColor; FLinearColor PlaybackEventNodeColor; FLinearColor PlaybackActionNodeColor | `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/AvaMediaEditorSettings.h:8` |
| `UAvaOutlinerSettings` | `/Script/AvalancheOutliner.AvaOutlinerSettings` |  | UDeveloperSettings | TMap<FName, FLinearColor> ItemColorMap; TMap<FName, FAvaOutlinerItemTypeFilterData> CustomItemTypeFilters; bool bAlwaysShowVisibilityState; bool bAlwaysShowLockState; bool bUseMutedHierarchy; bool bAutoExpandToSelection; int32 ItemDefaultViewMode; int32 ItemProxyViewMode | `Plugins/VirtualProduction/Avalanche/Source/AvalancheOutliner/Private/AvaOutlinerSettings.h:9` |
| `UAvaRundownEditorSettings` | `/Script/AvalancheMediaEditor.AvaRundownEditorSettings` |  | UDeveloperSettings | bool bShouldStopPagesOnClose; bool bPreviewCheckerBoard; bool bAutoStartPreviewBroadcastChannel; bool bPageDetailsShowProperties; TSoftObjectPtr<UAvaRundownMacroCollection> MacroCollection; EAvaRundownPageSet PreviewContinueActionPageSet; EAvaRundownPageSet PreviewOutActionPageSet; EAvaRundownPageSet ContinueActionPageSet; EAvaRundownPageSet TakeOutActionPageSet; EAvaRundownPageSet UpdateValuesActionPageSet; bool bAutoStartRundownServer; FString RundownServerName | `Plugins/VirtualProduction/Avalanche/Source/AvalancheMediaEditor/Private/Rundown/AvaRundownEditorSettings.h:11` |
| `UAvaSequencerSettings` | `/Script/AvalancheSequencer.AvaSequencerSettings` |  | UDeveloperSettings | FAvaSequencerDisplayRate DisplayRate; double StartTime; double EndTime; TSet<FAvaSequencePreset> CustomSequencePresets; TSet<FAvaSequencePresetGroup> CustomPresetGroups; FSidebarState SidebarState_DEPRECATED | `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequencer/Public/Settings/AvaSequencerSettings.h:14` |
| `UAvaTransitionEditorSettings` | `/Script/AvalancheTransitionEditor.AvaTransitionEditorSettings` |  | UDeveloperSettings | TSoftObjectPtr<UAvaTransitionTree> DefaultTemplate; bool bCreateTransitionLogicDefaultScene | `Plugins/VirtualProduction/Avalanche/Source/AvalancheTransitionEditor/Public/Settings/AvaTransitionEditorSettings.h:14` |
| `UAvaViewportSettings` | `/Script/AvalancheViewport.AvaViewportSettings` |  | UDeveloperSettings | bool bEnableViewportOverlay; bool bEnableBoundingBoxes; TSoftObjectPtr<UMaterial> ViewportBackgroundMaterial; TSoftObjectPtr<UMaterial> ViewportCheckerboardMaterial; FLinearColor ViewportCheckerboardColor0; FLinearColor ViewportCheckerboardColor1; float ViewportCheckerboardSize; bool bEnableShapesEditorOverlay; EAvaShapeEditorOverlayType ShapeEditorOverlayType; FAvaShapeEditorViewportControlPosition ShapeEditorViewportControlPosition; bool bGridEnabled; bool bGridAlwaysVisible; int32 GridSize; FLinearColor GridColor; float GridThickness; bool bPixelGridEnabled; FLinearColor PixelGridColor; int32 SnapState; bool bSnapIndicatorsEnabled; FLinearColor SnapIndicatorColor; float SnapIndicatorThickness; bool bGuidesEnabled; FString GuideConfigPath; FLinearColor EnabledGuideColor; FLinearColor EnabledLockedGuideColor; FLinearColor DisabledGuideColor; FLinearColor DisabledLockedGuideColor; FLinearColor DraggedGuideColor; FLinearColor SnappedToGuideColor; float GuideThickness; bool bSafeFramesEnabled; TArray<FAvaLevelViewportSafeFrame> SafeFrames; FLinearColor CameraBoundsShadeColor; bool bEnableTextureOverlay; TSoftObjectPtr<UTexture> TextureOverlayTexture; float TextureOverlayOpacity; bool bTextureOverlayStretch | `Plugins/VirtualProduction/Avalanche/Source/AvalancheViewport/Public/AvaViewportSettings.h:52` |
| `UBatchExportOptions` | `/Script/IKRigEditor.BatchExportOptions` |  | UObject | bool bOverwriteExistingFiles; bool bIncludeReferencedAssets; bool bRetainAdditiveFlags | `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/SRetargetAnimAssetsWindow.h:63` |
| `UBlueprintEditorSettings` | `/Script/BlueprintGraph.BlueprintEditorSettings` |  | UDeveloperSettings | bool bEnableInputTriggerSupportWarnings | `Source/Editor/BlueprintGraph/Public/BlueprintEditorSettings.h:89` |
| `UBlueprintHeaderViewSettings` | `/Script/BlueprintHeaderView.BlueprintHeaderViewSettings` |  | UDeveloperSettings |  | `Plugins/Editor/BlueprintHeaderView/Source/BlueprintHeaderView/Public/BlueprintHeaderViewSettings.h:52` |
| `UBlueprintPaletteFavorites` | `/Script/Kismet.BlueprintPaletteFavorites` |  | UObject |  | `Source/Editor/Kismet/Classes/BlueprintPaletteFavorites.h:105` |
| `UCameraCalibrationEditorSettings` | `/Script/CameraCalibrationCore.CameraCalibrationEditorSettings` |  | UDeveloperSettings |  | `Plugins/VirtualProduction/CameraCalibrationCore/Source/CameraCalibrationCore/Public/CameraCalibrationSettings.h:214` |
| `UCaptureManagerEditorSettings` | `/Script/CaptureManagerEditorSettings.CaptureManagerEditorSettings` |  | UDeveloperSettings |  | `Plugins/VirtualProduction/CaptureManager/CaptureManagerEditor/Source/CaptureManagerEditorSettings/Public/Settings/CaptureManagerEditorSettings.h:22` |
| `UCascadeOptions` | `/Script/UnrealEd.CascadeOptions` |  | UObject |  | `Source/Editor/UnrealEd/Classes/Preferences/CascadeOptions.h:17` |
| `UChaosClothEditorOptions` | `/Script/ChaosClothAssetEditor.ChaosClothEditorOptions` |  | UDeveloperSettings | bool bClothAssetsOpenInDataflowEditor; EConstructionViewportMousePanButton ConstructionViewportMousePanButton | `Plugins/ChaosClothAssetEditorCore/Source/ChaosClothAssetEditor/Private/ChaosClothAsset/ClothEditorOptions.h:23` |
| `UChooserEditorSettings` | `/Script/ChooserEditor.ChooserEditorSettings` |  | UDeveloperSettings | FString DefaultCreateType | `Plugins/Chooser/Source/ChooserEditor/Private/ChooserEditorSettings.h:11` |
| `UCineAssemblyTakeRecorderSettings` | `/Script/CineAssemblyToolsEditor.CineAssemblyTakeRecorderSettings` |  | UObject | TSoftObjectPtr<UCineAssemblySchema> AssemblySchema | `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/TakeRecorder/CineAssemblyTakeRecorderSettings.h:12` |
| `UClassViewerSettings` | `/Script/UnrealEd.ClassViewerSettings` |  | UObject |  | `Source/Editor/UnrealEd/Classes/Settings/ClassViewerSettings.h:30` |
| `UClothPainterSettings` | `/Script/ClothPainter.ClothPainterSettings` |  | UMeshPaintSettings | float ViewMin; float ViewMax; bool bFlipNormal; bool bCullBackface; float Opacity | `Source/Editor/ClothPainter/Private/ClothPaintSettings.h:26` |
| `UCompositeEditorPanelSettings` | `/Script/CompositeEditor.CompositeEditorPanelSettings` |  | UObject | bool bAutoApplyCompositeMeshMaterial; ECompositeMeshAppliedMaterialType CompositeMeshMaterialType; TArray<FName> CompositeMeshTableHiddenColumns; bool bSyncActorSelection; ECompositeMeshVisualizationMode MeshVisualizationMode | `Plugins/Compositing/Composite/Source/CompositeEditor/Private/UI/CompositeEditorPanelSettings.h:32` |
| `UCompositionGraphCaptureProtocol` | `/Script/MovieSceneCapture.CompositionGraphCaptureProtocol` |  | UMovieSceneImageCaptureProtocolBase |  | `Source/Runtime/MovieSceneCapture/Public/Protocols/CompositionGraphCaptureProtocol.h:49` |
| `UCompressedImageSequenceProtocol` | `/Script/MovieSceneCapture.CompressedImageSequenceProtocol` | Abstract | UImageSequenceProtocol |  | `Source/Runtime/MovieSceneCapture/Public/Protocols/ImageSequenceProtocol.h:62` |
| `UConcertInsightsClientSettings` | `/Script/ConcertInsightsClient.ConcertInsightsClientSettings` |  | UObject |  | `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsClient/Source/ConcertInsightsClient/Private/ConcertInsightsClientSettings.h:8` |
| `UContentBrowserFavoriteProjectSettings` | `/Script/ContentBrowser.ContentBrowserFavoriteProjectSettings` |  | UDeveloperSettings | TArray<FContentBrowserFavoriteItem> FavoriteItems | `Source/Editor/ContentBrowser/Private/ContentBrowserConfig.h:138` |
| `UControlRigEditModeSettings` | `/Script/ControlRigEditor.ControlRigEditModeSettings` |  | UDeveloperSettings |  | `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/EditMode/ControlRigEditModeSettings.h:26` |
| `UControlRigEditorSettings` | `/Script/ControlRig.ControlRigEditorSettings` |  | URigVMEditorSettings |  | `Plugins/Animation/ControlRig/Source/ControlRig/Public/Settings/ControlRigSettings.h:79` |
| `UControlRigPoseMirrorSettings` | `/Script/ControlRig.ControlRigPoseMirrorSettings` |  | UObject |  | `Plugins/Animation/ControlRig/Source/ControlRig/Public/Tools/ControlRigPoseMirrorSettings.h:14` |
| `UControlRigPoseProjectSettings` | `/Script/ControlRig.ControlRigPoseProjectSettings` |  | UObject |  | `Plugins/Animation/ControlRig/Source/ControlRig/Public/Tools/ControlRigPoseProjectSettings.h:14` |
| `UControlRigSnapSettings` | `/Script/ControlRigEditor.ControlRigSnapSettings` |  | UObject |  | `Plugins/Animation/ControlRig/Source/ControlRigEditor/Public/Tools/ControlRigSnapSettings.h:15` |
| `UCrashDiagnosticsSettings` | `/Script/CrashDiagnostics.CrashDiagnosticsSettings` |  | UObject |  | `Plugins/Experimental/EditorPerformance/Source/CrashDiagnostics/Private/CrashDiagnosticsSettings.h:9` |
| `UCrashReporterSettings` | `/Script/UnrealEd.CrashReporterSettings` |  | UObject |  | `Source/Editor/UnrealEd/Public/CrashReporterSettings.h:17` |
| `UCurveEdOptions` | `/Script/UnrealEd.CurveEdOptions` |  | UObject |  | `Source/Editor/UnrealEd/Classes/Preferences/CurveEdOptions.h:17` |
| `UCurveEditorSettings` | `/Script/CurveEditor.CurveEditorSettings` |  | UObject |  | `Source/Editor/CurveEditor/Public/CurveEditorSettings.h:106` |
| `UCustomizableObjectEditorSettings` | `/Script/CustomizableObjectEditor.CustomizableObjectEditorSettings` |  | UObject |  | `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectEditorSettings.h:13` |
| `UDMTextureSetSettings` | `/Script/DynamicMaterialTextureSetEditor.DMTextureSetSettings` |  | UDeveloperSettings |  | `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialTextureSetEditor/Private/DMTextureSetSettings.h:14` |
| `UDMXControlConsoleCompactEditorModel` | `/Script/DMXControlConsoleEditor.DMXControlConsoleCompactEditorModel` |  | UObject | TSoftObjectPtr<UDMXControlConsole> SoftControlConsole | `Plugins/VirtualProduction/DMX/DMXControlConsole/Source/DMXControlConsoleEditor/Private/Models/DMXControlConsoleCompactEditorModel.h:16` |
| `UDMXEditorSettings` | `/Script/DMXEditor.DMXEditorSettings` |  | UObject | FString LastGDTFImportPath; FString LastMVRImportPath; FString LastMVRExportPath; bool bFixturePatcherDMXMonitorEnabled_DEPRECATED; FDMXFixtureTypeFunctionsEditorSettings FixtureTypeFunctionsEditorSettings; FDMXMVRFixtureListSettings MVRFixtureListSettings; FDMXMVRFixturePatcherSettings FixturePatcherSettings; TArray<FDMXOutputConsoleFaderDescriptor> OutputConsoleFaders_DEPRECATED; FString LastOpenedControlConsolePath; int32 ChannelsMonitorUniverseID; FDMXMonitorSourceDescriptor ChannelsMonitorSource; FDMXMonitorSourceDescriptor ActivityMonitorSource; int32 ActivityMonitorMinUniverseID; int32 ActivityMonitorMaxUniverseID; FDMXConflictMonitorSettings ConflictMonitorSettings | `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Public/DMXEditorSettings.h:174` |
| `UDMXLibraryFromMVRImportOptions` | `/Script/DMXEditor.DMXLibraryFromMVRImportOptions` |  | UObject | bool bUpdateInputPort; bool bUpdateOutputPort | `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Factories/DMXLibraryFromMVRImportOptions.h:23` |
| `UDNAImportSettings` | `/Script/RigLogicEditor.DNAImportSettings` |  | UDeveloperSettings |  | `Plugins/Animation/RigLogic/Source/RigLogicEditor/Public/DNAImportSettings.h:16` |
| `UDataflowEditorOptions` | `/Script/DataflowEditor.DataflowEditorOptions` |  | UDeveloperSettings | EDataflowConstructionViewportMousePanButton ConstructionViewportMousePanButton; EDataflowEditorEvaluationMode EditorEvaluationMode | `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowEditorOptions.h:34` |
| `UDataflowEditorUserSettings` | `/Script/DataflowEditor.DataflowEditorUserSettings` |  | UObject |  | `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/DataflowEditor.h:36` |
| `UDatasmithC4DImportOptions` | `/Script/DatasmithC4DTranslator.DatasmithC4DImportOptions` |  | UDatasmithOptionsBase |  | `Plugins/Enterprise/DatasmithC4DImporter/Source/DatasmithC4DTranslator/Private/DatasmithC4DImportOptions.h:23` |
| `UDatasmithCommonTessellationOptions` | `/Script/DatasmithContent.DatasmithCommonTessellationOptions` |  | UDatasmithOptionsBase |  | `Plugins/Enterprise/DatasmithContent/Source/DatasmithContent/Public/DatasmithImportOptions.h:358` |
| `UDatasmithDeltaGenImportOptions` | `/Script/DatasmithDeltaGenTranslator.DatasmithDeltaGenImportOptions` |  | UDatasmithFBXImportOptions |  | `Plugins/Enterprise/DatasmithFBXImporter/Source/DatasmithDeltaGenTranslator/Private/DatasmithDeltaGenImportOptions.h:21` |
| `UDatasmithFBXImportOptions` | `/Script/DatasmithFBXTranslator.DatasmithFBXImportOptions` |  | UDatasmithOptionsBase |  | `Plugins/Enterprise/DatasmithFBXImporter/Source/DatasmithFBXTranslator/Public/DatasmithFBXImportOptions.h:14` |
| `UDatasmithImportOptions` | `/Script/DatasmithContent.DatasmithImportOptions` |  | UDatasmithOptionsBase |  | `Plugins/Enterprise/DatasmithContent/Source/DatasmithContent/Public/DatasmithImportOptions.h:368` |
| `UDatasmithMVRImportOptions` | `/Script/DatasmithMVRTranslator.DatasmithMVRImportOptions` |  | UDatasmithOptionsBase | bool bImportMVR | `Plugins/VirtualProduction/DMX/DatasmithMVR/Source/DatasmithMVRTranslator/Private/DatasmithMVRImportOptions.h:11` |
| `UDatasmithOpenNurbsImportOptions` | `/Script/DatasmithOpenNurbsTranslator.DatasmithOpenNurbsImportOptions` |  | UDatasmithOptionsBase |  | `Plugins/Enterprise/DatasmithCADImporter/Source/DatasmithOpenNurbsTranslator/Public/DatasmithOpenNurbsImportOptions.h:42` |
| `UDatasmithVREDImportOptions` | `/Script/DatasmithVREDTranslator.DatasmithVREDImportOptions` |  | UDatasmithFBXImportOptions |  | `Plugins/Enterprise/DatasmithFBXImporter/Source/DatasmithVREDTranslator/Private/DatasmithVREDImportOptions.h:12` |
| `UDatasmithWireOptions` | `/Script/DatasmithWireTranslator.DatasmithWireOptions` |  | UDatasmithOptionsBase |  | `Plugins/Enterprise/DatasmithCADImporter/Source/DatasmithWireTranslator/Private/DatasmithWireTranslator.h:14` |
| `UDaySequenceEditorSettings` | `/Script/DaySequenceEditor.DaySequenceEditorSettings` |  | UObject |  | `Plugins/Experimental/DaySequence/Source/DaySequenceEditor/Private/DaySequenceEditorSettings.h:55` |
| `UDirectoryPlaceholderSettings` | `/Script/DirectoryPlaceholder.DirectoryPlaceholderSettings` |  | UDeveloperSettings | bool bAutomaticallyCreatePlaceholders; bool bAutomaticallyCreatePlaceholdersInProjectContent; bool bAutomaticallyCreatePlaceholdersInProjectPlugins; bool bAutomaticallyCreatePlaceholdersInAdditionalPlugins; TArray<FString> ExcludePaths | `Plugins/Developer/DirectoryPlaceholder/Source/DirectoryPlaceholder/Private/DirectoryPlaceholderSettings.h:12` |
| `UDisplayClusterConfigurationData` | `/Script/DisplayClusterConfiguration.DisplayClusterConfigurationData` | PerObjectConfig | UDisplayClusterConfigurationData_Base |  | `Plugins/Runtime/nDisplay/Source/DisplayClusterConfiguration/Public/DisplayClusterConfigurationTypes.h:545` |
| `UDisplayClusterConfiguratorEditorSettings` | `/Script/DisplayClusterConfigurator.DisplayClusterConfiguratorEditorSettings` |  | UObject | bool bExportOnSave | `Plugins/Runtime/nDisplay/Source/DisplayClusterConfigurator/Private/Settings/DisplayClusterConfiguratorSettings.h:9` |
| `UDisplayClusterLightCardEditorSettings` | `/Script/DisplayClusterLightCardEditor.DisplayClusterLightCardEditorSettings` |  | UObject |  | `Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditor/Private/Settings/DisplayClusterLightCardEditorSettings.h:82` |
| `UDisplayClusterStageActorTemplate` | `/Script/DisplayClusterLightCardExtender.DisplayClusterStageActorTemplate` | PerObjectConfig Abstract | UObject | bool bIsFavorite | `Plugins/Runtime/nDisplayModularFeatures/Source/DisplayClusterLightCardExtender/Public/StageActor/DisplayClusterStageActorTemplate.h:9` |
| `UDrawPrimitiveDebuggerUserSettings` | `/Script/DrawPrimitiveDebugger.DrawPrimitiveDebuggerUserSettings` |  | UDeveloperSettings |  | `Source/Developer/DrawPrimitiveDebugger/Public/DrawPrimitiveDebuggerConfig.h:11` |
| `UDynamicMaterialEditorSettings` | `/Script/DynamicMaterialEditor.DynamicMaterialEditorSettings` |  | UDeveloperSettings | bool bFollowSelection; bool bAddDetailsPanelButton; bool bAutomaticallyCopyParametersToSourceMaterial; bool bAutomaticallyCompilePreviewMaterial; bool bAutomaticallyApplyToSourceOnPreviewCompile; EDMLiveEditMode LiveEditMode; EDMMaterialEditorLayout Layout; float SplitterLocation; float PreviewSplitterLocation; bool bUVVisualizerVisible; bool bUseFullChannelNamesInTopSlimLayout; float StagePreviewSize; float PropertyPreviewSize; double ThumbnailSize; EDMMaterialPreviewMesh PreviewMesh; TSoftObjectPtr<UStaticMesh> CustomPreviewMesh; FDMContentBrowserThumbnailSettings ContentBrowserThumbnail; bool bShowPreviewBackground; bool bPreviewImagesUseTextureUVs; TSoftObjectPtr<UTexture> DefaultMask; TMap<EDMMaterialPropertyType, FDMDefaultMaterialPropertySlotValue> DefaultSlotValueOverrides; TArray<FName> CustomEffectsFolders; TArray<FDMMaterialChannelListPreset> MaterialChannelPresets; bool bUseLinearColorForVectors; bool bValidatedPresets; bool bConvertedVarsToFlags | `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/DynamicMaterialEditorSettings.h:218` |
| `UEaseCurveToolSettings` | `/Script/EaseCurveTool.EaseCurveToolSettings` |  | UDeveloperSettings | bool bShowInSidebar; bool bShowCurveEditorToolbarButton; bool bToolTabVisible; TSoftObjectPtr<UEaseCurveLibrary> DefaultPresetLibrary; FText NewPresetCategory; FString QuickEaseTangents; int32 GraphSize; bool bGridSnap; int32 GridSize; bool bAutoZoomToFit; bool bAutoFlipTangents | `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/EaseCurveToolSettings.h:12` |
| `UEditorDataStorageSettings` | `/Script/TedsCore.EditorDataStorageSettings` |  | UObject |  | `Plugins/Experimental/EditorDataStorage/Source/TedsCore/Private/EditorDataStorageSettings.h:22` |
| `UEditorExperimentalSettings` | `/Script/UnrealEd.EditorExperimentalSettings` |  | UObject |  | `Source/Editor/UnrealEd/Classes/Settings/EditorExperimentalSettings.h:16` |
| `UEditorLoadingSavingSettings` | `/Script/UnrealEd.EditorLoadingSavingSettings` |  | UObject | int32 AutoSaveInteractionDelayInSeconds | `Source/Editor/UnrealEd/Classes/Settings/EditorLoadingSavingSettings.h:94` |
| `UEditorMiscSettings` | `/Script/UnrealEd.EditorMiscSettings` |  | UObject |  | `Source/Editor/UnrealEd/Classes/Settings/EditorMiscSettings.h:15` |
| `UEditorPerProjectUserSettings` | `/Script/UnrealEd.EditorPerProjectUserSettings` |  | UObject | uint32 bConfirmEditorClose: 1; EGlobalTabSwitchingBehavior TabSwitchingBehavior; bool bShowTabSwitchingDialog; int32 AssetViewerProfileIndex | `Source/Editor/UnrealEd/Classes/Editor/EditorPerProjectUserSettings.h:20` |
| `UEditorStyleSettings` | `/Script/UnrealEd.EditorStyleSettings` |  | UObject | float ApplicationScale | `Source/Editor/UnrealEd/Classes/Settings/EditorStyleSettings.h:35` |
| `UEditorUtilitySubsystem` | `/Script/Blutility.EditorUtilitySubsystem` |  | UEditorSubsystem |  | `Source/Editor/Blutility/Public/EditorUtilitySubsystem.h:46` |
| `UEnhancedInputEditorSettings` | `/Script/InputEditor.EnhancedInputEditorSettings` |  | UDeveloperSettingsBackedByCVars |  | `Plugins/EnhancedInput/Source/InputEditor/Public/EnhancedInputEditorSettings.h:38` |
| `UFNiagaraMemoryBufferSimCacheVisualizerSettings` | `/Script/NiagaraEditor.FNiagaraMemoryBufferSimCacheVisualizerSettings` |  | UObject | ENiagaraSimTarget DisplaySimTarget; ENDIMemoryBufferViewType DisplayAsType; int32 DisplayColumns | `Plugins/FX/Niagara/Source/NiagaraEditor/Private/Customizations/SimCache/NiagaraMemoryBufferSimCacheVisualizer.h:19` |
| `UFabLocalAssets` | `/Script/Fab.FabLocalAssets` |  | UObject |  | `Plugins/Fab/Source/Fab/Private/Utilities/FabLocalAssets.h:14` |
| `UFabSettings` | `/Script/Fab.FabSettings` |  | UObject |  | `Plugins/Fab/Source/Fab/Private/FabSettings.h:43` |
| `UFacialAnimationBulkImporterSettings` | `/Script/FacialAnimationEditor.FacialAnimationBulkImporterSettings` |  | UObject | FDirectoryPath SourceImportPath; FDirectoryPath TargetImportPath; FString CurveNodeName | `Plugins/Editor/FacialAnimation/Source/FacialAnimationEditor/Private/FacialAnimationBulkImporterSettings.h:7` |
| `UFbxAnimSequenceImportData` | `/Script/UnrealEd.FbxAnimSequenceImportData` |  | UFbxAssetImportData |  | `Source/Editor/UnrealEd/Classes/Factories/FbxAnimSequenceImportData.h:36` |
| `UFbxAssetImportData` | `/Script/UnrealEd.FbxAssetImportData` |  | UAssetImportData |  | `Source/Editor/UnrealEd/Classes/Factories/FbxAssetImportData.h:24` |
| `UFbxExportOption` | `/Script/UnrealEd.FbxExportOption` |  | UObject | EFbxMaterialBakeMode BakeMaterialInputs; FFbxMaterialBakeSize DefaultMaterialBakeSize | `Source/Editor/UnrealEd/Classes/Exporters/FbxExportOption.h:63` |
| `UFbxImportUI` | `/Script/UnrealEd.FbxImportUI` |  | UObject, IImportSettingsParser |  | `Source/Editor/UnrealEd/Classes/Factories/FbxImportUI.h:97` |
| `UFbxMeshImportData` | `/Script/UnrealEd.FbxMeshImportData` |  | UFbxAssetImportData |  | `Source/Editor/UnrealEd/Classes/Factories/FbxMeshImportData.h:60` |
| `UFbxSceneImportOptions` | `/Script/UnrealEd.FbxSceneImportOptions` |  | UObject |  | `Source/Editor/UnrealEd/Classes/Factories/FbxSceneImportOptions.h:22` |
| `UFbxSceneImportOptionsSkeletalMesh` | `/Script/UnrealEd.FbxSceneImportOptionsSkeletalMesh` |  | UObject |  | `Source/Editor/UnrealEd/Classes/Factories/FbxSceneImportOptionsSkeletalMesh.h:12` |
| `UFbxSceneImportOptionsStaticMesh` | `/Script/UnrealEd.FbxSceneImportOptionsStaticMesh` |  | UObject |  | `Source/Editor/UnrealEd/Classes/Factories/FbxSceneImportOptionsStaticMesh.h:44` |
| `UFbxStaticMeshImportData` | `/Script/UnrealEd.FbxStaticMeshImportData` |  | UFbxMeshImportData |  | `Source/Editor/UnrealEd/Classes/Factories/FbxStaticMeshImportData.h:16` |
| `UFlipbookEditorSettings` | `/Script/Paper2DEditor.FlipbookEditorSettings` |  | UObject |  | `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/FlipbookEditor/FlipbookEditorSettings.h:8` |
| `UFloatingPropertiesSettings` | `/Script/FloatingProperties.FloatingPropertiesSettings` |  | UDeveloperSettings | bool bEnabled; TMap<FFloatingPropertiesClassProperty, FFloatingPropertiesClassProperties> SavedValues; TMap<FFloatingPropertiesClassProperty, FFloatingPropertiesClassPropertyPosition> PropertyPositions; TMap<FFloatingPropertiesClassProperty, FFloatingPropertiesClassPropertyAnchor> PropertyAnchors | `Plugins/Experimental/FloatingProperties/Source/FloatingProperties/Public/FloatingPropertiesSettings.h:91` |
| `UFractureAutoUVSettings` | `/Script/FractureEditor.FractureAutoUVSettings` |  | UFractureToolSettings |  | `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolUV.h:56` |
| `UFractureBrickSettings` | `/Script/FractureEditor.FractureBrickSettings` |  | UFractureToolSettings |  | `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolBrick.h:40` |
| `UFractureClusterCutterSettings` | `/Script/FractureEditor.FractureClusterCutterSettings` |  | UFractureToolSettings |  | `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolClusterCutter.h:12` |
| `UFractureCollisionSettings` | `/Script/FractureEditor.FractureCollisionSettings` |  | UFractureToolSettings |  | `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolCutter.h:187` |
| `UFractureConvertSettings` | `/Script/FractureEditor.FractureConvertSettings` |  | UFractureToolSettings |  | `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolConvert.h:13` |
| `UFractureConvexActions` | `/Script/FractureEditor.FractureConvexActions` |  | UFractureToolSettings |  | `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolConvex.h:73` |
| `UFractureConvexSettings` | `/Script/FractureEditor.FractureConvexSettings` |  | UFractureToolSettings |  | `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolConvex.h:14` |
| `UFractureCustomVoronoiSettings` | `/Script/FractureEditor.FractureCustomVoronoiSettings` |  | UFractureToolSettings |  | `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolCustomVoronoi.h:38` |
| `UFractureCutterSettings` | `/Script/FractureEditor.FractureCutterSettings` |  | UFractureToolSettings |  | `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolCutter.h:22` |
| `UFractureInitialDynamicStateSettings` | `/Script/FractureEditor.FractureInitialDynamicStateSettings` |  | UFractureToolSettings |  | `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolProperties.h:20` |
| `UFractureMaterialsSettings` | `/Script/FractureEditor.FractureMaterialsSettings` |  | UFractureToolSettings |  | `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolMaterials.h:21` |
| `UFractureMeshCutSettings` | `/Script/FractureEditor.FractureMeshCutSettings` |  | UFractureToolSettings |  | `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolMeshCut.h:23` |
| `UFracturePlaneCutSettings` | `/Script/FractureEditor.FracturePlaneCutSettings` |  | UFractureToolSettings |  | `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolPlaneCut.h:15` |
| `UFractureProximityActions` | `/Script/FractureEditor.FractureProximityActions` |  | UFractureToolSettings |  | `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolProximity.h:80` |
| `UFractureProximitySettings` | `/Script/FractureEditor.FractureProximitySettings` |  | UFractureToolSettings |  | `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolProximity.h:14` |
| `UFractureRadialSettings` | `/Script/FractureEditor.FractureRadialSettings` |  | UFractureToolSettings |  | `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolRadial.h:12` |
| `UFractureRecomputeNormalsSettings` | `/Script/FractureEditor.FractureRecomputeNormalsSettings` |  | UFractureToolSettings |  | `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolRecomputeNormals.h:13` |
| `UFractureReimportSettings` | `/Script/FractureEditor.FractureReimportSettings` |  | UFractureToolSettings |  | `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolConvert.h:46` |
| `UFractureRemoveOnBreakSettings` | `/Script/FractureEditor.FractureRemoveOnBreakSettings` |  | UFractureToolSettings |  | `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolProperties.h:67` |
| `UFractureResampleSettings` | `/Script/FractureEditor.FractureResampleSettings` |  | UFractureToolSettings |  | `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolResample.h:13` |
| `UFractureSelectionSettings` | `/Script/FractureEditor.FractureSelectionSettings` |  | UFractureToolSettings |  | `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolSelection.h:47` |
| `UFractureSliceSettings` | `/Script/FractureEditor.FractureSliceSettings` |  | UFractureToolSettings |  | `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolSlice.h:13` |
| `UFractureSplitIslandsSettings` | `/Script/FractureEditor.FractureSplitIslandsSettings` |  | UFractureToolSettings |  | `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolSplitIslands.h:13` |
| `UFractureTinyGeoSettings` | `/Script/FractureEditor.FractureTinyGeoSettings` |  | UFractureToolSettings |  | `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolFixTinyGeo.h:48` |
| `UFractureToolSettings` | `/Script/FractureEditor.FractureToolSettings` | Abstract | UObject |  | `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Public/FractureTool.h:26` |
| `UFractureTransformGizmoSettings` | `/Script/FractureEditor.FractureTransformGizmoSettings` |  | UFractureToolSettings |  | `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolCutter.h:451` |
| `UFractureUniformSettings` | `/Script/FractureEditor.FractureUniformSettings` |  | UFractureToolSettings |  | `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolUniform.h:11` |
| `UFractureValidateSettings` | `/Script/FractureEditor.FractureValidateSettings` |  | UFractureToolSettings |  | `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolEditing.h:94` |
| `UFrameGrabberProtocol` | `/Script/MovieSceneCapture.FrameGrabberProtocol` | Abstract | UMovieSceneImageCaptureProtocolBase |  | `Source/Runtime/MovieSceneCapture/Public/Protocols/FrameGrabberProtocol.h:13` |
| `UFusionPatchImportOptions` | `/Script/HarmonixDspEditor.FusionPatchImportOptions` |  | UObject |  | `Plugins/Runtime/Harmonix/Source/HarmonixDspEditor/Private/FusionPatchImportOptions.h:13` |
| `UGLTFExportOptions` | `/Script/GLTFExporter.GLTFExportOptions` |  | UObject | float ExportUniformScale; bool bExportPreviewMesh; bool bSkipNearDefaultValues; bool bIncludeCopyrightNotice; bool bExportProxyMaterials; bool bUseImporterMaterialMapping; bool bExportUnlitMaterials; bool bExportClearCoatMaterials; bool bExportClothMaterials; bool bExportThinTranslucentMaterials; bool bExportSpecularGlossinessMaterials; bool bExportEmissiveStrength; EGLTFMaterialBakeMode BakeMaterialInputs; FGLTFMaterialBakeSize DefaultMaterialBakeSize; TEnumAsByte<TextureFilter> DefaultMaterialBakeFilter; TEnumAsByte<TextureAddress> DefaultMaterialBakeTiling; TMap<EGLTFMaterialPropertyGroup, FGLTFOverrideMaterialBakeSettings> DefaultInputBakeSettings; int32 DefaultLevelOfDetail; bool bExportSourceModel; bool bExportVertexColors; bool bExportVertexSkinWeights; bool bMakeSkinnedMeshesRoot; bool bUseMeshQuantization; bool bExportMorphTargets; bool bExportLevelSequences; bool bExportAnimationSequences; EGLTFTextureImageFormat TextureImageFormat; int32 TextureImageQuality; bool bExportTextureTransforms; bool bExportLightmaps; bool bAdjustNormalmaps; bool bExportHiddenInGame; bool bExportLights; bool bExportCameras; EGLTFMaterialVariantMode ExportMaterialVariants | `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Options/GLTFExportOptions.h:33` |
| `UGLTFProxyOptions` | `/Script/GLTFExporter.GLTFProxyOptions` |  | UObject | bool bBakeMaterialInputs; bool bUseThinTranslucentShadingModel; FGLTFMaterialBakeSize DefaultMaterialBakeSize; TEnumAsByte<TextureFilter> DefaultMaterialBakeFilter; TEnumAsByte<TextureAddress> DefaultMaterialBakeTiling; TMap<EGLTFMaterialPropertyGroup, FGLTFOverrideMaterialBakeSettings> DefaultInputBakeSettings | `Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Public/Options/GLTFProxyOptions.h:10` |
| `UGameplayAbilitiesEditorDeveloperSettings` | `/Script/GameplayAbilities.GameplayAbilitiesEditorDeveloperSettings` |  | UDeveloperSettingsBackedByCVars | bool bIgnoreCooldowns; bool bIgnoreCosts; float AbilitySystemGlobalScaler; float DebugDrawMaxDistance | `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayAbilitiesDeveloperSettings.h:135` |
| `UGameplayCamerasEditorSettings` | `/Script/GameplayCamerasEditor.GameplayCamerasEditorSettings` |  | UDeveloperSettings | FLinearColor CameraNodeTitleColor; FLinearColor CameraAssetTitleColor; FLinearColor CameraRigAssetTitleColor; FLinearColor CameraShakeAssetTitleColor; FLinearColor CameraRigTransitionTitleColor; FLinearColor CameraRigTransitionConditionTitleColor; FLinearColor CameraBlendNodeTitleColor; bool bEnableRunInEditor | `Plugins/Cameras/GameplayCameras/Source/GameplayCamerasEditor/Public/GameplayCamerasEditorSettings.h:14` |
| `UGameplayDebuggerUserSettings` | `/Script/GameplayDebugger.GameplayDebuggerUserSettings` |  | UDeveloperSettings |  | `Source/Runtime/GameplayDebugger/Public/GameplayDebuggerConfig.h:225` |
| `UGameplayTagsDeveloperSettings` | `/Script/GameplayTags.GameplayTagsDeveloperSettings` |  | UDeveloperSettings |  | `Source/Runtime/GameplayTags/Classes/GameplayTagsSettings.h:192` |
| `UGeometryCollectionResetSettings` | `/Script/FractureEditor.GeometryCollectionResetSettings` |  | UFractureToolSettings |  | `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Private/FractureToolGenerators.h:70` |
| `UGizmoSettings` | `/Script/GizmoSettings.GizmoSettings` |  | UDeveloperSettings |  | `Plugins/Experimental/GizmoFramework/Source/GizmoSettings/Public/GizmoSettings.h:10` |
| `UGraphEditorSettings` | `/Script/GraphEditor.GraphEditorSettings` |  | UObject |  | `Source/Editor/GraphEditor/Public/GraphEditorSettings.h:34` |
| `UGroomCreateBindingOptions` | `/Script/HairStrandsCore.GroomCreateBindingOptions` |  | UObject |  | `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomCreateBindingOptions.h:9` |
| `UGroomCreateFollicleMaskOptions` | `/Script/HairStrandsCore.GroomCreateFollicleMaskOptions` |  | UObject |  | `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomCreateFollicleMaskOptions.h:36` |
| `UGroomCreateStrandsTexturesOptions` | `/Script/HairStrandsCore.GroomCreateStrandsTexturesOptions` |  | UObject |  | `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomCreateStrandsTexturesOptions.h:29` |
| `UGroomHairGroupsMapping` | `/Script/HairStrandsCore.GroomHairGroupsMapping` |  | UObject |  | `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomImportOptions.h:72` |
| `UGroomHairGroupsPreview` | `/Script/HairStrandsCore.GroomHairGroupsPreview` |  | UObject |  | `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomImportOptions.h:62` |
| `UGroomImportOptions` | `/Script/HairStrandsCore.GroomImportOptions` |  | UObject |  | `Plugins/Runtime/HairStrands/Source/HairStrandsCore/Public/GroomImportOptions.h:15` |
| `UImageSequenceProtocol` | `/Script/MovieSceneCapture.ImageSequenceProtocol` | Abstract | UFrameGrabberProtocol |  | `Source/Runtime/MovieSceneCapture/Public/Protocols/ImageSequenceProtocol.h:16` |
| `UInEditorDocumentationSettings` | `/Script/InEditorDocumentation.InEditorDocumentationSettings` | DefaultConfig | UObject | FString TutorialUrl; bool bEnableEdcSearch; FString EdcSearchApiEndpoint; TMap<FString, FString> DocumentationPages | `Plugins/Experimental/InEditorDocumentation/Source/InEditorDocumentation/Public/InEditorDocumentationSettings.h:12` |
| `UInterchangeEditorSettings` | `/Script/InterchangeEngine.InterchangeEditorSettings` |  | UDeveloperSettings |  | `Source/Runtime/Interchange/Engine/Public/InterchangeProjectSettings.h:270` |
| `ULevelEditorMiscSettings` | `/Script/UnrealEd.LevelEditorMiscSettings` |  | UDeveloperSettings |  | `Source/Editor/UnrealEd/Classes/Settings/LevelEditorMiscSettings.h:17` |
| `ULevelEditorPlaySettings` | `/Script/UnrealEd.LevelEditorPlaySettings` |  | UObject |  | `Source/Editor/UnrealEd/Classes/Settings/LevelEditorPlaySettings.h:213` |
| `ULevelEditorViewportSettings` | `/Script/UnrealEd.LevelEditorViewportSettings` |  | UObject | EMarqueeSelectionMode MarqueeSelectionMode | `Source/Editor/UnrealEd/Classes/Settings/LevelEditorViewportSettings.h:310` |
| `ULevelInstanceEditorPerProjectUserSettings` | `/Script/LevelInstanceEditor.LevelInstanceEditorPerProjectUserSettings` |  | UDeveloperSettings |  | `Source/Editor/LevelInstanceEditor/Public/LevelInstanceEditorSettings.h:35` |
| `ULevelSequenceBurnInOptions` | `/Script/LevelSequence.LevelSequenceBurnInOptions` | PerObjectConfig | UObject |  | `Source/Runtime/LevelSequence/Public/LevelSequenceActor.h:29` |
| `ULevelSequenceEditorSettings` | `/Script/LevelSequenceEditor.LevelSequenceEditorSettings` |  | UObject |  | `Plugins/MovieScene/LevelSequenceEditor/Source/LevelSequenceEditor/Public/Misc/LevelSequenceEditorSettings.h:54` |
| `ULevelSequenceWithShotsSettings` | `/Script/LevelSequenceEditor.LevelSequenceWithShotsSettings` |  | UObject |  | `Plugins/MovieScene/LevelSequenceEditor/Source/LevelSequenceEditor/Public/Misc/LevelSequenceEditorSettings.h:80` |
| `ULiveCodingSettings` | `/Script/LiveCoding.LiveCodingSettings` |  | UObject |  | `Source/Developer/Windows/LiveCoding/Private/LiveCodingSettings.h:17` |
| `ULiveLinkEditorSettings` | `/Script/LiveLinkEditor.LiveLinkEditorSettings` |  | UObject |  | `Plugins/Animation/LiveLink/Source/LiveLinkEditor/Public/LiveLinkEditorSettings.h:12` |
| `ULiveLinkHubMessagingSettings` | `/Script/LiveLinkHubMessaging.LiveLinkHubMessagingSettings` |  | UObject |  | `Plugins/Animation/LiveLinkHub/Source/LiveLinkHubMessaging/Public/LiveLinkHubMessagingSettings.h:13` |
| `ULiveLinkHubTimeAndSyncSettings` | `/Script/LiveLinkHub.LiveLinkHubTimeAndSyncSettings` |  | UObject |  | `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Settings/LiveLinkHubTimeAndSyncSettings.h:21` |
| `ULiveLinkHubUserSettings` | `/Script/LiveLinkHub.LiveLinkHubUserSettings` |  | UObject |  | `Plugins/Animation/LiveLinkHub/Source/LiveLinkHub/Private/Settings/LiveLinkHubSettings.h:211` |
| `ULiveLinkUserSettings` | `/Script/LiveLink.LiveLinkUserSettings` |  | UObject |  | `Plugins/Animation/LiveLink/Source/LiveLink/Public/LiveLinkSettings.h:53` |
| `ULiveUpdateSlateSettings` | `/Script/LiveUpdateForSlate.LiveUpdateSlateSettings` |  | UObject | bool bEnableLiveUpdateForSlate | `Plugins/Editor/LiveUpdateForSlate/Source/LiveUpdateForSlate/Public/LiveUpdateSlateSettings.h:8` |
| `ULogVisualizerSettings` | `/Script/LogVisualizer.LogVisualizerSettings` |  | UObject |  | `Source/Developer/LogVisualizer/Public/LogVisualizerSettings.h:142` |
| `UMCPToolsetSettings` | `/Script/MCPClientToolset.MCPToolsetSettings` |  | UDeveloperSettings | TArray<FMCPServerConfig> MCPServers | `Plugins/Experimental/Toolsets/MCPClientToolset/Source/MCPClientToolset/Public/MCPClientToolset/MCPToolsetSettings.h:73` |
| `UMassDebuggerSettings` | `/Script/MassEntityDebugger.MassDebuggerSettings` |  | UMassModuleSettings |  | `Source/Editor/MassEntityDebugger/Public/MassDebuggerSettings.h:13` |
| `UMaterialEditorOptions` | `/Script/UnrealEd.MaterialEditorOptions` |  | UObject |  | `Source/Editor/UnrealEd/Classes/Preferences/MaterialEditorOptions.h:15` |
| `UMaterialEditorSettings` | `/Script/MaterialEditor.MaterialEditorSettings` |  | UObject |  | `Source/Editor/MaterialEditor/Public/MaterialEditorSettings.h:102` |
| `UMaterialStatsOptions` | `/Script/UnrealEd.MaterialStatsOptions` |  | UObject |  | `Source/Editor/UnrealEd/Classes/Preferences/MaterialStatsOptions.h:26` |
| `UMediaCompositingEditorSettings` | `/Script/MediaCompositingEditor.MediaCompositingEditorSettings` |  | UDeveloperSettings | bool bDisplayMediaTexturePrompt | `Plugins/Media/MediaCompositing/Source/MediaCompositingEditor/Private/Utils/MediaCompositingEditorSettings.h:9` |
| `UMediaFrameworkMediaCaptureSettings` | `/Script/MediaFrameworkUtilitiesEditor.MediaFrameworkMediaCaptureSettings` |  | UObject |  | `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/CaptureTab/SMediaFrameworkCapture.h:30` |
| `UMediaFrameworkVideoInputSettings` | `/Script/MediaFrameworkUtilitiesEditor.MediaFrameworkVideoInputSettings` |  | UObject |  | `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/MediaFrameworkVideoInputSettings.h:27` |
| `UMediaPlayerEditorSettings` | `/Script/MediaPlayerEditor.MediaPlayerEditorSettings` |  | UObject |  | `Plugins/Media/MediaPlayerEditor/Source/MediaPlayerEditor/Private/Shared/MediaPlayerEditorSettings.h:43` |
| `UMediaProfileEditorSettings` | `/Script/MediaProfile.MediaProfileEditorSettings` |  | UObject | bool bDisplayInToolbar; TSoftObjectPtr<UMediaProfile> UserMediaProfile | `Plugins/Media/MediaProfile/Source/MediaProfile/Public/Profile/MediaProfileSettings.h:108` |
| `UMediaProfileEditorUserSettings` | `/Script/MediaFrameworkUtilitiesEditor.MediaProfileEditorUserSettings` |  | UObject | bool bShowTimecodeInViewportToolbar; bool bShowTimecodeInEditorToolbar; bool bShowGenlockInViewportToolbar; bool bShowGenlockInEditorToolbar; bool bShowChannelsInViewportToolbar; TMap<FName, FMediaProfileEditorPerMediaItemSettings> PerMediaItemSettings; TArray<FMediaProfileEditorLayoutSettings> SavedLayouts; FString ActiveLayout | `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/AssetEditor/MediaProfileEditorUserSettings.h:93` |
| `UMediaViewerLibraryIni` | `/Script/MediaViewer.MediaViewerLibraryIni` |  | UObject | TArray<FMediaViewerLibraryGroup> Groups; TArray<FMediaViewerLibraryItemData> Items; TArray<FMediaViewerState> Bookmarks; TOptional<FMediaViewerState> LastOpenedState | `Plugins/Media/MediaViewer/Source/MediaViewer/Private/Library/MediaViewerLibraryIni.h:67` |
| `UMeshPaintModeSettings` | `/Script/MeshPaintEditorMode.MeshPaintModeSettings` |  | UObject |  | `Plugins/MeshPainting/Source/MeshPaintEditorMode/Private/MeshPaintModeSettings.h:35` |
| `UMeshPaintSettings` | `/Script/MeshPaint.MeshPaintSettings` |  | UObject |  | `Source/Editor/MeshPaint/Public/MeshPaintSettings.h:84` |
| `UMetaHumanCalibrationGeneratorSettings` | `/Script/MetaHumanCalibrationGenerator.MetaHumanCalibrationGeneratorSettings` |  | UObject |  | `Plugins/MetaHuman/MetaHumanCalibrationProcessing/Source/MetaHumanCalibrationGenerator/Private/Settings/MetaHumanCalibrationGeneratorSettings.h:13` |
| `UMetaHumanEditorSettings` | `/Script/MetaHumanCoreEditor.MetaHumanEditorSettings` |  | UObject | int32 SampleCount; int32 MaximumResolution; bool bForceSerialIngestion; bool bShowDevelopersContent; bool bShowOtherDevelopersContent; bool bLoadTrackersOnStartup; bool bTrainSolversFastLowMemory_DEPRECATED; TMap<FString, FString> PerformanceViewSetupSlot1; TMap<FString, FString> PerformanceViewSetupSlot2; TMap<FString, FString> PerformanceViewSetupSlot3; TMap<FString, FString> PerformanceViewSetupSlot4 | `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCoreEditor/Public/MetaHumanEditorSettings.h:14` |
| `UMetasoundEditorSettings` | `/Script/MetasoundEditor.MetasoundEditorSettings` |  | UObject |  | `Plugins/Runtime/Metasound/Source/MetasoundEditor/Private/MetasoundEditorSettings.h:108` |
| `UModelContextProtocolSettings` | `/Script/ModelContextProtocolEngine.ModelContextProtocolSettings` |  | UDeveloperSettings | FString ServerUrlPath; uint32 ServerPortNumber; bool bAutoStartServer; bool bEnableToolSearch | `Plugins/Experimental/ModelContextProtocol/Source/ModelContextProtocolEngine/Public/ModelContextProtocolSettings.h:17` |
| `UModelingComponentsSettings` | `/Script/ModelingComponents.ModelingComponentsSettings` |  | UDeveloperSettings |  | `Plugins/Runtime/MeshModelingToolset/Source/ModelingComponents/Public/ModelingComponentsSettings.h:18` |
| `UMotionTrailToolOptions` | `/Script/Sequencer.MotionTrailToolOptions` |  | UObject | ; ; FLinearColor DefaultColor; FLinearColor TimePreColor; FLinearColor TimePostColor; FLinearColor DashPreColor; FLinearColor DashPostColor; ; double TrailThickness; int32 FramesBefore; int32 FramesAfter; bool bShowKeys; FLinearColor SelectedKeyColor; double KeySize; bool bShowMarks; FLinearColor MarkColor; FLinearColor CurrentFrameMarkColor; double MarkSize; int32 MaxNumberPinned | `Source/Editor/Sequencer/Public/Tools/MotionTrailOptions.h:39` |
| `UMoviePipelineQueueProjectSettings` | `/Script/MovieRenderPipelineCore.MoviePipelineQueueProjectSettings` |  | UObject | EMoviePipelinePostRenderActionType PostRenderActionType | `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/MoviePipelineQueue.h:46` |
| `UMovieRenderGraphEditorSettings` | `/Script/MovieRenderPipelineCore.MovieRenderGraphEditorSettings` |  | UDeveloperSettings | FMovieGraphPostRenderSettings PostRenderSettings; EMoviePipelineDefaultConfigType DefaultConfigType; TArray<FSoftClassPath> VisibleBasicConfigOutputTypes; bool bShowBurnInForBasicConfig | `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/MovieRenderGraphEditorSettings.h:25` |
| `UMovieSceneAudioCaptureProtocolBase` | `/Script/MovieSceneCapture.MovieSceneAudioCaptureProtocolBase` | PerObjectConfig Abstract | UMovieSceneCaptureProtocolBase |  | `Source/Runtime/MovieSceneCapture/Public/MovieSceneCaptureProtocolBase.h:296` |
| `UMovieSceneCapture` | `/Script/MovieSceneCapture.MovieSceneCapture` | PerObjectConfig | UObject, IMovieSceneCaptureInterface, ICaptureProtocolHost |  | `Source/Runtime/MovieSceneCapture/Public/MovieSceneCapture.h:36` |
| `UMovieSceneCaptureProtocolBase` | `/Script/MovieSceneCapture.MovieSceneCaptureProtocolBase` | PerObjectConfig Abstract | UObject |  | `Source/Runtime/MovieSceneCapture/Public/MovieSceneCaptureProtocolBase.h:56` |
| `UMovieSceneImageCaptureProtocolBase` | `/Script/MovieSceneCapture.MovieSceneImageCaptureProtocolBase` | PerObjectConfig Abstract | UMovieSceneCaptureProtocolBase |  | `Source/Runtime/MovieSceneCapture/Public/MovieSceneCaptureProtocolBase.h:281` |
| `UMovieSceneSubSection` | `/Script/MovieScene.MovieSceneSubSection` |  | UMovieSceneSection , IMovieSceneEntityProvider |  | `Source/Runtime/MovieScene/Public/Sections/MovieSceneSubSection.h:92` |
| `UMovieSceneToolsProjectSettings` | `/Script/MovieSceneTools.MovieSceneToolsProjectSettings` |  | UObject |  | `Source/Editor/MovieSceneTools/Public/MovieSceneToolsProjectSettings.h:57` |
| `UMovieSceneTracksSettings` | `/Script/MovieSceneTracks.MovieSceneTracksSettings` | PerObjectConfig | UObject |  | `Source/Runtime/MovieSceneTracks/Public/MovieSceneTracksSettings.h:13` |
| `UNavigationToolSettings` | `/Script/SequenceNavigator.NavigationToolSettings` |  | UDeveloperSettings | bool bApplyDefaultColumnView; bool bUseShortNames; bool bUseMutedHierarchy; bool bAutoExpandToSelection; bool bAlwaysShowLockState; ENavigationToolItemViewMode ItemDefaultViewMode; ENavigationToolItemViewMode ItemProxyViewMode; TSet<FNavigationToolColumnView> CustomColumnViews; TSet<FName> EnabledBuiltInFilters; TMap<FName, FSequencerFilterBarConfig> FilterBars; bool bAutoExpandNodesOnFilterPass; bool bUseFilterSubmenusForCategories; bool bFilterBarVisible; EFilterBarLayout LastFilterBarLayout; float LastFilterBarSizeCoefficient; bool bSyncSelectionToNavigationTool; bool bSyncSelectionToSequencer | `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/NavigationToolSettings.h:52` |
| `UNeuralMorphEditorProjectSettings` | `/Script/NeuralMorphModelEditor.NeuralMorphEditorProjectSettings` |  | UDeveloperSettings |  | `Plugins/Animation/MLDeformer/NeuralMorphModel/Source/NeuralMorphModelEditor/Public/NeuralMorphEditorProjectSettings.h:12` |
| `UNiagaraDebugHUDSettings` | `/Script/Niagara.NiagaraDebugHUDSettings` |  | UObject, FNotifyHook | FNiagaraDebugHUDSettingsData Data | `Plugins/FX/Niagara/Source/Niagara/Public/NiagaraDebuggerCommon.h:815` |
| `UNiagaraOutliner` | `/Script/NiagaraEditor.NiagaraOutliner` |  | UObject, FNotifyHook |  | `Plugins/FX/Niagara/Source/NiagaraEditor/Private/NiagaraOutliner.h:122` |
| `UNiagaraScripStatsViewModelSettings` | `/Script/NiagaraEditor.NiagaraScripStatsViewModelSettings` |  | UObject |  | `Plugins/FX/Niagara/Source/NiagaraEditor/Private/ViewModels/NiagaraScriptStatsViewModel.h:19` |
| `UOnlinePIESettings` | `/Script/OnlineSubsystemUtils.OnlinePIESettings` |  | UDeveloperSettings |  | `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Private/OnlinePIESettings.h:13` |
| `UOutputLogSettings` | `/Script/OutputLog.OutputLogSettings` |  | UObject |  | `Source/Developer/OutputLog/Public/OutputLogSettings.h:84` |
| `UPCGEditorModeSettings` | `/Script/PCGEditor.PCGEditorModeSettings` |  | UDeveloperSettings | bool bEnableEditorMode; bool bHideToolButtonsDuringActiveTool; bool bShowEditorToastOnToolErrors; bool bDisableTemporalAntiAliasingWhenEnteringTool; TArray<FPCGPerInteractiveToolSettingSettings> InteractiveToolSettings | `Plugins/PCG/Source/PCGEditor/Private/EditorMode/PCGEdModeSettings.h:27` |
| `UPCGEditorSettings` | `/Script/PCGEditor.PCGEditorSettings` |  | UObject | EPCGEditorDoubleClickAction NodeDoubleClickAction; FPCGEditorAttributeListViewSettings AttributeListViewSettings | `Plugins/PCG/Source/PCGEditor/Public/PCGEditorSettings.h:81` |
| `UPCGMeshPartitionInteropEditorSettings` | `/Script/PCGMeshPartitionInteropEditor.PCGMeshPartitionInteropEditorSettings` |  | UObject |  | `Plugins/Experimental/PCGMeshPartitionInterop/Source/PCGMeshPartitionInteropEditor/Public/PCGMeshPartitionInteropEditorSettings.h:9` |
| `UPSDImporterEditorSettings` | `/Script/PSDImporterEditor.PSDImporterEditorSettings` |  | UDeveloperSettings | bool bResizeLayersToDocument; bool bImportInvisibleLayers | `Plugins/Experimental/PSDImporter/Source/PSDImporterEditor/Private/PSDImporterEditorSettings.h:12` |
| `UPVEditorSettings` | `/Script/ProceduralVegetationEditor.PVEditorSettings` |  | UObject |  | `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Public/PVEditorSettings.h:9` |
| `UPersonaOptions` | `/Script/UnrealEd.PersonaOptions` |  | UObject |  | `Source/Editor/UnrealEd/Classes/Preferences/PersonaOptions.h:114` |
| `UPhysicsAssetEditorOptions` | `/Script/UnrealEd.PhysicsAssetEditorOptions` |  | UObject |  | `Source/Editor/UnrealEd/Classes/Preferences/PhysicsAssetEditorOptions.h:45` |
| `UPhysicsAssetGenerationSettings` | `/Script/UnrealEd.PhysicsAssetGenerationSettings` |  | UObject |  | `Source/Editor/UnrealEd/Public/PhysicsAssetGenerationSettings.h:9` |
| `UPhysicsAssetRenderUtilities` | `/Script/Persona.PhysicsAssetRenderUtilities` |  | UObject |  | `Source/Editor/Persona/Public/PhysicsAssetRenderUtils.h:171` |
| `UPinnedCommandListSettings` | `/Script/PinnedCommandList.PinnedCommandListSettings` |  | UObject |  | `Source/Editor/PinnedCommandList/Private/PinnedCommandListSettings.h:53` |
| `UPoseSearchDebuggerConfig` | `/Script/PoseSearchEditor.PoseSearchDebuggerConfig` |  | UObject |  | `Plugins/Animation/PoseSearch/Source/Editor/Private/PoseSearchDebuggerSettings.h:11` |
| `UPythonScriptPluginUserSettings` | `/Script/PythonScriptPlugin.PythonScriptPluginUserSettings` |  | UDeveloperSettings |  | `Plugins/Experimental/PythonScriptPlugin/Source/PythonScriptPlugin/Private/PythonScriptPluginSettings.h:152` |
| `UReferenceViewerSettings` | `/Script/AssetManagerEditor.ReferenceViewerSettings` |  | UObject |  | `Plugins/Editor/AssetManagerEditor/Source/AssetManagerEditor/Public/ReferenceViewer/ReferenceViewerSettings.h:44` |
| `URemoteSessionStreamSettings` | `/Script/RemoteSessionEditor.RemoteSessionStreamSettings` |  | UObject |  | `Plugins/Experimental/RemoteSession/Source/RemoteSessionEditor/Private/Widgets/SRemoteSessionStream.h:42` |
| `URevisionControlOverlaySettings` | `/Script/SourceControlViewport.RevisionControlOverlaySettings` |  | UDeveloperSettings |  | `Source/Developer/SourceControlViewport/Public/RevisionControlOverlaySettings.h:12` |
| `URewindDebuggerSettings` | `/Script/RewindDebugger.RewindDebuggerSettings` |  | UDeveloperSettings | ERewindDebuggerCameraMode CameraMode; ERewindDebuggerObjectSortMode ObjectTrackSortMode; bool bShouldAutoEject; bool bShouldAutoRecordOnPIE; float PlaybackRate; bool bShowEmptyObjectTracks; TArray<FName> HiddenTrackTypes; FString DebugTargetActor; TArray<FSoftClassPath> SelectorAllowedTypes; TArray<FInstancedStruct> SelectorAllowedStructTypes | `Plugins/Animation/GameplayInsights/Source/RewindDebugger/Public/RewindDebuggerSettings.h:73` |
| `URewindDebuggerVLogSettings` | `/Script/RewindDebuggerVLog.RewindDebuggerVLogSettings` |  | UDeveloperSettings | uint8 DisplayVerbosity; TSet<FName> DisplayCategories; TMap<FName, uint8> DisplayCategoryVerbosities | `Plugins/Animation/GameplayInsights/Source/RewindDebuggerVLog/Private/RewindDebuggerVLogSettings.h:13` |
| `URigVMEditorSettings` | `/Script/RigVM.RigVMEditorSettings` |  | UDeveloperSettings |  | `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMSettings.h:31` |
| `UScribbleEditorSettings` | `/Script/Scribble.ScribbleEditorSettings` |  | UDeveloperSettings |  | `Plugins/Experimental/Animation/Scribble/Source/Scribble/Public/ScribbleSettings.h:19` |
| `USearchUserSettings` | `/Script/AssetSearch.SearchUserSettings` |  | UDeveloperSettings |  | `Plugins/Editor/AssetSearch/Source/Private/Settings/SearchUserSettings.h:26` |
| `USelectionSetsSettings` | `/Script/ControlRigEditor.SelectionSetsSettings` |  | UDeveloperSettings |  | `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Sequencer/SelectionSets/SelectionSetsSettings.h:20` |
| `USemanticSearchSettings` | `/Script/SemanticSearch.SemanticSearchSettings` | DefaultConfig | UDeveloperSettings | TArray<FDirectoryPath> IndexedPaths; bool bAutoIndexCachedOnStartup; bool bAutoIndexUncachedOnStartup; bool bAutoIndexOnSave; ESemanticSearchEmbeddingProvider Provider; FString CaptioningBaseUrl; FString CaptioningApiKey; FString CaptioningModel; FString EmbeddingBaseUrl; FString EmbeddingApiKey; FString EmbeddingModel; int32 EmbeddingDimension; int32 MaxRetries; float RetryTimeoutSeconds; int32 MaxConcurrentCaptionRequests; int32 MaxConcurrentEmbedRequests; ESemanticSearchIndexType IndexType; int32 PQSubvectorSize; int32 PQNBits; bool bEnableHybridSearch; int32 RRFConstant; int32 RRFOversample; int32 BM25MinShouldMatchPercent; float VectorDistanceCutoff; float SimilarityDistanceCutoff | `Plugins/Experimental/SemanticSearch/Source/SemanticSearch/Public/Settings/SemanticSearchSettings.h:21` |
| `USequencerSettings` | `/Script/Sequencer.SequencerSettings` | PerObjectConfig | UObject |  | `Source/Editor/Sequencer/Public/SequencerSettings.h:144` |
| `USequencerSimpleViewSettings` | `/Script/Sequencer.SequencerSimpleViewSettings` | DefaultConfig | UDeveloperSettings | bool bShowToolBar; bool bShowTransportControls; bool bShowRangeControls | `Source/Editor/Sequencer/Private/SimpleView/SequencerSimpleViewSettings.h:8` |
| `USizeMapSettings` | `/Script/AssetManagerEditor.SizeMapSettings` |  | UObject |  | `Plugins/Editor/AssetManagerEditor/Source/AssetManagerEditor/Private/SSizeMap.h:31` |
| `USkeletalMeshEditorSettings` | `/Script/UnrealEd.SkeletalMeshEditorSettings` |  | UObject |  | `Source/Editor/UnrealEd/Classes/Settings/SkeletalMeshEditorSettings.h:19` |
| `USkeletalMeshModelingToolsEditorSettings` | `/Script/MeshModelingToolsEditorOnly.SkeletalMeshModelingToolsEditorSettings` |  | UObject |  | `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingToolsEditorOnly/Public/SkeletalMesh/SkeletalMeshModelingToolsEditorSettings.h:11` |
| `USkinWeightImportOptions` | `/Script/Persona.SkinWeightImportOptions` |  | UObject | FString ProfileName | `Source/Editor/Persona/Public/SSkinWeightProfileImportOptions.h:25` |
| `USmartObjectAssetEditorSettings` | `/Script/SmartObjectsEditorModule.SmartObjectAssetEditorSettings` |  | UObject |  | `Plugins/Runtime/SmartObjects/Source/SmartObjectsEditorModule/Private/SmartObjectAssetEditorSettings.h:10` |
| `USpeedTreeImportData` | `/Script/SpeedTreeImporter.SpeedTreeImportData` |  | UAssetImportData |  | `Plugins/Editor/SpeedTreeImporter/Source/SpeedTreeImporter/Classes/SpeedTreeImportData.h:45` |
| `USpriteEditorSettings` | `/Script/Paper2DEditor.SpriteEditorSettings` |  | UObject |  | `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/SpriteEditor/SpriteEditorSettings.h:8` |
| `UStageMonitorEditorSettings` | `/Script/StageMonitorEditor.StageMonitorEditorSettings` |  | UObject | float RefreshRate; FString ColumnVisibilitySettings | `Plugins/VirtualProduction/StageMonitoring/Source/StageMonitorEditor/Private/StageMonitorEditorSettings.h:12` |
| `UStateCentricViewPerUserSettings` | `/Script/StateTreeEditorModule.StateCentricViewPerUserSettings` |  | UDeveloperSettings | TMap<TSoftClassPtr<UStateTreeSchema>, FStateCentricViewPerUserSetting> PerSchemaSettings | `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/StateCentricView/StateCentricViewPerUserSettings.h:155` |
| `UStateTreeEditorSettings` | `/Script/StateTreeEditorModule.StateTreeEditorSettings` |  | UDeveloperSettings |  | `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Public/StateTreeEditorSettings.h:28` |
| `UStateTreeEditorUserSettings` | `/Script/StateTreeEditorModule.StateTreeEditorUserSettings` |  | UDeveloperSettings |  | `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/StateTreeEditorUserSettings.h:24` |
| `UStaticMeshToSkeletalMeshConvertOptions` | `/Script/SkeletalMeshModelingTools.StaticMeshToSkeletalMeshConvertOptions` |  | UObject, IBoneReferenceSkeletonProvider | FDirectoryPath DestinationPath; EReferenceSkeletonImportOption SkeletonImportOption; ERootBonePlacementOptions RootBonePlacement; FSoftObjectPath Skeleton; FSoftObjectPath SkeletalMesh; FBoneReference BindingBoneName; FString PrefixToRemove; FString SkeletalMeshPrefixToAdd; FString SkeletalMeshSuffixToAdd; FString SkeletonPrefixToAdd; FString SkeletonSuffixToAdd | `Plugins/Animation/SkeletalMeshModelingTools/Source/SkeletalMeshModelingTools/Private/SkeletalMeshModelingToolsMeshConverter.h:108` |
| `UStructViewerSettings` | `/Script/UnrealEd.StructViewerSettings` |  | UObject |  | `Source/Editor/UnrealEd/Classes/Settings/StructViewerSettings.h:24` |
| `UTakeRecorderMicrophoneAudioManager` | `/Script/TakeRecorderSources.TakeRecorderMicrophoneAudioManager` | PerObjectConfig | UTakeRecorderAudioInputSettings |  | `Plugins/VirtualProduction/Takes/Source/TakeRecorderSources/Public/TakeRecorderMicrophoneAudioManager.h:27` |
| `UTakeRecorderUserSettings` | `/Script/TakeRecorder.TakeRecorderUserSettings` |  | UObject |  | `Plugins/VirtualProduction/Takes/Source/TakeRecorder/Public/TakeRecorderSettings.h:15` |
| `UTemplateSequenceEditorSettings` | `/Script/TemplateSequenceEditor.TemplateSequenceEditorSettings` |  | UObject |  | `Plugins/MovieScene/TemplateSequence/Source/TemplateSequenceEditor/Private/Misc/TemplateSequenceEditorSettings.h:10` |
| `UTerminalSettings` | `/Script/Terminal.TerminalSettings` |  | UDeveloperSettings | FString ShellExecutablePath; FString FontFamily; int32 FontSize; int32 ScrollbackLimit; FString ColorSchemeName; TArray<FString> StartupCommands; bool bPreventCloseDuringActivity; float ActivityTimeoutSeconds | `Plugins/Experimental/Terminal/Source/Terminal/Public/TerminalSettings.h:9` |
| `UTestCameraCalibrationSettings` | `/Script/CameraCalibrationEditor.TestCameraCalibrationSettings` |  | UDeveloperSettings |  | `Plugins/VirtualProduction/CameraCalibration/Source/CameraCalibrationEditor/Private/TestCameraCalibrationSettings.h:12` |
| `UTextureEditorSettings` | `/Script/TextureEditor.TextureEditorSettings` |  | UObject |  | `Source/Editor/TextureEditor/Classes/TextureEditorSettings.h:55` |
| `UTextureEncodingUserSettings` | `/Script/Engine.TextureEncodingUserSettings` |  | UDeveloperSettings |  | `Source/Runtime/Engine/Private/TextureEncodingSettingsPrivate.h:125` |
| `UTextureImportUserSettings` | `/Script/TextureUtilitiesCommon.TextureImportUserSettings` |  | UDeveloperSettings |  | `Source/Runtime/TextureUtilitiesCommon/Public/TextureImportUserSettings.h:16` |
| `UTileMapEditorSettings` | `/Script/Paper2DEditor.TileMapEditorSettings` |  | UObject |  | `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/TileMapEditing/TileMapEditorSettings.h:8` |
| `UTileSetEditorSettings` | `/Script/Paper2DEditor.TileSetEditorSettings` |  | UObject |  | `Plugins/2D/Paper2D/Source/Paper2DEditor/Private/TileSetEditor/TileSetEditorSettings.h:8` |
| `UTimecodeSynchronizerEditorSettings` | `/Script/TimecodeSynchronizer.TimecodeSynchronizerEditorSettings` |  | UObject |  | `Plugins/Media/TimecodeSynchronizer/Source/TimecodeSynchronizer/Public/TimecodeSynchronizerProjectSettings.h:54` |
| `UTimedDataMonitorEditorSettings` | `/Script/TimedDataMonitorEditor.TimedDataMonitorEditorSettings` |  | UObject | FTimedDataMonitorCalibrationParameters CalibrationSettings; FTimedDataMonitorTimeCorrectionParameters TimeCorrectionSettings; float RefreshRate; bool bDrawFrameTimesInBufferVisualization; bool bUseAccurateFrameTimesInBufferVisualization; bool bOverrideNumberOfStandardDeviationToShow; int32 OverrideNumberOfStandardDeviationToShow; double FrameTimeWarnThreshold; double TargetFrameTimePercent; ETimedDataMonitorEditorCalibrationType LastCalibrationType; bool bResetBufferStatEnabled; bool bClearMessageEnabled; bool bResetEvaluationTimeEnabled | `Plugins/VirtualProduction/TimedDataMonitor/Source/TimedDataMonitorEditor/Private/TimedDataMonitorEditorSettings.h:20` |
| `UToolMenus` | `/Script/ToolMenus.ToolMenus` |  | UObject |  | `Source/Developer/ToolMenus/Public/ToolMenus.h:99` |
| `UToolableTimelineDefaultSettings` | `/Script/Sequencer.ToolableTimelineDefaultSettings` | DefaultConfig | UDeveloperSettings |  | `Source/Editor/Sequencer/Private/ToolableTimeline/ToolableTimelineSettings.h:234` |
| `UToolableTimelineSettings` | `/Script/Sequencer.ToolableTimelineSettings` | DefaultConfig | UDeveloperSettings | FToolableTimelineInstanceSettings Settings | `Source/Editor/Sequencer/Private/ToolableTimeline/ToolableTimelineSettings.h:245` |
| `UToolsetRegistrySettings` | `/Script/ToolsetRegistry.ToolsetRegistrySettings` |  | UDeveloperSettings |  | `Plugins/Experimental/ToolsetRegistry/Source/ToolsetRegistry/Public/ToolsetRegistry/ToolsetRegistrySubsystem.h:21` |
| `UTransformGizmoEditorSettings` | `/Script/EditorInteractiveToolsFramework.TransformGizmoEditorSettings` |  | UDeveloperSettings | float TransformGizmoSize; bool bUseExperimentalGizmo; bool bUseEditorTRSGizmo; FGizmosParameters GizmosParameters | `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/TransformGizmoEditorSettings.h:13` |
| `UTweeningToolsUserSettings` | `/Script/TweeningUtilsEditor.TweeningToolsUserSettings` |  | UObject | TMap<FName, FString> PreferredTweenFunction | `Plugins/Animation/TweeningUtils/Source/TweeningUtilsEditor/Public/TweeningToolsUserSettings.h:13` |
| `UUAFEditorUserSettings` | `/Script/UAFEditor.UAFEditorUserSettings` |  | UDeveloperSettings | bool bSummonUAFBrowserHotkeyOpensSidebar; bool bAutoOpenFunctionsInSeparateTabs; bool bAutoCompileOutOfDateAssets; TArray<FString> UAFBrowserHiddenColumns | `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Settings/UAFEditorUserSettings.h:11` |
| `UUAFTemplateConfig` | `/Script/UAFEditor.UAFTemplateConfig` |  | UObject | ETemplateBlueprintMode BlueprintMode; FString BlueprintAssetName; TSubclassOf<AActor> BlueprintClass; TSoftObjectPtr<USkeletalMesh> SkeletalMesh; TSoftObjectPtr<UBlueprint> BlueprintToModify | `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/UAF/Wizard/TemplateConfig.h:22` |
| `UUndoHistorySettings` | `/Script/UndoHistoryEditor.UndoHistorySettings` |  | UObject |  | `Source/Editor/UndoHistoryEditor/Private/UndoHistorySettings.h:13` |
| `UUsdStageEditorSettings` | `/Script/USDStageEditor.UsdStageEditorSettings` |  | UObject |  | `Plugins/Importers/USDImporter/Source/USDStageEditor/Private/USDStageEditorSettings.h:9` |
| `UUsdStageImportOptions` | `/Script/USDStageImporter.UsdStageImportOptions` |  | UObject |  | `Plugins/Importers/USDImporter/Source/USDStageImporter/Public/USDStageImportOptions.h:48` |
| `UUserDefinedImageCaptureProtocol` | `/Script/MovieSceneCapture.UserDefinedImageCaptureProtocol` | Abstract | UUserDefinedCaptureProtocol |  | `Source/Runtime/MovieSceneCapture/Public/Protocols/UserDefinedCaptureProtocol.h:234` |
| `UVPUtilitiesEditorUserSettings` | `/Script/VPUtilitiesEditor.VPUtilitiesEditorUserSettings` |  | UObject |  | `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilitiesEditor/Public/VPUtilitiesEditorSettings.h:103` |
| `UVirtualCameraUserSettings` | `/Script/VirtualCamera.VirtualCameraUserSettings` |  | UObject | EVCamTutorialCompletionState VCamTutorialCompletionState; EVCamPhotoSaveMode PhotoSaveMode; FDirectoryPath PhotoSaveLocation; FDirectoryPath TextureSaveLocation | `Plugins/VirtualProduction/VirtualCamera/Source/VirtualCamera/Public/VCamUserSettings.h:27` |
| `UVirtualScoutingEditorSettings` | `/Script/VirtualScouting.VirtualScoutingEditorSettings` |  | UDeveloperSettings | ; ; ; ;  | `Plugins/VirtualProduction/VirtualScouting/Source/VirtualScouting/Public/VirtualScoutingSettings.h:53` |
| `UWaveformEditorTransformationsSettings` | `/Script/WaveformEditor.WaveformEditorTransformationsSettings` |  | UDeveloperSettings |  | `Plugins/Editor/WaveformEditor/Source/WaveformEditor/Private/WaveformEditorTransformationsSettings.h:15` |
| `UWaveformEditorWidgetsSettings` | `/Script/WaveformEditorWidgets.WaveformEditorWidgetsSettings` |  | UDeveloperSettings |  | `Plugins/Editor/WaveformEditor/Source/WaveformEditorWidgets/Private/WaveformEditorWidgetsSettings.h:11` |
| `UWaveformTransformationsWidgetsSettings` | `/Script/WaveformTransformationsWidgets.WaveformTransformationsWidgetsSettings` |  | UDeveloperSettings |  | `Plugins/Editor/WaveformEditor/Source/WaveformTransformationsWidgets/Private/WaveformTransformationsWidgetsSettings.h:20` |
| `UWidgetDesignerSettings` | `/Script/UMGEditor.WidgetDesignerSettings` |  | UDeveloperSettings |  | `Source/Editor/UMGEditor/Public/Settings/WidgetDesignerSettings.h:35` |
| `UWidgetPaletteFavorites` | `/Script/UMGEditor.WidgetPaletteFavorites` |  | UObject |  | `Source/Editor/UMGEditor/Classes/WidgetPaletteFavorites.h:15` |
| `UWorldBookmarkEditorPerProjectUserSettings` | `/Script/WorldBookmark.WorldBookmarkEditorPerProjectUserSettings` |  | UDeveloperSettings |  | `Source/Editor/WorldBookmark/Private/WorldBookmark/WorldBookmarkEditorSettings.h:36` |
| `UWorldPartitionEditorPerProjectUserSettings` | `/Script/Engine.WorldPartitionEditorPerProjectUserSettings` |  | UDeveloperSettings |  | `Source/Runtime/Engine/Public/WorldPartition/WorldPartitionEditorPerProjectUserSettings.h:52` |
| `UXRCreativeEditorSettings` | `/Script/XRCreative.XRCreativeEditorSettings` |  | UDeveloperSettings | EXRCreativeHandedness Handedness | `Plugins/Experimental/XRCreativeFramework/Source/XRCreative/Public/XRCreativeSettings.h:38` |

## config=Editor (239)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UAIAssistantContextProject` | `/Script/AIAssistant.AIAssistantContextProject` |  | UDeveloperSettings | FString Prompt | `Plugins/Experimental/AIAssistant/Source/AIAssistant/Private/AIAssistantToolset.h:26` |
| `UActorFactory` | `/Script/UnrealEd.ActorFactory` |  | UObject, IAssetFactoryInterface |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactory.h:25` |
| `UActorFactoryAmbientSound` | `/Script/UnrealEd.ActorFactoryAmbientSound` |  | UActorFactory |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactoryAmbientSound.h:18` |
| `UActorFactoryAnimationAsset` | `/Script/UnrealEd.ActorFactoryAnimationAsset` |  | UActorFactorySkeletalMesh |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactoryAnimationAsset.h:15` |
| `UActorFactoryBasicShape` | `/Script/UnrealEd.ActorFactoryBasicShape` |  | UActorFactoryStaticMesh |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactoryBasicShape.h:14` |
| `UActorFactoryBlueprint` | `/Script/UnrealEd.ActorFactoryBlueprint` |  | UActorFactory |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactoryBlueprint.h:14` |
| `UActorFactoryBoxReflectionCapture` | `/Script/UnrealEd.ActorFactoryBoxReflectionCapture` |  | UActorFactory |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactoryBoxReflectionCapture.h:11` |
| `UActorFactoryBoxVolume` | `/Script/UnrealEd.ActorFactoryBoxVolume` |  | UActorFactoryVolume |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactoryBoxVolume.h:14` |
| `UActorFactoryCameraActor` | `/Script/UnrealEd.ActorFactoryCameraActor` |  | UActorFactory |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactoryCameraActor.h:11` |
| `UActorFactoryChaosSolver` | `/Script/ChaosSolverEditor.ActorFactoryChaosSolver` |  | UActorFactory |  | `Plugins/Experimental/ChaosSolverPlugin/Source/ChaosSolverEditor/Private/Chaos/ActorFactoryChaosSolver.h:12` |
| `UActorFactoryCharacter` | `/Script/UnrealEd.ActorFactoryCharacter` |  | UActorFactory |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactoryCharacter.h:13` |
| `UActorFactoryClass` | `/Script/UnrealEd.ActorFactoryClass` |  | UActorFactory |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactoryClass.h:16` |
| `UActorFactoryCylinderVolume` | `/Script/UnrealEd.ActorFactoryCylinderVolume` |  | UActorFactoryVolume |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactoryCylinderVolume.h:14` |
| `UActorFactoryDeferredDecal` | `/Script/UnrealEd.ActorFactoryDeferredDecal` |  | UActorFactory |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactoryDeferredDecal.h:15` |
| `UActorFactoryDestructible` | `/Script/ApexDestructionEditor.ActorFactoryDestructible` |  | UActorFactory |  | `Plugins/Runtime/ApexDestruction/Source/ApexDestructionEditor/Private/ActorFactoryDestructible.h:12` |
| `UActorFactoryDirectionalLight` | `/Script/UnrealEd.ActorFactoryDirectionalLight` |  | UActorFactory |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactoryDirectionalLight.h:11` |
| `UActorFactoryEmitter` | `/Script/UnrealEd.ActorFactoryEmitter` |  | UActorFactory |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactoryEmitter.h:14` |
| `UActorFactoryEmptyActor` | `/Script/UnrealEd.ActorFactoryEmptyActor` |  | UActorFactory |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactoryEmptyActor.h:16` |
| `UActorFactoryEnvironmentQuery` | `/Script/EnvironmentQueryEditor.ActorFactoryEnvironmentQuery` |  | UActorFactory |  | `Plugins/AI/EnvironmentQueryEditor/Source/EnvironmentQueryEditor/Public/ActorFactoryEnvironmentQuery.h:11` |
| `UActorFactoryExponentialHeightFog` | `/Script/UnrealEd.ActorFactoryExponentialHeightFog` |  | UActorFactory |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactoryExponentialHeightFog.h:11` |
| `UActorFactoryFieldSystem` | `/Script/FieldSystemEditor.ActorFactoryFieldSystem` |  | UActorFactory |  | `Plugins/Experimental/FieldSystemPlugin/Source/FieldSyStemEditor/Private/Field/ActorFactoryFieldSystem.h:12` |
| `UActorFactoryFlesh` | `/Script/ChaosFleshEditor.ActorFactoryFlesh` |  | UActorFactory |  | `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEditor/Private/ChaosFlesh/Asset/ActorFactoryFlesh.h:12` |
| `UActorFactoryGeometryCache` | `/Script/GeometryCacheEd.ActorFactoryGeometryCache` |  | UActorFactory |  | `Plugins/Runtime/GeometryCache/Source/GeometryCacheEd/Classes/ActorFactoryGeometryCache.h:12` |
| `UActorFactoryGeometryCollection` | `/Script/GeometryCollectionEditor.ActorFactoryGeometryCollection` |  | UActorFactory |  | `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionEditor/Private/GeometryCollection/ActorFactoryGeometryCollection.h:14` |
| `UActorFactoryInteractiveFoliage` | `/Script/UnrealEd.ActorFactoryInteractiveFoliage` |  | UActorFactoryStaticMesh |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactoryInteractiveFoliage.h:13` |
| `UActorFactoryLandscape` | `/Script/LandscapeEditor.ActorFactoryLandscape` |  | UActorFactory |  | `Source/Editor/LandscapeEditor/Private/Classes/ActorFactoryLandscape.h:14` |
| `UActorFactoryLidarPointCloud` | `/Script/LidarPointCloudEditor.ActorFactoryLidarPointCloud` |  | UActorFactory |  | `Plugins/Enterprise/LidarPointCloud/Source/LidarPointCloudEditor/Private/ActorFactoryLidarPointCloud.h:13` |
| `UActorFactoryLocalFogVolume` | `/Script/UnrealEd.ActorFactoryLocalFogVolume` |  | UActorFactory |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactoryLocalFogVolume.h:10` |
| `UActorFactoryMediaBundle` | `/Script/MediaFrameworkUtilitiesEditor.ActorFactoryMediaBundle` |  | UActorFactory |  | `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/MediaBundleFactoryNew.h:28` |
| `UActorFactoryNiagara` | `/Script/NiagaraEditor.ActorFactoryNiagara` |  | UActorFactory |  | `Plugins/FX/Niagara/Source/NiagaraEditor/Public/ActorFactoryNiagara.h:14` |
| `UActorFactoryNote` | `/Script/UnrealEd.ActorFactoryNote` |  | UActorFactory |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactoryNote.h:10` |
| `UActorFactoryPawn` | `/Script/UnrealEd.ActorFactoryPawn` |  | UActorFactoryEmptyActor |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactoryPawn.h:13` |
| `UActorFactoryPhysicsAsset` | `/Script/UnrealEd.ActorFactoryPhysicsAsset` |  | UActorFactory |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactoryPhysicsAsset.h:14` |
| `UActorFactoryPlanarReflection` | `/Script/UnrealEd.ActorFactoryPlanarReflection` |  | UActorFactory |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactoryPlanarReflection.h:11` |
| `UActorFactoryPlaneReflectionCapture` | `/Script/UnrealEd.ActorFactoryPlaneReflectionCapture` |  | UActorFactory |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactoryPlaneReflectionCapture.h:11` |
| `UActorFactoryPlayerStart` | `/Script/UnrealEd.ActorFactoryPlayerStart` |  | UActorFactory |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactoryPlayerStart.h:11` |
| `UActorFactoryPointLight` | `/Script/UnrealEd.ActorFactoryPointLight` |  | UActorFactory |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactoryPointLight.h:11` |
| `UActorFactoryProceduralFoliage` | `/Script/FoliageEdit.ActorFactoryProceduralFoliage` |  | UActorFactoryBoxVolume |  | `Source/Editor/FoliageEdit/Private/ActorFactoryProceduralFoliage.h:18` |
| `UActorFactoryRectLight` | `/Script/UnrealEd.ActorFactoryRectLight` |  | UActorFactory |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactoryRectLight.h:11` |
| `UActorFactoryRuntimeVirtualTextureVolume` | `/Script/UnrealEd.ActorFactoryRuntimeVirtualTextureVolume` |  | UActorFactory |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactoryRuntimeVirtualTextureVolume.h:10` |
| `UActorFactorySkeletalMesh` | `/Script/UnrealEd.ActorFactorySkeletalMesh` |  | UActorFactory |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactorySkeletalMesh.h:18` |
| `UActorFactorySkyAtmosphere` | `/Script/UnrealEd.ActorFactorySkyAtmosphere` |  | UActorFactory |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactorySkyAtmosphere.h:11` |
| `UActorFactorySkyLight` | `/Script/UnrealEd.ActorFactorySkyLight` |  | UActorFactory |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactorySkyLight.h:11` |
| `UActorFactorySphereReflectionCapture` | `/Script/UnrealEd.ActorFactorySphereReflectionCapture` |  | UActorFactory |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactorySphereReflectionCapture.h:11` |
| `UActorFactorySphereVolume` | `/Script/UnrealEd.ActorFactorySphereVolume` |  | UActorFactoryVolume |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactorySphereVolume.h:14` |
| `UActorFactorySpotLight` | `/Script/UnrealEd.ActorFactorySpotLight` |  | UActorFactory |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactorySpotLight.h:11` |
| `UActorFactoryTargetPoint` | `/Script/UnrealEd.ActorFactoryTargetPoint` |  | UActorFactory |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactoryTargetPoint.h:10` |
| `UActorFactoryTextRender` | `/Script/UnrealEd.ActorFactoryTextRender` |  | UActorFactory |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactoryTextRender.h:11` |
| `UActorFactoryTriggerBox` | `/Script/UnrealEd.ActorFactoryTriggerBox` |  | UActorFactory |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactoryTriggerBox.h:11` |
| `UActorFactoryTriggerCapsule` | `/Script/UnrealEd.ActorFactoryTriggerCapsule` |  | UActorFactory |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactoryTriggerCapsule.h:11` |
| `UActorFactoryTriggerSphere` | `/Script/UnrealEd.ActorFactoryTriggerSphere` |  | UActorFactory |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactoryTriggerSphere.h:11` |
| `UActorFactoryVectorFieldVolume` | `/Script/UnrealEd.ActorFactoryVectorFieldVolume` |  | UActorFactory |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactoryVectorFieldVolume.h:14` |
| `UActorFactoryVolume` | `/Script/UnrealEd.ActorFactoryVolume` | Abstract | UActorFactory |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactoryVolume.h:12` |
| `UActorFactoryVolumetricCloud` | `/Script/UnrealEd.ActorFactoryVolumetricCloud` |  | UActorFactory |  | `Source/Editor/UnrealEd/Classes/ActorFactories/ActorFactoryVolumetricCloud.h:11` |
| `UAnimBlueprintThumbnailRenderer` | `/Script/UnrealEd.AnimBlueprintThumbnailRenderer` |  | UDefaultSizedThumbnailRenderer |  | `Source/Editor/UnrealEd/Classes/ThumbnailRendering/AnimBlueprintThumbnailRenderer.h:19` |
| `UAnimGraphSettings` | `/Script/AnimGraph.AnimGraphSettings` |  | UDeveloperSettings |  | `Source/Editor/AnimGraph/Public/AnimGraphSettings.h:8` |
| `UAnimSequenceExporterUSDOptions` | `/Script/USDExporter.AnimSequenceExporterUSDOptions` |  | UObject |  | `Plugins/Importers/USDImporter/Source/USDExporter/Public/AnimSequenceExporterUSDOptions.h:16` |
| `UAnimSequenceThumbnailRenderer` | `/Script/UnrealEd.AnimSequenceThumbnailRenderer` |  | UDefaultSizedThumbnailRenderer |  | `Source/Editor/UnrealEd/Classes/ThumbnailRendering/AnimSequenceThumbnailRenderer.h:18` |
| `UAnimStateTransitionNode` | `/Script/AnimGraph.AnimStateTransitionNode` |  | UAnimStateNodeBase | float CrossfadeDuration | `Source/Editor/AnimGraph/Public/AnimStateTransitionNode.h:19` |
| `UAnimationModifier` | `/Script/AnimationModifiers.AnimationModifier` |  | UObject |  | `Source/Editor/AnimationModifiers/Public/AnimationModifier.h:33` |
| `UAssetBakeOptions` | `/Script/MaterialBaking.AssetBakeOptions` |  | UObject |  | `Source/Developer/MaterialBaking/Public/MaterialOptions.h:103` |
| `UAssetDefinitionRegistry` | `/Script/AssetDefinition.AssetDefinitionRegistry` |  | UObject |  | `Source/Editor/AssetDefinition/Public/AssetDefinitionRegistry.h:17` |
| `UAssetRegUtilCommandlet` | `/Script/UnrealEd.AssetRegUtilCommandlet` |  | UCommandlet |  | `Source/Editor/UnrealEd/Classes/Commandlets/AssetRegUtilCommandlet.h:18` |
| `UAssetViewerSettings` | `/Script/AdvancedPreviewScene.AssetViewerSettings` |  | UObject, FEditorUndoClient | bool bFakeConfigValue_HACK | `Source/Editor/AdvancedPreviewScene/Public/AssetViewerSettings.h:340` |
| `UAutoReimportManager` | `/Script/UnrealEd.AutoReimportManager` |  | UObject |  | `Source/Editor/UnrealEd/Public/AutoReimport/AutoReimportManager.h:27` |
| `UBlendSpaceThumbnailRenderer` | `/Script/UnrealEd.BlendSpaceThumbnailRenderer` |  | UDefaultSizedThumbnailRenderer |  | `Source/Editor/UnrealEd/Classes/ThumbnailRendering/BlendSpaceThumbnailRenderer.h:18` |
| `UBlueprintEditorProjectSettings` | `/Script/UnrealEd.BlueprintEditorProjectSettings` |  | UDeveloperSettings |  | `Source/Editor/UnrealEd/Public/Settings/BlueprintEditorProjectSettings.h:13` |
| `UBlueprintThumbnailRenderer` | `/Script/UnrealEd.BlueprintThumbnailRenderer` |  | UDefaultSizedThumbnailRenderer |  | `Source/Editor/UnrealEd/Classes/ThumbnailRendering/BlueprintThumbnailRenderer.h:20` |
| `UCaptureManagerSettings` | `/Script/CaptureManagerSettings.CaptureManagerSettings` |  | UObject |  | `Plugins/VirtualProduction/CaptureManager/CaptureManagerApp/Source/CaptureManagerSettings/Public/Settings/CaptureManagerSettings.h:16` |
| `UCascadeConfiguration` | `/Script/Cascade.CascadeConfiguration` |  | UObject |  | `Plugins/FX/Cascade/Source/Cascade/Classes/CascadeConfiguration.h:30` |
| `UChunkAssignerCommandlet` | `/Script/UnrealEd.ChunkAssignerCommandlet` |  | UCommandlet |  | `Source/Editor/UnrealEd/Classes/Commandlets/ChunkAssignerCommandlet.h:15` |
| `UClassThumbnailRenderer` | `/Script/UnrealEd.ClassThumbnailRenderer` |  | UDefaultSizedThumbnailRenderer |  | `Source/Editor/UnrealEd/Classes/ThumbnailRendering/ClassThumbnailRenderer.h:15` |
| `UCodeEditorCustomization` | `/Script/CodeEditor.CodeEditorCustomization` |  | UObject |  | `Plugins/Experimental/CodeEditor/Source/CodeEditor/Private/CodeEditorCustomization.h:39` |
| `UCollisionAutomationTestConfigData` | `/Script/EditorTests.CollisionAutomationTestConfigData` |  | UObject |  | `Plugins/Tests/EditorTests/Source/EditorTests/Private/UnrealEd/CollisionAutomationTests.h:57` |
| `UCommonUIEditorSettings` | `/Script/CommonUI.CommonUIEditorSettings` |  | UObject |  | `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonUIEditorSettings.h:13` |
| `UCompileShadersTestBedCommandlet` | `/Script/UnrealEd.CompileShadersTestBedCommandlet` |  | UCommandlet |  | `Source/Editor/UnrealEd/Classes/Commandlets/CompileShadersTestBedCommandlet.h:9` |
| `UComposureEditorSettings` | `/Script/ComposureLayersEditor.ComposureEditorSettings` |  | UObject | TArray<FSoftObjectPath> FeaturedCompShotClassOverrides; TArray<FSoftObjectPath> FeaturedElementClassOverrides | `Plugins/Compositing/Composure/Source/ComposureLayersEditor/Private/ComposureEditorSettings.h:23` |
| `UConcertSessionBrowserSettings` | `/Script/ConcertSharedSlate.ConcertSessionBrowserSettings` |  | UObject |  | `Plugins/Developer/Concert/ConcertUI/ConcertSharedSlate/Source/ConcertSharedSlate/Public/Session/Browser/ConcertSessionBrowserSettings.h:11` |
| `UContentBrowserCollectionProjectSettings` | `/Script/ContentBrowser.ContentBrowserCollectionProjectSettings` |  | UDeveloperSettings |  | `Source/Editor/ContentBrowser/Private/ContentBrowserConfig.h:128` |
| `UContentBrowserDataSubsystem` | `/Script/ContentBrowserData.ContentBrowserDataSubsystem` |  | UEditorSubsystem, IContentBrowserItemDataSink |  | `Source/Editor/ContentBrowserData/Public/ContentBrowserDataSubsystem.h:113` |
| `UControlRigPoseThumbnailRenderer` | `/Script/ControlRigEditor.ControlRigPoseThumbnailRenderer` |  | UDefaultSizedThumbnailRenderer |  | `Plugins/Animation/ControlRig/Source/ControlRigEditor/Public/Tools/ControlRigPoseThumbnailRenderer.h:19` |
| `UControlRigThumbnailRenderer` | `/Script/ControlRigEditor.ControlRigThumbnailRenderer` |  | USkeletalMeshThumbnailRenderer |  | `Plugins/Animation/ControlRig/Source/ControlRigEditor/Public/ControlRigThumbnailRenderer.h:20` |
| `UCookCommandlet` | `/Script/UnrealEd.CookCommandlet` |  | UCommandlet |  | `Source/Editor/UnrealEd/Classes/Commandlets/CookCommandlet.h:24` |
| `UCookGlobalShadersCommandlet` | `/Script/UnrealEd.CookGlobalShadersCommandlet` |  | UCommandlet |  | `Source/Editor/UnrealEd/Classes/Commandlets/CookGlobalShadersCommandlet.h:14` |
| `UCookShadersCommandlet` | `/Script/UnrealEd.CookShadersCommandlet` |  | UCommandlet |  | `Source/Editor/UnrealEd/Classes/Commandlets/CookShadersCommandlet.h:10` |
| `UCopyNaniteFallbackSettingsToRayTracingProxyCommandlet` | `/Script/UnrealEd.CopyNaniteFallbackSettingsToRayTracingProxyCommandlet` |  | UCommandlet |  | `Source/Editor/UnrealEd/Classes/Commandlets/CopyNaniteFallbackSettingsToRayTracingProxyCommandlet.h:10` |
| `UCurveFloatThumbnailRenderer` | `/Script/UnrealEd.CurveFloatThumbnailRenderer` |  | UThumbnailRenderer |  | `Source/Editor/UnrealEd/Classes/ThumbnailRendering/CurveThumbnailRenderer.h:17` |
| `UCurveLinearColorThumbnailRenderer` | `/Script/UnrealEd.CurveLinearColorThumbnailRenderer` |  | UThumbnailRenderer |  | `Source/Editor/UnrealEd/Classes/ThumbnailRendering/CurveThumbnailRenderer.h:43` |
| `UCurveVector3ThumbnailRenderer` | `/Script/UnrealEd.CurveVector3ThumbnailRenderer` |  | UThumbnailRenderer |  | `Source/Editor/UnrealEd/Classes/ThumbnailRendering/CurveThumbnailRenderer.h:30` |
| `UCustomizableObjectInstanceFactory` | `/Script/CustomizableObjectEditor.CustomizableObjectInstanceFactory` |  | UActorFactory |  | `Plugins/Mutable/Source/CustomizableObjectEditor/Public/MuCOE/CustomizableObjectInstanceFactory.h:14` |
| `UDDCProjectSettings` | `/Script/UnrealEd.DDCProjectSettings` |  | UDeveloperSettings |  | `Source/Editor/UnrealEd/Public/Settings/EditorProjectSettings.h:296` |
| `UDMXGDTFImportUI` | `/Script/DMXEditor.DMXGDTFImportUI` |  | UObject | bool bUseSubDirectory; bool bImportXML; bool bImportTextures; bool bImportModels | `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Factories/DMXGDTFImportUI.h:10` |
| `UDataValidationChangelist` | `/Script/DataValidation.DataValidationChangelist` |  | UObject |  | `Plugins/Editor/DataValidation/Source/DataValidation/Public/DataValidationChangelist.h:17` |
| `UDataValidationSettings` | `/Script/DataValidation.DataValidationSettings` |  | UDeveloperSettings | uint32 bValidateOnSave : 1; uint32 bLoadAssetsWhenValidatingChangelists : 1; bool bEnableMaterialValidation; bool bMaterialValidationAllowCompilingShaders; bool bMaterialValidationShowWarningsWhenNotCompilingShaders; TArray<FMaterialEditorValidationPlatform> MaterialValidationPlatforms | `Plugins/Editor/DataValidation/Source/DataValidation/Public/DataValidationSettings.h:15` |
| `UDataflowSettings` | `/Script/DataflowCore.DataflowSettings` |  | UDeveloperSettings |  | `Source/Runtime/Dataflow/Core/Public/Dataflow/DataflowSettings.h:49` |
| `UDebugShaderCompileJobCommandlet` | `/Script/UnrealEd.DebugShaderCompileJobCommandlet` |  | UCommandlet |  | `Source/Editor/UnrealEd/Classes/Commandlets/DebugShaderCompileJobCommandlet.h:9` |
| `UDefaultSizedThumbnailRenderer` | `/Script/UnrealEd.DefaultSizedThumbnailRenderer` |  | UThumbnailRenderer |  | `Source/Editor/UnrealEd/Classes/ThumbnailRendering/DefaultSizedThumbnailRenderer.h:15` |
| `UDestructibleMeshThumbnailRenderer` | `/Script/ApexDestructionEditor.DestructibleMeshThumbnailRenderer` |  | UDefaultSizedThumbnailRenderer |  | `Plugins/Runtime/ApexDestruction/Source/ApexDestructionEditor/Private/DestructibleMeshThumbnailRenderer.h:16` |
| `UDiffAssetRegistriesCommandlet` | `/Script/UnrealEd.DiffAssetRegistriesCommandlet` |  | UCommandlet |  | `Source/Editor/UnrealEd/Classes/Commandlets/DiffAssetRegistriesCommandlet.h:15` |
| `UDirectLinkExtensionSettings` | `/Script/DirectLinkExtension.DirectLinkExtensionSettings` |  | UObject |  | `Plugins/Enterprise/DatasmithImporter/Source/DirectLinkExtension/Public/DirectLinkExtensionSettings.h:11` |
| `UDisplayClusterLightCardEditorProjectSettings` | `/Script/DisplayClusterLightCardEditor.DisplayClusterLightCardEditorProjectSettings` |  | UObject |  | `Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditor/Private/Settings/DisplayClusterLightCardEditorSettings.h:16` |
| `UDocumentationSettings` | `/Script/Documentation.DocumentationSettings` |  | UDeveloperSettings | TArray<FDocumentationBaseUrl> DocumentationBaseUrls; TArray<FDocumentationRedirect> DocumentationRedirects | `Source/Editor/Documentation/Public/DocumentationSettings.h:37` |
| `UDumpLightFunctionMaterialInfoCommandlet` | `/Script/UnrealEd.DumpLightFunctionMaterialInfoCommandlet` |  | UCommandlet |  | `Source/Editor/UnrealEd/Classes/Commandlets/DumpLightFunctionMaterialInfo.h:10` |
| `UDumpMaterialExpressionInfoCommandlet` | `/Script/UnrealEd.DumpMaterialExpressionInfoCommandlet` |  | UCommandlet |  | `Source/Editor/UnrealEd/Classes/Commandlets/DumpMaterialExpressionInfo.h:50` |
| `UDumpMaterialExpressionsCommandlet` | `/Script/UnrealEd.DumpMaterialExpressionsCommandlet` |  | UCommandlet |  | `Source/Editor/UnrealEd/Classes/Commandlets/DumpMaterialExpressionsCommandlet.h:10` |
| `UDumpMaterialInfoCommandlet` | `/Script/UnrealEd.DumpMaterialInfoCommandlet` |  | UCommandlet |  | `Source/Editor/UnrealEd/Classes/Commandlets/DumpMaterialInfo.h:14` |
| `UDumpMaterialShaderTypesCommandlet` | `/Script/UnrealEd.DumpMaterialShaderTypesCommandlet` |  | UCommandlet |  | `Source/Editor/UnrealEd/Classes/Commandlets/DumpMaterialShaderTypes.h:10` |
| `UDynamicMaterialInstanceThumbnailRenderer` | `/Script/DynamicMaterialEditor.DynamicMaterialInstanceThumbnailRenderer` |  | UDefaultSizedThumbnailRenderer |  | `Plugins/VirtualProduction/DynamicMaterial/Source/DynamicMaterialEditor/Private/UI/Utils/DynamicMaterialInstanceThumbnailRenderer.h:16` |
| `UEdGraphSchema_K2` | `/Script/BlueprintGraph.EdGraphSchema_K2` |  | UEdGraphSchema |  | `Source/Editor/BlueprintGraph/Classes/EdGraphSchema_K2.h:386` |
| `UEditorDomainSaveCommandlet` | `/Script/UnrealEd.EditorDomainSaveCommandlet` |  | UCommandlet |  | `Source/Editor/UnrealEd/Classes/Commandlets/EditorDomainSaveCommandlet.h:10` |
| `UEditorPerformanceProjectSettings` | `/Script/UnrealEd.EditorPerformanceProjectSettings` |  | UDeveloperSettings |  | `Source/Editor/UnrealEd/Public/Settings/EditorProjectSettings.h:222` |
| `UEditorProjectAppearanceSettings` | `/Script/UnrealEd.EditorProjectAppearanceSettings` |  | UDeveloperSettings |  | `Source/Editor/UnrealEd/Public/Settings/EditorProjectSettings.h:57` |
| `UEditorProjectAssetSettings` | `/Script/UnrealEd.EditorProjectAssetSettings` |  | UDeveloperSettings |  | `Source/Editor/UnrealEd/Public/Settings/EditorProjectSettings.h:276` |
| `UEditorUtilityWidget` | `/Script/Blutility.EditorUtilityWidget` | Abstract | UUserWidget, IAssetRegistryTagProviderInterface | FText TabDisplayName; FString HelpText; bool bAlwaysReregisterWithWindowsMenu | `Source/Editor/Blutility/Classes/EditorUtilityWidget.h:26` |
| `UEditorUtilityWidgetProjectSettings` | `/Script/Blutility.EditorUtilityWidgetProjectSettings` |  | UWidgetEditingProjectSettings |  | `Source/Editor/Blutility/Public/EditorUtilityWidgetProjectSettings.h:25` |
| `UEditorValidatorBase` | `/Script/DataValidation.EditorValidatorBase` | Abstract | UObject | bool bIsConfigDisabled | `Plugins/Editor/DataValidation/Source/DataValidation/Public/EditorValidatorBase.h:27` |
| `UEditorValidatorSubsystem` | `/Script/DataValidation.EditorValidatorSubsystem` |  | UEditorSubsystem |  | `Plugins/Editor/DataValidation/Source/DataValidation/Public/EditorValidatorSubsystem.h:257` |
| `UFleshAssetThumbnailRenderer` | `/Script/ChaosFleshEditor.FleshAssetThumbnailRenderer` |  | UDefaultSizedThumbnailRenderer |  | `Plugins/Experimental/ChaosFlesh/Source/ChaosFleshEditor/Public/ChaosFlesh/Asset/FleshAssetThumbnailRenderer.h:19` |
| `UFoliageType_ActorThumbnailRenderer` | `/Script/FoliageEdit.FoliageType_ActorThumbnailRenderer` |  | UBlueprintThumbnailRenderer |  | `Source/Editor/FoliageEdit/Public/FoliageType_ActorThumbnailRenderer.h:21` |
| `UFoliageType_ISMThumbnailRenderer` | `/Script/FoliageEdit.FoliageType_ISMThumbnailRenderer` |  | UDefaultSizedThumbnailRenderer |  | `Source/Editor/FoliageEdit/Public/FoliageType_ISMThumbnailRenderer.h:21` |
| `UFractureModeCustomizationSettings` | `/Script/FractureEditor.FractureModeCustomizationSettings` |  | UDeveloperSettings |  | `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Public/FractureEditorMode.h:146` |
| `UFractureModeSettings` | `/Script/FractureEditor.FractureModeSettings` |  | UDeveloperSettings |  | `Plugins/Experimental/ChaosEditor/Source/FractureEditor/Public/FractureModeSettings.h:34` |
| `UFusionPatchCreateOptions` | `/Script/HarmonixDspEditor.FusionPatchCreateOptions` |  | UObject | EFusionPatchKeyzoneNoteScaleOption ScaleOption; int32 OctaveAdjust | `Plugins/Runtime/Harmonix/Source/HarmonixDspEditor/Private/FusionPatchImportOptions.h:92` |
| `UGameFeatureVersePathMapperCommandlet` | `/Script/GameFeatures.GameFeatureVersePathMapperCommandlet` |  | UCommandlet |  | `Plugins/Runtime/GameFeatures/Source/GameFeatures/Public/GameFeatureVersePathMapperCommandlet.h:171` |
| `UGameFeaturesEditorSettings` | `/Script/GameFeaturesEditor.GameFeaturesEditorSettings` |  | UDeveloperSettings |  | `Plugins/Runtime/GameFeatures/Source/GameFeaturesEditor/Private/GameFeaturesEditorSettings.h:64` |
| `UGeometryCacheExporterUSDOptions` | `/Script/USDExporter.GeometryCacheExporterUSDOptions` |  | UObject |  | `Plugins/Importers/USDImporter/Source/USDExporter/Public/GeometryCacheExporterUSDOptions.h:16` |
| `UGeometryCacheThumbnailRenderer` | `/Script/GeometryCacheEd.GeometryCacheThumbnailRenderer` |  | UDefaultSizedThumbnailRenderer |  | `Plugins/Runtime/GeometryCache/Source/GeometryCacheEd/Classes/GeometryCacheThumbnailRenderer.h:19` |
| `UGeometryCollectionThumbnailRenderer` | `/Script/GeometryCollectionEditor.GeometryCollectionThumbnailRenderer` |  | UDefaultSizedThumbnailRenderer |  | `Plugins/Experimental/GeometryCollectionPlugin/Source/GeometryCollectionEditor/Public/GeometryCollection/GeometryCollectionThumbnailRenderer.h:19` |
| `UGroomActorFactory` | `/Script/HairStrandsEditor.GroomActorFactory` |  | UActorFactory |  | `Plugins/Runtime/HairStrands/Source/HairStrandsEditor/Public/GroomActorFactory.h:14` |
| `UGroomAssetThumbnailRenderer` | `/Script/HairStrandsEditor.GroomAssetThumbnailRenderer` |  | UDefaultSizedThumbnailRenderer |  | `Plugins/Runtime/HairStrands/Source/HairStrandsEditor/Private/GroomAssetThumbnailRenderer.h:12` |
| `UGroomBindingAssetThumbnailRenderer` | `/Script/HairStrandsEditor.GroomBindingAssetThumbnailRenderer` |  | UDefaultSizedThumbnailRenderer |  | `Plugins/Runtime/HairStrands/Source/HairStrandsEditor/Private/GroomBindingAssetThumbnailRenderer.h:13` |
| `UHLODBuilder` | `/Script/Engine.HLODBuilder` | Abstract | UObject | TSubclassOf<UHLODInstancedStaticMeshComponent> HLODInstancedStaticMeshComponentClass; TSubclassOf<UHLODInstancedSkinnedMeshComponent> HLODInstancedSkinnedMeshComponentClass | `Source/Runtime/Engine/Public/WorldPartition/HLOD/HLODBuilder.h:119` |
| `UHLODRebuildPolicy` | `/Script/Engine.HLODRebuildPolicy` | Abstract | UObject | TArray<FSoftObjectPath> HLODRebuildPolicies | `Source/Runtime/Engine/Public/WorldPartition/HLOD/HLODRebuildPolicy.h:41` |
| `UHLODRebuildPolicyImageCompare` | `/Script/WorldPartitionHLODUtilities.HLODRebuildPolicyImageCompare` |  | UHLODRebuildPolicy | uint32 MaxImageSize; uint32 WarmupFrameCount; float CaptureImageMargin; float MaximumLocalError; float MaximumGlobalError | `Plugins/Editor/WorldPartitionHLODUtilities/Source/Public/WorldPartition/HLOD/RebuildPolicies/HLODRebuildPolicyImageCompare.h:116` |
| `UHairCardGeneratorEditorSettings` | `/Script/HairCardGeneratorEditor.HairCardGeneratorEditorSettings` |  | UObject | FString HairCardAssetNameFormat; FString HairCardAssetPathFormat | `Plugins/Experimental/HairCardGenerator/Source/HairCardGeneratorEditor/Private/HairCardGeneratorEditorSettings.h:13` |
| `UHairCardGeneratorGroupSettings` | `/Script/HairCardGeneratorEditor.HairCardGeneratorGroupSettings` |  | UObject |  | `Plugins/Experimental/HairCardGenerator/Source/HairCardGeneratorEditor/Private/HairCardGeneratorPluginSettings.h:360` |
| `UHairCardGeneratorPluginSettings` | `/Script/HairCardGeneratorEditor.HairCardGeneratorPluginSettings` |  | UHairCardGenerationSettings |  | `Plugins/Experimental/HairCardGenerator/Source/HairCardGeneratorEditor/Private/HairCardGeneratorPluginSettings.h:121` |
| `UIKRetargeterThumbnailRenderer` | `/Script/IKRigEditor.IKRetargeterThumbnailRenderer` |  | UDefaultSizedThumbnailRenderer |  | `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/IKRetargeterThumbnailRenderer.h:37` |
| `UIKRigThumbnailRenderer` | `/Script/IKRigEditor.IKRigThumbnailRenderer` |  | USkeletalMeshThumbnailRenderer |  | `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RigEditor/IKRigThumbnailRenderer.h:13` |
| `ULevelEditor2DSettings` | `/Script/UnrealEd.LevelEditor2DSettings` |  | UDeveloperSettings |  | `Source/Editor/UnrealEd/Public/Settings/EditorProjectSettings.h:168` |
| `ULevelEditorProjectSettings` | `/Script/UnrealEd.LevelEditorProjectSettings` |  | UDeveloperSettings |  | `Source/Editor/UnrealEd/Public/Settings/EditorProjectSettings.h:200` |
| `ULevelExporterUSDOptions` | `/Script/USDExporter.LevelExporterUSDOptions` |  | UObject |  | `Plugins/Importers/USDImporter/Source/USDExporter/Public/LevelExporterUSDOptions.h:95` |
| `ULevelInstanceActorFactory` | `/Script/LevelInstanceEditor.LevelInstanceActorFactory` |  | UActorFactory |  | `Source/Editor/LevelInstanceEditor/Private/LevelInstanceActorFactory.h:10` |
| `ULevelInstanceEditorSettings` | `/Script/LevelInstanceEditor.LevelInstanceEditorSettings` |  | UDeveloperSettings |  | `Source/Editor/LevelInstanceEditor/Public/LevelInstanceEditorSettings.h:13` |
| `ULevelSequenceExporterUsdOptions` | `/Script/USDExporter.LevelSequenceExporterUsdOptions` |  | UObject |  | `Plugins/Importers/USDImporter/Source/USDExporter/Public/LevelSequenceExporterUSDOptions.h:18` |
| `ULevelThumbnailRenderer` | `/Script/UnrealEd.LevelThumbnailRenderer` |  | UDefaultSizedThumbnailRenderer |  | `Source/Editor/UnrealEd/Classes/ThumbnailRendering/LevelThumbnailRenderer.h:21` |
| `ULiveLinkFaceSourceDefaults` | `/Script/LiveLinkFaceSource.LiveLinkFaceSourceDefaults` |  | UObject |  | `Plugins/MetaHuman/MetaHumanLiveLink/Source/LiveLinkFaceSource/Public/LiveLinkFaceSourceDefaults.h:11` |
| `ULiveLinkHubEditorSettings` | `/Script/LiveLinkHubEditor.LiveLinkHubEditorSettings` |  | UObject |  | `Plugins/Animation/LiveLinkHub/Source/LiveLinkHubEditor/Private/LiveLinkHubEditorSettings.h:12` |
| `ULocalProfiles` | `/Script/AdvancedPreviewScene.LocalProfiles` |  | UObject |  | `Source/Editor/AdvancedPreviewScene/Public/AssetViewerSettings.h:309` |
| `ULocalizationSettings` | `/Script/Localization.LocalizationSettings` |  | UObject |  | `Source/Developer/Localization/Public/LocalizationSettings.h:22` |
| `UMaterialAssetSettings` | `/Script/MegascansPlugin.MaterialAssetSettings` |  | UObject | FString MasterMaterial3d; FString MasterMaterialSurface; FString MasterMaterialPlant | `Plugins/Bridge/Source/MegascansPlugin/Public/MSSettings.h:54` |
| `UMaterialBlendSettings` | `/Script/MegascansPlugin.MaterialBlendSettings` |  | UObject | FString BlendedMaterialName; FDirectoryPath BlendedMaterialPath | `Plugins/Bridge/Source/MegascansPlugin/Public/MSSettings.h:36` |
| `UMaterialEditorValidationSubsystem` | `/Script/MaterialEditor.MaterialEditorValidationSubsystem` |  | UEditorSubsystem |  | `Source/Editor/MaterialEditor/Public/MaterialEditorValidation.h:32` |
| `UMaterialExporterUSDOptions` | `/Script/USDExporter.MaterialExporterUSDOptions` |  | UObject |  | `Plugins/Importers/USDImporter/Source/USDExporter/Public/MaterialExporterUSDOptions.h:17` |
| `UMaterialFunctionThumbnailRenderer` | `/Script/UnrealEd.MaterialFunctionThumbnailRenderer` |  | UDefaultSizedThumbnailRenderer |  | `Source/Editor/UnrealEd/Classes/ThumbnailRendering/MaterialFunctionThumbnailRenderer.h:18` |
| `UMaterialInstanceThumbnailRenderer` | `/Script/UnrealEd.MaterialInstanceThumbnailRenderer` |  | UDefaultSizedThumbnailRenderer |  | `Source/Editor/UnrealEd/Classes/ThumbnailRendering/MaterialInstanceThumbnailRenderer.h:18` |
| `UMaterialLayerUsageCommandlet` | `/Script/UnrealEd.MaterialLayerUsageCommandlet` |  | UCommandlet |  | `Source/Editor/UnrealEd/Classes/Commandlets/MaterialLayerUsageCommandlet.h:9` |
| `UMaterialMergeOptions` | `/Script/MaterialBaking.MaterialMergeOptions` |  | UObject |  | `Source/Developer/MaterialBaking/Public/MaterialOptions.h:115` |
| `UMaterialOptions` | `/Script/MaterialBaking.MaterialOptions` |  | UObject |  | `Source/Developer/MaterialBaking/Public/MaterialOptions.h:63` |
| `UMaterialPresetsSettings` | `/Script/MegascansPlugin.MaterialPresetsSettings` |  | UObject |  | `Plugins/Bridge/Source/MegascansPlugin/Public/MSSettings.h:74` |
| `UMaterialValidationConfig` | `/Script/MaterialValidation.MaterialValidationConfig` |  | UDeveloperSettings |  | `Plugins/Editor/MaterialValidation/Source/Private/MaterialValidationConfig.h:13` |
| `UMediaFrameworkEditorCaptureSettings` | `/Script/MediaFrameworkUtilitiesEditor.MediaFrameworkEditorCaptureSettings` |  | UMediaFrameworkWorldSettingsAssetUserData |  | `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/CaptureTab/SMediaFrameworkCapture.h:48` |
| `UMediaFrameworkWorldSettingsAssetUserData` | `/Script/MediaFrameworkUtilitiesEditor.MediaFrameworkWorldSettingsAssetUserData` |  | UAssetUserData |  | `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/MediaFrameworkWorldSettingsAssetUserData.h:140` |
| `UMediaSequenceRecorderSettings` | `/Script/MediaCompositingEditor.MediaSequenceRecorderSettings` |  | UObject | bool bRecordMediaPlayerEnabled; FString MediaPlayerSubDirectory | `Plugins/Media/MediaCompositing/Source/MediaCompositingEditor/Private/Sequencer/MediaSequenceRecorderExtender.h:22` |
| `UMegascansSettings` | `/Script/MegascansPlugin.MegascansSettings` |  | UObject | bool bCreateFoliage; bool bApplyToSelection | `Plugins/Bridge/Source/MegascansPlugin/Public/MSSettings.h:9` |
| `UMeshTerrainModeCustomizationSettings` | `/Script/MeshTerrainMode.MeshTerrainModeCustomizationSettings` |  | UDeveloperSettings | FLinearColor UnselectedColor; FLinearColor HoverOverSelectedColor; FLinearColor HoverOverUnselectedColor; FLinearColor GeometrySelectedColor; FLinearColor GeometrySoftSelectedColor; FVector2f DetailsOverlaySize | `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/MeshTerrainModeSettings.h:291` |
| `UMeshTerrainModeSettings` | `/Script/MeshTerrainMode.MeshTerrainModeSettings` |  | UDeveloperSettings | FString RestrictiveModeAutoGeneratedAssetPath | `Plugins/Experimental/MeshTerrainMode/Source/MeshTerrainMode/Private/MeshTerrainModeSettings.h:60` |
| `UMetaHumanCharacterEditorWardrobeSettings` | `/Script/MetaHumanCharacterEditor.MetaHumanCharacterEditorWardrobeSettings` | DefaultConfig | UObject | TArray<FMetaHumanCharacterAssetsSection> WardrobeSections; TMap<FName, FText> SlotNameToCategoryNameMap; TMap<EMetaHumanCharacterEyelashesType, FSoftObjectPath> EyelashesTypeToAssetPath; TArray<FDirectoryPath> PresetDirectories | `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Public/MetaHumanCharacterEditorWardrobeSettings.h:16` |
| `UMetaHumanInstanceActorFactory` | `/Script/MetaHumanCharacterPaletteEditor.MetaHumanInstanceActorFactory` |  | UActorFactory |  | `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPaletteEditor/Private/MetaHumanInstanceActorFactory.h:17` |
| `UMetaHumanVideoLiveLinkSettings` | `/Script/MetaHumanLocalLiveLinkSource.MetaHumanVideoLiveLinkSettings` |  | UObject |  | `Plugins/MetaHuman/MetaHumanLiveLink/Source/MetaHumanLocalLiveLinkSource/Public/MetaHumanVideoLiveLinkSettings.h:13` |
| `UModelingToolsEditorModeSettings` | `/Script/ModelingToolsEditorMode.ModelingToolsEditorModeSettings` |  | UDeveloperSettings | FString RestrictiveModeAutoGeneratedAssetPath | `Plugins/Editor/ModelingToolsEditorMode/Source/ModelingToolsEditorMode/Public/ModelingToolsEditorModeSettings.h:59` |
| `UModelingToolsModeCustomizationSettings` | `/Script/ModelingToolsEditorMode.ModelingToolsModeCustomizationSettings` |  | UDeveloperSettings | FLinearColor UnselectedColor; FLinearColor HoverOverSelectedColor; FLinearColor HoverOverUnselectedColor; FLinearColor GeometrySelectedColor; FLinearColor GeometrySoftSelectedColor | `Plugins/Editor/ModelingToolsEditorMode/Source/ModelingToolsEditorMode/Public/ModelingToolsEditorModeSettings.h:296` |
| `UMoviePipelinePIEExecutorSettings` | `/Script/MovieRenderPipelineEditor.MoviePipelinePIEExecutorSettings` |  | UDeveloperSettings |  | `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Private/MoviePipelinePIEExecutorSettings.h:11` |
| `UMovieRenderPipelineProjectSettings` | `/Script/MovieRenderPipelineEditor.MovieRenderPipelineProjectSettings` |  | UObject |  | `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineEditor/Public/MovieRenderPipelineSettings.h:19` |
| `UMutableValidationSettings` | `/Script/MutableValidation.MutableValidationSettings` |  | UObject |  | `Plugins/Mutable/Source/MutableValidation/Private/MuV/MutableValidationSettings.h:7` |
| `UNiagaraDumpByteCodeCommandlet` | `/Script/NiagaraEditor.NiagaraDumpByteCodeCommandlet` |  | UCommandlet |  | `Plugins/FX/Niagara/Source/NiagaraEditor/Public/Commandlets/NiagaraDumpBytecodeCommandlet.h:13` |
| `UNiagaraDumpModuleInfoCommandlet` | `/Script/NiagaraEditor.NiagaraDumpModuleInfoCommandlet` |  | UCommandlet |  | `Plugins/FX/Niagara/Source/NiagaraEditor/Public/Commandlets/NiagaraDumpModuleInfoCommandlet.h:12` |
| `UNiagaraScriptValidationCommandlet` | `/Script/NiagaraEditor.NiagaraScriptValidationCommandlet` |  | UCommandlet |  | `Plugins/FX/Niagara/Source/NiagaraEditor/Public/Commandlets/NiagaraScriptValidationCommandlet.h:12` |
| `UNiagaraStatelessAuditCommandlet` | `/Script/NiagaraEditor.NiagaraStatelessAuditCommandlet` |  | UCommandlet |  | `Plugins/FX/Niagara/Source/NiagaraEditor/Public/Commandlets/NiagaraStatelessAuditCommandlet.h:12` |
| `UNiagaraSystemAuditCommandlet` | `/Script/NiagaraEditor.NiagaraSystemAuditCommandlet` |  | UCommandlet |  | `Plugins/FX/Niagara/Source/NiagaraEditor/Public/Commandlets/NiagaraSystemAuditCommandlet.h:10` |
| `UNiagaraTraversalCacheAuditCommandlet` | `/Script/NiagaraEditor.NiagaraTraversalCacheAuditCommandlet` |  | UCommandlet |  | `Plugins/FX/Niagara/Source/NiagaraEditor/Public/Commandlets/NiagaraTraversalCacheAuditCommandlet.h:17` |
| `UNiagaraValidationRule` | `/Script/Niagara.NiagaraValidationRule` |  | UObject | bool bIsConfigDisabled | `Plugins/FX/Niagara/Source/Niagara/Classes/NiagaraValidationRule.h:67` |
| `UOnlinePIEConfig` | `/Script/OnlineSubsystemUtils.OnlinePIEConfig` |  | UObject |  | `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Private/OnlinePIEConfig.h:9` |
| `UOodleNetworkTrainerCommandlet` | `/Script/OodleNetworkHandlerComponent.OodleNetworkTrainerCommandlet` |  | UCommandlet |  | `Plugins/Compression/OodleNetwork/Source/Classes/OodleNetworkTrainerCommandlet.h:61` |
| `UPCGEditorProjectSettings` | `/Script/PCGEditor.PCGEditorProjectSettings` |  | UDeveloperSettings | bool bAutoRefreshGPUStaticMeshSpawners | `Plugins/PCG/Source/PCGEditor/Public/PCGEditorSettings.h:33` |
| `UPCGToolsetSettings` | `/Script/PCGToolset.PCGToolsetSettings` | DefaultConfig | UDeveloperSettings | TArray<FDirectoryPath> SubgraphDirectories; TArray<FDirectoryPath> ExampleGraphDirectories; TArray<FDirectoryPath> InstantGraphDirectories | `Plugins/Experimental/Toolsets/PCGToolset/Source/PCGToolset/Public/PCGToolsetSettings.h:12` |
| `UPCGVolumeFactory` | `/Script/PCGEditor.PCGVolumeFactory` |  | UActorFactoryBoxVolume |  | `Plugins/PCG/Source/PCGEditor/Private/PCGVolumeFactory.h:12` |
| `UPaperImporterSettings` | `/Script/Paper2DEditor.PaperImporterSettings` |  | UObject |  | `Plugins/2D/Paper2D/Source/Paper2DEditor/Classes/PaperImporterSettings.h:52` |
| `UParametricRetessellateActionOptions` | `/Script/ParametricSurfaceExtension.ParametricRetessellateActionOptions` |  | UObject |  | `Plugins/Enterprise/DatasmithCADImporter/Source/ParametricSurfaceExtension/Public/ParametricRetessellateAction.h:31` |
| `UParticleSystemAuditCommandlet` | `/Script/UnrealEd.ParticleSystemAuditCommandlet` |  | UCommandlet |  | `Source/Editor/UnrealEd/Classes/Commandlets/ParticleSystemAuditCommandlet.h:10` |
| `UParticleSystemThumbnailRenderer` | `/Script/UnrealEd.ParticleSystemThumbnailRenderer` |  | UTextureThumbnailRenderer |  | `Source/Editor/UnrealEd/Classes/ThumbnailRendering/ParticleSystemThumbnailRenderer.h:18` |
| `UPhysicsAssetThumbnailRenderer` | `/Script/UnrealEd.PhysicsAssetThumbnailRenderer` |  | UDefaultSizedThumbnailRenderer |  | `Source/Editor/UnrealEd/Classes/ThumbnailRendering/PhysicsAssetThumbnailRenderer.h:13` |
| `UPinTypeSelectorFilter` | `/Script/KismetWidgets.PinTypeSelectorFilter` |  | UObject |  | `Source/Editor/KismetWidgets/Public/PinTypeSelectorFilter.h:10` |
| `UPlasticSourceControlProjectSettings` | `/Script/PlasticSourceControl.PlasticSourceControlProjectSettings` |  | UDeveloperSettings |  | `Plugins/Developer/PlasticSourceControl/Source/PlasticSourceControl/Private/PlasticSourceControlProjectSettings.h:10` |
| `UProjectUserAssetTagSettings` | `/Script/UserAssetTagsEditor.ProjectUserAssetTagSettings` | DefaultConfig | UDeveloperSettings | TMap<FSoftClassPath, FPerTypeFavoriteUserAssetTags> UserAssetTagsPerType | `Source/Editor/UserAssetTagsEditor/Private/Settings/ProjectUserAssetTagSettings.h:13` |
| `URenderResourceViewerSettings` | `/Script/RenderResourceViewer.RenderResourceViewerSettings` | DefaultConfig | UDeveloperSettings | TArray<FRenderResourceViewerTreemapFilter> Filters | `Source/Editor/RenderResourceViewer/Public/RenderResourceViewerSettings.h:21` |
| `URigVMProjectSettings` | `/Script/RigVM.RigVMProjectSettings` |  | UDeveloperSettings |  | `Plugins/Runtime/RigVM/Source/RigVM/Public/RigVMSettings.h:95` |
| `UScreenshotComparisonCommandlet` | `/Script/AutomationUtilsEditor.ScreenshotComparisonCommandlet` |  | UCommandlet |  | `Plugins/Experimental/AutomationUtils/Source/AutomationUtilsEditor/Public/ScreenshotComparisonCommandlet.h:9` |
| `UScriptableToolsModeCustomizationSettings` | `/Script/ScriptableToolsEditorMode.ScriptableToolsModeCustomizationSettings` |  | UDeveloperSettings |  | `Plugins/Editor/ScriptableToolsEditorMode/Source/ScriptableToolsEditorMode/Public/ScriptableToolsEditorModeSettings.h:14` |
| `USearchProjectSettings` | `/Script/AssetSearch.SearchProjectSettings` |  | UDeveloperSettings |  | `Plugins/Editor/AssetSearch/Source/Private/Settings/SearchProjectSettings.h:20` |
| `USequenceRecorderSettings` | `/Script/SequenceRecorder.SequenceRecorderSettings` |  | UObject | bool bCreateLevelSequence; bool bImmersiveMode; float SequenceLength; float RecordingDelay; bool bAllowLooping; float GlobalTimeDilation; bool bIgnoreTimeDilation; FString AnimationSubDirectory; EAudioRecordingMode RecordAudio; float AudioGain; bool bSplitAudioChannelsIntoSeparateTracks; bool bReplaceRecordedAudio; FText AudioTrackName; FString AudioSubDirectory; bool bRecordNearbySpawnedActors; float NearbyActorRecordingProximity; bool bRecordWorldSettingsActor; bool bReduceKeys; bool bAutoSaveAsset; FSequenceRecorderActorFilter ActorFilter; FAnimationRecordingSettings DefaultAnimationSettings; bool bRecordSequencerSpawnedActors; TArray<FPropertiesToRecordForClass> ClassesAndPropertiesToRecord; TArray<FPropertiesToRecordForActorClass> ActorsAndPropertiesToRecord; TArray<FSettingsForActorClass> PerActorSettings | `Source/Editor/SequenceRecorder/Public/SequenceRecorderSettings.h:85` |
| `USharedProfiles` | `/Script/AdvancedPreviewScene.SharedProfiles` |  | UObject | EProfileConfigVersion Version | `Source/Editor/AdvancedPreviewScene/Public/AssetViewerSettings.h:319` |
| `USkeletalMeshExporterUSDOptions` | `/Script/USDExporter.SkeletalMeshExporterUSDOptions` |  | UObject |  | `Plugins/Importers/USDImporter/Source/USDExporter/Public/SkeletalMeshExporterUSDOptions.h:16` |
| `USkeletalMeshThumbnailRenderer` | `/Script/UnrealEd.SkeletalMeshThumbnailRenderer` |  | UDefaultSizedThumbnailRenderer |  | `Source/Editor/UnrealEd/Classes/ThumbnailRendering/SkeletalMeshThumbnailRenderer.h:22` |
| `USkeletonThumbnailRenderer` | `/Script/UnrealEd.SkeletonThumbnailRenderer` |  | UDefaultSizedThumbnailRenderer |  | `Source/Editor/UnrealEd/Classes/ThumbnailRendering/SkeletonThumbnailRenderer.h:22` |
| `USlateBrushThumbnailRenderer` | `/Script/UnrealEd.SlateBrushThumbnailRenderer` |  | UDefaultSizedThumbnailRenderer |  | `Source/Editor/UnrealEd/Classes/ThumbnailRendering/SlateBrushThumbnailRenderer.h:20` |
| `USourceControlPreferences` | `/Script/SourceControl.SourceControlPreferences` |  | UDeveloperSettings |  | `Source/Developer/SourceControl/Public/SourceControlPreferences.h:22` |
| `USourceControlSettings` | `/Script/SourceControlWindows.SourceControlSettings` |  | UObject |  | `Source/Editor/SourceControlWindows/Private/SourceControlSettings.h:9` |
| `UStaticMeshExporterUSDOptions` | `/Script/USDExporter.StaticMeshExporterUSDOptions` |  | UObject |  | `Plugins/Importers/USDImporter/Source/USDExporter/Public/StaticMeshExporterUSDOptions.h:16` |
| `UStaticMeshThumbnailRenderer` | `/Script/UnrealEd.StaticMeshThumbnailRenderer` |  | UDefaultSizedThumbnailRenderer |  | `Source/Editor/UnrealEd/Classes/ThumbnailRendering/StaticMeshThumbnailRenderer.h:18` |
| `USubmitToolEditorSettings` | `/Script/SubmitToolEditor.SubmitToolEditorSettings` |  | UDeveloperSettings |  | `Plugins/Experimental/SubmitToolEditor/Source/SubmitToolEditor/Private/SubmitToolEditorSettings.h:38` |
| `USubstrateCommandlet` | `/Script/UnrealEd.SubstrateCommandlet` |  | UCommandlet |  | `Source/Editor/UnrealEd/Classes/Commandlets/SubstrateCommandlet.h:10` |
| `USummarizeTraceCommandlet` | `/Script/UnrealEd.SummarizeTraceCommandlet` |  | UCommandlet |  | `Source/Editor/UnrealEd/Classes/Commandlets/SummarizeTraceCommandlet.h:14` |
| `USummarizeTraceEditorWorkflowsCommandlet` | `/Script/UnrealEd.SummarizeTraceEditorWorkflowsCommandlet` |  | UCommandlet |  | `Source/Editor/UnrealEd/Classes/Commandlets/SummarizeTraceEditorWorkflowsCommandlet.h:9` |
| `USwitchActorFactory` | `/Script/VariantManagerContentEditor.SwitchActorFactory` |  | UActorFactory |  | `Plugins/Enterprise/VariantManagerContent/Source/VariantManagerContentEditor/Public/SwitchActorFactory.h:12` |
| `UTextAssetCommandlet` | `/Script/UnrealEd.TextAssetCommandlet` |  | UCommandlet |  | `Source/Editor/UnrealEd/Classes/Commandlets/TextAssetCommandlet.h:25` |
| `UTextFilterKeyValueHandlers` | `/Script/ContentBrowser.TextFilterKeyValueHandlers` |  | UObject |  | `Source/Editor/ContentBrowser/Private/TextFilterKeyValueHandlers.h:33` |
| `UTextFilterValueHandlers` | `/Script/ContentBrowser.TextFilterValueHandlers` |  | UObject |  | `Source/Editor/ContentBrowser/Private/TextFilterValueHandlers.h:18` |
| `UTextureImportSettings` | `/Script/TextureUtilitiesCommon.TextureImportSettings` |  | UDeveloperSettings |  | `Source/Runtime/TextureUtilitiesCommon/Public/TextureImportSettings.h:50` |
| `UThumbnailManager` | `/Script/UnrealEd.ThumbnailManager` |  | UObject |  | `Source/Editor/UnrealEd/Classes/ThumbnailRendering/ThumbnailManager.h:92` |
| `UToolPresetProjectSettings` | `/Script/ToolPresetEditor.ToolPresetProjectSettings` |  | UDeveloperSettings |  | `Plugins/Experimental/ToolPresets/Source/ToolPresetEditor/Public/ToolPresetSettings.h:47` |
| `UTutorialSettings` | `/Script/IntroTutorials.TutorialSettings` |  | UObject | TArray<FTutorialCategory> Categories; FSoftClassPath StartupTutorial | `Plugins/Editor/GuidedTutorials/Source/IntroTutorials/Private/TutorialSettings.h:13` |
| `UUAFAnimGraphEditorProjectSettings` | `/Script/UAFAnimGraphEditor.UAFAnimGraphEditorProjectSettings` |  | UDeveloperSettings | int32 MaxGraphUpdateLoopCount | `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraphEditor/Private/Settings/UAFAnimGraphEditorProjectSettings.h:13` |
| `UUAFEditorProjectSettings` | `/Script/UAFEditor.UAFEditorProjectSettings` |  | UDeveloperSettings |  | `Plugins/Experimental/UAF/UAF/Source/UAFEditor/Private/Settings/UAFEditorProjectSettings.h:11` |
| `UUMGEditorProjectSettings` | `/Script/UMGEditor.UMGEditorProjectSettings` |  | UWidgetEditingProjectSettings |  | `Source/Editor/UMGEditor/Public/UMGEditorProjectSettings.h:26` |
| `UUnrealEdOptions` | `/Script/UnrealEd.UnrealEdOptions` |  | UObject |  | `Source/Editor/UnrealEd/Classes/Preferences/UnrealEdOptions.h:84` |
| `UValkyrieMetaData` | `/Script/Engine.ValkyrieMetaData` | DefaultConfig | UObject |  | `Source/Runtime/Engine/Public/ObjectEditorUtils.h:208` |
| `UVolumeTextureThumbnailRenderer` | `/Script/UnrealEd.VolumeTextureThumbnailRenderer` |  | UDefaultSizedThumbnailRenderer |  | `Source/Editor/UnrealEd/Classes/ThumbnailRendering/VolumeTextureThumbnailRenderer.h:19` |
| `UWaterBodyActorFactory` | `/Script/WaterEditor.WaterBodyActorFactory` | Abstract | UActorFactory |  | `Plugins/Experimental/Water/Source/Editor/Private/WaterBodyActorFactory.h:10` |
| `UWaterBodyCustomActorFactory` | `/Script/WaterEditor.WaterBodyCustomActorFactory` |  | UWaterBodyActorFactory |  | `Plugins/Experimental/Water/Source/Editor/Private/WaterBodyActorFactory.h:53` |
| `UWaterBodyIslandActorFactory` | `/Script/WaterEditor.WaterBodyIslandActorFactory` |  | UActorFactory |  | `Plugins/Experimental/Water/Source/Editor/Private/WaterBodyIslandActorFactory.h:7` |
| `UWaterBodyLakeActorFactory` | `/Script/WaterEditor.WaterBodyLakeActorFactory` |  | UWaterBodyActorFactory |  | `Plugins/Experimental/Water/Source/Editor/Private/WaterBodyActorFactory.h:43` |
| `UWaterBodyOceanActorFactory` | `/Script/WaterEditor.WaterBodyOceanActorFactory` |  | UWaterBodyActorFactory |  | `Plugins/Experimental/Water/Source/Editor/Private/WaterBodyActorFactory.h:33` |
| `UWaterBodyRiverActorFactory` | `/Script/WaterEditor.WaterBodyRiverActorFactory` |  | UWaterBodyActorFactory |  | `Plugins/Experimental/Water/Source/Editor/Private/WaterBodyActorFactory.h:23` |
| `UWaterBrushManagerFactory` | `/Script/WaterEditor.WaterBrushManagerFactory` |  | UActorFactory |  | `Plugins/Experimental/Water/Source/Editor/Private/WaterBrushManagerFactory.h:7` |
| `UWaterZoneActorFactory` | `/Script/WaterEditor.WaterZoneActorFactory` |  | UActorFactory |  | `Plugins/Experimental/Water/Source/Editor/Private/WaterZoneActorFactory.h:7` |
| `UWidgetEditingProjectSettings` | `/Script/UMGEditor.WidgetEditingProjectSettings` | Abstract | UDeveloperSettings |  | `Source/Editor/UMGEditor/Public/WidgetEditingProjectSettings.h:124` |
| `UWorldBookmarkEditorSettings` | `/Script/WorldBookmark.WorldBookmarkEditorSettings` | DefaultConfig | UDeveloperSettings |  | `Source/Editor/WorldBookmark/Private/WorldBookmark/WorldBookmarkEditorSettings.h:12` |
| `UWorldThumbnailRenderer` | `/Script/UnrealEd.WorldThumbnailRenderer` |  | UDefaultSizedThumbnailRenderer |  | `Source/Editor/UnrealEd/Classes/ThumbnailRendering/WorldThumbnailRenderer.h:19` |

## config=Game (114)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `ACharacter` | `/Script/Engine.Character` |  | APawn |  | `Source/Runtime/Engine/Classes/GameFramework/Character.h:337` |
| `ADebugCameraController` | `/Script/Engine.DebugCameraController` |  | APlayerController |  | `Source/Runtime/Engine/Classes/Engine/DebugCameraController.h:23` |
| `ADebugCameraHUD` | `/Script/Engine.DebugCameraHUD` |  | AHUD |  | `Source/Runtime/Engine/Classes/Engine/DebugCameraHUD.h:13` |
| `ADefaultPawn` | `/Script/Engine.DefaultPawn` |  | APawn |  | `Source/Runtime/Engine/Classes/GameFramework/DefaultPawn.h:24` |
| `AGameModeBase` | `/Script/Engine.GameModeBase` |  | AInfo | EReplicationSystem GameNetDriverReplicationSystem | `Source/Runtime/Engine/Classes/GameFramework/GameModeBase.h:46` |
| `AGameNetworkManager` | `/Script/Engine.GameNetworkManager` |  | AInfo | G float BadPacketLossThreshold; G float SeverePacketLossThreshold; G int32 BadPingThreshold; G int32 SeverePingThreshold; G float MoveRepSize; G float MAXPOSITIONERRORSQUARED; G float MAXNEARZEROVELOCITYSQUARED; G float CLIENTADJUSTUPDATECOST; G float MAXCLIENTUPDATEINTERVAL; G float MaxClientForcedUpdateDuration; G float ServerForcedUpdateHitchThreshold; G float ServerForcedUpdateHitchCooldown; G float MaxMoveDeltaTime; G float MaxClientSmoothingDeltaTime; G float ClientNetSendMoveDeltaTime; G float ClientNetSendMoveDeltaTimeThrottled; G float ClientNetSendMoveDeltaTimeStationary; G int32 ClientNetSendMoveThrottleAtNetSpeed; G int32 ClientNetSendMoveThrottleOverPlayerCount; G float ClientErrorUpdateRateLimit; G float ClientNetCamUpdateDeltaTime; G float ClientNetCamUpdatePositionLimit; G bool ClientAuthorativePosition; G bool bMovementTimeDiscrepancyDetection; G bool bMovementTimeDiscrepancyResolution; G float MovementTimeDiscrepancyMaxTimeMargin; G float MovementTimeDiscrepancyMinTimeMargin; G float MovementTimeDiscrepancyResolutionRate; G float MovementTimeDiscrepancyDriftAllowance; G bool bMovementTimeDiscrepancyForceCorrectionsDuringResolution | `Source/Runtime/Engine/Classes/GameFramework/GameNetworkManager.h:26` |
| `AGameSession` | `/Script/Engine.GameSession` |  | AInfo |  | `Source/Runtime/Engine/Classes/GameFramework/GameSession.h:26` |
| `AGameStateBase` | `/Script/Engine.GameStateBase` |  | AInfo |  | `Source/Runtime/Engine/Classes/GameFramework/GameStateBase.h:31` |
| `AGameplayAbilityTargetActor_Trace` | `/Script/GameplayAbilities.GameplayAbilityTargetActor_Trace` | Abstract | AGameplayAbilityTargetActor |  | `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/GameplayAbilityTargetActor_Trace.h:21` |
| `AHUD` | `/Script/Engine.HUD` |  | AActor |  | `Source/Runtime/Engine/Classes/GameFramework/HUD.h:35` |
| `ALobbyBeaconPlayerState` | `/Script/Lobby.LobbyBeaconPlayerState` |  | AInfo |  | `Plugins/Online/OnlineFramework/Source/Lobby/Public/LobbyBeaconPlayerState.h:18` |
| `ALobbyBeaconState` | `/Script/Lobby.LobbyBeaconState` |  | AInfo |  | `Plugins/Online/OnlineFramework/Source/Lobby/Public/LobbyBeaconState.h:170` |
| `AMassEntityTestFarmPlot` | `/Script/MassEntityTestSuite.MassEntityTestFarmPlot` |  | AActor |  | `Source/Developer/MassEntityTestSuite/Public/MassEntityTestFarmPlot.h:184` |
| `AParticleEventManager` | `/Script/Engine.ParticleEventManager` |  | AActor |  | `Source/Runtime/Engine/Classes/Particles/ParticleEventManager.h:13` |
| `APawn` | `/Script/Engine.Pawn` |  | AActor, INavAgentInterface |  | `Source/Runtime/Engine/Classes/GameFramework/Pawn.h:42` |
| `APlayerController` | `/Script/Engine.PlayerController` |  | AController, IWorldPartitionStreamingSourceProvider |  | `Source/Runtime/Engine/Classes/GameFramework/PlayerController.h:261` |
| `ASpectatorPawn` | `/Script/Engine.SpectatorPawn` |  | ADefaultPawn |  | `Source/Runtime/Engine/Classes/GameFramework/SpectatorPawn.h:15` |
| `AStereoCapturePawn` | `/Script/PanoramicCapture.StereoCapturePawn` |  | ADefaultPawn |  | `Plugins/Experimental/PanoramicCapture/Source/PanoramicCapture/Public/StereoCapturePawn.h:51` |
| `AWheeledVehiclePawn` | `/Script/ChaosVehicles.WheeledVehiclePawn` |  | APawn |  | `Plugins/Experimental/ChaosVehiclesPlugin/Source/ChaosVehicles/Public/WheeledVehiclePawn.h:19` |
| `UAIPerceptionComponent` | `/Script/AIModule.AIPerceptionComponent` |  | UActorComponent |  | `Source/Runtime/AIModule/Classes/Perception/AIPerceptionComponent.h:207` |
| `UAIPerceptionStimuliSourceComponent` | `/Script/AIModule.AIPerceptionStimuliSourceComponent` |  | UActorComponent |  | `Source/Runtime/AIModule/Classes/Perception/AIPerceptionStimuliSourceComponent.h:14` |
| `UAIPerceptionSystem` | `/Script/AIModule.AIPerceptionSystem` |  | UAISubsystem |  | `Source/Runtime/AIModule/Classes/Perception/AIPerceptionSystem.h:29` |
| `UAISenseConfig` | `/Script/AIModule.AISenseConfig` |  | UObject |  | `Source/Runtime/AIModule/Classes/Perception/AISenseConfig.h:17` |
| `UAISenseEvent` | `/Script/AIModule.AISenseEvent` |  | UObject |  | `Source/Runtime/AIModule/Classes/Perception/AISenseEvent.h:12` |
| `UAISense_Hearing` | `/Script/AIModule.AISense_Hearing` |  | UAISense |  | `Source/Runtime/AIModule/Classes/Perception/AISense_Hearing.h:63` |
| `UAISense_Sight` | `/Script/AIModule.AISense_Sight` |  | UAISense |  | `Source/Runtime/AIModule/Classes/Perception/AISense_Sight.h:203` |
| `UAbilitySystemGlobals` | `/Script/GameplayAbilities.AbilitySystemGlobals` |  | UObject |  | `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/AbilitySystemGlobals.h:56` |
| `UAnimNotify_PlaySound` | `/Script/Engine.AnimNotify_PlaySound` |  | UAnimNotify | uint32 bPreviewIgnoreAttenuation:1 | `Source/Runtime/Engine/Classes/Animation/AnimNotifies/AnimNotify_PlaySound.h:15` |
| `UAssetManagerSettings` | `/Script/Engine.AssetManagerSettings` |  | UDeveloperSettings |  | `Source/Runtime/Engine/Classes/Engine/AssetManagerSettings.h:66` |
| `UAssetReferencingPolicySettings` | `/Script/AssetReferenceRestrictions.AssetReferencingPolicySettings` |  | UDeveloperSettings |  | `Plugins/Editor/AssetReferenceRestrictions/Source/AssetReferenceRestrictions/Public/AssetReferencingPolicySettings.h:179` |
| `UAssetToolsSettings` | `/Script/AssetTools.AssetToolsSettings` |  | UDeveloperSettings |  | `Source/Developer/AssetTools/Public/AssetToolsSettings.h:27` |
| `UAsyncMessageDeveloperSettings` | `/Script/AsyncMessageSystem.AsyncMessageDeveloperSettings` |  | UDeveloperSettings | bool bMessageQueueDebugEnabled; bool bTriggerDebugBreakpointWhenMessageQueued; bool bPrintScriptCallstackWhenMessageQueued; bool bShouldRecordQueueCallstackOnMessages; bool bEnabledDebuggingForAllQueuedMessages; TArray<FAsyncMessageId> EnabledDebugMessages; bool bEnableWorldSubsystem; bool bEnableWorldSubsystemInEditor | `Plugins/Experimental/AsyncMessageSystem/Source/AsyncMessageSystem/Private/AsyncMessageDeveloperSettings.h:10` |
| `UAttenuationVolumeComponent` | `/Script/AudioGameplayVolume.AttenuationVolumeComponent` |  | UAudioGameplayVolumeMutator |  | `Plugins/AudioGameplayVolume/Source/AudioGameplayVolume/Public/AttenuationVolumeComponent.h:38` |
| `UAudioGameplayComponent` | `/Script/AudioGameplay.AudioGameplayComponent` |  | UActorComponent |  | `Plugins/AudioGameplay/Source/AudioGameplay/Public/AudioGameplayComponent.h:13` |
| `UAudioGameplayVolumeComponent` | `/Script/AudioGameplayVolume.AudioGameplayVolumeComponent` |  | UAudioGameplayComponent |  | `Plugins/AudioGameplayVolume/Source/AudioGameplayVolume/Public/AudioGameplayVolumeComponent.h:28` |
| `UBTNode` | `/Script/AIModule.BTNode` | Abstract | UObject, IGameplayTaskOwnerInterface |  | `Source/Runtime/AIModule/Classes/BehaviorTree/BTNode.h:46` |
| `UBTTask_MoveDirectlyToward` | `/Script/AIModule.BTTask_MoveDirectlyToward` |  | UBTTask_MoveTo |  | `Source/Runtime/AIModule/Classes/BehaviorTree/Tasks/BTTask_MoveDirectlyToward.h:16` |
| `UBTTask_MoveTo` | `/Script/AIModule.BTTask_MoveTo` |  | UBTTask_BlackboardBase |  | `Source/Runtime/AIModule/Classes/BehaviorTree/Tasks/BTTask_MoveTo.h:35` |
| `UBTTask_RotateToFaceBBEntry` | `/Script/AIModule.BTTask_RotateToFaceBBEntry` |  | UBTTask_BlackboardBase |  | `Source/Runtime/AIModule/Classes/BehaviorTree/Tasks/BTTask_RotateToFaceBBEntry.h:17` |
| `UBinkMoviePlayerSettings` | `/Script/BinkMediaPlayer.BinkMoviePlayerSettings` |  | UObject |  | `Plugins/Media/BinkMedia/Source/BinkMediaPlayer/Private/BinkMoviePlayerSettings.h:61` |
| `UBuoyancyComponent` | `/Script/Water.BuoyancyComponent` |  | UActorComponent |  | `Plugins/Experimental/Water/Source/Runtime/Public/BuoyancyComponent.h:17` |
| `UCameraCalibrationSettings` | `/Script/CameraCalibrationCore.CameraCalibrationSettings` |  | UDeveloperSettings |  | `Plugins/VirtualProduction/CameraCalibrationCore/Source/CameraCalibrationCore/Public/CameraCalibrationSettings.h:22` |
| `UChatroom` | `/Script/Party.Chatroom` |  | UObject |  | `Plugins/Online/OnlineFramework/Source/Party/Public/Chatroom.h:32` |
| `UCommonInputPlatformSettings` | `/Script/CommonInput.CommonInputPlatformSettings` |  | UPlatformSettings |  | `Plugins/Runtime/CommonUI/Source/CommonInput/Public/CommonInputBaseTypes.h:215` |
| `UCommonInputSettings` | `/Script/CommonInput.CommonInputSettings` |  | UDeveloperSettings |  | `Plugins/Runtime/CommonUI/Source/CommonInput/Public/CommonInputSettings.h:24` |
| `UCommonLoadGuard` | `/Script/CommonUI.CommonLoadGuard` | DefaultConfig | UContentWidget | FSoftObjectPath SpinnerMaterialPath | `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonLoadGuard.h:150` |
| `UCommonUISettings` | `/Script/CommonUI.CommonUISettings` |  | UObject |  | `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonUISettings.h:32` |
| `UComposureGameSettings` | `/Script/Composure.ComposureGameSettings` |  | UObject | FSoftObjectPath StaticVideoPlateDebugImage; bool bSceneCapWarnOfMissingCam; FSoftObjectPath FallbackCompositingTexture | `Plugins/Compositing/Composure/Source/Composure/Private/ComposureConfigSettings.h:9` |
| `UConversationSettings` | `/Script/CommonConversationRuntime.ConversationSettings` | DefaultConfig | UDeveloperSettings |  | `Plugins/Experimental/CommonConversation/Source/CommonConversationRuntime/Public/ConversationSettings.h:15` |
| `UDataRegistrySettings` | `/Script/DataRegistry.DataRegistrySettings` |  | UDeveloperSettings |  | `Plugins/Runtime/DataRegistry/Source/DataRegistry/Public/DataRegistrySettings.h:16` |
| `UDaySequenceModifierComponent` | `/Script/DaySequence.DaySequenceModifierComponent` |  | USceneComponent , FDaySequenceModifierComponentTickableBase |  | `Plugins/Experimental/DaySequence/Source/DaySequence/Public/DaySequenceModifierComponent.h:137` |
| `UDisplayClusterMonitorSettings` | `/Script/DisplayClusterMonitor.DisplayClusterMonitorSettings` | DefaultConfig | UObject | float HeartbeatInterval; float UnresponsiveTimeThreshold; bool bAddNewObservablesToFront; int32 ViewportsInRow; bool bUseFixedViewportHeight; float FixedViewportHeight | `Plugins/Runtime/nDisplay/Source/DisplayClusterMonitor/Public/DisplayClusterMonitorSettings.h:16` |
| `UDisplayClusterStageMonitoringSettings` | `/Script/DisplayClusterStageMonitoring.DisplayClusterStageMonitoringSettings` |  | UDeveloperSettings |  | `Plugins/Runtime/nDisplay/Source/DisplayClusterStageMonitoring/Private/DisplayClusterStageMonitoringSettings.h:13` |
| `UEnvQueryManager` | `/Script/AIModule.EnvQueryManager` |  | UAISubsystem, FSelfRegisteringExec |  | `Source/Runtime/AIModule/Classes/EnvironmentQuery/EnvQueryManager.h:206` |
| `UEnvQueryTest_GameplayTags` | `/Script/AIModule.EnvQueryTest_GameplayTags` |  | UEnvQueryTest | bool bSearchComponentsForTags | `Source/Runtime/AIModule/Classes/EnvironmentQuery/Tests/EnvQueryTest_GameplayTags.h:17` |
| `UFilterVolumeComponent` | `/Script/AudioGameplayVolume.FilterVolumeComponent` |  | UAudioGameplayVolumeMutator |  | `Plugins/AudioGameplayVolume/Source/AudioGameplayVolume/Public/FilterVolumeComponent.h:36` |
| `UGameFeaturesSubsystemSettings` | `/Script/GameFeatures.GameFeaturesSubsystemSettings` |  | UDeveloperSettings |  | `Plugins/Runtime/GameFeatures/Source/GameFeatures/Public/GameFeaturesSubsystemSettings.h:11` |
| `UGameInstance` | `/Script/Engine.GameInstance` |  | UObject, FExec |  | `Source/Runtime/Engine/Classes/Engine/GameInstance.h:150` |
| `UGameNetworkManagerSettings` | `/Script/EngineSettings.GameNetworkManagerSettings` |  | UObject |  | `Source/Runtime/EngineSettings/Classes/GameNetworkManagerSettings.h:14` |
| `UGameSessionSettings` | `/Script/EngineSettings.GameSessionSettings` |  | UObject |  | `Source/Runtime/EngineSettings/Classes/GameSessionSettings.h:11` |
| `UGameplayAbilitiesDeveloperSettings` | `/Script/GameplayAbilities.GameplayAbilitiesDeveloperSettings` |  | UDeveloperSettings | FSoftClassPath AbilitySystemGlobalsClassName; bool bUseDebugTargetFromHud; TArray<FSoftObjectPath> GlobalAttributeSetDefaultsTableNames; FSoftObjectPath GlobalAttributeMetaDataTableName; FSoftClassPath GlobalGameplayCueManagerClass; FSoftObjectPath GlobalGameplayCueManagerName; TArray<FString> GameplayCueNotifyPaths; FSoftObjectPath GlobalCurveTableName; bool PredictTargetGameplayEffects; bool ReplicateActivationOwnedTags; FGameplayTag ActivateFailCanActivateAbilityTag; FGameplayTag ActivateFailCooldownTag; FGameplayTag ActivateFailCostTag; FGameplayTag ActivateFailNetworkingTag; FGameplayTag ActivateFailTagsBlockedTag; FGameplayTag ActivateFailTagsMissingTag; FSoftObjectPath GameplayTagResponseTableName; int32 MinimalReplicationTagCountBits | `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayAbilitiesDeveloperSettings.h:29` |
| `UGameplayBehaviorSubsystem` | `/Script/GameplayBehaviorsModule.GameplayBehaviorSubsystem` |  | UWorldSubsystem |  | `Plugins/Experimental/GameplayBehaviors/Source/GameplayBehaviorsModule/Public/GameplayBehaviorSubsystem.h:27` |
| `UGameplayEffectCreationMenu` | `/Script/GameplayAbilitiesEditor.GameplayEffectCreationMenu` |  | UObject |  | `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilitiesEditor/Public/GameplayEffectCreationMenu.h:30` |
| `UGameplayTask` | `/Script/GameplayTasks.GameplayTask` | Abstract | UObject, IGameplayTaskOwnerInterface |  | `Source/Runtime/GameplayTasks/Classes/GameplayTask.h:144` |
| `UGameplayTaskResource` | `/Script/GameplayTasks.GameplayTaskResource` | Abstract | UObject |  | `Source/Runtime/GameplayTasks/Classes/GameplayTaskResource.h:13` |
| `UGeneralProjectSettings` | `/Script/EngineSettings.GeneralProjectSettings` |  | UObject |  | `Source/Runtime/EngineSettings/Classes/GeneralProjectSettings.h:12` |
| `UHudSettings` | `/Script/EngineSettings.HudSettings` |  | UObject |  | `Source/Runtime/EngineSettings/Classes/HudSettings.h:11` |
| `ULiveLinkComponentSettings` | `/Script/LiveLinkComponents.LiveLinkComponentSettings` |  | UObject |  | `Plugins/Animation/LiveLink/Source/LiveLinkComponents/Public/LiveLinkComponentSettings.h:17` |
| `ULiveLinkMessageBusSourceSettings` | `/Script/LiveLink.LiveLinkMessageBusSourceSettings` |  | ULiveLinkSourceSettings |  | `Plugins/Animation/LiveLink/Source/LiveLink/Public/LiveLinkMessageBusSourceSettings.h:18` |
| `ULiveLinkSequencerSettings` | `/Script/LiveLinkSequencer.LiveLinkSequencerSettings` |  | UDeveloperSettings |  | `Plugins/Animation/LiveLink/Source/LiveLinkSequencer/Public/LiveLinkSequencerSettings.h:20` |
| `ULiveLinkSettings` | `/Script/LiveLink.LiveLinkSettings` |  | UObject |  | `Plugins/Animation/LiveLink/Source/LiveLink/Public/LiveLinkSettings.h:70` |
| `UMassSimulationSubsystem` | `/Script/MassSimulation.MassSimulationSubsystem` |  | UMassSubsystemBase |  | `Plugins/Runtime/MassGameplay/Source/MassSimulation/Public/MassSimulationSubsystem.h:17` |
| `UMediaProfileSettings` | `/Script/MediaProfile.MediaProfileSettings` |  | UObject | bool bApplyInCommandlet; bool bAutosaveAfterChange; TArray<TSoftObjectPtr<UProxyMediaSource>> MediaSourceProxy; TArray<TSoftObjectPtr<UProxyMediaOutput>> MediaOutputProxy; TSoftObjectPtr<UMediaProfile> StartupMediaProfile | `Plugins/Media/MediaProfile/Source/MediaProfile/Public/Profile/MediaProfileSettings.h:22` |
| `UMoviePlayerSettings` | `/Script/MoviePlayer.MoviePlayerSettings` |  | UObject |  | `Source/Runtime/MoviePlayer/Public/MoviePlayerSettings.h:18` |
| `UMultiServerSettings` | `/Script/MultiServerConfiguration.MultiServerSettings` |  | UObject | int32 TotalNumServers | `Plugins/Runtime/MultiServerReplication/Source/MultiServerConfiguration/Public/MultiServerSettings.h:14` |
| `UOnlineSession` | `/Script/Engine.OnlineSession` |  | UObject |  | `Source/Runtime/Engine/Classes/GameFramework/OnlineSession.h:17` |
| `UOnlineSessionClient` | `/Script/OnlineSubsystemUtils.OnlineSessionClient` |  | UOnlineSession |  | `Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Classes/OnlineSessionClient.h:22` |
| `UPartyMember` | `/Script/Party.PartyMember` | Abstract | UObject |  | `Plugins/Online/OnlineFramework/Source/Party/Public/Party/PartyMember.h:184` |
| `UPhysicsAsset` | `/Script/Engine.PhysicsAsset` | PerObjectConfig | UObject, IInterface_PreviewMeshProvider, IInterface_AssetUserData | FPhysicsAssetSolverSettings SolverSettings; FSolverIterations SolverIterations | `Source/Runtime/Engine/Classes/PhysicsEngine/PhysicsAsset.h:170` |
| `UPixelStreaming2PluginSettings` | `/Script/PixelStreaming2Settings.PixelStreaming2PluginSettings` |  | UDeveloperSettings |  | `Plugins/Media/PixelStreaming2/Source/PixelStreaming2Settings/Internal/PixelStreaming2PluginSettings.h:82` |
| `UPlatformsMenuSettings` | `/Script/DeveloperToolSettings.PlatformsMenuSettings` |  | UObject |  | `Source/Developer/DeveloperToolSettings/Classes/Settings/PlatformsMenuSettings.h:22` |
| `UProfileGo` | `/Script/AutomatedPerfTesting.ProfileGo` |  | UObject | float DefaultSettleTime; TArray<FProfileGoScenarioAPT> ProfileGoScenarios; TArray<FProfileGoGeneratedScenarioAPT> ProfileGoGeneratedScenarios; TArray<FProfileGoCollectionAPT> ProfileGoCollections; TArray<FProfileGoCommandAPT> ProfileGoCommands | `Plugins/Performance/AutomatedPerfTesting/Source/AutomatedPerfTesting/Public/ProfileGo/ProfileGo.h:224` |
| `UProjectPackagingSettings` | `/Script/DeveloperToolSettings.ProjectPackagingSettings` |  | UObject |  | `Source/Developer/DeveloperToolSettings/Classes/Settings/ProjectPackagingSettings.h:178` |
| `URazerChromaDevicesDeveloperSettings` | `/Script/RazerChromaDevices.RazerChromaDevicesDeveloperSettings` | DefaultConfig | UDeveloperSettings | bool bIsRazerChromaEnabled; bool bCreateRazerChromaInputDevice; bool bUseChromaAppInfoForInit; FRazerChromaAppInfo AppInfo | `Plugins/Experimental/RazerChromaDevices/Source/RazerChromaDevices/Public/RazerChromaDevicesDeveloperSettings.h:108` |
| `UReverbVolumeComponent` | `/Script/AudioGameplayVolume.ReverbVolumeComponent` |  | UAudioGameplayVolumeMutator |  | `Plugins/AudioGameplayVolume/Source/AudioGameplayVolume/Public/ReverbVolumeComponent.h:34` |
| `UShotgridSettings` | `/Script/Shotgrid.ShotgridSettings` |  | UObject |  | `Plugins/Experimental/Shotgrid/Source/Shotgrid/Private/ShotgridSettings.h:10` |
| `USlateRHIRendererSettings` | `/Script/SlateRHIRenderer.SlateRHIRendererSettings` |  | UDeveloperSettings |  | `Source/Runtime/SlateRHIRenderer/Public/SlateRHIRendererSettings.h:87` |
| `USmartObjectComponent` | `/Script/SmartObjectsModule.SmartObjectComponent` |  | USceneComponent |  | `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/SmartObjectComponent.h:53` |
| `USmartObjectUserComponent` | `/Script/SmartObjectsModule.SmartObjectUserComponent` |  | UActorComponent |  | `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/SmartObjectUserComponent.h:17` |
| `USocialChatManager` | `/Script/Party.SocialChatManager` |  | UObject |  | `Plugins/Online/OnlineFramework/Source/Party/Public/Chat/SocialChatManager.h:48` |
| `USocialDebugTools` | `/Script/Party.SocialDebugTools` |  | UObject, FExec |  | `Plugins/Online/OnlineFramework/Source/Party/Public/SocialDebugTools.h:26` |
| `USocialManager` | `/Script/Party.SocialManager` |  | UObject, FExec | FName PresenceFrameworkInstance; FName PresenceFrameworkAdapterInstance | `Plugins/Online/OnlineFramework/Source/Party/Public/SocialManager.h:33` |
| `USocialParty` | `/Script/Party.SocialParty` | Abstract | UObject |  | `Plugins/Online/OnlineFramework/Source/Party/Public/Party/SocialParty.h:100` |
| `USocialSettings` | `/Script/Party.SocialSettings` |  | UObject | int32 MinNicknameLength; int32 MaxNicknameLength; TArray<FSocialPlatformDescription> SocialPlatformDescriptions; TArray<FName> SonyOSSNames | `Plugins/Online/OnlineFramework/Source/Party/Public/SocialSettings.h:51` |
| `USocialSettingsXbl` | `/Script/Party.SocialSettingsXbl` |  | UObject |  | `Plugins/Online/OnlineFramework/Source/Party/Private/Microsoft/SocialSettingsXbl.h:13` |
| `USocialToolkit` | `/Script/Party.SocialToolkit` |  | UObject, FExec |  | `Plugins/Online/OnlineFramework/Source/Party/Public/SocialToolkit.h:48` |
| `USoundCueTemplateSettings` | `/Script/SoundCueTemplates.SoundCueTemplateSettings` |  | UDeveloperSettings |  | `Plugins/Runtime/SoundCueTemplates/Source/SoundCueTemplates/Public/SoundCueTemplateSettings.h:40` |
| `USoundscapeSettings` | `/Script/Soundscape.SoundscapeSettings` |  | UDeveloperSettings |  | `Plugins/Runtime/Soundscape/Source/SoundScape/Public/SoundscapeSettings.h:13` |
| `UStageMonitoringSettings` | `/Script/StageMonitorCommon.StageMonitoringSettings` |  | UDeveloperSettings |  | `Plugins/VirtualProduction/StageMonitoring/Source/StageMonitorCommon/Public/StageMonitoringSettings.h:184` |
| `UStormSyncCoreSettings` | `/Script/StormSyncCore.StormSyncCoreSettings` | DefaultConfig | UDeveloperSettings |  | `Plugins/VirtualProduction/StormSync/Source/StormSyncCore/Public/StormSyncCoreSettings.h:15` |
| `UStormSyncDrivesSettings` | `/Script/StormSyncDrives.StormSyncDrivesSettings` | DefaultConfig | UDeveloperSettings |  | `Plugins/VirtualProduction/StormSync/Source/StormSyncDrives/Public/StormSyncDrivesSettings.h:61` |
| `UStormSyncTransportSettings` | `/Script/StormSyncTransportCore.StormSyncTransportSettings` | DefaultConfig | UDeveloperSettings |  | `Plugins/VirtualProduction/StormSync/Source/StormSyncTransportCore/Public/StormSyncTransportSettings.h:15` |
| `USubmixOverrideVolumeComponent` | `/Script/AudioGameplayVolume.SubmixOverrideVolumeComponent` |  | UAudioGameplayVolumeMutator |  | `Plugins/AudioGameplayVolume/Source/AudioGameplayVolume/Public/SubmixOverrideVolumeComponent.h:34` |
| `USubmixSendVolumeComponent` | `/Script/AudioGameplayVolume.SubmixSendVolumeComponent` |  | UAudioGameplayVolumeMutator |  | `Plugins/AudioGameplayVolume/Source/AudioGameplayVolume/Public/SubmixSendVolumeComponent.h:33` |
| `USubtitlesAudioSubsystem` | `/Script/SubtitlesAndClosedCaptions.SubtitlesAudioSubsystem` |  | UAudioEngineSubsystem , IActiveSoundUpdateInterface |  | `Plugins/SubtitlesAndClosedCaptions/Source/SubtitlesAndClosedCaptions/Public/SubtitlesAudioSubsystem.h:19` |
| `USubtitlesSettings` | `/Script/SubtitlesAndClosedCaptions.SubtitlesSettings` |  | UDeveloperSettings |  | `Plugins/SubtitlesAndClosedCaptions/Source/SubtitlesAndClosedCaptions/Public/SubtitlesSettings.h:11` |
| `USubtitlesSubsystem` | `/Script/SubtitlesAndClosedCaptions.SubtitlesSubsystem` |  | UWorldSubsystem |  | `Plugins/SubtitlesAndClosedCaptions/Source/SubtitlesAndClosedCaptions/Public/SubtitlesSubsystem.h:40` |
| `USwitchboardProjectSettings` | `/Script/SwitchboardEditor.SwitchboardProjectSettings` |  | UObject | FSoftObjectPath SwitchboardOSCListener | `Plugins/VirtualProduction/Switchboard/Source/SwitchboardEditor/Public/SwitchboardProjectSettings.h:14` |
| `UTestGameInstance` | `/Script/CQTest.TestGameInstance` |  | UGameInstance |  | `Source/Developer/CQTest/Public/TestGameInstance.h:11` |
| `UUIFrameworkLocalSettings` | `/Script/UIFramework.UIFrameworkLocalSettings` |  | UDeveloperSettings | TSoftObjectPtr<UObject> ErrorResource; TSoftObjectPtr<UObject> LoadingResource | `Plugins/Experimental/UIFramework/Source/Public/UIFLocalSettings.h:15` |
| `UVCamInputSettings` | `/Script/VCamCore.VCamInputSettings` | DefaultConfig | UDeveloperSettings | FName DefaultInputProfile; TMap<FName, FVCamInputProfile> InputProfiles | `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/Input/VCamInputSettings.h:29` |
| `UVPSettings` | `/Script/VPSettings.VPSettings` |  | UObject |  | `Plugins/Experimental/VirtualProduction/VPSettings/Source/Public/VPSettings.h:13` |
| `UWidgetStateSettings` | `/Script/UMG.WidgetStateSettings` |  | UDeveloperSettings |  | `Source/Runtime/UMG/Public/Binding/States/WidgetStateSettings.h:25` |
| `UZenStreamingSettings` | `/Script/StorageServerClient.ZenStreamingSettings` |  | UDeveloperSettings |  | `Source/Runtime/StorageServerClient/Private/ZenStreamingSettings.h:10` |

## config=EditorSettings (60)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UAnalyticsPrivacySettings` | `/Script/UnrealEd.AnalyticsPrivacySettings` |  | UObject, IImportantToggleSettingInterface |  | `Source/Editor/UnrealEd/Classes/Analytics/AnalyticsPrivacySettings.h:18` |
| `UArcSplineGenerator` | `/Script/ComponentVisualizers.ArcSplineGenerator` |  | USplineGeneratorBase |  | `Source/Editor/ComponentVisualizers/Public/SplineGeneratorPanel.h:114` |
| `UAssetToolsEditorSettings` | `/Script/AssetTools.AssetToolsEditorSettings` |  | UDeveloperSettings |  | `Source/Developer/AssetTools/Public/AssetToolsSettings.h:67` |
| `UAudioEditorSettings` | `/Script/AudioEditor.AudioEditorSettings` |  | UDeveloperSettings |  | `Source/Editor/AudioEditor/Classes/AudioEditorSettings.h:53` |
| `UBakeToControlRigSettings` | `/Script/ControlRigEditor.BakeToControlRigSettings` |  | UObject |  | `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/BakeToControlRigSettings.h:10` |
| `UCircleSplineGenerator` | `/Script/ComponentVisualizers.CircleSplineGenerator` |  | USplineGeneratorBase |  | `Source/Editor/ComponentVisualizers/Public/SplineGeneratorPanel.h:80` |
| `UCollectionSettings` | `/Script/CollectionManager.CollectionSettings` |  | UDeveloperSettings |  | `Source/Developer/CollectionManager/Public/CollectionSettings.h:8` |
| `UContentBrowserSettings` | `/Script/UnrealEd.ContentBrowserSettings` |  | UObject | bool bDisplayQuickJumpText; bool bDisplayExcludedCollections | `Source/Editor/UnrealEd/Classes/Settings/ContentBrowserSettings.h:17` |
| `UCrashReportsPrivacySettings` | `/Script/UnrealEd.CrashReportsPrivacySettings` |  | UObject, IImportantToggleSettingInterface |  | `Source/Editor/UnrealEd/Classes/Analytics/CrashReportsPrivacySettings.h:18` |
| `UCreateControlPoseAssetRigSettings` | `/Script/ControlRigEditor.CreateControlPoseAssetRigSettings` |  | UObject |  | `Plugins/Animation/ControlRig/Source/ControlRigEditor/Public/Tools/CreateControlAssetRigSettings.h:14` |
| `UCurveEditorFilterBase` | `/Script/CurveEditor.CurveEditorFilterBase` |  | UObject |  | `Source/Editor/CurveEditor/Public/Filters/CurveEditorFilterBase.h:28` |
| `UDataTableEditorSettings` | `/Script/DataTableEditor.DataTableEditorSettings` |  | UDeveloperSettings |  | `Source/Editor/DataTableEditor/Private/DataTableEditorSettings.h:14` |
| `UDataprepContentConsumer` | `/Script/DataprepCore.DataprepContentConsumer` | Abstract | UObject |  | `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Public/DataprepContentConsumer.h:106` |
| `UDatasmithConsumer` | `/Script/DatasmithImporter.DatasmithConsumer` |  | UDataprepContentConsumer |  | `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Private/DatasmithConsumer.h:26` |
| `UDatasmithImporterEditorSettings` | `/Script/DatasmithImporter.DatasmithImporterEditorSettings` |  | UObject |  | `Plugins/Enterprise/DatasmithImporter/Source/DatasmithImporter/Public/DatasmithImporterEditorSettings.h:7` |
| `UEditorPerformanceSettings` | `/Script/UnrealEd.EditorPerformanceSettings` |  | UDeveloperSettings |  | `Source/Editor/UnrealEd/Classes/Editor/EditorPerformanceSettings.h:31` |
| `UEditorSettings` | `/Script/UnrealEd.EditorSettings` |  | UObject |  | `Source/Editor/UnrealEd/Public/Settings/EditorSettings.h:56` |
| `UEllipseSplineGenerator` | `/Script/ComponentVisualizers.EllipseSplineGenerator` |  | USplineGeneratorBase |  | `Source/Editor/ComponentVisualizers/Public/SplineGeneratorPanel.h:174` |
| `UGlobalSandboxedEditingEditorSettings` | `/Script/SandboxedEditing.GlobalSandboxedEditingEditorSettings` | DefaultConfig | UObject | FString DefaultExportDirectory; FString DefaultImportDirectory | `Plugins/Developer/Sandbox/SandboxedEditing/Source/SandboxedEditing/Private/GlobalSandboxedEditingEditorSettings.h:9` |
| `UHomeScreenSettings` | `/Script/MainFrame.HomeScreenSettings` |  | UObject |  | `Source/Editor/MainFrame/Public/Settings/HomeScreenSettings.h:10` |
| `UInternationalizationSettingsModel` | `/Script/InternationalizationSettings.InternationalizationSettingsModel` |  | UObject | ETimezoneSetting DisplayTimezone | `Source/Editor/InternationalizationSettings/Classes/InternationalizationSettingsModel.h:124` |
| `ULineSplineGenerator` | `/Script/ComponentVisualizers.LineSplineGenerator` |  | USplineGeneratorBase |  | `Source/Editor/ComponentVisualizers/Public/SplineGeneratorPanel.h:236` |
| `ULoadAnimToControlRigSettings` | `/Script/ControlRigEditor.LoadAnimToControlRigSettings` |  | UObject |  | `Plugins/Animation/ControlRig/Source/ControlRigEditor/Private/Sequencer/LoadAnimToControlRigSettings.h:11` |
| `UMacGraphicsSwitchingSettings` | `/Script/MacGraphicsSwitching.MacGraphicsSwitchingSettings` |  | UObject | int32 RendererID; bool bShowGraphicsSwitching | `Plugins/Editor/MacGraphicsSwitching/Source/MacGraphicsSwitching/Private/MacGraphicsSwitchingSettings.h:8` |
| `UMediaProfileEditorCaptureSettings` | `/Script/MediaFrameworkUtilitiesEditor.MediaProfileEditorCaptureSettings` |  | UMediaFrameworkWorldSettingsAssetUserData |  | `Plugins/Media/MediaFrameworkUtilities/Source/MediaFrameworkUtilitiesEditor/Private/AssetEditor/MediaProfileEditorUserSettings.h:135` |
| `UMeshVertexAttributePaintToolProperties` | `/Script/MeshModelingToolsEditorOnlyExp.MeshVertexAttributePaintToolProperties` |  | UInteractiveToolPropertySet |  | `Plugins/Experimental/MeshModelingToolsetExp/Source/MeshModelingToolsEditorOnlyExp/Public/MeshVertexAttributePaintToolBase.h:354` |
| `UModelingComponentsEditorSettings` | `/Script/ModelingComponents.ModelingComponentsEditorSettings` |  | UDeveloperSettings |  | `Plugins/Runtime/MeshModelingToolset/Source/ModelingComponents/Public/ModelingComponentsSettings.h:89` |
| `UMovieSceneAnimationTrackRecorderEditorSettings` | `/Script/TakeTrackRecorders.MovieSceneAnimationTrackRecorderEditorSettings` | Abstract | UMovieSceneTrackRecorderSettings |  | `Plugins/VirtualProduction/Takes/Source/TakeTrackRecorders/Public/TrackRecorders/MovieSceneAnimationTrackRecorderSettings.h:15` |
| `UMovieSceneAnimationTrackRecorderSettings` | `/Script/TakeTrackRecorders.MovieSceneAnimationTrackRecorderSettings` |  | UMovieSceneAnimationTrackRecorderEditorSettings |  | `Plugins/VirtualProduction/Takes/Source/TakeTrackRecorders/Public/TrackRecorders/MovieSceneAnimationTrackRecorderSettings.h:81` |
| `UMovieSceneMetaData` | `/Script/MovieScene.MovieSceneMetaData` | PerObjectConfig | UObject, IMovieSceneMetaDataInterface |  | `Source/Runtime/MovieScene/Public/MovieSceneMetaData.h:15` |
| `UMovieSceneTakeSettings` | `/Script/TakeMovieScene.MovieSceneTakeSettings` |  | UObject |  | `Plugins/VirtualProduction/Takes/Source/TakeMovieScene/Public/MovieSceneTakeSettings.h:11` |
| `UMovieSceneUserExportFBXControlRigSettings` | `/Script/MovieSceneTools.MovieSceneUserExportFBXControlRigSettings` |  | UObject | TArray<FControlToTransformMappings> ControlChannelMappings | `Source/Editor/MovieSceneTools/Public/MovieSceneToolsUserSettings.h:282` |
| `UMovieSceneUserImportFBXControlRigSettings` | `/Script/MovieSceneTools.MovieSceneUserImportFBXControlRigSettings` |  | UObject | TArray<FControlToTransformMappings> ControlChannelMappings | `Source/Editor/MovieSceneTools/Public/MovieSceneToolsUserSettings.h:201` |
| `UMovieSceneUserImportFBXSettings` | `/Script/MovieSceneTools.MovieSceneUserImportFBXSettings` |  | UObject |  | `Source/Editor/MovieSceneTools/Public/MovieSceneToolsUserSettings.h:64` |
| `UMovieSceneUserThumbnailSettings` | `/Script/MovieSceneTools.MovieSceneUserThumbnailSettings` |  | UObject |  | `Source/Editor/MovieSceneTools/Public/MovieSceneToolsUserSettings.h:25` |
| `UPropertyColorSettings` | `/Script/UnrealEd.PropertyColorSettings` |  | UObject | TArray<FPropertyColorCustomProperty> CustomProperties | `Source/Editor/UnrealEd/Private/PropertyColorSettings.h:40` |
| `URectangleSplineGenerator` | `/Script/ComponentVisualizers.RectangleSplineGenerator` |  | USplineGeneratorBase |  | `Source/Editor/ComponentVisualizers/Public/SplineGeneratorPanel.h:210` |
| `URigVMControllerSettings` | `/Script/RigVMDeveloper.RigVMControllerSettings` |  | UObject |  | `Plugins/Runtime/RigVM/Source/RigVMDeveloper/Public/RigVMModel/RigVMController.h:1877` |
| `USkinWeightsPaintToolProperties` | `/Script/MeshModelingToolsEditorOnly.SkinWeightsPaintToolProperties` |  | UBrushBaseProperties | EWeightEditMode EditingMode; EWeightEditOperation BrushMode; EComponentSelectionMode ComponentSelectionMode; EWeightColorMode ColorMode; TArray<FLinearColor> ColorRamp; FLinearColorRamp LinearColorRamp; bool bShowGroupBoundaries; FColor GroupBoundaryColor; float GroupBoundaryThickness; TEnumAsByte<EAxis::Type> MirrorAxis; EMirrorDirection MirrorDirection; float PruneValue; int32 ClampValue; int32 ClampSelectValue; float AddStrength; float ReplaceValue; float RelaxStrength; float AverageStrength; FSkinWeightBrushConfig BrushConfigAdd; FSkinWeightBrushConfig BrushConfigReplace; FSkinWeightBrushConfig BrushConfigMultiply; FSkinWeightBrushConfig BrushConfigRelax; FSkinWeightRelaxBrushAdvancedConfig RelaxBrushAdvancedConfig; ESkinWeightsPaintToolPropertiesCustomVersion CustomVersion | `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingToolsEditorOnly/Public/SkeletalMesh/SkinWeightsPaintTool.h:456` |
| `USlateThemeManager` | `/Script/SlateCore.SlateThemeManager` |  | UObject | FGuid CurrentThemeId | `Source/Runtime/SlateCore/Public/Styling/StyleColors.h:144` |
| `USourceCodeAccessSettings` | `/Script/SourceCodeAccess.SourceCodeAccessSettings` |  | UObject | FString PreferredAccessor | `Source/Developer/SourceCodeAccess/Private/SourceCodeAccessSettings.h:10` |
| `USplineGeneratorBase` | `/Script/ComponentVisualizers.SplineGeneratorBase` |  | UObject |  | `Source/Editor/ComponentVisualizers/Public/SplineGeneratorPanel.h:46` |
| `USquareSplineGenerator` | `/Script/ComponentVisualizers.SquareSplineGenerator` |  | USplineGeneratorBase |  | `Source/Editor/ComponentVisualizers/Public/SplineGeneratorPanel.h:152` |
| `UStateCentricViewSettings` | `/Script/StateTreeEditorModule.StateCentricViewSettings` |  | UDeveloperSettings | TMap<TSoftClassPtr<UStateTreeSchema>, FStateCentricViewPerSchemaSetting> PerSchemaSettings | `Plugins/Runtime/StateTree/Source/StateTreeEditorModule/Private/StateCentricView/StateCentricViewSettings.h:83` |
| `USynthesisEditorSettings` | `/Script/SynthesisEditor.SynthesisEditorSettings` |  | UDeveloperSettings |  | `Plugins/Runtime/Synthesis/Source/SynthesisEditor/Classes/SynthesisEditorSettings.h:10` |
| `UTakeMetaData` | `/Script/TakesCore.TakeMetaData` | PerObjectConfig | UObject, IMovieSceneMetaDataInterface |  | `Plugins/VirtualProduction/Takes/Source/TakesCore/Public/TakeMetaData.h:22` |
| `UTakePresetSettings` | `/Script/TakesCore.TakePresetSettings` |  | UObject |  | `Plugins/VirtualProduction/Takes/Source/TakesCore/Public/TakePresetSettings.h:29` |
| `UTakeRecorderHitchVisualizationSettings` | `/Script/TakeRecorderEditor.TakeRecorderHitchVisualizationSettings` |  | UObject | bool bShowFrameDropMarkers; bool bShowFrameRepeatMarkers; bool bShowCatchupRanges | `Plugins/VirtualProduction/Takes/Source/TakeRecorderEditor/Private/Timecode/Visualization/TakeRecorderHitchVisualizationSettings.h:10` |
| `UTakeRecorderLevelVisibilitySource` | `/Script/TakeRecorderSources.TakeRecorderLevelVisibilitySource` |  | UTakeRecorderLevelVisibilitySourceSettings |  | `Plugins/VirtualProduction/Takes/Source/TakeRecorderSources/Public/TakeRecorderLevelVisibilitySource.h:36` |
| `UTakeRecorderLevelVisibilitySourceSettings` | `/Script/TakeRecorderSources.TakeRecorderLevelVisibilitySourceSettings` | Abstract | UTakeRecorderSource |  | `Plugins/VirtualProduction/Takes/Source/TakeRecorderSources/Public/TakeRecorderLevelVisibilitySource.h:13` |
| `UTakeRecorderLiveLinkSource` | `/Script/LiveLinkSequencer.TakeRecorderLiveLinkSource` |  | UTakeRecorderSource |  | `Plugins/Animation/LiveLink/Source/LiveLinkSequencer/Private/TakeRecorderSource/TakeRecorderLiveLinkSource.h:47` |
| `UTakeRecorderMicrophoneAudioSource` | `/Script/TakeRecorderSources.TakeRecorderMicrophoneAudioSource` |  | UTakeRecorderMicrophoneAudioSourceSettings |  | `Plugins/VirtualProduction/Takes/Source/TakeRecorderSources/Public/TakeRecorderMicrophoneAudioSource.h:78` |
| `UTakeRecorderMicrophoneAudioSourceSettings` | `/Script/TakeRecorderSources.TakeRecorderMicrophoneAudioSourceSettings` | Abstract | UTakeRecorderSource |  | `Plugins/VirtualProduction/Takes/Source/TakeRecorderSources/Public/TakeRecorderMicrophoneAudioSource.h:23` |
| `UTakeRecorderProjectSettings` | `/Script/TakeRecorder.TakeRecorderProjectSettings` |  | UObject |  | `Plugins/VirtualProduction/Takes/Source/TakeRecorder/Public/TakeRecorderSettings.h:57` |
| `UTakeRecorderWorldSourceSettings` | `/Script/TakeRecorderSources.TakeRecorderWorldSourceSettings` | Abstract | UTakeRecorderSource |  | `Plugins/VirtualProduction/Takes/Source/TakeRecorderSources/Public/TakeRecorderWorldSource.h:18` |
| `UTutorialStateSettings` | `/Script/IntroTutorials.TutorialStateSettings` |  | UObject | TArray<FTutorialProgress> TutorialsProgress; bool bDismissedAllTutorials | `Plugins/Editor/GuidedTutorials/Source/IntroTutorials/Private/TutorialStateSettings.h:40` |
| `UVISettings` | `/Script/ViewportInteraction.VISettings` |  | UObject |  | `Source/Editor/ViewportInteraction/Public/VISettings.h:13` |
| `UVRModeSettings` | `/Script/VREditor.VRModeSettings` |  | UVISettings |  | `Source/Editor/VREditor/Public/VRModeSettings.h:33` |
| `UVisualStudioSourceCodeAccessSettings` | `/Script/VisualStudioSourceCodeAccess.VisualStudioSourceCodeAccessSettings` |  | UObject | bool bUproject; bool bPreview | `Plugins/Developer/VisualStudioSourceCodeAccess/Source/VisualStudioSourceCodeAccess/Private/VisualStudioSourceCodeAccessSettings.h:10` |
| `UWorldPartitionEditorSettings` | `/Script/WorldPartitionEditor.WorldPartitionEditorSettings` |  | UDeveloperSettings | TSubclassOf<UWorldPartitionConvertCommandlet> CommandletClass; int32 InstancedFoliageGridSize; int32 MinimapLowQualityWorldUnitsPerPixelThreshold; bool bEnableLoadingInEditor; bool bEnableStreamingGenerationLogOnPIE; bool bShowHLODsInEditor; bool bShowHLODsOverLoadedRegions; bool bEnableAdvancedHLODSettings; double HLODMinDrawDistance; double HLODMaxDrawDistance | `Source/Editor/WorldPartitionEditor/Public/WorldPartition/WorldPartitionEditorSettings.h:12` |

## config=Input (22)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `AVisualLoggerCameraController` | `/Script/LogVisualizer.VisualLoggerCameraController` |  | ADebugCameraController |  | `Source/Developer/LogVisualizer/Private/VisualLoggerCameraController.h:11` |
| `UCommonUIInputSettings` | `/Script/CommonUI.CommonUIInputSettings` |  | UObject | bool bLinkCursorToGamepadFocus; int32 UIActionProcessingPriority; TArray<FUIInputAction> InputActions; TArray<FUIInputAction> ActionOverrides; FCommonAnalogCursorSettings AnalogCursorSettings; TSoftClassPtr<UUserWidget> DefaultVirtualPointerClass | `Plugins/Runtime/CommonUI/Source/CommonUI/Public/Input/CommonUIInputSettings.h:114` |
| `UConsole` | `/Script/Engine.Console` |  | UObject , FOutputDevice |  | `Source/Runtime/Engine/Classes/Engine/Console.h:65` |
| `UConsoleSettings` | `/Script/EngineSettings.ConsoleSettings` |  | UObject |  | `Source/Runtime/EngineSettings/Classes/ConsoleSettings.h:59` |
| `UDisplayClusterPlayerInput` | `/Script/DisplayCluster.DisplayClusterPlayerInput` |  | UEnhancedPlayerInput |  | `Plugins/Runtime/nDisplay/Source/DisplayCluster/Public/DisplayClusterPlayerInput.h:16` |
| `UEnhancedInputComponent` | `/Script/EnhancedInput.EnhancedInputComponent` |  | UInputComponent |  | `Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h:372` |
| `UEnhancedInputDeveloperSettings` | `/Script/EnhancedInput.EnhancedInputDeveloperSettings` |  | UDeveloperSettingsBackedByCVars |  | `Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputDeveloperSettings.h:42` |
| `UEnhancedInputEditorProjectSettings` | `/Script/InputEditor.EnhancedInputEditorProjectSettings` |  | UDeveloperSettings |  | `Plugins/EnhancedInput/Source/InputEditor/Public/EnhancedInputEditorSettings.h:18` |
| `UEnhancedInputPlatformSettings` | `/Script/EnhancedInput.EnhancedInputPlatformSettings` |  | UPlatformSettings | bool bShouldLogMappingContextRedirects | `Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputPlatformSettings.h:50` |
| `UEnhancedPlayerInput` | `/Script/EnhancedInput.EnhancedPlayerInput` |  | UPlayerInput |  | `Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedPlayerInput.h:93` |
| `UGameInputDeveloperSettings` | `/Script/GameInputBase.GameInputDeveloperSettings` | DefaultConfig | UObject | TArray<FGameInputDeviceConfiguration> DeviceConfigurations; TArray<FGameInputDeviceIdentifier> DevicesToIgnore; uint32 SupportedDeviceFamilies; bool bDoNotProcessDuplicateCapabilitiesForSingleUser; bool bEnableHapticSensorSupport | `Plugins/Runtime/GameInput/Source/GameInputBase/Public/GameInputDeveloperSettings.h:481` |
| `UGameInputPlatformSettings` | `/Script/GameInputBase.GameInputPlatformSettings` | DefaultConfig | UPlatformSettings | bool bProcessController; bool bProcessRawInput; bool bSpecialDevicesRequireExplicitDeviceConfiguration; bool bProcessGamepad; bool bProcessKeyboard; bool bProcessMouse; bool bProcessSensors; bool bProcessRacingWheel; float RacingWheelDeadzone; bool bProcessArcadeStick; bool bProcessFlightStick; float FlightStickPitchDeadzone; float FlightStickRollDeadzone; float FlightStickThrottleDeadzone; float FlightStickYawDeadzone | `Plugins/Runtime/GameInput/Source/GameInputBase/Public/GameInputDeveloperSettings.h:327` |
| `UInputComponent` | `/Script/Engine.InputComponent` |  | UActorComponent |  | `Source/Runtime/Engine/Classes/Components/InputComponent.h:747` |
| `UInputMappingContext` | `/Script/EnhancedInput.InputMappingContext` |  | UDataAsset |  | `Plugins/EnhancedInput/Source/EnhancedInput/Public/InputMappingContext.h:86` |
| `UInputModifier` | `/Script/EnhancedInput.InputModifier` | Abstract | UObject |  | `Plugins/EnhancedInput/Source/EnhancedInput/Public/InputModifiers.h:15` |
| `UInputPlatformSettings` | `/Script/Engine.InputPlatformSettings` |  | UPlatformSettings |  | `Source/Runtime/Engine/Classes/GameFramework/InputSettings.h:535` |
| `UInputSettings` | `/Script/Engine.InputSettings` |  | UObject |  | `Source/Runtime/Engine/Classes/GameFramework/InputSettings.h:22` |
| `UInputTrigger` | `/Script/EnhancedInput.InputTrigger` | Abstract | UObject | float ActuationThreshold; bool bShouldAlwaysTick | `Plugins/EnhancedInput/Source/EnhancedInput/Public/InputTriggers.h:112` |
| `UInputTriggerTimedBase` | `/Script/EnhancedInput.InputTriggerTimedBase` | Abstract | UInputTrigger | bool bAffectedByTimeDilation | `Plugins/EnhancedInput/Source/EnhancedInput/Public/InputTriggers.h:211` |
| `UOpenXRHandTrackingSettings` | `/Script/OpenXRHandTracking.OpenXRHandTrackingSettings` |  | UObject |  | `Plugins/Runtime/OpenXRHandTracking/Source/OpenXRHandTracking/Public/OpenXRHandTrackingSettings.h:12` |
| `UPlayerInput` | `/Script/Engine.PlayerInput` |  | UObject |  | `Source/Runtime/Engine/Classes/GameFramework/PlayerInput.h:431` |
| `URawInputSettings` | `/Script/RawInput.RawInputSettings` |  | UDeveloperSettings |  | `Plugins/Experimental/RawInput/Source/RawInput/Public/RawInputSettings.h:86` |

## config=ChaosVD (17)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UChaosVDAccelerationStructureVisualizationSettings` | `/Script/ChaosVDBuiltInExtensions.ChaosVDAccelerationStructureVisualizationSettings` | PerObjectConfig | UChaosVDVisualizationSettingsObjectBase |  | `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions/Private/AccelerationStructures/Settings/ChaosVDAccelerationStructureVisualizationSettings.h:39` |
| `UChaosVDCameraDataSettings` | `/Script/ChaosVDBuiltInExtensions.ChaosVDCameraDataSettings` | PerObjectConfig | UChaosVDVisualizationSettingsObjectBase |  | `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions/Private/CameraTraces/Settings/ChaosVDCameraDataSettings.h:17` |
| `UChaosVDCharacterConstraintsVisualizationSettings` | `/Script/ChaosVD.ChaosVDCharacterConstraintsVisualizationSettings` | PerObjectConfig | UChaosVDVisualizationSettingsObjectBase |  | `Plugins/ChaosVD/Source/ChaosVD/Private/Settings/ChaosVDCharacterConstraintsVisualizationSettings.h:36` |
| `UChaosVDCollisionDataVisualizationSettings` | `/Script/ChaosVD.ChaosVDCollisionDataVisualizationSettings` | PerObjectConfig | UChaosVDVisualizationSettingsObjectBase |  | `Plugins/ChaosVD/Source/ChaosVD/Private/Settings/ChaosVDCollisionVisualizationSettings.h:25` |
| `UChaosVDGeneralSettings` | `/Script/ChaosVD.ChaosVDGeneralSettings` | PerObjectConfig | UChaosVDSettingsObjectBase | bool bTrimEmptyFrames; int32 MaxGameThreadFramesToQueueNum; bool bStreamingSystemEnabled; float StreamingBoxExtentSize; bool bProcessPendingOperationsQueueInWorkerThread; bool bUpdateSceneOutlinerDuringPlayback; int32 MaxConnectionRetries; FFilePath DefaultSavePathOverride; bool bAutoStartLiveSessionsPlayback; bool bSafeLoadingMode; EChaosVDParticleExtraDataLoadingMode ParticleExtraDataLoadingMode; bool bShowUnsafeDataWarning; bool bShowSafeModeSkippedWarning; bool bShowNativeSerializationWarning | `Plugins/ChaosVD/Source/ChaosVD/Public/Settings/ChaosVDGeneralSettings.h:42` |
| `UChaosVDGenericDebugDrawSettings` | `/Script/ChaosVDBuiltInExtensions.ChaosVDGenericDebugDrawSettings` | PerObjectConfig | UChaosVDVisualizationSettingsObjectBase |  | `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions/Private/GenericDebugDraw/Settings/ChaosVDGenericDebugDrawSettings.h:21` |
| `UChaosVDJointConstraintsVisualizationSettings` | `/Script/ChaosVD.ChaosVDJointConstraintsVisualizationSettings` | PerObjectConfig | UChaosVDVisualizationSettingsObjectBase |  | `Plugins/ChaosVD/Source/ChaosVD/Private/Settings/ChaosVDJointConstraintVisualizationSettings.h:32` |
| `UChaosVDMetricsViewSettings` | `/Script/ChaosVDBuiltInExtensions.ChaosVDMetricsViewSettings` |  | UChaosVDSettingsObjectBase | uint32 HeatmapCellSize; FChaosVDHeatmapColorSettings HeatmapColorSettings; TMap<ChaosVDParticleMetricsType, FChaosVDMetricsSettings> MetricSettings | `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions/Private/PerformanceMetrics/Settings/ChaosVDMetricsViewSettings.h:62` |
| `UChaosVDMiscSettings` | `/Script/ChaosVD.ChaosVDMiscSettings` | PerObjectConfig | UChaosVDSettingsObjectBase |  | `Plugins/ChaosVD/Source/ChaosVD/Private/Settings/ChaosVDMiscSettings.h:57` |
| `UChaosVDParticleVisualizationColorSettings` | `/Script/ChaosVD.ChaosVDParticleVisualizationColorSettings` | PerObjectConfig | UChaosVDVisualizationSettingsObjectBase |  | `Plugins/ChaosVD/Source/ChaosVD/Private/Settings/ChaosVDParticleVisualizationSettings.h:215` |
| `UChaosVDParticleVisualizationDebugDrawSettings` | `/Script/ChaosVD.ChaosVDParticleVisualizationDebugDrawSettings` | PerObjectConfig | UChaosVDVisualizationSettingsObjectBase |  | `Plugins/ChaosVD/Source/ChaosVD/Private/Settings/ChaosVDParticleVisualizationSettings.h:234` |
| `UChaosVDParticleVisualizationSettings` | `/Script/ChaosVD.ChaosVDParticleVisualizationSettings` | PerObjectConfig | UChaosVDVisualizationSettingsObjectBase |  | `Plugins/ChaosVD/Source/ChaosVD/Private/Settings/ChaosVDParticleVisualizationSettings.h:300` |
| `UChaosVDSceneQueriesVisualizationSettings` | `/Script/ChaosVD.ChaosVDSceneQueriesVisualizationSettings` | PerObjectConfig | UChaosVDVisualizationSettingsObjectBase |  | `Plugins/ChaosVD/Source/ChaosVD/Private/Settings/ChaosVDSceneQueryVisualizationSettings.h:36` |
| `UChaosVDSettingsObjectBase` | `/Script/ChaosVD.ChaosVDSettingsObjectBase` |  | UObject |  | `Plugins/ChaosVD/Source/ChaosVD/Public/Settings/ChaosVDCoreSettings.h:27` |
| `UChaosVDSolverTrackSettings` | `/Script/ChaosVD.ChaosVDSolverTrackSettings` | PerObjectConfig | UChaosVDSettingsObjectBase |  | `Plugins/ChaosVD/Source/ChaosVD/Private/Settings/ChaosVDSolverTrackSettings.h:12` |
| `UChaosVDVisualizationSettingsObjectBase` | `/Script/ChaosVD.ChaosVDVisualizationSettingsObjectBase` |  | UChaosVDSettingsObjectBase |  | `Plugins/ChaosVD/Source/ChaosVD/Public/Settings/ChaosVDCoreSettings.h:67` |
| `UMoverCVDSimDataSettings` | `/Script/MoverCVDEditor.MoverCVDSimDataSettings` | PerObjectConfig | UChaosVDVisualizationSettingsObjectBase |  | `Plugins/Experimental/Mover/Source/MoverCVDEditor/Private/MoverCVDSimDataSettings.h:17` |

## config=Mass (14)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `AInstancedActorsManager` | `/Script/InstancedActors.InstancedActorsManager` |  | APartitionActor, ISMInstanceManager, IActorInstanceManagerInterface |  | `Plugins/Runtime/InstancedActors/Source/InstancedActors/Public/InstancedActorsManager.h:69` |
| `UMassBehaviorSettings` | `/Script/MassAIBehavior.MassBehaviorSettings` |  | UMassModuleSettings | TSoftClassPtr<UMassStateTreeProcessor> DynamicStateTreeProcessorClass | `Plugins/AI/MassAI/Source/MassAIBehavior/Public/MassBehaviorSettings.h:13` |
| `UMassEntitySettings` | `/Script/MassEntity.MassEntitySettings` |  | UMassModuleSettings |  | `Source/Runtime/MassEntity/Public/MassEntitySettings.h:20` |
| `UMassEntityTraitBase` | `/Script/MassSpawner.MassEntityTraitBase` | Abstract | UObject |  | `Plugins/Runtime/MassGameplay/Source/MassSpawner/Public/MassEntityTraitBase.h:17` |
| `UMassGameplaySettings` | `/Script/MassCommon.MassGameplaySettings` |  | UMassModuleSettings |  | `Plugins/Runtime/MassGameplay/Source/MassCommon/Public/MassGameplaySettings.h:9` |
| `UMassLODSubsystem` | `/Script/MassLOD.MassLODSubsystem` |  | UMassSubsystemBase |  | `Plugins/Runtime/MassGameplay/Source/MassLOD/Public/MassLODSubsystem.h:76` |
| `UMassModuleSettings` | `/Script/MassEntity.MassModuleSettings` | Abstract | UObject |  | `Source/Runtime/MassEntity/Public/MassSettings.h:16` |
| `UMassMovementSettings` | `/Script/MassMovement.MassMovementSettings` |  | UMassModuleSettings |  | `Plugins/Runtime/MassGameplay/Source/MassMovement/Public/MassMovementSettings.h:12` |
| `UMassProcessor` | `/Script/MassEntity.MassProcessor` |  | UObject |  | `Source/Runtime/MassEntity/Public/MassProcessor.h:78` |
| `UMassReplicationSettings` | `/Script/MassReplication.MassReplicationSettings` |  | UMassModuleSettings |  | `Plugins/Runtime/MassGameplay/Source/MassReplication/Public/MassReplicationSettings.h:8` |
| `UMassSettings` | `/Script/MassEntity.MassSettings` |  | UDeveloperSettings |  | `Source/Runtime/MassEntity/Public/MassSettings.h:25` |
| `UMassSimulationSettings` | `/Script/MassSimulation.MassSimulationSettings` |  | UMassModuleSettings |  | `Plugins/Runtime/MassGameplay/Source/MassSimulation/Public/MassSimulationSettings.h:15` |
| `UMassSubsystemBase` | `/Script/MassEntity.MassSubsystemBase` | Abstract | UWorldSubsystem |  | `Source/Runtime/MassEntity/Public/MassSubsystemBase.h:35` |
| `UMassTickableSubsystemBase` | `/Script/MassEntity.MassTickableSubsystemBase` | Abstract | UTickableWorldSubsystem |  | `Source/Runtime/MassEntity/Public/MassSubsystemBase.h:83` |

## config=DeviceProfiles (6)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UAndroidDeviceProfileMatchingRules` | `/Script/AndroidDeviceProfileSelector.AndroidDeviceProfileMatchingRules` |  | UObject |  | `Plugins/Runtime/AndroidDeviceProfileSelector/Source/AndroidDeviceProfileSelector/Private/AndroidDeviceProfileMatchingRules.h:77` |
| `UAndroidJavaSurfaceViewDevices` | `/Script/AndroidDeviceProfileSelector.AndroidJavaSurfaceViewDevices` |  | UObject |  | `Plugins/Runtime/AndroidDeviceProfileSelector/Source/AndroidDeviceProfileSelector/Public/AndroidJavaSurfaceViewDevices.h:19` |
| `UDeviceProfile` | `/Script/Engine.DeviceProfile` |  | UTextureLODSettings |  | `Source/Runtime/Engine/Classes/DeviceProfiles/DeviceProfile.h:20` |
| `UDeviceProfileFragment` | `/Script/Engine.DeviceProfileFragment` |  | UObject |  | `Source/Runtime/Engine/Classes/DeviceProfiles/DeviceProfileFragment.h:13` |
| `UDeviceProfileManager` | `/Script/Engine.DeviceProfileManager` |  | UObject |  | `Source/Runtime/Engine/Classes/DeviceProfiles/DeviceProfileManager.h:50` |
| `UTextureLODSettings` | `/Script/Engine.TextureLODSettings` |  | UObject |  | `Source/Runtime/Engine/Classes/Engine/TextureLODSettings.h:154` |

## config=Plugins (6)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UGeometryMaskSettings` | `/Script/GeometryMask.GeometryMaskSettings` | DefaultConfig | UDeveloperSettings | float DefaultResolutionMultiplier | `Plugins/VirtualProduction/GeometryMask/Source/GeometryMask/Private/GeometryMaskSettings.h:9` |
| `UMLAdapterSettings` | `/Script/MLAdapter.MLAdapterSettings` |  | UDeveloperSettings |  | `Plugins/AI/MLAdapter/Source/MLAdapter/Public/MLAdapterSettings.h:21` |
| `UMassCrowdSettings` | `/Script/MassCrowd.MassCrowdSettings` |  | UMassModuleSettings |  | `Plugins/AI/MassCrowd/Source/MassCrowd/Public/MassCrowdSettings.h:51` |
| `UMassLookAtSettings` | `/Script/MassAIBehavior.MassLookAtSettings` |  | UDeveloperSettings |  | `Plugins/AI/MassAI/Source/MassAIBehavior/Public/MassLookAtSettings.h:14` |
| `UMassSmartObjectSettings` | `/Script/MassSmartObjects.MassSmartObjectSettings` |  | UMassModuleSettings |  | `Plugins/Runtime/MassGameplay/Source/MassSmartObjects/Public/MassSmartObjectSettings.h:19` |
| `UZoneGraphSettings` | `/Script/ZoneGraph.ZoneGraphSettings` |  | UDeveloperSettings |  | `Plugins/Runtime/ZoneGraph/Source/ZoneGraph/Public/ZoneGraphSettings.h:18` |

## config=DMXEditor (4)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UDMXAddFixturePatchMenuData` | `/Script/DMXEditor.DMXAddFixturePatchMenuData` |  | UObject | TSoftObjectPtr<UDMXEntityFixtureType> SoftFixtureType; int32 ActiveModeIndex; int32 NumPatches; bool bIncrementChannelAfterPatching | `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Widgets/FixturePatch/DMXAddFixturePatchMenuData.h:13` |
| `UDMXLibrary` | `/Script/DMXRuntime.DMXLibrary` |  | UDMXObjectBase |  | `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXRuntime/Public/Library/DMXLibrary.h:49` |
| `UDMXMVRExportOptions` | `/Script/DMXEditor.DMXMVRExportOptions` |  | UObject |  | `Plugins/VirtualProduction/DMX/DMXEngine/Source/DMXEditor/Private/Exporters/DMXMVRExportOptions.h:9` |
| `UDMXPixelMappingDMXLibraryViewModel` | `/Script/DMXPixelMappingEditor.DMXPixelMappingDMXLibraryViewModel` |  | UObject , FEditorUndoClient | FDMXReadOnlyFixturePatchListDescriptor FixturePatchListDescriptor | `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/ViewModels/DMXPixelMappingDMXLibraryViewModel.h:24` |

## config=Interchange (4)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UGLTFPipelineSettings` | `/Script/InterchangePipelines.GLTFPipelineSettings` |  | UDeveloperSettings |  | `Plugins/Interchange/Runtime/Source/Pipelines/Public/InterchangeglTFPipeline.h:21` |
| `UInterchangeFbxSettings` | `/Script/InterchangeFbxParser.InterchangeFbxSettings` |  | UDeveloperSettings |  | `Plugins/Interchange/Runtime/Source/Parsers/Fbx/Public/InterchangeFbxSettings.h:17` |
| `UInterchangeMaterialXPipeline` | `/Script/InterchangePipelines.InterchangeMaterialXPipeline` |  | UInterchangePipelineBase |  | `Plugins/Interchange/Runtime/Source/Pipelines/Public/InterchangeMaterialXPipeline.h:95` |
| `UMaterialXPipelineSettings` | `/Script/InterchangePipelines.MaterialXPipelineSettings` |  | UDeveloperSettings |  | `Plugins/Interchange/Runtime/Source/Pipelines/Public/InterchangeMaterialXPipeline.h:26` |

## config=MultiUserServerUserSettings (4)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UConcertTransportLogSettings` | `/Script/MultiUserServer.ConcertTransportLogSettings` | DefaultConfig | UObject | ETimeFormat TimestampTimeFormat | `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Settings/ConcertTransportLogSettings.h:11` |
| `UMultiUserServerColumnVisibilitySettings` | `/Script/MultiUserServer.MultiUserServerColumnVisibilitySettings` | DefaultConfig | UObject | FColumnVisibilitySnapshot SessionBrowserColumnVisibility; FColumnVisibilitySnapshot DeleteActivityDialogColumnVisibility; FColumnVisibilitySnapshot ArchivedActivityBrowserColumnVisibility; FColumnVisibilitySnapshot LiveActivityBrowserColumnVisibility; FColumnVisibilitySnapshot LiveSessionContentColumnVisibility; FColumnVisibilitySnapshot TransportLogColumnVisibility; FColumnVisibilitySnapshot PackageTransmissionColumnVisibility | `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Settings/MultiUserServerColumnVisibilitySettings.h:11` |
| `UMultiUserServerPackageTransmissionSettings` | `/Script/MultiUserServer.MultiUserServerPackageTransmissionSettings` | DefaultConfig | UObject | ETimeFormat TimestampTimeFormat | `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Settings/MultiUserServerPackageTransmissionSettings.h:11` |
| `UMultiUserServerUserPreferences` | `/Script/MultiUserServer.MultiUserServerUserPreferences` | DefaultConfig | UObject | bool bWarnUserAboutMuting; bool bWarnUserAboutUnmuting | `Plugins/Developer/Concert/ConcertApp/MultiUserServer/Source/MultiUserServer/Private/Settings/MultiUserServerUserPreferences.h:10` |

## config=Niagara (4)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UNiagaraBakerSettings` | `/Script/Niagara.NiagaraBakerSettings` |  | UObject |  | `Plugins/FX/Niagara/Source/Niagara/Classes/NiagaraBakerSettings.h:140` |
| `UNiagaraEditorSettings` | `/Script/NiagaraEditor.NiagaraEditorSettings` |  | UDeveloperSettings | bool bDisplayPreviewMoviesInTooltips; FVector2f TooltipPreviewMovieSize; FLinearColor DefaultNoteColor | `Plugins/FX/Niagara/Source/NiagaraEditor/Public/NiagaraEditorSettings.h:341` |
| `UNiagaraEffectType` | `/Script/Niagara.NiagaraEffectType` |  | UObject |  | `Plugins/FX/Niagara/Source/Niagara/Classes/NiagaraEffectType.h:403` |
| `UNiagaraSettings` | `/Script/Niagara.NiagaraSettings` |  | UDeveloperSettings | int32 QuickSimCacheCaptureFrameCount | `Plugins/FX/Niagara/Source/Niagara/Public/NiagaraSettings.h:120` |

## config=CommonUI (3)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UCommonBorder` | `/Script/CommonUI.CommonBorder` | DefaultConfig | UBorder |  | `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonBorder.h:35` |
| `UCommonCustomNavigation` | `/Script/CommonUI.CommonCustomNavigation` | DefaultConfig | UBorder |  | `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonCustomNavigation.h:13` |
| `UCommonTextBlock` | `/Script/CommonUI.CommonTextBlock` | DefaultConfig | UTextBlock |  | `Plugins/Runtime/CommonUI/Source/CommonUI/Public/CommonTextBlock.h:128` |

## config=Camera (2)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UCameraAnimationCameraModifier` | `/Script/EngineCameras.CameraAnimationCameraModifier` |  | UCameraModifier |  | `Plugins/Cameras/EngineCameras/Source/EngineCameras/Public/Animations/CameraAnimationCameraModifier.h:186` |
| `UCameraModifier_CameraShake` | `/Script/Engine.CameraModifier_CameraShake` |  | UCameraModifier |  | `Source/Runtime/Engine/Classes/Camera/CameraModifier_CameraShake.h:142` |

## config=EditorKeyBindings (2)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UEditorKeyboardShortcutSettings` | `/Script/InputBindingEditor.EditorKeyboardShortcutSettings` |  | UDeveloperSettings |  | `Source/Editor/InputBindingEditor/Private/EditorKeyboardShortcutSettings.h:10` |
| `UUnrealEdKeyBindings` | `/Script/UnrealEd.UnrealEdKeyBindings` |  | UObject |  | `Source/Editor/UnrealEd/Classes/Preferences/UnrealEdKeyBindings.h:43` |

## config=GameUserSettings (2)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UEnhancedInputUserSettings` | `/Script/EnhancedInput.EnhancedInputUserSettings` |  | USaveGame |  | `Plugins/EnhancedInput/Source/EnhancedInput/Public/UserSettings/EnhancedInputUserSettings.h:515` |
| `UGameUserSettings` | `/Script/Engine.GameUserSettings` |  | UObject |  | `Source/Runtime/Engine/Classes/GameFramework/GameUserSettings.h:37` |

## config=GameplayTags (2)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UGameplayTagsSettings` | `/Script/GameplayTags.GameplayTagsSettings` |  | UGameplayTagsList |  | `Source/Runtime/GameplayTags/Classes/GameplayTagsSettings.h:102` |
| `URestrictedGameplayTagsList` | `/Script/GameplayTags.RestrictedGameplayTagsList` |  | UObject |  | `Source/Runtime/GameplayTags/Classes/GameplayTagsSettings.h:55` |

## config=MaterialExpressions (2)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UMaterialExpression` | `/Script/Engine.MaterialExpression` |  | UObject |  | `Source/Runtime/Engine/Public/Materials/MaterialExpression.h:151` |
| `UMaterialExternalCodeCollection` | `/Script/Engine.MaterialExternalCodeCollection` |  | UObject | TArray<FMaterialExternalCodeDeclaration> ExternalCodeDeclarations | `Source/Runtime/Engine/Private/Materials/MaterialExternalCodeRegistry.h:175` |

## config=MetaHumanCharacter (2)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UMetaHumanCharacterEditorSettings` | `/Script/MetaHumanCharacterEditor.MetaHumanCharacterEditorSettings` |  | UDeveloperSettings | FDirectoryPath TextureSynthesisModelDir; int32 TextureSynthesisThreadCount; TSoftObjectPtr<class UStaticMesh> SculptManipulatorMesh; TSoftObjectPtr<class UStaticMesh> MoveManipulatorMesh; TSoftObjectPtr<class UStaticMesh> KeyPointCharacterManipulatorMesh; TSoftObjectPtr<class UStaticMesh> KeyPointTargetManipulatorMesh; bool bShowCompatibilityModeBodies; bool bEnableExperimentalWorkflows; TMap<FName, TSoftObjectPtr<UMaterialInstanceConstant>> ScalableNormalsTypeMaterials; TArray<FSoftObjectPath> TemplateAnimationDataTableAssets; TSoftObjectPtr<class UAnimSequence> ShowHandsPose; TArray<FDirectoryPath> PresetsDirectories; EMetaHumanCharacterThumbnailCameraPosition PresetsThumbnailType; EMetaHumanCharacterMigrationAction MigrationAction; FDirectoryPath MigratedPackagePath; FString MigratedNamePrefix; FString MigratedNameSuffix; int32 TextureStreamingBoost; FName DefaultLightingEnvironment; TMap<FString, TSoftObjectPtr<UWorld>> CustomLightPresets; bool bOpenCustomLightPresetInLevelEditor; bool bAutoSpawnPreviewActor; bool bValidateLightingEnvironments; int32 CameraSpeed_DEPRECATED; FEditorViewportCameraSpeedSettings CameraSpeedSettings; float MouseSensitivityModifier; bool bUseVirtualTextures | `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterEditor/Public/MetaHumanCharacterEditorSettings.h:35` |
| `UMetaHumanCharacterPaletteProjectSettings` | `/Script/MetaHumanCharacterPalette.MetaHumanCharacterPaletteProjectSettings` | DefaultConfig | UDeveloperSettings | TSoftClassPtr<class UMetaHumanCollectionPipeline> DefaultCharacterPipelineClass; TMap<EMetaHumanQualityLevel, TSoftClassPtr<class UMetaHumanCollectionPipeline>> DefaultCharacterLegacyPipelines; TMap<EMetaHumanQualityLevel, TSoftClassPtr<class UMetaHumanCollectionPipeline>> DefaultCharacterUEFNPipelines | `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPalette/Public/MetaHumanCharacterPaletteProjectSettings.h:12` |

## config=MetaHumanSDK (2)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UMetaHumanCloudServicesSettings` | `/Script/MetaHumanSDKEditor.MetaHumanCloudServicesSettings` |  | UObject | FString TextureSynthesisServiceUrl; FString AutorigServiceUrl; float Timeout; float LongPollTimeout; float AuthTimeout; float AuthPollInterval; int32 RetryCount; EMetaHumanCloudServiceEnvironment ServiceEnvironment; FEosConstantsPlatform ProdEosConstants; FEosConstantsPlatform GameDevEosConstants | `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Public/Cloud/MetaHumanCloudServicesSettings.h:42` |
| `UMetaHumanSDKSettings` | `/Script/MetaHumanSDKEditor.MetaHumanSDKSettings` |  | UObject | FString VersionServiceBaseUrl; FSoftObjectPath DefaultDNAPipelinePath{ TEXT("/MetaHumanSDK/DefaultDNAPipeline.DefaultDNAPipeline") }; FDirectoryPath CinematicImportPath{TEXT("/Game/MetaHumans")}; FDirectoryPath OptimizedImportPath{TEXT("/Game/MetaHumans")}; FDirectoryPath CharacterAssetPackagingPath{TEXT("/Game/EditableCharacters")}; FDirectoryPath CharacterAssemblyPackagingPath{TEXT("/Game/CharacterAssemblies")}; FDirectoryPath SkeletalClothingPackagingPath{TEXT("/Game/SkeletalClothing")}; FDirectoryPath OutfitPackagingPath{TEXT("/Game/Outfits")}; FDirectoryPath GroomPackagingPath{TEXT("/Game/Grooms")} | `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Public/MetaHumanSDKSettings.h:12` |

## config=ObjectMixer (2)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `ULightMixerEditorSettings` | `/Script/LightMixer.LightMixerEditorSettings` |  | UObject | bool bHideObjectMixerMenuItem | `Plugins/Editor/ObjectMixer/LightMixer/Source/LightMixer/Public/LightMixerEditorSettings.h:7` |
| `UObjectMixerEditorSettings` | `/Script/ObjectMixerEditor.ObjectMixerEditorSettings` |  | UDeveloperSettings | bool bSyncSelection; EObjectMixerHybridMode HybridRowPolicy | `Plugins/Editor/ObjectMixer/ObjectMixer/Source/ObjectMixer/Public/ObjectMixerEditorSettings.h:17` |

## config=OpenColorIO (2)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UOpenColorIODefaultViewportSettings` | `/Script/OpenColorIOEditor.OpenColorIODefaultViewportSettings` |  | UObject |  | `Plugins/Compositing/OpenColorIO/Source/OpenColorIOEditor/Private/OpenColorIOEditorSettings.h:57` |
| `UOpenColorIOLevelViewportSettings` | `/Script/OpenColorIOEditor.OpenColorIOLevelViewportSettings` |  | UObject |  | `Plugins/Compositing/OpenColorIO/Source/OpenColorIOEditor/Private/OpenColorIOEditorSettings.h:35` |

## config=RemoteControl (2)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `URemoteControlLogicConfig` | `/Script/RemoteControlLogic.RemoteControlLogicConfig` |  | UObject |  | `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlLogic/Public/RemoteControlLogicConfig.h:12` |
| `URemoteControlSettings` | `/Script/RemoteControlCommon.RemoteControlSettings` |  | UDeveloperSettings | bool bIgnoreGetterSetterCheck; bool bIgnoreWarnings; bool bAllowAnyRemoteFunctionCall; bool bRestrictServerAccess; bool bEnableRemotePythonExecution; bool bAllowConsoleCommandRemoteExecution; TArray<FRCAllowedRemoteFunctionCall> CustomAllowedRemoteFunctionCalls; FString AllowedOrigin; bool bShowPassphraseDisabledWarning; bool bLogicPanelVisibility; TSet<FName> EntitiesListHiddenColumns; FName DefaultPanelMode | `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlCommon/Public/RemoteControlSettings.h:180` |

## config=SmartObjects (2)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `USmartObjectSettings` | `/Script/SmartObjectsModule.SmartObjectSettings` |  | UDeveloperSettings |  | `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/SmartObjectSettings.h:11` |
| `USmartObjectSubsystem` | `/Script/SmartObjectsModule.SmartObjectSubsystem` |  | UWorldSubsystem |  | `Plugins/Runtime/SmartObjects/Source/SmartObjectsModule/Public/SmartObjectSubsystem.h:294` |

## config=VirtualProductionUtilities (2)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UVPBookmarkSettings` | `/Script/VPUtilities.VPBookmarkSettings` |  | UObject |  | `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilities/Public/VPBookmarkSettings.h:8` |
| `UVPUtilitiesEditorSettings` | `/Script/VPUtilitiesEditor.VPUtilitiesEditorSettings` |  | UObject |  | `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilitiesEditor/Public/VPUtilitiesEditorSettings.h:18` |

## config=ADM (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UADMSpatializationSettings` | `/Script/ADMSpatialization.ADMSpatializationSettings` |  | UDeveloperSettings |  | `Plugins/Runtime/ADM/Source/ADMSpatialization/Private/ADMSpatializationSettings.h:11` |

## config=AccumulationDOF (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UAccumulationDOFLevelViewportSettings` | `/Script/AccumulationDOFEditor.AccumulationDOFLevelViewportSettings` |  | UObject |  | `Plugins/VirtualProduction/AccumulationDOF/Source/AccumulationDOFEditor/Private/AccumulationDOFEditorSettings.h:71` |

## config=AjaMedia (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UAjaMediaSettings` | `/Script/AjaMedia.AjaMediaSettings` |  | UObject |  | `Plugins/Media/AjaMedia/Source/AjaMedia/Public/AjaMediaSettings.h:12` |

## config=AnimNext (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UAnimNextConfig` | `/Script/UAF.AnimNextConfig` |  | UObject |  | `Plugins/Experimental/UAF/UAF/Source/UAF/Internal/AnimNextConfig.h:9` |

## config=AnimNextAnimGraph (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UAnimNextAnimGraphSettings` | `/Script/UAFAnimGraph.AnimNextAnimGraphSettings` |  | UObject |  | `Plugins/Experimental/UAF/UAFAnimGraph/Source/UAFAnimGraph/Internal/AnimNextAnimGraphSettings.h:16` |

## config=AudioInsights (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UAudioInsightsSettings` | `/Script/AudioInsights.AudioInsightsSettings` |  | UDeveloperSettings |  | `Plugins/AudioInsights/Source/AudioInsights/Public/AudioInsightsSettings.h:13` |

## config=AudioModulation (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UAudioModulationSettings` | `/Script/AudioModulation.AudioModulationSettings` |  | UDeveloperSettings |  | `Plugins/Runtime/AudioModulation/Source/AudioModulation/Public/AudioModulationSettings.h:16` |

## config=CineCameraRigs (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UCineCameraRigRailSettings` | `/Script/CineCameraRigs.CineCameraRigRailSettings` |  | UObject |  | `Plugins/Experimental/CineCameraRigs/Source/CineCameraRigs/Public/CineCameraRigsSettings.h:13` |

## config=Composure (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UDefaultComposureEditorSettings` | `/Script/ComposureLayersEditor.DefaultComposureEditorSettings` |  | UObject | TArray<FSoftObjectPath> FeaturedCompShotClasses; TArray<FSoftObjectPath> FeaturedElementClasses; TMap<FName, FString> DefaultElementNames | `Plugins/Compositing/Composure/Source/ComposureLayersEditor/Private/ComposureEditorSettings.h:7` |

## config=ConcertSyncCore (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UConcertSyncConfig` | `/Script/ConcertSyncCore.ConcertSyncConfig` |  | UObject | TArray<FConcertReplicationActionEntry> PostReplicateActions | `Plugins/Developer/Concert/ConcertSync/ConcertSyncCore/Source/ConcertSyncCore/Public/ConcertSyncSettings.h:59` |

## config=ConfigSettingsToolsetTest (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UConfigSettingsToolsetTestSettings` | `/Script/ConfigSettingsToolset.ConfigSettingsToolsetTestSettings` |  | UObject |  | `Plugins/Experimental/Toolsets/ConfigSettingsToolset/Source/ConfigSettingsToolset/Private/Tests/ConfigSettingsToolsetTestObjects.h:13` |

## config=Crypto (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UCryptoKeysSettings` | `/Script/CryptoKeys.CryptoKeysSettings` |  | UObject |  | `Plugins/Editor/CryptoKeys/Source/CryptoKeys/Classes/CryptoKeysSettings.h:31` |

## config=DMXPixelMappingEditor (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UDMXPixelMappingEditorSettings` | `/Script/DMXPixelMappingEditor.DMXPixelMappingEditorSettings` | DefaultConfig | UObject | FDMXPixelMappingHierarchySettings HierarchySettings; FDMXPixelMappingDesignerSettings DesignerSettings; EDMXPixelMappingResetDMXMode EditorResetDMXMode | `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Settings/DMXPixelMappingEditorSettings.h:77` |

## config=DeformerGraph (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UOptimusSettings` | `/Script/OptimusSettings.OptimusSettings` |  | UDeveloperSettings |  | `Plugins/Animation/DeformerGraph/Source/OptimusSettings/Public/OptimusSettings.h:25` |

## config=DisplayClusterLaunch (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UDisplayClusterLaunchEditorProjectSettings` | `/Script/DisplayClusterLaunchEditor.DisplayClusterLaunchEditorProjectSettings` |  | UObject | bool bCloseEditorOnLaunch; bool bConnectToMultiUser; FString ExplicitSessionName; bool bEnableUnrealInsights; bool bEnableStatNamedEvents; FDirectoryPath ExplicitTraceFileSaveDirectory; FSoftObjectPath ConsoleVariablesPreset; TSet<FString> AdditionalConsoleVariables; TSet<FString> AdditionalConsoleCommands; TSet<FString> CommandLineArguments; FString LogFileName; TArray<FDisplayClusterLaunchLoggingConstruct> Logging | `Plugins/Editor/DisplayClusterLaunch/Source/DisplayClusterLaunchEditor/Public/DisplayClusterLaunchEditorProjectSettings.h:58` |

## config=Fab (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UMegascansMaterialParentSettings` | `/Script/Fab.MegascansMaterialParentSettings` |  | UDeveloperSettings |  | `Plugins/Fab/Source/Fab/Private/Pipelines/InterchangeMegascansPipeline.h:89` |

## config=FastGeoStreaming (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UFastGeoWorldPartitionRuntimeCellTransformer` | `/Script/FastGeoStreaming.FastGeoWorldPartitionRuntimeCellTransformer` | DefaultConfig | UWorldPartitionRuntimeCellTransformer | TArray<TSubclassOf<AActor>> BuiltinAllowedActorClasses; TArray<TSubclassOf<AActor>> BuiltinDisallowedActorClasses; TArray<TSubclassOf<UActorComponent>> BuiltinAllowedComponentClasses; TArray<TSubclassOf<UActorComponent>> BuiltinDisallowedComponentClasses; TArray<TSubclassOf<UActorComponent>> BuiltinIgnoredRemainingComponentClasses; TArray<TSubclassOf<UActorComponent>> BuiltinIgnoredRemainingExactComponentClasses | `Plugins/Experimental/FastGeoStreaming/Source/FastGeoStreaming/Public/FastGeoWorldPartitionRuntimeCellTransformer.h:172` |

## config=GameplayCameras (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UGameplayCamerasSettings` | `/Script/GameplayCameras.GameplayCamerasSettings` | DefaultConfig | UDeveloperSettings | bool bAutoBuildInPIE; EGameplayCamerasViewRotationMode DefaultViewRotationMode; int32 CombinedCameraRigNumThreshold; int32 MaxUsageSearchDistance; double DefaultIKAimingAngleTolerance; double DefaultIKAimingDistanceTolerance; uint8 DefaultIKAimingMaxIterations; double DefaultIKAimingMinDistance | `Plugins/Cameras/GameplayCameras/Source/GameplayCameras/Public/GameplayCamerasSettings.h:16` |

## config=GameplayTagsList (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UGameplayTagsList` | `/Script/GameplayTags.GameplayTagsList` |  | UObject |  | `Source/Runtime/GameplayTags/Classes/GameplayTagsSettings.h:33` |

## config=GuidedTutorials (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UEditorTutorialSettings` | `/Script/IntroTutorials.EditorTutorialSettings` |  | UObject | bool bDisableAllTutorialAlerts; TArray<FTutorialCategory> Categories; FSoftClassPath StartupTutorial; TArray<FTutorialContext> TutorialContexts | `Plugins/Editor/GuidedTutorials/Source/IntroTutorials/Private/EditorTutorialSettings.h:36` |

## config=InstancedActors (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UInstancedActorsProjectSettings` | `/Script/InstancedActors.InstancedActorsProjectSettings` |  | UDeveloperSettings | int32 GridSize; FDataRegistryType NamedSettingsRegistryType; FDataRegistryType ActorClassSettingsRegistryType; FName DefaultBaseSettingsName; FName EnforcedSettingsName; FInstancedActorsConfig DefaultConfig | `Plugins/Runtime/InstancedActors/Source/InstancedActors/Public/InstancedActorsSettings.h:50` |

## config=LocalizationServiceSettings (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UOneSkyLocalizationTargetSettings` | `/Script/OneSkyLocalizationService.OneSkyLocalizationTargetSettings` |  | UObject |  | `Plugins/Developer/OneSkyLocalizationService/Source/OneSkyLocalizationService/Private/OneSkyLocalizationServiceSettings.h:38` |

## config=MQTT (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UMQTTClientSettings` | `/Script/MQTTCore.MQTTClientSettings` |  | UObject | FMQTTURL DefaultURL; uint32 PublishRate | `Plugins/Protocols/MQTT/Source/MQTTCore/Public/MQTTClientSettings.h:14` |

## config=MemoryUsageQueries (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UMemoryUsageQueriesConfig` | `/Script/MemoryUsageQueries.MemoryUsageQueriesConfig` |  | UObject |  | `Plugins/MemoryUsageQueries/Source/MemoryUsageQueries/Public/MemoryUsageQueriesConfig.h:58` |

## config=MeshPartition (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `USettings` | `/Script/MeshPartition.Settings` |  | UDeveloperSettings |  | `Plugins/Experimental/MeshPartition/Source/MeshPartition/Public/MeshPartitionSettings.h:16` |

## config=MetaHumanCharacterUAF (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UMetaHumanCharacterUAFProjectSettings` | `/Script/MetaHumanCharacterUAFEditor.MetaHumanCharacterUAFProjectSettings` | DefaultConfig | UDeveloperSettings | TMap<EMetaHumanQualityLevel, TSoftClassPtr<AActor>> Blueprints | `Plugins/Experimental/MetaHuman/MetaHumanCharacterUAF/Source/MetaHumanCharacterUAFEditor/Private/MetaHumanCharacterUAFProjectSettings.h:11` |

## config=MetaSound (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UMetaSoundSettings` | `/Script/MetasoundEngine.MetaSoundSettings` |  | UDeveloperSettings |  | `Plugins/Runtime/Metasound/Source/MetasoundEngine/Public/MetasoundSettings.h:154` |

## config=ModelViewViewModel (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UMVVMDeveloperProjectSettings` | `/Script/ModelViewViewModelBlueprint.MVVMDeveloperProjectSettings` |  | UDeveloperSettings |  | `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelBlueprint/Public/MVVMDeveloperProjectSettings.h:68` |

## config=MotionDesign (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UAvaSequence` | `/Script/AvalancheSequence.AvaSequence` |  | ULevelSequence |  | `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Public/AvaSequence.h:31` |

## config=MovieRenderPipeline (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UMovieGraphProjectSettings` | `/Script/MovieRenderPipelineCore.MovieGraphProjectSettings` | DefaultConfig | UDeveloperSettings | TArray<FMovieGraphNamedResolution> DefaultNamedResolutions | `Plugins/MovieScene/MovieRenderPipeline/Source/MovieRenderPipelineCore/Public/Graph/MovieGraphProjectSettings.h:18` |

## config=MultiUserClient (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UMultiUserReplicationSettings` | `/Script/MultiUserClient.MultiUserReplicationSettings` |  | UObject | FConcertStreamObjectAutoBindingRules ReplicationEditorSettings; FMultiUserFrequencyDefaultRules FrequencyRules | `Plugins/Developer/Concert/ConcertApp/MultiUserClient/Source/MultiUserClient/Private/Settings/MultiUserReplicationSettings.h:13` |

## config=Mutable (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UCustomizableObjectProjectSettings` | `/Script/CustomizableObjectEditor.CustomizableObjectProjectSettings` |  | UObject |  | `Plugins/Mutable/Source/CustomizableObjectEditor/Private/MuCOE/CustomizableObjectProjectSettings.h:9` |

## config=NamingTokens (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UNamingTokensEditableText` | `/Script/NamingTokensUI.NamingTokensEditableText` | DefaultConfig | UMultiLineEditableText |  | `Plugins/Developer/NamingTokens/Source/NamingTokensUI/Public/NamingTokensEditableText.h:16` |

## config=NetworkPrediction (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UNetworkPredictionSettingsObject` | `/Script/NetworkPrediction.NetworkPredictionSettingsObject` |  | UObject |  | `Plugins/Runtime/NetworkPrediction/Source/NetworkPrediction/Public/NetworkPredictionSettings.h:113` |

## config=NiagaraToolsets (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UNiagaraToolsetsSettings` | `/Script/NiagaraToolsets.NiagaraToolsetsSettings` |  | UDeveloperSettings |  | `Plugins/Experimental/Toolsets/NiagaraToolsets/Source/NiagaraToolsets/Private/NiagaraToolsetsSettings.h:11` |

## config=ObjectMixerSerializedData (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UObjectMixerEditorSerializedData` | `/Script/ObjectMixerEditor.ObjectMixerEditorSerializedData` |  | UObject | TSet<FObjectMixerSerializationDataPerFilter> SerializedDataPerFilter | `Plugins/Editor/ObjectMixer/ObjectMixer/Source/ObjectMixer/Public/ObjectMixerEditorSerializedData.h:101` |

## config=PIEPreviewSettings (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UPIEPreviewSettings` | `/Script/PIEPreviewDeviceProfileSelector.PIEPreviewSettings` |  | UObject |  | `Source/Editor/PIEPreviewDeviceProfileSelector/Private/PIEPreviewSettings.h:17` |

## config=PerformanceCaptureWorkflow (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UPerformanceCaptureSettings` | `/Script/PerformanceCaptureWorkflow.PerformanceCaptureSettings` | DefaultConfig | UObject | TSoftClassPtr<APerformanceCaptureStageRoot> StageRoot; TSoftObjectPtr<USkeletalMesh> DefaultPerformerSkelMesh; TArray<TSoftClassPtr<ASkeletalMeshActor>> AllowedCaptureCharacterActorClasses; TArray<TSoftClassPtr<ASkeletalMeshActor>> DisallowedCaptureCharacterActorClasses; TSoftClassPtr<UMVVMViewModelBase> ViewModelClass; TSoftObjectPtr<UEditorUtilityWidgetBlueprint> MocapManagerUI; TSoftObjectPtr<UPCapWorkflowCustomization> MocapManagerDefaultWorkflow; TSoftClassPtr<UEditorUtilityWidget> WorkflowPhaseUIBaseClass; TSoftObjectPtr<UPCapSessionTemplate> DefaultSessionTemplate; TSoftClassPtr<UPerformanceCaptureDatabaseHelper> DatabaseHelperClass; TSoftObjectPtr<UPCapDataTable> SessionTable; TSoftObjectPtr<UPCapDataTable> ProductionTable | `Plugins/VirtualProduction/PerformanceCaptureWorkflow/Source/PerformanceCaptureWorkflow/Private/PCapSettings.h:24` |

## config=PixelStreaming (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UPixelStreamingSettings` | `/Script/PixelStreamingInput.PixelStreamingSettings` |  | UDeveloperSettings |  | `Plugins/Media/PixelStreaming/Source/PixelStreamingInput/Public/EditorPixelStreamingSettings.h:11` |

## config=RemoteControlProtocolWidgets (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `URemoteControlProtocolWidgetsSettings` | `/Script/RemoteControlProtocolWidgets.RemoteControlProtocolWidgetsSettings` |  | UObject | TSet<FName> HiddenProtocolTypeNames; FName PreferredProtocol | `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlProtocolWidgets/Private/RemoteControlProtocolWidgetsSettings.h:14` |

## config=RewindDebugger (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `URewindDebuggerProjectSettings` | `/Script/RewindDebugger.RewindDebuggerProjectSettings` |  | UDeveloperSettings | TArray<FSoftClassPath> SelectorAllowedTypes; TArray<FInstancedStruct> SelectorAllowedStructTypes | `Plugins/Animation/GameplayInsights/Source/RewindDebugger/Public/RewindDebuggerSettings.h:41` |

## config=RuntimeOptions (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `URuntimeOptionsBase` | `/Script/Engine.RuntimeOptionsBase` | Abstract | UObject |  | `Source/Runtime/Engine/Classes/Engine/RuntimeOptionsBase.h:36` |

## config=StateTree (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UStateTreeSettings` | `/Script/StateTreeModule.StateTreeSettings` |  | UDeveloperSettings |  | `Plugins/Runtime/StateTree/Source/StateTreeModule/Public/StateTreeSettings.h:11` |

## config=TemplateCategories (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UTemplateCategories` | `/Script/GameProjectGeneration.TemplateCategories` |  | UObject |  | `Source/Editor/GameProjectGeneration/Classes/TemplateProjectDefs.h:253` |

## config=TemplateDefs (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UTemplateProjectDefs` | `/Script/GameProjectGeneration.TemplateProjectDefs` |  | UObject |  | `Source/Editor/GameProjectGeneration/Classes/TemplateProjectDefs.h:115` |

## config=Text3D (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UText3DProjectSettings` | `/Script/Text3D.Text3DProjectSettings` |  | UDeveloperSettings | TSoftObjectPtr<UMaterial> DefaultMaterial; TSoftObjectPtr<UText3DStyleSet> DefaultStyleSet; TSoftObjectPtr<UFont> FallbackFont; TSoftObjectPtr<UFontFace> FallbackFontFace; FString FontDirectory; float FontFaceGlyphCleanupDelay; bool bForceDisableTextCollision; bool bUseExistingCharactersAsTemplates; TArray<FString> FavoriteFonts; bool bShowOnlyMonospaced; bool bShowOnlyBold; bool bShowOnlyItalic; bool bDebugMode | `Plugins/VirtualProduction/Text3D/Source/Text3D/Public/Settings/Text3DProjectSettings.h:17` |

## config=TraceSourceFilters (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UTraceSourceFilteringSettings` | `/Script/SourceFilteringCore.TraceSourceFilteringSettings` |  | UObject | bool bDrawFilteringStates; bool bDrawOnlyPassingActors; bool bDrawFilterDescriptionForRejectedActors; bool bOutputOptimizedFilterState | `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringCore/Public/TraceSourceFilteringSettings.h:8` |

## config=TranslationPickerSettings (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UTranslationPickerSettings` | `/Script/TranslationEditor.TranslationPickerSettings` |  | UObject |  | `Source/Developer/TranslationEditor/Private/TranslationPickerEditWindow.h:33` |

## config=USDCore (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UUsdProjectSettings` | `/Script/USDClasses.UsdProjectSettings` |  | UDeveloperSettings |  | `Plugins/Runtime/USDCore/Source/USDClasses/Public/USDProjectSettings.h:60` |

## config=USDImporter (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `AUsdStageActor` | `/Script/USDStage.UsdStageActor` |  | AActor |  | `Plugins/Importers/USDImporter/Source/USDStage/Public/USDStageActor.h:50` |

## config=USDPregen (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UUSDPregenSettings` | `/Script/USDPregenInterchange.USDPregenSettings` |  | UDeveloperSettings |  | `Plugins/Experimental/USDPregen/Source/USDPregenInterchange/Public/USDPregenSettings.h:11` |

## config=UnitTest (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UUnitTestManager` | `/Script/NetcodeUnitTest.UnitTestManager` |  | UObject, FTickableGameObject, FOutputDevice |  | `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Classes/UnitTestManager.h:25` |

## config=UnitTestStats (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UUnitTest` | `/Script/NetcodeUnitTest.UnitTest` | Abstract | UUnitTestBase |  | `Plugins/NetcodeUnitTest/NetcodeUnitTest/Source/NetcodeUnitTest/Classes/UnitTest.h:106` |

## config=UnrealEd (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UUnrealEdTypes` | `/Script/UnrealEd.UnrealEdTypes` |  | UObject |  | `Source/Editor/UnrealEd/Classes/Editor/UnrealEdTypes.h:163` |

## config=UserVPRoles (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UVPRolesUserSettings` | `/Script/VPRoles.VPRolesUserSettings` |  | UObject |  | `Plugins/Experimental/VirtualProduction/VPRoles/Source/VPRoles/Private/VPRolesSettings.h:9` |

## config=UserWorldBookmarks (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UWorldBookmark` | `/Script/WorldBookmark.WorldBookmark` | PerObjectConfig | UBookmarkBase | FDateTime LastLoadedTimeStampUTC; bool bFavorite; FString BookmarkAssetPath | `Source/Editor/WorldBookmark/Public/WorldBookmark/WorldBookmark.h:41` |

## config=VirtualCameraCore (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UVirtualCameraCoreUserSettings` | `/Script/VCamCore.VirtualCameraCoreUserSettings` |  | UObject |  | `Plugins/VirtualProduction/VirtualCameraCore/Source/VCamCore/Public/VCamCoreUserSettings.h:11` |

## config=VirtualScoutingSettings (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UVirtualScoutingSettings` | `/Script/VirtualScouting.VirtualScoutingSettings` | DefaultConfig | UDeveloperSettings | bool bUseImperial; bool bViewfinderUseExposure; bool bSwapToGrabToolOnSpawnNewActor; float ViewfinderExposureCompensation; TArray<float> ViewfinderApertureArray; TArray<float> ViewfinderMaskArray; FName SequenceToolCollection; FName PlacementToolCollection | `Plugins/VirtualProduction/VirtualScouting/Source/VirtualScouting/Public/VirtualScoutingSettings.h:12` |

## config=VisualLogger (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UVisualLoggerSettings` | `/Script/Engine.VisualLoggerSettings` |  | UDeveloperSettings |  | `Source/Runtime/Engine/Public/VisualLogger/VisualLoggerSettings.h:11` |

## config=WidgetEditorToolPalette (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UCreateWidgetToolSettings` | `/Script/WidgetEditorToolPalette.CreateWidgetToolSettings` |  | UDeveloperSettings |  | `Plugins/Experimental/WidgetEditorToolPalette/Source/WidgetEditorToolPalette/Public/Settings/CreateWidgetToolSettings.h:65` |

## config=XRCreativeSettings (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `UXRCreativeSettings` | `/Script/XRCreative.XRCreativeSettings` | DefaultConfig | UDeveloperSettings |  | `Plugins/Experimental/XRCreativeFramework/Source/XRCreative/Public/XRCreativeSettings.h:20` |

## config=ZoneGraph (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `AZoneGraphData` | `/Script/ZoneGraph.ZoneGraphData` |  | AActor |  | `Plugins/Runtime/ZoneGraph/Source/ZoneGraph/Public/ZoneGraphData.h:13` |

## config=game (1)

| class | ini section | flags | base | config properties | file:line |
|---|---|---|---|---|---|
| `AWorldSettings` | `/Script/Engine.WorldSettings` |  | AInfo, IInterface_AssetUserData | uint8 bReuseAddressAndPort : 1; int32 MaxNumberOfBookmarks; TSubclassOf<class UBookmarkBase> DefaultBookmarkClass | `Source/Runtime/Engine/Classes/GameFramework/WorldSettings.h:362` |
