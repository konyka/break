# Plugins / MetaHumanBodyTrackerInterface

- module root: `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanBodyTrackerInterface`
- headers: 1; symbols: 48
- symbol kinds: class=3, enum=1, enumerator=3, function=8, macro=1, member=22, prototype=8, struct=2
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, MetaHumanCoreTech, MetaHumanPipelineCore
- PublicDependencyModuleNames: CaptureDataCore

### `Plugins/MetaHuman/MetaHumanCoreTechLib/Source/MetaHumanBodyTrackerInterface/Public/MetaHumanBodyTrackerInterface.h` (Public)


#### enum `EMetaHumanBodyTrackerMode`  
`enum class EMetaHumanBodyTrackerMode : uint8`  
_L22-27_
- reflection: `UENUM()`
- L24 _public enumerator_ `None = 0`
- L25 _public enumerator_ `Realtime`
- L26 _public enumerator_ `Offline`

#### class `AMetaHumanBodyDriverActorInterface`  
`class AMetaHumanBodyDriverActorInterface : public AActor`  
_L30-56_
- reflection: `UCLASS()`
- inherits: `AActor`
- L36 _public function_ `virtual void Initialize()`
- L38 _public function_ `virtual void Update(const FFrameAnimationData& InAnimationData)`
- L40 _public function_ `virtual void SetBodyDriverSkeletalMeshComponent(TWeakObjectPtr<USkeletalMeshComponent> InSkeletalMeshComponent)`
- L42 _public function_ `virtual FVector GetDebugRelativeLocation() const`
- L43 _public function_ `virtual FRotator GetDebugRelativeRotation() const`
- L44 _public function_ `virtual FVector GetCameraRelativeLocation() const`
- L46 _public function_ `virtual void SetVisualizationSkeletalMeshParams(bool bInVisible, const FVector& InOffset, const FColor& InColor)`
- L49 _public member_ `TObjectPtr<class USkeletalMesh> SMPLXSkeletalMeshSkinned;` — `UPROPERTY()`
- L52 _public member_ `TObjectPtr<class USkeletalMesh> MHSkeletalMeshSizedBare;` — `UPROPERTY()`
- L55 _public member_ `TObjectPtr<class USkeletalMesh> BodyDriverSkeletalMesh;` — `UPROPERTY()`

#### class `IMetaHumanBodyTrackerInterface`  
`class IMetaHumanBodyTrackerInterface : public IModularFeature`  
_L58-122_
- inherits: `IModularFeature`
- L62 _public prototype_ `virtual ~IMetaHumanBodyTrackerInterface() = default;`
- L64 _public function_ `static FName GetModularFeatureName()`
- L107 _public prototype_ `virtual bool ExtendPipeline(const FBodyTrackerInputParams& InBodyTrackerInputParams, UE::MetaHuman::Pipeline::FPipeline& InOutPipeline, FBodyTrackerOutputParams& OutBodyTrackerOutputParams) const = 0;`
- L109 _public prototype_ `virtual TSubclassOf<AMetaHumanBodyDriverActorInterface> GetBodyDriverActorClass() const = 0;`
- L111 _public prototype_ `virtual FString GetBodyControlRigAssetPath() const = 0;`
- L113 _public prototype_ `virtual FString GetMetaHumanRetargeterAssetPath() const = 0;`
- L115 _public prototype_ `virtual USkeletalMesh* MakeMHSkeletalMesh(UObject* InOuter, const TArray<float>& InShape) const = 0;`
- L117 _public prototype_ `virtual USkeletalMesh* MakeSMPLSkeletalMesh(UObject* InOuter, const TArray<float>& InShape) const = 0;`
- L120 _public prototype_ `virtual void CustomizePerformanceDetails(IDetailLayoutBuilder& InDetailBuilder) const = 0;`

#### class `IMetaHumanBodyTrackerInterface::FBodyTrackerDataInterface`  
`class FBodyTrackerDataInterface`  
_L70-72_

#### struct `IMetaHumanBodyTrackerInterface::FBodyTrackerInputParams`  
`struct FBodyTrackerInputParams`  
_L74-98_
- L76 _public member_ `EMetaHumanBodyTrackerMode BodyTrackerMode = EMetaHumanBodyTrackerMode::None;`
- L78 _public member_ `int32 PipelineStage = -1;`
- L79 _public member_ `int32 PipelineFrameRangesIndex = -1;`
- L80 _public member_ `TArray<FFrameRange> PipelineFrameRanges;`
- L81 _public member_ `TArray<FFrameRange> PipelineExcludedFrames;`
- L83 _public member_ `TSharedPtr<UE::MetaHuman::Pipeline::FNode> ImageSrcNode;`
- L84 _public member_ `TSharedPtr<UE::MetaHuman::Pipeline::FNode> FaceAnimSrcNode;`
- L86 _public member_ `TArray64<FFrameAnimationData> AnimationData;`
- L88 _public member_ `FFrameRange ImageSequenceRange;`
- L90 _public member_ `bool bSkipPreview = false;`
- L91 _public member_ `float Fps = 30.0f;`
- L92 _public member_ `bool bAutoBodyHeight = true;`
- L93 _public member_ `float BodyHeight = 180.0f;`
- L94 _public member_ `class UMetaHumanPerformance* Performance = nullptr;`
- L95 _public member_ `bool bEnableFootLocking = true;`
- L97 _public member_ `TSharedPtr<FBodyTrackerDataInterface> BodyTrackerData;`

#### struct `IMetaHumanBodyTrackerInterface::FBodyTrackerOutputParams`  
`struct FBodyTrackerOutputParams`  
_L100-105_
- L102 _public member_ `FString AnimationPinName;`
- L103 _public member_ `TSharedPtr<FBodyTrackerDataInterface> BodyTrackerData;`
- L104 _public member_ `int32 BodyTrackerFinalPipelineStage = 0;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API METAHUMANBODYTRACKERINTERFACE_API`
