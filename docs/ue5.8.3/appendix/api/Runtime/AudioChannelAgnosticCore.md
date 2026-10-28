# Runtime / AudioChannelAgnosticCore

- module root: `Source/Runtime/AudioChannelAgnosticCore`
- headers: 9; symbols: 221
- symbol kinds: class=15, enum=2, enumerator=20, function=91, macro=1, member=40, namespace=12, prototype=21, struct=8, typedef=11
- PrivateDependencyModuleNames: Core, SignalProcessing
- PublicDependencyModuleNames: Core, CoreUObject
- PublicIncludePathModuleNames: AudioMixer

### `Source/Runtime/AudioChannelAgnosticCore/Public/ChannelAgnostic/ChannelAgnosticTranscoding.h` (Public)


#### enum `Audio::EChannelTranscodeMethod`  
`enum class EChannelTranscodeMethod : uint8`  
_L9-13_
- L11 _public enumerator_ `ChannelDrop`
- L12 _public enumerator_ `MixUpOrDown`

#### struct `Audio::ChannelAgnosticTranscoder::FGetTranscoderParams`  
`struct FGetTranscoderParams`  
_L18-23_
- L20 _public member_ `const FChannelTypeFamily& ToType;`
- L21 _public member_ `EChannelTranscodeMethod TranscodeMethod = EChannelTranscodeMethod::ChannelDrop;`
- L22 _public member_ `EChannelMapMonoUpmixMethod MixMethod = EChannelMapMonoUpmixMethod::EqualPower;`

#### struct `Audio::TFromVisitor`  
`template<typename TFromType> struct UE_EXPERIMENTAL(5.8,"AudioChannelAgnosticCore is experimental and in flux") TFromVisitor final : IChannelTypeVisitor`  
_L49-71_
- inherits: `IChannelTypeVisitor`
- L51 _public member_ `const TFromType& FromType;`
- L52 _public member_ `const ChannelAgnosticTranscoder::FGetTranscoderParams& Params;`
- L53 _public member_ `ChannelAgnosticTranscoder::FTranscoder& Transcoder;`
- L55 _public function_ `TFromVisitor(const TFromType& InFromType, const ChannelAgnosticTranscoder::FGetTranscoderParams& InParams, ChannelAgnosticTranscoder::FTranscoder& InTranscoder) : FromType(InFromType), Params(InParams), Transcoder(InTranscoder)`
- L59 _public function_ `virtual void Visit(const FDiscreteChannelTypeFamily& InTo) override`
- L63 _public function_ `virtual void Visit(const FSoundfieldChannelTypeFamily& InTo) override`
- L67 _public function_ `virtual void Visit(const FCompositeChannelTypeFamily& InTo) override`

#### struct `Audio::FTranscoderResolver`  
`struct FTranscoderResolver final : public IChannelTypeVisitor`  
_L73-106_
- inherits: `IChannelTypeVisitor`
- L77 _public function_ `explicit FTranscoderResolver(const ChannelAgnosticTranscoder::FGetTranscoderParams& InParams) : Params(InParams)`
- L78 _public function_ `virtual void Visit(const FDiscreteChannelTypeFamily& InFrom) override`
- L83 _public function_ `virtual void Visit(const FSoundfieldChannelTypeFamily& InFrom) override`
- L88 _public function_ `virtual void Visit(const FCompositeChannelTypeFamily& InFrom) override`
- L95 _public function_ `static ChannelAgnosticTranscoder::FTranscoder Resolve(const FChannelTypeFamily& FromType, const ChannelAgnosticTranscoder::FGetTranscoderParams& Params)`
- L102 _public member_ `ChannelAgnosticTranscoder::FGetTranscoderParams Params;`
- L103 _public member_ `ChannelAgnosticTranscoder::FTranscoder Result;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Audio`
- L16 _namespace_ `namespace ChannelAgnosticTranscoder` (scope `Audio`)
- L25 _typedef_ `using FTranscoder = TFunction<void(TArrayView<const float*>, TArrayView<float*>, const int32 NumFrames)>;` (scope `Audio::ChannelAgnosticTranscoder`)
- L27 _typedef_ `using FDiscrete = FDiscreteChannelTypeFamily;` (scope `Audio::ChannelAgnosticTranscoder`)
- L28 _typedef_ `using FSoundfield = FSoundfieldChannelTypeFamily;` (scope `Audio::ChannelAgnosticTranscoder`)
- L29 _typedef_ `using FComposite = FCompositeChannelTypeFamily;` (scope `Audio::ChannelAgnosticTranscoder`)
- L30 _typedef_ `using FParams = FGetTranscoderParams;` (scope `Audio::ChannelAgnosticTranscoder`)
- L33 _prototype_ `FTranscoder GetTranscoder(const FDiscrete& InFrom, const FDiscrete& InTo, const FParams&);` (scope `Audio::ChannelAgnosticTranscoder`) — Discrete-to-X
- L34 _prototype_ `FTranscoder GetTranscoder(const FDiscrete& InFrom, const FSoundfield& InTo, const FParams&);` (scope `Audio::ChannelAgnosticTranscoder`) — d->s
- L35 _prototype_ `FTranscoder GetTranscoder(const FDiscrete& InFrom, const FComposite& InTo, const FParams&);` (scope `Audio::ChannelAgnosticTranscoder`) — d->c
- L38 _prototype_ `FTranscoder GetTranscoder(const FSoundfield& InFrom, const FSoundfield& InTo, const FParams&);` (scope `Audio::ChannelAgnosticTranscoder`) — Soundfield-to-X
- L39 _prototype_ `FTranscoder GetTranscoder(const FSoundfield& InFrom, const FDiscrete& InTo, const FParams&);` (scope `Audio::ChannelAgnosticTranscoder`) — s->d
- L40 _prototype_ `FTranscoder GetTranscoder(const FSoundfield& InFrom, const FComposite& InTo, const FParams&);` (scope `Audio::ChannelAgnosticTranscoder`) — s->c
- L43 _prototype_ `FTranscoder GetTranscoder(const FComposite& InFrom, const FComposite& InTo, const FParams&);` (scope `Audio::ChannelAgnosticTranscoder`) — Composite-to-X
- L44 _prototype_ `FTranscoder GetTranscoder(const FComposite& InFrom, const FDiscrete& InTo, const FParams&);` (scope `Audio::ChannelAgnosticTranscoder`) — c->d
- L45 _prototype_ `FTranscoder GetTranscoder(const FComposite& InFrom, const FSoundfield& InTo, const FParams&);` (scope `Audio::ChannelAgnosticTranscoder`) — c->s

### `Source/Runtime/AudioChannelAgnosticCore/Public/ChannelAgnostic/ChannelAgnosticType.h` (Public)


#### class `Audio::FChannelAgnosticType`  
`class FChannelAgnosticType`  
_L18-110_
- L38 _public prototype_ `FChannelAgnosticType(const FChannelAgnosticType& Other) = default;` — To be a Variable it *must* be copyable.
- L39 _public prototype_ `FChannelAgnosticType(FChannelAgnosticType&& Other) = default;`
- L40 _public prototype_ `FChannelAgnosticType& operator=(FChannelAgnosticType&& Other) = default;`
- L41 _public prototype_ `FChannelAgnosticType& operator=(const FChannelAgnosticType& Other) = default;`
- L45 _public function_ `int32 NumFrames() const`
- L49 _public function_ `int32 NumChannels() const`
- L53 _public function_ `TArrayView<const float> GetChannel(const int32 InChannelIndex) const`
- L62 _public function_ `TArrayView<float> GetChannel(const int32 InChannelIndex)`
- L75 _public function_ `const FChannelTypeFamily& GetType() const`
- L89 _public function_ `TArrayView<float> GetRawMultiMono()` — For fast raw DSP access to the buffer. @return View of entire multi-mono buffer.
- L99 _public function_ `TArrayView<const float> GetRawMultiMono() const` — For fast raw DSP access to the buffer. @return View of entire multi-mono buffer.
- L106 _private member_ `TScratchBuffer<float> Buffer;`
- L107 _private member_ `const FChannelTypeFamily* Type = nullptr;` — Keep this as pointer internally for easy of copying.
- L108 _private member_ `int32 NumFramesPrivate = 0;`
- L109 _private member_ `int32 NumChannelsPrivate = 0;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Audio`

### `Source/Runtime/AudioChannelAgnosticCore/Public/ChannelAgnostic/ChannelAgnosticTypeUtils.h` (Public)


#### class `Audio::FChannelAgnosticUtils`  
`class FChannelAgnosticUtils`  
_L14-37_

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`

### `Source/Runtime/AudioChannelAgnosticCore/Public/ScratchBuffer.h` (Public)


#### class `Audio::TScratchBuffer`  
`template <typename T> class UE_EXPERIMENTAL(5.8,"AudioChannelAgnosticCore is experimental and in flux") TScratchBuffer`  
_L10-136_
- L15 _public typedef_ `using ValueType = T;`
- L17 _public function_ `explicit TScratchBuffer(const int32 InNum, FSimpleAllocBase* InAllocator) : Allocator(InAllocator)`
- L23 _public function_ `TScratchBuffer(const TScratchBuffer& Other) : Allocator(Other.Allocator)`
- L29 _public function_ `TScratchBuffer(TScratchBuffer&& Other) : Allocator(Other.Allocator)`
- L35 _public function_ `TScratchBuffer& operator=(const TScratchBuffer& Other)`
- L57 _public function_ `TScratchBuffer& operator=(TScratchBuffer&& Other)` — Move operator.
- L74 _public function_ `~TScratchBuffer()`
- L79 _public function_ `bool IsValid() const`
- L84 _public function_ `int32 Num() const`
- L90 _public function_ `TArrayView<ValueType> GetView()`
- L96 _public function_ `TArrayView<const ValueType> GetView() const`
- L103 _private function_ `void Reset()`
- L109 _private function_ `void DoAllocation(const int32 InNum)`
- L122 _private function_ `void FreeAllocation()`
- L131 _private member_ `FSimpleAllocBase* Allocator = nullptr;`
- L132 _private member_ `TArrayView<ValueType> Allocation;`
- L133 _private member_ `int32 LifetimeToken = -1;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Audio`

### `Source/Runtime/AudioChannelAgnosticCore/Public/SimpleAlloc/SimpleAllocBase.h` (Public)


#### class `Audio::FSimpleAllocBase`  
`class FSimpleAllocBase`  
_L11-28_
- L25 _public function_ `virtual uint32 GetCurrentLifetime() const`
- L27 _public function_ `virtual void Reset()`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Audio`
- L30 _namespace_ `namespace SimpleAllocBasePrivate` (scope `Audio`)
- L33 _function_ `FORCEINLINE static uint32 GetDefaultSizeToAlignment(const uint32 InSize)` (scope `Audio::SimpleAllocBasePrivate`) — This is what's defined in MemoryBase, so follow it here.

### `Source/Runtime/AudioChannelAgnosticCore/Public/SimpleAlloc/SimpleHeapAllocator.h` (Public)


#### class `Audio::FSimpleHeapAllocator`  
`class FSimpleHeapAllocator final : public FSimpleAllocBase`  
_L9-26_
- inherits: `FSimpleAllocBase`
- L17 _public function_ `virtual void* Malloc(const SIZE_T InSizeBytes, const uint32 InAlignment=DEFAULT_ALIGNMENT) override`
- L22 _public function_ `virtual void Free(void* InPtr) override`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Audio`

### `Source/Runtime/AudioChannelAgnosticCore/Public/SimpleAlloc/SimpleLinearAllocator.h` (Public)


#### class `Audio::FSimpleLinearAllocator`  
`class FSimpleLinearAllocator : public FSimpleAllocBase`  
_L10-59_
- inherits: `FSimpleAllocBase`
- L16 _public function_ `explicit FSimpleLinearAllocator(const TArrayView<uint8> InPage) : Page(InPage)`
- L24 _public function_ `virtual void* Malloc(const SIZE_T InSizeBytes, const uint32 InAlignment = DEFAULT_ALIGNMENT) override`
- L41 _public function_ `virtual void Free(void*) override`
- L44 _public function_ `virtual uint32 GetCurrentLifetime() const override`
- L49 _public function_ `virtual void Reset() override`
- L56 _protected member_ `uint32 Top = 0;` — Top of all allocations, climbs upwards towards end of page.
- L57 _protected member_ `uint32 CurrentLifetime = 0;` — Each reset the lifetime is increased
- L58 _protected member_ `TArrayView<uint8> Page;` — One page for now.

#### class `Audio::FSimpleLinearAllocatorFromHeap`  
`class FSimpleLinearAllocatorFromHeap final : public FSimpleLinearAllocator`  
_L61-73_
- inherits: `FSimpleLinearAllocator`
- L65 _public function_ `explicit FSimpleLinearAllocatorFromHeap(const SIZE_T InPageSize, const uint32 InPageAlignment = DEFAULT_ALIGNMENT) : FSimpleLinearAllocator(MakeArrayView(static_cast<uint8*>(FMemory::Malloc(InPageSize,InPageAlignment)), IntCastChecked<int32>(InPageSize)))`
- L69 _public function_ `virtual ~FSimpleLinearAllocatorFromHeap() override`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`

### `Source/Runtime/AudioChannelAgnosticCore/Public/TypeFamily/ChannelTypeFamily.h` (Public)


#### enum `ESpeakerShortNames`  
`enum class ESpeakerShortNames : uint32`  
_L22-43_
- desc: A Comprehensive Short form Speaker enumeration
- L24 _public enumerator_ `FL = EAudioMixerChannel::FrontLeft` — Front Left
- L25 _public enumerator_ `FR = EAudioMixerChannel::FrontRight` — Front Right
- L26 _public enumerator_ `FC = EAudioMixerChannel::FrontCenter` — Front Center
- L27 _public enumerator_ `LFE = EAudioMixerChannel::LowFrequency` — Low-Frequency Effects (Subwoofer)
- L28 _public enumerator_ `FLC = EAudioMixerChannel::FrontLeftOfCenter` — Front Left Center
- L29 _public enumerator_ `FRC = EAudioMixerChannel::FrontRightOfCenter` — Front Right Center
- L30 _public enumerator_ `SL = EAudioMixerChannel::SideLeft` — Side Left
- L31 _public enumerator_ `SR = EAudioMixerChannel::SideRight` — Side Right
- L32 _public enumerator_ `BL = EAudioMixerChannel::BackLeft` — Back Left
- L33 _public enumerator_ `BR = EAudioMixerChannel::BackRight` — Back Right
- L34 _public enumerator_ `BC = EAudioMixerChannel::BackCenter` — Back Center
- L35 _public enumerator_ `TFL = EAudioMixerChannel::TopFrontLeft` — Top Front Left
- L36 _public enumerator_ `TFR = EAudioMixerChannel::TopFrontRight` — Top Front Right
- L37 _public enumerator_ `TBL = EAudioMixerChannel::TopBackLeft` — Top Back Left
- L38 _public enumerator_ `TBR = EAudioMixerChannel::TopBackRight` — Top Back Right
- L40 _public enumerator_ `NumChannels = EAudioMixerChannel::ChannelTypeCount`
- L41 _public enumerator_ `DefaultChannel = EAudioMixerChannel::DefaultChannel`
- L42 _public enumerator_ `Unknown = EAudioMixerChannel::Unknown`

#### class `Audio::IChannelTypeVisitor`  
`class IChannelTypeVisitor`  
_L75-85_
- L78 _public prototype_ `virtual ~IChannelTypeVisitor() = default;`

#### class `Audio::FChannelTypeFamily`  
`class FChannelTypeFamily : public FTypeFamily`  
_L88-222_
- inherits: `FTypeFamily`
- desc: Base type for all "channel" based types.
- L92 _public typedef_ `using Super = FTypeFamily;`
- L121 _public function_ `bool IsAbstract() const` — If this type can be instantiated or is just organisational. @return true if abstract, false otherwise
- L131 _public function_ `bool IsParentsDefault() const` — If this is marked as being the default on its parent @return true if true, false otherwise.
- L141 _public function_ `const FChannelTypeFamily* GetDefaultChild() const` — Returns the default child if one exists. Example. "Stereo" would return "Stereo_2_0" @return Pointer to type, null otherwise.
- L148 _public function_ `int32 NumChannels() const` — Num of channels @return >= 0
- L150 _public typedef_ `using IPanner = IDiscretePanner;`
- L159 _public function_ `virtual const IPanner* GetPanner(const FGetPannerParams& InParams = {}) const`
- L166 _public function_ `FName GetFamilyName() const` — Returns the family name (C++ type) of this ChannelType. This allows us to safely downcast (if necessary). @return The name of this type Family. (i.e. Discrete/Ambisoncs).
- L180 _public function_ `virtual TOptional<FChannelName> GetChannelName(const int32 InChannelIndex) const`
- L184 _public function_ `T* Cast()`
- L197 _public function_ `const T* Cast() const`
- L200 _public function_ `virtual void Accept(IChannelTypeVisitor& InVisitor) const`
- L211 _protected function_ `void SetNumChannels(const int32 InNumChannels)`
- L217 _private member_ `bool bIsAbstract = false;`
- L218 _private member_ `bool bIsParentsDefault = false;`
- L219 _private member_ `const FChannelTypeFamily* DefaultChild = nullptr;`
- L220 _private member_ `int32 NumChannelsPrivate = 0;`
- L221 _private member_ `FName FamilyType;`

#### struct `Audio::FChannelTypeFamily::FGetPannerParams`  
`struct FGetPannerParams`  
_L152-157_

#### struct `Audio::FChannelTypeFamily::FChannelName`  
`struct FChannelName`  
_L173-177_
- desc: Returns the name of the channel. For discrete this would be what speaker its mapped to etc. @param InChannelIndex Index of channel >= 0 and < NumChannels. @return Optional containing the Channel name and friendly name.
- L175 _public member_ `FName Name;`
- L176 _public member_ `FString FriendlyName;`

#### class `Audio::FDiscreteChannelTypeFamily`  
`class FDiscreteChannelTypeFamily : public FChannelTypeFamily`  
_L224-336_
- inherits: `FChannelTypeFamily`
- L228 _public typedef_ `using Super = FChannelTypeFamily;`
- L238 _public function_ `static FName GetFamilyTypeName()`
- L256 _public function_ `bool HasHeightChannels() const` — Returns true if this format defines any height data. @return true if heights are found.
- L267 _public function_ `int32 FindSpeakerIndex(const ESpeakerShortNames InSpeaker) const` — Find the index in the list of Channels for speaker. @param InSpeaker @return >= 0 (index) INDEX_NONE (failed to find).
- L274 _public function_ `int32 FindSpeakerIndex(const FName InSpeaker) const`
- L286 _public function_ `bool HasSpeaker(const ESpeakerShortNames InSpeaker) const` — Checks if a paticular speaker is present in the Channels for this Format. @param InSpeaker @return true (exists), false otherwise.
- L306 _public function_ `const TArray<FSpeaker>& GetSpeakerOrder() const` — Get the order of the speakers defined on this discrete format. @return Array of speakers in order.
- L309 _public function_ `TArray<FName> GetSpeakerIds() const`
- L317 _public function_ `virtual void Accept(IChannelTypeVisitor& InVisitor) const override`
- L325 _public function_ `virtual const IPanner* GetPanner(const FGetPannerParams& InParams ={}) const override`
- L333 _protected prototype_ `static TUniquePtr<IDiscretePanner> MakePanner(const TArray<FSpeaker>& Order);`
- L334 _protected member_ `TArray<FSpeaker> Order;`
- L335 _protected member_ `TUniquePtr<IPanner> Panner;` — Just one for now.

#### struct `Audio::FDiscreteChannelTypeFamily::FSpeaker`  
`struct FSpeaker`  
_L230-236_
- L232 _public member_ `FName ID;` — ID of speaker.
- L233 _public member_ `float AzimuthDegrees = 0.f;` — -180 (left), 0 (front), 180 (right).
- L234 _public member_ `float ElevationDegrees = 0.f;` — -180 (down), 0 (ground), 180 (up).
- L235 _public member_ `bool bIsSpatialized = true;` — If false, azimuth+elevation are ignored.

#### class `Audio::FSoundfieldChannelTypeFamily`  
`class FSoundfieldChannelTypeFamily : public FChannelTypeFamily`  
_L340-377_
- inherits: `FChannelTypeFamily`
- desc: Soundfield
- L344 _public typedef_ `using Super = FChannelTypeFamily;`
- L348 _public function_ `static FName GetFamilyTypeName()`
- L358 _public function_ `explicit FSoundfieldChannelTypeFamily(const FName& InUniqueName, const int32 InOrder, FChannelTypeFamily* InParentType, const FString& InFriendlyName, const bool bIsParentsDefault, const bool InbIsAbstract) : Super(InUniqueName, GetFamilyTypeName(), OrderToNumChannels(InOrder), InParentType, InFriendlyName, bIsParentsDefault, InbIsAbstract) , Order(InOrder)`
- L364 _public function_ `int32 GetAmbisonicsOrder() const`
- L370 _public function_ `virtual void Accept(IChannelTypeVisitor& InVisitor) const override`
- L376 _private member_ `int32 Order = 0;`

#### class `Audio::FCompositeChannelTypeFamily`  
`class FCompositeChannelTypeFamily : public FChannelTypeFamily`  
_L381-432_
- inherits: `FChannelTypeFamily`
- L386 _public typedef_ `using Super = FChannelTypeFamily;`
- L390 _public function_ `static FName GetFamilyTypeName()`
- L396 _public function_ `explicit FCompositeChannelTypeFamily(const FName& InUniqueName, FChannelTypeFamily* InParentType, const FString& InFriendlyName, const bool bIsParentsDefault) : Super(InUniqueName, GetFamilyTypeName(), 1, InParentType, InFriendlyName, bIsParentsDefault, false)`
- L402 _public function_ `int32 NumTypes() const`
- L415 _public function_ `const FContainedType* GetType(const int32 InTypeIndex) const`
- L425 _public function_ `virtual void Accept(IChannelTypeVisitor& InVisitor) const override`
- L431 _protected member_ `TArray<FContainedType> Types;`

#### struct `Audio::FCompositeChannelTypeFamily::FContainedType`  
`struct FContainedType`  
_L407-412_
- L409 _public member_ `FName Type;` — Type name of embedded format.
- L410 _public member_ `uint32 Offset = 0;` — Index in channels.
- L411 _public member_ `uint32 Count = 0;` — Count in channels.

#### class `Audio::IChannelTypeRegistry`  
`class IChannelTypeRegistry : public ITypeFamilyRegistry`  
_L438-494_
- inherits: `ITypeFamilyRegistry`
- desc: Channel type registry.
- L443 _public function_ `const FChannelTypeFamily* FindChannel(const FName InName) const`
- L448 _public function_ `FChannelTypeFamily* FindChannel(const FName InName)`
- L464 _public function_ `const FChannelTypeFamily* FindConcreteChannel(const FName InName) const` — Find the first concrete (non-abstract, > 0 channels) channel. (e.g. Stereo -> 'Stereo_2_0') Each Abstract type should have a designated default child. @param InName Name of format. @return Pointer to type (on success), nullptr on failure
- L477 _public function_ `const FChannelTypeFamily& FindConcreteChannelChecked(const FName InName) const`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Audio`
- L46 _macro_ `#define FOREACH_ENUM_ESPEAKERSHORTNAMES(op) \` — Pasted from UHT generated.h, but we can't use because of AudioUnitTests.
- L63 _prototype_ `const TCHAR* LexToString(const ESpeakerShortNames InSpeaker);`
- L64 _prototype_ `FName LexToName(const ESpeakerShortNames InSpeaker);`
- L65 _prototype_ `TOptional<ESpeakerShortNames> NameToShortSpeakerName(const FName InName);`
- L66 _prototype_ `uint32 ShortNamesToChannelMask(const TArray<ESpeakerShortNames>& InChannels);`
- L68 _namespace_ `namespace Audio`
- L258 _function_ `return Order.FindByPredicate([](const FSpeaker& i) -> bool { return !FMath::IsNearlyZero(i.ElevationDegrees); }) != nullptr;` (scope `Audio::FDiscreteChannelTypeFamily::HasHeightChannels`)
- L270 _function_ `return Order.IndexOfByPredicate([SpeakerName](const FSpeaker& i) -> bool { return SpeakerName == i.ID; });` (scope `Audio::FDiscreteChannelTypeFamily::FindSpeakerIndex`)
- L276 _function_ `return Order.IndexOfByPredicate([InSpeaker](const FSpeaker& i) -> bool { return InSpeaker == i.ID; });` (scope `Audio::FDiscreteChannelTypeFamily::FindSpeakerIndex`)
- L312 _function_ `Algo::Transform(Order, Ids, [](const FSpeaker& i) -> FName { return i.ID; });` (scope `Audio::FDiscreteChannelTypeFamily::GetSpeakerIds`)
- L498 _prototype_ `IChannelTypeRegistry& GetChannelRegistry();` (scope `Audio`)

### `Source/Runtime/AudioChannelAgnosticCore/Public/TypeFamily/TypeFamily.h` (Public)


#### class `Audio::FTypeFamily`  
`class FTypeFamily`  
_L11-62_
- L15 _private member_ `FName Name;`
- L16 _private member_ `const FTypeFamily* Parent = nullptr;`
- L17 _private member_ `FString FriendlyName;`
- L21 _private function_ `const FTypeFamily* FindAncestor(Predicate Pred) const`
- L34 _public function_ `FTypeFamily(const FName InName, const FTypeFamily* InParent, const FString& InFriendlyName) : Name(InName) , Parent(InParent) , FriendlyName(InFriendlyName)`
- L40 _public prototype_ `virtual ~FTypeFamily() = default;`
- L43 _public function_ `bool IsA(const FTypeFamily* Other) const`
- L50 _public function_ `bool IsA(const FName& Other) const`
- L57 _public function_ `const FName& GetName() const`
- L59 _public function_ `const FString& GetFriendlyName() const`
- L61 _public function_ `const FTypeFamily* GetParent() const`

#### class `Audio::ITypeFamilyRegistry`  
`class ITypeFamilyRegistry`  
_L65-89_
- desc: Simple type registry.
- L79 _public function_ `const T* Find(const FName& InUniqueName) const`

#### struct `Audio::TFamilyRegistry`  
`template<typename T> struct TFamilyRegistry`  
_L92-115_
- desc: Convenience template so we don't have to specialize each Find.
- L94 _public member_ `ITypeFamilyRegistry& FamilyRegistry;`
- L96 _public function_ `explicit TFamilyRegistry(ITypeFamilyRegistry& InFamilyRegistry) : FamilyRegistry(InFamilyRegistry)`
- L100 _public function_ `const T* Find(const FName& InName) const`
- L107 _public function_ `const T& FindChecked(const FName& InName) const`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Audio`
- L46 _function_ `return nullptr != FindAncestor([Other](const FTypeFamily* i) -> bool { return i==Other; });` (scope `Audio::FTypeFamily::IsA`)
- L53 _function_ `return nullptr != FindAncestor([&](const FTypeFamily* i) -> bool { return i->Name==Other; });` (scope `Audio::FTypeFamily::IsA`)
