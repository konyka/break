# Plugins / ModelingToolsEditorMode

- module root: `Plugins/Editor/ModelingToolsEditorMode/Source/ModelingToolsEditorMode`
- headers: 21; symbols: 776
- symbol kinds: class=32, delegate=3, enum=6, enumerator=16, function=41, macro=5, member=358, namespace=13, prototype=293, struct=9
- PrivateDependencyModuleNames: ContentBrowserData, CoreUObject, DeveloperSettings, DynamicMesh, EditorConfig, EditorFramework, EditorInteractiveToolsFramework, EditorWidgets, Engine, GeometryCore, GeometryFramework, GeometryProcessingInterfaces, InputCore, InteractiveToolsFramework, MeshLODToolset, MeshModelingTools, MeshModelingToolsEditorOnly, MeshModelingToolsEditorOnlyExp, MeshModelingToolsExp, ModelingComponents, ModelingComponentsEditorOnly, ModelingEditorUI, Projects, PropertyEditor, RHI, Slate, SlateCore, StatusBar, StylusInput, ToolMenus, ToolPresetAsset, ToolPresetEditor, ToolWidgets, TypedElementRuntime, UnrealEd, WidgetRegistration
- PublicDependencyModuleNames: Core

### `Plugins/Editor/ModelingToolsEditorMode/Source/ModelingToolsEditorMode/Private/ModelingStylusInputHandler.h` (Private)


#### class `UE::Modeling::FStylusInputHandler`  
`class FStylusInputHandler final : public UE::StylusInput::IStylusInputEventHandler, public IToolStylusStateProviderAPI`  
_L26-61_
- inherits: `UE::StylusInput::IStylusInputEventHandler,IToolStylusStateProviderAPI`
- desc: FStylusInputHandler registers itself as a listener for stylus events and implements the IToolStylusStateProviderAPI interface, which allows MeshSurfacePointTool implementations to query for pen pressure. This is kind of a hack. Unfortunately, the current Stylus module is a Plugin so it cannot be used in the base ToolsFramework directly. So, we need this in the Mode as a workaround.
- L29 _public prototype_ `FStylusInputHandler();`
- L39 _public prototype_ `bool RegisterWindow(const TSharedRef<SWidget>& Widget);` — Registers the window containing the given Widget for Stylus input handling. Registered windows persist for the lifetime of the StylusInputHandler. @param Widget The widget whose window is to be registered. @return True if the window was registered, false if the window was invalid or was previously registered.
- L43 _public prototype_ `virtual FString GetName() override;` — IStylusInputEventHandler implementation
- L44 _public prototype_ `virtual void OnPacket(const UE::StylusInput::FStylusInputPacket& Packet, UE::StylusInput::IStylusInputInstance* Instance) override;`
- L48 _public function_ `virtual float GetCurrentPressure() const override` — IToolStylusStateProviderAPI implementation
- L54 _private prototype_ `void ProcessPacket(const UE::StylusInput::FStylusInputPacket& Packet, UE::StylusInput::IStylusInputInstance* Instance);`
- L55 _private prototype_ `const UE::StylusInput::IStylusInputTabletContext* GetTabletContext(UE::StylusInput::IStylusInputInstance* Instance, uint32 TabletContextID);`
- L57 _private member_ `TMap<TSharedPtr<SWindow>, UE::StylusInput::IStylusInputInstance*> StylusInputInstances;`
- L58 _private member_ `TMap<uint32, TSharedPtr<UE::StylusInput::IStylusInputTabletContext>> TabletContexts;`
- L60 _private member_ `float ActivePressure = 1.0f;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Modeling` (scope `UE`)

### `Plugins/Editor/ModelingToolsEditorMode/Source/ModelingToolsEditorMode/Private/ModelingToolsEditablePaletteConfig.h` (Private)


#### class `UModelingModeEditableToolPaletteConfig`  
`class UModelingModeEditableToolPaletteConfig : public UEditorConfigBase, public IEditableToolPaletteConfigManager`  
_L16-37_
- reflection: `UCLASS(EditorConfig="EditableToolPalette")`
- inherits: `UEditorConfigBase,IEditableToolPaletteConfigManager`
- desc: Implementation of IEditableToolPaletteConfigManager specific to ModelingMode, currently needed because we cannot have one at the FModeToolkit level due to EditorConfig depending on UnrealEd which is where the mode toolkit lives
- L23 _public prototype_ `virtual FEditableToolPaletteSettings* GetMutablePaletteConfig(const FName& InstanceName) override;` — IEditableToolPaletteConfigManager Interface
- L24 _public prototype_ `virtual const FEditableToolPaletteSettings* GetConstPaletteConfig(const FName& InstanceName) override;`
- L25 _public prototype_ `virtual void SavePaletteConfig(const FName& InstanceName) override;`
- L27 _public prototype_ `static void Initialize();`
- L28 _public function_ `static UModelingModeEditableToolPaletteConfig* Get()`
- L29 _public function_ `static IEditableToolPaletteConfigManager* GetAsConfigManager()`
- L32 _public member_ `TMap<FName, FEditableToolPaletteSettings> EditableToolPalettes;` — `UPROPERTY(meta=(EditorConfig))`
- L36 _private member_ `static TObjectPtr<UModelingModeEditableToolPaletteConfig> Instance;`

### `Plugins/Editor/ModelingToolsEditorMode/Source/ModelingToolsEditorMode/Public/DetailsCustomizations/BakeMeshAttributeToolCustomizations.h` (Public)


#### class `FBakeMeshAttributeMapsToolDetails`  
`class FBakeMeshAttributeMapsToolDetails : public IDetailCustomization`  
_L8-13_
- inherits: `IDetailCustomization`
- desc: Customization for UBakeMeshAttributeMapsToolProperties
- L11 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L12 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

#### class `FBakeMultiMeshAttributeMapsToolDetails`  
`class FBakeMultiMeshAttributeMapsToolDetails : public IDetailCustomization`  
_L16-21_
- inherits: `IDetailCustomization`
- desc: Customization for UBakeMultiMeshAttributeMapsToolProperties
- L19 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L20 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

#### class `FBakeMeshAttributeVertexToolDetails`  
`class FBakeMeshAttributeVertexToolDetails : public IDetailCustomization`  
_L24-29_
- inherits: `IDetailCustomization`
- desc: Customization for UBakeMeshAttributeVertexToolProperties
- L27 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L28 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

### `Plugins/Editor/ModelingToolsEditorMode/Source/ModelingToolsEditorMode/Public/DetailsCustomizations/BakeTransformToolCustomizations.h` (Public)


#### class `FBakeTransformToolDetails`  
`class FBakeTransformToolDetails : public IDetailCustomization`  
_L11-22_
- inherits: `IDetailCustomization`
- desc: Customization for UBakeTransformToolProperties
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L15 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L18 _protected prototype_ `void EvaluateBakeScaleMethodRestrictions(TSharedRef<IPropertyHandle> AllowNoScale, TSharedRef<IPropertyHandle> BakeScaleHandle);`
- L21 _protected member_ `TSharedPtr<FPropertyRestriction> BakeScaleMethodEnumRestriction;` — Property restriction applied to the EBakeScaleMethod enum dropdown box

### `Plugins/Editor/ModelingToolsEditorMode/Source/ModelingToolsEditorMode/Public/DetailsCustomizations/MeshTopologySelectionMechanicCustomization.h` (Public)


#### class `FMeshTopologySelectionMechanicPropertiesDetails`  
`class FMeshTopologySelectionMechanicPropertiesDetails : public IDetailCustomization`  
_L11-16_
- inherits: `IDetailCustomization`
- desc: Customization for UMeshTopologySelectionMechanicProperties
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L15 _public prototype_ `void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

### `Plugins/Editor/ModelingToolsEditorMode/Source/ModelingToolsEditorMode/Public/DetailsCustomizations/MeshVertexAttributePaintToolDetailCustomization.h` (Public)


#### class `UE::MeshVertexAttributePaintToolBase::FVertexAttributePaintToolDetailCustomization`  
`class FVertexAttributePaintToolDetailCustomization : public IDetailCustomization`  
_L20-102_
- inherits: `IDetailCustomization`
- L23 _public prototype_ `FVertexAttributePaintToolDetailCustomization();`
- L26 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L29 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L31 _public prototype_ `void OnSelectionChanged();`
- L35 _private prototype_ `void AddEditingModeRow(IDetailCategoryBuilder& EditModeCategory) const;`
- L36 _private prototype_ `void AddColorModeRow(IDetailCategoryBuilder& EditModeCategory) const;`
- L37 _private prototype_ `void AddColorRampRow(IDetailCategoryBuilder& EditModeCategory) const;`
- L38 _private prototype_ `TSharedRef<SWidget> BuildColorRampMenu() const;`
- L39 _private prototype_ `void AddValuesDisplayRows(IDetailCategoryBuilder& EditModeCategory) const;`
- L41 _private prototype_ `void AddBrushUI(IDetailLayoutBuilder& DetailBuilder) const;`
- L42 _private prototype_ `void AddBrushModeRow(IDetailCategoryBuilder& BrushCategory) const;`
- L43 _private prototype_ `void AddBrushFalloffModeRow(IDetailCategoryBuilder& BrushCategory) const;`
- L44 _private prototype_ `void AddBrushRadiusRow(IDetailCategoryBuilder& BrushCategory) const;`
- L45 _private prototype_ `void AddBrushValueRow(IDetailCategoryBuilder& BrushCategory) const;`
- L46 _private prototype_ `void AddBrushFalloffRow(IDetailCategoryBuilder& BrushCategory) const;`
- L47 _private prototype_ `void AddBrushAccumulateRow(IDetailCategoryBuilder& BrushCategory) const;`
- L48 _private prototype_ `void AddBrushValueAtBrushRow(IDetailCategoryBuilder& BrushCategory) const;`
- L49 _private prototype_ `void AddBrushValueQueryMethodRow(IDetailCategoryBuilder& BrushCategory) const;`
- L50 _private prototype_ `void AddBrushHitBackFacesRow(IDetailCategoryBuilder& BrushCategory) const;`
- L52 _private prototype_ `TSharedRef<SWidget> MakeBrushMirrorEnableWidget() const;`
- L53 _private prototype_ `void AddBrushMirrorEnableRow(IDetailCategoryBuilder& BrushCategory) const;`
- L54 _private prototype_ `void AddBrushMirrorPlaneRow(IDetailCategoryBuilder& BrushCategory) const;`
- L55 _private prototype_ `void AddBrushMirrorHideOnBrushStrokeRow(IDetailCategoryBuilder& BrushCategory) const;`
- L56 _private prototype_ `void AddBrushMirrorObjectSpaceRow(IDetailCategoryBuilder& BrushCategory) const;`
- L57 _private prototype_ `void AddBrushMirrorUI(IDetailLayoutBuilder& DetailBuilder) const;`
- L59 _private prototype_ `void AddVisibilityFilterRow(IDetailCategoryBuilder& BrushCategory) const;`
- L61 _private prototype_ `void AddSelectionUI(IDetailLayoutBuilder& DetailBuilder) const;`
- L62 _private prototype_ `TSharedRef<SWidget> MakeDragToolToolbar() const;`
- L63 _private prototype_ `TSharedRef<SWidget> MakeSelectionElementsToolbar() const;`
- L64 _private prototype_ `TSharedRef<SWidget> MakeSelectionIsolationWidget() const;`
- L65 _private prototype_ `TSharedRef<SWidget> MakeSelectionEditActionsToolbar() const;`
- L66 _private prototype_ `void AddSelectionElementsRow(IDetailCategoryBuilder& BrushCategory) const;`
- L67 _private prototype_ `void AddEmptySelectionWarningRow(IDetailCategoryBuilder& BrushCategory) const;`
- L68 _private prototype_ `void MakeSelectionOperationRow(IDetailCategoryBuilder& EditValuesCategory, const FText& RowName, const TSharedRef<SWidget>& ButtonWidget, const TSharedRef<SWidget>& ValueWidget) const;`
- L69 _private prototype_ `void MakeSelectionAddMultiplySliderOperationRow(IDetailCategoryBuilder& EditValuesCategory) const;`
- L70 _private prototype_ `void MakeSelectionAddOperationRow(IDetailCategoryBuilder& EditValuesCategory) const;`
- L71 _private prototype_ `void MakeSelectionReplaceOperationRow(IDetailCategoryBuilder& EditValuesCategory) const;`
- L72 _private prototype_ `void MakeSelectionInvertOperationRow(IDetailCategoryBuilder& EditValuesCategory) const;`
- L73 _private prototype_ `void MakeSelectionRelaxOperationRow(IDetailCategoryBuilder& EditValuesCategory) const;`
- L74 _private prototype_ `void MakeSelectionMirrorOperationRow(IDetailCategoryBuilder& EditValuesCategory) const;`
- L75 _private prototype_ `void MakeSelectionPruneOperationRow(IDetailCategoryBuilder& EditValuesCategory) const;`
- L76 _private prototype_ `void MakeSelectionCopyAndPasteRow(IDetailCategoryBuilder& EditValuesCategory) const;`
- L78 _private prototype_ `TSharedRef<SWidget> MakeMirrorAxisWidget() const;`
- L79 _private prototype_ `TSharedRef<SWidget> MakeMirrorShowAndAxisWidget() const;`
- L80 _private prototype_ `TSharedRef<SWidget> MakeMirrorDirectionButtonsWidget() const;`
- L81 _private prototype_ `TSharedRef<SWidget> MakeMirrorPlaneWidget(bool bShowDirection) const;`
- L82 _private prototype_ `TSharedRef<SWidget> MakeMirrorObjectSpaceCheckboxWidget() const;`
- L83 _private prototype_ `TSharedRef<SWidget> MakeMirrorObjectSpaceWidget() const;`
- L84 _private prototype_ `TSharedRef<SWidget> MakeMirrorButton() const;`
- L86 _private prototype_ `void HideProperty(IDetailLayoutBuilder& DetailBuilder, FName PropertyName) const;`
- L88 _private member_ `IDetailLayoutBuilder* CurrentDetailBuilder = nullptr;`
- L89 _private member_ `TWeakObjectPtr<UMeshVertexAttributePaintToolProperties> ToolProperties;`
- L90 _private member_ `TWeakObjectPtr<UMeshVertexAttributePaintToolBase> Tool;`
- L92 _private member_ `TArray<FName> BrushQueryTypeNames;`
- L93 _private member_ `TMap<FName, EMeshVertexAttributePaintToolValueQueryType> BrushQueryTypeEnumFromNames;`
- L94 _private member_ `TMap<EMeshVertexAttributePaintToolValueQueryType, FName> BrushQueryTypeNameFromEnum;`
- L96 _private member_ `TArray<FName> VisibilityFilterNames;`
- L98 _private member_ `static float WeightSliderWidths;`
- L99 _private member_ `static float WeightEditingLabelsPercent;`
- L100 _private member_ `static float WeightEditVerticalPadding;`
- L101 _private member_ `static float WeightEditHorizontalPadding;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MeshVertexAttributePaintToolBase` (scope `UE`)

### `Plugins/Editor/ModelingToolsEditorMode/Source/ModelingToolsEditorMode/Public/DetailsCustomizations/MeshVertexPaintToolCustomizations.h` (Public)


#### class `FVertexPaintBasicPropertiesDetails`  
`class FVertexPaintBasicPropertiesDetails : public IDetailCustomization`  
_L12-24_
- inherits: `IDetailCustomization`
- desc: customization for UVertexPaintBasicProperties creates custom widgets for paint and erase brushes with pressure sensitivity
- L15 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L16 _public prototype_ `void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L19 _private prototype_ `static void BuildPaintPressureWidget( IDetailLayoutBuilder& DetailBuilder, const TSharedPtr<IPropertyHandle>& ColorPropHandle, TSharedPtr<IPropertyHandle> EnablePressureSensitivityHandle );` — helper to build strength widget, with pressure sensitivity toggle

### `Plugins/Editor/ModelingToolsEditorMode/Source/ModelingToolsEditorMode/Public/DetailsCustomizations/MeshVertexSculptToolCustomizations.h` (Public)


#### class `FSculptBrushPropertiesDetails`  
`class FSculptBrushPropertiesDetails : public IDetailCustomization`  
_L29-34_
- inherits: `IDetailCustomization`
- desc: customization for USculptBrushProperties, creates two-column layout for secondary brush properties like lazy/etc
- L32 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L33 _public prototype_ `void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

#### class `FVertexBrushSculptPropertiesDetails`  
`class FVertexBrushSculptPropertiesDetails : public IDetailCustomization`  
_L39-61_
- inherits: `IDetailCustomization`
- desc: customization for vertexsculpt properties, creates combopanel for brush type, small-style combopanel for falloff type, and stacks controls to the right
- L42 _public prototype_ `virtual ~FVertexBrushSculptPropertiesDetails();`
- L44 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L45 _public prototype_ `void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L48 _protected member_ `TWeakObjectPtr<UMeshVertexSculptTool> TargetTool;`
- L50 _protected prototype_ `TSharedPtr<SWidget> MakeRegionFilterWidget();`
- L51 _protected prototype_ `TSharedPtr<SWidget> MakeFreezeTargetWidget();`
- L53 _protected member_ `TSharedPtr<SButton> FreezeTargetButton;`
- L54 _protected prototype_ `FReply OnToggledFreezeTarget();`
- L55 _protected prototype_ `void OnSetFreezeTarget(ECheckBoxState State);`
- L56 _protected prototype_ `bool IsFreezeTargetEnabled();`
- L58 _protected member_ `TSharedPtr<SComboPanel> FalloffTypeCombo;`
- L59 _protected member_ `TArray<TWeakObjectPtr<UObject>> ObjectsBeingCustomized;`
- L60 _protected member_ `FDelegateHandle FalloffTypeUpdateHandle;`

#### class `FVertexBrushAlphaPropertiesDetails`  
`class FVertexBrushAlphaPropertiesDetails : public IDetailCustomization`  
_L67-82_
- inherits: `IDetailCustomization`
- desc: customization for UVertexBrushAlphaProperties, creates custom asset picker tileview-combopanel for brush alphas and stacks controls to the right
- L70 _public prototype_ `virtual ~FVertexBrushAlphaPropertiesDetails();`
- L72 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L73 _public prototype_ `void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L75 _public member_ `TSharedPtr<FRecentAlphasProvider> RecentAlphasProvider;`
- L78 _protected member_ `TWeakObjectPtr<UMeshVertexSculptTool> TargetTool;`
- L79 _protected member_ `TArray<TWeakObjectPtr<UObject>> ObjectsBeingCustomized;`
- L80 _protected member_ `TSharedPtr<SToolInputAssetComboPanel> AlphaAssetPicker;`
- L81 _protected member_ `FDelegateHandle AlphaTextureUpdateHandle;`

#### class `FMeshSculptBrushOpPropertiesDetails`  
`template<typename BrushClass> class FMeshSculptBrushOpPropertiesDetails : public IDetailCustomization`  
_L87-99_
- inherits: `IDetailCustomization`
- desc: customization for UMeshSculptBrushOpProps - creates custom brush strength w/ pressure sensitivity toggle, when applicable
- L90 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L91 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L94 _private prototype_ `static void BuildStrengthPressureWidget( IDetailLayoutBuilder& DetailBuilder, const TSharedPtr<IPropertyHandle>& StrengthHandle, TSharedPtr<IPropertyHandle> EnablePressureSensitivityHandle );` — helper to build strength widget, with pressure sensitivity toggle when applicable

#### class `FMeshSculptLayerPropertiesDetails`  
`class FMeshSculptLayerPropertiesDetails : public IDetailCustomization`  
_L103-116_
- inherits: `IDetailCustomization`
- desc: customization for UMeshSculptLayerProperties - creates custom mesh layer panel
- L106 _public prototype_ `FMeshSculptLayerPropertiesDetails();`
- L107 _public prototype_ `~FMeshSculptLayerPropertiesDetails();`
- L109 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L110 _public prototype_ `void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L113 _private member_ `TSharedPtr<IMeshLayersController> Controller;`
- L114 _private member_ `FDelegateHandle SculptUpdatesHandle;`
- L115 _private member_ `TWeakObjectPtr<UMeshSculptLayerProperties> SculptProperties;`

### `Plugins/Editor/ModelingToolsEditorMode/Source/ModelingToolsEditorMode/Public/DetailsCustomizations/ModelingToolPropertyCustomizations.h` (Public)


#### class `FModelingToolsAxisFilterCustomization`  
`class FModelingToolsAxisFilterCustomization : public IPropertyTypeCustomization`  
_L10-17_
- inherits: `IPropertyTypeCustomization`
- desc: Details customization for FModelingModeAxisFilter struct - X/Y/Z booleans are laid out in a single horizontal row
- L13 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L15 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L16 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

#### class `FModelingToolsColorChannelFilterCustomization`  
`class FModelingToolsColorChannelFilterCustomization : public IPropertyTypeCustomization`  
_L21-28_
- inherits: `IPropertyTypeCustomization`
- desc: Details customization for FModelingToolsColorChannelFilter struct - R/G/B/A booleans are laid out in a single horizontal row
- L24 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L26 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L27 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

### `Plugins/Editor/ModelingToolsEditorMode/Source/ModelingToolsEditorMode/Public/DetailsCustomizations/ModelingToolsBrushSizeCustomization.h` (Public)


#### class `FSculptToolsUIConstants`  
`class FSculptToolsUIConstants`  
_L10-16_
- desc: defining this here so we can use in FModelingToolsBrushSizeCustomization, should move to some shared constants header/file
- L14 _public member_ `static constexpr int SculptShortLabelWidth = 40;` — sculpt panel packs in the widgets w/ short fixed-width labels

#### class `FModelingToolsBrushSizeCustomization`  
`class FModelingToolsBrushSizeCustomization : public IPropertyTypeCustomization`  
_L20-27_
- inherits: `IPropertyTypeCustomization`
- desc: Details customization for FBrushToolRadius struct. This maybe should be removed in favor of just doing custom UI in FSculptBrushPropertiesDetails...
- L23 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L25 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L26 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

### `Plugins/Editor/ModelingToolsEditorMode/Source/ModelingToolsEditorMode/Public/ModelingModeAssetUtils.h` (Public)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Modeling` (scope `UE`)
- L30 _prototype_ `FString GetNewAssetPathName(const FString& BaseName, const UWorld* TargetWorld, FString SuggestedFolder);` (scope `UE::Modeling`) — Determines path and name for a new Asset based on current mode settings, etc @param BaseName desired initial string for the name @param TargetWorld World the new Asset will be used in, which can determine its generated path based on various settings @param SuggestedFolder a suggested path for the asset, ignored if empty @return Path+Name for the new Asset (package)
- L37 _prototype_ `FString GetWorldRelativeAssetRootPath(const UWorld* World);` (scope `UE::Modeling`) — Determines the world relative asset root path. @param World World the new Asset will be used in; if this is a nullptr then it will be set using the current world context. @return Asset root path relative to the world.
- L43 _prototype_ `FString GetGlobalAssetRootPath();` (scope `UE::Modeling`) — Determines the global asset root path. @return Global asset root path.
- L50 _prototype_ `void OnNewAssetCreated(UObject* Asset);` (scope `UE::Modeling`) — Utility function that may auto-save a newly created asset depending on current mode settings, and posts notifications for the Editor @param Asset the new asset object (eg UStaticMesh, UTexture2D, etc)
- L57 _prototype_ `bool AutoSaveAsset(UObject* Asset);` (scope `UE::Modeling`) — Utility function that will attempt to auto-save an asset, and post Editor change notifications @param Asset the  asset object (eg UStaticMesh, UTexture2D, etc)

### `Plugins/Editor/ModelingToolsEditorMode/Source/ModelingToolsEditorMode/Public/ModelingModeToolExtensions.h` (Public)


#### class `FModelingModeAssetAPI`  
`class FModelingModeAssetAPI`  
_L20-23_
- desc: dummy class for extension API below

#### struct `FExtensionToolQueryInfo`  
`struct FExtensionToolQueryInfo`  
_L33-40_
- desc: This struct is passed to IModelingModeToolExtension implementations to allow them to forward various Tools Context information to their ToolBuilders/etc Note that if bIsInfoQueryOnly is true, then the Extension does not need to construct Tool Builders, the query is for information purposes only
- L35 _public member_ `bool bIsInfoQueryOnly = false;`
- L37 _public member_ `UInteractiveToolsContext* ToolsContext = nullptr;`
- L38 _public member_ `FModelingModeAssetAPI* AssetAPI = nullptr;`
- L39 _public member_ `IToolStylusStateProviderAPI* StylusAPI = nullptr;`

#### struct `FExtensionToolDescription`  
`struct FExtensionToolDescription`  
_L46-60_
- desc: IModelingModeToolExtension implementations return the list of Tools they provide via instances of FExtensionToolDescription.
- L49 _public member_ `FText ToolName;` — Long name of the Tool, used in various places in the UI
- L51 _public member_ `TSharedPtr<FUICommandInfo> ToolCommand;` — Command that is added to the Tool button set. This defines the button label.
- L53 _public member_ `UInteractiveToolBuilder* ToolBuilder = nullptr;` — Builder for the Tool. This can be null if FExtensionToolQueryInfo.bIsInfoQueryOnly is true.
- L59 _public member_ `TFunction<const UE::IInteractiveToolCommandsInterface&()> ToolCommandsGetter = nullptr;` — Optional lambda that returns this tool's hotkey commands object, if one exists, so that those commands can be properly bound/unbound when tool starts/ends. E.g. this will be something like "return FThisExtensionToolCommands::Get();"

#### struct `FModelingModeExtensionExtendedInfo`  
`struct FModelingModeExtensionExtendedInfo`  
_L66-72_
- desc: IModelingModeToolExtension implementations can optionally return additional information used in the Eidtor UI via instances of FModelingModeExtensionExtendedInfo.
- L69 _public member_ `FText ToolPaletteButtonTooltip;` — Tooltip to use for UI buttons that refer to the Extension
- L71 _public member_ `TSharedPtr<FUICommandInfo> ExtensionCommand;` — Command button that will be used for the extension in the Modeling Mode Tab Bar. This can be undefined, in which case a Command button w/ default icon will be created.

#### class `IModelingModeToolExtension`  
`class IModelingModeToolExtension : public IModularFeature`  
_L80-125_
- inherits: `IModularFeature`
- desc: IModelingModeToolExtension uses the IModularFeature API to allow a Plugin to provide a set of InteractiveTool's to be exposed in Modeling Mode. The Tools will be included in a section of the Modeling Mode tool list, based on GetToolSectionName().
- L83 _public prototype_ `virtual ~IModelingModeToolExtension() = default;`
- L88 _public prototype_ `virtual FText GetExtensionName() = 0;` — @return A text string that identifies this Extension.
- L94 _public prototype_ `virtual FText GetToolSectionName() = 0;` — @return A text string that defines the name of the Toolbar Section this Extension's tools will be included in. @warning If the same Section is used in multiple Extensions, some buttons may not be shown
- L106 _public prototype_ `virtual void GetExtensionTools(const FExtensionToolQueryInfo& QueryInfo, TArray<FExtensionToolDescription>& ToolsOut) = 0;` — Query the Extension for a list of Tools to expose in Modeling Mode. Note that this function *will* be called multiple times by Modeling Mode, as the information about the set of Tools is needed in multiple places. The QueryInfo.bIsInfoQueryOnly flag indicates whether the caller requires ToolBuilder instances. If creating multiple copies of the ToolBuilder for a particular Tool would be problematic, it is the responsiblity of the IModelingModeToolExtension implementation to cache these internally, otherwise they will be garbage collected when the caller releases them.
- L112 _public function_ `virtual bool GetExtensionExtendedInfo(FModelingModeExtensionExtendedInfo& InfoOut)` — Query the Extension for extended information. This function is optional, the results will be ignored unless it is overridden and returns true.
- L118 _public function_ `virtual bool GetExtensionToolTargets(TArray<TSubclassOf<UToolTargetFactory>>& ToolTargetFactoriesOut)` — Query the extension for additional tool targets. This function is optional and the result will be ignored unless it is overridden and returns true.
- L120 _public function_ `static FName GetModularFeatureName()`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`

### `Plugins/Editor/ModelingToolsEditorMode/Source/ModelingToolsEditorMode/Public/ModelingSelectionInteraction.h` (Public)


#### enum `EModelingSelectionInteraction_DragMode`  
`enum class EModelingSelectionInteraction_DragMode : uint8`  
_L33-38_
- reflection: `UENUM()`
- L35 _public enumerator_ `NoDragInteraction = 0`
- L36 _public enumerator_ `PathInteraction = 1`
- L37 _public enumerator_ `RectangleMarqueeInteraction = 2`

#### enum `EModelingSelectionInteraction_LocalFrameMode`  
`enum class EModelingSelectionInteraction_LocalFrameMode : uint8`  
_L41-45_
- reflection: `UENUM()`
- L43 _public enumerator_ `FromGeometry = 0`
- L44 _public enumerator_ `FromObject = 1`

#### class `UModelingSelectionInteraction`  
`class UModelingSelectionInteraction : public UObject, public IInputBehaviorSource, public IClickBehaviorTarget, public IHoverBehaviorTarget`  
_L66-233_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IInputBehaviorSource,IClickBehaviorTarget,IHoverBehaviorTarget`
- desc: UModelingSelectionInteraction provides element-level selection behavior (ie mesh triangles/edges/vertices) via the UGeometrySelectionManager. The Interaction doesn't actually know about the meshes or interact with them at all, it simply "operates" the SelectionManager based on user input. In addition to handling selection/deselection behaviors based on user input, the UModelingSelectionInteraction also creates a Gizmo for the active selection if it is transformable, and forwards gizmo transformations to the SelectionManager. Currently some desired Selection-related interactions require a slightly convoluted path through the code, because (for example) we want the standard UE editor gizmo to have "click precedence" over our selection click behaviors. However we will get the input event first, so we need to be able to check if the gizmo is hit via a callback function provided by the EdMode owning the ToolsContext this Interaction will be registered in. Similarly we need to be able to filter out hits if a closer visible object is hit, because there is no higher-level Behavior that will do that for us. (This may be improved in future, if more of the existing Editor interaction behaviors are re-implemented as InputBehaviors)
- L76 _public prototype_ `virtual void Initialize( TObjectPtr<UGeometrySelectionManager> SelectionManager, TUniqueFunction<bool()> CanChangeSelectionCallbackIn, TUniqueFunction<bool(const FInputDeviceRay&)> ExternalHitCaptureCallbackIn);` — Set up the Interaction, creates and registers Behaviors/etc. @param CanChangeSelectionCallbackIn this function will be called to determine if the current Selection is allowed to be modified (for example, when a Tool is active, we may wish to lock selection)
- L81 _public prototype_ `virtual void Shutdown();`
- L83 _public function_ `UGeometrySelectionManager* GetSelectionManager()`
- L84 _public prototype_ `UE::Geometry::FGeometrySelectionUpdateConfig GetActiveSelectionUpdateConfig() const;`
- L86 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI);`
- L87 _public prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI);`
- L94 _public function_ `EModelingSelectionInteraction_DragMode GetActiveDragMode() const`
- L95 _public prototype_ `void SetActiveDragMode(EModelingSelectionInteraction_DragMode NewMode);`
- L102 _public prototype_ `virtual void ApplyPendingTransformInteractions();` — this needs to be called from EdMode tick or rendering, to avoid mouse-interrupt priority issues
- L104 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnBeginTransformInteraction);`
- L105 _public member_ `FOnBeginTransformInteraction OnTransformBegin;`
- L107 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnEndTransformInteraction);`
- L108 _public member_ `FOnEndTransformInteraction OnTransformEnd;`
- L113 _public function_ `EModelingSelectionInteraction_LocalFrameMode GetLocalFrameMode() const` — Support for Adjusting Local Frame Mode
- L114 _public prototype_ `void SetLocalFrameMode(EModelingSelectionInteraction_LocalFrameMode NewLocalFrameMode);`
- L119 _protected member_ `TObjectPtr<USingleClickOrDragInputBehavior> ClickOrDragBehavior;` — `UPROPERTY()` — click-to-select behavior, various drag behaviors
- L123 _protected member_ `TObjectPtr<UMouseHoverBehavior> HoverBehavior;` — `UPROPERTY()` — mouse hover behavior
- L127 _protected member_ `TObjectPtr<UInputBehaviorSet> BehaviorSet;` — `UPROPERTY()` — set of all behaviors, will be passed up to UInputRouter
- L133 _public function_ `virtual const UInputBehaviorSet* GetInputBehaviors() const` — IInputBehaviorSource API
- L141 _public prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos) override;` — IClickBehaviorTarget implementation
- L142 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPos) override;`
- L148 _public prototype_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos) override;` — IHoverBehaviorTarget implementation
- L149 _public prototype_ `virtual void OnBeginHover(const FInputDeviceRay& DevicePos) override;`
- L150 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L151 _public prototype_ `virtual void OnEndHover() override;`
- L156 _public prototype_ `virtual void OnUpdateModifierState(int ModifierID, bool bIsOn) override;` — IModifierToggleBehaviorTarget implementation
- L162 _protected function_ `TUniqueFunction<bool()> CanChangeSelectionCallback = []()` — default change-selection callback always allows selection change
- L162 _protected member_ `TUniqueFunction<bool()> CanChangeSelectionCallback = []() { return true; };` — default change-selection callback always allows selection change
- L165 _protected function_ `TUniqueFunction<bool(const FInputDeviceRay&)> ExternalHitCaptureCallback = [](const FInputDeviceRay&)`
- L165 _protected member_ `TUniqueFunction<bool(const FInputDeviceRay&)> ExternalHitCaptureCallback = [](const FInputDeviceRay&) { return false; };`
- L167 _protected prototype_ `void ComputeSceneHits(const FInputDeviceRay& ClickPos, bool& bHitActiveObjects, FInputRayHit& ActiveObjectHit, bool& bHitInactiveObjectFirst, FInputRayHit& InactiveObjectHit);`
- L171 _protected member_ `bool bClearSelectionOnClicked = false;`
- L174 _protected member_ `static const int AddToSelectionModifier = 1;` — flags used to identify behavior modifier keys/buttons
- L175 _protected member_ `bool bAddToSelectionEnabled = false;`
- L177 _protected member_ `static const int ToggleSelectionModifier = 2;`
- L178 _protected member_ `bool bToggleSelectionEnabled = false;`
- L183 _protected member_ `TObjectPtr<UGeometrySelectionManager> SelectionManager;` — `UPROPERTY()`
- L185 _protected member_ `FDelegateHandle OnSelectionModifiedDelegate;`
- L186 _protected prototype_ `void OnSelectionManager_SelectionModified();`
- L192 _protected member_ `TObjectPtr<UTransformProxy> TransformProxy;` — `UPROPERTY()`
- L195 _protected member_ `TObjectPtr<UCombinedTransformGizmo> TransformGizmo;` — `UPROPERTY()`
- L198 _protected member_ `TObjectPtr<UDragAlignmentInteraction> DragAlignmentInteraction;` — `UPROPERTY()`
- L201 _protected member_ `TObjectPtr<UKeyAsModifierInputBehavior> DragAlignmentToggleBehavior;` — `UPROPERTY()`
- L203 _protected member_ `UE::Geometry::FFrame3d InitialGizmoFrame;`
- L204 _protected member_ `FVector3d InitialGizmoScale;`
- L205 _protected member_ `UE::Geometry::FFrame3d LastUpdateGizmoFrame;`
- L206 _protected member_ `FVector3d LastUpdateGizmoScale;`
- L207 _protected member_ `FVector3d LastTranslationDelta;`
- L208 _protected member_ `FVector4d LastRotateDelta;`
- L209 _protected member_ `FVector3d LastScaleDelta;`
- L210 _protected member_ `bool bInActiveTransform = false;`
- L212 _protected prototype_ `void UpdateGizmoOnSelectionChange();`
- L213 _protected member_ `bool bGizmoUpdatePending = false;`
- L215 _protected prototype_ `void OnBeginGizmoTransform(UTransformProxy* Proxy);`
- L216 _protected prototype_ `void OnEndGizmoTransform(UTransformProxy* Proxy);`
- L217 _protected prototype_ `void OnGizmoTransformChanged(UTransformProxy* Proxy, FTransform Transform);`
- L221 _protected member_ `EModelingSelectionInteraction_DragMode ActiveDragMode = EModelingSelectionInteraction_DragMode::NoDragInteraction;`
- L222 _protected prototype_ `void UpdateActiveDragMode();`
- L224 _protected member_ `EModelingSelectionInteraction_LocalFrameMode LocalFrameMode = EModelingSelectionInteraction_LocalFrameMode::FromGeometry;`
- L227 _protected member_ `TObjectPtr<URectangleMarqueeInteraction> RectangleMarqueeInteraction;` — `UPROPERTY()`
- L229 _protected prototype_ `void OnMarqueeRectangleFinished(const FCameraRectangle& Rectangle, bool bCancelled);`
- L232 _protected member_ `TObjectPtr<UPathSelectionInteraction> PathSelectionInteraction;` — `UPROPERTY()`

#### class `UPathSelectionInteraction`  
`class UPathSelectionInteraction : public UObject, public IClickDragBehaviorTarget`  
_L244-260_
- reflection: `UCLASS()`
- inherits: `UObject,IClickDragBehaviorTarget`
- desc: UPathSelectionInteraction is a simple drag-interaction for Selection, which essentially just selects/deselects any element hit by the cursor. Currently no attempt is made to (eg) subsample, so a fast-moving cursor will skip over some faces.
- L248 _public prototype_ `void Setup(UModelingSelectionInteraction* SelectionInteraction);`
- L252 _protected member_ `TWeakObjectPtr<UModelingSelectionInteraction> SelectionInteraction = nullptr;` — `UPROPERTY()`
- L254 _protected prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) override;`
- L255 _protected prototype_ `virtual void OnClickPress(const FInputDeviceRay& PressPos) override;`
- L256 _protected prototype_ `virtual void OnClickDrag(const FInputDeviceRay& DragPos) override;`
- L257 _protected prototype_ `virtual void OnClickRelease(const FInputDeviceRay& ReleasePos) override;`
- L258 _protected prototype_ `virtual void OnTerminateDragSequence() override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MODELINGTOOLSEDITORMODE_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Geometry` (scope `UE`)
- L104 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnBeginTransformInteraction);`
- L107 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnEndTransformInteraction);`

### `Plugins/Editor/ModelingToolsEditorMode/Source/ModelingToolsEditorMode/Public/ModelingToolsActions.h` (Public)


#### enum `EModelingModeActionCommands`  
`enum class EModelingModeActionCommands`  
_L9-13_
- L11 _public enumerator_ `FocusViewToCursor`
- L12 _public enumerator_ `ToggleSelectionLockState`

#### class `FModelingModeActionCommands`  
`class FModelingModeActionCommands : public TCommands<FModelingModeActionCommands>`  
_L16-28_
- inherits: `TCommands<FModelingModeActionCommands>`
- L19 _public prototype_ `FModelingModeActionCommands();`
- L21 _public prototype_ `virtual void RegisterCommands() override;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> FocusViewCommand;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> ToggleSelectionLockStateCommand;`
- L26 _public prototype_ `static void RegisterCommandBindings(TSharedPtr<FUICommandList> UICommandList, TFunction<void(EModelingModeActionCommands)> OnCommandExecuted);`
- L27 _public prototype_ `static void UnRegisterCommandBindings(TSharedPtr<FUICommandList> UICommandList);`

#### class `FModelingToolActionCommands`  
`class FModelingToolActionCommands : public TInteractiveToolCommands<FModelingToolActionCommands>`  
_L35-63_
- inherits: `TInteractiveToolCommands<FModelingToolActionCommands>`
- desc: TInteractiveToolCommands implementation for this module that provides standard Editor hotkey support
- L38 _public prototype_ `FModelingToolActionCommands();`
- L40 _public prototype_ `virtual void GetToolDefaultObjectList(TArray<UInteractiveTool*>& ToolCDOs) override;`
- L49 _public prototype_ `static void RegisterAllToolActions();` — Register all Tool command sets. Call this in module startup
- L54 _public prototype_ `static void UnregisterAllToolActions();` — Unregister all Tool command sets. Call this from module shutdown.
- L61 _public prototype_ `static void UpdateToolCommandBinding(UInteractiveTool* Tool, TSharedPtr<FUICommandList> UICommandList, bool bUnbind = false);` — Add or remove commands relevant to Tool to the given UICommandList. Call this when the active tool changes (eg on ToolManager.OnToolStarted / OnToolEnded) @param bUnbind if true, commands are removed, otherwise added

#### Free symbols / members of external scopes

- L70 _macro_ `#define DECLARE_TOOL_ACTION_COMMANDS(CommandsClassName) \`
- L79 _prototype_ `DECLARE_TOOL_ACTION_COMMANDS(FSculptToolActionCommands);`
- L80 _prototype_ `DECLARE_TOOL_ACTION_COMMANDS(FVertexSculptToolActionCommands);`
- L81 _prototype_ `DECLARE_TOOL_ACTION_COMMANDS(FMeshGroupPaintToolActionCommands);`
- L82 _prototype_ `DECLARE_TOOL_ACTION_COMMANDS(FMeshVertexPaintToolActionCommands);`
- L83 _prototype_ `DECLARE_TOOL_ACTION_COMMANDS(FMeshAttributePaintToolActionCommands);`
- L84 _prototype_ `DECLARE_TOOL_ACTION_COMMANDS(FTransformToolActionCommands);`
- L85 _prototype_ `DECLARE_TOOL_ACTION_COMMANDS(FDrawPolygonToolActionCommands);`
- L86 _prototype_ `DECLARE_TOOL_ACTION_COMMANDS(FMeshSelectionToolActionCommands);`
- L87 _prototype_ `DECLARE_TOOL_ACTION_COMMANDS(FEditMeshMaterialsToolActionCommands);`
- L88 _prototype_ `DECLARE_TOOL_ACTION_COMMANDS(FMeshPlaneCutToolActionCommands);`
- L89 _prototype_ `DECLARE_TOOL_ACTION_COMMANDS(FCubeGridToolActionCommands);`
- L90 _prototype_ `DECLARE_TOOL_ACTION_COMMANDS(FEditMeshPolygonsToolActionCommands);`
- L91 _prototype_ `DECLARE_TOOL_ACTION_COMMANDS(FDrawAndRevolveToolActionCommands);`

### `Plugins/Editor/ModelingToolsEditorMode/Source/ModelingToolsEditorMode/Public/ModelingToolsEditorMode.h` (Public)


#### class `UModelingToolsEditorMode`  
`class UModelingToolsEditorMode : public UBaseLegacyWidgetEdMode, public ILegacyEdModeSelectInterface`  
_L31-191_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UBaseLegacyWidgetEdMode,ILegacyEdModeSelectInterface`
- L35 _public member_ `const static FEditorModeID EM_ModelingToolsEditorModeId;`
- L37 _public prototype_ `UModelingToolsEditorMode();`
- L38 _public prototype_ `UModelingToolsEditorMode(FVTableHelper& Helper);`
- L39 _public prototype_ `~UModelingToolsEditorMode();`
- L44 _public prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;`
- L46 _public prototype_ `virtual void ActorSelectionChangeNotify() override;`
- L48 _public prototype_ `virtual bool ShouldDrawWidget() const override;`
- L49 _public prototype_ `virtual bool ProcessEditDelete() override;`
- L50 _public prototype_ `virtual bool ProcessEditCut() override;`
- L52 _public prototype_ `virtual bool CanAutoSave() const override;`
- L54 _public prototype_ `virtual bool GetPivotForOrbit(FVector& OutPivot) const override;`
- L56 _public function_ `virtual bool RequiresLegacyViewportInteractions() const override`
- L63 _public prototype_ `virtual void Enter() override;` — called when we "start" this editor mode (ie switch to this tab)
- L66 _public prototype_ `virtual void Exit() override;` — called when we "end" this editor mode (ie switch to another tab)
- L68 _public prototype_ `virtual bool ShouldToolStartBeAllowed(const FString& ToolIdentifier) const override;`
- L76 _public prototype_ `virtual bool BoxSelect(FBox& InBox, bool InSelect = true) override;` — ILegacyEdModeSelectInterface
- L77 _public prototype_ `virtual bool FrustumSelect(const FConvexVolume& InFrustum, FEditorViewportClient* InViewportClient, bool InSelect) override;`
- L81 _public prototype_ `virtual bool HasCustomViewportFocus() const override;` — Manage viewport focus
- L82 _public prototype_ `virtual FBox ComputeCustomViewportFocus() const override;`
- L90 _public function_ `virtual UGeometrySelectionManager* GetSelectionManager() const`
- L94 _public function_ `virtual UModelingSelectionInteraction* GetSelectionInteraction() const`
- L100 _public member_ `bool bEnableVolumeElementSelection = true;` — `UPROPERTY()`
- L103 _public member_ `bool bEnableStaticMeshElementSelection = true;` — `UPROPERTY()`
- L105 _public prototype_ `bool GetMeshElementSelectionSystemEnabled() const;`
- L106 _public prototype_ `void NotifySelectionSystemEnabledStateModified();`
- L109 _protected prototype_ `virtual void BindCommands() override;`
- L110 _protected prototype_ `virtual void CreateToolkit() override;`
- L111 _protected prototype_ `virtual void OnToolStarted(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L112 _protected prototype_ `virtual void OnToolEnded(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L114 _protected prototype_ `virtual void OnToolPostBuild(UInteractiveToolManager* InToolManager, EToolSide InSide, UInteractiveTool* InBuiltTool, UInteractiveToolBuilder* InToolBuilder, const FToolBuilderState& ToolState);`
- L117 _protected prototype_ `void RegisterUVEditor();` — Method to optionally register the UV Editor launcher in the Modeling Mode UV category if the plugin is available.
- L119 _protected member_ `FDelegateHandle MeshCreatedEventHandle;`
- L120 _protected member_ `FDelegateHandle TextureCreatedEventHandle;`
- L121 _protected member_ `FDelegateHandle MaterialCreatedEventHandle;`
- L122 _protected member_ `FDelegateHandle SelectionModifiedEventHandle;`
- L124 _protected member_ `FDelegateHandle EditorClosedEventHandle;`
- L125 _protected prototype_ `void OnEditorClosed();`
- L127 _protected member_ `TSharedPtr<FLevelObjectsObserver> LevelObjectsObserver;`
- L130 _protected member_ `TObjectPtr<UModelingSceneSnappingManager> SceneSnappingManager;` — `UPROPERTY()`
- L133 _protected member_ `TObjectPtr<UGeometrySelectionManager> SelectionManager;` — `UPROPERTY()`
- L136 _protected member_ `TObjectPtr<UModelingSelectionInteraction> SelectionInteraction;` — `UPROPERTY()`
- L138 _protected member_ `FDelegateHandle SelectionManager_SelectionModifiedHandle;`
- L140 _protected prototype_ `bool GetGeometrySelectionChangesAllowed() const;`
- L141 _protected prototype_ `bool TestForEditorGizmoHit(const FInputDeviceRay&) const;`
- L144 _protected member_ `bool bSelectionSystemEnabled = false;`
- L146 _protected prototype_ `void UpdateSelectionManagerOnEditorSelectionChange(bool bEnteringMode = false);`
- L148 _protected prototype_ `void OnToolsContextRender(IToolsContextRenderAPI* RenderAPI);`
- L149 _protected prototype_ `void OnToolsContextDrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI);`
- L151 _protected prototype_ `void ModelingModeShortcutRequested(EModelingModeActionCommands Command);`
- L152 _protected prototype_ `void FocusCameraAtCursorHotkey();`
- L154 _protected prototype_ `void AcceptActiveToolActionOrTool();`
- L155 _protected prototype_ `void CancelActiveToolActionOrTool();`
- L157 _protected prototype_ `void ConfigureRealTimeViewportsOverride(bool bEnable);`
- L159 _protected member_ `FDelegateHandle BlueprintPreCompileHandle;`
- L160 _protected prototype_ `void OnBlueprintPreCompile(UBlueprint* Blueprint);`
- L168 _protected member_ `TArray<TObjectPtr<UInteractiveCommand>> ModelingModeCommands;` — `UPROPERTY()`
- L172 _protected member_ `static FDateTime LastModeStartTimestamp;` — analytics tracking
- L173 _protected member_ `static FDateTime LastToolStartTimestamp;`
- L176 _protected member_ `static FDelegateHandle GlobalModelingWorldTeardownEventHandle;` — tracking of unlocked stuff
- L179 _private prototype_ `void PopulateModelingModeViewportToolbar(const FName InMenuName, const TSharedPtr<const FUICommandList>& InCommandList);` — add modeling-mode-specific portion of new viewport toolbar
- L181 _private prototype_ `static void RemoveModelingModeViewportToolbarExtensions();` — remove modeling-mode-specific portion of new viewport toolbar
- L184 _private member_ `TMap<FString, FExtensionToolDescription> ExtensionToolToInfo;` — Support extension tools having their own hotkey classes
- L187 _private prototype_ `bool TryGetExtensionToolCommandGetter(UInteractiveToolManager* Manager, UInteractiveTool* Tool, TFunction<const UE::IInteractiveToolCommandsInterface&()>& GetterOut) const;` — Note: this will only work when the given tool is active, because we get the tool identifier out of the manager using GetActiveToolName
- L190 _private member_ `TFunction<const UE::IInteractiveToolCommandsInterface& ()> ExtensionToolCommandsGetter;` — Used to unbind extension tool commands

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`

### `Plugins/Editor/ModelingToolsEditorMode/Source/ModelingToolsEditorMode/Public/ModelingToolsEditorModeModule.h` (Public)


#### class `FModelingToolsEditorModeModule`  
`class FModelingToolsEditorModeModule : public IModuleInterface`  
_L8-22_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L16 _public prototype_ `void OnPostEngineInit();`
- L20 _private member_ `TArray<FName> ClassesToUnregisterOnShutdown;` — StaticClass is not safe on shutdown, so we cache the name, and use this to unregister on shut down
- L21 _private member_ `TArray<FName> PropertiesToUnregisterOnShutdown;`

### `Plugins/Editor/ModelingToolsEditorMode/Source/ModelingToolsEditorMode/Public/ModelingToolsEditorModeSettings.h` (Public)


#### enum `EModelingModeDefaultMeshObjectType`  
`enum class EModelingModeDefaultMeshObjectType`  
_L15-23_
- reflection: `UENUM()`
- L18 _public enumerator_ `StaticMeshAsset` — Generate a new Static Mesh Asset (using Generated Asset settings below) and AStaticMeshActor
- L20 _public enumerator_ `VolumeActor` — Generate a new AVolume Actor
- L22 _public enumerator_ `DynamicMeshActor` — Generate a new ADynamicMeshActor (stored locally in the Level)

#### enum `EModelingModeAssetGenerationBehavior`  
`enum class EModelingModeAssetGenerationBehavior`  
_L28-38_
- reflection: `UENUM()`
- L31 _public enumerator_ `AutoGenerateAndAutosave` — Generate and automatically Save new Assets on creation
- L34 _public enumerator_ `AutoGenerateButDoNotAutosave` — Generate new Assets and mark as Modified but do not automatically Save
- L37 _public enumerator_ `InteractivePromptToSave` — Prompt to Save each new Asset upon Creation

#### enum `EModelingModeAssetGenerationLocation`  
`enum class EModelingModeAssetGenerationLocation`  
_L43-53_
- reflection: `UENUM()`
- L46 _public enumerator_ `AutoGeneratedWorldRelativeAssetPath` — All generated assets will be stored in an AutoGenerated folder that is located relative to the World they are being saved in
- L49 _public enumerator_ `AutoGeneratedGlobalAssetPath` — All generated assets will be stored in a root-level AutoGenerated folder
- L52 _public enumerator_ `CurrentAssetBrowserPathIfAvailable` — Generated assets will be stored in the currently-visible Asset Browser folder if available, otherwise at the Auto Generated Asset Path

#### class `UModelingToolsEditorModeSettings`  
`class UModelingToolsEditorModeSettings : public UDeveloperSettings`  
_L60-231_
- reflection: `UCLASS(MinimalAPI, config=Editor)`
- inherits: `UDeveloperSettings`
- desc: Settings for the Modeling Tools Editor Mode plug-in.
- L68 _public function_ `virtual FName GetContainerName() const override`
- L69 _public function_ `virtual FName GetCategoryName() const override`
- L70 _public function_ `virtual FName GetSectionName() const override`
- L72 _public prototype_ `virtual FText GetSectionText() const override;`
- L73 _public prototype_ `virtual FText GetSectionDescription() const override;`
- L79 _protected member_ `bool bEnableDynamicMeshActors = false;` — `UPROPERTY()` — Enable/Disable the options to emit Dynamic Mesh Actors in Modeling Mode Tools
- L83 _protected member_ `EModelingModeAssetGenerationLocation AssetGenerationLocation = EModelingModeAssetGenerationLocation::AutoGeneratedWorldRelativeAssetPath;` — `UPROPERTY(config, EditAnywhere, Category = "Modeling Mode|Generated Assets")` — Where should Assets auto-generated by Modeling Tools be stored by default
- L87 _protected member_ `EModelingModeAssetGenerationBehavior AssetGenerationMode = EModelingModeAssetGenerationBehavior::AutoGenerateButDoNotAutosave;` — `UPROPERTY(config, EditAnywhere, Category = "Modeling Mode|Generated Assets")` — How should Assets auto-generated by Modeling Tools be handled in terms of saving, naming, etc
- L91 _public function_ `EModelingModeAssetGenerationLocation GetAssetGenerationLocation() const`
- L98 _public function_ `void SetAssetGenerationLocation(const EModelingModeAssetGenerationLocation Location)`
- L103 _public function_ `EModelingModeAssetGenerationBehavior GetAssetGenerationMode() const`
- L110 _public function_ `void SetAssetGenerationMode(const EModelingModeAssetGenerationBehavior Mode)`
- L117 _public member_ `EModelingModeDefaultMeshObjectType DefaultMeshObjectType = EModelingModeDefaultMeshObjectType::StaticMeshAsset;` — `UPROPERTY(config, EditAnywhere, Category = "Modeling Mode")` — What type of Mesh Object should Output Type Setting default to in Modeling Mode Tools (takes effect after Editor restart)
- L121 _public member_ `FString AutoGeneratedAssetPath = TEXT("_GE` — `UPROPERTY(config, EditAnywhere, Category = "Modeling Mode|Generated Assets")` — Assets auto-generated by Modeling Tools are stored at this path, relative to the parent path defined by the Location. Set to an empty string to disable.
- L125 _public member_ `bool bStoreUnsavedLevelAssetsInTopLevelGameFolder = true;` — `UPROPERTY(config, EditAnywhere, Category = "Modeling Mode|Generated Assets")` — If true, Auto-Generated Assets created in an unsaved Level will be stored relative to top-level folder, otherwise they will be stored in /Temp and cannot be saved until they are explicitly moved to a permanent location
- L129 _public member_ `bool bUsePerUserAutogenSubfolder = true;` — `UPROPERTY(config, EditAnywhere, Category = "Modeling Mode|Generated Assets")` — If true, Autogenerated Assets are stored in per-user folders below the Autogen path
- L133 _public member_ `FString AutogenSubfolderUserNameOverride;` — `UPROPERTY(config, EditAnywhere, Category = "Modeling Mode|Generated Assets")` — Overrides the user name used for per-user folders below the Autogen path. This might be necessary to resolve issues with source control, for example. Note that the per-user folder name might not contain the name exactly as provided.
- L137 _public member_ `bool bAppendRandomStringToName = true;` — `UPROPERTY(config, EditAnywhere, Category = "Modeling Mode|Generated Assets")` — If true, Autogenerated Assets have a short random string generated and appended to their name
- L145 _public member_ `bool bRespectLevelEditorGizmoMode = false;` — `UPROPERTY(config, EditAnywhere, Category = "Modeling Mode|User Interface")` — If true, the standard UE Editor Gizmo Mode (ie selected via the Level Editor Viewport toggle) will be used to configure the Modeling Gizmo, otherwise a Combined Gizmo will always be used. It may be necessary to exit and re-enter Modeling Mode after changing this setting.
- L154 _public member_ `bool bEnablePersistentSelections = false;` — `UPROPERTY(config, EditAnywhere, Category = "Modeling Mode|Selection", meta = (DisplayName="Enable Mesh Selection UI"))` — `UPROPERTY()`
- L159 _public member_ `bool bEnableMeshSelections = true;` — `UPROPERTY(config, EditAnywhere, Category = "Modeling Mode|Selection", meta = (DisplayName="Enable Mesh Selection UI"))` — Enable/Disable the Mesh Selection System.
- L161 _public function_ `virtual bool GetMeshSelectionsEnabled() const`
- L166 _public function_ `virtual void SetMeshSelectionsEnabled(bool bEnabled)`
- L172 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(UModelingToolsEditorModeSettingsModified, UObject*, FProperty*);`
- L173 _public member_ `UModelingToolsEditorModeSettingsModified OnModified;`
- L175 _public function_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override`
- L186 _public function_ `virtual bool InRestrictiveMode() const`
- L191 _public function_ `virtual void SetRestrictiveMode(bool bEnabled)`
- L196 _public function_ `virtual FString GetRestrictiveModeAutoGeneratedAssetPath() const`
- L201 _public function_ `virtual bool SetRestrictiveModeAutoGeneratedAssetPath(const FString& AssetPath)`
- L215 _protected member_ `FString RestrictiveModeAutoGeneratedAssetPath = TEXT("Mes` — `UPROPERTY(Config)` — Assets auto-generated by Modeling Tools are stored at this path when in restrictive mode, relative to the package folder path.
- L217 _protected member_ `bool bRestrictiveMode = false;`
- L230 _public member_ `bool bEnableAbsoluteWorldSnapping = false;` — `UPROPERTY(Transient)` — Toggle Absolute World Grid Position snapping

#### struct `FModelingModeCustomSectionColor`  
`struct FModelingModeCustomSectionColor`  
_L240-251_
- reflection: `USTRUCT()`
- desc: Defines a color to be used for a particular Tool Palette Section
- L246 _public member_ `FString SectionName = TEXT("");` — `UPROPERTY(EditAnywhere, Category = "SectionColor")` — Name of Section in Modeling Mode Tool Palette
- L250 _public member_ `FLinearColor Color = FLinearColor::Gray;` — `UPROPERTY(EditAnywhere, Category = "SectionColor")` — Custom Header Color

#### struct `FModelingModeCustomToolColor`  
`struct FModelingModeCustomToolColor`  
_L258-275_
- reflection: `USTRUCT()`
- desc: Defines a color to be used for a particular Tool Palette Tool
- L270 _public member_ `FString ToolName = TEXT("");` — `UPROPERTY(EditAnywhere, Category = "ToolColor")` — Name of Section or Tool in Modeling Mode Tool Palette Format: SectionName        (Specifies a default color for all tools in the section.) SectionName.ToolName        (Specifies an override color for a specific tool in the given section.)
- L274 _public member_ `FLinearColor Color = FLinearColor::Gray;` — `UPROPERTY(EditAnywhere, Category = "ToolColor")` — Custom Tool Color

#### struct `FModelingModeAssetCollectionSet`  
`struct FModelingModeAssetCollectionSet`  
_L282-293_
- reflection: `USTRUCT()`
- desc: Defines a Named list/set of content-browser Collection names
- L288 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, Category = "CollectionSet")` — Name of the set of collections
- L292 _public member_ `TArray<FCollectionReference> Collections;` — `UPROPERTY(EditAnywhere, Category = "CollectionSet")` — List of Collection names

#### class `UModelingToolsModeCustomizationSettings`  
`class UModelingToolsModeCustomizationSettings : public UDeveloperSettings`  
_L297-420_
- reflection: `UCLASS(MinimalAPI, config=Editor)`
- inherits: `UDeveloperSettings`
- L304 _public function_ `virtual FName GetContainerName() const`
- L305 _public function_ `virtual FName GetCategoryName() const`
- L306 _public function_ `virtual FName GetSectionName() const`
- L308 _public prototype_ `virtual FText GetSectionText() const override;`
- L309 _public prototype_ `virtual FText GetSectionDescription() const override;`
- L315 _public member_ `bool bUseLegacyModelingPalette = false;` — `UPROPERTY(config, EditAnywhere, Category = "Modeling Mode|UI Customization")` — Toggle between the Legacy Modeling Mode Palette and the new UI (requires exiting and re-entering the Mode)
- L319 _public member_ `TArray<FString> ToolSectionOrder;` — `UPROPERTY(config, EditAnywhere, Category = "Modeling Mode|UI Customization")` — Add the names of Modeling Mode Tool Palette Sections to have them appear at the top of the Tool Palette, in the order listed below.
- L323 _public member_ `TArray<FString> ToolFavorites;` — `UE_DEPRECATED(5.3, "Modeling Mode favorites are now set through FEditablePalette or the Mode UI itself")` — Tool Names listed in the array below will appear in a Favorites section at the top of the Modeling Mode Tool Palette
- L327 _public member_ `TArray<FModelingModeCustomSectionColor> SectionColors;` — `UPROPERTY(config, EditAnywhere, Category = "Modeling Mode|UI Customization")` — Custom Section Header Colors for listed Sections in the Modeling Mode Tool Palette
- L337 _public member_ `TArray<FModelingModeCustomToolColor> ToolColors;` — `UPROPERTY(config, EditAnywhere, Category = "Modeling Mode|UI Customization")` — Custom Tool Colors for listed Tools in the Modeling Mode Tool Palette. Format: SectionName        (Specifies a default color for all tools in the section.) SectionName.ToolName        (Specifies an override color for a specific tool in the given section.)
- L345 _public member_ `TArray<FModelingModeAssetCollectionSet> BrushAlphaSets;` — `UPROPERTY(config, EditAnywhere, Category = "Modeling Mode|Tool Assets")` — A Brush Alpha Set is a named list of Content Browser Collections, which will be shown as a separate tab in the Texture Asset Picker used in various Modeling Mode Tools when selecting a Brush Alpha (eg in Sculpting)
- L352 _public member_ `bool bShowCategoryButtonLabels = true;` — `UPROPERTY(config, EditAnywhere, Category = "Modeling Mode|UI Customization")` — If true, the category labels will be shown on the toolbar buttons, else they will be hidden
- L358 _public member_ `bool bAlwaysShowToolButtons = false;` — `UPROPERTY(config, EditAnywhere, Category = "Modeling Mode|UI Customization")` — If true, Tool buttons will always be shown when in a Tool. By default they will be hidden.
- L364 _public member_ `FLinearColor UnselectedColor = FLinearColor(.068478f, 0.56478f, 0.708376f,.5f);` — `UPROPERTY(Config, EditAnywhere, Category = "Modeling Mode|Mesh Element Selection Mode")` — Custom color for when geometry is not a part of current selection when using Mesh Element Selection
- L370 _public member_ `FLinearColor HoverOverSelectedColor = FLinearColor(1.0f, 0.943014f, 0.74f);` — `UPROPERTY(Config, EditAnywhere, Category = "Modeling Mode|Mesh Element Selection Mode")` — Custom color hovering over selected geometry in Mesh Element Selection
- L376 _public member_ `FLinearColor HoverOverUnselectedColor = FLinearColor(1.0f, 0.25f, 0.712328f, .5f);` — `UPROPERTY(Config, EditAnywhere, Category = "Modeling Mode|Mesh Element Selection Mode")` — Custom color hovering over unselected geometry in Mesh Element Selection
- L382 _public member_ `FLinearColor GeometrySelectedColor = FLinearColor(0.982251f, 0.672443f, 0.029557f, .5f);` — `UPROPERTY(Config, EditAnywhere, Category = "Modeling Mode|Mesh Element Selection Mode")` — Custom color for when geometry is a part of the current selection when using Mesh Element Selection
- L388 _public member_ `FLinearColor GeometrySoftSelectedColor = FLinearColor(0.063f, 0.161f, 0.71f, .5f);` — `UPROPERTY(Config, EditAnywhere, Category = "Modeling Mode|Mesh Element Selection Mode")` — Custom color for when geometry is a part of the soft selection when using Mesh Element Selection
- L395 _public member_ `int32 LastMeshSelectionDragMode = 0;` — `UPROPERTY(config)`
- L398 _public member_ `int32 LastMeshSelectionLocalFrameMode = 0;` — `UPROPERTY(config)`
- L401 _public member_ `bool bMeshSelectionHitBackFaces = true;` — `UPROPERTY(config)`
- L408 _public member_ `int32 LastMeshSelectionElementType = 0;` — `UPROPERTY()`
- L411 _public member_ `int32 LastMeshSelectionTopologyMode = 0;` — `UPROPERTY()`
- L414 _public member_ `bool bLastMeshSelectionVolumeToggle = true;` — `UPROPERTY()`
- L417 _public member_ `bool bLastMeshSelectionStaticMeshToggle = true;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MODELINGTOOLSEDITORMODE_API`
- L172 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(UModelingToolsEditorModeSettingsModified, UObject*, FProperty*);`

### `Plugins/Editor/ModelingToolsEditorMode/Source/ModelingToolsEditorMode/Public/ModelingToolsEditorModeStyle.h` (Public)


#### class `FModelingToolsEditorModeStyle`  
`class FModelingToolsEditorModeStyle`  
_L11-30_
- L14 _public prototype_ `static void Initialize();`
- L16 _public prototype_ `static void Shutdown();`
- L18 _public prototype_ `static TSharedPtr< class ISlateStyle > Get();`
- L20 _public prototype_ `static FName GetStyleSetName();`
- L23 _public prototype_ `static const FSlateBrush* GetBrush(FName PropertyName, const ANSICHAR* Specifier = NULL);` — use to access icons defined by the style set by name, eg GetBrush("BrushFalloffIcons.Smooth")
- L26 _private prototype_ `static FString InContent(const FString& RelativePath, const ANSICHAR* Extension);`
- L29 _private member_ `static TSharedPtr< class FSlateStyleSet > StyleSet;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MODELINGTOOLSEDITORMODE_API`

### `Plugins/Editor/ModelingToolsEditorMode/Source/ModelingToolsEditorMode/Public/ModelingToolsEditorModeToolkit.h` (Public)


#### struct `FToolPresetOption`  
`struct FToolPresetOption`  
_L33-40_
- L35 _public member_ `FString PresetLabel;`
- L36 _public member_ `FString PresetTooltip;`
- L37 _public member_ `FSlateIcon PresetIcon;`
- L38 _public member_ `int32 PresetIndex;`
- L39 _public member_ `FSoftObjectPath PresetCollection;`

#### class `FModelingToolsEditorModeToolkit`  
`class FModelingToolsEditorModeToolkit : public FModeToolkit`  
_L42-237_
- inherits: `FModeToolkit`
- L46 _public prototype_ `FModelingToolsEditorModeToolkit();`
- L47 _public prototype_ `~FModelingToolsEditorModeToolkit();`
- L50 _public prototype_ `virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode) override;` — FModeToolkit interface
- L53 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L54 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L55 _public prototype_ `virtual TSharedPtr<class SWidget> GetInlineContent() const override;`
- L58 _public prototype_ `virtual void InitializeAfterModeSetup();` — initialize toolkit widgets that need to wait until mode is initialized/entered
- L61 _public prototype_ `virtual void PostNotification(const FText& Message);` — set/clear notification message area
- L62 _public prototype_ `virtual void ClearNotification();`
- L65 _public prototype_ `virtual void PostWarning(const FText& Message);` — set/clear warning message area
- L66 _public prototype_ `virtual void ClearWarning();`
- L69 _public prototype_ `virtual void GetToolPaletteNames(TArray<FName>& InPaletteName) const;` — Returns the Mode specific tabs in the mode toolbar
- L70 _public prototype_ `virtual FText GetToolPaletteDisplayName(FName PaletteName) const;`
- L71 _public prototype_ `virtual void BuildToolPalette(FName PaletteName, class FToolBarBuilder& ToolbarBuilder);`
- L72 _public prototype_ `virtual void OnToolPaletteChanged(FName PaletteName) override;`
- L73 _public function_ `virtual bool HasIntegratedToolPalettes() const`
- L74 _public function_ `virtual bool HasExclusiveToolPalettes() const`
- L76 _public function_ `virtual FText GetActiveToolDisplayName() const override`
- L77 _public function_ `virtual FText GetActiveToolMessage() const override`
- L79 _public prototype_ `virtual void ShowRealtimeAndModeWarnings(bool bShowRealtimeWarning);`
- L81 _public prototype_ `virtual void OnToolStarted(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L82 _public prototype_ `virtual void OnToolEnded(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L84 _public prototype_ `virtual void CustomizeModeDetailsViewArgs(FDetailsViewArgs& ArgsInOut) override;`
- L86 _public prototype_ `void OnActiveViewportChanged(TSharedPtr<IAssetViewport>, TSharedPtr<IAssetViewport> );`
- L88 _public prototype_ `virtual void InvokeUI() override;`
- L89 _public prototype_ `virtual void ShutdownUI() override;`
- L90 _public prototype_ `virtual void ExtendSecondaryModeToolbar(UToolMenu *InModeToolbarMenu) override;`
- L92 _public prototype_ `virtual bool RequestAcceptCancelButtonOverride(IToolHostCustomizationAPI::FAcceptCancelButtonOverrideParams& Params);`
- L93 _public prototype_ `virtual bool RequestCompleteButtonOverride(IToolHostCustomizationAPI::FCompleteButtonOverrideParams& Params);`
- L94 _public prototype_ `virtual void ClearButtonOverrides();`
- L97 _public prototype_ `virtual FText GetRestrictiveModeAutoGeneratedAssetPathText() const;` — Read and write Autogen Subfolder quick setting in restrictive mode.
- L98 _public prototype_ `virtual void OnRestrictiveModeAutoGeneratedAssetPathTextCommitted(const FText& InNewText, ETextCommit::Type InTextCommit) const;`
- L100 _public prototype_ `virtual void ForceToolPaletteRebuild();`
- L104 _public prototype_ `void BindGizmoNumericalUI();` — The mode is expected to call this after setting up the gizmo context object so that any subsequently created gizmos are bound to the numerical UI.
- L107 _public prototype_ `UGeometrySelectionManager* GetMeshSelectionManager();` — get cached UGeometrySelectionManager pointer for the current Mode
- L110 _public function_ `bool IsInActiveTool() const` — @return true if we are currently in a tool, used to enable/disable UI things
- L114 _public function_ `TSharedPtr<STransformGizmoNumericalUIOverlay> GetGizmoNumericalUIOverlayWidget()` — This is exposed only for the convenience of being able to create the numerical UI submenu in a non-member function in ModelingModeToolkit_Toolbars.cpp
- L116 _public prototype_ `void NotifySelectionSystemEnabledStateModified();`
- L119 _public prototype_ `void DisconnectStylusStateProviderAPI();` — Tells the stylus API to clean up any active tracked windows / contexts
- L121 _public prototype_ `IToolStylusStateProviderAPI* GetStylusStateProviderAPI() const;`
- L124 _private member_ `const static TArray<FName> PaletteNames_Standard;`
- L126 _private member_ `bool bInActiveTool = false;`
- L127 _private member_ `FText ActiveToolName;`
- L128 _private member_ `FText ActiveToolMessage;`
- L129 _private member_ `FStatusBarMessageHandle ActiveToolMessageHandle;`
- L130 _private member_ `const FSlateBrush* ActiveToolIcon = nullptr;`
- L132 _private member_ `TOptional<IToolHostCustomizationAPI::FAcceptCancelButtonOverrideParams> AcceptCancelButtonParams;`
- L133 _private member_ `TOptional<IToolHostCustomizationAPI::FCompleteButtonOverrideParams> CompleteButtonParams;`
- L134 _private member_ `bool bCurrentOverrideButtonsWereClicked = false;`
- L136 _private prototype_ `FReply HandleAcceptCancelClick(bool bAccept);`
- L137 _private prototype_ `FReply HandleCompleteClick();`
- L139 _private member_ `UGeometrySelectionManager* CachedSelectionManager = nullptr;`
- L141 _private member_ `TSharedPtr<SWidget> ToolkitWidget;`
- L142 _private prototype_ `void UpdateActiveToolProperties();`
- L143 _private prototype_ `void InvalidateCachedDetailPanelState(UObject* ChangedObject);`
- L146 _private prototype_ `void RegisterPalettes();` — A utility function to register the tool palettes with the ToolkitBuilder
- L147 _private member_ `FDelegateHandle ActivePaletteChangedHandle;`
- L149 _private member_ `TSharedPtr<SWidget> ToolShutdownViewportOverlayWidget;`
- L150 _private prototype_ `void MakeToolShutdownOverlayWidget();`
- L152 _private prototype_ `void MakeGizmoNumericalUIOverlayWidget();`
- L153 _private member_ `TSharedPtr<STransformGizmoNumericalUIOverlay> GizmoNumericalUIOverlayWidget;`
- L155 _private prototype_ `TSharedRef<SWidget> MakeMenu_ModelingModeConfigSettings();`
- L157 _private member_ `TSharedPtr<STextBlock> ModeWarningArea;`
- L158 _private member_ `TSharedPtr<STextBlock> ModeHeaderArea;`
- L159 _private member_ `TSharedPtr<STextBlock> ToolWarningArea;`
- L160 _private member_ `TSharedPtr<SButton> AcceptButton;`
- L161 _private member_ `TSharedPtr<SButton> CancelButton;`
- L162 _private member_ `TSharedPtr<SButton> CompletedButton;`
- L164 _private prototype_ `TSharedPtr<SWidget> MakeAssetConfigPanel();`
- L166 _private member_ `FText ActiveWarning{};`
- L168 _private member_ `TArray<TSharedPtr<FString>> AssetLocationModes;`
- L169 _private member_ `TArray<TSharedPtr<FString>> AssetSaveModes;`
- L170 _private member_ `TSharedPtr<STextComboBox> AssetLocationMode;`
- L171 _private member_ `TSharedPtr<STextComboBox> AssetSaveMode;`
- L172 _private member_ `TSharedPtr<SEditableTextBox> NewAssetPath;`
- L173 _private prototype_ `void UpdateAssetLocationMode(TSharedPtr<FString> NewString);`
- L174 _private prototype_ `void UpdateAssetSaveMode(TSharedPtr<FString> NewString);`
- L175 _private prototype_ `void UpdateAssetPanelFromSettings();`
- L176 _private prototype_ `void UpdateObjectCreationOptionsFromSettings();`
- L177 _private prototype_ `void OnAssetSettingsModified();`
- L178 _private member_ `FDelegateHandle AssetSettingsModifiedHandle;`
- L179 _private prototype_ `void OnShowAssetSettings();`
- L180 _private prototype_ `void SelectNewAssetPath() const;`
- L183 _private member_ `TSharedPtr<SWidget> ToolPresetArea;` — Presets
- L184 _private prototype_ `TSharedPtr<SWidget> MakePresetPanel();`
- L185 _private member_ `TSharedPtr<FAssetData> CurrentPreset;`
- L186 _private member_ `FSoftObjectPath CurrentPresetPath;`
- L187 _private member_ `FText CurrentPresetLabel;`
- L188 _private member_ `FToolPresetOption SelectedPresetToEdit;`
- L189 _private member_ `FString NewPresetLabel;`
- L190 _private member_ `FString NewPresetTooltip;`
- L191 _private member_ `FSlateIcon NewPresetIcon;`
- L193 _private member_ `TArray<TSharedPtr<FToolPresetOption>> AvailablePresetsForTool;`
- L194 _private member_ `TSharedPtr<SEditableComboBox<TSharedPtr<FString>>> PresetComboBox;`
- L195 _private member_ `TSharedPtr<FRecentPresetCollectionProvider> RecentPresetCollectionProvider;`
- L197 _private prototype_ `TSharedRef<SWidget> GetPresetCreateButtonContent();`
- L199 _private prototype_ `void CreateNewPresetInCollection(const FString& PresetLabel, FSoftObjectPath CollectionPath, const FString& ToolTip, FSlateIcon Icon);`
- L200 _private prototype_ `void LoadPresetFromCollection(const int32 PresetIndex, FSoftObjectPath CollectionPath);`
- L201 _private prototype_ `void UpdatePresetInCollection(const FToolPresetOption& PresetToEditIn, bool bUpdateStoredPresetValues);`
- L203 _private function_ `FString GetCurrentPresetPath()`
- L204 _private prototype_ `void HandlePresetAssetChanged(const FAssetData& InAssetData);`
- L205 _private prototype_ `bool HandleFilterPresetAsset(const FAssetData& InAssetData);`
- L207 _private prototype_ `void RebuildPresetListForTool(bool bSettingsOpened);`
- L208 _private prototype_ `TSharedRef<SWidget> MakePresetComboWidget(TSharedPtr<FString> InItem);`
- L209 _private prototype_ `bool IsPresetEnabled() const;`
- L210 _private prototype_ `void ClearPresetComboList();`
- L215 _private prototype_ `void UpdateCategoryButtonLabelVisibility(UObject* Obj, FPropertyChangedEvent& ChangeEvent);` — Updates the category button labels' visibility based off of the current editor preference for it
- L220 _private prototype_ `void UpdateSelectionColors(UObject* Obj, FPropertyChangedEvent& ChangeEvent) const;` — Updates the mesh element selection colors based off of the current editor preference for it
- L222 _private member_ `TArray<TSharedPtr<FString>> AssetLODModes;`
- L223 _private member_ `TSharedPtr<STextBlock> AssetLODModeLabel;`
- L224 _private member_ `TSharedPtr<STextComboBox> AssetLODMode;`
- L225 _private member_ `TSharedPtr<FEditablePalette> FavoritesPalette;`
- L227 _private member_ `bool bFirstInitializeAfterModeSetup = true;`
- L228 _private member_ `bool bShowActiveSelectionActions = true;`
- L231 _private member_ `TUniquePtr<UE::Modeling::FStylusInputHandler> StylusInputHandler;`
- L235 _private prototype_ `bool EngineAssetsSelected() const;` — tests if selection includes components backed by assets from the /Engine folder, of types the tools might otherwise modify (currently, static meshes)

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace ETextCommit`
- L14 _macro_ `#define LOCTEXT_NAMESPACE "ModelingToolsEditorModeToolkit"`
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace Modeling` (scope `UE`)

### `Plugins/Editor/ModelingToolsEditorMode/Source/ModelingToolsEditorMode/Public/ModelingToolsHostCustomizationAPI.h` (Public)


#### class `UModelingToolsHostCustomizationAPI`  
`class UModelingToolsHostCustomizationAPI : public UObject, public IToolHostCustomizationAPI`  
_L20-42_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UObject,IToolHostCustomizationAPI`
- desc: An implementation of IToolHostCustomizationAPI meant to be used with modeling tools editor mode. Mostly it just forwards the relevant requests to the mode toolkit, which changes its accept/cancel/complete overlay buttons temporarily (until the next click of those buttons).
- L25 _public function_ `virtual bool SupportsAcceptCancelButtonOverride() override`
- L26 _public prototype_ `virtual bool RequestAcceptCancelButtonOverride(FAcceptCancelButtonOverrideParams& Params) override;`
- L28 _public function_ `virtual bool SupportsCompleteButtonOverride() override`
- L29 _public prototype_ `virtual bool RequestCompleteButtonOverride(FCompleteButtonOverrideParams& Params) override;`
- L31 _public prototype_ `virtual void ClearButtonOverrides() override;`
- L34 _public prototype_ `static UModelingToolsHostCustomizationAPI* Register(UInteractiveToolsContext* ToolsContext, TSharedRef<FModelingToolsEditorModeToolkit> Toolkit);` — Helper to create, initialize, and register a UModelingToolsHostCustomizationAPI object with the context store
- L38 _public prototype_ `static bool Deregister(UInteractiveToolsContext* ToolsContext);` — Helper to deregister the UModelingToolsHostCustomizationAPI from the context store
- L41 _protected member_ `TWeakPtr<FModelingToolsEditorModeToolkit> Toolkit;`

### `Plugins/Editor/ModelingToolsEditorMode/Source/ModelingToolsEditorMode/Public/ModelingToolsManagerActions.h` (Public)


#### class `FModelingToolsManagerCommands`  
`class FModelingToolsManagerCommands : public TCommands<FModelingToolsManagerCommands>`  
_L12-262_
- inherits: `TCommands<FModelingToolsManagerCommands>`
- desc: TInteractiveToolCommands implementation for Modeling Mode Tools
- L15 _public prototype_ `FModelingToolsManagerCommands();`
- L26 _protected member_ `TArray<FStartToolCommand> RegisteredTools;` — Tool start-commands listed below are stored in this list
- L33 _protected member_ `TArray<FDynamicExtensionCommand> ExtensionPaletteCommands;`
- L39 _public prototype_ `TSharedPtr<FUICommandInfo> FindToolByName(FString Name, bool& bFound) const;` — Find Tool start-command below by registered name (tool icon name in Mode palette)
- L45 _public prototype_ `FText GetCommandLabel(TSharedPtr<const FUICommandInfo> Command, bool bShortName) const;` — Helper that gets the regular command label (result of GetLabel) or a shortened version if one was registered and bShortName is true.
- L51 _public member_ `TSharedPtr<FUICommandInfo> BeginAddBoxPrimitiveTool;`
- L52 _public member_ `TSharedPtr<FUICommandInfo> BeginAddCylinderPrimitiveTool;`
- L53 _public member_ `TSharedPtr<FUICommandInfo> BeginAddCapsulePrimitiveTool;`
- L54 _public member_ `TSharedPtr<FUICommandInfo> BeginAddConePrimitiveTool;`
- L55 _public member_ `TSharedPtr<FUICommandInfo> BeginAddArrowPrimitiveTool;`
- L56 _public member_ `TSharedPtr<FUICommandInfo> BeginAddRectanglePrimitiveTool;`
- L57 _public member_ `TSharedPtr<FUICommandInfo> BeginAddDiscPrimitiveTool;`
- L58 _public member_ `TSharedPtr<FUICommandInfo> BeginAddTorusPrimitiveTool;`
- L59 _public member_ `TSharedPtr<FUICommandInfo> BeginAddSpherePrimitiveTool;`
- L60 _public member_ `TSharedPtr<FUICommandInfo> BeginAddStairsPrimitiveTool;`
- L62 _public member_ `TSharedPtr<FUICommandInfo> BeginAddPatchTool;`
- L63 _public member_ `TSharedPtr<FUICommandInfo> BeginRevolveBoundaryTool;`
- L64 _public member_ `TSharedPtr<FUICommandInfo> BeginDrawPolygonTool;`
- L65 _public member_ `TSharedPtr<FUICommandInfo> BeginDrawPolyPathTool;`
- L66 _public member_ `TSharedPtr<FUICommandInfo> BeginDrawAndRevolveTool;`
- L67 _public member_ `TSharedPtr<FUICommandInfo> BeginRevolveSplineTool;`
- L68 _public member_ `TSharedPtr<FUICommandInfo> BeginShapeSprayTool;`
- L69 _public member_ `TSharedPtr<FUICommandInfo> BeginDrawSplineTool;`
- L70 _public member_ `TSharedPtr<FUICommandInfo> BeginExtractSplineTool;`
- L71 _public member_ `TSharedPtr<FUICommandInfo> BeginTriangulateSplinesTool;`
- L73 _public member_ `TSharedPtr<FUICommandInfo> BeginSculptMeshTool;`
- L74 _public member_ `TSharedPtr<FUICommandInfo> BeginCubeGridTool;`
- L75 _public member_ `TSharedPtr<FUICommandInfo> BeginPolyEditTool;`
- L76 _public member_ `TSharedPtr<FUICommandInfo> BeginSubdividePolyTool;`
- L77 _public member_ `TSharedPtr<FUICommandInfo> BeginTriEditTool;`
- L78 _public member_ `TSharedPtr<FUICommandInfo> BeginPolyDeformTool;`
- L79 _public member_ `TSharedPtr<FUICommandInfo> BeginSmoothMeshTool;`
- L80 _public member_ `TSharedPtr<FUICommandInfo> BeginOffsetMeshTool;`
- L81 _public member_ `TSharedPtr<FUICommandInfo> BeginDisplaceMeshTool;`
- L82 _public member_ `TSharedPtr<FUICommandInfo> BeginMeshSpaceDeformerTool;`
- L83 _public member_ `TSharedPtr<FUICommandInfo> BeginTransformMeshesTool;`
- L84 _public member_ `TSharedPtr<FUICommandInfo> BeginEditPivotTool;`
- L85 _public member_ `TSharedPtr<FUICommandInfo> BeginAddPivotActorTool;`
- L86 _public member_ `TSharedPtr<FUICommandInfo> BeginBakeTransformTool;`
- L87 _public member_ `TSharedPtr<FUICommandInfo> BeginCombineMeshesTool;`
- L88 _public member_ `TSharedPtr<FUICommandInfo> BeginDuplicateMeshesTool;`
- L89 _public member_ `TSharedPtr<FUICommandInfo> BeginAlignObjectsTool;`
- L90 _public member_ `TSharedPtr<FUICommandInfo> BeginTransferMeshTool;`
- L91 _public member_ `TSharedPtr<FUICommandInfo> BeginConvertMeshesTool;`
- L92 _public member_ `TSharedPtr<FUICommandInfo> BeginSplitMeshesTool;`
- L93 _public member_ `TSharedPtr<FUICommandInfo> BeginPatternTool;`
- L94 _public member_ `TSharedPtr<FUICommandInfo> BeginHarvestInstancesTool;`
- L97 _public member_ `TSharedPtr<FUICommandInfo> BeginRemeshSculptMeshTool;`
- L98 _public member_ `TSharedPtr<FUICommandInfo> BeginRemeshMeshTool;`
- L99 _public member_ `TSharedPtr<FUICommandInfo> BeginProjectToTargetTool;`
- L100 _public member_ `TSharedPtr<FUICommandInfo> BeginSimplifyMeshTool;`
- L101 _public member_ `TSharedPtr<FUICommandInfo> BeginEditNormalsTool;`
- L102 _public member_ `TSharedPtr<FUICommandInfo> BeginEditTangentsTool;`
- L103 _public member_ `TSharedPtr<FUICommandInfo> BeginRemoveOccludedTrianglesTool;`
- L104 _public member_ `TSharedPtr<FUICommandInfo> BeginUVProjectionTool;`
- L105 _public member_ `TSharedPtr<FUICommandInfo> BeginUVLayoutTool;`
- L106 _public member_ `TSharedPtr<FUICommandInfo> BeginUVTransferTool;`
- L107 _public member_ `TSharedPtr<FUICommandInfo> BeginPlaneCutTool;`
- L108 _public member_ `TSharedPtr<FUICommandInfo> BeginMirrorTool;`
- L109 _public member_ `TSharedPtr<FUICommandInfo> BeginHoleFillTool;`
- L110 _public member_ `TSharedPtr<FUICommandInfo> BeginLatticeDeformerTool;`
- L111 _public member_ `TSharedPtr<FUICommandInfo> BeginPolygonCutTool;`
- L114 _public member_ `TSharedPtr<FUICommandInfo> BeginVoxelMergeTool;`
- L115 _public member_ `TSharedPtr<FUICommandInfo> BeginVoxelBooleanTool;`
- L118 _public member_ `TSharedPtr<FUICommandInfo> BeginVoxelSolidifyTool;`
- L119 _public member_ `TSharedPtr<FUICommandInfo> BeginVoxelBlendTool;`
- L120 _public member_ `TSharedPtr<FUICommandInfo> BeginVoxelMorphologyTool;`
- L121 _public member_ `TSharedPtr<FUICommandInfo> BeginSelfUnionTool;`
- L122 _public member_ `TSharedPtr<FUICommandInfo> BeginMeshBooleanTool;`
- L123 _public member_ `TSharedPtr<FUICommandInfo> BeginMeshTrimTool;`
- L124 _public member_ `TSharedPtr<FUICommandInfo> BeginCutMeshWithMeshTool;`
- L125 _public member_ `TSharedPtr<FUICommandInfo> BeginMeshSelectionTool;`
- L126 _public member_ `TSharedPtr<FUICommandInfo> BeginBspConversionTool;`
- L127 _public member_ `TSharedPtr<FUICommandInfo> BeginMeshToVolumeTool;`
- L128 _public member_ `TSharedPtr<FUICommandInfo> BeginVolumeToMeshTool;`
- L129 _public member_ `TSharedPtr<FUICommandInfo> BeginMeshGroupPaintTool;`
- L130 _public member_ `TSharedPtr<FUICommandInfo> BeginMeshVertexPaintTool;`
- L132 _public member_ `TSharedPtr<FUICommandInfo> BeginPhysicsInspectorTool;`
- L133 _public member_ `TSharedPtr<FUICommandInfo> BeginSimpleCollisionEditorTool;`
- L134 _public member_ `TSharedPtr<FUICommandInfo> BeginSetCollisionGeometryTool;`
- L135 _public member_ `TSharedPtr<FUICommandInfo> BeginEditCollisionGeometryTool;`
- L136 _public member_ `TSharedPtr<FUICommandInfo> BeginExtractCollisionGeometryTool;`
- L138 _public member_ `TSharedPtr<FUICommandInfo> BeginMeshInspectorTool;`
- L139 _public member_ `TSharedPtr<FUICommandInfo> BeginGlobalUVGenerateTool;`
- L140 _public member_ `TSharedPtr<FUICommandInfo> BeginGroupUVGenerateTool;`
- L141 _public member_ `TSharedPtr<FUICommandInfo> BeginWeldEdgesTool;`
- L142 _public member_ `TSharedPtr<FUICommandInfo> BeginPolyGroupsTool;`
- L143 _public member_ `TSharedPtr<FUICommandInfo> BeginEditMeshMaterialsTool;`
- L144 _public member_ `TSharedPtr<FUICommandInfo> BeginTransformUVIslandsTool;`
- L145 _public member_ `TSharedPtr<FUICommandInfo> BeginMeshAttributePaintTool;`
- L146 _public member_ `TSharedPtr<FUICommandInfo> BeginAttributeEditorTool;`
- L147 _public member_ `TSharedPtr<FUICommandInfo> BeginBakeMeshAttributeMapsTool;`
- L148 _public member_ `TSharedPtr<FUICommandInfo> BeginBakeMultiMeshAttributeMapsTool;`
- L149 _public member_ `TSharedPtr<FUICommandInfo> BeginBakeRenderCaptureTool;`
- L150 _public member_ `TSharedPtr<FUICommandInfo> BeginBakeMeshAttributeVertexTool;`
- L151 _public member_ `TSharedPtr<FUICommandInfo> BeginUVSeamEditTool;`
- L153 _public member_ `TSharedPtr<FUICommandInfo> BeginSkinWeightsPaintTool;`
- L154 _public member_ `TSharedPtr<FUICommandInfo> BeginSkinWeightsBindingTool;`
- L156 _public member_ `TSharedPtr<FUICommandInfo> BeginSkeletonEditingTool;`
- L158 _public member_ `TSharedPtr<FUICommandInfo> BeginLODManagerTool;`
- L159 _public member_ `TSharedPtr<FUICommandInfo> BeginGenerateStaticMeshLODAssetTool;`
- L160 _public member_ `TSharedPtr<FUICommandInfo> BeginISMEditorTool;`
- L162 _public member_ `TSharedPtr<FUICommandInfo> BeginPolyModelTool_Inset;`
- L163 _public member_ `TSharedPtr<FUICommandInfo> BeginPolyModelTool_Outset;`
- L164 _public member_ `TSharedPtr<FUICommandInfo> BeginPolyModelTool_CutFaces;`
- L165 _public member_ `TSharedPtr<FUICommandInfo> BeginPolyModelTool_InsertEdgeLoop;`
- L166 _public member_ `TSharedPtr<FUICommandInfo> BeginPolyModelTool_ExtrudeEdges;`
- L167 _public member_ `TSharedPtr<FUICommandInfo> BeginPolyModelTool_PushPull;`
- L168 _public member_ `TSharedPtr<FUICommandInfo> BeginPolyModelTool_Bevel;`
- L170 _public member_ `TSharedPtr<FUICommandInfo> BeginPolyModelTool_PolyEd;`
- L171 _public member_ `TSharedPtr<FUICommandInfo> BeginPolyModelTool_TriSel;`
- L175 _public member_ `TSharedPtr<FUICommandInfo> MeshSelectionModeAction_NoSelection;` — selection state actions
- L176 _public member_ `TSharedPtr<FUICommandInfo> MeshSelectionModeAction_MeshTriangles;`
- L177 _public member_ `TSharedPtr<FUICommandInfo> MeshSelectionModeAction_MeshVertices;`
- L178 _public member_ `TSharedPtr<FUICommandInfo> MeshSelectionModeAction_MeshEdges;`
- L179 _public member_ `TSharedPtr<FUICommandInfo> MeshSelectionModeAction_GroupFaces;`
- L180 _public member_ `TSharedPtr<FUICommandInfo> MeshSelectionModeAction_GroupCorners;`
- L181 _public member_ `TSharedPtr<FUICommandInfo> MeshSelectionModeAction_GroupEdges;`
- L184 _public member_ `TSharedPtr<FUICommandInfo> BeginSelectionAction_Delete;`
- L185 _public member_ `TSharedPtr<FUICommandInfo> BeginSelectionAction_Disconnect;`
- L186 _public member_ `TSharedPtr<FUICommandInfo> BeginSelectionAction_Retriangulate;`
- L188 _public member_ `TSharedPtr<FUICommandInfo> BeginSelectionAction_SelectAll;`
- L189 _public member_ `TSharedPtr<FUICommandInfo> BeginSelectionAction_ExpandToConnected;`
- L190 _public member_ `TSharedPtr<FUICommandInfo> BeginSelectionAction_Invert;`
- L191 _public member_ `TSharedPtr<FUICommandInfo> BeginSelectionAction_InvertConnected;`
- L192 _public member_ `TSharedPtr<FUICommandInfo> BeginSelectionAction_Expand;`
- L193 _public member_ `TSharedPtr<FUICommandInfo> BeginSelectionAction_Contract;`
- L195 _public member_ `TSharedPtr<FUICommandInfo> BeginSelectionAction_Extrude;`
- L196 _public member_ `TSharedPtr<FUICommandInfo> BeginSelectionAction_Offset;`
- L198 _public member_ `TSharedPtr<FUICommandInfo> SelectionDragMode_None;`
- L199 _public member_ `TSharedPtr<FUICommandInfo> SelectionDragMode_Path;`
- L200 _public member_ `TSharedPtr<FUICommandInfo> SelectionLocalFrameMode_Geometry;`
- L201 _public member_ `TSharedPtr<FUICommandInfo> SelectionLocalFrameMode_Object;`
- L202 _public member_ `TSharedPtr<FUICommandInfo> SelectionMeshTypes_Volumes;`
- L203 _public member_ `TSharedPtr<FUICommandInfo> SelectionMeshTypes_StaticMeshes;`
- L204 _public member_ `TSharedPtr<FUICommandInfo> SelectionLocking;`
- L205 _public member_ `TSharedPtr<FUICommandInfo> SelectionHitBackFaces;`
- L206 _public member_ `TSharedPtr<FUICommandInfo> SelectionEnableSoftSelection;`
- L208 _public member_ `TSharedPtr<FUICommandInfo> AddToFavorites;`
- L209 _public member_ `TSharedPtr<FUICommandInfo> RemoveFromFavorites;`
- L210 _public member_ `TSharedPtr<FUICommandInfo> LoadFavoritesTools;`
- L211 _public member_ `TSharedPtr<FUICommandInfo> LoadSelectionTools;`
- L212 _public member_ `TSharedPtr<FUICommandInfo> LoadShapesTools;`
- L213 _public member_ `TSharedPtr<FUICommandInfo> LoadCreateTools;`
- L214 _public member_ `TSharedPtr<FUICommandInfo> LoadPolyTools;`
- L215 _public member_ `TSharedPtr<FUICommandInfo> LoadTriTools;`
- L216 _public member_ `TSharedPtr<FUICommandInfo> LoadDeformTools;`
- L217 _public member_ `TSharedPtr<FUICommandInfo> LoadTransformTools;`
- L218 _public member_ `TSharedPtr<FUICommandInfo> LoadMeshOpsTools;`
- L219 _public member_ `TSharedPtr<FUICommandInfo> LoadVoxOpsTools;`
- L220 _public member_ `TSharedPtr<FUICommandInfo> LoadAttributesTools;`
- L221 _public member_ `TSharedPtr<FUICommandInfo> LoadUVsTools;`
- L222 _public member_ `TSharedPtr<FUICommandInfo> LoadBakingTools;`
- L223 _public member_ `TSharedPtr<FUICommandInfo> LoadVolumeTools;`
- L224 _public member_ `TSharedPtr<FUICommandInfo> LoadLodsTools;`
- L226 _public member_ `TSharedPtr<FUICommandInfo> LaunchUVEditor;` — For connecting ModelingMode with UVEditor plugin
- L228 _public member_ `TSharedPtr<FUICommandInfo> LoadSkinTools;` — skeletal mesh editing tools
- L229 _public member_ `TSharedPtr<FUICommandInfo> LoadSkeletonTools;`
- L235 _public member_ `TSharedPtr<FUICommandInfo> AcceptActiveTool;`
- L236 _public member_ `TSharedPtr<FUICommandInfo> CancelActiveTool;`
- L237 _public member_ `TSharedPtr<FUICommandInfo> CompleteActiveTool;`
- L239 _public member_ `TSharedPtr<FUICommandInfo> AcceptOrCompleteActiveTool;`
- L240 _public member_ `TSharedPtr<FUICommandInfo> CancelOrCompleteActiveTool;`
- L245 _public prototype_ `virtual void RegisterCommands() override;` — Initialize above commands
- L253 _public prototype_ `static TSharedPtr<FUICommandInfo> RegisterExtensionPaletteCommand( FName Name, const FText& Label, const FText& Tooltip, const FSlateIcon& Icon);` — Dynamically register a new UI Command based on the given Name/Label/Tooltip/Icon. This is intended to be used outside of RegisterCommands(), eg by Modeling Mode extensions loaded when the Toolkit is created.
- L261 _private member_ `TMap<FUICommandInfo*, int32> CommandToRegisteredToolsIndex;` — Gets index into RegisteredTools for a given command.

#### struct `FModelingToolsManagerCommands::FStartToolCommand`  
`struct FStartToolCommand`  
_L18-25_
- L20 _public member_ `FString ToolUIName;`
- L21 _public member_ `TSharedPtr<FUICommandInfo> ToolCommand;`
- L24 _public member_ `FText ShortName;` — Optional (not used if empty). Only relevant if using short labels for tools

#### struct `FModelingToolsManagerCommands::FDynamicExtensionCommand`  
`struct FDynamicExtensionCommand`  
_L28-32_
- L30 _public member_ `FName RegistrationName;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> Command;`
