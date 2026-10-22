# Plugins / InterchangePipelines

- module root: `Plugins/Interchange/Runtime/Source/Pipelines`
- headers: 18; symbols: 794
- symbol kinds: class=19, delegate=2, enum=12, enumerator=44, function=50, macro=13, member=318, namespace=13, prototype=305, struct=13, typedef=5
- PrivateDependencyModuleNames: ApplicationCore, CinematicCamera, DeveloperSettings, Foliage, GLTFCore, GeometryCache, HairStrandsCore, ImageCore, InputCore, InterchangeImport, LevelSequence, MainFrame, PhysicsUtilities, Slate, SlateCore, TextureUtilitiesCommon, UnrealEd, VariantManagerContent
- PublicDependencyModuleNames: Core, CoreUObject, Engine, InterchangeCommon, InterchangeCore, InterchangeEngine, InterchangeFactoryNodes, InterchangeNodes

### `Plugins/Interchange/Runtime/Source/Pipelines/Private/InterchangePipelineLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogInterchangePipeline, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogInterchangePipeline, Log, All);`

### `Plugins/Interchange/Runtime/Source/Pipelines/Public/InterchangeGenericAnimationPipeline.h` (Public)


#### enum `EInterchangeAnimationRange`  
`enum class EInterchangeAnimationRange : uint8`  
_L23-32_
- reflection: `UENUM(BlueprintType)`
- desc: Animation length type when importing.
- L26 _public enumerator_ `Timeline UMETA(DisplayName = "Source Timeline")` — This option imports the range of frames based on timeline definition in the source.
- L28 _public enumerator_ `Animated UMETA(DisplayName = "Animated Time")` — This option imports the range of frames that have animation.
- L30 _public enumerator_ `SetRange UMETA(DisplayName = "Set Range")` — This option imports the range of frames specified by "FrameImportRange".
- L31 _public enumerator_ `MAX`

#### enum `EInterchangeFrameAlignment`  
`enum class EInterchangeFrameAlignment : uint8`  
_L35-41_
- reflection: `UENUM(BlueprintType)`
- L37 _public enumerator_ `None UMETA(DisplayName = "None")`
- L38 _public enumerator_ `SnapToFloor UMETA(DisplayName = "Snap To Floor")`
- L39 _public enumerator_ `SnapToClosest UMETA(DisplayName = "Snap To Closest Frame Boundary")`
- L40 _public enumerator_ `SnapToCeiling UMETA(DisplayName = "Snap To Ceiling")`

#### class `UInterchangeGenericAnimationPipeline`  
`class UInterchangeGenericAnimationPipeline : public UInterchangePipelineBase`  
_L44-172_
- reflection: `UCLASS(MinimalAPI, BlueprintType, hidedropdown)`
- inherits: `UInterchangePipelineBase`
- L51 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L54 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L56 _public prototype_ `static FString GetPipelineCategory(UClass* AssetClass);`
- L60 _public member_ `TWeakObjectPtr<UInterchangeGenericCommonSkeletalMeshesAndAnimationsProperties> CommonSkeletalMeshesAndAnimationsProperties;` — `UPROPERTY(Transient)` — Common SkeletalMeshes And Animations Properties Settings Pointer
- L64 _public member_ `TWeakObjectPtr<UInterchangeGenericCommonMeshesProperties> CommonMeshesProperties;` — `UPROPERTY(Transient)` — Common Meshes Properties Settings Pointer
- L69 _public member_ `bool bImportAnimations = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")` — If enabled, import all animation assets found in the source.
- L73 _public member_ `bool bImportBoneTracks = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (EditCondition = "bImportAnimations"))` — Import bone transform tracks. If false, this will discard any bone transform tracks.
- L77 _public member_ `EInterchangeAnimationRange AnimationRange = EInterchangeAnimationRange::Timeline;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (EditCondition = "bImportAnimations && bImportBoneTracks", DisplayName = "Animation Length"))` — Determines which animation range to import: the range defined at export, the range of frames with animation, or a manually defined range.
- L81 _public member_ `FInt32Interval FrameImportRange = FInt32Interval(0, 0);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (UIMin = 0, ClampMin = 0))` — The frame range used when the Animation Length setting is set to Set Range.
- L85 _public member_ `bool bUse30HzToBakeBoneAnimation = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (EditCondition = "bImportAnimations && bImportBoneTracks", ToolTip = "If enabled, samples all animation curves to 30 FPS"))` — If enabled, samples all imported animation data at the default rate of 30 FPS.
- L89 _public member_ `int32 CustomBoneAnimationSampleRate = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (EditCondition = "bImportAnimations && bImportBoneTracks && !bUse30HzToBakeBoneAnimation", ToolTip = "Sample fbx animation data at the specified sample rate, 0 find automaticaly the best sample rate", ClampMin = 0, UIMin = 0, ClampMax = 48000, UIMax = 60))` — Use this option to specify a sample rate for the imported animation, a value of 0 use the best matching sample rate.
- L93 _public member_ `EInterchangeFrameAlignment FrameAlignment = EInterchangeFrameAlignment::None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (EditCondition = "bImportAnimations && bImportBoneTracks"))` — Frame alignment settings
- L96 _public member_ `bool bSnapToClosestFrameBoundary_DEPRECATED = false;` — `UPROPERTY()`
- L100 _public member_ `bool bImportCustomAttribute = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (SubCategory = "Curves", EditCondition = "bImportAnimations", DisplayName = "Import Attributes as Curves or Animation Attributes"))` — If enabled, import node attributes as either Animation Curves or Animation Attributes.
- L104 _public member_ `bool bAddCurveMetadataToSkeleton_DEPRECATED = true;` — `UPROPERTY()` — Determines whether to automatically add curve metadata to an animation's skeleton. If this setting is disabled, curve metadata will be added to skeletal meshes for morph targets, but no metadata entry will be created for general curves.
- L108 _public member_ `bool bSetMaterialDriveParameterOnCustomAttribute = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (SubCategory = "Curves", EditCondition = "bImportAnimations && bImportCustomAttribute", DisplayName = "Set Material Curve Type"))` — Set the material curve type for all custom attributes.
- L112 _public member_ `TArray<FString> MaterialCurveSuffixes = {TEXT("_mat` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (SubCategory = "Curves", EditCondition = "bImportAnimations && bImportCustomAttribute && bSetMaterialDriveParameterOnCustomAttribute", DisplayName = "Material Curve Suffixes"))` — Set the Material Curve Type for custom attributes that have the specified suffixes. This setting is not used if the Set Material Curve Type setting is enabled.
- L116 _public member_ `bool bRemoveCurveRedundantKeys = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (SubCategory = "Curves", EditCondition = "bImportAnimations && bImportCustomAttribute", DisplayName = "Remove Redundant Keys"))` — When importing custom attributes as curves, remove redundant keys.
- L120 _public member_ `bool bDoNotImportCurveWithZero = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (SubCategory = "Curves", EditCondition = "bImportAnimations && bImportCustomAttribute", DisplayName = "Do not import curves with only 0 values"))` — When importing a custom attribute or morph target as a curve, only import if it has a value other than zero. This avoids adding extra curves to evaluate.
- L124 _public member_ `bool bDeleteExistingNonCurveCustomAttributes = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (SubCategory = "Curves", EditCondition = "bImportAnimations && bImportCustomAttribute", DisplayName = "Delete existing Animation Attributes"))` — If enabled, all previous node attributes imported as Animation Attributes will be deleted when doing a reimport.
- L128 _public member_ `bool bDeleteExistingCustomAttributeCurves = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (SubCategory = "Curves", EditCondition = "bImportAnimations && bImportCustomAttribute", DisplayName = "Delete existing Animation Curves"))` — If enabled, all previous node attributes imported as Animation Curves will be deleted when doing a reimport.
- L132 _public member_ `bool bDeleteExistingMorphTargetCurves = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (SubCategory = "Curves", EditCondition = "bImportAnimations && bImportCustomAttribute", DisplayName = "Delete existing Morph Target Curves"))` — If enabled, all previous morph target curves will be deleted when doing a reimport.
- L136 _public member_ `FString SourceAnimationName;` — `UPROPERTY()` — Name of the source animation that was imported. This is used to reimport correct animation from the translated source.
- L138 _public prototype_ `virtual void AdjustSettingsForContext(const FInterchangePipelineContextParams& ContextParams) override;`
- L142 _public prototype_ `virtual bool IsPropertyChangeNeedRefresh(const FPropertyChangedEvent& PropertyChangedEvent) const override;`
- L144 _public prototype_ `virtual void GetSupportAssetClasses(TArray<UClass*>& PipelineSupportAssetClasses) const override;`
- L148 _public prototype_ `void ImplementUseSourceNameForAssetOptionAnimSequence(bool bUseSourceNameForAsset, const FString& AssetName);`
- L152 _protected prototype_ `virtual void ExecutePipeline(UInterchangeBaseNodeContainer* InBaseNodeContainer, const TArray<UInterchangeSourceData*>& InSourceDatas, const FString& ContentBasePath) override;`
- L154 _protected function_ `virtual bool CanExecuteOnAnyThread(EInterchangePipelineTask PipelineTask) override`
- L161 _private prototype_ `void CreateLevelSequenceFactoryNode(UInterchangeAnimationTrackSetNode& Node);`
- L163 _private prototype_ `void CreateAnimSequenceFactoryNode(UInterchangeSkeletalAnimationTrackNode& Node);`
- L167 _private member_ `bool bSceneImport = false;` — `UPROPERTY()` — Set as a property to carry this value over during a duplicate
- L169 _private member_ `UInterchangeBaseNodeContainer* BaseNodeContainer = nullptr;`
- L170 _private member_ `TArray<const UInterchangeSourceData*> SourceDatas;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API INTERCHANGEPIPELINES_API`

### `Plugins/Interchange/Runtime/Source/Pipelines/Public/InterchangeGenericAssetsPipeline.h` (Public)


#### class `UInterchangeGenericAssetsPipeline`  
`class UInterchangeGenericAssetsPipeline : public UInterchangePipelineBase`  
_L42-236_
- reflection: `UCLASS(MinimalAPI, BlueprintType, editinlinenew)`
- inherits: `UInterchangePipelineBase`
- desc: This pipeline is the generic option for all types of meshes. It should be called before specialized mesh pipelines like the generic static mesh or skeletal mesh pipelines. All import options that are shared between mesh types should be added here.
- L47 _public prototype_ `UInterchangeGenericAssetsPipeline();`
- L53 _public member_ `FString PipelineDisplayName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common", meta = (StandAlonePipelineProperty = "True", PipelineInternalEditionData = "True"))` — The name of the pipeline that will be display in the import dialog.
- L57 _public member_ `EReimportStrategyFlags ReimportStrategy = EReimportStrategyFlags::ApplyNoProperties;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common", meta = (AdjustPipelineAndRefreshDetailOnChange = "True"))` — Set the reimport strategy.
- L61 _public member_ `bool bUseSourceNameForAsset = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common")` — If enabled, and the Asset Name setting is empty, and there is only one asset and one source, the imported asset is given the same name as the source data.
- L65 _public member_ `bool bSceneNameSubFolder = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common")` — Create an additional Content folder inside of the chosen import directory, and name it after the imported scene
- L69 _public member_ `bool bAssetTypeSubFolders = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common")` — Group the assets according to their type into additional Content folders created on the import directory (/Materials, /StaticMeshes, /SkeletalMeshes, etc.)
- L73 _public member_ `FString AssetName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common", meta = (StandAlonePipelineProperty = "True"))` — If set, and there is only one asset and one source, the imported asset is given this name.
- L77 _public member_ `FVector ImportOffsetTranslation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common", meta = (DisplayName = "Offset Translation"))` — Translation offset applied to meshes and animations.
- L81 _public member_ `FRotator ImportOffsetRotation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common", meta = (DisplayName = "Offset Rotation"))` — Rotation offset applied to meshes and animations.
- L85 _public member_ `float ImportOffsetUniformScale = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common", meta = (DisplayName = "Offset Uniform Scale"))` — Uniform scale offset applied to meshes and animations.
- L89 _public member_ `TObjectPtr<UInterchangeGenericCommonMeshesProperties> CommonMeshesProperties;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Instanced, Category = "Common Meshes")` — COMMON_MESHES_CATEGORY Properties //////
- L93 _public member_ `TObjectPtr<UInterchangeGenericCommonSkeletalMeshesAndAnimationsProperties> CommonSkeletalMeshesAndAnimationsProperties;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Instanced, Category = "Common Skeletal Meshes and Animations")` — COMMON_SKELETAL_ANIMATIONS_CATEGORY //////
- L97 _public member_ `TObjectPtr<UInterchangeGenericMeshPipeline> MeshPipeline;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Instanced, Category = "Meshes")` — MESHES_CATEGORY Properties //////
- L101 _public member_ `TObjectPtr<UInterchangeGenericAnimationPipeline> AnimationPipeline;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Instanced, Category = "Animation")` — ANIMATIONS_CATEGORY Properties //////
- L105 _public member_ `TObjectPtr<UInterchangeGenericMaterialPipeline> MaterialPipeline;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Instanced, Category = "Materials")` — MATERIALS_CATEGORY Properties //////
- L109 _public member_ `TObjectPtr<UInterchangeGenericGroomPipeline> GroomPipeline;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Instanced, Category = "Grooms")` — GROOMS_CATEGORY Properties //////
- L113 _public member_ `FString SceneNameFolderPrefix;` — `UPROPERTY(meta = (PipelineInternalEditionData = "True"))` — Internal property to cache the name of the sub-folder prefix for use during reimport
- L115 _public prototype_ `virtual void PreDialogCleanup(const FName PipelineStackName) override;`
- L117 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L119 _public prototype_ `virtual void PostLoad() override;`
- L121 _public prototype_ `virtual bool IsSettingsAreValid(TOptional<FText>& OutInvalidReason) const override;`
- L124 _public prototype_ `virtual void AdjustSettingsForContext(const FInterchangePipelineContextParams& ContextParams) override;`
- L126 _public prototype_ `virtual void FilterPropertiesFromTranslatedData(UInterchangeBaseNodeContainer* InBaseNodeContainer) override;`
- L128 _public prototype_ `virtual bool IsPropertyChangeNeedRefresh(const FPropertyChangedEvent& PropertyChangedEvent) const override;`
- L130 _public prototype_ `virtual void GetSupportAssetClasses(TArray<UClass*>& PipelineSupportAssetClasses) const override;`
- L133 _public prototype_ `virtual TArray<FInterchangeConflictInfo> GetConflictInfos(UObject* ReimportObject, UInterchangeBaseNodeContainer* InBaseNodeContainer, UInterchangeSourceData* SourceData) override;`
- L135 _public prototype_ `virtual void ShowConflictDialog(const FGuid& ConflictUniqueId) override;`
- L137 _public function_ `virtual bool IsScripted() override`
- L143 _public prototype_ `virtual bool GetPropertyPossibleValues(const FName PropertyPath, TArray<FString>& PossibleValues) override;`
- L160 _public member_ `bool bImportOnlyAnimationAdjusted = false;` — `UPROPERTY(meta = (AlwaysResetToDefault = "True"))` — We need to store the adjusted import only animation boolean to restore it in PreDialogCleanup
- L164 _protected prototype_ `virtual void ExecutePipeline(UInterchangeBaseNodeContainer* InBaseNodeContainer, const TArray<UInterchangeSourceData*>& InSourceDatas, const FString& ContentBasePath) override;`
- L165 _protected prototype_ `virtual void ExecutePostFactoryPipeline(const UInterchangeBaseNodeContainer* BaseNodeContainer, const FString& NodeKey, UObject* CreatedAsset, bool bIsAReimport) override;`
- L166 _protected prototype_ `virtual void ExecutePostImportPipeline(const UInterchangeBaseNodeContainer* BaseNodeContainer, const FString& NodeKey, UObject* CreatedAsset, bool bIsAReimport) override;`
- L168 _protected function_ `virtual bool CanExecuteOnAnyThread(EInterchangePipelineTask PipelineTask) override`
- L176 _protected prototype_ `virtual void SetReimportSourceIndex(UClass* ReimportObjectClass, const int32 SourceFileIndex) override;`
- L182 _private prototype_ `void CreateMaterialConflict(UStaticMesh* StaticMesh, USkeletalMesh* SkeletalMesh, UInterchangeBaseNodeContainer* TransientBaseNodeContainer);`
- L183 _private prototype_ `void InternalRecursiveFillJointsFromReferenceSkeleton(TSharedPtr<FSkeletonJoint> ParentJoint, TMap<FString, TSharedPtr<FSkeletonJoint>>& Joints, const int32 BoneIndex, const FReferenceSkeleton& ReferenceSkeleton);`
- L184 _private prototype_ `void InternalRecursiveFillJointsFromNodeContainer(TSharedPtr<FSkeletonJoint> ParentJoint, TMap<FString, TSharedPtr<FSkeletonJoint>>& Joints, const FString& JoinUid, const UInterchangeBaseNodeContainer* BaseNodeContainer, const bool bConvertStaticToSkeletalActive);`
- L185 _private prototype_ `void CreateSkeletonConflict(USkeleton* SpecifiedSkeleton, USkeletalMesh* SkeletalMesh, UInterchangeBaseNodeContainer* TransientBaseNodeContainer);`
- L191 _private prototype_ `void ImplementUseSourceNameForAssetOption(UInterchangeBaseNodeContainer* InBaseNodeContainer, const TArray<UInterchangeSourceData*>& InSourceDatas);` — Implement pipeline option bUseSourceNameForAsset
- L196 _private prototype_ `void AddMetaData(UObject* CreatedAsset, const UInterchangeBaseNode* Node);` — Adds the user defined attributes (UInterchangeUserDefinedAttributesAPI) to the package meta data (FMetaData) for WITH_EDITORONLY_DATA, and add UAssetUserData for AActors.
- L216 _private member_ `FMaterialConflictData MaterialConflictData;`
- L232 _private member_ `FSkeletonConflictData SkeletonConflictData;`
- L235 _private member_ `bool bHasNotify_MetaDataAttributeKeyNameTooLong = false;` — Make sure we notify the user only once for metadata attribute key name too long

#### struct `UInterchangeGenericAssetsPipeline::FSkeletonJoint`  
`struct FSkeletonJoint : public TSharedFromThis<FSkeletonJoint>`  
_L146-156_
- inherits: `TSharedFromThis<FSkeletonJoint>`
- L148 _public member_ `FString JointName;`
- L149 _public member_ `bool bAdded = false;`
- L150 _public member_ `bool bRemoved = false;`
- L151 _public member_ `bool bMatch = false;`
- L152 _public member_ `bool bConflict = false;`
- L153 _public member_ `bool bChildConflict = false;`
- L154 _public member_ `TSharedPtr<FSkeletonJoint> Parent;`
- L155 _public member_ `TArray<TSharedPtr<FSkeletonJoint>> Children;`

#### struct `UInterchangeGenericAssetsPipeline::FMaterialConflictData`  
`struct FMaterialConflictData`  
_L198-215_
- L200 _public member_ `FGuid ConflictUniqueId;`
- L201 _public member_ `TArray<FString> AssetMaterialNames;`
- L202 _public member_ `TArray<FString> ImportMaterialNames;`
- L203 _public member_ `TArray<int32> MatchMaterialIndexes;`
- L204 _public member_ `UObject* ReimportObject = nullptr;`
- L205 _public member_ `const FText DialogTitle = NSLOCTEXT("UInterchang`
- L207 _public function_ `void Reset()`

#### struct `UInterchangeGenericAssetsPipeline::FSkeletonConflictData`  
`struct FSkeletonConflictData`  
_L218-231_
- L220 _public member_ `FGuid ConflictUniqueId;`
- L221 _public member_ `TMap<FString, TSharedPtr<FSkeletonJoint>> Joints;`
- L222 _public member_ `UObject* ReimportObject = nullptr;`
- L223 _public member_ `const FText DialogTitle = NSLOCTEXT("UInterchang`
- L225 _public function_ `void Reset()`

#### class `SInterchangeGenericAssetMaterialConflictWidget`  
`class SInterchangeGenericAssetMaterialConflictWidget : public SInterchangeBaseConflictWidget`  
_L238-286_
- inherits: `SInterchangeBaseConflictWidget`
- L250 _public member_ `static const FName NAME_Import;`
- L251 _public member_ `static const FName NAME_Asset;`
- L253 _public member_ `static const FSlateColor SlateColorFullConflict;`
- L254 _public member_ `static const FSlateColor SlateColorSubConflict;`
- L256 _public function_ `SLATE_BEGIN_ARGS(SInterchangeGenericAssetMaterialConflictWidget) : _AssetMaterialNames() , _ImportMaterialNames() , _MatchMaterialIndexes() , _ReimportObject(nullptr)`
- L262 _public prototype_ `SLATE_ARGUMENT(TArray<FString>, AssetMaterialNames) SLATE_ARGUMENT(TArray<FString>, ImportMaterialNames) SLATE_ARGUMENT(TArray<int32>, MatchMaterialIndexes) SLATE_ARGUMENT(UObject*, ReimportObject) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L269 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L271 _public prototype_ `FReply OnDone();`
- L273 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L277 _protected prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FListItem> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L279 _protected member_ `TArray<FString> AssetMaterialNames;`
- L280 _protected member_ `TArray<FString> ImportMaterialNames;`
- L281 _protected member_ `TArray<int32> MatchMaterialIndexes;`
- L282 _protected member_ `UObject* ReimportObject = nullptr;`
- L284 _protected member_ `TArray<TSharedPtr<FListItem>> RowItems;`
- L285 _protected member_ `TSharedPtr<SListView<TSharedPtr<FListItem>>> MaterialList;`

#### struct `SInterchangeGenericAssetMaterialConflictWidget::FListItem`  
`struct FListItem`  
_L242-248_
- L244 _public member_ `FString ImportName;`
- L245 _public member_ `int32 bMatched = INDEX_NONE;`
- L246 _public member_ `FString AssetMatchedName;`
- L247 _public member_ `FString AssetName;`

#### enum `EInterchangeSkeletonCompareSection`  
`enum class EInterchangeSkeletonCompareSection : uint8`  
_L288-293_
- L290 _public enumerator_ `Skeleton = 0`
- L291 _public enumerator_ `References`
- L292 _public enumerator_ `Count`

#### class `SInterchangeGenericAssetSkeletonConflictWidget`  
`class SInterchangeGenericAssetSkeletonConflictWidget : public SInterchangeBaseConflictWidget`  
_L295-371_
- inherits: `SInterchangeBaseConflictWidget`
- L297 _private typedef_ `using FExpansionPredicate = TDelegate<bool(TSharedPtr<UInterchangeGenericAssetsPipeline::FSkeletonJoint>)>;`
- L301 _public function_ `SLATE_BEGIN_ARGS(SInterchangeGenericAssetSkeletonConflictWidget) : _AssetReferencingSkeleton() , _Joints() , _ReimportObject(nullptr)`
- L314 _public prototype_ `void Construct(const FArguments& InArgs);`
- L315 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L317 _public function_ `FReply OnDone()`
- L327 _public function_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override`
- L336 _public function_ `SInterchangeGenericAssetSkeletonConflictWidget()`
- L340 _private member_ `TArray<TSharedPtr<FString>> AssetReferencingSkeleton;`
- L341 _private member_ `TArray<TSharedPtr<UInterchangeGenericAssetsPipeline::FSkeletonJoint>> Joints;`
- L342 _private member_ `UObject* ReimportObject;`
- L346 _private prototype_ `void OnSetExpansionRecursive(TSharedPtr<UInterchangeGenericAssetsPipeline::FSkeletonJoint> SkeletonJoint, bool bShouldBeExpanded, const FExpansionPredicate Predicate = FExpansionPredicate());` — Recursive Expansion
- L351 _private member_ `bool bShowSectionFlag[(uint8)EInterchangeSkeletonCompareSection::Count];` — Collapse generic
- L352 _private prototype_ `FReply OnExpandToConflict();`
- L353 _private prototype_ `FReply SetSectionVisible(EInterchangeSkeletonCompareSection SectionIndex);`
- L354 _private prototype_ `EVisibility IsSectionVisible(EInterchangeSkeletonCompareSection SectionIndex);`
- L355 _private prototype_ `const FSlateBrush* GetCollapsableArrow(EInterchangeSkeletonCompareSection SectionIndex) const;`
- L361 _private member_ `TSharedPtr<STreeView<TSharedPtr<UInterchangeGenericAssetsPipeline::FSkeletonJoint>>> CompareTree;` — Skeleton Data
- L364 _private prototype_ `TSharedPtr<SWidget> ConstructSkeletonComparison();` — Construct slate
- L365 _private prototype_ `TSharedPtr<SWidget> ConstructSkeletonReference();`
- L367 _private prototype_ `TSharedRef<ITableRow> OnGenerateRowCompareTreeView(TSharedPtr<UInterchangeGenericAssetsPipeline::FSkeletonJoint> RowData, const TSharedRef<STableViewBase>& Table);` — Slate events
- L368 _private prototype_ `void OnGetChildrenRowCompareTreeView(TSharedPtr<UInterchangeGenericAssetsPipeline::FSkeletonJoint> InParent, TArray< TSharedPtr<UInterchangeGenericAssetsPipeline::FSkeletonJoint> >& OutChildren);`
- L369 _private prototype_ `TSharedRef<ITableRow> OnGenerateRowAssetReferencingSkeleton(TSharedPtr<FString> InItem, const TSharedRef<STableViewBase>& OwnerTable);`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API INTERCHANGEPIPELINES_API`

### `Plugins/Interchange/Runtime/Source/Pipelines/Public/InterchangeGenericAssetsPipelineSharedSettings.h` (Public)


#### enum `EInterchangeForceMeshType`  
`enum class EInterchangeForceMeshType : uint8`  
_L26-36_
- reflection: `UENUM(BlueprintType)`
- desc: Enumerates the options for importing all meshes as one type.
- L29 _public enumerator_ `IFMT_None UMETA(DisplayName = "None")` — Import both static meshes and skeletal meshes from the source without converting them.
- L31 _public enumerator_ `IFMT_StaticMesh UMETA(DisplayName = "Static Mesh")` — Import all meshes from the source as static meshes.
- L33 _public enumerator_ `IFMT_SkeletalMesh UMETA(DisplayName = "Skeletal Mesh")` — Import all meshes from the source as skeletal meshes.
- L35 _public enumerator_ `IFMT_MAX`

#### enum `EInterchangeVertexColorImportOption`  
`enum class EInterchangeVertexColorImportOption : uint8`  
_L39-49_
- reflection: `UENUM(BlueprintType)`
- L42 _public enumerator_ `IVCIO_Replace UMETA(DisplayName = "Replace")` — Import the mesh using the vertex colors from the translated source.
- L44 _public enumerator_ `IVCIO_Ignore UMETA(DisplayName = "Ignore")` — Ignore vertex colors from the translated source. In case of a reimport, keep the existing mesh vertex colors.
- L46 _public enumerator_ `IVCIO_Override UMETA(DisplayName = "Override")` — Override all vertex colors with the specified color.
- L48 _public enumerator_ `IVCIO_MAX`

#### class `UInterchangeGenericCommonMeshesProperties`  
`class UInterchangeGenericCommonMeshesProperties : public UInterchangePipelineBase`  
_L53-180_
- reflection: `UCLASS(MinimalAPI, BlueprintType, hidedropdown)`
- inherits: `UInterchangePipelineBase`
- L58 _public function_ `static FString GetPipelineCategory(UClass* AssetClass)`
- L71 _public member_ `EInterchangeForceMeshType ForceAllMeshAsType = EInterchangeForceMeshType::IFMT_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common Meshes", meta = (SubCategory = "Conversion"))` — If set, imports all meshes in the source as either static meshes or skeletal meshes. For skeletal meshes the conversion will happen only if there is no skinned meshes. Mixing rigid skeletal mesh with skinned mesh is not good and will result in multiple skeletal meshes.
- L75 _public member_ `bool bConvertStaticsWithAnimatedTransformToSkeletals = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common Meshes", meta = (SubCategory = "Conversion", editcondition = "ForceAllMeshAsType == EInterchangeForceMeshType::IFMT_None"))` — If enabled, and some static mesh transforms are animated, the pipeline will convert the static mesh into a rigid skeletal mesh.
- L79 _public member_ `bool bConvertStaticsWithMorphTargetsToSkeletals = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common Meshes", meta = (SubCategory = "Conversion", editcondition = "ForceAllMeshAsType == EInterchangeForceMeshType::IFMT_None"))` — If enabled, all static meshes that have morph targets will be imported as skeletal meshes instead.
- L83 _public member_ `bool bConvertStaticsInBoneHierarchyToSkeletals = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common Meshes", meta = (SubCategory = "Conversion", editcondition = "ForceAllMeshAsType == EInterchangeForceMeshType::IFMT_None"))` — If enabled, all static meshes nested in bone hierarchies will be imported as skeletal meshes instead.
- L91 _public member_ `bool bSingleBoneSkeleton = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common Meshes", meta = (SubCategory = "Conversion", editcondition = "ForceAllMeshAsType == EInterchangeForceMeshType::IFMT_SkeletalMesh"))` — If enabled, converted static meshes to skeletal meshes will use a skeleton with a unique bone at the geometry origin. Otherwise, the bone structure is determined by the model hierarchy. This setting is only used if Force All Meshes As Type setting is set to "Skeletal Mesh".
- L95 _public member_ `bool bImportLods = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common Meshes")` — If enabled, any existing LODs for meshes are imported. This setting is only used if the Bake Meshes setting is also enabled.
- L99 _public member_ `bool bBakeMeshes = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common Meshes")` — If enabled, meshes are baked with the scene instance hierarchy transform.
- L103 _public member_ `bool bBakePivotMeshes = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common Meshes", meta = (editcondition = "!bBakeMeshes"))` — If enabled, the inverse node rotation pivot will be apply to the mesh vertices. The pivot from the DCC will then be the origin of the mesh.
- L107 _public member_ `bool bKeepSectionsSeparate = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common Meshes")` — If checked, sections with matching materials are kept separate and will not get combined.
- L111 _public member_ `EInterchangeVertexColorImportOption VertexColorImportOption = EInterchangeVertexColorImportOption::IVCIO_Replace;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common Meshes")` — Specify how vertex colors should be imported.
- L115 _public member_ `FColor VertexOverrideColor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common Meshes")` — Specify an override color for use when the Vertex Color Import Option setting is set to Override.
- L123 _public member_ `bool bImportSockets = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common Meshes")` — If checked, import sockets StaticMesh, naming convention, SOCKET_MeshName_xx where "MeshName" should match the mesh you want to add socket to. The xx part is to add a unique id if many socket on the same mesh exist. SkeletalMesh, Naming convention, any leaf scene node under the skeleton root with a name starting with "SOCKET_" prefix.
- L127 _public member_ `bool bRecomputeNormals = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common Meshes", meta = (SubCategory = "Build"))` — If enabled, normals in the imported mesh are ignored and recomputed.
- L131 _public member_ `bool bRecomputeTangents = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common Meshes", meta = (SubCategory = "Build"))` — If enabled, tangents in the imported mesh are ignored and recomputed.
- L135 _public member_ `bool bUseMikkTSpace = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common Meshes", meta = (SubCategory = "Build", editcondition = "bRecomputeTangents"))` — If enabled, tangents are recomputed using MikkTSpace.
- L139 _public member_ `bool bComputeWeightedNormals = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common Meshes", meta = (SubCategory = "Build", editcondition = "bRecomputeNormals"))` — If enabled, normals are computed using the surface area and the corner angle of the triangle as a ratio.
- L143 _public member_ `bool bUseHighPrecisionTangentBasis = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common Meshes", meta = (SubCategory = "Build"))` — If true, tangents are stored at 16-bit vs 8-bit precision.
- L147 _public member_ `bool bUseFullPrecisionUVs = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common Meshes", meta = (SubCategory = "Build"))` — If true, UVs are stored at full floating-point precision.
- L151 _public member_ `bool bUseBackwardsCompatibleF16TruncUVs = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common Meshes", meta = (SubCategory = "Build"))` — If enabled, UVs are converted to 16-bit by a legacy truncation process instead of the default rounding process. This may avoid differences when reimporting older content.
- L155 _public member_ `bool bRemoveDegenerates = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common Meshes", meta = (SubCategory = "Build"))` — If true, degenerate triangles are removed.
- L159 _public member_ `bool bAutoDetectMeshType_DEPRECATED = true;` — `UE_DEPRECATED(5.8, "Use bConvertStaticsWithAnimatedTransformToSkeletals instead")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "bAutoDetectMeshType is deprecated. Use bConvertStaticsWithAnimatedTransformToSkeletals instead."))`
- L162 _public function_ `virtual bool IsPropertyChangeNeedRefresh(const FPropertyChangedEvent& PropertyChangedEvent) const override`

#### class `UInterchangeGenericCommonSkeletalMeshesAndAnimationsProperties`  
`class UInterchangeGenericCommonSkeletalMeshesAndAnimationsProperties : public UInterchangePipelineBase`  
_L183-256_
- reflection: `UCLASS(MinimalAPI, BlueprintType, hidedropdown)`
- inherits: `UInterchangePipelineBase`
- L188 _public function_ `static FString GetPipelineCategory(UClass* AssetClass)`
- L195 _public member_ `bool bImportOnlyAnimations = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common Skeletal Meshes and Animations")` — If enabled, only animations are imported from the source. You must also set a valid skeleton.
- L199 _public member_ `bool bTryAutoSelectSkeleton = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common Skeletal Meshes and Animations")` — If enabled, the pipeline will try to find a skeleton asset at the import location if available and set the skeleton property to use that asset. A new skeleton will be created if no skeleton asset is found.
- L203 _public member_ `TSoftObjectPtr<USkeleton> Skeleton;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common Skeletal Meshes and Animations", meta = (EditCondition = "!bTryAutoSelectSkeleton"))` — Skeleton to use for imported asset. When importing a skeletal mesh, leaving this as "None" will create a new skeleton. When importing an animation, this must be specified.
- L207 _public member_ `bool bUseT0AsRefPose = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common Skeletal Meshes and Animations", meta=(DisplayName="Use T0 As Ref Pose"))` — If enabled, skinned meshes will be rebind using the joints transform pose at frame 0 instead of being import with the bind pose.
- L211 _public member_ `bool bAddCurveMetadataToSkeleton = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common Skeletal Meshes and Animations")` — Determines whether to automatically add curve metadata to a skeleton. If this setting is disabled, curve metadata will be added to skeletal meshes for morph targets, but no metadata entry will be created for general curves.
- L215 _public member_ `bool bImportMeshesInBoneHierarchy_DEPRECATED = true;` — `UE_DEPRECATED(5.8, "Use UInterchangeGenericCommonMeshesProperties::bConvertStaticsInBoneHierarchyToSkeletals instead")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "bImportMeshesInBoneHierarchy is deprecated. Use UInterchangeGenericCommonMeshesProperties::bConvertStaticsInBoneHierarchyToSkeletals instead."))`
- L219 _public member_ `bool bConvertStaticsWithMorphTargetsToSkeletals_DEPRECATED = false;` — `UE_DEPRECATED(5.8, "Use UInterchangeGenericCommonMeshesProperties::bConvertStaticsWithMorphTargetsToSkeletals instead")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "bConvertStaticsWithMorphTargetsToSkeletals is deprecated. Use UInterchangeGenericCommonMeshesProperties::bConvertStaticsWithMorphTargetsToSkeletals instead."))`
- L222 _public function_ `virtual bool IsPropertyChangeNeedRefresh(const FPropertyChangedEvent& PropertyChangedEvent) const override`
- L239 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L242 _public function_ `virtual bool IsSettingsAreValid(TOptional<FText>& OutInvalidReason) const override`
- L253 _public prototype_ `UInterchangeSkeletonFactoryNode* CreateSkeletonFactoryNode(UInterchangeBaseNodeContainer* BaseNodeContainer, const FString& RootJointUid, const FString& SourceFileName );` — Create a UInterchangeSkeletonFactoryNode
- L255 _public prototype_ `bool IsSkeletonValid() const;`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API INTERCHANGEPIPELINES_API`

### `Plugins/Interchange/Runtime/Source/Pipelines/Public/InterchangeGenericAudioPipeline.h` (Public)


#### class `UInterchangeGenericAudioPipeline`  
`class UInterchangeGenericAudioPipeline : public UInterchangePipelineBase`  
_L14-72_
- reflection: `UCLASS(MinimalAPI, BlueprintType, EditInlineNew)`
- inherits: `UInterchangePipelineBase`
- desc: Basic pipeline for importing sound wave assets.
- L19 _public prototype_ `static FString GetPipelineCategory(UClass* AssetClass);`
- L23 _public member_ `FString PipelineDisplayName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio", meta = (StandAlonePipelineProperty = "True", PipelineInternalEditionData = "True"))` — The name of the pipeline that will be display in the import dialog.
- L27 _public member_ `bool bImportSounds = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")` — If enabled, imports all sounds found in the source.
- L29 _public function_ `virtual bool IsScripted() override`
- L35 _public prototype_ `virtual void AdjustSettingsForContext(const FInterchangePipelineContextParams& ContextParams) override;`
- L36 _public prototype_ `virtual void ExecutePipeline(UInterchangeBaseNodeContainer* InBaseNodeContainer, const TArray<UInterchangeSourceData*>& InSourceDatas, const FString& ContentBasePath) override;`
- L39 _public prototype_ `virtual bool IsPropertyChangeNeedRefresh(const FPropertyChangedEvent& PropertyChangedEvent) const override;`
- L41 _public prototype_ `virtual void FilterPropertiesFromTranslatedData(UInterchangeBaseNodeContainer* InBaseNodeContainer) override;`
- L43 _public prototype_ `virtual void GetSupportAssetClasses(TArray<UClass*>& PipelineSupportAssetClasses) const override;`
- L47 _protected function_ `virtual bool CanExecuteOnAnyThread(EInterchangePipelineTask PipelineTask) override`
- L58 _protected prototype_ `UInterchangeAudioSoundWaveFactoryNode* CreateSoundWaveFactoryNode(const UInterchangeAudioSoundWaveNode* SoundWaveNode);` — `UFUNCTION(BlueprintCallable, Category = "Interchange")` — Creates a SoundWaveFactoryNode for a given SoundWaveNode, if one doesn't already exist. Initializes the factory node, sets the custom directory path, and sets the target nodes on both the factory and sound wave nodes.
- L62 _private member_ `TObjectPtr<UInterchangeBaseNodeContainer> BaseNodeContainer;` — `UPROPERTY(Transient)`
- L65 _private member_ `TArray<const TObjectPtr<UInterchangeSourceData>> SourceDatas;` — `UPROPERTY(Transient)`
- L68 _private member_ `TArray<TObjectPtr<UInterchangeAudioSoundWaveNode>> SoundWaveNodes;` — `UPROPERTY(Transient)`
- L71 _private member_ `TArray<TObjectPtr<UInterchangeAudioSoundWaveFactoryNode>> SoundWaveFactoryNodes;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API INTERCHANGEPIPELINES_API`

### `Plugins/Interchange/Runtime/Source/Pipelines/Public/InterchangeGenericGroomPipeline.h` (Public)


#### class `UInterchangeGenericGroomPipeline`  
`class UInterchangeGenericGroomPipeline : public UInterchangePipelineBase`  
_L17-81_
- reflection: `UCLASS(MinimalAPI, BlueprintType, editinlinenew)`
- inherits: `UInterchangePipelineBase`
- L22 _public prototype_ `static FString GetPipelineCategory(UClass* AssetClass);`
- L26 _public member_ `FString PipelineDisplayName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grooms", meta = (StandAlonePipelineProperty = "True", PipelineInternalEditionData = "True"))` — The name of the pipeline that will be displayed in the import dialog.
- L30 _public member_ `bool bEnableGroomTypesImport = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grooms")` — If enabled, allow the import of groom-type assets.
- L34 _public member_ `bool bImportGrooms = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grooms", meta = (EditCondition = bEnableGroomTypesImport))` — If enabled, import all groom assets found in the source.
- L38 _public member_ `bool bImportGroomBindings = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grooms", meta = (EditCondition = bEnableGroomTypesImport))` — If enabled, import all groom bindings found in the source.
- L42 _public member_ `FHairGroupsInterpolation GroupInterpolationSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grooms")` — Settings that will be applied to all hair groups in the groom asset
- L46 _public member_ `bool bImportGroomCaches = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grooms", meta = (SubCategory = "Caches", EditCondition = bEnableGroomTypesImport))` — If enabled, import all groom caches found in the source.
- L50 _public member_ `FSoftObjectPath GroomAsset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grooms", meta = (SubCategory = "Caches", EditCondition = "bImportGrooms == false", MetaClass = "/Script/HairStrandsCore.GroomAsset"))` — If the groom asset is not imported, provide an existing one against which the groom cache will be validated
- L54 _public member_ `EInterchangeGroomCacheImportType ImportGroomCacheType = EInterchangeGroomCacheImportType::All;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grooms", meta = (SubCategory = "Caches", EditCondition = bImportGroomCaches))` — Groom Cache types to import
- L57 _public member_ `bool bOverrideTimeRange = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grooms", meta = (SubCategory = "Caches"))`
- L60 _public member_ `int32 FrameStart = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grooms", meta = (SubCategory = "Caches", EditCondition = bOverrideTimeRange))`
- L63 _public member_ `int32 FrameEnd = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grooms", meta = (SubCategory = "Caches", EditCondition = bOverrideTimeRange))`
- L67 _public member_ `int32 NumInterpolationPoints = 100;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grooms", meta = (SubCategory = "Bindings", ClampMin = "0", ClampMax = "100"))` — Number of points used for the rbf interpolation
- L71 _protected prototype_ `virtual void ExecutePipeline(UInterchangeBaseNodeContainer* BaseNodeContainer, const TArray<UInterchangeSourceData*>& SourceDatas, const FString& ContentBasePath) override;`
- L75 _public prototype_ `virtual void GetSupportAssetClasses(TArray<UClass*>& PipelineSupportAssetClasses) const override;`
- L76 _public prototype_ `virtual void FilterPropertiesFromTranslatedData(UInterchangeBaseNodeContainer* InBaseNodeContainer) override;`
- L77 _public prototype_ `virtual bool IsPropertyChangeNeedRefresh(const FPropertyChangedEvent& PropertyChangedEvent) const override;`
- L80 _public prototype_ `virtual bool IsSettingsAreValid(TOptional<FText>& OutInvalidReason) const override;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API INTERCHANGEPIPELINES_API`

### `Plugins/Interchange/Runtime/Source/Pipelines/Public/InterchangeGenericMaterialPipeline.h` (Public)


#### enum `EInterchangeMaterialImportOption`  
`enum class EInterchangeMaterialImportOption : uint8`  
_L38-44_
- reflection: `UENUM(BlueprintType)`
- L41 _public enumerator_ `ImportAsMaterials` — Import all materials from the source as material assets.
- L43 _public enumerator_ `ImportAsMaterialInstances` — Import all materials from the source as material instance assets.

#### enum `EInterchangeMaterialSearchLocation`  
`enum class EInterchangeMaterialSearchLocation : uint8`  
_L47-59_
- reflection: `UENUM(BlueprintType)`
- L50 _public enumerator_ `Local` — Search for existing material in local import folder only.
- L52 _public enumerator_ `UnderParent` — Search for existing material recursively from parent folder.
- L54 _public enumerator_ `UnderRoot` — Search for existing material recursively from root folder.
- L56 _public enumerator_ `AllAssets` — Search for existing material in all assets folders.
- L58 _public enumerator_ `DoNotSearch UE_DEPRECATED(5.8, "Moved as a boolean, bReuseExistingMaterials in UInterchangeGenericMaterialPipeline") UMETA(Hidden, Deprecated)` — Do not search for existing existing materials. Deprecated replaced with boolean bReuseExistingMaterials

#### class `UInterchangeGenericMaterialPipeline`  
`class UInterchangeGenericMaterialPipeline : public UInterchangePipelineBase`  
_L62-335_
- reflection: `UCLASS(MinimalAPI, BlueprintType, editinlinenew)`
- inherits: `UInterchangePipelineBase`
- L67 _public prototype_ `UInterchangeGenericMaterialPipeline();`
- L70 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L73 _public prototype_ `static FString GetPipelineCategory(UClass* AssetClass);`
- L77 _public member_ `FString PipelineDisplayName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials", Meta = (StandAlonePipelineProperty = "True", PipelineInternalEditionData = "True"))` — The name of the pipeline that will be display in the import dialog.
- L81 _public member_ `FString AssetName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials", Meta = (StandAlonePipelineProperty = "True"))` — If enabled, and there is only one asset and one source, the imported asset will be given this name.
- L85 _public member_ `bool bImportMaterials = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")` — If enabled, imports the material assets found in the sources.
- L92 _public member_ `bool bReuseExistingMaterials = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials", Meta = (EditCondition = "bImportMaterials"))` — When enabled, if the name of a material in the imported source matches a material that already exists in the project, the imported assets will reuse that existing material.
- L96 _public member_ `EInterchangeMaterialSearchLocation SearchLocation = EInterchangeMaterialSearchLocation::Local;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials", Meta = (EditCondition = "bImportMaterials && bReuseExistingMaterials"))` — Determines where to look for matching materials.
- L103 _public member_ `bool bCreateNewMaterials = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials", Meta = (EditCondition = "bImportMaterials"))` — When enabled, a new material asset will be created for each material in the imported source that has not been matched to an existing material.
- L107 _public member_ `EInterchangeMaterialImportOption MaterialImport = EInterchangeMaterialImportOption::ImportAsMaterials;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials", Meta=(DisplayName="New Material Asset Type", EditCondition = "bImportMaterials && bCreateNewMaterials"))` — Determines which kind of material asset to create for all new materials.
- L111 _public member_ `bool bCreateMaterialInstanceForParent = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials", Meta=(DisplayName = "Create MaterialInstance From Parent", EditCondition="bImportMaterials && bCreateNewMaterials && MaterialImport==EInterchangeMaterialImportOption::ImportAsMaterialInstances"))` — If enabled, material instances are created from a specified parent material.
- L115 _public member_ `FSoftObjectPath ParentMaterial;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials", Meta= (EditCondition="bImportMaterials && bCreateNewMaterials && MaterialImport==EInterchangeMaterialImportOption::ImportAsMaterialInstances && bCreateMaterialInstanceForParent", AllowedClasses="/Script/Engine.MaterialInterface"))` — Optional material used as the parent when importing materials as instances. If no parent material is specified, one will be automatically selected during the import process.
- L122 _public member_ `bool bIdentifyDuplicateMaterials = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials", Meta = (EditCondition = "bImportMaterials"))` — If enabled and duplicated materials are detected, for each set of duplicated materials, a reference material along with respective material instances are created.
- L125 _public member_ `TObjectPtr<UInterchangeGenericTexturePipeline> TexturePipeline;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Instanced, Category = "Textures")`
- L128 _public member_ `TObjectPtr<UInterchangeSparseVolumeTexturePipeline> SparseVolumeTexturePipeline;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Instanced, Category = "Volumes")`
- L136 _public member_ `bool bOverrideDisplacement = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials", Meta = (DisplayName = "Override Displacement Center", EditCondition = "bImportMaterials"))` — If enabled, it will override the displacement center set by shader graph nodes, if any Note: Some MaterialX Surface may have their preferred displacement center specified. In that case, enabling this option may affect the rendering result.
- L140 _public member_ `float OverrideDisplacementCenter = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials", Meta = (EditCondition = "bOverrideDisplacement && bImportMaterials", ClampMin = "0", DisplayName = "Displacement Center"))` — Set the value of the displacement center. If enabled it will also override any displacement center value set by shader graph nodes
- L143 _public prototype_ `virtual void PreDialogCleanup(const FName PipelineStackName) override;` — BEGIN UInterchangePipelineBase overrides
- L144 _public prototype_ `virtual bool IsSettingsAreValid(TOptional<FText>& OutInvalidReason) const override;`
- L145 _public prototype_ `virtual void AdjustSettingsForContext(const FInterchangePipelineContextParams& ContextParams) override;`
- L147 _public prototype_ `virtual void FilterPropertiesFromTranslatedData(UInterchangeBaseNodeContainer* InBaseNodeContainer) override;`
- L148 _public prototype_ `virtual bool IsPropertyChangeNeedRefresh(const FPropertyChangedEvent& PropertyChangedEvent) const override;`
- L150 _public prototype_ `virtual void GetSupportAssetClasses(TArray<UClass*>& PipelineSupportAssetClasses) const override;`
- L154 _protected prototype_ `virtual void ExecutePipeline(UInterchangeBaseNodeContainer* InBaseNodeContainer, const TArray<UInterchangeSourceData*>& InSourceDatas, const FString& ContentBasePath) override;`
- L155 _protected prototype_ `virtual void ExecutePostFactoryPipeline(const UInterchangeBaseNodeContainer* BaseNodeContainer, const FString& NodeKey, UObject* CreatedAsset, bool bIsAReimport) override;`
- L156 _protected prototype_ `virtual void ExecutePostImportPipeline(const UInterchangeBaseNodeContainer* BaseNodeContainer, const FString& NodeKey, UObject* CreatedAsset, bool bIsAReimport) override;`
- L157 _protected prototype_ `virtual void SetReimportSourceIndex(UClass* ReimportObjectClass, const int32 SourceFileIndex) override;`
- L161 _protected member_ `TObjectPtr<UInterchangeBaseNodeContainer> BaseNodeContainer;` — `UPROPERTY()`
- L163 _protected member_ `TArray<const UInterchangeSourceData*> SourceDatas;`
- L166 _private prototype_ `UInterchangeBaseMaterialFactoryNode* CreateBaseMaterialFactoryNode(const UInterchangeBaseNode* MaterialNode, TSubclassOf<UInterchangeBaseMaterialFactoryNode> NodeType, bool bAddMaterialInstanceSuffix = false);`
- L167 _private prototype_ `UInterchangeMaterialFactoryNode* CreateMaterialFactoryNode(const UInterchangeShaderGraphNode* ShaderGraphNode);`
- L168 _private prototype_ `UInterchangeMaterialFunctionFactoryNode* CreateMaterialFunctionFactoryNode(const UInterchangeShaderGraphNode* FunctionCallShaderNode);`
- L169 _private prototype_ `UInterchangeMaterialInstanceFactoryNode* CreateMaterialInstanceFactoryNode(const UInterchangeShaderGraphNode* ShaderGraphNode);`
- L170 _private prototype_ `void CreateSpecularProfileFactoryNode(const UInterchangeSpecularProfileNode* SpecularProfileNode);`
- L173 _private prototype_ `bool HasClearCoat(const UInterchangeShaderGraphNode* ShaderGraphNode) const;` — True if the shader graph has a clear coat input.
- L175 _private function_ `bool IsClearCoatModel(const UInterchangeShaderGraphNode* ShaderGraphNode) const` — `UE_DEPRECATED(5.3, "Deprecated. Use HasClearCoat.")`
- L181 _private prototype_ `bool HasSheen(const UInterchangeShaderGraphNode* ShaderGraphNode) const;` — True if the shader graph has a sheen color input.
- L183 _private function_ `bool IsSheenModel(const UInterchangeShaderGraphNode* ShaderGraphNode) const` — `UE_DEPRECATED(5.3, "Deprecated. Use HasSheen.")`
- L189 _private prototype_ `bool HasSubsurface(const UInterchangeShaderGraphNode* ShaderGraphNode) const;` — True if the shader graph has a subsurface color input.
- L191 _private function_ `bool IsSubsurfaceModel(const UInterchangeShaderGraphNode* ShaderGraphNode) const` — `UE_DEPRECATED(5.3, "Deprecated. Use HasSubsurface.")`
- L197 _private prototype_ `bool HasThinTranslucency(const UInterchangeShaderGraphNode* ShaderGraphNode) const;` — True if the shader graph has a transmission color input.
- L199 _private function_ `bool IsThinTranslucentModel(const UInterchangeShaderGraphNode* ShaderGraphNode) const` — `UE_DEPRECATED(5.3, "Deprecated. Use HasThinTranslucency.")`
- L205 _private prototype_ `bool IsMetalRoughModel(const UInterchangeShaderGraphNode* ShaderGraphNode) const;` — True if the shader graph has a base color input (Metallic/Roughness model).
- L207 _private function_ `bool IsPBRModel(const UInterchangeShaderGraphNode* ShaderGraphNode) const` — `UE_DEPRECATED(5.3, "Deprecated. Use IsMetalRoughModel and IsSpecGlossModel to identify the correct PBR model.")`
- L213 _private prototype_ `bool IsPhongModel(const UInterchangeShaderGraphNode* ShaderGraphNode) const;` — True if the shader graph has diffuse color and specular inputs.
- L216 _private prototype_ `bool IsLambertModel(const UInterchangeShaderGraphNode* ShaderGraphNode) const;` — True if the shader graph has a diffuse color input.
- L219 _private prototype_ `bool IsSurfaceUnlitModel(const UInterchangeShaderGraphNode* ShaderGraphNode) const;` — True if the shader graph has the surface unlit's shader type name.
- L222 _private prototype_ `bool IsUnlitModel(const UInterchangeShaderGraphNode* ShaderGraphNode) const;` — True if the shader graph has an unlit color input.
- L225 _private prototype_ `bool IsSpecGlossModel(const UInterchangeShaderGraphNode* ShaderGraphNode) const;` — True if the shader graph has specular color and glossiness scalar inputs.
- L227 _private prototype_ `bool HandlePhongModel(const UInterchangeShaderGraphNode* ShaderGraphNode, UInterchangeMaterialFactoryNode* MaterialFactoryNode);`
- L228 _private prototype_ `bool HandleLambertModel(const UInterchangeShaderGraphNode* ShaderGraphNode, UInterchangeMaterialFactoryNode* MaterialFactoryNode);`
- L229 _private prototype_ `bool HandleMetalRoughnessModel(const UInterchangeShaderGraphNode* ShaderGraphNode, UInterchangeMaterialFactoryNode* MaterialFactoryNode);`
- L230 _private prototype_ `bool HandleClearCoat(const UInterchangeShaderGraphNode* ShaderGraphNode, UInterchangeMaterialFactoryNode* MaterialFactoryNode);`
- L231 _private prototype_ `bool HandleSubsurface(const UInterchangeShaderGraphNode* ShaderGraphNode, UInterchangeMaterialFactoryNode* MaterialFactoryNode);`
- L232 _private prototype_ `bool HandleSheen(const UInterchangeShaderGraphNode* ShaderGraphNode, UInterchangeMaterialFactoryNode* MaterialFactoryNode);`
- L233 _private prototype_ `bool HandleThinTranslucent(const UInterchangeShaderGraphNode* ShaderGraphNode, UInterchangeMaterialFactoryNode* MaterialFactoryNode);`
- L234 _private prototype_ `void HandleCommonParameters(const UInterchangeShaderGraphNode* ShaderGraphNode, UInterchangeMaterialFactoryNode* MaterialFactoryNode);`
- L235 _private prototype_ `bool HandleBxDFInput(const UInterchangeShaderGraphNode* ShaderGraphNode, UInterchangeMaterialFactoryNode* MaterialFactoryNode);`
- L236 _private prototype_ `bool HandleUnlitModel(const UInterchangeShaderGraphNode* ShaderGraphNode, UInterchangeMaterialFactoryNode* MaterialFactoryNode);`
- L237 _private prototype_ `bool HandleSpecGlossModel(const UInterchangeShaderGraphNode* ShaderGraphNode, UInterchangeMaterialFactoryNode* MaterialFactoryNode);`
- L238 _private prototype_ `bool HandleSubstrate(const UInterchangeShaderGraphNode* ShaderGraphNode, UInterchangeMaterialFactoryNode* MaterialFactoryNode);`
- L240 _private prototype_ `void HandleFlattenNormalNode(const UInterchangeShaderNode* ShaderNode, UInterchangeBaseMaterialFactoryNode* MaterialFactoryNode, UInterchangeMaterialExpressionFactoryNode* FlattenNormalFactoryNode);`
- L241 _private prototype_ `void HandleNormalFromHeightMapNode(const UInterchangeShaderNode* ShaderNode, UInterchangeBaseMaterialFactoryNode* MaterialFactoryNode, UInterchangeMaterialExpressionFactoryNode* NormalFromHeightMapFactoryNode);`
- L242 _private prototype_ `void HandleMakeFloat3Node(const UInterchangeShaderNode* ShaderNode, UInterchangeBaseMaterialFactoryNode* MaterialFactoryNode, UInterchangeMaterialExpressionFactoryNode* MakeFloat3FactoryNode);`
- L243 _private prototype_ `void HandleTextureNode(const UInterchangeTextureNode* TextureNode, UInterchangeBaseMaterialFactoryNode* MaterialFactoryNode, UInterchangeMaterialExpressionFactoryNode* TextureBaseFactoryNode, const FString& ExpressionClassName, bool bIsAParameter);`
- L244 _private prototype_ `void HandleTextureObjectNode(const UInterchangeShaderNode* ShaderNode, UInterchangeBaseMaterialFactoryNode* MaterialFactoryNode, UInterchangeMaterialExpressionFactoryNode* TextureObjectFactoryNode);`
- L245 _private prototype_ `void HandleTextureSampleNode(const UInterchangeShaderNode* ShaderNode, UInterchangeBaseMaterialFactoryNode* MaterialFactoryNode, UInterchangeMaterialExpressionFactoryNode* TextureSampleFactoryNode);`
- L246 _private prototype_ `void HandleTextureSampleBlurNode(const UInterchangeShaderNode* ShaderNode, UInterchangeBaseMaterialFactoryNode* MaterialFactoryNode, UInterchangeMaterialExpressionFactoryNode* TextureSampleFactoryNode);`
- L247 _private prototype_ `void HandleTextureCoordinateNode(const UInterchangeShaderNode* ShaderNode, UInterchangeBaseMaterialFactoryNode* MaterialFactoryNode, UInterchangeMaterialExpressionFactoryNode*& TextureSampleFactoryNode);`
- L248 _private prototype_ `void HandleLerpNode(const UInterchangeShaderNode* ShaderNode, UInterchangeBaseMaterialFactoryNode* MaterialFactoryNode, UInterchangeMaterialExpressionFactoryNode* LerpFactoryNode);`
- L249 _private prototype_ `void HandleMaskNode(const UInterchangeShaderNode* ShaderNode, UInterchangeBaseMaterialFactoryNode* MaterialFactoryNode, UInterchangeMaterialExpressionFactoryNode* MaskFactoryNode);`
- L250 _private prototype_ `void HandleRotatorNode(const UInterchangeShaderNode* ShaderNode, UInterchangeBaseMaterialFactoryNode* MaterialFactoryNode, UInterchangeMaterialExpressionFactoryNode* RotatorFactoryNode);`
- L251 _private prototype_ `void HandleRotateAboutAxisNode(const UInterchangeShaderNode* ShaderNode, UInterchangeBaseMaterialFactoryNode* MaterialFactoryNode, UInterchangeMaterialExpressionFactoryNode* RotateAboutAxisFactoryNode);`
- L252 _private prototype_ `void HandleTimeNode(const UInterchangeShaderNode* ShaderNode, UInterchangeBaseMaterialFactoryNode* MaterialFactoryNode, UInterchangeMaterialExpressionFactoryNode* TimeFactoryNode);`
- L253 _private prototype_ `void HandleTransformPositionNode(const UInterchangeShaderNode* ShaderNode, UInterchangeBaseMaterialFactoryNode* MaterialFactoryNode, UInterchangeMaterialExpressionFactoryNode* TransformPositionFactoryNode);`
- L254 _private prototype_ `void HandleTransformVectorNode(const UInterchangeShaderNode* ShaderNode, UInterchangeBaseMaterialFactoryNode* MaterialFactoryNode, UInterchangeMaterialExpressionFactoryNode* TransformVectorFactoryNode);`
- L255 _private prototype_ `void HandleNoiseNode(const UInterchangeShaderNode* ShaderNode, UInterchangeBaseMaterialFactoryNode* MaterialFactoryNode, UInterchangeMaterialExpressionFactoryNode* NoiseFactoryNode);`
- L256 _private prototype_ `void HandleVectorNoiseNode(const UInterchangeShaderNode* ShaderNode, UInterchangeBaseMaterialFactoryNode* MaterialFactoryNode, UInterchangeMaterialExpressionFactoryNode* NoiseFactoryNode);`
- L257 _private prototype_ `void HandleSwitchNode(const UInterchangeShaderNode* ShaderNode, UInterchangeBaseMaterialFactoryNode* MaterialFactoryNode, UInterchangeMaterialExpressionFactoryNode* SwitchFactoryNode);`
- L258 _private prototype_ `void HandleSlabBSDFNode(const UInterchangeShaderNode* ShaderNode, UInterchangeBaseMaterialFactoryNode* MaterialFactoryNode, UInterchangeMaterialExpressionFactoryNode* SlabBSDFFactoryNode);`
- L259 _private prototype_ `void HandleLuminanceNode(const UInterchangeShaderNode* ShaderNode, UInterchangeBaseMaterialFactoryNode* MaterialFactoryNode, UInterchangeMaterialExpressionFactoryNode* LuminanceFactoryNode);`
- L260 _private prototype_ `void HandleTexturePropertyNode(const UInterchangeShaderNode* ShaderNode, UInterchangeBaseMaterialFactoryNode* MaterialFactoryNode, UInterchangeMaterialExpressionFactoryNode* TexturePropertyFactoryNode);`
- L261 _private prototype_ `void HandleTrigonometryNode(const UInterchangeShaderNode* ShaderNode, UClass* StaticClass, UInterchangeBaseMaterialFactoryNode* MaterialFactoryNode, UInterchangeMaterialExpressionFactoryNode* TrigonometryFactoryNode);`
- L263 _private prototype_ `void HandleScalarParameterNode(const UInterchangeShaderNode* ShaderNode, UInterchangeMaterialExpressionFactoryNode* ScalarParameterFactoryNode);`
- L264 _private prototype_ `void HandleVectorParameterNode(const UInterchangeShaderNode* ShaderNode, UInterchangeMaterialExpressionFactoryNode* VectorParameterFactoryNode);`
- L265 _private prototype_ `void HandleStaticBooleanParameterNode(const UInterchangeShaderNode* ShaderNode, UInterchangeMaterialExpressionFactoryNode* StaticBooleanParameterFactoryNode);`
- L267 _private prototype_ `UInterchangeMaterialExpressionFactoryNode* CreateMaterialExpressionForShaderNode(UInterchangeBaseMaterialFactoryNode* MaterialFactoryNode, const UInterchangeShaderNode* ShaderNode, const FString& ParentUid);`
- L268 _private prototype_ `TTuple<UInterchangeMaterialExpressionFactoryNode*, FString> CreateMaterialExpressionForInput(UInterchangeBaseMaterialFactoryNode* MaterialFactoryNode, const UInterchangeShaderNode* ShaderNode, const FString& InputName, const FString& ParentUid);`
- L270 _private prototype_ `UInterchangeMaterialExpressionFactoryNode* CreateExpressionNode(const FString& ExpressionName, const FString& ParentUid, UClass* MaterialExpressionClass);`
- L272 _private prototype_ `UInterchangeMaterialExpressionFactoryNode* HandleFloatInput(const UInterchangeShaderNode* ShaderNode, const FString& InputName, const FString& ParentUid, bool bIsAParameter);`
- L273 _private prototype_ `UInterchangeMaterialExpressionFactoryNode* CreateConstantExpression(const UInterchangeShaderNode* ShaderNode, const FString& InputName, const FString& ParentUid);`
- L274 _private prototype_ `UInterchangeMaterialExpressionFactoryNode* CreateScalarParameterExpression(const UInterchangeShaderNode* ShaderNode, const FString& InputName, const FString& ParentUid);`
- L275 _private prototype_ `UInterchangeMaterialExpressionFactoryNode* HandleLinearColorInput(const UInterchangeShaderNode* ShaderNode, const FString& InputName, const FString& ParentUid, bool bIsAParameter);`
- L276 _private prototype_ `UInterchangeMaterialExpressionFactoryNode* CreateConstant3VectorExpression(const UInterchangeShaderNode* ShaderNode, const FString& InputName, const FString& ParentUid);`
- L277 _private prototype_ `UInterchangeMaterialExpressionFactoryNode* CreateVectorParameterExpression(const UInterchangeShaderNode* ShaderNode, const FString& InputName, const FString& ParentUid);`
- L278 _private prototype_ `UInterchangeMaterialExpressionFactoryNode* CreateStaticBooleanParameterExpression(const UInterchangeShaderNode* ShaderNode, const FString& InputName, const FString& ParentUid);`
- L279 _private prototype_ `UInterchangeMaterialExpressionFactoryNode* CreateVector2ParameterExpression(const UInterchangeShaderNode* ShaderNode, const FString& InputName, const FString& ParentUid);`
- L280 _private prototype_ `UInterchangeMaterialExpressionFactoryNode* CreateFunctionCallExpression(const UInterchangeShaderNode* ShaderNode, const FString& MaterialExpressionUid, UInterchangeBaseMaterialFactoryNode* MaterialFactoryNode);`
- L286 _private prototype_ `void VisitShaderGraphNode(const UInterchangeShaderGraphNode* ShaderGraphNode, UInterchangeMaterialInstanceFactoryNode* MaterialInstanceFactoryNode) const;` — Visits a given shader node and its connections to find its strongest value. The goal is to simplify a branch of a node graph to a single value, to be used for material instancing.
- L287 _private prototype_ `void VisitShaderNode(const UInterchangeShaderNode* ShaderNode, UInterchangeMaterialInstanceFactoryNode* MaterialInstanceFactoryNode, TSet<const UInterchangeShaderNode*> & VisitedNodes) const;`
- L288 _private prototype_ `void VisitShaderInput(const UInterchangeShaderNode* ShaderNode, UInterchangeMaterialInstanceFactoryNode* MaterialInstanceFactoryNode, const FString& InputName, TSet<const UInterchangeShaderNode*> & VisitedNodes) const;`
- L290 _private prototype_ `void VisitScalarParameterNode(const UInterchangeShaderNode* ShaderNode, UInterchangeMaterialInstanceFactoryNode* MaterialInstanceFactoryNode) const;`
- L291 _private prototype_ `void VisitTextureSampleNode(const UInterchangeShaderNode* ShaderNode, UInterchangeMaterialInstanceFactoryNode* MaterialInstanceFactoryNode) const;`
- L292 _private prototype_ `void VisitVectorParameterNode(const UInterchangeShaderNode* ShaderNode, UInterchangeMaterialInstanceFactoryNode* MaterialInstanceFactoryNode) const;`
- L294 _private prototype_ `FString GetTextureUidAttributeFromShaderNode(const UInterchangeShaderNode* ShaderNode, FName ParameterName, bool& OutIsAParameter) const;`
- L295 _private prototype_ `FString CreateInputKey(const FString& InputName, bool bIsAParameter) const;`
- L311 _private member_ `} MaterialCreationContext;`
- L318 _private member_ `TArray<FMaterialExpressionCreationContext> MaterialExpressionCreationContextStack;`
- L320 _private typedef_ `using FParameterMaterialInputType = TTuple<FString, EMaterialInputType>;`
- L322 _private member_ `const UInterchangeBaseNode * AttributeStorageNode = nullptr;`
- L325 _private function_ `void UpdateSearchLocationProperty()`

#### enum `UInterchangeGenericMaterialPipeline::EMaterialInputType`  
`enum class EMaterialInputType : uint8`  
_L299-305_
- L301 _public enumerator_ `Unknown`
- L302 _public enumerator_ `Color`
- L303 _public enumerator_ `Vector`
- L304 _public enumerator_ `Scalar`

#### struct `UInterchangeGenericMaterialPipeline::FMaterialCreationContext`  
`struct FMaterialCreationContext`  
_L308-311_
- L310 _public member_ `EMaterialInputType InputTypeBeingProcessed = EMaterialInputType::Color;`

#### struct `UInterchangeGenericMaterialPipeline::FMaterialExpressionCreationContext`  
`struct FMaterialExpressionCreationContext`  
_L313-316_
- L315 _public member_ `FString OutputName;` — The name of the output we will be connecting from

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API INTERCHANGEPIPELINES_API`
- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace Interchange` (scope `UE`)
- L32 _namespace_ `namespace Materials` (scope `UE::Interchange`)
- L32 _namespace_ `namespace HashUtils` (scope `UE::Interchange::Materials`)

### `Plugins/Interchange/Runtime/Source/Pipelines/Public/InterchangeGenericMeshPipeline.h` (Public)


#### enum `EInterchangeCombineStaticMeshesBehavior`  
`enum class EInterchangeCombineStaticMeshesBehavior : uint8`  
_L32-39_
- reflection: `UENUM(BlueprintType)`
- L34 _public enumerator_ `All UMETA(DisplayName="Combine All", Tooltip="Combine all the meshes into a single Static Mesh")`
- L36 _public enumerator_ `VisibleOnly UMETA(DisplayName = "Combine Visible Meshes Only", Tooltip="Skip adding the hidden meshes to the combined Static Mesh")`
- L38 _public enumerator_ `DoNotCombine UMETA(DisplayName = "Do Not Combine Static Meshes", Tooltip = "All meshes will be imported as individual Static Mesh assets")`

#### enum `EInterchangeCombineSkeletalMeshesBehavior`  
`enum class EInterchangeCombineSkeletalMeshesBehavior : uint8`  
_L42-49_
- reflection: `UENUM(BlueprintType)`
- L44 _public enumerator_ `BySkeleton UMETA(DisplayName="Combine All That Use Same Skeleton", Tooltip="Combine all the meshes that use a specific Skeleton as a single Skeletal Mesh")`
- L46 _public enumerator_ `BySkeletonVisibleOnly UMETA(DisplayName = "Combine All Visible That Use Same Skeleton", Tooltip="Combine all visible meshes that use a specific Skeleton as a single Skeletal Mesh")`
- L48 _public enumerator_ `DoNotCombine UMETA(DisplayName = "Do Not Combine Skeletal Meshes", Tooltip = "All meshes will be imported as individual Skeletal Mesh assets")`

#### class `UInterchangeGenericMeshPipeline`  
`class UInterchangeGenericMeshPipeline : public UInterchangePipelineBase`  
_L53-529_
- reflection: `UCLASS(MinimalAPI, BlueprintType, hidedropdown)`
- inherits: `UInterchangePipelineBase`
- desc: Hide drop down will make sure the class is not showing in the class picker
- L59 _public prototype_ `static FString GetPipelineCategory(UClass* AssetClass);` — IInterchangeGenericPipelineCategoryInterface
- L63 _public member_ `TWeakObjectPtr<UInterchangeGenericCommonMeshesProperties> CommonMeshesProperties;` — `UPROPERTY(Transient)` — Common Meshes Properties Settings Pointer
- L67 _public member_ `TWeakObjectPtr<UInterchangeGenericCommonSkeletalMeshesAndAnimationsProperties> CommonSkeletalMeshesAndAnimationsProperties;` — `UPROPERTY(Transient)` — Common SkeletalMeshes And Animations Properties Settings Pointer
- L73 _public member_ `bool bImportStaticMeshes = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Meshes")` — If enabled, imports all static mesh assets found in the sources.
- L76 _public member_ `bool bCombineStaticMeshes_DEPRECATED = false;` — `UPROPERTY(meta=(DeprecatedProperty, DeprecationMessage = "bCombineStaticMeshes is no longer used. Use CombineStaticMeshesBehavior"))`
- L80 _public member_ `EInterchangeCombineStaticMeshesBehavior CombineStaticMeshesBehavior = EInterchangeCombineStaticMeshesBehavior::DoNotCombine;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Meshes", meta=(DisplayName = "Combine Static Meshes"))` — Specifies the behavior for combining static meshes into a single static mesh.
- L84 _public member_ `FName LodGroup = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Meshes", meta=(DisplayName = "LOD Group"), meta = (ReimportRestrict = "true"))` — The LOD group that will be assigned to this mesh.
- L88 _public member_ `bool bAutoComputeLODScreenSizes = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Meshes", meta=(ReimportRestrict = "true"))` — If enabled, LOD Screen Sizes would be auto-computed.
- L92 _public member_ `TArray<float> LODScreenSizes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Meshes", meta=(EditCondition = "!bAutoComputeLODScreenSizes", DisplayName = "LOD Screen Sizes", ReimportRestrict="true"))` — This setting is only used if the Auto Compute LOD Screen Sizes setting is disabled.
- L95 _public member_ `bool bImportCollision_DEPRECATED = true;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use Collision instead."))`
- L101 _public member_ `bool bCollision = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Meshes", meta = (DisplayName = "Import Collisions", SubCategory = "Collision"))` — If enabled, custom collision will be imported. If enabled and there is no custom collision, a generic collision will be automatically generated. If disabled, no collision will be created or imported.
- L113 _public member_ `bool bImportCollisionAccordingToMeshName = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Meshes", meta = (DisplayName = "Import Collisions According To Mesh Name", SubCategory = "Collision", editcondition = "bCollision == true"))` — If enabled, meshes with certain prefixes will be imported as collision primitives for the mesh with the corresponding unprefixed name. Supported prefixes are: UBX_ Box collision UCP_ Capsule collision USP_ Sphere collision UCX_ Convex collision
- L117 _public member_ `bool bOneConvexHullPerUCX = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Meshes", meta = (SubCategory = "Collision", editcondition = "bCollision == true && bImportCollisionAccordingToMeshName"))` — If enabled, each UCX collision mesh will be imported as a single convex hull. If disabled, a UCX mesh will be decomposed into its separate pieces and a convex hull generated for each.
- L121 _public member_ `EInterchangeMeshCollision Collision = EInterchangeMeshCollision::Convex18DOP;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Meshes", meta = (ScriptName = "FallbackCollisionType", DisplayName = "Fallback Collision Type", SubCategory = "Collision", editcondition = "bCollision == true"))` — Type used to generate a collision when no custom collisions are present in the file.
- L125 _public member_ `bool bForceCollisionPrimitiveGeneration = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Meshes", meta = (SubCategory = "Collision", editcondition = "bCollision == true", PipelineInternalEditionData = "True"))` — Sets whether to generate collision shapes even if the provided mesh data doesn't match the requested collision shape very well
- L134 _public member_ `bool bBuildNanite = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Meshes", meta = (SubCategory = "Build"))` — If enabled, imported meshes will be rendered by Nanite at runtime. Make sure your meshes and materials meet the requirements for Nanite. See also NaniteTriangleThreshold
- L141 _public member_ `int64 NaniteTriangleThreshold = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Meshes", meta = (SubCategory = "Build", EditCondition = "bBuildNanite"))` — Minimum triangle count a mesh needs to have in order to get Nanite enabled for it when BuildNanite is enabled. When zero it means Nanite will always be enabled for all meshes when BuildNanite is enabled.
- L145 _public member_ `bool bBuildReversedIndexBuffer = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Meshes", meta = (SubCategory = "Build"))` — If enabled, builds a reversed index buffer for each static mesh.
- L149 _public member_ `bool bGenerateLightmapUVs = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Meshes", meta = (SubCategory = "Build"))` — If enabled, generates lightmap UVs for each static mesh.
- L156 _public member_ `bool bGenerateDistanceFieldAsIfTwoSided = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Meshes", meta=(SubCategory = "Build", DisplayName="Two-Sided Distance Field Generation"))` — Determines whether to generate the distance field treating every triangle hit as a front face. When enabled, prevents the distance field from being discarded due to the mesh being open, but also lowers distance field ambient occlusion quality.
- L160 _public member_ `bool bSupportFaceRemap = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Meshes", meta = (SubCategory = "Build", DisplayName="Enable Physical Material Mask"))` — If enabled, imported static meshes are set up for use with physical material masks.
- L164 _public member_ `int32 MinLightmapResolution = 64;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Meshes", meta = (SubCategory = "Build"))` — When generating lightmaps, determines the amount of padding used to pack UVs. Set this value to the lowest-resolution lightmap you expect to use with the imported meshes.
- L168 _public member_ `int32 SrcLightmapIndex = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Meshes", meta = (SubCategory = "Build", DisplayName="Source Lightmap Index"))` — Specifies the index of the UV channel that will be used as the source when generating lightmaps.
- L172 _public member_ `int32 DstLightmapIndex = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Meshes", meta = (SubCategory = "Build", DisplayName="Destination Lightmap Index"))` — Specifies the index of the UV channel that will store generated lightmap UVs.
- L176 _public member_ `FVector BuildScale3D = FVector(1.0);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Meshes", meta = (SubCategory = "Build", DisplayName="Build Scale"))` — The local scale applied when building the mesh.
- L183 _public member_ `float DistanceFieldResolutionScale = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Meshes", meta = (SubCategory = "Build"))` — Scale to apply to the mesh when allocating the distance field volume texture. The default scale is 1, which assumes that the mesh will be placed unscaled in the world.
- L189 _public member_ `TSoftObjectPtr<class UStaticMesh> DistanceFieldReplacementMesh = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Meshes", meta = (SubCategory = "Build"))` — If set, replaces the distance field for all imported meshes with the distance field of the specified Static Mesh.
- L198 _public member_ `int32 MaxLumenMeshCards = 12;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Meshes", meta = (SubCategory = "Build"))` — The maximum number of Lumen mesh cards to generate for this mesh. More cards means that the surface will have better coverage, but will result in increased runtime overhead. Set this to 0 to disable mesh card generation for this mesh. The default is 12.
- L204 _public member_ `bool bImportSkeletalMeshes = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skeletal Meshes")` — If enabled, imports all skeletal mesh assets found in the sources.
- L208 _public member_ `EInterchangeSkeletalMeshContentType SkeletalMeshImportContentType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skeletal Meshes", meta = (DisplayName = "Import Content Type"))` — Determines what types of information are imported for skeletal meshes.
- L212 _public member_ `EInterchangeSkeletalMeshContentType LastSkeletalMeshImportContentType;` — `UPROPERTY()` — The value of the content type during the last import. This cannot be edited and is set only on successful import or reimport.
- L216 _public member_ `EInterchangeCombineSkeletalMeshesBehavior CombineSkeletalMeshesBehavior = EInterchangeCombineSkeletalMeshesBehavior::BySkeleton;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skeletal Meshes", meta=(DisplayName = "Combine Skeletal Meshes"))` — Specifies the behavior for combining skeletal meshes into a single skeletal mesh.
- L220 _public member_ `bool bImportMorphTargets = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skeletal Meshes")` — If enabled, imports all morph target shapes found in the source.
- L224 _public member_ `bool bMergeMorphTargetsWithSameName = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skeletal Meshes", meta = (EditCondition = "bImportMorphTargets"))` — If enabled, all morph target shapes with the same name will be merge together. Turn it to false if you want to control those morph with different values.
- L228 _public member_ `bool bImportVertexAttributes = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skeletal Meshes", meta = (ToolTip = "If enabled, creates named vertex attributes for secondary vertex color data."))` — If enabled, imports per-vertex attributes from the FBX file.
- L232 _public member_ `bool bUpdateSkeletonReferencePose = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skeletal Meshes")` — Enable this option to update the reference pose of the Skeleton (of the mesh). The reference pose of the mesh is always updated.
- L236 _public member_ `bool bCreatePhysicsAsset = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skeletal Meshes")` — If enabled, create new PhysicsAsset if one doesn't exist.
- L240 _public member_ `TSoftObjectPtr<UPhysicsAsset> PhysicsAsset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skeletal Meshes", meta = (editcondition = "!bCreatePhysicsAsset"))` — If set, use the specified PhysicsAsset. If not set and the Create Physics Asset setting is not enabled, the importer will not generate or set any physics asset.
- L244 _public member_ `bool bUseHighPrecisionSkinWeights = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skeletal Meshes", meta = (SubCategory = "Build"))` — If enabled, imported skin weights use 16 bits instead of 8 bits.
- L248 _public member_ `float ThresholdPosition = 0.00002f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skeletal Meshes", meta = (SubCategory = "Build"))` — Threshold value that is used to decide whether two vertex positions are equal.
- L252 _public member_ `float ThresholdTangentNormal = 0.00002f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skeletal Meshes", meta = (SubCategory = "Build"))` — Threshold value that is used to decide whether two normals, tangents, or bi-normals are equal.
- L256 _public member_ `float ThresholdUV = 0.0009765625f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skeletal Meshes", meta = (SubCategory = "Build"))` — Threshold value that is used to decide whether two UVs are equal.
- L260 _public member_ `float MorphThresholdPosition = 0.015f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skeletal Meshes", meta = (SubCategory = "Build"))` — Threshold to compare vertex position equality when computing morph target deltas.
- L268 _public member_ `int32 BoneInfluenceLimit = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skeletal Meshes", meta = (SubCategory = "Build"))` — The maximum number of bone influences to allow each vertex in this mesh to use. If set higher than the limit determined by the project settings, it has no effect. If set to 0, the value is taken from the DefaultBoneInfluenceLimit project setting.
- L274 _public member_ `bool bImportGeometryCaches = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Geometry Caches")` — If enabled, imports all geometry cache assets found in the sources.
- L278 _public member_ `bool bFlattenTracks = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Geometry Caches")` — Whether or not to merge all vertex animation into one track
- L282 _public member_ `float CompressedPositionPrecision = 0.01f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Geometry Caches", meta = (ClampMin = "0.000001", ClampMax = "1000", UIMin = "0.0001", UIMax = "10"))` — Precision used for compressing vertex positions (lower = better result but less compression, higher = more lossy compression but smaller size)
- L286 _public member_ `int32 CompressedTextureCoordinatesNumberOfBits = 10;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Geometry Caches", meta = (ClampMin = "1", ClampMax = "31", UIMin = "4", UIMax = "16"))` — Bit-precision used for compressing texture coordinates (hight = better result but less compression, lower = more lossy compression but smaller size)
- L290 _public member_ `bool bOverrideTimeRange = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Geometry Caches", meta = (SubCategory = "Sampling"))` — If enabled, override the imported animation range. Otherwise, the imported range is automatically set to the range of non-empty animated frames
- L293 _public member_ `int32 FrameStart = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Geometry Caches", meta = (SubCategory = "Sampling", editcondition = "bOverrideTimeRange == true"))`
- L296 _public member_ `int32 FrameEnd = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Geometry Caches", meta = (SubCategory = "Sampling", editcondition = "bOverrideTimeRange == true"))`
- L299 _public member_ `EInterchangeMotionVectorsHandling MotionVectors = EInterchangeMotionVectorsHandling::NoMotionVectors;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Geometry Caches", AdvancedDisplay)`
- L306 _public member_ `bool bApplyConstantTopologyOptimizations = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Geometry Caches", AdvancedDisplay)` — Force the preprocessor to only do optimization once instead of when the preprocessor decides. This may lead to some problems with certain meshes but makes sure motion blur always works if the topology is constant.
- L313 _public member_ `bool bStoreImportedVertexNumbers = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Geometry Caches", AdvancedDisplay)` — Store the imported vertex numbers. This lets you know the vertex numbers inside the DCC. The values of each vertex number will range from 0 to 7 for a cube. Even if the number of positions might be 24.
- L317 _public member_ `bool bOptimizeIndexBuffers = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Geometry Caches", AdvancedDisplay)` — Optimizes index buffers for each unique frame, to allow better cache coherency on the GPU. Very costly and time-consuming process, recommended to OFF.
- L319 _public prototype_ `virtual void AdjustSettingsForContext(const FInterchangePipelineContextParams& ContextParams) override;`
- L321 _public prototype_ `virtual void PreDialogCleanup(const FName PipelineStackName) override;`
- L324 _public prototype_ `virtual bool IsPropertyChangeNeedRefresh(const FPropertyChangedEvent& PropertyChangedEvent) const override;`
- L325 _public prototype_ `virtual bool GetPropertyPossibleValues(const FName PropertyPath, TArray<FString>& PossibleValues) override;`
- L327 _public prototype_ `virtual void GetSupportAssetClasses(TArray<UClass*>& PipelineSupportAssetClasses) const override;`
- L330 _public prototype_ `static UInterchangePipelineMeshesUtilities* CreateMeshPipelineUtilities(UInterchangeBaseNodeContainer* InBaseNodeContainer , const UInterchangeGenericMeshPipeline* Pipeline);`
- L334 _protected prototype_ `virtual void ExecutePipeline(UInterchangeBaseNodeContainer* InBaseNodeContainer, const TArray<UInterchangeSourceData*>& InSourceDatas, const FString& ContentBasePath) override;`
- L336 _protected prototype_ `virtual void ExecutePostFactoryPipeline(const UInterchangeBaseNodeContainer* InBaseNodeContainer, const FString& NodeKey, UObject* CreatedAsset, bool bIsAReimport) override;`
- L338 _protected prototype_ `virtual void ExecutePostImportPipeline(const UInterchangeBaseNodeContainer* InBaseNodeContainer, const FString& NodeKey, UObject* CreatedAsset, bool bIsAReimport) override;`
- L340 _protected function_ `virtual bool CanExecuteOnAnyThread(EInterchangePipelineTask PipelineTask) override`
- L345 _protected prototype_ `virtual void SetReimportSourceIndex(UClass* ReimportObjectClass, const int32 SourceFileIndex) override;`
- L356 _protected prototype_ `static bool DoClassesIncludeAllEditableStructProperties(const TArray<const UClass*>& Classes, const UStruct* Struct);` — This function return true if all UPROPERTYs of the @Struct exist in the provided @Classes. @Struct UPROPERTY tested must be: not transient, editable @param Classes - The array of UClass that should contains the Struct properties @param Struct - The struct that has the referenced properties
- L362 _private member_ `TObjectPtr<UInterchangePipelineMeshesUtilities> PipelineMeshesUtilities = nullptr;` — Meshes utilities, to parse the translated graph and extract the meshes informations.
- L365 _private member_ `TMap<FString, UInterchangeMeshFactoryNode*> AssemblyPartMeshUidToFactoryNodeTable;` — Table to access the corresponding factory node for the given mesh uid
- L371 _private prototype_ `void UpdateAssemblyPartDependencyTable(UInterchangeMeshFactoryNode* MeshFactoryNode, const TMap<int32, TArray<FString>>& NodeUidsPerLodIndex);` — Update the MeshUid to MeshFactoryNode table with the given node uids @param NodeUidsPerLodIndex - The NodeUids can be a UInterchangeSceneNode or a UInterchangeMeshNode.
- L376 _private prototype_ `void CreateAssemblyPartDependencies();` — Creates the final dependencies between nanite assembly parts
- L384 _private prototype_ `void ExecutePreImportPipelineSkeletalMesh();` — This function will create any skeletalmesh we need to create according to the pipeline options
- L391 _private prototype_ `UInterchangeSkeletalMeshFactoryNode* CreateSkeletalMeshFactoryNode(const FString& RootJointUid, const TArray<FString>& NodeUids);` — This function will create the SkeletalMeshFactoryNode and all necessary UInterchangeSkeletalMeshLodDataNode nodes. It will also process/parse all input nodes into the created UInterchangeSkeletalMeshLodDataNode nodes, and will also generate the Transforms that should be used for Mesh acquisitions. @param NodeUids - NodeUid Can be Mesh(Mesh/LODContainer/Bundle) or MeshInstance (SceneNode instantiating a Mesh).
- L396 _private prototype_ `void PostImportSkeletalMesh(UObject* CreatedAsset, const UInterchangeFactoryBaseNode* FactoryNode);` — This function will finish creating the skeletalmesh asset
- L401 _private prototype_ `void PostImportPhysicsAssetImport(UObject* CreatedAsset, const UInterchangeFactoryBaseNode* FactoryNode);` — This function will finish creating the physics asset with the skeletalmesh render data
- L405 _public prototype_ `void ImplementUseSourceNameForAssetOptionSkeletalMesh(const int32 MeshesImportedNodeCount, const bool bUseSourceNameForAsset, const FString& AssetName);` — Specialize for skeletalmesh
- L418 _private prototype_ `void ExecutePreImportPipelineStaticMesh();` — This function will create any skeletalmesh we need to create according to the pipeline options
- L420 _private prototype_ `void ExecutePostFactoryPipelineStaticMesh(const UInterchangeBaseNodeContainer* InBaseNodeContainer, const FString& NodeKey, UObject* CreatedAsset, bool bIsAReimport);`
- L423 _private member_ `TArray<UInterchangeStaticMeshFactoryNode*> StaticMeshFactoryNodes;` — Static mesh factory assets nodes
- L428 _private prototype_ `void ApplyMeshProperties(UInterchangeStaticMeshFactoryNode* StaticMeshFactoryNode);` — Applies Common mesh properties and LODGroup settings.
- L436 _private prototype_ `UInterchangeStaticMeshFactoryNode* CreateStaticMeshFactoryNode(const TArray<FString>& NodeUids, const TArray<FString>& CollisionMeshUids = {});` — This function can create a UInterchangeStaticMeshFactoryNode @param NodeUids: All primary MeshUid references for which the Factory Node is created. In case a UInterchangeMeshLODContainerNode the containing UInterchangeMeshNodes won't be part of given Array. NodeUid Can be Mesh(Mesh/LODContainer/Bundle) or MeshInstance (SceneNode instantiating a Mesh).
- L442 _private prototype_ `bool MakeMeshFactoryNodeUidAndDisplayLabel(const TArray<FString>& NodeUids, FString& OutFactoryNodeUid, FString& OutFactoryDisplayLabel) const;` — Return a reasonable UID and display label for a new mesh factory node. * @param NodeUids: NodeUid Can be Mesh(Mesh/LODContainer/Bundle) or MeshInstance (SceneNode instantiating a Mesh).
- L450 _private prototype_ `void GetMeshesInformationFromTranslatedData(const UInterchangeBaseNodeContainer* InBaseNodeContainer , bool& bContainStaticMesh , bool& bContainSkeletalMesh , bool& bContainGeometryCache) const;` — Fill all reference parameter from the translated node found in the container
- L461 _private prototype_ `void ExecutePreImportPipelineGeometryCache();` — This function will create any geometry cache we need to create according to the pipeline options
- L464 _private member_ `TArray<UInterchangeGeometryCacheFactoryNode*> GeometryCacheFactoryNodes;` — Geometry cache factory assets nodes
- L470 _private prototype_ `UInterchangeGeometryCacheFactoryNode* CreateGeometryCacheFactoryNode(const TArray<FString>& MeshUids);` — This function can create a UInterchangeGeometryCacheFactoryNode @param MeshUids - The MeshUids can represent a SceneNode pointing on a MeshNode or directly a MeshNode
- L476 _private prototype_ `void AddMeshesToGeometryCache(UInterchangeGeometryCacheFactoryNode* GeometryCacheFactoryNode, const TArray<FString>& NodeUids);` — This function add all mesh nodes to the geometry cache. @param NodeUids - Can be a UInterchangeSceneNode or a UInterchangeMeshNode.
- L483 _public prototype_ `virtual void PostLoad() override;`
- L485 _public prototype_ `void AddToAssemblyPartMeshUidToFactoryNodeTable(const FString& MeshNodeUid, UInterchangeMeshFactoryNode* MeshFactoryNode);`
- L496 _public prototype_ `UInterchangeSkeletalMeshFactoryNode* CreateSkeletalMeshFactoryNode(const FString& RootJointUid, const TMap<int32, TArray<FString>>& MeshUidsPerLodIndex);` — `UE_DEPRECATED(5.8, "Deprecated. Use CreateSkeletalMeshFactoryNode(const FString& RootJointUid, const TArray<FString>& NodeUids) instead.")` — This function can create a UInterchangeSkeletalMeshFactoryNode @param MeshUidsPerLodIndex - The MeshUids can represent a SceneNode pointing on a MeshNode or directly a MeshNode
- L500 _public prototype_ `UInterchangeSkeletalMeshLodDataNode* CreateSkeletalMeshLodDataNode(const FString& NodeName, const FString& NodeUniqueID, const FString& ParentNodeUniqueID);` — `UE_DEPRECATED(5.8, "Deprecated. Use CreateSkeletalMeshFactoryNode(const FString& RootJointUid, const TArray<FString>& NodeUids) instead. It will also take care of LodDataNode generations.")` — This function can create a UInterchangeSkeletalMeshLodDataNode which represent the LOD data need by the factory to create a lod mesh
- L507 _public prototype_ `void AddLodDataToSkeletalMesh(const UInterchangeSkeletonFactoryNode* SkeletonFactoryNode, UInterchangeSkeletalMeshFactoryNode* SkeletalMeshFactoryNode, const TMap<int32, TArray<FString>>& NodeUidsPerLodIndex);` — `UE_DEPRECATED(5.8, "Deprecated. Use CreateSkeletalMeshFactoryNode(const FString& RootJointUid, const TArray<FString>& NodeUids) instead. It will also take care of LodData parsing to SkeletalMeshes")` — This function add all lod data node to the skeletal mesh. @param NodeUidsPerLodIndex - The NodeUids can be a UInterchangeSceneNode or a UInterchangeMeshNode. The scene node can bake each instance of the mesh versus the mesh node will import only the modelled mesh.
- L514 _public prototype_ `UInterchangeStaticMeshFactoryNode* CreateStaticMeshFactoryNode(const TMap<int32, TArray<FString>>& MeshUidsPerLodIndex, const FString& BaseMeshUid = TEXT(""));` — `UE_DEPRECATED(5.8, "Deprecated. Use CreateStaticMeshFactoryNode(const TArray<FString>& MeshNodeOrMeshInstanceNodeUids, const TArray<FString>& CollisionMeshUids = {}) instead.")`
- L517 _public prototype_ `UInterchangeStaticMeshLodDataNode* FindOrCreateStaticMeshLodDataNode(UInterchangeStaticMeshFactoryNode* StaticMeshFactoryNode, const int32 LODIndex);` — `UE_DEPRECATED(5.8, "Deprecated. Use CreateStaticMeshFactoryNode(const TArray<FString>& MeshNodeOrMeshInstanceNodeUids, const TArray<FString>& CollisionMeshUids = {}) instead. It will also take care of LodDataNode generations.")`
- L520 _public prototype_ `void AddLodDataToStaticMesh(UInterchangeStaticMeshFactoryNode* StaticMeshFactoryNode, const TMap<int32, TArray<FString>>& NodeUidsPerLodIndex);` — `UE_DEPRECATED(5.8, "Deprecated. Use CreateStaticMeshFactoryNode(const TArray<FString>& MeshNodeOrMeshInstanceNodeUids, const TArray<FString>& CollisionMeshUids = {}) instead. It will also take care of LodData parsing to StaticMeshes.")`
- L523 _public prototype_ `bool MakeMeshFactoryNodeUidAndDisplayLabel(const TMap<int32, TArray<FString>>& MeshUidsPerLodIndex, int32 LodIndex, FString& NewMeshUid, FString& DisplayLabel, const FString& BaseMeshUid);` — `UE_DEPRECATED(5.8, "Deprecated. Use MakeMeshFactoryNodeUidAndDisplayLabel(const TArray<FString>& MeshNodeOrMeshInstancingNodeUids, FString& OutFactoryNodeUid, FString& OutFactoryDisplayLabel) instead.")`
- L526 _protected member_ `UInterchangeBaseNodeContainer* BaseNodeContainer = nullptr;`
- L527 _protected member_ `TArray<const UInterchangeSourceData*> SourceDatas;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API INTERCHANGEPIPELINES_API`

### `Plugins/Interchange/Runtime/Source/Pipelines/Public/InterchangeGenericScenesPipeline.h` (Public)


#### enum `EInterchangeSceneHierarchyType`  
`enum class EInterchangeSceneHierarchyType : uint8`  
_L29-34_
- reflection: `UENUM(BlueprintType)`
- L31 _public enumerator_ `CreateLevelActors UMETA(DisplayName = "Create level actors", ToolTip = "Create actors in the current editor world for all scene nodes in the source hierarchy.")`
- L32 _public enumerator_ `CreateLevelInstanceActor UMETA(DisplayName = "Create a level instance actor", ToolTip = "Create a level instance actor referencing a new/existing world containing all scene nodes in the source hierarchy.")`
- L33 _public enumerator_ `CreatePackedActor UMETA(DisplayName = "Create a packed level actor", ToolTip = "Create a packed level actor blueprint which packed all meshes from a new/existing world containing all scene nodes in the source hierarchy.")`

#### class `UInterchangeGenericLevelPipeline`  
`class UInterchangeGenericLevelPipeline : public UInterchangePipelineBase`  
_L37-169_
- reflection: `UCLASS(MinimalAPI, BlueprintType, editinlinenew)`
- inherits: `UInterchangePipelineBase`
- L42 _public prototype_ `virtual ~UInterchangeGenericLevelPipeline();`
- L46 _public member_ `FString PipelineDisplayName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene", meta = (StandAlonePipelineProperty = "True", PipelineInternalEditionData = "True"))` — The name of the pipeline that will be display in the import dialog.
- L50 _public member_ `EReimportStrategyFlags ReimportPropertyStrategy = EReimportStrategyFlags::ApplyNoProperties;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene", meta = (SubCategory = "Actors properties", AdjustPipelineAndRefreshDetailOnChange = "True"))` — Set the reimport strategy when reimporting into the level.
- L54 _public member_ `EInterchangeSceneHierarchyType SceneHierarchyType = EInterchangeSceneHierarchyType::CreateLevelActors;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene")` — Choose how you want to import the hierarchy.
- L58 _public member_ `bool bDeleteMissingActors = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene", meta = (SubCategory = "Reimport Actors"))` — If enabled, deletes actors that were not part of the translation when reimporting into a level.
- L62 _public member_ `bool bForceReimportDeletedActors = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene", meta = (SubCategory = "Reimport Actors"))` — If enabled, respawns actors that were deleted in the editor prior to a reimport.
- L66 _public member_ `bool bForceReimportDeletedAssets = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene", meta = (SubCategory = "Reimport Assets"))` — If enabled, recreates assets that were deleted in the editor prior to reimporting into a level.
- L70 _public member_ `bool bDeleteMissingAssets = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene", meta = (SubCategory = "Reimport Assets"))` — If enabled, deletes assets that were not part of the translation when reimporting into a level.
- L74 _public member_ `bool bUseHierarchicalISMComponents = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene", meta = (SubCategory = "Component properties", DisplayName = "Use Hierarchical ISM Components"))` — If enabled, HierarchicalInstancedStaticMeshComponents will be generated on import instead of InstancedStaticMeshComponents.
- L77 _public prototype_ `virtual void AdjustSettingsForContext(const FInterchangePipelineContextParams& ContextParams) override;` — BEGIN UInterchangePipelineBase overrides
- L81 _protected prototype_ `virtual void ExecutePipeline(UInterchangeBaseNodeContainer* InBaseNodeContainer, const TArray<UInterchangeSourceData*>& InSourceDatas, const FString& ContentBasePath) override;`
- L82 _protected prototype_ `virtual void ExecutePostImportPipeline(const UInterchangeBaseNodeContainer* BaseNodeContainer, const FString& NodeKey, UObject* CreatedAsset, bool bIsAReimport) override;`
- L83 _protected prototype_ `virtual void ExecutePostBroadcastPipeline(const UInterchangeBaseNodeContainer* BaseNodeContainer, const FString& NodeKey, UObject* CreatedAsset, bool bIsAReimport) override;`
- L85 _protected function_ `virtual bool CanExecuteOnAnyThread(EInterchangePipelineTask PipelineTask) override`
- L94 _protected prototype_ `virtual void ExecuteSceneNodePreImport(const FTransform& GlobalOffsetTransform, const UInterchangeSceneNode* SceneNode);` — PreImport step called for each translated SceneNode.
- L99 _protected prototype_ `virtual void ExecuteSceneVariantSetNodePreImport(const UInterchangeSceneVariantSetsNode& SceneVariantSetNode);` — PreImport step called for each translated SceneVariantSetNode.
- L104 _protected prototype_ `virtual UInterchangeActorFactoryNode* CreateActorFactoryNode(const UInterchangeBaseNode* TranslatedAssetNode) const;` — Return a new Actor Factory Node to be used for the given SceneNode.
- L107 _protected function_ `virtual UInterchangeActorFactoryNode* CreateActorFactoryNode(const UInterchangeSceneNode* SceneNode, const UInterchangeBaseNode* TranslatedAssetNode) const` — `UE_DEPRECATED(5.8, "Use CreateActorFactoryNode(const UInterchangeBaseNode* TranslatedAssetNode) instead")`
- L115 _protected prototype_ `virtual void CreateComponentFactoryNode(const UInterchangeSceneComponentNode* TranslatedAssetNode) const;` — Return a new Component Factory Node.
- L120 _protected prototype_ `virtual void SetUpFactoryNode(UInterchangeActorFactoryNode* ActorFactoryNode, const UInterchangeSceneNode* SceneNode, const UInterchangeBaseNode* TranslatedAssetNode, bool bIsRootJoint = false) const;` — Use to set up the given factory node's attributes after its initialization.
- L122 _protected prototype_ `virtual void PopulateSceneNodesPreImport(TArray<UInterchangeSceneNode*>& SceneNodes, TArray<UInterchangeSceneComponentNode*>& SceneComponentNodes) const;`
- L128 _protected prototype_ `virtual void SetUpComponents(UInterchangeActorFactoryNode* ActorFactoryNode, const UInterchangeSceneNode* SceneNode) const;` — Use to set up the given factory node's component's attributes after its initialization.
- L130 _protected prototype_ `virtual void SetUpComponentDependencies(UInterchangeActorFactoryNode* ActorFactoryNode, const TArray<FString>& SceneComponentUids) const;`
- L134 _protected member_ `bool bUsePhysicalInsteadOfStandardPerspectiveCamera = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common Skeletal Meshes and Animations")` — Disable this option to not convert Standard(Perspective) to Physical Cameras
- L137 _protected member_ `UInterchangeBaseNodeContainer* BaseNodeContainer = nullptr;`
- L146 _protected member_ `UInterchangeSceneImportAssetFactoryNode* SceneImportFactoryNode = nullptr;` — Factory node created by the pipeline to later create the SceneImportAsset This factory node must be unique and depends on all the other factory nodes and its factory must be called after all factories Note that this factory node is not created at runtime. Therefore, the reimport of a level will not work at runtime
- L147 _protected member_ `UInterchangeLevelFactoryNode* LevelFactoryNode = nullptr;`
- L148 _protected member_ `UInterchangeLevelInstanceActorFactoryNode* LevelInstanceActorFactoryNode = nullptr;`
- L159 _protected member_ `FPostPipelineImportData PostPipelineImportData;`
- L162 _protected prototype_ `void CacheActiveJointUids();`
- L163 _protected member_ `TSet<FString> Cached_ActiveJointUids;`
- L165 _protected member_ `FPreviewScene* PreviewScene = nullptr;`
- L168 _private prototype_ `void CreateActorFactoryNode(const FTransform& GlobalOffsetTransform, const UInterchangeSceneNode* SceneNode, const FString& SkeletalMeshFactoryNodeUid);`

#### struct `UInterchangeGenericLevelPipeline::FPostPipelineImportData`  
`struct FPostPipelineImportData`  
_L150-157_
- L152 _public prototype_ `void AddLevelInstanceActor(ALevelInstance* LevelInstanceActor, UWorld* ReferenceWorld);`
- L155 _private member_ `TSet<UWorld*> Worlds;`
- L156 _private member_ `TMap<ALevelInstance*, UWorld*> ReferenceWorldPerLevelInstanceToUpdates;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API INTERCHANGEPIPELINES_API`

### `Plugins/Interchange/Runtime/Source/Pipelines/Public/InterchangeGenericTexturePipeline.h` (Public)


#### class `UInterchangeGenericTexturePipeline`  
`class UInterchangeGenericTexturePipeline : public UInterchangePipelineBase`  
_L19-114_
- reflection: `UCLASS(MinimalAPI, BlueprintType, editinlinenew)`
- inherits: `UInterchangePipelineBase`
- L24 _public prototype_ `static FString GetPipelineCategory(UClass* AssetClass);`
- L28 _public member_ `FString PipelineDisplayName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Textures", meta = (StandAlonePipelineProperty = "True", PipelineInternalEditionData = "True"))` — The name of the pipeline that will be display in the import dialog.
- L32 _public member_ `bool bImportTextures = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Textures")` — If enabled, imports all texture assets found in the source.
- L36 _public member_ `FString AssetName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Textures", meta=(StandAlonePipelineProperty = "True"))` — If set, and there is only one asset and one source, the imported asset will be given this name.
- L44 _public member_ `bool bDetectNormalMapTexture = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Textures", Meta=(EditCondition="bImportTextures"))` — If enabled, tests each newly imported texture to see if it is a normal map. If it is, the SRGB, Compression Settings, and LOD Group properties of that texture will be adjusted.
- L48 _public member_ `bool bFlipNormalMapGreenChannel = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Textures", Meta=(EditCondition="bImportTextures"))` — If enabled, the texture's green channel will be inverted for normal maps. This setting is only used if the Detect Normal Map Texture setting is also enabled or if the texture has been imported as a Normal map.
- L52 _public member_ `bool bImportUDIMs = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Textures", Meta=(EditCondition="bImportTextures"))` — If enabled, imports textures as UDIMs if they are named using a UDIM naming pattern.
- L56 _public member_ `bool bDetectLongLatCubemap = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Textures", Meta = (EditCondition = "bImportTextures && (bIsReimport == false)"))` — Detect if a texture should be imported as long/lat cubemap. The minimum size to detect a cubemap texture is a 512 pixels height. Use the CVar Interchange.Textures.MinCubeMapDetection if you want to control that setting.
- L60 _public member_ `TSet<FString> FileExtensionsToImportAsLongLatCubemap = {"hdr` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Textures", Meta=(EditCondition="bImportTextures && (bDetectLongLatCubemap == false)"))` — Specify the file types that should be imported as long/lat cubemaps.
- L68 _public member_ `bool bPreferCompressedSourceData = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Textures", Meta=(EditCondition="bImportTextures"))` — If enabled, the translator compresses the source data payload whenever possible. This generally results in smaller assets. However, some operations like the texture build might be slower, because the source data first needs to be decompressed. If disabled, the translator leaves the decision to the factory or the pipelines.
- L74 _public member_ `bool bAllowNonPowerOfTwo = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Textures", Meta=(EditCondition="bImportTextures"))` — If enabled, textures that have a non-power-of-two resolution are imported.
- L77 _public prototype_ `virtual void AdjustSettingsForContext(const FInterchangePipelineContextParams& ContextParams) override;`
- L78 _public prototype_ `virtual void ExecutePipeline(UInterchangeBaseNodeContainer* InBaseNodeContainer, const TArray<UInterchangeSourceData*>& InSourceDatas, const FString& ContentBasePath) override;`
- L79 _public prototype_ `virtual void ExecutePostFactoryPipeline(const UInterchangeBaseNodeContainer* BaseNodeContainer, const FString& NodeKey, UObject* CreatedAsset, bool bIsAReimport) override;`
- L83 _public prototype_ `virtual bool IsPropertyChangeNeedRefresh(const FPropertyChangedEvent& PropertyChangedEvent) const override;`
- L85 _public prototype_ `virtual void FilterPropertiesFromTranslatedData(UInterchangeBaseNodeContainer* InBaseNodeContainer) override;`
- L87 _public prototype_ `virtual void GetSupportAssetClasses(TArray<UClass*>& PipelineSupportAssetClasses) const override;`
- L92 _protected prototype_ `UInterchangeTextureFactoryNode* HandleCreationOfTextureFactoryNode(const UInterchangeTextureNode* TextureNode);`
- L94 _protected prototype_ `UInterchangeTextureFactoryNode* CreateTextureFactoryNode(const UInterchangeTextureNode* TextureNode, const TSubclassOf<UInterchangeTextureFactoryNode>& FactorySubclass);`
- L96 _protected prototype_ `void PostImportTextureAssetImport(UObject* CreatedAsset, bool bIsAReimport);`
- L100 _private member_ `TObjectPtr<UInterchangeBaseNodeContainer> BaseNodeContainer;` — `UPROPERTY()`
- L102 _private member_ `TArray<const UInterchangeSourceData*> SourceDatas;`
- L105 _private member_ `TArray<UInterchangeTextureNode*> TextureNodes;` — Texture translated assets nodes
- L108 _private member_ `TArray<UInterchangeTextureFactoryNode*> TextureFactoryNodes;` — Texture factory assets nodes
- L112 _private member_ `bool bIsReimport = false;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API INTERCHANGEPIPELINES_API`

### `Plugins/Interchange/Runtime/Source/Pipelines/Public/InterchangeLODDataParser.h` (Public)


#### struct `FInterchangeMeshLODDataParser`  
`template <class TMeshFactoryType> struct FInterchangeMeshLODDataParser`  
_L33-117_
- desc: Helper struct that processes an array of NodeUids into LODContainers. Template to handle StaticMesh and SkeletalMeshes in one go. Difference between SKM and SM is the Collision and SkeletonUID setting for the LODDataNode.
- L36 _private typedef_ `using TLODDataNodeType = std::conditional_t< std::is_same_v<TMeshFactoryType, UInterchangeStaticMeshFactoryNode>, UInterchangeStaticMeshLodDataNode, UInterchangeSkeletalMeshLodDataNode >;`
- L42 _private member_ `TMeshFactoryType* MeshFactoryNode;` — The one we are setting up
- L43 _private member_ `const FString MeshFactoryNodeUid;`
- L45 _private member_ `UInterchangeBaseNodeContainer& BaseNodeContainer;`
- L46 _private member_ `const bool bBakeMeshes;`
- L47 _private member_ `const bool bBakePivotMeshes;`
- L48 _private member_ `TObjectPtr<UInterchangePipelineMeshesUtilities> PipelineMeshesUtilities;`
- L49 _private member_ `UInterchangeGenericMeshPipeline* GenericMeshPipeline;`
- L50 _private member_ `FString SourceAssetFileName;` — Used for warnings
- L51 _private member_ `const FString SkeletonFactoryNodeUid;` — To Set for UInterchangeSkeletalMeshLodDataNode
- L52 _private member_ `bool bUseTimeZeroAsBindPose;`
- L55 _private member_ `FTransform GlobalOffsetTransform;`
- L56 _private member_ `TMap<int32, TLODDataNodeType*> LODIndexToLodDataNodeMap;`
- L57 _private member_ `TMap<int32, TMap<FString, FString>> ExistingLodSlotMaterialDependenciesPerLODIndices;`
- L58 _private member_ `TSet<FString> UniqueMeshUids;`
- L59 _private member_ `TMap<int32, int32> OriginalToCompactLODIndexMap;` — TSet<FString> UniqueMeshUids;  All MeshUids processed (including all LODs).
- L72 _private member_ `TOptional<TPair<FString, FMatrix>> RootJointParentUidAndGlobalInverseMatrix;` — Used for calculating skeletalMesh's relative transform to RootJoineNode's parent (aka Skeleton Transform). This is needed, because GetTimeZeroGlobalTransform/GetBindPoseGlobalTransform on SceneNodes fallback onto LocalTransforms, if BindPose/T0 is not present. Inherently this means that we get the Transform's relative to the Root SceneNode, regardless if they are Joint or not, To fix for this behavior we apply the RootJoint's Parent's Global Transform inverse when BakeMesh==false, to acquire 'SkeletonTransform'. (See @UE::Interchange::Private::MeshHelper::CalculateCompleteSceneNodeTransform) If it is not set, the CalculateCompleteScenNodeTransform will try to identify the RootJoint's ParentNode and acquire described transform for application in there. (Based on Parent hierarchy and UInterchangeJointNode classification) The FString is the RootJointParent's UID, this is used for identifying, if the the instancing Node is part of the child tree/hierarchy of the RootJointParent. (See @UE::Interchange::Private::MeshHelper::CalculateCompleteSceneNodeTransform)
- L73 _private member_ `bool bCreatingSkeletalMesh = !std::is_same_v<TMeshFactoryType, UInterchangeStaticMeshFactoryNode>;`
- L74 _private member_ `bool bAlignSkeletalMeshInScene;`
- L76 _private member_ `TArray<FString> AllNodeUids;` — Used for collission processing, combination of NodeUids and CollisionNodeUids
- L80 _public prototype_ `explicit FInterchangeMeshLODDataParser(UInterchangeBaseNodeContainer& InBaseNodeContainer, TMeshFactoryType* InStaticMeshFactoryNode, TObjectPtr<UInterchangePipelineMeshesUtilities> InPipelineMeshesUtilities, UInterchangeGenericMeshPipeline* InGenericMeshPipeline, const FString& InSourceAssetFileName, const FString& InRootJointNodeUid = TEXT("") , const FString& InSkeletonFactoryNodeUid = TEXT(""), const bool InbUseTimeZeroAsBindPose = false);`
- L96 _public prototype_ `void ProcessNodeUids(const TArray<FString>& RenderNodeUids, const TArray<FString>& CollisionMeshUids = {});` — Note Regarding CollisionMeshUids: -If bImportCollision:=false	=> we ignore the CollisionMeshUids array -If bImportCollision:=true: --If bImportCollisionAccordingToMeshName:=true	=> we add the CollisionMeshUids as Collisions --If bImportCollisionAccordingToMeshName:=false	=> we add the CollisionMeshUids as RenderMeshes
- L98 _public function_ `TSet<FString> GetUniqueMeshUids() const`
- L102 _private prototype_ `void CreateMeshLodDataNode(const int32 LODIndex);`
- L103 _private prototype_ `TLODDataNodeType* GetMeshLodDataNode(const int32 MappedLODIndex);` — Mapped via OriginalToCompactLODIndexMap.
- L104 _private prototype_ `void LogWarning(const FText& Text);`
- L106 _private prototype_ `void ProcessCollision(const FString& NodeUid, UInterchangeStaticMeshLodDataNode* LodDataNode, const FTransform& Transform);`
- L112 _private prototype_ `void ProcessNode(const UInterchangeBaseNode* BaseNode, const FTransform& MeshTransform, const UInterchangeSceneNode* CurrentTransformNode, const int32 LODIndex, bool bProcessAsSubMesh, bool bProcessAsCollision);` — bProcessAsSubMesh:= such as Mesh of a MeshLODContainerNode/MeshBundle/ISMComponentNode we track these, as the ones flagged as sub mesh do not need to be configured via TargetNodes and the AssemblyParts do not need to be set either.
- L115 _private prototype_ `void PreProcess(const TArray<FString>& NodeUids);` — Parses All nodes to identify used LODIndices, sets up OriginalToCompactLODIndexMap, and creates all MeshLodDataNodes.
- L116 _private prototype_ `void FindAllAvailableLODIndices(const UInterchangeBaseNode* BaseNode, TSet<int32>& AvailableLODIndices);`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Interchange` (scope `UE`)
- L18 _namespace_ `namespace CollisionHelper` (scope `UE::Interchange`)
- L20 _prototype_ `TTuple<EInterchangeMeshCollision, FString> GetCollisionMeshType( TObjectPtr<UInterchangePipelineMeshesUtilities> PipelineMeshesUtilities, const UInterchangeBaseNodeContainer& NodeContainer, const FString& NodeUid, const TArray<FString>& AllNodeUids, bool bImportCollisionAccordingToMeshName );` (scope `UE::Interchange::CollisionHelper`)

### `Plugins/Interchange/Runtime/Source/Pipelines/Public/InterchangeMaterialXPipeline.h` (Public)


#### class `UMaterialXPipelineSettings`  
`class UMaterialXPipelineSettings : public UDeveloperSettings`  
_L27-93_
- reflection: `UCLASS(MinimalAPI, config = Interchange, meta = (DisplayName = "MaterialX Settings", ToolTip = "Interchange MaterialX Pipeline Settings"))`
- inherits: `UDeveloperSettings`
- L32 _public prototype_ `UMaterialXPipelineSettings();`
- L34 _public prototype_ `bool AreRequiredPackagesLoaded();`
- L36 _public prototype_ `FString GetAssetPathString(EInterchangeMaterialXSettings EnumType) const;`
- L39 _public function_ `template<typename EnumT> FString GetAssetPathString(EnumT EnumValue) const`
- L51 _public member_ `TMap<EInterchangeMaterialXShaders, FSoftObjectPath> PredefinedSurfaceShaders;` — `UPROPERTY(EditAnywhere, config, Category = "MaterialXPredefined | Surface Shaders", meta = (DisplayName = "MaterialX Predefined Surface Shaders"))`
- L54 _public member_ `TMap<EInterchangeMaterialXBSDF, FSoftObjectPath> PredefinedBSDF;` — `UPROPERTY(EditAnywhere, config, Category = "MaterialXPredefined | BSDF", meta = (DisplayName = "MaterialX Predefined BSDF"))`
- L57 _public member_ `TMap<EInterchangeMaterialXEDF, FSoftObjectPath> PredefinedEDF;` — `UPROPERTY(EditAnywhere, config, Category = "MaterialXPredefined | EDF", meta = (DisplayName = "MaterialX Predefined EDF"))`
- L60 _public member_ `TMap<EInterchangeMaterialXVDF, FSoftObjectPath> PredefinedVDF;` — `UPROPERTY(EditAnywhere, config, Category = "MaterialXPredefined | VDF", meta = (DisplayName = "MaterialX Predefined VDF"))`
- L64 _public prototype_ `void InitPredefinedAssets();` — Init the Predefined with Substrate assets, since the default value is set in BaseInterchange.ini and we have no way in the config file to conditionally init a property
- L70 _private typedef_ `using FMaterialXSettings = TMap<EInterchangeMaterialXSettings, TPair<TSet<FName>, TSet<FName>>>;`
- L72 _private prototype_ `static bool ShouldFilterAssets(UMaterialFunction* Asset, const TSet<FName>& Inputs, const TSet<FName>& Outputs);`
- L74 _private prototype_ `static EInterchangeMaterialXSettings ToEnumKey(uint8 EnumType, uint8 EnumValue);`
- L77 _private function_ `template<typename EnumT> static EInterchangeMaterialXSettings ToEnumKey(EnumT EnumValue)`
- L89 _private member_ `static FMaterialXSettings SettingsInputsOutputs;` — The key is a combination of the index in the variant + the corresponding enum
- L91 _private member_ `bool bIsSubstrateEnabled{ false };`

#### class `UInterchangeMaterialXPipeline`  
`class UInterchangeMaterialXPipeline : public UInterchangePipelineBase`  
_L96-128_
- reflection: `UCLASS(MinimalAPI, config = Interchange, BlueprintType)`
- inherits: `UInterchangePipelineBase`
- L100 _private prototype_ `UInterchangeMaterialXPipeline();`
- L103 _public member_ `TObjectPtr<UMaterialXPipelineSettings> MaterialXSettings;`
- L107 _public member_ `bool bVolumetricMaterial = true;` — `UPROPERTY(EditAnywhere, config, Category = "Volume")` — If true, handle Volume Distribution Functions as volumetric materials, i.e an internal Substrate Volumetric FOG-Cloud BSDF is created, otherwise a simple volume Slab BSDF is used.
- L113 _public member_ `bool bRecomputeNormals = true;` — `UPROPERTY(EditAnywhere, config, Category = "Displacement", meta = (DisplayName = "Normals From Height"))` — Derive the normals from height for displacement shaders, this option is best suited with procedural normals (for example shader graphs created specifically for offline-renderers). Otherwise this option should be disabled if there's already a normal map plugged to the normal input of the surfaceshader.
- L116 _protected prototype_ `virtual void AdjustSettingsForContext(const FInterchangePipelineContextParams& ContextParams) override;`
- L117 _protected prototype_ `virtual void ExecutePipeline(UInterchangeBaseNodeContainer* BaseNodeContainer, const TArray<UInterchangeSourceData*>& SourceDatas, const FString& ContentBasePath) override;`
- L119 _protected function_ `virtual bool CanExecuteOnAnyThread(EInterchangePipelineTask PipelineTask) override`
- L127 _private member_ `static TMap<FString, EInterchangeMaterialXSettings> PathToEnumMapping;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API INTERCHANGEPIPELINES_API`
- L20 _typedef_ `using EInterchangeMaterialXSettings = TVariant<EInterchangeMaterialXShaders, EInterchangeMaterialXBSDF, EInterchangeMaterialXEDF, EInterchangeMaterialXVDF>;`
- L22 _prototype_ `uint32 GetTypeHash(EInterchangeMaterialXSettings Key);`
- L24 _prototype_ `bool operator==(EInterchangeMaterialXSettings Lhs, EInterchangeMaterialXSettings Rhs);`

### `Plugins/Interchange/Runtime/Source/Pipelines/Public/InterchangePipelineHelper.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Interchange` (scope `UE`)
- L11 _namespace_ `namespace PipelineHelper` (scope `UE::Interchange`)
- L13 _prototype_ `void ShowModalDialog(TSharedRef<SInterchangeBaseConflictWidget> ConflictWidget, const FText& Title, const FVector2D& WindowSize);` (scope `UE::Interchange::PipelineHelper`)
- L16 _prototype_ `bool FillSubPathFromSourceNode(UInterchangeFactoryBaseNode* FactoryNode, const UInterchangeSourceNode* SourceNode);` (scope `UE::Interchange::PipelineHelper`) — Fills in the FactoryNode's SubPath custom attribute with the SourceNode's sub path prefixes and suffixes

### `Plugins/Interchange/Runtime/Source/Pipelines/Public/InterchangePipelineMeshesUtilities.h` (Public)


#### struct `FInterchangeMeshInstance`  
`struct FInterchangeMeshInstance`  
_L29-81_
- reflection: `USTRUCT(BlueprintType)`
- desc: A mesh instance is a description of a translated scene node that points to a translated mesh asset. A mesh instance that points to a mesh node will have only LOD 0 and will point to one scene mesh node.
- L33 _public function_ `FInterchangeMeshInstance() : bReferenceSkinnedMesh(false) , bReferenceMorphTarget(false) , bHasMorphTargets(false) , bIsGeometryCache(false) , bHasTransformAnimationTrack(false) , bIsVisible(false) , InstancingNode(nullptr)`
- L45 _public member_ `bool bReferenceSkinnedMesh;` — `UPROPERTY(EditAnywhere, Category = "Interchange | Pipeline | MeshesInstance")`
- L48 _public member_ `bool bReferenceMorphTarget;` — `UPROPERTY(EditAnywhere, Category = "Interchange | Pipeline | MeshesInstance")`
- L51 _public member_ `bool bHasMorphTargets;` — `UPROPERTY(EditAnywhere, Category = "Interchange | Pipeline | MeshesInstance")`
- L54 _public member_ `bool bIsGeometryCache;` — `UPROPERTY(EditAnywhere, Category = "Interchange | Pipeline | MeshesInstance")`
- L57 _public member_ `bool bHasTransformAnimationTrack;` — `UPROPERTY(EditAnywhere, Category = "Interchange | Pipeline | MeshesInstance")`
- L60 _public member_ `bool bIsVisible;` — `UPROPERTY(EditAnywhere, Category = "Interchange | Pipeline | MeshesInstance")`
- L68 _public member_ `TObjectPtr<const UInterchangeBaseNode> InstancingNode;` — `UPROPERTY(EditAnywhere, Category = "Interchange | Pipeline | MeshesInstance")` — It is the node that is instantiating a Mesh, for which the FInterchangeMeshInstance 'instance' is created. Instancing node can be: - UInterchangeSceneNode - UInterchangeGeometryCacheNode - UInterchangeInstancedStaticMeshComponentNode
- L74 _public member_ `TArray<FString> ReferencingMeshGeometryUids;` — `UPROPERTY(EditAnywhere, Category = "Interchange | Pipeline | MeshesInstance")` — All mesh geometry referenced by this MeshInstance.
- L77 _public prototype_ `bool IsNestedInSkeleton() const;` — Returns true if this mesh instance is instanced from a Joint node (i.e. part of a skeleton)
- L80 _public prototype_ `bool DoNotInstantiateInLevel() const;` — Returns true if the associated SceneNode is flagged as DoNotInstantiateInLevel.

#### struct `FInterchangeMeshGeometry`  
`struct FInterchangeMeshGeometry`  
_L87-178_
- reflection: `USTRUCT(BlueprintType)`
- desc: A mesh geometry is a description of a translated mesh asset node that defines a geometry.
- L91 _public function_ `FInterchangeMeshGeometry() : BaseNode(nullptr) , bIsReferencedBySkeleton(false) , bHasTransformAnimationTrack(false) , bIsMorphTarget(false) , bIsSkinnedMesh(false) , bHasMorphTargetDependencies(false) , bHasSkeletonDependencies(false) , bHasAssemblyPartDependencies(false) , AssemblyPartDependenciesArray() , AllUnderlyingMeshNodeUidsArray()`
- L109 _public member_ `TObjectPtr<const UInterchangeBaseNode> BaseNode = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Interchange | Pipeline | MeshesGeometry")` — The UInterchangeMeshNode or UInterchangeMeshLODContainerNode pointer represented by this structure.
- L115 _public member_ `TArray<FString> UidsOfInstancingNodes;` — `UPROPERTY(EditAnywhere, Category = "Interchange | Pipeline | MeshesGeometry")` — All instancing Node Uids.
- L121 _public member_ `TArray<FString> AttachedSocketUids;` — `UPROPERTY(EditAnywhere, Category = "Interchange | Pipeline | MeshesGeometry")` — A list of all scene nodes that represent sockets attached to this mesh.
- L127 _public member_ `bool bIsReferencedBySkeleton;` — `UPROPERTY(EditAnywhere, Category = "Interchange | Pipeline | MeshesGeometry")` — Indicates that at least 1 of the Instancing Node Uids is a Joint (aka part of a skeleton) or not.
- L133 _public member_ `bool bHasTransformAnimationTrack;` — `UPROPERTY(EditAnywhere, Category = "Interchange | Pipeline | MeshesGeometry")` — Indicates that at least 1 of the Instancing Node Uids has a transform animation.
- L135 _public prototype_ `void SetupMeshGeometry(const UInterchangeBaseNodeContainer& BaseNodeContainer, const UInterchangeBaseNode* InBaseNode);`
- L137 _public prototype_ `bool IsMorphTarget() const;`
- L138 _public function_ `bool IsSkinnedMesh() const`
- L139 _public function_ `bool HasMorphTargetDependencies() const`
- L140 _public function_ `bool HasSkeletonDependecies() const`
- L141 _public function_ `bool HasAssemblyPartDependencies() const`
- L142 _public function_ `void GetAssemblyPartDependencies(TArray<FString>& AssemblyPartDependencies) const`
- L144 _public prototype_ `FString GetSkeletonRootUid(const UInterchangeBaseNodeContainer& BaseNodeContainer, const TArray<FString>& SkeletonRootNodeUids) const;`
- L152 _private prototype_ `template <class T> T ParseMeshOrLODContainerNode(const UInterchangeBaseNodeContainer& BaseNodeContainer, T DefaultValue, TFunctionRef<T(T, T)> HandleConflictFunction, TFunctionRef<T(const UInterchangeMeshNode* MeshNode)> MeshFunction) const;` — Helper function to parse/process the above public functions on a UInterchangeMeshnode or UInterchangeMeshLODContainerNode.
- L154 _private prototype_ `static bool BoolConflictHandler(bool bLeft, bool bRight);`
- L158 _private prototype_ `static FString StringConflictHandler(const FString& Left, const FString& Right);` — Used for handling SkeletonRootUid conflicts, which shouldn't happen.
- L164 _private prototype_ `void SetIsSkinnedMesh(const UInterchangeBaseNodeContainer& BaseNodeContainer);` — Helper functions to set values
- L165 _private prototype_ `void SetHasMorphTargetDependencies(const UInterchangeBaseNodeContainer& BaseNodeContainer);`
- L166 _private prototype_ `void SetHasSkeletonDependecies(const UInterchangeBaseNodeContainer& BaseNodeContainer);`
- L167 _private prototype_ `void SetHasAssemblyPartDependencies(const UInterchangeBaseNodeContainer& BaseNodeContainer);`
- L168 _private prototype_ `void SetAssemblyPartDependencies(const UInterchangeBaseNodeContainer& BaseNodeContainer);`
- L171 _private member_ `bool bIsMorphTarget;` — Values:
- L172 _private member_ `bool bIsSkinnedMesh;`
- L173 _private member_ `bool bHasMorphTargetDependencies;`
- L174 _private member_ `bool bHasSkeletonDependencies;`
- L175 _private member_ `bool bHasAssemblyPartDependencies;`
- L176 _private member_ `TArray<FString> AssemblyPartDependenciesArray;`
- L177 _private member_ `TArray<FString> AllUnderlyingMeshNodeUidsArray;`

#### struct `FInterchangePipelineMeshesUtilitiesContext`  
`struct FInterchangePipelineMeshesUtilitiesContext`  
_L184-261_
- reflection: `USTRUCT(BlueprintType)`
- desc: Represents the context UInterchangePipelineMeshesUtilities will use when the client queries data.
- L189 _public prototype_ `FInterchangePipelineMeshesUtilitiesContext() = default;`
- L190 _public prototype_ `FInterchangePipelineMeshesUtilitiesContext(const FInterchangePipelineMeshesUtilitiesContext&) = default;`
- L191 _public prototype_ `FInterchangePipelineMeshesUtilitiesContext(FInterchangePipelineMeshesUtilitiesContext&&) = default;`
- L192 _public prototype_ `FInterchangePipelineMeshesUtilitiesContext& operator=(const FInterchangePipelineMeshesUtilitiesContext&) = default;`
- L193 _public prototype_ `FInterchangePipelineMeshesUtilitiesContext& operator=(FInterchangePipelineMeshesUtilitiesContext&&) = default;`
- L200 _public member_ `EInterchangeForceMeshType ForceMeshType = EInterchangeForceMeshType::IFMT_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange | Pipeline | MeshesContext")` — Whether to force import all meshes as Static Meshes or Skeletal Meshes.
- L206 _public member_ `bool bConvertStaticsWithAnimatedTransformToSkeletals = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange | Pipeline | MeshesContext")` — If enabled, all static meshes that have a transform animation will be imported as skeletal meshes instead.
- L212 _public member_ `bool bConvertStaticsWithMorphTargetsToSkeletals = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange | Pipeline | MeshesContext", meta = (DisplayName = "Convert Static Meshes with Morph Targets to Skeletal Meshes"))` — If enabled, all static meshes that have morph targets will be imported as skeletal meshes instead.
- L218 _public member_ `bool bConvertStaticsInBoneHierarchyToSkeletals = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange | Pipeline | MeshesContext")` — If enabled, all static meshes nested in bone hierarchies will be imported as skeletal meshes instead.
- L224 _public member_ `bool bQueryGeometryOnlyIfNoInstance = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange | Pipeline | MeshesContext")` — When querying geometry, this flag will not add MeshGeometry if there is a scene node that points to a geometry.
- L230 _public member_ `bool bIgnoreGeometryCaches = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange | Pipeline | MeshesContext")` — If enabled, all geometry caches will be ignored. The mesh utility will not return any geometry caches.
- L234 _public member_ `bool bImportMeshesInBoneHierarchy_DEPRECATED = true;` — `UE_DEPRECATED(5.8, "Use bConvertStaticsInBoneHierarchyToSkeletals instead.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use bConvertStaticsInBoneHierarchyToSkeletals instead."))`
- L238 _public member_ `bool bConvertStaticMeshToSkeletalMesh_DEPRECATED = false;` — `UE_DEPRECATED(5.8, "Use ForceMeshType instead.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use ForceMeshType instead."))`
- L242 _public member_ `bool bConvertSkeletalMeshToStaticMesh_DEPRECATED = false;` — `UE_DEPRECATED(5.8, "Use ForceMeshType instead.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use ForceMeshType instead."))`
- L246 _public member_ `bool bIgnoreStaticMeshes_DEPRECATED = false;` — `UE_DEPRECATED(5.8, "Use ForceMeshType instead.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use ForceMeshType instead."))`
- L248 _public prototype_ `bool IsStaticMeshInstance(const FInterchangeMeshInstance& MeshInstance, UInterchangeBaseNodeContainer* BaseNodeContainer);`
- L249 _public prototype_ `bool IsSkeletalMeshInstance(const FInterchangeMeshInstance& MeshInstance, UInterchangeBaseNodeContainer* BaseNodeContainer);`
- L250 _public prototype_ `bool IsGeometryCacheInstance(const FInterchangeMeshInstance& MeshInstance);`
- L251 _public prototype_ `bool IsStaticMeshGeometry(const FInterchangeMeshGeometry& MeshGeometry);`
- L252 _public prototype_ `bool IsSkeletalMeshGeometry(const FInterchangeMeshGeometry& MeshGeometry);`
- L253 _public prototype_ `bool IsGeometryCacheGeometry(const FInterchangeMeshGeometry& MeshGeometry);`
- L256 _public function_ `inline bool IsSkeletalMeshInstance(const FInterchangeMeshInstance& MeshInstance, UInterchangeBaseNodeContainer* BaseNodeContainer, bool& bOutIsStaticMeshNestedInSkeleton)` — `UE_DEPRECATED(5.8, "Use IsSkeletalMeshInstance(const FInterchangeMeshInstance& MeshInstance, UInterchangeBaseNodeContainer* BaseNodeContainer) instead.")`

#### class `UInterchangePipelineMeshesUtilities`  
`class UInterchangePipelineMeshesUtilities : public UObject`  
_L265-463_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: /
- L273 _public prototype_ `static UInterchangePipelineMeshesUtilities* CreateInterchangePipelineMeshesUtilities(UInterchangeBaseNodeContainer* BaseNodeContainer);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Pipeline | Meshes")` — Create an instance of UInterchangePipelineMeshesUtilities.
- L279 _public prototype_ `void GetAllMeshInstanceUids(TArray<FString>& MeshInstanceUids) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Pipeline | Meshes")` — Get the unique IDs of all mesh instances.
- L284 _public prototype_ `void IterateAllMeshInstance(TFunctionRef<void(const FInterchangeMeshInstance&)> IterationLambda) const;` — Iterate over all mesh instances.
- L290 _public prototype_ `void GetAllSkinnedMeshInstance(TArray<FString>& MeshInstanceUids) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Pipeline | Meshes")` — Get the unique IDs of all skinned mesh instances.
- L295 _public prototype_ `void IterateAllSkinnedMeshInstance(TFunctionRef<void(const FInterchangeMeshInstance&)> IterationLambda) const;` — Iterate over all skinned mesh instances.
- L301 _public prototype_ `void GetAllStaticMeshInstance(TArray<FString>& MeshInstanceUids, const bool bAllowNotVisibles = true) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Pipeline | Meshes")` — Get the unique IDs of all static mesh instances.
- L306 _public prototype_ `void IterateAllStaticMeshInstance(TFunctionRef<void(const FInterchangeMeshInstance&)> IterationLambda) const;` — Iterate over all static mesh instances.
- L312 _public prototype_ `void GetAllGeometryCacheInstance(TArray<FString>& MeshInstanceUids) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Pipeline | Meshes")` — Get the unique IDs of all geometry cache instances.
- L317 _public prototype_ `void IterateAllGeometryCacheInstance(TFunctionRef<void(const FInterchangeMeshInstance&)> IterationLambda) const;` — Iterate over all geometry cache instances.
- L323 _public prototype_ `void GetAllMeshGeometry(TArray<FString>& MeshGeometryUids) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Pipeline | Meshes")` — Get the unique IDs of all mesh geometry.
- L328 _public prototype_ `void IterateAllMeshGeometry(TFunctionRef<void(const FInterchangeMeshGeometry&)> IterationLambda) const;` — Iterate over all mesh geometry.
- L334 _public prototype_ `void GetAllSkinnedMeshGeometry(TArray<FString>& MeshGeometryUids) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Pipeline | Meshes")` — Get the unique IDs of all skinned mesh geometry.
- L339 _public prototype_ `void IterateAllSkinnedMeshGeometry(TFunctionRef<void(const FInterchangeMeshGeometry&)> IterationLambda) const;` — Iterate over all skinned mesh geometry.
- L345 _public prototype_ `void GetAllStaticMeshGeometry(TArray<FString>& MeshGeometryUids) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Pipeline | Meshes")` — Get the unique IDs of all static mesh geometry.
- L350 _public prototype_ `void IterateAllStaticMeshGeometry(TFunctionRef<void(const FInterchangeMeshGeometry&)> IterationLambda) const;` — Iterate over all static mesh geometry.
- L356 _public prototype_ `void GetAllGeometryCacheGeometry(TArray<FString>& MeshGeometryUids) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Pipeline | Meshes")` — Get the unique IDs of all geometry cache geometry.
- L361 _public prototype_ `void IterateAllGeometryCacheGeometry(TFunctionRef<void(const FInterchangeMeshGeometry&)> IterationLambda) const;` — Iterate over all geometry cache geometry.
- L367 _public prototype_ `void GetAllMeshGeometryNotInstanced(TArray<FString>& MeshGeometryUids) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Pipeline | Meshes")` — Get the unique IDs of all non-instanced mesh geometry.
- L372 _public prototype_ `void IterateAllMeshGeometryNotIntanced(TFunctionRef<void(const FInterchangeMeshGeometry&)> IterationLambda) const;` — Iterate over all non-instanced mesh geometry.
- L378 _public prototype_ `bool IsValidMeshInstanceUid(const FString& MeshInstanceUid) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Pipeline | Meshes")` — Return true if there is an existing FInterchangeMeshInstance that matches the MeshInstanceUid key.
- L384 _public prototype_ `const FInterchangeMeshInstance& GetMeshInstanceByUid(const FString& MeshInstanceUid) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Pipeline | Meshes")` — Get the instanced mesh from the unique ID.
- L390 _public prototype_ `bool IsValidMeshGeometryUid(const FString& MeshGeometryUid) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Pipeline | Meshes")` — Return true if there is an existing FInterchangeMeshGeometry that matches the MeshInstanceUid key.
- L396 _public prototype_ `const FInterchangeMeshGeometry& GetMeshGeometryByUid(const FString& MeshGeometryUid) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Pipeline | Meshes")` — Get the geometry mesh from the unique ID.
- L402 _public prototype_ `void GetAllMeshInstanceUidsUsingMeshGeometryUid(const FString& MeshGeometryUid, TArray<FString>& MeshInstanceUids) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Pipeline | Meshes")` — Get all instanced mesh UIDs that use the mesh geometry unique ID.
- L407 _public prototype_ `void IterateAllMeshInstanceUsingMeshGeometry(const FString& MeshGeometryUid, TFunctionRef<void(const FInterchangeMeshInstance&)> IterationLambda) const;` — Iterate over all instanced mesh UIDs that use the mesh geometry unique ID.
- L416 _public prototype_ `void GetCombinedSkinnedMeshInstances(TMap<FString, TArray<FString>>& OutMeshInstanceUidsPerSkeletonRootUid, bool bUseSingleBoneForConvertedMeshes = false, bool bVisibleOnly = false) const;` — Return a list of skinned FInterchangeMeshInstance UIDs that can be combined together. We cannot create a skinned mesh that has multiple skeleton root nodes. This function returns a combined MeshInstance per skeleton roots. @Param bUseSingleBoneForConvertedMeshes - If true, the skeleton roots assigned to non-skinned meshes will be using a single bone. Otherwise, the skeleton will follow the hierarchy scene node hierarchy. @Param bVisibleOnly - If true, invisible meshes will be ignored
- L424 _public prototype_ `FString GetMeshInstanceSkeletonRootUid(const FString& MeshInstanceUid) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Pipeline | Meshes")` — Return the skeleton root node UID. This is the UID for a UInterchangeSceneNode that has a "Joint" specialized type. Return an empty string if the MeshInstanceUid parameter points to nothing.
- L426 _public prototype_ `FString GetMeshInstanceSkeletonRootUid(const FInterchangeMeshInstance& MeshInstance) const;`
- L433 _public prototype_ `FString GetMeshGeometrySkeletonRootUid(const FString& MeshGeometryUid) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Pipeline | Meshes")` — Return the skeleton root node UID. This is the UID for a UInterchangeSceneNode that has a "Joint" specialized type. Return an empty string if the MeshGeometryUid parameter points to nothing.
- L435 _public prototype_ `FString GetMeshGeometrySkeletonRootUid(const FInterchangeMeshGeometry& MeshGeometry) const;`
- L440 _public prototype_ `bool HasAssemblyMeshDependencies() const;` — Returns true if there are nanite assembly mesh-to-mesh dependencies specified by the input meshes.
- L445 _public prototype_ `bool IsAssemblyMeshUid(const FString& MeshUid) const;` — Returns true if the given mesh uid is the base or part mesh of a nanite assembly.
- L449 _public function_ `void SetContext(const FInterchangePipelineMeshesUtilitiesContext& Context) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Pipeline | Meshes")`
- L455 _protected member_ `TMap<FString, FInterchangeMeshGeometry> MeshGeometriesPerMeshUid;`
- L456 _protected member_ `TMap<FString, FInterchangeMeshInstance> MeshInstancesPerMeshInstanceUid;`
- L457 _protected member_ `TMap<FString, FString> SkeletonRootUidPerMeshUid;`
- L458 _protected member_ `TSet<FString> AssemblyMeshUids;`
- L460 _protected member_ `UInterchangeBaseNodeContainer* BaseNodeContainer;`
- L462 _protected member_ `mutable FInterchangePipelineMeshesUtilitiesContext CurrentDataContext;`

#### struct `UE::Interchange::MeshesUtilities::ReorderSlotMaterialDependencies::FOrderHelper`  
`struct FOrderHelper`  
_L546-556_
- L548 _public member_ `int32 Index;`
- L549 _public member_ `FString Name;`
- L550 _public function_ `FOrderHelper(int32 InIndex, const FString& InName) : Index(InIndex) , Name(InName)`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API INTERCHANGEPIPELINES_API`
- L18 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogInterchangePipelineMeshesUtilities, Log, All);`
- L18 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogInterchangePipelineMeshesUtilities, Log, All);`
- L465 _namespace_ `namespace UE`
- L465 _namespace_ `namespace Interchange` (scope `UE`)
- L465 _namespace_ `namespace MeshesUtilities` (scope `UE::Interchange`)
- L473 _function_ `template<class T> void ApplySlotMaterialDependencies(T& FactoryNode , const TMap<FString, FString>& SlotMaterialDependencies , const UInterchangeBaseNodeContainer& NodeContainer , TMap<FString, FString> *ExistingSlotMaterialDependenciesPtr)` (scope `UE::Interchange::MeshesUtilities`) — Applies material slot dependencies stored in SlotMaterialDependencies to FactoryNode. If the caller want to support bKeepSectionSeparate feature it must provide a valid ExistingSlotMaterialDependenciesPtr.
- L538 _function_ `template<class T> void ReorderSlotMaterialDependencies(T& FactoryNode, const UInterchangeBaseNodeContainer& NodeContainer)` (scope `UE::Interchange::MeshesUtilities`)
- L590 _function_ `` (scope `UE::Interchange::MeshesUtilities::ReorderSlotMaterialDependencies`)

### `Plugins/Interchange/Runtime/Source/Pipelines/Public/InterchangePipelineObjectVersion.h` (Public)


#### struct `FFortniteMainInterchangePipelineObjectVersion`  
`struct FFortniteMainInterchangePipelineObjectVersion`  
_L6-27_
- L9 _public prototype_ `FFortniteMainInterchangePipelineObjectVersion() = delete;` — Not instantiable.
- L26 _public member_ `const static FGuid GUID;` — The GUID for this custom version number

#### enum `FFortniteMainInterchangePipelineObjectVersion::Type`  
`enum Type`  
_L11-23_
- L13 _public enumerator_ `InitialVersion`
- L16 _public enumerator_ `InterchangeAddCurveMetadataToSkeletonPropertyMove` — Interchange Move generic animation pipeline property bAddCurveMetadataToSkeleton to the generic shared skeletalmesh and animation pipeline
- L18 _public enumerator_ `InterchangeAddFrameAlignmentGenericAnimationPipelineConfig`
- L21 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L22 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

### `Plugins/Interchange/Runtime/Source/Pipelines/Public/InterchangePipelinesModule.h` (Public)


#### class `IInterchangePipelinesModule`  
`class IInterchangePipelinesModule : public IModuleInterface`  
_L13-38_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L24 _public function_ `static inline IInterchangePipelinesModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L34 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Interchange/Runtime/Source/Pipelines/Public/InterchangeSparseVolumeTexturePipeline.h` (Public)


#### class `UInterchangeSparseVolumeTexturePipeline`  
`class UInterchangeSparseVolumeTexturePipeline : public UInterchangePipelineBase`  
_L19-65_
- reflection: `UCLASS(MinimalAPI, BlueprintType, editinlinenew)`
- inherits: `UInterchangePipelineBase`
- L24 _public prototype_ `static FString GetPipelineCategory(UClass* AssetClass);`
- L32 _public member_ `FString PipelineDisplayName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Volumes", meta = (StandAlonePipelineProperty = "True", PipelineInternalEditionData = "True"))`
- L36 _public member_ `bool bImportSparseVolumeTextures = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Volumes")` — If enabled, imports all sparse volume texture assets found in the source.
- L43 _public member_ `bool bImportAnimatedSparseVolumeTextures = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Volumes")` — If enabled, will attempt to import volume nodes corresponding to numbered files in the same folder as individual frames of an animated SparseVolumeTextures.
- L47 _public member_ `FString AssetName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Volumes", meta = (StandAlonePipelineProperty = "True"))` — If set, and there is only one asset and one source, the imported asset will be given this name.
- L50 _public prototype_ `virtual void AdjustSettingsForContext(const FInterchangePipelineContextParams& ContextParams) override;`
- L51 _public prototype_ `virtual void ExecutePipeline( UInterchangeBaseNodeContainer* InBaseNodeContainer, const TArray<UInterchangeSourceData*>& InSourceDatas, const FString& ContentBasePath ) override;`
- L57 _public prototype_ `virtual bool IsPropertyChangeNeedRefresh(const FPropertyChangedEvent& PropertyChangedEvent) const override;`
- L58 _public prototype_ `virtual void FilterPropertiesFromTranslatedData(UInterchangeBaseNodeContainer* InBaseNodeContainer) override;`
- L59 _public prototype_ `virtual void GetSupportAssetClasses(TArray<UClass*>& PipelineSupportAssetClasses) const override;`
- L64 _private member_ `TObjectPtr<UInterchangeBaseNodeContainer> BaseNodeContainer;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API INTERCHANGEPIPELINES_API`

### `Plugins/Interchange/Runtime/Source/Pipelines/Public/InterchangeglTFPipeline.h` (Public)


#### class `UGLTFPipelineSettings`  
`class UGLTFPipelineSettings : public UDeveloperSettings`  
_L22-46_
- reflection: `UCLASS(MinimalAPI, config = Interchange, meta = (DisplayName = "glTF Settings", ToolTip = "Interchange settings for glTF conversions."))`
- inherits: `UDeveloperSettings`
- L28 _public member_ `TMap<FString, FSoftObjectPath> MaterialParents;` — `UPROPERTY(EditAnywhere, config, Category = "PredefinedglTFMaterialLibrary", meta = (DisplayName = "Predefined glTF Material Library"))`
- L30 _public prototype_ `TArray<FString> ValidateMaterialInstancesAndParameters() const;`
- L32 _public prototype_ `UInterchangeMaterialInstanceFactoryNode* BuildMaterialInstance(UInterchangeBaseNodeContainer* NodeContainer, const UInterchangeShaderGraphNode* ShaderGraphNode, const FString& OldFactoryNodeUId);`
- L34 _public function_ `bool IsMaterialParentsEditible()`
- L35 _public function_ `void SetMaterialParentsEditible(bool bEditible)`
- L37 _private prototype_ `TSet<FString> GenerateExpectedParametersList(const FString& Identifier) const;`
- L39 _private member_ `static const TArray<FString> ExpectedMaterialInstanceIdentifiers;` — Default MaterialInstance' identifiers
- L45 _private member_ `bool bMaterialParentsEditible = true;` — Helper for the Settings Customizer to decide if the ParentMaterials should be editable or not. Should be editable from Project Settings, and should NOT be editable from the Import. It is set by the Pipeline's Customizer. Equals to Pipeline->CanEditPropertiesStates()

#### class `UInterchangeGLTFPipeline`  
`class UInterchangeGLTFPipeline : public UInterchangePipelineBase`  
_L49-72_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangePipelineBase`
- L53 _private prototype_ `UInterchangeGLTFPipeline();`
- L59 _public member_ `FString PipelineDisplayName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Common", meta = (StandAlonePipelineProperty = "True", PipelineInternalEditionData = "True"))` — The name of the pipeline that will be display in the import dialog.
- L61 _public member_ `TObjectPtr<UGLTFPipelineSettings> GLTFPipelineSettings;`
- L64 _protected prototype_ `virtual void AdjustSettingsForContext(const FInterchangePipelineContextParams& ContextParams) override;`
- L65 _protected prototype_ `virtual void ExecutePipeline(UInterchangeBaseNodeContainer* BaseNodeContainer, const TArray<UInterchangeSourceData*>& SourceDatas, const FString& ContentBasePath) override;`
- L67 _protected function_ `virtual bool CanExecuteOnAnyThread(EInterchangePipelineTask PipelineTask) override`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API INTERCHANGEPIPELINES_API`
