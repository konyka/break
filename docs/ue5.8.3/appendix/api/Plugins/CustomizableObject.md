# Plugins / CustomizableObject

- module root: `Plugins/Mutable/Source/CustomizableObject`
- headers: 44; symbols: 2322
- symbol kinds: class=44, delegate=20, enum=21, enumerator=400, externvar=23, function=76, macro=45, member=797, namespace=54, prototype=729, struct=102, typedef=7, variable=4
- PrivateDependencyModuleNames: MutableTools
- PublicDependencyModuleNames: DerivedDataCache, EditorStyle, MessageLog, UnrealEd

### `Plugins/Mutable/Source/CustomizableObject/Internal/MuCO/CustomizableObjectCompilerTypes.h` (Internal)


#### struct `FCompilationOptions`  
`struct FCompilationOptions`  
_L19-93_
- L23 _public member_ `ECustomizableObjectTextureCompression TextureCompression = ECustomizableObjectTextureCompression::Fast;` — Enum to know what texture compression should be used. This compression is used only in manual compiles in editor. When packaging, ECustomizableObjectTextureCompression::HighQuality is always used.
- L26 _public member_ `int32 OptimizationLevel = UE_MUTABLE_MAX_OPTIMIZATION;` — From 0 to UE_MUTABLE_MAX_OPTIMIZATION
- L32 _public member_ `uint64 EmbeddedDataBytesLimit = 1024;` — High (inclusive) limit of the size in bytes of a data block to be included into the compiled object directly instead of stored in a streamable file. This option does not modify the DDC Key.
- L35 _public member_ `int32 MinDiskMips = 7;` — Number of minimum mipmaps that we want to always be available in disk regardless of NumHighResImageLODs.
- L40 _public member_ `int32 NumHighResImageMips = 2;` — Number of image mipmaps that will be flagged as high-res data (possibly to store separately). This is only used if the total mips in the source image is above the MinDiskMips.
- L43 _public member_ `ECustomizableObjectNumBoneInfluences CustomizableObjectNumBoneInfluences = ECustomizableObjectNumBoneInfluences::Four;` — Did we have the extra bones enabled when we compiled?
- L46 _public member_ `bool bIsCooking = false;` — Compiling for cook
- L49 _public member_ `const ITargetPlatform* TargetPlatform = nullptr;` — This can be set for additional settings
- L52 _public member_ `bool bRealTimeMorphTargetsEnabled = false;` — Used to enable the use of real time morph targets.
- L55 _public member_ `bool b16BitBoneWeightsEnabled = false;` — Used to enable 16 bit bone weights
- L58 _public member_ `bool bSkinWeightProfilesEnabled = false;` — Used to enable skin weight profiles.
- L61 _public member_ `bool bPhysicsAssetMergeEnabled = false;` — Used to enable physics asset merge.
- L64 _public member_ `bool bUseLegacyLayouts = false;` — Determines if the max grid size is determined solely by the Skeletal Mesh noded or if the Mesh Section and Material Modify nodes can alter it.
- L67 _public member_ `bool bAnimBpPhysicsManipulationEnabled = false;` — Used to enable AnimBp override physics mainipualtion.
- L70 _public member_ `bool bForceLargeLODBias = false;` — Force a very big number on the mips to skip during compilation. Useful to debug special cooks of the data.
- L71 _public member_ `int32 DebugBias = 0;`
- L77 _public member_ `bool bGatherReferences = false;` — If true, gather all game asset references and save them in the Customizable Object. This option does not modify the DDC Key.
- L83 _public member_ `bool bQueryCompiledDatafromDDC = false;` — Whether or not the compiler should query a request to load the compiled data from the DDC. This option does not modify the DDC Key.
- L89 _public member_ `bool bStoreCompiledDataInDDC = false;` — Whether or not the compiler should store the compiled data to the DDC. This option does not modify the DDC Key.
- L92 _public member_ `TMap<FString, FString> ParamNamesToSelectedOptions;` — Stores the only option of an Int Param that should be compiled.

#### enum `ECompilationStatePrivate`  
`enum class ECompilationStatePrivate : uint8`  
_L96-101_
- L98 _public enumerator_ `None`
- L99 _public enumerator_ `InProgress`
- L100 _public enumerator_ `Completed`

#### enum `ECompilationResultPrivate`  
`enum class ECompilationResultPrivate : uint8`  
_L104-110_
- L106 _public enumerator_ `Unknown` — Not compiled yet (compilation may be in progress).
- L107 _public enumerator_ `Success` — No errors or warnings.
- L108 _public enumerator_ `Errors` — At least have one error. Can have warnings.
- L109 _public enumerator_ `Warnings` — Only warnings.

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_MUTABLE_MAX_OPTIMIZATION 2` — Index of the maximum optimization level when compiling CustomizableObjects

### `Plugins/Mutable/Source/CustomizableObject/Internal/MuCO/CustomizableObjectCustomVersion.h` (Internal)


#### struct `FCustomizableObjectCustomVersion`  
`struct FCustomizableObjectCustomVersion`  
_L12-297_
- desc: Custom serialization version for assets/classes in the CustomizableObject and CustomizableObjectEditor modules
- L293 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L296 _private function_ `FCustomizableObjectCustomVersion()`

#### enum `FCustomizableObjectCustomVersion::Type`  
`enum Type`  
_L14-290_
- L17 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Before any version changes were made in the plugin
- L19 _public enumerator_ `FixBlueprintPinsUseRealNumbers`
- L21 _public enumerator_ `NodeExposePinOnNameChangedDelegateAdded`
- L23 _public enumerator_ `GroupProjectorPinTypeAdded`
- L25 _public enumerator_ `AutomaticNodeMaterial`
- L27 _public enumerator_ `AutomaticNodeMaterialPerformance`
- L29 _public enumerator_ `LayoutClassAdded`
- L31 _public enumerator_ `AutomaticNodeMaterialPerformanceBug`
- L33 _public enumerator_ `PinsNamesImageToTexture`
- L35 _public enumerator_ `BugPinsSwitch`
- L37 _public enumerator_ `PostLoadToCustomVersion` — Wrapped old backwards compatible code that was located at PostLoads inside this custom version.
- L39 _public enumerator_ `AutomaticNodeMaterialUXImprovements`
- L41 _public enumerator_ `ExtendMaterialOnlyMutableModeParameters`
- L43 _public enumerator_ `ExtendMaterialOnlyMutableModeParametersBug`
- L45 _public enumerator_ `ExtendMaterialRemoveImages`
- L47 _public enumerator_ `EditMaterialOnlyMutableModeParameters` — Force refresh to avoid having Images which are not in Mutable mode.
- L49 _public enumerator_ `GroupProjectorIntToScalarIndex`
- L51 _public enumerator_ `FixBlueprintPinsUseRealNumbersAgain`
- L53 _public enumerator_ `NodeMaterialAddTablePin`
- L55 _public enumerator_ `MorphMaterialAddFactorPin`
- L57 _public enumerator_ `NodeSkeletalMeshCorruptedPinRef`
- L59 _public enumerator_ `CustomizableObjectInstanceDescriptor`
- L61 _public enumerator_ `DescriptorBuildParameterDecorations`
- L63 _public enumerator_ `DescriptorMultilayerProjectors`
- L65 _public enumerator_ `DeformSkeletonOptionsAdded`
- L67 _public enumerator_ `GroupProjectorImagePin`
- L69 _public enumerator_ `GroupProjectorImagePinRemoved`
- L71 _public enumerator_ `StateTextureCompressionStrategyEnum`
- L73 _public enumerator_ `AddedTableNodesTextureMode`
- L75 _public enumerator_ `ConvertAnimationSlotToFName`
- L77 _public enumerator_ `RemovedParameterDecorations`
- L79 _public enumerator_ `AutomaticNodeSkeletalMesh`
- L81 _public enumerator_ `AutomaticNodeSkeletalMeshPinDataOuter`
- L83 _public enumerator_ `AutomaticNodeSkeletalMeshPinDataUProperty`
- L85 _public enumerator_ `EditMaterialMaskPinDesync` — MTBL-979
- L87 _public enumerator_ `IgnoreDisabledSections`
- L89 _public enumerator_ `SkeletalMeshNodeDefaultPinWithoutPinData`
- L91 _public enumerator_ `AddedTableMaterialSwitch`
- L93 _public enumerator_ `FixPinsNamesImageToTexture2`
- L95 _public enumerator_ `MeshReshapeVertexColorUsageSelection`
- L97 _public enumerator_ `DeduplicateNodeVariant`
- L99 _public enumerator_ `TextureCompressionEnum`
- L101 _public enumerator_ `NodeTextureParameterDefaultToReferenceValue`
- L103 _public enumerator_ `NodeVariationSerializationIssue` — The parent class and child classes had a member with the same name. Unreal was serialized the member from the child class but deserialized it to the parent class.
- L105 _public enumerator_ `RegenerateNodeObjectsIds`
- L107 _public enumerator_ `NodeMaterialPinDataImageDetails`
- L109 _public enumerator_ `CustomizableObjectStateHasSeparateNeverStreamFlag`
- L111 _public enumerator_ `CustomizableObjectNodeHasSeparateNeverStreamFlag`
- L113 _public enumerator_ `AddedColumnIdDataToTableNodePins`
- L115 _public enumerator_ `AddedAnyTextureTypeToPassThroughTextures`
- L117 _public enumerator_ `ProjectorNodesDefaultValueFix`
- L119 _public enumerator_ `StateUIMetadata`
- L121 _public enumerator_ `AddedRenameOptionToParameterNodes`
- L123 _public enumerator_ `CompilationOptions`
- L125 _public enumerator_ `NodeTablePinViewer`
- L127 _public enumerator_ `NewComponentOptions`
- L129 _public enumerator_ `NodeMaterialTypedImagePins`
- L131 _public enumerator_ `FixedMultilayerMaterialIds`
- L133 _public enumerator_ `UseUVRects` — Instead of pointing at layout blocks in the edited parent, define custom absolute UV layout rects.
- L135 _public enumerator_ `AddModifierPin` — Move the modifiers output pin from Material to Modifier
- L137 _public enumerator_ `CorrectlySerializeTableToParamNames`
- L139 _public enumerator_ `MovedCompatibilityFromPostBackwardsCompatibleFixup`
- L141 _public enumerator_ `FixModifierPin`
- L143 _public enumerator_ `ConvertEditAndExtendToModifiers`
- L145 _public enumerator_ `NodeComponentMesh` — Moved LOD pins from NodeObject to NodeComponentMesh.
- L147 _public enumerator_ `MergeNodeComponents`
- L149 _public enumerator_ `UnifyRequiredTags`
- L151 _public enumerator_ `MaterialPinsRename` — Moved from "Material" to "Mesh Section"
- L153 _public enumerator_ `MoveLayoutToNodeSkeletalMesh` — Move the layouts from the NodeLayout to the NodeSkeletalMesh
- L155 _public enumerator_ `RemoveNodeLayout`
- L157 _public enumerator_ `ComponentsArray`
- L159 _public enumerator_ `FixMaterialPinsRename`
- L161 _public enumerator_ `ModifierClipWithMeshCleanup`
- L163 _public enumerator_ `RealTimeMorphTargetOverrideDataStructureRework`
- L165 _public enumerator_ `FixAutomaticBlocksStrategyLegacyNodes`
- L167 _public enumerator_ `SnapToBoneComponentIndexToName`
- L169 _public enumerator_ `SetDisplayNamePropertyAsPinNameOfTableNodes`
- L171 _public enumerator_ `FixedNoPinsInRerouteNodes`
- L173 _public enumerator_ `TableNoneOptionsMovedToUnrealCode`
- L175 _public enumerator_ `UpdatedNodesPinName`
- L177 _public enumerator_ `UpdatedNodesPinName2`
- L179 _public enumerator_ `UpdatedNodesPinName3`
- L181 _public enumerator_ `TextureVariationsToVariations`
- L183 _public enumerator_ `MovedLODSettingsToMeshComponentNode`
- L185 _public enumerator_ `AddedTableNodeCompilationFilters`
- L187 _public enumerator_ `ChangedComponentsInheritance`
- L189 _public enumerator_ `ChangedSwitchNodesInputPinsFriendlyNames`
- L191 _public enumerator_ `TableNodeCompilationFilterArray`
- L193 _public enumerator_ `EnableMutableMacros`
- L195 _public enumerator_ `EnableMutableMacrosNewVersion`
- L197 _public enumerator_ `BaseObjectNodeNamePin`
- L199 _public enumerator_ `FixMaterialNodeMaterialPinIncorrectLocalization`
- L201 _public enumerator_ `FixStaticMeshNodeLODMaterialDataInvalidation`
- L203 _public enumerator_ `FixStaticMeshNodeLODMaterialDataInvalidationBackOut`
- L205 _public enumerator_ `FixStaticMeshNodeLODMaterialDataInvalidation2`
- L207 _public enumerator_ `SetDisplayNamePropertyAsPinNameOfTableNodes2` — Added in order to apply the same fix for cases where the version was skipped
- L209 _public enumerator_ `NodeTextureParameterPassthroughPin`
- L211 _public enumerator_ `PinSkeletalMesh`
- L213 _public enumerator_ `NodeStaticStringRemoveHiddenInputPin`
- L215 _public enumerator_ `PassthroughParameter`
- L217 _public enumerator_ `MeshSectionNodeInputPinsAsReferences`
- L219 _public enumerator_ `WrongVariationNodeInputOrderAfterSerializationFix`
- L221 _public enumerator_ `PassthroughSkeletalMeshComponentOverrideSubtypeFix`
- L223 _public enumerator_ `PassthroughSkeletalMeshComponentComponentMaterialOverride`
- L225 _public enumerator_ `StoreMaterialPinReferenceFromConstantMaterialNode`
- L227 _public enumerator_ `StoreOverlayMaterialPinAsReference`
- L229 _public enumerator_ `RemovedOverlayMaterialUpropertyFromSkeletalMeshComponentNode`
- L231 _public enumerator_ `NodeModifierTransformInMeshStorePinsAsReferences`
- L233 _public enumerator_ `RemovedTypedSwitches`
- L235 _public enumerator_ `SkeletalMeshMakeNodeDeprecations` — SKM Component has gotten some responsibilities stripped from it and moved to the new Skeletal Mesh Make node
- L237 _public enumerator_ `TextureFromColorPinCaching`
- L239 _public enumerator_ `TextureLayerNodePinCaching`
- L241 _public enumerator_ `TextureLayerNodeExplicitLayerTypePins`
- L243 _public enumerator_ `CopySKMComponentNameToMakeSKMNode`
- L245 _public enumerator_ `NodeComponentMeshAddToNumLODs`
- L247 _public enumerator_ `SkeletalMeshParameterMutableSkeletalMeshPin`
- L249 _public enumerator_ `SkeletalMeshParameterMutableSkeletalMeshPinBackout`
- L251 _public enumerator_ `NodeComponentMeshAddToNumLODsBackout`
- L253 _public enumerator_ `NodeComponentMeshAddToNumLODsRestore`
- L255 _public enumerator_ `SkeletalMeshParameterMutableSkeletalMeshPinRestore`
- L257 _public enumerator_ `ComponentAddSkeletalMeshChangedInputsOrder` — Make the Component Name pin be above the LOD pins of the Component Mesh Add To node.
- L259 _public enumerator_ `ComponentAddNodeModifierOutputPin` — Changed the output type of the Component Mesh Add To node from Component to Modifier.
- L261 _public enumerator_ `MorphStackCategoryName`
- L263 _public enumerator_ `MergerTextureNodes`
- L265 _public enumerator_ `AddMissingOverlayPin`
- L267 _public enumerator_ `FixOverrideAndOverlayMaterialPinNames` — Those being different for Overlay/Override was confusing the pin remapper.
- L269 _public enumerator_ `MergedSkeletalMeshComponentNodes`
- L271 _public enumerator_ `SkeletalMeshBreakMaterialPinType`
- L273 _public enumerator_ `MorphReshapeMigratedToReshapeNode`
- L275 _public enumerator_ `MorphStackDefinition_RemovedMorphAutoPopulate`
- L277 _public enumerator_ `UseLegacyLayouts`
- L279 _public enumerator_ `ModifierMorphMeshSection_CacheFactorPin`
- L281 _public enumerator_ `MorphStackDefinition_RemoveOrphanMeshPin`
- L283 _public enumerator_ `MeshReshapeBonesToDeformAsFName` — Mesh Reshape node BonesToDeform changed from TArray<FMeshReshapeBoneReference> to TArray<FName>.
- L285 _public enumerator_ `ModifierSkeletalMeshMergeUseSkeletalMeshPin`
- L288 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L289 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CUSTOMIZABLEOBJECT_API`

### `Plugins/Mutable/Source/CustomizableObject/Internal/MuCO/CustomizableObjectIdentifier.h` (Internal)


#### struct `FCustomizableObjectIdPair`  
`struct FCustomizableObjectIdPair`  
_L11-36_
- reflection: `USTRUCT(BlueprintType)`
- L16 _public member_ `FString CustomizableObjectGroupName;` — `UPROPERTY(Category = CustomizableObject, BlueprintReadOnly, EditDefaultsOnly)`
- L19 _public member_ `FString CustomizableObjectName;` — `UPROPERTY(Category = CustomizableObject, BlueprintReadOnly, EditDefaultsOnly)`
- L21 _public function_ `FCustomizableObjectIdPair()`
- L22 _public prototype_ `FCustomizableObjectIdPair(FString ObjectGroupName, FString ObjectName);`
- L24 _public function_ `bool operator ==(const FCustomizableObjectIdPair& Other) const`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CUSTOMIZABLEOBJECT_API`
- L29 _function_ `friend FArchive& operator <<(FArchive& Ar, FCustomizableObjectIdPair& IdPair)`

### `Plugins/Mutable/Source/CustomizableObject/Internal/MuCO/CustomizableObjectInstancePrivate.h` (Internal)


#### enum `ECOInstanceFlags`  
`enum ECOInstanceFlags`  
_L55-64_
- desc: CustomizableObject Instance flags for internal use
- L57 _public enumerator_ `ECONone = 0` — Should not use the name None here.. it collides with other enum in global namespace
- L60 _public enumerator_ `ReplacePhysicsAssets = 1 << 1` — Update process
- L62 _public enumerator_ `HasPendingHighPriorityUpdate = 1 << 2`
- L63 _public enumerator_ `HasPendingLowPriorityUpdate = 1 << 3`

#### struct `FCustomizableInstanceComponentData`  
`struct FCustomizableInstanceComponentData`  
_L70-93_
- reflection: `USTRUCT()`
- L74 _public member_ `FName ComponentName;`
- L76 _public member_ `UE::Mutable::Private::FComponentId ComponentId = INDEX_NONE;`
- L80 _public member_ `TArray<FString> MeshPartPaths;` — Just used for mutable.EnableMutableAnimInfoDebugging command
- L83 _public member_ `UE::Mutable::Private::FSkeletalMeshId LastSkeletalMeshId;`
- L86 _public member_ `TArray<TObjectPtr<UMaterialInterface>> OverrideMaterials;` — `UPROPERTY(Transient)`
- L89 _public member_ `TObjectPtr<UMaterialInterface> OverlayMaterial;` — `UPROPERTY(Transient)`
- L92 _public member_ `TArray<TObjectPtr<UMaterialInterface>> OverlayMaterials;` — `UPROPERTY(Transient)`

#### struct `FAnimInstanceOverridePhysicsAsset`  
`struct FAnimInstanceOverridePhysicsAsset`  
_L97-106_
- reflection: `USTRUCT()`
- L102 _public member_ `int32 PropertyIndex = 0;` — `UPROPERTY(Transient)`
- L105 _public member_ `TObjectPtr<UPhysicsAsset> PhysicsAsset;` — `UPROPERTY(Transient)`

#### struct `FAnimBpGeneratedPhysicsAssets`  
`struct FAnimBpGeneratedPhysicsAssets`  
_L110-116_
- reflection: `USTRUCT()`
- L115 _public member_ `TArray<FAnimInstanceOverridePhysicsAsset> AnimInstancePropertyIndexAndPhysicsAssets;` — `UPROPERTY(Transient)`

#### struct `FMaterialReuseCacheKey`  
`struct FMaterialReuseCacheKey`  
_L119-125_
- L121 _public member_ `TStrongObjectPtr<UMaterialInterface> MaterialTemplate;`
- L122 _public member_ `UE::Mutable::Private::FOperation::ADDRESS Root;`
- L124 _public prototype_ `bool operator==(const FMaterialReuseCacheKey&) const = default;`

#### struct `FTextureReuseCacheKey`  
`struct FTextureReuseCacheKey`  
_L131-136_
- L133 _public member_ `UE::Mutable::Private::FOperation::ADDRESS Root;`
- L135 _public prototype_ `bool operator==(const FTextureReuseCacheKey&) const = default;`

#### enum `ESkeletalMeshStatus`  
`enum class ESkeletalMeshStatus : uint8`  
_L148-153_
- desc: Indicates the status of the generated Skeletal Mesh.
- L150 _public enumerator_ `NotGenerated` — Set only when loading the Instance for the first time or after compiling. Any generation, successful or not, can not end up in this state.
- L151 _public enumerator_ `Success` — Generated successfully.
- L152 _public enumerator_ `Error` — Not generated. Set only after a failed update.

#### class `UCustomizableInstancePrivate`  
`class UCustomizableInstancePrivate : public UObject`  
_L157-300_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L164 _public member_ `TMap<FName, TObjectPtr<USkeletalMesh>> SkeletalMeshes;` — `UPROPERTY(Transient, VisibleAnywhere, Category = NoCategory)` — Generated Skeletal Meshes.
- L168 _public member_ `TArray<TObjectPtr<UMaterialInterface>> Materials;` — `UPROPERTY(Transient, VisibleAnywhere, Category = NoCategory)` — Generated Materials.
- L172 _public member_ `TArray<TObjectPtr<UTexture>> Textures;` — `UPROPERTY(Transient, VisibleAnywhere, Category = NoCategory)` — Generated Textures.
- L176 _public member_ `TArray<TObjectPtr<const UObject>> ExtensionData;` — `UPROPERTY(Transient)` — Generated Extension Data.
- L180 _public member_ `bool bKeepOwnershipOfGeneratedResources = true;` — `UPROPERTY(EditAnywhere, Category = UpdateOptions)` — If check, Mutable will keep the ownership of the generated resources. This means that Mutable may decide to modify or reuse them for performance considerations.
- L184 _public member_ `TArray<uint32> RelevantParameters;` — Indices of the parameters that are relevant for the given parameter values. This only gets updated if parameter decorations are generated.
- L187 _public member_ `TSharedPtr<UE::Mutable::Private::FLiveInstance> LiveInstance;` — Only used in LiveUpdateMode to reuse core instances between updates and their temp data to speed up updates, but spend way more memory
- L190 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L192 _public prototype_ `void BindObjectDelegates(UCustomizableObject* CurrentCustomizableObject, UCustomizableObject* NewCustomizableObject);`
- L194 _public prototype_ `void OnPostCompile();`
- L195 _public prototype_ `void OnObjectStatusChanged(FCustomizableObjectStatus::EState Previous, FCustomizableObjectStatus::EState Next);`
- L198 _public function_ `ECOInstanceFlags GetCOInstanceFlags() const`
- L199 _public function_ `void SetCOInstanceFlags(ECOInstanceFlags FlagsToSet)`
- L200 _public function_ `void ClearCOInstanceFlags(ECOInstanceFlags FlagsToClear)`
- L201 _public function_ `bool HasCOInstanceFlags(ECOInstanceFlags FlagsToCheck) const`
- L203 _public prototype_ `void BuildResources(const TSharedRef<FUpdateContextPrivate>& Context, UCustomizableObjectInstance* Public);`
- L206 _public prototype_ `bool UpdateSkeletalMesh_PostBeginUpdate0(UCustomizableObjectInstance* Instance, const TSharedRef<FUpdateContextPrivate>& Context);` — Returns true if success (?)
- L209 _public prototype_ `void PostEditChangePropertyWithoutEditor();` — The following method is basically copied from PostEditChangeProperty and/or SkeletalMesh.cpp to be able to replicate PostEditChangeProperty without the editor
- L212 _public prototype_ `void ForceSetReferenceSkeletalMesh() const;` — Only use as an emergency fallback! Set the reference SkeletalMesh unconditionally to all actors using this instance. It will hitch.
- L214 _public prototype_ `const TArray<FAnimInstanceOverridePhysicsAsset>* GetGeneratedPhysicsAssetsForAnimInstance(TSubclassOf<UAnimInstance> AnimInstance) const;`
- L217 _public prototype_ `void RegenerateImportedModels(const TSharedRef<FUpdateContextPrivate>& OperationData);`
- L220 _public prototype_ `FCustomizableInstanceComponentData* GetComponentData(const FName& ComponentName);`
- L221 _public prototype_ `FCustomizableInstanceComponentData& GetComponentData(UE::Mutable::Private::FComponentId ComponentId);`
- L223 _public prototype_ `void InvalidateGeneratedData();`
- L225 _public prototype_ `int32 GetState() const;`
- L227 _public prototype_ `void SetState(int32 InState);`
- L229 _public prototype_ `FCustomizableObjectInstanceDescriptor& GetDescriptor() const;`
- L231 _public prototype_ `void CopyParametersFromInstance(UCustomizableObjectInstance* Instance);`
- L234 _public prototype_ `int32 FindIntParameterNameIndex(const FString& ParamName) const;` — Finds in IntParameters a parameter with name ParamName, returns the index if found, -1 otherwise.
- L237 _public prototype_ `int32 FindFloatParameterNameIndex(const FString& ParamName) const;` — Finds in FloatParameters a parameter with name ParamName, returns the index if found, -1 otherwise.
- L240 _public prototype_ `int32 FindBoolParameterNameIndex(const FString& ParamName) const;` — Finds in BoolParameters a parameter with name ParamName, returns the index if found, -1 otherwise.
- L243 _public prototype_ `int32 FindVectorParameterNameIndex(const FString& ParamName) const;` — Finds in VectorParameters a parameter with name ParamName, returns the index if found, -1 otherwise.
- L246 _public prototype_ `int32 FindProjectorParameterNameIndex(const FString& ParamName) const;` — Finds in ProjectorParameters a parameter with name ParamName, returns the index if found, -1 otherwise.
- L248 _public prototype_ `bool IsParameterRelevant(uint32 ParameterIndex) const;`
- L250 _public prototype_ `UCustomizableObjectInstance* GetPublic() const;`
- L252 _public prototype_ `void RegisterCustomizableObjectInstanceUsage(UCustomizableObjectInstanceUsage& Obj);`
- L253 _public prototype_ `void UnregisterCustomizableObjectInstanceUsage(UCustomizableObjectInstanceUsage& Obj);`
- L256 _public member_ `TArray<FCustomizableInstanceComponentData> ComponentsData;` — `UPROPERTY(Transient)`
- L259 _public member_ `TMap<TSubclassOf<UAnimInstance>, FAnimBpGeneratedPhysicsAssets> AnimBpPhysicsAssets;` — `UPROPERTY(Transient, Category = Animation, editfixedsize, VisibleAnywhere)`
- L262 _private member_ `ECOInstanceFlags InstanceFlagsPrivate = ECOInstanceFlags::ECONone;`
- L267 _public member_ `FCustomizableObjectInstanceDescriptor CommittedDescriptor;` — `UPROPERTY(Transient)` — Copy of the descriptor of the latest successful update.
- L270 _public member_ `FDescriptorHash CommittedDescriptorHash;` — Hash of the descriptor copy of the latest successful update.
- L273 _public member_ `ESkeletalMeshStatus SkeletalMeshStatus = ESkeletalMeshStatus::NotGenerated;` — Status of the generated Skeletal Mesh. Not to be confused with the Update Result.
- L275 _public member_ `bool bShowOnlyRuntimeParameters = true;`
- L276 _public member_ `bool bShowOnlyRelevantParameters = true;`
- L277 _public member_ `bool bShowUISections = false;`
- L278 _public member_ `bool bShowUIThumbnails = false;`
- L282 _public member_ `FText ParametersSearchFilter;` — Preview Instance Properties search box filter. Saved here to avoid losing the text during UI refreshes.
- L287 _public member_ `FObjectInstanceTransactedDelegate OnInstanceTransactedDelegate;` — Delegate called when the Instance has been transacted
- L290 _public member_ `TMap<FMaterialReuseCacheKey, TStrongObjectPtr<UMaterialInterface>> LastMaterialsReuseCache;`
- L291 _public member_ `TMap<FMaterialReuseCacheKey, TStrongObjectPtr<UMaterialInterface>> CurrentMaterialsReuseCache;`
- L293 _public member_ `TMap<FTextureReuseCacheKey, TStrongObjectPtr<UTexture2D>> LastTextureReuseCache;`
- L294 _public member_ `TMap<FTextureReuseCacheKey, TStrongObjectPtr<UTexture2D>> CurrentTextureReuseCache;`
- L297 _public member_ `TSharedPtr<IMutableEditorLogger> UpdateLogger;` — Pointer to a instance of class that logs update messages to an editor widget.
- L299 _public member_ `TArray<UCustomizableObjectInstanceUsage*> InstanceUsages;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API CUSTOMIZABLEOBJECT_API`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Mutable` (scope `UE`)
- L21 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L39 _externvar_ `extern const FString MULTILAYER_PROJECTOR_PARAMETERS_INVALID;` — Log texts
- L43 _externvar_ `extern const FString NUM_LAYERS_PARAMETER_POSTFIX;` — FParameters encoding
- L44 _externvar_ `extern const FString OPACITY_PARAMETER_POSTFIX;`
- L45 _externvar_ `extern const FString IMAGE_PARAMETER_POSTFIX;`
- L46 _externvar_ `extern const FString POSE_PARAMETER_POSTFIX;`
- L51 _prototype_ `void ConvertImage(UTexture2D* Texture, UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FImage> MutableImage, const FMutableModelImageProperties& Props, int32 OnlyLOD = -1, int32 ExtractChannel = -1);` — \param OnlyLOD: If not 0, extract and convert only one single LOD from the source image. \param ExtractChannel: If different than -1, extract a single-channel image with the specified source channel data.
- L66 _prototype_ `ENUM_CLASS_FLAGS(ECOInstanceFlags);`
- L128 _prototype_ `uint32 GetTypeHash(const FMaterialReuseCacheKey& Key);`
- L139 _prototype_ `uint32 GetTypeHash(const FTextureReuseCacheKey& Key);`
- L143 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FObjectInstanceTransactedDelegate, const FTransactionObjectEvent&);`
- L143 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FObjectInstanceTransactedDelegate, const FTransactionObjectEvent&);`
- L303 _prototype_ `UPhysicsAsset* GetOrBuildMainPhysicsAsset(const TSharedRef<FUpdateContextPrivate>& Context, TObjectPtr<UPhysicsAsset> TamplateAsset, const UE::Mutable::Private::FPhysicsBody* PhysicsBody, bool bDisableCollisionBetweenAssets, int32 ComponentIndex);`
- L305 _prototype_ `USkeleton* MergeSkeletons(const TArray<TObjectPtr<USkeleton>>& SkeletonsToMerge, UCustomizableObject& CustomizableObject, bool& bOutCreatedNewSkeleton);`
- L307 _prototype_ `void InitSkeletalMeshData(const TSharedRef<FUpdateContextPrivate>& Context, USkeletalMesh* SkeletalMesh, const FMutableRefSkeletalMeshData& RefSkeletalMeshData, const UCustomizableObject& CustomizableObject, const TSharedPtr<FInstanceUpdateData::FComponent>& Component);`
- L309 _prototype_ `void BuildOrCopyClothingData(const TSharedRef<FUpdateContextPrivate>& Context, USkeletalMesh* SkeletalMesh, const UModelResources& CustomizableObjectInstance, int32 InstanceComponentIndex);`
- L311 _prototype_ `bool BuildSkeletonData(const TSharedRef<FUpdateContextPrivate>& Context, USkeletalMesh& SkeletalMesh, int32 ComponentIndex);`
- L313 _prototype_ `void BuildMeshSockets(USkeletalMesh* SkeletalMesh, const UModelResources& ModelResources, const FMutableRefSkeletalMeshData& RefSkeletalMeshData, UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FMesh>& MutableMesh);`
- L315 _prototype_ `bool BuildOrCopyRenderData(const TSharedRef<FUpdateContextPrivate>& Context, USkeletalMesh* SkeletalMesh, UCustomizableObjectInstance* CustomizableObjectInstance, int32 ComponentIndex);`
- L317 _prototype_ `void BuildOrCopyElementData(const TSharedRef<FUpdateContextPrivate>& Context, USkeletalMesh* SkeletalMesh, int32 ComponentIndex);`
- L319 _prototype_ `void BuildOrCopyMorphTargetsData(const TSharedRef<FUpdateContextPrivate>& Context, USkeletalMesh* SkeletalMesh, int32 ComponentIndex);`
- L321 _prototype_ `UE::Tasks::FTask LoadAdditionalAssetsAndData(const TSharedRef<FUpdateContextPrivate>& Context);`
- L323 _prototype_ `void AdditionalAssetsAsyncLoaded(TSharedRef<FUpdateContextPrivate> Context, UE::Tasks::FTaskEvent Event);`

### `Plugins/Mutable/Source/CustomizableObject/Internal/MuCO/CustomizableObjectInstanceUsagePrivate.h` (Internal)


#### class `UCustomizableObjectInstanceUsagePrivate`  
`class UCustomizableObjectInstanceUsagePrivate : public UObject`  
_L13-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L21 _public prototype_ `void Callbacks();` — Common end point of all updates. Even those which failed.
- L23 _public prototype_ `USkeletalMesh* GetSkeletalMesh() const;`
- L25 _public prototype_ `USkeletalMesh* GetAttachedSkeletalMesh() const;`
- L27 _public prototype_ `UCustomizableObjectInstanceUsage* GetPublic();`
- L29 _public prototype_ `const UCustomizableObjectInstanceUsage* GetPublic() const;`
- L32 _public member_ `bool bPendingSetReferenceSkeletalMesh = true;` — Used to replace the Skeletal Mesh of the parent component by the Reference Skeletal Mesh.
- L34 _public member_ `bool bIsNetModeDedicatedServer = false;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CUSTOMIZABLEOBJECT_API`

### `Plugins/Mutable/Source/CustomizableObject/Internal/MuCO/CustomizableObjectMipDataProvider.h` (Internal)


#### class `FMutableUpdateImageContext`  
`class FMutableUpdateImageContext`  
_L30-55_
- desc: This struct stores the data relevant for the construction of a specific texture. This includes all the data required to rebuild the image (or any of its mips).
- L34 _public function_ `FMutableUpdateImageContext(TSharedRef<UE::Mutable::Private::FLiveInstance> InLiveInstance) : LiveInstance(InLiveInstance)`
- L41 _public member_ `FString CapturedDescriptor;` — Benchmarking Utility data (it may not always be present)
- L42 _public member_ `bool bLevelBegunPlay = false;`
- L44 _public member_ `FString CustomizableObjectPathName;`
- L45 _public member_ `FString InstancePathName;`
- L47 _public member_ `FName CustomizableObjectName;`
- L49 _public member_ `TSharedRef<UE::Mutable::Private::FLiveInstance> LiveInstance;`
- L51 _public member_ `TSharedPtr<UE::Mutable::Private::FSystem> System;`
- L53 _public member_ `TSharedPtr<FModelStreamableBulkData> ModelStreamableBulkData;`

#### struct `FMutableMipUpdateLevel`  
`struct FMutableMipUpdateLevel`  
_L58-69_
- L60 _public function_ `FMutableMipUpdateLevel(int32 InMipLevel, void* InDest, int32 InSizeX, int32 InSizeY, int32 InDataSize, EPixelFormat InFormat) : Dest(InDest), MipLevel(InMipLevel), SizeX(InSizeX), SizeY(InSizeY), DataSize(InDataSize), Format(InFormat)`
- L63 _public member_ `void* Dest;` — Only access from the FMutableTextureMipDataProvider, owned by the FTextureMipInfoArray so don't delete
- L64 _public member_ `int32 MipLevel;`
- L65 _public member_ `int32 SizeX;`
- L66 _public member_ `int32 SizeY;`
- L67 _public member_ `int32 DataSize;`
- L68 _public member_ `EPixelFormat Format;`

#### struct `UE::Mutable::Private::MemoryCounters::FPrefetchMemoryCounter`  
`struct FPrefetchMemoryCounter`  
_L73-80_
- L75 _public function_ `static std::atomic<SSIZE_T>& Get()`

#### struct `FMutableImageOperationData`  
`struct FMutableImageOperationData`  
_L84-112_
- desc: Runtime data used during a mutable image mipmap update
- L87 _public member_ `int32 MipsToSkip = 0;` — This option comes from the operation request. It is used to reduce the number of mipmaps that mutable must generate for images.
- L88 _public member_ `FMutableImageReference RequestedImage;`
- L90 _public member_ `TSharedPtr<FMutableUpdateImageContext> UpdateContext;`
- L92 _public member_ `UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FImage> Result;`
- L94 _public member_ `TArray<FMutableMipUpdateLevel> Levels;`
- L96 _public member_ `uint32 MutableTaskId = FMutableTaskGraph::INVALID_ID;`
- L98 _public typedef_ `using FPrefetchArray = TArray<uint8, UE::Mutable::Private::FDefaultMemoryTrackingAllocator<UE::Mutable::Private::MemoryCounters::FPrefetchMemoryCounter>>;`
- L99 _public member_ `FPrefetchArray AllocatedMemory;`
- L102 _public member_ `FThreadSafeCounter* Counter;` — Used to sync with the FMutableTextureMipDataProvider and FRenderAssetUpdate::Tick
- L103 _public member_ `FTextureUpdateSyncOptions::FCallback RescheduleCallback;`
- L105 _public member_ `bool bIsCancelled = false;`
- L108 _public member_ `FCriticalSection CounterTaskLock;` — Access to the Counter must be protected with this because it may be accessed from another thread to null it.
- L111 _public member_ `int64 ImageUpdateStartBytes = 0;` — Image Update Memory stats

#### class `FMutableTextureMipDataProvider`  
`class FMutableTextureMipDataProvider : public FTextureMipDataProvider`  
_L115-144_
- inherits: `FTextureMipDataProvider`
- L118 _public prototype_ `FMutableTextureMipDataProvider(const UTexture* Texture, UCustomizableObjectInstance* InCustomizableObjectInstance, const FMutableImageReference& InImageRef);`
- L120 _public prototype_ `virtual void Init(const FTextureUpdateContext& Context, const FTextureUpdateSyncOptions& SyncOptions) override;`
- L121 _public prototype_ `virtual int32 GetMips(const FTextureUpdateContext& Context, int32 StartingMipIndex, const FTextureMipInfoArray& MipInfos, const FTextureUpdateSyncOptions& SyncOptions) override;`
- L122 _public prototype_ `virtual bool PollMips(const FTextureUpdateSyncOptions& SyncOptions) override;`
- L123 _public prototype_ `virtual void CleanUp(const FTextureUpdateSyncOptions& SyncOptions) override;`
- L124 _public prototype_ `virtual void Cancel(const FTextureUpdateSyncOptions& SyncOptions) override;`
- L125 _public prototype_ `virtual ETickThread GetCancelThread() const override;`
- L126 _public prototype_ `void AbortPollMips() override;`
- L129 _private prototype_ `void CancelAsyncTasks();`
- L130 _private prototype_ `void PrintWarningAndAdvanceToCleanup();`
- L134 _public member_ `UCustomizableObjectInstance* CustomizableObjectInstance = nullptr;` — Todo: Simplify by replacing the reference to the Instance with some static parametrization or hash with enough info to reconstruct the texture
- L136 _public member_ `FMutableImageReference ImageRef;`
- L137 _public member_ `TSharedPtr<FMutableUpdateImageContext> UpdateContext;`
- L139 _public member_ `bool bRequestAborted = false;`
- L141 _public member_ `TSharedPtr<FMutableImageOperationData> OperationData;`
- L143 _public member_ `TUniquePtr<FMutableStreamRequest> PrefetchRequest;`

#### class `UMutableTextureMipDataProviderFactory`  
`class UMutableTextureMipDataProviderFactory : public UTextureMipDataProviderFactory`  
_L148-175_
- reflection: `UCLASS(MinimalAPI, hidecategories=Object)`
- inherits: `UTextureMipDataProviderFactory`
- L153 _public function_ `virtual FTextureMipDataProvider* AllocateMipDataProvider(UTexture* Asset) override`
- L161 _public function_ `virtual bool WillProvideMipDataWithoutDisk() const override`
- L166 _public prototype_ `virtual bool ShouldAllowPlatformTiling(const UTexture* Owner) const override;`
- L170 _public member_ `TObjectPtr<UCustomizableObjectInstance> CustomizableObjectInstance = nullptr;` — `UPROPERTY(Transient)` — Todo: Simplify by replacing the reference to the Instance with some static parametrization or hash with enough info to reconstruct the texture
- L172 _public member_ `FMutableImageReference ImageRef;`
- L173 _public member_ `TSharedPtr<FMutableUpdateImageContext> UpdateContext;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Mutable` (scope `UE`)
- L17 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Mutable` (scope `UE`)
- L18 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L71 _namespace_ `namespace UE`
- L71 _namespace_ `namespace Mutable` (scope `UE`)
- L71 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L71 _namespace_ `namespace MemoryCounters` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/CustomizableObject/Internal/MuCO/CustomizableObjectPrivate.h` (Internal)


#### struct `MutableCompiledDataStreamHeader`  
`struct MutableCompiledDataStreamHeader`  
_L71-86_
- desc: Warning! MutableCompiledDataHeader must be the first data serialized in a stream
- L73 _public member_ `int32 InternalVersion=0;`
- L74 _public member_ `FGuid VersionId;`
- L76 _public function_ `MutableCompiledDataStreamHeader()`
- L77 _public function_ `MutableCompiledDataStreamHeader(int32 InInternalVersion, FGuid InVersionId) : InternalVersion(InInternalVersion), VersionId(InVersionId)`

#### struct `FMutableRemappedBone`  
`struct FMutableRemappedBone`  
_L90-104_
- reflection: `USTRUCT()`
- L95 _public member_ `FName Name;` — `UPROPERTY()`
- L98 _public member_ `uint32 Hash = 0;` — `UPROPERTY()`
- L100 _public function_ `bool operator==(const FName& InName)`

#### struct `FMutableModelParameterValue`  
`struct FMutableModelParameterValue`  
_L108-119_
- reflection: `USTRUCT()`
- L112 _public prototype_ `FMutableModelParameterValue() = default;`
- L115 _public member_ `FString Name;` — `UPROPERTY()`
- L118 _public member_ `int Value = 0;` — `UPROPERTY()`

#### struct `FMutableModelParameterProperties`  
`struct FMutableModelParameterProperties`  
_L123-135_
- reflection: `USTRUCT()`
- L127 _public prototype_ `FMutableModelParameterProperties() = default;`
- L128 _public member_ `FString Name;`
- L131 _public member_ `EMutableParameterType Type = EMutableParameterType::None;` — `UPROPERTY()`
- L134 _public member_ `TArray<FMutableModelParameterValue> PossibleValues;` — `UPROPERTY()`

#### class `FSkeletalMeshCache`  
`class FSkeletalMeshCache`  
_L138-152_
- L141 _public prototype_ `TStrongObjectPtr<UCustomizableObjectSkeletalMesh> Get(const UE::Mutable::Private::FSkeletalMeshId& Key);`
- L143 _public prototype_ `void Add(const UE::Mutable::Private::FSkeletalMeshId& Key, UCustomizableObjectSkeletalMesh* Value);`
- L145 _public prototype_ `void Clear();`
- L148 _private member_ `TMap<UE::Mutable::Private::FSkeletalMeshId, TWeakObjectPtr<UCustomizableObjectSkeletalMesh>> GeneratedSkeletalMeshes;`
- L151 _private member_ `UE::FMutex Lock;`

#### class `FTextureCache`  
`class FTextureCache`  
_L156-184_
- L172 _public prototype_ `TStrongObjectPtr<UTexture2D> Get(const FId& Key);`
- L174 _public prototype_ `void Add(const FId& Key, UTexture2D* Value);`
- L176 _public prototype_ `void Remove(const UTexture2D& Value);`
- L178 _public prototype_ `void Clear();`
- L181 _private member_ `TMap<FId, TWeakObjectPtr<UTexture2D>> GeneratedTextures;`
- L183 _private member_ `UE::FMutex Lock;`

#### struct `FTextureCache::FId`  
`struct FId`  
_L159-170_
- L161 _public member_ `UE::Mutable::Private::FImageId Resource;`
- L163 _public member_ `int32 SkippedMips = 0;`
- L165 _public member_ `bool bIsBake = false;`
- L167 _public prototype_ `bool operator==(const FId&) const = default;`

#### class `FSkeletonCache`  
`class FSkeletonCache`  
_L187-198_
- L190 _public prototype_ `USkeleton* Get(const TArray<FName>& Key);`
- L192 _public prototype_ `void Add(const TArray<FName>& Key, USkeleton* Value);`
- L194 _public prototype_ `void Clear();`
- L197 _private member_ `TMap<TArray<FName>, TWeakObjectPtr<USkeleton>> MergedSkeletons;`

#### struct `FCustomizableObjectStatusTypes`  
`struct FCustomizableObjectStatusTypes`  
_L201-223_
- L213 _public member_ `static constexpr EState StartState = EState::NoModel;`
- L215 _public member_ `static constexpr bool ValidTransitions[3][3] = {`

#### enum `FCustomizableObjectStatusTypes::EState`  
`enum class EState : uint8`  
_L203-211_
- L205 _public enumerator_ `Loading = 0` — Waiting for PostLoad and Asset Registry to finish.
- L206 _public enumerator_ `ModelLoaded` — Model loaded correctly.
- L207 _public enumerator_ `NoModel` — No model (due to no model not found and automatic compilations disabled).
- L210 _public enumerator_ `Count`

#### struct `FMutableModelImageProperties`  
`struct FMutableModelImageProperties`  
_L229-292_
- reflection: `USTRUCT()`
- L233 _public function_ `FMutableModelImageProperties() : Filter(TF_Default) , SRGB(0) , FlipGreenChannel(0) , IsPassThrough(0) , LODBias(0) , MipGenSettings(TextureMipGenSettings::TMGS_FromTextureGroup) , LODGroup(TEXTUREGROUP_World) , AddressX(TA_Clamp) , AddressY(TA_Clamp)`
- L245 _public function_ `FMutableModelImageProperties(const FString& InTextureParameterName, TextureFilter InFilter, uint32 InSRGB, uint32 InFlipGreenChannel, uint32 bInIsPassThrough, int32 InLODBias, TEnumAsByte<TextureMipGenSettings> InMipGenSettings, TEnumAsByte<enum TextureGroup> InLODGroup, TEnumAsByte<enum TextureAddress> InAddressX, TEnumAsByte<enum TextureAddress> InAddressY) : TextureParameterName(InTextureParameterName) , Filter(InFilter) , SRGB(InSRGB) , FlipGreenChannel(InFlipGreenChannel) , IsPassThrough(bInIsPassThrough) , LODBias(InLODBias) , MipGenSettings(InMipGenSettings) , LODGroup(InLODGroup) , AddressX(InAddressX) , AddressY(InAddressY)`
- L262 _public member_ `FString TextureParameterName;` — `UPROPERTY()` — Name in the material.
- L268 _public member_ `uint32 SRGB : 1;` — `UPROPERTY()`
- L271 _public member_ `uint32 FlipGreenChannel : 1;` — `UPROPERTY()`
- L274 _public member_ `uint32 IsPassThrough : 1;` — `UPROPERTY()`
- L277 _public member_ `int32 LODBias;` — `UPROPERTY()`
- L280 _public member_ `TEnumAsByte<TextureMipGenSettings> MipGenSettings;` — `UPROPERTY()`
- L291 _public prototype_ `bool operator!=(const FMutableModelImageProperties& rhs) const;`

#### struct `FMutableRefSocket`  
`struct FMutableRefSocket`  
_L296-320_
- reflection: `USTRUCT()`
- L301 _public member_ `FName SocketName;` — `UPROPERTY()`
- L303 _public member_ `FName BoneName;` — `UPROPERTY()`
- L306 _public member_ `FVector RelativeLocation = FVector::ZeroVector;` — `UPROPERTY()`
- L308 _public member_ `FRotator RelativeRotation = FRotator::ZeroRotator;` — `UPROPERTY()`
- L310 _public member_ `FVector RelativeScale = FVector::ZeroVector;` — `UPROPERTY()`
- L313 _public member_ `bool bForceAlwaysAnimated = false;` — `UPROPERTY()`
- L315 _public prototype_ `bool operator ==(const FMutableRefSocket& Other) const;`

#### struct `FMutableRefSkeletalMeshSettings`  
`struct FMutableRefSkeletalMeshSettings`  
_L324-337_
- reflection: `USTRUCT()`
- L329 _public member_ `bool bEnablePerPolyCollision = false;` — `UPROPERTY()`
- L332 _public member_ `float DefaultUVChannelDensity = 0.f;` — `UPROPERTY()`

#### struct `FMutableRefSkeletalMeshData`  
`struct FMutableRefSkeletalMeshData`  
_L341-388_
- reflection: `USTRUCT()`
- L347 _public member_ `TObjectPtr<USkeletalMesh> SkeletalMesh;` — `UPROPERTY()` — Reference Skeletal Mesh
- L351 _public member_ `TSoftObjectPtr<USkeletalMesh> SoftSkeletalMesh;` — `UPROPERTY()` — Path to load the ReferenceSkeletalMesh
- L355 _public member_ `TObjectPtr<USkeletalMeshLODSettings> SkeletalMeshLODSettings;` — `UPROPERTY()` — Optional USkeletalMeshLODSettings
- L359 _public member_ `TArray<FMutableRefSocket> Sockets;` — `UPROPERTY()` — Sockets
- L363 _public member_ `FBoxSphereBounds Bounds = FBoxSphereBounds(ForceInitToZero);` — `UPROPERTY()` — Bounding Box
- L367 _public member_ `FMutableRefSkeletalMeshSettings Settings;` — `UPROPERTY()` — Settings
- L371 _public member_ `TObjectPtr<USkeleton> Skeleton;` — `UPROPERTY()` — Skeleton
- L375 _public member_ `TObjectPtr<UPhysicsAsset> PhysicsAsset;` — `UPROPERTY()` — PhysicsAsset
- L379 _public member_ `TSoftClassPtr<UAnimInstance> PostProcessAnimInst;` — `UPROPERTY()` — Post Processing AnimBP
- L383 _public member_ `TObjectPtr<UPhysicsAsset> ShadowPhysicsAsset;` — `UPROPERTY()` — Shadow PhysicsAsset

#### struct `FAnimBpOverridePhysicsAssetsInfo`  
`struct FAnimBpOverridePhysicsAssetsInfo`  
_L392-407_
- reflection: `USTRUCT()`
- L397 _public member_ `TSoftClassPtr<UAnimInstance> AnimInstanceClass;` — `UPROPERTY()`
- L400 _public member_ `int32 PropertyIndex = -1;` — `UPROPERTY()`
- L402 _public prototype_ `bool operator==(const FAnimBpOverridePhysicsAssetsInfo& Rhs) const;`

#### struct `FMutableStreamableBlock`  
`struct FMutableStreamableBlock`  
_L412-435_
- reflection: `USTRUCT()`
- desc: TODO: Optimize this struct
- L417 _public member_ `uint32 FileId = 0;` — `UPROPERTY()`
- L421 _public member_ `uint16 Flags = 0;` — `UPROPERTY()` — Used to store properties of the data, necessary for its recovery. For instance if it is high-res.
- L423 _public member_ `uint16 IsPrefetched = 0;`
- L426 _public member_ `uint64 Offset = 0;` — `UPROPERTY()`

#### struct `FMutableParameterIndex`  
`struct FMutableParameterIndex`  
_L439-450_
- L442 _public function_ `FMutableParameterIndex(int32 InIndex, int32 InTypedIndex)`
- L448 _public member_ `int32 Index = INDEX_NONE;`
- L449 _public member_ `int32 TypedIndex = INDEX_NONE;`

#### struct `FIntegerParameterOptionKey`  
`struct FIntegerParameterOptionKey`  
_L454-468_
- reflection: `USTRUCT()`
- L459 _public member_ `FString ParameterName;` — `UPROPERTY()`
- L462 _public member_ `FString ParameterOption;` — `UPROPERTY()`
- L466 _public prototype_ `bool operator==(const FIntegerParameterOptionKey& Other) const = default;`

#### struct `FIntegerParameterOptionDataTable`  
`struct FIntegerParameterOptionDataTable`  
_L472-478_
- reflection: `USTRUCT()`
- L477 _public member_ `TSet<TSoftObjectPtr<UDataTable>> DataTables;` — `UPROPERTY()`

#### struct `FIntegerParameterUIData`  
`struct FIntegerParameterUIData`  
_L482-494_
- reflection: `USTRUCT()`
- L486 _public prototype_ `FIntegerParameterUIData() = default;`
- L488 _public prototype_ `FIntegerParameterUIData(const FMutableParamUIMetadata& InParamUIMetadata);`
- L491 _public member_ `FMutableParamUIMetadata ParamUIMetadata;` — `UPROPERTY()`

#### struct `FMutableParameterData`  
`struct FMutableParameterData`  
_L498-522_
- reflection: `USTRUCT()`
- L502 _public prototype_ `FMutableParameterData() = default;`
- L504 _public prototype_ `FMutableParameterData(const FMutableParamUIMetadata& InParamUIMetadata, EMutableParameterType InType);`
- L507 _public member_ `FMutableParamUIMetadata ParamUIMetadata;` — `UPROPERTY()`
- L511 _public member_ `EMutableParameterType Type = EMutableParameterType::None;` — `UPROPERTY()` — Parameter type
- L515 _public member_ `TMap<FString, FIntegerParameterUIData> ArrayIntegerParameterOption;` — `UPROPERTY()` — In the case of an integer parameter, store here all options
- L519 _public member_ `ECustomizableObjectGroupType IntegerParameterGroupType = ECustomizableObjectGroupType::COGT_ONE_OR_NONE;` — `UPROPERTY()` — How are the different options selected (one, one or none, etc...)

#### struct `FMutableStateData`  
`struct FMutableStateData`  
_L526-550_
- reflection: `USTRUCT()`
- L531 _public member_ `FMutableStateUIMetadata StateUIMetadata;` — `UPROPERTY()`
- L536 _public member_ `bool bLiveUpdateMode = false;` — `UPROPERTY()` — In this mode instances and their temp data will be reused between updates. It will be much faster but spend as much as ten times the memory. Useful for customization lockers with few characters that are going to have their parameters changed many times, not for in-game
- L540 _public member_ `bool bDisableMeshStreaming = false;` — `UPROPERTY()` — If this is enabled, Mesh streaming won't be used for this state, and all LODs will be generated when an instance is first updated.
- L544 _public member_ `bool bDisableTextureStreaming = false;` — `UPROPERTY()` — If this is enabled, texture streaming won't be used for this state, and full images will be generated when an instance is first updated.
- L547 _public member_ `TMap<FString, FString> ForcedParameterValues;` — `UPROPERTY()`

#### enum `EMutableFileFlags`  
`enum class EMutableFileFlags : uint8`  
_L554-560_
- desc: This is encoded in exact bits so if extended, review its uses everywhere.
- L556 _public enumerator_ `None = 0`
- L557 _public enumerator_ `HighRes = 1 << 0`
- L558 _public enumerator_ `DoesExist = 1 << 1`
- L559 _public enumerator_ `DoesExistCached = 1 << 2`

#### enum `UE::Mutable::Private::EStreamableDataType`  
`enum class EStreamableDataType : uint32`  
_L565-571_
- desc: uint32 for padding and DDC purposes
- L567 _public enumerator_ `None = 0`
- L568 _public enumerator_ `Model`
- L570 _public enumerator_ `DataTypeCount`

#### struct `UE::Mutable::Private::FBlock`  
`struct FBlock`  
_L574-598_
- L577 _public member_ `uint32 Id;` — Used on some data types as the index to the block stored in the CustomizableObject
- L580 _public member_ `uint32 SourceId;` — Used on some data types to group blocks.
- L583 _public member_ `uint32 Size;` — Size of the data block.
- L585 _public member_ `uint32 Padding = 0;`
- L588 _public member_ `uint64 Offset;` — Offset in the full source streamed data file that is created when compiling.

#### struct `UE::Mutable::Private::FFile`  
`struct FFile`  
_L601-635_
- L603 _public member_ `EStreamableDataType DataType = EStreamableDataType::None;`
- L606 _public member_ `uint16 ResourceType = 0;` — Rom ResourceType.
- L609 _public member_ `uint16 Flags = 0;` — Common flags of the data stored in this file. See EMutableFileFlags.
- L612 _public member_ `uint32 Id = 0;` — Id generated from a hash of the file content + offset to avoid collisions.
- L615 _public member_ `uint64 Size = 0;` — File size
- L618 _public member_ `TArray<FBlock> Blocks;` — List of blocks that are contained in the file, in order.
- L621 _public prototype_ `uint64 GetSize() const;` — Get the total size of blocks in this file.
- L624 _public prototype_ `void GetFileData(struct FMutableCachedPlatformData*, TArray64<uint8>& DataDestination, bool bDropData);` — Copy the requested block to the requested buffer and return its size.

#### struct `UE::Mutable::Private::FFileCategoryID`  
`struct FFileCategoryID`  
_L637-661_
- L639 _public prototype_ `FFileCategoryID(EStreamableDataType DataType, uint16 ResourceType, uint16 Flags);`
- L641 _public prototype_ `FFileCategoryID() = default;`
- L644 _public member_ `EStreamableDataType DataType = EStreamableDataType::None;` — EDataType
- L647 _public member_ `uint16 ResourceType = 0;` — Rom ResourceType.
- L650 _public member_ `uint16 Flags = 0;` — Rom flags
- L653 _public prototype_ `bool operator==(const FFileCategoryID& Other) const = default;`

#### struct `UE::Mutable::Private::FFileCategory`  
`struct FFileCategory`  
_L664-675_
- L666 _public member_ `FFileCategoryID Id;`
- L669 _public member_ `uint64 DataSize = 0;` — Accumulated size of resources from this category
- L673 _public member_ `uint32 FirstFile = 0;` — Categories within a bucket with a limited number of files will use sequential ID starting at FirstFile and up to FirstFile + NumFiles.
- L674 _public member_ `uint32 NumFiles = 0;`

#### struct `UE::Mutable::Private::FFileCategoryOverride`  
`struct FFileCategoryOverride`  
_L678-682_
- L680 _public member_ `FFileCategoryID Id;`
- L681 _public member_ `uint32 NumFiles = 0;`

#### struct `UE::Mutable::Private::FFileBucket`  
`struct FFileBucket`  
_L686-693_
- desc: Group bulk data by categories.
- L689 _public member_ `TArray<FFileCategory> Categories;` — Resources belonging to these categories will be added to the bucket.
- L692 _public member_ `uint64 DataSize = 0;` — Accumulated size of the resources of all categories within this bucket

#### struct `UE::Mutable::Private::FModelStreamableData`  
`struct FModelStreamableData`  
_L695-722_
- L697 _public function_ `void Get(uint32 Key, TArrayView64<uint8> Destination, bool bDropData)`
- L710 _public function_ `void Set(uint32 Key, const uint8* Source, int64 Size)`
- L721 _public member_ `TMap<uint32, TArray64<uint8> > Data;` — Temp, to be replaced with disk storage

#### struct `UE::Mutable::Private::FMutableCachedPlatformData`  
`struct FMutableCachedPlatformData`  
_L725-741_
- L728 _public member_ `TSharedPtr<UE::Mutable::Private::FModel, ESPMode::ThreadSafe> Model;` — UE::Mutable::Private::Model
- L731 _public member_ `TStrongObjectPtr<UModelResources> ModelResources;` — UModelResources
- L734 _public member_ `TSharedPtr<FModelStreamableBulkData> ModelStreamableBulkData;` — Streamable resources info such as files and offsets.
- L737 _public member_ `FModelStreamableData ModelStreamableData;` — Struct containing map of RomId to RomBytes.
- L740 _public member_ `TArray<FFile> BulkDataFiles;` — List of files to serialize. Each file has a list of binary blocks to be serialized.

#### struct `FModelStreamableBulkData`  
`struct FModelStreamableBulkData`  
_L789-822_
- L792 _public member_ `TMap<uint32, FMutableStreamableBlock> ModelStreamables;` — Map of Hash to Streaming blocks, used to stream a block of data representing a resource from the BulkData
- L794 _public member_ `TArray<EMutableFileFlags> BulkDataFlags;`
- L795 _public member_ `TArray<FByteBulkData> StreamableBulkData;`
- L799 _public member_ `bool bIsStoredInDDC = false;` — Used to know if roms and other resources must be streamed from the DDC.
- L800 _public member_ `UE::DerivedData::FCacheKey DDCKey = UE::DerivedData::FCacheKey::Empty;`
- L801 _public member_ `UE::DerivedData::ECachePolicy DDCDefaultPolicy = UE::DerivedData::ECachePolicy::Default;`
- L802 _public member_ `TArray<FIoHash> DDCValues;`
- L806 _public member_ `FString FullFilePath;` — File path to stream resources from when not using FByteBulkData or DDC.
- L808 _public prototype_ `void Serialize(FArchive& Ar, UObject* Owner, bool bCooked);`

#### class `UModelStreamableData`  
`class UModelStreamableData : public UObject`  
_L826-838_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Interface class to allow custom serialization of FModelStreamableBulkData and its FBulkData.
- L830 _private prototype_ `UModelStreamableData();`
- L833 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L835 _public prototype_ `virtual void PostLoad() override;`
- L837 _public member_ `TSharedPtr<FModelStreamableBulkData> StreamingData;`

#### struct `FMutableParamNameSet`  
`struct FMutableParamNameSet`  
_L841-846_
- reflection: `USTRUCT()`
- L845 _public member_ `TSet<FString> ParamNames;`

#### class `UModelResources`  
`class UModelResources : public UObject`  
_L853-977_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Class containing all UE resources derived from a CO compilation. These resources will be embedded in the CO at cook time but not in the editor. Editor compilations will serialize this class to disk using the Serialize methods. Ensure new fields are serialized, too. Variables and settings that should not change until the CO is re-compiled should be stored here.
- L864 _public member_ `TArray<FMutableRefSkeletalMeshData> ReferenceSkeletalMeshesData;` — `UPROPERTY()` — Key is FComponentId. All the SkeletalMeshes generated for this CustomizableObject instances will use the Reference Skeletal Mesh properties for everything that Mutable doesn't create or modify. This struct stores the information used from the Reference Skeletal Meshes to avoid having them loaded at all times. This includes data like LOD distances, LOD render data settings, Mesh sockets, Bounding volumes, etc.
- L867 _public member_ `TMap<uint32, TSoftObjectPtr<UObject>> PassthroughObjects;` — `UPROPERTY()`
- L871 _public member_ `TArray<uint32> DuplicateObjects;` — `UPROPERTY()`
- L875 _public member_ `TArray<TSoftObjectPtr<UTexture2D>> RuntimeReferencedTextures;` — `UPROPERTY()` — Runtime referenced textures used by the UE::Mutable::Private::FModel.
- L880 _public member_ `TArray<TSoftClassPtr<UAnimInstance>> AnimBPs;` — `UPROPERTY()` — UAnimBlueprint assets gathered from the SkeletalMesh, to be used in mesh generation in-game
- L884 _public member_ `TArray<FAnimBpOverridePhysicsAssetsInfo> AnimBpOverridePhysiscAssetsInfo;` — `UPROPERTY()`
- L887 _public member_ `TArray<FMutableModelImageProperties> ImageProperties;` — `UPROPERTY()`
- L891 _public member_ `TMap<FString, FMutableParameterData> ParameterUIDataMap;` — `UPROPERTY()` — Parameter UI metadata information for all the dependencies of this Customizable Object.
- L895 _public member_ `TMap<FString, FMutableStateData> StateUIDataMap;` — `UPROPERTY()` — State UI metadata information for all the dependencies of this Customizable Object
- L900 _public member_ `TMap<FIntegerParameterOptionKey, FIntegerParameterOptionDataTable> IntParameterOptionDataTable;` — `UPROPERTY()` — DataTable used by an int parameter and its value.
- L905 _public member_ `bool bAllowClothingPhysicsEditsPropagation = true;` — `UPROPERTY()` — Currently not used, this option should be selectable from editor maybe as a compilation flag
- L911 _public member_ `TMap<FString, FMutableParamNameSet> TableToParamNames;` — `UPROPERTY()` — Stores what param names use a certain table as a table can be used from multiple table nodes, useful for partial compilations to restrict params
- L916 _public member_ `TMap<FString, FString> CustomizableObjectPathMap;` — `UPROPERTY()` — Map to identify what CustomizableObject owns a parameter. Used to display a tooltip when hovering a parameter in the Prev. instance panel
- L919 _public member_ `TMap<FString, FCustomizableObjectIdPair> GroupNodeMap;` — `UPROPERTY()`
- L923 _public member_ `bool bIsCompiledWithOptimization = true;` — `UPROPERTY()` — If the object is compiled with maximum optimizations.
- L927 _public member_ `bool bIsTextureStreamingDisabled = false;` — `UPROPERTY()` — This is a non-user-controlled flag to disable streaming (set at object compilation time, depending on optimization).
- L934 _public member_ `TMap<FName, FGuid> ParticipatingObjects;` — `UPROPERTY()` — List of external packages that if changed, a compilation is required. Key is the package name. Value is the the UPackage::Guid, which is regenerated each time the packages is saved. Updated each time the CO is compiled and saved in the Derived Data.
- L939 _public member_ `TMap<uint32, FInstancedStruct> ExternalOperations;` — `UPROPERTY()` — Key is UE::Mutable::Private::OP::ADDRESS. UPROPERTY does not support typedefs.
- L943 _public member_ `TMap<TObjectPtr<const UScriptStruct>, uint32> ExternalOperationVersions;` — `UPROPERTY()` — Value is the compiled version of the operation.
- L947 _public member_ `TArray<FName> ComponentNamesPerObjectComponent;` — `UPROPERTY()` — Key is FComponentId. Name of all possible components.
- L950 _public member_ `TMap<FString, TObjectPtr<UTexture>> TextureParameterDefaultValues;` — `UPROPERTY()`
- L953 _public member_ `TMap<FString, TObjectPtr<USkeletalMesh>> SkeletalMeshParameterDefaultValues;` — `UPROPERTY()`
- L956 _public member_ `TMap<FString, TObjectPtr<UMaterialInterface>> MaterialParameterDefaultValues;` — `UPROPERTY()`
- L959 _public member_ `TMap<FString, FInstancedStruct> ExternalTypeParameterDefaultValues;` — `UPROPERTY()`
- L962 _public member_ `TMap<FString, TObjectPtr<const UScriptStruct>> ExternalTypeParameterTypes;` — `UPROPERTY()`
- L965 _public member_ `FString ReleaseVersion;` — `UPROPERTY()`
- L968 _public member_ `int32 CodeVersion = 0;` — `UPROPERTY()`
- L975 _public member_ `bool bCompiledWithHDTextureCompression = false;` — `UPROPERTY()` — Value of the variable TextureCompression in the last compilation of this CO. this is needed since we can compile a CO through blueprints with a different compilation setting than the stored in the COE.

#### struct `FMutableMeshComponentData`  
`struct FMutableMeshComponentData`  
_L981-999_
- reflection: `USTRUCT()`
- L987 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)` — Name to identify this component.
- L998 _public member_ `TObjectPtr<USkeletalMesh> ReferenceSkeletalMesh;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)` — All the SkeletalMeshes generated for this CustomizableObject instances will use the Reference Skeletal Mesh properties for everything that Mutable doesn't create or modify. This includes data like LOD distances, Physics properties, Bounding Volumes, Skeleton, etc. While a CustomizableObject instance is being created for the first time, and in some situation with lots of objects this may require some seconds, the Reference Skeletal Mesh is used for the actor. This works as a better solution than the alternative of not showing anything, although this can be disabled with the function "SetReplaceDiscardedWithReferenceMeshEnabled" (See the c++ section).

#### enum `ECustomizableObjectVersions`  
`enum class ECustomizableObjectVersions : int32`  
_L1006-1362_
- reflection: `UENUM()`
- desc: This is a manual version number for the binary blobs in this asset. Increasing it invalidates all the previously compiled models.
- L1008 _public enumerator_ `FirstEnumeratedVersion = 450`
- L1010 _public enumerator_ `DeterminisiticMeshVertexIds`
- L1012 _public enumerator_ `NumRuntimeReferencedTextures`
- L1014 _public enumerator_ `DeterminisiticLayoutBlockIds`
- L1016 _public enumerator_ `BackoutDeterminisiticLayoutBlockIds`
- L1018 _public enumerator_ `FixWrappingProjectorLayoutBlockId`
- L1020 _public enumerator_ `MeshReferenceSupport`
- L1022 _public enumerator_ `ImproveMemoryUsageForStreamableBlocks`
- L1024 _public enumerator_ `FixClipMeshWithMeshCrash`
- L1026 _public enumerator_ `SkeletalMeshLODSettingsSupport`
- L1028 _public enumerator_ `RemoveCustomCurve`
- L1030 _public enumerator_ `AddEditorGamePlayTags`
- L1032 _public enumerator_ `AddedParameterThumbnailsToEditor`
- L1034 _public enumerator_ `ComponentsLODsRedesign`
- L1036 _public enumerator_ `ComponentsLODsRedesign2`
- L1038 _public enumerator_ `LayoutToPOD`
- L1040 _public enumerator_ `AddedRomFlags`
- L1042 _public enumerator_ `LayoutNodeCleanup`
- L1044 _public enumerator_ `AddSurfaceAndMeshMetadata`
- L1046 _public enumerator_ `TablesPropertyNameBug`
- L1048 _public enumerator_ `DataTablesParamTrackingForCompileOnlySelected`
- L1050 _public enumerator_ `CompilationOptimizationsMeshFormat`
- L1052 _public enumerator_ `ModelStreamableBulkData`
- L1054 _public enumerator_ `LayoutBlocksAsInt32`
- L1056 _public enumerator_ `IntParameterOptionDataTable`
- L1058 _public enumerator_ `RemoveLODCountLimit`
- L1060 _public enumerator_ `IntParameterOptionDataTablePartialBackout`
- L1062 _public enumerator_ `IntParameterOptionDataTablePartialRestore`
- L1064 _public enumerator_ `CorrectlySerializeTableToParamNames`
- L1066 _public enumerator_ `AddMaterialSlotNameIndexToSurfaceMetadata`
- L1068 _public enumerator_ `NodeComponentMesh`
- L1070 _public enumerator_ `MoveEditNodesToModifiers`
- L1072 _public enumerator_ `DerivedDataCache`
- L1074 _public enumerator_ `ComponentsArray`
- L1076 _public enumerator_ `FixComponentNames`
- L1078 _public enumerator_ `AddedFaceCullStrategyToSomeOperations`
- L1080 _public enumerator_ `DDCParticipatingObjects`
- L1082 _public enumerator_ `GroupRomsBySource`
- L1084 _public enumerator_ `RemovedGroupRomsBySource`
- L1086 _public enumerator_ `ReGroupRomsBySource`
- L1088 _public enumerator_ `UIMetadataGameplayTags`
- L1090 _public enumerator_ `TransformInMeshModifier`
- L1092 _public enumerator_ `SurfaceMetadataSlotNameIndexToName`
- L1094 _public enumerator_ `BulkDataFilesNumFilesLimit`
- L1096 _public enumerator_ `RemoveModifiersHack`
- L1098 _public enumerator_ `SurfaceMetadataSerialized`
- L1100 _public enumerator_ `FixesForMeshSectionMultipleOutputs`
- L1102 _public enumerator_ `ImageParametersInServerBuilds`
- L1104 _public enumerator_ `RemovedUnnecessarySerializationVersioning`
- L1106 _public enumerator_ `AddTextureCompressionSettingCompilationInfo`
- L1108 _public enumerator_ `RestructureConstantImageData`
- L1110 _public enumerator_ `RestructureConstantMeshData`
- L1112 _public enumerator_ `RestructureRomData`
- L1114 _public enumerator_ `RestructureRomDataRemovingRomHash`
- L1116 _public enumerator_ `ModifiedRomCompiledDataSerialization`
- L1118 _public enumerator_ `ModelResourcesExtensionData`
- L1120 _public enumerator_ `LODsPerComponent`
- L1122 _public enumerator_ `LODsPerComponentTypeMismatch`
- L1124 _public enumerator_ `ImageHiResLODsUseLODGroupInfo`
- L1126 _public enumerator_ `MovedTableRowNoneGenerationToUnreal`
- L1128 _public enumerator_ `RemoveObsoletMeshInterpolateAndGeometryOp`
- L1130 _public enumerator_ `RemoveObsoleteDataTypesFromEnum`
- L1132 _public enumerator_ `ConvertModelResourcesToUObject`
- L1134 _public enumerator_ `RemoveObsoletImageGradientOp`
- L1136 _public enumerator_ `MeshReferencesExtendedForCompilation`
- L1138 _public enumerator_ `RemoveObsoleteBoolOps`
- L1140 _public enumerator_ `AddOverlayMaterials`
- L1142 _public enumerator_ `PrefetchHighQualityMipMaps`
- L1144 _public enumerator_ `AddedMeshParameterOp`
- L1146 _public enumerator_ `AddedMeshParameterOpForDDCPollution`
- L1148 _public enumerator_ `ExtendedMeshParameterArgumentsWithLODAndSection`
- L1150 _public enumerator_ `AddAssetUserDataEditor`
- L1152 _public enumerator_ `MeshDataRomSplit`
- L1154 _public enumerator_ `MeshDataRomSplitBackout`
- L1156 _public enumerator_ `MovedLODSettingsToMeshComponentNode`
- L1158 _public enumerator_ `AddedMeshPrepareLayoutOp`
- L1160 _public enumerator_ `AddedMeshIDToMeshParamOp`
- L1162 _public enumerator_ `ClothMorphMeshMetadata`
- L1164 _public enumerator_ `AddedMeshIDToMeshParamOpBackout`
- L1166 _public enumerator_ `MeshDataRomSplitSerializationFix`
- L1168 _public enumerator_ `ReaddAddedMeshIDToMeshParamOp`
- L1170 _public enumerator_ `AddConnectedChildObjectComponentsToPrepass`
- L1172 _public enumerator_ `FixMeshReusalDueToLayouts`
- L1174 _public enumerator_ `IncorrectBonePoseMerging`
- L1176 _public enumerator_ `CoreParameterUObjects`
- L1178 _public enumerator_ `MoveMeshMetadataToOperation`
- L1180 _public enumerator_ `MovePhysicsBodiesToRoms`
- L1182 _public enumerator_ `SwitchOpCompactRepresentation`
- L1184 _public enumerator_ `AddedBlockMasksToRuntimeLayouts`
- L1186 _public enumerator_ `StoreMipTailInASingleRom`
- L1188 _public enumerator_ `FixDDCCrashesAndLoadTimes`
- L1190 _public enumerator_ `CompactBindingDataStructure`
- L1192 _public enumerator_ `MorphMeshParameters`
- L1194 _public enumerator_ `MaterialParameter`
- L1196 _public enumerator_ `AddLinearTosRGB`
- L1198 _public enumerator_ `AddMaterialArgs`
- L1200 _public enumerator_ `CacheReferenceTextureSize`
- L1202 _public enumerator_ `MaterialBreak`
- L1204 _public enumerator_ `AddNodeMeshTransformWithBoneHierarchy`
- L1206 _public enumerator_ `MaterialBreakBackOutFix`
- L1208 _public enumerator_ `MaterialBreakCheckFix`
- L1210 _public enumerator_ `LazyAddressOutsideFImage`
- L1212 _public enumerator_ `EnableMeshLODStreaming`
- L1214 _public enumerator_ `DeterministicSocketsIds`
- L1216 _public enumerator_ `CompilationEarlyOutOnRepeatedParameters`
- L1218 _public enumerator_ `FixSkinWeightProfilesConversion`
- L1220 _public enumerator_ `MaterialIDMovedToArgs`
- L1222 _public enumerator_ `FixMissingLODSettings`
- L1224 _public enumerator_ `FixSocketPriority`
- L1226 _public enumerator_ `FixDefaultBehaviourAndsWithoutOperants`
- L1228 _public enumerator_ `BumpVersionDDCCrash`
- L1230 _public enumerator_ `ImageParameterConvert`
- L1232 _public enumerator_ `InstancedStructType`
- L1234 _public enumerator_ `SkeletalMeshParameter`
- L1236 _public enumerator_ `RelevantParameters`
- L1238 _public enumerator_ `DeduplicateFMaterials`
- L1240 _public enumerator_ `AddBonePosePriority`
- L1242 _public enumerator_ `RemovedMaterialLayerEncoding`
- L1244 _public enumerator_ `AddedSkeletalMeshBreakNode`
- L1246 _public enumerator_ `ReplaceSurfaceIdWithSharedSurfaceId`
- L1248 _public enumerator_ `Deduplicate_MI_CONSTANT`
- L1250 _public enumerator_ `AddOverrideMaterials`
- L1252 _public enumerator_ `TexutreParametersFormatFromReferenceTexture`
- L1254 _public enumerator_ `AddMaterialModify`
- L1256 _public enumerator_ `AddImageMultiCompose`
- L1258 _public enumerator_ `DeduplicateFMaterialsSharingPassthroughObject`
- L1260 _public enumerator_ `RemovedReuseTextures`
- L1262 _public enumerator_ `ComponentId`
- L1264 _public enumerator_ `PassthroughTexturesForBreakNodes`
- L1266 _public enumerator_ `VersionBumpBackout`
- L1268 _public enumerator_ `ComponentId2`
- L1270 _public enumerator_ `BackoutGenerateBulkFileWithDataLimit`
- L1272 _public enumerator_ `ClothCore`
- L1274 _public enumerator_ `ConvertBoneIdsToBoneNames`
- L1276 _public enumerator_ `AddLayerIndexToMatParamTextures`
- L1278 _public enumerator_ `ClothCoreSerializationIssue`
- L1280 _public enumerator_ `ClothCoreSerializationIssue2`
- L1282 _public enumerator_ `MovePhysicsAssetCore`
- L1284 _public enumerator_ `ChangedLayerIndexDataType`
- L1286 _public enumerator_ `MutableSkeletonToPassthroughObject`
- L1288 _public enumerator_ `UseCompressedMorphsForAllMorphData`
- L1290 _public enumerator_ `TestMoveSocketsToCore`
- L1292 _public enumerator_ `RemoveMorphTarget`
- L1294 _public enumerator_ `AssetUserDataPassthroughObject2`
- L1296 _public enumerator_ `NewProgramAddressFormat`
- L1298 _public enumerator_ `IS_SWITCH`
- L1300 _public enumerator_ `SkeletalMeshConditionalSwitch`
- L1302 _public enumerator_ `GenerateSkeletalMesh`
- L1304 _public enumerator_ `SourceImageNoMipmapsSettingPreserve`
- L1306 _public enumerator_ `MaterialSlotNameToCore`
- L1308 _public enumerator_ `GenerateMutableSourceSkeletalMesh`
- L1310 _public enumerator_ `AddSkeletalMeshMorphAndSkeletalMaterialModifyOps`
- L1312 _public enumerator_ `FixSkeletalMeshParameterNotWorking`
- L1314 _public enumerator_ `AddSkeletalMeshMergeV1`
- L1316 _public enumerator_ `SK_CLIPMESHWITHMESH`
- L1318 _public enumerator_ `SKO_CONVERT`
- L1320 _public enumerator_ `SKO_CONVERTBackout`
- L1322 _public enumerator_ `SKO_CONVERTRestore`
- L1324 _public enumerator_ `SK_TRANSFORM`
- L1326 _public enumerator_ `SK_TRANSFORMWITHBONE`
- L1328 _public enumerator_ `SurfaceModifiers`
- L1330 _public enumerator_ `MultipleMeshesPerLOD`
- L1332 _public enumerator_ `SK_CONVERT`
- L1334 _public enumerator_ `MI_SKELETALMESHOBJECT_BREAK`
- L1336 _public enumerator_ `ReshapeMorphInvertedSelection`
- L1338 _public enumerator_ `RemovedMorphReshapeOp`
- L1340 _public enumerator_ `RemoveSurfaceMetadata`
- L1342 _public enumerator_ `SK_RESHAPE`
- L1344 _public enumerator_ `SkinWeightProfilesCore`
- L1346 _public enumerator_ `MaterialModifyIssues`
- L1348 _public enumerator_ `FixMinQualityLODLevels`
- L1350 _public enumerator_ `AddedClothAssetLODIndexMetadata`
- L1352 _public enumerator_ `AddedMacroContextToSKMNodeKey`
- L1354 _public enumerator_ `RemoveMeshFormatInProjectors`
- L1356 _public enumerator_ `AddedSKMMakeNodesInReshapeOps`
- L1358 _public enumerator_ `IM_CONFORM`
- L1361 _public enumerator_ `LastCustomizableObjectVersion` — -----<new versions can be added above this line>--------

#### class `UCustomizableObjectPrivate`  
`class UCustomizableObjectPrivate : public UObject`  
_L1367-1620_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L1371 _private member_ `TSharedPtr<UE::Mutable::Private::FModel, ESPMode::ThreadSafe> MutableModel;`
- L1375 _private member_ `TObjectPtr<UModelStreamableData> ModelStreamableData;` — `UPROPERTY()` — Stores streamable data info to be used by MutableModel In-Game. Cooked resources.
- L1379 _private member_ `TObjectPtr<UModelResources> ModelResources;` — `UPROPERTY()` — Stores resources to be used by MutableModel In-Game. Cooked resources.
- L1387 _private member_ `TObjectPtr<UModelResources> ModelResourcesEditor;` — `UPROPERTY(Transient)` — Stores resources to be used by MutableModel in the Editor. Editor resources. Editor-Only to avoid packaging assets referenced by editor compilations.
- L1392 _private member_ `TSharedPtr<FModelStreamableBulkData> ModelStreamableDataEditor;` — Stores streamable data info to be used by MutableModel in the Editor. Editor streaming.
- L1397 _public prototype_ `virtual void PostLoad() override;` — UObject interface
- L1400 _public prototype_ `void SetModel(const TSharedPtr<UE::Mutable::Private::FModel>& Model, const FGuid Identifier, bool bIsCooking);` — Must be called after unlocking the CustomizableObject.
- L1401 _public prototype_ `const TSharedPtr<UE::Mutable::Private::FModel>& GetModel();`
- L1402 _public prototype_ `const TSharedPtr<const UE::Mutable::Private::FModel> GetModel() const;`
- L1404 _public prototype_ `UModelResources* GetModelResources();`
- L1405 _public prototype_ `const UModelResources* GetModelResources() const;`
- L1406 _public prototype_ `UModelResources& GetModelResourcesChecked();`
- L1407 _public prototype_ `const UModelResources& GetModelResourcesChecked() const;`
- L1411 _public prototype_ `UModelResources* GetModelResources(bool bIsCooking);`
- L1412 _public prototype_ `const UModelResources* GetModelResources(bool bIsCooking) const;`
- L1414 _public prototype_ `void SetModelResources(UModelResources* InModelResources, bool bIsCooking);`
- L1415 _public prototype_ `void SetModelStreamableBulkData(const TSharedPtr<FModelStreamableBulkData>& StreamableData, bool bIsCooking);`
- L1418 _public prototype_ `TSharedPtr<FModelStreamableBulkData> GetModelStreamableBulkData(bool bIsCooking = false) const;`
- L1421 _public prototype_ `bool IsLocked() const;` — See UCustomizableObjectSystem::LockObject()
- L1424 _public prototype_ `void ApplyStateForcedValuesToParameters(FCustomizableObjectInstanceDescriptor& Descriptor);` — Modify the provided mutable parameters so that the forced values for the given customizable object state are applied.
- L1426 _public prototype_ `int32 FindParameter(const FString& Name) const;`
- L1427 _public prototype_ `int32 FindParameterTyped(const FString& Name, EMutableParameterType Type) const;`
- L1429 _public prototype_ `EMutableParameterType GetParameterType(int32 ParamIndex) const;`
- L1431 _public prototype_ `int32 FindIntParameterValue(int32 ParamIndex, const FString& Value) const;`
- L1433 _public prototype_ `FString GetStateName(int32 StateIndex) const;`
- L1436 _public prototype_ `void PostCompile();`
- L1439 _public prototype_ `UCustomizableObject* GetPublic() const;`
- L1444 _public prototype_ `FString GetCompiledDataFileName(const ITargetPlatform* InTargetPlatform = nullptr, bool bIsDiskStreamer = false) const;` — Compose file name.
- L1447 _public prototype_ `TArray<uint8> BuildDerivedDataKey(FCompilationOptions Options);` — DDC helpers. BuildDerivedDataKey is expensive, try to cache it as much as possible.
- L1448 _public prototype_ `UE::DerivedData::FCacheKey GetDerivedDataCacheKeyForOptions(FCompilationOptions InOptions);`
- L1451 _public prototype_ `void LogMemory();` — Log data for debugging purposes
- L1455 _public prototype_ `void UpdateParameterPropertiesFromModel(const TSharedPtr<UE::Mutable::Private::FModel>& Model);` — Rebuild ParameterProperties from the current compiled model.
- L1457 _public prototype_ `void AddUncompiledCOWarning(const FString& AdditionalLoggingInfo);`
- L1461 _public prototype_ `void UpdateVersionId();` — Create new GUID for this CO
- L1463 _public prototype_ `FGuid GetVersionId() const;`
- L1465 _public prototype_ `void SaveEmbeddedData(FArchive& Ar);`
- L1468 _public prototype_ `void UpdateDataDistributionId();` — Regenerate the DataDistributionId. Used to keep the same cooked data distribution between builds.
- L1471 _public prototype_ `bool LoadModelResources(FArchive& Ar, const ITargetPlatform* InTargetPlatform, bool bSkipEditorOnlyData = false);` — Generic Load methods to read compiled data
- L1472 _public prototype_ `void LoadModelStreamableBulk(FArchive& Ar, bool bIsCooking);`
- L1473 _public prototype_ `void LoadModel(FArchive& Ar, bool bIsCooking);`
- L1476 _public prototype_ `void LoadCompiledDataFromDisk();` — Load compiled data for the running platform from disk, this is used to load Editor Compilations.
- L1481 _public prototype_ `bool TryLoadCompiledCookDataForPlatform(const ITargetPlatform* TargetPlatform);` — Loads data previously compiled in BeginCacheForCookedPlatformData onto the UProperties in *this, in preparation for saving the cooked package for *this or for a CustomizableObjectInstance using *this. Returns whether the data was successfully loaded.
- L1485 _public prototype_ `void LoadEmbeddedData(FArchive& Ar);` — Data that may be stored in the asset itself, only in packaged builds.
- L1488 _public prototype_ `bool TryUpdateIsChildObject();` — Compute bIsChildObject if currently possible to do so. Return whether it was computed.
- L1490 _public prototype_ `void SetIsChildObject(bool bIsChildObject);`
- L1494 _public prototype_ `bool IsCompilationOutOfDate(bool bSkipIndirectReferences, TArray<FName>& OutOfDatePackages, TArray<FName>& AddedPackages, TArray<FName>& RemovedPackages, bool& bReleaseVersionDiff) const;` — See ICustomizableObjectEditorModule::IsCompilationOutOfDate.
- L1497 _public prototype_ `TArray<FString>& GetCustomizableObjectClassTags();`
- L1499 _public prototype_ `TArray<FString>& GetPopulationClassTags();`
- L1501 _public prototype_ `TMap<FString, FParameterTags>& GetCustomizableObjectParametersTags();`
- L1504 _public prototype_ `TObjectPtr<UEdGraph>& GetSource() const;`
- L1507 _public prototype_ `void BackwardsCompatibleFixup(int32 CustomizableObjectCustomVersion);`
- L1509 _public prototype_ `FName GetComponentName(UE::Mutable::Private::FComponentId ComponentId) const;`
- L1512 _public prototype_ `EMutableCompileMeshType GetMeshCompileType() const;`
- L1514 _public prototype_ `const TArray<TSoftObjectPtr<UCustomizableObject>>& GetWorkingSet() const;`
- L1516 _public prototype_ `bool IsTableMaterialsParentCheckDisabled() const;`
- L1518 _public prototype_ `bool IsRealTimeMorphTargetsEnabled() const;`
- L1520 _public prototype_ `bool Is16BitBoneWeightsEnabled() const;`
- L1522 _public prototype_ `bool IsAltSkinWeightProfilesEnabled() const;`
- L1524 _public prototype_ `bool IsPhysicsAssetMergeEnabled() const;`
- L1526 _public prototype_ `bool ShouldUseLegacyLayouts() const;`
- L1528 _public prototype_ `bool IsEnabledAnimBpPhysicsAssetsManipulation() const;`
- L1531 _public prototype_ `const FString& GetIntParameterAvailableOption(int32 ParamIndex, int32 K) const;`
- L1533 _public prototype_ `int32 GetEnumParameterNumValues(int32 ParamIndex) const;`
- L1535 _public prototype_ `FString FindIntParameterValueName(int32 ParamIndex, int32 ParamValue) const;`
- L1537 _public prototype_ `int32 FindState(const FString& Name) const;`
- L1539 _public prototype_ `int32 GetStateParameterIndex(int32 StateIndex, int32 ParameterIndex) const;`
- L1541 _public prototype_ `bool IsParameterMultidimensional(const int32& InParamIndex) const;`
- L1544 _public member_ `FSkeletalMeshCache SkeletalMeshCache;` — Cache of generated Skeletal Meshes. Only takes into account geometry. Materials may be different. Passthrough Skeletal Meshes are not contemplated.
- L1547 _public member_ `FTextureCache TextureCache;` — Cache of generated Textures. Passthrough Textures are not contemplated.
- L1550 _public member_ `FSkeletonCache SkeletonCache;` — Cache of merged Skeletons
- L1552 _public member_ `TSharedRef<UE::Mutable::Private::FImageIdRegistry> ImageIdRegistry = MakeShared<UE::Mutable::Private::FImageIdRegistry>();`
- L1554 _public member_ `TSharedRef<UE::Mutable::Private::FMaterialIdRegistry> MaterialIdRegistry = MakeShared<UE::Mutable::Private::FMaterialIdRegistry>();`
- L1556 _public member_ `TSharedRef<UE::Mutable::Private::FSkeletalMeshIdRegistry> SkeletalMeshIdRegistry = MakeShared<UE::Mutable::Private::FSkeletalMeshIdRegistry>();`
- L1558 _public member_ `TSharedPtr<UE::Mutable::Private::FModel> SerializedModel;`
- L1561 _public member_ `bool bLocked = false;` — See UCustomizableObjectSystem::LockObject. Must only be modified from the game thread
- L1566 _public member_ `TArray<FMutableMeshComponentData> MutableMeshComponents_DEPRECATED;` — `UPROPERTY()`
- L1569 _public member_ `FGuid Identifier;` — Unique Identifier - Deterministic. Used to locate Model and Streamable data on disk. Should not be modified.
- L1571 _public member_ `ECompilationResultPrivate CompilationResult = ECompilationResultPrivate::Unknown;`
- L1573 _public member_ `FPostCompileDelegate PostCompileDelegate;`
- L1576 _public member_ `TMap<FString, UE::Mutable::Private::FMutableCachedPlatformData> CachedPlatformsData;` — Map of PlatformName to CachedPlatformData. Only valid while cooking.
- L1580 _public member_ `FCustomizableObjectStatus Status;`
- L1584 _public member_ `TArray<FMutableModelParameterProperties> ParameterProperties;` — `UPROPERTY(Transient)` — This is information about the parameters in the model that is generated at model compile time.
- L1588 _public member_ `TObjectPtr<UModelResources> ReferencedObjects;` — `UPROPERTY()` — Reference to all UObject used in game. Only updated during the compilation if the user explicitly wants to save all references.
- L1592 _public member_ `TMap<FString, FMutableParameterIndex> ParameterPropertiesLookupTable;` — Map of name to index of ParameterProperties. use this to lookup fast by Name
- L1596 _public member_ `ECustomizableObjectTextureCompression TextureCompression = ECustomizableObjectTextureCompression::Fast;` — `UPROPERTY()`
- L1600 _public member_ `int32 OptimizationLevel = UE_MUTABLE_MAX_OPTIMIZATION;` — `UPROPERTY()` — From 0 to UE_MUTABLE_MAX_OPTIMIZATION
- L1605 _public member_ `uint64 EmbeddedDataBytesLimit = 1024;` — `UPROPERTY()` — High (inclusive) limit of the size in bytes of a data block to be included into the compiled object directly instead of stored in a streamable file.
- L1608 _public member_ `bool bDisableTableMissingDataWarning = false;` — `UPROPERTY()`
- L1613 _public member_ `FGuid CookedDataDistributionId;` — `UPROPERTY()` — Used to keep the same cooked data distribution between builds. This Id is part of the DDC key of the cooked data distribution.
- L1617 _public member_ `TSharedPtr<class IMutableEditorLogger> CompilationLogger;` — Editor Log list to print all the messages related to this CO.
- L1619 _public member_ `static constexpr int32 DerivedDataVersion = 0x2850e5a1;`

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Mutable` (scope `UE`)
- L26 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace Mutable` (scope `UE`)
- L32 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L37 _namespace_ `namespace UE`
- L37 _namespace_ `namespace DerivedData` (scope `UE`)
- L60 _prototype_ `FGuid GenerateIdentifier(const UCustomizableObject& CustomizableObject);`
- L62 _prototype_ `FString GetModelResourcesNameForPlatform(const UCustomizableObject& CustomizableObject, const ITargetPlatform& Platform);`
- L66 _prototype_ `FGuid GenerateDataDistributionIdentifier(const UCustomizableObject& CustomizableObject);`
- L79 _function_ `friend FArchive& operator<<(FArchive& Ar, MutableCompiledDataStreamHeader& Header)`
- L225 _typedef_ `using FCustomizableObjectStatus = FStateMachine<FCustomizableObjectStatusTypes>;`
- L428 _function_ `friend FArchive& operator<<(FArchive& Ar, FMutableStreamableBlock& Data)`
- L563 _namespace_ `namespace UE`
- L563 _namespace_ `namespace Mutable` (scope `UE`)
- L563 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L590 _function_ `friend FArchive& operator<<(FArchive& Ar, FBlock& Data)` (scope `UE::Mutable::Private`)
- L626 _function_ `friend FArchive& operator<<(FArchive& Ar, FFile& Data)` (scope `UE::Mutable::Private`)
- L654 _function_ `friend FArchive& operator<<(FArchive& Ar, FFileCategoryID& Data)` (scope `UE::Mutable::Private`)
- L747 _prototype_ `void GenerateBulkDataFilesListWithFileLimit( FGuid ObjectId, TSharedPtr<const UE::Mutable::Private::FModel, ESPMode::ThreadSafe> Model, FModelStreamableBulkData& ModelStreamableBulkData, uint32 NumFilesPerBucket, bool bAllowFileCategoryOverride, bool bAllowSplit, const ITargetPlatform& TargetPlatform, TArray<FFile>& OutBulkDataFiles);` (scope `UE::Mutable::Private`) — Generate the list of BulkData files with a restriction to the number of files to generate per bucket. Resources will be split into two buckets for non-optional and optional BulkData.
- L759 _prototype_ `void GenerateBulkDataFilesListWithSizeLimit( TSharedPtr<const UE::Mutable::Private::FModel, ESPMode::ThreadSafe> Model, FModelStreamableBulkData& ModelStreamableBulkData, const ITargetPlatform* TargetPlatform, uint64 TargetBulkDataFileBytes, TArray<FFile>& OutBulkDataFiles);` (scope `UE::Mutable::Private`) — Generate the list of BulkData files with a soft restriction to the size of the files.
- L769 _prototype_ `void GenerateBulkDataFilesList( TSharedPtr<const UE::Mutable::Private::FModel, ESPMode::ThreadSafe> Model, FModelStreamableBulkData& StreamableBulkData, bool bUseRomTypeAndFlagsToFilter, TFunctionRef<void(const FFileCategoryID&, const FClassifyNode&, TArray<FFile>&)> CreateFileList, TArray<FFile>& OutBulkDataFiles);` (scope `UE::Mutable::Private`) — Compute the number of files and sizes the BulkData will be split into and update the streamable's FileIds and Offsets.
- L776 _prototype_ `void SerializeBulkDataFiles( FMutableCachedPlatformData& CachedPlatformData, TArray<FFile>& BulkDataFiles, TFunctionRef<void(FFile&, TArray64<uint8>&, uint32 FileIndex)> WriteFile, bool bDropData);` (scope `UE::Mutable::Private`)
- L782 _prototype_ `UE::DerivedData::FValueId GetDerivedDataModelId();` (scope `UE::Mutable::Private`)
- L783 _prototype_ `UE::DerivedData::FValueId GetDerivedDataModelResourcesId();` (scope `UE::Mutable::Private`)
- L784 _prototype_ `UE::DerivedData::FValueId GetDerivedDataModelStreamableBulkDataId();` (scope `UE::Mutable::Private`)
- L785 _prototype_ `UE::DerivedData::FValueId GetDerivedDataBulkDataFilesId();` (scope `UE::Mutable::Private`)
- L811 _function_ `friend FArchive& operator<<(FArchive& Ar, FModelStreamableBulkData& Data)`
- L1628 _prototype_ `UE::DerivedData::FValueId GetDerivedDataValueIdForResource(UE::Mutable::Private::EStreamableDataType StreamableDataType, uint32 FileId, uint16 ResourceType, uint16 Flags);` — Returns the DDC ValueId of the file owning a streamable resource. @ param StreamableDataType - UE level data type @ param ResourceType - UE::Mutable::Private::EDataType
- L1631 _prototype_ `FString GetCompiledDataFolderPath();` — Compose folder name where the data is stored
- L1632 _prototype_ `FString GetDataTypeExtension(UE::Mutable::Private::EStreamableDataType DataType);`
- L1634 _prototype_ `uint32 GetECustomizableObjectVersionEnumHash();`
- L1636 _prototype_ `TObjectPtr<UModelResources> LoadModelResources_Internal(FArchive& Ar, const UCustomizableObject* Outer, const ITargetPlatform* InTargetPlatform, bool bSkipEditorOnlyData = false);`
- L1637 _prototype_ `const TSharedPtr<FModelStreamableBulkData> LoadModelStreamableBulk_Internal(FArchive& Ar);`
- L1638 _prototype_ `const TSharedPtr<UE::Mutable::Private::FModel, ESPMode::ThreadSafe> LoadModel_Internal(FArchive& Ar);`

### `Plugins/Mutable/Source/CustomizableObject/Internal/MuCO/CustomizableObjectSystemPrivate.h` (Internal)


#### struct `FMutableImageReference`  
`struct FMutableImageReference`  
_L52-59_
- desc: Key to identify an image inside a generated mutable runtime instance.
- L54 _public member_ `UE::Mutable::Private::FImageId ImageID;`
- L56 _public member_ `uint8 BaseMip = 0;`
- L58 _public member_ `TArray<int32> ConstantImagesNeededToGenerate;`

#### struct `FSkeletalMeshMorphTargets`  
`struct FSkeletalMeshMorphTargets`  
_L77-84_
- desc: Final data per component.
- L80 _public member_ `TArray<FName> RealTimeMorphTargetNames;` — Name of the Morph Target.
- L83 _public member_ `TArray<TArray<FMorphTargetLODModel>> RealTimeMorphsLODData;` — First index is the Morph Target (in sync with RealTimeMorphTargetNames). Second index is the LOD.

#### struct `FInstanceUpdateData`  
`struct FInstanceUpdateData`  
_L89-224_
- desc: Mutable data generated during the update steps. We keep it from begin to end update, and it is used in several steps.
- L197 _public member_ `TArray<TSharedRef<FComponent>> Components;`
- L198 _public member_ `TArray<TSharedRef<FLOD>> LODs;`
- L199 _public member_ `TArray<FOverrideMaterial> OverrideMaterials;`
- L200 _public member_ `TArray<FOverlayMaterial> OverlayMaterials;`
- L201 _public member_ `TArray<TSharedRef<FMaterial>> Materials;`
- L202 _public member_ `TArray<TSharedRef<FSurface>> Surfaces;`
- L203 _public member_ `TArray<TSharedRef<FImage>> Images;`
- L205 _public member_ `TArray<FName> ActiveBones;`
- L206 _public member_ `TArray<FName> BoneMaps;`
- L210 _public member_ `TMap<UE::Mutable::Private::FComponentId, FSkeletalMeshMorphTargets> RealTimeMorphTargets;` — Key is the Component Name. Value is the final Morph Target data to copy into the Skeletal Mesh.
- L213 _public function_ `void Clear()`

#### struct `FInstanceUpdateData::FImage`  
`struct FImage`  
_L91-114_
- L93 _public member_ `FName ParameterName;` — TODO MATERIAL_PIN This does not belong to the Image but the Material
- L94 _public member_ `UE::Mutable::Private::FImageId ImageID;`
- L97 _public member_ `int32 BaseMip;` — LOD of the ImageId.
- L99 _public member_ `uint16 FullImageSizeX;`
- L100 _public member_ `uint16 FullImageSizeY;`
- L102 _public member_ `UE::Mutable::Private::EImageFormat Format = UE::Mutable::Private::EImageFormat::None;`
- L104 _public member_ `UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FImage> Image;`
- L106 _public member_ `TArray<int32> ConstantImagesNeededToGenerate;`
- L108 _public member_ `int32 ImagePropertiesIndex = INDEX_NONE;` — TODO MATERIAL_PIN This does not belong to the Image but the Material
- L110 _public member_ `bool bIsPassThrough = false;`
- L111 _public member_ `bool bIsNonProgressive = false;`
- L113 _public member_ `int32 MaterialLayer = INDEX_NONE;` — TODO MATERIAL_PIN This does not belong to the Image but the Material

#### struct `FInstanceUpdateData::FMaterial`  
`struct FMaterial`  
_L116-124_
- L119 _public member_ `uint16 FirstImage = 0;` — Range in the Images array
- L120 _public member_ `uint16 ImageCount = 0;`
- L122 _public member_ `UE::Mutable::Private::FMaterialId MaterialId;`
- L123 _public member_ `UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FMaterial> Material;`

#### struct `FInstanceUpdateData::FSurface`  
`struct FSurface`  
_L126-134_
- L129 _public member_ `uint32 SurfaceId = 0;` — Id of the surface in the mutable core instance.
- L131 _public member_ `FName MaterialSlotName;`
- L133 _public member_ `uint32 MaterialIndex = INDEX_NONE;`

#### struct `FInstanceUpdateData::FLOD`  
`struct FLOD`  
_L136-151_
- L138 _public member_ `UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FMesh> Mesh;`
- L141 _public member_ `uint16 FirstSurface = 0;` — Range in the Surfaces array
- L142 _public member_ `uint16 SurfaceCount = 0;`
- L145 _public member_ `uint32 FirstActiveBone = 0;` — Range in the external Bones array
- L146 _public member_ `uint32 ActiveBoneCount = 0;`
- L149 _public member_ `uint32 FirstBoneMap = 0;` — Range in the external Bones array
- L150 _public member_ `uint32 BoneMapCount = 0;`

#### struct `FInstanceUpdateData::FOverrideMaterial`  
`struct FOverrideMaterial`  
_L153-158_
- L155 _public member_ `FName SlotName;`
- L157 _public member_ `uint32 MaterialIndex = INDEX_NONE;`

#### struct `FInstanceUpdateData::FOverlayMaterial`  
`struct FOverlayMaterial`  
_L160-165_
- L162 _public member_ `FName SlotName;`
- L164 _public member_ `uint32 MaterialIndex = INDEX_NONE;`

#### struct `FInstanceUpdateData::FBone`  
`struct FBone`  
_L167-173_
- L169 _public member_ `FName BoneName;`
- L170 _public member_ `FMatrix44f MatrixWithScale;`
- L172 _public function_ `bool operator==(const FName& OtherBoneName) const`

#### struct `FInstanceUpdateData::FComponent`  
`struct FComponent`  
_L175-195_
- L177 _public member_ `UE::Mutable::Private::FComponentId Id = INDEX_NONE;`
- L180 _public member_ `uint16 FirstLOD = 0;` — Range in the LODs array
- L181 _public member_ `uint16 LODCount = 0;`
- L183 _public member_ `uint16 FirstOverrideMaterial = 0;`
- L184 _public member_ `uint16 OverrideMaterialCount = 0;`
- L186 _public member_ `uint16 FirstOverlayMaterial = 0;`
- L187 _public member_ `uint16 OverlayMaterialCount = 0;`
- L189 _public member_ `uint32 OverlayMaterialIndex = INDEX_NONE;`
- L191 _public member_ `UE::Mutable::Private::FSkeletalMeshId SkeletalMeshId;`
- L192 _public member_ `UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FSkeletalMesh> SkeletalMesh;`
- L194 _public member_ `TArray<FBone> BonePose;`

#### class `FUpdateContextPrivate`  
`class FUpdateContextPrivate`  
_L230-387_
- desc: Update Context. Alive from the start to the end of the update (both API and LOD update).
- L233 _public prototype_ `void Init(bool bUseCommitedDescriptor);`
- L235 _public prototype_ `const FCustomizableObjectInstanceDescriptor& GetCapturedDescriptor() const;`
- L237 _public prototype_ `const FDescriptorHash& GetCapturedDescriptorHash() const;`
- L239 _public prototype_ `const FCustomizableObjectInstanceDescriptor&& MoveCommittedDescriptor();`
- L241 _public member_ `UE::Mutable::Private::FImageOperator::FImagePixelFormatFunc PixelFormatOverride;`
- L243 _public member_ `FInstanceUpdateData InstanceUpdateData;`
- L247 _private member_ `FCustomizableObjectInstanceDescriptor CapturedDescriptor;` — Descriptor which the update will be performed on.
- L250 _private member_ `FDescriptorHash CapturedDescriptorHash;` — Hash of the descriptor.
- L253 _public member_ `TArray<uint32> RelevantParameters;`
- L256 _public member_ `TArray<TStrongObjectPtr<const UObject>> Objects;` — Hard references to objects. Avoids GC to collect them.
- L260 _public member_ `TArray<TStrongObjectPtr<const UTexture>> LoadedPassThroughTexturesPendingSetMaterial;` — Used during an update to prevent the pass-through textures loaded by LoadAdditionalAssetsAsync() from being unloaded by GC between AdditionalAssetsAsyncLoaded() and their setting into the generated materials in BuildResources()
- L263 _public member_ `TArray<UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FExtensionData>> ExtensionData;`
- L268 _public member_ `TArray<bool> MeshChangedPerInstanceComponent;` — Used to know if the updated instances' meshes are different from the previous ones. The index of the array is the instance component's index. @return true if the mesh is new or new to this instance (e.g. mesh cached by another instance).
- L271 _public member_ `TArray<FName> ComponentNames;` — List of component names. Key is the FComponentId.
- L274 _public member_ `TMap<UE::Mutable::Private::FMaterialId, TStrongObjectPtr<UMaterialInterface>> MaterialUpdateCache;` — Materials already build in this update.
- L277 _public member_ `TMap<FTextureCache::FId, TStrongObjectPtr<UTexture>> TextureUpdateCache;` — Textures already build in this update.
- L280 _public member_ `TMap<FName, uint8> FirstLODAvailable;` — Calculated at runtime.
- L283 _public member_ `TMap<FName, uint8> NumLODsAvailable;` — Calculated at runtime.
- L286 _public member_ `TMap<FName, uint8> FirstResidentLOD;` — Calculated at runtime.
- L288 _public member_ `TMap<UE::Mutable::Private::FImageId, TUniquePtr<FTexturePlatformData>> ImageToPlatformDataMap;`
- L291 _public member_ `TArray<UCustomizableObjectInstanceUsage*> AttachedParentUpdated;` — If a InstanceUsage is in this array it means that its AttachParent has been modified (USkeletalMesh changed, UMaterial changed...).
- L293 _public member_ `FInstanceUpdateDelegate UpdateCallback;`
- L294 _public member_ `FInstanceUpdateNativeDelegate UpdateNativeCallback;`
- L296 _public member_ `UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FInstance> MutableInstance;`
- L299 _public member_ `TSharedPtr<UE::Mutable::Private::FParameters> Parameters;` — Instance parameters at the time of the operation request.
- L300 _public member_ `TSharedPtr<UE::Mutable::Private::FSystem> MutableSystem;`
- L301 _public member_ `TSharedPtr<UE::Mutable::Private::FModel> Model;`
- L303 _public member_ `TSharedPtr<UE::Mutable::Private::FLiveInstance> LiveInstance;`
- L305 _public member_ `TSharedPtr<FUnrealMutableResourceProvider> ExternalResourceProvider;`
- L307 _public member_ `TSharedPtr<FMutableUpdateImageContext> UpdateImageContext;`
- L310 _public member_ `TSharedPtr<UE::Mutable::Private::FPassthroughObjectLoader> PassthroughObjectLoader;` — Manage loading Passthrough Objects discovered on the StartUpdate.
- L314 _public member_ `TWeakObjectPtr<UCustomizableObjectInstance> Instance;` — Weak reference to the instance we are operating on. It is weak because we don't want to lock it in case it becomes irrelevant in the game while operations are pending and it needs to be destroyed.
- L317 _public member_ `TWeakObjectPtr<UCustomizableObject> Object;` — Customizable Object we are operating on. It can be destroyed between Game Thread tasks.
- L320 _public member_ `double StartQueueTime = 0.0;` — Update stats
- L321 _public member_ `double QueueTime = 0.0;`
- L323 _public member_ `double StartUpdateTime = 0.0;`
- L324 _public member_ `double UpdateTime = 0.0;`
- L326 _public member_ `double TaskGetMeshesTimeStart = 0.0;`
- L327 _public member_ `double TaskGetMeshesTime = 0.0;`
- L328 _public member_ `double TaskGetImagesTimeStart = 0.0;`
- L329 _public member_ `double TaskGetImagesTime = 0.0;`
- L330 _public member_ `double TaskConvertResourcesTime = 0.0;`
- L331 _public member_ `double TaskCallbacksTime = 0.0;`
- L334 _public member_ `int64 UpdateStartBytes = 0;` — Update Memory stats
- L336 _public member_ `int64 UpdateEndPeakBytes = 0;`
- L338 _public member_ `int64 UpdateEndRealPeakBytes = 0;`
- L341 _public member_ `int32 MipsToSkip = 0;` — This option comes from the operation request. It is used to reduce the number of mipmaps that mutable must generate for images.
- L343 _public member_ `EUpdateResult UpdateResult = EUpdateResult::Success;`
- L346 _public member_ `uint8 bNeverStreamMips : 1 = false;` — This option comes from the operation request
- L349 _public member_ `uint8 bLiveUpdateMode : 1 = false;` — When this option is enabled it will reuse the Mutable core instance and its temp data between updates.
- L351 _public member_ `uint8 bUseResueTextureCache : 1 = false;`
- L353 _public member_ `uint8 bUseSkeletalMeshCache : 1 = false;`
- L355 _public member_ `uint8 bUseCaches : 1 = true;`
- L358 _public member_ `uint8 bStreamMeshLODs : 1 = false;` — Whether the mesh to generate should support Mesh LOD streaming or not.
- L361 _public member_ `uint8 bLowPriorityTasksBlocked : 1 = false;` — true if the Update has blocked Low Priority Tasks from launching.
- L364 _public member_ `uint8 bIsHighPriority : 1 = false;` — Add to the high priority queue or not
- L367 _public member_ `uint8 bForce : 1= false;` — Do not optimize the update.
- L370 _public member_ `uint8 bBake : 1 = false;` — Update due to a bake.
- L372 _public member_ `uint8 bIsUpdateAborted : 1 = false;`
- L374 _public member_ `uint8 bKeepOwnershipOfGeneratedResources : 1 = false;`
- L376 _public member_ `uint8 UpdateStarted : 1 = false;`
- L378 _public member_ `uint8 bLevelBegunPlay : 1 = false;`
- L381 _public member_ `uint8 bOptimizedUpdate : 1 = false;` — true if the update has been optimized (skips all Tasks and calls FinishUpdateGlobal directly on the Enqueue).
- L386 _public member_ `bool bClearCacheLayer1 = false;` — Determines if the Cachelayer1 (locked and unlocked data) should be cleared or not during the execution of the BeginUpdate_MutableThread. It is only useful during the initial generation as we do not need to consider clearing the layer one during LOD or MIP generation

#### enum `ECustomizableObjectDDCPolicy`  
`enum class ECustomizableObjectDDCPolicy : uint8`  
_L395-400_
- reflection: `UENUM()`
- L397 _public enumerator_ `None = 0`
- L398 _public enumerator_ `Local`
- L399 _public enumerator_ `Default`

#### struct `FEditorCompileSettings`  
`struct FEditorCompileSettings`  
_L404-416_
- desc: Struct used to keep a copy of the EditorSettings needed to compile Customizable Objects.
- L407 _public member_ `bool bIsMutableEnabled = true;` — General case
- L410 _public member_ `bool bEnableAutomaticCompilation = true;` — Auto Compile
- L411 _public member_ `bool bCompileObjectsSynchronously = true;`
- L414 _public member_ `ECustomizableObjectDDCPolicy EditorDerivedDataCachePolicy = ECustomizableObjectDDCPolicy::Default;` — DDC settings
- L415 _public member_ `ECustomizableObjectDDCPolicy CookDerivedDataCachePolicy = ECustomizableObjectDDCPolicy::Default;`

#### class `UCustomizableObjectSystemPrivate`  
`class UCustomizableObjectSystemPrivate : public UObject, public IStreamingManager`  
_L444-605_
- reflection: `UCLASS()`
- inherits: `UObject,IStreamingManager`
- desc: Private part, hidden from outside the plugin. UE STREAMING: [- NumLODsAvailable -----------------------------] = 8 (State and platform dependent) [- Stripped --[- Packaged -----------------------] 0      1      2      3      4      5      6      7 |------|------|------|------|------|------|------| [- Streaming --------[- Residents -] ^                    ^ |                    | FirstLODAvailable    FirstResidentLOD [- NumLODsToStream ----------------] = 5 (Compiled constant, ModelResources) NumLODsToStream = 0 DEFINITIONS: FirstLODAvailable =	    First available lod per platform.																Skeletal Mesh Component. FirstResidentLOD =       First LOD generated with geometry.																Skeletal Mesh Component.
- L450 _public member_ `static UCustomizableObjectSystem* SSystem;` — Singleton for the unreal mutable system.
- L453 _public member_ `TSharedPtr<UE::Mutable::Private::FSystem> MutableSystem;` — Pointer to the lower level mutable system that actually does the work.
- L456 _public member_ `uint64 LastWorkingMemoryBytes = 0;` — Store the last streaming memory size in bytes, to change it when it is safe.
- L459 _public member_ `TSharedPtr<class FUnrealMutableModelBulkReader> Streamer;` — This object is responsible for streaming data to the MutableSystem.
- L461 _public member_ `TDeque<FMutableInstanceUpdate> HighPriorityInstanceUpdates;`
- L462 _public member_ `TDeque<FMutableInstanceUpdate> LowPriorityInstanceUpdates;`
- L463 _public member_ `int32 PendingInstanceUpdates = 0;`
- L465 _public member_ `static int32 EnableMutableProgressiveMipStreaming;`
- L466 _public member_ `static int32 EnableMutableLiveUpdate;`
- L467 _public member_ `static int32 EnableMutableAnimInfoDebugging;`
- L468 _public member_ `static int32 MutableMeshesLODBias;`
- L469 _public member_ `static int32 MaxTextureSizeToGenerate;`
- L470 _public member_ `static bool bGenerateInstancesWithinRange;`
- L473 _public prototype_ `virtual void UpdateResourceStreaming(float DeltaTime, bool bProcessEverything = false) override;` — IStreamingManager interface
- L474 _public prototype_ `virtual int32 BlockTillAllRequestsFinished(float TimeLimit = 0.0f, bool bLogResults = false) override;`
- L475 _public function_ `virtual void CancelForcedResources() override`
- L476 _public function_ `virtual void AddLevel(ULevel* Level) override`
- L477 _public function_ `virtual void RemoveLevel(ULevel* Level) override`
- L478 _public function_ `virtual void NotifyLevelChange() override`
- L479 _public function_ `virtual void SetDisregardWorldResourcesForFrames(int32 NumFrames) override`
- L480 _public function_ `virtual void NotifyLevelOffset(ULevel* Level, const FVector& Offset) override`
- L482 _public prototype_ `void UpdateTick(bool bBlocking);`
- L484 _public prototype_ `void MainTick(bool bBlocking);`
- L486 _public prototype_ `int32 GetRemainingWork() const;`
- L488 _public prototype_ `UCustomizableObjectSystem* GetPublic() const;`
- L490 _public prototype_ `void EnqueueUpdateSkeletalMesh(const TSharedRef<FUpdateContextPrivate>& Context);`
- L492 _public member_ `TSharedPtr<FUpdateContextPrivate> CurrentMutableOperation = nullptr;`
- L495 _public member_ `FTSTicker::FDelegateHandle TickWarningsDelegateHandle;` — Handle to the registered TickDelegate.
- L499 _public prototype_ `static void OnMutableEnabledChanged(IConsoleVariable* CVar = nullptr);` — Change the current status of Mutable. Enabling/Disabling core features. Disabling Mutable will turn off compilation, generation, and streaming and will remove the system ticker.
- L502 _public prototype_ `void UpdateMemoryLimit();` — Update the last set amount of internal memory Mutable can use to build objects.
- L504 _public prototype_ `bool TryStartUpdate(const TSharedRef<FUpdateContextPrivate>& Context);`
- L505 _public prototype_ `bool TryStartAutomaticUpdateForInstance(UCustomizableObjectInstance& Instance);`
- L508 _public prototype_ `void StartUpdate(const TSharedRef<FUpdateContextPrivate>& Context);` — Start the actual work of Update Skeletal Mesh process (Update Skeletal Mesh without the queue).
- L511 _public prototype_ `bool IsUpdating(const UCustomizableObjectInstance& Instance) const;` — See UCustomizableObjectInstance::IsUpdating.
- L514 _public member_ `FMutableTaskGraph MutableTaskGraph;` — Mutable TaskGraph system (Mutable Thread).
- L517 _public member_ `UE::Tasks::FTask LastUpdateMutableTask = UE::Tasks::MakeCompletedTask<void>();` — Last Mutable task from the previous update. The next update can not start until this task has been completed.
- L519 _public member_ `FLogBenchmarkUtil LogBenchmarkUtil;`
- L521 _public member_ `bool bAutoCompileCommandletEnabled = false;`
- L524 _public prototype_ `void UpdateViewLocations();` — mutable.GenerateInstancesWithinRange = true
- L525 _public prototype_ `bool IsDiscardedByDistance(const UCustomizableObjectInstance& Instance) const;`
- L526 _public prototype_ `void DiscardInstance(UCustomizableObjectInstance& Instance);`
- L529 _public member_ `TSet<TWeakObjectPtr<const AActor>> ViewCenters;` — The list of actors that define a view radius (GenerationRange) around them.
- L530 _public member_ `TArray<FVector> ViewLocations;`
- L533 _public member_ `float GenerationRangeSquare = 2000.f * 2000.f;` — Instance generation range when mutable.GenerateInstancesWithinRange is true
- L535 _public member_ `TSharedRef<FMutableStreamableManager> StreamableManager = MakeShared<FMutableStreamableManager>();`
- L539 _public member_ `FEditorCompileSettings EditorSettings;` — Copy of the Mutable Editor Settings tied to CO compilation. They are updated whenever changed
- L544 _public member_ `TArray<FGuid> UncompiledCustomizableObjectIds;` — Array to keep track of cached objects
- L547 _public member_ `TWeakPtr<SNotificationItem> UncompiledCustomizableObjectsNotificationPtr;` — Weak pointer to the Uncompiled Customizable Objects notification
- L551 _public member_ `float LogStartedUpdateUnmute = 0.0;` — Time when the "Started Update Skeletal Mesh Async" log will be unmuted (in seconds).
- L554 _public member_ `float LogStartedUpdateLast = 0;` — Time of the last "Started Update Skeletal Mesh Async" log (in seconds).
- L558 _public function_ `static const TArray<UCustomizableObjectInstance*>& GetCustomizableObjectInstances()`
- L562 _public prototype_ `static void RegisterCustomizableObjectInstance(UCustomizableObjectInstance& Obj);`
- L563 _public prototype_ `static void UnregisterCustomizableObjectInstance(UCustomizableObjectInstance& Obj);`
- L566 _public prototype_ `static void RegisterInstanceToGeneratedList(UCustomizableObjectInstance& Obj);`
- L567 _public prototype_ `static void UnregisterInstancefromGeneratedList(UCustomizableObjectInstance& Obj);`
- L568 _public prototype_ `static void RegisterInstanceToAutomaticUpdateList(UCustomizableObjectInstance& Obj);`
- L569 _public prototype_ `static void UnregisterInstanceFromAutomaticUpdateList(UCustomizableObjectInstance& Obj);`
- L571 _public prototype_ `void TickDiscardInstances();`
- L572 _public prototype_ `void TickAutomaticUpdateInstances();`
- L574 _public prototype_ `static void RegisterInstanceToPendinSetReferenceSkeletalMeshList(UCustomizableObjectInstance& Obj);`
- L575 _public prototype_ `void TickPendingSetReferenceSkeletalMesh();`
- L582 _public prototype_ `static bool IsUsingBenchmarkingSettings();` — Get to know if the settings used by the mutable syustem are optimzed for benchmarking operations or not @return true if using benchmarking optimized settings, false otherwise.
- L588 _public prototype_ `static void SetUsageOfBenchmarkingSettings(bool bUseBenchmarkingOptimizedSettings);` — Enable or disable the usage of benchmarking optimized settings @param bUseBenchmarkingOptimizedSettings True to enable the usage of benchmarking settings, false to disable it.
- L590 _public prototype_ `void LogUpdateMessage(const FString& Message, ELogVerbosity::Type Verbosity, UCustomizableObjectInstance* Instance, bool bClearMessageList = false);`
- L594 _private member_ `inline static bool bUseBenchmarkingSettings = false;` — Flag that controls some of the settings used for the generation of instances.
- L597 _private member_ `static TArray<UCustomizableObjectInstance*> CustomizableObjectInstances;` — Added to in PostInitProperties, removed from in BeginDestroy. No CDOs
- L598 _private member_ `static TArray<UCustomizableObjectInstance*> GeneratedInstances;`
- L599 _private member_ `static TArray<UCustomizableObjectInstance*> AutomaticUpdateInstances;`
- L601 _private member_ `static TArray<UCustomizableObjectInstance*> PendingSetReferenceSkeletalMesh;`
- L603 _private member_ `int32 DiscardIndex = 0;`
- L604 _private member_ `int32 AutomaticUpdateIndex = 0;`

#### Free symbols / members of external scopes

- L32 _macro_ `#define UE_API CUSTOMIZABLEOBJECT_API`
- L41 _namespace_ `namespace LowLevelTasks`
- L45 _macro_ `#define MUTABLE_STREAMED_DATA_MAXCHUNKSIZE (512 * 1024 * 1024)` — Split StreamedBulkData into chunks smaller than MUTABLE_STREAMED_DATA_MAXCHUNKSIZE
- L48 _externvar_ `extern TAutoConsoleVariable<bool> CVarMutableHighPriorityLoading;`
- L67 _prototype_ `void ReconstructMorphTargetsFromMeshCompressedData(const UE::Mutable::Private::FMesh& Mesh, TArray<FMorphTargetLODModel>& OutMorphTargets, UE::Mutable::Private::EMorphUsageFlags UsageFilter);` — Reconstruct the final Morph Targets using the mesh compressed morphs. @param Mesh Mesh containing the compressed data. @param OutMorphTargets Resulting Morph Targets LOD models filtered by usage. @param UsageFilter Usage filter applied to the OutMorphTargets.
- L70 _prototype_ `void ReconstructMorphTargetsFromMeshCompressedData(const UE::Mutable::Private::FMesh& Mesh, TArray<FMorphTargetCompressedLODModel>& OutMorphTargets, UE::Mutable::Private::EMorphUsageFlags UsageFilter);`
- L73 _prototype_ `void FinishUpdateGlobal(const TSharedRef<FUpdateContextPrivate>& Context);` — End a Customizable Object Instance Update. All code paths of an update have to end here.
- L390 _typedef_ `typedef TSharedPtr<FUpdateContextPrivate> FMutableInstanceUpdate;`
- L609 _prototype_ `TUniquePtr<FTexturePlatformData> MutableCreateImagePlatformData(UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FImage> MutableImage, int32 OnlyLOD, uint16 FullSizeX, uint16 FullSizeY);` — Set OnlyLOD to -1 to generate all mips
- L613 _prototype_ `bool IsStreamingEnabled(const UCustomizableObject& Object, int32 State);` — Return true if Streaming is enabled for the given Object.
- L617 _function_ `template<typename Type> Type* ToObject(const FString& Parameter)`
- L622 _function_ `template<typename Type> Type* ToObject(const FName& Parameter)`

### `Plugins/Mutable/Source/CustomizableObject/Internal/MuCO/CustomizableSkeletalComponentPrivate.h` (Internal)


#### class `UCustomizableSkeletalComponentPrivate`  
`class UCustomizableSkeletalComponentPrivate : public UObject`  
_L12-21_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L17 _public prototype_ `UCustomizableSkeletalComponentPrivate();`
- L20 _public member_ `TObjectPtr<UCustomizableObjectInstanceUsage> InstanceUsage;` — `UPROPERTY(Instanced)`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CUSTOMIZABLEOBJECT_API`

### `Plugins/Mutable/Source/CustomizableObject/Internal/MuCO/CustomizableSkeletalMeshActorPrivate.h` (Internal)


#### class `UCustomizableSkeletalMeshActorPrivate`  
`class UCustomizableSkeletalMeshActorPrivate : public UObject`  
_L20-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L25 _public prototype_ `ACustomizableSkeletalMeshActor* GetPublic();`
- L27 _public prototype_ `void Init(UCustomizableObjectInstance* Instance);`
- L29 _public prototype_ `TArray<TObjectPtr<UCustomizableSkeletalComponent>>& GetComponents();`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CUSTOMIZABLEOBJECT_API`

### `Plugins/Mutable/Source/CustomizableObject/Internal/MuCO/DescriptorHash.h` (Internal)


#### class `FDescriptorHash`  
`class FDescriptorHash`  
_L12-27_
- desc: Hash of the Descriptor. Can change and is not backwards compatible. Do not serialize.
- L15 _public prototype_ `FDescriptorHash() = default;`
- L17 _public prototype_ `explicit FDescriptorHash(const FCustomizableObjectInstanceDescriptor& Descriptor);`
- L20 _public prototype_ `bool operator==(const FDescriptorHash& Other) const = default;` — Return true if this Hashes are the same.
- L22 _public prototype_ `FString ToString() const;`
- L25 _private member_ `uint32 Hash = 0;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CUSTOMIZABLEOBJECT_API`

### `Plugins/Mutable/Source/CustomizableObject/Internal/MuCO/FMutableTaskGraph.h` (Internal)


#### class `FMutableTaskGraph`  
`class FMutableTaskGraph`  
_L35-138_
- desc: Mutable Tasks System. Allows launching tasks in different threads: - Mutable Thread - Game Thread - Any Thread Concurrency between tasks in the Mutable Thread is forbidden by chaining all tasks through their prerequisites. LOW PRIORITY MUTABLE TASKS: - Only one Low Priority task can be launched at the same time. This is because once a Task Graph task is launched, it can not be canceled. To allow canceling them, the system holds them until it can ensure that its execution will be imminent (no other tasks running). - A Low Priority task will not be launched if one of the follow conditions is true (in order): 1. There is a task Low Priority task running. 2. Flag bLaunchMutableTaskLowPriority is false. 3. There is a Normal Priority task running (unless time limit).
- L56 _public prototype_ `~FMutableTaskGraph();`
- L58 _public prototype_ `void AddGameThreadTask(const TCHAR* DebugName, TUniqueFunction<void(float)>&& TaskBody, const TArray<UE::Tasks::FTask>& Prerequisites = {});`
- L61 _public prototype_ `UE::Tasks::FTask AddMutableThreadTask(const TCHAR* DebugName, TUniqueFunction<void()>&& TaskBody, const TArray<UE::Tasks::FTask>& Prerequisites = {});` — Create and launch a task on the Mutable Thread with Normal priority.
- L63 _public prototype_ `UE::Tasks::FTask AddGenerationTask(const TCHAR* DebugName, TUniqueFunction<void()>&& TaskBody, const TArray<UE::Tasks::FTask>& Prerequisites = {});`
- L65 _public prototype_ `UE::Tasks::FTask AddImageStreamingTask(const TCHAR* DebugName, TUniqueFunction<void()>&& TaskBody, const TArray<UE::Tasks::FTask>& Prerequisites = {});`
- L67 _public prototype_ `UE::Tasks::FTask AddMeshStreamingTask(const TCHAR* DebugName, TUniqueFunction<void()>&& TaskBody, const TArray<UE::Tasks::FTask>& Prerequisites = {});`
- L70 _public prototype_ `uint32 AddMutableThreadTaskLowPriority(const TCHAR* DebugName, TFunction<void()>&& TaskBody);` — Create and launch a task on the Mutable Thread with Low priority.
- L75 _public prototype_ `bool CancelMutableThreadTaskLowPriority(uint32 Id);` — Cancel, if not already launched, a Mutable Thread with Low priority. Return true if the task has been canceled before launching it. Return false if not found or running.
- L78 _public prototype_ `void WaitForMutableTasks();` — Wait for all Mutable Thread tasks.
- L81 _public prototype_ `void WaitForLaunchedLowPriorityTask(uint32 TaskID);` — Wait for the launched low-priority task if it matches the TaskID.
- L85 _public prototype_ `void AllowLaunchingMutableTaskLowPriority(bool bAllow, bool bFromMutableTask);` — Allow or disallow launching Mutable Tasks with Low priority. @param bFromMutableTask true if called from a Mutable Task.
- L88 _public prototype_ `void Tick();` — Returns the number of remaining tasks.
- L90 _public prototype_ `int32 GetRemainingWork() const;`
- L97 _public prototype_ `void TryLaunchMutableTaskLowPriority(bool bFromMutableTask);` — A Mutable Task Low Priority will only be launched if: - No other low priority task is running. - Is allowed to launch low priority tasks. @param bFromMutableTask true if called from a Mutable Task.
- L99 _public prototype_ `void TryLaunchGameThreadTask();`
- L102 _public prototype_ `bool IsTaskCompleted(const UE::Tasks::FTask& Task) const;` — Return true if the task is completed (or is no longer valid).
- L104 _public member_ `mutable FCriticalSection MutableTaskLock;`
- L107 _public member_ `bool bAllowLaunchMutableTaskLowPriority = true;` — Allow or disallow launching low priority tasks.
- L110 _public member_ `TArray<FMutableThreadLowPriorityTask> QueueMutableTasksLowPriority;` — Queue of low priority tasks. FIFO.
- L113 _public member_ `TQueue<FGameThreadTask> GameThreadTasks;` — Queue of Game Thread tasks that need to be executed.
- L116 _public member_ `static constexpr uint32 INVALID_ID = 0;`
- L120 _private member_ `uint32 TaskIdGenerator = INVALID_ID;` — Incremental task ID generator.
- L123 _private member_ `uint32 LastMutableTaskLowPriorityID = INVALID_ID;` — The ID of the Last Mutable Task Low Priority launched to the TaskGraph system.
- L126 _private member_ `UE::Tasks::FTask LastMutableTaskLowPriority;` — Last Mutable Task Low Priority launched to the TaskGraph system.
- L129 _private member_ `UE::Tasks::FTask LastMutableTask;` — Last Mutable Task launched to the TaskGraph system. Low and normal priority.
- L131 _private member_ `mutable FCriticalSection CriticalSectionLastGenerationTask;`
- L132 _private member_ `mutable FCriticalSection CriticalSectionLastImageStreaming;`
- L133 _private member_ `mutable FCriticalSection CriticalSectionLastMeshStreamingTask;`
- L135 _private member_ `UE::Tasks::FTask LastGenerationTask;`
- L136 _private member_ `UE::Tasks::FTask LastImageStreamingTask;`
- L137 _private member_ `UE::Tasks::FTask LastMeshStreamingTask;`

#### struct `FMutableTaskGraph::FMutableThreadLowPriorityTask`  
`struct FMutableThreadLowPriorityTask`  
_L37-43_
- L39 _public member_ `uint32 Id;`
- L40 _public member_ `FString DebugName;`
- L41 _public member_ `TFunction<void()> Body;`
- L42 _public member_ `double CreationTime = FPlatformTime::Seconds();`

#### struct `FMutableTaskGraph::FGameThreadTask`  
`struct FGameThreadTask`  
_L45-53_
- L47 _public member_ `FString DebugName;`
- L48 _public member_ `TUniqueFunction<void(float)> Body;`
- L49 _public member_ `TArray<UE::Tasks::FTask> Prerequisites;`
- L52 _public prototype_ `bool AreDependenciesComplete() const;` — Check if all the dependencies of this task have been completed.

#### Free symbols / members of external scopes

- L12 _externvar_ `extern TAutoConsoleVariable<bool> CVarEnableParallelUpdates;`

### `Plugins/Mutable/Source/CustomizableObject/Internal/MuCO/ICustomizableObjectEditorModule.h` (Internal)


#### class `ICustomizableObjectEditorModule`  
`class ICustomizableObjectEditorModule : public IModuleInterface`  
_L39-147_
- inherits: `IModuleInterface`
- desc: Customizable object editor module interface
- L42 _public function_ `static ICustomizableObjectEditorModule* Get()`
- L51 _public function_ `static ICustomizableObjectEditorModule& GetChecked()`
- L59 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetCustomizableObjectEditorToolBarExtensibilityManager()`
- L60 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetCustomizableObjectEditorMenuExtensibilityManager()`
- L63 _public prototype_ `virtual FCustomizableObjectEditorLogger& GetLogger() = 0;` — Returns the module logger.
- L73 _public prototype_ `virtual bool IsCompilationOutOfDate(const UCustomizableObject& Object, bool bSkipIndirectReferences, TArray<FName>& OutOfDatePackages, TArray<FName>& AddedPackages, TArray<FName>& RemovedPackages, bool& bReleaseVersionDiff) const = 0;` — Return if the CO is not compiled or the ParticipatingObjects system has detected a change (participating objects dirty or re-saved since last compilation). @param Object object to check. @param bSkipIndirectReferences if true, do not check for added/removed indirect references. @param OutOfDatePackages list of out of date packages. @param AddedPackages list of added packages since the last compilation. @param RemovedPackages list of removed packages since the last compilation. @param bReleaseVersionDiff true if the Release Version has changed since the last compilation. @return true if the compilation is out of date.
- L78 _public prototype_ `virtual void OnUpstreamCOsLoadedFixup(UCustomizableObject* Object, int32 CustomizableObjectCustomVersion) const = 0;` — Fixup operations executed once the upstream COs (parent COs) have been loaded. @param CustomizableObjectCustomVersion Version index used to determine what change in the data should be performed.
- L80 _public typedef_ `using IsCompilationOutOfDateCallback = TFunction<void(bool bOutOfDate, bool bVersionDiff, const TArray<FName>& OutOfDatePackages, const TArray<FName>& AddedPackages, const TArray<FName>& RemovedPackages)>;`
- L84 _public prototype_ `virtual void IsCompilationOutOfDate(const UCustomizableObject& Object, bool bSkipIndirectReferences, float MaxTime, const IsCompilationOutOfDateCallback& Callback) const = 0;` — Async version. See IsCompilationOutOfDate. @param MaxTime. Max time it can spend on each Game Thread tick. Use MAX_flt for sync call.
- L87 _public prototype_ `virtual bool IsRootObject(const UCustomizableObject& Object) const = 0;` — See GraphTraversal::IsRootObject(...)
- L91 _public prototype_ `virtual FString GetCurrentReleaseVersionForObject(const UCustomizableObject& Object) const = 0;` — Get the current Release Version for the given Object. @return Current version as string.
- L94 _public prototype_ `virtual UCustomizableObject* GetRootObject(UCustomizableObject* ChildObject) const = 0;` — See GraphTraversal::GetRootObject(...)
- L97 _public prototype_ `virtual const UCustomizableObject* GetRootObject(const UCustomizableObject* ChildObject) const = 0;` — See GraphTraversal::GetRootObject(...)
- L99 _public prototype_ `virtual void GetAllObjectsInGraph(UCustomizableObject*, TSet<UCustomizableObject*>& OutRelated ) const = 0;`
- L106 _public prototype_ `virtual void BakeCustomizableObjectInstance(UCustomizableObjectInstance* InTargetInstance, const FBakingConfiguration& InBakingConfig) = 0;` — Execute this method in order to bake the provided instance. It will schedule a special type of instance update before proceeding with the bake itself. @param InTargetInstance The instance we want to bake @param InBakingConfig Structure containing the configuration to be used for the baking
- L109 _public prototype_ `virtual void EvictSkeletalMeshThumbnailScene(USkeletalMesh* InSkeletalMesh) const = 0;` — Evict scenes from the UCustomizableObjectSkeletalMeshThumbnailRenderer cache used for InSkeletalMesh
- L113 _public prototype_ `virtual void CompileCustomizableObject(UCustomizableObject& Object, const FCompileParams* Params, bool bSilent, bool bForce) = 0;` — Compile the given Customizable Object. If calling inside the Customizable Object Editor module, consider using ICustomizableObjectEditorModulePrivate::EnqueueCompileRequest.
- L115 _public prototype_ `virtual void Tick(bool bBlocking) = 0;`
- L117 _public prototype_ `virtual int32 GetRemainingWork() const = 0;`
- L120 _public prototype_ `virtual void CancelCompileRequests() = 0;` — Force finish current compile request and cancels all pending requests
- L123 _public prototype_ `virtual int32 GetNumCompileRequests() = 0;` — Return the number of pending compilation requests. Ongoing requests included.
- L125 _public prototype_ `virtual USkeletalMesh* GetReferenceSkeletalMesh(const UCustomizableObject& Object, const FName& Component) const = 0;`
- L128 _public prototype_ `virtual TMap<FName, FGuid> GetParticipatingObjects(const UCustomizableObject* Object, const FCompilationOptions* Options = nullptr) const = 0;` — Perform a fast compilation pass to get all participating objects.
- L130 _public prototype_ `virtual void BackwardsCompatibleFixup(UEdGraph& Graph, int32 CustomizableObjectCustomVersion) = 0;`
- L132 _public prototype_ `virtual void PostBackwardsCompatibleFixup(UEdGraph& Graph) = 0;`
- L134 _public prototype_ `virtual bool IsCompiling(const UCustomizableObject& Object) const = 0;`
- L136 _public prototype_ `virtual void BeginCacheForCookedPlatformData(UCustomizableObject& Object, const ITargetPlatform* TargetPlatform) = 0;`
- L138 _public prototype_ `virtual bool IsCachedCookedPlatformDataLoaded(UCustomizableObject& Object, const ITargetPlatform* TargetPlatform) = 0;`
- L142 _public prototype_ `virtual void AddPendingLoad(UCustomizableObject* Object) = 0;` — Add a CO to the pending - load list.COs need to wait until all related objects are fully loaded before being able to do things like check-if-up-to-date or compile.
- L144 _public prototype_ `virtual void RegisterExternalOperation(const UScriptStruct* Operation) = 0;`
- L146 _public prototype_ `virtual void UnregisterExternalOperation(const UScriptStruct* Operation) = 0;`

#### Free symbols / members of external scopes

- L25 _externvar_ `extern const FName CustomizableObjectEditorAppIdentifier;`
- L26 _externvar_ `extern const FName CustomizableObjectInstanceEditorAppIdentifier;`
- L27 _externvar_ `extern const FName CustomizableObjectPopulationEditorAppIdentifier;`
- L28 _externvar_ `extern const FName CustomizableObjectPopulationClassEditorAppIdentifier;`
- L29 _externvar_ `extern const FName CustomizableObjectDebuggerAppIdentifier;`
- L30 _externvar_ `extern const FName CustomizableObjectMacroLibraryEditorAppIdentifier;`
- L33 _macro_ `#define MODULE_NAME_COE "CustomizableObjectEditor"`

### `Plugins/Mutable/Source/CustomizableObject/Internal/MuCO/ICustomizableObjectModulePrivate.h` (Internal)


#### class `ICustomizableObjectModulePrivate`  
`class ICustomizableObjectModulePrivate : public ICustomizableObjectModule`  
_L15-24_
- inherits: `ICustomizableObjectModule`
- L18 _public function_ `static ICustomizableObjectModulePrivate& Get()`
- L23 _public prototype_ `virtual TSet<TStrongObjectPtr<const UScriptStruct>> GetRegisteredExternalOperations() const = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Mutable` (scope `UE`)

### `Plugins/Mutable/Source/CustomizableObject/Internal/MuCO/LoadUtils.h` (Internal)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L16 _prototype_ `UObject* LoadObject(const FAssetData& DataAsset);` (scope `UE::Mutable::Private`)
- L19 _prototype_ `UObject* LoadObject(const FSoftObjectPath& Path);` (scope `UE::Mutable::Private`)
- L22 _prototype_ `UObject* LoadObject(const FSoftObjectPtr& SoftObject);` (scope `UE::Mutable::Private`)
- L26 _function_ `template <typename T> T* LoadObject(UObject* Outer, const TCHAR* Name, const TCHAR* Filename = nullptr, uint32 LoadFlags = LOAD_None, UPackageMap* Sandbox = nullptr, const FLinkerInstancingContext* InstancingContext = nullptr)` (scope `UE::Mutable::Private`)
- L36 _function_ `template<typename T> T* LoadObject(const TSoftObjectPtr<T>& SoftObject)` (scope `UE::Mutable::Private`)
- L47 _function_ `template<typename T> UClass* LoadClass(const FSoftClassPath& Path)` (scope `UE::Mutable::Private`)
- L58 _function_ `template<typename T> UClass* LoadClass(const TSoftClassPtr<T>& SoftClass)` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/CustomizableObject/Internal/MuCO/LogBenchmarkUtil.h` (Internal)


#### struct `FInstanceUpdateStats`  
`struct FInstanceUpdateStats`  
_L74-101_
- desc: Object representing the update data of an instance. In practical terms represents one row of the CSV we generate
- L76 _public member_ `FString CustomizableObjectPathName = "";`
- L77 _public member_ `FString CustomizableObjectInstancePathName = "";`
- L78 _public member_ `FString UpdateType = "";`
- L79 _public member_ `FString Descriptor = "";` — Simplified for compatibility (maybe in the future we keep the entire descriptor)
- L81 _public member_ `EUpdateResult UpdateResult = EUpdateResult::Error;`
- L83 _public member_ `bool bLevelBegunPlay = false;`
- L85 _public member_ `uint32 TriangleCount = 0;`
- L87 _public member_ `double QueueTime = 0.0;`
- L88 _public member_ `double UpdateTime = 0.0;`
- L89 _public member_ `double TaskGetMeshesTime = 0.0;`
- L91 _public member_ `double TaskGetImagesTime = 0.0;`
- L92 _public member_ `double TaskConvertResourcesTime = 0.0;`
- L93 _public member_ `double TaskCallbacksTime = 0.0;`
- L95 _public member_ `double UpdatePeakMemory = 0.0;`
- L96 _public member_ `double UpdateRealPeakMemory = 0.0;`
- L98 _public member_ `double TaskUpdateImageTime = 0.0;`
- L99 _public member_ `double TaskUpdateImagePeakMemory = 0.0;`
- L100 _public member_ `double TaskUpdateImageRealPeakMemory = 0.0;`

#### struct `FStatistic`  
`struct FStatistic`  
_L104-110_
- L106 _public member_ `double Min = +TNumericLimits<double>::Max();`
- L107 _public member_ `double Max = -TNumericLimits<double>::Max();`
- L108 _public member_ `double LowerBound = 0.0f;`
- L109 _public member_ `double UpperBound = 0.0f;`

#### struct `FInstanceUpdateStatistics`  
`struct FInstanceUpdateStatistics`  
_L113-127_
- L115 _public member_ `FStatistic TriangleCount;`
- L116 _public member_ `FStatistic QueueTime;`
- L117 _public member_ `FStatistic UpdateTime;`
- L118 _public member_ `FStatistic TaskGetMeshTime;`
- L119 _public member_ `FStatistic TaskGetImagesTime;`
- L120 _public member_ `FStatistic TaskConvertResourcesTime;`
- L121 _public member_ `FStatistic TaskCallbacksTime;`
- L122 _public member_ `FStatistic UpdatePeakMemory;`
- L123 _public member_ `FStatistic UpdateRealPeakMemory;`
- L124 _public member_ `FStatistic TaskUpdateImageTime;`
- L125 _public member_ `FStatistic TaskUpdateImagePeakMemory;`
- L126 _public member_ `FStatistic TaskUpdateImageRealPeakMemory;`

#### class `FLogBenchmarkUtil`  
`class FLogBenchmarkUtil`  
_L136-197_
- desc: Benchmarking system. Gathers stats and send it to Insights an Benchmarking Files.
- L139 _public prototype_ `~FLogBenchmarkUtil();`
- L146 _public prototype_ `static void SetBenchmarkReportingStateOverride(bool bIsEnabled);` — Enables or disables the benchmarking system from code. Usefull for enabling the benchmarking without having to mess with CVarEnableBenchmark @param bIsEnabled True to enable, false to disable and let CVarEnableBenchmark decide .
- L152 _public prototype_ `static bool IsBenchmarkingReportingEnabled();` — Get to know if the benchmarking is active or not @return True if the CVarEnableBenchmark CVar or the override are set to true, false otherwise
- L155 _public prototype_ `void GetInstancesStats(int32& OutNumInstances, int32& OutNumBuiltInstances, int32& OutNumAllocatedSkeletalMeshes) const;` — Get stats.
- L158 _public prototype_ `void AddTexture(UTexture2D& Texture);` — Add Mutable created Texture to track.
- L161 _public prototype_ `void UpdateStats();` — Update stats which can only be updated on the tick.
- L164 _public prototype_ `void FinishUpdateMesh(const TSharedRef<FUpdateContextPrivate>& Context);` — Gathers update stats when it has finished.
- L166 _public prototype_ `void FinishUpdateImage(const FString& CustomizableObjectPathName, const FString& InstancePathName, const FString& InstanceDescriptor, const bool bDidLevelBeginPlay, double TaskUpdateImageTime, const int64 TaskUpdateImageMemoryPeak, const int64 TaskUpdateImageRealMemoryPeak);`
- L168 _public prototype_ `DECLARE_BENCHMARK_STAT(NumAllocatedTextures, uint32);`
- L169 _public prototype_ `DECLARE_BENCHMARK_STAT(TextureGPUSize, uint64);`
- L171 _public prototype_ `DECLARE_BENCHMARK_STAT(NumAllocatedSkeletalMeshes, int32);`
- L173 _public prototype_ `DECLARE_BENCHMARK_STAT(NumInstances, int32);`
- L175 _public prototype_ `DECLARE_BENCHMARK_STAT(NumPendingInstanceUpdates, int32) DECLARE_BENCHMARK_STAT(NumBuiltInstances, int32) DECLARE_BENCHMARK_STAT(InstanceBuildTimeAvrg, double);`
- L179 _public member_ `TArray<TWeakObjectPtr<UTexture2D>> TextureTrackerArray;`
- L183 _private member_ `inline static bool bIsEnabledOverride = false;`
- L185 _private member_ `double TotalUpdateTime = 0;`
- L186 _private member_ `uint32 NumUpdates = 0;`
- L188 _private member_ `TSharedPtr<FArchive> Archive;`
- L193 _public member_ `FOnMeshUpdateReportedSignature OnMeshUpdateReported;` — Delegate invoked each time a new mesh update is reported by this utility
- L196 _public member_ `FOnImageUpdateReportedSignature OnImageUpdateReported;` — Delegate invoked each time a new mip update is reported by this utility

#### Free symbols / members of external scopes

- L17 _macro_ `#define DECLARE_BENCHMARK_STAT(Name, Type) \` — Stat which automatically gets updated to Insights when modified.
- L51 _macro_ `#define DECLARE_BENCHMARK_INSIGHTS(Name, Description) \`
- L57 _delegate_ `DECLARE_STATS_GROUP(TEXT("Mutable"), STATGROUP_Mutable, STATCAT_Adv` — Mutable stats
- L71 _externvar_ `extern TAutoConsoleVariable<bool> CVarEnableBenchmark;`
- L131 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMeshUpdateReportedSignature, const TSharedRef<FUpdateContextPrivate> , FInstanceUpdateStats) DECLARE_MULTICAST_DELEGATE_OneParam(FOnImageUpdateReportedSignature, FInstanceUpdateStats) class FLogBenchmarkUtil { public: ~FLogBenchmarkUtil(); static void SetBenchmarkReportingStateOverride(bool bIsEnabled); static bool IsBenchmarkingReportingEnabled(); void GetInstancesStats(int32& OutNumInstances, int32& OutNumBuiltInstances, int32& OutNumAllocatedSkeletalMeshes) const; void AddTexture(UTexture2D& Texture); void UpdateStats(); void FinishUpdateMesh(const TSharedRef<FUpdateContextPrivate>& Context); void FinishUpdateImage(const FString& CustomizableObjectPathName, const FString& InstancePathName, const FString& InstanceDescriptor, const bool bDidLevelBeginPlay, double TaskUpdateImageTime, const int64 TaskUpdateImageMemoryPeak, const int64 TaskUpdateImageRealMemoryPeak); DECLARE_BENCHMARK_STAT(NumAllocatedTextures, uint32); DECLARE_BENCHMARK_STAT(TextureGPUSize, uint64);` — Delegate signature
- L132 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnImageUpdateReportedSignature, FInstanceUpdateStats) class FLogBenchmarkUtil { public: ~FLogBenchmarkUtil(); static void SetBenchmarkReportingStateOverride(bool bIsEnabled); static bool IsBenchmarkingReportingEnabled(); void GetInstancesStats(int32& OutNumInstances, int32& OutNumBuiltInstances, int32& OutNumAllocatedSkeletalMeshes) const; void AddTexture(UTexture2D& Texture); void UpdateStats(); void FinishUpdateMesh(const TSharedRef<FUpdateContextPrivate>& Context); void FinishUpdateImage(const FString& CustomizableObjectPathName, const FString& InstancePathName, const FString& InstanceDescriptor, const bool bDidLevelBeginPlay, double TaskUpdateImageTime, const int64 TaskUpdateImageMemoryPeak, const int64 TaskUpdateImageRealMemoryPeak); DECLARE_BENCHMARK_STAT(NumAllocatedTextures, uint32); DECLARE_BENCHMARK_STAT(TextureGPUSize, uint64); DECLARE_BENCHMARK_STAT(NumAllocatedSkeletalMeshes, int32);`

### `Plugins/Mutable/Source/CustomizableObject/Internal/MuCO/MutableProjectorTypeUtils.h` (Internal)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ProjectorUtils`
- L15 _prototype_ `ECustomizableObjectProjectorType GetEquivalentProjectorType (UE::Mutable::Private::EProjectorType ProjectorType);` (scope `ProjectorUtils`)
- L22 _prototype_ `UE::Mutable::Private::EProjectorType GetEquivalentProjectorType (ECustomizableObjectProjectorType ProjectorType);` (scope `ProjectorUtils`)

### `Plugins/Mutable/Source/CustomizableObject/Internal/MuCO/MutableStreamableManager.h` (Internal)


#### class `FMutableStreamableManager`  
`class FMutableStreamableManager : public TSharedFromThis<FMutableStreamableManager>`  
_L14-95_
- inherits: `TSharedFromThis<FMutableStreamableManager>`
- desc: Wrapper to the FStreamableManager that allows to kill in-flight async loads and force them sync.
- L18 _public function_ `template<typename PathContainerType = TArray<FSoftObjectPath>, typename FuncType = FStreamableDelegate> TSharedPtr<FStreamableHandle> RequestAsyncLoad( PathContainerType&& TargetsToStream, FuncType&& DelegateToCall = FStreamableDelegate(), TAsyncLoadPriority Priority = FStreamableManager::DefaultAsyncLoadPriority, bool bManageActiveHandle = false, bool bStartStalled = false, FString&& DebugName = FString(TEXT("MutableRequestAsyncLoad")), UE::FSourceLocation&& Location = UE::FSourceLocation::Current())`
- L65 _public function_ `template<typename PathContainerType = TArray<FSoftObjectPath>> TSharedPtr<FStreamableHandle> RequestSyncLoad( PathContainerType&& TargetsToStream, bool bManageActiveHandle = false, FString&& DebugName = FString(TEXT("MutableRequestAsyncLoad")), UE::FSourceLocation&& Location = UE::FSourceLocation::Current())`
- L75 _public prototype_ `void Tick(bool bBlocking);`
- L77 _public prototype_ `int32 GetRemainingWork() const;`
- L92 _private member_ `FStreamableManager StreamableManager;`
- L94 _private member_ `TArray<TSharedRef<FMutableStreamableHandle>> StreamableHandles;`

#### struct `FMutableStreamableManager::FMutableStreamableHandle`  
`struct FMutableStreamableHandle`  
_L80-90_
- L83 _public member_ `TSharedPtr<FStreamableHandle> Handle;` — Always valid.
- L85 _public member_ `FStreamableDelegate Delegate;`
- L89 _public member_ `bool bCompleted = false;` — Load completed and delegate called. Used since FStreamableHandle does not have away of knowing when the delegate has been called.

#### Free symbols / members of external scopes

- L41 _function_ `` (scope `FMutableStreamableManager::RequestAsyncLoad`)

### `Plugins/Mutable/Source/CustomizableObject/Internal/MuCO/StateMachine.h` (Internal)


#### class `FStateMachine`  
`template<typename T> class FStateMachine`  
_L16-48_
- desc: Simple state machine with transitions check. Type T must implement the following: - EState: Enum of valid states. - StartState: Variable defining the initial state. - ValidTransitions: 2D bool array of valid transitions.
- L19 _public typedef_ `using EState = typename T::EState;`
- L23 _public function_ `void NextState(EState State)`
- L32 _public function_ `EState Get() const`
- L37 _public function_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStateChangedDelegate, EState, EState) FOnStateChangedDelegate& GetOnStateChangedDelegate()`
- L45 _private member_ `FOnStateChangedDelegate OnStateChangedDelegate;`
- L47 _private member_ `EState CurrentState = T::StartState;`

#### Free symbols / members of external scopes

- L37 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStateChangedDelegate, EState, EState) FOnStateChangedDelegate& GetOnStateChangedDelegate() { return OnStateChangedDelegate; } private: FOnStateChangedDelegate OnStateChangedDelegate;`

### `Plugins/Mutable/Source/CustomizableObject/Internal/MuCO/UnrealConversionUtils.h` (Internal)


#### struct `UnrealConversionUtils::FSectionClothData`  
`struct FSectionClothData`  
_L43-53_
- L45 _public member_ `int32 SectionIndex;`
- L46 _public member_ `int32 LODIndex;`
- L47 _public member_ `int32 BaseVertex;`
- L48 _public member_ `TArrayView<const uint16> SectionIndex16View;`
- L49 _public member_ `TArrayView<const uint32> SectionIndex32View;`
- L50 _public member_ `TArrayView<const int32> ClothingDataIndicesView;`
- L51 _public member_ `TArrayView<const FCustomizableObjectMeshToMeshVertData> ClothingDataView;`
- L52 _public member_ `TArray<FMeshToMeshVertData> MappingData;`

#### Free symbols / members of external scopes

- L6 _macro_ `#define MUTABLE_VERTEXBUFFER_POSITION 0` — Order of the unreal vertex buffers when in mutable data
- L7 _macro_ `#define MUTABLE_VERTEXBUFFER_TANGENT 1`
- L8 _macro_ `#define MUTABLE_VERTEXBUFFER_TEXCOORDS 2`
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace Mutable` (scope `UE`)
- L24 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L41 _namespace_ `namespace UnrealConversionUtils`
- L70 _prototype_ `bool SetupRenderSections( FSkeletalMeshLODRenderData& LODResource, const UE::Mutable::Private::FMesh* InMutableMesh, const FReferenceSkeleton& InRefSkeleton, const TArray<FName>& InBoneMap, const int32 InFirstBoneMapIndex);` (scope `UnrealConversionUtils`) — Prepares the render sections found on the InSkeletalMesh and sets them up accordingly what the InMutableMesh requires @param LODResource - LODRenderData whose sections are ought to be updated @param InMutableMesh - Mutable mesh to be used as reference for the section data update on the Skeletal Mesh @param InBoneMap - Bones to be set as part of the sections. @param InFirstBoneMapIndex - Index to the first BoneMap bone that belongs to this LODResource. @param SectionMetadata - Section metadata for each surface in InMutableMesh. @return True if the operation was succesfull, false otherwise.
- L83 _prototype_ `void InitVertexBuffersWithDummyData( FSkeletalMeshLODRenderData& LODResource, const UE::Mutable::Private::FMesh* InMutableMesh, const bool bAllowCPUAccess);` (scope `UnrealConversionUtils`) — Initializes the LODResource's VertexBuffers with dummy data to prepare it for streaming. @param LODResource - LODRenderData to update @param InMutableMesh - Mutable mesh to be used as reference for the section data update on the Skeletal Mesh @param bAllowCPUAccess - Keeps this LODs data on the CPU so it can be used for things such as sampling in FX.
- L94 _prototype_ `void CopyMutableVertexBuffers( FSkeletalMeshLODRenderData& LODResource, const UE::Mutable::Private::FMesh* InMutableMesh, const bool bAllowCPUAccess, const bool bIsStreaming = false);` (scope `UnrealConversionUtils`) — Performs a copy of the data found on the vertex buffers on the mutable mesh to the buffers of the skeletal mesh @param LODResource - LODRenderData to update @param InMutableMesh - Mutable mesh to be used as reference for the vertex data update on the Skeletal Mesh @param bAllowCPUAccess - Keeps this LODs data on the CPU so it can be used for things such as sampling in FX. @param bIsStreaming - Copy vertex buffers from LOD streamin request
- L106 _prototype_ `void InitIndexBuffersWithDummyData( FSkeletalMeshLODRenderData& LODResource, const UE::Mutable::Private::FMesh* InMutableMesh);` (scope `UnrealConversionUtils`) — Initializes the LODResource's IndexBuffers with dummy data to prepare it for streaming. @param LODResource - LODRenderData to be updated. @param InMutableMesh - The mutable mesh whose index buffers you want to work with
- L118 _prototype_ `bool CopyMutableIndexBuffers( FSkeletalMeshLODRenderData& LODResource, const UE::Mutable::Private::FMesh* InMutableMesh, bool& bOutMarkRenderStateDirty, TOptional<TConstArrayView<int32>> RenderToMutableSectionIndexMap = {});` (scope `UnrealConversionUtils`) — Performs a copy of the data found on the index buffers on the mutable mesh to the buffers of the skeletal mesh @param LODResource - LODRenderData to be updated. @param InMutableMesh - The mutable mesh whose index buffers you want to work with @param bOutMarkRenderStateDirty @param RenderToMutableSectionIndexMap - Map form RenderSection Index to MutableSection Index. In case the optional is not set, the identity is used. @return True if the operation could be performed successfully, false if not.
- L132 _prototype_ `void CopyMutableSkinWeightProfilesBuffers( FSkeletalMeshLODRenderData& LODResource, USkeletalMesh& Owner, int32 LODIndex, const UE::Mutable::Private::FMesh* InMutableMesh );` (scope `UnrealConversionUtils`) — Performs a copy of the data found on the index buffers on the mutable mesh to the buffers of the skeletal mesh @param LODResource - LODRenderData to be updated. @param Owner - Outer mesh of the LODResource. @param LODIndex - LOD Index of the LODResource. @param InMutableMesh - Mutable mesh to be used to initialize the SkinWeightProfilesBuffers.
- L148 _prototype_ `void CopySkeletalMeshLODRenderData( FSkeletalMeshLODRenderData& LODResource, FSkeletalMeshLODRenderData& SourceLODResource, USkeletalMesh& Owner, int32 LODIndex, const bool bAllowCPUAccess );` (scope `UnrealConversionUtils`) — Performs a copy of the render data of a specific Skeletal Mesh LOD to another Skeletal Mesh @param LODResource - LODRenderData to copy to. @param SourceLODResource - LODRenderData to copy from. @param Owner - Outer mesh of the LODResource and SourceLODResource. @param LODIndex - LOD Index to copy to. @param bAllowCPUAccess - Keeps this LODs data on the CPU so it can be used for things such as sampling in FX.
- L160 _prototype_ `void UpdateSkeletalMeshLODRenderDataBuffersSize( FSkeletalMeshLODRenderData& LODResource );` (scope `UnrealConversionUtils`) — Update SkeletalMeshLODRenderData buffers size. @param LODResource - LODRenderData to be updated.
- L164 _prototype_ `void MorphTargetVertexInfoBuffers( FSkeletalMeshLODRenderData& LODResource, const USkeletalMesh& Owner, const UE::Mutable::Private::FMesh& MutableMesh, int32 LODIndex, bool bGenerateCPUMorphTargets, TOptional<TConstArrayView<int32>> RenderToMutableSectionIndexMap = {});` (scope `UnrealConversionUtils`)
- L173 _prototype_ `void SetMorphData( TNotNull<UE::Mutable::Private::FMesh*> Result, TNotNull<const USkeletalMesh*> SkeletalMesh, int32 LODIndex, int32 SectionIndex, uint32 SourceSectionBaseVertexIndex, uint32 SourceSectionNumVertices, uint32 SourceMeshNumVertices, FMorphTargetVertexInfoBuffers* OptionalMorphTargetVertexBuffer);` (scope `UnrealConversionUtils`)
- L180 _prototype_ `UE::Tasks::FTask ConvertSkeletalMeshFromRuntimeData(USkeletalMesh* SkeletalMesh, int32 BaseLODIndex, int32 BaseSectionIndex, int32 LODBias, uint8 ConversionFlags, UE::Mutable::Private::TManagedPtr<UE::Mutable::Private::FMesh> Result);` (scope `UnrealConversionUtils`)
- L193 _prototype_ `UE::Tasks::FTask ConvertSkeletalMeshFromRuntimeData(USkeletalMesh* SkeletalMesh, int32 LODBegin, int32 LODEnd, int32 GeometryLODBegin, int32 GeometryLODEnd, uint8 ConversionFlags, UE::Mutable::Private::TManagedPtr<UE::Mutable::Private::FSkeletalMesh> Result);` (scope `UnrealConversionUtils`) — Converts a LOD range of a USkeletalMesh to a FSkeletalMesh. @param SkeletalMesh - USkeletalMesh to convert. @param LODBegin - Begin of the LOD range to load. @param LODEnd - End of the LOD range to load. @param GeometryLODBegin - Begin of the LOD range for which the geometry will be loaded. @param GeometryLODEnd - End of the LOD rnage for which the geometry will be loaded. @param ConversionFlags - Flags used in the conversion to discard or modify some of the data. @param Result - Result FSkeletalMesh. @return The task which upon completion Result will contain the conversion result.
- L195 _prototype_ `TSharedPtr<UE::Mutable::Private::FPhysicsBody> MakePhysicsBodyFromAsset(UPhysicsAsset* Asset, const TArray<uint8>& BodySetupRelevancyMap);` (scope `UnrealConversionUtils`)
- L198 _prototype_ `void ClothVertexBuffers( FSkeletalMeshLODRenderData& LODResource, const UE::Mutable::Private::FMesh& MutableMesh, TOptional<TConstArrayView<int32>> RenderToMutableSectionIndexMap = {});` (scope `UnrealConversionUtils`)
- L203 _prototype_ `void PropagateBoneUsageFlagsThroughMeshPose(UE::Mutable::Private::FMesh& Mesh);` (scope `UnrealConversionUtils`)
- L205 _prototype_ `UE::Mutable::Private::TManagedPtr<UE::Mutable::Private::FPhysicsBody> CreatePhysicsBodyForMesh( const UPhysicsAsset& PhysicsAsset, const UE::Mutable::Private::FMesh& Mesh);` (scope `UnrealConversionUtils`)

### `Plugins/Mutable/Source/CustomizableObject/Internal/MuCO/UnrealMutableImageProvider.h` (Internal)


#### class `FUnrealMutableResourceProvider`  
`class FUnrealMutableResourceProvider : public UE::Mutable::Private::FExternalResourceProvider`  
_L14-48_
- inherits: `UE::Mutable::Private::FExternalResourceProvider`
- desc: Implementation of a mutable core provider for image parameters that are application-specific.
- L20 _public prototype_ `virtual TTuple<UE::Tasks::FTask, TFunction<void()>> GetImageAsync(UTexture* Texture, uint8 MipmapsToSkip, bool bLoadMipTail, TFunction<void(UE::Mutable::Private::TManagedPtr<UE::Mutable::Private::FImage>)>& ResultCallback) override;` — UE::Mutable::Private::ExternalResourceProvider interface Thread: worker
- L21 _public prototype_ `virtual TTuple<UE::Tasks::FTask, TFunction<void()>> GetReferencedImageAsync( int32 Id, uint8 MipmapsToSkip, TFunction<void(UE::Mutable::Private::TManagedPtr<UE::Mutable::Private::FImage>)>& ResultCallback) override;`
- L22 _public prototype_ `virtual UE::Mutable::Private::FExtendedImageDesc GetImageDesc(UTexture* Texture) override;`
- L23 _public prototype_ `virtual TTuple<UE::Tasks::FTask, TFunction<void()>> GetMeshAsync( USkeletalMesh* SkeletalMesh, int32 BaseLODIndex, int32 BaseSectionIndex, int32 LODBias, uint8 ConversionFlags, TFunction<void(UE::Mutable::Private::TManagedPtr<UE::Mutable::Private::FMesh>)>& ResultCallback) override;`
- L26 _public prototype_ `virtual TTuple<UE::Tasks::FTask, TFunction<void()>> GetSkeletalMeshAsync( USkeletalMesh* SkeletalMesh, int32 LODBegin, int32 LODEnd, int32 GeometryLODBegin, int32 GeometryLODEnd, uint8 ConversionFlags, TFunction<void(UE::Mutable::Private::TManagedPtr<UE::Mutable::Private::FSkeletalMesh>)>& ResultCallback) override;`
- L30 _public prototype_ `void CacheRuntimeReferencedImages(const TArray<TSoftObjectPtr<UTexture2D>>& RuntimeReferencedTextures);`
- L38 _private prototype_ `static UE::Mutable::Private::TManagedPtr<UE::Mutable::Private::FImage> CreateDummy();` — This will be called if an image Id has been requested by Mutable core but it has not been provided by any provider.
- L39 _private prototype_ `static UE::Mutable::Private::FExtendedImageDesc CreateDummyDesc();`
- L42 _private member_ `TArray<TStrongObjectPtr<UTexture>> Images;`
- L46 _private member_ `FCriticalSection RuntimeReferencedLock;`

### `Plugins/Mutable/Source/CustomizableObject/Internal/MuCO/UnrealMutableModelDiskStreamer.h` (Internal)


#### class `FUnrealMutableInputStream`  
`class FUnrealMutableInputStream : public UE::Mutable::Private::FInputStream`  
_L23-34_
- inherits: `UE::Mutable::Private::FInputStream`
- L27 _public prototype_ `FUnrealMutableInputStream(FArchive& ar);`
- L30 _public prototype_ `void Read(void* pData, uint64 size) override;` — UE::Mutable::Private::FInputStream interface
- L33 _private member_ `FArchive& m_ar;`

#### struct `FDDCReadRequest`  
`struct FDDCReadRequest`  
_L37-43_
- L39 _public prototype_ `FDDCReadRequest();`
- L41 _public member_ `UE::DerivedData::FRequestOwner RequestOwner;`
- L42 _public member_ `bool bSuccess = false;`

#### class `FUnrealMutableModelBulkReader`  
`class FUnrealMutableModelBulkReader : public UE::Mutable::Private::FModelReader`  
_L47-112_
- inherits: `UE::Mutable::Private::FModelReader`
- desc: Implementation of a mutable streamer using bulk storage.
- L51 _public prototype_ `~FUnrealMutableModelBulkReader();`
- L56 _public prototype_ `bool PrepareStreamingForObject(UCustomizableObject* Object);` — Make sure that the provided object can stream data.
- L63 _public prototype_ `void CancelStreamingForObject(const UCustomizableObject* CustomizableObject);` — Cancel any further streaming operations for the given object. This is necessary if the object compiled data is going to be modified. This can only happen in the editor, when recompiling. Any additional streaming requests for this object will fail.
- L68 _public prototype_ `bool AreTherePendingStreamingOperationsForObject(const UCustomizableObject* CustomizableObject) const;` — Checks if there are any streaming operations for the parameter object. @return true if there are streaming operations in flight
- L72 _public prototype_ `void EndStreaming();` — Release all the pending resources. This disables treamings for all objects.
- L75 _public prototype_ `bool DoesBlockExist(const UE::Mutable::Private::FModel*, uint32 BlockKey) override;` — UE::Mutable::Private::ModelReader interface
- L76 _public prototype_ `FOperationID BeginReadBlock(const UE::Mutable::Private::FModel*, uint32 BlockKey, void* pBuffer, uint64 size, UE::Mutable::Private::EDataType ResourceType, TFunction<void(bool bSuccess)>* CompletionCallback) override;`
- L77 _public prototype_ `bool IsReadCompleted(FOperationID) override;`
- L78 _public prototype_ `bool EndRead(FOperationID) override;`
- L106 _private member_ `TArray<FObjectData> Objects;`
- L108 _private member_ `mutable FCriticalSection CriticalSection;`
- L111 _private member_ `FOperationID LastOperationID = 0;` — This is used to generate unique ids for read requests.

#### struct `FUnrealMutableModelBulkReader::FReadRequest`  
`struct FReadRequest`  
_L81-93_
- L83 _public member_ `TSharedPtr<IBulkDataIORequest> BulkReadRequest;`
- L84 _public member_ `TSharedPtr<IAsyncReadFileHandle> FileHandle;`
- L85 _public member_ `TSharedPtr<IAsyncReadRequest> FileReadRequest;`
- L86 _public member_ `TSharedPtr<FAsyncFileCallBack> FileCallback;`
- L88 _public member_ `uint32 FileId = 0;`
- L91 _public member_ `TSharedPtr<FDDCReadRequest> DDCReadRequest;`

#### struct `FUnrealMutableModelBulkReader::FObjectData`  
`struct FObjectData`  
_L96-104_
- desc: Streaming data for one object.
- L98 _public member_ `TWeakPtr<const UE::Mutable::Private::FModel> Model;`
- L100 _public member_ `FString BulkFilePrefix;`
- L101 _public member_ `TMap<FOperationID, FReadRequest> CurrentReadRequests;`
- L103 _public member_ `TWeakPtr<FModelStreamableBulkData> ModelStreamableBulkData;`

#### class `UnrealMutableOutputStream`  
`class UnrealMutableOutputStream : public UE::Mutable::Private::FOutputStream`  
_L117-128_
- inherits: `UE::Mutable::Private::FOutputStream`
- L121 _public prototype_ `UnrealMutableOutputStream(FArchive& ar);`
- L124 _public prototype_ `void Write(const void* pData, uint64 size) override;` — UE::Mutable::Private::FOutputStream interface
- L127 _private member_ `FArchive& m_ar;`

#### class `FUnrealMutableModelBulkWriterEditor`  
`class FUnrealMutableModelBulkWriterEditor : public UE::Mutable::Private::FModelWriter`  
_L132-153_
- inherits: `UE::Mutable::Private::FModelWriter`
- desc: Implementation of a mutable streamer using bulk storage.
- L136 _public prototype_ `FUnrealMutableModelBulkWriterEditor(FArchive* InMainDataArchive = nullptr, FArchive* InStreamedDataArchive = nullptr);`
- L139 _public prototype_ `void OpenWriteFile(uint32 BlockKey, bool bIsStreamable) override;` — UE::Mutable::Private::FModelWriter interface
- L140 _public prototype_ `void Write(const void* pBuffer, uint64 size) override;`
- L141 _public prototype_ `void CloseWriteFile() override;`
- L146 _protected member_ `FArchive* MainDataArchive = nullptr;` — Non-owned pointer to an archive where we'll store the main model data (non-streamable)
- L149 _protected member_ `FArchive* StreamedDataArchive = nullptr;` — Non-owned pointer to an archive where we'll store the resouces (streamable)
- L151 _protected member_ `FArchive* CurrentWriteFile = nullptr;`

#### class `FUnrealMutableModelBulkWriterCook`  
`class FUnrealMutableModelBulkWriterCook : public UE::Mutable::Private::FModelWriter`  
_L157-178_
- inherits: `UE::Mutable::Private::FModelWriter`
- desc: Implementation of a mutable streamer using bulk storage.
- L161 _public prototype_ `FUnrealMutableModelBulkWriterCook(FArchive* InMainDataArchive = nullptr, UE::Mutable::Private::FModelStreamableData* InStreamedData = nullptr);`
- L164 _public prototype_ `void OpenWriteFile(uint32 BlockKey, bool bIsStreamable) override;` — UE::Mutable::Private::FModelWriter interface
- L165 _public prototype_ `void Write(const void* pBuffer, uint64 size) override;`
- L166 _public prototype_ `void CloseWriteFile() override;`
- L171 _protected member_ `FArchive* MainDataArchive = nullptr;` — Non-owned pointer to an archive where we'll store the main model data (non-streamable)
- L174 _protected member_ `UE::Mutable::Private::FModelStreamableData* StreamedData = nullptr;` — Non-owned pointer to an archive where we'll store the resouces (streamable)
- L176 _protected member_ `uint32 CurrentKey = 0;`
- L177 _protected member_ `bool CurrentIsStreamable = false;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Mutable` (scope `UE`)
- L17 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/CustomizableObject/Internal/MuCO/UnrealPortabilityHelpers.h` (Internal)


#### Free symbols / members of external scopes

- L12 _macro_ `#define ObjectPtrWrap(X) X`
- L13 _macro_ `#define ObjectPtrDecay(X) X`
- L24 _macro_ `#define UE_MUTABLE_GET_CLASS_PATHNAME(X) X->GetClassPathName()`
- L25 _macro_ `#define UE_MUTABLE_GET_CLASSPATHS(X) X.ClassPaths`
- L26 _macro_ `#define UE_MUTABLE_OBJECTPATH(X) FSoftObjectPath(X)`
- L27 _macro_ `#define UE_MUTABLE_TOPLEVELASSETPATH(X,Y) FTopLevelAssetPath(X, Y)`
- L28 _macro_ `#define UE_MUTABLE_ASSETCLASS(X) X.AssetClassPath`
- L29 _macro_ `#define UE_MUTABLE_GETOBJECTPATH(X) X.GetObjectPathString()`
- L31 _macro_ `#define UE_MUTABLE_SETSKINNEDASSET(X,Y) X->SetSkinnedAsset(Y)`
- L32 _macro_ `#define UE_MUTABLE_GETSKELETALMESHASSET(X) X->GetSkeletalMeshAsset()`
- L36 _macro_ `#define USkinnedAsset USkeletalMesh`
- L38 _macro_ `#define UE_MUTABLE_GET_CLASS_PATHNAME(X) X->GetFName()`
- L39 _macro_ `#define UE_MUTABLE_GET_CLASSPATHS(X) X.ClassNames`
- L40 _macro_ `#define UE_MUTABLE_OBJECTPATH(X) *X`
- L41 _macro_ `#define UE_MUTABLE_TOPLEVELASSETPATH(X,Y) (Y)`
- L42 _macro_ `#define UE_MUTABLE_ASSETCLASS(X) X.AssetClass`
- L43 _macro_ `#define UE_MUTABLE_GETOBJECTPATH(X) X.ObjectPath.ToString()`
- L45 _macro_ `#define UE_MUTABLE_SETSKINNEDASSET(X,Y) X->SetSkeletalMesh(Y)`
- L46 _macro_ `#define UE_MUTABLE_GETSKELETALMESHASSET(X) X->SkeletalMesh`

### `Plugins/Mutable/Source/CustomizableObject/Internal/MuCO/UnrealToMutableTextureConversionUtils.h` (Internal)


#### enum `EMutableMeshConversionFlags`  
`enum class EMutableMeshConversionFlags : uint8`  
_L14-35_
- desc: Flags that can influence the mesh conversion
- L17 _public enumerator_ `None = 0`
- L19 _public enumerator_ `IgnoreSkinning = 1 << 0` — Ignore the skeleton and skinning
- L22 _public enumerator_ `IgnorePhysics = 1 << 1` — Ignore Physics assets
- L25 _public enumerator_ `IgnoreMorphs = 1 << 2` — Ignore Morphs
- L28 _public enumerator_ `IgnoreTexCoords = 1 << 3` — Ignore Texture coordinates
- L31 _public enumerator_ `IgnoreAUD = 1 << 4` — Ignore AssetUserData
- L34 _public enumerator_ `AddMorphsAsRealTime = 1 << 5` — Add morphs as realtime morphs.

#### struct `FMutableSourceTextureData`  
`struct FMutableSourceTextureData`  
_L52-74_
- L54 _public prototype_ `FMutableSourceTextureData() = default;`
- L56 _public prototype_ `FMutableSourceTextureData(const UTexture2D& Texture);`
- L58 _public prototype_ `FTextureSource& GetSource();`
- L60 _public prototype_ `bool GetFlipGreenChannel() const;`
- L62 _public prototype_ `bool HasAlphaChannel() const;`
- L64 _public prototype_ `bool GetCompressionForceAlpha() const;`
- L66 _public prototype_ `bool IsNormalComposite() const;`
- L69 _private member_ `FTextureSource Source;`
- L70 _private member_ `bool bFlipGreenChannel = false;`
- L71 _private member_ `bool bHasAlphaChannel = false;`
- L72 _private member_ `bool bCompressionForceAlpha = false;`
- L73 _private member_ `bool bIsNormalComposite = false;`

#### struct `FMutableSourceMeshData`  
`struct FMutableSourceMeshData`  
_L80-114_
- L83 _public member_ `TSoftObjectPtr<UStreamableRenderAsset> Mesh;` — Assets involved in the conversion.
- L84 _public member_ `TSoftClassPtr<UAnimInstance> AnimInstance;`
- L85 _public member_ `TSoftObjectPtr<UStreamableRenderAsset> TableReferenceSkeletalMesh;`
- L87 _public member_ `UE::Mutable::Private::FComponentId ComponentId = INDEX_NONE;`
- L90 _public member_ `int8 BaseLODIndex = INDEX_NONE;` — Selection of the mesh section
- L91 _public member_ `int8 BaseSectionIndex = INDEX_NONE;`
- L92 _public member_ `int8 LODOffset = INDEX_NONE;`
- L95 _public member_ `EMutableMeshConversionFlags Flags = EMutableMeshConversionFlags::None;` — Required mesh properties.
- L98 _public member_ `bool bUseAllRealTimeMorphs = false;` — Required realtime mesh morphs.
- L99 _public member_ `TArray<FString> UsedRealTimeMorphTargetNames;`
- L102 _public member_ `bool bOnlyConnectedLOD = false;`
- L105 _public member_ `const UObject* MessageContext = nullptr;` — Context for log messages.
- L107 _public member_ `FString OptionalMessageInfo;`
- L109 _public member_ `FName AnimBPSlotName;`
- L111 _public member_ `FGameplayTagContainer GameplayTags;`
- L113 _public prototype_ `bool operator==(const FMutableSourceMeshData&) const = default;`

#### enum `EUnrealToMutableConversionError`  
`enum class EUnrealToMutableConversionError`  
_L132-139_
- L134 _public enumerator_ `Success`
- L135 _public enumerator_ `UnsupportedFormat`
- L136 _public enumerator_ `CompositeImageDimensionMismatch`
- L137 _public enumerator_ `CompositeUnsupportedFormat`
- L138 _public enumerator_ `Unknown`

#### class `FMeshConversionContext`  
`class FMeshConversionContext`  
_L144-161_
- desc: Mesh conversion context.
- L147 _public prototype_ `FMeshConversionContext() = default;`
- L152 _public member_ `FMutableSourceMeshData Source;` — Source Data
- L153 _public member_ `FString MorphName;`
- L155 _public member_ `TSharedPtr<FMutableCompilationContext> CompilationContext;`
- L158 _public member_ `TArray<TStrongObjectPtr<UObject>> ReferencedObjects;` — Keep strong references to meshes and other UObjects involved in the conversion
- L160 _public member_ `UE::Mutable::Private::TManagedPtr<UE::Mutable::Private::FMesh> Result;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CUSTOMIZABLEOBJECT_API`
- L46 _namespace_ `namespace UE`
- L46 _namespace_ `namespace Mutable` (scope `UE`)
- L46 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L117 _function_ `inline uint32 GetTypeHash(const FMutableSourceMeshData& Key)`
- L141 _prototype_ `EUnrealToMutableConversionError ConvertTextureUnrealSourceToMutable(UE::Mutable::Private::FImage* OutResult, FMutableSourceTextureData&, uint8 MipmapsToSkip, bool bLoadMipTail);`

### `Plugins/Mutable/Source/CustomizableObject/Private/MuCO/CustomizableObjectDGGUI.h` (Private)


#### class `UDGGUI`  
`class UDGGUI : public UUserWidget`  
_L18-30_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType, Blueprintable)`
- inherits: `UUserWidget`
- L23 _public prototype_ `class UCustomizableObjectInstanceUsage* GetCustomizableObjectInstanceUsage();` — `UFUNCTION(BlueprintImplementableEvent, Category = "DGGUI")`
- L26 _public prototype_ `void SetCustomizableObjectInstanceUsage(class UCustomizableObjectInstanceUsage* CustomizableObjectInstanceUsage);` — `UFUNCTION(BlueprintImplementableEvent, Category = "DGGUI")`
- L28 _public prototype_ `static void OpenDGGUI(const int32 SlotID, UCustomizableObjectInstanceUsage* SelectedCustomizableObjectInstanceUsage, const UWorld* CurrentWorld, const int32 PlayerIndex = 0);`
- L29 _public prototype_ `static bool CloseExistingDGGUI(const UWorld* CurrentWorld);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECT_API`

### `Plugins/Mutable/Source/CustomizableObject/Private/MuCO/CustomizableObjectMeshUpdate.h` (Private)


#### struct `FMutableMeshUpdateContext`  
`struct FMutableMeshUpdateContext`  
_L29-45_
- desc: Runtime data used during a mutable mesh LOD update
- L32 _public member_ `TSharedPtr<FMutableMeshContext> MeshContext;` — Mesh update context
- L35 _public member_ `TArray<UE::Mutable::Private::TManagedPtr<const UE::Mutable::Private::FLOD>> LODs;` — Meshes generated per LOD
- L39 _public member_ `int32 CurrentFirstLODIdx = INDEX_NONE;` — The resident first LOD resource index.With domain = [0, ResourceState.NumLODs[.NOT THE ASSET LOD INDEX!
- L42 _public member_ `int32 PendingFirstLODIdx = INDEX_NONE;` — The requested first LOD resource index. With domain = [0, ResourceState.NumLODs[. NOT THE ASSET LOD INDEX!
- L44 _public member_ `int32 AssetLODBias = 0;`

#### class `FCustomizableObjectMeshStreamIn`  
`class FCustomizableObjectMeshStreamIn : public FSkeletalMeshStreamIn`  
_L54-87_
- inherits: `FSkeletalMeshStreamIn`
- desc: This class provides a framework for loading the LODs of CustomizableObject skeletal meshes. Each thread essentially calls Tick() until the job is done. The object can be safely deleted when IsCompleted() returns true.
- L57 _public prototype_ `FCustomizableObjectMeshStreamIn( const UCustomizableObjectSkeletalMesh* InMesh, EThreadType CreateResourcesThread);`
- L61 _public prototype_ `void OnUpdateMeshFinished();`
- L64 _public prototype_ `virtual void Abort() override;` — Decrement TaskSynchronization counter and cancel pending low-priority tasks.
- L68 _private prototype_ `void DoInitiate(const FContext& Context);`
- L70 _private prototype_ `void DoConvertResources(const FContext& Context);`
- L72 _private prototype_ `void DoCreateBuffers(const FContext& Context);`
- L75 _private prototype_ `void RequestMeshUpdate(const FContext& Context);` — Creates a MeshUpdate task to generate the meshes for the LODs to stream in.
- L78 _private prototype_ `void ConvertMesh(const FContext& Context, bool& bOutMarkRenderStateDirty);` — Converts from UE::Mutable::Private::FMesh to FSkeletalMeshLODRenderData.
- L80 _private prototype_ `void MarkRenderStateDirty(const FContext& Context);`
- L83 _private member_ `TSharedPtr<FMutableMeshUpdateContext> UpdateContext;` — Data of the MeshUpdate.
- L86 _private member_ `uint32 MutableTaskId = 0;` — MeshUpdate task Id to cancel the task if the stream in task is aborted.

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Mutable` (scope `UE`)
- L21 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L47 _externvar_ `extern template class TRenderAssetUpdate<FSkelMeshUpdateContext>;`

### `Plugins/Mutable/Source/CustomizableObject/Private/MuCO/ExternalOperationProvider.h` (Private)


#### class `UE::Mutable::Private::FExternalOperationProvider`  
`class FExternalOperationProvider : public IExternalOperationProvider, public FGCObject`  
_L16-33_
- inherits: `IExternalOperationProvider,FGCObject`
- L19 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L20 _public function_ `virtual FString GetReferencerName() const override`
- L26 _public prototype_ `virtual const FInstancedStruct& Get(FOperation::ADDRESS Address) const override;` — IExternalOperationProvider interface
- L29 _public prototype_ `FExternalOperationProvider(UModelResources& InModelResources);` — Own interface
- L32 _private member_ `TMap<FOperation::ADDRESS, FInstancedStruct> ExternalOperations;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/CustomizableObject/Private/MuCO/MutableStreamRequest.h` (Private)


#### class `FMutableStreamRequest`  
`class FMutableStreamRequest`  
_L25-81_
- desc: Stream data from .mut or Bulk files. Can be destroyed at any time, even when the stream request is in progress.
- L28 _public prototype_ `FMutableStreamRequest(const TSharedPtr<FModelStreamableBulkData>& InModelStreamableBulkData);`
- L30 _public prototype_ `const TSharedPtr<FModelStreamableBulkData>& GetModelStreamableBulkData() const;`
- L33 _public prototype_ `void AddBlock(const FMutableStreamableBlock& Block, UE::Mutable::Private::EStreamableDataType DataType, uint16 InResourceType, TArrayView<uint8> AllocatedMemoryView);` — Add a block to stream.
- L36 _public prototype_ `UE::Tasks::FTask Stream();` — Stream the previously requested data.
- L39 _public prototype_ `void Cancel();` — Cancel pending requests
- L57 _private member_ `const TSharedPtr<FModelStreamableBulkData> ModelStreamableBulkData;`
- L59 _private member_ `TArray<uint32> OpenFilesIds;`
- L60 _private member_ `TArray<TSharedPtr<IAsyncReadFileHandle>> OpenFileHandles;`
- L76 _private member_ `TSharedRef<FHeapMemory> HeapMemory = MakeShared<FHeapMemory>();`
- L78 _private member_ `TArray<FBlockReadInfo> BlockReadInfos;`
- L80 _private member_ `bool bIsStreaming = false;`

#### struct `FMutableStreamRequest::FBlockReadInfo`  
`struct FBlockReadInfo`  
_L42-55_
- L44 _public prototype_ `FBlockReadInfo() = default;`
- L45 _public prototype_ `FBlockReadInfo(uint64 InOffset, IAsyncReadFileHandle* InFileHandle, TArrayView<uint8>& InAllocatedMemoryView, uint32 InFileId, UE::Mutable::Private::EStreamableDataType InDataType, uint16 InResourceType, uint16 InResourceFlags);`
- L47 _public member_ `uint64 Offset;`
- L48 _public member_ `IAsyncReadFileHandle* FileHandle;`
- L49 _public member_ `TArrayView<uint8> AllocatedMemoryView;`
- L50 _public member_ `uint32 FileId;`
- L51 _public member_ `uint16 ResourceType;`
- L52 _public member_ `uint16 ResourceFlags;`
- L54 _public member_ `UE::Mutable::Private::EStreamableDataType DataType;`

#### struct `FMutableStreamRequest::FHeapMemory`  
`struct FHeapMemory`  
_L62-74_
- L64 _public member_ `TArray<UE::Tasks::FTaskEvent> CompletionEvents;`
- L65 _public member_ `TArray<TSharedPtr<IAsyncReadRequest>> ReadRequests;`
- L66 _public member_ `TArray<TSharedPtr<IBulkDataIORequest>> BulkReadRequests;`
- L69 _public member_ `TSharedPtr<UE::DerivedData::FRequestOwner> DDCRequestOwner;`
- L72 _public member_ `bool bIsCancelled = false;`
- L73 _public member_ `FCriticalSection ReadRequestLock;`

#### Free symbols / members of external scopes

- L14 _variable_ `constexpr int32 BulkDataFileOffset = #if WITH_EDITOR sizeof(MutableCompiledDataStreamHeader);`

### `Plugins/Mutable/Source/CustomizableObject/Public/MuCO/CustomizableObject.h` (Public)


#### struct `FFParameterOptionsTags`  
`struct FFParameterOptionsTags`  
_L41-48_
- reflection: `USTRUCT()`
- L47 _public member_ `TArray<FString> Tags;` — `UPROPERTY(Category = "CustomizablePopulation", EditAnywhere)` — List of tags of a Parameter Options

#### struct `FParameterTags`  
`struct FParameterTags`  
_L52-63_
- reflection: `USTRUCT()`
- L58 _public member_ `TArray<FString> Tags;` — `UPROPERTY(Category = "CustomizablePopulation", EditAnywhere)` — List of tags of a parameter
- L62 _public member_ `TMap<FString, FFParameterOptionsTags> ParameterOptions;` — `UPROPERTY(Category = "CustomizablePopulation", EditAnywhere)` — Map of options available for a parameter can have and their tags

#### struct `FMutableLODSettings`  
`struct FMutableLODSettings`  
_L67-97_
- reflection: `USTRUCT()`
- L73 _public member_ `FPerPlatformInt MinLOD;` — `UPROPERTY(EditAnywhere, Category = LODSettings, meta = (DisplayName = "Minimum LOD"))` — Minimum LOD to render per Platform.
- L77 _public member_ `FPerQualityLevelInt MinQualityLevelLOD;` — `UPROPERTY(EditAnywhere, Category = LODSettings, meta = (DisplayName = "Quality Level Minimum LOD"))` — Minimum LOD to render per Quality level.
- L83 _public member_ `bool bOverrideLODStreamingSettings = true;` — `UPROPERTY(EditAnywhere, Category = LODSettings, meta = (DisplayName = "Override LOD Streaming Settings"))` — Override the LOD Streaming settings from the reference skeletal meshes.
- L90 _public member_ `FPerPlatformBool bEnableLODStreaming = true;` — `UPROPERTY(EditAnywhere, Category = LODSettings, meta = (EditCondition = "bOverrideLODStreamingSettings", DisplayName = "Enable LOD Streaming"))` — Enabled: streaming LODs will trigger automatic updates to generate and discard LODs. Streaming may decrease the amount of memory used, but will stress the CPU and Streaming of resources. Keep in mind that, even though updates may be faster depending on the amount of LODs to generate, there may be more updates to process. Disabled: all LODs will be generated at once. It may increase the amount of memory used by the meshes and the generation may take longer, but less updates will be required.
- L94 _public member_ `FPerPlatformInt NumMaxStreamedLODs = MAX_MESH_LOD_COUNT;` — `UPROPERTY(EditAnywhere, Category = LODSettings, meta = (EditCondition = "bOverrideLODStreamingSettings"))` — Limit the number of LODs to stream. A value of 0 is the same as disabling streaming of LODs.

#### struct `FCompileCallbackParams`  
`struct FCompileCallbackParams`  
_L101-124_
- reflection: `USTRUCT(BlueprintType)`
- L107 _public member_ `bool bRequestFailed = false;` — `UPROPERTY(BlueprintReadOnly, Category = Compile)` — The compile request has failed. See output log for more details. False if the request has been skipped.
- L111 _public member_ `bool bWarnings = false;` — `UPROPERTY(BlueprintReadOnly, Category = Compile)` — The compile request has finished with warnings. False if the request has been skipped.
- L115 _public member_ `bool bErrors = false;` — `UPROPERTY(BlueprintReadOnly, Category = Compile)` — The compile request has finished with errors. False if the request has been skipped.
- L119 _public member_ `bool bSkipped = false;` — `UPROPERTY(BlueprintReadOnly, Category = Compile)` — The compilation has been skipped due to Compile Parameters.
- L123 _public member_ `bool bCompiled = false;` — `UPROPERTY(BlueprintReadOnly, Category = Compile)` — The Customizable Object is compiled.

#### struct `FCompileParams`  
`struct FCompileParams`  
_L133-169_
- reflection: `USTRUCT(BlueprintType)`
- L139 _public member_ `bool bSkipIfCompiled = false;` — `UPROPERTY(BlueprintReadWrite, Category = Compile)` — If true, skip the compilation if the Customizable Object is already compiled.
- L143 _public member_ `bool bSkipIfNotOutOfDate = true;` — `UPROPERTY(BlueprintReadWrite, Category = Compile)` — If true, skip the compilation if the Customizable Object or its contents are not out of date (child Customizable Objects, Data Tables, referenced Materials...).
- L147 _public member_ `bool bGatherReferences = false;` — `UPROPERTY(BlueprintReadWrite, Category = Compile)` — Gathers all asset references used in this Customizable Object. Marks the object as modified.
- L151 _public member_ `bool bAsync = true;` — `UPROPERTY(BlueprintReadWrite, Category = Compile)` — If true, compile the Customizable Object asynchronously. If synchronously and the Customizable Object is not ready the compilation will fail.
- L155 _public member_ `TObjectPtr<UCustomizableObjectInstance> CompileOnlySelectedInstance = nullptr;` — `UPROPERTY(BlueprintReadWrite, Category = Compile)` — If assigned, compile the Customizable Object only the selected parameter of the given Instance.
- L158 _public member_ `ECustomizableObjectOptimizationLevel OptimizationLevel = ECustomizableObjectOptimizationLevel::FromCustomizableObject;` — `UPROPERTY(BlueprintReadWrite, Category = Compile)`
- L161 _public member_ `ECustomizableObjectTextureCompression TextureCompression = ECustomizableObjectTextureCompression::Fast;` — `UPROPERTY(BlueprintReadWrite, Category = Compile)`
- L165 _public member_ `FCompileDelegate Callback;` — `UPROPERTY(BlueprintReadWrite, Category = Compile)` — Called once the compilation request has finished (successfully or not).
- L168 _public member_ `FCompileNativeDelegate CallbackNative;` — See Callback.

#### class `UCustomizableObject`  
`class UCustomizableObject : public UObject`  
_L173-508_
- reflection: `UCLASS(MinimalAPI, BlueprintType, config=Engine)`
- inherits: `UObject`
- L180 _public prototype_ `UCustomizableObject();`
- L186 _private member_ `TObjectPtr<USkeletalMesh> ReferenceSkeletalMesh_DEPRECATED;` — `UPROPERTY()`
- L189 _private member_ `TArray<TObjectPtr<USkeletalMesh>> ReferenceSkeletalMeshes_DEPRECATED;` — `UPROPERTY()`
- L200 _public member_ `TObjectPtr<UObject> VersionBridge;` — `UPROPERTY(EditAnywhere, Category = Versioning)` — Optional Version Bridge asset. Used to decide which Mutable child Customizable Objects and Data Table rows must be included in a compilation/cook. An asset will be included if the struct/column version matches the game-specific system version. The provided asset must implement ICustomizableObjectVersionBridgeInterface.
- L209 _public member_ `FInstancedStruct VersionStruct;` — `UPROPERTY(EditAnywhere, Category = Versioning)` — Optional struct. Used to define which version this child Customizable Object belongs to. It will be used during cook/compilation to decide whether this Customizable Object should be included in the final compiled Customizable Object. To work, the root Customizable Object must have a Version Bridge.
- L214 _public member_ `FMutableLODSettings LODSettings;` — `UE_DEPRECATED(5.6, "Moved to Mesh Component Node")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage="Moved to Mesh Component Node"))`
- L219 _public member_ `bool bEnableUseRefSkeletalMeshAsPlaceholder = true;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject, DisplayName = "Use Reference Skeletal Mesh As Placeholder")` — true to use the Reference Skeletal Mesh as a placeholder while the Generated Skeletal Mesh is not ready. If false, a null mesh will be used to replace the discarded mesh due to 'ReplaceDiscardedWithReferenceMesh' being enabled.
- L224 _public member_ `bool bEnableMeshCache = false;` — `UPROPERTY(EditAnywhere, Category = CustomizableObject)` — If true, reuse previously generated USkeletalMesh (if still valid and the the number of LOD have not changed) USkeletalMeshes are only reused between the same CO.
- L229 _private member_ `FCompilationOptions_DEPRECATED CompileOptions_DEPRECATED;` — `UPROPERTY()`
- L232 _private member_ `bool bEnableRealTimeMorphTargets = false;` — `UPROPERTY(EditAnywhere, Category = CompileOptions)`
- L235 _private member_ `bool bEnable16BitBoneWeights = false;` — `UPROPERTY(EditAnywhere, Category = CompileOptions)`
- L238 _private member_ `bool bEnableAltSkinWeightProfiles = false;` — `UPROPERTY(EditAnywhere, Category = CompileOptions)`
- L241 _private member_ `bool bEnablePhysicsAssetMerge = false;` — `UPROPERTY(EditAnywhere, Category = CompileOptions)`
- L244 _private member_ `bool bUseLegacyLayouts = false;` — `UPROPERTY(EditAnywhere, Category = CompileOptions)`
- L248 _private member_ `bool bEnableAnimBpPhysicsAssetsManipulation = false;` — `UPROPERTY(EditAnywhere, Category = CompileOptions)` — Experimental
- L254 _private member_ `bool bDisableTableMaterialsParentCheck = false;` — `UPROPERTY(EditAnywhere, Category = CompileOptions)` — Disabling the Table Materials parent material check will let the user use any material regardless of its parent when connecting a material from a table column to a material node. Warning! But it will not check if the table material channels connected to the Material node exist in the actual material used in the Instance, and will fail silently at runtime when setting the value of those channels if they don't exist.
- L258 _private member_ `EMutableCompileMeshType MeshCompileType = EMutableCompileMeshType::LocalAndChildren;` — `UPROPERTY(EditAnywhere, Category = CompileOptions)` — Options when compiling this customizable object (see EMutableCompileMeshType declaration for info)
- L262 _private member_ `TArray<TSoftObjectPtr<UCustomizableObject>> WorkingSet;` — `UPROPERTY(EditAnywhere, Category = CompileOptions)` — Array of elements to use with compile option CompileType = WorkingSet
- L266 _private member_ `TObjectPtr<UEdGraph> Source;` — `UPROPERTY()` — Editor graph
- L270 _private member_ `FGuid VersionId;` — `UPROPERTY()` — Used to verify the derived data matches this version of the Customizable Object.
- L276 _public prototype_ `int32 GetComponentCount() const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)` — Get the number of components this Customizable Object has.
- L282 _public prototype_ `FName GetComponentName(int32 ComponentIndex) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)` — Return the name of the component. @param ComponentIndex [0 - GetComponentCount). Index may not represent the same component between runs. To identify them use the name. @return NAME_None if the component does not exist.
- L286 _public prototype_ `int32 GetParameterCount() const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)` — Get the number of parameters available in instances of this object.
- L289 _public prototype_ `bool ContainsParameter(const FString& ParameterName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)`
- L293 _public prototype_ `EMutableParameterType GetParameterTypeByName(const FString& Name) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)` — Get the type of a parameter from its name.
- L296 _public prototype_ `const FString& GetParameterName(int32 ParamIndex) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)`
- L300 _public prototype_ `int32 GetEnumParameterNumValues(const FString& ParameterName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)` — If the given parameter is enum int parameter, return how many possible values an enum parameter has. Otherwise, return 0.
- L304 _public prototype_ `const FString& GetEnumParameterValue(const FString& ParameterName, int32 ValueIndex) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)` — Gets the Name of the value at position ValueIndex in the list of available values for the int parameter.
- L308 _public prototype_ `bool ContainsEnumParameterValue(const FString& ParameterName, const FString Value) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)` — Return true if the enum parameter contains this value a possible option.
- L312 _public prototype_ `USkeletalMesh* GetComponentMeshReferenceSkeletalMesh(const FName& Name) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)` — DEPRECATED: Use GetSkeletalMeshComponentReferenceSkeletalMesh instead.
- L316 _public prototype_ `USkeletalMesh* GetSkeletalMeshComponentReferenceSkeletalMesh(const FName& ComponentName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)` — Given a Mesh Component name, return its reference Skeletal Mesh.
- L322 _public prototype_ `float GetFloatParameterDefaultValue(const FString& ParameterName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)` — Get the default value of a parameter of type Float. @param ParameterName The name of the Float parameter to get the default value of. @return The default value of the provided parameter name.
- L328 _public prototype_ `int32 GetEnumParameterDefaultValue(const FString& ParameterName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)` — Get the default value of a parameter of type Int. @param ParameterName The name of the Int parameter to get the default value of. @return The default value of the provided parameter name.
- L334 _public prototype_ `bool GetBoolParameterDefaultValue(const FString& ParameterName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)` — Get the default value of a parameter of type Bool. @param ParameterName The name of the Bool parameter to get the default value of. @return The default value of the provided parameter name.
- L340 _public prototype_ `FLinearColor GetColorParameterDefaultValue(const FString& ParameterName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)` — Get the default value of a parameter of type Color. @param ParameterName The name of the Color parameter to get the default value of. @return The default value of the provided parameter name.
- L346 _public prototype_ `FVector4f GetVectorParameterDefaultValue(const FString& ParameterName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)` — Get the default value of a parameter of type Vector. @param ParameterName The name of the Vector parameter to get the default value of. @return The default value of the provided parameter name.
- L352 _public prototype_ `FTransform GetTransformParameterDefaultValue(const FString& ParameterName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)` — Get the default value of a parameter of type Transform. @param ParameterName The name of the Transform parameter to get the default value of. @return The default value of the provided parameter name.
- L358 _public prototype_ `FCustomizableObjectProjector GetProjectorParameterDefaultValue(const FString& ParameterName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)` — Get the default value of a projector with the provided name @param ParameterName The name of the parameter to get the default value of. @return A data structure containing all the default data for the targeted projector parameter.
- L363 _public prototype_ `UTexture* GetTextureParameterDefaultValue(const FString& InParameterName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)` — Get the default value of a parameter of type Texture. @param InParameterName The name of the Texture parameter to get the default value of.
- L368 _public prototype_ `USkeletalMesh* GetSkeletalMeshParameterDefaultValue(const FString& ParameterName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)` — Get the default value of a parameter of type Skeletal Mesh. @param ParameterName The name of the Mesh parameter to get the default value of.
- L373 _public prototype_ `UMaterialInterface* GetMaterialParameterDefaultValue(const FString& ParameterName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)` — Get the default value of a parameter of type Material. @param ParameterName The name of the Material parameter to get the default value of.
- L378 _public prototype_ `FInstancedStruct GetExternalTypeParameterDefaultValue(const FString& ParameterName) const;` — Get the default value of a parameter of type External Type. @param ParameterName The name of the External Type parameter to get the default value of. @return The default value of the provided parameter name.
- L384 _public prototype_ `bool IsParameterMultidimensional(UPARAM(DisplayName = "Parameter Name") const FString& InParamet` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)` — Return true if the parameter at the index provided is multidimensional. @param InParameterName The name of the parameter to check. @return True if the parameter is multidimensional and false if it is not.
- L388 _public prototype_ `void Compile(const FCompileParams& Params);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)` — Compile the Customizable Object.
- L396 _public prototype_ `bool ConditionalAutoCompile();` — DEPRECATED. Use Compile instead. Compile the object if Automatic Compilation is enabled and has not been already compiled. Automatic compilation can be enabled/disabled in the Mutable's Plugin Settings. @return true if compiled
- L400 _public prototype_ `virtual void PostLoad() override;` — UObject interface
- L401 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L404 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L405 _public prototype_ `virtual FString GetDesc() override;`
- L406 _public prototype_ `virtual bool IsEditorOnly() const override;`
- L407 _public prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L408 _public prototype_ `virtual void PostSaveRoot(FObjectPostSaveRootContext ObjectSaveContext) override;`
- L409 _public prototype_ `virtual void PostRename(UObject* OldOuter, const FName OldName) override;`
- L410 _public prototype_ `virtual void BeginCacheForCookedPlatformData(const ITargetPlatform* TargetPlatform) override;`
- L411 _public prototype_ `virtual bool IsCachedCookedPlatformDataLoaded(const ITargetPlatform* TargetPlatform) override;`
- L416 _public prototype_ `int32 GetStateCount() const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)` — Return the number of object states that are defined in the CustomizableObject.
- L419 _public prototype_ `FString GetStateName(int32 StateIndex) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)`
- L423 _public prototype_ `int32 GetStateParameterCount(const FString& StateName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)` — Return the number of parameters that are editable at runtime for a specific state.
- L427 _public prototype_ `FString GetStateParameterName(const FString& StateName, int32 ParameterIndex) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)` — Return the name of one of the state's runtime parameters, by its index (from 0 to GetStateParameterCount - 1).
- L431 _public prototype_ `FMutableParamUIMetadata GetParameterUIMetadata(const FString& ParamName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)` — Return the metadata associated to a parameter.
- L435 _public prototype_ `FMutableParamUIMetadata GetEnumParameterValueUIMetadata(const FString& ParamName, const FString& OptionName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)` — Return the metadata associated to the given enum parameter value.
- L439 _public prototype_ `ECustomizableObjectGroupType GetEnumParameterGroupType(const FString& ParamName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)` — Returns the group type of the given integer parameter
- L443 _public prototype_ `FMutableStateUIMetadata GetStateUIMetadata(const FString& StateName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)` — Return the metadata associated to a state.
- L448 _public prototype_ `TArray<TSoftObjectPtr<UDataTable>> GetEnumParameterValueDataTable(const FString& ParamName, const FString& Value);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)` — Return the DataTables used by the given parameter and its value (if any).
- L455 _private member_ `TArray<FString> CustomizableObjectClassTags;` — `UPROPERTY()` — Array to store the selected Population Class tags for this Customizable Object
- L459 _private member_ `TArray<FString> PopulationClassTags;` — `UPROPERTY()` — Array to store all the Population Class tags
- L463 _private member_ `TMap<FString, FParameterTags> CustomizableObjectParametersTags;` — `UPROPERTY()` — Map of parameters available for the Customizable Object and their tags
- L473 _private member_ `bool bIsChildObject = false;` — `UPROPERTY()` — True if this object references a parent object. This is used basically to exclude this object from cooking. This is actually derived from the source graph object node pointing to another object or not, but it needs to be cached here because the source graph is not always available. For old objects this may be false even if they are child objects until they are resaved, but that is the conservative case and shouldn't cause a problem.
- L478 _public prototype_ `FPostCompileDelegate& GetPostCompileDelegate();`
- L483 _public prototype_ `UCustomizableObjectInstance* CreateInstance();` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)` — Create a new instance of this object. The instance parameters will be initialized with the object default values.
- L488 _public prototype_ `bool IsCompiled() const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)` — Check if the CustomizableObject asset has been compiled. This will always be true in a packaged game, but it could be false in the editor. It may return false due to the Customizable Object still being loaded.
- L492 _public prototype_ `bool IsLoading() const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)` — Return true if the Customizable Object is still being loaded. It may take a few frames to load the Customizable Object.
- L497 _public prototype_ `bool IsChildObject() const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)` — Return true if this Customizable Object has references to a parent Customizable Object. Only root Customizable Objects will return false.
- L500 _public prototype_ `const UCustomizableObjectPrivate* GetPrivate() const;`
- L502 _public prototype_ `UCustomizableObjectPrivate* GetPrivate();`
- L507 _private member_ `TObjectPtr<UCustomizableObjectPrivate> Private;` — `UPROPERTY(Instanced)`

#### Free symbols / members of external scopes

- L31 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMutable, Log, All);`
- L34 _delegate_ `DECLARE_MULTICAST_DELEGATE(FPostCompileDelegate) extern TAutoConsoleVariable<bool> CVarMutableAsyncCook;`
- L34 _prototype_ `DECLARE_MULTICAST_DELEGATE(FPostCompileDelegate) extern TAutoConsoleVariable<bool> CVarMutableAsyncCook;`
- L127 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FCompileDelegate, const FCompileCallbackParams&, Params);`
- L127 _prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FCompileDelegate, const FCompileCallbackParams&, Params);`
- L129 _delegate_ `DECLARE_DELEGATE_OneParam(FCompileNativeDelegate, const FCompileCallbackParams&);`
- L129 _prototype_ `DECLARE_DELEGATE_OneParam(FCompileNativeDelegate, const FCompileCallbackParams&);`

### `Plugins/Mutable/Source/CustomizableObject/Public/MuCO/CustomizableObjectExtension.h` (Public)


#### struct `FCustomizableObjectPinType`  
`struct FCustomizableObjectPinType`  
_L22-40_
- desc: A type of pin in the Mutable graph UI
- L33 _public member_ `FName Name;` — The identifier for this type, to be used internally Note that the same pin type names may be used by different extensions, so that extensions can interoperate with each other using extension-defined pin types. In other words, it's valid for one extension to create a new pin type and another extension to create nodes that use that type.
- L36 _public member_ `FText DisplayName;` — The display name for this type in the editor UI
- L39 _public member_ `FLinearColor Color;` — The color that will be used in the editor UI for this pin and any wires connected to it

#### struct `FObjectNodeInputPin`  
`struct FObjectNodeInputPin`  
_L43-69_
- desc: An input pin that will be added to Object nodes
- L46 _public member_ `FName PinType;` — This can be the name of a built-in pin type or an extension-defined FCustomizableObjectPinType
- L56 _public member_ `FName PinName;` — The internal name for the pin, to disambiguate it from other pins. Ensure this name is unique for object node pins created by the same extension. The system can automatically distinguish between pins with the same name across different extensions, so this doesn't need to be a globally unique name.
- L59 _public member_ `FText DisplayName;` — The name that will be displayed for the pin in the editor UI
- L68 _public member_ `bool bIsArray = false;` — Whether this pin accepts multiple inputs or not. Note that even if this is false, an Object node pin can still receive one input per Child Object node, so the extension still needs to handle receiving multiple inputs for a single pin.

#### class `UCustomizableObjectExtension`  
`class UCustomizableObjectExtension : public UObject`  
_L79-111_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: An extension that adds functionality to the Customizable Object system To create a new extension, make a subclass of this class and register it by calling ICustomizableObjectModule::Get().RegisterExtension().
- L84 _public function_ `virtual TArray<FCustomizableObjectPinType> GetPinTypes() const` — Returns any new pin types that are defined by this extension
- L87 _public function_ `virtual TArray<FObjectNodeInputPin> GetAdditionalObjectNodePins() const` — Returns the pins that this extension adds to Object nodes
- L100 _public function_ `virtual void OnSkeletalMeshCreated(FName ComponentName, USkeletalMesh* SkeletalMesh) const` — Called when a Skeletal Mesh asset is created @param InputPinData - The data for only the input pins *registered by this extension*. This helps to enforce separation between the extensions, so that they don't depend on each other. @param ComponentName - The component name of the Skeletal Mesh, for the case where the pin data is associated with a particular component. @param SkeletalMesh - The Skeletal Mesh that was created.
- L105 _public function_ `virtual void OnCustomizableObjectInstanceUsageUpdated(UCustomizableObjectInstanceUsage& Usage, TArray<TObjectPtr<const UObject>>& ExtensionData) const` — Called when a Customizable Object Instance Usage is being updated. @param Usage Customizable Object Instance Usage being updated.
- L110 _public function_ `virtual void OnCustomizableObjectInstanceUsageDiscarded(UCustomizableObjectInstanceUsage& Usage) const` — Called when a Customizable Object Instance Usage is being discarded. @param Usage Customizable Object Instance Usage being discarded.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/CustomizableObject/Public/MuCO/CustomizableObjectInstance.h` (Public)


#### enum `EPackageSaveResolutionType`  
`enum class EPackageSaveResolutionType : uint8`  
_L26-41_
- reflection: `UENUM()`
- desc: Represents what kind of saving procedure was performed to save the package
- L28 _public enumerator_ `None = 0`
- L31 _public enumerator_ `NewFile` — The package got saved as a new file.
- L34 _public enumerator_ `ReusedFile` — The package was already present on disk so it was used instead of creating a new one.
- L37 _public enumerator_ `Overriden UE_DEPRECATED(5.8, "This option is no longer used") UMETA(Hidden)` — The package was already present on disk so the old package was deleted and a new one was saved on its place
- L40 _public enumerator_ `UnableToOverride UE_DEPRECATED(5.8, "This option is no longer used") UMETA(Hidden)` — Error type : An override was required but due to an error or lack of user permission it could not be done.

#### struct `FBakedResourceData`  
`struct FBakedResourceData`  
_L48-103_
- reflection: `USTRUCT(BlueprintType, Blueprintable)`
- desc: Data structure that exposes the path to a baked package and also what type of save was performed (an override, a standard save with a new file...)
- L56 _public member_ `EPackageSaveResolutionType SaveType = EPackageSaveResolutionType::None;` — `UPROPERTY(BlueprintReadOnly, Category = CustomizableObjectInstanceBaker)` — The way the package represented by this object was saved onto disk.
- L63 _public member_ `FString AssetPath;` — `UPROPERTY(BlueprintReadOnly, Category = CustomizableObjectInstanceBaker)` — The path used by the saved package. EX : "/Game/baking_CO/BakeDir_Char/Part3/T_CharacterBake_Body_EyeBrown_Normal_2"
- L70 _public member_ `FString Prefix;` — `UPROPERTY(BlueprintReadOnly, Category = CustomizableObjectInstanceBaker)` — The section of the asset name that represents the asset type based prefix. EX : "T_", "M_", "SKEL_", "" ...
- L77 _public member_ `FString UserGivenName;` — `UPROPERTY(BlueprintReadOnly, Category = CustomizableObjectInstanceBaker)` — The section of the asset name that represents the name the user has requested for all the baked resources to have. EX : "CharacterBake_", "CO_ABC_", "MyTestBake_", "" ...
- L85 _public member_ `FString ComponentName;` — `UPROPERTY(BlueprintReadOnly, Category = CustomizableObjectInstanceBaker)` — The section of the asset name that represents the name of the component of the source asset that was baked. It can be empty in the case the resource is shared between multiple components. EX : "Body_", "A_", "B_", "" ...
- L94 _public member_ `FString ResourceName;` — `UPROPERTY(BlueprintReadOnly, Category = CustomizableObjectInstanceBaker)` — The section of the asset name that represents the name of the source resource that was baked. EX : "EyeBrown_Normal", "BodyTexture_4849745649878/", "AlbedoEyes_4756489*65", "BodyTexture" ... @note The substring is composed by the source object name and, in some cases, a suffix that contains the mutable resource generation hash used to be able to reuse baked mutable resources between baking runs.
- L102 _public member_ `FString UniqueAssetNameSuffix;` — `UPROPERTY(BlueprintReadOnly, Category = CustomizableObjectInstanceBaker)` — The section of the asset name that represents the suffix added in some cases to prevent name collisions during the bake. This is most likely to be empty. EX : "_2", "_1" , "" ...

#### struct `FCustomizableObjectInstanceBakeOutput`  
`struct FCustomizableObjectInstanceBakeOutput`  
_L111-126_
- reflection: `USTRUCT(BlueprintType, Blueprintable)`
- desc: Structure returned as output of the baking operation. May contain a filled collection of FBakedResourceData objects and also the success end state of the baking operation.
- L119 _public member_ `bool bWasBakeSuccessful = false;` — `UPROPERTY(BlueprintReadOnly, Category = CustomizableObjectInstanceBaker)` — Success state for the baking operation. True for success and false for failure.
- L125 _public member_ `TArray<FBakedResourceData> SavedPackages;` — `UPROPERTY(BlueprintReadOnly, Category = CustomizableObjectInstanceBaker)` — Collection of FBakedResourceData representing all saved packages during the baking operation. It may be empty if the operation failed.

#### struct `FBakingConfiguration`  
`struct FBakingConfiguration`  
_L136-213_
- reflection: `USTRUCT(BlueprintType, Blueprintable)`
- desc: Configuration data structure designed to serve as variable container for the customizable object instance baking methods.
- L142 _public prototype_ `FBakingConfiguration() = default;` — Note: We need to explicitly disable warnings on these constructors/operators for clang to be happy with deprecated variables
- L143 _public prototype_ `FBakingConfiguration(const FBakingConfiguration&) = default;`
- L144 _public prototype_ `FBakingConfiguration(FBakingConfiguration&&) = default;`
- L145 _public prototype_ `FBakingConfiguration& operator=(const FBakingConfiguration&) = default;`
- L146 _public prototype_ `FBakingConfiguration& operator=(FBakingConfiguration&&) = default;`
- L153 _public member_ `FString OutputPath = TEXT("/Ga` — `UPROPERTY(BlueprintReadWrite, Blueprintable, Category = CustomizableObjectInstanceBaker)` — The path where to save the baked resources. EX /Game/MyBakingTest
- L159 _public member_ `FString OutputFilesBaseName;` — `UPROPERTY(BlueprintReadWrite, Blueprintable, Category = CustomizableObjectInstanceBaker)` — The name to be used as base (prefix) during the naming of the exported resources
- L165 _public member_ `bool bExportAllResourcesOnBake = false;` — `UPROPERTY(BlueprintReadWrite, Blueprintable, Category = CustomizableObjectInstanceBaker)` — Determines if we want a full or partial export
- L171 _public member_ `bool bGenerateConstantMaterialInstancesOnBake = false;` — `UPROPERTY(BlueprintReadWrite, Blueprintable, Category = CustomizableObjectInstanceBaker)` — Determines if we want (or not) to generate constant material instances for each of the material instances found in the mutable instance
- L177 _public member_ `bool bReplaceRestrictedCharacters = false;` — `UPROPERTY(BlueprintReadWrite, Blueprintable, Category = CustomizableObjectInstanceBaker)` — If true, invalid characters will be removed from exported resource names
- L180 _public member_ `FString SkeletalMeshAssetPrefix = TEXT("SK_` — `UPROPERTY(BlueprintReadWrite, Blueprintable, Category = "CustomizableObjectInstanceBaker|ResourceNameGeneration")`
- L183 _public member_ `FString SkeletonAssetPrefix = TEXT("SKE` — `UPROPERTY(BlueprintReadWrite, Blueprintable, Category = "CustomizableObjectInstanceBaker|ResourceNameGeneration")`
- L186 _public member_ `FString PhysicsAssetPrefix = TEXT("PHY` — `UPROPERTY(BlueprintReadWrite, Blueprintable, Category = "CustomizableObjectInstanceBaker|ResourceNameGeneration")`
- L189 _public member_ `FString TextureAssetPrefix = TEXT("T_"` — `UPROPERTY(BlueprintReadWrite, Blueprintable, Category = "CustomizableObjectInstanceBaker|ResourceNameGeneration")`
- L192 _public member_ `FString MaterialAssetPrefix = TEXT("M_"` — `UPROPERTY(BlueprintReadWrite, Blueprintable, Category = "CustomizableObjectInstanceBaker|ResourceNameGeneration")`
- L195 _public member_ `FString MaterialInstanceAssetPrefix = TEXT("MI_` — `UPROPERTY(BlueprintReadWrite, Blueprintable, Category = "CustomizableObjectInstanceBaker|ResourceNameGeneration")`
- L198 _public member_ `FString MaterialDynamicInstanceAssetPrefix = TEXT("MID` — `UPROPERTY(BlueprintReadWrite, Blueprintable, Category = "CustomizableObjectInstanceBaker|ResourceNameGeneration")`
- L201 _public member_ `FString MaterialConstantInstanceAssetPrefix = TEXT("MIC` — `UPROPERTY(BlueprintReadWrite, Blueprintable, Category = "CustomizableObjectInstanceBaker|ResourceNameGeneration")`
- L207 _public member_ `FBakeOperationCompletedDelegate OnBakeOperationCompletedCallback;` — `UPROPERTY(BlueprintReadWrite, Blueprintable, Category = CustomizableObjectInstanceBaker)` — Callback executed once the baking operation gets completed. It will return the end success state and also some data about the assets saved.
- L212 _public member_ `const static inline FString BakedResourcePrefix = TEXT("BAK` — The contents of the prefix used to mark resources generated for a bake operation

#### enum `EUpdateResult`  
`enum class EUpdateResult : uint8`  
_L218-230_
- reflection: `UENUM(BlueprintType)`
- desc: Instance Update Result.
- L220 _public enumerator_ `Success` — Update finished without issues.
- L221 _public enumerator_ `Warning` — Generic warning. Update finished but with warnings.
- L223 _public enumerator_ `Error` — Generic error.
- L224 _public enumerator_ `ErrorOptimized` — The update was skipped since its result would have been the same as the current customization.
- L225 _public enumerator_ `ErrorReplaced` — The update was replaced by a newer update request.
- L226 _public enumerator_ `ErrorDiscarded` — The update was not finished since due to the LOD management discarding the data.
- L227 _public enumerator_ `Error16BitBoneIndex` — The update finish unsuccessfully due to Instance not supporting 16 Bit Bone Indexing required by the Engine.
- L229 _public enumerator_ `ErrorUncompiled` — The update failed due to the CO being uncompiled

#### struct `FUpdateContext`  
`struct FUpdateContext`  
_L236-245_
- reflection: `USTRUCT(BlueprintType)`
- desc: Instance Update Context. Used to avoid changing the delegate signature in the future.
- L241 _public member_ `EUpdateResult UpdateResult = EUpdateResult::Success;` — `UPROPERTY(BlueprintReadOnly, Category = UpdateResult)`
- L244 _public member_ `TObjectPtr<UCustomizableObjectInstance> Instance;` — `UPROPERTY(BlueprintReadOnly, Category = UpdateResult)`

#### struct `FPreSetSkeletalMeshParams`  
`struct FPreSetSkeletalMeshParams`  
_L265-274_
- reflection: `USTRUCT()`
- L270 _public member_ `TObjectPtr<UCustomizableObjectInstance> Instance;` — `UPROPERTY()`
- L273 _public member_ `TObjectPtr<USkeletalMesh> SkeletalMesh;` — `UPROPERTY()`

#### class `UCustomizableObjectInstance`  
`class UCustomizableObjectInstance : public UObject`  
_L286-804_
- reflection: `UCLASS(MinimalAPI, BlueprintType, HideCategories=(CustomizableObjectInstance))`
- inherits: `UObject`
- L295 _public prototype_ `UCustomizableObjectInstance();`
- L299 _public member_ `FObjectInstanceUpdatedDelegate UpdatedDelegate;` — `UPROPERTY(Transient, BlueprintAssignable, Category = CustomizableObjectInstance)` — Broadcast when the Customizable Object Instance is updated.
- L302 _public member_ `FObjectInstanceUpdatedNativeDelegate UpdatedNativeDelegate;` — Broadcast when the Customizable Object Instance is updated.
- L306 _public member_ `FPreSetSkeletalMeshDelegate PreSetSkeletalMeshDelegate;` — Broadcast before setting the generated Skeletal Mesh to the Skeletal Mesh Components. Broadcast even if Skeletal Meshes are reused.
- L310 _public member_ `FPreSetSkeletalMeshNativeDelegate PreSetSkeletalMeshNativeDelegate;` — Broadcast before setting the generated Skeletal Mesh to the Skeletal Mesh Components. Broadcast even if Skeletal Meshes are reused.
- L314 _public prototype_ `virtual bool CanEditChange( const FProperty* InProperty ) const override;`
- L315 _public prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L318 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L319 _public prototype_ `virtual void PostLoad() override;`
- L320 _public prototype_ `virtual void BeginDestroy() override;`
- L321 _public prototype_ `virtual FString GetDesc() override;`
- L322 _public prototype_ `virtual bool IsEditorOnly() const override;`
- L323 _public prototype_ `virtual void PostInitProperties() override;`
- L328 _public prototype_ `void SetObject(UCustomizableObject* InObject);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Set the CustomizableObject this instance will be generated from. It is usually not necessary to call this since instances are already generated from a CustomizableObject.
- L332 _public prototype_ `UCustomizableObject* GetCustomizableObject() const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Get the CustomizableObject that this is an instance of.
- L336 _public prototype_ `bool GetBuildParameterRelevancy() const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Return true if the parameter relevancy will be updated when this instance is generated.
- L340 _public prototype_ `void SetBuildParameterRelevancy(bool Value);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Set the flag that controls if parameter relevancy will be updated when this instance is generated.
- L344 _public prototype_ `FString GetCurrentState() const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Return the name of the current CustomizableObject state this is instance is set to.
- L348 _public prototype_ `void SetCurrentState(const FString& StateName);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Set the CustomizableObject state that this instance will be generated into.
- L352 _public prototype_ `USkeletalMesh* GetComponentMeshSkeletalMesh(const FName& ComponentName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — DEPRECATED: Use GetSkeletalMeshComponentSkeletalMesh
- L356 _public prototype_ `USkeletalMesh* GetSkeletalMeshComponentSkeletalMesh(const FName& ComponentName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Given a Mesh Component name, return its generated Skeletal Mesh.
- L359 _public prototype_ `TArray<UMaterialInterface*> GetSkeletalMeshComponentOverrideMaterials(const FName& ComponentName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)`
- L363 _public prototype_ `bool HasAnySkeletalMesh() const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Return true if a skeletal mesh has been generated for any component of this instance.
- L367 _public prototype_ `bool HasAnyParameters() const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Return true if the instance has any parameters.
- L371 _public prototype_ `void SetRandomValues();` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Set random values to the parameters.
- L375 _public prototype_ `void SetRandomValuesFromStream(const FRandomStream& InStream);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Set random values to the parameters using a stream.
- L379 _public prototype_ `void SetDefaultValue(const FString& ParamName);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Sets a parameter to its default value
- L383 _public prototype_ `void SetDefaultValues();` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Set all parameters to their default value.
- L388 _public prototype_ `TSet<UAssetUserData*> GetMergedAssetUserData(const FName& ComponentName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Returns the AssetUserData that was gathered from all the constituent mesh parts during the last update. It requires that the CustomizableObject had the bEnableAssetUserDataMerge set to true during compilation.
- L392 _public prototype_ `void UpdateSkeletalMeshAsync(bool bIgnoreCloseDist = false, bool bForceHighPriority = false);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Generate the instance with the current parameters and update all the components Skeletal Meshes asynchronously.
- L397 _public prototype_ `void UpdateSkeletalMeshAsyncResult(FInstanceUpdateDelegate Callback, bool bIgnoreCloseDist = false, bool bForceHighPriority = false);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Generate the instance with the current parameters and update all the components Skeletal Meshes asynchronously. Callback will be called once the update finishes, even if it fails.
- L399 _public prototype_ `void UpdateSkeletalMeshAsyncResult(FInstanceUpdateNativeDelegate Callback, bool bIgnoreCloseDist = false, bool bForceHighPriority = false);`
- L403 _public prototype_ `UCustomizableObjectInstance* Clone();` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Clones the instance creating a new identical transient instance.
- L407 _public prototype_ `UCustomizableObjectInstance* CloneStatic(UObject* Outer);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Clones the instance creating a new identical static instance with the given Outer.
- L411 _public prototype_ `void CopyParametersFromInstance(UCustomizableObjectInstance* Instance);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Copy parameters from the given Instance.
- L414 _public prototype_ `void DestroyLiveUpdateInstance();` — Destroy the Mutable Core Live Update Instance attached to this (if exists).
- L418 _public prototype_ `bool IsParameterRelevant(const FString& ParamName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Return true if the given parameter has any effect in the current object state, and considering the current values of the other parameters.
- L422 _public prototype_ `bool IsParameterDirty(const FString& ParamName, int32 RangeIndex = -1) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Return true if the parameter has changed but the Instance has not yet been updated.
- L426 _public prototype_ `int32 GetProjectorValueRange(const FString& ParamName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — For multidimensional parameters, return the number of dimensions that the given projector parameter supports.
- L430 _public prototype_ `int32 GetIntValueRange(const FString& ParamName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — For multidimensional parameters, return the number of dimensions that the given int parameter supports.
- L434 _public prototype_ `int32 GetFloatValueRange(const FString& ParamName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — For multidimensional parameters, return the number of dimensions that the given float parameter supports.
- L438 _public prototype_ `int32 GetTextureValueRange(const FString& ParamName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — For multidimensional parameters, return the number of dimensions that the given texture parameter supports.
- L442 _public prototype_ `const FString& GetIntParameterSelectedOption(const FString& ParamName, int32 RangeIndex = -1) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — DEPRECATED. Use GetEnumParameterSelectedOption instead.
- L446 _public prototype_ `const FString& GetEnumParameterSelectedOption(const FString& ParamName, int32 RangeIndex = -1) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Return the name of the option currently set in the given parameter.
- L450 _public prototype_ `void SetIntParameterSelectedOption(const FString& ParamName, const FString& SelectedOptionName, int32 RangeIndex = -1);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — DEPRECATED. Use SetEnumParameterSelectedOption instead.
- L454 _public prototype_ `void SetEnumParameterSelectedOption(const FString& ParamName, const FString& SelectedOptionName, int32 RangeIndex = -1);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Set the currently selected option value for the given parameter, by parameter name and option name.
- L458 _public prototype_ `float GetFloatParameterSelectedOption(const FString& FloatParamName, int32 RangeIndex = -1) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Gets the value of a float parameter with name "FloatParamName".
- L462 _public prototype_ `void SetFloatParameterSelectedOption(const FString& FloatParamName, float FloatValue, int32 RangeIndex = -1);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Sets the float value "FloatValue" of a float parameter with index "FloatParamIndex".
- L466 _public prototype_ `UTexture* GetTextureParameterSelectedOption(const FString& TextureParamName, int32 RangeIndex = -1) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Gets the value of a texture parameter with name "TextureParamName".
- L470 _public prototype_ `void SetTextureParameterSelectedOption(const FString& TextureParamName, UTexture* TextureValue, int32 RangeIndex = -1);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Sets the texture value "TextureValue" of a texture parameter with index "TextureParamIndex".
- L474 _public prototype_ `USkeletalMesh* GetSkeletalMeshParameterSelectedOption(const FString& SkeletalMeshParamName, int32 RangeIndex = -1);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Gets the value of a Skeletal Mesh parameter with name "SkeletalMeshParamName".
- L478 _public prototype_ `void SetSkeletalMeshParameterSelectedOption(const FString& SkeletalMeshParamName, USkeletalMesh* SkeletalMeshValue, int32 RangeIndex = -1);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Sets the Skeletal Mesh value "SkeletalMeshValue" of a Skeletal Mesh parameter with index "SkeletalMeshParamName".
- L482 _public prototype_ `UMaterialInterface* GetMaterialParameterSelectedOption(const FString& MaterialParamName, int32 RangeIndex = -1);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Gets the value of a Material parameter with name "MaterialParamName".
- L486 _public prototype_ `void SetMaterialParameterSelectedOption(const FString& MaterialParamName, UMaterialInterface* MaterialValue, int32 RangeIndex = -1);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Sets the Material value "MaterialParamName" of a Material parameter with index "MaterialParamName".
- L490 _public prototype_ `FInstancedStruct GetExternalTypeParameterSelectedOption(const FString& ExternalTypeParamName, int32 RangeIndex = -1) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Gets the value of an External Type parameter with name "ExternalTypeParamName".
- L494 _public prototype_ `void SetExternalTypeParameterSelectedOption(const FString& ExternalTypeParamName, const FInstancedStruct& ExternalTypeValue, int32 RangeIndex = -1);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Sets the External Type value "ExternalTypeValue" of an External Type parameter with name "ExternalTypeParamName".
- L498 _public prototype_ `FLinearColor GetColorParameterSelectedOption(const FString& ColorParamName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Gets the value of a color parameter with name "ColorParamName".
- L502 _public prototype_ `void SetColorParameterSelectedOption(const FString& ColorParamName, const FLinearColor& ColorValue);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Sets the color value "ColorValue" of a color parameter with index "ColorParamIndex".
- L506 _public prototype_ `bool GetBoolParameterSelectedOption(const FString& BoolParamName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Gets the bool value of a bool parameter with name "BoolParamName".
- L510 _public prototype_ `void SetBoolParameterSelectedOption(const FString& BoolParamName, bool BoolValue);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Sets the bool value "BoolValue" of a bool parameter with name "BoolParamName".
- L514 _public prototype_ `FVector4f GetVectorParameterSelectedOption(const FString& VectorParamName);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Gets the Vector value of a Vector parameter with name "VectorParamName".
- L518 _public prototype_ `void SetVectorParameterSelectedOption(const FString& VectorParamName, const FVector4f& VectorValue);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Sets the Vector value "VectorValue" of a Vector parameter with name "VectorParamName".
- L522 _public prototype_ `FTransform GetTransformParameterSelectedOption(const FString& TransformParamName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Gets the value of a transform parameter with name "TransformParamName".
- L526 _public prototype_ `void SetTransformParameterSelectedOption(const FString& TransformParamName, const FTransform& TransformValue);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Sets the transform value "TransformValue" of a transform parameter with name "TransformParamName".
- L531 _public prototype_ `void SetProjectorValue(const FString& ProjectorParamName, const FVector& OutPos, const FVector& OutDirection, const FVector& OutUp, const FVector& OutScale, float OutAngle, int32 RangeIndex = -1);` — `UE_DEPRECATED(5.8, "Use the 'SetProjectorParameterSelectedOption' method that takes a 'FCustomizableObjectProjector' instead.")` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance, meta = (DeprecatedFunction, DeprecationMessage = "Use the 'SetProjectorParameterSelectedOption' method that takes a 'FCustomizableObjectProjector' instead."))` — Sets the projector values of a projector parameter with index "ProjectorParamIndex".
- L539 _public prototype_ `void SetProjectorPosition(const FString& ProjectorParamName, const FVector& Pos, int32 RangeIndex = -1);` — `UE_DEPRECATED(5.8, "Use the 'SetProjectorParameterSelectedOption' method that takes a 'FCustomizableObjectProjector' instead.")` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance, meta = (DeprecatedFunction, DeprecationMessage = "Use the 'SetProjectorParameterSelectedOption' method that takes a 'FCustomizableObjectProjector' instead."))` — Set only the projector position keeping the rest of values.
- L544 _public prototype_ `void SetProjectorDirection(const FString& ProjectorParamName, const FVector& Direction, int32 RangeIndex = -1);` — `UE_DEPRECATED(5.8, "Use the 'SetProjectorParameterSelectedOption' method that takes a 'FCustomizableObjectProjector' instead.")` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance, meta = (DeprecatedFunction, DeprecationMessage = "Use the 'SetProjectorParameterSelectedOption' method that takes a 'FCustomizableObjectProjector' instead."))` — Set only the projector direction vector keeping the rest of values.
- L549 _public prototype_ `void SetProjectorUp(const FString& ProjectorParamName, const FVector& Up, int32 RangeIndex = -1);` — `UE_DEPRECATED(5.8, "Use the 'SetProjectorParameterSelectedOption' method that takes a 'FCustomizableObjectProjector' instead.")` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance, meta = (DeprecatedFunction, DeprecationMessage = "Use the 'SetProjectorParameterSelectedOption' method that takes a 'FCustomizableObjectProjector' instead."))` — Set only the projector up vector keeping the rest of values.
- L554 _public prototype_ `void SetProjectorScale(const FString& ProjectorParamName, const FVector& Scale, int32 RangeIndex = -1);` — `UE_DEPRECATED(5.8, "Use the 'SetProjectorParameterSelectedOption' method that takes a 'FCustomizableObjectProjector' instead.")` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance, meta = (DeprecatedFunction, DeprecationMessage = "Use the 'SetProjectorParameterSelectedOption' method that takes a 'FCustomizableObjectProjector' instead."))` — Set only the projector scale keeping the rest of values.
- L559 _public prototype_ `void SetProjectorAngle(const FString& ProjectorParamName, float Angle, int32 RangeIndex = -1);` — `UE_DEPRECATED(5.8, "Use the 'SetProjectorParameterSelectedOption' method that takes a 'FCustomizableObjectProjector' instead.")` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance, meta = (DeprecatedFunction, DeprecationMessage = "Use the 'SetProjectorParameterSelectedOption' method that takes a 'FCustomizableObjectProjector' instead."))` — Set only the cylindrical projector angle keeping the rest of values.
- L562 _public prototype_ `void SetProjectorParameterSelectedOption(const FString& ProjectorParamName, const FCustomizableObjectProjector& ProjectorValue, const int32 RangeIndex = -1);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)`
- L567 _public prototype_ `void GetProjectorValue(const FString& ProjectorParamName, FVector& OutPos, FVector& OutDirection, FVector& OutUp, FVector& OutScale, float& OutAngle, ECustomizableObjectProjectorType& OutType, int32 RangeIndex = -1) const;` — `UE_DEPRECATED(5.8, "Use the 'GetProjectorParameterSelectedOption' method that returns a 'FCustomizableObjectProjector' instead.")` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance, meta = (DeprecatedFunction, DeprecationMessage = "Use the 'GetProjectorParameterSelectedOption' method that returns a 'FCustomizableObjectProjector' instead."))` — Get the projector values of a projector parameter with index "ProjectorParamIndex".
- L573 _public prototype_ `void GetProjectorValueF(const FString& ProjectorParamName, FVector3f& Pos, FVector3f& Direction, FVector3f& Up, FVector3f& Scale, float& Angle, ECustomizableObjectProjectorType& Type, int32 RangeIndex = -1) const;` — `UE_DEPRECATED(5.8, "Use the 'GetProjectorParameterSelectedOption' method that returns a 'FCustomizableObjectProjector' instead.")`
- L581 _public prototype_ `FVector GetProjectorPosition(const FString & ParamName, int32 RangeIndex = -1) const;` — `UE_DEPRECATED(5.8, "Use the 'GetProjectorParameterSelectedOption' method that returns a 'FCustomizableObjectProjector' instead.")` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance, meta = (DeprecatedFunction, DeprecationMessage = "Use the 'GetProjectorParameterSelectedOption' method that returns a 'FCustomizableObjectProjector' instead."))` — Get the current projector position for the parameter with the given name.
- L586 _public prototype_ `FVector GetProjectorDirection(const FString & ParamName, int32 RangeIndex = -1) const;` — `UE_DEPRECATED(5.8, "Use the 'GetProjectorParameterSelectedOption' method that returns a 'FCustomizableObjectProjector' instead.")` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance, meta = (DeprecatedFunction, DeprecationMessage = "Use the 'GetProjectorParameterSelectedOption' method that returns a 'FCustomizableObjectProjector' instead."))` — Get the current projector direction vector for the parameter with the given name.
- L591 _public prototype_ `FVector GetProjectorUp(const FString & ParamName, int32 RangeIndex = -1) const;` — `UE_DEPRECATED(5.8, "Use the 'GetProjectorParameterSelectedOption' method that returns a 'FCustomizableObjectProjector' instead.")` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance, meta = (DeprecatedFunction, DeprecationMessage = "Use the 'GetProjectorParameterSelectedOption' method that returns a 'FCustomizableObjectProjector' instead."))` — Get the current projector up vector for the parameter with the given name.
- L596 _public prototype_ `FVector GetProjectorScale(const FString & ParamName, int32 RangeIndex = -1) const;` — `UE_DEPRECATED(5.8, "Use the 'GetProjectorParameterSelectedOption' method that returns a 'FCustomizableObjectProjector' instead.")` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance, meta = (DeprecatedFunction, DeprecationMessage = "Use the 'GetProjectorParameterSelectedOption' method that returns a 'FCustomizableObjectProjector' instead."))` — Get the current projector scale for the parameter with the given name.
- L601 _public prototype_ `float GetProjectorAngle(const FString& ParamName, int32 RangeIndex = -1) const;` — `UE_DEPRECATED(5.8, "Use the 'GetProjectorParameterSelectedOption' method that returns a 'FCustomizableObjectProjector' instead.")` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance, meta = (DeprecatedFunction, DeprecationMessage = "Use the 'GetProjectorParameterSelectedOption' method that returns a 'FCustomizableObjectProjector' instead."))` — Get the current cylindrical projector angle for the parameter with the given name.
- L606 _public prototype_ `ECustomizableObjectProjectorType GetProjectorParameterType(const FString& ParamName, int32 RangeIndex = -1) const;` — `UE_DEPRECATED(5.8, "Use the 'GetProjectorParameterSelectedOption' method that returns a 'FCustomizableObjectProjector' instead.")` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance, meta = (DeprecatedFunction, DeprecationMessage = "Use the 'GetProjectorParameterSelectedOption' method that returns a 'FCustomizableObjectProjector' instead."))` — Get the current projector type for the parameter with the given name.
- L610 _public prototype_ `FCustomizableObjectProjector GetProjector(const FString& ParamName, int32 RangeIndex = -1) const;` — `UE_DEPRECATED(5.8, "Use the 'GetProjectorParameterSelectedOption' method that returns a 'FCustomizableObjectProjector' instead.")` — Get the current projector for the parameter with the given name.
- L614 _public prototype_ `FCustomizableObjectProjector GetProjectorParameterSelectedOption(const FString& ParamName, int32 RangeIndex = -1) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Get the current projector for the parameter with the given name.
- L618 _public prototype_ `bool ContainsIntParameter(const FString& ParameterName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — DEPRECATED. Use ContainsEnumParameter instead.
- L622 _public prototype_ `bool ContainsEnumParameter(const FString& ParameterName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Return true if the Int Parameter exists.
- L626 _public prototype_ `bool ContainsFloatParameter(const FString& ParameterName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Return true if the Float Parameter exists.
- L630 _public prototype_ `bool ContainsTextureParameter(const FString& ParameterName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Return true if the Texture Parameter exists.
- L634 _public prototype_ `bool ContainsSkeletalMeshParameter(const FString& ParameterName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Return true if the Skeletal Mesh Parameter exists.
- L638 _public prototype_ `bool ContainsMaterialParameter(const FString& ParameterName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Return true if the Material Parameter exists.
- L642 _public prototype_ `bool ContainsExternalTypeParameter(const FString& ParameterName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Return true if the External Type Parameter exists.
- L646 _public prototype_ `bool ContainsBoolParameter(const FString& ParameterName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Return true if the Bool Parameter exists.
- L650 _public prototype_ `bool ContainsColorParameter(const FString& ParameterName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Return true if the Color Parameter exists.
- L654 _public prototype_ `bool ContainsVectorParameter(const FString& ParameterName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Return true if the Vector Parameter exists.
- L658 _public prototype_ `bool ContainsProjectorParameter(const FString& ParameterName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Return true if the Projector Parameter exists.
- L662 _public prototype_ `bool ContainsTransformParameter(const FString& ParameterName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Return true if the Transform Parameter exists.
- L667 _public prototype_ `int32 AddValueToIntRange(const FString& ParamName);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Increases the range of values of the integer with ParamName and returns the index of the new integer value, -1 otherwise. The added value is initialized with the first integer option and is the last one of the range.
- L672 _public prototype_ `int32 AddValueToFloatRange(const FString& ParamName);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Increases the range of values of the float with ParamName, returns the index of the new float value, -1 otherwise. The added value is initialized with 0.5f and is the last one of the range.
- L677 _public prototype_ `int32 AddValueToProjectorRange(const FString& ParamName);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Increases the range of values of the projector with ParamName, returns the index of the new projector value, -1 otherwise. The added value is initialized with the default projector as set up in the editor and is the last one of the range.
- L682 _public prototype_ `int32 RemoveValueFromIntRange(const FString& ParamName, int32 RangeIndex = -1);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Remove the FRangeIndex element of the integer range of values from the parameter ParamName. If RangeValue is -1 removes the last of the integer range of values. Returns the index of the last valid integer, -1 if no values left.
- L687 _public prototype_ `int32 RemoveValueFromFloatRange(const FString& ParamName, int32 RangeIndex = -1);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Remove the FRangeIndex element of the float range of values from the parameter ParamName. If RangeValue is -1 removes the last of the float range of values. Returns the index of the last valid float, -1 if no values left.
- L692 _public prototype_ `int32 RemoveValueFromProjectorRange(const FString& ParamName, int32 RangeIndex = -1);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Remove the FRangeIndex element of the projector range of values from the parameter ParamName. If RangeValue is -1 removes the last of the projector range of values. Returns the index of the last valid projector, -1 if no values left.
- L702 _public prototype_ `int32 MultilayerProjectorNumLayers(const FName& ProjectorParamName) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — See FMultilayerProjector::NumLayers.
- L706 _public prototype_ `void MultilayerProjectorCreateLayer(const FName& ProjectorParamName, int32 Index);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — See FMultilayerProjector::CreateLayer.
- L710 _public prototype_ `void MultilayerProjectorRemoveLayerAt(const FName& ProjectorParamName, int32 Index);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — See FMultilayerProjector::RemoveLayerAt.
- L714 _public prototype_ `FMultilayerProjectorLayer MultilayerProjectorGetLayer(const FName& ProjectorParamName, int32 Index) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — See FMultilayerProjector::GetLayer.
- L718 _public prototype_ `void MultilayerProjectorUpdateLayer(const FName& ProjectorParamName, int32 Index, const FMultilayerProjectorLayer& Layer);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — See FMultilayerProjector::UpdateLayer.
- L725 _public prototype_ `TArray<FName> GetComponentNames() const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Return the list of names of components generated for this instance. This only has values when the instance has been completely generated.
- L731 _public prototype_ `TSubclassOf<UAnimInstance> GetAnimBP(FName ComponentName, const FName& Slot) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Returns the animation BP for the parameter component and slot, gathered from all the meshes that compose this instance.
- L735 _public prototype_ `FGameplayTagContainer GetAnimationGameplayTags() const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Return the list of tags for this instance.
- L739 _public prototype_ `void ForEachComponentAnimInstance(FName ComponentName, FEachComponentAnimInstanceClassDelegate Delegate) const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Execute a delegate for each animation instance involved in this customizable object instance.
- L741 _public prototype_ `void ForEachComponentAnimInstance(FName ComponentName, FEachComponentAnimInstanceClassNativeDelegate Delegate) const;`
- L744 _public prototype_ `bool AnimInstanceNeedsFixup(TSubclassOf<UAnimInstance> AnimInstance) const;` — Check if the given UAnimInstance class requires to be fixed up.
- L747 _public prototype_ `void AnimInstanceFixup(UAnimInstance* AnimInstance) const;` — Fix the given UAnimInstance instance.
- L750 _public prototype_ `void SaveDescriptor(FArchive &CustomizableObjectDescriptor, bool bUseCompactDescriptor);` — See FCustomizableObjectInstanceDescriptor::SaveDescriptor.
- L753 _public prototype_ `void LoadDescriptor(FArchive &CustomizableObjectDescriptor);` — See FCustomizableObjectInstanceDescriptor::LoadDescriptor.
- L757 _public prototype_ `void SetReplacePhysicsAssets(bool bReplaceEnabled);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Enable physics asset replacement so that generated skeletal meshes have the merged physics assets of their skeletal mesh parts and reference mesh.
- L761 _public prototype_ `void SetKeepOwnershipOfGeneratedResources(bool bEnabled);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — If true, Mutable will keep the ownership of the generated resources. This means that Mutable may decide to modify or reuse them for performance considerations.
- L769 _public prototype_ `void Bake(const FBakingConfiguration& InBakingConfiguration);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstanceBaking)` — Performs the baking of the instance resources in an async fashion. Bind yourself to the callback present in InBakingConfiguration to get notified in case it fails @param InBakingConfiguration The configuration to be using for the baking operation
- L772 _public prototype_ `UCustomizableInstancePrivate* GetPrivate() const;`
- L776 _private member_ `FCustomizableObjectInstanceDescriptor Descriptor;` — `UPROPERTY()`
- L779 _private member_ `TObjectPtr<UCustomizableInstancePrivate> PrivateData;` — `UPROPERTY(Instanced)`
- L783 _private member_ `TObjectPtr<UCustomizableObject> CustomizableObject_DEPRECATED;` — `UPROPERTY()` — Deprecated properties
- L786 _private member_ `TArray<FCustomizableObjectBoolParameterValue> BoolParameters_DEPRECATED;` — `UPROPERTY()`
- L789 _private member_ `TArray<FCustomizableObjectIntParameterValue> IntParameters_DEPRECATED;` — `UPROPERTY()`
- L792 _private member_ `TArray<FCustomizableObjectFloatParameterValue> FloatParameters_DEPRECATED;` — `UPROPERTY()`
- L795 _private member_ `TArray<FCustomizableObjectTextureParameterValue> TextureParameters_DEPRECATED;` — `UPROPERTY()`
- L798 _private member_ `TArray<FCustomizableObjectVectorParameterValue> VectorParameters_DEPRECATED;` — `UPROPERTY()`
- L801 _private member_ `TArray<FCustomizableObjectProjectorParameterValue> ProjectorParameters_DEPRECATED;` — `UPROPERTY()`
- L803 _private member_ `bool bBuildParameterRelevancy_DEPRECATED = false;`

#### Free symbols / members of external scopes

- L129 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FBakeOperationCompletedDelegate, const FCustomizableObjectInstanceBakeOutput, BakeOperationOutput);`
- L129 _prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FBakeOperationCompletedDelegate, const FCustomizableObjectInstanceBakeOutput, BakeOperationOutput);`
- L248 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FInstanceUpdateDelegate, const FUpdateContext&, Result);`
- L248 _prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FInstanceUpdateDelegate, const FUpdateContext&, Result);`
- L249 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FInstanceUpdateNativeDelegate, const FUpdateContext&);`
- L249 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FInstanceUpdateNativeDelegate, const FUpdateContext&);`
- L261 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FObjectInstanceUpdatedDelegate, UCustomizableObjectInstance*, Instance);` — Broadcast when an Instance update has completed. Notice that Mutable internally can also start an Instance update.
- L261 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FObjectInstanceUpdatedDelegate, UCustomizableObjectInstance*, Instance);` — Broadcast when an Instance update has completed. Notice that Mutable internally can also start an Instance update.
- L262 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FObjectInstanceUpdatedNativeDelegate, UCustomizableObjectInstance*);`
- L262 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FObjectInstanceUpdatedNativeDelegate, UCustomizableObjectInstance*);`
- L276 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPreSetSkeletalMeshDelegate, const FPreSetSkeletalMeshParams&, Params);`
- L276 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPreSetSkeletalMeshDelegate, const FPreSetSkeletalMeshParams&, Params);`
- L277 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FPreSetSkeletalMeshNativeDelegate, const FPreSetSkeletalMeshParams&);`
- L277 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FPreSetSkeletalMeshNativeDelegate, const FPreSetSkeletalMeshParams&);`
- L279 _delegate_ `DECLARE_DELEGATE_OneParam(FProjectorStateChangedDelegate, FString);`
- L279 _prototype_ `DECLARE_DELEGATE_OneParam(FProjectorStateChangedDelegate, FString);`
- L281 _delegate_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FEachComponentAnimInstanceClassDelegate, FName, SlotIndex, TSubclassOf<UAnimInstance>, AnimInstClass);`
- L281 _prototype_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FEachComponentAnimInstanceClassDelegate, FName, SlotIndex, TSubclassOf<UAnimInstance>, AnimInstClass);`
- L283 _delegate_ `DECLARE_DELEGATE_TwoParams(FEachComponentAnimInstanceClassNativeDelegate, FName , TSubclassOf<UAnimInstance> );`
- L283 _prototype_ `DECLARE_DELEGATE_TwoParams(FEachComponentAnimInstanceClassNativeDelegate, FName , TSubclassOf<UAnimInstance> );`

### `Plugins/Mutable/Source/CustomizableObject/Public/MuCO/CustomizableObjectInstanceAssetUserData.h` (Public)


#### struct `FCustomizableObjectAnimationSlot`  
`struct FCustomizableObjectAnimationSlot`  
_L15-24_
- reflection: `USTRUCT(BlueprintType)`
- L20 _public member_ `FName Name;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CustomizableObjectInstance)`
- L23 _public member_ `TSoftClassPtr<UAnimInstance> AnimInstance;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CustomizableObjectInstance)`

#### class `UCustomizableObjectInstanceUserData`  
`class UCustomizableObjectInstanceUserData : public UAssetUserData`  
_L29-49_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UAssetUserData`
- desc: Additional data attached to Skeletal Meshes.
- L36 _public prototype_ `const FGameplayTagContainer& GetAnimationGameplayTags() const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Return the list of tags for this instance.
- L40 _public prototype_ `void SetAnimationGameplayTags(const FGameplayTagContainer& InstanceTags);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Sets the list of tags for this instance.
- L42 _public prototype_ `virtual bool Merge(const TNotNull<UAssetUserData*> Other) override;`
- L45 _public member_ `FGameplayTagContainer AnimationGameplayTag;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CustomizableObjectInstance)`
- L48 _public member_ `TArray<FCustomizableObjectAnimationSlot> AnimationSlots;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CustomizableObjectInstance)`

### `Plugins/Mutable/Source/CustomizableObject/Public/MuCO/CustomizableObjectInstanceDescriptor.h` (Public)


#### struct `FCustomizableObjectInstanceDescriptor`  
`struct FCustomizableObjectInstanceDescriptor`  
_L42-269_
- reflection: `USTRUCT()`
- desc: Internal use only! Currently in /Public due to UCustomizableObjectInstance::Descriptor. Set of parameters + state that defines a CustomizableObjectInstance. This object has the same parameters + state interface as UCustomizableObjectInstance. UCustomizableObjectInstance must share the same interface. Any public methods added here should also end up in the Instance.
- L46 _public prototype_ `FCustomizableObjectInstanceDescriptor() = default;`
- L48 _public prototype_ `explicit FCustomizableObjectInstanceDescriptor(UCustomizableObject& Object);`
- L56 _public prototype_ `void SaveDescriptor(FArchive &Ar, bool bUseCompactDescriptor);` — Serialize this object. Backwards compatibility is not guaranteed. Multilayer Projectors not supported. @param bUseCompactDescriptor If true it assumes the compiled objects are the same on both ends of the serialisation
- L64 _public prototype_ `void LoadDescriptor(FArchive &Ar);` — Deserialize this object. Backwards compatibility is not guaranteed. Multilayer Projectors not supported
- L67 _public prototype_ `UCustomizableObject* GetCustomizableObject() const;` — Could return nullptr in some rare situations, so check first
- L69 _public prototype_ `void SetCustomizableObject(UCustomizableObject* InCustomizableObject);`
- L71 _public prototype_ `bool GetBuildParameterRelevancy() const;`
- L73 _public prototype_ `void SetBuildParameterRelevancy(bool Value);`
- L76 _public prototype_ `void ReloadParameters();` — Update all parameters to be up to date with the Mutable Core parameters.
- L82 _public prototype_ `bool HasAnyParameters() const;`
- L84 _public prototype_ `const FString& GetIntParameterSelectedOption(const FString& ParamName, int32 RangeIndex = -1) const;`
- L86 _public prototype_ `void SetIntParameterSelectedOption(int32 IntParamIndex, const FString& SelectedOption, int32 RangeIndex = -1);`
- L88 _public prototype_ `void SetIntParameterSelectedOption(const FString& ParamName, const FString& SelectedOptionName, int32 RangeIndex = -1);`
- L90 _public prototype_ `float GetFloatParameterSelectedOption(const FString& FloatParamName, int32 RangeIndex = -1) const;`
- L92 _public prototype_ `void SetFloatParameterSelectedOption(const FString& FloatParamName, float FloatValue, int32 RangeIndex = -1);`
- L94 _public prototype_ `UTexture* GetTextureParameterSelectedOption(const FString& TextureParamName, int32 RangeIndex) const;`
- L96 _public prototype_ `void SetTextureParameterSelectedOption(const FString& TextureParamName, UTexture* TextureValue, int32 RangeIndex);`
- L98 _public prototype_ `USkeletalMesh* GetSkeletalMeshParameterSelectedOption(const FString& SkeletalMeshParamName, int32 RangeIndex = -1) const;`
- L100 _public prototype_ `void SetSkeletalMeshParameterSelectedOption(const FString& SkeletalMeshParamName, USkeletalMesh* SkeletalMeshValue, int32 RangeIndex = -1);`
- L102 _public prototype_ `UMaterialInterface* GetMaterialParameterSelectedOption(const FString& MaterialMeshParamName, int32 RangeIndex = -1) const;`
- L104 _public prototype_ `FInstancedStruct GetExternalTypeParameterSelectedOption(const FString& ExternalTypeParamName, int32 RangeIndex = -1) const;`
- L106 _public prototype_ `void SetExternalTypeParameterSelectedOption(const FString& ParamName, const FInstancedStruct& Value, int32 RangeIndex = -1);`
- L108 _public prototype_ `void SetMaterialParameterSelectedOption(const FString& MaterialParamName, UMaterialInterface* MaterialValue, int32 RangeIndex = -1);`
- L110 _public prototype_ `FTransform GetTransformParameterSelectedOption(const FString& TransformParamName) const;`
- L112 _public prototype_ `void SetTransformParameterSelectedOption(const FString& TransformParamName, const FTransform& TransformValue);`
- L114 _public prototype_ `bool GetBoolParameterSelectedOption(const FString& BoolParamName) const;`
- L116 _public prototype_ `void SetBoolParameterSelectedOption(const FString& BoolParamName, bool BoolValue);`
- L118 _public prototype_ `FVector4f GetVectorParameterSelectedOption(const FString& BoolParamName) const;`
- L120 _public prototype_ `void SetVectorParameterSelectedOption(const FString& VectorParamName, const FVector4f& VectorValue);`
- L122 _public prototype_ `void SetProjectorValue(const FString& ProjectorParamName, const FVector& Pos, const FVector& Direction, const FVector& Up, const FVector& Scale, float Angle, int32 RangeIndex = -1);`
- L127 _public prototype_ `void SetProjectorParameterSelectedOption(const FString& ProjectorParamName, const FCustomizableObjectProjector& ProjectorValue, const int32 RangeIndex = -1);`
- L129 _public prototype_ `void SetProjectorPosition(const FString& ProjectorParamName, const FVector& Pos, int32 RangeIndex = -1);`
- L131 _public prototype_ `void SetProjectorDirection(const FString& ProjectorParamName, const FVector& Direction, int32 RangeIndex = -1);`
- L133 _public prototype_ `void SetProjectorUp(const FString& ProjectorParamName, const FVector& Up, int32 RangeIndex = -1);`
- L135 _public prototype_ `void SetProjectorScale(const FString& ProjectorParamName, const FVector& Scale, int32 RangeIndex = -1);`
- L137 _public prototype_ `void SetProjectorAngle(const FString& ProjectorParamName, float Angle, int32 RangeIndex = -1);`
- L139 _public prototype_ `void GetProjectorValue(const FString& ProjectorParamName, FVector& OutPos, FVector& OutDirection, FVector& OutUp, FVector& OutScale, float& OutAngle, ECustomizableObjectProjectorType& OutType, int32 RangeIndex = -1) const;`
- L144 _public prototype_ `void GetProjectorValueF(const FString& ProjectorParamName, FVector3f& OutPos, FVector3f& OutDirection, FVector3f& OutUp, FVector3f& OutScale, float& OutAngle, ECustomizableObjectProjectorType& OutType, int32 RangeIndex = -1) const;`
- L149 _public prototype_ `FVector GetProjectorPosition(const FString & ParamName, int32 RangeIndex = -1) const;`
- L151 _public prototype_ `FVector GetProjectorDirection(const FString & ParamName, int32 RangeIndex = -1) const;`
- L153 _public prototype_ `FVector GetProjectorUp(const FString & ParamName, int32 RangeIndex = -1) const;`
- L155 _public prototype_ `FVector GetProjectorScale(const FString & ParamName, int32 RangeIndex = -1) const;`
- L157 _public prototype_ `float GetProjectorAngle(const FString& ParamName, int32 RangeIndex = -1) const;`
- L159 _public prototype_ `ECustomizableObjectProjectorType GetProjectorParameterType(const FString& ParamName, int32 RangeIndex = -1) const;`
- L161 _public prototype_ `FCustomizableObjectProjector GetProjectorParameterSelectedOption(const FString& ParamName, int32 RangeIndex = -1) const;`
- L163 _public prototype_ `int32 FindTypedParameterIndex(const FString& ParamName, EMutableParameterType Type) const;`
- L165 _public prototype_ `int32 GetProjectorValueRange(const FString& ParamName) const;`
- L167 _public prototype_ `int32 GetIntValueRange(const FString& ParamName) const;`
- L169 _public prototype_ `int32 GetFloatValueRange(const FString& ParamName) const;`
- L171 _public prototype_ `int32 GetTextureValueRange(const FString& ParamName) const;`
- L173 _public prototype_ `int32 AddValueToIntRange(const FString& ParamName);`
- L175 _public prototype_ `int32 AddValueToFloatRange(const FString& ParamName);`
- L177 _public prototype_ `int32 AddValueToTextureRange(const FString& ParamName);`
- L179 _public prototype_ `int32 AddValueToProjectorRange(const FString& ParamName);`
- L181 _public prototype_ `int32 RemoveValueFromIntRange(const FString& ParamName, int32 RangeIndex = -1);`
- L183 _public prototype_ `int32 RemoveValueFromFloatRange(const FString& ParamName, int32 RangeIndex = -1);`
- L185 _public prototype_ `int32 RemoveValueFromTextureRange(const FString& ParamName);`
- L187 _public prototype_ `int32 RemoveValueFromTextureRange(const FString& ParamName, int32 RangeIndex);`
- L189 _public prototype_ `int32 RemoveValueFromProjectorRange(const FString& ParamName, int32 RangeIndex = -1);`
- L191 _public prototype_ `int32 GetState() const;`
- L193 _public prototype_ `FString GetCurrentState() const;`
- L195 _public prototype_ `void SetState(int32 InState);`
- L197 _public prototype_ `void SetCurrentState(const FString& StateName);`
- L199 _public prototype_ `void SetRandomValues();`
- L201 _public prototype_ `void SetRandomValuesFromStream(const FRandomStream& InStream);`
- L203 _public prototype_ `void SetDefaultValue(int32 ParamIndex);`
- L205 _public prototype_ `void SetDefaultValues();`
- L207 _public prototype_ `bool IsMultilayerProjector(const FString& ParamName) const;`
- L209 _public prototype_ `int32 NumProjectorLayers(const FName& ParamName) const;`
- L211 _public prototype_ `void CreateLayer(const FName& ParamName, int32 Index);`
- L213 _public prototype_ `void RemoveLayerAt(const FName& ParamName, int32 Index);`
- L215 _public prototype_ `FMultilayerProjectorLayer GetLayer(const FName& ParamName, int32 Index) const;`
- L217 _public prototype_ `void UpdateLayer(const FName& ParamName, int32 Index, const FMultilayerProjectorLayer& Layer);`
- L220 _public prototype_ `TSharedPtr<UE::Mutable::Private::FParameters> GetParameters() const;` — Return a Mutable Core object containing all parameters.
- L222 _public prototype_ `FString ToString() const;`
- L225 _public member_ `TObjectPtr<UCustomizableObject> CustomizableObject = nullptr;` — `UPROPERTY()`
- L228 _public member_ `TArray<FCustomizableObjectBoolParameterValue> BoolParameters;` — `UPROPERTY()`
- L231 _public member_ `TArray<FCustomizableObjectIntParameterValue> IntParameters;` — `UPROPERTY()`
- L234 _public member_ `TArray<FCustomizableObjectFloatParameterValue> FloatParameters;` — `UPROPERTY()`
- L237 _public member_ `TArray<FCustomizableObjectTextureParameterValue> TextureParameters;` — `UPROPERTY()`
- L240 _public member_ `TArray<FCustomizableObjectSkeletalMeshParameterValue> SkeletalMeshParameters;` — `UPROPERTY()`
- L243 _public member_ `TArray<FCustomizableObjectMaterialParameterValue> MaterialParameters;` — `UPROPERTY()`
- L246 _public member_ `TArray<FCustomizableObjectVectorParameterValue> VectorParameters;` — `UPROPERTY()`
- L249 _public member_ `TArray<FCustomizableObjectProjectorParameterValue> ProjectorParameters;` — `UPROPERTY()`
- L252 _public member_ `TArray<FCustomizableObjectTransformParameterValue> TransformParameters;` — `UPROPERTY()`
- L255 _public member_ `TArray<FCustomizableObjectExternalTypeParameterValue> ExternalTypeParameters;` — `UPROPERTY()`
- L258 _public member_ `int32 State = 0;` — `UPROPERTY()`
- L261 _public member_ `bool bBuildParameterRelevancy = false;` — If this is set to true, when updating the instance an additional step will be performed to calculate the list of instance parameters that are relevant for the current parameter values.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CUSTOMIZABLEOBJECT_API`
- L24 _typedef_ `typedef TMap<const UCustomizableObjectInstance*, FMutableUpdateCandidate> FMutableInstanceUpdateMap;`
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Mutable` (scope `UE`)
- L26 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/CustomizableObject/Public/MuCO/CustomizableObjectInstanceUsage.h` (Public)


#### class `UCustomizableObjectInstanceUsage`  
`class UCustomizableObjectInstanceUsage : public UObject`  
_L22-113_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = (CustomizableObject))`
- inherits: `UObject`
- desc: This class can be used instead of a UCustomizableComponent (for example for non-BP projects) to link a UCustomizableObjectInstance and a USkeletalComponent so that the CustomizableObjectSystem takes care of updating it and its LODs, streaming, etc. It's a UObject, so it will be much cheaper than a UCustomizableComponent as it won't have to refresh its transforms every time it's moved.
- L30 _public prototype_ `UCustomizableObjectInstanceUsage();` — Own interface
- L32 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L33 _public prototype_ `virtual void PostLoad() override;`
- L34 _public prototype_ `virtual void BeginDestroy() override;`
- L37 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L41 _public prototype_ `void SetCustomizableObjectInstance(UCustomizableObjectInstance* CustomizableObjectInstance);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstanceUsage)`
- L44 _public prototype_ `UCustomizableObjectInstance* GetCustomizableObjectInstance() const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstanceUsage)`
- L47 _public prototype_ `void SetComponentName(const FName& Name);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstanceUsage)`
- L50 _public prototype_ `FName GetComponentName() const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstanceUsage)`
- L54 _public prototype_ `void AttachTo(USkeletalMeshComponent* SkeletalMeshComponent);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstanceUsage)` — Attach this Customizable Object Instance Usage to a Skeletal Mesh Component to be customized.
- L58 _public prototype_ `USkeletalMeshComponent* GetAttachParent() const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstanceUsage)` — Get the parent Skeletal Mesh Component this Customizable Object Instance Usage is attached to.
- L62 _public prototype_ `void UpdateSkeletalMeshAsync(bool bNeverSkipUpdate_DEPRECATED = false, bool bIgnoreCloseDist_DEPRECATED = false, bool bForceHighPriority = false);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObject)` — Update Skeletal Mesh asynchronously.
- L66 _public prototype_ `void UpdateSkeletalMeshAsyncResult(FInstanceUpdateDelegate Callback, bool bIgnoreCloseDist = false, bool bForceHighPriority = false);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstance)` — Update Skeletal Mesh asynchronously. Callback will be called once the update finishes, even if it fails.
- L71 _public prototype_ `void SetSkipSetReferenceSkeletalMesh(bool bSkip);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstanceUsage)` — Set to true to avoid automatically replacing the Skeletal Mesh of the parent Skeletal Mesh Component by the Reference Skeletal Mesh. If SkipSetSkeletalMeshOnAttach is true, it will not replace it.
- L74 _public prototype_ `bool GetSkipSetReferenceSkeletalMesh() const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstanceUsage)`
- L78 _public prototype_ `void SetSkipSetSkeletalMeshOnAttach(bool bSkip);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstanceUsage)` — Set to true to avoid automatically replacing the Skeletal Mesh of the parent Skeletal Mesh Component with any mesh.
- L80 _public prototype_ `UCustomizableObjectInstanceUsagePrivate* GetPrivate();`
- L82 _public prototype_ `const UCustomizableObjectInstanceUsagePrivate* GetPrivate() const;`
- L84 _public member_ `FCustomizableObjectInstanceUsageUpdatedDelegate UpdatedDelegate;`
- L89 _private member_ `TWeakObjectPtr<USkeletalMeshComponent> UsedSkeletalMeshComponent;` — `UPROPERTY()` — If the outer is no CustomizableSkeletalComponent, this SkeletalComponent will be used
- L93 _private member_ `TObjectPtr<UCustomizableObjectInstance> UsedCustomizableObjectInstance;` — `UPROPERTY(EditAnywhere, Category = CustomizableObjectInstanceUsage, meta = (DisplayName = "Customizable Object Instance"))` — If the outer is no CustomizableSkeletalComponentd, this Instance will be used
- L96 _private member_ `FName UsedComponentName;` — `UPROPERTY(EditAnywhere, Category = CustomizableObjectInstanceUsage, meta = (DisplayName = "Component Name"))`
- L100 _private member_ `bool bUsedSkipSetReferenceSkeletalMesh = false;` — `UPROPERTY(EditAnywhere, Category = CustomizableObjectInstanceUsage, meta = (DisplayName = "Skip Set Reference Skeletal Mesh"))` — Used to avoid replacing the SkeletalMesh of the parent component by the ReferenceSkeletalMesh if bPendingSetSkeletalMesh is true
- L103 _private member_ `bool bUsedSkipSetSkeletalMeshOnAttach = false;` — `UPROPERTY(EditAnywhere, Category = CustomizableObjectInstanceUsage, meta = (DisplayName = "Skip Set Skeletal Mesh On Attach"))`
- L106 _private member_ `TObjectPtr<UCustomizableObjectInstanceUsagePrivate> Private;` — `UPROPERTY(Instanced)`
- L109 _private member_ `TWeakObjectPtr<UCustomizableObjectInstance> OldCustomizableObjectInstance;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CUSTOMIZABLEOBJECT_API`
- L15 _delegate_ `DECLARE_DELEGATE(FCustomizableObjectInstanceUsageUpdatedDelegate);`
- L15 _prototype_ `DECLARE_DELEGATE(FCustomizableObjectInstanceUsageUpdatedDelegate);`

### `Plugins/Mutable/Source/CustomizableObject/Public/MuCO/CustomizableObjectParameterTypeDefinitions.h` (Public)


#### enum `EMutableParameterType`  
`enum class EMutableParameterType : uint8`  
_L15-28_
- reflection: `UENUM(BlueprintType)`
- L17 _public enumerator_ `None UMETA(DisplayName = "Unknown")`
- L18 _public enumerator_ `Bool UMETA(DisplayName = "Boolean")`
- L19 _public enumerator_ `Int UMETA(DisplayName = "Integer")`
- L20 _public enumerator_ `Float UMETA(DisplayName = "Float")`
- L21 _public enumerator_ `Color UMETA(DisplayName = "Color")`
- L22 _public enumerator_ `Projector UMETA(DisplayName = "Projector")`
- L23 _public enumerator_ `Texture UMETA(DisplayName = "Texture")`
- L24 _public enumerator_ `Transform UMETA(DisplayName = "Transform")`
- L25 _public enumerator_ `SkeletalMesh UMETA(DisplayName = "SkeletalMesh")`
- L26 _public enumerator_ `Material UMETA(DisplayName = "Material")`
- L27 _public enumerator_ `InstancedStruct UMETA(DisplayName = "InstancedStruct")`

#### enum `ECustomizableObjectGroupType`  
`enum class ECustomizableObjectGroupType : uint8`  
_L32-38_
- reflection: `UENUM(BlueprintType)`
- L34 _public enumerator_ `COGT_TOGGLE UMETA(DisplayName = "Toggle")`
- L35 _public enumerator_ `COGT_ALL UMETA(DisplayName = "All")`
- L36 _public enumerator_ `COGT_ONE UMETA(DisplayName = "One")`
- L37 _public enumerator_ `COGT_ONE_OR_NONE UMETA(DisplayName = "One or None")`

#### enum `EMutableCompileMeshType`  
`enum class EMutableCompileMeshType : uint8`  
_L43-50_
- reflection: `UENUM(BlueprintType)`
- desc: Customizable object mesh compilation options
- L45 _public enumerator_ `Full UMETA(DisplayName = "Full object")` — Compile this CO, and add all COs in the whole hierarchy
- L46 _public enumerator_ `Local UMETA(DisplayName = "Just local object")` — Compile this CO and add all parents until whole graph root
- L47 _public enumerator_ `LocalAndChildren UMETA(DisplayName = "Local object and children")` — Compile this CO and add all children and parents until whole graph root
- L48 _public enumerator_ `AddWorkingSetNoChildren UMETA(DisplayName = "Add working set, no children")` — Add to the compilation all COs in the Working Set array and all parents of this object and all parents of each element in the Working Set array until whole graph root, don't include this CO's children
- L49 _public enumerator_ `AddWorkingSetAndChildren UMETA(DisplayName = "Add working set and children")` — Add to the compilation all COs in the Working Set array and all parents of this object and all parents of each element in the Working Set array until whole graph root, include this CO's children

#### struct `FCustomizableObjectBoolParameterValue`  
`struct FCustomizableObjectBoolParameterValue`  
_L54-70_
- reflection: `USTRUCT(BlueprintType)`
- L58 _public member_ `static constexpr bool DEFAULT_PARAMETER_VALUE = false;`
- L60 _public member_ `inline static const FString DEFAULT_PARAMETER_VALUE_NAME;`
- L63 _public member_ `FString ParameterName;` — `UPROPERTY(Category = CustomizableObjectBoolParameterValue, VisibleAnywhere)`
- L66 _public member_ `bool ParameterValue = true;` — `UPROPERTY(Category = CustomizableObjectBoolParameterValue, VisibleAnywhere)`
- L69 _public member_ `FGuid Id;` — `UPROPERTY(Category = CustomizableObjectBoolParameterValue, VisibleAnywhere)`

#### struct `FCustomizableObjectIntParameterValue`  
`struct FCustomizableObjectIntParameterValue`  
_L83-112_
- reflection: `USTRUCT(BlueprintType)`
- L87 _public member_ `static constexpr int32 DEFAULT_PARAMETER_VALUE = INDEX_NONE;`
- L90 _public member_ `FString ParameterName;` — `UPROPERTY(Category = CustomizableObjectIntParameterValue, VisibleAnywhere)`
- L94 _public member_ `FString ParameterValueName;` — `UPROPERTY(Category = CustomizableObjectIntParameterValue, VisibleAnywhere)` — This is what we actually want to store.
- L97 _public member_ `FGuid Id;` — `UPROPERTY(Category = CustomizableObjectIntParameterValue, VisibleAnywhere)`
- L101 _public member_ `TArray<FString> ParameterRangeValueNames;` — `UPROPERTY()` — Same as ParameterValueName but for multidimensional params
- L103 _public function_ `FCustomizableObjectIntParameterValue()`
- L107 _public function_ `FCustomizableObjectIntParameterValue(const FString & InParamName, const FString & InParameterValueName, const FGuid & InUid, const TArray<FString>& InParameterRangeValueNames) : ParameterName(InParamName), ParameterValueName(InParameterValueName), Id(InUid)`

#### struct `FCustomizableObjectFloatParameterValue`  
`struct FCustomizableObjectFloatParameterValue`  
_L130-147_
- reflection: `USTRUCT(BlueprintType)`
- L134 _public member_ `static constexpr float DEFAULT_PARAMETER_VALUE = 0;`
- L137 _public member_ `FString ParameterName;` — `UPROPERTY(Category = CustomizableObjectFloatParameterValue, VisibleAnywhere)`
- L140 _public member_ `float ParameterValue = 0.0f;` — `UPROPERTY(Category = CustomizableObjectFloatParameterValue, VisibleAnywhere)`
- L143 _public member_ `FGuid Id;` — `UPROPERTY(Category = CustomizableObjectFloatParameterValue, VisibleAnywhere)`
- L146 _public member_ `TArray<float> ParameterRangeValues;` — `UPROPERTY(Category = CustomizableObjectFloatParameterValue, VisibleAnywhere)`

#### struct `FCustomizableObjectTextureParameterValue`  
`struct FCustomizableObjectTextureParameterValue`  
_L165-180_
- reflection: `USTRUCT(BlueprintType)`
- L170 _public member_ `FString ParameterName;` — `UPROPERTY(Category = CustomizableObjectTextureParameterValue, VisibleAnywhere)`
- L173 _public member_ `TObjectPtr<UTexture> ParameterValue;` — `UPROPERTY(Category = CustomizableObjectTextureParameterValue, VisibleAnywhere)`
- L176 _public member_ `FGuid Id;` — `UPROPERTY(Category = CustomizableObjectTextureParameterValue, VisibleAnywhere)`
- L179 _public member_ `TArray<TObjectPtr<UTexture>> ParameterRangeValues;` — `UPROPERTY(Category = CustomizableObjectTextureParameterValue, VisibleAnywhere)`

#### struct `FCustomizableObjectSkeletalMeshParameterValue`  
`struct FCustomizableObjectSkeletalMeshParameterValue`  
_L198-213_
- reflection: `USTRUCT()`
- L203 _public member_ `FString ParameterName;` — `UPROPERTY(Category = CustomizableObjectSkeletalMeshParameterValue, VisibleAnywhere)`
- L206 _public member_ `TObjectPtr<USkeletalMesh> ParameterValue;` — `UPROPERTY(Category = CustomizableObjectSkeletalMeshParameterValue, VisibleAnywhere)`
- L209 _public member_ `FGuid Id;` — `UPROPERTY(Category = CustomizableObjectSkeletalMeshParameterValue, VisibleAnywhere)`
- L212 _public member_ `TArray<TObjectPtr<USkeletalMesh>> ParameterRangeValues;` — `UPROPERTY(Category = CustomizableObjectSkeletalMeshParameterValue, VisibleAnywhere)`

#### struct `FCustomizableObjectMaterialParameterValue`  
`struct FCustomizableObjectMaterialParameterValue`  
_L231-246_
- reflection: `USTRUCT()`
- L236 _public member_ `FString ParameterName;` — `UPROPERTY(Category = CustomizableObjectMaterialParameterValue, VisibleAnywhere)`
- L239 _public member_ `TObjectPtr<UMaterialInterface> ParameterValue;` — `UPROPERTY(Category = CustomizableObjectMaterialParameterValue, VisibleAnywhere)`
- L242 _public member_ `FGuid Id;` — `UPROPERTY(Category = CustomizableObjectMaterialParameterValue, VisibleAnywhere)`
- L245 _public member_ `TArray<TObjectPtr<UMaterialInterface>> ParameterRangeValues;` — `UPROPERTY(Category = CustomizableObjectMaterialParameterValue, VisibleAnywhere)`

#### struct `FCustomizableObjectVectorParameterValue`  
`struct FCustomizableObjectVectorParameterValue`  
_L264-278_
- reflection: `USTRUCT(BlueprintType)`
- L268 _public member_ `inline static const FLinearColor DEFAULT_PARAMETER_VALUE = FLinearColor::Black;`
- L271 _public member_ `FString ParameterName;` — `UPROPERTY(Category = CustomizableObjectVectorParameterValue, VisibleAnywhere)`
- L274 _public member_ `FLinearColor ParameterValue = FLinearColor(ForceInit);` — `UPROPERTY(Category = CustomizableObjectVectorParameterValue, VisibleAnywhere)`
- L277 _public member_ `FGuid Id;` — `UPROPERTY(Category = CustomizableObjectVectorParameterValue, VisibleAnywhere)`

#### struct `FCustomizableObjectTransformParameterValue`  
`struct FCustomizableObjectTransformParameterValue`  
_L291-305_
- reflection: `USTRUCT(BlueprintType)`
- L295 _public member_ `inline static const FTransform DEFAULT_PARAMETER_VALUE = FTransform::Identity;`
- L298 _public member_ `FString ParameterName;` — `UPROPERTY(Category = CustomizableObjectTransformParameterValue, VisibleAnywhere)`
- L301 _public member_ `FTransform ParameterValue = FTransform::Identity;` — `UPROPERTY(Category = CustomizableObjectTransformParameterValue, VisibleAnywhere)`
- L304 _public member_ `FGuid Id;` — `UPROPERTY(Category = CustomizableObjectTransformParameterValue, VisibleAnywhere)`

#### enum `ECustomizableObjectProjectorType`  
`enum class ECustomizableObjectProjectorType : uint8`  
_L319-324_
- reflection: `UENUM()`
- L321 _public enumerator_ `Planar = 0 UMETA(DisplayName = "Planar projection")`
- L322 _public enumerator_ `Cylindrical = 1 UMETA(DisplayName = "Cylindrical projection")`
- L323 _public enumerator_ `Wrapping = 2 UMETA(DisplayName = "Wrapping projection")`

#### struct `FCustomizableObjectProjector`  
`struct FCustomizableObjectProjector`  
_L328-352_
- reflection: `USTRUCT(BlueprintType)`
- L333 _public member_ `FVector3f Position = FVector3f(0, 0, 0);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CustomizableObjectProjector)`
- L336 _public member_ `FVector3f Direction = FVector3f(1, 0, 0);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CustomizableObjectProjector)`
- L339 _public member_ `FVector3f Up = FVector3f(0, 1, 0);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CustomizableObjectProjector)`
- L342 _public member_ `FVector3f Scale = FVector3f(10, 10, 100);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CustomizableObjectProjector)`
- L345 _public member_ `ECustomizableObjectProjectorType ProjectionType = ECustomizableObjectProjectorType::Planar;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CustomizableObjectProjector)`
- L349 _public member_ `float Angle = 2.0f * PI;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CustomizableObjectProjector)` — Just for cylindrical projectors, in radians
- L351 _public prototype_ `bool operator==(const FCustomizableObjectProjector& Other) const = default;`

#### struct `FCustomizableObjectProjectorParameterValue`  
`struct FCustomizableObjectProjectorParameterValue`  
_L381-398_
- reflection: `USTRUCT(BlueprintType)`
- L385 _public member_ `inline static const FCustomizableObjectProjector DEFAULT_PARAMETER_VALUE = {};`
- L388 _public member_ `FString ParameterName;` — `UPROPERTY(Category = CustomizableObjectVectorParameterValue, VisibleAnywhere)`
- L391 _public member_ `FCustomizableObjectProjector Value;` — `UPROPERTY(Category = CustomizableObjectVectorParameterValue, VisibleAnywhere)`
- L394 _public member_ `FGuid Id;` — `UPROPERTY(Category = CustomizableObjectVectorParameterValue, VisibleAnywhere)`
- L397 _public member_ `TArray<FCustomizableObjectProjector> RangeValues;` — `UPROPERTY(Category = CustomizableObjectVectorParameterValue, VisibleAnywhere)`

#### struct `FCustomizableObjectExternalTypeParameterValue`  
`struct FCustomizableObjectExternalTypeParameterValue`  
_L416-433_
- reflection: `USTRUCT(BlueprintType)`
- L420 _public member_ `inline static const FInstancedStruct DEFAULT_PARAMETER_VALUE = {};`
- L423 _public member_ `FString ParameterName;` — `UPROPERTY(Category = CustomizableObjectVectorParameterValue, VisibleAnywhere)`
- L426 _public member_ `FInstancedStruct ParameterValue;` — `UPROPERTY(Category = CustomizableObjectVectorParameterValue, VisibleAnywhere)`
- L429 _public member_ `FGuid Id;` — `UPROPERTY(Category = CustomizableObjectVectorParameterValue, VisibleAnywhere)`
- L432 _public member_ `TArray<FInstancedStruct> ParameterRangeValues;` — `UPROPERTY(Category = CustomizableObjectVectorParameterValue, VisibleAnywhere)`

#### Free symbols / members of external scopes

- L73 _function_ `inline uint32 GetTypeHash(const FCustomizableObjectBoolParameterValue& Key)`
- L115 _function_ `inline uint32 GetTypeHash(const FCustomizableObjectIntParameterValue& Key)`
- L150 _function_ `inline uint32 GetTypeHash(const FCustomizableObjectFloatParameterValue& Key)`
- L183 _function_ `inline uint32 GetTypeHash(const FCustomizableObjectTextureParameterValue& Key)`
- L216 _function_ `inline uint32 GetTypeHash(const FCustomizableObjectSkeletalMeshParameterValue& Key)`
- L249 _function_ `inline uint32 GetTypeHash(const FCustomizableObjectMaterialParameterValue& Key)`
- L281 _function_ `inline uint32 GetTypeHash(const FCustomizableObjectVectorParameterValue& Key)`
- L308 _function_ `inline uint32 GetTypeHash(const FCustomizableObjectTransformParameterValue& Key)`
- L355 _function_ `inline uint32 GetTypeHash(const FCustomizableObjectProjector& Key)`
- L368 _function_ `inline FArchive& operator<<(FArchive& Ar, FCustomizableObjectProjector& Data)`
- L401 _function_ `inline uint32 GetTypeHash(const FCustomizableObjectProjectorParameterValue& Key)`
- L436 _prototype_ `uint32 GetTypeHash(const FCustomizableObjectExternalTypeParameterValue& Key);`

### `Plugins/Mutable/Source/CustomizableObject/Public/MuCO/CustomizableObjectSkeletalMesh.h` (Public)


#### struct `FMutableMeshContext`  
`struct FMutableMeshContext`  
_L28-56_
- desc: Context required to stream in/out mesh LODs of a UCustomizableObjectSkeletalMesh
- L30 _public function_ `FMutableMeshContext(const TSharedRef<UE::Mutable::Private::FLiveInstance>& InLiveInstance) : LiveInstance(InLiveInstance)`
- L33 _public member_ `TSharedPtr<UE::Mutable::Private::FSystem> System;`
- L34 _public member_ `TSharedRef<UE::Mutable::Private::FLiveInstance> LiveInstance;`
- L36 _public member_ `TSharedPtr<FModelStreamableBulkData> ModelStreamableBulkData;`
- L38 _public member_ `UE::Mutable::Private::FSkeletalMeshId SkeletalMeshId;`
- L41 _public member_ `TArray<TArray<uint32>> SurfaceIDs;` — IDs per LOD
- L51 _public member_ `uint32 PendingRenderStateDirtyLODs = 0;` — Bits of the absolute LOD indices whose FSkelMeshRenderSections have been modified by mesh streaming and whose primitives have not been notified yet. Keep it in the mesh context so that cancelled requests don't leave primitives in an inconsistent state. Otherwise, the next request for the same LOD would find the sections already correct, skip the notification, and leave the primitives referencing stale section data.
- L53 _public prototype_ `void AddPendingRenderStateDirtyLODs(uint32 LODMask);`
- L54 _public prototype_ `bool HasPendingRenderStateDirtyLODs() const;`
- L55 _public prototype_ `void ClearPendingRenderStateDirtyLODs();`

#### class `UCustomizableObjectSkeletalMesh`  
`class UCustomizableObjectSkeletalMesh : public USkeletalMesh`  
_L64-83_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USkeletalMesh`
- desc: CustomizableObjectSkeletalMesh is a class inheriting from USkeletalMesh with the sole purpose of allowing skeletal meshes generated by Mutable to stream-in Mesh LODs.
- L72 _private prototype_ `void InitMutableStreamingData(const TSharedRef<FUpdateContextPrivate>& InOperationData, int32 ComponentIndex, const int32 FirstLOD, const int32 LODCount);`
- L75 _private prototype_ `virtual bool StreamIn(int32 NewMipCount, bool bHighPrio) override;`
- L78 _private member_ `FString CustomizableObjectPathName;`
- L80 _private member_ `TSharedPtr<FMutableMeshContext> MeshContext;`
- L82 _private member_ `UE::Mutable::Private::FSkeletalMeshId SkeletalMeshId;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API CUSTOMIZABLEOBJECT_API`

### `Plugins/Mutable/Source/CustomizableObject/Public/MuCO/CustomizableObjectSystem.h` (Public)


#### enum `ECustomizableObjectOptimizationLevel`  
`enum class ECustomizableObjectOptimizationLevel : uint8`  
_L47-53_
- reflection: `UENUM(BlueprintType)`
- L49 _public enumerator_ `None = 0`
- L50 _public enumerator_ `Minimal UE_DEPRECATED(5.6, "Converted internally to None. Use None instead.") = 1`
- L51 _public enumerator_ `Maximum = 2`
- L52 _public enumerator_ `FromCustomizableObject = 3` — Grab the optimization settings from the CO

#### enum `ECustomizableObjectTextureCompression`  
`enum class ECustomizableObjectTextureCompression : uint8`  
_L57-65_
- reflection: `UENUM(BlueprintType)`
- L60 _public enumerator_ `None = 0` — Don't use texture compression
- L62 _public enumerator_ `Fast` — Use Mutable's fast low-quality compression
- L64 _public enumerator_ `HighQuality` — Use Unreal's highest quality compression (100x slower to compress)

#### enum `ECustomizableObjectNumBoneInfluences`  
`enum class ECustomizableObjectNumBoneInfluences : uint8`  
_L69-77_
- reflection: `UENUM()`
- L72 _public enumerator_ `Four = 4` — The enum values can be used as the real numeric value of number of bone influences
- L74 _public enumerator_ `Eight = 8`
- L76 _public enumerator_ `Twelve = 12` — This is essentially the same as "Unlimited", but UE ultimately limits to 12

#### struct `FPendingReleaseMaterialsInfo`  
`struct FPendingReleaseMaterialsInfo`  
_L92-101_
- reflection: `USTRUCT()`
- L97 _public member_ `TArray<TObjectPtr<UMaterialInterface>> Materials;` — `UPROPERTY()`
- L100 _public member_ `int32 TicksUntilRelease = 0;` — `UPROPERTY()`

#### struct `FCustomizableObjectExternalTexture`  
`struct FCustomizableObjectExternalTexture`  
_L106-112_
- desc: Opaque representation of a possible registered value for texture parameters.
- L108 _public prototype_ `FCustomizableObjectExternalTexture() = default;`
- L110 _public member_ `FString Name;`
- L111 _public member_ `FName Value;`

#### class `UCustomizableObjectSystem`  
`class UCustomizableObjectSystem : public UObject`  
_L116-276_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L124 _public prototype_ `UCustomizableObjectSystem() = default;`
- L125 _public prototype_ `void InitSystem();`
- L129 _public prototype_ `static UCustomizableObjectSystem* GetInstance();` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = Status)` — Get the singleton object. It will be created if it doesn't exist yet.
- L132 _public prototype_ `static UCustomizableObjectSystem* GetInstanceChecked();` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = Status)`
- L137 _public prototype_ `static bool IsUpdateResultValid(const EUpdateResult UpdateResult);` — `UFUNCTION(BlueprintCallable, Category = Status)` — Determines if the result of the instance update is valid or not. @return true if the result is successful or has warnings, false if the result is from the Error category
- L140 _public prototype_ `static bool IsCreated();` — Return true if the singleton has been created. It is different than GetInstance in that GetInstance will create it if it doesn't exist.
- L144 _public prototype_ `static bool IsActive();` — Returns the current status of Mutable. Only when active is it possible to compile COs, generate instances, and stream textures. @return True if Mutable is enabled.
- L147 _public prototype_ `virtual void BeginDestroy() override;`
- L148 _public prototype_ `virtual FString GetDesc() override;`
- L155 _public prototype_ `bool LockObject(UCustomizableObject*);` — Lock a CustomizableObjects, preventing the generation or update of any of its instances Will return true if successful, false if it fails to lock because an update is already underway This is usually only used in the editor
- L156 _public prototype_ `void UnlockObject(UCustomizableObject*);`
- L161 _public prototype_ `bool CheckIfDiskOrMipUpdateOperationsPending(const UCustomizableObject& Object) const;` — Checks if there are any outstanding disk or mip update operations in flight for the parameter Customizable Object that may make it unsafe to compile at the moment. @return true if there are operations in flight and it's not safe to compile
- L164 _public prototype_ `void EditorSettingsChanged(const FEditorCompileSettings& InEditorSettings);` — Called whenever the Mutable Editor Settings change, copying the new value of the current needed settings to the Customizable Object System
- L167 _public prototype_ `bool IsAutoCompileEnabled() const;` — If true, uncompiled Customizable Objects will be compiled whenever an instance update is required
- L170 _public prototype_ `bool IsAutoCompileCommandletEnabled() const;` — Return true if inside commandlets uncompiled Customizable Objects will be compiled whenever an instance update is required.
- L173 _public prototype_ `void SetAutoCompileCommandletEnabled(bool bValue);` — Set if inside commandlets uncompiled Customizable Objects will be compiled whenever an instance update is required.
- L176 _public prototype_ `bool IsAutoCompilationSync() const;` — If true, uncompiled Customizable Objects will be compiled synchronously
- L180 _public prototype_ `bool IsSupport16BitBoneIndexEnabled() const;` — `UE_DEPRECATED(5.8, "All platforms now support 16-bit bone indices. This always returns true.")`
- L182 _public prototype_ `bool IsProgressiveMipStreamingEnabled() const;`
- L183 _public prototype_ `void SetProgressiveMipStreamingEnabled(bool bIsEnabled);`
- L187 _public prototype_ `void AddUncompiledCOWarning(const UCustomizableObject& InObject, FString const* OptionalLogInfo = nullptr);` — Show a warning on-screen and via a notification (if in Editor) and log an error when a CustomizableObject is being used and it's not compiled.  Callers can add additional information to the error log.
- L190 _public prototype_ `UCustomizableObjectSystemPrivate* GetPrivate();` — Give access to the internal object data.
- L191 _public prototype_ `const UCustomizableObjectSystemPrivate* GetPrivate() const;`
- L195 _public prototype_ `FString GetPluginVersion() const;` — `UFUNCTION(BlueprintCallable, Category = Status)` — Find out the version of the plugin
- L199 _public prototype_ `int32 GetNumInstances() const;` — `UFUNCTION(BlueprintCallable, Category = Status)` — Get the number of instances built and alive.
- L203 _public prototype_ `int32 GetNumPendingInstances() const;` — `UFUNCTION(BlueprintCallable, Category = Status)` — Get the number of instances waiting to be updated.
- L207 _public prototype_ `int32 GetTotalInstances() const;` — `UFUNCTION(BlueprintCallable, Category = Status)` — Get the total number of instances including built and not built.
- L211 _public prototype_ `int64 GetTextureMemoryUsed() const;` — `UFUNCTION(BlueprintCallable, Category = Status)` — Get the amount of GPU memory in use in bytes for textures generated by mutable.
- L215 _public prototype_ `int32 GetAverageBuildTime() const;` — `UFUNCTION(BlueprintCallable, Category = Status)` — Return the average build/update time of an instance in ms.
- L219 _public prototype_ `bool IsUpdating(const UCustomizableObjectInstance* Instance) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = CustomizableObjectSystem)` — Return true if the instance is being updated.
- L226 _public prototype_ `void SetWorkingMemory(int32 KiloBytes);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectSystem)` — Set Mutable's working memory limit (kilobytes). Mutable will flush internal caches to try to keep its memory consumption below the WorkingMemory (i.e., it is not a hard limit). The working memory limit will especially reduce the memory required to perform Instance Updates and Texture Streaming. Notice that Mutable does not track all its memory (e.g., UObjects memory is no tracked). This value can also be set using "mutable.WorkingMemory" CVar.
- L230 _public prototype_ `int32 GetWorkingMemory() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = CustomizableObjectSystem)` — Get Mutable's working memory limit (kilobytes). See SetWorkingMemory(int32).
- L236 _public prototype_ `static bool ShouldClearWorkingMemoryOnUpdateEnd();` — Get if mutable should clear its working memory between instance updates. @return True if the clearing of memory will be performed, false otherwise.
- L241 _public prototype_ `void SetGenerateInstancesWithinRange(bool bActive);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectSystem)` — Instances within the generation range to the ViewCenters will be generated, When an instance falls outside the generation range the generated resources (meshes, textured, etc) will be dereferenced, and meshes on the components cleared.
- L245 _public prototype_ `void SetInstanceGenerationRange(float Distance);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectSystem)` — Instance generation range around view centers when mutable.GenerateInstancesWithinRange is true
- L249 _public prototype_ `void AddViewCenter(const AActor* const InCentralActor);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectSystem)` — Add ViewCenters. Used to generate instances around when generating instances within a range.
- L253 _public prototype_ `void RemoveViewCenter(const AActor* const InCentralActor);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectSystem)` — Remove ViewCenters. Used to generate instances around when generating instances within a range.
- L257 _public prototype_ `void ClearViewCenters();` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectSystem)` — Clear ViewCenters. Used to generate instances around when generating instances within a range.
- L261 _private member_ `TObjectPtr<UCustomizableObjectSystemPrivate> Private = nullptr;` — `UPROPERTY(Transient)`
- L269 _public prototype_ `void EnableBenchmark();` — Enables the collection of internal Mutable performance data. It has a performance cost.
- L274 _public prototype_ `void EndBenchmark();` — Disables the reporting of mutable instance benchmarking data.

#### Free symbols / members of external scopes

- L5 _macro_ `#define UE_MUTABLE_MAX_OPTIMIZATION 2`
- L14 _macro_ `#define UE_API CUSTOMIZABLEOBJECT_API`
- L29 _externvar_ `extern TAutoConsoleVariable<bool> CVarClearWorkingMemoryOnUpdateEnd;`
- L31 _externvar_ `extern TAutoConsoleVariable<bool> CVarReuseImagesBetweenInstances;`
- L33 _externvar_ `extern TAutoConsoleVariable<bool> CVarEnableMeshCache;`
- L35 _externvar_ `extern TAutoConsoleVariable<bool> CVarEnableRealTimeMorphTargets;`
- L37 _externvar_ `extern TAutoConsoleVariable<bool> CVarRollbackFixModelDiskStreamerDataRace;`
- L39 _externvar_ `extern TAutoConsoleVariable<bool> CVarEnableReleaseMeshResources;`
- L41 _externvar_ `extern TAutoConsoleVariable<bool> CVarFixLowPriorityTasksOverlap;`
- L43 _externvar_ `extern TAutoConsoleVariable<bool> CVarRollbackReuseProgramCacheBetweenUpdates;`
- L80 _namespace_ `namespace EMutableProfileMetric`
- L82 _typedef_ `typedef uint8 Type;` (scope `EMutableProfileMetric`)
- L84 _variable_ `constexpr Type BuiltInstances = 1;` (scope `EMutableProfileMetric`)
- L85 _variable_ `constexpr Type UpdateOperations = 2;` (scope `EMutableProfileMetric`)
- L86 _variable_ `constexpr Type Count = 4;` (scope `EMutableProfileMetric`)

### `Plugins/Mutable/Source/CustomizableObject/Public/MuCO/CustomizableObjectUIData.h` (Public)


#### struct `FMutableUIMetadata`  
`struct FMutableUIMetadata`  
_L16-51_
- reflection: `USTRUCT(BlueprintType)`
- L22 _public member_ `FString ObjectFriendlyName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = UI)` — This is the name to be shown in UI
- L26 _public member_ `FString UISectionName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = UI)` — This is the name of the section where the object will be placed in UI
- L30 _public member_ `int32 UIOrder = 0;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = UI)` — This is the order of the object inside its section
- L34 _public member_ `TSoftObjectPtr<UTexture2D> UIThumbnail;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = UI)` — Thumbnail for UI
- L39 _public member_ `TSoftObjectPtr<UObject> EditorUIThumbnailObject;` — `UPROPERTY(EditAnywhere, Category = UI)` — Editor Only Parameter Thumbnail. In an editor parameter combobox, this option will be represented with the selected asset's thumbnail.
- L44 _public member_ `TMap<FString, FString> ExtraInformation;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = UI)` — Extra information to be used in UI building, with semantics completely defined by the game/UI programmer, with a key to identify the semantic of its related value
- L48 _public member_ `TMap<FString, TSoftObjectPtr<UObject>> ExtraAssets;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = UI)` — Extra assets to be used in UI building

#### struct `FMutableParamUIMetadata`  
`struct FMutableParamUIMetadata : public FMutableUIMetadata`  
_L55-71_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FMutableUIMetadata`
- L60 _public member_ `float MinimumValue = 0.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = UI)`
- L63 _public member_ `float MaximumValue = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = UI)`
- L68 _public member_ `FGameplayTagContainer GameplayTags;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = UI)` — Gameplay tags to take into consideration when filtering parameters. Only applies to the options shown in drop downs. Child object parameters and data table rows.

#### struct `FMutableStateUIMetadata`  
`struct FMutableStateUIMetadata : public FMutableUIMetadata`  
_L75-80_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FMutableUIMetadata`

### `Plugins/Mutable/Source/CustomizableObject/Public/MuCO/CustomizableObject_Deprecated.h` (Public)


#### struct `FCompilationOptions_DEPRECATED`  
`struct FCompilationOptions_DEPRECATED`  
_L11-23_
- reflection: `USTRUCT()`
- L16 _public member_ `ECustomizableObjectTextureCompression TextureCompression = ECustomizableObjectTextureCompression::Fast;` — `UPROPERTY()`
- L19 _public member_ `int32 OptimizationLevel = 2;` — `UPROPERTY()` — UE_MUTABLE_MAX_OPTIMIZATION;
- L22 _public member_ `uint64 EmbeddedDataBytesLimit = 1024;` — `UPROPERTY()`

### `Plugins/Mutable/Source/CustomizableObject/Public/MuCO/CustomizableSkeletalComponent.h` (Public)


#### class `UCustomizableSkeletalComponent`  
`class UCustomizableSkeletalComponent : public USceneComponent`  
_L21-101_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, ClassGroup = (CustomizableObject), meta = (BlueprintSpawnableComponent))`
- inherits: `USceneComponent`
- L32 _public member_ `int32 ComponentIndex;` — `UPROPERTY(BlueprintReadWrite, Category = CustomizableSkeletalComponent)` — This component index refers to the object list of components DEPRECATED: Use FNames instead with Get/SetComponentName
- L37 _private member_ `TObjectPtr<UCustomizableObjectInstance> CustomizableObjectInstance;` — `UPROPERTY(EditAnywhere, Category = CustomizableSkeletalComponent)`
- L40 _private member_ `FName ComponentName;` — `UPROPERTY(EditAnywhere, Category = CustomizableSkeletalComponent)`
- L43 _private member_ `bool bSkipSetReferenceSkeletalMesh = false;` — `UPROPERTY(EditAnywhere, Category = CustomizableSkeletalComponent)`
- L46 _private member_ `bool bSkipSetSkeletalMeshOnAttach = false;` — `UPROPERTY(EditAnywhere, Category = CustomizableSkeletalComponent)`
- L49 _private member_ `TObjectPtr<UCustomizableSkeletalComponentPrivate> Private;` — `UPROPERTY(Instanced)`
- L54 _public prototype_ `UCustomizableSkeletalComponent();` — Own interface
- L57 _public prototype_ `virtual void PostLoad();`
- L58 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L62 _public prototype_ `UCustomizableObjectInstanceUsage* GetInstanceUsage();` — `UFUNCTION(BlueprintCallable, Category = CustomizableSkeletalComponent)`
- L65 _public prototype_ `void SetComponentName(const FName& Name);` — `UFUNCTION(BlueprintCallable, Category = CustomizableSkeletalComponent)`
- L68 _public prototype_ `FName GetComponentName() const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableSkeletalComponent)`
- L71 _public prototype_ `UCustomizableObjectInstance* GetCustomizableObjectInstance() const;` — `UFUNCTION(BlueprintCallable, Category = CustomizableSkeletalComponent)`
- L74 _public prototype_ `void SetCustomizableObjectInstance(UCustomizableObjectInstance* Instance);` — `UFUNCTION(BlueprintCallable, Category = CustomizableSkeletalComponent)`
- L79 _public prototype_ `void SetSkipSetReferenceSkeletalMesh(bool bSkip);` — `UFUNCTION(BlueprintCallable, Category = CustomizableSkeletalComponent)` — Set to true to avoid automatically replacing the Skeletal Mesh of the parent Skeletal Mesh Component by the Reference Skeletal Mesh. If SkipSetSkeletalMeshOnAttach is true, it will not replace it.
- L83 _public prototype_ `void SetSkipSetSkeletalMeshOnAttach(bool bSkip);` — `UFUNCTION(BlueprintCallable, Category = CustomizableObjectInstanceUsage)` — Set to true to avoid automatically replacing the Skeletal Mesh of the parent Skeletal Mesh Component with any mesh.
- L87 _public prototype_ `void UpdateSkeletalMeshAsync(bool bForceUpdate = false);` — `UFUNCTION(BlueprintCallable, Category = CustomizableSkeletalComponent)` — Update Skeletal Mesh asynchronously.
- L91 _public prototype_ `void UpdateSkeletalMeshAsyncResult(FInstanceUpdateDelegate Callback, bool bIgnoreCloseDist = false, bool bForceHighPriority = false);` — `UFUNCTION(BlueprintCallable, Category = CustomizableSkeletalComponent)` — Update Skeletal Mesh asynchronously. Callback will be called once the update finishes, even if it fails.
- L95 _protected prototype_ `UCustomizableSkeletalComponentPrivate* GetPrivate();`
- L97 _protected prototype_ `const UCustomizableSkeletalComponentPrivate* GetPrivate() const;`
- L100 _protected prototype_ `virtual void OnAttachmentChanged() override;` — USceneComponent interface

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CUSTOMIZABLEOBJECT_API`
- L17 _delegate_ `DECLARE_DELEGATE(FCustomizableSkeletalComponentUpdatedDelegate);`
- L17 _prototype_ `DECLARE_DELEGATE(FCustomizableSkeletalComponentUpdatedDelegate);`

### `Plugins/Mutable/Source/CustomizableObject/Public/MuCO/CustomizableSkeletalMeshActor.h` (Public)


#### class `ACustomizableSkeletalMeshActor`  
`class ACustomizableSkeletalMeshActor : public ASkeletalMeshActor`  
_L18-69_
- reflection: `UCLASS(MinimalAPI, ClassGroup = CustomizableObject, Blueprintable, ComponentWrapperClass, ConversionRoot, meta = (ChildCanTick))`
- inherits: `ASkeletalMeshActor`
- L25 _public prototype_ `ACustomizableSkeletalMeshActor(const FObjectInitializer& Initializer);`
- L28 _public prototype_ `UCustomizableObjectInstance* GetCustomizableObjectInstance();` — `UFUNCTION(BlueprintCallable, Category = "CustomizableSkeletalMeshActor")`
- L31 _public prototype_ `USkeletalMeshComponent* GetSkeletalMeshComponent(const FName& ComponentName);` — `UFUNCTION(BlueprintCallable, Category = "CustomizableSkeletalMeshActor")`
- L35 _public prototype_ `void SetDebugMaterial(UMaterialInterface* InDebugMaterial);` — `UE_DEPRECATED(5.6, "Plase replace with custom code.")` — `UFUNCTION(BlueprintCallable, Category = CustomizableSkeletalMeshActor, meta=(DeprecatedFunction))`
- L39 _public prototype_ `void EnableDebugMaterial(bool bEnableDebugMaterial);` — `UE_DEPRECATED(5.6, "Plase replace with custom code.")` — `UFUNCTION(BlueprintCallable, Category = CustomizableSkeletalMeshActor, meta=(DeprecatedFunction))`
- L41 _public prototype_ `UCustomizableSkeletalMeshActorPrivate* GetPrivate();`
- L42 _public prototype_ `const UCustomizableSkeletalMeshActorPrivate* GetPrivate() const;`
- L47 _private prototype_ `void SwitchComponentsMaterials(UCustomizableObjectInstance* Instance);` — `UFUNCTION()` — DEPRECATED
- L51 _private member_ `TArray<TObjectPtr<UCustomizableSkeletalComponent>> CustomizableSkeletalComponents;` — `UPROPERTY(VisibleAnywhere, Category = CustomizableSkeletalMeshActor)` — TODO: There are as many as components in the CO (not in the COI).
- L55 _private member_ `TArray<TObjectPtr<USkeletalMeshComponent>> SkeletalMeshComponents;` — `UPROPERTY(VisibleAnywhere, Category = CustomizableSkeletalMeshActor)` — TODO: There are as many as components in the CO (not in the COI).
- L59 _private member_ `TObjectPtr<UMaterialInterface> DebugMaterial;` — `UPROPERTY()` — DEPRECATED
- L62 _private member_ `bool bDebugMaterialEnabled = false;` — DEPRECATED
- L65 _private member_ `bool bRemoveDebugMaterial = false;` — DEPRECATED
- L68 _private member_ `TObjectPtr<UCustomizableSkeletalMeshActorPrivate> Private = nullptr;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CUSTOMIZABLEOBJECT_API`

### `Plugins/Mutable/Source/CustomizableObject/Public/MuCO/ICustomizableObjectModule.h` (Public)


#### struct `FRegisteredCustomizableObjectPinType`  
`struct FRegisteredCustomizableObjectPinType`  
_L12-16_
- L14 _public member_ `TWeakObjectPtr<const UCustomizableObjectExtension> Extension;`
- L15 _public member_ `FCustomizableObjectPinType PinType;`

#### struct `FRegisteredObjectNodeInputPin`  
`struct FRegisteredObjectNodeInputPin`  
_L18-25_
- L20 _public member_ `TWeakObjectPtr<const UCustomizableObjectExtension> Extension;`
- L22 _public member_ `FName GlobalPinName;` — A name for this pin that should be globally unique across extensions
- L24 _public member_ `FObjectNodeInputPin InputPin;`

#### class `ICustomizableObjectModule`  
`class ICustomizableObjectModule : public IModuleInterface`  
_L31-93_
- inherits: `IModuleInterface`
- desc: The public interface of the CustomizableObject module
- L41 _public function_ `static inline ICustomizableObjectModule& Get()` — Singleton-like access to ICustomizableObjectModule @return Returns CustomizableObjectModule singleton instance, loading the module on demand if needed
- L51 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L57 _public prototype_ `virtual ECustomizableObjectNumBoneInfluences GetNumBoneInfluences() const = 0;` — Returns the number of bone influences that Mutable will use according to the plugin conf
- L60 _public prototype_ `virtual FString GetPluginVersion() const = 0;` — Return a string representing the plugin version.
- L67 _public prototype_ `virtual void RegisterExtension(const UCustomizableObjectExtension* Extension) = 0;` — Extension functions These may only be called from the game thread
- L68 _public prototype_ `virtual void UnregisterExtension(const UCustomizableObjectExtension* Extension) = 0;`
- L69 _public prototype_ `virtual TArrayView<const UCustomizableObjectExtension* const> GetRegisteredExtensions() const = 0;`
- L78 _public prototype_ `virtual TArrayView<const FRegisteredCustomizableObjectPinType> GetExtendedPinTypes() const = 0;` — The results from these functions should only reference extensions that are still valid. If one of these functions returns data with an invalid weak pointer to a UCustomizableObjectExtension, it means that the extension was unloaded without calling UnregisterExtension.
- L79 _public prototype_ `virtual TArrayView<const FRegisteredObjectNodeInputPin> GetAdditionalObjectNodePins() const = 0;`
- L87 _public prototype_ `virtual void RegisterExternalOperation(const UScriptStruct* Operation) = 0;` — EXPERIMENTAL. USE WITH CAUTION! Register a new External Operation. All External Operations must inherit from UE::Mutable::FMutableOperation. It is only necessary to register operations in editor (to be able to create nodes). No need to register them at runtime.
- L92 _public prototype_ `virtual void UnregisterExternalOperation(const UScriptStruct* Operation) = 0;` — EXPERIMENTAL. USE WITH CAUTION! Unregister an External Operation.

#### Free symbols / members of external scopes

- L98 _prototype_ `UCustomizableObjectInstanceUsage* GetPlayerCustomizableObjectInstanceUsage(const int32 SlotID, const UWorld* CurrentWorld, const int32 PlayerIndex = 0);`
- L101 _prototype_ `void PrintParticipatingPackagesDiff(const TArray<FName>& OutOfDatePackages, const TArray<FName>& AddedPackages, const TArray<FName>& RemovedPackages, bool bReleaseVersion);`

### `Plugins/Mutable/Source/CustomizableObject/Public/MuCO/MultilayerProjector.h` (Public)


#### struct `FMultilayerProjectorLayer`  
`struct FMultilayerProjectorLayer`  
_L17-55_
- reflection: `USTRUCT(BlueprintType)`
- desc: Data structure representing a Multilayer Projector Layer. This struct is not actually saved, its values are obtained from the Instance Parameters.
- L26 _public prototype_ `void Read(const FCustomizableObjectInstanceDescriptor& Descriptor, const FString& ParamName, int32 Index);` — Read the Layer from the Instance Parameters. @param Descriptor Instance Descriptor. @param Index Index where to read the Layer in the Instance Parameters.
- L33 _public prototype_ `void Write(FCustomizableObjectInstanceDescriptor& Descriptor, const FString& ParamName, int32 Index) const;` — Write to Layer to the Instance Parameters. @param Descriptor Instance Descriptor. @param Index Index where to write the Layer in the Instance Parameters.
- L36 _public member_ `FVector Position;` — Layer position.
- L39 _public member_ `FVector Direction;` — Layer direction vector.
- L42 _public member_ `FVector Up;` — Layer up direction vector.
- L45 _public member_ `FVector Scale;` — Layer scale.
- L48 _public member_ `float Angle;` — Layer angle.
- L51 _public member_ `FString Image;` — Layer selected image.
- L54 _public member_ `float Opacity;` — Layer image opacity.

#### Free symbols / members of external scopes

- L58 _prototype_ `uint32 GetTypeHash(const FMultilayerProjectorLayer& Key);`

### `Plugins/Mutable/Source/CustomizableObject/Public/MuCO/Plugins/IMutableClothingModule.h` (Public)


#### class `IMutableClothingModule`  
`class IMutableClothingModule : public IModuleInterface`  
_L13-50_
- inherits: `IModuleInterface`
- L32 _public prototype_ `virtual bool UpdateClothSimulationLOD( int32 InSimulationLODIndex, UClothingAssetCommon& InOutClothingAsset, TConstArrayView<TArrayView<FMeshToMeshVertData>> InOutAttachedLODsRenderData) = 0;` — Updates in-place the InSimulationLODIndex of InOutClothingAsset physics mesh to conform to InOutAttachedLODsRenderData. Remaps InOutAttachedLODsRenderData indices to be valid after the modifications have been applied. NOTE: After calling UpdateClothSimulationLOD LOD transition mapping may contain invalid data if any modification has taken place. In that case, FixLODTransitionMappings() must be called after all InOutClothingAsset LODs have been updated. @param InSimulationLODIndex 		  Lod index in InOutClothingAsset to modify. @param InOutClothingAsset 		  Clothing asset to modify. @param InOutAttachedLODsRenderData List of mapping datas for all meshes attached to InOutClothingAsset's InSimulationLODIndex. @return true if the clothing asset has been modified, false otherwise.
- L46 _public prototype_ `virtual void FixLODTransitionMappings( int32 InSimulationLODIndex, UClothingAssetCommon& InOutClothingAsset) = 0;` — Fixes in-place LOD transition mappings for InSimulationLODIndex of InOutClothingAsset NOTE: FixLODTransitionMappings needs to run after all InOutClothingAsset LODs have been updated. @param InSimulationLODIndex LOD in InOutClothingAsset to fix. @param InOutClothingAsset   Clothing asset to fix.

#### Free symbols / members of external scopes

- L8 _macro_ `#define MUTABLE_CLOTHING_MODULE_NAME "MutableClothing"`
