# Plugins / UVEditorToolsEditorOnly

- module root: `Plugins/Editor/UVEditor/Source/UVEditorToolsEditorOnly`
- headers: 4; symbols: 57
- symbol kinds: class=8, function=3, macro=1, member=17, prototype=28
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, DynamicMesh, EditorWidgets, Engine, GeometryAlgorithms, GeometryCore, MeshConversion, MeshDescription, MeshModelingTools, MeshModelingToolsEditorOnly, MeshModelingToolsExp, MeshUtilitiesCommon, ModelingComponents, ModelingEditorUI, ModelingOperators, ModelingOperatorsEditorOnly, PropertyEditor, ProxyLODMeshReduction, Slate, SlateCore, StaticMeshDescription, ToolWidgets, UVEditorTools, UnrealEd
- PublicDependencyModuleNames: Core, InteractiveToolsFramework

### `Plugins/Editor/UVEditor/Source/UVEditorToolsEditorOnly/Public/DetailsCustomizations/UVEditorSeamToolCustomizations.h` (Public)


#### class `FUVEditorSeamToolPropertiesDetails`  
`class FUVEditorSeamToolPropertiesDetails : public IDetailCustomization`  
_L16-24_
- inherits: `IDetailCustomization`
- desc: Customization for UUVEditorSeamToolProperties
- L19 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L20 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L22 _public prototype_ `EUVEditorSeamMode GetCurrentMode(TSharedRef<IPropertyHandle> PropertyHandle) const;`
- L23 _public prototype_ `void OnCurrentModeChanged(EUVEditorSeamMode Mode, TSharedRef<IPropertyHandle> PropertyHandle);`

### `Plugins/Editor/UVEditor/Source/UVEditorToolsEditorOnly/Public/DetailsCustomizations/UVTransformToolCustomizations.h` (Public)


#### class `FUVEditorUVTransformToolDetails`  
`class FUVEditorUVTransformToolDetails : public IDetailCustomization`  
_L15-24_
- inherits: `IDetailCustomization`
- desc: Customization for UUVEditorUVTransformProperties
- L18 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L19 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L22 _protected prototype_ `void BuildQuickTranslateMenu(IDetailLayoutBuilder& DetailBuilder);`
- L23 _protected prototype_ `void BuildQuickRotateMenu(IDetailLayoutBuilder& DetailBuilder);`

#### class `FUVEditorUVQuickTransformToolDetails`  
`class FUVEditorUVQuickTransformToolDetails : public FUVEditorUVTransformToolDetails`  
_L27-32_
- inherits: `FUVEditorUVTransformToolDetails`
- desc: Customization for UUVEditorUVQuickTransformProperties
- L30 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L31 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

#### class `FUVEditorUVDistributeToolDetails`  
`class FUVEditorUVDistributeToolDetails : public IDetailCustomization`  
_L35-51_
- inherits: `IDetailCustomization`
- desc: Customization for UUVEditorUVDistributeProperties
- L38 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L39 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L43 _protected member_ `TSharedPtr<IPropertyHandle> DistributeModeHandle;`
- L44 _protected member_ `TSharedPtr<IPropertyHandle> EnableManualDistancesHandle;`
- L46 _protected member_ `TSharedPtr<IPropertyHandle> OrigManualExtentHandle;`
- L47 _protected member_ `TSharedPtr<IPropertyHandle> OrigManualSpacingHandle;`
- L49 _protected prototype_ `void BuildDistributeModeButtons(IDetailLayoutBuilder& DetailBuilder);`

#### class `FUVEditorUVAlignToolDetails`  
`class FUVEditorUVAlignToolDetails : public IDetailCustomization`  
_L54-66_
- inherits: `IDetailCustomization`
- desc: Customization for UUVEditorUVAlignProperties
- L57 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L58 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L62 _protected member_ `TSharedPtr<IPropertyHandle> AlignDirectionHandle;`
- L64 _protected prototype_ `void BuildAlignModeButtons(IDetailLayoutBuilder& DetailBuilder);`

### `Plugins/Editor/UVEditor/Source/UVEditorToolsEditorOnly/Public/UVEditorParameterizeMeshTool.h` (Public)


#### class `UUVEditorParameterizeMeshToolBuilder`  
`class UUVEditorParameterizeMeshToolBuilder : public UInteractiveToolBuilder`  
_L34-44_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolBuilder`
- L38 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L39 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`
- L43 _public member_ `const TArray<TObjectPtr<UUVEditorToolMeshInput>>* Targets = nullptr;` — This is a pointer so that it can be updated under the builder without having to set it in the mode after initializing targets.

#### class `UUVEditorParameterizeMeshTool`  
`class UUVEditorParameterizeMeshTool : public UInteractiveTool`  
_L52-108_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveTool`
- desc: UParameterizeMeshTool automatically decomposes the input mesh into charts, solves for UVs, and then packs the resulting charts
- L60 _public function_ `virtual void SetTargets(const TArray<TObjectPtr<UUVEditorToolMeshInput>>& TargetsIn)` — The tool will operate on the meshes given here.
- L66 _public prototype_ `virtual void Setup() override;`
- L67 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L69 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L71 _public function_ `virtual bool HasCancel() const override`
- L72 _public function_ `virtual bool HasAccept() const override`
- L73 _public prototype_ `virtual bool CanAccept() const override;`
- L75 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L79 _protected member_ `TArray<TObjectPtr<UUVEditorToolMeshInput>> Targets;` — `UPROPERTY()`
- L82 _protected member_ `TObjectPtr<UParameterizeMeshToolProperties> Settings = nullptr;` — `UPROPERTY()`
- L85 _protected member_ `TObjectPtr<UParameterizeMeshToolUVAtlasProperties> UVAtlasProperties = nullptr;` — `UPROPERTY()`
- L88 _protected member_ `TObjectPtr<UParameterizeMeshToolXAtlasProperties> XAtlasProperties = nullptr;` — `UPROPERTY()`
- L91 _protected member_ `TObjectPtr<UParameterizeMeshToolPatchBuilderProperties> PatchBuilderProperties = nullptr;` — `UPROPERTY()`
- L94 _protected member_ `TObjectPtr<UPolygroupLayersProperties> PolygroupLayerProperties = nullptr;` — `UPROPERTY()`
- L97 _protected member_ `TArray<TObjectPtr<UParameterizeMeshOperatorFactory>> Factories;` — `UPROPERTY()`
- L99 _protected prototype_ `void OnMethodTypeChanged();`
- L105 _protected member_ `UE::Geometry::UVEditorAnalytics::FTargetAnalytics InputTargetAnalytics;`
- L106 _protected member_ `FDateTime ToolStartTimeAnalytics;`
- L107 _protected prototype_ `void RecordAnalytics();`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API UVEDITORTOOLSEDITORONLY_API`

### `Plugins/Editor/UVEditor/Source/UVEditorToolsEditorOnly/Public/UVEditorToolsEditorOnlyModule.h` (Public)


#### class `FUVEditorToolsEditorOnlyModule`  
`class FUVEditorToolsEditorOnlyModule : public IModuleInterface`  
_L8-22_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L16 _public prototype_ `void OnPostEngineInit();`
- L20 _protected member_ `TArray<FName> ClassesToUnregisterOnShutdown;`
- L21 _protected member_ `TArray<FName> PropertiesToUnregisterOnShutdown;`
