# Plugins / MetaHumanFaceContourTracker

- module root: `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanFaceContourTracker`
- headers: 2; symbols: 62
- symbol kinds: class=2, macro=1, member=36, prototype=23
- PrivateDependencyModuleNames: Engine, MetaHumanCore, Projects, Slate, SlateCore
- PublicDependencyModuleNames: Core, CoreUObject, NNE

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanFaceContourTracker/Public/MetaHumanFaceContourTrackerAsset.h` (Public)


#### class `UMetaHumanFaceContourTrackerAsset`  
`class UMetaHumanFaceContourTrackerAsset : public UObject`  
_L23-136_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: Face Contour Tracker Asset Contains trackers for different facial features Used in MetaHuman Identity and Performance assets
- L28 _public prototype_ `static TObjectPtr<UMetaHumanFaceContourTrackerAsset> LoadDefaultTracker();`
- L32 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L33 _public prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& InTransactionEvent) override;`
- L35 _public prototype_ `virtual void PostLoad() override;`
- L39 _public member_ `TSharedPtr<UE::NNE::IModelInstanceGPU> FaceDetector;` — `UE_DEPRECATED(5.8, "FaceDetector is deprecated. Use FaceDetectorModel instead.")`
- L41 _public member_ `TSharedPtr<UE::NNE::IModelInstanceGPU> FullFaceTracker;` — `UE_DEPRECATED(5.8, "FullFaceTracker is deprecated. Use FullFaceTrackerModel instead.")`
- L43 _public member_ `TSharedPtr<UE::NNE::IModelInstanceGPU> BrowsDenseTracker;` — `UE_DEPRECATED(5.8, "BrowsDenseTracker is deprecated. Use BrowsDenseTrackerModel instead.")`
- L45 _public member_ `TSharedPtr<UE::NNE::IModelInstanceGPU> EyesDenseTracker;` — `UE_DEPRECATED(5.8, "EyesDenseTracker is deprecated. Use EyesDenseTrackerModel instead.")`
- L47 _public member_ `TSharedPtr<UE::NNE::IModelInstanceGPU> NasioLabialsDenseTracker;` — `UE_DEPRECATED(5.8, "NasioLabialsDenseTracker is deprecated. Use NasioLabialsDenseTrackerModel instead.")`
- L49 _public member_ `TSharedPtr<UE::NNE::IModelInstanceGPU> MouthDenseTracker;` — `UE_DEPRECATED(5.8, "MouthDenseTracker is deprecated. Use MouthDenseTrackerModel instead.")`
- L51 _public member_ `TSharedPtr<UE::NNE::IModelInstanceGPU> LipzipDenseTracker;` — `UE_DEPRECATED(5.8, "LipzipDenseTracker is deprecated. Use LipzipDenseTrackerModel instead.")`
- L53 _public member_ `TSharedPtr<UE::NNE::IModelInstanceGPU> ChinDenseTracker;` — `UE_DEPRECATED(5.8, "ChinDenseTracker is deprecated. Use ChinDenseTrackerModel instead.")`
- L55 _public member_ `TSharedPtr<UE::NNE::IModelInstanceGPU> TeethDenseTracker;` — `UE_DEPRECATED(5.8, "TeethDenseTracker is deprecated. Use TeethDenseTrackerModel instead.")`
- L57 _public member_ `TSharedPtr<UE::NNE::IModelInstanceGPU> TeethConfidenceTracker;` — `UE_DEPRECATED(5.8, "TeethConfidenceTracker is deprecated. Use TeethConfidenceTrackerModel instead.")`
- L59 _public member_ `TSharedPtr<UE::NNE::IModelInstanceRunSync> FaceDetectorModel;`
- L60 _public member_ `TSharedPtr<UE::NNE::IModelInstanceRunSync> FullFaceTrackerModel;`
- L61 _public member_ `TSharedPtr<UE::NNE::IModelInstanceRunSync> BrowsDenseTrackerModel;`
- L62 _public member_ `TSharedPtr<UE::NNE::IModelInstanceRunSync> EyesDenseTrackerModel;`
- L63 _public member_ `TSharedPtr<UE::NNE::IModelInstanceRunSync> NasioLabialsDenseTrackerModel;`
- L64 _public member_ `TSharedPtr<UE::NNE::IModelInstanceRunSync> MouthDenseTrackerModel;`
- L65 _public member_ `TSharedPtr<UE::NNE::IModelInstanceRunSync> LipzipDenseTrackerModel;`
- L66 _public member_ `TSharedPtr<UE::NNE::IModelInstanceRunSync> ChinDenseTrackerModel;`
- L67 _public member_ `TSharedPtr<UE::NNE::IModelInstanceRunSync> TeethDenseTrackerModel;`
- L68 _public member_ `TSharedPtr<UE::NNE::IModelInstanceRunSync> TeethConfidenceTrackerModel;`
- L70 _public prototype_ `void SetNNEBackend(const FString& InNNEBackend);`
- L71 _public prototype_ `FString GetNNEBackend(void) const;`
- L76 _public member_ `TSoftObjectPtr<UNNEModelData> FaceDetectorModelData;` — `UPROPERTY(EditAnywhere, Category = TrackerModels)`
- L79 _public member_ `TSoftObjectPtr<UNNEModelData> FullFaceTrackerModelData;` — `UPROPERTY(EditAnywhere, Category = TrackerModels)`
- L82 _public member_ `TSoftObjectPtr<UNNEModelData> BrowsDenseTrackerModelData;` — `UPROPERTY(EditAnywhere, Category = TrackerModels)`
- L85 _public member_ `TSoftObjectPtr<UNNEModelData> EyesDenseTrackerModelData;` — `UPROPERTY(EditAnywhere, Category = TrackerModels)`
- L88 _public member_ `TSoftObjectPtr<UNNEModelData> NasioLabialsDenseTrackerModelData;` — `UPROPERTY(EditAnywhere, Category = TrackerModels)`
- L91 _public member_ `TSoftObjectPtr<UNNEModelData> MouthDenseTrackerModelData;` — `UPROPERTY(EditAnywhere, Category = TrackerModels)`
- L94 _public member_ `TSoftObjectPtr<UNNEModelData> LipzipDenseTrackerModelData;` — `UPROPERTY(EditAnywhere, Category = TrackerModels)`
- L97 _public member_ `TSoftObjectPtr<UNNEModelData> ChinDenseTrackerModelData;` — `UPROPERTY(EditAnywhere, Category = TrackerModels)`
- L100 _public member_ `TSoftObjectPtr<UNNEModelData> TeethDenseTrackerModelData;` — `UPROPERTY(EditAnywhere, Category = TrackerModels)`
- L103 _public member_ `TSoftObjectPtr<UNNEModelData> TeethConfidenceTrackerModelData;` — `UPROPERTY(EditAnywhere, Category = TrackerModels)`
- L107 _public prototype_ `bool CanProcess() const;`
- L109 _public prototype_ `void LoadTrackers(bool bInShowProgressNotification, TFunction<void(bool)>&& Callback);`
- L111 _public prototype_ `void CancelLoadTrackers();`
- L113 _public prototype_ `bool LoadTrackersSynchronous();`
- L115 _public prototype_ `bool IsLoadingTrackers() const;`
- L119 _private member_ `TArray<TObjectPtr<UNNEModelData>> LoadedTrackerModelData;` — `UPROPERTY(Transient)`
- L121 _private member_ `TArray<TSharedPtr<UE::NNE::IModelInstanceRunSync>> LoadedTrackerModels;`
- L123 _private member_ `FString NNEBackend;`
- L125 _private member_ `TWeakPtr<class SNotificationItem> LoadNotification;`
- L126 _private member_ `TSharedPtr<struct FStreamableHandle> TrackersLoadHandle;`
- L128 _private prototype_ `TArray<TSoftObjectPtr<UNNEModelData>> GetTrackerModelData() const;`
- L129 _private prototype_ `TArray<TSharedPtr<UE::NNE::IModelInstanceRunSync>> GetTrackerModels() const;`
- L130 _private prototype_ `bool SetTrackerModels();`
- L132 _private prototype_ `TArray<FSoftObjectPath> GetTrackerModelDataAsSoftObjectPaths() const;`
- L133 _private prototype_ `bool AreTrackerModelsLoaded() const;`
- L135 _private prototype_ `bool CreateTrackerModels();`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API METAHUMANFACECONTOURTRACKER_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanFaceContourTracker/Public/MetaHumanFaceContourTrackerStyle.h` (Public)


#### class `FMetaHumanFaceContourTrackerStyle`  
`class FMetaHumanFaceContourTrackerStyle : public FSlateStyleSet`  
_L9-26_
- inherits: `FSlateStyleSet`
- desc: A Style set for MetaHuman Face Contour Tracker asset
- L13 _public prototype_ `virtual const FName& GetStyleSetName() const override;`
- L14 _public prototype_ `static const FMetaHumanFaceContourTrackerStyle& Get();`
- L16 _public prototype_ `static void ReloadTextures();`
- L18 _public prototype_ `static void Register();`
- L19 _public prototype_ `static void Unregister();`
- L23 _private prototype_ `FMetaHumanFaceContourTrackerStyle();`
- L25 _private member_ `static FName StyleName;`
