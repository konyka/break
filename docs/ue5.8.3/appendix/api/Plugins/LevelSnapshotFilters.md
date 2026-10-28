# Plugins / LevelSnapshotFilters

- module root: `Plugins/VirtualProduction/LevelSnapshots/Source/LevelShapshotFilters`
- headers: 21; symbols: 219
- symbol kinds: class=20, enum=8, enumerator=36, function=20, member=51, namespace=7, prototype=66, struct=7, typedef=4
- PrivateDependencyModuleNames: CoreUObject, Engine
- PublicDependencyModuleNames: Core

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelShapshotFilters/Public/Builtin/ActorChangedTransformFilter.h` (Public)


#### enum `ETransformReturnType::Type`  
`enum Type : int`  
_L12-18_
- L15 _public enumerator_ `IsValidWhenTransformChanged` — Return true if the snapshot and world actor have different transforms
- L17 _public enumerator_ `IsValidWhenTransformStayedSame` — Returns true of the snapshot and world actor have the same transform

#### class `UActorChangedTransformFilter`  
`class UActorChangedTransformFilter : public UActorSelectorFilter`  
_L26-53_
- reflection: `UCLASS(meta = (CommonSnapshotFilter))`
- inherits: `UActorSelectorFilter`
- desc: Allows an actor depending on whether the actors' transforms have changed. Use case: You want detect whether an actor has changed its transform.
- L32 _public prototype_ `virtual EFilterResult::Type IsActorValid(const FIsActorValidParams& Params) const override;`
- L39 _private member_ `TEnumAsByte<ETransformReturnType::Type> TransformCheckRule;` — `UPROPERTY(EditAnywhere, Category = "Config")` — Whether we allow actors that changed transform or that stayed at the same place.
- L43 _private member_ `bool bIgnoreLocation;` — `UPROPERTY(EditAnywhere, Category = "Config")` — If true, we do not compare the actors' locations.
- L47 _private member_ `bool bIgnoreRotation;` — `UPROPERTY(EditAnywhere, Category = "Config")` — If true, we do not compare the actors' rotations.
- L51 _private member_ `bool bIgnoreScale;` — `UPROPERTY(EditAnywhere, Category = "Config")` — If true, we do not compare the actors' scales.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ETransformReturnType`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelShapshotFilters/Public/Builtin/ActorDependentPropertyFilter.h` (Public)


#### enum `EDoNotCareHandling`  
`enum class EDoNotCareHandling`  
_L10-18_
- reflection: `UENUM()`
- L13 _public enumerator_ `UseIncludeFilter` — When IsActorValid returns Include, use RunOnIncludedActorFilter.
- L15 _public enumerator_ `UseExcludeFilter` — When IsActorValid returns Exclude, use RunOnExcludedActorFilter.
- L17 _public enumerator_ `UseDoNotCareFilter` — When IsActorValid returns DoNotCare, use RunOnDoNotCareActorFilter.

#### class `UActorDependentPropertyFilter`  
`class UActorDependentPropertyFilter : public ULevelSnapshotFilter`  
_L31-61_
- reflection: `UCLASS()`
- inherits: `ULevelSnapshotFilter`
- desc: Implements IsActorValid and IsPropertyValid as follows: - IsActorValid returns ActorFilter->IsActorValid - IsPropertyValid runs ActorFilter->IsActorValid. Depending on its results it runs - IncludePropertyFilter - ExcludePropertyFilter - DoNotCarePropertyFilter Use case: You want to allow certain properties when another filters would include the actor and allow different properties when excluded.
- L37 _public prototype_ `virtual EFilterResult::Type IsActorValid(const FIsActorValidParams& Params) const override;`
- L38 _public prototype_ `virtual EFilterResult::Type IsPropertyValid(const FIsPropertyValidParams& Params) const override;`
- L44 _public member_ `TObjectPtr<ULevelSnapshotFilter> ActorFilter;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Config")` — We run IsActorValid on this filter. IsPropertyValid uses one of the below filters depending on this filter.
- L48 _public member_ `TObjectPtr<ULevelSnapshotFilter> IncludePropertyFilter;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Config")` — Used by IsPropertyValid when ActorFilter->IsActorValid returns Include
- L52 _public member_ `TObjectPtr<ULevelSnapshotFilter> ExcludePropertyFilter;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Config")` — Used by IsPropertyValid when ActorFilter->IsActorValid returns Exclude
- L56 _public member_ `EDoNotCareHandling DoNotCareHandling;` — `UPROPERTY(EditAnywhere, Category = "Config")` — Determines what filter IsPropertyValid is supposed to use when IsActorValid returns DoNotCare.
- L60 _public member_ `TObjectPtr<ULevelSnapshotFilter> DoNotCarePropertyFilter;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Config")` — Used by IsPropertyValid when ActorFilter->IsActorValid returns DoNotCare and DoNotCareHandling == UseDoNotCareFilter.

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelShapshotFilters/Public/Builtin/ActorHasTagFilter.h` (Public)


#### enum `EActorToCheck::Type`  
`enum Type : int`  
_L12-20_
- L15 _public enumerator_ `WorldActor` — Checks only the tags of the world actor
- L17 _public enumerator_ `SnapshotActor` — Checks only the tags of the snapshot actor
- L19 _public enumerator_ `Both` — Checks the tags of both actors.

#### enum `ETagCheckingBehavior::Type`  
`enum Type : int`  
_L26-32_
- L29 _public enumerator_ `HasAllTags` — Actor must have all tags to pass
- L31 _public enumerator_ `HasAnyTag` — Actor must have at least one of the tags

#### class `UActorHasTagFilter`  
`class UActorHasTagFilter : public UActorSelectorFilter`  
_L37-60_
- reflection: `UCLASS(meta = (CommonSnapshotFilter))`
- inherits: `UActorSelectorFilter`
- desc: Allows an actor if it has all or any of the specified tags.
- L43 _public prototype_ `virtual EFilterResult::Type IsActorValid(const FIsActorValidParams& Params) const override;`
- L50 _private member_ `TEnumAsByte<ETagCheckingBehavior::Type> TagCheckingBehavior;` — `UPROPERTY(EditAnywhere, Category = "Config")` — How to match AllowedTags in each actor.
- L54 _private member_ `TSet<FName> AllowedTags;` — `UPROPERTY(EditAnywhere, Category = "Config")` — The tags to check the actor for.
- L58 _private member_ `TEnumAsByte<EActorToCheck::Type> ActorToCheck;` — `UPROPERTY(EditAnywhere, Category = "Config")` — Which of the actors we should check the tags on.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace EActorToCheck`
- L24 _namespace_ `namespace ETagCheckingBehavior`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelShapshotFilters/Public/Builtin/ActorInMapFilter.h` (Public)


#### class `UActorInMapFilter`  
`class UActorInMapFilter : public UActorSelectorFilter`  
_L12-33_
- reflection: `UCLASS(meta = (CommonSnapshotFilter))`
- inherits: `UActorSelectorFilter`
- desc: Allows an actor if it belongs to the specified map.
- L18 _public prototype_ `virtual EFilterResult::Type IsActorValid(const FIsActorValidParams& Params) const override;`
- L19 _public prototype_ `virtual EFilterResult::Type IsAddedActorValid(const FIsAddedActorValidParams& Params) const override;`
- L20 _public prototype_ `virtual EFilterResult::Type IsDeletedActorValid(const FIsDeletedActorValidParams& Params) const override;`
- L32 _private member_ `TArray<TSoftObjectPtr<UWorld>> AllowedLevels;` — `UPROPERTY(EditAnywhere, Category = "Config")` — Only actors belonging to this Level are considered. If since the snapshot was taken: 1. an actor was modified, it is only allowed if it was in one of these levels 2. an actor was added, it is only added back if it was in one of these levels

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelShapshotFilters/Public/Builtin/ActorSelector/ActorSelectorFilter.h` (Public)


#### class `UActorSelectorFilter`  
`class UActorSelectorFilter : public ULevelSnapshotBlueprintFilter`  
_L13-29_
- reflection: `UCLASS(Abstract)`
- inherits: `ULevelSnapshotBlueprintFilter`
- desc: Base class for filters that only implement IsActorValid
- L19 _public prototype_ `virtual EFilterResult::Type IsPropertyValid(const FIsPropertyValidParams& Params) const override;`
- L20 _public prototype_ `virtual EFilterResult::Type IsDeletedActorValid(const FIsDeletedActorValidParams& Params) const override;`
- L21 _public prototype_ `virtual EFilterResult::Type IsAddedActorValid(const FIsAddedActorValidParams& Params) const override;`
- L28 _public member_ `TEnumAsByte<EFilterResult::Type> DefaultResult = EFilterResult::DoNotCare;` — `UPROPERTY(EditAnywhere, Category = "Config")` — What to return for IsPropertyValid, IsDeletedActorValid, and IsAddedActorValid

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelShapshotFilters/Public/Builtin/BlueprintOnly/AndFilter.h` (Public)


#### class `UAndFilter`  
`class UAndFilter : public UParentFilter`  
_L10-25_
- reflection: `UCLASS(meta = (InternalSnapshotFilter))`
- inherits: `UParentFilter`
- L16 _public prototype_ `virtual EFilterResult::Type IsActorValid(const FIsActorValidParams& Params) const override;`
- L17 _public prototype_ `virtual EFilterResult::Type IsPropertyValid(const FIsPropertyValidParams& Params) const override;`
- L18 _public prototype_ `virtual EFilterResult::Type IsDeletedActorValid(const FIsDeletedActorValidParams& Params) const override;`
- L19 _public prototype_ `virtual EFilterResult::Type IsAddedActorValid(const FIsAddedActorValidParams& Params) const override;`
- L24 _private prototype_ `EFilterResult::Type EvaluateAndChain(TFunction<EFilterResult::Type(ULevelSnapshotFilter*)> EvaluateFilterCallback) const;`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelShapshotFilters/Public/Builtin/BlueprintOnly/NegationFilter.h` (Public)


#### class `UNegationFilter`  
`class UNegationFilter : public ULevelSnapshotFilter`  
_L18-58_
- reflection: `UCLASS(meta = (InternalSnapshotFilter))`
- inherits: `ULevelSnapshotFilter`
- desc: Returns the results of a child filter optionally negated. Negation rules: - Include negated becomes Exclude - Exclude negated becomes Include - DoNotCare negated becomes DoNotCare
- L28 _public prototype_ `ULevelSnapshotFilter* CreateChild(const TSubclassOf<ULevelSnapshotFilter>& ChildClass);` — `UFUNCTION(BlueprintCallable, Category = "Level Snapshots")` — Creates an instanced child. If you intend to save this filter, you should use this function instead of SetExternalChild;
- L35 _public prototype_ `void SetExternalChild(ULevelSnapshotFilter* NewChild);` — `UFUNCTION(BlueprintCallable, Category = "Level Snapshots")` — Creates an instanced child. If you intend to save this filter, you should use CreateChild;
- L38 _public prototype_ `ULevelSnapshotFilter* GetChild() const;` — `UFUNCTION(BlueprintPure, Category = "Level Snapshots")`
- L41 _public prototype_ `virtual EFilterResult::Type IsActorValid(const FIsActorValidParams& Params) const override;`
- L42 _public prototype_ `virtual EFilterResult::Type IsPropertyValid(const FIsPropertyValidParams& Params) const override;`
- L43 _public prototype_ `virtual EFilterResult::Type IsDeletedActorValid(const FIsDeletedActorValidParams& Params) const override;`
- L44 _public prototype_ `virtual EFilterResult::Type IsAddedActorValid(const FIsAddedActorValidParams& Params) const override;`
- L49 _public member_ `bool bShouldNegate = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Snapshots")`
- L54 _private member_ `TObjectPtr<ULevelSnapshotFilter> Child;` — `UPROPERTY(EditAnywhere, Category = "Level Snapshots")`
- L57 _private member_ `TObjectPtr<ULevelSnapshotFilter> InstancedChild;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Level Snapshots")`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelShapshotFilters/Public/Builtin/BlueprintOnly/OrFilter.h` (Public)


#### class `UOrFilter`  
`class UOrFilter : public UParentFilter`  
_L10-25_
- reflection: `UCLASS(meta = (InternalSnapshotFilter))`
- inherits: `UParentFilter`
- L16 _public prototype_ `virtual EFilterResult::Type IsActorValid(const FIsActorValidParams& Params) const override;`
- L17 _public prototype_ `virtual EFilterResult::Type IsPropertyValid(const FIsPropertyValidParams& Params) const override;`
- L18 _public prototype_ `virtual EFilterResult::Type IsDeletedActorValid(const FIsDeletedActorValidParams& Params) const override;`
- L19 _public prototype_ `virtual EFilterResult::Type IsAddedActorValid(const FIsAddedActorValidParams& Params) const override;`
- L24 _private prototype_ `EFilterResult::Type EvaluateOrChain(TFunction<EFilterResult::Type(ULevelSnapshotFilter*)> EvaluateFilterCallback) const;`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelShapshotFilters/Public/Builtin/BlueprintOnly/ParentFilter.h` (Public)


#### class `UParentFilter`  
`class UParentFilter : public ULevelSnapshotFilter`  
_L11-56_
- reflection: `UCLASS(meta = (InternalSnapshotFilter))`
- inherits: `ULevelSnapshotFilter`
- L22 _public prototype_ `void AddChild(ULevelSnapshotFilter* Filter);` — `UFUNCTION(BlueprintCallable, Category = "Level Snapshots")` — Adds a child you already created to this filter If you intend to save your filter, add children using CreateChild.
- L26 _public prototype_ `bool RemovedChild(ULevelSnapshotFilter* Filter);` — `UFUNCTION(BlueprintCallable, Category = "Level Snapshots")` — Removes a child from this filter
- L33 _public prototype_ `ULevelSnapshotFilter* CreateChild(const TSubclassOf<ULevelSnapshotFilter>& Class);` — `UFUNCTION(BlueprintCallable, Category = "Level Snapshots")` — Creates a child and adds it to this filter. If you intend to save your filter, add children using this function.
- L37 _public prototype_ `TArray<ULevelSnapshotFilter*> GetChildren() const;` — `UFUNCTION(BlueprintPure, Category = "Level Snapshots")` — Gets the children in this filter
- L47 _protected prototype_ `void ForEachChild(TFunction<EShouldBreak(ULevelSnapshotFilter* Child)> Callback) const;`
- L52 _private member_ `TArray<TObjectPtr<ULevelSnapshotFilter>> Children;` — `UPROPERTY(EditAnywhere, Category = "Level Snapshots")`
- L55 _private member_ `TArray<TObjectPtr<ULevelSnapshotFilter>> InstancedChildren;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Level Snapshots")`

#### enum `UParentFilter::EShouldBreak`  
`enum class EShouldBreak`  
_L41-45_
- L43 _public enumerator_ `Continue`
- L44 _public enumerator_ `Break`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelShapshotFilters/Public/Builtin/ConstantFilter.h` (Public)


#### class `UConstantFilter`  
`class UConstantFilter : public ULevelSnapshotFilter`  
_L11-34_
- reflection: `UCLASS()`
- inherits: `ULevelSnapshotFilter`
- desc: Filter which treats all actors the same.
- L17 _public function_ `virtual EFilterResult::Type IsActorValid(const FIsActorValidParams& Params) const override`
- L18 _public function_ `virtual EFilterResult::Type IsPropertyValid(const FIsPropertyValidParams& Params) const override`
- L19 _public function_ `virtual EFilterResult::Type IsDeletedActorValid(const FIsDeletedActorValidParams& Params) const override`
- L20 _public function_ `virtual EFilterResult::Type IsAddedActorValid(const FIsAddedActorValidParams& Params) const override`
- L24 _public member_ `TEnumAsByte<EFilterResult::Type> IsActorValidResult = EFilterResult::Include;` — `UPROPERTY(EditAnywhere, Category = "Config")`
- L27 _public member_ `TEnumAsByte<EFilterResult::Type> IsPropertyValidResult = EFilterResult::Include;` — `UPROPERTY(EditAnywhere, Category = "Config")`
- L30 _public member_ `TEnumAsByte<EFilterResult::Type> IsDeletedActorValidResult = EFilterResult::Include;` — `UPROPERTY(EditAnywhere, Category = "Config")`
- L33 _public member_ `TEnumAsByte<EFilterResult::Type> IsAddedActorValidResult = EFilterResult::Include;` — `UPROPERTY(EditAnywhere, Category = "Config")`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelShapshotFilters/Public/Builtin/LambdaFilter.h` (Public)


#### class `ULambdaFilter`  
`class ULambdaFilter : public ULevelSnapshotFilter`  
_L16-47_
- reflection: `UCLASS(meta = (InternalSnapshotFilter))`
- inherits: `ULevelSnapshotFilter`
- desc: Utility filter for native C++ filters.
- L21 _public typedef_ `using FIsActorValid = TFunction<EFilterResult::Type(const FIsActorValidParams&)>;`
- L22 _public typedef_ `using FIsPropertyValid = TFunction<EFilterResult::Type(const FIsPropertyValidParams&)>;`
- L23 _public typedef_ `using FIsDeletedActorValid = TFunction<EFilterResult::Type(const FIsDeletedActorValidParams&)>;`
- L24 _public typedef_ `using FIsAddedActorValid = TFunction<EFilterResult::Type(const FIsAddedActorValidParams&)>;`
- L26 _public function_ `static ULambdaFilter* Create(FIsActorValid IsActorValid, FIsPropertyValid IsPropertyValid, FIsDeletedActorValid IsDeletedActorValid, FIsAddedActorValid IsAddedActorValid, UObject* Outer = GetTransientPackage(), FName Name = FName(), EObjectFlags ObjectFlags = RF_NoFlags)`
- L37 _public function_ `virtual EFilterResult::Type IsActorValid(const FIsActorValidParams& Params) const override` — ~ Begin ULevelSnapshotFilter Interface
- L38 _public function_ `virtual EFilterResult::Type IsPropertyValid(const FIsPropertyValidParams& Params) const override`
- L39 _public function_ `virtual EFilterResult::Type IsDeletedActorValid(const FIsDeletedActorValidParams& Params) const override`
- L40 _public function_ `virtual EFilterResult::Type IsAddedActorValid(const FIsAddedActorValidParams& Params) const override`
- L43 _public member_ `FIsActorValid IsActorValidCallback;`
- L44 _public member_ `FIsPropertyValid IsPropertyValidCallback;`
- L45 _public member_ `FIsDeletedActorValid IsDeletedActorValidCallback;`
- L46 _public member_ `FIsAddedActorValid IsAddedActorValidCallback;`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelShapshotFilters/Public/Builtin/PropertyHasNameFilter.h` (Public)


#### enum `ENameMatchingRule::Type`  
`enum Type : int`  
_L12-22_
- L15 _public enumerator_ `MatchesExactly` — The property name must match the given name exactly.
- L17 _public enumerator_ `MatchesIgnoreCase` — The name must match the given name but ignores the case
- L19 _public enumerator_ `ContainsExactly` — The name must contains the following substring (case sensitive)
- L21 _public enumerator_ `ContainsIgnoreCase` — The name must contains the following substring (case insensitive)

#### class `UPropertyHasNameFilter`  
`class UPropertyHasNameFilter : public UPropertySelectorFilter`  
_L30-61_
- reflection: `UCLASS(meta = (CommonSnapshotFilter))`
- inherits: `UPropertySelectorFilter`
- desc: Allows a property when is has a certain name Use case: You only want to allow properties named "MyPropertyName"
- L36 _public prototype_ `virtual EFilterResult::Type IsPropertyValid(const FIsPropertyValidParams& Params) const override;`
- L41 _private prototype_ `bool DoesAnyOwningPropertyMatch(const FIsPropertyValidParams& Params) const;`
- L42 _private prototype_ `EFilterResult::Type GetPropertyMatchResult(const FString& PropertyNName) const;`
- L46 _private member_ `TEnumAsByte<ENameMatchingRule::Type> NameMatchingRule = ENameMatchingRule::ContainsIgnoreCase;` — `UPROPERTY(EditAnywhere, Category = "Config")` — How to compare the property name to AllowedNames
- L55 _private member_ `bool bIncludeStructSubproperties = true;` — `UPROPERTY(EditAnywhere, Category = "Config")` — Whether to implicitly include sub-properties of structs. Example: AllowedNames contains RelativeLocation. If bIncludeStructSubproperties == true, then the properties X, Y, and Z are included. Otherwise, you must explicitly add them to AllowedNames.
- L59 _private member_ `TSet<FString> AllowedNames;` — `UPROPERTY(EditAnywhere, Category = "Config")` — The names to match the property name against.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ENameMatchingRule`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelShapshotFilters/Public/Builtin/PropertySelector/PropertySelectorFilter.h` (Public)


#### class `UPropertySelectorFilter`  
`class UPropertySelectorFilter : public ULevelSnapshotBlueprintFilter`  
_L11-27_
- reflection: `UCLASS(Abstract)`
- inherits: `ULevelSnapshotBlueprintFilter`
- desc: Base class for filters that only implement IsActorValid
- L17 _public prototype_ `virtual EFilterResult::Type IsActorValid(const FIsActorValidParams& Params) const override;`
- L18 _public prototype_ `virtual EFilterResult::Type IsDeletedActorValid(const FIsDeletedActorValidParams& Params) const override;`
- L19 _public prototype_ `virtual EFilterResult::Type IsAddedActorValid(const FIsAddedActorValidParams& Params) const override;`
- L26 _public member_ `TEnumAsByte<EFilterResult::Type> DefaultResult = EFilterResult::DoNotCare;` — `UPROPERTY(EditAnywhere, Category = "Config")` — What to return for IsActorValid, IsDeletedActorValid, and IsAddedActorValid

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelShapshotFilters/Public/Builtin/PropertySelector/TransformPropertyFilter.h` (Public)


#### class `UTransformPropertyFilter`  
`class UTransformPropertyFilter : public UPropertySelectorFilter`  
_L16-36_
- reflection: `UCLASS()`
- inherits: `UPropertySelectorFilter`
- desc: Allows you to filter location, rotation, and scale properties on scene components. Use case: You want to restore the location but not rotation of an actor.
- L22 _public prototype_ `virtual EFilterResult::Type IsPropertyValid(const FIsPropertyValidParams& Params) const override;`
- L27 _public member_ `TEnumAsByte<EFilterResult::Type> Location;` — `UPROPERTY(EditAnywhere, Category = "Transform")` — Should the location property be restored?
- L31 _public member_ `TEnumAsByte<EFilterResult::Type> Rotation;` — `UPROPERTY(EditAnywhere, Category = "Transform")` — Should the rotation property be restored?
- L35 _public member_ `TEnumAsByte<EFilterResult::Type> Scale;` — `UPROPERTY(EditAnywhere, Category = "Transform")` — Should the scale property be restored?

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelShapshotFilters/Public/Builtin/PropertyTypeFilter.h` (Public)


#### enum `EBlueprintPropertyType::Type`  
`enum Type : int`  
_L13-52_
- desc: Copied from EPropertyType
- L19 _public enumerator_ `Byte` — CPT_NONE
- L25 _public enumerator_ `Int` — CPT_UInt16 = 2, Unsupported by Blueprints CPT_UInt32 = 3, Unsupported by Blueprints CPT_UInt64 = 4, Unsupported by Blueprints CPT_Int8 = 5, Unsupported by Blueprints CPT_Int16 = 6, Unsupported by Blueprints
- L26 _public enumerator_ `Int64`
- L27 _public enumerator_ `Bool`
- L32 _public enumerator_ `Float` — CPT_Bool8 = 10, Unsupported by Blueprints CPT_Bool16 = 11, Unsupported by Blueprints CPT_Bool32 = 12, Unsupported by Blueprints CPT_Bool64 = 13, Unsupported by Blueprints
- L33 _public enumerator_ `ObjectReference`
- L34 _public enumerator_ `Name`
- L36 _public enumerator_ `Interface` — CPT_Delegate = 17, Not useful for level snapshots
- L38 _public enumerator_ `Struct` — CPT_Unused_Index_19 = 19,
- L41 _public enumerator_ `String` — CPT_Unused_Index_21 = 21, CPT_Unused_Index_22 = 22,
- L42 _public enumerator_ `Text`
- L44 _public enumerator_ `WeakObjectReference` — CPT_MulticastDelegate = 25, Not useful for level snapshots
- L46 _public enumerator_ `SoftObjectReference` — CPT_LazyObjectReference = 27, No idea what this is; probably not useful for Blueprints
- L47 _public enumerator_ `Double`
- L48 _public enumerator_ `Array`
- L49 _public enumerator_ `Map`
- L50 _public enumerator_ `Set`

#### class `UPropertyTypeFilter`  
`class UPropertyTypeFilter : public UPropertySelectorFilter`  
_L61-76_
- reflection: `UCLASS()`
- inherits: `UPropertySelectorFilter`
- desc: Allows a property if it is of a certain type. Use case: You want to include only int properties.
- L67 _public prototype_ `virtual EFilterResult::Type IsPropertyValid(const FIsPropertyValidParams& Params) const override;`
- L74 _private member_ `TSet<TEnumAsByte<EBlueprintPropertyType::Type>> AllowedTypes;` — `UPROPERTY(EditAnywhere, Category = "Config")` — The property types that you want to allow

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace EBlueprintPropertyType`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelShapshotFilters/Public/FilterBlueprintFunctionLibrary.h` (Public)


#### class `UFilterBlueprintFunctionLibrary`  
`class UFilterBlueprintFunctionLibrary : public UBlueprintFunctionLibrary`  
_L12-20_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L18 _public prototype_ `static ULevelSnapshotFilter* CreateFilterByClass(const TSubclassOf<ULevelSnapshotFilter>& Class, FName Name = NAME_None, UObject* Outer = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Level Snapshots")`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelShapshotFilters/Public/LevelSnapshotFilterParams.h` (Public)


#### struct `FIsActorValidParams`  
`struct FIsActorValidParams`  
_L13-30_
- reflection: `USTRUCT(BlueprintType)`
- L19 _public member_ `TObjectPtr<AActor> SnapshotActor = nullptr;` — `UPROPERTY(BlueprintReadWrite, Category = "Level Snapshots")` — The actor saved in the snapshot
- L23 _public member_ `TObjectPtr<AActor> LevelActor = nullptr;` — `UPROPERTY(BlueprintReadWrite, Category = "Level Snapshots")` — The actor equivalent to LevelActor: it exists in the world
- L25 _public prototype_ `FIsActorValidParams() = default;`
- L26 _public function_ `FIsActorValidParams(AActor* InSnapshotActor, AActor* InLevelActor) : SnapshotActor(InSnapshotActor) , LevelActor(InLevelActor)`

#### struct `FIsPropertyValidParams`  
`struct FIsPropertyValidParams`  
_L33-78_
- reflection: `USTRUCT(BlueprintType)`
- L39 _public member_ `TObjectPtr<AActor> SnapshotActor = nullptr;` — `UPROPERTY(BlueprintReadOnly, Category = "Level Snapshots")` — The actor saved in the snapshot
- L43 _public member_ `TObjectPtr<AActor> LevelActor = nullptr;` — `UPROPERTY(BlueprintReadOnly, Category = "Level Snapshots")` — The actor equivalent to LevelActor: it exists in the world
- L47 _public member_ `FPropertyContainerHandle SnapshotPropertyContainer;` — `UPROPERTY(BlueprintReadOnly, Category = "Level Snapshots")` — For passing to FProperty::ContainerPtrToValuePtr. This is either SnapshotActor or a subobject thereof.
- L51 _public member_ `FPropertyContainerHandle LevelPropertyContainers;` — `UPROPERTY(BlueprintReadOnly, Category = "Level Snapshots")` — For passing to FProperty::ContainerPtrToValuePtr. This is either LevelPropertyContainers or a subobject thereof.
- L55 _public member_ `TFieldPath<FProperty> Property;` — `UPROPERTY(BlueprintReadOnly, Category = "Level Snapshots")` — The property that we may want to rollback.
- L67 _public member_ `TArray<FString> PropertyPath;` — `UPROPERTY(BlueprintReadOnly, Category = "Level Snapshots")` — Each elements is the name of a subobject name leading to this property. The last element is the property name. The first element is either the name of a component or a struct/subobject in the root actor. Examples: - MyCustomComponent -> MyCustomStructPropertyName -> PropertyName - MyCustomComponent -> MyCustomStructPropertyName - StructPropertyNameInActor -> PropertyName
- L69 _public prototype_ `FIsPropertyValidParams() = default;`
- L70 _public function_ `FIsPropertyValidParams(AActor* InSnapshotActor, AActor* InLevelActor, const FPropertyContainerHandle& InSnapshotPropertyContainer, const FPropertyContainerHandle& InLevelPropertyContainers, const TFieldPath<FProperty>& InProperty, const TArray<FString>& InPropertyPath) : SnapshotActor(InSnapshotActor) , LevelActor(InLevelActor) , SnapshotPropertyContainer(InSnapshotPropertyContainer) , LevelPropertyContainers(InLevelPropertyContainers) , Property(InProperty) , PropertyPath(InPropertyPath)`

#### struct `FIsDeletedActorValidParams`  
`struct FIsDeletedActorValidParams`  
_L81-108_
- reflection: `USTRUCT(BlueprintType)`
- L90 _public member_ `FSoftObjectPath SavedActorPath;` — `UPROPERTY(BlueprintReadOnly, Category = "Level Snapshots")` — Holds path info for an actor that was deleted since the snapshot was taken. Contains the path to the original actor before it was deleted.
- L93 _public member_ `TFunction<AActor* (const FSoftObjectPath&)> HelperForDeserialization;` — Helper property for deserializing SavedActorPath.
- L96 _public member_ `TFunction<UClass* (const FSoftObjectPath&)> ClassGetter;` — Helper for getting the class of the deleted actor
- L98 _public prototype_ `FIsDeletedActorValidParams() = default;`
- L99 _public function_ `FIsDeletedActorValidParams( FSoftObjectPath SavedActorPath, TFunction<AActor*(const FSoftObjectPath&)> HelperForDeserialization, TFunction<UClass* (const FSoftObjectPath&)> ClassGetter ) : SavedActorPath(SavedActorPath) , HelperForDeserialization(HelperForDeserialization) , ClassGetter(ClassGetter)`

#### struct `FIsAddedActorValidParams`  
`struct FIsAddedActorValidParams`  
_L111-123_
- reflection: `USTRUCT(BlueprintType)`
- L117 _public member_ `TObjectPtr<AActor> NewActor = nullptr;` — `UPROPERTY(BlueprintReadOnly, Category = "Level Snapshots")` — This actor was added to the level since the snapshot was taken.
- L119 _public prototype_ `FIsAddedActorValidParams() = default;`
- L120 _public function_ `explicit FIsAddedActorValidParams(AActor* NewActor) : NewActor(NewActor)`

#### struct `FIsDeletedComponentValidParams`  
`struct FIsDeletedComponentValidParams`  
_L126-143_
- reflection: `USTRUCT(BlueprintType)`
- L132 _public member_ `TObjectPtr<UActorComponent> DeletedComponent = nullptr;` — `UPROPERTY(BlueprintReadOnly, Category = "Level Snapshots")` — This component was removed from the actor. This instance exists in a transient snapshot world; it does not exist in the editor world.
- L136 _public member_ `TObjectPtr<AActor> EditorActor = nullptr;` — `UPROPERTY(BlueprintReadOnly, Category = "Level Snapshots")` — The actor the component was removed from; This instance exists in the editor world.
- L138 _public prototype_ `FIsDeletedComponentValidParams() = default;`
- L139 _public function_ `explicit FIsDeletedComponentValidParams(UActorComponent* DeletedComponent, AActor* EditorActor) : DeletedComponent(DeletedComponent) , EditorActor(EditorActor)`

#### struct `FIsAddedComponentValidParams`  
`struct FIsAddedComponentValidParams`  
_L146-158_
- reflection: `USTRUCT(BlueprintType)`
- L152 _public member_ `TObjectPtr<UActorComponent> AddedComponent = nullptr;` — `UPROPERTY(BlueprintReadOnly, Category = "Level Snapshots")` — This component was added to the actor. This is an instance in the editor world.
- L154 _public prototype_ `FIsAddedComponentValidParams() = default;`
- L155 _public function_ `explicit FIsAddedComponentValidParams(UActorComponent* AddedComponent) : AddedComponent(AddedComponent)`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelShapshotFilters/Public/LevelSnapshotFilters.h` (Public)


#### enum `EFilterResult::Type`  
`enum Type : int`  
_L13-28_
- L17 _public enumerator_ `Include` — This actor / property will be included.
- L20 _public enumerator_ `Exclude` — This actor / property will be excluded.
- L27 _public enumerator_ `DoNotCare` — The filter does not care what happens to this actor / property. Another filter will decide. If all filters don't care, actor / property is included. Use this for filters that only implement one function: IsActorValid or IsPropertyValid.

#### class `ULevelSnapshotFilter`  
`class ULevelSnapshotFilter : public UObject`  
_L63-97_
- reflection: `UCLASS(Abstract, BlueprintType, EditInlineNew)`
- inherits: `UObject`
- desc: Base-class for filtering a level snapshot. Native C++ classes should inherit directly from this class.
- L69 _public prototype_ `virtual EFilterResult::Type IsActorValid(const FIsActorValidParams& Params) const;` — @return Whether this actor should be considered when applying a snapshot to the world.
- L72 _public prototype_ `virtual EFilterResult::Type IsPropertyValid(const FIsPropertyValidParams& Params) const;` — @return Whether the property in LevelActor should be overriden with the value in SnapshotActor.
- L78 _public prototype_ `virtual EFilterResult::Type IsDeletedActorValid(const FIsDeletedActorValidParams& Params) const;` — This is called when an actor was removed from the world since the snapshot had been taken. @return Whether to track the removed actor
- L84 _public prototype_ `virtual EFilterResult::Type IsAddedActorValid(const FIsAddedActorValidParams& Params) const;` — This is called when an actor was added to the world since the snapshot had been taken. @return Whether to track the added actor
- L90 _public prototype_ `virtual EFilterResult::Type IsDeletedComponentValid(const FIsDeletedComponentValidParams& Params) const;` — This is called when a component was removed from an actor since the snapshot had been taken. @return Whether to track the removed component
- L96 _public prototype_ `virtual EFilterResult::Type IsAddedComponentValid(const FIsAddedComponentValidParams& Params) const;` — This is called when a component was added to the world since the snapshot had been taken. @return Whether to track the added component

#### class `ULevelSnapshotBlueprintFilter`  
`class ULevelSnapshotBlueprintFilter : public ULevelSnapshotFilter`  
_L103-148_
- reflection: `UCLASS(Abstract, Blueprintable)`
- inherits: `ULevelSnapshotFilter`
- desc: Base-class for filtering a level snapshot in Blueprints.
- L113 _public prototype_ `EFilterResult::Type IsActorValid(const FIsActorValidParams& Params) const override;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Level Snapshots")` — @return Whether the actor should be considered for the level snapshot.
- L119 _public prototype_ `EFilterResult::Type IsPropertyValid(const FIsPropertyValidParams& Params) const override;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Level Snapshots")` — @return Whether this property should be considered for rolling back to the version in the snapshot.
- L126 _public prototype_ `EFilterResult::Type IsDeletedActorValid(const FIsDeletedActorValidParams& Params) const override;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Level Snapshots")` — This is called when an actor was removed from the world since the snapshot had been taken. @return Whether to track the removed actor
- L133 _public prototype_ `EFilterResult::Type IsAddedActorValid(const FIsAddedActorValidParams& Params) const override;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Level Snapshots")` — This is called when an actor was added to the world since the snapshot had been taken. @return Whether to track the added actor
- L140 _public prototype_ `EFilterResult::Type IsDeletedComponentValid(const FIsDeletedComponentValidParams& Params) const;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Level Snapshots")` — This is called when a component was removed from an actor since the snapshot had been taken. @return Whether to track the removed component
- L147 _public prototype_ `EFilterResult::Type IsAddedComponentValid(const FIsAddedComponentValidParams& Params) const;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Level Snapshots")` — This is called when a component was added to the world since the snapshot had been taken. @return Whether to track the added component

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace EFilterResult`
- L31 _namespace_ `namespace EFilterResult`
- L33 _function_ `static bool ShouldInclude(EFilterResult::Type Type)` (scope `EFilterResult`)
- L38 _function_ `static bool CanInclude(EFilterResult::Type Type)` (scope `EFilterResult`)
- L43 _function_ `static bool CanNegate(EFilterResult::Type Type)` (scope `EFilterResult`)
- L48 _function_ `static EFilterResult::Type Negate(EFilterResult::Type Type)` (scope `EFilterResult`)

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelShapshotFilters/Public/LevelSnapshotFiltersModule.h` (Public)


#### class `FLevelSnapshotFiltersModule`  
`class FLevelSnapshotFiltersModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelShapshotFilters/Public/PropertyBlueprintFunctionLibrary.h` (Public)


#### class `UPropertyBlueprintFunctionLibrary`  
`class UPropertyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary`  
_L11-32_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L18 _public prototype_ `static FString GetPropertyOriginPath(const TFieldPath<FProperty>& Property);` — `UFUNCTION(BlueprintPure, Category = "Level Snapshots")` — Returns a path containing information which class declare the property.
- L22 _public prototype_ `static FString GetPropertyName(const TFieldPath<FProperty>& Property);` — `UFUNCTION(BlueprintPure, Category = "Level Snapshots")` — Gets only the property name of a property.
- L26 _public prototype_ `static AActor* LoadSnapshotActor(const FIsDeletedActorValidParams& Params);` — `UFUNCTION(BlueprintPure, Category = "Level Snapshots")` — Loads the actor identified by Params. You can use this for advanced filter queries.
- L30 _public prototype_ `static UClass* GetActorClassFromDeletedParams(const FIsDeletedActorValidParams& Params);` — `UFUNCTION(BlueprintPure, Category = "Level Snapshots")` — Finds the actor class from the given FIsDeletedActorValidParams. Use this for advanced filter queries

### `Plugins/VirtualProduction/LevelSnapshots/Source/LevelShapshotFilters/Public/PropertyContainerHandle.h` (Public)


#### struct `FPropertyContainerHandle`  
`struct FPropertyContainerHandle`  
_L10-23_
- reflection: `USTRUCT(BlueprintType)`
- desc: Blueprint wrapper for FProperty containers
- L16 _public member_ `void* PropertyContainerPtr;` — Pass this to FProperty::ContainerPtrToValuePtr(PropertyContainer). Never null.
- L18 _public prototype_ `FPropertyContainerHandle() = default;`
- L19 _public function_ `FPropertyContainerHandle(void* InPropertyContainerPtr) : PropertyContainerPtr(InPropertyContainerPtr)`
