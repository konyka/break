# Plugins / SharedMemoryMedia

- module root: `Plugins/Runtime/nDisplay/Source/SharedMemoryMedia`
- headers: 13; symbols: 237
- symbol kinds: class=11, delegate=1, enum=1, enumerator=3, function=52, member=73, namespace=5, prototype=75, struct=7, typedef=2, variable=7
- PrivateDependencyModuleNames: Core, CoreUObject, D3D12RHI, Engine, Media, MediaAssets, RHI, RenderCore, Renderer
- PublicDependencyModuleNames: MediaIOCore

### `Plugins/Runtime/nDisplay/Source/SharedMemoryMedia/Private/Platforms/Windows/SharedMemoryMediaPlatformWindowsD3D12.h` (Private)


#### class `FSharedMemoryMediaPlatformWindowsD3D12`  
`class FSharedMemoryMediaPlatformWindowsD3D12 : public FSharedMemoryMediaPlatform`  
_L17-46_
- inherits: `FSharedMemoryMediaPlatform`
- desc: D3D12 RHI specific implementation of FSharedMemoryMediaPlatform.
- L22 _private member_ `ID3D12Resource* CommittedResource[UE::SharedMemoryMedia::SenderNumBuffers]{ 0 };` — Pointer to the D3D12 shared memory heap.
- L25 _private member_ `HANDLE SharedHandle[UE::SharedMemoryMedia::SenderNumBuffers]{ 0 };` — Handles to the shared handles of the cross gpu resources
- L28 _private member_ `static bool bRegistered;` — Dummy bool to get the registration call made
- L31 _private prototype_ `static TSharedPtr<FSharedMemoryMediaPlatform> CreateInstance();` — Factory function to create this rhi platform instance. It is registed with and called by FSharedMemoryMediaPlatform
- L34 _private prototype_ `static const FString GetD3D12ComErrorDescription(HRESULT Hresult);` — Convenience function to stringify an HRESULT
- L39 _public prototype_ `virtual FTextureRHIRef CreateSharedTexture(EPixelFormat Format, bool bSrgb, int32 Width, int32 Height, const FGuid& Guid, uint32 BufferIdx, bool bCrossGpu) override;`
- L40 _public prototype_ `virtual void ReleaseSharedTexture(uint32 BufferIdx) override;`
- L41 _public prototype_ `virtual FTextureRHIRef OpenSharedTextureByGuid(const FGuid& Guid, FSharedMemoryMediaTextureDescription& OutTextureDescription) override;`
- L44 _public prototype_ `FSharedMemoryMediaPlatformWindowsD3D12();`
- L45 _public prototype_ `virtual ~FSharedMemoryMediaPlatformWindowsD3D12();`

### `Plugins/Runtime/nDisplay/Source/SharedMemoryMedia/Private/SharedMemoryMediaModule.h` (Private)


#### Free symbols / members of external scopes

- L6 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSharedMemoryMedia, Log, All);`
- L6 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSharedMemoryMedia, Log, All);`

### `Plugins/Runtime/nDisplay/Source/SharedMemoryMedia/Private/SharedMemoryMediaPlatform.h` (Private)


#### class `FSharedMemoryMediaPlatform`  
`class FSharedMemoryMediaPlatform`  
_L13-32_
- desc: This is the interface to the platform specific functions needed by shared memory media. It is mostly about the platform specific implementation of cross gpu textures.
- L19 _public function_ `virtual FTextureRHIRef CreateSharedTexture(EPixelFormat Format, bool bSrgb, int32 Width, int32 Height, const FGuid& Guid, uint32 BufferIdx, bool bCrossGpu)` — Creates a cross gpu texture
- L25 _public function_ `virtual FTextureRHIRef OpenSharedTextureByGuid(const FGuid& Guid, FSharedMemoryMediaTextureDescription& OutTextureDescription)` — Opens a cross gpu texture specified by a Guid
- L31 _public function_ `virtual void ReleaseSharedTexture(uint32 BufferIdx)` — Release any platform specific resources related to the indexed texture

#### class `FSharedMemoryMediaPlatformFactory`  
`class FSharedMemoryMediaPlatformFactory`  
_L35-60_
- desc: Factory of registered FSharedMemoryMediaPlatform RHI implementations. Use RegisterPlatformForRhi to register them.
- L40 _public typedef_ `typedef TSharedPtr<FSharedMemoryMediaPlatform>(*CreateSharedMemoryMediaPlatform)();` — This is the type definition of the rhi platform factory function that each rhi platfom implementation can register with.
- L45 _public prototype_ `bool RegisterPlatformForRhi(ERHIInterfaceType RhiType, CreateSharedMemoryMediaPlatform PlatformCreator);` — Rhi platform implementations call this function to register their factory creation function
- L48 _public prototype_ `TSharedPtr<FSharedMemoryMediaPlatform, ESPMode::ThreadSafe> CreateInstanceForRhi(ERHIInterfaceType RhiType);` — This factory function will create an instance of the rhi platform specific implementation, if it has been registered.
- L51 _public prototype_ `static FSharedMemoryMediaPlatformFactory* Get();` — Gets the singleton instance of this factory
- L54 _public prototype_ `static FString GetRhiTypeString(const ERHIInterfaceType RhiType);` — Helper function to get a stringified ERHIInterfaceType
- L59 _private member_ `TMap<ERHIInterfaceType, CreateSharedMemoryMediaPlatform> PlatformCreators;` — TMap of the collection of registered rhi platform factory functions

### `Plugins/Runtime/nDisplay/Source/SharedMemoryMedia/Private/SharedMemoryMediaPlayer.h` (Private)


#### class `FSharedMemoryMediaPlayer`  
`class FSharedMemoryMediaPlayer : public IMediaPlayer , protected IMediaCache , protected IMediaControls , protected IMediaTracks , protected IMediaView , public TSharedFromThis<FSharedMemoryMediaPlayer>`  
_L31-335_
- inherits: `IMediaPlayer,IMediaCache,IMediaControls,IMediaTracks,IMediaView,TSharedFromThis<FSharedMemoryMediaPlayer>`
- desc: Implements a media player using shared cross gpu textures. See USharedMemoryMediaCapture docstring for complementary information. It will open shared system memory based on its UniqueName setting, which much match that of the corresponding Media Output. This data will inform the Guid of the shared cross gpu textures and other metadata, and it will use this to open them and to detect when the textures are still valid. It will look at the frame numbers in the metadata when deciding if the data that it is looking for is ready. It informs the sender that it is actively reading the data using a keep alive shift register that it must continually refresh. Also, it acknowledges that it is done with a given gpu texture by setting the frame number in said shared system memory. Even if the sender closes the textures, the open handles in the player will keep them valid and avoid undue crashes.
- L39 _private typedef_ `using Super = IMediaPlayer;`
- L47 _public prototype_ `FSharedMemoryMediaPlayer();`
- L49 _public prototype_ `virtual ~FSharedMemoryMediaPlayer();`
- L54 _public prototype_ `virtual void Close() override;`
- L56 _public prototype_ `virtual FGuid GetPlayerPluginGUID() const override;`
- L58 _public prototype_ `virtual bool Open(const FString& Url, const IMediaOptions* Options) override;`
- L59 _public prototype_ `virtual bool Open(const TSharedRef<FArchive, ESPMode::ThreadSafe>& Archive, const FString& OriginalUrl, const IMediaOptions* Options) override;`
- L61 _public prototype_ `virtual void TickFetch(FTimespan DeltaTime, FTimespan Timecode) override;`
- L62 _public prototype_ `virtual void TickInput(FTimespan DeltaTime, FTimespan Timecode) override;`
- L63 _public prototype_ `virtual bool GetPlayerFeatureFlag(EFeatureFlag Flag) const;`
- L65 _public prototype_ `virtual FString GetStats() const override;`
- L67 _public prototype_ `virtual IMediaSamples& GetSamples() override;`
- L69 _public prototype_ `virtual IMediaCache& GetCache() override;`
- L70 _public prototype_ `virtual IMediaControls& GetControls() override;`
- L71 _public prototype_ `virtual FString GetInfo() const override;`
- L72 _public prototype_ `virtual IMediaTracks& GetTracks() override;`
- L73 _public prototype_ `virtual FString GetUrl() const override;`
- L74 _public prototype_ `virtual IMediaView& GetView() override;`
- L81 _public function_ `virtual bool QueryCacheState(EMediaCacheState State, TRangeSet<FTimespan>& OutTimeRanges) const override`
- L86 _public function_ `virtual int32 GetSampleCount(EMediaCacheState State) const override`
- L95 _protected function_ `virtual bool CanControl(EMediaControl Control) const override`
- L100 _protected function_ `virtual FTimespan GetDuration() const override`
- L105 _protected function_ `virtual float GetRate() const override`
- L110 _protected function_ `virtual EMediaState GetState() const override`
- L115 _protected function_ `virtual EMediaStatus GetStatus() const override`
- L120 _protected function_ `virtual TRangeSet<float> GetSupportedRates(EMediaRateThinning Thinning) const override`
- L127 _protected prototype_ `virtual FTimespan GetTime() const override;`
- L129 _protected function_ `virtual bool IsLooping() const override`
- L134 _protected function_ `virtual bool Seek(const FTimespan& Time) override`
- L139 _protected function_ `virtual bool SetLooping(bool Looping) override`
- L144 _protected function_ `virtual bool SetRate(float Rate) override`
- L153 _protected function_ `virtual bool GetAudioTrackFormat(int32 TrackIndex, int32 FormatIndex, FMediaAudioTrackFormat& OutFormat) const override`
- L158 _protected function_ `virtual int32 GetNumTracks(EMediaTrackType TrackType) const override`
- L163 _protected function_ `virtual int32 GetNumTrackFormats(EMediaTrackType TrackType, int32 TrackIndex) const override`
- L168 _protected function_ `virtual int32 GetSelectedTrack(EMediaTrackType TrackType) const override`
- L173 _protected function_ `virtual FText GetTrackDisplayName(EMediaTrackType TrackType, int32 TrackIndex) const override`
- L178 _protected function_ `virtual int32 GetTrackFormat(EMediaTrackType TrackType, int32 TrackIndex) const override`
- L183 _protected function_ `virtual FString GetTrackLanguage(EMediaTrackType TrackType, int32 TrackIndex) const override`
- L188 _protected function_ `virtual FString GetTrackName(EMediaTrackType TrackType, int32 TrackIndex) const override`
- L193 _protected function_ `virtual bool GetVideoTrackFormat(int32 TrackIndex, int32 FormatIndex, FMediaVideoTrackFormat& OutFormat) const override`
- L198 _protected function_ `virtual bool SelectTrack(EMediaTrackType TrackType, int32 TrackIndex) override`
- L203 _protected function_ `virtual bool SetTrackFormat(EMediaTrackType TrackType, int32 TrackIndex, int32 FormatIndex) override`
- L211 _protected prototype_ `virtual void JustInTimeSampleRender(FRHICommandListImmediate& RHICmdList);` — Enqueues a last minute wait and copy of the expected texture data for the renderer to use
- L214 _protected prototype_ `uint32 InputTextureFrameNumberForFrameNumber(uint32 FrameNumber) const;` — Offsets the frame number by the specified latency. Used to associate resources with frame numbers being evaluated
- L224 _protected prototype_ `bool DetermineNextSourceFrame(uint64 FrameNumber, uint32& OutExpectedFrameNumber, uint32& OutSharedMemoryIdx);` — Determine that the next source frame number and buffer index is. This depends on the player settings. @param OutExpectedFrameNumber Will contain the expected next source frame number @param OutSharedMemoryIdx Will contain the memory idx where we should be looking for the frame @return true only if the output values are valid.
- L227 _protected prototype_ `bool DetermineNextSourceFrameFramelockMode(uint64 FrameNumber, uint32& OutExpectedFrameNumber, uint32& OutSharedMemoryIdx);` — DetermineNextSourceFrame implementration for Framelock Mode
- L230 _protected prototype_ `bool DetermineNextSourceFrameGenlockMode(uint64 FrameNumber, uint32& OutExpectedFrameNumber, uint32& OutSharedMemoryIdx);` — DetermineNextSourceFrame implementration for Genlock Mode
- L233 _protected prototype_ `bool DetermineNextSourceFrameFreerunMode(uint64 FrameNumber, uint32& OutExpectedFrameNumber, uint32& OutSharedMemoryIdx);` — DetermineNextSourceFrame implementration for Freerun Mode
- L239 _protected member_ `static constexpr int32 NUMSHAREDMEM = UE::SharedMemoryMedia::SenderNumBuffers;` — Number of resources used for pipelining the data flow
- L242 _protected member_ `TSharedPtr<FSharedMemoryMediaPlatform, ESPMode::ThreadSafe> PlatformData;` — Platform specific data or resources
- L245 _protected member_ `FTextureRHIRef SharedCrossGpuTextures[NUMSHAREDMEM];` — Set of cross Gpu textures that the Media Capture allocates and the player opens
- L248 _protected member_ `int32 ReceiverIndex[NUMSHAREDMEM] = { 0 };` — Receiver Index used to know what part of the shared metadata corresponds to this receiver
- L251 _protected member_ `FGuid ReceiverId = FGuid::NewGuid();` — Unique number that identifies this receiver from any other
- L254 _protected member_ `FPlatformMemory::FSharedMemoryRegion* SharedMemory[NUMSHAREDMEM] = { 0 };` — Shared memory allocated by the Media Capture for IPC purposes with the Media Player
- L257 _protected member_ `FGPUFenceRHIRef FrameAckFences[NUMSHAREDMEM];` — Indicates that we're done reading the SharedCrossGpuTexture and we can ack the frame to the Media Capture for re-use
- L260 _protected member_ `std::atomic<bool> bFrameAckFenceBusy[NUMSHAREDMEM] = { 0 };` — Needs to be cleared before the corresponding FrameAckFence is reused.
- L263 _protected member_ `TStrongObjectPtr<UTexture2D> SampleCommonTexture;` — For all media samples to re-use
- L266 _protected member_ `uint32 LastFrameNumberThatUpdatedJustInTime = 0;` — Used to ensure that JustInTimeSampleRender is only run once per frame
- L269 _protected member_ `class FSharedMemoryMediaSamples* Samples = nullptr;` — The Media Samples used by this player
- L272 _protected member_ `FString OpenUrl;` — Cached Url currently playing. Used for queries from the outside.
- L275 _protected member_ `FSharedMemoryMediaTextureDescription SharedCrossGpuTextureDescriptions[NUMSHAREDMEM];` — Description of SharedCrossGpuTextures
- L278 _protected member_ `FString UniqueName;` — Unique Name that must match the corresponding MediaOutput setting. It is used to find allocated shared memory by name
- L281 _protected member_ `ESharedMemoryMediaSourceMode Mode = ESharedMemoryMediaSourceMode::Framelocked;` — Reception mode. See ESharedMemoryMediaSourceMode for more details.
- L284 _protected member_ `bool bZeroLatency = true;` — Zero latency option to wait for the cross gpu texture rendered on the same frame. May adversely affect fps. Only applicable when bUseFrameNumbers is true
- L287 _protected member_ `std::atomic<int32> RunningTasksCount{ 0 };` — Counter of running tasks used to detect when to release resources
- L330 _protected member_ `} ModeState;`
- L333 _protected member_ `EMediaState PlayerState = EMediaState::Stopped;` — Current state of the player

#### struct `FSharedMemoryMediaPlayer::FModeState`  
`struct FModeState`  
_L290-330_
- desc: State of each Mode
- L308 _public member_ `} Freerun;`
- L321 _public member_ `} Genlock;`
- L324 _public function_ `void Reset()` — Resets the state for all modes

#### struct `FSharedMemoryMediaPlayer::FModeState::FFreerunModeState`  
`struct FFreerunModeState`  
_L293-308_
- desc: Freerun mode state
- L296 _public member_ `uint32 LastSourceFrameNumberPicked = 0;` — Keep track of the last source frame that was picked. Used to avoid picking the same frame and detect unexpected source frame changes.
- L299 _public member_ `uint32 LastSourceFrameNumberConsideredAtIdx[NUMSHAREDMEM]{ 0 };` — Keep track of the last frame considered at each buffer index. Used to manage acks.
- L302 _public function_ `void Reset()` — Reset the state, as if the stream were started again.

#### struct `FSharedMemoryMediaPlayer::FModeState::FGenlockModeState`  
`struct FGenlockModeState`  
_L311-321_
- desc: Genlock mode state
- L314 _public member_ `uint32 LastSourceFrameNumberPicked = 0;` — Keep track of last picked frame. Used to aim for consecutiveness.
- L317 _public function_ `void Reset()` — Reset the state, as if the stream were started again.

### `Plugins/Runtime/nDisplay/Source/SharedMemoryMedia/Private/SharedMemoryMediaPlayerFactory.h` (Private)


#### class `FSharedMemoryMediaPlayerFactory`  
`class FSharedMemoryMediaPlayerFactory : public IMediaPlayerFactory`  
_L13-40_
- inherits: `IMediaPlayerFactory`
- desc: Factory for the shared memory media player.
- L18 _private member_ `TArray<FString> SupportedPlatforms;` — List of platforms that the media player support.
- L21 _private member_ `TArray<FString> SupportedUriSchemes;` — List of supported URI schemes.
- L25 _public prototype_ `FSharedMemoryMediaPlayerFactory();`
- L29 _public prototype_ `virtual bool CanPlayUrl(const FString& Url, const IMediaOptions* Options, TArray<FText>* OutWarnings, TArray<FText>* OutErrors) const override;`
- L30 _public prototype_ `virtual int32 GetPlayabilityConfidenceScore(const FString& Url, const IMediaOptions* Options, TArray<FText>* OutWarnings, TArray<FText>* OutErrors) const override;`
- L31 _public prototype_ `virtual TSharedPtr<IMediaPlayer, ESPMode::ThreadSafe> CreatePlayer(IMediaEventSink& EventSink) override;`
- L32 _public prototype_ `virtual FText GetDisplayName() const override;`
- L33 _public prototype_ `virtual FName GetPlayerName() const override;`
- L34 _public prototype_ `virtual FGuid GetPlayerPluginGUID() const override;`
- L35 _public prototype_ `virtual const TArray<FString>& GetSupportedPlatforms() const override;`
- L36 _public prototype_ `virtual bool SupportsFeature(EMediaFeature Feature) const override;`

### `Plugins/Runtime/nDisplay/Source/SharedMemoryMedia/Private/SharedMemoryMediaSample.h` (Private)


#### class `FSharedMemoryMediaSample`  
`class FSharedMemoryMediaSample : public IMediaTextureSample`  
_L17-145_
- inherits: `IMediaTextureSample`
- desc: This is the mostly empty sample that the player generates each frame. Its job is mainly to provide the sample converter that will call back the player when rendering the sample, and fill in the data just in time.
- L23 _public member_ `TWeakPtr<FSharedMemoryMediaPlayer, ESPMode::ThreadSafe> Player;` — The player that created this sample
- L26 _public member_ `TSharedPtr<FSharedMemoryMediaTextureSampleConverter, ESPMode::ThreadSafe> Converter;` — Custom converter that will be the one checking back with the player for just in time sample render purposes
- L29 _public member_ `FTextureRHIRef Texture;` — The texture that will get its pixels just in time when playing back this sample
- L32 _public member_ `FTimespan Time;` — Player time for this sample to be evaluated at
- L35 _public member_ `uint32 Stride = 0;` — Texture stride
- L38 _public member_ `FIntPoint Dim = FIntPoint::ZeroValue;` — Texture dimensions
- L41 _public member_ `bool bSrgb = false;` — Whether the sample is sRGB encoded or not
- L44 _public member_ `EMediaTextureSampleFormat Format = EMediaTextureSampleFormat::CharBGR10A2;` — Sample format
- L49 _private member_ `TArray<uint8> BackupData;` — Used in case the Texture is not valid, so we can provide pixels to the Media Framework
- L55 _public function_ `const void* GetBuffer() override`
- L73 _public function_ `FIntPoint GetDim() const override`
- L78 _public function_ `FTimespan GetDuration() const override`
- L84 _public function_ `EMediaTextureSampleFormat GetFormat() const override`
- L89 _public function_ `FIntPoint GetOutputDim() const override`
- L94 _public function_ `uint32 GetStride() const override`
- L99 _public function_ `FMediaTimeStamp GetTime() const override`
- L104 _public function_ `bool IsCacheable() const override`
- L109 _public function_ `bool IsOutputSrgb() const override`
- L114 _public function_ `virtual bool ShouldApplyColorConversion() const override`
- L123 _public function_ `virtual IMediaTextureSampleConverter* GetMediaTextureSampleConverter() override`
- L139 _public function_ `virtual FRHITexture* GetTexture() const override`

### `Plugins/Runtime/nDisplay/Source/SharedMemoryMedia/Private/SharedMemoryMediaSamples.h` (Private)


#### class `FSharedMemoryMediaSamples`  
`class FSharedMemoryMediaSamples : public IMediaSamples`  
_L12-57_
- inherits: `IMediaSamples`
- desc: This is the mostly empty media samples that only carries a single sample per frame, that the player provides.
- L16 _public function_ `FSharedMemoryMediaSamples()`
- L21 _public prototype_ `FSharedMemoryMediaSamples(const FSharedMemoryMediaSamples&) = delete;`
- L22 _public prototype_ `FSharedMemoryMediaSamples& operator=(const FSharedMemoryMediaSamples&) = delete;`
- L28 _public function_ `virtual bool FetchVideo(TRange<FTimespan> TimeRange, TSharedPtr<IMediaTextureSample, ESPMode::ThreadSafe>& OutSample) override`
- L42 _public function_ `virtual bool PeekVideoSampleTime(FMediaTimeStamp& TimeStamp) override`
- L47 _public function_ `virtual void FlushSamples() override`
- L56 _public member_ `TSharedPtr<FSharedMemoryMediaSample, ESPMode::ThreadSafe> CurrentSample;`

### `Plugins/Runtime/nDisplay/Source/SharedMemoryMedia/Private/SharedMemoryMediaSourceOptions.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace SharedMemoryMediaOption`
- L10 _variable_ `static const FName UniqueName("Uni` (scope `SharedMemoryMediaOption`)
- L11 _variable_ `static const FName Mode("Mod` (scope `SharedMemoryMediaOption`)
- L12 _variable_ `static const FName ZeroLatency("Zer` (scope `SharedMemoryMediaOption`)

### `Plugins/Runtime/nDisplay/Source/SharedMemoryMedia/Private/SharedMemoryMediaTextureSampleConverter.h` (Private)


#### class `FSharedMemoryMediaTextureSampleConverter`  
`class FSharedMemoryMediaTextureSampleConverter : public IMediaTextureSampleConverter`  
_L10-37_
- inherits: `IMediaTextureSampleConverter`
- L15 _public member_ `FSharedMemoryMediaPlayer* Player = nullptr;` — The player that this converter will check back with for just in time sample render purposes
- L20 _public function_ `virtual uint32 GetConverterInfoFlags() const override`
- L25 _public function_ `virtual bool Convert(FRHICommandListImmediate& RHICmdList, FTextureRHIRef& InDstTexture, const FConversionHints& Hints) override`

### `Plugins/Runtime/nDisplay/Source/SharedMemoryMedia/Private/SharedMemoryMediaTypes.h` (Private)


#### struct `FSharedMemoryMediaTextureDescription`  
`struct FSharedMemoryMediaTextureDescription`  
_L38-58_
- L40 _public member_ `uint32 Width = 0;`
- L41 _public member_ `uint32 Height = 0;`
- L42 _public member_ `uint32 BytesPerPixel = 0;`
- L43 _public member_ `uint32 Stride = 0;`
- L44 _public member_ `EPixelFormat Format = EPixelFormat::PF_Unknown;`
- L45 _public member_ `FGuid Guid = UE::SharedMemoryMedia::ZeroGuid;`
- L46 _public member_ `bool bSrgb = false;`
- L48 _public function_ `bool IsEquivalentTo(const FSharedMemoryMediaTextureDescription& Other) const`

#### struct `FSharedMemoryMediaFrameMetadata`  
`struct FSharedMemoryMediaFrameMetadata`  
_L63-135_
- desc: This structure represents the IPC between sender and receiver of the shared memory media.
- L66 _public member_ `static constexpr uint32 MAGIC = 0x534D4D4D;` — SMMM - Shared Memory Media Metadata
- L69 _public member_ `static constexpr uint8 KeepAliveCounterResetValue = 12;` — Value that receivers should use when resetting the KeepAliveCounters. Corresponds to number of sender frames.
- L72 _public member_ `static constexpr uint32 MaxNumReceivers = 4;` — Maximum number of concurrent receivers of the shared texture
- L85 _public member_ `} Sender;`
- L107 _public member_ `FReceiver Receivers[MaxNumReceivers] = {};` — Array of possible receivers
- L112 _public prototype_ `void Initialize();` — Initialize critical values
- L115 _public prototype_ `bool IsSlotIndexValid(const int32 SlotIndex) const;` — Returns true is the SlotId is valid
- L118 _public prototype_ `bool IsReceiverConnectedToSlot(const FGuid& Id, const int32 SlotIndex) const;` — Checks if the receiver of the given Id owns the given slot
- L121 _public prototype_ `int32 ConnectToSlot(const FGuid& Id);` — Finds a slot for the give receiver. Returns the slot index, or INDEX_NONE if it could not find one.
- L124 _public prototype_ `void DisconnectReceiverFromSlot(const FGuid& Id, const int32 SlotIndex);` — Give up control of the slot
- L127 _public prototype_ `bool KeepAlive(const int32 SlotIndex);` — Keeps the connection to the slot alive. True if succeeded.
- L130 _public prototype_ `bool AllReceiversAckedFrameNumber(const uint32 FrameNumber) const;` — Returns true only if all active receivers have acked the given frame number
- L134 _public prototype_ `void DecrementKeepAlives();` — Decrements all keepalives, which is intended to auto-disconnect stale receivers. The receiver must keep resetting its keepalive to avoid letting it expire.

#### struct `FSharedMemoryMediaFrameMetadata::FSender`  
`struct FSender`  
_L75-85_
- desc: Data that the sender wants to communicate
- L78 _public member_ `uint32 Magic = MAGIC;` — Used to determine that the rest of the metadata is valid.
- L81 _public member_ `FGuid TextureGuid;` — Each shared cross gpu texture is assigned a Guid. The player can use this to locate and open them.
- L84 _public member_ `uint32 FrameNumber = 0;` — This is the sender's frame number of the pixel data in the texture.

#### struct `FSharedMemoryMediaFrameMetadata::FReceiver`  
`struct FReceiver`  
_L88-104_
- desc: Data that the receiver wants to communicate (although KeepAliveShiftRegister is shifted by the Sender)
- L91 _public member_ `std::atomic<uint32> FrameNumberAcked = ~0u;` — Frame number that the receiver is done reading. This signals the sender that it can re-use the texture.
- L97 _public member_ `std::atomic<uint8> KeepAliveCounter = 0;` — The receiver sets this register. This signals the sender that it should wait for the related frame number ack before re-using the texture. The sender will decrement this register each frame, as a way to time out the session in case the receiver disappears without clearing it.
- L100 _public member_ `FGuid Id;` — Receiver id, used to detect collisions where two receivers think that they own the same slot
- L103 _public prototype_ `void Disconnect();` — Disconnect from this slot. Meant to be called by the receiver.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SharedMemoryMedia` (scope `UE`)
- L13 _variable_ `constexpr float SpinWaitTimeSeconds = 50 * 1e-6f;` (scope `UE::SharedMemoryMedia`) — When the implementation requires spin waiting on a fence or polling shared system memory, it will sleep by the amount below in a loop until the condition is met or a given timout occurs.
- L16 _variable_ `static const FGuid PlayerGuid = FGuid(0xAF8C5107, 0x13CF992C, 0x9FD4EBFE, 0x2E3E049F);` (scope `UE::SharedMemoryMedia`) — Guid that identifies the SharedMemoryMediaPlayer.
- L25 _function_ `static FGuid GenerateSharedMemoryGuid(FString UniqueName, uint32 BufferIdx)` (scope `UE::SharedMemoryMedia`) — Used to generate a Guid based on the UniqueName that sender and receiver uses to open the same shared system memory used for IPC. There will be one shard memory region per buffer index. There are SenderNumBuffers buffer indices. A given frame number uses a buffer index defined by: BufferIdx = FrameNumber % SenderNumBuffers.
- L35 _variable_ `static const FGuid ZeroGuid = FGuid(0, 0, 0, 0);` (scope `UE::SharedMemoryMedia`) — Convenience ZeroGuid value.

### `Plugins/Runtime/nDisplay/Source/SharedMemoryMedia/Public/SharedMemoryMediaCapture.h` (Public)


#### class `USharedMemoryMediaCapture`  
`class USharedMemoryMediaCapture : public UMediaCapture`  
_L35-110_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMediaCapture`
- desc: Output Media for SharedMemory. The pixels are captured into shared cross gpu textures, that a player can read. Inter-process communication happens via shared system memory. The metadata exchanged is documented in the FSharedMemoryMediaFrameMetadata structure. The shared memory can be located via a UniqueName that must match in the Media Output and corresponding Media Source settings. It is mostly intended for use in nDisplay render nodes, which are designed to be frame-locked.
- L43 _protected prototype_ `virtual bool ShouldCaptureRHIResource() const override;`
- L44 _protected prototype_ `virtual bool InitializeCapture() override;`
- L45 _protected prototype_ `virtual void StopCaptureImpl(bool bAllowPendingFrameToBeProcess) override;`
- L46 _protected function_ `virtual bool SupportsAnyThreadCapture() const override`
- L52 _protected prototype_ `virtual FIntPoint GetCustomOutputSize(const FIntPoint& InSize) const override;` — For custom conversion, methods that need to be overridden
- L53 _protected prototype_ `virtual EMediaCaptureResourceType GetCustomOutputResourceType() const override;`
- L55 _protected prototype_ `virtual void OnCustomCapture_RenderingThread( FRDGBuilder& GraphBuilder, const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, FRDGTextureRef InSourceTexture, FRDGTextureRef OutputTexture, const FRHICopyTextureInfo& CopyInfo, FVector2D CropU, FVector2D CropV) override;`
- L68 _protected function_ `void AddCopyToSharedGpuTexturePass(FRDGBuilder& GraphBuilder, FRDGTextureRef InSourceTexture, uint32 SharedTextureIdx)` — `UE_DEPRECATED(5.5, "Use the version of AddCopyToSharedGpuTexturePass with FRHICopyTextureInfo.")`
- L74 _protected function_ `void AddInvertAlphaConversionPass(FRDGBuilder& GraphBuilder, const FRDGTextureRef& SourceTexture, FRDGTextureRef DestTexture)` — `UE_DEPRECATED(5.5, "Use the version of AddInvertAlphaConversionPass with FRHICopyTextureInfo.")`
- L80 _protected prototype_ `void AddCopyToSharedGpuTexturePass(FRDGBuilder& GraphBuilder, FRDGTextureRef InSourceTexture, uint32 SharedTextureIdx, const FRHICopyTextureInfo& CopyInfo);` — Adds to the graph builder the copy from the input texture to the shared gpu texture that corresponds to the current frame number
- L83 _protected prototype_ `void AddInvertAlphaConversionPass(FRDGBuilder& GraphBuilder, const FRDGTextureRef& SourceTexture, FRDGTextureRef DestTexture, const FRHICopyTextureInfo& CopyInfo);` — Adds a pass to invert the alpha of the texture
- L88 _private member_ `static constexpr int32 NUMBUFFERS = UE::SharedMemoryMedia::SenderNumBuffers;` — Number of shared buffers
- L91 _private member_ `FPlatformMemory::FSharedMemoryRegion* SharedMemory[NUMBUFFERS] = { 0 };` — Shared RAM used for IPC between media capture and player
- L94 _private member_ `FTextureRHIRef SharedCrossGpuTextures[NUMBUFFERS];` — Shared Cross Gpu Textures. The texture exchange happens using these.
- L97 _private member_ `FGPUFenceRHIRef TextureReadyFences[NUMBUFFERS];` — Fence for an async task to know when the cross gpu texture has the data to be shared
- L100 _private member_ `std::atomic<bool> bTextureReadyFenceBusy[NUMBUFFERS] = { 0 };` — Flags that the associated TextureReadyFence can be re-used. Otherwise the player may still be reading it.
- L103 _private member_ `TSharedPtr<FSharedMemoryMediaPlatform, ESPMode::ThreadSafe> PlatformData;` — Platform specific data or resources
- L106 _private member_ `FGuid SharedCrossGpuTextureGuids[NUMBUFFERS];` — Guids associated with the cross gpu textures in use. These are communicated to the player for it to open them by name.
- L109 _private member_ `std::atomic<int32> RunningTasksCount{ 0 };` — Counter of running tasks used to detect when to release resources

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace SharedMemoryMedia` (scope `UE`)
- L21 _variable_ `constexpr int32 SenderNumBuffers = 3;` (scope `UE::SharedMemoryMedia`) — This defines the number of textures used for communication. Having more that one allows for overlapping sends and minimize waits on frame acks for texture re-use. Use 3 for best performance, or 2 for a potential compromise with resource usage.

### `Plugins/Runtime/nDisplay/Source/SharedMemoryMedia/Public/SharedMemoryMediaOutput.h` (Public)


#### class `USharedMemoryMediaOutput`  
`class USharedMemoryMediaOutput : public UMediaOutput`  
_L17-47_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMediaOutput`
- desc: Output information for a SharedMemory media capture.
- L25 _public member_ `FString UniqueName = TEXT("Uni` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Output")` — Shared memory will be opened by using this name. Should be unique per media output.
- L29 _public member_ `bool bInvertAlpha = true;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, Category = "Output")` — If checked, the alpha channel of the texture will be inverted
- L33 _public member_ `bool bCrossGpu = true;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, Category = "Output")` — If checked, the texture will be shared across different GPUs. Disable if not needed for faster performance
- L38 _public prototype_ `virtual bool Validate(FString& FailureReason) const override;`
- L39 _public prototype_ `virtual FIntPoint GetRequestedSize() const override;`
- L40 _public prototype_ `virtual EPixelFormat GetRequestedPixelFormat() const override;`
- L41 _public prototype_ `virtual EMediaCaptureConversionOperation GetConversionOperation(EMediaCaptureSourceType InSourceType) const override;`
- L44 _protected prototype_ `virtual UMediaCapture* CreateMediaCaptureImpl() override;`

### `Plugins/Runtime/nDisplay/Source/SharedMemoryMedia/Public/SharedMemoryMediaSource.h` (Public)


#### enum `ESharedMemoryMediaSourceMode`  
`enum class ESharedMemoryMediaSourceMode : uint8`  
_L17-22_
- reflection: `UENUM(BlueprintType)`
- desc: Mode of operation when receiving data. Framelocked - Matches source and local frame numbers. Always use this mode in nDisplay. Genlocked - It doesn't match frame numbers, but it also doesn't skip frames, so will hold back the sender if it is faster than the receiver. Freerun - It always grabs the latest frame. It may skip frames if they arrive too fast.
- L19 _public enumerator_ `Framelocked = 0` — Matches source and local frame numbers. Always use this mode in nDisplay.
- L20 _public enumerator_ `Genlocked` — It doesn't match frame numbers, but it also doesn't skip frames, so will hold back the sender if it is faster than the receiver.
- L21 _public enumerator_ `Freerun` — It always grabs the latest frame. It may skip frames if they arrive too fast.

#### class `USharedMemoryMediaSource`  
`class USharedMemoryMediaSource : public UMediaSource`  
_L28-64_
- reflection: `UCLASS(BlueprintType, hideCategories=(Platforms,Object))`
- inherits: `UMediaSource`
- desc: Media source for SharedMemory streams.
- L36 _public member_ `FString UniqueName = TEXT("Uni` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")` — Shared memory will be found by using this name. Should match the media output setting.
- L45 _public member_ `ESharedMemoryMediaSourceMode Mode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")` — Mode of operation when receiving data. Framelocked - Matches source and local frame numbers. Always use this mode in nDisplay. Genlocked - It doesn't match frame numbers, but it also doesn't skip frames, so will hold back the sender if it is faster than the receiver. Freerun - It always grabs the latest frame. It may skip frames if they arrive too fast.
- L49 _public member_ `bool bZeroLatency = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")` — Zero latency option to wait for the cross gpu texture rendered on the same frame. May adversely affect fps. Only applicable in Framelocked mode.
- L54 _public prototype_ `virtual FString GetUrl() const override;`
- L55 _public prototype_ `virtual bool Validate() const override;`
- L59 _public prototype_ `virtual bool GetMediaOption(const FName& Key, bool DefaultValue) const override;`
- L60 _public prototype_ `virtual int64 GetMediaOption(const FName& Key, int64 DefaultValue) const override;`
- L61 _public prototype_ `virtual FString GetMediaOption(const FName& Key, const FString& DefaultValue) const override;`
- L62 _public prototype_ `virtual bool HasMediaOption(const FName& Key) const override;`
