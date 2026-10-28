# Plugins / BlackmagicCore

- module root: `Plugins/Media/BlackmagicMedia/Source/BlackmagicCore`
- headers: 16; symbols: 726
- symbol kinds: class=16, delegate=1, enum=12, enumerator=39, function=43, macro=8, member=290, namespace=25, prototype=254, struct=33, typedef=4, union=1
- PrivateDependencyModuleNames: BlackmagicSDK, GPUTextureTransfer, MediaIOCore
- PublicDependencyModuleNames: Core, Engine, RHI

### `Plugins/Media/BlackmagicMedia/Source/BlackmagicCore/Private/BlackmagicDevice.h` (Private)


#### class `BlackmagicDesign::Private::FDevice`  
`class FDevice`  
_L15-63_
- L18 _public function_ `static FDevice* GetDevice()`
- L19 _public prototype_ `static void CreateInstance();`
- L20 _public prototype_ `static void DestroyInstance();`
- L23 _public prototype_ `FUniqueIdentifier RegisterChannel(const FChannelInfo& InChannelInfo, const FInputChannelOptions& InInputChannelOptions, ReferencePtr<IInputEventCallback> InCallback);`
- L24 _public prototype_ `void UnregisterCallbackForChannel(const FChannelInfo& InChannelInfo, FUniqueIdentifier InIdentifier);`
- L25 _public prototype_ `FUniqueIdentifier RegisterOutputChannel(const FChannelInfo& InChannelInfo, const FOutputChannelOptions& InChannelOptions, ReferencePtr<IOutputEventCallback> InCallback);`
- L26 _public prototype_ `void UnregisterOutputChannel(const FChannelInfo& InChannelInfo, FUniqueIdentifier InIdentifier);`
- L27 _public prototype_ `bool SendVideoFrameData(const FChannelInfo& InChannelInfo, const FFrameDescriptor& InFrame);`
- L28 _public prototype_ `bool ShouldCaptureThisFrame(const FChannelInfo& InChannelInfo, ::FTimecode Timecode, uint32 FrameNumber);`
- L29 _public prototype_ `bool SendVideoFrameData(const FChannelInfo& InChannelInfo, FFrameDescriptor_GPUDMA& InFrame);`
- L30 _public prototype_ `bool SendAudioSamples(const FChannelInfo& InChannelInfo, const FAudioSamplesDescriptor& InSamples);`
- L39 _public prototype_ `void Thread_CommandThread();`
- L42 _private prototype_ `void AddCommand(FCommand* InCommand);`
- L43 _private prototype_ `FOutputChannel* FindChannel(const FChannelInfo& InChannelInfo);`
- L46 _private member_ `static FDevice* DeviceInstance;`
- L47 _private prototype_ `FDevice();`
- L48 _private prototype_ `~FDevice();`
- L49 _private prototype_ `FDevice(const FDevice&) = delete;`
- L50 _private prototype_ `FDevice& operator=(const FDevice&) = delete;`
- L53 _public member_ `std::vector<FInputChannel*> Channels;`
- L54 _public member_ `std::vector<FOutputChannel*> OutputChannels;`
- L55 _public member_ `std::mutex ChannelsMutex;`
- L58 _private member_ `std::condition_variable CommandVariable;`
- L59 _private member_ `std::mutex CommandMutex;`
- L60 _private member_ `std::thread CommandThread;`
- L61 _private member_ `std::vector<FCommand*> Commands;`
- L62 _private member_ `volatile bool bIsCommandThreadRunning;`

#### struct `BlackmagicDesign::Private::FDevice::FCommand`  
`struct FCommand`  
_L32-37_
- L34 _public function_ `virtual ~FCommand()`
- L35 _public prototype_ `virtual void Execute() = 0;`
- L36 _public prototype_ `virtual bool MustExecuteOnShutdown() const = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace BlackmagicDesign`
- L10 _namespace_ `namespace Private` (scope `BlackmagicDesign`)

### `Plugins/Media/BlackmagicMedia/Source/BlackmagicCore/Private/BlackmagicDeviceScanner.h` (Private)


#### class `BlackmagicDesign::Private::DeviceScanner`  
`class DeviceScanner`  
_L16-34_
- desc: DeviceScanner definition
- L19 _public prototype_ `DeviceScanner();`
- L20 _public prototype_ `~DeviceScanner();`
- L22 _public prototype_ `DeviceScanner(const DeviceScanner&) = delete;`
- L23 _public prototype_ `DeviceScanner& operator=(const DeviceScanner&) = delete;`
- L25 _public prototype_ `int32_t GetNumDevices() const;`
- L26 _public prototype_ `bool GetDeviceTextId(int32_t InDeviceIndex, BlackmagicDesign::BlackmagicDeviceScanner::FormatedTextType& OutTextId) const;`
- L27 _public prototype_ `bool GetDeviceInfo(int32_t InDeviceIndex, BlackmagicDesign::BlackmagicDeviceScanner::DeviceInfo& OutDeviceInfo) const;`
- L30 _private prototype_ `IDeckLink* GetDevice(int32_t InDeviceIndex) const;`
- L33 _private member_ `std::vector<IDeckLink*> Devices;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace BlackmagicDesign`
- L12 _namespace_ `namespace Private` (scope `BlackmagicDesign`)

### `Plugins/Media/BlackmagicMedia/Source/BlackmagicCore/Private/BlackmagicHelper.h` (Private)


#### struct `BlackmagicDesign::Private::UniqueIdentifierGenerator`  
`struct UniqueIdentifierGenerator`  
_L16-23_
- L19 _public member_ `static const int32_t InvalidId;`
- L20 _public prototype_ `static FUniqueIdentifier GenerateNextUniqueIdentifier();`
- L22 _private member_ `static std::atomic_char32_t CurrentId;`

#### struct `BlackmagicDesign::Private::Helpers`  
`struct Helpers`  
_L25-52_
- L28 _public prototype_ `static bool EPixelFormatToBMDPixelFormat(EPixelFormat InPixelFormat, BMDPixelFormat& OutPixelFormat);`
- L29 _public prototype_ `static bool ETimecodeFormatToBMDTimecodeFormat(ETimecodeFormat InTimecodeFormat, BMDTimecodeFormat& OutTimecodeFormat);`
- L30 _public prototype_ `static bool BMDPixelFormatToEPixelFormat(BMDPixelFormat InPixelFormat, EPixelFormat& OutPixelFormat, EFullPixelFormat& OutFullPixelFormat);`
- L31 _public prototype_ `static bool EFieldDominanceToBMDFieldDominance(EFieldDominance InFieldDominance, BMDFieldDominance& OutFieldDominance);`
- L32 _public prototype_ `static bool BMDFieldDominanceToEFieldDominance(BMDFieldDominance InFieldDominance, EFieldDominance & OutFieldDominance);`
- L33 _public prototype_ `static bool Is8Bits(BMDPixelFormat InPixelFormat);`
- L34 _public prototype_ `static bool Is8Bits(EPixelFormat InPixelFormat);`
- L35 _public prototype_ `static bool Is10Bits(BMDPixelFormat InPixelFormat);`
- L36 _public prototype_ `static bool Is10Bits(EPixelFormat InPixelFormat);`
- L37 _public prototype_ `static bool IsYUV(BMDPixelFormat InPixelFormat);`
- L38 _public prototype_ `static bool IsSDFormat(const BMDDisplayMode InMode);`
- L39 _public prototype_ `static bool IsHDFormat(const BMDDisplayMode InMode);`
- L40 _public prototype_ `static bool Is2kFormat(const BMDDisplayMode InMode);`
- L41 _public prototype_ `static bool Is4kFormat(const BMDDisplayMode InMode);`
- L42 _public prototype_ `static bool Is8kFormat(const BMDDisplayMode InMode);`
- L43 _public prototype_ `static bool IsInterlacedDisplayMode(const BMDDisplayMode InMode);`
- L44 _public prototype_ `static void BlockForAmountOfTime(float InSeconds);`
- L47 _public prototype_ `static IDeckLink* GetDeviceForIndex(int32_t InIndex);` — Returned DeckLink pointer must be released by the caller
- L48 _public prototype_ `static IDeckLink* GetDeviceForIdentifier(int64_t InIdentifier);`
- L50 _public prototype_ `static FTimecode AdjustTimecodeForUE(const FFormatInfo& InFormatInfo, const FTimecode& InTimecode, const FTimecode& InPreviousTimecode);`
- L51 _public prototype_ `static FTimecode AdjustTimecodeFromUE(const FFormatInfo& InFormatInfo, const FTimecode& InTimecode);`

#### struct `BlackmagicDesign::Private::UE_10Bit_PixelFormat`  
`struct UE_10Bit_PixelFormat`  
_L55-55_
- L55 _public member_ `struct UE_10Bit_PixelFormat { int32_t R : 10; int32_t G : 10; int32_t B : 10; int32_t A : 2; };`
- L55 _public member_ `struct UE_10Bit_PixelFormat { int32_t R : 10; int32_t G : 10; int32_t B : 10; int32_t A : 2; };`
- L55 _public member_ `struct UE_10Bit_PixelFormat { int32_t R : 10; int32_t G : 10; int32_t B : 10; int32_t A : 2; };`
- L55 _public member_ `struct UE_10Bit_PixelFormat { int32_t R : 10; int32_t G : 10; int32_t B : 10; int32_t A : 2; };`

#### struct `BlackmagicDesign::Private::bmd_10Bit_PixelFormat`  
`struct bmd_10Bit_PixelFormat`  
_L56-56_
- L56 _public member_ `struct bmd_10Bit_PixelFormat { int32_t Rh : 6; int32_t A : 2; int32_t Gh : 4; int32_t Rl : 4; int32_t Bh : 2; int32_t Gl : 6; int32_t Bl : 8; };`
- L56 _public member_ `struct bmd_10Bit_PixelFormat { int32_t Rh : 6; int32_t A : 2; int32_t Gh : 4; int32_t Rl : 4; int32_t Bh : 2; int32_t Gl : 6; int32_t Bl : 8; };`
- L56 _public member_ `struct bmd_10Bit_PixelFormat { int32_t Rh : 6; int32_t A : 2; int32_t Gh : 4; int32_t Rl : 4; int32_t Bh : 2; int32_t Gl : 6; int32_t Bl : 8; };`
- L56 _public member_ `struct bmd_10Bit_PixelFormat { int32_t Rh : 6; int32_t A : 2; int32_t Gh : 4; int32_t Rl : 4; int32_t Bh : 2; int32_t Gl : 6; int32_t Bl : 8; };`
- L56 _public member_ `struct bmd_10Bit_PixelFormat { int32_t Rh : 6; int32_t A : 2; int32_t Gh : 4; int32_t Rl : 4; int32_t Bh : 2; int32_t Gl : 6; int32_t Bl : 8; };`
- L56 _public member_ `struct bmd_10Bit_PixelFormat { int32_t Rh : 6; int32_t A : 2; int32_t Gh : 4; int32_t Rl : 4; int32_t Bh : 2; int32_t Gl : 6; int32_t Bl : 8; };`
- L56 _public member_ `struct bmd_10Bit_PixelFormat { int32_t Rh : 6; int32_t A : 2; int32_t Gh : 4; int32_t Rl : 4; int32_t Bh : 2; int32_t Gl : 6; int32_t Bl : 8; };`

#### union `BlackmagicDesign::Private::Conversion_UE_10Bit_to_bmd_10Bit`  
`union Conversion_UE_10Bit_to_bmd_10Bit`  
_L57-63_
- L62 _public member_ `int32_t UEColor : 10;`

#### struct `BlackmagicDesign::Private::Conversion_UE_10Bit_to_bmd_10Bit::(anonymous)`  
`struct`  
_L59-59_

#### struct `BlackmagicDesign::Private::Conversion_UE_10Bit_to_bmd_10Bit::(anonymous)`  
`struct`  
_L60-60_

#### struct `BlackmagicDesign::Private::Conversion_UE_10Bit_to_bmd_10Bit::(anonymous)`  
`struct`  
_L61-61_

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace BlackmagicDesign`
- L14 _namespace_ `namespace Private` (scope `BlackmagicDesign`)
- L59 _member_ `struct { int32_t bmdBl : 8; int32_t bmdBh : 2; };` (scope `BlackmagicDesign::Private::Conversion_UE_10Bit_to_bmd_10Bit::__anon9fad9a370108`)
- L59 _member_ `struct { int32_t bmdBl : 8; int32_t bmdBh : 2; };` (scope `BlackmagicDesign::Private::Conversion_UE_10Bit_to_bmd_10Bit::__anon9fad9a370108`)
- L60 _member_ `struct { int32_t bmdGl : 6; int32_t bmdGh : 4; };` (scope `BlackmagicDesign::Private::Conversion_UE_10Bit_to_bmd_10Bit::__anon9fad9a370208`)
- L60 _member_ `struct { int32_t bmdGl : 6; int32_t bmdGh : 4; };` (scope `BlackmagicDesign::Private::Conversion_UE_10Bit_to_bmd_10Bit::__anon9fad9a370208`)
- L61 _member_ `struct { int32_t bmdRl : 4; int32_t bmdRh : 6; };` (scope `BlackmagicDesign::Private::Conversion_UE_10Bit_to_bmd_10Bit::__anon9fad9a370308`)
- L61 _member_ `struct { int32_t bmdRl : 4; int32_t bmdRh : 6; };` (scope `BlackmagicDesign::Private::Conversion_UE_10Bit_to_bmd_10Bit::__anon9fad9a370308`)

### `Plugins/Media/BlackmagicMedia/Source/BlackmagicCore/Private/BlackmagicInputChannel.h` (Private)


#### class `BlackmagicDesign::Private::FInputChannelNotificationCallback`  
`class FInputChannelNotificationCallback : public IDeckLinkInputCallback`  
_L14-41_
- inherits: `IDeckLinkInputCallback`
- L17 _public prototype_ `FInputChannelNotificationCallback(FInputChannel* InOwner, IDeckLinkInput* InDeckLinkInput, IDeckLinkStatus* InDeckLinkStatus);`
- L18 _public prototype_ `virtual ~FInputChannelNotificationCallback() = default;`
- L20 _public prototype_ `HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, LPVOID *ppv);`
- L22 _public prototype_ `ULONG STDMETHODCALLTYPE AddRef();`
- L23 _public prototype_ `ULONG STDMETHODCALLTYPE Release();`
- L25 _public prototype_ `HRESULT STDMETHODCALLTYPE VideoInputFormatChanged(BMDVideoInputFormatChangedEvents InNotificationEvents, IDeckLinkDisplayMode* InNewDisplayMode, BMDDetectedVideoInputFormatFlags InDetectedSignalFlags);`
- L26 _public prototype_ `HRESULT STDMETHODCALLTYPE VideoInputFrameArrived(IDeckLinkVideoInputFrame* InVideoFrame, IDeckLinkAudioInputPacket* InAudioPacket);`
- L29 _private prototype_ `void GetHDRMetaData(IInputEventCallback::FFrameReceivedInfo& FrameInfo, IDeckLinkVideoInputFrame* InVideoFrame);`
- L30 _private prototype_ `double GetFloatMetaData(IDeckLinkVideoFrameMetadataExtensions* MetadataExtensions, BMDDeckLinkFrameMetadataID MetaDataID);`
- L31 _private prototype_ `bool IsHDRLoggingOK();`
- L33 _private member_ `FInputChannel* InputChannel;`
- L34 _private member_ `IDeckLinkInput* DeckLinkInput;`
- L35 _private member_ `IDeckLinkStatus* DeckLinkStatus;`
- L36 _private member_ `std::atomic_char32_t RefCount;`
- L37 _private member_ `int64_t FrameNumber;`
- L38 _private member_ `bool bHasProcessedVideoInput = false;`
- L39 _private member_ `int32_t HDRLogCount;`
- L40 _private member_ `std::chrono::time_point<std::chrono::system_clock> HDRLogResetCountTime;`

#### class `BlackmagicDesign::Private::FInputChannel`  
`class FInputChannel`  
_L43-115_
- L54 _public prototype_ `FInputChannel(const FChannelInfo& InChannelInfo);`
- L55 _public prototype_ `~FInputChannel();`
- L56 _public prototype_ `FInputChannel(const FInputChannel&) = delete;`
- L57 _public prototype_ `FInputChannel& operator=(const FInputChannel&) = delete;`
- L59 _public prototype_ `bool Initialize(const FInputChannelOptions& InChannelOptions);`
- L60 _public prototype_ `void Reinitialize();`
- L62 _public function_ `const FChannelInfo& GetChannelInfo() const`
- L64 _public prototype_ `bool IsCompatible(const FChannelInfo& InChannelInfo, const FInputChannelOptions& InChannelOptions) const;`
- L66 _public prototype_ `size_t NumberOfListeners();`
- L67 _public prototype_ `bool InitializeListener(FUniqueIdentifier InIdentifier, const FInputChannelOptions& InChannelOptions, ReferencePtr<IInputEventCallback> InCallback);`
- L68 _public prototype_ `void UninitializeListener(FUniqueIdentifier InIdentifier);`
- L71 _private prototype_ `bool InitializeListener_Helper(const FListener InListener);`
- L72 _private prototype_ `bool UninitializeListener_Helper(const FListener InListener);`
- L74 _private prototype_ `bool InitializeInterfaces();`
- L75 _private prototype_ `bool VerifyFormatSupport();`
- L76 _private prototype_ `bool VerifyDeviceUsage();`
- L77 _private prototype_ `bool InitializeDeckLink();`
- L78 _private prototype_ `bool InitializeAudio();`
- L79 _private prototype_ `bool InitializeLTC();`
- L80 _private prototype_ `void ReleaseLTC();`
- L81 _private prototype_ `bool InitializeStream();`
- L86 _private member_ `FChannelInfo ChannelInfo;`
- L87 _private member_ `FInputChannelOptions ChannelOptions;`
- L88 _private member_ `int32_t ReadAudioCounter;`
- L89 _private member_ `int32_t ReadLTCCounter;`
- L90 _private member_ `int32_t ReadVideoCounter;`
- L91 _private member_ `int32_t ReadTimecodeCounter;`
- L94 _private member_ `IDeckLink* DeckLink;`
- L95 _private member_ `IDeckLinkInput* DeckLinkInput;`
- L96 _private member_ `IDeckLinkProfileAttributes* DeckLinkAttributes;`
- L97 _private member_ `IDeckLinkConfiguration* DeckLinkConfiguration;`
- L98 _private member_ `FInputChannelNotificationCallback* NotificationCallback;`
- L99 _private member_ `IDeckLinkStatus* DeckLinkStatus;`
- L100 _private member_ `bool bStreamStarted;`
- L102 _private member_ `BMDVideoInputFlags VideoInputFlags;`
- L103 _private member_ `BMDPixelFormat PixelFormat;`
- L104 _private member_ `BMDDisplayMode DisplayMode;`
- L106 _private member_ `BMDTimecodeFormat DeviceTimecodeFormat;`
- L108 _private member_ `std::vector<FListener> Listeners;`
- L109 _private member_ `std::mutex ListenerMutex;`
- L111 _private member_ `volatile bool bIsWaitingForInterlaceEvent;`
- L113 _private member_ `bool bCanProcessOddFrame;`
- L114 _private member_ `FTimecode PreviousReceivedTimecode;`

#### struct `BlackmagicDesign::Private::FInputChannel::FListener`  
`struct FListener`  
_L46-51_
- L48 _public member_ `FUniqueIdentifier Identifier;`
- L49 _public member_ `ReferencePtr<IInputEventCallback> Callback;`
- L50 _public member_ `FInputChannelOptions Option;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace BlackmagicDesign`
- L10 _namespace_ `namespace Private` (scope `BlackmagicDesign`)

### `Plugins/Media/BlackmagicMedia/Source/BlackmagicCore/Private/BlackmagicOutputChannel.h` (Private)


#### class `CustomAllocator`  
`class CustomAllocator : public IDeckLinkMemoryAllocator`  
_L12-33_
- inherits: `IDeckLinkMemoryAllocator`
- L15 _public prototype_ `CustomAllocator();`
- L16 _public prototype_ `virtual ~CustomAllocator();`
- L19 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, LPVOID* ppv);` — IUnknown methods
- L20 _public prototype_ `virtual ULONG STDMETHODCALLTYPE AddRef(void);`
- L21 _public prototype_ `virtual ULONG STDMETHODCALLTYPE Release(void);`
- L24 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE AllocateBuffer(unsigned int bufferSize, void** allocatedBuffer);` — IDeckLinkMemoryAllocator methods
- L25 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE ReleaseBuffer(void* buffer);`
- L26 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE Commit();`
- L27 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE Decommit();`
- L30 _private member_ `ULONG RefCount;`
- L31 _private member_ `uint32_t AllocatedSize;`
- L32 _private member_ `void* AllocatedBuffer;`

#### struct `BlackmagicDesign::Private::FAudioPacket`  
`struct FAudioPacket : public Blackmagic::Private::IPoolable`  
_L40-70_
- inherits: `Blackmagic::Private::IPoolable`
- L44 _public member_ `const uint32_t BLACKMAGIC_AUDIOSIZE_MAX = (201 * 1024);` — Assuming lowest framerate of 14.98 fps, Sample rate of 48 KHZ, 32 bit depth and 16 Channels 16 * (32/8) * 48000 / 14.98 = 201 kB
- L46 _public member_ `uint8_t* AudioBuffer;`
- L47 _public member_ `uint32_t NumAudioSamples = 0;`
- L48 _public member_ `uint32_t AudioBufferSize = 0;`
- L50 _public function_ `FAudioPacket()`
- L55 _public function_ `virtual ~FAudioPacket()`
- L63 _public function_ `virtual void Clear()`

#### class `BlackmagicDesign::Private::FOutputChannelNotificationCallback`  
`class FOutputChannelNotificationCallback : public IDeckLinkVideoOutputCallback`  
_L74-92_
- inherits: `IDeckLinkVideoOutputCallback`
- L77 _public prototype_ `FOutputChannelNotificationCallback(FOutputChannel* InOwner, IDeckLinkOutput* InDeckLinkOutput);`
- L78 _public prototype_ `virtual ~FOutputChannelNotificationCallback() = default;`
- L80 _public prototype_ `HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, LPVOID *ppv);`
- L82 _public prototype_ `ULONG STDMETHODCALLTYPE AddRef();`
- L83 _public prototype_ `ULONG STDMETHODCALLTYPE Release();`
- L85 _public prototype_ `HRESULT STDMETHODCALLTYPE ScheduledFrameCompleted(IDeckLinkVideoFrame* InCompletedFrame, BMDOutputFrameCompletionResult InResult);`
- L86 _public prototype_ `HRESULT STDMETHODCALLTYPE ScheduledPlaybackHasStopped();`
- L89 _private member_ `FOutputChannel* OutputChannel;`
- L90 _private member_ `IDeckLinkOutput* DeckLinkOutput;`
- L91 _private member_ `std::atomic_char32_t RefCount;`

#### class `BlackmagicDesign::Private::FOutputChannelRenderAudioCallback`  
`class FOutputChannelRenderAudioCallback : public IDeckLinkAudioOutputCallback`  
_L94-111_
- inherits: `IDeckLinkAudioOutputCallback`
- L97 _public prototype_ `FOutputChannelRenderAudioCallback(FOutputChannel* InOwner, IDeckLinkOutput* InDeckLinkOutput);`
- L98 _public function_ `virtual ~FOutputChannelRenderAudioCallback()`
- L100 _public prototype_ `HRESULT STDMETHODCALLTYPE RenderAudioSamples(BOOL Preroll);`
- L102 _public prototype_ `HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, LPVOID* ppv);`
- L104 _public prototype_ `ULONG STDMETHODCALLTYPE AddRef();`
- L105 _public prototype_ `ULONG STDMETHODCALLTYPE Release();`
- L108 _private member_ `FOutputChannel* OutputChannel;`
- L109 _private member_ `IDeckLinkOutput* DeckLinkOutput;`
- L110 _private member_ `std::atomic_char32_t RefCount;`

#### class `BlackmagicDesign::Private::FDecklinkVideoFrame`  
`class FDecklinkVideoFrame : public IDeckLinkMutableVideoFrame, public IDeckLinkVideoFrameMetadataExtensions`  
_L116-176_
- inherits: `IDeckLinkMutableVideoFrame,IDeckLinkVideoFrameMetadataExtensions`
- desc: Wrapper class around IDeckLinkMutableVideoFrame that also extends IDeckLinkVideoFrameMetadataExtensions in order to provide HDR metadata to the SDI feed.
- L119 _public function_ `FDecklinkVideoFrame(IDeckLinkMutableVideoFrame* InWrappedVideoFrame, FHDRMetaData InHDRMetadata) : RefCount(1) , WrappedVideoFrame(InWrappedVideoFrame) , HDRMetadata(MoveTemp(InHDRMetadata))`
- L126 _public prototype_ `virtual ~FDecklinkVideoFrame() = default;`
- L129 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID RIID, LPVOID* PPV) override;`
- L130 _public prototype_ `virtual ULONG STDMETHODCALLTYPE AddRef() override;`
- L131 _public prototype_ `virtual ULONG STDMETHODCALLTYPE Release() override;`
- L135 _public prototype_ `virtual BMDFrameFlags STDMETHODCALLTYPE GetFlags(void) override;`
- L136 _public prototype_ `virtual long STDMETHODCALLTYPE GetWidth(void) override;`
- L137 _public prototype_ `virtual long STDMETHODCALLTYPE GetHeight(void) override;`
- L138 _public prototype_ `virtual long STDMETHODCALLTYPE GetRowBytes(void) override;`
- L139 _public prototype_ `virtual BMDPixelFormat STDMETHODCALLTYPE GetPixelFormat(void) override;`
- L140 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE GetBytes( void** Buffer) override;`
- L141 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE GetTimecode( BMDTimecodeFormat Format, IDeckLinkTimecode** Timecode) override;`
- L142 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE GetAncillaryData( IDeckLinkVideoFrameAncillary** ancillary) override;`
- L146 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE SetFlags( BMDFrameFlags NewFlags) override;`
- L147 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE SetTimecode( BMDTimecodeFormat Format, IDeckLinkTimecode* Timecode) override;`
- L148 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE SetTimecodeFromComponents( BMDTimecodeFormat Format, unsigned char Hours, unsigned char Minutes, unsigned char Seconds, unsigned char Frames, BMDTimecodeFlags Flags) override;`
- L149 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE SetAncillaryData( IDeckLinkVideoFrameAncillary* Ancillary) override;`
- L150 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE SetTimecodeUserBits( BMDTimecodeFormat Format, BMDTimecodeUserBits UserBits) override;`
- L154 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE GetInt(BMDDeckLinkFrameMetadataID MetadataId, LONGLONG* Value) override;`
- L155 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE GetFloat(BMDDeckLinkFrameMetadataID MetadataId, double* Value) override;`
- L156 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE GetFlag(BMDDeckLinkFrameMetadataID MetadataId, BOOL* Value) override;`
- L157 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE GetString(BMDDeckLinkFrameMetadataID MetadataId, BSTR* Value) override;`
- L158 _public prototype_ `virtual HRESULT STDMETHODCALLTYPE GetBytes(BMDDeckLinkFrameMetadataID MetadataId, void* Buffer, unsigned int* BufferSize) override;`
- L163 _private prototype_ `bool IsHDRLoggingOK();` — Utility function to throttle HDR warning logs.
- L167 _private member_ `ULONG RefCount;` — Used to destroy object at 0 refs.
- L169 _private member_ `ReferencePtr<IDeckLinkMutableVideoFrame> WrappedVideoFrame;` — Wrapped video frame.
- L171 _private member_ `FHDRMetaData HDRMetadata;` — Holds HDR Metadata.
- L173 _private member_ `int32_t HDRLogCount;` — Used for throttling HDR logs.
- L175 _private member_ `double LastHDRLogResetTime = 0.0;` — Used for keeping track of the last HDR logging reset time.

#### class `BlackmagicDesign::Private::FOutputChannel`  
`class FOutputChannel`  
_L178-370_
- L190 _public prototype_ `FOutputChannel(const FChannelInfo& InChannelInfo, const FOutputChannelOptions InChannelOptions);`
- L191 _public prototype_ `~FOutputChannel();`
- L192 _public prototype_ `FOutputChannel(const FOutputChannel&) = delete;`
- L193 _public prototype_ `FOutputChannel& operator=(const FOutputChannel&) = delete;`
- L195 _public prototype_ `bool Initialize();`
- L197 _public function_ `const FChannelInfo& GetChannelInfo() const`
- L199 _public function_ `bool IsCompatible(const FChannelInfo& InChannelInfo, const FOutputChannelOptions& InChannelOptions) const`
- L201 _public prototype_ `size_t NumberOfListeners();`
- L202 _public prototype_ `void AddListener(const FUniqueIdentifier& InIdentifier, ReferencePtr<IOutputEventCallback> InCallback);`
- L203 _public prototype_ `void RemoveListener(const FUniqueIdentifier& InIdentifier);`
- L205 _public prototype_ `bool SetVideoFrameData(const FFrameDescriptor& InFrame);`
- L206 _public prototype_ `bool SetVideoFrameData(FFrameDescriptor_GPUDMA& InFrame);`
- L209 _public prototype_ `bool ShouldCaptureThisFrame(::FTimecode Timecode, uint32 FrameNumber);` — Return whether to capture or discard a frame based on its timecode and frame number.
- L211 _public prototype_ `bool SetAudioFrameData(const FAudioSamplesDescriptor& InSamples);`
- L213 _public prototype_ `void OnScheduledFrameCompleted(IDeckLinkVideoFrame* InCompletedFrame, BMDOutputFrameCompletionResult InResult);`
- L214 _public prototype_ `bool OnRenderAudio(BOOL bPreRoll);`
- L215 _public prototype_ `void UnregisterBuffers();`
- L219 _private prototype_ `bool InitializeInterfaces();`
- L220 _private prototype_ `bool InitializeLinkConfiguration();`
- L221 _private prototype_ `bool InitializeFrameBuffer();`
- L222 _private prototype_ `bool VerifyFormatSupport();`
- L223 _private prototype_ `bool VerifyIfDeviceUsed();`
- L224 _private prototype_ `bool InitializeDeckLink();`
- L225 _private prototype_ `bool InitializeKeyer();`
- L226 _private prototype_ `bool InitializeAudio();`
- L227 _private prototype_ `bool InitializeVideo();`
- L228 _private prototype_ `bool InitializeWaitForInterlacedOddFieldEvent();`
- L230 _private prototype_ `bool SendPreRollFrames();`
- L231 _private prototype_ `void EmbedTimecodeInFrame(FOutputFrame* InFrame);`
- L236 _private prototype_ `FOutputFrame* FetchAvailableWritingFrame(const FBaseFrameData& InFrame);` — Frame management
- L237 _private prototype_ `FOutputFrame* FetchAvailableWritingFrameInterlaced(const FBaseFrameData& InFrame);`
- L238 _private prototype_ `FOutputFrame* FetchAvailableWritingFrameProgressive(const FBaseFrameData& InFrame);`
- L239 _private prototype_ `void PushWhenFrameReady(FOutputFrame* InFrame);`
- L240 _private prototype_ `bool IsFrameReadyToBeRead(FOutputFrame* InFrame);`
- L241 _private prototype_ `bool ScheduleOutputFrame(FOutputFrame* InFrame);`
- L242 _private prototype_ `void AdvanceTime();`
- L244 _private prototype_ `uint32_t GetNumAudioSamplesPerFrame();`
- L245 _private prototype_ `uint8_t GetAudioBitDepth();`
- L247 _private prototype_ `void VideoThread_ScheduleVideo();`
- L248 _private prototype_ `void AudioThread_ScheduleAudioSamples();`
- L250 _private prototype_ `uint8_t GetBytesPerPixel() const;`
- L253 _public member_ `bool bIsDebugAlive;`
- L259 _private member_ `FChannelInfo ChannelInfo;`
- L260 _private member_ `FOutputChannelOptions ChannelOptions;`
- L261 _private member_ `IDeckLink* DeckLink;`
- L262 _private member_ `IDeckLinkProfileAttributes* DeckLinkAttributes;`
- L263 _private member_ `IDeckLinkOutput* DeckLinkOutput;`
- L264 _private member_ `IDeckLinkConfiguration* DeckLinkConfiguration;`
- L265 _private member_ `IDeckLinkKeyer* Keyer;`
- L266 _private member_ `FOutputChannelNotificationCallback* NotificationCallback;`
- L267 _private member_ `FOutputChannelRenderAudioCallback* RenderAudioCallback;`
- L269 _private member_ `bool bAudioOutputStarted;`
- L270 _private member_ `bool bVideoOutputStarted;`
- L272 _private member_ `std::atomic<BMDTimeValue> OutputTime;`
- L274 _private member_ `BMDVideoOutputFlags VideoOutputFlags;`
- L275 _private member_ `BMDPixelFormat PixelFormat;`
- L276 _private member_ `BMDDisplayMode DisplayMode;`
- L278 _private member_ `bool bOutputTimecode;`
- L279 _private member_ `BMDTimecodeFormat DeviceTimecodeFormat;`
- L281 _private member_ `std::vector<FListener> Listeners;`
- L282 _private member_ `std::mutex CallbackMutex;`
- L283 _private member_ `std::mutex AllocatorMutex;`
- L285 _private member_ `std::unique_ptr<std::thread> ScheduleVideoThread;`
- L286 _private member_ `std::unique_ptr<std::thread> ScheduleAudioSamplesThread;`
- L287 _private member_ `std::unique_ptr<std::thread> WaitForInterlacedOddFieldThread;`
- L288 _private member_ `std::unique_ptr<std::mutex> WaitForInterlacedOddFieldMutex;`
- L289 _private member_ `std::unique_ptr<std::condition_variable> WaitForInterlacedOddFieldCondition;`
- L291 _private member_ `volatile bool bWaitForInterlacedOddFieldActive;`
- L293 _private member_ `volatile bool bScheduleAudioSamplesActive;`
- L294 _private member_ `volatile bool bScheduleVideoActive;`
- L296 _private member_ `std::mutex WaitForVideoScheduleMutex;`
- L297 _private member_ `std::mutex WaitForAudioRenderMutex;`
- L298 _private member_ `std::condition_variable WaitForVideoScheduleCondition;`
- L299 _private member_ `std::condition_variable WaitForAudioRenderCondition;`
- L301 _private member_ `std::atomic<uint32_t> InFlightFrames;`
- L302 _private member_ `std::atomic<uint32_t> LostFrameCounter;`
- L303 _private member_ `uint32_t DroppedFrameCounter;`
- L304 _private member_ `uint32_t QueuedDroppedFrameCount;`
- L339 _private member_ `int32_t AudioBufferSize = 0;`
- L341 _private member_ `std::mutex FrameLock;`
- L342 _private member_ `std::mutex ScheduleLock;`
- L343 _private member_ `std::vector<FOutputFrame*> AllFrames;`
- L344 _private member_ `std::vector<FOutputFrame*> FrameReadyToWrite;` — Ready to be used by the Unreal Engine
- L347 _private member_ `std::atomic<FOutputFrame*> LastScheduledFrame;` — Pointer to the last sent frame to be reused when no new frames are ready to be sent
- L349 _private member_ `static constexpr uint8_t NumVideoPrerollFrames = 2;`
- L350 _private member_ `std::atomic<uint32_t> NumBufferedAudioSamples;`
- L351 _private member_ `uint32_t AudioSamplesWaterLevel = 0;`
- L353 _private member_ `CustomAllocator* Allocator = nullptr;`
- L355 _private member_ `volatile bool bIsWaitingForInterlaceEvent;`
- L357 _private member_ `Blackmagic::Private::ThreadSafeQueue<FOutputFrame*> VideoFramesToSchedule;`
- L358 _private member_ `Blackmagic::Private::ThreadSafeQueue<FAudioPacket*> AudioPacketsToSchedule;`
- L359 _private member_ `Blackmagic::Private::ThreadSafeObjectPool<FAudioPacket> AudioPacketPool;`
- L361 _private member_ `UE::GPUTextureTransfer::TextureTransferPtr TextureTransfer;`
- L363 _private member_ `bool bIsSSE2Available;`
- L364 _private member_ `bool bIsFieldAEven;`
- L365 _private member_ `bool bIsFirstFetch;`
- L366 _private member_ `bool bIsPrerollingAudio;`
- L367 _private member_ `bool bPlaybackStopped;`
- L369 _private member_ `bool bRegisteredDMABuffers = false;`

#### struct `BlackmagicDesign::Private::FOutputChannel::FListener`  
`struct FListener`  
_L181-185_
- L183 _public member_ `FUniqueIdentifier Identifier;`
- L184 _public member_ `ReferencePtr<IOutputEventCallback> Callback;`

#### struct `BlackmagicDesign::Private::FOutputChannel::FOutputFrame`  
`struct FOutputFrame`  
_L306-337_
- L308 _public prototype_ `FOutputFrame();`
- L309 _public prototype_ `~FOutputFrame();`
- L310 _public prototype_ `FOutputFrame(const FOutputFrame&) = delete;`
- L311 _public prototype_ `FOutputFrame& operator=(const FOutputFrame&) = delete;`
- L313 _public member_ `static const uint32_t InvalidFrameIdentifier;`
- L315 _public member_ `ReferencePtr<FDecklinkVideoFrame> BlackmagicFrame;`
- L316 _public member_ `uint8_t* AudioBuffer;`
- L317 _public member_ `uint32_t NumAudioSamples;`
- L319 _public member_ `FTimecode Timecode;`
- L320 _public member_ `FTimecode Timecode2;`
- L322 _public member_ `uint32_t CopiedVideoBufferSize;`
- L323 _public member_ `uint32_t CopiedAudioBufferSize;`
- L324 _public member_ `uint32_t FrameIdentifier;`
- L325 _public member_ `uint32_t FrameIdentifierF2;`
- L327 _public member_ `std::atomic<uint32_t> InFlightCount;`
- L329 _public member_ `bool bVideoLineFilled;`
- L330 _public member_ `bool bVideoF2LineFilled;` — used in interlaced
- L331 _public member_ `bool bAudioLineFilled;`
- L333 _public member_ `bool bVideoScheduled;`
- L334 _public member_ `bool bAudioScheduled;`
- L336 _public prototype_ `void Clear();`

#### Free symbols / members of external scopes

- L36 _namespace_ `namespace BlackmagicDesign`
- L38 _namespace_ `namespace Private` (scope `BlackmagicDesign`)

### `Plugins/Media/BlackmagicMedia/Source/BlackmagicCore/Private/BlackmagicVideoFormats.h` (Private)


#### class `BlackmagicDesign::Private::VideoFormatsScanner`  
`class VideoFormatsScanner`  
_L16-24_
- desc: VideoFormatsScanner definition
- L19 _public prototype_ `VideoFormatsScanner(int32_t InDeviceId, bool bForOutput);`
- L21 _public prototype_ `static BlackmagicDesign::BlackmagicVideoFormats::VideoFormatDescriptor GetVideoFormat(IDeckLinkDisplayMode* InBlackmagicVideoMode);`
- L23 _public member_ `std::vector<BlackmagicDesign::BlackmagicVideoFormats::VideoFormatDescriptor> FormatList;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace BlackmagicDesign`
- L12 _namespace_ `namespace Private` (scope `BlackmagicDesign`)

### `Plugins/Media/BlackmagicMedia/Source/BlackmagicCore/Private/Common.h` (Private)


#### Free symbols / members of external scopes

- L35 _macro_ `#define FALSE 0`
- L39 _macro_ `#define TRUE 1`

### `Plugins/Media/BlackmagicMedia/Source/BlackmagicCore/Private/Platform/GenericPlatform.h` (Private)
_(no declarations extracted)_

### `Plugins/Media/BlackmagicMedia/Source/BlackmagicCore/Private/Platform/Linux/LinuxPlatform.h` (Private)


#### Free symbols / members of external scopes

- L16 _macro_ `#define ENUM(x) _ ## x` — convert Windows style enums in Linux, i.e. BMDPixelFormat to _BMDPixelFormat
- L18 _macro_ `#define BSTR const char*`
- L20 _macro_ `#define LONGLONG int64_t`
- L23 _typedef_ `typedef bool BOOL;` — simulate Windows BOOL type
- L31 _prototype_ `bool IsEqualIID(REFIID LHS, REFIID RHS);` — Defined outside of namespace to match windows' implementation
- L33 _namespace_ `namespace BlackmagicPlatform`
- L35 _prototype_ `std::string GetName(IDeckLinkDisplayMode* DisplayMode);` (scope `BlackmagicPlatform`)
- L37 _prototype_ `bool InitializeAPI();` (scope `BlackmagicPlatform`)
- L38 _prototype_ `void ReleaseAPI();` (scope `BlackmagicPlatform`)
- L40 _prototype_ `IDeckLinkIterator* CreateDeckLinkIterator();` (scope `BlackmagicPlatform`)
- L41 _prototype_ `void DestroyDeckLinkIterator(IDeckLinkIterator*);` (scope `BlackmagicPlatform`)
- L43 _prototype_ `IDeckLinkVideoConversion* CreateDeckLinkVideoConversion();` (scope `BlackmagicPlatform`)
- L44 _prototype_ `void DestroyDeckLinkVideoConversion(IDeckLinkVideoConversion*);` (scope `BlackmagicPlatform`)
- L46 _prototype_ `void SetThreadPriority_TimeCritical(std::thread& InThread);` (scope `BlackmagicPlatform`)
- L48 _prototype_ `bool GetDisplayName(IDeckLink* Device, TCHAR* OutDisplayName, int32_t Size);` (scope `BlackmagicPlatform`)
- L50 _prototype_ `void* Allocate(uint32_t Size);` (scope `BlackmagicPlatform`)
- L51 _prototype_ `bool Free(void* Address, uint32_t Size);` (scope `BlackmagicPlatform`)

### `Plugins/Media/BlackmagicMedia/Source/BlackmagicCore/Private/Platform/Win/WinPlatform.h` (Private)


#### Free symbols / members of external scopes

- L15 _macro_ `#define ENUM(x) x` — convert Windows style enums in Linux, i.e. BMDPixelFormat to _BMDPixelFormat
- L18 _macro_ `#define FALSE 0`
- L22 _macro_ `#define TRUE 1`
- L30 _namespace_ `namespace BlackmagicPlatform`
- L32 _prototype_ `bool InitializeAPI();` (scope `BlackmagicPlatform`)
- L33 _prototype_ `void ReleaseAPI();` (scope `BlackmagicPlatform`)
- L35 _prototype_ `std::string GetName(IDeckLinkDisplayMode* DisplayMode);` (scope `BlackmagicPlatform`)
- L37 _prototype_ `IDeckLinkIterator* CreateDeckLinkIterator();` (scope `BlackmagicPlatform`)
- L38 _prototype_ `void DestroyDeckLinkIterator(IDeckLinkIterator*);` (scope `BlackmagicPlatform`)
- L40 _prototype_ `IDeckLinkVideoConversion* CreateDeckLinkVideoConversion();` (scope `BlackmagicPlatform`)
- L41 _prototype_ `void DestroyDeckLinkVideoConversion(IDeckLinkVideoConversion*);` (scope `BlackmagicPlatform`)
- L43 _prototype_ `void SetThreadPriority_TimeCritical(std::thread& InThread);` (scope `BlackmagicPlatform`)
- L45 _prototype_ `bool GetDisplayName(IDeckLink* Device, TCHAR* OutDisplayName, int32_t Size);` (scope `BlackmagicPlatform`)
- L47 _prototype_ `void* Allocate(uint32_t BufferSize);` (scope `BlackmagicPlatform`)
- L48 _prototype_ `bool Free(void* Address, uint32_t BufferSize);` (scope `BlackmagicPlatform`)

### `Plugins/Media/BlackmagicMedia/Source/BlackmagicCore/Private/SSE2MemCpy.h` (Private)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace BlackmagicDesign`
- L7 _namespace_ `namespace Private` (scope `BlackmagicDesign`)
- L9 _prototype_ `bool IsSSE2Available();` (scope `BlackmagicDesign::Private`)
- L10 _prototype_ `bool IsCorrectlyAlignedForSSE2MemCpy(const void* InDst, const void* InSrc, unsigned int InSize);` (scope `BlackmagicDesign::Private`)
- L11 _prototype_ `void SSE2MemCpy(const void* InDst, const void* InSrc, unsigned int InSize);` (scope `BlackmagicDesign::Private`)

### `Plugins/Media/BlackmagicMedia/Source/BlackmagicCore/Private/ThreadSafeObjectPool.h` (Private)


#### class `Blackmagic::Private::IPoolable`  
`class IPoolable`  
_L12-18_
- L15 _public function_ `virtual ~IPoolable()`
- L17 _public prototype_ `virtual void Clear() = 0;` — Clear the object before it is reused by the pool.

#### class `Blackmagic::Private::ThreadSafeObjectPool`  
`template <typename ObjectType> class ThreadSafeObjectPool`  
_L21-95_
- L24 _public function_ `ThreadSafeObjectPool(uint32_t PoolCapacity)`
- L31 _public function_ `~ThreadSafeObjectPool()` — Destructor.
- L39 _public function_ `ObjectType* Acquire()` — Acquire an object from the pool.
- L53 _public function_ `size_t Num() const` — Get the number of objects stored.
- L60 _public function_ `void Release(ObjectType* Object)` — Return the given object to the pool.
- L74 _public function_ `void Reserve(uint32_t NumObjects)` — Reserve the specified number of objects.
- L91 _private member_ `mutable std::mutex PoolMutex;`
- L94 _private member_ `std::vector<ObjectType*> Pool;` — List of unused objects.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Blackmagic`
- L10 _namespace_ `namespace Private` (scope `Blackmagic`)

### `Plugins/Media/BlackmagicMedia/Source/BlackmagicCore/Private/ThreadSafeQueue.h` (Private)


#### class `Blackmagic::Private::ThreadSafeQueue`  
`template<class T> class ThreadSafeQueue`  
_L14-55_
- L17 _public function_ `void Push(const T& InValue)`
- L23 _public function_ `bool Pop(T& OutValue)`
- L35 _public function_ `void Erase(const T& InValue)`
- L45 _public function_ `size_t Size() const`
- L53 _private member_ `mutable std::mutex QueueMutex;`
- L54 _private member_ `std::vector<T> List;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Blackmagic`
- L11 _namespace_ `namespace Private` (scope `Blackmagic`)

### `Plugins/Media/BlackmagicMedia/Source/BlackmagicCore/Public/BlackmagicCoreModule.h` (Public)


#### class `FBlackmagicCoreModule`  
`class FBlackmagicCoreModule : public IModuleInterface`  
_L11-33_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _public function_ `bool IsInitialized()` — Whether the API is initialized.
- L25 _public function_ `bool CanUseBlackmagicCard()` — Whether a blackmagic card can be used.
- L31 _private member_ `bool bCanForceBlackmagicUsage = false;`
- L32 _private member_ `bool bInitialized = false;`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogBlackmagicCore, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogBlackmagicCore, Log, All);`

### `Plugins/Media/BlackmagicMedia/Source/BlackmagicCore/Public/BlackmagicLib.h` (Public)


#### enum `BlackmagicDesign::EPixelFormat`  
`enum class EPixelFormat`  
_L23-27_
- L25 _public enumerator_ `pf_8Bits`
- L26 _public enumerator_ `pf_10Bits`

#### enum `BlackmagicDesign::EFullPixelFormat`  
`enum class EFullPixelFormat`  
_L29-37_
- L31 _public enumerator_ `pf_8BitBGRA`
- L32 _public enumerator_ `pf_8BitYUV`
- L33 _public enumerator_ `pf_10BitRGB`
- L34 _public enumerator_ `pf_10BitRGBXLE`
- L35 _public enumerator_ `pf_10BitYUV`
- L36 _public enumerator_ `pf_10BitRGBX`

#### enum `BlackmagicDesign::EPixelColor`  
`enum class EPixelColor`  
_L39-43_
- L41 _public enumerator_ `YCbCr`
- L42 _public enumerator_ `RGB`

#### enum `BlackmagicDesign::EFieldDominance`  
`enum class EFieldDominance`  
_L45-50_
- L47 _public enumerator_ `Progressive`
- L48 _public enumerator_ `Interlaced`
- L49 _public enumerator_ `ProgressiveSegmentedFrame`

#### enum `BlackmagicDesign::EHDRMetaDataColorspace`  
`enum class EHDRMetaDataColorspace`  
_L52-57_
- L54 _public enumerator_ `Rec601`
- L55 _public enumerator_ `Rec709`
- L56 _public enumerator_ `Rec2020`

#### enum `BlackmagicDesign::EHDRMetaDataEOTF`  
`enum class EHDRMetaDataEOTF`  
_L58-64_
- L60 _public enumerator_ `SDR`
- L61 _public enumerator_ `HDR`
- L62 _public enumerator_ `PQ`
- L63 _public enumerator_ `HLG`

#### enum `BlackmagicDesign::EAudioBitDepth`  
`enum class EAudioBitDepth`  
_L66-70_
- L68 _public enumerator_ `Signed_16Bits`
- L69 _public enumerator_ `Signed_32Bits`

#### enum `BlackmagicDesign::EAudioChannelConfiguration`  
`enum class EAudioChannelConfiguration : uint8_t`  
_L72-77_
- L74 _public enumerator_ `Channels_2 = 2`
- L75 _public enumerator_ `Channels_8 = 8`
- L76 _public enumerator_ `Channels_16 = 16`

#### enum `BlackmagicDesign::EAudioSampleRate`  
`enum class EAudioSampleRate : uint32_t`  
_L79-82_
- L81 _public enumerator_ `SR_48kHz = 48000`

#### enum `BlackmagicDesign::ERHI`  
`enum class ERHI : uint8_t`  
_L84-91_
- L86 _public enumerator_ `Invalid`
- L87 _public enumerator_ `D3D11`
- L88 _public enumerator_ `D3D12`
- L89 _public enumerator_ `Cuda`
- L90 _public enumerator_ `Vulkan`

#### struct `BlackmagicDesign::FUniqueIdentifier`  
`struct FUniqueIdentifier`  
_L101-110_
- desc: FUniqueIdentifier definition
- L103 _public prototype_ `FUniqueIdentifier();`
- L104 _public prototype_ `explicit FUniqueIdentifier(int32_t InIdentifier);`
- L105 _public prototype_ `bool IsValid() const;`
- L106 _public prototype_ `bool operator== (const FUniqueIdentifier& rhs) const;`
- L109 _private member_ `int32_t Identifier;`

#### struct `BlackmagicDesign::FTimecode`  
`struct FTimecode`  
_L115-125_
- desc: FTimecode definition limited to 30fps
- L117 _public prototype_ `FTimecode();`
- L118 _public prototype_ `bool operator== (const FTimecode& Other) const;`
- L120 _public member_ `uint32_t Hours;`
- L121 _public member_ `uint32_t Minutes;`
- L122 _public member_ `uint32_t Seconds;`
- L123 _public member_ `uint32_t Frames;`
- L124 _public member_ `bool bIsDropFrame;`

#### enum `BlackmagicDesign::ETimecodeFormat`  
`enum struct ETimecodeFormat`  
_L127-133_
- L129 _public enumerator_ `TCF_None`
- L130 _public enumerator_ `TCF_LTC`
- L131 _public enumerator_ `TCF_VITC1`
- L132 _public enumerator_ `TCF_Auto`

#### enum `BlackmagicDesign::ELinkConfiguration`  
`enum struct ELinkConfiguration`  
_L135-141_
- L137 _public enumerator_ `SingleLink`
- L138 _public enumerator_ `DualLink`
- L139 _public enumerator_ `QuadLinkTSI`
- L140 _public enumerator_ `QuadLinkSqr`

#### struct `BlackmagicDesign::FFormatInfo`  
`struct FFormatInfo`  
_L146-161_
- desc: FFormatInfo definition Information about a given frame desc
- L149 _public member_ `uint32_t FrameRateNumerator = 0;` — Framerate
- L150 _public member_ `uint32_t FrameRateDenominator = 0;`
- L153 _public member_ `uint32_t Width = 0;` — Image Width & Weight in texels
- L154 _public member_ `uint32_t Height = 0;`
- L156 _public member_ `EFieldDominance FieldDominance = EFieldDominance::Progressive;`
- L157 _public member_ `FBlackmagicVideoFormat DisplayMode = 0;` — Unique identifier that represent all that combination for the device
- L159 _public prototype_ `bool operator==(FFormatInfo& Other) const;`

#### struct `BlackmagicDesign::FAudioFormat`  
`struct FAudioFormat`  
_L165-170_
- desc: FAudioFormat definition
- L167 _public member_ `EAudioBitDepth BitDepth;`
- L168 _public member_ `EAudioChannelConfiguration ChannelConfigration;`
- L169 _public prototype_ `bool operator==(FAudioFormat& Other) const;`

#### struct `BlackmagicDesign::FChannelInfo`  
`struct FChannelInfo`  
_L174-179_
- desc: FChannelInfo definition
- L176 _public member_ `int32_t DeviceIndex;`
- L178 _public prototype_ `bool operator==(FChannelInfo& Other) const;`

#### struct `BlackmagicDesign::FHDRMetaData`  
`struct FHDRMetaData`  
_L183-217_
- desc: HDR Metadata.
- L185 _public prototype_ `FHDRMetaData();`
- L188 _public member_ `bool bIsAvailable;` — Whether the data contained in this struct is valid.
- L190 _public member_ `EHDRMetaDataColorspace ColorSpace;` — Target color space.
- L192 _public member_ `EHDRMetaDataEOTF EOTF;` — HDR Transfer function.
- L194 _public member_ `double WhitePointX;` — White point X coordinate.
- L196 _public member_ `double WhitePointY;` — White point Y coordinate.
- L198 _public member_ `double DisplayPrimariesRedX;` — Red chromaticity X coordinate.
- L200 _public member_ `double DisplayPrimariesRedY;` — Red chromaticity Y coordinate.
- L202 _public member_ `double DisplayPrimariesGreenX;` — Green chromaticity X coordinate.
- L204 _public member_ `double DisplayPrimariesGreenY;` — Green chromaticity Y coordinate.
- L206 _public member_ `double DisplayPrimariesBlueX;` — Blue chromaticity X coordinate.
- L208 _public member_ `double DisplayPrimariesBlueY;` — Blue chromaticity Y coordinate.
- L210 _public member_ `double MaxDisplayLuminance;` — Max display mastering luminance.
- L212 _public member_ `double MinDisplayLuminance;` — Min display mastering luminance.
- L214 _public member_ `double MaxContentLightLevel;` — Max content light level.
- L216 _public member_ `double MaxFrameAverageLightLevel;` — Max frame average light level.

#### struct `BlackmagicDesign::FInputChannelOptions`  
`struct FInputChannelOptions`  
_L221-238_
- desc: FInputChannelOptions definition
- L223 _public prototype_ `FInputChannelOptions();`
- L225 _public member_ `FFormatInfo FormatInfo;`
- L226 _public member_ `int32_t CallbackPriority;`
- L228 _public member_ `bool bReadVideo;`
- L229 _public member_ `EPixelFormat PixelFormat;`
- L231 _public member_ `ETimecodeFormat TimecodeFormat;`
- L233 _public member_ `bool bReadAudio;`
- L234 _public member_ `int32_t NumberOfAudioChannel;`
- L236 _public member_ `bool bUseTheDedicatedLTCInput;`
- L237 _public member_ `bool bAutoDetect;`

#### struct `BlackmagicDesign::FOutputChannelOptions`  
`struct FOutputChannelOptions`  
_L242-277_
- desc: FOutputChannelOptions definition
- L244 _public prototype_ `FOutputChannelOptions();`
- L246 _public function_ `bool IsInterlaced() const`
- L251 _public member_ `FFormatInfo FormatInfo;`
- L252 _public member_ `int32_t CallbackPriority;`
- L253 _public member_ `EPixelFormat PixelFormat;`
- L255 _public member_ `EAudioSampleRate AudioSampleRate;`
- L256 _public member_ `EAudioBitDepth AudioBitDepth;`
- L257 _public member_ `EAudioChannelConfiguration NumAudioChannels;`
- L259 _public member_ `uint32_t NumberOfBuffers;`
- L261 _public member_ `ETimecodeFormat TimecodeFormat;`
- L262 _public member_ `ELinkConfiguration LinkConfiguration;`
- L265 _public member_ `FHDRMetaData HDRMetadata;` — HDR Metadata.
- L267 _public member_ `bool bOutputKey;`
- L268 _public member_ `bool bOutputVideo;`
- L269 _public member_ `bool bOutputAudio;`
- L270 _public member_ `bool bOutputInterlacedFieldsTimecodeNeedToMatch;`
- L271 _public member_ `bool bOutputInterlaceAsProgressive;`
- L272 _public member_ `bool bOutputInterlaceOnEvenFrames;`
- L273 _public member_ `bool bLogDropFrames;`
- L274 _public member_ `bool bUseGPUDMA;`
- L275 _public member_ `bool bScheduleInDifferentThread;`
- L276 _public member_ `bool bEncodeTimecodeInTexel;`

#### struct `BlackmagicDesign::IInputEventCallback`  
`struct IInputEventCallback`  
_L281-344_
- desc: IInputEventCallback definition
- L328 _public prototype_ `virtual ~IInputEventCallback();`
- L330 _public prototype_ `virtual void AddRef() = 0;`
- L331 _public prototype_ `virtual void Release() = 0;`
- L333 _public prototype_ `virtual void OnInitializationCompleted(bool bSuccess) = 0;`
- L334 _public prototype_ `virtual void OnShutdownCompleted() = 0;`
- L336 _public function_ `virtual void OnFrameReceived(const FFrameReceivedInfo&)`
- L339 _public function_ `virtual void OnFrameReceived(const FFrameReceivedInfo&, FFrameReceivedBufferHolders& )`
- L342 _public prototype_ `virtual void OnFrameFormatChanged(const FFormatInfo& NewFormat) = 0;`
- L343 _public prototype_ `virtual void OnInterlacedOddFieldEvent(long long FrameNumber) = 0;`

#### struct `BlackmagicDesign::IInputEventCallback::FFrameReceivedInfo`  
`struct FFrameReceivedInfo`  
_L283-310_
- L285 _public prototype_ `FFrameReceivedInfo();`
- L287 _public member_ `bool bHasInputSource;`
- L289 _public member_ `int64_t FrameNumber;`
- L292 _public member_ `bool bHaveTimecode;` — Timecode
- L293 _public member_ `FTimecode Timecode;`
- L296 _public member_ `void* VideoBuffer;` — Video
- L297 _public member_ `int32_t VideoWidth;`
- L298 _public member_ `int32_t VideoHeight;`
- L299 _public member_ `int32_t VideoPitch;`
- L300 _public member_ `EPixelFormat PixelFormat;`
- L301 _public member_ `EFullPixelFormat FullPixelFormat;`
- L302 _public member_ `EFieldDominance FieldDominance;`
- L303 _public member_ `FHDRMetaData HDRMetaData;`
- L306 _public member_ `void* AudioBuffer;` — Audio
- L307 _public member_ `int32_t AudioBufferSize;`
- L308 _public member_ `int32_t NumberOfAudioChannel;`
- L309 _public member_ `int32_t AudioRate;`

#### struct `BlackmagicDesign::IInputEventCallback::FFrameBufferHolder`  
`struct FFrameBufferHolder`  
_L313-316_
- desc: An empty type to expose. The real job is done in an internal child implementation.
- L315 _public prototype_ `virtual ~FFrameBufferHolder() = default;`

#### struct `BlackmagicDesign::IInputEventCallback::FFrameReceivedBufferHolders`  
`struct FFrameReceivedBufferHolders`  
_L322-326_
- desc: A container for video and audio buffer holders. These holders prevent internal buffers from being released while they are in use.
- L324 _public member_ `TSharedPtr<FFrameBufferHolder>* VideoBufferHolder = nullptr;`
- L325 _public member_ `TSharedPtr<FFrameBufferHolder>* AudioBufferHolder = nullptr;`

#### struct `BlackmagicDesign::IOutputEventCallback`  
`struct IOutputEventCallback`  
_L348-369_
- desc: IOutputEventCallback definition
- L358 _public prototype_ `virtual ~IOutputEventCallback();`
- L360 _public prototype_ `virtual void AddRef() = 0;`
- L361 _public prototype_ `virtual void Release() = 0;`
- L363 _public prototype_ `virtual void OnInitializationCompleted(bool bSuccess) = 0;`
- L364 _public prototype_ `virtual void OnShutdownCompleted() = 0;`
- L366 _public prototype_ `virtual void OnOutputFrameCopied(const FFrameSentInfo& InFrameInfo) = 0;`
- L367 _public prototype_ `virtual void OnPlaybackStopped() = 0;`
- L368 _public prototype_ `virtual void OnInterlacedOddFieldEvent() = 0;`

#### struct `BlackmagicDesign::IOutputEventCallback::FFrameSentInfo`  
`struct FFrameSentInfo`  
_L350-356_
- L352 _public prototype_ `FFrameSentInfo();`
- L354 _public member_ `uint32_t FramesLost;`
- L355 _public member_ `uint32_t FramesDropped;`

#### struct `BlackmagicDesign::FBaseFrameData`  
`struct FBaseFrameData`  
_L371-376_
- L373 _public member_ `FTimecode Timecode;`
- L374 _public member_ `uint32_t FrameIdentifier = 0;`
- L375 _public member_ `bool bEvenFrame = true;`

#### struct `BlackmagicDesign::FFrameDescriptor`  
`struct FFrameDescriptor : public FBaseFrameData`  
_L378-383_
- inherits: `FBaseFrameData`
- L380 _public member_ `uint8_t* VideoBuffer = nullptr;`
- L381 _public member_ `int32_t VideoWidth = 0;`
- L382 _public member_ `int32_t VideoHeight = 0;`

#### struct `BlackmagicDesign::FFrameDescriptor_GPUDMA`  
`struct FFrameDescriptor_GPUDMA : public FBaseFrameData`  
_L385-388_
- inherits: `FBaseFrameData`
- L387 _public member_ `FRHITexture* RHITexture = nullptr;`

#### struct `BlackmagicDesign::FAudioSamplesDescriptor`  
`struct FAudioSamplesDescriptor`  
_L390-398_
- L392 _public member_ `uint8_t* AudioBuffer = nullptr;`
- L393 _public member_ `int32_t AudioBufferLength = 0;`
- L394 _public member_ `int32_t NumAudioSamples = 0;`
- L396 _public member_ `FTimecode Timecode;`
- L397 _public member_ `uint32_t FrameIdentifier = 0;`

#### class `BlackmagicDesign::BlackmagicDeviceScanner`  
`class BlackmagicDeviceScanner`  
_L402-442_
- desc: BlackmagicDeviceScanner definition
- L405 _public member_ `const static int32_t FormatedTextSize = 64;`
- L406 _public typedef_ `using FormatedTextType = TCHAR[FormatedTextSize];`
- L430 _public prototype_ `BlackmagicDeviceScanner();`
- L431 _public prototype_ `~BlackmagicDeviceScanner();`
- L433 _public prototype_ `BlackmagicDeviceScanner(const BlackmagicDeviceScanner&) = delete;`
- L434 _public prototype_ `BlackmagicDeviceScanner& operator=(const BlackmagicDeviceScanner&) = delete;`
- L436 _public prototype_ `int32_t GetNumDevices() const;`
- L437 _public prototype_ `bool GetDeviceTextId(int32_t InDeviceIndex, FormatedTextType& OutTextId) const;`
- L438 _public prototype_ `bool GetDeviceInfo(int32_t InDeviceIndex, DeviceInfo& OutDeviceInfo) const;`
- L441 _private member_ `Private::DeviceScanner* Scanner;`

#### struct `BlackmagicDesign::BlackmagicDeviceScanner::DeviceInfo`  
`struct DeviceInfo`  
_L408-428_
- L410 _public member_ `bool bIsSupported;`
- L411 _public member_ `bool bCanDoCapture;`
- L412 _public member_ `bool bCanDoPlayback;`
- L413 _public member_ `bool bCanDoFullDuplex;`
- L414 _public member_ `bool bCanDoDualLink;`
- L415 _public member_ `bool bCanDoQuadLink;`
- L416 _public member_ `bool bCanDoQuadSquareLink;`
- L417 _public member_ `bool bHasGenlockReferenceInput;`
- L418 _public member_ `bool bHasLTCTimecodeInput;`
- L419 _public member_ `bool bCanAutoDetectInputFormat;`
- L420 _public member_ `bool bSupportInternalKeying;`
- L421 _public member_ `bool bSupportExternalKeying;`
- L423 _public member_ `uint32_t NumberOfSubDevices;`
- L424 _public member_ `uint32_t DevicePersistentId;`
- L425 _public member_ `uint32_t ProfileId;`
- L426 _public member_ `uint32_t DeviceGroupId;`
- L427 _public member_ `uint32_t SubDeviceIndex;`

#### struct `BlackmagicDesign::BlackmagicVideoFormats`  
`struct BlackmagicVideoFormats`  
_L446-480_
- desc: BlackmagicVideoFormats definition
- L469 _public prototype_ `BlackmagicVideoFormats(int32_t InDeviceId, bool bForOutput);`
- L470 _public prototype_ `~BlackmagicVideoFormats();`
- L472 _public prototype_ `BlackmagicVideoFormats(const BlackmagicVideoFormats&) = delete;`
- L473 _public prototype_ `BlackmagicVideoFormats& operator=(const BlackmagicVideoFormats&) = delete;`
- L475 _public prototype_ `int32_t GetNumSupportedFormat() const;`
- L476 _public prototype_ `VideoFormatDescriptor GetSupportedFormat(int32_t InIndex) const;`
- L479 _private member_ `Private::VideoFormatsScanner* Formats;`

#### struct `BlackmagicDesign::BlackmagicVideoFormats::VideoFormatDescriptor`  
`struct VideoFormatDescriptor`  
_L448-467_
- L450 _public prototype_ `VideoFormatDescriptor();`
- L452 _public member_ `FBlackmagicVideoFormat VideoFormatIndex;`
- L453 _public member_ `uint32_t FrameRateNumerator;`
- L454 _public member_ `uint32_t FrameRateDenominator;`
- L455 _public member_ `uint32_t ResolutionWidth;`
- L456 _public member_ `uint32_t ResolutionHeight;`
- L457 _public member_ `bool bIsProgressiveStandard;`
- L458 _public member_ `bool bIsInterlacedStandard;`
- L459 _public member_ `bool bIsPsfStandard;`
- L460 _public member_ `bool bIsSD;`
- L461 _public member_ `bool bIsHD;`
- L462 _public member_ `bool bIs2K;`
- L463 _public member_ `bool bIs4K;`
- L464 _public member_ `bool bIs8K;`
- L466 _public member_ `bool bIsValid;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace GPUTextureTransfer` (scope `UE`)
- L18 _namespace_ `namespace BlackmagicDesign`
- L20 _typedef_ `using LoggingCallbackPtr = void(*)(const TCHAR* Format, ...);` (scope `BlackmagicDesign`)
- L21 _typedef_ `using FBlackmagicVideoFormat = int32_t;` (scope `BlackmagicDesign`) — BMDDisplayMode
- L93 _namespace_ `namespace Private` (scope `BlackmagicDesign`)
- L484 _prototype_ `void SetLoggingCallbacks(LoggingCallbackPtr LogInfoFunc, LoggingCallbackPtr LogWarningFunc, LoggingCallbackPtr LogErrorFunc, LoggingCallbackPtr LogVerboseFunc);` (scope `BlackmagicDesign`) — Configure Logging
- L488 _prototype_ `bool ApiInitialization();` (scope `BlackmagicDesign`) — Initialization
- L489 _prototype_ `void ApiUninitialization();` (scope `BlackmagicDesign`)
- L493 _prototype_ `FUniqueIdentifier RegisterCallbackForChannel(const FChannelInfo& InChannelInfo, const FInputChannelOptions& InChannelOptions, ReferencePtr<IInputEventCallback> InCallback);` (scope `BlackmagicDesign`) — Register/Unregister
- L494 _prototype_ `void UnregisterCallbackForChannel(const FChannelInfo& InChannelInfo, FUniqueIdentifier InIdentifier);` (scope `BlackmagicDesign`)
- L496 _prototype_ `FUniqueIdentifier RegisterOutputChannel(const FChannelInfo& InChannelInfo, const FOutputChannelOptions& InChannelOptions, ReferencePtr<IOutputEventCallback> InCallback);` (scope `BlackmagicDesign`)
- L497 _prototype_ `void UnregisterOutputChannel(const FChannelInfo& InChannelInfo, FUniqueIdentifier InIdentifier, bool bCallCompleted);` (scope `BlackmagicDesign`)
- L498 _prototype_ `bool SendVideoFrameData(const FChannelInfo& InChannelInfo, const FFrameDescriptor& InFrame);` (scope `BlackmagicDesign`)
- L499 _prototype_ `bool SendVideoFrameData(const FChannelInfo& InChannelInfo, FFrameDescriptor_GPUDMA& InFrame);` (scope `BlackmagicDesign`)
- L501 _prototype_ `bool ShouldCaptureThisFrame(const FChannelInfo& InChannelInfo, ::FTimecode Timecode, uint32 FrameNumber);` (scope `BlackmagicDesign`) — Return whether to capture or discard a frame based on its timecode and frame number.
- L502 _prototype_ `bool SendAudioSamples(const FChannelInfo& InChannelInfo, const FAudioSamplesDescriptor& InSamples);` (scope `BlackmagicDesign`)

### `Plugins/Media/BlackmagicMedia/Source/BlackmagicCore/Public/BlackmagicReferencePtr.h` (Public)


#### class `BlackmagicDesign::ReferencePtr`  
`template<class T> class ReferencePtr`  
_L10-104_
- L13 _public function_ `ReferencePtr() : Pointer(nullptr)`
- L17 _public function_ `explicit ReferencePtr(T* InPointer) : Pointer(InPointer)`
- L26 _public function_ `ReferencePtr(const ReferencePtr<T>& InAutoPointer) : Pointer(InAutoPointer.Pointer)`
- L35 _public function_ `ReferencePtr(ReferencePtr&& InAutoPointer) : Pointer(InAutoPointer.Pointer)`
- L41 _public function_ `ReferencePtr& operator=(const ReferencePtr& InAutoPointer)`
- L52 _public function_ `ReferencePtr& operator=(ReferencePtr&& InAutoPointer)`
- L60 _public function_ `~ReferencePtr()`
- L68 _public function_ `T* operator->()`
- L73 _public function_ `void Reset()`
- L82 _public function_ `T* Get()`
- L87 _public function_ `const T* Get() const`
- L92 _public function_ `operator T*()`
- L97 _public function_ `operator const T*() const`
- L103 _private member_ `T* Pointer;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace BlackmagicDesign`
- L107 _function_ `template<class T > bool operator==(const ReferencePtr<T>& lhs, std::nullptr_t rhs) noexcept` (scope `BlackmagicDesign`)
- L109 _function_ `template< class T > bool operator==(std::nullptr_t lhs, const ReferencePtr<T>& rhs) noexcept` (scope `BlackmagicDesign`)
- L111 _function_ `template< class T > bool operator!=(const ReferencePtr<T>& lhs, std::nullptr_t rhs) noexcept` (scope `BlackmagicDesign`)
- L113 _function_ `template< class T > bool operator!=(std::nullptr_t lhs, const ReferencePtr<T>& rhs) noexcept` (scope `BlackmagicDesign`)
