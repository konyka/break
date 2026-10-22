# Runtime / NavigationSystem

- module root: `Source/Runtime/NavigationSystem`
- headers: 59; symbols: 3284
- symbol kinds: class=60, delegate=18, enum=41, enumerator=151, externvar=4, function=508, macro=47, member=1032, namespace=14, prototype=1293, struct=88, typedef=23, union=2, variable=3
- PrivateDependencyModuleNames: Navmesh, RHI, RenderCore, SourceControl
- PrivateIncludePathModuleNames: DerivedDataCache, TargetPlatform
- PublicDependencyModuleNames: Chaos, Core, CoreUObject, EditorFramework, Engine, GeometryCollectionEngine, UnrealEd

### `Source/Runtime/NavigationSystem/Private/NavGraph/NavGraphGenerator.h` (Private)


#### class `FNavGraphGenerator`  
`class FNavGraphGenerator : public FNavDataGenerator`  
_L14-36_
- inherits: `FNavDataGenerator`
- desc: Class that handles generation of the ANavigationGraph data
- L17 _public prototype_ `FNavGraphGenerator(ANavigationGraph* InDestNavGraph);`
- L18 _public prototype_ `virtual ~FNavGraphGenerator();`
- L22 _private function_ `FNavGraphGenerator(FNavGraphGenerator const& NoCopy)` — Prevent copying.
- L23 _private function_ `FNavGraphGenerator& operator=(FNavGraphGenerator const& NoCopy)`
- L27 _private prototype_ `void Init();` — Performs initial setup of member variables so that generator is ready to do its thing from this point on
- L28 _private prototype_ `void CleanUpIntermediateData();`
- L29 _private prototype_ `void UpdateBuilding();`
- L33 _private member_ `TArray<AVolume const*> InclusionVolumes;` — Bounding geometry definition.
- L35 _private member_ `FCriticalSection GraphChangingLock;`

### `Source/Runtime/NavigationSystem/Private/NavigationObjectRepository.h` (Private)


#### class `UNavigationObjectRepository`  
`class UNavigationObjectRepository : public UWorldSubsystem`  
_L26-215_
- reflection: `UCLASS()`
- inherits: `UWorldSubsystem`
- desc: World subsystem dedicated to store different types of navigation related elements that the NavigationSystem needs to access.
- L46 _public prototype_ `TSharedPtr<const FNavigationElement> AddNavigationElement(FNavigationElement&& Element, ENotifyOnSuccess NotifyOnSuccess = ENotifyOnSuccess::Yes);` — Adds the provided navigation element to the list of registered elements. @param Element Reference to the navigation element to register. @param NotifyOnSuccess Indicates if OnNavigationElementRegisteredDelegate must be broadcast on successful registration. @return Handle to the registered element. @note Method will assert if the same element is registered twice.
- L53 _public prototype_ `void RemoveNavigationElement(FNavigationElementHandle Handle);` — Removes the navigation element associated with the provided handle from the list of registered elements. @param Handle Handle to the element to unregister. @note Method will assert if the element can't be removed (i.e., not registered or already unregistered).
- L58 _public prototype_ `void ForEachNavigationElement(TFunctionRef<void(const TSharedRef<const FNavigationElement>&)>) const;` — Iterates through all registered navigation elements and call provided function with the element as parameter.
- L65 _public prototype_ `TSharedPtr<const FNavigationElement> RegisterNavRelevantObject(const INavRelevantInterface& NavRelevantObject);` — Adds the provided object implementing INavRelevantInterface to the list of registered navigation relevant objects. @param NavRelevantObject INavRelevantInterface of the object to register. @note Method will also assert if same interface pointers is registered twice.
- L72 _public prototype_ `void UnregisterNavRelevantObject(const INavRelevantInterface& NavRelevantObject);` — Removes the provided interface from the list of registered navigation relevant objects. @param NavRelevantObject INavRelevantInterface of the object to unregister. @note Method will also assert if interface can't be removed (i.e. not registered or already unregistered).
- L79 _public prototype_ `void UnregisterNavRelevantObject(const UObject* NavRelevantObject);` — Removes the provided object from the list of registered navigation relevant objects. @param NavRelevantObject INavRelevantInterface of the object to unregister. @note Method will also assert if interface can't be removed (i.e. not registered or already unregistered).
- L86 _public prototype_ `FNavigationElementHandle GetNavigationElementHandleForUObject(const UObject* NavRelevantObject) const;` — Returns the handle associated with the specific UObject if it is registered in the repository. @param NavRelevantObject The UObject for which the handle must be retrieved. @return The handle associated with the specified UObject if already registered, an invalid handle otherwise.
- L94 _public prototype_ `TSharedPtr<const FNavigationElement> GetNavigationElementForUObject(const UObject* NavRelevantObject) const;` — Returns a shared pointer to the FNavigationElement created for a registered UObject. @param NavRelevantObject The UObject for which the FNavigationElement must be retrieved. @return A valid shared pointer if the specified UObject is registered and an associated FNavigationElement was created, null pointer otherwise.
- L102 _public prototype_ `TSharedPtr<FNavigationElement> GetMutableNavigationElementForUObject(const UObject* NavRelevantObject) const;` — Returns a shared pointer to the mutable FNavigationElement created for a registered UObject. @param NavRelevantObject The UObject for which the FNavigationElement must be retrieved. @return A valid shared pointer if the specified UObject is registered and an associated FNavigationElement was created, null pointer otherwise.
- L113 _public prototype_ `TSharedPtr<const FNavigationElement> UpdateNavigationElementForUObject(const INavRelevantInterface& NavRelevantInterface, const UObject& NavRelevantObject);` — Returns a shared pointer to the FNavigationElement created for a registered UObject. This method will not handle other navigation structure updates (e.g., NavigationOctree) and should only be used by the NavigationSystem. @param NavRelevantInterface The interface to use to update an existing element @param NavRelevantObject The UObject for which the FNavigationElement must be retrieved. @return A valid shared pointer if the specified UObject is registered and an associated FNavigationElement was created, null pointer otherwise.
- L120 _public prototype_ `TSharedPtr<const FNavigationElement> GetNavigationElementForHandle(FNavigationElementHandle Handle) const;` — Returns a shared pointer to the FNavigationElement associated with the provided handle. @param Handle The handle for which the FNavigationElement must be retrieved. @return A valid shared pointer if a FNavigationElement associated with the provided handle was registered, null pointer otherwise.
- L127 _public prototype_ `TSharedPtr<FNavigationElement> GetMutableNavigationElementForHandle(FNavigationElementHandle Handle) const;` — Returns a shared pointer to the mutable FNavigationElement associated with the provided handle. @param Handle The handle for which the FNavigationElement must be retrieved. @return A valid shared pointer if a FNavigationElement associated with the provided handle was registered, null pointer otherwise.
- L134 _public prototype_ `void RegisterCustomNavLinkObject(INavLinkCustomInterface& CustomNavLinkObject);` — Adds the provided interface to the list of registered custom navigation links. @param CustomNavLinkObject INavLinkCustomInterface of the object to register. @note Method will also assert if same interface pointers is registered twice.
- L141 _public prototype_ `void UnregisterCustomNavLinkObject(INavLinkCustomInterface& CustomNavLinkObject);` — Removes the provided interface from the list of registered custom navigation links. @param CustomNavLinkObject INavLinkCustomInterface of the object to unregister. @note Method will also assert if interface can't be removed (i.e. not registered or already unregistered).
- L147 _public function_ `TConstArrayView<TWeakInterfacePtr<INavLinkCustomInterface>> GetCustomLinks() const` — Returns the list of registered custom navigation links. @return Const view on the list of all registered custom navigation links.
- L153 _public function_ `int32 GetNumRegisteredElements() const` — Returns the number of navigation elements registered in the repository
- L159 _public function_ `int32 GetNumRegisteredUObjects() const` — Returns the number of UObject registered in the repository for which a FNavigationElement has been created and registered.
- L165 _public function_ `int32 GetNumRegisteredCustomLinks() const` — Returns the number of UObjects implementing INavLinkCustomInterface registered in the repository
- L171 _public member_ `FOnNavigationElementRegistrationEvent OnNavigationElementAddedDelegate;` — Delegate executed when a navigation element is added in the repository.
- L174 _public member_ `FOnNavigationElementRegistrationEvent OnNavigationElementRemovedDelegate;` — Delegate executed when a navigation element is removed from the repository.
- L177 _public member_ `FOnCustomNavLinkObjectRegistrationEvent OnCustomNavLinkObjectRegistered;` — Delegate executed when a custom navigation link is registered with the repository.
- L180 _public member_ `FOnCustomNavLinkObjectRegistrationEvent OnCustomNavLinkObjectUnregistered;` — Delegate executed when a custom navigation link is unregistered with the repository.
- L183 _protected prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`
- L187 _private prototype_ `TSharedPtr<const FNavigationElement> RegisterNavRelevantObjectInternal(const INavRelevantInterface& NavRelevantInterface, const UObject& NavRelevantObject, ENotifyOnSuccess NotifyOnSuccess);`
- L190 _private member_ `TMap<FObjectKey, FNavigationElementHandle> ObjectsToHandleMap;` — For legacy object registration path (i.e., Actor/ActorComponent)
- L193 _private member_ `TMap<FNavigationElementHandle, TSharedPtr<FNavigationElement>> NavRelevantElements;` — List of registered navigation elements.
- L196 _private member_ `TArray<TWeakInterfacePtr<INavLinkCustomInterface>> CustomLinkObjects;` — List of registered custom navigation link objects.
- L199 _private prototype_ `UE_MT_DECLARE_TS_RW_ACCESS_DETECTOR(NavElementAccessDetector);` — Multi thread access detector used to validate accesses to the maps of registered UObjects and FNavigationElement
- L209 _public member_ `FOnNavRelevantObjectRegistrationEvent OnNavRelevantObjectRegistered;` — `UE_DEPRECATED(5.5, "Use OnNavigationElementAddedDelegate instead.")`
- L212 _public member_ `FOnNavRelevantObjectRegistrationEvent OnNavRelevantObjectUnregistered;` — `UE_DEPRECATED(5.5, "Use OnNavigationElementRemovedDelegate instead.")`

#### enum `UNavigationObjectRepository::ENotifyOnSuccess`  
`enum class ENotifyOnSuccess : uint8`  
_L33-37_
- desc: Specifies whether OnNavigationElementAddedDelegate must be broadcast on successful registration.
- L35 _public enumerator_ `No`
- L36 _public enumerator_ `Yes`

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_DELEGATE_OneParam(FOnNavRelevantObjectRegistrationEvent, INavRelevantInterface&);`
- L16 _prototype_ `DECLARE_DELEGATE_OneParam(FOnNavRelevantObjectRegistrationEvent, INavRelevantInterface&);` — `UE_DEPRECATED(5.5, "Use the overloaded version with FNavigationElement instead.")`
- L18 _delegate_ `DECLARE_DELEGATE_OneParam(FOnNavigationElementRegistrationEvent, const TSharedRef<const FNavigationElement>&);`
- L18 _prototype_ `DECLARE_DELEGATE_OneParam(FOnNavigationElementRegistrationEvent, const TSharedRef<const FNavigationElement>&);`
- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCustomNavLinkObjectRegistrationEvent, INavLinkCustomInterface&);`
- L19 _prototype_ `DECLARE_DELEGATE_OneParam(FOnCustomNavLinkObjectRegistrationEvent, INavLinkCustomInterface&);`

### `Source/Runtime/NavigationSystem/Public/AbstractNavData.h` (Public)


#### struct `FAbstractNavigationPath`  
`struct FAbstractNavigationPath : public FNavigationPath`  
_L20-27_
- inherits: `FNavigationPath`
- L22 _public typedef_ `typedef FNavigationPath Super;`
- L24 _public prototype_ `FAbstractNavigationPath();`
- L26 _public member_ `static const FNavPathType Type;`

#### class `FAbstractQueryFilter`  
`class FAbstractQueryFilter : public INavigationQueryFilterInterface`  
_L29-48_
- inherits: `INavigationQueryFilterInterface`
- L32 _public function_ `virtual void Reset() override`
- L33 _public function_ `virtual void SetAreaCost(uint8 AreaType, float Cost) override`
- L34 _public function_ `virtual void SetFixedAreaEnteringCost(uint8 AreaType, float Cost) override`
- L35 _public function_ `virtual void SetExcludedArea(uint8 AreaType) override`
- L36 _public function_ `virtual void SetAllAreaCosts(const float* CostArray, const int32 Count) override`
- L37 _public function_ `virtual void GetAllAreaCosts(float* CostArray, float* FixedCostArray, const int32 Count) const override`
- L38 _public function_ `virtual void SetBacktrackingEnabled(const bool bBacktracking) override`
- L39 _public function_ `virtual bool IsBacktrackingEnabled() const override`
- L40 _public function_ `virtual float GetHeuristicScale() const override`
- L41 _public function_ `virtual bool IsEqual(const INavigationQueryFilterInterface* Other) const override`
- L42 _public function_ `virtual void SetIncludeFlags(uint16 Flags) override`
- L43 _public function_ `virtual uint16 GetIncludeFlags() const override`
- L44 _public function_ `virtual void SetExcludeFlags(uint16 Flags) override`
- L45 _public function_ `virtual uint16 GetExcludeFlags() const override`
- L46 _public function_ `virtual FVector GetAdjustedEndLocation(const FVector& EndLocation) const override`
- L47 _public prototype_ `virtual INavigationQueryFilterInterface* CreateCopy() const override;`

#### class `AAbstractNavData`  
`class AAbstractNavData : public ANavigationData`  
_L51-92_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `ANavigationData`
- L56 _public prototype_ `AAbstractNavData(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L58 _public prototype_ `virtual void PostLoad() override;`
- L62 _public function_ `virtual bool SupportsExternalPackaging() const override`
- L67 _public function_ `virtual void BatchRaycast(TArray<FNavigationRaycastWork>& Workload, FSharedConstNavQueryFilter QueryFilter, const UObject* Querier = NULL) const override`
- L68 _public function_ `virtual bool FindMoveAlongSurface(const FNavLocation& StartLocation, const FVector& TargetPosition, FNavLocation& OutLocation, FSharedConstNavQueryFilter Filter = NULL, const UObject* Querier = NULL) const override`
- L69 _public function_ `virtual void BatchFindMoveAlongSurface(TArray<FNavigationFindMoveAlongSurfaceWork>& Workload, FSharedConstNavQueryFilter Filter = NULL, const UObject* Querier = NULL) const override`
- L70 _public function_ `virtual bool FindOverlappingEdges(const FNavLocation& StartLocation, TConstArrayView<FVector> ConvexPolygon, TArray<FVector>& OutEdges, FSharedConstNavQueryFilter Filter = NULL, const UObject* Querier = NULL) const override`
- L71 _public function_ `virtual bool GetPathSegmentBoundaryEdges(const FNavigationPath& Path, const FNavPathPoint& StartPoint, const FNavPathPoint& EndPoint, const TConstArrayView<FVector> SearchArea, TArray<FVector>& OutEdges, const float MaxAreaEnterCost, FSharedConstNavQueryFilter Filter = NULL, const UObject* Querier = NULL) const override`
- L72 _public function_ `virtual FBox GetBounds() const override`
- L73 _public function_ `virtual FNavLocation GetRandomPoint(FSharedConstNavQueryFilter Filter = NULL, const UObject* Querier = NULL) const override`
- L74 _public function_ `virtual bool GetRandomReachablePointInRadius(const FVector& Origin, float Radius, FNavLocation& OutResult, FSharedConstNavQueryFilter Filter = NULL, const UObject* Querier = NULL) const override`
- L75 _public function_ `virtual bool GetRandomPointInNavigableRadius(const FVector& Origin, float Radius, FNavLocation& OutResult, FSharedConstNavQueryFilter Filter = NULL, const UObject* Querier = NULL) const override`
- L76 _public function_ `virtual bool ProjectPoint(const FVector& Point, FNavLocation& OutLocation, const FVector& Extent, FSharedConstNavQueryFilter Filter = NULL, const UObject* Querier = NULL) const override`
- L77 _public function_ `virtual void BatchProjectPoints(TArray<FNavigationProjectionWork>& Workload, const FVector& Extent, FSharedConstNavQueryFilter Filter = NULL, const UObject* Querier = NULL) const override`
- L78 _public function_ `virtual void BatchProjectPoints(TArray<FNavigationProjectionWork>& Workload, FSharedConstNavQueryFilter Filter = NULL, const UObject* Querier = NULL) const override`
- L79 _public function_ `virtual ENavigationQueryResult::Type CalcPathCost(const FVector& PathStart, const FVector& PathEnd, FVector::FReal& OutPathCost, FSharedConstNavQueryFilter QueryFilter = NULL, const UObject* Querier = NULL) const override`
- L80 _public function_ `virtual ENavigationQueryResult::Type CalcPathLength(const FVector& PathStart, const FVector& PathEnd, FVector::FReal& OutPathLength, FSharedConstNavQueryFilter QueryFilter = NULL, const UObject* Querier = NULL) const override`
- L81 _public function_ `virtual ENavigationQueryResult::Type CalcPathLengthAndCost(const FVector& PathStart, const FVector& PathEnd, FVector::FReal& OutPathLength, FVector::FReal& OutPathCost, FSharedConstNavQueryFilter QueryFilter = NULL, const UObject* Querier = NULL) const override`
- L82 _public function_ `virtual bool DoesNodeContainLocation(NavNodeRef NodeRef, const FVector& WorldSpaceLocation) const override`
- L83 _public function_ `virtual void OnNavAreaAdded(const UClass* NavAreaClass, int32 AgentIndex) override`
- L84 _public function_ `virtual void OnNavAreaRemoved(const UClass* NavAreaClass) override`
- L85 _public function_ `virtual bool IsNodeRefValid(NavNodeRef NodeRef) const override`
- L88 _public prototype_ `static FPathFindingResult FindPathAbstract(const FNavAgentProperties& AgentProperties, const FPathFindingQuery& Query);`
- L89 _public prototype_ `static bool TestPathAbstract(const FNavAgentProperties& AgentProperties, const FPathFindingQuery& Query, int32* NumVisitedNodes);`
- L90 _public prototype_ `static bool RaycastAbstract(const ANavigationData* NavDataInstance, const FVector& RayStart, const FVector& RayEnd, FVector& HitLocation, FSharedConstNavQueryFilter QueryFilter, const UObject* Querier);`
- L91 _public prototype_ `static bool RaycastAbstract(const ANavigationData* NavDataInstance, const FVector& RayStart, const FVector& RayEnd, FVector& HitLocation, FNavigationRaycastAdditionalResults* AdditionalResults, FSharedConstNavQueryFilter QueryFilter, const UObject* Querier);`

### `Source/Runtime/NavigationSystem/Public/BaseGeneratedNavLinksProxy.h` (Public)


#### class `UBaseGeneratedNavLinksProxy`  
`class UBaseGeneratedNavLinksProxy : public UObject, public INavLinkCustomInterface`  
_L17-38_
- reflection: `UCLASS(Blueprintable, MinimalAPI)`
- inherits: `UObject,INavLinkCustomInterface`
- desc: Experimental Base class used to create generated navlinks proxy. The proxy id is used to represent multiple links generated from the same configuration.
- L22 _private prototype_ `virtual void GetLinkData(FVector& LeftPt, FVector& RightPt, ENavLinkDirection::Type& Direction) const override;` — BEGIN INavLinkCustomInterface
- L23 _private prototype_ `virtual FNavLinkId GetId() const override;`
- L24 _private prototype_ `virtual void UpdateLinkId(FNavLinkId ProxyId) override;`
- L25 _private prototype_ `virtual UObject* GetLinkOwner() const override;`
- L28 _private function_ `void SetOwner(UObject* NewOwner)`
- L33 _protected member_ `FNavLinkId LinkProxyId;` — `UPROPERTY(Transient)` — The LinkID will be the same for all navlinks using the proxy.
- L37 _protected member_ `TObjectPtr<UObject> Owner = nullptr;` — `UPROPERTY(Transient)` — Proxy owner.

### `Source/Runtime/NavigationSystem/Public/CrowdManagerBase.h` (Public)


#### class `UCrowdManagerBase`  
`class UCrowdManagerBase : public UObject`  
_L13-26_
- reflection: `UCLASS(Abstract, Transient, MinimalAPI)`
- inherits: `UObject`
- desc: Base class for Crowd Managers. If you want to create a custom crowd manager implement a class extending this one and set UNavigationSystemV1::CrowdManagerClass to point at your class
- L17 _public prototype_ `virtual void Tick(float DeltaTime) PURE_VIRTUAL(UCrowdManagerBase::Tick, );`
- L20 _public prototype_ `virtual void OnNavDataRegistered(ANavigationData& NavDataInstance) PURE_VIRTUAL(UCrowdManagerBase::OnNavDataRegistered, );` — Called by the nav system when a new navigation data instance is registered.
- L23 _public prototype_ `virtual void OnNavDataUnregistered(ANavigationData& NavDataInstance) PURE_VIRTUAL(UCrowdManagerBase::OnNavDataUnregistered, );` — Called by the nav system when a navigation data instance is removed.
- L25 _public prototype_ `virtual void CleanUp(float DeltaTime) PURE_VIRTUAL(UCrowdManagerBase::CleanUp, );`

### `Source/Runtime/NavigationSystem/Public/NavAreas/NavArea.h` (Public)


#### class `UNavArea`  
`class UNavArea : public UNavAreaBase`  
_L14-116_
- reflection: `UCLASS(DefaultToInstanced, abstract, Config=Engine, Blueprintable, MinimalAPI)`
- inherits: `UNavAreaBase`
- desc: Class containing definition of a navigation area
- L21 _public member_ `float DefaultCost;` — `UPROPERTY(EditAnywhere, Category=NavArea, config, meta=(ClampMin = "0.0"))` — travel cost multiplier for path distance
- L26 _protected member_ `float FixedAreaEnteringCost;` — `UPROPERTY(EditAnywhere, Category=NavArea, config, meta=(ClampMin = "0.0"))` — entering cost
- L31 _public member_ `FColor DrawColor;` — `UPROPERTY(EditAnywhere, Category=NavArea, config)` — area color in navigation view
- L35 _public member_ `FNavAgentSelector SupportedAgents;` — `UPROPERTY(EditAnywhere, Category=NavArea, config)` — restrict area only to specified agents
- L82 _public prototype_ `UNavArea(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L84 _public prototype_ `virtual void FinishDestroy() override;`
- L85 _public prototype_ `virtual void PostLoad() override;`
- L86 _public prototype_ `virtual void PostInitProperties() override;`
- L87 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L89 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);`
- L90 _public prototype_ `virtual void PostCDOCompiled(const FPostCDOCompiledContext& Context) override;`
- L93 _public function_ `inline uint16 GetAreaFlags() const`
- L94 _public function_ `inline bool HasFlags(uint16 InFlags) const`
- L96 _public function_ `inline bool IsSupportingAgent(int32 AgentIndex) const`
- L99 _public function_ `virtual void InitializeArea()` — called before adding to navigation system
- L102 _public function_ `virtual float GetFixedAreaEnteringCost()` — Get the fixed area entering cost.
- L105 _public prototype_ `static FColor GetColor(UClass* AreaDefinitionClass);` — Retrieved color declared for AreaDefinitionClass
- L108 _public prototype_ `virtual void CopyFrom(TSubclassOf<UNavArea> AreaClass);` — copy properties from other area
- L113 _protected member_ `uint16 AreaFlags;` — these flags will be applied to navigation data along with AreaID
- L115 _protected prototype_ `void RegisterArea();`

#### union `UNavArea::(anonymous)`  
``  
_L40-79_

#### struct `UNavArea::__anonb996300f010a::(anonymous)`  
``  
_L42-77_

#### Free symbols / members of external scopes

- L45 _member_ `uint32 bSupportsAgent0 : 1;` (scope `UNavArea::__anonb996300f010a::__anonb996300f0208`) — `UPROPERTY(config)`
- L47 _member_ `uint32 bSupportsAgent1 : 1;` (scope `UNavArea::__anonb996300f010a::__anonb996300f0208`) — `UPROPERTY(config)`
- L49 _member_ `uint32 bSupportsAgent2 : 1;` (scope `UNavArea::__anonb996300f010a::__anonb996300f0208`) — `UPROPERTY(config)`
- L51 _member_ `uint32 bSupportsAgent3 : 1;` (scope `UNavArea::__anonb996300f010a::__anonb996300f0208`) — `UPROPERTY(config)`
- L53 _member_ `uint32 bSupportsAgent4 : 1;` (scope `UNavArea::__anonb996300f010a::__anonb996300f0208`) — `UPROPERTY(config)`
- L55 _member_ `uint32 bSupportsAgent5 : 1;` (scope `UNavArea::__anonb996300f010a::__anonb996300f0208`) — `UPROPERTY(config)`
- L57 _member_ `uint32 bSupportsAgent6 : 1;` (scope `UNavArea::__anonb996300f010a::__anonb996300f0208`) — `UPROPERTY(config)`
- L59 _member_ `uint32 bSupportsAgent7 : 1;` (scope `UNavArea::__anonb996300f010a::__anonb996300f0208`) — `UPROPERTY(config)`
- L61 _member_ `uint32 bSupportsAgent8 : 1;` (scope `UNavArea::__anonb996300f010a::__anonb996300f0208`) — `UPROPERTY(config)`
- L63 _member_ `uint32 bSupportsAgent9 : 1;` (scope `UNavArea::__anonb996300f010a::__anonb996300f0208`) — `UPROPERTY(config)`
- L65 _member_ `uint32 bSupportsAgent10 : 1;` (scope `UNavArea::__anonb996300f010a::__anonb996300f0208`) — `UPROPERTY(config)`
- L67 _member_ `uint32 bSupportsAgent11 : 1;` (scope `UNavArea::__anonb996300f010a::__anonb996300f0208`) — `UPROPERTY(config)`
- L69 _member_ `uint32 bSupportsAgent12 : 1;` (scope `UNavArea::__anonb996300f010a::__anonb996300f0208`) — `UPROPERTY(config)`
- L71 _member_ `uint32 bSupportsAgent13 : 1;` (scope `UNavArea::__anonb996300f010a::__anonb996300f0208`) — `UPROPERTY(config)`
- L73 _member_ `uint32 bSupportsAgent14 : 1;` (scope `UNavArea::__anonb996300f010a::__anonb996300f0208`) — `UPROPERTY(config)`
- L75 _member_ `uint32 bSupportsAgent15 : 1;` (scope `UNavArea::__anonb996300f010a::__anonb996300f0208`) — `UPROPERTY(config)`
- L78 _member_ `uint32 SupportedAgentsBits;` (scope `UNavArea::__anonb996300f010a`)

### `Source/Runtime/NavigationSystem/Public/NavAreas/NavAreaMeta.h` (Public)


#### class `UNavAreaMeta`  
`class UNavAreaMeta : public UNavArea`  
_L19-25_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UNavArea`
- desc: A convenience class for an area that has IsMetaArea() == true. Do not use this class when determining whether an area class is "meta". Call IsMetaArea instead.
- L24 _public prototype_ `UNavAreaMeta(const FObjectInitializer& ObjectInitializer);`

### `Source/Runtime/NavigationSystem/Public/NavAreas/NavAreaMeta_SwitchByAgent.h` (Public)


#### class `UNavAreaMeta_SwitchByAgent`  
`class UNavAreaMeta_SwitchByAgent : public UNavAreaMeta`  
_L14-74_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UNavAreaMeta`
- desc: Class containing definition of a navigation area
- L19 _private member_ `TSubclassOf<UNavArea> Agent0Area;` — `UPROPERTY(EditAnywhere, Category=AgentTypes)`
- L22 _private member_ `TSubclassOf<UNavArea> Agent1Area;` — `UPROPERTY(EditAnywhere, Category=AgentTypes)`
- L25 _private member_ `TSubclassOf<UNavArea> Agent2Area;` — `UPROPERTY(EditAnywhere, Category=AgentTypes)`
- L28 _private member_ `TSubclassOf<UNavArea> Agent3Area;` — `UPROPERTY(EditAnywhere, Category=AgentTypes)`
- L31 _private member_ `TSubclassOf<UNavArea> Agent4Area;` — `UPROPERTY(EditAnywhere, Category=AgentTypes)`
- L34 _private member_ `TSubclassOf<UNavArea> Agent5Area;` — `UPROPERTY(EditAnywhere, Category=AgentTypes)`
- L37 _private member_ `TSubclassOf<UNavArea> Agent6Area;` — `UPROPERTY(EditAnywhere, Category=AgentTypes)`
- L40 _private member_ `TSubclassOf<UNavArea> Agent7Area;` — `UPROPERTY(EditAnywhere, Category=AgentTypes)`
- L43 _private member_ `TSubclassOf<UNavArea> Agent8Area;` — `UPROPERTY(EditAnywhere, Category=AgentTypes)`
- L46 _private member_ `TSubclassOf<UNavArea> Agent9Area;` — `UPROPERTY(EditAnywhere, Category=AgentTypes)`
- L49 _private member_ `TSubclassOf<UNavArea> Agent10Area;` — `UPROPERTY(EditAnywhere, Category=AgentTypes)`
- L52 _private member_ `TSubclassOf<UNavArea> Agent11Area;` — `UPROPERTY(EditAnywhere, Category=AgentTypes)`
- L55 _private member_ `TSubclassOf<UNavArea> Agent12Area;` — `UPROPERTY(EditAnywhere, Category=AgentTypes)`
- L58 _private member_ `TSubclassOf<UNavArea> Agent13Area;` — `UPROPERTY(EditAnywhere, Category=AgentTypes)`
- L61 _private member_ `TSubclassOf<UNavArea> Agent14Area;` — `UPROPERTY(EditAnywhere, Category=AgentTypes)`
- L64 _private member_ `TSubclassOf<UNavArea> Agent15Area;` — `UPROPERTY(EditAnywhere, Category=AgentTypes)`
- L66 _private prototype_ `virtual TSubclassOf<UNavAreaBase> PickAreaClassForAgent(const AActor& Actor, const FNavAgentProperties& NavAgent) const override;`
- L70 _private prototype_ `virtual void UpdateAgentConfig();` — setup AgentXArea properties
- L72 _private member_ `static bool bUpdateAgentConfigCallbackRegistered;`

### `Source/Runtime/NavigationSystem/Public/NavAreas/NavArea_Default.h` (Public)


#### class `UNavArea_Default`  
`class UNavArea_Default : public UNavArea`  
_L15-18_
- reflection: `UCLASS(Config=Engine, MinimalAPI)`
- inherits: `UNavArea`
- desc: Regular navigation area, applied to entire navigation data by default

### `Source/Runtime/NavigationSystem/Public/NavAreas/NavArea_LowHeight.h` (Public)


#### class `UNavArea_LowHeight`  
`class UNavArea_LowHeight : public UNavArea`  
_L17-22_
- reflection: `UCLASS(Config = Engine, MinimalAPI)`
- inherits: `UNavArea`
- desc: Special area that can be generated in spaces with insufficient free height above. Cannot be traversed by anyone.
- L21 _public function_ `virtual bool IsLowArea() const override`

### `Source/Runtime/NavigationSystem/Public/NavAreas/NavArea_Null.h` (Public)


#### class `UNavArea_Null`  
`class UNavArea_Null : public UNavArea`  
_L15-18_
- reflection: `UCLASS(Config=Engine, MinimalAPI)`
- inherits: `UNavArea`
- desc: In general represents an empty area, that cannot be traversed by anyone. Ever.

### `Source/Runtime/NavigationSystem/Public/NavAreas/NavArea_Obstacle.h` (Public)


#### class `UNavArea_Obstacle`  
`class UNavArea_Obstacle : public UNavArea`  
_L15-18_
- reflection: `UCLASS(Config = Engine, MinimalAPI)`
- inherits: `UNavArea`
- desc: In general represents a high cost area, that shouldn't be traversed by anyone unless no other path exist.

### `Source/Runtime/NavigationSystem/Public/NavCollision.h` (Public)


#### struct `FNavCollisionCylinder`  
`struct FNavCollisionCylinder`  
_L19-31_
- reflection: `USTRUCT()`
- L24 _public member_ `FVector Offset = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category=Cylinder)`
- L27 _public member_ `float Radius = 0.f;` — `UPROPERTY(EditAnywhere, Category=Cylinder)`
- L30 _public member_ `float Height = 0.f;` — `UPROPERTY(EditAnywhere, Category=Cylinder)`

#### struct `FNavCollisionBox`  
`struct FNavCollisionBox`  
_L34-43_
- reflection: `USTRUCT()`
- L39 _public member_ `FVector Offset = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category=Box)`
- L42 _public member_ `FVector Extent = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category=Box)`

#### class `UNavCollision`  
`class UNavCollision : public UNavCollisionBase`  
_L46-147_
- reflection: `UCLASS(config=Engine, MinimalAPI)`
- inherits: `UNavCollisionBase`
- L50 _private member_ `TNavStatArray<int32> ConvexShapeIndices;`
- L52 _private member_ `FBox Bounds;`
- L56 _private member_ `TArray<FNavCollisionCylinder> CylinderCollision;` — `UPROPERTY(EditAnywhere, Category=Navigation)` — list of nav collision cylinders
- L60 _private member_ `TArray<FNavCollisionBox> BoxCollision;` — `UPROPERTY(EditAnywhere, Category=Navigation)` — list of nav collision boxes
- L79 _private member_ `TSubclassOf<class UNavArea> AreaClass;` — `UPROPERTY(EditAnywhere, Category = Navigation, meta = (EditCondition = "bIsDynamicObstacle || bUseSurfaceArea"))` — Navigation area type for this mesh's collision geometry. Area usages (mutually exclusive): 1) Dynamic Obstacles - GetNavigationModifier() creates convex area modifiers with AreaClass - These paint obstacle volumes into the navmesh during generation - Used for dynamic obstacles that can move/appear/disappear at runtime - Area class applied via nav modifier system 2) Surface Area - GetNavigationModifier() adds a FAreaNavModifier - AreaClass flows to FRecastRawGeometryElement during collision export - Applied during triangle rasterization - Area class applied during voxelization, not as post-process modifier
- L83 _private member_ `uint32 bGatherConvexGeometry : 1;` — `UPROPERTY(EditAnywhere, Category=Navigation, config)` — If set, convex collisions will be exported offline for faster runtime navmesh building (increases memory usage)
- L87 _private member_ `uint32 bCreateOnClient : 1;` — `UPROPERTY(EditAnywhere, Category=Navigation, config)` — If false, will not create nav collision when connecting as a client
- L90 _private member_ `uint32 bForceGeometryRebuild : 1;` — if set, convex geometry will be rebuilt instead of using cooked data
- L93 _private member_ `FGuid BodySetupGuid;` — Guid of associated BodySetup
- L96 _private member_ `FFormatContainer CookedFormatData;` — Cooked data for each format
- L99 _private prototype_ `virtual void PostInitProperties() override;`
- L100 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L101 _private prototype_ `virtual void PostLoad() override;`
- L102 _private prototype_ `virtual void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize) override;`
- L104 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L106 _private prototype_ `virtual bool NeedsLoadForTargetPlatform(const class ITargetPlatform* TargetPlatform) const override;`
- L107 _private function_ `virtual bool NeedsLoadForClient() const override`
- L110 _private prototype_ `FGuid GetGuid() const;`
- L114 _private prototype_ `virtual void Setup(class UBodySetup* BodySetup) override;` — Tries to read data from DDC, and if that fails gathers navigation collision data, stores it and uploads to DDC
- L116 _private prototype_ `virtual FBox GetBounds() const override;`
- L119 _private prototype_ `void CopyUserSettings(const UNavCollision& OtherData);` — copy user settings from other nav collision data
- L122 _private prototype_ `virtual void DrawSimpleGeom(FPrimitiveDrawInterface* PDI, const FTransform& Transform, const FColor Color) override;` — show cylinder and box collisions
- L125 _private prototype_ `virtual void GetNavigationModifier(FCompositeNavModifier& Modifier, const FTransform& LocalToWorld) override;` — Get data for dynamic obstacle and collisions with surface navarea.
- L128 _private prototype_ `virtual bool HasSurfaceAreaClass() const override;` — Returns true if this collision has a surface area class set for collision triangles.
- L131 _private prototype_ `virtual bool ExportGeometry(const FTransform& LocalToWorld, FNavigableGeometryExport& GeoExport) const override;` — Export collision data
- L134 _private prototype_ `void GatherCollision();` — Read collisions data
- L137 _private prototype_ `virtual void InvalidateCollision() override;`
- L141 _protected prototype_ `void ClearCollision();`
- L144 _protected prototype_ `void InvalidatePhysicsData();`
- L146 _protected prototype_ `FByteBulkData* GetCookedData(FName Format);`

### `Source/Runtime/NavigationSystem/Public/NavDebugTypes.h` (Public)


#### Free symbols / members of external scopes

- L11 _typedef_ `typedef FDebugRenderSceneProxy::FMesh FNavDebugMeshData;`

### `Source/Runtime/NavigationSystem/Public/NavFilters/NavigationQueryFilter.h` (Public)


#### struct `FNavigationFilterArea`  
`struct FNavigationFilterArea`  
_L15-46_
- reflection: `USTRUCT()`
- L21 _public member_ `TSubclassOf<UNavArea> AreaClass;` — `UPROPERTY(EditAnywhere, Category=Area)` — navigation area class
- L25 _public member_ `float TravelCostOverride;` — `UPROPERTY(EditAnywhere, Category=Area, meta=(EditCondition="bOverrideTravelCost",ClampMin=0.001))` — override for travel cost
- L29 _public member_ `float EnteringCostOverride;` — `UPROPERTY(EditAnywhere, Category=Area, meta=(EditCondition="bOverrideEnteringCost",ClampMin=0))` — override for entering cost
- L33 _public member_ `uint32 bIsExcluded : 1;` — `UPROPERTY(EditAnywhere, Category=Area)` — mark as excluded
- L36 _public member_ `uint32 bOverrideTravelCost : 1;` — `UPROPERTY(EditAnywhere, Category=Area, meta=(InlineEditConditionToggle))`
- L39 _public member_ `uint32 bOverrideEnteringCost : 1;` — `UPROPERTY(EditAnywhere, Category=Area, meta=(InlineEditConditionToggle))`
- L41 _public function_ `FNavigationFilterArea()`

#### struct `FNavigationFilterFlags`  
`struct FNavigationFilterFlags`  
_L52-99_
- reflection: `USTRUCT()`
- desc: Use UNavigationSystemV1.DescribeFilterFlags() to setup user friendly names of flags

#### union `FNavigationFilterFlags::(anonymous)`  
``  
_L58-97_

#### struct `FNavigationFilterFlags::__anondd5ccb8a010a::(anonymous)`  
``  
_L60-95_

#### class `UNavigationQueryFilter`  
`class UNavigationQueryFilter : public UObject`  
_L103-156_
- reflection: `UCLASS(Abstract, Blueprintable, MinimalAPI)`
- inherits: `UObject`
- desc: Class containing definition of a navigation query filter
- L109 _private member_ `TArray<FNavigationFilterArea> Areas;` — `UPROPERTY(EditAnywhere, Category=Filter, meta = (TitleProperty = "AreaClass"))` — list of overrides for navigation areas
- L113 _private member_ `FNavigationFilterFlags IncludeFlags;` — `UPROPERTY(EditAnywhere, Category=Filter)` — required flags of navigation nodes
- L117 _private member_ `FNavigationFilterFlags ExcludeFlags;` — `UPROPERTY(EditAnywhere, Category=Filter)` — forbidden flags of navigation nodes
- L120 _private prototype_ `FSharedConstNavQueryFilter GetQueryFilter(const ANavigationData& NavData, const UObject* Querier) const;` — get filter for given navigation data and initialize on first access
- L123 _private prototype_ `static FSharedConstNavQueryFilter GetQueryFilter(const ANavigationData& NavData, TSubclassOf<UNavigationQueryFilter> FilterClass);` — helper functions for accessing filter
- L124 _private prototype_ `static FSharedConstNavQueryFilter GetQueryFilter(const ANavigationData& NavData, const UObject* Querier, TSubclassOf<UNavigationQueryFilter> FilterClass);`
- L127 _private function_ `template<class T> static FSharedConstNavQueryFilter GetQueryFilter(const ANavigationData& NavData, TSubclassOf<UNavigationQueryFilter> FilterClass = T::StaticClass())`
- L133 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L139 _protected member_ `uint32 bInstantiateForQuerier : 1;` — if set, filter will not be cached by navigation data and can be configured per Querier
- L142 _protected member_ `uint32 bIsMetaFilter : 1;` — if set to true GetSimpleFilterForAgent will be called when determining the actual filter class to be used
- L145 _protected prototype_ `void AddTravelCostOverride(TSubclassOf<UNavArea> AreaClass, float TravelCost);` — helper functions for adding area overrides
- L146 _protected prototype_ `void AddEnteringCostOverride(TSubclassOf<UNavArea> AreaClass, float EnteringCost);`
- L147 _protected prototype_ `void AddExcludedArea(TSubclassOf<UNavArea> AreaClass);`
- L150 _protected prototype_ `int32 FindAreaOverride(TSubclassOf<UNavArea> AreaClass) const;` — find index of area data
- L153 _protected prototype_ `virtual void InitializeFilter(const ANavigationData& NavData, const UObject* Querier, FNavigationQueryFilter& Filter) const;` — setup filter for given navigation data, use to create custom filters
- L155 _protected function_ `virtual TSubclassOf<UNavigationQueryFilter> GetSimpleFilterForAgent(const UObject& Querier) const`

#### Free symbols / members of external scopes

- L63 _member_ `uint32 bNavFlag0 : 1;` (scope `FNavigationFilterFlags::__anondd5ccb8a010a::__anondd5ccb8a0208`) — `UPROPERTY(EditAnywhere, Category=Flags)`
- L65 _member_ `uint32 bNavFlag1 : 1;` (scope `FNavigationFilterFlags::__anondd5ccb8a010a::__anondd5ccb8a0208`) — `UPROPERTY(EditAnywhere, Category=Flags)`
- L67 _member_ `uint32 bNavFlag2 : 1;` (scope `FNavigationFilterFlags::__anondd5ccb8a010a::__anondd5ccb8a0208`) — `UPROPERTY(EditAnywhere, Category=Flags)`
- L69 _member_ `uint32 bNavFlag3 : 1;` (scope `FNavigationFilterFlags::__anondd5ccb8a010a::__anondd5ccb8a0208`) — `UPROPERTY(EditAnywhere, Category=Flags)`
- L71 _member_ `uint32 bNavFlag4 : 1;` (scope `FNavigationFilterFlags::__anondd5ccb8a010a::__anondd5ccb8a0208`) — `UPROPERTY(EditAnywhere, Category=Flags)`
- L73 _member_ `uint32 bNavFlag5 : 1;` (scope `FNavigationFilterFlags::__anondd5ccb8a010a::__anondd5ccb8a0208`) — `UPROPERTY(EditAnywhere, Category=Flags)`
- L75 _member_ `uint32 bNavFlag6 : 1;` (scope `FNavigationFilterFlags::__anondd5ccb8a010a::__anondd5ccb8a0208`) — `UPROPERTY(EditAnywhere, Category=Flags)`
- L77 _member_ `uint32 bNavFlag7 : 1;` (scope `FNavigationFilterFlags::__anondd5ccb8a010a::__anondd5ccb8a0208`) — `UPROPERTY(EditAnywhere, Category=Flags)`
- L79 _member_ `uint32 bNavFlag8 : 1;` (scope `FNavigationFilterFlags::__anondd5ccb8a010a::__anondd5ccb8a0208`) — `UPROPERTY(EditAnywhere, Category=Flags)`
- L81 _member_ `uint32 bNavFlag9 : 1;` (scope `FNavigationFilterFlags::__anondd5ccb8a010a::__anondd5ccb8a0208`) — `UPROPERTY(EditAnywhere, Category=Flags)`
- L83 _member_ `uint32 bNavFlag10 : 1;` (scope `FNavigationFilterFlags::__anondd5ccb8a010a::__anondd5ccb8a0208`) — `UPROPERTY(EditAnywhere, Category=Flags)`
- L85 _member_ `uint32 bNavFlag11 : 1;` (scope `FNavigationFilterFlags::__anondd5ccb8a010a::__anondd5ccb8a0208`) — `UPROPERTY(EditAnywhere, Category=Flags)`
- L87 _member_ `uint32 bNavFlag12 : 1;` (scope `FNavigationFilterFlags::__anondd5ccb8a010a::__anondd5ccb8a0208`) — `UPROPERTY(EditAnywhere, Category=Flags)`
- L89 _member_ `uint32 bNavFlag13 : 1;` (scope `FNavigationFilterFlags::__anondd5ccb8a010a::__anondd5ccb8a0208`) — `UPROPERTY(EditAnywhere, Category=Flags)`
- L91 _member_ `uint32 bNavFlag14 : 1;` (scope `FNavigationFilterFlags::__anondd5ccb8a010a::__anondd5ccb8a0208`) — `UPROPERTY(EditAnywhere, Category=Flags)`
- L93 _member_ `uint32 bNavFlag15 : 1;` (scope `FNavigationFilterFlags::__anondd5ccb8a010a::__anondd5ccb8a0208`) — `UPROPERTY(EditAnywhere, Category=Flags)`
- L96 _member_ `uint16 Packed = 0;` (scope `FNavigationFilterFlags::__anondd5ccb8a010a`)

### `Source/Runtime/NavigationSystem/Public/NavFilters/RecastFilter_UseDefaultArea.h` (Public)


#### class `URecastFilter_UseDefaultArea`  
`class URecastFilter_UseDefaultArea : public UNavigationQueryFilter`  
_L17-22_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UNavigationQueryFilter`
- desc: Regular navigation area, applied to entire navigation data by default
- L21 _private prototype_ `virtual void InitializeFilter(const ANavigationData& NavData, const UObject* Querier, FNavigationQueryFilter& Filter) const override;`

### `Source/Runtime/NavigationSystem/Public/NavGraph/NavigationGraph.h` (Public)


#### struct `FNavGraphEdge`  
`struct FNavGraphEdge`  
_L11-33_
- reflection: `USTRUCT()`
- L19 _public member_ `struct FNavGraphNode* Start;`
- L21 _public member_ `struct FNavGraphNode* End;`
- L23 _public member_ `int32 Flags : EgdeFlagsCount;`
- L24 _public member_ `uint32 bEnabled : 1;`
- L26 _public function_ `FNavGraphEdge() : Start(NULL) , End(NULL) , Flags(0) , bEnabled(false)`

#### enum `FNavGraphEdge::(anonymous)`  
`enum`  
_L15-17_

#### struct `FNavGraphNode`  
`struct FNavGraphNode`  
_L37-54_
- reflection: `USTRUCT()`
- L43 _public member_ `TObjectPtr<UObject> Owner;` — `UPROPERTY()` — Who's this node referring to? This will most commonly point to an actor or a component
- L49 _public member_ `TArray<FNavGraphEdge> Edges;`
- L53 _public prototype_ `FNavGraphNode();`

#### enum `FNavGraphNode::(anonymous)`  
`enum`  
_L45-47_

#### class `ANavigationGraph`  
`class ANavigationGraph : public ANavigationData`  
_L58-63_
- reflection: `UCLASS(config=Engine, MinimalAPI, abstract)`
- inherits: `ANavigationData`
- desc: currently abstract since it's not full implemented

#### Free symbols / members of external scopes

- L16 _enumerator_ `EgdeFlagsCount = 7` (scope `FNavGraphEdge::__anone99ceef90103`)
- L46 _enumerator_ `InitialEdgesCount = 4` (scope `FNavGraphNode::__anone99ceef90203`)

### `Source/Runtime/NavigationSystem/Public/NavGraph/NavigationGraphNode.h` (Public)


#### class `ANavigationGraphNode`  
`class ANavigationGraphNode : public AActor`  
_L11-14_
- reflection: `UCLASS(config=Engine, MinimalAPI, NotBlueprintable, abstract)`
- inherits: `AActor`

### `Source/Runtime/NavigationSystem/Public/NavGraph/NavigationGraphNodeComponent.h` (Public)


#### class `UNavigationGraphNodeComponent`  
`class UNavigationGraphNodeComponent : public USceneComponent`  
_L11-26_
- reflection: `UCLASS(config=Engine, MinimalAPI, HideCategories=(Mobility))`
- inherits: `USceneComponent`
- L16 _private member_ `FNavGraphNode Node;` — `UPROPERTY()`
- L19 _private member_ `TObjectPtr<UNavigationGraphNodeComponent> NextNodeComponent;` — `UPROPERTY()`
- L22 _private member_ `TObjectPtr<UNavigationGraphNodeComponent> PrevNodeComponent;` — `UPROPERTY()`
- L25 _private prototype_ `virtual void BeginDestroy() override;`

### `Source/Runtime/NavigationSystem/Public/NavLinkComponent.h` (Public)


#### class `UNavLinkComponent`  
`class UNavLinkComponent : public UPrimitiveComponent, public INavLinkHostInterface`  
_L16-43_
- reflection: `UCLASS(ClassGroup = (Navigation), meta = (BlueprintSpawnableComponent), hidecategories = (Activation), MinimalAPI)`
- inherits: `UPrimitiveComponent,INavLinkHostInterface`
- L21 _private member_ `TArray<FNavigationLink> Links;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Navigation)`
- L23 _private prototype_ `virtual void GetNavigationData(FNavigationRelevantData& Data) const override;`
- L24 _private prototype_ `virtual bool IsNavigationRelevant() const override;`
- L26 _private function_ `virtual bool GetNavigationLinksClasses(TArray<TSubclassOf<class UNavLinkDefinition> >& OutClasses) const override`
- L27 _private prototype_ `virtual bool GetNavigationLinksArray(TArray<FNavigationLink>& OutLink, TArray<FNavigationSegmentLink>& OutSegments) const override;`
- L29 _private prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform &LocalToWorld) const override;`
- L30 _private prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L31 _private function_ `virtual bool ShouldRecreateProxyOnUpdateTransform() const override`
- L34 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L35 _private prototype_ `virtual void PostEditUndo() override;`
- L36 _private prototype_ `virtual void PostEditImport() override;`
- L39 _private prototype_ `virtual void OnRegister() override;`
- L42 _protected prototype_ `void InitializeLinksAreaClasses();`

### `Source/Runtime/NavigationSystem/Public/NavLinkCustomComponent.h` (Public)


#### class `UNavLinkCustomComponent`  
`class UNavLinkCustomComponent : public UNavRelevantComponent, public INavLinkCustomInterface`  
_L28-253_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UNavRelevantComponent,INavLinkCustomInterface`
- L32 _private prototype_ `DECLARE_DELEGATE_ThreeParams(FOnMoveReachedLink, UNavLinkCustomComponent* , UObject* , const FVector& );`
- L33 _private prototype_ `DECLARE_DELEGATE_TwoParams(FBroadcastFilter, UNavLinkCustomComponent* , TArray<UObject*>& );`
- L36 _private prototype_ `virtual void GetLinkData(FVector& LeftPt, FVector& RightPt, ENavLinkDirection::Type& Direction) const override;` — BEGIN INavLinkCustomInterface
- L37 _private prototype_ `virtual void GetSupportedAgents(FNavAgentSelector& OutSupportedAgents) const override;`
- L38 _private prototype_ `virtual TSubclassOf<UNavArea> GetLinkAreaClass() const override;`
- L39 _private prototype_ `virtual FNavLinkAuxiliaryId GetAuxiliaryId() const override;`
- L40 _private prototype_ `virtual FNavLinkId GetId() const override;`
- L41 _private prototype_ `virtual void UpdateLinkId(FNavLinkId NewUniqueId) override;`
- L42 _private prototype_ `virtual bool IsLinkPathfindingAllowed(const UObject* Querier) const override;`
- L43 _private prototype_ `virtual bool OnLinkMoveStarted(UObject* PathComp, const FVector& DestPoint) override;`
- L44 _private prototype_ `virtual void OnLinkMoveFinished(UObject* PathComp) override;`
- L48 _private prototype_ `virtual void GetNavigationData(FNavigationRelevantData& Data) const override;`
- L49 _private prototype_ `virtual void CalcAndCacheBounds() const override;`
- L53 _private prototype_ `virtual void OnRegister() override;`
- L54 _private prototype_ `virtual void OnUnregister() override;`
- L55 _private prototype_ `virtual TStructOnScope<FActorComponentInstanceData> GetComponentInstanceData() const override;`
- L58 _private prototype_ `void ApplyComponentInstanceData(struct FNavLinkCustomInstanceData* ComponentInstanceData);`
- L61 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L62 _private prototype_ `virtual void PostLoad() override;`
- L64 _private prototype_ `virtual void PostEditImport() override;`
- L69 _private prototype_ `void SetLinkData(const FVector& RelativeStart, const FVector& RelativeEnd, ENavLinkDirection::Type Direction);` — set basic link data: end points and direction
- L70 _private prototype_ `virtual FNavigationLink GetLinkModifier() const;`
- L73 _private prototype_ `void SetEnabledArea(TSubclassOf<UNavArea> AreaClass);` — set area class to use when link is enabled
- L74 _private function_ `TSubclassOf<UNavArea> GetEnabledArea() const`
- L77 _private prototype_ `void SetDisabledArea(TSubclassOf<UNavArea> AreaClass);` — set area class to use when link is disabled
- L78 _private function_ `TSubclassOf<UNavArea> GetDisabledArea() const`
- L80 _private function_ `void SetSupportedAgents(const FNavAgentSelector& InSupportedAgents)`
- L81 _private function_ `FNavAgentSelector GetSupportedAgents() const`
- L85 _private prototype_ `void AddNavigationObstacle(TSubclassOf<UNavArea> AreaClass, const FVector& BoxExtent, const FVector& BoxOffset = FVector::ZeroVector);` — add box obstacle during generation of navigation data this can be used to create empty area under doors
- L88 _private prototype_ `void ClearNavigationObstacle();` — removes simple obstacle
- L91 _private prototype_ `void SetBroadcastData(float Radius, ECollisionChannel TraceChannel = ECC_Pawn, float Interval = 0.0f);` — set properties of trigger around link entry point(s), that will notify nearby agents about link state change
- L93 _private prototype_ `void SendBroadcastWhenEnabled(bool bEnabled);`
- L94 _private prototype_ `void SendBroadcastWhenDisabled(bool bEnabled);`
- L97 _private prototype_ `void SetBroadcastFilter(FBroadcastFilter const& InDelegate);` — set delegate to filter
- L100 _private prototype_ `void SetEnabled(bool bNewEnabled);` — change state of smart link (used area class)
- L101 _private function_ `bool IsEnabled() const`
- L104 _private prototype_ `void SetMoveReachedLink(FOnMoveReachedLink const& InDelegate);` — set delegate to notify about reaching this link during path following
- L107 _private prototype_ `bool HasMovingAgents() const;` — check is any agent is currently moving though this link
- L110 _private prototype_ `FVector GetStartPoint() const;` — get link start point in world space
- L113 _private prototype_ `FVector GetEndPoint() const;` — get link end point in world space
- L115 _private function_ `TSubclassOf<UNavArea> GetObstacleAreaClass() const`
- L121 _private function_ `template< class UserClass > inline void SetMoveReachedLink(UserClass* TargetOb, typename FOnMoveReachedLink::TMethodPtr< UserClass > InFunc)`
- L126 _private function_ `template< class UserClass > inline void SetMoveReachedLink(UserClass* TargetOb, typename FOnMoveReachedLink::TConstMethodPtr< UserClass > InFunc)`
- L132 _private function_ `template< class UserClass > inline void SetBroadcastFilter(UserClass* TargetOb, typename FBroadcastFilter::TMethodPtr< UserClass > InFunc)`
- L137 _private function_ `template< class UserClass > inline void SetBroadcastFilter(UserClass* TargetOb, typename FBroadcastFilter::TConstMethodPtr< UserClass > InFunc)`
- L144 _protected prototype_ `void OnNavAreaRegistered(const UWorld& World, const UClass* NavAreaClass);`
- L145 _protected prototype_ `void OnNavAreaUnregistered(const UWorld& World, const UClass* NavAreaClass);`
- L152 _protected member_ `uint32 NavLinkUserId;` — `UE_DEPRECATED(5.3, "LinkIds are now based on FNavLinkId. Use CustomLinkId instead. This Id is no longer used by the engine.")` — `UPROPERTY()`
- L156 _protected member_ `FNavLinkId CustomLinkId;` — `UPROPERTY()` — link Id assigned by navigation system
- L165 _protected member_ `FNavLinkAuxiliaryId AuxiliaryCustomLinkId;` — `UPROPERTY()` — Assigned in the constructor. This uniquely identifies a component in an Actor, but will not be unique between duplicate level instances. containing the same Actor. This is Hashed with the Actor Instance FGuid to create the CustomLinkId so that Actors with more than one UNavLinkCustomComponent can have a completely unique ID per UNavLinkCustomComponent even across level instances.
- L169 _protected member_ `TSubclassOf<UNavArea> EnabledAreaClass;` — `UPROPERTY(EditAnywhere, Category=SmartLink)` — area class to use when link is enabled
- L173 _protected member_ `TSubclassOf<UNavArea> DisabledAreaClass;` — `UPROPERTY(EditAnywhere, Category=SmartLink)` — area class to use when link is disabled
- L177 _protected member_ `FNavAgentSelector SupportedAgents;` — `UPROPERTY(EditAnywhere, Category=SmartLink)` — restrict area only to specified agents
- L181 _protected member_ `FVector LinkRelativeStart;` — `UPROPERTY(EditAnywhere, Category=SmartLink)` — start point, relative to owner
- L185 _protected member_ `FVector LinkRelativeEnd;` — `UPROPERTY(EditAnywhere, Category=SmartLink)` — end point, relative to owner
- L189 _protected member_ `TEnumAsByte<ENavLinkDirection::Type> LinkDirection;` — `UPROPERTY(EditAnywhere, Category=SmartLink)` — direction of link
- L193 _protected member_ `uint32 bLinkEnabled : 1;` — `UPROPERTY(EditAnywhere, Category=SmartLink)` — is link currently in enabled state? (area class)
- L197 _protected member_ `uint32 bNotifyWhenEnabled : 1;` — `UPROPERTY(EditAnywhere, Category=Broadcast)` — should link notify nearby agents when it changes state to enabled
- L201 _protected member_ `uint32 bNotifyWhenDisabled : 1;` — `UPROPERTY(EditAnywhere, Category=Broadcast)` — should link notify nearby agents when it changes state to disabled
- L205 _protected member_ `uint32 bCreateBoxObstacle : 1;` — `UPROPERTY(EditAnywhere, Category=Obstacle)` — if set, box obstacle area will be added to generation
- L209 _protected member_ `FVector ObstacleOffset;` — `UPROPERTY(EditAnywhere, Category=Obstacle)` — offset of simple box obstacle
- L213 _protected member_ `FVector ObstacleExtent;` — `UPROPERTY(EditAnywhere, Category=Obstacle)` — extent of simple box obstacle
- L217 _protected member_ `TSubclassOf<UNavArea> ObstacleAreaClass;` — `UPROPERTY(EditAnywhere, Category=Obstacle)` — area class for simple box obstacle
- L221 _protected member_ `float BroadcastRadius;` — `UPROPERTY(EditAnywhere, Category=Broadcast)` — radius of state change broadcast
- L225 _protected member_ `float BroadcastInterval;` — `UPROPERTY(EditAnywhere, Category=Broadcast, Meta=(UIMin="0.0", ClampMin="0.0"))` — interval for state change broadcast (0 = single broadcast)
- L229 _protected member_ `TEnumAsByte<ECollisionChannel> BroadcastChannel;` — `UPROPERTY(EditAnywhere, Category=Broadcast)` — trace channel for state change broadcast
- L232 _protected member_ `FBroadcastFilter OnBroadcastFilter;` — delegate to call when link is reached
- L235 _protected member_ `TArray<TWeakObjectPtr<UObject> > MovingAgents;` — list of agents moving though this link
- L238 _protected member_ `FOnMoveReachedLink OnMoveReachedLink;` — delegate to call when link is reached
- L241 _protected member_ `FTimerHandle TimerHandle_BroadcastStateChange;` — Handle for efficient management of BroadcastStateChange timer
- L244 _protected prototype_ `void BroadcastStateChange();` — notify nearby agents about link changing state
- L247 _protected prototype_ `void CollectNearbyAgents(TArray<UObject*>& NotifyList);` — gather agents to notify about state change
- L250 _protected member_ `FDelegateHandle OnNavAreaRegisteredDelegateHandle;`
- L251 _protected member_ `FDelegateHandle OnNavAreaUnregisteredDelegateHandle;`

#### struct `FNavLinkCustomInstanceData`  
`struct FNavLinkCustomInstanceData : public FActorComponentInstanceData`  
_L257-289_
- reflection: `USTRUCT()`
- inherits: `FActorComponentInstanceData`
- desc: Used to store navlink data during RerunConstructionScripts
- L262 _public prototype_ `FNavLinkCustomInstanceData() = default;`
- L263 _public function_ `FNavLinkCustomInstanceData(const UNavLinkCustomComponent* SourceComponent) : FActorComponentInstanceData(SourceComponent)`
- L267 _public prototype_ `virtual ~FNavLinkCustomInstanceData() = default;`
- L269 _public function_ `virtual bool ContainsData() const override`
- L274 _public function_ `virtual void ApplyToComponent(UActorComponent* Component, const ECacheApplyPhase CacheApplyPhase) override`
- L285 _public member_ `FNavLinkId CustomLinkId;` — `UPROPERTY()`
- L288 _public member_ `FNavLinkAuxiliaryId AuxiliaryCustomLinkId;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L32 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnMoveReachedLink, UNavLinkCustomComponent* , UObject* , const FVector& );`
- L33 _delegate_ `DECLARE_DELEGATE_TwoParams(FBroadcastFilter, UNavLinkCustomComponent* , TArray<UObject*>& );`

### `Source/Runtime/NavigationSystem/Public/NavLinkCustomInterface.h` (Public)


#### class `UNavLinkCustomInterface`  
`class UNavLinkCustomInterface : public UInterface`  
_L28-31_
- reflection: `UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `INavLinkCustomInterface`  
`class INavLinkCustomInterface`  
_L33-106_
- L38 _private function_ `virtual void GetLinkData(FVector& LeftPt, FVector& RightPt, ENavLinkDirection::Type& Direction) const` — Get basic link data: two points (relative to owner) and direction
- L41 _private function_ `virtual void GetSupportedAgents(FNavAgentSelector& OutSupportedAgents) const` — Get agents supported by this link
- L44 _private function_ `virtual TSubclassOf<UNavArea> GetLinkAreaClass() const` — Get basic link data: area class (null = default walkable)
- L46 _private function_ `virtual FNavLinkAuxiliaryId GetAuxiliaryId() const`
- L49 _private function_ `virtual uint32 GetLinkId() const final` — `UE_DEPRECATED(5.3, "LinkIds are now based on a FNavLinkId. Call GetId() instead. This function only returns Invalid Id.")`
- L54 _private function_ `virtual FNavLinkId GetId() const` — Get unique ID number for custom link Owner should get its unique ID by calling INavLinkCustomInterface::GetUniqueId() and store it
- L57 _private function_ `virtual void UpdateLinkId(uint32 NewUniqueId) final` — `UE_DEPRECATED(5.3, "LinkIds are now based on a FNavLinkId. Call the version of this function that takes a FNavLinkId. This function now has no effect.")`
- L60 _private function_ `virtual void UpdateLinkId(FNavLinkId NewUniqueId)` — Update unique ID number for custom link by navigation system.
- L63 _private prototype_ `virtual UObject* GetLinkOwner() const;` — Get object owner of navigation link, used for creating containers with multiple links
- L68 _private function_ `virtual bool IsLinkPathfindingAllowed(const UObject* Querier) const` — Check if link allows path finding Querier is usually an AIController trying to find path
- L73 _private function_ `virtual bool OnLinkMoveStarted(class UObject* PathComp, const FVector& DestPoint)` — Notify called when agent starts using this link for movement. returns true = custom movement, path following will NOT update velocity until FinishUsingCustomLink() is called on it
- L76 _private function_ `virtual void OnLinkMoveFinished(class UObject* PathComp)` — Notify called when agent finishes using this link for movement
- L79 _private function_ `virtual bool IsLinkUsingCustomReachCondition(const UObject* PathComp) const` — Whether or not this link has custom reach conditions that need to override the default reach checks done by the path following component.
- L84 _private function_ `virtual bool HasReachedLinkStart(const UObject* PathComp, const FVector& CurrentLocation, const FNavPathPoint& LinkStart, const FNavPathPoint& LinkEnd) const` — Function that replaces the default reach check when IsLinkUsingCustomReachCondition is true. Returns true if CurrentLocation has reached the start of the link.
- L87 _private prototype_ `static uint32 GetUniqueId();` — `UE_DEPRECATED(5.3, "LinkIds are now based on FNavLinkId using FNavLinkId::GenerateUniqueId(). This function will still generate an incremental Id however it does not work well in all circumstances.")`
- L91 _private prototype_ `static void UpdateUniqueId(FNavLinkId AlreadyUsedId);` — `UE_DEPRECATED(5.3, "LinkIds are now based on FNavLinkId. If your project is still using any of the old incremental Ids (saved in actors in levels or licensee code) then this function must be called still (typically by existing engine code), otherwise it is not necessary.")` — Helper function: bump unique ID numbers above given one
- L94 _private function_ `static void UpdateUniqueId(uint32 AlreadyUsedId)` — `UE_DEPRECATED(5.3, "LinkIds are now based on FNavLinkId. You may need to call the other version of this function that takes a FNavLinkId. This function has no effect.")`
- L97 _private prototype_ `static FNavigationLink GetModifier(const INavLinkCustomInterface* CustomNavLink);` — Helper function: create modifier for navigation data export
- L100 _private prototype_ `static void ResetUniqueId();` — `UE_DEPRECATED(5.3, "LinkIds are now based on a FNavLinkId Hash. If your project is still using any of the old incremental Ids then this function must be called still (typically by existing engine code), otherwise it is not necessary.")`
- L102 _private prototype_ `static void OnPreWorldInitialization(UWorld* World, const FWorldInitializationValues IVS);`
- L105 _private member_ `static uint32 NextUniqueId;` — `UE_DEPRECATED(5.3, "LinkIds are now based on FNavLinkId using FNavLinkId::GenerateUniqueId().")`

### `Source/Runtime/NavigationSystem/Public/NavLinkHostInterface.h` (Public)


#### class `UNavLinkHostInterface`  
`class UNavLinkHostInterface : public UInterface`  
_L12-15_
- reflection: `UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `INavLinkHostInterface`  
`class INavLinkHostInterface`  
_L17-32_
- L24 _private prototype_ `virtual bool GetNavigationLinksClasses(TArray<TSubclassOf<class UNavLinkDefinition> >& OutClasses) const PURE_VIRTUAL(INavLinkHostInterface::GetNavigationLinksClasses,return false;);` — Retrieves UNavLinkDefinition derived UClasses hosted by this interface implementer
- L31 _private function_ `virtual bool GetNavigationLinksArray(TArray<FNavigationLink>& OutLink, TArray<FNavigationSegmentLink>& OutSegments) const` — _Optional_ way of retrieving navigation link data - if INavLinkHostInterface implementer defines custom navigation links then it can just retrieve a list of links

### `Source/Runtime/NavigationSystem/Public/NavLinkRenderingComponent.h` (Public)


#### class `UNavLinkRenderingComponent`  
`class UNavLinkRenderingComponent : public UPrimitiveComponent`  
_L14-33_
- reflection: `UCLASS(hidecategories=Object, editinlinenew, MinimalAPI)`
- inherits: `UPrimitiveComponent`
- L19 _private prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L22 _private function_ `virtual bool ShouldRecreateProxyOnUpdateTransform() const override` — Should recreate proxy one very update
- L23 _private function_ `virtual bool GetIgnoreBoundsForEditorFocus() const override`
- L25 _private prototype_ `virtual bool ComponentIsTouchingSelectionBox(const FBox& InSelBBox, const bool bConsiderOnlyBSP, const bool bMustEncompassEntireComponent) const override;`
- L26 _private prototype_ `virtual bool ComponentIsTouchingSelectionFrustum(const FConvexVolume& InFrustum, const bool bConsiderOnlyBSP, const bool bMustEncompassEntireComponent) const override;`
- L31 _private prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform &LocalToWorld) const override;`

### `Source/Runtime/NavigationSystem/Public/NavLinkRenderingProxy.h` (Public)


#### class `FNavLinkRenderingProxy`  
`class FNavLinkRenderingProxy : public FPrimitiveSceneProxy`  
_L15-87_
- inherits: `FPrimitiveSceneProxy`
- L18 _private member_ `AActor* LinkOwnerActor;`
- L19 _private member_ `class INavLinkHostInterface* LinkOwnerHost;`
- L22 _public prototype_ `SIZE_T GetTypeHash() const override;`
- L70 _private member_ `TArray<FNavLinkDrawing> OffMeshPointLinks;`
- L71 _private member_ `TArray<FNavLinkSegmentDrawing> OffMeshSegmentLinks;`
- L75 _public prototype_ `FNavLinkRenderingProxy(const UPrimitiveComponent* InComponent);` — Initialization constructor.
- L76 _public prototype_ `virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override;`
- L77 _public prototype_ `virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override;`
- L78 _public prototype_ `virtual uint32 GetMemoryFootprint( void ) const override;`
- L79 _public prototype_ `uint32 GetAllocatedSize( void ) const;`
- L80 _public prototype_ `void StorePointLinks(const FTransform& LocalToWorld, const TArray<FNavigationLink>& LinksArray);`
- L81 _public prototype_ `void StoreSegmentLinks(const FTransform& LocalToWorld, const TArray<FNavigationSegmentLink>& LinksArray);`
- L83 _public prototype_ `static void GetLinkMeshes(const TArray<FNavLinkDrawing>& OffMeshPointLinks, const TArray<FNavLinkSegmentDrawing>& OffMeshSegmentLinks, TArray<float>& StepHeights, FMaterialRenderProxy* const MeshColorInstance, int32 ViewIndex, FMeshElementCollector& Collector, uint32 AgentMask);`
- L86 _public prototype_ `static void DrawLinks(FPrimitiveDrawInterface* PDI, TArray<FNavLinkDrawing>& OffMeshPointLinks, TArray<FNavLinkSegmentDrawing>& OffMeshSegmentLinks, TArray<float>& StepHeights, FMaterialRenderProxy* const MeshColorInstance, uint32 AgentMask);` — made static to allow consistent navlinks drawing even if something is drawing links without FNavLinkRenderingProxy

#### struct `FNavLinkRenderingProxy::FNavLinkDrawing`  
`struct FNavLinkDrawing`  
_L24-44_
- L26 _public function_ `FNavLinkDrawing()`
- L27 _public function_ `FNavLinkDrawing(const FTransform& InLocalToWorld, const FNavigationLink& Link) : Left(InLocalToWorld.TransformPosition(Link.Left)) , Right(InLocalToWorld.TransformPosition(Link.Right)) , Direction(Link.Direction) , Color(UNavArea::GetColor(Link.GetAreaClass())) , SnapRadius(Link.SnapRadius) , SnapHeight(Link.bUseSnapHeight ? Link.SnapHeight : -1.0f) , SupportedAgentsBits(Link.SupportedAgents.PackedBits)`
- L37 _public member_ `FVector Left;`
- L38 _public member_ `FVector Right;`
- L39 _public member_ `ENavLinkDirection::Type Direction;`
- L40 _public member_ `FColor Color;`
- L41 _public member_ `float SnapRadius;`
- L42 _public member_ `float SnapHeight;`
- L43 _public member_ `uint32 SupportedAgentsBits;`

#### struct `FNavLinkRenderingProxy::FNavLinkSegmentDrawing`  
`struct FNavLinkSegmentDrawing`  
_L45-67_
- L47 _public function_ `FNavLinkSegmentDrawing()`
- L48 _public function_ `FNavLinkSegmentDrawing(const FTransform& InLocalToWorld, const FNavigationSegmentLink& Link) : LeftStart(InLocalToWorld.TransformPosition(Link.LeftStart)) , LeftEnd(InLocalToWorld.TransformPosition(Link.LeftEnd)) , RightStart(InLocalToWorld.TransformPosition(Link.RightStart)) , RightEnd(InLocalToWorld.TransformPosition(Link.RightEnd)) , Direction(Link.Direction) , Color(UNavArea::GetColor(Link.GetAreaClass())) , SnapRadius(Link.SnapRadius) , SnapHeight(Link.bUseSnapHeight ? Link.SnapHeight : -1.0f) , SupportedAgentsBits(Link.SupportedAgents.PackedBits)`
- L60 _public member_ `FVector LeftStart, LeftEnd;`
- L60 _public member_ `FVector LeftStart, LeftEnd;`
- L61 _public member_ `FVector RightStart, RightEnd;`
- L61 _public member_ `FVector RightStart, RightEnd;`
- L62 _public member_ `ENavLinkDirection::Type Direction;`
- L63 _public member_ `FColor Color;`
- L64 _public member_ `float SnapRadius;`
- L65 _public member_ `float SnapHeight;`
- L66 _public member_ `uint32 SupportedAgentsBits;`

### `Source/Runtime/NavigationSystem/Public/NavLinkTrivial.h` (Public)


#### class `UNavLinkTrivial`  
`class UNavLinkTrivial : public UNavLinkDefinition`  
_L10-13_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UNavLinkDefinition`

### `Source/Runtime/NavigationSystem/Public/NavMesh/LinkGenerationConfig.h` (Public)


#### enum `ENavLinkBuilderFlags`  
`enum class ENavLinkBuilderFlags : uint16`  
_L17-21_
- reflection: `UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L19 _public enumerator_ `CreateCenterPointLink = 1 << 0`
- L20 _public enumerator_ `CreateExtremityLink = 1 << 1`

#### struct `FNavLinkGenerationJumpConfig`  
`struct FNavLinkGenerationJumpConfig`  
_L26-143_
- reflection: `USTRUCT()`
- desc: Experimental configuration to generate vertical links.
- L30 _public prototype_ `FNavLinkGenerationJumpConfig();`
- L34 _public prototype_ `~FNavLinkGenerationJumpConfig() = default;` — Note: We need to explicitly disable warnings on these constructors/operators for clang to be happy with deprecated variables
- L35 _public prototype_ `FNavLinkGenerationJumpConfig(const FNavLinkGenerationJumpConfig&) = default;`
- L36 _public prototype_ `FNavLinkGenerationJumpConfig(FNavLinkGenerationJumpConfig&&) = default;`
- L37 _public prototype_ `FNavLinkGenerationJumpConfig& operator=(const FNavLinkGenerationJumpConfig&) = default;`
- L38 _public prototype_ `FNavLinkGenerationJumpConfig& operator=(FNavLinkGenerationJumpConfig&&) = default;`
- L43 _public member_ `bool bEnabled = true;` — `UPROPERTY(EditAnywhere, Config, Category = Settings)` — Should this config be used to generate links.
- L47 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, Config, Category = Settings)` — A name for this config
- L52 _public member_ `float JumpLength = 150.f;` — `UPROPERTY(EditAnywhere, Config, Category = Settings, meta=(UIMin=0, ClampMin=0, UIMax=10000))` — Horizontal length of the jump. How far from the starting point we will look for ground.
- L56 _public member_ `float JumpDistanceFromEdge = 10.f;` — `UPROPERTY(EditAnywhere, Config, Category = Settings, meta=(UIMin=0, ClampMin=0))` — How far from the navmesh edge is the jump started.
- L63 _public member_ `float JumpMaxDepth = 150.f;` — `UPROPERTY(EditAnywhere, Config, Category = Settings)` — How far below the starting height we want to look for landing ground. A negative value can be used to generate a trajectory landing above the starting height (if negative, make sure to use a JumpHeight value big enough).
- L67 _public member_ `float JumpHeight = 50.f;` — `UPROPERTY(EditAnywhere, Config, Category = Settings, meta=(UIMin=0, ClampMin=0))` — Peak height relative to the height of the starting point.
- L71 _public member_ `float JumpEndsHeightTolerance = 80.f;` — `UPROPERTY(EditAnywhere, Config, Category = Settings, meta=(UIMin=0, ClampMin=0))` — Tolerance at both ends of the jump to find ground.
- L76 _public member_ `float SamplingSeparationFactor = 1.f;` — `UPROPERTY(EditAnywhere, Config, Category = Settings, meta=(UIMin=1, ClampMin=1))` — Value multiplied by CellSize to find the distance between sampling trajectories. Default is 1. Larger values improve generation speed but might introduce sampling errors.
- L81 _public member_ `float FilterDistanceThreshold = 80.f;` — `UPROPERTY(EditAnywhere, Config, Category = Settings, meta=(UIMin=0, ClampMin=0))` — When filtering similar links, it's the distance used to compare between segment endpoints to match similar links. Use greater distance for more filtering (0 to deactivate filtering).
- L85 _public member_ `uint16 LinkBuilderFlags = (uint16)ENavLinkBuilderFlags::CreateCenterPointLink;` — `UPROPERTY(EditAnywhere, Config, Category = Settings, meta = (Bitmask, BitmaskEnum = "/Script/NavigationSystem.ENavLinkBuilderFlags"))` — Flags used to indicate how links will be added.
- L91 _public member_ `TSubclassOf<UNavAreaBase> AreaClass_DEPRECATED;` — `UE_DEPRECATED(5.6, "AreaClass is deprecated")` — `UPROPERTY(Config, meta = (DeprecatedProperty, DeprecationMessage = "Use DownDirectionAreaClass and UpDirectionAreaClass instead."))` — Area class for links generated by this configuration.
- L100 _public member_ `TSubclassOf<UNavAreaBase> DownDirectionAreaClass;` — `UPROPERTY(EditAnywhere, Config, Category = Settings)` — Area class for downward traversal of links generated by this configuration. @note If the value matches UpDirectionAreaClass, a single bidirectional link will be used to represent links generated by this configuration. If the value is null, no link will be generated in this direction
- L108 _public member_ `TSubclassOf<UNavAreaBase> UpDirectionAreaClass;` — `UPROPERTY(EditAnywhere, Config, Category = Settings)` — Area class for upward traversal of links generated by this configuration. @note If the value matches DownDirectionAreaClass, a single bidirectional link will be used to represent links generated by this configuration. If the value is null, no link will be generated in this direction
- L119 _public member_ `TSubclassOf<UBaseGeneratedNavLinksProxy> LinkProxyClass;` — `UPROPERTY(EditAnywhere, Category= Settings)` — Class used to handle links made with this configuration. Using this allows to implement custom behaviors when using navlinks, for example during the pathfollow. Note that having a proxy is not required for successful navlink pathfinding, but it does allow for custom behavior at the start and the end of a given navlink. This implies that using LinkProxyClass is optional, and it can remain empty (the default value). @see INavLinkCustomInterface @see UGeneratedNavLinksProxy
- L123 _public member_ `FNavLinkId LinkProxyId;` — `UPROPERTY()` — Identifier used identify the current proxy handler. All links generated through this config will use the same handler.
- L129 _public member_ `TObjectPtr<UBaseGeneratedNavLinksProxy> LinkProxy = nullptr;` — `UPROPERTY(SkipSerialization)` — Current proxy. The proxy instance is build from the LinkProxyClass (provided it's not null). A proxy will be created if a @see LinkProxyClass is used.
- L134 _public member_ `bool bLinkProxyRegistered = false;` — `UPROPERTY(SkipSerialization)` — Is the link proxy registered to the navigation system CustomNavLinksMap. Registration occurs on PostRegisterAllComponents or on PostLoadPreRebuild if a new proxy was created.
- L137 _public prototype_ `bool Serialize(FArchive& Ar);` — Implemented for deprecated property cleanup purposes.
- L141 _public prototype_ `void CopyToDetourConfig(dtNavLinkBuilderJumpConfig& OutDetourConfig) const;` — Copy configuration to dtNavLinkBuilderJumpConfig.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FNavLinkGenerationJumpConfig> : public TStructOpsTypeTraitsBase2<FNavLinkGenerationJumpConfig>`  
_L145-151_
- inherits: `TStructOpsTypeTraitsBase2<FNavLinkGenerationJumpConfig>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L148-150_

#### struct `FNavLinkGenerationJumpDownConfig`  
`struct UE_DEPRECATED(5.7, "Use FNavLinkGenerationJumpConfig instead.") FNavLinkGenerationJumpDownConfig`  
_L159-267_
- reflection: `USTRUCT()`
- desc: Experimental configuration to generate vertical links.
- L163 _public prototype_ `FNavLinkGenerationJumpDownConfig();`
- L166 _public prototype_ `~FNavLinkGenerationJumpDownConfig() = default;` — Note: We need to explicitly disable warnings on these constructors/operators for clang to be happy with deprecated variables
- L167 _public prototype_ `FNavLinkGenerationJumpDownConfig(const FNavLinkGenerationJumpDownConfig&) = default;`
- L168 _public prototype_ `FNavLinkGenerationJumpDownConfig(FNavLinkGenerationJumpDownConfig&&) = default;`
- L169 _public prototype_ `FNavLinkGenerationJumpDownConfig& operator=(const FNavLinkGenerationJumpDownConfig&) = default;`
- L170 _public prototype_ `FNavLinkGenerationJumpDownConfig& operator=(FNavLinkGenerationJumpDownConfig&&) = default;`
- L174 _public member_ `bool bEnabled = true;` — `UPROPERTY(Config)` — Should this config be used to generate links.
- L179 _public member_ `float JumpLength = 150.f;` — `UPROPERTY(EditAnywhere, Config, Category = Settings, meta=(UIMin=0, ClampMin=0))` — Horizontal length of the jump. How far from the starting point we will look for ground.
- L183 _public member_ `float JumpDistanceFromEdge = 10.f;` — `UPROPERTY(EditAnywhere, Config, Category = Settings, meta=(UIMin=0, ClampMin=0))` — How far from the navmesh edge is the jump started.
- L187 _public member_ `float JumpMaxDepth = 150.f;` — `UPROPERTY(EditAnywhere, Config, Category = Settings, meta=(UIMin=0, ClampMin=0))` — How far below the starting height we want to look for landing ground.
- L191 _public member_ `float JumpHeight = 50.f;` — `UPROPERTY(EditAnywhere, Config, Category = Settings, meta=(UIMin=0, ClampMin=0))` — Peak height relative to the height of the starting point.
- L195 _public member_ `float JumpEndsHeightTolerance = 80.f;` — `UPROPERTY(EditAnywhere, Config, Category = Settings, meta=(UIMin=0, ClampMin=0))` — Tolerance at both ends of the jump to find ground.
- L200 _public member_ `float SamplingSeparationFactor = 1.f;` — `UPROPERTY(EditAnywhere, Config, Category = Settings, meta=(UIMin=1, ClampMin=1))` — Value multiplied by CellSize to find the distance between sampling trajectories. Default is 1. Larger values improve generation speed but might introduce sampling errors.
- L205 _public member_ `float FilterDistanceThreshold = 80.f;` — `UPROPERTY(EditAnywhere, Config, Category = Settings, meta=(UIMin=0, ClampMin=0))` — When filtering similar links, it's the distance used to compare between segment endpoints to match similar links. Use greater distance for more filtering (0 to deactivate filtering).
- L209 _public member_ `uint16 LinkBuilderFlags = (uint16)ENavLinkBuilderFlags::CreateCenterPointLink;` — `UPROPERTY(EditAnywhere, Config, Category = Settings, meta = (Bitmask, BitmaskEnum = "/Script/NavigationSystem.ENavLinkBuilderFlags"))` — Flags used to indicate how links will be added.
- L215 _public member_ `TSubclassOf<UNavAreaBase> AreaClass_DEPRECATED;` — `UE_DEPRECATED(5.6, "AreaClass is deprecated")` — `UPROPERTY(Config, meta = (DeprecatedProperty, DeprecationMessage = "Use DownDirectionAreaClass and UpDirectionAreaClass instead."))` — Area class for links generated by this configuration.
- L224 _public member_ `TSubclassOf<UNavAreaBase> DownDirectionAreaClass;` — `UPROPERTY(EditAnywhere, Config, Category = Settings)` — Area class for downward traversal of links generated by this configuration. @note If the value matches UpDirectionAreaClass, a single bidirectional link will be used to represent links generated by this configuration. If the value is null, no link will be generated in this direction
- L232 _public member_ `TSubclassOf<UNavAreaBase> UpDirectionAreaClass;` — `UPROPERTY(EditAnywhere, Config, Category = Settings)` — Area class for upward traversal of links generated by this configuration. @note If the value matches DownDirectionAreaClass, a single bidirectional link will be used to represent links generated by this configuration. If the value is null, no link will be generated in this direction
- L243 _public member_ `TSubclassOf<UBaseGeneratedNavLinksProxy> LinkProxyClass;` — `UPROPERTY(EditAnywhere, Category= Settings)` — Class used to handle links made with this configuration. Using this allows to implement custom behaviors when using navlinks, for example during the pathfollow. Note that having a proxy is not required for successful navlink pathfinding, but it does allow for custom behavior at the start and the end of a given navlink. This implies that using LinkProxyClass is optional, and it can remain empty (the default value). @see INavLinkCustomInterface @see UGeneratedNavLinksProxy
- L247 _public member_ `FNavLinkId LinkProxyId;` — `UPROPERTY()` — Identifier used identify the current proxy handler. All links generated through this config will use the same handler.
- L253 _public member_ `TObjectPtr<UBaseGeneratedNavLinksProxy> LinkProxy = nullptr;` — `UPROPERTY(Transient)` — Current proxy. The proxy instance is build from the LinkProxyClass (provided it's not null). A proxy will be created if a @see LinkProxyClass is used.
- L258 _public member_ `bool bLinkProxyRegistered = false;` — `UPROPERTY(Transient)` — Is the link proxy registered to the navigation system CustomNavLinksMap. Registration occurs on PostRegisterAllComponents or on PostLoadPreRebuild if a new proxy was created.
- L261 _public prototype_ `bool Serialize(FArchive& Ar);` — Implemented for deprecated property cleanup purposes.
- L265 _public prototype_ `void CopyToDetourConfig(dtNavLinkBuilderJumpDownConfig& OutDetourConfig) const;` — Copy configuration to dtNavLinkBuilderJumpDownConfig.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FNavLinkGenerationJumpDownConfig> : public TStructOpsTypeTraitsBase2<FNavLinkGenerationJumpDownConfig>`  
_L269-275_
- inherits: `TStructOpsTypeTraitsBase2<FNavLinkGenerationJumpDownConfig>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L272-274_

#### Free symbols / members of external scopes

- L22 _prototype_ `ENUM_CLASS_FLAGS(ENavLinkBuilderFlags);`
- L149 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon92d457820103`)
- L273 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon92d457820203`)

### `Source/Runtime/NavigationSystem/Public/NavMesh/LinkGenerationDebugFlags.h` (Public)


#### enum `ELinkGenerationDebugFlags`  
`enum class ELinkGenerationDebugFlags : uint16`  
_L7-18_
- reflection: `UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L9 _public enumerator_ `WalkableSurface = 1 << 0`
- L10 _public enumerator_ `WalkableBorders = 1 << 1`
- L11 _public enumerator_ `SelectedEdge = 1 << 2`
- L12 _public enumerator_ `SelectedEdgeTrajectory = 1 << 3`
- L13 _public enumerator_ `SelectedEdgeLandingSamples = 1 << 4`
- L14 _public enumerator_ `SelectedEdgeCollisions = 1 << 5`
- L15 _public enumerator_ `SelectedEdgeCollisionsSamples = 1 << 6`
- L16 _public enumerator_ `Links = 1 << 7`
- L17 _public enumerator_ `FilteredLinks = 1 << 8`

#### Free symbols / members of external scopes

- L19 _prototype_ `ENUM_CLASS_FLAGS(ELinkGenerationDebugFlags);`

### `Source/Runtime/NavigationSystem/Public/NavMesh/NavMeshBoundsVolume.h` (Public)


#### class `ANavMeshBoundsVolume`  
`class ANavMeshBoundsVolume : public AVolume`  
_L17-40_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `AVolume`
- L22 _private member_ `FNavAgentSelector SupportedAgents;` — `UPROPERTY(EditAnywhere, Category = Navigation)`
- L26 _private member_ `uint8 bAllowPhysicsOverlap : 1 = false;` — `UPROPERTY(EditAnywhere, Category = Navigation)` — If true, then this volume will have a BodyInstance and calls to EncompassesPoint will function as expected.
- L29 _private prototype_ `virtual void PostRegisterAllComponents() override;`
- L30 _private prototype_ `virtual void PostUnregisterAllComponents() override;`
- L34 _private prototype_ `virtual void PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L35 _private prototype_ `virtual void PostEditUndo() override;`
- L38 _private prototype_ `static void OnPostEngineInit();`

### `Source/Runtime/NavigationSystem/Public/NavMesh/NavMeshPath.h` (Public)


#### struct `FNavMeshNodeFlags`  
`struct FNavMeshNodeFlags`  
_L13-32_
- desc: Helper to translate FNavPathPoint.Flags.
- L16 _public member_ `uint8 PathFlags;` — Extra node information (like "path start", "off-mesh connection").
- L18 _public member_ `uint8 Area;` — Area type after this node.
- L20 _public member_ `uint16 AreaFlags;` — Area flags for this node.
- L22 _public function_ `FNavMeshNodeFlags() : PathFlags(0), Area(0), AreaFlags(0)`
- L23 _public function_ `FNavMeshNodeFlags(const uint32 Flags) : PathFlags((uint8)Flags), Area((uint8)(Flags >> 8)), AreaFlags((uint16)(Flags >> 16))`
- L24 _public function_ `uint32 Pack() const`
- L25 _public function_ `bool IsNavLink() const`
- L27 _public function_ `FNavMeshNodeFlags& AddAreaFlags(const uint16 InAreaFlags)`

#### struct `FNavMeshPath`  
`struct FNavMeshPath : public FNavigationPath`  
_L35-183_
- inherits: `FNavigationPath`
- L37 _public typedef_ `typedef FNavigationPath Super;`
- L39 _public prototype_ `FNavMeshPath();`
- L40 _public prototype_ `~FNavMeshPath();`
- L42 _public prototype_ `FNavMeshPath(const FNavMeshPath&);`
- L43 _public prototype_ `FNavMeshPath(FNavMeshPath&& Other);`
- L44 _public prototype_ `FNavMeshPath& operator=(const FNavMeshPath& Other);`
- L45 _public prototype_ `FNavMeshPath& operator=(FNavMeshPath&& Other);`
- L47 _public function_ `inline void SetWantsStringPulling(const bool bNewWantsStringPulling)`
- L48 _public function_ `inline bool WantsStringPulling() const`
- L49 _public function_ `inline bool IsStringPulled() const`
- L52 _public prototype_ `void PerformStringPulling(const FVector& StartLoc, const FVector& EndLoc);` — find string pulled path from PathCorridor
- L54 _public function_ `inline void SetWantsPathCorridor(const bool bNewWantsPathCorridor)`
- L55 _public function_ `inline bool WantsPathCorridor() const`
- L57 _public function_ `inline const TArray<FNavigationPortalEdge>& GetPathCorridorEdges() const`
- L58 _public function_ `inline void SetPathCorridorEdges(const TArray<FNavigationPortalEdge>& InPathCorridorEdges)`
- L60 _public function_ `inline void OnPathCorridorUpdated()`
- L62 _public prototype_ `virtual void DebugDraw(const ANavigationData* NavData, const FColor PathColor, UCanvas* Canvas, const bool bPersistent, const float LifeTime, const uint32 NextPathPointIndex = 0) const override;`
- L64 _public prototype_ `bool ContainsWithSameEnd(const FNavMeshPath* Other) const;`
- L66 _public prototype_ `void OffsetFromCorners(FVector::FReal Distance);`
- L68 _public prototype_ `void ApplyFlags(int32 NavDataFlags);`
- L70 _public prototype_ `virtual void ResetForRepath() override;`
- L73 _public prototype_ `bool GetNodeFlags(int32 NodeIdx, FNavMeshNodeFlags& Flags) const;` — get flags of path point or corridor poly (depends on bStringPulled flag)
- L76 _public function_ `virtual FVector::FReal GetCostFromNode(NavNodeRef PathNode) const override` — get cost of path, starting from next poly in corridor
- L79 _public function_ `virtual FVector::FReal GetCostFromIndex(int32 PathPointIndex) const override` — get cost of path, starting from given point
- L91 _public function_ `inline FVector::FReal GetTotalPathLength() const`
- L96 _public function_ `inline int32 GetNodeRefIndex(const NavNodeRef NodeRef) const`
- L99 _public function_ `virtual bool ContainsNode(NavNodeRef NodeRef) const override` — check if path (all polys in corridor) contains given node
- L101 _public function_ `virtual bool ContainsCustomLink(FNavLinkId UniqueLinkId) const override`
- L102 _public function_ `virtual bool ContainsAnyCustomLink() const override`
- L104 _public prototype_ `bool IsPathSegmentANavLink(const int32 PathSegmentStartIndex) const;`
- L106 _public prototype_ `virtual bool DoesIntersectBox(const FBox& Box, uint32 StartingIndex = 0, int32* IntersectingSegmentIndex = NULL, FVector* AgentExtent = NULL) const override;`
- L107 _public prototype_ `virtual bool DoesIntersectBox(const FBox& Box, const FVector& AgentLocation, uint32 StartingIndex = 0, int32* IntersectingSegmentIndex = NULL, FVector* AgentExtent = NULL) const override;`
- L109 _public prototype_ `virtual FVector GetSegmentDirection(uint32 SegmentEndIndex) const override;` — retrieves normalized direction vector to given path segment. If path is not string pulled navigation corridor is being used
- L111 _public prototype_ `void Invert();`
- L114 _private prototype_ `bool DoesPathIntersectBoxImplementation(const FBox& Box, const FVector& StartLocation, uint32 StartingIndex, int32* IntersectingSegmentIndex, FVector* AgentExtent) const;`
- L115 _private prototype_ `void InternalResetNavMeshPath();`
- L120 _public prototype_ `virtual void DescribeSelfToVisLog(struct FVisualLogEntry* Snapshot) const override;`
- L121 _public prototype_ `virtual FString GetDescription() const override;`
- L128 _protected prototype_ `FVector::FReal GetStringPulledLength(const int32 StartingPoint) const;` — calculates total length of string pulled path. Does not generate string pulled path if it's not already generated (see bWantsStringPulling and bStrigPulled) Internal use only
- L133 _protected prototype_ `FVector::FReal GetPathCorridorLength(const int32 StartingEdge) const;` — calculates estimated length of path expressed as sequence of navmesh edges. It basically sums up distances between every subsequent nav edge pair edge middles. Internal use only
- L138 _protected prototype_ `const TArray<FNavigationPortalEdge>& GeneratePathCorridorEdges() const;` — it's only const to be callable in const environment. It's not supposed to be called directly externally anyway, just as part of retrieving corridor on demand or generating it in internal processes. It fills a mutable array.
- L143 _public member_ `TArray<NavNodeRef> PathCorridor;` — sequence of navigation mesh poly ids representing an obstacle-free navigation corridor
- L146 _public member_ `TArray<FVector::FReal> PathCorridorCost;` — for every poly in PathCorridor stores traversal cost from previous navpoly
- L150 _public member_ `TArray<uint32> CustomLinkIds;` — `UE_DEPRECATED(5.3, "LinkIds are now based on FNavLinkId. Use CustomNavLinkIds instead. CustomLinkIds array is no longer populated or used in the engine")` — set of unique link Ids
- L152 _public member_ `TArray<FNavLinkId> CustomNavLinkIds;`
- L158 _private member_ `mutable TArray<FNavigationPortalEdge> PathCorridorEdges;` — sequence of FVector pairs where each pair represents navmesh portal edge between two polygons navigation corridor. Note, that it should always be accessed via GetPathCorridorEdges() since PathCorridorEdges content is generated on first access
- L161 _private member_ `mutable uint32 bCorridorEdgesGenerated : 1;` — transient variable indicating whether PathCorridorEdges contains up to date information
- L165 _public member_ `uint32 bDynamic : 1;` — is this path generated on dynamic navmesh (i.e. one attached to moving surface)
- L171 _protected member_ `uint32 bStringPulled : 1;` — does this path contain string pulled path? If true then NumPathVerts > 0 and OutPathVerts contains valid data. If false there's only navigation corridor data available.
- L175 _protected member_ `uint32 bWantsStringPulling : 1;` — If set to true path instance will contain a string pulled version. Otherwise only navigation corridor will be available. Defaults to true
- L179 _protected member_ `uint32 bWantsPathCorridor : 1;` — If set to true path instance will contain path corridor generated as a part pathfinding call (i.e. without the need to generate it with GeneratePathCorridorEdges
- L182 _public member_ `static const FNavPathType Type;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define RECAST_STRAIGHTPATH_OFFMESH_CONNECTION 0x04`

### `Source/Runtime/NavigationSystem/Public/NavMesh/NavMeshRenderingComponent.h` (Public)


#### enum `ENavMeshDetailFlags`  
`enum class ENavMeshDetailFlags : uint8`  
_L27-51_
- L29 _public enumerator_ `TriangleEdges`
- L30 _public enumerator_ `PolyEdges`
- L31 _public enumerator_ `BoundaryEdges`
- L32 _public enumerator_ `FilledPolys`
- L33 _public enumerator_ `TileBounds`
- L34 _public enumerator_ `PathCollidingGeometry`
- L35 _public enumerator_ `TileLabels`
- L36 _public enumerator_ `PolygonLabels`
- L37 _public enumerator_ `PolygonCost`
- L38 _public enumerator_ `PolygonFlags`
- L39 _public enumerator_ `PolygonAreaIDs`
- L40 _public enumerator_ `PathLabels`
- L41 _public enumerator_ `NavLinks`
- L42 _public enumerator_ `FailedNavLinks`
- L43 _public enumerator_ `Clusters`
- L44 _public enumerator_ `NavOctree`
- L45 _public enumerator_ `NavOctreeDetails`
- L46 _public enumerator_ `MarkForbiddenPolys`
- L47 _public enumerator_ `TileBuildTimes`
- L48 _public enumerator_ `TileBuildTimesHeatMap`
- L49 _public enumerator_ `TileResolutions`
- L50 _public enumerator_ `OnScreenInformation`

#### struct `FNavMeshSceneProxyData`  
`struct FNavMeshSceneProxyData : public TSharedFromThis<FNavMeshSceneProxyData, ESPMode::ThreadSafe>`  
_L54-118_
- inherits: `TSharedFromThis<FNavMeshSceneProxyData,ESPMode::ThreadSafe>`
- desc: exported to API for GameplayDebugger module
- L62 _public member_ `TArray<FDebugMeshData> MeshBuilders;`
- L72 _public member_ `TArray<FDebugRenderSceneProxy::FDebugLine> ThickLineItems;`
- L73 _public member_ `TArray<FDebugRenderSceneProxy::FDebugLine> TileEdgeLines;`
- L74 _public member_ `TArray<FDebugRenderSceneProxy::FDebugLine> NavMeshEdgeLines;`
- L75 _public member_ `TArray<FDebugRenderSceneProxy::FDebugLine> NavLinkLines;`
- L76 _public member_ `TArray<FDebugRenderSceneProxy::FDebugLine> ClusterLinkLines;`
- L77 _public member_ `TArray<FDebugRenderSceneProxy::FDebugLine> AuxLines;`
- L78 _public member_ `TArray<FDebugPoint> AuxPoints;`
- L79 _public member_ `TArray<FDebugRenderSceneProxy::FDebugBox> AuxBoxes;`
- L80 _public member_ `TArray<FDebugRenderSceneProxy::FMesh> Meshes;`
- L91 _public member_ `TArray<FDebugText> DebugLabels;`
- L93 _public member_ `TArray<FBoxCenterAndExtent> OctreeBounds;`
- L95 _public member_ `FBox Bounds;`
- L96 _public member_ `FVector NavMeshDrawOffset;`
- L97 _public member_ `uint32 bDataGathered : 1;`
- L98 _public member_ `uint32 bNeedsNewData : 1;`
- L99 _public member_ `int32 NavDetailFlags;`
- L101 _public function_ `FNavMeshSceneProxyData() : NavMeshDrawOffset(0, 0, 10.f), bDataGathered(false), bNeedsNewData(true), NavDetailFlags(0)`
- L104 _public prototype_ `void Reset();`
- L105 _public prototype_ `void Serialize(FArchive& Ar);`
- L106 _public prototype_ `uint32 GetAllocatedSize() const;`
- L110 _public prototype_ `void GatherData(const ARecastNavMesh* NavMesh, int32 InNavDetailFlags, const TArray<int32>& TileSet);` — `UE_DEPRECATED(5.5, "Use the version of this function that takes an array of FNavTileRefs instead")`
- L111 _public prototype_ `void GatherData(const ARecastNavMesh* NavMesh, int32 InNavDetailFlags, const TArray<struct FNavTileRef>& TileSet);`
- L114 _public prototype_ `void AddMeshForInternalData(const struct FRecastInternalDebugData& InInternalData);`

#### struct `FNavMeshSceneProxyData::FDebugMeshData`  
`struct FDebugMeshData`  
_L56-61_
- L58 _public member_ `TArray<FDynamicMeshVertex> Vertices;`
- L59 _public member_ `TArray<uint32> Indices;`
- L60 _public member_ `FColor ClusterColor;`

#### struct `FNavMeshSceneProxyData::FDebugPoint`  
`struct FDebugPoint`  
_L64-70_
- L66 _public function_ `FDebugPoint(const FVector& InPosition, const FColor& InColor, const float InSize) : Position(InPosition), Color(InColor), Size(InSize)`
- L67 _public member_ `FVector Position;`
- L68 _public member_ `FColor Color;`
- L69 _public member_ `float Size = 0.f;`

#### struct `FNavMeshSceneProxyData::FDebugText`  
`struct FDebugText`  
_L82-90_
- L84 _public member_ `FVector Location;`
- L85 _public member_ `FString Text;`
- L87 _public function_ `FDebugText()`
- L88 _public function_ `FDebugText(const FVector& InLocation, const FString& InText) : Location(InLocation), Text(InText)`
- L89 _public function_ `FDebugText(const FString& InText) : Location(FNavigationSystem::InvalidLocation), Text(InText)`

#### class `FNavMeshSceneProxy`  
`class FNavMeshSceneProxy final : public FDebugRenderSceneProxy, public FNoncopyable`  
_L121-154_
- inherits: `FDebugRenderSceneProxy,FNoncopyable`
- desc: exported to API for GameplayDebugger module
- L125 _public prototype_ `virtual SIZE_T GetTypeHash() const override;`
- L127 _public prototype_ `FNavMeshSceneProxy(const UPrimitiveComponent* InComponent, FNavMeshSceneProxyData* InProxyData, bool ForceToRender = false);`
- L130 _public prototype_ `virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override;`
- L133 _protected prototype_ `virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override;`
- L135 _protected function_ `virtual uint32 GetMemoryFootprint(void) const override`
- L136 _protected prototype_ `uint32 GetAllocatedSizeInternal(void) const;`
- L139 _private member_ `FNavMeshSceneProxyData ProxyData;`
- L141 _private member_ `FDynamicMeshIndexBuffer32 IndexBuffer;`
- L142 _private member_ `FStaticMeshVertexBuffers VertexBuffers;`
- L143 _private member_ `FLocalVertexFactory VertexFactory;`
- L145 _private member_ `TArray<TUniquePtr<FColoredMaterialRenderProxy>> MeshColors;`
- L146 _private member_ `TArray<FMeshBatchElement> MeshBatchElements;`
- L148 _private member_ `FDebugDrawDelegate DebugTextDrawingDelegate;`
- L149 _private member_ `FDelegateHandle DebugTextDrawingDelegateHandle;`
- L150 _private member_ `TWeakObjectPtr<UNavMeshRenderingComponent> RenderingComponent;`
- L151 _private member_ `uint32 bForceRendering : 1;`
- L152 _private member_ `uint32 bSkipDistanceCheck : 1;`
- L153 _private member_ `uint32 bUseThickLines : 1;`

#### class `FNavMeshDebugDrawDelegateHelper`  
`class FNavMeshDebugDrawDelegateHelper : public FDebugDrawDelegateHelper`  
_L157-189_
- inherits: `FDebugDrawDelegateHelper`
- L159 _private typedef_ `typedef FDebugDrawDelegateHelper Super;`
- L162 _public function_ `FNavMeshDebugDrawDelegateHelper() : bForceRendering(false) , bNeedsNewData(false)`
- L168 _public function_ `void SetupFromProxy(const FNavMeshSceneProxy* InSceneProxy)`
- L176 _public function_ `void Reset()`
- L183 _protected prototype_ `virtual void DrawDebugLabels(UCanvas* Canvas, APlayerController*) override;`
- L186 _private member_ `TArray<FNavMeshSceneProxyData::FDebugText> DebugLabels;`
- L187 _private member_ `uint32 bForceRendering : 1;`
- L188 _private member_ `uint32 bNeedsNewData : 1;`

#### class `UNavMeshRenderingComponent`  
`class UNavMeshRenderingComponent : public UDebugDrawComponent`  
_L193-231_
- reflection: `UCLASS(editinlinenew, ClassGroup = Debug, MinimalAPI)`
- inherits: `UDebugDrawComponent`
- L198 _public function_ `void ForceUpdate()`
- L199 _public function_ `bool IsForcingUpdate() const`
- L201 _public prototype_ `static bool IsNavigationShowFlagSet(const UWorld* World);`
- L204 _protected prototype_ `virtual void OnRegister() override;`
- L205 _protected prototype_ `virtual void OnUnregister() override;`
- L208 _protected prototype_ `virtual FDebugRenderSceneProxy* CreateDebugSceneProxy() override;`
- L210 _protected function_ `virtual FDebugDrawDelegateHelper& GetDebugDrawDelegateHelper() override`
- L214 _protected prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform &LocalToWorld) const override;`
- L218 _protected prototype_ `virtual void GatherData(const ARecastNavMesh& NavMesh, FNavMeshSceneProxyData& OutProxyData) const;` — Gathers drawable information from NavMesh and puts it in OutProxyData. Override to add additional information to OutProxyData.
- L220 _protected prototype_ `void TimerFunction();`
- L223 _protected member_ `uint32 bCollectNavigationData : 1;`
- L224 _protected member_ `uint32 bForceUpdate : 1;`
- L225 _protected member_ `FTimerHandle TimerHandle;`
- L229 _protected member_ `FNavMeshDebugDrawDelegateHelper NavMeshDebugDrawDelegateManager;`

#### Free symbols / members of external scopes

- L233 _namespace_ `namespace FNavMeshRenderingHelpers`
- L235 _prototype_ `void AddVertex(FNavMeshSceneProxyData::FDebugMeshData& MeshData, const FVector& Pos, const FColor Color = FColor::White);` (scope `FNavMeshRenderingHelpers`)
- L237 _prototype_ `void AddTriangleIndices(FNavMeshSceneProxyData::FDebugMeshData& MeshData, int32 V0, int32 V1, int32 V2);` (scope `FNavMeshRenderingHelpers`)

### `Source/Runtime/NavigationSystem/Public/NavMesh/NavTestRenderingComponent.h` (Public)


#### class `FNavTestSceneProxy`  
`class FNavTestSceneProxy final : public FDebugRenderSceneProxy`  
_L20-86_
- inherits: `FDebugRenderSceneProxy`
- L25 _public prototype_ `virtual SIZE_T GetTypeHash() const override;`
- L42 _public function_ `inline friend uint32 GetTypeHash(const FNodeDebugData& Other)`
- L48 _public prototype_ `explicit FNavTestSceneProxy(const UNavTestRenderingComponent* InComponent);`
- L50 _public prototype_ `virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override;`
- L52 _public prototype_ `void GatherPathPoints();`
- L54 _public prototype_ `void GatherPathStep();`
- L56 _public function_ `inline static bool LocationInView(const FVector& Location, const FSceneView* View)`
- L61 _public prototype_ `virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override;`
- L63 _public function_ `virtual uint32 GetMemoryFootprint() const override`
- L66 _private prototype_ `uint32 GetAllocatedSizeInternal() const;`
- L68 _private member_ `FVector3f NavMeshDrawOffset;`
- L70 _private member_ `uint32 bShowBestPath : 1;`
- L71 _private member_ `uint32 bShowNodePool : 1;`
- L72 _private member_ `uint32 bShowDiff : 1;`
- L74 _private member_ `ANavigationTestingActor* NavTestActor;`
- L75 _private member_ `TArray<FVector> PathPoints;`
- L76 _private member_ `TArray<FString> PathPointFlags;`
- L78 _private member_ `TArray<FDynamicMeshVertex> OpenSetVerts;`
- L79 _private member_ `TArray<uint32> OpenSetIndices;`
- L80 _private member_ `TArray<FDynamicMeshVertex> ClosedSetVerts;`
- L81 _private member_ `TArray<uint32> ClosedSetIndices;`
- L82 _private member_ `TSet<FNodeDebugData> NodeDebug;`
- L83 _private member_ `FSetElementId BestNodeId;`
- L85 _private member_ `FVector ClosestWallLocation;`

#### struct `FNavTestSceneProxy::FNodeDebugData`  
`struct FNodeDebugData`  
_L27-46_
- L29 _public member_ `NavNodeRef PolyRef;`
- L30 _public member_ `FVector Position;`
- L31 _public member_ `FString Desc;`
- L32 _public member_ `FSetElementId ParentId;`
- L33 _public member_ `uint32 bClosedSet : 1;`
- L34 _public member_ `uint32 bBestPath : 1;`
- L35 _public member_ `uint32 bModified : 1;`
- L36 _public member_ `uint32 bOffMeshLink : 1;`
- L38 _public function_ `inline bool operator==(const FNodeDebugData& Other) const`

#### class `FNavTestDebugDrawDelegateHelper`  
`class FNavTestDebugDrawDelegateHelper : public FDebugDrawDelegateHelper`  
_L88-110_
- inherits: `FDebugDrawDelegateHelper`
- L90 _private typedef_ `typedef FDebugDrawDelegateHelper Super;`
- L93 _public function_ `FNavTestDebugDrawDelegateHelper(): bShowBestPath(false), bShowDiff(false)`
- L97 _public prototype_ `void SetupFromProxy(const FNavTestSceneProxy* InSceneProxy);`
- L100 _protected prototype_ `virtual void DrawDebugLabels(UCanvas* Canvas, APlayerController*) override;`
- L103 _private member_ `TSet<FNavTestSceneProxy::FNodeDebugData> NodeDebug;`
- L104 _private member_ `ANavigationTestingActor* NavTestActor = nullptr;`
- L105 _private member_ `TArray<FVector> PathPoints;`
- L106 _private member_ `TArray<FString> PathPointFlags;`
- L107 _private member_ `FSetElementId BestNodeId;`
- L108 _private member_ `uint32 bShowBestPath : 1;`
- L109 _private member_ `uint32 bShowDiff : 1;`

#### class `UNavTestRenderingComponent`  
`class UNavTestRenderingComponent: public UDebugDrawComponent`  
_L115-129_
- reflection: `UCLASS(ClassGroup = Debug)`
- inherits: `UDebugDrawComponent`
- L121 _protected prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform &LocalToWorld) const override;`
- L124 _protected prototype_ `virtual FDebugRenderSceneProxy* CreateDebugSceneProxy() override;`
- L125 _protected function_ `virtual FDebugDrawDelegateHelper& GetDebugDrawDelegateHelper() override`
- L127 _private member_ `FNavTestDebugDrawDelegateHelper NavTestDebugDrawDelegateHelper;`

### `Source/Runtime/NavigationSystem/Public/NavMesh/PImplRecastNavMesh.h` (Public)


#### class `FPImplRecastNavMesh`  
`class FPImplRecastNavMesh`  
_L35-332_
- desc: Engine Private! - Private Implementation details of ARecastNavMesh
- L40 _public prototype_ `FPImplRecastNavMesh(ARecastNavMesh* Owner);` — Constructor
- L43 _public prototype_ `~FPImplRecastNavMesh();` — Dtor
- L50 _public prototype_ `void Serialize(FArchive& Ar, int32 NavMeshVersion);` — Serialization. @param Ar - The archive with which to serialize. @returns true if serialization was successful.
- L58 _public prototype_ `bool GetDebugGeometryForTile(FRecastDebugGeometry& OutGeometry, int32 TileIndex) const;` — `UE_DEPRECATED(5.5, "Use the version of this function that takes a FNavTileRef instead.")` — Gather debug geometry. @params OutGeometry Output geometry. @params TileIndex Used to collect geometry for a specific tile, INDEX_NONE will gather all tiles. @return True if done collecting.
- L65 _public prototype_ `bool GetDebugGeometryForTile(FRecastDebugGeometry& OutGeometry, FNavTileRef TileRef) const;` — Gather debug geometry. @params OutGeometry Output geometry. @params TileRef Used to collect geometry for a specific tile, an invalid FNavTileRef will gather all tiles. @return True if done collecting.
- L68 _public prototype_ `FBox GetNavMeshBounds() const;` — Returns bounding box for the whole navmesh.
- L71 _public prototype_ `bool GetNavMeshTileXY(const FVector& Point, int32& OutX, int32& OutY) const;` — Retrieves XY coordinates of tile specified by position
- L74 _public prototype_ `void GetNavMeshTilesIn(const TArray<FBox>& InclusionBounds, TArray<FNavTileRef>& OutRefs) const;` — Retrieves list of tiles that intersect specified bounds
- L77 _public function_ `inline int32 GetNavMeshTilesCount() const` — Retrieves number of tiles in this navmesh
- L82 _public prototype_ `ENavigationQueryResult::Type FindPath(const FVector& StartLoc, const FVector& EndLoc, const FVector::FReal CostLimit, const bool bRequireNavigableEndLocation, FNavMeshPath& Path, const FNavigationQueryFilter& Filter, const UObject* Owner) const;` — Generates path from the given query. Synchronous.
- L85 _public prototype_ `ENavigationQueryResult::Type TestPath(const FVector& StartLoc, const FVector& EndLoc, const bool bRequireNavigableEndLocation, const FNavigationQueryFilter& Filter, const UObject* Owner, int32* NumVisitedNodes = 0) const;` — Check if path exists
- L88 _public prototype_ `template< typename TRecastAStar, typename TRecastAStartGraph, typename TRecastGraphAStarFilter, typename TRecastAStarResult > ENavigationQueryResult::Type FindPathCustomAStar(TRecastAStartGraph& RecastGraphWrapper, TRecastAStar& AStarAlgo, const FVector& StartLoc, const FVector& EndLoc, const FVector::FReal CostLimit, FNavMeshPath& Path, const FNavigationQueryFilter& Filter, const UObject* Owner) const;`
- L91 _public prototype_ `void Raycast(const FVector& StartLoc, const FVector& EndLoc, const FNavigationQueryFilter& InQueryFilter, const UObject* Owner, ARecastNavMesh::FRaycastResult& RaycastResult, NavNodeRef StartNode = INVALID_NAVNODEREF) const;` — Checks if the whole segment is in navmesh
- L95 _public prototype_ `int32 DebugPathfinding(const FVector& StartLoc, const FVector& EndLoc, const FVector::FReal CostLimit, const bool bRequireNavigableEndLocation, const FNavigationQueryFilter& Filter, const UObject* Owner, TArray<FRecastDebugPathfindingData>& Steps);` — Generates path from given query and collect data for every step of A* algorithm
- L98 _public prototype_ `FNavLocation GetRandomPoint(const FNavigationQueryFilter& Filter, const UObject* Owner) const;` — Returns a random location on the navmesh.
- L102 _public prototype_ `ENavigationQueryResult::Type TestClusterPath(const FVector& StartLoc, const FVector& EndLoc, int32* NumVisitedNodes = 0) const;` — Check if path exists using cluster graph
- L105 _public prototype_ `bool GetRandomPointInCluster(NavNodeRef ClusterRef, FNavLocation& OutLocation) const;` — Returns a random location on the navmesh within cluster
- L112 _public prototype_ `bool FindMoveAlongSurface(const FNavLocation& StartLocation, const FVector& TargetPosition, FNavLocation& OutLocation, const FNavigationQueryFilter& Filter, const UObject* Owner) const;` — Tries to move current nav location towards target constrained to navigable area. Faster than ProjectPointToNavmesh. @param OutLocation if successful this variable will be filed with result @return true if successful, false otherwise
- L114 _public prototype_ `bool ProjectPointToNavMesh(const FVector& Point, FNavLocation& Result, const FVector& Extent, const FNavigationQueryFilter& Filter, const UObject* Owner) const;`
- L117 _public prototype_ `bool ProjectPointMulti(const FVector& Point, TArray<FNavLocation>& OutLocations, const FVector& Extent, FVector::FReal MinZ, FVector::FReal MaxZ, const FNavigationQueryFilter& Filter, const UObject* Owner) const;` — Project single point and grab all vertical intersections
- L121 _public prototype_ `NavNodeRef FindNearestPoly(FVector const& Loc, FVector const& Extent, const FNavigationQueryFilter& Filter, const UObject* Owner) const;` — Returns nearest navmesh polygon to Loc, or INVALID_NAVNODEREF if Loc is not on the navmesh.
- L124 _public prototype_ `bool FindPolysAroundCircle(const FVector& CenterPos, const NavNodeRef CenterNodeRef, const FVector::FReal Radius, const FNavigationQueryFilter& Filter, const UObject* Owner, TArray<NavNodeRef>* OutPolys = nullptr, TArray<NavNodeRef>* OutPolysParent = nullptr, TArray<float>* OutPolysCost = nullptr, int32* OutPolysCount = nullptr) const;` — Finds the polygons along the navigation graph that touch the specified circle. Return true if found any.
- L130 _public prototype_ `bool GetPolysWithinPathingDistance(FVector const& StartLoc, const FVector::FReal PathingDistance, const FNavigationQueryFilter& Filter, const UObject* Owner, TArray<NavNodeRef>& FoundPolys, FRecastDebugPathfindingData* DebugData) const;` — Retrieves all polys within given pathing distance from StartLocation. @NOTE query is not using string-pulled path distance (for performance reasons), it measured distance between middles of portal edges, do you might want to add an extra margin to PathingDistance
- L135 _public prototype_ `void GetEdgesForPathCorridor(const TArray<NavNodeRef>* PathCorridor, TArray<FNavigationPortalEdge>* PathCorridorEdges) const;` — @todo document
- L138 _public prototype_ `bool FindStraightPath(const FVector& StartLoc, const FVector& EndLoc, const TArray<NavNodeRef>& PathCorridor, TArray<FNavPathPoint>& PathPoints, TArray<FNavLinkId>* CustomLinks = NULL) const;` — finds stringpulled path from given corridor
- L141 _public prototype_ `bool FilterPolys(TArray<NavNodeRef>& PolyRefs, const FRecastQueryFilter* Filter, const UObject* Owner) const;` — Filters nav polys in PolyRefs with Filter
- L145 _public prototype_ `bool GetPolysInTile(int32 TileIndex, TArray<FNavPoly>& Polys) const;` — `UE_DEPRECATED(5.5, "Use the version of this function in ARecastNavMesh that takes a FNavTileRef instead.")` — Get all polys from tile
- L148 _public prototype_ `void UpdateNavigationLinkArea(FNavLinkId UserId, uint8 AreaType, uint16 PolyFlags) const;` — Updates area on polygons creating point-to-point connection with given UserId
- L152 _public prototype_ `void UpdateSegmentLinkArea(int32 UserId, uint8 AreaType, uint16 PolyFlags) const;` — Updates area on polygons creating segment-to-segment connection with given UserId
- L155 _public prototype_ `void ProcessSegmentLinksForTile(FNavTileRef TileRef) const;` — Creates segment link connections for the give tile
- L158 _public prototype_ `void ProcessSegmentLinksForTile(FNavTileRef TileRef, uint32 MaxSkippedNeigborTiles, dtTileRef* OutSkippedNeigborTiles, uint32& OutNumSkippedNeigborTiles) const;` — Creates segment link connections for the give tile and stores the list of indices skipped to avoid generating duplicate links
- L162 _public prototype_ `bool GetPolyCenter(NavNodeRef PolyID, FVector& OutCenter) const;` — Retrieves center of the specified polygon. Returns false on error.
- L164 _public prototype_ `bool GetPolyVerts(NavNodeRef PolyID, TArray<FVector>& OutVerts) const;` — Retrieves the vertices for the specified polygon. Returns false on error.
- L166 _public prototype_ `bool GetRandomPointInPoly(NavNodeRef PolyID, FVector& OutPoint) const;` — Retrieves a random point inside the specified polygon. Returns false on error.
- L168 _public prototype_ `FVector::FReal GetPolySurfaceArea(NavNodeRef PolyID) const;` — Retrieves the surface area of the specified polygon. Returns 0 on error.
- L170 _public prototype_ `bool GetPolyData(NavNodeRef PolyID, uint16& Flags, uint8& AreaType) const;` — Retrieves the flags for the specified polygon. Returns false on error.
- L172 _public prototype_ `uint32 GetPolyAreaID(NavNodeRef PolyID) const;` — Retrieves area ID for the specified polygon.
- L174 _public prototype_ `void SetPolyAreaID(NavNodeRef PolyID, uint8 AreaID);` — Sets area ID for the specified polygon.
- L176 _public prototype_ `bool GetPolyNeighbors(NavNodeRef PolyID, TArray<FNavigationPortalEdge>& Neighbors) const;` — Finds all polys connected with specified one
- L178 _public prototype_ `bool GetPolyNeighbors(NavNodeRef PolyID, TArray<NavNodeRef>& Neighbors) const;` — Finds all polys connected with specified one, results expressed as array of NavNodeRefs
- L180 _public prototype_ `bool GetPolyEdges(NavNodeRef PolyID, TArray<FNavigationPortalEdge>& Edges) const;` — Finds all polys connected with specified one
- L182 _public prototype_ `bool GetPolyWallSegments(NavNodeRef PolyID, const FNavigationQueryFilter& InQueryFilter, const UObject* QueryOwner, TArray<FNavigationPortalEdge>& OutNeighbors) const;` — Finds all wall segments for the specified polygon (walls or area borders)
- L184 _public prototype_ `bool GetClosestPointOnPoly(NavNodeRef PolyID, const FVector& TestPt, FVector& PointOnPoly) const;` — Finds closest point constrained to given poly
- L186 _public prototype_ `bool GetPolyTileIndex(NavNodeRef PolyID, uint32& PolyIndex, uint32& TileIndex) const;` — Decode poly ID into tile index and poly index
- L188 _public prototype_ `bool GetPolyTileRef(NavNodeRef PolyId, uint32& OutPolyIndex, FNavTileRef& OutTileRef) const;` — Decode poly ID into FNavTileRef and poly index
- L191 _public function_ `uint32 GetLinkUserId(NavNodeRef LinkPolyID) const` — `UE_DEPRECATED(5.3, "Please use GetNavLinkUserId() instead. This function only returns Invalid.")` — Retrieves user ID for given offmesh link poly
- L195 _public prototype_ `FNavLinkId GetNavLinkUserId(NavNodeRef LinkPolyID) const;`
- L197 _public prototype_ `bool GetLinkEndPoints(NavNodeRef LinkPolyID, FVector& PointA, FVector& PointB) const;` — Retrieves start and end point of offmesh link
- L199 _public prototype_ `bool IsCustomLink(NavNodeRef PolyRef) const;` — Check if poly is a custom link
- L203 _public prototype_ `bool GetClusterBounds(NavNodeRef ClusterRef, FBox& OutBounds) const;` — Retrieves bounds of cluster. Returns false on error.
- L204 _public prototype_ `NavNodeRef GetClusterRefFromPolyRef(const NavNodeRef PolyRef) const;`
- L207 _public function_ `uint32 GetTileIndexFromPolyRef(const NavNodeRef PolyRef) const`
- L209 _public prototype_ `static uint16 GetFilterForbiddenFlags(const FRecastQueryFilter* Filter);`
- L210 _public prototype_ `static void SetFilterForbiddenFlags(FRecastQueryFilter* Filter, uint16 ForbiddenFlags);`
- L212 _public prototype_ `void OnAreaCostChanged();`
- L215 _public function_ `dtNavMesh const* GetRecastMesh() const`
- L216 _public function_ `dtNavMesh* GetRecastMesh()`
- L217 _public prototype_ `void ReleaseDetourNavMesh();`
- L219 _public prototype_ `void RemoveTileCacheLayers(int32 TileX, int32 TileY);`
- L220 _public prototype_ `void RemoveTileCacheLayer(int32 TileX, int32 TileY, int32 LayerIdx);`
- L221 _public prototype_ `void AddTileCacheLayers(int32 TileX, int32 TileY, const TArray<FNavMeshTileData>& Layers);`
- L222 _public prototype_ `void AddTileCacheLayer(int32 TileX, int32 TileY, int32 LayerIdx, const FNavMeshTileData& LayerData);`
- L223 _public prototype_ `void MarkEmptyTileCacheLayers(int32 TileX, int32 TileY);`
- L224 _public prototype_ `FNavMeshTileData GetTileCacheLayer(int32 TileX, int32 TileY, int32 LayerIdx) const;`
- L225 _public prototype_ `TArray<FNavMeshTileData> GetTileCacheLayers(int32 TileX, int32 TileY) const;`
- L226 _public prototype_ `bool HasTileCacheLayers(int32 TileX, int32 TileY) const;`
- L232 _public prototype_ `void SetRecastMesh(dtNavMesh* NavMesh);` — Assigns recast generated navmesh to this instance. @param bOwnData if true from now on this FPImplRecastNavMesh instance will be responsible for this piece of memory
- L234 _public prototype_ `SIZE_T GetTotalDataSize() const;`
- L238 _public prototype_ `int32 GetCompressedTileCacheSize();`
- L242 _public prototype_ `void ApplyWorldOffset(const FVector& InOffset, bool bWorldShift);` — Called on world origin changes
- L247 _public prototype_ `FVector::FReal CalcSegmentCostOnPoly(NavNodeRef PolyID, const dtQueryFilter* Filter, const FVector& StartLoc, const FVector& EndLoc) const;` — calculated cost of given segment if traversed on specified poly. Function measures distance between specified points and returns cost of traversing this distance on given poly. @note no check if segment is on poly is performed.
- L249 _public member_ `ARecastNavMesh* NavMeshOwner;`
- L252 _public member_ `dtNavMesh* DetourNavMesh;` — Recast's runtime navmesh data that we can query against
- L255 _public member_ `TMap<FIntPoint, TArray<FNavMeshTileData> > CompressedTileCacheLayers;` — Compressed layers data, can be reused for tiles generation
- L258 _public member_ `TMap<FIntPoint, FRecastInternalDebugData> DebugDataMap;`
- L262 _public member_ `mutable dtNavMeshQuery SharedNavQuery;` — query used for searching data on game thread
- L265 _public prototype_ `static void SerializeRecastMeshTile(FArchive& Ar, int32 NavMeshVersion, unsigned char*& TileData, int32& TileDataSize);` — Helper function to serialize a single Recast tile.
- L268 _public prototype_ `static void SerializeCompressedTileCacheData(FArchive& Ar, int32 NavMeshVersion, unsigned char*& CompressedData, int32& CompressedDataSize);` — Helper function to serialize a Recast tile compressed data.
- L281 _public prototype_ `bool InitPathfinding(const FVector& UnrealStart, const FVector& UnrealEnd, const dtNavMeshQuery& Query, const dtQueryFilter* Filter, FVector& RecastStart, dtPolyRef& StartPoly, FVector& RecastEnd, dtPolyRef& EndPoly, FNavMeshPath* OutPath = nullptr) const;` — Initialize data for pathfinding @param UnrealStart Start location for the desired path @param UnrealEnd End location for the desired path @param Query Query to use to project start and end position to the navmesh @param Filter Filters which polygons are acceptable to project start and end locations @param RecastStart Outputs the start location snapped to the navmesh @param StartPoly Outputs the navmesh poly at the start location @param RecastEnd Outputs the end location snapped to the navmesh. Equal to UnrealEnd when there's no navmesh at the end location. @param EndPoly Outputs the navmesh poly at the end location. Invalid when there's no navmesh at the end location @param OutPath [optional] When provided, Path will be used to store relevant error codes that this method can produce
- L288 _public prototype_ `void PostProcessPath(dtStatus PathfindResult, FNavMeshPath& Path, const dtNavMeshQuery& Query, const dtQueryFilter* Filter, NavNodeRef StartNode, NavNodeRef EndNode, FVector UnrealStart, FVector UnrealEnd, FVector RecastStart, FVector RecastEnd, dtQueryResult& PathResult) const;` — Marks path flags, perform string pulling if needed
- L296 _public prototype_ `void GetDebugPolyEdges(const dtMeshTile& Tile, bool bInternalEdges, bool bNavMeshEdges, TArray<FVector>& InternalEdgeVerts, TArray<FVector>& NavMeshEdgeVerts) const;` — `UE_DEPRECATED(5.5, "Use GetTilePolyEdges instead.")`
- L308 _public prototype_ `void GetTilePolyEdges(const dtMeshTile& Tile, bool bGatherInteriorPolyEdges, bool bGatherExteriorNavMeshEdges, TArray<FVector>& OutInteriorPolyEdgeVerts, TArray<FVector>& OutExteriorNavMeshEdgeVerts) const;` — Traverses given tile's edges and detects the ones that are either internal poly (i.e. not triangle, but whole navmesh polygon) or external navmesh edge. Returns a pair of verts for each edge found. @param Tile The tile whose edges to traverse. @param bGatherInteriorPolyEdges If true, populates OutPolyEdgeVerts with the tile's internal poly edges. @param bGatherExternalNavMeshEdges If true, populates OutNavMeshEdgeVerts with the tile's external navmesh edges. @param OutInteriorPolyEdgeVerts Output poly edge vertex array. Contains a pair of verts for each edge. @param OutExteriorNavMeshEdgeVerts Output navmesh edge vertex array. Contains a pair of verts for each edge. @note This is really slow.
- L311 _public prototype_ `void GetEdgesForPathCorridorImpl(const TArray<NavNodeRef>* PathCorridor, TArray<FNavigationPortalEdge>* PathCorridorEdges, const dtNavMeshQuery& NavQuery) const;` — workhorse function finding portal edges between corridor polys
- L319 _public prototype_ `void GetTilePolyEdgesForFilter(const dtMeshTile& Tile, const FNavigationQueryFilter& InQueryFilter, TArray<FNavigationWallEdge>& OutEdges) const;` — Traverse a tile and returns a list of all the edges around the passed in filter. @param Tile The tile whose edges to traverse. @param InQueryFilter the filter used to determine if an edge should be considered a border @param OutEdges Output edges array
- L325 _protected prototype_ `int32 GetTilesDebugGeometry(const FRecastNavMeshGenerator* Generator, const dtMeshTile& Tile, int32 VertBase, FRecastDebugGeometry& OutGeometry, int32 TileIdx = INDEX_NONE, uint16 ForbiddenFlags = 0) const;` — @param ForbiddenFlags polys with flags matching the filter will get added to
- L327 _protected prototype_ `ENavigationQueryResult::Type PostProcessPathInternal(dtStatus FindPathStatus, FNavMeshPath& Path, const dtNavMeshQuery& NavQuery, const dtQueryFilter* QueryFilter, NavNodeRef StartPolyID, NavNodeRef EndPolyID, const FVector& RecastStartPos, const FVector& RecastEndPos, dtQueryResult& PathResult) const;`
- L335 _function_ `template< typename TRecastAStar, typename TRecastAStartGraph, typename TRecastGraphAStarFilter, typename TRecastAStarResult > ENavigationQueryResult::Type FPImplRecastNavMesh::FindPathCustomAStar(TRecastAStartGraph& RecastGraphWrapper, TRecastAStar& AStarAlgo, const FVector& StartLoc, const FVector& EndLoc, const FVector::FReal CostLimit, FNavMeshPath& Path, const FNavigationQueryFilter& InQueryFilter, const UObject* Owner) const`

#### Free symbols / members of external scopes

- L32 _macro_ `#define RECAST_VERY_SMALL_AGENT_RADIUS 0.0f`

### `Source/Runtime/NavigationSystem/Public/NavMesh/RecastGeometryExport.h` (Public)


#### struct `FRecastGeometryExport`  
`struct FRecastGeometryExport : public FNavigableGeometryExport`  
_L15-86_
- inherits: `FNavigableGeometryExport`
- desc: Class that handles geometry exporting for Recast navmesh generation.
- L17 _public prototype_ `FRecastGeometryExport(FNavigationRelevantData& InData);`
- L19 _public member_ `FNavigationRelevantData* Data;`
- L20 _public member_ `TNavStatArray<FVector::FReal> VertexBuffer;`
- L21 _public member_ `TNavStatArray<int32> IndexBuffer;`
- L22 _public member_ `FWalkableSlopeOverride SlopeOverride;`
- L25 _public prototype_ `virtual void ExportChaosTriMesh(const Chaos::FTriangleMeshImplicitObject* const TriMesh, const FTransform& LocalToWorld) override;` — Export the collision of a Chaos triangle mesh into the Vertex and Index buffer.
- L27 _public prototype_ `virtual void ExportChaosConvexMesh(const FKConvexElem* const Convex, const FTransform& LocalToWorld) override;` — Export the collision of a Chaos convex mesh into the Vertex and Index buffer.
- L29 _public prototype_ `virtual void ExportChaosHeightField(const Chaos::FHeightField* const Heightfield, const FTransform& LocalToWorld) override;` — Export the collision of a Chaos height field into the Vertex and Index buffer.
- L32 _public prototype_ `virtual void ExportChaosHeightFieldSlice(const FNavHeightfieldSamples& PrefetchedHeightfieldSamples, const int32 NumRows, const int32 NumCols, const FTransform& LocalToWorld, const FBox& SliceBox) override;` — Export a slice of the collision of a Chaos height field into the Vertex and Index buffer. @param SliceBox Box that defines the slice we want to extract from the height field
- L34 _public prototype_ `virtual void ExportCustomMesh(const FVector* InVertices, int32 NumVerts, const int32* InIndices, int32 NumIndices, const FTransform& LocalToWorld) override;` — Export a custom mesh into the Vertex and Index buffer.
- L36 _public prototype_ `virtual void ExportRigidBodySetup(UBodySetup& BodySetup, const FTransform& LocalToWorld) override;` — Export a rigid body into the Vertex and Index buffer.
- L38 _public prototype_ `virtual void AddNavModifiers(const FCompositeNavModifier& Modifiers) override;` — Add Nav Modifiers to the owned NavigationRelevantData.
- L40 _public prototype_ `virtual void SetNavDataPerInstanceTransformDelegate(const FNavDataPerInstanceTransformDelegate& InDelegate) override;` — Optional delegate for geometry per instance transforms.
- L43 _public prototype_ `void ConvertVertexBufferToRecast();` — Convert the vertices in VertexBuffer from Unreal to Recast coordinates.
- L45 _public prototype_ `void StoreCollisionCache();` — Store Vertex and Index buffer data in associated FNavigationRelevantData.
- L48 _public prototype_ `static void ExportElementGeometry(const FNavigationElement& InElement, FNavigationRelevantData& OutData);` — Collects the collision information from a navigation element and stores it into the FNavigationRelevantData's CollisionData.
- L52 _public prototype_ `static void ExportVertexSoupGeometry(const TArray<FVector>& InVerts, FNavigationRelevantData& OutData);` — Convert a list of vertices into the navigation format and store it into the FNavigationRelevantData's CollisionData. @param InVerts Array of triangles vertices position. Each triangle will be created from 3 consecutive vertices in the array. Its size must be a multiple a 3.
- L55 _public prototype_ `static void ExportRigidBodyGeometry(UBodySetup& InOutBodySetup, TNavStatArray<FVector>& OutVertexBuffer, TNavStatArray<int32>& OutIndexBuffer, FBox& OutBounds, const FTransform& LocalToWorld = FTransform::Identity);` — Collect the collision information of a BodySetup as a triangle mesh.
- L62 _public prototype_ `static void ExportRigidBodyGeometry( UBodySetup& InOutBodySetup, TNavStatArray<FVector>& OutTriMeshVertexBuffer, TNavStatArray<int32>& OutTriMeshIndexBuffer, TNavStatArray<FVector>& OutConvexVertexBuffer, TNavStatArray<int32>& OutConvexIndexBuffer, TNavStatArray<int32>& OutShapeBuffer, FBox& OutBounds, const FTransform& LocalToWorld = FTransform::Identity);` — Collect the collision information of a BodySetup as a triangle mesh and a series of convex shapes.
- L73 _public prototype_ `static void ExportAggregatedGeometry( const FKAggregateGeom& AggGeom, TNavStatArray<FVector>& OutConvexVertexBuffer, TNavStatArray<int32>& OutConvexIndexBuffer, TNavStatArray<int32>& OutShapeBuffer, FBox& OutBounds, const FTransform& LocalToWorld = FTransform::Identity);` — Collect the collision information of an AggregateGeometry as a series of convex shapes.
- L82 _public prototype_ `static void TransformVertexSoupToRecast(const TArray<FVector>& VertexSoup, TNavStatArray<FVector>& Verts, TNavStatArray<int32>& Faces);` — Transform a list of vertex triplets from Unreal to Recast coordinate and generate an Index buffer.
- L85 _private prototype_ `FString GetDataOwnerName() const;`

### `Source/Runtime/NavigationSystem/Public/NavMesh/RecastHelpers.h` (Public)


#### Free symbols / members of external scopes

- L19 _prototype_ `extern FVector Unreal2RecastPoint(const FVector::FReal* UnrealPoint);`
- L20 _prototype_ `extern FVector Unreal2RecastPoint(const FVector& UnrealPoint);`
- L21 _prototype_ `extern FBox Unreal2RecastBox(const FBox& UnrealBox);`
- L22 _prototype_ `extern FMatrix Unreal2RecastMatrix();`
- L24 _prototype_ `extern FVector Recast2UnrealPoint(const FVector::FReal* RecastPoint);`
- L25 _prototype_ `extern FVector Recast2UnrealPoint(const FVector& RecastPoint);`
- L27 _prototype_ `extern FBox Recast2UnrealBox(const FVector::FReal* RecastMin, const FVector::FReal* RecastMax);`
- L28 _prototype_ `extern FBox Recast2UnrealBox(const FBox& RecastBox);`
- L29 _prototype_ `extern FMatrix Recast2UnrealMatrix();`
- L30 _prototype_ `extern FColor Recast2UnrealColor(const unsigned int RecastColor);`

### `Source/Runtime/NavigationSystem/Public/NavMesh/RecastInternalDebugData.h` (Public)


#### struct `FRecastInternalDebugData`  
`struct FRecastInternalDebugData : public duDebugDraw`  
_L15-73_
- inherits: `duDebugDraw`
- L17 _public member_ `duDebugDrawPrimitives CurrentPrim = DU_DRAW_POINTS;`
- L18 _public member_ `int32 FirstVertexIndex = 0;`
- L20 _public member_ `TArray<uint32> TriangleIndices;`
- L21 _public member_ `TArray<FVector> TriangleVertices;`
- L22 _public member_ `TArray<FColor> TriangleColors;`
- L24 _public member_ `TArray<FVector> LineVertices;`
- L25 _public member_ `TArray<FColor> LineColors;`
- L27 _public member_ `TArray<FVector> PointVertices;`
- L28 _public member_ `TArray<FColor> PointColors;`
- L30 _public member_ `TArray<FVector> LabelVertices;`
- L31 _public member_ `TArray<FString> Labels;`
- L33 _public member_ `double BuildTime = 0.;`
- L34 _public member_ `double BuildCompressedLayerTime = 0.;`
- L35 _public member_ `double BuildNavigationDataTime = 0.;`
- L36 _public member_ `double BuildLinkTime = 0;`
- L38 _public member_ `uint32 TriangleCount = 0;`
- L39 _public member_ `unsigned char Resolution = 0;`
- L41 _public function_ `FRecastInternalDebugData()`
- L42 _public prototype_ `virtual ~FRecastInternalDebugData() override = default;`
- L44 _public function_ `virtual void depthMask(bool state) override`
- L45 _public function_ `virtual void texture(bool state) override`
- L47 _public function_ `virtual void begin(duDebugDrawPrimitives prim, float size = 1.0f) override`
- L53 _public function_ `virtual void vertex(const FVector::FReal* pos, unsigned int color) override`
- L58 _public function_ `virtual void vertex(const FVector::FReal x, const FVector::FReal y, const FVector::FReal z, unsigned int color) override`
- L63 _public function_ `virtual void vertex(const FVector::FReal* pos, unsigned int color, const FVector::FReal* uv) override`
- L68 _public prototype_ `virtual void vertex(const FVector::FReal x, const FVector::FReal y, const FVector::FReal z, unsigned int color, const FVector::FReal u, const FVector::FReal v) override;`
- L70 _public prototype_ `virtual void text(const FVector::FReal x, const FVector::FReal y, const FVector::FReal z, const char* text) override;`
- L72 _public prototype_ `virtual void end() override;`

### `Source/Runtime/NavigationSystem/Public/NavMesh/RecastNavMesh.h` (Public)


#### enum `ERecastPartitioning::Type`  
`enum Type : int`  
_L68-73_
- L70 _public enumerator_ `Monotone`
- L71 _public enumerator_ `Watershed`
- L72 _public enumerator_ `ChunkyMonotone`

#### enum `ENavigationLedgeSlopeFilterMode`  
`enum class ENavigationLedgeSlopeFilterMode : uint8`  
_L77-82_
- reflection: `UENUM()`
- L79 _public enumerator_ `Recast` — Use walkableClimb value to filter
- L80 _public enumerator_ `None` — Skip slope filtering
- L81 _public enumerator_ `UseStepHeightFromAgentMaxSlope` — Use maximum step height computed from AgentMaxSlope

#### struct `FDetourTileSizeInfo`  
`struct FDetourTileSizeInfo`  
_L84-97_
- L86 _public member_ `unsigned short VertCount = 0;`
- L87 _public member_ `unsigned short PolyCount = 0;`
- L88 _public member_ `unsigned short MaxLinkCount = 0;`
- L89 _public member_ `unsigned short DetailMeshCount = 0;`
- L90 _public member_ `unsigned short DetailVertCount = 0;`
- L91 _public member_ `unsigned short DetailTriCount = 0;`
- L92 _public member_ `unsigned short BvNodeCount = 0;`
- L93 _public member_ `unsigned short OffMeshConCount = 0;`
- L94 _public member_ `unsigned short OffMeshSegConCount = 0;`
- L95 _public member_ `unsigned short ClusterCount = 0;`
- L96 _public member_ `unsigned short OffMeshBase = 0;`

#### struct `FDetourTileLayout`  
`struct FDetourTileLayout`  
_L99-121_
- L101 _public prototype_ `FDetourTileLayout(const dtMeshTile& tile);`
- L102 _public prototype_ `FDetourTileLayout(const FDetourTileSizeInfo& SizeInfo);`
- L105 _private prototype_ `void InitFromSizeInfo(const FDetourTileSizeInfo& SizeInfo);`
- L108 _public member_ `int32 HeaderSize = 0;`
- L109 _public member_ `int32 VertsSize = 0;`
- L110 _public member_ `int32 PolysSize = 0;`
- L111 _public member_ `int32 LinksSize = 0;`
- L112 _public member_ `int32 DetailMeshesSize = 0;`
- L113 _public member_ `int32 DetailVertsSize = 0;`
- L114 _public member_ `int32 DetailTrisSize = 0;`
- L115 _public member_ `int32 BvTreeSize = 0;`
- L116 _public member_ `int32 OffMeshConsSize = 0;`
- L117 _public member_ `int32 OffMeshSegsSize = 0;`
- L118 _public member_ `int32 ClustersSize = 0;`
- L119 _public member_ `int32 PolyClustersSize = 0;`
- L120 _public member_ `int32 TileSize = 0;`

#### struct `FRecastDebugPathfindingNode`  
`struct FRecastDebugPathfindingNode`  
_L136-160_
- L138 _public member_ `NavNodeRef PolyRef;`
- L139 _public member_ `NavNodeRef ParentRef;`
- L140 _public member_ `FVector::FReal Cost = 0.;`
- L141 _public member_ `FVector::FReal TotalCost = 0.;`
- L142 _public member_ `FVector::FReal Length = 0.;`
- L144 _public member_ `FVector NodePos;`
- L145 _public member_ `TArray<FVector3f, TInlineAllocator<6> > Verts;` — LWC_TODO: Precision loss. Issue here is regarding debug rendering needing to work with FVector3f.
- L146 _public member_ `uint8 NumVerts;`
- L148 _public member_ `uint8 bOpenSet : 1;`
- L149 _public member_ `uint8 bOffMeshLink : 1;`
- L150 _public member_ `uint8 bModified : 1;`
- L152 _public function_ `FRecastDebugPathfindingNode() : PolyRef(0), ParentRef(0), NumVerts(0), bOpenSet(0), bOffMeshLink(0), bModified(0)`
- L153 _public function_ `FRecastDebugPathfindingNode(NavNodeRef InPolyRef) : PolyRef(InPolyRef), ParentRef(0), NumVerts(0), bOpenSet(0), bOffMeshLink(0), bModified(0)`
- L155 _public function_ `inline bool operator==(const NavNodeRef& OtherPolyRef) const`
- L156 _public function_ `inline bool operator==(const FRecastDebugPathfindingNode& Other) const`
- L159 _public function_ `inline FVector::FReal GetHeuristicCost() const`

#### enum `ERecastDebugPathfindingFlags::Type`  
`enum Type : uint8`  
_L164-170_
- L166 _public enumerator_ `Basic = 0x0`
- L167 _public enumerator_ `BestNode = 0x1`
- L168 _public enumerator_ `Vertices = 0x2`
- L169 _public enumerator_ `PathLength = 0x4`

#### struct `FRecastDebugPathfindingData`  
`struct FRecastDebugPathfindingData`  
_L173-181_
- L175 _public member_ `TSet<FRecastDebugPathfindingNode> Nodes;`
- L176 _public member_ `FSetElementId BestNode;`
- L177 _public member_ `uint8 Flags;`
- L179 _public function_ `FRecastDebugPathfindingData() : Flags(ERecastDebugPathfindingFlags::Basic)`
- L180 _public function_ `FRecastDebugPathfindingData(ERecastDebugPathfindingFlags::Type InFlags) : Flags(InFlags)`

#### struct `FRecastDebugGeometry`  
`struct FRecastDebugGeometry`  
_L183-271_
- L231 _public member_ `static constexpr int32 BuildTimeBucketsCount = 5;`
- L233 _public member_ `TArray<FVector> MeshVerts;`
- L235 _public member_ `TArray<int32> AreaIndices[RECAST_MAX_AREAS];`
- L236 _public member_ `TArray<int32> ForbiddenIndices;`
- L237 _public member_ `TArray<int32> BuiltMeshIndices;`
- L238 _public member_ `TArray<int32> TileBuildTimesIndices[BuildTimeBucketsCount];`
- L240 _public member_ `TArray<FVector> PolyEdges;`
- L241 _public member_ `TArray<FVector> NavMeshEdges;`
- L242 _public member_ `TArray<FOffMeshLink> OffMeshLinks;`
- L243 _public member_ `TArray<FOffMeshLink> ForbiddenLinks;`
- L246 _public member_ `TArray<FCluster> Clusters;`
- L247 _public member_ `TArray<FClusterLink> ClusterLinks;`
- L251 _public member_ `TArray<FOffMeshSegment> OffMeshSegments;`
- L252 _public member_ `TArray<int32> OffMeshSegmentAreas[RECAST_MAX_AREAS];`
- L256 _public member_ `TArray<FIntPoint> TilesToDisplayInternalData;`
- L259 _public member_ `uint32 bGatherPolyEdges : 1;`
- L260 _public member_ `uint32 bGatherNavMeshEdges : 1;`
- L261 _public member_ `uint32 bMarkForbiddenPolys : 1;`
- L262 _public member_ `uint32 bGatherTileBuildTimesHeatMap : 1;`
- L264 _public member_ `double MinTileBuildTime = DBL_MAX;`
- L265 _public member_ `double MaxTileBuildTime = 0.;`
- L267 _public function_ `FRecastDebugGeometry() : bGatherPolyEdges(false), bGatherNavMeshEdges(false), bMarkForbiddenPolys(false), bGatherTileBuildTimesHeatMap(false)`
- L270 _public prototype_ `uint32 GetAllocatedSize() const;`

#### enum `FRecastDebugGeometry::EOffMeshLinkEnd`  
`enum EOffMeshLinkEnd`  
_L185-191_
- L187 _public enumerator_ `OMLE_None = 0x0`
- L188 _public enumerator_ `OMLE_Left = 0x1`
- L189 _public enumerator_ `OMLE_Right = 0x2`
- L190 _public enumerator_ `OMLE_Both = OMLE_Left | OMLE_Right`

#### struct `FRecastDebugGeometry::FOffMeshLink`  
`struct FOffMeshLink`  
_L193-204_
- L195 _public member_ `FVector Left;`
- L196 _public member_ `FVector Right;`
- L197 _public member_ `uint8 AreaID;`
- L198 _public member_ `uint8 Direction;`
- L199 _public member_ `uint8 ValidEnds;`
- L200 _public member_ `bool bIsGenerated;`
- L201 _public member_ `float Radius;`
- L202 _public member_ `float Height;`
- L203 _public member_ `FColor Color;`

#### struct `FRecastDebugGeometry::FCluster`  
`struct FCluster`  
_L207-210_
- L209 _public member_ `TArray<int32> MeshIndices;`

#### struct `FRecastDebugGeometry::FClusterLink`  
`struct FClusterLink`  
_L212-216_
- L214 _public member_ `FVector FromCluster;`
- L215 _public member_ `FVector ToCluster;`

#### struct `FRecastDebugGeometry::FOffMeshSegment`  
`struct FOffMeshSegment`  
_L221-228_
- L223 _public member_ `FVector LeftStart, LeftEnd;`
- L223 _public member_ `FVector LeftStart, LeftEnd;`
- L224 _public member_ `FVector RightStart, RightEnd;`
- L224 _public member_ `FVector RightStart, RightEnd;`
- L225 _public member_ `uint8 AreaID;`
- L226 _public member_ `uint8 Direction;`
- L227 _public member_ `uint8 ValidEnds;`

#### struct `FNavTileRef`  
`struct FNavTileRef`  
_L273-304_
- L275 _public function_ `FNavTileRef()`
- L276 _public function_ `explicit FNavTileRef(const uint64 InTileRef) : TileRef(InTileRef)`
- L278 _public function_ `explicit operator uint64() const`
- L280 _public function_ `bool operator==(const FNavTileRef InRef) const`
- L281 _public function_ `bool operator!=(const FNavTileRef InRef) const`
- L283 _public function_ `bool IsValid() const`
- L299 _public prototype_ `static void DeprecatedGetTileIdsFromNavTileRefs(const FPImplRecastNavMesh* RecastNavMeshImpl, const TArray<FNavTileRef>& InTileRefs, TArray<uint32>& OutTileIds);` — Those 2 functions are used for backward compatibility of the following deprecated functions in FRecastNavMeshGenerator and ARecastNavMesh: RemoveTileLayers AddGeneratedTilesTimeSliced AddGeneratedTiles RemoveLayers ProcessTileTasksAsync ProcessTileTasks AttachTiles DetachTiles OnNavMeshTilesUpdated InvalidateAffectedPaths They will be removed with the deprecated methods
- L300 _public prototype_ `static void DeprecatedMakeTileRefsFromTileIds(const FPImplRecastNavMesh* RecastNavMeshImpl, const TArray<uint32>& InTileIds, TArray<FNavTileRef>& OutTileRefs);`
- L303 _private member_ `uint64 TileRef = 0;`

#### struct `FNavPoly`  
`struct FNavPoly`  
_L306-310_
- L308 _public member_ `NavNodeRef Ref;`
- L309 _public member_ `FVector Center;`

#### enum `ERecastNamedFilter::Type`  
`enum Type`  
_L314-321_
- L316 _public enumerator_ `FilterOutNavLinks = 0` — filters out all off-mesh connections
- L317 _public enumerator_ `FilterOutAreas` — filters out all navigation areas except the default one (RECAST_DEFAULT_AREA)
- L318 _public enumerator_ `FilterOutNavLinksAndAreas` — combines FilterOutNavLinks and FilterOutAreas
- L320 _public enumerator_ `NamedFiltersCount`

#### struct `FNavigationWallEdge`  
`struct FNavigationWallEdge`  
_L324-334_
- L326 _public prototype_ `FNavigationWallEdge() = default;`
- L327 _public function_ `FNavigationWallEdge(const FVector& InStart, const FVector& InEnd) : Start(InStart) , End(InEnd)`
- L332 _public member_ `FVector Start = FVector::ZeroVector;`
- L333 _public member_ `FVector End = FVector::ZeroVector;`

#### enum `EHeightFieldRenderMode`  
`enum class EHeightFieldRenderMode : uint8`  
_L338-342_
- reflection: `UENUM()`
- L340 _public enumerator_ `Solid = 0`
- L341 _public enumerator_ `Walkable`

#### struct `FRecastNavMeshTileGenerationDebug`  
`struct FRecastNavMeshTileGenerationDebug`  
_L345-446_
- reflection: `USTRUCT()`
- L349 _public prototype_ `FRecastNavMeshTileGenerationDebug();`
- L353 _public member_ `uint32 bEnabled : 1;` — `UPROPERTY(Transient, EditAnywhere, Category = Debug)` — If set, the selected internal debug data will be kept during tile generation to be displayed with the navmesh.
- L359 _public member_ `FIntVector TileCoordinate = FIntVector::ZeroValue;` — `UPROPERTY(EditAnywhere, Category = Debug)` — Selected tile coordinate, only this tile will have it's internal data kept. When MaxTileCoordinate is enabled, this defines the lower bound of a rectangle. Tip: displaying the navmesh using 'Draw Tile Labels' show tile coordinates.
- L364 _public member_ `FIntVector MaxTileCoordinate = FIntVector::ZeroValue;` — `UPROPERTY(EditAnywhere, Category = Debug, meta=(EditCondition="bUseMaxTileCoordinate"))` — Optional: Highest bound included tile to define a rectangle with TileCoordinate for which the internal data is kept. Tip: displaying the navmesh using 'Draw Tile Labels' show tile coordinates.
- L368 _public member_ `uint32 bGenerateDebugTileOnly : 1;` — `UPROPERTY(EditAnywhere, Category = Debug)` — If set, the generator will only generate the tile selected to debug (set in TileCoordinate).
- L373 _public member_ `uint32 bCollisionGeometry : 1;` — `UPROPERTY(EditAnywhere, Category = Debug)` — Display the collision used for the navmesh rasterization. Note: The visualization is affected by the DrawOffset of the RecastNavmesh owner
- L378 _public member_ `uint32 bDynamicAreas : 1;` — `UPROPERTY(EditAnywhere, Category = Debug)` — Display the nav area modifier shapes. Note: The visualization is affected by the DrawOffset of the RecastNavmesh owner
- L381 _public member_ `EHeightFieldRenderMode HeightFieldRenderMode;` — `UPROPERTY(EditAnywhere, Category = Debug)`
- L384 _public member_ `uint32 bHeightfieldFromRasterization : 1;` — `UPROPERTY(EditAnywhere, Category = Debug)`
- L387 _public member_ `uint32 bHeightfieldPostInclusionBoundsFiltering : 1;` — `UPROPERTY(EditAnywhere, Category = Debug)`
- L390 _public member_ `uint32 bHeightfieldPostHeightFiltering : 1;` — `UPROPERTY(EditAnywhere, Category = Debug)`
- L393 _public member_ `uint32 bHeightfieldBounds : 1;` — `UPROPERTY(EditAnywhere, Category = Debug)`
- L396 _public member_ `uint32 bCompactHeightfield : 1;` — `UPROPERTY(EditAnywhere, Category = Debug)`
- L399 _public member_ `uint32 bCompactHeightfieldEroded : 1;` — `UPROPERTY(EditAnywhere, Category = Debug)`
- L402 _public member_ `uint32 bHeightFieldLayers : 1;` — `UPROPERTY(EditAnywhere, Category = Debug)`
- L405 _public member_ `uint32 bCompactHeightfieldRegions : 1;` — `UPROPERTY(EditAnywhere, Category = Debug)`
- L408 _public member_ `uint32 bCompactHeightfieldDistances : 1;` — `UPROPERTY(EditAnywhere, Category = Debug)`
- L411 _public member_ `uint32 bTileCacheLayerAreas : 1;` — `UPROPERTY(EditAnywhere, Category = Debug)`
- L414 _public member_ `uint32 bTileCacheLayerRegions : 1;` — `UPROPERTY(EditAnywhere, Category = Debug)`
- L418 _public member_ `uint32 bSkipContourSimplification : 1;` — `UPROPERTY(EditAnywhere, Category = Debug)` — If set, the contour simplification step will be skipped. Beware that enabling this changes the way navmesh will generate when Tile Generation Debug is enabled.
- L421 _public member_ `uint32 bTileCacheContours : 1;` — `UPROPERTY(EditAnywhere, Category = Debug)`
- L424 _public member_ `uint32 bTileCachePolyMesh : 1;` — `UPROPERTY(EditAnywhere, Category = Debug)`
- L427 _public member_ `uint32 bTileCacheDetailMesh : 1;` — `UPROPERTY(EditAnywhere, Category = Debug)`
- L430 _public member_ `uint32 bUseMaxTileCoordinate : 1;` — `UPROPERTY(EditAnywhere, Category = Debug, meta=(InlineEditConditionToggle))`
- L433 _public member_ `uint16 LinkGenerationDebugFlags;` — `UPROPERTY(EditAnywhere, Category = Debug, meta = (Bitmask, BitmaskEnum = "/Script/NavigationSystem.ELinkGenerationDebugFlags"))`
- L437 _public member_ `int32 LinkGenerationSelectedEdge;` — `UPROPERTY(EditAnywhere, Category = Debug, meta=(UIMin=-1, ClampMin=-1))` — Using -1 as 'no edge selected'.
- L441 _public member_ `int32 LinkGenerationSelectedConfig;` — `UPROPERTY(EditAnywhere, Category = Debug, meta=(UIMin=-1, ClampMin=-1))` — Using -1 as 'no config selected'.
- L445 _public prototype_ `bool IsWithinTileCoordinates(const int32 TileX, const int32 TileY) const;` — Indicates if the tile coordinate in parameter is within the tile coordinate selected to debug. Either equal to TileCoordinate or inside the rectangle formed by TileCoordinate and MaxTileCoordinate.

#### struct `FNavMeshDirtyTileElement`  
`struct FNavMeshDirtyTileElement`  
_L451-456_
- desc: Used to list tiles that needs rebuilding.
- L453 _public member_ `FIntPoint Coordinates;`
- L454 _public member_ `FVector::FReal InvokerDistanceSquared;`
- L455 _public member_ `ENavigationInvokerPriority InvokerPriority;`

#### struct `FNavMeshTileData`  
`struct FNavMeshTileData`  
_L461-538_
- desc: Structure to handle nav mesh tile's raw data persistence and releasing
- L498 _public member_ `int32 LayerIndex;` — layer index
- L499 _public member_ `FBox LayerBBox;`
- L501 _public member_ `int32 DataSize;` — size of allocated data
- L503 _public member_ `TSharedPtr<FNavData, ESPMode::ThreadSafe> NavData;` — actual tile data
- L505 _public function_ `FNavMeshTileData() : LayerIndex(0), DataSize(0)`
- L506 _public prototype_ `~FNavMeshTileData();`
- L508 _public prototype_ `explicit FNavMeshTileData(uint8* RawData, int32 RawDataSize, int32 LayerIdx = 0, FBox LayerBounds = FBox(ForceInit));`
- L510 _public function_ `inline uint8* GetData()`
- L516 _public function_ `inline const uint8* GetData() const`
- L522 _public function_ `inline uint8* GetDataSafe()`
- L527 _public function_ `inline bool operator==(const uint8* RawData) const`
- L532 _public function_ `inline bool IsValid() const`
- L534 _public prototype_ `uint8* Release();`
- L537 _public prototype_ `void MakeUnique();` — Duplicate shared state so we will have own copy of the data

#### struct `FNavMeshTileData::FNavData`  
`struct FNavData`  
_L464-495_
- desc: helper function so that we release NavData via dtFree not regular delete (for navigation mem stats)
- L467 _public prototype_ `void TestPtr() const;` — Temporary test to help reproduce a crash.
- L469 _public function_ `FNavData(uint8* InNavData, const int32 InDataSize) : RawNavData(InNavData)`
- L481 _public prototype_ `~FNavData();`
- L483 _public function_ `const uint8* GetRawNavData() const`
- L484 _public function_ `uint8* GetMutableRawNavData()`
- L486 _public function_ `void Reset()`
- L493 _protected member_ `uint8* RawNavData;`
- L494 _protected member_ `SIZE_T AllocatedSize;` — != DataSize

#### struct `FNavMeshConfig::FRecastNamedFiltersCreator`  
`struct FRecastNamedFiltersCreator`  
_L544-547_
- L546 _public prototype_ `FRecastNamedFiltersCreator(bool bVirtualFilters);`

#### struct `FNavMeshResolutionParam`  
`struct FNavMeshResolutionParam`  
_L551-568_
- reflection: `USTRUCT()`
- L555 _public function_ `bool IsValid() const`
- L559 _public member_ `float CellSize = 25.f;` — `UPROPERTY(EditAnywhere, Category = Generation, config, meta = (ClampMin = "1.0", ClampMax = "1024.0"))` — Horizontal size of voxelization cell
- L563 _public member_ `float CellHeight = 10.f;` — `UPROPERTY(EditAnywhere, Category = Generation, config, meta = (ClampMin = "1.0", ClampMax = "1024.0"))` — Vertical size of voxelization cell
- L567 _public member_ `float AgentMaxStepHeight = 35.f;` — `UPROPERTY(EditAnywhere, Category = Generation, config, meta = (ClampMin = "0.0"))` — Largest vertical step the agent can perform

#### class `ARecastNavMesh`  
`class ARecastNavMesh : public ANavigationData`  
_L571-1643_
- reflection: `UCLASS(config=Engine, defaultconfig, hidecategories=(Input,Rendering,Tags,Transformation,Actor,Layers,Replication), notplaceable, MinimalAPI)`
- inherits: `ANavigationData`
- L575 _private typedef_ `typedef uint16 FNavPolyFlags;`
- L577 _private prototype_ `virtual void Serialize( FArchive& Ar ) override;`
- L580 _private prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L585 _private member_ `uint32 bDrawTriangleEdges:1;` — `UPROPERTY(EditAnywhere, Category=Display)` — Draw edges of every navmesh's triangle
- L589 _private member_ `uint32 bDrawPolyEdges:1;` — `UPROPERTY(EditAnywhere, Category=Display, config)` — Draw edges of every poly (i.e. not only border-edges)
- L593 _private member_ `uint32 bDrawFilledPolys:1;` — `UPROPERTY(EditAnywhere, Category = Display)` — if disabled skips filling drawn navmesh polygons
- L597 _private member_ `uint32 bDrawNavMeshEdges:1;` — `UPROPERTY(EditAnywhere, Category=Display)` — Draw border-edges
- L601 _private member_ `uint32 bDrawTileBounds:1;` — `UPROPERTY(EditAnywhere, Category=Display)` — Draw the tile boundaries
- L605 _private member_ `uint32 bDrawTileResolutions:1;` — `UPROPERTY(EditAnywhere, Category=Display)` — Draw the tile resolutions
- L609 _private member_ `uint32 bDrawPathCollidingGeometry:1;` — `UPROPERTY(EditAnywhere, Category=Display)` — Draw input geometry passed to the navmesh generator.  Recommend disabling other geometry rendering via viewport showflags in editor.
- L612 _private member_ `uint32 bDrawTileLabels:1;` — `UPROPERTY(EditAnywhere, Category=Display)`
- L615 _private member_ `uint32 bDrawTileBuildTimes:1;` — `UPROPERTY(EditAnywhere, Category=Display)`
- L618 _private member_ `uint32 bDrawTileBuildTimesHeatMap:1;` — `UPROPERTY(EditAnywhere, Category=Display)`
- L622 _private member_ `uint32 bDrawPolygonLabels:1;` — `UPROPERTY(EditAnywhere, Category=Display, meta = (DisplayName = "Draw Polygon Indices"))` — Draw a label for every poly that indicates its poly and tile indices
- L626 _private member_ `uint32 bDrawDefaultPolygonCost:1;` — `UPROPERTY(EditAnywhere, Category=Display, meta=(DisplayName="Draw Polygon Costs"))` — Draw a label for every poly that indicates its default and fixed costs
- L630 _private member_ `uint32 bDrawPolygonFlags:1;` — `UPROPERTY(EditAnywhere, Category=Display)` — Draw a label for every poly that indicates its poly and area flags
- L634 _private member_ `uint32 bDrawPolygonAreaIDs:1;` — `UPROPERTY(EditAnywhere, Category=Display)` — Draw a label for every poly that indicates its area id and the list of all NavAreaClass used in the displayed tiles.
- L637 _private member_ `uint32 bDrawLabelsOnPathNodes:1;` — `UPROPERTY(EditAnywhere, Category=Display)`
- L641 _private member_ `uint32 bDrawNavLinks:1;` — `UPROPERTY(EditAnywhere, Category=Display)` — Draw valid links (both ends are valid).
- L645 _private member_ `uint32 bDrawFailedNavLinks:1;` — `UPROPERTY(EditAnywhere, Category=Display, Meta = (DisplayName = "Draw Failed and Valid NavLinks"))` — Draw failed links and valid links.
- L649 _private member_ `uint32 bDrawClusters:1;` — `UPROPERTY(EditAnywhere, Category=Display)` — Draw navmesh's clusters and cluster links. (Requires WITH_NAVMESH_CLUSTER_LINKS=1)
- L653 _private member_ `uint32 bDrawOctree : 1;` — `UPROPERTY(EditAnywhere, Category = Display)` — Draw octree used to store navigation relevant actors
- L657 _private member_ `uint32 bDrawOctreeDetails : 1;` — `UPROPERTY(EditAnywhere, Category = Display, meta=(editcondition = "bDrawOctree"))` — Draw octree used to store navigation relevant actors with the elements bounds
- L660 _private member_ `uint32 bDrawMarkedForbiddenPolys : 1;` — `UPROPERTY(EditAnywhere, Category = Display)`
- L664 _private member_ `uint32 bDrawOnScreenInformation : 1;` — `UPROPERTY(EditAnywhere, Category = Display)` — Draw detailed navmesh information as 2D text.
- L668 _private member_ `uint32 bDistinctlyDrawTilesBeingBuilt:1;` — `UPROPERTY(config)` — if true, show currently rebuilding tiles differently when visualizing
- L672 _private member_ `float DrawOffset;` — `UPROPERTY(EditAnywhere, Category=Display, config)` — vertical offset added to navmesh's debug representation for better readability
- L675 _private member_ `FRecastNavMeshTileGenerationDebug TileGenerationDebug;` — `UPROPERTY(EditAnywhere, Category = Display)`
- L683 _private member_ `uint32 bFixedTilePoolSize:1;` — `UPROPERTY(EditAnywhere, Category=Generation, config)` — if true, the NavMesh will allocate fixed size pool for tiles, should be enabled to support streaming
- L687 _private member_ `int32 TilePoolSize;` — `UPROPERTY(EditAnywhere, Category=Generation, config, meta=(editcondition = "bFixedTilePoolSize"))` — maximum number of tiles NavMesh can hold
- L691 _private member_ `float TileSizeUU;` — `UPROPERTY(EditAnywhere, Category=Generation, config, meta=(ClampMin = "300.0"))` — size of single tile, expressed in uu
- L697 _private member_ `float AverageLayersPerTile;` — `UPROPERTY(EditAnywhere, Category=Generation, config, meta=(ClampMin = "1.0"))` — Expected average number of layers per tile. This is a factor in the number of tiles the navmesh can hold when not using bFixedTilePoolSize. Log warnings are issued if this is too low.
- L702 _private member_ `uint32 bMinimizeLinkPoolSize:1;` — `UPROPERTY(EditAnywhere, Category=Generation, config, AdvancedDisplay)` — If true (default), minimize base link pool size using optimized allocation, else use previous larger base link pool. Changing this property requires a navmesh rebuild to fully benefit from the change.
- L712 _private member_ `float CellSize;` — `UE_DEPRECATED(all, "Use NavMeshResolutionParams to set CellSize for the different resolutions instead")` — `UPROPERTY(config, meta = (DeprecatedProperty, DeprecationMessage = "Use NavMeshResolutionParams to set CellSize for the different resolutions instead"))`
- L716 _private member_ `float CellHeight;` — `UE_DEPRECATED(all, "Use NavMeshResolutionParams to set CellHeight for the different resolutions instead")` — `UPROPERTY(config, meta = (DeprecatedProperty, DeprecationMessage = "Use NavMeshResolutionParams to set CellHeight for the different resolutions instead"))`
- L720 _private member_ `float AgentMaxStepHeight;` — `UE_DEPRECATED(all, "Use NavMeshResolutionParams to set AgentMaxStepHeight for the different resolutions instead")` — `UPROPERTY(config, meta = (DeprecatedProperty, DeprecationMessage = "Use NavMeshResolutionParams to set AgentMaxStepHeight for the different resolutions instead"))`
- L726 _private member_ `FNavMeshResolutionParam NavMeshResolutionParams[(uint8)ENavigationDataResolution::MAX];` — `UPROPERTY(EditAnywhere, Category = Generation, config)` — Resolution params If using multiple resolutions, it's recommended to choose the highest resolution first and set it according to the highest desired precision and then the other resolutions.
- L730 _private member_ `float AgentRadius;` — `UPROPERTY(EditAnywhere, Category = Generation, config, meta = (ClampMin = "0.0", ClampMax = "100000.0", UIMin = "0.0", UIMax = "100000.0"))` — Radius of smallest agent to traverse this navmesh
- L734 _private member_ `float AgentHeight;` — `UPROPERTY(EditAnywhere, Category = Generation, config, meta = (ClampMin = "0.0", ClampMax = "100000.0", UIMin = "0.0", UIMax = "100000.0"))` — Size of the tallest agent that will path with this navmesh.
- L738 _private member_ `float AgentMaxSlope;` — `UPROPERTY(EditAnywhere, Category=Generation, config, meta=(ClampMin = "0.0", ClampMax = "89.0", UIMin = "0.0", UIMax = "89.0" ))` — The maximum slope (angle) that the agent can move on.
- L742 _private member_ `float MinRegionArea;` — `UPROPERTY(EditAnywhere, Category=Generation, config, meta=(ClampMin = "0.0"))` — The minimum dimension of area. Areas smaller than this will be discarded
- L746 _private member_ `float MergeRegionSize;` — `UPROPERTY(EditAnywhere, Category=Generation, config, meta=(ClampMin = "0.0"))` — The size limit of regions to be merged with bigger regions (watershed partitioning only)
- L753 _private member_ `int MaxVerticalMergeError;` — `UE_DEPRECATED(5.5, "Not used anymore, the behavior is now binded to SimplificationElevationRatio.")` — `UPROPERTY(config)` — Maximum vertical deviation between raw contour points to allowing merging (in voxel). Use a low value (2-5) depending on CellHeight, AgentMaxStepHeight and AgentMaxSlope, to allow more precise contours (also see SimplificationElevationRatio). Use very high value to deactivate (Recast behavior).
- L757 _private member_ `float MaxSimplificationError;` — `UPROPERTY(EditAnywhere, Category = Generation, config, meta = (ClampMin = "0.0"))` — How much navigable shapes can get simplified - the higher the value the more freedom
- L762 _private member_ `float SimplificationElevationRatio;` — `UPROPERTY(EditAnywhere, Category = Generation, config, meta = (ClampMin = "0.0"))` — When simplifying contours, how much is the vertical error taken into account when comparing with MaxSimplificationError. Use 0 to deactivate (Recast behavior), use 1 as a typical value.
- L766 _private member_ `int32 MaxSimultaneousTileGenerationJobsCount;` — `UPROPERTY(EditAnywhere, Category = Generation, config, meta = (ClampMin = "0", UIMin = "0"), AdvancedDisplay)` — Sets the limit for number of asynchronous tile generators running at one time, also used for some synchronous tasks
- L773 _private member_ `int32 TileNumberHardLimit;` — `UPROPERTY(EditAnywhere, Category = Generation, config, meta = (ClampMin = "1", UIMin = "1"), AdvancedDisplay)` — Absolute hard limit to number of navmesh tiles. Be very, very careful while modifying it while having big maps with navmesh. A single, empty tile takes 176 bytes and empty tiles are allocated up front (subject to change, but that's where it's at now) @note TileNumberHardLimit is always rounded up to the closest power of 2
- L777 _private member_ `int32 ExpectedMaxLayersPerTile;` — `UPROPERTY(EditAnywhere, Category = Generation, config, meta = (ClampMin = "1", UIMin = "1"), AdvancedDisplay)` — Used when connecting segment links across layers to determine how much memory to allocate to hold skipped layers
- L780 _private member_ `int32 PolyRefTileBits;` — `UPROPERTY(VisibleAnywhere, Category = Generation, AdvancedDisplay)`
- L783 _private member_ `int32 PolyRefNavPolyBits;` — `UPROPERTY(VisibleAnywhere, Category = Generation, AdvancedDisplay)`
- L786 _private member_ `int32 PolyRefSaltBits;` — `UPROPERTY(VisibleAnywhere, Category = Generation, AdvancedDisplay)`
- L790 _private member_ `FVector NavMeshOriginOffset;` — `UPROPERTY(EditAnywhere, Category = Generation, AdvancedDisplay)` — Use this if you don't want your tiles to start at (0,0,0)
- L794 _private member_ `float DefaultDrawDistance;` — `UPROPERTY(config)` — navmesh draw distance in game (always visible in editor)
- L799 _private member_ `float DefaultMaxSearchNodes;` — `UPROPERTY(config)` — specifies default limit to A* nodes used when performing navigation queries. Can be overridden by passing custom FNavigationQueryFilter
- L803 _private member_ `float DefaultMaxHierarchicalSearchNodes;` — `UPROPERTY(config)` — specifies default limit to A* nodes used when performing hierarchical navigation queries.
- L807 _private member_ `ENavigationLedgeSlopeFilterMode LedgeSlopeFilterMode;` — `UPROPERTY(EditAnywhere, Category=Generation, config, AdvancedDisplay)` — filtering methode used for filtering ledge slopes
- L811 _private member_ `TEnumAsByte<ERecastPartitioning::Type> RegionPartitioning;` — `UPROPERTY(EditAnywhere, Category=Generation, config, AdvancedDisplay)` — partitioning method for creating navmesh polys
- L815 _private member_ `TEnumAsByte<ERecastPartitioning::Type> LayerPartitioning;` — `UPROPERTY(EditAnywhere, Category=Generation, config, AdvancedDisplay)` — partitioning method for creating tile layers
- L819 _private member_ `int32 RegionChunkSplits;` — `UPROPERTY(EditAnywhere, Category=Generation, config, AdvancedDisplay)` — number of chunk splits (along single axis) used for region's partitioning: ChunkyMonotone
- L823 _private member_ `int32 LayerChunkSplits;` — `UPROPERTY(EditAnywhere, Category=Generation, config, AdvancedDisplay)` — number of chunk splits (along single axis) used for layer's partitioning: ChunkyMonotone
- L831 _private member_ `uint32 bSortNavigationAreasByCost:1;` — `UPROPERTY(EditAnywhere, Category=Generation, config)` — Controls whether Navigation Areas will be sorted by cost before application to navmesh during navmesh generation. This is relevant when there are areas overlapping and we want to have area cost express area relevancy as well. Setting it to true will result in having area sorted by cost, but it will also increase navmesh generation cost a bit
- L835 _private member_ `uint32 bIsWorldPartitioned : 1;` — `UPROPERTY(EditAnywhere, Category=Generation, config, meta = (EditCondition = "bAllowWorldPartitionedNavMesh", HideEditConditionToggle, DisplayName = "IsWorldPartitionedNavMesh"))` — In a world partitioned map, is this navmesh using world partitioning
- L840 _private member_ `uint32 bGenerateNavLinks : 1;` — `UPROPERTY(EditAnywhere, Category=Generation, config)` — Experimental: if set, navlinks will be automatically generated. @see FNavLinkGenerationJumpConfig
- L845 _private member_ `uint32 bPerformVoxelFiltering:1;` — `UPROPERTY(EditAnywhere, Category=Generation, config, AdvancedDisplay)` — controls whether voxel filtering will be applied (via FRecastTileGenerator::ApplyVoxelFilter). Results in generated navmesh better fitting navigation bounds, but hits (a bit) generation performance
- L849 _private member_ `uint32 bMarkLowHeightAreas : 1;` — `UPROPERTY(EditAnywhere, Category = Generation, config, AdvancedDisplay)` — mark areas with insufficient free height above instead of cutting them out (accessible only for area modifiers using replace mode)
- L854 _private member_ `uint32 bUseExtraTopCellWhenMarkingAreas : 1;` — `UPROPERTY(EditAnywhere, Category = Generation, config, AdvancedDisplay)` — Expand the top of the area nav modifier's bounds by one cell height when applying to the navmesh. If unset, navmesh on top of surfaces might not be marked by marking bounds flush with top surfaces (since navmesh is generated slightly above collision, depending on cell height).
- L858 _private member_ `uint32 bFilterLowSpanSequences : 1;` — `UPROPERTY(EditAnywhere, Category = Generation, config, AdvancedDisplay)` — if set, only single low height span will be allowed under valid one
- L862 _private member_ `uint32 bFilterLowSpanFromTileCache : 1;` — `UPROPERTY(EditAnywhere, Category = Generation, config, AdvancedDisplay)` — if set, only low height spans with corresponding area modifier will be stored in tile cache (reduces memory, can't modify without full tile rebuild)
- L866 _private member_ `uint32 bDoFullyAsyncNavDataGathering : 1;` — `UPROPERTY(EditAnywhere, Category = Generation, config, AdvancedDisplay)` — if set, navmesh data gathering will never happen on the game thread and will only be done on background threads
- L870 _private member_ `uint32 bUseBetterOffsetsFromCorners : 1;` — `UPROPERTY(config)` — TODO: switch to disable new code from OffsetFromCorners if necessary - remove it later
- L874 _private member_ `uint32 bStoreEmptyTileLayers : 1;` — `UPROPERTY(config)` — If set, tiles generated without any navmesh data will be marked to distinguish them from not generated / streamed out ones. Defaults to false.
- L878 _private member_ `uint32 bUseVirtualFilters : 1;` — `UPROPERTY(config)` — Indicates whether default navigation filters will use virtual functions. Defaults to true.
- L885 _private member_ `uint32 bUseVirtualGeometryFilteringAndDirtying : 1;` — `UPROPERTY(config)` — Indicates whether to use the virtual methods to check if an object should generate geometry or if we should call the normal method directly (i.e. FNavigationOctreeElement::ShouldUseGeometry). If enabled, will also check if an object requesting an update on the navmesh is excluded to avoid dirtying the areas unnecessarily. Defaults to false.
- L889 _private member_ `uint32 bAllowNavLinkAsPathEnd : 1;` — `UPROPERTY(config)` — If set, paths can end at navlink poly (not the ground one!)
- L893 _private member_ `int32 TimeSliceFilterLedgeSpansMaxYProcess = 13;` — `UPROPERTY(EditAnywhere, Category = TimeSlicing, config, AdvancedDisplay, meta = (ClampMin = "1", UIMin = "1"))` — The maximum number of y coords to process when time slicing filter ledge spans during navmesh regeneration.
- L897 _private member_ `double TimeSliceLongDurationDebug = 0.002;` — `UPROPERTY(EditAnywhere, Category = TimeSlicing, config, AdvancedDisplay)` — If a single time sliced section of navmesh regen code exceeds this duration then it will trigger debug logging
- L901 _private member_ `uint32 InvokerTilePriorityBumpDistanceThresholdInTileUnits = 1;` — `UPROPERTY(EditAnywhere, Category = Generation, config, AdvancedDisplay)` — If >= 1, when sorting pending tiles by priority, tiles near invokers (within the distance threshold) will have their priority increased.
- L905 _private member_ `uint8 InvokerTilePriorityBumpIncrease = 1;` — `UPROPERTY(EditAnywhere, Category = Generation, config, AdvancedDisplay)` — Priority increase steps for tiles that are withing near distance.
- L911 _protected member_ `uint32 bAllowWorldPartitionedNavMesh : 1;` — `UPROPERTY()` — World partitioned navmesh are only allowed in partitioned worlds.
- L919 _protected member_ `FNavLinkGenerationJumpDownConfig NavLinkJumpDownConfig;` — `UE_DEPRECATED(5.7, "Use the NavLinkJumpConfigs array instead.")` — `UPROPERTY(config)` — Experimental configuration to generate vertical links.
- L925 _protected member_ `TArray<FNavLinkGenerationJumpConfig> NavLinkJumpConfigs;` — `UPROPERTY(EditAnywhere, Category=Generation, config)` — Experimental configurations to generate jump links.
- L929 _private member_ `bool bHasNoTileData : 1 = false;` — @returns true if there were no tiles when the navmesh was loaded.
- L933 _private member_ `uint32 bUseVoxelCache : 1;` — `UPROPERTY(config)` — Cache rasterized voxels instead of just collision vertices/indices in navigation octree
- L937 _private member_ `float TileSetUpdateInterval;` — `UPROPERTY(config)` — indicates how often we will sort navigation tiles to mach players position
- L940 _private member_ `static FNavPolyFlags NavLinkFlag;` — contains last available dtPoly's flag bit set (8th bit at the moment of writing)
- L943 _private member_ `static FVector::FReal DrawDistanceSq;` — Squared draw distance
- L946 _private member_ `static float MinimumSizeForChaosNavMeshInfluenceSq;` — MinimumSizeForChaosNavMeshInfluence
- L984 _public member_ `float HeuristicScale;` — `UPROPERTY(EditAnywhere, Category = Query, config, meta = (ClampMin = "0.1"))` — Euclidean distance heuristic scale used while pathfinding
- L988 _public member_ `float VerticalDeviationFromGroundCompensation;` — `UPROPERTY(EditAnywhere, Category = Query, config, meta = (ClampMin = "0.0"))` — Value added to each search height to compensate for error between navmesh polys and walkable geometry
- L991 _public member_ `FOnNavMeshUpdate OnNavMeshUpdate;` — broadcast for navmesh updates
- L993 _public function_ `inline static void SetDrawDistance(FVector::FReal NewDistance)`
- L994 _public function_ `inline static FVector::FReal GetDrawDistanceSq()`
- L996 _public function_ `inline static void SetMinimumSizeForChaosNavMeshInfluence(float NewSize)`
- L997 _public function_ `inline static float GetMinimumSizeForChaosNavMeshInfluenceSq()`
- L1002 _public prototype_ `bool HasValidNavmesh() const;`
- L1005 _public prototype_ `virtual ~ARecastNavMesh();` — Dtor
- L1014 _public prototype_ `virtual void PostInitProperties() override;`
- L1015 _public prototype_ `virtual void PostLoad() override;`
- L1016 _public prototype_ `virtual void PostRegisterAllComponents() override;`
- L1017 _public prototype_ `virtual void PostUnregisterAllComponents() override;`
- L1018 _public prototype_ `virtual void BeginDestroy() override;`
- L1023 _private prototype_ `bool CanUpdateNavMeshInEditor() const;`
- L1026 _public prototype_ `virtual void PostEditChangeChainProperty( struct FPropertyChangedChainEvent& PropertyChangedChainEvent) override;`
- L1027 _public prototype_ `virtual void PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L1028 _public prototype_ `virtual void PostEditUndo() override;`
- L1029 _public prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L1035 _public function_ `virtual bool ShouldExport() override` — RecastNavMesh instances are dynamically spawned and should not be copied
- L1038 _public prototype_ `virtual void LoadBeforeGeneratorRebuild() override;`
- L1040 _public prototype_ `virtual void CleanUp() override;`
- L1043 _public prototype_ `virtual FNavLocation GetRandomPoint(FSharedConstNavQueryFilter Filter = NULL, const UObject* Querier = NULL) const override;`
- L1046 _public prototype_ `virtual bool GetRandomReachablePointInRadius(const FVector& Origin, float Radius, FNavLocation& OutResult, FSharedConstNavQueryFilter Filter = NULL, const UObject* Querier = NULL) const override;` — finds a random location in Radius, reachable from Origin. @param Radius needs to be non-negative. The function fails for Radius < 0. Radius being 0 is still rasults in a valid request.
- L1047 _public prototype_ `virtual bool GetRandomPointInNavigableRadius(const FVector& Origin, float Radius, FNavLocation& OutResult, FSharedConstNavQueryFilter Filter = NULL, const UObject* Querier = NULL) const override;`
- L1049 _public prototype_ `virtual bool FindMoveAlongSurface(const FNavLocation& StartLocation, const FVector& TargetPosition, FNavLocation& OutLocation, FSharedConstNavQueryFilter Filter = NULL, const UObject* Querier = NULL) const override;`
- L1050 _public prototype_ `virtual void BatchFindMoveAlongSurface(TArray<FNavigationFindMoveAlongSurfaceWork>& Workload, FSharedConstNavQueryFilter Filter = NULL, const UObject* Querier = NULL) const override;`
- L1051 _public prototype_ `virtual bool FindOverlappingEdges(const FNavLocation& StartLocation, TConstArrayView<FVector> ConvexPolygon, TArray<FVector>& OutEdges, FSharedConstNavQueryFilter Filter = NULL, const UObject* Querier = NULL) const override;`
- L1052 _public prototype_ `virtual bool GetPathSegmentBoundaryEdges(const FNavigationPath& Path, const FNavPathPoint& StartPoint, const FNavPathPoint& EndPoint, const TConstArrayView<FVector> SearchArea, TArray<FVector>& OutEdges, const float MaxAreaEnterCost, FSharedConstNavQueryFilter Filter = NULL, const UObject* Querier = NULL) const override;`
- L1053 _public prototype_ `virtual bool ProjectPoint(const FVector& Point, FNavLocation& OutLocation, const FVector& Extent, FSharedConstNavQueryFilter Filter = NULL, const UObject* Querier = NULL) const override;`
- L1054 _public prototype_ `virtual bool IsNodeRefValid(NavNodeRef NodeRef) const override;`
- L1057 _public prototype_ `virtual void BatchProjectPoints(TArray<FNavigationProjectionWork>& Workload, const FVector& Extent, FSharedConstNavQueryFilter Filter = NULL, const UObject* Querier = NULL) const override;` — Project batch of points using shared search extent and filter
- L1062 _public prototype_ `virtual void BatchProjectPoints(TArray<FNavigationProjectionWork>& Workload, FSharedConstNavQueryFilter Filter = NULL, const UObject* Querier = NULL) const override;` — Project batch of points using shared search filter. This version is not requiring user to pass in Extent, and is instead relying on FNavigationProjectionWork.ProjectionLimit. @note function will assert if item's FNavigationProjectionWork.ProjectionLimit is invalid
- L1064 _public prototype_ `virtual ENavigationQueryResult::Type CalcPathCost(const FVector& PathStart, const FVector& PathEnd, FVector::FReal& OutPathCost, FSharedConstNavQueryFilter Filter = NULL, const UObject* Querier = NULL) const override;`
- L1065 _public prototype_ `virtual ENavigationQueryResult::Type CalcPathLength(const FVector& PathStart, const FVector& PathEnd, FVector::FReal& OutPathLength, FSharedConstNavQueryFilter QueryFilter = NULL, const UObject* Querier = NULL) const override;`
- L1066 _public prototype_ `virtual ENavigationQueryResult::Type CalcPathLengthAndCost(const FVector& PathStart, const FVector& PathEnd, FVector::FReal& OutPathLength, FVector::FReal& OutPathCost, FSharedConstNavQueryFilter QueryFilter = NULL, const UObject* Querier = NULL) const override;`
- L1067 _public prototype_ `virtual bool DoesNodeContainLocation(NavNodeRef NodeRef, const FVector& WorldSpaceLocation) const override;`
- L1069 _public prototype_ `virtual UPrimitiveComponent* ConstructRenderingComponent() override;`
- L1071 _public function_ `virtual FBox GetBounds() const override` — Returns bounding box for the navmesh.
- L1073 _public prototype_ `virtual void ApplyWorldOffset(const FVector& InOffset, bool bWorldShift) override;` — Called on world origin changes
- L1075 _public prototype_ `virtual void FillNavigationDataChunkActor(const FBox& InQueryBounds, class ANavigationDataChunkActor& DataChunkActor, FBox& OutTilesBounds) const override;`
- L1077 _public prototype_ `virtual void OnStreamingNavDataAdded(class ANavigationDataChunkActor& InActor) override;`
- L1078 _public prototype_ `virtual void OnStreamingNavDataRemoved(class ANavigationDataChunkActor& InActor) override;`
- L1080 _public prototype_ `virtual void OnStreamingLevelAdded(ULevel* InLevel, UWorld* InWorld) override;`
- L1081 _public prototype_ `virtual void OnStreamingLevelRemoved(ULevel* InLevel, UWorld* InWorld) override;`
- L1084 _public prototype_ `virtual double GetWorldPartitionNavigationDataBuilderOverlap() const override;`
- L1088 _public prototype_ `virtual void AttachNavMeshDataChunk(URecastNavMeshDataChunk& NavDataChunk);`
- L1089 _public prototype_ `virtual void DetachNavMeshDataChunk(URecastNavMeshDataChunk& NavDataChunk);`
- L1091 _public prototype_ `const TSet<FIntPoint>& GetActiveTileSet() const;`
- L1092 _public prototype_ `TSet<FIntPoint>& GetActiveTileSet();`
- L1094 _public prototype_ `void LogRecastTile(const TCHAR* Caller, const FName& Prefix, const FName& OperationName, const dtNavMesh& DetourMesh, const int32 TileX, const int32 TileY, const int32 LayerIndex, const uint64 TileRef) const;`
- L1098 _protected prototype_ `void SerializeRecastNavMesh(FArchive& Ar, FPImplRecastNavMesh*& NavMesh, int32 NavMeshVersion);` — Serialization helper.
- L1100 _protected prototype_ `virtual void RestrictBuildingToActiveTiles(bool InRestrictBuildingToActiveTiles) override;`
- L1102 _protected prototype_ `virtual void OnRegistered() override;`
- L1103 _protected prototype_ `virtual void OnUnregistered() override;`
- L1107 _public function_ `float GetCellSize(const ENavigationDataResolution Resolution) const` — Get the CellSize for the given resolution.
- L1110 _public function_ `void SetCellSize(const ENavigationDataResolution Resolution, const float Size)` — Set the CellSize for the given resolution.
- L1113 _public function_ `float GetCellHeight(const ENavigationDataResolution Resolution) const` — Get the CellHeight for the given resolution.
- L1116 _public function_ `void SetCellHeight(const ENavigationDataResolution Resolution, const float Height)` — Set the CellHeight for the given resolution.
- L1119 _public function_ `float GetAgentMaxStepHeight(const ENavigationDataResolution Resolution) const` — Get the AgentMaxStepHeight for the given resolution.
- L1122 _public function_ `void SetAgentMaxStepHeight(const ENavigationDataResolution Resolution, const float MaxStepHeight)` — Set the AgentMaxStepHeight for the given resolution.
- L1125 _public prototype_ `float GetTileSizeUU() const;` — Returns the tile size in world units.
- L1128 _public prototype_ `bool IsResizable() const;` — Whether NavMesh should adjust its tile pool size when NavBounds are changed
- L1131 _public prototype_ `FBox GetNavMeshBounds() const;` — Returns bounding box for the whole navmesh.
- L1135 _public prototype_ `FBox GetNavMeshTileBounds(int32 TileIndex) const;` — `UE_DEPRECATED(5.5, "Use the version of this function that takes a FNavTileRef instead.")` — Returns bounding box for a given navmesh tile.
- L1138 _public prototype_ `FBox GetNavMeshTileBounds(FNavTileRef TileRef) const;` — Returns bounding box for a given navmesh tile.
- L1142 _public prototype_ `bool GetNavMeshTileXY(int32 TileIndex, int32& OutX, int32& OutY, int32& Layer) const;` — `UE_DEPRECATED(5.5, "Use the version of this function that takes a FNavTileRef instead.")` — Retrieves XY coordinates of tile specified by index
- L1145 _public prototype_ `bool GetNavMeshTileXY(FNavTileRef TileRef, int32& OutX, int32& OutY, int32& Layer) const;` — Retrieves XY coordinates of tile
- L1148 _public prototype_ `bool GetNavMeshTileXY(const FVector& Point, int32& OutX, int32& OutY) const;` — Retrieves XY coordinates of tile specified by position
- L1152 _public prototype_ `bool GetNavmeshTileResolution(int32 TileIndex, ENavigationDataResolution& OutResolution) const;` — `UE_DEPRECATED(5.5, "Use the version of this function that takes a FNavTileRef instead.")` — Retrieves the tile resolution
- L1155 _public prototype_ `bool GetNavmeshTileResolution(FNavTileRef TileRef, ENavigationDataResolution& OutResolution) const;` — Retrieves the tile resolution
- L1158 _public prototype_ `bool CheckTileIndicesInValidRange(const FVector& Point, bool& bOutInRange) const;` — Checks the supplied Points tile indicies can fit in the range of an int32
- L1162 _public prototype_ `void GetNavMeshTilesAt(int32 TileX, int32 TileY, TArray<int32>& Indices) const;` — `UE_DEPRECATED(5.5, "Use the version of this function that takes an array of FNavTileRefs instead.")` — Retrieves all tile indices at matching XY coordinates
- L1165 _public prototype_ `void GetNavMeshTilesAt(int32 TileX, int32 TileY, TArray<FNavTileRef>& OutRefs) const;` — Retrieves all tiles at matching XY coordinates
- L1168 _public prototype_ `int32 GetNavMeshTilesCount() const;` — Retrieves number of tiles in this navmesh
- L1170 _public prototype_ `int32 GetNumActiveTiles() const;` — Returns the number of tiles that have active data (header and dataSize > 0). Unlike GetNavMeshTilesCount, this counts actual populated tiles rather than pool capacity.
- L1173 _public prototype_ `void GetAllNavMeshTiles(TArray<FNavTileRef>& OutRefs) const;` — Retrieves all tiles in this navmesh
- L1176 _public prototype_ `void RemoveTileCacheLayers(int32 TileX, int32 TileY);` — Removes compressed tile data at given tile coord
- L1179 _public prototype_ `void AddTileCacheLayers(int32 TileX, int32 TileY, const TArray<FNavMeshTileData>& InLayers);` — Stores compressed tile data for given tile coord
- L1182 _public prototype_ `void RemoveTileDebugData(int32 TileX, int32 TileY);`
- L1183 _public prototype_ `void AddTileDebugData(int32 TileX, int32 TileY, const struct FRecastInternalDebugData& InTileDebugData);`
- L1187 _public prototype_ `void MarkEmptyTileCacheLayers(int32 TileX, int32 TileY);` — Marks tile coord as rebuild and empty
- L1190 _public prototype_ `TArray<FNavMeshTileData> GetTileCacheLayers(int32 TileX, int32 TileY) const;` — Returns compressed tile data at given tile coord
- L1194 _public prototype_ `int32 GetCompressedTileCacheSize();`
- L1197 _public prototype_ `void GetEdgesForPathCorridor(const TArray<NavNodeRef>* PathCorridor, TArray<struct FNavigationPortalEdge>* PathCorridorEdges) const;`
- L1199 _public prototype_ `void UpdateDrawing();`
- L1202 _public prototype_ `void RequestDrawingUpdate(bool bForce = false);` — Creates a task to be executed on GameThread calling UpdateDrawing
- L1205 _public prototype_ `virtual void OnNavMeshTilesUpdated(const TArray<FNavTileRef>& ChangedTiles);` — called after regenerating tiles
- L1209 _public prototype_ `virtual void CreateSegmentLinkConnections(TSet<FNavTileRef>& TilesPendingSegmentLinks);` — Creates segment link connections for the given tiles. Called after navigation tiles are finished generating.
- L1213 _public prototype_ `virtual void OnNavMeshGenerationFinished();` — Event from generator that navmesh build has finished
- L1215 _public prototype_ `virtual void EnsureBuildCompletion() override;`
- L1217 _public prototype_ `virtual void SetConfig(const FNavDataConfig& Src) override;`
- L1219 _protected prototype_ `virtual void FillConfig(FNavDataConfig& Dest) override;`
- L1221 _protected function_ `inline const FNavigationQueryFilter& GetRightFilterRef(FSharedConstNavQueryFilter Filter) const`
- L1228 _public prototype_ `static bool IsVoxelCacheEnabled();`
- L1240 _public prototype_ `bool GetDebugGeometryForTile(FRecastDebugGeometry& OutGeometry, int32 TileIndex) const;` — `UE_DEPRECATED(5.5, "Use the version of the function that takes a FNavTileRef instead.")` — Gather debug geometry. @params OutGeometry Output geometry. @params TileIndex Used to collect geometry for a specific tile, INDEX_NONE will gather all tiles @return True if done collecting.
- L1247 _public prototype_ `bool GetDebugGeometryForTile(FRecastDebugGeometry& OutGeometry, FNavTileRef TileRef) const;` — Gather debug geometry. @params OutGeometry Output geometry. @params TileRef Used to collect geometry for a specific tile, an invalid FNavTileRef will gather all tiles @return True if done collecting.
- L1250 _public prototype_ `void DrawDebugPathCorridor(NavNodeRef const* PathPolys, int32 NumPathPolys, bool bPersistent=true) const;` — @todo docuement
- L1253 _public prototype_ `virtual uint32 LogMemUsed() const override;`
- L1256 _public prototype_ `void DumpDetailedMemoryStats() const;` — Dumps detailed per-section and per-tile memory statistics to the log.
- L1259 _public prototype_ `void UpdateNavMeshDrawing();`
- L1264 _public prototype_ `virtual void OnNavAreaChanged() override;`
- L1265 _public prototype_ `virtual void OnNavAreaAdded(const UClass* NavAreaClass, int32 AgentIndex) override;`
- L1266 _public prototype_ `virtual void OnNavAreaRemoved(const UClass* NavAreaClass) override;`
- L1267 _public prototype_ `virtual int32 GetNewAreaID(const UClass* AreaClass) const override;`
- L1268 _public function_ `virtual int32 GetMaxSupportedAreas() const override`
- L1271 _public prototype_ `uint16 GetDefaultForbiddenFlags() const;` — Get forbidden area flags from default query filter
- L1273 _public prototype_ `void SetDefaultForbiddenFlags(uint16 ForbiddenAreaFlags);` — Change forbidden area flags in default query filter
- L1276 _public prototype_ `virtual void SortAreasForGenerator(TArray<FRecastAreaNavModifierElement>& Areas) const;` — Area sort function
- L1278 _public prototype_ `virtual void RecreateDefaultFilter();`
- L1280 _public function_ `int32 GetMaxSimultaneousTileGenerationJobsCount() const`
- L1281 _public prototype_ `void SetMaxSimultaneousTileGenerationJobsCount(int32 NewJobsCountLimit);`
- L1284 _public function_ `FVector GetModifiedQueryExtent(const FVector& QueryExtent) const` — Returns query extent including adjustments for voxelization error compensation
- L1294 _public prototype_ `virtual void UpdateCustomLink(const INavLinkCustomInterface* CustomLink) override;`
- L1297 _public function_ `void UpdateNavigationLinkArea(int32 UserId, TSubclassOf<UNavArea> AreaClass) const` — `UE_DEPRECATED(5.3, "Use version of this function that takes a FNavLinkId. This function now has no effect.")`
- L1300 _public prototype_ `void UpdateNavigationLinkArea(FNavLinkId UserId, TSubclassOf<UNavArea> AreaClass) const;` — update area class and poly flags for all offmesh links with given UserId
- L1304 _public prototype_ `void UpdateSegmentLinkArea(int32 UserId, TSubclassOf<UNavArea> AreaClass) const;` — update area class and poly flags for all offmesh segment links with given UserId
- L1312 _public prototype_ `virtual void BeginBatchQuery() const override;` — Starts batch processing and locks access to navmesh from other threads
- L1315 _public prototype_ `virtual void FinishBatchQuery() const override;` — Finishes batch processing and release locks
- L1322 _public prototype_ `dtNavMesh* GetRecastMesh();` — dtNavMesh getter
- L1325 _public prototype_ `const dtNavMesh* GetRecastMesh() const;` — dtNavMesh getter
- L1328 _public function_ `int32 GetLinkUserId(NavNodeRef LinkPolyID) const` — `UE_DEPRECATED(5.3, "Please use GetNavLinkUserId() instead. This function only returns Invalid.")`
- L1334 _public prototype_ `FNavLinkId GetNavLinkUserId(NavNodeRef LinkPolyID) const;` — Retrieves LinkUserID associated with indicated PolyID
- L1336 _public prototype_ `FColor GetAreaIDColor(uint8 AreaID) const;`
- L1339 _public prototype_ `bool FindPolysAroundCircle(const FVector& CenterPos, const NavNodeRef CenterNodeRef, const FVector::FReal Radius, const FSharedConstNavQueryFilter& Filter, const UObject* QueryOwner, TArray<NavNodeRef>* OutPolys = nullptr, TArray<NavNodeRef>* OutPolysParent = nullptr, TArray<float>* OutPolysCost = nullptr, int32* OutPolysCount = nullptr) const;` — Finds the polygons along the navigation graph that touch the specified circle.
- L1342 _public prototype_ `NavNodeRef FindNearestPoly(FVector const& Loc, FVector const& Extent, FSharedConstNavQueryFilter Filter = NULL, const UObject* Querier = NULL) const;` — Returns nearest navmesh polygon to Loc, or INVALID_NAVNODEREF if Loc is not on the navmesh.
- L1346 _public prototype_ `FVector::FReal FindDistanceToWall(const FVector& StartLoc, FSharedConstNavQueryFilter Filter = nullptr, FVector::FReal MaxDistance = TNumericLimits<FVector::FReal>::Max(), FVector* OutClosestPointOnWall = nullptr) const;` — Finds the distance to the closest wall, limited to MaxDistance [out] OutClosestPointOnWall, if supplied, will be set to closest point on closest wall. Will not be set if no wall in the area (return value 0.f)
- L1349 _public prototype_ `bool GetPolyCenter(NavNodeRef PolyID, FVector& OutCenter) const;` — Retrieves center of the specified polygon. Returns false on error.
- L1352 _public prototype_ `bool GetPolyVerts(NavNodeRef PolyID, TArray<FVector>& OutVerts) const;` — Retrieves the vertices for the specified polygon. Returns false on error.
- L1355 _public prototype_ `bool GetRandomPointInPoly(NavNodeRef PolyID, FVector& OutPoint) const;` — Retrieves a random point inside the specified polygon. Returns false on error.
- L1358 _public prototype_ `FVector::FReal GetPolySurfaceArea(NavNodeRef PolyID) const;` — Retrieves the surface area of the specified polygon. Returns 0 on error.
- L1361 _public prototype_ `uint32 GetPolyAreaID(NavNodeRef PolyID) const;` — Retrieves area ID for the specified polygon.
- L1364 _public prototype_ `bool SetPolyArea(NavNodeRef PolyID, TSubclassOf<UNavArea> AreaClass);` — Sets area ID for the specified polygon.
- L1367 _public prototype_ `void SetPolyArrayArea(const TArray<FNavPoly>& Polys, TSubclassOf<UNavArea> AreaClass);` — Sets area ID for the specified polygons
- L1371 _public prototype_ `int32 ReplaceAreaInTileBounds(const FBox& Bounds, TSubclassOf<UNavArea> OldArea, TSubclassOf<UNavArea> NewArea, bool ReplaceLinks = true, TArray<NavNodeRef>* OutTouchedNodes = nullptr);` — In given Bounds find all areas of class OldArea and replace them with NewArea @return number of polys touched
- L1374 _public prototype_ `bool GetPolyFlags(NavNodeRef PolyID, uint16& PolyFlags, uint16& AreaFlags) const;` — Retrieves poly and area flags for specified polygon
- L1375 _public prototype_ `bool GetPolyFlags(NavNodeRef PolyID, FNavMeshNodeFlags& Flags) const;`
- L1378 _public prototype_ `bool GetPolyNeighbors(NavNodeRef PolyID, TArray<FNavigationPortalEdge>& Neighbors) const;` — Finds all polys connected with specified one
- L1381 _public prototype_ `bool GetPolyNeighbors(NavNodeRef PolyID, TArray<NavNodeRef>& Neighbors) const;` — Finds all polys connected with specified one, results expressed as array of NavNodeRefs
- L1384 _public prototype_ `bool GetPolyEdges(NavNodeRef PolyID, TArray<FNavigationPortalEdge>& Neighbors) const;` — Finds edges of specified poly
- L1387 _public prototype_ `bool GetPolyWallSegments(NavNodeRef PolyID, FSharedConstNavQueryFilter Filter, const UObject* QueryOwner, TArray<FNavigationPortalEdge>& OutNeighbors) const;` — Finds all wall segments for the specified polygon (walls or area borders)
- L1390 _public prototype_ `bool GetClosestPointOnPoly(NavNodeRef PolyID, const FVector& TestPt, FVector& PointOnPoly) const;` — Finds closest point constrained to given poly
- L1393 _public prototype_ `bool GetPolyTileIndex(NavNodeRef PolyID, uint32& PolyIndex, uint32& TileIndex) const;` — Decode poly ID into tile index and poly index
- L1396 _public prototype_ `bool GetLinkEndPoints(NavNodeRef LinkPolyID, FVector& PointA, FVector& PointB) const;` — Retrieves start and end point of offmesh link
- L1399 _public prototype_ `bool GetClusterBounds(NavNodeRef ClusterRef, FBox& OutBounds) const;` — Retrieves bounds of cluster. Returns false on error.
- L1402 _public prototype_ `bool GetRandomPointInCluster(NavNodeRef ClusterRef, FNavLocation& OutLocation) const;` — Get random point in given cluster
- L1405 _public prototype_ `NavNodeRef GetClusterRef(NavNodeRef PolyRef) const;` — Get cluster ref containing given poly ref
- L1411 _public prototype_ `bool GetPolysWithinPathingDistance(FVector const& StartLoc, const FVector::FReal PathingDistance, TArray<NavNodeRef>& FoundPolys, FSharedConstNavQueryFilter Filter = nullptr, const UObject* Querier = nullptr, FRecastDebugPathfindingData* DebugData = nullptr) const;` — Retrieves all polys within given pathing distance from StartLocation. @NOTE query is not using string-pulled path distance (for performance reasons), it measured distance between middles of portal edges, do you might want to add an extra margin to PathingDistance
- L1415 _public prototype_ `bool FilterPolys(TArray<NavNodeRef>& PolyRefs, const FRecastQueryFilter* Filter, const UObject* Querier = NULL) const;` — Filters nav polys in PolyRefs with Filter
- L1419 _public prototype_ `bool GetPolysInTile(int32 TileIndex, TArray<FNavPoly>& Polys) const;` — `UE_DEPRECATED(5.5, "Use the version of this function that takes a FNavTileRef instead.")` — Get all polys from tile
- L1422 _public prototype_ `bool GetPolysInTile(FNavTileRef TileRef, TArray<FNavPoly>& Polys) const;` — Get all polys from tile
- L1425 _public prototype_ `bool GetPolysInBox(const FBox& Box, TArray<FNavPoly>& Polys, FSharedConstNavQueryFilter Filter = nullptr, const UObject* Owner = nullptr) const;` — Get up to 256 polys that overlap the specified box
- L1428 _public prototype_ `bool FindEdges(const NavNodeRef CenterNodeRef, const FVector Center, const FVector::FReal Radius, const FSharedConstNavQueryFilter Filter, TArray<FNavigationWallEdge>& OutEdges) const;` — Find up to 64 navmesh eges in up to 64 polys around the center
- L1431 _public prototype_ `void GetTilePolyEdgesForFilter(FNavTileRef TileRef, FSharedConstNavQueryFilter Filter, TArray<FNavigationWallEdge>& OutEdges) const;` — Get all  navmesh edges from tile that form the border of the passed in Filter
- L1434 _public prototype_ `bool GetEdgesInTile(FNavTileRef TileRef, TArray<FNavigationWallEdge>& OutEdges) const;` — Get all exterior nav mesh edges from tile
- L1437 _public prototype_ `bool GetNavLinksInTile(const int32 TileIndex, TArray<FNavPoly>& Polys, const bool bIncludeLinksFromNeighborTiles) const;` — Get all polys from tile
- L1440 _public prototype_ `bool ProjectPointMulti(const FVector& Point, TArray<FNavLocation>& OutLocations, const FVector& Extent, FVector::FReal MinZ, FVector::FReal MaxZ, FSharedConstNavQueryFilter Filter = NULL, const UObject* Querier = NULL) const;` — Projects point on navmesh, returning all hits along vertical line defined by min-max Z params
- L1444 _public prototype_ `static FPathFindingResult FindPath(const FNavAgentProperties& AgentProperties, const FPathFindingQuery& Query);` — @todo document
- L1445 _public prototype_ `static bool TestPath(const FNavAgentProperties& AgentProperties, const FPathFindingQuery& Query, int32* NumVisitedNodes);`
- L1446 _public prototype_ `static bool TestHierarchicalPath(const FNavAgentProperties& AgentProperties, const FPathFindingQuery& Query, int32* NumVisitedNodes);`
- L1447 _public prototype_ `static bool NavMeshRaycast(const ANavigationData* Self, const FVector& RayStart, const FVector& RayEnd, FVector& HitLocation, FSharedConstNavQueryFilter QueryFilter, const UObject* Querier, FRaycastResult& Result);`
- L1448 _public prototype_ `static bool NavMeshRaycast(const ANavigationData* Self, const FVector& RayStart, const FVector& RayEnd, FVector& HitLocation, FSharedConstNavQueryFilter QueryFilter, const UObject* Querier = NULL);`
- L1449 _public prototype_ `static bool NavMeshRaycast(const ANavigationData* Self, const FVector& RayStart, const FVector& RayEnd, FVector& HitLocation, FNavigationRaycastAdditionalResults* AdditionalResults, FSharedConstNavQueryFilter QueryFilter, const UObject* Querier = NULL);`
- L1450 _public prototype_ `static bool NavMeshRaycast(const ANavigationData* Self, NavNodeRef RayStartNode, const FVector& RayStart, const FVector& RayEnd, FVector& HitLocation, FSharedConstNavQueryFilter QueryFilter, const UObject* Querier = NULL);`
- L1451 _public prototype_ `static bool NavMeshRaycast(const ANavigationData* Self, NavNodeRef RayStartNode, const FVector& RayStart, const FVector& RayEnd, FVector& HitLocation, FNavigationRaycastAdditionalResults* AdditionalResults, FSharedConstNavQueryFilter QueryFilter, const UObject* Querier = NULL);`
- L1453 _public prototype_ `virtual void BatchRaycast(TArray<FNavigationRaycastWork>& Workload, FSharedConstNavQueryFilter QueryFilter, const UObject* Querier = NULL) const override;`
- L1457 _public prototype_ `bool AdjustLocationWithFilter(const FVector& StartLoc, FVector& OutAdjustedLocation, const FNavigationQueryFilter& Filter, const UObject* Querier = NULL) const;` — finds a Filter-passing navmesh location closest to specified StartLoc @return true if adjusting was required, false otherwise
- L1462 _public prototype_ `bool HasCompleteDataInRadius(const FVector& TestLocation, FVector::FReal TestRadius) const;` — Check if navmesh is defined (either built/streamed or recognized as empty tile by generator) in given radius. @returns true if ALL tiles inside are ready
- L1467 _public prototype_ `bool HasCompleteDataAroundSegment(const FVector& StartLocation, const FVector& EndLocation, FVector::FReal TestRadius) const;` — Check if navmesh is defined (either built/streamed or recognized as empty tile by generator) within given radius around the given segment. @returns true if ALL tiles inside are ready
- L1470 _public prototype_ `bool IsSegmentOnNavmesh(const FVector& SegmentStart, const FVector& SegmentEnd, FSharedConstNavQueryFilter Filter = NULL, const UObject* Querier = NULL) const;` — @return true is specified segment is fully on navmesh (respecting the optional filter)
- L1473 _public prototype_ `bool IsCustomLink(NavNodeRef PolyRef) const;` — Check if poly is a custom link
- L1476 _public prototype_ `bool FindStraightPath(const FVector& StartLoc, const FVector& EndLoc, const TArray<NavNodeRef>& PathCorridor, TArray<FNavPathPoint>& PathPoints, TArray<FNavLinkId>* CustomLinks = NULL) const;` — finds stringpulled path from given corridor
- L1479 _public prototype_ `int32 DebugPathfinding(const FPathFindingQuery& Query, TArray<FRecastDebugPathfindingData>& Steps);` — Runs A* pathfinding on navmesh and collect data for every step
- L1481 _public prototype_ `static const FRecastQueryFilter* GetNamedFilter(ERecastNamedFilter::Type FilterType);`
- L1482 _public function_ `inline static FNavPolyFlags GetNavLinkFlag()`
- L1484 _public prototype_ `virtual bool NeedsRebuild() const override;`
- L1485 _public prototype_ `virtual bool SupportsRuntimeGeneration() const override;`
- L1486 _public prototype_ `virtual bool SupportsStreaming() const override;`
- L1488 _public prototype_ `bool IsWorldPartitionedDynamicNavmesh() const;`
- L1492 _public prototype_ `bool IsUsingActiveTilesGeneration(const UNavigationSystemV1& NavSys) const;` — When using active tiles generation, navigation is only allowed to be runtime generated on a subset of tiles. The subset is be defined by navinvokers or loaded world partitioned cells.
- L1495 _public prototype_ `virtual void PostLoadPreRebuild() override;` — Runs after LoadBeforeGeneratorRebuild but before the rebuild.
- L1497 _public prototype_ `virtual void ConditionalConstructGenerator() override;`
- L1499 _public function_ `bool ShouldGatherDataOnGameThread() const`
- L1500 _public function_ `int32 GetTileNumberHardLimit() const`
- L1502 _public prototype_ `virtual void UpdateActiveTiles(const TArray<FNavigationInvokerRaw>& InvokerLocations);`
- L1503 _public prototype_ `virtual void RemoveTiles(const TArray<FIntPoint>& Tiles);`
- L1505 _public prototype_ `void RebuildTile(const TArray<FNavMeshDirtyTileElement>& Tiles);`
- L1507 _public prototype_ `void DirtyTilesInBounds(const FBox& Bounds);`
- L1510 _public prototype_ `const TMap<FIntPoint, struct FRecastInternalDebugData>* GetDebugDataMap() const;`
- L1516 _public function_ `const FNavLinkGenerationJumpDownConfig& GetNavLinkJumpDownConfig() const` — `UE_DEPRECATED(5.7, "Use GetNavLinkJumpConfigs instead.")`
- L1520 _public function_ `const TArray<FNavLinkGenerationJumpConfig>& GetNavLinkJumpConfigs() const`
- L1524 _protected prototype_ `void UpdatePolyRefBitsPreview();`
- L1527 _protected prototype_ `void InvalidateAffectedPaths(const TArray<FNavTileRef>& ChangedTiles);` — Invalidates active paths that go through changed tiles
- L1531 _protected prototype_ `virtual FRecastNavMeshGenerator* CreateGeneratorInstance();` — created a new FRecastNavMeshGenerator instance. Overrider to supply your own extentions. Note: needs to derive from FRecastNavMeshGenerator
- L1533 _protected prototype_ `void CheckToDiscardSubLevelNavData(const UNavigationSystemBase& NavSys);`
- L1535 _protected prototype_ `bool IsGeneratingLinks() const;`
- L1536 _protected prototype_ `void RegisterGeneratedLinksProxy(FNavLinkGenerationJumpConfig& InOutNavLinkJumpConfig);`
- L1537 _protected prototype_ `void UnregisterGeneratedLinksProxy(FNavLinkGenerationJumpConfig& InOutNavLinkJumpConfig);`
- L1540 _protected prototype_ `void RegisterGeneratedLinksProxy();` — `UE_DEPRECATED(5.8, "Use the override using an FNavLinkGenerationJumpConfig instead.")`
- L1543 _protected prototype_ `void UnregisterGeneratedLinksProxy();` — `UE_DEPRECATED(5.8, "Use the override using an FNavLinkGenerationJumpConfig instead.")`
- L1547 _protected prototype_ `void CreateAndRegisterJumpDownLinksProxy(const FNavLinkId LinkProxyId = FNavLinkId::GenerateUniqueId());` — `UE_DEPRECATED(5.7, "Use the override using an FNavLinkGenerationJumpConfig instead.")` — Create and register links proxy. It's expected to be called on load or when the navmesh is rebuilt.
- L1550 _protected prototype_ `void CreateAndRegisterJumpLinksProxy(FNavLinkGenerationJumpConfig& InOutNavLinkJumpConfig, const FNavLinkId LinkProxyId = FNavLinkId::GenerateUniqueId());` — Create and register links proxy. It's expected to be called on load or when the navmesh is rebuilt.
- L1558 _private prototype_ `void DestroyRecastPImpl();` — destroys FPImplRecastNavMesh instance if it has been created
- L1560 _private prototype_ `void UpdateNavVersion();` — @todo docuement
- L1561 _private prototype_ `void UpdateNavObject();`
- L1564 _private prototype_ `URecastNavMeshDataChunk* GetNavigationDataChunk(ULevel* InLevel) const;` — @return Navmesh data chunk that belongs to this actor
- L1567 _private prototype_ `URecastNavMeshDataChunk* GetNavigationDataChunk(const ANavigationDataChunkActor& InActor) const;` — @return Navmesh data chunk that belongs to this actor
- L1570 _private prototype_ `bool HasCompleteDataInTile(const int32 TileX, const int32 TileY) const;` — Check if navmesh is defined (either built/streamed or recognized as empty tile by generator) in given tile
- L1574 _protected function_ `FPImplRecastNavMesh* GetRecastNavMeshImpl()` — retrieves RecastNavMeshImpl
- L1575 _protected function_ `const FPImplRecastNavMesh* GetRecastNavMeshImpl() const`
- L1590 _protected member_ `FUpdateActiveTilesWorkingMem UpdateActiveTilesWorkingMem;`
- L1594 _private prototype_ `URecastNavMeshDataChunk* GetNavigationDataChunk(const TArray<UNavigationDataChunk*>& InChunks) const;` — @return Navmesh data chunk that belongs to this actor
- L1597 _private member_ `uint32 NavMeshVersion;` — NavMesh versioning.
- L1605 _private member_ `FPImplRecastNavMesh* RecastNavMeshImpl;` — This is a pimpl-style arrangement used to tightly hide the Recast internals from the rest of the engine. Using this class should *not* require the inclusion of the private RecastNavMesh.h @NOTE: if we switch over to C++11 this should be unique_ptr @TODO since it's no secret we're using recast there's no point in having separate implementation class. FPImplRecastNavMesh should be merged into ARecastNavMesh
- L1609 _private member_ `mutable int32 BatchQueryCounter;` — batch query counter
- L1614 _private member_ `static const FRecastQueryFilter* NamedFilters[ERecastNamedFilter::NamedFiltersCount];`
- L1616 _private function_ `virtual bool IsNodeRefValid(NavNodeRef NodeRef) const override`
- L1618 _private function_ `virtual void BatchRaycast(TArray<FNavigationRaycastWork>& Workload, FSharedConstNavQueryFilter QueryFilter, const UObject* Querier = nullptr) const override`
- L1619 _private function_ `virtual bool FindMoveAlongSurface(const FNavLocation& StartLocation, const FVector& TargetPosition, FNavLocation& OutLocation, FSharedConstNavQueryFilter Filter = nullptr, const UObject* Querier = nullptr) const override`
- L1620 _private function_ `virtual void BatchFindMoveAlongSurface(TArray<FNavigationFindMoveAlongSurfaceWork>& Workload, FSharedConstNavQueryFilter Filter = NULL, const UObject* Querier = NULL) const override`
- L1621 _private function_ `virtual bool FindOverlappingEdges(const FNavLocation& StartLocation, TConstArrayView<FVector> ConvexPolygon, TArray<FVector>& OutEdges, FSharedConstNavQueryFilter Filter = nullptr, const UObject* Querier = nullptr) const override`
- L1622 _private function_ `virtual bool GetPathSegmentBoundaryEdges(const FNavigationPath& Path, const FNavPathPoint& StartPoint, const FNavPathPoint& EndPoint, const TConstArrayView<FVector> SearchArea, TArray<FVector>& OutEdges, const float MaxAreaEnterCost, FSharedConstNavQueryFilter Filter = nullptr, const UObject* Querier = nullptr) const override`
- L1623 _private function_ `virtual FNavLocation GetRandomPoint(FSharedConstNavQueryFilter Filter = nullptr, const UObject* Querier = nullptr) const override`
- L1624 _private function_ `virtual bool GetRandomReachablePointInRadius(const FVector& Origin, float Radius, FNavLocation& OutResult, FSharedConstNavQueryFilter Filter = nullptr, const UObject* Querier = nullptr) const override`
- L1625 _private function_ `virtual bool GetRandomPointInNavigableRadius(const FVector& Origin, float Radius, FNavLocation& OutResult, FSharedConstNavQueryFilter Filter = nullptr, const UObject* Querier = nullptr) const override`
- L1626 _private function_ `virtual bool ProjectPoint(const FVector& Point, FNavLocation& OutLocation, const FVector& Extent, FSharedConstNavQueryFilter Filter = nullptr, const UObject* Querier = nullptr) const override`
- L1627 _private function_ `virtual void BatchProjectPoints(TArray<FNavigationProjectionWork>& Workload, const FVector& Extent, FSharedConstNavQueryFilter Filter = nullptr, const UObject* Querier = nullptr) const override`
- L1628 _private function_ `virtual void BatchProjectPoints(TArray<FNavigationProjectionWork>& Workload, FSharedConstNavQueryFilter Filter = nullptr, const UObject* Querier = nullptr) const override`
- L1629 _private function_ `virtual ENavigationQueryResult::Type CalcPathCost(const FVector& PathStart, const FVector& PathEnd, FVector::FReal& OutPathCost, FSharedConstNavQueryFilter QueryFilter = nullptr, const UObject* Querier = nullptr) const override`
- L1630 _private function_ `virtual ENavigationQueryResult::Type CalcPathLength(const FVector& PathStart, const FVector& PathEnd, FVector::FReal& OutPathLength, FSharedConstNavQueryFilter QueryFilter = nullptr, const UObject* Querier = nullptr) const override`
- L1631 _private function_ `virtual ENavigationQueryResult::Type CalcPathLengthAndCost(const FVector& PathStart, const FVector& PathEnd, FVector::FReal& OutPathLength, FVector::FReal& OutPathCost, FSharedConstNavQueryFilter QueryFilter = nullptr, const UObject* Querier = nullptr) const override`
- L1632 _private function_ `virtual bool DoesNodeContainLocation(NavNodeRef NodeRef, const FVector& WorldSpaceLocation) const override`
- L1642 _public prototype_ `bool K2_ReplaceAreaInTileBounds(FBox Bounds, TSubclassOf<UNavArea> OldArea, TSubclassOf<UNavArea> NewArea, bool ReplaceLinks = true);` — `UFUNCTION(BlueprintCallable, Category = NavMesh, meta = (DisplayName = "ReplaceAreaInTileBounds"))` — @return true if any polygon/link has been touched
- L1647 _function_ `bool ARecastNavMesh::NavMeshRaycast(const ANavigationData* Self, const FVector& RayStart, const FVector& RayEnd, FVector& HitLocation, FSharedConstNavQueryFilter QueryFilter, const UObject* Querier)`
- L1653 _function_ `bool ARecastNavMesh::NavMeshRaycast(const ANavigationData* Self, const FVector& RayStart, const FVector& RayEnd, FVector& HitLocation, FNavigationRaycastAdditionalResults* AdditionalResults, FSharedConstNavQueryFilter QueryFilter, const UObject* Querier)`

#### struct `ARecastNavMesh::FRaycastResult`  
`struct FRaycastResult`  
_L950-977_
- L957 _public member_ `NavNodeRef CorridorPolys[MAX_PATH_CORRIDOR_POLYS];`
- L958 _public member_ `float CorridorCost[MAX_PATH_CORRIDOR_POLYS];`
- L959 _public member_ `int32 CorridorPolysCount;`
- L960 _public member_ `FVector::FReal HitTime;`
- L961 _public member_ `FVector HitNormal;`
- L962 _public member_ `uint32 bIsRaycastEndInCorridor : 1;`
- L964 _public function_ `FRaycastResult() : CorridorPolysCount(0) , HitTime(TNumericLimits<FVector::FReal>::Max()) , HitNormal(0.f) , bIsRaycastEndInCorridor(false)`
- L974 _public function_ `inline int32 GetMaxCorridorSize() const`
- L975 _public function_ `inline bool HasHit() const`
- L976 _public function_ `inline NavNodeRef GetLastNodeRef() const`

#### enum `ARecastNavMesh::FRaycastResult::(anonymous)`  
``  
_L953-955_

#### struct `ARecastNavMesh::FUpdateActiveTilesWorkingMem`  
`struct FUpdateActiveTilesWorkingMem`  
_L1577-1589_
- L1579 _public member_ `TSet<FIntPoint> OldActiveSet;`
- L1583 _public member_ `TArray<FNavMeshDirtyTileElement> TilesInMinDistance;` — `UE_DEPRECATED(5.5, "TilesInMinDistance not used anymore, use TilesInMinDistanceMap instead.")`
- L1585 _public member_ `TMap<FIntPoint, FNavMeshDirtyTileElement> TilesInMinDistanceMap;`
- L1587 _public member_ `TSet<FIntPoint> TilesInMaxDistance;`
- L1588 _public member_ `TArray<FIntPoint> TileToAppend;`

#### struct `FRecastNavMeshCachedData`  
`struct FRecastNavMeshCachedData`  
_L1667-1678_
- desc: structure to cache owning RecastNavMesh data so that it doesn't have to be polled directly from RecastNavMesh while asyncronously generating navmesh
- L1669 _public member_ `ARecastNavMesh::FNavPolyFlags FlagsPerArea[RECAST_MAX_AREAS];`
- L1670 _public member_ `ARecastNavMesh::FNavPolyFlags FlagsPerOffMeshLinkArea[RECAST_MAX_AREAS];`
- L1671 _public member_ `TMap<const UClass*, int32> AreaClassToIdMap;`
- L1672 _public member_ `TWeakObjectPtr<const ARecastNavMesh> ActorOwner;`
- L1673 _public member_ `uint32 bUseSortFunction : 1;`
- L1675 _public prototype_ `static FRecastNavMeshCachedData Construct(const ARecastNavMesh* RecastNavMeshActor);`
- L1676 _public prototype_ `void OnAreaAdded(const UClass* AreaClass, int32 AreaID);`
- L1677 _public prototype_ `void OnAreaRemoved(const UClass* AreaClass);`

#### Free symbols / members of external scopes

- L16 _macro_ `#define RECAST_MAX_SEARCH_NODES 2048`
- L18 _macro_ `#define RECAST_MIN_TILE_SIZE 300.f`
- L20 _macro_ `#define RECAST_MAX_AREAS 64`
- L21 _macro_ `#define RECAST_DEFAULT_AREA (RECAST_MAX_AREAS - 1)`
- L22 _macro_ `#define RECAST_LOW_AREA (RECAST_MAX_AREAS - 2)`
- L23 _macro_ `#define RECAST_NULL_AREA 0`
- L26 _macro_ `#define RECAST_UNWALKABLE_POLY_COST FLT_MAX` — Note poly costs are still floats in UE so we are using FLT_MAX as unwalkable still. Path CostLimit and Distance are based on FVector::FReal.
- L31 _macro_ `#define RECAST_ASYNC_REBUILDING 1`
- L36 _macro_ `#define ALLOW_TIME_SLICE_NAV_REGEN 0`
- L40 _macro_ `#define TIME_SLICE_NAV_REGEN (ALLOW_TIME_SLICE_NAV_REGEN && !RECAST_ASYNC_REBUILDING)` — TIME_SLICE_NAV_REGEN must be 0 if we are async rebuilding recast
- L64 _namespace_ `namespace ERecastPartitioning`
- L123 _namespace_ `namespace ERecastPathFlags`
- L126 _variable_ `inline const int32 SkipStringPulling = (1 << 0);` (scope `ERecastPathFlags`) — If set, path won't be post processed.
- L129 _variable_ `inline const int32 GenerateCorridor = (1 << 1);` (scope `ERecastPathFlags`) — If set, path will contain navigation corridor.
- L132 _variable_ `inline const uint8 FirstAvailableFlag = 2;` (scope `ERecastPathFlags`) — Make your game-specific flags start at this index
- L157 _function_ `inline friend uint32 GetTypeHash(const FRecastDebugPathfindingNode& Other)`
- L162 _namespace_ `namespace ERecastDebugPathfindingFlags`
- L285 _function_ `inline friend uint32 GetTypeHash(const FNavTileRef& NavTileRef)`
- L312 _namespace_ `namespace ERecastNamedFilter`
- L540 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnNavMeshUpdate);`
- L540 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnNavMeshUpdate);`
- L542 _namespace_ `namespace FNavMeshConfig`
- L954 _enumerator_ `MAX_PATH_CORRIDOR_POLYS = 128` (scope `ARecastNavMesh::FRaycastResult::__anonefdacc060103`)

### `Source/Runtime/NavigationSystem/Public/NavMesh/RecastNavMeshDataChunk.h` (Public)


#### struct `FRecastTileData`  
`struct FRecastTileData`  
_L12-42_
- L22 _public prototype_ `FRecastTileData();`
- L23 _public prototype_ `FRecastTileData(int32 TileDataSize, uint8* TileRawData, int32 TileCacheDataSize, uint8* TileCacheRawData);`
- L26 _public member_ `int32 OriginalX;` — Location of attached tile
- L27 _public member_ `int32 OriginalY;` — Tile Y coordinates when gathered
- L28 _public member_ `int32 X;`
- L29 _public member_ `int32 Y;`
- L30 _public member_ `int32 Layer;`
- L33 _public member_ `int32 TileDataSize;` — Tile data
- L34 _public member_ `TSharedPtr<FRawData> TileRawData;`
- L37 _public member_ `int32 TileCacheDataSize;` — Compressed tile cache layer
- L38 _public member_ `TSharedPtr<FRawData> TileCacheRawData;`
- L41 _public member_ `bool bAttached;` — Whether this tile is attached to NavMesh

#### struct `FRecastTileData::FRawData`  
`struct FRawData`  
_L14-20_
- L16 _public prototype_ `FRawData(uint8* InData);`
- L17 _public prototype_ `~FRawData();`
- L19 _public member_ `uint8* RawData;`

#### enum `EGatherTilesCopyMode`  
`enum EGatherTilesCopyMode`  
_L47-53_
- L49 _public enumerator_ `NoCopy = 0`
- L50 _public enumerator_ `CopyData = 1 << 0`
- L51 _public enumerator_ `CopyCacheData = 1 << 1`
- L52 _public enumerator_ `CopyDataAndCacheData = (CopyData | CopyCacheData)`

#### class `URecastNavMeshDataChunk`  
`class URecastNavMeshDataChunk : public UNavigationDataChunk`  
_L59-123_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UNavigationDataChunk`
- L64 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L69 _private prototype_ `TArray<FNavTileRef> AttachTiles(ARecastNavMesh& NavMesh);` — Attaches tiles to specified navmesh, transferring tile ownership to navmesh
- L72 _private prototype_ `TArray<FNavTileRef> AttachTiles(ARecastNavMesh& NavMesh, const bool bKeepCopyOfData, const bool bKeepCopyOfCacheData);` — Attaches tiles to specified navmesh
- L75 _private prototype_ `TArray<FNavTileRef> DetachTiles(ARecastNavMesh& NavMesh);` — Detaches tiles from specified navmesh, taking tile ownership
- L78 _private prototype_ `TArray<FNavTileRef> DetachTiles(ARecastNavMesh& NavMesh, const bool bTakeDataOwnership, const bool bTakeCacheDataOwnership);` — Detaches tiles from specified navmesh
- L88 _private prototype_ `void MoveTiles(FPImplRecastNavMesh& NavMeshImpl, const FIntPoint& Offset, const FVector::FReal RotationDeg, const FVector2D& RotationCenter);` — Experimental: Moves tiles data on the xy plane by the offset (in tile coordinates) and rotation (in degree). @param NavMeshImpl		Recast navmesh implementation. @param Offset			Offset in tile coordinates. @param RotationDeg		Rotation in degrees. @param RotationCenter	World position
- L91 _private prototype_ `int32 GetNumTiles() const;` — Number of tiles in this chunk
- L94 _private function_ `const TArray<FRecastTileData>& GetTiles() const` — Const accessor to the list of tiles in the data chunk.
- L98 _private prototype_ `void GetTilesBounds(const FPImplRecastNavMesh& NavMeshImpl, const TArray<FNavTileRef>& TileRefs, FBox& OutBounds) const;` — Returns the AABB for the given tiles.
- L102 _private function_ `TArray<FRecastTileData>& GetMutableTiles()` — Mutable accessor to the list of tiles in the data chunk.
- L105 _private prototype_ `void ReleaseTiles();` — Releases all tiles that this chunk holds
- L109 _private prototype_ `void GetTiles(const FPImplRecastNavMesh* NavMeshImpl, const TArray<int32>& TileIndices, const EGatherTilesCopyMode CopyMode, const bool bMarkAsAttached = true);` — `UE_DEPRECATED(5.5, "Use the version of this function that takes an array of FNavTileRefs instead.")` — Collect tiles with data and/or cache data from the provided TileIndices.
- L113 _private prototype_ `void GetTiles(const FPImplRecastNavMesh* NavMeshImpl, const TArray<FNavTileRef>& TileRefs, const EGatherTilesCopyMode CopyMode, const bool bMarkAsAttached = true);` — Collect tiles with data and/or cache data from the provided tile references.
- L118 _private prototype_ `void SerializeRecastData(FArchive& Ar, int32 NavMeshVersion);`
- L122 _private member_ `TArray<FRecastTileData> Tiles;`

### `Source/Runtime/NavigationSystem/Public/NavMesh/RecastNavMeshGenerator.h` (Public)


#### struct `FRecastBuildConfig`  
`struct FRecastBuildConfig : public rcConfig`  
_L49-133_
- inherits: `rcConfig`
- L52 _public member_ `uint32 bPerformVoxelFiltering:1;` — controls whether voxel filtering will be applied (via FRecastTileGenerator::ApplyVoxelFilter)
- L54 _public member_ `uint32 bGenerateDetailedMesh:1;` — generate detailed mesh (additional tessellation to match heights of geometry)
- L56 _public member_ `uint32 bGenerateBVTree:1;` — generate BV tree (space partitioning for queries)
- L58 _public member_ `uint32 bMarkLowHeightAreas : 1;` — if set, mark areas with insufficient free height instead of cutting them out
- L61 _public member_ `uint32 bUseExtraTopCellWhenMarkingAreas : 1;` — Expand the top of the area nav modifier's bounds by one cell height when applying to the navmesh. If unset, navmesh on top of surfaces might not be marked by marking bounds flush with top surfaces (since navmesh is generated slightly above collision, depending on cell height).
- L63 _public member_ `uint32 bFilterLowSpanSequences : 1;` — if set, only single low height span will be allowed under valid one
- L65 _public member_ `uint32 bFilterLowSpanFromTileCache : 1;` — if set, only low height spans with corresponding area modifier will be stored in tile cache (reduces memory, can't modify without full tile rebuild)
- L67 _public member_ `uint32 bGenerateLinks : 1;` — if set, navigation links will be automatically generated
- L69 _public member_ `uint32 bMinimizeLinkPoolSize : 1;` — if set, minimize base link pool size, else use previous larger base link pool.
- L72 _public member_ `int32 TileCachePartitionType;` — region partitioning method used by tile cache
- L74 _public member_ `int32 TileCacheChunkSize;` — chunk size for ChunkyMonotone partitioning
- L78 _public member_ `int32 MaxPolysPerTile;` — indicates what's the limit of navmesh polygons per tile. This value is calculated from other factors - DO NOT SET IT TO ARBITRARY VALUE
- L81 _public member_ `TArray<dtNavLinkBuilderJumpConfig> JumpConfigs;` — NavLink building configuration
- L84 _public member_ `float AgentHeight;` — Actual agent height (in uu)
- L86 _public member_ `float AgentMaxClimb;` — Actual agent climb (in uu)
- L88 _public member_ `float AgentRadius;` — Actual agent radius (in uu)
- L90 _public member_ `int32 AgentIndex;` — Agent index for filtering links
- L92 _public member_ `ENavigationDataResolution TileResolution;` — Resolution level
- L94 _public member_ `float AverageLayersPerTile;` — Average layers per tile
- L96 _public member_ `ENavigationLedgeSlopeFilterMode LedgeSlopeFilterMode;` — Ledge filtering mode
- L98 _public member_ `bool bIsTileSetupConfigCompleted;` — Is the config completely setup
- L100 _public member_ `float LinkSpillDistance;` — Used when generating links automatically. Distance representing how far generated links can go outside a tile (in uu).
- L102 _public function_ `FRecastBuildConfig()`
- L107 _public function_ `void Reset()`
- L129 _public function_ `rcReal GetTileSizeUU() const`
- L132 _public prototype_ `bool IsUsingCoarseCellSize() const;` — Detects if we are using big cell size values in relation to the walkableClimb and walkableSlopeAngle.

#### struct `FRecastVoxelCache`  
`struct FRecastVoxelCache`  
_L135-153_
- L146 _public member_ `int32 NumTiles;`
- L149 _public member_ `FTileInfo* Tiles;` — tile info
- L151 _public function_ `FRecastVoxelCache()`
- L152 _public prototype_ `FRecastVoxelCache(const uint8* Memory);`

#### struct `FRecastVoxelCache::FTileInfo`  
`struct FTileInfo`  
_L137-144_
- L139 _public member_ `int32 TileX;`
- L140 _public member_ `int32 TileY;`
- L141 _public member_ `int32 NumSpans;`
- L142 _public member_ `FTileInfo* NextTile;`
- L143 _public member_ `rcSpanCache* SpanData;`

#### struct `FRecastGeometryCache`  
`struct FRecastGeometryCache`  
_L155-178_
- L168 _public member_ `FHeader Header;`
- L171 _public member_ `FVector::FReal* Verts;` — recast coords of vertices (size: NumVerts * 3)
- L174 _public member_ `int32* Indices;` — vert indices for triangles (size: NumFaces * 3)
- L176 _public function_ `FRecastGeometryCache()`
- L177 _public prototype_ `FRecastGeometryCache(const uint8* Memory);`

#### struct `FRecastGeometryCache::FHeader`  
`struct FHeader`  
_L157-166_
- L159 _public member_ `FNavigationRelevantData::FCollisionDataHeader Validation;`
- L161 _public member_ `int32 NumVerts;`
- L162 _public member_ `int32 NumFaces;`
- L163 _public member_ `struct FWalkableSlopeOverride SlopeOverride;`
- L165 _public member_ `static uint32 StaticMagicNumber;`

#### struct `FRecastRawGeometryElement`  
`struct FRecastRawGeometryElement`  
_L180-202_
- L183 _public member_ `TArray<FVector::FReal> GeomCoords;` — Instance geometry
- L184 _public member_ `TArray<int32> GeomIndices;`
- L187 _public member_ `FBox GeomCoordsBounds;` — Bounds of the geometry
- L191 _public member_ `TArray<FTransform> PerInstanceTransform;` — Per instance transformations in unreal coords When empty, geometry is in world space
- L193 _public member_ `rcRasterizationFlags RasterizationFlags;`
- L196 _public member_ `TSubclassOf<UNavAreaBase> AreaClass;` — Nav area for collision triangles. If set, replaces RC_WALKABLE_AREA during rasterization.
- L198 _public prototype_ `static rcRasterizationFlags GetRasterizationFlags(const FCompositeNavModifier& InModifier);`
- L201 _public prototype_ `static TSubclassOf<UNavAreaBase> GetCollisionAreaClass(const FCompositeNavModifier& InModifier);` — Extracts AreaClass from nav modifier (UNavCollision creates single area modifier).

#### struct `FRecastAreaNavModifierElement`  
`struct FRecastAreaNavModifierElement`  
_L204-215_
- L206 _public member_ `TArray<FAreaNavModifier> Areas;`
- L210 _public member_ `TArray<FTransform> PerInstanceTransform;` — Per instance transformations in unreal coords When empty, areas are in world space
- L212 _public member_ `ENavigationDataResolution NavMeshResolution = ENavigationDataResolution::Invalid;`
- L214 _public member_ `bool bMaskFillCollisionUnderneathForNavmesh = false;`

#### struct `FRcTileBox`  
`struct FRcTileBox`  
_L217-275_
- L219 _public member_ `int32 XMin, XMax, YMin, YMax;`
- L219 _public member_ `int32 XMin, XMax, YMin, YMax;`
- L219 _public member_ `int32 XMin, XMax, YMin, YMax;`
- L219 _public member_ `int32 XMin, XMax, YMin, YMax;`
- L221 _public function_ `FRcTileBox(const FBox& UnrealBounds, const FVector& RcNavMeshOrigin, const FVector::FReal TileSizeInWorldUnits)`
- L260 _public function_ `inline bool Contains(const FIntPoint& Point) const`
- L266 _public function_ `static inline int32 ClampToInt32(const int64 Value)`

#### enum `ETimeSliceWorkResult`  
`enum class ETimeSliceWorkResult : uint8`  
_L286-291_
- desc: Return state of calling time sliced functions
- L288 _public enumerator_ `Failed`
- L289 _public enumerator_ `Succeeded`
- L290 _public enumerator_ `CallAgainNextTimeSlice`

#### enum `EGenerateCompressedLayersTimeSliced`  
`enum class EGenerateCompressedLayersTimeSliced : uint8`  
_L294-307_
- desc: State representing which area of GenerateCompressedLayersTimeSliced() we are processing
- L296 _public enumerator_ `Invalid`
- L297 _public enumerator_ `Init`
- L298 _public enumerator_ `CreateHeightField`
- L299 _public enumerator_ `RasterizeTriangles`
- L300 _public enumerator_ `EmptyLayers`
- L301 _public enumerator_ `VoxelFilter`
- L302 _public enumerator_ `RecastFilter`
- L303 _public enumerator_ `CompactHeightField`
- L304 _public enumerator_ `ErodeWalkable`
- L305 _public enumerator_ `BuildLayers`
- L306 _public enumerator_ `BuildTileCache`

#### enum `ERasterizeGeomRecastTimeSlicedState`  
`enum class ERasterizeGeomRecastTimeSlicedState : uint8`  
_L309-313_
- L311 _public enumerator_ `MarkWalkableTriangles`
- L312 _public enumerator_ `RasterizeTriangles`

#### enum `ERasterizeGeomTimeSlicedState`  
`enum class ERasterizeGeomTimeSlicedState : uint8`  
_L315-320_
- L317 _public enumerator_ `RasterizeGeometryTransformCoordsAndFlipIndices`
- L318 _public enumerator_ `RasterizeGeometryTransformCoords UE_DEPRECATED(5.5, "The state doesn't handle indices flipping. Use RasterizeGeometryTransformCoordsAndIndices instead.") = RasterizeGeometryTransformCoordsAndFlipIndices`
- L319 _public enumerator_ `RasterizeGeometryRecast`

#### enum `EGenerateRecastFilterTimeSlicedState`  
`enum class EGenerateRecastFilterTimeSlicedState : uint8`  
_L322-327_
- L324 _public enumerator_ `FilterLowHangingWalkableObstacles`
- L325 _public enumerator_ `FilterLedgeSpans`
- L326 _public enumerator_ `FilterWalkableLowHeightSpans`

#### enum `EDoWorkTimeSlicedState`  
`enum class EDoWorkTimeSlicedState : uint8`  
_L329-334_
- L331 _public enumerator_ `Invalid`
- L332 _public enumerator_ `GatherGeometryFromSources`
- L333 _public enumerator_ `GenerateTile`

#### enum `EGenerateTileTimeSlicedState`  
`enum class EGenerateTileTimeSlicedState : uint8`  
_L336-341_
- L338 _public enumerator_ `Invalid`
- L339 _public enumerator_ `GenerateCompressedLayers`
- L340 _public enumerator_ `GenerateNavigationData`

#### enum `EGenerateNavDataTimeSlicedState`  
`enum class EGenerateNavDataTimeSlicedState : uint8`  
_L343-348_
- L345 _public enumerator_ `Invalid`
- L346 _public enumerator_ `Init`
- L347 _public enumerator_ `GenerateLayers`

#### struct `FRecastTileTimeSliceSettings`  
`struct FRecastTileTimeSliceSettings`  
_L350-353_
- L352 _public member_ `int32 FilterLedgeSpansMaxYProcess = 13;`

#### struct `FGeneratedNavigationLink`  
`struct FGeneratedNavigationLink : public FNavigationLink`  
_L355-362_
- inherits: `FNavigationLink`
- L358 _public member_ `unsigned short generatedLinkPolyFlag = 0;` — User defined flags assigned to the polys of off-mesh connections
- L361 _public member_ `unsigned char generatedLinkArea = 0;` — User defined area ids assigned to the off-mesh connections

#### class `FRecastTileGenerator`  
`class FRecastTileGenerator : public FNoncopyable, public FGCObject`  
_L369-617_
- inherits: `FNoncopyable,FGCObject`
- desc: Class handling generation of a single tile, caching data that can speed up subsequent tile generations
- L374 _public prototype_ `FRecastTileGenerator(FRecastNavMeshGenerator& ParentGenerator, const FIntPoint& Location, const double PendingTileCreationTime);`
- L375 _public prototype_ `virtual ~FRecastTileGenerator();`
- L380 _public prototype_ `ETimeSliceWorkResult DoWorkTimeSliced();` — Does the work involved with regenerating this tile using time slicing. The return value determines the result of the time slicing
- L382 _public prototype_ `bool DoWork();` — Does the work involved with regenerating this tile
- L384 _public function_ `inline int32 GetTileX() const`
- L385 _public function_ `inline int32 GetTileY() const`
- L386 _public function_ `inline const FBox& GetTileBB() const`
- L388 _public function_ `inline bool IsLayerChanged(int32 LayerIdx) const` — Whether specified layer was updated
- L389 _public function_ `inline const TBitArray<>& GetDirtyLayersMask() const`
- L391 _public function_ `inline bool IsFullyRegenerated() const` — Whether tile data was fully regenerated
- L393 _public prototype_ `bool HasDataToBuild() const;` — Whether tile task has anything to build
- L395 _public function_ `const TArray<FNavMeshTileData>& GetCompressedLayers() const`
- L397 _public prototype_ `static FBox CalculateTileBounds(int32 X, int32 Y, const FVector& RcNavMeshOrigin, const FBox& TotalNavBounds, FVector::FReal TileSizeInWorldUnits);`
- L401 _protected function_ `TArray<FNavMeshTileData>& GetNavigationData()` — to be used solely by FRecastNavMeshGenerator
- L404 _public prototype_ `uint32 GetUsedMemCount() const;`
- L407 _public member_ `uint32 UsedMemoryOnStartup;` — Memory amount used to construct generator
- L410 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject begin
- L411 _public prototype_ `virtual FString GetReferencerName() const override;`
- L415 _public function_ `const FRecastInternalDebugData& GetDebugData() const`
- L416 _public function_ `FRecastInternalDebugData& GetMutableDebugData()`
- L419 _public typedef_ `typedef TArray<int32, TInlineAllocator<4096>> TInlineMaskArray;`
- L429 _protected prototype_ `ETimeSliceWorkResult GenerateTileTimeSliced();` — Does the actual TimeSliced tile generation. @note always trigger tile generation only via DoWorkTimeSliced(). This is a worker function The return value determines the result of the time slicing @return Suceeded if new tile navigation data has been generated and is ready to be added to navmesh instance, @return Failed if failed or no need to generate (still valid). @return CallAgainNextTimeSlice, time slice is finished this frame but we need to call this function again next frame
- L436 _protected prototype_ `bool GenerateTile();` — Does the actual tile generation. @note always trigger tile generation only via DoWorkTime(). This is a worker function The return value determines the result of the time slicing @return true if new tile navigation data has been generated and is ready to be added to navmesh instance, @return false if failed or no need to generate (still valid).
- L438 _protected prototype_ `void Setup(const FRecastNavMeshGenerator& ParentGenerator, const TArray<FBox>& DirtyAreas);`
- L441 _protected prototype_ `void SetupTileConfigFromHighestResolution(const FRecastNavMeshGenerator& ParentGenerator);` — Find highest navmesh resolution from Modifiers and use it to update the tile configuration.
- L444 _protected prototype_ `virtual void GatherGeometry(const FRecastNavMeshGenerator& ParentGenerator, bool bGeometryChanged);` — Gather geometry
- L446 _protected prototype_ `virtual void PrepareGeometrySources(const FRecastNavMeshGenerator& ParentGenerator, bool bGeometryChanged);` — Gather geometry sources to be processed later by the GatherGeometryFromSources
- L448 _protected prototype_ `void GatherGeometryFromSources();` — Gather geometry from the prefetched sources
- L450 _protected prototype_ `ETimeSliceWorkResult GatherGeometryFromSourcesTimeSliced();` — Gather geometry from the prefetched sources time sliced version
- L452 _protected prototype_ `void GatherNavigationDataGeometry(const TSharedRef<FNavigationRelevantData, ESPMode::ThreadSafe>& ElementData, UNavigationSystemV1& NavSys, const FNavDataConfig& OwnerNavDataConfig, bool bGeometryChanged);` — Gather geometry from a specified Navigation Data
- L455 _protected prototype_ `bool CreateHeightField(FNavMeshBuildContext& BuildContext);` — Start functions used by GenerateCompressedLayersTimeSliced / GenerateCompressedLayers
- L456 _protected prototype_ `ETimeSliceWorkResult RasterizeTrianglesTimeSliced(FNavMeshBuildContext& BuildContext, FTileRasterizationContext& RasterContext);`
- L457 _protected prototype_ `void RasterizeTriangles(FNavMeshBuildContext& BuildContext, FTileRasterizationContext& RasterContext);`
- L458 _protected prototype_ `ETimeSliceWorkResult RasterizeGeometryRecastTimeSliced(FNavMeshBuildContext& BuildContext, const TArray<FVector::FReal>& Coords, const TArray<int32>& Indices, const FBox& CoordsBounds, const rcRasterizationFlags RasterizationFlags, FTileRasterizationContext& RasterContext, TSubclassOf<UNavAreaBase> AreaClass = nullptr);`
- L459 _protected prototype_ `void RasterizeGeometryRecast(FNavMeshBuildContext& BuildContext, const TArray<FVector::FReal>& Coords, const TArray<int32>& Indices, const FBox& CoordsBounds, const rcRasterizationFlags RasterizationFlags, FTileRasterizationContext& RasterContext, TSubclassOf<UNavAreaBase> AreaClass = nullptr);`
- L460 _protected prototype_ `void RasterizeGeometryTransformCoordsAndFlipIndices(const TArray<FVector::FReal>& Coords, const TArray<int32>& Indices, const FBox& CoordsBounds, const FTransform& LocalToWorld);`
- L461 _protected prototype_ `ETimeSliceWorkResult RasterizeGeometryTimeSliced(FNavMeshBuildContext& BuildContext, const TArray<FVector::FReal>& Coords, const TArray<int32>& Indices, const FBox& CoordsBounds, const FTransform& LocalToWorld, const rcRasterizationFlags RasterizationFlags, FTileRasterizationContext& RasterContext, TSubclassOf<UNavAreaBase> AreaClass = nullptr);`
- L462 _protected prototype_ `void RasterizeGeometry(FNavMeshBuildContext& BuildContext, const TArray<FVector::FReal>& Coords, const TArray<int32>& Indices, const FBox& CoordsBounds, const FTransform& LocalToWorld, const rcRasterizationFlags RasterizationFlags, FTileRasterizationContext& RasterContext, TSubclassOf<UNavAreaBase> AreaClass = nullptr);`
- L463 _protected prototype_ `void GenerateRecastFilter(FNavMeshBuildContext& BuildContext);`
- L464 _protected prototype_ `ETimeSliceWorkResult GenerateRecastFilterTimeSliced(FNavMeshBuildContext& BuildContext);`
- L465 _protected prototype_ `bool BuildCompactHeightField(FNavMeshBuildContext& BuildContext);`
- L466 _protected prototype_ `bool RecastErodeWalkable(FNavMeshBuildContext& BuildContext);`
- L467 _protected prototype_ `bool RecastBuildLayers(FNavMeshBuildContext& BuildContext, FTileRasterizationContext& RasterContext);`
- L468 _protected prototype_ `bool RecastBuildTileCache(FNavMeshBuildContext& BuildContext, FTileRasterizationContext& RasterContext);`
- L472 _protected prototype_ `virtual ETimeSliceWorkResult GenerateCompressedLayersTimeSliced(FNavMeshBuildContext& BuildContext);` — Builds CompressedLayers array (geometry + modifiers) time sliced
- L475 _protected prototype_ `virtual bool GenerateCompressedLayers(FNavMeshBuildContext& BuildContext, const dtLinkBuilderData& InLinkBuilderData);` — Builds CompressedLayers array (geometry + modifiers)
- L478 _protected prototype_ `bool GenerateNavigationDataLayer(FNavMeshBuildContext& BuildContext, FTileCacheCompressor& TileCompressor, FTileCacheAllocator& GenNavAllocator, FTileGenerationContext& GenerationContext, const dtLinkBuilderData& InLinkBuilderData, int32 LayerIdx);` — Builds a navigation data layer
- L481 _protected prototype_ `ETimeSliceWorkResult GenerateNavigationDataTimeSliced(FNavMeshBuildContext& BuildContext, const dtLinkBuilderData& InLinkBuilderData);` — Builds NavigationData array (layers + obstacles) time sliced
- L484 _protected prototype_ `bool GenerateNavigationData(FNavMeshBuildContext& BuildContext, const dtLinkBuilderData& InLinkBuilderData);` — Builds NavigationData array (layers + obstacles)
- L487 _protected prototype_ `dtStatus BuildTileCacheLinks(FNavMeshBuildContext& BuildContext, struct dtTileCacheAlloc* alloc, const dtTileCacheLayer& layer, const struct dtTileCacheContourSet& lcset, const float DefaultSnapHeight, TInlineGeneratedNavLinkArray& OutGeneratedLinks) const;` — Builds navigation links
- L490 _protected prototype_ `virtual void ApplyVoxelFilter(struct rcHeightfield* SolidHF, FVector::FReal WalkableRadius);`
- L493 _protected prototype_ `void InitRasterizationMaskArray(const rcHeightfield* InSolidHF, TInlineMaskArray& OutRasterizationMasks);` — Compute rasterization mask
- L494 _protected prototype_ `void ComputeRasterizationMasks(FNavMeshBuildContext& BuildContext, FTileRasterizationContext& RasterContext);`
- L495 _protected prototype_ `void MarkRasterizationMask(rcContext* , rcHeightfield* InSolidHF, const FAreaNavModifier& Modifier, const FTransform& LocalToWorld, const int32 Mask, TInlineMaskArray& OutMaskArray);`
- L499 _protected prototype_ `void MarkDynamicAreas(FNavMeshBuildContext& BuildContext, dtTileCacheLayer& Layer);` — apply areas from DynamicAreas to layer
- L500 _protected prototype_ `void MarkDynamicArea(FNavMeshBuildContext& BuildContext, const FAreaNavModifier& Modifier, const FTransform& LocalToWorld, dtTileCacheLayer& Layer);`
- L501 _protected prototype_ `void MarkDynamicArea(FNavMeshBuildContext& BuildContext, const FAreaNavModifier& Modifier, const FTransform& LocalToWorld, dtTileCacheLayer& Layer, const int32 AreaId, const int32* ReplaceAreaIdPtr);`
- L503 _protected prototype_ `void AppendModifier(const FCompositeNavModifier& Modifier, const FNavDataPerInstanceTransformDelegate& InTransformsDelegate);`
- L505 _protected prototype_ `void ValidateAndAppendGeometry(const FNavigationRelevantData& ElementData, const FCompositeNavModifier& InModifier);` — Appends specified geometry to tile's geometry
- L507 _protected prototype_ `void AppendGeometry(const FNavigationRelevantData& ElementData, const FCompositeNavModifier& InModifier, const FNavDataPerInstanceTransformDelegate& InTransformsDelegate);`
- L510 _protected prototype_ `void PrepareVoxelCache(const TNavStatArray<uint8>& RawCollisionCache, const FBox& RecastBounds, const FCompositeNavModifier& InModifier, TNavStatArray<rcSpanCache>& SpanData);` — prepare voxel cache from collision data
- L511 _protected prototype_ `bool HasVoxelCache(const TNavStatArray<uint8>& RawVoxelCache, rcSpanCache*& CachedVoxels, int32& NumCachedVoxels) const;`
- L512 _protected prototype_ `void AddVoxelCache(TNavStatArray<uint8>& RawVoxelCache, const rcSpanCache* CachedVoxels, const int32 NumCachedVoxels) const;`
- L514 _protected prototype_ `void DumpAsyncData();`
- L515 _protected prototype_ `void DumpSyncData();`
- L518 _protected prototype_ `bool IsTileDebugActive() const;`
- L519 _protected prototype_ `bool IsTileDebugAllowingGeneration() const;`
- L524 _protected prototype_ `void MarkDynamicAreas(dtTileCacheLayer& Layer);` — `UE_DEPRECATED(5.8, "Please use the overload with the added BuildContext.")` — Deprecated functions
- L526 _protected prototype_ `void MarkDynamicArea(const FAreaNavModifier& Modifier, const FTransform& LocalToWorld, dtTileCacheLayer& Layer);` — `UE_DEPRECATED(5.8, "Please use the overload with the added BuildContext.")`
- L528 _protected prototype_ `void MarkDynamicArea(const FAreaNavModifier& Modifier, const FTransform& LocalToWorld, dtTileCacheLayer& Layer, const int32 AreaId, const int32* ReplaceAreaIdPtr);` — `UE_DEPRECATED(5.8, "Please use the overload with the added BuildContext.")`
- L532 _protected member_ `uint32 bRegenerateCompressedLayers : 1;`
- L533 _protected member_ `uint32 bFullyEncapsulatedByInclusionBounds : 1;`
- L534 _protected member_ `uint32 bUpdateGeometry : 1;`
- L535 _protected member_ `uint32 bHasLowAreaModifiers : 1;`
- L536 _protected member_ `uint32 bHasGeometryToRasterizeAsFilledConvexVolume : 1;`
- L539 _protected member_ `ERasterizeGeomRecastTimeSlicedState RasterizeGeomRecastState;` — Start time slicing variables
- L540 _protected member_ `ERasterizeGeomTimeSlicedState RasterizeGeomState;`
- L541 _protected member_ `EGenerateRecastFilterTimeSlicedState GenerateRecastFilterState;`
- L542 _protected member_ `int32 GenRecastFilterLedgeSpansYStart;`
- L543 _protected member_ `EDoWorkTimeSlicedState DoWorkTimeSlicedState;`
- L544 _protected member_ `EGenerateTileTimeSlicedState GenerateTileTimeSlicedState;`
- L546 _protected member_ `EGenerateNavDataTimeSlicedState GenerateNavDataTimeSlicedState;`
- L547 _protected member_ `int32 GenNavDataLayerTimeSlicedIdx;`
- L548 _protected member_ `EGenerateCompressedLayersTimeSliced GenCompressedLayersTimeSlicedState;`
- L549 _protected member_ `int32 RasterizeTrianglesTimeSlicedRawGeomIdx;`
- L550 _protected member_ `int32 RasterizeTrianglesTimeSlicedInstTransformIdx;`
- L551 _protected member_ `TNavStatArray<uint8> RasterizeGeomRecastTriAreas;`
- L552 _protected member_ `const FNavRegenTimeSliceManager* TimeSliceManager;`
- L554 _protected member_ `TUniquePtr<struct FTileCacheAllocator> GenNavDataTimeSlicedAllocator;`
- L555 _protected member_ `TUniquePtr<struct FTileGenerationContext> GenNavDataTimeSlicedGenerationContext;`
- L556 _protected member_ `TUniquePtr<struct FTileRasterizationContext> GenCompressedlayersTimeSlicedRasterContext;`
- L558 _protected member_ `FRecastTileTimeSliceSettings TileTimeSliceSettings;`
- L561 _protected member_ `int32 TileX;`
- L562 _protected member_ `int32 TileY;`
- L563 _protected member_ `uint32 Version;`
- L566 _protected member_ `double TileCreationTime = 0.;` — Time when the tile was requested
- L569 _protected member_ `FBox TileBB;` — Tile's bounding box, Unreal coords
- L572 _protected member_ `FBox TileBBExpandedForAgent;` — Tile's bounding box expanded by Agent's radius horizontally, Unreal coords
- L575 _protected member_ `TBitArray<> DirtyLayers;` — Layers dirty flags
- L578 _protected member_ `FRecastBuildConfig TileConfig;` — Parameters defining navmesh tiles
- L581 _protected member_ `TNavStatArray<FBox> InclusionBounds;` — Bounding geometry definition.
- L584 _protected member_ `FRecastNavMeshCachedData AdditionalCachedData;` — Additional config
- L587 _protected member_ `TArray<FNavMeshTileData> CompressedLayers;` — generated tile data
- L588 _protected member_ `TArray<FNavMeshTileData> NavigationData;`
- L591 _protected member_ `TArray<FVector::FReal> RasterizeGeometryWorldRecastCoords;` — Result of calling RasterizeGeometry()
- L592 _protected member_ `TArray<int32> RasterizeGeometryFlippedIndices;`
- L593 _protected member_ `FBox RasterizeGeometryWorldRecastCoordsBounds;`
- L594 _protected member_ `uint8 bRasterizeGeometryUseFlippedIndices : 1;`
- L597 _protected member_ `TArray<FRecastRawGeometryElement> RawGeometry;` — tile's geometry: without voxel cache
- L599 _protected member_ `TArray<FRecastAreaNavModifierElement> Modifiers;` — areas used for creating navigation data: obstacles
- L601 _protected member_ `TArray<FSimpleLinkNavModifier> OffmeshLinks;` — navigation links
- L603 _protected member_ `TWeakPtr<FNavDataGenerator, ESPMode::ThreadSafe> ParentGeneratorWeakPtr;`
- L605 _protected member_ `TNavStatArray<TSharedRef<FNavigationRelevantData, ESPMode::ThreadSafe> > NavigationRelevantData;`
- L606 _protected member_ `TWeakObjectPtr<UNavigationSystemV1> NavSystem;`
- L607 _protected member_ `FNavDataConfig NavDataConfig;`
- L609 _protected member_ `rcHeightfield* SolidHF;`
- L610 _protected member_ `rcCompactHeightfield* CompactHF;`
- L612 _protected member_ `FRecastNavMeshTileGenerationDebug TileDebugSettings;`
- L615 _protected member_ `FRecastInternalDebugData DebugData;`

#### struct `FRecastTileGeneratorWrapper`  
`struct FRecastTileGeneratorWrapper : public FNonAbandonableTask`  
_L619-637_
- inherits: `FNonAbandonableTask`
- L621 _public member_ `TSharedRef<FRecastTileGenerator> TileGenerator;`
- L623 _public function_ `FRecastTileGeneratorWrapper(TSharedRef<FRecastTileGenerator> InTileGenerator) : TileGenerator(InTileGenerator)`
- L628 _public function_ `void DoWork()`
- L633 _public function_ `inline TStatId GetStatId() const`

#### struct `FPendingTileElement`  
`struct FPendingTileElement`  
_L642-701_
- L645 _public member_ `FIntPoint Coord;` — tile coordinates on a grid in recast space
- L647 _public member_ `FVector::FReal SeedDistance;` — distance to seed, used for sorting pending tiles
- L649 _public member_ `double CreationTime;` — time at which the element was first added to the queue
- L653 _public member_ `FVector::FReal DebugInvokerDistanceSquared = TNumericLimits<FVector::FReal>::Max();` — Squared distance to invoker source
- L656 _public member_ `ENavigationInvokerPriority DebugInvokerPriority = ENavigationInvokerPriority::Default;` — Priority from navigation invoker
- L660 _public member_ `ENavigationInvokerPriority SortingPriority = ENavigationInvokerPriority::Default;` — Priority used for sorting
- L663 _public member_ `bool bRebuildGeometry;` — Whether we need a full rebuild for this tile grid cell
- L667 _public member_ `TArray<FBox> DirtyAreas;` — We need to store dirty area bounds to check which cached layers needs to be regenerated In case geometry is changed, cached layers data will be fully regenerated without using dirty areas list
- L669 _public function_ `FPendingTileElement() : Coord(FIntPoint::NoneValue) , SeedDistance(TNumericLimits<FVector::FReal>::Max()) , CreationTime(-1.) , bRebuildGeometry(false)`
- L677 _public function_ `bool operator == (const FIntPoint& Location) const`
- L682 _public function_ `bool operator == (const FPendingTileElement& Other) const`
- L687 _public function_ `bool operator < (const FPendingTileElement& Other) const`
- L692 _public function_ `double GetDurationSinceCreation(const double CurrenTimeSeconds) const`

#### struct `TRunningTileElement`  
`template<typename TTileGeneratorTask> struct TRunningTileElement`  
_L704-730_
- L706 _public function_ `TRunningTileElement() : Coord(FIntPoint::NoneValue) , bShouldDiscard(false) , AsyncTask(nullptr)`
- L713 _public function_ `TRunningTileElement(FIntPoint InCoord) : Coord(InCoord) , bShouldDiscard(false) , AsyncTask(nullptr)`
- L720 _public function_ `bool operator == (const TRunningTileElement& Other) const`
- L726 _public member_ `FIntPoint Coord;` — tile coordinates on a grid in recast space
- L728 _public member_ `bool bShouldDiscard;` — whether generated results should be discarded
- L729 _public member_ `FAsyncTask<TTileGeneratorTask>* AsyncTask;`

#### struct `FTileTimestamp`  
`struct FTileTimestamp`  
_L735-744_
- L737 _public member_ `FNavTileRef NavTileRef;`
- L738 _public member_ `double Timestamp;`
- L740 _public function_ `bool operator == (const FTileTimestamp& Other) const`

#### enum `EProcessTileTasksSyncTimeSlicedState`  
`enum class EProcessTileTasksSyncTimeSlicedState : uint8`  
_L746-754_
- L748 _public enumerator_ `Init`
- L749 _public enumerator_ `DoWork`
- L750 _public enumerator_ `AddGeneratedTiles`
- L751 _public enumerator_ `StoreCompessedTileCacheLayers`
- L752 _public enumerator_ `AppendUpdateTiles`
- L753 _public enumerator_ `Finish`

#### enum `EAddGeneratedTilesTimeSlicedState`  
`enum class EAddGeneratedTilesTimeSlicedState : uint8`  
_L756-760_
- L758 _public enumerator_ `Init`
- L759 _public enumerator_ `AddTiles`

#### class `FRecastNavMeshGenerator`  
`class FRecastNavMeshGenerator : public FNavDataGenerator`  
_L765-1124_
- inherits: `FNavDataGenerator`
- desc: Class that handles generation of the whole Recast-based navmesh.
- L768 _public prototype_ `FRecastNavMeshGenerator(ARecastNavMesh& InDestNavMesh);`
- L769 _public prototype_ `virtual ~FRecastNavMeshGenerator();`
- L773 _private function_ `FRecastNavMeshGenerator(FRecastNavMeshGenerator const& NoCopy)` — Prevent copying.
- L774 _private function_ `FRecastNavMeshGenerator& operator=(FRecastNavMeshGenerator const& NoCopy)`
- L777 _public prototype_ `virtual bool RebuildAll() override;`
- L778 _public prototype_ `virtual void EnsureBuildCompletion() override;`
- L779 _public prototype_ `virtual void CancelBuild() override;`
- L780 _public prototype_ `virtual void TickAsyncBuild(float DeltaSeconds) override;`
- L781 _public prototype_ `virtual void OnNavigationBoundsChanged() override;`
- L784 _public prototype_ `virtual void RebuildDirtyAreas(const TArray<FNavigationDirtyArea>& DirtyAreas) override;` — Asks generator to update navigation affected by DirtyAreas
- L787 _public prototype_ `virtual bool IsBuildInProgressCheckDirty() const override;` — determines whether this generator is performing navigation building actions at the moment, dirty areas are also checked
- L791 _public prototype_ `virtual bool GetTimeSliceData(int32& OutNumRemainingBuildTasks, double& OutCurrentBuildTaskDuration) const override;` — returns true if we are time slicing and the data is valid to use false otherwise
- L794 _public function_ `int32 GetNumRemaningBuildTasksHelper() const`
- L795 _public prototype_ `virtual int32 GetNumRemaningBuildTasks() const override;`
- L796 _public prototype_ `virtual int32 GetNumRunningBuildTasks() const override;`
- L799 _public prototype_ `bool IsTileChanged(const FNavTileRef InTileRef) const;` — Checks if a given tile is being build or has just finished building
- L801 _public function_ `inline uint32 GetVersion() const`
- L803 _public function_ `const ARecastNavMesh* GetOwner() const`
- L806 _public prototype_ `void OnAreaAdded(const UClass* AreaClass, int32 AreaID);` — update area data
- L807 _public prototype_ `void OnAreaRemoved(const UClass* AreaClass);`
- L810 _public function_ `inline class UWorld* GetWorld() const` — --- accessors --- //
- L812 _public function_ `const FRecastBuildConfig& GetConfig() const`
- L814 _public function_ `const FRecastNavMeshTileGenerationDebug& GetTileDebugSettings() const`
- L816 _public function_ `const TNavStatArray<FBox>& GetInclusionBounds() const`
- L818 _public function_ `FVector GetRcNavMeshOrigin() const`
- L822 _public prototype_ `int32 FindInclusionBoundEncapsulatingBox(const FBox& Box) const;` — checks if any on InclusionBounds encapsulates given box. @return index to first item in InclusionBounds that meets expectations
- L825 _public function_ `FBox GetTotalBounds() const` — Total navigable area box, sum of all navigation volumes bounding boxes
- L827 _public function_ `const FRecastNavMeshCachedData& GetAdditionalCachedData() const`
- L829 _public prototype_ `bool HasDirtyTiles() const;`
- L830 _public prototype_ `bool HasDirtyTiles(const FBox& AreaBounds) const;`
- L831 _public prototype_ `int32 GetDirtyTilesCount(const FBox& AreaBounds) const;`
- L833 _public prototype_ `bool GatherGeometryOnGameThread() const;`
- L834 _public prototype_ `bool IsTimeSliceRegenActive() const;`
- L836 _public prototype_ `FBox GrowBoundingBox(const FBox& BBox, bool bIncludeAgentHeight) const;`
- L839 _public prototype_ `virtual bool ShouldGenerateGeometryForOctreeElement(const FNavigationOctreeElement& Element, const FNavDataConfig& NavDataConfig) const;` — Returns if the provided Octree Element should generate geometry on the provided NavDataConfig. Can be used to extend the logic to decide what geometry is generated on what Navmesh
- L842 _public prototype_ `virtual void ExportNavigationData(const FString& FileName) const override;`
- L843 _public prototype_ `virtual void GrabDebugSnapshot(struct FVisualLogEntry* Snapshot, const FBox& BoundingBox, const FName& CategoryName, ELogVerbosity::Type Verbosity) const override;`
- L848 _public prototype_ `static void GetDebugGeometry(const FNavigationRelevantData& EncodedData, FNavDebugMeshData& DebugMeshData);` — Converts data encoded in EncodedData.CollisionData to FNavDebugMeshData format
- L851 _public function_ `const FNavRegenTimeSliceManager* GetTimeSliceManager() const`
- L853 _public function_ `void SetNextTimeSliceRegenActive(bool bRegenState)`
- L856 _public prototype_ `virtual void SetupTileConfig(const ENavigationDataResolution TileResolution, FRecastBuildConfig& OutConfig) const;` — Update the config according to the resolution
- L861 _protected prototype_ `virtual void Init();` — Performs initial setup of member variables so that generator is ready to do its thing from this point on. Called just after construction by ARecastNavMesh
- L864 _protected prototype_ `virtual void ConfigureBuildProperties(FRecastBuildConfig& OutConfig);` — Used to configure Config. Override to influence build properties
- L867 _protected prototype_ `void UpdateNavigationBounds();` — Updates cached list of navigation bounds
- L870 _protected prototype_ `virtual void SortPendingBuildTiles();` — Sorts pending build tiles by proximity to player, so tiles closer to player will get generated first
- L873 _protected prototype_ `virtual void GetSeedLocations(UWorld& World, TArray<FVector2D>& OutSeedLocations) const;` — Get seed locations used for sorting pending build tiles. Tiles closer to these locations will be prioritized first.
- L876 _protected prototype_ `bool ConstructTiledNavMesh();` — Instantiates dtNavMesh and configures it for tiles generation. Returns false if failed
- L879 _protected prototype_ `void CalcNavMeshProperties(int32& MaxTiles, int32& MaxPolys);` — Determine bit masks for poly address
- L882 _protected prototype_ `virtual void MarkDirtyTiles(const TArray<FNavigationDirtyArea>& DirtyAreas);` — Marks grid tiles affected by specified areas as dirty
- L885 _protected prototype_ `virtual bool ShouldDirtyTilesRequestedByObject( const UNavigationSystemV1& NavSys, const FNavigationOctree& NavOctreeInstance, const UObject& SourceObject, const FNavDataConfig& NavDataConfig) const final;` — `UE_DEPRECATED(5.5, "Use ShouldDirtyTilesRequestedByElement with FNavigationElement instead.")`
- L892 _protected prototype_ `virtual bool ShouldDirtyTilesRequestedByElement( const UNavigationSystemV1& NavSys, const FNavigationOctree& NavOctreeInstance, FNavigationElementHandle SourceElement, const FNavDataConfig& NavDataConfig) const;` — Returns if the provided FNavigationElement that requested a navmesh dirtying should dirty this Navmesh. Useful to avoid tiles regeneration from elements that are excluded from the provided NavDataConfig
- L899 _protected prototype_ `bool MarkNavBoundsDirty();` — Marks all tiles overlapping with InclusionBounds dirty (via MarkDirtyTiles).
- L902 _protected function_ `int32 GetNumActiveTiles() const` — Returns the number of tiles currently populated with navigation data. O(1) — reads the maintained counter directly.
- L904 _protected prototype_ `void RemoveLayers(const FIntPoint& Tile, TArray<FNavTileRef>& UpdatedTiles);`
- L905 _protected prototype_ `void RemoveAllTiles(TArray<FNavTileRef>& UpdatedTiles);`
- L907 _protected prototype_ `void StoreCompressedTileCacheLayers(const FRecastTileGenerator& TileGenerator, int32 TileX, int32 TileY);`
- L910 _protected prototype_ `void StoreDebugData(const FRecastTileGenerator& TileGenerator, int32 TileX, int32 TileY);`
- L915 _protected prototype_ `TArray<FNavTileRef> ProcessTileTasksAsyncAndGetUpdatedTiles(const int32 NumTasksToProcess);` — Processes pending tile generation tasks Async
- L917 _protected prototype_ `TSharedRef<FRecastTileGenerator> CreateTileGeneratorFromPendingElement(FIntPoint &OutTileLocation, const int32 ForcedPendingTileIdx = INDEX_NONE);`
- L920 _protected prototype_ `virtual TArray<FNavTileRef> ProcessTileTasksSyncTimeSlicedAndGetUpdatedTiles();` — Processes pending tile generation tasks Sync with option for time slicing currently an experimental feature.
- L921 _protected prototype_ `TArray<FNavTileRef> ProcessTileTasksSyncAndGetUpdatedTiles(const int32 NumTasksToProcess);`
- L923 _protected prototype_ `virtual int32 GetNextPendingDirtyTileToBuild() const;`
- L926 _protected prototype_ `TArray<FNavTileRef> ProcessTileTasksAndGetUpdatedTiles(const int32 NumTasksToProcess);` — Processes pending tile generation tasks
- L928 _protected prototype_ `void ResetTimeSlicedTileGeneratorSync();`
- L932 _public prototype_ `ETimeSliceWorkResult AddGeneratedTilesTimeSliced(FRecastTileGenerator& TileGenerator, TArray<FNavTileRef>& OutResultTileRefs);` — Adds generated tiles to NavMesh, replacing old ones, uses time slicing returns Failed if any layer failed
- L935 _public prototype_ `TArray<FNavTileRef> AddGeneratedTilesAndGetUpdatedTiles(FRecastTileGenerator& TileGenerator);` — Adds generated tiles to NavMesh, replacing old ones
- L939 _public prototype_ `TArray<FNavTileRef> RemoveTileLayersAndGetUpdatedTiles(const int32 TileX, const int32 TileY, TMap<int32, dtPolyRef>* OldLayerTileIdMap = nullptr);` — Removes all tiles at specified grid location and returns the updated FNavTileRef
- L942 _public prototype_ `void RemoveTileLayers(dtNavMesh* DetourMesh, const int32 TileX, const int32 TileY);` — Removes all tiles at specified grid location
- L944 _public prototype_ `void RemoveTiles(const TArray<FIntPoint>& Tiles);`
- L946 _public prototype_ `void ReAddTiles(const TArray<FNavMeshDirtyTileElement>& Tiles);`
- L948 _public function_ `bool IsBuildingRestrictedToActiveTiles() const`
- L949 _public prototype_ `bool IsInActiveSet(const FIntPoint& Tile) const;`
- L954 _public function_ `void SetMaxTileGeneratorTasks(int32 NewLimit)` — sets a limit to number of asynchronous tile generators running at one time @note if used at runtime will not result in killing tasks above limit count @mote function does not validate the input parameter - it's on caller
- L956 _public function_ `void SetSortPendingTileMethod(const ENavigationSortPendingTilesMethod InMethod)`
- L958 _public prototype_ `static void CalcPolyRefBits(ARecastNavMesh* NavMeshOwner, int32& MaxTileBits, int32& MaxPolyBits);`
- L961 _public prototype_ `bool IsGeneratingLinks() const;` — Returns true if bGenerateNavLinks is enabled and bAllowLinkGeneration is true.
- L966 _protected prototype_ `void ResolveGeneratedLinkAreas(FRecastBuildConfig& OutConfig);` — Resolve area class from link generation config into recast areaIds and flags. Must be called after AdditionalCachedData is constructed.
- L968 _protected prototype_ `virtual void RestrictBuildingToActiveTiles(bool InRestrictBuildingToActiveTiles);`
- L971 _protected prototype_ `void DiscardCurrentBuildingTasks();` — Blocks until build for specified list of tiles is complete and discard results
- L973 _protected prototype_ `virtual TSharedRef<FRecastTileGenerator> CreateTileGenerator(const FIntPoint& Coord, const TArray<FBox>& DirtyAreas, const double PendingTileCreationTime = 0.);`
- L976 _protected function_ `template <typename T> TSharedRef<T> ConstructTileGeneratorImpl(const FIntPoint& Coord, const TArray<FBox>& DirtyAreas, const double PendingTileCreationTime)`
- L983 _protected prototype_ `FBox GrowDirtyBounds(const FBox& BBox, bool bIncludeAgentHeight) const;`
- L988 _protected prototype_ `virtual uint32 LogMemUsed() const override;`
- L990 _protected prototype_ `bool IsAllowedToAddTileLayers(const FIntPoint Tile) const;`
- L991 _protected prototype_ `void AddGeneratedTileLayer(int32 LayerIndex, FRecastTileGenerator& TileGenerator, const TMap<int32, dtPolyRef>& OldLayerTileIdMap, TArray<FNavTileRef>& OutResultTileRefs);`
- L1002 _protected prototype_ `void LogDirtyAreas(const UObject& OwnerNav, const TMap<FPendingTileElement, TArray<FNavigationDirtyAreaPerTileDebugInformation>>& DirtyAreasDebuggingInformation) const;` — Used internally, when LogNavigationDirtyArea is VeryVerbose, to log the number of tiles a dirty area is requesting.
- L1011 _protected member_ `FRecastBuildConfig Config;` — Parameters defining navmesh tiles
- L1016 _protected member_ `FVector BBoxGrowth;` — `UE_DEPRECATED(5.5, "Use BBoxGrowthLow and BBoxGrowthHigh instead.")` — Used to grow generic element bounds to match this generator's properties (most notably Config.borderSize)
- L1020 _protected member_ `FVector BBoxGrowthLow;` — Growth in the negative axis direction. Used to grow generic element bounds to match this generator's properties (most notably Config.borderSize)
- L1024 _protected member_ `FVector BBoxGrowthHigh;` — Growth in the positive axis direction. Used to grow generic element bounds to match this generator's properties (most notably Config.borderSize)
- L1026 _protected member_ `int32 NumActiveTiles;`
- L1031 _protected member_ `int32 MaxTileGeneratorTasks;` — the limit to number of asynchronous tile generators running at one time, this is also used by the sync non time sliced regeneration ProcessTileTasksSync, but not by ProcessTileTasksSyncTimeSliced.
- L1034 _protected member_ `FBox TotalNavBounds;` — Total bounding box that includes all volumes, in unreal units.
- L1037 _protected member_ `TNavStatArray<FBox> InclusionBounds;` — Bounding geometry definition.
- L1040 _protected member_ `ARecastNavMesh* DestNavMesh;` — Navigation mesh that owns this generator
- L1043 _protected member_ `TNavStatArray<FPendingTileElement> PendingDirtyTiles;` — List of dirty tiles that needs to be regenerated
- L1046 _protected member_ `TNavStatArray<TRunningTileElement<FRecastTileGeneratorWrapper>> RunningDirtyTiles;` — List of dirty tiles currently being regenerated
- L1050 _protected member_ `TSet<FNavTileRef> TilesPendingSegmentLinkConnections;` — List of tiles that have been generated but have not completed segment link connections yet
- L1055 _protected member_ `TNavStatArray<FTileTimestamp> RecentlyBuiltTiles;` — List of tiles that were recently regenerated
- L1058 _protected member_ `TSet<FIntPoint> ActiveTileSet;`
- L1061 _protected member_ `FRecastNavMeshCachedData AdditionalCachedData;`
- L1064 _protected member_ `FVector RcNavMeshOrigin;` — Use this if you don't want your tiles to start at (0,0,0)
- L1066 _protected member_ `double RebuildAllStartTime = 0;`
- L1068 _protected member_ `uint32 bInitialized:1;`
- L1070 _protected member_ `uint32 bRestrictBuildingToActiveTiles:1;`
- L1074 _protected member_ `uint32 Version;` — Runtime generator's version, increased every time all tile generators get invalidated like when navmesh size changes
- L1076 _protected member_ `ENavigationSortPendingTilesMethod SortPendingTilesMethod = ENavigationSortPendingTilesMethod::SortWithSeedLocations;`
- L1123 _protected member_ `FSyncTimeSlicedData SyncTimeSlicedData;`

#### struct `FRecastNavMeshGenerator::FNavigationDirtyAreaPerTileDebugInformation`  
`struct FNavigationDirtyAreaPerTileDebugInformation`  
_L995-999_
- desc: Data struct used by 'LogDirtyAreas' that contains all the information regarding the areas that are being dirtied, per dirtied tile.
- L997 _public member_ `FNavigationDirtyArea DirtyArea;`
- L998 _public member_ `bool bTileWasAlreadyAdded = false;`

#### struct `FRecastNavMeshGenerator::FSyncTimeSlicedData`  
`struct FSyncTimeSlicedData`  
_L1079-1121_
- desc: Grouping all the member variables used by the time slicing code together for neatness
- L1081 _public prototype_ `FSyncTimeSlicedData();`
- L1084 _public member_ `double CurrentTileRegenDuration;` — Accumulated time spent processing the tile (in seconds).
- L1088 _public member_ `int64 TileRegenStartFrame = 0;` — Frame when the tile start being processed.
- L1091 _public member_ `int64 TileRegenEndFrame = 0;` — Frame when the tile is done being processed.
- L1097 _public member_ `bool bTimeSliceRegenActive;` — if we are currently using time sliced regen or not - currently an experimental feature. do not manipulate this value directly instead call SetNextTimeSliceRegenActive()
- L1098 _public member_ `bool bNextTimeSliceRegenActive;`
- L1101 _public member_ `EProcessTileTasksSyncTimeSlicedState ProcessTileTasksSyncState;` — Used by ProcessTileTasksSyncTimeSliced
- L1104 _public member_ `TArray<FNavTileRef> UpdatedTilesCache;` — Used by ProcessTileTasksSyncTimeSliced
- L1107 _public member_ `TArray<FNavTileRef> ResultTileRefsCached;` — Used by AddGeneratedTilesTimeSliced
- L1110 _public member_ `TMap<int32, dtPolyRef> OldLayerTileIdMapCached;` — Used by AddGeneratedTilesTimeSliced
- L1113 _public member_ `EAddGeneratedTilesTimeSlicedState AddGeneratedTilesState;` — Used by AddGeneratedTilesTimeSliced
- L1116 _public member_ `int32 AddGenTilesLayerIndex;` — Used by AddGeneratedTilesTimeSliced
- L1119 _public member_ `TSharedPtr<FRecastTileGenerator> TileGeneratorSync;` — Do not null or Reset this directly instead call ResetTimeSlicedTileGeneratorSync(). The only exception currently is in ProcessTileTasksSyncTimeSliced
- L1120 _public member_ `FNavRegenTimeSliceManager* TimeSliceManager;`

#### Free symbols / members of external scopes

- L47 _macro_ `#define MAX_VERTS_PER_POLY 6`
- L241 _function_ `` (scope `FRcTileBox::FRcTileBox`)
- L363 _typedef_ `typedef TArray<FGeneratedNavigationLink, TInlineAllocator<64>> TInlineGeneratedNavLinkArray;`
- L639 _typedef_ `typedef FAsyncTask<FRecastTileGeneratorWrapper> FRecastTileGeneratorTask;`
- L697 _function_ `friend uint32 GetTypeHash(const FPendingTileElement& Element)`
- L733 _typedef_ `typedef TRunningTileElement<FRecastTileGeneratorWrapper> FRunningTileElement;` — `UE_DEPRECATED(5.5, "FRunningTileElement is deprecated. Please use TRunningTileElement<FRecastTileGeneratorWrapper> instead.")`

### `Source/Runtime/NavigationSystem/Public/NavMesh/RecastQueryFilter.h` (Public)


#### class `FRecastQueryFilter`  
`class FRecastQueryFilter : public INavigationQueryFilterInterface, public dtQueryFilter`  
_L16-53_
- inherits: `INavigationQueryFilterInterface,dtQueryFilter`
- L19 _public prototype_ `FRecastQueryFilter(bool bIsVirtual = true);`
- L20 _public prototype_ `virtual ~FRecastQueryFilter()= default;`
- L22 _public prototype_ `virtual void Reset() override;`
- L24 _public prototype_ `virtual void SetAreaCost(uint8 AreaType, float Cost) override;`
- L25 _public prototype_ `virtual void SetFixedAreaEnteringCost(uint8 AreaType, float Cost) override;`
- L26 _public prototype_ `virtual void SetExcludedArea(uint8 AreaType) override;`
- L27 _public prototype_ `virtual void SetAllAreaCosts(const float* CostArray, const int32 Count) override;`
- L28 _public prototype_ `virtual void GetAllAreaCosts(float* CostArray, float* FixedCostArray, const int32 Count) const override;`
- L29 _public prototype_ `virtual void SetBacktrackingEnabled(const bool bBacktracking) override;`
- L30 _public prototype_ `virtual bool IsBacktrackingEnabled() const override;`
- L31 _public prototype_ `virtual float GetHeuristicScale() const override;`
- L32 _public prototype_ `virtual bool IsEqual(const INavigationQueryFilterInterface* Other) const override;`
- L33 _public prototype_ `virtual void SetIncludeFlags(uint16 Flags) override;`
- L34 _public prototype_ `virtual uint16 GetIncludeFlags() const override;`
- L35 _public prototype_ `virtual void SetExcludeFlags(uint16 Flags) override;`
- L36 _public prototype_ `virtual uint16 GetExcludeFlags() const override;`
- L37 _public function_ `virtual FVector GetAdjustedEndLocation(const FVector& EndLocation) const override`
- L38 _public prototype_ `virtual INavigationQueryFilterInterface* CreateCopy() const override;`
- L40 _public function_ `const dtQueryFilter* GetAsDetourQueryFilter() const`
- L44 _public prototype_ `void SetIsVirtual(bool bIsVirtual);` — Changes whether the filter will use virtual set of filtering functions (getVirtualCost and passVirtualFilter) or the inlined ones (getInlineCost and passInlineFilter)
- L47 _public prototype_ `void SetShouldIgnoreClosedNodes(const bool bIgnoreClosed);` — Instruct filter whether it can reopen nodes already on closed list

#### struct `FRecastSpeciaLinkFilter`  
`struct FRecastSpeciaLinkFilter : public dtQuerySpecialLinkFilter`  
_L55-64_
- inherits: `dtQuerySpecialLinkFilter`
- L57 _public function_ `FRecastSpeciaLinkFilter(UNavigationSystemV1* NavSystem, const UObject* Owner) : NavSys(NavSystem), SearchOwner(Owner), CachedOwnerOb(nullptr)`
- L58 _public prototype_ `virtual bool isLinkAllowed(const uint64 UserId) const override;`
- L59 _public prototype_ `virtual void initialize() override;`
- L61 _public member_ `UNavigationSystemV1* NavSys;`
- L62 _public member_ `FWeakObjectPtr SearchOwner;`
- L63 _public member_ `UObject* CachedOwnerOb;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define RECAST_VERY_SMALL_AGENT_RADIUS 0.0f`

### `Source/Runtime/NavigationSystem/Public/NavMesh/RecastVersion.h` (Public)


#### Free symbols / members of external scopes

- L10 _macro_ `#define NAVMESHVER_INITIAL 1`
- L11 _macro_ `#define NAVMESHVER_TILED_GENERATION 2`
- L12 _macro_ `#define NAVMESHVER_SEAMLESS_REBUILDING_1 3`
- L13 _macro_ `#define NAVMESHVER_AREA_CLASSES 4`
- L14 _macro_ `#define NAVMESHVER_CLUSTER_PATH 5`
- L15 _macro_ `#define NAVMESHVER_SEGMENT_LINKS 6`
- L16 _macro_ `#define NAVMESHVER_DYNAMIC_LINKS 7`
- L17 _macro_ `#define NAVMESHVER_64BIT 9`
- L18 _macro_ `#define NAVMESHVER_CLUSTER_SIMPLIFIED 10`
- L19 _macro_ `#define NAVMESHVER_OFFMESH_HEIGHT_BUG 11`
- L20 _macro_ `#define NAVMESHVER_LANDSCAPE_HEIGHT 13`
- L21 _macro_ `#define NAVMESHVER_LWCOORDS 14`
- L22 _macro_ `#define NAVMESHVER_OODLE_COMPRESSION 15`
- L23 _macro_ `#define NAVMESHVER_LWCOORDS_SEREALIZATION 17 // Allows for nav meshes to be serialized agnostic of LWCoords being float or double.`
- L24 _macro_ `#define NAVMESHVER_MAXTILES_COUNT_CHANGE 19`
- L25 _macro_ `#define NAVMESHVER_LWCOORDS_OPTIMIZATION 20`
- L26 _macro_ `#define NAVMESHVER_OPTIM_FIX_SERIALIZE_PARAMS 21 // Fix, serialize params that used to be in the tile and are now in the navmesh.`
- L27 _macro_ `#define NAVMESHVER_MAXTILES_COUNT_SKIP_INCLUSION 22`
- L28 _macro_ `#define NAVMESHVER_TILE_RESOLUTIONS 23 // Addition of a tile resolution index to the tile header.`
- L29 _macro_ `#define NAVMESHVER_TILE_RESOLUTIONS_CELLHEIGHT 24 // Addition of CellHeight in the resolution params, deprecating the original CellHeight.`
- L30 _macro_ `#define NAVMESHVER_1_VOXEL_AGENT_STEEP_SLOPE_FILTER_FIX 25 // Fix, remove steep slope filtering during heightfield ledge filtering when the agent radius is included into a single voxel`
- L31 _macro_ `#define NAVMESHVER_TILE_RESOLUTIONS_AGENTMAXSTEPHEIGHT 26 // Addition of AgentMaxStepHeight in the resolution params, deprecating the original AgentMaxStepHeight.`
- L32 _macro_ `#define NAVMESHVER_NAVLINK_JUMP_CONFIGS 27 // Addition of NavLinkJumpConfigs, deprecating the original NavLinkJumpDownConfig`
- L33 _macro_ `#define NAVMESHVER_TILEVERT_ENCODING 28 // Store vertex data as tile-local floats (dtTileVert) instead of world-space doubles`
- L35 _macro_ `#define NAVMESHVER_LATEST NAVMESHVER_TILEVERT_ENCODING`
- L36 _macro_ `#define NAVMESHVER_MIN_COMPATIBLE NAVMESHVER_LWCOORDS_OPTIMIZATION`

### `Source/Runtime/NavigationSystem/Public/NavModifierComponent.h` (Public)


#### class `UNavModifierComponent`  
`class UNavModifierComponent : public UNavRelevantComponent`  
_L16-87_
- reflection: `UCLASS(ClassGroup = (Navigation), meta = (BlueprintSpawnableComponent), hidecategories = (Activation), config = Engine, defaultconfig, MinimalAPI)`
- inherits: `UNavRelevantComponent`
- L22 _private member_ `TSubclassOf<UNavArea> AreaClass;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Navigation)` — NavArea to apply inside the defined volume.
- L26 _private member_ `TSubclassOf<UNavArea> AreaClassToReplace;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Navigation)` — When setting this value, the modifier behavior changes : it will now replace any surface marked by AreaClassToReplace in the volume and replace it with AreaClass.
- L30 _private member_ `FVector FailsafeExtent;` — `UPROPERTY(EditAnywhere, Category = Navigation)` — box extent used ONLY when owning actor doesn't have collision component
- L34 _private member_ `ENavigationDataResolution NavMeshResolution;` — `UPROPERTY(EditAnywhere, Category = Navigation, AdvancedDisplay)` — Experimental: Indicates which navmesh resolution should be used around the actor.
- L39 _private member_ `uint8 bIncludeAgentHeight : 1;` — `UPROPERTY(config, EditAnywhere, Category = Navigation)` — Setting to 'true' will result in expanding lower bounding box of the nav modifier by agent's height, before applying to navmesh
- L43 _private prototype_ `virtual void CalculateBounds() const;` — Does the actual calculating and caching of the bounds when called by CalcAndCacheBounds
- L45 _private prototype_ `virtual void CalcAndCacheBounds() const override;` — @Note We might make this function non-virtual in the future in favor of child classes overriding CalculateBounds, see #jira UE-202451
- L46 _private prototype_ `virtual void GetNavigationData(FNavigationRelevantData& Data) const override;`
- L49 _private prototype_ `void SetAreaClass(TSubclassOf<UNavArea> NewAreaClass);` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation")`
- L51 _private prototype_ `void SetAreaClassToReplace(TSubclassOf<UNavArea> NewAreaClassToReplace);` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation")`
- L54 _protected prototype_ `void OnTransformUpdated(USceneComponent* RootComponent, EUpdateTransformFlags UpdateTransformFlags, ETeleportType Teleport);`
- L57 _protected prototype_ `void OnNavAreaRegistered(const UWorld& World, const UClass* NavAreaClass);`
- L58 _protected prototype_ `void OnNavAreaUnregistered(const UWorld& World, const UClass* NavAreaClass);`
- L62 _protected prototype_ `virtual void OnRegister() override;`
- L63 _protected prototype_ `virtual void OnUnregister() override;`
- L66 _protected prototype_ `void PopulateComponentBounds(FTransform InParentTransform, const UBodySetup& InBodySetup) const;`
- L77 _protected member_ `mutable TArray<FRotatedBox> ComponentBounds;`
- L78 _protected member_ `mutable FDelegateHandle TransformUpdateHandle;`
- L81 _protected member_ `mutable FTransform CachedTransform;` — cached in CalcAndCacheBounds and tested in GetNavigationData to see if cached data is still valid
- L84 _protected member_ `FDelegateHandle OnNavAreaRegisteredDelegateHandle;`
- L85 _protected member_ `FDelegateHandle OnNavAreaUnregisteredDelegateHandle;`

#### struct `UNavModifierComponent::FRotatedBox`  
`struct FRotatedBox`  
_L68-75_
- L70 _public member_ `FBox Box;`
- L71 _public member_ `FQuat Quat;`
- L73 _public function_ `FRotatedBox()`
- L74 _public function_ `FRotatedBox(const FBox& InBox, const FQuat& InQuat) : Box(InBox), Quat(InQuat)`

### `Source/Runtime/NavigationSystem/Public/NavModifierVolume.h` (Public)


#### class `ANavModifierVolume`  
`class ANavModifierVolume : public AVolume, public INavRelevantInterface`  
_L21-80_
- reflection: `UCLASS(hidecategories=(Navigation), MinimalAPI)`
- inherits: `AVolume,INavRelevantInterface`
- desc: Allows applying selected AreaClass to navmesh, using Volume's shape
- L28 _protected member_ `TSubclassOf<UNavArea> AreaClass;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Default)` — NavArea to apply inside the defined volume.
- L32 _protected member_ `TSubclassOf<UNavArea> AreaClassToReplace;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Default)` — When setting this value, the modifier volume behavior changes : it will now replace any surface marked by AreaClassToReplace in the volume and replace it with AreaClass.
- L36 _protected member_ `bool bMaskFillCollisionUnderneathForNavmesh;` — `UPROPERTY(EditAnywhere, Category = Default, AdvancedDisplay)` — Experimental: if set, the 2D space occupied by the volume box will ignore FillCollisionUnderneathForNavmesh
- L41 _protected member_ `ENavigationDataResolution NavMeshResolution;` — `UPROPERTY(EditAnywhere, Category = Default, AdvancedDisplay)` — Experimental: When not set to None, the navmesh tiles touched by the navigation modifier volume will be built using the highest resolution found.
- L44 _protected member_ `FDelegateHandle OnNavAreaRegisteredDelegateHandle;`
- L45 _protected member_ `FDelegateHandle OnNavAreaUnregisteredDelegateHandle;`
- L49 _public prototype_ `ANavModifierVolume(const FObjectInitializer& ObjectInitializer);`
- L52 _public prototype_ `void SetAreaClass(TSubclassOf<UNavArea> NewAreaClass = {});` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation")`
- L54 _public prototype_ `void SetAreaClassToReplace(TSubclassOf<UNavArea> NewAreaClassToReplace = {});` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation")`
- L56 _public function_ `TSubclassOf<UNavArea> GetAreaClass() const`
- L57 _public function_ `TSubclassOf<UNavArea> GetAreaClassToReplace() const`
- L59 _public prototype_ `virtual void GetNavigationData(FNavigationRelevantData& Data) const override;`
- L60 _public prototype_ `virtual FBox GetNavigationBounds() const override;`
- L61 _public prototype_ `virtual void RebuildNavigationData() override;`
- L64 _public prototype_ `virtual void PostEditUndo() override;`
- L65 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L69 _protected prototype_ `virtual void PostLoad() override;`
- L70 _protected prototype_ `virtual void PostInitProperties() override;`
- L71 _protected prototype_ `virtual void BeginDestroy() override;`
- L74 _protected prototype_ `virtual void PostRegisterAllComponents() override;`
- L75 _protected prototype_ `virtual void PostUnregisterAllComponents() override;`
- L77 _protected prototype_ `void OnNavAreaRegistered(const UWorld& World, const UClass* NavAreaClass);`
- L78 _protected prototype_ `void OnNavAreaUnregistered(const UWorld& World, const UClass* NavAreaClass);`

### `Source/Runtime/NavigationSystem/Public/NavNodeInterface.h` (Public)


#### class `UNavNodeInterface`  
`class UNavNodeInterface : public UInterface`  
_L10-13_
- reflection: `UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `INavNodeInterface`  
`class INavNodeInterface`  
_L15-25_
- L23 _private prototype_ `virtual class UNavigationGraphNodeComponent* GetNavNodeComponent() PURE_VIRTUAL(FNavAgentProperties::GetNavNodeComponent,return NULL;);` — Retrieves pointer to implementation's UNavigationGraphNodeComponent

### `Source/Runtime/NavigationSystem/Public/NavRelevantComponent.h` (Public)


#### class `UNavRelevantComponent`  
`class UNavRelevantComponent : public UActorComponent, public INavRelevantInterface`  
_L11-52_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UActorComponent,INavRelevantInterface`
- L16 _private prototype_ `virtual void OnRegister() override;`
- L17 _private prototype_ `virtual void OnUnregister() override;`
- L21 _private prototype_ `virtual FBox GetNavigationBounds() const override;`
- L22 _private prototype_ `virtual bool IsNavigationRelevant() const override;`
- L23 _private prototype_ `virtual void UpdateNavigationBounds() override;`
- L24 _private prototype_ `virtual UObject* GetNavigationParent() const override;`
- L27 _private prototype_ `virtual void CalcAndCacheBounds() const;`
- L30 _private prototype_ `void SetNavigationRelevancy(bool bRelevant);` — `UFUNCTION(BlueprintCallable, Category="AI|Navigation")`
- L33 _private prototype_ `void ForceNavigationRelevancy(bool bForce);` — force relevancy and skip attaching navigation data to owner's root entry
- L36 _private prototype_ `void RefreshNavigationModifiers();` — force refresh in navigation octree
- L41 _protected member_ `mutable FBox Bounds;` — bounds for navigation octree
- L45 _protected member_ `uint32 bAttachToOwnersRoot : 1;` — `UPROPERTY()` — attach navigation data to entry for owner's root component (depends on its relevancy)
- L47 _protected member_ `mutable uint32 bBoundsInitialized : 1;`
- L48 _protected member_ `uint32 bNavParentCacheInitialized : 1;`
- L51 _protected member_ `TObjectPtr<UObject> CachedNavParent;` — `UPROPERTY(transient)`

### `Source/Runtime/NavigationSystem/Public/NavSystemConfigOverride.h` (Public)


#### enum `ENavSystemOverridePolicy`  
`enum class ENavSystemOverridePolicy : uint8`  
_L14-19_
- reflection: `UENUM()`
- L16 _public enumerator_ `Override` — the pre-existing nav system instance will be destroyed.
- L17 _public enumerator_ `Append` — config information will be added to pre-existing nav system instance
- L18 _public enumerator_ `Skip` — if there's already a NavigationSystem in the world then the overriding config will be ignored

#### class `ANavSystemConfigOverride`  
`class ANavSystemConfigOverride : public AActor`  
_L23-84_
- reflection: `UCLASS(hidecategories = (Input, Rendering, Actor, LOD, Cooking), MinimalAPI)`
- inherits: `AActor`
- L30 _private member_ `TObjectPtr<class UBillboardComponent> SpriteComponent;` — `UPROPERTY()`
- L35 _protected member_ `TObjectPtr<UNavigationSystemConfig> NavigationSystemConfig;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Navigation, Instanced, meta = (NoResetToDefault))`
- L39 _protected member_ `ENavSystemOverridePolicy OverridePolicy;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Navigation)` — If there's already a NavigationSystem instance in the world how should this nav override behave
- L42 _protected member_ `uint8 bLoadOnClient : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Navigation, AdvancedDisplay)`
- L45 _public prototype_ `ANavSystemConfigOverride(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L48 _public prototype_ `virtual void PostInitProperties() override;`
- L50 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L55 _public prototype_ `virtual void BeginPlay() override;`
- L57 _public prototype_ `virtual void PostRegisterAllComponents() override;`
- L58 _public prototype_ `virtual void PostUnregisterAllComponents() override;`
- L65 _public prototype_ `void ApplyChanges();` — `UFUNCTION(Category = Navigation, meta = (CallInEditor = "true"))` — made an explicit function since rebuilding navigation system can be expensive
- L72 _protected prototype_ `virtual void OverrideNavSystem();` — Creates a new navigation system and plugs it into the world. If there's a nav system instance already in place it gets destroyed.
- L76 _protected prototype_ `virtual void AppendToNavSystem(UNavigationSystemBase& PrevNavSys);` — Appends non-conflicting information (like supported agents) to a pre-existing nav system instance
- L80 _protected prototype_ `void InitializeForWorld(UNavigationSystemBase* NewNavSys, UWorld* World, const FNavigationSystemRunMode RunMode);` — Called only in the editor mode
- L83 _protected prototype_ `void ApplyConfig();`

### `Source/Runtime/NavigationSystem/Public/NavigationData.h` (Public)


#### struct `FSupportedAreaData`  
`struct FSupportedAreaData`  
_L29-43_
- reflection: `USTRUCT()`
- L34 _public member_ `FString AreaClassName;` — `UPROPERTY(VisibleAnywhere, Category=Areas)`
- L37 _public member_ `int32 AreaID;` — `UPROPERTY(VisibleAnywhere, Category=Areas)`
- L40 _public member_ `TObjectPtr<const UClass> AreaClass;` — `UPROPERTY(transient)`
- L42 _public prototype_ `FSupportedAreaData(TSubclassOf<UNavArea> NavAreaClass = {}, int32 InAreaID = INDEX_NONE);`

#### struct `FNavPathRecalculationRequest`  
`struct FNavPathRecalculationRequest`  
_L45-55_
- L47 _public member_ `FNavPathWeakPtr Path;`
- L48 _public member_ `ENavPathUpdateType::Type Reason;`
- L50 _public function_ `FNavPathRecalculationRequest(const FNavPathSharedPtr& InPath, ENavPathUpdateType::Type InReason) : Path(InPath.ToSharedRef()), Reason(InReason)`
- L54 _public function_ `bool operator==(const FNavPathRecalculationRequest& Other) const`

#### struct `FPathFindingResult`  
`struct FPathFindingResult`  
_L57-70_
- L59 _public member_ `FNavPathSharedPtr Path;`
- L60 _public member_ `ENavigationQueryResult::Type Result;`
- L62 _public function_ `FPathFindingResult(ENavigationQueryResult::Type InResult = ENavigationQueryResult::Invalid) : Result(InResult)`
- L65 _public function_ `inline bool IsSuccessful() const`
- L69 _public prototype_ `inline bool IsPartial() const;`
- L1176 _function_ `inline bool FPathFindingResult::IsPartial() const`

#### struct `FNavigationRaycastAdditionalResults`  
`struct FNavigationRaycastAdditionalResults`  
_L72-78_
- L77 _public member_ `bool bIsRayEndInCorridor = false;` — When the ray is not obstructed, indicates if the projection of RayEnd is located at the end of the explored corridor. When bIsRaytEndInCorridor is false, it means that RayEnd failed to project to the NavigationData or on a navigation node that is not part of the explored corridor (e.g. different height)

#### struct `FNavigationPath`  
`struct FNavigationPath : public TSharedFromThis<FNavigationPath, ESPMode::ThreadSafe>`  
_L80-517_
- inherits: `TSharedFromThis<FNavigationPath,ESPMode::ThreadSafe>`
- L83 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FPathObserverDelegate, FNavigationPath*, ENavPathEvent::Type);` — DECLARE_DELEGATE_OneParam(FPathObserverDelegate, FNavigationPath*);
- L85 _public prototype_ `FNavigationPath();`
- L86 _public prototype_ `FNavigationPath(const TArray<FVector>& Points, AActor* Base = NULL);`
- L87 _public prototype_ `virtual ~FNavigationPath();`
- L90 _public prototype_ `FNavigationPath(const FNavigationPath&) = default;`
- L91 _public prototype_ `FNavigationPath& operator=(const FNavigationPath& Other) = default;`
- L94 _public function_ `inline bool IsValid() const`
- L98 _public function_ `inline bool IsUpToDate() const`
- L102 _public function_ `inline bool IsReady() const`
- L106 _public function_ `inline bool IsPartial() const`
- L110 _public function_ `inline bool DidSearchReachedLimit() const`
- L117 _public function_ `bool IsErrorStartLocationNonNavigable() const` — True when the path request failed because the start location couldn't be projected on the NavData. False doesn't guarantee that the location is navigable, it's also possible a previous error skipped the projection altogether
- L124 _public function_ `bool IsErrorEndLocationNonNavigable() const` — True when the path request failed because the end location couldn't be projected on the NavData. False doesn't guarantee that the location is navigable, it's also possible a previous error skipped the projection altogether
- L128 _public function_ `inline bool IsWaitingForRepath() const`
- L132 _public function_ `inline void SetManualRepathWaiting(const bool bInWaitingForRepath)`
- L136 _public function_ `inline bool ShouldUpdateStartPointOnRepath() const`
- L140 _public function_ `inline bool ShouldUpdateEndPointOnRepath() const`
- L144 _public function_ `inline FVector GetDestinationLocation() const`
- L148 _public function_ `inline FPathObserverDelegate& GetObserver()`
- L152 _public function_ `inline FDelegateHandle AddObserver(FPathObserverDelegate::FDelegate NewObserver)`
- L156 _public function_ `inline void RemoveObserver(FDelegateHandle HandleOfObserverToRemove)`
- L161 _public function_ `inline void MarkReady()`
- L166 _public prototype_ `inline void SetNavigationDataUsed(const ANavigationData* const NewData);`
- L168 _public function_ `inline ANavigationData* GetNavigationDataUsed() const`
- L172 _public function_ `inline void SetQuerier(const UObject* InQuerier)`
- L176 _public function_ `inline const UObject* GetQuerier() const`
- L180 _public function_ `inline void SetQueryData(const FPathFindingQueryData& QueryData)`
- L184 _public function_ `inline FPathFindingQueryData GetQueryData() const`
- L191 _public function_ `inline void SetIsPartial(const bool bPartial)` — FORCEINLINE void SetObserver(const FPathObserverDelegate& Observer) { ObserverDelegate = Observer; }
- L195 _public function_ `inline void SetSearchReachedLimit(const bool bLimited)`
- L199 _public function_ `void SetErrorStartLocationNonNavigable(const bool bErrorNonNavigable)`
- L203 _public function_ `void SetErrorEndLocationNonNavigable(const bool bErrorNonNavigable)`
- L207 _public function_ `inline void SetFilter(FSharedConstNavQueryFilter InFilter)`
- L212 _public function_ `inline FSharedConstNavQueryFilter GetFilter() const`
- L216 _public function_ `inline AActor* GetBaseActor() const`
- L221 _public function_ `FVector GetStartLocation() const`
- L225 _public function_ `FVector GetEndLocation() const`
- L230 _public function_ `inline void DoneUpdating(ENavPathUpdateType::Type UpdateType)`
- L251 _public function_ `inline double GetTimeStamp() const`
- L252 _public function_ `inline void SetTimeStamp(double TimeStamp)`
- L254 _public prototype_ `void Invalidate();`
- L255 _public prototype_ `void RePathFailed();`
- L259 _public prototype_ `virtual void ResetForRepath();` — Resets all variables describing generated path before attempting new pathfinding call. This function will NOT reset setup variables like goal actor, filter, observer, etc
- L262 _public prototype_ `void RemoveOverlappingPoints(const FVector& Tolerance);` — Remove points that are at the same location.
- L264 _public prototype_ `virtual void DebugDraw(const ANavigationData* NavData, const FColor PathColor, class UCanvas* Canvas, const bool bPersistent, const float LifeTime, const uint32 NextPathPointIndex = 0) const;`
- L267 _public prototype_ `virtual void DescribeSelfToVisLog(struct FVisualLogEntry* Snapshot) const;`
- L268 _public prototype_ `virtual FString GetDescription() const;`
- L273 _public function_ `virtual bool ContainsCustomLink(uint32 UniqueLinkId) const final` — `UE_DEPRECATED(5.3, "Use version that takes FNavLinkId instead. This function only returns false.")` — check if path contains specific custom nav link
- L275 _public prototype_ `virtual bool ContainsCustomLink(FNavLinkId UniqueLinkId) const;`
- L278 _public prototype_ `virtual bool ContainsAnyCustomLink() const;` — check if path contains any custom nav link
- L281 _public prototype_ `virtual bool ContainsNode(NavNodeRef NodeRef) const;` — check if path contains given node
- L284 _public function_ `virtual FVector::FReal GetCostFromIndex(int32 PathPointIndex) const` — get cost of path, starting from given point
- L290 _public function_ `virtual FVector::FReal GetCostFromNode(NavNodeRef PathNode) const` — get cost of path, starting from given node
- L295 _public function_ `inline FVector::FReal GetCost() const`
- L301 _public prototype_ `virtual FVector::FReal GetLengthFromPosition(FVector SegmentStart, uint32 NextPathPointIndex) const;` — calculates total length of segments from NextPathPoint to the end of path, plus distance from CurrentPosition to NextPathPoint
- L303 _public function_ `inline FVector::FReal GetLength() const`
- L308 _public function_ `static bool GetPathPoint(const FNavigationPath* Path, uint32 PathVertIdx, FNavPathPoint& PathPoint)`
- L319 _public function_ `inline const TArray<FNavPathPoint>& GetPathPoints() const`
- L323 _public function_ `inline TArray<FNavPathPoint>& GetPathPoints()`
- L329 _public prototype_ `FBasedPosition GetPathPointLocation(uint32 Index) const;` — get based position of path point
- L332 _public prototype_ `virtual bool DoesIntersectBox(const FBox& Box, uint32 StartingIndex = 0, int32* IntersectingSegmentIndex = NULL, FVector* AgentExtent = NULL) const;` — checks if given path, starting from StartingIndex, intersects with given AABB box
- L335 _public prototype_ `virtual bool DoesIntersectBox(const FBox& Box, const FVector& AgentLocation, uint32 StartingIndex = 0, int32* IntersectingSegmentIndex = NULL, FVector* AgentExtent = NULL) const;` — checks if given path, starting from StartingIndex, intersects with given AABB box. This version uses AgentLocation as beginning of the path with segment between AgentLocation and path's StartingIndex-th node treated as first path segment to check
- L339 _public prototype_ `virtual FVector GetSegmentDirection(uint32 SegmentEndIndex) const;` — retrieves normalized direction vector to given path segment for '0'-th segment returns same as for 1st segment
- L342 _private prototype_ `bool DoesPathIntersectBoxImplementation(const FBox& Box, const FVector& StartLocation, uint32 StartingIndex, int32* IntersectingSegmentIndex, FVector* AgentExtent) const;`
- L345 _private prototype_ `void InternalResetNavigationPath();` — reset variables describing built path, leaves setup variables required for rebuilding
- L351 _public function_ `template<typename PathClass> inline const PathClass* CastPath() const` — type safe casts
- L357 _public function_ `template<typename PathClass> inline PathClass* CastPath()`
- L363 _public prototype_ `void SetGoalActorObservation(const AActor& ActorToObserve, float TetherDistance);` — enables path observing specified AActor's location and update itself if actor changes location
- L365 _public function_ `void SetGoalActorTetherDistance(const float NewTetherDistace)` — Modifies distance to the GoalActor at which we'll update the path
- L367 _public prototype_ `void DisableGoalActorObservation();` — turns goal actor location's observation
- L369 _public prototype_ `void SetSourceActor(const AActor& InSourceActor);` — set's up the path to use SourceActor's location in case of recalculation
- L371 _public function_ `const AActor* GetSourceActor() const`
- L372 _public function_ `const INavAgentInterface* GetSourceActorAsNavAgent() const`
- L374 _public function_ `FVector GetLastRepathGoalLocation() const`
- L375 _public prototype_ `void UpdateLastRepathGoalLocation();`
- L377 _public function_ `double GetLastUpdateTime() const`
- L378 _public function_ `float GetGoalActorTetherDistance() const`
- L381 _public function_ `void EnableRecalculationOnInvalidation(bool bShouldAutoUpdate)` — if enabled path will request recalculation if it gets invalidated due to a change to underlying navigation
- L385 _public function_ `bool WillRecalculateOnInvalidation() const`
- L391 _public function_ `void SetIgnoreInvalidation(bool bShouldIgnore)` — if ignoring, path will stay bUpToDate after being invalidated due to a change to underlying navigation (observer and auto repath will NOT be triggered!)
- L392 _public function_ `bool GetIgnoreInvalidation() const`
- L394 _public prototype_ `EPathObservationResult::Type TickPathObservation();`
- L397 _public prototype_ `FVector GetGoalLocation() const;` — If GoalActor is set it retrieved its navigation location, if not retrieved last path point location
- L400 _public prototype_ `FVector GetPathFindingStartLocation() const;` — retrieved location to start path finding from (in case of path recalculation)
- L402 _public function_ `const AActor* GetGoalActor() const`
- L406 _public function_ `const INavAgentInterface* GetGoalActorAsNavAgent() const`
- L413 _public member_ `TArray<NavNodeRef> ShortcutNodeRefs;` — additional node refs used during path following shortcuts
- L418 _protected function_ `virtual void OnPathUpdated(ENavPathUpdateType::Type UpdateType)` — optional notify called when path finishes update, before broadcasting to observes - requires bUseOnPathUpdatedNotify flag set
- L424 _protected member_ `TArray<FNavPathPoint> PathPoints;` — IMPORTANT: path is assumed to be valid if it contains _MORE_ than _ONE_ point point 0 is path's starting point - if it's the only point on the path then there's no path per se
- L427 _protected member_ `TWeakObjectPtr<AActor> Base;` — base actor, if exist path points locations will be relative to it
- L433 _private member_ `TWeakObjectPtr<const AActor> GoalActor;` — if set path will observe GoalActor's location and update itself if goal moves more then @note only actual navigation paths can use this feature, meaning the ones associated with a NavigationData instance (meaning NavigationDataUsed != NULL)
- L436 _private member_ `const INavAgentInterface* GoalActorAsNavAgent;` — cached result of GoalActor casting to INavAgentInterface
- L439 _private member_ `TWeakObjectPtr<const AActor> SourceActor;` — if set will be queried for location in case of path's recalculation
- L442 _private member_ `const INavAgentInterface* SourceActorAsNavAgent;` — cached result of PathSource casting to INavAgentInterface
- L446 _protected member_ `FSharedConstNavQueryFilter Filter;` — DEPRECATED: filter used to build this path
- L449 _protected member_ `static const FNavPathType Type;` — type of path
- L451 _protected member_ `FNavPathType PathType;`
- L454 _protected member_ `FPathObserverDelegate ObserverDelegate;` — A delegate that will be called when path becomes invalid
- L457 _protected member_ `uint32 bUpToDate : 1;` — "true" until navigation data used to generate this path has been changed/invalidated
- L460 _protected member_ `uint32 bIsReady : 1;` — when false it means path instance has been created, but not filled with data yet
- L463 _protected member_ `uint32 bIsPartial : 1;` — "true" when path is only partially generated, when goal is unreachable and path represent best guess
- L468 _protected member_ `uint32 bReachedSearchLimit : 1;` — set to true when path finding algorithm reached a technical limit (like limit of A* nodes). This generally means path cannot be trusted to lead to requested destination although it might lead closer to destination.
- L471 _protected member_ `uint32 bErrorStartLocationNonNavigable : 1 = false;` — "true" when the start location could not be projected on the navigation data
- L474 _protected member_ `uint32 bErrorEndLocationNonNavigable : 1 = false;` — "true" when the end location could not be projected on the navigation data
- L477 _protected member_ `uint32 bDoAutoUpdateOnInvalidation : 1;` — if true path will request re-pathing if it gets invalidated due to underlying navigation changed
- L483 _protected member_ `uint32 bIgnoreInvalidation : 1;` — if true path will keep bUpToDate value after getting invalidated due to underlying navigation changed (observer and auto repath will NOT be triggered!) it's NOT safe to use if path relies on navigation data references (e.g. poly corridor)
- L486 _protected member_ `uint32 bUpdateStartPointOnRepath : 1;` — if true path will use GetPathFindingStartLocation() for updating QueryData before repath
- L489 _protected member_ `uint32 bUpdateEndPointOnRepath : 1;` — if true path will use GetGoalLocation() for updating QueryData before repath
- L492 _protected member_ `uint32 bWaitingForRepath : 1;` — set when path is waiting for recalc from navigation data
- L495 _protected member_ `uint32 bUseOnPathUpdatedNotify : 1;` — if true path will call OnPathUpdated notify
- L499 _protected member_ `uint32 bObservingGoalActor : 1;` — indicates whether at any point GoalActor was a valid Actor. Used as an optimization in FNavigationPath::TickPathObservation
- L502 _protected member_ `TWeakObjectPtr<ANavigationData> NavigationDataUsed;` — navigation data used to generate this path
- L505 _protected member_ `FPathFindingQueryData PathFindingQueryData;` — essential part of query used to generate this path
- L508 _protected member_ `double LastUpdateTimeStamp;` — gets set during path creation and on subsequent path's updates
- L513 _private member_ `float GoalActorLocationTetherDistanceSq;` — if GoalActor is set this is the distance we'll try to keep GoalActor from end of path. If GoalActor moves more then this from the end of the path we'll recalculate the path
- L516 _private member_ `FVector GoalActorLastLocation;` — last location of goal actor that was used for repaths to prevent spamming when path is partial
- L1181 _function_ `inline void FNavigationPath::SetNavigationDataUsed(const ANavigationData* const NavData)`

#### enum `ERuntimeGenerationType`  
`enum class ERuntimeGenerationType : uint8`  
_L523-533_
- reflection: `UENUM()`
- desc: Supported options for runtime navigation data generation
- L526 _public enumerator_ `Static` — No runtime generation, fully static navigation data
- L528 _public enumerator_ `DynamicModifiersOnly` — Supports only navigation modifiers updates
- L530 _public enumerator_ `Dynamic` — Fully dynamic, supports geometry changes along with navigation modifiers
- L532 _public enumerator_ `LegacyGeneration UMETA(Hidden)` — Only for legacy loading don't use it!

#### class `ANavigationData`  
`class ANavigationData : public AActor, public INavigationDataInterface`  
_L540-1150_
- reflection: `UCLASS(config=Engine, defaultconfig, NotBlueprintable, abstract, MinimalAPI)`
- inherits: `AActor,INavigationDataInterface`
- desc: Represents abstract Navigation Data (sub-classed as NavMesh, NavGraph, etc) Used as a common interface for all navigation types handled by NavigationSystem
- L545 _private member_ `TObjectPtr<UPrimitiveComponent> RenderingComp;` — `UPROPERTY(transient, duplicatetransient)`
- L549 _protected member_ `FNavDataConfig NavDataConfig;` — `UPROPERTY()`
- L553 _protected member_ `uint32 bEnableDrawing:1;` — `UPROPERTY(Transient, EditAnywhere, Category=Display)` — if set to true then this navigation data will be drawing itself when requested as part of "show navigation"
- L562 _protected member_ `uint32 bForceRebuildOnLoad : 1;` — `UPROPERTY(config, EditAnywhere, Category = Runtime)` — By default, navigation will skip the first update after being successfully loaded. Setting bForceRebuildOnLoad to true can override this behavior.
- L567 _protected member_ `uint32 bAutoDestroyWhenNoNavigation : 1;` — `UPROPERTY(config, EditAnywhere, Category = Runtime)` — Should this instance auto-destroy when there's no navigation system on world when it gets created/loaded
- L571 _protected member_ `uint32 bCanBeMainNavData : 1;` — `UPROPERTY(config, EditAnywhere, Category = Runtime, AdvancedDisplay)` — If set, navigation data can act as default one in navigation system's queries
- L575 _protected member_ `uint32 bCanSpawnOnRebuild : 1;` — `UPROPERTY(config, VisibleAnywhere, Category = Runtime, AdvancedDisplay)` — If set, navigation data will be spawned in persistent level during rebuild if actor doesn't exist
- L579 _protected member_ `uint32 bRebuildAtRuntime_DEPRECATED:1;` — `UPROPERTY(config)` — If true, the NavMesh can be dynamically rebuilt at runtime.
- L583 _protected member_ `ERuntimeGenerationType RuntimeGeneration;` — `UPROPERTY(EditAnywhere, Category = Runtime, config)` — Navigation data runtime generation options
- L590 _protected member_ `uint32 bRequiresInitialRebuild : 1;` — Set when this nav data was spawned at runtime because no serialized instance existed in the loaded level. Gates that normally prevent rebuilding Static navmesh in game worlds check this flag to allow a one-time rebuild so NPCs can pathfind. Cleared once the rebuild completes, after which the nav data resumes normal Static behavior.
- L594 _protected member_ `float ObservedPathsTickInterval;` — `UPROPERTY(EditAnywhere, Category = Runtime, config)` — all observed paths will be processed every ObservedPathsTickInterval seconds
- L602 _public prototype_ `virtual void PostInitProperties() override;`
- L603 _public prototype_ `virtual void PostInitializeComponents() override;`
- L604 _public prototype_ `virtual void PostLoad() override;`
- L606 _public prototype_ `virtual void RerunConstructionScripts() override;`
- L607 _public prototype_ `virtual void PostEditUndo() override;`
- L608 _public function_ `bool IsBuildingOnLoad() const`
- L609 _public function_ `void SetIsBuildingOnLoad(bool bValue)`
- L611 _public prototype_ `virtual void Destroyed() override;`
- L612 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L615 _public prototype_ `virtual void CleanUp();`
- L616 _public prototype_ `virtual void ApplyWorldOffset(const FVector& InOffset, bool bWorldShift) override;`
- L619 _protected prototype_ `void RequestRegistration();`
- L623 _private prototype_ `void UnregisterAndCleanUp();` — Simply unregisters self from navigation system and calls CleanUp
- L626 _public prototype_ `void DestroyActor();`
- L627 _public prototype_ `virtual void CleanUpAndMarkPendingKill();`
- L629 _public function_ `inline bool IsRegistered() const`
- L630 _public prototype_ `virtual void OnRegistered();`
- L631 _public prototype_ `virtual void OnUnregistered();`
- L633 _public function_ `inline uint16 GetNavDataUniqueID() const`
- L635 _public prototype_ `virtual void TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;`
- L637 _public function_ `virtual bool NeedsRebuild() const`
- L638 _public prototype_ `virtual bool SupportsRuntimeGeneration() const;`
- L639 _public prototype_ `virtual bool SupportsStreaming() const;`
- L640 _public prototype_ `virtual void OnNavigationBoundsChanged();`
- L642 _public function_ `virtual void FillNavigationDataChunkActor(const FBox& QueryBounds, class ANavigationDataChunkActor& DataChunkActor, FBox& OutTilesBounds) const`
- L643 _public function_ `virtual void OnStreamingNavDataAdded(class ANavigationDataChunkActor& InActor)`
- L644 _public function_ `virtual void OnStreamingNavDataRemoved(class ANavigationDataChunkActor& InActor)`
- L646 _public function_ `virtual void OnStreamingLevelAdded(ULevel* InLevel, UWorld* InWorld)`
- L647 _public function_ `virtual void OnStreamingLevelRemoved(ULevel* InLevel, UWorld* InWorld)`
- L650 _public function_ `virtual double GetWorldPartitionNavigationDataBuilderOverlap() const`
- L657 _public function_ `inline const FNavDataConfig& GetConfig() const`
- L658 _public function_ `inline ERuntimeGenerationType GetRuntimeGenerationMode() const`
- L659 _public function_ `bool RequiresInitialRebuild() const`
- L660 _public function_ `void MarkRequiresInitialRebuild()`
- L661 _public function_ `void ClearRequiresInitialRebuild()`
- L665 _public prototype_ `virtual void SetConfig(const FNavDataConfig& Src);` — Populates NavDataConfig and sets NavAgentProperties with the Src config Should be used when initially configuring the navdata and not when updating values used in NavDataConfig
- L667 _public function_ `void SetSupportsDefaultAgent(bool bIsDefault)`
- L668 _public function_ `bool IsSupportingDefaultAgent() const`
- L669 _public function_ `const FNavAgentProperties& GetNavAgentProperties() const`
- L674 _public prototype_ `virtual bool DoesSupportAgent(const FNavAgentProperties& AgentProps) const;`
- L676 _public function_ `virtual void RestrictBuildingToActiveTiles(bool InRestrictBuildingToActiveTiles)`
- L678 _public function_ `bool CanBeMainNavData() const`
- L679 _public function_ `bool CanSpawnOnRebuild() const`
- L680 _public function_ `bool NeedsRebuildOnLoad() const`
- L683 _protected function_ `virtual void FillConfig(FNavDataConfig& Dest)`
- L687 _public prototype_ `virtual void ConditionalConstructGenerator();` — Creates new generator in case navigation supports it
- L690 _public function_ `virtual void LoadBeforeGeneratorRebuild()` — Any loading before NavDataGenerator->RebuildAll()
- L693 _public function_ `virtual void PostLoadPreRebuild()` — Runs after LoadBeforeGeneratorRebuild but before the rebuild.
- L696 _public prototype_ `virtual void RebuildAll();` — Triggers rebuild in case navigation supports it
- L699 _public prototype_ `virtual void EnsureBuildCompletion();` — Blocks until navigation build is complete
- L702 _public prototype_ `virtual void CancelBuild();` — Cancels current build
- L708 _public prototype_ `virtual void TickAsyncBuild(float DeltaSeconds);` — Ticks navigation build If the generator is set to time sliced rebuild then this function will only get called when there is sufficient time (effectively roughly once in n frames where n is the number of time sliced nav data generators currently building)
- L711 _public function_ `FNavDataGenerator* GetGenerator()` — Retrieves navigation data generator
- L712 _public function_ `const FNavDataGenerator* GetGenerator() const`
- L715 _public prototype_ `virtual void RebuildDirtyAreas(const TArray<FNavigationDirtyArea>& DirtyAreas);` — Request navigation data update after changes in nav octree
- L729 _public prototype_ `virtual void SetRebuildingSuspended(const bool bNewSuspend);` — Configures this NavData instance's navigation generation to be suspended or active. It's active by default. If Suspended then all calls to RebuildDirtyAreas will result in caching the request in SuspendedDirtyAreas until SetRebuildingSuspended(false) gets call at which time all the contents of SuspendedDirtyAreas will get pushed to the nav generator and SuspendedDirtyAreas will be cleaned out. Note that calling SetRebuildingSuspended(true) won't suspend the nav generation already in progress. Warning: Leaving generation suspended for extended periods of time can trigger a RebuildAll(). To prevent the queue from growing out of control, it is limited by ai.navigation.MaxDirtyAreasCountWhileSuspended If that limit is reached, upon resuming, the entire navigation data will be rebuilt.
- L732 _public function_ `virtual bool IsRebuildingSuspended() const` — Retrieves if this NavData instance's navigation generation is suspended
- L735 _public function_ `virtual int32 GetNumSuspendedDirtyAreas() const` — Retrieves the number of suspended dirty areas
- L740 _protected prototype_ `void RegisterAsNavAreaClassObserver();` — register self with navigation system as new NavAreaDefinition(s) observer
- L748 _public function_ `template<typename PathType> FNavPathSharedPtr CreatePathInstance(const FPathFindingQueryData& QueryData) const` — Created an instance of navigation path of specified type. PathType needs to derive from FNavigationPath
- L759 _public function_ `void RegisterObservedPath(FNavPathSharedPtr SharedPath)`
- L769 _public function_ `void RequestRePath(FNavPathSharedPtr Path, ENavPathUpdateType::Type Reason)`
- L777 _protected prototype_ `void PurgeUnusedPaths();` — removes from ActivePaths all paths that no longer have shared references (and are invalid in fact)
- L779 _protected prototype_ `void RegisterActivePath(FNavPathSharedPtr SharedPath);`
- L783 _public prototype_ `virtual FBox GetBounds() const PURE_VIRTUAL(ANavigationData::GetBounds,return FBox(););` — Returns bounding box for the navmesh.
- L786 _public prototype_ `TArray<FBox> GetNavigableBounds() const;` — Returns list of navigable bounds.
- L789 _public prototype_ `TArray<FBox> GetNavigableBoundsInLevel(ULevel* InLevel) const;` — Returns list of navigable bounds that belongs to specific level
- L794 _public prototype_ `void DrawDebugPath(FNavigationPath* Path, const FColor PathColor = FColor::White, class UCanvas* Canvas = nullptr, const bool bPersistent = true, const float LifeTime = -1.f, const uint32 NextPathPointIndex = 0) const;`
- L796 _public function_ `inline bool IsDrawingEnabled() const`
- L799 _public prototype_ `virtual uint32 LogMemUsed() const;` — @return Total mem counted, including super calls.
- L806 _public function_ `virtual void BeginBatchQuery() const` — Starts batch processing and locks access to navigation data from other threads
- L809 _public function_ `virtual void FinishBatchQuery() const` — Finishes batch processing and release locks
- L814 _public function_ `inline FSharedConstNavQueryFilter GetDefaultQueryFilter() const`
- L815 _public function_ `inline const class INavigationQueryFilterInterface* GetDefaultQueryFilterImpl() const`
- L816 _public function_ `inline FVector GetDefaultQueryExtent() const`
- L826 _public function_ `inline FPathFindingResult FindPath(const FNavAgentProperties& AgentProperties, const FPathFindingQuery& Query) const` — Synchronously looks for a path from @StartLocation to @EndLocation for agent with properties @AgentProperties. NavMesh actor appropriate for specified FNavAgentProperties will be found automatically @param ResultPath results are put here @return true if path has been found, false otherwise @note don't make this function virtual! Look at implementation details and its comments for more info.
- L841 _public function_ `inline FPathFindingResult FindHierarchicalPath(const FNavAgentProperties& AgentProperties, const FPathFindingQuery& Query) const` — Synchronously looks for a path from @StartLocation to @EndLocation for agent with properties @AgentProperties. NavMesh actor appropriate for specified FNavAgentProperties will be found automatically @param ResultPath results are put here @return true if path has been found, false otherwise @note don't make this function virtual! Look at implementation details and its comments for more info.
- L855 _public function_ `inline bool TestPath(const FNavAgentProperties& AgentProperties, const FPathFindingQuery& Query, int32* NumVisitedNodes) const` — Synchronously checks if path between two points exists FNavAgentProperties will be found automatically @return true if path has been found, false otherwise @note don't make this function virtual! Look at implementation details and its comments for more info.
- L869 _public function_ `inline bool TestHierarchicalPath(const FNavAgentProperties& AgentProperties, const FPathFindingQuery& Query, int32* NumVisitedNodes) const` — Synchronously checks if path between two points exists using hierarchical graph FNavAgentProperties will be found automatically @return true if path has been found, false otherwise @note don't make this function virtual! Look at implementation details and its comments for more info.
- L883 _public function_ `inline bool Raycast(const FVector& RayStart, const FVector& RayEnd, FVector& HitLocation, FSharedConstNavQueryFilter QueryFilter, const UObject* Querier = NULL) const` — Synchronously makes a raycast on navigation data using QueryFilter @param HitLocation if line was obstructed this will be set to hit location. Otherwise it contains SegmentEnd @return true if line from RayStart to RayEnd is obstructed @note don't make this function virtual! Look at implementation details and its comments for more info.
- L896 _public function_ `inline bool Raycast(const FVector& RayStart, const FVector& RayEnd, FVector& HitLocation, FNavigationRaycastAdditionalResults* AdditionalResults, FSharedConstNavQueryFilter QueryFilter, const UObject* Querier = NULL) const` — Synchronously makes a raycast on navigation data using QueryFilter @param HitLocation if line was obstructed this will be set to hit location. Otherwise it contains SegmentEnd @param AdditionalResults contains more information about the result of the raycast query. See FNavigationRaycastAdditionalResults description for details @return true if line from RayStart to RayEnd is obstructed @note don't make this function virtual! Look at implementation details and its comments for more info.
- L904 _public prototype_ `virtual void BatchRaycast(TArray<FNavigationRaycastWork>& Workload, FSharedConstNavQueryFilter QueryFilter, const UObject* Querier = NULL) const PURE_VIRTUAL(ANavigationData::BatchRaycast, );` — Raycasts batched for efficiency
- L910 _public prototype_ `virtual bool FindMoveAlongSurface(const FNavLocation& StartLocation, const FVector& TargetPosition, FNavLocation& OutLocation, FSharedConstNavQueryFilter Filter = NULL, const UObject* Querier = NULL) const PURE_VIRTUAL(ANavigationData::FindMoveAlongSurface, return false;);` — Tries to move current nav location towards target constrained to navigable area. Faster than ProjectPointToNavmesh. @param OutLocation if successful this variable will be filed with result @return true if successful, false otherwise
- L915 _public prototype_ `virtual void BatchFindMoveAlongSurface(TArray<FNavigationFindMoveAlongSurfaceWork>& Workload, FSharedConstNavQueryFilter Filter = NULL, const UObject* Querier = NULL) const PURE_VIRTUAL(ANavigationData::BatchFindMoveAlongSurface, );` — Batches FindMoveAlongSurface calls for efficiency. @note Refer to FindMoveAlongSurface function documentation for more information
- L924 _public prototype_ `virtual bool FindOverlappingEdges(const FNavLocation& StartLocation, TConstArrayView<FVector> ConvexPolygon, TArray<FVector>& OutEdges, FSharedConstNavQueryFilter Filter = NULL, const UObject* Querier = NULL) const PURE_VIRTUAL(ANavigationData::FindOverlappingEdges, return false;);` — Returns the navmesh edges that touch the convex polygon. The edges are not clipped by the polygon. @param StartLocation a location on the navmesh where to start searching. @param ConvexPolygon 2D convex polygon that describes the search area. @param OutEdges result edges, each edge is an adjacent pair of points in the array. @param Filter Nav filter to use, or if nullptr, default filter is used. @return true if successful, false otherwise
- L936 _public prototype_ `virtual bool GetPathSegmentBoundaryEdges(const FNavigationPath& Path, const FNavPathPoint& StartPoint, const FNavPathPoint& EndPoint, const TConstArrayView<FVector> SearchArea, TArray<FVector>& OutEdges, const float MaxAreaEnterCost, FSharedConstNavQueryFilter Filter = NULL, const UObject* Querier = NULL) const PURE_VIRTUAL(ANavigationData::GetPathSegmentBoundaryEdges, return false;);` — Searches navmesh edges between the two path points, search up to the convex polygon described in SearchArea. The returned edges are not clipped to the search area polygon. @param Path Path where From and To belong to. @param StartPoint start location of the path segment. @param EndPoint end location of the path segment. @param SearchArea 2D convex polygon that describes the search area. @param OutEdges result edges, each edge is an adjacent pair of points in the array. @param MaxAreaEnterCost if the fixed cost to enter a node is higher than this value, the node is considered unnavigable. @param Filter Nav filter to use, or if nullptr, default filter is used. @return true if successful, false otherwise
- L938 _public prototype_ `virtual FNavLocation GetRandomPoint(FSharedConstNavQueryFilter Filter = NULL, const UObject* Querier = NULL) const PURE_VIRTUAL(ANavigationData::GetRandomPoint, return FNavLocation(););`
- L941 _public prototype_ `virtual bool GetRandomReachablePointInRadius(const FVector& Origin, float Radius, FNavLocation& OutResult, FSharedConstNavQueryFilter Filter = NULL, const UObject* Querier = NULL) const PURE_VIRTUAL(ANavigationData::GetRandomReachablePointInRadius, return false;);` — finds a random location in Radius, reachable from Origin
- L944 _public prototype_ `virtual bool GetRandomPointInNavigableRadius(const FVector& Origin, float Radius, FNavLocation& OutResult, FSharedConstNavQueryFilter Filter = NULL, const UObject* Querier = NULL) const PURE_VIRTUAL(ANavigationData::GetRandomPointInNavigableRadius, return false;);` — finds a random location in navigable space, in given Radius
- L950 _public prototype_ `virtual bool ProjectPoint(const FVector& Point, FNavLocation& OutLocation, const FVector& Extent, FSharedConstNavQueryFilter Filter = NULL, const UObject* Querier = NULL) const PURE_VIRTUAL(ANavigationData::ProjectPoint, return false;);` — Tries to project given Point to this navigation type, within given Extent. @param OutLocation if successful this variable will be filed with result @return true if successful, false otherwise
- L953 _public prototype_ `virtual void BatchProjectPoints(TArray<FNavigationProjectionWork>& Workload, const FVector& Extent, FSharedConstNavQueryFilter Filter = NULL, const UObject* Querier = NULL) const PURE_VIRTUAL(ANavigationData::BatchProjectPoints, );` — batches ProjectPoint's work for efficiency
- L958 _public prototype_ `virtual void BatchProjectPoints(TArray<FNavigationProjectionWork>& Workload, FSharedConstNavQueryFilter Filter = NULL, const UObject* Querier = NULL) const PURE_VIRTUAL(ANavigationData::BatchProjectPoints, );` — Project batch of points using shared search filter. This version is not requiring user to pass in Extent, and is instead relying on FNavigationProjectionWork.ProjectionLimit. @note function should assert if item's FNavigationProjectionWork.ProjectionLimit is invalid
- L963 _public prototype_ `virtual ENavigationQueryResult::Type CalcPathCost(const FVector& PathStart, const FVector& PathEnd, FVector::FReal& OutPathCost, FSharedConstNavQueryFilter QueryFilter = NULL, const UObject* Querier = NULL) const PURE_VIRTUAL(ANavigationData::CalcPathCost, return ENavigationQueryResult::Invalid;);` — Calculates path from PathStart to PathEnd and retrieves its cost. @NOTE this function does not generate string pulled path so the result is an (over-estimated) approximation @NOTE potentially expensive, so use it with caution
- L968 _public prototype_ `virtual ENavigationQueryResult::Type CalcPathLength(const FVector& PathStart, const FVector& PathEnd, FVector::FReal& OutPathLength, FSharedConstNavQueryFilter QueryFilter = NULL, const UObject* Querier = NULL) const PURE_VIRTUAL(ANavigationData::CalcPathLength, return ENavigationQueryResult::Invalid;);` — Calculates path from PathStart to PathEnd and retrieves its length. @NOTE this function does not generate string pulled path so the result is an (over-estimated) approximation @NOTE potentially expensive, so use it with caution
- L973 _public prototype_ `virtual ENavigationQueryResult::Type CalcPathLengthAndCost(const FVector& PathStart, const FVector& PathEnd, FVector::FReal& OutPathLength, FVector::FReal& OutPathCost, FSharedConstNavQueryFilter QueryFilter = NULL, const UObject* Querier = NULL) const PURE_VIRTUAL(ANavigationData::CalcPathLengthAndCost, return ENavigationQueryResult::Invalid;);` — Calculates path from PathStart to PathEnd and retrieves its length. @NOTE this function does not generate string pulled path so the result is an (over-estimated) approximation @NOTE potentially expensive, so use it with caution
- L977 _public prototype_ `virtual bool DoesNodeContainLocation(NavNodeRef NodeRef, const FVector& WorldSpaceLocation) const PURE_VIRTUAL(ANavigationData::DoesNodeContainLocation, return false;);` — Checks if specified navigation node contains given location @param Location is expressed in WorldSpace, navigation data is responsible for tansforming if need be
- L979 _public prototype_ `double GetWorldTimeStamp() const;`
- L986 _public prototype_ `virtual void OnNavAreaAdded(const UClass* NavAreaClass, int32 AgentIndex);` — new area was registered in navigation system
- L989 _public prototype_ `virtual void OnNavAreaRemoved(const UClass* NavAreaClass);` — area was removed from navigation system
- L992 _public prototype_ `virtual void OnNavAreaChanged();` — called after changes to registered area classes
- L994 _public prototype_ `void OnNavAreaEvent(const UClass* NavAreaClass, ENavAreaEvent::Type Event);`
- L997 _public prototype_ `void ProcessNavAreas(const TSet<const UClass*>& AreaClasses, int32 AgentIndex);` — add all existing areas
- L1000 _public prototype_ `const UClass* GetAreaClass(int32 AreaID) const;` — get class associated with AreaID
- L1003 _public prototype_ `bool IsAreaAssigned(int32 AreaID) const;` — check if AreaID was assigned to class (class itself may not be loaded yet!)
- L1006 _public prototype_ `int32 GetAreaID(const UClass* AreaClass) const;` — get ID assigned to AreaClas or -1 when not assigned
- L1009 _public function_ `virtual int32 GetMaxSupportedAreas() const` — get max areas supported by this navigation data
- L1012 _public function_ `void GetSupportedAreas(TArray<FSupportedAreaData>& Areas) const` — read all supported areas
- L1018 _public prototype_ `virtual void UpdateCustomLink(const INavLinkCustomInterface* CustomLink);`
- L1025 _public prototype_ `FSharedConstNavQueryFilter GetQueryFilter(TSubclassOf<UNavigationQueryFilter> FilterClass) const;` — get cached query filter
- L1028 _public prototype_ `void StoreQueryFilter(TSubclassOf<UNavigationQueryFilter> FilterClass, FSharedConstNavQueryFilter NavFilter);` — store cached query filter
- L1031 _public prototype_ `void RemoveQueryFilter(TSubclassOf<UNavigationQueryFilter> FilterClass);` — removes cached query filter
- L1036 _public function_ `virtual UPrimitiveComponent* ConstructRenderingComponent()`
- L1039 _public prototype_ `void SetNavRenderingEnabled(bool bEnable);` — updates state of rendering component
- L1042 _public function_ `virtual bool CanChangeIsSpatiallyLoadedFlag() const override`
- L1046 _protected prototype_ `void InstantiateAndRegisterRenderingComponent();`
- L1049 _protected prototype_ `virtual int32 GetNewAreaID(const UClass* AreaClass) const;` — get ID to assign for newly added area
- L1054 _protected member_ `uint32 DataVersion;` — `UPROPERTY()` — Navigation data versioning.
- L1056 _protected typedef_ `typedef FPathFindingResult (*FFindPathPtr)(const FNavAgentProperties& AgentProperties, const FPathFindingQuery& Query);`
- L1057 _protected member_ `FFindPathPtr FindPathImplementation;`
- L1058 _protected member_ `FFindPathPtr FindHierarchicalPathImplementation;`
- L1060 _protected typedef_ `typedef bool (*FTestPathPtr)(const FNavAgentProperties& AgentProperties, const FPathFindingQuery& Query, int32* NumVisitedNodes);`
- L1061 _protected member_ `FTestPathPtr TestPathImplementation;`
- L1062 _protected member_ `FTestPathPtr TestHierarchicalPathImplementation;`
- L1064 _protected typedef_ `typedef bool(*FNavRaycastPtr)(const ANavigationData* NavDataInstance, const FVector& RayStart, const FVector& RayEnd, FVector& HitLocation, FSharedConstNavQueryFilter QueryFilter, const UObject* Querier);`
- L1066 _protected member_ `FNavRaycastPtr RaycastImplementation;` — `UE_DEPRECATED(5.6, "Please use RaycastImplementationWithAdditionalResults instead")`
- L1068 _protected typedef_ `typedef bool(*FNavRaycastWithAdditionalResultsPtr)(const ANavigationData* NavDataInstance, const FVector& RayStart, const FVector& RayEnd, FVector& HitLocation, FNavigationRaycastAdditionalResults* AdditionalResults, FSharedConstNavQueryFilter QueryFilter, const UObject* Querier);`
- L1069 _protected member_ `FNavRaycastWithAdditionalResultsPtr RaycastImplementationWithAdditionalResults;`
- L1072 _protected member_ `TSharedPtr<FNavDataGenerator, ESPMode::ThreadSafe> NavDataGenerator;`
- L1078 _protected member_ `TArray<FNavigationDirtyArea> SuspendedDirtyAreas;` — caches requests to rebuild dirty areas while nav rebuilding is suspended via SetRebuildingSuspended(true) call. Calling SetRebuildingSuspended(false) will result in pushing SuspendedDirtyAreas contents to the nav generator and clearing out of SuspendedDirtyAreas
- L1085 _protected member_ `TArray<FNavPathWeakPtr> ActivePaths;` — Container for all path objects generated with this Navigation Data instance. Is meant to be added to only on GameThread, and in fact should user should never add items to it manually, @see CreatePathInstance
- L1088 _protected member_ `mutable FTransactionallySafeCriticalSection ActivePathsLock;` — Synchronization object for paths registration from main thread and async pathfinding thread
- L1093 _protected member_ `TArray<FNavPathWeakPtr> ObservedPaths;` — Contains paths that requested observing its goal's location. These paths will be processed on a regular basis (@see ObservedPathsTickInterval)
- L1096 _protected member_ `TArray<FNavPathRecalculationRequest> RepathRequests;` — paths that requested re-calculation
- L1099 _protected member_ `float NextObservedPathsTickInSeconds;` — contains how much time left to the next ObservedPaths processing
- L1102 _protected member_ `FSharedNavQueryFilter DefaultQueryFilter;` — Query filter used when no other has been passed to relevant functions
- L1105 _protected member_ `TMap<UClass*,FSharedConstNavQueryFilter > QueryFilters;` — Map of query filters by UNavigationQueryFilter class
- L1109 _protected member_ `TArray<FSupportedAreaData> SupportedAreas;` — `UPROPERTY(VisibleAnywhere, Category=Areas, meta=(TitleProperty="{AreaID}: {AreaClassName}"))` — serialized area class - ID mapping
- L1112 _protected member_ `TMap<const UClass*, int32> AreaClassToIdMap;` — mapping for SupportedAreas
- L1115 _protected member_ `uint32 bRegistered : 1;` — whether this instance is registered with Navigation System
- L1118 _protected member_ `uint32 bSupportsDefaultAgent : 1;` — was it generated for default agent (SupportedAgents[0])
- L1123 _protected member_ `uint32 bRebuildingSuspended : 1;` — Set via SetRebuildingSuspended and controlling if RebuildDirtyAreas get passed over to the generator instantly or cached in SuspendedDirtyAreas to be applied at later date with SetRebuildingSuspended(false) call
- L1129 _protected member_ `uint32 bReachedSuspendedAreasMaxCount : 1 = false;` — Becomes true when too many dirty areas have been accumulated while rebuild was suspended (see SetRebuildingSuspended). If rebuilding is resumed after reaching the max count, this entire navigation data will be rebuilt.
- L1132 _protected member_ `uint32 bIsBuildingOnLoad : 1;`
- L1136 _private member_ `uint16 NavDataUniqueID;`
- L1138 _private prototype_ `static uint16 GetNextUniqueID();`
- L1144 _protected member_ `FNavAgentProperties NavAgentProperties;` — The exact nav agent properties used when registering this navdata in the navigation system. If navdata configuration changes are needed, NavDataConfig can be modified and used
- L1146 _protected function_ `void SetNavAgentProperties(const FNavAgentProperties& InNavAgentProperties)`

#### struct `FAsyncPathFindingQuery`  
`struct FAsyncPathFindingQuery : public FPathFindingQuery`  
_L1152-1174_
- inherits: `FPathFindingQuery`
- L1154 _public member_ `const uint32 QueryID;`
- L1155 _public member_ `const FNavPathQueryDelegate OnDoneDelegate;`
- L1156 _public member_ `const TEnumAsByte<EPathFindingMode::Type> Mode;`
- L1157 _public member_ `FPathFindingResult Result;`
- L1159 _public function_ `FAsyncPathFindingQuery() : QueryID(INVALID_NAVQUERYID) , Mode(EPathFindingMode::Regular)`
- L1164 _public prototype_ `FAsyncPathFindingQuery(const UObject* InOwner, const ANavigationData& InNavData, const FVector& Start, const FVector& End, const FNavPathQueryDelegate& Delegate, FSharedConstNavQueryFilter SourceQueryFilter, const FVector::FReal CostLimit = TNumericLimits<FVector::FReal>::Max());`
- L1165 _public prototype_ `FAsyncPathFindingQuery(const FPathFindingQuery& Query, const FNavPathQueryDelegate& Delegate, const EPathFindingMode::Type QueryMode);`
- L1168 _protected function_ `inline static uint32 GetUniqueID()`
- L1173 _protected member_ `static uint32 LastPathFindingUniqueID;`

#### Free symbols / members of external scopes

- L83 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FPathObserverDelegate, FNavigationPath*, ENavPathEvent::Type);` — DECLARE_DELEGATE_OneParam(FPathObserverDelegate, FNavigationPath*);

### `Source/Runtime/NavigationSystem/Public/NavigationDataHandler.h` (Public)


#### struct `FNavigationDataHandler`  
`struct FNavigationDataHandler`  
_L11-60_
- L13 _public member_ `FNavigationOctreeController& OctreeController;`
- L14 _public member_ `FNavigationDirtyAreasController& DirtyAreasController;`
- L16 _public prototype_ `FNavigationDataHandler(FNavigationOctreeController& InOctreeController, FNavigationDirtyAreasController& InDirtyAreasController);`
- L18 _public prototype_ `void ConstructNavOctree(const FVector& Origin, const double Radius, const ENavDataGatheringModeConfig DataGatheringMode, const float GatheringNavModifiersWarningLimitTime);`
- L24 _public prototype_ `void RemoveFromNavOctree(const FOctreeElementId2& ElementId, int32 UpdateFlags);` — Removes the octree node and the NavigationElementHandle-OctreeElementId pair associated to the specified OctreeElementId. It will also dirty the area base of the NavigationElement values and the specified update flags.
- L26 _public prototype_ `FSetElementId RegisterElementWithNavOctree(const TSharedRef<const FNavigationElement>& ElementRef, int32 UpdateFlags);`
- L27 _public prototype_ `void AddElementToNavOctree(const FNavigationDirtyElement& DirtyElement);`
- L37 _public prototype_ `bool UnregisterElementWithNavOctree(const TSharedRef<const FNavigationElement>& ElementRef, int32 UpdateFlags);` — Removes associated NavOctreeElement and invalidates associated pending updates. Also removes element from the list of children of the NavigationParent, if any. @param ElementRef		Navigation element for which we must remove the associated NavOctreeElement @param UpdateFlags		Flags indicating in which context the method is called to allow/forbid certain operations @return True if associated NavOctreeElement has been removed or pending update has been invalidated; false otherwise.
- L43 _public prototype_ `void UpdateNavOctreeElement(FNavigationElementHandle ElementHandle, const TSharedRef<const FNavigationElement>& UpdatedElement, int32 UpdateFlags);` — Unregister element associated with the provided handle and register the new element. Also update any pending update associated to that element.
- L45 _public prototype_ `bool UpdateNavOctreeElementBounds(FNavigationElementHandle Element, const FBox& NewBounds, const TConstArrayView<FBox> DirtyAreas);`
- L47 _public prototype_ `void FindElementsInNavOctree(const FBox& QueryBox, const FNavigationOctreeFilter& Filter, TArray<FNavigationOctreeElement>& Elements);`
- L49 _public prototype_ `bool ReplaceAreaInOctreeData(FNavigationElementHandle Element, TSubclassOf<UNavArea> OldArea, TSubclassOf<UNavArea> NewArea, bool bReplaceChildClasses) const;`
- L51 _public prototype_ `void AddLevelCollisionToOctree(ULevel& Level);`
- L52 _public prototype_ `void RemoveLevelCollisionFromOctree(ULevel& Level);`
- L54 _public prototype_ `void ProcessPendingOctreeUpdates();`
- L56 _public prototype_ `void DemandLazyDataGathering(FNavigationRelevantData& ElementData);`
- L59 _private prototype_ `void UpdateNavOctreeParentChain(const TSharedRef<const FNavigationElement>& Element, bool bSkipElementOwnerUpdate = false);`

### `Source/Runtime/NavigationSystem/Public/NavigationDirtyAreasController.h` (Public)


#### struct `FNavigationDirtyAreasController`  
`struct FNavigationDirtyAreasController`  
_L22-100_
- L25 _public member_ `float DirtyAreasUpdateFreq = 60.f;` — update frequency for dirty areas on navmesh
- L28 _public member_ `float DirtyAreasUpdateTime = 0.f;` — temporary cumulative time to calculate when we need to update dirty areas
- L32 _public member_ `TArray<FNavigationDirtyArea> DirtyAreas;` — stores areas marked as dirty throughout the frame, processes them once a frame in Tick function
- L34 _public member_ `uint8 bCanAccumulateDirtyAreas : 1;`
- L35 _public member_ `uint8 bUseWorldPartitionedDynamicMode : 1;`
- L38 _public member_ `uint8 bDirtyAreasReportedWhileAccumulationLocked : 1;`
- L40 _private member_ `uint8 bCanReportOversizedDirtyArea : 1;`
- L41 _private member_ `uint8 bNavigationBuildLocked : 1;`
- L44 _private member_ `float DirtyAreaWarningSizeThreshold = -1.f;` — -1 by default, if set to a positive value dirty area with bounds size over that threshold will be logged
- L46 _private prototype_ `bool ShouldReportOversizedDirtyArea() const;`
- L50 _public prototype_ `FNavigationDirtyAreasController();`
- L52 _public prototype_ `void Reset();`
- L55 _public prototype_ `void ForceRebuildOnNextTick();` — sets cumulative time to at least one cycle so next tick will rebuild dirty areas
- L57 _public prototype_ `void Tick(float DeltaSeconds, const TArray<ANavigationData*>& NavDataSet, bool bForceRebuilding = false);`
- L68 _public prototype_ `void AddArea(const FBox& NewArea, const ENavigationDirtyFlag Flags, const TFunction<const TSharedPtr<const FNavigationElement>()>& ElementProviderFunc = nullptr, const FNavigationDirtyElement* DirtyElement = nullptr, const FName& DebugReason = NAME_None);` — Add a dirty area to the queue based on the provided bounds and flags. Bounds must be valid and non-empty otherwise the request will be ignored and a warning reported. Accumulation must be allowed and flags valid otherwise the add is ignored. @param NewArea Bounding box of the affected area @param Flags Indicates the type of modification applied to the area @param ElementProviderFunc Optional function to retrieve source element that can be used for error reporting and navmesh exclusion @param DirtyElement Optional dirty element @param DebugReason Source of the new area
- L81 _public prototype_ `void AddAreas(const TConstArrayView<FBox> NewAreas, const ENavigationDirtyFlag Flags, const TFunction<const TSharedPtr<const FNavigationElement>()>& ElementProviderFunc = nullptr, const FNavigationDirtyElement* DirtyElement = nullptr, const FName& DebugReason = NAME_None);` — Add non-empty list of dirty areas to the queue based on the provided bounds and flags. Bounds must be valid and non-empty otherwise the request will be ignored and a warning reported. Accumulation must be allowed and flags valid otherwise the add is ignored. A check will be triggered if an empty array is provided. @param NewAreas Array of bounding boxes of the affected areas @param Flags Indicates the type of modification applied to the area @param ElementProviderFunc Optional function to retrieve source element that can be used for error reporting and navmesh exclusion @param DirtyElement Optional dirty element @param DebugReason Source of the new area
- L84 _public function_ `bool IsDirty() const`
- L85 _public function_ `int32 GetNumDirtyAreas() const`
- L87 _public prototype_ `void OnNavigationBuildLocked();`
- L88 _public prototype_ `void OnNavigationBuildUnlocked();`
- L90 _public prototype_ `void SetUseWorldPartitionedDynamicMode(bool bIsWPDynamic);`
- L91 _public prototype_ `void SetCanReportOversizedDirtyArea(const bool bCanReport);`
- L92 _public prototype_ `void SetDirtyAreaWarningSizeThreshold(const float Threshold);`
- L95 _public function_ `bool HadDirtyAreasReportedWhileAccumulationLocked() const`
- L98 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FSkipObjectSignature, const UObject& );`
- L99 _public member_ `FSkipObjectSignature ShouldSkipObjectPredicate;`

#### Free symbols / members of external scopes

- L20 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogNavigationDirtyArea, Warning, All);`
- L98 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FSkipObjectSignature, const UObject& );`

### `Source/Runtime/NavigationSystem/Public/NavigationInvokerComponent.h` (Public)


#### class `UNavigationInvokerComponent`  
`class UNavigationInvokerComponent : public UActorComponent`  
_L15-56_
- reflection: `UCLASS(ClassGroup = (Navigation), meta = (BlueprintSpawnableComponent), MinimalAPI)`
- inherits: `UActorComponent`
- L23 _protected member_ `float TileGenerationRadius;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Navigation, meta = (ClampMin = "0.1", ClampMax = "6400000", UIMin = "0.1", UIMax = "6400000"))` — Navigation data is requested within a TileGenerationRadius circle around the component owner.
- L28 _protected member_ `float TileRemovalRadius;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Navigation, meta = (ClampMin = "0.1", ClampMax = "6400000", UIMin = "0.1", UIMax = "6400000"))` — Navigation data can be discarded when outside of a TileRemovalRadius circle around the component owner. This is computed for all navigation invokers, so a navigation data must be outside of all navigation invokers TileRemovalRadius circles to be discarded.
- L32 _protected member_ `FNavAgentSelector SupportedAgents;` — `UPROPERTY(EditAnywhere, Category = Navigation)` — restrict navigation generation to specific agents
- L36 _protected member_ `ENavigationInvokerPriority Priority;` — `UPROPERTY(EditAnywhere, Category = Navigation)` — Experimental invocation priority. It will modify the order in which invoked tiles are being built if SortPendingTilesMethod is set to SortByPriority.
- L39 _public prototype_ `UNavigationInvokerComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L41 _public prototype_ `void RegisterWithNavigationSystem(UNavigationSystemV1& NavSys);`
- L45 _public prototype_ `void SetGenerationRadii(const float GenerationRadius, const float RemovalRadius);` — Sets generation/removal ranges. Doesn't force navigation system's update. Will get picked up the next time NavigationSystem::UpdateInvokers gets called
- L47 _public function_ `float GetGenerationRadius() const`
- L48 _public function_ `float GetRemovalRadius() const`
- L50 _public prototype_ `virtual void Activate(bool bReset = false) override;`
- L51 _public prototype_ `virtual void Deactivate() override;`
- L52 _public prototype_ `virtual void PostInitProperties() override;`
- L55 _private prototype_ `void OnNavigationInitStart(const class UNavigationSystemBase& NavSys);`

### `Source/Runtime/NavigationSystem/Public/NavigationOctree.h` (Public)


#### struct `FNavigationOctreeElement`  
`struct FNavigationOctreeElement`  
_L22-109_
- L24 _public member_ `FBoxSphereBounds Bounds;`
- L25 _public member_ `TSharedRef<FNavigationRelevantData, ESPMode::ThreadSafe> Data;`
- L27 _public function_ `explicit FNavigationOctreeElement(const TSharedRef<const FNavigationElement>& SourceObject) : Bounds(SourceObject.Get().GetBounds()) , Data(MakeShared<FNavigationRelevantData>(SourceObject))`
- L33 _public function_ `FNavigationOctreeElement(const FNavigationOctreeElement& Other) : Bounds(Other.Bounds) , Data(Other.Data)`
- L38 _public function_ `FNavigationOctreeElement(FNavigationOctreeElement&& Other) noexcept : Bounds(MoveTemp(Other.Bounds)) , Data(MoveTemp(Other.Data))`
- L44 _public function_ `FNavigationOctreeElement& operator=(FNavigationOctreeElement&& Other)`
- L54 _public function_ `FNavigationOctreeElement& operator=(const FNavigationOctreeElement& Other)`
- L64 _public function_ `FORCEINLINE bool IsEmpty() const`
- L70 _public function_ `FORCEINLINE bool IsMatchingFilter(const FNavigationOctreeFilter& Filter) const`
- L80 _public function_ `FORCEINLINE FCompositeNavModifier GetModifierForAgent(const FNavAgentProperties* NavAgent = nullptr) const` — Retrieves Modifier if it doesn't contain any "Meta Navigation Areas". If it does, then retrieves a copy with meta areas substituted with appropriate non-meta areas, depending on NavAgent.
- L85 _public function_ `FORCEINLINE bool ShouldUseGeometry(const FNavDataConfig& NavConfig) const`
- L90 _public function_ `FORCEINLINE int32 GetAllocatedSize() const`
- L95 _public function_ `FORCEINLINE void Shrink()`
- L100 _public function_ `FORCEINLINE void ValidateAndShrink()`
- L105 _public function_ `const TSharedRef<const FNavigationElement>& GetSourceElement() const`

#### struct `FNavigationOctreeSemantics`  
`struct FNavigationOctreeSemantics`  
_L111-139_
- L113 _public typedef_ `typedef TOctree2<FNavigationOctreeElement, FNavigationOctreeSemantics> FOctree;`
- L118 _public typedef_ `typedef TInlineAllocator<MaxElementsPerLeaf> ElementAllocator;`
- L120 _public function_ `FORCEINLINE static const FBoxSphereBounds& GetBoundingBox(const FNavigationOctreeElement& NavData)`
- L125 _public function_ `FORCEINLINE static bool AreElementsEqual(const FNavigationOctreeElement& A, const FNavigationOctreeElement& B)`
- L130 _public function_ `FORCEINLINE static void ApplyOffset(FNavigationOctreeElement& Element, const FVector& InOffset)`
- L138 _public prototype_ `static void SetElementId(FOctree& OctreeOwner, const FNavigationOctreeElement& Element, FOctreeElementId2 Id);`

#### enum `FNavigationOctreeSemantics::(anonymous)`  
`enum`  
_L114-114_

#### enum `FNavigationOctreeSemantics::(anonymous)`  
`enum`  
_L115-115_

#### enum `FNavigationOctreeSemantics::(anonymous)`  
`enum`  
_L116-116_

#### class `FNavigationOctree`  
`class FNavigationOctree : public TOctree2<FNavigationOctreeElement, FNavigationOctreeSemantics>, public TSharedFromThis<FNavigationOctree, ESPMode::ThreadSafe>`  
_L141-235_
- inherits: `TOctree2<FNavigationOctreeElement,FNavigationOctreeSemantics>,TSharedFromThis<FNavigationOctree,ESPMode::ThreadSafe>`
- L144 _public prototype_ `DECLARE_DELEGATE_TwoParams(FGeometryExportDelegate, const FNavigationElement&, FNavigationRelevantData&);`
- L145 _public member_ `FGeometryExportDelegate GeometryExportDelegate;`
- L156 _public function_ `inline void AddElement(const FNavigationOctreeElement& Element)` — Adds an element to the octree. @param Element - The element to add.
- L172 _public function_ `inline void RemoveElement(FOctreeElementId2 ElementId)` — Removes an element from the octree. @param ElementId - The element to remove from the octree.
- L182 _public prototype_ `FNavigationOctree(const FVector& Origin, FVector::FReal Radius);`
- L183 _public prototype_ `virtual ~FNavigationOctree();`
- L186 _public prototype_ `void AddNode(const FBox& Bounds, FNavigationOctreeElement& OctreeElement);` — Add new node and fill it with navigation export data
- L189 _public prototype_ `void AppendToNode(const FOctreeElementId2& Id, const TSharedRef<const FNavigationElement>& ElementRef, const FBox& Bounds, FNavigationOctreeElement& Data);` — Append new data to existing node
- L192 _public prototype_ `void UpdateNode(const FOctreeElementId2& Id, const FBox& NewBounds);` — Updates element bounds remove/add operation
- L195 _public prototype_ `void RemoveNode(const FOctreeElementId2& Id);` — Remove node
- L197 _public prototype_ `void SetNavigableGeometryStoringMode(ENavGeometryStoringMode NavGeometryMode);`
- L199 _public prototype_ `const FNavigationRelevantData* GetDataForID(const FOctreeElementId2& Id) const;`
- L201 _public prototype_ `FNavigationRelevantData* GetMutableDataForID(const FOctreeElementId2& Id);`
- L203 _public function_ `ENavGeometryStoringMode GetNavGeometryStoringMode() const`
- L208 _public prototype_ `void SetDataGatheringMode(ENavDataGatheringModeConfig Mode);`
- L211 _public prototype_ `bool IsLazyGathering(const FNavigationElement& NavigationElement) const;` — Lazy data gathering methods
- L213 _public prototype_ `void DemandLazyDataGathering(FNavigationRelevantData& ElementData);`
- L215 _public prototype_ `void DemandChildLazyDataGathering(FNavigationRelevantData& ElementData, const FNavigationElement& ChildElement) const;`
- L218 _public prototype_ `void SetGatheringNavModifiersTimeLimitWarning(const float Threshold);`
- L224 _protected prototype_ `void SetElementIdImpl(FNavigationElementHandle ElementHandle, FOctreeElementId2 Id);`
- L226 _protected member_ `TMap<FNavigationElementHandle, FOctreeElementId2> ElementToOctreeId;`
- L227 _protected member_ `ENavDataGatheringMode DefaultGeometryGatheringMode;`
- L228 _protected member_ `uint32 bGatherGeometry : 1;`
- L229 _protected member_ `uint32 NodesMemory;`
- L231 _protected member_ `float GatheringNavModifiersTimeLimitWarning;`
- L234 _private member_ `SIZE_T OctreeSizeBytes = 0;`

#### enum `FNavigationOctree::ENavGeometryStoringMode`  
`enum ENavGeometryStoringMode`  
_L147-150_
- L148 _public enumerator_ `SkipNavGeometry`
- L149 _public enumerator_ `StoreNavGeometry`

#### Free symbols / members of external scopes

- L18 _typedef_ `typedef FNavigationRelevantDataFilter FNavigationOctreeFilter;`
- L20 _prototype_ `LLM_DECLARE_TAG(NavigationOctree);`
- L114 _enumerator_ `enum { MaxElementsPerLeaf = 16 }; enum { MinInclusiveElementsPerNode = 7 }; enum { MaxNodeDepth = 12 }; typedef TInlineAllocator<MaxElementsPerLeaf> ElementAllocator; FORCEINLINE static const FBoxSphereBounds& GetBoundingBox(const FNavigationOctreeElement& NavData) {` (scope `FNavigationOctreeSemantics::__anon95e7a7430103`)
- L115 _enumerator_ `enum { MinInclusiveElementsPerNode = 7 }; enum { MaxNodeDepth = 12 }; typedef TInlineAllocator<MaxElementsPerLeaf> ElementAllocator; FORCEINLINE static const FBoxSphereBounds& GetBoundingBox(const FNavigationOctreeElement& NavData) { return NavData.Bounds;` (scope `FNavigationOctreeSemantics::__anon95e7a7430203`)
- L116 _enumerator_ `enum { MaxNodeDepth = 12 }; typedef TInlineAllocator<MaxElementsPerLeaf> ElementAllocator; FORCEINLINE static const FBoxSphereBounds& GetBoundingBox(const FNavigationOctreeElement& NavData) { return NavData.Bounds; }` (scope `FNavigationOctreeSemantics::__anon95e7a7430303`)
- L144 _delegate_ `DECLARE_DELEGATE_TwoParams(FGeometryExportDelegate, const FNavigationElement&, FNavigationRelevantData&);`

### `Source/Runtime/NavigationSystem/Public/NavigationOctreeController.h` (Public)


#### struct `FNavigationDirtyElementKeyFunctions`  
`struct FNavigationDirtyElementKeyFunctions : BaseKeyFuncs<FNavigationDirtyElement, FNavigationElementHandle, false>`  
_L8-24_
- inherits: `BaseKeyFuncs<FNavigationDirtyElement,FNavigationElementHandle,false>`
- L10 _public function_ `static FNavigationElementHandle GetSetKey(ElementInitType Element)`
- L15 _public function_ `static bool Matches(KeyInitType A, KeyInitType B)`
- L20 _public function_ `static uint32 GetKeyHash(KeyInitType Key)`

#### struct `FNavigationOctreeController`  
`struct FNavigationOctreeController`  
_L26-86_
- L37 _public member_ `TSet<FNavigationDirtyElement, FNavigationDirtyElementKeyFunctions> PendingUpdates;`
- L38 _public member_ `TSharedPtr<FNavigationOctree, ESPMode::ThreadSafe> NavOctree;`
- L41 _public member_ `uint8 bNavOctreeLock : 1 = false;` — if set, navoctree updates are ignored, use with caution!
- L43 _public prototype_ `inline void SetNavigationOctreeLock(bool bLock);`
- L45 _public prototype_ `bool HasPendingUpdateForElement(FNavigationElementHandle Element) const;`
- L47 _public prototype_ `inline void RemoveNode(FOctreeElementId2 ElementId, FNavigationElementHandle GetHandle);`
- L49 _public prototype_ `void SetNavigableGeometryStoringMode(FNavigationOctree::ENavGeometryStoringMode NavGeometryMode);`
- L51 _public prototype_ `void Reset();`
- L53 _public prototype_ `inline const FNavigationOctree* GetOctree() const;`
- L54 _public prototype_ `inline FNavigationOctree* GetMutableOctree();`
- L56 _public prototype_ `inline const FOctreeElementId2* GetNavOctreeIdForElement(FNavigationElementHandle Element) const;`
- L58 _public prototype_ `bool GetNavOctreeElementData(FNavigationElementHandle Element, ENavigationDirtyFlag& DirtyFlags, FBox& DirtyBounds);`
- L60 _public prototype_ `const FNavigationRelevantData* GetDataForElement(FNavigationElementHandle Element) const;`
- L62 _public prototype_ `FNavigationRelevantData* GetMutableDataForElement(FNavigationElementHandle Element);`
- L64 _public prototype_ `inline bool HasElementNavOctreeId(const FNavigationElementHandle Element) const;`
- L66 _public prototype_ `inline bool IsNavigationOctreeLocked() const;`
- L69 _public function_ `bool IsValid() const` — basically says if navoctree has been created already
- L71 _public prototype_ `inline bool IsValidElement(const FOctreeElementId2* ElementId) const;`
- L72 _public prototype_ `inline bool IsValidElement(const FOctreeElementId2& ElementId) const;`
- L74 _public function_ `bool IsEmpty() const`
- L79 _public prototype_ `inline void AddChild(FNavigationElementHandle Parent, const TSharedRef<const FNavigationElement>& Child);`
- L80 _public prototype_ `inline void RemoveChild(FNavigationElementHandle Parent, const TSharedRef<const FNavigationElement>& Child);`
- L81 _public prototype_ `inline void GetChildren(FNavigationElementHandle Parent, TArray<const TSharedRef<const FNavigationElement>>& OutChildren) const;`
- L85 _private member_ `TMultiMap<FNavigationElementHandle, const TSharedRef<const FNavigationElement>> OctreeParentChildNodesMap;` — Map of all elements that are tied to indexed navigation parent
- L92 _function_ `inline const FOctreeElementId2* FNavigationOctreeController::GetNavOctreeIdForElement(const FNavigationElementHandle Element) const`
- L99 _function_ `inline bool FNavigationOctreeController::HasElementNavOctreeId(const FNavigationElementHandle Element) const`
- L104 _function_ `inline void FNavigationOctreeController::RemoveNode(const FOctreeElementId2 ElementId, const FNavigationElementHandle ElementHandle)`
- L113 _function_ `inline const FNavigationOctree* FNavigationOctreeController::GetOctree() const`
- L118 _function_ `inline FNavigationOctree* FNavigationOctreeController::GetMutableOctree()`
- L123 _function_ `inline bool FNavigationOctreeController::IsNavigationOctreeLocked() const`
- L128 _function_ `inline void FNavigationOctreeController::SetNavigationOctreeLock(bool bLock)`
- L133 _function_ `inline bool FNavigationOctreeController::IsValidElement(const FOctreeElementId2* ElementId) const`
- L138 _function_ `inline bool FNavigationOctreeController::IsValidElement(const FOctreeElementId2& ElementId) const`
- L143 _function_ `void FNavigationOctreeController::AddChild(const FNavigationElementHandle Parent, const TSharedRef<const FNavigationElement>& Child)`
- L148 _function_ `void FNavigationOctreeController::RemoveChild(const FNavigationElementHandle Parent, const TSharedRef<const FNavigationElement>& Child)`
- L163 _function_ `void FNavigationOctreeController::GetChildren(const FNavigationElementHandle Parent, TArray<const TSharedRef<const FNavigationElement>>& OutChildren) const`

#### enum `FNavigationOctreeController::EOctreeUpdateMode`  
`enum EOctreeUpdateMode`  
_L28-35_
- L30 _public enumerator_ `OctreeUpdate_Default = 0` — regular update, mark dirty areas depending on exported content
- L31 _public enumerator_ `OctreeUpdate_Geometry = 1` — full update, mark dirty areas for geometry rebuild
- L32 _public enumerator_ `OctreeUpdate_Modifiers = 2` — quick update, mark dirty areas for modifier rebuild
- L33 _public enumerator_ `OctreeUpdate_Refresh = 4` — update is used for refresh, don't invalidate pending queue
- L34 _public enumerator_ `OctreeUpdate_ParentChain = 8` — update child nodes, don't remove anything

### `Source/Runtime/NavigationSystem/Public/NavigationPath.h` (Public)


#### class `UNavigationPath`  
`class UNavigationPath : public UObject`  
_L21-90_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UObject`
- L26 _private member_ `FOnNavigationPathUpdated PathUpdatedNotifier;` — `UPROPERTY(BlueprintAssignable)`
- L29 _private member_ `TArray<FVector> PathPoints;` — `UPROPERTY(BlueprintReadOnly, Category = Navigation)`
- L32 _private member_ `ENavigationOptionFlag RecalculateOnInvalidation = ENavigationOptionFlag::Default;` — `UPROPERTY(BlueprintReadOnly, Category = Navigation)`
- L35 _private member_ `uint32 bIsValid : 1;`
- L36 _private member_ `uint32 bDebugDrawingEnabled : 1;`
- L37 _private member_ `FColor DebugDrawingColor;`
- L39 _private member_ `FDelegateHandle DrawDebugDelegateHandle;`
- L42 _protected member_ `FNavPathSharedPtr SharedPath;`
- L44 _protected member_ `FNavigationPath::FPathObserverDelegate::FDelegate PathObserver;`
- L45 _protected member_ `FDelegateHandle PathObserverDelegateHandle;`
- L50 _public prototype_ `virtual void BeginDestroy() override;` — UObject begin
- L54 _public prototype_ `FString GetDebugString() const;` — `UFUNCTION(BlueprintCallable, Category = "AI|Debug")`
- L57 _public prototype_ `void EnableDebugDrawing(bool bShouldDrawDebugData, FLinearColor PathColor = FLinearColor::White);` — `UFUNCTION(BlueprintCallable, Category = "AI|Debug")`
- L61 _public prototype_ `void EnableRecalculationOnInvalidation(ENavigationOptionFlag DoRecalculation);` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation")` — if enabled path will request recalculation if it gets invalidated due to a change to underlying navigation
- L64 _public prototype_ `double GetPathLength() const;` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation")`
- L68 _public prototype_ `double GetLengthFromPosition(FVector Position, int32 NextPathPointIndex) const;` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation")` — returns the remaining length of the path from Position, including the distance from Position to the NextPathPoint
- L71 _public prototype_ `double GetPathCost() const;` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation")`
- L74 _public prototype_ `bool IsPartial() const;` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation")`
- L77 _public prototype_ `bool IsValid() const;` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation")`
- L80 _public prototype_ `bool IsStringPulled() const;` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation")`
- L82 _public prototype_ `void SetPath(FNavPathSharedPtr NewSharedPath);`
- L83 _public function_ `FNavPathSharedPtr GetPath()`
- L86 _protected prototype_ `void DrawDebug(UCanvas* Canvas, APlayerController*);`
- L87 _protected prototype_ `void OnPathEvent(FNavigationPath* Path, ENavPathEvent::Type PathEvent);`
- L89 _protected prototype_ `void SetPathPointsFromPath(FNavigationPath& NativePath);`

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNavigationPathUpdated, UNavigationPath*, AffectedPath, TEnumAsByte<ENavPathEvent::Type>, PathEvent);`
- L14 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNavigationPathUpdated, UNavigationPath*, AffectedPath, TEnumAsByte<ENavPathEvent::Type>, PathEvent);`

### `Source/Runtime/NavigationSystem/Public/NavigationPathGenerator.h` (Public)


#### class `UNavigationPathGenerator`  
`class UNavigationPathGenerator : public UInterface`  
_L11-14_
- reflection: `UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `INavigationPathGenerator`  
`class INavigationPathGenerator`  
_L16-25_
- L24 _private prototype_ `virtual FNavPathSharedPtr GetGeneratedPath(class INavAgentInterface* Agent) PURE_VIRTUAL(INavigationPathGenerator::GetGeneratedPath, return FNavPathSharedPtr(NULL););` — Retrieved path generated for specified navigation Agent

### `Source/Runtime/NavigationSystem/Public/NavigationSystem.h` (Public)


#### struct `FNavigationSystem::FCustomLinkOwnerInfo`  
`struct FCustomLinkOwnerInfo`  
_L74-83_
- L76 _public member_ `FWeakObjectPtr LinkOwner;`
- L77 _public member_ `INavLinkCustomInterface* LinkInterface;`
- L79 _public function_ `FCustomLinkOwnerInfo() : LinkInterface(nullptr)`
- L80 _public prototype_ `FCustomLinkOwnerInfo(INavLinkCustomInterface* Link);`
- L82 _public function_ `bool IsValid() const`

#### struct `FNavigationSystemExec`  
`struct FNavigationSystemExec: public FSelfRegisteringExec`  
_L94-100_
- inherits: `FSelfRegisteringExec`
- L98 _protected prototype_ `virtual bool Exec_Runtime(UWorld* Inworld, const TCHAR* Cmd, FOutputDevice& Ar) override;`

#### enum `ENavigationBuildLock::Type`  
`enum Type`  
_L104-111_
- L106 _public enumerator_ `NoUpdateInEditor = 1 << 1` — editor doesn't allow automatic updates
- L107 _public enumerator_ `NoUpdateInPIE = 1 << 2` — PIE doesn't allow automatic updates
- L108 _public enumerator_ `InitialLock = 1 << 3` — initial lock, release manually after levels are ready for rebuild (e.g. streaming)
- L109 _public enumerator_ `Custom = 1 << 4`
- L110 _public enumerator_ `AsyncLoadLock = 1 << 5` — used in editor worlds to prevent automatic update when loading a map using async loading

#### class `FNavRegenTimeSlicer`  
`class FNavRegenTimeSlicer`  
_L124-184_
- L128 _public prototype_ `void SetupTimeSlice(double SliceDuration);` — Setup the initial values for a time slice. This can be called on an instance after TestTimeSliceFinished() has returned true and EndTimeSliceAndAdjustDuration() has been called
- L134 _public prototype_ `void StartTimeSlice();` — Starts the time slice, this can be called multiple times as long as EndTimeSliceAndAdjustDuration() is called between each call. StartTimeSlice should not be called after TestTimeSliceFinished() has returned true
- L143 _public prototype_ `void EndTimeSliceAndAdjustDuration();` — Useful when multiple sections of code need to be timesliced per frame using the same time slice duration that do not necessarily occur concurrently. This ends the time sliced code section and adjusts the RemainingDuration based on the time used between calls to StartTimeSlice and the last call to TestTimeSliceFinished. Note the actual time slice is not tested in this function. Thats done in TestTimeSliceFinished! This can be called multiple times as long as StartTimeSlice() is called before EndTimeSliceAndAdjustDuration(). EndTimeSliceAndAdjustDuration can be called after TestTimeSliceFinished() has returned true in this case the RemainingDuration will just be zero
- L144 _public function_ `double GetStartTime() const`
- L145 _public prototype_ `bool TestTimeSliceFinished() const;`
- L148 _public function_ `bool IsTimeSliceFinishedCached() const` — /  Returns the cached result of calling TestTimeSliceFinished, false by default
- L149 _public function_ `double GetRemainingDuration() const`
- L150 _public function_ `double GetRemainingDurationFraction() const`
- L159 _public prototype_ `void DebugSetLongTimeSliceData(TFunction<void(FName, double)> LongTimeSliceFunction, double LongTimeSliceDuration) const;` — Sets data used for debugging time slices that are taking too long to process. @param LongTimeSliceFunction function called when a time slice is taking too long to process. @param LongTimeSliceDuration when a time slice takes longer than this duration LongTimeSliceFunction will be called.
- L160 _public prototype_ `void DebugResetLongTimeSliceFunction() const;`
- L166 _public function_ `void DebugSetSectionName(FName InDebugSectionName) const` — Sets the debug name for a time sliced section of code. Do not call this directly use MARK_TIMESLICE_SECTION_DEBUG
- L173 _protected member_ `double OriginalDuration = 0.;`
- L174 _protected member_ `double RemainingDuration = 0.;`
- L175 _protected member_ `double StartTime = 0.;`
- L176 _protected member_ `mutable double TimeLastTested = 0.;`
- L177 _protected member_ `mutable bool bTimeSliceFinishedCached = false;`
- L180 _protected member_ `mutable TFunction<void(FName, double)> DebugLongTimeSliceFunction;`
- L181 _protected member_ `mutable double DebugLongTimeSliceDuration = 0.;`
- L182 _protected member_ `mutable FName DebugSectionName = FNavigationSystem::DebugTimeSliceDefaultSectionName;`

#### struct `FTileHistoryData`  
`struct FTileHistoryData`  
_L187-204_
- L190 _public member_ `int32 TileX = 0;` — Tile coordinates
- L191 _public member_ `int32 TileY = 0;`
- L194 _public member_ `float TileRegenTime = 0.f;` — Accumulated time spent processing the tile (seconds).
- L197 _public member_ `float TileWaitTime = 0.f;` — Time between the tile was requested and when it's finished building (seconds).
- L200 _public member_ `int64 StartRegenFrame = 0;` — Frame when tile processing started.
- L203 _public member_ `int64 EndRegenFrame = 0;` — Frame when tile processing ended.

#### class `FNavRegenTimeSliceManager`  
`class FNavRegenTimeSliceManager`  
_L207-288_
- L210 _public prototype_ `FNavRegenTimeSliceManager();`
- L212 _public function_ `void PushTileRegenTime(double NewTime)`
- L214 _public function_ `double GetAverageTileRegenTime() const`
- L216 _public function_ `double GetAverageDeltaTime() const`
- L218 _public prototype_ `void ResetTileWaitTimeArrays(const TArray<TObjectPtr<ANavigationData>>& NavDataSet);`
- L219 _public prototype_ `void PushTileWaitTime(const int32 NavDataIndex, const double NewTime);`
- L222 _public prototype_ `void ResetTileHistoryData(const TArray<TObjectPtr<ANavigationData>>& NavDataSet);`
- L223 _public prototype_ `void PushTileHistoryData(const int32 NavDataIndex, const FTileHistoryData& TileData);`
- L226 _public prototype_ `double GetAverageTileWaitTime(const int32 NavDataIndex) const;`
- L227 _public prototype_ `void ResetTileWaitTime(const int32 NavDataIndex);`
- L229 _public function_ `bool DoTimeSlicedUpdate() const`
- L231 _public prototype_ `void CalcAverageDeltaTime(uint64 FrameNum);`
- L233 _public prototype_ `void CalcTimeSliceDuration(const TArray<TObjectPtr<ANavigationData>>& NavDataSet, int32 NumTilesToRegen, const TArray<double>& CurrentTileRegenDurations);`
- L235 _public prototype_ `void SetMinTimeSliceDuration(double NewMinTimeSliceDuration);`
- L237 _public prototype_ `void SetMaxTimeSliceDuration(double NewMaxTimeSliceDuration);`
- L239 _public prototype_ `void SetMaxDesiredTileRegenDuration(float NewMaxDesiredTileRegenDuration);`
- L241 _public function_ `int32 GetNavDataIdx() const`
- L242 _public function_ `void SetNavDataIdx(int32 InNavDataIdx)`
- L244 _public function_ `FNavRegenTimeSlicer& GetTimeSlicer()`
- L245 _public function_ `const FNavRegenTimeSlicer& GetTimeSlicer() const`
- L248 _public prototype_ `void LogTileStatistics(const TArray<TObjectPtr<ANavigationData>>& NavDataSet) const;`
- L252 _protected member_ `FNavRegenTimeSlicer TimeSlicer;`
- L255 _protected member_ `FMovingWindowAverageFast<double, 256> MovingWindowTileRegenTime;` — Used to calculate the moving window average of the actual time spent inside functions used to regenerate a tile, this is processing time not actual time over multiple frames
- L258 _protected member_ `FMovingWindowAverageFast<double, 256> MovingWindowDeltaTime;` — Used to calculate the actual moving window delta time
- L261 _protected member_ `TArray<TArray<double>> TileWaitTimes;` — Average tile wait time per NavDataIndex
- L265 _protected member_ `TArray<TArray<FTileHistoryData>> TileHistoryData;` — Tile processing time per NavDataIndex
- L266 _protected member_ `double TileHistoryStartTime = 0;`
- L270 _protected member_ `double MinTimeSliceDuration;` — If there are enough tiles to process this in the Min Time Slice Duration
- L273 _protected member_ `double MaxTimeSliceDuration;` — The max Desired Time Slice Duration
- L275 _protected member_ `uint64 FrameNumOld;`
- L281 _protected member_ `float MaxDesiredTileRegenDuration;` — The max real world desired time to Regen all the tiles in PendingDirtyTiles, Note it could take longer than this, as the time slice is clamped per frame between MinTimeSliceDuration and MaxTimeSliceDuration.
- L283 _protected member_ `double TimeLastCall;`
- L285 _protected member_ `int32 NavDataIdx;`
- L287 _protected member_ `bool bDoTimeSlicedUpdate;`

#### class `UNavigationSystemV1`  
`class UNavigationSystemV1 : public UNavigationSystemBase`  
_L291-1486_
- reflection: `UCLASS(Within=World, config=Engine, defaultconfig, MinimalAPI)`
- inherits: `UNavigationSystemBase`
- L298 _public prototype_ `UNavigationSystemV1(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L299 _public prototype_ `virtual ~UNavigationSystemV1() = default;`
- L301 _public prototype_ `void GatherDebugLabels(TArray<FString>& InOutDebugLabels) const;`
- L304 _public member_ `TObjectPtr<ANavigationData> MainNavData;` — `UPROPERTY(Transient)`
- L308 _public member_ `TObjectPtr<ANavigationData> AbstractNavData;` — `UPROPERTY(Transient)` — special navigation data for managing direct paths, not part of NavDataSet!
- L316 _protected member_ `FName DefaultAgentName;` — `UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = Navigation)` — If not None indicates which of navigation datas and supported agents are going to be used as the default ones. If navigation agent of this type does not exist or is not enabled then the first available nav data will be used as the default one
- L319 _protected member_ `TSoftClassPtr<UCrowdManagerBase> CrowdManagerClass;` — `UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = Navigation)`
- L323 _protected member_ `uint32 bAutoCreateNavigationData:1;` — `UPROPERTY(config, EditAnywhere, Category=NavigationSystem)` — Should navigation system spawn default Navigation Data when there's none and there are navigation bounds present?
- L327 _protected member_ `uint32 bSpawnNavDataInNavBoundsLevel:1;` — `UPROPERTY(config, EditAnywhere, Category = NavigationSystem)` — If true will try to spawn the navigation data instance in the sublevel with navigation bounds, if false it will spawn in the persistent level
- L331 _protected member_ `uint32 bAllowClientSideNavigation:1;` — `UPROPERTY(config, EditAnywhere, Category=NavigationSystem)` — If false, will not create nav collision when connecting as a client
- L335 _protected member_ `uint32 bShouldDiscardSubLevelNavData:1;` — `UPROPERTY(config, EditAnywhere, Category = NavigationSystem)` — If true, games should ignore navigation data inside loaded sublevels
- L339 _protected member_ `uint32 bTickWhilePaused:1;` — `UPROPERTY(config, EditAnywhere, Category=NavigationSystem)` — If true, will update navigation even when the game is paused
- L345 _protected member_ `uint32 bSupportRebuilding : 1;` — `UPROPERTY()` — gets set to true if gathering navigation data (like in navoctree) is required due to the need of navigation generation Is always true in Editor Mode. In other modes it depends on bRebuildAtRuntime of every required NavigationData class' CDO
- L348 _protected member_ `uint32 bDirtyNavDataPackageOnNavigationGenerationFinished : 1;` — `UPROPERTY()`
- L353 _protected member_ `uint32 bWaitForAsyncLoadingBeforeBuildingNavigationAutomatically : 1 = true;` — `UPROPERTY(config, EditAnywhere, Category=NavigationSystem)` — In editor worlds, wait for async loading to finish before allowing to build navigation automatically (true by default).
- L362 _public member_ `uint32 bInitialBuildingLocked:1;` — `UPROPERTY(config, EditAnywhere, Category=NavigationSystem)` — if set to true will result navigation system not rebuild navigation until a call to ReleaseInitialBuildingLock() is called. Does not influence editor-time generation (i.e. does influence PIE and Game). Defaults to false.
- L371 _public member_ `uint32 bWholeWorldNavigable:1;` — `UPROPERTY(config, EditAnywhere, Category=NavigationSystem)` — @todo removing it from edition since it's currently broken and I'm not sure we want that at all since I'm not sure we can make it efficient in a generic case
- L376 _public member_ `uint32 bSkipAgentHeightCheckWhenPickingNavData:1;` — `UPROPERTY(config, EditAnywhere, Category=NavigationSystem)` — false by default, if set to true will result in not caring about nav agent height when trying to match navigation data to passed in nav agent
- L381 _public member_ `int32 GeometryExportTriangleCountWarningThreshold = 200000;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category = NavigationSystem)` — Warnings are logged if exporting the navigation collision for an object exceed this triangle count. Use -1 to disable.
- L391 _protected member_ `uint32 bGenerateNavigationOnlyAroundNavigationInvokers:1;` — `UPROPERTY(EditDefaultsOnly, Category = "Navigation Enforcing", config)` — If set to true navigation will be generated only around registered "navigation enforcers" This has a range of consequences (including how navigation octree operates) so it needs to be a conscious decision. Once enabled results in whole world being navigable. @see RegisterNavigationInvoker
- L395 _protected member_ `float ActiveTilesUpdateInterval;` — `UPROPERTY(EditAnywhere, Category = "Navigation Enforcing", meta = (ClampMin = "0.1", UIMin = "0.1", EditCondition = "bGenerateNavigationOnlyAroundNavigationInvokers"), config)` — Minimal time, in seconds, between active tiles set update
- L399 _protected member_ `double InvokersMaximumDistanceFromSeed = -1;` — `UPROPERTY(EditAnywhere, Category = "Navigation Enforcing", meta = (EditCondition = "bGenerateNavigationOnlyAroundNavigationInvokers"), config)` — When in use, invokers farther away from any invoker seed will be ignored (set to -1 to disable).
- L403 _protected member_ `ENavDataGatheringModeConfig DataGatheringMode;` — `UPROPERTY(EditDefaultsOnly, Category = "NavigationSystem", config)` — Sets how navigation data should be gathered when building collision information
- L407 _protected member_ `float DirtyAreaWarningSizeThreshold;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category = NavigationSystem, meta = (ClampMin = "-1.0", UIMin = "-1.0"))` — -1 by default, if set to a positive value dirty areas with any dimensions in 2d over the threshold created at runtime will be logged
- L414 _protected member_ `float GatheringNavModifiersWarningLimitTime;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category = NavigationSystem, meta = (ClampMin = "-1.0", UIMin = "-1.0"))` — -1.0f by default, if set to a positive value, all calls to GetNavigationData will be timed and compared to it. Over the limit calls will be logged as warnings. In seconds. Non-shipping build only.
- L418 _protected member_ `TArray<FNavDataConfig> SupportedAgents;` — `UPROPERTY(config, EditAnywhere, Category = Agents)` — List of agents types supported by this navigation system
- L424 _protected member_ `FNavAgentSelector SupportedAgentsMask;` — `UPROPERTY(config, EditAnywhere, Category = Agents)` — NavigationSystem's properties in Project Settings define all possible supported agents, but a specific navigation system can choose to support only a subset of agents. Set via NavigationSystemConfig
- L429 _public member_ `FBox BuildBounds;` — `UPROPERTY(Transient)` — Bounds of tiles to be built
- L432 _public member_ `TArray<TObjectPtr<ANavigationData>> NavDataSet;` — `UPROPERTY(Transient)`
- L435 _public member_ `TArray<TObjectPtr<ANavigationData>> NavDataRegistrationQueue;` — `UPROPERTY(Transient)`
- L438 _public member_ `TArray<FNavigationBoundsUpdateRequest> PendingNavBoundsUpdates;` — List of pending navigation bounds update requests (add, remove, update size)
- L441 _public member_ `FOnNavDataGenericEvent OnNavDataRegisteredEvent;` — `UPROPERTY(/*BlueprintAssignable, */Transient)`
- L444 _public member_ `FOnNavDataGenericEvent OnNavigationGenerationFinishedDelegate;` — `UPROPERTY(BlueprintAssignable, Transient, meta = (displayname = OnNavigationGenerationFinished))`
- L446 _public member_ `FOnNavigationInitDone OnNavigationInitDone;`
- L449 _private member_ `TWeakObjectPtr<UCrowdManagerBase> CrowdManager;`
- L452 _private member_ `uint32 bNavDataRemovedDueToMissingNavBounds : 1;` — set to true when navigation processing was blocked due to missing nav bounds
- L456 _protected member_ `TSet<FNavigationBounds> RegisteredNavBounds;` — All areas where we build/have navigation
- L459 _private member_ `TMap<UObject*, FNavigationInvoker> Invokers;`
- L461 _private member_ `TArray<FNavigationInvokerRaw> InvokerLocations;` — Contains pre-digested and cached invokers' info. Generated by UpdateInvokers
- L463 _private member_ `TArray<FBox> InvokersSeedBounds;`
- L465 _private member_ `double NextInvokersUpdateTime;`
- L466 _private prototype_ `void UpdateInvokers();`
- L470 _public prototype_ `void DebugLogInvokers(FOutputDevice& OutputDevice) const;`
- L474 _protected prototype_ `virtual void UpdateNavDataActiveTiles();`
- L477 _private prototype_ `void DirtyTilesInBuildBounds();`
- L479 _private prototype_ `void UnregisterInvoker_Internal(const UObject& Invoker);`
- L482 _private prototype_ `void RegisterToRepositoryDelegates();` — Registers to the navigation objects repository subsystem delegates to get notified on object registration
- L485 _private prototype_ `void UnregisterFromRepositoryDelegates() const;` — Unregisters from the navigation objects repository subsystem delegates
- L488 _private prototype_ `void UpdateDelayedUnlockeRegistration(const TArray<FAssetCompileData>& AssetCompileData);`
- L489 _private prototype_ `void RegisterDelayedUnlock(float DelayInSeconds);`
- L490 _private prototype_ `void UnregisterDelayedUnlock();`
- L492 _private member_ `FDelegateHandle OnAssetPostCompileEventHandle;`
- L493 _private member_ `FTSTicker::FDelegateHandle DelayedUnlockHandle;`
- L502 _public prototype_ `static UNavigationSystemV1* GetNavigationSystem(UObject* WorldContextObject);` — `UFUNCTION(BlueprintPure, Category = "AI|Navigation", meta = (WorldContext = "WorldContextObject"))`
- L506 _public prototype_ `static bool K2_ProjectPointToNavigation(UObject* WorldContextObject, const FVector& Point, FVector& ProjectedLocation, ANavigationData* NavData, TSubclassOf<UNavigationQueryFilter> FilterClass, const FVector QueryExtent = FVector::ZeroVector);` — `UFUNCTION(BlueprintPure, Category = "AI|Navigation", meta = (WorldContext = "WorldContextObject", DisplayName = "Project Point to Navigation", ScriptName = "ProjectPointToNavigation"))` — Project a point onto the NavigationData
- L511 _public prototype_ `static bool K2_GetRandomReachablePointInRadius(UObject* WorldContextObject, const FVector& Origin, FVector& RandomLocation, float Radius, ANavigationData* NavData = NULL, TSubclassOf<UNavigationQueryFilter> FilterClass = {});` — `UFUNCTION(BlueprintPure, Category = "AI|Navigation", meta = (WorldContext = "WorldContextObject", DisplayName = "Get Random Reachable Point in Radius", ScriptName = "GetRandomReachablePointInRadius"))` — Generates a random location reachable from given Origin location. @return Return Value represents if the call was successful
- L516 _public prototype_ `static bool K2_GetRandomLocationInNavigableRadius(UObject* WorldContextObject, const FVector& Origin, FVector& RandomLocation, float Radius, ANavigationData* NavData = NULL, TSubclassOf<UNavigationQueryFilter> FilterClass = {});` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation", meta = (WorldContext = "WorldContextObject", DisplayName = "Get Random Location in Navigable Radius", ScriptName = "GetRandomLocationInNavigableRadius"))` — Generates a random location in navigable space within given radius of Origin. @return Return Value represents if the call was successful
- L520 _public prototype_ `static ENavigationQueryResult::Type GetPathCost(UObject* WorldContextObject, const FVector& PathStart, const FVector& PathEnd, double& PathCost, ANavigationData* NavData = NULL, TSubclassOf<UNavigationQueryFilter> FilterClass = {});` — `UFUNCTION(BlueprintPure, Category = "AI|Navigation", meta = (WorldContext = "WorldContextObject"))` — Potentially expensive. Use with caution. Consider using UPathFollowingComponent::GetRemainingPathCost instead
- L524 _public prototype_ `static ENavigationQueryResult::Type GetPathLength(UObject* WorldContextObject, const FVector& PathStart, const FVector& PathEnd, double& PathLength, ANavigationData* NavData = NULL, TSubclassOf<UNavigationQueryFilter> FilterClass = {});` — `UFUNCTION(BlueprintPure, Category = "AI|Navigation", meta = (WorldContext = "WorldContextObject"))` — Potentially expensive. Use with caution
- L527 _public prototype_ `static bool IsNavigationBeingBuilt(UObject* WorldContextObject);` — `UFUNCTION(BlueprintPure, Category="AI|Navigation", meta=(WorldContext="WorldContextObject" ))`
- L530 _public prototype_ `static bool IsNavigationBeingBuiltOrLocked(UObject* WorldContextObject);` — `UFUNCTION(BlueprintPure, Category = "AI|Navigation", meta = (WorldContext = "WorldContextObject"))`
- L535 _public prototype_ `static UNavigationPath* FindPathToLocationSynchronously(UObject* WorldContextObject, const FVector& PathStart, const FVector& PathEnd, AActor* PathfindingContext = NULL, TSubclassOf<UNavigationQueryFilter> FilterClass = {});` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation", meta = (WorldContext="WorldContextObject"))` — Finds path instantly, in a FindPath Synchronously. @param PathfindingContext could be one of following: NavigationData (like Navmesh actor), Pawn or Controller. This parameter determines parameters of specific pathfinding query
- L541 _public prototype_ `static UNavigationPath* FindPathToActorSynchronously(UObject* WorldContextObject, const FVector& PathStart, AActor* GoalActor, float TetherDistance = 50.f, AActor* PathfindingContext = NULL, TSubclassOf<UNavigationQueryFilter> FilterClass = {});` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation", meta = (WorldContext="WorldContextObject"))` — Finds path instantly, in a FindPath Synchronously. Main advantage over FindPathToLocationSynchronously is that the resulting path will automatically get updated if goal actor moves more than TetherDistance away from last path node @param PathfindingContext could be one of following: NavigationData (like Navmesh actor), Pawn or Controller. This parameter determines parameters of specific pathfinding query
- L548 _public prototype_ `static bool NavigationRaycast(UObject* WorldContextObject, const FVector& RayStart, const FVector& RayEnd, FVector& HitLocation, TSubclassOf<UNavigationQueryFilter> FilterClass = {}, AController* Querier = NULL);` — `UFUNCTION(BlueprintCallable, Category="AI|Navigation", meta=(WorldContext="WorldContextObject" ))` — Performs navigation raycast on NavigationData appropriate for given Querier. @param Querier if not passed default navigation data will be used @param HitLocation if line was obstructed this will be set to hit location. Otherwise it contains SegmentEnd @return true if line from RayStart to RayEnd was obstructed. Also, true when no navigation data present
- L555 _public prototype_ `static bool NavigationRaycastWithAdditionalResults(UObject* WorldContextObject, const FVector& RayStart, const FVector& RayEnd, FVector& HitLocation, FNavigationRaycastAdditionalResults* AdditionalResults, TSubclassOf<UNavigationQueryFilter> FilterClass = {}, AController* Querier = NULL);` — Performs navigation raycast on NavigationData appropriate for given Querier. @param Querier if not passed default navigation data will be used @param HitLocation if line was obstructed this will be set to hit location. Otherwise it contains SegmentEnd @param AdditionalResults contains more information about the result of the raycast query. See FNavigationRaycastAdditionalResults description for details @return true if line from RayStart to RayEnd was obstructed. Also, true when no navigation data present
- L560 _public prototype_ `void SetMaxSimultaneousTileGenerationJobsCount(int32 MaxNumberOfJobs);` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation")` — will limit the number of simultaneously running navmesh tile generation jobs to specified number. @param MaxNumberOfJobs gets trimmed to be at least 1. You cannot use this function to pause navmesh generation
- L564 _public prototype_ `void ResetMaxSimultaneousTileGenerationJobsCount();` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation")` — Brings limit of simultaneous navmesh tile generation jobs back to Project Setting's default value
- L572 _public prototype_ `void RegisterNavigationInvoker(AActor* Invoker, float TileGenerationRadius = 3000, float TileRemovalRadius = 5000);` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation")` — Registers given actor as a "navigation enforcer" which means navigation system will make sure navigation is being generated in specified radius around it. @note: you need NavigationSystem's GenerateNavigationOnlyAroundNavigationInvokers to be set to true to take advantage of this feature
- L577 _public prototype_ `void UnregisterNavigationInvoker(AActor* Invoker);` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation")` — Removes given actor from the list of active navigation enforcers. @see RegisterNavigationInvoker for more details
- L580 _public prototype_ `void SetGeometryGatheringMode(ENavDataGatheringModeConfig NewMode);` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation|Generation")`
- L583 _public prototype_ `bool K2_ReplaceAreaInOctreeData(const UObject* Object, TSubclassOf<UNavArea> OldArea, TSubclassOf<UNavArea> NewArea);` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation", meta=(DisplayName="Replace Area in Octree Data"))`
- L585 _public function_ `inline bool IsActiveTilesGenerationEnabled() const`
- L588 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNavigationDirty, const FBox&);` — delegate type for events that dirty the navigation data ( Params: const FBox& DirtyBounds )
- L590 _public member_ `static FOnNavigationDirty NavigationDirtyEvent;` — called after navigation influencing event takes place
- L613 _public prototype_ `virtual void PostInitProperties() override;`
- L614 _public prototype_ `virtual void FinishDestroy() override;`
- L615 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L617 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L618 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L622 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L624 _public function_ `UWorld* GetWorld() const override`
- L626 _public function_ `UCrowdManagerBase* GetCrowdManager() const`
- L629 _protected prototype_ `void CalcTimeSlicedUpdateData(TArray<double>& OutCurrentTimeSlicedBuildTaskDurations, TArray<bool>& OutIsTimeSlicingArray, bool& bOutAnyNonTimeSlicedGenerators, TArray<int32, TInlineAllocator<8>>& OutNumTimeSlicedRemainingBuildTasksArray);`
- L632 _protected prototype_ `virtual void CreateCrowdManager();` — spawn new crowd manager
- L637 _protected prototype_ `void SetSupportedAgentsNavigationClass(int32 AgentIndex, TSubclassOf<ANavigationData> NavigationDataClass);` — Used to properly set navigation class for indicated agent and propagate information to other places (like project settings) that may need this information
- L650 _public prototype_ `FPathFindingResult FindPathSync(const FNavAgentProperties& AgentProperties, FPathFindingQuery Query, EPathFindingMode::Type Mode = EPathFindingMode::Regular);` — Synchronously looks for a path from @fLocation to @EndLocation for agent with properties @AgentProperties. NavData actor appropriate for specified FNavAgentProperties will be found automatically @param ResultPath results are put here @param NavData optional navigation data that will be used instead of the one that would be deducted from AgentProperties @param Mode switch between normal and hierarchical path finding algorithms
- L658 _public prototype_ `FPathFindingResult FindPathSync(FPathFindingQuery Query, EPathFindingMode::Type Mode = EPathFindingMode::Regular);` — Does a simple path finding from @StartLocation to @EndLocation on specified NavData. If none passed MainNavData will be used Result gets placed in ResultPath @param NavData optional navigation data that will be used instead main navigation data @param Mode switch between normal and hierarchical path finding algorithms
- L668 _public prototype_ `uint32 FindPathAsync(const FNavAgentProperties& AgentProperties, FPathFindingQuery Query, const FNavPathQueryDelegate& ResultDelegate, EPathFindingMode::Type Mode = EPathFindingMode::Regular);` — Asynchronously looks for a path from @StartLocation to @EndLocation for agent with properties @AgentProperties. NavData actor appropriate for specified FNavAgentProperties will be found automatically @param AgentProperties optional agent properties used to determine the NavData to use, only when the NavData inside the FPathFindingQuery was left empty. @param ResultDelegate delegate that will be called once query has been processed and finished. Will be called even if query fails - in such case see comments for delegate's params @param Mode switch between normal and hierarchical path finding algorithms @return request ID
- L671 _public prototype_ `void AbortAsyncFindPathRequest(uint32 AsynPathQueryID);` — Removes query indicated by given ID from queue of path finding requests to process.
- L679 _public prototype_ `bool TestPathSync(FPathFindingQuery Query, EPathFindingMode::Type Mode = EPathFindingMode::Regular, int32* NumVisitedNodes = NULL) const;` — Synchronously check if path between two points exists Does not return path object, but will run faster (especially in hierarchical mode) @param Mode switch between normal and hierarchical path finding algorithms. @note Hierarchical mode ignores QueryFilter @return true if path exists
- L685 _public prototype_ `bool GetRandomPoint(FNavLocation& ResultLocation, ANavigationData* NavData = NULL, FSharedConstNavQueryFilter QueryFilter = NULL);` — Finds random point in navigable space @param ResultLocation Found point is put here @param NavData If NavData == NULL then MainNavData is used. @return true if any location found, false otherwise
- L691 _public prototype_ `bool GetRandomReachablePointInRadius(const FVector& Origin, float Radius, FNavLocation& ResultLocation, ANavigationData* NavData = NULL, FSharedConstNavQueryFilter QueryFilter = NULL) const;` — Finds random, reachable point in navigable space restricted to Radius around Origin @param ResultLocation Found point is put here @param NavData If NavData == NULL then MainNavData is used. @return true if any location found, false otherwise
- L697 _public prototype_ `bool GetRandomPointInNavigableRadius(const FVector& Origin, float Radius, FNavLocation& ResultLocation, ANavigationData* NavData = NULL, FSharedConstNavQueryFilter QueryFilter = NULL) const;` — Finds random, point in navigable space restricted to Radius around Origin. Resulting location is not tested for reachability from the Origin @param ResultLocation Found point is put here @param NavData If NavData == NULL then MainNavData is used. @return true if any location found, false otherwise
- L701 _public prototype_ `ENavigationQueryResult::Type GetPathCost(const FVector& PathStart, const FVector& PathEnd, FVector::FReal& PathCost, const ANavigationData* NavData = NULL, FSharedConstNavQueryFilter QueryFilter = NULL) const;` — Calculates a path from PathStart to PathEnd and retrieves its cost. @NOTE potentially expensive, so use it with caution
- L705 _public prototype_ `ENavigationQueryResult::Type GetPathLength(const FVector& PathStart, const FVector& PathEnd, FVector::FReal& PathLength, const ANavigationData* NavData = NULL, FSharedConstNavQueryFilter QueryFilter = NULL) const;` — Calculates a path from PathStart to PathEnd and retrieves its overestimated length. @NOTE potentially expensive, so use it with caution
- L709 _public prototype_ `ENavigationQueryResult::Type GetPathLengthAndCost(const FVector& PathStart, const FVector& PathEnd, FVector::FReal& PathLength, FVector::FReal& PathCost, const ANavigationData* NavData = NULL, FSharedConstNavQueryFilter QueryFilter = NULL) const;` — Calculates a path from PathStart to PathEnd and retrieves its overestimated length and cost. @NOTE potentially expensive, so use it with caution
- L712 _public function_ `bool ProjectPointToNavigation(const FVector& Point, FNavLocation& OutLocation, const FVector& Extent = INVALID_NAVEXTENT, const FNavAgentProperties* AgentProperties = NULL, FSharedConstNavQueryFilter QueryFilter = NULL)` — @todo document
- L718 _public prototype_ `bool ProjectPointToNavigation(const FVector& Point, FNavLocation& OutLocation, const FVector& Extent = INVALID_NAVEXTENT, const ANavigationData* NavData = NULL, FSharedConstNavQueryFilter QueryFilter = NULL) const;` — @todo document
- L723 _public prototype_ `virtual ANavigationData* GetNavDataForProps(const FNavAgentProperties& AgentProperties);` — Looks for NavData generated for specified movement properties and returns it. NULL if not found;
- L728 _public prototype_ `virtual const ANavigationData* GetNavDataForProps(const FNavAgentProperties& AgentProperties) const;` — Looks for NavData generated for specified movement properties and returns it. NULL if not found; Const version.
- L732 _public prototype_ `virtual ANavigationData* GetNavDataForAgentName(const FName AgentName) const;` — Goes through all registered NavigationData instances and retrieves the one supporting agent named AgentName
- L740 _public prototype_ `virtual ANavigationData* GetNavDataForProps(const FNavAgentProperties& AgentProperties, const FVector& AgentLocation, const FVector& Extent = INVALID_NAVEXTENT) const;` — Looks up NavData appropriate for specified movement properties and returns it. NULL if not found; This is the encouraged way of querying for the appropriate NavData. It makes no difference for NavigationSystemV1 (AgentLocation and Extent parameters not being used) but NaV2 will take advantage of it and all engine-level AI navigation code is going to use call this flavor.
- L743 _public prototype_ `ANavigationData* GetDefaultNavDataInstance(FNavigationSystem::ECreateIfMissing CreateNewIfNoneFound);` — Returns the world default navigation data instance. Creates one if it doesn't exist.
- L745 _public function_ `virtual INavigationDataInterface* GetMainNavData() const override` — Returns the world default navigation data instance.
- L746 _public function_ `ANavigationData& GetMainNavDataChecked() const`
- L749 _public prototype_ `virtual void SetBuildBounds(const FBox& Bounds) override;` — Set limiting bounds to be used when building navigation data.
- L751 _public prototype_ `virtual FBox GetNavigableWorldBounds() const override;`
- L753 _public prototype_ `virtual bool ContainsNavData(const FBox& Bounds) const override;`
- L754 _public prototype_ `virtual FBox ComputeNavDataBounds() const override;`
- L755 _public prototype_ `virtual void AddNavigationDataChunk(class ANavigationDataChunkActor& DataChunkActor) override;`
- L756 _public prototype_ `virtual void RemoveNavigationDataChunk(class ANavigationDataChunkActor& DataChunkActor) override;`
- L757 _public prototype_ `virtual void FillNavigationDataChunkActor(const FBox& QueryBounds, class ANavigationDataChunkActor& DataChunkActor, FBox& OutTilesBounds) override;`
- L759 _public function_ `ANavigationData* GetDefaultNavDataInstance() const`
- L761 _public function_ `ANavigationData* GetAbstractNavData() const`
- L767 _public prototype_ `virtual ANavigationData* CreateNavigationDataInstanceInLevel(const FNavDataConfig& NavConfig, ULevel* SpawnLevel);` — constructs a navigation data instance of specified NavDataClass, in passed Level for supplied NavConfig. If Level == null and bSpawnNavDataInNavBoundsLevel == true then the first volume actor in RegisteredNavBounds will be used to source the level. Otherwise the navdata instance will be spawned in NavigationSystem's world
- L769 _public prototype_ `FSharedNavQueryFilter CreateDefaultQueryFilterCopy() const;`
- L773 _public prototype_ `bool ShouldGeneratorRun(const FNavDataGenerator* Generator) const;` — Super-hacky safety feature for threaded navmesh building. Will be gone once figure out why keeping TSharedPointer to Navigation Generator doesn't guarantee its existence
- L775 _public prototype_ `virtual bool IsNavigationBuilt(const AWorldSettings* Settings) const override;`
- L777 _public prototype_ `virtual bool IsThereAnywhereToBuildNavigation() const;`
- L779 _public function_ `bool ShouldGenerateNavigationEverywhere() const`
- L781 _public function_ `bool ShouldAllowClientSideNavigation() const`
- L782 _public function_ `virtual bool ShouldLoadNavigationOnClient(ANavigationData* NavData = nullptr) const`
- L783 _public function_ `virtual bool ShouldDiscardSubLevelNavData(ANavigationData* NavData = nullptr) const`
- L785 _public prototype_ `FBox GetWorldBounds() const;`
- L787 _public prototype_ `FBox GetLevelBounds(ULevel* InLevel) const;`
- L789 _public prototype_ `bool IsNavigationRelevant(const AActor* TestActor) const;`
- L791 _public prototype_ `const TSet<FNavigationBounds>& GetNavigationBounds() const;`
- L793 _public prototype_ `static const FNavDataConfig& GetDefaultSupportedAgent();`
- L794 _public prototype_ `static const FNavDataConfig& GetBiggestSupportedAgent(const UWorld* World);`
- L797 _public prototype_ `static double GetWorldPartitionNavigationDataBuilderOverlap(const UWorld& World);`
- L800 _public prototype_ `const FNavDataConfig& GetDefaultSupportedAgentConfig() const;`
- L801 _public function_ `inline const TArray<FNavDataConfig>& GetSupportedAgents() const`
- L802 _public prototype_ `void OverrideSupportedAgents(const TArray<FNavDataConfig>& NewSupportedAgents);`
- L803 _public prototype_ `void SetSupportedAgentsMask(const FNavAgentSelector& InSupportedAgentsMask);`
- L804 _public function_ `FNavAgentSelector GetSupportedAgentsMask() const`
- L806 _public prototype_ `virtual void ApplyWorldOffset(const FVector& InOffset, bool bWorldShift) override;`
- L809 _public prototype_ `bool IsNavigationDirty() const;` — checks if navigation/navmesh is dirty and needs to be rebuilt
- L812 _public prototype_ `bool CanRebuildDirtyNavigation() const;` — checks if dirty navigation data can rebuild itself
- L814 _public function_ `bool SupportsNavigationGeneration() const`
- L816 _public prototype_ `bool DirtyNavDataPackageOnNavigationGenerationFinished() const;`
- L818 _public prototype_ `static bool DoesPathIntersectBox(const FNavigationPath* Path, const FBox& Box, uint32 StartingIndex = 0, FVector* AgentExtent = NULL);`
- L819 _public prototype_ `static bool DoesPathIntersectBox(const FNavigationPath* Path, const FBox& Box, const FVector& AgentLocation, uint32 StartingIndex = 0, FVector* AgentExtent = NULL);`
- L824 _public prototype_ `virtual void RegisterInvoker(AActor& Invoker, float TileGenerationRadius, float TileRemovalRadius, const FNavAgentSelector& Agents, ENavigationInvokerPriority InPriority);`
- L826 _public prototype_ `virtual void RegisterInvoker(const TWeakInterfacePtr<INavigationInvokerInterface>& Invoker, float TileGenerationRadius, float TileRemovalRadius, const FNavAgentSelector& Agents, ENavigationInvokerPriority InPriority);`
- L828 _public prototype_ `virtual void UnregisterInvoker(AActor& Invoker);`
- L830 _public prototype_ `virtual void UnregisterInvoker(const TWeakInterfacePtr<INavigationInvokerInterface>& Invoker);`
- L832 _public prototype_ `static void RegisterNavigationInvoker(AActor& Invoker, float TileGenerationRadius, float TileRemovalRadius, const FNavAgentSelector& Agents = FNavAgentSelector(), ENavigationInvokerPriority Priority = ENavigationInvokerPriority::Default);`
- L834 _public prototype_ `static void UnregisterNavigationInvoker(AActor& Invoker);`
- L836 _public function_ `const TArray<FNavigationInvokerRaw>& GetInvokerLocations() const`
- L837 _public function_ `const TArray<FBox>& GetInvokersSeedBounds() const`
- L844 _public prototype_ `virtual void UnregisterNavData(ANavigationData* NavData);` — @todo document
- L849 _public prototype_ `virtual void UnregisterUnusedNavData();` — Traverses SupportedAgents and for all agents not supported (i.e. filtered out by SupportedAgentsMask) checks if there's a currently registered NavigationData instance for that agent, and if so it unregisters that agent
- L852 _public prototype_ `virtual void RequestRegistrationDeferred(ANavigationData& NavData);` — Adds NavData to registration candidates queue - NavDataRegistrationQueue
- L855 _protected prototype_ `void ApplySupportedAgentsFilter();`
- L859 _protected prototype_ `void RegisterNavigationDataInstances();` — Processes all NavigationData instances in UWorld owning navigation system instance, and registers all previously unregistered
- L864 _protected prototype_ `virtual bool ConditionalPopulateNavOctree();` — called in places where we need to spawn the NavOctree, but is checking additional conditions if we really want to do that depending on navigation data setup among others @return true if NavOctree instance has been created, or if one is already present
- L867 _protected prototype_ `virtual void ConstructNavOctree();` — called to instantiate NavigationSystem's NavOctree instance
- L870 _protected prototype_ `virtual void ProcessRegistrationCandidates();` — Processes registration of candidates queues via RequestRegistration and stored in NavDataRegistrationQueue
- L873 _protected prototype_ `void ProcessCustomLinkPendingRegistration();` — Registers custom navigation links awaiting registration in the navigation object repository
- L876 _protected prototype_ `virtual void PerformNavigationBoundsUpdate(const TArray<FNavigationBoundsUpdateRequest>& UpdateRequests);` — used to apply updates of nav volumes in navigation system's tick
- L879 _protected prototype_ `void AddNavigationBounds(const FNavigationBounds& NewBounds);` — adds data to RegisteredNavBounds
- L882 _protected prototype_ `virtual void GatherNavigationBounds();` — Searches for all valid navigation bounds in the world and stores them
- L886 _protected prototype_ `virtual void GetInvokerSeedLocations(const UWorld& InWorld, TArray<FVector, TInlineAllocator<32>>& OutSeedLocations);` — Get seed locations for invokers, @see InvokersMaximumDistanceFromSeed By default these are the player pawn locations. If a player controller has no pawn assigned, the player's camera location will be used instead.
- L889 _protected prototype_ `ANavigationData* GetNavDataWithID(const uint16 NavDataID) const;` — @return pointer to ANavigationData instance of given ID, or NULL if it was not found. Note it looks only through registered navigation data
- L892 _protected prototype_ `TSharedPtr<const FNavigationElement> GetNavigationElementForUObject(const UObject*) const;` — @return Valid shared pointer on a FNavigationElement if the provided UObject is registered in the navigation system, an invalid one otherwise.
- L895 _protected prototype_ `FNavigationElementHandle GetNavigationElementHandleForUObject(const UObject*) const;` — @return Valid handle if the provided UObject is registered in the navigation system, FNavigationElementHandle::Invalid otherwise.
- L897 _protected prototype_ `static void RegisterComponentToNavOctree(UActorComponent* Comp);`
- L898 _protected prototype_ `static void UnregisterComponentToNavOctree(UActorComponent* Comp);`
- L901 _public prototype_ `virtual void ReleaseInitialBuildingLock();`
- L906 _public prototype_ `static bool SupportsDynamicChanges(UWorld* World);`
- L907 _public prototype_ `static FNavigationElementHandle AddNavigationElement(UWorld* World, FNavigationElement&& Element);`
- L908 _public prototype_ `static void RemoveNavigationElement(UWorld* World, FNavigationElementHandle ElementHandle);`
- L909 _public prototype_ `static void OnNavigationElementUpdated(UWorld* World, FNavigationElementHandle ElementHandle, FNavigationElement&& Element);`
- L911 _public prototype_ `static void OnNavRelevantObjectRegistered(UObject& Object);`
- L912 _public prototype_ `static void UpdateNavRelevantObjectInNavOctree(UObject& Object);`
- L913 _public prototype_ `static void OnNavRelevantObjectUnregistered(UObject& Object);`
- L915 _public prototype_ `static void OnComponentRegistered(UActorComponent* Comp);`
- L916 _public prototype_ `static void OnComponentUnregistered(UActorComponent* Comp);`
- L917 _public prototype_ `static void RegisterComponent(UActorComponent* Comp);`
- L918 _public prototype_ `static void UnregisterComponent(UActorComponent* Comp);`
- L919 _public prototype_ `static void OnActorRegistered(AActor* Actor);`
- L920 _public prototype_ `static void OnActorUnregistered(AActor* Actor);`
- L923 _public prototype_ `static void UpdateActorInNavOctree(AActor& Actor);` — update navoctree entry for specified actor/component
- L924 _public prototype_ `static void UpdateComponentInNavOctree(UActorComponent& Comp);`
- L926 _public prototype_ `static void UpdateActorAndComponentsInNavOctree(AActor& Actor, bool bUpdateAttachedActors = true);` — update all navoctree entries for actor and its components
- L928 _public prototype_ `static void UpdateNavOctreeAfterMove(USceneComponent* Comp);` — update all navoctree entries for actor and its non scene components after root movement
- L932 _protected prototype_ `static void RegisterNavRelevantObjectStatic(const INavRelevantInterface& NavRelevantObject, const UObject& Object);` — Fetches the repository from the provided object and registers the object with it.
- L935 _protected prototype_ `void RegisterNavRelevantObjectInternal(const INavRelevantInterface& NavRelevantObject, const UObject& Object);` — Similar to UnregisterNavRelevantObjectStatic but uses the cached repository.
- L938 _protected prototype_ `static void UnregisterNavRelevantObjectStatic(const UObject& Object);` — Fetches the repository from the provided object and unregisters the object with it.
- L941 _protected prototype_ `void UnregisterNavRelevantObjectInternal(const UObject& Object);` — Similar to UnregisterNavRelevantObjectStatic but uses the cached repository.
- L948 _protected prototype_ `static void UpdateNavRelevantObjectInNavOctreeStatic( const INavRelevantInterface& InNavRelevantObject, const UObject& InObject, UNavigationSystemV1* InNavigationSystem, TFunctionRef<void(UNavigationSystemV1&, const TSharedRef<const FNavigationElement>&)> InCallback);` — In actor/component code paths it is possible that updates get called without a previous call to register (wasn't relevant at that time). In those cases we create a new, or an updated, navigation element if needed. @note Method expects only navigation relevant objects and will ensure otherwise.
- L961 _protected prototype_ `static int32 GetAllAttachedActors(const AActor& RootActor, TArray<AActor*>& OutAttachedActors);` — A helper function that gathers all actors attached to RootActor and fetches them back. The function does consider multi-level attachments. @param RootActor The reference actor to get the attached actors from. @param OutAttachedActors is getting reset at the beginning of the function. When done it is guaranteed to contain unique, non-null ptrs. It will not include RootActor. @return the number of unique attached actors
- L964 _protected prototype_ `static void UpdateAttachedActorsInNavOctree(AActor& RootActor);` — updates navoctree information on actors attached to RootActor
- L968 _public prototype_ `static void ClearNavOctreeAll(AActor* Actor);` — removes all navoctree entries for actor and its components
- L971 _public prototype_ `static void UpdateNavOctreeBounds(AActor* Actor);` — updates bounds of all components implementing INavRelevantInterface
- L973 _public prototype_ `void AddDirtyArea(const FBox& NewArea, ENavigationDirtyFlag Flags, const FName& DebugReason = NAME_None);`
- L974 _public prototype_ `void AddDirtyArea(const FBox& NewArea, ENavigationDirtyFlag Flags, const TFunction<const TSharedPtr<const FNavigationElement>()>& ElementProviderFunc, const FName& DebugReason = NAME_None);`
- L975 _public prototype_ `void AddDirtyAreas(const TArray<FBox>& NewAreas, ENavigationDirtyFlag Flags, const FName& DebugReason = NAME_None);`
- L976 _public prototype_ `bool HasDirtyAreasQueued() const;`
- L977 _public prototype_ `int32 GetNumDirtyAreas() const;`
- L978 _public function_ `float GetDirtyAreaWarningSizeThreshold() const`
- L980 _public function_ `const FNavigationOctree* GetNavOctree() const`
- L981 _public function_ `FNavigationOctree* GetMutableNavOctree()`
- L983 _public function_ `inline const FOctreeElementId2* GetNavOctreeIdForElement(FNavigationElementHandle Element) const`
- L988 _public function_ `inline bool HasPendingUpdateForElement(FNavigationElementHandle Element) const`
- L993 _public prototype_ `void FlushPendingOperations();`
- L996 _public prototype_ `void ProcessPendingOctreeUpdates();` — Update any pending FNavigationDirtyElement in the navigation system default navigation octree.
- L999 _protected prototype_ `void ResetDefaultDirtyAreasController();`
- L1001 _protected prototype_ `void RemoveFromNavOctree(const FOctreeElementId2& ElementId, int32 UpdateFlags);`
- L1004 _public prototype_ `const FNavigationRelevantData* GetDataForElement(FNavigationElementHandle Element) const;`
- L1006 _public prototype_ `FNavigationRelevantData* GetMutableDataForElement(FNavigationElementHandle Element);`
- L1009 _public prototype_ `void FindElementsInNavOctree(const FBox& QueryBox, const FNavigationOctreeFilter& Filter, TArray<FNavigationOctreeElement>& Elements);` — find all elements in navigation octree within given box (intersection)
- L1012 _public prototype_ `void UpdateNavOctreeElement(FNavigationElementHandle Handle, const TSharedRef<const FNavigationElement>& Element, int32 UpdateFlags);` — update single element in navoctree
- L1015 _public prototype_ `bool UpdateNavOctreeElementBounds(FNavigationElementHandle Handle, const FBox& NewBounds, TConstArrayView<FBox> DirtyAreas);` — update element's bounds in navigation octree and mark only specified area as dirty, doesn't re-export geometry
- L1018 _public prototype_ `bool ReplaceAreaInOctreeData(FNavigationElementHandle Handle, TSubclassOf<UNavArea> OldArea, TSubclassOf<UNavArea> NewArea, bool bReplaceChildClasses = false);` — fetched element's data from the octree and replaces occurrences of OldArea with NewArea
- L1023 _public prototype_ `virtual void RegisterCustomLink(INavLinkCustomInterface& CustomLink);`
- L1024 _public prototype_ `void UnregisterCustomLink(INavLinkCustomInterface& CustomLink);`
- L1025 _public function_ `int32 GetNumCustomLinks() const`
- L1027 _public prototype_ `static void RequestCustomLinkRegistering(INavLinkCustomInterface& CustomLink, UObject* OwnerOb);`
- L1028 _public prototype_ `static void RequestCustomLinkUnregistering(INavLinkCustomInterface& CustomLink, UObject* ObjectOb);`
- L1031 _public function_ `INavLinkCustomInterface* GetCustomLink(uint32 UniqueLinkId) const` — `UE_DEPRECATED(5.3, "LinkIds are now based on FNavLinkId call the version of this function that takes FNavLinkId. This function only returns nullptr.")`
- L1034 _public prototype_ `INavLinkCustomInterface* GetCustomLink(FNavLinkId UniqueLinkId) const;` — find custom link by unique ID
- L1037 _public prototype_ `void UpdateCustomLink(const INavLinkCustomInterface* CustomLink);` — updates custom link for all active navigation data instances
- L1040 _public prototype_ `static FBox ComputeCustomLinkBounds(const INavLinkCustomInterface& CustomLink);` — Return a Bounding Box containing the navlink points
- L1045 _public prototype_ `static void RequestAreaRegistering(UClass* NavAreaClass);`
- L1046 _public prototype_ `static void RequestAreaUnregistering(UClass* NavAreaClass);`
- L1049 _public prototype_ `int32 GetSupportedAgentIndex(const ANavigationData* NavData) const;` — find index in SupportedAgents array for given navigation data
- L1052 _public prototype_ `int32 GetSupportedAgentIndex(const FNavAgentProperties& NavAgent) const;` — find index in SupportedAgents array for agent type
- L1059 _public prototype_ `void DescribeFilterFlags(UEnum* FlagsEnum) const;` — prepare descriptions of navigation flags in UNavigationQueryFilter class: using enum
- L1062 _public prototype_ `void DescribeFilterFlags(const TArray<FString>& FlagsDesc) const;` — prepare descriptions of navigation flags in UNavigationQueryFilter class: using array
- L1065 _public prototype_ `void ResetCachedFilter(TSubclassOf<UNavigationQueryFilter> FilterClass);` — removes cached filters from currently registered navigation data
- L1072 _public prototype_ `virtual void Build();` — Triggers navigation building on all eligible navigation data.
- L1075 _public prototype_ `virtual void CancelBuild();` — Cancels all currently running navigation builds
- L1078 _public prototype_ `void OnPIEStart();` — @todo document
- L1080 _public prototype_ `void OnPIEEnd();` — @todo document
- L1083 _public function_ `inline bool IsNavigationBuildingLocked(uint8 Flags = ~0) const` — @todo document
- L1086 _public function_ `inline bool IsNavigationBuildingPermanentlyLocked() const` — check if building is permanently locked to avoid showing navmesh building notify (due to queued dirty areas)
- L1092 _public function_ `inline bool IsNavigationOctreeLocked() const` — check if navigation octree updates are currently ignored
- L1096 _public prototype_ `void OnNavigationBoundsUpdated(ANavMeshBoundsVolume* NavVolume);` — `UFUNCTION(BlueprintCallable, Category = "AI|Navigation")` — @todo document
- L1097 _public prototype_ `virtual void OnNavigationBoundsAdded(ANavMeshBoundsVolume* NavVolume);`
- L1098 _public prototype_ `virtual void OnNavigationBoundsRemoved(ANavMeshBoundsVolume* NavVolume);`
- L1101 _public prototype_ `bool IsNavigationBuildInProgress();` — determines whether any generator is performing navigation building actions at the moment, dirty areas are also checked
- L1103 _public prototype_ `virtual void OnNavigationGenerationFinished(ANavigationData& NavData);`
- L1106 _public prototype_ `int32 GetNumRemainingBuildTasks() const;` — Used to display "navigation building in progress" counter
- L1109 _public prototype_ `int32 GetNumRunningBuildTasks() const;` — Number of currently running tasks
- L1113 _protected prototype_ `virtual void DoInitialSetup();` — Sets up SuportedAgents and NavigationDataCreators. Override it to add additional setup, but make sure to call Super implementation
- L1116 _protected prototype_ `virtual void UpdateAbstractNavData();` — Find or create abstract nav data
- L1120 _protected prototype_ `virtual void AddLevelToOctree(ULevel& Level);` — Called during ConditionalPopulateNavOctree and gives subclassess a chance to influence what gets added
- L1123 _protected prototype_ `virtual void OnBeginTearingDown(UWorld* World);` — Called as part of UWorld::BeginTearingDown
- L1127 _public prototype_ `virtual void CleanUp(const FNavigationSystem::ECleanupMode Mode = FNavigationSystem::ECleanupMode::CleanupUnsafe) override;` — Called upon UWorld destruction to release what needs to be released
- L1132 _public prototype_ `virtual void OnInitializeActors() override;` — Called when owner-UWorld initializes actors
- L1135 _public prototype_ `virtual void OnWorldInitDone(FNavigationSystemRunMode Mode);`
- L1138 _public function_ `inline virtual bool IsWorldInitDone() const override` — Returns true if world has been initialized.
- L1139 _public function_ `inline bool IsInitialized() const`
- L1141 _public function_ `inline FNavigationSystemRunMode GetRunMode() const`
- L1144 _public prototype_ `void InitializeLevelCollisions();` — adds BSP collisions of currently streamed in levels to octree
- L1152 _public prototype_ `void AddNavigationBuildLock(uint8 Flags);`
- L1153 _public prototype_ `void RemoveNavigationBuildLock(uint8 Flags, const ELockRemovalRebuildAction RebuildAction = ELockRemovalRebuildAction::Rebuild);`
- L1155 _public prototype_ `void SetNavigationOctreeLock(bool bLock);`
- L1159 _public function_ `virtual bool GetIsAutoUpdateEnabled() const` — checks if auto-rebuilding navigation data is enabled. Defaults to bNavigationAutoUpdateEnabled value, but can be overridden per nav sys instance
- L1163 _public prototype_ `static void SetNavigationAutoUpdateEnabled(bool bNewEnable, UNavigationSystemBase* InNavigationSystem);` — allow editor to toggle whether seamless navigation building is enabled
- L1165 _public function_ `inline bool IsNavigationRegisterLocked() const`
- L1166 _public function_ `inline bool IsNavigationUnregisterLocked() const`
- L1167 _public function_ `inline bool IsNavigationUpdateLocked() const`
- L1168 _public function_ `inline void AddNavigationUpdateLock(uint8 Flags)`
- L1169 _public function_ `inline void RemoveNavigationUpdateLock(uint8 Flags)`
- L1171 _public prototype_ `void UpdateLevelCollision(ULevel* InLevel);`
- L1175 _public function_ `inline bool IsSetUpForLazyGeometryExporting() const`
- L1177 _public prototype_ `static UNavigationSystemV1* GetCurrent(UWorld* World);`
- L1178 _public prototype_ `static UNavigationSystemV1* GetCurrent(UObject* WorldContextObject);`
- L1180 _public prototype_ `virtual void InitializeForWorld(UWorld& World, FNavigationSystemRunMode Mode) override;`
- L1183 _public prototype_ `void GetNavAgentPropertiesArray(TArray<FNavAgentProperties>& OutNavAgentProperties) const;` — Fetch the array of all nav-agent properties.
- L1185 _public function_ `static inline bool ShouldUpdateNavOctreeOnComponentChange()`
- L1199 _public prototype_ `virtual bool ShouldCreateNavigationSystemInstance(const UWorld* World) const override;` — Indicates whether navigation is allowed for a given world. @param World The world in which the navigation would be used @return whether the navigation system can be used in the specified world or not
- L1201 _public function_ `static inline bool IsNavigationSystemStatic()`
- L1218 _public prototype_ `static void ConfigureAsStatic(bool bEnableStatic = true);` — call with bEnableStatic == true to signal the NavigationSystem it doesn't need to store any navigation-generation-related data at game runtime, because nothing is going to use it anyway. This will short-circuit all code related to navmesh rebuilding, so use it only if you have fully static navigation in your game. bEnableStatic = false will reset the mechanism. Note: this is not a runtime switch. It's highly advisable not to call it manually and use UNavigationSystemModuleConfig.bStrictlyStatic instead
- L1220 _public prototype_ `static void SetUpdateNavOctreeOnComponentChange(bool bNewUpdateOnComponentChange);`
- L1225 _public prototype_ `bool HandleCycleNavDrawnCommand( const TCHAR* Cmd, FOutputDevice& Ar );` — Exec command handlers
- L1226 _public prototype_ `bool HandleCountNavMemCommand();`
- L1231 _public prototype_ `void CycleNavigationDataDrawn();`
- L1233 _public function_ `FNavRegenTimeSliceManager& GetMutableNavRegenTimeSliceManager()`
- L1235 _public function_ `FNavigationSystemRunMode GetOperationMode() const`
- L1240 _protected member_ `FNavigationSystemRunMode OperationMode;` — `UPROPERTY()`
- L1243 _protected member_ `TArray<FAsyncPathFindingQuery> AsyncPathFindingQueries;` — Queued async pathfinding queries to process in the next update.
- L1246 _protected member_ `TArray<FAsyncPathFindingQuery> AsyncPathFindingCompletedQueries;` — Queued async pathfinding results computed by the dedicated task in the last frame and ready to dispatch in the next update.
- L1249 _protected member_ `FGraphEventRef AsyncPathFindingTask;` — Graph event that the main thread will wait for to synchronize with the async pathfinding task, if any.
- L1252 _protected member_ `TAtomic<bool> bAbortAsyncQueriesRequested;` — Flag used by main thread to ask the async pathfinding task to stop and postpone remaining queries, if any.
- L1254 _protected member_ `FCriticalSection NavDataRegistration;`
- L1256 _protected member_ `TMap<FNavAgentProperties, TWeakObjectPtr<ANavigationData> > AgentToNavDataMap;`
- L1258 _protected member_ `FNavigationOctreeController DefaultOctreeController;`
- L1260 _protected member_ `TMap<FNavLinkId, FNavigationSystem::FCustomLinkOwnerInfo> CustomNavLinksMap;`
- L1262 _protected member_ `FNavigationDirtyAreasController DefaultDirtyAreasController;`
- L1265 _protected member_ `TObjectPtr<UNavigationObjectRepository> Repository = nullptr;` — `UPROPERTY(transient)`
- L1267 _protected member_ `TArray<TWeakObjectPtr<ANavigationData>> NavigationDataToRemove;`
- L1270 _protected member_ `FCriticalSection NavDataRegistrationSection;` — async queries
- L1273 _protected member_ `uint8 NavUpdateLockFlags;`
- L1275 _protected member_ `uint8 NavBuildingLockFlags;`
- L1278 _protected member_ `uint8 InitialNavBuildingLockFlags;` — set of locking flags applied on startup of navigation system
- L1280 _protected member_ `uint8 bInitialSetupHasBeenPerformed : 1;`
- L1281 _protected member_ `uint8 bInitialLevelsAdded : 1;`
- L1282 _protected member_ `uint8 bWorldInitDone : 1;`
- L1284 _protected member_ `uint8 bCleanUpDone : 1;` — set when the NavSys instance has been cleaned up. This is an irreversible state
- L1285 _protected member_ `uint8 bAsyncBuildPaused : 1;` — mz@todo remove, replaced by bIsPIEActive and IsGameWorld
- L1289 _protected member_ `mutable FBox NavigableWorldBounds;` — cached navigable world bounding box
- L1292 _protected member_ `int32 CurrentlyDrawnNavDataIndex;` — indicates which of multiple navigation data instances to draw
- L1296 _protected member_ `static FNavigationSystemExec ExecHandler;` — self-registering exec command to handle nav sys console commands
- L1300 _protected member_ `static bool bNavigationAutoUpdateEnabled;` — whether seamless navigation building is enabled
- L1301 _protected member_ `static bool bUpdateNavOctreeOnComponentChange;`
- L1302 _protected member_ `static bool bStaticRuntimeNavigation;`
- L1303 _protected member_ `static bool bIsPIEActive;`
- L1305 _protected member_ `TSet<TObjectPtr<const UClass>> NavAreaClasses;`
- L1307 _protected member_ `FNavRegenTimeSliceManager NavRegenTimeSliceManager;`
- L1310 _protected prototype_ `void OnPostLoadMap(UWorld* LoadedWorld);` — delegate handler for PostLoadMap event
- L1313 _protected prototype_ `void OnMapOpened(const FString& Filename, bool bAsTemplate);`
- L1316 _protected prototype_ `void OnActorMoved(AActor* Actor);` — delegate handler for ActorMoved events
- L1320 _protected prototype_ `void OnNavigationDirtied(const FBox& Bounds);` — delegate handler called when navigation is dirtied
- L1322 _protected member_ `FDelegateHandle ReloadCompleteDelegateHandle;`
- L1325 _protected prototype_ `virtual void OnReloadComplete(EReloadCompleteReason Reason);` — called to notify NavigationSystem about finished reload
- L1331 _protected prototype_ `virtual ERegistrationResult RegisterNavData(ANavigationData* NavData);` — Registers given navigation data with this Navigation System. @return RegistrationSuccessful if registration was successful, other results mean it failed @see ERegistrationResult
- L1334 _protected prototype_ `void RegisterNavAreaClass(UClass* NavAreaClass);` — tries to register navigation area
- L1337 _protected prototype_ `void UnregisterNavAreaClass(UClass* NavAreaClass);` — tries to unregister navigation area
- L1339 _protected prototype_ `void OnNavigationAreaEvent(UClass* AreaClass, ENavAreaEvent::Type Event);`
- L1341 _protected prototype_ `FSetElementId RegisterNavigationElementWithNavOctree(const TSharedRef<const FNavigationElement>& Element, int32 UpdateFlags);`
- L1343 _protected prototype_ `void UnregisterNavigationElementWithOctree(const TSharedRef<const FNavigationElement>& Element, int32 UpdateFlags);`
- L1346 _protected prototype_ `bool GetNavOctreeElementData(FNavigationElementHandle Element, ENavigationDirtyFlag& OutDirtyFlags, FBox& OutDirtyBounds);` — read element data from navigation octree
- L1351 _protected prototype_ `void AddElementToNavOctree(const FNavigationDirtyElement& DirtyElement);` — Adds given element to NavOctree. No check for owner's validity are performed, nor its presence in NavOctree - function assumes callee responsibility in this regard
- L1353 _protected prototype_ `void SetCrowdManager(UCrowdManagerBase* NewCrowdManager);`
- L1356 _protected prototype_ `void AddLevelCollisionToOctree(ULevel* Level);` — Add BSP collision data to navigation octree
- L1359 _protected prototype_ `void RemoveLevelCollisionFromOctree(ULevel* Level);` — Remove BSP collision data from navigation octree
- L1361 _protected prototype_ `virtual void SpawnMissingNavigationData();`
- L1369 _protected prototype_ `uint8 FillInstantiatedDataMask(TBitArray<>& OutInstantiatedMask, ULevel* InLevel = nullptr);` — Fills a mask indicating which navigation data associated to the supported agent mask are already instantiated. @param OutInstantiatedMask The mask that will represent already instantiated navigation data. @param InLevel If specified will be used to search for navigation data; will use the owning world otherwise. @return Number of instantiated navigation data.
- L1376 _protected prototype_ `void SpawnMissingNavigationDataInLevel(const TBitArray<>& InInstantiatedMask, ULevel* InLevel = nullptr);` — Spawns missing navigation data. @param InInstantiatedMask The mask representing already instantiated navigation data. @param InLevel Level in which the new data must be added. See CreateNavigationDataInstanceInLevel doc.
- L1379 _public prototype_ `void DemandLazyDataGathering(FNavigationRelevantData& ElementData);`
- L1383 _private prototype_ `void CheckToLimitNavigationBoundsToLoadedRegions(FNavigationBounds& OutBounds) const;` — Reduces a nav bounds only to regions overlapping loaded world partition regions (if any exist)
- L1386 _protected prototype_ `virtual void RebuildDirtyAreas(float DeltaSeconds);`
- L1389 _protected prototype_ `void AddNavigationBoundsUpdateRequest(const FNavigationBoundsUpdateRequest& UpdateRequest);` — adds navigation bounds update request to a pending list
- L1392 _protected prototype_ `virtual void RebuildAll(bool bIsLoadTime = false);` — Triggers navigation building on all eligible navigation data.
- L1395 _protected prototype_ `void OnLevelAddedToWorld(ULevel* InLevel, UWorld* InWorld);` — Handler for FWorldDelegates::LevelAddedToWorld event
- L1398 _protected prototype_ `void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld);` — Handler for FWorldDelegates::LevelRemovedFromWorld event
- L1401 _protected function_ `void OnWorldPostActorTick(UWorld* World, ELevelTick TickType, float DeltaTime)` — Handler for FWorldDelegates::OnWorldPostActorTick event
- L1408 _protected prototype_ `void AddAsyncQuery(const FAsyncPathFindingQuery& Query);` — Adds given request to requests queue. Note it's to be called only on game thread only
- L1412 _protected prototype_ `void TriggerAsyncQueries(TArray<FAsyncPathFindingQuery>& PathFindingQueries);` — spawns a non-game-thread task to process requests given in PathFindingQueries. In the process PathFindingQueries gets copied.
- L1415 _protected prototype_ `void PerformAsyncQueries(TArray<FAsyncPathFindingQuery> PathFindingQueries);` — Processes pathfinding requests given in PathFindingQueries.
- L1418 _protected prototype_ `void DispatchAsyncQueriesResults(const TArray<FAsyncPathFindingQuery>& PathFindingQueries) const;` — Broadcasts completion delegate for all completed async pathfinding requests.
- L1424 _protected prototype_ `void PostponeAsyncQueries();` — Requests the async pathfinding task to abort and waits for it to complete before resuming the main thread. Pathfind task will postpone remaining queries to next frame.
- L1427 _protected prototype_ `virtual void DestroyNavOctree();`
- L1432 _protected prototype_ `bool RequiresNavOctree() const;` — Whether Navigation system needs to populate nav octree. Depends on runtime generation settings of each navigation data, always true in the editor
- L1437 _protected prototype_ `ERuntimeGenerationType GetRuntimeGenerationType() const;` — Return "Strongest" runtime generation type required by registered navigation data objects Depends on runtime generation settings of each navigation data, always ERuntimeGenerationType::Dynamic in the editor world
- L1442 _protected prototype_ `bool DoesAnyNavDataSupportRuntimeGeneration() const;` — Returns true if any registered navigation data supports runtime generation. Unlike GetRuntimeGenerationType which returns the raw config enum, this also accounts for nav data that was spawned at runtime and needs rebuilding.
- L1447 _protected prototype_ `bool DoesAnyNavDataRequireGeometryStorage() const;` — Returns true if any registered navigation data requires geometry to be stored in the nav octree. This is true for Dynamic nav data, or nav data that was spawned at runtime (which needs a full rebuild). DynamicModifiersOnly does NOT require geometry storage.
- L1450 _protected prototype_ `void LogNavDataRegistrationResult(ERegistrationResult);` — `UE_DEPRECATED(5.8, "Use LogNavDataRegistrationResult receiving ANavigationData* instead.")`
- L1452 _protected prototype_ `void LogNavDataRegistrationResult(ERegistrationResult, const ANavigationData* NavigationData) const;`
- L1457 _protected prototype_ `bool IsAllowedToRebuild() const;` — Whether Navigation System is allowed to rebuild the navmesh Depends on runtime generation settings of each navigation data, always true in the editor
- L1460 _protected prototype_ `void OnGenerateNavigationOnlyAroundNavigationInvokersChanged();` — Handle forwarding the information where needed when the setting is changed
- L1466 _public prototype_ `void VerifyNavigationRenderingComponents(const bool bShow);`
- L1468 _public prototype_ `virtual int GetNavigationBoundsForNavData(const ANavigationData& NavData, TArray<FBox>& OutBounds, ULevel* InLevel = nullptr) const;` — @param InLevel Optional parameter to limit the navigation bounds to consider to the ones from that level
- L1469 _public prototype_ `static INavigationDataInterface* GetNavDataForActor(const AActor& Actor);`
- L1470 _public prototype_ `virtual void Configure(const UNavigationSystemConfig& Config) override;`
- L1471 _public prototype_ `virtual void AppendConfig(const UNavigationSystemConfig& NewConfig) override;`
- L1474 _public prototype_ `void GetOnScreenMessages(TMultiMap<FCoreDelegates::EOnScreenMessageSeverity, FText>& OutMessages);`
- L1485 _public prototype_ `static bool K2_GetRandomPointInNavigableRadius(UObject* WorldContextObject, const FVector& Origin, FVector& RandomLocation, float Radius, ANavigationData* NavData = NULL, TSubclassOf<UNavigationQueryFilter> FilterClass = {});` — `UE_DEPRECATED(5.1, "This version is deprecated. Please use GetRandomLocationInNavigableRadius instead")` — `UFUNCTION(BlueprintPure, Category = "AI|Navigation", meta = (WorldContext = "WorldContextObject", DisplayName = "GetRandomPointInNavigableRadius", ScriptName = "GetRandomPointInNavigableRadius", DeprecatedFunction, DeprecationMessage = "GetRandomPointInNavigableRadius is deprecated. Use GetRandomLocationInNavigableRadius instead"))` — Note that this function was only deprecated for blueprint in 5.1 Note2: originally deprecated as 4.22, bumped up to 5.1 as per comment above.

#### enum `UNavigationSystemV1::ERegistrationResult`  
`enum ERegistrationResult`  
_L592-600_
- L594 _public enumerator_ `RegistrationError`
- L595 _public enumerator_ `RegistrationFailed_DataPendingKill` — means navigation data being registered is marked as pending kill
- L596 _public enumerator_ `RegistrationFailed_AgentAlreadySupported` — this means that navigation agent supported by given nav data is already handled by some other, previously registered instance
- L597 _public enumerator_ `RegistrationFailed_AgentNotValid` — given instance contains navmesh that doesn't support any of expected agent types, or instance doesn't specify any agent
- L598 _public enumerator_ `RegistrationFailed_NotSuitable` — given instance had been considered unsuitable by current navigation system instance itself. NOTE: this value is not currently being used by the engine-supplied navigation system classes
- L599 _public enumerator_ `RegistrationSuccessful`

#### enum `UNavigationSystemV1::EOctreeUpdateMode`  
`enum EOctreeUpdateMode`  
_L603-610_
- desc: EOctreeUpdateMode is deprecated. Use FNavigationOctreeController::EOctreeUpdateMode instead
- L605 _public enumerator_ `OctreeUpdate_Default = 0` — regular update, mark dirty areas depending on exported content
- L606 _public enumerator_ `OctreeUpdate_Geometry = 1` — full update, mark dirty areas for geometry rebuild
- L607 _public enumerator_ `OctreeUpdate_Modifiers = 2` — quick update, mark dirty areas for modifier rebuild
- L608 _public enumerator_ `OctreeUpdate_Refresh = 4` — update is used for refresh, don't invalidate pending queue
- L609 _public enumerator_ `OctreeUpdate_ParentChain = 8` — update child nodes, don't remove anything

#### enum `UNavigationSystemV1::ELockRemovalRebuildAction`  
`enum class ELockRemovalRebuildAction`  
_L1146-1151_
- L1148 _public enumerator_ `Rebuild`
- L1149 _public enumerator_ `RebuildIfNotInEditor`
- L1150 _public enumerator_ `NoRebuild`

#### class `UNavigationSystemModuleConfig`  
`class UNavigationSystemModuleConfig : public UNavigationSystemConfig`  
_L1492-1530_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UNavigationSystemConfig`
- L1498 _public member_ `uint32 bDirtyNavDataPackageOnNavigationGenerationFinished : 1;` — `UPROPERTY()`
- L1503 _protected member_ `uint32 bStrictlyStatic : 1;` — `UPROPERTY(EditAnywhere, Category = Navigation)` — Whether at game runtime we expect any kind of dynamic navigation generation
- L1506 _protected member_ `uint32 bCreateOnClient : 1;` — `UPROPERTY(EditAnywhere, Category = Navigation)`
- L1509 _protected member_ `uint32 bAutoSpawnMissingNavData : 1;` — `UPROPERTY(EditAnywhere, Category = Navigation)`
- L1512 _protected member_ `uint32 bSpawnNavDataInNavBoundsLevel : 1;` — `UPROPERTY(EditAnywhere, Category = Navigation)`
- L1515 _public prototype_ `UNavigationSystemModuleConfig(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L1517 _public prototype_ `virtual void PostInitProperties() override;`
- L1519 _public prototype_ `virtual UNavigationSystemBase* CreateAndConfigureNavigationSystem(UWorld& World) const override;`
- L1522 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L1529 _protected prototype_ `void UpdateWithNavSysCDO(const UNavigationSystemV1& NavSysCDO);`

#### Free symbols / members of external scopes

- L47 _macro_ `#define ALLOW_TIME_SLICE_DEBUG 1`
- L49 _macro_ `#define ALLOW_TIME_SLICE_DEBUG 0`
- L53 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNavAreaChanged, const UClass* );` — delegate to let interested parties know that new nav area class has been registered
- L53 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNavAreaChanged, const UClass* );` — delegate to let interested parties know that new nav area class has been registered
- L56 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNavDataGenericEvent, ANavigationData*, NavData);` — Delegate to let interested parties know that Nav Data has been registered
- L56 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNavDataGenericEvent, ANavigationData*, NavData);` — Delegate to let interested parties know that Nav Data has been registered
- L58 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnNavigationInitDone);`
- L58 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnNavigationInitDone);`
- L60 _namespace_ `namespace NavigationDebugDrawing`
- L62 _externvar_ `extern const float PathLineThickness;` (scope `NavigationDebugDrawing`)
- L63 _externvar_ `extern const FVector PathOffset;` (scope `NavigationDebugDrawing`)
- L64 _externvar_ `extern const FVector PathNodeBoxExtent;` (scope `NavigationDebugDrawing`)
- L67 _namespace_ `namespace FNavigationSystem`
- L72 _typedef_ `typedef ANavigationData* (*FNavigationDataInstanceCreator)(UWorld*, const FNavDataConfig&);` (scope `FNavigationSystem`) — Used to construct an ANavigationData instance for specified navigation data agent
- L85 _prototype_ `bool ShouldLoadNavigationOnClient(ANavigationData& NavData);` (scope `FNavigationSystem`)
- L87 _prototype_ `void MakeAllComponentsNeverAffectNav(AActor& Actor);` (scope `FNavigationSystem`)
- L90 _externvar_ `extern const FName DebugTimeSliceDefaultSectionName;` (scope `FNavigationSystem`)
- L102 _namespace_ `namespace ENavigationBuildLock`
- L117 _macro_ `#define MARK_TIMESLICE_SECTION_DEBUG(TIME_SLICER, TIME_SLICE_FNAME) \`
- L121 _macro_ `#define MARK_TIMESLICE_SECTION_DEBUG(TIME_SLICER, TIME_SLICE_FNAME) ;`
- L588 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNavigationDirty, const FBox&);` — delegate type for events that dirty the navigation data ( Params: const FBox& DirtyBounds )

### `Source/Runtime/NavigationSystem/Public/NavigationSystemModule.h` (Public)


#### class `INavSysModule`  
`class INavSysModule : public IModuleInterface`  
_L14-39_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L25 _public function_ `static inline INavSysModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Source/Runtime/NavigationSystem/Public/NavigationSystemTypes.h` (Public)


#### struct `FPathFindingQueryData`  
`struct FPathFindingQueryData`  
_L28-51_
- L30 _public member_ `TWeakObjectPtr<const UObject> Owner;`
- L31 _public member_ `FVector StartLocation;`
- L32 _public member_ `FVector EndLocation;`
- L33 _public member_ `FSharedConstNavQueryFilter QueryFilter;`
- L36 _public member_ `FVector::FReal CostLimit;` — cost limit of nodes allowed to be added to the open list
- L39 _public member_ `int32 NavDataFlags;` — additional flags passed to navigation data handling request
- L42 _public member_ `uint32 bAllowPartialPaths : 1;` — if set, allow partial paths as a result
- L45 _public member_ `uint32 bRequireNavigableEndLocation : 1;` — if set, require the end location to be linked to the navigation data
- L47 _public function_ `FPathFindingQueryData() : StartLocation(FNavigationSystem::InvalidLocation), EndLocation(FNavigationSystem::InvalidLocation), CostLimit(TNumericLimits<FVector::FReal>::Max()), NavDataFlags(0), bAllowPartialPaths(true), bRequireNavigableEndLocation(true)`
- L49 _public function_ `FPathFindingQueryData(const UObject* InOwner, const FVector& InStartLocation, const FVector& InEndLocation, FSharedConstNavQueryFilter InQueryFilter = nullptr, int32 InNavDataFlags = 0, bool bInAllowPartialPaths = true, const FVector::FReal InCostLimit = TNumericLimits<FVector::FReal>::Max(), const bool bInRequireNavigableEndLocation = true) : Owner(InOwner), StartLocation(InStartLocation), EndLocation(InEndLocation), QueryFilter(InQueryFilter), CostLimit(InCostLimit), NavDataFlags(InNavDataFlags), bAllowPartialPaths(bInAllowPartialPaths), bRequireNavigableEndLocation(bInRequireNavigableEndLocation)`

#### struct `FPathFindingQuery`  
`struct FPathFindingQuery : public FPathFindingQueryData`  
_L53-74_
- inherits: `FPathFindingQueryData`
- L55 _public member_ `TWeakObjectPtr<const ANavigationData> NavData;`
- L56 _public member_ `FNavPathSharedPtr PathInstanceToFill;`
- L57 _public member_ `FNavAgentProperties NavAgentProperties;`
- L59 _public function_ `FPathFindingQuery() : FPathFindingQueryData()`
- L60 _public prototype_ `FPathFindingQuery(const UObject* InOwner, const ANavigationData& InNavData, const FVector& Start, const FVector& End, FSharedConstNavQueryFilter SourceQueryFilter = NULL, FNavPathSharedPtr InPathInstanceToFill = NULL, const FVector::FReal CostLimit = TNumericLimits<FVector::FReal>::Max(), const bool bInRequireNavigableEndLocation = true);`
- L61 _public prototype_ `FPathFindingQuery(const INavAgentInterface& InNavAgent, const ANavigationData& InNavData, const FVector& Start, const FVector& End, FSharedConstNavQueryFilter SourceQueryFilter = NULL, FNavPathSharedPtr InPathInstanceToFill = NULL, const FVector::FReal CostLimit = TNumericLimits<FVector::FReal>::Max(), const bool bInRequireNavigableEndLocation = true);`
- L63 _public prototype_ `explicit FPathFindingQuery(FNavPathSharedRef PathToRecalculate, const ANavigationData* NavDataOverride = NULL);`
- L65 _public function_ `FPathFindingQuery& SetPathInstanceToUpdate(FNavPathSharedPtr InPathInstanceToFill)`
- L66 _public function_ `FPathFindingQuery& SetAllowPartialPaths(const bool bAllow)`
- L67 _public function_ `FPathFindingQuery& SetRequireNavigableEndLocation(const bool bRequire)`
- L68 _public function_ `FPathFindingQuery& SetNavAgentProperties(const FNavAgentProperties& InNavAgentProperties)`
- L73 _public prototype_ `static FVector::FReal ComputeCostLimitFromHeuristic(const FVector& StartPos, const FVector& EndPos, const FVector::FReal HeuristicScale, const FVector::FReal CostLimitFactor, const FVector::FReal MinimumCostLimit);` — utility function to compute a cost limit using an Euclidean heuristic, an heuristic scale and a cost limit factor CostLimitFactor: multiplier used to compute the cost limit value from the initial heuristic MinimumCostLimit: minimum clamping value used to prevent low cost limit for short path query

#### enum `EPathFindingMode::Type`  
`enum Type`  
_L78-82_
- L80 _public enumerator_ `Regular`
- L81 _public enumerator_ `Hierarchical`

#### struct `FMoveRequestCustomData`  
`struct FMoveRequestCustomData`  
_L89-91_
- desc: Custom data passed to movement requests.

#### struct `FNavigationInvokerRaw`  
`struct FNavigationInvokerRaw`  
_L99-108_
- L101 _public member_ `FVector Location;`
- L102 _public member_ `float RadiusMin;`
- L103 _public member_ `float RadiusMax;`
- L104 _public member_ `FNavAgentSelector SupportedAgents;`
- L105 _public member_ `ENavigationInvokerPriority Priority;`
- L107 _public prototype_ `FNavigationInvokerRaw(const FVector& InLocation, float Min, float Max, const FNavAgentSelector& InSupportedAgents, ENavigationInvokerPriority InPriority);`

#### struct `FNavigationInvoker`  
`struct FNavigationInvoker`  
_L112-137_
- L115 _public member_ `TWeakObjectPtr<AActor> Actor;` — The Invoker source should be either an Actor or an Object. Thus only 1 of those member should be set. We'll use IsExplicitlyNull to know which one to use
- L116 _public member_ `TWeakInterfacePtr<INavigationInvokerInterface> Object;`
- L119 _public member_ `float GenerationRadius;` — tiles GenerationRadius away or close will be generated if they're not already present
- L123 _public member_ `float RemovalRadius;` — tiles over RemovalRadius will get removed. @Note needs to be >= GenerationRadius or will get clamped
- L126 _public member_ `FNavAgentSelector SupportedAgents;` — restrict navigation generation to specific agents
- L129 _public member_ `ENavigationInvokerPriority Priority;` — invoker Priority used when dirtying tiles
- L131 _public prototype_ `FNavigationInvoker();`
- L132 _public prototype_ `FNavigationInvoker(AActor& InActor, float InGenerationRadius, float InRemovalRadius, const FNavAgentSelector& InSupportedAgents, ENavigationInvokerPriority InPriority);`
- L133 _public prototype_ `FNavigationInvoker(INavigationInvokerInterface& InObject, float InGenerationRadius, float InRemovalRadius, const FNavAgentSelector& InSupportedAgents, ENavigationInvokerPriority InPriority);`
- L135 _public prototype_ `FString GetName() const;`
- L136 _public prototype_ `bool GetLocation(FVector& OutLocation) const;`

#### enum `FNavigationSystem::ECreateIfMissing`  
`enum ECreateIfMissing`  
_L150-155_
- L152 _public enumerator_ `Invalid = -1`
- L153 _public enumerator_ `DontCreate = 0`
- L154 _public enumerator_ `Create = 1`

#### struct `NavigationHelper::FNavLinkOwnerData`  
`struct FNavLinkOwnerData`  
_L166-174_
- L168 _public member_ `const AActor* Actor;`
- L169 _public member_ `FTransform LinkToWorld;`
- L171 _public function_ `FNavLinkOwnerData() : Actor(nullptr)`
- L172 _public prototype_ `FNavLinkOwnerData(const AActor& InActor);`
- L173 _public prototype_ `FNavLinkOwnerData(const USceneComponent& InComponent);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define NAVSYS_DEBUG (0 && UE_BUILD_DEBUG)`
- L11 _macro_ `#define RECAST_INTERNAL_DEBUG_DATA (!UE_BUILD_SHIPPING)`
- L25 _typedef_ `typedef TSharedPtr<const FNavigationQueryFilter, ESPMode::ThreadSafe> FSharedConstNavQueryFilter;`
- L26 _typedef_ `typedef TSharedPtr<struct FNavigationPath, ESPMode::ThreadSafe> FNavPathSharedPtr;`
- L76 _namespace_ `namespace EPathFindingMode`
- L93 _typedef_ `typedef TSharedPtr<FMoveRequestCustomData, ESPMode::ThreadSafe> FCustomMoveSharedPtr;`
- L94 _typedef_ `typedef TWeakPtr<FMoveRequestCustomData, ESPMode::ThreadSafe> FCustomMoveWeakPtr;`
- L139 _namespace_ `namespace NavigationHelper`
- L141 _prototype_ `void GatherCollision(UBodySetup* RigidBody, TNavStatArray<FVector>& OutVertexBuffer, TNavStatArray<int32>& OutIndexBuffer, const FTransform& ComponentToWorld = FTransform::Identity);` (scope `NavigationHelper`)
- L142 _prototype_ `void GatherCollision(UBodySetup* RigidBody, UNavCollision* NavCollision);` (scope `NavigationHelper`)
- L145 _prototype_ `void GatherCollision(const FKAggregateGeom& AggGeom, UNavCollision& NavCollision);` (scope `NavigationHelper`) — gather collisions from aggregated geom, convex and tri mesh elements are not supported - use override with full UBodySetup param instead
- L148 _namespace_ `namespace FNavigationSystem`
- L157 _typedef_ `typedef ECreateIfMissing ECreateIfEmpty;` (scope `FNavigationSystem`)
- L164 _namespace_ `namespace NavigationHelper`
- L176 _delegate_ `DECLARE_DELEGATE_ThreeParams(FNavLinkProcessorDelegate, FCompositeNavModifier*, const AActor*, const TArray<FNavigationLink>&);`
- L176 _prototype_ `DECLARE_DELEGATE_ThreeParams(FNavLinkProcessorDelegate, FCompositeNavModifier*, const AActor*, const TArray<FNavigationLink>&);` (scope `NavigationHelper`)
- L177 _delegate_ `DECLARE_DELEGATE_ThreeParams(FNavLinkSegmentProcessorDelegate, FCompositeNavModifier*, const AActor*, const TArray<FNavigationSegmentLink>&);`
- L177 _prototype_ `DECLARE_DELEGATE_ThreeParams(FNavLinkSegmentProcessorDelegate, FCompositeNavModifier*, const AActor*, const TArray<FNavigationSegmentLink>&);` (scope `NavigationHelper`)
- L179 _delegate_ `DECLARE_DELEGATE_ThreeParams(FNavLinkProcessorDataDelegate, FCompositeNavModifier*, const FNavLinkOwnerData&, const TArray<FNavigationLink>&);`
- L179 _prototype_ `DECLARE_DELEGATE_ThreeParams(FNavLinkProcessorDataDelegate, FCompositeNavModifier*, const FNavLinkOwnerData&, const TArray<FNavigationLink>&);` (scope `NavigationHelper`)
- L180 _delegate_ `DECLARE_DELEGATE_ThreeParams(FNavLinkSegmentProcessorDataDelegate, FCompositeNavModifier*, const FNavLinkOwnerData&, const TArray<FNavigationSegmentLink>&);`
- L180 _prototype_ `DECLARE_DELEGATE_ThreeParams(FNavLinkSegmentProcessorDataDelegate, FCompositeNavModifier*, const FNavLinkOwnerData&, const TArray<FNavigationSegmentLink>&);` (scope `NavigationHelper`)
- L186 _prototype_ `void SetNavLinkProcessorDelegate(const FNavLinkProcessorDataDelegate& NewDelegate);` (scope `NavigationHelper`) — Set new implementation of nav link processor, a function that will be be used to process/transform links before adding them to CompositeModifier. This function is supposed to be called once during the engine/game setup phase. Not intended to be toggled at runtime
- L187 _prototype_ `void SetNavLinkSegmentProcessorDelegate(const FNavLinkSegmentProcessorDataDelegate& NewDelegate);` (scope `NavigationHelper`)
- L190 _prototype_ `void ProcessNavLinkAndAppend(FCompositeNavModifier* OUT CompositeModifier, const AActor* Actor, const TArray<FNavigationLink>& IN NavLinks);` (scope `NavigationHelper`) — called to do any necessary processing on NavLinks and put results in CompositeModifier
- L191 _prototype_ `void ProcessNavLinkAndAppend(FCompositeNavModifier* OUT CompositeModifier, const FNavLinkOwnerData& OwnerData, const TArray<FNavigationLink>& IN NavLinks);` (scope `NavigationHelper`)
- L194 _prototype_ `void ProcessNavLinkSegmentAndAppend(FCompositeNavModifier* OUT CompositeModifier, const AActor* Actor, const TArray<FNavigationSegmentLink>& IN NavLinks);` (scope `NavigationHelper`) — called to do any necessary processing on NavLinks and put results in CompositeModifier
- L195 _prototype_ `void ProcessNavLinkSegmentAndAppend(FCompositeNavModifier* OUT CompositeModifier, const FNavLinkOwnerData& OwnerData, const TArray<FNavigationSegmentLink>& IN NavLinks);` (scope `NavigationHelper`)
- L197 _prototype_ `void DefaultNavLinkProcessorImpl(FCompositeNavModifier* OUT CompositeModifier, const FNavLinkOwnerData& OwnerData, const TArray<FNavigationLink>& IN NavLinks);` (scope `NavigationHelper`)
- L198 _prototype_ `void DefaultNavLinkSegmentProcessorImpl(FCompositeNavModifier* OUT CompositeModifier, const FNavLinkOwnerData& OwnerData, const TArray<FNavigationSegmentLink>& IN NavLinks);` (scope `NavigationHelper`)
- L200 _prototype_ `bool IsBodyNavigationRelevant(const UBodySetup& IN BodySetup);` (scope `NavigationHelper`)

### `Source/Runtime/NavigationSystem/Public/NavigationTestingActor.h` (Public)


#### struct `FNavTestTickHelper`  
`struct FNavTestTickHelper : FTickableGameObject`  
_L19-28_
- inherits: `FTickableGameObject`
- L21 _public member_ `TWeakObjectPtr<ANavigationTestingActor> Owner;`
- L23 _public function_ `FNavTestTickHelper() : Owner(NULL)`
- L24 _public prototype_ `virtual void Tick(float DeltaTime);`
- L25 _public function_ `virtual bool IsTickable() const`
- L26 _public function_ `virtual bool IsTickableInEditor() const`
- L27 _public prototype_ `virtual TStatId GetStatId() const ;`

#### enum `ENavCostDisplay::Type`  
`enum Type : int`  
_L33-38_
- L35 _public enumerator_ `TotalCost`
- L36 _public enumerator_ `HeuristicOnly`
- L37 _public enumerator_ `RealCostOnly`

#### class `ANavigationTestingActor`  
`class ANavigationTestingActor : public AActor, public INavAgentInterface, public INavPathObserverInterface`  
_L42-266_
- reflection: `UCLASS(hidecategories=(Object, Actor, Input, Rendering, Replication, HLOD, Cooking), showcategories=("Input|MouseInput", "Input|TouchInput"), Blueprintable, MinimalAPI)`
- inherits: `AActor,INavAgentInterface,INavPathObserverInterface`
- L48 _private member_ `TObjectPtr<class UCapsuleComponent> CapsuleComponent;` — `UPROPERTY()`
- L53 _private member_ `TObjectPtr<class UNavTestRenderingComponent> EdRenderComp;` — `UPROPERTY()` — Editor Preview
- L57 _private member_ `TObjectPtr<UNavigationInvokerComponent> InvokerComponent;` — `UPROPERTY(EditAnywhere, Category = Navigation, meta=(EditCondition="bActAsNavigationInvoker"))`
- L60 _private member_ `uint32 bActAsNavigationInvoker : 1;` — `UPROPERTY(EditAnywhere, Category = Navigation, meta=(InlineEditConditionToggle))`
- L66 _public member_ `FNavAgentProperties NavAgentProps;` — `UPROPERTY(EditAnywhere, Category=Agent)` — @todo document
- L69 _public member_ `FVector QueryingExtent;` — `UPROPERTY(EditAnywhere, Category=Agent)`
- L72 _public member_ `TObjectPtr<ANavigationData> MyNavData;` — `UPROPERTY(transient)`
- L75 _public member_ `FVector ProjectedLocation;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=AgentStatus)`
- L78 _public member_ `uint32 bProjectedLocationValid : 1;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=AgentStatus)`
- L82 _public member_ `uint32 bSearchStart : 1;` — `UPROPERTY(EditAnywhere, Category=Pathfinding)` — if set, start the search from this actor, else start the search from the other actor
- L87 _public member_ `float CostLimitFactor;` — `UPROPERTY(EditAnywhere, Category=Pathfinding, meta = (ClampMin = "0", UIMin = "0"))` — this multiplier is used to compute a max node cost allowed to the open list (cost limit = CostLimitFactor*InitialHeuristicEstimate)
- L92 _public member_ `float MinimumCostLimit;` — `UPROPERTY(EditAnywhere, Category = Pathfinding, meta = (ClampMin = "0", UIMin = "0"))` — minimum cost limit clamping value (in cost units) used to allow large deviation in short paths
- L99 _public member_ `uint32 bBacktracking : 1;` — `UPROPERTY(EditAnywhere, Category = Pathfinding)` — Instead of regular pathfinding from source to target location do a 'backwards' search that searches from the source, but as if the allowed movement direction was coming from the target. Meaningful only for paths containing one-direction nav links.
- L102 _public member_ `uint32 bUseHierarchicalPathfinding : 1;` — `UPROPERTY(EditAnywhere, Category=Pathfinding)`
- L106 _public member_ `uint32 bGatherDetailedInfo : 1;` — `UPROPERTY(EditAnywhere, Category=Pathfinding)` — if set, all steps of A* algorithm will be accessible for debugging
- L110 _public member_ `uint32 bRequireNavigableEndLocation : 1;` — `UPROPERTY(EditAnywhere, Category=Pathfinding)` — if set, require the end location to be close to the navigation data. The tolerance is controlled by QueryingExtent
- L113 _public member_ `uint32 bDrawDistanceToWall : 1;` — `UPROPERTY(EditAnywhere, Category=Query)`
- L117 _public member_ `uint32 bDrawIfNavDataIsReadyInRadius : 1;` — `UPROPERTY(EditAnywhere, Category=Query)` — If set, a cylinder is drawn to indicate if the navigation data is ready (has been generated) for the given radius (green when ready, red otherwise).
- L121 _public member_ `uint32 bDrawIfNavDataIsReadyToQueryTargetActor : 1;` — `UPROPERTY(EditAnywhere, Category=Query)` — If set, a capsule is drawn to indicate if the navigation data is ready (has been generated) for the given radius from the current actor to the query target (green when ready, red otherwise).
- L126 _public member_ `uint32 bDrawRaycastToQueryTargetActor : 1;` — `UPROPERTY(EditAnywhere, Category=Query)` — If set, a line is drawn to indicate to result of a ray cast on the navigation data between the current actor and the QueryTargetActor location (red when there is a hit, green when there is no hit and the ray end is on the explored corridor, orange otherwise).
- L130 _public member_ `TObjectPtr<AActor> QueryTargetActor;` — `UPROPERTY(EditAnywhere, Category=Query)` — Actor to use as a target for navigation data queries
- L134 _public member_ `uint32 bShowNodePool : 1;` — `UPROPERTY(EditAnywhere, Category=Debug)` — show polys from open (orange) and closed (yellow) sets
- L138 _public member_ `uint32 bShowBestPath : 1;` — `UPROPERTY(EditAnywhere, Category=Debug)` — show current best path
- L142 _public member_ `uint32 bShowDiffWithPreviousStep : 1;` — `UPROPERTY(EditAnywhere, Category=Debug)` — show which nodes were modified in current A* step
- L145 _public member_ `uint32 bShouldBeVisibleInGame : 1;` — `UPROPERTY(EditAnywhere, Category=Debug)`
- L149 _public member_ `float RadiusUsedToValidateNavData = 0;` — `UPROPERTY(EditAnywhere, Category=Query)` — NavData must be ready for all tiles within radius. When using 0, NavData must be ready at the actor location.
- L153 _public member_ `TEnumAsByte<ENavCostDisplay::Type> CostDisplayMode;` — `UPROPERTY(EditAnywhere, Category=Debug)` — determines which cost will be shown
- L157 _public member_ `FVector2D TextCanvasOffset;` — `UPROPERTY(EditAnywhere, Category=Debug)` — text canvas offset to apply
- L160 _public member_ `uint32 bPathExist : 1;` — `UPROPERTY(transient, VisibleAnywhere, BlueprintReadOnly, Category=PathfindingStatus)`
- L163 _public member_ `uint32 bPathIsPartial : 1;` — `UPROPERTY(transient, VisibleAnywhere, BlueprintReadOnly, Category=PathfindingStatus)`
- L166 _public member_ `uint32 bPathSearchOutOfNodes : 1;` — `UPROPERTY(transient, VisibleAnywhere, BlueprintReadOnly, Category=PathfindingStatus)`
- L170 _public member_ `float PathfindingTime;` — `UPROPERTY(transient, VisibleAnywhere, BlueprintReadOnly, Category=PathfindingStatus)` — Time in micro seconds
- L173 _public member_ `double PathCost;` — `UPROPERTY(transient, VisibleAnywhere, BlueprintReadOnly, Category=PathfindingStatus)`
- L176 _public member_ `int32 PathfindingSteps;` — `UPROPERTY(transient, VisibleAnywhere, BlueprintReadOnly, Category=PathfindingStatus)`
- L179 _public member_ `TObjectPtr<ANavigationTestingActor> OtherActor;` — `UPROPERTY(EditAnywhere, Category=Pathfinding)`
- L183 _public member_ `TSubclassOf<class UNavigationQueryFilter> FilterClass;` — `UPROPERTY(EditAnywhere, Category=Query)` — "None" will result in default filter being used. This filter is used by the PathFind and Raycast queries.
- L187 _public member_ `int32 ShowStepIndex;` — `UPROPERTY(EditInstanceOnly, Category=Debug, meta=(ClampMin="-1", UIMin="-1"))` — Show debug steps up to this index. Use -1 to disable.
- L190 _public member_ `float OffsetFromCornersDistance;` — `UPROPERTY(EditAnywhere, Category=Pathfinding)`
- L192 _public member_ `FVector ClosestWallLocation;`
- L193 _public member_ `FVector RaycastHitLocation;`
- L195 _public member_ `bool bNavDataIsReadyInRadius;`
- L196 _public member_ `bool bNavDataIsReadyToQueryTargetActor;`
- L197 _public member_ `bool bRaycastToQueryTargetActorResult;`
- L198 _public member_ `bool bRaycastToQueryTargetEndsInCorridor;`
- L202 _public member_ `TArray<struct FRecastDebugPathfindingData> DebugSteps;` — detail data gathered from each step of regular A* algorithm
- L204 _public member_ `FNavTestTickHelper* TickHelper;`
- L207 _public member_ `FNavPathSharedPtr LastPath;`
- L208 _public member_ `FNavigationPath::FPathObserverDelegate::FDelegate PathObserver;`
- L211 _public prototype_ `virtual ~ANavigationTestingActor();` — Dtor
- L213 _public prototype_ `virtual void BeginDestroy() override;`
- L216 _public prototype_ `virtual void PreEditChange(FProperty* PropertyThatWillChange) override;`
- L217 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L218 _public prototype_ `virtual void PostEditMove(bool bFinished) override;`
- L220 _public prototype_ `virtual void PostLoad() override;`
- L221 _public prototype_ `void TickMe();`
- L225 _public function_ `virtual const FNavAgentProperties& GetNavAgentPropertiesRef() const override`
- L226 _public prototype_ `virtual FVector GetNavAgentLocation() const override;`
- L227 _public function_ `virtual void GetMoveGoalReachTest(const AActor* MovingActor, const FVector& MoveOffset, FVector& GoalOffset, float& GoalRadius, float& GoalHalfHeight) const override`
- L231 _public function_ `virtual void OnPathUpdated(class INavigationPathGenerator* PathGenerator) override`
- L232 _public function_ `virtual void OnPathInvalid(class INavigationPathGenerator* PathGenerator) override`
- L233 _public function_ `virtual void OnPathFailed(class INavigationPathGenerator* PathGenerator) override`
- L236 _public prototype_ `void UpdateNavData();`
- L237 _public prototype_ `void UpdatePathfinding();`
- L238 _public prototype_ `virtual void SearchPathTo(ANavigationTestingActor* Goal);`
- L243 _public prototype_ `void OnPathEvent(FNavigationPath* InvalidatedPath, ENavPathEvent::Type Event);` — Called when given path becomes invalid (via @see PathObserverDelegate) NOTE: InvalidatedPath doesn't have to be instance's current Path
- L248 _public prototype_ `virtual FPathFindingQuery BuildPathFindingQuery(const ANavigationTestingActor* Goal) const;` — Virtual method to override if you want to customize the query being constructed for the path find (e.g. change the filter or add constraints/goal evaluators).
- L251 _public function_ `class UCapsuleComponent* GetCapsuleComponent() const` — Returns CapsuleComponent subobject
- L254 _public function_ `class UNavTestRenderingComponent* GetEdRenderComp() const` — Returns EdRenderComp subobject
- L258 _protected prototype_ `void UpdateLocalQueries();`
- L259 _protected prototype_ `void UpdateTargetActorQueries();`
- L261 _protected prototype_ `FVector FindClosestWallLocation() const;`
- L262 _protected prototype_ `bool CheckIfNavDataIsReadyInRadius();`
- L263 _protected prototype_ `bool CheckIfNavDataIsReadyToActor(const AActor* TargetActor);`
- L264 _protected prototype_ `bool CheckRaycastToActor(const AActor* TargetActor, FVector& OutHitLocation, bool& bOutIsRaycastEndInCorridor);`
- L265 _protected prototype_ `void OnQueryTargetActorTransformUpdated(USceneComponent* InRootComponent, EUpdateTransformFlags UpdateTransformFlags, ETeleportType Teleport);`

#### Free symbols / members of external scopes

- L31 _namespace_ `namespace ENavCostDisplay`

### `Source/Runtime/NavigationSystem/Public/SplineNavModifierComponent.h` (Public)


#### enum `ESubdivisionLOD`  
`enum class ESubdivisionLOD`  
_L13-19_
- reflection: `UENUM()`
- L15 _public enumerator_ `Low`
- L16 _public enumerator_ `Medium`
- L17 _public enumerator_ `High`
- L18 _public enumerator_ `Ultra`

#### class `USplineNavModifierComponent`  
`class USplineNavModifierComponent : public UNavModifierComponent`  
_L26-83_
- reflection: `UCLASS(Blueprintable, MinimalAPI, Meta = (BlueprintSpawnableComponent), hidecategories = (Variable, Tags, Cooking, Collision))`
- inherits: `UNavModifierComponent`
- desc: Used to assign a chosen NavArea to the nav mesh in the vicinity of a chosen spline. A tube is constructed around the spline and intersected with the nav mesh. Set its dimensions with StrokeWidth and StrokeHeight.
- L35 _private member_ `bool bUpdateNavDataOnSplineChange = true;` — `UPROPERTY(EditAnywhere, Category = Navigation)` — If true, any changes to Spline Components on this actor will cause this component to update the nav mesh. This will be slow if the spline has many points, or the nav mesh is sufficiently large.
- L39 _private member_ `FComponentReference AttachedSpline;` — `UPROPERTY(EditAnywhere, Category = Navigation, Meta = (UseComponentPicker, AllowedClasses = "/Script/Engine.SplineComponent", DisplayName = "Nav Modifier Spline"))` — The SplineComponent which will modify the nav mesh; it must also be attached to this component's owner actor
- L43 _private member_ `double StrokeWidth = 500.0f;` — `UPROPERTY(EditAnywhere, Category = Navigation, Meta=(UIMin="10", ClampMin="10"))` — Cross-sectional width of the tube enclosing the spline
- L47 _private member_ `double StrokeHeight = 500.0f;` — `UPROPERTY(EditAnywhere, Category = Navigation, Meta=(UIMin="10", ClampMin="10"))` — Cross-sectional height of the tube enclosing the spline
- L51 _private member_ `ESubdivisionLOD SubdivisionLOD = ESubdivisionLOD::Medium;` — `UPROPERTY(EditAnywhere, Category = Navigation)` — Higher LOD will capture finer details in the spline
- L53 _private prototype_ `USplineNavModifierComponent(const FObjectInitializer& ObjectInitializer);`
- L62 _private prototype_ `void UpdateNavigationWithComponentData();` — `UFUNCTION(CallInEditor, Category = Navigation, Meta=(DisplayName="UpdateNavigationData"))` — Recalculates bounds, then re-computes the NavModifierVolumes and re-marks the nav mesh. Disable UpdateNavDataOnSplineChange and use this to manually update when either the spline or nav mesh is too large to handle rapid updates. Does nothing in non-editor builds
- L66 _protected prototype_ `virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L67 _protected prototype_ `virtual bool IsComponentTickEnabled() const override;`
- L70 _protected prototype_ `virtual void CalculateBounds() const override;`
- L71 _protected prototype_ `virtual void GetNavigationData(FNavigationRelevantData& Data) const override;`
- L73 _protected prototype_ `float GetSubdivisionThreshold() const;`
- L78 _private member_ `uint32 SplineVersion = INVALID_SPLINE_VERSION;` — Used to check against attached spline's version each tick for changes
- L82 _private member_ `FTransform SplineTransform = FTransform();` — Used for bounds calculation and to check against attached spline's transform each tick for changes

#### Free symbols / members of external scopes

- L8 _macro_ `#define INVALID_SPLINE_VERSION MIN_int32`
