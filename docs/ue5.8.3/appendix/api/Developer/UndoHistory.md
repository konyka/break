# Developer / UndoHistory

- module root: `Source/Developer/UndoHistory`
- headers: 6; symbols: 86
- symbol kinds: class=6, enum=1, enumerator=5, function=8, macro=1, member=23, namespace=4, prototype=33, struct=3, typedef=2
- PrivateDependencyModuleNames: ApplicationCore, CoreUObject, InputCore, Slate, SlateCore
- PublicDependencyModuleNames: Core

### `Source/Developer/UndoHistory/Private/UndoHistoryModule.h` (Private)


#### class `FUndoHistoryModule`  
`class FUndoHistoryModule : public IUndoHistoryModule`  
_L11-20_
- inherits: `IUndoHistoryModule`
- desc: Implements the UndoHistory module.
- L16 _public prototype_ `virtual void StartupModule() override;`
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L18 _public prototype_ `virtual bool SupportsDynamicReloading() override;`

### `Source/Developer/UndoHistory/Private/Widgets/ClassLookupReflectionDataProvider.h` (Private)


#### class `UE::UndoHistory::FClassLookupReflectionDataProvider`  
`class FClassLookupReflectionDataProvider : public IReflectionDataProvider`  
_L12-28_
- inherits: `IReflectionDataProvider`
- desc: Just uses LoadObject to look up class data. Works on editor builds but not on most programs, like MultiUserServer.
- L17 _public prototype_ `virtual bool HasClassDisplayName(const FSoftClassPath& ClassPath) const override;`
- L18 _public prototype_ `virtual TOptional<FString> GetClassDisplayName(const FSoftClassPath& ClassPath) const override;`
- L19 _public function_ `virtual bool SupportsGetPropertyReflectionData() const override`
- L20 _public prototype_ `virtual TOptional<FPropertyReflectionData> GetPropertyReflectionData(const FSoftClassPath& ClassPath, FName PropertyName) const override;`
- L25 _private prototype_ `TOptional<TNonNullPtr<UClass>> LookUpClass(const FSoftClassPath& ClassPath) const;`
- L26 _private prototype_ `TOptional<TNonNullPtr<FProperty>> LookUpProperty(const FSoftClassPath& ClassPath, FName PropertyName) const;`
- L27 _private prototype_ `EPropertyType GetPropertyType(const FProperty& Property) const;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UndoHistory` (scope `UE`)

### `Source/Developer/UndoHistory/Private/Widgets/UndoHistoryUtils.h` (Private)


#### class `FUndoHistoryUtils`  
`class FUndoHistoryUtils`  
_L10-88_
- L27 _public function_ `static TArray<FBasicPropertyInfo> GetChangedPropertiesInfo(const UE::UndoHistory::IReflectionDataProvider& ReflectionData, const FSoftClassPath& InObjectClass, const TArray<FName>& InChangedProperties)`
- L41 _private function_ `static TArray<FBasicPropertyInfo> GetChangedPropertiesInfoUsingReflectionInterface(const UE::UndoHistory::IReflectionDataProvider& ReflectionData, const FSoftClassPath& InObjectClass, const TArray<FName>& InChangedProperties)`
- L79 _private function_ `static TArray<FBasicPropertyInfo> GetChangedPropertiesWithoutReflectionInfo(const TArray<FName>& InChangedProperties)`

#### struct `FUndoHistoryUtils::FBasicPropertyInfo`  
`struct FBasicPropertyInfo`  
_L14-25_
- L16 _public member_ `FString PropertyName;`
- L17 _public member_ `FString PropertyType;`
- L18 _public member_ `EPropertyFlags PropertyFlags = CPF_None;`
- L20 _public function_ `FBasicPropertyInfo(FString InPropertyName, FString InPropertyType = FString(), EPropertyFlags InPropertyFlags = CPF_None) : PropertyName(MoveTemp(InPropertyName)) , PropertyType(MoveTemp(InPropertyType)) , PropertyFlags(InPropertyFlags)`

### `Source/Developer/UndoHistory/Public/IUndoHistoryModule.h` (Public)


#### class `IUndoHistoryModule`  
`class IUndoHistoryModule : public IModuleInterface`  
_L12-34_
- inherits: `IModuleInterface`
- desc: Interface for the UndoHistory module.
- L23 _public function_ `static IUndoHistoryModule& Get( )` — Gets a reference to the UndoHistory module instance. @todo gmp: better implementation using dependency injection. @return A reference to the module.
- L33 _public prototype_ `virtual ~IUndoHistoryModule( ) = default;` — Virtual destructor.

### `Source/Developer/UndoHistory/Public/Widgets/IReflectionDataProvider.h` (Public)


#### enum `UE::UndoHistory::EPropertyType`  
`enum class EPropertyType : uint8`  
_L10-17_
- L12 _public enumerator_ `ObjectProperty`
- L13 _public enumerator_ `StructProperty`
- L14 _public enumerator_ `EnumProperty`
- L15 _public enumerator_ `ArrayProperty`
- L16 _public enumerator_ `Other`

#### struct `UE::UndoHistory::FPropertyReflectionData`  
`struct FPropertyReflectionData`  
_L19-27_
- L22 _public member_ `FString CppMacroType;` — The result of FProperty::GetCPPMacroType (the part that is returned by ref, e.g. "FName").
- L24 _public member_ `FString TypeName;` — The result of FProperty::GetClass()::GetName()
- L25 _public member_ `EPropertyFlags PropertyFlags;`
- L26 _public member_ `EPropertyType PropertyType;`

#### class `UE::UndoHistory::IReflectionDataProvider`  
`class IReflectionDataProvider`  
_L36-49_
- desc: Provides reflection data to SUndoHistoryDetails. On editor builds reflection data is fully available however on non-editor builds there is no straightforward way of obtaining it. For example, Concert implements this interface to return data where available.
- L40 _public prototype_ `virtual bool HasClassDisplayName(const FSoftClassPath& ClassPath) const = 0;`
- L42 _public prototype_ `virtual TOptional<FString> GetClassDisplayName(const FSoftClassPath& ClassPath) const = 0;` — @return What UClass::GetName() would return, if available
- L44 _public prototype_ `virtual bool SupportsGetPropertyReflectionData() const = 0;`
- L46 _public prototype_ `virtual TOptional<FPropertyReflectionData> GetPropertyReflectionData(const FSoftClassPath& ClassPath, FName PropertyName) const = 0;` — @return Various misc data required for UI, e.g. for the type column
- L48 _public prototype_ `virtual ~IReflectionDataProvider() = default;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UndoHistory` (scope `UE`)
- L52 _prototype_ `TSharedRef<IReflectionDataProvider> CreateDefaultReflectionProvider();` (scope `UE::UndoHistory`) — Gets the default provider that just calls LoadObject. Works on editor builds. Will not work in most programs, like MultiUserServer.

### `Source/Developer/UndoHistory/Public/Widgets/SUndoHistoryDetails.h` (Public)


#### class `SUndoHistoryDetails`  
`class SUndoHistoryDetails : public SCompoundWidget`  
_L14-141_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SUndoHistoryDetails)`
- L28 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<UE::UndoHistory::IReflectionDataProvider> InReflectionData = UE::UndoHistory::CreateDefaultReflectionProvider());` — Construct this widget @param InArgs The declaration data for this widget.
- L33 _public prototype_ `void SetSelectedTransaction(const struct FTransactionDiff& InTransactionDiff);` — Set the transaction to be displayed in the details panel.
- L38 _public prototype_ `void Reset();` — Clear the details panel.
- L42 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface
- L47 _private typedef_ `using FUndoDetailsTreeNodePtr = TSharedPtr<FUndoDetailsTreeNode>;`
- L48 _private typedef_ `using FTreeItemTextFilter = TTextFilter<const FString&>;`
- L72 _private prototype_ `FUndoDetailsTreeNodePtr CreateTreeNode(const FString& InObjectPathName, const FSoftClassPath& InObjectClass, const TSharedPtr<FTransactionObjectEvent>& InEvent) const;` — Create a changed object node.
- L75 _private prototype_ `FText CreateToolTipText(EPropertyFlags InFlags) const;` — Create a tooltip text for a property.
- L78 _private prototype_ `bool SupportsTypeRow() const;` — Whether the type row will be generated
- L81 _private prototype_ `void OnFilterTextChanged(const FText& InFilterText);` — Callback to handle a change in the filter box.
- L84 _private prototype_ `void FullRefresh();` — Refresh the details tree view.
- L87 _private prototype_ `void PopulateSearchStrings(const FString&, TArray<FString>& OutSearchStrings) const;` — Populate the search strings for the filter.
- L90 _private prototype_ `void Populate();` — Populate the details tree.
- L93 _private prototype_ `TSharedRef<ITableRow> HandleGenerateRow(FUndoDetailsTreeNodePtr InNode, const TSharedRef<STableViewBase>& OwnerTable) const;` — Callback for generating a UndoHistoryDetailsRow
- L96 _private prototype_ `FText HandleGetFilterHighlightText() const;` — Callback for getting the filter highlight text.
- L99 _private prototype_ `EVisibility HandleDetailsVisibility() const;` — Callback for getting the details visibility.
- L102 _private prototype_ `FText HandleTransactionName() const;` — Callback for getting the transaction name.
- L105 _private prototype_ `FText HandleTransactionId() const;` — Callback for getting the transaction id.
- L108 _private prototype_ `void HandleTransactionIdNavigate();` — Callback for handling a click on the transaction id.
- L113 _private member_ `TSharedPtr<UE::UndoHistory::IReflectionDataProvider> ReflectionData;` — Gives us information about property data (gives programs the opportunity to inject custom handler since not all reflection data is available in programs).
- L116 _private member_ `TSharedPtr<STreeView<FUndoDetailsTreeNodePtr> > ChangedObjectsTreeView;` — Holds the ChangedObjects TreeView.
- L119 _private member_ `TArray<FUndoDetailsTreeNodePtr> ChangedObjects;` — Holds the ChangedObjects to be used as an ItemSource to the TreeView.
- L122 _private member_ `TArray<FUndoDetailsTreeNodePtr> FilteredChangedObjects;` — Holds the ChangedObjects to be displayed.
- L125 _private member_ `TSharedPtr<class SSearchBox> FilterTextBoxWidget;` — Holds the search box.
- L128 _private member_ `FText TransactionName;` — Holds the TransactionName.
- L131 _private member_ `FText TransactionId;` — Holds the TransactionId.
- L134 _private member_ `TSharedPtr<FTreeItemTextFilter> SearchBoxFilter;` — The TextFilter attached to the SearchBox widget of the UndoHistoryDetails panel.
- L137 _private member_ `bool bNeedsRefresh;` — If the details tree needs to be refreshed.
- L140 _private member_ `bool bNeedsExpansion;` — If the tree items need to be expanded (ie. When the filter text changes).

#### struct `SUndoHistoryDetails::FUndoDetailsTreeNode`  
`struct FUndoDetailsTreeNode`  
_L51-67_
- desc: Tree node representing a changed object and its changed properties as children.
- L53 _public member_ `FString Name;`
- L54 _public member_ `FString Type;`
- L55 _public member_ `FText ToolTip;`
- L56 _public member_ `TSharedPtr<FTransactionObjectEvent> TransactionEvent;`
- L57 _public member_ `TArray<FUndoDetailsTreeNodePtr> Children;`
- L58 _public member_ `int32 PathDepth = 0;`
- L60 _public function_ `FUndoDetailsTreeNode(FString InName, FString InType, FText InToolTip, TSharedPtr<FTransactionObjectEvent> InTransactionEvent = nullptr, int32 InPathDepth = 0) : Name(MoveTemp(InName)) , Type(MoveTemp(InType)) , ToolTip(MoveTemp(InToolTip)) , TransactionEvent(MoveTemp(InTransactionEvent)) , PathDepth(InPathDepth)`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UNDOHISTORY_API`
