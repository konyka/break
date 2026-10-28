# Plugins / UnrealUSDWrapper

- module root: `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper`
- headers: 41; symbols: 1496
- symbol kinds: class=48, delegate=5, enum=17, enumerator=74, externvar=151, function=35, macro=20, member=108, namespace=79, prototype=914, struct=17, typedef=28
- PublicDependencyModuleNames: CinematicCamera, Core, CoreUObject, Engine, IntelTBB, Projects, Python3, USDClasses

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/USDIncludesEnd.h` (Public)
_(no declarations extracted)_

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/USDIncludesStart.h` (Public)


#### struct `boost::python::error_already_set`  
`struct BOOST_PYTHON_DECL error_already_set`  
_L63-66_
- L65 _public prototype_ `virtual ~error_already_set();`

#### Free symbols / members of external scopes

- L10 _macro_ `#define USD_INCLUDES_START`
- L33 _macro_ `#define _DEBUG`
- L47 _macro_ `#define try` — We can define these out, but USD uses 'throw' as well, which is also not allowed with no-exceptions
- L48 _macro_ `#define catch(...) if(false)`
- L56 _macro_ `#define ERRORS_DWA052500_H_`
- L59 _namespace_ `namespace boost`
- L61 _namespace_ `namespace python` (scope `boost`)
- L67 _prototype_ `BOOST_PYTHON_DECL bool handle_exception_impl( function0<void> );` (scope `boost::python`)
- L68 _prototype_ `BOOST_PYTHON_DECL void throw_error_already_set();` (scope `boost::python`)
- L69 _function_ `template <class T> inline T* expect_non_null( T* x )` (scope `boost::python`)
- L70 _prototype_ `template <class T> inline T* expect_non_null( T* x )` (scope `boost::python`)

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/USDListener.h` (Public)


#### struct `UsdUtils::FPrimChangeFlags`  
`struct FPrimChangeFlags`  
_L25-56_
- desc: Analogous to pxr::SdfChangeList::Entry::_Flags
- L27 _public member_ `bool bDidChangeIdentifier : 1;`
- L28 _public member_ `bool bDidChangeResolvedPath : 1;`
- L29 _public member_ `bool bDidReplaceContent : 1;`
- L30 _public member_ `bool bDidReloadContent : 1;`
- L31 _public member_ `bool bDidReorderChildren : 1;`
- L32 _public member_ `bool bDidReorderProperties : 1;`
- L33 _public member_ `bool bDidRename : 1;`
- L34 _public member_ `bool bDidChangePrimVariantSets : 1;`
- L35 _public member_ `bool bDidChangePrimInheritPaths : 1;`
- L36 _public member_ `bool bDidChangePrimSpecializes : 1;`
- L37 _public member_ `bool bDidChangePrimReferences : 1;`
- L38 _public member_ `bool bDidChangeAttributeTimeSamples : 1;`
- L39 _public member_ `bool bDidChangeAttributeConnection : 1;`
- L40 _public member_ `bool bDidChangeRelationshipTargets : 1;`
- L41 _public member_ `bool bDidAddTarget : 1;`
- L42 _public member_ `bool bDidRemoveTarget : 1;`
- L43 _public member_ `bool bDidAddInertPrim : 1;`
- L44 _public member_ `bool bDidAddNonInertPrim : 1;`
- L45 _public member_ `bool bDidRemoveInertPrim : 1;`
- L46 _public member_ `bool bDidRemoveNonInertPrim : 1;`
- L47 _public member_ `bool bDidAddPropertyWithOnlyRequiredFields : 1;`
- L48 _public member_ `bool bDidAddProperty : 1;`
- L49 _public member_ `bool bDidRemovePropertyWithOnlyRequiredFields : 1;`
- L50 _public member_ `bool bDidRemoveProperty : 1;`
- L52 _public function_ `FPrimChangeFlags()`

#### struct `UsdUtils::FFieldChange`  
`struct FFieldChange`  
_L62-67_
- desc: Analogous to pxr::SdfChangeList::Entry::InfoChange, describes a change to an attribute. Here we break off PropertyName and Field for simplicity
- L64 _public member_ `FString Field;` — default, variability, timeSamples, etc.
- L65 _public member_ `UE::FVtValue OldValue;` — Can be empty when we create a new attribute opinion
- L66 _public member_ `UE::FVtValue NewValue;` — Can be empty when we clear an existing attribute opinion

#### enum `UsdUtils::ESubLayerChangeType`  
`enum ESubLayerChangeType`  
_L71-76_
- desc: Analogous to pxr::SdfChangeList::SubLayerChangeType, describes a change to a sublayer
- L73 _public enumerator_ `SubLayerAdded`
- L74 _public enumerator_ `SubLayerRemoved`
- L75 _public enumerator_ `SubLayerOffset`

#### struct `UsdUtils::FSdfChangeListEntry`  
`struct FSdfChangeListEntry`  
_L79-86_
- desc: Analogous to pxr::SdfChangeList::Entry, describes a generic change to an object
- L81 _public member_ `TArray<FFieldChange> FieldChanges;`
- L82 _public member_ `FPrimChangeFlags Flags;`
- L83 _public member_ `FString OldPath;` — Empty if Flags.bDidRename is not set
- L84 _public member_ `FString OldIdentifier;` — Empty if Flags.bDIdChangeIdentifier is not set
- L85 _public member_ `TArray<TPair<FString, ESubLayerChangeType>> SubLayerChanges;`

#### class `FUsdListener`  
`class FUsdListener`  
_L102-142_
- desc: Registers to Usd Notices and emits events when the Usd Stage has changed
- L105 _public prototype_ `FUsdListener();`
- L106 _public prototype_ `FUsdListener(const UE::FUsdStage& Stage);`
- L108 _public prototype_ `FUsdListener(const FUsdListener& Other) = delete;`
- L109 _public prototype_ `FUsdListener(FUsdListener&& Other) = delete;`
- L111 _public prototype_ `virtual ~FUsdListener();`
- L113 _public prototype_ `FUsdListener& operator=(const FUsdListener& Other) = delete;`
- L114 _public prototype_ `FUsdListener& operator=(FUsdListener&& Other) = delete;`
- L116 _public prototype_ `void Register(const UE::FUsdStage& Stage);`
- L119 _public prototype_ `void Block();` — Increment/decrement the block counter
- L120 _public prototype_ `void Unblock();`
- L121 _public prototype_ `bool IsBlocked() const;`
- L124 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE(FOnStageEditTargetChanged);` — Stage-specific events
- L125 _public prototype_ `FOnStageEditTargetChanged& GetOnStageEditTargetChanged();`
- L127 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnSdfLayersChanged, const UsdUtils::FLayerToSdfChangeList&);`
- L128 _public prototype_ `FOnSdfLayersChanged& GetOnSdfLayersChanged();`
- L130 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE(FOnSdfLayerDirtinessChanged);`
- L131 _public prototype_ `FOnSdfLayerDirtinessChanged& GetOnSdfLayerDirtinessChanged();`
- L133 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams( FOnObjectsChanged, const UsdUtils::FObjectChangesByPath& , const UsdUtils::FObjectChangesByPath& );`
- L138 _public prototype_ `FOnObjectsChanged& GetOnObjectsChanged();`
- L141 _private member_ `TUniquePtr<FUsdListenerImpl> Impl;`

#### class `FScopedBlockNotices`  
`class FScopedBlockNotices final`  
_L144-158_
- L147 _public prototype_ `explicit FScopedBlockNotices(FUsdListener& InListener);`
- L148 _public prototype_ `~FScopedBlockNotices();`
- L150 _public prototype_ `FScopedBlockNotices() = delete;`
- L151 _public prototype_ `FScopedBlockNotices(const FScopedBlockNotices&) = delete;`
- L152 _public prototype_ `FScopedBlockNotices(FScopedBlockNotices&&) = delete;`
- L153 _public prototype_ `FScopedBlockNotices& operator=(const FScopedBlockNotices&) = delete;`
- L154 _public prototype_ `FScopedBlockNotices& operator=(FScopedBlockNotices&&) = delete;`
- L157 _private member_ `FUsdListener& Listener;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API UNREALUSDWRAPPER_API`
- L17 _namespace_ `namespace UE`
- L22 _namespace_ `namespace UsdUtils`
- L68 _typedef_ `using FAttributeChange = FFieldChange;` (scope `UsdUtils`) — Renamed in 5.6 as this can refer to a relationship, or even prim metadata
- L88 _typedef_ `using FObjectChangeNotice = FSdfChangeListEntry;` (scope `UsdUtils`) — Renamed in 5.3 as it is used for layer changes now too
- L90 _typedef_ `using FSdfChangeList = TArray<TPair<UE::FSdfPath, FSdfChangeListEntry>>;` (scope `UsdUtils`)
- L91 _typedef_ `using FLayerToSdfChangeList = TArray<TPair<UE::FSdfLayerWeak, FSdfChangeList>>;` (scope `UsdUtils`)
- L96 _typedef_ `using FObjectChangesByPath = TCaseSensitiveStringMap<TArray<FSdfChangeListEntry>>;` (scope `UsdUtils`) — Describes USD object changes by object path (an object can be a prim, a property, etc.)
- L124 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE(FOnStageEditTargetChanged);` — Stage-specific events
- L127 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnSdfLayersChanged, const UsdUtils::FLayerToSdfChangeList&);`
- L130 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE(FOnSdfLayerDirtinessChanged);`
- L133 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams( FOnObjectsChanged, const UsdUtils::FObjectChangesByPath& , const UsdUtils::FObjectChangesByPath& );`

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/USDMemory.h` (Public)


#### enum `EUsdActiveAllocator`  
`enum class EUsdActiveAllocator`  
_L93-99_
- L96 _public enumerator_ `Unreal` — Redirects operator new and delete to FMemory::Malloc and FMemory::Free
- L98 _public enumerator_ `System` — Redirects operator new and delete to FMemory::SystemMalloc and FMemory::SystemFree

#### class `FUsdMemoryManager`  
`class FUsdMemoryManager`  
_L103-160_
- L106 _public prototype_ `static void Initialize();`
- L107 _public prototype_ `static void Shutdown();`
- L110 _public prototype_ `static void ActivateAllocator(EUsdActiveAllocator Allocator);` — Pushes Allocator on the stack of active allocators
- L113 _public prototype_ `static bool DeactivateAllocator(EUsdActiveAllocator Allocator);` — Pops Allocator from the stack of active allocators
- L116 _public prototype_ `static void* Malloc(SIZE_T Count);` — Redirects the call to malloc to the currently active allocator.
- L119 _public prototype_ `static void Free(void* Original);` — Redirects the call to free to the currently active allocator.
- L122 _private prototype_ `static FActiveAllocatorsStack& GetActiveAllocatorsStackForThread();`
- L125 _private prototype_ `static bool IsUsingSystemMalloc();` — Returns if the current active allocator is EActiveAllocator::System
- L127 _private member_ `static TOptional<FTlsSlot> ActiveAllocatorsStackTLS;`
- L157 _private member_ `static FThreadSafeSet SystemAllocedPtrs;`
- L159 _private member_ `static FCriticalSection CriticalSection;`

#### struct `FUsdMemoryManager::FThreadSafeSet`  
`struct FThreadSafeSet`  
_L129-155_
- L132 _public function_ `void Add(void* Ptr)`
- L139 _public function_ `bool Remove(void* Ptr)`
- L153 _private member_ `static constexpr int32 BucketCount = 61;`
- L154 _private member_ `FSubSet SubSets[BucketCount];` — static constexpr int32 BucketCount = 61;   Prime number for better modulo distribution

#### struct `FUsdMemoryManager::FThreadSafeSet::FSubSet`  
`struct FSubSet`  
_L147-151_
- L149 _public member_ `FRWLock Lock;`
- L150 _public member_ `TSet<void*> Set;`

#### class `TScopedAllocs`  
`template<EUsdActiveAllocator AllocatorType> class TScopedAllocs final`  
_L168-203_
- desc: Activates an allocator on construction and deactivates it on destruction
- L171 _public function_ `TScopedAllocs()`
- L191 _public function_ `~TScopedAllocs()`
- L198 _public prototype_ `TScopedAllocs(const TScopedAllocs<AllocatorType>& Other) = delete;`
- L199 _public prototype_ `TScopedAllocs(TScopedAllocs<AllocatorType>&& Other) = delete;`
- L201 _public prototype_ `TScopedAllocs& operator=(const TScopedAllocs<AllocatorType>& Other) = delete;`
- L202 _public prototype_ `TScopedAllocs& operator=(TScopedAllocs<AllocatorType>&& Other) = delete;`

#### class `TUsdStore`  
`template<typename UsdObjectType> class TUsdStore final`  
_L213-321_
- desc: Stores a USD object. Ensures that its constructed, copied, moved and destroyed using the USD allocator.
- L216 _public function_ `TUsdStore()`
- L226 _public function_ `TUsdStore(const TUsdStore<UsdObjectType>& Other)`
- L232 _public function_ `TUsdStore(TUsdStore<UsdObjectType>&& Other)`
- L238 _public function_ `TUsdStore<UsdObjectType>& operator=(const TUsdStore<UsdObjectType>& Other)`
- L245 _public function_ `TUsdStore<UsdObjectType>& operator=(TUsdStore<UsdObjectType>&& Other)`
- L252 _public function_ `TUsdStore(const UsdObjectType& UsdObject)`
- L258 _public function_ `TUsdStore(UsdObjectType&& UsdObject)`
- L264 _public function_ `TUsdStore<UsdObjectType>& operator=(const UsdObjectType& UsdObject)`
- L271 _public function_ `TUsdStore<UsdObjectType>& operator=(UsdObjectType&& UsdObject)`
- L278 _public function_ `explicit operator bool() const`
- L283 _public function_ `~TUsdStore()`
- L289 _public function_ `UsdObjectType& Get()`
- L294 _public function_ `const UsdObjectType& Get() const`
- L299 _public function_ `UsdObjectType& operator*()`
- L304 _public function_ `const UsdObjectType& operator*() const`
- L309 _public function_ `UsdObjectType* operator->()`
- L314 _public function_ `const UsdObjectType* operator->() const`
- L320 _private member_ `TOptional<UsdObjectType> StoredUsdObject;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API UNREALUSDWRAPPER_API`
- L21 _macro_ `#define USE_USD_MEMORY_MANAGER 0` — Default to 0 in case the USD SDK is not used Also, on Linux/Mac, the USD SDK doesn't need the memory overloads to support UE allocators so the USD memory manager is not needed
- L33 _macro_ `#define USE_USD_MEMORY_MANAGER 1`
- L205 _typedef_ `using FScopedUsdAllocs = TScopedAllocs<EUsdActiveAllocator::System>;`
- L206 _typedef_ `using FScopedUnrealAllocs = TScopedAllocs<EUsdActiveAllocator::Unreal>;`
- L324 _function_ `template<typename UsdObjectType, typename... ArgTypes> TUsdStore<UsdObjectType> MakeUsdStore(ArgTypes&&... Args)`
- L332 _function_ `template<typename ObjectType, typename... ArgTypes> TSharedRef<ObjectType> MakeSharedUnreal(ArgTypes&&... Args)` — MakeShared version that makes sure that the SharedPointer allocs are made with the Unreal allocator
- L342 _macro_ `#define REPLACEMENT_OPERATOR_NEW_AND_DELETE_USD \`
- L356 _macro_ `#define REPLACEMENT_OPERATOR_NEW_AND_DELETE_USD`
- L360 _macro_ `#define IMPLEMENT_MODULE_USD( ModuleImplClass, ModuleName ) \`
- L378 _macro_ `#define IMPLEMENT_MODULE_USD( ModuleImplClass, ModuleName ) IMPLEMENT_MODULE( ModuleImplClass, ModuleName )`

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UnrealUSDWrapper.h` (Public)


#### enum `EUsdInterpolationMethod`  
`enum class EUsdInterpolationMethod`  
_L62-72_
- L65 _public enumerator_ `Vertex` — Each element in a buffer maps directly to a specific vertex
- L67 _public enumerator_ `FaceVarying` — Each element in a buffer maps to a specific face/vertex pair
- L69 _public enumerator_ `Uniform` — Each vertex on a face is the same value
- L71 _public enumerator_ `Constant` — Single value

#### enum `EUsdGeomOrientation`  
`enum class EUsdGeomOrientation`  
_L74-80_
- L77 _public enumerator_ `RightHanded` — Right handed coordinate system
- L79 _public enumerator_ `LeftHanded` — Left handed coordinate system

#### enum `EUsdSubdivisionScheme`  
`enum class EUsdSubdivisionScheme`  
_L82-88_
- L84 _public enumerator_ `None`
- L85 _public enumerator_ `CatmullClark`
- L86 _public enumerator_ `Loop`
- L87 _public enumerator_ `Bilinear`

#### enum `EUsdPurpose`  
`enum class EUsdPurpose : int32`  
_L91-97_
- reflection: `UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L93 _public enumerator_ `Default = 0 UMETA(Hidden)`
- L94 _public enumerator_ `Proxy = 1`
- L95 _public enumerator_ `Render = 2`
- L96 _public enumerator_ `Guide = 4`

#### enum `EUsdDefaultKind`  
`enum class EUsdDefaultKind : int32`  
_L101-109_
- reflection: `UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L103 _public enumerator_ `None = 0 UMETA(Hidden)`
- L104 _public enumerator_ `Model = 1`
- L105 _public enumerator_ `Component = 2`
- L106 _public enumerator_ `Group = 4`
- L107 _public enumerator_ `Assembly = 8`
- L108 _public enumerator_ `Subcomponent = 16`

#### enum `EUsdLoadPolicy`  
`enum class EUsdLoadPolicy : uint8`  
_L114-118_
- reflection: `UENUM()`
- desc: Corresponds to pxr::UsdLoadPolicy, refer to the USD SDK documentation
- L116 _public enumerator_ `UsdLoadWithDescendants` — Load a prim plus all its descendants.
- L117 _public enumerator_ `UsdLoadWithoutDescendants` — Load a prim by itself with no descendants.

#### enum `EUsdInitialLoadSet`  
`enum class EUsdInitialLoadSet : uint8`  
_L121-125_
- reflection: `UENUM()`
- L123 _public enumerator_ `LoadAll`
- L124 _public enumerator_ `LoadNone`

#### enum `EUsdInterpolationType`  
`enum class EUsdInterpolationType : uint8`  
_L128-132_
- reflection: `UENUM()`
- L130 _public enumerator_ `Held`
- L131 _public enumerator_ `Linear`

#### enum `EUsdRootMotionHandling`  
`enum class EUsdRootMotionHandling : uint8`  
_L135-148_
- reflection: `UENUM()`
- L138 _public enumerator_ `NoAdditionalRootMotion` — Use for the root bone just its regular joint animation as described on the SkelAnimation prim.
- L143 _public enumerator_ `UseMotionFromSkelRoot` — Use the transform animation from the SkelRoot prim in addition to the root bone joint animation as described on the SkelAnimation prim. Note that the SkelRoot prim's Sequencer transform track will no longer contain the transform animation data used in this manner, so as to not apply the animation twice.
- L147 _public enumerator_ `UseMotionFromSkeleton` — Use the transform animation from the Skeleton prim in addition to the root bone joint animation as described on the SkelAnimation prim.

#### enum `EUsdCollisionType`  
`enum class EUsdCollisionType : uint8`  
_L151-176_
- reflection: `UENUM()`
- L154 _public enumerator_ `None` — No approximation so equivalent to CTF_UseComplexAsSimple
- L157 _public enumerator_ `ConvexDecomposition` — Breaks up concave meshes into multiple, simple convex collider primitives
- L160 _public enumerator_ `ConvexHull` — Single convex hull primitive around the mesh
- L163 _public enumerator_ `Sphere` — Single sphere collider
- L166 _public enumerator_ `Cube` — Single cube collider
- L169 _public enumerator_ `MeshSimplification` — Behaves the same as ConvexDecomposition in Unreal, it's just listed separately as it's a separate value in USD
- L172 _public enumerator_ `Capsule` — Single capsule collider
- L175 _public enumerator_ `CustomMesh` — Use a separate, dedicated collider mesh

#### enum `EGeometryCacheImport`  
`enum class EGeometryCacheImport : uint8`  
_L180-191_
- reflection: `UENUM()`
- desc: Stage option on how to handle geometry caches in stage workflow
- L183 _public enumerator_ `Never` — Never imported (no persistent assets); always streamed from the USD stage
- L186 _public enumerator_ `OnLoad` — Imported on stage load; played back from the persistent assets
- L190 _public enumerator_ `OnSave` — Imported on save; geometry caches are streamed from the stage until they are saved. Afterwards they are played back from the persistent assets

#### enum `EUsdListPosition`  
`enum class EUsdListPosition : uint8`  
_L195-220_
- reflection: `UENUM()`
- desc: Corresponds to pxr::UsdListPosition, refer to the USD SDK documentation
- L201 _public enumerator_ `FrontOfPrependList` — The position at the front of the prepend list. An item added at this position will, after composition is applied, be stronger than other items prepended in this layer, and stronger than items added by weaker layers.
- L207 _public enumerator_ `BackOfPrependList` — The position at the back of the prepend list. An item added at this position will, after composition is applied, be weaker than other items prepended in this layer, but stronger than items added by weaker layers.
- L213 _public enumerator_ `FrontOfAppendList` — The position at the front of the append list. An item added at this position will, after composition is applied, be stronger than other items appended in this layer, and stronger than items added by weaker layers.
- L219 _public enumerator_ `BackOfAppendList` — The position at the back of the append list. An item added at this position will, after composition is applied, be weaker than other items appended in this layer, but stronger than items added by weaker layers.

#### struct `FMatrix2D`  
`struct FMatrix2D`  
_L227-238_
- reflection: `USTRUCT(BlueprintType)`
- desc: Corresponds to pxr::GfMatrix2d. We don't expose any methods though, this is just to facilitate reading/writing these types from USD.
- L232 _public member_ `FVector2D Row0 = FVector2D(1.0, 0.0);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD")`
- L235 _public member_ `FVector2D Row1 = FVector2D(0.0, 1.0);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD")`
- L237 _public prototype_ `bool operator==(const FMatrix2D& Other) const = default;`

#### struct `FMatrix3D`  
`struct FMatrix3D`  
_L245-259_
- reflection: `USTRUCT(BlueprintType)`
- desc: Corresponds to pxr::GfMatrix3d. We don't expose any methods though, this is just to facilitate reading/writing these types from USD.
- L250 _public member_ `FVector Row0 = FVector(1.0, 0.0, 0.0);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD")`
- L253 _public member_ `FVector Row1 = FVector(0.0, 1.0, 0.0);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD")`
- L256 _public member_ `FVector Row2 = FVector(0.0, 0.0, 1.0);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USD")`
- L258 _public prototype_ `bool operator==(const FMatrix3D& Other) const = default;`

#### struct `FSdfTimeCode`  
`struct FSdfTimeCode`  
_L261-268_
- L263 _public member_ `double Time;`
- L265 _public prototype_ `FSdfTimeCode(double Time = 0.0);`
- L266 _public prototype_ `bool operator==(const FSdfTimeCode& Other) const = default;`
- L267 _public prototype_ `operator double() const;`

#### struct `FSdfAssetPath`  
`struct FSdfAssetPath`  
_L270-278_
- L272 _public member_ `FString AssetPath;`
- L273 _public member_ `FString ResolvedPath;`
- L275 _public prototype_ `FSdfAssetPath(const FString& AssetPath = {}, const FString& ResolvedPath = {});`
- L276 _public prototype_ `bool operator==(const FSdfAssetPath& Other) const = default;`
- L277 _public prototype_ `operator FString() const;`

#### struct `FQuat4h`  
`struct FQuat4h`  
_L280-291_
- L282 _public member_ `FFloat16 X;`
- L283 _public member_ `FFloat16 Y;`
- L284 _public member_ `FFloat16 Z;`
- L285 _public member_ `FFloat16 W;`
- L287 _public prototype_ `FQuat4h(float X = 0.0f, float Y = 0.0f, float Z = 0.0f, float W = 0.0f);`
- L288 _public prototype_ `FQuat4h(const FQuat4f& Quat);`
- L289 _public prototype_ `bool operator==(const FQuat4h& Other) const = default;`
- L290 _public prototype_ `operator FQuat4f() const;`

#### struct `FVector3h`  
`struct FVector3h`  
_L293-303_
- L295 _public member_ `FFloat16 X;`
- L296 _public member_ `FFloat16 Y;`
- L297 _public member_ `FFloat16 Z;`
- L299 _public prototype_ `FVector3h(float X = 0.0f, float Y = 0.0f, float Z = 0.0f);`
- L300 _public prototype_ `FVector3h(const FVector3f& Vec);`
- L301 _public prototype_ `bool operator==(const FVector3h& Other) const = default;`
- L302 _public prototype_ `operator FVector3f() const;`

#### struct `FVector4h`  
`struct FVector4h`  
_L305-316_
- L307 _public member_ `FFloat16 X;`
- L308 _public member_ `FFloat16 Y;`
- L309 _public member_ `FFloat16 Z;`
- L310 _public member_ `FFloat16 W;`
- L312 _public prototype_ `FVector4h(float X = 0.0f, float Y = 0.0f, float Z = 0.0f, float W = 0.0f);`
- L313 _public prototype_ `FVector4h(const FVector4f& Vec);`
- L314 _public prototype_ `bool operator==(const FVector4h& Other) const = default;`
- L315 _public prototype_ `operator FVector4f() const;`

#### class `IUnrealUSDWrapperModule`  
`class IUnrealUSDWrapperModule : public IModuleInterface`  
_L318-320_
- inherits: `IModuleInterface`

#### class `UnrealUSDWrapper`  
`class UnrealUSDWrapper`  
_L322-453_
- L326 _public prototype_ `static double GetDefaultTimeCode();`
- L333 _public prototype_ `static TArray<FString> RegisterPlugins(const FString& PathToPlugInfo);` — Registers all USD plug-ins discovered at PathToPlugInfo. @return An array containing the names of any newly registered plugins.
- L339 _public prototype_ `static TArray<FString> RegisterPlugins(const TArray<FString>& PathsToPlugInfo);` — Registers all USD plug-ins discovered in any of PathsToPlugInfo. @return An array containing the names of any newly registered plugins.
- L349 _public prototype_ `static TArray<FString> GetAllSupportedFileFormats();` — Returns the file extensions of all file formats supported by USD. These include the extensions for the file formats built into USD as well as those for any other file formats introduced through the USD plugin system (e.g. "abc" for the Alembic file format of the usdAbc plugin).
- L356 _public prototype_ `static TArray<FString> GetNativeFileFormats();` — Returns the file extensions that are native to USD. These are the extensions for the file formats built into USD (i.e. "usd", "usda", "usdc", and "usdz").
- L357 _public prototype_ `static void GetNativeFileFormats(TArray<FString>& OutTextFormats, TArray<FString>& OutPossiblyBinaryFormats);`
- L364 _public prototype_ `static void AddUsdExportFileFormatDescriptions(TArray<FString>& OutFormatExtensions, TArray<FString>& OutFormatDescriptions);` — Internally used by all the export factories, this will query the supported export USD file formats and fill out OutFormatExtensions with entries like "usd", "usda", "usdc", etc., and OutFormatDescriptions with entries like "Universal Scene Description binary file" or "Universal Scene Description text file"
- L369 _public prototype_ `static void AddUsdImportFileFormatDescriptions(TArray<FString>& OutFormats);` — Internally used by all the import factories, this will query the supported export USD file formats and fill out OutFormats with entries like "usda; Universal Scene Description text files", "usdc; Universal Scene Description binary files", etc.
- L388 _public prototype_ `static UE::FUsdStage OpenStage( const TCHAR* Identifier, EUsdInitialLoadSet InitialLoadSet, bool bUseStageCache = true, bool bForceReloadLayersFromDisk = false );` — Opens a USD stage from a file on disk or existing layers, with a population mask or not. @param Identifier - Path to a file that the USD SDK can open (or the identifier of a root layer), which will become the root layer of the new stage @param RootLayer - Existing root layer to use for the new stage, instead of reading it from disk @param SessionLayer - Existing session layer to use for the new stage, instead of creating a new one @param InitialLoadSet - How to handle USD payloads when opening this stage @param PopulationMask - List of prim paths to import, following the USD population mask rules @param bUseStageCache - If true, and the stage is already opened in the stage cache (or the layers are already loaded in the registry) then the file reading may be skipped, and the existing stage returned. When false, the stage and all its referenced layers will be re-read anew, and the stage will not be added to the stage cache. @param bForceReloadLayersFromDisk - USD layers are always cached in the layer registry, so trying to reopen an already opened layer will just fetch it from memory (potentially with edits). If this is true, all local layers used by the stage will be force- reloaded from disk @return The opened stage, which may be invalid.
- L394 _public prototype_ `static UE::FUsdStage OpenStage( UE::FSdfLayer RootLayer, UE::FSdfLayer SessionLayer, EUsdInitialLoadSet InitialLoadSet, bool bUseStageCache = true, bool bForceReloadLayersFromDisk = false );`
- L401 _public prototype_ `static UE::FUsdStage OpenMaskedStage( const TCHAR* Identifier, EUsdInitialLoadSet InitialLoadSet, const TArray<FString>& PopulationMask, bool bForceReloadLayersFromDisk = false );`
- L407 _public prototype_ `static UE::FUsdStage OpenMaskedStage( UE::FSdfLayer RootLayer, UE::FSdfLayer SessionLayer, EUsdInitialLoadSet InitialLoadSet, const TArray<FString>& PopulationMask, bool bForceReloadLayersFromDisk = false );`
- L416 _public prototype_ `static UE::FUsdStage NewStage(const TCHAR* FilePath);` — Creates a new USD root layer file, opens it as a new stage and returns that stage
- L419 _public prototype_ `static UE::FUsdStage NewStage();` — Creates a new memory USD root layer, opens it as a new stage and returns that stage
- L428 _public prototype_ `static UE::FUsdStage GetClipboardStage(bool bCreateIfNeeded = true);` — Get the singleton, persistent stage used as a clipboard for prim cut/copy/paste operations. WARNING: This stage may remain open indefinitely! If you use this directly, be aware that there may be unintended consequences (e.g. a sublayer added to this stage may never fully close). When invoking a paste or clear of the clipboard stage when it is unknown whether a previous cut or copy was done, setting the bCreateIfNeeded parameter to false will avoid needlessly creating the stage.
- L431 _public prototype_ `static TArray<UE::FUsdStage> GetAllStagesFromCache();` — Returns all the stages that are currently opened in the USD utils stage cache, shared between C++ and Python
- L434 _public prototype_ `static void EraseStageFromCache(const UE::FUsdStage& Stage);` — Removes the stage from the stage cache. See UsdStageCache::Erase.
- L444 _public prototype_ `static void SetDefaultResolverDefaultSearchPath(const TArray<FDirectoryPath>& SearchPath);` — Set the directories that will be used as the default search path by USD's default resolver during asset resolution. Each directory in the search path should be an absolute path. If it is not, it will be anchored to the current working directory. Note that the default search path must be set before the first invocation of USD's resolver system, so this function must be called before that to have any effect.
- L448 _public prototype_ `static void SetupDiagnosticDelegate();` — `UE_DEPRECATED(5.6, "Use RegisterDiagnosticDelegate from USDErrorUtils.h.")` — Starts listening to error/warning/log messages emitted by USD
- L452 _public prototype_ `static void ClearDiagnosticDelegate();` — `UE_DEPRECATED(5.6, "Use UnregisterDiagnosticDelegate from USDErrorUtils.h.")` — Stops listening to error/warning/log messages emitted by USD

#### class `IUsdPrim`  
`class IUsdPrim`  
_L455-483_
- L459 _public prototype_ `static bool IsValidPrimName(const FString& Name, FText& OutReason);`
- L461 _public prototype_ `static EUsdPurpose GetPurpose(const pxr::UsdPrim& Prim, bool bComputed = true);`
- L463 _public prototype_ `static bool HasGeometryData(const pxr::UsdPrim& Prim);`
- L464 _public prototype_ `static bool HasGeometryDataOrLODVariants(const pxr::UsdPrim& Prim);`
- L465 _public prototype_ `static int GetNumLODs(const pxr::UsdPrim& Prim);`
- L467 _public prototype_ `static bool IsKindChildOf(const pxr::UsdPrim& Prim, const std::string& InBaseKind);`
- L468 _public prototype_ `static pxr::TfToken GetKind(const pxr::UsdPrim& Prim);`
- L469 _public prototype_ `static bool SetKind(const pxr::UsdPrim& Prim, const pxr::TfToken& Kind);`
- L470 _public prototype_ `static bool ClearKind(const pxr::UsdPrim& Prim);`
- L472 _public prototype_ `static pxr::GfMatrix4d GetLocalTransform(const pxr::UsdPrim& Prim);`
- L473 _public prototype_ `static pxr::GfMatrix4d GetLocalToWorldTransform(const pxr::UsdPrim& Prim);`
- L474 _public prototype_ `static pxr::GfMatrix4d GetLocalToWorldTransform(const pxr::UsdPrim& Prim, double Time);`
- L475 _public prototype_ `static pxr::GfMatrix4d GetLocalToWorldTransform(const pxr::UsdPrim& Prim, double Time, const pxr::SdfPath& AbsoluteRootPath);`
- L476 _public prototype_ `static bool HasTransform(const pxr::UsdPrim& Prim);`
- L478 _public prototype_ `static bool SetActiveLODIndex(const pxr::UsdPrim& Prim, int LODIndex);`
- L480 _public prototype_ `static EUsdGeomOrientation GetGeometryOrientation(const pxr::UsdGeomMesh& Mesh);`
- L481 _public prototype_ `static EUsdGeomOrientation GetGeometryOrientation(const pxr::UsdGeomMesh& Mesh, double Time);`

#### struct `FUsdDelegates`  
`struct FUsdDelegates`  
_L699-704_
- L701 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FUsdImportDelegate, FString );`
- L702 _public member_ `static FUsdImportDelegate OnPreUsdImport;`
- L703 _public member_ `static FUsdImportDelegate OnPostUsdImport;`

#### Free symbols / members of external scopes

- L28 _macro_ `#define USD_PREVIEW_SURFACE_MAX_UV_SETS 4` — We are capped to 4 because the geometry cache and skeletal mesh + morph target shaders have a hard-coded limit of 4 texture coordinates, so our material instances can't cross that limit or else they wouldn't compile when assigned to those meshes
- L29 _macro_ `#define UNUSED_UV_INDEX USD_PREVIEW_SURFACE_MAX_UV_SETS`
- L47 _typedef_ `using UsdStageRefPtr = TfRefPtr<UsdStage>;`
- L48 _typedef_ `using UsdStageWeakPtr = TfWeakPtr<UsdStage>;`
- L50 _typedef_ `using SdfLayerRefPtr = TfRefPtr<SdfLayer>;`
- L51 _typedef_ `using SdfLayerWeakPtr = TfWeakPtr<SdfLayer>;`
- L57 _namespace_ `namespace UE`
- L98 _prototype_ `ENUM_CLASS_FLAGS(EUsdPurpose);`
- L110 _prototype_ `ENUM_CLASS_FLAGS(EUsdDefaultKind);`
- L485 _namespace_ `namespace UnrealIdentifiers`
- L488 _externvar_ `extern const pxr::TfToken LOD;` (scope `UnrealIdentifiers`)
- L489 _externvar_ `extern const pxr::TfToken LodSubtreeAPI;` (scope `UnrealIdentifiers`)
- L490 _externvar_ `extern const pxr::TfToken UnrealLodSubtreeLevels;` (scope `UnrealIdentifiers`)
- L492 _externvar_ `extern const pxr::TfToken SubdivisionAPI;` (scope `UnrealIdentifiers`)
- L493 _externvar_ `extern const pxr::TfToken SubdivisionLevel;` (scope `UnrealIdentifiers`)
- L495 _externvar_ `extern const FString StaticMeshBuildSettingsAPI;` (scope `UnrealIdentifiers`)
- L496 _externvar_ `extern const FString NaniteBuildSettingsAPI;` (scope `UnrealIdentifiers`)
- L499 _externvar_ `extern const pxr::TfToken MaterialAssignment;` (scope `UnrealIdentifiers`) — Attribute name when assigning Unreal materials to UsdGeomMeshes
- L500 _externvar_ `extern const pxr::TfToken Unreal;` (scope `UnrealIdentifiers`)
- L502 _externvar_ `extern const pxr::TfToken UnrealNaniteOverride;` (scope `UnrealIdentifiers`)
- L503 _externvar_ `extern const pxr::TfToken UnrealNaniteOverrideEnable;` (scope `UnrealIdentifiers`)
- L504 _externvar_ `extern const pxr::TfToken UnrealNaniteOverrideDisable;` (scope `UnrealIdentifiers`)
- L506 _externvar_ `extern const pxr::TfToken LiveLinkAPI;` (scope `UnrealIdentifiers`)
- L507 _externvar_ `extern const pxr::TfToken ControlRigAPI;` (scope `UnrealIdentifiers`)
- L508 _externvar_ `extern const pxr::TfToken UnrealAnimBlueprintPath;` (scope `UnrealIdentifiers`)
- L509 _externvar_ `extern const pxr::TfToken UnrealLiveLinkSubjectName;` (scope `UnrealIdentifiers`)
- L510 _externvar_ `extern const pxr::TfToken UnrealLiveLinkEnabled;` (scope `UnrealIdentifiers`)
- L511 _externvar_ `extern const pxr::TfToken UnrealControlRigPath;` (scope `UnrealIdentifiers`)
- L512 _externvar_ `extern const pxr::TfToken UnrealUseFKControlRig;` (scope `UnrealIdentifiers`)
- L513 _externvar_ `extern const pxr::TfToken UnrealControlRigReduceKeys;` (scope `UnrealIdentifiers`)
- L514 _externvar_ `extern const pxr::TfToken UnrealControlRigReductionTolerance;` (scope `UnrealIdentifiers`)
- L516 _externvar_ `extern const pxr::TfToken SparseVolumeTextureAPI;` (scope `UnrealIdentifiers`)
- L517 _externvar_ `extern const pxr::TfToken UnrealSVTMappedFields;` (scope `UnrealIdentifiers`)
- L518 _externvar_ `extern const pxr::TfToken UnrealSVTMappedMaterialParameters;` (scope `UnrealIdentifiers`)
- L519 _externvar_ `extern const pxr::TfToken UnrealSVTMappedGridComponents;` (scope `UnrealIdentifiers`)
- L520 _externvar_ `extern const pxr::TfToken UnrealSVTMappedAttributeChannels;` (scope `UnrealIdentifiers`)
- L521 _externvar_ `extern const pxr::TfToken UnrealSVTAttributesADataType;` (scope `UnrealIdentifiers`)
- L522 _externvar_ `extern const pxr::TfToken UnrealSVTAttributesBDataType;` (scope `UnrealIdentifiers`)
- L524 _externvar_ `extern const pxr::TfToken DiffuseColor;` (scope `UnrealIdentifiers`)
- L525 _externvar_ `extern const pxr::TfToken EmissiveColor;` (scope `UnrealIdentifiers`)
- L526 _externvar_ `extern const pxr::TfToken Metallic;` (scope `UnrealIdentifiers`)
- L527 _externvar_ `extern const pxr::TfToken Roughness;` (scope `UnrealIdentifiers`)
- L528 _externvar_ `extern const pxr::TfToken Opacity;` (scope `UnrealIdentifiers`)
- L529 _externvar_ `extern const pxr::TfToken OpacityMode;` (scope `UnrealIdentifiers`)
- L530 _externvar_ `extern const pxr::TfToken OpacityThreshold;` (scope `UnrealIdentifiers`)
- L531 _externvar_ `extern const pxr::TfToken Normal;` (scope `UnrealIdentifiers`)
- L532 _externvar_ `extern const pxr::TfToken Specular;` (scope `UnrealIdentifiers`)
- L533 _externvar_ `extern const pxr::TfToken SpecularColor;` (scope `UnrealIdentifiers`)
- L534 _externvar_ `extern const pxr::TfToken UseSpecularWorkflow;` (scope `UnrealIdentifiers`)
- L535 _externvar_ `extern const pxr::TfToken ClearCoat;` (scope `UnrealIdentifiers`)
- L536 _externvar_ `extern const pxr::TfToken ClearCoatRoughness;` (scope `UnrealIdentifiers`)
- L537 _externvar_ `extern const pxr::TfToken Anisotropy;` (scope `UnrealIdentifiers`)
- L538 _externvar_ `extern const pxr::TfToken Tangent;` (scope `UnrealIdentifiers`)
- L539 _externvar_ `extern const pxr::TfToken SubsurfaceColor;` (scope `UnrealIdentifiers`)
- L540 _externvar_ `extern const pxr::TfToken Displacement;` (scope `UnrealIdentifiers`)
- L541 _externvar_ `extern const pxr::TfToken Occlusion;` (scope `UnrealIdentifiers`)
- L542 _externvar_ `extern const pxr::TfToken Refraction;` (scope `UnrealIdentifiers`)
- L544 _externvar_ `extern const pxr::TfToken Xform;` (scope `UnrealIdentifiers`)
- L547 _externvar_ `extern const pxr::TfToken Surface;` (scope `UnrealIdentifiers`) — Tokens used mostly for shade material conversion
- L548 _externvar_ `extern const pxr::TfToken St;` (scope `UnrealIdentifiers`)
- L549 _externvar_ `extern const pxr::TfToken Varname;` (scope `UnrealIdentifiers`)
- L550 _externvar_ `extern const pxr::TfToken Scale;` (scope `UnrealIdentifiers`)
- L551 _externvar_ `extern const pxr::TfToken Rotation;` (scope `UnrealIdentifiers`)
- L552 _externvar_ `extern const pxr::TfToken Translation;` (scope `UnrealIdentifiers`)
- L553 _externvar_ `extern const pxr::TfToken In;` (scope `UnrealIdentifiers`)
- L554 _externvar_ `extern const pxr::TfToken Result;` (scope `UnrealIdentifiers`)
- L555 _externvar_ `extern const pxr::TfToken File;` (scope `UnrealIdentifiers`)
- L556 _externvar_ `extern const pxr::TfToken WrapS;` (scope `UnrealIdentifiers`)
- L557 _externvar_ `extern const pxr::TfToken WrapT;` (scope `UnrealIdentifiers`)
- L558 _externvar_ `extern const pxr::TfToken Repeat;` (scope `UnrealIdentifiers`)
- L559 _externvar_ `extern const pxr::TfToken Mirror;` (scope `UnrealIdentifiers`)
- L560 _externvar_ `extern const pxr::TfToken Clamp;` (scope `UnrealIdentifiers`)
- L561 _externvar_ `extern const pxr::TfToken Fallback;` (scope `UnrealIdentifiers`)
- L562 _externvar_ `extern const pxr::TfToken R;` (scope `UnrealIdentifiers`)
- L563 _externvar_ `extern const pxr::TfToken RGB;` (scope `UnrealIdentifiers`)
- L564 _externvar_ `extern const pxr::TfToken RawColorSpaceToken;` (scope `UnrealIdentifiers`)
- L565 _externvar_ `extern const pxr::TfToken SRGBColorSpaceToken;` (scope `UnrealIdentifiers`)
- L566 _externvar_ `extern const pxr::TfToken SourceColorSpaceToken;` (scope `UnrealIdentifiers`)
- L569 _externvar_ `extern const pxr::TfToken UsdPreviewSurface;` (scope `UnrealIdentifiers`) — Tokens copied from usdImaging, because at the moment it's all we need from it
- L570 _externvar_ `extern const pxr::TfToken UsdTransform2d;` (scope `UnrealIdentifiers`)
- L571 _externvar_ `extern const pxr::TfToken UsdPrimvarReader_float2;` (scope `UnrealIdentifiers`)
- L572 _externvar_ `extern const pxr::TfToken UsdPrimvarReader_float3;` (scope `UnrealIdentifiers`)
- L573 _externvar_ `extern const pxr::TfToken UsdUVTexture;` (scope `UnrealIdentifiers`)
- L576 _externvar_ `extern const pxr::TfToken WorldSpaceNormals;` (scope `UnrealIdentifiers`) — Token used to indicate that a material parsed from a material prim should use world space normals
- L579 _externvar_ `extern const pxr::TfToken PrimvarsNormals;` (scope `UnrealIdentifiers`) — Normals and points can also be primvars and have indices, but there is no defined tokens for them
- L580 _externvar_ `extern const pxr::TfToken PrimvarsPoints;` (scope `UnrealIdentifiers`)
- L582 _externvar_ `extern const pxr::TfToken GroomAPI;` (scope `UnrealIdentifiers`)
- L583 _externvar_ `extern const pxr::TfToken GroomBindingAPI;` (scope `UnrealIdentifiers`)
- L584 _externvar_ `extern const pxr::TfToken UnrealGroomToBind;` (scope `UnrealIdentifiers`)
- L585 _externvar_ `extern const pxr::TfToken UnrealGroomReferenceMesh;` (scope `UnrealIdentifiers`)
- L587 _externvar_ `extern const pxr::TfToken UnrealContentPath;` (scope `UnrealIdentifiers`)
- L588 _externvar_ `extern const pxr::TfToken UnrealAssetType;` (scope `UnrealIdentifiers`)
- L589 _externvar_ `extern const pxr::TfToken UnrealExportTime;` (scope `UnrealIdentifiers`)
- L590 _externvar_ `extern const pxr::TfToken UnrealEngineVersion;` (scope `UnrealIdentifiers`)
- L592 _externvar_ `extern const pxr::TfToken UnrealCollapsingAPI;` (scope `UnrealIdentifiers`)
- L593 _externvar_ `extern const pxr::TfToken UnrealCollapsingAttr;` (scope `UnrealIdentifiers`)
- L594 _externvar_ `extern const pxr::TfToken CollapsingAllow;` (scope `UnrealIdentifiers`)
- L595 _externvar_ `extern const pxr::TfToken CollapsingDefault;` (scope `UnrealIdentifiers`)
- L596 _externvar_ `extern const pxr::TfToken CollapsingNever;` (scope `UnrealIdentifiers`)
- L598 _externvar_ `extern const pxr::TfToken NaniteAssemblyRootAPI;` (scope `UnrealIdentifiers`)
- L599 _externvar_ `extern const pxr::TfToken NaniteAssemblyExternalRefAPI;` (scope `UnrealIdentifiers`)
- L600 _externvar_ `extern const pxr::TfToken NaniteAssemblySkelBindingAPI;` (scope `UnrealIdentifiers`)
- L601 _externvar_ `extern const pxr::TfToken UnrealNaniteAssemblyMeshType;` (scope `UnrealIdentifiers`)
- L602 _externvar_ `extern const pxr::TfToken UnrealNaniteAssemblyMeshAssetPath;` (scope `UnrealIdentifiers`)
- L603 _externvar_ `extern const pxr::TfToken UnrealNaniteAssemblySkeleton;` (scope `UnrealIdentifiers`)
- L604 _externvar_ `extern const pxr::TfToken PrimvarsUnrealNaniteAssemblyBindJoints;` (scope `UnrealIdentifiers`)
- L605 _externvar_ `extern const pxr::TfToken PrimvarsUnrealNaniteAssemblyBindJointWeights;` (scope `UnrealIdentifiers`)
- L606 _externvar_ `extern const pxr::TfToken NaniteAssemblyStaticMesh;` (scope `UnrealIdentifiers`)
- L607 _externvar_ `extern const pxr::TfToken NaniteAssemblySkeletalMesh;` (scope `UnrealIdentifiers`)
- L611 _externvar_ `extern const TCHAR* LayerSavedComment;` (scope `UnrealIdentifiers`)
- L612 _externvar_ `extern const TCHAR* TwoSidedMaterialSuffix;` (scope `UnrealIdentifiers`)
- L614 _externvar_ `extern const TCHAR* Invisible;` (scope `UnrealIdentifiers`)
- L615 _externvar_ `extern const TCHAR* Inherited;` (scope `UnrealIdentifiers`)
- L616 _externvar_ `extern const TCHAR* IdentifierPrefix;` (scope `UnrealIdentifiers`)
- L619 _externvar_ `extern const TCHAR* ExportedSkeletonPrimName;` (scope `UnrealIdentifiers`) — The prim name we always use when exporting Skeletons inside SkelRoots to USD
- L622 _externvar_ `extern FName TransformPropertyName;` (scope `UnrealIdentifiers`) — USceneComponent properties
- L623 _externvar_ `extern FName HiddenInGamePropertyName;` (scope `UnrealIdentifiers`)
- L624 _externvar_ `extern FName HiddenPropertyName;` (scope `UnrealIdentifiers`)
- L627 _externvar_ `extern FName AspectRatioPropertyName;` (scope `UnrealIdentifiers`) — UCameraComponent properties
- L628 _externvar_ `extern FName OrthoWidthPropertyName;` (scope `UnrealIdentifiers`)
- L629 _externvar_ `extern FName OrthoFarClipPlanePropertyName;` (scope `UnrealIdentifiers`)
- L630 _externvar_ `extern FName OrthoNearClipPlanePropertyName;` (scope `UnrealIdentifiers`)
- L633 _externvar_ `extern FName CurrentFocalLengthPropertyName;` (scope `UnrealIdentifiers`) — UCineCameraComponent properties
- L634 _externvar_ `extern FName ManualFocusDistancePropertyName;` (scope `UnrealIdentifiers`)
- L635 _externvar_ `extern FName CurrentAperturePropertyName;` (scope `UnrealIdentifiers`)
- L636 _externvar_ `extern FName SensorWidthPropertyName;` (scope `UnrealIdentifiers`)
- L637 _externvar_ `extern FName SensorHeightPropertyName;` (scope `UnrealIdentifiers`)
- L638 _externvar_ `extern FName SensorHorizontalOffsetPropertyName;` (scope `UnrealIdentifiers`)
- L639 _externvar_ `extern FName SensorVerticalOffsetPropertyName;` (scope `UnrealIdentifiers`)
- L640 _externvar_ `extern FName ExposureCompensationPropertyName;` (scope `UnrealIdentifiers`)
- L641 _externvar_ `extern FName ProjectionModePropertyName;` (scope `UnrealIdentifiers`)
- L642 _externvar_ `extern FName CustomNearClipppingPlanePropertyName;` (scope `UnrealIdentifiers`)
- L643 _externvar_ `extern FName DepthOfFieldFstopPropertyName;` (scope `UnrealIdentifiers`)
- L644 _externvar_ `extern FName CameraISOPropertyName;` (scope `UnrealIdentifiers`)
- L645 _externvar_ `extern FName CameraShutterSpeedPropertyName;` (scope `UnrealIdentifiers`)
- L648 _externvar_ `extern FName IntensityPropertyName;` (scope `UnrealIdentifiers`) — LightComponentBase properties
- L649 _externvar_ `extern FName LightColorPropertyName;` (scope `UnrealIdentifiers`)
- L652 _externvar_ `extern FName UseTemperaturePropertyName;` (scope `UnrealIdentifiers`) — LightComponent properties
- L653 _externvar_ `extern FName TemperaturePropertyName;` (scope `UnrealIdentifiers`)
- L656 _externvar_ `extern FName SourceWidthPropertyName;` (scope `UnrealIdentifiers`) — URectLightComponent properties
- L657 _externvar_ `extern FName SourceHeightPropertyName;` (scope `UnrealIdentifiers`)
- L660 _externvar_ `extern FName SourceRadiusPropertyName;` (scope `UnrealIdentifiers`) — UPointLightComponent properties
- L663 _externvar_ `extern FName OuterConeAnglePropertyName;` (scope `UnrealIdentifiers`) — USpotLightComponent properties
- L664 _externvar_ `extern FName InnerConeAnglePropertyName;` (scope `UnrealIdentifiers`)
- L667 _externvar_ `extern FName LightSourceAnglePropertyName;` (scope `UnrealIdentifiers`) — UDirectionalLightComponent properties
- L670 _externvar_ `extern FString MaterialAllPurpose;` (scope `UnrealIdentifiers`) — Material purpose tokens that we convert from USD, if available
- L671 _externvar_ `extern FString MaterialAllPurposeText;` (scope `UnrealIdentifiers`) — Text to show on UI for "allPurpose", as its value is actually the empty string
- L672 _externvar_ `extern FString MaterialPreviewPurpose;` (scope `UnrealIdentifiers`)
- L673 _externvar_ `extern FString MaterialFullPurpose;` (scope `UnrealIdentifiers`)
- L675 _externvar_ `extern FString PrimvarsDisplayColor;` (scope `UnrealIdentifiers`)
- L676 _externvar_ `extern FString PrimvarsDisplayOpacity;` (scope `UnrealIdentifiers`)
- L677 _externvar_ `extern FString DoubleSided;` (scope `UnrealIdentifiers`)
- L680 _externvar_ `extern FString ModelDrawMode;` (scope `UnrealIdentifiers`) — Tokens from UsdGeomModelAPI that we need to reference from the UsdStageActor
- L681 _externvar_ `extern FString ModelApplyDrawMode;` (scope `UnrealIdentifiers`)
- L684 _externvar_ `extern FString UsdNamespaceDelimiter;` (scope `UnrealIdentifiers`) — The character used to separate property namespaces (usually just ':')
- L686 _externvar_ `extern const FName UniversalRenderContext;` (scope `UnrealIdentifiers`) — Likely the empty string
- L687 _externvar_ `extern const FName UnrealRenderContext;` (scope `UnrealIdentifiers`)
- L688 _externvar_ `extern const FName MaterialXRenderContext;` (scope `UnrealIdentifiers`)
- L689 _externvar_ `extern const FName MdlRenderContext;` (scope `UnrealIdentifiers`)
- L691 _externvar_ `extern const FString UniversalRenderContextDisplayString;` (scope `UnrealIdentifiers`) — "universal"
- L695 _externvar_ `extern const FName PointInstancerTag;` (scope `UnrealIdentifiers`) — This marks a generated scene component as corresponding to a PointInstancer prim. It is mainly used to let us know to cleanup any ISM/HISM child component whenever we're cleaning up the scene component
- L701 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FUsdImportDelegate, FString );`

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UsdWrappers/ForwardDeclarations.h` (Public)


#### class `UE::FDummyPtrBase`  
`class FDummyPtrBase`  
_L46-58_
- desc: We use these types so that we can keep the same FUsdStage, etc. type aliases and not change the rest of the code. It's the bare minimum to be able to be tested for validity (and always fail).
- L49 _public function_ `explicit operator bool() const`
- L54 _public function_ `bool operator==(const FDummyPtrBase&) const`

#### class `UE::FDummyRefPtrType`  
`class FDummyRefPtrType : public FDummyPtrBase`  
_L64-69_
- inherits: `FDummyPtrBase`
- L67 _public function_ `FDummyRefPtrType()`
- L68 _public function_ `FDummyRefPtrType(const FDummyWeakPtrType&)`

#### class `UE::FDummyWeakPtrType`  
`class FDummyWeakPtrType : public FDummyPtrBase`  
_L71-76_
- inherits: `FDummyPtrBase`
- L74 _public function_ `FDummyWeakPtrType()`
- L75 _public function_ `FDummyWeakPtrType(const FDummyRefPtrType&)`

#### Free symbols / members of external scopes

- L20 _typedef_ `using UsdStageRefPtr = TfRefPtr<UsdStage>;`
- L21 _typedef_ `using UsdStageWeakPtr = TfWeakPtr<UsdStage>;`
- L23 _typedef_ `using SdfLayerRefPtr = TfRefPtr<SdfLayer>;`
- L24 _typedef_ `using SdfLayerWeakPtr = TfWeakPtr<SdfLayer>;`
- L27 _namespace_ `namespace UE`
- L31 _typedef_ `using FUsdStage = FUsdStageBase<pxr::UsdStageRefPtr>;` (scope `UE`)
- L32 _typedef_ `using FUsdStageWeak = FUsdStageBase<pxr::UsdStageWeakPtr>;` (scope `UE`)
- L36 _typedef_ `using FSdfLayer = FSdfLayerBase<pxr::SdfLayerRefPtr>;` (scope `UE`)
- L37 _typedef_ `using FSdfLayerWeak = FSdfLayerBase<pxr::SdfLayerWeakPtr>;` (scope `UE`)
- L41 _namespace_ `namespace UE`
- L80 _typedef_ `using FUsdStage = FUsdStageBase<FDummyRefPtrType>;` (scope `UE`)
- L81 _typedef_ `using FUsdStageWeak = FUsdStageBase<FDummyWeakPtrType>;` (scope `UE`)
- L85 _typedef_ `using FSdfLayer = FSdfLayerBase<FDummyRefPtrType>;` (scope `UE`)
- L86 _typedef_ `using FSdfLayerWeak = FSdfLayerBase<FDummyWeakPtrType>;` (scope `UE`)

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UsdWrappers/PcpLayerStack.h` (Public)


#### class `UE::FPcpLayerStack`  
`class FPcpLayerStack`  
_L37-77_
- desc: Minimal pxr::PcpLayerStackRefPtr wrapper for Unreal that can be used from no-rtti modules.
- L40 _public prototype_ `FPcpLayerStack();`
- L42 _public prototype_ `FPcpLayerStack(const FPcpLayerStack& Other);`
- L43 _public prototype_ `FPcpLayerStack(FPcpLayerStack&& Other);`
- L44 _public prototype_ `~FPcpLayerStack();`
- L46 _public prototype_ `FPcpLayerStack& operator=(const FPcpLayerStack& Other);`
- L47 _public prototype_ `FPcpLayerStack& operator=(FPcpLayerStack&& Other);`
- L49 _public prototype_ `bool operator==(const FPcpLayerStack& Other) const;`
- L50 _public prototype_ `bool operator!=(const FPcpLayerStack& Other) const;`
- L52 _public prototype_ `explicit operator bool() const;`
- L57 _public prototype_ `explicit FPcpLayerStack(const pxr::PcpLayerStackRefPtr& InPcpLayerStack);`
- L58 _public prototype_ `explicit FPcpLayerStack(pxr::PcpLayerStackRefPtr&& InPcpLayerStack);`
- L59 _public prototype_ `FPcpLayerStack& operator=(const pxr::PcpLayerStackRefPtr& InPcpLayerStack);`
- L60 _public prototype_ `FPcpLayerStack& operator=(pxr::PcpLayerStackRefPtr&& InPcpLayerStack);`
- L62 _public prototype_ `operator pxr::PcpLayerStackRefPtr&();`
- L63 _public prototype_ `operator const pxr::PcpLayerStackRefPtr&() const;`
- L68 _public prototype_ `FPcpLayerStackIdentifier GetIdentifier() const;`
- L69 _public prototype_ `TArray<FSdfLayer> GetLayers() const;`
- L70 _public prototype_ `FSdfLayerOffset GetLayerOffsetForLayer(const FSdfLayer& Layer) const;`
- L71 _public prototype_ `FSdfLayerOffset GetLayerOffsetForLayer(const FSdfLayerWeak& Layer) const;`
- L72 _public prototype_ `bool HasLayer(const FSdfLayer& Layer) const;`
- L73 _public prototype_ `bool HasLayer(const FSdfLayerWeak& Layer) const;`
- L76 _private member_ `TUniquePtr<Internal::FPcpLayerStackImpl> Impl;`

#### Free symbols / members of external scopes

- L20 _typedef_ `using PcpLayerStackRefPtr = TfRefPtr<PcpLayerStack>;`
- L25 _namespace_ `namespace UE`
- L29 _namespace_ `namespace Internal` (scope `UE`)

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UsdWrappers/PcpLayerStackIdentifier.h` (Public)


#### class `UE::FPcpLayerStackIdentifier`  
`class FPcpLayerStackIdentifier`  
_L30-66_
- desc: Minimal pxr::PcpLayerStackIdentifier wrapper for Unreal that can be used from no-rtti modules.
- L33 _public prototype_ `FPcpLayerStackIdentifier();`
- L35 _public prototype_ `FPcpLayerStackIdentifier(const FPcpLayerStackIdentifier& Other);`
- L36 _public prototype_ `FPcpLayerStackIdentifier(FPcpLayerStackIdentifier&& Other);`
- L37 _public prototype_ `~FPcpLayerStackIdentifier();`
- L39 _public prototype_ `FPcpLayerStackIdentifier& operator=(const FPcpLayerStackIdentifier& Other);`
- L40 _public prototype_ `FPcpLayerStackIdentifier& operator=(FPcpLayerStackIdentifier&& Other);`
- L42 _public prototype_ `bool operator==(const FPcpLayerStackIdentifier& Other) const;`
- L43 _public prototype_ `bool operator!=(const FPcpLayerStackIdentifier& Other) const;`
- L45 _public prototype_ `explicit operator bool() const;`
- L50 _public prototype_ `explicit FPcpLayerStackIdentifier(const pxr::PcpLayerStackIdentifier& InPcpLayerStackIdentifier);`
- L51 _public prototype_ `explicit FPcpLayerStackIdentifier(pxr::PcpLayerStackIdentifier&& InPcpLayerStackIdentifier);`
- L52 _public prototype_ `FPcpLayerStackIdentifier& operator=(const pxr::PcpLayerStackIdentifier& InPcpLayerStackIdentifier);`
- L53 _public prototype_ `FPcpLayerStackIdentifier& operator=(pxr::PcpLayerStackIdentifier&& InPcpLayerStackIdentifier);`
- L55 _public prototype_ `operator pxr::PcpLayerStackIdentifier&();`
- L56 _public prototype_ `operator const pxr::PcpLayerStackIdentifier&() const;`
- L61 _public prototype_ `FSdfLayerWeak RootLayer() const;`
- L62 _public prototype_ `FSdfLayerWeak SessionLayer() const;`
- L65 _private member_ `TUniquePtr<Internal::FPcpLayerStackIdentifierImpl> Impl;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Internal` (scope `UE`)

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UsdWrappers/PcpMapExpression.h` (Public)


#### class `UE::FPcpMapExpression`  
`class FPcpMapExpression`  
_L30-60_
- desc: Minimal pxr::PcpMapExpression wrapper for Unreal that can be used from no-rtti modules.
- L33 _public prototype_ `FPcpMapExpression();`
- L35 _public prototype_ `FPcpMapExpression(const FPcpMapExpression& Other);`
- L36 _public prototype_ `FPcpMapExpression(FPcpMapExpression&& Other);`
- L37 _public prototype_ `~FPcpMapExpression();`
- L39 _public prototype_ `FPcpMapExpression& operator=(const FPcpMapExpression& Other);`
- L40 _public prototype_ `FPcpMapExpression& operator=(FPcpMapExpression&& Other);`
- L45 _public prototype_ `explicit FPcpMapExpression(const pxr::PcpMapExpression& InPcpMapExpression);`
- L46 _public prototype_ `explicit FPcpMapExpression(pxr::PcpMapExpression&& InPcpMapExpression);`
- L47 _public prototype_ `FPcpMapExpression& operator=(const pxr::PcpMapExpression& InPcpMapExpression);`
- L48 _public prototype_ `FPcpMapExpression& operator=(pxr::PcpMapExpression&& InPcpMapExpression);`
- L50 _public prototype_ `operator pxr::PcpMapExpression&();`
- L51 _public prototype_ `operator const pxr::PcpMapExpression&() const;`
- L56 _public prototype_ `FSdfLayerOffset GetTimeOffset() const;`
- L59 _private member_ `TUniquePtr<Internal::FPcpMapExpressionImpl> Impl;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Internal` (scope `UE`)

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UsdWrappers/PcpNodeRef.h` (Public)


#### enum `UE::EPcpArcType`  
`enum class EPcpArcType`  
_L30-41_
- desc: Analogous to pxr::PcpArcType
- L32 _public enumerator_ `PcpArcTypeRoot`
- L33 _public enumerator_ `PcpArcTypeInherit`
- L34 _public enumerator_ `PcpArcTypeVariant`
- L35 _public enumerator_ `PcpArcTypeRelocate`
- L36 _public enumerator_ `PcpArcTypeReference`
- L37 _public enumerator_ `PcpArcTypePayload`
- L38 _public enumerator_ `PcpArcTypeSpecialize`
- L40 _public enumerator_ `PcpNumArcTypes`

#### class `UE::FPcpNodeRef`  
`class FPcpNodeRef`  
_L46-86_
- desc: Minimal pxr::PcpNodeRef wrapper for Unreal that can be used from no-rtti modules.
- L49 _public prototype_ `FPcpNodeRef();`
- L51 _public prototype_ `FPcpNodeRef(const FPcpNodeRef& Other);`
- L52 _public prototype_ `FPcpNodeRef(FPcpNodeRef&& Other);`
- L53 _public prototype_ `~FPcpNodeRef();`
- L55 _public prototype_ `FPcpNodeRef& operator=(const FPcpNodeRef& Other);`
- L56 _public prototype_ `FPcpNodeRef& operator=(FPcpNodeRef&& Other);`
- L58 _public prototype_ `bool operator==(const FPcpNodeRef& Other) const;`
- L59 _public prototype_ `bool operator!=(const FPcpNodeRef& Other) const;`
- L61 _public prototype_ `explicit operator bool() const;`
- L66 _public prototype_ `explicit FPcpNodeRef(const pxr::PcpNodeRef& InPcpNodeRef);`
- L67 _public prototype_ `explicit FPcpNodeRef(pxr::PcpNodeRef&& InPcpNodeRef);`
- L68 _public prototype_ `FPcpNodeRef& operator=(const pxr::PcpNodeRef& InPcpNodeRef);`
- L69 _public prototype_ `FPcpNodeRef& operator=(pxr::PcpNodeRef&& InPcpNodeRef);`
- L71 _public prototype_ `operator pxr::PcpNodeRef&();`
- L72 _public prototype_ `operator const pxr::PcpNodeRef&() const;`
- L77 _public prototype_ `EPcpArcType GetArcType() const;`
- L78 _public prototype_ `FPcpNodeRef GetParentNode() const;`
- L79 _public prototype_ `FPcpMapExpression GetMapToParent() const;`
- L80 _public prototype_ `FPcpMapExpression GetMapToRoot() const;`
- L81 _public prototype_ `FSdfPath GetPath() const;`
- L82 _public prototype_ `FPcpLayerStack GetLayerStack() const;`
- L85 _private member_ `TUniquePtr<Internal::FPcpNodeRefImpl> Impl;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L24 _namespace_ `namespace Internal` (scope `UE`)

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UsdWrappers/PcpPrimIndex.h` (Public)


#### class `UE::FPcpPrimIndex`  
`class FPcpPrimIndex`  
_L30-64_
- desc: Minimal pxr::PcpPrimIndex wrapper for Unreal that can be used from no-rtti modules.
- L33 _public prototype_ `FPcpPrimIndex();`
- L35 _public prototype_ `FPcpPrimIndex(const FPcpPrimIndex& Other);`
- L36 _public prototype_ `FPcpPrimIndex(FPcpPrimIndex&& Other);`
- L37 _public prototype_ `~FPcpPrimIndex();`
- L39 _public prototype_ `FPcpPrimIndex& operator=(const FPcpPrimIndex& Other);`
- L40 _public prototype_ `FPcpPrimIndex& operator=(FPcpPrimIndex&& Other);`
- L42 _public prototype_ `explicit operator bool() const;`
- L47 _public prototype_ `explicit FPcpPrimIndex(const pxr::PcpPrimIndex& InPcpPrimIndex);`
- L48 _public prototype_ `explicit FPcpPrimIndex(pxr::PcpPrimIndex&& InPcpPrimIndex);`
- L49 _public prototype_ `FPcpPrimIndex& operator=(const pxr::PcpPrimIndex& InPcpPrimIndex);`
- L50 _public prototype_ `FPcpPrimIndex& operator=(pxr::PcpPrimIndex&& InPcpPrimIndex);`
- L52 _public prototype_ `operator pxr::PcpPrimIndex&();`
- L53 _public prototype_ `operator const pxr::PcpPrimIndex&() const;`
- L58 _public prototype_ `bool IsValid() const;`
- L59 _public prototype_ `FPcpNodeRef GetRootNode() const;`
- L60 _public prototype_ `FString DumpToString(bool bIncludeInheritOriginInfo = true, bool bIncludeMaps = true) const;`
- L63 _private member_ `TUniquePtr<Internal::FPcpPrimIndexImpl> Impl;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Internal` (scope `UE`)

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UsdWrappers/SdfAttributeSpec.h` (Public)


#### class `UE::FSdfAttributeSpec`  
`class FSdfAttributeSpec`  
_L34-72_
- desc: Minimal pxr::SdfAttributeSpecHandle wrapper for Unreal that can be used from no-rtti modules.
- L37 _public prototype_ `FSdfAttributeSpec();`
- L39 _public prototype_ `FSdfAttributeSpec(const FSdfAttributeSpec& Other);`
- L40 _public prototype_ `FSdfAttributeSpec(FSdfAttributeSpec&& Other);`
- L41 _public prototype_ `~FSdfAttributeSpec();`
- L43 _public prototype_ `FSdfAttributeSpec& operator=(const FSdfAttributeSpec& Other);`
- L44 _public prototype_ `FSdfAttributeSpec& operator=(FSdfAttributeSpec&& Other);`
- L46 _public prototype_ `bool operator==(const FSdfAttributeSpec& Other) const;`
- L47 _public prototype_ `bool operator!=(const FSdfAttributeSpec& Other) const;`
- L49 _public prototype_ `explicit operator bool() const;`
- L54 _public prototype_ `explicit FSdfAttributeSpec(const pxr::SdfAttributeSpecHandle& InSdfAttributeSpecHandle);`
- L55 _public prototype_ `explicit FSdfAttributeSpec(pxr::SdfAttributeSpecHandle&& InSdfAttributeSpecHandle);`
- L56 _public prototype_ `FSdfAttributeSpec& operator=(const pxr::SdfAttributeSpecHandle& InSdfAttributeSpecHandle);`
- L57 _public prototype_ `FSdfAttributeSpec& operator=(pxr::SdfAttributeSpecHandle&& InSdfAttributeSpecHandle);`
- L59 _public prototype_ `operator pxr::SdfAttributeSpecHandle&();`
- L60 _public prototype_ `operator const pxr::SdfAttributeSpecHandle&() const;`
- L65 _public prototype_ `UE::FVtValue GetDefaultValue() const;`
- L66 _public prototype_ `bool SetDefaultValue(const UE::FVtValue& Value);`
- L68 _public prototype_ `FString GetName() const;`
- L71 _private member_ `TUniquePtr<Internal::FSdfAttributeSpecImpl> Impl;`

#### Free symbols / members of external scopes

- L17 _typedef_ `using SdfAttributeSpecHandle = SdfHandle<SdfAttributeSpec>;`
- L22 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Internal` (scope `UE`)

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UsdWrappers/SdfChangeBlock.h` (Public)


#### class `UE::FSdfChangeBlock`  
`class FSdfChangeBlock final`  
_L19-27_
- desc: Minimal pxr::SdfChangeBlock wrapper for Unreal that can be used from no-rtti modules.
- L22 _public prototype_ `FSdfChangeBlock();`
- L23 _public prototype_ `~FSdfChangeBlock();`
- L26 _private member_ `TUniquePtr<Internal::FSdfChangeBlockImpl> Impl;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API UNREALUSDWRAPPER_API`
- L9 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Internal` (scope `UE`)

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UsdWrappers/SdfLayer.h` (Public)


#### struct `UE::FSdfLayerOffset`  
`struct FSdfLayerOffset`  
_L24-36_
- L26 _public prototype_ `FSdfLayerOffset() = default;`
- L28 _public function_ `FSdfLayerOffset(double InOffset, double InScale) : Offset(InOffset) , Scale(InScale)`
- L34 _public member_ `double Offset = 0.0;`
- L35 _public member_ `double Scale = 1.0;`

#### struct `UE::FSdfPayload`  
`struct FSdfPayload`  
_L38-50_
- L40 _public function_ `FSdfPayload(const FString& InAssetPath = {}, const FSdfPath& InPrimPath = {}, const FSdfLayerOffset& InLayerOffset = {}) : AssetPath(InAssetPath) , PrimPath(InPrimPath) , LayerOffset(InLayerOffset)`
- L47 _public member_ `FString AssetPath;`
- L48 _public member_ `FSdfPath PrimPath;`
- L49 _public member_ `FSdfLayerOffset LayerOffset;`

#### struct `UE::FSdfReference`  
`struct FSdfReference`  
_L59-71_
- desc: In the USD API, pxr::SdfPayload and pxr::SdfReference are very similar except that the latter includes support for a custom data dictionary. The UE wrapping of SdfReference does not currently include support for that custom data, leaving the FSdfReference wrapper identical to the FSdfPayload wrapper. We keep them as distinct types though to better mimic the USD API and in case support for custom data dictionaries on references is added to the FSdfReference wrapper in the future.
- L61 _public function_ `FSdfReference(const FString& InAssetPath = {}, const FSdfPath& InPrimPath = {}, const FSdfLayerOffset& InLayerOffset = {}) : AssetPath(InAssetPath) , PrimPath(InPrimPath) , LayerOffset(InLayerOffset)`
- L68 _public member_ `FString AssetPath;`
- L69 _public member_ `FSdfPath PrimPath;`
- L70 _public member_ `FSdfLayerOffset LayerOffset;`

#### class `UE::FSdfLayerBase`  
`template<typename PtrType> class FSdfLayerBase`  
_L78-203_
- desc: Minimal pxr::SdfLayer pointer wrapper for Unreal that can be used from no-rtti modules. Use the aliases FSdfLayer and FSdfLayerWeak instead (defined on ForwardDeclarations.h)
- L81 _public prototype_ `FSdfLayerBase();`
- L83 _public prototype_ `FSdfLayerBase(const FSdfLayer& Other);`
- L84 _public prototype_ `FSdfLayerBase(FSdfLayer&& Other);`
- L85 _public prototype_ `FSdfLayerBase(const FSdfLayerWeak& Other);`
- L86 _public prototype_ `FSdfLayerBase(FSdfLayerWeak&& Other);`
- L88 _public prototype_ `~FSdfLayerBase();`
- L90 _public prototype_ `FSdfLayerBase& operator=(const FSdfLayer& Other);`
- L91 _public prototype_ `FSdfLayerBase& operator=(FSdfLayer&& Other);`
- L92 _public prototype_ `FSdfLayerBase& operator=(const FSdfLayerWeak& Other);`
- L93 _public prototype_ `FSdfLayerBase& operator=(FSdfLayerWeak&& Other);`
- L98 _public prototype_ `template<typename OtherPtrType> bool operator==(const FSdfLayerBase<OtherPtrType>& Other) const;` — We have to implement a templated comparison operator, or else we get ambigous conversions on the Mac targets when comparing FSdfLayer and FSdfLayerWeak
- L100 _public prototype_ `explicit operator bool() const;`
- L108 _public prototype_ `explicit FSdfLayerBase(const pxr::SdfLayerRefPtr& InSdfLayer);`
- L109 _public prototype_ `explicit FSdfLayerBase(pxr::SdfLayerRefPtr&& InSdfLayer);`
- L110 _public prototype_ `explicit FSdfLayerBase(const pxr::SdfLayerWeakPtr& InSdfLayer);`
- L111 _public prototype_ `explicit FSdfLayerBase(pxr::SdfLayerWeakPtr&& InSdfLayer);`
- L113 _public prototype_ `FSdfLayerBase& operator=(const pxr::SdfLayerRefPtr& InSdfLayer);`
- L114 _public prototype_ `FSdfLayerBase& operator=(pxr::SdfLayerRefPtr&& InSdfLayer);`
- L115 _public prototype_ `FSdfLayerBase& operator=(const pxr::SdfLayerWeakPtr& InSdfLayer);`
- L116 _public prototype_ `FSdfLayerBase& operator=(pxr::SdfLayerWeakPtr&& InSdfLayer);`
- L120 _public prototype_ `operator PtrType&();` — We can provide reference cast operators for the type we do have, but need to settle on providing copy cast operators for the other types
- L121 _public prototype_ `operator const PtrType&() const;`
- L123 _public prototype_ `operator pxr::SdfLayerRefPtr() const;`
- L124 _public prototype_ `operator pxr::SdfLayerWeakPtr() const;`
- L129 _public prototype_ `FString GetComment() const;`
- L130 _public prototype_ `void SetComment(const TCHAR* Comment) const;`
- L132 _public prototype_ `void TransferContent(const FSdfLayer& SourceLayer);`
- L134 _public prototype_ `static TSet<FSdfLayerWeak> GetLoadedLayers();`
- L135 _public prototype_ `static FSdfLayer FindOrOpen(const TCHAR* Identifier, const TMap<FString, FString>& FileFormatArguments = {});`
- L136 _public prototype_ `static FSdfLayer CreateNew(const TCHAR* Identifier, const TMap<FString, FString>& FileFormatArguments = {});`
- L138 _public prototype_ `TMap<FString, FString> GetFileFormatArguments() const;`
- L140 _public prototype_ `bool Save(bool bForce = false) const;`
- L142 _public prototype_ `TSet<FString> GetCompositionAssetDependencies() const;`
- L144 _public prototype_ `bool UpdateCompositionAssetDependency(const TCHAR* OldAssetPath, const TCHAR* NewAssetPath = nullptr);`
- L146 _public prototype_ `FString GetRealPath() const;`
- L147 _public prototype_ `FString GetIdentifier() const;`
- L148 _public prototype_ `FString GetDisplayName() const;`
- L150 _public prototype_ `FString ComputeAbsolutePath(const FString& AssetPath) const;`
- L152 _public prototype_ `bool IsDirty() const;`
- L153 _public prototype_ `bool IsEmpty() const;`
- L154 _public prototype_ `bool IsAnonymous() const;`
- L156 _public prototype_ `bool Export(const TCHAR* Filename, const FString& Comment = {}, const TMap<FString, FString>& FileFormatArguments = {}) const;`
- L158 _public prototype_ `void Clear();`
- L160 _public prototype_ `void Reload(bool bForce = false);`
- L162 _public prototype_ `bool HasStartTimeCode() const;`
- L163 _public prototype_ `double GetStartTimeCode() const;`
- L164 _public prototype_ `void SetStartTimeCode(double TimeCode);`
- L166 _public prototype_ `bool HasEndTimeCode() const;`
- L167 _public prototype_ `double GetEndTimeCode() const;`
- L168 _public prototype_ `void SetEndTimeCode(double TimeCode);`
- L170 _public prototype_ `bool HasTimeCodesPerSecond() const;`
- L171 _public prototype_ `double GetTimeCodesPerSecond() const;`
- L172 _public prototype_ `void SetTimeCodesPerSecond(double TimeCodesPerSecond);`
- L174 _public prototype_ `bool HasFramesPerSecond() const;`
- L175 _public prototype_ `double GetFramesPerSecond() const;`
- L176 _public prototype_ `void SetFramesPerSecond(double FramesPerSecond);`
- L178 _public prototype_ `TArray<FString> GetSubLayerPaths() const;`
- L179 _public prototype_ `void SetSubLayerPaths(const TArray<FString>& NewPaths);`
- L180 _public prototype_ `int64 GetNumSubLayerPaths() const;`
- L181 _public prototype_ `void InsertSubLayerPath(const FString& Path, int32 Index = -1);`
- L182 _public prototype_ `void RemoveSubLayerPath(int32 Index);`
- L183 _public prototype_ `TArray<FSdfLayerOffset> GetSubLayerOffsets() const;`
- L184 _public prototype_ `FSdfLayerOffset GetSubLayerOffset(int32 Index) const;`
- L185 _public prototype_ `void SetSubLayerOffset(const FSdfLayerOffset& Offset, int32 Index);`
- L187 _public prototype_ `bool HasSpec(const FSdfPath& Path) const;`
- L189 _public prototype_ `FSdfPrimSpec GetPseudoRoot() const;`
- L190 _public prototype_ `FSdfPrimSpec GetPrimAtPath(const FSdfPath& Path) const;`
- L192 _public prototype_ `TSet<double> ListTimeSamplesForPath(const FSdfPath& Path) const;`
- L193 _public prototype_ `void EraseTimeSample(const FSdfPath& Path, double Time);`
- L195 _public prototype_ `bool IsMuted() const;`
- L196 _public prototype_ `void SetMuted(bool bMuted);`
- L202 _private member_ `TUniquePtr<Internal::FSdfLayerImpl<PtrType>> Impl;`

#### class `UE::FSdfLayerUtils`  
`class FSdfLayerUtils`  
_L208-212_
- desc: Wrapper for global functions in pxr/usd/sdf/layerUtils.h
- L211 _public prototype_ `static FString SdfComputeAssetPathRelativeToLayer(const FSdfLayer& Anchor, const TCHAR* AssetPath);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UNREALUSDWRAPPER_API`
- L14 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Internal` (scope `UE`)

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UsdWrappers/SdfPath.h` (Public)


#### class `UE::FSdfPath`  
`class FSdfPath`  
_L29-110_
- desc: Minimal pxr::SdfPath wrapper for Unreal that can be used from no-rtti modules.
- L32 _public prototype_ `FSdfPath();`
- L33 _public prototype_ `explicit FSdfPath(const TCHAR* InPath);`
- L35 _public prototype_ `FSdfPath(const FSdfPath& Other);`
- L36 _public prototype_ `FSdfPath(FSdfPath&& Other);`
- L38 _public prototype_ `FSdfPath& operator=(const FSdfPath& Other);`
- L39 _public prototype_ `FSdfPath& operator=(FSdfPath&& Other);`
- L41 _public prototype_ `~FSdfPath();`
- L43 _public prototype_ `bool operator==(const FSdfPath& Other) const;`
- L44 _public prototype_ `bool operator!=(const FSdfPath& Other) const;`
- L45 _public prototype_ `bool operator<(const FSdfPath& Other) const;`
- L46 _public prototype_ `bool operator<=(const FSdfPath& Other) const;`
- L54 _public prototype_ `explicit FSdfPath(const pxr::SdfPath& InSdfPath);`
- L55 _public prototype_ `explicit FSdfPath(pxr::SdfPath&& InSdfPath);`
- L56 _public prototype_ `FSdfPath& operator=(const pxr::SdfPath& InSdfPath);`
- L57 _public prototype_ `FSdfPath& operator=(pxr::SdfPath&& InSdfPath);`
- L59 _public prototype_ `operator pxr::SdfPath&();`
- L60 _public prototype_ `operator const pxr::SdfPath&() const;`
- L65 _public prototype_ `static const FSdfPath& AbsoluteRootPath();`
- L70 _public prototype_ `static bool IsValidPathString(const TCHAR* PathString, FString* OutErrorMessage = nullptr);` — Returns true if PathString is a valid path string, meaning that passing the string to the FSdfPath constructor will result in a valid, non-empty FSdfPath. Otherwise, returns false and, if OutErrorMessage is not null, sets it to the parse error.
- L72 _public prototype_ `bool IsEmpty() const noexcept;`
- L74 _public prototype_ `bool IsAbsoluteRootPath() const;`
- L75 _public prototype_ `bool IsPrimPath() const;`
- L76 _public prototype_ `bool IsAbsoluteRootOrPrimPath() const;`
- L77 _public prototype_ `bool IsPrimPropertyPath() const;`
- L78 _public prototype_ `bool IsPropertyPath() const;`
- L79 _public prototype_ `bool IsRelationalAttributePath() const;`
- L80 _public prototype_ `bool IsTargetPath() const;`
- L81 _public prototype_ `FString GetName() const;`
- L82 _public prototype_ `FString GetElementString() const;`
- L83 _public prototype_ `FSdfPath GetAbsoluteRootOrPrimPath() const;`
- L85 _public prototype_ `FSdfPath ReplaceName(const TCHAR* NewLeafName) const;`
- L86 _public prototype_ `FSdfPath ReplacePrefix(const UE::FSdfPath& OldPrefix, const UE::FSdfPath& NewPrefix, bool FixTargetPaths = true) const;`
- L90 _public prototype_ `FSdfPath GetParentPath() const;`
- L91 _public prototype_ `FSdfPath GetPrimPath() const;`
- L92 _public prototype_ `FSdfPath AppendPath(const UE::FSdfPath& NewRelativeSuffix) const;`
- L93 _public prototype_ `FSdfPath AppendChild(const TCHAR* ChildName) const;`
- L94 _public prototype_ `FSdfPath AppendProperty(FName PropertyName) const;`
- L96 _public prototype_ `FSdfPath StripAllVariantSelections() const;`
- L98 _public prototype_ `FString GetString() const;`
- L100 _public prototype_ `TArray<FSdfPath> GetPrefixes() const;`
- L101 _public prototype_ `int32 GetPathElementCount() const;`
- L103 _public prototype_ `bool HasPrefix(const UE::FSdfPath& Prefix) const;`
- L105 _public prototype_ `FSdfPath MakeAbsolutePath(const FSdfPath& Anchor) const;`
- L106 _public prototype_ `FSdfPath MakeRelativePath(const FSdfPath& Anchor) const;`
- L109 _private member_ `TUniquePtr<Internal::FSdfPathImpl> Impl;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API UNREALUSDWRAPPER_API`
- L19 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Internal` (scope `UE`)

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UsdWrappers/SdfPayloadsProxy.h` (Public)


#### class `UE::FSdfPayloadsProxy`  
`class FSdfPayloadsProxy`  
_L33-65_
- desc: Minimal pxr::SdfPayloadsProxy wrapper for Unreal that can be used from no-rtti modules.
- L36 _public prototype_ `FSdfPayloadsProxy();`
- L38 _public prototype_ `FSdfPayloadsProxy(const FSdfPayloadsProxy& Other);`
- L39 _public prototype_ `FSdfPayloadsProxy(FSdfPayloadsProxy&& Other);`
- L40 _public prototype_ `~FSdfPayloadsProxy();`
- L42 _public prototype_ `FSdfPayloadsProxy& operator=(const FSdfPayloadsProxy& Other);`
- L43 _public prototype_ `FSdfPayloadsProxy& operator=(FSdfPayloadsProxy&& Other);`
- L45 _public prototype_ `explicit operator bool() const;`
- L50 _public prototype_ `explicit FSdfPayloadsProxy(const pxr::SdfPayloadsProxy& InSdfPayloadsProxy);`
- L51 _public prototype_ `explicit FSdfPayloadsProxy(pxr::SdfPayloadsProxy&& InSdfPayloadsProxy);`
- L52 _public prototype_ `FSdfPayloadsProxy& operator=(const pxr::SdfPayloadsProxy& InSdfPayloadsProxy);`
- L53 _public prototype_ `FSdfPayloadsProxy& operator=(pxr::SdfPayloadsProxy&& InSdfPayloadsProxy);`
- L55 _public prototype_ `operator pxr::SdfPayloadsProxy&();`
- L56 _public prototype_ `operator const pxr::SdfPayloadsProxy&() const;`
- L61 _public prototype_ `TArray<FSdfPayload> GetAppliedItems() const;`
- L64 _private member_ `TUniquePtr<Internal::FSdfPayloadsProxyImpl> Impl;`

#### Free symbols / members of external scopes

- L17 _typedef_ `using SdfPayloadsProxy = SdfListEditorProxy<SdfPayloadTypePolicy>;`
- L22 _namespace_ `namespace UE`
- L25 _namespace_ `namespace Internal` (scope `UE`)

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UsdWrappers/SdfPrimSpec.h` (Public)


#### enum `UE::ESdfSpecType`  
`enum class ESdfSpecType`  
_L36-52_
- desc: Corresponds to pxr::SdfSpecType, refer to the USD SDK documentation
- L38 _public enumerator_ `SdfSpecTypeUnknown = 0`
- L39 _public enumerator_ `SdfSpecTypeAttribute`
- L40 _public enumerator_ `SdfSpecTypeConnection`
- L41 _public enumerator_ `SdfSpecTypeExpression`
- L42 _public enumerator_ `SdfSpecTypeMapper`
- L43 _public enumerator_ `SdfSpecTypeMapperArg`
- L44 _public enumerator_ `SdfSpecTypePrim`
- L45 _public enumerator_ `SdfSpecTypePseudoRoot`
- L46 _public enumerator_ `SdfSpecTypeRelationship`
- L47 _public enumerator_ `SdfSpecTypeRelationshipTarget`
- L48 _public enumerator_ `SdfSpecTypeVariant`
- L49 _public enumerator_ `SdfSpecTypeVariantSet`
- L51 _public enumerator_ `SdfNumSpecTypes`

#### class `UE::FSdfPrimSpec`  
`class FSdfPrimSpec`  
_L57-105_
- desc: Minimal pxr::SdfPrimSpecHandle wrapper for Unreal that can be used from no-rtti modules.
- L60 _public prototype_ `FSdfPrimSpec();`
- L62 _public prototype_ `FSdfPrimSpec(const FSdfPrimSpec& Other);`
- L63 _public prototype_ `FSdfPrimSpec(FSdfPrimSpec&& Other);`
- L64 _public prototype_ `~FSdfPrimSpec();`
- L66 _public prototype_ `FSdfPrimSpec& operator=(const FSdfPrimSpec& Other);`
- L67 _public prototype_ `FSdfPrimSpec& operator=(FSdfPrimSpec&& Other);`
- L69 _public prototype_ `bool operator==(const FSdfPrimSpec& Other) const;`
- L70 _public prototype_ `bool operator!=(const FSdfPrimSpec& Other) const;`
- L72 _public prototype_ `explicit operator bool() const;`
- L77 _public prototype_ `explicit FSdfPrimSpec(const pxr::SdfPrimSpecHandle& InSdfPrimSpec);`
- L78 _public prototype_ `explicit FSdfPrimSpec(pxr::SdfPrimSpecHandle&& InSdfPrimSpec);`
- L79 _public prototype_ `FSdfPrimSpec& operator=(const pxr::SdfPrimSpecHandle& InSdfPrimSpec);`
- L80 _public prototype_ `FSdfPrimSpec& operator=(pxr::SdfPrimSpecHandle&& InSdfPrimSpec);`
- L82 _public prototype_ `operator pxr::SdfPrimSpecHandle&();`
- L83 _public prototype_ `operator const pxr::SdfPrimSpecHandle&() const;`
- L88 _public prototype_ `ESdfSpecType GetSpecType() const;`
- L89 _public prototype_ `FSdfLayerWeak GetLayer() const;`
- L90 _public prototype_ `FSdfPath GetPath() const;`
- L92 _public prototype_ `FSdfPrimSpec GetRealNameParent() const;`
- L93 _public prototype_ `bool RemoveNameChild(const FSdfPrimSpec& Child);`
- L95 _public prototype_ `UE::FSdfAttributeSpec GetAttributeAtPath(const UE::FSdfPath& Path) const;`
- L97 _public prototype_ `FSdfPayloadsProxy GetPayloadList() const;`
- L98 _public prototype_ `FSdfReferencesProxy GetReferenceList() const;`
- L100 _public prototype_ `FName GetTypeName() const;`
- L101 _public prototype_ `FName GetName() const;`
- L104 _private member_ `TUniquePtr<Internal::FSdfPrimSpecImpl> Impl;`

#### Free symbols / members of external scopes

- L19 _typedef_ `using SdfPrimSpecHandle = SdfHandle<SdfPrimSpec>;`
- L23 _namespace_ `namespace UE`
- L30 _namespace_ `namespace Internal` (scope `UE`)

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UsdWrappers/SdfReferencesProxy.h` (Public)


#### class `UE::FSdfReferencesProxy`  
`class FSdfReferencesProxy`  
_L33-65_
- desc: Minimal pxr::SdfReferencesProxy wrapper for Unreal that can be used from no-rtti modules.
- L36 _public prototype_ `FSdfReferencesProxy();`
- L38 _public prototype_ `FSdfReferencesProxy(const FSdfReferencesProxy& Other);`
- L39 _public prototype_ `FSdfReferencesProxy(FSdfReferencesProxy&& Other);`
- L40 _public prototype_ `~FSdfReferencesProxy();`
- L42 _public prototype_ `FSdfReferencesProxy& operator=(const FSdfReferencesProxy& Other);`
- L43 _public prototype_ `FSdfReferencesProxy& operator=(FSdfReferencesProxy&& Other);`
- L45 _public prototype_ `explicit operator bool() const;`
- L50 _public prototype_ `explicit FSdfReferencesProxy(const pxr::SdfReferencesProxy& InSdfReferencesProxy);`
- L51 _public prototype_ `explicit FSdfReferencesProxy(pxr::SdfReferencesProxy&& InSdfReferencesProxy);`
- L52 _public prototype_ `FSdfReferencesProxy& operator=(const pxr::SdfReferencesProxy& InSdfReferencesProxy);`
- L53 _public prototype_ `FSdfReferencesProxy& operator=(pxr::SdfReferencesProxy&& InSdfReferencesProxy);`
- L55 _public prototype_ `operator pxr::SdfReferencesProxy&();`
- L56 _public prototype_ `operator const pxr::SdfReferencesProxy&() const;`
- L61 _public prototype_ `TArray<FSdfReference> GetAppliedItems() const;`
- L64 _private member_ `TUniquePtr<Internal::FSdfReferencesProxyImpl> Impl;`

#### Free symbols / members of external scopes

- L17 _typedef_ `using SdfReferencesProxy = SdfListEditorProxy<SdfReferenceTypePolicy>;`
- L22 _namespace_ `namespace UE`
- L25 _namespace_ `namespace Internal` (scope `UE`)

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UsdWrappers/UsdAttribute.h` (Public)


#### class `UE::FUsdAttribute`  
`class FUsdAttribute`  
_L35-114_
- desc: Minimal pxr::UsdAttribute wrapper for Unreal that can be used from no-rtti modules.
- L38 _public prototype_ `FUsdAttribute();`
- L40 _public prototype_ `FUsdAttribute(const FUsdAttribute& Other);`
- L41 _public prototype_ `FUsdAttribute(FUsdAttribute&& Other);`
- L42 _public prototype_ `~FUsdAttribute();`
- L44 _public prototype_ `FUsdAttribute& operator=(const FUsdAttribute& Other);`
- L45 _public prototype_ `FUsdAttribute& operator=(FUsdAttribute&& Other);`
- L47 _public prototype_ `bool operator==(const FUsdAttribute& Other) const;`
- L48 _public prototype_ `bool operator!=(const FUsdAttribute& Other) const;`
- L50 _public prototype_ `explicit operator bool() const;`
- L55 _public prototype_ `explicit FUsdAttribute(const pxr::UsdAttribute& InUsdAttribute);`
- L56 _public prototype_ `explicit FUsdAttribute(pxr::UsdAttribute&& InUsdAttribute);`
- L57 _public prototype_ `FUsdAttribute& operator=(const pxr::UsdAttribute& InUsdAttribute);`
- L58 _public prototype_ `FUsdAttribute& operator=(pxr::UsdAttribute&& InUsdAttribute);`
- L60 _public prototype_ `operator pxr::UsdAttribute&();`
- L61 _public prototype_ `operator const pxr::UsdAttribute&() const;`
- L66 _public prototype_ `operator pxr::UsdProperty&();` — Also define the conversion operators directly to the base class as we can't "forward declare the class inheritance", but it is nice to be able to pass an UE::FUsdAttribute to a function that takes an pxr::UsdProperty directly
- L67 _public prototype_ `operator const pxr::UsdProperty&() const;`
- L72 _public prototype_ `bool GetMetadata(const TCHAR* Key, UE::FVtValue& Value) const;`
- L73 _public prototype_ `bool HasMetadata(const TCHAR* Key) const;`
- L74 _public prototype_ `bool SetMetadata(const TCHAR* Key, const UE::FVtValue& Value) const;`
- L75 _public prototype_ `bool ClearMetadata(const TCHAR* Key) const;`
- L79 _public prototype_ `FName GetName() const;`
- L80 _public prototype_ `FName GetBaseName() const;`
- L81 _public prototype_ `FName GetTypeName() const;`
- L82 _public prototype_ `FString GetCPPTypeName() const;`
- L84 _public prototype_ `bool GetTimeSamples(TArray<double>& Times) const;`
- L85 _public prototype_ `size_t GetNumTimeSamples() const;`
- L87 _public prototype_ `bool HasValue() const;`
- L88 _public prototype_ `bool HasAuthoredValue() const;`
- L89 _public prototype_ `bool HasFallbackValue() const;`
- L91 _public prototype_ `bool ValueMightBeTimeVarying() const;`
- L93 _public prototype_ `bool Get(UE::FVtValue& Value, TOptional<double> Time = {}) const;`
- L95 _public prototype_ `FUsdResolveInfo GetResolveInfo(double Time) const;`
- L97 _public prototype_ `bool Set(const UE::FVtValue& Value, TOptional<double> Time = {}) const;`
- L100 _public prototype_ `template <typename T> bool Get(T& Value, TOptional<double> Time = {}) const;`
- L102 _public prototype_ `bool Clear() const;`
- L103 _public prototype_ `bool ClearAtTime(double Time) const;`
- L105 _public prototype_ `bool ClearConnections() const;`
- L107 _public prototype_ `static bool GetUnionedTimeSamples(const TArray<UE::FUsdAttribute>& Attrs, TArray<double>& OutTimes);`
- L109 _public prototype_ `FSdfPath GetPath() const;`
- L110 _public prototype_ `FUsdPrim GetPrim() const;`
- L113 _private member_ `TUniquePtr<Internal::FUsdAttributeImpl> Impl;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L27 _namespace_ `namespace Internal` (scope `UE`)
- L117 _namespace_ `namespace UsdUtils`
- L121 _prototype_ `template<typename ValueType> ValueType GetAttributeValue(const UE::FUsdPrim& Prim, FStringView AttributeName, TOptional<double> Time = {});` (scope `UsdUtils`) — Returns the attribute value for the given prim and attribute name. If the attribute doesn't exist, it returns the default value for the type.
- L127 _prototype_ `template<typename ValueType> bool GetAuthoredAttributeValue(const UE::FUsdPrim& InPrim, FStringView InAttributeName, ValueType& OutValue, TOptional<double> InTime = {});` (scope `UsdUtils`) — Outputs the authored attribute value for the given prim and attribute name, and returns true. If the attribute doesn't exist, returns false and leaves OutValue unassigned. If the attribute does exist but has no authored opinion, returns false but assigns OutValue with the attribute's fallback value, if possible.

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UsdWrappers/UsdEditContext.h` (Public)


#### class `UE::FUsdEditContext`  
`class FUsdEditContext final`  
_L21-33_
- desc: Minimal pxr::UsdEditContext wrapper for Unreal that can be used from no-rtti modules.
- L23 _private prototype_ `FUsdEditContext(const FUsdEditContext& Other) = delete;`
- L24 _private prototype_ `FUsdEditContext& operator=(const FUsdEditContext& Other) = delete;`
- L27 _public prototype_ `explicit FUsdEditContext(const FUsdStageWeak& Stage);`
- L28 _public prototype_ `FUsdEditContext(const FUsdStageWeak& Stage, const FSdfLayer& EditTarget);`
- L29 _public prototype_ `~FUsdEditContext();`
- L32 _private member_ `TUniquePtr<Internal::FUsdEditContextImpl> Impl;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UNREALUSDWRAPPER_API`
- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Internal` (scope `UE`)

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UsdWrappers/UsdGeomBBoxCache.h` (Public)


#### class `UE::FUsdGeomBBoxCache`  
`class FUsdGeomBBoxCache`  
_L38-82_
- desc: Minimal pxr::UsdGeomBBoxCache wrapper for Unreal that can be used from no-rtti modules. Unlike the other wrapper types, FUsdGeomBBoxCache contains its own mutex in order to try and make its usage somewhat thread-safe. The wrapped functions will use this mutex already, and the conversion operators that return the underlying type will check that the mutex is locked before returning (the caller is expected to lock the mutex before using the operators).
- L41 _public prototype_ `FUsdGeomBBoxCache(double Time, EUsdPurpose IncludedPurposeFlags, bool bUseExtentsHint = false, bool bIgnoreVisibility = false);`
- L42 _public prototype_ `FUsdGeomBBoxCache(const FUsdGeomBBoxCache& Other);`
- L43 _public prototype_ `FUsdGeomBBoxCache(FUsdGeomBBoxCache&& Other);`
- L45 _public prototype_ `FUsdGeomBBoxCache& operator=(const FUsdGeomBBoxCache& Other);`
- L46 _public prototype_ `FUsdGeomBBoxCache& operator=(FUsdGeomBBoxCache&& Other);`
- L48 _public prototype_ `~FUsdGeomBBoxCache();`
- L53 _public prototype_ `explicit FUsdGeomBBoxCache(const pxr::UsdGeomBBoxCache& InUsdGeomBBoxCache);`
- L54 _public prototype_ `explicit FUsdGeomBBoxCache(pxr::UsdGeomBBoxCache&& InUsdGeomBBoxCache);`
- L56 _public prototype_ `operator pxr::UsdGeomBBoxCache&();`
- L57 _public prototype_ `operator const pxr::UsdGeomBBoxCache&() const;`
- L62 _public prototype_ `void Clear();`
- L64 _public prototype_ `void SetIncludedPurposes(EUsdPurpose IncludedPurposeFlags);`
- L65 _public prototype_ `EUsdPurpose GetIncludedPurposes() const;`
- L67 _public prototype_ `bool GetUseExtentsHint() const;`
- L68 _public prototype_ `bool GetIgnoreVisibility() const;`
- L70 _public prototype_ `void SetTime(double UsdTimeCode);`
- L71 _public prototype_ `double GetTime() const;`
- L78 _public member_ `mutable FRWLock Lock;` — The underlying pxr::UsdGeomBBoxCache object is not thread-safe, so we have this. This mutex will be internally locked for all of the wrapped function calls. It is exposed so that it can be locked by the user in case it is desirable to use the underlying pxr::UsdGeomBBoxCache type directly
- L81 _private member_ `TUniquePtr<Internal::FUsdGeomBBoxCacheImpl> Impl;`

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Internal` (scope `UE`)

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UsdWrappers/UsdGeomSubset.h` (Public)


#### class `UE::FUsdGeomSubset`  
`class FUsdGeomSubset`  
_L26-65_
- desc: Minimal pxr::UsdGeomSubset wrapper for Unreal that can be used from no-rtti modules.
- L29 _public prototype_ `FUsdGeomSubset();`
- L30 _public prototype_ `FUsdGeomSubset(const FUsdPrim& UsdPrim);`
- L32 _public prototype_ `FUsdGeomSubset(const FUsdGeomSubset& Other);`
- L33 _public prototype_ `FUsdGeomSubset(FUsdGeomSubset&& Other);`
- L34 _public prototype_ `~FUsdGeomSubset();`
- L36 _public prototype_ `FUsdGeomSubset& operator=(const FUsdGeomSubset& Other);`
- L37 _public prototype_ `FUsdGeomSubset& operator=(FUsdGeomSubset&& Other);`
- L39 _public prototype_ `explicit operator bool() const;`
- L44 _public prototype_ `explicit FUsdGeomSubset(const pxr::UsdGeomSubset& InUsdGeomSubset);`
- L45 _public prototype_ `explicit FUsdGeomSubset(pxr::UsdGeomSubset&& InUsdGeomSubset);`
- L46 _public prototype_ `FUsdGeomSubset& operator=(const pxr::UsdGeomSubset& InUsdGeomSubset);`
- L47 _public prototype_ `FUsdGeomSubset& operator=(pxr::UsdGeomSubset&& InUsdGeomSubset);`
- L49 _public prototype_ `operator pxr::UsdGeomSubset&();`
- L50 _public prototype_ `operator const pxr::UsdGeomSubset&() const;`
- L55 _public prototype_ `FUsdPrim GetPrim() const;`
- L57 _public prototype_ `FUsdAttribute GetElementTypeAttr() const;`
- L59 _public prototype_ `FUsdAttribute GetFamilyNameAttr() const;`
- L61 _public prototype_ `FUsdAttribute GetIndicesAttr() const;`
- L64 _private member_ `TUniquePtr<Internal::FUsdGeomSubsetImpl> Impl;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Internal` (scope `UE`)

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UsdWrappers/UsdGeomXformable.h` (Public)


#### class `UE::FUsdGeomXformable`  
`class FUsdGeomXformable : public FUsdTyped`  
_L32-71_
- inherits: `FUsdTyped`
- desc: Minimal pxr::UsdGeomXformable wrapper for Unreal that can be used from no-rtti modules.
- L35 _public prototype_ `FUsdGeomXformable();`
- L36 _public prototype_ `FUsdGeomXformable(const FUsdGeomXformable& Other);`
- L37 _public prototype_ `FUsdGeomXformable(FUsdGeomXformable&& Other);`
- L39 _public prototype_ `explicit FUsdGeomXformable(const FUsdPrim& Prim);`
- L41 _public prototype_ `FUsdGeomXformable& operator=(const FUsdGeomXformable& Other);`
- L42 _public prototype_ `FUsdGeomXformable& operator=(FUsdGeomXformable&& Other);`
- L44 _public prototype_ `~FUsdGeomXformable();`
- L46 _public prototype_ `explicit operator bool() const;`
- L51 _public prototype_ `explicit FUsdGeomXformable(const pxr::UsdGeomXformable& InUsdGeomXformable);`
- L52 _public prototype_ `explicit FUsdGeomXformable(pxr::UsdGeomXformable&& InUsdGeomXformable);`
- L53 _public prototype_ `explicit FUsdGeomXformable(const pxr::UsdPrim& Prim);`
- L55 _public prototype_ `operator pxr::UsdGeomXformable&();`
- L56 _public prototype_ `operator const pxr::UsdGeomXformable&() const;`
- L61 _public prototype_ `bool GetResetXformStack() const;`
- L63 _public prototype_ `bool TransformMightBeTimeVarying() const;`
- L64 _public prototype_ `bool GetTimeSamples(TArray<double>* Times) const;`
- L66 _public prototype_ `FUsdAttribute GetXformOpOrderAttr() const;`
- L67 _public prototype_ `bool ClearXformOpOrder() const;`
- L70 _private member_ `TUniquePtr<Internal::FUsdGeomXformableImpl> Impl;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L24 _namespace_ `namespace Internal` (scope `UE`)

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UsdWrappers/UsdPayloads.h` (Public)


#### class `UE::FUsdPayloads`  
`class FUsdPayloads`  
_L36-102_
- desc: Minimal pxr::UsdPayloads wrapper for Unreal that can be used from no-rtti modules.
- L39 _public prototype_ `FUsdPayloads();`
- L40 _public prototype_ `FUsdPayloads(const FUsdPayloads& Other);`
- L41 _public prototype_ `FUsdPayloads(FUsdPayloads&& Other);`
- L43 _public prototype_ `FUsdPayloads& operator=(const FUsdPayloads& Other);`
- L44 _public prototype_ `FUsdPayloads& operator=(FUsdPayloads&& Other);`
- L46 _public prototype_ `~FUsdPayloads();`
- L48 _public prototype_ `explicit operator bool() const;`
- L52 _public prototype_ `explicit FUsdPayloads(const pxr::UsdPayloads& InUsdPayloads);` — Auto conversion from/to pxr::UsdPayloads
- L53 _public prototype_ `explicit FUsdPayloads(pxr::UsdPayloads&& InUsdPayloads);`
- L54 _public prototype_ `FUsdPayloads& operator=(const pxr::UsdPayloads& InUsdPayloads);`
- L55 _public prototype_ `FUsdPayloads& operator=(pxr::UsdPayloads&& InUsdPayloads);`
- L57 _public prototype_ `operator pxr::UsdPayloads();`
- L58 _public prototype_ `operator const pxr::UsdPayloads() const;`
- L64 _private prototype_ `explicit FUsdPayloads(const pxr::UsdPrim& InPrim);` — FUsdPayloads instances are only constructable by instances of FUsdPrim. Use FUsdPrim::GetPayloads() to construct an instance.
- L69 _public prototype_ `bool AddPayload(const FSdfPayload& Payload, EUsdListPosition Position = EUsdListPosition::BackOfPrependList);`
- L71 _public prototype_ `bool AddPayload( const FString& Identifier, const FSdfPath& PrimPath, const FSdfLayerOffset& LayerOffset = {}, EUsdListPosition Position = EUsdListPosition::BackOfPrependList );`
- L78 _public prototype_ `bool AddPayload( const FString& Identifier, const FSdfLayerOffset& LayerOffset = {}, EUsdListPosition Position = EUsdListPosition::BackOfPrependList );`
- L84 _public prototype_ `bool AddInternalPayload( const FSdfPath& PrimPath, const FSdfLayerOffset& LayerOffset = {}, EUsdListPosition Position = EUsdListPosition::BackOfPrependList );`
- L90 _public prototype_ `bool RemovePayload(const FSdfPayload& Payload);`
- L92 _public prototype_ `bool ClearPayloads();`
- L94 _public prototype_ `bool SetPayloads(const TArray<FSdfPayload>& Items);`
- L96 _public prototype_ `FUsdPrim GetPrim() const;`
- L99 _private member_ `TUniquePtr<Internal::FUsdPayloadsImpl> Impl;`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L28 _namespace_ `namespace Internal` (scope `UE`)

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UsdWrappers/UsdPrim.h` (Public)


#### enum `UE::ESdfSpecifier`  
`enum class ESdfSpecifier`  
_L42-48_
- desc: Corresponds to pxr::SdfSpecifier, refer to the USD SDK documentation
- L44 _public enumerator_ `Def` — Defines a concrete prim
- L45 _public enumerator_ `Over` — Overrides an existing prim
- L46 _public enumerator_ `Class` — Defines an abstract prim
- L47 _public enumerator_ `Num` — The number of specifiers

#### class `UE::FUsdPrim`  
`class FUsdPrim`  
_L53-185_
- desc: Minimal pxr::UsdPrim wrapper for Unreal that can be used from no-rtti modules.
- L56 _public prototype_ `FUsdPrim();`
- L58 _public prototype_ `FUsdPrim(const FUsdPrim& Other);`
- L59 _public prototype_ `FUsdPrim(FUsdPrim&& Other);`
- L60 _public prototype_ `~FUsdPrim();`
- L62 _public prototype_ `FUsdPrim& operator=(const FUsdPrim& Other);`
- L63 _public prototype_ `FUsdPrim& operator=(FUsdPrim&& Other);`
- L65 _public prototype_ `bool operator==(const FUsdPrim& Other) const;`
- L66 _public prototype_ `bool operator!=(const FUsdPrim& Other) const;`
- L68 _public prototype_ `explicit operator bool() const;`
- L73 _public prototype_ `explicit FUsdPrim(const pxr::UsdPrim& InUsdPrim);`
- L74 _public prototype_ `explicit FUsdPrim(pxr::UsdPrim&& InUsdPrim);`
- L75 _public prototype_ `FUsdPrim& operator=(const pxr::UsdPrim& InUsdPrim);`
- L76 _public prototype_ `FUsdPrim& operator=(pxr::UsdPrim&& InUsdPrim);`
- L78 _public prototype_ `operator pxr::UsdPrim&();`
- L79 _public prototype_ `operator const pxr::UsdPrim&() const;`
- L84 _public prototype_ `bool GetMetadata(const TCHAR* Key, UE::FVtValue& Value) const;`
- L85 _public prototype_ `bool HasMetadata(const TCHAR* Key) const;`
- L86 _public prototype_ `bool SetMetadata(const TCHAR* Key, const UE::FVtValue& Value) const;`
- L87 _public prototype_ `bool ClearMetadata(const TCHAR* Key) const;`
- L88 _public prototype_ `TMap<FString, UE::FVtValue> GetAllMetadata() const;`
- L89 _public prototype_ `TMap<FString, UE::FVtValue> GetAllAuthoredMetadata() const;`
- L91 _public prototype_ `FString GetDisplayName() const;`
- L92 _public prototype_ `bool SetDisplayName(const FString& Name) const;`
- L93 _public prototype_ `bool ClearDisplayName() const;`
- L94 _public prototype_ `bool HasAuthoredDisplayName() const;`
- L98 _public prototype_ `bool SetSpecifier(ESdfSpecifier Specifier);`
- L100 _public prototype_ `bool IsActive() const;`
- L101 _public prototype_ `bool SetActive(bool bActive);`
- L103 _public prototype_ `bool IsValid() const;`
- L104 _public prototype_ `bool IsPseudoRoot() const;`
- L105 _public prototype_ `bool IsModel() const;`
- L106 _public prototype_ `bool IsDefined() const;`
- L107 _public prototype_ `bool IsGroup() const;`
- L109 _public prototype_ `TArray<FName> GetAppliedSchemas() const;`
- L111 _public prototype_ `bool IsA(FName SchemaIdentifier) const;`
- L112 _public prototype_ `bool HasAPI(FName SchemaIdentifier) const;`
- L113 _public prototype_ `bool HasAPI(FName SchemaIdentifier, FName InstanceName) const;`
- L115 _public prototype_ `bool CanApplyAPI(FName SchemaIdentifier, FString* OutWhyNot = nullptr) const;`
- L116 _public prototype_ `bool CanApplyAPI(FName SchemaIdentifier, FName InstanceName, FString* OutWhyNot = nullptr) const;`
- L118 _public prototype_ `bool ApplyAPI(FName SchemaIdentifier) const;`
- L119 _public prototype_ `bool ApplyAPI(FName SchemaIdentifier, FName InstanceName) const;`
- L121 _public prototype_ `bool RemoveAPI(FName SchemaIdentifier) const;`
- L122 _public prototype_ `bool RemoveAPI(FName SchemaIdentifier, FName InstanceName) const;`
- L124 _public prototype_ `const FSdfPath GetPrimPath() const;`
- L125 _public prototype_ `FUsdStage GetStage() const;`
- L127 _public prototype_ `FName GetName() const;`
- L129 _public prototype_ `FName GetTypeName() const;`
- L130 _public prototype_ `bool SetTypeName(FName TypeName) const;`
- L131 _public prototype_ `bool ClearTypeName() const;`
- L132 _public prototype_ `bool HasAuthoredTypeName() const;`
- L134 _public prototype_ `FUsdPrim GetParent() const;`
- L136 _public prototype_ `TArray<FUsdPrim> GetChildren() const;`
- L137 _public prototype_ `TArray<FUsdPrim> GetFilteredChildren(bool bTraverseInstanceProxies) const;`
- L139 _public prototype_ `FUsdVariantSets GetVariantSets() const;`
- L140 _public prototype_ `FUsdVariantSet GetVariantSet(const FString& VariantSetName) const;`
- L141 _public prototype_ `bool HasVariantSets() const;`
- L143 _public prototype_ `FUsdPayloads GetPayloads() const;`
- L144 _public prototype_ `bool HasAuthoredPayloads() const;`
- L145 _public prototype_ `bool IsLoaded() const;`
- L146 _public prototype_ `void Load(EUsdLoadPolicy Policy = EUsdLoadPolicy::UsdLoadWithDescendants);`
- L147 _public prototype_ `void Unload();`
- L149 _public prototype_ `FUsdReferences GetReferences() const;`
- L150 _public prototype_ `bool HasAuthoredReferences() const;`
- L152 _public prototype_ `TArray<FSdfPrimSpec> GetPrimStack() const;`
- L154 _public prototype_ `FPcpPrimIndex GetPrimIndex() const;`
- L155 _public prototype_ `FPcpPrimIndex ComputeExpandedPrimIndex() const;`
- L157 _public prototype_ `bool RemoveProperty(FName PropName) const;`
- L159 _public prototype_ `FUsdAttribute CreateAttribute(const TCHAR* AttrName, FName TypeName) const;`
- L160 _public prototype_ `TArray<FUsdAttribute> GetAttributes() const;`
- L161 _public prototype_ `FUsdAttribute GetAttribute(const TCHAR* AttrName) const;`
- L162 _public prototype_ `bool HasAttribute(const TCHAR* AttrName) const;`
- L164 _public prototype_ `FUsdRelationship CreateRelationship(const TCHAR* RelName, bool bCustom = true) const;`
- L165 _public prototype_ `TArray<FUsdRelationship> GetRelationships() const;`
- L166 _public prototype_ `FUsdRelationship GetRelationship(const TCHAR* RelationshipName) const;`
- L167 _public prototype_ `bool HasRelationship(const TCHAR* RelName) const;`
- L169 _public prototype_ `bool IsInstanceable() const;`
- L170 _public prototype_ `bool SetInstanceable(bool bInstanceable) const;`
- L171 _public prototype_ `bool ClearInstanceable() const;`
- L172 _public prototype_ `bool HasAuthoredInstanceable() const;`
- L173 _public prototype_ `bool IsInstance() const;`
- L174 _public prototype_ `bool IsInstanceProxy() const;`
- L175 _public prototype_ `bool IsPrototype() const;`
- L176 _public prototype_ `bool IsInPrototype() const;`
- L177 _public prototype_ `FUsdPrim GetPrototype() const;`
- L178 _public prototype_ `FUsdPrim GetPrimInPrototype() const;`
- L179 _public prototype_ `TArray<FUsdPrim> GetInstances() const;`
- L180 _public prototype_ `static bool IsPrototypePath(const FSdfPath& Path);`
- L181 _public prototype_ `static bool IsPathInPrototype(const FSdfPath& Path);`
- L184 _private member_ `TUniquePtr<Internal::FUsdPrimImpl> Impl;`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L36 _namespace_ `namespace Internal` (scope `UE`)

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UsdWrappers/UsdReferences.h` (Public)


#### class `UE::FUsdReferences`  
`class FUsdReferences`  
_L36-102_
- desc: Minimal pxr::UsdReferences wrapper for Unreal that can be used from no-rtti modules.
- L39 _public prototype_ `FUsdReferences();`
- L40 _public prototype_ `FUsdReferences(const FUsdReferences& Other);`
- L41 _public prototype_ `FUsdReferences(FUsdReferences&& Other);`
- L43 _public prototype_ `FUsdReferences& operator=(const FUsdReferences& Other);`
- L44 _public prototype_ `FUsdReferences& operator=(FUsdReferences&& Other);`
- L46 _public prototype_ `~FUsdReferences();`
- L48 _public prototype_ `explicit operator bool() const;`
- L52 _public prototype_ `explicit FUsdReferences(const pxr::UsdReferences& InUsdReferences);` — Auto conversion from/to pxr::UsdReferences
- L53 _public prototype_ `explicit FUsdReferences(pxr::UsdReferences&& InUsdReferences);`
- L54 _public prototype_ `FUsdReferences& operator=(const pxr::UsdReferences& InUsdReferences);`
- L55 _public prototype_ `FUsdReferences& operator=(pxr::UsdReferences&& InUsdReferences);`
- L57 _public prototype_ `operator pxr::UsdReferences();`
- L58 _public prototype_ `operator const pxr::UsdReferences() const;`
- L64 _private prototype_ `explicit FUsdReferences(const pxr::UsdPrim& InPrim);` — FUsdReferences instances are only constructable by instances of FUsdPrim. Use FUsdPrim::GetReferences() to construct an instance.
- L69 _public prototype_ `bool AddReference(const FSdfReference& Reference, EUsdListPosition Position = EUsdListPosition::BackOfPrependList);`
- L71 _public prototype_ `bool AddReference( const FString& Identifier, const FSdfPath& PrimPath, const FSdfLayerOffset& LayerOffset = {}, EUsdListPosition Position = EUsdListPosition::BackOfPrependList );`
- L78 _public prototype_ `bool AddReference( const FString& Identifier, const FSdfLayerOffset& LayerOffset = {}, EUsdListPosition Position = EUsdListPosition::BackOfPrependList );`
- L84 _public prototype_ `bool AddInternalReference( const FSdfPath& PrimPath, const FSdfLayerOffset& LayerOffset = {}, EUsdListPosition Position = EUsdListPosition::BackOfPrependList );`
- L90 _public prototype_ `bool RemoveReference(const FSdfReference& Reference);`
- L92 _public prototype_ `bool ClearReferences();`
- L94 _public prototype_ `bool SetReferences(const TArray<FSdfReference>& Items);`
- L96 _public prototype_ `FUsdPrim GetPrim() const;`
- L99 _private member_ `TUniquePtr<Internal::FUsdReferencesImpl> Impl;`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L28 _namespace_ `namespace Internal` (scope `UE`)

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UsdWrappers/UsdRelationship.h` (Public)


#### class `UE::FUsdRelationship`  
`class FUsdRelationship`  
_L31-81_
- desc: Minimal pxr::UsdRelationship wrapper for Unreal that can be used from no-rtti modules.
- L34 _public prototype_ `FUsdRelationship();`
- L36 _public prototype_ `FUsdRelationship(const FUsdRelationship& Other);`
- L37 _public prototype_ `FUsdRelationship(FUsdRelationship&& Other);`
- L38 _public prototype_ `~FUsdRelationship();`
- L40 _public prototype_ `FUsdRelationship& operator=(const FUsdRelationship& Other);`
- L41 _public prototype_ `FUsdRelationship& operator=(FUsdRelationship&& Other);`
- L43 _public prototype_ `bool operator==(const FUsdRelationship& Other) const;`
- L44 _public prototype_ `bool operator!=(const FUsdRelationship& Other) const;`
- L46 _public prototype_ `explicit operator bool() const;`
- L51 _public prototype_ `explicit FUsdRelationship(const pxr::UsdRelationship& InUsdRelationship);`
- L52 _public prototype_ `explicit FUsdRelationship(pxr::UsdRelationship&& InUsdRelationship);`
- L53 _public prototype_ `FUsdRelationship& operator=(const pxr::UsdRelationship& InUsdRelationship);`
- L54 _public prototype_ `FUsdRelationship& operator=(pxr::UsdRelationship&& InUsdRelationship);`
- L56 _public prototype_ `operator pxr::UsdRelationship&();`
- L57 _public prototype_ `operator const pxr::UsdRelationship&() const;`
- L62 _public prototype_ `operator pxr::UsdProperty&();` — Also define the conversion operators directly to the base class as we can't "forward declare the class inheritance", but it is nice to be able to pass an UE::FUsdRelationship to a function that takes an pxr::UsdProperty directly
- L63 _public prototype_ `operator const pxr::UsdProperty&() const;`
- L68 _public prototype_ `bool GetMetadata(const TCHAR* Key, UE::FVtValue& Value) const;`
- L69 _public prototype_ `bool HasMetadata(const TCHAR* Key) const;`
- L70 _public prototype_ `bool SetMetadata(const TCHAR* Key, const UE::FVtValue& Value) const;`
- L71 _public prototype_ `bool ClearMetadata(const TCHAR* Key) const;`
- L75 _public prototype_ `bool SetTargets(const TArray<UE::FSdfPath>& Targets) const;`
- L76 _public prototype_ `bool ClearTargets(bool bRemoveSpec) const;`
- L77 _public prototype_ `bool GetTargets(TArray<UE::FSdfPath>& Targets) const;`
- L80 _private member_ `TUniquePtr<Internal::FUsdRelationshipImpl> Impl;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Internal` (scope `UE`)

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UsdWrappers/UsdResolveInfo.h` (Public)


#### class `UE::FUsdResolveInfo`  
`class FUsdResolveInfo`  
_L31-56_
- desc: Minimal pxr::UsdResolveInfo wrapper for Unreal that can be used from no-rtti modules.
- L34 _public prototype_ `FUsdResolveInfo();`
- L35 _public prototype_ `FUsdResolveInfo(const FUsdResolveInfo& Other);`
- L36 _public prototype_ `FUsdResolveInfo(FUsdResolveInfo&& Other);`
- L38 _public prototype_ `~FUsdResolveInfo();`
- L43 _public prototype_ `explicit FUsdResolveInfo(const pxr::UsdResolveInfo& InResolveInfo);`
- L44 _public prototype_ `explicit FUsdResolveInfo(pxr::UsdResolveInfo&& InResolveInfo);`
- L46 _public prototype_ `operator pxr::UsdResolveInfo&();`
- L47 _public prototype_ `operator const pxr::UsdResolveInfo&() const;`
- L52 _public prototype_ `FPcpNodeRef GetNode() const;`
- L55 _private member_ `TUniquePtr<Internal::FUsdResolveInfoImpl> Impl;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Internal` (scope `UE`)

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UsdWrappers/UsdSkelAnimQuery.h` (Public)


#### class `UE::FUsdSkelAnimQuery`  
`class FUsdSkelAnimQuery`  
_L34-73_
- desc: Minimal pxr::UsdSkelAnimQuery wrapper for Unreal that can be used from no-rtti modules.
- L37 _public prototype_ `FUsdSkelAnimQuery();`
- L38 _public prototype_ `FUsdSkelAnimQuery(const FUsdSkelAnimQuery& Other);`
- L39 _public prototype_ `FUsdSkelAnimQuery(FUsdSkelAnimQuery&& Other);`
- L40 _public prototype_ `~FUsdSkelAnimQuery();`
- L42 _public prototype_ `FUsdSkelAnimQuery& operator=(const FUsdSkelAnimQuery& Other);`
- L43 _public prototype_ `FUsdSkelAnimQuery& operator=(FUsdSkelAnimQuery&& Other);`
- L45 _public prototype_ `explicit operator bool() const;`
- L50 _public prototype_ `explicit FUsdSkelAnimQuery(const pxr::UsdSkelAnimQuery& InUsdSkelAnimQuery);`
- L51 _public prototype_ `explicit FUsdSkelAnimQuery(pxr::UsdSkelAnimQuery&& InUsdSkelAnimQuery);`
- L53 _public prototype_ `operator pxr::UsdSkelAnimQuery&();`
- L54 _public prototype_ `operator const pxr::UsdSkelAnimQuery&() const;`
- L59 _public prototype_ `bool IsValid() const;`
- L61 _public prototype_ `UE::FUsdPrim GetPrim() const;`
- L63 _public prototype_ `bool ComputeBlendShapeWeights(TArray<float>& Weights, TOptional<double> TimeCode = {}) const;`
- L65 _public prototype_ `bool GetJointTransformTimeSamples(TArray<double>& TimeCodes) const;`
- L66 _public prototype_ `bool GetBlendShapeWeightTimeSamples(TArray<double>& TimeCodes) const;`
- L68 _public prototype_ `TArray<FString> GetJointOrder() const;`
- L69 _public prototype_ `TArray<FString> GetBlendShapeOrder() const;`
- L72 _private member_ `TUniquePtr<Internal::FUsdSkelAnimQueryImpl> Impl;`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Internal` (scope `UE`)

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UsdWrappers/UsdSkelBinding.h` (Public)


#### class `UE::FUsdSkelBinding`  
`class FUsdSkelBinding`  
_L34-63_
- desc: Minimal pxr::UsdSkelBinding wrapper for Unreal that can be used from no-rtti modules.
- L37 _public prototype_ `FUsdSkelBinding();`
- L38 _public prototype_ `FUsdSkelBinding(const FUsdSkelBinding& Other);`
- L39 _public prototype_ `FUsdSkelBinding(FUsdSkelBinding&& Other);`
- L40 _public prototype_ `~FUsdSkelBinding();`
- L42 _public prototype_ `FUsdSkelBinding& operator=(const FUsdSkelBinding& Other);`
- L43 _public prototype_ `FUsdSkelBinding& operator=(FUsdSkelBinding&& Other);`
- L48 _public prototype_ `explicit FUsdSkelBinding(const pxr::UsdSkelBinding& InUsdSkelBinding);`
- L49 _public prototype_ `explicit FUsdSkelBinding(pxr::UsdSkelBinding&& InUsdSkelBinding);`
- L51 _public prototype_ `operator pxr::UsdSkelBinding&();`
- L52 _public prototype_ `operator const pxr::UsdSkelBinding&() const;`
- L57 _public prototype_ `UE::FUsdPrim GetSkeleton() const;`
- L59 _public prototype_ `TArray<UE::FUsdSkelSkinningQuery> GetSkinningTargets() const;`
- L62 _private member_ `TUniquePtr<Internal::FUsdSkelBindingImpl> Impl;`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Internal` (scope `UE`)

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UsdWrappers/UsdSkelBlendShape.h` (Public)


#### class `UE::FUsdSkelBlendShape`  
`class FUsdSkelBlendShape : public FUsdTyped`  
_L32-64_
- inherits: `FUsdTyped`
- desc: Minimal pxr::UsdSkelBlendShape wrapper for Unreal that can be used from no-rtti modules.
- L35 _public prototype_ `FUsdSkelBlendShape();`
- L36 _public prototype_ `FUsdSkelBlendShape(const FUsdPrim& Prim);`
- L37 _public prototype_ `FUsdSkelBlendShape(const FUsdSkelBlendShape& Other);`
- L38 _public prototype_ `FUsdSkelBlendShape(FUsdSkelBlendShape&& Other);`
- L39 _public prototype_ `~FUsdSkelBlendShape();`
- L41 _public prototype_ `FUsdSkelBlendShape& operator=(const FUsdSkelBlendShape& Other);`
- L42 _public prototype_ `FUsdSkelBlendShape& operator=(FUsdSkelBlendShape&& Other);`
- L44 _public prototype_ `explicit operator bool() const;`
- L49 _public prototype_ `explicit FUsdSkelBlendShape(const pxr::UsdSkelBlendShape& InUsdSkelBlendShape);`
- L50 _public prototype_ `explicit FUsdSkelBlendShape(pxr::UsdSkelBlendShape&& InUsdSkelBlendShape);`
- L51 _public prototype_ `explicit FUsdSkelBlendShape(const pxr::UsdPrim& Prim);`
- L53 _public prototype_ `operator pxr::UsdSkelBlendShape&();`
- L54 _public prototype_ `operator const pxr::UsdSkelBlendShape&() const;`
- L59 _public prototype_ `FUsdSkelInbetweenShape GetInbetween(const FString& Name) const;`
- L60 _public prototype_ `TArray<FUsdSkelInbetweenShape> GetInbetweens() const;`
- L63 _private member_ `TUniquePtr<Internal::FUsdSkelBlendShapeImpl> Impl;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L24 _namespace_ `namespace Internal` (scope `UE`)

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UsdWrappers/UsdSkelBlendShapeQuery.h` (Public)


#### class `UE::FUsdSkelBlendShapeQuery`  
`class FUsdSkelBlendShapeQuery`  
_L34-70_
- desc: Minimal pxr::UsdSkelBlendShapeQuery wrapper for Unreal that can be used from no-rtti modules.
- L37 _public prototype_ `FUsdSkelBlendShapeQuery();`
- L38 _public prototype_ `FUsdSkelBlendShapeQuery(const UE::FUsdPrim& SkelBindingAPIPrim);`
- L39 _public prototype_ `FUsdSkelBlendShapeQuery(const FUsdSkelBlendShapeQuery& Other);`
- L40 _public prototype_ `FUsdSkelBlendShapeQuery(FUsdSkelBlendShapeQuery&& Other);`
- L41 _public prototype_ `~FUsdSkelBlendShapeQuery();`
- L43 _public prototype_ `FUsdSkelBlendShapeQuery& operator=(const FUsdSkelBlendShapeQuery& Other);`
- L44 _public prototype_ `FUsdSkelBlendShapeQuery& operator=(FUsdSkelBlendShapeQuery&& Other);`
- L46 _public prototype_ `explicit operator bool() const;`
- L51 _public prototype_ `explicit FUsdSkelBlendShapeQuery(const pxr::UsdSkelBlendShapeQuery& InUsdSkelBlendShapeQuery);`
- L52 _public prototype_ `explicit FUsdSkelBlendShapeQuery(pxr::UsdSkelBlendShapeQuery&& InUsdSkelBlendShapeQuery);`
- L54 _public prototype_ `operator pxr::UsdSkelBlendShapeQuery&();`
- L55 _public prototype_ `operator const pxr::UsdSkelBlendShapeQuery&() const;`
- L60 _public prototype_ `bool IsValid() const;`
- L62 _public prototype_ `UE::FUsdPrim GetPrim() const;`
- L64 _public prototype_ `size_t GetNumBlendShapes() const;`
- L66 _public prototype_ `UE::FUsdSkelBlendShape GetBlendShape(size_t BlendShapeIndex) const;`
- L69 _private member_ `TUniquePtr<Internal::FUsdSkelBlendShapeQueryImpl> Impl;`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Internal` (scope `UE`)

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UsdWrappers/UsdSkelCache.h` (Public)


#### class `UE::FUsdSkelCache`  
`class FUsdSkelCache`  
_L37-81_
- desc: Minimal pxr::UsdSkelCache wrapper for Unreal that can be used from no-rtti modules.
- L40 _public prototype_ `FUsdSkelCache();`
- L41 _public prototype_ `FUsdSkelCache(const FUsdSkelCache& Other);`
- L42 _public prototype_ `FUsdSkelCache(FUsdSkelCache&& Other);`
- L43 _public prototype_ `~FUsdSkelCache();`
- L45 _public prototype_ `FUsdSkelCache& operator=(const FUsdSkelCache& Other);`
- L46 _public prototype_ `FUsdSkelCache& operator=(FUsdSkelCache&& Other);`
- L51 _public prototype_ `explicit FUsdSkelCache(const pxr::UsdSkelCache& InUsdSkelCache);`
- L52 _public prototype_ `explicit FUsdSkelCache(pxr::UsdSkelCache&& InUsdSkelCache);`
- L54 _public prototype_ `operator pxr::UsdSkelCache&();`
- L55 _public prototype_ `operator const pxr::UsdSkelCache&() const;`
- L60 _public prototype_ `void Clear();`
- L62 _public prototype_ `bool Populate(const UE::FUsdPrim& SkelRootPrim, bool bTraverseInstanceProxies);`
- L64 _public prototype_ `UE::FUsdSkelSkeletonQuery GetSkelQuery(const UE::FUsdPrim& SkeletonPrim) const;`
- L66 _public prototype_ `UE::FUsdSkelAnimQuery GetAnimQuery(const UE::FUsdPrim& SkelAnimationPrim) const;`
- L68 _public prototype_ `UE::FUsdSkelSkinningQuery GetSkinningQuery(const UE::FUsdPrim& SkinnedPrim) const;`
- L70 _public prototype_ `bool ComputeSkelBindings(const UE::FUsdPrim& InSkelRootPrim, TArray<UE::FUsdSkelBinding>& OutBindings, bool bTraverseInstanceProxies) const;`
- L72 _public prototype_ `bool ComputeSkelBinding( const UE::FUsdPrim& InSkelRootPrim, const UE::FUsdPrim& InSkeletonPrim, UE::FUsdSkelBinding& OutBinding, bool bTraverseInstanceProxies ) const;`
- L80 _private member_ `TUniquePtr<Internal::FUsdSkelCacheImpl> Impl;`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L29 _namespace_ `namespace Internal` (scope `UE`)

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UsdWrappers/UsdSkelInbetweenShape.h` (Public)


#### class `UE::FUsdSkelInbetweenShape`  
`class FUsdSkelInbetweenShape`  
_L34-65_
- desc: Minimal pxr::UsdSkelInbetweenShape wrapper for Unreal that can be used from no-rtti modules.
- L37 _public prototype_ `FUsdSkelInbetweenShape();`
- L38 _public prototype_ `FUsdSkelInbetweenShape(const FUsdSkelInbetweenShape& Other);`
- L39 _public prototype_ `FUsdSkelInbetweenShape(FUsdSkelInbetweenShape&& Other);`
- L40 _public prototype_ `~FUsdSkelInbetweenShape();`
- L42 _public prototype_ `FUsdSkelInbetweenShape& operator=(const FUsdSkelInbetweenShape& Other);`
- L43 _public prototype_ `FUsdSkelInbetweenShape& operator=(FUsdSkelInbetweenShape&& Other);`
- L45 _public prototype_ `explicit operator bool() const;`
- L50 _public prototype_ `explicit FUsdSkelInbetweenShape(const pxr::UsdSkelInbetweenShape& InUsdSkelInbetweenShape);`
- L51 _public prototype_ `explicit FUsdSkelInbetweenShape(pxr::UsdSkelInbetweenShape&& InUsdSkelInbetweenShape);`
- L53 _public prototype_ `operator pxr::UsdSkelInbetweenShape&();`
- L54 _public prototype_ `operator const pxr::UsdSkelInbetweenShape&() const;`
- L59 _public prototype_ `bool GetWeight(float* OutWeight) const;`
- L60 _public prototype_ `UE::FUsdAttribute GetAttr() const;`
- L61 _public prototype_ `bool IsDefined() const;`
- L64 _private member_ `TUniquePtr<Internal::FUsdSkelInbetweenShapeImpl> Impl;`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Internal` (scope `UE`)

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UsdWrappers/UsdSkelRoot.h` (Public)


#### class `UE::FUsdSkelRoot`  
`class FUsdSkelRoot : public FUsdTyped`  
_L32-65_
- inherits: `FUsdTyped`
- desc: Minimal pxr::UsdSkelRoot wrapper for Unreal that can be used from no-rtti modules.
- L35 _public prototype_ `FUsdSkelRoot();`
- L36 _public prototype_ `FUsdSkelRoot(const FUsdSkelRoot& Other);`
- L37 _public prototype_ `FUsdSkelRoot(FUsdSkelRoot&& Other);`
- L39 _public prototype_ `explicit FUsdSkelRoot(const FUsdPrim& Prim);`
- L41 _public prototype_ `FUsdSkelRoot& operator=(const FUsdSkelRoot& Other);`
- L42 _public prototype_ `FUsdSkelRoot& operator=(FUsdSkelRoot&& Other);`
- L44 _public prototype_ `~FUsdSkelRoot();`
- L46 _public prototype_ `explicit operator bool() const;`
- L51 _public prototype_ `explicit FUsdSkelRoot(const pxr::UsdSkelRoot& InUsdSkelRoot);`
- L52 _public prototype_ `explicit FUsdSkelRoot(pxr::UsdSkelRoot&& InUsdSkelRoot);`
- L53 _public prototype_ `explicit FUsdSkelRoot(const pxr::UsdPrim& Prim);`
- L55 _public prototype_ `operator pxr::UsdSkelRoot&();`
- L56 _public prototype_ `operator const pxr::UsdSkelRoot&() const;`
- L61 _public prototype_ `static FUsdSkelRoot Find(const UE::FUsdPrim& Prim);`
- L64 _private member_ `TUniquePtr<Internal::FUsdSkelRootImpl> Impl;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L24 _namespace_ `namespace Internal` (scope `UE`)

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UsdWrappers/UsdSkelSkeletonQuery.h` (Public)


#### class `UE::FUsdSkelSkeletonQuery`  
`class FUsdSkelSkeletonQuery`  
_L34-72_
- desc: Minimal pxr::UsdSkelSkeletonQuery wrapper for Unreal that can be used from no-rtti modules.
- L40 _public prototype_ `FUsdSkelSkeletonQuery();` — WARNING: Default-constructed objects are permanently invalid! The default constructor is available for technical reasons, but you should create these objects by calling FUsdSkelCache::GetSkelQuery(SkeletonPrim)
- L41 _public prototype_ `FUsdSkelSkeletonQuery(const FUsdSkelSkeletonQuery& Other);`
- L42 _public prototype_ `FUsdSkelSkeletonQuery(FUsdSkelSkeletonQuery&& Other);`
- L43 _public prototype_ `~FUsdSkelSkeletonQuery();`
- L45 _public prototype_ `FUsdSkelSkeletonQuery& operator=(const FUsdSkelSkeletonQuery& Other);`
- L46 _public prototype_ `FUsdSkelSkeletonQuery& operator=(FUsdSkelSkeletonQuery&& Other);`
- L48 _public prototype_ `explicit operator bool() const;`
- L53 _public prototype_ `explicit FUsdSkelSkeletonQuery(const pxr::UsdSkelSkeletonQuery& InUsdSkelSkeletonQuery);`
- L54 _public prototype_ `explicit FUsdSkelSkeletonQuery(pxr::UsdSkelSkeletonQuery&& InUsdSkelSkeletonQuery);`
- L56 _public prototype_ `operator pxr::UsdSkelSkeletonQuery&();`
- L57 _public prototype_ `operator const pxr::UsdSkelSkeletonQuery&() const;`
- L62 _public prototype_ `bool IsValid() const;`
- L64 _public prototype_ `UE::FUsdPrim GetPrim() const;`
- L65 _public prototype_ `UE::FUsdPrim GetSkeleton() const;`
- L66 _public prototype_ `UE::FUsdSkelAnimQuery GetAnimQuery() const;`
- L68 _public prototype_ `bool ComputeJointLocalTransforms(TArray<FTransform>& UsdSpaceTransforms, double TimeCode, bool bAtRest = false) const;`
- L71 _private member_ `TUniquePtr<Internal::FUsdSkelSkeletonQueryImpl> Impl;`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Internal` (scope `UE`)

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UsdWrappers/UsdSkelSkinningQuery.h` (Public)


#### class `UE::FUsdSkelSkinningQuery`  
`class FUsdSkelSkinningQuery`  
_L34-72_
- desc: Minimal pxr::UsdSkelSkinningQuery wrapper for Unreal that can be used from no-rtti modules.
- L37 _public prototype_ `FUsdSkelSkinningQuery();`
- L38 _public prototype_ `FUsdSkelSkinningQuery(const FUsdSkelSkinningQuery& Other);`
- L39 _public prototype_ `FUsdSkelSkinningQuery(FUsdSkelSkinningQuery&& Other);`
- L40 _public prototype_ `~FUsdSkelSkinningQuery();`
- L42 _public prototype_ `FUsdSkelSkinningQuery& operator=(const FUsdSkelSkinningQuery& Other);`
- L43 _public prototype_ `FUsdSkelSkinningQuery& operator=(FUsdSkelSkinningQuery&& Other);`
- L45 _public prototype_ `explicit operator bool() const;`
- L50 _public prototype_ `explicit FUsdSkelSkinningQuery(const pxr::UsdSkelSkinningQuery& InUsdSkelSkinningQuery);`
- L51 _public prototype_ `explicit FUsdSkelSkinningQuery(pxr::UsdSkelSkinningQuery&& InUsdSkelSkinningQuery);`
- L53 _public prototype_ `operator pxr::UsdSkelSkinningQuery&();`
- L54 _public prototype_ `operator const pxr::UsdSkelSkinningQuery&() const;`
- L59 _public prototype_ `bool IsValid() const;`
- L61 _public prototype_ `UE::FUsdPrim GetPrim() const;`
- L63 _public prototype_ `UE::FUsdRelationship GetBlendShapeTargetsRel() const;`
- L65 _public prototype_ `bool GetBlendShapeOrder(TArray<FString>& BlendShapes) const;`
- L68 _public prototype_ `FMatrix GetGeomBindTransform(double UsdTimeCode) const;` — Note: This matrix is in USD space, retrieved as-is
- L71 _private member_ `TUniquePtr<Internal::FUsdSkelSkinningQueryImpl> Impl;`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Internal` (scope `UE`)

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UsdWrappers/UsdStage.h` (Public)


#### class `UE::FUsdStageBase`  
`template<typename PtrType> class FUsdStageBase`  
_L29-131_
- desc: Minimal pxr::UsdStage pointer wrapper for Unreal that can be used from no-rtti modules. Use the aliases FUsdStage and FUsdStageWeak instead (defined on ForwardDeclarations.h)
- L32 _public prototype_ `FUsdStageBase();`
- L34 _public prototype_ `FUsdStageBase(const FUsdStage& Other);`
- L35 _public prototype_ `FUsdStageBase(FUsdStage&& Other);`
- L36 _public prototype_ `FUsdStageBase(const FUsdStageWeak& Other);`
- L37 _public prototype_ `FUsdStageBase(FUsdStageWeak&& Other);`
- L39 _public prototype_ `FUsdStageBase& operator=(const FUsdStage& Other);`
- L40 _public prototype_ `FUsdStageBase& operator=(FUsdStage&& Other);`
- L41 _public prototype_ `FUsdStageBase& operator=(const FUsdStageWeak& Other);`
- L42 _public prototype_ `FUsdStageBase& operator=(FUsdStageWeak&& Other);`
- L44 _public prototype_ `~FUsdStageBase();`
- L46 _public prototype_ `explicit operator bool() const;`
- L51 _public prototype_ `template<typename OtherPtrType> bool operator==(const FUsdStageBase<OtherPtrType>& Other) const;` — We have to implement a templated comparison operator, or else we get ambigous conversions on the Mac targets when comparing FUsdStage and FUsdStageWeak
- L57 _public prototype_ `explicit FUsdStageBase(const pxr::UsdStageRefPtr& InUsdPtr);`
- L58 _public prototype_ `explicit FUsdStageBase(pxr::UsdStageRefPtr&& InUsdPtr);`
- L59 _public prototype_ `explicit FUsdStageBase(const pxr::UsdStageWeakPtr& InUsdPtr);`
- L60 _public prototype_ `explicit FUsdStageBase(pxr::UsdStageWeakPtr&& InUsdPtr);`
- L62 _public prototype_ `operator PtrType&();`
- L63 _public prototype_ `operator const PtrType&() const;`
- L65 _public prototype_ `operator pxr::UsdStageRefPtr() const;`
- L66 _public prototype_ `operator pxr::UsdStageWeakPtr() const;`
- L71 _public prototype_ `void LoadAndUnload( const TSet<UE::FSdfPath>& LoadSet, const TSet<UE::FSdfPath>& UnloadSet, EUsdLoadPolicy Policy = EUsdLoadPolicy::UsdLoadWithDescendants );`
- L81 _public prototype_ `bool Export(const TCHAR* FileName, bool bAddSourceFileComment = true, const TMap<FString, FString>& FileFormatArguments = {}) const;` — Saves a flattened copy of the stage to the given path (e.g. "C:/Folder/FlattenedStage.usda"). Will use the corresponding file writer depending on FilePath extension. Will not alter the current stage.
- L83 _public prototype_ `FSdfLayer GetRootLayer() const;`
- L84 _public prototype_ `FSdfLayer GetSessionLayer() const;`
- L85 _public prototype_ `bool HasLocalLayer(const FSdfLayer& Layer) const;`
- L87 _public prototype_ `FUsdPrim GetPseudoRoot() const;`
- L88 _public prototype_ `FUsdPrim GetDefaultPrim() const;`
- L89 _public prototype_ `FUsdPrim GetPrimAtPath(const FSdfPath& Path) const;`
- L91 _public prototype_ `TArray<FSdfLayer> GetLayerStack(bool bIncludeSessionLayers = true) const;`
- L92 _public prototype_ `TArray<FSdfLayer> GetUsedLayers(bool bIncludeClipLayers = true) const;`
- L94 _public prototype_ `void MuteAndUnmuteLayers(const TArray<FString>& MuteLayers, const TArray<FString>& UnmuteLayers);`
- L95 _public prototype_ `bool IsLayerMuted(const FString& LayerIdentifier) const;`
- L97 _public prototype_ `bool IsEditTargetValid() const;`
- L98 _public prototype_ `void SetEditTarget(const FSdfLayer& Layer);`
- L99 _public prototype_ `FSdfLayer GetEditTarget() const;`
- L101 _public prototype_ `bool GetMetadata(const TCHAR* Key, UE::FVtValue& Value) const;`
- L102 _public prototype_ `bool HasMetadata(const TCHAR* Key) const;`
- L103 _public prototype_ `bool SetMetadata(const TCHAR* Key, const UE::FVtValue& Value) const;`
- L104 _public prototype_ `bool ClearMetadata(const TCHAR* Key) const;`
- L106 _public prototype_ `double GetStartTimeCode() const;`
- L107 _public prototype_ `double GetEndTimeCode() const;`
- L108 _public prototype_ `void SetStartTimeCode(double TimeCode);`
- L109 _public prototype_ `void SetEndTimeCode(double TimeCode);`
- L110 _public prototype_ `double GetTimeCodesPerSecond() const;`
- L111 _public prototype_ `void SetTimeCodesPerSecond(double TimeCodesPerSecond);`
- L112 _public prototype_ `double GetFramesPerSecond() const;`
- L113 _public prototype_ `void SetFramesPerSecond(double FramesPerSecond);`
- L115 _public prototype_ `void SetInterpolationType(EUsdInterpolationType InterpolationType);`
- L116 _public prototype_ `EUsdInterpolationType GetInterpolationType() const;`
- L118 _public prototype_ `void SetDefaultPrim(const FUsdPrim& Prim);`
- L120 _public prototype_ `FUsdPrim OverridePrim(const FSdfPath& Path);`
- L121 _public prototype_ `FUsdPrim DefinePrim(const FSdfPath& Path, const TCHAR* TypeName = TEXT(""));`
- L122 _public prototype_ `FUsdPrim CreateClassPrim(const FSdfPath& RootPrimPath);`
- L123 _public prototype_ `bool RemovePrim(const FSdfPath& Path);`
- L130 _private member_ `TUniquePtr<Internal::FUsdStageImpl<PtrType>> Impl;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UNREALUSDWRAPPER_API`
- L12 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Internal` (scope `UE`)

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UsdWrappers/UsdTyped.h` (Public)


#### class `UE::FUsdTyped`  
`class FUsdTyped`  
_L32-66_
- desc: Minimal pxr::UsdTyped wrapper for Unreal that can be used from no-rtti modules.
- L35 _public prototype_ `FUsdTyped();`
- L36 _public prototype_ `FUsdTyped(const FUsdTyped& Other);`
- L37 _public prototype_ `FUsdTyped(FUsdTyped&& Other);`
- L39 _public prototype_ `explicit FUsdTyped(const FUsdPrim& Prim);`
- L41 _public prototype_ `FUsdTyped& operator=(const FUsdTyped& Other);`
- L42 _public prototype_ `FUsdTyped& operator=(FUsdTyped&& Other);`
- L44 _public prototype_ `~FUsdTyped();`
- L46 _public prototype_ `explicit operator bool() const;`
- L51 _public prototype_ `explicit FUsdTyped(const pxr::UsdTyped& InUsdTyped);`
- L52 _public prototype_ `explicit FUsdTyped(pxr::UsdTyped&& InUsdTyped);`
- L53 _public prototype_ `explicit FUsdTyped(const pxr::UsdPrim& Prim);`
- L55 _public prototype_ `operator pxr::UsdTyped&();`
- L56 _public prototype_ `operator const pxr::UsdTyped&() const;`
- L61 _public prototype_ `FSdfPath GetPath() const;`
- L62 _public prototype_ `FUsdPrim GetPrim() const;`
- L65 _private member_ `TUniquePtr<Internal::FUsdTypedImpl> Impl;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L24 _namespace_ `namespace Internal` (scope `UE`)

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UsdWrappers/UsdVariantSets.h` (Public)


#### class `UE::FUsdVariantSet`  
`class FUsdVariantSet`  
_L39-103_
- desc: Minimal pxr::UsdVariantSet wrapper for Unreal that can be used from no-rtti modules.
- L42 _public prototype_ `FUsdVariantSet();`
- L43 _public prototype_ `FUsdVariantSet(const FUsdVariantSet& Other);`
- L44 _public prototype_ `FUsdVariantSet(FUsdVariantSet&& Other);`
- L46 _public prototype_ `FUsdVariantSet& operator=(const FUsdVariantSet& Other);`
- L47 _public prototype_ `FUsdVariantSet& operator=(FUsdVariantSet&& Other);`
- L49 _public prototype_ `~FUsdVariantSet();`
- L51 _public prototype_ `explicit operator bool() const;`
- L55 _public prototype_ `explicit FUsdVariantSet(const pxr::UsdVariantSet& InUsdVariantSet);` — Auto conversion from/to pxr::UsdVariantSet
- L56 _public prototype_ `explicit FUsdVariantSet(pxr::UsdVariantSet&& InUsdVariantSet);`
- L57 _public prototype_ `FUsdVariantSet& operator=(const pxr::UsdVariantSet& InUsdVariantSet);`
- L58 _public prototype_ `FUsdVariantSet& operator=(pxr::UsdVariantSet&& InUsdVariantSet);`
- L60 _public prototype_ `operator pxr::UsdVariantSet();`
- L61 _public prototype_ `operator const pxr::UsdVariantSet() const;`
- L68 _private prototype_ `explicit FUsdVariantSet(const pxr::UsdPrim& InPrim, const std::string& InVariantSetName);` — FUsdVariantSet instances are only constructable by instances of FUsdPrim or FUsdVariantSets. Use FUsdPrim::GetVariantSet() or FUsdVariantSets::GetVariantSet() to construct an instance.
- L73 _public prototype_ `bool AddVariant(const FString& VariantName, EUsdListPosition Position = EUsdListPosition::BackOfPrependList);`
- L75 _public prototype_ `TArray<FString> GetVariantNames() const;`
- L77 _public prototype_ `bool HasAuthoredVariant(const FString& VariantName) const;`
- L79 _public prototype_ `FString GetVariantSelection() const;`
- L81 _public prototype_ `bool HasAuthoredVariantSelection(FString* Value = nullptr) const;`
- L83 _public prototype_ `bool SetVariantSelection(const FString& VariantName);`
- L85 _public prototype_ `bool ClearVariantSelection();`
- L87 _public prototype_ `bool BlockVariantSelection();`
- L92 _public prototype_ `FUsdPrim GetPrim() const;`
- L94 _public prototype_ `FString GetName() const;`
- L96 _public prototype_ `bool IsValid() const;`
- L99 _private member_ `TUniquePtr<Internal::FUsdVariantSetImpl> Impl;`

#### class `UE::FUsdVariantSets`  
`class FUsdVariantSets`  
_L108-164_
- desc: Minimal pxr::UsdVariantSets wrapper for Unreal that can be used from no-rtti modules.
- L111 _public prototype_ `FUsdVariantSets();`
- L112 _public prototype_ `FUsdVariantSets(const FUsdVariantSets& Other);`
- L113 _public prototype_ `FUsdVariantSets(FUsdVariantSets&& Other);`
- L115 _public prototype_ `FUsdVariantSets& operator=(const FUsdVariantSets& Other);`
- L116 _public prototype_ `FUsdVariantSets& operator=(FUsdVariantSets&& Other);`
- L118 _public prototype_ `~FUsdVariantSets();`
- L120 _public prototype_ `explicit operator bool() const;`
- L129 _public prototype_ `operator pxr::UsdVariantSets();` — Auto conversion to pxr::UsdVariantSets
- L130 _public prototype_ `operator const pxr::UsdVariantSets() const;`
- L136 _private prototype_ `explicit FUsdVariantSets(const pxr::UsdPrim& InPrim);` — FUsdVariantSets instances are only constructable by instances of FUsdPrim. Use FUsdPrim::GetVariantSets() to construct an instance.
- L141 _public prototype_ `FUsdVariantSet AddVariantSet(const FString& VariantSetName, EUsdListPosition Position = EUsdListPosition::BackOfPrependList);`
- L143 _public prototype_ `TArray<FString> GetNames() const;`
- L145 _public function_ `FUsdVariantSet operator[](const FString& VariantSetName) const`
- L150 _public prototype_ `FUsdVariantSet GetVariantSet(const FString& VariantSetName) const;`
- L152 _public prototype_ `bool HasVariantSet(const FString& VariantSetName) const;`
- L154 _public prototype_ `FString GetVariantSelection(const FString& VariantSetName) const;`
- L156 _public prototype_ `bool SetSelection(const FString& VariantSetName, const FString& VariantName);`
- L158 _public prototype_ `TMap<FString, FString> GetAllVariantSelections() const;`
- L161 _private member_ `TUniquePtr<Internal::FUsdVariantSetsImpl> Impl;`

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace UE`
- L30 _namespace_ `namespace Internal` (scope `UE`)

### `Plugins/Runtime/USDCore/Source/UnrealUSDWrapper/Public/UsdWrappers/VtValue.h` (Public)


#### class `UE::FVtValue`  
`class FVtValue`  
_L27-81_
- desc: Minimal pxr::VtValue wrapper for Unreal that can be used from no-rtti modules.
- L30 _public prototype_ `FVtValue();`
- L32 _public prototype_ `FVtValue(const FVtValue& Other);`
- L33 _public prototype_ `FVtValue(FVtValue&& Other);`
- L35 _public prototype_ `FVtValue& operator=(const FVtValue& Other);`
- L36 _public prototype_ `FVtValue& operator=(FVtValue&& Other);`
- L38 _public prototype_ `~FVtValue();`
- L40 _public prototype_ `bool operator==(const FVtValue& Other) const;`
- L41 _public prototype_ `bool operator!=(const FVtValue& Other) const;`
- L49 _public prototype_ `explicit FVtValue(const pxr::VtValue& InVtValue);`
- L50 _public prototype_ `explicit FVtValue(pxr::VtValue&& InVtValue);`
- L51 _public prototype_ `FVtValue& operator=(const pxr::VtValue& InVtValue);`
- L52 _public prototype_ `FVtValue& operator=(pxr::VtValue&& InVtValue);`
- L54 _public prototype_ `pxr::VtValue& GetUsdValue();`
- L55 _public prototype_ `const pxr::VtValue& GetUsdValue() const;`
- L60 _public prototype_ `FString GetTypeName() const;`
- L61 _public prototype_ `bool IsArrayValued() const;`
- L65 _public prototype_ `template <typename T> T Get() const;` — Returns UE types (FQuat, TArray<FFloat16>, etc.), performing USD to Unreal conversions when needed
- L75 _public prototype_ `template <typename T> void Set(const T& Value);` — Receives UE types (FQuat, TArray<FFloat16>, etc.), performing Unreal to USD conversions when needed. pxr::VtValue provides assignment operators/constructors as the main "setters", but we provide this explicit setter instead, given that an assignment operator for the UE::FVtValue wrapper class may provide ambiguous/unclear behavior in edge cases (e.g. assigning another pxr::VtValue or assigning an UE::FVtValue)
- L77 _public prototype_ `bool IsEmpty() const;`
- L80 _private member_ `TUniquePtr<Internal::FVtValueImpl> Impl;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Internal` (scope `UE`)
