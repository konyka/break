# Plugins / MetasoundExperimentalEngineRuntime

- module root: `Plugins/Experimental/MetasoundExperimental/Source/MetasoundExperimentalEngineRuntime`
- headers: 8; symbols: 135
- symbol kinds: class=9, enum=7, enumerator=19, function=20, macro=2, member=34, namespace=6, prototype=32, struct=6
- PrivateDependencyModuleNames: AudioChannelAgnosticCore, AudioExtensions, Core, CoreUObject, Engine, MetasoundEngine, MetasoundExperimentalRuntime, MetasoundFrontend, MetasoundGraphCore, MetasoundStandardNodes, SignalProcessing
- PublicDependencyModuleNames: AudioExperimentalRuntime, Core, CoreUObject, MetasoundExperimentalRuntime, MetasoundFrontend, MetasoundGraphCore

### `Plugins/Experimental/MetasoundExperimental/Source/MetasoundExperimentalEngineRuntime/Private/MetasoundExperimentalEngineRuntimeModule.h` (Private)


#### class `FMetasoundExperimentalEngineRuntimeModule`  
`class FMetasoundExperimentalEngineRuntimeModule : public IModuleInterface`  
_L8-17_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;`
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/MetasoundExperimental/Source/MetasoundExperimentalEngineRuntime/Private/MetasoundFadeNode.h` (Private)


#### enum `EMetaSoundFadeOutputType`  
`enum EMetaSoundFadeOutputType : uint8`  
_L15-19_
- reflection: `UENUM()`
- L17 _public enumerator_ `FloatType UMETA(DisplayName = "Float")`
- L18 _public enumerator_ `AudioBufferType UMETA(DisplayName = "Audio")`

#### struct `FMetaSoundFadeNodeConfiguration`  
`struct FMetaSoundFadeNodeConfiguration : public FMetaSoundFrontendNodeConfiguration`  
_L22-37_
- reflection: `USTRUCT()`
- inherits: `FMetaSoundFrontendNodeConfiguration`
- L26 _public prototype_ `FMetaSoundFadeNodeConfiguration();`
- L30 _public member_ `TEnumAsByte<EMetaSoundFadeOutputType> OutputType = EMetaSoundFadeOutputType::FloatType;` — `UPROPERTY(EditAnywhere, Category = General)` — Output Type for Fade Value
- L33 _public prototype_ `virtual TInstancedStruct<FMetasoundFrontendClassInterface> OverrideDefaultInterface(const FMetasoundFrontendClass& InNodeClass) const;` — Get the current interface for the class based upon the node extension
- L36 _public prototype_ `virtual TSharedPtr<const Metasound::IOperatorData> GetOperatorData() const override;` — Pass data down to the operator.

### `Plugins/Experimental/MetasoundExperimental/Source/MetasoundExperimentalEngineRuntime/Public/CatAudioProxyView.h` (Public)


#### class `Audio::TCatProxyView`  
`template<typename TType, typename TData> class TCatProxyView : public IProxyData, public TSharedFromThis<TCatProxyView<TType, TData>>`  
_L59-172_
- inherits: `IProxyData,TSharedFromThis<TCatProxyView<TType,TData>>`
- desc: Thread-safe, lock-free "view" over proxy data published from the game thread and consumed from the audio thread. Modeled as a one-directional linked list: the head is the "latest" version and older nodes hold an atomic pointer to their successor so stale references can always resolve to the current head via GetLatest(). Pushing a new version is a compare-exchange on the tail's NextPtr, after which NextSharedPtr is assigned (the caller's shared-ref keeps the new head alive during the transition). Typical usage: struct FMyData { ... }; class FMyProxy : public Audio::TCatProxyView<FMyProxy, FMyData> { public: IMPL_AUDIOPROXY_CLASS(FMyProxy); }; // Game thread: create + publish. Proxy = FMyProxy::Create(MoveTemp(InitialData)); Proxy = Proxy->New(MoveTemp(UpdatedData)); // Audio thread: const TSharedRef<const FMyProxy> Latest = Proxy->GetLatest(); Trivial scalar updates can be applied directly on GetData() without pushing a new node; only structural changes (resizing arrays, etc.) require New(). NOTE: scratch-duplicated into MetasoundExperimentalEngineRuntime for the CAT Wave Player 2.0 move. MetasoundPolyphonyInternal retains its own copy pending consolidation (see cat-wave-player-move-spec.md §0). Threading contract: - New() must be called from a single thread. In practice is called from the game thread only. Callers must hold a shared ref to the head they are publishing from for the duration of the call. - GetLatest() / IsLatest() / GetData() are safe to call concurrently from 
- L62 _protected member_ `static constexpr bool bWasAudioProxyClassImplemented = false;`
- L66 _protected member_ `std::atomic<TCatProxyView*> NextPtr = nullptr;`
- L67 _protected member_ `TSharedPtr<TCatProxyView> NextSharedPtr = nullptr;`
- L69 _protected member_ `TData Data;`
- L72 _public function_ `TCatProxyView(EPrivateToken) : IProxyData(TType::GetAudioProxyTypeName())`
- L78 _public function_ `TCatProxyView(EPrivateToken, TData&& InData) : IProxyData(TType::GetAudioProxyTypeName()) , Data(MoveTemp(InData))`
- L85 _public function_ `virtual ~TCatProxyView() override`
- L101 _public function_ `virtual void* QueryInterface(const FName InterfaceId) override` — Create() instantiates the base TCatProxyView (not TType) and static-casts the shared ref to TType*. The actual runtime object is therefore TCatProxyView, and any QueryInterface override declared on TType is never reached via the vtable. We answer TType::GetAudioProxyTypeName() here so CheckTypeCast<TType>() and GetAs<TType>() both work against the real object.
- L111 _public function_ `static TSharedRef<TType> Create(TData&& InData)` — Create a fresh proxy reference; takes ownership of InData.
- L132 _public function_ `TSharedRef<TType> New(TData&& InData)` — Publish a new data version; returns the new head. The caller should replace its cached shared ref with the return value so subsequent New() calls append to the linear chain. Memory ordering: we assign NextSharedPtr BEFORE the release-store that publishes NewPtr via CAS. A reader which acquire-loads a non-null NextPtr is then guaranteed to observe a fully-constructed NextSharedPtr, which keeps the chain's lifetime intact on the reader side. Pairs with the acquire load in GetLatest() / IsLatest(). Single-writer contract: the audio proxy chain is published from the game thread only. Concurrent publishers are not supported (NextSharedPtr is a non-atomic TSharedPtr). Readers may be on any thread, including the audio render thread.
- L155 _public function_ `bool IsLatest() const`
- L160 _public function_ `TSharedRef<const TType> GetLatest() const`
- L170 _public function_ `const TData& GetData() const`
- L171 _public function_ `TData& GetData()`

#### enum `Audio::TCatProxyView::EPrivateToken`  
`enum EPrivateToken`  
_L64-64_

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Audio`

### `Plugins/Experimental/MetasoundExperimental/Source/MetasoundExperimentalEngineRuntime/Public/CatSoundWaveContainer.h` (Public)


#### enum `ECatSoundWaveContainerType`  
`enum class ECatSoundWaveContainerType : uint8`  
_L25-29_
- reflection: `UENUM(BlueprintType)`
- L27 _public enumerator_ `Standard`
- L28 _public enumerator_ `Random`

#### struct `FCatSoundWaveContainerEntry`  
`struct FCatSoundWaveContainerEntry`  
_L32-48_
- reflection: `USTRUCT(BlueprintType)`
- L36 _public prototype_ `FCatSoundWaveContainerEntry() = default;`
- L38 _public function_ `explicit FCatSoundWaveContainerEntry(USoundWave* InSoundWave) : SoundWave(InSoundWave)`
- L44 _public member_ `TObjectPtr<USoundWave> SoundWave;` — `UPROPERTY(EditAnywhere, Category = "Entry", meta = (ExactClass = true, AllowedClasses = "/Script/Engine.SoundWave"))`
- L47 _public member_ `float Weight = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Entry")`

#### class `UCatSoundWaveContainer`  
`class UCatSoundWaveContainer : public UObject, public IAudioProxyDataFactory`  
_L53-79_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, meta = (DisplayName = "Audio Sound Wave Container"))`
- inherits: `UObject,IAudioProxyDataFactory`
- desc: Named UCatSoundWaveContainer (not USoundWaveContainer) to avoid a UClass short-name collision with MetasoundPolyphonyInternal::USoundWaveContainer.
- L59 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedChainEvent) override;`
- L62 _public prototype_ `virtual TSharedPtr<Audio::IProxyData> CreateProxyData(const Audio::FProxyDataInitParams& InitParams) override;`
- L69 _public prototype_ `void RebuildProxy();` — Publish the current container state onto the proxy chain. Callable from code constructing a container in-memory (e.g. the test harness) so audio-thread consumers see the contents without waiting for an editor property change.
- L72 _public member_ `ECatSoundWaveContainerType Type = ECatSoundWaveContainerType::Standard;` — `UPROPERTY(EditAnywhere, Category = Defaults)`
- L75 _public member_ `TArray<FCatSoundWaveContainerEntry> Entries;` — `UPROPERTY(EditAnywhere, Category = Sounds)`
- L78 _private member_ `TSharedPtr<FCatSoundWaveContainerProxy> Proxy;`

#### class `FCatSoundWaveContainerData`  
`class FCatSoundWaveContainerData : public Audio::ISoundWaveContainer`  
_L81-108_
- inherits: `Audio::ISoundWaveContainer`
- L84 _public prototype_ `FCatSoundWaveContainerData() = default;`
- L85 _public prototype_ `FCatSoundWaveContainerData(const FCatSoundWaveContainerData& Other) = default;`
- L86 _public prototype_ `FCatSoundWaveContainerData(FCatSoundWaveContainerData&& Other) = default;`
- L88 _public prototype_ `explicit FCatSoundWaveContainerData(const Audio::FProxyDataInitParams& InInitParams);`
- L89 _public prototype_ `FCatSoundWaveContainerData(const Audio::FProxyDataInitParams& InInitParams, const UCatSoundWaveContainer& SoundWaveContainer);`
- L91 _public prototype_ `void Update(const UCatSoundWaveContainer& SoundWaveContainer);`
- L103 _public prototype_ `virtual TArray<FSoundWaveProxyPtr> GetContainedWaveProxies() const override;` — Audio::ISoundWaveContainer.
- L105 _public member_ `ECatSoundWaveContainerType Type = ECatSoundWaveContainerType::Standard;`
- L106 _public member_ `TArray<FEntry> Entries;`
- L107 _public member_ `Audio::FProxyDataInitParams InitParams;`

#### struct `FCatSoundWaveContainerData::FEntry`  
`struct FEntry`  
_L93-100_
- L95 _public prototype_ `FEntry() = default;`
- L96 _public prototype_ `FEntry(const Audio::FProxyDataInitParams& InInitParams, const FCatSoundWaveContainerEntry& Entry);`
- L98 _public member_ `TSharedPtr<FSoundWaveProxy> SoundWave;`
- L99 _public member_ `float Weight = 1.0f;`

#### class `FCatSoundWaveContainerProxy`  
`class FCatSoundWaveContainerProxy : public Audio::TCatProxyView<FCatSoundWaveContainerProxy, FCatSoundWaveContainerData>`  
_L112-142_
- inherits: `Audio::TCatProxyView<FCatSoundWaveContainerProxy,FCatSoundWaveContainerData>`
- desc: QueryInterface is hand-rolled (not IMPL_AUDIOPROXY_CLASS) so we can also answer Audio::ISoundWaveContainer by forwarding to the Data field.
- L119 _public function_ `static FName GetAudioProxyTypeName()`
- L124 _public function_ `static FName GetInterfaceId()`
- L125 _public member_ `static constexpr bool bWasAudioProxyClassImplemented = true;`
- L127 _public function_ `virtual void* QueryInterface(const FName InInterfaceId) override`

#### Free symbols / members of external scopes

- L22 _macro_ `#define UE_API METASOUNDEXPERIMENTALENGINERUNTIME_API`

### `Plugins/Experimental/MetasoundExperimental/Source/MetasoundExperimentalEngineRuntime/Public/CatSoundWaveContainerAsset.h` (Public)


#### class `MetasoundCatExperimental::FSoundWaveContainerAsset`  
`class FSoundWaveContainerAsset`  
_L21-46_
- desc: MetaSound data-type wrapper around FCatSoundWaveContainerProxy. Acts as a read-side handle that the node operator holds by value on the audio thread; GetLatest() walks the proxy's linked list and caches the head so subsequent calls are cheap.
- L24 _public prototype_ `FSoundWaveContainerAsset() = default;`
- L25 _public prototype_ `FSoundWaveContainerAsset(const FSoundWaveContainerAsset&) = default;`
- L26 _public prototype_ `FSoundWaveContainerAsset& operator=(const FSoundWaveContainerAsset&) = default;`
- L28 _public prototype_ `explicit FSoundWaveContainerAsset(const TSharedPtr<Audio::IProxyData>& InData);`
- L31 _public prototype_ `TSharedPtr<const FCatSoundWaveContainerProxy> GetLatest() const;` — Walk to the latest-published proxy and cache it; safe to call every block.
- L33 _public function_ `void SetProxy(TSharedPtr<const FCatSoundWaveContainerProxy> InProxy)`
- L38 _public function_ `TSharedPtr<const FCatSoundWaveContainerProxy> GetProxy() const`
- L40 _public function_ `bool IsValid() const`
- L42 _public function_ `const FCatSoundWaveContainerProxy* operator->() const`
- L45 _private member_ `mutable TSharedPtr<const FCatSoundWaveContainerProxy> Proxy;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METASOUNDEXPERIMENTALENGINERUNTIME_API`
- L14 _namespace_ `namespace MetasoundCatExperimental`

### `Plugins/Experimental/MetasoundExperimental/Source/MetasoundExperimentalEngineRuntime/Public/MetasoundCatWavePlayerNode.h` (Public)


#### enum `ECatWavePlayerFormatChooser`  
`enum class ECatWavePlayerFormatChooser : uint8`  
_L25-35_
- reflection: `UENUM()`
- desc: Output-format selection mode for the Audio Wave Player. W10: scoped to this node (not the engine-wide enum) by intent for the duration of the experimental phase. The cross-node enum EMetasoundChannelAgnosticNodeFormatChooser is missing a "SourceAuto" variant (main spec §4 Open #7); localizing here avoids touching MetasoundFrontend from an experimental-plugin module and keeps this node's config self-contained. When the engine-wide enum grows a matching variant, the Wave Player config should adopt it directly.
- L28 _public enumerator_ `Auto` — Derive the output format from the contents of the attached SoundWaveContainer (largest channel count among entries, clamped to MVP formats).
- L31 _public enumerator_ `SourceAuto` — Inherit the format from the enclosing UMetaSoundSource. Default.
- L34 _public enumerator_ `Custom` — Pin a specific format via CustomFormat. Must be one of the MVP formats (Mono / Stereo / Quad / 5.1 / 7.1).

#### enum `ECatWavePlayerPlaybackType`  
`enum class ECatWavePlayerPlaybackType : uint8`  
_L39-45_
- reflection: `UENUM()`
- desc: How the container is stepped through.
- L42 _public enumerator_ `Index` — Each Play trigger plays the entry at the supplied Index input.
- L44 _public enumerator_ `Sequence` — Each Play trigger advances through the container in sequence.

#### enum `ECatWavePlayerPlaybackMode`  
`enum class ECatWavePlayerPlaybackMode : uint8`  
_L49-55_
- reflection: `UENUM()`
- desc: How playback chooses entries (index-driven vs weighted-random).
- L52 _public enumerator_ `Standard` — Deterministic ordering: Index or Sequence input controls selection.
- L54 _public enumerator_ `Random` — Weighted random: entry weights drive selection.

#### struct `FMetasoundCatWavePlayerNodeConfiguration`  
`struct FMetasoundCatWavePlayerNodeConfiguration : public FMetaSoundFrontendNodeConfiguration`  
_L64-90_
- reflection: `USTRUCT()`
- inherits: `FMetaSoundFrontendNodeConfiguration`
- desc: Configuration struct for the CAT Wave Player. See cat-wave-player-move-spec.md §3.2. Drives both OverrideDefaultInterface (so the node UI reshapes to match the mode) and GetOperatorData (so the operator knows its static configuration without round-tripping through the vertex interface).
- L68 _public prototype_ `FMetasoundCatWavePlayerNodeConfiguration();`
- L72 _public member_ `int32 MaxVoices = 2;` — `UPROPERTY(EditAnywhere, Category = General, meta = (ClampMin = "1", UIMin = "1"))` — Maximum number of simultaneous voices. Minimum enforced to 1.
- L76 _public member_ `ECatWavePlayerFormatChooser Format = ECatWavePlayerFormatChooser::SourceAuto;` — `UPROPERTY(EditAnywhere, Category = General)` — Output-format derivation mode. See ECatWavePlayerFormatChooser.
- L80 _public member_ `FName CustomFormat = TEXT("Cat` — `UPROPERTY(EditAnywhere, Category = General, meta = (EditCondition = "Format == ECatWavePlayerFormatChooser::Custom", EditConditionHides))` — Used when Format == Custom. Must be one of the MVP-registered formats (main spec §4 Confirmed #14).
- L83 _public member_ `ECatWavePlayerPlaybackType PlaybackType = ECatWavePlayerPlaybackType::Index;` — `UPROPERTY(EditAnywhere, Category = General)`
- L86 _public member_ `ECatWavePlayerPlaybackMode PlaybackMode = ECatWavePlayerPlaybackMode::Standard;` — `UPROPERTY(EditAnywhere, Category = General)`
- L88 _public prototype_ `virtual TInstancedStruct<FMetasoundFrontendClassInterface> OverrideDefaultInterface(const FMetasoundFrontendClass& InNodeClass) const override;`
- L89 _public prototype_ `virtual TSharedPtr<const Metasound::IOperatorData> GetOperatorData() const override;`

### `Plugins/Experimental/MetasoundExperimental/Source/MetasoundExperimentalEngineRuntime/Public/MetasoundGranulatorNode.h` (Public)


#### class `UMetaSoundGranulatorNodeOptionsHelper`  
`class UMetaSoundGranulatorNodeOptionsHelper : public UObject`  
_L13-19_
- reflection: `UCLASS()`
- inherits: `UObject`
- L18 _private prototype_ `static TArray<FPropertyTextFName> GetSoundFileFormatChannelOptions();` — `UFUNCTION()`

#### enum `EGranularEnvelope`  
`enum class EGranularEnvelope : uint8`  
_L23-33_
- reflection: `UENUM()`
- L25 _public enumerator_ `Gaussian = 0`
- L26 _public enumerator_ `Triangle`
- L27 _public enumerator_ `DownwardTriangle`
- L28 _public enumerator_ `UpwardTriangle`
- L29 _public enumerator_ `ExponentialDecay`
- L30 _public enumerator_ `ExponentialAttack`
- L31 _public enumerator_ `Hann`
- L32 _public enumerator_ `Count UMETA(Hidden)`

#### class `Metasound::GranulatorPrivate::FGranulatorOperatorData`  
`class FGranulatorOperatorData final : public TOperatorData<FGranulatorOperatorData>`  
_L37-50_
- inherits: `TOperatorData<FGranulatorOperatorData>`
- L40 _public member_ `static const FLazyName OperatorDataTypeName;`
- L42 _public function_ `explicit FGranulatorOperatorData(const FName& InOutputAudioTypeName, const EGranularEnvelope& InGranularEnvelope) : OutputAudioTypeName(InOutputAudioTypeName) , GranularEnvelope(InGranularEnvelope)`
- L48 _public member_ `FName OutputAudioTypeName;`
- L49 _public member_ `EGranularEnvelope GranularEnvelope;`

#### struct `FMetaSoundGranulatorNodeConfiguration`  
`struct FMetaSoundGranulatorNodeConfiguration : public FMetaSoundFrontendNodeConfiguration`  
_L54-76_
- reflection: `USTRUCT()`
- inherits: `FMetaSoundFrontendNodeConfiguration`
- L58 _public prototype_ `FMetaSoundGranulatorNodeConfiguration();`
- L62 _public member_ `FName OutputAudioTypeName = TEXT("Cat` — `UPROPERTY(EditAnywhere, Category = General, meta = (GetOptions="MetaSoundGranulatorNodeOptionsHelper.GetSoundFileFormatChannelOptions"))` — What the CAT output type is. Only azimuthal discrete channel types supported.
- L66 _public member_ `EGranularEnvelope GranularEnvelope = EGranularEnvelope::Hann;` — `UPROPERTY(EditAnywhere, Category = General)` — What grain envelope to use for the granulator
- L69 _public prototype_ `virtual TInstancedStruct<FMetasoundFrontendClassInterface> OverrideDefaultInterface(const FMetasoundFrontendClass& InNodeClass) const override;` — Get the current interface for the class based upon the node extension
- L72 _public prototype_ `virtual TSharedPtr<const Metasound::IOperatorData> GetOperatorData() const override;` — Pass data down to the operator.
- L75 _private member_ `mutable TSharedPtr<Metasound::GranulatorPrivate::FGranulatorOperatorData> OperatorData;`

#### Free symbols / members of external scopes

- L35 _namespace_ `namespace Metasound`
- L35 _namespace_ `namespace GranulatorPrivate` (scope `Metasound`)

### `Plugins/Experimental/MetasoundExperimental/Source/MetasoundExperimentalEngineRuntime/Public/MetasoundMappingFunctionNode.h` (Public)


#### class `Metasound::Experimental::FMappingFunctionNodeOperatorData`  
`class FMappingFunctionNodeOperatorData : public TOperatorData<FMappingFunctionNodeOperatorData>`  
_L14-27_
- inherits: `TOperatorData<FMappingFunctionNodeOperatorData>`
- L17 _public member_ `static const FLazyName OperatorDataTypeName;`
- L19 _public function_ `FMappingFunctionNodeOperatorData(const FRuntimeFloatCurve& InMappingFunction, bool bInWrapInputs) : MappingFunction(InMappingFunction) , bWrapInputs(bInWrapInputs)`
- L25 _public member_ `FRuntimeFloatCurve MappingFunction;`
- L26 _public member_ `bool bWrapInputs = false;`

#### struct `FMetaSoundMappingFunctionNodeConfiguration`  
`struct FMetaSoundMappingFunctionNodeConfiguration : public FMetaSoundFrontendNodeConfiguration`  
_L31-49_
- reflection: `USTRUCT()`
- inherits: `FMetaSoundFrontendNodeConfiguration`
- L35 _public prototype_ `FMetaSoundMappingFunctionNodeConfiguration();`
- L39 _public member_ `bool bWrapInputs = false;` — `UPROPERTY(EditAnywhere, Category = General)` — Whether or not to wrap the input values to remain in the defined input range. Otherwise, inputs are clamped.
- L43 _public member_ `FRuntimeFloatCurve MappingFunction;` — `UPROPERTY(EditAnywhere, Category = General)` — Mapping function (curve) to map inputs to outputs
- L45 _public prototype_ `TSharedPtr<const Metasound::IOperatorData> GetOperatorData() const override;`
- L48 _private member_ `TSharedPtr<Metasound::Experimental::FMappingFunctionNodeOperatorData> OperatorData;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Metasound`
- L12 _namespace_ `namespace Experimental` (scope `Metasound`)
