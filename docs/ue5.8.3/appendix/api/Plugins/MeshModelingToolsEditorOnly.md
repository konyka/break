# Plugins / MeshModelingToolsEditorOnly

- module root: `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingToolsEditorOnly`
- headers: 19; symbols: 1279
- symbol kinds: class=66, delegate=10, enum=21, enumerator=94, function=82, macro=14, member=418, namespace=12, prototype=532, struct=17, typedef=13
- PrivateDependencyModuleNames: AdvancedPreviewScene, ApplicationCore, CoreUObject, Engine, InputCore, Json, Persona, RenderCore, SceneOutliner, Slate, SlateCore, ToolWidgets, UnrealEd
- PublicDependencyModuleNames: Core, DynamicMesh, GeometryCore, GeometryFramework, InteractiveToolsFramework, MeshConversion, MeshDescription, MeshModelingTools, ModelingComponents, ModelingComponentsEditorOnly, ModelingOperators, ModelingOperatorsEditorOnly, PropertyEditor, SkeletalMeshDescription, SkeletalMeshModifiers, SkeletalMeshUtilitiesCommon, StaticMeshDescription

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingToolsEditorOnly/Private/SkeletalMesh/SkinWeightsPaintToolPropertiesCustomVersion.h` (Private)


#### enum `ESkinWeightsPaintToolPropertiesCustomVersion`  
`enum class ESkinWeightsPaintToolPropertiesCustomVersion : uint32`  
_L17-32_
- reflection: `UENUM()`
- desc: Versioning for the skin weights paint tool properties (USkinWeightsPaintToolProperties). Mind this differs fundamentally from the common custom object version logic, it is and has to use the UInteractiveToolPropertySet::RestoreProperties system. See USkinWeightsPaintToolProperties::RestoreProperties for the related upgrade path
- L20 _public enumerator_ `NoVersion = 0x00` — Before versioning was added
- L23 _public enumerator_ `SkinWeightPaintToolUseLinearColorRamp = 0x01 << 0` — Upgrade SkinWeightsPaintToolProperties to use FLinearColorRamp instead of an array of linear colors
- L27 _public enumerator_ `SkinWeightPaintToolClampStrengthToUnit = 0x01 << 1` — Clamp per-mode brush Strength values to [0,1] (Multiply slider semantics changed from "factor 0..2" to "factor 0..1 with Ctrl mirroring across 1.0").
- L30 _public enumerator_ `VersionPlusOne` — Add new versions above
- L31 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingToolsEditorOnly/Public/AttributeEditorTool.h` (Public)


#### class `UAttributeEditorToolBuilder`  
`class UAttributeEditorToolBuilder : public UMultiSelectionMeshEditingToolBuilder`  
_L23-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingToolBuilder`
- L28 _public prototype_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L29 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L32 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### enum `EAttributeEditorElementType`  
`enum class EAttributeEditorElementType : uint8`  
_L41-49_
- reflection: `UENUM()`
- L43 _public enumerator_ `Vertex = 0`
- L44 _public enumerator_ `VertexInstance = 1`
- L45 _public enumerator_ `Triangle = 2`
- L46 _public enumerator_ `Polygon = 3`
- L47 _public enumerator_ `Edge = 4`
- L48 _public enumerator_ `PolygonGroup = 5`

#### enum `EAttributeEditorAttribType`  
`enum class EAttributeEditorAttribType : uint8`  
_L53-63_
- reflection: `UENUM()`
- L55 _public enumerator_ `Int32 = 0`
- L56 _public enumerator_ `Boolean = 1`
- L57 _public enumerator_ `Float = 2`
- L58 _public enumerator_ `Vector2 = 3`
- L59 _public enumerator_ `Vector3 = 4`
- L60 _public enumerator_ `Vector4 = 5`
- L61 _public enumerator_ `String = 6`
- L62 _public enumerator_ `Unknown = 7`

#### class `UAttributeEditorAttribProperties`  
`class UAttributeEditorAttribProperties : public UInteractiveToolPropertySet`  
_L67-88_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L72 _public member_ `TArray<FString> VertexAttributes;` — `UPROPERTY(VisibleAnywhere, Category = AttributesInspector, meta=(NoResetToDefault))`
- L75 _public member_ `TArray<FString> InstanceAttributes;` — `UPROPERTY(VisibleAnywhere, Category = AttributesInspector, meta=(NoResetToDefault))`
- L78 _public member_ `TArray<FString> TriangleAttributes;` — `UPROPERTY(VisibleAnywhere, Category = AttributesInspector, meta=(NoResetToDefault))`
- L81 _public member_ `TArray<FString> PolygonAttributes;` — `UPROPERTY(VisibleAnywhere, Category = AttributesInspector, meta=(NoResetToDefault))`
- L84 _public member_ `TArray<FString> EdgeAttributes;` — `UPROPERTY(VisibleAnywhere, Category = AttributesInspector, meta=(NoResetToDefault))`
- L87 _public member_ `TArray<FString> GroupAttributes;` — `UPROPERTY(VisibleAnywhere, Category = AttributesInspector, meta=(NoResetToDefault))`

#### enum `EAttributeEditorToolActions`  
`enum class EAttributeEditorToolActions`  
_L94-115_
- reflection: `UENUM()`
- L96 _public enumerator_ `NoAction`
- L98 _public enumerator_ `ClearNormals`
- L99 _public enumerator_ `DiscardTangents`
- L100 _public enumerator_ `ClearAllUVs`
- L101 _public enumerator_ `ClearSelectedUVs`
- L102 _public enumerator_ `AddUVSet`
- L103 _public enumerator_ `DeleteSelectedUVSet`
- L104 _public enumerator_ `DuplicateSelectedUVSet`
- L105 _public enumerator_ `AddAttribute`
- L106 _public enumerator_ `AddWeightMapLayer`
- L107 _public enumerator_ `AddPolyGroupLayer`
- L108 _public enumerator_ `DeleteAttribute`
- L109 _public enumerator_ `ClearAttribute`
- L110 _public enumerator_ `CopyAttributeFromTo`
- L112 _public enumerator_ `EnableLightmapUVs`
- L113 _public enumerator_ `DisableLightmapUVs`
- L114 _public enumerator_ `ResetLightmapUVChannels`

#### class `UAttributeEditorActionPropertySet`  
`class UAttributeEditorActionPropertySet : public UInteractiveToolPropertySet`  
_L120-130_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L125 _public member_ `TWeakObjectPtr<UAttributeEditorTool> ParentTool;`
- L127 _public function_ `void Initialize(UAttributeEditorTool* ParentToolIn)`
- L128 _public prototype_ `void PostAction(EAttributeEditorToolActions Action);`

#### class `UAttributeEditorNormalsActions`  
`class UAttributeEditorNormalsActions : public UAttributeEditorActionPropertySet`  
_L134-151_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAttributeEditorActionPropertySet`
- L140 _public function_ `void ResetHardNormals()` — `UFUNCTION(CallInEditor, Category = Normals, meta = (DisplayPriority = 1))` — Remove any hard edges / split normals, setting all normals to a single averaged vertex normal
- L147 _public function_ `void DiscardTangents()` — `UFUNCTION(CallInEditor, Category = Normals, meta = (DisplayPriority = 2))` — Clear Tangents from the mesh

#### class `UAttributeEditorUVActions`  
`class UAttributeEditorUVActions : public UAttributeEditorActionPropertySet`  
_L156-197_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAttributeEditorActionPropertySet`
- L162 _public member_ `FString UVLayer;` — `UPROPERTY(EditAnywhere, Category = UVs, meta = (GetOptions = GetUVLayerNamesFunc, NoResetToDefault))`
- L165 _public prototype_ `TArray<FString> GetUVLayerNamesFunc();` — `UFUNCTION()`
- L168 _public member_ `TArray<FString> UVLayerNamesList;` — `UPROPERTY()`
- L172 _public function_ `void ClearAll()` — `UFUNCTION(CallInEditor, Category = UVs, meta = (DisplayPriority = 1))` — Clear all UV layers, setting all UV values to (0,0)
- L179 _public function_ `void AddNew()` — `UFUNCTION(CallInEditor, Category = UVs, meta = (DisplayPriority = 2))` — Add a new UV layer
- L186 _public function_ `void DeleteSelected()` — `UFUNCTION(CallInEditor, Category = UVs, meta = (DisplayPriority = 3))` — Clear the selected UV layers, setting all UV values to (0,0)
- L193 _public function_ `void DuplicateSelected()` — `UFUNCTION(CallInEditor, Category = UVs, meta = (DisplayPriority = 4))` — Duplicate the selected UV layers

#### class `UAttributeEditorLightmapUVActions`  
`class UAttributeEditorLightmapUVActions : public UAttributeEditorActionPropertySet`  
_L203-237_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAttributeEditorActionPropertySet`
- L209 _public member_ `bool bGenerateLightmapUVs;` — `UPROPERTY(VisibleAnywhere, Category = LightmapUVs)` — Whether or not Lightmap UVs are enabled in the Static Mesh Build Settings. Use the Static Mesh Editor to change this value.
- L213 _public member_ `int32 SourceUVIndex;` — `UPROPERTY(VisibleAnywhere, Category = LightmapUVs, meta = (DisplayName = "Source Channel", NoResetToDefault))` — Source UV channel used to compute Lightmap UVs. Use the Static Mesh Editor to change this value.
- L217 _public member_ `int32 DestinationUVIndex;` — `UPROPERTY(VisibleAnywhere, Category = LightmapUVs, meta = (DisplayName = "Dest Channel", NoResetToDefault))` — Lightmap UVs are stored in this UV Channel. Use the Static Mesh Editor to change this value.
- L220 _public function_ `void Enable()` — `UFUNCTION(CallInEditor, Category = LightmapUVs, meta = (DisplayPriority = 1))`
- L226 _public function_ `void Disable()` — `UFUNCTION(CallInEditor, Category = LightmapUVs, meta = (DisplayPriority = 2))`
- L233 _public function_ `void Reset()` — `UFUNCTION(CallInEditor, Category = LightmapUVs, meta = (DisplayPriority = 3))` — Reset Lightmap UV channels to Source Channel UV0 and Destination as UVMax+1

#### class `UAttributeEditorNewAttributeActions`  
`class UAttributeEditorNewAttributeActions : public UAttributeEditorActionPropertySet`  
_L241-276_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAttributeEditorActionPropertySet`
- L246 _public member_ `FString NewName;` — `UPROPERTY(EditAnywhere, Category = NewAttribute, meta = (DisplayName = "New Attribute Name"))`
- L250 _public member_ `EAttributeEditorElementType ElementType;` — `UPROPERTY(EditAnywhere, Category = NewAttribute)` — `UPROPERTY()`
- L254 _public member_ `EAttributeEditorAttribType DataType;` — `UPROPERTY(EditAnywhere, Category = NewAttribute)` — `UPROPERTY()`
- L264 _public function_ `void AddWeightMapLayer()` — `UFUNCTION(CallInEditor, Category = NewAttribute, meta = (DisplayPriority = 2))` — Add a new Per-Vertex Weight Map layer with the given Name
- L271 _public function_ `void AddPolyGroupLayer()` — `UFUNCTION(CallInEditor, Category = NewAttribute, meta = (DisplayPriority = 3, DisplayName = "Add PolyGroup Layer"))` — Add a new PolyGroup layer with the given Name

#### class `UAttributeEditorModifyAttributeActions`  
`class UAttributeEditorModifyAttributeActions : public UAttributeEditorActionPropertySet`  
_L280-306_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAttributeEditorActionPropertySet`
- L285 _public member_ `FString Attribute;` — `UPROPERTY(EditAnywhere, Category = ModifyAttribute, meta = (GetOptions = GetAttributeNamesFunc, NoResetToDefault))`
- L288 _public prototype_ `TArray<FString> GetAttributeNamesFunc();` — `UFUNCTION()`
- L291 _public member_ `TArray<FString> AttributeNamesList;` — `UPROPERTY()`
- L295 _public function_ `void DeleteSelected()` — `UFUNCTION(CallInEditor, Category = ModifyAttribute, meta = (DisplayPriority = 1))` — Remove the selected Attribute Name from the mesh

#### class `UAttributeEditorCopyAttributeActions`  
`class UAttributeEditorCopyAttributeActions : public UAttributeEditorActionPropertySet`  
_L310-325_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAttributeEditorActionPropertySet`
- L315 _public member_ `TArray<FString> FromAttribute;` — `UPROPERTY(EditAnywhere, Category = CopyAttribute)`
- L318 _public member_ `TArray<FString> ToAttribute;` — `UPROPERTY(EditAnywhere, Category = CopyAttribute)`
- L321 _public function_ `void CopyFromTo()` — `UFUNCTION(CallInEditor, Category = CopyAttribute, meta = (DisplayPriority = 1))`

#### class `UAttributeEditorTool`  
`class UAttributeEditorTool : public UMultiSelectionMeshEditingTool, public IInteractiveToolManageGeometrySelectionAPI`  
_L336-412_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingTool,IInteractiveToolManageGeometrySelectionAPI`
- desc: Mesh Attribute Editor Tool
- L342 _public prototype_ `UAttributeEditorTool();`
- L344 _public prototype_ `virtual void Setup() override;`
- L345 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L346 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L348 _public function_ `virtual bool HasCancel() const override`
- L349 _public function_ `virtual bool HasAccept() const override`
- L350 _public function_ `virtual bool CanAccept() const override`
- L352 _public prototype_ `virtual void RequestAction(EAttributeEditorToolActions ActionType);`
- L355 _public function_ `virtual bool IsInputSelectionValidOnOutput() override` — IInteractiveToolManageGeometrySelectionAPI -- this tool won't update external geometry selection or change selection-relevant mesh IDs
- L363 _protected member_ `TObjectPtr<UAttributeEditorNormalsActions> NormalsActions;` — `UPROPERTY()`
- L366 _protected member_ `TObjectPtr<UAttributeEditorUVActions> UVActions;` — `UPROPERTY()`
- L369 _protected member_ `TObjectPtr<UAttributeEditorLightmapUVActions> LightmapUVActions;` — `UPROPERTY()`
- L372 _protected member_ `TObjectPtr<UAttributeEditorAttribProperties> AttributeProps;` — `UPROPERTY()`
- L375 _protected member_ `TObjectPtr<UAttributeEditorNewAttributeActions> NewAttributeProps;` — `UPROPERTY()`
- L378 _protected member_ `TObjectPtr<UAttributeEditorModifyAttributeActions> ModifyAttributeProps;` — `UPROPERTY()`
- L381 _protected member_ `TObjectPtr<UAttributeEditorCopyAttributeActions> CopyAttributeProps;` — `UPROPERTY()`
- L385 _protected member_ `bool bTargetIsStaticMesh = true;`
- L387 _protected member_ `bool bAttributeListsValid = false;`
- L388 _protected member_ `bool bHaveAutoGeneratedLightmapUVSet = false;`
- L389 _protected prototype_ `void InitializeAttributeLists();`
- L391 _protected prototype_ `void UpdateAutoGeneratedLightmapUVChannel(UPrimitiveComponent* TargetComponent, int32 NewMaxUVChannels);`
- L393 _protected member_ `EAttributeEditorToolActions PendingAction = EAttributeEditorToolActions::NoAction;`
- L394 _protected prototype_ `void ClearNormals();`
- L395 _protected prototype_ `void DiscardTangents();`
- L396 _protected prototype_ `void ClearUVs();`
- L397 _protected prototype_ `void DeleteSelectedUVSet();`
- L398 _protected prototype_ `void DuplicateSelectedUVSet();`
- L399 _protected prototype_ `void AddUVSet();`
- L400 _protected prototype_ `void AddNewAttribute();`
- L401 _protected prototype_ `void AddNewWeightMap();`
- L402 _protected prototype_ `void AddNewGroupsLayer();`
- L403 _protected prototype_ `void DeleteAttribute();`
- L404 _protected prototype_ `void ClearAttribute();`
- L405 _protected prototype_ `void SetLightmapUVsEnabled(bool bEnabled);`
- L406 _protected prototype_ `void ResetLightmapUVsChannels();`
- L408 _protected prototype_ `void AddNewAttribute(EAttributeEditorElementType ElemType, EAttributeEditorAttribType AttribType, FName AttributeName);`
- L411 _protected prototype_ `void EmitAttributesChange();`

#### class `FAttributeEditor_AttributeListsChange`  
`class FAttributeEditor_AttributeListsChange : public FToolCommandChange`  
_L415-421_
- inherits: `FToolCommandChange`
- L418 _public prototype_ `virtual void Apply(UObject* Object) override;`
- L419 _public prototype_ `virtual void Revert(UObject* Object) override;`
- L420 _public prototype_ `virtual FString ToString() const override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MESHMODELINGTOOLSEDITORONLY_API`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingToolsEditorOnly/Public/DetailsCustomizations/UVUnwrapToolCustomizations.h` (Public)


#### class `FRecomputeUVsToolDetails`  
`class FRecomputeUVsToolDetails : public IDetailCustomization`  
_L12-23_
- inherits: `IDetailCustomization`
- desc: Customization for UUVEditorRecomputeUVsToolProperties
- L15 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L16 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L19 _protected prototype_ `void EvaluateLayoutTypeRestrictions(TSharedRef<IPropertyHandle> IslandGenerationModeHandle, TSharedRef<IPropertyHandle> UnwrapTypeHandle, TSharedRef<IPropertyHandle> LayoutTypeHandle);`
- L22 _protected member_ `TSharedPtr<FPropertyRestriction> LayoutTypeEnumRestriction;` — Property restriction applied to blend paint enum dropdown box

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingToolsEditorOnly/Public/MeshModelingToolsEditorOnly.h` (Public)


#### class `FMeshModelingToolsEditorOnlyModule`  
`class FMeshModelingToolsEditorOnlyModule : public IModuleInterface`  
_L10-23_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L17 _public prototype_ `void OnPostEngineInit();`
- L21 _protected member_ `TArray<FName> ClassesToUnregisterOnShutdown;`
- L22 _protected member_ `TArray<FName> PropertiesToUnregisterOnShutdown;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMeshModelingToolsEditor, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMeshModelingToolsEditor, Log, All);`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingToolsEditorOnly/Public/ParameterizeMeshTool.h` (Public)


#### class `UParameterizeMeshToolBuilder`  
`class UParameterizeMeshToolBuilder : public USingleSelectionMeshEditingToolBuilder`  
_L30-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingToolBuilder`
- L34 _public prototype_ `virtual USingleSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L35 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`

#### class `UParameterizeMeshTool`  
`class UParameterizeMeshTool : public USingleSelectionMeshEditingTool, public IInteractiveToolManageGeometrySelectionAPI`  
_L44-106_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingTool,IInteractiveToolManageGeometrySelectionAPI`
- desc: UParameterizeMeshTool automatically decomposes the input mesh into charts, solves for UVs, and then packs the resulting charts
- L49 _public prototype_ `virtual void Setup() override;`
- L50 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L52 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L53 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L55 _public function_ `virtual bool HasCancel() const override`
- L56 _public function_ `virtual bool HasAccept() const override`
- L57 _public prototype_ `virtual bool CanAccept() const override;`
- L59 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L62 _public function_ `virtual bool IsInputSelectionValidOnOutput() override` — IInteractiveToolManageGeometrySelectionAPI -- this tool won't update external geometry selection or change selection-relevant mesh IDs
- L69 _protected member_ `TObjectPtr<UMeshUVChannelProperties> UVChannelProperties = nullptr;` — `UPROPERTY()`
- L72 _protected member_ `TObjectPtr<UParameterizeMeshToolProperties> Settings = nullptr;` — `UPROPERTY()`
- L75 _protected member_ `TObjectPtr<UParameterizeMeshToolUVAtlasProperties> UVAtlasProperties = nullptr;` — `UPROPERTY()`
- L78 _protected member_ `TObjectPtr<UParameterizeMeshToolXAtlasProperties> XAtlasProperties = nullptr;` — `UPROPERTY()`
- L81 _protected member_ `TObjectPtr<UParameterizeMeshToolPatchBuilderProperties> PatchBuilderProperties = nullptr;` — `UPROPERTY()`
- L84 _protected member_ `TObjectPtr<UPolygroupLayersProperties> PolygroupLayerProperties = nullptr;` — `UPROPERTY()`
- L87 _protected member_ `TObjectPtr<UExistingMeshMaterialProperties> MaterialSettings = nullptr;` — `UPROPERTY()`
- L90 _protected member_ `bool bCreateUVLayoutViewOnSetup = true;` — `UPROPERTY()`
- L93 _protected member_ `TObjectPtr<UUVLayoutPreview> UVLayoutView = nullptr;` — `UPROPERTY()`
- L96 _protected member_ `TObjectPtr<UMeshOpPreviewWithBackgroundCompute> Preview = nullptr;` — `UPROPERTY()`
- L99 _protected member_ `TObjectPtr<UParameterizeMeshOperatorFactory> Factory;` — `UPROPERTY()`
- L101 _protected member_ `TSharedPtr<UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> InputMesh;`
- L103 _protected prototype_ `void OnMethodTypeChanged();`
- L105 _protected prototype_ `void OnPreviewMeshUpdated();`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API MESHMODELINGTOOLSEDITORONLY_API`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingToolsEditorOnly/Public/PolygonOnMeshTool.h` (Public)


#### class `UPolygonOnMeshToolBuilder`  
`class UPolygonOnMeshToolBuilder : public USingleSelectionMeshEditingToolBuilder`  
_L36-42_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingToolBuilder`
- L41 _public prototype_ `virtual USingleSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`

#### enum `EPolygonType`  
`enum class EPolygonType`  
_L47-54_
- reflection: `UENUM()`
- L49 _public enumerator_ `Circle`
- L50 _public enumerator_ `Square`
- L51 _public enumerator_ `Rectangle`
- L52 _public enumerator_ `RoundRect`
- L53 _public enumerator_ `Custom`

#### class `UPolygonOnMeshToolProperties`  
`class UPolygonOnMeshToolProperties : public UInteractiveToolPropertySet`  
_L63-124_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Standard properties of the polygon-on-mesh operations
- L70 _public member_ `EEmbeddedPolygonOpMethod Operation = EEmbeddedPolygonOpMethod::CutThrough;` — `UPROPERTY(EditAnywhere, Category = Operation)` — What operation to apply using the Polygon
- L74 _public member_ `EPolygonType Shape = EPolygonType::Circle;` — `UPROPERTY(EditAnywhere, Category = Shape)` — Polygon Shape to use in this Operation
- L78 _public member_ `bool bCutWithBoolean = true;` — `UPROPERTY(EditAnywhere, Category = Operation)` — Use a volumetric boolean rather than curve projection; cuts through all layers and across edges
- L84 _public member_ `bool bTryToFixHoles = false;` — `UPROPERTY(EditAnywhere, Category = Operation, meta = (EditCondition = "bCutWithBoolean && (Operation == EEmbeddedPolygonOpMethod::CutThrough || Operation == EEmbeddedPolygonOpMethod::CutOutside || Operation == EEmbeddedPolygonOpMethod::InsertPolygon)", EditConditionHides))` — Automatically attempt to fill any open boundaries left by CSG (e.g. due to numerical errors)
- L93 _public member_ `float PolygonScale = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "0.01", UIMax = "10.0", ClampMin = "0.00001", ClampMax = "10000"))` — Scale of polygon to embed
- L97 _public member_ `float Width = 100.0f;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "0.001", UIMax = "1000.0", ClampMin = "0.00001", ClampMax = "10000", EditCondition = "Shape != EPolygonType::Custom"))` — Width of Polygon
- L101 _public member_ `float Height = 50.0f;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "0.001", UIMax = "1000.0", ClampMin = "0.00001", ClampMax = "10000", EditCondition = "Shape == EPolygonType::Rectangle || Shape == EPolygonType::RoundRect"))` — Height of Polygon
- L105 _public member_ `float CornerRatio = 0.5f;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "0.01", ClampMin = "0.00001", ClampMax = "1.0", EditCondition = "Shape == EPolygonType::RoundRect"))` — Corner Ratio of RoundRect Polygon
- L109 _public member_ `int32 Subdivisions = 12;` — `UPROPERTY(EditAnywhere, Category = Shape, meta = (UIMin = "3", UIMax = "20", ClampMin = "3", ClampMax = "10000", EditCondition = "Shape == EPolygonType::Circle || Shape == EPolygonType::RoundRect"))` — Number of sides in Circle or RoundRect Corner
- L116 _public member_ `bool bCanAcceptFailedResult = false;` — `UPROPERTY(EditAnywhere, Category = Operation, AdvancedDisplay)` — Whether the tool will allow accepting a result if the operation fails, for instance due to inability to insert the polygon when not cutting with boolean, or due to unrepaired cracks in the result.
- L123 _public member_ `bool bShowIntermediateResultOnFailure = false;` — `UPROPERTY(EditAnywhere, Category = Operation, AdvancedDisplay, meta = (EditCondition = "!bCanAcceptFailedResult"))` — If an operation fails and we do not allow accepting the result, whether to show the intermediate failed result, or to show the original mesh.

#### enum `EPolygonOnMeshToolActions`  
`enum class EPolygonOnMeshToolActions`  
_L130-134_
- reflection: `UENUM()`
- L132 _public enumerator_ `NoAction`
- L133 _public enumerator_ `DrawPolygon`

#### class `UPolygonOnMeshToolActionPropertySet`  
`class UPolygonOnMeshToolActionPropertySet : public UInteractiveToolPropertySet`  
_L138-155_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L143 _public member_ `TWeakObjectPtr<UPolygonOnMeshTool> ParentTool;`
- L145 _public function_ `void Initialize(UPolygonOnMeshTool* ParentToolIn)`
- L147 _public prototype_ `void PostAction(EPolygonOnMeshToolActions Action);`
- L151 _public function_ `void DrawPolygon()` — `UFUNCTION(CallInEditor, Category = Actions, meta = (DisplayName = "Draw Polygon", DisplayPriority = 1))` — Extrude the current set of selected faces. Click in viewport to confirm extrude height.

#### class `UPolygonOnMeshTool`  
`class UPolygonOnMeshTool : public USingleSelectionMeshEditingTool, public UE::Geometry::IDynamicMeshOperatorFactory, public IClickBehaviorTarget, public IHoverBehaviorTarget`  
_L164-260_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingTool,UE::Geometry::IDynamicMeshOperatorFactory,IClickBehaviorTarget,IHoverBehaviorTarget`
- desc: Simple Mesh Plane Cutting Tool
- L170 _public prototype_ `UPolygonOnMeshTool();`
- L172 _public prototype_ `virtual void Setup() override;`
- L173 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L175 _public prototype_ `virtual void SetWorld(UWorld* World);`
- L177 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L178 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L180 _public function_ `virtual bool HasCancel() const override`
- L181 _public function_ `virtual bool HasAccept() const override`
- L182 _public prototype_ `virtual bool CanAccept() const override;`
- L184 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L187 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory API
- L190 _public prototype_ `virtual void RequestAction(EPolygonOnMeshToolActions ActionType);`
- L198 _public prototype_ `virtual bool HitTest(const FRay& Ray, FHitResult& OutHit);`
- L201 _public prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos) override;` — IClickBehaviorTarget API
- L202 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPos) override;`
- L205 _public prototype_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos) override;` — IHoverBehaviorTarget API
- L206 _public function_ `virtual void OnBeginHover(const FInputDeviceRay& DevicePos) override`
- L207 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L208 _public function_ `virtual void OnEndHover() override`
- L214 _protected member_ `TObjectPtr<UPolygonOnMeshToolProperties> BasicProperties;` — `UPROPERTY()`
- L217 _protected member_ `TObjectPtr<UPolygonOnMeshToolActionPropertySet> ActionProperties;` — `UPROPERTY()`
- L220 _protected member_ `TObjectPtr<UMeshOpPreviewWithBackgroundCompute> Preview;` — `UPROPERTY()`
- L223 _protected member_ `TObjectPtr<ULineSetComponent> DrawnLineSet;` — `UPROPERTY()`
- L225 _protected member_ `TArray<int> EdgesOnFailure;`
- L226 _protected member_ `TArray<int> EmbeddedEdges;`
- L227 _protected member_ `bool bOperationSucceeded;`
- L230 _protected member_ `UWorld* TargetWorld;`
- L232 _protected member_ `FTransform3d WorldTransform;`
- L233 _protected member_ `FViewCameraState CameraState;`
- L235 _protected member_ `TSharedPtr<UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> OriginalDynamicMesh;`
- L238 _protected member_ `TObjectPtr<UConstructionPlaneMechanic> PlaneMechanic = nullptr;` — `UPROPERTY()`
- L241 _protected member_ `TObjectPtr<UCollectSurfacePathMechanic> DrawPolygonMechanic = nullptr;` — `UPROPERTY()`
- L243 _protected member_ `EPolygonOnMeshToolActions PendingAction = EPolygonOnMeshToolActions::NoAction;`
- L245 _protected member_ `UE::Geometry::FFrame3d DrawPlaneWorld;`
- L247 _protected member_ `UE::Geometry::FPolygon2d LastDrawnPolygon;`
- L248 _protected member_ `UE::Geometry::FPolygon2d ActivePolygon;`
- L249 _protected prototype_ `void UpdatePolygonType();`
- L251 _protected prototype_ `void SetupPreview();`
- L252 _protected prototype_ `void UpdateDrawPlane();`
- L254 _protected prototype_ `void BeginDrawPolygon();`
- L255 _protected prototype_ `void CompleteDrawPolygon();`
- L257 _protected prototype_ `void UpdateVisualization();`
- L259 _protected prototype_ `void GenerateAsset(const TArray<FDynamicMeshOpResult>& Results);`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API MESHMODELINGTOOLSEDITORONLY_API`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingToolsEditorOnly/Public/SimplifyMeshTool.h` (Public)


#### class `USimplifyMeshToolBuilder`  
`class USimplifyMeshToolBuilder : public USingleSelectionMeshEditingToolBuilder`  
_L25-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingToolBuilder`
- L30 _public prototype_ `virtual USingleSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`

#### enum `EApplyWeightMapToSimplifyMeasure`  
`enum class EApplyWeightMapToSimplifyMeasure : uint32`  
_L36-43_
- reflection: `UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L38 _public enumerator_ `None = 0 UMETA(Hidden)`
- L39 _public enumerator_ `QuadricError = 1 << 0`
- L40 _public enumerator_ `GeometricTolerance = 1 << 1`
- L41 _public enumerator_ `EdgeLengths = 1 << 2`
- L42 _public enumerator_ `All = 0b111 UMETA(Hidden)`

#### class `USimplifyMeshToolProperties`  
`class USimplifyMeshToolProperties : public UMeshConstraintProperties`  
_L50-149_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshConstraintProperties`
- desc: Standard properties of the Simplify operation
- L54 _public prototype_ `USimplifyMeshToolProperties();`
- L58 _public member_ `ESimplifyType SimplifierType;` — `UPROPERTY(EditAnywhere, Category = Options)` — Simplification Scheme
- L62 _public member_ `ESimplifyTargetType TargetMode;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (EditCondition = "SimplifierType != ESimplifyType::MinimalPlanar && SimplifierType != ESimplifyType::MinimalPolygroup && SimplifierType != ESimplifyType::ClusterBased"))` — Simplification Target Type
- L67 _public member_ `int TargetPercentage;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (UIMin = "0", UIMax = "100", ClampMin = "0.0", ClampMax = "100.0", EditCondition = "SimplifierType != ESimplifyType::ClusterBased && SimplifierType != ESimplifyType::MinimalPolygroup && SimplifierType != ESimplifyType::MinimalPlanar && TargetMode == ESimplifyTargetType::Percentage"))` — Target percentage of original triangle count
- L72 _public member_ `float TargetEdgeLength;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (UIMin = "3.0", UIMax = "10.0", ClampMin = "0.001", ClampMax = "1000.0", EditCondition = "SimplifierType == ESimplifyType::ClusterBased || (TargetMode == ESimplifyTargetType::EdgeLength && SimplifierType != ESimplifyType::UEStandard && SimplifierType != ESimplifyType::MinimalPlanar && SimplifierType != ESimplifyType::MinimalPolygroup)"))` — Target edge length
- L77 _public member_ `float TargetQuadricErrorRoot = 0;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (UIMin = "0.0", UIMax = "100.0", ClampMin = "0.", ClampMax = "10000.0", EditCondition = "TargetMode == ESimplifyTargetType::QuadricError && (SimplifierType != ESimplifyType::UEStandard && SimplifierType != ESimplifyType::MinimalPlanar && SimplifierType != ESimplifyType::MinimalPolygroup && SimplifierType != ESimplifyType::ClusterBased)"))` — Square root of target quadric error
- L82 _public member_ `int TargetTriangleCount;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (UIMin = "4", UIMax = "10000", ClampMin = "1", ClampMax = "9999999999", EditCondition = "TargetMode == ESimplifyTargetType::TriangleCount && SimplifierType != ESimplifyType::MinimalPlanar && SimplifierType != ESimplifyType::MinimalPolygroup && SimplifierType != ESimplifyType::ClusterBased"))` — Target triangle count
- L87 _public member_ `int TargetVertexCount;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (UIMin = "4", UIMax = "10000", ClampMin = "1", ClampMax = "9999999999", EditCondition = "TargetMode == ESimplifyTargetType::VertexCount && SimplifierType != ESimplifyType::MinimalPlanar && SimplifierType != ESimplifyType::ClusterBased"))` — Target vertex count
- L91 _public member_ `float MinimalAngleThreshold = 0.01f;` — `UPROPERTY()` — Angle threshold in degrees used for testing if two triangles should be considered coplanar, or two lines collinear
- L96 _public member_ `float PolyEdgeAngleTolerance = .1f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (UIMin = "0.001", ClampMin = "0.0", UIMax = "90.0", ClampMax = "180.0", EditCondition = "SimplifierType == ESimplifyType::MinimalPolygroup"))` — Threshold angle change (in degrees) along a polygroup edge, above which a vertex must be added
- L100 _public member_ `float BoundaryEdgeAngleTolerance = 30.0f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (UIMin = "0.001", ClampMin = "0.0", UIMax = "90.0", ClampMax = "180.0", EditCondition = "SimplifierType == ESimplifyType::ClusterBased"))` — Threshold angle change (in degrees) between adjacent boundary edges, above which the common vertex must be preserved
- L104 _public member_ `bool bDiscardAttributes;` — `UPROPERTY(EditAnywhere, Category = Options)` — Discard UVs and existing normals, allowing the simplifier to ignore any UV and normal seams. New per-vertex normals are computed.
- L108 _public member_ `bool bGeometricConstraint;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (EditCondition = "SimplifierType != ESimplifyType::MinimalPolygroup"))` — If true, then simplification will consider geometric deviation with the input mesh
- L113 _public member_ `float GeometricTolerance;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (UIMin = "0.0", UIMax = "10.0", ClampMin = "0.0", ClampMax = "10000000.0", EditCondition = "bGeometricConstraint && SimplifierType != ESimplifyType::UEStandard && SimplifierType != ESimplifyType::MinimalPolygroup"))` — Geometric deviation tolerance used when bGeometricConstraint is enabled, to limit the geometric deviation between the simplified and original meshes
- L118 _public member_ `float RegularizeWeight = 0.000001f;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (UIMin = "0.0", UIMax = "0.01", ClampMin = "0.0", ClampMax = "10.0", EditCondition = "SimplifierType != ESimplifyType::UEStandard && SimplifierType != ESimplifyType::MinimalPolygroup && SimplifierType != ESimplifyType::ClusterBased"))` — Optional regularization term to favor vertices remaining near their original locations. Using a small regularization weight can give cleaner topology in flat regions.
- L121 _public member_ `uint32 ApplyWeightMapTo = (int32)EApplyWeightMapToSimplifyMeasure::All;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (Bitmask, BitmaskEnum = "/Script/MeshModelingToolsEditorOnly.EApplyWeightMapToSimplifyMeasure"))`
- L125 _public member_ `bool bShowGroupColors = false;` — `UPROPERTY(EditAnywhere, Category = Display)` — Display colors corresponding to the mesh's polygon groups
- L129 _public member_ `bool bReproject;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay)` — Enable projection back to input mesh
- L133 _protected function_ `virtual bool IsPreventNormalFlipsEnabled() const override`
- L141 _protected function_ `virtual bool IsPreventTinyTrianglesEnabled() const override`

#### class `USimplifyMeshTool`  
`class USimplifyMeshTool : public USingleSelectionMeshEditingTool, public UE::Geometry::IDynamicMeshOperatorFactory`  
_L158-200_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingTool,UE::Geometry::IDynamicMeshOperatorFactory`
- desc: Simple Mesh Simplifying Tool
- L163 _public prototype_ `virtual void Setup() override;`
- L164 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L166 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L168 _public function_ `virtual bool HasCancel() const override`
- L169 _public function_ `virtual bool HasAccept() const override`
- L170 _public prototype_ `virtual bool CanAccept() const override;`
- L172 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L175 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory API
- L179 _private member_ `TObjectPtr<USimplifyMeshToolProperties> SimplifyProperties;` — `UPROPERTY()`
- L182 _private member_ `TObjectPtr<UMeshWeightChannelDensityProperties> WeightMapProperties;` — `UPROPERTY()`
- L185 _private member_ `TObjectPtr<UMeshStatisticsProperties> MeshStatisticsProperties;` — `UPROPERTY()`
- L188 _private member_ `TObjectPtr<UMeshOpPreviewWithBackgroundCompute> Preview;` — `UPROPERTY()`
- L191 _private member_ `TObjectPtr<UMeshElementsVisualizer> MeshElementsDisplay;` — `UPROPERTY()`
- L194 _private member_ `TSharedPtr<FMeshDescription, ESPMode::ThreadSafe> OriginalMeshDescription;` — cached mesh description version of the original mesh -- created (by conversion or copy) as needed
- L196 _private member_ `TSharedPtr<UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> OriginalMesh;` — Dynamic Mesh versions precomputed in Setup (rather than recomputed for every simplify op)
- L197 _private member_ `TSharedPtr<UE::Geometry::FDynamicMeshAABBTree3, ESPMode::ThreadSafe> OriginalMeshSpatial;`
- L199 _private prototype_ `void UpdateVisualization();`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MESHMODELINGTOOLSEDITORONLY_API`
- L18 _prototype_ `PREDECLARE_GEOMETRY(class FDynamicMesh3);`
- L19 _prototype_ `PREDECLARE_GEOMETRY(typedef TMeshAABBTree3<FDynamicMesh3> FDynamicMeshAABBTree3);`
- L44 _prototype_ `ENUM_CLASS_FLAGS(EApplyWeightMapToSimplifyMeasure);`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingToolsEditorOnly/Public/SkeletalMesh/IHotkeyHintProvider.h` (Public)


#### class `UHotkeyHintProvider`  
`class UHotkeyHintProvider : public UInterface`  
_L15-19_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IHotkeyHintProvider`  
`class IHotkeyHintProvider : public IInterface`  
_L22-70_
- inherits: `IInterface`
- L33 _public prototype_ `virtual void GetHotkeyHints(TArray<FHotkeyHint>& OutHints) const = 0;`
- L38 _public function_ `static bool TryAppendCommandHint(TArray<FHotkeyHint>& OutHints, const TSharedPtr<const FUICommandInfo>& Command, const TSharedPtr<const FUICommandList>& CommandList = nullptr)` — If CommandList is provided, the hint is filtered by CanExecute and skipped if Command isn't bound on the list. If null, the hint is always appended (tool actions, which are inherently always-executable while the tool is active, can pass null).
- L62 _public function_ `static bool TryAppendCommandHint(TArray<FHotkeyHint>& OutHints, const FName ContextName, const FName CommandName, const TSharedPtr<const FUICommandList>& CommandList = nullptr)`

#### struct `IHotkeyHintProvider::FHotkeyHint`  
`struct FHotkeyHint`  
_L27-31_
- L29 _public member_ `FText Label;`
- L30 _public member_ `FText HotkeyText;`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingToolsEditorOnly/Public/SkeletalMesh/ISkeletalMeshGeometryIsolationAwareTool.h` (Public)


#### class `USkeletalMeshGeometryIsolationAwareTool`  
`class USkeletalMeshGeometryIsolationAwareTool : public UInterface`  
_L11-15_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `ISkeletalMeshGeometryIsolationAwareTool`  
`class ISkeletalMeshGeometryIsolationAwareTool : public IInterface`  
_L18-24_
- inherits: `IInterface`
- L23 _public prototype_ `virtual bool IsInputIsolationValidOnOutput() const = 0;`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingToolsEditorOnly/Public/SkeletalMesh/RefSkeletonPoser.h` (Public)


#### class `URefSkeletonPoser`  
`class URefSkeletonPoser: public UObject`  
_L15-70_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L20 _public prototype_ `void SetRefSkeleton(const FReferenceSkeleton& InRefSkeleton);`
- L21 _public prototype_ `const FReferenceSkeleton& GetRefSkeleton() const;`
- L23 _public prototype_ `void ModifyBoneAdditiveTransform(int32 BoneIndex, TFunctionRef<void(FTransform&)> InModifyFunc);`
- L24 _public prototype_ `void ClearBoneAdditiveTransform(int32 BoneIndex);`
- L25 _public prototype_ `void ClearAllBoneAdditiveTransforms();`
- L27 _public prototype_ `TOptional<FTransform> GetBoneAdditiveTransform(int32 BoneIndex);`
- L29 _public prototype_ `const TArray<FTransform>& GetComponentSpaceTransforms();`
- L31 _public prototype_ `const FTransform& GetComponentSpaceTransform(const uint32 Index);`
- L33 _public prototype_ `const TArray<FTransform>& GetComponentSpaceTransformsRefPose();`
- L35 _public prototype_ `void BeginPoseChange();`
- L36 _public prototype_ `void EndPoseChange();`
- L37 _public prototype_ `bool IsRecordingPoseChange();`
- L40 _protected prototype_ `void Invalidate(const uint32 Index = INDEX_NONE);`
- L42 _protected member_ `FReferenceSkeleton RefSkeleton;`
- L43 _protected member_ `TArray<FTransform> Transforms;`
- L44 _protected member_ `TBitArray<> TransformCached;`
- L46 _protected member_ `TMap<int32, FTransform> AdditiveTransforms;`
- L48 _protected member_ `TArray<FTransform> RefTransforms;`
- L67 _protected member_ `TUniquePtr<FPoseChange> ActivePoseChange;`
- L69 _protected member_ `bool bPoseChanged = false;`

#### class `URefSkeletonPoser::FPoseChange`  
`class FPoseChange : public FToolCommandChange`  
_L50-65_
- inherits: `FToolCommandChange`
- L53 _public prototype_ `FPoseChange(URefSkeletonPoser* InPoser);`
- L55 _public member_ `TMap<int32, FTransform> OldAdditiveTransforms;`
- L56 _public member_ `TMap<int32, FTransform> NewAdditiveTransforms;`
- L58 _public prototype_ `virtual FString ToString() const override;`
- L60 _public prototype_ `virtual void Apply(UObject* Object) override;`
- L62 _public prototype_ `virtual void Revert(UObject* Object) override;`
- L64 _public prototype_ `void Close(URefSkeletonPoser* InPoser);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MESHMODELINGTOOLSEDITORONLY_API`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingToolsEditorOnly/Public/SkeletalMesh/SReferenceSkeletonTree.h` (Public)


#### class `ReferenceSkeletonTreeLocals::FSkeletonModifierChange`  
`class FSkeletonModifierChange : public FCommandChange`  
_L27-47_
- inherits: `FCommandChange`
- L30 _public prototype_ `FSkeletonModifierChange(const USkeletonModifier* InModifier);`
- L32 _public function_ `virtual FString ToString() const override`
- L37 _public prototype_ `virtual void Apply(UObject* Object) override;`
- L38 _public prototype_ `virtual void Revert(UObject* Object) override;`
- L40 _public prototype_ `void StoreSkeleton(const USkeletonModifier* InModifier);`
- L43 _private member_ `FReferenceSkeleton PreChangeSkeleton;`
- L44 _private member_ `TArray<int32> PreBoneTracker;`
- L45 _private member_ `FReferenceSkeleton PostChangeSkeleton;`
- L46 _private member_ `TArray<int32> PostBoneTracker;`

#### enum `ReferenceSkeletonTreeLocals::EBoneRenameType`  
`enum class EBoneRenameType : uint32`  
_L49-55_
- L51 _public enumerator_ `Rename`
- L52 _public enumerator_ `SearchAndReplace`
- L53 _public enumerator_ `AddPrefix`
- L54 _public enumerator_ `AddSuffix`

#### class `FBoneElement`  
`class FBoneElement : public TSharedFromThis<FBoneElement>`  
_L59-82_
- inherits: `TSharedFromThis<FBoneElement>`
- L62 _public prototype_ `FBoneElement(const FName& InBoneName, TWeakObjectPtr<USkeletonModifier> InModifier);`
- L64 _public member_ `FName BoneName;`
- L66 _public member_ `bool bIsHidden = false;`
- L68 _public member_ `TSharedPtr<FBoneElement> UnFilteredParent;`
- L69 _public member_ `TSharedPtr<FBoneElement> Parent;`
- L70 _public member_ `TArray<TSharedPtr<FBoneElement>> Children;`
- L72 _public prototype_ `void RequestRename(const ReferenceSkeletonTreeLocals::EBoneRenameType InRenameType) const;`
- L74 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnRenameRequested, const ReferenceSkeletonTreeLocals::EBoneRenameType);`
- L75 _public member_ `FOnRenameRequested OnRenameRequested;`
- L77 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnRenamed, const FName, const FName);`
- L78 _public member_ `FOnRenamed OnRenamed;`
- L81 _private member_ `TWeakObjectPtr<USkeletonModifier> WeakModifier;`

#### struct `FRefSkeletonTreeDelegates`  
`struct FRefSkeletonTreeDelegates`  
_L88-118_
- L92 _public prototype_ `FRefSkeletonTreeDelegates() = default;` — Avoid deprecation warnings when the struct is constructed or copied with default methods
- L93 _public prototype_ `FRefSkeletonTreeDelegates(const FRefSkeletonTreeDelegates&) = default;`
- L94 _public prototype_ `FRefSkeletonTreeDelegates(FRefSkeletonTreeDelegates&&) = default;`
- L95 _public prototype_ `FRefSkeletonTreeDelegates& operator=(const FRefSkeletonTreeDelegates&) = default;`
- L96 _public prototype_ `FRefSkeletonTreeDelegates& operator=(FRefSkeletonTreeDelegates&&) = default;`
- L99 _public member_ `FOnDragDetected OnDragDetected;`
- L100 _public member_ `FOnRefSkeletonTreeCanAcceptDrop OnCanAcceptDrop;`
- L101 _public member_ `FOnRefSkeletonTreeAcceptDrop OnAcceptDrop;`
- L102 _public member_ `FOnBoneRenamed OnBoneRenamed;`
- L104 _public member_ `FOnTextCommitted OnBoneNameCommitted;` — `UE_DEPRECATED(5.8, "Instead use OnBoneElementNameCommitted which is explicit about the renamed element")`
- L106 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FOnBoneElementNameCommitted, const FText& , ETextCommit::Type , TSharedRef<FBoneElement> ) FOnBoneElementNameCommitted OnBoneElementNameCommitted;`
- L110 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FOnGetRowWidget, FName) FOnGetRowWidget OnGetRowWidget;` — Tools can use these to extend the skeleton tree with extra commands or widgets
- L113 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnExtendCommandList, TSharedPtr<FUICommandList>) FOnExtendCommandList OnExtendCommandList;`
- L116 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnExtendContextMenu, FMenuBuilder&) FOnExtendContextMenu OnExtendContextMenu;`

#### class `SBoneItem`  
`class SBoneItem : public SCompoundWidget`  
_L120-158_
- inherits: `SCompoundWidget`
- L122 _private function_ `SLATE_BEGIN_ARGS(SBoneItem)`
- L123 _private prototype_ `SLATE_ARGUMENT(TWeakPtr<FBoneElement>, TreeElement) SLATE_ARGUMENT(TWeakObjectPtr<USkeletonModifier>, WeakModifier) SLATE_ARGUMENT(FRefSkeletonTreeDelegates, Delegates) SLATE_EVENT( FIsSelected, IsSelected ) SLATE_ATTRIBUTE(bool, IsReadOnly) SLATE_END_ARGS() virtual ~SBoneItem() override;`
- L133 _private prototype_ `void Construct(const FArguments& InArgs);` — Slate construction function
- L135 _private prototype_ `void HandleOnRenameRequested(const ReferenceSkeletonTreeLocals::EBoneRenameType InType);`
- L139 _private prototype_ `bool OnVerifyNameChanged(const FText& InText, FText& OutErrorMessage) const;`
- L140 _private prototype_ `void OnTextCommitted(const FText& Text, ETextCommit::Type TextCommitType);`
- L142 _private prototype_ `void OnEnterEditingMode();`
- L143 _private prototype_ `void OnExitEditingMode();`
- L145 _private prototype_ `static FSlateColor GetTextColor(FIsSelected InIsSelected);`
- L147 _private prototype_ `FText GetName() const;`
- L149 _private member_ `TWeakPtr<FBoneElement> WeakTreeElement;`
- L150 _private member_ `TWeakObjectPtr<USkeletonModifier> WeakModifier;`
- L151 _private member_ `TSharedPtr< SInlineEditableTextBlock > InlineWidget;`
- L153 _private member_ `bool bEditing = false;`
- L154 _private member_ `TOptional<ReferenceSkeletonTreeLocals::EBoneRenameType> OptRenameType;`
- L157 _private member_ `FRefSkeletonTreeDelegates::FOnBoneElementNameCommitted OnBoneElementNameCommitted;` — Delegate executed when the bone name was committed

#### class `FBoneItemDragDropOp`  
`class FBoneItemDragDropOp : public FDecoratedDragDropOp`  
_L160-172_
- inherits: `FDecoratedDragDropOp`
- L163 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FBoneItemDragDropOp, FDecoratedDragDropOp) static TSharedRef<FBoneItemDragDropOp> New(TArrayView<const TSharedPtr<FBoneElement>> InElements);`
- L168 _public prototype_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;` — FDecoratedDragDropOp interface
- L171 _public member_ `TArray< TWeakPtr<FBoneElement> > Elements;`

#### class `SReferenceSkeletonRow`  
`class SReferenceSkeletonRow : public SMultiColumnTableRow<TSharedPtr<FBoneElement>>`  
_L174-196_
- inherits: `SMultiColumnTableRow<TSharedPtr<FBoneElement>>`
- L177 _public function_ `SLATE_BEGIN_ARGS(SReferenceSkeletonRow)`
- L178 _public prototype_ `SLATE_ARGUMENT(TWeakObjectPtr<USkeletonModifier>, WeakModifier) SLATE_ARGUMENT(TSharedPtr<FBoneElement>, TreeElement) SLATE_ARGUMENT(FRefSkeletonTreeDelegates, Delegates) SLATE_ARGUMENT(bool, IsReadOnly) SLATE_END_ARGS()`
- L188 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;` — SMultiColumnTableRow interface
- L192 _private member_ `TWeakPtr<FBoneElement> WeakTreeElement;`
- L193 _private member_ `TWeakObjectPtr<USkeletonModifier> WeakModifier;`
- L194 _private member_ `FRefSkeletonTreeDelegates Delegates;`
- L195 _private member_ `bool bIsReadOnly = false;`

#### class `FReferenceSkeletonWidgetNotifier`  
`class FReferenceSkeletonWidgetNotifier: public ISkeletalMeshNotifier`  
_L200-208_
- inherits: `ISkeletalMeshNotifier`
- L203 _public prototype_ `FReferenceSkeletonWidgetNotifier(TSharedRef<SReferenceSkeletonTree> InTree);`
- L204 _public prototype_ `virtual void HandleNotification(const TArray<FName>& BoneNames, const ESkeletalMeshNotifyType InNotifyType) override;`
- L207 _private member_ `TWeakPtr<SReferenceSkeletonTree> Tree;`

#### class `SReferenceSkeletonTree`  
`class SReferenceSkeletonTree : public SCompoundWidget, public FEditorUndoClient`  
_L210-321_
- inherits: `SCompoundWidget,FEditorUndoClient`
- L212 _private typedef_ `using SReferenceSkeletonTreeView = ReferenceSkeletonTreeLocals::SReferenceSkeletonTreeView;`
- L215 _public function_ `SLATE_BEGIN_ARGS(SReferenceSkeletonTree) : _bIsReadOnly(false)`
- L218 _public prototype_ `SLATE_ARGUMENT(TWeakObjectPtr<USkeletonModifier>, Modifier) SLATE_ARGUMENT(FRefSkeletonTreeDelegates, Delegates) SLATE_ARGUMENT_DEPRECATED(bool, bIsReadOnly, 5.8, "This argument did not provide functionality and is now deprecated") SLATE_END_ARGS() SReferenceSkeletonTree();`
- L227 _public prototype_ `void Construct(const FArguments& InArgs);` — Slate construction function
- L229 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L230 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L233 _public prototype_ `void GetSelectedBoneNames(TArray<FName>& OutSelectedBoneNames) const;` — Selection
- L234 _public prototype_ `TArray<TSharedPtr<FBoneElement>> GetSelectedItems() const;`
- L235 _public prototype_ `bool HasSelectedItems() const;`
- L236 _public prototype_ `void SelectItemFromNames(const TArray<FName>& InBoneNames, bool bFrameSelection = false);`
- L238 _public prototype_ `TSharedPtr<ISkeletalMeshNotifier> GetNotifier();`
- L242 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — SWidget interface
- L245 _private prototype_ `void BindCommands();`
- L247 _private prototype_ `void AddItemToSelection(const TSharedPtr<FBoneElement>& InItem);`
- L248 _private prototype_ `void RemoveItemFromSelection(const TSharedPtr<FBoneElement>& InItem);`
- L249 _private prototype_ `void ReplaceItemInSelection(const FText& OldName, const FText& NewName);`
- L252 _private prototype_ `void HandleNewBone();` — Create, Rename, Delete, Parent bones
- L253 _private prototype_ `bool CanAddNewBone() const;`
- L254 _private prototype_ `void HandleRenameBone(const ReferenceSkeletonTreeLocals::EBoneRenameType InRenameType) const;`
- L255 _private prototype_ `bool CanRenameBone() const;`
- L256 _private prototype_ `void HandleDeleteBone();`
- L257 _private prototype_ `bool CanDeleteBone() const;`
- L258 _private prototype_ `void HandleUnParentBone();`
- L259 _private prototype_ `bool CanUnParentBone() const;`
- L262 _private prototype_ `void HandleCopyBones() const;` — Copy & Paste
- L263 _private prototype_ `bool CanCopyBones() const;`
- L264 _private prototype_ `void HandlePasteBones(const bool bUsingGlobalTransforms);`
- L265 _private prototype_ `bool CanPasteBones() const;`
- L266 _private prototype_ `void HandleDuplicateBones();`
- L267 _private prototype_ `bool CanDuplicateBones() const;`
- L270 _private prototype_ `void OnFilterTextChanged(const FText& SearchText);` — Filter
- L273 _private prototype_ `void RefreshTreeView(bool IsInitialSetup=false);` — Callbacks
- L274 _private prototype_ `void HandleGetChildrenForTree(TSharedPtr<FBoneElement> InItem, TArray<TSharedPtr<FBoneElement>>& OutChildren);`
- L275 _private prototype_ `void OnSelectionChanged(TSharedPtr<FBoneElement> InItem, ESelectInfo::Type InSelectInfo);`
- L277 _private prototype_ `TSharedRef< SWidget > CreateAddNewMenu();`
- L278 _private prototype_ `EVisibility GetAddNewButtonVisibility() const;`
- L279 _private prototype_ `TSharedPtr< SWidget > CreateContextMenu();`
- L281 _private prototype_ `void OnItemDoubleClicked(TSharedPtr<FBoneElement> InItem);`
- L282 _private prototype_ `void OnSetExpansionRecursive(TSharedPtr<FBoneElement> InItem, bool bShouldBeExpanded);`
- L283 _private prototype_ `void SetExpansionRecursive(TSharedPtr<FBoneElement> InElement, bool bTowardsParent, bool bShouldBeExpanded);`
- L286 _private prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — Delegates
- L287 _private prototype_ `TOptional<EItemDropZone> OnCanAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<FBoneElement> TargetItem);`
- L288 _private prototype_ `FReply OnAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<FBoneElement> TargetItem);`
- L289 _private prototype_ `void OnBoneRenamed(const FName InOldName, const FName InNewName) const;`
- L291 _private prototype_ `void OnBoneElementNameCommitted(const FText& InText, ETextCommit::Type InCommitType, TSharedRef<FBoneElement> BoneElement);`
- L294 _private member_ `TWeakObjectPtr<USkeletonModifier> Modifier;` — The modifier that actually does modifications on the reference skeleton
- L296 _private member_ `TSharedPtr<FReferenceSkeletonWidgetNotifier> Notifier;`
- L299 _private prototype_ `void BeginChange();` — undo
- L300 _private prototype_ `void EndChange();`
- L301 _private prototype_ `void CancelChange();`
- L302 _private member_ `TUniquePtr<ReferenceSkeletonTreeLocals::FSkeletonModifierChange> ActiveChange;`
- L305 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Commands
- L308 _private member_ `TSharedPtr<SReferenceSkeletonTreeView> TreeView;` — Tree view
- L309 _private member_ `TArray<TSharedPtr<FBoneElement>> RootElements;`
- L310 _private member_ `TArray<TSharedPtr<FBoneElement>> AllElements;`
- L313 _private member_ `TSharedPtr<FTextFilterExpressionEvaluator> TextFilter;` — filter
- L316 _private member_ `bool bIsReadOnly = false;`
- L318 _private member_ `FRefSkeletonTreeDelegates Delegates;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API MESHMODELINGTOOLSEDITORONLY_API`
- L23 _namespace_ `namespace ReferenceSkeletonTreeLocals`
- L74 _delegate_ `DECLARE_DELEGATE_OneParam(FOnRenameRequested, const ReferenceSkeletonTreeLocals::EBoneRenameType);`
- L77 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnRenamed, const FName, const FName);`
- L84 _typedef_ `using FOnRefSkeletonTreeCanAcceptDrop = STableRow<TSharedPtr<FBoneElement>>::FOnCanAcceptDrop;`
- L85 _typedef_ `using FOnRefSkeletonTreeAcceptDrop = STableRow<TSharedPtr<FBoneElement>>::FOnAcceptDrop;`
- L86 _typedef_ `using FOnBoneRenamed = FBoneElement::FOnRenamed;`
- L106 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnBoneElementNameCommitted, const FText& , ETextCommit::Type , TSharedRef<FBoneElement> ) FOnBoneElementNameCommitted OnBoneElementNameCommitted;`
- L110 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FOnGetRowWidget, FName) FOnGetRowWidget OnGetRowWidget;` — Tools can use these to extend the skeleton tree with extra commands or widgets
- L113 _delegate_ `DECLARE_DELEGATE_OneParam(FOnExtendCommandList, TSharedPtr<FUICommandList>) FOnExtendCommandList OnExtendCommandList;`
- L116 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnExtendContextMenu, FMenuBuilder&) FOnExtendContextMenu OnExtendContextMenu;`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingToolsEditorOnly/Public/SkeletalMesh/SkeletalMeshEditingInterface.h` (Public)


#### class `USkeletalMeshEditingInterface`  
`class USkeletalMeshEditingInterface : public UInterface`  
_L34-37_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `ISkeletalMeshEditingInterface`  
`class ISkeletalMeshEditingInterface`  
_L43-62_
- L48 _public prototype_ `TSharedPtr<ISkeletalMeshNotifier> GetNotifier();`
- L49 _public prototype_ `bool NeedsNotification() const;`
- L51 _public prototype_ `virtual bool CanModifySkeleton() const;`
- L52 _public prototype_ `virtual TSharedPtr<SWidget> GetCustomSkeletonTreeWidget(TSharedPtr<ISkeletalMeshEditorBinding> EditorBinding);`
- L56 _protected prototype_ `virtual void HandleSkeletalMeshModified(const TArray<FName>& BoneNames, const ESkeletalMeshNotifyType InNotifyType) = 0;`
- L59 _private member_ `TSharedPtr<FSkeletalMeshToolNotifier> Notifier;`

#### class `FSkeletalMeshToolNotifier`  
`class FSkeletalMeshToolNotifier: public ISkeletalMeshNotifier`  
_L68-76_
- inherits: `ISkeletalMeshNotifier`
- L71 _public prototype_ `FSkeletalMeshToolNotifier(TWeakInterfacePtr<ISkeletalMeshEditingInterface> InInterface);`
- L72 _public prototype_ `virtual void HandleNotification(const TArray<FName>& BoneNames, const ESkeletalMeshNotifyType InNotifyType) override;`
- L75 _protected member_ `TWeakInterfacePtr<ISkeletalMeshEditingInterface> Interface;`

#### struct `HBoneHitProxy`  
`struct HBoneHitProxy : public HHitProxy`  
_L82-96_
- inherits: `HHitProxy`
- L84 _public prototype_ `DECLARE_HIT_PROXY( ) int32 BoneIndex;`
- L87 _public member_ `FName BoneName;`
- L89 _public function_ `HBoneHitProxy(int32 InBoneIndex, FName InBoneName) : HHitProxy(HPP_Foreground) , BoneIndex(InBoneIndex) , BoneName(InBoneName)`
- L95 _public function_ `virtual EMouseCursor::Type GetMouseCursor() override`

#### class `USkeletalMeshGizmoContextObjectBase`  
`class USkeletalMeshGizmoContextObjectBase : public UObject`  
_L103-111_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- L108 _public prototype_ `virtual USkeletalMeshGizmoWrapperBase* GetNewWrapper(UInteractiveToolManager* InToolManager, UObject* Outer = nullptr, IGizmoStateTarget* InStateTarget = nullptr, const TScriptInterface<ITransformGizmoSource>& GizmoSource = nullptr) PURE_VIRTUAL(UGizmoContextObject::GetNewWrapper, return nullptr;);`

#### class `USkeletalMeshGizmoWrapperBase`  
`class USkeletalMeshGizmoWrapperBase : public UObject`  
_L118-142_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- L123 _protected typedef_ `using FGetTransform = TUniqueFunction<FTransform(void)>;`
- L124 _protected typedef_ `using FSetTransform = TUniqueFunction<void(const FTransform&)>;`
- L127 _public prototype_ `virtual void Initialize(const FTransform& InTransform = FTransform::Identity, const EToolContextCoordinateSystem& InTransformMode = EToolContextCoordinateSystem::Local) PURE_VIRTUAL(USkeletalMeshGizmoWrapperBase::Initialize, return;) virtual void HandleBoneTransform(FGetTransform GetTransformFunc, FSetTransform SetTransformFunc) PURE_VIRTUAL(USkeletalMeshGizmoWrapperBase::HandleBoneTransform, return;) virtual void Clear() PURE_VIRTUAL(USkeletalMeshGizmoWrapperBase::Clear, return;) virtual bool CanInteract() const PURE_VIRTUAL(USkeletalMeshGizmoWrapperBase::CanInteract, return false;) virtual bool IsGizmoHit(const FInputDeviceRay& PressPos) const PURE_VIRTUAL(USkeletalMeshGizmoWrapperBase::IsGizmoHit, return false;) UPROPERTY() TWeakObjectPtr<USceneComponent> Component;`

#### class `USkeletalMeshEditorContextObjectBase`  
`class USkeletalMeshEditorContextObjectBase : public UObject`  
_L149-172_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- L154 _public prototype_ `virtual EMeshLODIdentifier GetEditingLOD() PURE_VIRTUAL(USkeletalMeshEditorContextObjectBase::GetEditingLOD, return EMeshLODIdentifier::LOD0;) virtual void HideSkeleton() PURE_VIRTUAL(USkeletalMeshEditorContextObjectBase::HideSkeleton, return;) virtual void ShowSkeleton() PURE_VIRTUAL(USkeletalMeshEditorContextObjectBase::ShowSkeleton, return;) virtual void ToggleBoneManipulation(bool bEnable) PURE_VIRTUAL(USkeletalMeshEditorContextObjectBase::ToggleBoneManipulation, return;) virtual const TArray<FTransform>& GetComponentSpaceBoneTransforms(UToolTarget* InToolTarget) PURE_VIRTUAL(USkeletalMeshEditorContextObjectBase::GetComponentSpaceBoneTransforms, static TArray<FTransform> Dummy; return Dummy;) virtual FName GetEditingMorphTarget() PURE_VIRTUAL(USkeletalMeshEditorContextObjectBase::GetEditingMorphTarget, return NAME_None;);`
- L161 _public prototype_ `virtual TMap<FName, float> GetMorphTargetWeights() PURE_VIRTUAL(USkeletalMeshEditorContextObjectBase::GetMorphTargetWeights, return {};);`
- L162 _public prototype_ `virtual void NotifyMorphTargetEdited() PURE_VIRTUAL(USkeletalMeshEditorContextObjectBase::NotifyMorphTargetEdited, return;);`
- L166 _public function_ `virtual const UE::Geometry::FMeshPlanarSymmetry* GetBaseMeshSymmetry()` — Base-mesh symmetry for the editing asset (ref pose, deltas excluded), or nullptr if unavailable. Owned by the host; may be invalidated by edits that mutate base geometry.
- L168 _public function_ `virtual const TArray<int32>& GetIsolatedTriangles() const`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API MESHMODELINGTOOLSEDITORONLY_API`
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingToolsEditorOnly/Public/SkeletalMesh/SkeletalMeshModelingToolsEditorSettings.h` (Public)


#### class `USkeletalMeshModelingToolsEditorSettings`  
`class USkeletalMeshModelingToolsEditorSettings : public UObject`  
_L12-45_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- L19 _public function_ `void SetLocalRotationAxisLength(const float InLocalRotationAxisLength)` — Sets the local rotation axis length
- L22 _public function_ `float GetLocalRotationAxisLength() const` — Gets the local rotation axis length
- L25 _public function_ `void SetLocalRotationAxisThickness(const float InLocalRotationAxisThickness)` — Sets the local rotation axis thickness
- L28 _public function_ `float GetLocalRotationAxisThickness() const` — Gets the local rotation axis thickness
- L31 _public function_ `void SetShowAllLocalRotationAxes(const bool InShowAllLocalRotationAxes)` — Sets if all or only the selected local rotation axes are displayed
- L34 _public function_ `bool GetShowAllLocalRotationAxes() const` — Gets if all or only the selected local rotation axes are displayed
- L38 _private member_ `float LocalRotationAxisLength = 0.f;` — `UPROPERTY(config)`
- L41 _private member_ `float LocalRotationAxisThickness = 0.f;` — `UPROPERTY(config)`
- L44 _private member_ `bool bShowAllLocalRotationAxes = false;` — `UPROPERTY(config)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MESHMODELINGTOOLSEDITORONLY_API`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingToolsEditorOnly/Public/SkeletalMesh/SkeletalMeshToolsHelper.h` (Public)


#### struct `SkeletalMeshToolsHelper::FVertInfo`  
`struct FVertInfo`  
_L23-27_
- L25 _public member_ `int32 VertArrayIndex;`
- L26 _public member_ `int32 VertID;`

#### class `SkeletalMeshToolsHelper::FMeshMorphTargetChange`  
`class FMeshMorphTargetChange : public FMeshChange`  
_L63-75_
- inherits: `FMeshChange`
- desc: Records before/after morph-target vertex deltas for undo/redo. Shared between the brush-stroke commit path in the morph sculpt tool and the in-tool mirror action.
- L66 _public member_ `FName MorphTargetName;`
- L67 _public member_ `TArray<int32> Vertices;`
- L68 _public member_ `TArray<FVector> OldDeltas;`
- L69 _public member_ `TArray<FVector> NewDeltas;`
- L71 _public prototype_ `FMeshMorphTargetChange() = default;`
- L73 _public prototype_ `virtual FString ToString() const override;`
- L74 _public prototype_ `virtual void ApplyChangeToMesh(UE::Geometry::FDynamicMesh3* Mesh, bool bRevert) const override;`

#### struct `SkeletalMeshToolsHelper::FPoseChangeDetector`  
`struct FPoseChangeDetector`  
_L90-120_
- L108 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FNotifier, FPayload);`
- L110 _public prototype_ `void CheckPose(const TArray<FTransform>& ComponentSpaceTransforms, const TMap<FName,float>& MorphTargetWeights);`
- L111 _public prototype_ `FNotifier& GetNotifier();`
- L114 _protected member_ `FNotifier Notifier;`
- L116 _protected member_ `TArray<FTransform> PreviousComponentSpaceTransforms;`
- L117 _protected member_ `TMap<FName, float> PreviousMorphTargetWeights;`
- L119 _protected member_ `EState State = PoseStoppedChanging;`

#### enum `SkeletalMeshToolsHelper::FPoseChangeDetector::EState`  
`enum EState`  
_L92-97_
- L94 _public enumerator_ `PoseJustChanged`
- L95 _public enumerator_ `PoseChanged`
- L96 _public enumerator_ `PoseStoppedChanging`

#### struct `SkeletalMeshToolsHelper::FPoseChangeDetector::FPayload`  
`struct FPayload`  
_L99-106_
- L101 _public member_ `EState CurrentState;`
- L102 _public member_ `const TArray<FTransform>& ComponentSpaceTransforms;`
- L103 _public member_ `const TMap<FName, float>& MorphTargetWeights;`
- L104 _public member_ `const TArray<FTransform>& PreviousComponentSpaceTransforms;`
- L105 _public member_ `const TMap<FName, float>& PreviousMorphTargetWeights;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MESHMODELINGTOOLSEDITORONLY_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Geometry` (scope `UE`)
- L19 _namespace_ `namespace SkeletalMeshToolsHelper`
- L31 _prototype_ `void SetupPreviewTangentMode(UDynamicMeshComponent* Component);` (scope `SkeletalMeshToolsHelper`) — Sets tangent mode for the provided preview mesh based on if there is a valid tangent overlay.
- L36 _prototype_ `void GetUnposedMesh( TFunctionRef<void(FVertInfo, const FVector&)> WriteFunc, TFunctionRef<FVector(int32)> GetPosedVertexFunc, const FDynamicMesh3& SourceMesh, const TArray<FMatrix>& BoneMatrices, FName SkinWeightProfile, const TMap<FName, float>& MorphTargetWeights, const TArray<int32>& VertArray = {} );` (scope `SkeletalMeshToolsHelper`) — Unposes a mesh: for each SourceMesh vertex (or those in VertArray), reads the posed position via GetPosedVertexFunc, removes skin transform, removes morph contributions in MorphTargetWeights using deltas from SourceMesh, and emits the resulting ref-pose position via WriteFunc.
- L47 _prototype_ `void GetPosedMesh( TFunctionRef<void(FVertInfo, const FVector&)> WriteFunc, const FDynamicMesh3& SourceMesh, const TArray<FMatrix>& BoneMatrices, FName SkinWeightProfile, const TMap<FName, float>& MorphTargetWeights, const TArray<int32>& VertArray = {} );` (scope `SkeletalMeshToolsHelper`)
- L56 _prototype_ `TArray<FMatrix> ComputeBoneMatrices( const TArray<FTransform>& ComponentSpaceTransformsRefPose, const TArray<FTransform>& ComponentSpaceTransforms );` (scope `SkeletalMeshToolsHelper`)
- L84 _prototype_ `void MirrorMorphTargetOnMesh( UE::Geometry::FDynamicMesh3& Mesh, FName MorphTargetName, const UE::Geometry::FMeshPlanarSymmetry& Symmetry, FMeshMorphTargetChange* OutDeltaChange = nullptr);` (scope `SkeletalMeshToolsHelper`) — Mirror MorphTargetName's deltas on Mesh across Symmetry's plane in place. Positive side is the source; negative side receives the reflected delta. On-plane vertices have their delta snapped to the plane. Pass OutDeltaChange to capture the per-vertex before/after for an undo record. Pass nullptr when the caller has its own change tracking (e.g. USkeletalMeshBackedDynamicMeshComponent's FChangeScope + MorphTargetChangeTracker).
- L108 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FNotifier, FPayload);`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingToolsEditorOnly/Public/SkeletalMesh/SkeletonEditingTool.h` (Public)


#### class `SkeletonEditingTool::FRefSkeletonChange`  
`class FRefSkeletonChange : public FToolCommandChange`  
_L42-62_
- inherits: `FToolCommandChange`
- desc: A wrapper change class that stores a reference skeleton and the bones' indexes trackers to be used for undo/redo.
- L45 _public prototype_ `FRefSkeletonChange(const USkeletonEditingTool* InTool);`
- L47 _public function_ `virtual FString ToString() const override`
- L52 _public prototype_ `virtual void Apply(UObject* Object) override;`
- L53 _public prototype_ `virtual void Revert(UObject* Object) override;`
- L55 _public prototype_ `void StoreSkeleton(const USkeletonEditingTool* InTool);`
- L58 _private member_ `FReferenceSkeleton PreChangeSkeleton;`
- L59 _private member_ `TArray<int32> PreBoneTracker;`
- L60 _private member_ `FReferenceSkeleton PostChangeSkeleton;`
- L61 _private member_ `TArray<int32> PostBoneTracker;`

#### class `FSkeletonEditingToolCommands`  
`class FSkeletonEditingToolCommands : public TCommands<FSkeletonEditingToolCommands>`  
_L66-96_
- inherits: `TCommands<FSkeletonEditingToolCommands>`
- L69 _public prototype_ `FSkeletonEditingToolCommands();`
- L71 _public prototype_ `virtual void RegisterCommands() override;`
- L74 _public member_ `TSharedPtr<FUICommandInfo> NewBone;` — Skeleton Editing commands
- L75 _public member_ `TSharedPtr<FUICommandInfo> RemoveBone;`
- L76 _public member_ `TSharedPtr<FUICommandInfo> UnParentBone;`
- L77 _public member_ `TSharedPtr<FUICommandInfo> RenameBone;`
- L78 _public member_ `TSharedPtr<FUICommandInfo> SearchAndReplace;`
- L79 _public member_ `TSharedPtr<FUICommandInfo> AddPrefix;`
- L80 _public member_ `TSharedPtr<FUICommandInfo> AddSuffix;`
- L83 _public member_ `TSharedPtr<FUICommandInfo> CopyBones;` — Copy & Paste commands
- L84 _public member_ `TSharedPtr<FUICommandInfo> CopyBoneTransforms;`
- L85 _public member_ `TSharedPtr<FUICommandInfo> PasteBonesLocal;`
- L86 _public member_ `TSharedPtr<FUICommandInfo> PasteBonesGlobal;`
- L87 _public member_ `TSharedPtr<FUICommandInfo> PasteBoneTransformsLocal;`
- L88 _public member_ `TSharedPtr<FUICommandInfo> PasteBoneTransformsGlobal;`
- L90 _public member_ `TSharedPtr<FUICommandInfo> DuplicateBones;`
- L92 _public member_ `TSharedPtr<FUICommandInfo> ImportBonesFromAssignedSkeleton;`
- L95 _public member_ `TSharedPtr<FUICommandInfo> PasteBones;` — `UE_DEPRECATED(5.8, "Instead use PasteBonesLocal")`

#### class `USkeletonEditingToolBuilder`  
`class USkeletonEditingToolBuilder : public UInteractiveToolWithToolTargetsBuilder`  
_L103-115_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolWithToolTargetsBuilder`
- L109 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;` — UInteractiveToolBuilder overrides
- L110 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`
- L114 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;` — UInteractiveToolWithToolTargetsBuilder overrides

#### enum `EEditingOperation`  
`enum class EEditingOperation : uint8`  
_L122-131_
- reflection: `UENUM()`
- L124 _public enumerator_ `Select` — Selecting bones in the viewport.
- L125 _public enumerator_ `Create` — Creating bones in the viewport.
- L126 _public enumerator_ `Remove` — Removing current selection.
- L127 _public enumerator_ `Transform` — Transforming bones in the viewport or thru the details panel.
- L128 _public enumerator_ `Parent` — Parenting bones in the viewport.
- L129 _public enumerator_ `Rename` — Renaming bones thru the details panel.
- L130 _public enumerator_ `Mirror` — Mirroring bones thru the details panel.

#### class `USkeletonEditingTool`  
`class USkeletonEditingTool : public USingleSelectionTool, public IClickDragBehaviorTarget, public ISkeletalMeshEditingInterface, public ISkeletalMeshGeometryIsolationAwareTool, public IInteractiveToolManageGeometrySelectionAPI, public IHotkeyHintProvider`  
_L139-384_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionTool,IClickDragBehaviorTarget,ISkeletalMeshEditingInterface,ISkeletalMeshGeometryIsolationAwareTool,IInteractiveToolManageGeometrySelectionAPI,IHotkeyHintProvider`
- L150 _public member_ `static constexpr const TCHAR* ActionCommandsContextName = TEXT("Ske`
- L152 _public prototype_ `void Init(const FToolBuilderState& InSceneState);`
- L155 _public prototype_ `virtual void Setup() override;` — UInteractiveTool overrides
- L156 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L158 _public prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI) override;`
- L159 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L161 _public function_ `virtual bool HasCancel() const override`
- L162 _public function_ `virtual bool HasAccept() const override`
- L163 _public function_ `virtual bool CanAccept() const override`
- L165 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L168 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& InPressPos) override;` — ICLickDragBehaviorTarget overrides
- L170 _public prototype_ `virtual void OnClickPress(const FInputDeviceRay& InPressPos) override;`
- L171 _public prototype_ `virtual void OnClickDrag(const FInputDeviceRay& InDragPos) override;`
- L172 _public prototype_ `virtual void OnClickRelease(const FInputDeviceRay& InReleasePos) override;`
- L173 _public prototype_ `virtual void OnTerminateDragSequence() override;`
- L175 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L178 _public prototype_ `virtual FBox GetWorldSpaceFocusBox() override;` — IInteractiveToolCameraFocusAPI overrides
- L181 _public prototype_ `void MirrorBones();` — Modifier functions
- L182 _public prototype_ `void RenameBones();`
- L183 _public prototype_ `void MoveBones();`
- L184 _public prototype_ `void OrientBones();`
- L185 _public prototype_ `void RemoveBones();`
- L186 _public prototype_ `void UnParentBones();`
- L187 _public prototype_ `void SnapBoneToComponentSelection(const bool bCreate);`
- L189 _public prototype_ `const TArray<FName>& GetSelection() const;`
- L191 _public prototype_ `const FTransform& GetTransform(const FName InBoneName, const bool bWorld) const;`
- L192 _public prototype_ `void SetTransforms(const TArray<FName>& InBones, const TArray<FTransform>& InTransforms, const bool bWorld) const;`
- L195 _public prototype_ `virtual void OnUpdateModifierState(int ModifierID, bool bIsOn) override;` — IModifierToggleBehaviorTarget overrides
- L198 _public prototype_ `virtual bool CanModifySkeleton() const override;` — ISkeletalMeshEditingInterface overrides
- L199 _public prototype_ `virtual TSharedPtr<SWidget> GetCustomSkeletonTreeWidget(TSharedPtr<ISkeletalMeshEditorBinding> EditorBinding) override;`
- L202 _public prototype_ `EEditingOperation GetOperation() const;`
- L203 _public prototype_ `void SetOperation(const EEditingOperation InOperation, const bool bUpdateGizmo = true);`
- L205 _public prototype_ `bool HasSelectedComponent() const;`
- L208 _public prototype_ `virtual bool IsInputIsolationValidOnOutput() const override;` — ISkeletalMeshGeometryIsolationAwareTool
- L211 _public prototype_ `virtual bool IsInputSelectionValidOnOutput() override;` — IInteractiveToolManageGeometrySelectionAPI
- L214 _public prototype_ `virtual void GetHotkeyHints(TArray<FHotkeyHint>& OutHints) const override;` — IHotkeyHintProvider
- L218 _protected prototype_ `virtual void RegisterActions(FInteractiveToolActionSet& ActionSet) override;` — UInteractiveTool overrides
- L221 _protected prototype_ `virtual void HandleSkeletalMeshModified(const TArray<FName>& BoneNames, const ESkeletalMeshNotifyType InNotifyType) override;` — ISkeletalMeshEditingInterface overrides
- L224 _protected prototype_ `virtual TScriptInterface<ITransformGizmoSource> BuildTransformSource();` — Build a transform source to override the mode tools functionality
- L227 _protected prototype_ `void CreateNewBone();` — Modifier functions
- L228 _protected prototype_ `void ParentBones(const FName& InParentName);`
- L230 _protected prototype_ `static TOptional<FName> GetBoneName(HHitProxy* InHitProxy);`
- L235 _public member_ `TObjectPtr<USkeletonEditingProperties> Properties;` — `UPROPERTY()`
- L238 _public member_ `TObjectPtr<UProjectionProperties> ProjectionProperties;` — `UPROPERTY()`
- L241 _public member_ `TObjectPtr<UMirroringProperties> MirroringProperties;` — `UPROPERTY()`
- L244 _public member_ `TObjectPtr<UOrientingProperties> OrientingProperties;` — `UPROPERTY()`
- L247 _public member_ `TObjectPtr<UPolygonSelectionMechanic> SelectionMechanic;` — `UPROPERTY()`
- L252 _protected member_ `TObjectPtr<USkeletonModifier> Modifier = nullptr;` — `UPROPERTY()`
- L255 _protected member_ `TObjectPtr<USingleClickInputBehavior> LeftClickBehavior = nullptr;` — `UPROPERTY()`
- L258 _protected member_ `TObjectPtr<UPreviewMesh> PreviewMesh = nullptr;` — `UPROPERTY()`
- L261 _protected member_ `TWeakObjectPtr<UWorld> TargetWorld = nullptr;` — `UPROPERTY()`
- L264 _protected member_ `TWeakObjectPtr<UGizmoViewContext> ViewContext = nullptr;` — `UPROPERTY()`
- L267 _protected member_ `EEditingOperation Operation = EEditingOperation::Select;` — `UPROPERTY()`
- L271 _protected member_ `TWeakObjectPtr<USkeletalMeshGizmoContextObjectBase> GizmoContext = nullptr;` — `UPROPERTY()` — gizmo
- L274 _protected member_ `TObjectPtr<USkeletalMeshGizmoWrapperBase> GizmoWrapper = nullptr;` — `UPROPERTY()`
- L277 _protected member_ `TWeakObjectPtr<USkeletalMeshEditorContextObjectBase> EditorContext = nullptr;` — `UPROPERTY()`
- L279 _protected prototype_ `void UpdateGizmo() const;`
- L282 _protected prototype_ `void BeginChange();` — ref skeleton transactions
- L283 _protected prototype_ `void EndChange();`
- L284 _protected prototype_ `void CancelChange();`
- L285 _protected member_ `TUniquePtr<SkeletonEditingTool::FRefSkeletonChange> ActiveChange;`
- L291 _private prototype_ `void HandleCopyBoneTransforms() const;` — Copies bone transforms to clipboard
- L294 _private prototype_ `bool CanCopyBoneTransforms() const;` — Returns true if bone transforms can be copied to the clipboard
- L297 _private prototype_ `void HandlePasteBoneTransforms(const bool bUsingGlobalTransforms);` — Pastes bone transforms from the clipboard to selected bones
- L300 _private prototype_ `bool CanPasteBoneTransforms() const;` — Returns true if bone transforms can be pasted from the clipboard to selected bones
- L303 _private prototype_ `void HandleImportBonesFromAssignedSkeleton();` — Merges bones from the assigned USkeleton asset into the mesh skeleton currently being edited.
- L306 _private prototype_ `bool CanImportBonesFromAssignedSkeleton() const;` — Returns true if the target has an assigned USkeleton asset that can be merged in.
- L308 _private prototype_ `TArray<int32> GetSelectedBoneIndexes() const;`
- L316 _private prototype_ `FRIEND_ENUM_CLASS_FLAGS(USkeletonEditingTool::EBoneSelectionMode)`
- L321 _private member_ `static constexpr int ToggleSelectionModifier = 2;`
- L322 _private member_ `EBoneSelectionMode SelectionMode = EBoneSelectionMode::Single;`
- L324 _private member_ `TArray<FName> Selection;`
- L326 _private prototype_ `void SelectBone(const FName& InBoneName);`
- L327 _private prototype_ `FName GetCurrentBone() const;`
- L329 _private prototype_ `void NormalizeSelection();`
- L332 _private prototype_ `void SetupModifier(ISkeletonCommitter* InCommitter);` — setup
- L333 _private prototype_ `void SetupPreviewMesh();`
- L334 _private prototype_ `void SetupProperties();`
- L335 _private prototype_ `void SetupBehaviors();`
- L336 _private prototype_ `void SetupGizmo(USceneComponent* InComponent);`
- L337 _private prototype_ `void SetupWatchers();`
- L338 _private prototype_ `void SetupComponentsSelection();`
- L341 _private prototype_ `void RegisterCreateAction(FInteractiveToolActionSet& InOutActionSet, const int32 InActionId);` — actions
- L342 _private prototype_ `void RegisterDeleteAction(FInteractiveToolActionSet& InOutActionSet, const int32 InActionId);`
- L343 _private prototype_ `void RegisterSelectAction(FInteractiveToolActionSet& InOutActionSet, const int32 InActionId);`
- L344 _private prototype_ `void RegisterParentAction(FInteractiveToolActionSet& InOutActionSet, const int32 InActionId);`
- L345 _private prototype_ `void RegisterUnParentAction(FInteractiveToolActionSet& InOutActionSet, const int32 InActionId);`
- L346 _private prototype_ `void RegisterCopyAction(FInteractiveToolActionSet& InOutActionSet, const int32 InActionId);`
- L347 _private prototype_ `void RegisterPasteBonesLocalAction(FInteractiveToolActionSet& InOutActionSet, const int32 InActionId);`
- L348 _private prototype_ `void RegisterPasteBonesGlobalAction(FInteractiveToolActionSet& InOutActionSet, const int32 InActionId);`
- L349 _private prototype_ `void RegisterCopyBoneTransformsAction(FInteractiveToolActionSet& InOutActionSet, const int32 InActionId);`
- L350 _private prototype_ `void RegisterPasteBoneTransformsLocalAction(FInteractiveToolActionSet& InOutActionSet, const int32 InActionId);`
- L351 _private prototype_ `void RegisterPasteBoneTransformsGlobalAction(FInteractiveToolActionSet& InOutActionSet, const int32 InActionId);`
- L352 _private prototype_ `void RegisterDuplicateAction(FInteractiveToolActionSet& InOutActionSet, const int32 InActionId);`
- L353 _private prototype_ `void RegisterSelectComponentsAction(FInteractiveToolActionSet& InOutActionSet, const int32 InActionId);`
- L354 _private prototype_ `void RegisterSelectionFilterCyclingAction(FInteractiveToolActionSet& InOutActionSet, const int32 InActionId);`
- L355 _private prototype_ `void RegisterSnapAction(FInteractiveToolActionSet& InOutActionSet, const int32 InActionId);`
- L357 _private prototype_ `void PerformPasteBonesAction(const bool bUsingGlobalTransforms);`
- L358 _private prototype_ `void PerformPasteBoneTransformsAction(const bool bUsingGlobalTransforms);`
- L360 _private prototype_ `TArray<int32> GetSelectedComponents() const;`
- L362 _private prototype_ `FTransform ComputeTransformFromComponents(const TArray<int32>& InIDs) const;`
- L364 _private member_ `TValueWatcher<TArray<FName>> SelectionWatcher;`
- L365 _private member_ `TValueWatcher<EToolContextCoordinateSystem> CoordinateSystemWatcher;`
- L367 _private member_ `int32 ParentIndex = INDEX_NONE;`
- L369 _private member_ `TFunction<void()> PendingClickFunction;`
- L370 _private member_ `TFunction<void()> PendingReleaseFunction;`
- L371 _private member_ `TFunction<void()> DeferredFocusFunction;`
- L373 _private member_ `TUniquePtr<UE::Geometry::FTriangleGroupTopology> Topology = nullptr;`
- L376 _private member_ `bool bDeferUntilFocused = false;` — Defer pending function on tick to allow other external notification to be handled.
- L378 _private member_ `TWeakObjectPtr<USkeletalMesh> WeakMesh = nullptr;`
- L380 _private member_ `TUniquePtr<FSkeletalMeshNotifierBindScope> SkeletonTreeNotifierBindScope;`
- L383 _private member_ `TSharedPtr<SReferenceSkeletonTree> SkeletonTree;` — The skeleton tree this tool displays

#### enum `USkeletonEditingTool::EBoneSelectionMode`  
`enum class EBoneSelectionMode : uint8`  
_L310-315_
- L312 _public enumerator_ `Single = 0`
- L313 _public enumerator_ `Additive = 1 << 0`
- L314 _public enumerator_ `Toggle = 1 << 1`

#### class `USkeletonEditingProperties`  
`class USkeletonEditingProperties : public UInteractiveToolPropertySet`  
_L393-416_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L397 _public prototype_ `void Initialize(USkeletonEditingTool* ParentToolIn);`
- L400 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category = "Details")`
- L403 _public member_ `FTransform Transform;` — `UPROPERTY()`
- L406 _public member_ `bool bUpdateChildren = false;` — `UPROPERTY(EditAnywhere, Category = "Details")`
- L409 _public member_ `bool bEnableComponentSelection = false;` — `UPROPERTY()`
- L412 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent) override;`
- L415 _public member_ `TWeakObjectPtr<USkeletonEditingTool> ParentTool = nullptr;`

#### enum `EProjectionType`  
`enum class EProjectionType : uint8`  
_L423-428_
- reflection: `UENUM()`
- L425 _public enumerator_ `CameraPlane` — The camera plane is used as the projection plane
- L426 _public enumerator_ `OnMesh` — The mesh surface is used for projection
- L427 _public enumerator_ `WithinMesh` — The mesh volume is used for projection

#### class `UProjectionProperties`  
`class UProjectionProperties: public UInteractiveToolPropertySet`  
_L435-460_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L440 _public prototype_ `void Initialize(USkeletonEditingTool* ParentToolIn, TObjectPtr<UPreviewMesh> PreviewMesh);`
- L442 _public prototype_ `void UpdatePlane(const UGizmoViewContext& InViewContext, const FVector& InOrigin);`
- L443 _public prototype_ `bool GetProjectionPoint(const FInputDeviceRay& InRay, FVector& OutHitPoint) const;`
- L446 _public member_ `EProjectionType ProjectionType = EProjectionType::WithinMesh;` — `UPROPERTY(EditAnywhere, Category = "Project")`
- L448 _public member_ `FViewCameraState CameraState;`
- L450 _public member_ `TWeakObjectPtr<USkeletonEditingTool> ParentTool = nullptr;`
- L453 _private member_ `TWeakObjectPtr<UPreviewMesh> PreviewMesh = nullptr;`
- L456 _private member_ `FVector PlaneOrigin = FVector::ZeroVector;` — `UPROPERTY()`
- L459 _private member_ `FVector PlaneNormal = FVector::ZAxisVector;` — `UPROPERTY()`

#### class `UMirroringProperties`  
`class UMirroringProperties: public UInteractiveToolPropertySet`  
_L467-480_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L472 _public prototype_ `void Initialize(USkeletonEditingTool* ParentToolIn);`
- L474 _public prototype_ `void MirrorBones();`
- L477 _public member_ `FMirrorOptions Options;` — `UPROPERTY(EditAnywhere, Category = "Mirror")`
- L479 _public member_ `TWeakObjectPtr<USkeletonEditingTool> ParentTool = nullptr;`

#### class `UOrientingProperties`  
`class UOrientingProperties: public UInteractiveToolPropertySet`  
_L487-507_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L492 _public prototype_ `void Initialize(USkeletonEditingTool* ParentToolIn);`
- L494 _public prototype_ `void OrientBones();`
- L497 _public member_ `bool bAutoOrient = false;` — `UPROPERTY(EditAnywhere, Category = "Orient")`
- L500 _public member_ `FOrientOptions Options;` — `UPROPERTY(EditAnywhere, Category = "Orient")`
- L503 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent) override;`
- L506 _public member_ `TWeakObjectPtr<USkeletonEditingTool> ParentTool = nullptr;`

#### Free symbols / members of external scopes

- L23 _macro_ `#define UE_API MESHMODELINGTOOLSEDITORONLY_API`
- L36 _namespace_ `namespace SkeletonEditingTool`
- L386 _prototype_ `ENUM_CLASS_FLAGS(USkeletonEditingTool::EBoneSelectionMode);`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingToolsEditorOnly/Public/SkeletalMesh/SkeletonTransformProxy.h` (Public)


#### class `USkeletonTransformProxy`  
`class USkeletonTransformProxy : public UTransformProxy`  
_L18-38_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UTransformProxy`
- L24 _public prototype_ `void Initialize(const FTransform& InTransform, const EToolContextCoordinateSystem& InTransformMode);`
- L26 _public prototype_ `bool IsValid() const;`
- L29 _public prototype_ `virtual FTransform GetTransform() const override;` — UTransformProxy overrides
- L32 _public member_ `EToolContextCoordinateSystem TransformMode = EToolContextCoordinateSystem::Local;` — `UPROPERTY()`
- L36 _protected prototype_ `virtual void UpdateSharedTransform() override;` — UTransformProxy overrides
- L37 _protected prototype_ `virtual void UpdateObjects() override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MESHMODELINGTOOLSEDITORONLY_API`

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingToolsEditorOnly/Public/SkeletalMesh/SkinWeightsBindingTool.h` (Public)


#### class `USkinWeightsBindingToolBuilder`  
`class USkinWeightsBindingToolBuilder : public UMultiSelectionMeshEditingToolBuilder`  
_L34-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingToolBuilder`
- L38 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L39 _public prototype_ `virtual UMultiSelectionMeshEditingTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L42 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### enum `ESkinWeightsBindType`  
`enum class ESkinWeightsBindType : uint8`  
_L47-51_
- reflection: `UENUM()`
- desc: A mirror of UE::Geometry::ESkinBindingType
- L49 _public enumerator_ `DirectDistance = 0 UMETA(DisplayName = "Direct Distance")`
- L50 _public enumerator_ `GeodesicVoxel = 1 UMETA(DisplayName = "Geodesic Voxel")`

#### class `USkinWeightsBindingToolProperties`  
`class USkinWeightsBindingToolProperties : public UInteractiveToolPropertySet`  
_L54-84_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L60 _public member_ `FName CurrentBone = NAME_None;` — `UPROPERTY()`
- L64 _public member_ `bool ConfirmCurrentSettings = false;` — `UPROPERTY(EditAnywhere, Category = Tool, meta=(TransientToolProperty))` — Explicit confirmation is required before the tool commits new skin weights
- L68 _public member_ `ESkinWeightsBindType BindingType = ESkinWeightsBindType::DirectDistance;` — `UPROPERTY(EditAnywhere, Category = Binding)` — Binding type to use
- L72 _public member_ `float Stiffness = 0.2f;` — `UPROPERTY(EditAnywhere, Category = Binding, meta=(ClampMin="0.0", ClampMax="1.0", UIMin="0.0", UIMax="1.0"))` — Stiffness of binding. Lower values allow more distant bones to contribute more
- L76 _public member_ `int32 MaxInfluences = 5;` — `UPROPERTY(EditAnywhere, Category = Binding, meta=(ClampMin="1", UIMin="1", UIMax="10"))` — Maximum bones that will influence each vertex
- L80 _public member_ `int32 VoxelResolution = 128;` — `UPROPERTY(EditAnywhere, Category = Binding, meta=(EditCondition = "BindingType == ESkinWeightsBindType::GeodesicVoxel", ClampMin="1", UIMin="8", UIMax="1024"))` — The resolution of the voxel grid if doing geodesic voxel binding
- L83 _public member_ `bool bDebugDraw = false;` — `UPROPERTY(EditAnywhere, Category = Debug)`

#### class `USkinWeightsBindingTool`  
`class USkinWeightsBindingTool : public UMultiSelectionMeshEditingTool, public UE::Geometry::IDynamicMeshOperatorFactory, public ISkeletalMeshEditingInterface, public ISkeletalMeshGeometryIsolationAwareTool, public IInteractiveToolManageGeometrySelectionAPI`  
_L90-155_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMultiSelectionMeshEditingTool,UE::Geometry::IDynamicMeshOperatorFactory,ISkeletalMeshEditingInterface,ISkeletalMeshGeometryIsolationAwareTool,IInteractiveToolManageGeometrySelectionAPI`
- L100 _public prototype_ `USkinWeightsBindingTool();`
- L103 _public prototype_ `void Init(const FToolBuilderState& InSceneState);`
- L105 _public prototype_ `virtual void Setup() override;`
- L106 _public prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L108 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L109 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L111 _public function_ `virtual bool HasCancel() const override`
- L112 _public function_ `virtual bool HasAccept() const override`
- L113 _public prototype_ `virtual bool CanAccept() const override;`
- L116 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory API
- L119 _public prototype_ `virtual bool IsInputIsolationValidOnOutput() const override;` — ISkeletalMeshGeometryIsolationAwareTool
- L122 _public prototype_ `virtual bool IsInputSelectionValidOnOutput() override;` — IInteractiveToolManageGeometrySelectionAPI
- L125 _public member_ `TObjectPtr<USkinWeightsBindingToolProperties> Properties = nullptr;` — `UPROPERTY()`
- L128 _public member_ `TObjectPtr<UMeshOpPreviewWithBackgroundCompute> Preview = nullptr;` — `UPROPERTY()`
- L131 _protected member_ `TSharedPtr<UE::Geometry::FOccupancyGrid3> Occupancy;`
- L133 _protected member_ `TSharedPtr<UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> OriginalMesh;`
- L135 _protected member_ `TUniquePtr<FMeshDescription> EditedMeshDescription;`
- L137 _protected member_ `FReferenceSkeleton ReferenceSkeleton;`
- L139 _protected prototype_ `void GenerateAsset(const FDynamicMeshOpResult& Result);`
- L141 _protected prototype_ `static FVector4f WeightToColor(float Value);`
- L142 _protected prototype_ `void UpdateVisualization(bool bInForce = false);`
- L145 _protected member_ `TWeakObjectPtr<USkeletalMeshEditorContextObjectBase> EditorContext = nullptr;` — `UPROPERTY()`
- L148 _protected prototype_ `bool UpdateSkinWeightsFromDynamicMesh(UE::Geometry::FDynamicMesh3& InResultMesh) const;` — updates the skin weights using the operator's result
- L151 _protected prototype_ `virtual void HandleSkeletalMeshModified(const TArray<FName>& InBoneNames, const ESkeletalMeshNotifyType InNotifyType) override;` — ISkeletalMeshEditingInterface
- L154 _protected member_ `TFunction<void()> PendingUpdateFunction;` — UCLASS(MinimalAPI) class USkinWeightsBindingTool : public UMultiSelectionMeshEditingTool, public UE::Geometry::IDynamicMeshOperatorFactory, public ISkeletalMeshEditingInterface, public ISkeletalMeshGeometryIsolationAwareTool, public IInteractiveToolManageGeometrySelectionAPI { GENERATED_BODY() public: UE_API USkinWeightsBindingTool(); UE_API virtual ~USkinWeightsBindingTool() override; UE_API void Init(const FToolBuilderState& InSceneState); UE_API virtual void Setup() override; UE_API virtual void OnShutdown(EToolShutdownType ShutdownType) override; UE_API virtual void OnTick(float DeltaTime) override; UE_API virtual void Render(IToolsContextRenderAPI* RenderAPI) override; virtual bool HasCancel() const override { return true; } virtual bool HasAccept() const override { return true; } UE_API virtual bool CanAccept() const override; IDynamicMeshOperatorFactory API UE_API virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override; ISkeletalMeshGeometryIsolationAwareTool UE_API virtual bool IsInputIsolationValidOnOutput() const override; IInteractiveToolManageGeometrySelectionAPI UE_API virtual bool IsInputSelectionValidOnOutput() override; UPROPERTY() TObjectPtr<USkinWeightsBindingToolProperties> Properties = nullptr; UPROPERTY() TObjectPtr<UMeshOpPreviewWithBackgroundCompute> Preview = nullptr; protected: TSharedPtr<UE::Geometry::FOccupancyGrid3> Occupancy; TSharedPtr<UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> OriginalMesh; TUniquePtr<FMeshDescri

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API MESHMODELINGTOOLSEDITORONLY_API`
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingToolsEditorOnly/Public/SkeletalMesh/SkinWeightsPaintTool.h` (Public)


#### enum `EWeightEditMode`  
`enum class EWeightEditMode : uint8`  
_L59-64_
- reflection: `UENUM()`
- desc: weight edit mode
- L61 _public enumerator_ `Brush`
- L62 _public enumerator_ `Mesh`
- L63 _public enumerator_ `Bones`

#### enum `EMeshTransferOption`  
`enum class EMeshTransferOption : uint8`  
_L68-72_
- reflection: `UENUM()`
- desc: weight transfers happen between a source and target
- L70 _public enumerator_ `Source`
- L71 _public enumerator_ `Target`

#### enum `EWeightColorMode`  
`enum class EWeightColorMode : uint8`  
_L76-82_
- reflection: `UENUM()`
- desc: weight color mode
- L78 _public enumerator_ `Greyscale`
- L79 _public enumerator_ `Ramp`
- L80 _public enumerator_ `BoneColors`
- L81 _public enumerator_ `FullMaterial`

#### enum `EWeightBrushFalloffMode`  
`enum class EWeightBrushFalloffMode : uint8`  
_L86-90_
- reflection: `UENUM()`
- desc: brush falloff mode
- L88 _public enumerator_ `Surface`
- L89 _public enumerator_ `Volume`

#### enum `EWeightEditOperation`  
`enum class EWeightEditOperation : uint8`  
_L94-101_
- reflection: `UENUM()`
- desc: operation type when editing weights
- L96 _public enumerator_ `Add`
- L97 _public enumerator_ `Replace`
- L98 _public enumerator_ `Multiply`
- L99 _public enumerator_ `Relax`
- L100 _public enumerator_ `RelativeScale`

#### enum `EMirrorDirection`  
`enum class EMirrorDirection : uint8`  
_L105-109_
- reflection: `UENUM()`
- desc: mirror direction mode
- L107 _public enumerator_ `PositiveToNegative`
- L108 _public enumerator_ `NegativeToPositive`

#### struct `SkinPaintTool::FVertexBoneWeight`  
`struct FVertexBoneWeight`  
_L115-124_
- L117 _public function_ `FVertexBoneWeight() : BoneID(INDEX_NONE), VertexInBoneSpace(FVector::ZeroVector), Weight(0.0f)`
- L118 _public function_ `FVertexBoneWeight(BoneIndex InBoneIndex, const FVector& InPosInRefPose, float InWeight) : BoneID(InBoneIndex), VertexInBoneSpace(InPosInRefPose), Weight(InWeight)`
- L121 _public member_ `BoneIndex BoneID;`
- L122 _public member_ `FVector VertexInBoneSpace;`
- L123 _public member_ `float Weight;`

#### struct `SkinPaintTool::FSkinToolDeformer`  
`struct FSkinToolDeformer`  
_L129-159_
- desc: data required to preview the skinning deformations as you paint
- L131 _public prototype_ `void Initialize(const FReferenceSkeleton& InRefSkeleton, const TArray<FTransform>& PoseComponentSpace, const FDynamicMesh3& InMesh);`
- L133 _public prototype_ `void SetAllVerticesToBeUpdated();`
- L135 _public prototype_ `void SetToRefPose(USkinWeightsPaintTool* Tool);`
- L137 _public prototype_ `void UpdateVertexDeformation(USkinWeightsPaintTool* Tool, const TArray<FTransform>& PoseComponentSpace);`
- L139 _public prototype_ `void SetVertexNeedsUpdated(int32 VertexIndex);`
- L142 _public member_ `TSet<int32> VerticesWithModifiedWeights;` — which vertices require updating (partially re-calculated skinning deformation while painting)
- L144 _public member_ `TArray<FVector> RefPoseVertexPositions;` — position of all vertices in the reference pose
- L146 _public member_ `const FDynamicMesh3* Mesh;` — Store a ref to the Mesh so there is a way to iterate over valid verts
- L148 _public member_ `TArray<FTransform> InvCSRefPoseTransforms;` — inverted, component space ref pose transform of each bone
- L150 _public member_ `TArray<FTransform> PreviousPoseComponentSpace;` — bones transforms used in last deformation update
- L152 _public member_ `TArray<FTransform> RefPoseComponentSpace;` — bones transforms stored for duration of async deformation update
- L154 _public member_ `TArray<FName> BoneNames;` — bone index to bone name
- L155 _public member_ `TMap<FName, BoneIndex> BoneNameToIndexMap;`
- L157 _public member_ `FReferenceSkeleton RefSkeleton;`

#### struct `SkinPaintTool::FSingleBoneWeightEdits`  
`struct FSingleBoneWeightEdits`  
_L162-171_
- desc: store a sparse set of modifications to a set of vertex weights on a SINGLE bone
- L164 _public member_ `int32 BoneIndex;`
- L166 _public member_ `TMap<VertexIndex, float> OldWeights;`
- L167 _public member_ `TMap<VertexIndex, float> NewWeights;`
- L169 _public member_ `TArray<VertexIndex> VerticesAddedTo;`
- L170 _public member_ `TArray<VertexIndex> VerticesRemovedFrom;`

#### struct `SkinPaintTool::FMultiBoneWeightEdits`  
`struct FMultiBoneWeightEdits`  
_L175-187_
- desc: store a sparse set of modifications to a set of vertex weights for a SET of bones with support for merging edits. these are used for transaction history undo/redo.
- L177 _public prototype_ `void MergeSingleEdit( const int32 BoneIndex, const int32 VertexID, const float NewWeight, bool bPruneInfluence, const TArray<VertexWeights>& InPreChangeWeights);`
- L183 _public prototype_ `void MergeEdits(const FSingleBoneWeightEdits& BoneWeightEdits);`
- L186 _public member_ `TMap<BoneIndex, FSingleBoneWeightEdits> PerBoneWeightEdits;` — map of bone indices to weight edits made to that bone

#### struct `SkinPaintTool::FVertexChangeTracker`  
`struct FVertexChangeTracker`  
_L192-219_
- desc: Sparse first-touch gate over a fixed vertex window. Mask gives O(1) dedup; Vertices gives O(touched) iteration. Clear() only wipes the bits that were set, so clearing scales with what was touched, not with mesh size.
- L194 _public member_ `TBitArray<> Mask;`
- L195 _public member_ `TArray<int32> Vertices;`
- L197 _public function_ `void Init(int32 NumVertices)`
- L204 _public function_ `bool Mark(int32 VertexID)` — Returns true on the first Mark this window; false if already marked.
- L212 _public function_ `void Clear()`
- L218 _public function_ `bool IsEmpty() const`

#### class `SkinPaintTool::FMeshSkinWeightsChange`  
`class FMeshSkinWeightsChange : public FToolCommandChange`  
_L223-262_
- inherits: `FToolCommandChange`
- desc: Captures a per-vertex Before/After snapshot of weights touched in a stroke. Storing the full VertexWeights avoids per-bone delta replay and order-dependent eviction at undo time.
- L226 _public function_ `FMeshSkinWeightsChange(const FName InSkinWeightProfile, int32 NumVertices) : FToolCommandChange() , SkinWeightProfile(InSkinWeightProfile)`
- L233 _public function_ `virtual FString ToString() const override`
- L238 _public prototype_ `virtual void Apply(UObject* Object) override;`
- L239 _public prototype_ `virtual void Revert(UObject* Object) override;`
- L242 _public prototype_ `void StoreMultipleWeightEdits(const FMultiBoneWeightEdits& WeightEdits);` — Called per stamp during a stroke to accumulate touched vertices/bones into the change.
- L246 _public prototype_ `void Close(USkinWeightsPaintTool* Tool);` — Captures Before/After snapshots from the tool's weight buffers. Must run before SyncWeightBuffers (which overwrites PreChangeWeights).
- L249 _private prototype_ `static void RestoreVertexFromSnapshot(USkinWeightsPaintTool* Tool, int32 VertexID, const VertexWeights& Snapshot);`
- L251 _private member_ `FName SkinWeightProfile = FSkeletalMeshAttributesShared::DefaultSkinWeightProfileName;`
- L255 _private member_ `FVertexChangeTracker PerTransactionVertexChangeTracker;` — First-touch-this-transaction gate. Mark() dedups touches; Vertices drives Close's snapshot capture and Apply/Revert's replay.
- L258 _private member_ `TArray<VertexWeights> BeforeStates;` — Parallel with PerTransactionVertexChangeTracker.Vertices, populated by Close.
- L259 _private member_ `TArray<VertexWeights> AfterStates;`
- L261 _private member_ `TSet<BoneIndex> ChangedBones;`

#### struct `SkinPaintTool::FSkinToolWeights`  
`struct FSkinToolWeights`  
_L265-343_
- desc: intermediate storage of the weight maps for duration of tool
- L268 _public prototype_ `void InitializeSkinWeights( USkinWeightsPaintTool* InTool, const FDynamicMesh3& Mesh);` — copy the initial weight values from the skeletal mesh
- L272 _public prototype_ `bool IsInitialized() const;`
- L276 _public prototype_ `void CreateWeightEditForVertex( const int32 BoneIndex, const int32 VertexId, float NewWeightValue, FMultiBoneWeightEdits& WeightEdits);` — applies an edit to a single vertex weight on a single bone, then normalizes the remaining weights while keeping the edited weight intact (ie, adapts OTHER influences to achieve normalization)
- L282 _public prototype_ `void ApplyCurrentWeightsToMesh(FDynamicMesh3& Mesh, TFunction<int32(int32)> WeightsIndexToMeshIndex = {});`
- L284 _public prototype_ `static float GetWeightOfBoneOnVertex( const int32 BoneIndex, const int32 VertexID, const TArray<VertexWeights>& InVertexWeights);`
- L289 _public prototype_ `static void FillWeightEdit( const int32 BoneIndex, const int32 VertexID, const float NewWeight, const TArray<VertexWeights>& InVertexWeights);`
- L295 _public prototype_ `void RemoveInfluenceFromVertex( const VertexIndex VertexID, const BoneIndex BoneID, TArray<VertexWeights>& InOutVertexWeights);`
- L303 _public prototype_ `void SyncWeightBuffers();` — some weight editing operations are RELATIVE to existing weights before the change started (Multiply, Add etc) these "existing weights" are stored in the PreChangeWeights buffer PreChange and Current buffers must be synchronized after a transaction
- L305 _public prototype_ `float SetCurrentFalloffAndGetMaxFalloffThisStroke(int32 VertexID, float CurrentStrength);`
- L307 _public prototype_ `void ApplyEditsToCurrentWeights(const FMultiBoneWeightEdits& Edits, FVertexChangeTracker& InOutVertexChangeTracker);`
- L309 _public prototype_ `void UpdateIsBoneWeighted(BoneIndex BoneToUpdate);`
- L311 _public prototype_ `BoneIndex GetParentBoneToWeightTo(BoneIndex ChildBone);`
- L317 _public member_ `TArray<VertexWeights> PreChangeWeights;` — double-buffer of the entire weight matrix (stored sparsely for fast deformation) "Pre" is state of weights at stroke start "Current" is state of weights during stroke When stroke is over, PreChangeWeights are synchronized with CurrentWeights
- L318 _public member_ `TArray<VertexWeights> CurrentWeights;`
- L323 _public member_ `TArray<float> MaxFalloffPerVertexThisStroke;` — record the current maximum amount of falloff applied to each vertex during the current stroke values range from 0-1, this allows brushes to sweep over the same vertex, and apply only the maximum amount of modification (add/replace/relax etc) that was encountered for the duration of the stroke.
- L328 _public typedef_ `using BoneWeight = TPair<BoneIndex, float>;` — Per-stamp scratch used by ApplyEditsToCurrentWeights. Persistent allocation; reset in place between calls. PerWeightEditVertexChangeTracker gates the first touch of a vertex's slot during a stamp and drives the patch-back loop.
- L329 _public typedef_ `using UnlimitedVertexWeights = TArray<BoneWeight, TInlineAllocator<16>>;`
- L330 _public member_ `TArray<UnlimitedVertexWeights> PerWeightEditScratchPad;`
- L331 _public member_ `FVertexChangeTracker PerWeightEditVertexChangeTracker;`
- L334 _public member_ `TArray<bool> IsBoneWeighted;` — record which bones have any weight assigned to them
- L337 _public member_ `FSkinToolDeformer Deformer;` — update deformation when vertex weights are modified
- L340 _public member_ `FName Profile = FSkeletalMeshAttributesShared::DefaultSkinWeightProfileName;` — which skin profile is currently edited
- L342 _public member_ `TWeakObjectPtr<USkinWeightsPaintTool> Tool;`

#### struct `SkinPaintTool::FSkinMirrorData`  
`struct FSkinMirrorData`  
_L345-372_
- L348 _public prototype_ `void EnsureMirrorDataIsUpdated( const TArray<FName>& BoneNames, const TMap<FName, BoneIndex>& BoneNameToIndexMap, const FReferenceSkeleton& RefSkeleton, const TArray<FVector>& RefPoseVertices, EAxis::Type InMirrorAxis, EMirrorDirection InMirrorDirection);` — lazily updates the mirror data tables for the current skeleton/mesh/mirror plane
- L357 _public function_ `const TMap<int32, int32>& GetBoneMap() const` — get a map of Target > Source bone ids across the current mirror plane
- L359 _public prototype_ `const TMap<int32, int32>& GetVertexMap() const;` — get the map of Target > Source vertex ids across the current mirror plane
- L361 _public prototype_ `bool IsPointOnTargetMirrorSide(const FVector& InPoint) const;` — return true if the point lies on the TARGET side of the mirror plane
- L363 _public function_ `void SetNeedsReinitialized()` — forces mirror tables to be re-generated (do this after any mesh change operation)
- L367 _private member_ `bool bIsInitialized = false;`
- L368 _private member_ `TEnumAsByte<EAxis::Type> Axis;`
- L369 _private member_ `EMirrorDirection Direction;`
- L370 _private member_ `TMap<int32, int32> BoneMap;`
- L371 _private member_ `TMap<int32, int32> VertexMap;` — <Target, Source>

#### class `FSkinWeightsPaintToolCommands`  
`class FSkinWeightsPaintToolCommands : public TCommands<FSkinWeightsPaintToolCommands>`  
_L377-394_
- inherits: `TCommands<FSkinWeightsPaintToolCommands>`
- L380 _public prototype_ `FSkinWeightsPaintToolCommands();`
- L382 _public prototype_ `virtual void RegisterCommands() override;`
- L384 _public member_ `TSharedPtr<FUICommandInfo> IsolateSelectedBones;`
- L385 _public member_ `TSharedPtr<FUICommandInfo> ToggleSelectedBonesLockState;`
- L387 _public member_ `TSharedPtr<FUICommandInfo> LockSelectedBones;`
- L388 _public member_ `TSharedPtr<FUICommandInfo> UnlockSelectedBones;`
- L390 _public member_ `TSharedPtr<FUICommandInfo> LockAllBones;`
- L391 _public member_ `TSharedPtr<FUICommandInfo> UnlockAllBones;`
- L393 _public member_ `TSharedPtr<FUICommandInfo> BypassLocks;`

#### class `USkinWeightsPaintToolBuilder`  
`class USkinWeightsPaintToolBuilder : public UMeshSurfacePointMeshEditingToolBuilder`  
_L398-407_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSurfacePointMeshEditingToolBuilder`
- L403 _public prototype_ `UMeshSurfacePointTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L406 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### struct `FSkinWeightBrushConfig`  
`struct FSkinWeightBrushConfig`  
_L415-430_
- reflection: `USTRUCT()`
- desc: for saving/restoring the brush settings separately for each brush mode (Add, Replace, etc...) Note: Radius and FalloffMode are stored per-mode for serialization compatibility, but at runtime they behave as shared values — every writer propagates to all four per-mode configs (see USkinWeightsPaintToolProperties::SetSharedRadius / SetSharedFalloffMode) and RestoreProperties forces all four entries into sync on load.
- L420 _public member_ `float Strength = 1.f;` — `UPROPERTY()`
- L423 _public member_ `float Radius = 20.0f;` — `UPROPERTY()`
- L426 _public member_ `float Falloff = 1.0f;` — `UPROPERTY()`
- L429 _public member_ `EWeightBrushFalloffMode FalloffMode = EWeightBrushFalloffMode::Surface;` — `UPROPERTY()`

#### struct `FSkinWeightRelaxBrushAdvancedConfig`  
`struct FSkinWeightRelaxBrushAdvancedConfig`  
_L433-440_
- reflection: `USTRUCT()`
- L439 _public member_ `bool bAccumulate = true;` — `UPROPERTY()` — When true, Relax stamps read CurrentWeights so wiggling the brush keeps smoothing.

#### struct `FDirectEditWeightState`  
`struct FDirectEditWeightState`  
_L442-453_
- L444 _public member_ `EWeightEditOperation EditMode;`
- L445 _public member_ `float StartValue = 0.f;`
- L446 _public member_ `float CurrentValue = 0.f;`
- L447 _public member_ `bool bInTransaction = false;`
- L449 _public prototype_ `void Reset();`
- L450 _public prototype_ `float GetModeDefaultValue();`
- L451 _public prototype_ `float GetModeMinValue();`
- L452 _public prototype_ `float GetModeMaxValue();`

#### class `USkinWeightsPaintToolProperties`  
`class USkinWeightsPaintToolProperties : public UBrushBaseProperties`  
_L457-615_
- reflection: `UCLASS(MinimalAPI, config = EditorSettings)`
- inherits: `UBrushBaseProperties`
- desc: Container for properties displayed in Details panel while using USkinWeightsPaintTool
- L461 _private prototype_ `USkinWeightsPaintToolProperties();`
- L465 _public prototype_ `virtual void RestoreProperties(UInteractiveTool* RestoreToTool, const FString& CacheIdentifier = TEXT("")) override;`
- L470 _public member_ `EWeightEditMode EditingMode;` — `UPROPERTY(Config)` — brush vs selection modes
- L474 _public member_ `EWeightEditOperation BrushMode;` — `UPROPERTY(Config)` — custom brush modes and falloff types
- L475 _public member_ `EWeightEditOperation PriorBrushMode;` — when toggling with modifier key
- L479 _public member_ `EComponentSelectionMode ComponentSelectionMode = EComponentSelectionMode::Faces;` — `UPROPERTY(Config)` — are we selecting vertices, edges or faces
- L483 _public member_ `EWeightColorMode ColorMode;` — `UPROPERTY(EditAnywhere, Config, Category = MeshDisplay)` — weight color properties
- L487 _public member_ `TArray<FLinearColor> ColorRamp;` — `UE_DEPRECATED(5.8, "Use LinearColorRamp instead")` — `UPROPERTY(Config, meta = (DeprecatedProperty, DeprecationMessage = "Use LinearColorRamp instead."))`
- L490 _public member_ `FLinearColorRamp LinearColorRamp;` — `UPROPERTY(EditAnywhere, Config, Category = MeshDisplay, Meta = (EditCondition="ColorMode==EWeightColorMode::Ramp", EditConditionHides))`
- L494 _public member_ `bool bShowGroupBoundaries = true;` — `UPROPERTY(EditAnywhere, Config, Category = MeshDisplay)` — Show polygroup boundary edges in the viewport.
- L498 _public member_ `FColor GroupBoundaryColor = FColor(220, 100, 220);` — `UPROPERTY(EditAnywhere, Config, Category = MeshDisplay)` — Color of polygroup boundary edges.
- L502 _public member_ `float GroupBoundaryThickness = 1.5f;` — `UPROPERTY(EditAnywhere, Config, Category = MeshDisplay)` — Thickness multiplier for polygroup boundary edges. Drives the visualizer's ThicknessScale since the visualizer renders only polygroup edges.
- L506 _public member_ `TEnumAsByte<EAxis::Type> MirrorAxis = EAxis::X;` — `UPROPERTY(Config)` — weight editing arguments
- L508 _public member_ `EMirrorDirection MirrorDirection = EMirrorDirection::PositiveToNegative;` — `UPROPERTY(Config)`
- L510 _public member_ `float PruneValue = 0.01f;` — `UPROPERTY(Config)`
- L512 _public member_ `int32 ClampValue = 8;` — `UPROPERTY(Config)`
- L514 _public member_ `int32 ClampSelectValue = 8;` — `UPROPERTY(Config)`
- L516 _public member_ `float AddStrength = 1.0;` — `UPROPERTY(Config)`
- L518 _public member_ `float ReplaceValue = 1.0;` — `UPROPERTY(Config)`
- L520 _public member_ `float RelaxStrength = 0.5;` — `UPROPERTY(Config)`
- L522 _public member_ `float AverageStrength = 1.0;` — `UPROPERTY(Config)`
- L524 _public member_ `FDirectEditWeightState DirectEditState;` — the state of the direct weight editing tools (mode buttons + slider)
- L527 _public prototype_ `FSkinWeightBrushConfig& GetBrushConfig();` — save/restore user specified settings for each tool mode
- L528 _public member_ `TMap<EWeightEditOperation, FSkinWeightBrushConfig*> BrushConfigs;`
- L530 _public member_ `FSkinWeightBrushConfig BrushConfigAdd;` — `UPROPERTY(Config)`
- L532 _public member_ `FSkinWeightBrushConfig BrushConfigReplace;` — `UPROPERTY(Config)`
- L534 _public member_ `FSkinWeightBrushConfig BrushConfigMultiply;` — `UPROPERTY(Config)`
- L536 _public member_ `FSkinWeightBrushConfig BrushConfigRelax;` — `UPROPERTY(Config)`
- L539 _public member_ `FSkinWeightRelaxBrushAdvancedConfig RelaxBrushAdvancedConfig;` — `UPROPERTY(Config)`
- L544 _public member_ `TArray<FName> LockedBoneNames;` — `UPROPERTY()` — Persisted form of USkinWeightsPaintTool::LockedBoneIndices. Stored by name so a renamed/removed bone between launches drops the lock instead of mis-locking.
- L548 _public member_ `FString PropertySetCacheIdentifier;` — Cache key for the per-mesh RestoreProperties/SaveProperties round-trip; populated at Setup from the skeletal mesh asset path. Transient.
- L553 _public prototype_ `void SetSharedRadius(float InRadius);` — Radius and FalloffMode behave as shared brush state across all brush modes (matching the sculpt tool's pattern). Storage is still per-mode for config serialization compatibility; these setters propagate the value to every BrushConfig entry so the modes stay in lockstep.
- L554 _public prototype_ `void SetSharedFalloffMode(EWeightBrushFalloffMode InFalloffMode);`
- L557 _public member_ `bool bSyncBrushRadiusAcrossModes = true;` — `UPROPERTY(config)`
- L560 _public member_ `FName SkinWeightProfileOption = FSkeletalMeshAttributesShared::DefaultSkinWeightProfileName;` — `UPROPERTY(EditAnywhere, Category = SkinWeightLayer, meta = (DisplayName = "Active Profile", GetOptions = GetTargetSkinWeightProfilesFunc))`
- L564 _public member_ `bool bShowNewProfileName = false;` — `UPROPERTY(meta = (TransientToolProperty))` — new profile properties
- L567 _public member_ `FName NewSkinWeightProfile = "Pr` — `UPROPERTY(EditAnywhere, Category = SkinWeightLayer, meta = (TransientToolProperty, DisplayName = "New Profile Name", EditCondition = bShowNewProfileName, HideEditConditionToggle, NoResetToDefault))`
- L569 _public prototype_ `FName GetDesiredSkinWeightProfileForTool() const;`
- L572 _public member_ `TObjectPtr<USkinWeightsPaintTool> WeightTool;` — pointer back to paint tool
- L575 _public prototype_ `void SetComponentMode(EComponentSelectionMode InComponentMode);` — `UE_DEPRECATED(5.8, "Instead use SetComponentSelectionMode")`
- L583 _public prototype_ `void SetComponentSelectionMode(const EComponentSelectionMode InComponentMode, const bool bInConvertSelection);` — Sets the component selection mode @param InComponentMode		The component selection mode to set @param bInConvertSelection	When set to true, converts the current selection to the new mode
- L585 _public prototype_ `void SetFalloffMode(EWeightBrushFalloffMode InFalloffMode);`
- L586 _public prototype_ `void SetColorMode(EWeightColorMode InColorMode);`
- L587 _public prototype_ `void SetBrushMode(EWeightEditOperation InBrushMode);`
- L591 _public member_ `TWeakObjectPtr<USkeletalMesh> SourceSkeletalMesh;` — `UPROPERTY(EditAnywhere, Transient, Category = "WeightTransfer")` — transfer
- L593 _public member_ `EMeshTransferOption MeshSelectMode = EMeshTransferOption::Target;` — `UPROPERTY(EditAnywhere, Transient, Category = "WeightTransfer")`
- L595 _public member_ `FName SourceLOD = "LO` — `UPROPERTY(EditAnywhere, Category = "WeightTransfer", meta = (GetOptions = GetSourceLODsFunc))`
- L597 _public member_ `FName SourceSkinWeightProfile = FSkeletalMeshAttributesShared::DefaultSkinWeightProfileName;` — `UPROPERTY(EditAnywhere, Category = "WeightTransfer", meta = (DisplayName = "Source Profile", GetOptions = GetSourceSkinWeightProfilesFunc))`
- L599 _public member_ `FTransform SourcePreviewOffset = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Transient, Category = "WeightTransfer")`
- L603 _private prototype_ `TArray<FName> GetTargetSkinWeightProfilesFunc() const;` — `UFUNCTION()`
- L605 _private prototype_ `TArray<FName> GetSourceLODsFunc() const;` — `UFUNCTION()`
- L607 _private prototype_ `TArray<FName> GetSourceSkinWeightProfilesFunc() const;` — `UFUNCTION()`
- L614 _private member_ `ESkinWeightsPaintToolPropertiesCustomVersion CustomVersion;` — `UPROPERTY(Config)` — Defines a fully custom version stored in the UInteractiveToolPropertySet system. This allows to bump property versions much like common UObject allow bumping post load.

#### class `UDEPRECATED_WeightToolMeshSelector`  
`class UDEPRECATED_WeightToolMeshSelector : public UToolMeshSelector`  
_L623-626_
- reflection: `UCLASS(MinimalAPI, Deprecated)`
- inherits: `UToolMeshSelector`
- desc: this class wraps the all the components to enable selection on a single mesh in the skin weights tool this allows us to make selections on multiple different meshes NOTE: at some point we may want to do component selections on multiple meshes in any/all viewports at which time this class should be centralized and renamed to UMeshSelector or something like that. But there will need to be some sort of centralized facility to manage that and make sure it interacts nicely with other tools.

#### class `UWeightToolTransferManager`  
`class UWeightToolTransferManager : public UObject`  
_L630-689_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: this class wraps a source skeletal mesh used to transfer skin weights to the tool target mesh
- L637 _public prototype_ `void InitialSetup(USkinWeightsPaintTool* InWeightTool, FEditorViewportClient* InViewportClient);` — this must be called from within the parent tool's Setup() so that the selection mechanics are registered for capturing input
- L640 _public prototype_ `void Shutdown();` — called when the tool is shutdown
- L643 _public prototype_ `void Render(IToolsContextRenderAPI* RenderAPI);` — render the selection mechanism
- L644 _public prototype_ `void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI);`
- L647 _public prototype_ `void SetSourceMesh(USkeletalMesh* InSkeletalMesh = nullptr);` — update the mesh we are transferring from
- L650 _public prototype_ `void TransferWeights();` — run the weight transfer
- L653 _public prototype_ `bool CanTransferWeights() const;` — returns true if everything is setup and ready to transfer
- L656 _public function_ `UToolTarget* GetTarget() const` — gets the tool target for the source mesh
- L659 _public function_ `UPreviewMesh* GetPreviewMesh() const` — get the preview mesh for the source mesh
- L662 _public function_ `UToolMeshSelector* GetMeshSelector() const` — get the mesh selector for the source mesh
- L665 _public prototype_ `void OnPropertyModified(const USkinWeightsPaintToolProperties* WeightToolProperties, const FProperty* ModifiedProperty);` — called when tool settings are modified
- L670 _private prototype_ `void TransferWeightsFromOtherMeshOrSubset();` — actually run the weight transfer to copy weights from the source to the target
- L673 _private prototype_ `void TransferWeightsFromSameMeshAndLOD();` — actually run the weight transfer to copy weights from the source to the target
- L675 _private prototype_ `void ApplyTranferredWeightsAsTransaction( const UE::Geometry::FDynamicMeshVertexSkinWeightsAttribute* InTransferredSkinWeights, const TArray<int32>& InVertexSubset, const FDynamicMesh3& InTargetMesh);`
- L681 _private member_ `TObjectPtr<UPreviewMesh> SourcePreviewMesh = nullptr;` — `UPROPERTY()`
- L683 _private member_ `TObjectPtr<USkeletalMesh> SourceSkeletalMesh = nullptr;` — `UPROPERTY()`
- L685 _private member_ `TObjectPtr<UToolTarget> SourceTarget = nullptr;` — `UPROPERTY()`
- L687 _private member_ `TObjectPtr<UToolMeshSelector> MeshSelector;` — `UPROPERTY()`
- L688 _private member_ `TWeakObjectPtr<USkinWeightsPaintTool> WeightTool;`

#### class `UWeightToolSelectionIsolator`  
`class UWeightToolSelectionIsolator : public UObject`  
_L693-759_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: this class wraps all the data needed to isolate a selection of a mesh while editing skin weights
- L700 _public prototype_ `void InitialSetup(USkinWeightsPaintTool* InTool);` — call during tool Setup()
- L703 _public prototype_ `void UpdateIsolatedSelection();` — call every tick to apply deferred changes to mesh
- L706 _public prototype_ `bool CanIsolate() const;` — returns true if further isolation can be performed
- L709 _public prototype_ `bool IsMeshIsolated() const;` — returns true if any triangles are currently isolated
- L712 _public prototype_ `void IsolateSelectionAsTransaction();` — isolate the current selection
- L715 _public prototype_ `void UnIsolateSelectionAsTransaction();` — unisolate the current selection
- L718 _public prototype_ `void SetTrianglesToIsolate(const TArray<int32>& TrianglesToIsolate);` — isolate the array of triangles
- L721 _public prototype_ `void RestoreFullMesh();` — restores the whole mesh
- L724 _public prototype_ `void ApplyWeightsToFullMesh() const;` — apply weights directly
- L727 _public function_ `const TArray<int32>& GetIsolatedTriangles()` — get the current triangles that are isolated
- L730 _public function_ `const UE::Geometry::FDynamicSubmesh3& GetPartialSubmesh() const` — get the partial submesh mapping (valid only when IsMeshIsolated() is true)
- L733 _public function_ `USkinWeightsPaintTool& GetWeightTool() const` — get the weight tool this isolator is attached to
- L737 _public prototype_ `int32 PartialToFullMeshVertexIndex(int32 PartialMeshVertexIndex) const;` — convert to/from partial-isolated and full mesh vertex indices
- L738 _public prototype_ `int32 FullToPartialMeshVertexIndex(int32 FullMeshVertexIndex) const;`
- L741 _public prototype_ `const FDynamicMesh3& GetPartialMesh() const;` — returns the isolated partial mesh (if PartialMeshDescription is not null, this will return an empty DynamicMesh3)
- L745 _private prototype_ `void CreatePartialMesh();`
- L748 _private member_ `TObjectPtr<USkinWeightsPaintTool> WeightTool;` — `UPROPERTY()`
- L752 _private member_ `TArray<int32> CurrentlyIsolatedTriangles;` — when selection is isolated, we hide the full mesh and show a submesh when isolated selection is unhidden, we remap all changes from the submesh back to the full mesh
- L755 _private member_ `bool bIsolatedMeshNeedsUpdated = false;` — Flag to indicate the isolated mesh needs to be updated, handled on the next OnTick
- L758 _private member_ `UE::Geometry::FDynamicSubmesh3 PartialSubMesh;` — isolate selection sub-meshes

#### class `FIsolateSelectionChange`  
`class FIsolateSelectionChange : public FToolCommandChange`  
_L761-770_
- inherits: `FToolCommandChange`
- L764 _public member_ `TArray<int32> IsolatedTrianglesBefore;`
- L765 _public member_ `TArray<int32> IsolatedTrianglesAfter;`
- L767 _public prototype_ `virtual void Apply(UObject* Object) override;`
- L768 _public prototype_ `virtual void Revert(UObject* Object) override;`
- L769 _public prototype_ `virtual FString ToString() const override;`

#### class `USkinWeightsPaintTool`  
`class USkinWeightsPaintTool : public UDynamicMeshBrushTool, public ISkeletalMeshEditingInterface, public ISkeletalMeshGeometryIsolationAwareTool, public IInteractiveToolManageGeometrySelectionAPI, public IHotkeyHintProvider`  
_L776-1169_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDynamicMeshBrushTool,ISkeletalMeshEditingInterface,ISkeletalMeshGeometryIsolationAwareTool,IInteractiveToolManageGeometrySelectionAPI,IHotkeyHintProvider`
- desc: An interactive tool for painting and editing skin weights.
- L789 _public member_ `static constexpr const TCHAR* ActionCommandsContextName = TEXT("Ske`
- L792 _public prototype_ `virtual EMeshLODIdentifier GetEditingLOD();` — Derived tools can optionally override these if they are invoked in editors that don't offer skeletal mesh editor context object
- L793 _public prototype_ `virtual const TArray<FTransform>& GetComponentSpaceBoneTransforms();`
- L794 _public prototype_ `virtual void ToggleBoneManipulation(bool bEnable);`
- L797 _public function_ `virtual bool HasCancel() const override` — UBaseBrushTool overrides
- L798 _public function_ `virtual bool HasAccept() const override`
- L799 _public function_ `virtual bool CanAccept() const override`
- L800 _public prototype_ `virtual bool HitTest(const FRay& Ray, FHitResult& OutHit) override;`
- L801 _public prototype_ `virtual void OnBeginDrag(const FRay& Ray) override;`
- L802 _public prototype_ `virtual void OnUpdateDrag(const FRay& Ray) override;`
- L803 _public prototype_ `virtual void OnEndDrag(const FRay& Ray) override;`
- L804 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L805 _public prototype_ `virtual double EstimateMaximumTargetDimension() override;`
- L806 _public prototype_ `virtual void SetupBrushStampIndicator() override;`
- L807 _public prototype_ `virtual void UpdateBrushStampIndicator() override;`
- L808 _public prototype_ `virtual void ShutdownBrushStampIndicator() override;`
- L810 _public prototype_ `void Init(const FToolBuilderState& InSceneState);`
- L813 _public prototype_ `virtual void Setup() override;` — UInteractiveTool
- L814 _public prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI) override;`
- L815 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L817 _public prototype_ `FName GetActiveSkinWeightProfileName() const;`
- L820 _public function_ `virtual bool SupportsWorldSpaceFocusBox() override` — IInteractiveToolCameraFocusAPI
- L821 _public prototype_ `virtual FBox GetWorldSpaceFocusBox() override;`
- L824 _public prototype_ `virtual void OnUpdateModifierState(int ModifierID, bool bIsOn) override;` — IClickDragBehaviorTarget implementation
- L825 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& InPressPos) override;`
- L828 _public prototype_ `void ExternalUpdateSkinWeightLayer(const FName InSkinWeightProfile);` — Switches active skin profile during undo/redo replay.
- L831 _public prototype_ `void MirrorWeights(EAxis::Type Axis, EMirrorDirection Direction);` — weight editing operations (selection based)
- L832 _public prototype_ `void PruneWeights(const float Threshold, const TArray<BoneIndex>& BonesToPrune);`
- L833 _public prototype_ `void AverageWeights(const float Strength);`
- L834 _public prototype_ `void NormalizeWeights();`
- L835 _public prototype_ `void HammerWeights();`
- L836 _public prototype_ `void ClampInfluences(const int32 MaxInfluences);`
- L841 _public prototype_ `static void TruncateWeightMap(TMap<BoneIndex, float>& InOutWeights, int32 NumLockedBones = 0);` — HELPER functions for modifying weights given a map of BoneIndex > Weight values for a single vertex, modify the map by removing the smallest weights to fit in Max Influences - NumLockedBones
- L843 _public prototype_ `static void NormalizeWeightMap(TMap<BoneIndex, float>& InOutWeights, float ExpectedSum = 1.0f);` — given a map of BoneIndex > Weight values for a single vertex, modify the weights to sum to ExpectedSum
- L845 _public prototype_ `static void AccumulateWeights( const TArray<SkinPaintTool::VertexWeights>& AllWeights, const TArray<VertexIndex>& VerticesToAccumulate, const TSet<BoneIndex>& ExcludedBones, TMap<BoneIndex, float>& OutAccumulatedWeights);` — sum all the weights on all bones for a given list of vertices (results are not normalized!)
- L852 _public prototype_ `static void GetLockedWeight( const TArray<SkinPaintTool::VertexWeights>& AllWeights, VertexIndex InVertexID, const TSet<BoneIndex>& LockedBones, float& OutTotalLockedWeight, int32& OutNumLockedBones);` — query information about how weights are locked on a specific vertex
- L860 _public prototype_ `void CopyWeights();` — copy paste
- L861 _public prototype_ `void PasteWeights();`
- L862 _public member_ `static const FString CopyPasteWeightsIdentifier;`
- L865 _public prototype_ `void EditWeightsOnVertices( BoneIndex Bone, const float Value, const int32 Iterations, EWeightEditOperation EditOperation, const TArray<VertexIndex>& VerticesToEdit, const bool bShouldTransact);` — method to set weights directly (numeric input, for example)
- L874 _public prototype_ `void ToggleEditingMode();` — toggle brush / selection mode
- L876 _public prototype_ `void UpdateSelectorState() const;` — update the state of the mesh selectors
- L879 _public prototype_ `UToolMeshSelector* GetMainMeshSelector();` — get access to the mesh selector for the main mesh
- L881 _public prototype_ `UToolMeshSelector* GetActiveMeshSelector();` — get access to the currently active mesh selector (may be on the transfer source mesh)
- L883 _public prototype_ `bool HasActiveSelectionOnMainMesh();` — does the main mesh have an active selection ("active" meaning the selection is currently being rendered in the view and is editable)
- L885 _public prototype_ `void SelectAffected() const;` — select all vertices affected by the currently selected bone(s)
- L887 _public prototype_ `void SelectByInfluenceCount(const int32 MinInfluences) const;` — select all vertices affected by at least MinInfluences number of bones
- L890 _public prototype_ `void GetInfluences(const TArray<int32>& VertexIndices, TArray<BoneIndex>& OutBoneIndices);` — get the average weight value of each influence on the given vertices
- L892 _public prototype_ `float GetAverageWeightOnBone(const BoneIndex InBoneIndex, const TArray<int32>& VertexIndices);` — get the average weight value of a single bone on the given vertices
- L894 _public prototype_ `FName GetBoneNameFromIndex(BoneIndex InIndex) const;` — convert an index to a name
- L896 _public prototype_ `BoneIndex GetCurrentBoneIndex() const;` — get the currently selected bone
- L898 _public prototype_ `void GetVerticesAffectedByBone(BoneIndex IndexOfBone, TSet<int32>& OutVertexIndices) const;` — get a list of vertices affected by the given bone
- L901 _public prototype_ `void SetDisplayVertexColors(bool bShowVertexColors=true);` — toggle the display of weights on the preview mesh (if false, uses the normal skeletal mesh material)
- L903 _public prototype_ `void SetFocusInViewport() const;` — set focus back to viewport so that hotkeys are immediately detected while hovering
- L906 _public function_ `UToolTargetManager* GetTargetManager() const` — get the target manager (cached from Setup)
- L909 _public function_ `void SetTargetManager(UToolTargetManager* InTargetManager)` — Set the target manager
- L912 _public function_ `SkinPaintTool::FSkinToolWeights& GetWeights()` — allows outside systems to access the weight data
- L915 _public function_ `UWeightToolTransferManager* GetWeightTransferManager() const` — get access to the weight tranfer system
- L918 _public prototype_ `virtual FEditorViewportClient* GetViewportClient() const;` — get the viewport this tool is operating in
- L921 _public function_ `UWeightToolSelectionIsolator* GetSelectionIsolator() const` — get access to the selection isolation system
- L924 _public function_ `UMeshElementsVisualizer* GetMeshElementsDisplay() const` — get access to the mesh-element visualizer (used for polygroup-boundary edge rendering)
- L927 _public prototype_ `USkinWeightsPaintToolProperties* GetWeightToolProperties() const;` — get the tool properties
- L930 _public function_ `FDynamicMesh3& GetMesh()` — get access to the mesh being edited
- L934 _public prototype_ `const TArray<int32>& GetDefaultIsolationTriangles() const;` — Returns default isolation triangles from the editor context (empty if none). Stable for the tool's lifetime — the mode saves/restores isolation around tool activation.
- L937 _public prototype_ `const TSet<int32>& GetFinalLockedBoneIndices();` — get the set of bones whose weights are actually locked, taking into account bBypassAllLocks
- L940 _public prototype_ `const TSet<int32>& GetRawLockedBoneIndices();` — get the set of bones whose weights are locked by user, does not consider bBypassAllLocks
- L943 _public prototype_ `bool IsBypassingAllLocks() const;` — whether weight edits should respect locks or not
- L946 _public prototype_ `bool ShouldProceedWithAllBonesUnlocked();` — Certain operations do not support bone locking yet, show a dialog to check if user still want to proceed
- L958 _public prototype_ `void BeginChange();` — HOW TO EDIT WEIGHTS WITH UNDO/REDO: "Interactive" Edits: For multiple weight editing operations that need to be grouped into a single transaction, like dragging a slider or dragging a brush, you must call: 1. BeginChange() 2. ApplyWeightEditsWithoutTransaction() (this may be called multiple times) 2. EndChange() All the edits are stored into the "ActiveChange" and applied as a single transaction in EndChange(). Deformations and vertex colors will be updated throughout the duration of the change.
- L959 _public prototype_ `void EndChange(const FText& TransactionLabel);`
- L960 _public prototype_ `void ApplyWeightEditsWithoutTransaction(const SkinPaintTool::FMultiBoneWeightEdits& WeightEdits);`
- L964 _public prototype_ `void ApplyWeightEditsAsTransaction(const SkinPaintTool::FMultiBoneWeightEdits& WeightEdits, const FText& TransactionLabel);` — "One-off" Edits: For all one-and-done edits, you can call ApplyWeightEditsAsTransaction(). It will Begin/End the change and create a transaction for it.
- L967 _public prototype_ `void UpdateCurrentlyEditedMesh(const FDynamicMesh3& InDynamicMesh);` — call this whenever the target mesh is modified
- L970 _public prototype_ `void UpdateBrushIndicators();` — Update the brush indicators visibility state
- L973 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnSelectionChanged);` — called whenever the selection is modified
- L974 _public member_ `FOnSelectionChanged OnSelectionChanged;`
- L977 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnWeightsChanged);` — called whenever the weights are modified
- L978 _public member_ `FOnWeightsChanged OnWeightsChanged;`
- L981 _public function_ `const TSharedPtr<SReferenceSkeletonTree>& GetToolSkeletonTree() const` — Returns the skeleton tree displayed when using this tool
- L984 _public prototype_ `virtual bool IsInputIsolationValidOnOutput() const override;` — ISkeletalMeshGeometryIsolationAwareTool
- L987 _public prototype_ `virtual bool IsInputSelectionValidOnOutput() override;` — IInteractiveToolManageGeometrySelectionAPI
- L990 _public prototype_ `virtual void GetHotkeyHints(TArray<FHotkeyHint>& OutHints) const override;` — IHotkeyHintProvider
- L993 _protected prototype_ `virtual void RegisterActions(FInteractiveToolActionSet& ActionSet) override;` — UInteractiveTool overrides
- L995 _protected prototype_ `virtual void ApplyStamp(const FBrushStampData& Stamp);`
- L996 _protected prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L997 _protected prototype_ `virtual void OnTick(float DeltaTime) override;`
- L1000 _protected prototype_ `void OnLinearColorRampChanged(TArray<FRichCurve*> ChangedCurves);` — Called when linear color ramp curves changed
- L1003 _protected prototype_ `float CalculateBrushFalloff(float Distance) const;` — stamp
- L1004 _protected prototype_ `void CalculateVertexROI( const FBrushStampData& InStamp, TArray<VertexIndex>& OutVertexIDs, TArray<float>& OutVertexFalloffs);`
- L1008 _protected prototype_ `float CalculateBrushStrengthToUse(EWeightEditOperation EditMode) const;`
- L1009 _protected member_ `bool bInvertStroke = false;`
- L1010 _protected member_ `FBrushStampData StartStamp;`
- L1011 _protected member_ `FBrushStampData LastStamp;`
- L1012 _protected member_ `bool bStampPending;`
- L1013 _protected member_ `int32 TriangleUnderStamp;`
- L1014 _protected member_ `FVector StampLocalPos;`
- L1018 _protected member_ `TOptional<FVector3d> LastStampWorldPosition;` — Last accepted stamp's world-space position/radius; consulted by the Relax-accumulate dwell throttle in ApplyStamp.
- L1019 _protected member_ `double LastStampWorldRadius = 0.0;`
- L1023 _protected prototype_ `void CreateWeightEditsForVertices( EWeightEditOperation EditOperation, const BoneIndex Bone, const TArray<int32>& VerticesToEdit, const TArray<float>& VertexFalloffs, const float InValue, SkinPaintTool::FMultiBoneWeightEdits& InOutWeightEdits);` — generating bone weight edits to be stored in a transaction does not actually change the weight buffers
- L1033 _protected prototype_ `void CreateWeightEditsToRelaxVertices( TArray<int32> VerticesToEdit, TArray<float> VertexFalloffs, const float Strength, const bool bUsePreChangeWeight, SkinPaintTool::FMultiBoneWeightEdits& InOutWeightEdits);` — Single smoothing pass. To iterate, pair each call with ApplyWeightEditsWithoutTransaction so CurrentWeights advances before the next call. bUsePreChangeWeight=false reads CurrentWeights for cross-call compounding; true reads the at-stroke-start snapshot.
- L1041 _protected typedef_ `using DynamicVerticesOctree = UE::Geometry::TDynamicVerticesOctree3<FDynamicMesh3>;` — used to accelerate mesh queries
- L1042 _protected member_ `TUniquePtr<DynamicVerticesOctree> VerticesOctree;`
- L1043 _protected typedef_ `using DynamicTrianglesOctree = UE::Geometry::FDynamicMeshOctree3;`
- L1044 _protected member_ `TUniquePtr<DynamicTrianglesOctree> TrianglesOctree;`
- L1045 _protected member_ `TFuture<void> TriangleOctreeFuture;`
- L1046 _protected member_ `TArray<int32> TrianglesToReinsert;`
- L1047 _protected prototype_ `void InitializeOctrees();`
- L1051 _protected member_ `TObjectPtr<USkinWeightsPaintToolProperties> WeightToolProperties;` — `UPROPERTY()` — tool properties
- L1052 _protected prototype_ `virtual void OnPropertyModified(UObject* ModifiedObject, FProperty* ModifiedProperty) override;`
- L1055 _protected member_ `FDynamicMesh3 EditedMesh;` — the currently edited mesh descriptions
- L1057 _protected member_ `FName ActiveSkinWeightProfileName = FSkeletalMeshAttributesShared::DefaultSkinWeightProfileName;`
- L1060 _protected member_ `SkinPaintTool::FSkinToolWeights Weights;` — storage of vertex weights per bone
- L1063 _protected member_ `SkinPaintTool::FSkinMirrorData MirrorData;` — cached mirror data
- L1066 _protected member_ `TUniquePtr<SkinPaintTool::FMeshSkinWeightsChange> ActiveChange;` — storage for weight edits in the current transaction
- L1069 _protected member_ `TUniquePtr<UE::Geometry::TBoneWeightsDataSource<int32, float>> SmoothWeightsDataSource;` — Smooth weights data source and operator
- L1070 _protected member_ `TUniquePtr<UE::Geometry::TSmoothBoneWeights<int32, float>> SmoothWeightsOp;`
- L1071 _protected prototype_ `void InitializeSmoothWeightsOperator(const FDynamicMesh3& RestPoseMesh);`
- L1074 _protected prototype_ `void UpdateVertexColorForAllVertices();` — vertex colors updated when switching current bone or initializing whole mesh
- L1075 _protected member_ `bool bVertexColorsNeedUpdated = false;`
- L1077 _protected prototype_ `void UpdateVertexColorForSubsetOfVertices();` — Per-tick gate for vertex-color refresh. OnTick consumes and Clear()s.
- L1078 _protected member_ `SkinPaintTool::FVertexChangeTracker PerColorUpdateVertexChangeTracker;`
- L1079 _protected prototype_ `FVector4f GetColorOfVertex(VertexIndex InVertexIndex, BoneIndex InBoneIndex) const;`
- L1082 _protected prototype_ `void UpdateCurrentBone(const FName &BoneName);` — which bone are we currently painting?
- L1083 _protected prototype_ `BoneIndex GetBoneIndexFromName(const FName BoneName) const;`
- L1084 _protected prototype_ `bool HasSelectedBone() const;`
- L1085 _protected member_ `FName CurrentBone = NAME_None;`
- L1086 _protected member_ `TOptional<FName> PendingCurrentBone;`
- L1087 _protected member_ `TArray<FName> SelectedBoneNames;`
- L1088 _protected member_ `TArray<BoneIndex> SelectedBoneIndices;`
- L1091 _protected prototype_ `virtual void HandleSkeletalMeshModified(const TArray<FName>& InBoneNames, const ESkeletalMeshNotifyType InNotifyType) override;` — ISkeletalMeshEditingInterface
- L1092 _protected prototype_ `virtual TSharedPtr<SWidget> GetCustomSkeletonTreeWidget(TSharedPtr<ISkeletalMeshEditorBinding> EditorBinding) override;`
- L1096 _protected member_ `TObjectPtr<USkeletonModifier> SkeletonReader = nullptr;` — `UPROPERTY()` — used to spawn a tool skeleton tree widget
- L1099 _protected prototype_ `virtual TSharedRef<SWidget> OnGetLockWidget(FName BoneName);` — skin weight locking
- L1100 _protected prototype_ `void SetLockAllBones(bool bLock);`
- L1101 _protected prototype_ `void SetLockSelectedBones(bool bLock);`
- L1102 _protected prototype_ `void IsolateSelectedBones();`
- L1103 _protected prototype_ `void ToggleSelectedBonesLockState();`
- L1104 _protected prototype_ `void ToggleBypassLocks();`
- L1105 _protected prototype_ `void SetLockBone(BoneIndex InBoneIndex, bool bLock);`
- L1107 _protected member_ `TMap<BoneIndex, TSharedPtr<SButton>> LockButtons;`
- L1108 _protected member_ `TSet<BoneIndex> LockedBoneIndices;`
- L1109 _protected member_ `TSet<BoneIndex> UnlockedBoneIndices;`
- L1110 _protected member_ `bool bBypassLocks = false;`
- L1115 _protected member_ `TObjectPtr<UToolMeshSelector> MeshSelector;` — `UPROPERTY()` — the selection system for the main mesh
- L1118 _protected prototype_ `void OnActiveSkinWeightProfileChanged();` — skin weight layer
- L1119 _protected prototype_ `void OnNewSkinWeightProfileChanged();`
- L1120 _protected prototype_ `bool IsProfileValid(const FName InProfileName);`
- L1124 _protected member_ `TWeakObjectPtr<USkeletalMeshEditorContextObjectBase> EditorContext = nullptr;` — `UPROPERTY()` — global properties stored on initialization
- L1126 _protected member_ `TWeakObjectPtr<UPersonaEditorModeManagerContext> PersonaModeManagerContext = nullptr;` — `UPROPERTY()`
- L1128 _protected member_ `TWeakObjectPtr<UToolTargetManager> TargetManager = nullptr;` — `UPROPERTY()`
- L1132 _protected member_ `TObjectPtr<UWeightToolTransferManager> TransferManager = nullptr;` — `UPROPERTY()` — manages transferring skin weights from a separate mesh
- L1136 _protected member_ `TObjectPtr<UWeightToolSelectionIsolator> SelectionIsolator = nullptr;` — `UPROPERTY()` — manages isolating a selection of the mesh
- L1140 _protected member_ `TObjectPtr<class UMeshElementsVisualizer> MeshElementsDisplay = nullptr;` — `UPROPERTY()` — fast retained-mode wireframe for polygroup boundary edges and other mesh elements
- L1143 _protected member_ `bool bConfigDirty = false;` — True while the config changed but wasn't saved yet
- L1146 _protected member_ `TSharedPtr<SReferenceSkeletonTree> ToolSkeletonTree;` — The skeleton tree displayed when using this tool
- L1149 _protected member_ `FString PreviewProfileToRestore;` — editor state to restore when exiting the paint tool
- L1151 _protected member_ `TArray<FTransform> DefaultComponentSpaceBoneTransforms;`
- L1153 _protected member_ `TUniquePtr<FSkeletalMeshNotifierBindScope> SkeletonTreeNotifierBindScope;`
- L1168 _protected prototype_ `FName GetValidNewProfileName(const FName& InProposedName) const;`

#### struct `USkinWeightsPaintTool::FScopedSuspendIsolation`  
`struct FScopedSuspendIsolation`  
_L1159-1166_
- desc: Need to reisolate the mesh if making structural changes to the edited mesh submesh needs to be recreated
- L1161 _public prototype_ `FScopedSuspendIsolation(USkinWeightsPaintTool* InTool);`
- L1162 _public prototype_ `~FScopedSuspendIsolation();`
- L1164 _public member_ `USkinWeightsPaintTool* Tool;`
- L1165 _public member_ `TArray<int32> SavedIsolatedTriangles;`

#### Free symbols / members of external scopes

- L30 _macro_ `#define UE_API MESHMODELINGTOOLSEDITORONLY_API`
- L48 _namespace_ `namespace UE`
- L48 _namespace_ `namespace Geometry` (scope `UE`)
- L55 _typedef_ `using BoneIndex = int32;`
- L111 _namespace_ `namespace SkinPaintTool`
- L126 _typedef_ `using VertexWeights = TArray<FVertexBoneWeight, TFixedAllocator<UE::AnimationCore::MaxInlineBoneWeightCount>>;` (scope `SkinPaintTool`)
- L973 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnSelectionChanged);` — called whenever the selection is modified
- L977 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnWeightsChanged);` — called whenever the weights are modified

### `Plugins/Runtime/MeshModelingToolset/Source/MeshModelingToolsEditorOnly/Public/ToolMeshSelector.h` (Public)


#### enum `EComponentSelectionMode`  
`enum class EComponentSelectionMode : uint8`  
_L31-36_
- reflection: `UENUM()`
- desc: component selection mode
- L33 _public enumerator_ `Vertices`
- L34 _public enumerator_ `Edges`
- L35 _public enumerator_ `Faces`

#### enum `EMeshSelectorTool`  
`enum class EMeshSelectorTool : uint8`  
_L39-44_
- reflection: `UENUM()`
- L41 _public enumerator_ `Ray`
- L42 _public enumerator_ `Marquee`
- L43 _public enumerator_ `Lasso`

#### class `UToolMeshSelector`  
`class UToolMeshSelector : public UObject`  
_L54-121_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: this class wraps the all the components to enable selection on a single mesh in the skin weights tool this allows us to make selections on multiple different meshes NOTE: at some point we may want to do component selections on multiple meshes in any/all viewports at which time this class should be centralized and renamed to UMeshSelector or something like that. But there will need to be some sort of centralized facility to manage that and make sure it interacts nicely with other tools.
- L62 _public prototype_ `void InitialSetup(UWorld* InWorld, UInteractiveTool* InParentTool, FEditorViewportClient* InViewportClient, TFunction<void()> OnSelectionChangedFunc);` — `UE_DEPRECATED(5.7, "Use InitialSetup that does not need use a Viewport Client")` — must be called during the Setup of the parent tool
- L63 _public prototype_ `void InitialSetup(UWorld* InWorld, UInteractiveTool* InParentTool, TFunction<void()> OnSelectionChangedFunc);`
- L67 _public prototype_ `void SetMesh( UPreviewMesh* InMesh, const FTransform3d& InMeshTransform);` — must be called AFTER InitialSetup, and any time the mesh is changed passing in a null preview mesh will disable the selector
- L71 _public prototype_ `void UpdateAfterMeshDeformation();`
- L73 _public prototype_ `void Shutdown();`
- L75 _public prototype_ `void SetIsEnabled(bool bIsEnabled);`
- L76 _public prototype_ `void SetComponentSelectionMode(EComponentSelectionMode InMode);`
- L77 _public prototype_ `void SetTransform(const FTransform3d& InTargetTransform);`
- L79 _public prototype_ `void SetSelectionTool(EMeshSelectorTool InTool);`
- L80 _public prototype_ `EMeshSelectorTool GetSelectionTool() const;`
- L83 _public prototype_ `void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI);` — viewport
- L84 _public prototype_ `void Render(IToolsContextRenderAPI* RenderAPI);`
- L87 _public prototype_ `const TArray<int32>& GetSelectedVertices();` — get a list of currently selected vertices (converting edges and faces to vertices)
- L88 _public prototype_ `bool IsAnyComponentSelected() const;`
- L89 _public prototype_ `void GetSelectedTriangles(TArray<int32>& OutTriangleIndices) const;`
- L92 _public prototype_ `void GrowSelection() const;` — edit selection
- L93 _public prototype_ `void ShrinkSelection() const;`
- L94 _public prototype_ `void InvertSelection() const;`
- L95 _public prototype_ `void FloodSelection() const;`
- L96 _public prototype_ `void SelectBorder() const;`
- L98 _public prototype_ `void Tick(float DeltaTime);`
- L101 _public function_ `UPolygonSelectionMechanic* GetSelectionMechanic()` — get access to the selection mechanic
- L106 _private member_ `TObjectPtr<UInteractiveTool> ParentTool;` — `UPROPERTY()`
- L108 _private member_ `TObjectPtr<UWorld> World;` — `UPROPERTY()`
- L110 _private member_ `TObjectPtr<UPreviewMesh> PreviewMesh;` — `UPROPERTY()`
- L112 _private member_ `TObjectPtr<UPolygonSelectionMechanic> PolygonSelectionMechanic;` — `UPROPERTY()`
- L114 _private member_ `TUniquePtr<UE::Geometry::FDynamicMeshAABBTree3> MeshSpatial = nullptr;`
- L115 _private member_ `TUniquePtr<UE::Geometry::FTriangleGroupTopology> SelectionTopology = nullptr;`
- L118 _private member_ `TUniquePtr<UE::Geometry::FGroupTopology> PolygroupTopology = nullptr;` — Optional polygroup topology pushed to UToolMeshSelectorSelectionMechanic to enable the edge-loop gesture (the mechanic's primary FTriangleGroupTopology can't drive it).
- L120 _private member_ `TArray<VertexIndex> SelectedVerticesInternal;`

#### class `UToolMeshSelectorSelectionMechanic`  
`class UToolMeshSelectorSelectionMechanic : public UPolygonSelectionMechanic`  
_L124-161_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPolygonSelectionMechanic`
- L129 _public prototype_ `virtual void Setup(UInteractiveTool* ParentToolIn) override;`
- L130 _public prototype_ `virtual void Shutdown() override;`
- L134 _public prototype_ `void SetPolygroupTopology(const UE::Geometry::FGroupTopology* InPolygroupTopology);` — Provide a polygroup topology for the shift+double-click edge-loop gesture. Pointer is borrowed; the caller (UToolMeshSelector) owns the lifetime. Pass nullptr to disable.
- L138 _public prototype_ `void ClearLastSingleClickedVertex();` — Drop the tracked seed used by the shift+double-click edge-loop gesture. Must be called when the underlying mesh/topology changes so a stale vertex ID cannot be used as a seed.
- L142 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPos) override;` — Overridden to track recently single-click-selected corners, which seed the shift+double-click edge-loop gesture deterministically.
- L145 _private prototype_ `FInputRayHit OnEdgeLoopDoubleClickHit(const FInputDeviceRay& ClickPos);`
- L146 _private prototype_ `void OnEdgeLoopDoubleClicked(const FInputDeviceRay& ClickPos);`
- L149 _private member_ `TObjectPtr<ULocalDoubleClickInputBehavior> EdgeLoopDoubleClickBehavior;` — `UPROPERTY()`
- L151 _private member_ `const UE::Geometry::FGroupTopology* LoopWalkTopology = nullptr;`
- L159 _private member_ `int32 LastSingleClickedVertexID = INDEX_NONE;` — Two-deep history of single-click-selected corners. The double-click gesture uses PreviousSingleClickedVertexID because the first half of a shift+double-click is dispatched as a single click (see UDoubleClickInputBehavior state machine) and so overwrites LastSingleClickedVertexID with the double-clicked vertex itself. PreviousSingleClickedVertexID retains the click before that, which is the user's actual seed.
- L160 _private member_ `int32 PreviousSingleClickedVertexID = INDEX_NONE;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API MESHMODELINGTOOLSEDITORONLY_API`
- L46 _typedef_ `using VertexIndex = int32;`
