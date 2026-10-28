# Plugins / VariantManagerContent

- module root: `Plugins/Enterprise/VariantManagerContent/Source/VariantManagerContent`
- headers: 17; symbols: 357
- symbol kinds: class=15, delegate=7, enum=3, enumerator=18, function=5, macro=23, member=70, namespace=1, prototype=210, struct=5
- PrivateDependencyModuleNames: RHI, RenderCore
- PublicDependencyModuleNames: BlueprintGraph, Core, CoreUObject, EditorFramework, Engine, UnrealEd

### `Plugins/Enterprise/VariantManagerContent/Source/VariantManagerContent/Private/VariantManagerContentLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogVariantContent, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVariantContent, Log, All);`

### `Plugins/Enterprise/VariantManagerContent/Source/VariantManagerContent/Private/VariantManagerObjectVersion.h` (Private)


#### struct `FVariantManagerObjectVersion`  
`struct FVariantManagerObjectVersion`  
_L8-35_
- desc: Custom serialization version for changes to variant manager objects
- L31 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L34 _private function_ `FVariantManagerObjectVersion()`

#### enum `FVariantManagerObjectVersion::Type`  
`enum Type`  
_L10-28_
- L13 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Roughly corresponds to 4.21
- L15 _public enumerator_ `CorrectSerializationOfFNameBytes`
- L17 _public enumerator_ `CategoryFlagsAndManualDisplayText`
- L19 _public enumerator_ `CorrectSerializationOfFStringBytes`
- L21 _public enumerator_ `SerializePropertiesAsNames`
- L23 _public enumerator_ `StoreDisplayOrder`
- L26 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L27 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

### `Plugins/Enterprise/VariantManagerContent/Source/VariantManagerContent/Public/FunctionCaller.h` (Public)


#### struct `FFunctionCaller`  
`struct FFunctionCaller`  
_L22-122_
- reflection: `USTRUCT()`
- L29 _public prototype_ `void PostSerialize(const FArchive& Ar);` — Called after this event has been serialized in order to cache the function pointer if necessary
- L41 _public member_ `FName FunctionName;` — `UPROPERTY()` — The function that should be called to invoke this event. Functions must have either: - no parameters - a single, pass-by-value object/interface parameter, with no return parameter - two parameters, one for bound object and another for arguments - four parameters: bound object, level variant set, variant set and variant - five parameters: bound object, level variant set, variant set, variant and arguments
- L47 _public member_ `TMap<FName, FString> FunctionArguments;` — `UPROPERTY()` — The function arguments to be passed when invoking this event (provided function supports arguments).
- L55 _public prototype_ `uint32 GetDisplayOrder() const;` — Get the order with which the VariantManager should display this in a property list. Lower values will be shown higher up
- L60 _public prototype_ `void SetDisplayOrder(uint32 InDisplayOrder);` — Set the order with which the VariantManager should display this in a property list. Lower values will be shown higher up
- L65 _public prototype_ `void CacheFunctionName();` — Cache the function name to call from the blueprint function entry node. Will only cache the function if it has a valid signature.
- L72 _public prototype_ `bool IsBoundToBlueprint() const;` — Check whether this event is bound to a valid blueprint entry node @return true if this event is bound to a function entry node with a valid signature, false otherwise.
- L80 _public prototype_ `static bool IsValidFunction(UK2Node_FunctionEntry* Node);` — Helper function to determine whether the specified function entry is valid for this event @param Node         The node to test @return true if the function entry node is compatible with a variant director specification, false otherwise
- L89 _public prototype_ `UK2Node_FunctionEntry* GetFunctionEntry() const;` — Retrieve the function entry node this event is bound to @note Events may be bound to invalid function entries if they have been changed since they were assigned. @see SetFunctionEntry, IsValidFunction @return The function entry node if still available, nullptr if it has been destroyed, or was never assigned.
- L96 _public prototype_ `void SetFunctionEntry(UK2Node_FunctionEntry* Entry);` — Set the function entry that this event should trigger @param Entry        The graph node to bind to
- L103 _public prototype_ `bool CanHaveArguments() const;` — Returns true if bound to a function that can take arguments @return true if bound and if function can take arguments.
- L111 _public prototype_ `static bool CanHaveArguments(UK2Node_FunctionEntry* ThisFunc);` — Returns true if bound to a function that can take arguments @param ThisFunc		The graph node to bind to @return true if bound and if function can take arguments.
- L116 _private member_ `TWeakObjectPtr<UObject> FunctionEntry;` — `UPROPERTY()` — Weak pointer to the function entry within the blueprint graph for this event. Stored as an editor-only UObject so UHT can parse it when building for non-editor.
- L119 _private member_ `uint32 DisplayOrder = 0;` — `UPROPERTY()`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FFunctionCaller> : TStructOpsTypeTraitsBase2<FFunctionCaller>`  
_L125-128_
- inherits: `TStructOpsTypeTraitsBase2<FFunctionCaller>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L127-127_

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API VARIANTMANAGERCONTENT_API`
- L9 _macro_ `#define TARGET_PIN_NAME TEXT("Target")`
- L10 _macro_ `#define LEVEL_VARIANT_SETS_PIN_NAME TEXT("Level Variant Sets")`
- L11 _macro_ `#define VARIANT_SET_PIN_NAME TEXT("Variant Set")`
- L12 _macro_ `#define VARIANT_PIN_NAME TEXT("Variant")`
- L13 _macro_ `#define ARGUMENTS_PIN_NAME TEXT("Arguments")`
- L127 _enumerator_ `enum { WithPostSerialize = true };` (scope `TStructOpsTypeTraits::__anonc2ac62a80103`)

### `Plugins/Enterprise/VariantManagerContent/Source/VariantManagerContent/Public/LevelVariantSets.h` (Public)


#### class `ULevelVariantSets`  
`class ULevelVariantSets : public UObject`  
_L17-113_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L24 _public prototype_ `virtual void BeginDestroy() override;` — UObject interface
- L25 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L28 _public prototype_ `void AddVariantSets(const TArray<UVariantSet*>& NewVariantSets, int32 Index = INDEX_NONE);`
- L29 _public prototype_ `int32 GetVariantSetIndex(UVariantSet* VarSet);`
- L30 _public prototype_ `const TArray<UVariantSet*>& GetVariantSets() const;`
- L31 _public prototype_ `void RemoveVariantSets(const TArray<UVariantSet*> InVariantSets);`
- L33 _public prototype_ `FString GetUniqueVariantSetName(const FString& Prefix);`
- L36 _public prototype_ `UObject* GetDirectorInstance(UObject* WorldContext);` — Return an existing or create a new director instance for the world that WorldContext is in
- L39 _public prototype_ `int32 GetNumVariantSets();` — `UFUNCTION(BlueprintPure, Category="LevelVariantSets")`
- L42 _public prototype_ `UVariantSet* GetVariantSet(int32 VariantSetIndex);` — `UFUNCTION(BlueprintPure, Category="LevelVariantSets")`
- L45 _public prototype_ `UVariantSet* GetVariantSetByName(FString VariantSetName);` — `UFUNCTION(BlueprintPure, Category="LevelVariantSets")`
- L48 _public prototype_ `int32 GetVariantSetIndex(FString VariantSetName) const;` — `UFUNCTION(BlueprintPure, Category="LevelVariantSets")`
- L51 _public prototype_ `void SetDirectorGeneratedBlueprint(UObject* InDirectorBlueprint);`
- L52 _public prototype_ `UObject* GetDirectorGeneratedBlueprint();`
- L53 _public prototype_ `UBlueprintGeneratedClass* GetDirectorGeneratedClass();`
- L54 _public prototype_ `void OnDirectorBlueprintRecompiled(UBlueprint* InBP);`
- L58 _public prototype_ `UWorld* GetWorldContext(int32& OutPIEInstanceID);` — Returns the current world, as well as its PIEInstanceID This will break when the engine starts supporting multiple, concurrent worlds
- L59 _public prototype_ `void ResetWorldContext();`
- L64 _private prototype_ `void OnPieEvent(bool bIsSimulating);` — Called on level transitions, invalidate our CurrentWorld pointer
- L65 _private prototype_ `void OnMapChange(uint32 MapChangeFlags);`
- L70 _private prototype_ `UWorld* ComputeCurrentWorld(int32& OutPIEInstanceID);` — Returns the first PIE world that we find or the Editor world Also outputs the PIEInstanceID of the WorldContext, for convenience, which will be -1 for editor worlds
- L74 _private prototype_ `void SubscribeToEditorDelegates();` — Sub/unsub to PIE/Map change events, which our CurrentWorld whenever something happens
- L75 _private prototype_ `void UnsubscribeToEditorDelegates();`
- L79 _private prototype_ `void SubscribeToDirectorCompiled();` — Sub/unsub to whenever our director is recompiled, which allows us to track when functions get deleted/renamed/updated
- L80 _private prototype_ `void UnsubscribeToDirectorCompiled();`
- L86 _private prototype_ `void HandleDirectorDestroyed(ULevelVariantSetsFunctionDirector* Director);` — Whenever a director is destroyed we remove it from our map, so next time we need it we know we have to recreate it
- L91 _private member_ `UWorld* CurrentWorld = nullptr;`
- L92 _private member_ `int32 CurrentPIEInstanceID = INDEX_NONE;`
- L96 _private member_ `TObjectPtr<UObject> DirectorBlueprint;` — `UPROPERTY()` — A pointer to the director blueprint that generates this levelvariantsets' DirectorClass
- L98 _private member_ `FDelegateHandle OnBlueprintCompiledHandle;`
- L99 _private member_ `FDelegateHandle EndPlayDelegateHandle;`
- L105 _private member_ `TObjectPtr<UBlueprintGeneratedClass> DirectorClass;` — `UPROPERTY()` — The class that is used to spawn this levelvariantsets' director instance. Director instances are allocated one per instance
- L108 _private member_ `TArray<TObjectPtr<UVariantSet>> VariantSets;` — `UPROPERTY()`
- L112 _private member_ `TMap<UWorld*, TWeakObjectPtr<UObject>> WorldToDirectorInstance;` — We keep one director instance per world to serve as world context for our function caller functions. Their lifetimes are guaranteed by spawned ALevelVariantSetsActors

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API VARIANTMANAGERCONTENT_API`

### `Plugins/Enterprise/VariantManagerContent/Source/VariantManagerContent/Public/LevelVariantSetsActor.h` (Public)


#### class `ALevelVariantSetsActor`  
`class ALevelVariantSetsActor : public AActor`  
_L17-50_
- reflection: `UCLASS(MinimalAPI, hideCategories=(Rendering, Physics, HLOD, Activation, Input, Actor, Cooking))`
- inherits: `AActor`
- L23 _public prototype_ `ALevelVariantSetsActor(const FObjectInitializer& Init);`
- L28 _public prototype_ `ULevelVariantSets* GetLevelVariantSets(bool bLoad = false);` — `UFUNCTION(BlueprintCallable, Category="LevelVariantSets", meta=(ToolTip="Returns the LevelVariantSets asset, optionally loading it if necessary"))` — Non-const so that it doesn't show as pure in blueprints, since it might trigger a load
- L31 _public prototype_ `void SetLevelVariantSets(ULevelVariantSets* InVariantSets);` — `UFUNCTION(BlueprintCallable, Category="LevelVariantSets")`
- L34 _public prototype_ `bool SwitchOnVariantByName(FString VariantSetName, FString VariantName);` — `UFUNCTION(BlueprintCallable, Category="LevelVariantSets")`
- L37 _public prototype_ `bool SwitchOnVariantByIndex(int32 VariantSetIndex, int32 VariantIndex);` — `UFUNCTION(BlueprintCallable, Category="LevelVariantSets")`
- L42 _public member_ `FSoftObjectPath LevelVariantSets;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="LevelVariantSets", meta=(AllowedClasses="/Script/VariantManagerContent.LevelVariantSets"))`
- L49 _private member_ `TMap<TObjectPtr<UBlueprintGeneratedClass>, TObjectPtr<ULevelVariantSetsFunctionDirector>> DirectorInstances;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API VARIANTMANAGERCONTENT_API`

### `Plugins/Enterprise/VariantManagerContent/Source/VariantManagerContent/Public/LevelVariantSetsFunctionDirector.h` (Public)


#### class `ULevelVariantSetsFunctionDirector`  
`class ULevelVariantSetsFunctionDirector : public UObject`  
_L14-38_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UObject`
- L19 _public prototype_ `~ULevelVariantSetsFunctionDirector() = default;`
- L21 _public function_ `virtual void BeginDestroy() override`
- L27 _public function_ `OnDirectorDestroyed& GetOnDestroy()`
- L32 _public prototype_ `virtual UWorld* GetWorld() const override;`
- L37 _public member_ `OnDirectorDestroyed OnDestroy;` — Called from our destructor Mainly used by levelvariantsets to keep track of when a director becomes invalid and we need to create a new one for that world

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API VARIANTMANAGERCONTENT_API`
- L11 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(OnDirectorDestroyed, ULevelVariantSetsFunctionDirector*);`
- L11 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(OnDirectorDestroyed, ULevelVariantSetsFunctionDirector*);`

### `Plugins/Enterprise/VariantManagerContent/Source/VariantManagerContent/Public/PropertyValue.h` (Public)


#### enum `EPropertyValueCategory`  
`enum class EPropertyValueCategory : uint8`  
_L21-32_
- reflection: `UENUM()`
- L23 _public enumerator_ `Undefined = 0`
- L24 _public enumerator_ `Generic = 1`
- L25 _public enumerator_ `RelativeLocation = 2`
- L26 _public enumerator_ `RelativeRotation = 4`
- L27 _public enumerator_ `RelativeScale3D = 8`
- L28 _public enumerator_ `Visibility = 16`
- L29 _public enumerator_ `Material = 32`
- L30 _public enumerator_ `Color = 64`
- L31 _public enumerator_ `Option = 128`

#### struct `FCapturedPropSegment`  
`struct FCapturedPropSegment`  
_L42-54_
- reflection: `USTRUCT()`
- desc: Describes one link in a full property path For array properties, a link might be the outer (e.g. AttachChildren, -1, None) while also it may be an inner (e.g. AttachChildren, 2, Cube) Doing this allows us to resolve components regardless of their order, which is important for handling component reordering and transient components (e.g. runtime billboard components, etc)
- L47 _public member_ `FString PropertyName;` — `UPROPERTY()`
- L50 _public member_ `int32 PropertyIndex = INDEX_NONE;` — `UPROPERTY()`
- L53 _public member_ `FString ComponentName;` — `UPROPERTY()`

#### class `UPropertyValue`  
`class UPropertyValue : public UObject`  
_L57-236_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L63 _public prototype_ `void Init(const TArray<FCapturedPropSegment>& InCapturedPropSegments, FFieldClass* InLeafPropertyClass, const FString& InFullDisplayString, const FName& InPropertySetterName, EPropertyValueCategory InCategory = EPropertyValueCategory::Generic);`
- L65 _public prototype_ `class UVariantObjectBinding* GetParent() const;`
- L71 _public prototype_ `uint32 GetPropertyPathHash();` — Combined hash of this property and its indices We don't use GetTypeHash for this because almost always we want to hash UPropertyValues by the pointer instead, for complete uniqueness even with the same propertypath This is mostly just used for grouping UPropertyValues together for editing multiple at once
- L74 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject Interface
- L75 _public prototype_ `virtual void BeginDestroy() override;`
- L79 _public prototype_ `virtual bool Resolve(UObject* OnObject = nullptr);` — Tries to resolve the property value on the passed object, or the parent binding's bound object if the argument is nullptr
- L80 _public prototype_ `bool HasValidResolve() const;`
- L81 _public prototype_ `void ClearLastResolve();`
- L83 _public prototype_ `void* GetPropertyParentContainerAddress() const;`
- L84 _public prototype_ `virtual UStruct* GetPropertyParentContainerClass() const;`
- L87 _public prototype_ `virtual TArray<uint8> GetDataFromResolvedObject() const;` — Fetches the value bytes for this property from the resolved object
- L90 _public prototype_ `virtual void RecordDataFromResolvedObject();` — Uses GetDataFromResolvedObject to update our recorded data
- L93 _public prototype_ `virtual void ApplyDataToResolvedObject();` — Applies our recorded data to the PropertyValuePtr for the resolved object
- L98 _public prototype_ `virtual FFieldClass* GetPropertyClass() const;` — Returns the type of FProperty (FObjectProperty, FFloatProperty, etc) If checking for Enums, prefer checking if GetEnumPropertyEnum() != nullptr, as it may be that we received a FNumericProperty that actually represents an enum, which wouldn't be reflected here
- L99 _public prototype_ `EPropertyValueCategory GetPropCategory() const;`
- L100 _public prototype_ `virtual UScriptStruct* GetStructPropertyStruct() const;`
- L101 _public prototype_ `virtual UClass* GetObjectPropertyObjectClass() const;`
- L102 _public prototype_ `UEnum* GetEnumPropertyEnum() const;`
- L103 _public prototype_ `virtual bool ContainsProperty(const FProperty* Prop) const;`
- L106 _public prototype_ `const TArray<FCapturedPropSegment>& GetCapturedPropSegments() const;` — Returns an array of link segments that together describe the full property path
- L109 _public prototype_ `TArray<FName> GetValidEnumsFromPropertyOverride();` — Utility functions for UEnumProperties
- L110 _public prototype_ `FString GetEnumDocumentationLink();`
- L112 _public prototype_ `int32 GetRecordedDataAsEnumIndex();` — Used RecordedData as an enum value and gets the corresponding index for our Enum
- L114 _public prototype_ `void SetRecordedDataFromEnumIndex(int32 Index);` — Sets our RecordedData with the value that matches Index, for our Enum
- L116 _public prototype_ `void SanitizeRecordedEnumData();` — Makes sure RecordedData data is a valid Enum index for our Enum (_MAX is not allowed)
- L117 _public prototype_ `bool IsNumericPropertySigned();`
- L118 _public prototype_ `bool IsNumericPropertyUnsigned();`
- L119 _public prototype_ `bool IsNumericPropertyFloatingPoint();`
- L122 _public prototype_ `const FName& GetNamePropertyName() const;` — Utility functions for string properties
- L123 _public prototype_ `const FString& GetStrPropertyString() const;`
- L124 _public prototype_ `const FText& GetTextPropertyText() const;`
- L126 _public prototype_ `FName GetPropertyName() const;`
- L128 _public prototype_ `FText GetPropertyTooltip() const;` — `UFUNCTION(BlueprintCallable, Category="PropertyValue")`
- L130 _public prototype_ `const FString& GetFullDisplayString() const;` — `UFUNCTION(BlueprintCallable, Category="PropertyValue")`
- L131 _public prototype_ `FString GetLeafDisplayString() const;`
- L132 _public prototype_ `FString GetBaseDisplayString() const;`
- L133 _public prototype_ `virtual int32 GetValueSizeInBytes() const;`
- L134 _public prototype_ `int32 GetPropertyOffsetInBytes() const;`
- L137 _public prototype_ `bool HasRecordedData() const;` — `UFUNCTION(BlueprintCallable, Category="PropertyValue")`
- L138 _public prototype_ `const TArray<uint8>& GetRecordedData();`
- L139 _public prototype_ `virtual void SetRecordedData(const uint8* NewDataBytes, int32 NumBytes, int32 Offset = 0);`
- L140 _public prototype_ `virtual const TArray<uint8>& GetDefaultValue();`
- L141 _public prototype_ `void ClearDefaultValue();`
- L144 _public prototype_ `virtual bool IsRecordedDataCurrent();` — Returns true if our recorded data would remain the same if we called RecordDataFromResolvedObject right now
- L146 _public prototype_ `FOnPropertyApplied& GetOnPropertyApplied();`
- L147 _public prototype_ `FOnPropertyRecorded& GetOnPropertyRecorded();`
- L153 _public prototype_ `uint32 GetDisplayOrder() const;` — Get the order with which the VariantManager should display this in a property list. Lower values will be shown higher up
- L158 _public prototype_ `void SetDisplayOrder(uint32 InDisplayOrder);` — Set the order with which the VariantManager should display this in a property list. Lower values will be shown higher up
- L163 _protected prototype_ `void SetRecordedDataInternal(const uint8* NewDataBytes, int32 NumBytes, int32 Offset = 0);`
- L165 _protected prototype_ `FProperty* GetProperty() const;`
- L169 _protected prototype_ `virtual void ApplyViaFunctionSetter(UObject* TargetObject);` — Applies the recorded data to the TargetObject via the PropertySetter function (e.g. SetIntensity instead of setting the Intensity UPROPERTY directly)
- L172 _protected prototype_ `bool ResolveUSCSNodeRecursive(const USCS_Node* Node, int32 SegmentIndex);` — Recursively navigate the component/USCS_Node hierarchy trying to resolve our property path
- L173 _protected prototype_ `bool ResolvePropertiesRecursive(UStruct* ContainerClass, void* ContainerAddress, int32 PropertyIndex);`
- L175 _protected member_ `FOnPropertyApplied OnPropertyApplied;`
- L176 _protected member_ `FOnPropertyRecorded OnPropertyRecorded;`
- L179 _protected prototype_ `void OnPIEEnded(const bool bIsSimulatingInEditor);`
- L183 _protected member_ `FProperty* LeafProperty;` — Temp data cached from last resolve
- L184 _protected member_ `UStruct* ParentContainerClass;`
- L185 _protected member_ `void* ParentContainerAddress;`
- L186 _protected member_ `UObject* ParentContainerObject;` — Leafmost UObject* in the property path. Required as ParentContainerAddress
- L187 _protected member_ `uint8* PropertyValuePtr;` — may be pointing at a C++ struct
- L188 _protected member_ `UFunction* PropertySetter;`
- L194 _protected member_ `TArray<TFieldPath<FProperty>> Properties_DEPRECATED;` — `UPROPERTY()` — Properties were previously stored like this. Use CapturedPropSegments from now on, which stores properties by name instead. It is much safer, as we can't guarantee these pointers will be valid if they point at other packages (will depend on package load order, etc).
- L196 _protected member_ `TArray<int32> PropertyIndices_DEPRECATED;` — `UPROPERTY()`
- L199 _protected member_ `TArray<FCapturedPropSegment> CapturedPropSegments;` — `UPROPERTY()`
- L202 _protected member_ `FString FullDisplayString;` — `UPROPERTY()`
- L205 _protected member_ `FName PropertySetterName;` — `UPROPERTY()`
- L208 _protected member_ `TMap<FString, FString> PropertySetterParameterDefaults;` — `UPROPERTY()`
- L211 _protected member_ `bool bHasRecordedData;` — `UPROPERTY()`
- L216 _protected member_ `TObjectPtr<UClass> LeafPropertyClass_DEPRECATED;` — `UPROPERTY()` — We use these mainly to know how to serialize/deserialize the values of properties that need special care (e.g. UObjectProperties, name properties, text properties, etc)
- L217 _protected member_ `FFieldClass* LeafPropertyClass;`
- L220 _protected member_ `TArray<uint8> ValueBytes;` — `UPROPERTY()`
- L223 _protected member_ `EPropertyValueCategory PropCategory;` — `UPROPERTY()`
- L225 _protected member_ `TArray<uint8> DefaultValue;`
- L227 _protected member_ `TSoftObjectPtr<UObject> TempObjPtr;`
- L228 _protected member_ `FName TempName;`
- L229 _protected member_ `FString TempStr;`
- L230 _protected member_ `FText TempText;`
- L234 _protected member_ `uint32 DisplayOrder;` — `UPROPERTY()`

#### class `UPropertyValueTransform`  
`class UPropertyValueTransform : public UPropertyValue`  
_L240-247_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UPropertyValue`
- desc: Deprecated: Only here for backwards compatibility with 4.21
- L245 _private prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject Interface

#### class `UPropertyValueVisibility`  
`class UPropertyValueVisibility : public UPropertyValue`  
_L251-258_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UPropertyValue`
- desc: Deprecated: Only here for backwards compatibility
- L256 _private prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject Interface

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API VARIANTMANAGERCONTENT_API`
- L10 _macro_ `#define PATH_DELIMITER TEXT(" / ")`
- L11 _macro_ `#define ATTACH_CHILDREN_NAME TEXT("Children")`
- L13 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnPropertyRecorded);`
- L13 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnPropertyRecorded);`
- L14 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnPropertyApplied);`
- L14 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnPropertyApplied);`

### `Plugins/Enterprise/VariantManagerContent/Source/VariantManagerContent/Public/PropertyValueColor.h` (Public)


#### class `UPropertyValueColor`  
`class UPropertyValueColor : public UPropertyValue`  
_L14-25_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UPropertyValue`
- desc: Keeps an FLinearColor interface by using the property setter/getter functions, even though the property itself is of FColor type
- L21 _public prototype_ `TArray<uint8> GetDataFromResolvedObject() const override;` — UPropertyValue interface
- L22 _public prototype_ `virtual UScriptStruct* GetStructPropertyStruct() const override;`
- L23 _public prototype_ `virtual int32 GetValueSizeInBytes() const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API VARIANTMANAGERCONTENT_API`

### `Plugins/Enterprise/VariantManagerContent/Source/VariantManagerContent/Public/PropertyValueMaterial.h` (Public)


#### class `UPropertyValueMaterial`  
`class UPropertyValueMaterial : public UPropertyValue`  
_L14-47_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UPropertyValue`
- L20 _public prototype_ `UMaterialInterface* GetMaterial();`
- L21 _public prototype_ `void SetMaterial(UMaterialInterface* Mat);`
- L28 _public prototype_ `virtual bool Resolve(UObject* OnObject = nullptr) override;` — Our leaf property will always be OverrideMaterials/OverrideMaterials[0] just for the type/size/class information. It will normally fail to resolve if the StaticMeshComponent is just using default materials though, so we have to intercept resolve calls and handle them in a specific way. This will also let us zero out the value ptr and other things that shouldn't be used by themselves
- L30 _public prototype_ `virtual bool ContainsProperty(const FProperty* Prop) const override;`
- L32 _public prototype_ `virtual UStruct* GetPropertyParentContainerClass() const override;`
- L34 _public prototype_ `virtual TArray<uint8> GetDataFromResolvedObject() const override;`
- L35 _public prototype_ `virtual void ApplyDataToResolvedObject() override;`
- L37 _public prototype_ `virtual FFieldClass* GetPropertyClass() const override;`
- L38 _public prototype_ `virtual UClass* GetObjectPropertyObjectClass() const override;`
- L40 _public prototype_ `virtual int32 GetValueSizeInBytes() const override;`
- L42 _public prototype_ `virtual const TArray<uint8>& GetDefaultValue();`
- L46 _private member_ `static FProperty* OverrideMaterialsProperty;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API VARIANTMANAGERCONTENT_API`

### `Plugins/Enterprise/VariantManagerContent/Source/VariantManagerContent/Public/PropertyValueOption.h` (Public)


#### class `UPropertyValueOption`  
`class UPropertyValueOption : public UPropertyValue`  
_L13-25_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UPropertyValue`
- desc: PropertyValue that can only be captured from ASwitchActors
- L19 _public prototype_ `virtual bool Resolve(UObject* OnObject = nullptr) override;` — UPropertyValue interface
- L20 _public prototype_ `virtual TArray<uint8> GetDataFromResolvedObject() const override;`
- L21 _public prototype_ `virtual void ApplyDataToResolvedObject() override;`
- L22 _public prototype_ `virtual const TArray<uint8>& GetDefaultValue() override;`
- L23 _public prototype_ `virtual int32 GetValueSizeInBytes() const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API VARIANTMANAGERCONTENT_API`

### `Plugins/Enterprise/VariantManagerContent/Source/VariantManagerContent/Public/PropertyValueSoftObject.h` (Public)


#### class `UPropertyValueSoftObject`  
`class UPropertyValueSoftObject : public UPropertyValue`  
_L20-38_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UPropertyValue`
- desc: Stores data from a USoftObjectProperty. It will store it's recorded data as a raw UObject*, and use the usual UPropertyValue facilities for serializing it as a Soft object ptr. This derived class handles converting to and from the property's underlying FSoftObjectPtr to our UObject*. We can't keep a FSoftObjectPtr ourselves, neither as a temp member nor as raw bytes, as it has internal heap-allocated data members like FName and FString.
- L26 _public prototype_ `virtual int32 GetValueSizeInBytes() const override;` — UPropertyValue interface
- L27 _public prototype_ `virtual FFieldClass* GetPropertyClass() const override;`
- L29 _public prototype_ `virtual void ApplyDataToResolvedObject() override;`
- L30 _public prototype_ `virtual TArray<uint8> GetDataFromResolvedObject() const;`
- L32 _public prototype_ `virtual void ApplyViaFunctionSetter(UObject* TargetObject) override;`
- L34 _public prototype_ `virtual bool IsRecordedDataCurrent() override;`
- L36 _public prototype_ `virtual void SetRecordedData(const uint8* NewDataBytes, int32 NumBytes, int32 Offset = 0) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API VARIANTMANAGERCONTENT_API`

### `Plugins/Enterprise/VariantManagerContent/Source/VariantManagerContent/Public/SwitchActor.h` (Public)


#### class `ASwitchActor`  
`class ASwitchActor : public AActor`  
_L21-55_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `AActor`
- desc: Switch Actor allows quickly toggling the visibility of its child actors so that only one is visible at a time. It can also be captured with the Variant Manager to expose this capability as a property capture
- L27 _public prototype_ `ASwitchActor(const FObjectInitializer& Init);`
- L30 _public prototype_ `TArray<AActor*> GetOptions() const;` — `UFUNCTION(BlueprintCallable, CallInEditor, Category="SwitchActor", meta=(ToolTip="Returns the child actors that are available options, in a fixed order that may differ from the one displayed in the world outliner"))`
- L33 _public prototype_ `int32 GetSelectedOption() const;` — `UFUNCTION(BlueprintCallable, CallInEditor, Category="SwitchActor", meta=(ToolTip="If we have exactly one child actor visible, it will return a pointer to it. Returns nullptr otherwise"))`
- L36 _public prototype_ `void SelectOption(int32 OptionIndex);` — `UFUNCTION(BlueprintCallable, CallInEditor, Category="SwitchActor", meta=(ToolTip="Select one of the available options by index"))`
- L38 _public prototype_ `FOnSwitchActorSwitch& GetOnSwitchDelegate();`
- L43 _private prototype_ `void SetVisibility(bool bVisible);` — Dedicated function to set our visibility so that we can restore our component hierarchy to the last-set option, in case e.g. we're overriden by a parent ASwitchActor
- L45 _private prototype_ `void PostLoad() override;`
- L47 _private member_ `FOnSwitchActorSwitch OnSwitchActorSwitch;`
- L51 _private member_ `TObjectPtr<class USceneComponent> SceneComponent;` — `UPROPERTY(Category = SwitchActor, VisibleAnywhere)` — Exposing our root component like this allows manual Mobility control on the details panel
- L54 _private member_ `int32 LastSelectedOption;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API VARIANTMANAGERCONTENT_API`
- L11 _macro_ `#define SWITCH_ACTOR_SELECTED_OPTION_NAME TEXT("Selected Option")`
- L13 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSwitchActorSwitch, int32 );`
- L13 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSwitchActorSwitch, int32 );`

### `Plugins/Enterprise/VariantManagerContent/Source/VariantManagerContent/Public/ThumbnailGenerator.h` (Public)


#### Free symbols / members of external scopes

- L7 _macro_ `#define VARIANT_MANAGER_THUMBNAIL_SIZE 256`
- L11 _namespace_ `namespace ThumbnailGenerator`
- L13 _prototype_ `UTexture2D* GenerateThumbnailFromTexture(UTexture2D* InImage);` (scope `ThumbnailGenerator`)
- L14 _prototype_ `UTexture2D* GenerateThumbnailFromFile(FString FilePath);` (scope `ThumbnailGenerator`)
- L15 _prototype_ `UTexture2D* GenerateThumbnailFromCamera(UObject* WorldContextObject, const FTransform& CameraTransform, float FOVDegrees = 50.0f, float MinZ = 50.0f, float Gamma = 2.2f);` (scope `ThumbnailGenerator`)
- L16 _prototype_ `UTexture2D* GenerateThumbnailFromEditorViewport();` (scope `ThumbnailGenerator`)
- L17 _prototype_ `UTexture2D* GenerateThumbnailFromObjectThumbnail(UObject* Object);` (scope `ThumbnailGenerator`)

### `Plugins/Enterprise/VariantManagerContent/Source/VariantManagerContent/Public/Variant.h` (Public)


#### struct `FVariantDependency`  
`struct FVariantDependency`  
_L19-31_
- reflection: `USTRUCT(BlueprintType)`
- L24 _public member_ `TSoftObjectPtr<UVariantSet> VariantSet;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dependency")`
- L27 _public member_ `TSoftObjectPtr<UVariant> Variant;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dependency")`
- L30 _public member_ `bool bEnabled = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dependency")`

#### class `UVariant`  
`class UVariant : public UObject`  
_L34-152_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L41 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnVariantChanged, UVariant*);`
- L44 _public member_ `static FOnVariantChanged OnThumbnailUpdated;` — Broadcast whenever we modify a variant thumbnail
- L47 _public member_ `static FOnVariantChanged OnDependenciesUpdated;` — Broadcast whenever we add/remove/modify a variant dependency
- L51 _public prototype_ `class UVariantSet* GetParent();` — `UFUNCTION(BlueprintPure, Category="Variant")`
- L54 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject Interface
- L58 _public prototype_ `void SetDisplayText(const FText& NewDisplayText);` — `UFUNCTION(BlueprintCallable, Category="Variant")`
- L61 _public prototype_ `FText GetDisplayText() const;` — `UFUNCTION(BlueprintPure, Category="Variant")`
- L64 _public prototype_ `void AddBindings(const TArray<UVariantObjectBinding*>& NewBindings, int32 Index = INDEX_NONE);` — In case of a duplicate binding these will destroy the older bindings
- L65 _public prototype_ `int32 GetBindingIndex(UVariantObjectBinding* Binding);`
- L66 _public prototype_ `const TArray<UVariantObjectBinding*>& GetBindings() const;`
- L67 _public prototype_ `void RemoveBindings(const TArray<UVariantObjectBinding*>& Bindings);`
- L70 _public prototype_ `int32 GetNumActors();` — `UFUNCTION(BlueprintPure, Category="Variant")`
- L73 _public prototype_ `AActor* GetActor(int32 ActorIndex);` — `UFUNCTION(BlueprintPure, Category="Variant")`
- L75 _public prototype_ `UVariantObjectBinding* GetBindingByName(const FString& ActorName);`
- L78 _public prototype_ `void SwitchOn();` — `UFUNCTION(BlueprintCallable, Category="Variant")`
- L82 _public prototype_ `bool IsActive();` — `UFUNCTION(BlueprintCallable, Category="Variant")` — Returns true if none of our properties are dirty
- L85 _public prototype_ `void SetThumbnailFromObject(UObject* ObjectThumbnail);` — `UFUNCTION(BlueprintCallable, Category="Variant|Thumbnail")`
- L89 _public prototype_ `void SetThumbnailFromTexture(UTexture2D* NewThumbnail);` — `UFUNCTION(BlueprintCallable, Category="Variant|Thumbnail")` — Sets the thumbnail to use for this variant. Can receive nullptr to clear it
- L92 _public prototype_ `void SetThumbnailFromFile(FString FilePath);` — `UFUNCTION(BlueprintCallable, Category="Variant|Thumbnail")`
- L95 _public prototype_ `void SetThumbnailFromCamera(UObject* WorldContextObject, const FTransform& CameraTransform, float FOVDegrees = 50.0f, float MinZ = 50.0f, float Gamma = 2.2f);` — `UFUNCTION(BlueprintCallable, Category="Variant|Thumbnail", meta=(WorldContext = "WorldContextObject"))`
- L99 _public prototype_ `void SetThumbnailFromEditorViewport();` — `UFUNCTION(BlueprintCallable, Category="Variant|Thumbnail", meta=(CallInEditor="true"))` — Sets the thumbnail from the active editor viewport. Doesn't do anything if the Editor is not available
- L103 _public prototype_ `UTexture2D* GetThumbnail();` — `UFUNCTION(BlueprintCallable, Category="Variant|Thumbnail")` — Gets the thumbnail currently used for this variant
- L107 _public prototype_ `TArray<UVariant*> GetDependents(ULevelVariantSets* LevelVariantSets, bool bOnlyEnabledDependencies);` — `UFUNCTION(BlueprintCallable, Category="Variant|Dependencies")` — Returns all the variants that have this variant as a dependency
- L110 _public prototype_ `bool IsValidDependency(const UVariant* Other) const;` — Returns if we can safely trigger Other as a dependency without the danger of cycles
- L113 _public prototype_ `int32 AddDependency(FVariantDependency& Dependency);` — `UFUNCTION(Category = "Variant|Dependencies")`
- L118 _public prototype_ `FVariantDependency& GetDependency(int32 Index);` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Variant|Dependencies", meta=(ToolTip="Get the dependency at index 'Index' by value. Will crash if index is invalid"))` — Returning by reference in blueprint doesn't seem to work if we want to later modify the FVariantDependency, so here we leave the return type without UPARAM(ref) so C++ code can use it as ref, while this function in blueprint returns by value
- L121 _public prototype_ `void SetDependency(int32 Index, FVariantDependency& Dependency);` — `UFUNCTION(Category = "Variant|Dependencies")`
- L124 _public prototype_ `void DeleteDependency(int32 Index);` — `UFUNCTION(Category = "Variant|Dependencies")`
- L127 _public prototype_ `int32 GetNumDependencies();` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Variant|Dependencies")`
- L130 _private prototype_ `void SetThumbnailInternal(UTexture2D* NewThumbnail);`
- L134 _private member_ `TArray<FVariantDependency> Dependencies;` — `UPROPERTY()`
- L138 _private member_ `FText DisplayText_DEPRECATED;` — `UPROPERTY()` — The display name used to be a property. Use the non-deprecated, non-property version from now on
- L140 _private member_ `FText DisplayText;`
- L143 _private member_ `TArray<TObjectPtr<UVariantObjectBinding>> ObjectBindings;` — `UPROPERTY()`
- L146 _private member_ `TObjectPtr<UTexture2D> Thumbnail;` — `UPROPERTY()`
- L150 _private member_ `bool bTriedRestoringOldThumbnail;` — Whether we already tried restoring a thumbnail from the actual package (backwards compatibility)

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API VARIANTMANAGERCONTENT_API`
- L41 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnVariantChanged, UVariant*);`

### `Plugins/Enterprise/VariantManagerContent/Source/VariantManagerContent/Public/VariantManagerContentModule.h` (Public)


#### class `IVariantManagerContentModule`  
`class IVariantManagerContentModule : public IModuleInterface`  
_L10-22_
- inherits: `IModuleInterface`
- L13 _public function_ `static inline IVariantManagerContentModule& Get()`
- L18 _public function_ `static inline bool IsAvailable()`

#### Free symbols / members of external scopes

- L7 _macro_ `#define VARIANTMANAGERCONTENTMODULE_MODULE_NAME TEXT("VariantManagerContent")`

### `Plugins/Enterprise/VariantManagerContent/Source/VariantManagerContent/Public/VariantObjectBinding.h` (Public)


#### class `UVariantObjectBinding`  
`class UVariantObjectBinding : public UObject`  
_L15-71_
- reflection: `UCLASS(MinimalAPI, DefaultToInstanced, meta=(ScriptName="UVariantActorBinding"))`
- inherits: `UObject`
- L20 _public prototype_ `void SetObject(UObject* InObject);`
- L22 _public prototype_ `class UVariant* GetParent();`
- L25 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject Interface
- L28 _public prototype_ `FText GetDisplayText() const;`
- L30 _public prototype_ `FString GetObjectPath() const;`
- L31 _public prototype_ `UObject* GetObject() const;`
- L33 _public prototype_ `void AddCapturedProperties(const TArray<UPropertyValue*>& Properties);`
- L34 _public prototype_ `const TArray<UPropertyValue*>& GetCapturedProperties() const;`
- L35 _public prototype_ `void RemoveCapturedProperties(const TArray<UPropertyValue*>& Properties);`
- L36 _public prototype_ `void SortCapturedProperties();`
- L38 _public prototype_ `void AddFunctionCallers(const TArray<FFunctionCaller>& InFunctionCallers);`
- L39 _public prototype_ `TArray<FFunctionCaller>& GetFunctionCallers();`
- L40 _public prototype_ `const TArray<FFunctionCaller>& GetFunctionCallers() const;`
- L41 _public prototype_ `void RemoveFunctionCallers(const TArray<FFunctionCaller*>& InFunctionCallers);`
- L42 _public prototype_ `void ExecuteTargetFunction(FName FunctionName);`
- L43 _public prototype_ `void ExecuteAllTargetFunctions();`
- L46 _public prototype_ `void UpdateFunctionCallerNames();`
- L56 _private member_ `mutable FString CachedActorLabel;` — `UPROPERTY()` — Whenever we resolve, we cache the actor label here so that if we can't resolve anymore we can better indicate which actor is missing, instead of just saying 'Unloaded binding'
- L59 _private member_ `mutable FSoftObjectPath ObjectPtr;` — `UPROPERTY()`
- L63 _private member_ `mutable TLazyObjectPtr<UObject> LazyObjectPtr_DEPRECATED;` — `UPROPERTY()`
- L67 _private member_ `TArray<TObjectPtr<UPropertyValue>> CapturedProperties;` — `UPROPERTY()`
- L70 _private member_ `TArray<FFunctionCaller> FunctionCallers;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API VARIANTMANAGERCONTENT_API`

### `Plugins/Enterprise/VariantManagerContent/Source/VariantManagerContent/Public/VariantSet.h` (Public)


#### class `UVariantSet`  
`class UVariantSet : public UObject`  
_L15-101_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L20 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnVariantSetChanged, UVariantSet*);`
- L21 _public member_ `static FOnVariantSetChanged OnThumbnailUpdated;`
- L24 _public prototype_ `class ULevelVariantSets* GetParent();` — `UFUNCTION(BlueprintPure, Category="VariantSet")`
- L27 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject Interface
- L32 _public prototype_ `bool IsExpanded() const;` — Sets whether this variant set is expanded or not when displayed in a variant manager
- L33 _public prototype_ `void SetExpanded(bool bInExpanded);`
- L36 _public prototype_ `void SetDisplayText(const FText& NewDisplayText);` — `UFUNCTION(BlueprintCallable, Category="VariantSet")`
- L39 _public prototype_ `FText GetDisplayText() const;` — `UFUNCTION(BlueprintPure, Category="VariantSet")`
- L41 _public prototype_ `FString GetUniqueVariantName(const FString& InPrefix) const;`
- L43 _public prototype_ `void AddVariants(const TArray<UVariant*>& NewVariants, int32 Index = INDEX_NONE);`
- L45 _public prototype_ `int32 GetVariantIndex(UVariant* Var) const;` — `UFUNCTION(BlueprintPure, Category="VariantSet")`
- L46 _public prototype_ `const TArray<UVariant*>& GetVariants() const;`
- L47 _public prototype_ `void RemoveVariants(const TArray<UVariant*>& InVariants);`
- L50 _public prototype_ `int32 GetNumVariants() const;` — `UFUNCTION(BlueprintPure, Category="VariantSet")`
- L53 _public prototype_ `UVariant* GetVariant(int32 VariantIndex);` — `UFUNCTION(BlueprintPure, Category="VariantSet")`
- L56 _public prototype_ `UVariant* GetVariantByName(FString VariantName);` — `UFUNCTION(BlueprintPure, Category="VariantSet")`
- L59 _public prototype_ `int32 GetVariantIndexByName(FString VariantName) const;` — `UFUNCTION(BlueprintPure, Category="VariantSet")`
- L63 _public prototype_ `void SetThumbnailFromObject(UObject* ObjectThumbnail);` — `UFUNCTION(BlueprintCallable, Category = "VariantSet|Thumbnail")` — Sets the thumbnail to use for this variant set. Can receive nullptr to clear it
- L66 _public prototype_ `void SetThumbnailFromTexture(UTexture2D* NewThumbnail);` — `UFUNCTION(BlueprintCallable, Category = "VariantSet|Thumbnail")`
- L69 _public prototype_ `void SetThumbnailFromFile(FString FilePath);` — `UFUNCTION(BlueprintCallable, Category = "VariantSet|Thumbnail")`
- L72 _public prototype_ `void SetThumbnailFromCamera(UObject* WorldContextObject, const FTransform& CameraTransform, float FOVDegrees = 50.0f, float MinZ = 50.0f, float Gamma = 2.2f);` — `UFUNCTION(BlueprintCallable, Category = "VariantSet|Thumbnail", meta = (WorldContext = "WorldContextObject"))`
- L76 _public prototype_ `void SetThumbnailFromEditorViewport();` — `UFUNCTION(BlueprintCallable, Category = "VariantSet|Thumbnail", meta = (CallInEditor = "true"))` — Sets the thumbnail from the active editor viewport. Doesn't do anything if the Editor is not available
- L80 _public prototype_ `UTexture2D* GetThumbnail();` — `UFUNCTION(BlueprintCallable, Category = "VariantSet|Thumbnail")` — Gets the thumbnail currently used for this variant set
- L83 _private prototype_ `void SetThumbnailInternal(UTexture2D* NewThumbnail);`
- L89 _private member_ `FText DisplayText_DEPRECATED;` — `UPROPERTY()` — The display name used to be a property. Use the non-deprecated, non-property version from now on
- L91 _private member_ `FText DisplayText;`
- L94 _private member_ `bool bExpanded;` — `UPROPERTY()`
- L97 _private member_ `TArray<TObjectPtr<UVariant>> Variants;` — `UPROPERTY()`
- L100 _private member_ `TObjectPtr<UTexture2D> Thumbnail;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API VARIANTMANAGERCONTENT_API`
- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnVariantSetChanged, UVariantSet*);`
