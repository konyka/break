# Plugins / PropertyAccessEditor

- module root: `Plugins/Runtime/PropertyAccess/Source/PropertyAccessEditor`
- headers: 2; symbols: 94
- symbol kinds: class=2, function=3, member=35, namespace=2, prototype=48, struct=4
- PrivateDependencyModuleNames: AnimGraph, BlueprintGraph, Engine, GraphEditor, InputCore, KismetWidgets, PropertyPath, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Slate

### `Plugins/Runtime/PropertyAccess/Source/PropertyAccessEditor/Private/PropertyAccessEditor.h` (Private)


#### class `FPropertyAccessLibraryCompiler`  
`class FPropertyAccessLibraryCompiler : public IPropertyAccessLibraryCompiler`  
_L36-130_
- inherits: `IPropertyAccessLibraryCompiler`
- desc: A helper structure used to compile a property access library
- L39 _public prototype_ `FPropertyAccessLibraryCompiler(FPropertyAccessLibrary* InLibrary, const UClass* InClass, const FOnPropertyAccessDetermineBatchId& InOnDetermineBatchId);`
- L42 _public prototype_ `virtual void BeginCompilation() override;` — IPropertyAccessLibraryCompiler interface
- L43 _public prototype_ `virtual FPropertyAccessHandle AddCopy(TArrayView<FString> InSourcePath, TArrayView<FString> InDestPath, const FName& InContextId, UObject* InAssociatedObject = nullptr) override;`
- L44 _public prototype_ `virtual FPropertyAccessHandle AddAccess(TArrayView<FString> InPath, UObject* InAssociatedObject = nullptr) override;`
- L45 _public prototype_ `virtual bool FinishCompilation() override;`
- L46 _public prototype_ `virtual void IterateErrors(TFunctionRef<void(const FText&, UObject*)> InFunction) const override;`
- L47 _public prototype_ `virtual FCompiledPropertyAccessHandle GetCompiledHandle(FPropertyAccessHandle InHandle) const override;`
- L48 _public prototype_ `virtual EPropertyAccessCopyType GetCompiledHandleAccessType(FPropertyAccessHandle InHandle) const override;`
- L111 _protected member_ `FPropertyAccessLibrary* Library;` — The library we are compiling
- L114 _protected member_ `const UClass* Class;` — The class we are compiling the library for
- L117 _protected member_ `FOnPropertyAccessDetermineBatchId OnDetermineBatchId;` — Delegate used to determine batch ID (index) for a particular copy context
- L120 _protected member_ `TArray<FQueuedCopy> QueuedCopies;` — All copies to process in FinishCompilation()
- L123 _protected member_ `TArray<FQueuedAccess> QueuedAccesses;` — All accesses to process in FinishCompilation()
- L126 _protected member_ `TMap<FPropertyAccessHandle, FCompiledPropertyAccessHandle> CopyMap;` — Copy map used to resolve handles
- L129 _protected member_ `TMap<FPropertyAccessHandle, FCompiledPropertyAccessHandle> AccessMap;` — Access map used to resolve handles

#### struct `FPropertyAccessLibraryCompiler::FQueuedCopy`  
`struct FQueuedCopy`  
_L52-83_
- desc: Stored copy info for processing in FinishCompilation()
- L55 _public member_ `TArray<FString> SourcePath;` — The path to copy from
- L58 _public member_ `TArray<FString> DestPath;` — The path to copy to
- L61 _public member_ `FName ContextId = NAME_None;` — The user-defined context ID
- L64 _public member_ `FText SourceErrorText;` — Error text associated with the source path
- L67 _public member_ `FText DestErrorText;` — Error text associated with the dest path
- L70 _public member_ `EPropertyAccessResolveResult SourceResult = EPropertyAccessResolveResult::Failed;` — Result of the source path resolution
- L73 _public member_ `EPropertyAccessResolveResult DestResult = EPropertyAccessResolveResult::Failed;` — Result of the dest path resolution
- L76 _public member_ `UObject* AssociatedObject = nullptr;` — Associated object, used to provide context for path resolution
- L79 _public member_ `int32 BatchId = INDEX_NONE;` — Batch Id
- L82 _public member_ `int32 BatchIndex = INDEX_NONE;` — Index within the batch

#### struct `FPropertyAccessLibraryCompiler::FQueuedAccess`  
`struct FQueuedAccess`  
_L86-105_
- desc: Stored access info for processing in FinishCompilation()
- L89 _public member_ `TArray<FString> Path;` — The path to access
- L92 _public member_ `FText ErrorText;` — Error text associated with the path
- L95 _public member_ `EPropertyAccessResolveResult Result = EPropertyAccessResolveResult::Failed;` — Result of the path resolution
- L98 _public member_ `UObject* AssociatedObject = nullptr;` — Associated object, used to provide context for path resolution
- L101 _public member_ `int32 AccessIndex = INDEX_NONE;` — Compiled access index
- L104 _public member_ `EPropertyAccessCopyType AccessType = EPropertyAccessCopyType::None;` — Compiled access type

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace PropertyAccess`
- L14 _prototype_ `extern FPropertyAccessResolveResult ResolvePropertyAccess(const UStruct* InStruct, TArrayView<const FString> InPath, FProperty*& OutProperty, int32& OutArrayIndex);` (scope `PropertyAccess`) — Resolve a property path to a structure, returning the leaf property and array index if any. @return true if resolution succeeded
- L20 _prototype_ `extern FPropertyAccessResolveResult ResolvePropertyAccess(const UStruct* InStruct, TArrayView<const FString> InPath, const IPropertyAccessEditor::FResolvePropertyAccessArgs& InArgs);` (scope `PropertyAccess`) — Resolve a property path to a structure, calling back for each segment in path segment order if resolution succeed @return true if resolution succeeded
- L23 _prototype_ `extern EPropertyAccessCompatibility GetPropertyCompatibility(const FProperty* InPropertyA, const FProperty* InPropertyB);` (scope `PropertyAccess`) — Get the compatibility of the two supplied properties. Ordering matters for promotion (A->B).
- L26 _prototype_ `extern EPropertyAccessCompatibility GetPinTypeCompatibility(const FEdGraphPinType& InPinTypeA, const FEdGraphPinType& InPinTypeB);` (scope `PropertyAccess`) — Get the compatibility of the two supplied pins. Ordering matters for promotion (A->B).
- L29 _prototype_ `extern void MakeStringPath(const TArray<FBindingChainElement>& InBindingChain, TArray<FString>& OutStringPath);` (scope `PropertyAccess`) — Makes a string path from a binding chain
- L32 _prototype_ `extern FText MakeTextPath(const TArray<FString>& InPath, const UStruct* InStruct);` (scope `PropertyAccess`) — Makes a text path from an array of path segments

### `Plugins/Runtime/PropertyAccess/Source/PropertyAccessEditor/Private/SPropertyBinding.h` (Private)


#### class `SPropertyBinding`  
`class SPropertyBinding : public SCompoundWidget`  
_L15-123_
- inherits: `SCompoundWidget`
- L19 _public function_ `SLATE_BEGIN_ARGS(SPropertyBinding)`
- L21 _public prototype_ `SLATE_ARGUMENT(FPropertyBindingWidgetArgs, Args) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UBlueprint* InBlueprint, const TArray<FBindingContextStruct>& InBindingContextStructs);`
- L27 _public prototype_ `static void FillPropertyMenu(FMenuBuilder& MenuBuilder, const FPropertyBindingWidgetArgs& Args, const UBlueprint* Blueprint, FName PropertyName, UStruct* InOwnerStruct, TArray<TSharedPtr<FBindingChainElement>> InBindingChain);`
- L58 _protected prototype_ `TSharedRef<SWidget> OnGenerateDelegateMenu();`
- L59 _protected prototype_ `void FillPropertyMenu(FMenuBuilder& MenuBuilder, UStruct* InOwnerStruct, TArray<TSharedPtr<FBindingChainElement>> InBindingChain);`
- L60 _protected prototype_ `void FillCategoryMenu(FMenuBuilder& MenuBuilder, const FBindingContextStructCategory* Category);`
- L62 _protected prototype_ `const FSlateBrush* GetLinkIcon() const;`
- L63 _protected prototype_ `const FSlateBrush* GetCurrentBindingImage() const;`
- L64 _protected prototype_ `FText GetCurrentBindingText() const;`
- L65 _protected prototype_ `FSlateColor GetCurrentBindingTextColor() const;`
- L66 _protected prototype_ `FText GetCurrentBindingToolTipText() const;`
- L67 _protected prototype_ `FSlateColor GetCurrentBindingColor() const;`
- L69 _protected prototype_ `bool CanRemoveBinding();`
- L70 _protected prototype_ `void HandleRemoveBinding();`
- L72 _protected prototype_ `void HandleAddBinding(const TArray<TSharedPtr<FBindingChainElement>> InBindingChain) const;`
- L73 _protected prototype_ `static void HandleAddBinding(const FPropertyBindingWidgetArgs& Args, FName PropertyName, const TArray<TSharedPtr<FBindingChainElement>>& InBindingChain);`
- L74 _protected prototype_ `static void HandleSetBindingArrayIndex(const FPropertyBindingWidgetArgs& Args, FName PropertyName, int32 InArrayIndex, ETextCommit::Type InCommitType, FProperty* InProperty, TArray<TSharedPtr<FBindingChainElement>> InBindingChain);`
- L76 _protected prototype_ `void HandleCreateAndAddBinding();`
- L78 _protected prototype_ `static UStruct* ResolveIndirection(const FPropertyBindingWidgetArgs& Args, const TArray<TSharedPtr<FBindingChainElement>>& BindingChain);`
- L80 _protected prototype_ `EVisibility GetGotoBindingVisibility() const;`
- L82 _protected prototype_ `FReply HandleGotoBindingClicked();`
- L85 _protected prototype_ `static bool CanAcceptPropertyOrChildren(const FPropertyBindingWidgetArgs& Args, FProperty* InProperty, TConstArrayView<TSharedPtr<FBindingChainElement>> InBindingChain);` — Helper function to call the OnCanAcceptProperty* delegates, handles conversion of binding chain to TConstArrayView<FBindingChainElement> as expected by the delegate.
- L88 _protected prototype_ `static bool CanBindProperty(const FPropertyBindingWidgetArgs& Args, FProperty* InProperty, TConstArrayView<TSharedPtr<FBindingChainElement>> InBindingChain);` — Helper function to call the OnCanBindProperty* delegates, handles conversion of binding chain to TConstArrayView<FBindingChainElement> as expected by the delegate.
- L90 _protected prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L92 _protected prototype_ `bool HasAnyBindings() const;`
- L96 _private prototype_ `static bool IsClassDenied(const FPropertyBindingWidgetArgs& Args, UClass* OwnerClass);`
- L97 _private prototype_ `static bool IsFieldFromDeniedClass(const FPropertyBindingWidgetArgs& Args, FFieldVariant Field);`
- L98 _private prototype_ `static bool HasBindableProperties(const FPropertyBindingWidgetArgs& Args, const UBlueprint* Blueprint, UStruct* InStruct, TArray<TSharedPtr<FBindingChainElement>>& BindingChain);`
- L99 _private prototype_ `static bool HasBindablePropertiesRecursive(const FPropertyBindingWidgetArgs& Args, const UBlueprint* Blueprint, UStruct* InStruct, TSet<UStruct*>& VisitedStructs, TArray<TSharedPtr<FBindingChainElement>>& BindingChain);`
- L106 _private prototype_ `template <typename Predicate> static void ForEachBindableProperty(const FPropertyBindingWidgetArgs& Args, const UBlueprint* Blueprint, UStruct* InStruct, const TArray<TSharedPtr<FBindingChainElement>>& BindingChain, Predicate Pred);` — Note that an ArrayView is not used to pass the BindingChain around since the predicate can modify the array and this will invalidate the ArrayView if reallocation is performed.
- L109 _private prototype_ `template <typename Predicate> static void ForEachBindableFunction(const FPropertyBindingWidgetArgs& Args, UClass* FromClass, Predicate Pred);`
- L111 _private prototype_ `void AddCategoryToMenu(FMenuBuilder& MenuBuilder, const FBindingContextStructCategory& Category);`
- L112 _private prototype_ `void BuildContextStructCategoryRecursive(TConstArrayView<FString> CategoryNames, TArray<FBindingContextStructCategory>& ParentSubCategories, int32 ContextStructIndex);`
- L113 _private prototype_ `bool HasCategorySomethingToDisplayRecursive(const FBindingContextStructCategory& Category) const;`
- L115 _private prototype_ `TSharedRef<SWidget> MakeContextStructWidget(const FBindingContextStruct& ContextStruct) const;`
- L117 _private member_ `UBlueprint* Blueprint = nullptr;`
- L118 _private member_ `TArray<FBindingContextStruct> BindingContextStructs;`
- L120 _private member_ `TArray<FBindingContextStructCategory> BindingContextStructSections;` — Top level sections of the binding ContextStructs
- L121 _private member_ `FPropertyBindingWidgetArgs Args;`
- L122 _private member_ `FName PropertyName;`

#### struct `SPropertyBinding::FFunctionInfo`  
`struct FFunctionInfo`  
_L29-48_
- L31 _public function_ `FFunctionInfo() : Function(nullptr)`
- L36 _public function_ `FFunctionInfo(UFunction* InFunction) : DisplayName(InFunction->HasMetaData("ScriptName") ? InFunction->GetMetaDataText("ScriptName") : FText::FromName(InFunction->GetFName())) , Tooltip(InFunction->GetMetaData("Tooltip")) , FuncName(InFunction->GetFName()) , Function(InFunction)`
- L43 _public member_ `FText DisplayName;`
- L44 _public member_ `FString Tooltip;`
- L46 _public member_ `FName FuncName;`
- L47 _public member_ `UFunction* Function;`

#### struct `SPropertyBinding::FBindingContextStructCategory`  
`struct FBindingContextStructCategory`  
_L50-55_
- L52 _public member_ `FText Name;`
- L53 _public member_ `TArray<FBindingContextStructCategory> SubCategories;`
- L54 _public member_ `TArray<int32> BindingContextStructIndices;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ETextCommit`
