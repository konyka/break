# Editor / UniversalObjectLocatorEditor

- module root: `Source/Editor/UniversalObjectLocatorEditor`
- headers: 9; symbols: 154
- symbol kinds: class=9, enum=1, enumerator=2, function=10, macro=1, member=17, namespace=18, prototype=92, struct=3, typedef=1
- PrivateDependencyModuleNames: Core, CoreUObject, EditorWidgets, Engine, InputCore, MessageLog, PropertyEditor, SceneOutliner, Sequencer, Slate, SlateCore, UniversalObjectLocator, UnrealEd
- PublicDependencyModuleNames: PropertyEditor, SlateCore

### `Source/Editor/UniversalObjectLocatorEditor/Private/ActorLocatorEditor.h` (Private)


#### class `UE::UniversalObjectLocator::FActorLocatorEditor`  
`class FActorLocatorEditor : public ILocatorFragmentEditor`  
_L17-42_
- inherits: `ILocatorFragmentEditor`
- L19 _private prototype_ `ELocatorFragmentEditorType GetLocatorFragmentEditorType() const override;`
- L21 _private prototype_ `bool IsDragSupported(TSharedPtr<FDragDropOperation> DragOperation, UObject* Context) const override;`
- L23 _private prototype_ `UObject* ResolveDragOperation(TSharedPtr<FDragDropOperation> DragOperation, UObject* Context) const override;`
- L25 _private prototype_ `TSharedPtr<SWidget> MakeEditUI(const FEditUIParameters& InParameters) override;`
- L27 _private prototype_ `FText GetDisplayText(const FUniversalObjectLocatorFragment* InFragment = nullptr) const override;`
- L29 _private prototype_ `FText GetDisplayTooltip(const FUniversalObjectLocatorFragment* InFragment = nullptr) const override;`
- L31 _private prototype_ `FSlateIcon GetDisplayIcon(const FUniversalObjectLocatorFragment* InFragment = nullptr) const override;`
- L33 _private prototype_ `UClass* ResolveClass(const FUniversalObjectLocatorFragment& InFragment, UObject* InContext) const override;`
- L35 _private prototype_ `FUniversalObjectLocatorFragment MakeDefaultLocatorFragment() const override;`
- L39 _private prototype_ `AActor* GetActor(TWeakPtr<IFragmentEditorHandle> InWeakHandle) const;`
- L41 _private prototype_ `void OnSetActor(AActor* InActor, TWeakPtr<IFragmentEditorHandle> InWeakHandle);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UniversalObjectLocator` (scope `UE`)

### `Source/Editor/UniversalObjectLocatorEditor/Private/AnimInstanceLocatorEditor.h` (Private)


#### class `UE::UniversalObjectLocator::FAnimInstanceLocatorEditor`  
`class FAnimInstanceLocatorEditor : public ILocatorFragmentEditor`  
_L11-31_
- inherits: `ILocatorFragmentEditor`
- L14 _public prototype_ `ELocatorFragmentEditorType GetLocatorFragmentEditorType() const override;`
- L16 _public prototype_ `bool IsDragSupported(TSharedPtr<FDragDropOperation> DragOperation, UObject* Context) const override;`
- L18 _public prototype_ `UObject* ResolveDragOperation(TSharedPtr<FDragDropOperation> DragOperation, UObject* Context) const override;`
- L20 _public prototype_ `TSharedPtr<SWidget> MakeEditUI(const FEditUIParameters& InParameters) override;`
- L22 _public prototype_ `FText GetDisplayText(const FUniversalObjectLocatorFragment* InFragment) const override;`
- L24 _public prototype_ `FText GetDisplayTooltip(const FUniversalObjectLocatorFragment* InFragment) const override;`
- L26 _public prototype_ `FSlateIcon GetDisplayIcon(const FUniversalObjectLocatorFragment* InFragment) const override;`
- L28 _public prototype_ `UClass* ResolveClass(const FUniversalObjectLocatorFragment& InFragment, UObject* InContext) const override;`
- L30 _public prototype_ `FUniversalObjectLocatorFragment MakeDefaultLocatorFragment() const override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UniversalObjectLocator` (scope `UE`)

### `Source/Editor/UniversalObjectLocatorEditor/Private/AssetLocatorEditor.h` (Private)


#### class `UE::UniversalObjectLocator::FAssetLocatorEditor`  
`class FAssetLocatorEditor : public ILocatorFragmentEditor`  
_L15-39_
- inherits: `ILocatorFragmentEditor`
- L17 _private prototype_ `ELocatorFragmentEditorType GetLocatorFragmentEditorType() const override;`
- L19 _private prototype_ `bool IsDragSupported(TSharedPtr<FDragDropOperation> DragOperation, UObject* Context) const override;`
- L21 _private prototype_ `UObject* ResolveDragOperation(TSharedPtr<FDragDropOperation> DragOperation, UObject* Context) const override;`
- L23 _private prototype_ `TSharedPtr<SWidget> MakeEditUI(const FEditUIParameters& InParameters) override;`
- L25 _private prototype_ `FText GetDisplayText(const FUniversalObjectLocatorFragment* InFragment = nullptr) const override;`
- L27 _private prototype_ `FText GetDisplayTooltip(const FUniversalObjectLocatorFragment* InFragment = nullptr) const override;`
- L29 _private prototype_ `FSlateIcon GetDisplayIcon(const FUniversalObjectLocatorFragment* InFragment = nullptr) const override;`
- L31 _private prototype_ `UClass* ResolveClass(const FUniversalObjectLocatorFragment& InFragment, UObject* InContext) const override;`
- L33 _private prototype_ `FUniversalObjectLocatorFragment MakeDefaultLocatorFragment() const override;`
- L36 _private prototype_ `FAssetData GetAsset(TWeakPtr<IFragmentEditorHandle> InWeakHandle) const;`
- L38 _private prototype_ `void OnSetAsset(const FAssetData& InNewObject, TWeakPtr<IFragmentEditorHandle> InWeakHandle);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UniversalObjectLocator` (scope `UE`)

### `Source/Editor/UniversalObjectLocatorEditor/Private/UniversalObjectLocatorCustomization.h` (Private)


#### struct `UE::UniversalObjectLocator::FUniversalObjectLocatorCustomization`  
`struct FUniversalObjectLocatorCustomization final : public IPropertyTypeCustomization, public IUniversalObjectLocatorCustomization, public FSelfRegisteringEditorUndoClient`  
_L39-114_
- inherits: `IPropertyTypeCustomization,IUniversalObjectLocatorCustomization,FSelfRegisteringEditorUndoClient`
- L41 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L43 _public prototype_ `void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L44 _public prototype_ `void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L46 _public function_ `UObject* GetContext() const override`
- L47 _public prototype_ `UObject* GetSingleObject() const override;`
- L48 _public prototype_ `FString GetPathToObject() const override;`
- L49 _public prototype_ `void SetValue(FUniversalObjectLocator&& InNewValue) override;`
- L50 _public prototype_ `TSharedPtr<IPropertyHandle> GetProperty() const override;`
- L63 _private function_ `virtual void PostUndo(bool bSuccess) override`
- L64 _private function_ `virtual void PostRedo(bool bSuccess) override`
- L66 _private prototype_ `void RequestRebuild();`
- L67 _private prototype_ `void Rebuild();`
- L69 _private prototype_ `void TrimAbsoluteFragments();`
- L71 _private prototype_ `TSharedRef<SWidget> GetUserExposedFragmentTypeList(TWeakPtr<FFragmentItem> InWeakFragmentItem);`
- L72 _private prototype_ `FText GetFragmentText(TWeakPtr<FFragmentItem> InWeakFragmentItem) const;`
- L73 _private prototype_ `FText GetFragmentTooltipText(TWeakPtr<FFragmentItem> InWeakFragmentItem) const;`
- L74 _private prototype_ `const FSlateBrush* GetFragmentIcon(TWeakPtr<FFragmentItem> InWeakFragmentItem) const;`
- L76 _private prototype_ `TSharedRef<SWidget> GetFragmentTypeWidget(TWeakPtr<FFragmentItem> InWeakFragmentItem);`
- L78 _private prototype_ `bool HandleIsDragAllowed(TSharedPtr<FDragDropOperation> InDragOperation, TWeakPtr<FFragmentItem> InWeakFragmentItem);`
- L79 _private prototype_ `FReply HandleDrop(const FGeometry& InGeometry, const FDragDropEvent& InDropEvent, TWeakPtr<FFragmentItem> InWeakFragmentItem);`
- L81 _private prototype_ `void SetActor(AActor* InActor);`
- L83 _private prototype_ `const FCachedData& GetCachedData() const;`
- L85 _private prototype_ `FUniversalObjectLocator* GetCommonPropertyValue();`
- L86 _private prototype_ `const FUniversalObjectLocator* GetCommonPropertyValue() const;`
- L88 _private prototype_ `void ChangeEditorType(TWeakPtr<ILocatorFragmentEditor> InNewLocatorEditor, TWeakPtr<FFragmentItem> InWeakFragmentItem);`
- L89 _private prototype_ `bool CompareCurrentEditorType(TWeakPtr<ILocatorFragmentEditor> InNewLocatorEditor, TWeakPtr<FFragmentItem> InWeakFragmentItem) const;`
- L91 _private prototype_ `void RemoveFragment(TWeakPtr<FFragmentItem> InWeakFragmentItem);`
- L92 _private prototype_ `void ClearFragments();`
- L96 _private member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;`
- L97 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`
- L99 _private member_ `mutable FCachedData CachedData;`
- L101 _private member_ `TMap<FName, TSharedPtr<ILocatorFragmentEditor>> ApplicableLocators;`
- L103 _private member_ `mutable TArray<TSharedRef<FFragmentItem>> Fragments;`
- L105 _private member_ `TSharedPtr<SWidget> RootWidget;`
- L106 _private member_ `TSharedPtr<SWrapBox> WrapBox;`
- L108 _private member_ `TWeakObjectPtr<> WeakContext;`
- L109 _private member_ `TWeakObjectPtr<UClass> WeakContextClass;`
- L111 _private member_ `bool bRebuildRequested = false;`

#### struct `UE::UniversalObjectLocator::FUniversalObjectLocatorCustomization::FCachedData`  
`struct FCachedData`  
_L54-59_
- L56 _public member_ `TOptional<FUniversalObjectLocator> PropertyValue;`
- L57 _public member_ `TWeakObjectPtr<> WeakObject;`
- L58 _public member_ `FString ObjectPath;`

#### Free symbols / members of external scopes

- L33 _namespace_ `namespace UE`
- L33 _namespace_ `namespace UniversalObjectLocator` (scope `UE`)

### `Source/Editor/UniversalObjectLocatorEditor/Private/UniversalObjectLocatorEditorModule.h` (Private)


#### class `UE::UniversalObjectLocator::FUniversalObjectLocatorEditorModule`  
`class FUniversalObjectLocatorEditorModule : public IUniversalObjectLocatorEditorModule`  
_L16-38_
- inherits: `IUniversalObjectLocatorEditorModule`
- L21 _public prototype_ `void StartupModule() override;`
- L23 _public prototype_ `void ShutdownModule() override;`
- L25 _public prototype_ `void RegisterLocatorEditor(FName LocatorName, TSharedPtr<ILocatorFragmentEditor> LocatorEditor) override;`
- L27 _public prototype_ `void UnregisterLocatorEditor(FName LocatorName) override;`
- L29 _public prototype_ `TSharedPtr<ILocatorFragmentEditor> FindLocatorEditor(FName Name) override;`
- L31 _public prototype_ `void RegisterEditorContext(FName Name, TSharedPtr<ILocatorFragmentEditorContext> LocatorEditorContext) override;`
- L33 _public prototype_ `void UnregisterEditorContext(FName Name) override;`
- L35 _public member_ `TMap<FName, TSharedPtr<ILocatorFragmentEditor>> LocatorEditors;`
- L37 _public member_ `TMap<FName, TSharedPtr<ILocatorFragmentEditorContext>> LocatorEditorContexts;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UniversalObjectLocator` (scope `UE`)

### `Source/Editor/UniversalObjectLocatorEditor/Public/IUniversalObjectLocatorCustomization.h` (Public)


#### class `UE::UniversalObjectLocator::IFragmentEditorHandle`  
`class IFragmentEditorHandle`  
_L17-33_
- L20 _public prototype_ `virtual ~IFragmentEditorHandle() = default;`
- L23 _public prototype_ `virtual const FUniversalObjectLocatorFragment& GetFragment() const = 0;` — Get the fragment that this handle refers to
- L26 _public prototype_ `virtual const UClass* GetContextClass() const = 0;` — Get the context class that this fragment is resolved against
- L29 _public prototype_ `virtual const UClass* GetResolvedClass() const = 0;` — Get the class that this fragment is resolved to
- L32 _public prototype_ `virtual void SetValue(const FUniversalObjectLocatorFragment& InNewValue) = 0;` — Set the value of this fragment

#### class `UE::UniversalObjectLocator::IUniversalObjectLocatorCustomization`  
`class IUniversalObjectLocatorCustomization`  
_L35-46_
- L38 _public prototype_ `virtual ~IUniversalObjectLocatorCustomization() = default;`
- L40 _public prototype_ `virtual UObject* GetContext() const = 0;`
- L41 _public prototype_ `virtual UObject* GetSingleObject() const = 0;`
- L42 _public prototype_ `virtual FString GetPathToObject() const = 0;`
- L43 _public prototype_ `virtual void SetValue(FUniversalObjectLocator&& InNewValue) = 0;`
- L45 _public prototype_ `virtual TSharedPtr<IPropertyHandle> GetProperty() const = 0;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UniversalObjectLocator` (scope `UE`)

### `Source/Editor/UniversalObjectLocatorEditor/Public/IUniversalObjectLocatorEditorModule.h` (Public)


#### class `UE::UniversalObjectLocator::IUniversalObjectLocatorEditorModule`  
`class IUniversalObjectLocatorEditorModule : public IModuleInterface`  
_L16-41_
- inherits: `IModuleInterface`
- L23 _public prototype_ `virtual void RegisterLocatorEditor(FName Name, TSharedPtr<ILocatorFragmentEditor> LocatorEditor) = 0;` — Register a locator editor @param Name                     The name of the locator editor @param LocatorEditor            The locator editor to register
- L27 _public prototype_ `virtual void UnregisterLocatorEditor(FName Name) = 0;` — Unregister a locator editor previously registered via RegisterLocatorEditor @param Name                     The name of the locator editor
- L31 _public prototype_ `virtual TSharedPtr<ILocatorFragmentEditor> FindLocatorEditor(FName Name) = 0;` — Find a locator editor previously registered via RegisterLocatorEditor @param Name                     The name of the locator editor
- L36 _public prototype_ `virtual void RegisterEditorContext(FName Name, TSharedPtr<ILocatorFragmentEditorContext> LocatorEditorContext) = 0;` — Register a locator editor context, used to control editor behavior on a per-use basis @param Name                     The name of the context, used as an identifier @param LocatorEditorContext     The context to register
- L40 _public prototype_ `virtual void UnregisterEditorContext(FName Name) = 0;` — Unregister a locator editor context previously registered via RegisterEditorContext @param Name             The name of the context, used as an identifier

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UniversalObjectLocator` (scope `UE`)

### `Source/Editor/UniversalObjectLocatorEditor/Public/UniversalObjectLocatorEditor.h` (Public)


#### enum `UE::UniversalObjectLocator::ELocatorFragmentEditorType`  
`enum class ELocatorFragmentEditorType : uint8`  
_L26-33_
- L29 _public enumerator_ `Relative` — Locator fragment is relative to something else
- L32 _public enumerator_ `Absolute` — Locator fragment is absolute

#### class `UE::UniversalObjectLocator::ILocatorFragmentEditor`  
`class ILocatorFragmentEditor : public TSharedFromThis<ILocatorFragmentEditor>`  
_L35-112_
- inherits: `TSharedFromThis<ILocatorFragmentEditor>`
- L38 _public prototype_ `virtual ~ILocatorFragmentEditor() = default;`
- L42 _public prototype_ `virtual ELocatorFragmentEditorType GetLocatorFragmentEditorType() const = 0;` — Get the type of this locator editor (relative, absolute) @return the locator editor type
- L47 _public function_ `virtual bool IsAllowedInContext(FName InContextName) const` — Get whether this locator editor is allowed in the supplied context. @see ILocatorFragmentEditorContext. @param InContextName    The name of the context, if this is NAME_None, no context is supplied (the default for blueprint-instantiated UOL properties) @return true if this locator is allowed in the supplied context
- L53 _public prototype_ `virtual bool IsDragSupported(TSharedPtr<FDragDropOperation> InDragOperation, UObject* InContext) const = 0;` — Called to check whether a drag operation is supported for this fragment @param InDragOperation  The drag operation to check @param InContext        The context object @return true if the operation is supported, false if unsupported
- L59 _public prototype_ `virtual UObject* ResolveDragOperation(TSharedPtr<FDragDropOperation> InDragOperation, UObject* InContext) const = 0;` — Called to resolve a drag operation to an object @param InDragOperation  The drag operation to resolve @param InContext        The context object @return the resolved object
- L74 _public prototype_ `virtual TSharedPtr<SWidget> MakeEditUI(const FEditUIParameters& InParameters);` — Make the editor UI for this fragment (displayed in a context menu) @param InParameters     Parameters used to create the UI @return the editing widget
- L77 _public function_ `virtual TSharedPtr<SWidget> MakeEditUI(TSharedPtr<IUniversalObjectLocatorCustomization> Customization)` — `UE_DEPRECATED(5.5, "Please use MakeEditUI that takes a FEditUIParameters struct")`
- L80 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)` — `UE_DEPRECATED(5.5, "This method is mo longer used. Please use MakeEditUI to create your editor display within a popup window per-fragment")`
- L85 _public function_ `virtual FText GetDisplayText() const` — Get the text to display for the supplied fragment @param InFragment       The fragment to display. If this is nullptr then the name of the fragment type should be returned @return the text to display
- L86 _public prototype_ `virtual FText GetDisplayText(const FUniversalObjectLocatorFragment* InFragment) const = 0;`
- L91 _public function_ `virtual FText GetDisplayTooltip() const` — Get the tooltip text to display for this fragment @param InFragment       The fragment to display. If this is nullptr then the tooltip of the fragment type should be returned @return the tooltip text to display
- L92 _public prototype_ `virtual FText GetDisplayTooltip(const FUniversalObjectLocatorFragment* InFragment) const = 0;`
- L97 _public function_ `virtual FSlateIcon GetDisplayIcon() const` — Get the icon to display for this fragment @param InFragment       The fragment to display. If this is nullptr then the icon of the fragment type should be returned @return the icon to display
- L98 _public prototype_ `virtual FSlateIcon GetDisplayIcon(const FUniversalObjectLocatorFragment* InFragment) const = 0;`
- L104 _public prototype_ `virtual UClass* ResolveClass(const FUniversalObjectLocatorFragment& InFragment, UObject* InContext) const;` — Resolve the output class of a fragment at edit time @param InFragment       The fragment to resolve the class of @param InContext        The context to resolve the class against @return the class that was resolved from the fragment
- L108 _public prototype_ `virtual FUniversalObjectLocatorFragment MakeDefaultLocatorFragment() const = 0;` — Make a default fragment for the fragment type that this editor UI manipulates @return a default fragment for this locator editor to use
- L111 _public prototype_ `virtual FUniversalObjectLocator MakeDefaultLocator() const;` — `UE_DEPRECATED(5.5, "No longer required. Please override MakeDefaultLocatorFragment")`

#### struct `UE::UniversalObjectLocator::ILocatorFragmentEditor::FEditUIParameters`  
`struct FEditUIParameters`  
_L62-69_
- desc: Parameters used to create the UI for this locator fragment editor
- L65 _public member_ `TSharedRef<IUniversalObjectLocatorCustomization> Customization;` — The customization that is creating this UI
- L68 _public member_ `TSharedRef<IFragmentEditorHandle> Handle;` — The handle to the fragment to create the UI for

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UNIVERSALOBJECTLOCATOREDITOR_API`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace UniversalObjectLocator` (scope `UE`)
- L115 _typedef_ `typedef ILocatorFragmentEditor ILocatorEditor;` (scope `UE::UniversalObjectLocator`) — `UE_DEPRECATED(5.5, "Please use ILocatorFragmentEditor")`

### `Source/Editor/UniversalObjectLocatorEditor/Public/UniversalObjectLocatorEditorContext.h` (Public)


#### class `UE::UniversalObjectLocator::ILocatorFragmentEditorContext`  
`class ILocatorFragmentEditorContext : public TSharedFromThis<ILocatorFragmentEditorContext>`  
_L13-23_
- inherits: `TSharedFromThis<ILocatorFragmentEditorContext>`
- L16 _public prototype_ `virtual ~ILocatorFragmentEditorContext() = default;`
- L19 _public prototype_ `virtual UObject* GetContext(const IPropertyHandle& InPropertyHandle) const = 0;` — Get a context object that can be used to resolve partial fragments at edit time
- L22 _public function_ `virtual bool IsFragmentAllowed(FName InFragmentName) const` — Check whether the supplied locator fragment is supported in this context

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UniversalObjectLocator` (scope `UE`)
