# Plugins / DataprepLibraries

- module root: `Plugins/Enterprise/DataprepEditor/Source/DataprepLibraries`
- headers: 12; symbols: 316
- symbol kinds: class=47, delegate=1, enum=5, enumerator=10, function=47, member=74, namespace=4, prototype=122, struct=6
- PrivateDependencyModuleNames: BlueprintGraph, Core, CoreUObject, DataprepCore, DataprepEditor, DatasmithContent, DerivedDataCache, EditorFramework, EditorScriptingUtilities, Engine, GraphEditor, InputCore, KismetCompiler, LevelSequence, MeshDescription, PhysicsCore, Slate, SlateCore, StaticMeshDescription, StaticMeshEditor, ToolMenus, UnrealEd

### `Plugins/Enterprise/DataprepEditor/Source/DataprepLibraries/Private/DataprepEditingOperations.h` (Private)


#### class `UDataprepDeleteObjectsOperation`  
`class UDataprepDeleteObjectsOperation : public UDataprepEditingOperation`  
_L20-34_
- reflection: `UCLASS(Category = ObjectOperation, Meta = (DisplayName="Delete Objects", ToolTip = "Delete any asset or actor to process"))`
- inherits: `UDataprepEditingOperation`
- L26 _public function_ `virtual FText GetCategory_Implementation() const override`
- L32 _protected prototype_ `virtual void OnExecution_Implementation(const FDataprepContext& InContext) override;`

#### class `UDataprepMergeActorsOperation`  
`class UDataprepMergeActorsOperation : public UDataprepEditingOperation`  
_L37-87_
- reflection: `UCLASS(Category = ObjectOperation, Meta = (DisplayName="Merge", ToolTip = "Collect geometry from selected actors and merge them into single mesh."))`
- inherits: `UDataprepEditingOperation`
- L42 _public function_ `UDataprepMergeActorsOperation() : bDeleteMergedActors_DEPRECATED(true) , bDeleteMergedMeshes_DEPRECATED(true) , bPivotPointAtZero(false) , MergedMesh(nullptr) , MergedActor(nullptr)`
- L53 _public function_ `virtual FText GetCategory_Implementation() const override`
- L60 _public member_ `FString NewActorLabel;` — `UPROPERTY(EditAnywhere, Category = MergeSettings)` — Settings to use for the merge operation
- L64 _public member_ `bool bDeleteMergedActors_DEPRECATED;` — `UPROPERTY()` — Settings to use for the merge operation
- L68 _public member_ `bool bDeleteMergedMeshes_DEPRECATED;` — `UPROPERTY()` — Settings to use for the merge operation
- L71 _public member_ `FMeshMergingSettings MergeSettings_DEPRECATED;` — `UPROPERTY()`
- L75 _public member_ `bool bPivotPointAtZero;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MeshSettings)` — Whether merged mesh should have pivot at world origin, or at first merged component otherwise
- L78 _protected prototype_ `virtual void OnExecution_Implementation(const FDataprepContext& InContext) override;`
- L81 _protected prototype_ `bool MergeStaticMeshActors(UWorld* World, const TArray<UStaticMeshComponent*>& ComponentsToMerge, const FString& RootName, bool bCreateActor = true);`
- L84 _protected member_ `FVector MergedMeshWorldLocation;`
- L85 _protected member_ `UStaticMesh* MergedMesh;`
- L86 _protected member_ `AStaticMeshActor* MergedActor;`

#### class `UDataprepCreateProxyMeshOperation`  
`class UDataprepCreateProxyMeshOperation : public UDataprepEditingOperation`  
_L90-122_
- reflection: `UCLASS(Category = ObjectOperation, Meta = (DisplayName = "Create Proxy Mesh", ToolTip = "Collect geometry from selected actors and merge them into single mesh with reduction."))`
- inherits: `UDataprepEditingOperation`
- L95 _public function_ `UDataprepCreateProxyMeshOperation() : Quality(50.f) , MergedMesh(nullptr) , MergedActor(nullptr)`
- L104 _public function_ `virtual FText GetCategory_Implementation() const override`
- L111 _public member_ `FString NewActorLabel;` — `UPROPERTY(EditAnywhere, Category = ProxySettings)` — Settings to use for the create proxy operation
- L114 _public member_ `float Quality;` — `UPROPERTY(EditAnywhere, Category = ProxySettings, meta = (UIMin = 0, UIMax = 100))`
- L117 _protected prototype_ `virtual void OnExecution_Implementation(const FDataprepContext& InContext) override;`
- L120 _protected member_ `UStaticMesh* MergedMesh;`
- L121 _protected member_ `AStaticMeshActor* MergedActor;`

#### class `UDataprepDeleteUnusedAssetsOperation`  
`class UDataprepDeleteUnusedAssetsOperation : public UDataprepEditingOperation`  
_L125-139_
- reflection: `UCLASS(Category = ObjectOperation, Meta = (DisplayName="Delete Unused Assets", ToolTip = "Delete assets that are not referenced by any objects"))`
- inherits: `UDataprepEditingOperation`
- L131 _public function_ `virtual FText GetCategory_Implementation() const override`
- L137 _protected prototype_ `virtual void OnExecution_Implementation(const FDataprepContext& InContext) override;`

#### class `UDataprepCompactSceneGraphOperation`  
`class UDataprepCompactSceneGraphOperation : public UDataprepEditingOperation`  
_L142-158_
- reflection: `UCLASS(Category = ActorOperation, Meta = (DisplayName="Compact Scene Graph", ToolTip = "Delete actors that do not have visuals, but keep those needed to preserve hierarchy"))`
- inherits: `UDataprepEditingOperation`
- L148 _public function_ `virtual FText GetCategory_Implementation() const override`
- L154 _protected prototype_ `virtual void OnExecution_Implementation(const FDataprepContext& InContext) override;`
- L157 _protected prototype_ `bool IsActorVisible(AActor*, TMap<AActor*, bool>& VisibilityMap);`

#### class `UDataprepSpawnActorsAtLocation`  
`class UDataprepSpawnActorsAtLocation : public UDataprepEditingOperation`  
_L161-180_
- reflection: `UCLASS(Category = ActorOperation, Meta = (DisplayName = "Spawn Actors At Location", ToolTip = "For each actor in the input set, spawn an actor from the specified Asset at the same position and orientation than the reference"))`
- inherits: `UDataprepEditingOperation`
- L167 _public function_ `virtual FText GetCategory_Implementation() const override`
- L172 _public prototype_ `void SetAsset(UObject* Asset);`
- L175 _public member_ `TObjectPtr<UObject> SelectedAsset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ActorOperation)`
- L178 _protected prototype_ `virtual void OnExecution_Implementation(const FDataprepContext& InContext) override;`

#### class `FDataprepSpawnActorsAtLocationDetails`  
`class FDataprepSpawnActorsAtLocationDetails : public IDetailCustomization`  
_L182-210_
- inherits: `IDetailCustomization`
- L185 _public function_ `static TSharedRef< IDetailCustomization > MakeDetails()`
- L190 _public function_ `FDataprepSpawnActorsAtLocationDetails() : DataprepOperation(nullptr)`
- L193 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — Called when details should be customized
- L196 _private prototype_ `const FAssetData& GetAssetData() const;`
- L197 _private prototype_ `TSharedRef<SWidget> CreateWidget();`
- L198 _private prototype_ `TSharedRef<SWidget> GenerateAssetPicker();`
- L199 _private prototype_ `FText OnGetComboTextValue() const;`
- L200 _private prototype_ `FText GetObjectToolTip() const;`
- L201 _private prototype_ `void OnAssetSelectedFromPicker(const struct FAssetData& AssetData);`
- L202 _private prototype_ `void OnAssetEnterPressedInPicker(const TArray<FAssetData>& InSelectedAssets);`
- L205 _private member_ `TSharedPtr<class SMenuAnchor> AssetPickerAnchor;`
- L206 _private member_ `UDataprepSpawnActorsAtLocation* DataprepOperation;`
- L209 _private member_ `mutable FAssetData CachedAssetData;` — Cached AssetData of object selected

### `Plugins/Enterprise/DataprepEditor/Source/DataprepLibraries/Private/DataprepFilterLibrary.h` (Private)


#### enum `EDataprepSizeSource`  
`enum class EDataprepSizeSource : uint8`  
_L12-15_
- reflection: `UENUM()`
- L14 _public enumerator_ `BoundingBoxVolume`

#### enum `EDataprepSizeFilterMode`  
`enum class EDataprepSizeFilterMode : uint8`  
_L18-22_
- reflection: `UENUM()`
- L20 _public enumerator_ `SmallerThan`
- L21 _public enumerator_ `BiggerThan`

#### class `UDataprepFilterLibrary`  
`class UDataprepFilterLibrary : public UBlueprintFunctionLibrary`  
_L25-68_
- reflection: `UCLASS(Blueprintable, BlueprintType, meta = (DisplayName = "Datasmith Data Preparation Filter Library"))`
- inherits: `UBlueprintFunctionLibrary`
- L37 _public prototype_ `static TArray< UObject* > FilterByClass(const TArray< UObject* >& TargetArray, TSubclassOf< UObject > ObjectClass );` — `UFUNCTION(BlueprintPure, Category = "Dataprep | Filter", meta = (DeterminesOutputType = "ObjectClass"))` — Filter the array based on the Object's class. @param	TargetArray		Array of Object to filter. The array will not change. @param	ObjectClass		The Class of the object. @return	The filtered list.
- L47 _public prototype_ `static TArray< UObject* > FilterByName( const TArray< UObject* >& TargetArray, const FString& NameSubString, EEditorScriptingStringMatchType StringMatch = EEditorScriptingStringMatchType::Contains );` — `UFUNCTION(BlueprintPure, Category = "Dataprep | Filter", meta = (DeterminesOutputType = "TargetArray"))` — Filter the array based on the Object name. @param	TargetArray		Array of Object to filter. The array will not change. @param	NameSubString	The name to filter with. @param	StringMatch		Contains the NameSubString OR matches with the wildcard *? OR exactly the same value. @return	The filtered list.
- L58 _public prototype_ `static TArray< UObject* > FilterBySize( const TArray< UObject* >& TargetArray, EDataprepSizeSource SizeSource, EDataprepSizeFilterMode FilterMode, float Threshold);` — `UFUNCTION(BlueprintPure, Category = "Dataprep | Filter", meta = (DeterminesOutputType = "TargetArray"))` — Filter the array based on the geometry size. @param	TargetArray       Array of Actors or StaticMeshes to filter. The array will not change. @param   SizeSource        The reference dimension @param   FilterMode        How to compare the object size with the threshold @param   Threshold         Limit value @return	The filtered list.
- L67 _public prototype_ `static TArray< AActor* > FilterByTag( const TArray< AActor* >& TargetArray, FName Tag );` — `UFUNCTION(BlueprintPure, Category = "Dataprep | Filter", meta = (DeterminesOutputType = "TargetArray"))` — Filter the array based on a tag. @param	TargetArray		Array of Actors to filter. The array will not change. @param	Tag				The tag to filter with. @return	The filtered list.

### `Plugins/Enterprise/DataprepEditor/Source/DataprepLibraries/Private/DataprepOperations.h` (Private)


#### struct `FDataprepSetLODsReductionSettings`  
`struct FDataprepSetLODsReductionSettings`  
_L26-37_
- reflection: `USTRUCT(BlueprintType)`
- desc: Local struct used by UDataprepSetLODsOperation to better control UX
- L32 _public member_ `float PercentTriangles = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetLODsReductionSettings, meta=(UIMin = "0.0", UIMax = "1.0"))` — Percentage of triangles to keep. Ranges from 0.0 to 1.0: 1.0 = no reduction, 0.0 = no triangles.
- L36 _public member_ `float ScreenSize = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SetLODsReductionSettings, meta=(UIMin = "0.0", UIMax = "1.0"))` — ScreenSize to display this LOD. Ranges from 0.0 to 1.0.

#### class `UDataprepSetLODsOperation`  
`class UDataprepSetLODsOperation : public UDataprepOperation`  
_L40-68_
- reflection: `UCLASS(Category = MeshOperation, Meta = (DisplayName="Set LODs", ToolTip = "For each static mesh to process, replace the existing static mesh's LODs with new ones based on the set of reduction settings"))`
- inherits: `UDataprepOperation`
- L44 _private function_ `UDataprepSetLODsOperation() : bAutoComputeLODScreenSize(true)`
- L52 _public member_ `bool bAutoComputeLODScreenSize;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MeshOperation, meta = (DisplayName = "Auto Screen Size", ToolTip = "If true, the screen sizes at which LODs swap are automatically computed"))` — If true, the screen sizes at which LODs swap are computed automatically
- L56 _public member_ `TArray<FDataprepSetLODsReductionSettings> ReductionSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MeshOperation, Meta = (ToolTip = "Array of LOD reduction settings"))` — Array of reduction settings to apply to each new LOD.
- L60 _public function_ `virtual FText GetCategory_Implementation() const override`
- L66 _protected prototype_ `virtual void OnExecution_Implementation(const FDataprepContext& InContext) override;`

#### class `UDataprepSetLODGroupOperation`  
`class UDataprepSetLODGroupOperation : public UDataprepOperation`  
_L71-95_
- reflection: `UCLASS(Category = MeshOperation, Meta = (DisplayName="Set LOD Group", ToolTip = "For each static mesh to process, replace the existing static mesh's LODs with new ones based on selected group"))`
- inherits: `UDataprepOperation`
- L76 _public prototype_ `UDataprepSetLODGroupOperation();`
- L80 _public function_ `virtual FText GetCategory_Implementation() const override`
- L86 _protected prototype_ `virtual void OnExecution_Implementation(const FDataprepContext& InContext) override;`
- L92 _private member_ `FName GroupName;` — `UPROPERTY(EditAnywhere, Category = SetLOGGroup_Internal, meta = (ToolTip = ""))` — Name of the pre-defined LOD group to apply on the selected objects

#### class `UDataprepSetSimpleCollisionOperation`  
`class UDataprepSetSimpleCollisionOperation : public UDataprepOperation`  
_L98-122_
- reflection: `UCLASS(Category = MeshOperation, Meta = (DisplayName="Set Simple Collision", ToolTip = "For each static mesh to process, replace the existing static mesh's collision setup with a simple one based on selected shape"))`
- inherits: `UDataprepOperation`
- L102 _private function_ `UDataprepSetSimpleCollisionOperation() : ShapeType(EScriptCollisionShapeType::Box)`
- L110 _public member_ `EScriptCollisionShapeType ShapeType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MeshOperation, meta = (ToolTip = "Shape's of the collision geometry encompassing the static mesh"))` — Shape's of the collision geometry encompassing the static mesh
- L114 _public function_ `virtual FText GetCategory_Implementation() const override`
- L120 _protected prototype_ `virtual void OnExecution_Implementation(const FDataprepContext& InContext) override;`

#### class `UDataprepSetConvexDecompositionCollisionOperation`  
`class UDataprepSetConvexDecompositionCollisionOperation : public UDataprepOperation`  
_L125-159_
- reflection: `UCLASS(Category = MeshOperation, Meta = (DisplayName="Set Convex Collision", ToolTip = "For each static mesh to process, replace the existing static mesh's collision setup with a convex decomposition one computed using the Hull settings"))`
- inherits: `UDataprepOperation`
- L129 _private function_ `UDataprepSetConvexDecompositionCollisionOperation() : HullCount(4) , MaxHullVerts(16) , HullPrecision(100000)`
- L139 _public member_ `int32 HullCount;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MeshOperation, meta = (ToolTip = "Maximum number of convex pieces that will be created"))` — Maximum number of convex pieces that will be created
- L143 _public member_ `int32 MaxHullVerts;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MeshOperation, meta = (ToolTip = "Maximum number of vertices allowed for any generated convex hulls"))` — Maximum number of vertices allowed for any generated convex hulls
- L147 _public member_ `int32 HullPrecision;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MeshOperation, meta = (ToolTip = "Number of voxels to use when generating collision"))` — Number of voxels to use when generating collision
- L151 _public function_ `virtual FText GetCategory_Implementation() const override`
- L157 _protected prototype_ `virtual void OnExecution_Implementation(const FDataprepContext& InContext) override;`

#### class `UDataprepSetMobilityOperation`  
`class UDataprepSetMobilityOperation : public UDataprepOperation`  
_L162-186_
- reflection: `UCLASS(Category = ActorOperation, Meta = (DisplayName="Set Mobility", ToolTip = "For each actor to process, update its mobilty with the selected value"))`
- inherits: `UDataprepOperation`
- L166 _private function_ `UDataprepSetMobilityOperation() : MobilityType(EComponentMobility::Static)`
- L174 _public member_ `TEnumAsByte<EComponentMobility::Type> MobilityType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ActorOperation, meta = (ToolTip = "Type of mobility to set on actors"))` — Type of mobility to set on mesh actors
- L178 _public function_ `virtual FText GetCategory_Implementation() const override`
- L184 _protected prototype_ `virtual void OnExecution_Implementation(const FDataprepContext& InContext) override;`

#### class `UDataprepSetMaterialOperation`  
`class UDataprepSetMaterialOperation : public UDataprepOperation`  
_L189-213_
- reflection: `UCLASS(Category = MeshOperation, Meta = (DisplayName="Set Material", ToolTip = "On each static mesh or actor to process, replace any materials used with the specified one"))`
- inherits: `UDataprepOperation`
- L193 _private function_ `UDataprepSetMaterialOperation() : Material(nullptr)`
- L201 _public member_ `TObjectPtr<UMaterialInterface> Material;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MeshOperation, meta = (ToolTip = "Material to use as a substitute"))` — Material to use as a substitute
- L205 _public function_ `virtual FText GetCategory_Implementation() const override`
- L211 _protected prototype_ `virtual void OnExecution_Implementation(const FDataprepContext& InContext) override;`

#### class `UDataprepSubstituteMaterialOperation`  
`class UDataprepSubstituteMaterialOperation : public UDataprepOperation`  
_L216-250_
- reflection: `UCLASS(Category = MeshOperation, Meta = (DisplayName="Substitute Material", ToolTip = "On each static mesh or actor to process, replace the material matching the criteria with the specified one"))`
- inherits: `UDataprepOperation`
- L220 _private function_ `UDataprepSubstituteMaterialOperation() : MaterialSearch(TEXT("*")) , StringMatch(EEditorScriptingStringMatchType::MatchesWildcard) , MaterialSubstitute(nullptr)`
- L230 _public member_ `FString MaterialSearch;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MeshOperation, meta = (ToolTip = "Name of the material(s) to search for. Wildcard is supported"))` — Name of the material(s) to search for. Wildcard is supported
- L234 _public member_ `EEditorScriptingStringMatchType StringMatch;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MeshOperation, meta = (ToolTip = "Type of matching to perform with MaterialSearch string"))` — Type of matching to perform with MaterialSearch string
- L238 _public member_ `TObjectPtr<UMaterialInterface> MaterialSubstitute;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MeshOperation, meta = (ToolTip = "Material to use as a substitute"))` — Material to use as a substitute
- L242 _public function_ `virtual FText GetCategory_Implementation() const override`
- L248 _protected prototype_ `virtual void OnExecution_Implementation(const FDataprepContext& InContext) override;`

#### class `UDataprepSubstituteMaterialByTableOperation`  
`class UDataprepSubstituteMaterialByTableOperation : public UDataprepOperation`  
_L253-277_
- reflection: `UCLASS(Category = MeshOperation, Meta = (DisplayName="Substitute Material By Table", ToolTip = "On each static mesh or actor to process, replace the material found in the first column of the table with the one from the second column in the same row"))`
- inherits: `UDataprepOperation`
- L257 _private function_ `UDataprepSubstituteMaterialByTableOperation() : MaterialDataTable(nullptr)`
- L265 _public member_ `TObjectPtr<UDataTable> MaterialDataTable;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MeshOperation, meta = (ToolTip = "Data table to use for the substitution"))` — Data table to use for the substitution
- L269 _public function_ `virtual FText GetCategory_Implementation() const override`
- L275 _protected prototype_ `virtual void OnExecution_Implementation(const FDataprepContext& InContext) override;`

#### class `FDataprepSetLODGroupDetails`  
`class FDataprepSetLODGroupDetails : public IDetailCustomization`  
_L280-302_
- inherits: `IDetailCustomization`
- desc: Customization of the details of the Datasmith Scene for the data prep editor.
- L283 _public function_ `static TSharedRef< IDetailCustomization > MakeDetails()`
- L285 _public function_ `FDataprepSetLODGroupDetails() : DataprepOperation(nullptr)`
- L288 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — Called when details should be customized
- L291 _private prototype_ `TSharedRef< SWidget > CreateWidget();`
- L292 _private prototype_ `void OnLODGroupChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo);`
- L295 _private member_ `UDataprepSetLODGroupOperation* DataprepOperation;`
- L298 _private member_ `TArray< TSharedPtr< FString > > LODGroupOptions;` — LOD group options.
- L299 _private member_ `TArray<FName> LODGroupNames;`
- L301 _private member_ `TSharedPtr<IPropertyHandle> LodGroupPropertyHandle;`

#### class `UDataprepSetMeshOperation`  
`class UDataprepSetMeshOperation : public UDataprepOperation`  
_L305-329_
- reflection: `UCLASS(Category = ActorOperation, Meta = (DisplayName="Set Mesh", ToolTip = "On each actor to process, replace any meshes used with the specified one"))`
- inherits: `UDataprepOperation`
- L309 _private function_ `UDataprepSetMeshOperation() : StaticMesh(nullptr)`
- L317 _public member_ `TObjectPtr<UStaticMesh> StaticMesh;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ActorOperation, meta = (ToolTip = "Mesh to use as a substitute"))` — Mesh to use as a substitute
- L321 _public function_ `virtual FText GetCategory_Implementation() const override`
- L327 _protected prototype_ `virtual void OnExecution_Implementation(const FDataprepContext& InContext) override;`

#### class `UDataprepAddTagsOperation`  
`class UDataprepAddTagsOperation : public UDataprepOperation`  
_L332-351_
- reflection: `UCLASS(Category = ActorOperation, Meta = (DisplayName = "Add Tags", ToolTip = "On each actor to process, add specified tags"))`
- inherits: `UDataprepOperation`
- L339 _public member_ `TArray<FName> Tags;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ActorOperation, Meta = (ToolTip = "Array of tags to add"))` — Array of reduction settings to apply to each new LOD.
- L343 _public function_ `virtual FText GetCategory_Implementation() const override`
- L349 _protected prototype_ `virtual void OnExecution_Implementation(const FDataprepContext& InContext) override;`

#### class `UDataprepSetMetadataOperation`  
`class UDataprepSetMetadataOperation : public UDataprepOperation`  
_L354-373_
- reflection: `UCLASS(Category = ActorOperation, Meta = (DisplayName = "Set Metadata", ToolTip = "On each actor to process set metadata value"))`
- inherits: `UDataprepOperation`
- L361 _private member_ `TMap<FName, FString> Metadata;` — `UPROPERTY(EditAnywhere, Category = ActorOperation, Meta = (ToolTip = "Array of metadata values"))` — Table of metadata keys/values.
- L365 _public function_ `virtual FText GetCategory_Implementation() const override`
- L371 _protected prototype_ `virtual void OnExecution_Implementation(const FDataprepContext& InContext) override;`

#### class `UDataprepConsolidateObjectsOperation`  
`class UDataprepConsolidateObjectsOperation : public UDataprepOperation`  
_L376-392_
- reflection: `UCLASS(Category = AssetOperation, Meta = (DisplayName = "Replace Asset References", ToolTip = "Replace references to each asset with the first asset in the list"))`
- inherits: `UDataprepOperation`
- L384 _public function_ `virtual FText GetCategory_Implementation() const override`
- L390 _protected prototype_ `virtual void OnExecution_Implementation(const FDataprepContext& InContext) override;`

#### class `UDataprepRandomizeTransformOperation`  
`class UDataprepRandomizeTransformOperation : public UDataprepOperation`  
_L395-430_
- reflection: `UCLASS(Category = ActorOperation, Meta = (DisplayName = "Random Offset Transform", ToolTip = "For each actor in the input set, offset its position/rotation/scale with random vector generated from X/Y/Z Min-Max."))`
- inherits: `UDataprepOperation`
- L399 _private function_ `UDataprepRandomizeTransformOperation() : TransformType(ERandomizeTransformType::Location) , ReferenceFrame(ERandomizeTransformReferenceFrame::Relative)`
- L407 _public function_ `virtual FText GetCategory_Implementation() const override`
- L413 _public member_ `ERandomizeTransformType TransformType;` — `UPROPERTY(EditAnywhere, Category = ActorOperation, Meta = (ToolTip = "Transform component to randomize"))`
- L416 _public member_ `ERandomizeTransformReferenceFrame ReferenceFrame;` — `UPROPERTY(EditAnywhere, Category = ActorOperation, Meta = (ToolTip = "Reference frame to use (relative/world)"))`
- L419 _public member_ `FVector Min;` — `UPROPERTY(EditAnywhere, Category = ActorOperation, Meta = (ToolTip = "Min random value"))`
- L422 _public member_ `FVector Max;` — `UPROPERTY(EditAnywhere, Category = ActorOperation, Meta = (ToolTip = "Max random value"))`
- L425 _protected prototype_ `virtual void OnExecution_Implementation(const FDataprepContext& InContext) override;`
- L429 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — Track Min/Max changes and force values to be meaningful: Min<=Max

#### class `UDataprepFlipFacesOperation`  
`class UDataprepFlipFacesOperation : public UDataprepOperation`  
_L433-449_
- reflection: `UCLASS(Category = ActorOperation, Meta = (DisplayName = "Flip Faces", ToolTip = "On each actor to process, flip faces of each mesh"))`
- inherits: `UDataprepOperation`
- L441 _public function_ `virtual FText GetCategory_Implementation() const override`
- L447 _protected prototype_ `virtual void OnExecution_Implementation(const FDataprepContext& InContext) override;`

#### class `UDataprepSetOutputFolder`  
`class UDataprepSetOutputFolder : public UDataprepOperation`  
_L452-476_
- reflection: `UCLASS(Category = AssetOperation, Meta = (DisplayName="Output to Folder", ToolTip = "For each asset to process, set the sub-folder to save it to.\nThe sub-folder is relative to the folder specified to the Dataprep consumer."))`
- inherits: `UDataprepOperation`
- L456 _private function_ `UDataprepSetOutputFolder() : FolderName(TEXT("MySubFolder"))`
- L464 _public member_ `FString FolderName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AssetOperation, meta = (DisplayName = "Folder Name", ToolTip = "Name of the sub folder the assets to be saved to"))` — If true, the screen sizes at which LODs swap are computed automatically
- L468 _public function_ `virtual FText GetCategory_Implementation() const override`
- L474 _protected prototype_ `virtual void OnExecution_Implementation(const FDataprepContext& InContext) override;`

#### class `FDataprepSetOutputFolderDetails`  
`class FDataprepSetOutputFolderDetails : public IDetailCustomization`  
_L478-498_
- inherits: `IDetailCustomization`
- desc: Customization of the details of the "Output to Folder" operation.
- L481 _public function_ `static TSharedRef< IDetailCustomization > MakeDetails()`
- L484 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — Called when details should be customized
- L487 _private prototype_ `void FolderName_TextChanged(const FText& Text);`
- L488 _private prototype_ `void FolderName_TextCommited(const FText& InText, ETextCommit::Type InCommitType);`
- L491 _private member_ `UDataprepSetOutputFolder* Operation = nullptr;`
- L493 _private member_ `TSharedPtr<IPropertyHandle> FolderNamePropertyHandle;`
- L495 _private member_ `bool bValidFolderName = true;`
- L497 _private member_ `TSharedPtr< class SEditableTextBox > TextBox;`

#### class `UDataprepAddToLayerOperation`  
`class UDataprepAddToLayerOperation : public UDataprepOperation`  
_L501-520_
- reflection: `UCLASS(Category = ActorOperation, Meta = (DisplayName = "Add To Layer", ToolTip = "On each actor to process, add the actor to the layer"))`
- inherits: `UDataprepOperation`
- L508 _public member_ `FName LayerName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ActorOperation, Meta = (ToolTip = "Name of the layer to add the actors to"))` — Name of the layer to add the actors to.
- L512 _public function_ `virtual FText GetCategory_Implementation() const override`
- L518 _protected prototype_ `virtual void OnExecution_Implementation(const FDataprepContext& InContext) override;`

#### class `UDataprepSetCollisionComplexityOperation`  
`class UDataprepSetCollisionComplexityOperation : public UDataprepOperation`  
_L523-546_
- reflection: `UCLASS(Category = MeshOperation, Meta = (DisplayName="Set Collision Complexity", ToolTip = "For each static mesh to process, set its collision complexity"))`
- inherits: `UDataprepOperation`
- L527 _private function_ `UDataprepSetCollisionComplexityOperation() : CollisionTraceFlag(ECollisionTraceFlag::CTF_UseDefault)`
- L534 _public member_ `TEnumAsByte<ECollisionTraceFlag> CollisionTraceFlag;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MeshOperation, meta = (ToolTip = "Collision complexity"))`
- L538 _public function_ `virtual FText GetCategory_Implementation() const override`
- L544 _protected prototype_ `virtual void OnExecution_Implementation(const FDataprepContext& InContext) override;`

#### class `UDataprepSetMaxTextureSizeOperation`  
`class UDataprepSetMaxTextureSizeOperation : public UDataprepOperation`  
_L549-573_
- reflection: `UCLASS(Category = AssetOperation, Meta = (DisplayName = "Set Max Texture Size", ToolTip = "Set max size (width or height) each input texture"))`
- inherits: `UDataprepOperation`
- L555 _public member_ `int32 MaxTextureSize;` — `UPROPERTY(EditAnywhere, Category = AssetOperation, BlueprintReadWrite, meta = (UIMin = "1", ClampMin = "1"), Meta = (ToolTip = ""))`
- L558 _public member_ `bool bAllowPadding = false;` — `UPROPERTY(EditAnywhere, Category = AssetOperation, BlueprintReadWrite, meta = (ToolTip = "If true, original texture size will be enforced to power of two before resizing (if it's a non-power of two size), else only POT textures will be affected."))`
- L562 _public function_ `virtual FText GetCategory_Implementation() const override`
- L568 _protected prototype_ `virtual void OnExecution_Implementation(const FDataprepContext& InContext) override;`
- L572 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — Track changes of MaxTextureSize and force values to be power of two

#### class `UDataprepSetNaniteSettingsOperation`  
`class UDataprepSetNaniteSettingsOperation : public UDataprepOperation`  
_L576-604_
- reflection: `UCLASS(Category = MeshOperation, Meta = (DisplayName = "Set Nanite Settings", ToolTip = "For each static mesh to process, enables/disables Nanite build and if enabled update settings."))`
- inherits: `UDataprepOperation`
- L583 _public member_ `bool bNaniteEnabled = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MeshOperation, meta = (ToolTip = "If checked, Nanite data will be generated"))` — If true, Nanite data will be generated
- L588 _public member_ `int32 PositionPrecision = MIN_int32;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MeshOperation_Internal, meta = (/*EditConditionHides, EditCondition = "bNaniteEnabled",*/ ToolTip = "Step size is 2^(-PositionPrecision) cm. MIN_int32 is auto"))` — #ueent_todo: Same display as static mesh editor. See FNaniteSettingsLayout in StaticMeshEditorTool.h
- L592 _public member_ `float PercentTriangles = 100.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MeshOperation, meta = (/*EditConditionHides, EditCondition = "bNaniteEnabled",*/ ClampMin = 0, ClampMax = 100, UIMin = "0.0", UIMax = "100.0", ToolTip = "Percentage of triangles to keep from LOD0. 100.0 = no reduction, 0.0 = no triangles"))` — Percentage of triangles to keep from LOD0. 100.0 = no reduction, 0.0 = no triangles.
- L596 _public function_ `virtual FText GetCategory_Implementation() const override`
- L602 _protected prototype_ `virtual void OnExecution_Implementation(const FDataprepContext& InContext) override;`

#### class `FDataprepSetNaniteSettingsDetails`  
`class FDataprepSetNaniteSettingsDetails : public IDetailCustomization`  
_L607-625_
- inherits: `IDetailCustomization`
- desc: Customization of the details of the DataprepSetNaniteSettingsOperation for the Dataprep editor.
- L610 _public function_ `static TSharedRef< IDetailCustomization > MakeDetails()`
- L612 _public function_ `FDataprepSetNaniteSettingsDetails() : DataprepOperation(nullptr)`
- L615 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — Called when details should be customized
- L618 _private prototype_ `TSharedRef< SWidget > CreateWidget();`
- L619 _private prototype_ `void OnPositionPrecisionChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo);`
- L622 _private member_ `UDataprepSetNaniteSettingsOperation* DataprepOperation;`
- L624 _private member_ `TSharedPtr<IPropertyHandle> PositionPrecisionPropertyHandle;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace ESelectInfo`
- L21 _namespace_ `namespace ETextCommit`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepLibraries/Private/DataprepOperationsLibrary.h` (Private)


#### struct `FMaterialSubstitutionDataTable`  
`struct FMaterialSubstitutionDataTable : public FTableRowBase`  
_L29-44_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FTableRowBase`
- desc: Simple struct for the table row used for UDataprepOperationsLibrary::SubstituteMaterials
- L35 _public member_ `FString SearchString;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MaterialSubstitutionTable")` — Name of the material(s) to search for. Wildcard is supported
- L39 _public member_ `EEditorScriptingStringMatchType StringMatch = EEditorScriptingStringMatchType::Contains;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MaterialSubstitutionTable")` — Type of matching to perform with SearchString string
- L43 _public member_ `TObjectPtr<UMaterialInterface> MaterialReplacement = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MaterialSubstitutionTable")` — Material to use for the substitution

#### struct `FMeshSubstitutionDataTable`  
`struct FMeshSubstitutionDataTable`  
_L50-65_
- reflection: `USTRUCT(meta=(Deprecated = "4.25.0"))`
- desc: DEPRECATED - Simple struct for the table row used for UDataprepOperationsLibrary::SubstituteMaterials
- L56 _public member_ `FString SearchString_DEPRECATED;` — `UPROPERTY()` — DEPRECATED - Name of the mesh(es) to search for. Wildcard is supported
- L60 _public member_ `EEditorScriptingStringMatchType StringMatch_DEPRECATED = EEditorScriptingStringMatchType::Contains;` — `UPROPERTY()` — DEPRECATED - Type of matching to perform with SearchString string
- L64 _public member_ `TObjectPtr<UStaticMesh> MeshReplacement_DEPRECATED = nullptr;` — `UPROPERTY()` — DEPRECATED - Mesh to use for the substitution

#### struct `FLODGroupName`  
`struct FLODGroupName`  
_L73-80_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- desc: Simple struct to set up LODGroup name on static meshes This is for internal purpose only to allow users to select the name of the LODGroup to apply on static meshes in UDataprepOperationsLibrary::SetLODGroup
- L79 _public member_ `FString Value;` — `UPROPERTY()` — Value of the name of LODGroup not the display name

#### struct `FMeshReductionOptions`  
`struct FMeshReductionOptions`  
_L88-99_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- desc: Simple struct to set up LODGroup name on static meshes This is for internal purpose only to allow users to select the name of the LODGroup to apply on static meshes in UDataprepOperationsLibrary::SetLODGroup
- L94 _public member_ `float ReductionPercent = 0.0f;` — `UPROPERTY()` — Value of the name of LODGroup not the display name
- L98 _public member_ `float ScreenSize= 0.0f;` — `UPROPERTY()` — Value of the name of LODGroup not the display name

#### struct `FMeshReductionArray`  
`struct FMeshReductionArray`  
_L107-114_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- desc: Simple struct to set up LODGroup name on static meshes This is for internal purpose only to allow users to select the name of the LODGroup to apply on static meshes in UDataprepOperationsLibrary::SetLODGroup
- L113 _public member_ `TArray<FMeshReductionOptions> Array;` — `UPROPERTY()` — Value of the name of LODGroup not the display name

#### enum `ERandomizeTransformType`  
`enum class ERandomizeTransformType : uint8`  
_L117-122_
- reflection: `UENUM(BlueprintInternalUseOnly)`
- L119 _public enumerator_ `Rotation`
- L120 _public enumerator_ `Location`
- L121 _public enumerator_ `Scale`

#### enum `ERandomizeTransformReferenceFrame`  
`enum class ERandomizeTransformReferenceFrame : uint8`  
_L125-129_
- reflection: `UENUM(BlueprintInternalUseOnly)`
- L127 _public enumerator_ `World`
- L128 _public enumerator_ `Relative`

#### class `UDataprepOperationsLibrary`  
`class UDataprepOperationsLibrary : public UBlueprintFunctionLibrary`  
_L132-357_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L150 _public prototype_ `static void SetLods(const TArray<UObject*>& SelectedObjects, const FStaticMeshReductionOptions& ReductionOptions, TArray<UObject*>& ModifiedObjects);` — `UFUNCTION(BlueprintCallable, Category = "Dataprep | Operation")` — Generate LODs on the static meshes contained in the input array by the actors contained in the input array @param	SelectedObjects			Array of UObjects to process. @param	ReductionOptions		Options on how to generate LODs on the mesh. @remark: Static meshes are not re-built after the new LODs are set Generates an array of unique static meshes from the input array either by a cast if the UObject is a UStaticMesh or collecting the static meshes referred to if the UObject is a AActor Calls UEditorStaticMeshLibrary::SetLods on each static mesh of the resulting array.
- L166 _public prototype_ `static void SetSimpleCollision(const TArray<UObject*>& SelectedObjects, const EScriptCollisionShapeType ShapeType, TArray<UObject*>& ModifiedObjects);` — `UFUNCTION(BlueprintCallable, Category = "Dataprep | Operation")` — Set one simple collision of the given shape type on the static meshes contained in the input array or referred to by the actors contained in the input array @param	SelectedActors			Array of actors to process. @param	ShapeType				Options on which simple collision to add to the mesh. @remark: Static meshes are not re-built after the new collision settings are set Generates an array of unique static meshes from the input array either by a cast if the UObject is a UStaticMesh or collecting the static meshes referred to if the UObject is a AActor Calls UEditorStaticMeshLibrary::RemoveCollisions to remove any existing collisions on each static mesh of the resulting array Calls UEditorStaticMeshLibrary::AddSimpleCollisions on each static mesh of the resulting array.
- L183 _public prototype_ `static void SetConvexDecompositionCollision(const TArray<UObject*>& SelectedObjects, int32 HullCount, int32 MaxHullVerts, int32 HullPrecision, TArray<UObject*>& ModifiedObjects);` — `UFUNCTION(BlueprintCallable, Category = "Dataprep | Operation")` — Add complex collision on the static meshes contained in the input array by the actors contained in the input array @param	SelectedActors			Array of actors to process. @param	HullCount				Maximum number of convex pieces that will be created. Must be positive. @param	MaxHullVerts			Maximum number of vertices allowed for any generated convex hull. @param	HullPrecision			Number of voxels to use when generating collision. Must be positive. @remark: Static meshes are not re-built after the new collision settings are set Generates an array of unique static meshes from the input array either by a cast if the UObject is a UStaticMesh or collecting the static meshes referred to if the UObject is a AActor Calls UEditorStaticMeshLibrary::SetConvexDecompositionCollisions on each static mesh of the resulting array. Note that any simple collisions on each static mesh of the resulting array will be removed.
- L195 _public prototype_ `static void SubstituteMaterial(const TArray<UObject*>& SelectedObjects, const FString& MaterialSearch, EEditorScriptingStringMatchType StringMatch, UMaterialInterface* MaterialSubstitute);` — `UFUNCTION(BlueprintCallable, Category = "Dataprep | Operation")` — Replaces designated materials in all or specific content folders with specific ones @param SelectedObjects: Objects to consider for the substitution @param MaterialSearch: Name of the material(s) to search for. Wildcard is supported @param StringMatch: Type of matching to perform with MaterialSearch string @param MaterialSubstitute: Material to use for the substitution @remark: A material override will be added to static mesh components if their attached static mesh uses the searched material but not themselves
- L204 _public prototype_ `static void SubstituteMaterialsByTable(const TArray<UObject*>& SelectedObjects, const UDataTable* DataTable);` — `UFUNCTION(BlueprintCallable, Category = "Dataprep | Operation")` — Replaces designated materials in all or specific content folders with requested ones @param SelectedObjects: Objects to consider for the substitution @param DataTable: Data table to use for the substitution @remark: SubstituteMaterial is called for each entry of the input data table
- L212 _public prototype_ `static void SetLODGroup( const TArray< UObject* >& SelectedObjects, FName& LODGroupName, TArray<UObject*>& ModifiedObjects );` — `UFUNCTION(BlueprintCallable, Category = "Dataprep | Operation")` — Remove inputs content @param Objects Objects to remove @remark: Static meshes are not re-built after the new LOD groups are set
- L220 _public prototype_ `static void SetMaterial( const TArray< UObject* >& SelectedObjects, UMaterialInterface* MaterialSubstitute );` — `UFUNCTION(BlueprintCallable, Category = "Dataprep | Operation")` — Set the material to all elements of a set of Static Meshes or Static Mesh Actors @param SelectedObjects	Objects to set the input material on @param MaterialInterface Material to use
- L229 _public prototype_ `static void SetMobility( const TArray< UObject* >& SelectedObjects, EComponentMobility::Type MobilityType );` — `UFUNCTION(BlueprintCallable, Category = "Dataprep | Operation")` — Set mobility on a set of static mesh actors @param SelectedObjects Objects to set mobility on @param MobilityType Type of mobility to set on selected mesh actors @remark: Only objects of class AStaticMeshActor will be considered
- L237 _public prototype_ `static void SetMesh( const TArray< UObject* >& SelectedObjects, UStaticMesh* MeshSubstitute );` — `UFUNCTION(BlueprintCallable, Category = "Dataprep | Operation")` — Set the mesh to all elements of a set of Actors containing StaticMeshComponents @param SelectedObjects	Objects to set the input mesh on @param MeshSubstitute	Mesh to use
- L247 _public prototype_ `static void SubstituteMesh(const TArray<UObject*>& SelectedObjects, const FString& MeshSearch, EEditorScriptingStringMatchType StringMatch, UStaticMesh* MeshSubstitute);` — `UFUNCTION(BlueprintCallable, Category = "Dataprep | Operation")` — Replaces designated meshes in all or specific content folders with specific ones @param SelectedObjects:	Objects to consider for the substitution @param MeshSearch:		Name of the mesh(es) to search for. Wildcard is supported @param StringMatch:		Type of matching to perform with MeshSearch string @param MeshSubstitute:	Mesh to use for the substitution
- L256 _public prototype_ `static void SubstituteMeshesByTable(const TArray<UObject*>& SelectedObjects, const UDataTable* DataTable);` — `UFUNCTION(meta=(Deprecated = "4.25.0"))` — Replaces designated meshes in all or specific content folders with requested ones @param SelectedObjects:	Objects to consider for the substitution @param DataTable:		Data table to use for the substitution @remark: SubstituteMesh is called for each entry of the input data table
- L264 _public prototype_ `static void AddTags( const TArray< UObject* >& SelectedObjects, const TArray<FName>& InTags );` — `UFUNCTION(BlueprintCallable, Category = "Dataprep | Operation")` — Add tags to a set of actors @param SelectedObjects	Objects to add the tags to @param Tags				Array of tags to add
- L272 _public prototype_ `static void AddMetadata(const TArray<UObject*>& SelectedObjects, const TMap<FName, FString>& InMetadata);` — `UFUNCTION(BlueprintCallable, Category = "Dataprep | Operation")` — Adds metadata to selected objects that implement the UInterface_AssetUserData interface. @param SelectedObjects:	Objects to consider @param InMetadata:		The metadata to append
- L279 _public prototype_ `static void ConsolidateObjects( const TArray< UObject* >& SelectedObjects );` — `UFUNCTION(BlueprintCallable, Category = "Dataprep | Operation")` — Replace all references to the assets in the array, except the first, with the first asset of the array. @param SelectedObjects	Objects to consolidate
- L289 _public prototype_ `static void RandomizeTransform(const TArray<UObject*>& SelectedObjects, ERandomizeTransformType TransformType, ERandomizeTransformReferenceFrame ReferenceFrame, const FVector& Min, const FVector& Max);` — `UFUNCTION(BlueprintCallable, Category = "Dataprep | Operation")` — Alters transform of selected objects by appling randomly generated offset to one of the transform components (rotation, scale or translation) @param SelectedObjects:	Objects to consider @param TransformType:	Selected transform component to randomize @param Min:				Start of randomization range @param Max:				End of randomization range
- L296 _public prototype_ `static void FlipFaces( const TSet< UStaticMesh* >& StaticMeshes );` — `UFUNCTION(BlueprintCallable, Category = "Dataprep | Operation")` — Flip the faces of all elements of a set of Static Meshes or Static Mesh Actors @param SelectedObjects	Objects to the flip the faces of
- L305 _public prototype_ `static void SetSubOuputLevel(const TArray<UObject*>& SelectedObjects, const FString& SubLevelName);` — `UFUNCTION(BlueprintCallable, Category = "Dataprep | Operation")` — Add/Edit UDataprepConsumerUserData with the requested name for the sub-level @param SelectedObjects:	Objects to consider @param SubLevelName:	Name of the sub-level @note - This operation only applies on actors
- L314 _public prototype_ `static void SetSubOuputFolder(const TArray<UObject*>& SelectedObjects, const FString& SubFolderName);` — `UFUNCTION(BlueprintCallable, Category = "Dataprep | Operation")` — Add/Edit UDataprepConsumerUserData with the requested name for the sub-folder @param SelectedObjects:	Objects to consider @param SubFolderName:	Name of the sub-folder @note - This operation only applies on assets
- L323 _public prototype_ `static void AddToLayer(const TArray<UObject*>& SelectedObjects, const FName& LayerName);` — `UFUNCTION(BlueprintCallable, Category = "Dataprep | Operation")` — Add all Actors to a given layer. @param SelectedObjects:	Objects to consider @param LayerName:	Name of the sub-folder @note - This operation only applies on assets
- L332 _public prototype_ `static void SetCollisionComplexity(const TArray<UObject*>& InSelectedObjects, const ECollisionTraceFlag InCollisionTraceFlag, TArray<UObject*>& InModifiedObjects);` — `UFUNCTION(BlueprintCallable, Category = "Dataprep | Operation")` — Set collision complexity for selected meshes @param	InSelectedObjects			Array of meshes to process. @param	InCollisionTraceFlag		The new collision complexity. @param	InModifiedObjects			List of modified meshes.
- L341 _public prototype_ `static void ResizeTextures(const TArray<UTexture2D*>& InTextures, int32 InMaxSize);` — `UFUNCTION(BlueprintCallable, Category = "Dataprep | Operation")` — Resize textures to max width/height and optionally ensure power of two size. @param InTextures:	Textures to resize @param InMaxSize:	Max allowed width or height @note - This operation only applies on assets
- L352 _public prototype_ `static void SetNaniteSettings(const TArray<UObject*>& InSelectedObjects, bool bInEnabled, int32 InPositionPrecision, float InPercentTriangles, TArray<UObject*>& OutModifiedObjects);` — `UFUNCTION(BlueprintCallable, Category = "Dataprep | Operation")` — Set Nanite settings for selected meshes @param	InSelectedObjects			Array of objects to process. @param	bInEnabled					If true, Nanite data will be generated. @param	InPositionPrecision			Step size is 2^(-PositionPrecision) cm. MIN_int32 is auto. @param	InPercentTriangles			Percentage of triangles to keep from LOD0. 1.0 = no reduction, 0.0 = no triangles. @param	OutModifiedObjects			List of modified objects the processed meshes will be added to
- L355 _private prototype_ `static void SubstituteMaterial(const TArray<UObject*>& SelectedObjects, const FString& MaterialSearch, EEditorScriptingStringMatchType StringMatch, const TArray<UMaterialInterface*>& MaterialList, UMaterialInterface* MaterialSubstitute);`
- L356 _private prototype_ `static void SubstituteMesh(const TArray<UObject*>& SelectedObjects, const FString& MeshSearch, EEditorScriptingStringMatchType StringMatch, const TArray<UStaticMesh*>& MeshList, UStaticMesh* MeshSubstitute);`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace EComponentMobility`
- L23 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN( LogDataprep, Log, All );`
- L23 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN( LogDataprep, Log, All );`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepLibraries/Private/DataprepSelectionTransforms.h` (Private)


#### enum `EDataprepHierarchySelectionPolicy`  
`enum class EDataprepHierarchySelectionPolicy : uint8`  
_L11-18_
- reflection: `UENUM()`
- L14 _public enumerator_ `ImmediateChildren` — Select immediate children of the selected objects
- L17 _public enumerator_ `AllDescendants` — Select all descendants of the selected objects

#### class `UDataprepReferenceSelectionTransform`  
`class UDataprepReferenceSelectionTransform : public UDataprepSelectionTransform`  
_L21-34_
- reflection: `UCLASS(Category = SelectionTransform, Meta = (DisplayName="Select Referenced", ToolTip = "Return assets directly used/referenced by the selected objects."))`
- inherits: `UDataprepSelectionTransform`
- L25 _private function_ `UDataprepReferenceSelectionTransform() : bAllowIndirectReferences(false)`
- L30 _protected prototype_ `virtual void OnExecution_Implementation(const TArray<UObject*>& InObjects, TArray<UObject*>& OutObjects) override;`
- L33 _protected member_ `bool bAllowIndirectReferences;` — `UPROPERTY(EditAnywhere, Category = "HierarchySelectionOptions", meta = (ToolTip = "Include assets referenced/used by assets directly referenced/used by selected objects"))`

#### class `UDataprepReferencedSelectionTransform`  
`class UDataprepReferencedSelectionTransform : public UDataprepSelectionTransform`  
_L37-43_
- reflection: `UCLASS(Category = SelectionTransform, Meta = (DisplayName = "Select Referencers", ToolTip = "Return assets directly using/referencing the objects from previous filtering"))`
- inherits: `UDataprepSelectionTransform`
- L42 _protected prototype_ `virtual void OnExecution_Implementation(const TArray<UObject*>& InObjects, TArray<UObject*>& OutObjects) override;`

#### class `UDataprepHierarchySelectionTransform`  
`class UDataprepHierarchySelectionTransform : public UDataprepSelectionTransform`  
_L46-59_
- reflection: `UCLASS(Category = SelectionTransform, Meta = (DisplayName="Select Hierarchy", ToolTip = "Return immediate children or all the descendants of the selected objects"))`
- inherits: `UDataprepSelectionTransform`
- L50 _private function_ `UDataprepHierarchySelectionTransform() : SelectionPolicy(EDataprepHierarchySelectionPolicy::ImmediateChildren)`
- L55 _protected prototype_ `virtual void OnExecution_Implementation(const TArray<UObject*>& InObjects, TArray<UObject*>& OutObjects) override;`
- L58 _protected member_ `EDataprepHierarchySelectionPolicy SelectionPolicy;` — `UPROPERTY(EditAnywhere, Category = "HierarchySelectionOptions", meta = (DisplayName = "Select", ToolTip = "Specify policy of hierarchical parsing of selected objects"))`

#### class `UDataprepActorComponentsSelectionTransform`  
`class UDataprepActorComponentsSelectionTransform : public UDataprepSelectionTransform`  
_L62-68_
- reflection: `UCLASS(Category = SelectionTransform, Meta = (DisplayName="Select Actor Components", ToolTip = "Return components of the selected actors"))`
- inherits: `UDataprepSelectionTransform`
- L67 _protected prototype_ `virtual void OnExecution_Implementation(const TArray<UObject*>& InObjects, TArray<UObject*>& OutObjects) override;`

#### class `UDataprepOwningActorSelectionTransform`  
`class UDataprepOwningActorSelectionTransform : public UDataprepSelectionTransform`  
_L71-77_
- reflection: `UCLASS(Category = SelectionTransform, Meta = (DisplayName="Select Owning Actor", ToolTip = "Return the owning actors of selected components"))`
- inherits: `UDataprepSelectionTransform`
- L76 _protected prototype_ `virtual void OnExecution_Implementation(const TArray<UObject*>& InObjects, TArray<UObject*>& OutObjects) override;`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepLibraries/Public/DataprepLibrariesModule.h` (Public)


#### class `IDataprepLibrariesModule`  
`class IDataprepLibrariesModule : public IModuleInterface`  
_L8-11_
- inherits: `IModuleInterface`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepLibraries/Public/DataprepOperationsLibraryUtil.h` (Public)


#### class `DataprepOperationsLibraryUtil::FStaticMeshBuilder`  
`class FStaticMeshBuilder`  
_L13-20_
- L16 _public prototype_ `FStaticMeshBuilder(const TSet<UStaticMesh*>& InStaticMeshes);`
- L17 _public prototype_ `~FStaticMeshBuilder();`
- L19 _private member_ `TArray<UStaticMesh*> StaticMeshes;`

#### class `DataprepOperationsLibraryUtil::FScopedStaticMeshEdit`  
`class FScopedStaticMeshEdit final`  
_L22-43_
- L25 _public prototype_ `FScopedStaticMeshEdit( UStaticMesh* InStaticMesh );`
- L27 _public prototype_ `FScopedStaticMeshEdit( const FScopedStaticMeshEdit& Other ) = default;`
- L28 _public prototype_ `FScopedStaticMeshEdit( FScopedStaticMeshEdit&& Other ) = default;`
- L30 _public prototype_ `FScopedStaticMeshEdit& operator=( const FScopedStaticMeshEdit& Other ) = default;`
- L31 _public prototype_ `FScopedStaticMeshEdit& operator=( FScopedStaticMeshEdit&& Other ) = default;`
- L33 _public prototype_ `~FScopedStaticMeshEdit();`
- L36 _public prototype_ `static TArray< FMeshBuildSettings > PreventStaticMeshBuild( UStaticMesh* StaticMesh );`
- L38 _public prototype_ `static void RestoreStaticMeshBuild( UStaticMesh* StaticMesh, const TArray< FMeshBuildSettings >& BuildSettingsBackup );`
- L41 _private member_ `TArray< FMeshBuildSettings > BuildSettingsBackup;`
- L42 _private member_ `UStaticMesh* StaticMesh;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace DataprepOperationsLibraryUtil`
- L51 _prototype_ `TArray<UStaticMesh*> BuildStaticMeshes( const TSet<UStaticMesh*>& StaticMeshes, bool bForceBuild = false );` (scope `DataprepOperationsLibraryUtil`) — Builds render data of a set of static meshes. @param StaticMeshes	Set of static meshes to build if render data is missing or a forced build is required @param bForceBuild	Indicates if all static meshes should be built or only the incomplete ones @returns the array of static meshes which have actually been built
- L58 _prototype_ `TSet<UStaticMesh*> GetSelectedMeshes(const TArray<UObject*>& SelectedObjects);` (scope `DataprepOperationsLibraryUtil`) — Find the set of static meshes in or referenced by a given array of objects. @param SelectedObjects	Array of UObjects to go through @returns a set of static meshes
- L65 _prototype_ `TArray<UMaterialInterface*> GetUsedMaterials(const TArray<UObject*>& SelectedObjects);` (scope `DataprepOperationsLibraryUtil`) — Find the materials used by a set of objects. @param SelectedObjects	Array of UObjects to go through @returns array of materials
- L72 _prototype_ `TArray<UStaticMesh*> GetUsedMeshes(const TArray<UObject*>& SelectedObjects);` (scope `DataprepOperationsLibraryUtil`) — Find the meshes referenced by a set of actors. @param SelectedObjects	Array of UObjects to go through @returns array of static meshes used by the actors. Meshes in the result array are unique
- L77 _prototype_ `void SetMaterial(UStaticMesh* StaticMesh, int32 MaterialIndex, UMaterialInterface* NewMaterial);` (scope `DataprepOperationsLibraryUtil`) — Customized version of UStaticMesh::SetMaterial avoiding the triggering of UStaticMesh::Build and its side-effects

### `Plugins/Enterprise/DataprepEditor/Source/DataprepLibraries/Public/Fetchers/DataprepBoolFetcherLibrary.h` (Public)


#### class `UDataprepIsClassOfFetcher`  
`class UDataprepIsClassOfFetcher final : public UDataprepBoolFetcher`  
_L14-36_
- reflection: `UCLASS(BlueprintType, NotBlueprintable, Meta = (DisplayName="Is Class Of", ToolTip = "Filter objects based of their selected class."))`
- inherits: `UDataprepBoolFetcher`
- L19 _public prototype_ `virtual bool Fetch_Implementation(const UObject* Object, bool& bOutFetchSucceded) const final;`
- L23 _public prototype_ `virtual bool IsThreadSafe() const final;`
- L24 _public prototype_ `virtual FText GetAdditionalKeyword_Implementation() const;`
- L25 _public prototype_ `virtual FText GetNodeDisplayFetcherName_Implementation() const;`
- L30 _public member_ `TSubclassOf<UObject> Class;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Settings")` — The key for the for the string
- L33 _public member_ `bool bShouldIncludeChildClass = true;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Settings")`
- L35 _public member_ `static FText AdditionalKeyword;`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepLibraries/Public/Fetchers/DataprepFloatFetcherLibrary.h` (Public)


#### class `UDataprepFloatBoundingVolumeFetcher`  
`class UDataprepFloatBoundingVolumeFetcher final : public UDataprepFloatFetcher`  
_L12-24_
- reflection: `UCLASS(BlueprintType, NotBlueprintable, Meta = (DisplayName="Bounding Volume", ToolTip = "Filter objects based on their bounding box volume.\n For actor's bounding box only the components with a collision enabled will be used."))`
- inherits: `UDataprepFloatFetcher`
- L17 _public prototype_ `virtual float Fetch_Implementation(const UObject* Object, bool& bOutFetchSucceded) const final;`
- L21 _public prototype_ `virtual bool IsThreadSafe() const final;`
- L22 _public prototype_ `virtual FText GetNodeDisplayFetcherName_Implementation() const;`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepLibraries/Public/Fetchers/DataprepIntegerFetcherLibrary.h` (Public)


#### class `UDataprepTriangleCountFetcher`  
`class UDataprepTriangleCountFetcher final : public UDataprepIntegerFetcher`  
_L12-24_
- reflection: `UCLASS(BlueprintType, NotBlueprintable, Meta = (DisplayName="Triangle Count", ToolTip = "Filter objects based on their triangle count."))`
- inherits: `UDataprepIntegerFetcher`
- L17 _public prototype_ `virtual int32 Fetch_Implementation(const UObject* Object, bool& bOutFetchSucceded) const final;`
- L21 _public prototype_ `virtual bool IsThreadSafe() const final;`
- L22 _public prototype_ `virtual FText GetNodeDisplayFetcherName_Implementation() const;`

#### class `UDataprepVertexCountFetcher`  
`class UDataprepVertexCountFetcher final : public UDataprepIntegerFetcher`  
_L27-39_
- reflection: `UCLASS(BlueprintType, NotBlueprintable, Meta = (DisplayName = "Vertex Count", ToolTip = "Filter objects based on their vertex count."))`
- inherits: `UDataprepIntegerFetcher`
- L32 _public prototype_ `virtual int32 Fetch_Implementation(const UObject* Object, bool& bOutFetchSucceded) const final;`
- L36 _public prototype_ `virtual bool IsThreadSafe() const final;`
- L37 _public prototype_ `virtual FText GetNodeDisplayFetcherName_Implementation() const;`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepLibraries/Public/Fetchers/DataprepStringFetcherLibrary.h` (Public)


#### class `UDataprepStringObjectNameFetcher`  
`class UDataprepStringObjectNameFetcher final : public UDataprepStringFetcher`  
_L12-24_
- reflection: `UCLASS(BlueprintType, NotBlueprintable, Meta = (DisplayName="Object Name", ToolTip="Filter objects based on their names."))`
- inherits: `UDataprepStringFetcher`
- L17 _public prototype_ `virtual FString Fetch_Implementation(const UObject* Object, bool& bOutFetchSucceded) const final;`
- L21 _public prototype_ `virtual bool IsThreadSafe() const final;`
- L22 _public prototype_ `virtual FText GetNodeDisplayFetcherName_Implementation() const;`

#### class `UDataprepStringActorLabelFetcher`  
`class UDataprepStringActorLabelFetcher final : public UDataprepStringFetcher`  
_L27-40_
- reflection: `UCLASS(BlueprintType, NotBlueprintable, Meta = (DisplayName="Actor Label", ToolTip="Filter actors based on their label."))`
- inherits: `UDataprepStringFetcher`
- L33 _public prototype_ `virtual FString Fetch_Implementation(const UObject* Object, bool& bOutFetchSucceded) const override;`
- L37 _public prototype_ `virtual bool IsThreadSafe() const final;`
- L38 _public prototype_ `virtual FText GetNodeDisplayFetcherName_Implementation() const;`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepLibraries/Public/Fetchers/DataprepStringsArrayFetcherLibrary.h` (Public)


#### class `UDataprepStringActorTagsFetcher`  
`class UDataprepStringActorTagsFetcher final : public UDataprepStringsArrayFetcher`  
_L12-25_
- reflection: `UCLASS(BlueprintType, NotBlueprintable, Meta = (DisplayName = "Tag Value", ToolTip = "Filter actors based on the key values of their tags."))`
- inherits: `UDataprepStringsArrayFetcher`
- L18 _public prototype_ `virtual TArray<FString> Fetch_Implementation(const UObject* Object, bool& bOutFetchSucceded) const override;`
- L22 _public prototype_ `virtual bool IsThreadSafe() const final;`
- L23 _public prototype_ `virtual FText GetNodeDisplayFetcherName_Implementation() const;`

#### class `UDataprepStringActorLayersFetcher`  
`class UDataprepStringActorLayersFetcher final : public UDataprepStringsArrayFetcher`  
_L28-41_
- reflection: `UCLASS(BlueprintType, NotBlueprintable, Meta = (DisplayName = "Actor Layer", ToolTip = "Filter actors based on their layers."))`
- inherits: `UDataprepStringsArrayFetcher`
- L34 _public prototype_ `virtual TArray<FString> Fetch_Implementation(const UObject* Object, bool& bOutFetchSucceded) const override;`
- L38 _public prototype_ `virtual bool IsThreadSafe() const final;`
- L39 _public prototype_ `virtual FText GetNodeDisplayFetcherName_Implementation() const;`
