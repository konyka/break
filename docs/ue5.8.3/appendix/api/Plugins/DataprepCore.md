# Plugins / DataprepCore

- module root: `Plugins/Enterprise/DataprepEditor/Source/DataprepCore`
- headers: 41; symbols: 964
- symbol kinds: class=57, delegate=25, enum=9, enumerator=28, function=175, member=185, namespace=6, prototype=454, struct=18, typedef=7
- PrivateDependencyModuleNames: AssetTools, BlueprintGraph, Core, CoreUObject, DatasmithContent, EditorFramework, EditorScriptingUtilities, EditorStyle, EditorWidgets, Engine, GraphEditor, InputCore, InterchangeCore, InterchangeEngine, InterchangeFactoryNodes, KismetCompiler, LevelSequence, MeshDescription, MessageLog, PropertyEditor, RHI, RenderCore, Slate, SlateCore, StaticMeshDescription, UnrealEd, VariantManagerContent

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Private/Blueprint/K2Node_DataprepProducer.h` (Private)


#### class `UK2Node_DataprepProducer`  
`class UK2Node_DataprepProducer : public UK2Node`  
_L13-32_
- reflection: `UCLASS()`
- inherits: `UK2Node`
- L19 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L21 _public prototype_ `virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;`
- L23 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L24 _public prototype_ `virtual FText GetTooltipText() const override;`
- L25 _public function_ `virtual bool CanDuplicateNode() const override`
- L26 _public function_ `virtual bool CanUserDeleteNode() const override`
- L30 _public function_ `virtual bool IsNodePure() const override`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ENodeTitleType`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Private/DataprepCoreLogCategory.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDataprepCore, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDataprepCore, Log, All);`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Private/DataprepParameterizationArchive.h` (Private)


#### class `FDataprepParameterizationWriter`  
`class FDataprepParameterizationWriter : public FMemoryWriter`  
_L12-60_
- inherits: `FMemoryWriter`
- L15 _public function_ `FDataprepParameterizationWriter(UObject* Object, TArray<uint8>& InBytes) : FMemoryWriter(InBytes, true)`
- L38 _public prototype_ `virtual FArchive& operator<<(FName& Value) override;`
- L40 _public prototype_ `virtual FArchive& operator<<(UObject*& Value) override;`
- L42 _public function_ `virtual FArchive& operator<<(FText& Value) override`
- L48 _public prototype_ `virtual FArchive& operator<<(struct FLazyObjectPtr& Value) override;`
- L50 _public prototype_ `virtual FArchive& operator<<(struct FObjectPtr& Value) override;`
- L52 _public prototype_ `virtual FArchive& operator<<(struct FSoftObjectPtr& Value) override;`
- L54 _public prototype_ `virtual FArchive& operator<<(struct FSoftObjectPath& Value) override;`
- L56 _public prototype_ `virtual FArchive& operator<<(struct FWeakObjectPtr& Value) override;`
- L58 _public prototype_ `virtual FString GetArchiveName() const override;`

#### class `FDataprepParameterizationReader`  
`class FDataprepParameterizationReader : public FMemoryReader`  
_L62-112_
- inherits: `FMemoryReader`
- L65 _public function_ `FDataprepParameterizationReader(UObject* Object, TArray<uint8>& InBytes) : FMemoryReader(InBytes, true)`
- L90 _public prototype_ `virtual FArchive& operator<<(FName& Value) override;`
- L92 _public prototype_ `virtual FArchive& operator<<(UObject*& Value) override;`
- L94 _public function_ `virtual FArchive& operator<<(FText& Value) override`
- L100 _public prototype_ `virtual FArchive& operator<<(struct FLazyObjectPtr& Value) override;`
- L102 _public prototype_ `virtual FArchive& operator<<(struct FObjectPtr& Value) override;`
- L104 _public prototype_ `virtual FArchive& operator<<(struct FSoftObjectPtr& Value) override;`
- L106 _public prototype_ `virtual FArchive& operator<<(struct FSoftObjectPath& Value) override;`
- L108 _public prototype_ `virtual FArchive& operator<<(struct FWeakObjectPtr& Value) override;`
- L110 _public prototype_ `virtual FString GetArchiveName() const override;`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Private/InterchangeDataprepPipeline.h` (Private)


#### class `UInterchangeDataprepLevelPipeline`  
`class UInterchangeDataprepLevelPipeline : public UInterchangePipelineBase`  
_L13-20_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UInterchangePipelineBase`
- L18 _protected prototype_ `virtual void ExecutePipeline(UInterchangeBaseNodeContainer* BaseNodeContainer, const TArray<UInterchangeSourceData*>& SourceDatas, const FString& ContentBasePath) override;`
- L19 _protected prototype_ `virtual void ExecutePostImportPipeline(const UInterchangeBaseNodeContainer* BaseNodeContainer, const FString& NodeKey, UObject* CreatedAsset, bool bIsAReimport) override;`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Private/InterchangeFileProducer.h` (Private)


#### class `UInterchangeFileProducer`  
`class UInterchangeFileProducer : public UDataprepContentProducer`  
_L19-71_
- reflection: `UCLASS(Experimental, HideCategories = (InterchangeProducer_Internal))`
- inherits: `UDataprepContentProducer`
- L23 _private prototype_ `UInterchangeFileProducer();`
- L27 _public prototype_ `virtual void PostEditUndo() override;` — UObject interface
- L28 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L32 _public prototype_ `void SetFilePath( const FString& InFilePath );` — Update producer with the desired file
- L34 _public function_ `const FString& GetFilePath() const`
- L37 _public prototype_ `virtual const FText& GetLabel() const override;`
- L38 _public prototype_ `virtual const FText& GetDescription() const override;`
- L39 _public prototype_ `virtual FString GetNamespace() const override;`
- L40 _public prototype_ `virtual bool Supersede(const UDataprepContentProducer* OtherProducer) const override;`
- L41 _public prototype_ `virtual bool CanAddToProducersArray(bool bIsAutomated) override;`
- L44 _protected prototype_ `virtual bool Initialize() override;`
- L45 _protected prototype_ `virtual bool Execute(TArray< TWeakObjectPtr< UObject > >& OutAssets) override;`
- L46 _protected prototype_ `virtual void Reset() override;`
- L47 _protected prototype_ `virtual bool IsActive() override;`
- L51 _protected member_ `FString FilePath;` — `UPROPERTY(EditAnywhere, Category = InterchangeProducer)`
- L55 _private prototype_ `void OnFilePathChanged();` — Does what is required after setting a new FilePath
- L58 _private prototype_ `void UpdateName();` — Update the name of the producer based on the filename
- L60 _private prototype_ `bool InitTranslator();`
- L63 _private member_ `TUniquePtr< FDataprepWorkReporter > ProgressTaskPtr;`
- L66 _private member_ `TObjectPtr<UPackage> TransientPackage = nullptr;` — `UPROPERTY(Transient, DuplicateTransient)`
- L68 _private member_ `TArray< TWeakObjectPtr< UObject > > Assets;`

#### class `FInterchangeContentProducerDetails`  
`class FInterchangeContentProducerDetails : public IDetailCustomization`  
_L73-84_
- inherits: `IDetailCustomization`
- L76 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;`
- L77 _public prototype_ `FSlateColor GetStatusColorAndOpacity() const;`
- L78 _public prototype_ `bool IsProducerSuperseded() const;`
- L81 _protected member_ `class UDataprepAssetProducers* AssetProducers = nullptr;`
- L82 _protected member_ `UDataprepContentProducer* Producer = nullptr;`
- L83 _protected member_ `int32 ProducerIndex = INDEX_NONE;` — This index does not change for the lifetime of the property widget

#### class `FInterchangeFileProducerDetails`  
`class FInterchangeFileProducerDetails : public FInterchangeContentProducerDetails`  
_L87-94_
- inherits: `FInterchangeContentProducerDetails`
- desc: Customization of the details of the Interchange producer for the data prep editor.
- L90 _public function_ `static TSharedRef< IDetailCustomization > MakeDetails()`
- L93 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — Called when details should be customized

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Private/Parameterization/DataprepParameterization.h` (Private)


#### struct `FValueTypeValidationData`  
`struct FValueTypeValidationData`  
_L16-55_
- L18 _public member_ `TArray<TObjectPtr<UObject>> ObjectData;`
- L19 _public member_ `TArray<TFieldPath<FProperty>> PropertyData;`
- L20 _public member_ `TArray<FFieldClass*> PropertyTypeData;`
- L22 _public prototype_ `bool Serialize(FArchive& Ar);`
- L23 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector);`
- L25 _public function_ `void Add(UObject* InObj)`
- L29 _public function_ `void Add(FProperty* InProp)`
- L33 _public function_ `void Add(FFieldClass* InClass)`
- L37 _public function_ `void Reserve(int32 Count)`
- L41 _public function_ `int32 Num() const`
- L45 _public function_ `void Empty()`
- L51 _public function_ `bool operator == (const FValueTypeValidationData& Other) const`

#### struct `FDataprepParameterizationBinding`  
`struct FDataprepParameterizationBinding`  
_L62-88_
- reflection: `USTRUCT()`
- desc: The parameterization binding is a struct that hold an object and the property path to the parameterized property It also hold a array to validate the that value type of the parameterized property didn't change since it's creation
- L66 _public function_ `FDataprepParameterizationBinding() : ValueTypeValidationData()`
- L70 _public prototype_ `FDataprepParameterizationBinding(UDataprepParameterizableObject* InObjectBinded, TArray<FDataprepPropertyLink> InPropertyChain);`
- L72 _public prototype_ `FDataprepParameterizationBinding(FDataprepParameterizationBinding&&) = default;`
- L73 _public prototype_ `FDataprepParameterizationBinding(const FDataprepParameterizationBinding&) = default;`
- L74 _public prototype_ `FDataprepParameterizationBinding& operator=(FDataprepParameterizationBinding&&) = default;`
- L75 _public prototype_ `FDataprepParameterizationBinding& operator=(const FDataprepParameterizationBinding&) = default;`
- L77 _public prototype_ `bool operator==(const FDataprepParameterizationBinding& Other) const;`
- L80 _public member_ `TObjectPtr<UDataprepParameterizableObject> ObjectBinded = nullptr;` — `UPROPERTY()`
- L83 _public member_ `TArray<FDataprepPropertyLink> PropertyChain;` — `UPROPERTY()`
- L87 _public member_ `FValueTypeValidationData ValueTypeValidationData;` — `UPROPERTY()` — Value Type Validation Array. This is the result of a depth first search on the parametrized property

#### struct `FDataprepParametrizationBindingMapKeyFuncs`  
`struct FDataprepParametrizationBindingMapKeyFuncs : TDefaultMapHashableKeyFuncs<TSharedRef<FDataprepParameterizationBinding>, FName, false>`  
_L98-109_
- inherits: `TDefaultMapHashableKeyFuncs<TSharedRef<FDataprepParameterizationBinding>,FName,false>`
- desc: A override to defines how the map's pairs are hashed and compared. This allow us to have some map that work with TSharedRef but compare the object value instead of the pointer
- L100 _public function_ `static FORCEINLINE bool Matches(KeyInitType A, KeyInitType B)`
- L105 _public function_ `static FORCEINLINE uint32 GetKeyHash(KeyInitType Key)`

#### struct `FDataprepParametrizationBindingSetKeyFuncs`  
`struct FDataprepParametrizationBindingSetKeyFuncs : DefaultKeyFuncs<TSharedRef<FDataprepParameterizationBinding>>`  
_L115-127_
- inherits: `DefaultKeyFuncs<TSharedRef<FDataprepParameterizationBinding>>`
- desc: A override to defines how the set values are hashed and compared. This allow us to have some set that work with TSharedRef but compare the object value instead of the pointer
- L118 _public function_ `template<typename ComparableKey> static FORCEINLINE bool Matches(KeyInitType A, ComparableKey B)`
- L123 _public function_ `static FORCEINLINE uint32 GetKeyHash(KeyInitType Key)`

#### class `UDataprepParameterizationBindings`  
`class UDataprepParameterizationBindings : public UObject`  
_L133-223_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Encapsulate the unidirectionality necessary for a constant cost of access to the data related to the bindings
- L139 _public typedef_ `using FBindingToParameterNameMap = TMap<TSharedRef<FDataprepParameterizationBinding>, FName, FDefaultSetAllocator, FDataprepParametrizationBindingMapKeyFuncs>;`
- L140 _public typedef_ `using FSetOfBinding = TSet<TSharedRef<FDataprepParameterizationBinding>, FDataprepParametrizationBindingSetKeyFuncs>;`
- L145 _public prototype_ `bool ContainsBinding(const TSharedRef<FDataprepParameterizationBinding>& Binding) const;` — Does the data structure contains this binding
- L150 _public prototype_ `FName GetParameterNameForBinding(const TSharedRef<FDataprepParameterizationBinding>& Binding) const;` — Return the name of the parameter for a binding
- L155 _public prototype_ `const FSetOfBinding* GetBindingsFromObject(const UDataprepParameterizableObject* Object) const;` — Return a valid ptr if the object had some bindings
- L161 _public prototype_ `const FSetOfBinding* GetBindingsFromParameter(const FName& ParameterName) const;` — Get the bindings from a parameter Return nullptr if the parameter doesn't exist
- L166 _public prototype_ `bool HasBindingsForParameter(const FName& ParameterName) const;` — Does the data structure has some bindings for the parameter name
- L171 _public prototype_ `bool HasBindingsFromObject(UDataprepParameterizableObject* Object) const;` — Does the data structure has some bindings from the specified object
- L176 _public prototype_ `void Add(const TSharedRef<FDataprepParameterizationBinding>& Binding, const FName& ParameterName, FSetOfBinding& OutBindingsContainedByNewBinding);` — Add a binding and map it to the parameter
- L182 _public prototype_ `FName RemoveBinding(const TSharedRef<FDataprepParameterizationBinding>& Binding);` — Remove a binding. @return The name of the parameter the binding was associated with
- L188 _public prototype_ `TSet<FName> RemoveAllBindingsFromObject(UDataprepParameterizableObject* Object);` — Remove all the bindings from a object @return The name of the parameters that were associated to the binding of the object
- L193 _public prototype_ `TSharedPtr<FDataprepParameterizationBinding> GetContainingBinding(const TSharedRef<FDataprepParameterizationBinding>& Binding) const;` — @return A valid pointer if the binding is a part of an existing binding
- L195 _public prototype_ `const FBindingToParameterNameMap& GetBindingToParameterName() const;`
- L197 _public prototype_ `TArray<UDataprepParameterizableObject*> GetParameterizedObjects() const;`
- L200 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L201 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L208 _private prototype_ `void Save(FArchive& Ar);` — Do the actual serialization when saving
- L213 _private prototype_ `void Load(FArchive& Ar);` — Do the actual serialization when reloading
- L216 _private member_ `FBindingToParameterNameMap BindingToParameterName;` — Core storage also track a binding to it's parameter name
- L219 _private member_ `TMap<FName, FSetOfBinding> NameToBindings;` — Track the name usage for parameters
- L222 _private member_ `TMap<TObjectPtr<UDataprepParameterizableObject>, FSetOfBinding> ObjectToBindings;` — Track which binding a object has

#### class `UDataprepParameterization`  
`class UDataprepParameterization : public UObject`  
_L230-380_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: The DataprepParameterization contains the data for the parameterization of a pipeline
- L235 _public prototype_ `UDataprepParameterization();`
- L238 _public prototype_ `virtual void PostInitProperties() override;` — UObject interface
- L239 _public prototype_ `virtual void PostLoad() override;`
- L240 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L241 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L242 _public prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L243 _public prototype_ `virtual void FinishDestroy() override;`
- L246 _public prototype_ `void OnObjectModified(UObject* Object);`
- L248 _public prototype_ `UObject* GetDefaultObject();`
- L250 _public prototype_ `bool BindObjectProperty(UDataprepParameterizableObject* Object, const TArray<FDataprepPropertyLink>& PropertyChain, const FName& Name);`
- L252 _public prototype_ `bool IsObjectPropertyBinded(UDataprepParameterizableObject* Object, const TArray<FDataprepPropertyLink>& PropertyChain) const;`
- L254 _public prototype_ `FName GetNameOfParameterForObjectProperty(UDataprepParameterizableObject* Object, const TArray<struct FDataprepPropertyLink>& PropertyChain) const;`
- L256 _public prototype_ `void RemoveBindedObjectProperty(UDataprepParameterizableObject* Object, const TArray<FDataprepPropertyLink>& PropertyChain);`
- L258 _public prototype_ `void RemoveBindingFromObjects(const TArrayView<UDataprepParameterizableObject*>& Objects);`
- L260 _public prototype_ `void GetExistingParameterNamesForType(FProperty* Property, bool bIsDescribingFullProperty, TSet<FString>& OutValidExistingNames, TSet<FString>& OutInvalidNames) const;`
- L262 _public prototype_ `void DuplicateObjectParamaterization(const UDataprepParameterizableObject* InObject, UDataprepParameterizableObject* OutObject);`
- L269 _private prototype_ `void GenerateClass();` — Generate the Custom Container Class
- L274 _private prototype_ `void UpdateClass();` — Update the Custom Container Class to a newer version
- L279 _private prototype_ `void LoadParameterization();` — Do the process of regenerating the Custom Container Class and the data of its default object from the serialized data
- L284 _private prototype_ `void PrepareCustomClassForNewClassGeneration();` — Remove the current Custom Container Class so that we can create a new one
- L289 _private prototype_ `void CreateClassObject();` — Do the actual creation of the class object
- L296 _private prototype_ `void DoReinstancing(UClass* OldClass, bool bMigrateData = true);` — Do reinstancing of the objects created from the Custom Container Class @param OldClass The previous Custom Constainer Class @param bMigrateData Should we migrate the data from the old instances to the new instances
- L301 _private prototype_ `FProperty* AddPropertyToClass(const FName& ParameterisationPropertyName, FProperty& Property, bool bAddFullProperty);` — Try adding a binded property to the parameterization class
- L306 _private prototype_ `void UpdateParameterizationFromBinding(const TSharedRef<FDataprepParameterizationBinding>& Binding);` — Get a new value for the parameterization from it's associated binding
- L311 _private prototype_ `void PushParametrizationValueToBindings(FName ParameterName);` — Push the value of the parametrization to the bindings
- L317 _private prototype_ `bool RemoveBinding(const TSharedRef<FDataprepParameterizationBinding>& Binding, bool& bOutClassNeedUpdate);` — Do the actual removing of a binding @return True if binding was remove
- L322 _private prototype_ `void OnParameterizationDefaultObjectPostEdit(UDataprepParameterizableObject& Object, FPropertyChangedChainEvent& PropertyChangedChainEvent);` — Functions for the tracking of the post edit change
- L323 _private prototype_ `void OnParameterizedObjectPostEdit(UDataprepParameterizableObject& Object, FPropertyChangedChainEvent& PropertyChangedChainEvent);`
- L324 _private prototype_ `void OnAddedBindingToPostEditOfParameterizableObject(UDataprepParameterizableObject& Object, const FDelegateHandle& Handle);`
- L325 _private prototype_ `void OnRemovedBindingToPostEditOfParameterizableObject(UDataprepParameterizableObject& Object, const FDelegateHandle& Handle);`
- L326 _private prototype_ `void AddBindingToPostEditOfParameterizableObject(UDataprepParameterizableObject& Object, bool bShouldAddToTransaction);`
- L327 _private prototype_ `void RemoveBindingToPostEditOfParameterizableObject(UDataprepParameterizableObject& Object, bool bShouldAddToTransaction);`
- L335 _public prototype_ `bool OnAssetRename(ERenameFlags Flags);` — Update the package of the generated class Return if it can be rename
- L340 _private member_ `TObjectPtr<UDataprepParameterizationBindings> BindingsContainer;` — `UPROPERTY()` — The containers for the bindings
- L346 _private member_ `TMap<TObjectPtr<UDataprepParameterizableObject>, FDelegateHandle> ObservedObjects;` — Mapping of the observed object to their delegate handle The name are relative to the dataprep asset
- L350 _private member_ `TMap<FName, FProperty*> NameToParameterizationProperty;`
- L353 _private member_ `TObjectPtr<UClass> CustomContainerClass;` — `UPROPERTY(Transient, NonTransactional)`
- L356 _private member_ `TObjectPtr<UDataprepParameterizableObject> DefaultParameterisation;` — `UPROPERTY(Transient, NonTransactional)`
- L362 _private member_ `TArray<uint8> ParameterizationStorage;` — `UPROPERTY()` — This is used only to store a serialization of the values of the parameterization since we can't save our custom container class
- L364 _private prototype_ `DECLARE_EVENT(UDataprepParameterization, FOnCustomClassAboutToBeUpdated);`
- L365 _private member_ `FOnCustomClassAboutToBeUpdated OnCustomClassAboutToBeUpdated;`
- L367 _private typedef_ `using FMapOldToNewObjects = TMap<UObject*, UObject*>;`
- L368 _private prototype_ `DECLARE_EVENT_OneParam(UDataprepParameterization, FOnCustomClassWasUpdated, const FMapOldToNewObjects& );`
- L369 _private member_ `FOnCustomClassWasUpdated OnCustomClassWasUpdated;`
- L371 _private prototype_ `DECLARE_EVENT(UDataprepParameterization,FOnTellInstancesToReloadTheirSerializedData);`
- L372 _private member_ `FOnTellInstancesToReloadTheirSerializedData OnTellInstancesToReloadTheirSerializedData;`
- L377 _private member_ `FDelegateHandle OnObjectModifiedHandle;`
- L379 _private member_ `FDelegateHandle OnParameterizationDefaultObjectPostEditHandle;`

#### class `UDataprepParameterizationInstance`  
`class UDataprepParameterizationInstance : public UObject`  
_L384-445_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L389 _public prototype_ `UDataprepParameterizationInstance();`
- L390 _public prototype_ `virtual ~UDataprepParameterizationInstance();`
- L393 _public prototype_ `virtual void PostLoad() override;` — UObject interface
- L394 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L395 _public prototype_ `virtual void PostEditUndo() override;`
- L398 _public prototype_ `void OnObjectModified(UObject* Object);`
- L401 _public prototype_ `void ApplyParameterization(const TMap<UObject*, UObject*>& SourceToCopy);` — Apply the parameterization to a copy of the source pipeline
- L403 _public prototype_ `void SetParameterizationSource(UDataprepParameterization& Parameterization);`
- L405 _public function_ `UObject* GetParameterizationInstance()`
- L409 _private prototype_ `void CustomClassAboutToBeUpdated();`
- L415 _private prototype_ `void CustomClassWasUpdated(const TMap<UObject*, UObject*>& OldToNew);` — Used as call back for event coming from the source parameterization Change the parametrization instance to the new object after a reinstancing
- L420 _private prototype_ `void LoadParameterization();` — Load the parameterization data on the instance from the ParameterizationInstanceStorage
- L425 _private prototype_ `void SetupCallbacksFromSourceParameterisation();` — Setup the parameterization instance so that we can react to event coming from the source parameterization
- L430 _private prototype_ `void UndoSetupForCallbacksFromParameterization();` — Clean the parameterization instance so that we can bind to a new source parameterization
- L434 _private member_ `TObjectPtr<UDataprepParameterization> SourceParameterization;` — `UPROPERTY()` — The parameterization from which this instance was constructed
- L438 _private member_ `TObjectPtr<UObject> ParameterizationInstance;` — `UPROPERTY(Transient, NonTransactional)` — The actual object on which the parameterization data is stored
- L442 _private member_ `TArray<uint8> ParameterizationInstanceStorage;` — `UPROPERTY()` — This is used only to store a serialization of the values of the parameterization since we can't save the custom class
- L444 _private member_ `FDelegateHandle OnObjectModifiedHandle;`

#### Free symbols / members of external scopes

- L90 _prototype_ `uint32 GetTypeHash(const FDataprepParameterizationBinding& Binding);`
- L92 _prototype_ `uint32 GetTypeHash(const TArray<FDataprepPropertyLink>& PropertyLinks);`
- L364 _delegate_ `DECLARE_EVENT(UDataprepParameterization, FOnCustomClassAboutToBeUpdated);`
- L368 _delegate_ `DECLARE_EVENT_OneParam(UDataprepParameterization, FOnCustomClassWasUpdated, const FMapOldToNewObjects& );`
- L371 _delegate_ `DECLARE_EVENT(UDataprepParameterization,FOnTellInstancesToReloadTheirSerializedData);`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Private/SelectionSystem/DataprepSelectionSystemUtils.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace DataprepSelectionSystemUtils`
- L16 _function_ `template< class FilterClass, class FetcherClass, class FetchedDataType> void DoFiltering(const FilterClass& Filter, const FetcherClass& Fetcher, const TArrayView<UObject* const>& Objects, TFunctionRef<void (int32 Index, bool bFetchSucceded, const FetchedDataType& FetchedData)> FilteringFunction)` (scope `DataprepSelectionSystemUtils`)
- L21 _function_ `` (scope `DataprepSelectionSystemUtils::DoFiltering`)
- L81 _function_ `template< class FilterClass, class FetcherClass, class FetchedDataType> TArray<UObject*> FilterObjects(const FilterClass& Filter, const FetcherClass& Fetcher, const TArrayView<UObject* const>& Objects)` (scope `DataprepSelectionSystemUtils`) — A implementation for the filtering of the objects using a filter and fetcher This implementation is already multi-threaded when it's possible.
- L91 _function_ `` (scope `DataprepSelectionSystemUtils::FilterObjects`)
- L127 _function_ `template<class FetchedDataType> static void UpdateReportedDataIfSupported(const FetchedDataType& FetchedData, FDataprepSelectionInfo& OutInfo)` (scope `DataprepSelectionSystemUtils`)
- L147 _function_ `template< class FilterClass, class FetcherClass, class FetchedDataType> void FilterAndGatherInfo(const FilterClass& Filter, const FetcherClass& Fetcher, const TArrayView<UObject*>& InObjects, const TArrayView<FDataprepSelectionInfo>& OutFilterResults)` (scope `DataprepSelectionSystemUtils`) — A implementation for the filtering of the objects using a filter and fetcher This one also gather additional info on how the filtering was done This implementation is already multi-threaded when it's possible.
- L155 _function_ `` (scope `DataprepSelectionSystemUtils::FilterAndGatherInfo`)
- L183 _function_ `template< class FilterClass, class FetcherClass, class FetchedDataType> void FilterAndStoreInArrayView(const FilterClass& Filter, const FetcherClass& Fetcher, const TArrayView<UObject*>& InObjects, const TArrayView<bool>& OutFilterResults)` (scope `DataprepSelectionSystemUtils`) — A implementation for the filtering of the objects using a filter and fetcher This implementation is already multi-threaded when it's possible.
- L191 _function_ `` (scope `DataprepSelectionSystemUtils::FilterAndStoreInArrayView`)

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Private/Shared/DataprepCorePrivateUtils.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace EMessageSeverity`
- L18 _namespace_ `namespace DataprepCorePrivateUtils`
- L28 _function_ `template<class TArrayClass> bool MoveArrayElement(TArrayClass& Array, int32 SourceIndex, int32 DestinationIndex)` (scope `DataprepCorePrivateUtils`) — Move an array element to another spot This operation take O(n) time. Where n is the absolute value of SourceIndex - DestinationIndex @param SourceIndex The Index of the element to move @param DestinationIndex The index of where the element will be move to @return True if the element was move
- L56 _prototype_ `void DeleteRegisteredAsset(UObject* Asset);` (scope `DataprepCorePrivateUtils`) — Mark the input object for kill and unregister it @param Asset		The object to be deleted
- L59 _prototype_ `const FString& GetRootTemporaryDir();` (scope `DataprepCorePrivateUtils`) — Returns directory where to store temporary files when running Dataprep asset
- L62 _prototype_ `const FString& GetRootPackagePath();` (scope `DataprepCorePrivateUtils`) — Returns content folder where to create temporary assets when running Dataprep asset
- L71 _prototype_ `void LogMessage(EMessageSeverity::Type Severity, const FText& Message, const FText& NotificationText = FText());` (scope `DataprepCorePrivateUtils`) — Logs messages in output log and message panel using "Dataprep Core" label @param Severity				Severity of the message to log @param Message				Message to log @param NotificationText		Text of the notification to display to alert the user @remark Notification is only done ifNotificationText is not empty
- L76 _prototype_ `void ClearAssets(const TArray< TWeakObjectPtr< UObject > >& Assets);` (scope `DataprepCorePrivateUtils`) — Clear
- L79 _prototype_ `void BuildStaticMeshes(TSet<UStaticMesh*>& StaticMeshes, TFunction<bool(UStaticMesh*)> ProgressFunction, bool bForceBuild = false);` (scope `DataprepCorePrivateUtils`) — Build the render data based on the current geometry available in the static mesh
- L85 _prototype_ `void CompileMaterial(UMaterialInterface* MaterialInterface);` (scope `DataprepCorePrivateUtils`) — Ensures the material is ready for rendering @remark This is only to be shared with the Dataprep editor
- L90 _namespace_ `namespace Analytics` (scope `DataprepCorePrivateUtils`)
- L92 _prototype_ `void RecipeExecuted( UDataprepAssetInterface* InDataprepAsset );` (scope `DataprepCorePrivateUtils::Analytics`)
- L93 _prototype_ `void DataprepAssetCreated( UDataprepAssetInterface* InDataprepAsset );` (scope `DataprepCorePrivateUtils::Analytics`)
- L94 _prototype_ `void DataprepEditorOpened( UDataprepAssetInterface* InDataprepAsset );` (scope `DataprepCorePrivateUtils::Analytics`)
- L95 _prototype_ `void ExecuteTriggered( UDataprepAssetInterface* InDataprepAsset );` (scope `DataprepCorePrivateUtils::Analytics`)
- L96 _prototype_ `void ImportTriggered( UDataprepAssetInterface* InDataprepAsset );` (scope `DataprepCorePrivateUtils::Analytics`)
- L97 _prototype_ `void CommitTriggered( UDataprepAssetInterface* InDataprepAsset );` (scope `DataprepCorePrivateUtils::Analytics`)

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Public/Blueprint/K2Node_DataprepActionCore.h` (Public)


#### class `UK2Node_DataprepActionCore`  
`class UK2Node_DataprepActionCore : public UK2Node`  
_L16-29_
- reflection: `UCLASS(Abstract)`
- inherits: `UK2Node`
- L21 _public function_ `UDataprepActionAsset* GetDataprepAction() const`
- L22 _public prototype_ `void CreateDataprepActionAsset();`
- L23 _public prototype_ `void DuplicateExistingDataprepActionAsset(const UDataprepActionAsset& DataprepAction);`
- L28 _protected member_ `TObjectPtr<UDataprepActionAsset> DataprepActionAsset;` — `UPROPERTY()`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Public/DataprepActionAsset.h` (Public)


#### class `UDataprepActionStep`  
`class UDataprepActionStep : public UObject`  
_L52-105_
- reflection: `UCLASS()`
- inherits: `UObject`
- L58 _public function_ `UDataprepActionStep() : bIsEnabled(true) , StepObject(nullptr)`
- L64 _public prototype_ `virtual void PostLoad() override;`
- L68 _public member_ `bool bIsEnabled;` — `UPROPERTY()`
- L70 _public function_ `UDataprepParameterizableObject* GetStepObject()`
- L75 _public function_ `const UDataprepParameterizableObject* GetStepObject() const`
- L80 _public function_ `TSoftClassPtr<UDataprepParameterizableObject> GetPathOfStepObjectClass()`
- L91 _private member_ `TObjectPtr<UDataprepParameterizableObject> StepObject;` — `UPROPERTY()` — The actual object of the step
- L95 _private member_ `TSoftClassPtr<UDataprepParameterizableObject> PathOfStepObjectClass;` — `UPROPERTY()` — Will be used for future error message if the step object can't be loaded
- L99 _private member_ `TObjectPtr<UDataprepOperation> Operation_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use the step and step type instead."))` — The operation will only be not null if the step is a operation
- L104 _private member_ `TObjectPtr<UDataprepFilter> Filter_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use the step and step type instead."))` — The Filter will only be not null if the step is a Filter/Selector

#### struct `FDataprepActionContext`  
`struct FDataprepActionContext`  
_L108-175_
- desc: Structure to pass execution context to action
- L110 _public function_ `FDataprepActionContext()`
- L112 _public function_ `FDataprepActionContext& SetWorld( UWorld* InWorld )`
- L118 _public function_ `FDataprepActionContext& SetAssets( TArray< TWeakObjectPtr< UObject > >& InAssets )`
- L125 _public function_ `FDataprepActionContext& SetProgressReporter( const TSharedPtr< IDataprepProgressReporter >& InProgressReporter )`
- L131 _public function_ `FDataprepActionContext& SetLogger( const TSharedPtr< IDataprepLogger >& InLogger )`
- L137 _public function_ `FDataprepActionContext& SetTransientContentFolder( const FString& InTransientContentFolder )`
- L143 _public function_ `FDataprepActionContext& SetCanExecuteNextStep( DataprepActionAsset::FCanExecuteNextStepFunc InCanExecuteNextStepFunc )`
- L149 _public function_ `FDataprepActionContext& SetActionsContextChanged( DataprepActionAsset::FActionsContextChangedFunc InActionsContextChangedFunc )`
- L156 _public member_ `TWeakObjectPtr< UWorld > WorldPtr;` — Hold onto the world the consumer will process
- L159 _public member_ `TSet< TWeakObjectPtr< UObject > > Assets;` — Set of assets the consumer will process
- L162 _public member_ `FString TransientContentFolder;` — Path to transient content folder where were created
- L165 _public member_ `TSharedPtr< IDataprepProgressReporter > ProgressReporterPtr;` — Hold onto the reporter that the consumer should use to report progress
- L168 _public member_ `TSharedPtr< IDataprepLogger > LoggerPtr;` — Hold onto the logger that the consumer should use to log messages
- L171 _public member_ `DataprepActionAsset::FCanExecuteNextStepFunc ContinueCallback;` — Delegate called by an action after the execution of each step
- L174 _public member_ `DataprepActionAsset::FActionsContextChangedFunc ContextChangedCallback;` — Delegate called by an action if the working content has changed after the execution of an operation

#### class `UDataprepActionAppearance`  
`class UDataprepActionAppearance : public UObject`  
_L179-195_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Persists graphical state of the node associated with this action asset
- L185 _public member_ `bool bIsExpanded;` — `UPROPERTY()`
- L188 _public member_ `FDeprecateSlateVector2D NodeSize;` — `UPROPERTY()`
- L191 _public member_ `int32 GroupId;` — `UPROPERTY()`
- L194 _public member_ `bool bGroupIsEnabled;` — `UPROPERTY()`

#### class `UDataprepActionAsset`  
`class UDataprepActionAsset : public UObject`  
_L203-519_
- reflection: `UCLASS()`
- inherits: `UObject`
- L209 _public prototype_ `UDataprepActionAsset();`
- L211 _public prototype_ `virtual ~UDataprepActionAsset();`
- L214 _public prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L222 _public prototype_ `void Execute(const TArray<UObject*>& InObjects);` — `UFUNCTION(BlueprintCallable, Category = "Execution")` — Execute the action on a specific set of objects @param Objects The objects on which the action will operate
- L231 _public prototype_ `void ExecuteAction(const TSharedPtr<FDataprepActionContext>& InActionsContext, UDataprepActionStep* SpecificStep = nullptr, bool bSpecificStepOnly = true);` — Execute the action @param InActionsContext	Shared context which the action's steps will be executed on @param SpecificStep		Specific step to execute within the action @param bOnly				If true (default), only the specific step is executed, otherwise the action is executed up to the specific step
- L238 _public prototype_ `int32 AddStep(TSubclassOf<UDataprepParameterizableObject> StepType);` — Add a new step base on the type of step @param StepType This type of operation or fetcher(filter) we want to use @return The index of the added step or index none if the StepType is invalid
- L245 _public prototype_ `int32 AddStep(const UDataprepActionStep* ActionStep);` — Add a copy of the step to the action @param ActionStep The step we want to duplicate in the action @return The index of the added step or index none if the step is invalid
- L252 _public prototype_ `int32 AddSteps(const TArray<const UDataprepActionStep*>& ActionSteps);` — Add a copy of each step to the action @param ActionSteps The array of steps we want to duplicate in the action @return The index of the last added step or index none if no step is invalid
- L259 _public prototype_ `int32 AddStep(const UDataprepParameterizableObject* StepObject);` — Add a copy of the step object to the action @param StepObject The step object we want to duplicate in the action @return The index of the added step or index none if the step is invalid
- L267 _public prototype_ `bool InsertStep(const UDataprepActionStep* ActionStep, int32 Index);` — Insert a copy of the step into the action at the requested index @param Index Index to insert the action step at @param ActionStep The step to duplicate in the action @return The index of the added step or index none if the step is invalid
- L275 _public prototype_ `bool InsertSteps(const TArray<const UDataprepActionStep*>& ActionSteps, int32 Index);` — Insert a copy of each step into the action at the requested index @param Index Index to insert the action step at @param ActionSteps The array of steps to duplicate in the action @return The index of the added step or index none if the step is invalid
- L282 _public prototype_ `TWeakObjectPtr<UDataprepActionStep> GetStep(int32 Index);` — Access to a step of the action @param Index the index of the desired step @return A pointer to the step if it exist, otherwise nullptr
- L289 _public prototype_ `const TWeakObjectPtr<UDataprepActionStep> GetStep(int32 Index) const;` — Access to a step of the action @param Index the index of the desired step @return A const pointer to the operation if it exist, otherwise nullptr
- L295 _public prototype_ `int32 GetStepsCount() const;` — Get the number of steps of this action @return The number of steps
- L302 _public prototype_ `bool IsStepEnabled(int32 Index) const;` — Get enabled status of an operation @param Index The index of the operation @return True if the operation is enabled. Always return false if the operation index is invalid
- L309 _public prototype_ `void EnableStep(int32 Index, bool bEnable);` — Allow to set the enabled state of a step @param Index The index of the step @param bEnable The new enabled state of the step
- L318 _public prototype_ `bool MoveStep(int32 StepIndex, int32 DestinationIndex);` — Move a step to another spot in the order of steps This operation take O(n) time. Where n is the absolute value of StepIndex - DestinationIndex @param StepIndex The Index of the step to move @param DestinationIndex The index of where the step will be move to @return True if the step was move
- L325 _public prototype_ `bool SwapSteps(int32 FirstIndex, int32 SecondIndex);` — Swap the steps @param FirstIndex The index of the first step @param SecondIndex The index of the seconds step
- L333 _public prototype_ `bool RemoveStep(int32 Index, bool bDiscardParametrization = true);` — Remove a step from the action @param Index The index of the step to remove @param bDiscardParametrization If true, remove parameterization associated with action steps @return True if a step was removed
- L341 _public prototype_ `bool RemoveSteps(const TArray<int32>& Indices, bool bDiscardParametrization = true);` — Remove an array of steps from the action @param Indices Array of step indices to remove @param bDiscardParametrization If true, remove parameterization associated with action steps @return True if at least one step has been removed
- L347 _public prototype_ `FOnStepsOrderChanged& GetOnStepsOrderChanged();` — Allow an observer to be notified when the steps order changed that also include adding and removing steps @return The delegate that will be broadcasted when the steps order changed
- L353 _public prototype_ `FOnStepAboutToBeRemoved& GetOnStepAboutToBeRemoved();` — Allow an observer to be notified when a step is about to be removed from the action @return The event that will be broadcasted
- L359 _public prototype_ `FOnStepWasEdited& GetOnStepWasEdited();` — Allow an observer to be notified when a step was edited (the step itself or a sub object of it) @return The event that will be broadcasted
- L364 _public prototype_ `UDataprepActionAppearance* GetAppearance();` — @return The appearance information associated with this action asset
- L367 _public member_ `bool bExecutionInterrupted;` — `UPROPERTY(Transient)`
- L370 _public member_ `bool bIsEnabled;` — `UPROPERTY()`
- L373 _public function_ `const TCHAR* GetLabel() const` — Getter and Setter on the UI text of the action
- L374 _public function_ `void SetLabel( const TCHAR* InLabel )`
- L379 _public prototype_ `void NotifyDataprepSystemsOfRemoval();` — Do the necessary notification so that the Dataprep system can react properly to removal of this action
- L387 _public prototype_ `int32 AddOperation(const TSubclassOf<UDataprepOperation>& OperationClass);` — `UE_DEPRECATED(4.26, "Please use the function add step and simply pass the OperationClass")` — Add an operation to the action @param OperationClass The class of the operation @return The index of the added operation or index none if the class is
- L397 _public prototype_ `int32 AddFilterWithAFetcher(const TSubclassOf<UDataprepFilter>& FilterClass, const TSubclassOf<UDataprepFetcher>& FetcherClass);` — `UE_DEPRECATED(4.26, "Please use the function add step and simply pass the FetcherClass")` — Add a filter and setup it's fetcher @param FilterClass The type of filter we want @param FetcherClass The type of fetcher that we want. @return The index of the added filter or index none if the classes are incompatible or invalid Note that fetcher most be compatible with the filter
- L406 _private prototype_ `UObject* OnAddAsset(const UObject* Asset, const TCHAR* AssetName);` — Duplicate and add an asset to the Dataprep's and action's working set @param Asset			If not null, the asset will be duplicated @param AssetName		Name of the asset to create. Name collision will be performed before naming the asset @returns				The asset newly created
- L414 _private prototype_ `UObject* OnCreateAsset(UClass* AssetClass, const TCHAR* AssetName);` — Create and add an asset to the Dataprep's and action's working set @param AssetClass	If Asset is null, an asset of the given class will be returned @param AssetName		Name of the asset to create. Name collision will be performed before naming the asset @returns				The asset newly created
- L422 _private prototype_ `AActor* OnCreateActor(UClass* ActorClass, const TCHAR* ActorName);` — Add an actor to the Dataprep's transient world and action's working set @param ActorClass	Class of the actor to create @param ActorName		Name of the actor to create. Name collision will be performed before naming the asset @returns				The actor newly created
- L432 _private prototype_ `void OnRemoveObject(UObject* Object, bool bLocalContext);` — Remove an object from the Dataprep's and/or action's working set @param Object			Object to be removed from the working set @param bLocalContext		If set to true, the object is removed from the current working set. The object will not be accessible to any subsequent operation using the current context. If set to false, the object is removed from the Dataprep's working set. The object will not be accessible to any subsequent operation in the Dataprep's pipeline.
- L438 _private prototype_ `void OnAssetsModified(TArray<UObject*> Assets);` — Add an array of assets to the list of modified assets @param Assets		An array of assets which have been modifed
- L448 _private prototype_ `void OnDeleteObjects( TArray<UObject*> Objects);` — Delete an array of objects from the Dataprep's and action's working set @param Objects		The array of objects to delete @remark	The deletion of the object is deferred. However, if the object is not an asset, it is removed from the Dataprep's transient world. If the object is an asset, it is moved to the transient package, no action is taken to clean up any object referencing this asset. @remark	After execution, the object is not accessible by any subsequent operation in the Dataprep's pipeline.
- L454 _private prototype_ `void ProcessWorkingSetChanged();` — Executes the deletion and removal requested by an operation after its execution Notifies any observer about what has changed
- L457 _private prototype_ `UObject* GetAssetOuterByClass( UClass* AssetClass );` — Returns the outer to be used according to an asset's class
- L460 _private prototype_ `void AddAssetToContext( UObject* NewAsset, const TCHAR* DesiredName );` — Add an asset to the execution context
- L463 _private prototype_ `UDataprepActionStep* DuplicateStep(const UDataprepActionStep* InActionStep);` — Creates a copy af action step, including its parameterization
- L467 _private member_ `TArray<TObjectPtr<UDataprepActionStep>> Steps;` — `UPROPERTY()` — Array of operations and/or filters constituting this action
- L470 _private member_ `TObjectPtr<UDataprepActionAppearance> Appearance;` — `UPROPERTY()`
- L473 _private member_ `FOnStepsOrderChanged OnStepsOrderChanged;` — Broadcasts any change to the stack of steps
- L476 _private member_ `FOnStepAboutToBeRemoved OnStepsAboutToBeRemoved;` — Broadcast when a step is about to be removed
- L479 _private member_ `FOnStepWasEdited OnStepWasEdited;` — Broacast when a subobject of a step or a step object was edited
- L481 _private member_ `FDelegateHandle OnAssetDeletedHandle;`
- L484 _private member_ `TSharedPtr<FDataprepActionContext> ContextPtr;` — Pointer to the context passed to the action for its execution
- L487 _private member_ `TSharedPtr<FDataprepOperationContext> OperationContext;` — Context passed to the operation for its execution
- L490 _private member_ `TArray<UObject*> ObjectsToDelete;` — Array of objects requested to be deleted by an operation
- L493 _private member_ `TSet< TWeakObjectPtr< UObject > > ModifiedAssets;` — Set of objects which have been modified during the execution of an operation
- L496 _private member_ `TArray<UObject*> AddedObjects;` — Array of objects which have been added during the execution of an operation
- L499 _private member_ `TArray<TPair<UObject*,bool>> ObjectsToRemove;` — Array of objects requested to be removed by an operation
- L502 _private member_ `bool bWorkingSetHasChanged;` — Marker to check if an operation has made any changes to the action's working set
- L506 _private member_ `FString Label;` — `UPROPERTY(EditAnywhere, Category = "Label")` — UI label of the action
- L509 _private member_ `TWeakObjectPtr< UPackage > PackageForStaticMesh;` — Package which static meshes will be added to
- L512 _private member_ `TWeakObjectPtr< UPackage > PackageForTexture;` — Package which textures will be added to
- L515 _private member_ `TWeakObjectPtr< UPackage > PackageForMaterial;` — Package which materials will be added to
- L518 _private member_ `TWeakObjectPtr< UPackage > PackageForAnimation;` — Package which level sequences will be added to

#### Free symbols / members of external scopes

- L31 _namespace_ `namespace DataprepActionAsset`
- L39 _typedef_ `typedef TFunction<bool(UDataprepActionAsset* )> FCanExecuteNextStepFunc;` (scope `DataprepActionAsset`) — Callback function used to confirm continuation after executing an operation or a filter @param ActionAsset			The action asset checking for continuation @param OperationExecuted		Executed operation if not null @param FilterExecuted		Executed filter if not null
- L48 _typedef_ `typedef TFunction<void(const UDataprepActionAsset* , bool , bool , const TArray< TWeakObjectPtr<UObject> >& )> FActionsContextChangedFunc;` (scope `DataprepActionAsset`) — Callback used to report a global change to the content it is working on @param ActionAsset		The action asset reporting the change @param bWorldChanged		Indicates changes happened in the world @param bAssetChanged		Indicates the set of assets has changed @param NewAssets			New set of assets. Only valid if bAssetChanged is true
- L198 _delegate_ `DECLARE_EVENT(UDataprepActionAsset, FOnStepsOrderChanged);`
- L198 _prototype_ `DECLARE_EVENT(UDataprepActionAsset, FOnStepsOrderChanged);`
- L199 _delegate_ `DECLARE_EVENT_OneParam(UDataprepActionAsset, FOnStepAboutToBeRemoved, UDataprepParameterizableObject* );`
- L199 _prototype_ `DECLARE_EVENT_OneParam(UDataprepActionAsset, FOnStepAboutToBeRemoved, UDataprepParameterizableObject* );`
- L200 _delegate_ `DECLARE_EVENT_TwoParams(UDataprepParameterizableObject, FOnStepWasEdited, UDataprepParameterizableObject* , struct FPropertyChangedChainEvent&) UCLASS() class UDataprepActionAsset : public UObject { GENERATED_BODY() public: UDataprepActionAsset(); virtual ~UDataprepActionAsset();`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Public/DataprepAsset.h` (Public)


#### class `UDataprepAsset`  
`class UDataprepAsset : public UDataprepAssetInterface`  
_L30-257_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UDataprepAssetInterface`
- desc: A DataprepAsset is an implementation of the DataprepAssetInterface using a Blueprint as the recipe pipeline. The Blueprint is composed of DataprepAction nodes linearly connected.
- L35 _public prototype_ `virtual ~UDataprepAsset() = default;`
- L38 _public prototype_ `virtual void PostLoad() override;` — UObject interface
- L39 _public prototype_ `virtual bool Rename(const TCHAR* NewName , UObject* NewOuter , ERenameFlags Flags ) override;`
- L40 _public prototype_ `virtual void PreEditUndo() override;`
- L41 _public prototype_ `virtual void PostEditUndo() override;`
- L42 _public prototype_ `virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;`
- L46 _public prototype_ `virtual void ExecuteRecipe( const TSharedPtr<FDataprepActionContext>& InActionsContext ) override;` — UDataprepAssetInterface interface
- L47 _public function_ `virtual bool HasActions() const override`
- L48 _public function_ `virtual const TArray<UDataprepActionAsset*>& GetActions() const override`
- L50 _private prototype_ `virtual TArray<UDataprepActionAsset*> GetCopyOfActions(TMap<UObject*,UObject*>& OutOriginalToCopy) const override;`
- L54 _public function_ `int32 GetActionCount() const`
- L56 _public function_ `UDataprepActionAsset* GetAction(int32 Index)`
- L61 _public prototype_ `const UDataprepActionAsset* GetAction(int32 Index) const;`
- L63 _public function_ `int32 GetActionIndex(UDataprepActionAsset* ActionAsset) const`
- L74 _public prototype_ `int32 AddAction(const UDataprepActionAsset* Action = nullptr);` — Add a copy of the action to the Dataprep asset @param Action The action we want to duplicate in the Dataprep asset. Parameter can be null @return The index of the added action or index none if the action is invalid @remark If action is nullptr, a new DataprepActionAsset is simply created
- L83 _public prototype_ `int32 AddAction(const TArray<const UDataprepActionStep*>& ActionSteps);` — Creates an action from the array of action steps or one action per action steps then add the action(s) to the Dataprep asset @param ActionSteps The array of action steps to process @param bCreateOne Indicates if one or more action assets should be created. By default one is created @return The index of the last added action or index none if the action is invalid
- L91 _public prototype_ `int32 AddActions(const TArray<const UDataprepActionAsset*>& Actions);` — Add the actions to the Dataprep asset @param Actions The array of action to add @param bCreateOne Indicates if one or more action assets should be created. By default one is created @return The index of the last added action or index none if the action is invalid
- L99 _public prototype_ `bool InsertAction(int32 Index);` — Creates a new action then insert the action to the Dataprep asset at the requested index @param Index The index at which the insertion must happen @return True if the insertion is successful, false if the index is invalid
- L108 _public prototype_ `bool InsertAction(const TArray<const UDataprepActionStep*>& InActionSteps, int32 Index);` — Creates an action from the array of action steps or one action per action steps then insert the action(s) to the Dataprep asset at the requested index @param ActionSteps The array of action steps to process @param Index The index at which the insertion must happen @return True if the insertion is successful, false if the action steps or the index are invalid
- L116 _public prototype_ `bool InsertAction(const UDataprepActionAsset* InAction, int32 Index);` — Insert a copy of the action to the Dataprep asset at the requested index @param Action The action we want to duplicate in the Dataprep asset @param Index The index at which the insertion must happen @return True if the insertion is successful, false if the action or the index are invalid
- L124 _public prototype_ `bool InsertActions(const TArray<const UDataprepActionAsset*>& InActions, int32 Index);` — Insert a copy of each action into the Dataprep asset at the requested index @param Actions The array of actions to insert @param Index The index at which the insertion must happen @return True if the insertion is successful, false if the actions or the index are invalid
- L133 _public prototype_ `bool MoveAction(int32 SourceIndex, int32 DestinationIndex);` — Move an action to another spot in the order of actions This operation take O(n) time. Where n is the absolute value of SourceIndex - DestinationIndex @param SourceIndex The Index of the action to move @param DestinationIndex The index of where the action will be move to @return True if the action was moved
- L142 _public prototype_ `bool MoveActions(int32 FirstIndex, int32 Count, int32 MovePositions);` — Move group of actions to another spot in the order of actions @param FirstIndex The Index of the first action to move @param Count Number of actions to move @param MovePositions How many positions/offset (can be negative too) to move the actions @return True if the action group was moved
- L149 _public prototype_ `bool SwapActions(int32 FirstActionIndex, int32 SecondActionIndex);` — Swap the actions of a Dataprep asset @param FirstActionIndex The index of the first action @param SecondActionIndex The index of the second action
- L157 _public prototype_ `bool RemoveAction(int32 Index, bool bDiscardParametrization = true);` — Remove an action from the Dataprep asset @param Index The index of the action to remove @param bDiscardParametrization If true, remove parameterization associated with action steps @return True if the action was removed
- L165 _public prototype_ `bool RemoveActions(const TArray<int32>& Indices, bool bDiscardParametrization = true);` — Remove a set of actions from the Dataprep asset @param Index The index of the action to remove @param bDiscardParametrization If true, remove parameterization associated with action steps @return True if the action was removed
- L171 _public function_ `DECLARE_EVENT_TwoParams(UDataprepAsset, FOnDataprepActionAssetChange, UObject* , FDataprepAssetChangeType) FOnDataprepActionAssetChange& GetOnActionChanged()` — Allow an observer to be notified of an change in the pipeline return The event that will be broadcasted when a object has receive a modification that might change the result of the pipeline
- L177 _public function_ `DECLARE_EVENT_OneParam(UDataprepAsset, FOnStepObjectsAboutToBeRemoved, const TArrayView<UDataprepParameterizableObject*>&) FOnStepObjectsAboutToBeRemoved& GetOnStepObjectsAboutToBeRemoved()` — Allow an observer to be notified of the removal of some step from the asset
- L187 _public prototype_ `bool CreateParameterization();`
- L197 _public prototype_ `DECLARE_EVENT_OneParam(UDataprepParameterization, FDataprepParameterizationStatusForObjectsChanged, const TSet<UObject*>* ) FDataprepParameterizationStatusForObjectsChanged OnParameterizedObjectsStatusChanged;` — Event to notify the ui that a Dataprep parametrization was modified This necessary as the ui for the parameterization is only updated by manual event (the ui don't pull new values each frame) Note on the objects param: The parameterized objects that should refresh their ui. If nullptr all widgets that can display some info on the parameterization should be refreshed
- L201 _public prototype_ `virtual UObject* GetParameterizationObject() override;` — Internal Use only (the current implementation might be subject to change)
- L203 _public prototype_ `void BindObjectPropertyToParameterization(UDataprepParameterizableObject* Object, const TArray<struct FDataprepPropertyLink>& InPropertyChain,const FName& Name);`
- L205 _public prototype_ `bool IsObjectPropertyBinded(UDataprepParameterizableObject* Object, const TArray<struct FDataprepPropertyLink>& InPropertyChain) const;`
- L207 _public prototype_ `FName GetNameOfParameterForObjectProperty(UDataprepParameterizableObject* Object, const TArray<struct FDataprepPropertyLink>& InPropertyChain) const;`
- L209 _public prototype_ `void RemoveObjectPropertyFromParameterization(UDataprepParameterizableObject* Object, const TArray<struct FDataprepPropertyLink>& InPropertyChain);`
- L211 _public prototype_ `void GetExistingParameterNamesForType(FProperty* Property, bool bIsDescribingFullProperty, TSet<FString>& OutValidExistingNames, TSet<FString>& OutInvalidNames) const;`
- L214 _public function_ `UDataprepParameterization* GetDataprepParameterization()` — Internal only for now
- L220 _protected member_ `TObjectPtr<UBlueprint> DataprepRecipeBP_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Using directly ActionAssets property instead of Blueprint to manage actions."))` — DEPRECATED: Pointer to data preparation pipeline blueprint previously used to process input data
- L225 _protected member_ `TArray< FDataprepAssetProducer > Producers_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Property moved to UDataprepAssetInterface as Inputs."))` — DEPRECATED: List of producers referenced by the asset
- L229 _protected member_ `TObjectPtr<UDataprepContentConsumer> Consumer_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Property moved to UDataprepAssetInterface as Output."))` — DEPRECATED: COnsumer referenced by the asset
- L234 _private prototype_ `void OnOldAssetLoaded(UObject* Asset);` — Handler for when an Dataprep asset from version prior to 4.25 is loaded
- L237 _private prototype_ `FString HashActionsAppearance() const;` — Create string hash from all of the current actions's appearances
- L242 _private member_ `TObjectPtr<UEdGraphNode> StartNode_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Using directly ActionAssets property instead of Blueprint to manage actions."))` — DEPRECATED: Pointer to the entry node of the pipeline blueprint previously used to process input data
- L245 _private member_ `TObjectPtr<UDataprepParameterization> Parameterization;` — `UPROPERTY()`
- L248 _private member_ `TArray<TObjectPtr<UDataprepActionAsset>> ActionAssets;` — `UPROPERTY()`
- L250 _private member_ `FOnDataprepActionAssetChange OnActionChanged;`
- L252 _private member_ `FOnStepObjectsAboutToBeRemoved OnStepObjectsAboutToBeRemoved;`
- L255 _private member_ `FString SignatureBeforeUndoRedo;` — Used on undo/redo to detect addition/removal compared to change in execution order of actions
- L256 _private member_ `FString AppearanceSignatureBeforeUndoRedo;`

#### struct `UDataprepAsset::FRestrictedToActionAsset`  
`struct FRestrictedToActionAsset`  
_L180-185_
- L184 _private prototype_ `static void NotifyAssetOfTheRemovalOfSteps(UDataprepAsset& DataprepAsset, const TArrayView<UDataprepParameterizableObject*>& StepObjects);`

#### Free symbols / members of external scopes

- L171 _delegate_ `DECLARE_EVENT_TwoParams(UDataprepAsset, FOnDataprepActionAssetChange, UObject* , FDataprepAssetChangeType) FOnDataprepActionAssetChange& GetOnActionChanged() { return OnActionChanged; } DECLARE_EVENT_OneParam(UDataprepAsset, FOnStepObjectsAboutToBeRemoved, const TArrayView<UDataprepParameterizableObject*>&) FOnStepObjectsAboutToBeRemoved& GetOnStepObjectsAboutToBeRemoved() { return OnStepObjectsAboutToBeRemoved; } struct FRestrictedToActionAsset { private: friend UDataprepActionAsset; static void NotifyAssetOfTheRemovalOfSteps(UDataprepAsset& DataprepAsset, const TArrayView<UDataprepParameterizableObject*>& StepObjects); };` — Allow an observer to be notified of an change in the pipeline return The event that will be broadcasted when a object has receive a modification that might change the result of the pipeline
- L177 _delegate_ `DECLARE_EVENT_OneParam(UDataprepAsset, FOnStepObjectsAboutToBeRemoved, const TArrayView<UDataprepParameterizableObject*>&) FOnStepObjectsAboutToBeRemoved& GetOnStepObjectsAboutToBeRemoved() { return OnStepObjectsAboutToBeRemoved; } struct FRestrictedToActionAsset { private: friend UDataprepActionAsset; static void NotifyAssetOfTheRemovalOfSteps(UDataprepAsset& DataprepAsset, const TArrayView<UDataprepParameterizableObject*>& StepObjects); };` — Allow an observer to be notified of the removal of some step from the asset
- L197 _delegate_ `DECLARE_EVENT_OneParam(UDataprepParameterization, FDataprepParameterizationStatusForObjectsChanged, const TSet<UObject*>* ) FDataprepParameterizationStatusForObjectsChanged OnParameterizedObjectsStatusChanged;` — Event to notify the ui that a Dataprep parametrization was modified This necessary as the ui for the parameterization is only updated by manual event (the ui don't pull new values each frame) Note on the objects param: The parameterized objects that should refresh their ui. If nullptr all widgets that can display some info on the parameterization should be refreshed

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Public/DataprepAssetInstance.h` (Public)


#### class `UDataprepAssetInstance`  
`class UDataprepAssetInstance : public UDataprepAssetInterface`  
_L22-76_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UDataprepAssetInterface`
- desc: A DataprepAssetInstance is an implementation of the DataprepAssetInterface sharing its recipe pipeline with an existing Dataprep asset or another DataprepAssetInstance. It has its own inputs and output. It has overrides of the externalized parameters of the pipeline.
- L27 _public function_ `UDataprepAssetInstance() : Parent(nullptr)`
- L32 _public prototype_ `virtual ~UDataprepAssetInstance() = default;`
- L35 _public prototype_ `virtual void PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L39 _public prototype_ `virtual void ExecuteRecipe( const TSharedPtr<FDataprepActionContext>& InActionsContext ) override;` — UDataprepAssetInterface interface
- L40 _public function_ `virtual bool HasActions() const override`
- L41 _public prototype_ `virtual UObject* GetParameterizationObject() override;`
- L42 _public prototype_ `virtual const TArray<UDataprepActionAsset*>& GetActions() const override;`
- L44 _private prototype_ `virtual TArray<UDataprepActionAsset*> GetCopyOfActions(TMap<UObject*,UObject*>& OutOriginalToCopy) const override;`
- L48 _public function_ `const UDataprepAssetInterface* GetParent() const`
- L49 _public prototype_ `bool SetParent(UDataprepAssetInterface* InParent, bool bNotifyChanges = true);`
- L55 _public function_ `DECLARE_EVENT(UDataprepAssetInstance, FOnDataprepAssetInstanceChanged ) FOnDataprepAssetInstanceChanged& GetOnParentChanged()` — Allow an observer to be notified when the parent asset has changed @return The delegate that will be broadcasted when the parent asset has changed
- L61 _protected member_ `TObjectPtr<UDataprepAssetInterface> Parent;` — `UPROPERTY()` — Parent Dataprep asset's interface
- L64 _protected member_ `TObjectPtr<UDataprepParameterizationInstance> Parameterization;` — `UPROPERTY()`
- L67 _protected member_ `FOnDataprepAssetInstanceChanged OnParentChanged;` — Delegate broadcasted when the consumer or one of the producers has changed
- L71 _private prototype_ `UDataprepAsset* GetRootParent(UDataprepAssetInterface* InParent);` — Returns a pointer to the UDataprepAsset
- L75 _private member_ `TArray<TObjectPtr<UDataprepActionAsset>> ActionsFromDataprepAsset;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L55 _delegate_ `DECLARE_EVENT(UDataprepAssetInstance, FOnDataprepAssetInstanceChanged ) FOnDataprepAssetInstanceChanged& GetOnParentChanged() { return OnParentChanged; } protected: UPROPERTY() TObjectPtr<UDataprepAssetInterface> Parent;` — Allow an observer to be notified when the parent asset has changed @return The delegate that will be broadcasted when the parent asset has changed

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Public/DataprepAssetInterface.h` (Public)


#### enum `FDataprepAssetChangeType`  
`enum class FDataprepAssetChangeType : uint8`  
_L18-30_
- L20 _public enumerator_ `ProducerAdded`
- L21 _public enumerator_ `ProducerRemoved`
- L22 _public enumerator_ `ProducerModified`
- L23 _public enumerator_ `ConsumerModified`
- L24 _public enumerator_ `RecipeModified`
- L25 _public enumerator_ `ActionAdded`
- L26 _public enumerator_ `ActionModified`
- L27 _public enumerator_ `ActionMoved`
- L28 _public enumerator_ `ActionRemoved`
- L29 _public enumerator_ `ActionAppearanceModified`

#### class `UDataprepRecipeInterface`  
`class UDataprepRecipeInterface : public UObject`  
_L40-55_
- reflection: `UCLASS(Abstract, BlueprintType)`
- inherits: `UObject`
- desc: A DataprepAssetInterface is composed of a set of producers, inputs, a consumer, output, and a recipe, set of actions. The producers generate assets and populate a given world. The pipeline modifies the assets and the actors of the given world. Finally, the consumer converts the assets and the given world. An FBX exporter is a possible consumer. This class is an abstract modeling the data preparation pipeline.
- L49 _public function_ `DECLARE_EVENT(UDataprepRecipeInterface, FOnDataprepRecipeChanged ) FOnDataprepRecipeChanged& GetOnChanged()` — Allow an observer to be notified when when the recipe has changed @return The delegate that will be broadcasted when the recipe has changed
- L54 _protected member_ `FOnDataprepRecipeChanged OnChanged;` — Delegate broadcasted when the recipe has changed

#### class `UDataprepAssetInterface`  
`class UDataprepAssetInterface : public UObject`  
_L58-185_
- reflection: `UCLASS(Abstract, BlueprintType)`
- inherits: `UObject`
- L63 _public prototype_ `UDataprepAssetInterface();`
- L66 _public prototype_ `virtual void PostLoad() override;` — UObject interface
- L67 _public prototype_ `virtual void PostInitProperties() override;`
- L70 _public prototype_ `virtual ~UDataprepAssetInterface() = default;`
- L73 _public function_ `const UDataprepRecipeInterface* GetRecipe() const` — @return pointer on the recipe
- L75 _public function_ `UDataprepRecipeInterface* GetRecipe()`
- L78 _public function_ `const UDataprepContentConsumer* GetConsumer() const` — @return pointer on the consumer
- L80 _public function_ `UDataprepContentConsumer* GetConsumer()`
- L88 _public prototype_ `UDataprepContentConsumer* SetConsumer( UClass* NewConsumerClass, bool bNotifyChanges = true );` — Create a new consumer of the given class @param NewConsumerClass	Class of the consumer create @param bNotifyChanges	Indicates if observers should be notified of changes @return a pointer on the newly created consumer. Null pointer if the creation failed.
- L91 _public function_ `const UDataprepAssetProducers* GetProducers() const` — @return pointer on the producers
- L93 _public function_ `UDataprepAssetProducers* GetProducers()`
- L100 _public prototype_ `virtual TArray< TWeakObjectPtr< UObject > > RunProducers(const FDataprepProducerContext& InContext);` — Run all producers of the Dataprep asset @param InContext		Context containing all the data required to properly run producers @param OutAssets		Array of assets filled up by the producers when run
- L107 _public prototype_ `virtual bool RunConsumer(const FDataprepConsumerContext& InContext);` — Run the consumer associated with the Dataprep asset @param InContext		Context containing all the data required to properly run a consumer @return false if the consumer failed to execute
- L114 _public function_ `virtual void ExecuteRecipe(const TSharedPtr<FDataprepActionContext>& InActionsContext)` — Sequentially execute all the actions held by the Dataprep asset @param InOutContext	Context containing all the data required to properly run actions @remark The context can be modified by one or more actions. The caller must check on that
- L118 _public function_ `virtual bool HasActions() const` — @return True if the Dataprep recipe is actionable
- L121 _public prototype_ `virtual const TArray<UDataprepActionAsset*>& GetActions() const;` — @return the array of actions of the recipe
- L124 _public function_ `virtual UObject* GetParameterizationObject()` — Temporary function to allow the dataprep editor to show the parametrization
- L134 _public function_ `DECLARE_EVENT_OneParam(UDataprepAssetInterface, FOnDataprepAssetChanged, FDataprepAssetChangeType ) FOnDataprepAssetChanged& GetOnChanged()` — Allow an observer to be notified when the consumer or one of the producer has changed @return The delegate that will be broadcasted when the consumer or one of the producer has changed
- L142 _protected member_ `TObjectPtr<UDataprepRecipeInterface> Recipe;` — `UPROPERTY()` — Recipe associated to the Dataprep asset
- L146 _protected member_ `TObjectPtr<UDataprepAssetProducers> Inputs;` — `UPROPERTY()` — Producers associated to the Dataprep asset
- L150 _protected member_ `TObjectPtr<UDataprepContentConsumer> Output;` — `UPROPERTY()` — Consumer associated to the Dataprep asset
- L160 _protected prototype_ `void OnProducersChanged(FDataprepAssetChangeType , int32 );` — Answer notification that the producer has changed @param ChangeType	Type of change made on the producers, added, removed or modified @param Index			Index of the producer which has changed. Unused.
- L163 _protected prototype_ `void OnConsumerChanged();` — Answer notification that the consumer has changed
- L166 _protected prototype_ `void OnRecipeChanged();` — Answer notification that the recipe has changed
- L169 _protected prototype_ `void ExecuteRecipe_Internal(const TSharedPtr<FDataprepActionContext>& InActionsContext, const TArray<UDataprepActionAsset*>& ActionAssets);` — Does the actual execution of the pipeline with the specified action list
- L173 _private function_ `virtual TArray<UDataprepActionAsset*> GetCopyOfActions(TMap<UObject*,UObject*>& OutOriginalToCopy) const` — Get a copy of the Actions from the recipe with map of the original object to the copy objects
- L184 _protected member_ `FOnDataprepAssetChanged OnChanged;` — Delegate broadcasted when the consumer or one of the producers has changed

#### Free symbols / members of external scopes

- L49 _delegate_ `DECLARE_EVENT(UDataprepRecipeInterface, FOnDataprepRecipeChanged ) FOnDataprepRecipeChanged& GetOnChanged() { return OnChanged; } protected: FOnDataprepRecipeChanged OnChanged;` — Allow an observer to be notified when when the recipe has changed @return The delegate that will be broadcasted when the recipe has changed
- L134 _delegate_ `DECLARE_EVENT_OneParam(UDataprepAssetInterface, FOnDataprepAssetChanged, FDataprepAssetChangeType ) FOnDataprepAssetChanged& GetOnChanged() { return OnChanged; } protected: #if WITH_EDITORONLY_DATA UPROPERTY() TObjectPtr<UDataprepRecipeInterface> Recipe;` — Allow an observer to be notified when the consumer or one of the producer has changed @return The delegate that will be broadcasted when the consumer or one of the producer has changed

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Public/DataprepAssetProducers.h` (Public)


#### struct `FDataprepAssetProducer`  
`struct FDataprepAssetProducer`  
_L17-42_
- reflection: `USTRUCT()`
- desc: Structure to hold on a producer and its configuration
- L21 _public function_ `FDataprepAssetProducer()`
- L23 _public function_ `FDataprepAssetProducer(UDataprepContentProducer* InProducer, bool bInEnabled ) : Producer(InProducer) , bIsEnabled( bInEnabled )`
- L28 _public function_ `FDataprepAssetProducer(UDataprepContentProducer* InProducer, bool bInEnabled, int32 SuperseedingIndex ) : Producer(InProducer) , bIsEnabled( bInEnabled ) , SupersededBy( SuperseedingIndex )`
- L35 _public member_ `TObjectPtr<UDataprepContentProducer> Producer = nullptr;` — `UPROPERTY()`
- L38 _public member_ `bool bIsEnabled = true;` — `UPROPERTY()`
- L41 _public member_ `int32 SupersededBy = INDEX_NONE;` — `UPROPERTY()`

#### class `UDataprepAssetProducers`  
`class UDataprepAssetProducers : public UObject`  
_L50-197_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: A UDataprepAssetProducers is a utility class to manage the set of producers constituting the inputs of a DataprepAssetInterface. It provides a set of methods to edit the set of producers and their respective configuration.
- L55 _public prototype_ `virtual ~UDataprepAssetProducers() = default;`
- L58 _public prototype_ `virtual void Serialize( FArchive& Ar ) override;` — UObject interface
- L59 _public prototype_ `virtual void PostEditUndo() override;`
- L67 _public prototype_ `UDataprepContentProducer* AddProducer(UClass* ProducerClass);` — Add a producer of a given class @param ProducerClass Class of the Producer to add @return true if addition was successful, false otherwise
- L74 _public prototype_ `UDataprepContentProducer* AddProducerAutomated(UClass* ProducerClass);` — Add a producer of a given class but don't pop any ui @param ProducerClass Class of the Producer to add @return true if addition was successful, false otherwise
- L81 _public prototype_ `UDataprepContentProducer* CopyProducer( const UDataprepContentProducer* InProducer );` — Add a copy of a producer @param InProducer	Producer to duplicate @return true if addition was successful, false otherwise
- L88 _public prototype_ `bool RemoveProducer( int32 IndexToRemove );` — Remove the producer at a given index @param IndexToRemove Index of the producer to remove @return true if remove was successful, false otherwise
- L93 _public prototype_ `void RemoveAllProducers();` — Remove all producers
- L99 _public prototype_ `void EnableProducer(int32 Index, bool bValue);` — Enable/Disable the producer at a given index @param Index Index of the producer to update
- L105 _public prototype_ `bool EnableAllProducers(bool bValue);` — Enable/Disable the producer at a given index @param Index Index of the producer to update
- L111 _public function_ `void ToggleProducer( int32 Index )` — Toggle the producer at a given index @param Index Index of the producer to update
- L116 _public function_ `int32 GetProducersCount() const`
- L119 _public prototype_ `const UDataprepContentProducer* GetProducer(int32 Index) const;` — @return pointer on producer at Index-th position in AssetProducers array. nullptr if Index is invalid
- L122 _public function_ `UDataprepContentProducer* GetProducer(int32 Index)`
- L128 _public function_ `bool IsProducerEnabled(int32 Index) const` — @return True if producer at Index-th position is enabled. Returns false if disabled or Index is invalid
- L134 _public function_ `bool IsProducerSuperseded(int32 Index) const` — @return True if producer at Index-th position is superseded by an enabled producer. Returns false if not superseded or superseder is disabled or Index is invalid
- L144 _public prototype_ `TArray< TWeakObjectPtr< UObject > > Produce( const FDataprepProducerContext& InContext );` — Run all producers of the Dataprep asset @param InContext		Context containing all the data required to properly run producers @param OutAssets		Array of assets filled up by the producers when run
- L150 _public function_ `DECLARE_EVENT_TwoParams(UDataprepAssetProducers, FOnDataprepProducersChanged, FDataprepAssetChangeType, int32 ) FOnDataprepProducersChanged& GetOnChanged()` — Allow an observer to be notified when when one of the producer has changed @return The delegate that will be broadcasted when one of the producer has changed
- L157 _protected member_ `TArray< FDataprepAssetProducer > AssetProducers;` — `UPROPERTY()` — List of producers referenced by the asset
- L161 _protected member_ `int32 Padding;` — `UPROPERTY()` — List of producers referenced by the asset
- L169 _protected prototype_ `void OnProducerChanged( const UDataprepContentProducer* InProducer );` — Answer notification that the consumer has changed @param InProducer Producer which has changed
- L176 _protected prototype_ `int32 AddAssetProducer( const FDataprepAssetProducer& AssetProducer );` — Append an FDataprepAssetProducer @param AssetProducer		FDataprepAssetProducer to append @return Index of the added FDataprepAssetProducer. INDEX_NONE if the addition failed
- L185 _private prototype_ `void ValidateProducerChanges( int32 Index, bool &bChangeAll );` — Helper to check superseding on all producers after changes made on one producer @param Index Index of the producer to validate against @param bChangeAll Set to true if changes on input producer implied changes on other producers
- L187 _private prototype_ `UDataprepContentProducer* AddProducer_Internal(UClass* ProducerClass, bool bIsAutomated);`
- L190 _private member_ `FOnDataprepProducersChanged OnChanged;` — Delegate broadcasted when one of the producers has changed

#### Free symbols / members of external scopes

- L150 _delegate_ `DECLARE_EVENT_TwoParams(UDataprepAssetProducers, FOnDataprepProducersChanged, FDataprepAssetChangeType, int32 ) FOnDataprepProducersChanged& GetOnChanged() { return OnChanged; } protected: #if WITH_EDITORONLY_DATA UPROPERTY() TArray< FDataprepAssetProducer > AssetProducers;` — Allow an observer to be notified when when one of the producer has changed @return The delegate that will be broadcasted when one of the producer has changed

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Public/DataprepAssetUserData.h` (Public)


#### class `UDataprepAssetUserData`  
`class UDataprepAssetUserData : public UAssetUserData`  
_L15-27_
- reflection: `UCLASS(BlueprintType, meta = (ScriptName = "DataprepUserData", DisplayName = "Dataprep User Data"))`
- inherits: `UAssetUserData`
- desc: A DataprepAssetUserData is used to mark assets or actors created through a Dataprep pipeline
- L22 _public member_ `TSoftObjectPtr<UDataprepEditingOperation> DataprepOperationPtr;` — `UPROPERTY()` — Dataprep operation which was used to generate the hosting object, if applicable
- L26 _public member_ `TSoftObjectPtr<UDataprepAssetInterface> DataprepAssetPtr;` — `UPROPERTY()` — Dataprep asset which was used to generate the hosting object

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Public/DataprepBindingCommandChange.h` (Public)


#### class `TDataprepBindingCommandChange`  
`template<class ObservedObjectType, typename DelatgateToBindType> class TDataprepBindingCommandChange final : public FCommandChange`  
_L9-43_
- inherits: `FCommandChange`
- L12 _public prototype_ `DECLARE_DELEGATE_RetVal(DelatgateToBindType&, FDelegateAccessor);`
- L13 _public prototype_ `DECLARE_DELEGATE_TwoParams(OnUndoRedoDelegateType, ObservedObjectType&, const FDelegateHandle&);`
- L15 _public typedef_ `using FDelegate = typename DelatgateToBindType::FDelegate;`
- L17 _public prototype_ `TDataprepBindingCommandChange(bool bInWasBindingAdded , ObservedObjectType& ObservedObject , FDelegate&& InBinding , FDelegateAccessor InDelegateAccessor , OnUndoRedoDelegateType&& InOnApply , OnUndoRedoDelegateType&& InOnRevert , const FDelegateHandle& InHandle );`
- L26 _public prototype_ `virtual void Apply(UObject* Object) override;`
- L28 _public prototype_ `virtual void Revert(UObject* Object) override;`
- L30 _public function_ `virtual FString ToString() const override`
- L36 _private member_ `bool bWasBindingAdded;`
- L37 _private member_ `TWeakObjectPtr<ObservedObjectType> ObservedObjectWeakPtr;`
- L38 _private member_ `FDelegate Binding;`
- L39 _private member_ `FDelegateAccessor DelegateAccessor;`
- L40 _private member_ `OnUndoRedoDelegateType OnApply;`
- L41 _private member_ `OnUndoRedoDelegateType OnRevert;`
- L42 _private member_ `FDelegateHandle Handle;`
- L46 _function_ `template<class ObservedObjectType, typename DelatgateToBindType> TDataprepBindingCommandChange<ObservedObjectType, DelatgateToBindType>::TDataprepBindingCommandChange( bool bInWasBindingAdded , ObservedObjectType& ObservedObject , FDelegate&& InBinding , FDelegateAccessor InDelegateAccessor , OnUndoRedoDelegateType&& InOnApply , OnUndoRedoDelegateType&& InOnRevert , const FDelegateHandle& InHandle ) : bWasBindingAdded( bInWasBindingAdded ) , ObservedObjectWeakPtr( &ObservedObject ) , Binding( MoveTemp( InBinding ) ) , DelegateAccessor( MoveTemp( InDelegateAccessor ) ) , OnApply( MoveTemp( InOnApply ) ) , OnRevert( MoveTemp( InOnRevert ) ) , Handle( InHandle )`
- L66 _function_ `template<class ObservedObjectType, typename DelatgateToBindType> void TDataprepBindingCommandChange<ObservedObjectType, DelatgateToBindType>::Apply(UObject* Object)`
- L85 _function_ `template<class ObservedObjectType, typename DelatgateToBindType> void TDataprepBindingCommandChange<ObservedObjectType, DelatgateToBindType>::Revert(UObject* Object)`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_DELEGATE_RetVal(DelatgateToBindType&, FDelegateAccessor);`
- L13 _delegate_ `DECLARE_DELEGATE_TwoParams(OnUndoRedoDelegateType, ObservedObjectType&, const FDelegateHandle&);`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Public/DataprepContentConsumer.h` (Public)


#### class `UDataprepConsumerUserData`  
`class UDataprepConsumerUserData : public UAssetUserData`  
_L20-36_
- reflection: `UCLASS(BlueprintType, meta = (ScriptName = "DataprepConsumerUserData", DisplayName = "Dataprep Consumer User Data"))`
- inherits: `UAssetUserData`
- desc: A UDataprepConsumerUserData is used to mark an asset or an actor to be respectively moved to a sub-folder or sub-level A DataprepContentConsumer is not obligated to honor this marker
- L25 _public function_ `void AddMarker(const FString& MarkerName, const FString& Value)`
- L30 _public prototype_ `const FString& GetMarker(const FString& MarkerName) const;`
- L35 _protected member_ `TMap<FString,FString> Markers;` — `UPROPERTY()` — Map for Dataprep entities to store data consumable or not by a consumer

#### struct `FDataprepConsumerContext`  
`struct FDataprepConsumerContext`  
_L38-99_
- L40 _public function_ `FDataprepConsumerContext() : bSilentMode(false)`
- L42 _public function_ `FDataprepConsumerContext& SetWorld( UWorld* InWorld )`
- L48 _public function_ `FDataprepConsumerContext& SetAssets( TArray< TWeakObjectPtr< UObject > >& InAssets )`
- L55 _public function_ `FDataprepConsumerContext& SetProgressReporter( const TSharedPtr< IDataprepProgressReporter >& InProgressReporter )`
- L61 _public function_ `FDataprepConsumerContext& SetLogger( const TSharedPtr< IDataprepLogger >& InLogger )`
- L67 _public function_ `FDataprepConsumerContext& SetTransientContentFolder( const FString& InTransientContentFolder )`
- L73 _public function_ `FDataprepConsumerContext& SetSilentMode( bool InSilentMode )`
- L80 _public member_ `TWeakObjectPtr< UWorld > WorldPtr;` — Hold onto the world the consumer will process
- L83 _public member_ `TArray< TWeakObjectPtr< UObject > > Assets;` — Array of assets the consumer will process
- L86 _public member_ `FString TransientContentFolder;` — Path to transient content folder where were created
- L89 _public member_ `TSharedPtr< IDataprepProgressReporter > ProgressReporterPtr;` — Hold onto the reporter that the consumer should use to report progress
- L92 _public member_ `TSharedPtr< IDataprepLogger > LoggerPtr;` — Hold onto the logger that the consumer should use to log messages
- L98 _public member_ `bool bSilentMode;` — Indicates the execution of the consumer must be silent This member is true when executed in headless mode

#### class `UDataprepContentConsumer`  
`class UDataprepContentConsumer : public UObject`  
_L107-286_
- reflection: `UCLASS(Abstract, config = EditorSettings, BlueprintType)`
- inherits: `UObject`
- desc: Abstract class providing the minimal services required for a DataprepConsumer Use the SDataprepConsumerWidget class to detail the properties of this class
- L113 _public prototype_ `UDataprepContentConsumer();`
- L116 _public prototype_ `virtual void PostEditUndo() override;` — UObject interface
- L127 _public prototype_ `bool Consume(const FDataprepConsumerContext& InContext);` — Successively calls Initialize, Run and Reset. @param InContext : The world the consumer must process on. This world must be assumed to be transient. @return true if the calls were successful, false otherwise @remark A copy of the incoming context is made by the consumer. The internal context is cleared by a call to Reset @remark If TargetContentFolder member is empty, it is set to the package path of the consumer @remark The consumer is expected to remove objects it has consumed from the world and/or assets' array
- L130 _public function_ `virtual const FText& GetLabel() const` — Name used by the UI to be displayed.
- L136 _public function_ `virtual const FText& GetDescription() const` — Text briefly describing what the consumer is doing with the world and assets it consumes. Note: This text will be used as a tooltip in the UI.
- L146 _public prototype_ `bool SetLevelName(const FString& InLevelName, FText& OutFailureReason);` — `UFUNCTION(BlueprintCallable, Category = DataprepConsumer)` — Sets the name of the level the consumer should move objects to if applicable. @param InLevelName : New name for the consumer's level. @param OutFailureReason : String explaining reason of failure to set the level name @return true if the name has been successfully set @remark if InLevelName is empty or equal to 'current' (case insensitive), no change is made
- L157 _public prototype_ `bool SetLevelNameAutomated(const FString& InLevelName, FText& OutFailureReason);` — `UFUNCTION(BlueprintCallable, Category = DataprepConsumer)` — Sets the name of the level the consumer should move objects to if applicable. This version won't pop any ui @param InLevelName : New name for the consumer's level. @param OutFailureReason : String explaining reason of failure to set the level name @return true if the name has been successfully set @remark if InLevelName is empty or equal to 'current' (case insensitive), no change is made
- L160 _public function_ `const FString& GetLevelName()` — `UFUNCTION(BlueprintCallable, Category = DataprepConsumer)`
- L171 _public prototype_ `bool SetTargetContentFolder(const FString& InTargetContentFolder, FText& OutFailureReason);` — `UFUNCTION(BlueprintCallable, Category = DataprepConsumer)` — Sets the path of the package the consumer should move assets to if applicable. Generally, this package path is substituted to the temporary path the assets are in @param InTargetContentFolder : Path of the package to save any assets in @param OutFailureReason : String explaining reason of failure to set the target content folder @return true if the assignment has been successful, false otherwise @remark if InPackagePath is empty the package path of the consumer is used
- L183 _public prototype_ `bool SetTargetContentFolderAutomated(const FString& InTargetContentFolder, FText& OutFailureReason);` — `UFUNCTION(BlueprintCallable, Category = DataprepConsumer)` — Sets the path of the package the consumer should move assets to if applicable. This version won't pop any ui Generally, this package path is substituted to the temporary path the assets are in @param InTargetContentFolder : Path of the package to save any assets in @param OutFailureReason : String explaining reason of failure to set the target content folder @return true if the assignment has been successful, false otherwise @remark if InPackagePath is empty the package path of the consumer is used
- L186 _public function_ `const FString& GetTargetContentFolder()` — `UFUNCTION(BlueprintCallable, Category = DataprepConsumer)`
- L191 _public prototype_ `FString GetTargetPackagePath() const;` — Returns a well-formed path to use when calling CreatePackage to create the target package.
- L197 _public function_ `DECLARE_EVENT(UDataprepContentConsumer, FDataprepConsumerChanged) FDataprepConsumerChanged& GetOnChanged()` — Allow an observer to be notified when one of the properties of the consumer changes @return The delegate that will be broadcasted when the consumer changed
- L204 _public member_ `static const FString RelativeOutput;` — Name of marker to be used by consumers to indicate specific output for assets or actors
- L216 _protected prototype_ `virtual bool SetLevelNameImplementation(const FString& InLevelName, FText& OutFailureReason, const bool bIsAutomated);` — Sets the name of the level the consumer should move objects to if applicable. @param InLevelName : New name for the consumer's level. @param OutFailureReason : String explaining reason of failure to set the level name @param bIsAutomated If it is true the function shouldn't require any feedback from the user @return true if the name has been successfully set @remark if InLevelName is empty or equal to 'current' (case insensitive), no change should be made
- L227 _protected prototype_ `virtual bool SetTargetContentFolderImplementation(const FString& InTargetContentFolder, FText& OutFailureReason, const bool bIsAutomated);` — Sets the path of the package the consumer should move assets to if applicable. Generally, this package path is substituted to the temporary path the assets are in @param InTargetContentFolder : Path of the package to save any assets in @param OutFailureReason : String explaining reason of failure to set the target content folder @param bIsAutomated If it is true the function shouldn't require any feedback from the user @return true if the assignment has been successful, false otherwise @remark if InPackagePath is empty the package path of the consumer is used
- L233 _protected function_ `virtual bool Initialize()` — Initialize the consumer to be ready for the next call to the Run method. @return true if the initialization was successful, false otherwise
- L236 _protected function_ `virtual bool Run()` — Requests the consumer to perform its operation.
- L242 _protected function_ `virtual void Reset()` — Clean up the objects used by the consumer. This call follows a call to Run. @remark The consumer must assume that the world and assets it has not consumed are about to be deleted.
- L245 _protected function_ `void LogInfo(const FText& Message)` — Start of helper functions to log messages and report progress
- L253 _protected function_ `void LogWarning(const FText& Message)`
- L261 _protected function_ `void LogError(const FText& Message)`
- L272 _protected member_ `FString TargetContentFolder;` — `UPROPERTY()`
- L275 _protected member_ `FString LevelName;` — `UPROPERTY()`
- L278 _protected member_ `FDataprepConsumerContext Context;` — Context which the consumer will run with
- L281 _protected member_ `FDataprepConsumerChanged OnChanged;` — Delegate to broadcast changes to the consumer
- L285 _private prototype_ `void AddDataprepAssetUserData();` — Add a UDataprepAssetUserData object to each asset's and root component's AssetUserData

#### Free symbols / members of external scopes

- L197 _delegate_ `DECLARE_EVENT(UDataprepContentConsumer, FDataprepConsumerChanged) FDataprepConsumerChanged& GetOnChanged() { return OnChanged; } static const FString RelativeOutput;` — Allow an observer to be notified when one of the properties of the consumer changes @return The delegate that will be broadcasted when the consumer changed

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Public/DataprepContentProducer.h` (Public)


#### struct `FDataprepProducerContext`  
`struct FDataprepProducerContext`  
_L18-61_
- desc: Structure to pass execution context to producer
- L20 _public function_ `FDataprepProducerContext()`
- L23 _public member_ `TWeakObjectPtr<UWorld> WorldPtr;` — World where the producer must add its actors
- L29 _public member_ `TWeakObjectPtr<UPackage> RootPackagePtr;` — Package of the content folder under which the producer must create assets to @remark: It is important to follow this rule since the Dataprep consumer assumes this is where all created assets are located
- L32 _public member_ `TSharedPtr< IDataprepProgressReporter > ProgressReporterPtr;` — Reporter the producer should use to report progress
- L35 _public member_ `TSharedPtr< IDataprepLogger > LoggerPtr;` — Logger the producer should use to log messages
- L38 _public function_ `FDataprepProducerContext& SetWorld( UWorld* InWorld )` — Helpers to set different members of the context
- L44 _public function_ `FDataprepProducerContext& SetRootPackage( UPackage* InRootPackage )`
- L50 _public function_ `FDataprepProducerContext& SetProgressReporter( const TSharedPtr< IDataprepProgressReporter >& InProgressReporter )`
- L56 _public function_ `FDataprepProducerContext& SetLogger( const TSharedPtr< IDataprepLogger >& InLogger )`

#### class `UDataprepContentProducer`  
`class UDataprepContentProducer : public UObject`  
_L67-209_
- reflection: `UCLASS(Abstract, BlueprintType)`
- inherits: `UObject`
- desc: Abstract class to derived from to be a producer in the Dataprep asset
- L82 _public prototype_ `bool Produce(const FDataprepProducerContext& InContext, TArray< TWeakObjectPtr< UObject > >& OutAssets);` — Successively calls the Initialize, Execute and Reset methods Additionally, to avoid naming collision, rename the newly created actors to include the producer's namespace. @param InContext		Context containing all the data required to perform a run. @param OutAssets		Array of assets created by the producer @param OutReason		Text containing description of failure if the method returns false @remark The world in the context should be assumed to be transient
- L85 _public function_ `virtual const FText& GetLabel() const` — Name used by the UI to be displayed.
- L91 _public function_ `virtual const FText& GetDescription() const` — Text briefly describing what the producer is doing to populate the world and assets. Note: This text will be used as a tooltip in the UI.
- L97 _public prototype_ `virtual FString GetNamespace() const;` — Text briefly describing what the producer is doing to populate the world and assets. Note: This text will be used as a tooltip in the UI.
- L104 _public function_ `DECLARE_EVENT_OneParam( UDataprepContentProducer, FDataprepProducerChanged, const UDataprepContentProducer* ) FDataprepProducerChanged& GetOnChanged()` — Allow an observer to be notified when one of the properties of the producer changes @return The delegate that will be broadcasted when the consumer changed @remark: Subclass of UDataprepContentProducer must use this mechanism to communicate changes to the owning Dataprep asset
- L116 _public function_ `virtual bool Supersede(const UDataprepContentProducer* OtherProducer) const` — A producer supersede another if its produces the same content or a super-set of the other's content @param OtherProducer : Other producer to compare to. @return true if the other producer produces the same content or a sub-set of it @remark Each sub-class must implement this method
- L122 _public function_ `virtual bool CanAddToProducersArray(bool bIsAutomated)` — Allow a producer to pop a ui after being created. @return false to cancel the insertion of the new producer
- L131 _public function_ `virtual bool IsActive()` — Allow a producer to pop a ui after being created. @return false to cancel the insertion of the new producer
- L137 _public function_ `bool IsCancelled()` — Returns true if the producer was cancelled during execution
- L146 _protected function_ `virtual bool Initialize()` — Initialize the producer to be ready for a call to the Execute method. @param OutReason		Text containing description of failure if the method returns false @return true if the initialization was successful, false otherwise
- L152 _protected function_ `virtual bool Execute(TArray< TWeakObjectPtr< UObject > >& OutAssets)` — Populates the world and fill up the array of assets. Reminder: All assets must be stored in the sub-package of the package provided in the context
- L158 _protected function_ `virtual void Reset()` — Clean up the objects used by the producer. This call follows a call to Execute. Note: The producer must assume that the world and assets it has produced are about to be deleted.
- L161 _protected function_ `void LogInfo(const FText& Message)` — Start of helper functions to log messages and report progress
- L169 _protected function_ `void LogWarning(const FText& Message)`
- L177 _protected function_ `void LogError(const FText& Message)`
- L186 _protected function_ `bool IsValid()`
- L190 _protected member_ `FDataprepProducerContext Context;` — Context which the producer will run with
- L193 _protected member_ `FDataprepProducerChanged OnChanged;` — Delegate to broadcast changes to the producer
- L196 _protected member_ `TSharedPtr<FFeedbackContext> FeedbackContext;` — The feedback context in use to check for user cancellation
- L199 _private function_ `void Terminate()`

#### Free symbols / members of external scopes

- L104 _delegate_ `DECLARE_EVENT_OneParam( UDataprepContentProducer, FDataprepProducerChanged, const UDataprepContentProducer* ) FDataprepProducerChanged& GetOnChanged() { return OnChanged; } virtual bool Supersede(const UDataprepContentProducer* OtherProducer) const { unimplemented(); return true; } virtual bool CanAddToProducersArray(bool bIsAutomated) { return true; } virtual bool IsActive() { return true; } bool IsCancelled() { return Context.ProgressReporterPtr.IsValid() ? Context.ProgressReporterPtr->IsWorkCancelled() : false; } protected: /** * Initialize the producer to be ready for a call to the Execute method. * @param OutReason Text containing description of failure if the method returns false` — Allow an observer to be notified when one of the properties of the producer changes @return The delegate that will be broadcasted when the consumer changed @remark: Subclass of UDataprepContentProducer must use this mechanism to communicate changes to the owning Dataprep asset

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Public/DataprepCoreUtils.h` (Public)


#### class `FDataprepCoreUtils`  
`class FDataprepCoreUtils`  
_L24-248_
- L32 _public prototype_ `static UDataprepAsset* GetDataprepAssetOfObject(UObject* Object);` — Return the Dataprep asset that own the object, if the object is part of a Dataprep asset @return nullptr if the object is not a part of a Dataprep asset
- L38 _public prototype_ `static UDataprepActionAsset* GetDataprepActionAssetOf(UObject* Object);` — Return the Dataprep action asset that own the object, if the object is part of a Dataprep action asset @return nullptr if the object is not a part of a Dataprep action asset
- L41 _public prototype_ `static void PurgeObjects(TArray<UObject*> Objects);` — Delete the objects and do the manipulation required to safely delete the assets
- L49 _public prototype_ `static bool IsAsset(UObject* Object);` — Checks if the input object is an asset even if transient or in a transient package @param Object	The object to check on @return	true if Object has the right flags or Object is of predefined classes @remark	This method is *solely* intended for objects manipulated by a Dataprep asset
- L59 _public function_ `static void RenameObject(UObject* Object, const TCHAR* NewName = nullptr, UObject* NewOuter = nullptr)` — Rename this object to a unique name, or change its outer. @param	Object		The object to rename @param	NewName		The new name of the object, if null then NewOuter should be set @param	NewOuter	New Outer this object will be placed within, if null it will use the current outer @remark	This method is *solely* intended for objects manipulated by a Dataprep asset
- L73 _public function_ `static void MoveToTransientPackage(UObject* Object)` — Move an object to the /Game/Transient package. @param	Object		The object to move @remark	This method is *solely* intended for objects manipulated by a Dataprep asset
- L87 _public prototype_ `static bool ExecuteDataprep(UDataprepAssetInterface* DataprepAssetInterface, const TSharedPtr<IDataprepLogger>& Logger, const TSharedPtr<IDataprepProgressReporter>& Reporter);` — Execute a Dataprep asset (import, execute and commit) @param DataprepAssetInterface The Dataprep asset to execute @param Logger A optional log manager for the Dataprep producers, operations and consumer @param Reporter A optional progress reporter for the Dataprep producers, operations and consumer
- L95 _public prototype_ `static bool IsClassValidForStepCreation(const TSubclassOf<UDataprepParameterizableObject>& StepType, UClass*& OutValidRootClass, FText& OutMessageIfInvalid);` — Check if class can be used to create a step for a Dataprep action @param StepType The class for the creation of the step @param OutValidRootClass The valid root class if found. @param OutMessageIfInvalid A message to report if the class is invalid.
- L100 _public prototype_ `static UClass* GetTypeOfActionStep(const UDataprepParameterizableObject* Object);` — Return the type of step that action step might be (Filter or Operation)
- L108 _public prototype_ `static void BuildAssets(const TArray< TWeakObjectPtr<UObject> >& Assets, const TSharedPtr<IDataprepProgressReporter>& ProgressReporterPtr );` — Helper function to build assets for use in the Dataprep pipeline @param	Assets					Array of weak pointer on the assets to be build @param	ProgressReporterPtr		Pointer to a IDataprepProgressReporter interface. This pointer can be invalid.
- L120 _public prototype_ `static bool RemoveSteps(UDataprepActionAsset* ActionAsset, const TArray<int32>& Indices, int32& ActionIndex, bool bDiscardParametrization = true );` — Helper function to remove a step from an action. This function will remove the action from the Dataprep asset owning it if this is the last step. @param	ActionAsset		Action asset to perform the operation on @param	Indices			Array of step's indices to remove. @param	ActionIndex		Set to INDEX_NONE if the action was not removed from its owning Dataprep asset. Valid index otherwise. @param	bDiscardParametrization If true, discrad parameterization associated with the action steps @return  Returns true if the removal was successful, false otherwise
- L131 _public function_ `static bool RemoveStep(UDataprepActionAsset* ActionAsset, int32 Index, int32& ActionIndex, bool bDiscardParametrization = true)` — Helper function to remove a step from an action. This function will remove the action from the Dataprep asset owning it if this is the last step. @param	ActionAsset		Action asset to perform the operation on @param	Index			Index of the step to remove. @param	bDiscardParametrization If true, discrad parameterization associated with the action step @param	ActionIndex		Set to INDEX_NONE if the action was not removed from its owning Dataprep asset. Valid index otherwise.
- L232 _public prototype_ `static void GetActorsFromWorld(const UWorld* World, TArray<UObject*>& OutActors);` — Collect on the valid actors in the input World @param World			World to parse @param OutActors		Actors present in the world
- L239 _public prototype_ `static void GetActorsFromWorld(const UWorld* World, TArray<AActor*>& OutActors);` — Collect on the valid actors in the input World @param World			World to parse @param OutActors		Actors present in the world
- L247 _public prototype_ `static void DeleteTemporaryFolders( const FString& BaseTemporaryPath );` — Delete the specified folder including all assets and sub-folders inside it. @param BaseTemporaryPath			Root folder to start from @remark This is called at the end of the execution of a Dataprep asset to remove all the temporary assets and folders created during its execution.

#### class `FDataprepCoreUtils::FDataprepLogger`  
`class FDataprepLogger : public IDataprepLogger`  
_L136-147_
- inherits: `IDataprepLogger`
- L139 _public function_ `virtual ~FDataprepLogger()`
- L142 _public prototype_ `virtual void LogInfo(const FText& InLogText, const UObject& InObject) override;`
- L143 _public prototype_ `virtual void LogWarning(const FText& InLogText, const UObject& InObject) override;`
- L144 _public prototype_ `virtual void LogError(const FText& InLogText, const UObject& InObject) override;`

#### class `FDataprepCoreUtils::FDataprepFeedbackContext`  
`class FDataprepFeedbackContext : public FFeedbackContextEditor`  
_L149-168_
- inherits: `FFeedbackContextEditor`
- L157 _public function_ `virtual bool ReceivedUserCancel() override` — We want to override this method in order to cache the cancel result and not clear it, so it can be checked multiple times with the correct result! (FFeedbackContextEditor::ReceivedUserCancel clears it)
- L167 _private member_ `bool bTaskWasCancelledCache = false;`

#### class `FDataprepCoreUtils::FDataprepProgressUIReporter`  
`class FDataprepProgressUIReporter : public IDataprepProgressReporter`  
_L170-200_
- inherits: `IDataprepProgressReporter`
- L173 _public function_ `FDataprepProgressUIReporter() : bIsCancelled(false)`
- L178 _public function_ `FDataprepProgressUIReporter( TSharedRef<FFeedbackContext> InFeedbackContext ) : FeedbackContext(InFeedbackContext) , bIsCancelled(false)`
- L184 _public function_ `virtual ~FDataprepProgressUIReporter()`
- L189 _public prototype_ `virtual void BeginWork( const FText& InTitle, float InAmountOfWork, bool bInterruptible = true ) override;`
- L190 _public prototype_ `virtual void EndWork() override;`
- L191 _public prototype_ `virtual void ReportProgress( float Progress, const FText& InMessage ) override;`
- L192 _public prototype_ `virtual bool IsWorkCancelled() override;`
- L193 _public prototype_ `virtual FFeedbackContext* GetFeedbackContext() const override;`
- L197 _private member_ `TArray< TSharedPtr< FScopedSlowTask > > ProgressTasks;`
- L198 _private member_ `TSharedPtr< FFeedbackContext > FeedbackContext;`
- L199 _private member_ `bool bIsCancelled;`

#### class `FDataprepCoreUtils::FDataprepProgressTextReporter`  
`class FDataprepProgressTextReporter : public IDataprepProgressReporter`  
_L202-225_
- inherits: `IDataprepProgressReporter`
- L205 _public function_ `FDataprepProgressTextReporter() : TaskDepth(0) , FeedbackContext( new FFeedbackContextAnsi )`
- L211 _public function_ `virtual ~FDataprepProgressTextReporter()`
- L216 _public prototype_ `virtual void BeginWork( const FText& InTitle, float InAmountOfWork, bool bInterruptible = true ) override;`
- L217 _public prototype_ `virtual void EndWork() override;`
- L218 _public prototype_ `virtual void ReportProgress( float Progress, const FText& InMessage ) override;`
- L219 _public prototype_ `virtual bool IsWorkCancelled() override;`
- L220 _public prototype_ `virtual FFeedbackContext* GetFeedbackContext() const override;`
- L223 _private member_ `int32 TaskDepth;`
- L224 _private member_ `TUniquePtr<FFeedbackContextAnsi> FeedbackContext;`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Public/DataprepFactories.h` (Public)


#### class `UDataprepAssetFactory`  
`class UDataprepAssetFactory : public UFactory`  
_L16-27_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UFactory`
- L21 _public prototype_ `UDataprepAssetFactory();`
- L24 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`
- L25 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

#### class `UDataprepAssetInstanceFactory`  
`class UDataprepAssetInstanceFactory : public UFactory`  
_L30-46_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UFactory`
- L35 _public prototype_ `UDataprepAssetInstanceFactory();`
- L41 _public member_ `TObjectPtr<class UDataprepAsset> Parent;` — `UPROPERTY(EditAnywhere, Category="Settings")` — The parent of the of the instance to create
- L44 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Public/DataprepOperation.h` (Public)


#### class `FDataprepOperationCategories`  
`class FDataprepOperationCategories`  
_L57-64_
- L60 _public member_ `static FText ActorOperation;`
- L61 _public member_ `static FText AssetOperation;`
- L62 _public member_ `static FText MeshOperation;`
- L63 _public member_ `static FText ObjectOperation;`

#### struct `FDataprepContext`  
`struct FDataprepContext`  
_L71-80_
- reflection: `USTRUCT(BlueprintType)`
- desc: Experimental struct. Todo add struct wide comment
- L79 _public member_ `TArray<TObjectPtr<UObject>> Objects;` — `UPROPERTY(BlueprintReadOnly, Category = "Dataprep")` — This is the objects on which an operation can operate

#### struct `FDataprepOperationContext`  
`struct FDataprepOperationContext`  
_L85-130_
- desc: Contains all data regarding the context in which an operation will be executed
- L88 _public member_ `TSharedPtr<struct FDataprepContext> Context;` — The context contains on which the operation should operate on.
- L93 _public member_ `FDataprepAssetsModified AssetsModifiedDelegate;` — Delegate to indicate an asset has been modified
- L99 _public member_ `FDataprepAddAsset AddAssetDelegate;` — Delegate to duplicate and add an asset to the Dataprep content Only effective if the operation is of class UDataprepEditingOperation
- L105 _public member_ `FDataprepCreateAsset CreateAssetDelegate;` — Delegate to create and add an asset to the Dataprep content Only effective if the operation is of class UDataprepEditingOperation
- L111 _public member_ `FDataprepCreateActor CreateActorDelegate;` — Delegate to create and add an actor to the Dataprep content Only effective if the operation is of class UDataprepEditingOperation
- L117 _public member_ `FDataprepRemoveObject RemoveObjectDelegate;` — Delegate to remove an object from the Dataprep's or the action's working set Only effective if the operation is of class UDataprepEditingOperation
- L123 _public member_ `FDataprepDeleteObjects DeleteObjectsDelegate;` — Delegate to remove an asset from the Dataprep content Only effective if the operation is of class UDataprepEditingOperation
- L126 _public member_ `TSharedPtr<class IDataprepLogger> DataprepLogger;` — Optional Logger to capture the log produced by an operation (via the functions LogInfo, LogWarning and LogError).
- L129 _public member_ `TSharedPtr<class IDataprepProgressReporter> DataprepProgressReporter;` — Optional Progress Reporter to capture any progress reported by an operation.

#### class `UDataprepOperation`  
`class UDataprepOperation : public UDataprepParameterizableObject`  
_L137-272_
- reflection: `UCLASS(Abstract, Blueprintable)`
- inherits: `UDataprepParameterizableObject`
- desc: Base class for all Dataprep operations Dataprep operations act on a set of input obejcts and can modify their properties: f.e. change materials, add metadata etc.
- L149 _public prototype_ `void Execute(const TArray<UObject*>& InObjects);` — `UFUNCTION(BlueprintCallable, Category = "Execution")` — Execute the operation @param InObjects The objects that the operation will operate on
- L159 _protected prototype_ `void OnExecution(const FDataprepContext& InContext);` — `UFUNCTION(BlueprintNativeEvent)` — This function is called when the operation is executed. If your defining your operation in Blueprint or Python this is the function to override. @param InContext The context contains the data that the operation should operate on.
- L166 _protected prototype_ `virtual void OnExecution_Implementation(const FDataprepContext& InContext);` — This function is the same has OnExcution, but it's the extension point for an operation defined in c++. It will be called on the operation execution. @param InContext The context contains the data that the operation should operate on
- L173 _protected prototype_ `void LogInfo(const FText& InLogText);` — `UFUNCTION(BlueprintCallable, Category = "Log", meta = (HideSelfPin = "true"))` — Add an info to the log @param InLogText The text to add to the log
- L180 _protected prototype_ `void LogWarning(const FText& InLogText);` — `UFUNCTION(BlueprintCallable, Category = "Log", meta = (HideSelfPin = "true"))` — Add a warning to the log @param InLogText The text to add to the log
- L187 _protected prototype_ `void LogError(const FText& InLogError);` — `UFUNCTION(BlueprintCallable, Category = "Log", meta = (HideSelfPin = "true"))` — Add Error to the log @param InLogText The text to add to the log
- L195 _protected prototype_ `void BeginWork( const FText& InDescription, float InAmountOfWork );` — `UFUNCTION(BlueprintCallable, Category = "Report", meta = (HideSelfPin = "true"))` — Indicates the beginning of a new work to report on @param InDescription		Text describing the work about to begin @param InAmountOfWork	Expected total amount of work
- L199 _protected prototype_ `void EndWork();` — `UFUNCTION(BlueprintCallable, Category = "Report", meta = (HideSelfPin = "true"))` — Indicates the end of the work
- L207 _protected prototype_ `void ReportProgress( float IncrementOfWork, const FText& InMessage );` — `UFUNCTION(BlueprintCallable, Category = "Report", meta = (HideSelfPin = "true"))` — Report foreseen progress on the current work @param IncrementOfWork	Amount of progress foreseen until the next call @param InMessage			Message to be displayed along side the reported progress
- L215 _protected prototype_ `void AssetsModified( TArray<UObject*> Assets );` — `UFUNCTION(BlueprintCallable, Category = "Dataprep | Operation")` — Indicates an array of assets has changed during the operation. It is important to use this function if the modifications on the assets impact their appearance @param Assets			Array of assets which have been modified
- L223 _protected prototype_ `TSharedPtr<FDataprepWorkReporter> CreateTask( const FText& InDescription, float InAmountOfWork, float InIncrementOfWork = 1.0f );` — Create a task to report progress during the execution of an operation @param InDescription		The description of the task about to be performed @param InAmountOfWork	Expected amount of work for the task @param InIncrementOfWork	Expected increment during the execution of the task
- L226 _protected prototype_ `bool IsCancelled();` — Returns true if the operation was canceled during execution
- L236 _public prototype_ `void ExecuteOperation(TSharedRef<FDataprepOperationContext>& InOperationContext);` — Prepare the operation for the execution and execute it. This allow the operation to report information such as log to the operation context @param InOperationContext This contains the data necessary for the setup of the operation and also the DataprepContext
- L242 _public prototype_ `FText GetDisplayOperationName() const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Display")` — Allows to change the name of the fetcher for the ui if needed.
- L248 _public prototype_ `FText GetTooltip() const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Display")` — Allows to change the tooltip of the fetcher for the ui if needed.
- L254 _public prototype_ `FText GetCategory() const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Display")` — Allows to change the tooltip of the fetcher for the ui if needed.
- L260 _public prototype_ `FText GetAdditionalKeyword() const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Display|Search")` — Allows to add more keywords for when a user is searching for the fetcher in the ui.
- L262 _public prototype_ `virtual FText GetDisplayOperationName_Implementation() const;`
- L263 _public prototype_ `virtual FText GetTooltip_Implementation() const;`
- L264 _public prototype_ `virtual FText GetCategory_Implementation() const;`
- L265 _public prototype_ `virtual FText GetAdditionalKeyword_Implementation() const;`
- L269 _private member_ `TSharedPtr<const FDataprepOperationContext> OperationContext;`

#### class `UDataprepEditingOperation`  
`class UDataprepEditingOperation : public UDataprepOperation`  
_L282-357_
- reflection: `UCLASS(Abstract, Blueprintable)`
- inherits: `UDataprepOperation`
- desc: Base class for all Dataprep editing operations Dataprep editing operations act on a set of input obejcts and can modify their properties, but also can create new objects or delete existing ones (like assets and actors), based on the information they receive as an input
- L294 _protected prototype_ `UObject* AddAsset(const UObject* Asset, const FString& AssetName );` — `UFUNCTION(BlueprintCallable, Category = "Dataprep | Editing Operation")` — DUplicate and add an asset to the Dataprep's and action's working set @param Asset			If not null, the asset will be duplicated @param AssetName		Name of the asset to create. Name collision will be checked and fixed before naming the asset @returns				The asset newly created
- L303 _protected prototype_ `UObject* CreateAsset(UClass* AssetClass, const FString& AssetName );` — `UFUNCTION(BlueprintCallable, Category = "Dataprep | Editing Operation")` — Create and add an asset to the Dataprep's and action's working set @param AssetClass	If Asset is null, an asset of the given class will be returned @param AssetName		Name of the asset to create. Name collision will be checked and fixed before naming the asset @returns				The asset newly created
- L312 _protected prototype_ `AActor* CreateActor( UClass* ActorClass, const FString& ActorName );` — `UFUNCTION(BlueprintCallable, Category = "Dataprep | Editing Operation")` — Add an actor to the Dataprep's transient world and action's working set @param ActorClass	Class of the actor to create @param ActorName		Name of the actor to create. Name collision will be performed before naming the asset @returns				The actor newly created
- L323 _protected prototype_ `void RemoveObject(UObject* Object, bool bLocalContext = false);` — `UFUNCTION(BlueprintCallable, Category = "Dataprep | Editing Operation")` — Remove an object from the Dataprep's and/or action's working set @param Object			Object to be removed from the working set @param bLocalContext		If set to true, the object is removed from the current working set. The object will not be accessible to any subsequent operation using the current context. If set to false, the object is removed from the Dataprep's working set. The object will not be accessible to any subsequent operation in the Dataprep's pipeline.
- L334 _protected prototype_ `void RemoveObjects(TArray<UObject*> Objects, bool bLocalContext = false);` — `UFUNCTION(BlueprintCallable, Category = "Dataprep | Editing Operation")` — Remove an array of objects from the Dataprep's and/or action's working set @param Objects			An array of objects to be removed from the working set @param bLocalContext		If set to true, the object is removed from the current working set. The object will not be accessible to any subsequent operation using the current context. If set to false, the object is removed from the Dataprep's working set. The object will not be accessible to any subsequent operation in the Dataprep's pipeline.
- L345 _protected prototype_ `void DeleteObject(UObject* Objects);` — `UFUNCTION(BlueprintCallable, Category = "Dataprep | Editing Operation")` — Delete an object from the Dataprep's working set @param Object		The object to be deleted @remark	The deletion of the object is deferred. However, if the object is not an asset, it is removed from the Dataprep's transient world. If the object is an asset, it is moved to the transient package, no action is taken to clean up any object referencing this asset. @remark	After execution, the object is not accessible by any subsequent operation in the Dataprep's pipeline.
- L356 _protected prototype_ `void DeleteObjects(TArray<UObject*> Objects);` — `UFUNCTION(BlueprintCallable, Category = "Dataprep | Editing Operation")` — Delete an array of objects from the Dataprep's and action's working set @param Objects		The array of objects to delete @remark	The deletion of the object is deferred. However, if the object is not an asset, it is removed from the Dataprep's transient world. If the object is an asset, it is moved to the transient package, no action is taken to clean up any object referencing this asset. @remark	After execution, the object is not accessible by any subsequent operation in the Dataprep's pipeline.

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(UObject* , FDataprepAddAsset, const UObject* , const TCHAR* ) DECLARE_DELEGATE_RetVal_TwoParams(UObject* , FDataprepCreateAsset, UClass* , const TCHAR* ) DECLARE_DELEGATE_RetVal_TwoParams(class AActor* , FDataprepCreateActor, UClass* , const TCHAR* ) DECLARE_DELEGATE_TwoParams(FDataprepRemoveObject, UObject* , bool ) DECLARE_DELEGATE_OneParam(FDataprepAssetsModified, TArray<UObject*> ) DECLARE_DELEGATE_OneParam(FDataprepDeleteObjects, TArray<UObject*> ) class FDataprepOperationCategories { public: static FText ActorOperation;` — Delegate used by a Dataprep operation to add a copy of an asset to the Dataprep's working set @return	A new asset which is either a duplicate of Asset if not null or of class AssetClass and name AssetName @remark	Returns nullptr if Asset and AssetClass is null @remark	If Asset is not null, it will not be added to the list of assets tracked by Dataprep. It can safely be deleted
- L29 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(UObject* , FDataprepCreateAsset, UClass* , const TCHAR* ) DECLARE_DELEGATE_RetVal_TwoParams(class AActor* , FDataprepCreateActor, UClass* , const TCHAR* ) DECLARE_DELEGATE_TwoParams(FDataprepRemoveObject, UObject* , bool ) DECLARE_DELEGATE_OneParam(FDataprepAssetsModified, TArray<UObject*> ) DECLARE_DELEGATE_OneParam(FDataprepDeleteObjects, TArray<UObject*> ) class FDataprepOperationCategories { public: static FText ActorOperation; static FText AssetOperation; static FText MeshOperation; static FText ObjectOperation; };` — Delegate used by a Dataprep operation to create and add an asset to the Dataprep's working set @return	A new asset which is either a duplicate of Asset if not null or of class AssetClass and name AssetName @remark	Returns nullptr if Asset and AssetClass is null @remark	If Asset is not null, it will not be added to the list of assets tracked by Dataprep. It can safely be deleted
- L35 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(class AActor* , FDataprepCreateActor, UClass* , const TCHAR* ) DECLARE_DELEGATE_TwoParams(FDataprepRemoveObject, UObject* , bool ) DECLARE_DELEGATE_OneParam(FDataprepAssetsModified, TArray<UObject*> ) DECLARE_DELEGATE_OneParam(FDataprepDeleteObjects, TArray<UObject*> ) class FDataprepOperationCategories { public: static FText ActorOperation; static FText AssetOperation; static FText MeshOperation; static FText ObjectOperation; };` — Delegate used by a Dataprep operation to add an actor to the Dataprep's working set @return	A new Actor of class ActorClass and name ActorName added to the Dataprep's transient world
- L43 _delegate_ `DECLARE_DELEGATE_TwoParams(FDataprepRemoveObject, UObject* , bool ) DECLARE_DELEGATE_OneParam(FDataprepAssetsModified, TArray<UObject*> ) DECLARE_DELEGATE_OneParam(FDataprepDeleteObjects, TArray<UObject*> ) class FDataprepOperationCategories { public: static FText ActorOperation; static FText AssetOperation; static FText MeshOperation; static FText ObjectOperation; };` — Delegate used by a Dataprep operation to remove an object If bLocalContext is true, the object is removed from the working set of the action owning the operation Otherwise, the object is removed from the Dataprep's working set @remark If the object is removed from the Dataprep's working set, the operation is therefore owning the object.
- L48 _delegate_ `DECLARE_DELEGATE_OneParam(FDataprepAssetsModified, TArray<UObject*> ) DECLARE_DELEGATE_OneParam(FDataprepDeleteObjects, TArray<UObject*> ) class FDataprepOperationCategories { public: static FText ActorOperation; static FText AssetOperation; static FText MeshOperation; static FText ObjectOperation; };` — Delegate used by a Dataprep operation to indicates an asset has been modified
- L55 _delegate_ `DECLARE_DELEGATE_OneParam(FDataprepDeleteObjects, TArray<UObject*> ) class FDataprepOperationCategories { public: static FText ActorOperation; static FText AssetOperation; static FText MeshOperation; static FText ObjectOperation; };` — Delegate used by a Dataprep operation to remove and delete an array of objects from the Dataprep's working set. After execution, Object will not be accessible by subsequent operations. The asset is NOT immediately deleted. This is a deferred deletion.

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Public/DataprepParameterizableObject.h` (Public)


#### class `UDataprepParameterizableObject`  
`class UDataprepParameterizableObject : public UObject`  
_L19-39_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: The base class of all the object that can interact with the dataprep parameterization This include all the parameterizable object and the parameterization object itself Also all the object that can be place in a dataprep action derive from it
- L24 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L30 _public prototype_ `DECLARE_EVENT_TwoParams(UDataprepParameterizableObject, FOnPostEdit, UDataprepParameterizableObject&, FPropertyChangedChainEvent&);` — Broadcast when a object has been post edited Note that it doesn't broadcast on the interactive events
- L31 _public function_ `FOnPostEdit& GetOnPostEdit()`
- L38 _private member_ `FOnPostEdit OnPostEdit;`

#### Free symbols / members of external scopes

- L30 _delegate_ `DECLARE_EVENT_TwoParams(UDataprepParameterizableObject, FOnPostEdit, UDataprepParameterizableObject&, FPropertyChangedChainEvent&);` — Broadcast when a object has been post edited Note that it doesn't broadcast on the interactive events

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Public/DataprepRecipe.h` (Public)


#### class `UDEPRECATED_DataprepRecipe`  
`class UDEPRECATED_DataprepRecipe : public UObject`  
_L14-53_
- reflection: `UCLASS(Deprecated, Blueprintable, BlueprintType, meta = (DisplayName = "DEPRECATED Data Preparation Recipe", DeprecationMessage = "No use of Blueprint with Dataprep."))`
- inherits: `UObject`
- L19 _public function_ `UDEPRECATED_DataprepRecipe()`
- L22 _public function_ `virtual bool IsEditorOnly() const override` — Begin UObject override
- L31 _public function_ `virtual TArray<AActor*> GetActors() const` — `UFUNCTION(BlueprintCallable, Category = "Dataprep | Query", meta = (HideSelfPin = "true"), meta=(DeprecatedFunction, DeprecationMessage="No use of Blueprint with Dataprep."))` — DEPRECATED Returns all actors contained in its attached world
- L41 _public function_ `virtual TArray<UObject*> GetAssets() const` — `UFUNCTION(BlueprintCallable, Category = "Dataprep | Query", meta = (DeprecatedFunction, DeprecationMessage="No use of Blueprint with Dataprep.", HideSelfPin = "true"))` — DEPRECATED Returns all valid assets contained in attached world
- L52 _public prototype_ `void TriggerPipelineTraversal();` — `UFUNCTION(BlueprintImplementableEvent, meta=(DeprecatedFunction, DeprecationMessage="No use of Blueprint with Dataprep."))` — DEPRECATED Function used to trigger the execution of the pipeline An event node associated to this function must be in the pipeline graph to run it.

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Public/IDataprepLogger.h` (Public)


#### class `IDataprepLogger`  
`class IDataprepLogger`  
_L11-36_
- desc: This is the interface that a logger must implement to work with the Dataprep core functionalities
- L19 _public prototype_ `virtual void LogInfo(const FText& InLogText, const UObject& InObject) = 0;` — Records an info produced by an operation @param InLogText The text logged @param InObject The object that produced the log
- L26 _public prototype_ `virtual void LogWarning(const FText& InLogText, const UObject& InObject) = 0;` — Records a warning produced by an operation @param InLogText The text logged @param InObject The object that produced the log
- L33 _public prototype_ `virtual void LogError(const FText& InLogText, const UObject& InObject) = 0;` — Records a error produced by an operation @param InLogText The text logged @param InObject The object that produced the log
- L35 _public prototype_ `virtual ~IDataprepLogger() = default;`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Public/IDataprepProgressReporter.h` (Public)


#### class `IDataprepProgressReporter`  
`class IDataprepProgressReporter`  
_L15-44_
- desc: This is the interface that a progress reporter must implement to work with FDataprepWorkReporter
- L18 _public prototype_ `virtual ~IDataprepProgressReporter() = default;`
- L25 _public prototype_ `virtual void BeginWork( const FText& InDescription, float InAmountOfWork, bool bInterruptible = true ) = 0;` — Indicates the beginning of a new work to report on @param InDescription		Text describing the work about to begin @param InAmountOfWork	Expected total amount of work
- L28 _public prototype_ `virtual void EndWork() = 0;` — Indicates the end of the work
- L35 _public prototype_ `virtual void ReportProgress( float IncrementOfWork, const FText& InMessage ) = 0;` — Report foreseen progress on the current work @param IncrementOfWork	Amount of progress foreseen until the next call @param InMessage			Message to be displayed along side the reported progress
- L38 _public prototype_ `virtual bool IsWorkCancelled() = 0;` — Returns true if the work has been cancelled
- L41 _public prototype_ `virtual FFeedbackContext* GetFeedbackContext() const = 0;` — Returns the feedback context used by this progress reporter

#### class `FDataprepWorkReporter`  
`class FDataprepWorkReporter`  
_L50-87_
- desc: Helper class to encapsulate the IDataprepProgressReporter interface
- L59 _public prototype_ `FDataprepWorkReporter( const TSharedPtr<IDataprepProgressReporter>& InReporter, const FText& InDescription, float InAmountOfWork, float InIncrementOfWork = 1.0f, bool bInterruptible = true );` — Report foreseen progress on the current task @param InDescription			Description of the task @param InAmountOfWork		Total amount of work for the task @param InIncrementOfWork		Amount of incremental work at each step within the task
- L61 _public prototype_ `~FDataprepWorkReporter();`
- L68 _public prototype_ `void ReportNextStep( const FText& InMessage, float InIncrementOfWork );` — Report foreseen incremental amount of work until next call @param InMessage				Message to be displayed along side the reported progress @param InIncrementOfWork		Amount of incremental work foreseen during the next step
- L74 _public function_ `void ReportNextStep( const FText& InMessage )` — Report foreseen default incremental amount of work until next call @param InMessage		Message to be displayed along side the reported progress
- L79 _public prototype_ `bool IsWorkCancelled() const;`
- L83 _private member_ `TSharedPtr<IDataprepProgressReporter> Reporter;` — Dataprep progress reporter associated with the task
- L86 _private member_ `float DefaultIncrementOfWork;` — Default incremental amount of work for each step constituting the task

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Public/Parameterization/DataprepParameterizationUtils.h` (Public)


#### enum `EParametrizationState`  
`enum class EParametrizationState : uint8`  
_L15-21_
- L17 _public enumerator_ `CanBeParameterized`
- L18 _public enumerator_ `IsParameterized`
- L19 _public enumerator_ `ParentIsParameterized`
- L20 _public enumerator_ `InvalidForParameterization`

#### struct `FDataprepParameterizationContext`  
`struct FDataprepParameterizationContext`  
_L26-30_
- desc: A small context that help when constructing the widgets for the parameterization
- L28 _public member_ `TArray<FDataprepPropertyLink> PropertyChain;`
- L29 _public member_ `EParametrizationState State = EParametrizationState::CanBeParameterized;`

#### struct `FDataprepPropertyLink`  
`struct FDataprepPropertyLink`  
_L34-60_
- reflection: `USTRUCT()`
- L38 _public function_ `FDataprepPropertyLink( FProperty* InCachedProperty, const FName& InPropertyName, int32 InContenerIndex ) : CachedProperty(InCachedProperty) , PropertyName( InPropertyName ) , ContainerIndex( InContenerIndex )`
- L44 _public prototype_ `FDataprepPropertyLink() = default;`
- L45 _public prototype_ `FDataprepPropertyLink(const FDataprepPropertyLink& Other) = default;`
- L46 _public prototype_ `FDataprepPropertyLink(FDataprepPropertyLink&& Other) = default;`
- L47 _public prototype_ `FDataprepPropertyLink& operator=(const FDataprepPropertyLink& Other) = default;`
- L48 _public prototype_ `FDataprepPropertyLink& operator=(FDataprepPropertyLink&& Other) = default;`
- L53 _public member_ `TFieldPath<FProperty> CachedProperty;` — `UPROPERTY()`
- L56 _public member_ `FName PropertyName;` — `UPROPERTY()`
- L59 _public member_ `int32 ContainerIndex = INDEX_NONE;` — `UPROPERTY()`

#### class `FDataprepParameterizationUtils`  
`class FDataprepParameterizationUtils`  
_L64-98_
- L72 _public prototype_ `static TArray<FDataprepPropertyLink> MakePropertyChain(TSharedPtr<IPropertyHandle> PropertyHandle);` — Take a property handle from the details view and generate the property for the dataprep parameterization @param PropertyHandle This is the handle from the details panel @return A non empty array if we were able make a compatible property chain
- L79 _public prototype_ `static TArray<FDataprepPropertyLink> MakePropertyChain(FPropertyChangedChainEvent& PropertyChangedEvent);` — Take a Property Changed Event and extract a dataprep property link chain from it @param PropertyChangedEvent The event @return A non empty array if we were able make a compatible property chain
- L84 _public prototype_ `static FDataprepParameterizationContext CreateContext(TSharedPtr<IPropertyHandle> PropertyHandle, const FDataprepParameterizationContext& ParameterisationContext);` — Take a already existing parameterization context and create a new version including the handle.
- L91 _public prototype_ `static UDataprepAsset* GetDataprepAssetForParameterization(UObject* Object);` — Grab the dataprep used for the parameterization of the object. @param Object The object from which the bindings would be created @return A valid pointer if the object was valid for the parameterization
- L97 _public prototype_ `static bool IsPropertyChainValid(const TArray<FDataprepPropertyLink>& PropertyChain);` — Check if a property is chain supported by the dataprep parameterization systems Note that the cached properties of the chain must not be null

#### Free symbols / members of external scopes

- L62 _prototype_ `uint32 GetTypeHash(const FDataprepPropertyLink& PropertyLink);`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Public/SelectionSystem/DataprepBoolFetcher.h` (Public)


#### class `UDataprepBoolFetcher`  
`class UDataprepBoolFetcher : public UDataprepFetcher`  
_L17-45_
- reflection: `UCLASS(Abstract, Blueprintable, Meta = (DisplayName = "Condition"))`
- inherits: `UDataprepFetcher`
- desc: The bool fetcher is a specialized type of fetcher for the booleans
- L31 _public prototype_ `bool Fetch(const UObject* Object, bool& bOutFetchSucceded) const;` — `UFUNCTION(BlueprintNativeEvent)` — This function is called when the fetcher is executed. If your defining your fetcher in Blueprint this is the function to override. @param Object The object from which the fetcher should try to retrieve the boolean @param bOutFetchSucceded If the fetcher managed to retrieve the boolean from the object this bool must be set to true @return The fetched bool
- L40 _public function_ `virtual bool Fetch_Implementation(const UObject* Object, bool& bOutFetchSucceded) const` — This function is the same has Fetch, but it's the extension point for an operation defined in c++. It will be called on the fetcher execution. @param Object The object from which the fetcher should try to retrieve the boolean @param bOutFetchSucceded If the fetcher managed to retrieve the boolean from the object this bool must be set to true @return The fetched bool

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Public/SelectionSystem/DataprepBoolFilter.h` (Public)


#### class `UDataprepBoolFilter`  
`class UDataprepBoolFilter : public UDataprepFilter`  
_L16-38_
- reflection: `UCLASS()`
- inherits: `UDataprepFilter`
- L21 _public prototype_ `bool Filter(const bool bResult) const;`
- L24 _public prototype_ `virtual TArray<UObject*> FilterObjects(const TArrayView<UObject* const>& Objects) const override;`
- L25 _public prototype_ `virtual void FilterAndGatherInfo(const TArrayView<UObject*>& InObjects, const TArrayView<FDataprepSelectionInfo>& OutFilterResults) const override;`
- L26 _public prototype_ `virtual void FilterAndStoreInArrayView(const TArrayView<UObject *>& InObjects, const TArrayView<bool>& OutFilterResults) const override;`
- L27 _public function_ `virtual bool IsThreadSafe() const override`
- L28 _public prototype_ `virtual FText GetFilterCategoryText() const override;`
- L29 _public prototype_ `virtual TSubclassOf<UDataprepFetcher> GetAcceptedFetcherClass() const override;`
- L30 _public prototype_ `virtual void SetFetcher(const TSubclassOf<UDataprepFetcher>& FetcherClass) override;`
- L33 _private prototype_ `virtual const UDataprepFetcher* GetFetcherImplementation() const override;`
- L37 _private member_ `TObjectPtr<UDataprepBoolFetcher> BoolFetcher;` — `UPROPERTY()`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Public/SelectionSystem/DataprepFetcher.h` (Public)


#### class `UDataprepFetcher`  
`class UDataprepFetcher : public UDataprepParameterizableObject`  
_L19-59_
- reflection: `UCLASS(Abstract)`
- inherits: `UDataprepParameterizableObject`
- desc: The Dataprep fetcher is a base class for Dataprep Selection system. The responsibility of fetcher is return a certain type of data for a object. (Look at DataprepStringFetcher for a example) This abstract base class exist currently for the discovery process, some compile time validation and to propagate UDataprepParameterizableObject
- L27 _public function_ `virtual bool IsThreadSafe() const` — Is this fetcher safe to use in a multi thread execution?
- L33 _public prototype_ `FText GetDisplayFetcherName() const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Display")` — Allows to change the name of the fetcher for the ui if needed.
- L39 _public prototype_ `FText GetNodeDisplayFetcherName() const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Display")` — The name displayed on node title.
- L45 _public prototype_ `FText GetTooltipText() const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Display")` — Allows to change the tooltip of the fetcher for the ui if needed.
- L51 _public prototype_ `FText GetAdditionalKeyword() const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Display|Search")` — Allows to add more keywords for when a user is searching for the fetcher in the ui.
- L55 _public prototype_ `virtual FText GetDisplayFetcherName_Implementation() const;` — The Native way to override the blueprint native events above
- L56 _public prototype_ `virtual FText GetNodeDisplayFetcherName_Implementation() const;`
- L57 _public prototype_ `virtual FText GetTooltipText_Implementation() const;`
- L58 _public prototype_ `virtual FText GetAdditionalKeyword_Implementation() const;`

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Public/SelectionSystem/DataprepFilter.h` (Public)


#### class `UDataprepFilter`  
`class UDataprepFilter : public UDataprepParameterizableObject`  
_L25-142_
- reflection: `UCLASS(Abstract, BlueprintType)`
- inherits: `UDataprepParameterizableObject`
- desc: The Dataprep Filter a base class for the Dataprep selection system It's main responsibility is to filter a array of object and to return the selected objects
- L32 _public prototype_ `virtual void PostCDOContruct() override;`
- L40 _public function_ `virtual TArray<UObject*> FilterObjects(const TArrayView<UObject* const>& Objects) const` — Take an array of objects and return the objects that pass the filter @param Objects The object to filter @return The object that passed the filtering
- L49 _public function_ `virtual void FilterAndGatherInfo(const TArrayView<UObject*>& InObjects, const TArrayView<FDataprepSelectionInfo>& OutFilterResults) const` — Take an array of object and output the result into the arrays @param InObjects The object to filter @param OutFilterResult Will put true at the same index of the object if it passed the filter @param OutFetchedSucces Will put true at the same index of the object if the fetcher fetched a value @param OutFetchedLabel Will put a display of information contextual to the filter/fetcher
- L56 _public function_ `virtual void FilterAndStoreInArrayView(const TArrayView<UObject*>& InObjects, const TArrayView<bool>& OutFilterResults) const` — Take an array of object and output the result into the result array @param InObjects The object to filter @param OutFilterResult Will put true at the same index of the object if it has passed the filter
- L61 _public function_ `virtual bool IsThreadSafe() const` — Is this filter safe to use in a multi thread execution?
- L68 _public function_ `virtual FText GetFilterCategoryText() const` — Return the selector category for this filter Imagine the category as the following: Select by|Your filter category| data fetched by the fetcher Here a full example: Select by|String with|Object Name
- L73 _public function_ `virtual TSubclassOf<UDataprepFetcher> GetAcceptedFetcherClass() const` — Return the type of fetcher associated with this filter
- L84 _public function_ `virtual void SetFetcher(const TSubclassOf<UDataprepFetcher>& FetcherClass)` — Set a new fetcher for this filter Note: This should only set a new fetcher if the fetcher is a subclass of the result of GetAcceptedFetcherClass and if it's not the same class as the current one
- L87 _public function_ `UDataprepFetcher* GetFetcher()` — `UFUNCTION(BlueprintCallable, Category="Filter")`
- L92 _public function_ `const UDataprepFetcher* GetFetcher() const`
- L101 _public function_ `void SetIsExcludingResult(bool bInIsExcludingResult)` — Allow the filter to exclude only the element that would normally pass the filter @param bIsExcludingResult Should the filter be a excluding filter
- L118 _public function_ `bool IsExcludingResult() const` — Is this filter a excluding filter.
- L126 _public prototype_ `static UClass* GetFilterTypeForFetcherType(UClass* FetcherClass);` — Return the type of filter to use for a fetcher
- L130 _private function_ `virtual const UDataprepFetcher* GetFetcherImplementation() const`
- L139 _private member_ `bool bIsExcludingResult = false;` — `UPROPERTY(EditAnywhere, Category="Filter")` — Is this filter an excluding filter (a filter that produces the inverse of its normal output)
- L141 _private member_ `static TMap<UClass*, UClass*> FetcherClassToFilterClass;`

#### class `UDataprepFilterNoFetcher`  
`class UDataprepFilterNoFetcher : public UDataprepParameterizableObject`  
_L151-251_
- reflection: `UCLASS(Abstract, BlueprintType)`
- inherits: `UDataprepParameterizableObject`
- desc: The Dataprep Filter a base class for the Dataprep selection system It's main responsibility is to filter a array of object and to return the selected objects This version of the filter does not support fetchers, but instead works (filters) directly on the input objects
- L162 _public function_ `virtual TArray<UObject*> FilterObjects(const TArrayView<UObject* const>& Objects) const` — Take an array of objects and return the objects that pass the filter @param Objects The object to filter @return The object that passed the filtering
- L171 _public function_ `virtual void FilterAndGatherInfo(const TArrayView<UObject*>& InObjects, const TArrayView<FDataprepSelectionInfo>& OutFilterResults) const` — Take an array of object and output the result into the arrays @param InObjects The object to filter @param OutFilterResult Will put true at the same index of the object if it passed the filter @param OutFetchedSucces Will put true at the same index of the object if the fetcher fetched a value @param OutFetchedLabel Will put a display of information contextual to the filter/fetcher
- L178 _public function_ `virtual void FilterAndStoreInArrayView(const TArrayView<UObject*>& InObjects, const TArrayView<bool>& OutFilterResults) const` — Take an array of object and output the result into the result array @param InObjects The object to filter @param OutFilterResult Will put true at the same index of the object if it has passed the filter
- L183 _public function_ `virtual bool IsThreadSafe() const` — Is this filter safe to use in a multi thread execution?
- L190 _public function_ `virtual FText GetFilterCategoryText() const` — Return the selector category for this filter Imagine the category as the following: Select by|Your filter category| data fetched by the fetcher Here a full example: Select by|String with|Object Name
- L196 _public prototype_ `FText GetDisplayFilterName() const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Display")` — Allows to change the name of the filter for the ui if needed.
- L202 _public prototype_ `FText GetNodeDisplayFilterName() const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Display")` — The name displayed on node title.
- L208 _public prototype_ `FText GetTooltipText() const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Display")` — Allows to change the tooltip of the filter for the ui if needed.
- L214 _public prototype_ `FText GetAdditionalKeyword() const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Display|Search")` — Allows to add more keywords for when a user is searching for the filter in the ui.
- L217 _public prototype_ `virtual FText GetDisplayFilterName_Implementation() const;` — The Native way to override the blueprint native events above
- L218 _public prototype_ `virtual FText GetTooltipText_Implementation() const;`
- L219 _public prototype_ `virtual FText GetAdditionalKeyword_Implementation() const;`
- L225 _public function_ `void SetIsExcludingResult(bool bInIsExcludingResult)` — Allow the filter to exclude only the element that would normally pass the filter @param bIsExcludingResult Should the filter be a excluding filter
- L242 _public function_ `bool IsExcludingResult() const` — Is this filter a excluding filter.
- L250 _private member_ `bool bIsExcludingResult = false;` — `UPROPERTY(EditAnywhere, Category="Filter")` — Is this filter an excluding filter (a filter that produces the inverse of its normal output)

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Public/SelectionSystem/DataprepFloatFetcher.h` (Public)


#### class `UDataprepFloatFetcher`  
`class UDataprepFloatFetcher : public UDataprepFetcher`  
_L17-44_
- reflection: `UCLASS(Abstract, Blueprintable, Meta = (DisplayName = "Float"))`
- inherits: `UDataprepFetcher`
- desc: The float fetcher is a specialized type of fetcher for the float
- L30 _public prototype_ `float Fetch(const UObject* Object, bool& bOutFetchSucceded) const;` — `UFUNCTION(BlueprintNativeEvent)` — This function is called when the fetcher is executed. If your defining your fetcher in Blueprint this is the function to override. @param Object The object from which the fetcher should try to retrieve a float @param bOutFetchSucceded If the fetcher managed to retrieve a float from the object this bool must be set to true @return The fetched float
- L39 _public function_ `virtual float Fetch_Implementation(const UObject* Object, bool& bOutFetchSucceded) const` — This function is the same has Fetch, but it's the extension point for an operation defined in c++. It will be called on the fetcher execution. @param Object The object from which the fetcher should try to retrieve a float @param bOutFetchSucceded If the fetcher managed to retrieve a float from the object this bool must be set to true @return The fetched float

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Public/SelectionSystem/DataprepFloatFilter.h` (Public)


#### enum `EDataprepFloatMatchType`  
`enum class EDataprepFloatMatchType : uint8`  
_L16-21_
- reflection: `UENUM()`
- L18 _public enumerator_ `LessThan`
- L19 _public enumerator_ `GreatherThan`
- L20 _public enumerator_ `IsNearlyEqual`

#### class `UDataprepFloatFilter`  
`class UDataprepFloatFilter : public UDataprepFilter`  
_L24-69_
- reflection: `UCLASS()`
- inherits: `UDataprepFilter`
- L29 _public prototype_ `bool Filter(float Float) const;`
- L32 _public prototype_ `virtual TArray<UObject*> FilterObjects(const TArrayView<UObject* const>& Objects) const override;`
- L33 _public prototype_ `virtual void FilterAndGatherInfo(const TArrayView<UObject*>& InObjects, const TArrayView<FDataprepSelectionInfo>& OutFilterResults) const override;`
- L34 _public prototype_ `virtual void FilterAndStoreInArrayView(const TArrayView<UObject*>& InObjects, const TArrayView<bool>& OutFilterResults) const override;`
- L35 _public function_ `virtual bool IsThreadSafe() const override`
- L36 _public prototype_ `virtual FText GetFilterCategoryText() const override;`
- L37 _public prototype_ `virtual TSubclassOf<UDataprepFetcher> GetAcceptedFetcherClass() const override;`
- L38 _public prototype_ `virtual void SetFetcher(const TSubclassOf<UDataprepFetcher>& FetcherClass) override;`
- L40 _private prototype_ `virtual const UDataprepFetcher* GetFetcherImplementation() const override;`
- L45 _public prototype_ `EDataprepFloatMatchType GetFloatMatchingCriteria() const;`
- L46 _public prototype_ `float GetEqualValue() const;`
- L47 _public prototype_ `float GetTolerance() const;`
- L49 _public prototype_ `void SetFloatMatchingCriteria(EDataprepFloatMatchType FloatMatchingCriteria);`
- L50 _public prototype_ `void SetEqualValue(float EqualValue);`
- L51 _public prototype_ `void SetTolerance(float Tolerance);`
- L56 _private member_ `TObjectPtr<UDataprepFloatFetcher> FloatFetcher;` — `UPROPERTY()` — The source of float selected by the user
- L60 _private member_ `EDataprepFloatMatchType FloatMatchingCriteria;` — `UPROPERTY(EditAnywhere, Category = "Filter")` — The matching criteria used when checking if a fetched value can pass the filter
- L64 _private member_ `float EqualValue;` — `UPROPERTY(EditAnywhere, Category = "Filter")` — The value to use for the comparison against the fetched value
- L68 _private member_ `float Tolerance = KINDA_SMALL_NUMBER;` — `UPROPERTY(EditAnywhere, Category = "Filter")` — The value used for the tolerance when doing a nearly equal

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Public/SelectionSystem/DataprepIntegerFetcher.h` (Public)


#### class `UDataprepIntegerFetcher`  
`class UDataprepIntegerFetcher : public UDataprepFetcher`  
_L17-44_
- reflection: `UCLASS(Abstract, Blueprintable, Meta = (DisplayName = "Integer"))`
- inherits: `UDataprepFetcher`
- desc: The integer fetcher is a specialized type of fetcher for the integer
- L30 _public prototype_ `int32 Fetch(const UObject* Object, bool& bOutFetchSucceded) const;` — `UFUNCTION(BlueprintNativeEvent)` — This function is called when the fetcher is executed. If your defining your fetcher in Blueprint this is the function to override. @param Object The object from which the fetcher should try to retrieve a float @param bOutFetchSucceded If the fetcher managed to retrieve a float from the object this bool must be set to true @return The fetched float
- L39 _public function_ `virtual int32 Fetch_Implementation(const UObject* Object, bool& bOutFetchSucceded) const` — This function is the same has Fetch, but it's the extension point for an operation defined in c++. It will be called on the fetcher execution. @param Object The object from which the fetcher should try to retrieve a float @param bOutFetchSucceded If the fetcher managed to retrieve a float from the object this bool must be set to true @return The fetched float

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Public/SelectionSystem/DataprepIntegerFilter.h` (Public)


#### enum `EDataprepIntegerMatchType`  
`enum class EDataprepIntegerMatchType : uint8`  
_L16-22_
- reflection: `UENUM()`
- L18 _public enumerator_ `LessThan`
- L19 _public enumerator_ `GreatherThan`
- L20 _public enumerator_ `IsEqual`
- L21 _public enumerator_ `InBetween`

#### class `UDataprepIntegerFilter`  
`class UDataprepIntegerFilter : public UDataprepFilter`  
_L25-78_
- reflection: `UCLASS()`
- inherits: `UDataprepFilter`
- L30 _public prototype_ `bool Filter(int Integer) const;`
- L33 _public prototype_ `virtual TArray<UObject*> FilterObjects(const TArrayView<UObject* const>& Objects) const override;`
- L34 _public prototype_ `virtual void FilterAndGatherInfo(const TArrayView<UObject*>& InObjects, const TArrayView<FDataprepSelectionInfo>& OutFilterResults) const override;`
- L35 _public prototype_ `virtual void FilterAndStoreInArrayView(const TArrayView<UObject*>& InObjects, const TArrayView<bool>& OutFilterResults) const override;`
- L36 _public function_ `virtual bool IsThreadSafe() const override`
- L37 _public prototype_ `virtual FText GetFilterCategoryText() const override;`
- L38 _public prototype_ `virtual TSubclassOf<UDataprepFetcher> GetAcceptedFetcherClass() const override;`
- L39 _public prototype_ `virtual void SetFetcher(const TSubclassOf<UDataprepFetcher>& FetcherClass) override;`
- L42 _private prototype_ `virtual const UDataprepFetcher* GetFetcherImplementation() const override;`
- L46 _public prototype_ `EDataprepIntegerMatchType GetIntegerMatchingCriteria() const;`
- L47 _public prototype_ `void SetIntegerMatchingCriteria(EDataprepIntegerMatchType InIntegerMatchingCriteria);`
- L49 _public prototype_ `int GetEqualValue() const;`
- L50 _public prototype_ `void SetEqualValue(int InValue);`
- L52 _public prototype_ `int GetFromValue() const;`
- L53 _public prototype_ `void SetFromValue(int InValue);`
- L55 _public prototype_ `int GetToValue() const;`
- L56 _public prototype_ `void SetToValue(int InValue);`
- L61 _private member_ `TObjectPtr<UDataprepIntegerFetcher> IntFetcher;` — `UPROPERTY()` — The source of int selected by the user
- L65 _private member_ `EDataprepIntegerMatchType IntegerMatchingCriteria;` — `UPROPERTY(EditAnywhere, Category = Filter)` — The matching criteria used when checking if a fetched value can pass the filter
- L69 _private member_ `int EqualValue;` — `UPROPERTY(EditAnywhere, Category = Filter)` — The value to use when doing the comparison against the fetched value
- L73 _private member_ `int FromValue;` — `UPROPERTY(EditAnywhere, Category = Filter)` — A value used for the in-between check
- L77 _private member_ `int ToValue;` — `UPROPERTY(EditAnywhere, Category = Filter)` — A value used for the in-between check

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Public/SelectionSystem/DataprepObjectSelectionFilter.h` (Public)


#### class `UDataprepObjectSelectionFilter`  
`class UDataprepObjectSelectionFilter : public UDataprepFilterNoFetcher`  
_L14-54_
- reflection: `UCLASS(BlueprintType, NotBlueprintable, HideCategories = (Filter), Meta = (Hidden, DisplayName="Selection", ToolTip = "Filter selected objects"))`
- inherits: `UDataprepFilterNoFetcher`
- L19 _public function_ `UDataprepObjectSelectionFilter() : NumAssets( 0 ), NumActors( 0 )`
- L22 _public prototype_ `virtual TArray<UObject*> FilterObjects(const TArrayView<UObject* const>& Objects) const override;`
- L23 _public prototype_ `virtual void FilterAndGatherInfo(const TArrayView<UObject*>& InObjects, const TArrayView<FDataprepSelectionInfo>& OutFilterResults) const override;`
- L24 _public prototype_ `virtual void FilterAndStoreInArrayView(const TArrayView<UObject*>& InObjects, const TArrayView<bool>& OutFilterResults) const override;`
- L25 _public function_ `virtual bool IsThreadSafe() const override`
- L28 _public prototype_ `void SetSelection( const FString& InTransientContentPath, const TArray<UObject*>& InSelectedObjects );`
- L30 _public function_ `const TArray< FString >& GetCachedNames() const`
- L32 _public function_ `int32 GetNumAssets() const`
- L33 _public function_ `int32 GetNumActors() const`
- L36 _private prototype_ `void RunFilter(const TArrayView<UObject* const>& InputObjects, TArray<UObject*>& FilteredObjects, const TArrayView<bool>* OutFilterResults) const;`
- L43 _private member_ `TArray< FString > SelectedObjectPaths;` — `UPROPERTY()` — Partial paths of objects. For assets, the transient part is cutoff (as it changes between runs), for actors, the path up to level outer is cutoff (in case level name changes between runs)
- L46 _private member_ `int32 NumAssets;` — `UPROPERTY()`
- L49 _private member_ `int32 NumActors;` — `UPROPERTY()`
- L53 _private member_ `TArray< FString > CachedNames;` — `UPROPERTY()` — Cache some of the names of selected objects, up to some limit, for preview purpose

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Public/SelectionSystem/DataprepSelectionSystemStructs.h` (Public)


#### struct `TIsFilterDataDisplayable`  
`template <class T> struct TIsFilterDataDisplayable`  
_L10-13_
- desc: Those template must be keep in sync with the variant. Those are the data types that the filter preview can display the data in the columns (scene preview and asset preview)

#### enum `TIsFilterDataDisplayable::(anonymous)`  
`enum`  
_L12-12_

#### struct `TIsFilterDataDisplayable`  
`template <> struct TIsFilterDataDisplayable<int32>`  
_L16-19_

#### enum `TIsFilterDataDisplayable::(anonymous)`  
`enum`  
_L18-18_

#### struct `TIsFilterDataDisplayable`  
`template <> struct TIsFilterDataDisplayable<float>`  
_L22-25_

#### enum `TIsFilterDataDisplayable::(anonymous)`  
`enum`  
_L24-24_

#### struct `TIsFilterDataDisplayable`  
`template <> struct TIsFilterDataDisplayable<FString>`  
_L28-31_

#### enum `TIsFilterDataDisplayable::(anonymous)`  
`enum`  
_L30-30_

#### struct `FDataprepSelectionInfo`  
`struct FDataprepSelectionInfo`  
_L45-50_
- desc: A struct to cache the result of a filter with some additional info
- L47 _public member_ `FFilterVariantData FetchedData;`
- L48 _public member_ `uint8 bHasPassFilter:1;`
- L49 _public member_ `uint8 bWasDataFetchedAndCached:1;`

#### Free symbols / members of external scopes

- L12 _enumerator_ `enum { Value = false };` (scope `TIsFilterDataDisplayable::__anona73877190103`)
- L18 _enumerator_ `enum { Value = true };` (scope `TIsFilterDataDisplayable::__anona73877190203`)
- L24 _enumerator_ `enum { Value = true };` (scope `TIsFilterDataDisplayable::__anona73877190303`)
- L30 _enumerator_ `enum { Value = true };` (scope `TIsFilterDataDisplayable::__anona73877190403`)
- L40 _typedef_ `using FFilterVariantData = TVariant< FEmptyVariantState, int32, float, FString >;` — This type is the variant used by the dataprep filter preview system to store a fetched data and then displaying it latter. if you update this, add the new type to the list above. Try to compile it. It should fail on a couple of functors. Update those and keep the functions explicit so that the compilation will fail when adding a type to the variant. This way the programmer will be force to acknowledge how those functors should behave on the new type

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Public/SelectionSystem/DataprepSelectionTransform.h` (Public)


#### class `UDataprepSelectionTransform`  
`class UDataprepSelectionTransform : public UDataprepParameterizableObject`  
_L16-82_
- reflection: `UCLASS(Abstract, Blueprintable)`
- inherits: `UDataprepParameterizableObject`
- L28 _public prototype_ `void Execute(const TArray<UObject*>& InObjects, TArray<UObject*>& OutObjects);` — `UFUNCTION(BlueprintCallable, Category = "Execution")` — Execute the transform @param InObjects Input objects the transform will operate on @param OutObjects Resulting objects after the transform was executed
- L39 _protected prototype_ `void OnExecution(const TArray<UObject*>& InObjects, TArray<UObject*>& OutObjects);` — `UFUNCTION(BlueprintNativeEvent)` — This function is called when the transform is executed. If your defining your transform in Blueprint or Python this is the function to override. @param InObjects Input objects the transform will operate on @param OutObjects Resulting objects after the transform was executed
- L47 _protected prototype_ `virtual void OnExecution_Implementation(const TArray<UObject*>& InObjects, TArray<UObject*>& OutObjects);` — This function is the same has OnExcution, but it's the extension point for an transform defined in c++. It will be called on the transform execution. @param InObjects Input objects the transform will operate on @param OutObjects Resulting objects after the transform was executed
- L54 _public prototype_ `FText GetDisplayTransformName() const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Display")` — Allows to change the name of the transform for the ui if needed.
- L60 _public prototype_ `FText GetTooltip() const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Display")` — Allows to change the tooltip of the transform for the ui if needed.
- L66 _public prototype_ `FText GetCategory() const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Display")` — Allows to change the category of the transform for the ui if needed.
- L72 _public prototype_ `FText GetAdditionalKeyword() const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Display|Search")` — Allows to add more keywords for when a user is searching for the fetcher in the ui.
- L74 _public prototype_ `virtual FText GetDisplayTransformName_Implementation() const;`
- L75 _public prototype_ `virtual FText GetTooltip_Implementation() const;`
- L76 _public prototype_ `virtual FText GetCategory_Implementation() const;`
- L77 _public prototype_ `virtual FText GetAdditionalKeyword_Implementation() const;`
- L81 _public member_ `bool bOutputCanIncludeInput = true;` — `UPROPERTY(EditAnywhere, Category = SelectionTransform)` — Specifies if input objects that have matching type can be added to the result

#### class `UDataprepRecursiveSelectionTransform`  
`class UDataprepRecursiveSelectionTransform : public UDataprepSelectionTransform`  
_L85-98_
- reflection: `UCLASS(Abstract, Blueprintable)`
- inherits: `UDataprepSelectionTransform`
- L90 _public prototype_ `virtual void OnExecution_Implementation(const TArray<UObject*>& InObjects, TArray<UObject*>& OutObjects) override;`
- L92 _public prototype_ `virtual void ApplySelectionTransform(const TArray<UObject*>& InObjects, TArray<UObject*>& OutObjects);`
- L97 _private member_ `int32 AllowRecursionLevels = -1;` — `UPROPERTY(EditAnywhere, Category = SelectionTransform)` — How many times is it allowed to apply another transform on the result

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Public/SelectionSystem/DataprepStringFetcher.h` (Public)


#### class `UDataprepStringFetcher`  
`class UDataprepStringFetcher : public UDataprepFetcher`  
_L17-45_
- reflection: `UCLASS(Abstract, Blueprintable, Meta = (DisplayName = "String"))`
- inherits: `UDataprepFetcher`
- desc: The string fetcher is a specialized type of fetcher for the string
- L31 _public prototype_ `FString Fetch(const UObject* Object, bool& bOutFetchSucceded) const;` — `UFUNCTION(BlueprintNativeEvent)` — This function is called when the fetcher is executed. If your defining your fetcher in Blueprint this is the function to override. @param Object The object from which the fetcher should try to retrieve the string @param bOutFetchSucceded If the fetcher managed to retrieve the string from the object this bool must be set to true @return The fetched string
- L40 _public function_ `virtual FString Fetch_Implementation(const UObject* Object, bool& bOutFetchSucceded) const` — This function is the same has Fetch, but it's the extension point for an operation defined in c++. It will be called on the fetcher execution. @param Object The object from which the fetcher should try to retrieve the string @param bOutFetchSucceded If the fetcher managed to retrieve the string from the object this bool must be set to true @return The fetched string

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Public/SelectionSystem/DataprepStringFilter.h` (Public)


#### enum `EDataprepStringMatchType`  
`enum class EDataprepStringMatchType : uint8`  
_L16-21_
- reflection: `UENUM()`
- L18 _public enumerator_ `Contains`
- L19 _public enumerator_ `MatchesWildcard`
- L20 _public enumerator_ `ExactMatch`

#### class `UDataprepStringFilterMatchingArray`  
`class UDataprepStringFilterMatchingArray : public UDataprepParameterizableObject`  
_L24-35_
- reflection: `UCLASS()`
- inherits: `UDataprepParameterizableObject`
- L30 _public member_ `TArray<FString> Strings;` — `UPROPERTY(EditAnywhere, Category = Filter)`
- L34 _public member_ `bool bExpanded = true;` — `UPROPERTY()` — UI state that needs to be serialized along with string values

#### class `UDataprepStringFilter`  
`class UDataprepStringFilter : public UDataprepFilter`  
_L38-87_
- reflection: `UCLASS()`
- inherits: `UDataprepFilter`
- L44 _public prototype_ `bool Filter(const FString& String) const;`
- L47 _public prototype_ `virtual TArray<UObject*> FilterObjects(const TArrayView<UObject* const>& Objects) const override;`
- L48 _public prototype_ `virtual void FilterAndGatherInfo(const TArrayView<UObject*>& InObjects, const TArrayView<FDataprepSelectionInfo>& OutFilterResults) const override;`
- L49 _public prototype_ `virtual void FilterAndStoreInArrayView(const TArrayView<UObject*>& InObjects, const TArrayView<bool>& OutFilterResults) const override;`
- L50 _public function_ `virtual bool IsThreadSafe() const override`
- L51 _public prototype_ `virtual FText GetFilterCategoryText() const override;`
- L52 _public prototype_ `virtual TSubclassOf<UDataprepFetcher> GetAcceptedFetcherClass() const override;`
- L53 _public prototype_ `virtual void SetFetcher(const TSubclassOf<UDataprepFetcher>& FetcherClass) override;`
- L56 _private prototype_ `virtual const UDataprepFetcher* GetFetcherImplementation() const override;`
- L60 _public prototype_ `EDataprepStringMatchType GetStringMatchingCriteria() const;`
- L61 _public prototype_ `FString GetUserString() const;`
- L62 _public prototype_ `bool GetMatchInArray() const;`
- L63 _public prototype_ `UDataprepStringFilterMatchingArray* GetStringArray();`
- L65 _public prototype_ `void SetStringMatchingCriteria(EDataprepStringMatchType StringMatchingCriteria);`
- L66 _public prototype_ `void SetUserString(FString UserString);`
- L67 _public prototype_ `void SetMatchInArray(bool bInSet);`
- L72 _private member_ `EDataprepStringMatchType StringMatchingCriteria;` — `UPROPERTY(EditAnywhere, Category = Filter)` — The matching criteria used when checking if a fetched value can pass the filter
- L76 _private member_ `FString UserString;` — `UPROPERTY(EditAnywhere, Category = Filter)` — The string used when doing the comparison
- L79 _private member_ `TObjectPtr<UDataprepStringFilterMatchingArray> UserStringArray;` — `UPROPERTY(EditAnywhere, Category = Filter)`
- L82 _private member_ `bool bMatchInArray;` — `UPROPERTY(EditAnywhere, Category = Filter)`
- L86 _private member_ `TObjectPtr<UDataprepStringFetcher> StringFetcher;` — `UPROPERTY()` — The source of string selected by the user

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Public/SelectionSystem/DataprepStringsArrayFetcher.h` (Public)


#### class `UDataprepStringsArrayFetcher`  
`class UDataprepStringsArrayFetcher : public UDataprepFetcher`  
_L14-42_
- reflection: `UCLASS(Abstract, Blueprintable, Meta = (DisplayName = "Strings Array"))`
- inherits: `UDataprepFetcher`
- L28 _public prototype_ `TArray<FString> Fetch(const UObject* Object, bool& bOutFetchSucceded) const;` — `UFUNCTION(BlueprintNativeEvent)` — This function is called when the fetcher is executed. If you are defining your fetcher in Blueprint this is the function to override. @param Object The object from which the fetcher should try to retrieve the string @param bOutFetchSucceded If the fetcher managed to retrieve the string from the object this bool must be set to true @return The fetched string
- L37 _public function_ `virtual TArray<FString> Fetch_Implementation(const UObject* Object, bool& bOutFetchSucceded) const` — This function is the same has Fetch, but it's the extension point for an operation defined in c++. It will be called on the fetcher execution. @param Object The object from which the fetcher should try to retrieve the string @param bOutFetchSucceded If the fetcher managed to retrieve the string from the object this bool must be set to true @return The fetched string

### `Plugins/Enterprise/DataprepEditor/Source/DataprepCore/Public/SelectionSystem/DataprepStringsArrayFilter.h` (Public)


#### class `UDataprepStringsArrayFilter`  
`class UDataprepStringsArrayFilter : public UDataprepFilter`  
_L12-61_
- reflection: `UCLASS()`
- inherits: `UDataprepFilter`
- L18 _public prototype_ `bool Filter(const TArray<FString>& StringArray) const;`
- L21 _public prototype_ `virtual TArray<UObject*> FilterObjects(const TArrayView<UObject* const>& Objects) const override;`
- L22 _public prototype_ `virtual void FilterAndGatherInfo(const TArrayView<UObject*>& InObjects, const TArrayView<FDataprepSelectionInfo>& OutFilterResults) const override;`
- L23 _public prototype_ `virtual void FilterAndStoreInArrayView(const TArrayView<UObject*>& InObjects, const TArrayView<bool>& OutFilterResults) const override;`
- L24 _public function_ `virtual bool IsThreadSafe() const override`
- L25 _public prototype_ `virtual FText GetFilterCategoryText() const override;`
- L26 _public prototype_ `virtual TSubclassOf<UDataprepFetcher> GetAcceptedFetcherClass() const override;`
- L27 _public prototype_ `virtual void SetFetcher(const TSubclassOf<UDataprepFetcher>& FetcherClass) override;`
- L30 _private prototype_ `virtual const UDataprepFetcher* GetFetcherImplementation() const override;`
- L34 _public prototype_ `EDataprepStringMatchType GetStringMatchingCriteria() const;`
- L35 _public prototype_ `FString GetUserString() const;`
- L36 _public prototype_ `bool GetMatchInArray() const;`
- L37 _public prototype_ `UDataprepStringFilterMatchingArray* GetStringArray();`
- L39 _public prototype_ `void SetStringMatchingCriteria(EDataprepStringMatchType StringMatchingCriteria);`
- L40 _public prototype_ `void SetUserString(FString UserString);`
- L41 _public prototype_ `void SetMatchInArray(bool bInSet);`
- L46 _private member_ `EDataprepStringMatchType StringMatchingCriteria;` — `UPROPERTY(EditAnywhere, Category = Filter)` — The matching criteria used when checking if a fetched value can pass the filter
- L50 _private member_ `FString UserString;` — `UPROPERTY(EditAnywhere, Category = Filter)` — The string used when doing the comparison
- L53 _private member_ `TObjectPtr<UDataprepStringFilterMatchingArray> UserStringArray;` — `UPROPERTY(EditAnywhere, Category = Filter)`
- L56 _private member_ `bool bMatchInArray;` — `UPROPERTY(EditAnywhere, Category = Filter)`
- L60 _private member_ `TObjectPtr<UDataprepStringsArrayFetcher> StringsArrayFetcher;` — `UPROPERTY()` — The source of string selected by the user
