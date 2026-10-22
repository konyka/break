# Plugins / TextureGraphEditor

- module root: `Plugins/TextureGraph/Source/TextureGraphEditor`
- headers: 58; symbols: 1486
- symbol kinds: class=64, delegate=38, enum=5, enumerator=28, externvar=2, function=152, macro=8, member=413, namespace=3, prototype=745, struct=9, typedef=5, variable=14
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: ApplicationCore, AssetDefinition, CoreUObject, EditorWidgets, Engine, GraphEditor, ImageWidgets, InputCore, MessageLog, Slate, SlateCore
- PublicDependencyModuleNames: AdvancedPreviewScene, AssetTools, ContentBrowser, ContentBrowserData, Core, EditorFramework, Engine, KismetWidgets, Projects, PropertyEditor, RHI, RenderCore, Renderer, TextureGraph, TextureGraphEngine, ToolMenus, ToolWidgets, UnrealEd, WorkspaceMenuStructure

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/AssetDefinition_TextureGraph.h` (Private)


#### class `UAssetDefinition_TextureGraph`  
`class UAssetDefinition_TextureGraph : public UAssetDefinitionDefault`  
_L11-29_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L26 _public prototype_ `virtual FAssetOpenSupport GetAssetOpenSupport(const FAssetOpenSupportArgs& OpenSupportArgs) const override;`
- L27 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/AssetDefinition_TextureGraphInstance.h` (Private)


#### class `UAssetDefinition_TextureGraphInstance`  
`class UAssetDefinition_TextureGraphInstance : public UAssetDefinitionDefault`  
_L11-29_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L26 _public prototype_ `virtual FAssetOpenSupport GetAssetOpenSupport(const FAssetOpenSupportArgs& OpenSupportArgs) const override;`
- L27 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/Customizations/STG_LevelsSettings.h` (Private)


#### class `STG_LevelsSettings`  
`class STG_LevelsSettings : public SCompoundWidget`  
_L12-38_
- inherits: `SCompoundWidget`
- L16 _public function_ `SLATE_BEGIN_ARGS(STG_LevelsSettings) : _Levels(), _OnValueChanged()`
- L20 _public prototype_ `SLATE_ARGUMENT(FTG_LevelsSettings, Levels) SLATE_ARGUMENT(FTG_OnLevelsSettingsValueChanged, OnValueChanged) SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L27 _public prototype_ `void OnLowChanged(float InValue);`
- L28 _public prototype_ `void OnMidChanged(float InValue);`
- L29 _public prototype_ `void OnHighChanged(float InValue);`
- L30 _public prototype_ `void UpdateLevelsWidget();`
- L32 _protected member_ `TSharedPtr<SSlider> LowLevelsSlider;`
- L33 _protected member_ `TSharedPtr<SSlider> MidLevelsSlider;`
- L34 _protected member_ `TSharedPtr<SSlider> HighLevelsSlider;`
- L35 _protected member_ `FTG_LevelsSettings Levels;`
- L37 _protected member_ `FTG_OnLevelsSettingsValueChanged OnValueChanged;`

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_DELEGATE_OneParam(FTG_OnLevelsSettingsValueChanged, const FTG_LevelsSettings&);` — Notification for float value change
- L10 _prototype_ `DECLARE_DELEGATE_OneParam(FTG_OnLevelsSettingsValueChanged, const FTG_LevelsSettings&);` — Notification for float value change

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/Customizations/STG_TextureHistogram.h` (Private)


#### class `STG_TextureHistogram`  
`class STG_TextureHistogram : public SCompoundWidget`  
_L13-35_
- inherits: `SCompoundWidget`
- desc: This widget represents the Histogram of the source FTG_Texture assigned along with the UTG_Script where it belongs
- L16 _public function_ `SLATE_BEGIN_ARGS(STG_TextureHistogram): _HistogramColor(TextureHistogramUtils::LinearWhite), _BackgroundColor(FLinearColor(0.08f, 0.08f, 0.08f, 1.f)), _Height(20.0)`
- L21 _public prototype_ `SLATE_ARGUMENT(FLinearColor, HistogramColor) SLATE_ARGUMENT(FLinearColor, BackgroundColor) SLATE_ARGUMENT(float, Height) SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L29 _public prototype_ `void SetTexture(FTG_Texture& Source, UTextureGraph* InTextureGraph);`
- L31 _public member_ `static const float PreferredWidth;`
- L33 _protected member_ `TSharedPtr<STG_HistogramBlob> HistogramBars;`
- L34 _protected member_ `TiledBlobPtr HistogramBlob;`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/Customizations/TG_LevelsSettingsCustomization.h` (Private)


#### class `FTG_LevelsSettingsCustomization`  
`class FTG_LevelsSettingsCustomization : public IPropertyTypeCustomization`  
_L18-74_
- inherits: `IPropertyTypeCustomization`
- L20 _private member_ `TSharedPtr<IPropertyHandle> LevelsHandle;`
- L23 _public function_ `static TSharedRef<IPropertyTypeCustomization> Create()`
- L28 _public function_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override`
- L33 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override`
- L65 _public function_ `void OnValueChanged(const FTG_LevelsSettings& NewValue, TWeakPtr<IPropertyHandle> HandleWeakPtr)`

#### Free symbols / members of external scopes

- L16 _macro_ `#define LOCTEXT_NAMESPACE "FTextureGraphEditorModule"`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/Customizations/TG_MaterialCustomization.h` (Private)


#### class `FTG_MaterialCustomization`  
`class FTG_MaterialCustomization : public IPropertyTypeCustomization`  
_L14-42_
- inherits: `IPropertyTypeCustomization`
- L17 _public function_ `static TSharedRef<IPropertyTypeCustomization> Create()`
- L22 _public function_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override`
- L26 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/Customizations/TG_MaterialMappingInfoCustomization.h` (Private)


#### class `FTG_MaterialMappingInfoCustomization`  
`class FTG_MaterialMappingInfoCustomization : public IPropertyTypeCustomization`  
_L30-120_
- inherits: `IPropertyTypeCustomization`
- L34 _private member_ `UMixSettings* MixSettings;`
- L36 _private member_ `TSharedPtr<IPropertyHandle> MaterialInputPropertyHandle;`
- L37 _private member_ `TSharedPtr<IPropertyHandle> TargetPropertyHandle;`
- L40 _public function_ `static TSharedRef<IPropertyTypeCustomization> Create()`
- L45 _public function_ `void GenerateMaterialInputsArray(TArray< TSharedPtr<FString> >& OutComboBoxStrings, TArray<TSharedPtr<SToolTip>>& OutToolTips, TArray<bool>& OutRestrictedItems, bool bAllowClear, FName FilterStructName)`
- L65 _public function_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override`
- L70 _public function_ `FString OnGetTypeValueString()`
- L78 _public function_ `void OnTargetSelected(const FString& UpdatedTargetValue)`
- L83 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override`

#### Free symbols / members of external scopes

- L28 _macro_ `#define LOCTEXT_NAMESPACE "FTextureGraphEditorModule"`
- L56 _function_ `` (scope `FTG_MaterialMappingInfoCustomization::GenerateMaterialInputsArray`)

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/Customizations/TG_OutputSettingsCustomization.h` (Private)


#### class `FTG_OutputSettingsCustomization`  
`class FTG_OutputSettingsCustomization : public IPropertyTypeCustomization`  
_L34-215_
- inherits: `IPropertyTypeCustomization`
- L36 _private member_ `TSharedPtr<SVerticalBox> PropertyLayout;`
- L37 _private member_ `TSharedPtr<IPropertyHandle> PathPropertyHandle;`
- L38 _private member_ `FString DefaultPath;`
- L41 _public function_ `static TSharedRef<IPropertyTypeCustomization> Create()`
- L46 _public function_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override`
- L79 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override`
- L178 _public function_ `FReply OnBrowseClick()`
- L186 _public function_ `static void BrowseFolderPath(const FString& DefaultFolder, const FString& NewFolderName, FString& OutPackagePath)`
- L209 _public function_ `static FString GetCurrentFolderInContentBrowser()`

#### class `FTG_OutputExpressionInfoCustomization`  
`class FTG_OutputExpressionInfoCustomization : public IPropertyTypeCustomization`  
_L218-273_
- inherits: `IPropertyTypeCustomization`
- L221 _public function_ `static TSharedRef<IPropertyTypeCustomization> Create()`
- L226 _public function_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override`
- L231 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override`

#### Free symbols / members of external scopes

- L32 _macro_ `#define LOCTEXT_NAMESPACE "OutputSettingsCustomization"`
- L264 _function_ `` (scope `FTG_OutputExpressionInfoCustomization::CustomizeChildren`)

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/Customizations/TG_ParameterCustomization.h` (Private)


#### class `FTG_ParameterInfoCustomization`  
`class FTG_ParameterInfoCustomization : public IPropertyTypeCustomization`  
_L26-96_
- inherits: `IPropertyTypeCustomization`
- L29 _public function_ `static TSharedRef<IPropertyTypeCustomization> Create()`
- L34 _public function_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override`
- L39 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/Customizations/TG_ScalarCustomization.h` (Private)


#### class `FTG_ScalarTypeIdentifier`  
`class FTG_ScalarTypeIdentifier : public IPropertyTypeIdentifier`  
_L18-25_
- inherits: `IPropertyTypeIdentifier`
- L21 _public function_ `virtual bool IsPropertyTypeCustomized(const IPropertyHandle& PropertyHandle) const override`

#### class `FTG_ScalarCustomization`  
`class FTG_ScalarCustomization : public IPropertyTypeCustomization`  
_L27-155_
- inherits: `IPropertyTypeCustomization`
- L30 _private member_ `TSharedPtr<IPropertyHandle> ScalarHandle;` — Edited Property
- L33 _private member_ `bool bIsUsingSlider = false;` — True if the slider is being used to change the value of the property
- L36 _public function_ `static TSharedRef<IPropertyTypeCustomization> Create()`
- L41 _public function_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override`
- L93 _public function_ `float OnGetValue() const`
- L106 _public function_ `void OnValueChanged(float NewValue)`
- L129 _public function_ `void OnBeginSliderMovement()`
- L138 _public function_ `void OnEndSliderMovement()`
- L152 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override`

#### Free symbols / members of external scopes

- L16 _macro_ `#define LOCTEXT_NAMESPACE "FTextureGraphEditorModule"`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/Customizations/TG_TextureCustomization.h` (Private)


#### class `FTG_TextureCustomization`  
`class FTG_TextureCustomization : public IPropertyTypeCustomization`  
_L17-90_
- inherits: `IPropertyTypeCustomization`
- L20 _public function_ `static TSharedRef<IPropertyTypeCustomization> Create()`
- L25 _public function_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override`
- L73 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/Customizations/TG_VariantCustomization.h` (Private)


#### class `FTG_VariantCustomization`  
`class FTG_VariantCustomization : public IPropertyTypeCustomization`  
_L16-97_
- inherits: `IPropertyTypeCustomization`
- L19 _public function_ `static TSharedRef<IPropertyTypeCustomization> Create()`
- L24 _public function_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override`
- L28 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override`

#### Free symbols / members of external scopes

- L62 _function_ `` (scope `FTG_VariantCustomization::CustomizeChildren`)

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/Customizations/TG_ViewportSettingsCustomization.h` (Private)


#### class `FTG_ViewportSettingsCustomization`  
`class FTG_ViewportSettingsCustomization : public IPropertyTypeCustomization`  
_L19-66_
- inherits: `IPropertyTypeCustomization`
- L23 _private member_ `UMixSettings* MixSettings;`
- L25 _private member_ `TSharedPtr<IPropertyHandle> MaterialPropertyHandle;`
- L26 _private member_ `TSharedPtr<IPropertyHandle> MaterialMappingInfosPropertyHandle;`
- L29 _public function_ `static TSharedRef<IPropertyTypeCustomization> Create()`
- L34 _public function_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override`
- L40 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override`

#### Free symbols / members of external scopes

- L17 _macro_ `#define LOCTEXT_NAMESPACE "FTextureGraphEditorModule"`
- L48 _function_ `` (scope `FTG_ViewportSettingsCustomization::CustomizeChildren`)

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/EdGraph/STG_EditorGraphNode.h` (Private)


#### class `STG_EditorGraphNode`  
`class STG_EditorGraphNode : public SGraphNode`  
_L21-108_
- inherits: `SGraphNode`
- L24 _public function_ `SLATE_BEGIN_ARGS(STG_EditorGraphNode)`
- L27 _public prototype_ `virtual ~STG_EditorGraphNode() override;`
- L29 _public prototype_ `void Construct(const FArguments& InArgs, UTG_EdGraphNode* InNode);`
- L30 _public prototype_ `virtual void UpdateGraphNode() override;`
- L37 _public member_ `TSharedPtr<STextBlock> RightLabel;` — virtual const FSlateBrush* GetNodeBodyBrush() const override; virtual void RequestRenameOnSpawn() override {   Empty to avoid the default behavior to rename on node spawn   } virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;
- L39 _public prototype_ `virtual void CreatePinWidgets() override;`
- L40 _public prototype_ `virtual TSharedRef<SWidget> CreateTitleRightWidget() override;`
- L42 _public prototype_ `virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;` — virtual TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* Pin) const;
- L44 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L45 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L46 _public prototype_ `void UpdateInputPinLayout(const TSharedRef<SGraphPin>& PinToAdd);`
- L48 _public prototype_ `TSharedRef<SWidget> CreatePreviewWidget(UTG_Pin* Pin, const TSharedPtr<SWidget>& ThumbWidget);` — Thumbnail Widget
- L50 _public prototype_ `void SetPinIcon(const TSharedRef<SGraphPin> Shared);`
- L52 _public prototype_ `virtual const FSlateBrush* GetShadowBrush(bool bSelected) const override;`
- L60 _protected member_ `TSharedPtr<SVerticalBox> NotConnectableInputPinBox;` — The area where non connectable input pins reside
- L62 _protected member_ `TSharedPtr<SVerticalBox> ParametersBox;` — The area where Param pins and settings pins reside
- L64 _protected member_ `TSharedPtr<SVerticalBox> LowDetailParametersBox;` — The area where Param pins and settings pins reside for Low detail
- L66 _protected member_ `TSharedPtr<SVerticalBox> NotConnectableParametersBox;` — The area where non connectable Param pins and settings pins reside
- L68 _protected member_ `TSharedPtr<SVerticalBox> NodeSettingsBox;` — The area where node specific settings pins reside alyaws show in advance view
- L69 _protected prototype_ `int GetContentAreaBorderThickness();`
- L71 _protected prototype_ `virtual void CreateNodeSettingsLayout();`
- L72 _protected prototype_ `virtual TSharedRef<SWidget> CreateNodeSettings();`
- L73 _protected prototype_ `virtual TSharedRef<SWidget> CreateNodeContentArea() override;`
- L74 _protected prototype_ `virtual EVisibility ShowParameters() const;`
- L75 _protected prototype_ `virtual EVisibility ShowOverrideSettings() const;`
- L76 _protected prototype_ `void OnNodeReconstruct();`
- L77 _protected prototype_ `void OnNodePostEvaluate(const FTG_EvaluationContext* InContext);`
- L78 _protected prototype_ `void OnPinSelectionChanged(UEdGraphPin* Pin);`
- L80 _protected prototype_ `FSlateColor GetNodeTitleColor() const;`
- L81 _protected prototype_ `const FSlateBrush* GetNodeBodyBrush() const;`
- L82 _protected prototype_ `TSharedRef<SWidget> CreateTitleDetailsWidget();`
- L83 _protected prototype_ `virtual EVisibility IsTitleDetailVisible() const;`
- L84 _protected prototype_ `virtual bool UseLowDetailNodeTitles() const;`
- L85 _protected prototype_ `virtual TSharedRef<SWidget> CreateTitleWidget(TSharedPtr<SNodeTitle> NodeTitle) override;`
- L88 _private member_ `UTG_EdGraphNode* TGEditorGraphNode = nullptr;`
- L89 _private member_ `FDelegateHandle OnUpdateThumbHandle;`
- L90 _private member_ `FDelegateHandle OnPostEvaluateHandle;`
- L91 _private member_ `FDelegateHandle OnNodeChangedHandle;`
- L92 _private member_ `FDelegateHandle OnPinSelectionChangedHandle;`
- L93 _private member_ `FSlateBrush BodyBrush;`
- L94 _private member_ `FSlateBrush HeaderBrush;`
- L95 _private member_ `TSharedPtr<SBox> PreviewWidgetBox;`
- L96 _private member_ `TMap<FTG_Id, TSharedPtr<STG_NodeThumbnail>> PinThumbWidgetMap;`
- L97 _private prototype_ `FLinearColor GetPinThumbSelectionColor();`
- L98 _private prototype_ `FLinearColor GetPinThumbDeselectionColor();`
- L99 _private prototype_ `TSharedPtr<STG_NodeThumbnail> FindOrCreateThumbWidget(FTG_Id PinId);`
- L100 _private prototype_ `void ApplyThumbToWidget();`
- L101 _private prototype_ `void OnUpdateThumbnail(std::shared_ptr<JobBatch> JobBatch);`
- L102 _private prototype_ `UTexture* GetTextureFromBuffer(DeviceBufferPtr Buffer);`
- L103 _private prototype_ `FReply OnOutputIconClick(const FGeometry& SenderGeometry, const FPointerEvent& MouseEvent);`
- L104 _private prototype_ `TArray<FString> GetTitleDetailTextLines() const;`
- L105 _private prototype_ `FText GetLeftTitleText() const;`
- L106 _private prototype_ `FText GetRightTitleText() const;`
- L107 _private prototype_ `bool UseLowDetailParameters() const;`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/EdGraph/STG_NodeThumbnail.h` (Private)


#### class `STG_NodeThumbnail`  
`class STG_NodeThumbnail : public SCompoundWidget, public FGCObject`  
_L13-41_
- inherits: `SCompoundWidget,FGCObject`
- L16 _public function_ `SLATE_BEGIN_ARGS(STG_NodeThumbnail) :_Blob(nullptr) ,_BrushName("NodeThumb")`
- L21 _public prototype_ `SLATE_ARGUMENT(TiledBlobPtr , Blob) SLATE_ARGUMENT(FName , BrushName) SLATE_END_ARGS() virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L26 _public prototype_ `virtual FString GetReferencerName() const override;`
- L29 _public prototype_ `void Construct(const FArguments& InArgs);` — Constructs this widget with InArgs
- L31 _public prototype_ `void UpdateBlob(TiledBlobPtr InBlob);`
- L32 _public prototype_ `virtual void UpdateParams(TiledBlobPtr InBlob);`
- L33 _public prototype_ `virtual UMaterial* GetMaterial();`
- L34 _public prototype_ `UTexture* GetTextureFromBlob(TiledBlobPtr InBlob);`
- L37 _private member_ `FVector2D Position;`
- L38 _private member_ `FName BrushName;`
- L39 _private member_ `TSharedPtr<FSlateBrush> Brush;`
- L40 _private member_ `TObjectPtr<UMaterialInstanceDynamic> BrushMaterial = nullptr;`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/EdGraph/TG_EdGraphSchema.h` (Private)


#### class `UTG_EdGraphSchema`  
`class UTG_EdGraphSchema : public UEdGraphSchema`  
_L16-101_
- reflection: `UCLASS()`
- inherits: `UEdGraphSchema`
- L21 _public member_ `static const FLinearColor ImagePinColor;`
- L22 _public member_ `static const FLinearColor ScalarPinColor;`
- L23 _public member_ `static const FLinearColor VectorPinColor;`
- L24 _public member_ `static const FLinearColor ActivePinColor;`
- L25 _public member_ `static const FLinearColor InactivePinColor;`
- L28 _public member_ `static const FLinearColor InputNodesColor;` — Node title colors
- L29 _public member_ `static const FLinearColor FunctionNodesColor;`
- L30 _public member_ `static const FLinearColor MathsNodesColor;`
- L31 _public member_ `static const FLinearColor ProceduralNodesColor;`
- L32 _public member_ `static const FLinearColor OperatorNodesColor;`
- L33 _public member_ `static const FLinearColor OutputNodesColor;`
- L34 _public member_ `static const FLinearColor FilterNodesColor;`
- L35 _public member_ `static const FLinearColor ChannelNodesColor;`
- L36 _public member_ `static const FLinearColor CustomNodesColor;`
- L37 _public member_ `static const FLinearColor DevOnlyNodesColor;`
- L38 _public member_ `static const FLinearColor UtilitiesNodesColor;`
- L39 _public member_ `static const FLinearColor TGNodeColor;`
- L40 _public member_ `static const FLinearColor NodeBodyColor;`
- L41 _public member_ `static const FLinearColor NodeBodyColorOutline;`
- L43 _public member_ `static const FName PC_Boolean;`
- L44 _public member_ `static const FName PC_Byte;`
- L45 _public member_ `static const FName PC_Class;` — SubCategoryObject is the MetaClass of the Class passed thru this pin, or SubCategory can be 'self'. The DefaultValue string should always be empty, use DefaultObject.
- L46 _public member_ `static const FName PC_Int;`
- L47 _public member_ `static const FName PC_Int64;`
- L48 _public member_ `static const FName PC_Float;`
- L49 _public member_ `static const FName PC_Double;`
- L50 _public member_ `static const FName PC_Object;` — SubCategoryObject is the Class of the object passed thru this pin, or SubCategory can be 'self'. The DefaultValue string should always be empty, use DefaultObject.
- L51 _public member_ `static const FName PC_Interface;` — SubCategoryObject is the Class of the object passed thru this pin.
- L52 _public member_ `static const FName PC_String;`
- L53 _public member_ `static const FName PC_Text;`
- L54 _public member_ `static const FName PC_Struct;` — SubCategoryObject is the ScriptStruct of the struct passed thru this pin, 'self' is not a valid SubCategory. DefaultObject should always be empty, the DefaultValue string may be used for supported structs.
- L55 _public member_ `static const FName PC_Array;`
- L56 _public member_ `static const FName PC_Enum;` — SubCategoryObject is the UEnum object passed thru this pin
- L58 _public member_ `static const float NodeOutlineColorMultiplier;`
- L61 _public prototype_ `virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;`
- L63 _public prototype_ `virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;`
- L64 _public prototype_ `virtual bool TryCreateConnection(UEdGraphPin* A, UEdGraphPin* B) const override;`
- L66 _public prototype_ `virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;`
- L67 _public prototype_ `virtual FLinearColor GetSecondaryPinTypeColor(const FEdGraphPinType& PinType) const override;`
- L69 _public prototype_ `virtual void BreakNodeLinks(UEdGraphNode& TargetNode) const override;`
- L70 _public prototype_ `virtual void BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotifcation) const override;`
- L71 _public prototype_ `virtual void BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const override;`
- L73 _public prototype_ `virtual void DroppedAssetsOnGraph(const TArray<struct FAssetData>& Assets, const FVector2f& GraphPosition, UEdGraph* Graph) const override;`
- L74 _public prototype_ `virtual void DroppedAssetsOnNode(const TArray<struct FAssetData>& Assets, const FVector2f& GraphPosition, UEdGraphNode* Node) const override;`
- L75 _public prototype_ `virtual void GetAssetsGraphHoverMessage(const TArray<FAssetData>& Assets, const UEdGraph* HoverGraph, FString& OutTooltipText, bool& OutOkIcon) const override;`
- L76 _public prototype_ `virtual void GetAssetsNodeHoverMessage(const TArray<struct FAssetData>& Assets, const UEdGraphNode* HoverNode, FString& OutTooltipText, bool& OutOkIcon) const override;`
- L77 _public prototype_ `virtual void TrySetDefaultValue(UEdGraphPin& Pin, const FString& NewDefaultValue, bool bMarkAsModified = true) const override;`
- L78 _public prototype_ `virtual void TrySetDefaultObject(UEdGraphPin& Pin, UObject* NewDefaultObject, bool bMarkAsModified = true) const;`
- L81 _public prototype_ `UTG_Pin* GetTGPinFromEdPin(const UEdGraphPin* InPin) const;`
- L83 _public prototype_ `void GetPaletteActions(FGraphActionMenuBuilder& ActionMenuBuilder, const FString& CategoryName) const;`
- L84 _public prototype_ `static FLinearColor GetCategoryColor(FName Category);`
- L87 _private prototype_ `void GetTG_ExpressionsActions(FGraphActionMenuBuilder& ActionMenuBuilder) const;`
- L88 _private prototype_ `void GetCommentAction(FGraphActionMenuBuilder& ActionMenuBuilder, const UEdGraph* CurrentGraph) const;`
- L91 _private prototype_ `UTG_Node* GetTGNodeFromEdPin(const UEdGraphPin* InPin) const;` — From a Pin to its corresponding UTG_Node
- L95 _private prototype_ `bool ConnectionCausesLoop(const UEdGraphPin* FromPin, const UEdGraphPin* ToPin) const;` — Check whether connecting these pins would cause a loop
- L98 _private prototype_ `bool ArePinsCompatible_Internal(const UEdGraphPin* InA, const UEdGraphPin* InB) const;` — Internal check that 2 pins are compatible for connection
- L100 _private prototype_ `static TSharedPtr<IAssetReferenceFilter> MakeAssetReferenceFilter(const UEdGraph* Graph);`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/EdGraph/TG_EdGraphSchemaActions.h` (Private)


#### struct `FTG_EdGraphSchemaAction_NewNode`  
`struct FTG_EdGraphSchemaAction_NewNode : public FEdGraphSchemaAction`  
_L16-34_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- L25 _public member_ `TSubclassOf<UTG_Expression> TG_ExpressionClass;` — `UPROPERTY()`
- L29 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`
- L32 _public prototype_ `static UEdGraphNode* CreateExpressionNode(UEdGraph* ParentGraph, const UClass* ExpressionClass, UEdGraphPin* FromPin, const UE::Slate::FDeprecateVector2DParameter& Location, bool bSelectNewNode = true);`
- L33 _public prototype_ `static UEdGraphNode* CreateExpressionNode(UEdGraph* ParentGraph, UTG_Expression* Expression, UEdGraphPin* FromPin, const UE::Slate::FDeprecateVector2DParameter& Location, bool bSelectNewNode = true);`

#### struct `FTG_EdGraphSchemaAction_NewComment`  
`struct FTG_EdGraphSchemaAction_NewComment : public FEdGraphSchemaAction`  
_L38-57_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Action to add a 'comment' node to the graph
- L46 _public function_ `static FName StaticGetTypeId()` — Simple type info
- L53 _public function_ `virtual FName GetTypeId() const override` — FEdGraphSchemaAction interface
- L55 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/EdGraph/TG_EditorErrorReporter.h` (Private)


#### class `FTG_EditorErrorReporter`  
`class FTG_EditorErrorReporter: public FTextureGraphErrorReporter`  
_L8-32_
- inherits: `FTextureGraphErrorReporter`
- L11 _public function_ `FTG_EditorErrorReporter(FTG_Editor* InEditor) : FTextureGraphErrorReporter() , Editor(InEditor)`
- L16 _public prototype_ `virtual ~FTG_EditorErrorReporter() = default;`
- L18 _public prototype_ `virtual FTextureGraphErrorReport ReportLog(int32 ErrorId, const FString& ErrorMsg, UObject* ReferenceObj = nullptr) override;`
- L20 _public prototype_ `virtual FTextureGraphErrorReport ReportWarning(int32 ErrorId, const FString& ErrorMsg, UObject* ReferenceObj = nullptr) override;`
- L22 _public prototype_ `virtual FTextureGraphErrorReport ReportError(int32 ErrorId, const FString& ErrorMsg, UObject* ReferenceObj = nullptr) override;`
- L24 _public prototype_ `virtual void Clear() override;`
- L27 _private prototype_ `static EAppMsgCategory GetMsgAppCategoryFromEMessageSeverity(EMessageSeverity::Type ErrorType);`
- L29 _private prototype_ `FTextureGraphErrorReport Report(int32 ErrorId, const FString& ErrorMsg, UObject* ReferenceObj, EMessageSeverity::Type ErrorType);`
- L31 _private member_ `FTG_Editor* Editor;`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/Pins/STG_GraphMaterialIdMaskInfos.h` (Private)


#### class `STextureGraphMaterialIdMaskInfos`  
`class STextureGraphMaterialIdMaskInfos : public SGraphPin`  
_L21-184_
- inherits: `SGraphPin`
- L24 _public function_ `SLATE_BEGIN_ARGS(STextureGraphMaterialIdMaskInfos)`
- L25 _public function_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)`
- L36 _protected member_ `FString SelectedIdsText;`
- L37 _protected member_ `TArray<int32> SelectedIds;`
- L39 _protected function_ `FText HandleOutputText() const`
- L44 _protected function_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override` — SGraphPin interface
- L62 _protected function_ `TSharedRef<SWidget> GenerateMaterialIdMaskInfos()`
- L115 _protected function_ `void HandleSelectionUpdate()`
- L153 _protected function_ `void HandleOnMaterialIdClicked(const int32 Id)`
- L165 _protected function_ `TArray<FMaterialIDMaskInfo> GetMaterialIdMaskInfos() const`
- L172 _protected function_ `UTG_Expression_MaterialID* GetMaterialIDExpression() const`
- L178 _protected function_ `FString GetColorName(const FMaterialIDMaskInfo& MaskInfo) const`

#### Free symbols / members of external scopes

- L103 _function_ `FExecuteAction::CreateSP(this, &STextureGraphMaterialIdMaskInfos::HandleOnMaterialIdClicked, Info.MaterialIdReferenceId), FCanExecuteAction(), FIsActionChecked::CreateLambda([this, Info]() {return SelectedIds.Contains(Info.MaterialIdReferenceId); }) ), MenuOverlayBox, NAME_None, FText::Format(NSLOCTEXT("STG_MaterialIdMaskInfo", "MaterialMaskId", "{0}"), FText::FromString(GetColorName(Info))), EUserInterfaceActionType::Check );` (scope `STextureGraphMaterialIdMaskInfos::GenerateMaterialIdMaskInfos`)

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/Pins/STG_GraphPinMaterial.h` (Private)


#### class `STG_GraphPinMaterial`  
`class STG_GraphPinMaterial : public SGraphPin`  
_L17-32_
- inherits: `SGraphPin`
- L20 _public function_ `SLATE_BEGIN_ARGS(STG_GraphPinMaterial)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L26 _protected prototype_ `FString GetCurrentAssetPath() const;`
- L27 _protected prototype_ `void OnAssetSelected(const FAssetData& AssetData);`
- L30 _protected prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/Pins/STG_GraphPinOutputSettings.h` (Private)


#### class `STG_GraphPinOutputSettings`  
`class STG_GraphPinOutputSettings : public SGraphPin`  
_L10-46_
- inherits: `SGraphPin`
- L13 _public function_ `SLATE_BEGIN_ARGS(STG_GraphPinOutputSettings)`
- L14 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L17 _public prototype_ `FProperty* GetPinProperty() const;`
- L18 _public prototype_ `bool ShowChildProperties() const;`
- L19 _public prototype_ `bool CollapsibleChildProperties() const;`
- L20 _public prototype_ `EVisibility ShowLabel() const;`
- L22 _public prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L23 _public prototype_ `virtual TSharedRef<SWidget> GetLabelWidget(const FName& InLabelStyle) override;`
- L28 _private prototype_ `void ParseDefaultValueData();` — Parses the Data from the pin to fill in the names of the array.
- L30 _private function_ `bool GetDefaultValueIsEnabled() const`
- L35 _private prototype_ `const FSlateBrush* GetAdvancedViewArrow() const;`
- L36 _private prototype_ `void OnAdvancedViewChanged(const ECheckBoxState NewCheckedState);`
- L37 _private prototype_ `ECheckBoxState IsAdvancedViewChecked() const;`
- L38 _private prototype_ `EVisibility IsUIEnabled() const;`
- L40 _private prototype_ `FTG_OutputSettings GetOutputSettings() const;`
- L41 _private prototype_ `void OnOutputSettingsChanged(const FTG_OutputSettings& NewOutputSettings);`
- L44 _private member_ `FTG_OutputSettings OutputSettings;` — Parse OutputSettings used for editing.
- L45 _private member_ `bool bIsUIHidden = true;`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/Pins/STG_GraphPinOutputSettingsWidget.h` (Private)


#### class `STG_GraphPinOutputSettingsWidget`  
`class STG_GraphPinOutputSettingsWidget : public SCompoundWidget, public FEditorUndoClient`  
_L19-147_
- inherits: `SCompoundWidget,FEditorUndoClient`
- desc: Widget for editing OutputSettings.
- L24 _private prototype_ `DECLARE_DELEGATE_RetVal(FText, FGetTextDelegate);`
- L25 _private prototype_ `DECLARE_DELEGATE_TwoParams(FTextCommitted, const FText&, ETextCommit::Type);`
- L26 _private prototype_ `DECLARE_DELEGATE_RetVal(TSharedRef<SWidget>, FGenerateEnumMenu);`
- L30 _public function_ `DECLARE_DELEGATE_OneParam(FOnOutputSettingsChanged, const FTG_OutputSettings& ) SLATE_BEGIN_ARGS(STG_GraphPinOutputSettingsWidget) : _DescriptionMaxWidth(250.0f) , _PropertyHandle(nullptr)`
- L39 _public prototype_ `SLATE_ARGUMENT(float, DescriptionMaxWidth) SLATE_ATTRIBUTE(FTG_OutputSettings, OutputSettings) SLATE_ARGUMENT(TSharedPtr<IPropertyHandle>, PropertyHandle) SLATE_EVENT(FOnOutputSettingsChanged, OnOutputSettingsChanged) SLATE_END_ARGS();` — Maximum with of the query description field.
- L50 _public prototype_ `STG_GraphPinOutputSettingsWidget();`
- L53 _public prototype_ `void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L54 _public prototype_ `TSharedRef<SWidget> AddEditBoxWithBrowseButton(FText Label, FGetTextDelegate GetText, FTextCommitted OnTextCommitted);`
- L55 _public prototype_ `TSharedRef<SWidget> AddEditBox(FText Label, FGetTextDelegate GetText, FTextCommitted OnTextCommitted);`
- L56 _public prototype_ `TSharedRef<SWidget> AddEnumComobox(FText Label, FGetTextDelegate GetText, FGenerateEnumMenu OnGenerateEnumMenu);`
- L57 _public prototype_ `TSharedPtr<SWidget> AddSRGBWidget();`
- L58 _public prototype_ `FTG_OutputSettings GetSettings() const;`
- L59 _public prototype_ `void GenerateStringsFromEnum(TArray<FString>& OutEnumNames, const FString& EnumPathName);`
- L62 _public prototype_ `template<typename T> void GenerateValuesFromEnum(TArray<T>& OutEnumValues, const FString& EnumPathName) const;`
- L65 _public prototype_ `template<typename T> int GetValueFromIndex(const FString& EnumPathName, int Index) const;`
- L66 _public prototype_ `FString GetEnumValueDisplayName(const FString& EnumPathName, int EnumValue) const;`
- L67 _public prototype_ `EVisibility ShowParameters() const;`
- L68 _public prototype_ `EVisibility ShowPinLabel() const;`
- L72 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L73 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L77 _private member_ `UEdGraphPin* GraphPinObj;`
- L79 _private member_ `TSlateAttribute<FTG_OutputSettings> OutputSettingsAttribute;`
- L80 _private member_ `FOnOutputSettingsChanged OnOutputSettingsChanged;`
- L81 _private member_ `FTG_OutputSettings CachedOutputSettings;`
- L82 _private member_ `FString SelectedWidthName;`
- L84 _private member_ `int SelectedWidthIndex;`
- L85 _private member_ `int SelectedHeightIndex;`
- L86 _private member_ `int SelectedFormatIndex;`
- L87 _private member_ `int SelectedTextureTypeIndex;`
- L88 _private member_ `int SelectedLodGroupIndex;`
- L89 _private member_ `int SelectedCompressionIndex;`
- L90 _private member_ `bool bSRGB = false;`
- L92 _private member_ `FGetTextDelegate GetPathDelegate;`
- L93 _private member_ `FTextCommitted PathCommitted;`
- L94 _private member_ `FGetTextDelegate GetNameDelegate;`
- L95 _private member_ `FTextCommitted NameCommitted;`
- L96 _private member_ `FGenerateEnumMenu OnGenerateWidthMenu;`
- L97 _private member_ `FGetTextDelegate GetWidthDelegate;`
- L98 _private member_ `FGenerateEnumMenu OnGenerateHeightMenu;`
- L99 _private member_ `FGetTextDelegate GetHeightDelegate;`
- L100 _private member_ `FGenerateEnumMenu OnGenerateFormatMenu;`
- L101 _private member_ `FGetTextDelegate GetFormatDelegate;`
- L102 _private member_ `FGenerateEnumMenu OnGenerateTexturePresetTypeMenu;`
- L103 _private member_ `FGetTextDelegate GetTexturePresetTypeDelegate;`
- L104 _private member_ `FGenerateEnumMenu OnGenerateLodGroupMenu;`
- L105 _private member_ `FGetTextDelegate GetLodGroupDelegate;`
- L106 _private member_ `FGenerateEnumMenu OnGenerateCompressionMenu;`
- L107 _private member_ `FGetTextDelegate GetCompressionDelegate;`
- L109 _private prototype_ `FText GetNameAsText() const;`
- L110 _private prototype_ `void OnNameCommitted(const FText& NewText, ETextCommit::Type CommitInfo);`
- L112 _private prototype_ `FText GetPathAsText() const;`
- L113 _private prototype_ `void OnPathCommitted(const FText& NewText, ETextCommit::Type CommitInfo);`
- L115 _private prototype_ `TSharedRef<SWidget> OnGenerateWidthEnumMenu();`
- L116 _private prototype_ `void HandleWidthChanged(FString OuputName, int Index);`
- L117 _private prototype_ `FText HandleWidthText() const;`
- L119 _private prototype_ `TSharedRef<SWidget> OnGenerateHeightEnumMenu();`
- L120 _private prototype_ `void HandleHeightChanged(FString OuputName, int Index);`
- L121 _private prototype_ `FText HandleHeightText() const;`
- L123 _private prototype_ `TSharedRef<SWidget> OnGenerateFormatEnumMenu();`
- L124 _private prototype_ `void HandleFormatChanged(FString OuputName, int Index);`
- L125 _private prototype_ `FText HandleFormatText() const;`
- L127 _private prototype_ `TSharedRef<SWidget> OnGenerateTexturePresetTypeEnumMenu();`
- L128 _private prototype_ `void HandleTexturePresetTypeChanged(FString OuputName, int Index);`
- L129 _private prototype_ `FText HandleTexturePresetTypeText() const;`
- L131 _private prototype_ `TSharedRef<SWidget> OnGenerateLodGroupEnumMenu();`
- L132 _private prototype_ `void HandleLodGroupChanged(FString OuputName, int Index);`
- L133 _private prototype_ `FText HandleLodGroupText() const;`
- L135 _private prototype_ `TSharedRef<SWidget> OnGenerateCompressionEnumMenu();`
- L136 _private prototype_ `void HandleCompressionChanged(FString OuputName, int Index);`
- L137 _private prototype_ `FText HandleCompressionText() const;`
- L139 _private prototype_ `ECheckBoxState HandleSRGBIsChecked() const;`
- L140 _private prototype_ `void HandleSRGBExecute(ECheckBoxState InNewState);`
- L142 _private prototype_ `FReply OnBrowseClick();`
- L144 _private prototype_ `bool IsDefaultPreset() const;`
- L146 _private member_ `const int LabelSize = 150;`

#### Free symbols / members of external scopes

- L24 _delegate_ `DECLARE_DELEGATE_RetVal(FText, FGetTextDelegate);`
- L25 _delegate_ `DECLARE_DELEGATE_TwoParams(FTextCommitted, const FText&, ETextCommit::Type);`
- L26 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedRef<SWidget>, FGenerateEnumMenu);`
- L30 _delegate_ `DECLARE_DELEGATE_OneParam(FOnOutputSettingsChanged, const FTG_OutputSettings& ) SLATE_BEGIN_ARGS(STG_GraphPinOutputSettingsWidget) : _DescriptionMaxWidth(250.0f) , _PropertyHandle(nullptr) {} SLATE_ARGUMENT(float, DescriptionMaxWidth) SLATE_ATTRIBUTE(FTG_OutputSettings, OutputSettings) SLATE_ARGUMENT(TSharedPtr<IPropertyHandle>, PropertyHandle) SLATE_EVENT(FOnOutputSettingsChanged, OnOutputSettingsChanged) SLATE_END_ARGS();`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/Pins/STG_GraphPinString.h` (Private)


#### class `STG_GraphPinString`  
`class STG_GraphPinString : public SGraphPin`  
_L16-41_
- inherits: `SGraphPin`
- L19 _public function_ `SLATE_BEGIN_ARGS(STG_GraphPinString)`
- L20 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L26 _protected prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L29 _protected prototype_ `FText GetTypeInValue() const;`
- L30 _protected prototype_ `virtual void SetTypeInValue(const FText& NewTypeInValue, ETextCommit::Type CommitInfo);`
- L33 _protected prototype_ `bool GetDefaultValueIsReadOnly() const;` — @return True if the pin default value field is read-only
- L36 _private prototype_ `TSharedRef<SWidget> GenerateComboBoxEntry(TSharedPtr<FString> Value);`
- L37 _private prototype_ `void HandleComboBoxSelectionChanged(TSharedPtr<FString> Value, ESelectInfo::Type InSelectInfo);`
- L38 _private prototype_ `TSharedPtr<SWidget> TryBuildComboBoxWidget();`
- L40 _private member_ `TArray<TSharedPtr<FString>> ComboBoxOptions;`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/Pins/STG_GraphPinTextureDescriptor.h` (Private)


#### class `STG_GraphPinTextureDescriptor`  
`class STG_GraphPinTextureDescriptor : public SGraphPin`  
_L10-46_
- inherits: `SGraphPin`
- L13 _public function_ `SLATE_BEGIN_ARGS(STG_GraphPinTextureDescriptor)`
- L14 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L17 _public prototype_ `FProperty* GetPinProperty() const;`
- L18 _public prototype_ `bool ShowChildProperties() const;`
- L19 _public prototype_ `bool CollapsibleChildProperties() const;`
- L20 _public prototype_ `EVisibility ShowLabel() const;`
- L22 _public prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L23 _public prototype_ `virtual TSharedRef<SWidget> GetLabelWidget(const FName& InLabelStyle) override;`
- L28 _private prototype_ `void ParseDefaultValueData();` — Parses the Data from the pin to fill in the names of the array.
- L30 _private function_ `bool GetDefaultValueIsEnabled() const`
- L35 _private prototype_ `const FSlateBrush* GetAdvancedViewArrow() const;`
- L36 _private prototype_ `void OnAdvancedViewChanged(const ECheckBoxState NewCheckedState);`
- L37 _private prototype_ `ECheckBoxState IsAdvancedViewChecked() const;`
- L38 _private prototype_ `EVisibility IsUIEnabled() const;`
- L40 _private prototype_ `FTG_TextureDescriptor GetTextureDescriptor() const;`
- L41 _private prototype_ `void OnTextureDescriptorChanged(const FTG_TextureDescriptor& NewTextureDescriptor);`
- L44 _private member_ `FTG_TextureDescriptor TextureDescriptor;` — Parse TextureDescriptor used for editing.
- L45 _private member_ `bool bIsUIHidden = true;`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/Pins/STG_GraphPinTextureDescriptorWidget.h` (Private)


#### class `STG_GraphPinTextureDescriptorWidget`  
`class STG_GraphPinTextureDescriptorWidget : public SCompoundWidget, public FEditorUndoClient`  
_L19-110_
- inherits: `SCompoundWidget,FEditorUndoClient`
- desc: Widget for editing TextureDescriptor.
- L24 _private prototype_ `DECLARE_DELEGATE_RetVal(FText, FGetTextDelegate);`
- L25 _private prototype_ `DECLARE_DELEGATE_TwoParams(FTextCommitted, const FText&, ETextCommit::Type);`
- L26 _private prototype_ `DECLARE_DELEGATE_RetVal(TSharedRef<SWidget>, FGenerateEnumMenu);`
- L30 _public function_ `DECLARE_DELEGATE_OneParam(FOnTextureDescriptorChanged, const FTG_TextureDescriptor& ) SLATE_BEGIN_ARGS(STG_GraphPinTextureDescriptorWidget) : _DescriptionMaxWidth(250.0f) , _PropertyHandle(nullptr)`
- L39 _public prototype_ `SLATE_ARGUMENT(float, DescriptionMaxWidth) SLATE_ATTRIBUTE(FTG_TextureDescriptor, TextureDescriptor) SLATE_ARGUMENT(TSharedPtr<IPropertyHandle>, PropertyHandle) SLATE_EVENT(FOnTextureDescriptorChanged, OnTextureDescriptorChanged) SLATE_END_ARGS();` — Maximum with of the query description field.
- L50 _public prototype_ `STG_GraphPinTextureDescriptorWidget();`
- L53 _public prototype_ `void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L54 _public prototype_ `TSharedRef<SWidget> AddEnumComobox(FText Label, FGetTextDelegate GetText, FGenerateEnumMenu OnGenerateEnumMenu);`
- L55 _public prototype_ `TSharedRef<SWidget> AddSRGBWidget();`
- L56 _public prototype_ `FTG_TextureDescriptor GetSettings() const;`
- L57 _public prototype_ `void GenerateStringsFromEnum(TArray<FString>& OutEnumNames, const FString& EnumPathName);`
- L60 _public prototype_ `template<typename T> void GenerateValuesFromEnum(TArray<T>& OutEnumValues, const FString& EnumPathName) const;`
- L63 _public prototype_ `template<typename T> int GetValueFromIndex(const FString& EnumPathName, int Index) const;`
- L64 _public prototype_ `FString GetEnumValueDisplayName(const FString& EnumPathName, int EnumValue) const;`
- L65 _public prototype_ `EVisibility ShowParameters() const;`
- L66 _public prototype_ `EVisibility ShowPinLabel() const;`
- L70 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L71 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L75 _private member_ `UEdGraphPin* GraphPinObj;`
- L77 _private member_ `TSlateAttribute<FTG_TextureDescriptor> TextureDescriptorAttribute;`
- L78 _private member_ `FOnTextureDescriptorChanged OnTextureDescriptorChanged;`
- L79 _private member_ `FTG_TextureDescriptor CachedTextureDescriptor;`
- L80 _private member_ `FString SelectedWidthName;`
- L82 _private member_ `int SelectedWidthIndex;`
- L83 _private member_ `int SelectedHeightIndex;`
- L84 _private member_ `int SelectedFormatIndex;`
- L85 _private member_ `bool bSRGB = false;`
- L87 _private member_ `FGenerateEnumMenu OnGenerateWidthMenu;`
- L88 _private member_ `FGetTextDelegate GetWidthDelegate;`
- L89 _private member_ `FGenerateEnumMenu OnGenerateHeightMenu;`
- L90 _private member_ `FGetTextDelegate GetHeightDelegate;`
- L91 _private member_ `FGenerateEnumMenu OnGenerateFormatMenu;`
- L92 _private member_ `FGetTextDelegate GetFormatDelegate;`
- L94 _private prototype_ `TSharedRef<SWidget> OnGenerateWidthEnumMenu();`
- L95 _private prototype_ `void HandleWidthChanged(FString OuputName, int Index);`
- L96 _private prototype_ `FText HandleWidthText() const;`
- L98 _private prototype_ `TSharedRef<SWidget> OnGenerateHeightEnumMenu();`
- L99 _private prototype_ `void HandleHeightChanged(FString OuputName, int Index);`
- L100 _private prototype_ `FText HandleHeightText() const;`
- L102 _private prototype_ `TSharedRef<SWidget> OnGenerateFormatEnumMenu();`
- L103 _private prototype_ `void HandleFormatChanged(FString OuputName, int Index);`
- L104 _private prototype_ `FText HandleFormatText() const;`
- L106 _private prototype_ `ECheckBoxState HandleSRGBIsChecked() const;`
- L107 _private prototype_ `void HandleSRGBExecute(ECheckBoxState InNewState);`
- L109 _private member_ `const int LabelSize = 75;`

#### Free symbols / members of external scopes

- L24 _delegate_ `DECLARE_DELEGATE_RetVal(FText, FGetTextDelegate);`
- L25 _delegate_ `DECLARE_DELEGATE_TwoParams(FTextCommitted, const FText&, ETextCommit::Type);`
- L26 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedRef<SWidget>, FGenerateEnumMenu);`
- L30 _delegate_ `DECLARE_DELEGATE_OneParam(FOnTextureDescriptorChanged, const FTG_TextureDescriptor& ) SLATE_BEGIN_ARGS(STG_GraphPinTextureDescriptorWidget) : _DescriptionMaxWidth(250.0f) , _PropertyHandle(nullptr) {} SLATE_ARGUMENT(float, DescriptionMaxWidth) SLATE_ATTRIBUTE(FTG_TextureDescriptor, TextureDescriptor) SLATE_ARGUMENT(TSharedPtr<IPropertyHandle>, PropertyHandle) SLATE_EVENT(FOnTextureDescriptorChanged, OnTextureDescriptorChanged) SLATE_END_ARGS();`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/Pins/STG_TextureDescriptor.h` (Private)


#### class `STG_TextureDescriptor`  
`class STG_TextureDescriptor : public SCompoundWidget, public FEditorUndoClient`  
_L19-97_
- inherits: `SCompoundWidget,FEditorUndoClient`
- desc: Widget for editing TextureDescriptor.
- L22 _private prototype_ `DECLARE_DELEGATE_RetVal(FText, FGetTextDelegate);`
- L23 _private prototype_ `DECLARE_DELEGATE_TwoParams(FTextCommitted, const FText&, ETextCommit::Type);`
- L24 _private prototype_ `DECLARE_DELEGATE_RetVal(TSharedRef<SWidget>, FGenerateEnumMenu);`
- L28 _public function_ `DECLARE_DELEGATE_OneParam(FOnTextureDescriptorChanged, const FTG_TextureDescriptor& ) SLATE_BEGIN_ARGS(STG_TextureDescriptor) : _DescriptionMaxWidth(250.0f) ,_ShowingAsPin(true) , _PropertyHandle(nullptr)`
- L38 _public prototype_ `SLATE_ARGUMENT(float, DescriptionMaxWidth) SLATE_ARGUMENT(bool, ShowingAsPin) SLATE_ARGUMENT(TSharedPtr<IPropertyHandle>, PropertyHandle) SLATE_EVENT(FOnTextureDescriptorChanged, OnTextureDescriptorChanged) SLATE_END_ARGS();` — Maximum with of the query description field.
- L49 _public prototype_ `void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L50 _public prototype_ `TSharedRef<SWidget> AddEditBox(FText Label, FGetTextDelegate GetText, FTextCommitted OnTextCommitted);`
- L51 _public prototype_ `TSharedRef<SWidget> AddEnumComobox(FText Label, FGetTextDelegate GetText, FGenerateEnumMenu OnGenerateEnumMenu);`
- L52 _public prototype_ `FTG_TextureDescriptor GetTextureDescriptor() const;`
- L53 _public prototype_ `void SetValue(FTG_TextureDescriptor Settings);`
- L54 _public prototype_ `void GenerateStringsFromEnum(TArray<FString>& OutEnumNames, const FString& EnumPathName);`
- L55 _public prototype_ `int GetValueFromIndex(const FString& EnumPathName, int Index) const;`
- L56 _public prototype_ `FString GetEnumValueDisplayName(const FString& EnumPathName, int EnumValue) const;`
- L60 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L61 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L65 _private member_ `UEdGraphPin* GraphPinObj;`
- L67 _private member_ `FOnTextureDescriptorChanged OnTextureDescriptorChanged;`
- L68 _private member_ `FTG_TextureDescriptor CachedTextureDescriptor;`
- L69 _private member_ `FString SelectedWidthName;`
- L71 _private member_ `int SelectedWidthIndex;`
- L72 _private member_ `int SelectedHeightIndex;`
- L73 _private member_ `int SelectedFormatIndex;`
- L75 _private member_ `bool ShowingAsPin;`
- L77 _private member_ `FGenerateEnumMenu OnGenerateWidthMenu;`
- L78 _private member_ `FGetTextDelegate GetWidthDelegate;`
- L79 _private member_ `FGenerateEnumMenu OnGenerateHeightMenu;`
- L80 _private member_ `FGetTextDelegate GetHeightDelegate;`
- L81 _private member_ `FGenerateEnumMenu OnGenerateFormatMenu;`
- L82 _private member_ `FGetTextDelegate GetFormatDelegate;`
- L84 _private prototype_ `TSharedRef<SWidget> OnGenerateWidthEnumMenu();`
- L85 _private prototype_ `void HandleWidthChanged(FString OuputName, int Index);`
- L86 _private prototype_ `FText HandleWidthText() const;`
- L88 _private prototype_ `TSharedRef<SWidget> OnGenerateHeightEnumMenu();`
- L89 _private prototype_ `void HandleHeightChanged(FString OuputName, int Index);`
- L90 _private prototype_ `FText HandleHeightText() const;`
- L92 _private prototype_ `TSharedRef<SWidget> OnGenerateFormatEnumMenu();`
- L93 _private prototype_ `void HandleFormatChanged(FString OuputName, int Index);`
- L94 _private prototype_ `FText HandleFormatText() const;`
- L96 _private prototype_ `void AddVerticalSeperation(TSharedPtr<SVerticalBox> VBox, FMargin Padding);`

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_DELEGATE_RetVal(FText, FGetTextDelegate);`
- L23 _delegate_ `DECLARE_DELEGATE_TwoParams(FTextCommitted, const FText&, ETextCommit::Type);`
- L24 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedRef<SWidget>, FGenerateEnumMenu);`
- L28 _delegate_ `DECLARE_DELEGATE_OneParam(FOnTextureDescriptorChanged, const FTG_TextureDescriptor& ) SLATE_BEGIN_ARGS(STG_TextureDescriptor) : _DescriptionMaxWidth(250.0f) ,_ShowingAsPin(true) , _PropertyHandle(nullptr) {} SLATE_ARGUMENT(float, DescriptionMaxWidth) SLATE_ARGUMENT(bool, ShowingAsPin) SLATE_ARGUMENT(TSharedPtr<IPropertyHandle>, PropertyHandle) SLATE_EVENT(FOnTextureDescriptorChanged, OnTextureDescriptorChanged) SLATE_END_ARGS();`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/SBlobTile.h` (Private)


#### class `SBlobTile`  
`class SBlobTile : public SBorder, public FGCObject`  
_L11-53_
- inherits: `SBorder,FGCObject`
- desc: Need FGCObject to control garbage collection of objects
- L14 _public function_ `SLATE_BEGIN_ARGS(SBlobTile) : _withToolTip(false), _withDescription(false), _padding(FMargin(0,0,0,0)), _borderColor(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f)), _blob(nullptr)`
- L20 _public prototype_ `SLATE_ARGUMENT(bool, withToolTip) SLATE_ARGUMENT(bool, withDescription) SLATE_ARGUMENT(FMargin, padding) SLATE_ARGUMENT(FLinearColor, borderColor) SLATE_ARGUMENT(BlobPtr , blob) SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L29 _public prototype_ `void CreateWidgetBrush(UTexture* BlobTexture);`
- L30 _public prototype_ `void MakeWidgetMaterial(bool bShowChecker);`
- L32 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override`
- L37 _public function_ `virtual FString GetReferencerName() const override`
- L44 _private prototype_ `void SetPercentageBorderSize(FMargin margin);`
- L46 _private member_ `uint32 ImageWidth = 1;`
- L47 _private member_ `uint32 ImageHeight = 1;`
- L48 _private member_ `FString ImageName;`
- L51 _private member_ `TSharedPtr<FSlateBrush> Brush;` — Needs our own brush to display the blob content
- L52 _private member_ `TObjectPtr<UMaterialInstanceDynamic> BrushMaterial = nullptr;`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/SBlobTileView.h` (Private)


#### class `SBlobTileView`  
`class SBlobTileView : public SBorder, public FGCObject`  
_L15-50_
- inherits: `SBorder,FGCObject`
- desc: Need FGCObject to control garbage collection of objects
- L18 _public function_ `SLATE_BEGIN_ARGS(SBlobTileView) : _withToolTip(false), _withDescription(false), _finalized(true), _padding(FMargin(0, 0, 0, 0)), _blob(nullptr), _OnFinalizeBlob()`
- L25 _public prototype_ `SLATE_ARGUMENT(bool, withToolTip) SLATE_ARGUMENT(bool, withDescription) SLATE_ARGUMENT(bool, finalized) SLATE_ARGUMENT(FMargin, padding) SLATE_ARGUMENT(BlobPtr , blob) SLATE_EVENT(FOnFinalizeBlobEvent, OnFinalizeBlob) SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L35 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override`
- L40 _public function_ `virtual FString GetReferencerName() const override`
- L46 _private prototype_ `void CreateTiles(BlobPtr Blob, TSharedPtr<SUniformGridPanel> GridPanel, FMargin Padding);`
- L48 _private member_ `TSharedPtr<FSlateBrush> _brush;` — Needs our own brush to display the blob content
- L49 _private member_ `TObjectPtr<UMaterialInstanceDynamic> _brushMaterial = nullptr;`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_DELEGATE(FOnFinalizeBlobEvent);`
- L13 _prototype_ `DECLARE_DELEGATE(FOnFinalizeBlobEvent);`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/STG_EditorViewport.h` (Private)


#### class `STG_EditorViewport`  
`class STG_EditorViewport : public SAssetEditorViewport, public FGCObject, public ICommonEditorViewportToolbarInfoProvider`  
_L26-113_
- inherits: `SAssetEditorViewport,FGCObject,ICommonEditorViewportToolbarInfoProvider`
- L29 _public function_ `SLATE_BEGIN_ARGS(STG_EditorViewport)`
- L37 _private member_ `FName CurrentMaterialName;`
- L38 _private member_ `FName RenderModeName;` — Current Selected render mode name
- L39 _private member_ `TArray<FName> RenderModesList;`
- L40 _private member_ `TSharedPtr<class FEditorViewportClient> EditorViewportClient;` — Editor viewport client
- L41 _private member_ `TObjectPtr<UTextureGraphBase> TextureGraphPtr;` — Pointer to the Texture Graph being shown
- L43 _private member_ `EViewModeIndex CurrentViewMode;` — The currently selected view mode
- L44 _private member_ `TSharedPtr<FAdvancedPreviewScene> PreviewScene;` — The scene for this viewport
- L45 _private member_ `TObjectPtr<UMeshComponent> PreviewMeshComponent;` — Component for the preview mesh
- L46 _private member_ `EThumbnailPrimType PreviewPrimType;` — The preview primitive we are using
- L48 _private member_ `FDelegateHandle PreviewFeatureLevelChangedHandle;` — Handle to the registered OnPreviewFeatureLevelChanged delegate
- L50 _private member_ `RenderModeToolBar;`
- L52 _private member_ `TSharedPtr<TG_RenderModeManager> RenderModeMgr;`
- L55 _protected prototype_ `void GenerateRenderModesList();`
- L57 _protected prototype_ `virtual FReply OnDrop( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L59 _public prototype_ `void Construct(const FArguments& InArgs);`
- L60 _public prototype_ `void SetTextureGraph(const TObjectPtr<UTextureGraphBase>& InTextureGraph);`
- L62 _public prototype_ `STG_EditorViewport();`
- L65 _public prototype_ `void RefreshViewport();`
- L66 _public prototype_ `bool SetPreviewAsset(UObject* InAsset);`
- L67 _public prototype_ `void OnSetPreviewPrimitive(EThumbnailPrimType PrimType, bool bInitialLoad = false);`
- L68 _public prototype_ `bool IsPreviewPrimitiveChecked(EThumbnailPrimType PrimType) const;`
- L69 _public prototype_ `void OnSetPreviewMeshFromSelection();`
- L70 _public prototype_ `bool IsPreviewMeshFromSelectionChecked() const;`
- L71 _public prototype_ `void TogglePreviewGrid();`
- L72 _public prototype_ `bool IsTogglePreviewGridChecked() const;`
- L73 _public prototype_ `void TogglePreviewBackground();`
- L74 _public prototype_ `bool IsTogglePreviewBackgroundChecked() const;`
- L76 _public prototype_ `void GenerateRendermodeToolbar();`
- L77 _public function_ `TArray<FName> GetRenderModesList() const`
- L78 _public prototype_ `bool IsRenderModeEnabled(FName RenderModeTypeArg) const;`
- L79 _public prototype_ `void SetRenderMode(FName RenderModeTypeArg);`
- L80 _public prototype_ `void InitRenderModes(UTextureGraphBase* InTextureGraph);`
- L81 _public prototype_ `void UpdateRenderMode();`
- L82 _public function_ `FText GetRenderModeName()`
- L83 _public function_ `FName GetRenderModeFName()`
- L85 _public prototype_ `void InitPreviewMesh();`
- L88 _public prototype_ `class FEditorViewportClient& GetViewportClient();` — @return The editor viewport client
- L89 _public prototype_ `void OnObjectPropertyChanged(UObject* ObjectBeingModified, FPropertyChangedEvent& PropertyChangedEvent);`
- L92 _public function_ `TSharedRef<FAdvancedPreviewScene> GetPreviewScene()` — Returns the preview scene being rendered in the viewport
- L95 _public prototype_ `virtual TSharedRef<class SEditorViewport> GetViewportWidget() override;` — ICommonEditorViewportToolbarInfoProvider interface
- L96 _public prototype_ `virtual TSharedPtr<FExtender> GetExtenders() const override;`
- L97 _public prototype_ `virtual void OnFloatingButtonClicked() override;`
- L101 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L102 _public prototype_ `bool SetPreviewAssetByName(const TCHAR* InAssetName);`
- L104 _public prototype_ `virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;`
- L105 _public prototype_ `virtual TSharedPtr<SWidget> BuildViewportToolbar() override;`
- L106 _public prototype_ `virtual TSharedPtr<IPreviewProfileController> CreatePreviewProfileController() override;`
- L107 _public prototype_ `virtual void PopulateViewportOverlays(TSharedRef<class SOverlay> Overlay) override;`
- L108 _public prototype_ `virtual void BindCommands() override;`
- L112 _public function_ `FORCEINLINE virtual FString GetReferencerName() const override` — Overriding ReferencerName as it should be unique name

#### Free symbols / members of external scopes

- L24 _macro_ `#define LOCTEXT_NAMESPACE "TG_Editor"`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/STG_EditorViewportToolBar.h` (Private)


#### class `STG_EditorViewportPreviewShapeToolBar`  
`class STG_EditorViewportPreviewShapeToolBar : public SViewportToolBar`  
_L16-23_
- inherits: `SViewportToolBar`
- L19 _public function_ `SLATE_BEGIN_ARGS(STG_EditorViewportPreviewShapeToolBar)`
- L20 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<class STG_EditorViewport> InViewport);`

#### class `STG_EditorViewportRenderModeToolBar`  
`class STG_EditorViewportRenderModeToolBar : public SViewportToolBar`  
_L25-40_
- inherits: `SViewportToolBar`
- L28 _public function_ `SLATE_BEGIN_ARGS(STG_EditorViewportRenderModeToolBar)`
- L29 _public prototype_ `SLATE_END_ARGS() TSharedPtr<SEditorViewportToolbarMenu> RenderModeToolBar;`
- L32 _public member_ `TSharedPtr<SHorizontalBox> HorizontalBox;`
- L33 _public member_ `TSharedPtr<class STG_EditorViewport>ViewportRef;` — Holds the reference of view port
- L34 _public member_ `FName CurrentRenderMode;`
- L35 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<class STG_EditorViewport> InViewport);`
- L36 _public prototype_ `void HandleOnRenderModeChange(FName UpdatedRenderMode);`
- L37 _public prototype_ `TSharedRef<SWidget> GenerateRenderModes();`
- L38 _public prototype_ `FText GetRenderModeLabel() const;`
- L39 _public prototype_ `void Init();`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/STG_NodePreview.h` (Private)


#### class `FNodeViewer`  
`class FNodeViewer final : public UE::ImageWidgets::IImageViewer`  
_L25-92_
- inherits: `UE::ImageWidgets::IImageViewer`
- desc: Image viewer implementation that holds the node buffer information and draws the node texture.
- L29 _public prototype_ `virtual FImageInfo GetCurrentImageInfo() const override;` — IImageViewer overrides - begin
- L30 _public prototype_ `virtual void DrawCurrentImage(FViewport* Viewport, FCanvas* Canvas, const FDrawProperties& Properties) override;`
- L31 _public prototype_ `virtual TOptional<TVariant<FColor, FLinearColor>> GetCurrentImagePixelColor(FIntPoint PixelCoords, int32 MipIndex) const override;`
- L32 _public function_ `virtual void OnImageSelected(const FGuid& ImageGuid) override`
- L33 _public function_ `virtual bool IsValidImage(const FGuid& Guid) const override`
- L34 _public function_ `virtual FText GetImageName(const FGuid& Guid) const override`
- L38 _public prototype_ `FText GetFormatLabelText() const;` — Returns the format label for the status bar
- L41 _public prototype_ `bool IsSingleChannel() const;` — Indicates that a node is single channel, i.e. grayscale.
- L44 _public prototype_ `void SetTexture(const BlobPtr& InBlob, FLinearColor InClearColor = FLinearColor(0.1f, 0.1f, 0.1f, 1));` — Sets the node buffer to a given node.
- L45 _public prototype_ `void UpdateTexture();`
- L48 _public prototype_ `void SetLabelText(FText InText);` — Sets the label text.
- L51 _public prototype_ `void SetRGBA(bool bR, bool bG, bool bB, bool bA);` — Toggles RGBA components for display.
- L54 _public prototype_ `void SetDrawSettings(const UE::ImageWidgets::SImageViewport::FDrawSettings& InDrawSettings);` — Sets the required Draw settings for the viewport.
- L57 _public prototype_ `UE::ImageWidgets::SImageViewport::FDrawSettings GetDrawSettings() const;` — Returns the Draw settings for the viewport.
- L60 _private prototype_ `void DrawTexture(const FTextureResource* TextureResource, FCanvas* Canvas, const FDrawProperties::FPlacement& TilePlacementInfo, const FDrawProperties::FMip& Mip) const;` — Draws the node texture in the viewport
- L64 _private prototype_ `ESimpleElementBlendMode GetBlendMode() const;` — Determines the blend mode based on the node texture and the RGBA toggles.
- L67 _private prototype_ `UTexture* GetTextureFromBuffer(const DeviceBufferPtr& Buffer) const;` — Retrieves the texture  from a given node buffer.
- L70 _private prototype_ `int32 GetNodeTextureNumMips() const;` — Returns the num mips for node texture
- L73 _private prototype_ `bool IsSRGB() const;` — Indicates that a node is in sRGB format.
- L76 _private member_ `BlobPtr CurrentBlob;` — The Blob for this node.
- L79 _private member_ `UTexture* NodeTexture = nullptr;` — The texture for the node.
- L82 _private member_ `bool bRGBA[4] = {true, true, true, true};` — Toggles for enabling RGBA components for drawing.
- L85 _private member_ `BufferDescriptor NodeDescriptor;` — Node meta data.
- L88 _private member_ `UE::ImageWidgets::SImageViewport::FDrawSettings DrawSettings;` — Current draw settings for the viewport.
- L91 _private member_ `FText LabelText;` — Label text for adding node description.

#### class `STG_NodePreviewWidget`  
`class STG_NodePreviewWidget : public SCompoundWidget`  
_L97-164_
- inherits: `SCompoundWidget`
- desc: Widget for the Node Preview tab containing the image viewport.
- L100 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnNodeBlobChanged, BlobPtr Blob);`
- L102 _public function_ `SLATE_BEGIN_ARGS(STG_NodePreviewWidget)`
- L107 _public prototype_ `SLATE_EVENT(FOnNodeBlobChanged, OnNodeBlobChanged) SLATE_END_ARGS() virtual ~STG_NodePreviewWidget() override;` — Callback to notify about the node preview texture having changed.
- L112 _public prototype_ `UE::ImageWidgets::SImageViewport::FDrawSettings GetDrawSettings() const;`
- L113 _public prototype_ `void Construct(const FArguments& InArgs);`
- L116 _public prototype_ `void SelectionChanged(UTG_Node* Node);` — Notify the preview about the node selection having changed.
- L119 _public prototype_ `void NodeDeleted(const UTG_Node* Node);` — Notify the preview about a node being deleted.
- L122 _public prototype_ `void Update() const;` — Trigger an update of the node preview after the displayed contents changed.
- L124 _public prototype_ `bool GetOutputVariantFromNode(FTG_Variant& OutVariant) const;`
- L127 _public prototype_ `FText GetLabelText(FTG_Variant& InVariant, bool bValidVariant) const;` — Get the label text for the node preview
- L130 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;` — SWidget overrides - begin
- L135 _private prototype_ `void AddFormatLabel(SHorizontalBox& HorizontalBox);` — Add toolbar and status bar extensions to the viewport.
- L136 _private prototype_ `void AddLockButton(FToolBarBuilder& ToolbarBuilder) const;`
- L137 _private prototype_ `void AddRGBAButtons(FToolBarBuilder& ToolbarBuilder);`
- L140 _private prototype_ `void ToggleLock();` — Toggles the node preview lock based on the lock button extension in the viewport toolbar.
- L143 _private member_ `TSharedPtr<UE::ImageWidgets::SImageViewport> Viewport;` — The viewport widget for displaying the node preview.
- L146 _private member_ `TSharedPtr<FNodeViewer> NodeViewer;` — The image viewer implementation holding and drawing the actual image.
- L149 _private member_ `TSharedPtr<FUICommandList> CommandList;` — The additional commands used for this widget.
- L153 _private member_ `UTG_Node* SelectedNode = nullptr;` — UTG_EdGraphNode* SelectedNode = nullptr;
- L157 _private member_ `UTG_Node* LockedNode = nullptr;` — UTG_EdGraphNode* LockedNode = nullptr;
- L160 _private member_ `FOnNodeBlobChanged OnNodeBlobChanged;` — Callback to notify about the node preview texture having changed to make sure that for example the histogram is synced with the node preview.
- L163 _private member_ `bool bRGBA[4] = {true, true, true, true};` — Flags for toggling RGBA channels in the preview, which are hooked up to the RGBA buttons in the viewport toolbar extension.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ImageWidgets` (scope `UE`)
- L100 _delegate_ `DECLARE_DELEGATE_OneParam(FOnNodeBlobChanged, BlobPtr Blob);`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/STG_OutputSelectionDlg.h` (Private)


#### class `STG_OutputSelectionDlg`  
`class STG_OutputSelectionDlg : public SWindow`  
_L12-37_
- inherits: `SWindow`
- L14 _private function_ `SLATE_BEGIN_ARGS(STG_OutputSelectionDlg)`
- L22 _public prototype_ `void Construct(const FArguments& InArgs);`
- L25 _public prototype_ `EAppReturnType::Type ShowModal();` — Displays the dialog in a blocking fashion
- L28 _protected prototype_ `FReply OnButtonClick(EAppReturnType::Type ButtonID);`
- L29 _protected member_ `EAppReturnType::Type UserResponse;`
- L32 _private member_ `TSharedPtr<SScrollBox> ScrollBox;`
- L33 _private member_ `TObjectPtr<UTG_EdGraph> EdGraph;`
- L35 _private prototype_ `void AddExportItems();`
- L36 _private prototype_ `void OnOutputSelectionChanged(const FString ItemName, ECheckBoxState NewState);`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/STG_OutputSelector.h` (Private)


#### class `STG_OutputSelector`  
`class STG_OutputSelector : public SCompoundWidget`  
_L10-29_
- inherits: `SCompoundWidget`
- L12 _private prototype_ `DECLARE_DELEGATE_TwoParams(FOnOutputSelectionChanged, const FString ItemName, ECheckBoxState NewState);`
- L14 _private function_ `SLATE_BEGIN_ARGS(STG_OutputSelector)`
- L23 _public prototype_ `void Construct(const FArguments& InArgs);`
- L24 _public prototype_ `ECheckBoxState OnCheckBoxState() const;`
- L26 _public member_ `FOnOutputSelectionChanged OnOutputSelectionChanged;`
- L28 _private member_ `bool bIsSelected;`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnOutputSelectionChanged, const FString ItemName, ECheckBoxState NewState);`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/STG_Palette.h` (Private)


#### class `STG_PaletteItem`  
`class STG_PaletteItem : public SGraphPaletteItem`  
_L22-45_
- inherits: `SGraphPaletteItem`
- desc: This class is the custom Graph action menu item for Texture Graph
- L25 _public function_ `SLATE_BEGIN_ARGS(STG_PaletteItem)`
- L26 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, FCreateWidgetForActionData* const InCreateData);`
- L30 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L33 _protected prototype_ `virtual FString GetIconBrushName();`
- L35 _protected prototype_ `virtual FString GetDefaultIconBrushName();`
- L37 _protected prototype_ `TSharedRef<SWidget> CreateHotkeyDisplayWidget(const TSharedPtr<const FInputChord> HotkeyChord);` — Create the hotkey display widget
- L39 _protected prototype_ `const FSlateBrush* GetIconBrush();`
- L41 _protected prototype_ `virtual FText GetItemTooltip() const override;`
- L44 _protected member_ `FCreateWidgetMouseButtonDown MouseButtonDownDelegate;` — Delegate executed when mouse button goes down

#### class `STG_PaletteTileItem`  
`class STG_PaletteTileItem : public STG_PaletteItem`  
_L48-69_
- inherits: `STG_PaletteItem`
- desc: Widget for displaying a single item
- L51 _public function_ `SLATE_BEGIN_ARGS( STG_PaletteTileItem )`
- L52 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, FCreateWidgetForActionData* const InCreateData);`
- L56 _public prototype_ `virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L58 _public prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L61 _protected prototype_ `virtual FString GetIconBrushName() override;`
- L63 _protected prototype_ `virtual FString GetDefaultIconBrushName() override;`
- L66 _private member_ `TSharedPtr<SBox> BackgroundArea;`
- L67 _private member_ `TSharedPtr<SImage> IconWidget;`
- L68 _private member_ `FSlateBrush BackgroundBrush;`

#### class `STG_Palette`  
`class STG_Palette : public SGraphPalette`  
_L73-137_
- inherits: `SGraphPalette`
- L76 _public function_ `SLATE_BEGIN_ARGS( STG_Palette )`
- L77 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TWeakPtr<FTG_Editor> InTGEditorPtr);`
- L83 _protected prototype_ `virtual TSharedRef<SWidget> OnCreateWidgetForAction(FCreateWidgetForActionData* const InCreateData) override;` — SGraphPalette Interface
- L84 _protected prototype_ `virtual void CollectAllActions(FGraphActionListBuilderBase& OutAllActions) override;`
- L85 _protected prototype_ `virtual void RefreshActionsList(bool bPreserveExpansion) override;`
- L88 _protected prototype_ `void CreatePaletteMenu();`
- L90 _protected prototype_ `TSharedRef<SWidget> CreatePaletteTileMenu();`
- L92 _protected prototype_ `TSharedPtr<SWidget> FindWidgetInChildren(TSharedPtr<SWidget> Parent, FName ChildType) const;`
- L94 _protected prototype_ `TSharedRef<SWidget> CreatePaletteListMenu();`
- L96 _protected prototype_ `TSharedRef<SWidget> CreateViewToggle();`
- L99 _protected prototype_ `FString GetFilterCategoryName() const;` — Get the currently selected category name
- L102 _protected prototype_ `void CategorySelectionChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);` — Callback for when the selected category changes
- L105 _protected prototype_ `void AddAssetFromAssetRegistry(const FAssetData& InAddedAssetData);` — Callback from the Asset Registry when a new asset is added.
- L108 _protected prototype_ `void RemoveAssetFromRegistry(const FAssetData& InAddedAssetData);` — Callback from the Asset Registry when an asset is removed.
- L111 _protected prototype_ `void RenameAssetFromRegistry(const FAssetData& InAddedAssetData, const FString& InNewName);` — Callback from the Asset Registry when an asset is renamed.
- L113 _protected prototype_ `void RefreshAssetInRegistry(const FAssetData& InAddedAssetData);`
- L115 _protected prototype_ `EVisibility GetVisibility(bool IsTileView) const;`
- L117 _protected prototype_ `ECheckBoxState OnGetToggleCheckState(bool IsTileView) const;`
- L120 _protected member_ `bool IsTileViewChecked = true;`
- L121 _protected member_ `bool IsListViewChecked = false;`
- L122 _protected member_ `FSlateBrush BackgroundBrush;`
- L123 _protected member_ `FSlateBrush BackgroundHoverBrush;`
- L124 _protected member_ `FSlateBrush CheckedBrush;`
- L126 _protected member_ `TWeakPtr<FTG_Editor> TGEditorPtr;` — Pointer back to the material editor that owns us
- L129 _protected member_ `TArray< TSharedPtr<FString> > CategoryNames;` — List of available Category Names
- L132 _protected member_ `TSharedPtr<STextComboBox> CategoryComboBox;` — Combo box used to select category
- L134 _protected member_ `TSharedPtr<SWidget> ToggleButtons;`
- L136 _protected member_ `TSharedPtr<STG_ActionMenuTileView> TGActionMenuTileView;`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/STG_TextureDetails.h` (Private)


#### class `STG_TextureDetails`  
`class STG_TextureDetails : public SCompoundWidget`  
_L14-46_
- inherits: `SCompoundWidget`
- L16 _private function_ `SLATE_BEGIN_ARGS(STG_TextureDetails)`
- L22 _public prototype_ `void Construct(const FArguments& InArgs);`
- L23 _public prototype_ `void CalculateHistogram(BlobPtr InBlob, UTextureGraph* InTextureGraph);`
- L25 _private member_ `TiledBlobPtr HistogramResult;`
- L27 _private member_ `bool UseBlobWidget = true;`
- L28 _private prototype_ `void MakeControls();`
- L30 _private member_ `TSharedPtr<SVerticalBox> VerticalBox;`
- L31 _private member_ `TSharedPtr<STG_RGBAButtons> RGBAButtons;`
- L32 _private member_ `TSharedPtr<STextureHistogram> TextureHistogramWidget;`
- L33 _private member_ `TSharedPtr<STG_HistogramBlob> HistogramBlobWidgetR;`
- L34 _private member_ `TSharedPtr<STG_HistogramBlob> HistogramBlobWidgetG;`
- L35 _private member_ `TSharedPtr<STG_HistogramBlob> HistogramBlobWidgetB;`
- L36 _private member_ `TSharedPtr<STG_HistogramBlob> HistogramBlobWidgetLuma;`
- L37 _private member_ `bool bShowHistogram = true;`
- L38 _private member_ `FSlateRoundedBoxBrush* CheckedBrush;`
- L40 _private prototype_ `void ClearHistogramWidgets();`
- L41 _private prototype_ `void AddHistogramWidget();`
- L42 _private prototype_ `EVisibility ShowR() const;`
- L43 _private prototype_ `EVisibility ShowG() const;`
- L44 _private prototype_ `EVisibility ShowB() const;`
- L45 _private prototype_ `EVisibility ShowLuma() const;`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/TG_Editor.h` (Private)


#### class `FTG_Editor`  
`class FTG_Editor : public ITG_Editor, public FGCObject, public FTickableGameObject, public FEditorUndoClient, public FNotifyHook`  
_L36-352_
- inherits: `ITG_Editor,FGCObject,FTickableGameObject,FEditorUndoClient,FNotifyHook`
- L39 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;`
- L40 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;`
- L41 _public prototype_ `void OnTextureGraphPreSave(UObject* Object, FObjectPreSaveContext SaveContext);`
- L49 _public prototype_ `void InitEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UTextureGraph* TG_Script);` — Edits the specified static TSX Asset object @param	Mode								Asset editing mode for this editor (standalone or world-centric) @param	InitToolkitHost						When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param	ObjectToEdit						The TSX Asset to edit
- L52 _public prototype_ `FTG_Editor();` — Constructor
- L57 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;` — Inherited via ITG_Editor
- L58 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L59 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L60 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L63 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — Inherited via FGCObject
- L65 _public function_ `virtual FString GetReferencerName() const override`
- L67 _public prototype_ `class UMixInterface* GetTextureGraphInterface() const override;`
- L70 _public prototype_ `virtual void Tick(float DeltaTime) override;` — Inherited via FTickableGameObject
- L72 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L74 _public function_ `virtual bool IsTickableWhenPaused() const override`
- L76 _public function_ `virtual bool IsTickableInEditor() const override`
- L78 _public prototype_ `virtual TStatId GetStatId() const override;`
- L80 _public prototype_ `virtual FText GetOriginalObjectName() const override;`
- L82 _public prototype_ `virtual TSharedPtr<IAssetReferenceFilter> MakeAssetReferenceFilter() const override;`
- L84 _public prototype_ `UTG_Expression* CreateNewExpression(UClass* NewExpressionClass, const FVector2D& NodePos, bool bAutoSelect, bool bAutoAssignResource, const class UEdGraph* Graph = nullptr) override;`
- L87 _public function_ `TSharedRef<class IDetailsView> GetDetailView() const` — Widget Accessors
- L90 _public function_ `TSharedRef<class IDetailsView> GetPreviewSettingsView() const` — Widget Accessors
- L93 _public function_ `TSharedRef<class IDetailsView> GetOutputView() const` — Widget Accessors
- L96 _public function_ `TSharedRef<class IDetailsView> GetParameterView() const` — Widget Accessors parameters panel
- L99 _public prototype_ `void FocusDetailsPanel();` — Called to bring focus to the details panel
- L102 _public prototype_ `void RefreshErrors();` — Refresh Errors and Warnings
- L105 _public prototype_ `void RefreshPreviewViewport();` — Refreshes the viewport containing the preview mesh.
- L108 _public prototype_ `void RefreshNodePreview(const TSet<class UObject*>& NewSelection, const FInvalidationDetails* Details, bool bUpdateOnly);` — Called to update the selection view
- L110 _public prototype_ `void SetMesh(class UMeshComponent* InPreviewMesh, class UWorld* InWorld) override;`
- L111 _public prototype_ `bool SetPreviewAsset(UObject* InAsset);`
- L114 _public prototype_ `void RefreshDetailsView() const;` — Force Refresh Details View
- L117 _protected prototype_ `TArray<UTG_EdGraphNode*> GetCurrentSelectedTG_EdGraphNodes() const;`
- L121 _protected prototype_ `void OnSelectedNodesChanged(const TSet<class UObject*>& NewSelection);` — Called when the selection changes in the GraphEditor
- L123 _protected prototype_ `void OnNodeDoubleClicked(UEdGraphNode* EdGraphNode);` — Called when a node is double clicked
- L125 _protected prototype_ `virtual void RefreshViewport() override;`
- L127 _protected prototype_ `virtual void RefreshTool() override;`
- L132 _protected prototype_ `virtual void SaveAsset_Execute() override;` — Called when "Save" is clicked for this asset
- L133 _protected prototype_ `virtual void SaveAssetAs_Execute() override;`
- L134 _protected prototype_ `virtual bool OnRequestClose(EAssetEditorCloseReason InCloseReason) override;`
- L135 _protected prototype_ `virtual void OnClose() override;`
- L138 _protected prototype_ `bool UpdateOriginalTextureGraph();`
- L142 _private prototype_ `void RegisterToolbar();` — Register TG_ specific toolbar for the editor
- L144 _private prototype_ `virtual void PostInitAssetEditor() override;`
- L146 _private prototype_ `void OnRenameNodeClicked();`
- L147 _private prototype_ `bool CanRenameNode() const;`
- L149 _private prototype_ `void BindCommands();` — Bind commands to delegates
- L150 _private prototype_ `void SetShowNodeHistogramView(bool bValue);`
- L151 _private prototype_ `void SetShowPaletteView(bool bValue);`
- L153 _private prototype_ `void OnGraphChanged(UTG_Graph* InGraph, UTG_Node* InNode, bool Tweaking);`
- L155 _private prototype_ `void OnNodeAdded(UTG_Node* InNode);`
- L156 _private prototype_ `void OnNodeRemoved(UTG_Node* InNode, FName Name);`
- L157 _private prototype_ `void OnNodeRenamed(UTG_Node* InNode, FName OldName);`
- L158 _private prototype_ `bool IsOutputNode(UTG_Node* InNode);`
- L159 _private prototype_ `void UpdateMixSettings();`
- L161 _private prototype_ `void OnPinSelectionUpdated(UEdGraphPin* Pin);`
- L163 _private prototype_ `void OnRunGraph_Clicked();` — Run Graph by invoking the graph notifications
- L166 _private prototype_ `void ToggleAutoUpdate();`
- L167 _private prototype_ `bool IsShowingAutoUpdate() const;`
- L169 _private prototype_ `void HandleTabWindowSelected(const FName TabID,const FString OuputName);`
- L170 _private prototype_ `bool GetTabSelected(const FName TabID);`
- L172 _private prototype_ `void OnRenderingDone(UMixInterface* TextureGraph, const FInvalidationDetails* Details);`
- L173 _private prototype_ `void OnBatchQueued(UMixInterface* TextureGraph, const FInvalidationDetails* Details);`
- L174 _private prototype_ `void OnPreviewMeshChangedEvent();`
- L175 _private prototype_ `void OnViewportMaterialChanged();`
- L176 _private prototype_ `void OnMaterialMappingChanged();`
- L178 _private prototype_ `void OnLogGraph_Clicked();` — Log Graph in console
- L181 _private prototype_ `void UndoGraphAction();` — Called to undo the last action
- L184 _private prototype_ `void RedoGraphAction();` — Called to redo the last undone action
- L186 _private prototype_ `void ReplicateExtraNodes() const;`
- L187 _private prototype_ `void OnCreateComment();`
- L190 _private prototype_ `void OnConvertInputParameterToFromConstant();` — Called when converting an INputParm node from / to constant
- L192 _private prototype_ `bool OnVerifyNodeTextCommit(const FText& Text, UEdGraphNode* EdGraphNode, FText& OutErrorMessage);`
- L194 _private prototype_ `TSharedRef<class SGraphEditor> CreateGraphEditorWidget();` — Create new graph editor widget
- L196 _private prototype_ `FActionMenuContent OnCreateGraphActionMenu(UEdGraph* InGraph, const FVector2f& InNodePosition, const TArray<UEdGraphPin*>& InDraggedPins, bool bAutoExpand, SGraphEditor::FActionMenuClosed InOnMenuClosed);`
- L199 _private prototype_ `TSharedRef<class STG_NodePreviewWidget> CreateNodePreviewWidget();` — Create Node preview widget
- L202 _private prototype_ `TSharedRef<class STG_TextureDetails> CreateTextureDetailsWidget();` — Create Texture details widget
- L205 _private prototype_ `FGraphAppearanceInfo GetGraphAppearance() const;` — Gets the current TG_ Graph's appearance
- L208 _private prototype_ `void BuildSubTools();` — Builds the sub-tools that are a part of the texture graph editor.
- L211 _private prototype_ `void OnEditorLayoutChanged();` — Called when the Viewport Layout has changed.
- L213 _private prototype_ `void OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent);`
- L215 _private prototype_ `void OnFinishedChangingSettings(const FPropertyChangedEvent& PropertyChangedEvent);`
- L217 _private prototype_ `void OnFinishedChangingOutput(const FPropertyChangedEvent& PropertyChangedEvent);`
- L219 _private prototype_ `void UpdateParametersUI();`
- L222 _private prototype_ `FString GetCurrentFolderInContentBrowser();` — Get the Current selected folder from content browser
- L224 _private prototype_ `void DeleteSelectedNodes();` — Delete all selected nodes in the graph
- L226 _private prototype_ `bool DeleteNodes(TArray<class UEdGraphNode*> NodesToDelete, bool ForceDelete = false);` — Deletes the list of provided nodes. Force delete override CanUserDeleteNode check
- L228 _private prototype_ `bool CanDeleteSelectedNodes() const;` — Whether we can delete all selected nodes
- L230 _private prototype_ `void CopySelectedNodes();` — Copy all selected nodes in the graph
- L232 _private prototype_ `bool CanCopySelectedNodes() const;` — Whether we can copy all selected nodes
- L234 _private prototype_ `void CutSelectedNodes();`
- L236 _private prototype_ `bool CanCutSelectedNodes() const;`
- L238 _private prototype_ `void DuplicateSelectedNodes();`
- L240 _private prototype_ `bool CanDuplicateSelectedNodes() const;`
- L241 _private prototype_ `void PasteNodes();`
- L243 _private prototype_ `void DeleteSelectedDuplicatableNodes();`
- L244 _private prototype_ `void PasteNodesHere(const FVector2D& Location, const class UEdGraph* Graph);`
- L246 _private prototype_ `bool CanPasteNodes() const;`
- L249 _private prototype_ `void OnNodeTitleCommitted(const FText& NewText, ETextCommit::Type CommitInfo, UEdGraphNode* NodeBeingChanged);` — Called when the title of a node is changed
- L252 _private prototype_ `void OnSelectedBlobChanged(BlobPtr Blob);` — Called when blob gets updated for the Texture Selection Preview
- L255 _private prototype_ `TSharedRef<SDockTab> SpawnTab_GraphEditor(const FSpawnTabArgs& Args);`
- L256 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args);`
- L257 _private prototype_ `TSharedRef<SDockTab> SpawnTab_TG_Properties(const FSpawnTabArgs& Args);`
- L258 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Palette(const FSpawnTabArgs& Args);`
- L259 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Find(const FSpawnTabArgs& Args);`
- L260 _private prototype_ `TSharedRef<SDockTab> SpawnTab_PreviewSettings(const FSpawnTabArgs& Args);`
- L261 _private prototype_ `TSharedRef<SDockTab> SpawnTab_ParameterDefaults(const FSpawnTabArgs& Args);`
- L262 _private prototype_ `TSharedRef<SDockTab> SpawnTab_NodePreview(const FSpawnTabArgs& Args);`
- L263 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Output(const FSpawnTabArgs& Args);`
- L264 _private prototype_ `TSharedRef<SDockTab> SpawnTab_PreviewSceneSettings(const FSpawnTabArgs& Args);`
- L265 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Errors(const FSpawnTabArgs& Args);`
- L266 _private prototype_ `TSharedRef<SDockTab> SpawnTab_TextureDetails(const FSpawnTabArgs& Args);`
- L268 _private prototype_ `void ExportAsUAsset();`
- L269 _private prototype_ `FReply OnExportClick();`
- L271 _private prototype_ `TSharedPtr<class STG_EditorViewport> GetEditorViewport() const;`
- L272 _private prototype_ `void SetViewportPreviewMesh();`
- L274 _private prototype_ `bool CanEnableOnRun();`
- L276 _private prototype_ `void UpdateGenerator();`
- L277 _private prototype_ `void RunGraph(bool Tweaking);`
- L278 _private prototype_ `void JumpToNode(const UEdGraphNode* Node);`
- L279 _private prototype_ `void OnMessageLogLinkActivated(const class TSharedRef<IMessageToken>& Token);`
- L281 _private prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient Interface
- L282 _private function_ `virtual void PostRedo(bool bSuccess) override`
- L285 _public member_ `TObjectPtr<UTextureGraph> OriginalTextureGraph;` — Original Texture Graph
- L288 _public member_ `TObjectPtr<UTextureGraph> EditedTextureGraph;` — Duplicated Texture Graph used in the editor
- L289 _public member_ `TObjectPtr<UTG_EdGraph> TG_EdGraph;`
- L290 _public member_ `FDateTime SessionStartTime;`
- L293 _private member_ `TObjectPtr<UTG_Parameters> TG_Parameters;`
- L294 _private member_ `FExportSettings TargetExportSettings;`
- L297 _private member_ `TSharedPtr<class IDetailsView> DetailsView;` — Property View
- L300 _private member_ `TSharedPtr<class IDetailsView> PreviewSettingsView;` — Settings View
- L303 _private member_ `TSharedPtr<class IDetailsView> OutputView;` — Output View
- L306 _private member_ `TSharedPtr<class IDetailsView> ParameterView;` — Parameter View
- L309 _private member_ `TSharedPtr<SGraphEditor> GraphEditorWidget;` — Graph editor widget being displayed
- L312 _private member_ `TSharedPtr<STG_NodePreviewWidget> NodePreview;` — Node preview widget being displayed
- L315 _private member_ `TSharedPtr<class STG_TextureDetails> TextureDetails;` — Texture details widget being displayed
- L318 _private member_ `TSharedPtr<FUICommandList> GraphEditorCommands;` — Command list for this editor
- L321 _private member_ `AssetEditorViewportFactoryFunction MakeViewportFunc;` — Storage for our viewport creation function that will be passed to the viewport layout system
- L323 _private member_ `FAdvancedPreviewSceneModule::FOnPreviewSceneChanged OnPreviewSceneChangedDelegate;`
- L326 _private member_ `TSharedPtr<class FEditorViewportTabContent> ViewportTabContent;` — Tracking the active viewports in this editor.
- L329 _private member_ `TWeakPtr<SDockTab> SpawnedDetailsTab;` — Tab that holds the details panel
- L330 _private member_ `TWeakPtr<SDockTab> NodeHistogramTab;`
- L331 _private member_ `TWeakPtr<SDockTab> PaletteTab;`
- L332 _private member_ `TWeakPtr<SDockTab> PreviewSceneSettingsDockTab;`
- L335 _private member_ `TSharedPtr<class SWidget> ErrorsWidget;` — Stats log, with the log listing that it reflects
- L336 _private member_ `TSharedPtr<class IMessageLogListing> ErrorsListing;`
- L339 _private member_ `TSharedPtr<SWidget> AdvancedPreviewSettingsWidget;` — Scene preview settings widget
- L342 _private member_ `FString ErrorHash;` — Hashed error code use to refresh the error displaying widget when this will change
- L345 _private member_ `uint32 ParametersHash;` — Hash for Graph Params to check if anything was added
- L347 _private member_ `TSharedPtr<class IPropertyRowGenerator> Generator;`
- L349 _private member_ `TSharedPtr<class STG_Palette> Palette;`
- L351 _private member_ `bool bAutoRunGraph = true;`

#### Free symbols / members of external scopes

- L34 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureGraphEditor, Log, All);`
- L34 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureGraphEditor, Log, All);`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/TG_EditorCommands.h` (Private)


#### class `FTG_EditorCommands`  
`class FTG_EditorCommands : public TCommands<FTG_EditorCommands>`  
_L8-39_
- inherits: `TCommands<FTG_EditorCommands>`
- L11 _public prototype_ `FTG_EditorCommands();`
- L14 _public prototype_ `virtual void RegisterCommands() override;`
- L17 _public member_ `TSharedPtr<FUICommandInfo> RunGraph;`
- L18 _public member_ `TSharedPtr<FUICommandInfo> AutoUpdateGraph;`
- L19 _public member_ `TSharedPtr<FUICommandInfo> LogGraph;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> ExportAsUAsset;`
- L25 _public member_ `TSharedPtr< FUICommandInfo > ConvertInputParameterToConstant;` — Node Actions
- L26 _public member_ `TSharedPtr< FUICommandInfo > ConvertInputParameterFromConstant;` — Convert an input param to from constant
- L31 _public member_ `TSharedPtr< FUICommandInfo > SetCylinderPreview;` — Viewport Commands
- L32 _public member_ `TSharedPtr< FUICommandInfo > SetSpherePreview;` — Sets the preview mesh to a sphere
- L33 _public member_ `TSharedPtr< FUICommandInfo > SetPlanePreview;` — Sets the preview mesh to a plane
- L34 _public member_ `TSharedPtr< FUICommandInfo > SetCubePreview;` — Sets the preview mesh to a cube
- L35 _public member_ `TSharedPtr< FUICommandInfo > SetPreviewMeshFromSelection;` — Sets the preview mesh to the current selection in the level editor
- L36 _public member_ `TSharedPtr< FUICommandInfo > TogglePreviewGrid;` — Toggles the preview pane's grid
- L37 _public member_ `TSharedPtr< FUICommandInfo > TogglePreviewBackground;` — Toggles the preview pane's background

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/TG_EditorTabs.h` (Private)


#### struct `FTG_EditorTabs`  
`struct FTG_EditorTabs`  
_L8-27_
- desc: TG_ editor tabs identifiers
- L11 _public member_ `static const FName ViewportTabId;` — The tab id for the TG_ fixture types tab
- L12 _public member_ `static const FName PropertiesTabId;`
- L13 _public member_ `static const FName PaletteTabId;`
- L14 _public member_ `static const FName FindTabId;`
- L15 _public member_ `static const FName GraphEditorId;`
- L16 _public member_ `static const FName PreviewSceneSettingsTabId;`
- L17 _public member_ `static const FName ParameterDefaultsTabId;`
- L18 _public member_ `static const FName NodePreviewTabId;`
- L19 _public member_ `static const FName OutputTabId;`
- L20 _public member_ `static const FName PreviewSettingsTabId;`
- L21 _public member_ `static const FName ErrorsTabId;`
- L22 _public member_ `static const FName TextureDetailsTabId;`
- L23 _public member_ `static const FName TextureExporterTabId;`
- L26 _public prototype_ `FTG_EditorTabs() = delete;` — Disable default constructor

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/TG_Factory.h` (Private)


#### class `UTG_Factory`  
`class UTG_Factory : public UFactory`  
_L9-15_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L13 _public prototype_ `UTG_Factory();`
- L14 _public prototype_ `UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn);`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/TG_InstanceEditor.h` (Private)


#### class `FTG_InstanceEditor`  
`class FTG_InstanceEditor : public ITG_Editor, public FGCObject, public FTickableGameObject, public FEditorUndoClient`  
_L28-97_
- inherits: `ITG_Editor,FGCObject,FTickableGameObject,FEditorUndoClient`
- L31 _protected prototype_ `virtual void RefreshViewport() override;`
- L32 _protected prototype_ `virtual void RefreshTool() override;`
- L35 _public prototype_ `virtual void SetMesh(UMeshComponent* PreviewMesh, UWorld* World) override;`
- L37 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;`
- L38 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;`
- L39 _public prototype_ `void OnTextureGraphPreSave(UObject* Object, FObjectPreSaveContext SaveContext);`
- L41 _public prototype_ `TSharedRef<SDockTab> SpawnTab_TG_Properties(const FSpawnTabArgs& Args);`
- L49 _public prototype_ `void InitEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UTextureGraphInstance* TG_Script);` — Edits the specified static TSX Asset object @param	Mode								Asset editing mode for this editor (standalone or world-centric) @param	InitToolkitHost						When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param	ObjectToEdit						The TSX Asset to edit
- L52 _public prototype_ `FTG_InstanceEditor();` — Constructor
- L57 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;` — Inherited via ITG_Editor
- L58 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L59 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L60 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L63 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — Inherited via FGCObject
- L65 _public function_ `virtual FString GetReferencerName() const override`
- L67 _public prototype_ `virtual class UMixInterface* GetTextureGraphInterface() const override;`
- L70 _public prototype_ `virtual void Tick(float DeltaTime) override;` — Inherited via FTickableGameObject
- L72 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L74 _public function_ `virtual bool IsTickableWhenPaused() const override`
- L76 _public function_ `virtual bool IsTickableInEditor() const override`
- L78 _public prototype_ `virtual TStatId GetStatId() const override;`
- L80 _public prototype_ `virtual FText GetOriginalObjectName() const override;`
- L82 _public prototype_ `virtual TSharedPtr<IAssetReferenceFilter> MakeAssetReferenceFilter() const override;`
- L85 _public prototype_ `virtual void OnClose() override;`
- L93 _private member_ `TUniquePtr<struct FTG_InstanceImpl> InstanceImpl;`
- L95 _private member_ `TObjectPtr<UTextureGraphInstance> TextureGraphInstance;`

#### Free symbols / members of external scopes

- L26 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureGraphInstanceEditor, Log, All);`
- L26 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTextureGraphInstanceEditor, Log, All);`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/TG_InstanceFactory.h` (Private)


#### class `UTG_InstanceFactory`  
`class UTG_InstanceFactory : public UFactory`  
_L10-19_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L15 _public member_ `TObjectPtr<class UTextureGraphBase> InitialParent;` — `UPROPERTY()`
- L17 _public prototype_ `UTG_InstanceFactory();`
- L18 _public prototype_ `UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn);`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/TG_RenderModeManager.h` (Private)


#### enum `ERenderModes`  
`enum class ERenderModes : uint8`  
_L11-28_
- reflection: `UENUM()`
- L13 _public enumerator_ `PBRMetalness UMETA(DisplayName = "PBR Metalness")`
- L14 _public enumerator_ `Albedo UMETA(DisplayName = "Albedo")`
- L15 _public enumerator_ `Normal UMETA(DisplayName = "Normal")`
- L16 _public enumerator_ `Displacement UMETA(DisplayName = "Displacement")`
- L17 _public enumerator_ `Roughness UMETA(DisplayName = "Roughness")`
- L18 _public enumerator_ `Specular UMETA(DisplayName = "Specular")`
- L19 _public enumerator_ `Metalness UMETA(DisplayName = "Metalness")`
- L20 _public enumerator_ `LayerMask UMETA(DisplayName = "Layer Mask")`
- L21 _public enumerator_ `ActiveMask UMETA(DisplayName = "Active Mask")`
- L22 _public enumerator_ `UV UMETA(DisplayName = "D: UV")`
- L23 _public enumerator_ `WorldNormals UMETA(DisplayName = "D: WorldNormals")`
- L24 _public enumerator_ `WorldTangents UMETA(DisplayName = "D: WorldTangents")`
- L25 _public enumerator_ `WorldPosition UMETA(DisplayName = "D: WorldPosition")`
- L26 _public enumerator_ `WorldUVMask UMETA(DisplayName = "D: WorldUVMask")`
- L27 _public enumerator_ `Default = PBRMetalness UMETA(DisplayName = "Default")`

#### class `TG_RenderModeManager`  
`class TG_RenderModeManager`  
_L37-61_
- L40 _protected member_ `FName _lastRenderMode;` — Last used render mode (used for unbinding)
- L41 _protected member_ `FName _currentRenderMode;` — Currently applied render mode
- L42 _protected member_ `TMap<int, MaterialMap> _renderModeMaterials;`
- L43 _protected member_ `TArray<FName> _renderModesString;`
- L45 _protected prototype_ `void InitializeDefaultMaterials(int totalTargets, UTextureGraphBase* TextureGraph);`
- L46 _protected prototype_ `RenderMaterial_BPPtr GetTargetRenderModeMaterial(int targetId, FName renderMode);`
- L47 _protected prototype_ `void BindBlobToMaterial(RenderMaterialPtr renderMaterial, TiledBlobPtr blobToBind, const FName& targetName);`
- L48 _protected prototype_ `virtual void UpdateRenderMode(UTextureGraphBase* TextureGraph);`
- L50 _public prototype_ `TG_RenderModeManager();`
- L51 _public prototype_ `virtual ~TG_RenderModeManager();`
- L52 _public prototype_ `virtual void ChangeRenderMode(FName NewRenderMode, UTextureGraphBase* TextureGraph);`
- L53 _public prototype_ `void Clear();`
- L54 _public prototype_ `bool IsCurrentRenderModelLit(int targetId = 0);`
- L59 _public function_ `FORCEINLINE FName GetCurrentRenderMode()`
- L60 _public function_ `FORCEINLINE FName GetLastRenderMode()`

#### Free symbols / members of external scopes

- L32 _typedef_ `typedef std::shared_ptr<RenderMaterial_BP> RenderMaterial_BPPtr;`
- L33 _typedef_ `typedef std::shared_ptr<class RenderMaterial> RenderMaterialPtr;`
- L34 _typedef_ `typedef std::shared_ptr<class TiledBlob> TiledBlobPtr;`
- L35 _typedef_ `typedef TMap<FName, RenderMaterial_BPPtr> MaterialMap;`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/TG_Style.h` (Private)


#### class `FTG_Style`  
`class FTG_Style : public FSlateStyleSet`  
_L9-21_
- inherits: `FSlateStyleSet`
- L13 _public prototype_ `static void Register();`
- L14 _public prototype_ `static void Unregister();`
- L15 _public prototype_ `static TArray<FString> GetPaletteIconNames();`
- L16 _public prototype_ `static const FTG_Style& Get();`
- L18 _public prototype_ `const bool HasKey(FName StyleName) const;`
- L20 _private prototype_ `FTG_Style();`

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace TSEditorStyleConstants`
- L26 _variable_ `const FName Pin_Generic_Image_C = TEXT("TS.` (scope `TSEditorStyleConstants`)
- L27 _variable_ `const FName Pin_Generic_Image_DC = TEXT("TS.` (scope `TSEditorStyleConstants`)
- L28 _variable_ `const FName Pin_IN_Image_C = TEXT("TS.` (scope `TSEditorStyleConstants`)
- L29 _variable_ `const FName Pin_IN_Image_DC = TEXT("TS.` (scope `TSEditorStyleConstants`)
- L30 _variable_ `const FName Pin_OUT_Image_C = TEXT("TS.` (scope `TSEditorStyleConstants`)
- L31 _variable_ `const FName Pin_OUT_Image_DC = TEXT("TS.` (scope `TSEditorStyleConstants`)
- L33 _variable_ `const FName Pin_IN_Vector_C = TEXT("TS.` (scope `TSEditorStyleConstants`)
- L34 _variable_ `const FName Pin_IN_Vector_DC = TEXT("TS.` (scope `TSEditorStyleConstants`)
- L35 _variable_ `const FName Pin_OUT_Vector_C = TEXT("TS.` (scope `TSEditorStyleConstants`)
- L36 _variable_ `const FName Pin_OUT_Vector_DC = TEXT("TS.` (scope `TSEditorStyleConstants`)
- L38 _variable_ `const FName Pin_IN_Scalar_C = TEXT("TS.` (scope `TSEditorStyleConstants`)
- L39 _variable_ `const FName Pin_IN_Scalar_DC = TEXT("TS.` (scope `TSEditorStyleConstants`)
- L40 _variable_ `const FName Pin_OUT_Scalar_C = TEXT("TS.` (scope `TSEditorStyleConstants`)
- L41 _variable_ `const FName Pin_OUT_Scalar_DC = TEXT("TS.` (scope `TSEditorStyleConstants`)

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/Widgets/ActionMenuWidgets/STG_ActionMenuTileView.h` (Private)


#### class `STG_ActionMenuTileView`  
`class STG_ActionMenuTileView : public SCompoundWidget, public FGCObject`  
_L57-365_
- inherits: `SCompoundWidget,FGCObject`
- desc: This class implements the hibrid Graph and Tile view of GraphActionMenu
- L61 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FOnCreateWidgetForAction, FCreateWidgetForActionData* const);` — Delegate that can be used to create a widget for a particular action
- L63 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SExpanderArrow>, FOnCreateCustomRowExpander, FCustomExpanderData const&);` — Delegate that can be used to create a custom "expander" widget for a particular row
- L65 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnActionSelected, const TArray< TSharedPtr<FEdGraphSchemaAction> >&, ESelectInfo::Type);` — Delegate executed when an action is selected
- L67 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnActionDoubleClicked, const TArray< TSharedPtr<FEdGraphSchemaAction> >&);` — Delegate executed when an action is double clicked
- L69 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnActionDragged, const TArray< TSharedPtr<FEdGraphSchemaAction> >&, const FPointerEvent&);` — Delegate executed when an action is dragged
- L71 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnCategoryDragged, const FText&, const FPointerEvent&);` — Delegate executed when a category is dragged
- L73 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnCollectAllActions, FGraphActionListBuilderBase&);` — Delegate executed when the list of all actions needs to be refreshed
- L75 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnCollectStaticSections, TArray<int32>&) DECLARE_DELEGATE_ThreeParams(FOnCategoryTextCommitted, const FText&, ETextCommit::Type, TWeakPtr< FGraphActionNode >);` — Delegate executed when the list of all actions needs to be refreshed, should return any sections that should always be visible, even if they don't have children.
- L79 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FCanRenameSelectedAction, TWeakPtr< FGraphActionNode >);` — Delegate executed to check if the selected action is valid for renaming
- L81 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FGetSectionTitle, int32);` — Delegate to get the name of a section if the widget is a section separator.
- L83 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<IToolTip>, FGetSectionToolTip, int32);` — Delegate to get the tooltip of a section if the widget is a section separator.
- L85 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<SWidget>, FGetSectionWidget, TSharedRef<SWidget>, int32);` — Delegate to get the widget that appears on the section bar in the section separator.
- L87 _public prototype_ `DECLARE_DELEGATE_RetVal(FText, FGetFilterText);` — Delegate to get the filter text
- L89 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnActionMatchesName, FEdGraphSchemaAction*, const FName&);` — Delegate to check if an action matches a specified name (used for renaming items etc.)
- L91 _public prototype_ `DECLARE_DELEGATE_RetVal(TSharedRef<FGraphActionListBuilderBase>, FOnGetActionList);` — Delegate that can be used to create and/or get a custom action list.
- L93 _public function_ `SLATE_BEGIN_ARGS(STG_ActionMenuTileView) : _AutoExpandActionMenu(false) , _AlphaSortItems(true) , _SortItemsRecursively(true) , _ShowFilterTextBox(true) , _UseSectionStyling(false) , _bAllowPreselectedItemActivation(false) , _GraphObj(nullptr)`
- L103 _public prototype_ `SLATE_EVENT(FOnActionSelected, OnActionSelected) SLATE_EVENT(FOnActionDoubleClicked, OnActionDoubleClicked) SLATE_EVENT(FOnActionDragged, OnActionDragged) SLATE_EVENT(FOnCategoryDragged, OnCategoryDragged) SLATE_EVENT(FOnContextMenuOpening, OnContextMenuOpening) SLATE_EVENT(FOnCreateWidgetForAction, OnCreateWidgetForAction) SLATE_EVENT(FOnCreateCustomRowExpander, OnCreateCustomRowExpander) SLATE_EVENT(FOnGetActionList, OnGetActionList) SLATE_EVENT(FOnCollectAllActions, OnCollectAllActions) SLATE_EVENT(FOnCollectStaticSections, OnCollectStaticSections) SLATE_EVENT(FOnCategoryTextCommitted, OnCategoryTextCommitted) SLATE_EVENT(FCanRenameSelectedAction, OnCanRenameSelectedAction) SLATE_EVENT(FGetSectionTitle, OnGetSectionTitle) SLATE_EVENT(FGetSectionToolTip, OnGetSectionToolTip) SLATE_EVENT(FGetSectionWidget, OnGetSectionWidget) SLATE_EVENT(FGetFilterText, OnGetFilterText) SLATE_EVENT(FOnActionMatchesName, OnActionMatchesName) SLATE_ARGUMENT(bool, AutoExpandActionMenu) SLATE_ARGUMENT(bool, AlphaSortItems) SLATE_ARGUMENT(bool, SortItemsRecursively) SLATE_ARGUMENT(bool, ShowFilterTextBox) SLATE_ARGUMENT(bool, UseSectionStyling) SLATE_ARGUMENT(bool, bAllowPreselectedItemActivation) SLATE_ARGUMENT(TArray<UEdGraphPin*>, DraggedFromPins) SLATE_ARGUMENT(UEdGraph*, GraphObj) SLATE_END_ARGS() void Construct(const FArguments& InArgs, bool bIsReadOnly = true);`
- L134 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject override
- L135 _public prototype_ `virtual FString GetReferencerName() const override;`
- L136 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L143 _public prototype_ `void RefreshAllActions(bool bPreserveExpansion, bool bHandleOnSelectionEvent = true);` — Refreshes the actions that this widget should display @param bPreserveExpansion		TRUE if the expansion state of the tree should be preserved @param bHandleOnSelectionEvent		TRUE if the item should be selected and any actions that occur with selection will be handled. FALSE and only selection will occur
- L146 _public prototype_ `void GetSectionExpansion(TMap<int32, bool>& SectionExpansion) const;` — Returns a map of all top level sections and their current expansion state.
- L149 _public prototype_ `void SetSectionExpansion(const TMap<int32, bool>& SectionExpansion);` — Sets the sections to be expanded of all top level sections.
- L151 _public prototype_ `void CalculateFillScale(const FGeometry& AllottedGeometry);`
- L153 _public prototype_ `float GetTileViewItemWidth() const;`
- L157 _protected member_ `TSharedPtr< STreeView< TSharedPtr<FGraphActionNode> > > TreeView;` — Tree view for showing actions
- L160 _protected member_ `TMap< TSharedPtr<FGraphActionNode>, TSharedPtr<STileView<TSharedPtr<FGraphActionNode> > > > TreeTileViewMap;` — Tree tile view map for showing actions
- L163 _protected member_ `TSharedPtr<SSearchBox> FilterTextBox;` — Text box used for searching for actions
- L166 _protected member_ `TSharedPtr<FGraphActionListBuilderBase> AllActions;` — List of all actions we can browser
- L169 _protected member_ `TArray< TSharedPtr<FGraphActionNode> > FilteredActionNodes;` — Flattened list of all actions passing the filter
- L172 _protected member_ `TSharedPtr<FGraphActionNode> FilteredRootAction;` — Root of filtered actions tree
- L175 _protected member_ `float SelectedSuggestionScore;` — Stored score for our current selection, so that we can quickly maintain selection when building the list asynchronously
- L177 _protected member_ `int32 SelectedSuggestionSourceIndex;` — Stored index in the AllActions list builder that we think is the best fit
- L179 _protected member_ `int32 SelectedSuggestion;` — Used to track selected action for keyboard interaction
- L181 _protected member_ `bool bIgnoreUIUpdate;` — Allows us to set selection (via keyboard) without triggering action
- L183 _protected member_ `bool bAutoExpandActionMenu;` — Should we auto-expand categories
- L185 _protected member_ `bool bShowFilterTextBox;` — Should we display the filter text box
- L187 _protected member_ `bool bAlphaSortItems;` — Don't sort items alphabetically
- L189 _protected member_ `bool bSortItemsRecursively;` — If only the top entries should be sorted or subentries as well
- L191 _protected member_ `bool bUseSectionStyling;` — Should the rows and sections be styled like the details panel?
- L193 _protected member_ `bool bAllowPreselectedItemActivation;` — Whether we allow pre-selected items to be activated with a left-click
- L196 _protected member_ `FOnActionSelected OnActionSelected;` — Delegate to call when action is selected
- L198 _protected member_ `FOnActionDoubleClicked OnActionDoubleClicked;` — Delegate to call when action is double clicked
- L200 _protected member_ `FOnActionDragged OnActionDragged;` — Delegate to call when an action is dragged.
- L202 _protected member_ `FOnCategoryDragged OnCategoryDragged;` — Delegate to call when a category is dragged.
- L204 _protected member_ `FOnCreateWidgetForAction OnCreateWidgetForAction;` — Delegate to call to create widget for an action
- L206 _protected member_ `FOnCreateCustomRowExpander OnCreateCustomRowExpander;` — Delegate to call for creating a custom "expander" widget for indenting a menu row with
- L208 _protected member_ `FOnGetActionList OnGetActionList;` — Delegate to call to get a custom action list
- L210 _protected member_ `FOnCollectAllActions OnCollectAllActions;` — Delegate to call to collect all actions
- L212 _protected member_ `FOnCollectStaticSections OnCollectStaticSections;` — Delegate to call to collect all always visible sections
- L214 _protected member_ `FOnCategoryTextCommitted OnCategoryTextCommitted;` — Delegate to call to handle any post-category rename events
- L216 _protected member_ `FCanRenameSelectedAction OnCanRenameSelectedAction;` — Delegate to call to check if a selected action is valid for renaming
- L218 _protected member_ `FGetSectionTitle OnGetSectionTitle;` — Delegate to get the name of a section separator.
- L220 _protected member_ `FGetSectionToolTip OnGetSectionToolTip;` — Delegate to get the tooltip of a section separator.
- L222 _protected member_ `FGetSectionWidget OnGetSectionWidget;` — Delegate to get the widgets of a section separator.
- L224 _protected member_ `FGetFilterText OnGetFilterText;` — Delegate to get the filter text if supplied from an external source
- L226 _protected member_ `FOnActionMatchesName OnActionMatchesName;` — Delegate to check if an action matches a specified name (used for renaming items etc.)
- L230 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& KeyEvent) override;` — SWidget interface
- L234 _public prototype_ `TSharedRef<SEditableTextBox> GetFilterTextBox();` — Get filter text box widget
- L237 _public prototype_ `void GetSelectedActions(TArray< TSharedPtr<FEdGraphSchemaAction> >& OutSelectedActions) const;` — Get action that is currently selected
- L240 _public prototype_ `void OnRequestRenameOnActionNode();` — Initiates a rename on the selected action node, if possible
- L243 _public prototype_ `bool CanRequestRenameOnActionNode() const;` — Queries if a rename on the selected action node is possible
- L246 _public prototype_ `FString GetSelectedCategoryName() const;` — Get category that is currently selected
- L249 _public prototype_ `void GetSelectedCategorySubActions(TArray<TSharedPtr<FEdGraphSchemaAction>>& OutActions) const;` — Get category child actions that is currently selected
- L252 _public prototype_ `void GetCategorySubActions(TWeakPtr<FGraphActionNode> InAction, TArray<TSharedPtr<FEdGraphSchemaAction>>& OutActions) const;` — Get category child actions for the passed in action
- L263 _public prototype_ `bool SelectItemByName(const FName& ItemName, ESelectInfo::Type SelectInfo = ESelectInfo::Direct, int32 SectionId = INDEX_NONE, bool bIsCategory = false);` — Selects an non-creation item in the list, searching by FName, deselects if name is none @param	ItemName		The name of the item to select @param	SelectInfo		The selection type @param	SectionId		If known, the section Id to restrict the selection to, useful in the case of categories where they can exist multiple times @param	bIsCategory		TRUE if the selection is a category, categories obey different rules and it's hard to re-select properly without this knowledge @return					TRUE if the item was successfully selected or the tree cleared, FALSE if unsuccessful
- L266 _public prototype_ `void ExpandCategory(const FText& CategoryName);` — Expands any category with the associated name
- L269 _public prototype_ `bool OnMouseButtonDownEvent(TWeakPtr<FEdGraphSchemaAction> InAction);` — Handler for mouse button going down
- L272 _public prototype_ `void UpdateForNewActions(int32 IdxStart);` — Updates the displayed list starting from IdxStart, useful for async building the display list of actions
- L274 _public prototype_ `void GenerateFilteredItems(bool bPreserveExpansion);` — Regenerated filtered results (FilteredRootAction and FilteredActionNodes) based on filter text
- L277 _public member_ `static FString LastUsedFilterText;` — The last typed action within the graph action menu
- L281 _protected prototype_ `FText GetFilterText() const;` — Get current filter text
- L284 _protected prototype_ `void MarkActiveSuggestion();` — Change the selection to reflect the active suggestion
- L287 _protected prototype_ `bool TryToSpawnActiveSuggestion();` — Try to spawn the node reflected by the active suggestion
- L290 _protected prototype_ `bool ShouldExpandNodes() const;` — Returns true if the tree should be autoexpanded
- L293 _protected prototype_ `bool CanRenameNode(TWeakPtr<FGraphActionNode> InNode) const;` — Checks if the passed in node is safe for renaming
- L298 _protected prototype_ `void OnFilterTextChanged(const FText& InFilterText);` — Called when filter text changes
- L300 _protected prototype_ `void OnFilterTextCommitted(const FText& InText, ETextCommit::Type CommitInfo);` — Called when enter is hit in search box
- L302 _protected prototype_ `void OnGetChildrenForCategory(TSharedPtr<FGraphActionNode> InItem, TArray< TSharedPtr<FGraphActionNode> >& OutChildren);` — Get children
- L304 _protected prototype_ `TSharedRef<ITableRow> MakeWidget(TSharedPtr<FGraphActionNode> InItem, const TSharedRef<STableViewBase>& OwnerTable, bool bIsReadOnly,bool bMakeTiles);` — Create widget for the supplied node
- L306 _protected prototype_ `TSharedRef<ITableRow> GenerateChildForTree(TSharedPtr<FGraphActionNode> InItem, const TSharedRef<STableViewBase>& OwnerTable, bool bIsReadOnly);` — Create the widget for the Child node of the Tree hooked up with treeview
- L308 _protected prototype_ `TSharedRef<ITableRow> GenerateTileForChildItem(TSharedPtr<FGraphActionNode> InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Create the widget for the child of tile view inside the tree's category node, hooked up with tile view of each category node
- L315 _protected prototype_ `void OnItemSelected(TSharedPtr< FGraphActionNode > InSelectedItem, ESelectInfo::Type SelectInfo);` — Called when tree item is selected @param	InSelectedItem	The action node that is being selected @param	SelectInfo		Selection type - Only OnMouseClick and OnKeyPress will trigger a call to HandleSelection
- L322 _protected prototype_ `void OnTileItemSelected(TSharedPtr< FGraphActionNode > InSelectedItem, ESelectInfo::Type SelectInfo);` — Called when Tile view item is selected @param	InSelectedItem	The action node that is being selected @param	SelectInfo		Selection type - Only OnMouseClick and OnKeyPress will trigger a call to HandleSelection
- L324 _protected prototype_ `TArray< TSharedPtr<FGraphActionNode> > GetSelectedItems() const;`
- L332 _protected prototype_ `bool HandleSelection(TSharedPtr< FGraphActionNode >& InSelectedItem, ESelectInfo::Type InSelectionType);` — Executes the selection delegate providing it has been bound, and the provided action node given is valid and is an action node @param InselectedItem	The graph action node selected @return true if item selection delegate was executed
- L335 _protected prototype_ `void OnItemDoubleClicked(TSharedPtr< FGraphActionNode > InClickedItem);` — Called when tree item is double clicked
- L337 _protected prototype_ `FReply OnItemDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — Called when tree item dragged
- L339 _protected prototype_ `void OnNameTextCommitted(const FText& NewText, ETextCommit::Type InTextCommit, TWeakPtr< FGraphActionNode > InAction);` — Callback when rename text is committed
- L341 _protected prototype_ `void OnItemScrolledIntoView(TSharedPtr<FGraphActionNode> InActionNode, const TSharedPtr<ITableRow>& InWidget);` — Handler for when an item has scrolled into view after having been requested to do so
- L343 _protected prototype_ `void OnSetExpansionRecursive(TSharedPtr<FGraphActionNode> InTreeNode, bool bInIsItemExpanded);` — Callback for expanding tree items recursively
- L350 _protected prototype_ `FScoreResults ScoreAndAddActions(int32 StartingIndex = INDEX_NONE);`
- L352 _protected prototype_ `void UpdateActiveSelection(FScoreResults ForResults);` — Helper function to update the active selection after updating the displayed tree
- L355 _private member_ `TArray<UEdGraphPin*> DraggedFromPins;` — The pins that have been dragged off of to prompt the creation of this action menu.
- L358 _private member_ `UEdGraph* GraphObj;` — The graph that this menu is being constructed in
- L360 _private member_ `float FillScale;`
- L362 _private member_ `static const int TileWidth;`
- L364 _private member_ `static const int TileHeight;`

#### struct `STG_ActionMenuTileView::FScoreResults`  
`struct FScoreResults`  
_L345-349_
- desc: Helper function for adding and scoring actions from our builder
- L347 _public member_ `int32 BestMatchIndex;`
- L348 _public member_ `float BestMatchScore;`

#### Free symbols / members of external scopes

- L61 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FOnCreateWidgetForAction, FCreateWidgetForActionData* const);` — Delegate that can be used to create a widget for a particular action
- L63 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SExpanderArrow>, FOnCreateCustomRowExpander, FCustomExpanderData const&);` — Delegate that can be used to create a custom "expander" widget for a particular row
- L65 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnActionSelected, const TArray< TSharedPtr<FEdGraphSchemaAction> >&, ESelectInfo::Type);` — Delegate executed when an action is selected
- L67 _delegate_ `DECLARE_DELEGATE_OneParam(FOnActionDoubleClicked, const TArray< TSharedPtr<FEdGraphSchemaAction> >&);` — Delegate executed when an action is double clicked
- L69 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnActionDragged, const TArray< TSharedPtr<FEdGraphSchemaAction> >&, const FPointerEvent&);` — Delegate executed when an action is dragged
- L71 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnCategoryDragged, const FText&, const FPointerEvent&);` — Delegate executed when a category is dragged
- L73 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCollectAllActions, FGraphActionListBuilderBase&);` — Delegate executed when the list of all actions needs to be refreshed
- L75 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCollectStaticSections, TArray<int32>&) DECLARE_DELEGATE_ThreeParams(FOnCategoryTextCommitted, const FText&, ETextCommit::Type, TWeakPtr< FGraphActionNode >);` — Delegate executed when the list of all actions needs to be refreshed, should return any sections that should always be visible, even if they don't have children.
- L77 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnCategoryTextCommitted, const FText&, ETextCommit::Type, TWeakPtr< FGraphActionNode >);` — Delegate executed when a category is being renamed so any post-rename actions can be handled
- L79 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FCanRenameSelectedAction, TWeakPtr< FGraphActionNode >);` — Delegate executed to check if the selected action is valid for renaming
- L81 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FGetSectionTitle, int32);` — Delegate to get the name of a section if the widget is a section separator.
- L83 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<IToolTip>, FGetSectionToolTip, int32);` — Delegate to get the tooltip of a section if the widget is a section separator.
- L85 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<SWidget>, FGetSectionWidget, TSharedRef<SWidget>, int32);` — Delegate to get the widget that appears on the section bar in the section separator.
- L87 _delegate_ `DECLARE_DELEGATE_RetVal(FText, FGetFilterText);` — Delegate to get the filter text
- L89 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnActionMatchesName, FEdGraphSchemaAction*, const FName&);` — Delegate to check if an action matches a specified name (used for renaming items etc.)
- L91 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedRef<FGraphActionListBuilderBase>, FOnGetActionList);` — Delegate that can be used to create and/or get a custom action list.

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/Widgets/ActionMenuWidgets/STG_GraphActionMenu.h` (Private)


#### class `STG_GraphActionMenu`  
`class STG_GraphActionMenu : public SBorder`  
_L28-79_
- inherits: `SBorder`
- desc: This class implements the customization to the SGraphActionMenu for Texture Graph
- L31 _public function_ `SLATE_BEGIN_ARGS(STG_GraphActionMenu) : _GraphObj(static_cast<UEdGraph*>(NULL)) , _bSpwanOnSelect(true) , _NewNodePosition(FVector2D::ZeroVector) , _AutoExpandActionMenu(false)`
- L38 _public prototype_ `SLATE_ARGUMENT(UEdGraph*, GraphObj) SLATE_ARGUMENT(bool, bSpwanOnSelect) SLATE_ARGUMENT(FVector2D, NewNodePosition) SLATE_ARGUMENT(TArray<UEdGraphPin*>, DraggedFromPins) SLATE_ARGUMENT(SGraphEditor::FActionMenuClosed, OnClosedCallback) SLATE_ARGUMENT(bool, AutoExpandActionMenu) SLATE_EVENT(SGraphActionMenu::FOnActionDragged, OnActionDragged) SLATE_EVENT(SGraphActionMenu::FOnCollectAllActions, OnCollectAllActions) SLATE_EVENT(SGraphActionMenu::FOnCreateWidgetForAction, OnCreateWidgetForAction) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L52 _public prototype_ `~STG_GraphActionMenu();`
- L54 _public prototype_ `TSharedRef<SEditableTextBox> GetFilterTextBox();`
- L55 _public prototype_ `TSharedRef<SWidget> OnCreateWidgetForAction(FCreateWidgetForActionData* const InCreateData);`
- L59 _protected member_ `bool bSpwanOnSelect;` — From Right click menu action is executed when selected
- L61 _protected member_ `FSlateBrush Brush;`
- L63 _protected member_ `UEdGraph* GraphObj;`
- L65 _protected member_ `TArray<UEdGraphPin*> DraggedFromPins;`
- L67 _protected member_ `FDeprecateSlateVector2D NewNodePosition;`
- L69 _protected member_ `bool AutoExpandActionMenu;`
- L71 _protected member_ `SGraphEditor::FActionMenuClosed OnClosedCallback;`
- L73 _protected member_ `TSharedPtr<SGraphActionMenu> GraphActionMenu;`
- L75 _protected prototype_ `void OnActionSelected(const TArray< TSharedPtr<FEdGraphSchemaAction> >& SelectedAction, ESelectInfo::Type InSelectionType);`
- L78 _protected prototype_ `void CollectAllActions(FGraphActionListBuilderBase& OutAllActions);` — Callback used to populate all actions list in SGraphActionMenu

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/Widgets/STG_Blob.h` (Private)


#### class `STG_Blob`  
`class STG_Blob : public SCompoundWidget, public FGCObject`  
_L14-48_
- inherits: `SCompoundWidget,FGCObject`
- L17 _public function_ `SLATE_BEGIN_ARGS(STG_Blob) :_Blob(nullptr) ,_BrushName("Blob") ,_Width(RenderMaterial_Thumbnail::GThumbWidth) ,_Height(RenderMaterial_Thumbnail::GThumbHeight)`
- L24 _public prototype_ `SLATE_ARGUMENT(TiledBlobPtr , Blob) SLATE_ARGUMENT(FName , BrushName) SLATE_ARGUMENT(int , Width) SLATE_ARGUMENT(int, Height) SLATE_END_ARGS() virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L31 _public prototype_ `virtual FString GetReferencerName() const override;`
- L34 _public prototype_ `void Construct(const FArguments& InArgs);` — Constructs this widget with InArgs
- L36 _public prototype_ `void UpdateBlob(BlobPtr InBlob);`
- L37 _public prototype_ `virtual void UpdateParams(BlobPtr InBlob);`
- L38 _public prototype_ `virtual UMaterial* GetMaterial();`
- L39 _public prototype_ `UTexture* GetTextureFromBlob(BlobPtr InBlob);`
- L42 _protected member_ `FName BrushName;`
- L43 _protected member_ `TSharedPtr<FSlateBrush> Brush;`
- L44 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> BrushMaterial = nullptr;`
- L47 _private member_ `FVector2D Position;`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/Widgets/STG_HistogramBlob.h` (Private)


#### enum `ETG_HistogramCurves`  
`enum class ETG_HistogramCurves : uint8`  
_L17-24_
- reflection: `UENUM(BlueprintType)`
- L19 _public enumerator_ `R = 0`
- L20 _public enumerator_ `G`
- L21 _public enumerator_ `B`
- L22 _public enumerator_ `Luma`
- L23 _public enumerator_ `RGB`

#### class `STG_HistogramBlob`  
`class STG_HistogramBlob : public STG_Blob`  
_L26-58_
- inherits: `STG_Blob`
- L29 _public function_ `SLATE_BEGIN_ARGS(STG_HistogramBlob) :_HistogramResult(nullptr) ,_BrushName("HistogramBlob") , _Width(512) , _Height(512) , _Curves(ETG_HistogramCurves::RGB)`
- L37 _public prototype_ `SLATE_ARGUMENT(TiledBlobPtr, HistogramResult) SLATE_ARGUMENT(FName , BrushName) SLATE_ARGUMENT(int, Width) SLATE_ARGUMENT(int, Height) SLATE_ARGUMENT(ETG_HistogramCurves, Curves) SLATE_END_ARGS() virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L45 _public prototype_ `virtual FString GetReferencerName() const override;`
- L47 _public prototype_ `void Construct(const FArguments& InArgs);` — Constructs this widget with InArgs
- L49 _public prototype_ `void Clear();`
- L50 _public prototype_ `virtual void UpdateParams(BlobPtr InBlob) override;`
- L51 _public prototype_ `virtual UMaterial* GetMaterial() override;`
- L53 _public prototype_ `void Update(TiledBlobPtr InHistogramResult);`
- L57 _private member_ `ETG_HistogramCurves Curves;` — TiledBlobPtr HistogramResult;

### `Plugins/TextureGraph/Source/TextureGraphEditor/Private/Widgets/STG_RGBAButtons.h` (Private)


#### enum `ETSChannelButton`  
`enum class ETSChannelButton : uint8`  
_L14-20_
- L16 _public enumerator_ `Red`
- L17 _public enumerator_ `Green`
- L18 _public enumerator_ `Blue`
- L19 _public enumerator_ `Alpha`

#### class `STG_RGBAButtons`  
`class STG_RGBAButtons : public SCompoundWidget`  
_L22-46_
- inherits: `SCompoundWidget`
- L25 _public function_ `SLATE_BEGIN_ARGS(STG_RGBAButtons)`
- L27 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L31 _public function_ `bool GetIsRChannel() const`
- L32 _public function_ `bool GetIsGChannel() const`
- L33 _public function_ `bool GetIsBChannel() const`
- L34 _public function_ `bool GetIsAChannel() const`
- L36 _private member_ `bool bIsRedChannel = true;`
- L37 _private member_ `bool bIsGreenChannel = true;`
- L38 _private member_ `bool bIsBlueChannel = true;`
- L39 _private member_ `bool bIsAlphaChannel = true;`
- L40 _private member_ `FSlateRoundedBoxBrush* CheckedBrush;`
- L42 _private prototype_ `TSharedRef<SWidget> MakeChannelControlWidget();`
- L43 _private prototype_ `TSharedRef<SWidget> CreateChannelWidget(ETSChannelButton Type, FString Name, FText ToolTipText);`
- L44 _private prototype_ `void OnChannelButtonCheckStateChanged(ETSChannelButton Button);`
- L45 _private prototype_ `ECheckBoxState OnGetChannelButtonCheckState(ETSChannelButton Button) const;`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Public/EdGraph/TG_EdGraph.h` (Public)


#### class `UTG_EdGraph`  
`class UTG_EdGraph : public UEdGraph`  
_L21-86_
- reflection: `UCLASS()`
- inherits: `UEdGraph`
- L32 _public prototype_ `void InitializeFromTextureGraph(UTextureGraph* InTextureGraph, TWeakPtr<class FTG_Editor> InTGEditor);` — Initialize the EdGrpah from the model TextureGraph Generate the viewmodel graph matching the source model @param TextureGraph
- L41 _public prototype_ `UTG_EdGraphNode* AddModelNode(UTG_Node* ModelNode, bool bUserInvoked, const FVector2D& Location);` — Add a TG_Node to the Graph and create a EdGraphNode controlling it @param	ModelNode	Ts_Node to be added @return	UTG_EdGraphNode*	Newly created ViewModelNode holding a pointer to ModelNode and representing it in the graph
- L49 _public prototype_ `UTG_EdGraphNode* GetViewModelNode(FTG_Id NodeId);` — Find the TG_EdGraphNode from the FTG_Id representing a TG_Node @param NodeId @return ViewModelNode or nullptr if not found
- L54 _public prototype_ `void RefreshEditorDetails() const;` — Force refresh Editor details
- L61 _public prototype_ `void OnNodeCreateThumbnail(UTG_Node* Node, const FTG_EvaluationContext* EvaluationContext);` — Tells the node to create a thumbnail for its output pins @param Node @param EvaluationContext
- L65 _public member_ `TObjectPtr<UTextureGraph> TextureGraph = nullptr;` — `UPROPERTY()`
- L67 _public member_ `TWeakPtr<FTG_Editor> TGEditor = nullptr;`
- L68 _public member_ `FTG_PinSelectionManager PinSelectionManager;`
- L70 _public prototype_ `void CacheThumbBlob(FTG_Id PinId, TiledBlobPtr InBlob);`
- L71 _public prototype_ `TiledBlobPtr GetCachedThumbBlob(FTG_Id PinId);`
- L75 _private prototype_ `void BuildEdGraphViewmodel();` — Generate the viewmodel matching the Script
- L76 _private prototype_ `bool CreateViewModelLinkFromModelPins(const UTG_Pin* pinFrom, const UTG_Pin* pinTo);`
- L78 _private prototype_ `void OnNodeSignatureChanged(UTG_Node* InNode);`
- L79 _private prototype_ `void OnNodePostEvaluation(UTG_Node* InNode, const FTG_EvaluationContext* Context);`
- L81 _private prototype_ `void GraphChanged(UTG_Graph* InGraph, UTG_Node* InNode, bool Tweaking);`
- L82 _private member_ `TMap<FTG_Id, TiledBlobPtr> PinThumbBlobMap;`
- L85 _public prototype_ `void FixDuplicatedNodesPinConnections(TSet<UEdGraphNode*>& PastedNodes);`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Public/EdGraph/TG_EdGraphNode.h` (Public)


#### class `UTG_EdGraphNode`  
`class UTG_EdGraphNode : public UEdGraphNode`  
_L31-120_
- reflection: `UCLASS()`
- inherits: `UEdGraphNode`
- L37 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnTSEditorGraphNodeChanged);`
- L38 _public member_ `FOnTSEditorGraphNodeChanged OnNodeReconstructDelegate;`
- L39 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNodePostEvaluateDelegate, const FTG_EvaluationContext*) FOnNodePostEvaluateDelegate OnNodePostEvaluateDelegate;`
- L41 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPinSelectionChangeDelegate, UEdGraphPin*) FOnPinSelectionChangeDelegate OnPinSelectionChangeDelegate;`
- L44 _public prototype_ `void Construct(UTG_Node* InNode);`
- L47 _public prototype_ `void BeginDestroy() override;`
- L48 _public prototype_ `void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L54 _public prototype_ `FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L55 _public prototype_ `virtual void OnRenameNode(const FString& NewName) override;`
- L56 _public prototype_ `void GetNodeContextMenuActions(UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;`
- L57 _public prototype_ `FLinearColor GetNodeTitleColor() const override;`
- L58 _public prototype_ `FLinearColor GetNodeBodyTintColor() const;`
- L59 _public prototype_ `void AllocateDefaultPins() override;`
- L60 _public prototype_ `FName GetPinCategory(UTG_Pin* Pin, TWeakObjectPtr<UObject>& PinSubCategoryObject);`
- L61 _public prototype_ `bool CanUserDeleteNode() const override;`
- L62 _public prototype_ `void PrepareForCopying() override;`
- L63 _public prototype_ `void PostCopyNode();`
- L64 _public prototype_ `virtual void PostPasteNode() override;`
- L67 _public prototype_ `void UpdatePinVisibility(UEdGraphPin* Pin, UTG_Pin* TGPin) const;`
- L68 _public prototype_ `void UpdateInputPinsVisibility() const;`
- L69 _public prototype_ `void UpdatePinsEditCondition() const;`
- L73 _public prototype_ `virtual void PinDefaultValueChangedWithTweaking(UEdGraphPin* Pin, bool bIsTweaking);` — Called when the DefaultValue of one of the pins of this node is changed in the editor
- L74 _public prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L75 _public prototype_ `virtual void AutowireNewNode(UEdGraphPin* FromPin) override;`
- L78 _public prototype_ `virtual void ReconstructNode() override;`
- L79 _public prototype_ `virtual FString GetTitleDetail();`
- L80 _public prototype_ `void OnNodeChanged(UTG_Node* InNode);`
- L82 _public function_ `UTG_Node* GetNode() const`
- L83 _public prototype_ `virtual FText GetTooltipText() const override;`
- L86 _public prototype_ `UObject* GetDetailsObject();`
- L91 _public prototype_ `void SelectPin(UEdGraphPin* Pin, bool IsSelected);` — Sets the selected pin for Node
- L93 _public prototype_ `const UEdGraphPin* GetSelectedPin() const;`
- L96 _public prototype_ `TArray<UEdGraphPin*> GetOutputPins() const;`
- L97 _public prototype_ `TArray<UEdGraphPin*> GetTextureOutputPins() const;`
- L103 _protected prototype_ `void UpdatePosition();` — Copy the edNode position to the model node
- L105 _protected prototype_ `void OnNodePostEvaluate(const FTG_EvaluationContext* Fts_EvaluationContext);`
- L106 _protected prototype_ `bool UpdateEdPinDefaultValue(UEdGraphPin* EdPin, const UTG_EdGraphSchema* Schema);`
- L107 _protected prototype_ `void UpdatePinsAndReconstructNode();`
- L109 _protected prototype_ `void OnUpdateCommentText(const FString& NewComment) override;`
- L110 _protected prototype_ `void OnCommentBubbleToggled(bool bInCommentBubbleVisible) override;`
- L111 _protected prototype_ `void UpdateCommentBubblePinned();`
- L112 _protected prototype_ `FLinearColor GetTitleColor() const;`
- L113 _protected prototype_ `float GetNodeAlpha() const;`
- L116 _protected member_ `TObjectPtr<UTG_Node> Node;` — `UPROPERTY()` — /  Model TS Node this Editor graph node is representing
- L119 _private member_ `UEdGraphPin* SelectedPin = nullptr;`

#### Free symbols / members of external scopes

- L37 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnTSEditorGraphNodeChanged);`
- L39 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNodePostEvaluateDelegate, const FTG_EvaluationContext*) FOnNodePostEvaluateDelegate OnNodePostEvaluateDelegate;`
- L41 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPinSelectionChangeDelegate, UEdGraphPin*) FOnPinSelectionChangeDelegate OnPinSelectionChangeDelegate;`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Public/EdGraph/TG_EditorGraphNodeFactory.h` (Public)


#### class `FTG_EditorGraphNodeFactory`  
`class FTG_EditorGraphNodeFactory : public FGraphPanelNodeFactory`  
_L10-13_
- inherits: `FGraphPanelNodeFactory`
- L12 _private prototype_ `virtual TSharedPtr<SGraphNode> CreateNode(UEdGraphNode* InNode) const override;`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Public/EdGraph/TG_EditorGraphPanelPinFactory.h` (Public)


#### class `FTG_EditorGraphPanelPinFactory`  
`class FTG_EditorGraphPanelPinFactory : public FGraphPanelPinFactory`  
_L9-19_
- inherits: `FGraphPanelPinFactory`
- L14 _public prototype_ `virtual TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* InPin) const override;` — FGraphPanelPinFactory interface
- L17 _private prototype_ `TSharedPtr<class SGraphPin> CreateEnumPin(class UEdGraphPin* InPin) const;`
- L18 _private prototype_ `TSharedPtr<SWidget> FindWidgetInChildren(TSharedPtr<SWidget> Parent, FName ChildType) const;`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Public/EdGraph/TG_PinSelectionManager.h` (Public)


#### class `FTG_PinSelectionManager`  
`class FTG_PinSelectionManager : public FGCObject`  
_L20-35_
- inherits: `FGCObject`
- L23 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L24 _public function_ `virtual FString GetReferencerName() const override`
- L29 _public prototype_ `void UpdateSelection(UEdGraphPin* Pin);`
- L31 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPinSelectionUpdated, UEdGraphPin* ) FOnPinSelectionUpdated OnPinSelectionUpdated;`

#### Free symbols / members of external scopes

- L31 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPinSelectionUpdated, UEdGraphPin* ) FOnPinSelectionUpdated OnPinSelectionUpdated;`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Public/ITG_Editor.h` (Public)


#### class `ITG_Editor`  
`class ITG_Editor : public FAssetEditorToolkit`  
_L14-60_
- inherits: `FAssetEditorToolkit`
- desc: Public interface to TS Editor
- L20 _protected prototype_ `virtual void RefreshViewport() = 0;` — Refreshes the TS Editor's viewport.
- L25 _protected prototype_ `virtual void RefreshTool() = 0;` — Refreshes everything in the TS Editor.
- L40 _public function_ `virtual UTG_Expression* CreateNewExpression(UClass* NewExpressionClass, const FVector2D& NodePos, bool bAutoSelect, bool bAutoAssignResource, const class UEdGraph* Graph = nullptr)` — Creates a new material expression of the specified class. @param	NewExpressionClass		The type of mix expression to add.  Must be a child of UTG_Expression. @param	NodePos					Position of the new node. @param	bAutoSelect				If true, deselect all expressions and select the newly created one. @param	bAutoAssignResource		If true, assign resources to new expression. @param	Graph            		Graph to create new expression within. @return	UMaterialExpression*	Newly created material expression
- L46 _public function_ `virtual FText GetOriginalObjectName() const` — Gets the name of the mix name that we are editing
- L51 _public function_ `virtual TSharedPtr<IAssetReferenceFilter> MakeAssetReferenceFilter() const` — Creates an IAssetReferenceFilter that can be used to check if an asset is valid to be used with this texture graph.
- L54 _public prototype_ `virtual class UMixInterface* GetTextureGraphInterface() const = 0;` — Gets the TextureGraph edited
- L59 _public prototype_ `virtual void SetMesh(class UMeshComponent* PreviewMesh, class UWorld* World) = 0;` — This mesh will be used to display the rendering

### `Plugins/TextureGraph/Source/TextureGraphEditor/Public/STextureHistogram.h` (Public)


#### enum `ETextureHistogramStyle`  
`enum class ETextureHistogramStyle : uint8`  
_L15-22_
- reflection: `UENUM(BlueprintType)`
- L18 _public enumerator_ `Bar = 0` — Draw the histogram in descrete bar shape
- L21 _public enumerator_ `Curve` — Draw the histogram in continous line curve shader

#### enum `ETextureHistogramLayout`  
`enum class ETextureHistogramLayout : uint8`  
_L25-32_
- reflection: `UENUM(BlueprintType)`
- L28 _public enumerator_ `Combined = 0` — Draw RGBA curves in histogram in one graph
- L31 _public enumerator_ `Split` — Draw RGBA curves in histogram in vertically seperated graphs

#### struct `TextureHistogramUtils`  
`struct TextureHistogramUtils`  
_L34-45_
- L37 _public member_ `inline static const FLinearColor LinearGray = FLinearColor(0.047f, 0.047f, 0.047f, 1);`
- L38 _public member_ `inline static const FLinearColor LinearRed = FLinearColor(1.0f, 0.0f, 0.0f, 0.4f);`
- L39 _public member_ `inline static const FLinearColor LinearGreen = FLinearColor(0.0f, 1.0f, 0.0f, 0.4f);`
- L40 _public member_ `inline static const FLinearColor LinearBlue = FLinearColor(0.0f, 0.0f, 1.0f, 0.4f);`
- L41 _public member_ `inline static const FLinearColor LinearWhite = FLinearColor(1.0f, 1.0f, 1.0f, 0.4f);`
- L43 _public member_ `inline static const float UniformMargin = 15.0f;`
- L44 _public member_ `inline static const FMargin Margin = FMargin(35, 10, 25, 35);`

#### class `STextureHistogram`  
`class STextureHistogram : public SCompoundWidget`  
_L54-123_
- inherits: `SCompoundWidget`
- desc: Texture Histogram widget used to draw the histogram of a texture Require data in an TArray of FVector4
- L57 _public function_ `SLATE_BEGIN_ARGS(STextureHistogram) : _NumBins(256), _NumVerticalScaleLines(3), _NumHorizontalScaleLines(8), _bDrawScaleLines(true), _bDrawBackground(true), _ScaleLineColor(TextureHistogramUtils::LinearWhite), _RCurveColor(TextureHistogramUtils::LinearRed), _GCurveColor(TextureHistogramUtils::LinearGreen), _BCurveColor(TextureHistogramUtils::LinearBlue), _ACurveColor(TextureHistogramUtils::LinearWhite), _DrawLayout(ETextureHistogramLayout::Split), _DrawStyle(ETextureHistogramStyle::Curve), _Height(20.0)`
- L72 _public prototype_ `SLATE_ARGUMENT(int32, NumBins) SLATE_ARGUMENT(int, NumVerticalScaleLines) SLATE_ARGUMENT(int, NumHorizontalScaleLines) SLATE_ARGUMENT(bool, bDrawScaleLines) SLATE_ARGUMENT(bool, bDrawBackground) SLATE_ARGUMENT(FLinearColor, ScaleLineColor) SLATE_ARGUMENT(FLinearColor, RCurveColor) SLATE_ARGUMENT(FLinearColor, GCurveColor) SLATE_ARGUMENT(FLinearColor, BCurveColor) SLATE_ARGUMENT(FLinearColor, ACurveColor) SLATE_ARGUMENT(ETextureHistogramLayout, DrawLayout) SLATE_ARGUMENT(ETextureHistogramStyle, DrawStyle) SLATE_ARGUMENT(float, Height) SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L88 _public prototype_ `void SetHistogramData(TArray<FVector4> InHistogramData);`
- L92 _private prototype_ `void DrawCombineHistogramCurves(const FArguments& InArgs);`
- L93 _private prototype_ `void DrawSplitHistogramCurves(const FArguments& InArgs);`
- L94 _private prototype_ `void AddCurveWidget(const FArguments& InArgs,TSharedRef<SWidget> ReferenceLineWidget, TSharedRef<SWidget> CurveWidget);`
- L95 _private prototype_ `void DrawCombineBarHistogram(const FArguments& InArgs);`
- L96 _private prototype_ `void DrawSplitBarHistogram(const FArguments& InArgs);`
- L98 _private prototype_ `int GetMaxBin();`
- L99 _private prototype_ `TArray<int32> GetRValues() const;`
- L100 _private prototype_ `TArray<int32> GetGValues() const;`
- L101 _private prototype_ `TArray<int32> GetBValues() const;`
- L102 _private prototype_ `TArray<int32> GetLuminanceValues() const;`
- L104 _private member_ `bool bDrawCombined;`
- L105 _private member_ `bool bDrawBars;`
- L106 _private member_ `TArray<FVector4> HistogramData;`
- L107 _private member_ `TSharedPtr<SVerticalBox> SplitBox;`
- L108 _private member_ `TSharedPtr<STextureHistogramCurve> HistogramCurveR;`
- L109 _private member_ `TSharedPtr<STextureHistogramCurve> HistogramCurveG;`
- L110 _private member_ `TSharedPtr<STextureHistogramCurve> HistogramCurveB;`
- L111 _private member_ `TSharedPtr<STextureHistogramCurve> HistogramCurveA;`
- L113 _private member_ `TSharedPtr<STextureHistogramBars> HistogramBarsR;`
- L114 _private member_ `TSharedPtr<STextureHistogramBars> HistogramBarsG;`
- L115 _private member_ `TSharedPtr<STextureHistogramBars> HistogramBarsB;`
- L116 _private member_ `TSharedPtr<STextureHistogramBars> HistogramBarsA;`
- L118 _private member_ `TSharedPtr<STextureHistogramReferenceLines> ReferenceLinesR;`
- L119 _private member_ `TSharedPtr<STextureHistogramReferenceLines> ReferenceLinesG;`
- L120 _private member_ `TSharedPtr<STextureHistogramReferenceLines> ReferenceLinesB;`
- L121 _private member_ `TSharedPtr<STextureHistogramReferenceLines> ReferenceLinesA;`
- L122 _private member_ `TSharedPtr<STextureHistogramReferenceLines> ReferenceLinesCombine;`

#### class `STextureHistogramCurve`  
`class STextureHistogramCurve : public SCompoundWidget`  
_L126-157_
- inherits: `SCompoundWidget`
- desc: Widget to Draw the Curve Style Histogram
- L129 _public function_ `SLATE_BEGIN_ARGS(STextureHistogramCurve): _bShadeCurve(true), _LineColor(FLinearColor::Red), _Height(20.0)`
- L134 _public prototype_ `SLATE_ARGUMENT(bool, bShadeCurve) SLATE_ARGUMENT(FLinearColor, LineColor) SLATE_ARGUMENT(float, Height) SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L140 _public prototype_ `void SetHistogramData(const TArray<int32>& InHistogramData);`
- L141 _public function_ `void SetMax(int MaxValue)`
- L143 _public prototype_ `int GetMaxBin();`
- L145 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L146 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L147 _public prototype_ `void DrawHistogramCurve(const FGeometry& AllottedGeometry, FSlateWindowElementList& ElementList, int32 LayerId, TArray<int32> Values) const;`
- L148 _public prototype_ `void DrawShadeForCurve(const FGeometry& AllottedGeometry, FSlateWindowElementList& ElementList, int32 LayerId, TArray<FVector2D> ShadePoints) const;`
- L151 _private member_ `int Max;`
- L152 _private member_ `bool bShadeCurve;`
- L153 _private member_ `FLinearColor LineColor;`
- L154 _private member_ `FColor ShadeColor;`
- L155 _private member_ `TArray<int32> HistogramData;`
- L156 _private member_ `TSharedPtr<SCanvas> Canvas;`

#### class `STextureHistogramBars`  
`class STextureHistogramBars : public SCompoundWidget`  
_L160-185_
- inherits: `SCompoundWidget`
- desc: Widget to Draw the Bars for Histogram
- L163 _public function_ `SLATE_BEGIN_ARGS(STextureHistogramBars) : _ShadeColor(FLinearColor::Red), _Height(20.0)`
- L167 _public prototype_ `SLATE_ARGUMENT(FLinearColor, ShadeColor) SLATE_ARGUMENT(float, Height) SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L172 _public prototype_ `void SetHistogramData(const TArray<int32>& InHistogramData);`
- L173 _public function_ `void SetMax(int MaxValue)`
- L174 _public prototype_ `int GetMaxBin();`
- L176 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L177 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L178 _public prototype_ `void DrawHistogramBars(const FGeometry& AllottedGeometry, FSlateWindowElementList& ElementList, int32 LayerId, TArray<int32> Values, FLinearColor BarColor) const;`
- L181 _private member_ `int Max;`
- L182 _private member_ `FLinearColor ShadeColor;`
- L183 _private member_ `TArray<int32> HistogramData;`
- L184 _private member_ `TSharedPtr<SCanvas> Canvas;`

#### class `STextureHistogramReferenceLines`  
`class STextureHistogramReferenceLines : public SCompoundWidget`  
_L188-228_
- inherits: `SCompoundWidget`
- desc: Widget to Draw the Reference Lines for Histogram
- L191 _public function_ `SLATE_BEGIN_ARGS(STextureHistogramReferenceLines) : _Color(FLinearColor::White), _NumBins(256), _NumVerticalScaleLines(3), _NumHorizontalScaleLines(8), _bDraw(true), _bDrawBackground(true), _Height(20.0), _Label("Histogram")`
- L201 _public prototype_ `SLATE_ARGUMENT(FLinearColor, Color) SLATE_ARGUMENT(int32, NumBins) SLATE_ARGUMENT(int, NumVerticalScaleLines) SLATE_ARGUMENT(int, NumHorizontalScaleLines) SLATE_ARGUMENT(bool, bDraw) SLATE_ARGUMENT(bool, bDrawBackground) SLATE_ARGUMENT(float, Height) SLATE_ARGUMENT(FString, Label) SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L212 _public function_ `void SetMax(int MaxValue)`
- L214 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L215 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L216 _public prototype_ `void DrawReferenceLines(const FGeometry& AllottedGeometry, FSlateWindowElementList& ElementList, int32 LayerId) const;`
- L219 _private member_ `int Max;`
- L220 _private member_ `int32 NumBins;`
- L221 _private member_ `int NumVerticalScaleLines;`
- L222 _private member_ `int NumHorizontalScaleLines;`
- L223 _private member_ `bool bDraw;`
- L224 _private member_ `bool bDrawBackground;`
- L225 _private member_ `FString Label;`
- L226 _private member_ `FLinearColor Color;`
- L227 _private member_ `TSharedPtr<SCanvas> Canvas;`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Public/TG_Exporter.h` (Public)


#### struct `FTG_ExporterUtility`  
`struct FTG_ExporterUtility`  
_L16-43_
- L19 _public prototype_ `FTG_ExporterUtility();` — Initializes the global state of the exporter (commands, tab spawners, etc):
- L20 _public prototype_ `void Cleanup();`
- L23 _public prototype_ `~FTG_ExporterUtility();` — Destructor declaration purely so that we can pimpl:
- L26 _public prototype_ `void SetTextureGraphToExport(UTextureGraphBase* InTextureGraph);` — Sets the current texture graph to be used with the exporter
- L29 _public prototype_ `TSharedRef<SDockTab> CreateTGExporterTab(const FSpawnTabArgs& Args);` — Function registered with tab manager to create the Texture Graph Exporter
- L33 _private member_ `TUniquePtr<struct FTG_InstanceImpl> Impl;`
- L34 _private member_ `TObjectPtr<UTextureGraphInstance> TextureGraphInstance;`
- L35 _private member_ `TSharedPtr<FTabManager> TGExporterTabManager;`
- L36 _private member_ `TSharedPtr<FTabManager::FLayout> TGExporterLayout;`
- L39 _private prototype_ `FTG_ExporterUtility(const FTG_ExporterUtility&);` — prevent copying:
- L40 _private prototype_ `FTG_ExporterUtility(FTG_ExporterUtility&&);`
- L41 _private prototype_ `FTG_ExporterUtility& operator=(FTG_ExporterUtility const&);`
- L42 _private prototype_ `FTG_ExporterUtility& operator=(FTG_ExporterUtility&&);`

#### struct `FTG_ExporterCommands`  
`struct FTG_ExporterCommands : public TCommands<FTG_ExporterCommands>`  
_L46-69_
- inherits: `TCommands<FTG_ExporterCommands>`
- L48 _public function_ `FTG_ExporterCommands() : TCommands<FTG_ExporterCommands>( TEXT("TextureGraphExporter"),`
- L59 _public prototype_ `virtual void RegisterCommands() override;` — TCommand<> interface
- L62 _public member_ `TSharedPtr<FUICommandInfo> ShowOutputPreview;`
- L63 _public member_ `TSharedPtr<FUICommandInfo> Show3DPreview;`
- L64 _public member_ `TSharedPtr<FUICommandInfo> Show3DPreviewSettings;`
- L65 _public member_ `TSharedPtr<FUICommandInfo> ShowParameters;`
- L66 _public member_ `TSharedPtr<FUICommandInfo> ShowExportSettings;`
- L67 _public member_ `TSharedPtr<FUICommandInfo> ShowDetails;`

#### struct `FTG_InstanceImpl`  
`struct FTG_InstanceImpl: public FTickableGameObject, public FGCObject, public FNotifyHook`  
_L73-178_
- inherits: `FTickableGameObject,FGCObject,FNotifyHook`
- L79 _public prototype_ `FTG_InstanceImpl();`
- L82 _public prototype_ `void Cleanup(bool bFlushMixInvalidations = true);`
- L84 _public prototype_ `void SetTextureGraphToExport(UTextureGraphInstance* InTextureGraph, bool bClearPreviousMixInvalidations);` — Sets the Texture Graph to be exported in the Exporter
- L85 _public prototype_ `void OnGraphChanged(UTG_Graph* InGraph, UTG_Node* InNode, bool Tweaking);`
- L86 _public prototype_ `TSharedRef<FTabManager::FLayout> GetDefaultLayout();`
- L87 _public prototype_ `void Initialize();`
- L88 _public prototype_ `void RegisterTabSpawners(const TSharedPtr<FTabManager>);`
- L89 _public prototype_ `void UnregisterTabSpawners(const TSharedPtr<FTabManager>);`
- L90 _public prototype_ `void SetMesh(class UMeshComponent* InPreviewMesh, class UWorld* InWorld);`
- L91 _public prototype_ `void SetViewportPreviewMesh();`
- L92 _public prototype_ `void UpdatePreviewMesh();`
- L93 _public prototype_ `void CleanupSlateReferences();`
- L96 _private member_ `TObjectPtr<UTextureGraphInstance> TextureGraphInstance;`
- L97 _private member_ `TWeakPtr<class STG_NodePreviewWidget> NodePreviewPtr;`
- L99 _private member_ `TSharedPtr<class IDetailsView> DetailsView;`
- L100 _private member_ `TSharedPtr<class IDetailsView> ParametersView;`
- L101 _private member_ `TSharedPtr<class IDetailsView> ExportSettingsView;`
- L102 _private member_ `TSharedPtr<class IDetailsView> PreviewSettingsView;`
- L103 _private member_ `TSharedPtr<class IDetailsView> PreviewSceneSettingsView;`
- L106 _private member_ `TSharedPtr<SWidget> AdvancedPreviewSettingsWidget;` — Scene preview settings widget
- L108 _private member_ `TWeakPtr<SDockTab> PreviewSceneSettingsDockTab;`
- L110 _private member_ `FAdvancedPreviewSceneModule::FOnPreviewSceneChanged OnPreviewSceneChangedDelegate;`
- L113 _private member_ `TSharedPtr<class FEditorViewportTabContent> ViewportTabContent;` — Tracking the active viewports in this editor.
- L115 _private member_ `TObjectPtr<class UTG_Parameters> Parameters;`
- L116 _private member_ `TObjectPtr<class UTG_ExportSettings> ExportSettings;`
- L117 _private member_ `TSharedPtr<class FExportSettings> TargetExportSettings;`
- L119 _private member_ `TArray<TSharedPtr<FName>> OutputNodesList;`
- L120 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FName>>> OutputNodesComboBoxWidget;`
- L121 _private member_ `UTG_Node* SelectedNode = nullptr;`
- L123 _private prototype_ `virtual void Tick(float DeltaTime) override;` — Inherited via FTickableGameObject
- L125 _private function_ `virtual ETickableTickType GetTickableTickType() const override`
- L127 _private function_ `virtual bool IsTickableWhenPaused() const override`
- L129 _private function_ `virtual bool IsTickableInEditor() const override`
- L131 _private prototype_ `virtual TStatId GetStatId() const override;`
- L134 _private prototype_ `virtual void NotifyPostChange( const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged ) override;` — Post edit change notify for properties.
- L137 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — Inherited via FGCObject
- L138 _private function_ `virtual FString GetReferencerName() const override`
- L143 _private prototype_ `void BuildSubTools();` — Builds the sub-tools that are a part of the texture graph editor.
- L146 _private prototype_ `void OnEditorLayoutChanged();` — Called when the Viewport Layout has changed.
- L148 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args);`
- L149 _private prototype_ `TSharedRef<SDockTab> SpawnTab_ParameterDefaults(const FSpawnTabArgs& Args);`
- L150 _private prototype_ `TSharedRef<SDockTab> SpawnTab_NodePreview(const FSpawnTabArgs& Args);`
- L151 _private prototype_ `TSharedRef<SDockTab> SpawnTab_ExportSettings(const FSpawnTabArgs& Args);`
- L152 _private prototype_ `TSharedRef<SDockTab> SpawnTab_TG_Properties(const FSpawnTabArgs& Args);`
- L153 _private prototype_ `TSharedRef<SDockTab> SpawnTab_PreviewSettings(const FSpawnTabArgs& Args);`
- L154 _private prototype_ `TSharedRef<SDockTab> SpawnTab_PreviewSceneSettings(const FSpawnTabArgs& Args);`
- L155 _private prototype_ `TSharedPtr<class STG_EditorViewport> GetEditorViewport() const;`
- L157 _private prototype_ `bool SetPreviewAsset(UObject* InAsset);`
- L158 _private function_ `TSharedRef<class IDetailsView> GetDetailsView() const`
- L159 _private function_ `TSharedRef<class IDetailsView> GetPreviewSettingsView() const`
- L160 _private function_ `TSharedRef<class IDetailsView> GetPreviewSceneSettingsView() const`
- L161 _private function_ `TSharedRef<class IDetailsView> GetExportSettingsView() const`
- L162 _private function_ `TSharedRef<class IDetailsView> GetParametersView() const`
- L163 _private prototype_ `void OnViewportMaterialChanged();`
- L164 _private prototype_ `void OnMaterialMappingChanged();`
- L165 _private prototype_ `void UpdateExportSettingsUI();`
- L166 _private prototype_ `void UpdateParametersUI();`
- L167 _private prototype_ `virtual void RefreshViewport();`
- L168 _private prototype_ `void OnRenderingDone(class UMixInterface* TextureGraph, const struct FInvalidationDetails* Details);`
- L169 _private prototype_ `TSharedRef<SWidget> GenerateOutputComboItem(TSharedPtr<FName> String);`
- L170 _private prototype_ `void OnOutputSelectionChanged(TSharedPtr<FName> String, ESelectInfo::Type Arg);`
- L171 _private prototype_ `FReply OnExportClicked(EAppReturnType::Type ButtonID);`
- L174 _private prototype_ `FTG_InstanceImpl(const FTG_InstanceImpl&);` — prevent copying:
- L175 _private prototype_ `FTG_InstanceImpl(FTG_InstanceImpl&&);`
- L176 _private prototype_ `FTG_InstanceImpl& operator=(FTG_InstanceImpl const&);`
- L177 _private prototype_ `FTG_InstanceImpl& operator=(FTG_InstanceImpl&&);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define LOCTEXT_NAMESPACE "TextureGraphExporter"`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Public/TG_Parameter.h` (Public)


#### struct `FTG_ParameterInfo`  
`struct FTG_ParameterInfo`  
_L15-21_
- reflection: `USTRUCT()`
- L19 _public member_ `FTG_Id Id;`
- L20 _public member_ `FName Name;`

#### class `UTG_Parameters`  
`class UTG_Parameters : public UObject`  
_L24-33_
- reflection: `UCLASS()`
- inherits: `UObject`
- L29 _public member_ `TArray<FTG_ParameterInfo> Parameters;` — `UPROPERTY(EditAnywhere, EditFixedSize, Category = "TextureGraph", meta=(EditFixedOrder, ShowOnlyInnerProperties))`
- L31 _public member_ `TObjectPtr<class UTG_Graph> TextureGraph;`

### `Plugins/TextureGraph/Source/TextureGraphEditor/Public/TextureGraphEditorModule.h` (Public)


#### class `FTextureGraphEditorModule`  
`class FTextureGraphEditorModule : public IModuleInterface`  
_L21-51_
- inherits: `IModuleInterface`
- L25 _private member_ `AssetTypeActionsArray CreatedAssetTypeActions;` — All created asset type actions.  Cached here so that we can unregister them during shutdown.
- L27 _private member_ `FTickerDelegate TickDelegate;` — Delegate to run the Tick method in charge of running TextureGraphEngine update
- L29 _private member_ `FTSTicker::FDelegateHandle TickDelegateHandle;` — Handle of the delegate to run the Tick method in charge of running TextureGraphEngine update
- L30 _private member_ `TUniquePtr<FTG_ExporterUtility> TG_Exporter;`
- L33 _protected member_ `TSharedPtr<FTG_EditorGraphNodeFactory> GraphNodeFactory;`
- L34 _protected member_ `TSharedPtr<FTG_EditorGraphPanelPinFactory> GraphPanelPinFactory;`
- L37 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L38 _public prototype_ `virtual void ShutdownModule() override;`
- L41 _public prototype_ `virtual void StartTextureGraphEngine();`
- L42 _public prototype_ `virtual void ShutdownTextureGraphEngine();`
- L43 _public prototype_ `bool Tick(float deltaTime);`
- L44 _public prototype_ `void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action);`
- L45 _public prototype_ `void UnRegisterAllAssetTypeActions();`
- L46 _public prototype_ `static TSharedRef<ITG_Editor> CreateTextureGraphEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UTextureGraph* InTextureGraph);`
- L47 _public prototype_ `static TSharedRef<ITG_Editor> CreateTextureGraphInstanceEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UTextureGraphInstance* InTextureGraphInstance);`
- L50 _public function_ `const TUniquePtr<FTG_ExporterUtility>& GetTextureExporter() const` — Returns a reference to the Blueprint Debugger state object

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TEXTUREGRAPHEDITOR_API`
- L17 _typedef_ `typedef TArray<TSharedPtr<IAssetTypeActions>> AssetTypeActionsArray;`
- L18 _externvar_ `extern const FName TG_EditorAppIdentifier;`
- L19 _externvar_ `extern const FName TG_InstanceEditorAppIdentifier;`
