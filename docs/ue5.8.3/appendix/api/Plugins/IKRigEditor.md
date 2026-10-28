# Plugins / IKRigEditor

- module root: `Plugins/Animation/IKRig/Source/IKRigEditor`
- headers: 66; symbols: 2227
- symbol kinds: class=116, delegate=16, enum=15, enumerator=53, externvar=2, function=189, macro=9, member=657, namespace=2, prototype=1095, struct=58, typedef=15
- PrivateDependencyModuleNames: AnimGraph, AnimGraphRuntime, AnimationBlueprintLibrary, AnimationCore, AnimationWidgets, ApplicationCore, AssetTools, BlueprintGraph, ContentBrowser, CoreUObject, EditorFramework, EditorWidgets, Engine, IKRig, IKRigDeveloper, InputCore, Kismet, KismetWidgets, MeshDescription, MessageLog, Persona, PropertyEditor, SkeletalMeshDescription, SkeletonEditor, Slate, SlateCore, StructUtilsEditor, ToolMenus, ToolWidgets, UnrealEd
- PublicDependencyModuleNames: AdvancedPreviewScene, Core

### `Plugins/Animation/IKRig/Source/IKRigEditor/Private/RetargetEditor/CurveUtils.h` (Private)


#### class `FCurveUtils`  
`class FCurveUtils`  
_L18-43_
- desc: Simple helper class to contain function for loading curve values from anim sequence. Note, these functions are copies from ones in the RigMapper plugin Subsystem, but we do not want to make IKRig depend upon this plugin whilst it is experimental, and does not seem worthwhile making an additional plugin. When RigMapper plugin moves out of experimental, this code should be re-consolidated.
- L23 _public typedef_ `using FPoseValues = TArray<TOptional<float>>;`
- L24 _public typedef_ `using FFrameValues = TArray<FCurveUtils::FPoseValues>;`
- L29 _public prototype_ `static bool LoadCurveValuesFromAnimSequence(const UAnimSequence* InSource, const USkeleton* InSourceSkeleton, TArray<FName>& OutCurveNames, TArray<FFrameTime>& OutFrameTimes, FCurveUtils::FFrameValues& OutCurveValuesPerFrame, TArray<int32> & OutCurveFlags, TArray<FLinearColor> & OutCurveColors);` — Load curve values from animation sequence
- L34 _public prototype_ `static FFrameRate GetAnimSequenceRate(const UAnimSequence* AnimSequence);` — Get the frame rate for the animation sequence
- L38 _private prototype_ `static bool LoadCurveValuesFromAnimSequence(const UAnimSequence* InSource, TArray<FString>& OutCurveNames, TArray<FFrameTime>& OutFrameTimes, FFrameValues& OutCurveValuesPerFrame);`
- L39 _private typedef_ `using FPose = TMap<FString, float>;`
- L40 _private typedef_ `using FFramePoses = TArray<FCurveUtils::FPose>;`
- L41 _private prototype_ `static bool BakeSparseKeys(const FFramePoses& InPoses, const TArray<FString>& InCurveNames, TArray<FFrameTime>& OutFrameTimes, FFrameValues& OutCurveValuesPerFrame);`
- L42 _private prototype_ `static void SparseBakeCurve(const FString& InCurveName, int32 InCurveIndex, float InCurveValue, FFrameValues& OutCurveValuesPerFrame, const TArray<FFrameTime>& InFrameTimesInOrder, int32 InFrameIndex, const FFramePoses& InPoses, const TArray<FFrameTime>& InFrameTimes, const int32 InActualFrameIndex);`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/IKRigEditor.h` (Public)


#### class `FIKRigEditor`  
`class FIKRigEditor : public IModuleInterface`  
_L10-22_
- inherits: `IModuleInterface`
- L13 _public prototype_ `void StartupModule() override;`
- L14 _public prototype_ `void ShutdownModule() override;`
- L17 _private member_ `TSharedPtr<class FAssetTypeActions_AnimationAssetRetarget> RetargetAnimationAssetAction;`
- L18 _private member_ `TSharedPtr<class FAssetTypeActions_IKRigDefinition> IKRigDefinitionAssetAction;`
- L19 _private member_ `TSharedPtr<class FAssetTypeActions_IKRetargeter> IKRetargeterAssetAction;`
- L21 _private member_ `TArray<FName> ClassesToUnregisterOnShutdown;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API IKRIGEDITOR_API`
- L24 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogIKRigEditor, Warning, All);`
- L24 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogIKRigEditor, Warning, All);`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/AssetTypeActions_IKRetargeter.h` (Public)


#### class `FAssetTypeActions_IKRetargeter`  
`class FAssetTypeActions_IKRetargeter : public FAssetTypeActions_Base`  
_L12-28_
- inherits: `FAssetTypeActions_Base`
- L16 _public function_ `virtual FText GetName() const override` — BEGIN IAssetTypeActions
- L17 _public function_ `virtual FColor GetTypeColor() const override`
- L18 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L19 _public prototype_ `virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;`
- L20 _public function_ `virtual uint32 GetCategories() override`
- L21 _public prototype_ `virtual UThumbnailInfo* GetThumbnailInfo(UObject* Asset) const override;`
- L22 _public prototype_ `virtual const TArray<FText>& GetSubMenus() const override;`
- L25 _public prototype_ `static void ExtendIKRigMenuToMakeRetargeter();`
- L26 _public prototype_ `static void CreateNewIKRetargeterFromIKRig(UObject* InSelectedObject);`
- L27 _public prototype_ `static void ExtendAnimAssetMenusForBatchRetargeting();`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/IKRetargetAnimInstance.h` (Public)


#### struct `FAnimNode_PreviewRetargetPose`  
`struct FAnimNode_PreviewRetargetPose : public FAnimNode_Base`  
_L16-45_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_Base`
- desc: a node just to preview a retarget pose
- L20 _public member_ `FPoseLink InputPose;`
- L23 _public member_ `TObjectPtr<UIKRetargeter> IKRetargeterAsset = nullptr;` — Retarget asset holding the pose to preview.
- L26 _public member_ `ERetargetSourceOrTarget SourceOrTarget;` — Whether to preview the source or the target
- L29 _public member_ `float RetargetPoseBlend = 1.0f;` — Amount to blend the retarget pose with the reference pose when shoing the retarget pose
- L32 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;` — FAnimNode_Base interface
- L33 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L36 _public function_ `const TArray<FTransform>& GetLocalRetargetPose() const`
- L37 _public function_ `const TArray<FTransform>& GetGlobalRetargetPose() const`
- L41 _private member_ `TArray<int32> RequiredBoneToMeshBoneMap;` — mapping from required bone indices (from LODs) to actual bone indices within the skeletal mesh
- L43 _private member_ `TArray<FTransform> RetargetLocalPose;`
- L44 _private member_ `TArray<FTransform> RetargetGlobalPose;`

#### class `UIKRetargetAnimInstance`  
`class UIKRetargetAnimInstance : public UAnimPreviewInstance`  
_L48-82_
- reflection: `UCLASS(transient, NotBlueprintable)`
- inherits: `UAnimPreviewInstance`
- L54 _public prototype_ `void SetRetargetMode(const ERetargeterOutputMode& OutputMode);`
- L56 _public prototype_ `void SetRetargetPoseBlend(const float& RetargetPoseBlend);`
- L58 _public prototype_ `void ConfigureAnimInstance( const ERetargetSourceOrTarget& SourceOrTarget, UIKRetargeter* InIKRetargetAsset, TWeakObjectPtr<USkeletalMeshComponent> InSourceMeshComponent);`
- L63 _public prototype_ `void SetOverrideSets(const TArray<FName>& InOverrideSets);`
- L65 _public prototype_ `FIKRetargetProcessor* GetRetargetProcessor();`
- L67 _public prototype_ `const FAnimNode_RetargetPoseFromMesh& GetRetargetAnimNode();`
- L69 _public prototype_ `void ForceInitializeProcessor(USkeletalMeshComponent* TargetComponent);`
- L71 _public function_ `const TArray<FTransform>& GetLocalRetargetPose() const`
- L72 _public function_ `const TArray<FTransform>& GetGlobalRetargetPose() const`
- L75 _protected prototype_ `virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override;`
- L78 _protected member_ `FAnimNode_PreviewRetargetPose PreviewPoseNode;` — `UPROPERTY(Transient)`
- L81 _protected member_ `FAnimNode_RetargetPoseFromMesh RetargetNode;` — `UPROPERTY(Transient)`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/IKRetargetAnimInstanceProxy.h` (Public)


#### struct `FIKRetargetAnimInstanceProxy`  
`struct FIKRetargetAnimInstanceProxy : public FAnimPreviewInstanceProxy`  
_L18-58_
- reflection: `USTRUCT()`
- inherits: `FAnimPreviewInstanceProxy`
- desc: Proxy override for this UAnimInstance-derived class
- L24 _public prototype_ `FIKRetargetAnimInstanceProxy() = default;`
- L25 _public prototype_ `FIKRetargetAnimInstanceProxy( UAnimInstance* InAnimInstance, FAnimNode_PreviewRetargetPose* InPreviewPoseNode, FAnimNode_RetargetPoseFromMesh* InRetargetNode);`
- L29 _public prototype_ `virtual ~FIKRetargetAnimInstanceProxy() override = default;`
- L32 _public prototype_ `virtual void Initialize(UAnimInstance* InAnimInstance) override;` — FAnimPreviewInstanceProxy interface
- L33 _public prototype_ `virtual void CacheBones() override;`
- L34 _public prototype_ `virtual bool Evaluate(FPoseContext& Output) override;`
- L35 _public prototype_ `virtual void UpdateAnimationNode(const FAnimationUpdateContext& InContext) override;`
- L40 _public prototype_ `virtual FAnimNode_Base* GetCustomRootNode() override;` — Called when the anim instance is being initialized. These nodes can be provided
- L41 _public prototype_ `virtual void GetCustomNodes(TArray<FAnimNode_Base*>& OutNodes) override;`
- L44 _public prototype_ `void ConfigureAnimInstance( const ERetargetSourceOrTarget& InSourceOrTarget, UIKRetargeter* InIKRetargetAsset, TWeakObjectPtr<USkeletalMeshComponent> InSourceMeshComponent);`
- L49 _public prototype_ `void SetRetargetMode(const ERetargeterOutputMode& InOutputMode);`
- L51 _public prototype_ `void SetRetargetPoseBlend(const float& InRetargetPoseBlend) const;`
- L53 _public member_ `FAnimNode_PreviewRetargetPose* PreviewPoseNode;`
- L54 _public member_ `FAnimNode_RetargetPoseFromMesh* RetargetNode;`
- L56 _public member_ `ERetargetSourceOrTarget SourceOrTarget;`
- L57 _public member_ `ERetargeterOutputMode OutputMode;`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/IKRetargetApplicationMode.h` (Public)


#### class `FIKRetargetApplicationMode`  
`class FIKRetargetApplicationMode : public FApplicationMode`  
_L11-29_
- inherits: `FApplicationMode`
- L16 _public prototype_ `FIKRetargetApplicationMode(TSharedRef<class FWorkflowCentricApplication> InHostingApp, TSharedRef<class IPersonaPreviewScene> InPreviewScene);`
- L19 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;` — FApplicationMode interface
- L25 _protected member_ `TWeakPtr<FIKRetargetEditor> IKRetargetEditorPtr;` — The hosting app
- L28 _protected member_ `FWorkflowAllowedTabSet TabFactories;` — The tab factories we support

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/IKRetargetAssetBrowserTabSummoner.h` (Public)


#### struct `FIKRetargetAssetBrowserTabSummoner`  
`struct FIKRetargetAssetBrowserTabSummoner : public FWorkflowTabFactory`  
_L10-21_
- inherits: `FWorkflowTabFactory`
- L13 _public member_ `static const FName TabID;`
- L15 _public prototype_ `FIKRetargetAssetBrowserTabSummoner(const TSharedRef<FIKRetargetEditor>& InIKRetargetEditor);`
- L16 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L17 _public prototype_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override;`
- L20 _protected member_ `TWeakPtr<FIKRetargetEditor> IKRetargetEditor;`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/IKRetargetBatchOperation.h` (Public)


#### struct `FAdditiveRetargetSettings`  
`struct FAdditiveRetargetSettings`  
_L22-35_
- L25 _public member_ `TObjectPtr<UAnimSequence> SequenceAsset;` — the asset this operates on
- L28 _public member_ `TEnumAsByte<EAdditiveAnimationType> AdditiveAnimType;` — the settings to save/restore before/after retargeting
- L29 _public member_ `TEnumAsByte<EAdditiveBasePoseType> RefPoseType;`
- L30 _public member_ `int32 RefFrameIndex;`
- L31 _public member_ `TObjectPtr<UAnimSequence> RefPoseSeq;`
- L33 _public prototype_ `void PrepareForRetarget(UAnimSequence* InSequenceAsset);`
- L34 _public prototype_ `void RestoreOnAsset() const;`

#### enum `ERetargetRootLockMode`  
`enum class ERetargetRootLockMode : uint8`  
_L39-47_
- reflection: `UENUM()`
- desc: which skeleton are we referring to?
- L42 _public enumerator_ `FromSourceAnimation` — Uses the "ForceRootLock" setting in the source animation
- L44 _public enumerator_ `ForceRootLocked` — Force the root to be locked, regardless of whether the source animation has the root locked or not.
- L46 _public enumerator_ `ForceRootUnlocked` — Force the root to be unlocked, regardless of whether the source animation has the root locked or not.

#### struct `FIKRetargetBatchOperationContext`  
`struct FIKRetargetBatchOperationContext`  
_L50-111_
- desc: Data needed to run a batch "duplicate and retarget" operation on a set of animation assets
- L56 _public member_ `TArray<TWeakObjectPtr<UObject>> AssetsToRetarget;` — The source assets to duplicate and retarget
- L59 _public member_ `USkeletalMesh* SourceMesh = nullptr;` — Source mesh to use to copy animation FROM.
- L62 _public member_ `USkeletalMesh* TargetMesh = nullptr;` — Target mesh to use to copy animation TO.
- L65 _public member_ `UIKRetargeter* IKRetargetAsset = nullptr;` — The retargeter used to copy animation
- L68 _public member_ `EditorAnimUtils::FNameDuplicationRule NameRule;` — Rename rules for duplicated assets
- L72 _public member_ `bool bUseSourcePath = false;` — Any files with the same name will be overwritten instead of creating a new file with a numeric suffix. This is useful when iterating on a batch process.
- L76 _public member_ `bool bOverwriteExistingFiles = false;` — Any files with the same name will be overwritten instead of creating a new file with a numeric suffix. This is useful when iterating on a batch process.
- L79 _public member_ `bool bIncludeReferencedAssets = true;` — Duplicates and retargets any animation assets referenced by the input assets. For example, sequences in an animation blueprint or blendspace.
- L82 _public member_ `bool bExportOnlyAnimatedBones = true;` — Will not produce keys on bones that are not animated, reducing size on disk of the resulting files.
- L86 _public member_ `bool bRetainAdditiveFlags = true;` — Keep the additive animation sequence attributes on the retargeted results. NOTE: results may not be WYSIWYG with the editor, but the behavior should remain intact.
- L89 _public member_ `TArray<FName> OverrideSetNames;` — An array of property override sets to apply. These must be present in the supplied IK Retarget asset.
- L92 _public function_ `void Reset()` — Reset all data (called when window re-opened
- L106 _public function_ `bool IsValid() const` — Is the data configured in such a way that we could run the retarget?

#### struct `FIKRetargetBatchOperationInputs`  
`struct FIKRetargetBatchOperationInputs`  
_L117-177_
- reflection: `USTRUCT(BlueprintType)`
- desc: Input data for running a batch animation retarget. Using a struct allows for future expansion without breaking existing Blueprint nodes.
- L123 _public member_ `TArray<FAssetData> AssetsToRetarget;` — `UPROPERTY(BlueprintReadWrite, Category="IK Batch Retarget")` — A list of animation assets to retarget (sequences, blendspaces or montages)
- L127 _public member_ `TObjectPtr<USkeletalMesh> SourceMesh = nullptr;` — `UPROPERTY(BlueprintReadWrite, Category="IK Batch Retarget")` — The skeletal mesh with desired proportions to playback the assets to retarget
- L131 _public member_ `TObjectPtr<USkeletalMesh> TargetMesh = nullptr;` — `UPROPERTY(BlueprintReadWrite, Category="IK Batch Retarget")` — The skeletal mesh to retarget the animation onto
- L135 _public member_ `TObjectPtr<UIKRetargeter> IKRetargetAsset = nullptr;` — `UPROPERTY(BlueprintReadWrite, Category="IK Batch Retarget")` — The IK Retargeter asset with IK Rigs appropriate for the source and target skeletal mesh
- L139 _public member_ `TArray<FName> InOverrideSetNames;` — `UPROPERTY(BlueprintReadWrite, Category="IK Batch Retarget")` — An array of names of the property override sets to apply to the retarget (must be stored in the IK Retarget Asset)
- L143 _public member_ `FString Search = TEXT("");` — `UPROPERTY(BlueprintReadWrite, Category="Naming")` — A string to search for in the file name (replaced with "Replace" string)
- L147 _public member_ `FString Replace = TEXT("");` — `UPROPERTY(BlueprintReadWrite, Category="Naming")` — A string to replace with in the file name
- L151 _public member_ `FString Prefix = TEXT("");` — `UPROPERTY(BlueprintReadWrite, Category="Naming")` — A string to add to the start of the new file name
- L155 _public member_ `FString Suffix = TEXT("");` — `UPROPERTY(BlueprintReadWrite, Category="Naming")` — A string to add at the end of the new file name
- L159 _public member_ `FString TargetPath = TEXT("");` — `UPROPERTY(BlueprintReadWrite, Category="Pathing")` — A string containing the destination path for the retargeted assets. Ignored if bUseSourcePath is set to true.
- L163 _public member_ `bool bUseSourcePath = false;` — `UPROPERTY(BlueprintReadWrite, Category="Pathing")` — Place the assets in the same folder as their source location instead of the given target path.
- L167 _public member_ `bool bIncludeReferencedAssets = true;` — `UPROPERTY(BlueprintReadWrite, Category="IK Batch Retarget")` — Whether to retarget animation assets referenced by the AssetsToRetarget
- L171 _public member_ `bool bOverwriteExistingFiles = false;` — `UPROPERTY(BlueprintReadWrite, Category="IK Batch Retarget")` — Whether to overwrite any existing output files with the same name, or create new files with a unique name
- L176 _public member_ `bool bRetainAdditiveFlags = true;` — `UPROPERTY(BlueprintReadWrite, Category="IK Batch Retarget")` — Keep the additive animation sequence attributes on the retargeted results. NOTE: results may not be WYSIWYG with the editor, but the behavior should remain intact.

#### class `UIKRetargetBatchOperation`  
`class UIKRetargetBatchOperation : public UObject`  
_L181-272_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: Encapsulate ability to batch duplicate and retarget a set of animation assets
- L194 _public prototype_ `static TArray<FAssetData> RunBatchRetarget(const FIKRetargetBatchOperationInputs& Inputs);` — `UFUNCTION(BlueprintCallable, Category=IKBatchRetarget)` — Convenience function to run a batch animation retarget from Blueprint / Python. This function will duplicate a list of AssetsToRetarget and use the supplied IK Retargeter to retarget the animation from the source to the target using the settings in the provided IK Retargeter asset. @param Inputs a struct with all the inputs required to run a batch process @return a list of new animation files created
- L206 _public prototype_ `static TArray<FAssetData> DuplicateAndRetarget( const TArray<FAssetData>& AssetsToRetarget, USkeletalMesh* SourceMesh, USkeletalMesh* TargetMesh, UIKRetargeter* IKRetargetAsset, const FString& Search = TEXT(""), const FString& Replace = TEXT(""), const FString& Prefix = TEXT(""), const FString& Suffix = TEXT(""), const FString& TargetPath = TEXT(""), const bool bUseSourcePath = false, const bool bIncludeReferencedAssets = true, const bool bOverwriteExistingFiles = false);` — `UFUNCTION(BlueprintCallable, Category=IKBatchRetarget, meta=( DeprecatedFunction, DeprecationMessage="Use RunBatchRetarget instead. It uses a struct for better future-proofing and cleaner Blueprint graphs." ))` — `UE_DEPRECATED(5.8, "DuplicateAndRetarget is deprecated. Use RunBatchRetarget instead.")` — @deprecated This function is deprecated. Please use RunBatchRetarget which takes a FIKRetargetBatchOperationInputs struct.
- L221 _public prototype_ `void RunRetarget(FIKRetargetBatchOperationContext& Context);` — Actually run the process to duplicate and retarget the assets for the given context
- L225 _private prototype_ `void Reset();`
- L229 _private prototype_ `int32 GenerateAssetLists(const FIKRetargetBatchOperationContext& Context);` — Initialize set of referenced assets to retarget. @return	Number of assets that need retargeting.
- L232 _private prototype_ `void DuplicateRetargetAssets(const FIKRetargetBatchOperationContext& Context, FScopedSlowTask& Progress);` — Duplicate all the assets to retarget
- L235 _private prototype_ `void RetargetAssets(const FIKRetargetBatchOperationContext& Context, FScopedSlowTask& Progress);` — Retarget skeleton and animation on all the duplicates
- L238 _private prototype_ `void ConvertAnimation(const FIKRetargetBatchOperationContext& Context, FIKRetargetProcessor& OutProcessor, FScopedSlowTask& Progress);` — Convert animation on all the duplicates
- L241 _private prototype_ `void ApplyCurveOps(const FIKRetargetBatchOperationContext& Context, const FIKRetargetProcessor& InProcessor, FScopedSlowTask& Progress);` — Apply any curve operations on all the duplicates
- L244 _private prototype_ `void OverwriteExistingAssets(const FIKRetargetBatchOperationContext& Context, FScopedSlowTask& Progress);` — Replace existing assets (optional)
- L247 _private prototype_ `void NotifyUserOfResults(const FIKRetargetBatchOperationContext& Context, FScopedSlowTask& Progress) const;` — Output notifications of results
- L250 _private prototype_ `void GetNewAssets(TArray<UObject*>& NewAssets) const;` — Generate list of newly created assets to report to user
- L253 _private prototype_ `void CleanupIfCancelled(const FScopedSlowTask& Progress) const;` — If user cancelled half way, cleanup all the duplicated assets
- L257 _private prototype_ `void AddCurveValuesToAnimSequence(const UAnimSequence* InSourceSequence, USkeleton* InSourceSkeleton, USkeleton* InTargetSkeleton, const FIKRetargetCurvesOpBase::FCurveData& InCurveMetaData, const FIKRetargetCurvesOpBase::FFrameValues& InCurveValuesPerFrame, const FIKRetargetCurvesOpBase::FFrameValues& InOriginalCurveValuesPerFrame, const FFrameRate& InFrameRate, const TArray<FFrameTime>& InFrameTimes, bool bInShouldTransact, IAnimationDataController& OutTargetSeqController) const;` — Set the processed curve data into the target animation sequence. Curves not modified by any op are copied directly from source to preserve tangents and exact key times.
- L264 _private member_ `TArray<UAnimationAsset*> AnimationAssetsToRetarget;` — Lists of assets to retarget. Populated from selection during init
- L265 _private member_ `TArray<UAnimBlueprint*> AnimBlueprintsToRetarget;`
- L268 _private member_ `TMap<UAnimationAsset*, UAnimationAsset*> DuplicatedAnimAssets;` — Lists of original assets map to duplicate assets
- L269 _private member_ `TMap<UAnimBlueprint*, UAnimBlueprint*> DuplicatedBlueprints;`
- L271 _private member_ `TMap<UAnimationAsset*, UAnimationAsset*> RemappedAnimAssets;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API IKRIGEDITOR_API`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/IKRetargetCommands.h` (Public)


#### class `FIKRetargetCommands`  
`class FIKRetargetCommands : public TCommands<FIKRetargetCommands>`  
_L9-80_
- inherits: `TCommands<FIKRetargetCommands>`
- L12 _public function_ `FIKRetargetCommands() : TCommands<FIKRetargetCommands> ( "IKRetarget", NSLOCTEXT("Contexts", "IKRetarget", "IK Retarget"), NAME_None, FIKRetargetEditorStyle::Get().GetStyleSetName()`
- L22 _public member_ `TSharedPtr< FUICommandInfo > RunRetargeter;` — run the retargeter
- L24 _public member_ `TSharedPtr< FUICommandInfo > ShowRetargetPose;` — show current retarget pose
- L26 _public member_ `TSharedPtr< FUICommandInfo > EditRetargetPose;` — edit retarget pose
- L29 _public member_ `TSharedPtr< FUICommandInfo > ShowAssetSettings;` — open asset settings
- L31 _public member_ `TSharedPtr< FUICommandInfo > ShowOverrideSets;` — open the override set manager
- L33 _public member_ `TSharedPtr< FUICommandInfo > ShowVariables;` — open the variables editor
- L36 _public member_ `TSharedPtr< FUICommandInfo > EnableRoot;` — enable Root retarget pass
- L38 _public member_ `TSharedPtr< FUICommandInfo > EnableFK;` — enable FK retarget pass
- L40 _public member_ `TSharedPtr< FUICommandInfo > EnableIK;` — enable IK retarget pass
- L42 _public member_ `TSharedPtr< FUICommandInfo > EnablePostPass;` — enable IK retarget pass
- L45 _public member_ `TSharedPtr< FUICommandInfo > ResetAllBones;` — reset retarget pose to ref pose
- L47 _public member_ `TSharedPtr< FUICommandInfo > ResetSelectedBones;` — reset retarget pose to ref pose
- L49 _public member_ `TSharedPtr< FUICommandInfo > ResetSelectedAndChildrenBones;` — reset retarget pose to ref pose
- L52 _public member_ `TSharedPtr< FUICommandInfo > AlignAllBones;` — auto align all bones in skeleton
- L54 _public member_ `TSharedPtr< FUICommandInfo > AlignSelected;` — auto align selected bones
- L56 _public member_ `TSharedPtr< FUICommandInfo > AlignSelectedAndChildren;` — auto align selected bones and children
- L58 _public member_ `TSharedPtr< FUICommandInfo > SnapCharacterToGround;` — auto align selected bones
- L61 _public member_ `TSharedPtr< FUICommandInfo > DeleteRetargetPose;` — delete retarget pose
- L63 _public member_ `TSharedPtr< FUICommandInfo > RenameRetargetPose;` — rename retarget pose
- L65 _public member_ `TSharedPtr< FUICommandInfo > NewRetargetPose;` — new retarget pose
- L67 _public member_ `TSharedPtr< FUICommandInfo > DuplicateRetargetPose;` — duplicate retarget pose
- L70 _public member_ `TSharedPtr< FUICommandInfo > ImportRetargetPose;` — import retarget pose
- L72 _public member_ `TSharedPtr< FUICommandInfo > ImportRetargetPoseFromAnim;` — import retarget pose from anim
- L74 _public member_ `TSharedPtr< FUICommandInfo > ExportRetargetPose;` — export retarget pose
- L76 _public member_ `TSharedPtr< FUICommandInfo > ExportAnimation;` — export animation
- L79 _public prototype_ `virtual void RegisterCommands() override;` — initialize commands

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/IKRetargetDefaultMode.h` (Public)


#### class `FIKRetargetDefaultMode`  
`class FIKRetargetDefaultMode : public IPersonaEditMode`  
_L16-54_
- inherits: `IPersonaEditMode`
- L19 _public member_ `static FName ModeName;`
- L21 _public prototype_ `FIKRetargetDefaultMode() = default;`
- L24 _public function_ `void SetEditorController(const TSharedPtr<FIKRetargetEditorController> InEditorController)` — glue for all the editor parts to communicate
- L27 _public prototype_ `virtual bool GetCameraTarget(FSphere& OutTarget) const override;` — IPersonaEditMode interface
- L28 _public prototype_ `virtual IPersonaPreviewScene& GetAnimPreviewScene() const override;`
- L32 _public prototype_ `virtual void Initialize() override;` — FEdMode interface
- L33 _public prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;`
- L34 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L35 _public function_ `virtual bool IsCompatibleWith(FEditorModeID OtherModeID) const override`
- L36 _public prototype_ `virtual bool HandleClick(FEditorViewportClient* InViewportClient, HHitProxy* HitProxy, const FViewportClick& Click) override;`
- L37 _public prototype_ `virtual void Enter() override;`
- L38 _public prototype_ `virtual void Exit() override;`
- L42 _private prototype_ `void RenderDebugProxies(FPrimitiveDrawInterface* PDI, const FIKRetargetEditorController* Controller);`
- L45 _private member_ `ERetargetSourceOrTarget SkeletonMode;` — the skeleton currently being edited
- L48 _private member_ `TWeakPtr<FIKRetargetEditorController> EditorController;` — The hosting app
- L50 _private member_ `UE::Widget::EWidgetMode CurrentWidgetMode;`
- L51 _private member_ `bool bIsTranslating = false;`
- L53 _private member_ `bool bIsInitialized = false;`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/IKRetargetDetails.h` (Public)


#### enum `EIKRetargetTransformType`  
`enum class EIKRetargetTransformType : int8`  
_L16-22_
- L18 _public enumerator_ `Current`
- L19 _public enumerator_ `Reference`
- L20 _public enumerator_ `RelativeOffset`
- L21 _public enumerator_ `Bone`

#### class `UIKRetargetBoneDetails`  
`class UIKRetargetBoneDetails : public UObject`  
_L25-120_
- reflection: `UCLASS(MinimalAPI, config = Engine, hidecategories = UObject)`
- inherits: `UObject`
- L32 _public member_ `FName SelectedBone;` — `UPROPERTY(VisibleAnywhere, Category = "Selection")`
- L35 _public member_ `FTransform LocalTransform;` — `UPROPERTY()`
- L38 _public member_ `FTransform OffsetTransform;` — `UPROPERTY()`
- L41 _public member_ `FTransform CurrentTransform;` — `UPROPERTY()`
- L44 _public member_ `FTransform ReferenceTransform;` — `UPROPERTY()`
- L46 _public member_ `TWeakPtr<FIKRetargetEditorController> EditorController;`
- L50 _public prototype_ `FEulerTransform GetTransform(EIKRetargetTransformType TransformType, const bool bLocalSpace) const;`
- L51 _public prototype_ `bool IsComponentRelative(ESlateTransformComponent::Type Component, EIKRetargetTransformType TransformType) const;`
- L52 _public prototype_ `void OnComponentRelativeChanged(ESlateTransformComponent::Type Component, bool bIsRelative, EIKRetargetTransformType TransformType);`
- L53 _public prototype_ `void OnCopyToClipboard(ESlateTransformComponent::Type Component, EIKRetargetTransformType TransformType) const;`
- L54 _public prototype_ `void OnPasteFromClipboard(ESlateTransformComponent::Type Component, EIKRetargetTransformType TransformType);`
- L55 _public prototype_ `void OnNumericValueCommitted( ESlateTransformComponent::Type Component, ESlateRotationRepresentation::Type Representation, ESlateTransformSubComponent::Type SubComponent, FVector::FReal Value, ETextCommit::Type CommitType, EIKRetargetTransformType TransformType, bool bIsCommit);`
- L64 _public prototype_ `TOptional<FVector::FReal> GetNumericValue( EIKRetargetTransformType TransformType, ESlateTransformComponent::Type Component, ESlateRotationRepresentation::Type Representation, ESlateTransformSubComponent::Type SubComponent);`
- L71 _public prototype_ `static void OnMultiNumericValueCommitted( ESlateTransformComponent::Type Component, ESlateRotationRepresentation::Type Representation, ESlateTransformSubComponent::Type SubComponent, FVector::FReal Value, ETextCommit::Type CommitType, EIKRetargetTransformType TransformType, TArrayView<TObjectPtr<UIKRetargetBoneDetails>> Bones, bool bIsCommit);` — Method to react to changes of numeric values in the widget
- L82 _public prototype_ `template<typename DataType> void GetContentFromData(const DataType& InData, FString& Content) const;`
- L88 _private prototype_ `void CommitValueAsRelativeOffset( UIKRetargeterController* AssetController, const FReferenceSkeleton& RefSkeleton, const ERetargetSourceOrTarget SourceOrTarget, const int32 BoneIndex, UDebugSkelMeshComponent* Mesh, ESlateTransformComponent::Type Component, ESlateRotationRepresentation::Type Representation, ESlateTransformSubComponent::Type SubComponent, FVector::FReal Value, bool bShouldTransact);`
- L100 _private prototype_ `void CommitValueAsBoneSpace( UIKRetargeterController* AssetController, const FReferenceSkeleton& RefSkeleton, const ERetargetSourceOrTarget SourceOrTarget, const int32 BoneIndex, UDebugSkelMeshComponent* Mesh, ESlateTransformComponent::Type Component, ESlateRotationRepresentation::Type Representation, ESlateTransformSubComponent::Type SubComponent, FVector::FReal Value, bool bShouldTransact);`
- L112 _private prototype_ `static TOptional<FVector::FReal> CleanRealValue(TOptional<FVector::FReal> InValue);`
- L114 _private prototype_ `bool IsRootBone() const;`
- L116 _private member_ `bool BoneRelative[3] = { false, true, false };`
- L117 _private member_ `bool RelativeOffsetTransformRelative[3] = { false, true, false };`
- L118 _private member_ `bool CurrentTransformRelative[3];`
- L119 _private member_ `bool ReferenceTransformRelative[3];`

#### struct `FIKRetargetTransformWidgetData`  
`struct FIKRetargetTransformWidgetData`  
_L122-134_
- L124 _public function_ `FIKRetargetTransformWidgetData(EIKRetargetTransformType InType, FText InLabel, FText InTooltip)`
- L131 _public member_ `EIKRetargetTransformType TransformType;`
- L132 _public member_ `FText ButtonLabel;`
- L133 _public member_ `FText ButtonTooltip;`

#### struct `FIKRetargetTransformUIData`  
`struct FIKRetargetTransformUIData`  
_L136-143_
- L138 _public member_ `TArray<EIKRetargetTransformType> TransformTypes;`
- L139 _public member_ `TArray<FText> ButtonLabels;`
- L140 _public member_ `TArray<FText> ButtonTooltips;`
- L141 _public member_ `TAttribute<TArray<EIKRetargetTransformType>> VisibleTransforms;`
- L142 _public member_ `TArray<TSharedRef<IPropertyHandle>> Properties;`

#### class `FIKRetargetBoneDetailCustomization`  
`class FIKRetargetBoneDetailCustomization : public IDetailCustomization, FGCObject`  
_L145-170_
- inherits: `IDetailCustomization,FGCObject`
- L149 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L155 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L158 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L159 _public prototype_ `virtual FString GetReferencerName() const override;`
- L164 _private prototype_ `void GetTransformUIData( const bool bIsEditingPose, const IDetailLayoutBuilder& DetailBuilder, FIKRetargetTransformUIData& OutData) const;`
- L169 _private member_ `TArray<TObjectPtr<UIKRetargetBoneDetails>> Bones;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API IKRIGEDITOR_API`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/IKRetargetEditPoseMode.h` (Public)


#### enum `FIKRetargetTrackingState`  
`enum class FIKRetargetTrackingState : int8`  
_L17-22_
- L19 _public enumerator_ `None`
- L20 _public enumerator_ `RotatingBone`
- L21 _public enumerator_ `TranslatingRoot`

#### struct `FBoneEdit`  
`struct FBoneEdit`  
_L24-42_
- L26 _public member_ `FName Name;` — name of last selected bone
- L27 _public member_ `int32 Index;` — index of last selected bone
- L28 _public member_ `FTransform ParentGlobalTransform;` — global transform of parent of last selected bone
- L29 _public member_ `FTransform GlobalTransform;` — global transform of last selected bone
- L30 _public member_ `FTransform LocalTransform;` — local transform of last selected bone
- L31 _public member_ `FQuat AccumulatedGlobalOffset;` — the accumulated offset from rotation gizmo
- L33 _public member_ `TArray<FQuat> PreviousDeltaRotation;` — the prev stored local offsets of all selected bones
- L36 _public member_ `FVector AccumulatedPositionOffset;` — translation edits
- L38 _public function_ `void Reset()`

#### class `FIKRetargetEditPoseMode`  
`class FIKRetargetEditPoseMode : public IPersonaEditMode`  
_L44-107_
- inherits: `IPersonaEditMode`
- L47 _public member_ `static FName ModeName;`
- L49 _public prototype_ `FIKRetargetEditPoseMode() = default;`
- L52 _public function_ `void SetEditorController(const TSharedPtr<FIKRetargetEditorController> InEditorController)` — glue for all the editor parts to communicate
- L55 _public prototype_ `virtual bool GetCameraTarget(FSphere& OutTarget) const override;` — IPersonaEditMode interface
- L56 _public prototype_ `virtual class IPersonaPreviewScene& GetAnimPreviewScene() const override;`
- L57 _public prototype_ `virtual void GetOnScreenDebugInfo(TArray<FText>& OutDebugInfo) const override;`
- L61 _public prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;` — FEdMode interface
- L62 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L63 _public prototype_ `virtual void DrawHUD(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View, FCanvas* Canvas) override;`
- L64 _public function_ `virtual bool IsCompatibleWith(FEditorModeID OtherModeID) const override`
- L65 _public prototype_ `virtual bool AllowWidgetMove() override;`
- L66 _public prototype_ `virtual bool ShouldDrawWidget() const override;`
- L67 _public prototype_ `virtual bool UsesTransformWidget() const override;`
- L68 _public prototype_ `virtual bool UsesTransformWidget(UE::Widget::EWidgetMode CheckMode) const override;`
- L69 _public prototype_ `virtual FVector GetWidgetLocation() const override;`
- L70 _public prototype_ `virtual bool HandleClick(FEditorViewportClient* InViewportClient, HHitProxy* HitProxy, const FViewportClick& Click) override;`
- L71 _public prototype_ `virtual bool StartTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;`
- L72 _public prototype_ `virtual bool EndTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;`
- L73 _public prototype_ `virtual bool BeginTransform(const FGizmoState& InState) override;`
- L74 _public prototype_ `virtual bool EndTransform(const FGizmoState& InState) override;`
- L75 _public prototype_ `virtual bool InputDelta(FEditorViewportClient* InViewportClient, FViewport* InViewport, FVector& InDrag, FRotator& InRot, FVector& InScale) override;`
- L76 _public prototype_ `virtual bool GetCustomDrawingCoordinateSystem(FMatrix& InMatrix, void* InData) override;`
- L77 _public prototype_ `virtual bool GetCustomInputCoordinateSystem(FMatrix& InMatrix, void* InData) override;`
- L78 _public prototype_ `virtual void Enter() override;`
- L79 _public prototype_ `virtual void Exit() override;`
- L85 _private prototype_ `void GetEditedComponentScaleAndOffset(float& OutScale, FVector& OutOffset) const;` — get the scale and offset associated with the currently edited skeletal mesh component
- L87 _private member_ `UE::Widget::EWidgetMode CurrentWidgetMode;`
- L89 _private prototype_ `bool IsRootSelected() const;`
- L90 _private prototype_ `bool IsOnlyRootSelected() const;`
- L91 _private prototype_ `void UpdateWidgetTransform();`
- L93 _private prototype_ `bool HandleBeginTransform(const FEditorViewportClient* InViewportClient);`
- L94 _private prototype_ `bool HandleEndTransform(FEditorViewportClient* InViewportClient);`
- L97 _private member_ `FBoneEdit BoneEdit;` — the bone(s) currently being edited
- L100 _private member_ `ERetargetSourceOrTarget SourceOrTarget;` — the skeleton currently being edited
- L103 _private member_ `TWeakPtr<FIKRetargetEditorController> EditorController;` — The hosting app
- L106 _private member_ `FIKRetargetTrackingState TrackingState;` — viewport selection/editing state

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/IKRetargetEditor.h` (Public)


#### class `FIKRetargetEditor`  
`class FIKRetargetEditor : public FPersonaAssetEditorToolkit, public IHasPersonaToolkit, public FTickableEditorObject`  
_L29-95_
- inherits: `FPersonaAssetEditorToolkit,IHasPersonaToolkit,FTickableEditorObject`
- L36 _public prototype_ `FIKRetargetEditor();`
- L37 _public prototype_ `virtual ~FIKRetargetEditor() override = default;`
- L39 _public prototype_ `void InitAssetEditor( const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UIKRetargeter* Asset);`
- L45 _public prototype_ `virtual void OnClose() override;` — FAssetEditorToolkit interface
- L46 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;`
- L47 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;`
- L48 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L49 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L50 _public prototype_ `virtual FText GetToolkitName() const override;`
- L51 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L52 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L56 _public prototype_ `virtual void Tick(float DeltaTime) override;` — /  FTickableEditorObject Interface
- L57 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L58 _public prototype_ `virtual TStatId GetStatId() const override;`
- L62 _public function_ `virtual TSharedRef<IPersonaToolkit> GetPersonaToolkit() const override` — IHasPersonaToolkit interface
- L65 _public function_ `TSharedRef<FIKRetargetEditorController> GetController() const`
- L67 _public prototype_ `void SetupAnimInstance();`
- L72 _private prototype_ `void BindCommands();` — toolbar
- L73 _private prototype_ `void ExtendToolbar();`
- L74 _private prototype_ `void FillToolbar(FToolBarBuilder& ToolbarBuilder);`
- L78 _private prototype_ `void HandleViewportCreated(const TSharedRef<class IPersonaViewport>& InViewport);` — preview scene setup
- L79 _private prototype_ `void HandlePreviewSceneCreated(const TSharedRef<IPersonaPreviewScene>& InPersonaPreviewScene);`
- L80 _private prototype_ `void HandleDetailsCreated(const TSharedRef<class IDetailsView>& InDetailsView);`
- L81 _private prototype_ `void OnFinishedChangingDetails(const FPropertyChangedEvent& PropertyChangedEvent);`
- L82 _private prototype_ `void HandleOnPreviewSceneSettingsCustomized(IDetailLayoutBuilder& DetailBuilder) const;`
- L86 _private member_ `TSharedRef<FIKRetargetEditorController> EditorController;` — centralized management across all views
- L89 _private member_ `TSharedPtr<IPersonaToolkit> PersonaToolkit;` — Preview scene to be supplied by IHasPersonaToolkit::GetPersonaToolkit
- L92 _private member_ `float PreviousTime;` — record previous playback time of source anim instance to trigger reset when scrubbing / looping

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace IKRetargetApplicationModes`
- L26 _externvar_ `extern const FName IKRetargetApplicationMode;` (scope `IKRetargetApplicationModes`)

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/IKRetargetEditorController.h` (Public)


#### enum `ERetargeterOutputMode`  
`enum class ERetargeterOutputMode : uint8`  
_L36-40_
- desc: retarget editor modes
- L38 _public enumerator_ `RunRetarget` — output the retargeted target pose
- L39 _public enumerator_ `EditRetargetPose` — allow editing the retarget pose

#### enum `ESelectionEdit`  
`enum class ESelectionEdit : uint8`  
_L42-47_
- L44 _public enumerator_ `Add` — add to selection set
- L45 _public enumerator_ `Remove` — remove from selection
- L46 _public enumerator_ `Replace` — replace selection entirely

#### struct `FBoundIKRig`  
`struct FBoundIKRig`  
_L49-59_
- L51 _public prototype_ `FBoundIKRig(UIKRigDefinition* InIKRig, const FIKRetargetEditorController& InController);`
- L52 _public prototype_ `void UnBind() const;`
- L54 _public member_ `TWeakObjectPtr<UIKRigDefinition> IKRig;`
- L55 _public member_ `FDelegateHandle ReInitIKDelegateHandle;`
- L56 _public member_ `FDelegateHandle AddedChainDelegateHandle;`
- L57 _public member_ `FDelegateHandle RenameChainDelegateHandle;`
- L58 _public member_ `FDelegateHandle RemoveChainDelegateHandle;`

#### struct `FRetargetPlaybackManager`  
`struct FRetargetPlaybackManager : public TSharedFromThis<FRetargetPlaybackManager>`  
_L61-76_
- inherits: `TSharedFromThis<FRetargetPlaybackManager>`
- L63 _public prototype_ `FRetargetPlaybackManager(const TWeakPtr<FIKRetargetEditorController>& InEditorController);`
- L64 _public prototype_ `void PlayAnimationAsset(UAnimationAsset* AssetToPlay);`
- L65 _public prototype_ `void StopPlayback();`
- L66 _public prototype_ `void PausePlayback();`
- L67 _public prototype_ `void ResumePlayback() const;`
- L68 _public prototype_ `bool IsStopped() const;`
- L72 _private member_ `TWeakPtr<FIKRetargetEditorController> EditorController;`
- L73 _private member_ `UAnimationAsset* AnimThatWasPlaying = nullptr;`
- L74 _private member_ `float TimeWhenPaused = 0.0f;`
- L75 _private member_ `bool bWasPlayingAnim = false;`

#### class `FIKRetargetEditorController`  
`class FIKRetargetEditorController : public TSharedFromThis<FIKRetargetEditorController>, public FSelfRegisteringEditorUndoClient, FGCObject`  
_L79-376_
- inherits: `TSharedFromThis<FIKRetargetEditorController>,FSelfRegisteringEditorUndoClient,FGCObject`
- desc: a home for cross-widget communication to synchronize state across all tabs and viewport
- L86 _public prototype_ `virtual ~FIKRetargetEditorController() override = default;`
- L89 _public prototype_ `void Initialize(TSharedPtr<FIKRetargetEditor> InEditor, UIKRetargeter* InAsset);` — Initialize the editor
- L91 _public prototype_ `void Close();` — Close the editor
- L94 _public prototype_ `virtual void PostUndo( bool bSuccess );` — FSelfRegisteringEditorUndoClient interface
- L95 _public prototype_ `virtual void PostRedo(bool bSuccess);`
- L96 _public prototype_ `virtual bool MatchesContext( const FTransactionContext& InContext, const TArray<TPair<UObject*, FTransactionObjectEvent>>& TransactionObjectContexts ) const;`
- L100 _public prototype_ `void BindToIKRigAssets();` — Bind callbacks to this IK Rig
- L102 _public prototype_ `void HandleIKRigNeedsInitialized(UIKRigDefinition* ModifiedIKRig) const;` — callback when IK Rig asset requires reinitialization
- L104 _public prototype_ `void HandleRetargetChainAdded(UIKRigDefinition* ModifiedIKRig) const;` — callback when IK Rig asset's retarget chain's have been added or removed
- L106 _public prototype_ `void HandleRetargetChainRenamed(UIKRigDefinition* ModifiedIKRig, FName OldName, FName NewName) const;` — callback when IK Rig asset's retarget chain has been renamed
- L108 _public prototype_ `void HandleRetargetChainRemoved(UIKRigDefinition* ModifiedIKRig, const FName InChainRemoved) const;` — callback when IK Rig asset's retarget chain has been removed
- L110 _public prototype_ `void HandleRetargeterNeedsInitialized() const;` — callback when IK Retargeter asset requires reinitialization
- L112 _public prototype_ `void ReinitializeRetargeterNoUIRefresh() const;` — reinitialize retargeter without refreshing UI
- L114 _public member_ `FDelegateHandle RetargeterReInitDelegateHandle;` — delegate handles to un-bind
- L115 _public member_ `FDelegateHandle OpStackModifiedDelegateHandle;`
- L116 _public member_ `FDelegateHandle OverrideSetsModifiedDelegateHandle;`
- L117 _public member_ `FDelegateHandle VariablesModifiedDelegateHandle;`
- L119 _public prototype_ `void HandleIKRigReplaced(ERetargetSourceOrTarget SourceOrTarget);` — callback when IK Rig asset has been swapped out
- L120 _public member_ `FDelegateHandle IKRigReplacedDelegateHandle;`
- L122 _public prototype_ `void HandlePreviewMeshReplaced(ERetargetSourceOrTarget SourceOrTarget);` — callback when Preview Mesh asset has been swapped out
- L123 _public member_ `FDelegateHandle PreviewMeshReplacedDelegateHandle;`
- L124 _public member_ `FDelegateHandle RetargeterInitializedDelegateHandle;`
- L127 _public member_ `TObjectPtr<UIKRetargeterController> AssetController;` — all modifications to the data model should go through this controller
- L130 _public member_ `TWeakPtr<FIKRetargetEditor> Editor;` — the persona toolkit
- L133 _public member_ `TSharedPtr<FIKRetargetPoseExporter> PoseExporter;` — import / export retarget poses
- L136 _public member_ `TUniquePtr<FRetargetPlaybackManager> PlaybackManager;` — manage playback of animation in the editor
- L139 _public prototype_ `UDebugSkelMeshComponent* GetSkeletalMeshComponent(const ERetargetSourceOrTarget SourceOrTarget) const;` — viewport skeletal mesh
- L140 _public member_ `UDebugSkelMeshComponent* SourceSkelMeshComponent;`
- L141 _public member_ `UDebugSkelMeshComponent* TargetSkelMeshComponent;`
- L144 _public member_ `USceneComponent* SourceRootComponent;` — this root component is used as a parent of the source skeletal mesh to allow us to translate the source. we can't offset the source mesh component itself because that conflicts with root motion
- L147 _public prototype_ `UIKRetargetAnimInstance* GetAnimInstance(const ERetargetSourceOrTarget SourceOrTarget) const;` — viewport anim instance
- L149 _public member_ `TObjectPtr<UIKRetargetAnimInstance> SourceAnimInstance;` — `UPROPERTY(transient, NonTransactional)`
- L151 _public member_ `TObjectPtr<UIKRetargetAnimInstance> TargetAnimInstance;` — `UPROPERTY(transient, NonTransactional)`
- L155 _public function_ `void SetDetailsView(const TSharedPtr<IDetailsView>& InDetailsView)` — store pointers to various tabs of UI, have to manage access to these because they can be null if the tabs are closed
- L156 _public function_ `void SetAssetBrowserView(const TSharedPtr<SIKRetargetAssetBrowser>& InAssetBrowserView)`
- L157 _public function_ `void SetOutputLogView(const TSharedPtr<SIKRigOutputLog>& InOutputLogView)`
- L158 _public function_ `void SetHierarchyView(const TSharedPtr<SIKRetargetHierarchy>& InHierarchyView)`
- L159 _public function_ `void SetOpStackView(const TSharedPtr<SRetargetOpStack>& InOpStackView)`
- L160 _public function_ `void SetOverrideSetsView(const TSharedPtr<SIKRetargetOverrideManager>& InOverrideSetView)`
- L161 _public function_ `void SetVariablesView(const TSharedPtr<SIKRetargetVariablesEditor>& InVariablesView)`
- L162 _public prototype_ `bool IsObjectInDetailsView(const UObject* Object);`
- L165 _public prototype_ `void RefreshAllViews() const;` — force refresh all views in the editor
- L166 _public prototype_ `void RefreshDetailsView() const;`
- L167 _public prototype_ `void RefreshAssetBrowserView() const;`
- L168 _public prototype_ `void RefreshHierarchyView() const;`
- L169 _public prototype_ `void RefreshOpStackView() const;`
- L170 _public prototype_ `void RefreshOverrideSetView() const;`
- L171 _public prototype_ `void RefreshVariablesView() const;`
- L172 _public prototype_ `void RefreshPoseList() const;`
- L173 _public prototype_ `void SetDetailsObject(UObject* DetailsObject) const;`
- L174 _public prototype_ `void SetDetailsObjects(const TArray<UObject*>& DetailsObjects) const;`
- L175 _public prototype_ `void ShowDetailsForOp(const int32 OpIndex) const;`
- L178 _public prototype_ `bool IsReadyToRetarget() const;` — retargeter state
- L179 _public prototype_ `bool IsCurrentMeshLoaded() const;`
- L180 _public prototype_ `bool IsEditingPose() const;`
- L183 _public prototype_ `void ClearOutputLog() const;` — clear the output log
- L186 _public prototype_ `USkeletalMesh* GetSkeletalMesh(const ERetargetSourceOrTarget SourceOrTarget) const;` — get the USkeletalMesh we are transferring animation between (either source or target)
- L188 _public prototype_ `const USkeleton* GetSkeleton(const ERetargetSourceOrTarget SourceOrTarget) const;` — get the USkeleton we are transferring animation between (either source or target)
- L190 _public prototype_ `UDebugSkelMeshComponent* GetEditedSkeletalMesh() const;` — get currently edited debug skeletal mesh
- L192 _public prototype_ `const FRetargetSkeleton& GetCurrentlyEditedSkeleton(const FIKRetargetProcessor& Processor) const;` — get the currently edited retarget skeleton
- L195 _public prototype_ `FTransform GetGlobalRetargetPoseOfBone( const ERetargetSourceOrTarget SourceOrTarget, const int32& BoneIndex, const float& Scale, const FVector& Offset) const;` — get world space pose of a bone (with component scale / offset applied)
- L202 _public prototype_ `static void GetGlobalRetargetPoseOfImmediateChildren( const FRetargetSkeleton& RetargetSkeleton, const int32& BoneIndex, const float& Scale, const FVector& Offset, TArray<int32>& OutChildrenIndices, TArray<FVector>& OutChildrenPositions);` — get world space positions of all immediate children of bone (with component scale / offset applied)
- L211 _public prototype_ `FIKRetargetProcessor* GetRetargetProcessor() const;` — get the retargeter that is running in the viewport (which is a duplicate of the source asset)
- L213 _public prototype_ `void OnPlaybackReset() const;` — Reset the planting state of the IK (when scrubbing or animation loops over)
- L216 _public prototype_ `void SetRetargeterMode(ERetargeterOutputMode Mode);` — Set viewport / editor tool mode
- L217 _public function_ `void SetRetargetModeToPreviousMode()`
- L218 _public function_ `ERetargeterOutputMode GetRetargeterMode() const`
- L219 _public prototype_ `FText GetRetargeterModeLabel();`
- L220 _public prototype_ `FSlateIcon GetCurrentRetargetModeIcon() const;`
- L221 _public prototype_ `FSlateIcon GetRetargeterModeIcon(ERetargeterOutputMode Mode) const;`
- L222 _public prototype_ `float GetRetargetPoseAmount() const;`
- L223 _public prototype_ `void SetRetargetPoseAmount(float InValue);`
- L227 _public function_ `ERetargetSourceOrTarget GetSourceOrTarget() const` — general editor mode can be either viewing/editing source or target
- L228 _public prototype_ `void SetSourceOrTargetMode(ERetargetSourceOrTarget SourceOrTarget);`
- L235 _public function_ `const FIKRetargetDebugDrawState& GetSelectionState() const` — GENERAL SELECTION access to all selection state for the editor
- L236 _public prototype_ `void CleanSelection(ERetargetSourceOrTarget SourceOrTarget);`
- L237 _public prototype_ `void ClearSelection(const bool bKeepBoneSelection=false);`
- L239 _public prototype_ `bool GetCameraTargetForSelection(FSphere& OutTarget) const;` — to frame selection when pressing "f" in viewport
- L242 _public prototype_ `void EditBoneSelection( const TArray<FName>& InBoneNames, ESelectionEdit EditMode, const bool bFromHierarchyView = false);` — SELECTION - BONES (viewport or hierarchy view)
- L246 _public function_ `const TArray<FName>& GetSelectedBones() const`
- L247 _public prototype_ `void SetRootSelected(const bool bIsSelected);`
- L248 _public function_ `bool GetRootSelected() const`
- L249 _public prototype_ `bool IsEditingPoseWithAnyBoneSelected() const;`
- L250 _public prototype_ `TArray<FName> GetSelectedBonesAndChildren() const;`
- L254 _public prototype_ `void EditChainSelection( const TArray<FName>& InChainNames, ESelectionEdit EditMode, const bool bFromChainsView);` — SELECTION - CHAINS (viewport or chains view)
- L258 _public function_ `const TArray<FName>& GetSelectedChains() const`
- L262 _public prototype_ `void SetOpSelected(const int32 InOpIndex);` — SELECTION - OP STACK
- L263 _public prototype_ `FName GetSelectedOpName() const;`
- L264 _public prototype_ `FIKRetargetOpBase* GetSelectedOp() const;`
- L265 _public prototype_ `int32 GetSelectedOpIndex() const;`
- L269 _public prototype_ `FName GetSelectedOverrideSet() const;` — SELECTION - OVERRIDE SETS
- L275 _public prototype_ `bool IsBoneRetargeted(const FName& BoneName, ERetargetSourceOrTarget SourceOrTarget) const;` — determine if bone in the specified skeleton is part of the retarget (in a mapped chain)
- L277 _public prototype_ `FName GetChainDisplayNameForBone(const FName& BoneName, ERetargetSourceOrTarget SourceOrTarget) const;` — get the name of the chain that contains this bone
- L280 _public prototype_ `TObjectPtr<UIKRetargetBoneDetails> GetOrCreateBoneDetailsObject(const FName& BoneName);` — factory to get/create bone details UObject
- L285 _public member_ `TArray<TSharedPtr<FName>> PoseNames;` — toggle current retarget pose
- L286 _public prototype_ `FText GetCurrentPoseName() const;`
- L287 _public prototype_ `void OnPoseSelected(TSharedPtr<FName> InPoseName, ESelectInfo::Type SelectInfo) const;`
- L290 _public prototype_ `void HandleResetAllBones() const;` — reset retarget pose
- L291 _public prototype_ `void HandleResetSelectedBones() const;`
- L292 _public prototype_ `void HandleResetSelectedAndChildrenBones() const;`
- L295 _public prototype_ `void HandleAlignBones(const bool bIncludeChildren, const bool bIncludeAllBones) const;` — auto generate retarget pose
- L296 _public prototype_ `void HandleSnapToGround() const;`
- L297 _public member_ `ERetargetAutoAlignMethod CurrentPoseAlignmentMode;`
- L300 _public prototype_ `void HandleNewPose();` — create new retarget pose
- L301 _public prototype_ `bool CanCreatePose() const;`
- L302 _public prototype_ `FReply CreateNewPose() const;`
- L303 _public member_ `TSharedPtr<SWindow> NewPoseWindow;`
- L304 _public member_ `TSharedPtr<SEditableTextBox> NewPoseEditableText;`
- L307 _public prototype_ `void HandleDuplicatePose();` — duplicate current retarget pose
- L308 _public prototype_ `FReply CreateDuplicatePose() const;`
- L311 _public prototype_ `void HandleDeletePose();` — delete retarget pose
- L312 _public prototype_ `bool CanDeletePose() const;`
- L315 _public prototype_ `void HandleRenamePose();` — rename retarget pose
- L316 _public prototype_ `FReply RenamePose() const;`
- L317 _public prototype_ `bool CanRenamePose() const;`
- L318 _public member_ `TSharedPtr<SWindow> RenamePoseWindow;`
- L319 _public member_ `TSharedPtr<SEditableTextBox> NewNameEditableText;`
- L322 _public prototype_ `void FixZeroHeightRetargetRoot(ERetargetSourceOrTarget SourceOrTarget) const;` — detect and auto-fix retarget pose that causes root height to be on the ground
- L327 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L328 _public function_ `virtual FString GetReferencerName() const override`
- L332 _public prototype_ `void RenderSkeleton(FPrimitiveDrawInterface* PDI, ERetargetSourceOrTarget SourceOrTarget) const;` — render the skeleton's in the viewport (either source or target)
- L334 _public prototype_ `void UpdateSkeletalMeshComponents() const;`
- L339 _private prototype_ `bool PromptToFixPelvisHeight(ERetargetSourceOrTarget SourceOrTarget) const;` — modal dialog to ask user if they want to fix root bones that are "on the ground"
- L340 _private member_ `bool bAskedToFixRoot = false;`
- L343 _private member_ `TSharedPtr<IDetailsView> DetailsView;` — asset properties tab
- L345 _private member_ `TSharedPtr<SIKRetargetAssetBrowser> AssetBrowserView;` — asset browser view
- L347 _private member_ `TSharedPtr<SIKRigOutputLog> OutputLogView;` — output log view
- L349 _private member_ `TSharedPtr<SIKRetargetHierarchy> HierarchyView;` — hierarchy view
- L351 _private member_ `TSharedPtr<SRetargetOpStack> OpStackView;` — op stack widget
- L353 _private member_ `TSharedPtr<SIKRetargetOverrideManager> OverrideSetView;` — overrides widget
- L355 _private member_ `TSharedPtr<SIKRetargetVariablesEditor> VariablesView;` — variables widget
- L358 _private member_ `TSharedPtr<SWindow> IKRigPickerWindow;` — when prompting user to assign an IK Rig
- L361 _private member_ `ERetargeterOutputMode OutputMode = ERetargeterOutputMode::RunRetarget;` — the current output mode of the retargeter
- L362 _private member_ `ERetargeterOutputMode PreviousMode;`
- L364 _private member_ `float RetargetPosePreviewBlend = 1.0f;` — slider value to blend between reference pose and retarget pose
- L367 _private member_ `ERetargetSourceOrTarget CurrentlyEditingSourceOrTarget = ERetargetSourceOrTarget::Target;` — which skeleton are we editing / viewing?
- L370 _private member_ `FIKRetargetDebugDrawState Selection;` — current selection set
- L372 _private member_ `TMap<FName,TObjectPtr<UIKRetargetBoneDetails>> AllBoneDetails;` — `UPROPERTY()`
- L375 _private member_ `TArray<FBoundIKRig> BoundIKRigs;` — ik rigs bound to this editor (will receive callbacks when requiring reinitialization

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/IKRetargetEditorStyle.h` (Public)


#### class `FIKRetargetEditorStyle`  
`class FIKRetargetEditorStyle final : public FSlateStyleSet`  
_L11-65_
- inherits: `FSlateStyleSet`
- L15 _public function_ `FIKRetargetEditorStyle() : FSlateStyleSet("IKRetargetEditorStyle")`
- L55 _public function_ `static FIKRetargetEditorStyle& Get()`
- L61 _public function_ `~FIKRetargetEditorStyle()`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/IKRetargetFactory.h` (Public)


#### class `UIKRetargetFactory`  
`class UIKRetargetFactory : public UFactory`  
_L15-33_
- reflection: `UCLASS(MinimalAPI, hidecategories=Object)`
- inherits: `UFactory`
- L20 _private member_ `TWeakObjectPtr<class UIKRigDefinition> SourceIKRig;` — `UPROPERTY()`
- L24 _public prototype_ `UIKRetargetFactory();`
- L27 _public prototype_ `virtual FText GetDisplayName() const override;` — UFactory Interface
- L28 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L29 _public prototype_ `virtual FText GetToolTip() const override;`
- L30 _public prototype_ `virtual FString GetDefaultNewAssetName() const override;`
- L31 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L32 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API IKRIGEDITOR_API`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/IKRetargetHierarchyTabSummoner.h` (Public)


#### struct `FIKRetargetHierarchyTabSummoner`  
`struct FIKRetargetHierarchyTabSummoner : public FWorkflowTabFactory`  
_L10-21_
- inherits: `FWorkflowTabFactory`
- L13 _public member_ `static const FName TabID;`
- L15 _public prototype_ `FIKRetargetHierarchyTabSummoner(const TSharedRef<FIKRetargetEditor>& InIKRigEditor);`
- L16 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L17 _public prototype_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override;`
- L20 _protected member_ `TWeakPtr<FIKRetargetEditor> RetargetEditor;`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/IKRetargetHitProxies.h` (Public)


#### struct `HIKRetargetEditorBoneProxy`  
`struct HIKRetargetEditorBoneProxy : public HHitProxy`  
_L10-36_
- inherits: `HHitProxy`
- desc: allow bone selection to edit retarget pose
- L12 _public prototype_ `DECLARE_HIT_PROXY();`
- L14 _public member_ `FName BoneName;`
- L15 _public member_ `int32 BoneIndex;`
- L16 _public member_ `ERetargetSourceOrTarget SourceOrTarget;`
- L18 _public function_ `HIKRetargetEditorBoneProxy( const FName& InBoneName, const int32 InBoneIndex, ERetargetSourceOrTarget InSourceOrTarget) : HHitProxy(HPP_World), BoneName(InBoneName), BoneIndex(InBoneIndex), SourceOrTarget(InSourceOrTarget)`
- L27 _public function_ `virtual EMouseCursor::Type GetMouseCursor()`
- L32 _public function_ `virtual bool AlwaysAllowsTranslucentPrimitives() const override`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/IKRetargetOpDetails.h` (Public)


#### class `FIKRetargetOpBaseSettingsCustomization`  
`class FIKRetargetOpBaseSettingsCustomization : public IPropertyTypeCustomization`  
_L26-102_
- inherits: `IPropertyTypeCustomization`
- L31 _public function_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InStructCustomizationUtils) override` — IPropertyTypeCustomization
- L37 _public prototype_ `bool LoadAndValidateStructToCustomize( const TSharedRef<IPropertyHandle>& InStructPropertyHandle, const IPropertyTypeCustomizationUtils& InStructCustomizationUtils);`
- L41 _public prototype_ `static void AddPropertyToGroup( const TSharedRef<IPropertyHandle>& InPropertyHandle, IDetailChildrenBuilder& ChildBuilder);`
- L45 _public prototype_ `static void AddChildPropertiesToCategoryGroups( const TSharedRef<IPropertyHandle>& InParentPropertyHandle, IDetailChildrenBuilder& ChildBuilder);`
- L49 _public prototype_ `static void AddChildPropertiesInCategory( const TSharedRef<IPropertyHandle>& InParentPropertyHandle, IDetailChildrenBuilder& InChildBuilder, const FName& InCategoryName, const TArray<FName>& InPropertiesToIgnore = {});`
- L55 _public prototype_ `static void AddBaseOpProperties( TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& ChildBuilder);`
- L61 _protected typedef_ `using FChainSettingsGetter = TFunction<UObject*(const FName)>;`
- L64 _protected function_ `template<typename TSettings, typename TWrapper> FChainSettingsGetter TMakeChainSettingsGetter( const FName InOpName, const FName SettingsMemberPropertyName, const TArray<FName>& HiddenProps = {})`
- L97 _protected member_ `FName OpName;` — the op that owns the settings being customized / edited
- L98 _protected member_ `TArray<TWeakObjectPtr<UObject>> SelectedObjects;`
- L99 _protected member_ `UIKRigStructViewer* StructViewer;`
- L100 _protected member_ `UIKRetargeter* RetargetAsset;`
- L101 _protected member_ `UIKRetargeterController* AssetController;`

#### class `FChainsFKOpCustomization`  
`class FChainsFKOpCustomization : public FIKRetargetOpBaseSettingsCustomization`  
_L108-122_
- inherits: `FIKRetargetOpBaseSettingsCustomization`
- L111 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L117 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization

#### class `URetargetFKChainSettingsWrapper`  
`class URetargetFKChainSettingsWrapper : public UIKRigStructWrapperBase`  
_L125-131_
- reflection: `UCLASS()`
- inherits: `UIKRigStructWrapperBase`
- L130 _public member_ `FRetargetFKChainSettings Settings;` — `UPROPERTY(EditAnywhere, Category = "FK Chain Settings")`

#### class `FRunIKRigOpCustomization`  
`class FRunIKRigOpCustomization : public FIKRetargetOpBaseSettingsCustomization`  
_L137-151_
- inherits: `FIKRetargetOpBaseSettingsCustomization`
- L140 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L146 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization

#### class `URunIKRigSettingsWrapper`  
`class URunIKRigSettingsWrapper : public UIKRigStructWrapperBase`  
_L154-160_
- reflection: `UCLASS()`
- inherits: `UIKRigStructWrapperBase`
- L159 _public member_ `FIKRetargetRunIKRigChainSettings Settings;` — `UPROPERTY(EditAnywhere, Category = "IK Chain Settings")`

#### class `FIKChainOpCustomization`  
`class FIKChainOpCustomization : public FIKRetargetOpBaseSettingsCustomization`  
_L166-180_
- inherits: `FIKRetargetOpBaseSettingsCustomization`
- L169 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L175 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization

#### class `URetargetIKChainSettingsWrapper`  
`class URetargetIKChainSettingsWrapper : public UIKRigStructWrapperBase`  
_L183-189_
- reflection: `UCLASS()`
- inherits: `UIKRigStructWrapperBase`
- L188 _public member_ `FRetargetIKChainSettings Settings;` — `UPROPERTY(EditAnywhere, Category = "IK Chain Settings")`

#### class `FStrideWarpOpCustomization`  
`class FStrideWarpOpCustomization : public FIKRetargetOpBaseSettingsCustomization`  
_L195-209_
- inherits: `FIKRetargetOpBaseSettingsCustomization`
- L198 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L204 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization

#### class `URetargetStrideWarpSettingsWrapper`  
`class URetargetStrideWarpSettingsWrapper : public UIKRigStructWrapperBase`  
_L212-218_
- reflection: `UCLASS()`
- inherits: `UIKRigStructWrapperBase`
- L217 _public member_ `FRetargetStrideWarpChainSettings Settings;` — `UPROPERTY(EditAnywhere, Category = "Stride Warp Settings")`

#### class `FSpeedPlantOpCustomization`  
`class FSpeedPlantOpCustomization : public FIKRetargetOpBaseSettingsCustomization`  
_L224-238_
- inherits: `FIKRetargetOpBaseSettingsCustomization`
- L227 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L233 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization

#### class `URetargetSpeedPlantSettingsWrapper`  
`class URetargetSpeedPlantSettingsWrapper : public UIKRigStructWrapperBase`  
_L241-247_
- reflection: `UCLASS()`
- inherits: `UIKRigStructWrapperBase`
- L246 _public member_ `FRetargetSpeedPlantingSettings Settings;` — `UPROPERTY(EditAnywhere, Category = "Stride Warp Settings")`

#### class `FPoleVectorOpCustomization`  
`class FPoleVectorOpCustomization : public FIKRetargetOpBaseSettingsCustomization`  
_L253-267_
- inherits: `FIKRetargetOpBaseSettingsCustomization`
- L256 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L262 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization

#### class `UPoleVectorSettingsWrapper`  
`class UPoleVectorSettingsWrapper : public UIKRigStructWrapperBase`  
_L270-276_
- reflection: `UCLASS()`
- inherits: `UIKRigStructWrapperBase`
- L275 _public member_ `FRetargetPoleVectorSettings Settings;` — `UPROPERTY(EditAnywhere, Category = "Pole Vector Settings")`

#### class `FAdditivePoseOpCustomization`  
`class FAdditivePoseOpCustomization : public FIKRetargetOpBaseSettingsCustomization`  
_L282-305_
- inherits: `FIKRetargetOpBaseSettingsCustomization`
- L285 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L291 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization
- L299 _private prototype_ `void UpdatePoseNameOptions();`
- L301 _private member_ `TSharedPtr<IPropertyHandle> PoseToApplyProperty;`
- L303 _private member_ `TSharedPtr<FName> CurrentPoseOption;`
- L304 _private member_ `TArray<TSharedPtr<FName>> PoseNameOptions;`

#### class `URetargetPoseOpSettingsWrapper`  
`class URetargetPoseOpSettingsWrapper : public UIKRigStructWrapperBase`  
_L308-314_
- reflection: `UCLASS()`
- inherits: `UIKRigStructWrapperBase`
- L313 _public member_ `FIKRetargetAdditivePoseOpSettings Settings;` — `UPROPERTY(EditAnywhere, Category = "Retarget Pose Settings")`

#### class `FStretchChainOpCustomization`  
`class FStretchChainOpCustomization : public FIKRetargetOpBaseSettingsCustomization`  
_L320-334_
- inherits: `FIKRetargetOpBaseSettingsCustomization`
- L323 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L329 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization

#### class `UStretchChainSettingsWrapper`  
`class UStretchChainSettingsWrapper : public UIKRigStructWrapperBase`  
_L337-343_
- reflection: `UCLASS()`
- inherits: `UIKRigStructWrapperBase`
- L342 _public member_ `FRetargetStretchChainSettings Settings;` — `UPROPERTY(EditAnywhere, Category = "Stretch Chain Settings")`

#### class `FFloorConstraintOpCustomization`  
`class FFloorConstraintOpCustomization : public FIKRetargetOpBaseSettingsCustomization`  
_L349-363_
- inherits: `FIKRetargetOpBaseSettingsCustomization`
- L352 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L358 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization

#### class `UFloorConstraintSettingsWrapper`  
`class UFloorConstraintSettingsWrapper : public UIKRigStructWrapperBase`  
_L366-372_
- reflection: `UCLASS()`
- inherits: `UIKRigStructWrapperBase`
- L371 _public member_ `FFloorConstraintChainSettings Settings;` — `UPROPERTY(EditAnywhere, Category = "Floor Constraint Chain Settings")`

#### class `FBlendToSourceOpCustomization`  
`class FBlendToSourceOpCustomization : public FIKRetargetOpBaseSettingsCustomization`  
_L378-392_
- inherits: `FIKRetargetOpBaseSettingsCustomization`
- L381 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L387 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization

#### class `UBlendToSourceSettingsWrapper`  
`class UBlendToSourceSettingsWrapper : public UIKRigStructWrapperBase`  
_L395-401_
- reflection: `UCLASS()`
- inherits: `UIKRigStructWrapperBase`
- L400 _public member_ `FIKRetargetBlendToSourceChainSettings Settings;` — `UPROPERTY(EditAnywhere, Category = "Blend to Source Chain Settings")`

#### class `FOffsetGoalsOpCustomization`  
`class FOffsetGoalsOpCustomization : public FIKRetargetOpBaseSettingsCustomization`  
_L407-421_
- inherits: `FIKRetargetOpBaseSettingsCustomization`
- L410 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L416 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization

#### class `UOffsetGoalsSettingsWrapper`  
`class UOffsetGoalsSettingsWrapper : public UIKRigStructWrapperBase`  
_L424-430_
- reflection: `UCLASS()`
- inherits: `UIKRigStructWrapperBase`
- L429 _public member_ `FIKRetargetOffsetGoalsChainSettings Settings;` — `UPROPERTY(EditAnywhere, Category = "Offset Goals Chain Settings")`

#### class `FScaleGoalsOpCustomization`  
`class FScaleGoalsOpCustomization : public FIKRetargetOpBaseSettingsCustomization`  
_L436-450_
- inherits: `FIKRetargetOpBaseSettingsCustomization`
- L439 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L445 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization

#### class `UScaleGoalsSettingsWrapper`  
`class UScaleGoalsSettingsWrapper : public UIKRigStructWrapperBase`  
_L453-459_
- reflection: `UCLASS()`
- inherits: `UIKRigStructWrapperBase`
- L458 _public member_ `FIKRetargetScaleGoalsChainSettings Settings;` — `UPROPERTY(EditAnywhere, Category = "Scale Goals Chain Settings")`

#### Free symbols / members of external scopes

- L74 _function_ `` (scope `FIKRetargetOpBaseSettingsCustomization::TMakeChainSettingsGetter`)
- L80 _function_ `` (scope `FIKRetargetOpBaseSettingsCustomization::TMakeChainSettingsGetter::__anon6ee50f760102`)

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/IKRetargetOpStackTabSummoner.h` (Public)


#### struct `FIKRetargetOpStackTabSummoner`  
`struct FIKRetargetOpStackTabSummoner : public FWorkflowTabFactory`  
_L10-21_
- inherits: `FWorkflowTabFactory`
- L13 _public member_ `static const FName TabID;`
- L15 _public prototype_ `FIKRetargetOpStackTabSummoner(const TSharedRef<FIKRetargetEditor>& InIKRetargetEditor);`
- L16 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L17 _public prototype_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override;`
- L20 _protected member_ `TWeakPtr<FIKRetargetEditor> RetargetEditor;`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/IKRetargetOutputLogTabSummoner.h` (Public)


#### struct `FIKRetargetOutputLogTabSummoner`  
`struct FIKRetargetOutputLogTabSummoner : public FWorkflowTabFactory`  
_L10-21_
- inherits: `FWorkflowTabFactory`
- L13 _public member_ `static const FName TabID;`
- L15 _public prototype_ `FIKRetargetOutputLogTabSummoner(const TSharedRef<FIKRetargetEditor>& InIKRetargetEditor);`
- L16 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L17 _public prototype_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override;`
- L20 _protected member_ `TWeakPtr<FIKRetargetEditor> IKRetargetEditor;`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/IKRetargetOverrideCustomization.h` (Public)


#### class `FRetargetOverrideCustomization`  
`class FRetargetOverrideCustomization : public IPropertyTypeCustomization`  
_L13-129_
- inherits: `IPropertyTypeCustomization`
- desc: This builds a custom details view for FRetargetOverrideSet types. It supports editing retarget op settings overrides stored within a retarget override set
- L18 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L24 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization interface
- L25 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L30 _private prototype_ `void CustomizeOutsideEditor(TSharedRef<IPropertyHandle> OverrideSetHandle, IDetailChildrenBuilder& ChildBuilder);` — We customize the FRetargetOverrideSet details differently when outside the retarget editor context.
- L34 _private prototype_ `TObjectPtr<UIKRetargeterController> GetAssetController(const IPropertyTypeCustomizationUtils& CustomizationUtils);` — Get the controller for the retarget asset by traversing through the UIKRigStructViewer being customized @return a pointer to the asset controller this set belongs to (or nullptr if outside editor)
- L44 _private prototype_ `void AddRowForPropertyOverride( TSharedPtr<IPropertyHandle> InPropertyHandle, IDetailGroup& InPropertyGroup, const FName& InOverrideSetName, const FName& InOpName, const FString& InPropertyPath);` — Injects a custom row for a property override into a detail group. @param InPropertyHandle  Handle to the property being displayed. @param InPropertyGroup   The detail group where this row will be added. @param InOverrideSetName The name of the current override set. @param InOpName          The name of the retarget op the override belongs to. @param InPropertyPath    The full path to the property within the op's settings.
- L52 _private prototype_ `TSharedRef<SWidget> GetBindingMenuContent( TSharedPtr<IPropertyHandle> InPropertyHandle, FName InOverrideSetName, FName InOpName, FString InPropertyPath);` — Generates the binding dropdown menu content for a specific property override
- L63 _private prototype_ `TMap<FString, TArray<int32>> MapOverridesToGroups(const TSharedPtr<IPropertyHandle>& OpOverridesHandle) const;` — Iterates through the overrides in an override set and groups them by their property path. @param OpOverridesHandle  Handle to the FRetargetOpOverrides struct. @return A map where keys are group names and values are indices into the override array.
- L72 _private prototype_ `TSharedPtr<FStructOnScope>& GetCachedScopedStruct(const FName& InOpName, const UScriptStruct* OpSettingsType);` — Retrieves or creates a cached FStructOnScope for a specific retarget op. Used for temporary value manipulation or default value comparisons. @param InOpName          The name of the operation. @param OpSettingsType    The script struct type to instantiate if not cached. @return A reference to the shared pointer containing the scoped struct.
- L82 _private prototype_ `bool CopyStoredValueToScopedStruct( const TSharedPtr<FStructOnScope>& InScopedStruct, const UScriptStruct* OpSettingsType, const FString& InPropertyPath, const TSharedPtr<IPropertyHandle>& InRawValueHandle);` — Copies a serialized string value from a property handle into the corresponding property of a live struct instance. @param InScopedStruct     The destination struct instance. @param OpSettingsType     The struct type definition. @param InPropertyPath     The path to the property to be updated. @param InRawValueHandle   The handle containing the source serialized value. @return True if the value was successfully resolved and copied.
- L93 _private prototype_ `const UScriptStruct* GetSettingsStruct(TSharedPtr<IPropertyHandle>& OpOverridesHandle) const;` — Resolves the underlying UScriptStruct type for a retarget operation's settings. @param OpOverridesHandle   Handle to the FRetargetOpOverrides. @return The UScriptStruct pointer if found, otherwise nullptr.
- L101 _private prototype_ `TSharedPtr<IPropertyHandle> ResolveHandleFromPath(TSharedPtr<IPropertyHandle> InRootHandle, const FString& InPath);` — Navigates a property handle hierarchy based on a string path. @param InRootHandle      The starting point for the search. @param InPath            The string path (e.g., "Settings->SubStruct->Value"). @return A handle to the leaf property if the path is valid, otherwise null.
- L109 _private prototype_ `void GetOverridePropertyPath( const TSharedPtr<IPropertyHandle>& InOpOverridesHandle, const int32 InOverrideIndex, FString& OutPath) const;` — Extracts the property path string from a specific override entry in the override set. @param InOpOverridesHandle Handle to the parent FRetargetOpOverrides. @param InOverrideIndex   Index of the override in the TArray. @param OutPath           [Out] The resulting property path string.
- L120 _private prototype_ `TSharedPtr<IPropertyHandle> GetOverrideValueHandle( const TSharedPtr<IPropertyHandle>& InOpOverridesHandle, const int32 InOverrideIndex) const;` — Gets the property handle for the 'Value' field of a specific override entry. @param InOpOverridesHandle Handle to the parent FRetargetOpOverrides. @param InOverrideIndex   Index of the override in the TArray. @return The handle to the override's value string.
- L125 _private member_ `TMap<FName, TSharedPtr<FStructOnScope>> ScopedInstances;` — Stores the binary data for temp op settings structs while being edited <OpName, OpSettingsMemory>
- L128 _private member_ `TWeakObjectPtr<UIKRetargeterController> AssetController;` — Stored and referenced by UI callbacks for transactional edits to override sets.

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/IKRetargetOverridesTabSummoner.h` (Public)


#### struct `FIKRetargetOverridesTabSummoner`  
`struct FIKRetargetOverridesTabSummoner : public FWorkflowTabFactory`  
_L11-22_
- inherits: `FWorkflowTabFactory`
- desc: Summons the "Retarget Override Sets" tab in the IK Retarget editor.
- L14 _public member_ `static const FName TabID;`
- L16 _public prototype_ `FIKRetargetOverridesTabSummoner(const TSharedRef<FIKRetargetEditor>& InIKRetargetEditor);`
- L17 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L18 _public prototype_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override;`
- L21 _protected member_ `TWeakPtr<FIKRetargetEditor> IKRetargetEditor;`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/IKRetargetPoseExporter.h` (Public)


#### class `FIKRetargetPoseExporter`  
`class FIKRetargetPoseExporter : public TSharedFromThis<FIKRetargetPoseExporter>`  
_L9-48_
- inherits: `TSharedFromThis<FIKRetargetPoseExporter>`
- L13 _public prototype_ `FIKRetargetPoseExporter() = default;`
- L15 _public prototype_ `void Initialize(TSharedPtr<FIKRetargetEditorController> InController);`
- L18 _public prototype_ `void HandleImportFromPoseAsset();` — import retarget pose from asset
- L19 _public prototype_ `FReply ImportPoseAsset() const;`
- L20 _public prototype_ `bool OnShouldFilterPoseToImport(const struct FAssetData& AssetData) const;`
- L21 _public prototype_ `void OnPoseAssetSelected(const FAssetData& SelectedAsset);`
- L22 _public prototype_ `TSharedRef<SWidget> OnGeneratePoseComboWidget(TSharedPtr<FName> Item) const;`
- L23 _public prototype_ `void OnSelectPoseFromPoseAsset(TSharedPtr<FName> Item, ESelectInfo::Type SelectInfo);`
- L24 _public prototype_ `void RefreshPoseList();`
- L25 _public member_ `FSoftObjectPath RetargetPoseToImport;`
- L26 _public member_ `TSharedPtr<SWindow> ImportPoseWindow;`
- L27 _public member_ `TArray<TSharedPtr<FName>> PosesInSelectedAsset;`
- L28 _public member_ `TSharedPtr<FName> SelectedPose;`
- L31 _public prototype_ `void HandleImportFromSequenceAsset();` — import retarget pose from animation sequence
- L32 _public prototype_ `bool OnShouldFilterSequenceToImport(const struct FAssetData& AssetData) const;`
- L33 _public prototype_ `FReply OnImportPoseFromSequence();`
- L34 _public prototype_ `void OnSequenceSelectedForPose(const FAssetData& SelectedAsset);`
- L35 _public member_ `TSharedPtr<SWindow> ImportPoseFromSequenceWindow;`
- L36 _public member_ `FSoftObjectPath SequenceToImportAsPose;`
- L37 _public member_ `int32 FrameOfSequenceToImport;`
- L38 _public member_ `FText ImportedPoseName;`
- L41 _public prototype_ `void HandleExportPoseAsset();` — export retarget pose to asset
- L45 _private prototype_ `static void NotifyUser(const FText& Message, SNotificationItem::ECompletionState NotificationType);`
- L47 _private member_ `TWeakPtr<FIKRetargetEditorController> Controller;`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/IKRetargetVariablesTabSummoner.h` (Public)


#### struct `FIKRetargetVariablesTabSummoner`  
`struct FIKRetargetVariablesTabSummoner : public FWorkflowTabFactory`  
_L11-22_
- inherits: `FWorkflowTabFactory`
- desc: Summons the "Variables" tab in the IK Retarget editor.
- L14 _public member_ `static const FName TabID;`
- L16 _public prototype_ `FIKRetargetVariablesTabSummoner(const TSharedRef<FIKRetargetEditor>& InIKRetargetEditor);`
- L17 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L18 _public prototype_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override;`
- L21 _protected member_ `TWeakPtr<FIKRetargetEditor> IKRetargetEditor;`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/IKRetargeterController.h` (Public)


#### enum `ERetargetStructViewerMode`  
`enum class ERetargetStructViewerMode : uint8`  
_L32-36_
- reflection: `UENUM()`
- desc: used to index into the map of cached struct viewers in the editor
- L34 _public enumerator_ `Settings`
- L35 _public enumerator_ `OverrideSets`

#### class `UIKRetargeterController`  
`class UIKRetargeterController : public UObject`  
_L41-849_
- reflection: `UCLASS(MinimalAPI, BlueprintType, hidecategories = UObject)`
- inherits: `UObject`
- desc: A stateless singleton (1-per-asset) class used to make modifications to a UIKRetargeter asset. Use UIKRetargeter.GetController() to get the controller for the asset you want to modify.
- L47 _public prototype_ `UIKRetargeterController();`
- L50 _public prototype_ `virtual void PostInitProperties() override;` — UObject
- L54 _public prototype_ `UIKRetargeter* GetAsset() const;` — Get access to the retargeter asset. Warning: Do not make modifications to the asset directly. Using the controller API guarantees correctness.
- L59 _private member_ `TObjectPtr<UIKRetargeter> Asset = nullptr;` — The actual asset that this Controller modifies. This is the only field this class should have.
- L71 _public prototype_ `static UIKRetargeterController* GetController(const UIKRetargeter* InRetargeterAsset);` — `UFUNCTION(BlueprintCallable, Category="IK Retarget", meta = (BlueprintThreadSafe, DisplayName = "Get IK Retarget Controller"))` — Get the controller for the given retargeter asset @param InRetargeterAsset an IK Retarget asset @return the controller with an API for modifying the given retarget asset
- L77 _public prototype_ `void SetIKRig(const ERetargetSourceOrTarget SourceOrTarget, UIKRigDefinition* IKRig) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Retarget", meta = (BlueprintThreadSafe, DisplayName = "Set IK Rig"))` — Set the IK Rig to use as the source or target (to copy animation FROM/TO) @param SourceOrTarget an enum specifying either "Source" or "Target" @param the IK Rig asset to apply as either the "Source" (to copy FROM) or "Target" (to copy TO)
- L83 _public prototype_ `const UIKRigDefinition* GetIKRig(const ERetargetSourceOrTarget SourceOrTarget) const;` — `UFUNCTION(BlueprintCallable, Category="IK Retarget", meta = (BlueprintThreadSafe, DisplayName = "Get IK Rig"))` — Get either source or target IK Rig @param SourceOrTarget an enum specifying either "Source" or "Target" @return the IK Rig asset associated with either the Source or Target of the IK Retargeter
- L88 _public prototype_ `TArray<UIKRigDefinition*> GetAllTargetIKRigs() const;` — `UFUNCTION(BlueprintCallable, Category="IK Retarget", meta = (BlueprintThreadSafe))` — Get all target IK Rigs referenced by all ops @return an array of all target IK Rig assets associated with all the ops in the stack
- L94 _public prototype_ `void SetPreviewMesh(const ERetargetSourceOrTarget SourceOrTarget, USkeletalMesh* InPreviewMesh) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Retarget", meta = (BlueprintThreadSafe))` — Set the preview skeletal mesh for either source or target @param SourceOrTarget an enum specifying either "Source" or "Target" @param InPreviewMesh a skeletal mesh asset to use as the preview mesh in the retarget editor (may be used on other meshes at runtime)
- L100 _public prototype_ `USkeletalMesh* GetPreviewMesh(const ERetargetSourceOrTarget SourceOrTarget) const;` — `UFUNCTION(BlueprintCallable, Category="IK Retarget", meta = (BlueprintThreadSafe))` — Get the preview skeletal mesh @param SourceOrTarget an enum specifying either "Source" or "Target" @return the skeletal mesh asset currently being used as a preview mesh
- L109 _public prototype_ `int32 AddRetargetOp(const FString InIKRetargetOpType) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Retarget")` — Add a new retarget op of the given type to the bottom of the stack. Returns the stack index. @param InIKRetargetOpType: the full package path of the UStruct type, ie /Script/IKRig.IKRetargetPinBoneOp
- L116 _public prototype_ `bool RemoveRetargetOp(const int32 InOpIndex) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Retarget")` — Remove the retarget op at the given stack index NOTE: if this op is a parent, all it's children will be removed as well @param InOpIndex: the index of the op to remove @return true if op was found and removed, false otherwise
- L121 _public prototype_ `bool RemoveAllOps() const;` — `UFUNCTION(BlueprintCallable, Category="IK Retarget")` — Remove all ops in the stack. @return true if any ops were removed, false otherwise
- L128 _public prototype_ `FName SetOpName(const FName InName, const int32 InOpIndex) const;` — `UFUNCTION(BlueprintCallable, Category="IK Retarget")` — Set the name of the op at the given index in the stack. @param InName the new name to use @param InOpIndex the index of the op to be renamed @return the new name of the op (after it's made unique)
- L134 _public prototype_ `FName GetOpName(const int32 InOpIndex) const ;` — `UFUNCTION(BlueprintCallable, Category="IK Retarget")` — Get the name of the op at the given index in the stack. @param InOpIndex the index of the op to get the name of @return the name of the op or None if the index was invalid
- L142 _public prototype_ `bool SetParentOpByName(const FName InChildOpName, const FName InParentOpName) const;` — `UFUNCTION(BlueprintCallable, Category="IK Retarget")` — Set the name of the op to parent this op to Children ops are forced to execute before their parent @param InChildOpName the op to be parented @param InParentOpName the name of the op to parent to @return true if both parent and child were found, and the parent relationship was allowed
- L148 _public prototype_ `FName GetParentOpByName(const FName InOpName) const ;` — `UFUNCTION(BlueprintCallable, Category="IK Retarget")` — Get the name of the parent op for the given op. @param InOpName the name of the op to get the parent of @return the name of the parent op or None if the op was not found or did not have a parent
- L154 _public prototype_ `int32 GetIndexOfOpByName(const FName InOpName) const;` — `UFUNCTION(BlueprintCallable, Category="IK Retarget")` — Get the index of an op. @param InOpName the name of the op to get the index of @return the integer index of the op in the stack or -1 if op not found.
- L161 _public prototype_ `void AddDefaultOps() const;` — `UFUNCTION(BlueprintCallable, Category="IK Retarget", meta = (BlueprintThreadSafe))` — Automatically add basic retargeting operations Adds these ops in the following order: Pelvis Motion, FK Chains, IK Chains, IK Solve and Root Motion If any of these ops are already present, they will not be re-added. @param bRunInitialSetup: if true, will run the initial setup routine on each op after they are all added to the stack.
- L167 _public prototype_ `void RunOpInitialSetup(const int32 InOpIndex) const;` — `UFUNCTION(BlueprintCallable, Category="IK Retarget", meta = (BlueprintThreadSafe))` — Force the op to run the initial setup. This is normally run when an Op is added through the editor UI. NOTE: ops may not have custom initial setup routines; the exact behavior is op-dependent @param InOpIndex the index of the op to run setup on
- L174 _public prototype_ `void AssignIKRigToAllOps(const ERetargetSourceOrTarget InSourceOrTarget, const UIKRigDefinition* InIKRig) const;` — `UFUNCTION(BlueprintCallable, Category="IK Retarget", meta = (BlueprintThreadSafe))` — Force all ops to use the assigned IK Rig and update their chain mappings. NOTE: some ops may not reference an IK Rig at all; the exact behavior is op-dependent @param InSourceOrTarget whether to assign the provided IK Rig as a source or target IK Rig @param InIKRig the IK Rig asset to assign
- L178 _public prototype_ `void ResetChainSettingsInAllOps(const FName InTargetChainName) const;` — `UFUNCTION(BlueprintCallable, Category="IK Retarget")` — Tell each op to reset any settings associated with this chain
- L183 _public prototype_ `int32 GetNumRetargetOps() const;` — `UFUNCTION(BlueprintCallable, Category="IK Retarget")` — Get the number of Ops in the stack. @return int, the number of ops
- L190 _public prototype_ `bool MoveRetargetOpInStack(int32 InOpToMoveIndex, int32 InTargetIndex) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Retarget")` — Move the retarget op at the given index to the target index. NOTE: due to constraints on execution order, the actual index may differ from what is requested @InOpToMoveIndex the index of the op to be moved @InTargetIndex the index where the op should be moved to
- L197 _public prototype_ `bool SetRetargetOpEnabled(int32 InRetargetOpIndex, bool bIsEnabled) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Retarget")` — Toggle an op on/off. @param InRetargetOpIndex the index of the op to modify @param bIsEnabled if true, turns the op On, else Off @return true if op was found at index
- L203 _public prototype_ `bool GetRetargetOpEnabled(int32 InRetargetOpIndex) const;` — `UFUNCTION(BlueprintCallable, Category="IK Retarget")` — Get enabled status of the given Op. @param InRetargetOpIndex the index of the op to get the enabled state for @return true if op is enabled, false if op is disabled or not found
- L210 _public prototype_ `UIKRetargetOpControllerBase* GetOpController(int32 InOpIndex);` — `UFUNCTION(BlueprintCallable, Category="IK Rig")` — Get a controller to get/set the settings for a given op in the stack NOTE: the returned UIKRetargetOpControllerBase* should be cast to the type specific to your op to get full functionality for that op. @param InOpIndex: the index of the op in the stack to return a controller for @return a pointer to the base op controller UClass or null if the op was not found
- L217 _public prototype_ `int32 AddRetargetOp(const UScriptStruct* InRetargetOpType, const FName InParentOpName = NAME_None) const;` — add a new retarget op to the stack
- L220 _public prototype_ `TArray<int32> GetChildOpIndices(const int32 InOpIndex) const;` — Gather up all the ops that are children of this op
- L223 _public prototype_ `bool GetCanOpHaveChildren(const int32 InOpIndex) const;` — Returns true if this op type can contain child ops (ops forced to be ordered before the parent)
- L226 _public prototype_ `int32 GetParentOpIndex(const int32 InOpIndex) const;` — Get the index of the parent op or INDEX_NONE if it's root level
- L229 _public prototype_ `FName GetUniqueOpName(const FName NameToMakeUnique, int32 OpIndexToIgnore) const;` — Return NameToMakeUnique with a numbered suffix that makes it unique in the stack
- L233 _public function_ `template <typename T> T* GetFirstRetargetOpOfType() const` — Get access to the first retarget operation of the given type
- L239 _public prototype_ `FIKRetargetOpBase* GetRetargetOpByIndex(const int32 InOpIndex) const;` — Get access to the given retarget operation by index.
- L242 _public prototype_ `FIKRetargetOpBase* GetRetargetOpByName(const FName InOpName) const;` — Get access to the given retarget operation by name.
- L245 _public prototype_ `FInstancedStruct* GetRetargetOpStructAtIndex(int32 Index) const;` — Get access to the given retarget operation.
- L248 _public prototype_ `int32 GetIndexOfRetargetOp(FIKRetargetOpBase* RetargetOp) const;` — Get the index of a given retarget operation.
- L251 _public prototype_ `void OnOpPropertyChanged(const FName& InOpName, const FPropertyChangedEvent& InPropertyChangedEvent) const;` — A callback whenever the property of an op is modified
- L254 _public prototype_ `uint8* GetChainSettingsMemory(const FName& InOpName, const FName InChainName) const;` — Return pointer to the memory associated with the given chain on the given op.
- L263 _public prototype_ `void CleanAsset() const;` — Ensures all internal data is compatible with assigned meshes and ready to edit. - Removes bones from retarget poses that are no longer in skeleton - Removes chain settings for chains that are no longer in target IK Rig
- L266 _public prototype_ `UIKRigDefinition* GetIKRigWriteable(const ERetargetSourceOrTarget SourceOrTarget) const;` — Get either source or target IK Rig
- L269 _public prototype_ `bool GetAskedToFixRootHeightForMesh(USkeletalMesh* Mesh) const;` — Get if we've already asked to fix the root height for the given skeletal mesh
- L272 _public prototype_ `void SetAskedToFixRootHeightForMesh(USkeletalMesh* Mesh, bool InAsked) const;` — Set if we've asked to fix the root height for the given skeletal mesh
- L275 _public prototype_ `FName GetPelvisBone(const ERetargetSourceOrTarget SourceOrTarget) const;` — Get name of the Root bone used for retargeting.
- L286 _public prototype_ `void AutoMapChains(const EAutoMapChainType AutoMapType, const bool bForceRemap, const FName InOpName=NAME_None) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Retarget", meta = (BlueprintThreadSafe))` — Use string comparision to find "best" Source chain to map to each Target chain or clear the mappings @param AutoMapType an enum specifying the type of mapping to perform (ie, Exact, Fuzzy or Clear) @param bForceRemap if false, will only remap those mappings that unset/None @param InOpName if specified, will auto-map only the chain mapping in the specified op, otherwise applies to all ops
- L293 _public prototype_ `bool SetSourceChain(FName InSourceChainName, FName InTargetChainName, const FName InOpName=NAME_None) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Retarget", meta = (BlueprintThreadSafe))` — Assign a source chain to the given target chain. Animation will be copied from the source to the target. @param InSourceChainName the name of the source retarget chain to assign @param InTargetChainName the name of the target chain to map @param InOpName if specified, will set the source chain only for that op (otherwise applies to all ops with a chain mapping)
- L300 _public prototype_ `FName GetSourceChain(const FName& InTargetChainName, const FName InOpName=NAME_None) const;` — `UFUNCTION(BlueprintCallable, Category="IK Retarget", meta = (BlueprintThreadSafe))` — Get the name of the source chain mapped to a given target chain (the chain animation is copied FROM). @param InTargetChainName the name of the target retarget chain to get a mapping for @param InOpName if specified, will get the source chain for that op (otherwise gets the first chain mapping in the op stack) @return the name of the source chain mapped to the given target chain (or None if not mapped)
- L306 _public prototype_ `void ResetChainSettingsToDefault(const FName InTargetChainName, const FName InOpName) const;` — `UFUNCTION(BlueprintCallable, Category="IK Retarget", meta = (BlueprintThreadSafe))` — Reset the settings for the given chain in the given op back to the defaults. @param InTargetChainName the name of the chain @param InOpName the name of the op containing the chain settings
- L315 _public prototype_ `const UIKRigDefinition* GetTargetIKRigForOp(const FName InOpName) const;` — `UFUNCTION(BlueprintCallable, Category="IK Retarget", meta = (BlueprintThreadSafe))` — Get the target IK Rig associated with the given Op. May be different than the default IK Rig. NOTE: all ops use the global SOURCE IK rig, but each op may use its own custom TARGET IK Rig. NOTE: not all ops maintain their own target IK Rig in which case this function returns nullptr NOTE: some ops may refer to the target IK Rig used by their parent op. In that case, this function returns the parent Op's IK Rig. @param InOpName the name of the retarget op @return the IK Rig assset associated with this op
- L323 _public prototype_ `const FRetargetChainMapping* GetChainMapping(const FName InOpName = NAME_None) const;` — Get access to the mapping between source/target chains for the particular op (may be null) If no op name is specified, it returns the first chain mapping it finds
- L326 _public prototype_ `void CleanChainMaps(const FName InOpName=NAME_None) const;` — Clean all chain mappings in all ops, or if InOpName is specified, just that op
- L329 _public prototype_ `bool AreChainSettingsAtDefault(const FName InTargetChainName, const FName InOpName) const;` — Ask if the given op has settings for the given chain that are not at the default
- L332 _public prototype_ `bool IsChainGoalConnectedToASolver(const FName& GoalName) const;` — Get whether the given chain's IK goal is connected to a solver
- L335 _public prototype_ `void HandleRetargetChainAdded(UIKRigDefinition* IKRig) const;` — Call this when IK Rig chain is added or removed.
- L338 _public prototype_ `void HandleRetargetChainRenamed(UIKRigDefinition* InIKRig, FName OldChainName, FName NewChainName) const;` — Call this when IK Rig chain is renamed. Retains existing mappings using the new name
- L341 _public prototype_ `void HandleRetargetChainRemoved(UIKRigDefinition* IKRig, const FName& InChainRemoved) const;` — Call this when IK Rig chain is removed.
- L352 _public prototype_ `FName CreateRetargetPose(const FName& NewPoseName, const ERetargetSourceOrTarget SourceOrTarget) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Retarget", meta =(BlueprintThreadSafe))` — Add new retarget pose. @param NewPoseName The name to assign to the new retarget pose @param SourceOrTarget Specifies whether the pose applies to the source or target skeleton @return The name of the newly created retarget pose
- L359 _public prototype_ `bool RemoveRetargetPose(const FName& PoseToRemove, const ERetargetSourceOrTarget SourceOrTarget) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Retarget", meta =(BlueprintThreadSafe))` — Remove a retarget pose. @param PoseToRemove The name of the retarget pose to remove @param SourceOrTarget Specifies whether the pose belongs to the source or target skeleton @return True if the pose was found and successfully removed, false otherwise
- L367 _public prototype_ `FName DuplicateRetargetPose(const FName PoseToDuplicate, const FName NewName, const ERetargetSourceOrTarget SourceOrTarget) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Retarget", meta =(BlueprintThreadSafe))` — Duplicate a retarget pose. @param PoseToDuplicate The name of the retarget pose to duplicate @param NewName The name to assign to the duplicated pose @param SourceOrTarget Specifies whether the pose belongs to the source or target skeleton @return The name of the new duplicated pose, or NAME_None if PoseToDuplicate is not found
- L375 _public prototype_ `bool RenameRetargetPose(const FName OldPoseName, const FName NewPoseName, const ERetargetSourceOrTarget SourceOrTarget) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Retarget", meta =(BlueprintThreadSafe))` — Rename current retarget pose. @param OldPoseName The current name of the retarget pose to rename @param NewPoseName The new name to assign to the retarget pose @param SourceOrTarget Specifies whether the pose belongs to the source or target skeleton @return True if the pose was found and successfully renamed, false otherwise
- L382 _public prototype_ `bool SetCurrentRetargetPose(FName CurrentPose, const ERetargetSourceOrTarget SourceOrTarget) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Retarget", meta =(BlueprintThreadSafe))` — Change which retarget pose is used by the retargeter at runtime. @param CurrentPose The name of the retarget pose to set as current @param SourceOrTarget Specifies whether the pose applies to the source or target skeleton @return True if the current pose was successfully set, false otherwise
- L388 _public prototype_ `FName GetCurrentRetargetPoseName(const ERetargetSourceOrTarget SourceOrTarget) const;` — `UFUNCTION(BlueprintCallable, Category="IK Retarget", meta =(BlueprintThreadSafe))` — Get the name of the current retarget pose. @param SourceOrTarget Specifies whether to retrieve the pose from the source or target skeleton @return The name of the current retarget pose
- L394 _public prototype_ `TMap<FName, FIKRetargetPose>& GetRetargetPoses(const ERetargetSourceOrTarget SourceOrTarget) const;` — `UFUNCTION(BlueprintCallable, Category="IK Retarget", meta =(BlueprintThreadSafe))` — Get access to array of retarget poses. @param SourceOrTarget Specifies whether to retrieve poses from the source or target skeleton @return A reference to the map of retarget pose names to their pose data
- L400 _public prototype_ `FIKRetargetPose& GetCurrentRetargetPose(const ERetargetSourceOrTarget SourceOrTarget) const;` — `UFUNCTION(BlueprintCallable, Category="IK Retarget", meta =(BlueprintThreadSafe))` — Get the current retarget pose. @param SourceOrTarget Specifies whether to retrieve the pose from the source or target skeleton @return A reference to the current retarget pose data
- L407 _public prototype_ `void ResetRetargetPose(const FName& PoseToReset, const TArray<FName>& BonesToReset, const ERetargetSourceOrTarget SourceOrTarget) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Retarget", meta =(BlueprintThreadSafe))` — Reset a retarget pose for the specified bones. @param PoseToReset The name of the retarget pose to reset @param BonesToReset The array of bone names to reset; if empty, resets all bones to the reference pose @param SourceOrTarget Specifies whether the pose belongs to the source or target skeleton
- L414 _public prototype_ `void SetRotationOffsetForRetargetPoseBone(const FName& BoneName, const FQuat& RotationOffset, const ERetargetSourceOrTarget SkeletonMode) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Retarget", meta =(BlueprintThreadSafe))` — Set a delta rotation for a given bone in the current retarget pose. @param BoneName The name of the bone to apply the rotation offset to @param RotationOffset The quaternion representing the rotation offset to apply @param SkeletonMode Specifies whether the bone belongs to the source or target skeleton
- L421 _public prototype_ `FQuat GetRotationOffsetForRetargetPoseBone(const FName& BoneName, const ERetargetSourceOrTarget SourceOrTarget) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Retarget", meta =(BlueprintThreadSafe))` — Get a delta rotation for a given bone in the current retarget pose. @param BoneName The name of the bone to retrieve the rotation offset for @param SourceOrTarget Specifies whether the bone belongs to the source or target skeleton @return The quaternion representing the rotation offset for the specified bone
- L427 _public prototype_ `void SetRootOffsetInRetargetPose(const FVector& TranslationOffset, const ERetargetSourceOrTarget SourceOrTarget) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Retarget", meta =(BlueprintThreadSafe))` — Set the translation offset on the retarget pelvis bone for the current retarget pose. @param TranslationOffset The vector representing the translation offset to apply to the pelvis bone @param SourceOrTarget Specifies whether the pelvis bone belongs to the source or target skeleton
- L433 _public prototype_ `FVector GetRootOffsetInRetargetPose(const ERetargetSourceOrTarget SourceOrTarget) const;` — `UFUNCTION(BlueprintCallable, Category="IK Retarget", meta = (BlueprintThreadSafe))` — Get the translation offset on the retarget pelvis bone for the current retarget pose. @param SourceOrTarget Specifies whether the pelvis bone belongs to the source or target skeleton @return The vector representing the translation offset of the pelvis bone
- L439 _public prototype_ `void AutoAlignAllBones(ERetargetSourceOrTarget SourceOrTarget, const ERetargetAutoAlignMethod Method = ERetargetAutoAlignMethod::ChainToChain) const;` — `UFUNCTION(BlueprintCallable, Category="IK Retarget")` — Automatically align all bones in mapped chains and store in the current retarget pose. @param SourceOrTarget Specifies whether to align bones in the source or target skeleton @param Method The method to use for automatic alignment (defaults to ChainToChain)
- L446 _public prototype_ `void AutoAlignBones(const TArray<FName>& BonesToAlign, const ERetargetAutoAlignMethod Method, ERetargetSourceOrTarget SourceOrTarget) const;` — `UFUNCTION(BlueprintCallable, Category="IK Retarget")` — Automatically align an array of bones and store in the current retarget pose. @param BonesToAlign The array of bone names to align; bones not in mapped chains are ignored @param Method The method to use for automatic alignment @param SourceOrTarget Specifies whether to align bones in the source or target skeleton
- L452 _public prototype_ `void SnapBoneToGround(FName ReferenceBone, ERetargetSourceOrTarget SourceOrTarget);` — `UFUNCTION(BlueprintCallable, Category="IK Retarget")` — Moves the entire skeleton vertically until the specified bone is the same height off the ground as in the reference pose. @param ReferenceBone The name of the bone to use as a reference for ground snapping @param SourceOrTarget Specifies whether the skeleton belongs to the source or target
- L459 _public prototype_ `FName MakePoseNameUnique( const FString& PoseName, const ERetargetSourceOrTarget SourceOrTarget) const;` — Add a numbered suffix to the given pose name to make it unique.
- L463 _public prototype_ `TWeakPtr<const FIKRigSkeleton> GetCachedIKRigSkeleton(const USkeletalMesh* InSkeletalMesh) const;`
- L473 _public prototype_ `FName AddNewRetargetOverrideSet(FName InOverrideSetName);` — `UFUNCTION(BlueprintCallable, Category="IK Retarget")` — Add a new override set to store retarget op setting overrides. @param InOverrideSetName    The name of the new set. @return The name of the new retarget override set (guaranteed unique).
- L479 _public prototype_ `bool RemoveRetargetOverrideSet(FName InOverrideSetName);` — `UFUNCTION(BlueprintCallable, Category="IK Retarget")` — Remove an override set by name. @param InOverrideSetName    The name of the override set to remove. @return True if the override set was removed, false otherwise.
- L486 _public prototype_ `bool RenameRetargetOverrideSet(FName InOverrideSetName, FName InNewName);` — `UFUNCTION(BlueprintCallable, Category="IK Retarget")` — Rename an existing override set. @param InOverrideSetName    The name of the override set to rename. @param InNewName            The new name. @return True if the override set was renamed, false otherwise.
- L492 _public prototype_ `FName DuplicateRetargetOverrideSet(FName InOverrideSetName);` — `UFUNCTION(BlueprintCallable, Category="IK Retarget")` — Duplicate an existing override set, creating a new set with all the same property overrides. @param InOverrideSetName    The name of the override set to duplicate. @return The name of the new duplicated override set (guaranteed unique).
- L499 _public prototype_ `void ReorderOverrideSet(FName InSetToMove, FName InTargetSet, bool bInsertAfter);` — Reorder an override set relative to another set. The dragged set becomes a sibling of the target (same parent) and is placed before or after it. @param InSetToMove      The override set to move. @param InTargetSet      The override set to position relative to. @param bInsertAfter     If true, insert after target. If false, insert before.
- L507 _public prototype_ `bool SetParentOverrideSet(FName InOverrideSetName, FName InParentName);` — `UFUNCTION(BlueprintCallable, Category="IK Retarget")` — Assign a parent to the given override set. NOTE: Override sets can be applied hierarchically to make for easy composition of property overrides. @param InOverrideSetName    The name of the override set to re-parent. @param InParentName         The new parent name or NAME_None. @return True if the override set was re-parented, false otherwise.
- L513 _public prototype_ `FName GetParentOverrideSet(FName InOverrideSetName);` — `UFUNCTION(BlueprintCallable, Category="IK Retarget")` — Get the name of the parent for the given override set. @param InOverrideSetName    The name of the override set. @return The name of the parent override set or NAME_None.
- L520 _public prototype_ `FName GetUniqueOverrideSetName(const FName NameToMakeUnique) const;` — Return NameToMakeUnique with a numbered suffix that makes it unique among existing override sets.
- L523 _public prototype_ `const TMap<FName, FRetargetOverrideSet>& GetAllOverrideSets() const;` — Get read-only access to all override sets in the retargeter.
- L526 _public prototype_ `FRetargetOverrideSet* FindOverrideSet(const FName InOverrideSetName) const;` — Get access to an override set by name.
- L529 _public prototype_ `FRetargetOpPropertyOverride* FindPropertyOverride( const FName InOverrideSetName, const FName InOpName, const FString& InPropertyPath) const;` — Helper to get a single property override
- L535 _public prototype_ `const TArray<FName> GetAllChildrenOverrideSets(const FName InOverrideSetName) const;` — Get a list of all override sets that are children of the given set (recursive).
- L538 _public prototype_ `const TArray<FName> GetDirectChildrenOverrideSets(const FName InOverrideSetName) const;` — Get a list of all override sets that are direct children of the given set (non-recursive).
- L541 _public prototype_ `FRetargetOpOverrides* FindOpOverrides(const FName InOverrideSetName, const FName InOpName) const;` — Find the specific op overrides within a given override set.
- L544 _public prototype_ `FRetargetOpOverrides* AddOpOverrides(const FName InOverrideSetName, const FName InOpName) const;` — Add an Op override entry to the given override set.
- L547 _public prototype_ `bool RemoveOpOverrides(const FName InOverrideSetName, const FName InOpName) const;` — Remove all property overrides for the given op in the given override set.
- L550 _public prototype_ `bool UpdateOverrideValue( const FName InOverrideSetName, const FName InOpName, const FString& InPropertyPath, const FStructOnScope& InNewValue, const bool bShouldTransact=true) const;` — Update the value of a stored property override inside the given override set, for the given op and property path.
- L558 _public prototype_ `bool BindPropertyOverrideToCurve( const FName& InCurveName, const FName InOverrideSetName, const FName InOpName, const FString& InPropertyPath) const;` — Bind a property override to a curve.
- L571 _public prototype_ `bool BindPropertyOverrideToVariable( const FName InVariableName, const FName InOverrideSetName, const FName InOpName, const FString& InPropertyPath) const;` — Bind the given variable to the given property override. @param InVariableName The name of the variable to bind. Use NAME_None to unbind. @param InOverrideSetName The name of the override set containing the op. @param InOpName The name of the specific retarget op containing the property. @param InPropertyPath The leaf property path within the op settings. @return true if the binding was successful, false otherwise
- L583 _public prototype_ `bool ClearPropertyOverrideBinding( const FName InOverrideSetName, const FName InOpName, const FString& InPropertyPath) const;` — Clear all bindings on the given property override. @param InOverrideSetName The name of the override set containing the op. @param InOpName The name of the specific retarget op containing the property. @param InPropertyPath The leaf property path within the op settings. @return true if the binding was found and cleared, false otherwise
- L593 _public prototype_ `bool CanPropertyOverrideBindToCurve( const FName InOpName, const FString& InPropertyPath) const;` — Check if this property override is compatible with curve binding (is a numeric type). @param InOpName The name of the specific retarget op containing the property. @param InPropertyPath The leaf property path within the op settings. @return true if the override can be bound to a curve, false otherwise
- L598 _public prototype_ `bool AddPropertyOverrideToOp(const FName InOverrideSetName, const FName InOpName, const FString& InPropertyPath) const;` — Add a property override for a specific op within a specific override set.
- L601 _public prototype_ `bool OverrideAllProperties(const FName InOverrideSetName, const FName InOpName) const;` — Add a property override for all properties within the given op.
- L604 _public prototype_ `bool OverrideAllEditedProperties(const FName InOverrideSetName, const FName InOpName) const;` — Add a property override for all edited properties within the given op (properties not at their default value).
- L607 _public prototype_ `bool RemovePropertyOverrideFromOp(const FName InOverrideSetName, const FName InOpName, const FString& InPropertyPath) const;` — Remove a given property override for a specific op within a specific override set.
- L610 _public prototype_ `bool RemoveAllPropertyOverridesFromSet(const FName InOverrideSetName) const;` — Remove all property overrides from all ops stored in the given override set.
- L614 _public prototype_ `bool SetOverrideSetActiveByDefault(const FName InOverrideSetName, const bool bActiveByDefault) const;` — Set the given override set to be active by default (unless otherwise overridden by the user). @return True if the override set was found and modified, false otherwise.
- L618 _public prototype_ `bool GetOverrideSetActiveByDefault(const FName InOverrideSetName) const;` — Get if the given override set is configured to be active by default. @return True if the override set was found and is active by default, false otherwise.
- L621 _public prototype_ `bool HasPropertyOverride(const FName InOverrideSetName, const FName InOpName, const FString& InPropertyPath) const;` — Returns true if the given override set has an override for the given property on the given op.
- L624 _public prototype_ `FName GetOverrideSetName(const FRetargetOverrideSet* InOverrideSet) const;` — Returns the name of the given override set.
- L627 _public prototype_ `FProperty* GetPropertyForOverride(const FName InOpName, const FString& InPropertyPath) const;` — Helper to get an FProperty* for a given property override
- L634 _public prototype_ `const FRetargetVariableContainer& GetVariables() const;` — Get read-only access to the set of variables for this retarget asset.
- L640 _public prototype_ `const FProperty* GetVariableProperty(const FName InVariableName) const;` — Get the FProperty of a variable by name. @param InVariableName The name of the variable to find in the property bag. @return The FProperty if found, otherwise nullptr.
- L648 _public prototype_ `static bool IsPropertyCompatibleForBinding(const FProperty* Source, const FProperty* Target);` — Determine if the source property (override) can be bound to the target (variable). This checks for type compatibility, including allowed casts like float to double. @param Source The property override being bound. @param Target The property of the variable being bound to. @return True if the properties are compatible for a data binding.
- L656 _public prototype_ `FName GetVariableBoundToPropertyOverride( const FName InOverrideSetName, const FName InOpName, const FString& InPropertyPath) const;` — Get the name of the variable bound to the given property override. @param InOverrideSetName The name of the override set. @param InOpName The name of the operation. @param InPropertyPath The specific property path to check. @return The name of the bound variable, or NAME_None if no binding exists.
- L667 _public prototype_ `FName GetCurveBoundToPropertyOverride( const FName InOverrideSetName, const FName InOpName, const FString& InPropertyPath) const;` — Get the name of the curve bound to the given property override. @param InOverrideSetName The name of the override set. @param InOpName The name of the operation. @param InPropertyPath The specific property path to check. @return The name of the bound curve, or NAME_None if no binding exists.
- L678 _public prototype_ `bool GetPropertyOverrideHasBinding( const FName InOverrideSetName, const FName InOpName, const FString& InPropertyPath) const;` — Get if the property override is bound to anything (curve or variable). @param InOverrideSetName The name of the override set. @param InOpName The name of the operation. @param InPropertyPath The specific property path to check. @return true if the override is bound to anything, false otherwise
- L687 _public prototype_ `FName AddNewVariable(const FName InVariableName) const;` — Adds a new variable to the retargeter's variable container (defaults to float type) @param InVariableName The desired name for the new variable (if Name_None, a default name is created) @return The actual name assigned to the variable (may be suffixed if a name collision occurred).
- L693 _public prototype_ `bool DeleteVariable(const FName InVariableName) const;` — Deletes a variable from the retargeter and clears any associated property bindings. @param InVariableName The name of the variable to remove. @return True if the variable was found and successfully removed.
- L700 _public prototype_ `bool RenameVariable(const FName InVariableName, const FName InNewName) const;` — Renames an existing variable and updates all internal property bindings to reflect the new name. @param InVariableName The current name of the variable. @param InNewName The new name to assign to the variable. @return True if the rename was successful.
- L707 _public prototype_ `bool SetVariableType(const FName InVariableName, const FEdGraphPinType& NewPinType) const;` — Changes the underlying data type of a variable. This may clear existing bindings if types become incompatible. @param InVariableName The name of the variable to modify. @param NewPinType The new type definition (float, bool, etc.) via a Graph Pin Type. @return True if the type was successfully changed.
- L713 _public prototype_ `bool GetVariableExists(const FName InVariableName) const;` — Check if a variable with the given name exists in this asset. @param InVariableName The name to check. @return True if the variable exists in the property bag.
- L718 _public prototype_ `void IterateAllOverrides(const TFunctionRef<void(FRetargetOpPropertyOverride&)>& Visitor) const;` — Helper to iterate every PropertyOverride in the asset. @param Visitor A lambda or function to execute for every override found in the asset.
- L723 _private prototype_ `void PostEditOverrideSets() const;` — Controller functions call this anytime the override sets are modified
- L726 _private prototype_ `void CleanPoseList(const ERetargetSourceOrTarget SourceOrTarget) const;` — Remove bones from retarget poses that are no longer in skeleton
- L736 _public prototype_ `const FRetargetChainMapping& GetChainMapping() const;` — `UE_DEPRECATED(5.6, "Chain mappings are stored on individual ops. Use the version that takes an op name. ")` — get access to the mapping between source/target chains
- L741 _public prototype_ `FTargetRootSettings GetRootSettings() const;` — `UE_DEPRECATED(5.6, "Root settings are now accessed through the Pelvis Motion Op controller.")` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Retarget", meta = (BlueprintThreadSafe))` — Get a copy of the retarget root settings for this asset.
- L746 _public prototype_ `void SetRootSettings(const FTargetRootSettings& RootSettings) const;` — `UE_DEPRECATED(5.6, "Root settings are now accessed through the Pelvis Motion Op controller.")` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Retarget", meta = (BlueprintThreadSafe))` — Set the retarget root settings for this asset.
- L751 _public prototype_ `FRetargetGlobalSettings GetGlobalSettings() const;` — `UE_DEPRECATED(5.6, "Global settings are now accessed through Op controllers that perform the same duties.")` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Retarget", meta = (BlueprintThreadSafe))` — Get a copy of the global settings for this asset.
- L756 _public prototype_ `void SetGlobalSettings(const FRetargetGlobalSettings& GlobalSettings) const;` — `UE_DEPRECATED(5.6, "Global settings are now accessed through Op controllers that perform the same duties.")` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Retarget", meta = (BlueprintThreadSafe))` — Get a copy of the global settings for this asset.
- L761 _public prototype_ `FTargetChainSettings GetRetargetChainSettings(const FName& TargetChainName) const;` — `UE_DEPRECATED(5.6, "Access to chain settings must go through an Op controller now.")` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Retarget", meta = (BlueprintThreadSafe))` — Get a copy of the settings for the target chain by name.
- L766 _public prototype_ `bool SetRetargetChainSettings(const FName& TargetChainName, const FTargetChainSettings& Settings) const;` — `UE_DEPRECATED(5.6, "Access to chain settings must go through an Op controller now.")` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Retarget", meta = (BlueprintThreadSafe))` — Set the settings for the target chain by name. Returns true if the chain settings were applied, false otherwise.
- L771 _public prototype_ `const TArray<URetargetChainSettings*>& GetAllChainSettings() const;` — `UE_DEPRECATED(5.6, "Access to chain settings must go through an Op controller now.")` — `UFUNCTION(BlueprintCallable, Category="IK Retarget", meta = (BlueprintThreadSafe))` — Get read-only access to the list of settings for each target chain
- L775 _public prototype_ `URetargetChainSettings* GetChainSettings(const FName& TargetChainName) const;` — `UE_DEPRECATED(5.6, "Access to chain settings must go through an Op controller now.")` — convenience to get chain settings UObject by name
- L787 _private prototype_ `DECLARE_MULTICAST_DELEGATE(FOnRetargeterNeedsInitialized);` — DELEGATE CALLBACKS FOR OUTSIDE SYSTEMS
- L788 _private member_ `FOnRetargeterNeedsInitialized RetargeterNeedsInitialized;`
- L790 _private prototype_ `DECLARE_MULTICAST_DELEGATE(FOnOpStackModified);`
- L791 _private member_ `FOnOpStackModified OpStackModified;`
- L793 _private prototype_ `DECLARE_MULTICAST_DELEGATE(FOnOverrideSetsModified);`
- L794 _private member_ `FOnOverrideSetsModified OverrideSetsModified;`
- L796 _private prototype_ `DECLARE_MULTICAST_DELEGATE(FOnVariablesModified);`
- L797 _private member_ `FOnVariablesModified VariablesModified;`
- L799 _private prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnIKRigReplaced, ERetargetSourceOrTarget);`
- L800 _private member_ `FOnIKRigReplaced IKRigReplaced;`
- L802 _private prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPreviewMeshReplaced, ERetargetSourceOrTarget);`
- L803 _private member_ `FOnPreviewMeshReplaced PreviewMeshReplaced;`
- L806 _private member_ `TUniquePtr<FRetargetAutoPoseGenerator> AutoPoseGenerator;` — auto pose generator
- L809 _private member_ `mutable FCriticalSection ControllerLock;` — only allow modifications to data model from one thread at a time
- L812 _private member_ `mutable int32 ReinitializeScopeCounter = 0;` — prevent reinitializing from inner operations
- L818 _private member_ `TMap<ERetargetStructViewerMode, TObjectPtr<UIKRigStructViewer>> StructViewers;` — `UPROPERTY(Transient)` — a dummy UObject to wrap UStructs for the details panel maps each mode to its corresponding UIKRigStructViewer wrapper
- L821 _private member_ `mutable TMap<const USkeletalMesh*, TSharedPtr<FIKRigSkeleton>> CachedSkeletons;` — transient cache used for duration of editing
- L826 _public function_ `FOnPreviewMeshReplaced& OnPreviewMeshReplaced()` — Attach a delegate to be notified whenever either the source or target Preview Mesh asset's are swapped out.
- L829 _public function_ `FOnIKRigReplaced& OnIKRigReplaced()` — Attach a delegate to be notified whenever either the source or target IK Rig asset's are swapped out.
- L832 _public function_ `FOnRetargeterNeedsInitialized& OnRetargeterNeedsInitialized()` — Attach a delegate to be notified whenever the retargeter is modified in such a way that would require re-initialization of the processor.
- L835 _public function_ `FOnOpStackModified& OnOpStackModified()` — Attach a delegate to be notified whenever the op stack is modified.
- L838 _public function_ `FOnOverrideSetsModified& OnOverrideSetsModified()` — Attach a delegate to be notified whenever the override sets are modified.
- L841 _public function_ `FOnVariablesModified& OnVariablesModified()` — Attach a delegate to be notified whenever the variables are modified.
- L845 _public prototype_ `UIKRigStructViewer* GetStructViewer(ERetargetStructViewerMode InMode);` — get the singleton struct viewer for editing structs belonging to the asset this controller controls NOTE: there are 2 details views in the retarget editor, the InMode specifies which viewer you want to reset and reuse

#### enum `ERetargetRefreshMode`  
`enum class ERetargetRefreshMode : uint8`  
_L852-857_
- desc: Retargeter can reinit just the processor or other UI as well depending on the data model modification type
- L854 _public enumerator_ `ProcessorOnly`
- L855 _public enumerator_ `ProcessorAndOpStack`
- L856 _public enumerator_ `ProcessorAndFullUI`

#### struct `FScopedReinitializeIKRetargeter`  
`struct FScopedReinitializeIKRetargeter`  
_L859-882_
- L861 _public function_ `FScopedReinitializeIKRetargeter(const UIKRetargeterController *InController, ERetargetRefreshMode InRefreshMode = ERetargetRefreshMode::ProcessorOnly)`
- L867 _public function_ `~FScopedReinitializeIKRetargeter()`
- L880 _public member_ `const UIKRetargeterController* Controller;`
- L881 _public member_ `ERetargetRefreshMode RefreshMode = ERetargetRefreshMode::ProcessorOnly;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API IKRIGEDITOR_API`
- L787 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnRetargeterNeedsInitialized);` — DELEGATE CALLBACKS FOR OUTSIDE SYSTEMS
- L790 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnOpStackModified);`
- L793 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnOverrideSetsModified);`
- L796 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnVariablesModified);`
- L799 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnIKRigReplaced, ERetargetSourceOrTarget);`
- L802 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPreviewMeshReplaced, ERetargetSourceOrTarget);`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/IKRetargeterPoseGenerator.h` (Public)


#### enum `ERetargetAutoAlignMethod`  
`enum class ERetargetAutoAlignMethod : uint8`  
_L29-39_
- reflection: `UENUM()`
- desc: A Note on Determining the "Direction" of a Bone... What are we using to determine the "direction" of the source and target bones to align? If chain only has one bone OR this bone is located at the end of a chain, then we cannot compute a tangent! So we fallback to an analysis of the geometry... this is necessary because we cannot rely solely on the shape of the skeleton. Any assumptions we make could be invalidated in different circumstances. For example, 1. we cannot assume the local axes are aligned in any meaningful way, and even if they are we cannot assume WHICH axis is the correct one 2. we cannot assume that any child bones are located in a position that would create a meaningful vector (ie twist bones in arbitrary locations) 3. we cannot assume that extrapolating the direction from the parent is meaningful. For example, feet are usually perpendicular to the knee. Since the skeleton cannot be relied upon to provide robust directional information for individual and/or leaf bones, we must instead fallback on looking at the mesh that is skinned to it and try to discern a direction vector from that. If there is no skinning data, then we simply do NOT auto-align that bone.
- L32 _public enumerator_ `ChainToChain` — use the chain to determine the source and target directions to align
- L34 _public enumerator_ `MeshToMesh` — use mesh direction as source, and mesh direction as the target to align
- L36 _public enumerator_ `LocalRotationAxes` — match the local rotation axes of each bone individually (will be horribly wrong if characters don't share axis orientations)
- L38 _public enumerator_ `GlobalRotationAxes` — match the global rotation axes of each bone individually (will be horribly wrong if characters don't share axis orientations)

#### struct `FRetargetAutoPoseGenerator`  
`struct FRetargetAutoPoseGenerator`  
_L42-136_
- desc: a sub-system used by the IKRetargetEditorController for automatically generating a retarget pose
- L45 _public prototype_ `FRetargetAutoPoseGenerator(const TWeakObjectPtr<UIKRetargeterController> InController);` — created and owned by the retarget editor controller
- L49 _public prototype_ `void AlignBones( const TArray<FName>& BonesToAlign, const ERetargetAutoAlignMethod Method, const ERetargetSourceOrTarget SourceOrTarget, const bool bSuppressWarnings) const;` — align the specified bones on the current skeleton to the OTHER skeleton, using the specified method NOTE: if BonesToAlign is empty, it will align ALL bones in the skeleton
- L57 _public prototype_ `void SnapToGround(const FName BoneToPutOnGround, const ERetargetSourceOrTarget SourceOrTarget) const;` — adjust the vertical height of the pelvis to place the character back on the ground if BoneToPutOnGround is not specified (NAME_None), then will find the lowest bone and use that
- L62 _private prototype_ `void AlignBone( const FName BoneToAlign, const ERetargetAutoAlignMethod Method, const ERetargetSourceOrTarget SourceOrTarget) const;` — generates a local rotation offset to align BoneToAlign to the opposite skeleton, and stores it in the current retarget pose
- L68 _private prototype_ `void AlignPelvisBone(const ERetargetSourceOrTarget SourceOrTarget) const;` — generates a local rotation offset to align the pelvis based on the spine orientation
- L71 _private prototype_ `bool GetSpineChain(const ERetargetSourceOrTarget SourceOrTarget, FName& OutChainName) const;` — get the chain most likely to be the spine
- L74 _private prototype_ `FVector GetChainDirection(const FName ChainName, const ERetargetSourceOrTarget SourceOrTarget) const;` — get the chain most likely to be the spine
- L77 _private prototype_ `void ApplyWorldRotationToRetargetPose( const FQuat& WorldRotationOffset, const FName BoneToAffect, const ERetargetSourceOrTarget SourceOrTarget) const;` — takes a world space rotation offset, converts it to local space and stores it in the current retarget pose
- L83 _private prototype_ `bool GetChainTangent( const FName ChainName, const float Param, const ERetargetSourceOrTarget SourceOrTarget, FVector& OutDirection) const;` — get the tangent vector of a retarget chain at a given param (0-1)
- L90 _private prototype_ `bool GetChainTangentFromMesh( const FName ChainName, const float Param, const ERetargetSourceOrTarget SourceOrTarget, FVector& OutDirection) const;` — discern the direction of a bone based on the mesh it is skinned to
- L97 _private prototype_ `void GetPointsWeightedToBones( const TArray<FName>& Bones, const ERetargetSourceOrTarget SourceOrTarget, TArray<FVector>& OutVertexPositions) const;` — get the locations of vertices skinned to a sub-set of bones
- L103 _private prototype_ `void GetAllChildrenOfBone( const FName Bone, const ERetargetSourceOrTarget SourceOrTarget, TArray<FName>& OutAllChildren) const;` — get all children (recursive) of the given bone
- L109 _private prototype_ `void GetRefPoseVerticesAndWeights( const ERetargetSourceOrTarget SourceOrTarget, TArray<TMap<FName, float>>& OutWeights, TArray<FVector>& OutPositions) const;` — get the vertex ref pose and skinning weights for a given mesh (source or target)
- L115 _private prototype_ `void GetDeformedVertexPositions( const TArray<int32>& VerticesToDeform, const TArray<FVector>& VertexRefPose, const TArray<FTransform>& RefPoseBoneTransforms, const TArray<FTransform>& CurrentBoneTransforms, const TArray<TMap<FName, float>>& SkinWeights, const ERetargetSourceOrTarget SourceOrTarget, TArray<FVector>& OutDeformedPositions) const;` — calculates the skinned vertex positions for a subset of the mesh using the supplied bone transforms
- L125 _private prototype_ `bool IsARetargetLeaf( const FName ChainName, const float Param, ERetargetSourceOrTarget SourceOrTarget) const;` — gets the bone at this point in the chain, returns true if non of it's children are retargeted
- L131 _private prototype_ `bool CheckReadyToAlignBones() const;` — get the processor from the editor and return true if it's initialized
- L133 _private member_ `TWeakObjectPtr<UIKRetargeterController> Controller;`
- L134 _private member_ `TSharedPtr<FIKRetargetProcessor> Processor;`
- L135 _private member_ `static constexpr float ParamStepSize = 0.1f;`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/IKRetargeterThumbnailRenderer.h` (Public)


#### class `FIKRetargeterThumbnailScene`  
`class FIKRetargeterThumbnailScene : public FThumbnailPreviewScene`  
_L16-33_
- inherits: `FThumbnailPreviewScene`
- L20 _public prototype_ `FIKRetargeterThumbnailScene();`
- L23 _public prototype_ `void SetSkeletalMeshes(USkeletalMesh* SourceMesh, USkeletalMesh* TargetMesh) const;` — sets the retargeter to use in the next CreateView()
- L27 _protected prototype_ `virtual void GetViewMatrixParameters(const float InFOVDegrees, FVector& OutOrigin, float& OutOrbitPitch, float& OutOrbitYaw, float& OutOrbitZoom) const override;` — FThumbnailPreviewScene implementation
- L31 _private member_ `ASkeletalMeshActor* SourceActor;` — the skeletal mesh actors used to display all skeletal mesh thumbnails
- L32 _private member_ `ASkeletalMeshActor* TargetActor;`

#### class `UIKRetargeterThumbnailRenderer`  
`class UIKRetargeterThumbnailRenderer : public UDefaultSizedThumbnailRenderer`  
_L38-57_
- reflection: `UCLASS(config=Editor, MinimalAPI)`
- inherits: `UDefaultSizedThumbnailRenderer`
- desc: this thumbnail renderer displays a given IK Rig in the asset icon
- L43 _private prototype_ `virtual bool CanVisualizeAsset(UObject* Object) override;`
- L44 _private prototype_ `virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget*, FCanvas* Canvas, bool bAdditionalViewFamily) override;`
- L45 _private prototype_ `virtual EThumbnailRenderFrequency GetThumbnailRenderFrequency(UObject* Object) const override;`
- L49 _private prototype_ `virtual void BeginDestroy() override;` — UObject implementation
- L52 _private prototype_ `USkeletalMesh* GetPreviewMeshFromAsset(UObject* Object, ERetargetSourceOrTarget SourceOrTarget) const;`
- L53 _private prototype_ `bool HasSourceOrTargetMesh(UObject* Object) const;`
- L56 _protected member_ `TObjectInstanceThumbnailScene<FIKRetargeterThumbnailScene, 128> ThumbnailSceneCache;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API IKRIGEDITOR_API`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/SIKRetargetAssetBrowser.h` (Public)


#### class `SIKRetargetAssetBrowser`  
`class SIKRetargetAssetBrowser : public SBox`  
_L15-59_
- inherits: `SBox`
- L18 _public function_ `SLATE_BEGIN_ARGS(SIKRetargetAssetBrowser)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FIKRetargetEditorController> InEditorController);`
- L23 _public prototype_ `void RefreshView();`
- L27 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;`
- L30 _private prototype_ `void ExecuteFindInContentBrowserAction();`
- L31 _private prototype_ `bool CanExecuteFindInContentBrowserAction();`
- L33 _private prototype_ `FReply OnExportButtonClicked();`
- L34 _private prototype_ `bool IsExportButtonEnabled() const;`
- L36 _private prototype_ `FReply OnPlayRefPoseClicked();`
- L37 _private prototype_ `bool IsPlayRefPoseEnabled() const;`
- L39 _private prototype_ `void OnAssetDoubleClicked(const FAssetData& AssetData);`
- L40 _private prototype_ `bool OnShouldFilterAsset(const struct FAssetData& AssetData);`
- L41 _private prototype_ `TSharedPtr<SWidget> OnGetAssetContextMenu(const TArray<FAssetData>& SelectedAssets) const;`
- L44 _private member_ `FGetCurrentSelectionDelegate GetCurrentSelectionDelegate;` — Used to get the currently selected assets
- L47 _private member_ `TWeakPtr<FIKRetargetEditorController> EditorController;` — editor controller
- L50 _private member_ `TSharedPtr<SBox> AssetBrowserBox;` — the animation asset browser
- L53 _private member_ `FString PrevBatchOutputPath = "";` — remember the path the user chose between exports
- L56 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Commands to execute

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/SIKRetargetChainMapList.h` (Public)


#### class `FRetargetChainMapElement`  
`class FRetargetChainMapElement`  
_L22-45_
- L26 _public prototype_ `TSharedRef<ITableRow> MakeListRowWidget( const TSharedRef<STableViewBase>& InOwnerTable, TSharedRef<FRetargetChainMapElement> InStackElement, TSharedPtr<SIKRetargetChainMapList> InChainList);`
- L31 _public function_ `static TSharedRef<FRetargetChainMapElement> Make(FName InTargetChainName)`
- L36 _public member_ `FName TargetChainName;`
- L41 _private function_ `FRetargetChainMapElement(FName InTargetChainName) : TargetChainName(InTargetChainName)` — Hidden constructor, always use Make above
- L44 _private prototype_ `FRetargetChainMapElement() = default;` — Hidden constructor, always use Make above

#### class `SIKRetargetChainMapRow`  
`class SIKRetargetChainMapRow : public SMultiColumnTableRow< FRetargetChainMapElementPtr >`  
_L48-80_
- inherits: `SMultiColumnTableRow<FRetargetChainMapElementPtr>`
- L52 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, TSharedRef<FRetargetChainMapElement> InChainElement, TSharedPtr<SIKRetargetChainMapList> InChainList);`
- L59 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;` — Overridden from SMultiColumnTableRow.  Generates a widget for this column of the table row.
- L61 _public prototype_ `void OnSourceChainComboSelectionChanged(TSharedPtr<FString> InName, ESelectInfo::Type SelectInfo);`
- L65 _private prototype_ `FReply OnResetToDefaultClicked();`
- L67 _private prototype_ `EVisibility GetResetToDefaultVisibility() const;`
- L69 _private prototype_ `FText GetSourceChainName() const;`
- L71 _private prototype_ `FText GetTargetIKGoalName() const;`
- L73 _private member_ `TArray<TSharedPtr<FString>> SourceChainOptions;`
- L75 _private member_ `TWeakPtr<FRetargetChainMapElement> ChainMapElement;`
- L77 _private member_ `TWeakPtr<SIKRetargetChainMapList> ChainMapList;`

#### struct `FChainMapFilterOptions`  
`struct FChainMapFilterOptions`  
_L82-96_
- L84 _public member_ `bool bHideUnmappedChains = false;`
- L85 _public member_ `bool bHideMappedChains = false;`
- L86 _public member_ `bool bHideChainsWithoutIK = false;`
- L88 _public member_ `bool bNeverShowChainsWithoutIK = false;`
- L90 _public function_ `void Reset()`

#### struct `FChainMapListConfig`  
`struct FChainMapListConfig`  
_L98-120_
- L101 _public member_ `FName OpWithChainSettings = NAME_None;` — the name of the op that owns the chain settings
- L103 _public member_ `FName OpWithChainMapping = NAME_None;` — the name of the op that owns the chain mapping
- L105 _public member_ `TWeakObjectPtr<UIKRetargeterController> Controller;` — the asset controller that owns the op
- L107 _public member_ `FChainMapFilterOptions Filter;` — the default filter options for the list
- L109 _public member_ `bool bEnableGoalColumn = true;` — whether to show the column for IK goals or not
- L111 _public member_ `bool bEnableChainMapping = true;` — whether to allow remapping target chains to source chains
- L113 _public member_ `TFunction<UObject*(FName)> ChainSettingsGetterFunc;` — a callback to get the chain settings for a given chain
- L115 _public function_ `bool IsValid() const`

#### class `SIKRetargetChainMapList`  
`class SIKRetargetChainMapList : public SCompoundWidget, FEditorUndoClient, FGCObject`  
_L124-187_
- inherits: `SCompoundWidget,FEditorUndoClient,FGCObject`
- L129 _public function_ `SLATE_BEGIN_ARGS(SIKRetargetChainMapList)`
- L130 _public prototype_ `SLATE_ARGUMENT(FChainMapListConfig, InChainMapListConfig) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L135 _public prototype_ `void ClearSelection() const;`
- L137 _public prototype_ `void ResetChainSettings(const FName InTargetChainName) const;`
- L140 _public prototype_ `void RefreshView();` — call to refresh the list view
- L143 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;` — FGCObject interface
- L144 _public function_ `virtual FString GetReferencerName() const override`
- L153 _private member_ `FChainMapListConfig Config;` — the options for this chain map list
- L156 _private member_ `TSharedPtr<SRetargetChainMapListViewType> ListView;` — list view
- L157 _private member_ `TArray< TSharedPtr<FRetargetChainMapElement> > ListViewItems;`
- L161 _private member_ `TSharedPtr<IDetailsView> DetailsView;` — the details view for editing selected chain properties
- L164 _private prototype_ `bool IsListEnabled() const;` — callbacks
- L165 _private prototype_ `bool IsChainMappingEnabled() const;`
- L167 _private prototype_ `void OnItemClicked(TSharedPtr<FRetargetChainMapElement> InItem);` — when a chain is clicked on in the table view
- L168 _private member_ `TArray<TObjectPtr<UObject>> AllStructWrappers;`
- L171 _private prototype_ `TSharedRef<SWidget> CreateChainMapMenuWidget();` — auto-map chain button
- L172 _private prototype_ `void AutoMapChains(const EAutoMapChainType AutoMapType, const bool bSetUnmatchedToNone);`
- L176 _private prototype_ `TSharedRef<SWidget> CreateFilterMenuWidget();` — filtering the list with search box
- L177 _private prototype_ `void OnFilterTextChanged(const FText& SearchText);`
- L178 _private member_ `TSharedPtr<FTextFilterExpressionEvaluator> TextFilter;`
- L180 _private member_ `TSharedPtr<FUICommandList> MenuCommandList;` — menu for adding new solver commands
- L183 _private prototype_ `TSharedRef<ITableRow> MakeListRowWidget(TSharedPtr<FRetargetChainMapElement> InElement, const TSharedRef<STableViewBase>& OwnerTable);` — list view generate row callback

#### Free symbols / members of external scopes

- L47 _typedef_ `typedef TSharedPtr< FRetargetChainMapElement > FRetargetChainMapElementPtr;`
- L122 _typedef_ `typedef SListView< TSharedPtr<FRetargetChainMapElement> > SRetargetChainMapListViewType;`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/SIKRetargetHierarchy.h` (Public)


#### class `FIKRetargetHierarchyElement`  
`class FIKRetargetHierarchyElement : public TSharedFromThis<FIKRetargetHierarchyElement>`  
_L16-33_
- inherits: `TSharedFromThis<FIKRetargetHierarchyElement>`
- L20 _public prototype_ `FIKRetargetHierarchyElement(const FName& InName, const TSharedRef<FIKRetargetEditorController>& InEditorController);`
- L22 _public member_ `FText Key;`
- L23 _public member_ `TWeakPtr<FIKRetargetHierarchyElement> Parent;`
- L24 _public member_ `TArray<TWeakPtr<FIKRetargetHierarchyElement>> Children;`
- L25 _public member_ `FName Name;`
- L26 _public member_ `bool bIsHidden = false;`
- L28 _public prototype_ `FName GetChainName() const;`
- L32 _private member_ `TWeakPtr<FIKRetargetEditorController> EditorController;`

#### class `SIKRetargetHierarchyRow`  
`class SIKRetargetHierarchyRow : public SMultiColumnTableRow<TSharedPtr<FIKRetargetHierarchyElement>>`  
_L35-64_
- inherits: `SMultiColumnTableRow<TSharedPtr<FIKRetargetHierarchyElement>>`
- L40 _public function_ `SLATE_BEGIN_ARGS(SIKRetargetHierarchyRow)`
- L41 _public function_ `SLATE_ARGUMENT(TSharedPtr<FIKRetargetEditorController>, EditorController) SLATE_ARGUMENT(TSharedPtr<FIKRetargetHierarchyElement>, TreeElement) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable)`
- L57 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;` — Overridden from SMultiColumnTableRow.  Generates a widget for this column of the list view.
- L61 _private member_ `TSharedPtr<STableViewBase> OwnerTable;`
- L62 _private member_ `TWeakPtr<FIKRetargetHierarchyElement> WeakTreeElement;`
- L63 _private member_ `TWeakPtr<FIKRetargetEditorController> EditorController;`

#### struct `FRetargetHierarchyFilterOptions`  
`struct FRetargetHierarchyFilterOptions`  
_L66-71_
- L68 _public member_ `bool bHideBonesNotInChain;`
- L69 _public member_ `bool bHideNotRetargetedBones;`
- L70 _public member_ `bool bHideRetargetedBones;`

#### class `SIKRetargetHierarchy`  
`class SIKRetargetHierarchy : public SCompoundWidget, public FEditorUndoClient`  
_L75-120_
- inherits: `SCompoundWidget,FEditorUndoClient`
- L78 _public function_ `SLATE_BEGIN_ARGS(SIKRetargetHierarchy)`
- L79 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FIKRetargetEditorController> InEditorController);`
- L83 _public prototype_ `void ShowItemAfterSelection(FName ItemKey);`
- L85 _public function_ `void RefreshPoseList() const`
- L90 _private member_ `TWeakPtr<FIKRetargetEditorController> EditorController;` — centralized editor controls (facilitate cross-communication between multiple UI elements)
- L93 _private member_ `TSharedPtr<FUICommandList> CommandList;` — command list we bind to
- L96 _private member_ `TSharedPtr<SIKRetargetPoseEditor> EditPoseView;` — edit pose widget
- L99 _private member_ `TSharedPtr<SIKRetargetHierarchyTreeView> TreeView;` — tree view widget
- L100 _private member_ `TArray<TSharedPtr<FIKRetargetHierarchyElement>> RootElements;`
- L101 _private member_ `TArray<TSharedPtr<FIKRetargetHierarchyElement>> AllElements;`
- L104 _private prototype_ `TSharedRef<SWidget> CreateFilterMenuWidget();` — filtering the tree with search box
- L105 _private prototype_ `void OnFilterTextChanged(const FText& SearchText);`
- L106 _private member_ `TSharedPtr<FTextFilterExpressionEvaluator> TextFilter;`
- L107 _private member_ `FRetargetHierarchyFilterOptions FilterOptions;`
- L110 _private prototype_ `void RefreshTreeView(bool IsInitialSetup=false);` — tree view callbacks
- L111 _private prototype_ `void HandleGetChildrenForTree(TSharedPtr<FIKRetargetHierarchyElement> InElement, TArray<TSharedPtr<FIKRetargetHierarchyElement>>& OutChildren);`
- L112 _private prototype_ `void OnSelectionChanged(TSharedPtr<FIKRetargetHierarchyElement> Selection, ESelectInfo::Type SelectInfo);`
- L113 _private prototype_ `void OnItemDoubleClicked(TSharedPtr<FIKRetargetHierarchyElement> InElement);`
- L114 _private prototype_ `void OnSetExpansionRecursive(TSharedPtr<FIKRetargetHierarchyElement> InElement, bool bShouldBeExpanded);`
- L115 _private prototype_ `void SetExpansionRecursive(TSharedPtr<FIKRetargetHierarchyElement> InElement, bool bTowardsParent, bool bShouldBeExpanded);`

#### Free symbols / members of external scopes

- L73 _typedef_ `typedef SBaseHierarchyTreeView<FIKRetargetHierarchyElement> SIKRetargetHierarchyTreeView;`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/SIKRetargetOverrideManager.h` (Public)


#### class `FIKRetargetOverrideSetElement`  
`class FIKRetargetOverrideSetElement : public TSharedFromThis<FIKRetargetOverrideSetElement>`  
_L18-39_
- inherits: `TSharedFromThis<FIKRetargetOverrideSetElement>`
- desc: Tree element representing a single override set in the hierarchy
- L22 _public prototype_ `FIKRetargetOverrideSetElement( const FName& InName, const TSharedRef<FIKRetargetEditorController>& InEditorController);`
- L26 _public member_ `FText Key;`
- L27 _public member_ `TWeakPtr<FIKRetargetOverrideSetElement> Parent;`
- L28 _public member_ `TArray<TWeakPtr<FIKRetargetOverrideSetElement>> Children;`
- L29 _public member_ `TWeakPtr<SIKRetargetOverrideManager> OverrideManager;`
- L30 _public member_ `FName Name;`
- L31 _public member_ `bool bIsHidden = false;`
- L33 _public prototype_ `FText GetNumOpsLabel() const;`
- L34 _public prototype_ `FText GetNumOverridesLabel() const;`
- L38 _private member_ `TWeakPtr<FIKRetargetEditorController> EditorController;`

#### class `SIKRetargetOverrideSetRow`  
`class SIKRetargetOverrideSetRow : public SMultiColumnTableRow<TSharedPtr<FIKRetargetOverrideSetElement>>`  
_L42-75_
- inherits: `SMultiColumnTableRow<TSharedPtr<FIKRetargetOverrideSetElement>>`
- desc: Row widget for the override set tree view
- L47 _public function_ `SLATE_BEGIN_ARGS(SIKRetargetOverrideSetRow)`
- L48 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FIKRetargetEditorController>, EditorController) SLATE_ARGUMENT(TSharedPtr<FIKRetargetOverrideSetElement>, TreeElement) SLATE_ARGUMENT(TSharedPtr<SIKRetargetOverrideManager>, OverrideManager) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable);`
- L56 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;` — Overridden from SMultiColumnTableRow. Generates a widget for this column of the tree view.
- L59 _public prototype_ `void OnRequestRename();` — Requests that the inline text block enters edit mode
- L63 _private prototype_ `FText GetItemText() const;`
- L64 _private prototype_ `bool OnVerifyTextChanged(const FText& InText, FText& OutErrorMessage);`
- L65 _private prototype_ `void OnTextCommitted(const FText& InText, ETextCommit::Type CommitInfo);`
- L67 _private prototype_ `ECheckBoxState IsOverrideSetActive() const;`
- L68 _private prototype_ `void OnOverrideSetActiveChanged(ECheckBoxState NewState) const;`
- L70 _private member_ `TSharedPtr<STableViewBase> OwnerTable;`
- L71 _private member_ `TWeakPtr<FIKRetargetOverrideSetElement> WeakTreeElement;`
- L72 _private member_ `TWeakPtr<FIKRetargetEditorController> EditorController;`
- L73 _private member_ `TWeakPtr<SIKRetargetOverrideManager> OverrideManager;`
- L74 _private member_ `TSharedPtr<SInlineEditableTextBlock> InlineTextBlock;`

#### class `FRetargetOverrideSetDragDropOp`  
`class FRetargetOverrideSetDragDropOp : public FDecoratedDragDropOp`  
_L78-89_
- inherits: `FDecoratedDragDropOp`
- desc: Drag and drop operation for re-parenting override sets in the tree
- L82 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FRetargetOverrideSetDragDropOp, FDecoratedDragDropOp) static TSharedRef<FRetargetOverrideSetDragDropOp> New(TWeakPtr<FIKRetargetOverrideSetElement> InElement);`
- L86 _public prototype_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;`
- L88 _public member_ `TWeakPtr<FIKRetargetOverrideSetElement> Element;`

#### struct `FRetargetOverrideSetFilterOptions`  
`struct FRetargetOverrideSetFilterOptions`  
_L91-95_
- L93 _public prototype_ `FRetargetOverrideSetFilterOptions() = default;`
- L94 _public member_ `bool bHideEmptySets = false;`

#### class `SIKRetargetOverrideManager`  
`class SIKRetargetOverrideManager : public SCompoundWidget, public FEditorUndoClient`  
_L100-166_
- inherits: `SCompoundWidget,FEditorUndoClient`
- desc: Widget for managing and hierarchy of retarget override sets
- L103 _public function_ `SLATE_BEGIN_ARGS(SIKRetargetOverrideManager)`
- L104 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FIKRetargetEditorController> InEditorController);`
- L109 _public prototype_ `FName GetSelectedOverrideSetName() const;` — Gets the name of the override set currently selected in the tree
- L114 _private member_ `TWeakPtr<FIKRetargetEditorController> EditorController;` — centralized editor controls (facilitate cross-communication between multiple UI elements)
- L117 _private member_ `TSharedPtr<IDetailsView> DetailsView;` — the details view for editing selected override set properties
- L120 _private member_ `TSharedPtr<SIKRetargetOverrideSetTreeView> TreeView;` — tree view widget
- L121 _private member_ `TArray<TSharedPtr<FIKRetargetOverrideSetElement>> RootElements;`
- L122 _private member_ `TArray<TSharedPtr<FIKRetargetOverrideSetElement>> AllElements;`
- L125 _private prototype_ `void OnFilterTextChanged(const FText& SearchText);` — filtering the tree with search box
- L126 _private member_ `TSharedPtr<FTextFilterExpressionEvaluator> TextFilter;`
- L127 _private member_ `FRetargetOverrideSetFilterOptions FilterOptions;`
- L130 _private prototype_ `void RefreshTreeView(bool IsInitialSetup=false);` — tree view callbacks
- L131 _private prototype_ `void HandleGetChildrenForTree(TSharedPtr<FIKRetargetOverrideSetElement> InElement, TArray<TSharedPtr<FIKRetargetOverrideSetElement>>& OutChildren);`
- L132 _private prototype_ `void OnSelectionChanged(TSharedPtr<FIKRetargetOverrideSetElement> Selection, ESelectInfo::Type SelectInfo);`
- L133 _private prototype_ `void OnItemDoubleClicked(TSharedPtr<FIKRetargetOverrideSetElement> InElement);`
- L134 _private prototype_ `void OnSetExpansionRecursive(TSharedPtr<FIKRetargetOverrideSetElement> InElement, bool bShouldBeExpanded);`
- L135 _private prototype_ `void SetExpansionRecursive(TSharedPtr<FIKRetargetOverrideSetElement> InElement, bool bTowardsParent, bool bShouldBeExpanded);`
- L136 _private prototype_ `TSharedPtr<SWidget> OnGenerateContextMenu();`
- L140 _private prototype_ `FReply OnDragDetected( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — drag and drop operations
- L143 _private prototype_ `TOptional<EItemDropZone> OnCanAcceptDrop( const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<FIKRetargetOverrideSetElement> TargetElement);`
- L147 _private prototype_ `FReply OnAcceptDrop( const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<FIKRetargetOverrideSetElement> TargetElement);`
- L154 _private prototype_ `void BindCommands();` — keyboard shortcuts
- L155 _private prototype_ `void DeleteSelectedOverrideSet();`
- L156 _private prototype_ `void RenameSelectedOverrideSet();`
- L157 _private prototype_ `bool HasSelectedOverrideSet() const;`
- L158 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L161 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;`

#### Free symbols / members of external scopes

- L97 _typedef_ `typedef SBaseHierarchyTreeView<FIKRetargetOverrideSetElement> SIKRetargetOverrideSetTreeView;`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/SIKRetargetPoseEditor.h` (Public)


#### class `SIKRetargetPoseEditor`  
`class SIKRetargetPoseEditor : public SCompoundWidget`  
_L12-36_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SIKRetargetPoseEditor)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FIKRetargetEditorController> InEditorController);`
- L22 _public prototype_ `void RefreshPoseNames();`
- L26 _private member_ `TSharedPtr<SVerticalBox> Contents;`
- L28 _private prototype_ `TSharedRef<SWidget> MakeToolbar(TSharedPtr<FUICommandList> Commands);`
- L29 _private prototype_ `TSharedRef<SWidget> GenerateResetMenuContent(TSharedPtr<FUICommandList> Commands);`
- L30 _private prototype_ `TSharedRef<SWidget> GenerateEditMenuContent(TSharedPtr<FUICommandList> Commands);`
- L31 _private prototype_ `TSharedRef<SWidget> GenerateNewMenuContent(TSharedPtr<FUICommandList> Commands);`
- L32 _private prototype_ `TObjectPtr<UIKRetargeterController> GetAssetControllerFromSelectedObjects(IDetailLayoutBuilder& DetailBuilder) const;`
- L34 _private member_ `TWeakPtr<FIKRetargetEditorController> EditorController;`
- L35 _private member_ `TArray<TSharedPtr<FName>> PoseNames;`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/SIKRetargetVariablesEditor.h` (Public)


#### struct `FVariableRow`  
`struct FVariableRow`  
_L15-18_
- L17 _public member_ `FName PropertyName;`

#### class `SIKRetargetVariablesEditor`  
`class SIKRetargetVariablesEditor : public SCompoundWidget, public FNotifyHook`  
_L20-45_
- inherits: `SCompoundWidget,FNotifyHook`
- L23 _public function_ `SLATE_BEGIN_ARGS(SIKRetargetVariablesEditor)`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FIKRetargetEditorController> InEditorController);`
- L29 _public prototype_ `virtual void NotifyPreChange(FProperty* PropertyAboutToChange) override;` — FNotifyHook Interface
- L30 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;`
- L33 _public prototype_ `void RefreshList();`
- L37 _private prototype_ `UIKRetargeter* GetAsset() const;`
- L38 _private prototype_ `TSharedRef<ITableRow> OnGenerateVariableRow(TSharedPtr<FVariableRow> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L39 _private prototype_ `TSharedRef<SWidget> MakeTypeSelectorForVariable(TSharedPtr<FVariableRow> InRow) const;`
- L40 _private prototype_ `TSharedRef<SWidget> MakeValueWidgetForVariable(TSharedPtr<FVariableRow> InRow);`
- L42 _private member_ `TArray<TSharedPtr<FVariableRow>> VariableRows;`
- L43 _private member_ `TSharedPtr<SListView<TSharedPtr<FVariableRow>>> VariablesListView;`
- L44 _private member_ `TWeakPtr<FIKRetargetEditorController> EditorController;`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/SRetargetAnimAssetsWindow.h` (Public)


#### class `SBatchExportPathDialog`  
`class SBatchExportPathDialog: public SWindow`  
_L23-60_
- inherits: `SWindow`
- desc: dialog to select path to export to
- L28 _public function_ `SLATE_BEGIN_ARGS(SBatchExportPathDialog)`
- L29 _public function_ `SLATE_ARGUMENT(FIKRetargetBatchOperationContext*, BatchContext) SLATE_ARGUMENT(bool, ExportRetargetAssets) SLATE_END_ARGS() SBatchExportPathDialog() : UserResponse(EAppReturnType::Cancel)`
- L35 _public prototype_ `void Construct(const FArguments& InArgs);`
- L38 _public prototype_ `EAppReturnType::Type ShowModal();` — displays the dialog in a blocking fashion
- L42 _private prototype_ `FReply OnButtonClick(EAppReturnType::Type ButtonID);`
- L45 _private prototype_ `void UpdateExampleText();` — example rename text
- L48 _private prototype_ `FText GetFolderPath() const;` — modify folder output path
- L51 _private prototype_ `static FString ConvertToCleanString(const FText& ToClean);` — remove characters not allowed in asset names
- L53 _private member_ `FText ExampleText;` — The rename rule sample text
- L54 _private member_ `EAppReturnType::Type UserResponse;`
- L57 _private member_ `FIKRetargetBatchOperationContext* BatchContext;` — the context/data-model we are editing with this pop-up window
- L59 _private member_ `bool bExportingRetargetAssets;`

#### class `UBatchExportOptions`  
`class UBatchExportOptions : public UObject`  
_L64-94_
- reflection: `UCLASS(Blueprintable, config=EditorPerProjectUserSettings, Category = "BatchExportOptions")`
- inherits: `UObject`
- desc: settings object used in details view of the batch retarget window
- L71 _public prototype_ `static UBatchExportOptions* GetInstance();` — singleton class
- L76 _public member_ `bool bOverwriteExistingFiles = false;` — `UPROPERTY(EditAnywhere, Config, Config, Category = "File")` — Any files with the same name will be overwritten instead of creating a new file with a numeric suffix. This is useful when iterating on a batch process.
- L80 _public member_ `bool bIncludeReferencedAssets = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = "File")` — Duplicates and retargets any animation assets referenced by the input assets. For example, sequences in an animation blueprint or blendspace.
- L85 _public member_ `bool bRetainAdditiveFlags = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = "File")` — If retargeting additive animations, they will have their additive settings reset so that the retargeter evaluates the motion in a non-additive way. Setting this flag to true will ensure that the resulting animation sequences will retain their additive settings after the retarget operation.
- L93 _private member_ `static UBatchExportOptions* SingletonInstance;`

#### class `SBatchExportOptionsDialog`  
`class SBatchExportOptionsDialog: public SWindow`  
_L97-116_
- inherits: `SWindow`
- desc: dialog to select batch export options
- L102 _public function_ `SLATE_BEGIN_ARGS(SBatchExportOptionsDialog)`
- L103 _public prototype_ `SLATE_ARGUMENT(FIKRetargetBatchOperationContext*, BatchContext) SLATE_END_ARGS() SBatchExportOptionsDialog();`
- L107 _public prototype_ `void Construct(const FArguments& InArgs);`
- L108 _public prototype_ `EAppReturnType::Type ShowModal();`
- L112 _protected prototype_ `FReply OnButtonClick(EAppReturnType::Type ButtonID);`
- L114 _protected member_ `FIKRetargetBatchOperationContext* BatchContext;`
- L115 _protected member_ `EAppReturnType::Type UserResponse;`

#### class `SRetargetPoseViewport`  
`class SRetargetPoseViewport: public SEditorViewport`  
_L119-158_
- inherits: `SEditorViewport`
- desc: viewport in retarget dialog that previews results of retargeting before exporting animations
- L124 _public function_ `SLATE_BEGIN_ARGS(SRetargetPoseViewport)`
- L126 _public function_ `SLATE_ARGUMENT(FIKRetargetBatchOperationContext*, BatchContext) SLATE_END_ARGS() SRetargetPoseViewport() : PreviewScene(FPreviewScene::ConstructionValues())`
- L131 _public prototype_ `void Construct(const FArguments& InArgs);`
- L133 _public prototype_ `void SetSkeletalMesh(USkeletalMesh* InSkeletalMesh, ERetargetSourceOrTarget SourceOrTarget);`
- L134 _public prototype_ `void SetRetargetAsset(UIKRetargeter* RetargetAsset);`
- L135 _public prototype_ `void SetOverrideSets(const TArray<FName>& InOverrideSets);`
- L136 _public prototype_ `void PlayAnimation(UAnimationAsset* AnimationAsset);`
- L137 _public prototype_ `bool IsRetargeterValid();`
- L142 _protected prototype_ `virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;` — SEditorViewport interface
- L147 _private member_ `UAnimationAsset* AnimThatWasPlaying;`
- L148 _private member_ `float TimeWhenPaused;`
- L150 _private member_ `FPreviewScene PreviewScene;`
- L151 _private member_ `TObjectPtr<UDebugSkelMeshComponent> SourceComponent;`
- L152 _private member_ `TObjectPtr<UDebugSkelMeshComponent> TargetComponent;`
- L153 _private member_ `TObjectPtr<UIKRetargetAnimInstance> SourceAnimInstance;`
- L154 _private member_ `TObjectPtr<UIKRetargetAnimInstance> TargetAnimInstance;`
- L157 _private member_ `FIKRetargetBatchOperationContext* BatchContext;` — the data model

#### struct `FProceduralRetargetAssets`  
`struct FProceduralRetargetAssets : FGCObject`  
_L162-187_
- inherits: `FGCObject`
- desc: a container for procedurally generated retarget assets (used in memory and discarded after batch retarget operation) can optionally be saved to disk as well
- L164 _public prototype_ `FProceduralRetargetAssets();`
- L167 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L168 _public function_ `virtual FString GetReferencerName() const override`
- L171 _public prototype_ `void AutoGenerateIKRigAsset(USkeletalMesh* Mesh, ERetargetSourceOrTarget SourceOrTarget);`
- L172 _public prototype_ `void AutoGenerateIKRetargetAsset();`
- L175 _public member_ `TObjectPtr<UIKRigDefinition> SourceIKRig;` — resulting assets used to retarget animation, or export to disk
- L176 _public member_ `TObjectPtr<UIKRigDefinition> TargetIKRig;`
- L177 _public member_ `TObjectPtr<UIKRetargeter> Retargeter;`
- L180 _public member_ `FAutoCharacterizeResults SourceCharacterizationResults;` — results of characterizing for error reporting
- L181 _public member_ `FAutoCharacterizeResults TargetCharacterizationResults;`
- L182 _public member_ `FAutoFBIKResults SourceIKResults;`
- L183 _public member_ `FAutoFBIKResults TargetIKResults;`
- L186 _private prototype_ `void CreateNewRetargetAsset();`

#### class `FRetargetPoseViewportClient`  
`class FRetargetPoseViewportClient: public FEditorViewportClient`  
_L190-203_
- inherits: `FEditorViewportClient`
- desc: client for SRetargetPoseViewport
- L195 _public prototype_ `FRetargetPoseViewportClient(FPreviewScene& InPreviewScene, const TSharedRef<SRetargetPoseViewport>& InRetargetPoseViewport);`
- L198 _public prototype_ `virtual void Tick(float DeltaTime) override;` — FEditorViewportClient interface
- L199 _public function_ `virtual FSceneInterface* GetScene() const override`
- L200 _public function_ `virtual FLinearColor GetBackgroundColor() const override`
- L201 _public function_ `virtual void SetViewMode(EViewModeIndex Index) override final`

#### class `UBatchRetargetSettings`  
`class UBatchRetargetSettings : public UObject`  
_L207-246_
- reflection: `UCLASS(Blueprintable, Category = "BatchRetargetSettings")`
- inherits: `UObject`
- desc: settings object used in details view of the batch retarget window
- L214 _public prototype_ `static UBatchRetargetSettings* GetInstance();` — singleton class
- L218 _public member_ `TObjectPtr<USkeletalMesh> SourceSkeletalMesh;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Source")` — The skeletal mesh with the proportions you want to copy animation FROM.
- L222 _public member_ `TObjectPtr<USkeletalMesh> TargetSkeletalMesh;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target")` — The skeletal mesh with the proportions you want to copy animation TO.
- L230 _public member_ `bool bAutoGenerateRetargeter = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Retargeter")` — When true, the system will attempt to generate an IK Retargeter compatible with the supplied source and target skeletal meshes. If the skeletons are successfully characterized, it will align the retarget poses automatically. Automatic retargeting is currently limited to common, predefined skeleton types that Unreal knows about (see documentation for full list). If you attempt to use a skeletal mesh that is not compatible with a predefined template, warnings will be displayed in the output log and the export button will be disabled. In that case, you must supply a custom retargeter asset.
- L234 _public member_ `TObjectPtr<UIKRetargeter> RetargetAsset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Retargeter", meta = (EditCondition = "!bAutoGenerateRetargeter"))` — You may also supply a custom IK Retargeter if needed.
- L239 _public member_ `FName OverrideSetToApply;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Retargeter", meta = (EditCondition = "!bAutoGenerateRetargeter", GetOptions = "GetOverrideSetOptions"))` — Override set from the retargeter to apply during preview and export. Only available when using a manually supplied retargeter asset.
- L242 _public prototype_ `TArray<FString> GetOverrideSetOptions() const;` — `UFUNCTION()`
- L245 _private member_ `static UBatchRetargetSettings* SingletonInstance;`

#### class `SRetargetExporterAssetBrowser`  
`class SRetargetExporterAssetBrowser : public SBox`  
_L249-268_
- inherits: `SBox`
- desc: asset browser for user to select animation assets to duplicate/retarget
- L252 _public function_ `SLATE_BEGIN_ARGS(SRetargetExporterAssetBrowser)`
- L253 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<SRetargetAnimAssetsWindow> RetargetWindow);`
- L256 _public prototype_ `void RefreshView();`
- L257 _public prototype_ `void GetSelectedAssets(TArray<FAssetData>& OutSelectedAssets) const;`
- L258 _public prototype_ `bool AreAnyAssetsSelected() const;`
- L262 _private prototype_ `void OnAssetDoubleClicked(const FAssetData& AssetData);`
- L263 _private prototype_ `bool OnShouldFilterAsset(const struct FAssetData& AssetData);`
- L265 _private member_ `FGetCurrentSelectionDelegate GetCurrentSelectionDelegate;`
- L266 _private member_ `TSharedPtr<SRetargetAnimAssetsWindow> RetargetWindow;`
- L267 _private member_ `TSharedPtr<SBox> AssetBrowserBox;`

#### enum `EBatchRetargetUIState`  
`enum class EBatchRetargetUIState`  
_L270-277_
- L272 _public enumerator_ `MISSING_MESH`
- L273 _public enumerator_ `AUTO_RETARGET_INVALID`
- L274 _public enumerator_ `MANUAL_RETARGET_INVALID`
- L275 _public enumerator_ `NO_ANIMATIONS_SELECTED`
- L276 _public enumerator_ `READY_TO_EXPORT`

#### class `SRetargetAnimAssetsWindow`  
`class SRetargetAnimAssetsWindow : public SCompoundWidget, FGCObject`  
_L280-346_
- inherits: `SCompoundWidget,FGCObject`
- desc: window to display when configuring batch duplicate & retarget process
- L285 _public prototype_ `SRetargetAnimAssetsWindow();`
- L287 _public function_ `SLATE_BEGIN_ARGS(SRetargetAnimAssetsWindow) : _CurrentSkeletalMesh(nullptr) , _WidgetWindow(nullptr) , _ShowRemapOption(false)`
- L293 _public prototype_ `SLATE_ARGUMENT(USkeletalMesh*, CurrentSkeletalMesh) SLATE_ARGUMENT(TSharedPtr<SWindow>, WidgetWindow) SLATE_ARGUMENT(bool, ShowRemapOption) SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L301 _public function_ `virtual FString GetReferencerName() const override` — FGCObject
- L302 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L305 _public function_ `TObjectPtr<UBatchRetargetSettings> GetSettings()`
- L306 _public function_ `TSharedPtr<SRetargetPoseViewport> GetViewport()`
- L310 _private prototype_ `void SetAssets(USkeletalMesh* SourceMesh, USkeletalMesh* TargetMesh, UIKRetargeter* Retargeter);`
- L311 _private prototype_ `void ShowAssetWarnings();`
- L313 _private prototype_ `void OnFinishedChangingSelectionProperties(const FPropertyChangedEvent& PropertyChangedEvent);`
- L316 _private prototype_ `bool CanExportAnimations() const;` — export button states
- L317 _private prototype_ `FReply OnExportAnimations();`
- L318 _private prototype_ `bool CanExportRetargetAssets() const;`
- L319 _private prototype_ `FReply OnExportRetargetAssets();`
- L322 _private prototype_ `EBatchRetargetUIState GetCurrentState() const;` — output current status to the message area
- L323 _private prototype_ `EVisibility GetWarningVisibility() const;`
- L324 _private prototype_ `FText GetWarningText() const;`
- L327 _private member_ `FIKRetargetBatchOperationContext BatchContext;` — necessary data collected from UI to run retarget.
- L329 _private prototype_ `void ApplyOverrideSetToPreview();`
- L332 _private member_ `TSharedPtr<SRetargetPoseViewport> Viewport;` — ui elements
- L333 _private member_ `TSharedPtr<SRetargetExporterAssetBrowser> AssetBrowser;`
- L334 _private member_ `TSharedPtr<SIKRigOutputLog> LogView;`
- L335 _private member_ `FIKRigLogger Log;`
- L336 _private member_ `TObjectPtr<UBatchRetargetSettings> Settings;`
- L337 _private member_ `FProceduralRetargetAssets ProceduralAssets;`
- L341 _public prototype_ `static void ShowWindow(TArray<UObject*> InAnimAssets);`
- L342 _public member_ `static TSharedPtr<SWindow> Window;`
- L344 _public member_ `static const FName LogName;`
- L345 _public member_ `static const FText LogLabel;`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RetargetEditor/SRetargetOpStack.h` (Public)


#### class `FRetargetOpStackElement`  
`class FRetargetOpStackElement`  
_L22-78_
- desc: SListView item-type for a single retarget op
- L26 _public prototype_ `static TSharedRef<ITableRow> MakeListRowWidget( const TSharedRef<STableViewBase>& InOwnerTable, TSharedRef<FRetargetOpStackElement> InStackElement, TSharedPtr<SRetargetOpList> InOpListWidget);`
- L31 _public function_ `static TSharedRef<FRetargetOpStackElement> Make( const int32 InOpIndex, const bool InCanHaveChildren, const TSharedPtr<SRetargetOpList>& InOpListWidget)`
- L40 _public prototype_ `FName GetName() const;`
- L42 _public prototype_ `const UScriptStruct* GetType() const;`
- L44 _public function_ `int32 GetIndexInStack() const`
- L46 _public function_ `bool GetCanHaveChildren() const`
- L48 _public function_ `const TArray<FRetargetOpStackElement*>& GetChildren() const`
- L50 _public function_ `void AddChild(FRetargetOpStackElement* InChild)`
- L52 _public function_ `const FRetargetOpStackElement* GetParent() const`
- L54 _public function_ `void SetParent(FRetargetOpStackElement* InParentElement)`
- L56 _public function_ `TWeakPtr<SRetargetOpList> GetOpList() const`
- L58 _public prototype_ `DECLARE_DELEGATE(FOnRenameRequested);`
- L59 _public member_ `FOnRenameRequested OnRenameRequested;`
- L63 _private member_ `int32 IndexInStack = INDEX_NONE;`
- L64 _private member_ `bool bCanHaveChildren = false;`
- L65 _private member_ `TArray<FRetargetOpStackElement*> ChildElements;`
- L66 _private member_ `FRetargetOpStackElement* ParentElement = nullptr;`
- L67 _private member_ `TWeakPtr<SRetargetOpList> OpListWidget;`
- L70 _private prototype_ `FRetargetOpStackElement() = default;` — hidden constructors, always use Make above
- L71 _private function_ `FRetargetOpStackElement( const int32 InIndexInStack, const bool InHasChildren, const TSharedPtr<SRetargetOpList>& InOpListWidget) : IndexInStack(InIndexInStack), bCanHaveChildren(InHasChildren), OpListWidget(InOpListWidget)`

#### struct `FIKRetargetOpMetaData`  
`struct FIKRetargetOpMetaData`  
_L82-88_
- desc: meta data about an op type used to create filtered menus for creating ops with compatible child types in parent-op menus
- L84 _public member_ `FName NiceName;`
- L85 _public member_ `const UScriptStruct* OpType = nullptr;`
- L86 _public member_ `const UScriptStruct* ParentType = nullptr;`
- L87 _public member_ `bool bIsSingleton = false;`

#### class `SRetargetOpList`  
`class SRetargetOpList : public SListView<TSharedPtr<FRetargetOpStackElement>>`  
_L96-166_
- inherits: `SListView<TSharedPtr<FRetargetOpStackElement>>`
- desc: an SListView customized for retarget ops Supports: - slow double-click rename of list items - drag/drop reordering w/ nested ops - building a menu of compatible ops to add to the list - deleting ops
- L100 _public function_ `SLATE_BEGIN_ARGS(SRetargetOpList)`
- L101 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<FIKRetargetEditorController>, InEditorController) SLATE_ARGUMENT(TWeakPtr<FRetargetOpStackElement>, InParentElement) SLATE_END_ARGS() virtual ~SRetargetOpList() = default;`
- L107 _public prototype_ `void Construct(const FArguments& InArgs);`
- L109 _public prototype_ `TSharedRef<ITableRow> MakeListRowWidget(TSharedPtr<FRetargetOpStackElement> InElement, const TSharedRef<STableViewBase>& OwnerTable);`
- L111 _public prototype_ `bool IsEnabled() const;`
- L114 _public prototype_ `FReply OnDragDetected( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — drag and drop operations
- L117 _public prototype_ `TOptional<EItemDropZone> OnCanAcceptDrop( const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<FRetargetOpStackElement> TargetElement);`
- L121 _public prototype_ `FReply OnAcceptDrop( const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<FRetargetOpStackElement> TargetElement);`
- L128 _public prototype_ `virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override;` — slow-click renaming
- L129 _public prototype_ `void OnSelectionChanged(TSharedPtr<FRetargetOpStackElement> InItem, ESelectInfo::Type SelectInfo) const;`
- L130 _public prototype_ `void OnItemClicked(TSharedPtr<FRetargetOpStackElement> InItem);`
- L131 _public prototype_ `void RequestRenameSelectedOp() const;`
- L135 _public prototype_ `TSharedRef<SWidget> CreateAddNewOpMenu();` — add new op menu
- L137 _public prototype_ `void AddNewRetargetOp(const UScriptStruct* ScriptStruct);` — menu command callback for adding a new op
- L141 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);` — delete op from stack
- L142 _public prototype_ `void DeleteRetargetOp(TSharedPtr<FRetargetOpStackElement> OpToDelete);`
- L145 _public prototype_ `void RefreshAndRestore();` — must be called after refresh
- L148 _public member_ `TArray< TSharedPtr<FRetargetOpStackElement> > Elements;` — the elements contained in this list
- L151 _public member_ `TWeakPtr<FIKRetargetEditorController> EditorController;` — editor controller
- L155 _public member_ `TWeakPtr<FRetargetOpStackElement> ParentElement;` — the type of op that is the parent of this list of ops if this is null, then it's assumed to be the top-level op stack
- L160 _private member_ `uint32 LastClickCycles = 0;` — slow double-click rename state
- L161 _private member_ `TWeakPtr<FRetargetOpStackElement> LastSelectedElement;`
- L164 _private member_ `TArray<FIKRetargetOpMetaData> AllOpsMetaData;` — a map of op types to the parent op type (cached at startup)
- L165 _private prototype_ `void CacheOpTypeMetaData();`

#### class `SRetargetOpItem`  
`class SRetargetOpItem : public SCompoundWidget`  
_L169-202_
- inherits: `SCompoundWidget`
- desc: builds an UI element representing a single op
- L172 _public function_ `SLATE_BEGIN_ARGS(SRetargetOpItem)`
- L173 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<SRetargetOpList>, InOpListWidget) SLATE_ARGUMENT(TWeakPtr<FRetargetOpStackElement>, InStackElement) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L180 _public prototype_ `void OnNameCommitted(const FText& InText, ETextCommit::Type InCommitType) const;` — RENAMING op
- L181 _public prototype_ `FText GetName() const;`
- L184 _public prototype_ `void GenerateRightClickMenu(FMenuBuilder& InMenuBuilder);`
- L186 _public member_ `static float OpHorizontalPadding;`
- L187 _public member_ `static float OpVerticalPadding;`
- L191 _private prototype_ `FIKRetargetEditorController* GetEditorController() const;`
- L193 _private prototype_ `void MakeOverrideSubMenu(FMenuBuilder& SubMenuBuilder, TSharedPtr<FRetargetPropertyOverrideNode> Node);`
- L195 _private prototype_ `bool IsOpEnabled() const;`
- L197 _private prototype_ `FIKRetargetOpBase* GetRetargetOp() const;`
- L199 _private member_ `TWeakPtr<SRetargetOpList> ListView;`
- L200 _private member_ `TWeakPtr<FRetargetOpStackElement> Element;`
- L201 _private member_ `TSharedPtr<SInlineEditableTextBlock> EditNameWidget;`

#### class `SParentRetargetOpItem`  
`class SParentRetargetOpItem : public STableRow<TSharedPtr<FRetargetOpStackElement>>`  
_L206-224_
- inherits: `STableRow<TSharedPtr<FRetargetOpStackElement>>`
- desc: an SRetargetOpList item representing a single op with children op beneath it (contains an SRetgargetOpList to house children ops)
- L210 _public function_ `SLATE_BEGIN_ARGS(SParentRetargetOpItem)`
- L211 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<FRetargetOpStackElement>, InStackElement) SLATE_ARGUMENT(TWeakPtr<SRetargetOpList>, InOpListWidget) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable);`
- L217 _public prototype_ `void RefreshListView() const;`
- L221 _private member_ `TWeakPtr<FRetargetOpStackElement> ParentStackElement;`
- L222 _private member_ `TWeakPtr<SRetargetOpList> OpListWidget;`
- L223 _private member_ `TSharedPtr<SRetargetOpList> ChildrenListView;`

#### class `SRetargetOpSingleItem`  
`class SRetargetOpSingleItem : public STableRow<TSharedPtr<FRetargetOpStackElement>>`  
_L227-248_
- inherits: `STableRow<TSharedPtr<FRetargetOpStackElement>>`
- desc: an SRetargetOpList item representing a single op with no children
- L231 _public function_ `SLATE_BEGIN_ARGS(SRetargetOpSingleItem)`
- L232 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<FRetargetOpStackElement>, InStackElement) SLATE_ARGUMENT(TWeakPtr<SRetargetOpList>, InOpListWidget) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable);`
- L238 _public prototype_ `bool GetWarningMessage(FText& Message) const;`
- L240 _public prototype_ `bool IsOpEnabled() const;`
- L244 _private prototype_ `FIKRetargetOpBase* GetRetargetOp() const;`
- L246 _private member_ `TWeakPtr<FRetargetOpStackElement> StackElement;`
- L247 _private member_ `TWeakPtr<SRetargetOpList> OpListWidget;`

#### class `FRetargetOpStackDragDropOp`  
`class FRetargetOpStackDragDropOp : public FDecoratedDragDropOp`  
_L250-266_
- inherits: `FDecoratedDragDropOp`
- L254 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FRetargetOpStackDragDropOp, FDecoratedDragDropOp) static TSharedRef<FRetargetOpStackDragDropOp> New(TWeakPtr<FRetargetOpStackElement> InElement);`
- L258 _public prototype_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;`
- L260 _public prototype_ `static int32 GetIndexToMoveTo( const TSharedPtr<FRetargetOpStackElement>& InDraggedElement, const TSharedPtr<FRetargetOpStackElement>& InTargetElement, const EItemDropZone InDropZone);`
- L265 _public member_ `TWeakPtr<FRetargetOpStackElement> Element;`

#### class `SRetargetOpStack`  
`class SRetargetOpStack : public SCompoundWidget, public FEditorUndoClient`  
_L270-286_
- inherits: `SCompoundWidget,FEditorUndoClient`
- desc: top level view of a stack of ik retargeter ops shows the main menu for adding ops to the retargeting stack, and a list view of top-level ops
- L274 _public function_ `SLATE_BEGIN_ARGS(SRetargetOpStack)`
- L275 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<FIKRetargetEditorController>, InEditorController) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakPtr<FIKRetargetEditorController>& InEditorController);`
- L280 _public prototype_ `void RefreshStackView() const;`
- L284 _private member_ `TWeakPtr<FIKRetargetEditorController> EditorController;`
- L285 _private member_ `TSharedPtr<SRetargetOpList> ListView;`

#### Free symbols / members of external scopes

- L58 _delegate_ `DECLARE_DELEGATE(FOnRenameRequested);`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RigEditor/AssetTypeActions_IKRigDefinition.h` (Public)


#### class `FAssetTypeActions_IKRigDefinition`  
`class FAssetTypeActions_IKRigDefinition : public FAssetTypeActions_Base`  
_L9-24_
- inherits: `FAssetTypeActions_Base`
- L13 _public function_ `virtual FText GetName() const override` — IAssetTypeActions Implementation
- L14 _public function_ `virtual FColor GetTypeColor() const override`
- L15 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L16 _public prototype_ `virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;`
- L17 _public function_ `virtual uint32 GetCategories() override`
- L18 _public prototype_ `virtual const TArray<FText>& GetSubMenus() const override;`
- L19 _public prototype_ `virtual UThumbnailInfo* GetThumbnailInfo(UObject* Asset) const override;`
- L22 _public prototype_ `static void ExtendSkeletalMeshMenuToMakeIKRig();`
- L23 _public prototype_ `static void CreateNewIKRigFromSkeletalMesh(UObject* InSelectedObject);`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RigEditor/IKRigAnimInstance.h` (Public)


#### class `UIKRigAnimInstance`  
`class UIKRigAnimInstance : public UAnimPreviewInstance`  
_L14-31_
- reflection: `UCLASS(transient, NotBlueprintType, NotBlueprintable)`
- inherits: `UAnimPreviewInstance`
- L20 _public prototype_ `void SetIKRigAsset(UIKRigDefinition* IKRigAsset);`
- L22 _public prototype_ `void SetProcessorNeedsInitialized();`
- L24 _public prototype_ `FIKRigProcessor* GetCurrentlyRunningProcessor();`
- L27 _protected prototype_ `virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override;`
- L30 _protected member_ `FAnimNode_IKRig IKRigNode;` — `UPROPERTY(Transient)`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RigEditor/IKRigAnimInstanceProxy.h` (Public)


#### struct `FIKRigAnimInstanceProxy`  
`struct FIKRigAnimInstanceProxy : public FAnimPreviewInstanceProxy`  
_L13-38_
- reflection: `USTRUCT()`
- inherits: `FAnimPreviewInstanceProxy`
- desc: Proxy override for this UAnimInstance-derived class
- L19 _public prototype_ `FIKRigAnimInstanceProxy() = default;`
- L20 _public prototype_ `FIKRigAnimInstanceProxy(UAnimInstance* InAnimInstance, FAnimNode_IKRig* IKRigNode);`
- L21 _public prototype_ `virtual ~FIKRigAnimInstanceProxy() override = default;`
- L24 _public prototype_ `virtual void Initialize(UAnimInstance* InAnimInstance) override;` — FAnimPreviewInstanceProxy interface
- L25 _public prototype_ `virtual bool Evaluate(FPoseContext& Output) override;`
- L26 _public prototype_ `virtual void UpdateAnimationNode(const FAnimationUpdateContext& InContext) override;`
- L31 _public prototype_ `virtual FAnimNode_Base* GetCustomRootNode() override;` — Called when the anim instance is being initialized. These nodes can be provided
- L32 _public prototype_ `virtual void GetCustomNodes(TArray<FAnimNode_Base*>& OutNodes) override;`
- L35 _public prototype_ `void SetIKRigAsset(UIKRigDefinition* InIKRigAsset);`
- L37 _public member_ `FAnimNode_IKRig* IKRigNode;`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RigEditor/IKRigAssetBrowserTabSummoner.h` (Public)


#### struct `FIKRigAssetBrowserTabSummoner`  
`struct FIKRigAssetBrowserTabSummoner : public FWorkflowTabFactory`  
_L10-21_
- inherits: `FWorkflowTabFactory`
- L13 _public member_ `static const FName TabID;`
- L15 _public prototype_ `FIKRigAssetBrowserTabSummoner(const TSharedRef<FIKRigEditorToolkit>& InIKRetargetEditor);`
- L16 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L17 _public prototype_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override;`
- L20 _protected member_ `TWeakPtr<FIKRigEditorToolkit> IKRigEditor;`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RigEditor/IKRigAutoCharacterizer.h` (Public)


#### enum `EPreferredAxis`  
`enum class EPreferredAxis`  
_L10-19_
- L12 _public enumerator_ `None`
- L13 _public enumerator_ `PositiveX`
- L14 _public enumerator_ `NegativeX`
- L15 _public enumerator_ `PositiveY`
- L16 _public enumerator_ `NegativeY`
- L17 _public enumerator_ `PositiveZ`
- L18 _public enumerator_ `NegativeZ`

#### struct `FCharacterizationStandard`  
`struct FCharacterizationStandard`  
_L22-155_
- desc: the central ground truth for standardized characterization labels used in Unreal
- L32 _public member_ `static const FName Spine;` — core
- L33 _public member_ `static const FName Neck;`
- L34 _public member_ `static const FName Head;`
- L35 _public member_ `static const FName Tail;`
- L37 _public member_ `static const FName LeftLeg;` — legs
- L38 _public member_ `static const FName RightLeg;`
- L40 _public member_ `static const FName LeftFoot;` — feet
- L41 _public member_ `static const FName RightFoot;`
- L43 _public member_ `static const FName LeftClavicle;` — arms
- L44 _public member_ `static const FName RightClavicle;`
- L45 _public member_ `static const FName LeftArm;`
- L46 _public member_ `static const FName RightArm;`
- L48 _public member_ `static const FName LeftThumbMetacarpal;` — left hand
- L49 _public member_ `static const FName LeftIndexMetacarpal;`
- L50 _public member_ `static const FName LeftMiddleMetacarpal;`
- L51 _public member_ `static const FName LeftRingMetacarpal;`
- L52 _public member_ `static const FName LeftPinkyMetacarpal;`
- L53 _public member_ `static const FName LeftThumb;`
- L54 _public member_ `static const FName LeftIndex;`
- L55 _public member_ `static const FName LeftMiddle;`
- L56 _public member_ `static const FName LeftRing;`
- L57 _public member_ `static const FName LeftPinky;`
- L59 _public member_ `static const FName RightThumbMetacarpal;` — right hand
- L60 _public member_ `static const FName RightIndexMetacarpal;`
- L61 _public member_ `static const FName RightMiddleMetacarpal;`
- L62 _public member_ `static const FName RightRingMetacarpal;`
- L63 _public member_ `static const FName RightPinkyMetacarpal;`
- L64 _public member_ `static const FName RightThumb;`
- L65 _public member_ `static const FName RightIndex;`
- L66 _public member_ `static const FName RightMiddle;`
- L67 _public member_ `static const FName RightRing;`
- L68 _public member_ `static const FName RightPinky;`
- L70 _public member_ `static const FName LeftBigToe;` — left foot
- L71 _public member_ `static const FName LeftIndexToe;`
- L72 _public member_ `static const FName LeftMiddleToe;`
- L73 _public member_ `static const FName LeftRingToe;`
- L74 _public member_ `static const FName LeftPinkyToe;`
- L76 _public member_ `static const FName RightBigToe;` — right foot
- L77 _public member_ `static const FName RightIndexToe;`
- L78 _public member_ `static const FName RightMiddleToe;`
- L79 _public member_ `static const FName RightRingToe;`
- L80 _public member_ `static const FName RightPinkyToe;`
- L82 _public member_ `static const FName LeftHandIKGoal;` — standard bipedal IK goal names
- L83 _public member_ `static const FName LeftFootIKGoal;`
- L84 _public member_ `static const FName RightHandIKGoal;`
- L85 _public member_ `static const FName RightFootIKGoal;`
- L88 _public member_ `static constexpr float PelvisRotationStiffness = 0.95f;` — standard bone settings for IK
- L89 _public member_ `static constexpr float ClavicleRotationStiffness = 0.95f;`
- L90 _public member_ `static constexpr float FootRotationStiffness = 0.85f;`
- L142 _public member_ `static const FName LeftLegA;` — enough extra legs to cover arachnids if you need more, just use a hard coded FName according to the convention above
- L143 _public member_ `static const FName LeftLegB;`
- L144 _public member_ `static const FName LeftLegC;`
- L145 _public member_ `static const FName RightLegA;`
- L146 _public member_ `static const FName RightLegB;`
- L147 _public member_ `static const FName RightLegC;`
- L149 _public member_ `static const FName LeftFootAIKGoal;`
- L150 _public member_ `static const FName LeftFootBIKGoal;`
- L151 _public member_ `static const FName LeftFootCIKGoal;`
- L152 _public member_ `static const FName RightFootAIKGoal;`
- L153 _public member_ `static const FName RightFootBIKGoal;`
- L154 _public member_ `static const FName RightFootCIKGoal;`

#### enum `ECleanOrFullName`  
`enum class ECleanOrFullName`  
_L159-163_
- desc: clean names are used for comparison full names are used to resolve a retarget definition onto an actual skeleton (which may have prefixes)
- L161 _public enumerator_ `Full`
- L162 _public enumerator_ `Clean`

#### struct `FAbstractHierarchy`  
`struct FAbstractHierarchy`  
_L166-242_
- desc: an abstract representation of a skeleton including just their names and hierarchy
- L168 _public prototype_ `FAbstractHierarchy(USkeletalMesh* InMesh);`
- L170 _public function_ `FAbstractHierarchy( const TArray<FName>& InBones, const TArray<int32>& InParentIndices) : FullBoneNames(InBones), ParentIndices(InParentIndices)`
- L179 _public prototype_ `int32 GetParentIndex(const FName BoneName, const ECleanOrFullName NameType) const;` — get index of parent bone
- L182 _public prototype_ `int32 GetBoneIndex(const FName BoneName, const ECleanOrFullName NameType) const;` — get the index from the name
- L185 _public prototype_ `FName GetBoneName(const int32 BoneIndex, const ECleanOrFullName NameType) const;` — get the name of a bone from it's index
- L188 _public prototype_ `bool IsChildOf(const FName Parent, const FName PotentialChild, const ECleanOrFullName NameType) const;` — returns true if PotentialChild is within the branch under Parent
- L191 _public prototype_ `void GetBonesInChain( const FName Start, const FName End, const ECleanOrFullName NameType, TArray<FName>& OutBonesInChain) const;` — outputs a list of bone names in order from root to leaf that reside between start and end (inclusive)
- L198 _public prototype_ `const TArray<FName>& GetBoneNames(const ECleanOrFullName NameType) const;` — read-only access to the full names of the bones
- L201 _public prototype_ `void GetImmediateChildren( const FName& BoneName, const ECleanOrFullName NameType, TArray<FName>& OutChildren) const;` — get a list of the immediate children of BoneName
- L209 _public prototype_ `void Compare( const FAbstractHierarchy& OtherHierarchy, TArray<FName>& OutMissingBones, TArray<FName>& OutBonesWithDifferentParent, int32& OutNumMatchingBones, float& OutPercentOfTemplateMatched) const;` — returns an integer score representing the number of bones in Other matching this OutMissingBones will contain the names of all bones in the template that were not found in the input OutBonesWithDifferentParent will contain the names of all bones in the input that have a different parent in the template
- L217 _public prototype_ `void FindBonesNotInOther( const FAbstractHierarchy& OtherHierarchy, TArray<FName>& OutMissingBones, TArray<FName>& OutBonesWithDifferentParent) const;` — return a list of all bones in this hierarchy that are NOT in OtherHierarchy
- L223 _public prototype_ `int32 GetNumMatchingBones(const FAbstractHierarchy& OtherHierarchy) const;` — return the total number of bones that are also in OtherHierarchy with the same parent
- L227 _private prototype_ `void GenerateCleanBoneNames();` — strips extra junk off the bone names to make direct comparisons
- L230 _private prototype_ `void CheckBoneExistsAndHasSameParent( const FName& CleanBoneName, const FAbstractHierarchy& OtherHierarchy, bool& OutExists, bool& OutSameParent) const;` — checks if bone exists and has the same parent in both hierarchies (expects the clean bone name for apples-apples comparison)
- L237 _private prototype_ `static FString FindLargestCommonPrefix(const TArray<FName>& ArrayOfNames);` — returns the largest prefix that is common to ALL names in the input array
- L239 _private member_ `TArray<FName> FullBoneNames;`
- L240 _private member_ `TArray<FName> CleanBoneNames;`
- L241 _private member_ `TArray<int32> ParentIndices;`

#### struct `FBoneSettingsForIK`  
`struct FBoneSettingsForIK`  
_L244-260_
- L246 _public function_ `FBoneSettingsForIK(const FName InBoneName) : BoneToApplyTo(InBoneName)`
- L248 _public member_ `FName BoneToApplyTo;`
- L249 _public member_ `float RotationStiffness = 0.f;`
- L250 _public member_ `float PositionStiffness = 0.f;`
- L251 _public member_ `EPreferredAxis PreferredAxis = EPreferredAxis::None;`
- L252 _public member_ `bool bIsHinge = false;`
- L253 _public member_ `bool bExcluded = false;`
- L255 _public prototype_ `FVector GetPreferredAxisAsAngles() const;`
- L256 _public prototype_ `void LockNonPreferredAxes(EPBIKLimitType& OutX, EPBIKLimitType& OutY, EPBIKLimitType& OutZ) const;`
- L259 _private member_ `static constexpr float PreferredAngleMagnitude = 90.f;`

#### struct `FAllBoneSettingsForIK`  
`struct FAllBoneSettingsForIK`  
_L262-273_
- L264 _public prototype_ `void SetPreferredAxis(const FName BoneName, const EPreferredAxis PreferredAxis, const bool bTreatAsHinge=true);`
- L265 _public prototype_ `void SetRotationStiffness(const FName BoneName, const float RotationStiffness);`
- L266 _public prototype_ `void SetPositionStiffness(const FName BoneName, const float PositionStiffness);`
- L267 _public prototype_ `void SetExcluded(const FName BoneName, const bool bExclude);`
- L268 _public function_ `const TArray<FBoneSettingsForIK>& GetBoneSettings() const`
- L271 _private prototype_ `FBoneSettingsForIK& GetOrAddBoneSettings(const FName BoneName);`
- L272 _private member_ `TArray<FBoneSettingsForIK> AllBoneSettings;`

#### struct `FBoneToPin`  
`struct FBoneToPin`  
_L275-285_
- L277 _public function_ `FBoneToPin( const FName InBoneToPin, const FName InBoneToPinTo, const ERetargetSourceOrTarget InSkeletonToPinTo) : BoneToPin(InBoneToPin), BoneToPinTo(InBoneToPinTo), SkeletonToPinTo(InSkeletonToPinTo)`
- L282 _public member_ `FName BoneToPin;`
- L283 _public member_ `FName BoneToPinTo;`
- L284 _public member_ `ERetargetSourceOrTarget SkeletonToPinTo;`

#### struct `FBonesToPin`  
`struct FBonesToPin`  
_L287-301_
- L289 _public function_ `void AddBoneToPin( const FName BoneToPin, const FName BoneToPinTo, ERetargetSourceOrTarget SkeletonToPinTo = ERetargetSourceOrTarget::Target)`
- L297 _public function_ `const TArray<FBoneToPin>& GetBonesToPin() const`
- L300 _private member_ `TArray<FBoneToPin> AllBonesToPin;`

#### struct `FAutoRetargetDefinition`  
`struct FAutoRetargetDefinition`  
_L303-309_
- L305 _public member_ `FRetargetDefinition RetargetDefinition;`
- L306 _public member_ `FAllBoneSettingsForIK BoneSettingsForIK;`
- L307 _public member_ `FBonesToPin BonesToPin;`
- L308 _public member_ `TArray<FName> BonesToExcludeFromAutoPose;`

#### struct `FAutoCharacterizeResults`  
`struct FAutoCharacterizeResults`  
_L312-330_
- desc: the results of auto characterizing an input skeletal mesh
- L315 _public member_ `FAutoRetargetDefinition AutoRetargetDefinition;` — the pelvis and a list of bone chains
- L317 _public member_ `bool bUsedTemplate = false;` — did the auto characterizer use a template or procedurally generate the retarget definition?
- L319 _public member_ `FName BestTemplateName = NAME_None;` — the template that most closely matched with the input skeleton
- L321 _public member_ `int32 BestNumMatchingBones = 0;` — the number of bones that matched
- L323 _public member_ `float BestPercentageOfTemplateScore = 0.0f;` — the score of how closely the template matched the input skeleton (0-1)
- L325 _public member_ `TArray<FName> MissingBones;` — bones that were in the template, but not found in the input
- L327 _public member_ `TArray<FName> BonesWithMissingParent;` — bones that do not have the same parent as the equivalent in the template
- L329 _public member_ `TMap<FName,int32> ExpandedChains;` — number of bones we extended the spine/neck chains beyond what the template provides

#### struct `FTemplateHierarchy`  
`struct FTemplateHierarchy`  
_L334-341_
- desc: a hard coded template representing a "known" hierarchy that is used in the world (ie UE5 Mannequin, Fortnite skeleton etc..) contains the recommended retarget definition to use for this template, including the pelvis, retarget chains and bone settings
- L336 _public function_ `FTemplateHierarchy(const FName& InName, const FAbstractHierarchy& InHierarchy) : Name(InName), Hierarchy(InHierarchy)`
- L338 _public member_ `FName Name;`
- L339 _public member_ `FAbstractHierarchy Hierarchy;`
- L340 _public member_ `FAutoRetargetDefinition AutoRetargetDefinition;`

#### struct `FKnownTemplateHierarchies`  
`struct FKnownTemplateHierarchies`  
_L344-361_
- desc: a collection of FTemplateHierarchy to compare against
- L346 _public prototype_ `FKnownTemplateHierarchies();`
- L350 _public prototype_ `void GetClosestMatchingKnownHierarchy(const FAbstractHierarchy& InHierarchy, FAutoCharacterizeResults& Results) const;` — iterate over all the known hierarchies, find the one that is closest to the given hierarchy outputs the FAutoCharacterizeResults which includes a retarget definition to use
- L353 _public prototype_ `const FTemplateHierarchy* GetKnownHierarchyByName(const FName Name) const;` — get a pointer to a template hierarchy by name
- L358 _private prototype_ `FTemplateHierarchy& AddTemplateHierarchy(const FName& Label, const TArray<FName>& BoneNames, const TArray<int32>& ParentIndices);` — add a template hierarchy
- L360 _private member_ `TArray<FTemplateHierarchy> KnownHierarchies;`

#### struct `FAutoCharacterizer`  
`struct FAutoCharacterizer`  
_L365-398_
- desc: contains all the known hierarchies in popular usage, and provides a function to compare any given Skeletal Mesh against them if a template is matched to the input skeleton, then the retarget definition is adapted to the given skeleton
- L367 _public prototype_ `FAutoCharacterizer() = default;`
- L371 _public prototype_ `void GenerateRetargetDefinitionFromMesh(USkeletalMesh* Mesh, FAutoCharacterizeResults& Results) const;` — call this function with any skeletal mesh to auto-generate a retarget definition for it. the results includes the retarget definition itself, as well as the scores indicating how closely the skeleton was matched to a known hierarchy
- L374 _public prototype_ `const FTemplateHierarchy* GetKnownTemplateHierarchy(const FName& TemplateName) const;` — get read-only access to a template by name
- L380 _private prototype_ `void AdaptTemplateToHierarchy( const FTemplateHierarchy& Template, const FAbstractHierarchy& TargetHierarchy, FAutoCharacterizeResults& Results) const;` — adapts the retarget definition of a template to apply to a different hierarchy may require removing chains that are not valid on the target hierarchy and changing start/end bones to better match it
- L387 _private prototype_ `int32 ExpandChain(FBoneChain* ChainToExpand, const FAbstractHierarchy& Hierarchy) const;` — expand the given bone chain to include bones beyond the end bone specified by the template (useful for Spines and Necks) returns the number of bones that the chain was expanded by
- L390 _private prototype_ `void FindClosestNameInArray( const FName& NameToMatch, const TArray<FName>& NamesToCheck, FName& OutClosestName, float& OutBestScore) const;` — outputs the closest name to NameToMatch in NamesToCheck. OutBestScore ranges from 0-1 as percentage of string that matched NameToMatch.
- L397 _private member_ `FKnownTemplateHierarchies KnownHierarchies;` — all the known templates to compare against

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RigEditor/IKRigAutoFBIK.h` (Public)


#### enum `EAutoFBIKResult`  
`enum class EAutoFBIKResult`  
_L10-17_
- desc: what was the outcome of trying to automatically setup FBIK?
- L12 _public enumerator_ `AllOk`
- L13 _public enumerator_ `MissingMesh`
- L14 _public enumerator_ `UnknownSkeletonType`
- L15 _public enumerator_ `MissingChains`
- L16 _public enumerator_ `MissingPelvisBone`

#### struct `FAutoFBIKResults`  
`struct FAutoFBIKResults`  
_L21-27_
- desc: the results of auto characterizing an input skeletal mesh
- L23 _public function_ `FAutoFBIKResults() : Outcome(EAutoFBIKResult::AllOk)`
- L25 _public member_ `EAutoFBIKResult Outcome;`
- L26 _public member_ `TArray<FName> MissingChains;`

#### struct `FAutoFBIKCreator`  
`struct FAutoFBIKCreator`  
_L30-36_
- desc: given an IK Rig, will automatically generate an FBIK setup for use with retargeting
- L32 _public prototype_ `FAutoFBIKCreator() = default;`
- L35 _public prototype_ `void CreateFBIKSetup(const UIKRigController& IKRigController, FAutoFBIKResults& Results) const;` — call this function with any IK Rig controller to automatically create a FBIK setup

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RigEditor/IKRigCommands.h` (Public)


#### class `FIKRigCommands`  
`class FIKRigCommands : public TCommands<FIKRigCommands>`  
_L9-35_
- inherits: `TCommands<FIKRigCommands>`
- L12 _public function_ `FIKRigCommands() : TCommands<FIKRigCommands> ( "IKRig", NSLOCTEXT("Contexts", "IKRig", "IK Rig"), NAME_None,`
- L22 _public member_ `TSharedPtr< FUICommandInfo > Reset;` — reset whole system to initial state
- L25 _public member_ `TSharedPtr< FUICommandInfo > AutoRetargetChains;` — automatically generate retarget chains
- L28 _public member_ `TSharedPtr< FUICommandInfo > AutoSetupFBIK;` — automatically setup full body ik
- L31 _public member_ `TSharedPtr< FUICommandInfo > ShowAssetSettings;` — show settings of the asset in the details panel
- L34 _public prototype_ `virtual void RegisterCommands() override;` — initialize commands

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RigEditor/IKRigController.h` (Public)


#### class `UIKRigController`  
`class UIKRigController : public UObject`  
_L43-470_
- reflection: `UCLASS(MinimalAPI, BlueprintType, hidecategories = UObject)`
- inherits: `UObject`
- desc: A singleton (per-asset) class used to make modifications to a UIKRigDefinition asset All modifications to an IKRigDefinition must go through this controller. Editors can subscribe to the callbacks on this controller to be notified of changes that require reinitialization of a running IK Rig processor instance. The API here is split into public/scripting sections which are accessible from Blueprint/Python and sections that are only relevant to editors in C++.
- L49 _public prototype_ `UIKRigController();`
- L57 _public prototype_ `static UIKRigController* GetController(const UIKRigDefinition* InIKRigDefinition);` — `UFUNCTION(BlueprintCallable, Category="IK Rig", meta = (DisplayName = "Get IK Rig Controller"))` — Use this to get the controller for the given IKRig
- L62 _public prototype_ `bool SetSkeletalMesh(USkeletalMesh* SkeletalMesh) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Rig", meta = (DisplayName = "Set IK Rig Skeletal Mesh"))` — Sets the preview mesh to use. Loads the hierarchy into the asset's IKRigSkeleton. Returns true if the mesh was able to be set. False if it was incompatible for any reason.
- L66 _public prototype_ `USkeletalMesh* GetSkeletalMesh() const;` — `UFUNCTION(BlueprintCallable, Category="IK Rig", meta = (DisplayName = "Get IK Rig Skeletal Mesh"))` — Get the skeletal mesh this asset is initialized with
- L70 _public prototype_ `bool IsSkeletalMeshCompatible(USkeletalMesh* SkeletalMeshToCheck) const;` — `UFUNCTION(BlueprintCallable, Category="IK Rig")` — Returns true if the provided skeletal mesh could be used with this IK Rig.
- L79 _public prototype_ `UIKRigDefinition* GetAsset() const;` — Get the asset this controller controls. Warning: Do not use for general editing of the data model. If you need to make modifications to the asset, do so through the API provided by this controller.
- L80 _public prototype_ `TObjectPtr<UIKRigDefinition>& GetAssetPtr();`
- L83 _public prototype_ `void BroadcastNeedsReinitialized() const;` — force all currently connected processors to reinitialize using latest asset state
- L90 _public prototype_ `const FIKRigSkeleton& GetIKRigSkeleton() const;` — Get read-access to the IKRig skeleton representation
- L99 _public prototype_ `int32 AddSolver(const FString InIKRigSolverType) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Rig")` — Add a new solver of the given type to the bottom of the stack. Returns the stack index. The type here is the full package path of the UStruct type. For example: /Script/IKRig.FullBodyIKSolver
- L103 _public prototype_ `bool RemoveSolver(const int32 SolverIndex) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Rig")` — Remove the solver at the given stack index.
- L107 _public prototype_ `int32 GetNumSolvers() const;` — `UFUNCTION(BlueprintCallable, Category="IK Rig")` — Get the number of solvers in the stack.
- L111 _public prototype_ `bool MoveSolverInStack(int32 SolverToMoveIndex, int32 TargetSolverIndex) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Rig")` — Move the solver at the given index to the target index.
- L115 _public prototype_ `bool SetSolverEnabled(int32 SolverIndex, bool bIsEnabled) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Rig")` — Set enabled/disabled status of the given solver.
- L119 _public prototype_ `bool GetSolverEnabled(int32 SolverIndex) const;` — `UFUNCTION(BlueprintCallable, Category="IK Rig")` — Get enabled status of the given solver.
- L123 _public prototype_ `bool SetStartBone(const FName RootBoneName, int32 SolverIndex) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Rig")` — Set the root bone on a given solver. (not all solvers support root bones, checks CanSetStartBone() first)
- L127 _public prototype_ `FName GetStartBone(int32 SolverIndex) const;` — `UFUNCTION(BlueprintCallable, Category="IK Rig")` — Get the name of the root bone on a given solver. (not all solvers support start bones, checks CanSetStartBone() first)
- L131 _public prototype_ `bool SetEndBone(const FName EndBoneName, int32 SolverIndex) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Rig")` — Set the end bone on a given solver. (not all solvers require extra end bones, checks CanSetEndBone() first)
- L135 _public prototype_ `FName GetEndBone(int32 SolverIndex) const;` — `UFUNCTION(BlueprintCallable, Category="IK Rig")` — Get the name of the end bone on a given solver. (not all solvers require extra end bones, checks CanSetEndBone() first)
- L139 _public prototype_ `UIKRigSolverControllerBase* GetSolverController(int32 SolverIndex);` — `UFUNCTION(BlueprintCallable, Category="IK Rig")` — Get a controller to customize the settings for a given solver in the stack
- L144 _public prototype_ `int32 GetIndexOfSolver(UIKRigSolverControllerBase* InController);` — `UFUNCTION(BlueprintCallable, Category="IK Rig")` — Get the index for a given solver in the stack The input here is a solver controller (as returned by GetSolverController())
- L151 _public prototype_ `int32 AddSolver(UScriptStruct* InIKRigSolverType) const;` — Add a solver to the IK Rig asset's solver stack
- L154 _public prototype_ `FIKRigSolverBase* GetSolverAtIndex(int32 Index) const;` — Get access to the given solver.
- L157 _public prototype_ `FInstancedStruct* GetSolverStructAtIndex(int32 Index) const;` — Get access to the instanced struct for a given solver.
- L160 _public prototype_ `int32 GetIndexOfSolver(FIKRigSolverBase* Solver) const;` — Get access to the given solver.
- L163 _public prototype_ `const TArray<FIKRigSolverBase*> GetSolverArray() const;` — Get read-only access to the array of solvers.
- L166 _public prototype_ `FString GetSolverUniqueName(int32 SolverIndex) const;` — Get unique label for a given solver. Returns dash separated index and name like so, "0 - SolverName".
- L174 _public prototype_ `FName AddNewGoal(const FName GoalName, const FName BoneName) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Rig")` — Add a new Goal associated with the given Bone. GoalName must be unique. Bones can have multiple Goals (rare).
- L178 _public prototype_ `bool RemoveGoal(const FName GoalName) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Rig")` — Remove the Goal by name.
- L182 _public prototype_ `FName RenameGoal(const FName OldName, const FName PotentialNewName) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Rig")` — Rename a Goal. Returns new name, which may be different after being sanitized. Returns NAME_None if this fails.
- L186 _public prototype_ `bool SetGoalBone(const FName GoalName, const FName NewBoneName) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Rig")` — The the Bone that the given Goal should be parented to / associated with.
- L190 _public prototype_ `FName GetBoneForGoal(const FName GoalName) const;` — `UFUNCTION(BlueprintCallable, Category="IK Rig")` — The the Bone associated with the given Goal.
- L194 _public prototype_ `FName GetGoalNameForBone(const FName BoneName) const;` — `UFUNCTION(BlueprintCallable, Category="IK Rig")` — Get the Goal associated with the given Bone (may be NAME_None)
- L198 _public prototype_ `bool ConnectGoalToSolver(const FName GoalName, int32 SolverIndex) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Rig")` — Connect the given Goal to the given Solver. This creates an "Effector" with settings specific to this Solver.
- L202 _public prototype_ `bool DisconnectGoalFromSolver(const FName GoalToRemove, int32 SolverIndex) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Rig")` — Disconnect the given Goal from the given Solver. This removes the Effector that associates the Goal with the Solver.
- L206 _public prototype_ `bool IsGoalConnectedToSolver(const FName GoalName, int32 SolverIndex) const;` — `UFUNCTION(BlueprintCallable, Category="IK Rig")` — Returns true if the given Goal is connected to the given Solver. False otherwise.
- L210 _public prototype_ `bool IsGoalConnectedToAnySolver(const FName GoalName) const;` — `UFUNCTION(BlueprintCallable, Category="IK Rig")` — Returns true if the given Goal is connected to ANY solver. False otherwise.
- L214 _public prototype_ `UIKRigEffectorGoal* GetGoal(const FName GoalName) const;` — `UFUNCTION(BlueprintCallable, Category="IK Rig")` — Get read-write access to the Goal with the given name.
- L218 _public prototype_ `const TArray<UIKRigEffectorGoal*>& GetAllGoals() const;` — `UFUNCTION(BlueprintCallable, Category="IK Rig")` — Get access to the list of Goals.
- L224 _public prototype_ `UObject* GetGoalSettingsForSolver(const FName GoalName, int32 SolverIndex) const;` — `UE_DEPRECATED(5.6, "In 5.6+ each solver provides it's own controller. Use GetSolverController(SolverIndex).GetGoalSettings(GoalName) instead.")` — `UFUNCTION(BlueprintCallable, Category="IK Rig")` — Get the UObject for the settings associated with the given Goal in the given Solver. Solvers can define their own per-Goal settings depending on their needs. These are termed "Effectors".
- L228 _public prototype_ `bool DoesSolverHaveCustomGoalSettings(const FName GoalName, int32 SolverIndex) const;` — `UFUNCTION(BlueprintCallable, Category="IK Rig")` — returns true if the goal has custom settings for the given solver
- L235 _public prototype_ `int32 GetGoalIndex(const FName InGoalName, const ENameCase CompareMethod = ENameCase::IgnoreCase) const;` — Get the index of the given Goal in the list of Goals.
- L238 _public prototype_ `FTransform GetGoalCurrentTransform(const FName GoalName) const;` — Get the global-space transform of the given Goal. This may be set by the user in the editor, or at runtime.
- L241 _public prototype_ `void SetGoalCurrentTransform(const FName GoalName, const FTransform& Transform) const;` — Set the Goal to the given transform.
- L244 _public prototype_ `void ResetGoalTransforms() const;` — Reset all Goals back to their initial transforms.
- L247 _public prototype_ `void ResetInitialGoalTransforms() const;` — Reset initial goal transform
- L250 _public prototype_ `static void SanitizeGoalName(FString& InOutName);` — Ensure that the given name adheres to required standards for Goal names (no special characters etc..)
- L253 _public prototype_ `FName GetUniqueGoalName(const FName NameToMakeUnique) const;` — Add a suffix as needed to ensure the Goal name is unique
- L256 _public prototype_ `bool ModifyGoal(const FName GoalName) const;` — Modify a Goal for a transaction. Returns true if Goal found.
- L264 _public prototype_ `bool SetBoneExcluded(const FName BoneName, const bool bExclude) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Rig")` — Include/exclude a bone from all the solvers. All bones are included by default.
- L268 _public prototype_ `bool GetBoneExcluded(const FName BoneName) const;` — `UFUNCTION(BlueprintCallable, Category="IK Rig")` — Returns true if the given Bone is excluded, false otherwise.
- L272 _public prototype_ `bool AddBoneSetting(const FName BoneName, int32 SolverIndex) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Rig")` — Add settings to the given Bone/Solver. Does nothing if Bone already has settings in this Solver.
- L276 _public prototype_ `bool RemoveBoneSetting(const FName BoneName, int32 SolverIndex) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Rig")` — Remove settings for the given Bone/Solver. Does nothing if Bone doesn't have setting in this Solver.
- L280 _public prototype_ `FTransform GetRefPoseTransformOfBone(const FName BoneName) const;` — `UFUNCTION(BlueprintCallable, Category="IK Rig")` — Get the global-space retarget pose transform of the given Bone.
- L285 _public prototype_ `UObject* GetBoneSettings(const FName BoneName, int32 SolverIndex) const;` — `UE_DEPRECATED(5.6, "In 5.6+ each solver provides it's own controller. Use GetSolverController(SolverIndex).GetBoneSettings(BoneName) instead.")` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Rig")` — Get the generic (Solver-specific) Bone settings UObject for this Bone in the given Solver.
- L292 _public prototype_ `FIKRigBoneSettingsBase* GetSettingsForBone(const FName BoneName, int32 SolverIndex) const;` — Get the generic (Solver-specific) Bone settings UStruct for this Bone in the given Solver.
- L295 _public prototype_ `bool CanAddBoneSetting(const FName BoneName, int32 SolverIndex, FText* OutError = nullptr) const;` — Returns true if this Bone can have settings in the given Solver.
- L298 _public prototype_ `bool CanRemoveBoneSetting(const FName BoneName, int32 SolverIndex) const;` — Returns true if settings for this Bone can be removed from the given Solver.
- L301 _public prototype_ `bool DoesBoneHaveSettings(const FName BoneName) const;` — Returns true if the given Bone has any settings in any Solver.
- L310 _public prototype_ `FName AddRetargetChain(const FName ChainName, const FName StartBoneName, const FName EndBoneName, const FName GoalName) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Rig")` — Add a new chain with the given Chain and Bone names. Returns newly created chain name (uniquified). Note: only the ChainName is required here, all else can be set later.
- L314 _public prototype_ `bool RemoveRetargetChain(const FName ChainName) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Rig")` — Remove a Chain with the given name. Returns true if a Chain was removed.
- L318 _public prototype_ `FName RenameRetargetChain(const FName ChainName, const FName NewChainName) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Rig")` — Renamed the given Chain. Returns the new name (same as old if unsuccessful).
- L322 _public prototype_ `bool SetRetargetChainStartBone(const FName ChainName, const FName StartBoneName) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Rig")` — Set the Start Bone for the given Chain. Returns true if operation was successful.
- L326 _public prototype_ `bool SetRetargetChainEndBone(const FName ChainName, const FName EndBoneName) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Rig")` — Set the End Bone for the given Chain. Returns true if operation was successful.
- L330 _public prototype_ `bool SetRetargetChainGoal(const FName ChainName, const FName GoalName) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Rig")` — Set the Goal for the given Chain. Returns true if operation was successful.
- L334 _public prototype_ `FName GetRetargetChainGoal(const FName ChainName) const;` — `UFUNCTION(BlueprintCallable, Category="IK Rig")` — Get the Goal name for the given Chain.
- L338 _public prototype_ `FName GetRetargetChainStartBone(const FName ChainName) const;` — `UFUNCTION(BlueprintCallable, Category="IK Rig")` — Get the End Bone name for the given Chain.
- L342 _public prototype_ `FName GetRetargetChainEndBone(const FName ChainName) const;` — `UFUNCTION(BlueprintCallable, Category="IK Rig")` — Get the Start Bone name for the given Chain.
- L346 _public prototype_ `const TArray<FBoneChain>& GetRetargetChains() const;` — `UFUNCTION(BlueprintCallable, Category="IK Rig")` — Get read-only access to the list of Chains.
- L350 _public prototype_ `bool SetRetargetRoot(const FName RootBoneName) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Rig", DisplayName="SetPelvisBone")` — Set the Pelvis Bone of the retargeting (can only be one).
- L354 _public prototype_ `FName GetRetargetRoot() const;` — `UFUNCTION(BlueprintCallable, Category="IK Rig", DisplayName="GetPelvisBone")` — Get the name of the Pelvis Bone of the retargeting (can only be one).
- L358 _public prototype_ `bool SetRootMotionBone(const FName RootBoneName) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="IK Rig")` — Set the bone used to store root motion for the skeleton (could be different from the root of the hierarchy).
- L362 _public prototype_ `FName GetRootMotionBone() const;` — `UFUNCTION(BlueprintCallable, Category="IK Rig")` — Get the bone used to store root motion for the skeleton (could be different from the root of the hierarchy).
- L367 _public prototype_ `bool ApplyAutoGeneratedRetargetDefinition();` — `UFUNCTION(BlueprintCallable, Category="IK Rig")` — Analyse the skeleton to see if it matches a known template and automatically generates all retarget chains and sets the pelvis Returns true if a matching skeletal template was found and the retarget definition for it was applied.
- L372 _public prototype_ `bool ApplyAutoFBIK();` — `UFUNCTION(BlueprintCallable, Category="IK Rig")` — Analyse the skeleton to see if it matches a known template and automatically generates a full body IK setup Returns true if a matching skeletal template was found and the FBIK setup for it was applied.
- L379 _public prototype_ `void SetRetargetDefinition(const FRetargetDefinition& RetargetDefinition) const;` — Replace the entire retarget definition (includes all bone chains and the pelvis setting)
- L382 _public prototype_ `void AutoGenerateRetargetDefinition(FAutoCharacterizeResults& Results) const;` — Auto generates a retarget definition and returns the results
- L385 _public prototype_ `void AutoGenerateFBIK(FAutoFBIKResults& Results) const;` — Auto generates an FBIK setup for the current skeletal mesh
- L388 _public prototype_ `const FAutoCharacterizer& GetAutoCharacterizer() const;` — Get read-only access to characterizer
- L391 _public prototype_ `FName AddRetargetChainInternal(const FBoneChain& BoneChain) const;` — Add a Chain with the given BoneChain settings. Returns newly created chain name.
- L394 _public prototype_ `const FBoneChain* GetRetargetChainByName(const FName ChainName) const;` — Get read-only access to a single retarget chain with the given name
- L397 _public prototype_ `FName GetRetargetChainFromBone(const FName BoneName, const FIKRigSkeleton* OptionalSkeleton) const;` — Get the name of the retarget chain that contains the given Bone. Returns NAME_None if Bone not in a Chain.
- L400 _public prototype_ `FName GetRetargetChainFromGoal(const FName GoalName) const;` — Get the name of the retarget chain that contains the given Goal. Returns NAME_None if Goal not in a Chain.
- L403 _public prototype_ `void SortRetargetChains() const;` — Sorts the Chains from Root to tip based on the Start Bone of each Chain.
- L406 _public prototype_ `FName GetUniqueRetargetChainName(FName NameToMakeUnique) const;` — Make unique name for a retargeting bone chain. Adds a numbered suffix to make it unique.
- L410 _public prototype_ `bool ValidateChain( const FName ChainName, const FIKRigSkeleton* OptionalSkeleton, TSet<int32>& OutChainIndices) const;` — Returns true if this is a valid chain. Produces array of bone indices between start and end (inclusive). Optionally provide a runtime skeleton from an IKRigProcessor to get indices for a running instance (otherwise uses stored hierarchy in asset)
- L414 _public prototype_ `TArray<UIKRigStructWrapperBase*> GetStructWrappers(const int32 InNum, TSubclassOf<UIKRigStructWrapperBase> InType);` — returns an array of wrappers to display structs in the details panel NOTE: these are recycled by the editor using this controller (assumes one editor per asset)
- L419 _private prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnIKRigNeedsInitialized, UIKRigDefinition*);` — Called whenever the rig is modified in such a way that would require re-initialization by dependent systems.
- L420 _private member_ `FOnIKRigNeedsInitialized IKRigNeedsInitialized;`
- L423 _private prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRetargetChainAdded, UIKRigDefinition*);` — Called whenever a retarget chain is added.
- L424 _private member_ `FOnRetargetChainAdded RetargetChainAdded;`
- L427 _private prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRetargetChainRemoved, UIKRigDefinition*, const FName );` — Called whenever a retarget chain is removed.
- L428 _private member_ `FOnRetargetChainRemoved RetargetChainRemoved;`
- L431 _private prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnRetargetChainRenamed, UIKRigDefinition*, FName , FName );` — Called whenever a retarget chain is renamed.
- L432 _private member_ `FOnRetargetChainRenamed RetargetChainRenamed;`
- L436 _public function_ `FOnIKRigNeedsInitialized& OnIKRigNeedsInitialized()`
- L437 _public function_ `FOnRetargetChainAdded& OnRetargetChainAdded()`
- L438 _public function_ `FOnRetargetChainRemoved& OnRetargetChainRemoved()`
- L439 _public function_ `FOnRetargetChainRenamed& OnRetargetChainRenamed()`
- L444 _private member_ `TUniquePtr<FAutoCharacterizer> AutoCharacterizer;` — auto characterizer
- L447 _private member_ `TUniquePtr<FAutoFBIKCreator> AutoFBIKCreator;` — auto fbik generator
- L450 _private member_ `mutable int32 ReinitializeScopeCounter = 0;` — prevent reinitializing from inner operations
- L451 _private member_ `mutable bool bGoalsChangedInScope = false;`
- L455 _private member_ `TObjectPtr<UIKRigDefinition> Asset = nullptr;` — `UPROPERTY(transient)` — The actual IKRigDefinition asset that this Controller modifies.
- L460 _private member_ `FIKRigStructWrapperPool StructViewerPool;` — `UPROPERTY(transient)` — a pool of objects inheriting from UIKRigStructWrapperBase for editing various IK Rig struct types in a details view NOTE: pool contains a bucket per settings type
- L463 _private member_ `static TMap<UIKRigDefinition*, UIKRigController*> Controllers;` — Static global map of assets to their associated controller
- L466 _private prototype_ `void BroadcastGoalsChange() const;` — broadcast changes within the asset goals array

#### struct `FScopedReinitializeIKRig`  
`struct FScopedReinitializeIKRig`  
_L472-495_
- L474 _public function_ `FScopedReinitializeIKRig(const UIKRigController *InController, const bool bGoalsChanged=false)`
- L480 _public function_ `~FScopedReinitializeIKRig()`
- L494 _public member_ `const UIKRigController* Controller;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API IKRIGEDITOR_API`
- L419 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnIKRigNeedsInitialized, UIKRigDefinition*);` — Called whenever the rig is modified in such a way that would require re-initialization by dependent systems.
- L423 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRetargetChainAdded, UIKRigDefinition*);` — Called whenever a retarget chain is added.
- L427 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRetargetChainRemoved, UIKRigDefinition*, const FName );` — Called whenever a retarget chain is removed.
- L431 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnRetargetChainRenamed, UIKRigDefinition*, FName , FName );` — Called whenever a retarget chain is renamed.

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RigEditor/IKRigDefinitionFactory.h` (Public)


#### class `UIKRigDefinitionFactory`  
`class UIKRigDefinitionFactory : public UFactory`  
_L15-45_
- reflection: `UCLASS(MinimalAPI, BlueprintType, hidecategories=Object)`
- inherits: `UFactory`
- L21 _public prototype_ `UIKRigDefinitionFactory();`
- L24 _public prototype_ `virtual UObject* FactoryCreateNew( UClass* Class, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory interface
- L31 _public prototype_ `virtual FText GetDisplayName() const override;`
- L32 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L33 _public prototype_ `virtual FText GetToolTip() const override;`
- L34 _public prototype_ `virtual FString GetDefaultNewAssetName() const override;`
- L35 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`
- L44 _public prototype_ `static UIKRigDefinition* CreateNewIKRigAsset(const FString& InPackagePath, const FString& InAssetName);` — `UFUNCTION(BlueprintCallable, Category = "IK Rig", DisplayName="Create New IK Rig Asset")` — Create a new IK Rig rig asset at a specified location in your project's content folder. @param InDesiredPackagePath The package path to where the new IK Rig will be placed. (ie "/Game/MyIKRigs/") @param InAssetName The name of the new asset (ie "IK_MyNewRig")

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API IKRIGEDITOR_API`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RigEditor/IKRigDetailCustomizations.h` (Public)


#### class `FIKRigGenericDetailCustomization`  
`class FIKRigGenericDetailCustomization : public IDetailCustomization`  
_L12-42_
- inherits: `IDetailCustomization`
- L16 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L22 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L27 _private prototype_ `static const TArray<FText>& GetButtonLabels();` — Labels and transform types used by the transform widget
- L28 _private prototype_ `static const TArray<EIKRigTransformType::Type>& GetTransformTypes();`
- L32 _private function_ `template<typename ClassToCustomize> void CustomizeDetailsForClass(IDetailLayoutBuilder& DetailBuilder, const TArray<TWeakObjectPtr<UObject>>& ObjectsBeingCustomized)` — Per class customization
- L36 _private prototype_ `template<> void CustomizeDetailsForClass<UIKRigBoneDetails>(IDetailLayoutBuilder& DetailBuilder, const TArray<TWeakObjectPtr<UObject>>& ObjectsBeingCustomized);` — Template specializations
- L38 _private prototype_ `template<> void CustomizeDetailsForClass<UIKRigEffectorGoal>(IDetailLayoutBuilder& DetailBuilder, const TArray<TWeakObjectPtr<UObject>>& ObjectsBeingCustomized);`
- L41 _private member_ `TSharedPtr<FScopedTransaction> ValueChangedTransaction;` — Transaction to handle value changed. It's being effective once the value committed

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RigEditor/IKRigEditMode.h` (Public)


#### class `FIKRigEditMode`  
`class FIKRigEditMode : public IPersonaEditMode`  
_L18-73_
- inherits: `IPersonaEditMode`
- L23 _public member_ `static FName ModeName;`
- L25 _public prototype_ `FIKRigEditMode();`
- L28 _public function_ `void SetEditorController(const TSharedPtr<FIKRigEditorController> InEditorController)` — glue for all the editor parts to communicate
- L31 _public prototype_ `virtual bool GetCameraTarget(FSphere& OutTarget) const override;` — IPersonaEditMode interface
- L32 _public prototype_ `virtual class IPersonaPreviewScene& GetAnimPreviewScene() const override;`
- L33 _public prototype_ `virtual void GetOnScreenDebugInfo(TArray<FText>& OutDebugInfo) const override;`
- L37 _public prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;` — FEdMode interface
- L38 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L39 _public prototype_ `virtual void DrawHUD(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View, FCanvas* Canvas) override;`
- L40 _public function_ `virtual bool IsCompatibleWith(FEditorModeID OtherModeID) const override`
- L41 _public prototype_ `virtual bool AllowWidgetMove() override;`
- L42 _public prototype_ `virtual bool ShouldDrawWidget() const override;`
- L43 _public prototype_ `virtual bool UsesTransformWidget() const override;`
- L44 _public prototype_ `virtual bool UsesTransformWidget(UE::Widget::EWidgetMode CheckMode) const override;`
- L45 _public prototype_ `virtual FVector GetWidgetLocation() const override;`
- L46 _public prototype_ `virtual bool HandleClick(FEditorViewportClient* InViewportClient, HHitProxy* HitProxy, const FViewportClick& Click) override;`
- L47 _public prototype_ `virtual bool StartTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;`
- L48 _public prototype_ `virtual bool EndTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;`
- L49 _public prototype_ `virtual bool InputDelta(FEditorViewportClient* InViewportClient, FViewport* InViewport, FVector& InDrag, FRotator& InRot, FVector& InScale) override;`
- L50 _public prototype_ `virtual bool GetCustomDrawingCoordinateSystem(FMatrix& InMatrix, void* InData) override;`
- L51 _public prototype_ `virtual bool GetCustomInputCoordinateSystem(FMatrix& InMatrix, void* InData) override;`
- L52 _public prototype_ `virtual bool InputKey(FEditorViewportClient* ViewportClient,FViewport* Viewport, FKey Key,EInputEvent Event) override;`
- L53 _public prototype_ `virtual bool BeginTransform(const FGizmoState& InState) override;`
- L54 _public prototype_ `virtual bool EndTransform(const FGizmoState& InState) override;`
- L59 _private prototype_ `void RenderGoals(FPrimitiveDrawInterface* PDI);`
- L60 _private prototype_ `void RenderBones(FPrimitiveDrawInterface* PDI);`
- L61 _private prototype_ `void GetBoneColors( FIKRigEditorController* Controller, const FIKRigProcessor& Processor, const FReferenceSkeleton& RefSkeleton, bool bUseMultiColorAsDefaultColor, TArray<FLinearColor>& OutBoneColors) const;`
- L68 _private prototype_ `bool HandleBeginTransform() const;`
- L69 _private prototype_ `bool HandleEndTransform() const;`
- L72 _private member_ `TWeakPtr<FIKRigEditorController> EditorController;` — The hosting app

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RigEditor/IKRigEditorController.h` (Public)


#### enum `EIKRigSelectionType`  
`enum EIKRigSelectionType : int8`  
_L30-35_
- L32 _public enumerator_ `Hierarchy`
- L33 _public enumerator_ `SolverStack`
- L34 _public enumerator_ `RetargetChains`

#### class `UIKRigBoneDetails`  
`class UIKRigBoneDetails : public UObject`  
_L38-85_
- reflection: `UCLASS(MinimalAPI, config = Engine, hidecategories = UObject)`
- inherits: `UObject`
- L45 _public function_ `void SetBone(const FName& BoneName)` — todo update bone info automatically using something else
- L51 _public member_ `FName SelectedBone;` — `UPROPERTY(VisibleAnywhere, Category = "Selection")`
- L54 _public member_ `FTransform CurrentTransform;` — `UPROPERTY(VisibleAnywhere, Category = "Bone Transforms")`
- L57 _public member_ `FTransform ReferenceTransform;` — `UPROPERTY(VisibleAnywhere, Category = "Bone Transforms")`
- L60 _public member_ `TWeakObjectPtr<UAnimInstance> AnimInstancePtr;` — `UPROPERTY()`
- L63 _public member_ `TWeakObjectPtr<UIKRigDefinition> AssetPtr;` — `UPROPERTY()`
- L67 _public prototype_ `TOptional<FTransform> GetTransform(EIKRigTransformType::Type TransformType) const;`
- L68 _public prototype_ `bool IsComponentRelative(ESlateTransformComponent::Type Component, EIKRigTransformType::Type TransformType) const;`
- L69 _public prototype_ `void OnComponentRelativeChanged(ESlateTransformComponent::Type Component, bool bIsRelative, EIKRigTransformType::Type TransformType);`
- L70 _public prototype_ `void OnCopyToClipboard(ESlateTransformComponent::Type Component, EIKRigTransformType::Type TransformType) const;`
- L71 _public prototype_ `void OnPasteFromClipboard(ESlateTransformComponent::Type Component, EIKRigTransformType::Type TransformType);`
- L74 _public function_ `template <typename DataType> void GetContentFromData(const DataType& InData, FString& Content) const`
- L83 _private member_ `static bool CurrentTransformRelative[3];`
- L84 _private member_ `static bool ReferenceTransformRelative[3];`

#### enum `EChainSide`  
`enum class EChainSide`  
_L87-92_
- L89 _public enumerator_ `Left`
- L90 _public enumerator_ `Right`
- L91 _public enumerator_ `Center`

#### struct `FRetargetChainAnalyzer`  
`struct FRetargetChainAnalyzer`  
_L95-109_
- desc: use string matching and skeletal analysis to suggest a reasonable default name for retarget chains
- L97 _public member_ `TSharedPtr<FTextFilterExpressionEvaluator> TextFilter;`
- L99 _public function_ `FRetargetChainAnalyzer()`
- L104 _public prototype_ `void AssignBestGuessName(FBoneChain& Chain, const FIKRigSkeleton& IKRigSkeleton);`
- L106 _public prototype_ `static FName GetDefaultChainName();`
- L108 _public prototype_ `EChainSide GetSideOfChain(const TArray<int32>& BoneIndices, const FIKRigSkeleton& IKRigSkeleton) const;`

#### class `FIKRigEditorController`  
`class FIKRigEditorController : public TSharedFromThis<FIKRigEditorController>, FGCObject`  
_L112-290_
- inherits: `TSharedFromThis<FIKRigEditorController>,FGCObject`
- desc: a home for cross-widget communication to synchronize state across all tabs and viewport
- L117 _public prototype_ `void Initialize(TSharedPtr<FIKRigEditorToolkit> Toolkit, const UIKRigDefinition* Asset);` — initialize the editor controller to an instance of the IK Rig editor
- L119 _public prototype_ `void Close() const;` — cleanup when editor closed
- L122 _public prototype_ `FIKRigProcessor* GetIKRigProcessor() const;` — get the currently active processor running the IK Rig in the editor
- L124 _public prototype_ `const FIKRigSkeleton* GetCurrentIKRigSkeleton() const;` — get the currently running IKRig skeleton (if there is a running processor)
- L127 _public prototype_ `void HandleIKRigNeedsInitialized(UIKRigDefinition* ModifiedIKRig) const;` — callback when IK Rig requires re-initialization
- L130 _public prototype_ `void HandleDeleteSelectedElements();` — delete key pressed (in either viewport or tree view)
- L133 _public prototype_ `void AddNewGoals(const TArray<FName>& GoalNames, const TArray<FName>& BoneNames);` — create goals
- L135 _public prototype_ `void ClearSelection() const;` — clear all selected objects
- L137 _public prototype_ `void HandleGoalSelectedInViewport(const FName& GoalName, bool bReplace) const;` — callback when goal is selected in the viewport
- L139 _public prototype_ `void HandleBoneSelectedInViewport(const FName& BoneName, bool bReplace) const;` — callback when bone is selected in the viewport
- L141 _public prototype_ `void Reset() const;` — reset all goals to initial transforms
- L143 _public prototype_ `void RefreshTreeView() const;` — refresh just the skeleton tree view
- L145 _public prototype_ `void ClearOutputLog() const;` — clear the output log
- L147 _public prototype_ `void AutoGenerateRetargetChains() const;` — automatically generates retarget chains
- L149 _public prototype_ `void AutoGenerateFBIK() const;` — automatically generates IK setup
- L152 _public prototype_ `void GetSelectedSolvers(TArray<TSharedPtr<FSolverStackElement> >& OutSelectedSolvers) const;` — return list of those solvers in the stack that are selected by user
- L154 _public prototype_ `int32 GetSelectedSolverIndex();` — get index of the first selected solver, return INDEX_None if nothing selected
- L156 _public prototype_ `void GetSelectedGoalNames(TArray<FName>& OutGoalNames) const;` — get names of all goals that are selected
- L158 _public prototype_ `int32 GetNumSelectedGoals() const;` — return the number of selected goals
- L160 _public prototype_ `void GetSelectedBoneNames(TArray<FName>& OutBoneNames) const;` — get names of all bones that are selected
- L162 _public prototype_ `void GetSelectedBones(TArray<TSharedPtr<FIKRigTreeElement>>& OutBoneItems) const;` — get all bones that are selected
- L164 _public prototype_ `bool IsGoalSelected(const FName& GoalName) const;` — returns true if Goal is currently selected
- L166 _public prototype_ `bool DoesSkeletonHaveSelectedItems() const;` — is anything selected in the skeleton view?
- L168 _public prototype_ `TArray<FName> GetSelectedChains() const;` — get name of the selected retargeting chain
- L170 _public prototype_ `void GetChainsSelectedInSkeletonView(TArray<FBoneChain>& InOutChains);` — get chains selected in skeleton view
- L173 _public prototype_ `void CreateNewRetargetChains();` — create new retarget chains from selected bones (or single empty chain if no selection)
- L176 _public function_ `void ShowDetailsForBone(const FName BoneName) const` — show single transform of bone in details view
- L177 _public prototype_ `void ShowDetailsForBones(const TArray<FName>& BoneNames) const;`
- L179 _public prototype_ `void ShowDetailsForBoneSettings(const TArray<TSharedPtr<FIKRigTreeElement>>& InItems) const;` — show BONE settings in details view
- L181 _public prototype_ `void ShowDetailsForGoals(const TArray<FName>& GoalName) const;` — show GOAL settings in details view
- L183 _public prototype_ `void ShowDetailsForGoalSettings(const TArray<TSharedPtr<FIKRigTreeElement>>& InItems) const;` — show EFFECTOR settings in details view
- L185 _public prototype_ `void ShowDetailsForSolvers(const TArray<int32>& InSolverIndices) const;` — show SOLVER settings in details view
- L187 _public prototype_ `void ShowAssetDetails() const;` — show nothing in details view
- L189 _public prototype_ `void ShowDetailsForElements(const TArray<TSharedPtr<FIKRigTreeElement>>& InItems) const;` — show details for items
- L191 _public prototype_ `void ShowStructWrappersInDetailsView(TArray<UIKRigStructWrapperBase*> InStructWrappers) const;` — show the currently configured IKRigStructWrapper objects in the details tab
- L193 _public prototype_ `void OnFinishedChangingDetails(const FPropertyChangedEvent& PropertyChangedEvent) const;` — callback when detail is edited
- L195 _public prototype_ `bool IsObjectInDetailsView(const UObject* Object) const;` — returns true if the supplied UObject is being shown in the details panel
- L198 _public prototype_ `void SetDetailsView(const TSharedPtr<class IDetailsView>& InDetailsView);` — set details tab view
- L200 _public function_ `void SetHierarchyView(const TSharedPtr<SIKRigHierarchy>& InSkeletonView)` — set skeleton tab view
- L202 _public function_ `void SetSolverStackView(const TSharedPtr<SIKRigSolverStack>& InSolverStackView)` — set solver stack tab view
- L204 _public function_ `void SetRetargetingView(const TSharedPtr<SIKRigRetargetChainList>& InRetargetingView)` — set retargeting tab view
- L206 _public function_ `void SetOutputLogView(const TSharedPtr<SIKRigOutputLog>& InOutputLogView)` — set output log view
- L209 _public prototype_ `bool PromptToAddDefaultSolver() const;` — right after importing a skeleton, we ask user what solver they want to use
- L211 _public prototype_ `FName PromptToAddNewRetargetChain(FBoneChain& BoneChain) const;` — show user the new retarget chain they are about to create (provides option to edit name)
- L213 _public prototype_ `void PromptToAssignGoalToChain(FName NewGoalName) const;` — right after creating a goal, we ask user if they want it assigned to a retarget chain
- L216 _public prototype_ `void PlayAnimationAsset(UAnimationAsset* AssetToPlay);` — play preview animation on running anim instance in editor (before IK)
- L219 _public member_ `TObjectPtr<UIKRigController> AssetController;` — all modifications to the data model should go through this controller
- L222 _public member_ `UDebugSkelMeshComponent* SkelMeshComponent;` — viewport skeletal mesh
- L225 _public member_ `TObjectPtr<UIKRigAnimInstance> AnimInstance;` — viewport anim instance
- L228 _public member_ `TWeakPtr<FIKRigEditorToolkit> EditorToolkit;` — the persona toolkit
- L231 _public member_ `FRetargetChainAnalyzer ChainAnalyzer;` — used to analyze a retarget chain
- L234 _public member_ `bool bManipulatingGoals = false;` — UI and viewport selection state
- L237 _public prototype_ `EIKRigSelectionType GetLastSelectedType() const;` — record which part of the UI was last selected
- L238 _public prototype_ `void SetLastSelectedType(EIKRigSelectionType SelectionType);`
- L242 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override` — FGCObject interface
- L248 _public function_ `virtual FString GetReferencerName() const override`
- L252 _public prototype_ `TObjectPtr<UIKRigBoneDetails> CreateBoneDetails(const TSharedPtr<FIKRigTreeElement const>& InItem) const;` — UIKRigBoneDetails factory *
- L256 _private prototype_ `TArray<TSharedPtr<FIKRigTreeElement>> FilterByFirstItemType( const TArray<TSharedPtr<FIKRigTreeElement>>& InItems, TFunctionRef<TSubclassOf<UObject>(const TSharedPtr<FIKRigTreeElement>&)> GetTypeOfItem) const;`
- L261 _private member_ `TSharedPtr<IDetailsView> DetailsView;` — asset properties tab
- L264 _private member_ `TSharedPtr<SIKRigHierarchy> SkeletonView;` — the skeleton tree view
- L267 _private member_ `TSharedPtr<SIKRigSolverStack> SolverStackView;` — the solver stack view
- L270 _private member_ `TSharedPtr<SIKRigRetargetChainList> RetargetingView;` — the solver stack view
- L273 _private member_ `TSharedPtr<SIKRigAssetBrowser> AssetBrowserView;` — asset browser view
- L276 _private member_ `TSharedPtr<SIKRigOutputLog> OutputLogView;` — output log view
- L279 _private member_ `TSharedPtr<SWindow> MeshPickerWindow;` — when prompting user to assign a skeletal mesh
- L281 _private member_ `EIKRigSelectionType LastSelectedType;`
- L283 _private member_ `mutable TArray<TObjectPtr<UIKRigBoneDetails>> BoneDetails;`
- L286 _private member_ `FDelegateHandle ReinitializeDelegateHandle;` — remove delegate when closing editor

#### struct `FIKRigSolverTypeAndName`  
`struct FIKRigSolverTypeAndName`  
_L292-296_
- L294 _public member_ `FText NiceName;`
- L295 _public member_ `UScriptStruct* SolverType;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API IKRIGEDITOR_API`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RigEditor/IKRigEditorStyle.h` (Public)


#### class `FIKRigEditorStyle`  
`class FIKRigEditorStyle final : public FSlateStyleSet`  
_L12-66_
- inherits: `FSlateStyleSet`
- L16 _public function_ `FIKRigEditorStyle() : FSlateStyleSet("IKRigEditorStyle")`
- L56 _public function_ `static FIKRigEditorStyle& Get()`
- L62 _public function_ `~FIKRigEditorStyle()`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RigEditor/IKRigHitProxies.h` (Public)


#### struct `HIKRigEditorBoneProxy`  
`struct HIKRigEditorBoneProxy : public HHitProxy`  
_L8-18_
- inherits: `HHitProxy`
- L10 _public prototype_ `DECLARE_HIT_PROXY();`
- L12 _public member_ `FName BoneName;`
- L14 _public prototype_ `HIKRigEditorBoneProxy(const FName& InBoneName);`
- L16 _public prototype_ `virtual EMouseCursor::Type GetMouseCursor() override;`
- L17 _public prototype_ `virtual bool AlwaysAllowsTranslucentPrimitives() const override;`

#### struct `HIKRigEditorGoalProxy`  
`struct HIKRigEditorGoalProxy : public HHitProxy`  
_L20-30_
- inherits: `HHitProxy`
- L22 _public prototype_ `DECLARE_HIT_PROXY();`
- L24 _public member_ `FName GoalName;`
- L26 _public prototype_ `HIKRigEditorGoalProxy(const FName& InGoalName);`
- L28 _public prototype_ `virtual EMouseCursor::Type GetMouseCursor() override;`
- L29 _public prototype_ `virtual bool AlwaysAllowsTranslucentPrimitives() const override;`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RigEditor/IKRigMode.h` (Public)


#### class `FIKRigMode`  
`class FIKRigMode : public FApplicationMode`  
_L11-29_
- inherits: `FApplicationMode`
- L16 _public prototype_ `FIKRigMode(TSharedRef<class FWorkflowCentricApplication> InHostingApp, TSharedRef<class IPersonaPreviewScene> InPreviewScene);`
- L19 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;` — FApplicationMode interface
- L25 _protected member_ `TWeakPtr<FIKRigEditorToolkit> IKRigEditorPtr;` — The hosting app
- L28 _protected member_ `FWorkflowAllowedTabSet TabFactories;` — The tab factories we support

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RigEditor/IKRigOutputLogTabSummoner.h` (Public)


#### struct `FIKRigOutputLogTabSummoner`  
`struct FIKRigOutputLogTabSummoner : public FWorkflowTabFactory`  
_L10-21_
- inherits: `FWorkflowTabFactory`
- L13 _public member_ `static const FName TabID;`
- L15 _public prototype_ `FIKRigOutputLogTabSummoner(const TSharedRef<FIKRigEditorToolkit>& InIKRigEditor);`
- L16 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L17 _public prototype_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override;`
- L20 _protected member_ `TWeakPtr<FIKRigEditorToolkit> IKRigEditor;`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RigEditor/IKRigRetargetChainTabSummoner.h` (Public)


#### struct `FIKRigRetargetChainTabSummoner`  
`struct FIKRigRetargetChainTabSummoner : public FWorkflowTabFactory`  
_L10-21_
- inherits: `FWorkflowTabFactory`
- L13 _public member_ `static const FName TabID;`
- L15 _public prototype_ `FIKRigRetargetChainTabSummoner(const TSharedRef<FIKRigEditorToolkit>& InIKRigEditor);`
- L16 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L17 _public prototype_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override;`
- L20 _protected member_ `TWeakPtr<FIKRigEditorToolkit> IKRigEditor;`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RigEditor/IKRigSkeletonCommands.h` (Public)


#### class `FIKRigSkeletonCommands`  
`class FIKRigSkeletonCommands : public TCommands<FIKRigSkeletonCommands>`  
_L9-61_
- inherits: `TCommands<FIKRigSkeletonCommands>`
- L12 _public function_ `FIKRigSkeletonCommands() : TCommands<FIKRigSkeletonCommands> ( "IKRigSkeleton", NSLOCTEXT("Contexts", "IKRigSkeleton", "IK Rig Skeleton"), NAME_None, FIKRigEditorStyle::Get().GetStyleSetName()`
- L22 _public member_ `TSharedPtr< FUICommandInfo > NewGoal;` — create new goal on selected bone
- L24 _public member_ `TSharedPtr< FUICommandInfo > DeleteElement;` — delete selected element
- L26 _public member_ `TSharedPtr< FUICommandInfo > ConnectGoalToSolver;` — add goal to selected solvers
- L28 _public member_ `TSharedPtr< FUICommandInfo > DisconnectGoalFromSolver;` — remove goal to selected solvers
- L31 _public member_ `TSharedPtr< FUICommandInfo > SetStartBoneOnSolver;` — set root bone on selected solvers
- L34 _public member_ `TSharedPtr< FUICommandInfo > SetEndBoneOnSolver;` — set end bone on selected solvers (Pole Solvers only)
- L37 _public member_ `TSharedPtr< FUICommandInfo > AddBoneSettings;` — add bone setting to bone
- L39 _public member_ `TSharedPtr< FUICommandInfo > RemoveBoneSettings;` — remove bone setting from bone
- L42 _public member_ `TSharedPtr< FUICommandInfo > ExcludeBone;` — remove bone from solve
- L44 _public member_ `TSharedPtr< FUICommandInfo > IncludeBone;` — add bone to solve
- L47 _public member_ `TSharedPtr< FUICommandInfo > NewRetargetChain;` — create retarget chain
- L49 _public member_ `TSharedPtr< FUICommandInfo > SetPelvis;` — set the pelvis bone
- L51 _public member_ `TSharedPtr< FUICommandInfo > ClearPelvis;` — clear the pelvis bone
- L54 _public member_ `TSharedPtr< FUICommandInfo > RenameGoal;` — rename selected goal
- L57 _public member_ `TSharedPtr< FUICommandInfo > RefreshHierarchy;` — reload the hierarchy
- L60 _public prototype_ `virtual void RegisterCommands() override;` — initialize commands

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RigEditor/IKRigSkeletonTabSummoner.h` (Public)


#### struct `FIKRigSkeletonTabSummoner`  
`struct FIKRigSkeletonTabSummoner : public FWorkflowTabFactory`  
_L10-21_
- inherits: `FWorkflowTabFactory`
- L13 _public member_ `static const FName TabID;`
- L15 _public prototype_ `FIKRigSkeletonTabSummoner(const TSharedRef<FIKRigEditorToolkit>& InIKRigEditor);`
- L16 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L17 _public prototype_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override;`
- L20 _protected member_ `TWeakPtr<FIKRigEditorToolkit> IKRigEditor;`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RigEditor/IKRigSolverStackTabSummoner.h` (Public)


#### struct `FIKRigSolverStackTabSummoner`  
`struct FIKRigSolverStackTabSummoner : public FWorkflowTabFactory`  
_L10-21_
- inherits: `FWorkflowTabFactory`
- L13 _public member_ `static const FName TabID;`
- L15 _public prototype_ `FIKRigSolverStackTabSummoner(const TSharedRef<FIKRigEditorToolkit>& InIKRigEditor);`
- L16 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L17 _public prototype_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override;`
- L20 _protected member_ `TWeakPtr<FIKRigEditorToolkit> IKRigEditor;`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RigEditor/IKRigStructViewer.h` (Public)


#### struct `FIKRigStructToView`  
`struct FIKRigStructToView`  
_L17-53_
- L20 _public member_ `const UScriptStruct* Type = nullptr;` — the type that corresponds to the struct memory returned by the StructMemoryProvider
- L24 _public member_ `TFunction<uint8*()> MemoryProvider;` — provides the memory address of the struct to edit (refreshed after undo/redo) NOTE: we can't just pass in raw pointers to the struct memory because these can be destroyed after a transaction. So instead we pass in TFunction callbacks that get the latest memory locations when the details panel is refreshed.
- L26 _public member_ `TWeakObjectPtr<UObject> Owner = nullptr;` — a UObject that owns the struct (this is what will be transacted when the property is edited)
- L28 _public member_ `FName UniqueName;` — a unique identifier that callbacks can use to know what struct was modified
- L30 _public function_ `void Reset()`
- L38 _public function_ `bool IsValid() const`

#### class `UIKRigStructViewer`  
`class UIKRigStructViewer : public UObject, public IBoneReferenceSkeletonProvider`  
_L60-157_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UObject,IBoneReferenceSkeletonProvider`
- desc: a thin wrapper around UStruct data to display in a details panel this is a generic wrapper that works for any struct it is intended to work with FIKRigStructViewerCustomization which simply puts the entire struct in the details panel if you need customization, you need to work with UIKRigStructWrapperBase which allows customized derived classes
- L69 _public function_ `void SetStructToView(const FIKRigStructToView& InStructToView)` — Configures an instance of a struct to display in the details panel with undo/redo support. @param InStructToView the struct to view (see FStructToView for details)
- L74 _public function_ `virtual bool IsValid() const`
- L79 _public function_ `void Reset()`
- L84 _public function_ `TSharedPtr<FStructOnScope>& GetStructOnScope()`
- L103 _public function_ `FName GetTypeName() const`
- L117 _public function_ `UObject* GetStructOwner() const`
- L122 _public prototype_ `void TriggerReinitializationIfNeeded(const FPropertyChangedEvent& InEvent);`
- L124 _public prototype_ `void SetupPropertyEditingCallbacks(const TSharedPtr<IPropertyHandle>& InProperty);`
- L127 _public prototype_ `virtual USkeleton* GetSkeleton(bool& bInvalidSkeletonIsError, const IPropertyHandle* PropertyHandle) override;` — IBoneReferenceSkeletonProvider overrides.
- L132 _protected prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnNeedsReinitialized, const FName& , const FPropertyChangedEvent& );`
- L133 _protected member_ `FOnNeedsReinitialized NeedsReinitializedDelegate;`
- L135 _protected prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPreEditProperty, const FName& , const FProperty* );`
- L136 _protected member_ `FOnPreEditProperty PreEditPropertyDelegate;`
- L138 _protected prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPostEditProperty, const FName& , const FPropertyChangedEvent& );`
- L139 _protected member_ `FOnPostEditProperty PostEditPropertyDelegate;`
- L142 _protected member_ `TSharedPtr<FStructOnScope> StructOnScope;` — a wrapper of the struct sent to the details panel
- L144 _protected member_ `FIKRigStructToView StructToView;` — the data needed to display and edit an instance of a struct in memory
- L150 _public function_ `FOnNeedsReinitialized& OnNeedsReinitialized()` — attach a delegate to be notified whenever a property is edited that requires the system to be reinitialized NOTE: This happens in a few hard-coded special cases or for any property marked with the meta tag: ReinitializeOnEdit
- L153 _public function_ `FOnPreEditProperty& OnPreEditProperty()` — attach a delegate to be notified BEFORE a property is edited
- L156 _public function_ `FOnPostEditProperty& OnPostEditProperty()` — attach a delegate to be notified AFTER a property is edited

#### class `FIKRigStructViewerCustomization`  
`class FIKRigStructViewerCustomization : public IDetailCustomization`  
_L159-171_
- inherits: `IDetailCustomization`
- L162 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L165 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L168 _public prototype_ `static TArray<IDetailPropertyRow*> AddAllPropertiesToCategoryGroups( const TSharedPtr<FStructOnScope>& StructData, IDetailLayoutBuilder& InDetailBuilder);`

#### class `UIKRigStructWrapperBase`  
`class UIKRigStructWrapperBase : public UIKRigStructViewer`  
_L176-228_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UIKRigStructViewer`
- desc: this is meant to be subclassed by a type that contains a UProperty of a struct to be edited similar to UIKRigStructViewer but supports multi-struct editing and greater customization
- L182 _public prototype_ `void Initialize(FIKRigStructToView& InStructToWrap, const FName& InWrapperPropertyName);`
- L184 _public prototype_ `void InitializeWithRetargeter(FIKRigStructToView& InStructToWrap, const FName& InWrapperPropertyName, UIKRetargeterController* InRetargeterController);`
- L186 _public prototype_ `virtual bool IsValid() const override;`
- L188 _public function_ `FName GetWrapperPropertyName() const`
- L190 _public function_ `bool IsPropertyHidden(const FName& InPropertyName) const`
- L192 _public prototype_ `void SetPropertyHidden(const FName& InPropertyName, bool bHidden);`
- L194 _public prototype_ `void UpdateWrappedStructWithLatestValues();`
- L196 _public prototype_ `void UpdateWrapperStructWithLatestValues();`
- L198 _public prototype_ `virtual void PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent ) override;`
- L210 _public function_ `static TSubclassOf<UIKRigStructWrapperBase> GetStructWrapperFromMetaData(const UScriptStruct* S)` — NOTE: How to add multi-edit support to IK Rig settings structs. IK Rig settings structs can supply a "UIWrapper" meta data string with the path to a custom wrapper class to be displayed in the details panel when editing that struct. In order to ensure that edits to the wrapper are pushed back to the actual struct-to-be-edited, the wrapper must inherit from UIKRigStructWrapperBase. This stores a pointer to the original memory and triggers callbacks when properties are edited to push those values back to the struct being edited. By default, only a single struct under a UProperty named "Settings" will be displayed in the details panel. See example subclasses of UIKRigStructWrapperBase.
- L225 _private member_ `TArray<FName> PropertiesToHide;`
- L226 _private member_ `FName WrapperPropertyName;`
- L227 _private member_ `FProperty* WrapperProperty;`

#### class `FIKRigStructWrapperCustomization`  
`class FIKRigStructWrapperCustomization : public IDetailCustomization`  
_L230-238_
- inherits: `IDetailCustomization`
- L233 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L236 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface

#### struct `FIKRigStructWrapperBucket`  
`struct FIKRigStructWrapperBucket`  
_L242-248_
- reflection: `USTRUCT()`
- desc: NOTE: this is a dummy wrapper around TArray<TObjectPtr<>> that is necessary because we cannot store TArray<rawpointer> as a TMap value in the pool
- L247 _public member_ `TArray<TObjectPtr<UIKRigStructWrapperBase>> Items;` — `UPROPERTY(Transient)`

#### struct `FIKRigStructWrapperPool`  
`struct FIKRigStructWrapperPool`  
_L251-305_
- reflection: `USTRUCT()`
- L257 _public function_ `void Init(UObject* InOuter)` — call once to give the pool an owning UObject to prevent GC, otherwise uses GetTransientPackage()
- L261 _public function_ `TArray<UIKRigStructWrapperBase*> GetStructWrappers(int32 Num, TSubclassOf<UIKRigStructWrapperBase> InType)` — get (or lazily instantiate) Num wrappers of the requested subclass. NOTE: buckets will grow, but never shrink
- L300 _private member_ `TWeakObjectPtr<UObject> CreationOuter;` — `UPROPERTY(Transient)` — used as the Outer for all pooled objects
- L304 _private member_ `TMap<TSubclassOf<UIKRigStructWrapperBase>, FIKRigStructWrapperBucket> Pool;` — `UPROPERTY(Transient)` — one bucket per subclass; values are GC-tracked via TObjectPtr

#### Free symbols / members of external scopes

- L132 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnNeedsReinitialized, const FName& , const FPropertyChangedEvent& );`
- L135 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPreEditProperty, const FName& , const FProperty* );`
- L138 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPostEditProperty, const FName& , const FPropertyChangedEvent& );`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RigEditor/IKRigStructWrappers.h` (Public)


#### class `UBodyMoverSettingsWrapper`  
`class UBodyMoverSettingsWrapper : public UIKRigStructWrapperBase`  
_L22-28_
- reflection: `UCLASS()`
- inherits: `UIKRigStructWrapperBase`
- L27 _public member_ `FIKRigBodyMoverSettings Settings;` — `UPROPERTY(EditAnywhere, Category = "Body Mover Settings")`

#### class `UBodyMoverGoalSettingsWrapper`  
`class UBodyMoverGoalSettingsWrapper : public UIKRigStructWrapperBase`  
_L31-37_
- reflection: `UCLASS()`
- inherits: `UIKRigStructWrapperBase`
- L36 _public member_ `FIKRigBodyMoverGoalSettings Settings;` — `UPROPERTY(EditAnywhere, Category = "Body Mover Goal Settings")`

#### class `UFBIKSettingsWrapper`  
`class UFBIKSettingsWrapper : public UIKRigStructWrapperBase`  
_L44-50_
- reflection: `UCLASS()`
- inherits: `UIKRigStructWrapperBase`
- L49 _public member_ `FIKRigFBIKSettings Settings;` — `UPROPERTY(EditAnywhere, Category = "Full-Body IK Settings")`

#### class `UFBIKGoalSettingsWrapper`  
`class UFBIKGoalSettingsWrapper : public UIKRigStructWrapperBase`  
_L53-59_
- reflection: `UCLASS()`
- inherits: `UIKRigStructWrapperBase`
- L58 _public member_ `FIKRigFBIKGoalSettings Settings;` — `UPROPERTY(EditAnywhere, Category = "FBIK Goal Settings")`

#### class `UFBIKBoneSettingsWrapper`  
`class UFBIKBoneSettingsWrapper : public UIKRigStructWrapperBase`  
_L62-68_
- reflection: `UCLASS()`
- inherits: `UIKRigStructWrapperBase`
- L67 _public member_ `FIKRigFBIKBoneSettings Settings;` — `UPROPERTY(EditAnywhere, Category = "FBIK Bone Settings")`

#### class `ULimbSolverSettingsWrapper`  
`class ULimbSolverSettingsWrapper : public UIKRigStructWrapperBase`  
_L75-81_
- reflection: `UCLASS()`
- inherits: `UIKRigStructWrapperBase`
- L80 _public member_ `FIKRigLimbSolverSettings Settings;` — `UPROPERTY(EditAnywhere, Category = "Limb Solver Settings")`

#### class `UPoleSolverSettingsWrapper`  
`class UPoleSolverSettingsWrapper : public UIKRigStructWrapperBase`  
_L88-94_
- reflection: `UCLASS()`
- inherits: `UIKRigStructWrapperBase`
- L93 _public member_ `FIKRigPoleSolverSettings Settings;` — `UPROPERTY(EditAnywhere, Category = "Pole Solver Settings")`

#### class `USetTransformSettingsWrapper`  
`class USetTransformSettingsWrapper : public UIKRigStructWrapperBase`  
_L101-107_
- reflection: `UCLASS()`
- inherits: `UIKRigStructWrapperBase`
- L106 _public member_ `FIKRigSetTransformSettings Settings;` — `UPROPERTY(EditAnywhere, Category = "Set Transform Settings")`

#### class `UStretchLimbSettingsWrapper`  
`class UStretchLimbSettingsWrapper : public UIKRigStructWrapperBase`  
_L114-120_
- reflection: `UCLASS()`
- inherits: `UIKRigStructWrapperBase`
- L119 _public member_ `FIKRigStretchLimbSettings Settings;` — `UPROPERTY(EditAnywhere, Category = "Stretch Limb Settings")`

#### class `UStretchLimbBoneSettingsWrapper`  
`class UStretchLimbBoneSettingsWrapper : public UIKRigStructWrapperBase`  
_L123-129_
- reflection: `UCLASS()`
- inherits: `UIKRigStructWrapperBase`
- L128 _public member_ `FIKRigStretchLimbBoneSettings Settings;` — `UPROPERTY(EditAnywhere, Category = "Stretch Limb Bone Settings")`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RigEditor/IKRigThumbnailRenderer.h` (Public)


#### class `UIKRigThumbnailRenderer`  
`class UIKRigThumbnailRenderer : public USkeletalMeshThumbnailRenderer`  
_L14-26_
- reflection: `UCLASS(config=Editor, MinimalAPI)`
- inherits: `USkeletalMeshThumbnailRenderer`
- desc: this thumbnail renderer displays a given IK Rig in the asset icon
- L19 _private prototype_ `virtual bool CanVisualizeAsset(UObject* Object) override;`
- L20 _private prototype_ `virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget*, FCanvas* Canvas, bool bAdditionalViewFamily) override;`
- L21 _private prototype_ `virtual EThumbnailRenderFrequency GetThumbnailRenderFrequency(UObject* Object) const override;`
- L25 _private prototype_ `USkeletalMesh* GetPreviewMeshFromRig(UObject* Object) const;`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RigEditor/IKRigToolkit.h` (Public)


#### class `FIKRigEditorToolkit`  
`class FIKRigEditorToolkit : public FPersonaAssetEditorToolkit, public IHasPersonaToolkit, public FSelfRegisteringEditorUndoClient, public FTickableEditorObject`  
_L20-85_
- inherits: `FPersonaAssetEditorToolkit,IHasPersonaToolkit,FSelfRegisteringEditorUndoClient,FTickableEditorObject`
- L28 _public prototype_ `FIKRigEditorToolkit();`
- L31 _public prototype_ `void InitAssetEditor( const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UIKRigDefinition* IKRigAsset);`
- L37 _public prototype_ `virtual void OnClose() override;` — FAssetEditorToolkit interface
- L38 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;`
- L39 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;`
- L40 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L41 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L42 _public prototype_ `virtual FText GetToolkitName() const override;`
- L43 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L44 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L48 _public prototype_ `virtual void Tick(float DeltaTime) override;` — /  FTickableEditorObject Interface
- L49 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L50 _public prototype_ `virtual TStatId GetStatId() const override;`
- L54 _public function_ `virtual TSharedRef<IPersonaToolkit> GetPersonaToolkit() const override` — IHasPersonaToolkit interface
- L58 _public prototype_ `virtual void PostUndo( bool bSuccess );` — FSelfRegisteringEditorUndoClient interface
- L59 _public prototype_ `virtual void PostRedo(bool bSuccess);`
- L60 _public prototype_ `virtual bool MatchesContext( const FTransactionContext& InContext, const TArray<TPair<UObject*, FTransactionObjectEvent>>& TransactionObjectContexts ) const override;`
- L63 _public function_ `TSharedRef<FIKRigEditorController> GetController() const`
- L66 _public prototype_ `void HandlePreviewSceneCreated(const TSharedRef<IPersonaPreviewScene>& InPersonaPreviewScene);` — tab creation callbacks
- L67 _public prototype_ `void HandleDetailsCreated(const TSharedRef<class IDetailsView>& InDetailsView) const;`
- L68 _public prototype_ `void HandleViewportCreated(const TSharedRef<class IPersonaViewport>& InViewport);`
- L69 _public prototype_ `void HandleOnPreviewSceneSettingsCustomized(IDetailLayoutBuilder& DetailBuilder) const;`
- L75 _private prototype_ `void BindCommands();` — toolbar
- L76 _private prototype_ `void ExtendToolbar();`
- L77 _private prototype_ `void FillToolbar(FToolBarBuilder& ToolbarBuilder);`
- L81 _private member_ `TSharedRef<FIKRigEditorController> EditorController;` — centralized management of selection across skeleton view and viewport
- L84 _private member_ `TSharedPtr<IPersonaToolkit> PersonaToolkit;` — Preview scene to be supplied by IHasPersonaToolkit::GetPersonaToolkit

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace IKRigEditorModes`
- L17 _externvar_ `extern const FName IKRigEditorMode;` (scope `IKRigEditorModes`)

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RigEditor/SIKRigAssetBrowser.h` (Public)


#### class `SIKRigAssetBrowser`  
`class SIKRigAssetBrowser : public SBox`  
_L13-42_
- inherits: `SBox`
- L16 _public function_ `SLATE_BEGIN_ARGS(SIKRigAssetBrowser)`
- L17 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FIKRigEditorController> InEditorController);`
- L23 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;`
- L26 _private prototype_ `void ExecuteFindInContentBrowserAction();`
- L27 _private prototype_ `bool CanExecuteFindInContentBrowserAction();`
- L29 _private prototype_ `void RefreshView();`
- L30 _private prototype_ `void OnPathChange(const FString& NewPath);`
- L31 _private prototype_ `void OnAssetDoubleClicked(const FAssetData& AssetData);`
- L32 _private prototype_ `bool OnShouldFilterAsset(const struct FAssetData& AssetData);`
- L33 _private prototype_ `TSharedPtr<SWidget> OnGetAssetContextMenu(const TArray<FAssetData>& SelectedAssets) const;`
- L35 _private member_ `TWeakPtr<FIKRigEditorController> EditorController;`
- L36 _private member_ `TSharedPtr<SBox> AssetBrowserBox;`
- L37 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L39 _private member_ `FGetCurrentSelectionDelegate GetCurrentSelectionDelegate;` — Used to get the currently selected assets

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RigEditor/SIKRigHierarchy.h` (Public)


#### enum `EIKRigTreeElementType`  
`enum class EIKRigTreeElementType`  
_L22-22_
- L22 _public enumerator_ `enum class EIKRigTreeElementType { BONE, GOAL, GOAL_SETTINGS, BONE_SETTINGS }; class FIKRigTreeElement : public TSharedFromThis<FIKRigTreeElement> { public: FIKRigTreeElement( const FText& InKey,`
- L22 _public enumerator_ `enum class EIKRigTreeElementType { BONE, GOAL, GOAL_SETTINGS, BONE_SETTINGS }; class FIKRigTreeElement : public TSharedFromThis<FIKRigTreeElement> { public: FIKRigTreeElement( const FText& InKey,`
- L22 _public enumerator_ `enum class EIKRigTreeElementType { BONE, GOAL, GOAL_SETTINGS, BONE_SETTINGS }; class FIKRigTreeElement : public TSharedFromThis<FIKRigTreeElement> { public: FIKRigTreeElement( const FText& InKey,`
- L22 _public enumerator_ `enum class EIKRigTreeElementType { BONE, GOAL, GOAL_SETTINGS, BONE_SETTINGS }; class FIKRigTreeElement : public TSharedFromThis<FIKRigTreeElement> { public: FIKRigTreeElement( const FText& InKey,`

#### class `FIKRigTreeElement`  
`class FIKRigTreeElement : public TSharedFromThis<FIKRigTreeElement>`  
_L24-74_
- inherits: `TSharedFromThis<FIKRigTreeElement>`
- L28 _public prototype_ `FIKRigTreeElement( const FText& InKey, EIKRigTreeElementType InType, const TSharedRef<FIKRigEditorController>& InEditorController);`
- L33 _public member_ `FText Key;`
- L34 _public member_ `EIKRigTreeElementType ElementType;`
- L37 _public member_ `bool bIsHidden = false;` — determines if this item is filtered out of the view
- L38 _public member_ `TSharedPtr<FIKRigTreeElement> UnFilteredParent;`
- L40 _public member_ `TSharedPtr<FIKRigTreeElement> Parent;`
- L41 _public member_ `TArray<TSharedPtr<FIKRigTreeElement>> Children;`
- L44 _public member_ `FName EffectorGoalName = NAME_None;` — effector meta-data (if it is an effector)
- L45 _public member_ `int32 EffectorIndex = INDEX_NONE;`
- L48 _public member_ `FName BoneSettingBoneName = NAME_None;` — bone setting meta-data (if it is a bone setting)
- L49 _public member_ `int32 BoneSettingsSolverIndex = INDEX_NONE;`
- L52 _public member_ `FName BoneName = NAME_None;` — name of bone if it is one
- L55 _public member_ `FName GoalName = NAME_None;` — name of goal if it is one
- L58 _public prototype_ `void RequestRename();` — delegate for when the context menu requests a rename
- L59 _public prototype_ `DECLARE_DELEGATE(FOnRenameRequested);`
- L60 _public member_ `FOnRenameRequested OnRenameRequested;`
- L63 _public prototype_ `void GetStruct(const UScriptStruct*& OutType, uint8*& OutMemory) const;` — get the underlying object
- L66 _public prototype_ `FName GetChainName() const;` — get the name of the retarget chain this element belongs to (or NAME_None if not in a chain)
- L70 _private member_ `TWeakPtr<FIKRigEditorController> EditorController;` — centralized editor controls
- L73 _private member_ `mutable TObjectPtr<UIKRigBoneDetails> OptionalBoneDetails = nullptr;` — on demand bone details object

#### class `SIKRigHierarchyItem`  
`class SIKRigHierarchyItem : public SCompoundWidget`  
_L76-95_
- inherits: `SCompoundWidget`
- L78 _private function_ `SLATE_BEGIN_ARGS(SIKRigHierarchyItem)`
- L79 _private prototype_ `SLATE_ARGUMENT(TWeakPtr<FIKRigEditorController>, EditorController) SLATE_ARGUMENT(TWeakPtr<FIKRigTreeElement>, TreeElement) SLATE_ARGUMENT(TWeakPtr<SIKRigHierarchy>, HierarchyView) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L88 _private prototype_ `bool OnVerifyNameChanged(const FText& InText, FText& OutErrorMessage) const;`
- L89 _private prototype_ `void OnNameCommitted(const FText& InText, ETextCommit::Type InCommitType) const;`
- L90 _private prototype_ `FText GetName() const;`
- L92 _private member_ `TWeakPtr<FIKRigTreeElement> WeakTreeElement;`
- L93 _private member_ `TWeakPtr<FIKRigEditorController> EditorController;`
- L94 _private member_ `TWeakPtr<SIKRigHierarchy> HierarchyView;`

#### class `FIKRigSkeletonDragDropOp`  
`class FIKRigSkeletonDragDropOp : public FDecoratedDragDropOp`  
_L97-104_
- inherits: `FDecoratedDragDropOp`
- L100 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FIKRigSkeletonDragDropOp, FDecoratedDragDropOp) static TSharedRef<FIKRigSkeletonDragDropOp> New(TWeakPtr<FIKRigTreeElement> InElement);`
- L102 _public prototype_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;`
- L103 _public member_ `TWeakPtr<FIKRigTreeElement> Element;`

#### class `SIKRigSkeletonRow`  
`class SIKRigSkeletonRow : public SMultiColumnTableRow<TSharedPtr<FIKRigTreeElement>>`  
_L106-149_
- inherits: `SMultiColumnTableRow<TSharedPtr<FIKRigTreeElement>>`
- L110 _public function_ `SLATE_BEGIN_ARGS(SIKRigSkeletonRow)`
- L111 _public function_ `SLATE_ARGUMENT(TSharedPtr<FIKRigEditorController>, EditorController) SLATE_ARGUMENT(TSharedPtr<FIKRigTreeElement>, TreeElement) SLATE_ARGUMENT(TSharedPtr<SIKRigHierarchy>, HierarchyView) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable)`
- L134 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;` — Overridden from SMultiColumnTableRow.  Generates a widget for this column of the list view.
- L138 _public prototype_ `FReply HandleDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — drag and drop
- L139 _public prototype_ `TOptional<EItemDropZone> HandleCanAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<FIKRigTreeElement> TargetItem);`
- L140 _public prototype_ `FReply HandleAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<FIKRigTreeElement> TargetItem);`
- L145 _private member_ `TSharedPtr<STableViewBase> OwnerTable;`
- L146 _private member_ `TWeakPtr<FIKRigTreeElement> WeakTreeElement;`
- L147 _private member_ `TWeakPtr<FIKRigEditorController> EditorController;`
- L148 _private member_ `TWeakPtr<SIKRigHierarchy> HierarchyView;`

#### struct `FIKRigHierarchyFilterOptions`  
`struct FIKRigHierarchyFilterOptions`  
_L151-166_
- L153 _public member_ `bool bShowAll = true;`
- L154 _public member_ `bool bShowOnlyBones = false;`
- L155 _public member_ `bool bShowOnlyGoals = false;`
- L156 _public member_ `bool bShowOnlyBoneSettings = false;`
- L157 _public member_ `bool bHideUnaffectedBones = false;`
- L159 _public function_ `void ResetShowOptions()`

#### struct `FIKRigHierarchyImportSettings`  
`struct FIKRigHierarchyImportSettings`  
_L169-175_
- reflection: `USTRUCT()`
- L174 _public member_ `TObjectPtr<USkeletalMesh> Mesh = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Hierachy Import")`

#### class `SIKRigHierarchy`  
`class SIKRigHierarchy : public SCompoundWidget, public FEditorUndoClient`  
_L179-325_
- inherits: `SCompoundWidget,FEditorUndoClient`
- L182 _public function_ `SLATE_BEGIN_ARGS(SIKRigHierarchy)`
- L185 _public prototype_ `~SIKRigHierarchy() = default;`
- L187 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<FIKRigEditorController> InEditorController);`
- L190 _public prototype_ `static bool IsBoneInSelection(TArray<TSharedPtr<FIKRigTreeElement>>& SelectedBoneItems, const FName& BoneName);` — selection state queries
- L191 _public prototype_ `void GetSelectedBones(TArray<TSharedPtr<FIKRigTreeElement>>& OutBoneItems) const;`
- L192 _public prototype_ `void GetSelectedBoneNames(TArray<FName>& OutSelectedBoneNames) const;`
- L193 _public prototype_ `void GetSelectedGoals(TArray<TSharedPtr<FIKRigTreeElement>>& OutSelectedGoals) const;`
- L194 _public prototype_ `int32 GetNumSelectedGoals();`
- L195 _public prototype_ `void GetSelectedGoalNames(TArray<FName>& OutSelectedGoalNames) const;`
- L196 _public prototype_ `bool IsGoalSelected(const FName& GoalName);`
- L197 _public prototype_ `void AddSelectedItemFromViewport( const FName& ItemName, EIKRigTreeElementType ItemType, const bool bReplace);`
- L201 _public prototype_ `void GetSelectedBoneChains(TArray<FBoneChain>& OutChains) const;`
- L202 _public prototype_ `TArray<TSharedPtr<FIKRigTreeElement>> GetSelectedItems() const;`
- L203 _public prototype_ `bool HasSelectedItems() const;`
- L207 _public prototype_ `bool IsElementConnectedToSolver(TWeakPtr<FIKRigTreeElement> TreeElement, int32 SolverIndex);` — determine if the element is connected to the selected solver
- L209 _public prototype_ `bool IsElementConnectedToAnySolver(TWeakPtr<FIKRigTreeElement> TreeElement);` — determine if the element is connected to ANY solver
- L211 _public prototype_ `bool IsElementExcludedBone(TWeakPtr<FIKRigTreeElement> TreeElement);` — determine if the element is an excluded bone
- L214 _public prototype_ `bool IsSkeletonLoaded() const;` — return true if a skeleton hierarchy has been loaded from an asset
- L216 _public prototype_ `FReply OnImportSkeletonClicked() const;` — import skeletal mesh into the asset
- L220 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);` — SWidget interface
- L224 _private prototype_ `void BindCommands();` — Bind commands that this widget handles
- L227 _private prototype_ `void AddItemToSelection(const TSharedPtr<FIKRigTreeElement>& InItem);` — directly, programmatically add item to selection
- L229 _private prototype_ `void RemoveItemFromSelection(const TSharedPtr<FIKRigTreeElement>& InItem);` — directly, programmatically add item to selection
- L231 _private prototype_ `void ReplaceItemInSelection(const FText& OldName, const FText& NewName);` — directly, programmatically replace item in selection
- L234 _private prototype_ `void HandleNewGoal() const;` — creating / renaming / deleting goals
- L235 _private prototype_ `bool CanAddNewGoal() const;`
- L236 _private prototype_ `void HandleRenameGoal() const;`
- L237 _private prototype_ `bool CanRenameGoal() const;`
- L238 _private prototype_ `void HandleDeleteElements();`
- L239 _private prototype_ `bool CanDeleteElement() const;`
- L243 _private prototype_ `void HandleConnectGoalToSolver();` — connecting/disconnecting goals to solvers
- L244 _private prototype_ `void HandleDisconnectGoalFromSolver();`
- L245 _private prototype_ `bool CanConnectGoalToSolvers() const;`
- L246 _private prototype_ `bool CanDisconnectGoalFromSolvers() const;`
- L247 _private prototype_ `void ConnectSelectedGoalsToSelectedSolvers(bool bConnect);`
- L248 _private prototype_ `int32 GetNumSelectedGoalToSolverConnections(bool bCountOnlyConnected) const;`
- L252 _private prototype_ `void HandleSetRootBoneOnSolvers();` — setting root bone
- L253 _private prototype_ `bool CanSetRootBoneOnSolvers();`
- L257 _private prototype_ `void HandleSetEndBoneOnSolvers();` — setting end bone
- L258 _private prototype_ `bool CanSetEndBoneOnSolvers() const;`
- L259 _private prototype_ `bool HasEndBoneCompatibleSolverSelected() const;`
- L263 _private prototype_ `void HandleAddBoneSettings();` — per-bone settings
- L264 _private prototype_ `bool CanAddBoneSettings();`
- L265 _private prototype_ `void HandleRemoveBoneSettings();`
- L266 _private prototype_ `bool CanRemoveBoneSettings();`
- L270 _private prototype_ `void HandleExcludeBone();` — exclude/include bones
- L271 _private prototype_ `bool CanExcludeBone();`
- L272 _private prototype_ `void HandleIncludeBone();`
- L273 _private prototype_ `bool CanIncludeBone();`
- L277 _private prototype_ `void HandleNewRetargetChain();` — retarget chains
- L278 _private prototype_ `bool CanAddNewRetargetChain();`
- L279 _private prototype_ `void HandleSetRetargetRoot();`
- L280 _private prototype_ `bool CanSetPelvis();`
- L281 _private prototype_ `void HandleClearPelvis();`
- L282 _private prototype_ `bool CanClearPelvis();`
- L286 _private prototype_ `bool CanRefreshHierarchy();` — refresh the bone hierarchy
- L287 _private prototype_ `void HandleRefreshHierarchy();`
- L290 _private member_ `TWeakPtr<FIKRigEditorController> EditorController;` — centralized editor controls (facilitate cross-communication between multiple UI elements)
- L293 _private member_ `TSharedPtr<FUICommandList> CommandList;` — command list we bind to
- L296 _private member_ `TSharedPtr<SIKRigSkeletonTreeView> TreeView;` — tree view widget
- L297 _private member_ `TArray<TSharedPtr<FIKRigTreeElement>> RootElements;`
- L298 _private member_ `TArray<TSharedPtr<FIKRigTreeElement>> AllElements;`
- L301 _private prototype_ `TSharedRef<SWidget> CreateFilterMenuWidget();` — filtering the tree with search box
- L302 _private prototype_ `void OnFilterTextChanged(const FText& SearchText);`
- L303 _private member_ `TSharedPtr<FTextFilterExpressionEvaluator> TextFilter;`
- L304 _private member_ `FIKRigHierarchyFilterOptions FilterOptions;`
- L307 _private prototype_ `void RefreshTreeView(bool IsInitialSetup=false);` — tree view callbacks
- L308 _private prototype_ `void HandleGetChildrenForTree(TSharedPtr<FIKRigTreeElement> InItem, TArray<TSharedPtr<FIKRigTreeElement>>& OutChildren);`
- L309 _private prototype_ `void OnSelectionChanged(TSharedPtr<FIKRigTreeElement> Selection, ESelectInfo::Type SelectInfo);`
- L310 _private prototype_ `TSharedRef< SWidget > CreateAddNewMenu();`
- L311 _private prototype_ `TSharedPtr< SWidget > CreateContextMenu();`
- L312 _private prototype_ `void OnItemClicked(TSharedPtr<FIKRigTreeElement> InItem);`
- L313 _private prototype_ `void OnItemDoubleClicked(TSharedPtr<FIKRigTreeElement> InItem);`
- L314 _private prototype_ `void OnSetExpansionRecursive(TSharedPtr<FIKRigTreeElement> InItem, bool bShouldBeExpanded);`
- L315 _private prototype_ `void SetExpansionRecursive(TSharedPtr<FIKRigTreeElement> InElement, bool bTowardsParent, bool bShouldBeExpanded);`
- L316 _private prototype_ `void FillContextMenu(FMenuBuilder& MenuBuilder);`
- L319 _private member_ `FIKRigHierarchyImportSettings ImportSettings;`

#### Free symbols / members of external scopes

- L59 _delegate_ `DECLARE_DELEGATE(FOnRenameRequested);`
- L177 _typedef_ `typedef SBaseHierarchyTreeView<FIKRigTreeElement> SIKRigSkeletonTreeView;`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RigEditor/SIKRigOutputLog.h` (Public)


#### class `SIKRigOutputLog`  
`class SIKRigOutputLog : public SBox`  
_L11-28_
- inherits: `SBox`
- L16 _public function_ `SLATE_BEGIN_ARGS(SIKRigOutputLog)`
- L17 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FName& InLogName);`
- L21 _public prototype_ `void ClearLog() const;`
- L26 _private member_ `TSharedPtr<SWidget> OutputLogWidget;` — the output log
- L27 _private member_ `TSharedPtr<IMessageLogListing> MessageLogListing;`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RigEditor/SIKRigRetargetChainList.h` (Public)


#### class `FRetargetChainElement`  
`class FRetargetChainElement`  
_L26-49_
- L30 _public prototype_ `TSharedRef<ITableRow> MakeListRowWidget( const TSharedRef<STableViewBase>& InOwnerTable, TSharedRef<FRetargetChainElement> InStackElement, TSharedPtr<SIKRigRetargetChainList> InChainList);`
- L35 _public function_ `static TSharedRef<FRetargetChainElement> Make(const FName& InChainName)`
- L40 _public member_ `FName ChainName;`
- L45 _private function_ `FRetargetChainElement(const FName& InChainName) : ChainName(InChainName)` — Hidden constructor, always use Make above
- L48 _private function_ `FRetargetChainElement()` — Hidden constructor, always use Make above

#### class `SIKRigRetargetChainRow`  
`class SIKRigRetargetChainRow : public SMultiColumnTableRow<TSharedPtr<FRetargetChainElement>>`  
_L52-86_
- inherits: `SMultiColumnTableRow<TSharedPtr<FRetargetChainElement>>`
- L56 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, TSharedRef<FRetargetChainElement> InChainElement, TSharedPtr<SIKRigRetargetChainList> InChainList);`
- L63 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;` — Overridden from SMultiColumnTableRow.  Generates a widget for this column of the table row.
- L67 _private prototype_ `const FReferenceSkeleton& GetReferenceSkeleton() const;`
- L69 _private prototype_ `TSharedRef<SWidget> MakeGoalComboEntryWidget(TSharedPtr<FString> InItem) const;`
- L71 _private prototype_ `void OnStartBoneComboSelectionChanged(FName InName) const;`
- L72 _private prototype_ `void OnEndBoneComboSelectionChanged(FName InName) const;`
- L73 _private prototype_ `void OnGoalComboSelectionChanged(TSharedPtr<FString> InGoalName, ESelectInfo::Type SelectInfo);`
- L75 _private prototype_ `FName GetStartBoneName(bool& bMultipleValues) const;`
- L76 _private prototype_ `FName GetEndBoneName(bool& bMultipleValues) const;`
- L77 _private prototype_ `FText GetGoalName() const;`
- L79 _private prototype_ `void OnRenameChain(const FText& InText, ETextCommit::Type ) const;`
- L81 _private member_ `TArray<TSharedPtr<FString>> GoalOptions;`
- L82 _private member_ `TWeakPtr<FRetargetChainElement> ChainElement;`
- L83 _private member_ `TWeakPtr<SIKRigRetargetChainList> ChainList;`

#### struct `FIKRigRetargetChainSettings`  
`struct FIKRigRetargetChainSettings`  
_L89-109_
- reflection: `USTRUCT()`
- L93 _public function_ `FIKRigRetargetChainSettings()`
- L95 _public function_ `FIKRigRetargetChainSettings(FName InChainName, const FName& InStartBone, const FName& InEndBone) : ChainName(InChainName) , StartBone(InStartBone) , EndBone(InEndBone)`
- L102 _public member_ `FName ChainName;` — `UPROPERTY(EditAnywhere, Category = "Bone Chain")`
- L105 _public member_ `FName StartBone;` — `UPROPERTY(VisibleAnywhere, Category = "Bone Chain")`
- L108 _public member_ `FName EndBone;` — `UPROPERTY(VisibleAnywhere, Category = "Bone Chain")`

#### struct `FChainFilterOptions`  
`struct FChainFilterOptions`  
_L111-116_
- L113 _public member_ `bool bHideSingleBoneChains = false;`
- L114 _public member_ `bool bShowOnlyIKChains = false;`
- L115 _public member_ `bool bShowOnlyMissingBoneChains = false;`

#### class `SIKRigRetargetChainList`  
`class SIKRigRetargetChainList : public SCompoundWidget, public FEditorUndoClient`  
_L120-183_
- inherits: `SCompoundWidget,FEditorUndoClient`
- L123 _public function_ `SLATE_BEGIN_ARGS(SIKRigRetargetChainList)`
- L124 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FIKRigEditorController> InEditorController);`
- L128 _public prototype_ `TArray<FName> GetSelectedChains() const;`
- L133 _private member_ `TSharedPtr<FUICommandList> CommandList;` — menu for adding new solver commands
- L136 _private member_ `TWeakPtr<FIKRigEditorController> EditorController;` — editor controller
- L139 _private prototype_ `void OnPelvisBoneComboSelectionChanged(FName InName);` — pelvis / root bone widgets
- L140 _private prototype_ `void OnRootBoneComboSelectionChanged(FName InName);`
- L141 _private prototype_ `FName GetPelvisBoneName(bool& bMultipleValues) const;`
- L142 _private prototype_ `FName GetRootBoneName(bool& bMultipleValues) const;`
- L143 _private prototype_ `const FReferenceSkeleton& GetReferenceSkeleton() const;`
- L146 _private member_ `TSharedPtr<SRetargetChainListViewType> ListView;` — list view
- L147 _private member_ `TArray< TSharedPtr<FRetargetChainElement> > ListViewItems;`
- L151 _private prototype_ `TSharedRef<SWidget> CreateFilterMenuWidget();` — filtering the list with search box
- L152 _private prototype_ `void OnFilterTextChanged(const FText& SearchText);`
- L153 _private member_ `TSharedPtr<FTextFilterExpressionEvaluator> TextFilter;`
- L154 _private member_ `FChainFilterOptions ChainFilterOptions;`
- L157 _private prototype_ `bool IsAddChainEnabled() const;` — callback when "Add New Chain" clicked
- L160 _private prototype_ `void OnItemClicked(TSharedPtr<FRetargetChainElement> InItem);` — when a chain is clicked on in the stack view
- L163 _private prototype_ `TSharedRef<ITableRow> MakeListRowWidget(TSharedPtr<FRetargetChainElement> InElement, const TSharedRef<STableViewBase>& OwnerTable);` — list view generate row callback
- L166 _private prototype_ `void RefreshView();` — call to refresh the list view
- L169 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);` — SWidget interface
- L173 _private prototype_ `TSharedPtr< SWidget > CreateContextMenu();` — list view OnContextMenuOpening callback
- L176 _private prototype_ `void SortChainList();` — sort chain list callback
- L179 _private prototype_ `void MirrorSelectedChains() const;` — mirror the selected chains (right-click menu callback)

#### Free symbols / members of external scopes

- L118 _typedef_ `typedef SListView< TSharedPtr<FRetargetChainElement> > SRetargetChainListViewType;`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/RigEditor/SIKRigSolverStack.h` (Public)


#### class `FSolverStackElement`  
`class FSolverStackElement`  
_L20-46_
- L24 _public prototype_ `TSharedRef<ITableRow> MakeListRowWidget( const TSharedRef<STableViewBase>& InOwnerTable, TSharedRef<FSolverStackElement> InStackElement, TSharedPtr<SIKRigSolverStack> InSolverStack);`
- L29 _public function_ `static TSharedRef<FSolverStackElement> Make(FText DisplayName, int32 SolverIndex)`
- L34 _public member_ `FText DisplayName;`
- L35 _public member_ `int32 IndexInStack;`
- L39 _private function_ `FSolverStackElement(FText InDisplayName, int32 SolverIndex) : DisplayName(InDisplayName), IndexInStack(SolverIndex)` — Hidden constructor, always use Make above
- L45 _private function_ `FSolverStackElement()` — Hidden constructor, always use Make above

#### class `SIKRigSolverStackItem`  
`class SIKRigSolverStackItem : public STableRow<TSharedPtr<FSolverStackElement>>`  
_L48-66_
- inherits: `STableRow<TSharedPtr<FSolverStackElement>>`
- L52 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable, TSharedRef<FSolverStackElement> InStackElement, TSharedPtr<SIKRigSolverStack> InSolverStack);`
- L58 _public prototype_ `bool GetWarningMessage(FText& Message) const;`
- L60 _public prototype_ `bool IsSolverEnabled() const;`
- L63 _private prototype_ `const FIKRigSolverBase* GetSolver(const bool bFromAsset) const;`
- L64 _private member_ `TWeakPtr<FSolverStackElement> StackElement;`
- L65 _private member_ `TWeakPtr<SIKRigSolverStack> SolverStack;`

#### class `FIKRigSolverStackDragDropOp`  
`class FIKRigSolverStackDragDropOp : public FDecoratedDragDropOp`  
_L68-75_
- inherits: `FDecoratedDragDropOp`
- L71 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FIKRigSolverStackDragDropOp, FDecoratedDragDropOp) static TSharedRef<FIKRigSolverStackDragDropOp> New(TWeakPtr<FSolverStackElement> InElement);`
- L73 _public prototype_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;`
- L74 _public member_ `TWeakPtr<FSolverStackElement> Element;`

#### struct `FIKRigSolverMetaData`  
`struct FIKRigSolverMetaData`  
_L77-81_
- L79 _public member_ `UScriptStruct* ScriptStruct;`
- L80 _public member_ `FText NiceName;`

#### class `SIKRigSolverStack`  
`class SIKRigSolverStack : public SCompoundWidget, public FEditorUndoClient`  
_L84-143_
- inherits: `SCompoundWidget,FEditorUndoClient`
- L87 _public function_ `SLATE_BEGIN_ARGS(SIKRigSolverStack)`
- L90 _public prototype_ `~SIKRigSolverStack();`
- L92 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<FIKRigEditorController> InEditorController);`
- L96 _private member_ `TSharedPtr<FUICommandList> CommandList;` — menu for adding new solver commands
- L99 _private member_ `TWeakPtr<FIKRigEditorController> EditorController;` — editor controller
- L102 _private member_ `TSharedPtr<SSolverStackListViewType> ListView;` — the solver stack list view
- L103 _private member_ `TArray< TSharedPtr<FSolverStackElement> > ListViewItems;`
- L106 _private prototype_ `TSharedRef<SWidget> CreateAddNewMenuWidget();` — solver stack menu
- L107 _private prototype_ `void BuildAddNewMenu(FMenuBuilder& MenuBuilder);`
- L108 _private prototype_ `bool IsAddSolverEnabled() const;`
- L112 _private member_ `TArray<FIKRigSolverMetaData> AllSolversMetaData;` — all type info about all available solver types (cached at startup)
- L113 _private prototype_ `void CacheSolverMetaData();`
- L116 _private prototype_ `void AddNewSolver(UScriptStruct* SolverType);` — menu command callback for adding a new solver
- L118 _private prototype_ `void DeleteSolver(TSharedPtr<FSolverStackElement> SolverToDelete);` — delete solver from stack
- L120 _private prototype_ `void OnSelectionChanged(TSharedPtr<FSolverStackElement> InItem, ESelectInfo::Type SelectInfo);` — when a solver is selected on in the stack view
- L122 _private prototype_ `void OnItemClicked(TSharedPtr<FSolverStackElement> InItem);` — when a solver is clicked on in the stack view
- L123 _private prototype_ `void ShowDetailsForItems(const TArray<TSharedPtr<FSolverStackElement>>& InItems);`
- L126 _private prototype_ `TSharedRef<ITableRow> MakeListRowWidget(TSharedPtr<FSolverStackElement> InElement, const TSharedRef<STableViewBase>& OwnerTable);` — list view generate row callback
- L129 _private prototype_ `void RefreshStackView();` — call to refresh the stack view
- L132 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);` — SWidget interface
- L136 _private prototype_ `FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — drag and drop operations
- L137 _private prototype_ `TOptional<EItemDropZone> OnCanAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<FSolverStackElement> TargetItem);`
- L138 _private prototype_ `FReply OnAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<FSolverStackElement> TargetItem);`

#### Free symbols / members of external scopes

- L83 _typedef_ `typedef SListView< TSharedPtr<FSolverStackElement> > SSolverStackListViewType;`

### `Plugins/Animation/IKRig/Source/IKRigEditor/Public/SBaseHierarchyTreeView.h` (Public)


#### class `SBaseHierarchyTreeView`  
`template<class ItemType> class SBaseHierarchyTreeView : public STreeView<TSharedPtr<ItemType>>`  
_L8-95_
- inherits: `STreeView<TSharedPtr<ItemType>>`
- L10 _private typedef_ `typedef STreeView<TSharedPtr<ItemType>> BaseView;`
- L11 _private typedef_ `using TSparseItemMap = typename BaseView::TSparseItemMap;`
- L12 _private typedef_ `using TItemSet = typename BaseView::TItemSet;`
- L16 _public prototype_ `virtual ~SBaseHierarchyTreeView() = default;`
- L18 _public function_ `virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override`
- L26 _public function_ `void SaveAndClearState()` — Save a snapshot of items expansion and selection state
- L33 _public function_ `void RestoreState(const TSharedPtr<ItemType>& ItemPtr)` — Restore items expansion and selection state from the saved snapshot after tree reconstruction
- L40 _public member_ `uint32 LastClickCycles = 0;` — slow double-click rename state
- L41 _public member_ `TWeakPtr<ItemType> LastSelected;`
- L46 _private function_ `void SaveAndClearSparseItemInfos()` — Save a snapshot of the internal map that tracks item expansion before tree reconstruction
- L53 _private function_ `void RestoreSparseItemInfos(const TSharedPtr<ItemType>& ItemPtr)` — Restore the expansion infos map from the saved snapshot after tree reconstruction
- L70 _private function_ `void SaveAndClearSelection()` — Save a snapshot of the internal set that tracks item selection before tree reconstruction
- L77 _private function_ `void RestoreSelection(const TSharedPtr<ItemType>& ItemPtr)` — Restore the selection from the saved snapshot after tree reconstruction
- L91 _private member_ `TSparseItemMap OldSparseItemInfos;` — A temporary snapshot of the SparseItemInfos in STreeView, used during SIKRetargetHierarchy::RefreshTreeView()
- L94 _private member_ `TItemSet OldSelectedItems;` — A temporary snapshot of the SelectedItems in SListView, used during SIKRetargetHierarchy::RefreshTreeView()
