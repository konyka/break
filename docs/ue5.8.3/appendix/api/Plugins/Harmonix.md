# Plugins / Harmonix

- module root: `Plugins/Runtime/Harmonix/Source/Harmonix`
- headers: 7; symbols: 146
- symbol kinds: class=9, enum=3, enumerator=11, function=82, macro=4, member=14, namespace=2, prototype=17, typedef=4
- PrivateDependencyModuleNames: CoreUObject, Engine, Slate, SlateCore
- PublicDependencyModuleNames: AudioExtensions, Core, DeveloperSettings

### `Plugins/Runtime/Harmonix/Source/Harmonix/Public/Harmonix.h` (Public)


#### class `FHarmonixModule`  
`class FHarmonixModule : public IModuleInterface`  
_L11-137_
- inherits: `IModuleInterface`
- L14 _public function_ `static inline FHarmonixModule& Get()`
- L20 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L21 _public prototype_ `virtual void ShutdownModule() override;`
- L35 _public function_ `static void SetMeasuredUserExperienceAndReactionToAudioRenderOffsetMs(float Milliseconds)` — User Experience Offset Ms is the number of milliseconds between the "smoothed music render time" and the time the player experiences hearing the rendered audio, makes an input, and we detect it in the game code. This is time spent buffering audio, marshaling it to the operating system, operating system buffering, DAC, home theater, TV's audio system, transmission through the air, controller detecting input, sending that input back to the console, console OS sending it to game code, etc. This should be a positive number, otherwise the player is somehow hearing the audio BEFORE it is even rendered. So the player is experiencing... ExperiencedAudioTime = SmoothedMusicRenderMs - User Experience Offset. (See more detail below)
- L36 _public function_ `static float GetMeasuredUserExperienceAndReactionToAudioRenderOffsetMs()`
- L46 _public function_ `static void SetMeasuredVideoToAudioRenderOffsetMs(float Milliseconds)` — Video Render Offset Ms is the number of milliseconds between the "smoothed music render time" and when graphics should be rendered that correspond to that time, so that the player experiences SEEING musically synchronized visual effects at the same moment they experience HEARING the associated musical moment. AudioTimeToRenderGraphicsFor = SmoothedMusicRenderMs - Video Render Offset MS (See more detail below)
- L47 _public function_ `static float GetMeasuredVideoToAudioRenderOffsetMs()`
- L135 _private member_ `float AudioLatencyMs = 0.0f;`
- L136 _private member_ `float VideoLatencyMs = 0.0f;`

#### class `UHarmonixBlueprintUtil`  
`class UHarmonixBlueprintUtil : public UBlueprintFunctionLibrary`  
_L140-164_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L145 _public function_ `static void SetMeasuredUserExperienceAndReactionToAudioRenderOffsetMs(float Milliseconds)` — `UFUNCTION(BlueprintCallable, Category = "Harmonix|Calibration")`
- L150 _public function_ `static float GetMeasuredUserExperienceAndReactionToAudioRenderOffsetMs()` — `UFUNCTION(BlueprintCallable, Category = "Harmonix|Calibration")`
- L155 _public function_ `static void SetMeasuredVideoToAudioRenderOffsetMs(float Milliseconds)` — `UFUNCTION(BlueprintCallable, Category = "Harmonix|Calibration")`
- L160 _public function_ `static float GetMeasuredVideoToAudioRenderOffsetMs()` — `UFUNCTION(BlueprintCallable, Category = "Harmonix|Calibration")`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API HARMONIX_API`

### `Plugins/Runtime/Harmonix/Source/Harmonix/Public/Harmonix/AudioRenderableProxy.h` (Public)


#### class `Harmonix::TRefCountedAudioRenderableWithQueuedChanges`  
`template<typename DATA_STRUCT> class TRefCountedAudioRenderableWithQueuedChanges`  
_L36-233_
- desc: This next class implements an intrusive ref counted wrapper around your audio renderable data. It can be shared between the UObject thread(s) and the audio rendering thread(s). In addition to the ref count, this version includes a TSharedAudioRenderableDataPtr to the *next*, or *updated*, data. This allows for a lock-free queue of updated settings, where new settings can be generated on the UObject side and appended to this as new settings. This way, consumers of these settings can look for updated data and move to that data at their leisure. Because this is done through a ref counted pointer, eventually, when no rendering instance is using an old instance of the data, the ref count will go to zero and the unused settings will be freed.
- L42 _public function_ `TRefCountedAudioRenderableWithQueuedChanges() : Data() , RefCount(1) , QueuedDataUpdate()` — FIRST: The Six... Empty Construct
- L48 _public function_ `TRefCountedAudioRenderableWithQueuedChanges(const TRefCountedAudioRenderableWithQueuedChanges<DATA_STRUCT>& Other) : Data(Other.Data) , RefCount(1) , QueuedDataUpdate(Other.QueuedDataUpdate)` — Copy Construct
- L54 _public function_ `TRefCountedAudioRenderableWithQueuedChanges<DATA_STRUCT>& operator=(const TRefCountedAudioRenderableWithQueuedChanges<DATA_STRUCT>& Other)` — Copy Assign
- L64 _public function_ `TRefCountedAudioRenderableWithQueuedChanges(TRefCountedAudioRenderableWithQueuedChanges<DATA_STRUCT>&& Other) noexcept : Data(MoveTemp(Other.Data)) , QueuedDataUpdate(MoveTemp(Other.QueuedDataUpdate))` — Move Construct
- L72 _public function_ `TRefCountedAudioRenderableWithQueuedChanges<DATA_STRUCT>& operator=(TRefCountedAudioRenderableWithQueuedChanges<DATA_STRUCT>&& Other) noexcept` — Move Assign
- L81 _public function_ `~TRefCountedAudioRenderableWithQueuedChanges()` — Destruct
- L90 _public function_ `template<typename ... TArgs> TRefCountedAudioRenderableWithQueuedChanges(TArgs&&... Args) noexcept : Data(Forward<TArgs>(Args)...) , RefCount(1)` — NOW: Some Specials... New With Arguments For DATA_STRUCT
- L95 _public function_ `TRefCountedAudioRenderableWithQueuedChanges(const DATA_STRUCT& Other) : Data(Other) , RefCount(1) , QueuedDataUpdate()` — Copy Construct From const DATA_STRUCT reference
- L101 _public function_ `TRefCountedAudioRenderableWithQueuedChanges(DATA_STRUCT& Other) : Data(Other) , RefCount(1) , QueuedDataUpdate()` — Copy Construct From non-const DATA_STRUCT reference
- L107 _public function_ `TRefCountedAudioRenderableWithQueuedChanges<DATA_STRUCT>& operator=(const DATA_STRUCT& Other)` — Copy Assign From DATA_STRUCT
- L114 _public function_ `TRefCountedAudioRenderableWithQueuedChanges(DATA_STRUCT&& Other) noexcept : Data(MoveTemp(Other)) , RefCount(1) , QueuedDataUpdate()` — Move Construct From DATA_STRUCT
- L120 _public function_ `TRefCountedAudioRenderableWithQueuedChanges<DATA_STRUCT>& operator=(DATA_STRUCT&& Other) noexcept` — Move Assign From DATA_STRUCT
- L130 _private member_ `DATA_STRUCT Data;`
- L133 _public function_ `FORCEINLINE operator DATA_STRUCT*()` — Conversion operators
- L138 _public function_ `FORCEINLINE operator const DATA_STRUCT*() const`
- L144 _public function_ `FORCEINLINE DATA_STRUCT* operator->()` — Dereference operators
- L148 _public function_ `FORCEINLINE const DATA_STRUCT* operator->() const`
- L155 _public function_ `FORCEINLINE bool operator==(const TRefCountedAudioRenderableWithQueuedChanges<DATA_STRUCT>& Other) const` — Comparisons
- L159 _public function_ `FORCEINLINE bool operator==(const DATA_STRUCT& Other) const`
- L170 _private member_ `mutable std::atomic<uint32> RefCount;`
- L172 _public function_ `FORCEINLINE void AddRef() const`
- L182 _public function_ `FORCEINLINE void RemoveRef() const`
- L201 _public function_ `FORCEINLINE int32 GetRefCount()`
- L207 _private member_ `TSharedAudioRenderableDataPtr<DATA_STRUCT, TRefCountedAudioRenderableWithQueuedChanges> QueuedDataUpdate;`
- L209 _public function_ `void QueueUpdate(const TSharedAudioRenderableDataPtr<DATA_STRUCT, TRefCountedAudioRenderableWithQueuedChanges>& Update)`
- L224 _public function_ `FORCEINLINE bool HasUpdate() const`
- L229 _public function_ `FORCEINLINE const TSharedAudioRenderableDataPtr<DATA_STRUCT, TRefCountedAudioRenderableWithQueuedChanges>& GetUpdate() const`

#### class `Harmonix::TSharedAudioRenderableDataPtr`  
`template<typename DATA_STRUCT, typename REFCOUNT_TYPE> class TSharedAudioRenderableDataPtr`  
_L237-385_
- desc: This next class is a shared pointer to an instance of the audio renderable data above.
- L242 _public function_ `static TSharedAudioRenderableDataPtr<DATA_STRUCT, REFCOUNT_TYPE> CreateSharedRenderable(const DATA_STRUCT& Source)` — Static Create Functions
- L246 _public function_ `static TSharedAudioRenderableDataPtr<DATA_STRUCT, REFCOUNT_TYPE> CreateSharedRenderable(DATA_STRUCT& Source)`
- L251 _public function_ `template<typename... TArgs> static TSharedAudioRenderableDataPtr<DATA_STRUCT, REFCOUNT_TYPE> CreateSharedRenderable(TArgs&& ... Args)`
- L259 _public function_ `TSharedAudioRenderableDataPtr() : Renderable(nullptr)` — FIRST: The Six... Empty Construct
- L263 _public function_ `TSharedAudioRenderableDataPtr(const TSharedAudioRenderableDataPtr<DATA_STRUCT, REFCOUNT_TYPE>& Other) : Renderable(Other.Renderable)` — Copy Construct
- L272 _public function_ `TSharedAudioRenderableDataPtr<DATA_STRUCT, REFCOUNT_TYPE>& operator=(const TSharedAudioRenderableDataPtr<DATA_STRUCT, REFCOUNT_TYPE>& Other)` — Copy Assign
- L290 _public function_ `TSharedAudioRenderableDataPtr(TSharedAudioRenderableDataPtr<DATA_STRUCT, REFCOUNT_TYPE>&& Other) noexcept : Renderable(MoveTemp(Other.Renderable))` — Move Construct
- L294 _public function_ `TSharedAudioRenderableDataPtr<DATA_STRUCT, REFCOUNT_TYPE>& operator=(TSharedAudioRenderableDataPtr<DATA_STRUCT, REFCOUNT_TYPE>&& Other) noexcept` — Move Assign
- L306 _public function_ `~TSharedAudioRenderableDataPtr()` — Destruct
- L316 _public function_ `TSharedAudioRenderableDataPtr(REFCOUNT_TYPE* SharedStruct) : Renderable(SharedStruct)` — From a new'd instance of AudioRenderableData or nullptr...
- L325 _public function_ `TSharedAudioRenderableDataPtr(const DATA_STRUCT& Source) : Renderable(new REFCOUNT_TYPE(Source))`
- L332 _public function_ `FORCEINLINE operator DATA_STRUCT* ()` — The Wrapped Data Conversion Operators...
- L336 _public function_ `FORCEINLINE operator const DATA_STRUCT* () const`
- L340 _public function_ `FORCEINLINE operator REFCOUNT_TYPE* ()`
- L344 _public function_ `FORCEINLINE operator const REFCOUNT_TYPE* () const`
- L349 _public function_ `FORCEINLINE DATA_STRUCT* operator->()` — Dereference Operators...
- L353 _public function_ `FORCEINLINE const DATA_STRUCT* operator->() const`
- L357 _public function_ `FORCEINLINE REFCOUNT_TYPE* operator*()`
- L361 _public function_ `FORCEINLINE const REFCOUNT_TYPE* operator*() const`
- L366 _public function_ `FORCEINLINE operator bool()` — Comparisons...
- L370 _public function_ `FORCEINLINE operator bool() const`
- L374 _public function_ `FORCEINLINE bool operator==(const TSharedAudioRenderableDataPtr& Other) const`
- L378 _public function_ `FORCEINLINE bool operator!=(const TSharedAudioRenderableDataPtr& Other) const`
- L384 _private member_ `REFCOUNT_TYPE* Renderable = nullptr;`

#### class `Harmonix::TGameThreadToAudioRenderThreadSettingQueue`  
`template<typename DATA_STRUCT> class TGameThreadToAudioRenderThreadSettingQueue`  
_L395-479_
- desc: This next class is a "maintainer" of a queue of audio renderable data structs. This level of indirection is required because of the way Metasound's audio proxy system works. This small class just holds a shared pointer to the current tail of the change queue... so the current version of the settings. Any new rendering instance that might come alive asks the asset's UObject for a unique ptr to a proxy. That proxy is actually a thin wrapper around one of these. So all rendering instamces see this same proxy, and can get the current setting tail when they are instantiated.
- L398 _public typedef_ `using NodeType = TRefCountedAudioRenderableWithQueuedChanges<DATA_STRUCT>;`
- L399 _public typedef_ `using SharedNodePtrType = TSharedAudioRenderableDataPtr<DATA_STRUCT, NodeType>;`
- L401 _public prototype_ `TGameThreadToAudioRenderThreadSettingQueue() = default;`
- L402 _public prototype_ `TGameThreadToAudioRenderThreadSettingQueue(const TGameThreadToAudioRenderThreadSettingQueue<DATA_STRUCT>& Other) = default;`
- L403 _public prototype_ `TGameThreadToAudioRenderThreadSettingQueue<DATA_STRUCT>& operator=(const TGameThreadToAudioRenderThreadSettingQueue<DATA_STRUCT>& Other) = default;`
- L404 _public prototype_ `TGameThreadToAudioRenderThreadSettingQueue(TGameThreadToAudioRenderThreadSettingQueue<DATA_STRUCT>&& Other) noexcept = default;`
- L405 _public prototype_ `TGameThreadToAudioRenderThreadSettingQueue<DATA_STRUCT>& operator=(TGameThreadToAudioRenderThreadSettingQueue<DATA_STRUCT>&& Other) = default;`
- L406 _public prototype_ `~TGameThreadToAudioRenderThreadSettingQueue() = default;`
- L408 _public function_ `TGameThreadToAudioRenderThreadSettingQueue(const DATA_STRUCT& InitialSettings) : Tail(InitialSettings)`
- L412 _public function_ `FORCEINLINE operator bool() const`
- L417 _public function_ `FORCEINLINE DATA_STRUCT* operator->()`
- L423 _public function_ `FORCEINLINE const DATA_STRUCT* operator->() const`
- L429 _public function_ `FORCEINLINE SharedNodePtrType& operator*()`
- L435 _public function_ `FORCEINLINE const SharedNodePtrType& operator*() const`
- L441 _public function_ `FORCEINLINE operator SharedNodePtrType& ()`
- L446 _public function_ `FORCEINLINE operator const SharedNodePtrType& () const`
- L451 _public function_ `FORCEINLINE operator DATA_STRUCT* ()`
- L456 _public function_ `FORCEINLINE operator const DATA_STRUCT* () const`
- L461 _public function_ `FORCEINLINE void SetNewSettings(const SharedNodePtrType& NewSettings)`
- L471 _public function_ `FORCEINLINE void SetNewSettings(const DATA_STRUCT& NewSettings)`
- L478 _private member_ `SharedNodePtrType Tail;`

#### class `Harmonix::TAudioRenderableProxy`  
`template<typename DATA_STRUCT, typename QUEUE_TYPE> class TAudioRenderableProxy : public Audio::TProxyData<TAudioRenderableProxy<DATA_STRUCT, QUEUE_TYPE>>`  
_L483-525_
- inherits: `Audio::TProxyData<TAudioRenderableProxy<DATA_STRUCT,QUEUE_TYPE>>`
- desc: And this next class simplifies that creation of the Audio::TProxyData that wrapps all of the above.
- L486 _public typedef_ `using QueueType = QUEUE_TYPE;`
- L487 _public typedef_ `using NodePtr = typename QUEUE_TYPE::SharedNodePtrType;`
- L490 _public function_ `static FName GetAudioProxyTypeName()` — IMPL_AUDIOPROXY_CLASS(TAudioRenderableProxy);
- L494 _public function_ `static FName GetInterfaceId()`
- L495 _public function_ `virtual void* QueryInterface(const FName InterfaceId) override`
- L503 _public member_ `static constexpr bool bWasAudioProxyClassImplemented = true;`
- L507 _public function_ `explicit TAudioRenderableProxy(const TSharedPtr<QUEUE_TYPE>& InSettingsQueue) : SettingsQueue(InSettingsQueue)`
- L512 _public prototype_ `TAudioRenderableProxy(const TAudioRenderableProxy<DATA_STRUCT, QUEUE_TYPE>& Other) = default;`
- L514 _public function_ `NodePtr GetRenderable()`
- L524 _private member_ `TSharedPtr<QUEUE_TYPE> SettingsQueue;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Harmonix`
- L14 _macro_ `#define USING_AUDIORENDERABLE_PROXY(RootStructName, ProxyName) using ProxyName = Harmonix::TAudioRenderableProxy<RootStructName, Harmonix::TGameThreadToAudioRenderThreadSettingQueue<RootStructName>>;` — This macro is short hand for declaring a `TAudioRenderableProxy` that wraps arround your "RootStructName" audio data type.
- L19 _macro_ `#define IMPL_AUDIORENDERABLE_PROXYABLE(StructName) \` — This next macro needs to be added to the struct containing the settings (UPROPERTIES) you want to share between the UObject asset and the Metasound Node. This so that later we can easily make the proxy with a template class.

### `Plugins/Runtime/Harmonix/Source/Harmonix/Public/Harmonix/HarmonixDeveloperSettings.h` (Public)


#### class `UHarmonixDeveloperSettings`  
`class UHarmonixDeveloperSettings : public UObject`  
_L10-13_
- reflection: `UCLASS(MinimalAPI, Abstract, EditInlineNew)`
- inherits: `UObject`
- desc: base class for all settings you want to group with this plugin allows configuration to appear in the "Harmonix"

### `Plugins/Runtime/Harmonix/Source/Harmonix/Public/Harmonix/HarmonixPluginSettings.h` (Public)


#### class `UHarmonixPluginSettings`  
`class UHarmonixPluginSettings : public UDeveloperSettings`  
_L12-26_
- reflection: `UCLASS(MinimalAPI, config = Engine, defaultconfig, Meta = (DisplayName = "Harmonix"))`
- inherits: `UDeveloperSettings`
- L22 _public prototype_ `virtual FText GetSectionText() const override;`
- L25 _public prototype_ `UHarmonixPluginSettings();`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API HARMONIX_API`

### `Plugins/Runtime/Harmonix/Source/Harmonix/Public/Harmonix/LocalMinimumMagnitudeTracker.h` (Public)


#### class `FLocalMinimumMagnitudeTracker`  
`template <typename T, int32 SIZE> class FLocalMinimumMagnitudeTracker`  
_L8-67_
- L11 _public function_ `FLocalMinimumMagnitudeTracker()`
- L13 _public function_ `void Reset()`
- L22 _public function_ `void Push(T v)`
- L49 _public function_ `T Min() const`
- L51 _public function_ `T Average() const`
- L62 _private member_ `T Ring[SIZE];`
- L63 _private member_ `int32 NextWrite = 0;`
- L64 _private member_ `int32 MinPosition = 0;`
- L65 _private member_ `T AccumulatedError = 0;`
- L66 _private member_ `bool Wrapped = false;`

### `Plugins/Runtime/Harmonix/Source/Harmonix/Public/Harmonix/MusicalTimebase.h` (Public)


#### enum `ECalibratedMusicTimebase`  
`enum class ECalibratedMusicTimebase : uint8`  
_L10-38_
- reflection: `UENUM(BlueprintType)`
- L17 _public enumerator_ `AudioRenderTime` — Tells you almost exactly where the audio renderer is right now (smoothed version of the jittery, raw position of the audio rendering). Useful for queuing up musical events based on the current song time.
- L23 _public enumerator_ `ExperiencedTime` — Tells you what the player is actually hearing & seeing this instant (when properly calibrated). Useful for scoring player input.
- L29 _public enumerator_ `VideoRenderTime` — Tells you what you should be drawing right now so it appears *in sync with the music.* (when properly calibrated). Useful for synchronizing animations, ui, and other visuals to the music.
- L35 _public enumerator_ `RawAudioRenderTime` — Tells you exactly where the audio renderer is right now. NOTE: Un-smoothed, jittery, raw position of the audio rendering. Only useful for debugging!
- L37 _public enumerator_ `Count UMETA(Hidden)`

#### Free symbols / members of external scopes

- L40 _prototype_ `ENUM_RANGE_BY_COUNT(ECalibratedMusicTimebase, ECalibratedMusicTimebase::Count);`

### `Plugins/Runtime/Harmonix/Source/Harmonix/Public/Harmonix/PropertyUtility.h` (Public)


#### enum `Harmonix::EPostEditAction`  
`enum EPostEditAction : uint8`  
_L16-21_
- L18 _public enumerator_ `DoNothing`
- L19 _public enumerator_ `UpdateTrivial`
- L20 _public enumerator_ `UpdateNonTrivial`

#### enum `Harmonix::EPostEditType`  
`enum EPostEditType : uint8`  
_L23-28_
- L25 _public enumerator_ `None`
- L26 _public enumerator_ `Trivial`
- L27 _public enumerator_ `NonTrivial`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Harmonix`
- L31 _prototype_ `EPostEditAction GetPropertyPostEditAction(const FProperty* Property, EPropertyChangeType::Type ChangeType, EPostEditAction DefaultAction = EPostEditAction::UpdateNonTrivial);` (scope `Harmonix`)
- L34 _prototype_ `EPostEditType GetPropertyPostEditType(const FProperty* Property);` (scope `Harmonix`)
- L37 _prototype_ `void LogPropertyValue(void* PropValuePtr, FProperty* Property);` (scope `Harmonix`) — Avoid using these methods directly. Use the template versions
- L38 _prototype_ `bool CopyStructRecursive(void* InDest, void* InSrc, const UScriptStruct* ScriptStruct);` (scope `Harmonix`)
- L39 _prototype_ `void LogStructRecursive(void* PropPtr, const UScriptStruct* ScriptStruct);` (scope `Harmonix`)
- L80 _function_ `template<typename TStructType> FString GetStructPropertyChainString(TStructType* StructPtr, const FPropertyChangedChainEvent& PropertyChangedChainEvent)` (scope `Harmonix`) — Given a pointer to a valid struct member, walk the PropertyChain given the PropertyChangedChainEvent constructing an FString representing the property chain. For example: FBaz { int Number = 4; } FBar { TArray<FBaz> BazArray; } UMyObject { FBar MyBar; virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedChainEvent) override { FString PropertyChangedString = Harmonix::GetStructPropertyChainString(&MyBar, PropertyChangedChainEvent); } } if MyBar.BazArray[3].Number was changed from 4 to 6 for example, then the resulting string will be - "MyBar.BazArray[3].Number = 6" ensures that the FProperty at the head of the PropertyChain is the same type as the struct passed in @param StructPtr					- Src Data ptr of type TStructType @param PropertyChangedChainEvent - Property chain that should correspond to the Struct type passed in. The Tail of the property chain should be a copiable value type.
- L208 _function_ `template<typename TStructType> void LogStructProperties(TStructType* StructPtr)` (scope `Harmonix`) — Given a pointer to a valid struct member, will recursively iterate over all the properties in the struct and all child structs and arrays and log the values in each logs each value on a new line For example: FBaz { int Number = 4; } FBar { TArray<FBaz> BazArray; } UMyObject { FBar MyBar; void LogProperty() { MyBar.BazArray.Add(FBaz()); MyBar.BazArray.Add(FBaz()); MyBar.BazArray[0].Number = 3; MyBar.BazArray[1].Number = 10; Harmonix::LogStructProperties(&MyBar); } } Log: MyBar { Log: BazArray [ Log: Baz { Log:    Number = 3 Log: } ~Baz Log: Baz { Log:    Number = 10 Log: } ~Baz Log: ] ~BazArray Log: } ~MyBar ensures that the FProperty at the head of the PropertyChain is the same type as the struct passed in
- L260 _function_ `template<typename TStructType> bool CopyStructProperty(TStructType* InDest, TStructType* InSrc, const FPropertyChangedChainEvent& PropertyChangedChainEvent)` (scope `Harmonix`) — Given pointers to valid structs walks the PropertyChain given the PropertyChangedChainEvent copying the property that was changed from the Source Struct to the Dest Struct Assumes that the number of elements in each struct and child struct arrays are identical For example: FBaz { int Number = 4; } FBar { TArray<FBaz> BazArray; } UMyObject { FBar MyBar; FBar MyBarProxy; virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedChainEvent) override { Harmonix::CopyStructProperty(&MyBarProxy, &MyBar, PropertyChangedChainEvent); } } if MyBar.BazArray[3].Number was changed from 4 to 6 for example, then the PropertyChangedChainEvent would point to that property that was changed. So the value in MyBar.BazArray[3].Number will be copied into MyBarProxy.BazArray[3].Number; ensures that the FProperty at the head of the PropertyChain is the same type as the struct passed in returns whether the copy was successful - Copy can fail if types don't match the PropertyChangedChainEvent - Copy can fail if there is a size mismatch in any child arrays contained in any of the structs
- L352 _function_ `template<typename TStructType> bool CopyStructProperties(TStructType* InDest, TStructType* InSrc)` (scope `Harmonix`) — Recursively copies the struct properties from InSrc to InDest Asusmes
