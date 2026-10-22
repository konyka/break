# Plugins / SourceFilteringCore

- module root: `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringCore`
- headers: 4; symbols: 50
- symbol kinds: class=5, enum=3, enumerator=13, function=9, macro=1, member=10, prototype=7, struct=2
- PrivateDependencyModuleNames: Core, CoreUObject

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringCore/Public/DataSourceFiltering.h` (Public)


#### enum `EFilterSetMode`  
`enum class EFilterSetMode : uint8`  
_L11-17_
- reflection: `UENUM()`
- desc: Enum representing the possible Filter Set operations
- L13 _public enumerator_ `AND`
- L14 _public enumerator_ `OR`
- L15 _public enumerator_ `NOT`
- L16 _public enumerator_ `Count UMETA(Hidden)`

#### enum `ESourceActorFilterOperation`  
`enum class ESourceActorFilterOperation`  
_L22-29_
- desc: Enum representing all possible Source Filter operations, used by FSourceFilterTrace::OutputFilterOperation
- L24 _public enumerator_ `RemoveFilter`
- L25 _public enumerator_ `MoveFilter`
- L26 _public enumerator_ `ReplaceFilter`
- L27 _public enumerator_ `SetFilterMode`
- L28 _public enumerator_ `SetFilterState`

#### enum `EWorldFilterOperation`  
`enum class EWorldFilterOperation`  
_L32-38_
- desc: Enum representing all possible World Filter operations, used by FSourceFilterTrace::OutputWorldOperation
- L34 _public enumerator_ `TypeFilter`
- L35 _public enumerator_ `NetModeFilter`
- L36 _public enumerator_ `InstanceFilter`
- L37 _public enumerator_ `RemoveWorld`

#### struct `FActorClassFilter`  
`struct FActorClassFilter`  
_L42-61_
- reflection: `USTRUCT()`
- desc: High-level filter structure used when filtering AActor instances to apply user filters to inside of a UWorld
- L49 _public member_ `FSoftClassPath ActorClass;` — `UPROPERTY(EditAnywhere, Category = TraceSourceFiltering)` — Target actor class used when applying this filter
- L53 _public member_ `bool bIncludeDerivedClasses = false;` — `UPROPERTY(EditAnywhere, Category = TraceSourceFiltering)` — Flag as to whether or not any derived classes from ActorClass should also be considered when filtering
- L55 _public function_ `inline bool operator==(const FActorClassFilter Rhs)`

#### Free symbols / members of external scopes

- L19 _prototype_ `ENUM_RANGE_BY_COUNT(EFilterSetMode, EFilterSetMode::Count);`

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringCore/Public/IDataSourceFilterInterface.h` (Public)


#### struct `FDataSourceFilterConfiguration`  
`struct FDataSourceFilterConfiguration`  
_L11-28_
- reflection: `USTRUCT(BlueprintType)`
- L15 _public function_ `FDataSourceFilterConfiguration() : bOnlyApplyDuringActorSpawn(false), bCanRunAsynchronously(false), FilterApplyingTickInterval(1)`
- L19 _public member_ `uint8 bOnlyApplyDuringActorSpawn : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Filtering)` — Flag whether or not this filter should only applied once, whenever an actor is spawned
- L23 _public member_ `uint8 bCanRunAsynchronously : 1;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Filtering)` — Flag whether or not this filter does not rely on gamethread only data, and therefore can work on a differen thread
- L27 _public member_ `uint8 FilterApplyingTickInterval;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Filtering, meta=(EditCondition="!bOnlyApplyDuringActorSpawn", ClampMin="1", ClampMax="255", UIMin="1", UIMax="128"))` — Interval, in frames, between applying the filter. The resulting value is cached for intermediate frames.

#### class `UDataSourceFilterInterface`  
`class UDataSourceFilterInterface : public UInterface`  
_L31-34_
- reflection: `UINTERFACE(MinimalAPI, Blueprintable)`
- inherits: `UInterface`

#### class `IDataSourceFilterInterface`  
`class IDataSourceFilterInterface`  
_L37-62_
- desc: Interface used for implementing Engine and UnrealInsights versions respectively UDataSourceFilter and UTraceDataSourceFilter
- L43 _public prototype_ `void GetDisplayText(FText& OutDisplayText) const;` — `UFUNCTION(BlueprintNativeEvent, Category = TraceSourceFiltering)`
- L44 _public function_ `virtual void GetDisplayText_Implementation(FText& OutDisplayText) const`
- L50 _public prototype_ `void GetToolTipText(FText& OutDisplayText) const;` — `UFUNCTION(BlueprintNativeEvent, Category = TraceSourceFiltering)`
- L51 _public function_ `virtual void GetToolTipText_Implementation(FText& OutDisplayText) const`
- L56 _public prototype_ `virtual const FDataSourceFilterConfiguration& GetConfiguration() const = 0;`
- L57 _public prototype_ `virtual void SetEnabled(bool bState) = 0;`
- L58 _public prototype_ `virtual bool IsEnabled() const = 0;`
- L60 _protected function_ `virtual void GetDisplayText_Internal(FText& OutDisplayText) const`
- L61 _protected function_ `virtual void GetToolTipText_Internal(FText& OutDisplayText) const`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SOURCEFILTERINGCORE_API`

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringCore/Public/IDataSourceFilterSetInterface.h` (Public)


#### class `UDataSourceFilterSetInterface`  
`class UDataSourceFilterSetInterface : public UInterface`  
_L11-14_
- reflection: `UINTERFACE(MinimalAPI, Blueprintable)`
- inherits: `UInterface`

#### class `IDataSourceFilterSetInterface`  
`class IDataSourceFilterSetInterface`  
_L17-24_
- desc: Interface used for implementing Engine and UnrealInsights versions respectively UDataSourceFilterSet and UTraceDataSourceFilterSet
- L23 _public prototype_ `virtual EFilterSetMode GetFilterSetMode() const = 0;` — Return the current Filter Set operation mode

### `Plugins/Developer/TraceSourceFiltering/Source/SourceFilteringCore/Public/TraceSourceFilteringSettings.h` (Public)


#### class `UTraceSourceFilteringSettings`  
`class UTraceSourceFilteringSettings : public UObject`  
_L9-47_
- reflection: `UCLASS(MinimalAPI, Config=TraceSourceFilters)`
- inherits: `UObject`
- L14 _public function_ `UTraceSourceFilteringSettings() : bDrawFilteringStates(false), bDrawOnlyPassingActors(false), bDrawFilterDescriptionForRejectedActors(false)`
- L17 _public function_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override`
- L23 _public function_ `FSimpleMulticastDelegate& GetOnSourceFilteringSettingsChanged()`
- L30 _public member_ `bool bDrawFilteringStates;` — `UPROPERTY(Config)` — Whether or not the filtering state for all considered AActor's inside for a UWorld should be drawn using a wire frame box
- L34 _public member_ `bool bDrawOnlyPassingActors;` — `UPROPERTY(Config)` — Whether or not only AActor's that are not filtered out should be considered for drawing their wireframe box
- L38 _public member_ `bool bDrawFilterDescriptionForRejectedActors;` — `UPROPERTY(Config)` — Whether or not to draw the failed UDataSourceFilter's description for AActor's that did not pass the filtering
- L42 _public member_ `bool bOutputOptimizedFilterState;` — `UPROPERTY(Config)` — Whether or not to, whenever it changes, output the optimized filter setup state to the log
- L46 _protected member_ `FSimpleMulticastDelegate OnSourceFilteringSettingsChanged;` — Delegate called whenever the contained properties change (see PostEditChangeProperty)
