# Plugins / RivermaxMedia

- module root: `Plugins/VirtualProduction/Rivermax/RivermaxMedia/Source/RivermaxMedia`
- headers: 14; symbols: 325
- symbol kinds: class=12, delegate=1, enum=5, enumerator=17, function=27, member=95, namespace=10, prototype=131, struct=8, typedef=5, variable=14
- PrivateDependencyModuleNames: Engine, OpenColorIO, RHI, RenderCore, RivermaxRendering
- PublicDependencyModuleNames: Core, CoreUObject, MediaAssets, MediaIOCore, RivermaxCore, TimeManagement

### `Plugins/VirtualProduction/Rivermax/RivermaxMedia/Source/RivermaxMedia/Private/RivermaxMediaLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogRivermaxMedia, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRivermaxMedia, Log, All);`

### `Plugins/VirtualProduction/Rivermax/RivermaxMedia/Source/RivermaxMedia/Private/RivermaxMediaModule.h` (Private)


#### class `FRivermaxMediaModule`  
`class FRivermaxMediaModule : public IRivermaxMediaModule`  
_L10-19_
- inherits: `IRivermaxMediaModule`
- L14 _public prototype_ `virtual void StartupModule() override;`
- L15 _public prototype_ `virtual void ShutdownModule() override;`
- L18 _public prototype_ `virtual TSharedPtr<IMediaPlayer> CreatePlayer(IMediaEventSink& EventSink) override;`

### `Plugins/VirtualProduction/Rivermax/RivermaxMedia/Source/RivermaxMedia/Private/RivermaxMediaPlayer.h` (Private)


#### class `UE::RivermaxMedia::FRivermaxMediaPlayer`  
`class FRivermaxMediaPlayer : public FMediaIOCorePlayerBase, public IRivermaxInputStreamListener`  
_L31-234_
- inherits: `FMediaIOCorePlayerBase,IRivermaxInputStreamListener`
- desc: Implements a media player using rivermax.
- L33 _private typedef_ `using Super = FMediaIOCorePlayerBase;`
- L41 _public prototype_ `FRivermaxMediaPlayer(IMediaEventSink& InEventSink);` — Create and initialize a new instance. @param InEventSink The object that receives media events from this player.
- L44 _public prototype_ `virtual ~FRivermaxMediaPlayer();` — Virtual destructor.
- L50 _public prototype_ `virtual bool JustInTimeSampleRender_RenderThread(FRHICommandListImmediate& RHICmdList, FTextureRHIRef& InDestinationTexture, TSharedPtr<FMediaIOCoreTextureSampleBase>& JITRProxySample) override;` — Called by the sample converter to setup rendering commands to convert this sample into texture.
- L52 _protected prototype_ `virtual TSharedPtr<FMediaIOCoreTextureSampleBase> PickSampleToRenderFramelocked_RenderThread(const FFrameInfo& InFrameInformation) override;`
- L55 _protected prototype_ `virtual TSharedPtr<FMediaIOCoreTextureSampleBase> PickSampleToRenderForTimeSynchronized_RenderThread(const FFrameInfo& InFrameInformation) override;` — Pick sample based on Vsync timecode and Start and End of sample reception.
- L60 _public prototype_ `virtual void Close() override;`
- L61 _public prototype_ `virtual FGuid GetPlayerPluginGUID() const override;`
- L62 _public prototype_ `virtual bool Open(const FString& Url, const IMediaOptions* Options) override;`
- L63 _public prototype_ `virtual void TickInput(FTimespan DeltaTime, FTimespan Timecode) override;`
- L68 _public prototype_ `virtual const FSlateBrush* GetDisplayIcon() const override;`
- L72 _public function_ `ERivermaxPixelFormat GetDesiredPixelFormat()`
- L78 _public prototype_ `virtual void OnInitializationCompleted(const FRivermaxInputInitializationResult& Result) override;`
- L79 _public prototype_ `virtual TSharedPtr<IRivermaxVideoSample> OnVideoFrameRequested(const FRivermaxInputVideoFrameDescriptor& FrameInfo) override;`
- L80 _public prototype_ `virtual void OnVideoFrameReceived(TSharedPtr<IRivermaxVideoSample> InReceivedVideoFrame) override;`
- L81 _public prototype_ `virtual void OnVideoFrameReceptionError(TSharedPtr<IRivermaxVideoSample> InReceivedVideoFrame) override;`
- L82 _public prototype_ `virtual void OnStreamError() override;`
- L83 _public prototype_ `virtual void OnVideoFormatChanged(const FRivermaxInputVideoFormatChangedInfo& NewFormatInfo) override;`
- L89 _protected prototype_ `virtual bool IsHardwareReady() const override;`
- L90 _protected prototype_ `virtual void SetupSampleChannels() override;`
- L91 _protected prototype_ `virtual TSharedPtr<FMediaIOCoreTextureSampleConverter> CreateTextureSampleConverter() const override;`
- L93 _protected prototype_ `virtual TSharedPtr<FMediaIOCoreTextureSampleBase> AcquireTextureSample_AnyThread() const override;`
- L96 _protected prototype_ `virtual FString GetAnalyticsEventPrefix() const override;`
- L97 _protected prototype_ `virtual void GetAnalyticsEventAttributes(const FString& EventName, TArray<FAnalyticsEventAttribute>& InOutAttributes) const override;`
- L137 _private prototype_ `TSharedPtr<IRivermaxAncSample> HandleAncFrameRequested(const FRivermaxInputAncFrameDescriptor& FrameInfo);` — Called by FAncStreamListener when an ANC packet arrives.
- L138 _private prototype_ `void HandleAncFrameReceived(TSharedPtr<IRivermaxAncSample> InReceivedAncFrame);`
- L139 _private prototype_ `void HandleAncFrameReceptionError();`
- L142 _private prototype_ `bool ConfigureStream(const IMediaOptions* Options);` — Sets up stream options based on the settings of the media source
- L145 _private prototype_ `void AllocateBuffers(const FIntPoint& InResolution);` — Allocates the sample pool used to receive incoming data
- L148 _private prototype_ `void SampleUploadSetupTaskThreadMode(TSharedPtr<FRivermaxMediaTextureSample> Sample, FSampleConverterOperationSetup& OutConverterSetup);` — Buffer upload setup that will wait on its own task to wait for sample and do the upload
- L151 _private typedef_ `using FWaitConditionFunc = TUniqueFunction<bool(const TSharedPtr<FRivermaxMediaTextureSample>&)>;` — Function waiting for the expected frame to be received.
- L152 _private prototype_ `bool WaitForSample(const TSharedPtr<FRivermaxMediaTextureSample>& Sample, const uint64 AwaitingFrameNumber, FWaitConditionFunc WaitConditionFunction, const double TimeoutSeconds);`
- L155 _private prototype_ `void PostSampleUsage(FRDGBuilder& GraphBuilder, TSharedPtr<FRivermaxMediaTextureSample> Sample);` — Called after sample was converted / rendered. Used write a fence to detect when sample is reusable
- L158 _private prototype_ `bool IsReadyToPlay() const;` — Whether player is ready to play
- L161 _private prototype_ `void WaitForPendingTasks();` — Waits for tasks in flight and flushes render commands before cleaning our ressources
- L164 _private prototype_ `TRefCountPtr<FRHITexture> CreateIntermediateRenderTarget(FRHICommandListImmediate& RHICmdList, const FIntPoint& InDim, EPixelFormat InPixelFormat, bool bInSRGB);` — Used to create texture for color encoding conversion.
- L168 _private member_ `static constexpr uint32 kMaxNumVideoFrameBuffer = 6;` — Size of the sample pool. The max number of FrameDelay (4) + 2 frames (to give time to return back to the pool)
- L171 _private member_ `EMediaState RivermaxThreadNewState;` — Current state of the media player.
- L174 _private member_ `FRivermaxInputStreamOptions StreamOptions;` — Options used to configure the stream. i.e.
- L177 _private member_ `TUniquePtr<IRivermaxInputStream> InputStream;` — Maps to the current input Device
- L180 _private member_ `TArray<TUniquePtr<IRivermaxInputStream>> AncInputStreams;` — ANC (2110-40) input streams (one per configured ANC stream).
- L183 _private member_ `TArray<TUniquePtr<FAncStreamListener>> AncStreamListeners;` — Listeners forwarded to AncInputStreams to keep ANC callbacks separate from video state.
- L193 _private member_ `TMap<uint32, FVideoFrameAncData> PendingAncData;` — Keyed by RTP timestamp (shared 90 kHz PTP clock between ST2110-20 and -40).
- L194 _private member_ `FCriticalSection PendingAncDataLock;`
- L197 _private member_ `ERivermaxPixelFormat DesiredPixelFormat = ERivermaxPixelFormat::RGB_10bit;` — Pixel format provided by media source
- L203 _private member_ `TUniquePtr<FRivermaxMediaTextureSamplePool> VideoTextureSamplePool;` — Pool of samples. The pool has full management of shared pointers. Unreferenced shared pointers automatically return back to the pool and released only when pool is destroyed.
- L206 _private member_ `TStaticArray<TSharedPtr<FRivermaxMediaTextureSample>, kMaxNumVideoFrameBuffer> FrameLockedSamples;` — Sample that input stream should write to in framelocking mode.
- L209 _private member_ `std::atomic<uint32> TasksInFlight = 0;` — Number of tasks currently in progress. Used during shutdown to know when we are good to continue
- L212 _private member_ `bool bStreamSupportsGPUDirect = false;` — Whether the created stream supports GPUDirect. Will be confirmed after initialization.
- L215 _private member_ `static constexpr double SleepTimeSeconds = 50.0 * 1E-6;` — Time to sleep when waiting for an operation to complete
- L218 _private member_ `mutable FCriticalSection StreamResolutionCriticalSection;` — Critical section used when accessing stream resolution and detect pending changes
- L221 _private member_ `FIntPoint StreamResolution = FIntPoint::ZeroValue;` — Resolution detected by our stream.
- L224 _private member_ `bool bFollowsStreamResolution = true;` — Whether the player follows resolution detected by our stream, adjusting texture size as required
- L227 _private member_ `uint32 LastFrameToAttemptReception = 0;` — Used to make sure that the player didn't accidentally skipped the reception of any frames.
- L230 _private member_ `mutable FCriticalSection ProxySampleAccessCriticalSection;` — Critical section used when accessing ProxySampleDummy.
- L233 _private member_ `TSharedPtr<FRivermaxMediaTextureSample> ProxySampleDummy;` — This is the proxy sample contains all common settings for texture samples for this player.

#### class `UE::RivermaxMedia::FRivermaxMediaPlayer::FAncStreamListener`  
`class FAncStreamListener : public IRivermaxInputStreamListener`  
_L107-134_
- inherits: `IRivermaxInputStreamListener`
- desc: Listener forwarded to the ANC input stream. Keeps ANC initialization separate from the video stream state machine.
- L110 _public function_ `explicit FAncStreamListener(FRivermaxMediaPlayer& InPlayer) : Player(InPlayer)`
- L111 _public prototype_ `virtual ~FAncStreamListener() = default;`
- L113 _public function_ `virtual void OnInitializationCompleted(const FRivermaxInputInitializationResult& Result) override`
- L114 _public function_ `virtual TSharedPtr<IRivermaxVideoSample> OnVideoFrameRequested(const FRivermaxInputVideoFrameDescriptor& FrameInfo) override`
- L115 _public function_ `virtual void OnVideoFrameReceived(TSharedPtr<IRivermaxVideoSample> InReceivedVideoFrame) override`
- L116 _public function_ `virtual void OnStreamError() override`
- L117 _public function_ `virtual void OnVideoFormatChanged(const FRivermaxInputVideoFormatChangedInfo& NewFormatInfo) override`
- L119 _public function_ `virtual TSharedPtr<IRivermaxAncSample> OnAncFrameRequested(const FRivermaxInputAncFrameDescriptor& FrameInfo) override`
- L123 _public function_ `virtual void OnAncFrameReceived(TSharedPtr<IRivermaxAncSample> InReceivedAncFrame) override`
- L127 _public function_ `virtual void OnAncFrameReceptionError() override`
- L133 _private member_ `FRivermaxMediaPlayer& Player;`

#### struct `UE::RivermaxMedia::FRivermaxMediaPlayer::FVideoFrameAncData`  
`struct FVideoFrameAncData`  
_L186-190_
- desc: Decoded ANC payload for one video frame. Add a TOptional field per new ANC type.
- L189 _public member_ `TOptional<FTimecode> Timecode;` — ATC LTC (see AncTimecodeDID/AncTimecodeSDID)

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace RivermaxMedia` (scope `UE`)

### `Plugins/VirtualProduction/Rivermax/RivermaxMedia/Source/RivermaxMedia/Private/RivermaxMediaSourceOptions.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace RivermaxMediaOption`
- L10 _variable_ `static const FName InterfaceAddress("Int` (scope `RivermaxMediaOption`)
- L11 _variable_ `static const FName StreamAddress("Str` (scope `RivermaxMediaOption`)
- L12 _variable_ `static const FName Port("Por` (scope `RivermaxMediaOption`)
- L13 _variable_ `static const FName PixelFormat("Pix` (scope `RivermaxMediaOption`)
- L14 _variable_ `static const FName UseGPUDirect("Use` (scope `RivermaxMediaOption`)
- L15 _variable_ `static const FName OverrideResolution("Ove` (scope `RivermaxMediaOption`)
- L18 _variable_ `static const FName AncStreamType("Anc` (scope `RivermaxMediaOption`) — ANC input stream (first entry in AncStreams array)
- L19 _variable_ `static const FName AncInterfaceAddress("Anc` (scope `RivermaxMediaOption`)
- L20 _variable_ `static const FName AncStreamAddress("Anc` (scope `RivermaxMediaOption`)
- L21 _variable_ `static const FName AncPort("Anc` (scope `RivermaxMediaOption`)

### `Plugins/VirtualProduction/Rivermax/RivermaxMedia/Source/RivermaxMedia/Private/RivermaxMediaTextureSample.h` (Private)


#### class `UE::RivermaxMedia::FRivermaxMediaTextureSample`  
`class FRivermaxMediaTextureSample : public FMediaIOCoreTextureSampleBase, public UE::RivermaxCore::IRivermaxVideoSample`  
_L22-176_
- inherits: `FMediaIOCoreTextureSampleBase,UE::RivermaxCore::IRivermaxVideoSample`
- desc: Implements a media texture sample for RivermaxMediaPlayer.
- L25 _public prototype_ `FRivermaxMediaTextureSample();`
- L29 _public function_ `static inline const TCHAR*& SampleStateToStringRef(ESampleState InState)` — A helper function that returns the string based on the provided state.
- L39 _public prototype_ `virtual bool IsCacheable() const override;`
- L40 _public prototype_ `virtual const FMatrix& GetYUVToRGBMatrix() const override;`
- L43 _public prototype_ `virtual IMediaTextureSampleConverter* GetMediaTextureSampleConverter() override;`
- L48 _public prototype_ `virtual bool InitializeJITR(const FMediaIOCoreSampleJITRConfigurationArgs& Args) override;`
- L49 _public prototype_ `virtual void CopyConfiguration(const TSharedPtr<FMediaIOCoreTextureSampleBase>& SourceSample) override;`
- L53 _public prototype_ `void InitializeGPUBuffer(const FIntPoint& InResolution, ERivermaxPixelFormat InSampleFormat, bool bSupportsGPUDirect);` — Initialized a RDG buffer based on the description required. Only useful for gpudirect functionality
- L56 _public prototype_ `ERivermaxPixelFormat GetInputFormat() const;` — Returns the incoming sample format
- L57 _public prototype_ `void SetInputFormat(ERivermaxPixelFormat InFormat);`
- L60 _public prototype_ `virtual TRefCountPtr<FRDGPooledBuffer> GetGPUBuffer() const override;` — Inherited via IRivermaxVideoSample
- L61 _public prototype_ `virtual uint8* GetVideoBufferRawPtr(uint32 VideoBufferSize) override;`
- L62 _public prototype_ `virtual void SetReceptionState(ESampleState State) override;`
- L64 _public function_ `virtual void InitializePoolable() override`
- L66 _public function_ `virtual void ShutdownPoolable() override`
- L87 _public function_ `virtual bool IsReadyForReuse() override`
- L97 _public function_ `bool TryLockForRendering()` — Attempts to lock this sample for rendering. Returns true if sample is ok to be rendered. Returns false if sample is already being rendered.
- L115 _public function_ `void MarkRenderingComplete()` — Marks that this sample can be rendered again if need be.
- L121 _public function_ `bool IsBeingRendered()`
- L127 _public function_ `FEvent* GetSampleReceivedEvent()`
- L132 _public function_ `void SetTimecode(const TOptional<FTimecode>& InTimecode)`
- L142 _public member_ `std::atomic<void*> LockedMemory = nullptr;` — Locked memory of gpu buffer when uploading. Set only for non-GPU-direct Dynamic buffers: locked once at InitializeGPUBuffer and unlocked in the destructor. ProcessSRD writes directly here via GetVideoBufferRawPtr, eliminating any intermediate CPU copy. Null for GPU-direct buffers.
- L145 _public member_ `FGPUFenceRHIRef SampleConversionFence;` — Write fence enqueued after sample conversion to know when it's ready to be reused
- L149 _private member_ `FEvent* SampleReceivedEvent = nullptr;` — This event isued to wait for the sample to be fully received.
- L152 _private member_ `std::atomic<bool> bIsPendingRendering = false;` — True when queued for rendering. Will be false once fence has been written, after shader usage.
- L157 _private member_ `ERivermaxPixelFormat InputFormat = ERivermaxPixelFormat::YUV422_8bit;` — Format in the rivermax realm
- L160 _private member_ `uint32 Stride = 0;` — Texture stride
- L163 _private member_ `TRefCountPtr<FRDGPooledBuffer> GPUBuffer;` — Pooled buffer used for gpudirect functionality. Received content will already be on GPU when received from NIC
- L169 _private member_ `uint32 RTPTimestamp = 0;` — RTP timestamp of this frame (90 kHz PTP clock). Used to look up the matching ANC entry.
- L172 _private member_ `FTimespan FrameReceptionStart = 0;` — The start of the reception marked by the first chunk received by rivermax.
- L175 _private member_ `FTimespan FrameReceptionEnd = 0;` — The end of the reception marked by the last processed packet.

#### class `UE::RivermaxMedia::FRivermaxMediaTextureSamplePool`  
`class FRivermaxMediaTextureSamplePool : public TMediaObjectPool<FRivermaxMediaTextureSample>`  
_L178-178_
- inherits: `TMediaObjectPool<FRivermaxMediaTextureSample>`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace RivermaxMedia` (scope `UE`)

### `Plugins/VirtualProduction/Rivermax/RivermaxMedia/Source/RivermaxMedia/Private/RivermaxMediaTextureSampleConverter.h` (Private)


#### struct `UE::RivermaxMedia::FSampleConverterOperationSetup`  
`struct FSampleConverterOperationSetup`  
_L23-33_
- desc: Structure used during late update to let player configure some operations
- L26 _public member_ `FPreInputConvertFunc PreConvertFunc = nullptr;` — Function to be called before setting up the sample conversion graph
- L29 _public member_ `FGetGPUBufferFunc GetGPUBufferFunc = nullptr;` — Function used to retrieve gpu buffer if available
- L32 _public member_ `FPostInputConvertFunc PostConvertFunc = nullptr;` — Function to be called after setting up the sample conversion graph

#### class `UE::RivermaxMedia::FRivermaxMediaTextureSampleConverter`  
`class FRivermaxMediaTextureSampleConverter : public FMediaIOCoreTextureSampleConverter`  
_L35-39_
- inherits: `FMediaIOCoreTextureSampleConverter`
- L38 _public prototype_ `virtual uint32 GetConverterInfoFlags() const override;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace RivermaxMedia` (scope `UE`)
- L18 _typedef_ `using FPreInputConvertFunc = TUniqueFunction<void(FRDGBuilder& GraphBuilder)>;` (scope `UE::RivermaxMedia`)
- L19 _typedef_ `using FGetGPUBufferFunc = TFunction<TRefCountPtr<FRDGPooledBuffer>()>;` (scope `UE::RivermaxMedia`)
- L20 _typedef_ `using FPostInputConvertFunc = TUniqueFunction<void(FRDGBuilder& GraphBuilder)>;` (scope `UE::RivermaxMedia`)

### `Plugins/VirtualProduction/Rivermax/RivermaxMedia/Source/RivermaxMedia/Private/RivermaxMediaUtils.h` (Private)


#### struct `UE::RivermaxMediaUtils::Private::FSourceBufferDesc`  
`struct FSourceBufferDesc`  
_L15-19_
- L17 _public member_ `uint32 BytesPerElement = 0;`
- L18 _public member_ `uint32 NumberOfElements = 0;`

#### struct `UE::RivermaxMediaUtils::Private::FPayloadSizeInformation`  
`struct FPayloadSizeInformation`  
_L21-31_
- L24 _public member_ `bool bIsExactFit = false;` — True if an exact fit is found. I.e. a packet size was found that divides sample row without the remainder.
- L30 _public member_ `uint32 PayloadSize = 0;` — If an exact fit this PayloadSize will be used without padding the resolution. If not an exact fit then the PayloadSize will be used to pad the resolution to.

#### struct `FRivermaxMediaVersion`  
`struct FRivermaxMediaVersion`  
_L84-108_
- desc: Custom version to keep track of and restore depricated properties.
- L104 _public member_ `const static FGuid GUID;` — Rivermax Guild
- L107 _private function_ `FRivermaxMediaVersion()`

#### enum `FRivermaxMediaVersion::Type`  
`enum Type`  
_L86-101_
- L88 _public enumerator_ `BeforeCustomVersionAdded = 0`
- L91 _public enumerator_ `VideoStreamStruct = 1` — Flat video properties on URivermaxMediaSource moved into FRivermaxVideoStream VideoStream struct.
- L94 _public enumerator_ `AncTimecodeInput = 2` — ANC input stream configuration (AncStreams) added to URivermaxMediaSource.
- L97 _public enumerator_ `VersionPlusOne` — Add new versions above this comment.
- L98 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace RivermaxMediaUtils` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::RivermaxMediaUtils`)
- L34 _variable_ `static constexpr uint8 AncTimecodeDID = 0x60;` (scope `UE::RivermaxMediaUtils::Private`) — ATC LTC timecode DID/SDID per SMPTE ST 291-1.
- L35 _variable_ `static constexpr uint8 AncTimecodeSDID = 0x60;` (scope `UE::RivermaxMediaUtils::Private`)
- L38 _variable_ `static constexpr uint32 MaxPayloadSize = 1420;` (scope `UE::RivermaxMediaUtils::Private`) — Maximum payload size in bytes that the plugin can send based on UDP max size and RTP header.
- L45 _variable_ `static constexpr uint32 MinPayloadSize = 600;` (scope `UE::RivermaxMediaUtils::Private`) — Smallest payload size (bytes) to use as a lower bound in search for a payload that can be equal across a line. The smaller the packet size, the greater the overhead. More packets mean more RTP and UDP headers need to be included, and more processing is required as a result.
- L47 _prototype_ `UE::RivermaxCore::ESamplingType PixelFormatToRivermaxSamplingType(ERivermaxPixelFormat InPixelFormat);` (scope `UE::RivermaxMediaUtils::Private`)
- L48 _prototype_ `ERivermaxPixelFormat RivermaxSamplingTypeToPixelFormat(UE::RivermaxCore::ESamplingType InSamplingType);` (scope `UE::RivermaxMediaUtils::Private`)
- L49 _prototype_ `UE::RivermaxCore::ERivermaxAlignmentMode MediaOutputAlignmentToRivermaxAlignment(ERivermaxMediaAlignmentMode InAlignmentMode);` (scope `UE::RivermaxMediaUtils::Private`)
- L50 _prototype_ `UE::RivermaxCore::EFrameLockingMode MediaOutputFrameLockingToRivermax(ERivermaxFrameLockingMode InFrameLockingMode);` (scope `UE::RivermaxMediaUtils::Private`)
- L51 _prototype_ `FSourceBufferDesc GetBufferDescription(const FIntPoint& Resolution, ERivermaxPixelFormat InPixelFormat);` (scope `UE::RivermaxMediaUtils::Private`)
- L64 _prototype_ `FIntVector GetComputeShaderGroupCount(uint32 NumberOfElements);` (scope `UE::RivermaxMediaUtils::Private`) — Computes the dispatch group count for a 2110 buffer conversion compute shader. Each group in the shader is declared as [numthreads(512,1,1)], which means 512 threads are launched per group. In the future we should consider using multi dimensional dispatch group count with a smaller group size. NumberOfElements - The total number of elements (e.g. pixels or items) that need to be processed. Returns FIntVector giving the number of groups to dispatch in each dimension. It needs to reflect DISPATCH_GROUP_COUNT in RivermaxShaders.usf.
- L67 _prototype_ `FIntPoint GetAlignedResolution(const UE::RivermaxCore::FVideoFormatInfo& InFormatInfo, const FIntPoint& ResolutionToAlign);` (scope `UE::RivermaxMediaUtils::Private`) — Gets a resolution aligned to a pixel group specified for the provided video format as per 2110-20 requirements.
- L73 _prototype_ `bool StreamOptionsToSDPDescription(const UE::RivermaxCore::FRivermaxOutputOptions& Options, TArray<char>& OutSDPDescription);` (scope `UE::RivermaxMediaUtils::Private`) — Convert a set of streaming option to its SDP description. Returns true if SDP could successfully be created from rivermax options.
- L80 _prototype_ `void FindPayloadSize(uint32 InBytesPerLine, const uint32 PixelGroupSize, FPayloadSizeInformation& OutPayloadSizeInformation);` (scope `UE::RivermaxMediaUtils::Private`) — Find the right size for the data portion of the UDP packet. It is generally desired to maximize the size of the packet and make it as close possible to the maximum UDP packet size which is typically 1500 with the header. OutPayloadSizeInformation contains information about the packet that requires smallest padding if an exact packet that fits equal number of bytes isn't found.

### `Plugins/VirtualProduction/Rivermax/RivermaxMedia/Source/RivermaxMedia/Public/IRivermaxMediaModule.h` (Public)


#### class `IRivermaxMediaModule`  
`class IRivermaxMediaModule : public IModuleInterface`  
_L17-36_
- inherits: `IModuleInterface`
- L20 _public function_ `static inline IRivermaxMediaModule& Get()`
- L25 _public function_ `static inline bool IsAvailable()`
- L35 _public prototype_ `virtual TSharedPtr<IMediaPlayer> CreatePlayer(IMediaEventSink& EventSink) = 0;` — Create a Rivermax based media player. @param EventSink The object that receives media events from the player. @return A new media player, or nullptr if a player couldn't be created.

### `Plugins/VirtualProduction/Rivermax/RivermaxMedia/Source/RivermaxMedia/Public/RivermaxCustomTimeStep.h` (Public)


#### class `URivermaxCustomTimeStep`  
`class URivermaxCustomTimeStep : public UGenlockedCustomTimeStep`  
_L16-92_
- reflection: `UCLASS(Blueprintable, editinlinenew)`
- inherits: `UGenlockedCustomTimeStep`
- desc: Genlock using PTP time from a rivermax card
- L22 _public prototype_ `virtual bool Initialize(UEngine* InEngine) override;`
- L23 _public prototype_ `virtual void Shutdown(UEngine* InEngine) override;`
- L24 _public prototype_ `virtual bool UpdateTimeStep(UEngine* InEngine) override;`
- L25 _public prototype_ `virtual ECustomTimeStepSynchronizationState GetSynchronizationState() const override;`
- L26 _public prototype_ `virtual FFrameRate GetFixedFrameRate() const override;`
- L30 _public prototype_ `virtual uint32 GetLastSyncCountDelta() const override;`
- L31 _public prototype_ `virtual bool IsLastSyncDataValid() const override;`
- L32 _public prototype_ `virtual FFrameRate GetSyncRate() const override;`
- L33 _public prototype_ `virtual bool WaitForSync() override;`
- L37 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L44 _private prototype_ `bool WaitForNextFrame();` — Waits for the next frame based on frame rate settings
- L47 _private prototype_ `void OnRivermaxManagerInitialized();` — We wait for Rivermax Manager to be initialized to do final verification before going to Synchronized state`
- L50 _private prototype_ `void EnableMonitoring();` — Adds current frame rate to boundary monitor
- L53 _private prototype_ `void DisableMonitoring();` — Removes current frame rate to boundary monitor
- L59 _public member_ `FFrameRate FrameRate = FFrameRate(24,1);` — `UPROPERTY(EditAnywhere, Category = "Genlock options")` — Target frame rate to which to genlock. Uses ST2059 standard to align PTP time to standard genlock
- L63 _public member_ `double AlignmentPointDelayMS = 0;` — `UPROPERTY(EditAnywhere, Category = "Genlock options")` — Delay from alignment point at which we tick the engine, in milliseconds
- L67 _public member_ `bool bEnableOverrunDetection = true;` — `UPROPERTY(EditAnywhere, Category = "Genlock options", meta = (DisplayName = "Display Dropped Frames Warning"), AdvancedDisplay)` — When enabled, will warn for skipped frames when engine is too slow
- L74 _private member_ `TObjectPtr<UEngine> InitializedEngine = nullptr;` — `UPROPERTY(Transient)` — Engine used to initialize the Provider
- L78 _private member_ `ECustomTimeStepSynchronizationState State = ECustomTimeStepSynchronizationState::Closed;` — The current SynchronizationState of this custom timestep
- L80 _private member_ `bool bIgnoreWarningForOneFrame = true;`
- L83 _private member_ `bool bIsPreviousFrameNumberValid = false;` — Frame number tracking
- L84 _private member_ `uint64 PreviousFrameNumber = 0;`
- L85 _private member_ `uint64 DeltaFrameNumber = 0;`
- L88 _private member_ `FGuid BoundaryMonitorListener;` — Frame boundary monitoring ID
- L91 _private member_ `FFrameRate CachedFrameRate;` — Cached frame rate used for boundary monitoring

### `Plugins/VirtualProduction/Rivermax/RivermaxMedia/Source/RivermaxMedia/Public/RivermaxMediaCapture.h` (Public)


#### class `URivermaxMediaCapture`  
`class URivermaxMediaCapture : public UMediaCapture, public UE::RivermaxCore::IRivermaxOutputStreamListener`  
_L21-118_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMediaCapture,UE::RivermaxCore::IRivermaxOutputStreamListener`
- desc: Output Media for Rivermax streams.
- L27 _public prototype_ `UE::RivermaxCore::FRivermaxOutputOptions GetOutputOptions() const;` — Rivermax capture specific API to provide stream options access
- L30 _public prototype_ `void GetLastPresentedFrameInformation(UE::RivermaxCore::FPresentedFrameInfo& OutFrameInfo) const;` — Returns information about last presented frame on the output stream
- L33 _public prototype_ `virtual void WaitForGPU(FRHITexture* InRHITexture) override;` — In cases of GPUDirect we should manually wait for work to be done.
- L38 _public prototype_ `virtual bool HasFinishedProcessing() const override;`
- L40 _protected prototype_ `virtual bool ValidateMediaOutput() const override;`
- L41 _protected prototype_ `virtual bool InitializeCapture() override;`
- L42 _protected prototype_ `virtual bool UpdateSceneViewportImpl(TSharedPtr<FSceneViewport>& InSceneViewport) override;`
- L43 _protected prototype_ `virtual bool UpdateRenderTargetImpl(UTextureRenderTarget2D* InRenderTarget) override;`
- L44 _protected prototype_ `virtual void StopCaptureImpl(bool bAllowPendingFrameToBeProcess) override;`
- L45 _protected prototype_ `virtual bool ShouldCaptureRHIResource() const override;`
- L46 _protected prototype_ `virtual void OnFrameCaptured_RenderingThread(const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, void* InBuffer, int32 Width, int32 Height, int32 BytesPerRow) override;`
- L47 _protected prototype_ `virtual void OnRHIResourceCaptured_RenderingThread(FRHICommandListImmediate& RHICmdList, const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, FBufferRHIRef InBuffer) override;`
- L48 _protected prototype_ `virtual void OnRHIResourceCaptured_AnyThread(const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, FBufferRHIRef InBuffer) override;`
- L49 _protected prototype_ `virtual void OnFrameCaptured_AnyThread(const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, const FMediaCaptureResourceData& InResourceData) override;`
- L50 _protected function_ `virtual bool SupportsAnyThreadCapture() const override`
- L54 _protected function_ `virtual bool SupportsAutoRestart() const`
- L60 _protected prototype_ `virtual FIntPoint GetCustomOutputSize(const FIntPoint& InSize) const override;` — For custom conversion, methods that need to be overriden
- L61 _protected prototype_ `virtual EMediaCaptureResourceType GetCustomOutputResourceType() const override;`
- L62 _protected prototype_ `virtual FRDGBufferDesc GetCustomBufferDescription(const FIntPoint& InDesiredSize) const override;`
- L63 _protected prototype_ `virtual void OnCustomCapture_RenderingThread(FRDGBuilder& GraphBuilder, const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, FRDGTextureRef InSourceTexture, FRDGBufferRef OutputBuffer, const FRHICopyTextureInfo& CopyInfo, FVector2D CropU, FVector2D CropV) override;`
- L64 _protected function_ `virtual bool IsOutputSynchronizationSupported() const override`
- L67 _protected prototype_ `virtual FString GetAnalyticsEventPrefix() const override;`
- L68 _protected prototype_ `virtual void GetAnalyticsEventAttributes(const FString& EventName, TArray<FAnalyticsEventAttribute>& InOutAttributes) const override;`
- L73 _protected prototype_ `virtual bool IsReadyForFinishDestroy();`
- L77 _protected prototype_ `virtual void OnInitializationCompleted(bool bHasSucceed) override;`
- L78 _protected prototype_ `virtual void OnStreamError() override;`
- L79 _protected prototype_ `virtual void OnPreFrameEnqueue() override;`
- L86 _private prototype_ `bool Initialize(const UE::RivermaxCore::FRivermaxOutputOptions& InMediaOutput);` — Initializes capture and launches stream creation.
- L93 _private prototype_ `bool ConfigureCapture() const;` — Checks whether the provided options are valid to start the capture. Resolves the interface address and ensures the resolution is aligned to the nearest pixel group. Returns false if the stream cannot be configured based on the provided settings.
- L96 _private prototype_ `void AddFrameReservationPass(FRDGBuilder& GraphBuilder);` — Enqueues a RHI lambda to reserve a spot for the next frame to capture
- L99 _private prototype_ `void OnFrameCapturedInternal_AnyThread(const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, void* InBuffer, int32 Width, int32 Height, int32 BytesPerRow);` — Common method called for non gpudirect route when a frame is captured, either from render thread or any thread
- L102 _private prototype_ `void OnRHIResourceCapturedInternal_AnyThread(const FCaptureBaseData& InBaseData, TSharedPtr<FMediaCaptureUserData, ESPMode::ThreadSafe> InUserData, FBufferRHIRef InBuffer);` — Common method called for gpudirect route when a frame is captured, either from render thread or any thread
- L106 _private member_ `TStaticArray<TUniquePtr<UE::RivermaxCore::IRivermaxOutputStream>, static_cast<uint32>(UE::RivermaxCore::ERivermaxStreamType::MAX)> Streams;`
- L108 _private member_ `UE::RivermaxCore::FRivermaxOutputOptions Options;` — Set of options used to configure output stream
- L111 _private member_ `TRefCountPtr<FRHIGPUFence> ShaderCompletedRenderingFence;` — When using GPUDirect we have to rely on our own fence to wait for output to be converted into buffer. This will be waited for in WaitForGPU function.
- L114 _private member_ `TSharedPtr<FEvent, ESPMode::ThreadSafe> GPUWaitCompleteEvent;` — Used with GPUDirect An Event used to block from render thread writing a fence again when we wait for it.
- L117 _private member_ `std::atomic<bool> bIsActive;` — Whether capture is active. Used to be queried by sync task

### `Plugins/VirtualProduction/Rivermax/RivermaxMedia/Source/RivermaxMedia/Public/RivermaxMediaOutput.h` (Public)


#### enum `ERivermaxMediaAlignmentMode`  
`enum class ERivermaxMediaAlignmentMode : uint8`  
_L16-28_
- reflection: `UENUM()`
- L21 _public enumerator_ `AlignmentPoint` — Uses NVIDIA Rivermax clock to calculate alignment points based on ST2059
- L27 _public enumerator_ `FrameCreation` — Aligns frame scheduling with frame creation not going faster than frame interval In its current shape, useful for a faster stream than frame creation rate

#### enum `ERivermaxFrameLockingMode`  
`enum class ERivermaxFrameLockingMode : uint8`  
_L34-41_
- reflection: `UENUM()`
- desc: Controls how rivermax capture behaves when there are no buffers available to capture into
- L37 _public enumerator_ `FreeRun` — If no frame available, continue
- L40 _public enumerator_ `BlockOnReservation` — Blocks RHI thread prior to capture the current frame if no space is available.

#### class `URivermaxMediaOutput`  
`class URivermaxMediaOutput : public UMediaOutput`  
_L48-165_
- reflection: `UCLASS(BlueprintType, meta=(MediaIOCustomLayout="Rivermax", DisplayName = "NVIDIA Rivermax Output"))`
- inherits: `UMediaOutput`
- desc: Output information for a Rivermax media capture.
- L55 _public prototype_ `virtual bool Validate(FString& FailureReason) const override;`
- L56 _public prototype_ `virtual FIntPoint GetRequestedSize() const override;`
- L57 _public prototype_ `virtual EPixelFormat GetRequestedPixelFormat() const override;`
- L58 _public prototype_ `virtual EMediaCaptureConversionOperation GetConversionOperation(EMediaCaptureSourceType InSourceType) const override;`
- L61 _public prototype_ `virtual FString GetDescriptionString() const override;`
- L62 _public prototype_ `virtual void GetDetailsPanelInfoElements(TArray<FInfoElement>& OutInfoElements) const override;`
- L68 _public prototype_ `void ExportSDP(const FString& InPath);` — Saves SDP into the file fath.
- L71 _public prototype_ `UE::RivermaxCore::FRivermaxOutputOptions GenerateStreamOptions() const;` — Aggregates URivermaxMediaOutput settings into FRivermaxOutputOptions that have information about individual stream types.
- L74 _protected prototype_ `virtual UMediaCapture* CreateMediaCaptureImpl() override;`
- L80 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L81 _public prototype_ `virtual void PostLoad() override;`
- L83 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L84 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L90 _public member_ `ERivermaxMediaAlignmentMode AlignmentMode = ERivermaxMediaAlignmentMode::AlignmentPoint;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Output")` — Used by frame scheduler to know how to align the output
- L97 _public member_ `bool bDoContinuousOutput = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Output", meta = (EditCondition = "AlignmentMode != ERivermaxMediaAlignmentMode::FrameCreation"))` — Whether to produce a continuous output stream repeating last frame if no new frames provided Note: Not supported in frame creation mode
- L101 _public member_ `ERivermaxFrameLockingMode FrameLockingMode = ERivermaxFrameLockingMode::FreeRun;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Output")` — For alignment point mode, controls whether we stall engine before capturing if there are no buffer available to capture into
- L106 _public member_ `int32 PresentationQueueSize_DEPRECATED = 2;` — `UE_DEPRECATED(5.8, "PresentationQueueSize is deprecated in favor of NumberOfTextureBuffers from UMediaOutput.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use UMediaOutput::NumberOfTextureBuffers instead."))` — DEPRECATED: Formally controlled the number of frames that could be queued / used in output queue.
- L113 _public member_ `bool bDoFrameCounterTimestamping = true;` — `UPROPERTY(EditAnywhere, Category = "Output", meta = (EditCondition = "AlignmentMode == ERivermaxMediaAlignmentMode::FrameCreation"))` — Experimental flag to use frame counter instead of using NVIDIA Rivermax clock for timestamping output frames Meant to be used for UE-UE streams where frame locking is done, e.g. nDisplay.
- L120 _public member_ `bool bOverrideResolution_DEPRECATED = false;` — `UE_DEPRECATED(5.7, "Override Resolution is deprecated. Use (Video Stream)->(Override Resolution) instead.")` — `UPROPERTY()` — If false, use the default source buffer size. If true, a specific resolution will be used.
- L125 _public member_ `FIntPoint Resolution_DEPRECATED = { 1920, 1080 };` — `UE_DEPRECATED(5.7, "Resolution is deprecated. Use (Video Stream)->(Resolution) instead.")` — `UPROPERTY()` — Resolution of this output stream
- L130 _public member_ `FFrameRate FrameRate_DEPRECATED = { 24,1 };` — `UE_DEPRECATED(5.7, "Frame Rate is deprecated. Use (Video Stream)->(Frame Rate) instead.")` — `UPROPERTY()` — Frame rate of this output stream
- L135 _public member_ `ERivermaxPixelFormat PixelFormat_DEPRECATED = ERivermaxPixelFormat::RGB_10bit;` — `UE_DEPRECATED(5.7, "Pixel Format is deprecated. Use (Video Stream)->(Pixel Format) instead.")` — `UPROPERTY()` — Pixel format for this output stream
- L139 _public member_ `FString InterfaceAddress_DEPRECATED = TEXT("*.*` — `UE_DEPRECATED(5.7, "Interface Address is deprecated. Use (Anc Stream) or (Video Stream)->(Interface Address) instead.")` — `UPROPERTY()`
- L143 _public member_ `FString StreamAddress_DEPRECATED = UE::RivermaxCore::DefaultStreamAddress;` — `UE_DEPRECATED(5.7, "Stream Address is deprecated. Use (Anc Stream) or (Video Stream)->(Stream Address) instead.")` — `UPROPERTY()`
- L148 _public member_ `int32 Port_DEPRECATED = 50000;` — `UE_DEPRECATED(5.7, "Port is deprecated. Use (Anc Stream) or (Video Stream)->(Port) instead.")` — `UPROPERTY()` — Port to use for this output
- L153 _public member_ `bool bUseGPUDirect_DEPRECATED = true;` — `UE_DEPRECATED(5.7, "Use GPU Direct is deprecated. Use Video->(GPU Direct) instead.")` — `UPROPERTY()` — Whether to use GPUDirect if available (Memcopy from GPU to NIC directly bypassing system) if available
- L157 _public member_ `FRivermaxVideoStream VideoStream;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Video")` — Video output stream properties.
- L161 _public member_ `TArray<FRivermaxAncStream> AncStreams;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anc")` — Collection of Ancillary streams.

### `Plugins/VirtualProduction/Rivermax/RivermaxMedia/Source/RivermaxMedia/Public/RivermaxMediaSource.h` (Public)


#### class `URivermaxMediaSource`  
`class URivermaxMediaSource : public UCaptureCardMediaSource`  
_L17-97_
- reflection: `UCLASS(BlueprintType, hideCategories=(Platforms,Object), meta=(MediaIOCustomLayout="Rivermax", DisplayName = "NVIDIA Rivermax Source"))`
- inherits: `UCaptureCardMediaSource`
- desc: Media source for Rivermax streams.
- L23 _public prototype_ `URivermaxMediaSource();`
- L29 _public member_ `FRivermaxVideoStream VideoStream;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Video")` — Video input stream properties.
- L33 _public member_ `TArray<FRivermaxAncStream> AncStreams;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ANC")` — ANC (ST 2110-40) input streams. Add entries to receive ancillary data.
- L38 _public member_ `bool bOverrideResolution = false;` — `UE_DEPRECATED(5.8, "Override Resolution is deprecated. Use (Video Stream)->(Override Resolution) instead.")` — `UPROPERTY()` — If false, use the default source buffer size. If true, a specific resolution will be used.
- L43 _public member_ `FIntPoint Resolution = {1920, 1080};` — `UE_DEPRECATED(5.8, "Resolution is deprecated. Use (Video Stream)->(Resolution) instead.")` — `UPROPERTY()` — Incoming stream video resolution
- L48 _public member_ `FFrameRate FrameRate = {24,1};` — `UE_DEPRECATED(5.8, "Frame Rate is deprecated. Use (Video Stream)->(Frame Rate) instead.")` — `UPROPERTY()` — Incoming stream video frame rate
- L53 _public member_ `ERivermaxPixelFormat PixelFormat = ERivermaxPixelFormat::RGB_10bit;` — `UE_DEPRECATED(5.8, "Pixel Format is deprecated. Use (Video Stream)->(Pixel Format) instead.")` — `UPROPERTY()` — Incoming stream pixel format
- L58 _public member_ `FString InterfaceAddress = TEXT("*.*` — `UE_DEPRECATED(5.8, "Interface Address is deprecated. Use (Video Stream)->(Interface Address) instead.")` — `UPROPERTY()` — Network card interface to use to receive data
- L63 _public member_ `FString StreamAddress = UE::RivermaxCore::DefaultStreamAddress;` — `UE_DEPRECATED(5.8, "Stream Address is deprecated. Use (Video Stream)->(Stream Address) instead.")` — `UPROPERTY()` — IP address where incoming stream is coming from
- L68 _public member_ `int32 Port = 50000;` — `UE_DEPRECATED(5.8, "Port is deprecated. Use (Video Stream)->(Port) instead.")` — `UPROPERTY()` — Port used by the sender to send its stream
- L73 _public member_ `bool bUseGPUDirect = true;` — `UE_DEPRECATED(5.8, "Use GPU Direct is deprecated. Use (Video Stream)->(GPU Direct) instead.")` — `UPROPERTY()` — Whether to use GPUDirect if available
- L77 _public prototype_ `virtual bool GetMediaOption(const FName& Key, bool DefaultValue) const override;`
- L78 _public prototype_ `virtual int64 GetMediaOption(const FName& Key, int64 DefaultValue) const override;`
- L79 _public prototype_ `virtual FString GetMediaOption(const FName& Key, const FString& DefaultValue) const override;`
- L80 _public prototype_ `virtual bool HasMediaOption(const FName& Key) const override;`
- L83 _public prototype_ `virtual void PostLoad() override;`
- L84 _public prototype_ `void Serialize(FArchive& Ar) override;`
- L88 _public prototype_ `virtual FString GetUrl() const override;`
- L89 _public prototype_ `virtual bool Validate() const override;`
- L92 _public prototype_ `virtual FString GetDescriptionString() const override;`
- L93 _public prototype_ `virtual void GetDetailsPanelInfoElements(TArray<FInfoElement>& OutInfoElements) const override;`

### `Plugins/VirtualProduction/Rivermax/RivermaxMedia/Source/RivermaxMedia/Public/RivermaxMediaTypes.h` (Public)


#### struct `FRivermaxStream`  
`struct FRivermaxStream`  
_L12-30_
- reflection: `USTRUCT(BlueprintType)`
- desc: Base struct shared by all Rivermax stream config structs (output and input).
- L21 _public member_ `FString InterfaceAddress = TEXT("*.*` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — Network card interface to use. Wildcards are supported: 192.*.0.110, 192.168.0.1?0, 192.168.0.1*
- L25 _public member_ `FString StreamAddress = UE::RivermaxCore::DefaultStreamAddress;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — Multicast IP address of the stream
- L29 _public member_ `int32 Port = 50000;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — UDP port of the stream

#### enum `ERivermaxAncStreamType`  
`enum class ERivermaxAncStreamType : uint8`  
_L41-45_
- reflection: `UENUM(BlueprintType)`
- desc: ANC stream type. None disables the stream. Anc specific reflection of UE::RivermaxCore::ERivermaxStreamType, for ease of access ST2110_40_TC starts at 3 to reflect ERivermaxStreamType. ST2110_20 = 0, ST2110_30 = 1, ST2110_40 = 2, - general ANC
- L43 _public enumerator_ `None = 0 UMETA(DisplayName = "None")`
- L44 _public enumerator_ `ST2110_40_TC = 3 UMETA(DisplayName = "ST 2110-40 (Timecode)")`

#### struct `FRivermaxAncStream`  
`struct FRivermaxAncStream : public FRivermaxStream`  
_L49-56_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRivermaxStream`
- desc: All settings required to initialize an ANC (2110-40) stream (input or output).
- L55 _public member_ `ERivermaxAncStreamType StreamType = ERivermaxAncStreamType::None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — ANC stream type such as Timecode. Set to None to disable.

#### enum `ERivermaxPixelFormat`  
`enum class ERivermaxPixelFormat : uint8`  
_L60-68_
- reflection: `UENUM(BlueprintType)`
- desc: Pixel format used by ST 2110-20 video streams (input and output).
- L62 _public enumerator_ `YUV422_8bit UMETA(DisplayName = "8bit YUV422")`
- L63 _public enumerator_ `YUV422_10bit UMETA(DisplayName = "10bit YUV422")`
- L64 _public enumerator_ `RGB_8bit UMETA(DisplayName = "8bit RGB")`
- L65 _public enumerator_ `RGB_10bit UMETA(DisplayName = "10bit RGB")`
- L66 _public enumerator_ `RGB_12bit UMETA(DisplayName = "12bit RGB")`
- L67 _public enumerator_ `RGB_16bit_Float UMETA(DisplayName = "16bit Float RGB")`

#### struct `FRivermaxVideoStream`  
`struct FRivermaxVideoStream : public FRivermaxStream`  
_L72-95_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FRivermaxStream`
- desc: Shared settings for an ST 2110-20 video stream (input or output).
- L78 _public member_ `FFrameRate FrameRate = {24, 1};` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — Frame rate of this stream
- L82 _public member_ `bool bOverrideResolution = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings", meta = (InlineEditConditionToggle))` — If false, use the size provided by the source. If true, a specific resolution will be used.
- L86 _public member_ `FIntPoint Resolution = {1920, 1080};` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (EditCondition = "bOverrideResolution"))` — Stream resolution
- L90 _public member_ `ERivermaxPixelFormat PixelFormat = ERivermaxPixelFormat::RGB_10bit;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — Pixel format
- L94 _public member_ `bool bUseGPUDirect = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Settings")` — Whether to use GPUDirect if available (memory transfer bypassing system memory)

### `Plugins/VirtualProduction/Rivermax/RivermaxMedia/Source/RivermaxMedia/Public/RivermaxTimecodeProvider.h` (Public)


#### class `URivermaxTimecodeProvider`  
`class URivermaxTimecodeProvider : public UGenlockedTimecodeProvider`  
_L27-73_
- reflection: `UCLASS(Blueprintable, editinlinenew)`
- inherits: `UGenlockedTimecodeProvider`
- desc: Timecode provider based on time returned by Rivermax GetTime API Rivermax clock is configured using Project Setting. If using multiple interfaces, make sure to configure the interface address you wish to use. PTP time is returned in International Atomic Time referential (TAI) as opposed to Coordinated Universal Time (UTC) Timecode going out of the clock generator is generally using UTC time reference so to generate an engine timecode that aligns with devices receiving LTC timecode, we need to convert PTP TAI time to UTC time. At the moment, that offset is fixed at 37 seconds. Clock generators can also output timecode with daylight saving time (DST) offsets which would not be affecting PTP time reference If devices receive timecode with DST offsets, engine timecode will need to be adjusted to correctly align.
- L33 _public prototype_ `virtual bool FetchTimecode(FQualifiedFrameTime& OutFrameTime) override;`
- L34 _public function_ `virtual ETimecodeProviderSynchronizationState GetSynchronizationState() const override`
- L35 _public prototype_ `virtual bool Initialize(class UEngine* InEngine) override;`
- L36 _public prototype_ `virtual void Shutdown(class UEngine* InEngine) override;`
- L37 _public function_ `virtual bool SupportsAutoDetected() const override`
- L46 _public member_ `FFrameRate FrameRate = FFrameRate(24, 1);` — `UPROPERTY(EditAnywhere, Category = "Genlock options")` — Frame Rate to provide timecode in
- L56 _public member_ `int32 PTPToLTCTimecodeFrameOffset = 1;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Genlock options")` — Frame offset subtracted to converted timecode to match LTC timecode due to transportation of timecode For LTC, it takes a full frame to transport the new value but for PTP, this doesn't happen, time is local. If a timecoded video feed is coming into Unreal, if PTP timecode isn't offset, it will be leading by 1 frame. A value of 1 means PTP timecode is 1 frame ahead so we substract 1 frame to the result A value of -1 would mean PTP is late by one frame compared to LTC so we add a frame to the result.
- L60 _public member_ `int32 UTCSecondsOffset = 37;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Genlock options")` — TAI to UTC time offset. TAI is currently 37 seconds ahead so we substract 37 seconds to PTP time to convert to UTC.
- L67 _public member_ `int32 DaylightSavingTimeHourOffset = 0;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Genlock options")` — If timecode generated by the clock generator has daylight saving applied, add offset here in order to match PTP based timecode with devices getting LTC timecode A positive value will be subtracted from the timecode generated from PTP time.
- L72 _private member_ `ETimecodeProviderSynchronizationState State = ETimecodeProviderSynchronizationState::Closed;` — The current SynchronizationState of the TimecodeProvider
