# Plugins / AppleARKitPoseTrackingLiveLink

- module root: `Plugins/Runtime/AR/AppleAR/AppleARKit/Source/AppleARKitPoseTrackingLiveLink`
- headers: 5; symbols: 46
- symbol kinds: class=6, delegate=2, function=2, member=11, prototype=25
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: ARUtilities, AppleARKit, AppleImageUtils, CoreUObject, HeadMountedDisplay, LiveLinkAnimationCore, LiveLinkInterface, XRBase
- PublicDependencyModuleNames: Core, Engine

### `Plugins/Runtime/AR/AppleAR/AppleARKit/Source/AppleARKitPoseTrackingLiveLink/Private/AppleARKitPoseTrackingLiveLinkImpl.h` (Private)


#### class `FAppleARKitPoseTrackingLiveLink`  
`class FAppleARKitPoseTrackingLiveLink : public IAppleARKitPoseTrackingLiveLink, public TSharedFromThis<FAppleARKitPoseTrackingLiveLink, ESPMode::ThreadSafe>`  
_L11-40_
- inherits: `IAppleARKitPoseTrackingLiveLink,TSharedFromThis<FAppleARKitPoseTrackingLiveLink,ESPMode::ThreadSafe>`
- L16 _public prototype_ `FAppleARKitPoseTrackingLiveLink();`
- L17 _public prototype_ `virtual ~FAppleARKitPoseTrackingLiveLink();`
- L19 _public prototype_ `void Init();`
- L20 _public prototype_ `void Shutdown();`
- L25 _private prototype_ `void PublishLiveLinkData(TSharedPtr<FAppleARKitAnchorData> Anchor) override;`
- L31 _private prototype_ `const TArray<FTransform>* GetRefPoseTransforms() const override;`
- L35 _private member_ `TSharedPtr<ILiveLinkSourceARKitPoseTracking> LiveLinkSource;` — If requested, publishes face ar updates to LiveLink for the animation system to use
- L37 _private member_ `FName PoseTrackingLiveLinkSubjectName;` — Copied from the UARSessionConfig project settings object
- L39 _private member_ `FName LocalDeviceId;` — The id of this device

### `Plugins/Runtime/AR/AppleAR/AppleARKit/Source/AppleARKitPoseTrackingLiveLink/Private/AppleARKitPoseTrackingLiveLinkModule.h` (Private)


#### class `FAppleARKitPoseTrackingLiveLinkModule`  
`class FAppleARKitPoseTrackingLiveLinkModule : public IModuleInterface, public IARLiveLinkRetargetingLogic`  
_L10-20_
- inherits: `IModuleInterface,IARLiveLinkRetargetingLogic`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L15 _public prototype_ `virtual void ShutdownModule() override;`
- L18 _public prototype_ `virtual void BuildPoseFromAnimationData(const UARLiveLinkRetargetAsset& SourceAsset, float DeltaTime, const FLiveLinkSkeletonStaticData* InSkeletonData, const FLiveLinkAnimationFrameData* InFrameData, FCompactPose& OutPose) override;` — Implements IARLiveLinkRetargetingLogic

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAppleARKitPoseTracking, Log, All);`
- L22 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAppleARKitPoseTracking, Log, All);`
- L24 _delegate_ `DECLARE_STATS_GROUP(TEXT("PoseTracking AR"), STATGROUP_PoseTrackingAR, STA`

### `Plugins/Runtime/AR/AppleAR/AppleARKit/Source/AppleARKitPoseTrackingLiveLink/Private/AppleARKitPoseTrackingLiveLinkRemapAsset.h` (Private)


#### class `UDEPRECATED_AppleARKitPoseTrackingLiveLinkRemapAsset`  
`class UDEPRECATED_AppleARKitPoseTrackingLiveLinkRemapAsset : public ULiveLinkRetargetAsset`  
_L15-34_
- reflection: `UCLASS(Blueprintable, Abstract, Deprecated, meta = (DeprecationMessage="This class is deprecated. Please use \"ARLiveLinkRetargetAsset\" instead."))`
- inherits: `ULiveLinkRetargetAsset`
- L20 _public prototype_ `UDEPRECATED_AppleARKitPoseTrackingLiveLinkRemapAsset(const FObjectInitializer& ObjectInitializer);`
- L21 _public prototype_ `virtual void BuildPoseFromAnimationData(float DeltaTime, const FLiveLinkSkeletonStaticData* InSkeletonData, const FLiveLinkAnimationFrameData* InFrameData, FCompactPose& OutPose) override;`
- L24 _public member_ `FVector AppleARKitHumanForward = FVector(-1, 0, 0);` — `UPROPERTY(EditAnywhere, Category="LiveLink")`
- L27 _public member_ `FVector MeshForward = FVector(0, 1, 0);` — `UPROPERTY(EditAnywhere, Category="LiveLink")`
- L30 _public member_ `TMap<FName, FName> AppleARKitBoneNamesToMeshBoneNames;` — `UPROPERTY(EditAnywhere, Category="LiveLink")`
- L33 _private prototype_ `FName GetRemappedBoneName(FName BoneName) const;`

### `Plugins/Runtime/AR/AppleAR/AppleARKit/Source/AppleARKitPoseTrackingLiveLink/Private/AppleARKitPoseTrackingLiveLinkSource.h` (Private)


#### class `FAppleARKitPoseTrackingLiveLinkSource`  
`class FAppleARKitPoseTrackingLiveLinkSource : public ILiveLinkSourceARKitPoseTracking`  
_L12-46_
- inherits: `ILiveLinkSourceARKitPoseTracking`
- desc: Publishes face blend shapes to LiveLink for use locally
- L16 _public prototype_ `FAppleARKitPoseTrackingLiveLinkSource();`
- L17 _public function_ `virtual ~FAppleARKitPoseTrackingLiveLinkSource()`
- L21 _private prototype_ `virtual void ReceiveClient(ILiveLinkClient* InClient, FGuid InSourceGuid) override;` — ILiveLinkSource interface
- L22 _private prototype_ `virtual bool IsSourceStillValid() const override;`
- L23 _private prototype_ `virtual bool RequestSourceShutdown() override;`
- L24 _private prototype_ `virtual FText GetSourceMachineName() const override;`
- L25 _private prototype_ `virtual FText GetSourceStatus() const override;`
- L26 _private prototype_ `virtual FText GetSourceType() const override;`
- L29 _private prototype_ `void UpdateLiveLink(FName SubjectName, const FTimecode& Timecode, uint32 FrameRate, const FARPose3D& PoseData, const FARPose3D& RefPoseData, FName DeviceId) override;`
- L30 _private function_ `const TArray<FTransform>* GetRefPoseTransforms() const override`
- L31 _private prototype_ `FLiveLinkStaticDataStruct SetupLiveLinkStaticData(const FARPose3D& RefPoseData);`
- L35 _private member_ `ILiveLinkClient* Client;` — The local client to push data updates to
- L38 _private member_ `FGuid SourceGuid;` — Our identifier in LiveLink
- L41 _private member_ `uint32 LastFramePublished;` — The last time we sent the data. Used to not send redundant data
- L43 _private member_ `bool bNewLiveLinkClient;`
- L45 _private member_ `TArray<FTransform> RefTransforms;`

### `Plugins/Runtime/AR/AppleAR/AppleARKit/Source/AppleARKitPoseTrackingLiveLink/Public/AppleARKitPoseTrackingLiveLinkSourceFactory.h` (Public)


#### class `ILiveLinkSourceARKitPoseTracking`  
`class ILiveLinkSourceARKitPoseTracking : public ILiveLinkSource`  
_L12-18_
- inherits: `ILiveLinkSource`
- desc: Interface that publishes face ar blend shape information via LiveLink
- L16 _public prototype_ `virtual void UpdateLiveLink(FName SubjectName, const FTimecode& Timecode, uint32 FrameRate, const FARPose3D& PoseData, const FARPose3D& RefPoseData, FName DeviceID = NAME_None) = 0;`
- L17 _public prototype_ `virtual const TArray<FTransform>* GetRefPoseTransforms() const = 0;`

#### class `FAppleARKitPoseTrackingLiveLinkSourceFactory`  
`class FAppleARKitPoseTrackingLiveLinkSourceFactory`  
_L21-26_
- desc: Factory that creates and registers the sources with the LiveLink client
- L25 _public prototype_ `static TSharedPtr<ILiveLinkSourceARKitPoseTracking> CreateLiveLinkSource();` — Creates a face mesh source that will autobind to the tracked face mesh
