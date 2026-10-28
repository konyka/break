# Plugins / SignificanceManager

- module root: `Plugins/Runtime/SignificanceManager/Source/SignificanceManager`
- headers: 2; symbols: 74
- symbol kinds: class=1, delegate=2, enum=1, enumerator=3, function=15, macro=1, member=23, prototype=20, struct=4, typedef=4
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, EngineSettings

### `Plugins/Runtime/SignificanceManager/Source/SignificanceManager/Public/OrderedBudget.h` (Public)


#### struct `FOrderedBudget`  
`struct FOrderedBudget`  
_L8-89_
- desc: Manages how to allocate a budget of levels to an ordered list of items (e.g., how to distribute minimum LOD levels to the N closest characters)
- L11 _public function_ `FOrderedBudget() : ValueForOutOfBounds(0)`
- L17 _public function_ `int32 GetBudgetForIndex(int32 Index) const` — Returns the budget number for the Index-th closest character
- L24 _public function_ `int32 GetBudgetLength() const` — Returns the number of items specified in the budget
- L37 _public function_ `bool RecreateBudget(const FString& Specification)` — Recreates the budget given a specification string. For example, the specification "0,2,3,5" would correspond to the following budget: Level0: 0 Level1: 2 Level2: 3 Level3: 5 Creating a table that contains: 1,1,2,2,2,3,3,3,3,3 (out of bounds = 4) Returns true if the budget was modified, or false if the existing budget already matched
- L69 _public function_ `void SetBudgetScale(float InScale)`
- L79 _private member_ `TArray<int32> BudgetValues;` — This is the budget value for the i-th closest character (e.g., there will be be 10 entries if the budgets ranges sum to cover 10)
- L82 _private member_ `float BudgetValuesScale = 1.0f;` — The scalar to apply to the budget values, it does so by compressing the index used when requesting the budget
- L85 _private member_ `int32 ValueForOutOfBounds;` — This is the budget value for things with an index further away than BudgetByIndex.Num()
- L88 _private member_ `FString BudgetString;` — My budget string

### `Plugins/Runtime/SignificanceManager/Source/SignificanceManager/Public/SignificanceManager.h` (Public)


#### class `USignificanceManager`  
`class USignificanceManager : public UObject`  
_L30-210_
- reflection: `UCLASS(MinimalAPI, config=Engine, defaultconfig)`
- inherits: `UObject`
- desc: The significance manager provides a framework for registering objects by tag to each have a significance value calculated from which a game specific subclass and game logic can make decisions about what level of detail objects should be at, tick frequency, whether to spawn effects, and other such functionality Each object that is registered must have a corresponding unregister event or else a dangling Object reference will be left resulting in an eventual crash once the Object has been garbage collected. Each user of the significance manager is expected to call the Update function from the appropriate location in the game code.  GameViewportClient::Tick may often serve as a good place to do this.
- L35 _public typedef_ `typedef TFunction<float(UObject*, const FTransform&)> FSignificanceFunction;`
- L36 _public typedef_ `typedef TFunction<void(UObject*, float, float, bool)> FPostSignificanceFunction;`
- L40 _public typedef_ `typedef TFunction<float(FManagedObjectInfo*, const FTransform&)> FManagedObjectSignificanceFunction;`
- L41 _public typedef_ `typedef TFunction<void(FManagedObjectInfo*, float, float, bool)> FManagedObjectPostSignificanceFunction;`
- L110 _public prototype_ `USignificanceManager();`
- L113 _public prototype_ `virtual void BeginDestroy() override;`
- L114 _public prototype_ `virtual UWorld* GetWorld() const override final;`
- L118 _public prototype_ `virtual void Update(TArrayView<const FTransform> Viewpoints);` — Overridable function to update the managed objects' significance
- L121 _public prototype_ `virtual void RegisterObject(UObject* Object, FName Tag, FManagedObjectSignificanceFunction SignificanceFunction, EPostSignificanceType InPostSignificanceType = EPostSignificanceType::None, FManagedObjectPostSignificanceFunction InPostSignificanceFunction = nullptr);` — Overridable function used to register an object as managed by the significance manager
- L124 _public prototype_ `virtual void UnregisterObject(UObject* Object);` — Overridable function used to unregister an object as managed by the significance manager
- L127 _public prototype_ `void UnregisterAll(FName Tag);` — Unregisters all objects with the specified tag.
- L130 _public prototype_ `const TArray<FManagedObjectInfo*>& GetManagedObjects(FName Tag) const;` — Returns objects of specified tag, Tag must be specified or else an empty array will be returned
- L133 _public prototype_ `void GetManagedObjects(TArray<FManagedObjectInfo*>& OutManagedObjects, bool bInSignificanceOrder = false) const;` — Returns all managed objects regardless of tag
- L136 _public prototype_ `USignificanceManager::FManagedObjectInfo* GetManagedObject(UObject* Object) const;` — Returns the managed object for the passed-in object, if any. Otherwise returns nullptr
- L139 _public prototype_ `const USignificanceManager::FManagedObjectInfo* GetManagedObject(const UObject* Object) const;` — Returns the managed object for the passed-in object, if any. Otherwise returns nullptr
- L142 _public prototype_ `float GetSignificance(const UObject* Object) const;` — Returns the significance value for a given object, returns 0 if object is not managed
- L145 _public prototype_ `bool QuerySignificance(const UObject* Object, float& OutSignificance) const;` — Returns true if the object is being tracked, placing the significance value in OutSignificance (or 0 if object is not managed)
- L148 _public prototype_ `static USignificanceManager* Get(const UWorld* World);` — Returns the significance manager for the specified World
- L152 _public function_ `template<class T> static T* Get(const UWorld* World)` — Templated convenience function to return a significance manager cast to a known type
- L158 _public function_ `const TArray<FTransform>& GetViewpoints() const` — Returns the list of viewpoints currently being represented by the significance manager
- L160 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L164 _protected prototype_ `void RegisterManagedObject(FManagedObjectInfo* ObjectInfo);` — Internal function that takes the managed object info and registers it with the significance manager
- L167 _protected prototype_ `virtual void OnShowDebugInfo(AHUD* HUD, UCanvas* Canvas, const FDebugDisplayInfo& DisplayInfo, float& YL, float& YPos);` — Callback function registered with HUD to supply debug info when ShowDebug SignificanceManager has been entered on the console
- L170 _protected member_ `uint32 bCreateOnClient:1;` — Whether the significance manager should be created on a client. Only used from CDO and
- L173 _protected member_ `uint32 bCreateOnServer:1;` — Whether the significance manager should be created on the server
- L176 _protected member_ `uint32 bSortSignificanceAscending:1;` — Whether the significance sort should sort high values to the end of the list
- L179 _protected member_ `TArray<FTransform> Viewpoints;` — The cached viewpoints for significance for calculating when a new object is registered
- L184 _private member_ `TMap<FName, TArray<FManagedObjectInfo*>> ManagedObjectsByTag;` — All objects being managed organized by Tag
- L187 _private member_ `TMap<TObjectPtr<UObject>, FManagedObjectInfo*> ManagedObjects;` — Reverse lookup map to find the tag for a given object
- L190 _private member_ `TArray<FManagedObjectInfo*> ObjArray;` — Array of all managed objects that we use for iteration during update. This is kept in sync with the ManagedObjects map.
- L192 _private member_ `TArray<FManagedObjectInfo*> ObjArrayCopy;` — We copy ObjArray to this before running update to avoid mutations during the update. To avoid memory allocations, making it a member.
- L200 _private member_ `TArray<FSequentialPostWorkPair> ObjWithSequentialPostWork;` — Array of all managed objects requiring sequential work that we use for iteration during update. This is kept in sync with the ManagedObjects map.
- L202 _private member_ `TArray<FSequentialPostWorkPair> ObjWithSequentialPostWorkCopy;` — We copy ObjWithSequentialPostWork to this before running update to avoid mutations during the update. To avoid memory allocations, making it a member.
- L206 _private member_ `FSoftClassPath SignificanceManagerClassName;` — `UPROPERTY(globalconfig, noclear, EditAnywhere, Category=DefaultClasses, meta=(MetaClass="/Script/SignificanceManager.SignificanceManager", DisplayName="Significance Manager Class"))` — Game specific significance class to instantiate

#### enum `USignificanceManager::EPostSignificanceType`  
`enum class EPostSignificanceType : uint8`  
_L44-52_
- L47 _public enumerator_ `None` — The object has no post work to be done
- L49 _public enumerator_ `Concurrent` — The object's post work can be done safely in parallel
- L51 _public enumerator_ `Sequential` — The object's post work must be done sequentially

#### struct `USignificanceManager::FManagedObjectInfoFixLayout`  
`struct FManagedObjectInfoFixLayout`  
_L55-58_
- desc: Hacky base class to avoid 8 bytes of padding after the vtable
- L57 _public prototype_ `virtual ~FManagedObjectInfoFixLayout() = default;`

#### struct `USignificanceManager::FManagedObjectInfo`  
`struct FManagedObjectInfo : public FManagedObjectInfoFixLayout`  
_L60-108_
- inherits: `FManagedObjectInfoFixLayout`
- L62 _public function_ `FManagedObjectInfo() : Object(nullptr) , Significance(-1.0f) , PostSignificanceType(EPostSignificanceType::None)`
- L69 _public function_ `FManagedObjectInfo(UObject* InObject, FName InTag, FManagedObjectSignificanceFunction InSignificanceFunction, EPostSignificanceType InPostSignificanceType = EPostSignificanceType::None, FManagedObjectPostSignificanceFunction InPostSignificanceFunction = nullptr) : Object(InObject) , Tag(InTag) , Significance(1.0f) , PostSignificanceType(InPostSignificanceType) , SignificanceFunction(MoveTemp(InSignificanceFunction)) , PostSignificanceFunction(MoveTemp(InPostSignificanceFunction))`
- L88 _public function_ `UObject* GetObject() const`
- L89 _public function_ `FName GetTag() const`
- L90 _public function_ `float GetSignificance() const`
- L91 _public function_ `FManagedObjectSignificanceFunction GetSignificanceFunction() const`
- L92 _public function_ `EPostSignificanceType GetPostSignificanceType() const`
- L93 _public function_ `FManagedObjectPostSignificanceFunction GetPostSignificanceNotifyDelegate() const`
- L96 _private member_ `UObject* Object;`
- L97 _private member_ `FName Tag;`
- L98 _private member_ `float Significance;`
- L99 _private member_ `EPostSignificanceType PostSignificanceType;`
- L101 _private member_ `FManagedObjectSignificanceFunction SignificanceFunction;`
- L102 _private member_ `FManagedObjectPostSignificanceFunction PostSignificanceFunction;`
- L104 _private prototype_ `void UpdateSignificance(const TArray<FTransform>& ViewPoints, const bool bSortSignificanceAscending);`

#### struct `USignificanceManager::FSequentialPostWorkPair`  
`struct FSequentialPostWorkPair`  
_L194-198_
- L196 _public member_ `FManagedObjectInfo* ObjectInfo;`
- L197 _public member_ `float OldSignificance;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SIGNIFICANCEMANAGER_API`
- L16 _delegate_ `DECLARE_STATS_GROUP(TEXT("Significance Manager"), STATGROUP_SignificanceManager`
- L17 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSignificance, Log, All);`
- L17 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSignificance, Log, All);`
