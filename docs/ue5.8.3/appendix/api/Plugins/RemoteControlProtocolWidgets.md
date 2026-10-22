# Plugins / RemoteControlProtocolWidgets

- module root: `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlProtocolWidgets`
- headers: 25; symbols: 520
- symbol kinds: class=28, delegate=15, enum=7, enumerator=31, function=80, macro=1, member=138, namespace=6, prototype=205, struct=7, typedef=2
- PrivateDependencyModuleNames: Core, CoreUObject, EditorStyle, EditorSubsystem, EditorWidgets, Engine, GraphEditor, InputCore, Projects, PropertyEditor, RemoteControl, RemoteControlCommon, RemoteControlProtocol, Slate, SlateCore, StructUtilsEditor, UnrealEd

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlProtocolWidgets/Private/Customizations/RCSignatureProtocolActionCustomization.h` (Private)


#### class `FRCSignatureProtocolActionCustomization`  
`class FRCSignatureProtocolActionCustomization : public IDetailCustomization`  
_L9-20_
- inherits: `IDetailCustomization`
- L12 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L15 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L19 _private prototype_ `TArray<const FRCSignatureProtocolAction*, TInlineAllocator<1>> GetProtocolActions(IDetailLayoutBuilder& InDetailBuilder) const;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlProtocolWidgets/Private/ProtocolCommandChange.h` (Private)


#### class `TRemoteControlProtocolCommandChange`  
`template <typename ChangeArgsType> class TRemoteControlProtocolCommandChange final : public FCommandChange`  
_L11-27_
- inherits: `FCommandChange`
- L14 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnUndoRedoDelegate, URemoteControlPreset* , const ChangeArgsType& );`
- L16 _public prototype_ `TRemoteControlProtocolCommandChange(URemoteControlPreset* InPreset, ChangeArgsType&& InChangeArgs, FOnUndoRedoDelegate&& InOnApply, FOnUndoRedoDelegate&& InOnRevert);`
- L18 _public prototype_ `virtual void Apply(UObject* InObject) override;`
- L19 _public prototype_ `virtual void Revert(UObject* InObject) override;`
- L20 _public function_ `virtual FString ToString() const override`
- L23 _private member_ `TWeakObjectPtr<URemoteControlPreset> PresetPtr;`
- L24 _private member_ `ChangeArgsType ChangeArgs;`
- L25 _private member_ `FOnUndoRedoDelegate OnApply;`
- L26 _private member_ `FOnUndoRedoDelegate OnRevert;`
- L30 _function_ `template <typename ChangeArgsType> TRemoteControlProtocolCommandChange<ChangeArgsType>::TRemoteControlProtocolCommandChange(URemoteControlPreset* InPreset, ChangeArgsType&& InChangeArgs, FOnUndoRedoDelegate&& InOnApply, FOnUndoRedoDelegate&& InOnRevert) : PresetPtr(InPreset) , ChangeArgs(MoveTemp(InChangeArgs)) , OnApply(MoveTemp(InOnApply)) , OnRevert(MoveTemp(InOnRevert))`
- L38 _function_ `template <typename ChangeArgsType> void TRemoteControlProtocolCommandChange<ChangeArgsType>::Apply(UObject* InObject)`
- L47 _function_ `template <typename ChangeArgsType> void TRemoteControlProtocolCommandChange<ChangeArgsType>::Revert(UObject* InObject)`

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnUndoRedoDelegate, URemoteControlPreset* , const ChangeArgsType& );`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlProtocolWidgets/Private/RemoteControlProtocolWidgetsModule.h` (Private)


#### class `FRemoteControlProtocolWidgetsModule`  
`class FRemoteControlProtocolWidgetsModule : public IRemoteControlProtocolWidgetsModule`  
_L14-59_
- inherits: `IRemoteControlProtocolWidgetsModule`
- L19 _public prototype_ `virtual void StartupModule() override;`
- L20 _public prototype_ `virtual void ShutdownModule() override;`
- L24 _public prototype_ `virtual void AddProtocolBinding(const FName InProtocolName) override;`
- L25 _public prototype_ `virtual TSharedRef<SWidget> GenerateDetailsForEntity(URemoteControlPreset* InPreset, const FGuid& InFieldId, const EExposedFieldType& InFieldType) override;`
- L26 _public prototype_ `virtual void ResetProtocolBindingList() override;`
- L27 _public prototype_ `virtual TSharedPtr<IRCProtocolBindingList> GetProtocolBindingList() const override;`
- L28 _public prototype_ `virtual const FName GetSelectedProtocolName() const override;`
- L29 _public prototype_ `virtual FOnProtocolBindingAddedOrRemoved& OnProtocolBindingAddedOrRemoved() override;`
- L30 _public prototype_ `virtual FOnActiveProtocolChanged& OnActiveProtocolChanged() override;`
- L36 _private prototype_ `void OnBindingAdded(TSharedRef<FProtocolBindingViewModel> InBindingViewModel);` — Called when binding is added.
- L39 _private prototype_ `void OnBindingRemoved(FGuid InBindingId);` — Called when binding is removed.
- L42 _private prototype_ `void SetActiveProtocolName(const FName InProtocolName);` — Sets the selected protocol in the list and user setting.
- L44 _private prototype_ `void RegisterPropertyEditorCustomizations();`
- L45 _private prototype_ `void UnregisterPropertyEditorCustomizations();`
- L49 _private member_ `TSharedPtr<IRCProtocolBindingList> RCProtocolBindingList;` — Binding list public interface instance
- L52 _private member_ `FOnProtocolBindingAddedOrRemoved OnProtocolBindingAddedOrRemovedDelegate;` — Called when binding is added or removed.
- L55 _private member_ `FOnActiveProtocolChanged OnActiveProtocolChangedDelegate;` — Called when active protocol selection changed.
- L58 _private member_ `FName ActiveProtocolName;` — Holds the active protocol name.

#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRemoteControlProtocolWidgets, Log, All);`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlProtocolWidgets/Private/RemoteControlProtocolWidgetsSettings.h` (Private)


#### class `URemoteControlProtocolWidgetsSettings`  
`class URemoteControlProtocolWidgetsSettings : public UObject`  
_L15-27_
- reflection: `UCLASS(Config = RemoteControlProtocolWidgets)`
- inherits: `UObject`
- desc: Remote Control Protocol Widget Settings
- L22 _public member_ `TSet<FName> HiddenProtocolTypeNames;` — `UPROPERTY(Config, EditAnywhere, Category = Widgets)` — Protocol types to be hidden in the list view.
- L26 _public member_ `FName PreferredProtocol;` — `UPROPERTY(Config)` — Last protocol added. Used as default in the binding list.

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlProtocolWidgets/Private/Styling/ProtocolPanelStyle.h` (Private)


#### class `FProtocolPanelStyle`  
`class FProtocolPanelStyle`  
_L13-48_
- L19 _public prototype_ `static void Initialize();` — Initialize the style set.
- L24 _public prototype_ `static void Shutdown();` — Shutdown the style set.
- L29 _public prototype_ `static TSharedPtr<ISlateStyle> Get();` — Static getter for the style set.
- L34 _public prototype_ `static FName GetStyleSetName();` — Static getter for the style set name.
- L39 _private prototype_ `static FString InContent(const FString& RelativePath, const ANSICHAR* Extension);` — Get a path to the module's resources folder.
- L42 _private prototype_ `static void SetupWidgetStyles(TSharedRef<FSlateStyleSet> InStyle);` — Initializes Protocol Widget Styles.
- L47 _private member_ `static TSharedPtr<FSlateStyleSet> StyleSet;` — Holds the style set.

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlProtocolWidgets/Private/Styling/ProtocolStyles.h` (Private)


#### struct `FProtocolWidgetStyle`  
`struct FProtocolWidgetStyle : public FSlateWidgetStyle`  
_L18-63_
- reflection: `USTRUCT()`
- inherits: `FSlateWidgetStyle`
- desc: Represents all custom protocol widgets.
- L22 _public prototype_ `FProtocolWidgetStyle();`
- L23 _public function_ `virtual ~FProtocolWidgetStyle()`
- L26 _public prototype_ `virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;`
- L28 _public member_ `static const FName TypeName;`
- L29 _public function_ `virtual const FName GetTypeName() const override`
- L31 _public prototype_ `static const FProtocolWidgetStyle& GetDefault();`
- L36 _public member_ `FTextBlockStyle BoldTextStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Mask Button Bold Text Style
- L37 _public function_ `FProtocolWidgetStyle& SetBoldTextStyle(const FTextBlockStyle& InBoldTextStyle)`
- L41 _public member_ `FSlateBrush ContentAreaBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Brush used by the RC Panels to draw the content associated with this panel.
- L42 _public function_ `FProtocolWidgetStyle& SetContentAreaBrush(const FSlateBrush& InContentAreaBrush)`
- L46 _public member_ `FSlateBrush ContentAreaBrushDark;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Brush used by the RC Panels to draw the content associated with this panel (Dark).
- L47 _public function_ `FProtocolWidgetStyle& SetContentAreaBrushDark(const FSlateBrush& InContentAreaBrushDark)`
- L51 _public member_ `FSlateBrush ContentAreaBrushLight;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Brush used by the RC Panels to draw the content associated with this panel (Light).
- L52 _public function_ `FProtocolWidgetStyle& SetContentAreaBrushLight(const FSlateBrush& InContentAreaBrushLight)`
- L56 _public member_ `FCheckBoxStyle MaskButtonStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Style used for the mask button
- L57 _public function_ `FProtocolWidgetStyle& SetMaskButtonStyle(const FCheckBoxStyle& InMaskButtonStyle)`
- L61 _public member_ `FTextBlockStyle PlainTextStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Mask Button Plain Text Style
- L62 _public function_ `FProtocolWidgetStyle& SetPlainTextStyle(const FTextBlockStyle& InPlainTextStyle)`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlProtocolWidgets/Private/ViewModels/ProtocolBindingViewModel.h` (Private)


#### enum `ProtocolBindingViewModel::EValidity`  
`enum class EValidity : uint8`  
_L21-28_
- desc: Describes all possible validity states
- L23 _public enumerator_ `Unchecked = 0`
- L24 _public enumerator_ `Ok = 1` — Unchecked = 0,   Not yet checked
- L25 _public enumerator_ `InvalidChild = 2` — Ok = 1,   Valid
- L26 _public enumerator_ `DuplicateInput = 3` — InvalidChild = 2,   There are one or more errors in child viewmodels
- L27 _public enumerator_ `LessThanTwoRanges = 4` — DuplicateInput = 3,   Input event/channel, etc. is the same as another protocol binding

#### class `FProtocolBindingViewModel`  
`class FProtocolBindingViewModel : public TSharedFromThis<FProtocolBindingViewModel> , public FEditorUndoClient , public TRCValidatableViewModel<ProtocolBindingViewModel::EValidity> , public IRCTreeNodeViewModel`  
_L32-168_
- inherits: `TSharedFromThis<FProtocolBindingViewModel>,FEditorUndoClient,TRCValidatableViewModel<ProtocolBindingViewModel::EValidity>,IRCTreeNodeViewModel`
- desc: Represents a single protocol binding for an entity
- L40 _public prototype_ `static TSharedRef<FProtocolBindingViewModel> Create(const TSharedRef<FProtocolEntityViewModel>& InParentViewModel, const TSharedRef<FRemoteControlProtocolBinding>& InBinding);` — Create a new ViewModel for the given Entity and Protocol Binding.
- L44 _public prototype_ `FGuid AddRangeMapping();` — Add a new RangeMapping.
- L47 _public prototype_ `void RemoveRangeMapping(const FGuid& InId);` — Remove a RangeMapping by Id.
- L50 _public prototype_ `void RemoveAllRangeMappings();` — Removes all RangeMappings.
- L53 _public prototype_ `void AddDefaultRangeMappings();` — Creates default range mappings depending on the input and output types.
- L56 _public function_ `const FGuid& GetId() const` — Get the Binding Id.
- L59 _public function_ `TWeakObjectPtr<URemoteControlPreset> GetPreset() const` — Get the owning Preset.
- L62 _public function_ `TWeakFieldPtr<FProperty> GetProperty() const` — Get the bound FProperty. Should always be valid so long as the VM itself is valid.
- L65 _public prototype_ `FRemoteControlProtocolBinding* GetBinding() const;` — Get the underlying protocol binding instance.
- L68 _public prototype_ `TSharedPtr<IRemoteControlProtocol> GetProtocol() const;` — Get the bound protocol.
- L71 _public function_ `FText GetProtocolName() const` — Get the bound protocol name as Text.
- L74 _public function_ `const TArray<TSharedPtr<FProtocolRangeViewModel>>& GetRanges() const` — Get the Range ViewModels.
- L77 _public prototype_ `FRemoteControlProtocolMapping* GetRangesMapping(const FGuid& InRangeId) const;` — Get the underlying RangeMapping.
- L80 _public prototype_ `void Remove() const;` — Removes this Protocol Binding.
- L83 _public prototype_ `virtual bool GetChildren(TArray<TSharedPtr<IRCTreeNodeViewModel>>& OutChildren) override;` — Get logical children of this ViewModel
- L86 _public prototype_ `virtual bool IsValid(FText& OutMessage) override;` — Checks (non-critical, fixable) validity
- L89 _public prototype_ `bool IsValid() const;` — Checks validity of this ViewModel
- L92 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRangeMappingAdded, TSharedRef<FProtocolRangeViewModel> );`
- L93 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRangeMappingRemoved, FGuid );`
- L94 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnRangeMappingsRemoved);`
- L95 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnChanged);`
- L98 _public function_ `FOnRangeMappingAdded& OnRangeMappingAdded()` — When single range mapping added.
- L101 _public function_ `FOnRangeMappingRemoved& OnRangeMappingRemoved()` — When single range mapping removed.
- L104 _public function_ `FOnRangeMappingsRemoved& OnRangeMappingsRemoved()` — When all range mappings removed.
- L107 _public function_ `FOnChanged& OnChanged()` — Something has changed within the ViewModel.
- L110 _public prototype_ `void NotifyChanged() const;` — Allows the view to notify the ViewModel of a change (ie. from SDetailsView)
- L119 _public function_ `FProtocolBindingViewModel(FPrivateToken)`
- L120 _public prototype_ `FProtocolBindingViewModel(FPrivateToken, const TSharedRef<FProtocolEntityViewModel>& InParentViewModel, const TSharedRef<FRemoteControlProtocolBinding>& InBinding);`
- L123 _private prototype_ `void Initialize();`
- L125 _private prototype_ `TSharedPtr<FProtocolRangeViewModel>& AddRangeMappingInternal();`
- L128 _private prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L129 _private function_ `virtual void PostRedo(bool bSuccess) override`
- L134 _private member_ `static TMap<EValidity, FText> ValidityMessages;` — Message for each Validity state
- L140 _private member_ `TWeakObjectPtr<URemoteControlPreset> Preset;` — Owning Preset.
- L143 _private member_ `TWeakPtr<FProtocolEntityViewModel> ParentViewModel;` — Owning Entity (Property within a Preset).
- L146 _private member_ `TWeakFieldPtr<FProperty> Property;` — Bound property.
- L149 _private member_ `FGuid PropertyId;` — Unique Id of the bound Property.
- L152 _private member_ `FGuid BindingId;` — Unique Id of this protocol binding.
- L155 _private member_ `TArray<TSharedPtr<FProtocolRangeViewModel>> Ranges;` — Range ViewModels for this protocol binding.
- L158 _private member_ `FOnRangeMappingAdded OnRangeMappingAddedDelegate;` — When single range mapping added.
- L161 _private member_ `FOnRangeMappingRemoved OnRangeMappingRemovedDelegate;` — When single range mapping removed.
- L164 _private member_ `FOnRangeMappingsRemoved OnRangeMappingsRemovedDelegate;` — When all range mappings removed.
- L167 _private member_ `FOnChanged OnChangedDelegate;` — Something has changed within the ViewModel.

#### struct `FProtocolBindingViewModel::FPrivateToken`  
`struct FPrivateToken`  
_L116-116_
- desc: Private token only allows members or friends to call MakeShared
- L116 _public prototype_ `struct FPrivateToken` — Private token only allows members or friends to call MakeShared

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace ProtocolBindingViewModel`
- L92 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRangeMappingAdded, TSharedRef<FProtocolRangeViewModel> );`
- L93 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRangeMappingRemoved, FGuid );`
- L94 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnRangeMappingsRemoved);`
- L95 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnChanged);`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlProtocolWidgets/Private/ViewModels/ProtocolEntityViewModel.h` (Private)


#### enum `ProtocolEntityViewModel::EValidity`  
`enum class EValidity : uint8`  
_L16-23_
- desc: Describes all possible validity states
- L18 _public enumerator_ `Unchecked = 0`
- L19 _public enumerator_ `Ok = 1` — Unchecked = 0,   Not yet checked
- L20 _public enumerator_ `InvalidChild = 2` — Ok = 1,   Valid
- L21 _public enumerator_ `UnsupportedType = 3` — InvalidChild = 2,   There are one or more errors in child viewmodels
- L22 _public enumerator_ `Unbound = 4` — UnsupportedType = 3,   The input or output property types aren't supported

#### class `FProtocolEntityViewModel`  
`class FProtocolEntityViewModel : public TSharedFromThis<FProtocolEntityViewModel> , public FEditorUndoClient , public TRCValidatableViewModel<ProtocolEntityViewModel::EValidity> , public IRCTreeNodeViewModel`  
_L27-126_
- inherits: `TSharedFromThis<FProtocolEntityViewModel>,FEditorUndoClient,TRCValidatableViewModel<ProtocolEntityViewModel::EValidity>,IRCTreeNodeViewModel`
- desc: Contains all bindings for a given Entity (ie. Property)
- L35 _public prototype_ `static TSharedRef<FProtocolEntityViewModel> Create(URemoteControlPreset* InPreset, const FGuid& InEntityId);` — Create a new ViewModel for the given Preset and EntityId
- L39 _public prototype_ `bool CanAddBinding(const FName& InProtocolName, FText& OutMessage);` — Check if the bound entity type is supported by Protocol Binding
- L42 _public prototype_ `TSharedPtr<FProtocolBindingViewModel> AddBinding(const FName& InProtocolName);` — Add a new Protocol Binding
- L45 _public prototype_ `void RemoveBinding(const FGuid& InBindingId);` — Remove a Protocol Binding by Id
- L48 _public function_ `const FGuid& GetId() const` — Get the Entity Id
- L51 _public prototype_ `TWeakFieldPtr<FProperty> GetProperty();` — Get the bound FProperty
- L54 _public function_ `const TArray<TSharedPtr<FProtocolBindingViewModel>>& GetBindings() const` — Get the Protocol Binding ViewModels
- L57 _public prototype_ `TArray<TSharedPtr<FProtocolBindingViewModel>> GetFilteredBindings(const TSet<FName>& InHiddenProtocolTypeNames);` — Get the Protocol Binding ViewModels, filtered by the provided list of hidden protocol type names
- L60 _public prototype_ `bool IsBound() const;` — Checks if this entity is bound to one or more objects.
- L63 _public prototype_ `virtual bool GetChildren(TArray<TSharedPtr<IRCTreeNodeViewModel>>& OutChildren) override;` — Get logical children of this ViewModel
- L66 _public prototype_ `virtual bool IsValid(FText& OutMessage) override;` — Checks (non-critical, fixable) validity
- L69 _public prototype_ `bool IsValid() const;` — Checks validity of this ViewModel
- L72 _public prototype_ `URemoteControlPreset* GetPreset() const;` — Returns the preset of this view model or nullptr if there is no outer preset
- L75 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBindingAdded, TSharedRef<FProtocolBindingViewModel> );`
- L76 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBindingRemoved, FGuid );`
- L77 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnChanged);`
- L79 _public function_ `FOnBindingAdded& OnBindingAdded()`
- L80 _public function_ `FOnBindingRemoved& OnBindingRemoved()`
- L83 _public function_ `FOnChanged& OnChanged()` — Something has changed within the ViewModel
- L90 _public function_ `FProtocolEntityViewModel(FPrivateToken)`
- L91 _public prototype_ `FProtocolEntityViewModel(FPrivateToken, URemoteControlPreset* InPreset, const FGuid& InEntityId);`
- L94 _protected prototype_ `void Initialize();`
- L97 _protected prototype_ `void OnEntityUnexposed(URemoteControlPreset* InPreset, const FGuid& InEntityId);` — Respond when entity is unexposed
- L100 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L101 _protected function_ `virtual void PostRedo(bool bSuccess) override`
- L106 _private member_ `static TMap<EValidity, FText> ValidityMessages;` — Message for each Validity state
- L112 _private member_ `TWeakObjectPtr<URemoteControlPreset> Preset;` — Owning Preset
- L115 _private member_ `TWeakFieldPtr<FProperty> Property;` — Bound property
- L118 _private member_ `FGuid PropertyId;` — Unique Id of the bound Property
- L121 _private member_ `TArray<TSharedPtr<FProtocolBindingViewModel>> Bindings;` — Protocol Binding ViewModels for this Entity
- L123 _private member_ `FOnBindingAdded OnBindingAddedDelegate;`
- L124 _private member_ `FOnBindingRemoved OnBindingRemovedDelegate;`
- L125 _private member_ `FOnChanged OnChangedDelegate;`

#### struct `FProtocolEntityViewModel::FPrivateToken`  
`struct FPrivateToken`  
_L87-87_
- desc: Private token only allows members or friends to call MakeShared
- L87 _public prototype_ `struct FPrivateToken` — Private token only allows members or friends to call MakeShared

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace ProtocolEntityViewModel`
- L75 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBindingAdded, TSharedRef<FProtocolBindingViewModel> );`
- L76 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBindingRemoved, FGuid );`
- L77 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnChanged);`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlProtocolWidgets/Private/ViewModels/ProtocolRangeViewModel.h` (Private)


#### enum `ProtocolRangeViewModel::EValidity`  
`enum class EValidity : uint8`  
_L22-32_
- desc: Describes all possible validity states
- L24 _public enumerator_ `Unchecked = 0`
- L26 _public enumerator_ `Ok = 1` — Not yet checked
- L28 _public enumerator_ `DuplicateInput = 2` — Valid
- L30 _public enumerator_ `UnsupportedType = 3` — The input value is the same as another range input

#### class `FProtocolRangeViewModel`  
`class FProtocolRangeViewModel : public TSharedFromThis<FProtocolRangeViewModel> , public FEditorUndoClient , public TRCValidatableViewModel<ProtocolRangeViewModel::EValidity> , public IRCTreeNodeViewModel`  
_L36-194_
- inherits: `TSharedFromThis<FProtocolRangeViewModel>,FEditorUndoClient,TRCValidatableViewModel<ProtocolRangeViewModel::EValidity>,IRCTreeNodeViewModel`
- desc: Represents a single range mapping for a given protocol binding
- L44 _public prototype_ `static TSharedRef<FProtocolRangeViewModel> Create(const TSharedRef<FProtocolBindingViewModel>& InParentViewModel, const FGuid& InRangeId);` — Create a new ViewModel for the given Protocol Binding and Range Id
- L48 _public prototype_ `void CopyInputValue(const TSharedPtr<IPropertyHandle>& InDstHandle) const;` — Copy the input to the given PropertyHandle
- L51 _public prototype_ `void SetInputData(const TSharedPtr<IPropertyHandle>& InSrcHandle) const;` — Set input from raw data
- L55 _public function_ `template <typename ValueType> void SetInputValue(ValueType InValue, bool bWithTransaction = false)` — Set input
- L69 _public prototype_ `void CopyOutputValue(const TSharedPtr<IPropertyHandle>& InDstHandle) const;` — Copy the output to the given PropertyHandle
- L72 _public prototype_ `void SetOutputData(const TSharedPtr<IPropertyHandle>& InSrcHandle) const;` — Set underlying output from raw data
- L75 _public prototype_ `void SetOutputData(const FRCFieldResolvedData& InResolvedData) const;` — Set underlying output from resolved data
- L79 _public function_ `template <typename ValueType> void SetOutputValue(ValueType InValue, bool bWithTransaction = false)` — Set output
- L93 _public function_ `const FGuid& GetId() const` — Get the Range Id
- L96 _public function_ `const FGuid& GetBindingId() const` — Get the owning ProtocolBinding Id
- L99 _public function_ `const URemoteControlPreset* GetPreset() const` — Get the owning Preset
- L102 _public prototype_ `FName GetInputTypeName() const;` — Get the input TypeName
- L105 _public prototype_ `FProperty* GetInputProperty() const;` — Get the range input FProperty
- L108 _public prototype_ `UObject* GetInputContainer() const;` — Get the containing object of the input property, or nullptr if it doesn't exist
- L111 _public function_ `TWeakFieldPtr<FProperty> GetProperty() const` — Get the bound FProperty
- L114 _public prototype_ `UObject* GetOutputContainer() const;` — Get the containing object of the output property, or nullptr if it doesn't exist
- L117 _public prototype_ `void CopyFromCurrentPropertyValue() const;` — Copies current property value to this range's output value.
- L120 _public prototype_ `void Remove() const;` — Removes this Range Mapping
- L123 _public function_ `virtual bool GetChildren(TArray<TSharedPtr<IRCTreeNodeViewModel>>& OutChildren) override` — Get logical children of this ViewModel
- L126 _public prototype_ `virtual bool IsValid(FText& OutMessage) override;` — Checks (non-critical, fixable) validity
- L129 _public prototype_ `bool IsValid() const;` — Checks validity of this ViewModel
- L132 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnChanged);`
- L135 _public function_ `FOnChanged& OnChanged()` — Something has changed within the ViewModel
- L144 _public function_ `FProtocolRangeViewModel(FPrivateToken)`
- L145 _public prototype_ `FProtocolRangeViewModel(FPrivateToken, const TSharedRef<FProtocolBindingViewModel>& InParentViewModel, const FGuid& InRangeId);`
- L148 _protected prototype_ `void Initialize();`
- L151 _protected prototype_ `void UpdateInputValueRange();` — Updates the input range value clamping (in case the type/precision has changed).
- L153 _protected function_ `FRemoteControlProtocolMapping* GetRangesData() const`
- L154 _protected function_ `FRemoteControlProtocolBinding* GetBinding() const`
- L157 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L158 _protected function_ `virtual void PostRedo(bool bSuccess) override`
- L162 _protected prototype_ `void OnParentChanged();` — Parent ViewModel changed.
- L166 _private prototype_ `bool IsInputSame(const FProtocolRangeViewModel* InOther) const;` — Checks if the input value is the same as that of the other provided ViewModel.
- L169 _private member_ `static TMap<EValidity, FText> ValidityMessages;` — Message for each Validity state
- L172 _private member_ `EValidity CurrentValidity = EValidity::Unchecked;` — Last checked validity state.
- L176 _private member_ `TWeakObjectPtr<URemoteControlPreset> Preset;` — Owning Preset
- L179 _private member_ `TWeakPtr<FProtocolBindingViewModel> ParentViewModel;` — Owning ProtocolBinding
- L182 _private member_ `FGuid RangeId;` — Unique Id of this Range
- L184 _private member_ `FOnChanged OnChangedDelegate;`
- L187 _private member_ `uint64 PreviousRangeMaxValue = 0;` — Previous value of RangeTypeSize for comparison when changed.
- L190 _private member_ `TStrongObjectPtr<URCPropertyContainerBase> InputProxyPropertyContainer;` — A UObject container/owner for the input property
- L193 _private member_ `TStrongObjectPtr<URCPropertyContainerBase> OutputProxyPropertyContainer;` — A UObject container/owner for the output property

#### struct `FProtocolRangeViewModel::FPrivateToken`  
`struct FPrivateToken`  
_L139-139_
- desc: Private token only allows members or friends to call MakeShared
- L139 _public prototype_ `struct FPrivateToken` — Private token only allows members or friends to call MakeShared

#### Free symbols / members of external scopes

- L17 _macro_ `#define LOCTEXT_NAMESPACE "ProtocolBindingViewModel"`
- L19 _namespace_ `namespace ProtocolRangeViewModel`
- L132 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnChanged);`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlProtocolWidgets/Private/ViewModels/RCViewModelCommon.h` (Private)


#### class `TRCValidatableViewModel`  
`template <typename ValidityStateType> class TRCValidatableViewModel`  
_L12-28_
- desc: A base type of viewmodels with validation for display ValidityStateType must have an "Unchecked" and "Ok" member
- L15 _public typedef_ `typedef ValidityStateType EValidity;`
- L17 _public prototype_ `virtual ~TRCValidatableViewModel() = default;`
- L20 _public prototype_ `virtual bool IsValid(FText& OutMessage) = 0;` — Checks (non-critical, fixable) validity
- L23 _public function_ `virtual bool GetCurrentValidity() const` — Get last-checked validity. Note that this does not perform any validation itself.
- L27 _protected member_ `EValidity CurrentValidity = EValidity::Unchecked;` — Last checked validity state.

#### class `IRCTreeNodeViewModel`  
`class IRCTreeNodeViewModel`  
_L31-39_
- desc: Common interface for treeview nodes.
- L34 _protected prototype_ `~IRCTreeNodeViewModel() = default;`
- L38 _public prototype_ `virtual bool GetChildren(TArray<TSharedPtr<IRCTreeNodeViewModel>>& OutChildren) = 0;` — See STreeView::OnGetChildren, return false if no children.

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlProtocolWidgets/Private/Widgets/Masks/SRCProtocolBindingMask.h` (Private)


#### class `SRCProtocolBindingMask`  
`class SRCProtocolBindingMask : public SRCProtocolMaskTriplet, public IHasMaskExtensibility`  
_L14-42_
- inherits: `SRCProtocolMaskTriplet,IHasMaskExtensibility`
- desc: A widget that represents a mask (specific to protocol bindings).
- L17 _public function_ `SLATE_BEGIN_ARGS(SRCProtocolBindingMask)`
- L20 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FProtocolBindingViewModel>& InViewModel);`
- L28 _protected prototype_ `virtual bool CanBeMasked() const override;`
- L29 _protected prototype_ `virtual EMaskingType GetMaskingType() override;`
- L30 _protected prototype_ `virtual bool HasOptionalMask() const override;`
- L34 _protected prototype_ `virtual ECheckBoxState IsMaskEnabled(ERCMask InMaskBit) const override;`
- L35 _protected prototype_ `virtual void SetMaskEnabled(ECheckBoxState NewState, ERCMask NewMaskBit) override;`
- L41 _private member_ `TSharedPtr<FProtocolBindingViewModel> ViewModel;` — ViewModel for the Protocol Binding.

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlProtocolWidgets/Private/Widgets/Masks/SRCProtocolMaskButton.h` (Private)


#### class `SRCProtocolMaskButton`  
`class SRCProtocolMaskButton : public SBorder`  
_L22-126_
- inherits: `SBorder`
- desc: A custom widget represents a mask widget.
- L25 _public function_ `SLATE_BEGIN_ARGS(SRCProtocolMaskButton) : _MaskBit() , _MaskColor() , _DefaultLabel() , _OptionalTooltip()`
- L32 _public prototype_ `SLATE_ARGUMENT(ERCMask, MaskBit) SLATE_ARGUMENT(FLinearColor, MaskColor) SLATE_ATTRIBUTE(FText, DefaultLabel) SLATE_ATTRIBUTE(FText, OptionalTooltip) SLATE_EVENT(FIsMasked, IsMasked) SLATE_EVENT(FOnMaskStateChanged, OnMasked) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L52 _public function_ `ERCMask GetMaskBit() const` — Retrieves mask bit.
- L62 _public prototype_ `bool IsMasked() const;` — Returns true if the mask is currently enabled @return	True if masked, otherwise false
- L67 _public prototype_ `void ToggleMaskedState(bool bSoftToggle = false);` — Toggles the masked state for this mask button, fire events as needed
- L74 _protected prototype_ `FText HandleMaskTooltip() const;` — Retrieves the tooltip of the mask button based on its state.
- L79 _protected prototype_ `ECheckBoxState IsMaskEnabled() const;` — Retrieves the state of the mask.
- L84 _protected prototype_ `void SetMaskEnabled(ECheckBoxState NewState);` — Handles masked state.
- L89 _private member_ `TAttribute<FText> DefaultLabel;` — Holds the label of this mask button.
- L92 _private member_ `TAttribute<FText> OptionalToolTipText;` — Holds the tooltip text of this mask button.
- L95 _private member_ `ERCMask MaskBit;` — Holds the mask that should be affected by this button as an uint8.
- L98 _private member_ `FLinearColor MaskColor = FLinearColor::White;` — The color of the mask to set
- L101 _private member_ `TSharedPtr<SCheckBox> Mask;` — Holds a shared reference to the underlying mask button.
- L104 _private member_ `TSharedPtr<STextBlock> MaskLabel;` — Holds a shared reference to the underlying mask label.
- L107 _private member_ `TSharedPtr<SBorder> MaskBorder;` — Holds a shared reference to the underlying mask border.
- L110 _private member_ `static FText MaskText;` — Holds the "Mask" string as text.
- L113 _private member_ `static FText UnmaskText;` — Holds the "Unmask" string as text.
- L116 _private member_ `TAttribute<ECheckBoxState> MaskedState;` — Are we Masked
- L119 _private member_ `FIsMasked IsInMaskedState;` — Are we masked
- L122 _private member_ `FOnMaskStateChanged OnMaskStateChanged;` — Delegate called when the masking state changes.
- L125 _private member_ `const FProtocolWidgetStyle* WidgetStyle;` — Protocol Widget Style reference.

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(ECheckBoxState, FIsMasked, ERCMask );` — Delegate that is executed to retrieve the current mask state
- L14 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(ECheckBoxState, FIsMasked, ERCMask );` — Delegate that is executed to retrieve the current mask state
- L17 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnMaskStateChanged, ECheckBoxState , ERCMask );` — Delegate that is executed when the mask state changes
- L17 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnMaskStateChanged, ECheckBoxState , ERCMask );` — Delegate that is executed when the mask state changes

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlProtocolWidgets/Private/Widgets/Masks/SRCSignatureProtocolMaskProperty.h` (Private)


#### class `SRCSignatureProtocolMaskProperty`  
`class SRCSignatureProtocolMaskProperty : public SRCProtocolMaskTriplet`  
_L10-27_
- inherits: `SRCProtocolMaskTriplet`
- L13 _public function_ `SLATE_BEGIN_ARGS(SRCSignatureProtocolMaskProperty)`
- L14 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs , const TSharedRef<IPropertyHandle>& InMaskPropertyHandle , TConstArrayView<const FRCSignatureProtocolAction*> InProtocolActions);`
- L22 _private prototype_ `virtual ECheckBoxState IsMaskEnabled(ERCMask InMaskBit) const override;`
- L23 _private prototype_ `virtual void SetMaskEnabled(ECheckBoxState InNewState, ERCMask InNewMaskBit) override;`
- L26 _private member_ `TSharedPtr<IPropertyHandle> MaskPropertyHandle;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlProtocolWidgets/Private/Widgets/SPropertyView.h` (Private)


#### enum `EPropertyNameVisibility`  
`enum class EPropertyNameVisibility : uint8`  
_L17-22_
- desc: Controls visibility of the property name column
- L19 _public enumerator_ `Show = 0` — Always show the name column
- L20 _public enumerator_ `Hide = 1` — Never show the name column
- L21 _public enumerator_ `HideTopLevel = 2` — Hide if either: Property has no children, or is draw in one row; Property is the top-level/root, and has children

#### class `SPropertyView`  
`class SPropertyView final : public SCompoundWidget`  
_L27-234_
- inherits: `SCompoundWidget`
- desc: Represents a single property, including a struct.
- L80 _public function_ `SLATE_BEGIN_ARGS(SPropertyView) : _Object(nullptr) , _Struct(nullptr) , _RootPropertyName(NAME_None) , _NameVisibility(EPropertyNameVisibility::HideTopLevel) , _DisplayName({}) , _Spacing(0) , _ColumnPadding(false) , _ResizableColumn(true)`
- L90 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<RemoteControlProtocolWidgetUtils::FPropertyViewColumnSizeData>, ColumnSizeData) SLATE_ARGUMENT(UObject*, Object) SLATE_ARGUMENT(TSharedPtr<FStructOnScope>, Struct) SLATE_ARGUMENT(FName, RootPropertyName) SLATE_ARGUMENT(EPropertyNameVisibility, NameVisibility) SLATE_ARGUMENT(TOptional<FText>, DisplayName) SLATE_ARGUMENT(float, Spacing) SLATE_ARGUMENT(bool, ColumnPadding) SLATE_ARGUMENT(bool, ResizableColumn) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L107 _public prototype_ `void SetProperty(UObject* InNewObject, const FName InPropertyName);` — Set's the object/property pair
- L110 _public prototype_ `void SetStruct(UObject* InNewObject, TSharedPtr<FStructOnScope>& InStruct);` — Set's the object/struct pair
- L113 _public prototype_ `void Refresh();` — Force a refresh/rebuild
- L115 _public function_ `static int32 GetDesiredWidth()`
- L116 _public function_ `static void SetDesiredWidth(int32 InDesiredWidth)`
- L119 _public prototype_ `TSharedPtr<IPropertyHandle> GetPropertyHandle() const;` — Get the property handle for the property on this view
- L122 _public function_ `FOnFinishedChangingProperties& OnFinishedChangingProperties() const` — Get the FOnFinishedChangingProperties delegate from the underlying PropertyRowGenerator
- L128 _protected function_ `virtual FVector2D ComputeDesiredSize(float) const override` — #ueent_todo: This is temporary until we find a better solution to the splitter issue See SConstrainedBox's trick in cpp file
- L137 _private prototype_ `void ConstructInternal();` — Fills up the details view with the detail nodes created by the property row manager
- L140 _private prototype_ `void AddWidgets(const TArray<TSharedRef<class IDetailTreeNode>>& InDetailTree, int32& InIndex, float InLeftPadding);` — Add widgets held by array of DetailTreeNode objects
- L143 _private prototype_ `void AddCategoryWidget(const TSharedRef<IDetailTreeNode>& InDetailTree, int32& InOutIndex, float InLeftPadding);` — Add widget for a category node
- L146 _private prototype_ `void AddContainerWidget(const TSharedRef<IDetailTreeNode>& InDetailTree, int32& InOutIndex, float InLeftPadding);` — Add widget for a container node (array, etc.)
- L149 _private prototype_ `TSharedRef<SWidget> CreatePropertyWidget(const FPropertyWidgetCreationArgs& InCreationArgs);` — Creates a layout for the supplied Name/Value widgets according to the supplied creation options.
- L152 _private prototype_ `void CreateDefaultWidget(const FPropertyWidgetCreationArgs& InCreationArgs);` — Inserts a generic widget for a property row into the grid panel
- L155 _private function_ `void OnLeftColumnResized(float InNewWidth)` — Callback used by all splitters in the details view, so that they move in sync
- L161 _private function_ `float OnGetLeftColumnWidth() const`
- L162 _private function_ `float OnGetRightColumnWidth() const`
- L163 _private function_ `void OnSetColumnWidth(float InWidth)`
- L166 _private prototype_ `void OnObjectPropertyChanged(UObject* InObject, struct FPropertyChangedEvent& InEvent);` — Callback to track property changes
- L169 _private prototype_ `void OnPropertyChanged(const struct FPropertyChangedEvent& InEvent);` — Callback to track property changes
- L172 _private prototype_ `void OnObjectReplaced(const TMap<UObject*, UObject*>& InReplacementObjectMap);` — Callback used to detect the existence of a new object to display after a re-instancing process
- L175 _private prototype_ `void OnObjectTransacted(UObject* InObject, const class FTransactionObjectEvent& InTransactionObjectEvent);` — Callback to track object transactions (undo/redo)
- L178 _private prototype_ `bool RowHasInputContent(const TSharedPtr<SWidget>& InValueWidget) const;` — Semi-reliable check to see if a row is an empty header row or not (customized).
- L181 _private prototype_ `bool FindRootPropertyHandle(TArray<TSharedRef<class IDetailTreeNode>>& InOutNodes);` — Attempts to find the property specified by RootPropertyName, returns true if found.
- L185 _private member_ `TSharedPtr<class IPropertyRowGenerator> Generator;` — Row generator applied on detailed object.
- L188 _private member_ `TStrongObjectPtr<UObject> Object = nullptr;` — Object to be detailed.
- L191 _private member_ `FName RootPropertyName;` — Name of the root property represented.
- L194 _private member_ `EPropertyNameVisibility NameVisibility = EPropertyNameVisibility::Show;` — Display name visibility option.
- L197 _private member_ `TOptional<FText> DisplayNameOverride;` — Optional display name override.
- L200 _private member_ `TSharedPtr<IPropertyHandle> Property;` — Property represented by this widget.
- L203 _private member_ `TSharedPtr<FStructOnScope> Struct;` — Struct to be detailed.
- L206 _private member_ `FDelegateHandle OnPropertyChangedHandle;` — Delegate handle to track property changes (from this widget).
- L209 _private member_ `FDelegateHandle OnObjectReplacedHandle;` — Delegate handle to track new object after a re-instancing process.
- L212 _private member_ `FDelegateHandle OnObjectTransactedHandle;` — Delegate handle to track when a object was transacted.
- L215 _private member_ `FDelegateHandle OnObjectPropertyChangedHandle;` — Delegate handle to track property changes (from FCoreUObjectDelegates).
- L218 _private member_ `float ColumnWidth = 0;` — Relative width to control splitters.
- L221 _private member_ `TSharedPtr<RemoteControlProtocolWidgetUtils::FPropertyViewColumnSizeData> ColumnSizeData;` — Points to the currently used column size data. Can be provided via argument as well.
- L224 _private member_ `float Spacing = 0;` — Spacing between rows. 0 by default.
- L227 _private member_ `bool bResizableColumn = false;` — Indicates if the name and value widgets have a splitter and can be resized.
- L230 _private member_ `TSharedPtr<SGridPanel> GridPanel;` — Grid panel storing the row widgets.
- L233 _private member_ `static int32 DesiredWidth;` — Ideal total width of the widget.

#### struct `SPropertyView::FPropertyWidgetCreationArgs`  
`struct FPropertyWidgetCreationArgs`  
_L29-77_
- L31 _public function_ `FPropertyWidgetCreationArgs( const int32 InIndex, const TSharedPtr<SWidget>& InNameWidget, const TSharedPtr<SWidget>& InValueWidget, const float InLeftPadding, const TOptional<float>& InValueMinWidth = {}, const TOptional<float>& InValueMaxWidth = {}) : Index(InIndex) , NameWidget(InNameWidget) , ValueWidget(InValueWidget) , LeftPadding(InLeftPadding) , ValueMinWidth(InValueMinWidth) , ValueMaxWidth(InValueMaxWidth) , ColumnSizeData(nullptr) , Spacing(0.0f) , bResizableColumn(false)`
- L49 _public function_ `FPropertyWidgetCreationArgs( const FPropertyWidgetCreationArgs& InOther, const TSharedPtr<SWidget>& InNameWidget, const TSharedPtr<RemoteControlProtocolWidgetUtils::FPropertyViewColumnSizeData>& InColumnSizeData, const float InSpacing, const bool bInResizeableColumn) : Index(InOther.Index) , NameWidget(InNameWidget ? InNameWidget : InOther.NameWidget) , ValueWidget(InOther.ValueWidget) , LeftPadding(InOther.LeftPadding) , ValueMinWidth(InOther.ValueMinWidth) , ValueMaxWidth(InOther.ValueMaxWidth) , ColumnSizeData(InColumnSizeData) , Spacing(InSpacing) , bResizableColumn(bInResizeableColumn)`
- L66 _public member_ `int32 Index;`
- L67 _public member_ `TSharedPtr<SWidget> NameWidget;`
- L68 _public member_ `TSharedPtr<SWidget> ValueWidget;`
- L69 _public member_ `float LeftPadding;`
- L70 _public member_ `TOptional<float> ValueMinWidth;`
- L71 _public member_ `TOptional<float> ValueMaxWidth;`
- L72 _public member_ `TSharedPtr<RemoteControlProtocolWidgetUtils::FPropertyViewColumnSizeData> ColumnSizeData;`
- L73 _public member_ `float Spacing;`
- L74 _public member_ `bool bResizableColumn = true;`
- L76 _public function_ `bool HasNameWidget() const`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace RemoteControlProtocolWidgetUtils`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlProtocolWidgets/Private/Widgets/SRCBindingWarning.h` (Private)


#### enum `ERCBindingWarningStatus`  
`enum class ERCBindingWarningStatus : uint8`  
_L11-17_
- desc: Status severity.
- L13 _public enumerator_ `Ok = 0`
- L14 _public enumerator_ `Info = 1`
- L15 _public enumerator_ `Warning = 2`
- L16 _public enumerator_ `Error = 3`

#### class `SRCBindingWarning`  
`class SRCBindingWarning : public SCompoundWidget`  
_L20-44_
- inherits: `SCompoundWidget`
- desc: An icon/tooltip pair for validation.
- L23 _public function_ `SLATE_BEGIN_ARGS(SRCBindingWarning) : _Status(ERCBindingWarningStatus::Ok) , _StatusMessage(FText::GetEmpty())`
- L28 _public prototype_ `SLATE_ATTRIBUTE(ERCBindingWarningStatus, Status) SLATE_ATTRIBUTE(FText, StatusMessage) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The current status and severity.
- L40 _private member_ `TAttribute<ERCBindingWarningStatus> Status;` — The current status and severity.
- L43 _private member_ `TAttribute<FText> StatusMessage;` — The text displayed in the tooltip.

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlProtocolWidgets/Private/Widgets/SRCProtocolBinding.h` (Private)


#### class `SRCProtocolBinding`  
`class SRCProtocolBinding : public STableRow<TSharedPtr<FProtocolBindingViewModel>>`  
_L23-73_
- inherits: `STableRow<TSharedPtr<FProtocolBindingViewModel>>`
- L27 _public function_ `DECLARE_DELEGATE_OneParam(FOnStartRecording, TSharedPtr<TStructOnScope<FRemoteControlProtocolEntity>> ProtocolEntity) DECLARE_DELEGATE_OneParam(FOnStopRecording, TSharedPtr<TStructOnScope<FRemoteControlProtocolEntity>> ProtocolEntity) SLATE_BEGIN_ARGS(SRCProtocolBinding)` — Delegate when start recording input from protocol
- L34 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<RemoteControlProtocolWidgetUtils::FPropertyViewColumnSizeData>, PrimaryColumnSizeData) SLATE_ARGUMENT(TSharedPtr<RemoteControlProtocolWidgetUtils::FPropertyViewColumnSizeData>, SecondaryColumnSizeData) SLATE_EVENT(FOnStartRecording, OnStartRecording) SLATE_EVENT(FOnStopRecording, OnStopRecording) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, const TSharedRef<FProtocolBindingViewModel>& InViewModel);`
- L44 _private prototype_ `TSharedRef<SWidget> ConstructMaskingWidget();` — Constructs the masking widget.
- L47 _private prototype_ `FReply OnDelete();` — Called when Delete button pressed.
- L50 _private prototype_ `FReply ToggleRecording() const;` — Toggle recording button handler
- L53 _private prototype_ `FSlateColor GetRecordingButtonColor() const;` — Get Recording button color based on binding status of protocol entity
- L57 _private member_ `TSharedPtr<FProtocolBindingViewModel> ViewModel;` — ViewModel for the Protocol Binding.
- L60 _private member_ `TSharedPtr<SRCProtocolRangeList> RangeList;` — RangeList Widget.
- L63 _private member_ `TSharedPtr<RemoteControlProtocolWidgetUtils::FPropertyViewColumnSizeData> PrimaryColumnSizeData;` — Container used by all primary splitters in the details view, so that they move in sync
- L66 _private member_ `TSharedPtr<RemoteControlProtocolWidgetUtils::FPropertyViewColumnSizeData> SecondaryColumnSizeData;` — Container used by all secondary splitters in the details view, so that they move in sync
- L69 _private member_ `FOnStartRecording OnStartRecording;` — Start recording delegate instance
- L72 _private member_ `FOnStopRecording OnStopRecording;` — Stop recording delegate instance

#### Free symbols / members of external scopes

- L27 _delegate_ `DECLARE_DELEGATE_OneParam(FOnStartRecording, TSharedPtr<TStructOnScope<FRemoteControlProtocolEntity>> ProtocolEntity) DECLARE_DELEGATE_OneParam(FOnStopRecording, TSharedPtr<TStructOnScope<FRemoteControlProtocolEntity>> ProtocolEntity) SLATE_BEGIN_ARGS(SRCProtocolBinding) {} SLATE_ARGUMENT(TSharedPtr<RemoteControlProtocolWidgetUtils::FPropertyViewColumnSizeData>, PrimaryColumnSizeData) SLATE_ARGUMENT(TSharedPtr<RemoteControlProtocolWidgetUtils::FPropertyViewColumnSizeData>, SecondaryColumnSizeData) SLATE_EVENT(FOnStartRecording, OnStartRecording) SLATE_EVENT(FOnStopRecording, OnStopRecording) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, const TSharedRef<FProtocolBindingViewModel>& InViewModel);` — Delegate when start recording input from protocol
- L30 _delegate_ `DECLARE_DELEGATE_OneParam(FOnStopRecording, TSharedPtr<TStructOnScope<FRemoteControlProtocolEntity>> ProtocolEntity) SLATE_BEGIN_ARGS(SRCProtocolBinding) {} SLATE_ARGUMENT(TSharedPtr<RemoteControlProtocolWidgetUtils::FPropertyViewColumnSizeData>, PrimaryColumnSizeData) SLATE_ARGUMENT(TSharedPtr<RemoteControlProtocolWidgetUtils::FPropertyViewColumnSizeData>, SecondaryColumnSizeData) SLATE_EVENT(FOnStartRecording, OnStartRecording) SLATE_EVENT(FOnStopRecording, OnStopRecording) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, const TSharedRef<FProtocolBindingViewModel>& InViewModel);` — Delegate when stop recording input from protocol

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlProtocolWidgets/Private/Widgets/SRCProtocolBindingList.h` (Private)


#### class `SRCProtocolBindingList`  
`class SRCProtocolBindingList final : public SCompoundWidget, public IRCProtocolBindingList`  
_L20-125_
- inherits: `SCompoundWidget,IRCProtocolBindingList`
- desc: The root view for a given entity. A (vertical) list of bindings, where each binding has a protocol.
- L23 _public function_ `SLATE_BEGIN_ARGS(SRCProtocolBindingList)`
- L25 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FProtocolEntityViewModel> InViewModel);`
- L31 _public prototype_ `virtual void AddProtocolBinding(const FName InProtocolName) override;`
- L32 _public prototype_ `virtual URemoteControlPreset* GetPreset() const;`
- L35 _public function_ `virtual FRemoteControlProtocolEntitySet GetAwaitingProtocolEntities() const override` — Get the set of entities which is awaiting state and waiting for binding.
- L43 _private prototype_ `virtual void OnStartRecording(TSharedPtr<TStructOnScope<FRemoteControlProtocolEntity>> InEntity) override;` — Start recording incoming protocol message handler
- L46 _private prototype_ `virtual void OnStopRecording(TSharedPtr<TStructOnScope<FRemoteControlProtocolEntity>> InEntity) override;` — Stop recording incoming protocol message handler
- L49 _private prototype_ `virtual bool Refresh(bool bNavigateToEnd = false) override;` — Refresh protocol binding list. Returns false if the backing widget wasn't valid.
- L55 _private prototype_ `TSharedRef<ITableRow> ConstructBindingWidget(TSharedPtr<IRCTreeNodeViewModel> InViewModel, const TSharedRef<STableViewBase>& InOwnerTable);` — Constructs a single item in the list.
- L58 _private prototype_ `bool CanAddProtocol();` — Check if the bound entity type is supported by Protocol.
- L61 _private prototype_ `FText HandleAddBindingToolTipText() const;` — Retrieves the appropriate tooltip based on the active protocol.
- L64 _private function_ `float OnGetPrimaryLeftColumnWidth() const` — Primary Column is between Input and Output values.
- L69 _private function_ `float OnGetPrimaryRightColumnWidth() const`
- L74 _private function_ `void OnSetPrimaryColumnWidth(float InWidth)`
- L80 _private function_ `float OnGetSecondaryLeftColumnWidth() const` — Secondary Column is for output struct labels - doesn't apply when the type is drawn in a single row.
- L85 _private function_ `float OnGetSecondaryRightColumnWidth() const`
- L90 _private function_ `void OnSetSecondaryColumnWidth(float InWidth)`
- L97 _private member_ `TSharedPtr<FProtocolEntityViewModel> ViewModel;` — ViewModel for the Protocol Entity.
- L100 _private member_ `FText StatusMessage;` — Current status message, if any
- L103 _private member_ `TSharedPtr<SListView<TSharedPtr<IRCTreeNodeViewModel>>> BindingList;` — ListView widget for each protocol binding
- L106 _private member_ `TArray<TSharedPtr<IRCTreeNodeViewModel>> FilteredBindings;` — Binding view models, filtered by the current HiddenProtocolTypeNames list
- L109 _private member_ `TSharedPtr<RemoteControlProtocolWidgetUtils::FPropertyViewColumnSizeData> PrimaryColumnSizeData;` — Container used by all primary splitters in the details view, so that they move in sync
- L112 _private member_ `float PrimaryColumnWidth = 0.5f;` — Relative width to control primary splitters
- L115 _private member_ `TSharedPtr<RemoteControlProtocolWidgetUtils::FPropertyViewColumnSizeData> SecondaryColumnSizeData;` — Container used by all primary splitters in the details view, so that they move in sync
- L118 _private member_ `float SecondaryColumnWidth = 0.5f;` — Relative width to control secondary splitters
- L121 _private member_ `FRemoteControlProtocolEntitySet AwaitingProtocolEntities;` — Set of protocol entities with awaiting state and waiting for binding
- L124 _private member_ `TMap<FName, bool> ProtocolNameToSupportsAwaitingProtocolEntitiesMap;` — Map of protocol names and their support of awaiting protocol entities

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlProtocolWidgets/Private/Widgets/SRCProtocolEntity.h` (Private)


#### class `SRCProtocolEntity`  
`class SRCProtocolEntity : public SCompoundWidget`  
_L13-28_
- inherits: `SCompoundWidget`
- desc: Widget for a given FRemoteControlProtocolEntity implementation.
- L16 _public function_ `SLATE_BEGIN_ARGS(SRCProtocolEntity)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FProtocolBindingViewModel>& InViewModel);`
- L24 _private member_ `TSharedPtr<FProtocolBindingViewModel> ViewModel;` — ViewModel for a Protocol Binding.
- L27 _private prototype_ `TSharedRef<SWidget> CreateStructureDetailView();` — Creates the widget for the current Protocol Binding implementation struct.

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlProtocolWidgets/Private/Widgets/SRCProtocolRange.h` (Private)


#### class `SRCProtocolRange`  
`class SRCProtocolRange : public STableRow<TSharedPtr<FProtocolRangeViewModel>>`  
_L22-79_
- inherits: `STableRow<TSharedPtr<FProtocolRangeViewModel>>`
- L25 _public function_ `SLATE_BEGIN_ARGS(SRCProtocolRange)`
- L27 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<RemoteControlProtocolWidgetUtils::FPropertyViewColumnSizeData>, PrimaryColumnSizeData) SLATE_ARGUMENT(TSharedPtr<RemoteControlProtocolWidgetUtils::FPropertyViewColumnSizeData>, SecondaryColumnSizeData) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, const TSharedRef<FProtocolRangeViewModel>& InViewModel);`
- L35 _protected prototype_ `TSharedRef<SWidget> MakeInput();` — Resolve the input widget.
- L38 _protected prototype_ `TSharedRef<SWidget> MakeOutput();` — Resolve the output widget.
- L41 _protected prototype_ `FReply CopyFromCurrentPropertyValue() const;` — Copies current property value to this range's output value.
- L44 _protected prototype_ `FReply OnDelete() const;` — Called when this ProtocolRange is deleted.
- L47 _private member_ `FDelegateHandle OnInputProxyPropertyChangedHandle;`
- L48 _private member_ `FDelegateHandle OnOutputProxyPropertyChangedHandle;`
- L50 _private prototype_ `TSharedPtr<IPropertyHandle> GetInputPropertyHandle() const;`
- L51 _private prototype_ `TSharedPtr<IPropertyHandle> GetOutputPropertyHandle() const;`
- L54 _private prototype_ `void OnInputProxyChanged(const FPropertyChangedEvent& InEvent);` — Applies proxy data to actual.
- L57 _private prototype_ `void OnOutputProxyChanged(const FPropertyChangedEvent& InEvent);` — Applies proxy data to actual.
- L60 _private prototype_ `void OnViewModelChanged() const;` — Called whenever the viewmodel changes.
- L64 _protected member_ `TSharedPtr<FProtocolRangeViewModel> ViewModel;` — Represents an individual range binding for a protocol binding.
- L66 _protected member_ `TSharedPtr<SSplitter> Splitter;`
- L68 _protected member_ `TSharedPtr<IPropertyRowGenerator> InputPropertyRowGenerator;`
- L69 _protected member_ `TSharedPtr<SPropertyView> InputPropertyView;`
- L71 _protected member_ `TSharedPtr<IPropertyRowGenerator> OutputPropertyRowGenerator;`
- L72 _protected member_ `TSharedPtr<SPropertyView> OutputPropertyView;`
- L75 _protected member_ `TSharedPtr<RemoteControlProtocolWidgetUtils::FPropertyViewColumnSizeData> PrimaryColumnSizeData;` — Container used by all primary splitters in the details view, so that they move in sync
- L78 _protected member_ `TSharedPtr<RemoteControlProtocolWidgetUtils::FPropertyViewColumnSizeData> SecondaryColumnSizeData;` — Container used by all secondary splitters in the details view, so that they move in sync

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlProtocolWidgets/Private/Widgets/SRCProtocolRangeList.h` (Private)


#### class `SRCProtocolRangeList`  
`class SRCProtocolRangeList : public SCompoundWidget`  
_L19-65_
- inherits: `SCompoundWidget`
- L22 _public function_ `SLATE_BEGIN_ARGS(SRCProtocolRangeList)`
- L24 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<RemoteControlProtocolWidgetUtils::FPropertyViewColumnSizeData>, PrimaryColumnSizeData) SLATE_ARGUMENT(TSharedPtr<RemoteControlProtocolWidgetUtils::FPropertyViewColumnSizeData>, SecondaryColumnSizeData) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FProtocolBindingViewModel>& InViewModel);`
- L29 _public prototype_ `void GetDesiredWidth(float& OutMinDesiredWidth, float& OutMaxDesiredWidth);`
- L33 _private prototype_ `TSharedRef<SWidget> ConstructHeader();` — Constructs the header widget with array controls.
- L36 _private prototype_ `TSharedRef<SWidget> ConstructChannelMuter();` — Constructs  the channel muting widget (if supported for type).
- L39 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FProtocolRangeViewModel> InViewModel, const TSharedRef<STableViewBase>& InOwnerTable) const;` — Constructs an individual widget per range binding.
- L42 _private prototype_ `void OnRangeMappingAdded(TSharedRef<FProtocolRangeViewModel> InRangeViewModel) const;` — Called when a range mapping is added.
- L45 _private prototype_ `void OnRangeMappingRemoved(FGuid InRangeId) const;` — Called when a range mapping is removed.
- L48 _private prototype_ `void OnViewModelChanged() const;` — Called whenever the viewmodel changes.
- L51 _private prototype_ `void Refresh() const;` — Refresh ListView.
- L55 _private member_ `TSharedPtr<FProtocolBindingViewModel> ViewModel;` — Represents an individual protocol binding for an entity.
- L58 _private member_ `TSharedPtr<SListView<TSharedPtr<FProtocolRangeViewModel>>> ListView;` — Container widget for all range bindings.
- L61 _private member_ `TSharedPtr<RemoteControlProtocolWidgetUtils::FPropertyViewColumnSizeData> PrimaryColumnSizeData;` — Container used by all primary splitters in the details view, so that they move in sync.
- L64 _private member_ `TSharedPtr<RemoteControlProtocolWidgetUtils::FPropertyViewColumnSizeData> SecondaryColumnSizeData;` — Container used by all secondary splitters in the details view, so that they move in sync. Secondary splitter is used for struct name/value separation.

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlProtocolWidgets/Private/Widgets/SRCProtocolShared.h` (Private)


#### class `RemoteControlProtocolWidgetUtils::SConstrainedBox`  
`class SConstrainedBox : public SCompoundWidget`  
_L13-33_
- inherits: `SCompoundWidget`
- desc: Helper class to force a widget to fill in a space. Copied from SDetailSingleItemRow.cpp
- L16 _public function_ `SLATE_BEGIN_ARGS(SConstrainedBox) : _MinWidth() , _MaxWidth()`
- L20 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_ATTRIBUTE(TOptional<float>, MinWidth) SLATE_ATTRIBUTE(TOptional<float>, MaxWidth) SLATE_END_ARGS() virtual ~SConstrainedBox() = default;`
- L27 _public prototype_ `void Construct(const FArguments& InArgs);`
- L28 _public prototype_ `virtual FVector2D ComputeDesiredSize(float InLayoutScaleMultiplier) const override;`
- L31 _private member_ `TAttribute<TOptional<float>> MinWidth;`
- L32 _private member_ `TAttribute<TOptional<float>> MaxWidth;`

#### struct `RemoteControlProtocolWidgetUtils::FPropertyViewColumnSizeData`  
`struct FPropertyViewColumnSizeData`  
_L36-46_
- desc: Copied from SDetailsViewBase.h
- L38 _public member_ `TAttribute<float> LeftColumnWidth;`
- L39 _public member_ `TAttribute<float> RightColumnWidth;`
- L40 _public member_ `SSplitter::FOnSlotResized OnWidthChanged;`
- L42 _public function_ `void SetColumnWidth(float InWidth)`

#### class `RemoteControlProtocolWidgetUtils::SCustomSplitter`  
`class SCustomSplitter : public SSplitter`  
_L48-66_
- inherits: `SSplitter`
- L51 _public function_ `SLATE_BEGIN_ARGS(SCustomSplitter)`
- L53 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SWidget>, LeftWidget) SLATE_ARGUMENT(TSharedPtr<SWidget>, RightWidget) SLATE_ARGUMENT(TSharedPtr<FPropertyViewColumnSizeData>, ColumnSizeData) SLATE_END_ARGS();`
- L58 _public prototype_ `virtual ~SCustomSplitter() = default;`
- L60 _public prototype_ `void Construct(const FArguments& InArgs);`
- L62 _public prototype_ `virtual void OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const override;`
- L65 _private member_ `TSharedPtr<FPropertyViewColumnSizeData> ColumnSizeData;`

#### struct `RemoteControlProtocolWidgetUtils::FRCPropertyViewCustomizationInfo`  
`struct FRCPropertyViewCustomizationInfo`  
_L69-82_
- desc: Info about a given property customization
- L72 _public member_ `FName Id = NAME_None;` — A name to uniquely identify this info, ie. the path or type name.
- L75 _public member_ `bool bHasHeaderContent = false;` — Used to determine if the first row needs to be drawn or not.
- L78 _public member_ `TArray<float> ColumnSizes;` — Size of each column in a detail row.
- L81 _public member_ `TArray<FText> ColumnLabels;` — Label for each column in a detail row, if applicable (ie. X Y Z).

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace RemoteControlProtocolWidgetUtils`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlProtocolWidgets/Public/IRCProtocolBindingList.h` (Public)


#### class `IRCProtocolBindingList`  
`class IRCProtocolBindingList`  
_L14-39_
- desc: Interface class for RCProtocolBindingList widget
- L17 _public typedef_ `using FRemoteControlProtocolEntitySet = TSet<TSharedPtr<TStructOnScope<FRemoteControlProtocolEntity>>>;`
- L20 _public prototype_ `virtual ~IRCProtocolBindingList() = default;` — Virtual destructor
- L23 _public prototype_ `virtual URemoteControlPreset* GetPreset() const = 0;` — Returns the remote control preset for which this list is currently drawn
- L26 _public prototype_ `virtual void AddProtocolBinding(const FName InProtocolName) = 0;` — Adds a new protocol binding of specified type to the current view model.
- L29 _public prototype_ `virtual FRemoteControlProtocolEntitySet GetAwaitingProtocolEntities() const = 0;` — Get the set of entities which is awaiting state and waiting for binding
- L32 _public prototype_ `virtual void OnStartRecording(TSharedPtr<TStructOnScope<FRemoteControlProtocolEntity>> InEntity) = 0;` — Start recording incoming protocol message handler
- L35 _public prototype_ `virtual void OnStopRecording(TSharedPtr<TStructOnScope<FRemoteControlProtocolEntity>> InEntity) = 0;` — Stop recording incoming protocol message handler
- L38 _public prototype_ `virtual bool Refresh(bool bNavigateToEnd = false) = 0;` — Refresh protocol binding list. Returns false if the backing widget wasn't valid.

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlProtocolWidgets/Public/IRemoteControlProtocolWidgetsModule.h` (Public)


#### class `IRemoteControlProtocolWidgetsModule`  
`class IRemoteControlProtocolWidgetsModule : public IModuleInterface`  
_L19-54_
- inherits: `IModuleInterface`
- desc: A Remote Control module that provides editor widgets for protocol bindings.
- L28 _public function_ `static IRemoteControlProtocolWidgetsModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public prototype_ `virtual void AddProtocolBinding(const FName InProtocolName) = 0;` — Adds a new protocol binding of specified type to the current view model.
- L38 _public prototype_ `virtual TSharedRef<SWidget> GenerateDetailsForEntity(URemoteControlPreset* InPreset, const FGuid& InFieldId, const EExposedFieldType& InFieldType = EExposedFieldType::Invalid) = 0;` — Creates a widget for the given Preset Field and FieldType
- L41 _public prototype_ `virtual void ResetProtocolBindingList() = 0;` — Reset protocol binding widget
- L44 _public prototype_ `virtual TSharedPtr<IRCProtocolBindingList> GetProtocolBindingList() const = 0;` — Get the binding list public reference
- L47 _public prototype_ `virtual const FName GetSelectedProtocolName() const = 0;` — Get the selected protocol name.
- L50 _public prototype_ `virtual FOnProtocolBindingAddedOrRemoved& OnProtocolBindingAddedOrRemoved() = 0;` — Called when binding is added or removed.
- L53 _public prototype_ `virtual FOnActiveProtocolChanged& OnActiveProtocolChanged() = 0;` — Called when active protocol selection changed.

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnProtocolBindingAddedOrRemoved, ERCProtocolBinding::Op );`
- L14 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnProtocolBindingAddedOrRemoved, ERCProtocolBinding::Op );`
- L16 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnActiveProtocolChanged, const FName );`
- L16 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnActiveProtocolChanged, const FName );`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlProtocolWidgets/Public/Widgets/Masks/SRCProtocolMask.h` (Public)


#### class `SRCProtocolMask`  
`class SRCProtocolMask : public SRCProtocolMaskTriplet, public IHasMaskExtensibility`  
_L15-43_
- reflection: `UE_DEPRECATED(5.6, "SRCProtocolMask deprecated. Prefer using SRCProtocolMaskTriplet for mask widgets")`
- inherits: `SRCProtocolMaskTriplet,IHasMaskExtensibility`
- desc: A widget that represents a mask.
- L18 _public function_ `SLATE_BEGIN_ARGS(SRCProtocolMask)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TWeakPtr<FRemoteControlField> InField);`
- L29 _protected prototype_ `virtual bool CanBeMasked() const override;`
- L30 _protected prototype_ `virtual EMaskingType GetMaskingType() override;`
- L31 _protected prototype_ `virtual bool HasOptionalMask() const override;`
- L35 _protected prototype_ `virtual ECheckBoxState IsMaskEnabled(ERCMask InMaskBit) const override;`
- L36 _protected prototype_ `virtual void SetMaskEnabled(ECheckBoxState NewState, ERCMask NewMaskBit) override;`
- L42 _private member_ `TWeakPtr<FRemoteControlField> WeakField;` — Holds a weak reference to the housing RC field.

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlProtocolWidgets/Public/Widgets/Masks/SRCProtocolMaskTriplet.h` (Public)


#### enum `EMasking::Bits`  
`enum class Bits : uint8`  
_L14-23_
- L16 _public enumerator_ `ETM_A`
- L18 _public enumerator_ `ETM_B`
- L20 _public enumerator_ `ETM_C`
- L22 _public enumerator_ `ETM_D`

#### enum `EMaskingType`  
`enum class EMaskingType : uint8`  
_L26-39_
- L28 _public enumerator_ `Color`
- L30 _public enumerator_ `Polar`
- L32 _public enumerator_ `Rotator`
- L34 _public enumerator_ `Vector`
- L36 _public enumerator_ `Quat`
- L38 _public enumerator_ `Unsupported`

#### class `FRemoteControlProtocolMasking`  
`class FRemoteControlProtocolMasking`  
_L41-46_
- L44 _public prototype_ `static const TMap<UScriptStruct*, EMaskingType>& GetStructsToMaskingTypes();`
- L45 _public prototype_ `static const TSet<UScriptStruct*>& GetOptionalMaskStructs();`

#### class `SRCProtocolMaskTriplet`  
`class SRCProtocolMaskTriplet : public SBorder`  
_L51-119_
- inherits: `SBorder`
- desc: A widget that represents a triplet mask.
- L54 _public function_ `SLATE_BEGIN_ARGS(SRCProtocolMaskTriplet) : _MaskA() , _MaskB() , _MaskC() , _OptionalMask() , _EnableOptionalMask(false)`
- L61 _public prototype_ `SLATE_ARGUMENT(ERCMask, MaskA) SLATE_ARGUMENT(ERCMask, MaskB) SLATE_ARGUMENT(ERCMask, MaskC) SLATE_ARGUMENT(ERCMask, OptionalMask) SLATE_ARGUMENT(EMaskingType, MaskingType) SLATE_ATTRIBUTE(bool, CanBeMasked) SLATE_ARGUMENT(bool, EnableOptionalMask) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L81 _private prototype_ `FText GetMaskLabel(EMasking::Bits InMaskBitName) const;` — Retrieves the label of the mask button based on type.
- L88 _protected function_ `virtual ECheckBoxState IsMaskEnabled(ERCMask InMaskBit) const` — Retrieves the state of the mask.
- L91 _protected prototype_ `void LoadMasks();` — Soft toggles masks based on active masks.
- L96 _protected function_ `virtual void SetMaskEnabled(ECheckBoxState NewState, ERCMask NewMaskBit)` — Handles masked state.
- L101 _protected member_ `const FProtocolWidgetStyle* WidgetStyle;` — Protocol Widget Style reference.
- L106 _private member_ `EMaskingType MaskingType;` — Holds the type of this triplet mask.
- L109 _private member_ `TSharedPtr<SRCProtocolMaskButton> MaskA;` — Holds a shared reference to the underlying mask button for A.
- L112 _private member_ `TSharedPtr<SRCProtocolMaskButton> MaskB;` — Holds a shared reference to the underlying mask button for B.
- L115 _private member_ `TSharedPtr<SRCProtocolMaskButton> MaskC;` — Holds a shared reference to the underlying mask button for C.
- L118 _private member_ `TSharedPtr<SRCProtocolMaskButton> MaskD;` — Holds a shared reference to the underlying mask button for D.

#### class `IHasMaskExtensibility`  
`class IHasMaskExtensibility`  
_L124-140_
- desc: Ensures the maskability of the derived classes.
- L129 _private prototype_ `virtual bool CanBeMasked() const = 0;` — True when the derived classes supports masking, false otherwise.
- L134 _private prototype_ `virtual EMaskingType GetMaskingType() = 0;` — Retrieves the masking type based on the property type.
- L139 _private prototype_ `virtual bool HasOptionalMask() const = 0;` — True when derived classes has optional mask.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace EMasking`
