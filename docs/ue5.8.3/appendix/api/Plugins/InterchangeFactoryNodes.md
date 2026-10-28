# Plugins / InterchangeFactoryNodes

- module root: `Plugins/Interchange/Runtime/Source/FactoryNodes`
- headers: 39; symbols: 1364
- symbol kinds: class=54, enum=5, enumerator=16, function=234, macro=25, member=130, namespace=17, prototype=876, struct=7
- PrivateDependencyModuleNames: GeometryCache, HairStrandsCore, LevelSequence
- PublicDependencyModuleNames: CinematicCamera, Core, CoreUObject, Engine, InterchangeCommon, InterchangeCore, InterchangeEngine, InterchangeNodes, TextureUtilitiesCommon, VariantManagerContent

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeActorFactoryNode.h` (Public)


#### class `UInterchangeActorFactoryNode`  
`class UInterchangeActorFactoryNode : public UInterchangeFactoryBaseNode`  
_L12-122_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBaseNode`
- L17 _public prototype_ `UInterchangeActorFactoryNode();`
- L19 _public prototype_ `virtual UClass* GetObjectClass() const override;`
- L22 _public prototype_ `bool GetCustomGlobalTransform(FTransform& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | ActorFactory")`
- L25 _public prototype_ `bool SetCustomGlobalTransform(const FTransform& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | ActorFactory")`
- L28 _public prototype_ `bool GetCustomLocalTransform(FTransform& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | ActorFactory")`
- L31 _public prototype_ `bool SetCustomLocalTransform(const FTransform& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | ActorFactory")`
- L34 _public prototype_ `bool GetCustomComponentVisibility(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | ActorFactory")`
- L37 _public prototype_ `bool SetCustomComponentVisibility(bool AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | ActorFactory")`
- L40 _public prototype_ `bool GetCustomActorVisibility(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | ActorFactory")`
- L43 _public prototype_ `bool SetCustomActorVisibility(bool AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | ActorFactory")`
- L46 _public prototype_ `bool GetCustomActorClassName(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | ActorFactory")`
- L49 _public prototype_ `bool SetCustomActorClassName(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | ActorFactory")`
- L52 _public prototype_ `bool GetCustomMobility(uint8& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | ActorFactory")`
- L55 _public prototype_ `bool SetCustomMobility(const uint8& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | ActorFactory")`
- L57 _public prototype_ `virtual void CopyWithObject(const UInterchangeFactoryBaseNode* SourceNode, UObject* Object) override;`
- L61 _public prototype_ `void GetLayerNames(TArray<FString>& OutLayerNames) const;` — Gets the LayerNames that this Actor is supposed to be part of.
- L64 _public prototype_ `bool AddLayerName(const FString& InLayerName);` — Add LayerName that this Actor is supposed to be part of.
- L67 _public prototype_ `bool AddLayerNames(const TArray<FString>& InLayerNames);` — Add LayerNames that this Actor is supposed to be part of.
- L70 _public prototype_ `bool RemoveLayerName(const FString& InLayerName);` — Remove LayerName that this Actor is supposed to be part of.
- L74 _public prototype_ `void GetTags(TArray<FString>& OutTags) const;` — Gets the Tags that this Actor is supposed to have.
- L77 _public prototype_ `bool AddTag(const FString& Tag);` — Add Tag that this Actor is supposed to have.
- L80 _public prototype_ `bool AddTags(const TArray<FString>& InTags);` — Add Tags that this Actor is supposed to have.
- L83 _public prototype_ `bool RemoveTag(const FString& Tag);` — Remove Tag that this Actor is supposed to have.
- L86 _public prototype_ `virtual void OnRestoreAllCustomAttributeDelegates() override;`
- L90 _public prototype_ `bool AddComponentUid(const FString& ComponentUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | Component")`
- L93 _public prototype_ `void GetComponentUids(TArray<FString>& OutComponentUids) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | Component")`
- L97 _private prototype_ `bool ApplyCustomGlobalTransformToAsset(UObject* Asset) const;`
- L98 _private prototype_ `bool FillCustomGlobalTransformFromAsset(UObject* Asset);`
- L100 _private prototype_ `bool ApplyCustomComponentVisibilityToAsset(UObject* Asset) const;`
- L101 _private prototype_ `bool FillCustomComponentVisibilityFromAsset(UObject* Asset);`
- L103 _private prototype_ `bool ApplyCustomLocalTransformToAsset(UObject* Asset) const;`
- L104 _private prototype_ `bool FillCustomLocalTransformFromAsset(UObject* Asset);`
- L106 _private prototype_ `bool ApplyCustomActorVisibilityToAsset(UObject* Asset) const;`
- L107 _private prototype_ `bool FillCustomActorVisibilityFromAsset(UObject* Asset);`
- L109 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(GlobalTransform);`
- L110 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(LocalTransform);`
- L111 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(ComponentVisibility);`
- L112 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(ActorVisibility);`
- L113 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(ActorClassName);`
- L114 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(Mobility);`
- L117 _private member_ `UE::Interchange::TArrayAttributeHelper<FString> LayerNames;` — A scene node can be part of multiple Layers.
- L118 _private member_ `UE::Interchange::TArrayAttributeHelper<FString> Tags;`
- L121 _private member_ `UE::Interchange::TArrayAttributeHelper<FString> ComponentUids;` — A scene node can represent many special types

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEFACTORYNODES_API`

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeAnimSequenceFactoryNode.h` (Public)


#### struct `UE::Interchange::FAnimSequenceNodeStaticData`  
`struct FAnimSequenceNodeStaticData : public FBaseNodeStaticData`  
_L21-31_
- inherits: `FBaseNodeStaticData`
- L23 _public prototype_ `static const FAttributeKey& GetAnimatedMorphTargetDependenciesKey();`
- L24 _public prototype_ `static const FAttributeKey& GetAnimatedAttributeCurveNamesKey();`
- L25 _public prototype_ `static const FAttributeKey& GetAnimatedAttributeStepCurveNamesKey();`
- L26 _public prototype_ `static const FAttributeKey& GetAnimatedMaterialCurveSuffixesKey();`
- L27 _public prototype_ `static const FAttributeKey& GetSceneNodeAnimationPayloadKeyUidMapKey();`
- L28 _public prototype_ `static const FAttributeKey& GetSceneNodeAnimationPayloadKeyTypeMapKey();`
- L29 _public prototype_ `static const FAttributeKey& GetMorphTargetNodePayloadKeyUidMapKey();`
- L30 _public prototype_ `static const FAttributeKey& GetMorphTargetNodePayloadKeyTypeMapKey();`

#### class `UInterchangeAnimSequenceFactoryNode`  
`class UInterchangeAnimSequenceFactoryNode : public UInterchangeFactoryBaseNode`  
_L37-448_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBaseNode`
- L42 _public prototype_ `UInterchangeAnimSequenceFactoryNode();`
- L50 _public prototype_ `void InitializeAnimSequenceNode(const FString& UniqueID, const FString& DisplayLabel, UInterchangeBaseNodeContainer* NodeContainer);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Initialize node data. @param UniqueID - The unique ID for this node. @param DisplayLabel - The name of the node.
- L55 _public function_ `virtual void Serialize(FArchive& Ar) override` — Override Serialize() to restore SlotMaterialDependencies on load.
- L72 _public prototype_ `virtual FString GetTypeName() const override;` — Return the node type name of the class. This is used when reporting errors.
- L75 _public prototype_ `virtual FString GetKeyDisplayName(const UE::Interchange::FAttributeKey& NodeAttributeKey) const override;`
- L76 _public prototype_ `virtual FString GetAttributeCategory(const UE::Interchange::FAttributeKey& NodeAttributeKey) const override;`
- L77 _public prototype_ `virtual bool ShouldHideAttribute(const UE::Interchange::FAttributeKey& NodeAttributeKey) const override;`
- L81 _public prototype_ `virtual class UClass* GetObjectClass() const override;` — Get the class this node creates.
- L86 _public prototype_ `bool GetCustomSkeletonFactoryNodeUid(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Get the unique ID of the skeleton factory node. Return false if the attribute is not set.
- L90 _public prototype_ `bool SetCustomSkeletonFactoryNodeUid(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Set the unique ID of the skeleton factory node. Return false if the attribute cannot be set.
- L104 _public prototype_ `bool GetCustomImportBoneTracks(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Get the import bone tracks state. If the attribute is true, bone tracks are imported. If the attribute is false, bone tracks are not imported. Return false if the attribute is not set. Return true if the attribute exists and can be queried.
- L108 _public prototype_ `bool SetCustomImportBoneTracks(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Set the import bone tracks state. Pass true to import bone tracks, or false to not import bone tracks.
- L112 _public prototype_ `bool GetCustomImportBoneTracksSampleRate(double& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Get the import bone tracks sample rate. Return false if the attribute is not set.
- L116 _public prototype_ `bool SetCustomImportBoneTracksSampleRate(const double& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Set the import bone tracks sample rate. Return false if the attribute could not be set.
- L120 _public prototype_ `bool GetCustomImportBoneTracksRangeStart(double& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Get the import bone tracks start time in seconds. Return false if the attribute is not set.
- L124 _public prototype_ `bool SetCustomImportBoneTracksRangeStart(const double& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Set the import bone tracks start time in seconds. Return false if the attribute could not be set.
- L128 _public prototype_ `bool GetCustomImportBoneTracksRangeStop(double& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Get the import bone tracks end time in seconds. Return false if the attribute is not set.
- L132 _public prototype_ `bool SetCustomImportBoneTracksRangeStop(const double& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Set the import bone tracks end time in seconds. Return false if the attribute could not be set.
- L150 _public prototype_ `bool GetCustomImportAttributeCurves(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Get the import attribute curves state. If true, all user custom attributes on nodes are imported. Return false if the attribute is not set.
- L154 _public prototype_ `bool SetCustomImportAttributeCurves(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Set the import attribute curves state. Return false if the attribute could not be set.
- L162 _public prototype_ `bool GetCustomDoNotImportCurveWithZero(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Get the custom attribute DoNotImportCurveWithZero. Return false if the attribute is not set. Note - If this attribute is enabled, only curves that have a value other than zero will be imported. This is to avoid adding extra curves to evaluate.
- L170 _public prototype_ `bool SetCustomDoNotImportCurveWithZero(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Set the custom attribute DoNotImportCurveWithZero. Return false if the attribute could not be set. Note - If this attribute is enabled, only curves that have a value other than zero will be imported. This is to avoid adding extra curves to evaluate.
- L178 _public prototype_ `bool GetCustomAddCurveMetadataToSkeleton(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Get the custom attribute AddCurveMetadataToSkeleton. Return false if the attribute is not set. Note - If this setting is disabled, curve metadata will be added to skeletal meshes for morph targets, but no metadata entry will be created for general curves.
- L186 _public prototype_ `bool SetCustomAddCurveMetadataToSkeleton(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Set the custom attribute AddCurveMetadataToSkeleton. Return false if the attribute could not be set. Note - If this setting is disabled, curve metadata will be added to skeletal meshes for morph targets, but no metadata entry will be created for general curves.
- L192 _public prototype_ `bool GetCustomRemoveCurveRedundantKeys(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Get the custom attribute RemoveCurveRedundantKeys. Return false if the attribute is not set.
- L198 _public prototype_ `bool SetCustomRemoveCurveRedundantKeys(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Set the custom attribute RemoveCurveRedundantKeys. Return false if the attribute could not be set.
- L215 _public prototype_ `bool GetCustomDeleteExistingMorphTargetCurves(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Get the custom attribute DeleteExistingMorphTargetCurves. Return false if the attribute is not set. Note: If true, all previous morph target curves are deleted if you reimport.
- L223 _public prototype_ `bool SetCustomDeleteExistingMorphTargetCurves(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Set the custom attribute DeleteExistingMorphTargetCurves. Return false if the attribute could not be set. Note: If true, all previous morph target curves are deleted if you reimport.
- L240 _public prototype_ `int32 GetAnimatedAttributeCurveNamesCount() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Return the number of animated attribute curve names this anim sequence drives. Curves are FRichCurve of type float.
- L244 _public prototype_ `void GetAnimatedAttributeCurveNames(TArray<FString>& OutAttributeCurveNames) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Get all animated attribute curve names.
- L248 _public prototype_ `void GetAnimatedAttributeCurveName(const int32 Index, FString& OutAttributeCurveName) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Get the animated attribute curve name at the specified index.
- L252 _public prototype_ `bool SetAnimatedAttributeCurveName(const FString& AttributeCurveName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Add an animated attribute curve name.
- L256 _public prototype_ `bool RemoveAnimatedAttributeCurveName(const FString& AttributeCurveName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Remove the specified animated attribute curve name.
- L276 _public prototype_ `bool GetCustomMaterialDriveParameterOnCustomAttribute(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Get the custom attribute MaterialDriveParameterOnCustomAttribute. Return false if the attribute is not set. Note: If true, sets Material Curve Type for all custom attributes.
- L284 _public prototype_ `bool SetCustomMaterialDriveParameterOnCustomAttribute(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Set the custom attribute MaterialDriveParameterOnCustomAttribute. Return false if the attribute could not be set. Note: If true, sets Material Curve Type for all custom attributes.
- L288 _public prototype_ `int32 GetAnimatedMaterialCurveSuffixesCount() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Return the number of animated material curve suffixes this anim sequence drives. Curves are FRichCurve of type float.
- L292 _public prototype_ `void GetAnimatedMaterialCurveSuffixes(TArray<FString>& OutMaterialCurveSuffixes) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Get all animated material curve suffixes.
- L296 _public prototype_ `void GetAnimatedMaterialCurveSuffixe(const int32 Index, FString& OutMaterialCurveSuffixe) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Get the animated material curve suffix with the specified index.
- L300 _public prototype_ `bool SetAnimatedMaterialCurveSuffixe(const FString& MaterialCurveSuffixe);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Add an animated material curve suffix.
- L304 _public prototype_ `bool RemoveAnimatedMaterialCurveSuffixe(const FString& MaterialCurveSuffixe);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Remove the specified animated material curve suffix.
- L322 _public prototype_ `int32 GetAnimatedAttributeStepCurveNamesCount() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Return the number of animated attribute step curve names this anim sequence drives.
- L326 _public prototype_ `void GetAnimatedAttributeStepCurveNames(TArray<FString>& OutAttributeStepCurveNames) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Get all animated attribute step curve names.
- L330 _public prototype_ `void GetAnimatedAttributeStepCurveName(const int32 Index, FString& OutAttributeStepCurveName) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Get the animated attribute step curve name at the specified index.
- L334 _public prototype_ `bool SetAnimatedAttributeStepCurveName(const FString& AttributeStepCurveName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Add an animated attribute step curve name.
- L338 _public prototype_ `bool RemoveAnimatedAttributeStepCurveName(const FString& AttributeStepCurveName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Remove the specified animated attribute step curve name.
- L352 _public prototype_ `bool GetCustomDeleteExistingCustomAttributeCurves(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Get the custom attribute DeleteExistingCustomAttributeCurves. Return false if the attribute is not set. Note - If true, all previous custom attribute curves are deleted if you reimport.
- L360 _public prototype_ `bool SetCustomDeleteExistingCustomAttributeCurves(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Set the custom attribute DeleteExistingCustomAttributeCurves. Return false if the attribute could not be set. Note - If true, all previous custom attribute curves are deleted if you reimport.
- L373 _public prototype_ `bool GetCustomDeleteExistingNonCurveCustomAttributes(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Get the custom attribute DeleteExistingNonCurveCustomAttributes. Return false if the attribute is not set. Note - If true, all previous non-curve custom attributes are deleted if you reimport.
- L381 _public prototype_ `bool SetCustomDeleteExistingNonCurveCustomAttributes(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Set the custom attribute DeleteExistingNonCurveCustomAttributes. Return false if the attribute could not be set. Note - If true, all previous non-curve custom attributes are deleted if you reimport.
- L390 _public prototype_ `bool GetCustomSkeletonSoftObjectPath(FSoftObjectPath& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Query the optional existing USkeleton this animation must use. If this attribute is set and the skeleton is valid, the AnimSequence factory uses this skeleton instead of the one imported from GetCustomSkeletonFactoryNodeUid. Pipelines set this attribute when the user wants to specify an existing skeleton. Return false if the attribute was not set.
- L398 _public prototype_ `bool SetCustomSkeletonSoftObjectPath(const FSoftObjectPath& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Set the optional existing USkeleton this animation must use. If this attribute is set and the skeleton is valid, the AnimSequence factory uses this skeleton instead of the one imported from GetCustomSkeletonFactoryNodeUid. Pipelines set this attribute when the user wants to specify an existing skeleton.
- L401 _public prototype_ `void GetSceneNodeAnimationPayloadKeys(TMap<FString, FInterchangeAnimationPayLoadKey>& OutSceneNodeAnimationPayloadKeys) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalAnimationTrack")`
- L404 _public prototype_ `void SetAnimationPayloadKeysForSceneNodeUids(const TMap<FString, FString>& SceneNodeAnimationPayloadKeyUids, const TMap<FString, uint8>& SceneNodeAnimationPayloadKeyTypes);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalAnimationTrack")`
- L407 _public prototype_ `void GetMorphTargetNodeAnimationPayloadKeys(TMap<FString, FInterchangeAnimationPayLoadKey>& OutMorphTargetNodeAnimationPayloads) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalAnimationTrack")`
- L410 _public prototype_ `void SetAnimationPayloadKeysForMorphTargetNodeUids(const TMap<FString, FString>& MorphTargetAnimationPayloadKeyUids, const TMap<FString, uint8>& MorphTargetAnimationPayloadKeyTypes);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalAnimationTrack")`
- L413 _public function_ `virtual bool IsRuntimeImportAllowed() const override` — Return if the import of the class is allowed at runtime.
- L419 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomSkeletonFactoryNodeUidKey = UE::Interchange::FAttributeKey(TEXT("Skel`
- L421 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomImportBoneTracksKey = UE::Interchange::FAttributeKey(TEXT("Impo`
- L422 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomImportBoneTracksSampleRateKey = UE::Interchange::FAttributeKey(TEXT("Impo`
- L423 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomImportBoneTracksRangeStartKey = UE::Interchange::FAttributeKey(TEXT("Impo`
- L424 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomImportBoneTracksRangeStopKey = UE::Interchange::FAttributeKey(TEXT("Impo`
- L426 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomImportAttributeCurvesKey = UE::Interchange::FAttributeKey(TEXT("Impo`
- L427 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomDoNotImportCurveWithZeroKey = UE::Interchange::FAttributeKey(TEXT("DoNo`
- L428 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomAddCurveMetadataToSkeletonKey = UE::Interchange::FAttributeKey(TEXT("AddC`
- L429 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomRemoveCurveRedundantKeysKey = UE::Interchange::FAttributeKey(TEXT("Remo`
- L430 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomMaterialDriveParameterOnCustomAttributeKey = UE::Interchange::FAttributeKey(TEXT("Mate`
- L431 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomDeleteExistingMorphTargetCurvesKey = UE::Interchange::FAttributeKey(TEXT("Dele`
- L432 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomDeleteExistingCustomAttributeCurvesKey = UE::Interchange::FAttributeKey(TEXT("Dele`
- L434 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomDeleteExistingNonCurveCustomAttributesKey = UE::Interchange::FAttributeKey(TEXT("Dele`
- L436 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomSkeletonSoftObjectPathKey = UE::Interchange::FAttributeKey(TEXT("Skel`
- L438 _private member_ `UE::Interchange::TArrayAttributeHelper<FString> AnimatedMorphTargetDependencies;`
- L439 _private member_ `UE::Interchange::TArrayAttributeHelper<FString> AnimatedAttributeCurveNames;`
- L440 _private member_ `UE::Interchange::TArrayAttributeHelper<FString> AnimatedAttributeStepCurveNames;`
- L441 _private member_ `UE::Interchange::TArrayAttributeHelper<FString> AnimatedMaterialCurveSuffixes;`
- L443 _private member_ `UE::Interchange::TMapAttributeHelper<FString, FString> SceneNodeAnimationPayLoadKeyUidMap;`
- L444 _private member_ `UE::Interchange::TMapAttributeHelper<FString, uint8> SceneNodeAnimationPayLoadKeyTypeMap;`
- L446 _private member_ `UE::Interchange::TMapAttributeHelper<FString, FString> MorphTargetNodePayloadKeyUidMap;`
- L447 _private member_ `UE::Interchange::TMapAttributeHelper<FString, uint8> MorphTargetNodePayloadKeyTypeMap;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API INTERCHANGEFACTORYNODES_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Interchange` (scope `UE`)
- L13 _namespace_ `namespace Animation` (scope `UE::Interchange`)
- L16 _prototype_ `FFrameRate ConvertSampleRatetoFrameRate(double SampleRate);` (scope `UE::Interchange::Animation`) — `UE_DEPRECATED(5.8, "Use ConvertSampleRateToFrameRate in InterchangeAnimationTrackSetNode.h instead")`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Interchange` (scope `UE`)

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeAudioSoundWaveFactoryNode.h` (Public)


#### class `UInterchangeAudioSoundWaveFactoryNode`  
`class UInterchangeAudioSoundWaveFactoryNode : public UInterchangeFactoryBaseNode`  
_L11-25_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBaseNode`
- L16 _public function_ `virtual FString GetTypeName() const override`
- L21 _public function_ `virtual UClass* GetObjectClass() const override`

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeCameraFactoryNode.h` (Public)


#### class `UInterchangeBaseCameraFactoryNode`  
`class UInterchangeBaseCameraFactoryNode : public UInterchangeActorFactoryNode`  
_L16-182_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeActorFactoryNode`
- L22 _public function_ `bool GetCustomNearClipPlane(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | CameraFactory")`
- L28 _public function_ `bool SetCustomNearClipPlane(const float& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | CameraFactory")`
- L34 _public function_ `bool GetCustomAutoExposureMethod(EInterchangeAutoExposureMethod& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L40 _public function_ `bool SetCustomAutoExposureMethod(const EInterchangeAutoExposureMethod& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Camera")`
- L46 _public function_ `bool GetCustomExposureCompensation(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | CameraFactory")`
- L52 _public function_ `bool SetCustomExposureCompensation(const float& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | CameraFactory")`
- L58 _public function_ `bool GetCustomExposureFstop(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | CameraFactory")`
- L64 _public function_ `bool SetCustomExposureFstop(const float& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | CameraFactory")`
- L70 _public function_ `bool GetCustomExposureISO(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | CameraFactory")`
- L76 _public function_ `bool SetCustomExposureISO(const float& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | CameraFactory")`
- L82 _public function_ `bool GetCustomExposureShutterSpeed(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | CameraFactory")`
- L88 _public function_ `bool SetCustomExposureShutterSpeed(const float& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | CameraFactory")`
- L93 _public function_ `virtual void CopyWithObject(const UInterchangeFactoryBaseNode* SourceNode, UObject* Object) override`
- L109 _protected prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(NearClipPlane);`
- L110 _protected prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(AutoExposureMethod);`
- L111 _protected prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(ExposureCompensation);`
- L112 _protected prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(ExposureFstop);`
- L113 _protected prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(ExposureISO);`
- L114 _protected prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(ExposureShutterSpeed);`
- L117 _protected function_ `virtual bool ApplyCustomNearClipPlaneToAsset(UObject* Asset) const` — We need to defer these to the derived classes as the implementation is slightly different for each
- L123 _protected function_ `virtual bool FillCustomNearClipPlaneFromAsset(UObject* Asset)`
- L130 _protected function_ `bool ApplyCustomAutoExposureMethodToAsset(UObject* Asset) const` — We must implement our other PostProcessSettings delegates because we need to also set the bOverride properties alongside the property values themselves, as otherwise they will have no effect
- L136 _protected function_ `bool FillCustomAutoExposureMethodFromAsset(UObject* Asset)`
- L141 _protected function_ `bool ApplyCustomExposureCompensationToAsset(UObject* Asset) const`
- L147 _protected function_ `bool FillCustomExposureCompensationFromAsset(UObject* Asset)`
- L152 _protected function_ `virtual bool ApplyCustomExposureFstopToAsset(UObject* Asset) const`
- L156 _protected function_ `virtual bool FillCustomExposureFstopFromAsset(UObject* Asset)`
- L161 _protected function_ `bool ApplyCustomExposureISOToAsset(UObject* Asset) const`
- L167 _protected function_ `bool FillCustomExposureISOFromAsset(UObject* Asset)`
- L172 _protected function_ `bool ApplyCustomExposureShutterSpeedToAsset(UObject* Asset) const`
- L178 _protected function_ `bool FillCustomExposureShutterSpeedFromAsset(UObject* Asset)`

#### class `UInterchangePhysicalCameraFactoryNode`  
`class UInterchangePhysicalCameraFactoryNode : public UInterchangeBaseCameraFactoryNode`  
_L185-352_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeBaseCameraFactoryNode`
- L191 _public function_ `bool GetCustomFocalLength(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | CameraFactory")`
- L197 _public function_ `bool SetCustomFocalLength(const float& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | CameraFactory")`
- L203 _public function_ `bool GetCustomFocusDistance(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | CameraFactory")`
- L209 _public function_ `bool SetCustomFocusDistance(const float& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | CameraFactory")`
- L215 _public function_ `bool GetCustomSensorWidth(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | CameraFactory")`
- L221 _public function_ `bool SetCustomSensorWidth(const float& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | CameraFactory")`
- L227 _public function_ `bool GetCustomSensorHeight(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | CameraFactory")`
- L233 _public function_ `bool SetCustomSensorHeight(const float& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | CameraFactory")`
- L239 _public function_ `bool GetCustomSensorHorizontalOffset(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | CameraFactory")`
- L245 _public function_ `bool SetCustomSensorHorizontalOffset(const float& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | CameraFactory")`
- L251 _public function_ `bool GetCustomSensorVerticalOffset(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | CameraFactory")`
- L257 _public function_ `bool SetCustomSensorVerticalOffset(const float& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | CameraFactory")`
- L263 _public function_ `bool GetCustomFocusMethod(ECameraFocusMethod& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | CameraFactory")`
- L269 _public function_ `bool SetCustomFocusMethod(const ECameraFocusMethod& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | CameraFactory")`
- L275 _public function_ `bool GetCustomDepthOfFieldFstop(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | CameraFactory")`
- L281 _public function_ `bool SetCustomDepthOfFieldFstop(const float& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | CameraFactory")`
- L286 _public function_ `virtual void CopyWithObject(const UInterchangeFactoryBaseNode* SourceNode, UObject* Object) override`
- L304 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(FocalLength);`
- L305 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(FocusDistance);`
- L306 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(SensorWidth);`
- L307 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(SensorHeight);`
- L308 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(SensorHorizontalOffset);`
- L309 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(SensorVerticalOffset);`
- L310 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(FocusMethod);`
- L311 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(DepthOfFieldFstop);`
- L321 _private function_ `virtual bool ApplyCustomNearClipPlaneToAsset(UObject* Asset) const override`
- L327 _private function_ `virtual bool FillCustomNearClipPlaneFromAsset(UObject* Asset) override`
- L332 _private function_ `virtual bool ApplyCustomExposureFstopToAsset(UObject* Asset) const override`
- L337 _private function_ `virtual bool FillCustomExposureFstopFromAsset(UObject* Asset) override`
- L342 _private function_ `bool ApplyCustomDepthOfFieldFstopToAsset(UObject* Asset) const`
- L348 _private function_ `bool FillCustomDepthOfFieldFstopFromAsset(UObject* Asset)`

#### class `UInterchangeStandardCameraFactoryNode`  
`class UInterchangeStandardCameraFactoryNode : public UInterchangeBaseCameraFactoryNode`  
_L358-477_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeBaseCameraFactoryNode`
- desc: Used for common non-physical camera with orthographic or perspective projection.
- L364 _public function_ `bool GetCustomProjectionMode(TEnumAsByte<ECameraProjectionMode::Type>& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | CameraFactory")`
- L369 _public function_ `bool SetCustomProjectionMode(const TEnumAsByte<ECameraProjectionMode::Type>& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | CameraFactory")`
- L375 _public function_ `bool GetCustomWidth(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | CameraFactory")`
- L380 _public function_ `bool SetCustomWidth(const float& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | CameraFactory")`
- L386 _public function_ `bool GetCustomFarClipPlane(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | CameraFactory")`
- L391 _public function_ `bool SetCustomFarClipPlane(const float& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | CameraFactory")`
- L397 _public function_ `bool GetCustomAspectRatio(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | CameraFactory")`
- L402 _public function_ `bool SetCustomAspectRatio(const float& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | CameraFactory")`
- L408 _public function_ `bool GetCustomFieldOfView(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | CameraFactory")`
- L413 _public function_ `bool SetCustomFieldOfView(const float& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | CameraFactory")`
- L418 _public function_ `virtual void CopyWithObject(const UInterchangeFactoryBaseNode* SourceNode, UObject* Object) override`
- L433 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(ProjectionMode);`
- L434 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(Width);`
- L435 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(FarClipPlane);`
- L436 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(AspectRatio);`
- L437 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(FieldOfView);`
- L444 _private function_ `virtual bool ApplyCustomNearClipPlaneToAsset(UObject* Asset) const override`
- L450 _private function_ `virtual bool FillCustomNearClipPlaneFromAsset(UObject* Asset) override`
- L455 _private function_ `virtual bool ApplyCustomExposureFstopToAsset(UObject* Asset) const override`
- L462 _private function_ `virtual bool FillCustomExposureFstopFromAsset(UObject* Asset) override`
- L467 _private function_ `bool ApplyCustomFarClipPlaneToAsset(UObject* Asset) const`
- L473 _private function_ `bool FillCustomFarClipPlaneFromAsset(UObject* Asset)`

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeCommonPipelineDataFactoryNode.h` (Public)


#### class `UInterchangeCommonPipelineDataFactoryNode`  
`class UInterchangeCommonPipelineDataFactoryNode : public UInterchangeFactoryBaseNode`  
_L16-57_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBaseNode`
- desc: This factory node is where pipelines can set global data that can be used by factories.
- L22 _public prototype_ `static UInterchangeCommonPipelineDataFactoryNode* FindOrCreateUniqueInstance(UInterchangeBaseNodeContainer* NodeContainer);` — Pipelines that want to modify the common data should ensure they create the unique common pipeline node.
- L25 _public prototype_ `static UInterchangeCommonPipelineDataFactoryNode* GetUniqueInstance(const UInterchangeBaseNodeContainer* NodeContainer);` — If the unique instance doesn't exist, this will return nullptr. This function should be use by the factories, to avoid creating a node.
- L29 _public prototype_ `bool GetCustomGlobalOffsetTransform(FTransform& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Common Pipeline Data")` — Return the global offset transform set by the pipelines.
- L33 _public prototype_ `bool SetCustomGlobalOffsetTransform(const UInterchangeBaseNodeContainer* NodeContainer, const FTransform& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Common Pipeline Data")` — Pipelines can set a global transform. Factories will use this global offset when importing assets.
- L37 _public prototype_ `bool GetBakeMeshes(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Common Pipeline Data")` — Return the value of the Bake Meshes setting set by the pipelines.
- L41 _public prototype_ `bool SetBakeMeshes(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Common Pipeline Data")` — Pipelines can set this Bake Meshes setting. Factories use this to identify whether they should apply global transforms to static meshes and skeletal meshes.
- L45 _public prototype_ `bool GetBakePivotMeshes(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Common Pipeline Data")` — Return the value of the Bake Meshes setting set by the pipelines.
- L49 _public prototype_ `bool SetBakePivotMeshes(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Common Pipeline Data")` — Pipelines can set this Bake Meshes setting. Factories use this to identify whether they should apply global transforms to static meshes and skeletal meshes.
- L52 _private function_ `UInterchangeCommonPipelineDataFactoryNode()`
- L54 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomGlobalOffsetTransformKey = UE::Interchange::FAttributeKey(TEXT("Glob`
- L55 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomBakeMeshesKey = UE::Interchange::FAttributeKey(TEXT("Bake`
- L56 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomBakePivotMeshesKey = UE::Interchange::FAttributeKey(TEXT("Bake`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEFACTORYNODES_API`

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeDecalActorFactoryNode.h` (Public)


#### class `UInterchangeDecalActorFactoryNode`  
`class UInterchangeDecalActorFactoryNode : public UInterchangeActorFactoryNode`  
_L12-48_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeActorFactoryNode`
- L17 _public prototype_ `UClass* GetObjectClass()const override;`
- L19 _public prototype_ `virtual void CopyWithObject(const UInterchangeFactoryBaseNode* SourceNode, UObject* Object) override;`
- L22 _public prototype_ `bool GetCustomSortOrder(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Decal")`
- L25 _public prototype_ `bool SetCustomSortOrder(const int32& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Decal")`
- L28 _public prototype_ `bool GetCustomDecalSize(FVector& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Decal")`
- L31 _public prototype_ `bool SetCustomDecalSize(const FVector& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Decal")`
- L34 _public prototype_ `bool GetCustomDecalMaterialPathName(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Decal")`
- L38 _public prototype_ `bool SetCustomDecalMaterialPathName(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Decal")`
- L45 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomSortOrderKey = UE::Interchange::FAttributeKey(TEXT("Sort`
- L46 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomDecalSizeKey = UE::Interchange::FAttributeKey(TEXT("Deca`
- L47 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomDecalMaterialPathNameKey = UE::Interchange::FAttributeKey(TEXT("Deca`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEFACTORYNODES_API`

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeDecalMaterialFactoryNode.h` (Public)


#### class `UInterchangeDecalMaterialFactoryNode`  
`class UInterchangeDecalMaterialFactoryNode : public UInterchangeBaseMaterialFactoryNode`  
_L13-35_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeBaseMaterialFactoryNode`
- L18 _public prototype_ `UClass* GetObjectClass()const override;`
- L21 _public prototype_ `bool GetCustomDiffuseTexturePath(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Decal")`
- L24 _public prototype_ `bool SetCustomDiffuseTexturePath(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Decal")`
- L27 _public prototype_ `bool GetCustomNormalTexturePath(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Decal")`
- L30 _public prototype_ `bool SetCustomNormalTexturePath(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Decal")`
- L33 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomDiffuseTexturePathKey = UE::Interchange::FAttributeKey(TEXT("Diff`
- L34 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomNormalTexturePathKey = UE::Interchange::FAttributeKey(TEXT("Norm`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API INTERCHANGEFACTORYNODES_API`

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeFactoryNodesModule.h` (Public)


#### class `IInterchangeFactoryNodesModule`  
`class IInterchangeFactoryNodesModule : public IModuleInterface`  
_L12-37_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L23 _public function_ `static inline IInterchangeFactoryNodesModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L33 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeGeometryCacheFactoryNode.h` (Public)


#### struct `UE::Interchange::FGeometryCacheNodeStaticData`  
`struct FGeometryCacheNodeStaticData : public FBaseNodeStaticData`  
_L17-20_
- inherits: `FBaseNodeStaticData`
- L19 _public prototype_ `static const FAttributeKey& GetSceneNodeAnimationPayloadKeyUidMapKey();`

#### class `UInterchangeGeometryCacheFactoryNode`  
`class UInterchangeGeometryCacheFactoryNode : public UInterchangeMeshFactoryNode`  
_L24-150_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeMeshFactoryNode`
- L29 _public prototype_ `UInterchangeGeometryCacheFactoryNode();`
- L38 _public prototype_ `void InitializeGeometryCacheNode(const FString& UniqueID, const FString& DisplayLabel, const FString& InAssetClass, UInterchangeBaseNodeContainer* NodeContainer);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | GeometryCache")` — Initialize node data. Also adds it to NodeContainer. @param UniqueID - The unique ID for this node. @param DisplayLabel - The name of the node. @param InAssetClass - The class the GeometryCache factory will create for this node.
- L44 _public prototype_ `bool GetCustomFlattenTracks(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | GeometryCache")` — Get whether to merge all geometries into a single mesh
- L48 _public prototype_ `bool SetCustomFlattenTracks(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | GeometryCache")` — Set whether to merge all geometries into a single mesh
- L52 _public prototype_ `bool GetCustomPositionPrecision(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | GeometryCache")` — Get the precision used for compressing vertex positions
- L56 _public prototype_ `bool SetCustomPositionPrecision(const float& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | GeometryCache")` — Set the precision used for compressing vertex positions
- L60 _public prototype_ `bool GetCustomNumBitsForUVs(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | GeometryCache")` — Get the number of bits for compressing the UV into
- L64 _public prototype_ `bool SetCustomNumBitsForUVs(const int32& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | GeometryCache")` — Set the number of bits for compressing the UV into
- L68 _public prototype_ `bool GetCustomStartFrame(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | GeometryCache")` — Get the start frame index of the animation
- L72 _public prototype_ `bool SetCustomStartFrame(const int32& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | GeometryCache")` — Set the start frame index of the animation
- L76 _public prototype_ `bool GetCustomEndFrame(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | GeometryCache")` — Get the end frame index of the animation
- L80 _public prototype_ `bool SetCustomEndFrame(const int32& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | GeometryCache")` — Set the end frame index of the animation
- L84 _public prototype_ `bool GetCustomMotionVectorsImport(EInterchangeMotionVectorsHandling& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | GeometryCache")` — Get how the motion vectors are managed
- L88 _public prototype_ `bool SetCustomMotionVectorsImport(EInterchangeMotionVectorsHandling AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | GeometryCache")` — Set how the motion vectors are managed
- L92 _public prototype_ `bool GetCustomApplyConstantTopologyOptimization(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | GeometryCache")` — Get whether constant topology optimization is applied
- L96 _public prototype_ `bool SetCustomApplyConstantTopologyOptimization(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | GeometryCache")` — Get whether constant topology optimization is applied
- L100 _public prototype_ `bool GetCustomStoreImportedVertexNumbers(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | GeometryCache")` — Get whether vertex numbers from DCC are stored in the geometry cache
- L104 _public prototype_ `bool SetCustomStoreImportedVertexNumbers(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | GeometryCache")` — Set whether vertex numbers from DCC are stored in the geometry cache
- L108 _public prototype_ `bool GetCustomOptimizeIndexBuffers(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | GeometryCache")` — Get whether to optimize the index buffers when building the geometry cache
- L112 _public prototype_ `bool SetCustomOptimizeIndexBuffers(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | GeometryCache")` — Set whether to optimize the index buffers when building the geometry cache
- L116 _public prototype_ `void GetSceneNodeAnimationPayloadKeys(TMap<FString, FString>& OutSceneNodeAnimationPayloadKeyUids) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | GeometryCache")` — Get the animation payload keys that are relevant to building the geometry cache
- L120 _public prototype_ `bool SetAnimationPayloadKeyForSceneNodeUid(const FString& SceneNodeUid, const FString& InUniqueId);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | GeometryCache")` — Set the animation payload keys that are relevant to building the geometry cache
- L125 _public prototype_ `virtual FString GetTypeName() const override;` — Return the node type name of the class. This is used when reporting errors.
- L128 _public prototype_ `virtual class UClass* GetObjectClass() const override;` — Get the class this node creates.
- L131 _private prototype_ `virtual void FillAssetClassFromAttribute() override;`
- L132 _private prototype_ `virtual bool SetNodeClassFromClassAttribute() override;`
- L135 _protected member_ `TSubclassOf<class UGeometryCache> AssetClass;`
- L138 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(FlattenTracks);`
- L139 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(PositionPrecision);`
- L140 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(NumBitsForUVs);`
- L141 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(OverrideTimeRange);`
- L142 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(StartFrame);`
- L143 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(EndFrame);`
- L144 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(MotionVectors);`
- L145 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(ApplyConstantTopologyOptimization);`
- L146 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(StoreImportedVertexNumbers);`
- L147 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(OptimizeIndexBuffers);`
- L149 _private member_ `UE::Interchange::TMapAttributeHelper<FString, FString> SceneNodeAnimationPayloadKeyUidMap;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API INTERCHANGEFACTORYNODES_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Interchange` (scope `UE`)

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeGroomBindingFactoryNode.h` (Public)


#### class `UInterchangeGroomBindingFactoryNode`  
`class UInterchangeGroomBindingFactoryNode : public UInterchangeFactoryBaseNode`  
_L12-30_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBaseNode`
- L17 _public prototype_ `virtual FString GetTypeName() const override;`
- L18 _public prototype_ `virtual class UClass* GetObjectClass() const override;`
- L22 _public prototype_ `bool GetNumInterpolationPoints(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Groom Binding")` — Get the number of points used for the rbf interpolation
- L26 _public prototype_ `bool SetNumInterpolationPoints(int32 AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Groom Binding")` — Set the number of points used for the rbf interpolation
- L29 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(NumInterpolationPoints);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEFACTORYNODES_API`

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeGroomCacheFactoryNode.h` (Public)


#### enum `EInterchangeGroomCacheImportType`  
`enum class EInterchangeGroomCacheImportType : uint8`  
_L12-18_
- reflection: `UENUM(BlueprintType)`
- L14 _public enumerator_ `None = 0x00 UMETA(Hidden)`
- L15 _public enumerator_ `Strands = 0x01`
- L16 _public enumerator_ `Guides = 0x02`
- L17 _public enumerator_ `All = Strands | Guides`

#### class `UInterchangeGroomCacheFactoryNode`  
`class UInterchangeGroomCacheFactoryNode : public UInterchangeFactoryBaseNode`  
_L21-79_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBaseNode`
- L26 _public prototype_ `virtual FString GetTypeName() const override;`
- L27 _public prototype_ `virtual class UClass* GetObjectClass() const override;`
- L30 _public prototype_ `bool GetCustomStartFrame(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Groom Cache")`
- L33 _public prototype_ `bool SetCustomStartFrame(const int32& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Groom Cache")`
- L36 _public prototype_ `bool GetCustomEndFrame(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Groom Cache")`
- L39 _public prototype_ `bool SetCustomEndFrame(const int32& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Groom Cache")`
- L42 _public prototype_ `bool GetCustomNumFrames(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Groom Cache")`
- L45 _public prototype_ `bool SetCustomNumFrames(const int32& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Groom Cache")`
- L48 _public prototype_ `bool GetCustomFrameRate(double& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Groom Cache")`
- L51 _public prototype_ `bool SetCustomFrameRate(const double& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Groom Cache")`
- L54 _public prototype_ `bool GetCustomGroomCacheAttributes(EInterchangeGroomCacheAttributes& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Groom Cache")`
- L57 _public prototype_ `bool SetCustomGroomCacheAttributes(const EInterchangeGroomCacheAttributes& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Groom Cache")`
- L60 _public prototype_ `bool GetCustomGroomCacheImportType(EInterchangeGroomCacheImportType& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Groom Cache")`
- L63 _public prototype_ `bool SetCustomGroomCacheImportType(const EInterchangeGroomCacheImportType& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Groom Cache")`
- L66 _public prototype_ `bool GetCustomGroomAssetPath(FSoftObjectPath& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Groom Cache")`
- L69 _public prototype_ `bool SetCustomGroomAssetPath(const FSoftObjectPath& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Groom Cache")`
- L72 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(StartFrame);`
- L73 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(EndFrame);`
- L74 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(NumFrames);`
- L75 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(FrameRate);`
- L76 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(GroomCacheAttributes);`
- L77 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(ImportType);`
- L78 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(GroomAssetPath);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEFACTORYNODES_API`

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeGroomComponentFactoryNode.h` (Public)


#### class `UInterchangeGroomComponentFactoryNode`  
`class UInterchangeGroomComponentFactoryNode : public UInterchangeSceneComponentFactoryNode`  
_L13-42_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeSceneComponentFactoryNode`
- L19 _public prototype_ `virtual FString GetTypeName() const override;`
- L21 _public prototype_ `virtual UClass* GetObjectClass() const override;`
- L25 _public prototype_ `bool GetGroomDependencyUid(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | Component | Groom")` — Get the groom asset to apply on the groom component
- L29 _public prototype_ `bool SetGroomDependencyUid(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | Component | Groom")` — Set the groom asset to apply on the groom component
- L33 _public prototype_ `bool GetGroomBindingDependencyUid(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | Component | Groom")` — Get the groom binding asset to apply on the groom component
- L37 _public prototype_ `bool SetGroomBindingDependencyUid(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | Component | Groom")` — Set the groom binding asset to apply on the groom component
- L40 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(GroomUid);`
- L41 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(GroomBindingUid);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API INTERCHANGEFACTORYNODES_API`

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeGroomFactoryNode.h` (Public)


#### class `UInterchangeGroomFactoryNode`  
`class UInterchangeGroomFactoryNode : public UInterchangeFactoryBaseNode`  
_L14-42_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBaseNode`
- L19 _public prototype_ `virtual FString GetTypeName() const override;`
- L20 _public prototype_ `virtual class UClass* GetObjectClass() const override;`
- L23 _public prototype_ `bool GetCustomGroupInterpolationSettings(FHairGroupsInterpolation& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Groom Cache")`
- L26 _public prototype_ `bool SetCustomGroupInterpolationSettings(const FHairGroupsInterpolation& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Groom Cache")`
- L30 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(CurveDecimation);` — DecimationSettings
- L31 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(VertexDecimation);`
- L34 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(GuideType);` — InterpolationSettings
- L35 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(HairToGuideDensity);`
- L36 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(RiggedGuideNumCurves);`
- L37 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(RiggedGuideNumPoints);`
- L38 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(InterpolationQuality);`
- L39 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(InterpolationDistance);`
- L40 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(bRandomizeGuide);`
- L41 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(bUseUniqueGuide);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEFACTORYNODES_API`

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeHeterogeneousVolumeActorFactoryNode.h` (Public)


#### class `UInterchangeHeterogeneousVolumeActorFactoryNode`  
`class UInterchangeHeterogeneousVolumeActorFactoryNode : public UInterchangeActorFactoryNode`  
_L13-30_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeActorFactoryNode`
- L18 _public prototype_ `UClass* GetObjectClass() const override;`
- L22 _public prototype_ `bool GetCustomVolumetricMaterialUid(FString& MaterialFactoryNodeUid) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | HeterogeneousVolumeActor")` — Gets the Uid of the material that should be assigned to the spawned HeterogeneousVolumeActor at its single material slot
- L26 _public prototype_ `bool SetCustomVolumetricMaterialUid(const FString& MaterialFactoryNodeUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | HeterogeneousVolumeActor")` — Sets the Uid of the material that should be assigned to the spawned HeterogeneousVolumeActor at its single material slot

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API INTERCHANGEFACTORYNODES_API`

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeLevelFactoryNode.h` (Public)


#### class `UInterchangeLevelFactoryNode`  
`class UInterchangeLevelFactoryNode : public UInterchangeFactoryBaseNode`  
_L13-111_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBaseNode`
- L17 _private prototype_ `UInterchangeLevelFactoryNode();`
- L20 _public function_ `static FStringView StaticAssetTypeName()`
- L28 _public function_ `virtual FString GetTypeName() const override` — Return the node type name of the class, we use this when reporting errors
- L35 _public prototype_ `virtual class UClass* GetObjectClass() const override;` — Get the class this node want to create
- L41 _public prototype_ `int32 GetCustomActorFactoryNodeUidCount() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LevelFactory")` — This function allow to retrieve the number of track dependencies for this object.
- L47 _public prototype_ `void GetCustomActorFactoryNodeUids(TArray<FString>& OutActorFactoryNodeUids) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LevelFactory")` — This function allow to retrieve all actor factory node unique id for this object.
- L53 _public prototype_ `void GetCustomActorFactoryNodeUid(const int32 Index, FString& OutActorFactoryNodeUid) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LevelFactory")` — This function allow to retrieve one actor factory node unique id for this object.
- L59 _public prototype_ `bool AddCustomActorFactoryNodeUid(const FString& ActorFactoryNodeUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LevelFactory")` — Add one actor factory node unique id to this object.
- L65 _public prototype_ `bool RemoveCustomActorFactoryNodeUid(const FString& ActorFactoryNodeUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LevelFactory")` — Remove one actor factory node unique id from this object.
- L71 _public prototype_ `bool GetCustomSceneImportAssetFactoryNodeUid(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LevelFactory")` — Get the actor factory node unique id that hold the re-import data.
- L77 _public prototype_ `bool SetCustomSceneImportAssetFactoryNodeUid(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LevelFactory")` — Set the actor factory node unique id that hold the re-import data.
- L83 _public prototype_ `bool GetCustomShouldCreateLevel(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LevelFactory")` — Get actors bounding box.
- L89 _public prototype_ `bool SetCustomShouldCreateLevel(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LevelFactory")` — Set actors bounding box.
- L95 _public prototype_ `bool GetCustomCreateWorldPartitionLevel(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LevelFactory")` — If true, created world partition level.
- L101 _public prototype_ `bool SetCustomCreateWorldPartitionLevel(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LevelFactory")` — If true, created world partition level.
- L105 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomShouldCreateLevelKey = UE::Interchange::FAttributeKey(TEXT("Shou`
- L106 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomSceneImportAssetFactoryNodeUidKey = UE::Interchange::FAttributeKey(TEXT("Scen`
- L107 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomCreateWorldPartitionLevelKey = UE::Interchange::FAttributeKey(TEXT("Crea`
- L108 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomParentLevelReferenceKey = UE::Interchange::FAttributeKey(TEXT("Pare`
- L110 _private member_ `UE::Interchange::TArrayAttributeHelper<FString> CustomActorFactoryNodeUids;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API INTERCHANGEFACTORYNODES_API`

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeLevelInstanceActorFactoryNode.h` (Public)


#### class `UInterchangeLevelInstanceActorFactoryNode`  
`class UInterchangeLevelInstanceActorFactoryNode : public UInterchangeActorFactoryNode`  
_L15-30_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeActorFactoryNode`
- L22 _public prototype_ `bool GetCustomLevelReference(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LevelInstanceActor")` — Get the Level this Level instance actor refer to.
- L25 _public prototype_ `bool SetCustomLevelReference(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LevelInstanceActor")` — Set the Level this Level instance actor refer to.
- L28 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomParentLevelKey = UE::Interchange::FAttributeKey(TEXT("Pare`
- L29 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomLevelReferenceKey = UE::Interchange::FAttributeKey(TEXT("Leve`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API INTERCHANGEFACTORYNODES_API`

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeLevelSequenceFactoryNode.h` (Public)


#### class `UInterchangeLevelSequenceFactoryNode`  
`class UInterchangeLevelSequenceFactoryNode : public UInterchangeFactoryBaseNode`  
_L13-83_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBaseNode`
- L17 _private prototype_ `UInterchangeLevelSequenceFactoryNode();`
- L20 _public function_ `static FStringView StaticAssetTypeName()`
- L28 _public function_ `virtual FString GetTypeName() const override` — Return the node type name of the class, we use this when reporting errors
- L35 _public prototype_ `virtual class UClass* GetObjectClass() const override;` — Get the class this node want to create
- L41 _public prototype_ `int32 GetCustomAnimationTrackUidCount() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LevelSequenceFactory")` — This function allow to retrieve the number of track dependencies for this object.
- L47 _public prototype_ `void GetCustomAnimationTrackUids(TArray<FString>& OutAnimationTrackUids) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LevelSequenceFactory")` — This function allow to retrieve the track dependency for this object.
- L53 _public prototype_ `void GetCustomAnimationTrackUid(const int32 Index, FString& OutAnimationTrackUid) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LevelSequenceFactory")` — This function allow to retrieve one track dependency for this object.
- L59 _public prototype_ `bool AddCustomAnimationTrackUid(const FString& AnimationTrackUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LevelSequenceFactory")` — Add one track dependency to this object.
- L65 _public prototype_ `bool RemoveCustomAnimationTrackUid(const FString& AnimationTrackUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LevelSequenceFactory")` — Remove one track dependency from this object.
- L71 _public prototype_ `bool SetCustomFrameRate(const float& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LevelSequenceFactory")` — Set the frame rate for the animations in the level sequence.
- L77 _public prototype_ `bool GetCustomFrameRate(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LevelSequenceFactory")` — Get the frame rate for the animations in the level sequence.
- L80 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomFrameRateKey = UE::Interchange::FAttributeKey(TEXT("Fram`
- L82 _private member_ `UE::Interchange::TArrayAttributeHelper<FString> CustomAnimationTrackUids;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API INTERCHANGEFACTORYNODES_API`

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeLightFactoryNode.h` (Public)


#### class `UInterchangeBaseLightFactoryNode`  
`class UInterchangeBaseLightFactoryNode : public UInterchangeActorFactoryNode`  
_L14-53_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeActorFactoryNode`
- L21 _public prototype_ `bool GetCustomLightColor(FColor& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LightFactory")`
- L24 _public prototype_ `bool SetCustomLightColor(const FColor& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LightFactory")`
- L27 _public prototype_ `bool GetCustomIntensity(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LightFactory")`
- L30 _public prototype_ `bool SetCustomIntensity(float AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LightFactory")`
- L33 _public prototype_ `bool GetCustomTemperature(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LightFactory")`
- L36 _public prototype_ `bool SetCustomTemperature(float AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LightFactory")`
- L39 _public prototype_ `bool GetCustomUseTemperature(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LightFactory")`
- L42 _public prototype_ `bool SetCustomUseTemperature(bool AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LightFactory")`
- L44 _public prototype_ `virtual void CopyWithObject(const UInterchangeFactoryBaseNode* SourceNode, UObject* Object) override;`
- L46 _public prototype_ `virtual void OnRestoreAllCustomAttributeDelegates() override;`

#### class `UInterchangeDirectionalLightFactoryNode`  
`class UInterchangeDirectionalLightFactoryNode : public UInterchangeBaseLightFactoryNode`  
_L56-73_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeBaseLightFactoryNode`
- L62 _public prototype_ `bool GetCustomLightSourceAngle(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | DirectionalLightFactory")`
- L65 _public prototype_ `bool SetCustomLightSourceAngle(float AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | DirectionalLightFactory")`
- L67 _public prototype_ `virtual void CopyWithObject(const UInterchangeFactoryBaseNode* SourceNode, UObject* Object) override;`
- L69 _public prototype_ `virtual void OnRestoreAllCustomAttributeDelegates() override;`

#### class `UInterchangeLightFactoryNode`  
`class UInterchangeLightFactoryNode : public UInterchangeBaseLightFactoryNode`  
_L76-129_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeBaseLightFactoryNode`
- L83 _public prototype_ `bool GetCustomIntensityUnits(ELightUnits& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LightFactory")`
- L86 _public prototype_ `bool SetCustomIntensityUnits(ELightUnits AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LightFactory")`
- L89 _public prototype_ `bool GetCustomAttenuationRadius(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LightFactory")`
- L92 _public prototype_ `bool SetCustomAttenuationRadius(float AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LightFactory")`
- L95 _public prototype_ `bool GetCustomIESTexture(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LightFactory")`
- L98 _public prototype_ `bool SetCustomIESTexture(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LightFactory")`
- L101 _public prototype_ `bool GetCustomUseIESBrightness(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LightFactory")`
- L104 _public prototype_ `bool SetCustomUseIESBrightness(const bool& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LightFactory")`
- L107 _public prototype_ `bool GetCustomIESBrightnessScale(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LightFactory")`
- L110 _public prototype_ `bool SetCustomIESBrightnessScale(const float& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LightFactory")`
- L113 _public prototype_ `bool GetCustomRotation(FRotator& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LightFactory")`
- L116 _public prototype_ `bool SetCustomRotation(const FRotator& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | LightFactory")`
- L118 _public prototype_ `virtual void CopyWithObject(const UInterchangeFactoryBaseNode* SourceNode, UObject* Object) override;`
- L120 _public prototype_ `virtual void OnRestoreAllCustomAttributeDelegates() override;`

#### class `UInterchangeRectLightFactoryNode`  
`class UInterchangeRectLightFactoryNode : public UInterchangeLightFactoryNode`  
_L132-156_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeLightFactoryNode`
- L139 _public prototype_ `bool GetCustomSourceWidth(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | RectLightFactory")`
- L142 _public prototype_ `bool SetCustomSourceWidth(float AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | RectLightFactory")`
- L145 _public prototype_ `bool GetCustomSourceHeight(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | RectLightFactory")`
- L148 _public prototype_ `bool SetCustomSourceHeight(float AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | RectLightFactory")`
- L150 _public prototype_ `virtual void CopyWithObject(const UInterchangeFactoryBaseNode* SourceNode, UObject* Object) override;`
- L152 _public prototype_ `virtual void OnRestoreAllCustomAttributeDelegates() override;`

#### class `UInterchangePointLightFactoryNode`  
`class UInterchangePointLightFactoryNode : public UInterchangeLightFactoryNode`  
_L160-189_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeLightFactoryNode`
- L166 _public prototype_ `bool GetCustomUseInverseSquaredFalloff(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | PointLightFactory")`
- L169 _public prototype_ `bool SetCustomUseInverseSquaredFalloff(bool AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | PointLightFactory")`
- L172 _public prototype_ `bool GetCustomLightFalloffExponent(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | PointLightFactory")`
- L175 _public prototype_ `bool SetCustomLightFalloffExponent(float AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | PointLightFactory")`
- L178 _public prototype_ `bool GetCustomSourceRadius(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | PointLightFactory")`
- L181 _public prototype_ `bool SetCustomSourceRadius(float AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | PointLightFactory")`
- L183 _public prototype_ `virtual void CopyWithObject(const UInterchangeFactoryBaseNode* SourceNode, UObject* Object) override;`

#### class `UInterchangeSpotLightFactoryNode`  
`class UInterchangeSpotLightFactoryNode : public UInterchangePointLightFactoryNode`  
_L192-216_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangePointLightFactoryNode`
- L199 _public prototype_ `bool GetCustomInnerConeAngle(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SpotLightFactory")`
- L202 _public prototype_ `bool SetCustomInnerConeAngle(float AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SpotLightFactory")`
- L205 _public prototype_ `bool GetCustomOuterConeAngle(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SpotLightFactory")`
- L208 _public prototype_ `bool SetCustomOuterConeAngle(float AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SpotLightFactory")`
- L210 _public prototype_ `virtual void CopyWithObject(const UInterchangeFactoryBaseNode* SourceNode, UObject* Object) override;`

#### class `UInterchangeSkyLightFactoryNode`  
`class UInterchangeSkyLightFactoryNode : public UInterchangeBaseLightFactoryNode`  
_L219-241_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeBaseLightFactoryNode`
- L226 _public prototype_ `bool GetCustomCubemapDependency(FString& TextureCubeFactoryNodeUid) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkyLightFactory")`
- L229 _public prototype_ `bool SetCustomCubemapDependency(FString TextureCubeFactoryNodeUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkyLightFactory")`
- L232 _public prototype_ `bool GetCustomSourceType(EInterchangeSkyLightSourceType& SourceType) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkyLightFactory")`
- L235 _public prototype_ `bool SetCustomSourceType(EInterchangeSkyLightSourceType SourceType);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkyLightFactory")`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API INTERCHANGEFACTORYNODES_API`

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeMaterialFactoryNode.h` (Public)


#### class `UInterchangeBaseMaterialFactoryNode`  
`class UInterchangeBaseMaterialFactoryNode : public UInterchangeFactoryBaseNode`  
_L17-32_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UInterchangeFactoryBaseNode`
- L22 _public prototype_ `static FString GetMaterialFactoryNodeUidFromMaterialNodeUid(const FString& TranslatedNodeUid);`
- L25 _public prototype_ `bool GetCustomIsMaterialImportEnabled(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L28 _public prototype_ `bool SetCustomIsMaterialImportEnabled(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L31 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomIsMaterialImportEnabledKey = UE::Interchange::FAttributeKey(TEXT("IsMa`

#### class `UInterchangeMaterialFactoryNode`  
`class UInterchangeMaterialFactoryNode : public UInterchangeBaseMaterialFactoryNode`  
_L35-294_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeBaseMaterialFactoryNode`
- L41 _public prototype_ `virtual FString GetTypeName() const override;`
- L43 _public prototype_ `virtual class UClass* GetObjectClass() const override;`
- L48 _public prototype_ `bool GetBaseColorConnection(FString& ExpressionNodeUid, FString& OutputName) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L51 _public prototype_ `bool ConnectToBaseColor(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L54 _public prototype_ `bool ConnectOutputToBaseColor(const FString& ExpressionNodeUid, const FString& OutputName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L57 _public prototype_ `bool GetMetallicConnection(FString& ExpressionNodeUid, FString& OutputName) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L60 _public prototype_ `bool ConnectToMetallic(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L63 _public prototype_ `bool ConnectOutputToMetallic(const FString& ExpressionNodeUid, const FString& OutputName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L66 _public prototype_ `bool GetSpecularConnection(FString& ExpressionNodeUid, FString& OutputName) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L69 _public prototype_ `bool ConnectToSpecular(const FString& ExpressionNodeUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L72 _public prototype_ `bool ConnectOutputToSpecular(const FString& ExpressionNodeUid, const FString& OutputName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L75 _public prototype_ `bool GetRoughnessConnection(FString& ExpressionNodeUid, FString& OutputName) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L78 _public prototype_ `bool ConnectToRoughness(const FString& ExpressionNodeUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L81 _public prototype_ `bool ConnectOutputToRoughness(const FString& ExpressionNodeUid, const FString& OutputName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L84 _public prototype_ `bool GetAnisotropyConnection(FString& ExpressionNodeUid, FString& OutputName) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L87 _public prototype_ `bool ConnectToAnisotropy(const FString& ExpressionNodeUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L90 _public prototype_ `bool ConnectOutputToAnisotropy(const FString& ExpressionNodeUid, const FString& OutputName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L93 _public prototype_ `bool GetEmissiveColorConnection(FString& ExpressionNodeUid, FString& OutputName) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L96 _public prototype_ `bool ConnectToEmissiveColor(const FString& ExpressionNodeUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L99 _public prototype_ `bool ConnectOutputToEmissiveColor(const FString& ExpressionNodeUid, const FString& OutputName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L102 _public prototype_ `bool GetNormalConnection(FString& ExpressionNodeUid, FString& OutputName) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L105 _public prototype_ `bool ConnectToNormal(const FString& ExpressionNodeUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L108 _public prototype_ `bool ConnectOutputToNormal(const FString& ExpressionNodeUid, const FString& OutputName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L111 _public prototype_ `bool GetTangentConnection(FString& ExpressionNodeUid, FString& OutputName) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L114 _public prototype_ `bool ConnectToTangent(const FString& ExpressionNodeUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L117 _public prototype_ `bool ConnectOutputToTangent(const FString& ExpressionNodeUid, const FString& OutputName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L120 _public prototype_ `bool GetSubsurfaceConnection(FString& ExpressionNodeUid, FString& OutputName) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L123 _public prototype_ `bool ConnectToSubsurface(const FString& ExpressionNodeUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L126 _public prototype_ `bool ConnectOutputToSubsurface(const FString& ExpressionNodeUid, const FString& OutputName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L129 _public prototype_ `bool GetOpacityConnection(FString& ExpressionNodeUid, FString& OutputName) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L132 _public prototype_ `bool ConnectToOpacity(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L135 _public prototype_ `bool ConnectOutputToOpacity(const FString& ExpressionNodeUid, const FString& OutputName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L138 _public prototype_ `bool GetOcclusionConnection(FString& ExpressionNodeUid, FString& OutputName) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L141 _public prototype_ `bool ConnectToOcclusion(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L144 _public prototype_ `bool ConnectOutputToOcclusion(const FString& ExpressionNodeUid, const FString& OutputName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L147 _public prototype_ `bool GetRefractionConnection(FString& ExpressionNodeUid, FString& OutputName) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L150 _public prototype_ `bool ConnectToRefraction(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L153 _public prototype_ `bool ConnectOutputToRefraction(const FString& ExpressionNodeUid, const FString& OutputName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L156 _public prototype_ `bool GetClearCoatConnection(FString& ExpressionNodeUid, FString& OutputName) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L159 _public prototype_ `bool ConnectToClearCoat(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L162 _public prototype_ `bool ConnectOutputToClearCoat(const FString& ExpressionNodeUid, const FString& OutputName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L165 _public prototype_ `bool GetClearCoatRoughnessConnection(FString& ExpressionNodeUid, FString& OutputName) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L168 _public prototype_ `bool ConnectToClearCoatRoughness(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L171 _public prototype_ `bool ConnectOutputToClearCoatRoughness(const FString& ExpressionNodeUid, const FString& OutputName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L174 _public prototype_ `bool GetClearCoatNormalConnection(FString& ExpressionNodeUid, FString& OutputName) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L177 _public prototype_ `bool ConnectToClearCoatNormal(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L180 _public prototype_ `bool ConnectOutputToClearCoatNormal(const FString& ExpressionNodeUid, const FString& OutputName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L183 _public prototype_ `bool GetTransmissionColorConnection(FString& ExpressionNodeUid, FString& OutputName) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L186 _public prototype_ `bool ConnectToTransmissionColor(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L189 _public prototype_ `bool ConnectOutputToTransmissionColor(const FString& ExpressionNodeUid, const FString& OutputName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L192 _public prototype_ `bool GetSurfaceCoverageConnection(FString& ExpressionNodeUid, FString& OutputName) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L195 _public prototype_ `bool ConnectToSurfaceCoverage(const FString& ExpressionUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L198 _public prototype_ `bool ConnectOutputToSurfaceCoverage(const FString& ExpressionNodeUid, const FString& OutputName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L201 _public prototype_ `bool GetFuzzColorConnection(FString& ExpressionNodeUid, FString& OutputName) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L204 _public prototype_ `bool ConnectToFuzzColor(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L207 _public prototype_ `bool ConnectOutputToFuzzColor(const FString& ExpressionNodeUid, const FString& OutputName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L210 _public prototype_ `bool GetClothConnection(FString& ExpressionNodeUid, FString& OutputName) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L213 _public prototype_ `bool ConnectToCloth(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L216 _public prototype_ `bool ConnectOutputToCloth(const FString& ExpressionNodeUid, const FString& OutputName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L219 _public prototype_ `bool GetDisplacementConnection(FString& ExpressionNodeUid, FString& OutputName) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L222 _public prototype_ `bool ConnectToDisplacement(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L225 _public prototype_ `bool ConnectOutputToDisplacement(const FString& ExpressionNodeUid, const FString& OutputName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`
- L230 _public prototype_ `bool GetCustomShadingModel(TEnumAsByte<EMaterialShadingModel>& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L233 _public prototype_ `bool SetCustomShadingModel(const TEnumAsByte<EMaterialShadingModel>& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L236 _public prototype_ `bool GetCustomTranslucencyLightingMode(TEnumAsByte<ETranslucencyLightingMode>& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L239 _public prototype_ `bool SetCustomTranslucencyLightingMode(const TEnumAsByte<ETranslucencyLightingMode>& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L242 _public prototype_ `bool GetCustomBlendMode(TEnumAsByte<EBlendMode>& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L245 _public prototype_ `bool SetCustomBlendMode(const TEnumAsByte<EBlendMode>& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L248 _public prototype_ `bool GetCustomTwoSided(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L252 _public prototype_ `bool SetCustomTwoSided(const bool& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Sets if this shader graph should be rendered two sided or not. Defaults to off.
- L255 _public prototype_ `bool GetCustomOpacityMaskClipValue(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L258 _public prototype_ `bool SetCustomOpacityMaskClipValue(const float& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L261 _public prototype_ `bool GetCustomRefractionMethod(TEnumAsByte<ERefractionMode>& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L264 _public prototype_ `bool SetCustomRefractionMethod(const TEnumAsByte<ERefractionMode>& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L267 _public prototype_ `bool GetCustomScreenSpaceReflections(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L270 _public prototype_ `bool SetCustomScreenSpaceReflections(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L273 _public prototype_ `bool GetCustomDisplacementCenter(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L276 _public prototype_ `bool SetCustomDisplacementCenter(float AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L279 _public prototype_ `bool GetCustomDisplacementMagnitude(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L282 _public prototype_ `bool SetCustomDisplacementMagnitude(float AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L286 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(TranslucencyLightingMode) IMPLEMENT_NODE_ATTRIBUTE_KEY(BlendMode) IMPLEMENT_NODE_ATTRIBUTE_KEY(TwoSided) IMPLEMENT_NODE_ATTRIBUTE_KEY(OpacityMaskClipValue);`

#### class `UInterchangeMaterialExpressionFactoryNode`  
`class UInterchangeMaterialExpressionFactoryNode : public UInterchangeFactoryBaseNode`  
_L297-314_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBaseNode`
- L302 _public prototype_ `virtual FString GetTypeName() const override;`
- L306 _public prototype_ `bool GetCustomExpressionClassName(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L309 _public prototype_ `bool SetCustomExpressionClassName(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L312 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomExpressionClassNameKey = UE::Interchange::FAttributeKey(TEXT("Expr`

#### class `UInterchangeMaterialInstanceFactoryNode`  
`class UInterchangeMaterialInstanceFactoryNode : public UInterchangeBaseMaterialFactoryNode`  
_L317-363_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeBaseMaterialFactoryNode`
- L322 _public prototype_ `virtual FString GetTypeName() const override;`
- L323 _public prototype_ `virtual UClass* GetObjectClass() const override;`
- L327 _public prototype_ `bool GetCustomInstanceClassName(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialInstanceFactory")`
- L330 _public prototype_ `bool SetCustomInstanceClassName(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialInstanceFactory")`
- L333 _public prototype_ `bool GetCustomParent(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialInstanceFactory")`
- L336 _public prototype_ `bool SetCustomParent(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialInstanceFactory")`
- L339 _public prototype_ `bool GetCustomBlendMode(TEnumAsByte<EBlendMode>& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialInstanceFactory")`
- L342 _public prototype_ `bool SetCustomBlendMode(TEnumAsByte<EBlendMode> AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialInstanceFactory")`
- L345 _public prototype_ `bool GetCustomTwoSided(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialInstanceFactory")`
- L348 _public prototype_ `bool SetCustomTwoSided(bool AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialInstanceFactory")`
- L352 _public prototype_ `bool GetCustomEnableTessellation(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialInstanceFactory")` — Used to enable displacement
- L355 _public prototype_ `bool SetCustomEnableTessellation(bool AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialInstanceFactory")`

#### class `UInterchangeMaterialReferenceFactoryNode`  
`class UInterchangeMaterialReferenceFactoryNode : public UInterchangeBaseMaterialFactoryNode`  
_L373-380_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeBaseMaterialFactoryNode`
- desc: Describes a reference to an existing (as in, not imported) material. Note that the material is referenced via the UInterchangeFactoryBaseNode::CustomReferenceObject member. The idea is that mesh / actor factory nodes can reference one of these nodes as a slot dependency, and Interchange will assign that existing material to the corresponding slot during import
- L378 _public prototype_ `virtual FString GetTypeName() const override;`
- L379 _public prototype_ `virtual UClass* GetObjectClass() const override;`

#### class `UInterchangeMaterialFunctionCallExpressionFactoryNode`  
`class UInterchangeMaterialFunctionCallExpressionFactoryNode : public UInterchangeMaterialExpressionFactoryNode`  
_L383-406_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeMaterialExpressionFactoryNode`
- L388 _public prototype_ `virtual FString GetTypeName() const override;`
- L392 _public prototype_ `bool GetCustomMaterialFunctionDependency(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")`
- L401 _public prototype_ `bool SetCustomMaterialFunctionDependency(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Set the unique ID of the material function that the function call expression is referring to. Note that a call to AddFactoryDependencyUid is made to guarantee that the material function is created before the function call expression
- L404 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomMaterialFunctionDependencyKey = UE::Interchange::FAttributeKey(TEXT("Mate`

#### class `UInterchangeMaterialFunctionFactoryNode`  
`class UInterchangeMaterialFunctionFactoryNode : public UInterchangeBaseMaterialFactoryNode`  
_L409-423_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeBaseMaterialFactoryNode`
- L415 _public prototype_ `virtual FString GetTypeName() const override;`
- L417 _public prototype_ `virtual class UClass* GetObjectClass() const override;`
- L420 _public prototype_ `bool GetInputConnection(const FString& InputName, FString& ExpressionNodeUid, FString& OutputName) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | MaterialFactory")`

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeMeshActorFactoryNode.h` (Public)


#### class `UInterchangeMeshActorFactoryNode`  
`class UInterchangeMeshActorFactoryNode : public UInterchangeActorFactoryNode`  
_L12-97_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeActorFactoryNode`
- L17 _public prototype_ `UInterchangeMeshActorFactoryNode();`
- L22 _public function_ `virtual void Serialize(FArchive& Ar) override` — Override Serialize() to restore SlotMaterialDependencies on load.
- L34 _public prototype_ `bool SetCustomInstancedAssetFactoryNodeUid(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Set the resolved asset factory node.
- L38 _public prototype_ `bool GetCustomInstancedAssetFactoryNodeUid(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Get the resolved asset factory node.
- L44 _public prototype_ `void GetSlotMaterialDependencies(TMap<FString, FString>& OutMaterialDependencies) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Retrieve the correspondence table between slot names and assigned materials for this object.
- L50 _public prototype_ `bool GetSlotMaterialDependencyUid(const FString& SlotName, FString& OutMaterialDependency) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Retrieve the Material dependency for the specified slot of this object.
- L56 _public prototype_ `bool SetSlotMaterialDependencyUid(const FString& SlotName, const FString& MaterialDependencyUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Add a Material dependency to the specified slot of this object.
- L62 _public prototype_ `bool RemoveSlotMaterialDependencyUid(const FString& SlotName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Remove the Material dependency associated with the specified slot name from this object.
- L66 _public prototype_ `bool SetCustomAnimationAssetUidToPlay(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMesh")` — Set the animation asset for this scene node to play. (This is only relevant for SkeletalMeshActors: scene nodes that are instantiating skeletal meshes.)
- L69 _public prototype_ `bool GetCustomAnimationAssetUidToPlay(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMesh")` — Get the animation asset set for this scene node to play.
- L73 _public prototype_ `bool GetCustomGeometricTransform(FTransform& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Get the geometric offset. Any mesh attached to this scene node will be offset using this transform.
- L77 _public prototype_ `bool SetCustomGeometricTransform(const FTransform& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Set the geometric offset. Any mesh attached to this scene node will be offset using this transform.
- L79 _public function_ `bool GetCustomKeepSectionsSeparate(bool& AttributeValue) const`
- L87 _private member_ `UE::Interchange::TMapAttributeHelper<FString, FString> SlotMaterialDependencies;`
- L90 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomInstancedAssetFactoryNodeUidKey = UE::Interchange::FAttributeKey(TEXT("Inst` — A factory node can reference an asset on top of base asset:
- L93 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomAnimationAssetUidToPlayKey = UE::Interchange::FAttributeKey(TEXT("Anim` — A scene node can reference an animation asset on top of base asset:
- L96 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomGeometricTransformKey = UE::Interchange::FAttributeKey(TEXT("Geom` — A scene node can have a transform apply to the mesh it reference.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEFACTORYNODES_API`

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeMeshFactoryNode.h` (Public)


#### struct `UE::Interchange::FMeshFactoryNodeStaticData`  
`struct FMeshFactoryNodeStaticData : public FBaseNodeStaticData`  
_L15-20_
- inherits: `FBaseNodeStaticData`
- L17 _public prototype_ `static const FAttributeKey& GetLodDependenciesBaseKey();`
- L18 _public prototype_ `static const FAttributeKey& GetSlotMaterialDependencyBaseKey();`
- L19 _public prototype_ `static const FAttributeKey& GetAssemblyPartDependencyBaseKey();`

#### class `UInterchangeMeshFactoryNode`  
`class UInterchangeMeshFactoryNode : public UInterchangeFactoryBaseNode`  
_L25-314_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Abstract)`
- inherits: `UInterchangeFactoryBaseNode`
- L30 _public prototype_ `UInterchangeMeshFactoryNode();`
- L35 _public function_ `virtual void Serialize(FArchive& Ar) override` — Override Serialize() to restore SlotMaterialDependencies and AssemblyPartDependencies on load.
- L51 _public prototype_ `virtual FString GetKeyDisplayName(const UE::Interchange::FAttributeKey& NodeAttributeKey) const override;`
- L52 _public prototype_ `virtual FString GetAttributeCategory(const UE::Interchange::FAttributeKey& NodeAttributeKey) const override;`
- L53 _public prototype_ `virtual bool ShouldHideAttribute(const UE::Interchange::FAttributeKey& NodeAttributeKey) const override;`
- L58 _public prototype_ `static const FString& GetMeshSocketPrefix();`
- L62 _public prototype_ `int32 GetLodDataCount() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Return the number of LODs this static mesh has.
- L65 _public prototype_ `void GetLodDataUniqueIds(TArray<FString>& OutLodDataUniqueIds) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")`
- L68 _public prototype_ `bool AddLodDataUniqueId(const FString& LodDataUniqueId);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")`
- L71 _public prototype_ `bool RemoveLodDataUniqueId(const FString& LodDataUniqueId);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")`
- L75 _public prototype_ `bool GetCustomVertexColorReplace(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Query whether the static mesh factory should replace the vertex color. Return false if the attribute was not set.
- L79 _public prototype_ `bool SetCustomVertexColorReplace(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Set whether the static mesh factory should replace the vertex color. Return false if the attribute could not be set.
- L83 _public prototype_ `bool GetCustomVertexColorIgnore(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Query whether the static mesh factory should ignore the vertex color. Return false if the attribute was not set.
- L87 _public prototype_ `bool SetCustomVertexColorIgnore(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Set whether the static mesh factory should ignore the vertex color. Return false if the attribute could not be set.
- L91 _public prototype_ `bool GetCustomVertexColorOverride(FColor& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Query whether the static mesh factory should override the vertex color. Return false if the attribute was not set.
- L95 _public prototype_ `bool SetCustomVertexColorOverride(const FColor& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Set whether the static mesh factory should override the vertex color. Return false if the attribute could not be set.
- L99 _public prototype_ `bool GetCustomKeepSectionsSeparate(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Query whether sections with matching materials are kept separate and will not get combined.
- L103 _public prototype_ `bool SetCustomKeepSectionsSeparate(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Set whether sections with matching materials are kept separate and will not get combined.
- L107 _public prototype_ `bool GetCustomImportSockets(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Query whether the mesh factory should create sockets.
- L111 _public prototype_ `bool SetCustomImportSockets(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Set whether the mesh factory should create sockets.
- L115 _public prototype_ `void GetSlotMaterialDependencies(TMap<FString, FString>& OutMaterialDependencies) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Retrieve the correspondence table between slot names and assigned materials for this object.
- L119 _public prototype_ `bool GetSlotMaterialDependencyUid(const FString& SlotName, FString& OutMaterialDependency) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Retrieve the Material dependency for the specified slot of this object.
- L123 _public prototype_ `bool SetSlotMaterialDependencyUid(const FString& SlotName, const FString& MaterialDependencyUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Add a Material dependency to the specified slot of this object.
- L127 _public prototype_ `bool RemoveSlotMaterialDependencyUid(const FString& SlotName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Remove the Material dependency associated with the specified slot name of this object.
- L131 _public prototype_ `bool ResetSlotMaterialDependencies();` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Reset all the material dependencies.
- L135 _public prototype_ `int32 GetAssemblyPartDependenciesCount() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Retrieve the number of Nanite assembly part dependencies for this object.
- L139 _public prototype_ `void GetAssemblyPartDependencies(TMap<FString, FString>& OutAssemblyPartDependencies) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Retrieve the Nanite assembly part dependencies for this object.
- L143 _public prototype_ `bool SetAssemblyPartDependencyUid(const FString& MeshUid, const FString& AssemblyPartDependencyUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Add a Nanite assembly part dependency to this object.
- L147 _public prototype_ `bool RemoveAssemblyPartDependencyUid(const FString& MeshUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Remove a Nanite assembly part dependency associated with this object
- L151 _public prototype_ `bool ResetAssemblyDependencies();` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Reset all the Nanite assembly dependencies.
- L155 _public prototype_ `bool GetCustomLODGroup(FName& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Query whether a custom LOD group is set for the mesh.
- L159 _public prototype_ `bool SetCustomLODGroup(const FName& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Set a custom LOD group for the mesh.
- L163 _public prototype_ `bool GetCustomRecomputeNormals(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Query whether normals in the imported mesh are ignored and recomputed. When normals are recomputed, the tangents are also recomputed.
- L167 _public prototype_ `bool SetCustomRecomputeNormals(const bool& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Set whether normals in the imported mesh are ignored and recomputed. When normals are recomputed, the tangents are also recomputed.
- L171 _public prototype_ `bool GetCustomRecomputeTangents(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Query whether tangents in the imported mesh are ignored and recomputed.
- L175 _public prototype_ `bool SetCustomRecomputeTangents(const bool& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Set whether tangents in the imported mesh are ignored and recomputed.
- L179 _public prototype_ `bool GetCustomUseMikkTSpace(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Query whether tangents are recomputed using MikkTSpace when they need to be recomputed.
- L183 _public prototype_ `bool SetCustomUseMikkTSpace(const bool& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Set whether tangents are recomputed using MikkTSpace when they need to be recomputed.
- L187 _public prototype_ `bool GetCustomComputeWeightedNormals(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Query whether normals are recomputed by weighting the surface area and the corner angle of the triangle as a ratio.
- L191 _public prototype_ `bool SetCustomComputeWeightedNormals(const bool& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Set whether normals are recomputed by weighting the surface area and the corner angle of the triangle as a ratio.
- L195 _public prototype_ `bool GetCustomUseHighPrecisionTangentBasis(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Query whether tangents are stored at 16-bit precision instead of the default 8-bit precision.
- L199 _public prototype_ `bool SetCustomUseHighPrecisionTangentBasis(const bool& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Set whether tangents are stored at 16-bit precision instead of the default 8-bit precision.
- L203 _public prototype_ `bool GetCustomUseFullPrecisionUVs(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Query whether UVs are stored at full floating point precision.
- L207 _public prototype_ `bool SetCustomUseFullPrecisionUVs(const bool& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Set whether UVs are stored at full floating point precision.
- L211 _public prototype_ `bool GetCustomUseBackwardsCompatibleF16TruncUVs(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Query whether UVs are converted to 16-bit by a legacy truncation process instead of the default rounding process. This may avoid differences when reimporting older content.
- L215 _public prototype_ `bool SetCustomUseBackwardsCompatibleF16TruncUVs(const bool& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Set whether UVs are converted to 16-bit by a legacy truncation process instead of the default rounding process. This may avoid differences when reimporting older content.
- L219 _public prototype_ `bool GetCustomRemoveDegenerates(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Query whether degenerate triangles are removed.
- L223 _public prototype_ `bool SetCustomRemoveDegenerates(const bool& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | Mesh")` — Set whether degenerate triangles are removed.
- L225 _public prototype_ `virtual void CopyWithObject(const UInterchangeFactoryBaseNode* SourceNode, UObject* Object) override;`
- L229 _public prototype_ `bool GetPayloadKeyStringAttribute(const FString& PayloadAttributeKey, FString& Value);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Get a payload key string attribute from this node. Returns false if the attribute does not exist.
- L233 _public prototype_ `bool AddPayloadKeyStringAttribute(const FString& PayloadAttributeKey, const FString& Value);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Add a string attribute for the payload. Returns false if the attribute does not exist or if it cannot be added.
- L237 _public prototype_ `bool GetPayloadKeyFloatAttribute(const FString& PayloadAttributeKey, float& Value);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Get a payload key float attribute from this node. Returns false if the attribute does not exist.
- L241 _public prototype_ `bool AddPayloadKeyFloatAttribute(const FString& PayloadAttributeKey, float Value);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Add a float attribute for the payload. Returns false if the attribute does not exist or if it cannot be added.
- L245 _public prototype_ `bool GetPayloadKeyInt32Attribute(const FString& PayloadAttributeKey, int32& Value);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Get a payload key int32 attribute from this node. Returns false if the attribute does not exist.
- L249 _public prototype_ `bool AddPayloadKeyInt32Attribute(const FString& PayloadAttributeKey, int32 Value);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Add an int attribute for the payload. Returns false if the attribute does not exist or if it cannot be added.
- L253 _public prototype_ `bool GetPayloadKeyBooleanAttribute(const FString& PayloadAttributeKey, bool& Value);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Get a payload key boolean attribute from this node. Returns false if the attribute does not exist.
- L257 _public prototype_ `bool AddPayloadKeyBooleanAttribute(const FString& PayloadAttributeKey, bool Value);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Add a boolean attribute for the payload. Returns false if the attribute does not exist or if it cannot be added.
- L261 _public prototype_ `bool GetPayloadKeyDoubleAttribute(const FString& PayloadAttributeKey, double& Value);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Get a payload key double attribute from this node. Returns false if the attribute does not exist.
- L265 _public prototype_ `bool AddPayloadKeyDoubleAttribute(const FString& PayloadAttributeKey, double Value);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Mesh")` — Add a double attribute for the payload. Returns false if the attribute does not exist or if it cannot be added.
- L267 _public prototype_ `static void CopyPayloadKeyStorageAttributes(const UInterchangeBaseNode* SourceNode, UE::Interchange::FAttributeStorage& DestinationStorage);`
- L272 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(VertexColorIgnore) IMPLEMENT_NODE_ATTRIBUTE_KEY(VertexColorOverride) IMPLEMENT_NODE_ATTRIBUTE_KEY(KeepSectionsSeparate) IMPLEMENT_NODE_ATTRIBUTE_KEY(LODGroup) IMPLEMENT_NODE_ATTRIBUTE_KEY(RecomputeNormals) IMPLEMENT_NODE_ATTRIBUTE_KEY(RecomputeTangents) IMPLEMENT_NODE_ATTRIBUTE_KEY(UseMikkTSpace) IMPLEMENT_NODE_ATTRIBUTE_KEY(ComputeWeightedNormals) IMPLEMENT_NODE_ATTRIBUTE_KEY(UseHighPrecisionTangentBasis) IMPLEMENT_NODE_ATTRIBUTE_KEY(UseFullPrecisionUVs) IMPLEMENT_NODE_ATTRIBUTE_KEY(UseBackwardsCompatibleF16TruncUVs) IMPLEMENT_NODE_ATTRIBUTE_KEY(RemoveDegenerates) IMPLEMENT_NODE_ATTRIBUTE_KEY(ImportSockets) UE::Interchange::TArrayAttributeHelper<FString> LodDependencies;`
- L287 _private member_ `UE::Interchange::TMapAttributeHelper<FString, FString> SlotMaterialDependencies;`
- L288 _private member_ `UE::Interchange::TMapAttributeHelper<FString, FString> AssemblyPartDependencies;`
- L291 _protected prototype_ `virtual void FillAssetClassFromAttribute() PURE_VIRTUAL("Fil`
- L292 _protected prototype_ `virtual bool SetNodeClassFromClassAttribute() PURE_VIRTUAL("SetNodeClassFromCl`
- L294 _protected member_ `const UE::Interchange::FAttributeKey ClassNameAttributeKey = UE::Interchange::FBaseNodeStaticData::ClassTypeAttributeKey();`
- L296 _protected prototype_ `bool ApplyCustomRecomputeNormalsToAsset(UObject * Asset) const;`
- L297 _protected prototype_ `bool FillCustomRecomputeNormalsFromAsset(UObject * Asset);`
- L298 _protected prototype_ `bool ApplyCustomRecomputeTangentsToAsset(UObject * Asset) const;`
- L299 _protected prototype_ `bool FillCustomRecomputeTangentsFromAsset(UObject * Asset);`
- L300 _protected prototype_ `bool ApplyCustomUseMikkTSpaceToAsset(UObject * Asset) const;`
- L301 _protected prototype_ `bool FillCustomUseMikkTSpaceFromAsset(UObject * Asset);`
- L302 _protected prototype_ `bool ApplyCustomComputeWeightedNormalsToAsset(UObject * Asset) const;`
- L303 _protected prototype_ `bool FillCustomComputeWeightedNormalsFromAsset(UObject * Asset);`
- L304 _protected prototype_ `bool ApplyCustomUseHighPrecisionTangentBasisToAsset(UObject * Asset) const;`
- L305 _protected prototype_ `bool FillCustomUseHighPrecisionTangentBasisFromAsset(UObject * Asset);`
- L306 _protected prototype_ `bool ApplyCustomUseFullPrecisionUVsToAsset(UObject * Asset) const;`
- L307 _protected prototype_ `bool FillCustomUseFullPrecisionUVsFromAsset(UObject * Asset);`
- L308 _protected prototype_ `bool ApplyCustomUseBackwardsCompatibleF16TruncUVsToAsset(UObject * Asset) const;`
- L309 _protected prototype_ `bool FillCustomUseBackwardsCompatibleF16TruncUVsFromAsset(UObject * Asset);`
- L310 _protected prototype_ `bool ApplyCustomRemoveDegeneratesToAsset(UObject * Asset) const;`
- L311 _protected prototype_ `bool FillCustomRemoveDegeneratesFromAsset(UObject * Asset);`
- L313 _protected member_ `bool bIsNodeClassInitialized = false;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API INTERCHANGEFACTORYNODES_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Interchange` (scope `UE`)

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangePhysicsAssetFactoryNode.h` (Public)


#### class `UInterchangePhysicsAssetFactoryNode`  
`class UInterchangePhysicsAssetFactoryNode : public UInterchangeFactoryBaseNode`  
_L18-153_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UInterchangeFactoryBaseNode`
- L30 _public function_ `void InitializePhysicsAssetNode(const FString& UniqueID, const FString& DisplayLabel, const FString& InAssetClass, UInterchangeBaseNodeContainer* NodeContainer)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Skeleton")` — Initialize node data. @param: UniqueID - The unique ID for this node. @param DisplayLabel - The name of the node. @param InAssetClass - The class the Skeleton factory will create for this node.
- L39 _public function_ `virtual void Serialize(FArchive& Ar) override`
- L55 _public function_ `virtual FString GetTypeName() const override` — Return the node type name of the class. This is used when reporting errors.
- L62 _public function_ `virtual class UClass* GetObjectClass() const override` — Get the class this node creates.
- L74 _public function_ `virtual bool ShouldHideAttribute(const UE::Interchange::FAttributeKey& NodeAttributeKey) const override`
- L85 _public function_ `virtual FGuid GetHash() const override`
- L93 _public function_ `bool GetCustomSkeletalMeshUid(FString& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Skeleton")` — Get the Skeletal Mesh asset UID used to create the data in the post-pipeline step.
- L99 _public function_ `bool SetCustomSkeletalMeshUid(const FString& AttributeValue)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Skeleton")` — Set the Skeletal Mesh asset UID used to create the data in the post-pipeline step.
- L105 _public function_ `virtual bool IsRuntimeImportAllowed() const override` — Return if the import of the class is allowed at runtime.
- L112 _private function_ `void FillAssetClassFromAttribute()`
- L126 _private function_ `bool SetNodeClassFromClassAttribute()`
- L135 _private function_ `bool IsEditorOnlyDataDefined()`
- L144 _private member_ `const UE::Interchange::FAttributeKey ClassNameAttributeKey = UE::Interchange::FBaseNodeStaticData::ClassTypeAttributeKey();`
- L146 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomSkeletalMeshUidKey = UE::Interchange::FAttributeKey(TEXT("Skel` — SkeletalMesh asset Uid use to create the data in the post pipeline step
- L150 _protected member_ `TSubclassOf<UPhysicsAsset> AssetClass;`
- L152 _protected member_ `bool bIsNodeClassInitialized = false;`

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeSceneComponentFactoryNodes.h` (Public)


#### class `UInterchangeSceneComponentFactoryNode`  
`class UInterchangeSceneComponentFactoryNode : public UInterchangeFactoryBaseNode`  
_L13-54_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBaseNode`
- desc: TODO: move to its own file.
- L18 _public prototype_ `UInterchangeSceneComponentFactoryNode();`
- L20 _public prototype_ `virtual FString GetTypeName() const override;`
- L22 _public prototype_ `virtual UClass* GetObjectClass() const override;`
- L26 _public prototype_ `bool AddComponentUid(const FString& ComponentUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | Component")`
- L29 _public prototype_ `void GetComponentUids(TArray<FString>& OutComponentUids) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | Component")`
- L33 _public prototype_ `bool GetCustomLocalTransform(FTransform& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Component")`
- L36 _public prototype_ `bool SetCustomLocalTransform(const FTransform& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Component")`
- L40 _public prototype_ `bool GetCustomComponentVisibility(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Component")`
- L43 _public prototype_ `bool SetCustomComponentVisibility(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Component")`
- L47 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomLocalTransformKey = UE::Interchange::FAttributeKey(TEXT("Loca` — Component's Local Transform.
- L50 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomComponentVisibilityKey = UE::Interchange::FAttributeKey(TEXT("Comp` — Component's Visibility
- L53 _private member_ `UE::Interchange::TArrayAttributeHelper<FString> ComponentUids;` — Childnre Component Uids.

#### class `UInterchangeInstancedStaticMeshComponentFactoryNode`  
`class UInterchangeInstancedStaticMeshComponentFactoryNode : public UInterchangeSceneComponentFactoryNode`  
_L57-99_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeSceneComponentFactoryNode`
- L61 _public prototype_ `UInterchangeInstancedStaticMeshComponentFactoryNode ();`
- L63 _public prototype_ `virtual FString GetTypeName() const override;`
- L65 _public prototype_ `virtual UClass* GetObjectClass() const override;`
- L68 _public prototype_ `void AddInstanceTransform(const FTransform& InstanceTransform);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | ComponentFactory | Instanced")`
- L70 _public prototype_ `void AddInstanceTransforms(const TArray<FTransform>& InInstanceTransforms);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | ComponentFactory | Instanced")`
- L73 _public prototype_ `void GetInstanceTransforms(TArray<FTransform>& OutInstanceTransforms) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | ComponentFactory | Instanced")`
- L77 _public prototype_ `bool GetCustomInstancedAssetUid(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | ComponentFactory | Instanced")` — Get which asset, if any, a scene node is instantiating. Return false if the Attribute was not set previously.
- L81 _public prototype_ `bool SetCustomInstancedAssetUid(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | ComponentFactory | Instanced")` — Add an asset for this scene node to instantiate.
- L85 _public prototype_ `bool GetCustomHierarchicalISM(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | ComponentFactory | Instanced")`
- L88 _public prototype_ `bool SetCustomHierarchicalISM(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Scene | ComponentFactory | Instanced")`
- L92 _private member_ `UE::Interchange::TArrayAttributeHelper<FTransform> InstanceTransforms;` — Instanced StaticMesh Component's Instances.
- L95 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomAssetInstanceUidKey = UE::Interchange::FAttributeKey(TEXT("Asse` — To track/connect StaticMesh.
- L98 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomHierarchicalISMKey = UE::Interchange::FAttributeKey(TEXT("Hier` — To track if it should be Hierarchical ISM

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEFACTORYNODES_API`

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeSceneImportAssetFactoryNode.h` (Public)


#### class `UInterchangeSceneImportAssetFactoryNode`  
`class UInterchangeSceneImportAssetFactoryNode : public UInterchangeFactoryBaseNode`  
_L13-23_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBaseNode`
- L19 _public prototype_ `virtual class UClass* GetObjectClass() const override;` — UInterchangeFactoryBaseNode Begin

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API INTERCHANGEFACTORYNODES_API`

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeSceneVariantSetsFactoryNode.h` (Public)


#### class `UInterchangeSceneVariantSetsFactoryNode`  
`class UInterchangeSceneVariantSetsFactoryNode : public UInterchangeFactoryBaseNode`  
_L13-75_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBaseNode`
- L17 _private prototype_ `UInterchangeSceneVariantSetsFactoryNode();`
- L20 _public function_ `static FStringView StaticAssetTypeName()`
- L28 _public function_ `virtual FString GetTypeName() const override` — Return the node type name of the class. This is used when reporting errors.
- L35 _public prototype_ `virtual class UClass* GetObjectClass() const override;` — Get the class this node creates.
- L41 _public prototype_ `int32 GetCustomVariantSetUidCount() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SceneVariantSetFactory")` — Retrieve the number of unique IDs of all translated VariantSets for this object.
- L47 _public prototype_ `void GetCustomVariantSetUids(TArray<FString>& OutVariantUids) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SceneVariantSetFactory")` — Retrieve the unique IDs of all translated VariantSets for this object.
- L53 _public prototype_ `void GetCustomVariantSetUid(const int32 Index, FString& OutVariantUid) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SceneVariantSetFactory")` — Retrieve the UID of the VariantSet with the specified index.
- L59 _public prototype_ `bool AddCustomVariantSetUid(const FString& VariantUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SceneVariantSetFactory")` — Add a unique id of a translated VariantSet for this object.
- L65 _public prototype_ `bool RemoveCustomVariantSetUid(const FString& VariantUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SceneVariantSetFactory")` — Remove the specified unique ID of a translated VariantSet from this object.
- L68 _public function_ `virtual bool IsRuntimeImportAllowed() const override` — Return if the import of the class is allowed at runtime.
- L74 _private member_ `UE::Interchange::TArrayAttributeHelper<FString> CustomVariantSetUids;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API INTERCHANGEFACTORYNODES_API`

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeSkeletalMeshFactoryNode.h` (Public)


#### enum `EInterchangeSkeletalMeshContentType`  
`enum class EInterchangeSkeletalMeshContentType : uint8`  
_L16-22_
- reflection: `UENUM(BlueprintType)`
- L18 _public enumerator_ `All UMETA(DisplayName = "Geometry and Skin Weights", ToolTip = "Imports all skeletal mesh content: geometry and skin weights.")`
- L19 _public enumerator_ `Geometry UMETA(DisplayName = "Geometry Only", ToolTip = "Imports the skeletal mesh geometry only. This creates a default skeleton, or maps the geometry to the existing one. You can import morph targets and LODs with the mesh.")`
- L20 _public enumerator_ `SkinningWeights UMETA(DisplayName = "Skin Weights Only", ToolTip = "Imports the skeletal mesh skin weights only. No geometry, morph targets, or LODs are imported.")`
- L21 _public enumerator_ `MAX`

#### class `UInterchangeSkeletalMeshFactoryNode`  
`class UInterchangeSkeletalMeshFactoryNode : public UInterchangeMeshFactoryNode`  
_L25-228_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeMeshFactoryNode`
- L30 _public prototype_ `UInterchangeSkeletalMeshFactoryNode();`
- L39 _public prototype_ `void InitializeSkeletalMeshNode(const FString& UniqueID, const FString& DisplayLabel, const FString& InAssetClass, UInterchangeBaseNodeContainer* NodeContainer);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMesh")` — Initialize node data. Also adds it to NodeContainer. @param: UniqueID - The unique ID for this node. @param DisplayLabel - The name of the node. @param InAssetClass - The class the SkeletalMesh factory will create for this node.
- L44 _public prototype_ `virtual FString GetTypeName() const override;` — Return the node type name of the class. This is used when reporting errors.
- L47 _public prototype_ `virtual class UClass* GetObjectClass() const override;` — Get the class this node creates.
- L52 _public prototype_ `bool GetCustomSkeletonSoftObjectPath(FSoftObjectPath& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMesh")` — Query the skeletal mesh factory skeleton UObject. Return false if the attribute was not set.
- L56 _public prototype_ `bool SetCustomSkeletonSoftObjectPath(const FSoftObjectPath& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMesh")` — Set the skeletal mesh factory skeleton UObject. Return false if the attribute could not be set.
- L60 _public prototype_ `bool GetCustomImportMorphTarget(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMesh")` — Query whether the skeletal mesh factory should create morph targets. Return false if the attribute was not set.
- L64 _public prototype_ `bool SetCustomImportMorphTarget(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMesh")` — Set whether the skeletal mesh factory should create morph targets. Return false if the attribute could not be set.
- L72 _public prototype_ `bool GetCustomAddCurveMetadataToSkeleton(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Get the custom attribute AddCurveMetadataToSkeleton. Return false if the attribute is not set. Note - If this setting is disabled, curve metadata will be added to skeletal meshes for morph targets, but no metadata entry will be created for general curves.
- L80 _public prototype_ `bool SetCustomAddCurveMetadataToSkeleton(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | AnimSequence")` — Set the custom attribute AddCurveMetadataToSkeleton. Return false if the attribute could not be set. Note - If this setting is disabled, curve metadata will be added to skeletal meshes for morph targets, but no metadata entry will be created for general curves.
- L84 _public prototype_ `bool GetCustomImportVertexAttributes(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMesh")` — Query whether the skeletal mesh factory should import vertex attributes. Return false if the attribute was not set.
- L88 _public prototype_ `bool SetCustomImportVertexAttributes(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMesh")` — Set whether the skeletal mesh factory should import vertex attributes. Return false if the attribute could not be set.
- L92 _public prototype_ `bool GetCustomCreatePhysicsAsset(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMesh")` — Query whether the skeletal mesh factory should create a physics asset. Return false if the attribute was not set.
- L96 _public prototype_ `bool SetCustomCreatePhysicsAsset(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMesh")` — Set whether the skeletal mesh factory should create a physics asset. Return false if the attribute could not be set.
- L100 _public prototype_ `bool GetCustomPhysicAssetSoftObjectPath(FSoftObjectPath& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMesh")` — Query a physics asset the skeletal mesh factory should use. Return false if the attribute was not set.
- L104 _public prototype_ `bool SetCustomPhysicAssetSoftObjectPath(const FSoftObjectPath& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMesh")` — Set a physics asset the skeletal mesh factory should use. Return false if the attribute could not be set.
- L108 _public prototype_ `bool GetCustomImportContentType(EInterchangeSkeletalMeshContentType& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMesh")` — Query the skeletal mesh import content type. This content type determines whether the factory imports partial or full translated content. Return false if the attribute was not set.
- L112 _public prototype_ `bool SetCustomImportContentType(const EInterchangeSkeletalMeshContentType& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMesh")` — Set the skeletal mesh import content type. This content type determines whether the factory imports partial or full translated content. Return false if the attribute could not be set.
- L116 _public prototype_ `bool GetCustomUseHighPrecisionSkinWeights(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMesh")` — Query the skeletal mesh UseHighPrecisionSkinWeights setting.
- L120 _public prototype_ `bool SetCustomUseHighPrecisionSkinWeights(const bool& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMesh")` — Set the skeletal mesh UseHighPrecisionSkinWeights setting.
- L124 _public prototype_ `bool GetCustomThresholdPosition(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMesh")` — Query the skeletal mesh threshold value that is used to decide whether two vertex positions are equal.
- L128 _public prototype_ `bool SetCustomThresholdPosition(const float& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMesh")` — Set the skeletal mesh threshold value that is used to decide whether two vertex positions are equal.
- L132 _public prototype_ `bool GetCustomThresholdTangentNormal(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMesh")` — Query the skeletal mesh threshold value that is used to decide whether two normals, tangents, or bi-normals are equal.
- L136 _public prototype_ `bool SetCustomThresholdTangentNormal(const float& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMesh")` — Set the skeletal mesh threshold value that is used to decide whether two normals, tangents, or bi-normals are equal.
- L140 _public prototype_ `bool GetCustomThresholdUV(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMesh")` — Query the skeletal mesh threshold value that is used to decide whether two UVs are equal.
- L144 _public prototype_ `bool SetCustomThresholdUV(const float& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMesh")` — Set the skeletal mesh threshold value that is used to decide whether two UVs are equal.
- L148 _public prototype_ `bool GetCustomMorphThresholdPosition(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMesh")` — Query the skeletal mesh threshold value that is used to compare vertex position equality when computing morph target deltas.
- L152 _public prototype_ `bool SetCustomMorphThresholdPosition(const float& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMesh")` — Set the skeletal mesh threshold value that is used to compare vertex position equality when computing morph target deltas.
- L160 _public prototype_ `bool GetCustomBoneInfluenceLimit(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMesh")` — Query the maximum number of bone influences to allow each vertex in this mesh to use. If set higher than the limit determined by the project settings, it has no effect. If set to 0, the value is taken from the DefaultBoneInfluenceLimit project setting.
- L168 _public prototype_ `bool SetCustomBoneInfluenceLimit(const int32& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMesh")` — Set the maximum number of bone influences to allow each vertex in this mesh to use. If set higher than the limit determined by the project settings, it has no effect. If set to 0, the value is taken from the DefaultBoneInfluenceLimit project setting.
- L172 _public prototype_ `bool GetCustomMergeMorphTargetShapeWithSameName(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMesh")` — Query whether the skeletal mesh factory should merge morph target shape with the same name under one morph target. Return false if the attribute was not set.
- L176 _public prototype_ `bool SetCustomMergeMorphTargetShapeWithSameName(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMesh")` — Set whether the skeletal mesh factory should merge morph target shape with the same name under one morph target. Return false if the attribute could not be set.
- L181 _public prototype_ `virtual void AppendAssetRegistryTags(FAssetRegistryTagsContext Context) const override;` — The skeletal mesh thumbnail can have an overlay if the last reimport was geometry only. This thumbnail overlay feature uses the metadata to find out if the last import was geometry only.
- L183 _public prototype_ `virtual void AppendAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const override;` — `UE_DEPRECATED(5.4, "Implement the version that takes FAssetRegistryTagsContext instead.")`
- L185 _public prototype_ `virtual void CopyWithObject(const UInterchangeFactoryBaseNode* SourceNode, UObject* Object) override;`
- L188 _public function_ `virtual bool IsRuntimeImportAllowed () const override` — Return if the import of the class is allowed at runtime.
- L194 _private prototype_ `virtual void FillAssetClassFromAttribute() override;`
- L195 _private prototype_ `virtual bool SetNodeClassFromClassAttribute() override;`
- L197 _private member_ `const UE::Interchange::FAttributeKey ClassNameAttributeKey = UE::Interchange::FBaseNodeStaticData::ClassTypeAttributeKey();`
- L199 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(AddCurveMetadataToSkeleton) IMPLEMENT_NODE_ATTRIBUTE_KEY(ImportVertexAttributes) IMPLEMENT_NODE_ATTRIBUTE_KEY(SkeletonSoftObjectPath) IMPLEMENT_NODE_ATTRIBUTE_KEY(CreatePhysicsAsset) IMPLEMENT_NODE_ATTRIBUTE_KEY(PhysicAssetSoftObjectPath) IMPLEMENT_NODE_ATTRIBUTE_KEY(ImportContentType) IMPLEMENT_NODE_ATTRIBUTE_KEY(UseHighPrecisionSkinWeights) IMPLEMENT_NODE_ATTRIBUTE_KEY(ThresholdPosition) IMPLEMENT_NODE_ATTRIBUTE_KEY(ThresholdTangentNormal) IMPLEMENT_NODE_ATTRIBUTE_KEY(ThresholdUV) IMPLEMENT_NODE_ATTRIBUTE_KEY(MorphThresholdPosition) IMPLEMENT_NODE_ATTRIBUTE_KEY(BoneInfluenceLimit) IMPLEMENT_NODE_ATTRIBUTE_KEY(MergeMorphTargetShapeWithSameName) bool ApplyCustomUseHighPrecisionSkinWeightsToAsset(UObject* Asset) const;`
- L215 _private prototype_ `bool FillCustomUseHighPrecisionSkinWeightsFromAsset(UObject* Asset);`
- L216 _private prototype_ `bool ApplyCustomThresholdPositionToAsset(UObject* Asset) const;`
- L217 _private prototype_ `bool FillCustomThresholdPositionFromAsset(UObject* Asset);`
- L218 _private prototype_ `bool ApplyCustomThresholdTangentNormalToAsset(UObject* Asset) const;`
- L219 _private prototype_ `bool FillCustomThresholdTangentNormalFromAsset(UObject* Asset);`
- L220 _private prototype_ `bool ApplyCustomThresholdUVToAsset(UObject* Asset) const;`
- L221 _private prototype_ `bool FillCustomThresholdUVFromAsset(UObject* Asset);`
- L222 _private prototype_ `bool ApplyCustomMorphThresholdPositionToAsset(UObject* Asset) const;`
- L223 _private prototype_ `bool FillCustomMorphThresholdPositionFromAsset(UObject* Asset);`
- L224 _private prototype_ `bool ApplyCustomBoneInfluenceLimitToAsset(UObject* Asset) const;`
- L225 _private prototype_ `bool FillCustomBoneInfluenceLimitFromAsset(UObject* Asset);`
- L227 _protected member_ `TSubclassOf<USkeletalMesh> AssetClass;`

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeSkeletalMeshLodDataNode.h` (Public)


#### struct `UE::Interchange::FSkeletalMeshNodeLodDataStaticData`  
`struct FSkeletalMeshNodeLodDataStaticData : public FBaseNodeStaticData`  
_L18-24_
- inherits: `FBaseNodeStaticData`
- L20 _public prototype_ `static const FAttributeKey& GetLODMeshDataArrayBaseKey();`
- L23 _public prototype_ `static const FAttributeKey& GetMeshUidsBaseKey();` — `UE_DEPRECATED(5.8, "Deprecated. Use GetLODMeshDataArrayBaseKey instead.")`

#### class `UInterchangeSkeletalMeshLodDataNode`  
`class UInterchangeSkeletalMeshLodDataNode : public UInterchangeFactoryBaseNode`  
_L30-101_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBaseNode`
- L35 _public prototype_ `UInterchangeSkeletalMeshLodDataNode();`
- L40 _public prototype_ `virtual FString GetTypeName() const override;` — Return the node type name of the class. This is used when reporting errors.
- L43 _public prototype_ `virtual FString GetKeyDisplayName(const UE::Interchange::FAttributeKey& NodeAttributeKey) const override;`
- L45 _public prototype_ `virtual FString GetAttributeCategory(const UE::Interchange::FAttributeKey& NodeAttributeKey) const override;`
- L51 _public prototype_ `bool GetCustomSkeletonUid(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMeshLodData")` — Query the LOD skeletal mesh factory skeleton reference. Return false if the attribute was not set.
- L55 _public prototype_ `bool SetCustomSkeletonUid(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMeshLodData")` — Set the LOD skeletal mesh factory skeleton reference. Return false if the attribute could not be set.
- L59 _public prototype_ `int32 GetMeshUidsCount() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMeshLodData")` — Return the number of mesh geometries this LOD will be made from.
- L64 _public prototype_ `void GetMeshUids(TArray<FString>& OutMeshUids) const;` — `UE_DEPRECATED(5.8, "Deprecated. Use GetLODMeshDataArray instead.")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMeshLodData")` — Query all mesh geometry this LOD will be made from.
- L69 _public prototype_ `bool AddMeshUid(const FString& MeshUid);` — `UE_DEPRECATED(5.8, "Deprecated. Use AddLODMeshData instead.")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMeshLodData")` — Add a mesh geometry used to create this LOD geometry.
- L73 _public prototype_ `void GetLODMeshDataArray(TArray<FInterchangeLODMeshData>& OutLODMeshDataArray) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMeshLodData")` — Gets all MeshUid+Transform pairs.
- L77 _public prototype_ `bool AddLODMeshData(const FInterchangeLODMeshData& LODMeshData);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMeshLodData")` — Adds a MeshUid + Transform pair to the node.
- L81 _public prototype_ `bool RemoveAllMeshes();` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMeshLodData")` — Remove all mesh geometry used to create this LOD geometry.
- L85 _public prototype_ `void RemoveMeshUid(const FString& MeshUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | SkeletalMeshLodData")` — Removes all occurances of a specific MeshUid from the entries.
- L88 _public function_ `virtual bool IsRuntimeImportAllowed() const override` — Return if the import of the class is allowed at runtime.
- L95 _private prototype_ `bool IsEditorOnlyDataDefined();`
- L97 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomSkeletonUidKey = UE::Interchange::FAttributeKey(TEXT("__Sk`
- L99 _private member_ `UE::Interchange::TArrayAttributeHelper<FInterchangeLODMeshData> LODMeshDataArray;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API INTERCHANGEFACTORYNODES_API`
- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Interchange` (scope `UE`)

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeSkeletonFactoryNode.h` (Public)


#### class `UInterchangeSkeletonFactoryNode`  
`class UInterchangeSkeletonFactoryNode : public UInterchangeFactoryBaseNode`  
_L17-196_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UInterchangeFactoryBaseNode`
- L23 _public function_ `UInterchangeSkeletonFactoryNode()`
- L35 _public function_ `void InitializeSkeletonNode(const FString& UniqueID, const FString& DisplayLabel, const FString& InAssetClass, UInterchangeBaseNodeContainer* NodeContainer)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Skeleton")` — Initialize node data. @param: UniqueID - The unique ID for this node. @param DisplayLabel - The name of the node. @param InAssetClass - The class the Skeleton factory will create for this node.
- L44 _public function_ `virtual void Serialize(FArchive& Ar) override`
- L60 _public function_ `virtual FString GetTypeName() const override` — Return the node type name of the class. This is used when reporting errors.
- L67 _public function_ `virtual class UClass* GetObjectClass() const override` — Get the class this node creates.
- L77 _public function_ `virtual FGuid GetHash() const override`
- L85 _public function_ `bool GetCustomRootJointUid(FString& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Skeleton")` — Return false if the attribute was not set previously.
- L91 _public function_ `bool SetCustomRootJointUid(const FString& AttributeValue)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Skeleton")`
- L98 _public function_ `bool GetCustomUseTimeZeroForBindPose(bool& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Skeleton")` — Query whether this skeleton should replace joint transforms with time-zero evaluation instead of bind pose.
- L105 _public function_ `bool SetCustomUseTimeZeroForBindPose(const bool& AttributeValue)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Skeleton")` — If AttributeValue is true, force this skeleton to use time-zero evaluation instead of its bind pose.
- L112 _public function_ `bool GetCustomSkeletalMeshFactoryNodeUid(FString& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Skeleton", meta = (DeprecatedFunction, DeprecationMessage = "Use GetCustomSkeletalMeshFactoryNodeUidAtIndex (or GetCustomSkeletalMeshFactoryNodeUids) instead."))`
- L124 _public function_ `int32 GetCustomSkeletalMeshFactoryNodeCount() const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Skeleton")`
- L130 _public function_ `void GetCustomSkeletalMeshFactoryNodeUids(TArray<FString>& OutDependencies) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Skeleton")`
- L136 _public function_ `void GetCustomSkeletalMeshFactoryNodeUidAtIndex(const int32 Index, FString& OutDependency) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Skeleton")`
- L142 _public function_ `bool AddCustomSkeletalMeshFactoryNodeUid(const FString& InDependency)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Skeleton")`
- L149 _private function_ `void FillAssetClassFromAttribute()`
- L163 _private function_ `bool SetNodeClassFromClassAttribute()`
- L172 _private function_ `bool IsEditorOnlyDataDefined()`
- L181 _private member_ `const UE::Interchange::FAttributeKey ClassNameAttributeKey = UE::Interchange::FBaseNodeStaticData::ClassTypeAttributeKey();`
- L184 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomRootJointIDKey = UE::Interchange::FAttributeKey(TEXT("Root` — Skeleton
- L185 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomUseTimeZeroForBindPoseKey = UE::Interchange::FAttributeKey(TEXT("UseT`
- L187 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomSkeletalMeshFactoryNodeUidKey = UE::Interchange::FAttributeKey(TEXT("Skel` — const UE::Interchange::FAttributeKey Macro_CustomSkeletalMeshFactoryNodeUidKey = UE::Interchange::FAttributeKey(TEXT("SkeletalMeshFactoryNodeUid"));
- L189 _private member_ `UE::Interchange::TArrayAttributeHelper<FString> SkeletalMeshFactoryNodeUids;`
- L193 _protected member_ `TSubclassOf<USkeleton> AssetClass;`
- L195 _protected member_ `bool bIsNodeClassInitialized = false;`

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeSparseVolumeTextureFactoryNode.h` (Public)


#### class `UInterchangeSparseVolumeTextureFactoryNode`  
`class UInterchangeSparseVolumeTextureFactoryNode : public UInterchangeFactoryBaseNode`  
_L14-126_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBaseNode`
- L19 _public prototype_ `virtual FString GetTypeName() const override;`
- L20 _public prototype_ `virtual class UClass* GetObjectClass() const override;`
- L25 _public prototype_ `bool GetCustomAttributesAFormat(EInterchangeSparseVolumeTextureFormat& Format) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Gets the data type of the AttributesA texture of the SparseVolumeTexture we'll create
- L29 _public prototype_ `bool SetCustomAttributesAFormat(EInterchangeSparseVolumeTextureFormat Format);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Sets the data type of the AttributesA texture of the SparseVolumeTexture we'll create
- L33 _public prototype_ `bool GetCustomAttributesBFormat(EInterchangeSparseVolumeTextureFormat& Format) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Gets the data type of the AttributesB texture of the SparseVolumeTexture we'll create
- L37 _public prototype_ `bool SetCustomAttributesBFormat(EInterchangeSparseVolumeTextureFormat Format);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Sets the data type of the AttributesB texture of the SparseVolumeTexture we'll create
- L41 _public prototype_ `bool GetCustomAttributesAChannelX(FString& GridNameAndComponentIndex) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Gets the grid name and component index that will be assigned to the AttributesA texture, channel X (e.g. "density_0" or "temperature_2")
- L45 _public prototype_ `bool SetCustomAttributesAChannelX(FString GridNameAndComponentIndex);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Sets the grid name and component index that will be assigned to the AttributesA texture, channel X (e.g. "density_0" or "temperature_2")
- L49 _public prototype_ `bool GetCustomAttributesAChannelY(FString& GridNameAndComponentIndex) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Gets the grid name and component index that will be assigned to the AttributesA texture, channel Y (e.g. "density_0" or "temperature_2")
- L53 _public prototype_ `bool SetCustomAttributesAChannelY(FString GridNameAndComponentIndex);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Sets the grid name and component index that will be assigned to the AttributesA texture, channel Y (e.g. "density_0" or "temperature_2")
- L57 _public prototype_ `bool GetCustomAttributesAChannelZ(FString& GridNameAndComponentIndex) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Gets the grid name and component index that will be assigned to the AttributesA texture, channel Z (e.g. "density_0" or "temperature_2")
- L61 _public prototype_ `bool SetCustomAttributesAChannelZ(FString GridNameAndComponentIndex);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Sets the grid name and component index that will be assigned to the AttributesA texture, channel Z (e.g. "density_0" or "temperature_2")
- L65 _public prototype_ `bool GetCustomAttributesAChannelW(FString& GridNameAndComponentIndex) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Gets the grid name and component index that will be assigned to the AttributesA texture, channel W (e.g. "density_0" or "temperature_2")
- L69 _public prototype_ `bool SetCustomAttributesAChannelW(FString GridNameAndComponentIndex);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Sets the grid name and component index that will be assigned to the AttributesA texture, channel W (e.g. "density_0" or "temperature_2")
- L73 _public prototype_ `bool GetCustomAttributesBChannelX(FString& GridNameAndComponentIndex) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Gets the grid name and component index that will be assigned to the AttributesB texture, channel X (e.g. "density_0" or "temperature_2")
- L77 _public prototype_ `bool SetCustomAttributesBChannelX(FString GridNameAndComponentIndex);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Sets the grid name and component index that will be assigned to the AttributesB texture, channel X (e.g. "density_0" or "temperature_2")
- L81 _public prototype_ `bool GetCustomAttributesBChannelY(FString& GridNameAndComponentIndex) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Gets the grid name and component index that will be assigned to the AttributesB texture, channel Y (e.g. "density_0" or "temperature_2")
- L85 _public prototype_ `bool SetCustomAttributesBChannelY(FString GridNameAndComponentIndex);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Sets the grid name and component index that will be assigned to the AttributesB texture, channel Y (e.g. "density_0" or "temperature_2")
- L89 _public prototype_ `bool GetCustomAttributesBChannelZ(FString& GridNameAndComponentIndex) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Gets the grid name and component index that will be assigned to the AttributesB texture, channel Z (e.g. "density_0" or "temperature_2")
- L93 _public prototype_ `bool SetCustomAttributesBChannelZ(FString GridNameAndComponentIndex);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Sets the grid name and component index that will be assigned to the AttributesB texture, channel Z (e.g. "density_0" or "temperature_2")
- L97 _public prototype_ `bool GetCustomAttributesBChannelW(FString& GridNameAndComponentIndex) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Gets the grid name and component index that will be assigned to the AttributesB texture, channel W (e.g. "density_0" or "temperature_2")
- L101 _public prototype_ `bool SetCustomAttributesBChannelW(FString GridNameAndComponentIndex);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Sets the grid name and component index that will be assigned to the AttributesB texture, channel W (e.g. "density_0" or "temperature_2")
- L105 _public prototype_ `bool GetCustomAnimationID(FString& OutAnimationID) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Gets the animation ID of the volume nodes that were grouped together to create this animated SparseVolumeTextureFactoryNode, if any
- L109 _public prototype_ `bool SetCustomAnimationID(const FString& InAnimationID);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Material")` — Sets the animation ID of the volume nodes that were grouped together to create this animated SparseVolumeTextureFactoryNode, if any

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API INTERCHANGEFACTORYNODES_API`

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeSpecularProfileFactoryNode.h` (Public)


#### class `UInterchangeSpecularProfileFactoryNode`  
`class UInterchangeSpecularProfileFactoryNode : public UInterchangeFactoryBaseNode`  
_L14-43_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBaseNode`
- L23 _public prototype_ `virtual FString GetTypeName() const override;` — Return the node type name of the class. This is used when reporting errors.
- L25 _public prototype_ `virtual class UClass* GetObjectClass() const override;`
- L28 _public prototype_ `bool SetCustomFormat(ESpecularProfileFormat Format);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | SpecularProfile")`
- L31 _public prototype_ `bool GetCustomFormat(ESpecularProfileFormat& Format) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | SpecularProfile")`
- L34 _public prototype_ `bool GetCustomTexture(FString& TextureUid) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | SpecularProfile")`
- L37 _public prototype_ `bool SetCustomTexture(const FString& TextureUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | FactoryNode | SpecularProfile")`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEFACTORYNODES_API`

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeStaticMeshFactoryNode.h` (Public)


#### enum `EInterchangeNaniteShapePreservation`  
`enum class EInterchangeNaniteShapePreservation : int32`  
_L19-24_
- reflection: `UENUM()`
- desc: Mirrors ENaniteShapePreservation from Engine/EngineTypes.h
- L21 _public enumerator_ `None`
- L22 _public enumerator_ `PreserveArea`
- L23 _public enumerator_ `Voxelize`

#### enum `EInterchangeNaniteGenerateFallback`  
`enum class EInterchangeNaniteGenerateFallback : int32`  
_L28-32_
- reflection: `UENUM()`
- desc: Mirrors ENaniteGenerateFallback from Engine/EngineTypes.h
- L30 _public enumerator_ `PlatformDefault`
- L31 _public enumerator_ `Enabled`

#### enum `EInterchangeNaniteFallbackTarget`  
`enum class EInterchangeNaniteFallbackTarget : int32`  
_L36-41_
- reflection: `UENUM()`
- desc: Mirrors ENaniteFallbackTarget from Engine/EngineTypes.h
- L38 _public enumerator_ `Auto`
- L39 _public enumerator_ `PercentTriangles`
- L40 _public enumerator_ `RelativeError`

#### struct `UE::Interchange::FStaticMeshNodeStaticData`  
`struct FStaticMeshNodeStaticData : public FBaseNodeStaticData`  
_L47-51_
- inherits: `FBaseNodeStaticData`
- L49 _public prototype_ `static const FAttributeKey& GetLODScreenSizeBaseKey();`
- L50 _public prototype_ `static const FAttributeKey& GetSocketUidsBaseKey();`

#### class `UInterchangeStaticMeshFactoryNode`  
`class UInterchangeStaticMeshFactoryNode : public UInterchangeMeshFactoryNode`  
_L57-519_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeMeshFactoryNode`
- L62 _public prototype_ `UInterchangeStaticMeshFactoryNode();`
- L71 _public prototype_ `void InitializeStaticMeshNode(const FString& UniqueID, const FString& DisplayLabel, const FString& InAssetClass, UInterchangeBaseNodeContainer* NodeContainer);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Initialize node data. Also adds it to NodeContainer. @param UniqueID - The unique ID for this node. @param DisplayLabel - The name of the node. @param InAssetClass - The class the StaticMesh factory will create for this node.
- L76 _public prototype_ `virtual FString GetTypeName() const override;` — Return the node type name of the class. This is used when reporting errors.
- L79 _public prototype_ `virtual class UClass* GetObjectClass() const override;` — Get the class this node creates.
- L81 _public prototype_ `virtual void CopyWithObject(const UInterchangeFactoryBaseNode* SourceNode, UObject* Object) override;`
- L85 _public prototype_ `virtual FString GetKeyDisplayName(const UE::Interchange::FAttributeKey& NodeAttributeKey) const override;`
- L86 _public prototype_ `virtual FString GetAttributeCategory(const UE::Interchange::FAttributeKey& NodeAttributeKey) const override;`
- L93 _public prototype_ `bool GetCustomAutoComputeLODScreenSizes(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Get whether the static mesh factory should auto compute LOD Screen Sizes. Return false if the attribute was not set.
- L97 _public prototype_ `bool SetCustomAutoComputeLODScreenSizes(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Set whether the static mesh factory should auto compute LOD Screen Sizes. Return false if the attribute was not set.
- L101 _public prototype_ `int32 GetLODScreenSizeCount() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Returns the number of LOD Screen Sizes the static mesh has.
- L105 _public prototype_ `void GetLODScreenSizes(TArray<float>& OutLODScreenSizes) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Returns All the LOD Screen Sizes set for the static mesh.
- L109 _public prototype_ `bool SetLODScreenSizes(const TArray<float>& InLODScreenSizes);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Sets the LOD Screen Sizes for the static mesh.
- L113 _public prototype_ `bool GetCustomBuildNanite(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Get whether the static mesh factory should set the Nanite build setting. Return false if the attribute was not set.
- L117 _public prototype_ `bool SetCustomBuildNanite(const bool& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Set whether the static mesh factory should set the Nanite build setting. Return false if the attribute was not set.
- L121 _public prototype_ `int32 GetSocketUidCount() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Return the number of socket UIDs this static mesh has.
- L124 _public prototype_ `void GetSocketUids(TArray<FString>& OutSocketUids) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L127 _public prototype_ `bool AddSocketUid(const FString& SocketUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L130 _public prototype_ `bool AddSocketUids(const TArray<FString>& InSocketUids);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L133 _public prototype_ `bool RemoveSocketUd(const FString& SocketUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L137 _public prototype_ `bool GetCustomBuildReversedIndexBuffer(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Get whether the static mesh should build a reversed index buffer.
- L141 _public prototype_ `bool SetCustomBuildReversedIndexBuffer(const bool& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Set whether the static mesh should build a reversed index buffer.
- L145 _public prototype_ `bool GetCustomGenerateLightmapUVs(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Get whether the static mesh should generate lightmap UVs.
- L149 _public prototype_ `bool SetCustomGenerateLightmapUVs(const bool& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Set whether the static mesh should generate lightmap UVs.
- L156 _public prototype_ `bool GetCustomGenerateDistanceFieldAsIfTwoSided(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Get whether to generate the distance field by treating every triangle hit as a front face. This prevents the distance field from being discarded due to the mesh being open, but also lowers distance field ambient occlusion quality.
- L163 _public prototype_ `bool SetCustomGenerateDistanceFieldAsIfTwoSided(const bool& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Set whether to generate the distance field by treating every triangle hit as a front face. This prevents the distance field from being discarded due to the mesh being open, but also lowers distance field ambient occlusion quality.
- L167 _public prototype_ `bool GetCustomSupportFaceRemap(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Get whether the static mesh is set up for use with physical material masks.
- L171 _public prototype_ `bool SetCustomSupportFaceRemap(const bool& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Set whether the static mesh is set up for use with physical material masks.
- L175 _public prototype_ `bool GetCustomMinLightmapResolution(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Get the amount of padding used to pack UVs for the static mesh.
- L179 _public prototype_ `bool SetCustomMinLightmapResolution(const int32& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Set the amount of padding used to pack UVs for the static mesh.
- L183 _public prototype_ `bool GetCustomSrcLightmapIndex(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Get the index of the UV that is used as the source for generating lightmaps for the static mesh.
- L187 _public prototype_ `bool SetCustomSrcLightmapIndex(const int32& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Set the index of the UV that is used as the source for generating lightmaps for the static mesh.
- L191 _public prototype_ `bool GetCustomDstLightmapIndex(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Get the index of the UV that is used to store generated lightmaps for the static mesh.
- L195 _public prototype_ `bool SetCustomDstLightmapIndex(const int32& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Set the index of the UV that is used to store generated lightmaps for the static mesh.
- L199 _public prototype_ `bool GetCustomBuildScale3D(FVector& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Get the local scale that is applied when building the static mesh.
- L203 _public prototype_ `bool SetCustomBuildScale3D(const FVector& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Set the local scale that is applied when building the static mesh.
- L210 _public prototype_ `bool GetCustomDistanceFieldResolutionScale(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Get the scale to apply to the mesh when allocating the distance field volume texture. The default scale is 1, which assumes that the mesh will be placed unscaled in the world.
- L217 _public prototype_ `bool SetCustomDistanceFieldResolutionScale(const float& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Set the scale to apply to the mesh when allocating the distance field volume texture. The default scale is 1, which assumes that the mesh will be placed unscaled in the world.
- L221 _public prototype_ `bool GetCustomDistanceFieldReplacementMesh(FSoftObjectPath& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Get the static mesh asset whose distance field will be used as the distance field for the imported mesh.
- L225 _public prototype_ `bool SetCustomDistanceFieldReplacementMesh(const FSoftObjectPath& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Set the static mesh asset whose distance field will be used as the distance field for the imported mesh.
- L234 _public prototype_ `bool GetCustomMaxLumenMeshCards(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Get the maximum number of Lumen mesh cards to generate for this mesh. More cards means that the surface will have better coverage, but will result in increased runtime overhead. Set this to 0 to disable mesh card generation for this mesh. The default is 12.
- L243 _public prototype_ `bool SetCustomMaxLumenMeshCards(const int32& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Set the maximum number of Lumen mesh cards to generate for this mesh. More cards means that the surface will have better coverage, but will result in increased runtime overhead. Set this to 0 to disable mesh card generation for this mesh. The default is 12.
- L252 _public prototype_ `bool SetCustomSubstituteUID(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Currently specifically used for LOD group nodes. If an LOD Group is identified as identical to another one (when bakeMesh is turned off), then said LOD Group's asset won't be created and the substitute UID will be set to the FactoryNode that's identical to the one at hand.
- L259 _public prototype_ `bool GetCustomSubstituteUID(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")` — Gets the Substitute UID, said UID can be used to acquire an identical FactoryNode. (for more see SetCustomSubstituteUID)
- L264 _public prototype_ `bool GetCustomNaniteExplicitTangents(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L267 _public prototype_ `bool SetCustomNaniteExplicitTangents(const bool& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L270 _public prototype_ `bool GetCustomNaniteLerpUVs(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L273 _public prototype_ `bool SetCustomNaniteLerpUVs(const bool& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L276 _public prototype_ `bool GetCustomNaniteSeparable(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L279 _public prototype_ `bool SetCustomNaniteSeparable(const bool& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L282 _public prototype_ `bool GetCustomNaniteVoxelNDF(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L285 _public prototype_ `bool SetCustomNaniteVoxelNDF(const bool& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L288 _public prototype_ `bool GetCustomNaniteVoxelOpacity(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L291 _public prototype_ `bool SetCustomNaniteVoxelOpacity(const bool& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L294 _public prototype_ `bool GetCustomNaniteShapePreservation(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L297 _public prototype_ `bool SetCustomNaniteShapePreservation(const int32& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L300 _public prototype_ `bool GetCustomNanitePositionPrecision(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L303 _public prototype_ `bool SetCustomNanitePositionPrecision(const int32& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L306 _public prototype_ `bool GetCustomNaniteNormalPrecision(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L309 _public prototype_ `bool SetCustomNaniteNormalPrecision(const int32& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L312 _public prototype_ `bool GetCustomNaniteTangentPrecision(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L315 _public prototype_ `bool SetCustomNaniteTangentPrecision(const int32& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L318 _public prototype_ `bool GetCustomNaniteBoneWeightPrecision(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L321 _public prototype_ `bool SetCustomNaniteBoneWeightPrecision(const int32& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L324 _public prototype_ `bool GetCustomNaniteTargetMinimumResidencyInKB(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L327 _public prototype_ `bool SetCustomNaniteTargetMinimumResidencyInKB(const int32& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L330 _public prototype_ `bool GetCustomNaniteKeepPercentTriangles(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L333 _public prototype_ `bool SetCustomNaniteKeepPercentTriangles(const float& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L336 _public prototype_ `bool GetCustomNaniteTrimRelativeError(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L339 _public prototype_ `bool SetCustomNaniteTrimRelativeError(const float& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L342 _public prototype_ `bool GetCustomNaniteGenerateFallback(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L345 _public prototype_ `bool SetCustomNaniteGenerateFallback(const int32& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L348 _public prototype_ `bool GetCustomNaniteFallbackTarget(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L351 _public prototype_ `bool SetCustomNaniteFallbackTarget(const int32& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L354 _public prototype_ `bool GetCustomNaniteFallbackPercentTriangles(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L357 _public prototype_ `bool SetCustomNaniteFallbackPercentTriangles(const float& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L360 _public prototype_ `bool GetCustomNaniteFallbackRelativeError(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L363 _public prototype_ `bool SetCustomNaniteFallbackRelativeError(const float& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L366 _public prototype_ `bool GetCustomNaniteMaxEdgeLengthFactor(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L369 _public prototype_ `bool SetCustomNaniteMaxEdgeLengthFactor(const float& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L372 _public prototype_ `bool GetCustomNaniteNumRays(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L375 _public prototype_ `bool SetCustomNaniteNumRays(const int32& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L378 _public prototype_ `bool GetCustomNaniteVoxelLevel(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L381 _public prototype_ `bool SetCustomNaniteVoxelLevel(const int32& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L384 _public prototype_ `bool GetCustomNaniteRayBackUp(float& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L387 _public prototype_ `bool SetCustomNaniteRayBackUp(const float& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L390 _public prototype_ `bool GetCustomNaniteDisplacementUVChannel(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L393 _public prototype_ `bool SetCustomNaniteDisplacementUVChannel(const int32& AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMesh")`
- L396 _private prototype_ `virtual void FillAssetClassFromAttribute() override;`
- L397 _private prototype_ `virtual bool SetNodeClassFromClassAttribute() override;`
- L399 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomBuildReversedIndexBufferKey = UE::Interchange::FAttributeKey(TEXT("Buil`
- L400 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomGenerateLightmapUVsKey = UE::Interchange::FAttributeKey(TEXT("Gene`
- L401 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomGenerateDistanceFieldAsIfTwoSidedKey = UE::Interchange::FAttributeKey(TEXT("Gene`
- L402 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomSupportFaceRemapKey = UE::Interchange::FAttributeKey(TEXT("Supp`
- L403 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomMinLightmapResolutionKey = UE::Interchange::FAttributeKey(TEXT("MinL`
- L404 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomSrcLightmapIndexKey = UE::Interchange::FAttributeKey(TEXT("SrcL`
- L405 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomDstLightmapIndexKey = UE::Interchange::FAttributeKey(TEXT("DstL`
- L406 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomBuildScale3DKey = UE::Interchange::FAttributeKey(TEXT("Buil`
- L407 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomDistanceFieldResolutionScaleKey = UE::Interchange::FAttributeKey(TEXT("Dist`
- L408 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomDistanceFieldReplacementMeshKey = UE::Interchange::FAttributeKey(TEXT("Dist`
- L409 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomMaxLumenMeshCardsKey = UE::Interchange::FAttributeKey(TEXT("MaxL`
- L410 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomBuildNaniteKey = UE::Interchange::FAttributeKey(TEXT("Buil`
- L411 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomAutoComputeLODScreenSizesKey = UE::Interchange::FAttributeKey(TEXT("Auto`
- L412 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomSubstituteUIDKey = UE::Interchange::FAttributeKey(TEXT("Subs`
- L415 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomNaniteExplicitTangentsKey = UE::Interchange::FAttributeKey(TEXT("Nani` — Nanite build settings attribute keys
- L416 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomNaniteLerpUVsKey = UE::Interchange::FAttributeKey(TEXT("Nani`
- L417 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomNaniteSeparableKey = UE::Interchange::FAttributeKey(TEXT("Nani`
- L418 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomNaniteVoxelNDFKey = UE::Interchange::FAttributeKey(TEXT("Nani`
- L419 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomNaniteVoxelOpacityKey = UE::Interchange::FAttributeKey(TEXT("Nani`
- L420 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomNaniteShapePreservationKey = UE::Interchange::FAttributeKey(TEXT("Nani`
- L421 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomNanitePositionPrecisionKey = UE::Interchange::FAttributeKey(TEXT("Nani`
- L422 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomNaniteNormalPrecisionKey = UE::Interchange::FAttributeKey(TEXT("Nani`
- L423 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomNaniteTangentPrecisionKey = UE::Interchange::FAttributeKey(TEXT("Nani`
- L424 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomNaniteBoneWeightPrecisionKey = UE::Interchange::FAttributeKey(TEXT("Nani`
- L425 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomNaniteTargetMinimumResidencyInKBKey = UE::Interchange::FAttributeKey(TEXT("Nani`
- L426 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomNaniteKeepPercentTrianglesKey = UE::Interchange::FAttributeKey(TEXT("Nani`
- L427 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomNaniteTrimRelativeErrorKey = UE::Interchange::FAttributeKey(TEXT("Nani`
- L428 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomNaniteGenerateFallbackKey = UE::Interchange::FAttributeKey(TEXT("Nani`
- L429 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomNaniteFallbackTargetKey = UE::Interchange::FAttributeKey(TEXT("Nani`
- L430 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomNaniteFallbackPercentTrianglesKey = UE::Interchange::FAttributeKey(TEXT("Nani`
- L431 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomNaniteFallbackRelativeErrorKey = UE::Interchange::FAttributeKey(TEXT("Nani`
- L432 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomNaniteMaxEdgeLengthFactorKey = UE::Interchange::FAttributeKey(TEXT("Nani`
- L433 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomNaniteNumRaysKey = UE::Interchange::FAttributeKey(TEXT("Nani`
- L434 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomNaniteVoxelLevelKey = UE::Interchange::FAttributeKey(TEXT("Nani`
- L435 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomNaniteRayBackUpKey = UE::Interchange::FAttributeKey(TEXT("Nani`
- L436 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomNaniteDisplacementUVChannelKey = UE::Interchange::FAttributeKey(TEXT("Nani`
- L438 _private member_ `UE::Interchange::TArrayAttributeHelper<float> LODScreenSizes;`
- L439 _private member_ `UE::Interchange::TArrayAttributeHelper<FString> SocketUids;`
- L447 _protected prototype_ `bool ApplyCustomBuildReversedIndexBufferToAsset(UObject* Asset) const;`
- L448 _protected prototype_ `bool FillCustomBuildReversedIndexBufferFromAsset(UObject* Asset);`
- L449 _protected prototype_ `bool ApplyCustomGenerateLightmapUVsToAsset(UObject* Asset) const;`
- L450 _protected prototype_ `bool FillCustomGenerateLightmapUVsFromAsset(UObject* Asset);`
- L451 _protected prototype_ `bool ApplyCustomGenerateDistanceFieldAsIfTwoSidedToAsset(UObject* Asset) const;`
- L452 _protected prototype_ `bool FillCustomGenerateDistanceFieldAsIfTwoSidedFromAsset(UObject* Asset);`
- L453 _protected prototype_ `bool ApplyCustomSupportFaceRemapToAsset(UObject* Asset) const;`
- L454 _protected prototype_ `bool FillCustomSupportFaceRemapFromAsset(UObject* Asset);`
- L455 _protected prototype_ `bool ApplyCustomMinLightmapResolutionToAsset(UObject* Asset) const;`
- L456 _protected prototype_ `bool FillCustomMinLightmapResolutionFromAsset(UObject* Asset);`
- L457 _protected prototype_ `bool ApplyCustomSrcLightmapIndexToAsset(UObject* Asset) const;`
- L458 _protected prototype_ `bool FillCustomSrcLightmapIndexFromAsset(UObject* Asset);`
- L459 _protected prototype_ `bool ApplyCustomDstLightmapIndexToAsset(UObject* Asset) const;`
- L460 _protected prototype_ `bool FillCustomDstLightmapIndexFromAsset(UObject* Asset);`
- L461 _protected prototype_ `bool ApplyCustomBuildScale3DToAsset(UObject* Asset) const;`
- L462 _protected prototype_ `bool FillCustomBuildScale3DFromAsset(UObject* Asset);`
- L463 _protected prototype_ `bool ApplyCustomDistanceFieldResolutionScaleToAsset(UObject* Asset) const;`
- L464 _protected prototype_ `bool FillCustomDistanceFieldResolutionScaleFromAsset(UObject* Asset);`
- L465 _protected prototype_ `bool ApplyCustomDistanceFieldReplacementMeshToAsset(UObject* Asset) const;`
- L466 _protected prototype_ `bool FillCustomDistanceFieldReplacementMeshFromAsset(UObject* Asset);`
- L467 _protected prototype_ `bool ApplyCustomMaxLumenMeshCardsToAsset(UObject* Asset) const;`
- L468 _protected prototype_ `bool FillCustomMaxLumenMeshCardsFromAsset(UObject* Asset);`
- L471 _protected prototype_ `bool ApplyCustomNaniteExplicitTangentsToAsset(UObject* Asset) const;` — Nanite build settings Apply/Fill
- L472 _protected prototype_ `bool FillCustomNaniteExplicitTangentsFromAsset(UObject* Asset);`
- L473 _protected prototype_ `bool ApplyCustomNaniteLerpUVsToAsset(UObject* Asset) const;`
- L474 _protected prototype_ `bool FillCustomNaniteLerpUVsFromAsset(UObject* Asset);`
- L475 _protected prototype_ `bool ApplyCustomNaniteSeparableToAsset(UObject* Asset) const;`
- L476 _protected prototype_ `bool FillCustomNaniteSeparableFromAsset(UObject* Asset);`
- L477 _protected prototype_ `bool ApplyCustomNaniteVoxelNDFToAsset(UObject* Asset) const;`
- L478 _protected prototype_ `bool FillCustomNaniteVoxelNDFFromAsset(UObject* Asset);`
- L479 _protected prototype_ `bool ApplyCustomNaniteVoxelOpacityToAsset(UObject* Asset) const;`
- L480 _protected prototype_ `bool FillCustomNaniteVoxelOpacityFromAsset(UObject* Asset);`
- L481 _protected prototype_ `bool ApplyCustomNaniteShapePreservationToAsset(UObject* Asset) const;`
- L482 _protected prototype_ `bool FillCustomNaniteShapePreservationFromAsset(UObject* Asset);`
- L483 _protected prototype_ `bool ApplyCustomNanitePositionPrecisionToAsset(UObject* Asset) const;`
- L484 _protected prototype_ `bool FillCustomNanitePositionPrecisionFromAsset(UObject* Asset);`
- L485 _protected prototype_ `bool ApplyCustomNaniteNormalPrecisionToAsset(UObject* Asset) const;`
- L486 _protected prototype_ `bool FillCustomNaniteNormalPrecisionFromAsset(UObject* Asset);`
- L487 _protected prototype_ `bool ApplyCustomNaniteTangentPrecisionToAsset(UObject* Asset) const;`
- L488 _protected prototype_ `bool FillCustomNaniteTangentPrecisionFromAsset(UObject* Asset);`
- L489 _protected prototype_ `bool ApplyCustomNaniteBoneWeightPrecisionToAsset(UObject* Asset) const;`
- L490 _protected prototype_ `bool FillCustomNaniteBoneWeightPrecisionFromAsset(UObject* Asset);`
- L491 _protected prototype_ `bool ApplyCustomNaniteTargetMinimumResidencyInKBToAsset(UObject* Asset) const;`
- L492 _protected prototype_ `bool FillCustomNaniteTargetMinimumResidencyInKBFromAsset(UObject* Asset);`
- L493 _protected prototype_ `bool ApplyCustomNaniteKeepPercentTrianglesToAsset(UObject* Asset) const;`
- L494 _protected prototype_ `bool FillCustomNaniteKeepPercentTrianglesFromAsset(UObject* Asset);`
- L495 _protected prototype_ `bool ApplyCustomNaniteTrimRelativeErrorToAsset(UObject* Asset) const;`
- L496 _protected prototype_ `bool FillCustomNaniteTrimRelativeErrorFromAsset(UObject* Asset);`
- L497 _protected prototype_ `bool ApplyCustomNaniteGenerateFallbackToAsset(UObject* Asset) const;`
- L498 _protected prototype_ `bool FillCustomNaniteGenerateFallbackFromAsset(UObject* Asset);`
- L499 _protected prototype_ `bool ApplyCustomNaniteFallbackTargetToAsset(UObject* Asset) const;`
- L500 _protected prototype_ `bool FillCustomNaniteFallbackTargetFromAsset(UObject* Asset);`
- L501 _protected prototype_ `bool ApplyCustomNaniteFallbackPercentTrianglesToAsset(UObject* Asset) const;`
- L502 _protected prototype_ `bool FillCustomNaniteFallbackPercentTrianglesFromAsset(UObject* Asset);`
- L503 _protected prototype_ `bool ApplyCustomNaniteFallbackRelativeErrorToAsset(UObject* Asset) const;`
- L504 _protected prototype_ `bool FillCustomNaniteFallbackRelativeErrorFromAsset(UObject* Asset);`
- L505 _protected prototype_ `bool ApplyCustomNaniteMaxEdgeLengthFactorToAsset(UObject* Asset) const;`
- L506 _protected prototype_ `bool FillCustomNaniteMaxEdgeLengthFactorFromAsset(UObject* Asset);`
- L507 _protected prototype_ `bool ApplyCustomNaniteNumRaysToAsset(UObject* Asset) const;`
- L508 _protected prototype_ `bool FillCustomNaniteNumRaysFromAsset(UObject* Asset);`
- L509 _protected prototype_ `bool ApplyCustomNaniteVoxelLevelToAsset(UObject* Asset) const;`
- L510 _protected prototype_ `bool FillCustomNaniteVoxelLevelFromAsset(UObject* Asset);`
- L511 _protected prototype_ `bool ApplyCustomNaniteRayBackUpToAsset(UObject* Asset) const;`
- L512 _protected prototype_ `bool FillCustomNaniteRayBackUpFromAsset(UObject* Asset);`
- L513 _protected prototype_ `bool ApplyCustomNaniteDisplacementUVChannelToAsset(UObject* Asset) const;`
- L514 _protected prototype_ `bool FillCustomNaniteDisplacementUVChannelFromAsset(UObject* Asset);`
- L517 _protected member_ `TSubclassOf<UStaticMesh> AssetClass;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API INTERCHANGEFACTORYNODES_API`
- L43 _namespace_ `namespace UE`
- L45 _namespace_ `namespace Interchange` (scope `UE`)

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeStaticMeshLodDataNode.h` (Public)


#### struct `UE::Interchange::FStaticMeshNodeLodDataStaticData`  
`struct FStaticMeshNodeLodDataStaticData : public FBaseNodeStaticData`  
_L20-42_
- inherits: `FBaseNodeStaticData`
- L22 _public prototype_ `static const FAttributeKey& GetLODMeshDataArrayBaseKey();`
- L23 _public prototype_ `static const FAttributeKey& GetBoxCollisionMeshDataArrayBaseKey();`
- L24 _public prototype_ `static const FAttributeKey& GetCapsuleCollisionMeshDataArrayBaseKey();`
- L25 _public prototype_ `static const FAttributeKey& GetSphereCollisionMeshDataArrayBaseKey();`
- L26 _public prototype_ `static const FAttributeKey& GetConvexCollisionMeshDataArrayBaseKey();`
- L29 _public prototype_ `static const FAttributeKey& GetMeshUidsBaseKey();` — `UE_DEPRECATED(5.8, "Use GetLODMeshDataArrayBaseKey instead")`
- L32 _public prototype_ `static const FAttributeKey& GetBoxCollisionMeshUidsBaseKey();` — `UE_DEPRECATED(5.8, "Use GetBoxCollisionMeshDataArrayBaseKey instead")`
- L35 _public prototype_ `static const FAttributeKey& GetCapsuleCollisionMeshUidsBaseKey();` — `UE_DEPRECATED(5.8, "Use GetCapsuleCollisionMeshDataArrayBaseKey instead")`
- L38 _public prototype_ `static const FAttributeKey& GetSphereCollisionMeshUidsBaseKey();` — `UE_DEPRECATED(5.8, "Use GetSphereCollisionMeshDataArrayBaseKey instead")`
- L41 _public prototype_ `static const FAttributeKey& GetConvexCollisionMeshUidsBaseKey();` — `UE_DEPRECATED(5.8, "Use GetConvexCollisionMeshDataArrayBaseKey instead")`

#### class `UInterchangeStaticMeshLodDataNode`  
`class UInterchangeStaticMeshLodDataNode : public UInterchangeFactoryBaseNode`  
_L48-353_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeFactoryBaseNode`
- L53 _public prototype_ `UInterchangeStaticMeshLodDataNode();`
- L58 _public prototype_ `virtual FString GetTypeName() const override;` — Return the node type name of the class. This is used when reporting errors.
- L61 _public prototype_ `virtual FString GetKeyDisplayName(const UE::Interchange::FAttributeKey& NodeAttributeKey) const override;`
- L62 _public prototype_ `virtual FString GetAttributeCategory(const UE::Interchange::FAttributeKey& NodeAttributeKey) const override;`
- L68 _public prototype_ `int32 GetLODMeshDataArrayCount() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L71 _public prototype_ `void GetLODMeshDataArray(TArray<FInterchangeLODMeshData>& OutLODMeshDataArray) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L74 _public prototype_ `bool AddLODMeshData(const FInterchangeLODMeshData& LODMeshData);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L80 _public prototype_ `void RemoveMeshUid(const FString& MeshUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")` — Removes all entries where FInterchangeLODMeshData.MeshUid == MeshUid
- L83 _public prototype_ `bool RemoveAllLODMeshData();` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L89 _public prototype_ `bool AddBoxCollisionMeshData(const FInterchangeLODMeshData& MeshData);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")` — New collision-handling functions
- L92 _public prototype_ `bool AddSphereCollisionMeshData(const FInterchangeLODMeshData& MeshData);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L95 _public prototype_ `bool AddCapsuleCollisionMeshData(const FInterchangeLODMeshData& MeshData);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L98 _public prototype_ `bool AddConvexCollisionMeshData(const FInterchangeLODMeshData& MeshData);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L102 _public prototype_ `void GetBoxCollisionsMeshDataArray(TArray<FInterchangeLODMeshData>& OutMeshDataArray) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L105 _public prototype_ `void GetSphereCollisionsMeshDataArray(TArray<FInterchangeLODMeshData>& OutMeshDataArray) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L108 _public prototype_ `void GetCapsuleCollisionsMeshDataArray(TArray<FInterchangeLODMeshData>& OutMeshDataArray) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L111 _public prototype_ `void GetConvexCollisionsMeshDataArray(TArray<FInterchangeLODMeshData>& OutMeshDataArray) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L115 _public prototype_ `bool RemoveBoxCollisionMeshData(const FString& MeshUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L118 _public prototype_ `bool RemoveSphereCollisionMeshData(const FString& MeshUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L121 _public prototype_ `bool RemoveCapsuleCollisionMeshData(const FString& MeshUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L124 _public prototype_ `bool RemoveConvexCollisionMeshData(const FString& MeshUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L128 _public prototype_ `bool RemoveAllBoxCollisionMeshData();` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L131 _public prototype_ `bool RemoveAllSphereCollisionMeshData();` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L134 _public prototype_ `bool RemoveAllCapsuleCollisionMeshData();` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L137 _public prototype_ `bool RemoveAllConvexCollisionMeshData();` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L144 _public prototype_ `bool GetOneConvexHullPerUCX(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L147 _public prototype_ `bool SetOneConvexHullPerUCX(bool AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L150 _public prototype_ `bool GetImportCollisionType(EInterchangeMeshCollision& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L153 _public prototype_ `bool SetImportCollisionType(EInterchangeMeshCollision AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L160 _public prototype_ `bool GetForceCollisionPrimitiveGeneration(bool& bGenerate) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")` — Gets whether we're generating collision primitive shapes even if the mesh data doesn't match the desired shape very well
- L167 _public prototype_ `bool SetForceCollisionPrimitiveGeneration(bool bGenerate);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")` — Sets whether we're generating collision primitive shapes even if the mesh data doesn't match the desired shape very well
- L170 _public prototype_ `bool GetImportCollision(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L173 _public prototype_ `bool SetImportCollision(bool AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L181 _public prototype_ `int32 GetMeshUidsCount() const;` — `UE_DEPRECATED(5.8, "Use GetLODMeshDataArrayCount instead")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")` — Deprecated functions from here:
- L185 _public prototype_ `void GetMeshUids(TArray<FString>& OutMeshNames) const;` — `UE_DEPRECATED(5.8, "Use GetLODMeshDataArray instead")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L189 _public prototype_ `bool AddMeshUid(const FString& MeshName);` — `UE_DEPRECATED(5.8, "Use AddLODMeshData instead")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L193 _public prototype_ `bool RemoveAllMeshes();` — `UE_DEPRECATED(5.8, "Use RemoveAllLODMeshData instead")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L198 _public prototype_ `int32 GetBoxCollisionMeshUidsCount() const;` — `UE_DEPRECATED(5.8, "Use GetBoxCollisionsMeshDataArray instead")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L202 _public prototype_ `TMap<FString, FString> GetBoxCollisionMeshMap() const;` — `UE_DEPRECATED(5.8, "Use GetBoxCollisionsMeshDataArray instead")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L206 _public prototype_ `void GetBoxCollisionMeshUids(TArray<FString>& OutMeshNames) const;` — `UE_DEPRECATED(5.8, "No longer used: Collect the keys from GetBoxCollisionsMeshDataArray() instead.")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L210 _public prototype_ `void GetBoxColliderRenderMeshUid(const FString& InColliderMeshUid, FString& OutRenderMeshUid) const;` — `UE_DEPRECATED(5.8, "Deprecated. No longer used.")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L214 _public prototype_ `bool AddBoxCollisionMeshUid(const FString& ColliderMeshUid);` — `UE_DEPRECATED(5.8, "Use AddBoxCollisionMeshData instead.")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L218 _public prototype_ `bool AddBoxCollisionMeshUids(const FString& ColliderMeshUid, const FString& RenderMeshUid);` — `UE_DEPRECATED(5.8, "Use AddBoxCollisionMeshData instead.")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L222 _public prototype_ `bool RemoveBoxCollisionMeshUid(const FString& ColliderMeshUid);` — `UE_DEPRECATED(5.8, "Use RemoveBoxCollisionMeshData instead.")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L226 _public prototype_ `bool RemoveAllBoxCollisionMeshes();` — `UE_DEPRECATED(5.8, "Use RemoveAllBoxCollisionMeshData instead.")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L231 _public prototype_ `int32 GetCapsuleCollisionMeshUidsCount() const;` — `UE_DEPRECATED(5.8, "Use GetCapsuleCollisionsMeshDataArray instead.")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L235 _public prototype_ `TMap<FString, FString> GetCapsuleCollisionMeshMap() const;` — `UE_DEPRECATED(5.8, "Use GetCapsuleCollisionsMeshDataArray instead.")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L239 _public prototype_ `void GetCapsuleCollisionMeshUids(TArray<FString>& OutMeshNames) const;` — `UE_DEPRECATED(5.8, "No longer used: Collect the keys from GetCapsuleCollisionsMeshDataArray() instead.")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L243 _public prototype_ `void GetCapsuleColliderRenderMeshUid(const FString& InColliderMeshUid, FString& OutRenderMeshUid) const;` — `UE_DEPRECATED(5.8, "Deprecated. No longer used.")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L247 _public prototype_ `bool AddCapsuleCollisionMeshUid(const FString& ColliderMeshUid);` — `UE_DEPRECATED(5.8, "Use AddCapsuleCollisionMeshData instead.")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L251 _public prototype_ `bool AddCapsuleCollisionMeshUids(const FString& ColliderMeshUid, const FString& RenderMeshUid);` — `UE_DEPRECATED(5.8, "Use AddCapsuleCollisionMeshData instead.")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L255 _public prototype_ `bool RemoveCapsuleCollisionMeshUid(const FString& ColliderMeshUid);` — `UE_DEPRECATED(5.8, "Use RemoveCapsuleCollisionMeshData instead.")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L259 _public prototype_ `bool RemoveAllCapsuleCollisionMeshes();` — `UE_DEPRECATED(5.8, "Use RemoveAllCapsuleCollisionMeshData instead.")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L264 _public prototype_ `int32 GetSphereCollisionMeshUidsCount() const;` — `UE_DEPRECATED(5.8, "Use GetSphereCollisionsMeshDataArray instead.")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L268 _public prototype_ `TMap<FString, FString> GetSphereCollisionMeshMap() const;` — `UE_DEPRECATED(5.8, "Use GetSphereCollisionsMeshDataArray instead.")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L272 _public prototype_ `void GetSphereCollisionMeshUids(TArray<FString>& OutMeshNames) const;` — `UE_DEPRECATED(5.8, "No longer used: Collect the keys from GetSphereCollisionsMeshDataArray() instead.")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L276 _public prototype_ `void GetSphereColliderRenderMeshUid(const FString& InColliderMeshUid, FString& OutRenderMeshUid) const;` — `UE_DEPRECATED(5.8, "Deprecated. No longer used.")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L280 _public prototype_ `bool AddSphereCollisionMeshUid(const FString& ColliderMeshUid);` — `UE_DEPRECATED(5.8, "Use AddSphereCollisionMeshData instead.")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L284 _public prototype_ `bool AddSphereCollisionMeshUids(const FString& ColliderMeshUid, const FString& RenderMeshUid);` — `UE_DEPRECATED(5.8, "Use AddSphereCollisionMeshData instead.")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L288 _public prototype_ `bool RemoveSphereCollisionMeshUid(const FString& ColliderMeshUid);` — `UE_DEPRECATED(5.8, "Use RemoveSphereCollisionMeshData instead.")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L292 _public prototype_ `bool RemoveAllSphereCollisionMeshes();` — `UE_DEPRECATED(5.8, "Use RemoveAllSphereCollisionMeshData instead.")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L297 _public prototype_ `int32 GetConvexCollisionMeshUidsCount() const;` — `UE_DEPRECATED(5.8, "Use GetConvexCollisionsMeshDataArray instead.")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L301 _public prototype_ `TMap<FString, FString> GetConvexCollisionMeshMap() const;` — `UE_DEPRECATED(5.8, "Use GetConvexCollisionsMeshDataArray instead.")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L305 _public prototype_ `void GetConvexCollisionMeshUids(TArray<FString>& OutMeshNames) const;` — `UE_DEPRECATED(5.8, "Use GetConvexCollisionsMeshDataArray instead.")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L309 _public prototype_ `void GetConvexColliderRenderMeshUid(const FString& InColliderMeshUid, FString& OutRenderMeshUid) const;` — `UE_DEPRECATED(5.8, "Deprecated. No longer used.")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L313 _public prototype_ `bool AddConvexCollisionMeshUid(const FString& ColliderMeshUid);` — `UE_DEPRECATED(5.8, "Use AddConvexCollisionMeshData instead.")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L317 _public prototype_ `bool AddConvexCollisionMeshUids(const FString& ColliderMeshUid, const FString& RenderMeshUid);` — `UE_DEPRECATED(5.8, "Use AddConvexCollisionMeshData instead.")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L321 _public prototype_ `bool RemoveConvexCollisionMeshUid(const FString& MeshName);` — `UE_DEPRECATED(5.8, "Use RemoveConvexCollisionMeshData instead.")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L325 _public prototype_ `bool RemoveAllConvexCollisionMeshes();` — `UE_DEPRECATED(5.8, "Use RemoveConvexCollisionMeshData instead.")` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | StaticMeshLodData")`
- L333 _private prototype_ `bool IsEditorOnlyDataDefined();`
- L335 _private member_ `UE::Interchange::TArrayAttributeHelper<FInterchangeLODMeshData> LODMeshDataArray;`
- L336 _private member_ `UE::Interchange::TArrayAttributeHelper<FInterchangeLODMeshData> BoxCollisionMeshDataArray;`
- L337 _private member_ `UE::Interchange::TArrayAttributeHelper<FInterchangeLODMeshData> CapsuleCollisionMeshDataArray;`
- L338 _private member_ `UE::Interchange::TArrayAttributeHelper<FInterchangeLODMeshData> SphereCollisionMeshDataArray;`
- L339 _private member_ `UE::Interchange::TArrayAttributeHelper<FInterchangeLODMeshData> ConvexCollisionMeshDataArray;`
- L342 _private member_ `UE::Interchange::TArrayAttributeHelper<FString> MeshUids;` — Deprecated:
- L343 _private member_ `UE::Interchange::TMapAttributeHelper<FString, FString> BoxCollisionMeshUids;`
- L344 _private member_ `UE::Interchange::TMapAttributeHelper<FString, FString> CapsuleCollisionMeshUids;`
- L345 _private member_ `UE::Interchange::TMapAttributeHelper<FString, FString> SphereCollisionMeshUids;`
- L346 _private member_ `UE::Interchange::TMapAttributeHelper<FString, FString> ConvexCollisionMeshUids;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API INTERCHANGEFACTORYNODES_API`
- L16 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Interchange` (scope `UE`)

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeTexture2DArrayFactoryNode.h` (Public)


#### class `UInterchangeTexture2DArrayFactoryNode`  
`class UInterchangeTexture2DArrayFactoryNode : public UInterchangeTextureFactoryNode`  
_L18-94_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeTextureFactoryNode`
- L25 _public function_ `bool GetCustomAddressX(uint8& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L30 _public function_ `bool SetCustomAddressX(const uint8 AttributeValue, bool bAddApplyDelegate = true)`
- L40 _public function_ `bool GetCustomAddressY(uint8& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L45 _public function_ `bool SetCustomAddressY(const uint8 AttributeValue, bool bAddApplyDelegate = true)`
- L55 _public function_ `bool GetCustomAddressZ(uint8& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L61 _public function_ `bool SetCustomAddressZ(const uint8 AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L70 _public function_ `virtual void CopyWithObject(const UInterchangeFactoryBaseNode* SourceNode, UObject* Object) override`
- L85 _private function_ `virtual UClass* GetObjectClass() const override`
- L91 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(AddressX);` — Addressing
- L92 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(AddressY);`
- L93 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(AddressZ);`

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeTexture2DFactoryNode.h` (Public)


#### struct `UE::Interchange::FTexture2DFactoryNodeStaticData`  
`struct FTexture2DFactoryNodeStaticData : public FBaseNodeStaticData`  
_L15-22_
- inherits: `FBaseNodeStaticData`
- L17 _public function_ `static const FAttributeKey& GetBaseSourceBlocksKey()`

#### class `UInterchangeTexture2DFactoryNode`  
`class UInterchangeTexture2DFactoryNode : public UInterchangeTextureFactoryNode`  
_L26-202_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UInterchangeTextureFactoryNode`
- L35 _public function_ `bool GetCustomAddressX(TEnumAsByte<TextureAddress>& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L41 _public function_ `bool SetCustomAddressX(const TEnumAsByte<TextureAddress> AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L48 _public function_ `bool GetCustomAddressY(TEnumAsByte<TextureAddress>& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L54 _public function_ `bool SetCustomAddressY(const TEnumAsByte<TextureAddress> AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L62 _public function_ `virtual void Serialize(FArchive& Ar) override` — Override serialize to restore SourceBlocks on load.
- L81 _public function_ `TMap<int32, FString> GetSourceBlocks() const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture | UDIMs")` — Get the source blocks for the texture. If the map is empty, the texture is imported as a normal texture using the payload key.
- L94 _public function_ `void SetSourceBlocks(const TMap<int32, FString>& InSourceBlocks)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture | UDIMs")` — Set the source blocks for the texture. Using this suggests to the pipeline to consider this texture as a UDIM. The pipeline can choose whether to pass these blocks to the texture factory node. @param InSourceBlocks The blocks and their source image that compose the whole texture. The textures must be of the same format and use the same pixel format. The first block in the map is used to determine the accepted texture format and pixel format.
- L107 _public function_ `void SetSourceBlocks(TMap<int32, FString>&& InSourceBlocks)` — Set the source blocks for the texture. Using this suggests to the pipeline to consider this texture as a UDIM. The pipeline can choose whether to pass these blocks to the texture factory node. @param InSourceBlocks The blocks and their source image that compose the whole texture. The textures must be of the same format and use the same pixel format. The first block in the map is used to determine the accepted texture format and pixel format.
- L122 _public function_ `bool GetSourceBlockByCoordinates(int32 X, int32 Y, FString& OutSourceFile) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture | UDIMs")` — Get a source block from the texture. @param X The X coordinate of the block. @param Y The Y coordinate of the block. @param OutSourceFile The source file for that block if found. @return True if the source file for the block was found.
- L135 _public function_ `bool GetSourceBlock(int32 BlockIndex, FString& OutSourceFile) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture | UDIMs")` — Get a source block from the texture. @param BlockIndex The UDIM Index of the block. @param OutSourceFile The source file for that block if found. @return True if the source file for the block was found.
- L152 _public function_ `void SetSourceBlockByCoordinates(int32 X, int32 Y, const FString& InSourceFile)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture | UDIMs")` — Set a source block for the texture. @param X The X coordinate of the block. @param Y The Y coordinate of the block. @param InSourceFile The source file for that block. The textures must be of the same format and use the same pixel format. The first block in the map is used to determine the accepted texture format and pixel format.
- L167 _public function_ `void SetSourceBlock(int32 BlockIndex, const FString& InSourceFile)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture | UDIMs")` — Set a source block for the texture. @param BlockIndex The UDIM index of the block. @param InSourceFile The source file for that block. The textures must be of the same format and use the same pixel format. The first block in the map is used to determine the accepted texture format and pixel format.
- L175 _public function_ `virtual UClass* GetObjectClass() const override`
- L180 _public function_ `virtual void PostInitProperties()`
- L186 _public function_ `virtual void CopyWithObject(const UInterchangeFactoryBaseNode* SourceNode, UObject* Object) override`
- L198 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(AddressX);`
- L199 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(AddressY);`
- L201 _private member_ `UE::Interchange::TMapAttributeHelper<int32, FString> SourceBlocks;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Interchange` (scope `UE`)

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeTextureCubeArrayFactoryNode.h` (Public)


#### class `UInterchangeTextureCubeArrayFactoryNode`  
`class UInterchangeTextureCubeArrayFactoryNode : public UInterchangeTextureFactoryNode`  
_L16-25_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeTextureFactoryNode`
- L21 _private function_ `virtual UClass* GetObjectClass() const override`

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeTextureCubeFactoryNode.h` (Public)


#### class `UInterchangeTextureCubeFactoryNode`  
`class UInterchangeTextureCubeFactoryNode : public UInterchangeTextureFactoryNode`  
_L16-25_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeTextureFactoryNode`
- L21 _private function_ `virtual UClass* GetObjectClass() const override`

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeTextureFactoryNode.h` (Public)


#### class `UInterchangeTextureFactoryNode`  
`class UInterchangeTextureFactoryNode : public UInterchangeFactoryBaseNode`  
_L15-859_
- reflection: `UCLASS(BlueprintType, Abstract, MinimalAPI)`
- inherits: `UInterchangeFactoryBaseNode`
- L27 _public function_ `void InitializeTextureNode(const FString& UniqueID, const FString& DisplayLabel, const FString& InAssetName, UInterchangeBaseNodeContainer* NodeContainer)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Initialize node data. @param: UniqueID - The unique ID for this node. @param DisplayLabel - The name of the node. @param InAssetClass - The class the texture factory will create for this node.
- L40 _public function_ `virtual FString GetTypeName() const override` — Return the node type name of the class. This is used when reporting errors.
- L47 _public function_ `virtual UClass* GetObjectClass() const override` — Get the class this node creates.
- L54 _public function_ `virtual FGuid GetHash() const override`
- L59 _public function_ `static FString GetTextureFactoryNodeUidFromTextureNodeUid(const FString& TranslatedNodeUid)`
- L69 _public function_ `bool GetCustomTranslatedTextureNodeUid(FString& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Get the unique ID of the translated texture node.
- L78 _public function_ `bool SetCustomTranslatedTextureNodeUid(const FString& AttributeValue)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Set the unique ID of the translated texture node. This is a reference to the node that was created by the translator. It is needed to get the texture payload.
- L86 _public function_ `bool GetCustomAdjustBrightness(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L92 _public function_ `bool SetCustomAdjustBrightness(const float& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L103 _public function_ `bool GetCustomAdjustBrightnessCurve(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L109 _public function_ `bool SetCustomAdjustBrightnessCurve(const float& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L120 _public function_ `bool GetCustomAdjustVibrance(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L126 _public function_ `bool SetCustomAdjustVibrance(const float& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L137 _public function_ `bool GetCustomAdjustSaturation(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L143 _public function_ `bool SetCustomAdjustSaturation(const float& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L154 _public function_ `bool GetCustomAdjustRGBCurve(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L160 _public function_ `bool SetCustomAdjustRGBCurve(const float& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L171 _public function_ `bool GetCustomAdjustHue(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L177 _public function_ `bool SetCustomAdjustHue(const float& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L188 _public function_ `bool GetCustomAdjustMinAlpha(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L194 _public function_ `bool SetCustomAdjustMinAlpha(const float& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L205 _public function_ `bool GetCustomAdjustMaxAlpha(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L211 _public function_ `bool SetCustomAdjustMaxAlpha(const float& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L222 _public function_ `bool GetCustombChromaKeyTexture(bool& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L228 _public function_ `bool SetCustombChromaKeyTexture(const bool& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L239 _public function_ `bool GetCustomChromaKeyThreshold(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L245 _public function_ `bool SetCustomChromaKeyThreshold(const float& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L256 _public function_ `bool GetCustomChromaKeyColor(FColor& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L262 _public function_ `bool SetCustomChromaKeyColor(const FColor& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L276 _public function_ `bool GetCustomCompressionNoAlpha(bool& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L282 _public function_ `bool SetCustomCompressionNoAlpha(const bool& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L293 _public function_ `bool GetCustomDeferCompression(bool& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L299 _public function_ `bool SetCustomDeferCompression(const bool& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L310 _public function_ `bool GetCustomLossyCompressionAmount(uint8& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L316 _public function_ `bool SetCustomLossyCompressionAmount(const uint8& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L327 _public function_ `bool GetCustomMaxTextureSize(int32& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L333 _public function_ `bool SetCustomMaxTextureSize(const int32& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L344 _public function_ `bool GetCustomCompressionQuality(uint8& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L350 _public function_ `bool SetCustomCompressionQuality(const uint8& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L361 _public function_ `bool GetCustomCompressionSettings(uint8& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L367 _public function_ `bool SetCustomCompressionSettings(const uint8& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L377 _public function_ `bool GetCustomAlphaCoverageThresholds(FVector4& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L383 _public function_ `bool SetCustomAlphaCoverageThresholds(const FVector4& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L395 _public function_ `bool GetCustombDoScaleMipsForAlphaCoverage(bool& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L401 _public function_ `bool SetCustombDoScaleMipsForAlphaCoverage(const bool& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L413 _public function_ `bool GetCustombFlipGreenChannel(bool& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L419 _public function_ `bool SetCustombFlipGreenChannel(const bool& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L430 _public function_ `bool GetCustomPowerOfTwoMode(uint8& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L436 _public function_ `bool SetCustomPowerOfTwoMode(const uint8& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L447 _public function_ `bool GetCustomPaddingColor(FColor& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L453 _public function_ `bool SetCustomPaddingColor(const FColor& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L464 _public function_ `bool GetCustomFilter(uint8& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L470 _public function_ `bool SetCustomFilter(const uint8& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L477 _public function_ `bool GetCustomMipLoadOptions(uint8& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L483 _public function_ `bool SetCustomMipLoadOptions(const uint8& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L490 _public function_ `bool GetCustomSRGB(bool& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L496 _public function_ `bool SetCustomSRGB(const bool& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L503 _public function_ `bool GetCustombUseLegacyGamma(bool& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L509 _public function_ `bool SetCustombUseLegacyGamma(const bool& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L520 _public function_ `bool GetCustomVirtualTextureStreaming(bool& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L526 _public function_ `bool SetCustomVirtualTextureStreaming(const bool& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L533 _public prototype_ `bool GetCustomColorSpace(ETextureColorSpace& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L536 _public prototype_ `bool SetCustomColorSpace(ETextureColorSpace AttributeValue, bool bAddApplyDelegate = true);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L543 _public function_ `bool GetCustombPreserveBorder(bool& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L549 _public function_ `bool SetCustombPreserveBorder(const bool& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L560 _public function_ `bool GetCustomMipGenSettings(uint8& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L566 _public function_ `bool SetCustomMipGenSettings(const uint8& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L577 _public function_ `bool GetCustomLODBias(int32& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L583 _public function_ `bool SetCustomLODBias(const int32& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L590 _public function_ `bool GetCustomLODGroup(uint8& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L596 _public function_ `bool SetCustomLODGroup(const uint8& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L604 _public function_ `bool GetCustomDownscale(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L610 _public function_ `bool SetCustomDownscale(const float& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L617 _public function_ `bool GetCustomDownscaleOptions(uint8& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L623 _public function_ `bool SetCustomDownscaleOptions(const uint8& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L633 _public function_ `bool GetCustomCompositeTextureMode(uint8& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L639 _public function_ `bool SetCustomCompositeTextureMode(const uint8& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L650 _public function_ `bool GetCustomCompositePower(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")` — Return false if the Attribute was not set previously.
- L656 _public function_ `bool SetCustomCompositePower(const float& AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L670 _public function_ `bool GetCustomAllowNonPowerOfTwo(bool& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture | Import Settings")` — Return false if the Attribute was not set previously.
- L680 _public function_ `bool SetCustomAllowNonPowerOfTwo(const bool& AttributeValue)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture | Import Settings")` — Should the factory allow the import of texture that would have a resolution that is not a power of two By default this is not allowed
- L687 _public function_ `bool GetCustomPreferCompressedSourceData(bool& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture | Import Settings")` — Return false if the Attribute was not set previously.
- L697 _public function_ `bool SetCustomPreferCompressedSourceData(const bool& AttributeValue)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture | Import Settings")` — Determines whether the factory should tell the translator to provide a compressed source data payload when available. This will generally result in smaller assets. However, some operations like the texture build might be slower, because the source data first needs to be decompressed.
- L702 _public function_ `virtual void CopyWithObject(const UInterchangeFactoryBaseNode* SourceNode, UObject* Object) override`
- L751 _private member_ `const UE::Interchange::FAttributeKey ClassNameAttributeKey = UE::Interchange::FBaseNodeStaticData::ClassTypeAttributeKey();`
- L752 _private member_ `const UE::Interchange::FAttributeKey AssetNameKey = UE::Interchange::FBaseNodeStaticData::AssetNameKey();`
- L758 _private function_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(AdjustBrightness) IMPLEMENT_NODE_ATTRIBUTE_KEY(AdjustBrightnessCurve) IMPLEMENT_NODE_ATTRIBUTE_KEY(AdjustVibrance) IMPLEMENT_NODE_ATTRIBUTE_KEY(AdjustSaturation) IMPLEMENT_NODE_ATTRIBUTE_KEY(AdjustRGBCurve) IMPLEMENT_NODE_ATTRIBUTE_KEY(AdjustHue) IMPLEMENT_NODE_ATTRIBUTE_KEY(AdjustMinAlpha) IMPLEMENT_NODE_ATTRIBUTE_KEY(AdjustMaxAlpha) IMPLEMENT_NODE_ATTRIBUTE_KEY(bChromaKeyTexture) IMPLEMENT_NODE_ATTRIBUTE_KEY(ChromaKeyThreshold) IMPLEMENT_NODE_ATTRIBUTE_KEY(ChromaKeyColor)` — Texture Adjustments
- L836 _private function_ `bool FillCustomDownscaleFromAsset(UObject* Asset)`
- L855 _private prototype_ `bool ApplyCustomColorSpaceToAsset(UObject* Asset) const;`
- L857 _private prototype_ `bool FillCustomColorSpaceFromAsset(UObject* Asset);`

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeTextureLightProfileFactoryNode.h` (Public)


#### class `UInterchangeTextureLightProfileFactoryNode`  
`class UInterchangeTextureLightProfileFactoryNode : public UInterchangeTexture2DFactoryNode`  
_L19-133_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UInterchangeTexture2DFactoryNode`
- L24 _public function_ `UInterchangeTextureLightProfileFactoryNode()`
- L30 _public function_ `bool GetCustomBrightness(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L36 _public function_ `bool SetCustomBrightness(const float AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L47 _public function_ `bool GetCustomTextureMultiplier(float& AttributeValue) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L53 _public function_ `bool SetCustomTextureMultiplier(const float AttributeValue, bool bAddApplyDelegate = true)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Texture")`
- L62 _public function_ `void StoreIESSourceFileContents(const TArray64<uint8>& IESSourceFileContents)`
- L81 _public function_ `void GetIESSourceFileContents(TArray64<uint8>& IESSourceFileContent) const`
- L106 _public function_ `virtual void CopyWithObject(const UInterchangeFactoryBaseNode* SourceNode, UObject* Object) override`
- L122 _private function_ `virtual UClass* GetObjectClass() const override`
- L128 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(Brightness);` — Addressing
- L129 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(TextureMultiplier);`
- L132 _private member_ `UE::Interchange::TArrayAttributeHelper<FString> AttributeHelperIESSourceFileContentChunks;` — Note: Base64 encoded chunks of 2^16 sized strings.

### `Plugins/Interchange/Runtime/Source/FactoryNodes/Public/InterchangeVolumeTextureFactoryNode.h` (Public)


#### class `UInterchangeVolumeTextureFactoryNode`  
`class UInterchangeVolumeTextureFactoryNode : public UInterchangeTextureFactoryNode`  
_L16-25_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangeTextureFactoryNode`
- L21 _private function_ `virtual UClass* GetObjectClass() const override`
