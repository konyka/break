# Plugins / ProxyTable

- module root: `Plugins/Chooser/Source/ProxyTable`
- headers: 5; symbols: 95
- symbol kinds: class=5, delegate=2, function=8, macro=3, member=30, prototype=40, struct=7
- PrivateDependencyModuleNames: Core, CoreUObject, Engine
- PublicDependencyModuleNames: Chooser

### `Plugins/Chooser/Source/ProxyTable/Internal/LookupProxy.h` (Internal)


#### struct `FProxyTableContextProperty`  
`struct FProxyTableContextProperty : public FChooserParameterProxyTableBase`  
_L17-28_
- reflection: `USTRUCT()`
- inherits: `FChooserParameterProxyTableBase`
- L23 _public member_ `FChooserPropertyBinding Binding;` — `UPROPERTY(EditAnywhere, Meta = (BindingType = "UProxyTable*"), Category = "Binding")`
- L25 _public prototype_ `virtual bool GetValue(FChooserEvaluationContext& Context, const UProxyTable*& OutResult) const override;`
- L27 _public prototype_ `CHOOSER_PARAMETER_BOILERPLATE();`

#### struct `FLookupProxy`  
`struct FLookupProxy : public FObjectChooserBase`  
_L31-51_
- reflection: `USTRUCT(DisplayName = "Lookup Proxy", Meta = (Category = "Proxy Table", Tooltip = "Find a Proxy Asset entry in a Proxy Table, and evaluate it's value if this row is selected."))`
- inherits: `FObjectChooserBase`
- L34 _public prototype_ `virtual EIteratorStatus ChooseMulti(FChooserEvaluationContext &Context, FObjectChooserIteratorCallback Callback) const final override;`
- L35 _public prototype_ `virtual UObject* ChooseObject(FChooserEvaluationContext& Context) const final override;`
- L37 _public prototype_ `FLookupProxy();`
- L39 _public prototype_ `virtual void Compile(IHasContextClass* HasContext, bool bForce) override;`
- L40 _public prototype_ `virtual bool HasCompileErrors(FText& Message) override;`
- L42 _public prototype_ `virtual void GetDebugName(FString& OutName) const override;`
- L47 _public member_ `TObjectPtr<UProxyAsset> Proxy;` — `UPROPERTY(EditAnywhere, Category="Parameters")`
- L50 _public member_ `FInstancedStruct ProxyTable;` — `UPROPERTY(EditAnywhere, NoClear, Meta = (ExcludeBaseStruct, BaseStruct = "/Script/ProxyTable.ChooserParameterProxyTableBase"), Category = "Parameters")`

#### struct `FLookupProxyWithOverrideTable`  
`struct FLookupProxyWithOverrideTable : public FObjectChooserBase`  
_L54-69_
- reflection: `USTRUCT(meta=(Hidden))`
- inherits: `FObjectChooserBase`
- L57 _public prototype_ `virtual EIteratorStatus ChooseMulti(FChooserEvaluationContext& ContextData, FObjectChooserSoftObjectIteratorCallback Callback) const final override;`
- L58 _public prototype_ `virtual EIteratorStatus ChooseMulti(FChooserEvaluationContext &Context, FObjectChooserIteratorCallback Callback) const final override;`
- L59 _public prototype_ `virtual UObject* ChooseObject(FChooserEvaluationContext& Context) const final override;`
- L60 _public prototype_ `virtual void ChooseObject(FChooserEvaluationContext& Context, TSoftObjectPtr<UObject>& Result) const override;`
- L65 _public member_ `TObjectPtr<UProxyAsset> Proxy;` — `UPROPERTY(EditAnywhere, Category="Parameters")`
- L68 _public member_ `TObjectPtr<UProxyTable> OverrideProxyTable;` — `UPROPERTY(EditAnywhere, Category="Parameters")`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API PROXYTABLE_API`

### `Plugins/Chooser/Source/ProxyTable/Public/IChooserParameterProxyTable.h` (Public)


#### class `UChooserParameterProxyTable`  
`class UChooserParameterProxyTable : public UInterface`  
_L15-18_
- reflection: `UINTERFACE(MinimalAPI, NotBlueprintType, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IChooserParameterProxyTable`  
`class IChooserParameterProxyTable`  
_L20-25_
- L24 _public function_ `virtual void ConvertToInstancedStruct(FInstancedStruct& OutInstancedStruct) const`

#### struct `FChooserParameterProxyTableBase`  
`struct FChooserParameterProxyTableBase : public FChooserParameterBase`  
_L29-35_
- reflection: `USTRUCT()`
- inherits: `FChooserParameterBase`
- L34 _public function_ `virtual bool GetValue(FChooserEvaluationContext& Context, const UProxyTable*& OutResult) const`

### `Plugins/Chooser/Source/ProxyTable/Public/ProxyAsset.h` (Public)


#### class `UProxyAsset`  
`class UProxyAsset : public UObject, public IHasContextClass`  
_L18-65_
- reflection: `UCLASS(MinimalAPI,BlueprintType,Experimental)`
- inherits: `UObject,IHasContextClass`
- desc: EXPERIMENTAL: An indirect mapping to an asset. The direct mapping is defined in a Proxy Table.
- L22 _public function_ `UProxyAsset()`
- L24 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L26 _public member_ `static FName TypeTagName;`
- L29 _public member_ `FProxyTypeChanged OnTypeChanged;`
- L30 _public prototype_ `virtual void PostEditUndo() override;`
- L31 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L34 _public member_ `UClass* CachedPreviousType = nullptr;` — caching the type so that on Undo, we can tell if we should fire the changed delegate
- L35 _public member_ `EObjectChooserResultType CachedPreviousResultType = EObjectChooserResultType::ObjectResult;`
- L40 _public member_ `TObjectPtr<UClass> Type;` — `UPROPERTY(EditAnywhere, Category = "Proxy", Meta = (AllowAbstract=true))`
- L42 _public member_ `EObjectChooserResultType ResultType = EObjectChooserResultType::ObjectResult;` — `UPROPERTY(EditAnywhere, Category = "Proxy")`
- L45 _public member_ `TArray<FInstancedStruct> ContextData;` — `UPROPERTY(EditAnywhere, Meta = (ExcludeBaseStruct, BaseStruct = "/Script/Chooser.ContextObjectTypeBase"), Category = "Input")`
- L48 _public member_ `FGuid Guid;` — `UPROPERTY()`
- L50 _public function_ `virtual TConstArrayView<FInstancedStruct> GetContextData() const override`
- L51 _public function_ `virtual FString GetContextOwnerName() const override`
- L52 _public function_ `virtual UObject* GetContextOwnerAsset() override`
- L54 _public prototype_ `UObject* FindProxyObject(struct FChooserEvaluationContext& Context) const;`
- L55 _public prototype_ `FObjectChooserBase::EIteratorStatus FindProxyObjectMulti(FChooserEvaluationContext &Context, FObjectChooserBase::FObjectChooserIteratorCallback Callback) const;`
- L59 _public member_ `TObjectPtr<UClass> ContextClass_DEPRECATED;` — `UPROPERTY()`
- L61 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L62 _public prototype_ `virtual void PostLoad() override;`
- L63 _public prototype_ `virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FProxyTypeChanged, const UClass* OutputObjectType);`
- L12 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FProxyTypeChanged, const UClass* OutputObjectType);`

### `Plugins/Chooser/Source/ProxyTable/Public/ProxyTable.h` (Public)


#### struct `FProxyStructOutput`  
`struct FProxyStructOutput`  
_L15-24_
- reflection: `USTRUCT()`
- L20 _public member_ `FChooserStructPropertyBinding Binding;` — `UPROPERTY(EditAnywhere, Category = "Data")`
- L23 _public member_ `FInstancedStruct Value;` — `UPROPERTY(EditAnywhere, NoClear, Category = "Data")`

#### struct `FProxyEntry`  
`struct FProxyEntry`  
_L27-48_
- reflection: `USTRUCT()`
- L31 _public prototype_ `bool operator== (const FProxyEntry& Other) const;`
- L32 _public prototype_ `bool operator< (const FProxyEntry& Other) const;`
- L35 _public member_ `TObjectPtr<UProxyAsset> Proxy;` — `UPROPERTY(EditAnywhere, Category = "Data")`
- L39 _public member_ `FName Key;` — `UPROPERTY(EditAnywhere, Category = "Data")` — temporarily leaving this property for backwards compatibility with old content which used FNames rather than UProxyAsset
- L42 _public member_ `FInstancedStruct ValueStruct;` — `UPROPERTY(DisplayName="Value", EditAnywhere, NoClear, Meta = (ExcludeBaseStruct, BaseStruct = "/Script/Chooser.ObjectChooserBase"), Category = "Data")`
- L45 _public member_ `TArray<FProxyStructOutput> OutputStructData;` — `UPROPERTY(EditAnywhere, NoClear, Category = "Data")`
- L47 _public prototype_ `const FGuid GetGuid() const;`

#### struct `FRuntimeProxyValue`  
`struct FRuntimeProxyValue`  
_L57-69_
- reflection: `USTRUCT()`
- L62 _public member_ `TObjectPtr<UProxyAsset> ProxyAsset;` — `UPROPERTY()`
- L65 _public member_ `FInstancedStruct Value;` — `UPROPERTY()`
- L68 _public member_ `TArray<FProxyStructOutput> OutputStructData;` — `UPROPERTY()`

#### class `UProxyTable`  
`class UProxyTable : public UObject`  
_L75-114_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Experimental)`
- inherits: `UObject`
- desc: EXPERIMENTAL: Table mapping of proxy assets to a specific asset.
- L79 _public function_ `UProxyTable()`
- L80 _public prototype_ `virtual void BeginDestroy() override;`
- L83 _public member_ `TArray<FGuid> Keys;` — `UPROPERTY()`
- L86 _public member_ `TArray<FRuntimeProxyValue> RuntimeValues;` — `UPROPERTY()`
- L88 _public prototype_ `FObjectChooserBase::EIteratorStatus FindProxyObjectMulti(const FGuid& Key, FChooserEvaluationContext &Context, FObjectChooserBase::FObjectChooserIteratorCallback Callback) const;`
- L89 _public prototype_ `UObject* FindProxyObject(const FGuid& Key, FChooserEvaluationContext& Context) const;`
- L90 _public prototype_ `void FindProxyObject(const FGuid& Key, FChooserEvaluationContext& Context, TSoftObjectPtr<UObject>& Result) const;`
- L91 _public prototype_ `FObjectChooserBase::EIteratorStatus FindProxyObjectMulti(const FGuid& Key, FChooserEvaluationContext& Context, FObjectChooserBase::FObjectChooserSoftObjectIteratorCallback Callback) const;`
- L93 _public prototype_ `FObjectChooserBase::EIteratorStatus IterateProxyObjects(const FGuid& Key, FChooserEvaluationContext& Context, FObjectChooserBase::FObjectChooserIteratorCallback Callback) const;`
- L94 _public prototype_ `FObjectChooserBase::EIteratorStatus IterateProxyObjects(const FGuid& Key, FObjectChooserBase::FObjectChooserIteratorCallback Callback) const;`
- L96 _public prototype_ `virtual void PostLoad() override;`
- L99 _public member_ `FProxyTableChanged OnProxyTableChanged;`
- L102 _public member_ `TArray<FProxyEntry> Entries;` — `UPROPERTY(EditAnywhere, Category = "Hidden")`
- L105 _public member_ `TArray<TObjectPtr<UProxyTable>> InheritEntriesFrom;` — `UPROPERTY(EditAnywhere, Category = "Inheritance")`
- L107 _public prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L109 _private prototype_ `void BuildRuntimeData();`
- L110 _private member_ `TArray<TWeakObjectPtr<UProxyTable>> TableDependencies;`
- L111 _private member_ `TArray<TWeakObjectPtr<UProxyAsset>> ProxyDependencies;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API PROXYTABLE_API`
- L51 _function_ `inline uint32 GetTypeHash(const FProxyEntry& Entry)`
- L54 _delegate_ `DECLARE_MULTICAST_DELEGATE(FProxyTableChanged);`
- L54 _prototype_ `DECLARE_MULTICAST_DELEGATE(FProxyTableChanged);`

### `Plugins/Chooser/Source/ProxyTable/Public/ProxyTableFunctionLibrary.h` (Public)


#### class `UProxyTableFunctionLibrary`  
`class UProxyTableFunctionLibrary : public UBlueprintFunctionLibrary`  
_L16-63_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Proxy Table Function Library
- L29 _public prototype_ `static UObject* EvaluateProxyTable(const UObject* ContextObject, const UProxyTable* ProxyTable, FName Key);` — `UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe, BlueprintInternalUseOnly="true"), Category = "Animation")` — Temporary backwards compatibility function!  please switch to EvaluateProxyAsset @param ContextObject			(in) An Object from which the parameters to the Chooser Table will be read @param ProxyTable				(in) The ProxyTable asset @param Key					(in) The Key from the ProxyTable asset
- L39 _public prototype_ `static UObject* EvaluateProxyAsset(const UObject* ContextObject, const UProxyAsset* Proxy, TSubclassOf<UObject> ObjectClass);` — `UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe, DeterminesOutputType = "ObjectClass", BlueprintInternalUseOnly="true"), Category = "Animation")` — Resolve a proxy asset and return the selected UObject, or null @param ContextObject			(in) An Object from which the Proxy Table will be read, and parameters to any nested Chooser Tables that need to evaluate @param ProxyAsset				(in) The ProxyAsset asset @param ObjectClass			(in) Expected type of result objects
- L47 _public prototype_ `static FInstancedStruct MakeLookupProxy(UProxyAsset* Proxy);` — `UFUNCTION(BlueprintPure, Category = "Animation", meta = (BlueprintThreadSafe, BlueprintInternalUseOnly="true"))` — Create a LookupProxy struct @param Chooser				(in) the ChooserTable asset to evaluate
- L50 _public prototype_ `static FInstancedStruct MakeLookupProxyWithOverrideTable(UProxyAsset* Proxy, UProxyTable* ProxyTable);` — `UFUNCTION(BlueprintPure, Category = "Animation", meta = (BlueprintThreadSafe, BlueprintInternalUseOnly="true"))`
- L61 _public prototype_ `static TMap<UProxyAsset*, UObject*> GetProxyTableEntries(const UProxyTable* ProxyTable);` — `UFUNCTION(BlueprintCallable, Category = "Animation", meta = (CallInEditor = "true"))` — Get all entries in a ProxyTable as a map from ProxyAsset to its resolved UObject value. Editor-only: uses editor-only APIs (GetReferencedObject) that are not available in cooked builds. @param ProxyTable				(in) The ProxyTable asset to read entries from @return Map of ProxyAsset to resolved UObject value

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API PROXYTABLE_API`
