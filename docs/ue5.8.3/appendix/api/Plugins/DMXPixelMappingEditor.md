# Plugins / DMXPixelMappingEditor

- module root: `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor`
- headers: 51; symbols: 965
- symbol kinds: class=51, delegate=2, enum=4, enumerator=13, function=84, member=277, namespace=19, prototype=505, struct=8, typedef=2
- PrivateDependencyModuleNames: AppFramework, ApplicationCore, AssetDefinition, Core, CoreUObject, DMXEditor, DMXPixelMappingBlueprintGraph, DMXPixelMappingCore, DMXPixelMappingEditorWidgets, DMXPixelMappingRenderer, DMXPixelMappingRuntime, DMXRuntime, EditorStyle, Engine, InputCore, Projects, PropertyEditor, RHI, RenderCore, Slate, SlateCore, ToolMenus, ToolWidgets, UMG, UnrealEd

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/AssetDefinitions/AssetDefinition_DMXPixelMapping.h` (Private)


#### class `UAssetDefinition_DMXPixelMapping`  
`class UAssetDefinition_DMXPixelMapping : public UAssetDefinitionDefault`  
_L9-21_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L16 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L17 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L18 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L19 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Customizations/DMXPixelMappingColorSpaceDetails_RGBCMY.h` (Private)


#### class `FDMXPixelMappingColorSpaceDetails_RGBCMY`  
`class FDMXPixelMappingColorSpaceDetails_RGBCMY : public IDetailCustomization`  
_L15-57_
- inherits: `IDetailCustomization`
- desc: Details customization for the RGBCMY Color Space
- L20 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Creates an instance of this customization
- L23 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L38 _private prototype_ `void GenerateAttributeRow(IDetailLayoutBuilder& DetailBuilder, const FDMXAttributeRowData& AttributeRowData);` — Generates the row for one of the Attributes
- L41 _private prototype_ `FText GetRedAttributeDisplayName() const;` — Returns the Display Name of the Red Attribute
- L44 _private prototype_ `FText GetGreenAttributeDisplayName() const;` — Returns the Display Name of the Red Attribute
- L47 _private prototype_ `FText GetBlueAttributeDisplayName() const;` — Returns the Display Name of the Red Attribute
- L50 _private member_ `TSharedPtr<IPropertyHandle> SendCyanHandle;` — Property Handle for the bSendCyan Property
- L53 _private member_ `TSharedPtr<IPropertyHandle> SendMagentaHandle;` — Property Handle for the bSendMagenta Property
- L56 _private member_ `TSharedPtr<IPropertyHandle> SendYellowHandle;` — Property Handle for the bSendYellow Property

#### struct `FDMXPixelMappingColorSpaceDetails_RGBCMY::FDMXAttributeRowData`  
`struct FDMXAttributeRowData`  
_L28-35_
- desc: Holds required data to create an Attribute row
- L30 _public member_ `TSharedPtr<IPropertyHandle> AttributeHandle;`
- L31 _public member_ `TAttribute<FText> AttributeLabel;`
- L32 _public member_ `TSharedPtr<IPropertyHandle> IsInvertColorHandle;`
- L33 _public member_ `FText InvertColorLabel;`
- L34 _public member_ `bool bAppendSeparator = false;`

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Customizations/DMXPixelMappingDetailCustomization_FixtureGroup.h` (Private)


#### class `FDMXPixelMappingDetailCustomization_FixtureGroup`  
`class FDMXPixelMappingDetailCustomization_FixtureGroup : public IDetailCustomization`  
_L16-41_
- inherits: `IDetailCustomization`
- L20 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance(const TWeakPtr<FDMXPixelMappingToolkit> InToolkitWeakPtr)`
- L26 _public function_ `FDMXPixelMappingDetailCustomization_FixtureGroup(const TWeakPtr<FDMXPixelMappingToolkit> InToolkitWeakPtr) : ToolkitWeakPtr(InToolkitWeakPtr)` — Constructor
- L31 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L35 _private prototype_ `void OnComponentAddedOrRemoved(UDMXPixelMapping* PixelMapping, UDMXPixelMappingBaseComponent* Component);` — Called when a component was added or removed
- L38 _private member_ `TWeakPtr<FDMXPixelMappingToolkit> ToolkitWeakPtr;` — Weak reference to the DMX editor
- L40 _private member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;`

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Customizations/DMXPixelMappingDetailCustomization_FixtureGroupItem.h` (Private)


#### class `FDMXPixelMappingDetailCustomization_FixtureGroupItem`  
`class FDMXPixelMappingDetailCustomization_FixtureGroupItem : public IDetailCustomization`  
_L12-33_
- inherits: `IDetailCustomization`
- L16 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(const TWeakPtr<FDMXPixelMappingToolkit> InToolkitWeakPtr);`
- L18 _public prototype_ `FDMXPixelMappingDetailCustomization_FixtureGroupItem(const TWeakPtr<FDMXPixelMappingToolkit> InToolkitWeakPtr);`
- L21 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;`
- L26 _private prototype_ `bool CanEditEditorColor() const;` — Returns true if the EditorColor property is editable
- L29 _private member_ `TSharedPtr<IPropertyHandle> UsePatchColorHandle;` — Handle for the bUsePatchColor property
- L32 _private member_ `TWeakPtr<FDMXPixelMappingToolkit> ToolkitWeakPtr;` — Weak reference to the DMX editor

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Customizations/DMXPixelMappingDetailCustomization_Matrix.h` (Private)


#### class `FDMXPixelMappingDetailCustomization_Matrix`  
`class FDMXPixelMappingDetailCustomization_Matrix : public IDetailCustomization`  
_L12-32_
- inherits: `IDetailCustomization`
- L16 _public prototype_ `FDMXPixelMappingDetailCustomization_Matrix(const TWeakPtr<FDMXPixelMappingToolkit> InToolkitWeakPtr);`
- L18 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(const TWeakPtr<FDMXPixelMappingToolkit> InToolkitWeakPtr);`
- L21 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L25 _private prototype_ `bool CanEditEditorColor() const;` — Returns true if the EditorColor property is editable
- L28 _private member_ `TSharedPtr<IPropertyHandle> UsePatchColorHandle;` — Handle for the bUsePatchColor property
- L31 _private member_ `TWeakPtr<FDMXPixelMappingToolkit> ToolkitWeakPtr;` — Weak reference to the DMX editor

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Customizations/DMXPixelMappingDetailCustomization_OutputDMX.h` (Private)


#### class `FDMXPixelMappingDetailCustomization_OutputDMX`  
`class FDMXPixelMappingDetailCustomization_OutputDMX : public IDetailCustomization`  
_L12-42_
- inherits: `IDetailCustomization`
- L16 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance(const TWeakPtr<FDMXPixelMappingToolkit> InToolkitWeakPtr)`
- L22 _public function_ `FDMXPixelMappingDetailCustomization_OutputDMX(const TWeakPtr<FDMXPixelMappingToolkit> InToolkitWeakPtr) : ToolkitWeakPtr(InToolkitWeakPtr)` — Constructor
- L27 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;`
- L32 _private prototype_ `void CreateModulatorDetails(IDetailLayoutBuilder& InDetailLayout);` — Creates Details for the Output Modulators
- L35 _private prototype_ `void ForceRefresh();` — Forces the details to refresh
- L38 _private member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;` — Property utilities for this customization
- L41 _private member_ `TWeakPtr<FDMXPixelMappingToolkit> ToolkitWeakPtr;` — Weak reference to the DMX editor

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Customizations/DMXPixelMappingDetailCustomization_Renderer.h` (Private)


#### class `FDMXPixelMappingDetailCustomization_Renderer`  
`class FDMXPixelMappingDetailCustomization_Renderer : public IDetailCustomization`  
_L18-64_
- inherits: `IDetailCustomization`
- L22 _public prototype_ `FDMXPixelMappingDetailCustomization_Renderer(const TWeakPtr<FDMXPixelMappingToolkit> InWeakToolkit);`
- L24 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance(const TWeakPtr<FDMXPixelMappingToolkit> InWeakToolkit)`
- L30 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L34 _private prototype_ `void AddInputTextureWarning(IDetailCategoryBuilder& InCategory);` — Adds a warning if the input texture is not set
- L37 _private prototype_ `void AddMaterialDomainWarning(IDetailCategoryBuilder& InCategory);` — Add warning for material with domain != MD_UI
- L40 _private prototype_ `FText GetInputTextureWarningText() const;` — Returns the text displayed if the input texture is not set
- L43 _private prototype_ `EVisibility GetInputTextureWarningVisibility() const;` — Returns the visiblity of the input texture warning text
- L46 _private prototype_ `EVisibility GetMaterialDomainWarningVisibility() const;` — Returns the visibility of the input material domain
- L49 _private prototype_ `EDMXPixelMappingRendererType GetRendererType() const;` — Returns the current renderer type
- L51 _private member_ `TSharedPtr<IPropertyHandle> RendererTypeHandle;`
- L52 _private member_ `TSharedPtr<IPropertyHandle> InputTextureHandle;`
- L53 _private member_ `TSharedPtr<IPropertyHandle> InputMaterialHandle;`
- L54 _private member_ `TSharedPtr<IPropertyHandle> InputWidgetHandle;`
- L57 _private member_ `TWeakObjectPtr<UDMXPixelMappingRendererComponent> WeakRendererComponent;` — Renderer components being customized. Only valid if not multi editing
- L60 _private member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;` — Property utilities for this customization
- L63 _private member_ `TWeakPtr<FDMXPixelMappingToolkit> WeakToolkit;` — Weak reference to the DMX editor

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Customizations/DMXPixelMappingHorizontalAlignmentCustomization.h` (Private)


#### class `FDMXPixelMappingHorizontalAlignmentCustomization`  
`class FDMXPixelMappingHorizontalAlignmentCustomization : public IPropertyTypeCustomization`  
_L10-28_
- inherits: `IPropertyTypeCustomization`
- L15 _public prototype_ `static TSharedRef<class IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L18 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L19 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L24 _private prototype_ `EHorizontalAlignment GetAlignment(TSharedRef<IPropertyHandle> PropertyHandle) const;` — Returns the Aligment
- L27 _private prototype_ `void OnAlignmentChanged(EHorizontalAlignment NewAlignment, TSharedRef<IPropertyHandle> PropertyHandle);` — Called when the Alignment changed

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Customizations/DMXPixelMappingLayoutViewModelDetails.h` (Private)


#### class `FDMXPixelMappingLayoutViewModelDetails`  
`class FDMXPixelMappingLayoutViewModelDetails : public IDetailCustomization`  
_L17-69_
- inherits: `IDetailCustomization`
- desc: Details customization for the Layout View Model
- L22 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(const TWeakPtr<FDMXPixelMappingToolkit> InToolkitWeakPtr);` — Creates an instance of this customization
- L25 _public function_ `FDMXPixelMappingLayoutViewModelDetails(const TWeakPtr<FDMXPixelMappingToolkit> InToolkitWeakPtr) : WeakToolkit(InToolkitWeakPtr)` — Constructor
- L30 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;`
- L35 _private prototype_ `EVisibility GetAutoApplyPropertyVisiblity() const;` — Returns the visibility for the bAutoApply property
- L38 _private prototype_ `EVisibility GetApplyLayoutScriptButtonVisibility() const;` — Returns the visibility for the 'Apply Layout Script' button
- L41 _private prototype_ `FReply OnApplyLayoutScriptClicked();` — Called when the apply layout script button was clicked
- L44 _private prototype_ `void UpdateInfoText();` — Updates the info text
- L47 _private prototype_ `UDMXPixelMappingLayoutViewModel* GetLayoutViewModel() const;` — Retuns the object that is being customized
- L50 _private member_ `TWeakPtr<FDMXPixelMappingToolkit> ToolkitWeakPtr;` — Weak reference to the DMX editor
- L53 _private member_ `bool bShowLayoutScriptClass = false;` — If true, shows the Layout Script Class property
- L56 _private member_ `bool bShowLayoutScriptClassHiddenInfo = true;` — If true, shows an info why the Layout Script Class property is hidden
- L59 _private member_ `TSharedPtr<STextBlock> InfoTextBlock;` — Text block displaying info about what's being arranged
- L62 _private member_ `TSharedPtr<IPropertyHandle> AutoApplyHandle;` — Property handle for the bAutoApply property
- L65 _private member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;` — Property utilities for this customization
- L68 _private member_ `TWeakPtr<FDMXPixelMappingToolkit> WeakToolkit;` — Weak reference to the Pixel Mapping Toolkit

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Customizations/DMXPixelMappingPreprocessRendererDetails.h` (Private)


#### class `UE::DMXPixelMapping::Customizations::FDMXPixelMappingPreprocessRendererDetails`  
`class FDMXPixelMappingPreprocessRendererDetails : public IDetailCustomization`  
_L13-34_
- inherits: `IDetailCustomization`
- L17 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L20 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L24 _private prototype_ `void OnFilterMaterialChanged();` — Called when the filter material instance dynamic property changed
- L27 _private prototype_ `bool IsBlurDistanceMaterialParameterNameExisting() const;` — Tests if the blur distance parameter name exists on the filter material
- L30 _private member_ `TSharedPtr<IPropertyHandle> FilterMaterialHandle;` — Property handle for the FilterMaterial property
- L33 _private member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;` — Property utilities for this customization

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace DMXPixelMapping` (scope `UE`)
- L11 _namespace_ `namespace Customizations` (scope `UE::DMXPixelMapping`)

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Customizations/DMXPixelMappingVerticalAlignmentCustomization.h` (Private)


#### class `FDMXPixelMappingVerticalAlignmentCustomization`  
`class FDMXPixelMappingVerticalAlignmentCustomization : public IPropertyTypeCustomization`  
_L10-28_
- inherits: `IPropertyTypeCustomization`
- L15 _public prototype_ `static TSharedRef<class IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L18 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L19 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L24 _private prototype_ `EVerticalAlignment GetAlignment(TSharedRef<IPropertyHandle> PropertyHandle) const;` — Returns the Aligment
- L27 _private prototype_ `void OnAlignmentChanged(EVerticalAlignment NewAlignment, TSharedRef<IPropertyHandle> PropertyHandle);` — Called when the Alignment changed

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/DMXPixelMappingComponentReference.h` (Private)


#### struct `FDMXPixelMappingComponentReference`  
`struct FDMXPixelMappingComponentReference`  
_L16-62_
- reflection: `USTRUCT()`
- desc: The Component reference is a useful way to hold onto the selection in a way that allows for up to date access to the current preview object. This is a safe way to communicate between different parts of the pixel mapping editor
- L23 _public prototype_ `FDMXPixelMappingComponentReference() = default;`
- L25 _public function_ `FDMXPixelMappingComponentReference(TSharedPtr<FDMXPixelMappingToolkit> InToolkit, UDMXPixelMappingBaseComponent* InComponent) : ToolkitWeakPtr(InToolkit) , Component(InComponent)`
- L31 _public function_ `bool operator==(const FDMXPixelMappingComponentReference& Other) const` — Checks if widget reference is the same as another component reference, based on the template pointers.
- L42 _public function_ `bool operator!=(const FDMXPixelMappingComponentReference& Other) const` — Checks if widget reference is the different from another component reference, based on the template pointers.
- L47 _public function_ `bool IsValid() const`
- L50 _public function_ `UDMXPixelMappingBaseComponent* GetComponent() const` — @returns stored component pointer
- L58 _private member_ `TWeakPtr<FDMXPixelMappingToolkit> ToolkitWeakPtr;`
- L61 _private member_ `TWeakObjectPtr<UDMXPixelMappingBaseComponent> Component;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L52 _function_ `friend uint32 GetTypeHash(const FDMXPixelMappingComponentReference& ComponentRef)`

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/DMXPixelMappingEditorCommands.h` (Private)


#### class `FDMXPixelMappingEditorCommands`  
`class FDMXPixelMappingEditorCommands : public TCommands<FDMXPixelMappingEditorCommands>`  
_L9-47_
- inherits: `TCommands<FDMXPixelMappingEditorCommands>`
- desc: Defines commands for the pixel mapping editor.
- L13 _public prototype_ `FDMXPixelMappingEditorCommands();`
- L15 _public prototype_ `virtual void RegisterCommands() override;`
- L18 _public member_ `TSharedPtr<FUICommandInfo> AddMapping;` — Toolbar related
- L19 _public member_ `TSharedPtr<FUICommandInfo> PlayDMX;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> PauseDMX;`
- L21 _public member_ `TSharedPtr<FUICommandInfo> ResumeDMX;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> StopDMX;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> TogglePlayPauseDMX;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> TogglePlayStopDMX;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> EditorStopSendsDefaultValues;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> EditorStopSendsZeroValues;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> EditorStopKeepsLastValues;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> EnableResizeMode;` — Designer related
- L32 _public member_ `TSharedPtr<FUICommandInfo> EnableRotateMode;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> ToggleGridSnapping;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> FlipGroupHorizontally;`
- L37 _public member_ `TSharedPtr<FUICommandInfo> FlipGroupVertically;`
- L38 _public member_ `TSharedPtr<FUICommandInfo> SizeGroupToTexture;`
- L40 _public member_ `TSharedPtr<FUICommandInfo> ToggleScaleChildrenWithParent;`
- L41 _public member_ `TSharedPtr<FUICommandInfo> ToggleAlwaysSelectGroup;`
- L42 _public member_ `TSharedPtr<FUICommandInfo> ToggleShowMatrixCells;`
- L43 _public member_ `TSharedPtr<FUICommandInfo> ToggleShowComponentNames;`
- L44 _public member_ `TSharedPtr<FUICommandInfo> ToggleShowPatchInfo;`
- L45 _public member_ `TSharedPtr<FUICommandInfo> ToggleShowCellIDs;`
- L46 _public member_ `TSharedPtr<FUICommandInfo> ToggleShowPivot;`

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/DMXPixelMappingEditorLog.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDMXPixelMappingEditor, All, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDMXPixelMappingEditor, All, All);`

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/DMXPixelMappingEditorModule.h` (Private)


#### class `FDMXPixelMappingEditorModule`  
`class FDMXPixelMappingEditorModule : public IModuleInterface , public IHasMenuExtensibility`  
_L14-54_
- inherits: `IModuleInterface,IHasMenuExtensibility,IHasToolBarExtensibility`
- L21 _public prototype_ `virtual void StartupModule() override;`
- L22 _public prototype_ `virtual void ShutdownModule() override;`
- L26 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetMenuExtensibilityManager() override`
- L30 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetToolBarExtensibilityManager() override`
- L34 _public prototype_ `const FDMXPixelMappingEditorCommands& GetCommands() const;` — Get Editor toolkit commands
- L37 _public function_ `static EAssetTypeCategories::Type GetAssetCategory()` — Asset category
- L40 _private prototype_ `void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action);`
- L43 _public member_ `static const FName DMXPixelMappingEditorAppIdentifier;`
- L46 _private member_ `static EAssetTypeCategories::Type DMXPixelMappingCategory;`
- L49 _private member_ `TSharedPtr<FExtensibilityManager> MenuExtensibilityManager;`
- L51 _private member_ `TSharedPtr<FExtensibilityManager> ToolBarExtensibilityManager;`
- L53 _private member_ `TArray<TSharedPtr<IAssetTypeActions>> CreatedAssetTypeActions;`

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/DMXPixelMappingEditorStyle.h` (Private)


#### class `FDMXPixelMappingEditorStyle`  
`class FDMXPixelMappingEditorStyle : public FSlateStyleSet`  
_L8-18_
- inherits: `FSlateStyleSet`
- L12 _public prototype_ `FDMXPixelMappingEditorStyle();`
- L14 _public prototype_ `virtual ~FDMXPixelMappingEditorStyle();`
- L17 _public prototype_ `static const ISlateStyle& Get();` — @return The Slate style set for pixel mapping editor widgets

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/DMXPixelMappingEditorUtils.h` (Private)


#### class `FDMXPixelMappingEditorUtils`  
`class FDMXPixelMappingEditorUtils`  
_L19-50_
- desc: Shared Pixel Mapping editor functions
- L29 _public prototype_ `static UDMXPixelMappingRendererComponent* AddRenderer(UDMXPixelMapping* InPixelMapping);` — Add renderer to Pixel Mapping object @param InDMXPixelMapping		Pixel Mapping object @return Render Component pointer
- L39 _public prototype_ `static bool GetArrangedWidget(TSharedRef<SWidget> InWidget, FArrangedWidget& OutArrangedWidget);` — Returns the arranged widget of a widget. @param InWidget				The widget to get the arranged widget from @param OutArrangedWidget		The arranged widget @return						True if the arranged widget could be acquired
- L49 _public prototype_ `static UDMXPixelMappingBaseComponent* GetTargetComponentFromDragDropEvent(const TWeakPtr<FDMXPixelMappingToolkit>& WeakToolkit, const FDragDropEvent& DragDropEvent);` — Returns the target component from a drag drop event @param WeakToolkit			The toolkit in use @param DragDropEvent			The DragDropEvent to consider. @return						The component that is target of the drag drop op

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/DMXPixelMappingThumbnailRendering.h` (Private)


#### class `UDMXPixelMappingThumbnailRendering`  
`class UDMXPixelMappingThumbnailRendering : public UTextureThumbnailRenderer`  
_L15-27_
- reflection: `UCLASS()`
- inherits: `UTextureThumbnailRenderer`
- desc: Dynamically  rendering thumbnail for Pixel Mapping asset
- L22 _public prototype_ `virtual bool CanVisualizeAsset(UObject* Object) override;`
- L23 _public prototype_ `virtual void GetThumbnailSize(UObject* Object, float Zoom, uint32& OutWidth, uint32& OutHeight) const override;`
- L24 _public prototype_ `virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget*, FCanvas* Canvas, bool bAdditionalViewFamily) override;`
- L25 _public prototype_ `UTexture* GetThumbnailTextureFromObject(UObject* Object) const;`

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/DMXPixelMappingToolbar.h` (Private)


#### class `FDMXPixelMappingToolbar`  
`class FDMXPixelMappingToolbar : public TSharedFromThis<FDMXPixelMappingToolbar>`  
_L12-27_
- inherits: `TSharedFromThis<FDMXPixelMappingToolbar>`
- desc: Extends the PixelMapping asset editor toolkit toolbar
- L16 _public prototype_ `FDMXPixelMappingToolbar(TSharedPtr<FDMXPixelMappingToolkit> InToolkit);`
- L17 _public function_ `virtual ~FDMXPixelMappingToolbar()`
- L20 _public prototype_ `void ExtendToolbar();` — Extends the PixelMapping asset editor toolkit toolbar
- L24 _private prototype_ `TSharedRef<SWidget> GeneratePlaybackSettingsMenu(FName ParentMenuName) const;` — Generates the playback settings submenu
- L26 _private member_ `TWeakPtr<FDMXPixelMappingToolkit> WeakToolkit;`

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/DragDrop/DMXPixelMappingDragDropOp.h` (Private)


#### class `FDMXPixelMappingDragDropOp`  
`class FDMXPixelMappingDragDropOp : public FDecoratedDragDropOp`  
_L17-81_
- inherits: `FDecoratedDragDropOp`
- desc: This drag drop operation allows Component templates from the palate to be dragged and dropped into the designer or the Component hierarchy in order to spawn new Components.
- L21 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FDMXPixelMappingDragDropOp, FDecoratedDragDropOp) virtual ~FDMXPixelMappingDragDropOp();`
- L27 _public prototype_ `static TSharedRef<FDMXPixelMappingDragDropOp> New(const TSharedRef<FDMXPixelMappingToolkit>& InToolkit, const FVector2D& InGraphSpaceDragOffset, const TArray<TSharedPtr<FDMXPixelMappingComponentTemplate>>& InTemplates, UDMXPixelMappingBaseComponent* InParent);` — Constructs the drag drop operation.
- L30 _public prototype_ `static TSharedRef<FDMXPixelMappingDragDropOp> New(const TSharedRef<FDMXPixelMappingToolkit>& InToolkit, const FVector2D& InGraphSpaceDragOffset, const TArray<TWeakObjectPtr<UDMXPixelMappingBaseComponent>>& InDraggedComponents);` — Constructs the drag drop operation. Note, the component that initiated the drag drop op has to be the first element in the InDraggedComponents array.
- L33 _public prototype_ `void SetDraggedComponents(const TArray<TWeakObjectPtr<UDMXPixelMappingBaseComponent>>& InDraggedComponents);` — Sets dragged components. Clears the template, preventing from the template being used more than once.
- L39 _public prototype_ `void LayoutOutputComponents(const FVector2D& GraphSpacePosition);` — Lays out the draged output components at given locations. Requires the first in the selection to have specified the drag offset Note, doesn't work with matrix components, use GroupChildHelper from this class instead for that.
- L42 _public function_ `bool WasCreatedAsTemplate() const` — Returns true if the drag drop op was created with the constructor that provides a template
- L46 _public member_ `TWeakObjectPtr<UDMXPixelMappingBaseComponent> Parent;` — Can be used to store the parent of the dragged component(s)
- L49 _public member_ `FVector2D GraphSpaceDragOffset;` — The Drag offset, in graph space
- L52 _public function_ `const TSharedPtr<FDMXPixelMappingGroupChildDragDropHelper>& GetGroupChildDragDropHelper() const` — Returns the Group Item dragdrop helper. Only valid if only group items are dragged
- L55 _public function_ `const TArray<TWeakObjectPtr<UDMXPixelMappingBaseComponent>>& GetDraggedComponents() const` — Returns the dragged component references
- L58 _public function_ `const TArray<TSharedPtr<FDMXPixelMappingComponentTemplate>>& GetTemplates() const` — Returns the dragged component references
- L61 _public prototype_ `FVector2D ComputeGridSnapPosition(const FVector2D& DesiredPosition) const;` — Utiltity that returns the grid snapped position from a desired position.
- L65 _private member_ `bool bWasCreatedAsTemplate = false;` — True if this was created with the New version was used that provides a template
- L68 _private member_ `int32 TransactionIndex = INDEX_NONE;` — Transaction index of the drag drop op
- L71 _private member_ `TArray<TWeakObjectPtr<UDMXPixelMappingBaseComponent>> DraggedComponents;` — Components dragged with this opperation
- L74 _private member_ `TArray<TSharedPtr<FDMXPixelMappingComponentTemplate>> Templates;` — The templates to create component instances
- L77 _private member_ `TSharedPtr<FDMXPixelMappingGroupChildDragDropHelper> GroupChildDragDropHelper;` — Group Item drag drop helper
- L80 _private member_ `TWeakPtr<FDMXPixelMappingToolkit> WeakToolkit;` — The toolkit that constructed this drag drop op

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/DragDrop/DMXPixelMappingGroupChildDragDropHelper.h` (Private)


#### class `FDMXPixelMappingGroupChildDragDropHelper`  
`class FDMXPixelMappingGroupChildDragDropHelper : public TSharedFromThis<FDMXPixelMappingGroupChildDragDropHelper>`  
_L18-52_
- inherits: `TSharedFromThis<FDMXPixelMappingGroupChildDragDropHelper>`
- desc: Helper class that manages to layout group items while being dragged. Can return what is over the parent
- L23 _public prototype_ `static TSharedPtr<FDMXPixelMappingGroupChildDragDropHelper> Create(TSharedRef<FDragDropOperation> InPixelMappingDragDropOp);` — Creates a new helper, returns the helper or nullptr if it cannot be created from the drag drop op
- L26 _public prototype_ `void LayoutComponents(const FVector2D& GraphSpacePosition, bool bAlignCells);` — Lays out the widgets
- L29 _public function_ `TArray<TWeakObjectPtr<UDMXPixelMappingOutputComponent>> GetChildComponents() const` — Returns all group items
- L33 _private prototype_ `void LayoutAligned(const FVector2D& GraphSpacePosition);` — Helper that lays out cells aligned
- L36 _private prototype_ `void LayoutUnaligned(const FVector2D& GraphSpacePosition);` — Helper that lays out cells unaligned
- L39 _private member_ `FVector2D ParentPosition;` — Local position of the parent
- L42 _private member_ `FVector2D ParentSize;` — Size of the parent
- L45 _private member_ `TWeakObjectPtr<UDMXPixelMappingFixtureGroupComponent> WeakParentGroupComponent;` — The parent group component
- L48 _private member_ `TArray<TWeakObjectPtr<UDMXPixelMappingOutputComponent>> WeakChildComponents;` — The child group item components
- L51 _private member_ `TWeakPtr<FDMXPixelMappingDragDropOp> WeakPixelMappingDragDropOp;` — The drag drop op being handled

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Factories/DMXPixelMappingActorFactory.h` (Private)


#### class `UDMXPixelMappingActorFactory`  
`class UDMXPixelMappingActorFactory : public UActorFactory`  
_L16-29_
- reflection: `UCLASS()`
- inherits: `UActorFactory`
- desc: Actor Factory for DMX Pixel Mapping Actor
- L23 _public prototype_ `UDMXPixelMappingActorFactory();` — Constructor
- L26 _public prototype_ `virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg) override;`
- L27 _public prototype_ `virtual AActor* SpawnActor(UObject* Asset, ULevel* InLevel, const FTransform& Transform, const FActorSpawnParameters& InSpawnParams) override;`

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Factories/DMXPixelMappingFactoryNew.h` (Private)


#### class `UDMXPixelMappingFactoryNew`  
`class UDMXPixelMappingFactoryNew : public UFactory`  
_L9-23_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L15 _public prototype_ `UDMXPixelMappingFactoryNew();`
- L19 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L20 _private prototype_ `virtual FText GetDisplayName() const override;`
- L21 _private prototype_ `virtual uint32 GetMenuCategories() const override;`

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Settings/DMXPixelMappingEditorSettings.h` (Private)


#### struct `FDMXPixelMappingHierarchySettings`  
`struct FDMXPixelMappingHierarchySettings`  
_L12-35_
- reflection: `USTRUCT()`
- L18 _public member_ `bool bShowEditorColorColumn = true;` — `UPROPERTY()` — If true, shows the editor color column
- L22 _public member_ `bool bShowFixtureIDColumn = true;` — `UPROPERTY()` — If true, shows the fixture ID column
- L26 _public member_ `bool bShowPatchColumn = true;` — `UPROPERTY()` — If true, shows the patch column
- L30 _public member_ `FName SortByColumnId;` — `UPROPERTY()` — The sort by column Id. Can be none or a valid column id
- L34 _public member_ `bool bSortAscending = true;` — `UPROPERTY()` — If true, the current sort mode is ascending

#### struct `FDMXPixelMappingDesignerSettings`  
`struct FDMXPixelMappingDesignerSettings`  
_L38-73_
- reflection: `USTRUCT()`
- L44 _public member_ `bool bScaleChildrenWithParent = true;` — `UPROPERTY()` — If true, scales children when the parent component is resized
- L48 _public member_ `bool bAlwaysSelectGroup = false;` — `UPROPERTY()` — If true, selects parent when a child is clicked
- L52 _public member_ `bool bApplyLayoutScriptWhenLoaded = true;` — `UPROPERTY()` — If true, applies layout scripts instantly when they are loaded
- L56 _public member_ `bool bShowPivot = true;` — `UPROPERTY()` — If true, a pivot is displayed for selected components
- L60 _public member_ `bool bShowMatrixCells = true;` — `UPROPERTY()` — If true, shows a widget for each cell. It is recommended that this is turned off when pixel mapping large quantities of fixtures.
- L64 _public member_ `bool bShowComponentNames = true;` — `UPROPERTY()` — If true, shows the name of the Fixture Patch where applicable. It is recommended that this is turned off when pixel mapping large quantities of fixtures.
- L68 _public member_ `bool bShowPatchInfo = false;` — `UPROPERTY()` — If true, shows Fixture info bout the Fixture Patch where applicable. It is recommended that this is turned off when pixel mapping large quantities of fixtures.
- L72 _public member_ `bool bShowCellIDs = false;` — `UPROPERTY()` — If true, shows Cell IDs where applicable. It is recommended that this is turned off when pixel mapping large quantities of fixtures.

#### class `UDMXPixelMappingEditorSettings`  
`class UDMXPixelMappingEditorSettings : public UObject`  
_L78-99_
- reflection: `UCLASS(Config = DMXPixelMappingEditor, DefaultConfig)`
- inherits: `UObject`
- desc: Layout options for the Pixel Mapping editor
- L86 _public member_ `FDMXPixelMappingHierarchySettings HierarchySettings;` — `UPROPERTY(Config)` — Settings for the hierarchy tab
- L90 _public member_ `FDMXPixelMappingDesignerSettings DesignerSettings;` — `UPROPERTY(Config)` — Settings for the designer tab
- L95 _public member_ `EDMXPixelMappingResetDMXMode EditorResetDMXMode;` — `UE_DEPRECATED(5.6, "Each pixel mapping holds its own stop mode now. See UDMXPixelMapping::SetResetDMXMode")` — `UPROPERTY(Config)` — Reset DMX mode to be used in editor
- L98 _public member_ `static FSimpleMulticastDelegate OnEditorSettingsChanged;` — Raised by the pixel mapping toolkit when settings changed

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Toolkits/DMXPixelMappingToolkit.h` (Private)


#### enum `UE::DMX::EDMXPixelMappingTransformHandleMode`  
`enum class EDMXPixelMappingTransformHandleMode : uint8`  
_L38-42_
- L40 _public enumerator_ `Resize`
- L41 _public enumerator_ `Rotate`

#### class `UDMXPixelMappingToolkitSelection`  
`class UDMXPixelMappingToolkitSelection : public UObject`  
_L47-58_
- reflection: `UCLASS(Transient)`
- inherits: `UObject`
- desc: Selection in the pixel mapping toollkit. Using the UObject system for undo/redo.
- L54 _public member_ `TSet<FDMXPixelMappingComponentReference> Components;` — `UPROPERTY()`
- L57 _public member_ `TWeakObjectPtr<UDMXPixelMappingRendererComponent> ActiveRendererComponent;` — `UPROPERTY()`

#### class `FDMXPixelMappingToolkit`  
`class FDMXPixelMappingToolkit : public FAssetEditorToolkit , public FTickableEditorObject , public FSelfRegisteringEditorUndoClient , public FGCObject`  
_L63-329_
- inherits: `FAssetEditorToolkit,FTickableEditorObject,FSelfRegisteringEditorUndoClient,FGCObject`
- desc: Implements an Editor toolkit for Pixel Mapping.
- L69 _private typedef_ `using EDMXPixelMappingTransformHandleMode = UE::DMX::EDMXPixelMappingTransformHandleMode;`
- L72 _public function_ `DECLARE_MULTICAST_DELEGATE(FOnSelectedComponentsChangedDelegate) FOnSelectedComponentsChangedDelegate& GetOnSelectedComponentsChangedDelegate()`
- L76 _public prototype_ `FDMXPixelMappingToolkit();`
- L77 _public prototype_ `~FDMXPixelMappingToolkit();`
- L86 _public prototype_ `void InitPixelMappingEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UDMXPixelMapping* InDMXPixelMapping);` — Initilaizes the pixel mapping editor. @param Mode				The Toolkit Mode. @param					THe Toolkit Host. @param UDMXPixelMapping	The Pixel Mapping object that is being edited.
- L90 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L91 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L95 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L96 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L97 _public function_ `virtual FLinearColor GetWorldCentricTabColorScale() const override`
- L98 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L102 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L103 _public function_ `virtual bool IsTickable() const override`
- L104 _public prototype_ `virtual TStatId GetStatId() const override;`
- L107 _public prototype_ `UDMXPixelMapping* GetDMXPixelMapping() const;`
- L109 _public prototype_ `FDMXPixelMappingComponentReference GetReferenceFromComponent(UDMXPixelMappingBaseComponent* InComponent);`
- L111 _public prototype_ `UDMXPixelMappingRendererComponent* GetActiveRendererComponent() const;`
- L113 _public function_ `const TSharedPtr<FUICommandList>& GetDesignerCommandList() const`
- L115 _public prototype_ `const TSet<FDMXPixelMappingComponentReference>& GetSelectedComponents() const;`
- L118 _public prototype_ `TSharedRef<SDMXPixelMappingDMXLibraryView> GetOrCreateDMXLibraryView();` — Gets or creates the DMX Library View for this Pixel Mapping instance
- L121 _public prototype_ `TSharedRef<SDMXPixelMappingHierarchyView> GetOrCreateHierarchyView();` — Gets or creates the Hierarchy View for this Pixel Mapping instance
- L124 _public prototype_ `TSharedRef<SDMXPixelMappingDesignerView> GetOrCreateDesignerView();` — Gets or creates the Designer View for this Pixel Mapping instance
- L127 _public prototype_ `TSharedRef<SDMXPixelMappingPreviewView> GetOrCreatePreviewView();` — Gets or creates the Preview View for this Pixel Mapping instance
- L130 _public prototype_ `TSharedRef<SDMXPixelMappingDetailsView> GetOrCreateDetailsView();` — Gets or creates the Details View for this Pixel Mapping instance
- L133 _public prototype_ `TSharedRef<SDMXPixelMappingLayoutView> GetOrCreateLayoutView();` — Gets or creates the Layout View for this Pixel Mapping instance
- L136 _public prototype_ `bool IsPlayingDMX() const;` — Returns true if the pixel mapping asset is currently playing DMX
- L138 _public prototype_ `void SetActiveRenderComponent(UDMXPixelMappingRendererComponent* InComponent);`
- L142 _public prototype_ `template <typename ComponentType> TArray<ComponentType> MakeComponentArray(const TSet<FDMXPixelMappingComponentReference>& Components) const;` — Creates an array of components given specifed component references
- L144 _public prototype_ `void SelectComponents(const TSet<FDMXPixelMappingComponentReference>& Components);`
- L147 _public prototype_ `bool IsComponentSelected(UDMXPixelMappingBaseComponent* Component) const;` — Returns true if the component is selected
- L150 _public prototype_ `void AddRenderer();` — Adds a renderer to the pixel mapping. Sets it as active renderer if a new renderer was created
- L153 _public prototype_ `void RenameComponent(const FName& PreviousObjectName, const FString& DesiredObjectName) const;` — `UE_DEPRECATED(5.3, "Removed without replacement. Use UObject::Rename instead")`
- L159 _public prototype_ `TArray<UDMXPixelMappingBaseComponent*> CreateComponentsFromTemplates(UDMXPixelMappingRootComponent* RootComponent, UDMXPixelMappingBaseComponent* Target, const TArray<TSharedPtr<FDMXPixelMappingComponentTemplate>>& Templates);` — Creates components from the template. Returns the new components. If many component were created, the first component is the topmost parent.
- L162 _public prototype_ `void DeleteSelectedComponents();` — Deletes the selected Components
- L165 _public prototype_ `bool CanPerformCommandsOnGroup() const;` — Returns true if the current selection yields a fixture group on which commands can be performed on, e.g. SizeGroupToTexture
- L168 _public prototype_ `void FlipGroup(EOrientation Orientation, bool bTransacted);` — Flips children of a group either horizontally or vertically
- L171 _public prototype_ `void SizeGroupToTexture(bool bTransacted);` — Sizes the component to the render target of the pixelmapping asset
- L174 _public prototype_ `void ToggleGridSnapping();` — Toggles between grid snapping enabled and disabled
- L177 _public prototype_ `void SetTransformHandleMode(EDMXPixelMappingTransformHandleMode NewTransformHandleMode);` — Sets how transform handles operate
- L180 _public function_ `EDMXPixelMappingTransformHandleMode GetTransformHandleMode() const` — Returns the current transform handle mode
- L184 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L185 _protected prototype_ `virtual FString GetReferencerName() const override;`
- L190 _private prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L191 _private prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L195 _private prototype_ `void OnComponentAddedOrRemoved(UDMXPixelMapping* PixelMapping, UDMXPixelMappingBaseComponent* Component);` — Called when a component was added to the pixel mapping
- L198 _private prototype_ `void OnComponentRenamed(UDMXPixelMappingBaseComponent* Component);` — Called when a component object was renamed
- L201 _private prototype_ `void PlayDMX();` — Starts to play DMX on editor tick
- L204 _private prototype_ `void PauseDMX();` — Pauses playing DMX. Current DMX values will still be sent at a lower rate.
- L207 _private prototype_ `void StopPlayingDMX();` — Stops playing DMX
- L210 _private prototype_ `void TogglePlayPauseDMX();` — Toggles between playing and pausing DMX
- L213 _private prototype_ `void TogglePlayStopDMX();` — Toggles between playing and stopping DMX
- L216 _private prototype_ `void SetEditorResetDMXMode(EDMXPixelMappingResetDMXMode NewMode);` — Sets the reset DMX mode used by the editor
- L219 _private prototype_ `void UpdateBlueprintNodes() const;` — Updates blueprint nodes
- L222 _private prototype_ `void SaveThumbnailImage();` — Saves a thumbnail image for the pixel mapping asset
- L225 _private prototype_ `TSharedRef<SDockTab> SpawnTab_DMXLibraryView(const FSpawnTabArgs& Args);` — Spawns the DMX Library View
- L228 _private prototype_ `TSharedRef<SDockTab> SpawnTab_HierarchyView(const FSpawnTabArgs& Args);` — Spawns the Hierarchy View
- L231 _private prototype_ `TSharedRef<SDockTab> SpawnTab_DesignerView(const FSpawnTabArgs& Args);` — Spawns the Designer View
- L234 _private prototype_ `TSharedRef<SDockTab> SpawnTab_PreviewView(const FSpawnTabArgs& Args);` — Spawns the Preview View
- L237 _private prototype_ `TSharedRef<SDockTab> SpawnTab_DetailsView(const FSpawnTabArgs& Args);` — Spawns the Details View
- L240 _private prototype_ `TSharedRef<SDockTab> SpawnTab_LayoutView(const FSpawnTabArgs& Args);` — Spawns the Layout View
- L242 _private prototype_ `void SetupCommands();`
- L244 _private prototype_ `void ExtendToolbar();`
- L246 _private prototype_ `void CreateInternalViews();`
- L249 _private prototype_ `void PreSavePackage(class UPackage* Package, FObjectPreSaveContext Context);` — Called before any package was saved
- L252 _private prototype_ `ECheckBoxState GetEditorResetDMXModeCheckboxState(EDMXPixelMappingResetDMXMode CompareMode) const;` — Returns the check box state for the compared reset DMX mode
- L255 _private prototype_ `ECheckBoxState GetTransformHandleModeCheckboxState(EDMXPixelMappingTransformHandleMode CompareTransformHandleMode) const;` — Returns the checkbox state for a transform handle mode, checked if the mode equals the current mode.
- L261 _private prototype_ `UDMXPixelMappingFixtureGroupComponent* GetFixtureGroupFromSelection() const;` — Returns the fixture group from a selection. Returns the parent group if the primary selection is a child of a group. Returns the primary fixture group in selection or nullptr if no fixture group can be deduced from selection.
- L264 _private member_ `TMap<FName, TWeakPtr<SDockableTab>> SpawnedToolPanels;` — List of open tool panels; used to ensure only one exists at any one time
- L267 _private member_ `TSharedPtr<SDMXPixelMappingDMXLibraryView> DMXLibraryView;` — The DMX Library View instance
- L270 _private member_ `TSharedPtr<SDMXPixelMappingHierarchyView> HierarchyView;` — The Hierarchy View instance
- L273 _private member_ `TSharedPtr<SDMXPixelMappingDesignerView> DesignerView;` — The Designer View instance
- L276 _private member_ `TSharedPtr<SDMXPixelMappingPreviewView> PreviewView;` — The Preview View instance
- L279 _private member_ `TSharedPtr<SDMXPixelMappingDetailsView> DetailsView;` — The Details View instance
- L282 _private member_ `TSharedPtr<SDMXPixelMappingLayoutView> LayoutView;` — The Layout View instance
- L284 _private member_ `FOnSelectedComponentsChangedDelegate OnSelectedComponentsChangedDelegate;`
- L287 _private member_ `TObjectPtr<UDMXPixelMappingToolkitSelection> Selection;` — The selection object
- L289 _private member_ `TSharedPtr<FDMXPixelMappingToolbar> Toolbar;`
- L291 _private member_ `TArray<TWeakObjectPtr<UDMXPixelMappingOutputComponent>> ActiveOutputComponents;`
- L294 _private member_ `TSharedPtr<FUICommandList> DesignerCommandList;` — Command list for handling widget actions in the PixelMapping Toolkit
- L297 _private member_ `bool bAddingComponents = false;` — True while adding components (to avoid needlessly updating blueprint nodes on each component added via our own methods)
- L300 _private member_ `bool bRemovingComponents = false;` — True while removing components (to avoid needlessly updating blueprint nodes on each component removed via our own methods)
- L303 _private member_ `EDMXPixelMappingTransformHandleMode TransformHandleMode = EDMXPixelMappingTransformHandleMode::Resize;` — The current transform handle mode
- L307 _public member_ `static const FName DMXLibraryViewTabID;` — Name of the DMX Library View Tab
- L310 _public member_ `static const FName HierarchyViewTabID;` — Name of the Hierarchy View Tab
- L313 _public member_ `static const FName DesignerViewTabID;` — Name of the Designer View Tab
- L316 _public member_ `static const FName PreviewViewTabID;` — Name of the Preview View Tab
- L319 _public member_ `static const FName DetailsViewTabID;` — Name of the Details View Tab
- L322 _public member_ `static const FName LayoutViewTabID;` — Name of the Details View Tab
- L325 _public member_ `UE::DMX::FDMXEditorToolAnalyticsProvider AnalyticsProvider;` — The analytics provider for this tool
- L328 _public member_ `TArray<uint8, TFixedAllocator<sizeof(UDMXPixelMappingEditorSettings)>> EditorSettingsDump;` — Dumped editor settings for fast comparison

#### Free symbols / members of external scopes

- L36 _namespace_ `namespace UE`
- L36 _namespace_ `namespace DMX` (scope `UE`)
- L72 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnSelectedComponentsChangedDelegate) FOnSelectedComponentsChangedDelegate& GetOnSelectedComponentsChangedDelegate() { return OnSelectedComponentsChangedDelegate; } public: FDMXPixelMappingToolkit();`

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/ViewModels/DMXPixelMappingDMXLibraryViewModel.h` (Private)


#### class `UDMXPixelMappingDMXLibraryViewModel`  
`class UDMXPixelMappingDMXLibraryViewModel : public UObject , public FEditorUndoClient`  
_L25-117_
- reflection: `UCLASS(Config = DMXEditor)`
- inherits: `UObject,FEditorUndoClient`
- desc: Model for the DMX Library View
- L33 _public prototype_ `void CreateAndSetNewFixtureGroup(TWeakPtr<FDMXPixelMappingToolkit> InWeakToolkit);` — Adds a fixture group to pixel mapping. Sets it for this model
- L36 _public prototype_ `void UpdateFixtureGroupFromSelection(TWeakPtr<FDMXPixelMappingToolkit> InWeakToolkit);` — Sets the fixture group for this model from what's currently selected. Note only single selection is supported as of 5.3
- L39 _public prototype_ `void SetNewComponentsUsePatchColor(bool bUsePatchColor);` — Sets if new components should use the patch color
- L42 _public prototype_ `bool ShouldNewComponentsUsePatchColor() const;` — Returns true if new components should use the patch color
- L45 _public prototype_ `void AddFixturePatchesEnsured(const TArray<UDMXEntityFixturePatch*>& FixturePatches);` — Adds specified fixture patches to the pixel mapping. Ensures all patches are of the same library as the one of the current group.
- L48 _public function_ `UDMXLibrary* GetDMXLibrary() const` — Returns the DMX Library, or nullptr if none or many are selected
- L51 _public function_ `UDMXPixelMappingFixtureGroupComponent* GetFixtureGroupComponent() const` — Returns the Fixture Group, or nullptr if none or many are selected
- L54 _public function_ `bool IsMoreThanOneFixtureGroupSelected() const` — Returns true if more than one fixture group is sected.
- L57 _public function_ `const FDMXReadOnlyFixturePatchListDescriptor& GetFixturePatchListDescriptor() const` — Returns the default fixture patch list descriptor
- L60 _public prototype_ `void SaveFixturePatchListDescriptor(const FDMXReadOnlyFixturePatchListDescriptor& NewDescriptor);` — Saves the fixture patch list descriptor
- L63 _public member_ `FSimpleMulticastDelegate OnDMXLibraryChanged;` — Delegate broadcast when the DMX library changed
- L67 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L68 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L72 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L77 _private prototype_ `void UpdateDMXLibraryFromComponent();` — Updates the DMX Library from the component
- L80 _private prototype_ `void RemoveInvalidPatches();` — Removes invalid patches from pixel mapping
- L83 _private prototype_ `void SelectFixtureGroupComponent(UDMXPixelMappingFixtureGroupComponent* FixtureGroupComponent);` — Selects the fixture group component
- L86 _private prototype_ `void LayoutEvenOverParent(const TArray<UDMXPixelMappingBaseComponent*> Components);` — Layouts components evenly over the parent group
- L89 _private prototype_ `void LayoutAfterLastPatch(const TArray<UDMXPixelMappingBaseComponent*> Components);` — Layouts components after the last patch in the parent group
- L92 _private prototype_ `UDMXPixelMappingRootComponent* GetPixelMappingRootComponent() const;` — Returns the root component of the pixel mapping
- L95 _private prototype_ `TArray<UDMXPixelMappingFixtureGroupComponent*> GetFixtureGroupComponentsOfSameLibrary() const;` — Gets all fixture groups that use the same library as the current fixture group in use
- L99 _private member_ `TObjectPtr<UDMXLibrary> DMXLibrary;` — `UPROPERTY(EditAnywhere, Transient, Category = "DMXLibrary", Meta = (AllowPrivateAccess = true))` — The DMX library of this view
- L103 _private member_ `TWeakObjectPtr<UDMXPixelMappingFixtureGroupComponent> WeakFixtureGroupComponent;` — `UPROPERTY(Transient)` — The fixture group component that this model uses
- L107 _private member_ `FDMXReadOnlyFixturePatchListDescriptor FixturePatchListDescriptor;` — `UPROPERTY(Config)` — Default fixture patch list descriptor
- L110 _private member_ `bool bMoreThanOneFixtureGroupSelected = false;` — True if more than one fixture group is selected
- L113 _private member_ `bool bChangingProperties = false;` — True while changing properties
- L116 _private member_ `TWeakPtr<FDMXPixelMappingToolkit> WeakToolkit;` — The toolkit of the editor that uses this model

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/ViewModels/DMXPixelMappingHierarchyItem.h` (Private)


#### class `FDMXPixelMappingHierarchyItem`  
`class FDMXPixelMappingHierarchyItem final : public TSharedFromThis<FDMXPixelMappingHierarchyItem>`  
_L18-98_
- inherits: `TSharedFromThis<FDMXPixelMappingHierarchyItem>`
- desc: Model for the items in the hierarchy tree view. Children populate by construction and update on changes. Use OnModelChanged to listen to changes.
- L23 _public prototype_ `static TSharedRef<FDMXPixelMappingHierarchyItem> CreateNew(TWeakPtr<FDMXPixelMappingToolkit> InToolkit);` — Creates a new instance
- L26 _public prototype_ `TArray<TSharedPtr<FDMXPixelMappingHierarchyItem>> GetItemAndChildrenRecursive();` — Returns this item and all its children
- L29 _public prototype_ `bool HasEditorColor() const;` — Returns true if this row has an editor color
- L32 _public prototype_ `FLinearColor GetEditorColor() const;` — Returns the editor color. Optional return value is only set if the component can display an editor color
- L35 _public prototype_ `FText GetComponentNameText() const;` — Returns the component name
- L38 _public prototype_ `FText GetFixtureIDText() const;` — Returns the fixture ID text
- L41 _public prototype_ `FText GetPatchText() const;` — Returns the patch text
- L44 _public prototype_ `int64 GetAbsoluteChannel() const;` — Gets the absolute channel of the patch of the component. Returns -1 if this item doesn't have a patch
- L47 _public prototype_ `bool IsExpanded() const;` — Returns true if this item is expanded
- L50 _public prototype_ `void SetIsExpanded(bool bExpanded);` — Sets if the item is expanded
- L54 _public function_ `template <typename ProjectionType> void StableSortChildren(ProjectionType Projection)` — Sorts the children of this item by Projection.
- L60 _public prototype_ `void ReverseChildren();` — Reverses the children of this item
- L63 _public function_ `UDMXPixelMappingBaseComponent* GetComponent() const` — Returns the component of this model, or nullptr if the component is no longer valid
- L66 _public function_ `TArray<TSharedPtr<FDMXPixelMappingHierarchyItem>> GetChildren() const` — Returns the child models of this model (the child components of the component of this model)
- L69 _public member_ `FSimpleMulticastDelegate RequestEnterRenameMode;` — Delegate any object can raise, causes the table row that draws this items to enter rename mode
- L73 _private prototype_ `FDMXPixelMappingHierarchyItem(TWeakPtr<FDMXPixelMappingToolkit> InToolkit);` — Constructs this item from the root component of the toolkit
- L76 _private prototype_ `FDMXPixelMappingHierarchyItem(TWeakPtr<FDMXPixelMappingToolkit> InToolkit, UDMXPixelMappingBaseComponent* InComponentReference);` — Constructst this item from the specified component in the component hierarchy
- L79 _private prototype_ `void Initialize();` — Common initializer for constructors
- L82 _private prototype_ `void BuildChildren(UDMXPixelMappingBaseComponent* ParentPixelMappingComponent = nullptr);` — Builds the Children member. If ParentPixelMappingComponent uses the root component as parent
- L85 _private prototype_ `void OnFixturePatchChanged(const UDMXEntityFixturePatch* FixturePatch);` — Called when a fixture patch changed
- L88 _private prototype_ `void UpdateFixtureID();` — Updates the optional fixture ID
- L91 _private member_ `TArray<TSharedPtr<FDMXPixelMappingHierarchyItem>> Children;` — The child items in the component hierarchy
- L94 _private member_ `TWeakObjectPtr<UDMXPixelMappingBaseComponent> WeakComponent;` — Reference to the component this model handles
- L97 _private member_ `TWeakPtr<FDMXPixelMappingToolkit> WeakToolkit;` — Toolkit this model resides in

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/ViewModels/DMXPixelMappingLayoutViewModel.h` (Private)


#### enum `EDMXPixelMappingLayoutViewModelMode`  
`enum class EDMXPixelMappingLayoutViewModelMode`  
_L19-25_
- L21 _public enumerator_ `LayoutRendererComponentChildren`
- L22 _public enumerator_ `LayoutFixtureGroupComponentChildren`
- L23 _public enumerator_ `LayoutMatrixComponentChildren`
- L24 _public enumerator_ `LayoutNone`

#### class `UDMXPixelMappingLayoutViewModel`  
`class UDMXPixelMappingLayoutViewModel : public UObject , public FSelfRegisteringEditorUndoClient`  
_L29-139_
- reflection: `UCLASS(Transient)`
- inherits: `UObject,FSelfRegisteringEditorUndoClient`
- desc: Model for the Layout View
- L37 _protected prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L38 _protected prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L43 _public prototype_ `void SetToolkit(const TSharedRef<FDMXPixelMappingToolkit>& InToolkit);` — Sets the toolkit from which the model sources
- L46 _public prototype_ `EDMXPixelMappingLayoutViewModelMode GetMode() const;` — Returns the mode in which this model currently can work in
- L49 _public prototype_ `TArray<UObject*> GetLayoutScriptsObjectsSlow() const;` — Returns the Layout Scripts of relevant components. Looks up each relevant component and returns its script.
- L52 _public prototype_ `bool CanApplyLayoutScript() const;` — Returns true if a layout script can be applied.
- L55 _public prototype_ `void RequestApplyLayoutScript();` — Applies the layouts script on the next tick. Test if CanApplyLayoutScript before calling (ensured).
- L58 _public prototype_ `void ForceApplyLayoutScript();` — Applies the layouts script. Test if CanApplyLayoutScript before calling (ensured).
- L61 _public function_ `bool ShouldAutoApplyLayoutScript() const` — Returns true if the layout script should be auto-applied on property changes
- L64 _public prototype_ `UDMXPixelMappingOutputComponent* GetParentComponent() const;` — Returns the parent of the components being laid out
- L67 _public member_ `FSimpleMulticastDelegate OnModelChanged;` — Delegate executed when the Model changed
- L70 _public function_ `static FName GetAutoApplyPropertyName()` — Property name getters
- L71 _public function_ `static FName GetLayoutScriptClassPropertyName()`
- L75 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L76 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L81 _private prototype_ `void LayoutRendererComponentChildren();` — Lays out children of the Renderer Component
- L84 _private prototype_ `void LayoutFixtureGroupComponentChildren();` — Lays out children of the Fixture Group Components
- L87 _private prototype_ `void LayoutMatrixComponentChildren();` — Lays out children of the Matrixx Components
- L90 _private prototype_ `void ApplyLayoutTokens(const TArray<FDMXPixelMappingLayoutToken>& LayoutTokens) const;` — Applies the layout of the specified tokens
- L93 _private prototype_ `void OnLayoutScriptClassChanged();` — Called when the Layout Script Class of this Model changed
- L96 _private prototype_ `void OnSelectedComponentsChanged();` — Called when selected Components changed
- L99 _private prototype_ `void InstantiateLayoutScripts();` — Instantiates layout scripts for relevant components
- L102 _private prototype_ `void InitializeLayoutScript(UDMXPixelMappingOutputComponent* OutputComponent, UDMXPixelMappingLayoutScript* LayoutScript);` — Initializes memeber of the Layout Script in specified Component
- L105 _private prototype_ `void RefreshComponents();` — Refreshes components from what's currently selected in the Pixel Mapping Toolkit
- L108 _private prototype_ `void RefreshLayoutScriptClass();` — Refreshes the Layout Script Class
- L111 _private member_ `TWeakPtr<FDMXPixelMappingToolkit> WeakToolkit;` — The toolkit from which the Model currently sources
- L115 _private member_ `TWeakObjectPtr<UDMXPixelMappingRendererComponent> RendererComponent;` — `UPROPERTY()` — The Renderer Component currently in use
- L119 _private member_ `TArray<TWeakObjectPtr<UDMXPixelMappingFixtureGroupComponent>> FixtureGroupComponents;` — `UPROPERTY()` — The Fixture Group Components currently in use
- L123 _private member_ `TArray<TWeakObjectPtr<UDMXPixelMappingMatrixComponent>> MatrixComponents;` — `UPROPERTY()` — The Matrix Components currently in use
- L127 _private member_ `bool bAutoApply = true;` — `UPROPERTY(EditAnywhere, Category = "Layout Script", Meta = (DisplayName = "Apply Script on Property Changes"))` — If true, the script is auto applied on property changes
- L131 _private member_ `TSoftClassPtr<UDMXPixelMappingLayoutScript> LayoutScriptClass;` — `UPROPERTY(EditAnywhere, Category = "Layout Script", Meta = (ShowDisplayNames))` — The Layout Script class currently in use. Note, custom scripts can be blueprinted.
- L134 _private member_ `FTimerHandle ApplyLayoutScriptTimerHandle;` — Timer handle to apply the layout script, set when ApplyLayoutScript is requested.
- L138 _private member_ `TSoftClassPtr<UDMXPixelMappingLayoutScript> PreEditChangeLayoutScriptClass;` — `UPROPERTY(Transient)` — The Layout Script class currently before it was changed

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/ViewModels/DMXPixelMappingOutputComponentModel.h` (Private)


#### class `UE::DMX::FDMXPixelMappingOutputComponentModel`  
`class FDMXPixelMappingOutputComponentModel : public FGCObject , public TSharedFromThis<FDMXPixelMappingOutputComponentModel>`  
_L22-108_
- inherits: `FGCObject,TSharedFromThis<FDMXPixelMappingOutputComponentModel>`
- desc: Model for the Pixel Mapping Output Components. For Screen Component, see DMXPixelMappingScreenComponentModel.
- L28 _public prototype_ `FDMXPixelMappingOutputComponentModel(const TSharedRef<FDMXPixelMappingToolkit>& InToolkit, TWeakObjectPtr<UDMXPixelMappingOutputComponent> InOutputComponent);` — Constructor
- L31 _public prototype_ `virtual ~FDMXPixelMappingOutputComponentModel();` — Destructor
- L34 _public prototype_ `FVector2D GetPosition() const;` — Returns the position of the component
- L37 _public prototype_ `FVector2D GetSize() const;` — Returns the size of the component
- L40 _public prototype_ `FQuat2D GetQuaternion() const;` — Returns the rotation, in degrees
- L43 _public prototype_ `FText GetName() const;` — Returns the Name of the component
- L46 _public prototype_ `bool ShouldDraw() const;` — Returns true if a widget ever should be drawn
- L49 _public prototype_ `bool ShouldDrawName() const;` — Returns true if the name should drawn its name
- L52 _public prototype_ `bool ShouldDrawNameAbove() const;` — Returns true if the name should drawn its name above the widget
- L55 _public prototype_ `bool ShouldDrawCellID() const;` — Returns true if the cell ID should be shown
- L58 _public prototype_ `bool ShouldDrawPatchInfo() const;` — Returns true if the patch info should be shown
- L61 _public prototype_ `bool ShouldDrawPivot() const;` — Returns true if the pivot should be shown
- L64 _public prototype_ `FText GetAddressesText() const;` — Returns the addresses of the patch as text
- L67 _public prototype_ `FText GetFixtureIDText() const;` — Returns the Fixture ID as text. Empty unless a Matrix and Fixture Group Item component
- L70 _public prototype_ `FText GetCellIDText() const;` — Returns the Cell ID as text. Empty unless a Matrix Cell component.
- L73 _public prototype_ `FLinearColor GetColor() const;` — Returns the color of the widget
- L76 _public prototype_ `bool Equals(UDMXPixelMappingBaseComponent* Other) const;` — Returns true if this Model handles the Other component
- L80 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L81 _protected function_ `virtual FString GetReferencerName() const override`
- L89 _private prototype_ `void OnSelectedComponentsChanged();` — Called when selected Components changed
- L92 _private prototype_ `const UDMXEntityFixturePatch* GetFixturePatch() const;` — Returns the Fixture Patch of the component, or nullptr if the component does not use a Fixture Patch.
- L95 _private prototype_ `void UpdateFixtureNode();` — Updates the Fixture Node that correlates to this component
- L98 _private member_ `TWeakObjectPtr<UDMXMVRFixtureNode> WeakFixtureNode;` — The Fixture Node that corresponds to this component, only valid for Group Item and Matrix
- L101 _private member_ `bool bSelected = false;` — True if the component is selected
- L104 _private member_ `TObjectPtr<UDMXPixelMappingOutputComponent> OutputComponent;` — The actual output component
- L107 _private member_ `TWeakPtr<FDMXPixelMappingToolkit> WeakToolkit;` — The toolkit from which the Model currently sources

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace DMX` (scope `UE`)

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Viewports/DMXPixelMappingPreviewViewportClient.h` (Private)


#### class `FDMXPixelMappingPreviewViewportClient`  
`class FDMXPixelMappingPreviewViewportClient : public FViewportClient`  
_L11-32_
- inherits: `FViewportClient`
- L16 _public prototype_ `FDMXPixelMappingPreviewViewportClient(TWeakPtr<FDMXPixelMappingToolkit> InWeakToolkit, TWeakPtr<SDMXPixelMappingPreviewViewport> InWeakViewport);` — Constructor
- L19 _public prototype_ `bool IsDrawingVisibleRectOnly() const;` — If true, the widget draws the visible rect of the source texture
- L22 _public prototype_ `FBox2D GetVisibleTextureBoxGraphSpace() const;` — Returns the visible texture size in graph space
- L26 _protected prototype_ `virtual void Draw(FViewport* Viewport, FCanvas* Canvas) override;`
- L30 _private member_ `TWeakPtr<FDMXPixelMappingToolkit> WeakToolkit;`
- L31 _private member_ `TWeakPtr<SDMXPixelMappingPreviewViewport> WeakViewport;`

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Viewports/DMXPixelMappingSceneViewport.h` (Private)


#### class `FDMXPixelMappingSceneViewport`  
`class FDMXPixelMappingSceneViewport : public FSceneViewport`  
_L10-108_
- inherits: `FSceneViewport`
- desc: Pixel Mapping Scene Viewport disable viewport input handle, it let use a custom handle in designer
- L14 _public function_ `FDMXPixelMappingSceneViewport(const TSharedPtr<SViewport>& InViewportWidget) : FSceneViewport(InViewportWidget)`
- L19 _public function_ `static TSharedRef<FDMXPixelMappingSceneViewport> Create(const TSharedPtr<FViewportClient>& InViewportClient, const TSharedPtr<SViewport>& InViewportWidget)`
- L25 _protected function_ `virtual FReply OnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& MouseEvent) override`
- L32 _protected function_ `virtual FReply OnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& MouseEvent) override`
- L39 _protected function_ `virtual FReply OnMouseMove(const FGeometry& InGeometry, const FPointerEvent& MouseEvent) override`
- L46 _protected function_ `virtual FReply OnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& MouseEvent) override`
- L53 _protected function_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override`
- L60 _protected function_ `virtual FReply OnTouchStarted(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent) override`
- L67 _protected function_ `virtual FReply OnTouchMoved(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent) override`
- L74 _protected function_ `virtual FReply OnTouchEnded(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent) override`
- L81 _protected function_ `virtual FReply OnTouchForceChanged(const FGeometry& MyGeometry, const FPointerEvent& TouchEvent) override`
- L88 _protected function_ `virtual FReply OnTouchFirstMove(const FGeometry& MyGeometry, const FPointerEvent& TouchEvent) override`
- L95 _protected function_ `virtual FReply OnTouchGesture(const FGeometry& MyGeometry, const FPointerEvent& InGestureEvent) override`
- L102 _protected function_ `virtual FReply OnMotionDetected(const FGeometry& MyGeometry, const FMotionEvent& InMotionEvent) override`

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Viewports/DMXPixelMappingSourceTextureViewportClient.h` (Private)


#### class `FDMXPixelMappingSourceTextureViewportClient`  
`class FDMXPixelMappingSourceTextureViewportClient : public FCommonViewportClient`  
_L11-39_
- inherits: `FCommonViewportClient`
- L16 _public prototype_ `FDMXPixelMappingSourceTextureViewportClient(const TSharedPtr<FDMXPixelMappingToolkit>& Toolkit, TWeakPtr<SDMXPixelMappingSourceTextureViewport> InViewport);` — Constructor
- L19 _public prototype_ `bool IsDrawingVisibleRectOnly() const;` — If true, the widget draws the visible rect of the source texture
- L22 _public prototype_ `FBox2D GetVisibleTextureBoxGraphSpace() const;` — Returns the visible texture size in graph space
- L26 _protected prototype_ `virtual void Draw(FViewport* Viewport, FCanvas* Canvas) override;`
- L27 _protected function_ `virtual bool ShouldDPIScaleSceneCanvas() const override`
- L31 _protected prototype_ `virtual float UpdateViewportClientWindowDPIScale() const override;`
- L35 _private member_ `bool bUseDPIScaling = false;`
- L37 _private member_ `TWeakPtr<FDMXPixelMappingToolkit> WeakToolkit;`
- L38 _private member_ `TWeakPtr<SDMXPixelMappingSourceTextureViewport> WeakSourceTextureViewport;`

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Views/SDMXPixelMappingDMXLibraryView.h` (Private)


#### class `SDMXPixelMappingDMXLibraryView`  
`class SDMXPixelMappingDMXLibraryView : public SCompoundWidget , public FGCObject , public FSelfRegisteringEditorUndoClient`  
_L28-127_
- inherits: `SCompoundWidget,FGCObject,FSelfRegisteringEditorUndoClient`
- desc: Displays the DMX Library of the currently selected fixture group component
- L34 _public function_ `SLATE_BEGIN_ARGS(SDMXPixelMappingDMXLibraryView)`
- L39 _public prototype_ `virtual ~SDMXPixelMappingDMXLibraryView();`
- L42 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedPtr<FDMXPixelMappingToolkit>& InToolkit);` — Constructs this widget
- L45 _public prototype_ `void RequestRefresh();` — Refreshes the widget on the next tick
- L49 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L50 _protected function_ `virtual FString GetReferencerName() const override`
- L57 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L58 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L63 _private prototype_ `void ForceRefresh();` — Refreshes the widget
- L66 _private prototype_ `void OnComponentSelected();` — Called when a component was selected
- L69 _private prototype_ `void OnEntityAddedOrRemoved(UDMXLibrary* DMXLibrary, TArray<UDMXEntity*> Entities);` — Called when an entity was added or removed from the DMX Library
- L72 _private prototype_ `void OnComponentAddedOrRemoved(UDMXPixelMapping* PixelMapping, UDMXPixelMappingBaseComponent* Component);` — Called when a component was added or removed from pixel mapping
- L75 _private prototype_ `FReply OnAddFixtureGroupButtonClicked();` — Called when the 'Add Fixture Group' button was clicked
- L78 _private prototype_ `FReply OnAddSelectedPatchesClicked();` — Called when the 'Add Selected Patches' button was clicked
- L81 _private prototype_ `FReply OnAddAllPatchesClicked();` — Called when the 'Add All Patches' button was clicked
- L84 _private prototype_ `ECheckBoxState GetUsePatchColorCheckState() const;` — Returns the check state of the 'use patch color' check box
- L87 _private prototype_ `void OnUsePatchColorCheckStateChanged(ECheckBoxState NewCheckState);` — Called when the check state of the 'use patch color' check box changed
- L90 _private prototype_ `TArray<UDMXEntityFixturePatch*> GetFixturePatchesInDMXLibrary() const;` — Helper that returns all fixture patches in use in the pixel mapping
- L93 _private prototype_ `TArray<UDMXEntityFixturePatch*> GetFixturePatchesInPixelMapping() const;` — Helper that returns all fixture patches in use in the pixel mapping
- L96 _private member_ `TSharedPtr<SBorder> DMXLibraryBorder;` — Border that holds the details views
- L99 _private member_ `FTimerHandle RefreshTimerHandle;` — Timer handle for the Request Refresh method
- L102 _private member_ `bool bRenderComponentContainedInSelection = false;` — True if a renderere component is contained in the current selection
- L105 _private member_ `TSharedPtr<STextBlock> FixtureGroupNameTextBlock;` — Text block displaying the selected fixture group name
- L108 _private member_ `TSharedPtr<SWidgetSwitcher> ListOrAllPatchesAddedSwitcher;` — Switches between the list and the all patches added text blocok
- L111 _private member_ `TSharedPtr<SDMXPixelMappingFixturePatchList> FixturePatchList;` — List of fixture patches the user can select from
- L114 _private member_ `TSharedPtr<STextBlock> AllPatchesAddedTextBlock;` — Text block displaying 'all patches added' when no patches are available to add from the dmx library
- L117 _private member_ `TSharedPtr<SWrapBox> AddPatchesWrapBox;` — Wrap box containing the 'add selected patches' and 'add all patches' buttons and the 'Use Patch Color' checkbox
- L120 _private member_ `TSharedPtr<IDetailsView> ModelDetailsView;` — Details view for the model, displays the library picker
- L123 _private member_ `TObjectPtr<UDMXPixelMappingDMXLibraryViewModel> ViewModel;` — The view model of the focused DMX Library
- L126 _private member_ `TWeakPtr<FDMXPixelMappingToolkit> WeakToolkit;` — The toolkit of this editor

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Views/SDMXPixelMappingDesignerView.h` (Private)


#### class `SDMXPixelMappingDesignerView`  
`class SDMXPixelMappingDesignerView : public SDMXPixelMappingSurface , public FSelfRegisteringEditorUndoClient`  
_L26-214_
- inherits: `SDMXPixelMappingSurface,FSelfRegisteringEditorUndoClient`
- L45 _public function_ `SLATE_BEGIN_ARGS(SDMXPixelMappingDesignerView)`
- L48 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FDMXPixelMappingToolkit>& InToolkit);`
- L58 _public prototype_ `const FGeometry& GetGraphTickSpaceGeometry() const;` — Returns the geometry of the graph
- L62 _protected prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L63 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L64 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L65 _protected prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L66 _protected prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L67 _protected prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L68 _protected prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L69 _protected prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L70 _protected prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L71 _protected prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L75 _protected prototype_ `virtual FSlateRect ComputeAreaBounds() const override;`
- L76 _protected prototype_ `virtual int32 GetGraphRulePeriod() const override;`
- L77 _protected prototype_ `virtual float GetGridScaleAmount() const override;`
- L78 _protected prototype_ `virtual int32 GetGridSize() const override;`
- L82 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L83 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L88 _private prototype_ `void RebuildDesigner();` — Rebuilds the designer widget
- L91 _private prototype_ `void CreateExtensionWidgetsForSelection();` — Creates the extension widgets for the selected component
- L94 _private prototype_ `void ClearExtensionWidgets();` — Clears the extension widgets
- L97 _private prototype_ `void OpenContextMenu();` — Opens the designer context menu
- L100 _private prototype_ `EVisibility GetExtensionCanvasVisibility() const;` — Returns if the extension widget canvas should be visible
- L103 _private prototype_ `FVector2D GetExtensionPosition(TSharedPtr<SDMXPixelMappingTransformHandle> Handle);` — Gets the positioin of the extension widget
- L106 _private prototype_ `FVector2D GetExtensionSize(TSharedPtr<SDMXPixelMappingTransformHandle> Handle);` — Gets the size of the extension widget
- L109 _private prototype_ `FText GetHoveredComponentNameText() const;` — Returns text for the currently hovered component
- L112 _private prototype_ `FText GetHoveredComponentParentNameText() const;` — Returns text for the currently hovered component's parent
- L115 _private prototype_ `EVisibility GetRulerVisibility() const;` — Returns the visibility of the side rulers
- L118 _private prototype_ `FText GetCursorPositionText() const;` — Returns the cursor position as text
- L121 _private prototype_ `EVisibility GetCursorPositionTextVisibility() const;` — Returns the visibility of the cursor position text block
- L124 _private prototype_ `EVisibility GetZoomPanVisibility() const;` — Returns the visibility of the ZoomPan widget
- L127 _private prototype_ `FReply OnZoomToFitClicked();` — Called when zoom to fit was clicked
- L130 _private prototype_ `void OnComponentAdded(UDMXPixelMapping* PixelMapping, UDMXPixelMappingBaseComponent* Component);` — Called when a component was added
- L133 _private prototype_ `void OnComponentRemoved(UDMXPixelMapping* PixelMapping, UDMXPixelMappingBaseComponent* Component);` — Called when a component was removed
- L136 _private prototype_ `void OnSelectedComponentsChanged();` — Called when the selected component in the toolkit changed
- L139 _private prototype_ `void ResolvePendingSelectedComponents(bool bClearPreviousSelection = false);` — Adds any pending selected Components to the selection set
- L141 _private prototype_ `void PopulateWidgetGeometryCache(FArrangedWidget& Root);`
- L143 _private prototype_ `void PopulateWidgetGeometryCache_Loop(FArrangedWidget& Parent);`
- L146 _private prototype_ `UDMXPixelMappingOutputComponent* GetComponentUnderCursor() const;` — Returns the component under the cursor
- L149 _private prototype_ `TSet<FDMXPixelMappingComponentReference> GetSelectedComponents() const;` — Returns the selected components
- L152 _private prototype_ `FDMXPixelMappingComponentReference GetSelectedComponent() const;` — Returns the first best selected component
- L155 _private prototype_ `bool GetComponentGeometry(FDMXPixelMappingComponentReference InComponentReference, FGeometry& OutGeometry);` — Gets the Geometry of the component, returns true if successful
- L158 _private prototype_ `bool GetComponentGeometry(UDMXPixelMappingBaseComponent* InBaseComponent, FGeometry& OutGeometry);` — Gets the Geometry of the component, returns true if successful
- L161 _private prototype_ `bool GetGraphSpaceCursorPosition(FVector2D& OutGraphSpaceCursorPosition) const;` — Returns the cursor position in graph space
- L163 _private prototype_ `FGeometry GetDesignerGeometry() const;`
- L165 _private prototype_ `FGeometry MakeGeometryWindowLocal(const FGeometry& WidgetGeometry) const;`
- L168 _private prototype_ `void HandleDragEnterFromDetailsOrPalette(const TSharedPtr<FDMXPixelMappingDragDropOp>& DragDropOp);` — Updates the drag drop op to use the patches selected in the Palette
- L171 _private member_ `TWeakObjectPtr<UDMXPixelMappingBaseComponent> PendingSelectedComponent;` — The component that should be selected, but isn't selected yet
- L174 _private member_ `TSharedPtr<FDMXPixelMappingDragDropOp> PendingDragDropOp;` — The drag over DragDropOp that should be handled on the next tick
- L177 _private member_ `TSharedPtr<SCanvas> ExtensionWidgetCanvas;` — Canvas that holds the extension widget
- L180 _private member_ `TSharedPtr<SDMXPixelMappingSourceTextureViewport> SourceTextureViewport;` — Widget that holds the source texture
- L183 _private member_ `TSharedPtr<SConstraintCanvas> DesignCanvas;` — Canvas that holds the component widgets
- L185 _private member_ `TSharedPtr<SOverlay> PreviewHitTestRoot;`
- L188 _private member_ `TSharedPtr<SBorder> DesignCanvasBorder;` — Borer that contains the Design Canvas
- L191 _private member_ `FVector2D CursorPositionGraphSpace = FVector2D::ZeroVector;` — Cached cursor position in graph space
- L193 _private member_ `TMap<TWeakPtr<SWidget>, FArrangedWidget> CachedWidgetGeometry;`
- L196 _private member_ `TWeakObjectPtr<UDMXPixelMappingRendererComponent> CachedRendererComponent;` — Cached current renderer component
- L199 _private member_ `TSharedPtr<SDMXPixelMappingZoomPan> ZoomPan;` — The widget that handles zoom and pan
- L202 _private member_ `TSharedPtr<SDMXPixelMappingRuler> TopRuler;` — The ruler bar at the top of the designer.
- L205 _private member_ `TSharedPtr<SDMXPixelMappingRuler> SideRuler;` — The ruler bar on the left side of the designer.
- L208 _private member_ `FVector2D DragAnchor;` — The position in local space where the user began dragging a widget
- L211 _private member_ `TArray<TSharedRef<UE::DMX::IDMXPixelMappingOutputComponentWidgetInterface>> OutputComponentWidgets;` — Output component views currently displayed
- L213 _private member_ `TArray<TSharedPtr<SDMXPixelMappingTransformHandle>> TransformHandles;`

#### struct `SDMXPixelMappingDesignerView::FComponentHitResult`  
`struct FComponentHitResult`  
_L31-42_
- L34 _public member_ `TWeakObjectPtr<UDMXPixelMappingBaseComponent> Component;`
- L35 _public member_ `FArrangedWidget WidgetArranged;`
- L36 _public member_ `FName NamedSlot;`
- L39 _public function_ `FComponentHitResult() : WidgetArranged(SNullWidget::NullWidget, FGeometry())`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace DMX` (scope `UE`)

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Views/SDMXPixelMappingDetailsView.h` (Private)


#### class `SDMXPixelMappingDetailsView`  
`class SDMXPixelMappingDetailsView : public SCompoundWidget`  
_L12-41_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SDMXPixelMappingDetailsView)`
- L26 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedPtr<FDMXPixelMappingToolkit>& InToolkit);` — Constructs the widget. @param InArgs The construction arguments.
- L29 _private prototype_ `void OnSelectedComponentsChanged();`
- L32 _private prototype_ `void RegisterCustomizations();` — Registers the designer specific customizations
- L34 _private member_ `TWeakPtr<FDMXPixelMappingToolkit> WeakToolkit;`
- L37 _private member_ `TSharedPtr<IDetailsView> DetailsView;` — The details view that is displayed
- L40 _private member_ `TArray<TWeakObjectPtr<UObject>> SelectedObjects;` — Selected objects for this detail view

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Views/SDMXPixelMappingHierarchyView.h` (Private)


#### class `SDMXPixelMappingHierarchyView`  
`class SDMXPixelMappingHierarchyView final : public SCompoundWidget , public FSelfRegisteringEditorUndoClient`  
_L26-164_
- inherits: `SCompoundWidget,FSelfRegisteringEditorUndoClient`
- L31 _public function_ `SLATE_BEGIN_ARGS(SDMXPixelMappingHierarchyView)`
- L48 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedPtr<FDMXPixelMappingToolkit>& InToolkit);` — Constructs the widget. @param InArgs The construction arguments.
- L51 _public prototype_ `void RequestRefresh();` — Refreshes the widget on the next tick
- L55 _private prototype_ `void ForceRefresh();` — Refreshes the widget
- L58 _private prototype_ `void BuildChildSlotAndRefresh();` — Builds the child slot anew and refreshes the widget
- L61 _private prototype_ `TSharedRef<SHeaderRow> GenerateHeaderRow();` — Generates the header row for the tree view
- L64 _private prototype_ `TSharedRef<SWidget> GenerateHeaderRowFilterMenu();` — Generates the header row filter menu
- L67 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L71 _private prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L72 _private prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L76 _private prototype_ `void OnGetChildItems(TSharedPtr<FDMXPixelMappingHierarchyItem> InParent, TArray<TSharedPtr<FDMXPixelMappingHierarchyItem>>& OutChildren);` — Called to get child items
- L79 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FDMXPixelMappingHierarchyItem> Item, const TSharedRef<STableViewBase>& OwnerTable);` — Called when a row is generated
- L82 _private prototype_ `TSharedPtr<SWidget> OnContextMenuOpening();` — Called when the context menu is opening
- L85 _private prototype_ `void OnHierarchySelectionChanged(TSharedPtr<FDMXPixelMappingHierarchyItem> Item, ESelectInfo::Type SelectInfo);` — Called when selection changed in the hierarchy
- L88 _private prototype_ `void OnHierarchyExpansionChanged(TSharedPtr<FDMXPixelMappingHierarchyItem> Item, bool bExpanded);` — Called when selection changed in the hierarchy
- L91 _private prototype_ `void ToggleColumnVisility(FName ColumnId);` — Toggles the visibility of a column
- L94 _private prototype_ `bool IsColumVisible(FName ColumnId) const;` — Returns true if the specified column is currently visible
- L97 _private prototype_ `EColumnSortMode::Type GetColumnSortMode(FName ColumnId) const;` — Gets the sort mode for the given column ID
- L100 _private prototype_ `void SetSortAndRefresh(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode);` — Set the current sorting state of the hierarchy tree view and refreshes the tree, applying the new sorting
- L103 _private prototype_ `void OnComponentAddedOrRemoved(UDMXPixelMapping* PixelMapping, UDMXPixelMappingBaseComponent* Component);` — Called when a component was added or removed from the pixel mapping
- L106 _private prototype_ `void OnEditorSelectionChanged();` — Called when the selected widget has changed.  The treeview then needs to match the new selection.
- L109 _private prototype_ `void AdoptSelectionFromToolkit();` — Adopts the current selection of the toolkit
- L112 _private prototype_ `void RecursiveAdoptSelectionFromToolkit(const TSharedRef<FDMXPixelMappingHierarchyItem>& Model);` — Adopts the selection from toolkit
- L115 _private prototype_ `bool CanRenameSelectedComponent() const;` — Returns true if the current selection can to be renamed
- L118 _private prototype_ `void RenameSelectedComponent();` — Renames selected components
- L121 _private prototype_ `bool CanDeleteSelectedComponents() const;` — Returns true if the current selection can to be deleted
- L124 _private prototype_ `void DeleteSelectedComponents();` — Deletes selected components
- L127 _private prototype_ `void SetFilterText(const FText& Text);` — Sets the text for the filter
- L130 _private prototype_ `void GetWidgetFilterStrings(TSharedPtr<FDMXPixelMappingHierarchyItem> InModel, TArray<FString>& OutStrings) const;` — Gets an array of strings used for filtering/searching the specified widget.
- L133 _private member_ `bool bIsUpdatingSelection = false;` — Flag to ignore selections while the hierarchy view is updating the selection.
- L136 _private member_ `TArray<TSharedPtr<FDMXPixelMappingHierarchyItem>> TreeItems;` — All items in the tree
- L139 _private member_ `TArray<TSharedPtr<FDMXPixelMappingHierarchyItem>> FilteredRootItems;` — Root items being displayed
- L142 _private member_ `TArray<TSharedPtr<FDMXPixelMappingHierarchyItem>> AllRootItems;` — All root items
- L145 _private member_ `TSharedPtr<SSearchBox> SearchBox;` — The search box widget
- L148 _private member_ `TSharedPtr<STreeView<TSharedPtr<FDMXPixelMappingHierarchyItem>>> HierarchyTreeView;` — The hierarchy tree view widget
- L151 _private member_ `TSharedPtr<TreeFilterHandler<TSharedPtr<FDMXPixelMappingHierarchyItem>>> FilterHandler;` — Handles filtering the hierarchy based on an IFilter.
- L154 _private member_ `TSharedPtr<TTextFilter<TSharedPtr<FDMXPixelMappingHierarchyItem>>> SearchFilter;` — Text filter for the filter handler, set from the search bbox
- L157 _private member_ `FTimerHandle RequestRefreshTimerHandle;` — Timer handle for the request refresh timer
- L160 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Commands specific to the hierarchy.
- L163 _private member_ `TWeakPtr<FDMXPixelMappingToolkit> WeakToolkit;` — The toolkit that contains this widget

#### struct `SDMXPixelMappingHierarchyView::FColumnIds`  
`struct FColumnIds`  
_L35-41_
- desc: ColumnIds for the tree view
- L37 _public member_ `static const FName EditorColor;`
- L38 _public member_ `static const FName ComponentName;`
- L39 _public member_ `static const FName FixtureID;`
- L40 _public member_ `static const FName Patch;`

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Views/SDMXPixelMappingLayoutView.h` (Private)


#### class `SDMXPixelMappingLayoutView`  
`class SDMXPixelMappingLayoutView : public SCompoundWidget , public FGCObject , public FEditorUndoClient , public FNotifyHook`  
_L16-75_
- inherits: `SCompoundWidget,FGCObject,FEditorUndoClient,FNotifyHook`
- L23 _public function_ `SLATE_BEGIN_ARGS(SDMXPixelMappingLayoutView)`
- L28 _public prototype_ `virtual ~SDMXPixelMappingLayoutView();` — Destructor
- L31 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FDMXPixelMappingToolkit>& InToolkit);` — Constructs the widget
- L35 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L36 _protected function_ `virtual FString GetReferencerName() const override`
- L43 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L44 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L48 _protected prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;`
- L53 _private prototype_ `void Refresh();` — Refreshes the widget
- L56 _private prototype_ `TSharedRef<SWidget> CreateLayoutSettingsDetailsView();` — Creates a Details view of the Layout Settings
- L59 _private prototype_ `TSharedRef<SWidget> CreateLayoutModelDetailsView();` — Creates a Details view of the Layout Model
- L62 _private prototype_ `void InitializeLayoutScriptsDetailsView();` — Creates a details view of the Layout Script
- L65 _private member_ `bool bDidPropertiesEverChange = false;` — True when the details views in this widget ever changed properties
- L68 _private member_ `TSharedPtr<IDetailsView> LayoutScriptDetailsView;` — The Layout Script Details View
- L71 _private member_ `TObjectPtr<UDMXPixelMappingLayoutViewModel> Model;` — Model for this view
- L74 _private member_ `TWeakPtr<FDMXPixelMappingToolkit> WeakToolkit;` — Toolkit for this view

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Views/SDMXPixelMappingPreviewView.h` (Private)


#### class `SDMXPixelMappingPreviewView`  
`class SDMXPixelMappingPreviewView : public SDMXPixelMappingSurface`  
_L16-98_
- inherits: `SDMXPixelMappingSurface`
- L21 _public function_ `SLATE_BEGIN_ARGS(SDMXPixelMappingPreviewView)`
- L30 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedPtr<FDMXPixelMappingToolkit>& InToolkit);` — Constructs the widget. @param InArgs The construction arguments.
- L33 _public prototype_ `const FGeometry& GetGraphTickSpaceGeometry() const;` — Returns the geometry of the graph
- L37 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — SWidget interface
- L38 _protected prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L39 _protected prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L40 _protected prototype_ `virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L41 _protected prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L42 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L43 _protected prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L44 _protected prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L45 _protected prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L46 _protected prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L47 _protected prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L51 _protected prototype_ `virtual void OnPaintBackground(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId) const override;`
- L52 _protected prototype_ `virtual int32 GetGraphRulePeriod() const override;`
- L53 _protected prototype_ `virtual float GetGridScaleAmount() const override;`
- L54 _protected prototype_ `virtual int32 GetGridSize() const override;`
- L55 _protected prototype_ `virtual FSlateRect ComputeAreaBounds() const override;`
- L60 _private prototype_ `FOptionalSize GetHeightGraphSpace() const;` — Gets the height in graph space
- L63 _private prototype_ `FOptionalSize GetWidthGraphSpace() const;` — Gets the width in graph space
- L65 _private prototype_ `TSharedRef<SWidget> CreateOverlayUI();`
- L67 _private prototype_ `EVisibility IsZoomPanVisible() const;`
- L69 _private prototype_ `FGeometry MakeGeometryWindowLocal(const FGeometry& WidgetGeometry) const;`
- L71 _private prototype_ `FGeometry GetDesignerGeometry() const;`
- L72 _private prototype_ `void PopulateWidgetGeometryCache(FArrangedWidget& Root);`
- L73 _private prototype_ `void PopulateWidgetGeometryCache_Loop(FArrangedWidget& Parent);`
- L75 _private prototype_ `FReply HandleZoomToFitClicked();`
- L77 _private prototype_ `const TSet<FDMXPixelMappingComponentReference>& GetSelectedComponents() const;`
- L79 _private prototype_ `FDMXPixelMappingComponentReference GetSelectedComponent() const;`
- L81 _private prototype_ `FText GetSelectedComponentNameText() const;`
- L82 _private prototype_ `FText GetSelectedComponentParentNameText() const;`
- L83 _private prototype_ `EVisibility GetTitleBarVisibility() const;`
- L86 _private member_ `TSharedPtr<SDMXPixelMappingZoomPan> ZoomPan;` — Zoom pan widget
- L88 _private member_ `TSharedPtr<SDMXPixelMappingPreviewViewport> PreviewViewport;`
- L91 _private member_ `FVector2D CachedMousePosition;` — Cache last mouse position to be used as a paste drop location
- L93 _private member_ `TSharedPtr<SBox> PreviewSizeConstraint;`
- L95 _private member_ `TSharedPtr<SOverlay> PreviewHitTestRoot;`
- L97 _private member_ `TMap<TSharedRef<SWidget>, FArrangedWidget> CachedWidgetGeometry;`

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Widgets/SDMXPixelMappingDesignerCanvas.h` (Private)


#### class `SDMXPixelMappingDesignerCanvas`  
`class SDMXPixelMappingDesignerCanvas : public SConstraintCanvas`  
_L12-47_
- inherits: `SConstraintCanvas`
- desc: Most of the logic copied from a Engine/Source/Runtime/Slate/Public/Widgets/Layout/SConstraintCanvas.h We need to remove condition if (!IsChildWidgetCulled(MyCullingRect, CurWidget)) from OnPaint function
- L16 _public function_ `SLATE_BEGIN_ARGS(SDMXPixelMappingDesignerCanvas)`
- L18 _public prototype_ `SLATE_END_ARGS();`
- L25 _public prototype_ `void Construct(const FArguments& InArgs);` — Construct the widget @param InArgs   A declaration from which to construct the widget
- L41 _private typedef_ `typedef TArray<bool, TInlineAllocator<16>> FArrangedChildLayers;` — An array matching the length and order of ArrangedChildren. True means the child must be placed in a layer in front of all previous children.
- L43 _private prototype_ `void ArrangeLayeredChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren, FArrangedChildLayers& ArrangedChildLayers) const;` — Like ArrangeChildren but also generates an array of layering information (see FArrangedChildLayers).
- L46 _protected prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;` — SWidget interface

#### struct `SDMXPixelMappingDesignerCanvas::FChildZOrder`  
`struct FChildZOrder`  
_L28-32_
- L30 _public member_ `int32 ChildIndex;`
- L31 _public member_ `float ZOrder;`

#### struct `SDMXPixelMappingDesignerCanvas::FSortSlotsByZOrder`  
`struct FSortSlotsByZOrder`  
_L33-39_
- L35 _public function_ `bool operator()(const FChildZOrder& A, const FChildZOrder& B) const`

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Widgets/SDMXPixelMappingDesignerToolbar.h` (Private)


#### class `UE::DMX::SDMXPixelMappingDesignerToolbar`  
`class SDMXPixelMappingDesignerToolbar : public SViewportToolBar`  
_L17-79_
- inherits: `SViewportToolBar`
- L21 _public function_ `SLATE_BEGIN_ARGS(SDMXPixelMappingDesignerToolbar)`
- L25 _public prototype_ `SLATE_EVENT(FOnClicked, OnZoomToFitClicked) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FDMXPixelMappingToolkit>& InToolkit);` — Event raised when zoom to fit was clicked
- L33 _private prototype_ `TSharedRef<SWidget> GenerateTransformHandleModeSection();`
- L34 _private prototype_ `TSharedRef<SWidget> GenerateGridSnappingSection();`
- L35 _private prototype_ `TSharedRef<SWidget> GenerateZoomToFitSection(const FArguments& InArgs);`
- L36 _private prototype_ `TSharedRef<SWidget> GenerateSettingsSection();`
- L39 _private prototype_ `TSharedRef<SWidget> GenerateSnapGridMenu();` — Generates the grid snapping menu
- L42 _private prototype_ `FText GetSnapGridLabel() const;` — Returns the grid snapping label
- L45 _private prototype_ `ECheckBoxState GetSnapGridEnabledCheckState() const;` — Gets the check box state according to grid snapping being enabled
- L48 _private prototype_ `void OnSnapGridCheckStateChanged(ECheckBoxState NewCheckBoxState);` — Called when the grid snapping checkbox state changed
- L51 _private prototype_ `void OnTransformHandleModeSelected(ECheckBoxState DummyCheckBoxState, UE::DMX::EDMXPixelMappingTransformHandleMode NewTransformHandleMode);` — Called when a transform handle mode was selected. The checkbox state can be ignored. Instead clicking always enables.
- L54 _private prototype_ `ECheckBoxState GetCheckboxStateForTransormHandleMode(UE::DMX::EDMXPixelMappingTransformHandleMode TransformHandleMode) const;` — Returns the current checkbox state of the transform mode
- L57 _private prototype_ `TSharedRef<SWidget> GenerateSettingsMenuContent();` — Generates the contents of the settings menu
- L60 _private prototype_ `TSharedRef<SWidget> GenerateComponentFontSizeEditWidget();` — Generates a widget to edit the font size
- L63 _private prototype_ `TOptional<uint8> GetComponentFontSize() const;` — Gets the font size for component labels in the designer view
- L66 _private prototype_ `void SetComponentFontSize(uint8 FontSize);` — Sets the font size for component labels in the designer view
- L69 _private prototype_ `TSharedRef<SWidget> GenerateDesignerExposureEditWidget();` — Generates a widget to edit the display exposure
- L72 _private prototype_ `TOptional<float> GetDesignerExposure() const;` — Gets the exposure of the designer view
- L75 _private prototype_ `void SetDesignerExposure(float Exposure);` — Sets the exposure of the designer view
- L78 _private member_ `TWeakPtr<FDMXPixelMappingToolkit> WeakToolkit;` — The toolkit that owns this widget

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DMX` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace DMX` (scope `UE`)

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Widgets/SDMXPixelMappingFixturePatchList.h` (Private)


#### class `SDMXPixelMappingFixturePatchList`  
`class SDMXPixelMappingFixturePatchList final : public SDMXReadOnlyFixturePatchList`  
_L14-50_
- inherits: `SDMXReadOnlyFixturePatchList`
- desc: Displays the DMX Library of the currently selected fixture group component
- L18 _public function_ `SLATE_BEGIN_ARGS(SDMXPixelMappingFixturePatchList)`
- L21 _public prototype_ `SLATE_ARGUMENT(FDMXReadOnlyFixturePatchListDescriptor, ListDescriptor) SLATE_EVENT(FOnContextMenuOpening, OnContextMenuOpening) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<FDMXPixelMappingToolkit>& InToolkit, TWeakObjectPtr<UDMXPixelMappingDMXLibraryViewModel> InDMXLibraryModel);` — Describes the initial state of the list
- L32 _public prototype_ `void SelectAfter(const TArray<UDMXEntityFixturePatch*>& FixturePatches);` — Selects the first patch after the specified fixture patches
- L36 _private prototype_ `virtual void ForceRefresh() override;`
- L40 _private prototype_ `FReply OnRowDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — Called when a row in the list was dragged
- L43 _private member_ `TArray<TSharedPtr<FDMXEntityFixturePatchRef>> HiddenFixturePatches;` — Holds the fixutre patches which are hidden the list
- L46 _private member_ `TWeakObjectPtr<UDMXPixelMappingDMXLibraryViewModel> WeakDMXLibraryViewModel;` — View model of the displayed dmx library
- L49 _private member_ `TWeakPtr<FDMXPixelMappingToolkit> WeakToolkit;` — The toolkit of the editor that displays this widget

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Widgets/SDMXPixelMappingHierarchyRow.h` (Private)


#### class `SDMXPixelMappingHierarchyRow`  
`class SDMXPixelMappingHierarchyRow final : public SMultiColumnTableRow<TSharedPtr<FDMXPixelMappingHierarchyItem>>`  
_L19-73_
- inherits: `SMultiColumnTableRow<TSharedPtr<FDMXPixelMappingHierarchyItem>>`
- desc: Displays a single item in a hierarchy view
- L23 _public function_ `SLATE_BEGIN_ARGS(SDMXPixelMappingHierarchyRow)`
- L26 _public prototype_ `SLATE_EVENT(FOnDragDetected, OnItemDragDetected) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, TWeakPtr<FDMXPixelMappingToolkit> InWeakToolkit, const TSharedRef<FDMXPixelMappingHierarchyItem>& InItem);` — Delegate executed when a row was dragged
- L34 _public prototype_ `void EnterRenameMode();` — Starts editing the name of the component of this row
- L38 _private prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L42 _private prototype_ `TSharedRef<SWidget> GenerateEditorColorWidget();` — Generates a widget to display the editor color
- L45 _private prototype_ `TSharedRef<SWidget> GenerateComponentNameWidget();` — Generates a widget to display the name
- L48 _private prototype_ `TSharedRef<SWidget> GenerateFixtureIDWidget();` — Generates a widget to display the fixture ID
- L51 _private prototype_ `TSharedRef<SWidget> GeneratePatchWidget();` — Generates a widget to display the patch
- L54 _private prototype_ `bool OnVerifyNameTextChanged(const FText& InText, FText& OutErrorMessage);` — Called to verify the changed name in the related editable text block
- L57 _private prototype_ `void OnNameTextCommited(const FText& InText, ETextCommit::Type CommitInfo);` — Called when text is committed on the node
- L60 _private prototype_ `FReply OnRowDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — Called when this row was dragged
- L63 _private member_ `TSharedPtr<FDMXPixelMappingHierarchyItem> Item;` — Model of the component being displayed
- L66 _private member_ `TSharedPtr<SImage> EditorColorImageWidget;` — The editor color image widget
- L69 _private member_ `TSharedPtr<SInlineEditableTextBlock> EditableNameTextBox;` — Text box that displays and allows to edit the name
- L72 _private member_ `TWeakPtr<FDMXPixelMappingToolkit> WeakToolkit;` — Weak toolkit this widget belongs to

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Widgets/SDMXPixelMappingOutputComponent.h` (Private)


#### class `UE::DMX::IDMXPixelMappingOutputComponentWidgetInterface`  
`class IDMXPixelMappingOutputComponentWidgetInterface`  
_L21-49_
- desc: Interface for Output Component Widgets
- L25 _public prototype_ `virtual ~IDMXPixelMappingOutputComponentWidgetInterface();` — Destructor
- L28 _public prototype_ `void AddToCanvas(const TSharedRef<SConstraintCanvas>& InCanvas);` — Adds the widgets to a canvas. If it already resides in a canvas it is removed from that first.
- L31 _public prototype_ `void RemoveFromCanvas();` — Removes the widget from the canvas, if it was added to one.
- L34 _public prototype_ `virtual TSharedRef<SWidget> AsWidget() = 0;` — Returns the actual widget implementation
- L37 _public prototype_ `virtual bool Equals(UDMXPixelMappingBaseComponent* Component) const = 0;` — Returns true if the widet equals the component
- L41 _protected prototype_ `virtual FVector2D GetPosition() const = 0;` — Returns the position of the widget
- L45 _private member_ `TWeakPtr<SConstraintCanvas> ParentCanvas;` — When added to a parent, the canvas it was added to
- L48 _private member_ `SConstraintCanvas::FSlot* Slot = nullptr;` — The canvas slot of the component widget

#### class `UE::DMX::SDMXPixelMappingOutputComponent`  
`class SDMXPixelMappingOutputComponent : public IDMXPixelMappingOutputComponentWidgetInterface , public SCompoundWidget`  
_L53-87_
- inherits: `IDMXPixelMappingOutputComponentWidgetInterface,SCompoundWidget`
- desc: Widget that draws an Output Component.
- L58 _public function_ `SLATE_BEGIN_ARGS(SDMXPixelMappingOutputComponent)`
- L61 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FDMXPixelMappingToolkit>& InToolkit, TWeakObjectPtr<UDMXPixelMappingOutputComponent> InOutputComponent);`
- L67 _public function_ `virtual TSharedRef<SWidget> AsWidget() override`
- L68 _public prototype_ `virtual bool Equals(UDMXPixelMappingBaseComponent* Component) const override;`
- L71 _protected prototype_ `virtual FVector2D GetPosition() const override;`
- L75 _protected prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L80 _private prototype_ `TOptional<FSlateRenderTransform> GetRenderTransform() const;` — Returns the render transform for this widget
- L83 _private member_ `TSharedPtr<FDMXPixelMappingOutputComponentModel> Model;` — The model for this widget
- L86 _private member_ `TWeakPtr<FDMXPixelMappingToolkit> WeakToolkit;` — The toolkit that owns

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace DMX` (scope `UE`)

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Widgets/SDMXPixelMappingOutputComponentText.h` (Private)


#### class `SDMXPixelMappingOutputComponentText`  
`class SDMXPixelMappingOutputComponentText : public SCompoundWidget`  
_L14-50_
- inherits: `SCompoundWidget`
- desc: Draws the text in an output component widget
- L19 _public function_ `SLATE_BEGIN_ARGS(SDMXPixelMappingOutputComponentText)`
- L22 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FDMXPixelMappingToolkit>& InToolkit, TWeakObjectPtr<UDMXPixelMappingOutputComponent> OutputComponent);`
- L28 _public member_ `TSharedPtr<UE::DMX::FDMXPixelMappingOutputComponentModel> Model;` — The model for this widget
- L31 _public member_ `TWeakPtr<FDMXPixelMappingToolkit> WeakToolkit;` — The toolkit that owns
- L35 _protected prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L40 _private prototype_ `void OnPaintComponentName(const FPaintArgs& Args, const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FVector2f& Scale) const;` — Helper to paint the component name
- L43 _private prototype_ `void OnPaintCellID(const FPaintArgs& Args, const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FVector2f& Scale) const;` — Helper to paint the cell ID
- L46 _private prototype_ `void OnPaintPatchInfo(const FPaintArgs& Args, const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FVector2f& Scale) const;` — Helper to paint the patch info
- L49 _private prototype_ `uint8 GetFontSize() const;` — Returns the current font size

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace DMX` (scope `UE`)

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Widgets/SDMXPixelMappingPreviewViewport.h` (Private)


#### class `SDMXPixelMappingPreviewViewport`  
`class SDMXPixelMappingPreviewViewport : public SCompoundWidget`  
_L16-65_
- inherits: `SCompoundWidget`
- L21 _public function_ `SLATE_BEGIN_ARGS(SDMXPixelMappingPreviewViewport)`
- L30 _public prototype_ `void Construct(const FArguments& InArgs, TWeakPtr<FDMXPixelMappingToolkit> InToolkit);` — Constructs the widget. @param InArgs The construction arguments.
- L32 _public function_ `TSharedPtr<FSceneViewport> GetViewport() const`
- L34 _public function_ `TSharedPtr<SViewport> GetViewportWidget() const`
- L37 _public prototype_ `FOptionalSize GetWidthGraphSpace() const;` — Returns the texture width, in graph space
- L40 _public prototype_ `FOptionalSize GetHeightGraphSpace() const;` — Returns the texture height, in graph space
- L44 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L49 _private prototype_ `FMargin GetPaddingGraphSpace() const;` — Returns the padding of content, in graph space
- L52 _private prototype_ `UTexture* GetInputTexture() const;` — Returns the input texture currently in use
- L55 _private member_ `TSharedPtr<FDMXPixelMappingPreviewViewportClient> ViewportClient;` — Viewport client.
- L58 _private member_ `TSharedPtr<FSceneViewport> Viewport;` — Slate viewport for rendering and IO.
- L61 _private member_ `TSharedPtr<SViewport> ViewportWidget;` — Viewport widget.
- L64 _private member_ `TWeakPtr<FDMXPixelMappingToolkit> WeakToolkit;` — Weak pointer to the editor toolkit

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Widgets/SDMXPixelMappingRuler.h` (Private)


#### class `SDMXPixelMappingRuler`  
`class SDMXPixelMappingRuler : public SCompoundWidget`  
_L14-99_
- inherits: `SCompoundWidget`
- desc: Most of the logic copied from a private class Engine/Source/Editor/UMGEditor/Private/Designer/SRuler.h Add ruler for visual texture measurement in the editor
- L19 _public function_ `SLATE_BEGIN_ARGS(SDMXPixelMappingRuler) : _Orientation(Orient_Horizontal) , _OnMouseButtonDown()`
- L26 _public prototype_ `SLATE_ARGUMENT(EOrientation, Orientation) SLATE_EVENT(FPointerEventHandler, OnMouseButtonDown) SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L49 _public prototype_ `float DetermineOptimalSpacing(float InPixelsPerInput, uint32 MinTick, float MinTickSpacing) const;` — Determines the optimal spacing between tick marks in the slider for a given pixel density Increments until a minimum amount of slate units specified by MinTick is reached @param InPixelsPerInput	The density of pixels between each input @param MinTick			The minimum slate units per tick allowed @param MinTickSpacing	The minimum tick spacing in time units allowed @return the optimal spacing in time units
- L58 _public prototype_ `void SetRuling(FVector2D AbsoluteOrigin, float SlateToUnitScale);` — Sets the rules to use when rendering the ruler. @param AbsoluteOrigin The origin of the ruler in absolute window space. @param SlateToUnitScale The scaler applied to slate units to get the same number of units currently being displayed by the rule marks.
- L65 _public prototype_ `void SetCursor(TOptional<FVector2D> AbsoluteCursor);` — Sets the cursor position in window absolute space. @param AbsoluteCursor The position of the cursor in absolute window space.
- L69 _protected prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;` — SWidget interface
- L70 _protected prototype_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;`
- L71 _protected prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L72 _protected prototype_ `virtual FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L73 _protected prototype_ `virtual FReply OnMouseMove( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L74 _protected prototype_ `virtual FReply OnMouseWheel( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L82 _private prototype_ `int32 DrawTicks(FSlateWindowElementList& OutDrawElements, const FScrubRangeToScreen& RangeToScreen, FDrawTickArgs& InArgs) const;` — Draws the ticks on the track
- L86 _private member_ `EOrientation Orientation;` — The orientation of the ruler
- L89 _private member_ `FVector2D AbsoluteOrigin;` — The absolute origin of the document being measured.  The 0 on the ruler will start here.
- L92 _private member_ `TOptional<FVector2D> AbsoluteCursor;` — The absolute position of the cursor so that little lines can be drawn showing the cursors position on the ruler.
- L95 _private member_ `float SlateToUnitScale;` — The current conversion from Slate Pixel To Unit Size.
- L98 _private member_ `FPointerEventHandler MouseButtonDownHandler;` — The public event we expose when the mouse button is pressed onto the ruler.

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Widgets/SDMXPixelMappingSnapGridMenu.h` (Private)


#### class `UE::DMX::SDMXPixelMappingSnapGridMenu`  
`class SDMXPixelMappingSnapGridMenu : public SCompoundWidget`  
_L19-78_
- inherits: `SCompoundWidget`
- L23 _public function_ `SLATE_BEGIN_ARGS(SDMXPixelMappingSnapGridMenu)`
- L36 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FDMXPixelMappingToolkit>& InToolkit);` — Constructs this widget
- L40 _private prototype_ `TOptional<int32> GetColumns() const;` — Returns the number of columns for grid snapping as text
- L43 _private prototype_ `void OnColumnsEdited(int32 NewColumns);` — Called when the number of grid snapping columns was edited
- L46 _private prototype_ `TOptional<int32> GetRows() const;` — Returns the number of rows for grid snapping as text
- L49 _private prototype_ `void OnRowsEdited(int32 NewRows);` — Called when the number of grid snapping rows was edited
- L52 _private prototype_ `FLinearColor GetColor() const;` — Returns the current grid color
- L55 _private prototype_ `FReply OnColorBlockClicked(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — Called when the grid color block was clicked
- L58 _private prototype_ `void OnColorSelected(FLinearColor NewColor);` — Called when a color was selected in the color picker
- L61 _private prototype_ `void OnColorPickerCancelled(FLinearColor OriginalColor);` — Called when color picking was canceled
- L64 _private prototype_ `void OnColorPickerWindowClosed(const TSharedRef<SWindow>& Window);` — Called when the color picker window was closed
- L67 _private prototype_ `bool IsGridSnappingEnabled() const;` — Returns true if grid snapping is enabled
- L70 _private member_ `TSharedPtr<FScopedTransaction> ColorPickerTransaction;` — Transaction when selecting colors in its own menu
- L73 _private member_ `TWeakPtr<FDMXPixelMappingToolkit> WeakToolkit;` — The toolkit that owns this widget
- L76 _private member_ `FOnCheckStateChanged OnCheckStateChanged;` — Slate args
- L77 _private member_ `ECheckBoxState IsChecked;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace DMX` (scope `UE`)

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Widgets/SDMXPixelMappingSourceTextureViewport.h` (Private)


#### class `SDMXPixelMappingSourceTextureViewport`  
`class SDMXPixelMappingSourceTextureViewport : public SCompoundWidget`  
_L15-63_
- inherits: `SCompoundWidget`
- L19 _public function_ `SLATE_BEGIN_ARGS(SDMXPixelMappingSourceTextureViewport)`
- L26 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedPtr<FDMXPixelMappingToolkit>& InToolkit);` — Constructs this widget
- L29 _public function_ `TSharedPtr<FSceneViewport> GetViewport() const` — Returns the viewport of this widget
- L32 _public function_ `TSharedPtr<SViewport> GetViewportWidget() const` — Returns the viewport widget of this viewport
- L35 _public prototype_ `FOptionalSize GetWidthGraphSpace() const;` — Returns the texture width, in graph space
- L38 _public prototype_ `FOptionalSize GetHeightGraphSpace() const;` — Returns the texture height, in graph space
- L42 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L47 _private prototype_ `FMargin GetPaddingGraphSpace() const;` — Returns the padding of content, in graph space
- L50 _private prototype_ `UTexture* GetInputTexture() const;` — Returns the input texture currently in use
- L53 _private member_ `TWeakPtr<FDMXPixelMappingToolkit> WeakToolkit;` — Weak pointer to the editor toolkit
- L56 _private member_ `TSharedPtr<FDMXPixelMappingSourceTextureViewportClient> ViewportClient;` — viewport client.
- L59 _private member_ `TSharedPtr<FSceneViewport> Viewport;` — Slate viewport for rendering and IO.
- L62 _private member_ `TSharedPtr<SViewport> ViewportWidget;` — Viewport widget.

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Widgets/SDMXPixelMappingSurface.h` (Private)


#### class `SDMXPixelMappingSurface`  
`class SDMXPixelMappingSurface : public SCompoundWidget`  
_L18-162_
- inherits: `SCompoundWidget`
- desc: Most of the logic copied from a private class Engine/Source/Editor/UMGEditor/Private/Designer/SPaintSurface.h Base class for Preview and Designer Grid
- L23 _public function_ `SLATE_BEGIN_ARGS( SDMXPixelMappingSurface ) : _AllowContinousZoomInterpolation(false)`
- L28 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_ATTRIBUTE(bool, AllowContinousZoomInterpolation) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<FDMXPixelMappingToolkit>& InToolkit);` — Slot for this designers content (optional)
- L36 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface
- L37 _public prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L38 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L39 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L40 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L41 _public prototype_ `virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L42 _public prototype_ `virtual FReply OnTouchGesture(const FGeometry& MyGeometry, const FPointerEvent& GestureEvent) override;`
- L43 _public prototype_ `virtual FReply OnTouchEnded(const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent) override;`
- L44 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L45 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L49 _public prototype_ `FVector2D GetViewOffset() const;` — Returns the view offset
- L52 _public prototype_ `float GetZoomAmount() const;` — Gets the current zoom factor.
- L55 _public function_ `TSharedPtr<FDMXPixelMappingToolkit> GetToolkit()` — Returns the toolkit used with this surface
- L58 _public prototype_ `void ZoomToFit(bool bInstantZoom);` — Zooms to fit content
- L61 _protected prototype_ `virtual void OnPaintBackground(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId) const;`
- L63 _protected prototype_ `void PaintBackgroundAsLines(const FSlateBrush* BackgroundImage, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32& DrawLayerId) const;`
- L65 _protected prototype_ `void ChangeZoomLevel(int32 ZoomLevelDelta, const FVector2D& WidgetSpaceZoomOrigin, bool bOverrideZoomLimiting);`
- L67 _protected prototype_ `void PostChangedZoom();`
- L69 _protected prototype_ `bool ScrollToLocation(const FGeometry& MyGeometry, FVector2D DesiredCenterPosition, const float InDeltaTime);`
- L71 _protected prototype_ `bool ZoomToLocation(const FVector2D& CurrentSizeWithoutZoom, const FVector2D& DesiredSize, bool bDoneScrolling);`
- L73 _protected prototype_ `FText GetZoomText() const;`
- L74 _protected prototype_ `FSlateColor GetZoomTextColorAndOpacity() const;`
- L76 _protected prototype_ `FSlateRect ComputeSensibleBounds() const;`
- L78 _protected prototype_ `FVector2D GraphCoordToPanelCoord(const FVector2D& GraphSpaceCoordinate) const;`
- L79 _protected prototype_ `FVector2D PanelCoordToGraphCoord(const FVector2D& PanelSpaceCoordinate) const;`
- L82 _protected prototype_ `virtual FSlateRect ComputeAreaBounds() const;`
- L83 _protected prototype_ `virtual float GetGridScaleAmount() const;`
- L84 _protected prototype_ `virtual int32 GetGraphRulePeriod() const;`
- L85 _protected prototype_ `virtual int32 GetGridSize() const = 0;`
- L89 _protected member_ `FVector2D ViewOffset;` — The position within the graph at which the user is looking
- L92 _protected member_ `FVector2D GridOrigin;` — The position in the grid to begin drawing at.
- L95 _protected member_ `bool bDrawGridLines;` — Should we render the grid lines?
- L98 _protected member_ `int32 PreviousZoomLevel;` — Previous Zoom Level
- L101 _protected member_ `int32 ZoomLevel;` — How zoomed in/out we are. e.g. 0.25f results in quarter-sized nodes.
- L104 _protected member_ `bool bIsPanning = false;` — Are we panning the view at the moment?
- L107 _protected member_ `bool bIsZooming = false;` — Are we zooming the view with trackpad at the moment?
- L110 _protected member_ `TAttribute<bool> AllowContinousZoomInterpolation;` — Allow continuous zoom interpolation?
- L113 _protected member_ `FCurveSequence ZoomLevelGraphFade;` — Fade on zoom for graph
- L116 _protected member_ `FCurveSequence ZoomLevelFade;` — Curve that handles fading the 'Zoom +X' text
- L119 _protected member_ `TUniquePtr<FZoomLevelsContainer> ZoomLevels;` — The interface for mapping ZoomLevel values to actual node scaling values
- L121 _protected member_ `bool bAllowContinousZoomInterpolation;`
- L123 _protected member_ `bool bTeleportInsteadOfScrollingWhenZoomingToFit;`
- L125 _protected member_ `FVector2D ZoomTargetTopLeft;`
- L126 _protected member_ `FVector2D ZoomTargetBottomRight;`
- L127 _protected member_ `FVector2D ZoomToFitPadding;`
- L130 _protected member_ `float TotalMouseDelta;` — The Y component of mouse drag (used when zooming)
- L133 _protected member_ `FVector2D ZoomStartOffset;` — Offset in the panel the user started the LMB+RMB zoom from
- L136 _protected member_ `FVector2D ViewOffsetStart;`
- L139 _protected member_ `FVector2D MouseDownPositionAbsolute;`
- L142 _protected member_ `float TotalGestureMagnify;` — Cumulative magnify delta from trackpad gesture
- L145 _protected member_ `bool bRequireControlToOverZoom;` — Does the user need to press Control in order to over-zoom.
- L148 _protected member_ `bool bInitialZoomToFit = true;` — If true, zooms to fit as soon as a texture is loaded
- L151 _protected member_ `TWeakPtr<FDMXPixelMappingToolkit> WeakToolkit;` — Toolkit weak pointer
- L155 _private prototype_ `EActiveTimerReturnType HandleZoomToFit(double InCurrentTime, float InDeltaTime);` — Active timer that handles deferred zooming until the target zoom is reached
- L158 _private member_ `TWeakPtr<FActiveTimerHandle> ActiveTimerHandle;` — The handle to the active timer
- L161 _private member_ `bool bDeferredZoomToExtents;` — A flag noting if we have a pending zoom to extents operation to perform next tick.

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Widgets/SDMXPixelMappingTransformHandle.h` (Private)


#### enum `EDMXPixelMappingTransformDirection`  
`enum class EDMXPixelMappingTransformDirection : uint8`  
_L13-20_
- L15 _public enumerator_ `CenterRight`
- L16 _public enumerator_ `BottomRight`
- L17 _public enumerator_ `BottomCenter`
- L19 _public enumerator_ `MAX`

#### enum `EDMXPixelMappingTransformAction`  
`enum class EDMXPixelMappingTransformAction : uint8`  
_L22-27_
- L24 _public enumerator_ `None`
- L25 _public enumerator_ `Primary`
- L26 _public enumerator_ `Secondary`

#### class `SDMXPixelMappingTransformHandle`  
`class SDMXPixelMappingTransformHandle : public SCompoundWidget`  
_L34-92_
- inherits: `SCompoundWidget`
- desc: Most of the logic copied from a private class Engine/Source/Editor/UMGEditor/Private/Designer/STransformHandle.h This is a small dot widget for control the size of the selected widget
- L39 _public function_ `SLATE_BEGIN_ARGS(SDMXPixelMappingTransformHandle) : _Offset(FVector2D(0, 0))`
- L42 _public prototype_ `SLATE_ATTRIBUTE(FVector2D, Offset) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<SDMXPixelMappingDesignerView> InDesignerView, EDMXPixelMappingTransformDirection InTransformDirection, TAttribute<FVector2D> InOffset);`
- L48 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — SWidget interface
- L49 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L50 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L51 _public prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L54 _public function_ `EDMXPixelMappingTransformDirection GetTransformDirection() const`
- L55 _public function_ `FVector2D GetOffset() const`
- L58 _private prototype_ `EVisibility GetHandleVisibility() const;`
- L61 _private prototype_ `void Rotate(UDMXPixelMappingOutputComponent* OutputComponent, const FVector2D& CursorPosition, double WidgetScale);` — Rotate the component
- L64 _private prototype_ `void Resize(UDMXPixelMappingOutputComponent* OutputComponent, const FVector2D& CursorPosition, double WidgetScale);` — Resizes the component
- L67 _private prototype_ `FVector2D GetSnapSize(UDMXPixelMappingOutputComponent* OutputComponent, const FVector2D& RequestedSize) const;` — Utiltity that returns the snap size of an output component. Note, this snaps to pixels if grid snapping is disabled.
- L69 _private prototype_ `EDMXPixelMappingTransformAction ComputeActionAtLocation(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) const;`
- L71 _private prototype_ `FVector2D ComputeDragDirection(EDMXPixelMappingTransformDirection InTransformDirection) const;`
- L72 _private prototype_ `FVector2D ComputeOrigin(EDMXPixelMappingTransformDirection InTransformDirection) const;`
- L74 _private member_ `EDMXPixelMappingTransformDirection TransformDirection;`
- L75 _private member_ `EDMXPixelMappingTransformAction Action;`
- L77 _private member_ `FVector2D DragDirection = FVector2D::ZeroVector;`
- L78 _private member_ `FVector2D DragOrigin = FVector2D::ZeroVector;`
- L80 _private member_ `FVector2D MouseDownPosition = FVector2D::ZeroVector;`
- L81 _private member_ `FVector2D InitialSize = FVector2D::ZeroVector;`
- L82 _private member_ `double InitialRotation = 0.0;`
- L84 _private member_ `TSharedPtr<FScopedTransaction> ScopedTransaction;`
- L86 _private member_ `TWeakPtr<SDMXPixelMappingDesignerView> DesignerViewWeakPtr;`
- L88 _private member_ `TAttribute<FVector2D> Offset;`
- L91 _private member_ `FTimerHandle RequestApplyTransformHandle;` — Timer handle used when resize is requested

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingEditor/Private/Widgets/SDMXPixelMappingZoomPan.h` (Private)


#### class `SDMXPixelMappingZoomPan`  
`class SDMXPixelMappingZoomPan : public SCompoundWidget`  
_L13-46_
- inherits: `SCompoundWidget`
- desc: Most of the logic copied from a private class Engine/Source/Editor/UMGEditor/Private/Designer/SZoomPan.h Controll zoom for preview and designer
- L17 _public function_ `SLATE_BEGIN_ARGS(SDMXPixelMappingZoomPan)`
- L19 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_ATTRIBUTE(FVector2D, ViewOffset) SLATE_ATTRIBUTE(float, ZoomAmount) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Slot for this designers content (optional)
- L34 _public prototype_ `void SetContent( const TSharedRef< SWidget >& InContent );` — Sets the content for this border @param	InContent	The widget to use as content for the border
- L37 _protected prototype_ `void OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const override;`
- L39 _protected prototype_ `virtual float GetRelativeLayoutScale(int32 ChildIndex, float LayoutScaleMultiplier) const override;`
- L42 _protected member_ `TAttribute<FVector2D> ViewOffset;` — The position within the panel at which the user is looking
- L45 _protected member_ `TAttribute<float> ZoomAmount;` — How zoomed in/out we are. e.g. 0.25f results in quarter-sized widgets.
