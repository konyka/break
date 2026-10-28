# Editor / StructUtilsEditor

- module root: `Source/Editor/StructUtilsEditor`
- headers: 18; symbols: 549
- symbol kinds: class=32, delegate=6, enum=4, enumerator=36, externvar=25, function=48, macro=8, member=124, namespace=17, prototype=233, struct=14, typedef=2
- PrivateDependencyModuleNames: AIGraph, ApplicationCore, BlueprintGraph, GraphEditor, KismetCompiler, KismetWidgets, PropertyEditor, RenderCore, ToolMenus
- PublicDependencyModuleNames: AIModule, AssetTools, ComponentVisualizers, Core, CoreUObject, DataHierarchyEditor, DetailCustomizations, Engine, InputCore, PropertyEditor, Slate, SlateCore, UnrealEd

### `Source/Editor/StructUtilsEditor/Private/Customizations/SDraggableBox.h` (Private)


#### class `StructUtilsEditor::SDraggableBox`  
`class SDraggableBox : public SCompoundWidget`  
_L11-31_
- inherits: `SCompoundWidget`
- L14 _public function_ `SLATE_BEGIN_ARGS(SDraggableBox)`
- L15 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_ARGUMENT(TSharedPtr<IDetailDragDropHandler>, DragDropHandler) SLATE_ARGUMENT(bool, RequireDirectHover) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L23 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L24 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L25 _public prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L29 _protected member_ `TSharedPtr<IDetailDragDropHandler> DragDropHandler = nullptr;`
- L30 _protected member_ `bool bRequireDirectHover = true;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace StructUtilsEditor`

### `Source/Editor/StructUtilsEditor/Private/Customizations/STypeSelector.h` (Private)


#### class `STypeSelector`  
`class STypeSelector final : public SPinTypeSelector`  
_L20-61_
- inherits: `SPinTypeSelector`
- desc: This widget is a small wrapper around SPinTypeSelector to allow for a right click context menu on the selector pill for the container type so that it can all fit into one compact combo button. Eventually (TODO), it should be replaced by a base combo button drop down that supports right clicks as well as an update to the original SPinTypeSelector to support this for Compact Selector Type (rather than toggling). However, this will require updates to core widgets, which are currently hardcoded for left click only. Ex. 'SDoubleComboButton' (SComboButton) which inherits from 'SDoubleMenuAnchor' (SMenuAnchor) or similar with two menu anchors.
- L24 _public function_ `SLATE_BEGIN_ARGS(STypeSelector) : _Schema(nullptr) , _SchemaAction(nullptr) , _TypeTreeFilter(ETypeTreeFilter::None) , _bAllowContainers(true) , _TreeViewWidth(300.f) , _TreeViewHeight(350.f) , _Font(FAppStyle::GetFontStyle(TEXT("NormalFont"))) , _SelectorType(ESelectorType::Full) , _ReadOnly(false)` — Replicated arguments of SPinTypeSelector
- L35 _public prototype_ `SLATE_ATTRIBUTE(FEdGraphPinType, TargetPinType) SLATE_ARGUMENT(const UEdGraphSchema*, Schema) SLATE_ARGUMENT(TWeakPtr<const FEdGraphSchemaAction>, SchemaAction) SLATE_ARGUMENT(ETypeTreeFilter, TypeTreeFilter) SLATE_ARGUMENT(bool, bAllowContainers) SLATE_ATTRIBUTE(FOptionalSize, TreeViewWidth) SLATE_ATTRIBUTE(FOptionalSize, TreeViewHeight) SLATE_EVENT(FOnPinTypeChanged, OnPinTypePreChanged) SLATE_EVENT(FOnPinTypeChanged, OnPinTypeChanged) SLATE_ATTRIBUTE(FSlateFontInfo, Font) SLATE_ARGUMENT(ESelectorType, SelectorType) SLATE_ATTRIBUTE(bool, ReadOnly) SLATE_ARGUMENT(TArray<TSharedPtr<class IPinTypeSelectorFilter>>, CustomFilters) SLATE_END_ARGS() void Construct(const FArguments& InArgs, FGetPinTypeTree GetPinTypeTreeFunc);`
- L53 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — SWidget interface
- L54 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L57 _public prototype_ `virtual TSharedRef<SWidget> GetMenuContent(bool bForSecondaryType) override;`
- L60 _private prototype_ `FText GetToolTipForSelector() const;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API STRUCTUTILSEDITOR_API`

### `Source/Editor/StructUtilsEditor/Private/HierarchyEditor/SPropertyBagHierarchyEditor.h` (Private)


#### class `SPropertyBagHierarchyEditor`  
`class SPropertyBagHierarchyEditor : public SCompoundWidget`  
_L22-55_
- inherits: `SCompoundWidget`
- desc: A wrapper around the actual hierarchy editor. Receives and holds a shared reference to the view model.
- L25 _public function_ `SLATE_BEGIN_ARGS(SPropertyBagHierarchyEditor)`
- L27 _public prototype_ `SLATE_EVENT(FSimpleDelegate, OnCloseRequested) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FPropertyBagHierarchyViewModelOwner> InHierarchyViewModelOwner);`
- L34 _public prototype_ `TSharedPtr<IPropertyHandle> GetPropertyBagHandle() const;` — Returns the property handle that we generated ourselves via property row generator.
- L37 _public function_ `UHierarchyRoot* GetHierarchyRoot() const` — Returns the hierarchy root the editor is currently bound to. Used by the summoner to decide whether an already-open window can be reused as-is for a new request.
- L38 _public prototype_ `void NavigateToProperty(const FPropertyBagPropertyDesc& PropertyDesc, bool bAddIfNotFound = false);`
- L41 _private prototype_ `TSharedRef<SWidget> OnGenerateRowContentWidget(TSharedRef<FHierarchyElementViewModel> ElementViewModel) const;`
- L42 _private prototype_ `void OnAssetEditorClosed(UObject* Object, IAssetEditorInstance* AssetEditorInstance) const;`
- L45 _private member_ `TWeakObjectPtr<const UPropertyBagSchema> PropertyBagSchemaCDO;`
- L48 _private member_ `TSharedPtr<FPropertyBagHierarchyViewModelOwner> HierarchyViewModelOwner;` — Shared ownership — keeps the view model alive as long as this widget exists, even if the details panel is destroyed. When the last owner is released, the view model is finalized and marked as garbage.
- L50 _private member_ `TWeakObjectPtr<UHierarchyRoot> HierarchyRoot;`
- L52 _private member_ `TArray<TWeakObjectPtr<UObject>> OuterObjects;`
- L54 _private member_ `FSimpleDelegate OnCloseRequested;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API STRUCTUTILSEDITOR_API`

### `Source/Editor/StructUtilsEditor/Private/StructUtilsEditorLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogStructUtilsEditor, Log, All);`

### `Source/Editor/StructUtilsEditor/Private/StructUtilsEditorUtilsPrivate.h` (Private)


#### struct `UE::StructUtils::Private::FFindUserFunctionResult`  
`struct FFindUserFunctionResult`  
_L14-18_
- L16 _public member_ `UFunction* Function = nullptr;`
- L17 _public member_ `UObject* Target = nullptr;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace StructUtils` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::StructUtils`)
- L21 _prototype_ `TOptional<FFindUserFunctionResult> FindUserFunction(const TSharedPtr<IPropertyHandle>& InStructProperty, FName InFuncMetadataName);` (scope `UE::StructUtils::Private`) — @return the member and the member function that exist on the property handle object.
- L25 _function_ `template<typename T> requires TModels_V<CStaticStructProvider, T> bool IsScriptStruct(const TSharedPtr<IPropertyHandle>& PropertyHandle)` (scope `UE::StructUtils::Private`) — @return true property handle holds struct property of type T.

### `Source/Editor/StructUtilsEditor/Public/HierarchyEditor/PropertyBagHierarchyViewModel.h` (Public)


#### class `UPropertyBagHierarchyRoot`  
`class UPropertyBagHierarchyRoot : public UHierarchyRoot`  
_L24-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UHierarchyRoot`
- L29 _public member_ `FOnPropertyBagHierarchyModified OnHierarchyModified;`

#### class `UPropertyBagHierarchyCategory`  
`class UPropertyBagHierarchyCategory : public UHierarchyCategory`  
_L33-39_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UHierarchyCategory`

#### class `UPropertyBagHierarchySection`  
`class UPropertyBagHierarchySection : public UHierarchySection`  
_L42-48_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UHierarchySection`

#### struct `FPropertyBagPropertyMetadata_Base`  
`struct FPropertyBagPropertyMetadata_Base`  
_L51-58_
- reflection: `USTRUCT()`
- L55 _public prototype_ `virtual ~FPropertyBagPropertyMetadata_Base() = default;`
- L57 _public function_ `virtual void PostEditChange(const FPropertyChangedEvent& PropertyChangedEvent, TSharedPtr<FPropertyBagHierarchyPropertyViewModel> PropertyViewModel)`

#### struct `FPropertyBagPropertyMetadata_Common`  
`struct FPropertyBagPropertyMetadata_Common : public FPropertyBagPropertyMetadata_Base`  
_L61-74_
- reflection: `USTRUCT(DisplayName="Common")`
- inherits: `FPropertyBagPropertyMetadata_Base`
- L67 _public member_ `FText Tooltip;` — `UPROPERTY(EditAnywhere, Category="Generic", meta=(MultiLine))` — The tooltip for this property.
- L71 _public member_ `bool bAdvanced = false;` — `UPROPERTY(EditAnywhere, Category="Generic")` — Whether this property is advanced or not. If it's advanced, it will only display if the "Show Advanced" button is clicked.
- L73 _public prototype_ `virtual void PostEditChange(const FPropertyChangedEvent& PropertyChangedEvent, TSharedPtr<FPropertyBagHierarchyPropertyViewModel> PropertyViewModel) override;`

#### struct `FPropertyBagPropertyMetadata_Numeric`  
`struct FPropertyBagPropertyMetadata_Numeric : public FPropertyBagPropertyMetadata_Base`  
_L77-118_
- reflection: `USTRUCT(DisplayName="Numeric")`
- inherits: `FPropertyBagPropertyMetadata_Base`
- L81 _public member_ `static constexpr float DefaultClampMin = 0.f;`
- L82 _public member_ `static constexpr float DefaultClampMax = 10.f;`
- L83 _public member_ `static constexpr float DefaultUIMin = 0.f;`
- L84 _public member_ `static constexpr float DefaultUIMax = 10.f;`
- L85 _public member_ `static constexpr EUnit DefaultUnit = EUnit::Unspecified;`
- L88 _public member_ `bool bUseClampMin = false;` — `UPROPERTY()`
- L91 _public member_ `float ClampMin = DefaultClampMin;` — `UPROPERTY(EditAnywhere, Category="Numeric", meta=(EditCondition="bUseClampMin"))`
- L94 _public member_ `bool bUseClampMax = false;` — `UPROPERTY()`
- L97 _public member_ `float ClampMax = DefaultClampMax;` — `UPROPERTY(EditAnywhere, Category="Numeric", meta=(EditCondition="bUseClampMax"))`
- L100 _public member_ `bool bUseUIMin = false;` — `UPROPERTY()`
- L103 _public member_ `float UIMin = DefaultUIMin;` — `UPROPERTY(EditAnywhere, Category="Numeric", meta=(EditCondition="bUseUIMin"))`
- L106 _public member_ `bool bUseUIMax = false;` — `UPROPERTY()`
- L109 _public member_ `float UIMax = DefaultUIMax;` — `UPROPERTY(EditAnywhere, Category="Numeric", meta=(EditCondition="bUseUIMax"))`
- L112 _public member_ `bool bUseUnit = false;` — `UPROPERTY()`
- L115 _public member_ `EUnit Unit = DefaultUnit;` — `UPROPERTY(EditAnywhere, Category="Numeric", meta=(EditCondition="bUseUnit"))`
- L117 _public prototype_ `virtual void PostEditChange(const FPropertyChangedEvent& PropertyChangedEvent, TSharedPtr<FPropertyBagHierarchyPropertyViewModel> PropertyViewModel) override;`

#### class `UPropertyBagHierarchyProperty`  
`class UPropertyBagHierarchyProperty : public UHierarchyItem`  
_L121-178_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UHierarchyItem`
- L126 _public prototype_ `void Initialize(const FPropertyBagPropertyDesc& PropertyDesc);`
- L128 _public prototype_ `UPropertyBagHierarchyProperty* GetArchetype() const;`
- L130 _public prototype_ `static FHierarchyElementIdentity ConstructIdentity(const FPropertyBagPropertyDesc& PropertyDesc);`
- L132 _public prototype_ `FGuid GetPropertyId() const;`
- L134 _public prototype_ `FInstancedStruct* FindOrAddPropertyMetaData(const UScriptStruct* InScriptStruct);`
- L136 _public prototype_ `bool ContainsPropertyMetaDataOfType(const UScriptStruct* InScriptStruct);`
- L139 _public function_ `template<typename T> bool ContainsPropertyMetaDataOfType()`
- L145 _public prototype_ `const FInstancedStruct* FindPropertyMetaDataOfType(const UScriptStruct* InScriptStruct) const;`
- L147 _public prototype_ `FInstancedStruct* FindPropertyMetaDataOfTypeMutable(const UScriptStruct* InScriptStruct);`
- L150 _public function_ `template<typename T> const T* FindPropertyMetaDataOfType() const`
- L163 _public function_ `template<typename T> T* FindPropertyMetaDataOfTypeMutable()`
- L177 _public member_ `FInstancedStructArray PropertyMetadata;` — `UPROPERTY(EditAnywhere, Category="NoCategory")` — All metadata goes in here in form of FInstancedStruct. This is maintained by the API.

#### struct `FPropertyBagHierarchyPropertyViewModel`  
`struct FPropertyBagHierarchyPropertyViewModel : public FHierarchyItemViewModel`  
_L180-199_
- inherits: `FHierarchyItemViewModel`
- L182 _public prototype_ `FPropertyBagHierarchyPropertyViewModel(UPropertyBagHierarchyProperty* InProperty, TSharedRef<FHierarchyElementViewModel> InParent, TWeakObjectPtr<UDataHierarchyViewModelBase> InHierarchyViewModel);`
- L184 _public prototype_ `void UpdateMetaData();`
- L186 _public prototype_ `const FPropertyBagPropertyDesc* GetPropertyDesc() const;`
- L188 _public prototype_ `virtual void PostEditChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;`
- L189 _public function_ `virtual bool RepresentsExternalData() const override`
- L190 _public prototype_ `virtual bool DoesExternalDataStillExist(const UHierarchyDataRefreshContext* Context) const override;`
- L191 _public prototype_ `virtual void SyncViewModelsToDataInternal() override;`
- L195 _public function_ `virtual bool CanDeleteInternal() override` — Users can't manually delete the properties. They can still be deleted if their parent gets deleted however. We re-add the properties to the root in that case.
- L198 _protected prototype_ `virtual FString ToString() const override;`

#### class `UPropertyBagHierarchyViewModel`  
`class UPropertyBagHierarchyViewModel : public UDataHierarchyViewModelBase, public FTickableEditorObject`  
_L203-275_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDataHierarchyViewModelBase,FTickableEditorObject`
- desc: The hierarchy view model for property bags. Defines core rules for how the hierarchy behaves.
- L220 _public prototype_ `void Initialize(UObject* InOwningObject, TSharedRef<FPropertyPath> InPropertyPath);` — Initializes the hierarchy view model. Internally creates a PropertyRowGenerator to generate a stable property handle that survives details panel refreshes. The property handle is used by ApplyChangesToSinglePropertyDesc to notify pre/post change when editing property metadata (tooltips, clamp values, etc.) via the hierarchy editor. Note: PropertyUtilities must be set separately via SetPropertyUtilities() after Initialize returns. This is because Initialize triggers a PropertyRowGenerator layout rebuild which re-enters AcquireHierarchyViewModel, and setting utilities during that reentrancy would overwrite them with the generator's internal utilities. @param InOwningObject The UObject that owns the property bag (e.g. the Blueprint CDO or actor). Used to populate the PropertyRowGenerator. @param InPropertyPath Path to the FInstancedPropertyBag property within the owning object. Used to locate the property bag handle in the generated property tree.
- L222 _public prototype_ `virtual void BeginDestroy() override;`
- L224 _public prototype_ `void RegeneratePropertyBagHandle();`
- L226 _public prototype_ `void AddMissingPropertiesToRoot(bool bSendNotification = false);`
- L228 _public prototype_ `const FPropertyBagPropertyDesc* GetPropertyDescForProperty(FGuid PropertyId) const;`
- L229 _public prototype_ `TConstArrayView<FPropertyBagPropertyDesc> GetPropertyDescs() const;`
- L231 _public function_ `TSharedPtr<IPropertyHandle> GetPropertyBagHandle() const`
- L232 _public function_ `TSharedPtr<IPropertyUtilities> GetPropertyUtilities() const`
- L233 _public function_ `TSharedRef<FPropertyPath> GetCurrentPropertyPath() const`
- L236 _public prototype_ `void SetPropertyUtilities(TSharedRef<IPropertyUtilities> InPropertyUtilities);` — Updates the property utilities reference. Call when a new details panel instance provides fresh utilities.
- L238 _public prototype_ `void RebuildDetails() const;`
- L240 _public prototype_ `virtual UHierarchyRoot* GetHierarchyRoot() const override;`
- L243 _protected prototype_ `virtual void Tick(float DeltaTime) override;`
- L244 _protected prototype_ `virtual bool IsTickable() const override;`
- L245 _protected prototype_ `virtual TStatId GetStatId() const override;`
- L247 _protected prototype_ `virtual void OnHierarchyChanged(const TInstancedStruct<FHierarchyChangedPayload>& Payload) override;`
- L248 _protected prototype_ `virtual TSubclassOf<UHierarchyCategory> GetCategoryDataClass() const override;`
- L249 _protected prototype_ `virtual TSubclassOf<UHierarchySection> GetSectionDataClass() const override;`
- L250 _protected prototype_ `virtual TSharedPtr<FHierarchyElementViewModel> CreateCustomViewModelForElement(UHierarchyElement* Element, TSharedPtr<FHierarchyElementViewModel> Parent) override;`
- L252 _protected function_ `virtual bool SupportsSourcePanel() const override` — We auto-add elements to the hierarchy, so we don't need the source panel.
- L253 _protected function_ `virtual ESelectionMode::Type GetHierarchySelectionMode() const override`
- L254 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L255 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L257 _protected prototype_ `const FInstancedPropertyBag* GetPropertyBag() const;`
- L259 _protected prototype_ `static bool FindPropertyHandleRecursive(const TSharedPtr<IPropertyHandle>& PropertyHandle, TSharedRef<FPropertyPath> PropertyPath);`
- L260 _protected prototype_ `static TSharedPtr<IDetailTreeNode> FindTreeNodeRecursive(const TSharedRef<IDetailTreeNode>& RootNode, TSharedRef<FPropertyPath> PropertyPath);`
- L261 _protected prototype_ `static TSharedPtr<IDetailTreeNode> FindNode(const TArray<TSharedRef<IDetailTreeNode>>& RootNodes, TSharedRef<FPropertyPath> PropertyPath);`
- L264 _private member_ `TWeakPtr<IPropertyUtilities> PropertyUtilities;`
- L265 _private member_ `TWeakObjectPtr<const UPropertyBagSchema> PropertyBagSchema;`
- L267 _private member_ `TSharedPtr<IPropertyRowGenerator> PropertyRowGenerator;`
- L268 _private member_ `TWeakObjectPtr<UHierarchyRoot> HierarchyRoot;`
- L269 _private member_ `TWeakObjectPtr<UObject> OwningObject;`
- L270 _private member_ `TSharedPtr<FPropertyPath> PropertyPathToPropertyBag;`
- L272 _private member_ `uint64 LastHash = 0;`
- L274 _private member_ `TSharedPtr<IPropertyHandle> GeneratedPropertyBagHandle;`

#### struct `FPropertyBagHierarchyScriptRootViewModel`  
`struct FPropertyBagHierarchyScriptRootViewModel : public FHierarchyRootViewModel`  
_L277-284_
- inherits: `FHierarchyRootViewModel`
- L279 _public function_ `FPropertyBagHierarchyScriptRootViewModel(UHierarchyRoot* Root, TWeakObjectPtr<UPropertyBagHierarchyViewModel> ViewModel, bool bInIsForHierarchy) : FHierarchyRootViewModel(Root, ViewModel, bInIsForHierarchy)`
- L283 _public prototype_ `virtual void PostEditHierarchyStructure() override;`

#### class `FPropertyBagHierarchyViewModelPropertyEditorPolicy`  
`class FPropertyBagHierarchyViewModelPropertyEditorPolicy : public PropertyEditorPolicy::IArchetypePolicy`  
_L286-294_
- inherits: `PropertyEditorPolicy::IArchetypePolicy`
- L289 _public prototype_ `FPropertyBagHierarchyViewModelPropertyEditorPolicy();`
- L291 _public prototype_ `virtual ~FPropertyBagHierarchyViewModelPropertyEditorPolicy();`
- L293 _public prototype_ `virtual UObject* GetArchetypeForObject(const UObject* Object) const override;`

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnPropertyBagHierarchyModified);` — This file defines hierarchy elements and the view model that controls the hierarchy. If you are looking to make use of them, simply subclass UPropertyBagSchema and override relevant functions. If you wish to add properties to your usecase for editor purposes, consider subclassing either property, section or category. If your property is generic and should be functioning for every property bag, consider adding them in the base classes here.
- L21 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnPropertyBagHierarchyModified);` — This file defines hierarchy elements and the view model that controls the hierarchy. If you are looking to make use of them, simply subclass UPropertyBagSchema and override relevant functions. If you wish to add properties to your usecase for editor purposes, consider subclassing either property, section or category. If your property is generic and should be functioning for every property bag, consider adding them in the base classes here.

### `Source/Editor/StructUtilsEditor/Public/IPropertyBagEditorGraph.h` (Public)


#### class `UPropertyBagEdGraphDragAndDrop`  
`class UPropertyBagEdGraphDragAndDrop : public UInterface`  
_L30-33_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IPropertyBagEdGraphDragAndDrop`  
`class IPropertyBagEdGraphDragAndDrop`  
_L47-58_
- desc: PropertyBag Editor Drag and Drop public interface. Usage: This interface can be used independently or as a part of the IPropertyBagEdGraph interface (below), to be inherited by custom subclasses of UEdGraph. Once inherited, implement the following member overrides to validate and receive Drag and Drop operations from a PropertyBag details child row. The PropertyBagDragDropHandler (see PropertyBagDragDropHandler.h/.cpp) inherits from FGraphEditorDragDropAction, mimicking a graph schema action being dropped into the graph, or onto a pin or node. Note: The base handler class currently climbs down ownership from Graph->Pin, so if only the graph is valid, it will attempt the graph panel drop through the pins' or nodes' parent graph.
- L52 _public prototype_ `virtual bool CanReceivePropertyBagDetailsDropOnGraphPin(const UEdGraphPin* Pin) const;`
- L53 _public prototype_ `virtual bool CanReceivePropertyBagDetailsDropOnGraphNode(const UEdGraphNode* Node) const;`
- L54 _public prototype_ `virtual bool CanReceivePropertyBagDetailsDropOnGraph(const UEdGraph* Graph) const;`
- L55 _public prototype_ `virtual FReply OnPropertyBagDetailsDropOnGraphPin(const FPropertyBagPropertyDesc& PropertyDesc, UEdGraphPin* Pin, const FVector2f& GraphPosition) const;`
- L56 _public prototype_ `virtual FReply OnPropertyBagDetailsDropOnGraphNode(const FPropertyBagPropertyDesc& PropertyDesc, UEdGraphNode* Node, const FVector2f& GraphPosition) const;`
- L57 _public prototype_ `virtual FReply OnPropertyBagDetailsDropOnGraph(const FPropertyBagPropertyDesc& PropertyDesc, UEdGraph* Graph, const FVector2f& GraphPosition) const;`
- L77 _function_ `inline bool IPropertyBagEdGraphDragAndDrop::CanReceivePropertyBagDetailsDropOnGraphPin(const UEdGraphPin* Pin) const`
- L82 _function_ `inline bool IPropertyBagEdGraphDragAndDrop::CanReceivePropertyBagDetailsDropOnGraphNode(const UEdGraphNode* Node) const`
- L87 _function_ `inline bool IPropertyBagEdGraphDragAndDrop::CanReceivePropertyBagDetailsDropOnGraph(const UEdGraph* Graph) const`
- L92 _function_ `inline FReply IPropertyBagEdGraphDragAndDrop::OnPropertyBagDetailsDropOnGraphPin(const FPropertyBagPropertyDesc& PropertyDesc, UEdGraphPin* Pin, const FVector2f& GraphPosition) const`
- L97 _function_ `inline FReply IPropertyBagEdGraphDragAndDrop::OnPropertyBagDetailsDropOnGraphNode(const FPropertyBagPropertyDesc& PropertyDesc, UEdGraphNode* Node, const FVector2f& GraphPosition) const`
- L102 _function_ `inline FReply IPropertyBagEdGraphDragAndDrop::OnPropertyBagDetailsDropOnGraph(const FPropertyBagPropertyDesc& PropertyDesc, UEdGraph* Graph, const FVector2f& GraphPosition) const`

#### class `UPropertyBagEdGraph`  
`class UPropertyBagEdGraph : public UPropertyBagEdGraphDragAndDrop`  
_L61-64_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UPropertyBagEdGraphDragAndDrop`

#### class `IPropertyBagEdGraph`  
`class IPropertyBagEdGraph : public IPropertyBagEdGraphDragAndDrop`  
_L72-75_
- inherits: `IPropertyBagEdGraphDragAndDrop`
- desc: PropertyBag Editor public interface Usage: This interface to be inherited by custom subclasses of UEdGraph for full implementation of all StructUtils editor graph integration features.

### `Source/Editor/StructUtilsEditor/Public/IStructUtilsEditor.h` (Public)


#### class `IStructUtilsEditor`  
`class IStructUtilsEditor : public FAssetEditorToolkit`  
_L9-13_
- inherits: `FAssetEditorToolkit`
- desc: StructUtils Editor public interface

### `Source/Editor/StructUtilsEditor/Public/InstancedPropertyBagStructureDataProvider.h` (Public)


#### class `FInstancePropertyBagStructureDataProvider`  
`class FInstancePropertyBagStructureDataProvider : public IStructureDataProvider`  
_L11-43_
- inherits: `IStructureDataProvider`
- desc: FInstancePropertyBagStructureDataProvider Allows structure views to use FInstancedPropertyBag even if the bag layout changes. The caller needs to make sure that property bag outlives the property view widget.
- L14 _public function_ `FInstancePropertyBagStructureDataProvider(FInstancedPropertyBag& InPropertyBag) : PropertyBag(InPropertyBag)`
- L19 _public function_ `virtual bool IsValid() const override`
- L24 _public function_ `virtual const UStruct* GetBaseStructure() const override`
- L29 _public function_ `virtual void GetInstances(TArray<TSharedPtr<FStructOnScope>>& OutInstances, const UStruct* ExpectedBaseStructure) const override`
- L42 _protected member_ `FInstancedPropertyBag& PropertyBag;`

#### class `TInstancedPropertyBagStructureDataProvider`  
`template<typename BagInstanceType> class TInstancedPropertyBagStructureDataProvider : public IStructureDataProvider`  
_L52-113_
- inherits: `IStructureDataProvider`
- L55 _public function_ `explicit TInstancedPropertyBagStructureDataProvider(const TSharedPtr<BagInstanceType>& InPropertyBag) : PropertyBagInstances( {InPropertyBag} )`
- L60 _public function_ `explicit TInstancedPropertyBagStructureDataProvider(const TArray<TSharedPtr<BagInstanceType>>& InPropertyBagInstances) : PropertyBagInstances(InPropertyBagInstances)`
- L65 _public function_ `virtual bool IsValid() const override`
- L86 _public function_ `virtual const UStruct* GetBaseStructure() const override`
- L93 _public function_ `virtual void GetInstances(TArray<TSharedPtr<FStructOnScope>>& OutInstances, const UStruct* ExpectedBaseStructure) const override`
- L112 _protected member_ `TArray<TSharedPtr<BagInstanceType>> PropertyBagInstances;`

### `Source/Editor/StructUtilsEditor/Public/InstancedStructDetails.h` (Public)


#### class `FInstancedStructDetails`  
`class FInstancedStructDetails : public IPropertyTypeCustomization`  
_L26-55_
- inherits: `IPropertyTypeCustomization`
- desc: Type customization for FInstancedStruct.
- L32 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L35 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L36 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L40 _private prototype_ `void OnCopyInstancedStruct() const;`
- L42 _private prototype_ `bool CanPasteInstancedStruct() const;`
- L43 _private prototype_ `void OnPasteInstancedStruct();`
- L45 _private typedef_ `using FReplacementObjectMap = TMap<UObject*, UObject*>;`
- L46 _private prototype_ `void OnObjectsReinstanced(const FReplacementObjectMap& ObjectMap);`
- L49 _private member_ `TSharedPtr<IPropertyHandle> StructProperty;` — Handle to the struct property being edited
- L51 _private member_ `TSharedPtr<SInstancedStructPicker> StructPicker;`
- L52 _private member_ `TSharedPtr<IPropertyUtilities> PropUtils;`
- L54 _private member_ `FDelegateHandle OnObjectsReinstancedHandle;`

#### class `FInstancedStructDataDetails`  
`class FInstancedStructDataDetails : public IDetailCustomNodeBuilder, public TSharedFromThis<FInstancedStructDataDetails>`  
_L64-129_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FInstancedStructDataDetails>`
- desc: Node builder for FInstancedStruct children. Expects property handle holding FInstancedStruct as input. Can be used in a implementation of a IPropertyTypeCustomization CustomizeChildren() to display editable FInstancedStruct contents. OnChildRowAdded() is called right after each property is added, which allows the property row to be customizable. Child properties will be grouped if they 1) have "Category" metadata, and 2) have the "EnableCategories" metadata tag.
- L67 _public prototype_ `FInstancedStructDataDetails(TSharedPtr<IPropertyHandle> InStructProperty);`
- L71 _public prototype_ `virtual void SetOnRebuildChildren(FSimpleDelegate InOnRegenerateChildren) override;`
- L72 _public prototype_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& NodeRow) override;`
- L73 _public prototype_ `virtual void GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder) override;`
- L74 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L75 _public function_ `virtual bool RequiresTick() const override`
- L76 _public function_ `virtual bool InitiallyCollapsed() const override`
- L77 _public prototype_ `virtual FName GetName() const override;`
- L81 _public function_ `virtual void OnGroupRowAdded(IDetailGroup& GroupRow, int32 Level, const FString& Category) const` — Called when a group is added, override to customize a group row.
- L83 _public function_ `virtual void OnChildRowAdded(IDetailPropertyRow& ChildRow)` — Called when a child is added, override to customize a child row.
- L86 _protected prototype_ `static TArray<FString> GetPropertyCategories(TSharedPtr<IPropertyHandle> PropertyHandle);`
- L88 _protected prototype_ `virtual void AddChildRows(IDetailChildrenBuilder& ChildBuilder, const TArray<TSharedPtr<IPropertyHandle>>& ChildProperties);` — Add all the rows for a child properties.
- L90 _protected prototype_ `virtual void AddChildRow(IDetailChildrenBuilder& ChildBuilder, TSharedPtr<IPropertyHandle> ChildHandle, IDetailGroup* PropertyGroup);` — Add all the rows for a child's property.
- L93 _private prototype_ `void OnUserDefinedStructReinstancedHandle(const class UUserDefinedStruct& Struct);`
- L96 _private prototype_ `void OnStructValuePreChange();` — Pre/Post change notifications for struct value changes
- L97 _private prototype_ `void OnStructValuePostChange();`
- L98 _private prototype_ `void OnStructHandlePostChange();`
- L101 _private prototype_ `TArray<TWeakObjectPtr<const UStruct>> GetInstanceTypes() const;` — Returns type of the instanced struct for each instance/object being edited.
- L109 _private prototype_ `void GetPropertyGroups(const TArray<TSharedPtr<IPropertyHandle>>& InProperties, IDetailChildrenBuilder& InChildBuilder, TMap<TSharedPtr<IPropertyHandle>, IDetailGroup*>& OutPropertyToGroup) const;` — Adds groups for the specified properties. One group is created for each unique category (from property metadata) that the properties have. If a category is pipe-separated (eg, Foo|Bar), one group is added for "Foo" and another one for "Foo|Bar". In the returned map, the key is the property, and the value is the group. If the property doesn't have a group (category), then it will not have an entry in the map. Note that the property must opt-in to grouping by specifying the "EnableCategories" metadata tag.
- L112 _private member_ `TArray<TWeakObjectPtr<const UStruct>> CachedInstanceTypes;` — Cached instance types, used to invalidate the layout when types change.
- L115 _private member_ `bool bCanHandleStructValuePostChange = false;` — True if we're allowed to handle a StructValuePostChange
- L117 _private member_ `bool bStructChangeDetected = false;` — Mark the struct has changed, it requires a rebuild on the next iteration.
- L119 _private member_ `FDelegateHandle UserDefinedStructReinstancedHandle;`
- L123 _protected member_ `TSharedPtr<IPropertyHandle> StructProperty;` — Handle to the struct property being edited
- L126 _protected member_ `FSimpleDelegate OnRegenerateChildren;` — Delegate that can be used to refresh the child rows of the current struct (eg, when changing struct type)
- L128 _protected prototype_ `void OnStructLayoutChanges();`

#### class `FInstancedStructDataWithHeaderDetails`  
`class FInstancedStructDataWithHeaderDetails : public FInstancedStructDataDetails`  
_L131-138_
- inherits: `FInstancedStructDataDetails`
- L134 _public prototype_ `FInstancedStructDataWithHeaderDetails(TSharedPtr<IPropertyHandle> InStructProperty);`
- L135 _public prototype_ `virtual ~FInstancedStructDataWithHeaderDetails() override = default;`
- L137 _public prototype_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& NodeRow) override;`

#### class `FInstancedStructArrayBuilder`  
`class FInstancedStructArrayBuilder : public FDetailArrayBuilder, public TSharedFromThis<FInstancedStructArrayBuilder>`  
_L140-151_
- inherits: `FDetailArrayBuilder,TSharedFromThis<FInstancedStructArrayBuilder>`
- L143 _public prototype_ `FInstancedStructArrayBuilder(TSharedRef<IPropertyHandle> InArrayHandle);`
- L144 _public prototype_ `virtual ~FInstancedStructArrayBuilder() override = default;`
- L146 _public prototype_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& NodeRow) override;`
- L147 _public prototype_ `virtual void GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder) override;`
- L150 _private member_ `TSharedPtr<IPropertyHandle> ArrayHandle;`

#### class `FInstancedStructArrayDetails`  
`class FInstancedStructArrayDetails : public IPropertyTypeCustomization`  
_L153-166_
- inherits: `IPropertyTypeCustomization`
- L156 _public prototype_ `FInstancedStructArrayDetails() = default;`
- L157 _public prototype_ `virtual ~FInstancedStructArrayDetails() override = default;`
- L159 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L161 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L162 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L165 _private prototype_ `void OnGenerateArrayElementWidget(TSharedRef<IPropertyHandle> PropertyHandle, int32 Index, IDetailChildrenBuilder& DetailChildrenBuilder);`

#### class `FInstancedStructProvider`  
`class FInstancedStructProvider : public IStructureDataProvider`  
_L168-191_
- inherits: `IStructureDataProvider`
- L171 _public prototype_ `FInstancedStructProvider() = default;`
- L173 _public function_ `explicit FInstancedStructProvider(const TSharedPtr<IPropertyHandle>& InStructProperty) : StructProperty(InStructProperty)`
- L178 _public prototype_ `virtual ~FInstancedStructProvider() override = default;`
- L180 _public prototype_ `void Reset();`
- L181 _public prototype_ `virtual bool IsValid() const override;`
- L182 _public prototype_ `virtual const UStruct* GetBaseStructure() const override;`
- L183 _public prototype_ `virtual void GetInstances(TArray<TSharedPtr<FStructOnScope>>& OutInstances, const UStruct* ExpectedBaseStructure) const override;`
- L184 _public prototype_ `virtual bool IsPropertyIndirection() const override;`
- L185 _public prototype_ `virtual uint8* GetValueBaseAddress(uint8* ParentValueAddress, const UStruct* ExpectedBaseStructure) const override;`
- L188 _protected prototype_ `void EnumerateInstances(TFunctionRef<bool(const UScriptStruct* ScriptStruct, uint8* Memory, UPackage* Package)> InFunc) const;`
- L190 _protected member_ `TSharedPtr<IPropertyHandle> StructProperty;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API STRUCTUTILSEDITOR_API`

### `Source/Editor/StructUtilsEditor/Public/PropertyBagDetails.h` (Public)


#### enum `EPropertyBagChildRowFeatures`  
`enum class EPropertyBagChildRowFeatures : uint64`  
_L41-78_
- reflection: `UENUM(meta = (Bitflags))`
- desc: The property bag details child rows can be completely customized by assigning a combination of these values to their FPropertyBag 'ChildRowFeatures' metadata via the meta specifier. TODO: It isn't currently possible to specify bitwise operations in the metadata string, but this will be added shortly. More configurations can be added in the meantime to satisfy specific needs.
- L44 _public enumerator_ `Fixed = 0` — General Options
- L45 _public enumerator_ `Renaming = 1ULL << 0` — The property name is editable from the details view.
- L46 _public enumerator_ `Deletion = 1ULL << 1` — The property is able to be deleted.
- L47 _public enumerator_ `DragAndDrop = 1ULL << 2` — Drag and dropping properties is enabled.
- L48 _public enumerator_ `CompactTypeSelector = 1ULL << 3` — A compact type selector widget is enabled to the left of the name.
- L49 _public enumerator_ `AccessSpecifierButton = 1ULL << 4` — The property metadata can be set for public/private access.
- L50 _public enumerator_ `DropDownMenuButton = 1ULL << 5` — Drop-down menu (down arrow button) is enabled.
- L51 _public enumerator_ `Categories = 1ULL << 6` — Categories are enabled (UPROPERTY categories).
- L52 _public enumerator_ `AllGeneralOptions = Renaming | Deletion | DragAndDrop | CompactTypeSelector | AccessSpecifierButton | DropDownMenuButton | Categories`
- L57 _public enumerator_ `Menu_TypeSelector = 1ULL << 17` — Menu Options (for drop-down menu or other future menus (right click)
- L58 _public enumerator_ `Menu_Rename = 1ULL << 18` — Renaming the property from the drop-down menu. Requires property renaming enabled.
- L59 _public enumerator_ `Menu_Delete = 1ULL << 19` — Deleting the property from the drop-down menu.
- L60 _public enumerator_ `Menu_Categories = 1ULL << 20` — Create new/remove from categories.
- L61 _public enumerator_ `Menu_MetadataSpecifiers = 1ULL << 21` — Common metadata specifier options.
- L63 _public enumerator_ `AllMenuOptions = Menu_TypeSelector | Menu_Rename | Menu_Delete | Menu_Categories | Menu_MetadataSpecifiers`
- L66 _public enumerator_ `Deprecated = 1ULL << 63` — Insert new menu features above this line.
- L69 _public enumerator_ `ReadOnly = Fixed` — Below are configurations for convenience. These can be set via the Metadata specifier on the property bag.
- L71 _public enumerator_ `Core = Renaming | Deletion | DropDownMenuButton | Menu_TypeSelector | Menu_Rename | Menu_Delete` — Renaming and deleting enabled, with type selection happening in the drop-down menu.
- L73 _public enumerator_ `Extended = Core | DragAndDrop | CompactTypeSelector | Categories | Menu_Categories | Menu_MetadataSpecifiers` — Also enables the compact type selector icon, drag and drop, and categories support.
- L75 _public enumerator_ `All = AllGeneralOptions | AllMenuOptions` — All options.
- L77 _public enumerator_ `Default = Renaming | Deletion | Deprecated` — The default version includes deprecated UI features to support previous behavior.

#### class `FPropertyBagDetails`  
`class FPropertyBagDetails : public IPropertyTypeCustomization`  
_L139-193_
- inherits: `IPropertyTypeCustomization`
- desc: Type customization for FInstancedPropertyBag.
- L144 _public prototype_ `FPropertyBagDetails() = default;` — Required for deprecated variable 'bFixedLayout'. TODO: Remove when removing 5.6 deprecations.
- L145 _public prototype_ `~FPropertyBagDetails() = default;`
- L146 _public prototype_ `FPropertyBagDetails(const FPropertyBagDetails& Other) = delete;`
- L147 _public prototype_ `FPropertyBagDetails(FPropertyBagDetails&& Other) noexcept = delete;`
- L148 _public prototype_ `FPropertyBagDetails& operator=(const FPropertyBagDetails& Other) = delete;`
- L149 _public prototype_ `FPropertyBagDetails& operator=(FPropertyBagDetails&& Other) noexcept = delete;`
- L153 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L156 _public prototype_ `static TSharedPtr<SWidget> MakeAddPropertyWidget(TSharedPtr<IPropertyHandle> InStructProperty, TSharedPtr<IPropertyUtilities> InPropUtils, EPropertyBagPropertyType DefaultType = EPropertyBagPropertyType::Bool, FSlateColor IconColor = FSlateColor::UseForeground());` — Creates add property widget.
- L160 _protected prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L161 _protected prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L163 _protected prototype_ `static FReply SummonHierarchyEditor(TSharedPtr<IPropertyHandle> InPropertyBagHandle, TSharedPtr<IPropertyUtilities> InPropertyUtilities);`
- L164 _protected prototype_ `void NavigateToHierarchyProperty(const FPropertyBagPropertyDesc& Desc);`
- L166 _protected prototype_ `static void ClosePropertyBagHierarchyEditorWindow();`
- L170 _private member_ `TSharedPtr<IPropertyHandle> StructProperty;` — Handle to the property bag being edited
- L171 _private member_ `TSharedPtr<IPropertyUtilities> PropUtils;`
- L172 _private member_ `EPropertyBagPropertyType DefaultType = EPropertyBagPropertyType::Bool;`
- L173 _private member_ `EPropertyBagChildRowFeatures ChildRowFeatures = EPropertyBagChildRowFeatures::Default;`
- L178 _private member_ `static TWeakPtr<SWindow> PropertyBagHierarchyEditorWindow;` — We keep track of existing window & hierarchy editor loosely so we can recycle them where appropriate This also means we can only have 1 property bag hierarchy editor open at a time This is because an additional window can't rely on the existing details panel and property handles too much
- L179 _private member_ `static TWeakPtr<class SPropertyBagHierarchyEditor> PropertyBagHierarchyEditor;`
- L184 _private member_ `TSharedPtr<FPropertyBagHierarchyViewModelOwner> HierarchyViewModelOwner;` — Shared ownership of the hierarchy view model for this customization instance's lifetime. Released in the destructor; when the last consumer drops the owner, the view model is finalized and marked as garbage.
- L187 _private member_ `bool bFixedLayout = false;` — `UE_DEPRECATED(5.6, "Use 'ChildRowFeatures' instead.")`
- L188 _private member_ `bool bAllowContainers = true;`
- L191 _private member_ `TWeakObjectPtr<const UPropertyBagSchema> PropertyBagSchemaCDO;` — Default to UPropertyBagSchema, can be set with metadata PropertyBagSchemaClass
- L192 _private member_ `TWeakObjectPtr<UPropertyBagHierarchyRoot> HierarchyRoot;`

#### class `FPropertyBagInstanceDataDetails`  
`class FPropertyBagInstanceDataDetails : public FInstancedStructDataDetails`  
_L203-373_
- inherits: `FInstancedStructDataDetails`
- desc: Node builder for FInstancedPropertyBag children. - ValueProperty is FInstancedStruct of the FInstancedPropertyBag - StructProperty is FInstancedPropertyBag Can be used in a implementation of a IPropertyTypeCustomization CustomizeChildren() to display editable FInstancedPropertyBag contents. Use FPropertyBagDetails::MakeAddPropertyWidget() to create the add property widget. OnChildRowAdded() is called right after each property is added, which allows the property row to be customizable.
- L225 _public prototype_ `explicit FPropertyBagInstanceDataDetails(const FConstructParams& ConstructParams);`
- L226 _public prototype_ `FPropertyBagInstanceDataDetails(TSharedPtr<IPropertyHandle> InStructProperty, const TSharedPtr<IPropertyUtilities>& InPropUtils, bool bInFixedLayout, bool bInAllowContainers = true);`
- L230 _public prototype_ `~FPropertyBagInstanceDataDetails() = default;` — Required for deprecated variable 'bFixedLayout' and 'bAllowArrays'. TODO: Remove when removing 5.6 deprecations.
- L231 _public prototype_ `FPropertyBagInstanceDataDetails(const FPropertyBagInstanceDataDetails& Other) = delete;`
- L232 _public prototype_ `FPropertyBagInstanceDataDetails(FPropertyBagInstanceDataDetails&& Other) noexcept = delete;`
- L233 _public prototype_ `FPropertyBagInstanceDataDetails& operator=(const FPropertyBagInstanceDataDetails& Other) = delete;`
- L234 _public prototype_ `FPropertyBagInstanceDataDetails& operator=(FPropertyBagInstanceDataDetails&& Other) noexcept = delete;`
- L237 _public prototype_ `virtual void AddChildRows(IDetailChildrenBuilder& ChildBuilder, const TArray<TSharedPtr<IPropertyHandle>>& ChildProperties) override;`
- L238 _public prototype_ `virtual void OnGroupRowAdded(IDetailGroup& GroupRow, int32 Level, const FString& Category) const override;`
- L239 _public prototype_ `virtual void OnChildRowAdded(IDetailPropertyRow& ChildRow) override;`
- L262 _public typedef_ `using EnumeratePropertyBagFuncRef = TFunctionRef<bool(const FInstancedPropertyBag& , FInstancedPropertyBag& , IPropertyBagOverrideProvider& )>;` — Callback function for EnumeratePropertyBags. @return true to continue enumeration
- L269 _public function_ `virtual bool HasPropertyOverrides() const` — Method that is called to determine if a derived class has property override logic implemented. If true is returned, the overridden class is expected to implement PreChangeOverrides(), PostChangeOverrides(), EnumeratePropertyBags(). @return true of derived class has override logic implemented.
- L275 _public function_ `virtual void PreChangeOverrides()` — Called before property override is changed.
- L283 _public function_ `virtual void PostChangeOverrides()` — Called after property override is changed.
- L296 _public function_ `virtual void EnumeratePropertyBags(TSharedPtr<IPropertyHandle> PropertyBagHandle, const EnumeratePropertyBagFuncRef& Func) const` — Called to enumerate each property bag on the property handle. The Func expects DefaultPropertyBag (the values that are override), and PropertyBag (the one that PropertyBagHandle points to), and instance of IPropertyBagOverrideProvider which is used to query if specific property is overridden, or to set the property override state.
- L302 _public prototype_ `virtual EPropertyOverrideState IsPropertyOverridden(TSharedPtr<IPropertyHandle> ChildPropertyHandle) const;` — @return true if property of specified child property is overridden.
- L305 _public prototype_ `virtual void SetPropertyOverride(TSharedPtr<IPropertyHandle> ChildPropertyHandle, const bool bIsOverridden);` — Called to set the override state of specified child property.
- L308 _public prototype_ `virtual bool IsDefaultValue(TSharedPtr<IPropertyHandle> ChildPropertyHandle) const;` — @return true if the child property has default value.
- L311 _public prototype_ `virtual void ResetToDefault(TSharedPtr<IPropertyHandle> ChildPropertyHandle);` — Called to reset the child property to default value.
- L314 _public prototype_ `EVisibility ShouldShowHierarchyProperty(TSharedPtr<IPropertyHandle> ChildPropertyHandle) const;` — ~ Public Hierarchy Editor API
- L316 _public prototype_ `TWeakObjectPtr<const UHierarchySection> GetActiveHierarchySection() const;`
- L319 _public prototype_ `const TMap<TObjectKey<const UPropertyBagHierarchyProperty>, TSharedPtr<IPropertyHandle>>& GetHierarchyPropertyHandleMap() const;` — Retrieves the hierarchy property handle map. Only meaningful if used in conjunction with a hierarchy root.
- L322 _public prototype_ `UPropertyBagHierarchyViewModel* GetHierarchyViewModel() const;` — Retrieves the hierarchy view model, if available.
- L327 _protected prototype_ `TSharedRef<SWidget> OnPropertyNameContent(TSharedPtr<IPropertyHandle> ChildPropertyHandle, TSharedPtr<SInlineEditableTextBlock> InlineWidget) const;` — `UE_DEPRECATED(5.6, "Replaced by 'CreatePropertyDetailsWidget' to allow for more customizable drop-down menu location and content.")`
- L329 _protected member_ `TSharedPtr<IPropertyHandle> BagStructProperty;`
- L330 _protected member_ `TSharedPtr<IPropertyUtilities> PropUtils;`
- L332 _protected member_ `bool bAllowContainers = true;`
- L333 _protected member_ `EPropertyBagChildRowFeatures ChildRowFeatures = EPropertyBagChildRowFeatures::Default;`
- L336 _protected member_ `bool bFixedLayout = false;` — `UE_DEPRECATED(5.6, "Use 'ChildRowFeatures' instead.")`
- L338 _protected member_ `bool bAllowArrays = true;` — `UE_DEPRECATED(5.6, "Use 'bAllowContainers' instead.")`
- L341 _protected member_ `TSubclassOf<UEdGraphSchema> PropertyBagSchemaClass;` — `UE_DEPRECATED(5.8, "Use PropertyBagSchema instead. Will be invalid. PropertyBagSchema is set automatically via property metadata instead of passed in via construction arguments now.")`
- L344 _protected member_ `TWeakObjectPtr<const UPropertyBagSchema> PropertyBagSchema;` — Default to UPropertyBagSchema, can be set with metadata PropertyBagSchemaClass
- L346 _protected prototype_ `TSubclassOf<UPropertyBagSchema> GetPropertyBagSchemaClass() const;`
- L349 _protected prototype_ `void GenerateHierarchySectionRow(IDetailChildrenBuilder& ChildrenBuilder);` — ~ Hierarchy Editor API
- L350 _protected prototype_ `void GenerateHierarchyRootRows(IDetailChildrenBuilder& ChildrenBuilder);`
- L351 _protected prototype_ `void GenerateHierarchyLeftoverPropertyRows(IDetailChildrenBuilder& ChildrenBuilder, const TArray<TSharedPtr<IPropertyHandle>>& AllChildPropertyHandles);`
- L352 _protected prototype_ `void GenerateHierarchyShowAdvancedRow(IDetailChildrenBuilder& ChildrenBuilder);`
- L354 _protected prototype_ `const FSlateBrush* GetAdvancedImage() const;`
- L355 _protected prototype_ `EVisibility GetAdvancedButtonVisibility() const;`
- L357 _protected member_ `TSharedPtr<SWidget> ShowAdvancedButton;`
- L358 _protected member_ `bool bShouldShowAdvanced = false;`
- L371 _protected member_ `FHierarchyData HierarchyData;`

#### struct `FPropertyBagInstanceDataDetails::FConstructParams`  
`struct FConstructParams`  
_L209-223_
- L218 _public member_ `TSharedPtr<IPropertyHandle> BagStructProperty = nullptr;`
- L219 _public member_ `TSharedPtr<IPropertyUtilities> PropUtils = nullptr;`
- L220 _public member_ `bool bAllowContainers = true;`
- L221 _public member_ `EPropertyBagChildRowFeatures ChildRowFeatures = EPropertyBagChildRowFeatures::Default;`
- L222 _public member_ `FHierarchyParams HierarchyParams;`

#### struct `FPropertyBagInstanceDataDetails::FConstructParams::FHierarchyParams`  
`struct FHierarchyParams`  
_L212-216_
- desc: Hierarchy Params are only meaningful if the owning property bag has a valid HierarchyRoot provided by a schema
- L214 _public member_ `FPropertyBagPropertyDelegate OnNavigateToHierarchyPropertyRequested;`
- L215 _public member_ `TWeakObjectPtr<UPropertyBagHierarchyViewModel> HierarchyViewModel;`

#### enum `FPropertyBagInstanceDataDetails::EPropertyOverrideState`  
`enum class EPropertyOverrideState`  
_L242-247_
- desc: Enum describing if a property is overridden, or undetermined (e.g. multiselection)
- L244 _public enumerator_ `Yes`
- L245 _public enumerator_ `No`
- L246 _public enumerator_ `Undetermined`

#### struct `FPropertyBagInstanceDataDetails::IPropertyBagOverrideProvider`  
`struct IPropertyBagOverrideProvider`  
_L250-256_
- desc: Interface to allow to modify override status of a specific parameter.
- L252 _public prototype_ `virtual ~IPropertyBagOverrideProvider() = default;`
- L254 _public prototype_ `virtual bool IsPropertyOverridden(const FGuid PropertyID) const = 0;`
- L255 _public prototype_ `virtual void SetPropertyOverride(const FGuid PropertyID, const bool bIsOverridden) const = 0;`

#### struct `FPropertyBagInstanceDataDetails::FHierarchyData`  
`struct FHierarchyData`  
_L360-369_
- L362 _public member_ `TWeakObjectPtr<UPropertyBagHierarchyRoot> HierarchyRoot;`
- L363 _public member_ `TWeakObjectPtr<UPropertyBagHierarchyViewModel> HierarchyViewModel;`
- L364 _public member_ `TMap<TObjectKey<const UPropertyBagHierarchyProperty>, TSharedPtr<IPropertyHandle>> HierarchyPropertyHandleMap;`
- L365 _public member_ `TMap<FString, TWeakObjectPtr<const UPropertyBagHierarchyProperty>> PropertyPathPropertyMap;`
- L366 _public member_ `TWeakObjectPtr<const UHierarchySection> ActiveHierarchySection;`
- L368 _public member_ `FPropertyBagPropertyDelegate OnNavigateToHierarchyPropertyRequestedDelegate;`

#### class `UPropertyBagDetailsExtension`  
`class UPropertyBagDetailsExtension : public UObject`  
_L376-385_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L381 _public function_ `virtual TSharedRef<FPropertyBagInstanceDataDetails> CreateInstanceDataDetails(const FPropertyBagInstanceDataDetails::FConstructParams& Params) const`

#### class `UPropertyBagSchema`  
`class UPropertyBagSchema : public UEdGraphSchema_K2`  
_L391-411_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphSchema_K2`
- desc: Specific property bag schema to allow customizing the requirements (e.g. supported containers).
- L395 _public prototype_ `virtual bool SupportsPinTypeContainer(TWeakPtr<const FEdGraphSchemaAction> SchemaAction, const FEdGraphPinType& PinType, const EPinContainerType& ContainerType) const override;`
- L398 _public prototype_ `virtual UPropertyBagHierarchyRoot* GetHierarchyRoot(const TArray<UObject*>& ObjectsWithProperty) const;` — Retrieves the hierarchy root from the given objects that own the property bag. Optional.
- L401 _public prototype_ `virtual TArray<UScriptStruct*> GetHierarchyPropertyMetaDataTypes(const FPropertyBagPropertyDesc& Desc) const;` — Defines the property metadata for a given property. Useful if you want to add custom data to your properties.
- L404 _public prototype_ `virtual TSubclassOf<UPropertyBagHierarchyCategory> GetHierarchyCategoryType() const;` — Defines the category type within the hierarchy. Useful if you want to subclass and add your own properties.
- L407 _public prototype_ `virtual TSubclassOf<UPropertyBagHierarchySection> GetHierarchySectionType() const;` — Defines the section type within the hierarchy. Useful if you want to subclass and add your own properties.
- L410 _public prototype_ `virtual void TransferPropertyBagMetadataIntoHierarchy(const FInstancedPropertyBag& PropertyBag, UPropertyBagHierarchyRoot& HierarchyRoot) const;` — Post Load helper function. Override if you know what you are doing.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API STRUCTUTILSEDITOR_API`
- L80 _prototype_ `ENUM_CLASS_FLAGS(EPropertyBagChildRowFeatures);`
- L82 _namespace_ `namespace UE`
- L82 _namespace_ `namespace StructUtils` (scope `UE`)
- L84 _prototype_ `void SetPropertyDescFromPin(FPropertyBagPropertyDesc& Desc, const FEdGraphPinType& PinType);` (scope `UE::StructUtils`)
- L85 _prototype_ `FEdGraphPinType GetPropertyDescAsPin(const FPropertyBagPropertyDesc& Desc);` (scope `UE::StructUtils`)
- L86 _prototype_ `bool CanCreateValidGraphPinTypeForPropertyDesc(const FPropertyBagPropertyDesc& Desc);` (scope `UE::StructUtils`)
- L88 _prototype_ `TSharedRef<SWidget> CreateTypeSelectionWidget(TSharedPtr<IPropertyHandle> ChildPropertyHandle, const TSharedPtr<IPropertyHandle>& InBagStructProperty, const TSharedPtr<IPropertyUtilities>& InPropUtils, ESelectorType SelectorType, bool bAllowContainers = true, TSubclassOf<UEdGraphSchema> PropertyBagSchemaClass = nullptr);` (scope `UE::StructUtils`) — Creates type selection pill widget.
- L91 _prototype_ `const UPropertyBag* GetCommonBagStruct(TSharedPtr<IPropertyHandle> StructProperty);` (scope `UE::StructUtils`) — @return property bag struct common to all edited properties.
- L93 _prototype_ `TSubclassOf<UPropertyBagSchema> ExtractPropertyBagSchemaClass(TSharedRef<IPropertyHandle> InPropertyBagHandle);` (scope `UE::StructUtils`)
- L94 _prototype_ `const UPropertyBagSchema* ExtractPropertyBagSchemaCDO(TSharedRef<IPropertyHandle> InPropertyBagHandle);` (scope `UE::StructUtils`)
- L95 _prototype_ `UPropertyBagHierarchyRoot* ExtractHierarchyRoot(TSharedRef<IPropertyHandle> InPropertyBagHandle);` (scope `UE::StructUtils`)
- L105 _prototype_ `void ApplyChangesToPropertyDescs(const FText& SessionName, const TSharedPtr<IPropertyHandle>& StructProperty, TFunctionRef<void(TArray<FPropertyBagPropertyDesc>&)> Function);` (scope `UE::StructUtils`) — Allows the mutation of the property descriptors on a Property Bag property via the provided callback. Handles the whole transaction internally, including building a new Property Bag Struct (if necessary). @param SessionName Name of the transaction @param StructProperty The Property Bag handle @param Function The callback that does the mutation
- L108 _prototype_ `void ApplyChangesToPropertyDescs(const FText& SessionName, const TSharedPtr<IPropertyHandle>& StructProperty, const TSharedPtr<IPropertyUtilities>& PropUtils, TFunctionRef<void(TArray<FPropertyBagPropertyDesc>&)> Function);` (scope `UE::StructUtils`) — `UE_DEPRECATED(5.8, "Please use the version without the property utilities parameter.")`
- L119 _prototype_ `void ApplyChangesToSinglePropertyDesc(const FText& SessionName, const TSharedPtr<IPropertyHandle> PropertyHandle, const TSharedPtr<IPropertyHandle>& StructProperty, TFunctionRef<void(FPropertyBagPropertyDesc&)> Function);` (scope `UE::StructUtils`) — Allows the mutation of a single property descriptor on a Property Bag property via the provided callback. Handles the whole transaction internally, including building a new Property Bag Struct (if necessary). @param SessionName Name of the transaction @param PropertyHandle A child handle of the Property Bag to mutate @param StructProperty The Property Bag handle @param Function The callback that does the mutation
- L130 _prototype_ `void ApplyChangesToSinglePropertyDesc(const FText& SessionName, const FPropertyBagPropertyDesc& PropertyDesc, const TSharedPtr<IPropertyHandle>& StructProperty, TFunctionRef<void(FPropertyBagPropertyDesc&)> Function);` (scope `UE::StructUtils`) — Allows the mutation of a single property descriptor on a Property Bag property via the provided callback. Handles the whole transaction internally, including building a new Property Bag Struct (if necessary). @param SessionName Name of the transaction @param PropertyDesc The child descriptor to edit @param StructProperty The Property Bag handle @param Function The callback that does the mutation
- L133 _prototype_ `void ApplyChangesToSinglePropertyDesc(const FText& SessionName, const FPropertyBagPropertyDesc& PropertyDesc, const TSharedPtr<IPropertyHandle>& StructProperty, const TSharedPtr<IPropertyUtilities>& PropUtils, TFunctionRef<void(FPropertyBagPropertyDesc&)> Function);` (scope `UE::StructUtils`) — `UE_DEPRECATED(5.8, "Please use the version without the property utilities parameter.")`
- L207 _delegate_ `DECLARE_DELEGATE_OneParam(FPropertyBagPropertyDelegate, const FPropertyBagPropertyDesc& PropertyDesc) struct FConstructParams {` — Generic delegate to execute on a property description

### `Source/Editor/StructUtilsEditor/Public/PropertyBagDiff.h` (Public)


#### enum `UE::StructUtils::EPropertyBagDiffType`  
`enum class EPropertyBagDiffType : uint8`  
_L15-35_
- desc: Kind of difference detected between two property bag descriptors.
- L18 _public enumerator_ `Added` — ID present in New only.
- L20 _public enumerator_ `Removed` — ID present in Old only.
- L22 _public enumerator_ `Renamed` — Same ID, different Name.
- L24 _public enumerator_ `TypeChanged` — Same ID, !CompatibleType (or container / key types differ).
- L26 _public enumerator_ `ValueChanged` — Same ID, compatible type, value bytes differ.
- L28 _public enumerator_ `CategoryChanged` — Same ID, compatible type, the "Category" metadata key differs.
- L30 _public enumerator_ `MetaDataChanged` — Same ID, compatible type, a non-Category metadata key differs.
- L32 _public enumerator_ `FlagsChanged` — Same ID, PropertyFlags differ.
- L34 _public enumerator_ `Reordered` — Same ID, position relative to other surviving IDs changed.

#### struct `UE::StructUtils::FPropertyBagDiffEntry`  
`struct FPropertyBagDiffEntry`  
_L38-64_
- desc: Single difference between two property bag descriptors.
- L41 _public member_ `FGuid PropertyID;` — Stable identity of the property. Always set.
- L44 _public member_ `FName OldName = NAME_None;` — Name on the old side. NAME_None when DiffType == Added.
- L47 _public member_ `FName NewName = NAME_None;` — Name on the new side. NAME_None when DiffType == Removed.
- L50 _public member_ `EPropertyBagDiffType DiffType = EPropertyBagDiffType::ValueChanged;` — The kind of difference detected.
- L53 _public member_ `const FPropertyBagPropertyDesc* OldDesc = nullptr;` — Descriptor on the old side. Null when DiffType == Added.
- L56 _public member_ `const FPropertyBagPropertyDesc* NewDesc = nullptr;` — Descriptor on the new side. Null when DiffType == Removed.
- L63 _public member_ `FName MetaDataKey = NAME_None;` — For MetaDataChanged: the specific metadata key that differs. For CategoryChanged: NAME_None (key is implicitly "Category"). For all other diff types: NAME_None.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace StructUtils` (scope `UE`)
- L76 _prototype_ `void DiffPropertyBags(const FInstancedPropertyBag& Old, const FInstancedPropertyBag& New, TArray<FPropertyBagDiffEntry>& OutDiffs);` (scope `UE::StructUtils`) — Computes per-property differences between two property bags. Identity is matched by FPropertyBagPropertyDesc::ID so renames are detected as a single Renamed entry instead of an Added/Removed pair. One property may produce multiple entries when more than one dimension changed (e.g. Renamed + ValueChanged + CategoryChanged are emitted independently). The caller is responsible for keeping Old and New alive while iterating the returned descriptor pointers.

### `Source/Editor/StructUtilsEditor/Public/PropertyBagDragDropHandler.h` (Public)


#### enum `EPropertyBagDropState`  
`enum class EPropertyBagDropState`  
_L20-25_
- desc: State of the drop, useful for source-is-target validation on details rows.
- L22 _public enumerator_ `Invalid`
- L23 _public enumerator_ `Valid`
- L24 _public enumerator_ `SourceIsTarget`

#### class `FPropertyBagDetailsDragDropOp`  
`class FPropertyBagDetailsDragDropOp : public FGraphEditorDragDropAction`  
_L31-85_
- inherits: `FGraphEditorDragDropAction`
- desc: Provides information about the source row (single property or hierarchy element) being dragged. Inherits from FGraphEditorDragDropAction to support dragging to a graph pin/node/panel.
- L34 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FPropertyBagDetailsDragDropOp, FGraphEditorDragDropAction);`
- L49 _public prototype_ `FPropertyBagDetailsDragDropOp(const FPropertyBagPropertyDesc& InPropertyDesc);` — Property Bag Details - Drop Operation Constructor for property elements. @param InPropertyDesc Property description for the dropped property.
- L56 _public prototype_ `void SetDecoration(EPropertyBagDropState NewDropState, TOptional<FDecoration> OverriddenDecoration = {});` — Sets the pop up widget's icon and text. @param NewDropState The state of the drop operation. @param OverriddenDecoration An optional overridden decorator for the UI, including Message, Icon, and IconColor
- L60 _public prototype_ `virtual void HoverTargetChanged() override;` — Event when the drag and drop operation changes hover targets.
- L63 _public prototype_ `virtual EVisibility GetIconVisible() const override;` — Visibility of the cursor decorator icon.
- L65 _public prototype_ `virtual EVisibility GetErrorIconVisible() const override;` — Visibility of the cursor decorator error icon.
- L67 _public prototype_ `virtual FReply DroppedOnPin(const FVector2f& ScreenPosition, const FVector2f& GraphPosition) override;`
- L68 _public prototype_ `virtual FReply DroppedOnNode(const FVector2f& ScreenPosition, const FVector2f& GraphPosition) override;`
- L69 _public prototype_ `virtual FReply DroppedOnPanel(const TSharedRef<SWidget>& Panel, const FVector2f& ScreenPosition, const FVector2f& GraphPosition, UEdGraph& Graph) override;`
- L73 _public member_ `const FPropertyBagPropertyDesc PropertyDesc;` — The property description of the dragged property. May be default-constructed for non-property hierarchy elements.
- L75 _public member_ `EPropertyBagDropState CurrentDropState = EPropertyBagDropState::Invalid;` — Cached state for the decorator.
- L78 _public prototype_ `void SetHierarchyElement(TSharedPtr<FHierarchyElementViewModel> InElement);` — Optional hierarchy element view model for hierarchy-based drag & drop in the details panel.
- L79 _public prototype_ `TSharedPtr<FHierarchyElementViewModel> GetHierarchyElement() const;`
- L82 _private prototype_ `IPropertyBagEdGraphDragAndDrop* GetPropertyBagEdGraphDragAndDropInterface() const;`
- L84 _private member_ `TWeakPtr<FHierarchyElementViewModel> HierarchyElement;`

#### struct `FPropertyBagDetailsDragDropOp::FDecoration`  
`struct FDecoration`  
_L36-43_
- L38 _public prototype_ `explicit FDecoration(const FText& InMessage, const FSlateBrush* InIcon = nullptr, const FLinearColor& InColor = FLinearColor::White);`
- L40 _public member_ `const FText Message;`
- L41 _public member_ `const FSlateBrush* Icon;`
- L42 _public member_ `const FLinearColor IconColor;`

#### class `FPropertyBagDetailsDragDropHandlerTarget`  
`class FPropertyBagDetailsDragDropHandlerTarget : public IDetailDragDropHandler`  
_L88-118_
- inherits: `IDetailDragDropHandler`
- desc: Handles drag-and-drop (as a target) for a single property's child widget row.
- L91 _public prototype_ `FPropertyBagDetailsDragDropHandlerTarget() = default;`
- L93 _public prototype_ `FPropertyBagDetailsDragDropHandlerTarget(const FCanAcceptPropertyBagDetailsRowDropOp& CanAcceptDragDrop, const FOnPropertyBagDetailsRowDropOp& OnDragDrop);`
- L96 _public prototype_ `virtual TSharedPtr<FDragDropOperation> CreateDragDropOperation() const override;` — Creates the drag and drop operation. Disabled for the target. Enabled in subclasses.
- L98 _public prototype_ `virtual void BindCanAcceptDragDrop(FCanAcceptPropertyBagDetailsRowDropOp&& CanAcceptDragDrop);`
- L99 _public prototype_ `virtual void BindOnHandleDragDrop(FOnPropertyBagDetailsRowDropOp&& OnDragDrop);`
- L102 _public prototype_ `virtual void BindOnHandleHierarchyElementDrop(FOnPropertyBagHierarchyElementDropOp&& OnDrop);` — Bind a hierarchy-element-based drop handler. Used when the dropped element may not have a valid PropertyDesc (e.g. categories).
- L105 _public function_ `virtual bool UseHandleWidget() const override` — Disable automatic creation of the handle widget for targets. It is overridden in the source below.
- L111 _protected prototype_ `virtual TOptional<EItemDropZone> CanAcceptDrop(const FDragDropEvent& DragDropSource, EItemDropZone DropZone) const override;`
- L112 _protected prototype_ `virtual bool AcceptDrop(const FDragDropEvent& DragDropSource, EItemDropZone DropZone) const override;`
- L115 _private member_ `FCanAcceptPropertyBagDetailsRowDropOp CanAcceptDetailsRowDropOp;`
- L116 _private member_ `FOnPropertyBagDetailsRowDropOp OnHandleDetailsRowDropOp;`
- L117 _private member_ `FOnPropertyBagHierarchyElementDropOp OnHandleHierarchyElementDropOp;`

#### class `FPropertyBagDetailsDragDropHandler`  
`class FPropertyBagDetailsDragDropHandler : public FPropertyBagDetailsDragDropHandlerTarget`  
_L121-141_
- inherits: `FPropertyBagDetailsDragDropHandlerTarget`
- desc: Handles drag-and-drop (as a source or target) for a single property's child widget row.
- L124 _public prototype_ `FPropertyBagDetailsDragDropHandler(const FPropertyBagPropertyDesc& InPropertyDesc);`
- L127 _public function_ `void SetHierarchyElement(TSharedPtr<FHierarchyElementViewModel> InElement)` — Set an optional hierarchy element view model to attach to drag ops created by this handler.
- L130 _protected prototype_ `virtual TSharedPtr<FDragDropOperation> CreateDragDropOperation() const override;`
- L133 _protected function_ `virtual bool UseHandleWidget() const override` — Enable the automatic creation of the handle (grip) widget for the source.
- L137 _private member_ `const FPropertyBagPropertyDesc PropertyDesc;` — The current child row's property bag property description.
- L140 _private member_ `TWeakPtr<FHierarchyElementViewModel> HierarchyElement;` — Optional hierarchy element for hierarchy-based drag & drop.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API STRUCTUTILSEDITOR_API`
- L15 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(TOptional<EItemDropZone>, FCanAcceptPropertyBagDetailsRowDropOp, TSharedPtr<FPropertyBagDetailsDragDropOp> , EItemDropZone );`
- L15 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(TOptional<EItemDropZone>, FCanAcceptPropertyBagDetailsRowDropOp, TSharedPtr<FPropertyBagDetailsDragDropOp> , EItemDropZone );`
- L16 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnPropertyBagDetailsRowDropOp, const FPropertyBagPropertyDesc& , EItemDropZone );`
- L16 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnPropertyBagDetailsRowDropOp, const FPropertyBagPropertyDesc& , EItemDropZone );`
- L17 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnPropertyBagHierarchyElementDropOp, TSharedPtr<FHierarchyElementViewModel> , EItemDropZone );`
- L17 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnPropertyBagHierarchyElementDropOp, TSharedPtr<FHierarchyElementViewModel> , EItemDropZone );`

### `Source/Editor/StructUtilsEditor/Public/SInstancedStructPicker.h` (Public)


#### class `FInstancedStructFilter`  
`class FInstancedStructFilter : public IStructViewerFilter`  
_L19-45_
- inherits: `IStructViewerFilter`
- desc: Filter used by the instanced struct struct picker.
- L23 _public member_ `TWeakObjectPtr<const UScriptStruct> BaseStruct = nullptr;` — The base struct for the property that classes must be a child-of.
- L26 _public member_ `TArray<TSoftObjectPtr<const UScriptStruct>> AllowedStructs;` — The array of allowed structs
- L29 _public member_ `TArray<TSoftObjectPtr<const UScriptStruct>> DisallowedStructs;` — The array of disallowed structs
- L32 _public member_ `bool bAllowUserDefinedStructs = false;` — A flag controlling whether we allow UserDefinedStructs
- L35 _public member_ `bool bAllowBaseStruct = true;` — A flag controlling whether we allow to select the BaseStruct
- L38 _public member_ `bool bAllowChildStructs = true;` — A flag controlling whether we allow child structs of AllowedStructs / DisallowedStructs
- L40 _public prototype_ `virtual bool IsStructAllowed(const FStructViewerInitializationOptions& InInitOptions, const UScriptStruct* InStruct, TSharedRef<FStructViewerFilterFuncs> InFilterFuncs) override;`
- L41 _public prototype_ `virtual bool IsUnloadedStructAllowed(const FStructViewerInitializationOptions& InInitOptions, const FSoftObjectPath& InStructPath, TSharedRef<FStructViewerFilterFuncs> InFilterFuncs) override;`
- L44 _public member_ `TSharedPtr<IAssetReferenceFilter> AssetReferenceFilter;` — Optional filter to prevent selection of some structs e.g. ones in a plugin that is inaccessible from the object being edited

#### class `SInstancedStructPicker`  
`class SInstancedStructPicker : public SCompoundWidget`  
_L47-86_
- inherits: `SCompoundWidget`
- L50 _public function_ `SLATE_BEGIN_ARGS(SInstancedStructPicker)`
- L51 _public prototype_ `SLATE_EVENT(FOnStructPicked, OnStructPicked) SLATE_ARGUMENT(TArray<TSoftObjectPtr<const UScriptStruct>>, AllowedStructs) SLATE_ARGUMENT(TArray<TSoftObjectPtr<const UScriptStruct>>, DisallowedStructs) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<IPropertyHandle> InStructProperty, TSharedPtr<IPropertyUtilities> InPropertyUtils);`
- L58 _public prototype_ `const UScriptStruct* GetBaseScriptStruct() const;`
- L60 _public function_ `bool CanChangeStructType() const`
- L65 _public member_ `FOnStructPicked OnStructPicked;`
- L68 _private member_ `TSharedPtr<SComboButton> ComboButton;`
- L69 _private member_ `TSharedPtr<IPropertyHandle> StructProperty;`
- L70 _private member_ `TSharedPtr<IPropertyUtilities> PropUtils;`
- L73 _private member_ `bool bCanChangeStructType = true;` — Can we change the struct type at all? (controlled by the "StructTypeConst" meta-data)
- L76 _private member_ `TArray<TSoftObjectPtr<const UScriptStruct>> AllowedStructs;` — The array of allowed structs (additionally to the meta-data)
- L79 _private member_ `TArray<TSoftObjectPtr<const UScriptStruct>> DisallowedStructs;` — The array of disallowed structs (additionally to the meta-data)
- L81 _private prototype_ `FText GetDisplayValueString() const;`
- L82 _private prototype_ `FText GetTooltipText() const;`
- L83 _private prototype_ `const FSlateBrush* GetDisplayValueIcon() const;`
- L84 _private prototype_ `TSharedRef<SWidget> GenerateStructPicker();`
- L85 _private prototype_ `void StructPicked(const UScriptStruct* InStruct);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API STRUCTUTILSEDITOR_API`

### `Source/Editor/StructUtilsEditor/Public/StructUtilsDelegates.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace StructUtils` (scope `UE`)
- L9 _namespace_ `namespace Delegates` (scope `UE::StructUtils`)
- L13 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnUserDefinedStructReinstanced, const UUserDefinedStruct& );` — Called after the FInstancedStructs has been reinstantiated. E.g. safe to update UI.
- L13 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnUserDefinedStructReinstanced, const UUserDefinedStruct& );` (scope `UE::StructUtils::Delegates`) — Called after the FInstancedStructs has been reinstantiated. E.g. safe to update UI.
- L14 _externvar_ `extern FOnUserDefinedStructReinstanced OnUserDefinedStructReinstanced;` (scope `UE::StructUtils::Delegates`)

### `Source/Editor/StructUtilsEditor/Public/StructUtilsEditorModule.h` (Public)


#### struct `FPropertyBagHierarchyViewModelOwner`  
`struct FPropertyBagHierarchyViewModelOwner`  
_L33-47_
- desc: Shared owner for a UPropertyBagHierarchyViewModel. Holds the view model strongly. When the last TSharedPtr to this owner is released, the destructor finalizes the view model and marks it as garbage, stopping its editor tick deterministically and releasing it to the next GC pass. Consumers acquire one via FStructUtilsEditorModule::AcquireHierarchyViewModel and hold the returned TSharedPtr for as long as the view model is needed. Direct construction is not supported.
- L35 _public prototype_ `explicit FPropertyBagHierarchyViewModelOwner(UPropertyBagHierarchyViewModel* InViewModel);`
- L36 _public prototype_ `~FPropertyBagHierarchyViewModelOwner();`
- L38 _public prototype_ `FPropertyBagHierarchyViewModelOwner(const FPropertyBagHierarchyViewModelOwner&) = delete;`
- L39 _public prototype_ `FPropertyBagHierarchyViewModelOwner& operator=(const FPropertyBagHierarchyViewModelOwner&) = delete;`
- L40 _public prototype_ `FPropertyBagHierarchyViewModelOwner(FPropertyBagHierarchyViewModelOwner&&) = delete;`
- L41 _public prototype_ `FPropertyBagHierarchyViewModelOwner& operator=(FPropertyBagHierarchyViewModelOwner&&) = delete;`
- L43 _public function_ `UPropertyBagHierarchyViewModel* Get() const`
- L46 _private member_ `TStrongObjectPtr<UPropertyBagHierarchyViewModel> ViewModel;`

#### class `FStructUtilsEditorModule`  
`class FStructUtilsEditorModule : public IModuleInterface, public FStructureEditorUtils::INotifyOnStructChanged`  
_L52-88_
- inherits: `IModuleInterface,FStructureEditorUtils::INotifyOnStructChanged`
- desc: The public interface to this module
- L56 _public prototype_ `virtual void StartupModule() override;`
- L57 _public prototype_ `virtual void ShutdownModule() override;`
- L66 _public prototype_ `TSharedRef<FPropertyBagHierarchyViewModelOwner> AcquireHierarchyViewModel( UPropertyBagHierarchyRoot* InHierarchyRoot, UObject* InOwningObject, TSharedRef<FPropertyPath> InPropertyPath, TSharedRef<IPropertyUtilities> PropertyUtilities);` — Returns a shared owner of the hierarchy view model for the given root, creating one if needed. Hold the returned TSharedRef for as long as the view model is needed. When the last consumer drops it, the view model is finalized and marked as garbage, immediately stopping its editor tick. Subsequent calls for the same root will produce a fresh view model.
- L75 _protected prototype_ `virtual void PreChange(const class UUserDefinedStruct* Struct, FStructureEditorUtils::EStructureEditorChangeInfo Info) override;` — INotifyOnStructChanged
- L76 _protected prototype_ `virtual void PostChange(const class UUserDefinedStruct* Struct, FStructureEditorUtils::EStructureEditorChangeInfo Info) override;`
- L80 _private prototype_ `void OnPostGarbageCollect();`
- L83 _private member_ `TMap<TWeakObjectPtr<UPropertyBagHierarchyRoot>, TWeakPtr<FPropertyBagHierarchyViewModelOwner>> HierarchyViewModelMap;` — View model owner lookup by hierarchy root. Weak both ways. Strong ownership lives in TSharedPtr consumers.
- L85 _private member_ `TUniquePtr<FPropertyBagHierarchyViewModelPropertyEditorPolicy> HierarchyViewModelPropertyEditorPolicy;`
- L87 _private member_ `FDelegateHandle PostGarbageCollectHandle;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API STRUCTUTILSEDITOR_API`

### `Source/Editor/StructUtilsEditor/Public/StructUtilsEditorUtils.h` (Public)


#### struct `UE::StructUtils::FCreateUserDefinedStructArgs`  
`struct FCreateUserDefinedStructArgs`  
_L16-27_
- L19 _public member_ `EObjectFlags UserDefinedStructFlags = RF_Transactional | RF_Public;` — The default UserDefinedStruct flags.
- L21 _public member_ `bool bIsBlueprintType = true;` — Add the BlueprintType metadata to the struct.
- L26 _public member_ `bool bAddPropertyIDToPropertyName = false;` — The UserDefinedStruct editor appends the property ID to the property name. Whether the newly created User Defined Struct should reproduce the same behavior.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API STRUCTUTILSEDITOR_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace StructUtils` (scope `UE`)
- L36 _prototype_ `TValueOrError<UUserDefinedStruct*, void> CreateUserDefinedStructFromDescs(TNotNull<UObject*> UserDefinedStructOuter, const FInstancedPropertyBag& PropertyBag, FName UserDefinedStructName, const FCreateUserDefinedStructArgs& Args);` (scope `UE::StructUtils`) — @return a new user defined struct created from a property bag. Fails if the name is already used by another asset or if the asset could not be created or the FInstancedPropertyBag contains type that are not supported by UserDefinedStruct.
- L43 _prototype_ `TValueOrError<bool, void> UpdateUserDefinedStructFromDescs(TNotNull<UUserDefinedStruct*> Struct, const FInstancedPropertyBag& PropertyBag);` (scope `UE::StructUtils`) — Update, if needed, an existing user defined struct to have the exact same properties and default value as the property bag. @return true if an update occurs. Fails if FInstancedPropertyBag contains type that are not supported by UserDefinedStruct.

### `Source/Editor/StructUtilsEditor/Public/StructUtilsMetadata.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace StructUtils` (scope `UE`)
- L10 _namespace_ `namespace Metadata` (scope `UE::StructUtils`)
- L15 _externvar_ `extern const FLazyName HideInDetailPanelsName;` (scope `UE::StructUtils::Metadata`) — FInstancedPropertyBag
- L16 _externvar_ `extern const FLazyName ShowOnlyInnerPropertiesName;` (scope `UE::StructUtils::Metadata`)
- L19 _externvar_ `extern const FLazyName FixedLayoutName;` (scope `UE::StructUtils::Metadata`) — [Bag Property Metadata] FixedLayout: Indicates that the instanced property bag has a fixed layout and it is not possible to add/remove properties.
- L22 _externvar_ `extern const FLazyName DefaultTypeName;` (scope `UE::StructUtils::Metadata`) — [Bag Property Metadata] DefaultType: Default property type when adding a new Property. Should be taken from enum EPropertyBagPropertyType
- L25 _externvar_ `extern const FLazyName AllowContainersName;` (scope `UE::StructUtils::Metadata`) — [Bag Property Metadata] AllowContainers: By default it is always allowed to create containers (Array, Set) for properties. Use AllowContainers=false to disable container support.
- L28 _externvar_ `extern const FLazyName PropertyBagSchemaClassName;` (scope `UE::StructUtils::Metadata`) — [Bag Property Metadata] PropertyBagSchemaClass: Allow to specify the class for the PropertyBagSchema. Useful to specify which containers are available. If unset or invalid, fallback on UPropertyBagSchema.
- L31 _externvar_ `extern const FLazyName AllowArraysName;` (scope `UE::StructUtils::Metadata`) — `UE_DEPRECATED(5.6, "Remains for backwards compatibility. Please see 'AllowContainersName'.")`
- L34 _externvar_ `extern const FLazyName IsPinTypeAcceptedName;` (scope `UE::StructUtils::Metadata`) — [Bag Property Metadata] IsPinTypeAccepted: Name of a UFunction with signature bool(FEdGraphPinType). Returns false if the type should be discarded.
- L37 _externvar_ `extern const FLazyName CanRemovePropertyName;` (scope `UE::StructUtils::Metadata`) — [Bag Property Metadata] CanRemoveProperty: Name of a UFunction with signature bool(FGuid, FName). ID and name of the property that will be removed. Returns false if the property should not be removed.
- L40 _externvar_ `extern const FLazyName ChildRowFeaturesName;` (scope `UE::StructUtils::Metadata`) — [Bag Property Metadata] ChildRowFeatures: A list of UI features available to the PropertyBag properties when displayed in the details view child rows.
- L43 _externvar_ `extern const FLazyName ExtensionClass;` (scope `UE::StructUtils::Metadata`) — [Bag Property Metadata] ExtensionClass: Path of a class inheriting from UPropertyBagDetailsExtension
- L47 _externvar_ `extern const FLazyName EnableCategoriesName;` (scope `UE::StructUtils::Metadata`) — Common property metadata specifiers [Property Metadata] EnableCategoriesName: Required to enable the use of categories in general. Per property.
- L49 _externvar_ `extern const FLazyName CategoryName;` (scope `UE::StructUtils::Metadata`) — [Property Metadata] CategoryName: The name of the category (grouping of properties).
- L54 _externvar_ `extern const FLazyName BaseStructName;` (scope `UE::StructUtils::Metadata`) — Property metadata specifiers for FInstancedStruct/TInstancedStruct [PropertyMetadata] BaseStruct: Type name of the base class for the instanced struct
- L59 _externvar_ `extern const FLazyName BaseStructFunctionName;` (scope `UE::StructUtils::Metadata`) — [PropertyMetadata] BaseStructFunction: Name of a UFunction with signature UScriptStruct*(UE::StructUtils::FInstancedStructBaseStructQueryParams). Returns the type of the base struct for the instanced struct. (cf. InstancedStructBaseStructQueryParams.h for an example of function.) @note When return value is invalid, BaseStruct will be used if any.
- L62 _externvar_ `extern const FLazyName StructTypeConstName;` (scope `UE::StructUtils::Metadata`) — [PropertyMetadata] StructTypeConst: Determine whether the type of the instanced struct can be changed
- L65 _externvar_ `extern const FLazyName HideStructTypeName;` (scope `UE::StructUtils::Metadata`) — [PropertyMetadata] HideStructType: Determine whether the type of the instanced struct is visible
- L68 _prototype_ `bool AreCategoriesEnabled(const FPropertyBagPropertyDesc& Desc);` (scope `UE::StructUtils::Metadata`) — If organizing by category is enabled for this property.
- L70 _prototype_ `void EnableCategories(FPropertyBagPropertyDesc& OutDesc);` (scope `UE::StructUtils::Metadata`) — Enable category organization for this property.
- L72 _prototype_ `void DisableCategories(FPropertyBagPropertyDesc& OutDesc);` (scope `UE::StructUtils::Metadata`) — Disable category organization for this property.
- L74 _prototype_ `void SetCategory(FPropertyBagPropertyDesc& OutDesc, const FString& InGroupLabel, bool bAutoEnableCategories = true);` (scope `UE::StructUtils::Metadata`) — Set the category for this property.
- L76 _prototype_ `void RemoveCategory(FPropertyBagPropertyDesc& OutDesc, bool bAutoDisableCategories = true);` (scope `UE::StructUtils::Metadata`) — Remove the category for this property.
- L78 _prototype_ `FString GetCategory(const FPropertyBagPropertyDesc& InDesc);` (scope `UE::StructUtils::Metadata`) — Get the category for this property.
- L80 _namespace_ `namespace Specifiers` (scope `UE::StructUtils::Metadata`)
- L82 _externvar_ `extern const FLazyName ToolTipName;` (scope `UE::StructUtils::Metadata::Specifiers`)
- L83 _externvar_ `extern const FLazyName ClampMinName;` (scope `UE::StructUtils::Metadata::Specifiers`)
- L84 _externvar_ `extern const FLazyName ClampMaxName;` (scope `UE::StructUtils::Metadata::Specifiers`)
- L85 _externvar_ `extern const FLazyName UIMinName;` (scope `UE::StructUtils::Metadata::Specifiers`)
- L86 _externvar_ `extern const FLazyName UIMaxName;` (scope `UE::StructUtils::Metadata::Specifiers`)
- L87 _externvar_ `extern const FLazyName UnitsName;` (scope `UE::StructUtils::Metadata::Specifiers`)
- L88 _externvar_ `extern const FLazyName ForceUnitsName;` (scope `UE::StructUtils::Metadata::Specifiers`)
- L90 _prototype_ `bool SupportsClamping(const FPropertyBagPropertyDesc& InDesc);` (scope `UE::StructUtils::Metadata::Specifiers`)
- L91 _prototype_ `bool SupportsSettingUnits(const FPropertyBagPropertyDesc& InDesc);` (scope `UE::StructUtils::Metadata::Specifiers`)
