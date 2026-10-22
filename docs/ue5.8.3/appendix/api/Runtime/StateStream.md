# Runtime / StateStream

- module root: `Source/Runtime/StateStream`
- headers: 14; symbols: 345
- symbol kinds: class=13, delegate=1, enum=4, enumerator=4, function=81, macro=12, member=74, prototype=127, struct=15, typedef=12, variable=2
- PublicDependencyModuleNames: Core, CoreUObject

### `Source/Runtime/StateStream/Public/GenericStateStream.h` (Public)


#### struct `TStateStreamSettings`  
`template<typename TInterfaceType, typename TInstanceUserDataType = void, typename TLaneUserDataType = void> struct TStateStreamSettings`  
_L32-40_
- L34 _public typedef_ `using InterfaceType = TInterfaceType;`
- L35 _public typedef_ `using InstanceUserDataType = TInstanceUserDataType;`
- L36 _public typedef_ `using LaneUserDataType = TLaneUserDataType;`
- L38 _public member_ `static inline constexpr const TCHAR* DebugName = InterfaceType::Handle::DebugName;`
- L39 _public member_ `static inline constexpr bool SkipCreatingDeletes = false;`

#### enum `TStateStreamSettings::(anonymous)`  
`enum`  
_L37-37_

#### class `TStateStream`  
`template<typename Settings> class TStateStream : public IStateStream, public Settings::InterfaceType, public IStateStreamHandleOwner`  
_L49-198_
- inherits: `IStateStream,Settings::InterfaceType,IStateStreamHandleOwner`
- L52 _public typedef_ `using InterfaceType = typename Settings::InterfaceType;`
- L53 _public typedef_ `using FHandle = typename InterfaceType::Handle;`
- L54 _public typedef_ `using FStaticState = typename InterfaceType::StaticState;`
- L55 _public typedef_ `using FDynamicState = typename InterfaceType::DynamicState;`
- L56 _public typedef_ `using FInstanceUserDataType = typename Settings::InstanceUserDataType;`
- L57 _public typedef_ `using FLaneUserDataType = typename Settings::LaneUserDataType;`
- L61 _public prototype_ `virtual FHandle Game_CreateInstance(const FStaticState& Ss, const FDynamicState& Ds, uint32 LaneId = DefaultLaneId) override final;`
- L65 _public prototype_ `virtual void Game_AddRef(uint32 HandleId) override final;`
- L66 _public prototype_ `virtual void Game_Release(uint32 HandleId) override final;`
- L67 _public prototype_ `virtual void Game_Update(uint32 HandleId, const void* Ds, double TimeFactor, uint64 UserData) override;`
- L68 _public prototype_ `virtual void* Game_Edit(uint32 HandleId, double TimeFactor, uint64 UserData) override;`
- L69 _public prototype_ `virtual void* Render_GetUserData(uint32 HandleId) override final;`
- L73 _public function_ `virtual void Game_CreateLane() override`
- L74 _public function_ `virtual void Game_SetLaneUserData(uint32 LaneId, void* UserData) override`
- L75 _public function_ `virtual void Game_DestroyLane(uint32 LaneId) override`
- L76 _public prototype_ `virtual void Game_BeginTick(uint32 LaneId) override;`
- L77 _public prototype_ `virtual void Game_EndTick(StateStreamTime AbsoluteTime, uint32 LaneId) override;`
- L78 _public prototype_ `virtual void Game_SetDefaultLane(uint32 LaneId) override;`
- L79 _public prototype_ `virtual void Game_Exit() override;`
- L80 _public prototype_ `virtual void* Game_GetVoidPointer() override;`
- L81 _public prototype_ `virtual void Game_DebugRender(IStateStreamDebugRenderer& Renderer) override;`
- L82 _public prototype_ `virtual void Render_Update(StateStreamTime AbsoluteTime) override;`
- L83 _public prototype_ `virtual void Render_PostUpdate() override;`
- L84 _public prototype_ `virtual void Render_Exit() override;`
- L85 _public prototype_ `virtual void Render_GarbageCollect() override;`
- L86 _public prototype_ `virtual void Render_Enable(bool Enable) override;`
- L87 _public prototype_ `virtual const TCHAR* GetDebugName() override;`
- L88 _public prototype_ `virtual uint32 GetId() override;`
- L92 _public prototype_ `FInstanceUserDataType*& Render_GetUserData(const FHandle& Handle);` — Get the instance user data on the render side
- L95 _public prototype_ `const FDynamicState& Render_GetDynamicState(const FHandle& Handle);` — Get the instance interpolated dynamic state on the render side
- L98 _public function_ `virtual void Render_OnCreate(const FStaticState& Ss, const FDynamicState& Ds, FInstanceUserDataType*& UserData, bool IsDestroyedInSameFrame)` — Specialize to do custom things when state has been created / updated or destroyed
- L99 _public function_ `virtual void Render_OnUpdate(const FStaticState& Ss, const FDynamicState& Ds, FInstanceUserDataType*& UserData)`
- L100 _public function_ `virtual void Render_OnDestroy(const FStaticState& Ss, const FDynamicState& Ds, FInstanceUserDataType*& UserData)`
- L103 _public function_ `void Render_OnCreateInline(const FStaticState& Ss, const FDynamicState& Ds, FInstanceUserDataType*& UserData, bool IsDestroyedInSameFrame)` — ... or use template specialization to avoid virtual calls
- L104 _public function_ `void Render_OnUpdateInline(const FStaticState& Ss, const FDynamicState& Ds, FInstanceUserDataType*& UserData)`
- L105 _public function_ `void Render_OnDestroyInline(const FStaticState& Ss, const FDynamicState& Ds, FInstanceUserDataType*& UserData)`
- L108 _public function_ `uint32 GetUsedInstancesCount() const` — Get the used instance counts within the streams
- L111 _public function_ `uint32 GetUsedDynamicStatesCount() const` — Get the used dynamic states within the streams
- L113 _public prototype_ `TStateStream() = default;`
- L114 _public prototype_ `~TStateStream() = default;`
- L143 _protected prototype_ `FDynamicState& Edit(uint32 HandleId, double TimeFactor);` — Get the dynamic state to be edited on GT in between begin/end tick
- L147 _protected prototype_ `template<typename InDynamicState> void Update(uint32 HandleId, const InDynamicState& Ds, double TimeFactor);` — Update the editable dynamic state
- L150 _protected prototype_ `void ApplyChanges(const FTick& Tick, StateStreamTime Time, uint32 PrevTickIndex, StateStreamTime PrevTime, const TBitArray<>& ModifiedInstances);` — Interpolate and set the render dynamic states + call create / update / destroy callbacks. Called from the Render_Update
- L154 _protected prototype_ `template<typename T> void MakeInternal(T& State);` — Make the state internal in case it has been released by its owner
- L156 _protected member_ `uint32 ActiveDefaultLaneId = DefaultLaneId;`
- L158 _protected member_ `FLaneUserDataType* LaneUserData = nullptr;`
- L161 _protected member_ `FRWLock CurrentTickLock;` — Lock in order to write into the current tick
- L164 _protected member_ `FTick* CurrentTick = nullptr;` — Tick being worked on in game
- L167 _protected member_ `FTick* OldestAvailableTick = nullptr;` — Oldest finished tick available to rendering
- L170 _protected member_ `FTick* NewestAvailableTick = nullptr;` — Newest finished tick available to rendering
- L173 _protected member_ `TStateStreamStore<FInstance> Instances;` — Instances registered in the state stream
- L176 _protected member_ `TStateStreamStore<FDynamicState> DynamicStates;` — Dynamic states that will be referenced in the different ticks
- L179 _protected member_ `uint32 TickCounter = 1;` — Tick counter used to increment tick indices
- L182 _protected member_ `FTick* RendTick = nullptr;` — Last used tick for rendering.
- L185 _protected member_ `StateStreamTime RendTime = 0;` — Last used time for rendering
- L188 _protected member_ `bool RendEnabledRequested = true;` — Boolean to trigger the render update
- L191 _protected member_ `bool RendEnabled = true;` — Check if the render update has been enabled or not
- L194 _protected member_ `TArray<FInstance*> DeferredDestroys;` — List of instances to be destroyed
- L196 _protected prototype_ `TStateStream(const TStateStream&) = delete;`
- L197 _protected prototype_ `TStateStream& operator=(const TStateStream&) = delete;`
- L203 _function_ `template<typename Settings> typename TStateStream<Settings>::FHandle TStateStream<Settings>::Game_CreateInstance(const FStaticState& Ss, const FDynamicState& Ds, uint32 LaneId)`
- L235 _function_ `template<typename Settings> void TStateStream<Settings>::Game_AddRef(uint32 HandleId)`
- L246 _function_ `template<typename Settings> void TStateStream<Settings>::Game_Release(uint32 HandleId)`
- L274 _function_ `template<typename Settings> void TStateStream<Settings>::Game_Update(uint32 HandleId, const void* Ds, double TimeFactor, uint64 UserData)`
- L283 _function_ `template<typename Settings> void* TStateStream<Settings>::Game_Edit(uint32 HandleId, double TimeFactor, uint64 UserData)`
- L289 _function_ `template<typename Settings> typename TStateStream<Settings>::FDynamicState& TStateStream<Settings>::Edit(uint32 HandleId, double TimeFactor)`
- L333 _function_ `template<typename Settings> template<typename InDynamicState> void TStateStream<Settings>::Update(uint32 HandleId, const InDynamicState& Ds, double TimeFactor)`
- L359 _function_ `template<typename Settings> void* TStateStream<Settings>::Render_GetUserData(uint32 HandleId)`
- L367 _function_ `template<typename Settings> void TStateStream<Settings>::Game_BeginTick(uint32 LaneId)`
- L384 _function_ `template<typename Settings> void TStateStream<Settings>::Game_EndTick(StateStreamTime AbsoluteTime, uint32 LaneId)`
- L407 _function_ `template<typename Settings> void TStateStream<Settings>::Game_SetDefaultLane(uint32 LaneId)`
- L413 _function_ `template<typename Settings> void TStateStream<Settings>::Game_Exit()`
- L425 _function_ `template<typename Settings> void* TStateStream<Settings>::Game_GetVoidPointer()`
- L431 _function_ `template<typename Settings> uint32 TStateStream<Settings>::GetId()`
- L437 _function_ `template<typename Settings> void TStateStream<Settings>::Render_Update(StateStreamTime AbsoluteTime)`
- L575 _function_ `template<typename Settings> void TStateStream<Settings>::Render_PostUpdate()`
- L587 _function_ `template<typename Settings> void TStateStream<Settings>::Render_Exit()`
- L598 _function_ `template<typename Settings> void TStateStream<Settings>::Render_GarbageCollect()`
- L673 _function_ `template<typename Settings> void TStateStream<Settings>::Render_Enable(bool Enable)`
- L679 _function_ `template<typename Settings> const TCHAR* TStateStream<Settings>::GetDebugName()`
- L685 _function_ `template<typename Settings> void TStateStream<Settings>::Game_DebugRender(IStateStreamDebugRenderer& Renderer)`
- L698 _function_ `template<typename Settings> typename TStateStream<Settings>::FInstanceUserDataType*& TStateStream<Settings>::Render_GetUserData(const FHandle& Handle)`
- L707 _function_ `template<typename Settings> const typename TStateStream<Settings>::FDynamicState& TStateStream<Settings>::Render_GetDynamicState(const FHandle& Handle)`
- L716 _function_ `template<typename Settings> void TStateStream<Settings>::ApplyChanges(const FTick& Tick, StateStreamTime Time, uint32 PrevTickIndex, StateStreamTime PrevTime, const TBitArray<>& ModifiedInstances)`
- L829 _function_ `template<typename Settings> template<typename T> void TStateStream<Settings>::MakeInternal(T& State)`

#### enum `TStateStream::(anonymous)`  
`enum`  
_L58-58_

#### struct `TStateStream::FInstance`  
`struct FInstance`  
_L119-129_
- desc: Information about instance.
- L121 _public prototype_ `FInstance() = default;`
- L122 _public function_ `FInstance(const FStaticState& Ss, uint32 Rc, uint32 Ct) : StaticState(Ss), RefCount(Rc), CreateTick(Ct)`
- L123 _public member_ `FStaticState StaticState;`
- L124 _public member_ `uint32 RefCount = 0;`
- L125 _public member_ `uint32 CreateTick = 0;`
- L126 _public member_ `uint32 DeleteTick = ~0u;`
- L127 _public member_ `TOptional<FDynamicState> RendDynamicState;`
- L128 _public member_ `FInstanceUserDataType* UserData = nullptr;`

#### struct `TStateStream::FTick`  
`struct FTick`  
_L132-140_
- desc: Tick produced by game side.
- L134 _public member_ `TArray<uint32> DynamicStates;` — Contains for each instance the index of the dynamic states used by this tick (some might have been destroyed but index not reused)
- L135 _public member_ `TBitArray<> ModifiedInstances;` — Contains bits saying which of the instances that have been modified in this tick.
- L136 _public member_ `FTick* PrevTick = nullptr;` — Tick with earlier time
- L137 _public member_ `FTick* NextTick = nullptr;` — Tick with newer time
- L138 _public member_ `StateStreamTime Time = 0;` — Time Tick finished
- L139 _public member_ `uint32 Index = 0;` — Index of tick (created by TickCounter)

#### struct `TStateStream::ApplyChanges::FCreateInfo`  
`struct FCreateInfo`  
_L719-719_
- desc: TODO: This will do lots of allocations
- L719 _public member_ `struct FCreateInfo { FInstance* Instance; bool IsDestroyInSameFrame; };` — TODO: This will do lots of allocations
- L719 _public member_ `struct FCreateInfo { FInstance* Instance; bool IsDestroyInSameFrame; };` — TODO: This will do lots of allocations

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_STATS_GROUP(TEXT("StateStream"), STATGROUP_StateStream, STATCAT` — State stream stat group
- L18 _macro_ `#define DECLARE_STATESTREAM_COUNTER_STATS(Name, Group) \` — Declare state stream counter to the stat system and to unreal insights
- L23 _macro_ `#define DEFINE_STATESTREAM_COUNTER_STATS(Name, Group, Value) \` — Define state stream counter to the stat system and to unreal insights
- L37 _enumerator_ `enum { Id = InterfaceType::Id }; static inline constexpr const TCHAR* DebugName = InterfaceType::Handle::DebugName; static inline constexpr bool SkipCreatingDeletes = false;` (scope `TStateStreamSettings::__anonc41a41930103`)
- L58 _enumerator_ `enum { Id = Settings::Id }; virtual FHandle Game_CreateInstance(const FStaticState& Ss, const FDynamicState& Ds, uint32 LaneId = DefaultLaneId) override final; virtual void Game_AddRef(uint32 HandleId) override final;` (scope `TStateStream::__anonc41a41930203`)

### `Source/Runtime/StateStream/Public/Pow2ChunkedArray.h` (Public)


#### class `FPow2ChunkedArray`  
`template<typename T, uint32 MinSize = 16, uint32 MaxSize = 16777216> class FPow2ChunkedArray`  
_L17-46_
- L23 _public prototype_ `inline FPow2ChunkedArray();`
- L24 _public prototype_ `inline ~FPow2ChunkedArray();`
- L26 _public prototype_ `inline T& Add(const T& Value, uint32& OutIndex);`
- L27 _public prototype_ `inline T& Add(const T& Value);`
- L28 _public prototype_ `inline T& Add(T&& Value);`
- L30 _public prototype_ `inline const T& operator[](uint32 Index) const;`
- L31 _public prototype_ `inline T& operator[](uint32 Index);`
- L33 _public prototype_ `inline uint32 Num() const;`
- L35 _public prototype_ `inline const T& GetElementAt(uint32 Index) const;`
- L37 _public prototype_ `inline void* AddUninitialized(uint32& OutIndex);`
- L39 _public prototype_ `inline uint32 GetBucketIndex(uint32 Index) const;`
- L40 _public prototype_ `inline uint32 GetBucketStart(uint32 BucketIndex) const;`
- L41 _public prototype_ `inline uint32 GetBucketSize(uint32 BucketIndex) const;`
- L44 _private member_ `std::atomic<uint32> Size;`
- L45 _private member_ `volatile int64 Buckets[BucketCount];`
- L53 _function_ `template<typename T, uint32 MinSize, uint32 MaxSize> FPow2ChunkedArray<T, MinSize, MaxSize>::FPow2ChunkedArray()`
- L59 _function_ `template<typename T, uint32 MinSize, uint32 MaxSize> FPow2ChunkedArray<T, MinSize, MaxSize>::~FPow2ChunkedArray()`
- L79 _function_ `template<typename T, uint32 MinSize, uint32 MaxSize> T& FPow2ChunkedArray<T, MinSize, MaxSize>::Add(const T& Value, uint32& OutIndex)`
- L85 _function_ `template<typename T, uint32 MinSize, uint32 MaxSize> T& FPow2ChunkedArray<T, MinSize, MaxSize>::Add(const T& Value)`
- L92 _function_ `template<typename T, uint32 MinSize, uint32 MaxSize> T& FPow2ChunkedArray<T, MinSize, MaxSize>::Add(T&& Value)`
- L99 _function_ `template<typename T, uint32 MinSize, uint32 MaxSize> const T& FPow2ChunkedArray<T, MinSize, MaxSize>::operator[](uint32 Index) const`
- L105 _function_ `template<typename T, uint32 MinSize, uint32 MaxSize> T& FPow2ChunkedArray<T, MinSize, MaxSize>::operator[](uint32 Index)`
- L111 _function_ `template<typename T, uint32 MinSize, uint32 MaxSize> uint32 FPow2ChunkedArray<T, MinSize, MaxSize>::Num() const`
- L117 _function_ `template<typename T, uint32 MinSize, uint32 MaxSize> const T& FPow2ChunkedArray<T, MinSize, MaxSize>::GetElementAt(uint32 Index) const`
- L127 _function_ `template<typename T, uint32 MinSize, uint32 MaxSize> void* FPow2ChunkedArray<T, MinSize, MaxSize>::AddUninitialized(uint32& OutIndex)`
- L158 _function_ `template<typename T, uint32 MinSize, uint32 MaxSize> uint32 FPow2ChunkedArray<T, MinSize, MaxSize>::GetBucketIndex(uint32 Index) const`
- L164 _function_ `template<typename T, uint32 MinSize, uint32 MaxSize> uint32 FPow2ChunkedArray<T, MinSize, MaxSize>::GetBucketStart(uint32 BucketIndex) const`
- L170 _function_ `template<typename T, uint32 MinSize, uint32 MaxSize> uint32 FPow2ChunkedArray<T, MinSize, MaxSize>::GetBucketSize(uint32 BucketIndex) const`

#### enum `FPow2ChunkedArray::(anonymous)`  
`enum : uint32`  
_L20-20_

#### enum `FPow2ChunkedArray::(anonymous)`  
`enum : uint32`  
_L21-21_

#### Free symbols / members of external scopes

- L20 _enumerator_ `enum : uint32 { SkipCount = FGenericPlatformMath::CeilLogTwo(MinSize) }; enum : uint32 { BucketCount = FGenericPlatformMath::CeilLogTwo(MaxSize) - SkipCount + 1 }; inline FPow2ChunkedArray(); inline ~FPow2ChunkedArray(); inline T& Add(const T& Value, uint32& OutIndex); inline T& Add(const T& Value);` (scope `FPow2ChunkedArray::__anon9af75e720103`)
- L21 _enumerator_ `enum : uint32 { BucketCount = FGenericPlatformMath::CeilLogTwo(MaxSize) - SkipCount + 1 }; inline FPow2ChunkedArray(); inline ~FPow2ChunkedArray(); inline T& Add(const T& Value, uint32& OutIndex); inline T& Add(const T& Value); inline T& Add(T&& Value);` (scope `FPow2ChunkedArray::__anon9af75e720203`)

### `Source/Runtime/StateStream/Public/StateStream.h` (Public)


#### class `IStateStream`  
`class IStateStream`  
_L13-60_
- L16 _public function_ `virtual void Game_CreateLane()`
- L17 _public function_ `virtual void Game_SetLaneUserData(uint32 LaneId, void* UserData)`
- L18 _public function_ `virtual void Game_DestroyLane(uint32 LaneId)`
- L21 _public prototype_ `virtual void Game_BeginTick(uint32 LaneId) = 0;` — Create current tick data that will be update later on
- L24 _public prototype_ `virtual void Game_EndTick(StateStreamTime AbsoluteTime, uint32 LaneId) = 0;` — Make the current tick available to the renderer (update oldest/newest ticks) and then reset it
- L27 _public prototype_ `virtual void Game_SetDefaultLane(uint32 LaneId) = 0;` — Set the lane that will be used if provided lane is DefaultLaneId
- L30 _public prototype_ `virtual void Game_Exit() = 0;` — Release all the instance/ticks/dynamic states stored within that stream
- L33 _public prototype_ `virtual void* Game_GetVoidPointer() = 0;` — Get the state stream interface pointer
- L36 _public function_ `virtual void Game_DebugRender(IStateStreamDebugRenderer& Renderer)` — Debug render streams data on GT
- L39 _public prototype_ `virtual void Render_Update(StateStreamTime AbsoluteTime) = 0;` — Interpolate the instance render dynamic state from the available ticks [oldest-newest] given a time
- L42 _public prototype_ `virtual void Render_PostUpdate() = 0;` — Destroy the updated render state
- L45 _public prototype_ `virtual void Render_Exit() = 0;` — Last update of the render dynamic state
- L48 _public prototype_ `virtual void Render_GarbageCollect() = 0;` — Release all the ticks/data stored before the updated render tick
- L51 _public prototype_ `virtual void Render_Enable(bool Enable) = 0;` — Enable the state stream render interpolation
- L54 _public prototype_ `virtual uint32 GetId() = 0;` — Get the state stream id
- L57 _public function_ `virtual const TCHAR* GetDebugName()` — Get the state stream debug name
- L59 _public prototype_ `virtual ~IStateStream() = default;`

### `Source/Runtime/StateStream/Public/StateStreamCreator.h` (Public)


#### struct `FStateStreamRegisterContext`  
`struct FStateStreamRegisterContext`  
_L14-20_
- L16 _public member_ `FStateStreamManagerImpl& Manager;`
- L18 _public prototype_ `void Register(IStateStream& StateStream, bool TakeOwnership) const;`
- L19 _public prototype_ `void RegisterDependency(uint32 FromId, uint32 ToId) const;`

#### struct `FStateStreamUnregisterContext`  
`struct FStateStreamUnregisterContext`  
_L24-27_
- L26 _public member_ `FStateStreamManagerImpl& Manager;`

#### class `FStateStreamCreator`  
`class FStateStreamCreator`  
_L31-55_
- L34 _public typedef_ `using FRegisterFunction = TFunction<void(const FStateStreamRegisterContext&)>;`
- L35 _public typedef_ `using FUnregisterFunction = TFunction<void(const FStateStreamUnregisterContext&)>;`
- L37 _public prototype_ `FStateStreamCreator(uint32 Id, FRegisterFunction&& InRegisterFunction, FUnregisterFunction&& InUnregisterFunction);`
- L38 _public prototype_ `~FStateStreamCreator();`
- L41 _public prototype_ `static void RegisterStateStreams(const FStateStreamRegisterContext&);` — Called by system owning StateStreamManager
- L42 _public prototype_ `static void UnregisterStateStreams(const FStateStreamUnregisterContext&);`
- L45 _private prototype_ `FStateStreamCreator(const FStateStreamCreator&) = delete;`
- L46 _private prototype_ `FStateStreamCreator& operator=(const FStateStreamCreator&) = delete;`
- L48 _private member_ `FRegisterFunction RegisterFunction;`
- L49 _private member_ `FUnregisterFunction UnregisterFunction;`
- L51 _private member_ `static FStateStreamCreator* First;`
- L52 _private member_ `FStateStreamCreator* Next;`
- L53 _private member_ `FStateStreamCreator* Prev;`
- L54 _private member_ `uint32 Id;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API STATESTREAM_API`
- L59 _macro_ `#define STATESTREAM_CREATOR_INSTANCE(ImplName) \`
- L65 _macro_ `#define STATESTREAM_CREATOR_INSTANCE_WITH_DEPENDENCY(ImplName, ToId) \`
- L71 _macro_ `#define STATESTREAM_CREATOR_INSTANCE_WITH_FUNC(ImplName, ...) \`

### `Source/Runtime/StateStream/Public/StateStreamDebugRenderer.h` (Public)


#### class `IStateStreamDebugRenderer`  
`class IStateStreamDebugRenderer`  
_L11-18_
- L15 _public prototype_ `virtual void DrawText(const FStringView& Text, const FColor& Color) = 0;` — Interface to draw text with a given color for debug purposes
- L16 _public prototype_ `virtual void DrawText(uint32 X, uint32 Y, const FStringView& Text, const FColor& Color) = 0;`
- L17 _public function_ `virtual ~IStateStreamDebugRenderer()`

### `Source/Runtime/StateStream/Public/StateStreamDefinitions.h` (Public)


#### struct `FStateStreamInterpolateContext`  
`struct FStateStreamInterpolateContext : FStateStreamCopyContext`  
_L31-34_
- inherits: `FStateStreamCopyContext`
- L33 _public member_ `double Factor = 0;`

#### Free symbols / members of external scopes

- L10 _variable_ `inline constexpr uint32 DefaultLaneId = ~0u;`
- L14 _macro_ `#define DECLARE_STATESTREAM(Type) \`
- L23 _macro_ `#define UE_STATESTREAM_TIME_TYPE double`
- L26 _typedef_ `using StateStreamTime = UE_STATESTREAM_TIME_TYPE;`
- L40 _function_ `template<typename Type> inline void StateStreamInterpolate(FStateStreamInterpolateContext& Context, Type& Out, const Type& From, const Type& To)`
- L46 _function_ `inline void StateStreamInterpolate(FStateStreamInterpolateContext& Context, uint32& Out, const uint32& From, const uint32& To)`
- L51 _function_ `inline void StateStreamInterpolate(FStateStreamInterpolateContext& Context, float& Out, const float& From, const float& To)`
- L56 _function_ `inline void StateStreamInterpolate(FStateStreamInterpolateContext& Context, double& Out, const double& From, const double& To)`
- L62 _function_ `template<typename Type> inline bool StateStreamEquals(const Type& A, const Type& B)`

### `Source/Runtime/StateStream/Public/StateStreamHandle.h` (Public)


#### struct `FStateStreamHandle`  
`struct FStateStreamHandle`  
_L24-50_
- reflection: `USTRUCT(NoExport)`
- L26 _public prototype_ `void MakeInternal();`
- L28 _public function_ `inline bool IsValid() const`
- L29 _public function_ `inline uint32 GetId() const`
- L31 _public prototype_ `void* Render_GetUserData() const;`
- L34 _protected prototype_ `FStateStreamHandle() = default;`
- L35 _protected prototype_ `FStateStreamHandle(const FStateStreamHandle& Other);`
- L36 _protected prototype_ `FStateStreamHandle(FStateStreamHandle&& Other);`
- L37 _protected prototype_ `FStateStreamHandle& operator=(FStateStreamHandle&& Other);`
- L38 _protected prototype_ `FStateStreamHandle& operator=(const FStateStreamHandle& Other);`
- L39 _protected prototype_ `~FStateStreamHandle();`
- L41 _protected prototype_ `FStateStreamHandle(IStateStreamHandleOwner& O, uint32 I);`
- L42 _protected prototype_ `FStateStreamHandle(FStateStreamCopyContext& Context, const FStateStreamHandle& Other);`
- L43 _protected prototype_ `void Apply(FStateStreamCopyContext& Context, const FStateStreamHandle& Other);`
- L45 _protected prototype_ `bool operator==(const FStateStreamHandle& Other) const;`
- L47 _protected member_ `IStateStreamHandleOwner* Owner = nullptr;`
- L48 _protected member_ `uint32 IsInternal = 0;`
- L49 _protected member_ `uint32 Id = 0;`

#### class `IStateStreamHandleOwner`  
`class IStateStreamHandleOwner`  
_L56-64_
- L59 _public prototype_ `virtual void Game_AddRef(uint32 HandleId) = 0;`
- L60 _public prototype_ `virtual void Game_Release(uint32 HandleId) = 0;`
- L61 _public prototype_ `virtual void Game_Update(uint32 HandleId, const void* DynamicState, double TimeFactor, uint64 UserData) = 0;`
- L62 _public prototype_ `virtual void* Game_Edit(uint32 HandleId, double TimeFactor, uint64 UserData) = 0;`
- L63 _public prototype_ `virtual void* Render_GetUserData(uint32 HandleId) = 0;`

#### struct `FStateStreamCopyContext`  
`struct FStateStreamCopyContext`  
_L70-73_
- L72 _public member_ `uint32 IsInternal = 1;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API STATESTREAM_API`
- L79 _macro_ `#define DECLARE_STATESTREAM_HANDLE(Type) \`

### `Source/Runtime/StateStream/Public/StateStreamManager.h` (Public)


#### class `IStateStreamManager`  
`class IStateStreamManager`  
_L12-46_
- L15 _public function_ `virtual uint32 Game_CreateLane()`
- L16 _public function_ `virtual void Game_SetLaneUserData(uint32 LaneId, void* UserData)`
- L17 _public function_ `virtual void Game_DestroyLane(uint32 LaneId)`
- L21 _public prototype_ `virtual void Game_BeginTick(uint32 LaneId) = 0;` — Call from Game when a new tick is opened Note, no state stream handles can be created,updated,destroyed outside a Begin/End tick
- L25 _public prototype_ `virtual void Game_EndTick(double AbsoluteTime, uint32 LaneId) = 0;` — Close tick and make it available to render side. AbsoluteTime is the amount of time that Game consumed
- L28 _public prototype_ `virtual void Game_Exit() = 0;` — Should be called when game is exiting.
- L31 _public prototype_ `virtual bool Game_IsInTick(uint32 LaneId) = 0;` — Returns true if game is inside an open tick
- L34 _public prototype_ `virtual uint32 Game_SetDefaultLane(uint32 LaneId) = 0;` — Set the lane that will be used if provided lane is DefaultLaneId. Returns previous default lane id
- L38 _public function_ `template<typename T> T& Game_Get()` — Functions to fetch StateStream interface (not IStateStream) game side.
- L39 _public prototype_ `virtual void* Game_GetStreamPointer(uint32 Id) = 0;`
- L42 _public prototype_ `virtual void Game_DebugRender(IStateStreamDebugRenderer& Renderer, uint32 LaneId) = 0;` — StateStream debug rendering
- L45 _protected prototype_ `virtual ~IStateStreamManager() = default;`

#### struct `FStateStreamLaneScope`  
`struct FStateStreamLaneScope`  
_L50-69_
- L52 _public function_ `FStateStreamLaneScope(IStateStreamManager* InManager, uint32 LaneId) : Manager(InManager)`
- L59 _public function_ `~FStateStreamLaneScope()`
- L67 _public member_ `IStateStreamManager* Manager;`
- L68 _public member_ `uint32 OldLaneId;`

### `Source/Runtime/StateStream/Public/StateStreamManagerImpl.h` (Public)


#### class `FStateStreamManagerImpl`  
`class FStateStreamManagerImpl : public IStateStreamManager`  
_L15-84_
- inherits: `IStateStreamManager`
- L19 _public prototype_ `virtual uint32 Game_CreateLane();`
- L20 _public prototype_ `virtual void Game_SetLaneUserData(uint32 LaneId, void* UserData);`
- L21 _public prototype_ `virtual void Game_DestroyLane(uint32 LaneId);`
- L22 _public prototype_ `virtual void Game_BeginTick(uint32 LaneId) override;`
- L23 _public prototype_ `virtual void Game_EndTick(double AbsoluteTime, uint32 LaneId) override;`
- L24 _public prototype_ `virtual void Game_Exit() override;`
- L25 _public prototype_ `virtual bool Game_IsInTick(uint32 LaneId) override;`
- L26 _public prototype_ `virtual uint32 Game_SetDefaultLane(uint32 LaneId) override;`
- L27 _public prototype_ `virtual void* Game_GetStreamPointer(uint32 Id) override;`
- L28 _public prototype_ `virtual void Game_DebugRender(IStateStreamDebugRenderer& Renderer, uint32 LaneId) override;`
- L33 _public prototype_ `void Render_Register(IStateStream& Stream, bool TakeOwnership);` — Register new state streams into manager. TakeOwnership true means that manager will delete stream when shutting down
- L36 _public prototype_ `void Render_RegisterDependency(uint32 FromId, uint32 ToId);` — Register dependency between state streams given their ids. FromId will depend on ToId
- L39 _public prototype_ `void Render_RegisterDependency(IStateStream& From, IStateStream& To);` — Register dependency between state streams given their interfaces. From will depend on To
- L42 _public prototype_ `void Render_Update(double AbsoluteTime);` — Called at the beginning of a render frame. AbsolutTime is the amount of time the render frame consumes
- L45 _public prototype_ `void Render_Exit();` — Called before Render thread exits
- L48 _public prototype_ `void Render_GarbageCollect(bool AsTask = false);` — Garbage collect all the unnecessary ticks/data within each streams
- L51 _public prototype_ `IStateStream* Render_GetStream(uint32 Id);` — Get state stream from id
- L65 _private member_ `TArray<StateStreamRec> StateStreams;` — List of state streams available in the manager
- L69 _private member_ `TArray<IStateStream*> StateStreamsLookup;` — List of state streams for each registered state stream id. This will allow fast lookup to retrieve a state stream given an id
- L71 _private member_ `uint32 ActiveDefaultLaneId = DefaultLaneId;`
- L74 _private member_ `bool bIsInTick = false;` — Bool to check if we are currently in between the begin and the end tick
- L77 _private member_ `bool bGameExited = false;` — Bool to check if the game has already been exited on the GT side
- L80 _private member_ `bool bRenderExited = false;` — Bool to check if the game has already been exited on the RT side
- L83 _private member_ `UE::Tasks::FTask GarbageCollectTask;` — Async task to perform the garbage collection

#### struct `FStateStreamManagerImpl::StateStreamRec`  
`struct StateStreamRec`  
_L58-62_
- desc: Small structure used to list the state streams available in the manager
- L60 _public member_ `IStateStream* Stream;`
- L61 _public member_ `bool Owned;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API STATESTREAM_API`

### `Source/Runtime/StateStream/Public/StateStreamStore.h` (Public)


#### class `TStateStreamStore`  
`template<typename T> class TStateStreamStore`  
_L14-35_
- L17 _public prototype_ `inline TStateStreamStore();`
- L18 _public prototype_ `inline ~TStateStreamStore();`
- L20 _public prototype_ `inline uint32 Add(const T& Value);`
- L21 _public prototype_ `inline void* AddUninitialized(uint32& OutIndex);`
- L22 _public prototype_ `inline void Remove(uint32 Index);`
- L25 _public prototype_ `template <typename... ArgsType> inline uint32 Emplace(ArgsType&&... Args);`
- L27 _public prototype_ `inline T& operator[](uint32 Index);`
- L29 _public prototype_ `inline uint32 GetUsedCount() const;`
- L32 _private member_ `FRWLock Lock;`
- L33 _private member_ `FPow2ChunkedArray<T> Array;`
- L34 _private member_ `uint32 FirstFreeIndex = ~0u;`
- L41 _function_ `template<typename T> TStateStreamStore<T>::TStateStreamStore()`
- L47 _function_ `template<typename T> TStateStreamStore<T>::~TStateStreamStore()`
- L61 _function_ `template<typename T> uint32 TStateStreamStore<T>::Add(const T& Value)`
- L69 _function_ `template<typename T> void* TStateStreamStore<T>::AddUninitialized(uint32& OutIndex)`
- L88 _function_ `template<typename T> void TStateStreamStore<T>::Remove(uint32 Index)`
- L100 _function_ `template<typename T> template <typename... ArgsType> uint32 TStateStreamStore<T>::Emplace(ArgsType&&... Args)`
- L108 _function_ `template<typename T> T& TStateStreamStore<T>::operator[](uint32 Index)`
- L114 _function_ `template<typename T> uint32 TStateStreamStore<T>::GetUsedCount() const`

### `Source/Runtime/StateStream/Public/TransformStateStream.h` (Public)


#### struct `FTransformStaticState`  
`struct FTransformStaticState`  
_L14-17_
- reflection: `USTRUCT(StateStreamStaticState)`

#### struct `FTransformDynamicState`  
`struct FTransformDynamicState`  
_L24-52_
- reflection: `USTRUCT(StateStreamDynamicState)`
- L32 _private member_ `FTransform LocalTransform = FTransform::Identity;` — `UPROPERTY()` — Transform relative Parent
- L35 _private member_ `TArray<FTransform> BoneTransforms;` — `UPROPERTY()`
- L39 _private member_ `FTransformHandle Parent;` — `UPROPERTY()` — Parent
- L51 _private member_ `bool bVisible = true;` — `UPROPERTY()`

#### class `ITransformStateStream`  
`class ITransformStateStream`  
_L64-69_
- L67 _public prototype_ `DECLARE_STATESTREAM(Transform) virtual FTransformHandle Game_CreateInstance(const FTransformStaticState& Ss, const FTransformDynamicState& Ds, uint32 LaneId = DefaultLaneId) = 0;`

#### Free symbols / members of external scopes

- L58 _variable_ `inline constexpr uint32 TransformStateStreamId = 1;`

### `Source/Runtime/StateStream/Public/TransformStateStreamHandle.h` (Public)


#### struct `FTransformHandle`  
`struct FTransformHandle : public FStateStreamHandle`  
_L14-17_
- reflection: `USTRUCT(StateStreamHandle)`
- inherits: `FStateStreamHandle`

### `Source/Runtime/StateStream/Public/TransformStateStreamImpl.h` (Public)


#### class `FTransformObjectListener`  
`class FTransformObjectListener`  
_L15-24_
- L18 _public prototype_ `virtual void OnTransformObjectDirty() = 0;`
- L21 _private member_ `FTransformObjectListener* Prev = nullptr;`
- L22 _private member_ `FTransformObjectListener* Next= nullptr;`

#### class `FTransformObject`  
`class FTransformObject : public TRefCountingMixin<FTransformObject>, public FTransformObjectListener`  
_L30-59_
- inherits: `TRefCountingMixin<FTransformObject>,FTransformObjectListener`
- L40 _public prototype_ `Info GetInfo();`
- L42 _public prototype_ `void AddListener(FTransformObjectListener* Listener);`
- L43 _public prototype_ `void RemoveListener(FTransformObjectListener* Listener);`
- L46 _private prototype_ `virtual ~FTransformObject();`
- L47 _private prototype_ `void CallListeners();`
- L48 _private prototype_ `virtual void OnTransformObjectDirty() override final;`
- L50 _private member_ `TRefCountPtr<FTransformObject> Parent;`
- L51 _private member_ `FTransformObjectListener* First = 0;`
- L52 _private member_ `const FTransformDynamicState* LocalState = nullptr;`
- L53 _private member_ `FTransform WorldTransform;`
- L54 _private member_ `bool bDirty = true;`
- L55 _private member_ `bool bVisible = true;`

#### struct `FTransformObject::Info`  
`struct Info`  
_L33-38_
- L35 _public member_ `const FTransform& WorldTransform;`
- L36 _public member_ `const TArray<FTransform>& BoneTransforms;`
- L37 _public member_ `bool bVisible;`

#### class `FTransformStateStreamImpl`  
`class FTransformStateStreamImpl : public TStateStream<TStateStreamSettings<ITransformStateStream, FTransformObject>>`  
_L64-71_
- inherits: `TStateStream<TStateStreamSettings<ITransformStateStream,FTransformObject>>`
- L67 _private prototype_ `void SetParent(FTransformObject* Object, const FTransformDynamicState& Ds);`
- L68 _private prototype_ `virtual void Render_OnCreate(const FTransformStaticState& Ss, const FTransformDynamicState& Ds, FTransformObject*& UserData, bool IsDestroyedInSameFrame) override;`
- L69 _private prototype_ `virtual void Render_OnUpdate(const FTransformStaticState& Ss, const FTransformDynamicState& Ds, FTransformObject*& UserData) override;`
- L70 _private prototype_ `virtual void Render_OnDestroy(const FTransformStaticState& Ss, const FTransformDynamicState& Ds, FTransformObject*& UserData) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API STATESTREAM_API`

### `Source/Runtime/StateStream/Public/TransformStateStreamMath.h` (Public)


#### Free symbols / members of external scopes

- L12 _function_ `inline void StateStreamInterpolate(FStateStreamInterpolateContext& Context, FTransform& Out, const FTransform& From, const FTransform& To)`
- L17 _function_ `inline bool StateStreamEquals(const FTransform& A, const FTransform& B)`
- L22 _function_ `inline void StateStreamInterpolate(FStateStreamInterpolateContext& Context, TArray<FTransform>& Out, const TArray<FTransform>& From, const TArray<FTransform>& To)`
- L33 _function_ `inline bool StateStreamEquals(const TArray<FTransform>& A, const TArray<FTransform>& B)`
