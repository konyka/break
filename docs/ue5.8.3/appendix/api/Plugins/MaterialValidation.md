# Plugins / MaterialValidation

- module root: `Plugins/Editor/MaterialValidation/Source`
- headers: 13; symbols: 190
- symbol kinds: class=12, delegate=1, enum=2, enumerator=9, externvar=3, function=3, member=88, namespace=4, prototype=57, struct=11
- PrivateDependencyModuleNames: AssetDefinition, Core, CoreUObject, DataValidation, DeveloperSettings, Engine, InputCore, MaterialEditor, Projects, PropertyEditor, RHI, Slate, SlateCore, SourceControl, UnrealEd

### `Plugins/Editor/MaterialValidation/Source/Private/MaterialValidationAssetData.h` (Private)


#### struct `FStaticPermutationProperties`  
`struct FStaticPermutationProperties`  
_L15-47_
- reflection: `USTRUCT()`
- desc: Material instance properties that trigger a static permutation. This is a selected subset of FMaterialInstanceBasePropertyOverrides and may need updating if anything is added to that struct.
- L20 _public member_ `uint8 TwoSided : 1;` — `UPROPERTY()`
- L22 _public member_ `uint8 bIsThinSurface : 1;` — `UPROPERTY()`
- L24 _public member_ `uint8 DitheredLODTransition : 1;` — `UPROPERTY()`
- L26 _public member_ `uint8 bCastDynamicShadowAsMasked:1;` — `UPROPERTY()`
- L28 _public member_ `uint8 bOutputTranslucentVelocity : 1;` — `UPROPERTY()`
- L30 _public member_ `uint8 bHasPixelAnimation : 1;` — `UPROPERTY()`
- L32 _public member_ `uint8 bEnableTessellation : 1;` — `UPROPERTY()`
- L34 _public member_ `TEnumAsByte<EBlendMode> BlendMode;` — `UPROPERTY()`
- L36 _public member_ `TEnumAsByte<EMaterialShadingModel> ShadingModel;` — `UPROPERTY()`
- L38 _public member_ `float OpacityMaskClipValue;` — `UPROPERTY()`
- L40 _public member_ `uint32 UsageFlags;` — `UPROPERTY()`
- L42 _public prototype_ `FStaticPermutationProperties();`
- L44 _public prototype_ `bool operator==(const FStaticPermutationProperties& Other) const = default;`

#### struct `FStaticPermutationPropertyOverrideFlags`  
`struct FStaticPermutationPropertyOverrideFlags`  
_L54-82_
- reflection: `USTRUCT()`
- desc: Flags that enable override of the properties in FStaticPermutationProperties. This is a selected subset of FMaterialInstanceBasePropertyOverrides and may need updating if anything is added to that struct.
- L59 _public member_ `uint8 bOverride_OpacityMaskClipValue : 1;` — `UPROPERTY()`
- L61 _public member_ `uint8 bOverride_BlendMode : 1;` — `UPROPERTY()`
- L63 _public member_ `uint8 bOverride_ShadingModel : 1;` — `UPROPERTY()`
- L65 _public member_ `uint8 bOverride_DitheredLODTransition : 1;` — `UPROPERTY()`
- L67 _public member_ `uint8 bOverride_CastDynamicShadowAsMasked : 1;` — `UPROPERTY()`
- L69 _public member_ `uint8 bOverride_TwoSided : 1;` — `UPROPERTY()`
- L71 _public member_ `uint8 bOverride_bIsThinSurface : 1;` — `UPROPERTY()`
- L73 _public member_ `uint8 bOverride_OutputTranslucentVelocity : 1;` — `UPROPERTY()`
- L75 _public member_ `uint8 bOverride_bHasPixelAnimation : 1;` — `UPROPERTY()`
- L77 _public member_ `uint8 bOverride_bEnableTessellation : 1;` — `UPROPERTY()`
- L79 _public member_ `uint32 Override_UsageFlags;` — `UPROPERTY()`
- L81 _public prototype_ `FStaticPermutationPropertyOverrideFlags();`

#### struct `FMaterialValidationAssetData_Material`  
`struct FMaterialValidationAssetData_Material`  
_L90-110_
- reflection: `USTRUCT()`
- desc: Extracted data from UMaterial to be used for predicting the shader permutation ID of UMaterial and child UMaterialInstances. This is intended for storage external to the UMaterial so that we don't need to load it. In future this may be better in the AssetData, but we will need to resave all assets before we can rely on that.
- L95 _public member_ `TArray<uint32> StaticSwitchValues;` — `UPROPERTY()`
- L97 _public member_ `TArray<uint32> ComponentMaskValues;` — `UPROPERTY()`
- L99 _public member_ `FStaticPermutationProperties StaticProperties;` — `UPROPERTY()`
- L101 _public member_ `uint32 StaticPropertyLayoutHash = 0;` — `UPROPERTY()`
- L103 _public member_ `uint32 MaterialLayerHash = 0;` — `UPROPERTY()`
- L105 _public member_ `uint32 PermutationHash = 0;` — `UPROPERTY()`
- L107 _public member_ `uint16 StaticSwitchNum = 0;` — `UPROPERTY()`
- L109 _public member_ `uint16 ComponentMaskNum = 0;` — `UPROPERTY()`

#### struct `FMaterialValidationAssetData_MaterialInstance`  
`struct FMaterialValidationAssetData_MaterialInstance`  
_L118-138_
- reflection: `USTRUCT()`
- desc: Extracted data from UMaterialInstance to be used for predicting the shader permutation. This is intended for storage external to the UMaterialInstance so that we don't need to load it. In future this may be better in the AssetData, but we will need to resave all assets before we can rely on that.
- L123 _public member_ `TArray<uint32> StaticSwitchOverrideMask;` — `UPROPERTY()`
- L125 _public member_ `TArray<uint32> StaticSwitchOverrideValues;` — `UPROPERTY()`
- L127 _public member_ `TArray<uint32> ComponentMaskOverrideMask;` — `UPROPERTY()`
- L129 _public member_ `TArray<uint32> ComponentMaskOverrideValues;` — `UPROPERTY()`
- L131 _public member_ `FStaticPermutationProperties StaticProperties;` — `UPROPERTY()`
- L133 _public member_ `FStaticPermutationPropertyOverrideFlags StaticPropertyOverrideFlags;` — `UPROPERTY()`
- L135 _public member_ `uint32 MaterialLayerHash = 0;` — `UPROPERTY()`
- L137 _public member_ `uint32 PermutationHash = 0;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L140 _namespace_ `namespace MaterialValidation`
- L142 _prototype_ `uint32 BuildPermutationHash( FStaticPermutationProperties const& InStaticProperties, TConstArrayView<uint32> InStaticSwitchValues, TConstArrayView<uint32> InComponentMaskValues, uint32 InMaterialLayerHash );` (scope `MaterialValidation`)

### `Plugins/Editor/MaterialValidation/Source/Private/MaterialValidationChangelistTab.h` (Private)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace MaterialValidation`
- L9 _prototype_ `TSharedRef<SWidget> CreateChangelistTab();` (scope `MaterialValidation`) — Creates and returns the Changelists tab widget for the MaterialValidationToolkit.

### `Plugins/Editor/MaterialValidation/Source/Private/MaterialValidationCommandlet.h` (Private)


#### class `UMaterialValidationCommandlet`  
`class UMaterialValidationCommandlet : public UBaseIteratePackagesCommandlet`  
_L10-25_
- reflection: `UCLASS()`
- inherits: `UBaseIteratePackagesCommandlet`
- desc: Commandlet to validate and update the UMaterialValidationGroup assets.
- L15 _private prototype_ `virtual void InitializePackageNames(const TArray<FString>& Tokens, TArray<FString>& MapPathNames, bool& bExplicitPackages) override;`
- L16 _private prototype_ `virtual bool ShouldSkipPackage(const FString& Filename) override;`
- L17 _private prototype_ `virtual void PerformAdditionalOperations(class UObject* Object, bool& bSavePackage) override;`
- L22 _private member_ `bool bUpdateMaterials = true;` — true to update the materials bu removing those not found on disk and adding any materials found in the search paths. Disabled with UpdateMaterials=0 on commandline.
- L24 _private member_ `bool bUpdateMaterialPermutations = true;` — true to search for all material instances and add them to the approved list. Disabled with UpdatePermutations=0 on commandline.

### `Plugins/Editor/MaterialValidation/Source/Private/MaterialValidationConfig.h` (Private)


#### class `UMaterialValidationConfig`  
`class UMaterialValidationConfig : public UDeveloperSettings`  
_L14-37_
- reflection: `UCLASS(config = Editor, defaultconfig, meta = (DisplayName = "Data Validation Settings"), MinimalAPI)`
- inherits: `UDeveloperSettings`
- desc: Configuration for the material validation system.
- L19 _private function_ `virtual bool SupportsAutoRegistration() const override` — Disable auto registration of config UI becuase we use a specific detail customization below.
- L24 _public member_ `bool bEnable = false;` — `UPROPERTY(config, EditAnywhere, Category = MaterialPermutationBudget, meta = (DisplayName = "Enable Validation"))` — Set true to enable validation.
- L28 _public member_ `int32 ShaderBudgetShowThreshold = 0;` — `UPROPERTY(config, EditAnywhere, Category = MaterialPermutationBudget, meta = (EditCondition = "bEnable"))` — Threshold for shader count increase before showing to user.
- L32 _public member_ `int32 ShaderBudgetApprovalThreshold = 0;` — `UPROPERTY(config, EditAnywhere, Category = MaterialPermutationBudget, meta = (EditCondition = "bEnable"))` — Threshold for shader count increase before triggering further submit approval.
- L36 _public member_ `TArray<TSoftObjectPtr<UMaterialValidationGroup>> Groups;` — `UPROPERTY(config, EditAnywhere, Category = MaterialPermutationBudget, meta = (EditCondition = "bEnable", DisplayName = "Material Validation Groups"))` — An array of Material Validation Groups to use during validation.

#### class `FDataValidationSettingsCustomization`  
`class FDataValidationSettingsCustomization : public IDetailCustomization`  
_L43-49_
- inherits: `IDetailCustomization`
- desc: Detail customization which adds the UMaterialValidationConfig properties to the core UDataValidationSettings config panel. This simplifies the UI by keeping related items in a sinlge place.
- L45 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L48 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`

### `Plugins/Editor/MaterialValidation/Source/Private/MaterialValidationGroup.h` (Private)


#### struct `FMaterialValidationDesc`  
`struct FMaterialValidationDesc`  
_L11-41_
- reflection: `USTRUCT(MinimalAPI)`
- desc: Description of validation setup for a single UMaterial.
- L17 _public member_ `FMaterialValidationAssetData_Material AssetData;` — `UPROPERTY()` — The asset data for the material.
- L21 _public member_ `TArray<FMaterialValidationAssetData_MaterialInstance> MaterialInstanceAssetDatas;` — `UPROPERTY()` — The non-default asset datas from all of the material instances in the material hierarchy.
- L28 _public member_ `TMap<FString, int32> MaterialInstances;` — `UPROPERTY()` — Map of UMaterialInstance asset paths to MaterialInstanceAssetDatas array index. Value of -1 indicates a default AssetData. Paths are FString to avoid references to the actual assets which would need managing on asset delete etc.
- L32 _public member_ `TArray<uint32> PermutationHashes;` — `UPROPERTY()` — Array of material permutations not including the one from the base material which is stored in AssetData.PermutationHash.
- L36 _public member_ `int32 NumShadersBase = 0;` — `UPROPERTY()` — Number of shader types on the base material permutation.
- L40 _public member_ `int32 NumShadersTotal = 0;` — `UPROPERTY(VisibleAnywhere, Category = Material)` — Total sum of shader types for all permutations found of this material.

#### class `UMaterialValidationGroup`  
`class UMaterialValidationGroup : public UDataAsset`  
_L45-91_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UDataAsset`
- desc: Data Asset containing the validation setup for a group of UMaterials.
- L52 _public member_ `TArray<FDirectoryPath> MaterialPaths;` — `UPROPERTY(EditAnywhere, Category = Material)` — Array of explicit directory paths that we use when searching for UMaterial packages that need validating.
- L56 _public member_ `TArray<FDirectoryPath> MaterialExcludePaths;` — `UPROPERTY(EditAnywhere, Category = Material)` — Array of explicit directory paths that we exclude when searching for UMaterial packages that need validating.
- L60 _public member_ `bool bAddProjectPath;` — `UPROPERTY(EditAnywhere, Category = Material, meta = (DisplayName = "Include All Project Content"))` — Use the project content path in addition to MaterialPaths when searching for UMaterials.
- L64 _public member_ `bool bAddProjectPluginPaths;` — `UPROPERTY(EditAnywhere, Category = Material, meta = (DisplayName = "Include All Project Plugin Content"))` — Use all project plugin content paths in addition to MaterialPaths when searching for UMaterials.
- L68 _public member_ `TMap<FString, FMaterialValidationDesc> Materials;` — `UPROPERTY()` — Map of UMaterial asset paths to validation descriptions. Paths are FString to avoid references to the actual assets which would need managing on asset delete etc.
- L72 _public prototype_ `void GetMaterialPaths(TArray<FSoftObjectPath>& OutMaterialPaths) const;` — `UFUNCTION(BlueprintPure, Category = Material)` — Get UMaterial assets resolved to FSoftObjectPaths.
- L79 _public prototype_ `void UpdateMaterials();` — `UFUNCTION(CallInEditor, Category = Actions)` — Add all Material assets found under the material search paths. The new material assets will have empty permutation lists.
- L86 _public prototype_ `void UpdatePermutations();` — `UFUNCTION(CallInEditor, Category = Actions)` — Update current state of all Materials. For each material this will traverse the material instance hierarchy and add all existing permutations to the permutation list.
- L89 _protected prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L90 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`

### `Plugins/Editor/MaterialValidation/Source/Private/MaterialValidationGroupDiff.h` (Private)


#### class `SMaterialValidationGroupDiff`  
`class SMaterialValidationGroupDiff : public SCompoundWidget`  
_L11-34_
- inherits: `SCompoundWidget`
- desc: Widget for the UMaterialValidationGroup asset diff window.
- L14 _public function_ `SLATE_BEGIN_ARGS(SMaterialValidationGroupDiff)`
- L15 _public prototype_ `SLATE_ARGUMENT(UMaterialValidationGroup const*, OldGroup) SLATE_ARGUMENT(UMaterialValidationGroup const*, NewGroup) SLATE_ARGUMENT(FRevisionInfo, OldRevision) SLATE_ARGUMENT(FRevisionInfo, NewRevision) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L25 _public prototype_ `static TSharedPtr<SWindow> CreateDiffWindow( UMaterialValidationGroup const* InOldGroup, UMaterialValidationGroup const* InNewGroup, FRevisionInfo const& InOldRevision, FRevisionInfo const& InNewRevision);` — Create and display a standalone diff window.
- L32 _private member_ `TWeakObjectPtr<const UMaterialValidationGroup> OldGroup;`
- L33 _private member_ `TWeakObjectPtr<const UMaterialValidationGroup> NewGroup;`

### `Plugins/Editor/MaterialValidation/Source/Private/MaterialValidationLibrary.h` (Private)


#### class `UMaterialValidationLibrary`  
`class UMaterialValidationLibrary : public UBlueprintFunctionLibrary`  
_L21-182_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "MaterialValidationLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- desc: Material validation functionality exposed as a library of Blueprint functions.
- L32 _private prototype_ `static void GetAllGroups(TArray<UMaterialValidationGroup*>& OutGroups, bool bInSyncLoad);` — `UFUNCTION(BlueprintCallable, Category = Material)` — Get all configured Material Validation Groups. @param OutGroups		The returned array of groups. @param bInSyncLoad	Whether to sync load the group assets. When false we don't return unloaded group objects, but we do trigger async loading for them.
- L40 _private prototype_ `static void ResetGroup(UMaterialValidationGroup* InGroup);` — `UFUNCTION(BlueprintCallable, Category = Material)` — Remove all UMaterials from a Material Validation Group. @param InGroup	The group to reset.
- L50 _private prototype_ `static void AddMissingMaterialsToGroup(UMaterialValidationGroup* InGroup);` — `UFUNCTION(BlueprintCallable, Category = Material)` — Add all UMaterials to the Material Validation Group which are found in its material search directories. This will only add materials, and not remove existing ones. Materials are not updated with their permutations, so that newly found materials will have no approved permutations. @param InGroup	The group to add materials to.
- L58 _private prototype_ `static void RemoveInvalidMaterialsFromGroup(UMaterialValidationGroup* InGroup);` — `UFUNCTION(BlueprintCallable, Category = Material)` — Remove all UMaterials that no longer exist on disk from the Material Validation Group. @param InGroup	The group to update.
- L66 _private prototype_ `static void UpdateMaterialPermutationsInGroup(UMaterialValidationGroup* InGroup);` — `UFUNCTION(BlueprintCallable, Category = Material)` — Recalculate and reregister all existing permutations for all the existing materials in a Material Validation Group (can be slow to load and analyze the tree of material instances). @param InGroup	The group to update.
- L75 _private prototype_ `static FSoftObjectPath ResolveAssetPath(FString const& InAssetPath);` — Resolve a asset path string to a FSoftObjectPath while handling asset redirectors. @param	InAssetPath		A asset path. @returns	The FSoftObjectPath of the resolved asset.
- L86 _private prototype_ `static void IsMaterialInGroup(UMaterialValidationGroup const* InGroup, UMaterial* InMaterial, bool& bOutIsInGroupPath, bool& bOutIsInGroup);` — `UFUNCTION(BlueprintCallable, Category = Material)` — Get whether a material belongs to a group. @param	InGroup				The group to use. @param	InMaterial			The material to validate. @param	bOutIsInGroupPath	Returns true if the material is in the validation group search path. @param	bOutIsInGroup		Returns true if the material is in the validation group material list.
- L97 _private prototype_ `static void IsMaterialInstanceInGroup(UMaterialValidationGroup const* InGroup, UMaterialInstanceConstant* InMaterialInstance, bool& bOutMaterialInGroup, bool& bOutMaterialPermutationInGroup);` — `UFUNCTION(BlueprintCallable, Category = Material)` — Get whether a material instance belongs to the group and whether it has a known permutation. @param	InGroup							The group to use. @param	InMaterialInstance				The material instance to validate. @param	bOutMaterialInGroup				Returns true if the base material is in the validation group material list. @param	bOutMaterialPermutationInGroup	Returns true if the material instance permutation is in the permutation list.
- L108 _private prototype_ `static int32 GetShaderCount(UMaterialValidationGroup const* InGroup, UMaterial* InMaterial);` — `UFUNCTION(BlueprintCallable, Category = Material)` — Get the number of shaders used by all permutations of a base material using only the information stored in the group. @param	InGroup					The group to use. @param	InMaterial				The base material to evaluate. @returns	The total number of shaders calculated at the last time we updated the group.
- L123 _private prototype_ `static int32 GetModifiedShaderCount( UMaterialValidationGroup const* InGroup, UMaterial* InMaterial, TArray<UMaterialInterface*> const& InModifiedObjects, TArray<UMaterialInterface*> const& InReplacementObjects, bool bForceLoadObjects = false);` — `UFUNCTION(BlueprintCallable, Category = Material, meta = (AutoCreateRefTerm = "InReplacementObjects"))` — Get the number of shaders used by all permutations of a base material taking into account local changes in the materials. @param	InGroup					The group to use. @param	InMaterial				The base material to evaluate. @param	InModifiedObjects		An array of loaded material objects that should be used instead of the corresponding stored database values when evaluating permutations. @param	InReplacementObjects	An array of loaded material objects in sync with InModifiedObjects. When the corresponding array item exists and is valid it is used to replace the object in InModifiedObjects when evaluation permutations. This can be used to evaluate the impact of using a different object. @param	bForceLoadObjects		When true, any hierarchy asset not already in memory is synchronously loaded from disk. @returns	The total number of shaders. This value is the best estimate that we can give without triggering asset loads if bForceLoad=false.
- L138 _private prototype_ `static void GetMaterialHierarchyInfo(UMaterialValidationGroup const* InGroup, FSoftObjectPath const& InBaseMaterialPath, FMaterialDatabaseAssetHierarchyInfo& OutInfo);` — `UFUNCTION(BlueprintCallable, Category = Material)` — Get all of the material instance data for a single material hierarchy. @param	InGroup				The group to use. @param	InBaseMaterialPath	The path of the base material to evaluate. @param	OutInfo				Returnsa an object containing all of the material instance data.
- L147 _private prototype_ `static void GetMaterialProperties(FMaterialDatabaseAssetHierarchyInfo const& InInfo, TArray<FMaterialDatabaseAssetPropertyDesc>& OutProperties);` — `UFUNCTION(BlueprintCallable, Category = Material)` — Get all the material properties for a material hierarchy. @param	InInfo			The full hierarchy info. This is typically resolved by first calling GetMaterialHierarchyInfo(). @param	OutProperties	Returns an array of property descriptions.
- L157 _private prototype_ `static void GetMaterialPropertyValues(FMaterialDatabaseAssetHierarchyInfo const& InInfo, int32 InMaterialIndex, TArray<FMaterialDatabaseAssetPropertyValue>& OutValues);` — `UFUNCTION(BlueprintCallable, Category = Material)` — Get all the material property values for a material instance in a material hierarchy. @param	InInfo			The full hierarchy info. This is typically resolved by first calling GetMaterialHierarchyInfo(). @param	InMaterialIndex	The index of the material instance in the hierarchy. The instances are in the order defined by FMaterialDatabaseAssetHierarchyInfo::MaterialPaths. @param	OutValues		Returns an array of property values, one for each of the material properties as returned by GetProperties().
- L167 _private prototype_ `static void GetMaterialPropertyValues(FMaterialDatabaseAssetHierarchyInfo const& InInfo, UMaterialInstanceConstant* InMaterialInstance, TArray<FMaterialDatabaseAssetPropertyValue>& OutValues);` — Get all the currently edited material property values for a live, possibly unsaved, material instance object. The property layout (switch and mask names) is taken from InInfo and must be for the same base material. @param	InInfo				The full hierarchy info for the base material (from GetMaterialHierarchyInfo()). @param	InMaterialInstance	The material instance object to read values from. @param	OutValues			Returns an array of property values, one for each of the material properties as returned by GetProperties().
- L181 _private prototype_ `static void GetMaterialValidationDescDiff(UMaterialValidationGroup const* InGroupOld, UMaterialValidationGroup const* InGroupNew, FSoftObjectPath const& InBaseMaterialPath, bool bAllowAssetLoad, TArray<FMaterialInstanceDiffResult>& OutDiffs);` — `UFUNCTION(BlueprintCallable, Category = Material)` — Get the diff between two versions of a UMaterialValidationGroup for a single base material. Compares the raw stored data. There is no asset registry dependency and it works for deleted instances. The first entry in OutDiffs always contains the base material entry if it changed. @param	InGroupOld				The older version of the group for comparison. @param	InGroupNew				The newer version of the group for comparison. @param	InBaseMaterialPath		The path of the base material to find in the groups and diff. @param	bAllowAssetLoad			If true then the base UMaterial is loaded to resolve static parameter names. If false then static parameters are given generic names. @param	OutDiffs				Returns one entry per changed material instance. Empty if no differences found.

### `Plugins/Editor/MaterialValidation/Source/Private/MaterialValidationLibraryTypes.h` (Private)


#### enum `EMaterialPropertyCategory`  
`enum class EMaterialPropertyCategory : uint8`  
_L11-19_
- reflection: `UENUM(BlueprintType)`
- desc: Enumeration of material instance property types.
- L13 _public enumerator_ `Default`
- L14 _public enumerator_ `StaticProperty`
- L15 _public enumerator_ `UsageFlag`
- L16 _public enumerator_ `StaticSwitch`
- L17 _public enumerator_ `ComponentMask`
- L18 _public enumerator_ `Count`

#### enum `EMaterialInstanceDiffType`  
`enum class EMaterialInstanceDiffType : uint8`  
_L23-28_
- reflection: `UENUM(BlueprintType)`
- desc: Whether a material instance was added, removed, or modified between two revisions.
- L25 _public enumerator_ `Modified`
- L26 _public enumerator_ `Added`
- L27 _public enumerator_ `Removed`

#### struct `FMaterialDatabaseAssetHierarchyInfo`  
`struct FMaterialDatabaseAssetHierarchyInfo`  
_L35-51_
- reflection: `USTRUCT(BlueprintType)`
- desc: Structure that collects all the resolved asset data for one material hierarchy in the material asset database. Typically this is extracted from the compact form stored in a UMaterialValidationGroup and used in UI views or for further analysis.
- L41 _public member_ `TArray<FSoftObjectPath> MaterialPaths;` — `UPROPERTY(BlueprintReadOnly, Category = Material)` — Array of material asset paths. This includes the base UMaterial asset in the first entry, and the child UMaterialInstance assets after that.
- L44 _public member_ `TArray<FMaterialValidationAssetData_MaterialInstance> MaterialAssetDatas;` — `UPROPERTY()` — Array of asset data info. This is synced with the MaterialPaths array.
- L47 _public member_ `TArray<FName> StaticSwitchNames;` — `UPROPERTY()` — Array of all StaticSwitch names. This matches the layout of all StaticSwitchOverrideValues arrays in the MaterialAssetDatas.
- L50 _public member_ `TArray<FName> ComponentMaskNames;` — `UPROPERTY()` — Array of all ComponentMask names. This matches the layout of all ComponentMaskOverrideValues arrays in the MaterialAssetDatas.

#### struct `FMaterialDatabaseAssetPropertyDesc`  
`struct FMaterialDatabaseAssetPropertyDesc`  
_L55-68_
- reflection: `USTRUCT(BlueprintType)`
- desc: Description of a material property in the material asset database.
- L61 _public member_ `FName Id;` — `UPROPERTY(BlueprintReadOnly, Category = Material)` — Id for the property.
- L64 _public member_ `FName Name;` — `UPROPERTY(BlueprintReadOnly, Category = Material)` — Readable name for the property.
- L67 _public member_ `EMaterialPropertyCategory Category = EMaterialPropertyCategory::Default;` — `UPROPERTY(BlueprintReadOnly, Category = Material)` — Category for the property.

#### struct `FMaterialDatabaseAssetPropertyValue`  
`struct FMaterialDatabaseAssetPropertyValue`  
_L72-82_
- reflection: `USTRUCT(BlueprintType)`
- desc: Description of a resolved material value in the material asset database.
- L78 _public member_ `FString Value;` — `UPROPERTY(BlueprintReadOnly, Category = Material)` — String value for the property.
- L81 _public member_ `bool bIsModifiedFromParent = false;` — `UPROPERTY(BlueprintReadOnly, Category = Material)` — true if the value for the property is different from the value on its parent material.

#### struct `FMaterialInstancePropertyDiff`  
`struct FMaterialInstancePropertyDiff`  
_L86-102_
- reflection: `USTRUCT(BlueprintType)`
- desc: A single property difference between two versions of a material instance.
- L92 _public member_ `FName PropertyName;` — `UPROPERTY(BlueprintReadOnly, Category = Material)` — Human-readable name of the property.
- L95 _public member_ `EMaterialPropertyCategory Category = EMaterialPropertyCategory::Default;` — `UPROPERTY(BlueprintReadOnly, Category = Material)` — Category for the property.
- L98 _public member_ `FString OldValue;` — `UPROPERTY(BlueprintReadOnly, Category = Material)` — String representation of the value in the old revision. "[Inherited]" if not overridden.
- L101 _public member_ `FString NewValue;` — `UPROPERTY(BlueprintReadOnly, Category = Material)` — String representation of the value in the new revision. "[Inherited]" if not overridden.

#### struct `FMaterialInstanceDiffResult`  
`struct FMaterialInstanceDiffResult`  
_L106-119_
- reflection: `USTRUCT(BlueprintType)`
- desc: Diff result for a single material instance between two versions of a UMaterialValidationGroup.
- L112 _public member_ `FSoftObjectPath InstancePath;` — `UPROPERTY(BlueprintReadOnly, Category = Material)` — Asset path of the material or material instance.
- L115 _public member_ `EMaterialInstanceDiffType DiffType = EMaterialInstanceDiffType::Modified;` — `UPROPERTY(BlueprintReadOnly, Category = Material)` — Whether this instance was added, removed, or modified.
- L118 _public member_ `TArray<FMaterialInstancePropertyDiff> PropertyDiffs;` — `UPROPERTY(BlueprintReadOnly, Category = Material)` — Per-property differences. This will be empty for Added and Removed entries.

### `Plugins/Editor/MaterialValidation/Source/Private/MaterialValidationSimilarityBrowser.h` (Private)


#### class `USimilarityBrowserSettings`  
`class USimilarityBrowserSettings : public UObject`  
_L16-52_
- reflection: `UCLASS(Transient)`
- inherits: `UObject`
- desc: Transient settings object for the similarity browser, exposed to details panel UI.
- L23 _public member_ `TSoftObjectPtr<UMaterial> BaseMaterial;` — `UPROPERTY(EditAnywhere, Category="Selection", meta=(NoResetToDefault))` — Base material whose hierarchy is searched for similar instances.
- L26 _public member_ `TObjectPtr<UMaterialInstanceConstant> CurrentInstance;` — `UPROPERTY(EditAnywhere, Category="Selection", meta=(NoResetToDefault))` — The current material instance being compared against the hierarchy.
- L30 _public member_ `bool bShowUniqueOnly = true;` — `UPROPERTY(EditAnywhere, Category="Filter")` — When true, shows only one row for each unique material permutation and also hides rows which have the same permutation as the current instance.
- L32 _public member_ `bool bUseMaxDistance = false;` — `UPROPERTY(EditAnywhere, Category="Filter", meta=(InlineEditConditionToggle))`
- L35 _public member_ `float MaxDistance = 0.f;` — `UPROPERTY(EditAnywhere, Category="Filter", meta=(ClampMin=0, EditCondition="bUseMaxDistance"))` — Hides similarity rows whose distance exceeds this value.
- L39 _public member_ `float StaticPropertyWeight = 1.f;` — `UPROPERTY(EditAnywhere, Category="Category Weights", meta=(ClampMin=0, ClampMax=10))` — Distance contribution per different static property (BlendMode, TwoSided, etc.).
- L42 _public member_ `float UsageFlagWeight = 1.f;` — `UPROPERTY(EditAnywhere, Category="Category Weights", meta=(ClampMin=0, ClampMax=10))` — Distance contribution per different usage flag.
- L45 _public member_ `float StaticSwitchWeight = 1.f;` — `UPROPERTY(EditAnywhere, Category="Category Weights", meta=(ClampMin=0, ClampMax=10))` — Distance contribution per different static switch value.
- L48 _public member_ `float ComponentMaskWeight = 1.f;` — `UPROPERTY(EditAnywhere, Category="Category Weights", meta=(ClampMin=0, ClampMax=10))` — Distance contribution per different component mask value.
- L51 _public prototype_ `float GetWeightForCategory(EMaterialPropertyCategory Cat) const;` — Returns the distance weight for the given property category.

#### class `SMaterialInstanceSimilarityBrowser`  
`class SMaterialInstanceSimilarityBrowser : public SCompoundWidget`  
_L58-78_
- inherits: `SCompoundWidget`
- desc: Widget that finds existing material instances in a hierarchy that are "close" (fewest different properties) to a live material instance being edited. Intended to help a user discover approved permutations when validation warns that their instance creates a new one.
- L61 _public function_ `SLATE_BEGIN_ARGS(SMaterialInstanceSimilarityBrowser)`
- L62 _public prototype_ `SLATE_ARGUMENT(UMaterialValidationGroup const*, Group) SLATE_ARGUMENT(FSoftObjectPath, BaseMaterialPath) SLATE_ARGUMENT(UMaterialInstanceConstant*, CurrentInstance) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L70 _public prototype_ `static TSharedPtr<SWindow> CreateWindow(UMaterialValidationGroup const* InGroup, FSoftObjectPath const& InBaseMaterialPath, UMaterialInstanceConstant* InCurrentInstance);` — Create and display a standalone similarity browser window.
- L73 _public prototype_ `void NavigateTo(UMaterialValidationGroup const* InGroup, FSoftObjectPath const& InBaseMaterialPath, UMaterialInstanceConstant* InCurrentInstance);` — Update an existing browser to compare a different instance.
- L77 _private member_ `TSharedPtr<class MaterialValidation::SSimilarityBrowserWidget> BrowserWidget;` — Inner widget that owns all state and layout for the browser.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace MaterialValidation`

### `Plugins/Editor/MaterialValidation/Source/Private/MaterialValidationToolkit.h` (Private)


#### class `UAssetDefinition_MaterialValidationGroup`  
`class UAssetDefinition_MaterialValidationGroup : public UAssetDefinitionDefault`  
_L10-20_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- desc: UMaterialValidationGroup asset definition including editor toolkit setup.
- L14 _private prototype_ `virtual FText GetAssetDisplayName() const override;`
- L15 _private prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L16 _private prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L17 _private prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L18 _private prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L19 _private prototype_ `virtual EAssetCommandResult PerformAssetDiff(const FAssetDiffArgs& DiffArgs) const override;`

### `Plugins/Editor/MaterialValidation/Source/Private/MaterialValidationToolkitShared.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace MaterialValidation`
- L12 _externvar_ `extern float GAssetNameColumnWidth;` (scope `MaterialValidation`) — Shared column width for asset-path columns across all tables in the toolkit.
- L14 _externvar_ `extern const FText GEmptyText;` (scope `MaterialValidation`) — Text to use for empty cells.
- L16 _externvar_ `extern const FText GUnknownText;` (scope `MaterialValidation`) — Text to use for unknown values.
- L19 _prototype_ `TSharedRef<SWidget> GenerateAssetPathWidget(FSoftObjectPath InAssetPath, FSlateColor InColor);` (scope `MaterialValidation`) — Creates a path display widget with a browse-to-asset button.
- L21 _prototype_ `FSlateColor GetDeltaColor(int32 InDelta);` (scope `MaterialValidation`) — Get color to use according to whether cost delta is positive, negative or neutral.
- L23 _prototype_ `FText GetTextSignedInt(int32 Value);` (scope `MaterialValidation`) — Return FText that formats the number with a positive/negative sign.

### `Plugins/Editor/MaterialValidation/Source/Private/MaterialValidators.h` (Private)


#### class `UEditorValidator_MaterialPermutation`  
`class UEditorValidator_MaterialPermutation : public UEditorValidatorBase`  
_L16-33_
- reflection: `UCLASS()`
- inherits: `UEditorValidatorBase`
- desc: Implementation of UEditorValidatorBase that applies validation for limiting the addition of material permutations from UMaterials.
- L20 _private prototype_ `virtual bool CanValidateAsset_Implementation(const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext) const override;`
- L21 _private prototype_ `virtual EDataValidationResult ValidateLoadedAsset_Implementation(const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext) override;`
- L22 _private prototype_ `virtual void PostAssetValidation(TArray<TSharedRef<FTokenizedMessage>>& OutMessages) override;`
- L27 _private member_ `TArray<TObjectPtr<UMaterial>> BaseMaterials;` — `UPROPERTY()` — Collected base materials for which to validate the full hierarchy after individual asset validation is complete.
- L30 _private member_ `TArray<TObjectPtr<UMaterialInterface>> ModifiedObjects;` — `UPROPERTY()` — Collected individual assets whose changes should be taken into account when doing full hierarchy validation.
- L32 _private member_ `bool bHasFunctionFiles = false;` — Set when a material function is encountered. We skip the slow validation path because it is more likely to be very slow in this case.

#### class `UMaterialEditorValidator_Permutation`  
`class UMaterialEditorValidator_Permutation : public UMaterialEditorValidatorBase`  
_L37-42_
- reflection: `UCLASS()`
- inherits: `UMaterialEditorValidatorBase`
- desc: Implementation of UMaterialEditorValidatorBase that applies validation for limiting the addition of material permutations.
- L41 _private prototype_ `virtual bool Validate(UMaterialInterface* InMaterial, FMaterialEditorValidatorContext& InContext) const override;`

#### struct `FMaterialValidationHelpers`  
`struct FMaterialValidationHelpers`  
_L45-52_
- desc: Helper functions for external validation callers.
- L48 _public prototype_ `static void FetchRevisionHistory(TArray<UMaterialInterface*> const& InModifiedObjects);` — Fetches source control revision history for the packages backing the given objects.
- L51 _public prototype_ `static void LoadDepotVersions(TArray<UMaterialInterface*> const& InModifiedObjects, TArray<UMaterialInterface*>& OutReplacementObjects, TArray<UPackage*>& OutDepotPackages);` — Loads the depot HEAD revision for each object. OutReplacementObjects is aligned to InModifiedObjects (nullptr where unavailable).

### `Plugins/Editor/MaterialValidation/Source/Public/MaterialValidationModule.h` (Public)


#### class `FMaterialValidationModule`  
`class FMaterialValidationModule : public IModuleInterface`  
_L15-34_
- inherits: `IModuleInterface`
- L17 _private prototype_ `virtual void StartupModule() override;`
- L18 _private prototype_ `virtual void ShutdownModule() override;`
- L26 _public prototype_ `TSharedPtr<SWindow> OpenSimilarityBrowser(UMaterialInterface& MaterialInterface);` — Open (or reuse) the similarity browser window for the given material hierarchy. @param MaterialInterface the material (instance) used for similarity. The parent material will be picked automatically
- L29 _private prototype_ `void OnEditorInitialized(double Duration);`
- L30 _private prototype_ `void OnEditorPreExit();`
- L32 _private member_ `TArray<TWeakObjectPtr<class UMaterialEditorValidatorBase>> MaterialEditorValidators;`
- L33 _private member_ `TArray<TWeakObjectPtr<class UEditorValidatorBase>> EditorValidators;`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMaterialValidation, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMaterialValidation, Log, All);`
