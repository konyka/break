# Plugins / AjaCore

- module root: `Plugins/Media/AjaMedia/Source/Aja`
- headers: 14; symbols: 885
- symbol kinds: class=25, delegate=2, enum=11, enumerator=37, function=24, macro=7, member=332, namespace=28, prototype=374, struct=36, typedef=8, union=1
- PrivateDependencyModuleNames: GPUTextureTransfer, RenderCore
- PublicDependencyModuleNames: Core, RHI

### `Plugins/Media/AjaMedia/Source/Aja/Private/AutoDetectChannel.h` (Private)


#### class `AJA::Private::AutoDetectChannel`  
`class AutoDetectChannel`  
_L22-38_
- desc: AutoDetectChannel definition
- L25 _public prototype_ `AutoDetectChannel() = default;`
- L26 _public prototype_ `AutoDetectChannel(const AutoDetectChannel&) = delete;`
- L27 _public prototype_ `AutoDetectChannel& operator=(const AutoDetectChannel&) = delete;`
- L29 _public prototype_ `bool Initialize(IAJAAutoDetectCallbackInterface* InCallbackInterface);`
- L30 _public prototype_ `void Uninitialize();`
- L32 _public prototype_ `std::vector<AJAAutoDetectChannel::AutoDetectChannelData> GetFoundChannels() const;`
- L35 _private member_ `std::shared_ptr<AutoDetectChannelImpl> AutoDetectImplementation;`
- L36 _private member_ `std::shared_ptr<DeviceConnection> Device;`
- L37 _private member_ `std::weak_ptr<AutoDetectChannelInitialize_DeviceCommand> InitializeCommand;`

#### struct `AJA::Private::AutoDetectChannelInitialize_DeviceCommand`  
`struct AutoDetectChannelInitialize_DeviceCommand : DeviceCommand`  
_L43-50_
- inherits: `DeviceCommand`
- desc: AutoDetectChannelInitialize_DeviceCommand definition
- L45 _public prototype_ `AutoDetectChannelInitialize_DeviceCommand(const std::shared_ptr<DeviceConnection>& InConnection, const std::weak_ptr<AutoDetectChannelImpl>& InChannel);`
- L47 _public prototype_ `virtual void Execute(DeviceConnection::CommandList& InCommandList) override;`
- L49 _public member_ `std::weak_ptr<AutoDetectChannelImpl> AutoDetectImplementation;`

#### struct `AJA::Private::AutoDetectChannelUninitialize_DeviceCommand`  
`struct AutoDetectChannelUninitialize_DeviceCommand : DeviceCommand`  
_L55-62_
- inherits: `DeviceCommand`
- desc: AutoDetectChannelUninitialize_DeviceCommand definition
- L57 _public prototype_ `AutoDetectChannelUninitialize_DeviceCommand(const std::shared_ptr<DeviceConnection>& InConnection, const std::weak_ptr<AutoDetectChannelImpl>& InChannel);`
- L59 _public prototype_ `virtual void Execute(DeviceConnection::CommandList& InCommandList) override;`
- L61 _public member_ `std::shared_ptr<AutoDetectChannelImpl> AutoDetectImplementation;`

#### class `AJA::Private::AutoDetectChannelImpl`  
`class AutoDetectChannelImpl`  
_L67-96_
- desc: AutoDetectChannelImpl definition
- L70 _public prototype_ `AutoDetectChannelImpl() = delete;`
- L71 _public prototype_ `AutoDetectChannelImpl(IAJAAutoDetectCallbackInterface* InCallbackInterface);`
- L72 _public prototype_ `AutoDetectChannelImpl(const AutoDetectChannelImpl&) = delete;`
- L73 _public prototype_ `AutoDetectChannelImpl& operator=(const AutoDetectChannelImpl&) = delete;`
- L74 _public prototype_ `virtual ~AutoDetectChannelImpl();`
- L76 _public prototype_ `bool CanInitialize() const;`
- L77 _public prototype_ `bool Thread_Initialize(DeviceConnection::CommandList& InCommandList);`
- L78 _public prototype_ `void Uninitialize();`
- L79 _public prototype_ `void Thread_Destroy(DeviceConnection::CommandList& InCommandList);`
- L81 _public prototype_ `std::vector<AJAAutoDetectChannel::AutoDetectChannelData> GetFoundChannels() const;`
- L84 _private member_ `AJALock Lock;` — for callback
- L85 _private member_ `IAJAAutoDetectCallbackInterface* CallbackInterface;`
- L87 _private member_ `std::vector<AJAAutoDetectChannel::AutoDetectChannelData> FoundChannels;`
- L89 _private member_ `volatile bool bStopRequested;`
- L90 _private member_ `volatile bool bProcessCompleted;`
- L93 _private prototype_ `bool Thread_Configure(DeviceConnection::CommandList& InCommandList);`
- L94 _private prototype_ `void Thread_OnInitializationCompleted(bool bSucceed);`
- L95 _private prototype_ `bool Thread_Detect(int32_t InDeviceIndex, const AJADeviceScanner::DeviceInfo& InDeviceInfo);`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace AJA`
- L13 _namespace_ `namespace Private` (scope `AJA`)

### `Plugins/Media/AjaMedia/Source/Aja/Private/ChannelBase.h` (Private)


#### struct `AJA::Private::IOChannelInitialize_DeviceCommand`  
`struct IOChannelInitialize_DeviceCommand : DeviceCommand`  
_L21-28_
- inherits: `DeviceCommand`
- desc: IOChannelInitialize_DeviceCommand definition
- L23 _public prototype_ `IOChannelInitialize_DeviceCommand(const std::shared_ptr<DeviceConnection>& InConnection, const std::weak_ptr<ChannelThreadBase>& InChannel);`
- L25 _public prototype_ `virtual void Execute(DeviceConnection::CommandList& InCommandList) override;`
- L27 _public member_ `std::weak_ptr<ChannelThreadBase> ChannelThread;`

#### struct `AJA::Private::IOChannelUninitialize_DeviceCommand`  
`struct IOChannelUninitialize_DeviceCommand : DeviceCommand`  
_L32-43_
- inherits: `DeviceCommand`
- desc: IOChannelUninitialize_DeviceCommand definition
- L34 _public prototype_ `IOChannelUninitialize_DeviceCommand(const std::shared_ptr<DeviceConnection>& InConnection, const std::weak_ptr<ChannelThreadBase>& InChannel, TPromise<void> InCompletionPromise = {});`
- L36 _public prototype_ `virtual void Execute(DeviceConnection::CommandList& InCommandList) override;`
- L38 _public member_ `std::shared_ptr<ChannelThreadBase> ChannelThread;`
- L42 _private member_ `TPromise<void> CompletionPromise;` — Completion promise fired when the uninitialized command is done.

#### class `AJA::Private::ChannelThreadBase`  
`class ChannelThreadBase`  
_L47-147_
- desc: ChannelThreadBase OutputChannelThread
- L53 _public prototype_ `ChannelThreadBase() = delete;`
- L54 _public prototype_ `ChannelThreadBase(const ChannelThreadBase&) = delete;`
- L55 _public prototype_ `ChannelThreadBase& operator=(const ChannelThreadBase&) = delete;`
- L57 _public prototype_ `ChannelThreadBase(const AJADeviceOptions& InDevice, const AJAInputOutputChannelOptions& InOptions);`
- L58 _public prototype_ `virtual ~ChannelThreadBase();`
- L60 _public prototype_ `virtual bool CanInitialize() const;`
- L61 _public prototype_ `bool DeviceThread_Initialize(DeviceConnection::CommandList& InCommandList);`
- L62 _public prototype_ `virtual void Uninitialize();`
- L63 _public prototype_ `virtual void DeviceThread_Destroy(DeviceConnection::CommandList& InCommandList);`
- L66 _public function_ `const AJAInputOutputChannelOptions& GetOptions() const`
- L69 _public function_ `CNTV2Card& GetDevice() const` — CNTV2Card& GetDevice() { assert(Card); return *Card; } CNTV2Card& GetDevice() const { assert(Card); return *Card; }
- L70 _public function_ `CNTV2Card* GetDevicePtr() const`
- L72 _public prototype_ `AUTOCIRCULATE_STATUS GetCurrentAutoCirculateStatus() const;`
- L74 _public function_ `bool IsInput() const`
- L75 _public function_ `bool IsOutput() const`
- L77 _public function_ `bool UseAudio() const`
- L78 _public function_ `bool UseVideo() const`
- L79 _public function_ `bool UseAncillary() const`
- L80 _public function_ `bool UseAncillaryField2() const`
- L82 _public function_ `bool UseKey() const`
- L83 _public function_ `bool UseTimecode() const`
- L86 _public member_ `const AJADeviceOptions DeviceOption;`
- L87 _public member_ `std::shared_ptr<DeviceConnection> Device;`
- L90 _public member_ `AJALock Lock;` — for callback
- L92 _public member_ `NTV2Channel Channel;`
- L93 _public member_ `NTV2Channel KeyChannel;`
- L95 _public member_ `NTV2InputSource InputSource;`
- L96 _public member_ `NTV2InputSource KeySource;`
- L97 _public member_ `NTV2AudioSystem AudioSystem;`
- L99 _public member_ `NTV2FormatDescriptor FormatDescriptor;`
- L101 _public member_ `NTV2VideoFormat DesiredVideoFormat;` — DesiredVideoFormat and VideoFormat should match. There was a reason to have the 2 before (psf and levelB) but now they should be the same.
- L102 _public member_ `NTV2VideoFormat VideoFormat;`
- L104 _public member_ `AJATimeCodeBurn* TimecodeBurner;`
- L106 _public member_ `uint32_t BaseFrameIndex;`
- L108 _public member_ `uint32_t AncBufferSize;`
- L109 _public member_ `uint32_t AncF2BufferSize;`
- L110 _public member_ `uint32_t AudioBufferSize;`
- L111 _public member_ `uint32_t VideoBufferSize;`
- L113 _public member_ `bool bRegisteredChannel;`
- L114 _public member_ `bool bRegisteredKeyChannel;`
- L115 _public member_ `bool bRegisteredReference;`
- L116 _public member_ `bool bConnectedChannel;`
- L117 _public member_ `bool bConnectedKeyChannel;`
- L120 _protected prototype_ `virtual bool ChannelThread_Initialization(DeviceConnection::CommandList& InCommandList);`
- L121 _protected prototype_ `virtual bool DeviceThread_Configure(DeviceConnection::CommandList& InCommandList);`
- L122 _protected prototype_ `virtual bool DeviceThread_ConfigureAnc(DeviceConnection::CommandList& InCommandList);`
- L123 _protected prototype_ `virtual bool DeviceThread_ConfigureAudio(DeviceConnection::CommandList& InCommandList);`
- L124 _protected prototype_ `virtual bool DeviceThread_ConfigureVideo(DeviceConnection::CommandList& InCommandList);`
- L126 _protected prototype_ `virtual bool DeviceThread_ConfigureAutoCirculate(DeviceConnection::CommandList& InCommandList) = 0;`
- L127 _protected prototype_ `virtual bool DeviceThread_ConfigurePingPong(DeviceConnection::CommandList& InCommandList) = 0;`
- L129 _protected prototype_ `virtual void Thread_AutoCirculateLoop() = 0;`
- L130 _protected prototype_ `virtual void Thread_PingPongLoop() = 0;`
- L132 _protected prototype_ `void Thread_OnInitializationCompleted(bool bSucceed);`
- L135 _protected prototype_ `void BurnTimecode(const AJA::FTimecode& InTimecode, uint8_t* InVideoBuffer);` — Encode timecode onto a video buffer.
- L137 _protected prototype_ `void BurnTimecode(const AJA::FTimecode& InTimecode, const AJA::FTimecode& InTimecode2, uint8_t* InVideoBuffer);` — Burn two timecodes on the frame (Used for interlace debugging to identify the timecode of the two frames that make up an output frame.)
- L140 _private prototype_ `static void StaticThread(AJAThread* pThread, void* pContext);`
- L141 _private prototype_ `bool ChannelThread_ConfigureRouting(DeviceConnection::CommandList& InCommandList, NTV2FrameBufferFormat PixelFormat);`
- L144 _protected member_ `volatile bool bStopRequested;`
- L145 _protected member_ `AJAInputOutputChannelOptions Options;`
- L146 _protected member_ `AJAThread FrameThread;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace AJA`
- L13 _namespace_ `namespace Private` (scope `AJA`)

### `Plugins/Media/AjaMedia/Source/Aja/Private/Device.h` (Private)


#### class `AJA::Private::DeviceConnection`  
`class DeviceConnection`  
_L30-200_
- desc: The Device will Initialize itself. There is no callback to tell the user the Device is created properly. It should only be call from AJA thread. Other Channel will register and lock InitializationLock. The fist RegisterAndLockChannel will lock and complete the initialization.
- L33 _public member_ `static const uint32_t NumberOfFrameToAquire = 4;`
- L34 _public member_ `static const uint32_t NumberOfFrameForAutoCirculate = NumberOfFrameToAquire;`
- L35 _public member_ `static const uint32_t InvalidFrameBufferIndex = 0xFFFFFFFF;`
- L36 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnVerticalInterrupt, uint32 );`
- L97 _public prototype_ `DeviceConnection() = delete;`
- L98 _public prototype_ `DeviceConnection(const AJADeviceOptions& InDeviceOption);`
- L99 _public prototype_ `~DeviceConnection();`
- L100 _public prototype_ `DeviceConnection(const DeviceConnection&) = delete;`
- L101 _public prototype_ `DeviceConnection& operator=(const DeviceConnection&) = delete;`
- L103 _public prototype_ `static CNTV2Card* NewCNTV2Card(uint32_t InDeviceIndex);`
- L116 _public prototype_ `FDelegateHandle SetOnInterruptEvent(NTV2Channel InChannel, AJA::Private::DeviceConnection::FOnVerticalInterrupt::FDelegate OnInterrupt);` — Set a callback to be invoked whenever the card sends a vertical interrupt signal. @return a valid Delegate if the delegate was set correctly.
- L117 _public prototype_ `void ClearOnInterruptEvent(NTV2Channel InChannel, FDelegateHandle DelegateHandle);`
- L118 _public prototype_ `bool WaitForInputOrOutputInterrupt(NTV2Channel InChannel, int32_t InRepeatCount = 1, EInterruptType InInterrupt = EInterruptType::Auto);`
- L119 _public prototype_ `bool WaitForInputOrOutputInputField(NTV2Channel InChannel, int32_t InRepeatCount, NTV2FieldID& OutInputField);`
- L120 _public prototype_ `NTV2VideoFormat GetVideoFormat(NTV2Channel InChannel);`
- L121 _public prototype_ `uint32_t GetBaseFrameBufferIndex(NTV2Channel InChannel);`
- L122 _public prototype_ `bool WaitForInputFrameReceived(NTV2Channel InChannel);`
- L123 _public prototype_ `void OnInputFrameReceived(NTV2Channel InChannel);`
- L124 _public function_ `CNTV2Card* GetCard()`
- L125 _public prototype_ `void ClearFormat();`
- L126 _public prototype_ `void SetFormat(NTV2Channel InChannel, NTV2VideoFormat InFormat);`
- L156 _private function_ `bool Lock_IsInitialize() const`
- L157 _private prototype_ `bool Lock_Initialize();`
- L158 _private prototype_ `void Lock_UnInitialize();`
- L160 _private prototype_ `bool Lock_EnableChannel_SDILinkHelper(CNTV2Card* InCard, ETransportType InTransportType, NTV2Channel InChannel) const;`
- L161 _private prototype_ `bool Lock_EnableChannel_Helper(CNTV2Card* InCard, ETransportType InTransportType, NTV2InputSource InInputSource, NTV2Channel InChannel, bool InAsInput, bool bConnectChannel, bool bIsAutoDetected, ETimecodeFormat InTimecodeFormat, EPixelFormat InUEPixelFormat, NTV2VideoFormat InDesiredInputFormat, NTV2VideoFormat& OutFoundVideoFormat, FAjaHDROptions& InOutHDROptions);`
- L162 _private prototype_ `void Lock_SubscribeChannel_Helper(CNTV2Card* InCard, NTV2Channel InChannel, bool InAsInput) const;`
- L164 _private prototype_ `uint32_t Lock_AcquireBaseFrameIndex(NTV2Channel InChannel, NTV2VideoFormat InVideoFormat) const;`
- L167 _private member_ `AJADeviceOptions DeviceOption;`
- L170 _private member_ `AJALock ChannelInfoLock;` — Lock when we want to read and we are not under the ChannelLock. Use ChannelLock in the initialization phase.
- L171 _private member_ `std::vector<ChannelInfo*> ChannelInfos;`
- L173 _private member_ `CNTV2Card* Card;`
- L174 _private member_ `NTV2EveryFrameTaskMode TaskMode;`
- L175 _private member_ `bool bHasBiDirectionalSDI;`
- L178 _private member_ `bool bAnalogLtcFromReferenceInput;` — Is device's reference pin currently used to read LTC
- L179 _private member_ `NTV2FrameRate LTCFrameRate;`
- L181 _private member_ `bool bOutputReferenceSet;`
- L182 _private member_ `EAJAReferenceType OutputReferenceType;`
- L183 _private member_ `NTV2Channel OutputReferenceChannel;`
- L184 _private member_ `NTV2VideoFormat NotMultiVideoFormat;`
- L187 _public prototype_ `void AddCommand(const std::shared_ptr<DeviceCommand>& Command);`
- L188 _public prototype_ `void RemoveCommand(const std::shared_ptr<DeviceCommand>& Command);`
- L191 _private member_ `AJALock ChannelLock;`
- L192 _private member_ `AJAEvent CommandEvent;`
- L193 _private member_ `ThreadSafeQueue<std::shared_ptr<DeviceCommand>> Commands;`
- L194 _private member_ `volatile bool bStopRequested;`
- L195 _private member_ `AJAThread CommandThread;`
- L198 _private prototype_ `static void StaticThread(AJAThread* pThread, void* pContext);`
- L199 _private prototype_ `void Thread_CommandLoop();`

#### class `AJA::Private::DeviceConnection::SyncThreadInfoThread`  
`class SyncThreadInfoThread : public AJAThread`  
_L42-63_
- inherits: `AJAThread`
- L45 _public prototype_ `SyncThreadInfoThread(DeviceConnection* InDeviceConnection, ChannelInfo* InChannelInfo);`
- L47 _public function_ `FOnVerticalInterrupt& OnVerticalInterrupt()` — Delegate triggered whenever the VBI count has increased.
- L50 _private member_ `ChannelInfo* ChannelInfoPtr;`
- L51 _private member_ `DeviceConnection* DeviceConnectionPtr;`
- L53 _private member_ `std::mutex SyncMutex;`
- L54 _private member_ `std::condition_variable SyncCondition;`
- L55 _private member_ `volatile bool bWaitResult;`
- L56 _private member_ `FOnVerticalInterrupt OnVerticalInterruptDelegate;`
- L59 _public prototype_ `bool WaitForVerticalInterrupt(DeviceConnection* InDeviceConnection, ChannelInfo* InChannelInfo, uint32& OutSyncCount);`
- L60 _public prototype_ `static bool IsCurrentField(DeviceConnection* InDeviceConnection, ChannelInfo* InChannelInfo, NTV2FieldID InFieldId = NTV2_FIELD0);`
- L61 _public prototype_ `bool Wait_ExternalThread();`
- L62 _public prototype_ `virtual bool ThreadLoop() override;`

#### class `AJA::Private::DeviceConnection::WaitForInputInfo`  
`class WaitForInputInfo`  
_L65-74_
- L68 _private member_ `std::mutex SyncMutex;`
- L69 _private member_ `std::condition_variable SyncCondition;`
- L72 _public prototype_ `bool WaitForInput();`
- L73 _public prototype_ `void NotifyAll();`

#### struct `AJA::Private::DeviceConnection::ChannelInfo`  
`struct ChannelInfo`  
_L76-94_
- L78 _public prototype_ `ChannelInfo();`
- L81 _public member_ `std::unique_ptr<SyncThreadInfoThread> SyncThread;` — If the ref count > 1, a SyncThread will be spawn. See DeviceConnection::WaitForVerticalInterrupt.
- L82 _public member_ `std::unique_ptr<WaitForInputInfo> WaitForInput;`
- L83 _public member_ `ETransportType TransportType;`
- L84 _public member_ `NTV2Channel Channel;`
- L85 _public member_ `NTV2VideoFormat VideoFormat;`
- L86 _public member_ `ETimecodeFormat TimecodeFormat;`
- L87 _public member_ `int32_t RefCounter;`
- L88 _public member_ `uint32_t BaseFrameBufferIndex;`
- L89 _public member_ `bool bConnected;`
- L90 _public member_ `bool bIsOwned;`
- L91 _public member_ `bool bIsInput;`
- L92 _public member_ `bool bIsAutoDetected;`
- L93 _public member_ `bool bGenlockChannel;`

#### enum `AJA::Private::DeviceConnection::EInterruptType`  
`enum class EInterruptType`  
_L105-110_
- L107 _public enumerator_ `VerticalInterrupt`
- L108 _public enumerator_ `InputField`
- L109 _public enumerator_ `Auto`

#### struct `AJA::Private::DeviceConnection::CommandList`  
`struct CommandList`  
_L129-151_
- L132 _public prototype_ `CommandList(DeviceConnection&);`
- L135 _public prototype_ `bool RegisterChannel(ETransportType InTransportType, NTV2InputSource InInputSource, NTV2Channel InChannel, bool bInAsInput, bool bInAsGenlock, bool bConnectChannel, ETimecodeFormat InTimecodeFormat, EPixelFormat InUEPixelFormat, NTV2VideoFormat InDesiredInputFormat, bool bInAsOwner, bool bInIsAutoDetected);`
- L138 _public prototype_ `bool UnregisterChannel(NTV2Channel InChannel, bool bInAsOwner);`
- L140 _public prototype_ `bool IsChannelConnect(NTV2Channel InChannel);`
- L141 _public prototype_ `void SetChannelConnected(NTV2Channel InChannel, bool bConnected);`
- L143 _public prototype_ `bool RegisterAnalogLtc(EAnalogLTCSource InSource, NTV2FrameRate InFrameRate, bool bUseReferencePin);`
- L144 _public prototype_ `void UnregisterAnalogLtc(bool bUseReferencePin);`
- L146 _public prototype_ `bool RegisterReference(EAJAReferenceType OutputReferenceType, NTV2Channel InChannel);`
- L147 _public prototype_ `void UnregisterReference(NTV2Channel InChannel);`
- L150 _private member_ `DeviceConnection& Connection;`

#### struct `AJA::Private::DeviceCommand`  
`struct DeviceCommand`  
_L204-212_
- desc: DeviceCommand definition
- L206 _public prototype_ `DeviceCommand(const std::shared_ptr<DeviceConnection>& InConnection);`
- L207 _public function_ `virtual ~DeviceCommand()`
- L209 _public prototype_ `virtual void Execute(DeviceConnection::CommandList& InCommandList) = 0;`
- L211 _public member_ `std::shared_ptr<DeviceConnection> Device;`

#### class `AJA::Private::DeviceCache`  
`class DeviceCache`  
_L216-228_
- desc: DeviceCache definition
- L219 _public member_ `static const uint32_t MaxNumberOfDevice = 8;`
- L222 _public prototype_ `static std::shared_ptr<DeviceConnection> GetDevice(const AJADeviceOptions& InDeviceOption);` — This is a slow operation. Should be call from a thread
- L223 _public prototype_ `static void RemoveDevice(const std::shared_ptr<DeviceConnection>& InDevice);`
- L226 _private member_ `AJALock Lock;`
- L227 _private member_ `std::weak_ptr<DeviceConnection> DeviceInstance[MaxNumberOfDevice];`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace AJA`
- L18 _namespace_ `namespace Private` (scope `AJA`)
- L36 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnVerticalInterrupt, uint32 );`

### `Plugins/Media/AjaMedia/Source/Aja/Private/DeviceScanner.h` (Private)


#### class `AJA::Private::DeviceScanner`  
`class DeviceScanner`  
_L16-31_
- desc: DeviceScanner definition
- L19 _public prototype_ `DeviceScanner();`
- L20 _public prototype_ `~DeviceScanner();`
- L22 _public prototype_ `DeviceScanner(const DeviceScanner&) = delete;`
- L23 _public prototype_ `DeviceScanner& operator=(const DeviceScanner&) = delete;`
- L25 _public prototype_ `int32_t GetNumDevices() const;`
- L26 _public prototype_ `bool GetDeviceTextId(int32_t InDeviceIndex, AJADeviceScanner::FormatedTextType& OutTextId) const;`
- L27 _public prototype_ `bool GetDeviceInfo(int32_t InDeviceIndex, AJADeviceScanner::DeviceInfo& OutDeviceInfo) const;`
- L30 _private member_ `CNTV2DeviceScanner* Scanner;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace AJA`
- L12 _namespace_ `namespace Private` (scope `AJA`)

### `Plugins/Media/AjaMedia/Source/Aja/Private/Helpers.h` (Private)


#### enum `AJA::Private::ERP188Source`  
`enum class ERP188Source`  
_L56-61_
- L58 _public enumerator_ `LTC = 0`
- L59 _public enumerator_ `VITC1 = 1`
- L60 _public enumerator_ `VITC2 = 2`

#### enum `AJA::Private::EAnalogLTCSource`  
`enum class EAnalogLTCSource`  
_L63-67_
- L65 _public enumerator_ `LTC1 = 0`
- L66 _public enumerator_ `LTC2` — Max number of LTC from aja API

#### struct `AJA::Private::Helpers`  
`struct Helpers`  
_L79-152_
- L81 _public prototype_ `static bool GetTimecode(CNTV2Card* InCard, NTV2Channel InChannel, const NTV2VideoFormat InVideoFormat, uint32_t InFrameIndex, ETimecodeFormat InTimecodeFormat, bool bLogError, FTimecode& OutTimecode);`
- L82 _public prototype_ `static bool GetTimecode(CNTV2Card* InCard, EAnalogLTCSource AnalogLTCInput, const NTV2VideoFormat InVideoFormat, bool bInLogError, FTimecode& OutTimecode);`
- L83 _public prototype_ `static ETimecodeFormat GetTimecodeFormat(CNTV2Card* InCard, NTV2Channel InChannel);`
- L88 _public prototype_ `static FTimecode ConvertTimecodeFromRP188(const RP188_STRUCT& InRP188, const NTV2VideoFormat InVideoFormat);` — Output timecode will be usable directly by UE. If frame rate is greater than 30, frame number will be expanded to have a linear frame number up to frame rate -1. i.e. 0, 1, 2.., 59
- L89 _public prototype_ `static FTimecode ConvertTimecodeFromRP188(const NTV2_RP188& InRP188, const NTV2VideoFormat InVideoFormat);`
- L90 _public prototype_ `static NTV2_RP188 ConvertTimecodeToRP188(const FTimecode& Timecode);`
- L92 _public prototype_ `static NTV2FrameBufferFormat ConvertPixelFormatToFrameBufferFormat(EPixelFormat InPixelFormat);`
- L93 _public prototype_ `static EPixelFormat ConvertFrameBufferFormatToPixelFormat(NTV2FrameBufferFormat InPixelFormat);`
- L94 _public prototype_ `static AJA_PixelFormat ConvertToPixelFormat(EPixelFormat InPixelFormat);`
- L97 _public prototype_ `static NTV2HDRXferChars ConvertToAjaHDRXferChars(EAjaHDRMetadataEOTF HDRXferChars);` — Convert HDR transfer characteristics from Unreal to Aja format.
- L99 _public prototype_ `static EAjaHDRMetadataEOTF ConvertFromAjaHDRXferChars(NTV2HDRXferChars XferChar);` — Convert HDR transfer characteristics from Aja to Unreal format.
- L101 _public prototype_ `static NTV2HDRColorimetry ConvertToAjaHDRColorimetry(EAjaHDRMetadataGamut Colorimetry);` — Convert HDR colorimetry from Unreal to Aja format.
- L103 _public prototype_ `static EAjaHDRMetadataGamut ConvertFromAjaHDRColorimetry(NTV2HDRColorimetry);` — Convert HDR colorimetry from Aja to unreal format.
- L105 _public prototype_ `static NTV2HDRLuminance ConvertToAjaHDRLuminance(EAjaHDRMetadataLuminance HDRLuminance);` — Convert HDR luminance from Unreal to Aja format.
- L107 _public prototype_ `static EAjaHDRMetadataLuminance ConvertFromAjaHDRLuminance(NTV2HDRLuminance AjaHDRLuminance);` — Convert HDR luminance from Aja to Unreal format.
- L109 _public prototype_ `static NTV2FrameRate ConvertToFrameRate(uint32_t InNumerator, uint32_t InDenominator);`
- L110 _public prototype_ `static FFrameRate ConvertToUnrealFramerate(NTV2VideoFormat InVideoFormat);`
- L111 _public prototype_ `static TimecodeFormat ConvertToTimecodeFormat(NTV2VideoFormat InVideoFormat);`
- L113 _public prototype_ `static bool TryVideoFormatIndexToNTV2VideoFormat(FAJAVideoFormat InVideoFormatIndex, NTV2VideoFormat& OutFoundVideoFormat);`
- L114 _public prototype_ `static bool GetInputVideoFormat(CNTV2Card* InCard, ETransportType InTransportType, NTV2Channel InChannel, NTV2InputSource InInputSource, NTV2VideoFormat InExpectedVideoFormat, NTV2VideoFormat& OutFoundVideoFormat, bool bSetSDIConversion, std::string& OutFailedReason, bool bEnforceExpectedFormat = true);`
- L116 _public prototype_ `static bool GetInputHDRMetadata(CNTV2Card* InCard, NTV2Channel InChannel, FAjaHDROptions& OutHDRMetadata);` — Fetch HDR Metadata from VPID registers.
- L117 _public prototype_ `static std::optional<NTV2VideoFormat> GetInputVideoFormat(CNTV2Card* InCard, ETransportType InTransportType, NTV2Channel InChannel, NTV2InputSource InInputSource, NTV2VideoFormat InExpectedVideoFormat, bool bSetSDIConversion, std::string& OutFailedReason);`
- L118 _public prototype_ `static bool CompareFormats(NTV2VideoFormat LHS, NTV2VideoFormat& RHS, std::string& OutFailedReason);`
- L119 _public prototype_ `static void RouteSdiSignal(CNTV2Card* InCard, ETransportType InTransportType, NTV2Channel InChannel, NTV2VideoFormat InVideoFormat, NTV2FrameBufferFormat InPixelFormat, bool bIsInput, bool bIsInputColorRgb, bool bWillUseKey);`
- L120 _public prototype_ `static void RouteHdmiSignal(CNTV2Card* InCard, ETransportType InTransportType, NTV2InputSource InputSource, NTV2Channel InChannel, NTV2FrameBufferFormat InPixelFormat, bool bIsInput);`
- L121 _public prototype_ `static void RouteKeySignal(CNTV2Card* InCard, ETransportType InTransportType, NTV2Channel InChannel, NTV2Channel InKeyChannel, NTV2FrameBufferFormat InPixelFormat, bool bIsInput);`
- L122 _public prototype_ `static NTV2InputCrosspointID Get425MuxInput(const NTV2Channel inChannel);`
- L123 _public prototype_ `static NTV2OutputCrosspointID Get425MuxOutput(const NTV2Channel inChannel, const bool inIsRGB);`
- L124 _public prototype_ `static NTV2InputCrosspointID Get4KHDMI425MuxInput(const NTV2InputSource InInputSource, const UWord inQuadrant);`
- L125 _public prototype_ `static NTV2OutputCrosspointID Get4KHDMI425MuxOutput(const NTV2InputSource InInputSource, const UWord inQuadrant, const bool inIsRGB);`
- L127 _public prototype_ `static bool SetSDIOutLevelAtoLevelBConversion(CNTV2Card* InCard, ETransportType InTransportType, NTV2Channel InChannel, NTV2VideoFormat InFormat, bool bValue);`
- L128 _public prototype_ `static void SetSDIInLevelBtoLevelAConversion(CNTV2Card* InCard, ETransportType InTransportType, NTV2Channel InChannel, NTV2VideoFormat InFormat, NTV2VideoFormat& OutFormat);`
- L130 _public prototype_ `static bool ConvertTransportForDevice(CNTV2Card* InCard, uint32_t DeviceIndex, ETransportType& InOutTransportType, NTV2VideoFormat DesiredVideoFormat);`
- L132 _public prototype_ `static NTV2Channel GetTransportTypeChannel(ETransportType InTransportType, NTV2Channel InChannel);`
- L133 _public prototype_ `static int32_t GetNumberOfLinkChannel(ETransportType InTransportType);`
- L134 _public prototype_ `static bool IsTsiRouting(ETransportType InTransportType);`
- L135 _public prototype_ `static bool IsSdiTransport(ETransportType InTransportType);`
- L136 _public prototype_ `static bool IsHdmiTransport(ETransportType InTransportType);`
- L137 _public prototype_ `static const char* TransportTypeToString(ETransportType InTransportType);`
- L138 _public prototype_ `static const char* ReferenceTypeToString(EAJAReferenceType InReferenceType);`
- L140 _public prototype_ `static NTV2VideoFormat Get372Format(NTV2VideoFormat InFormat);`
- L141 _public prototype_ `static NTV2VideoFormat GetLevelA(NTV2VideoFormat InFormat);`
- L142 _public prototype_ `static NTV2VideoFormat GetSDI4kTSIFormat(NTV2VideoFormat InFormat);`
- L144 _public prototype_ `static bool IsCurrentInputField(CNTV2Card* InCard, NTV2Channel InChannel, NTV2FieldID InFieldId);`
- L145 _public prototype_ `static bool IsCurrentOutputField(CNTV2Card* InCard, NTV2Channel InChannel, NTV2FieldID InFieldId);`
- L147 _public prototype_ `static FTimecode AdjustTimecodeForUE(CNTV2Card* InCard, NTV2Channel InChannel, NTV2VideoFormat InVideoFormat, const FTimecode& InTimecode, const FTimecode& InPreviousTimecode, ULWord& InOutPreviousVerticalInterruptCount);`
- L148 _public prototype_ `static FTimecode AdjustTimecodeFromUE(NTV2VideoFormat InVideoFormat, const FTimecode& InTimecode);`
- L149 _public prototype_ `static bool IsDesiredTimecodePresent(CNTV2Card* InCard, NTV2Channel InChannel, ETimecodeFormat InDesiredFormat, const ULWord InDBBRegister, bool bInLogError);`
- L151 _public prototype_ `static NTV2Channel GetOverrideChannel(NTV2InputSource InInputSource, NTV2Channel InChannel, ETransportType InTransportType);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define MSWindows 1`
- L10 _macro_ `#define AJA_WINDOWS 1`
- L11 _macro_ `#define AJA_NO_AUTOIMPORT 1`
- L52 _namespace_ `namespace AJA`
- L54 _namespace_ `namespace Private` (scope `AJA`)
- L71 _macro_ `#define AJA_CHECK ensure` — #define AJA_CHECK(FUNCTION) { if (!(FUNCTION)) { *reinterpret_cast<char*>(0) = 0; } }
- L73 _macro_ `#define AJA_CHECK check`
- L76 _macro_ `#define AJA_TEST_MEMORY_BUFFER 0`
- L77 _macro_ `#define AJA_TEST_MEMORY_END_TAG 0x89`

### `Plugins/Media/AjaMedia/Source/Aja/Private/InputChannel.h` (Private)


#### class `AJA::Private::InputChannel`  
`class InputChannel`  
_L16-36_
- desc: InputChannel definition
- L19 _public prototype_ `InputChannel() = default;`
- L20 _public prototype_ `InputChannel(const InputChannel&) = delete;`
- L21 _public prototype_ `InputChannel& operator=(const InputChannel&) = delete;`
- L23 _public prototype_ `bool Initialize(const AJADeviceOptions& InDevice, const AJAInputOutputChannelOptions& Options);`
- L24 _public prototype_ `void Uninitialize();`
- L26 _public prototype_ `AUTOCIRCULATE_STATUS GetCurrentAutoCirculateStatus() const;`
- L27 _public prototype_ `const AJAInputOutputChannelOptions& GetOptions() const;`
- L28 _public prototype_ `const AJADeviceOptions& GetDeviceOptions() const;`
- L32 _private member_ `std::shared_ptr<InputChannelThread> ChannelThread;`
- L33 _private member_ `std::shared_ptr<DeviceConnection> Device;`
- L34 _private member_ `std::weak_ptr<IOChannelInitialize_DeviceCommand> InitializeCommand;`

#### class `AJA::Private::InputChannelThread`  
`class InputChannelThread : public ChannelThreadBase`  
_L40-80_
- inherits: `ChannelThreadBase`
- desc: InputChannelThread definition
- L42 _private typedef_ `using Super = ChannelThreadBase;`
- L44 _public prototype_ `InputChannelThread(InputChannel* InOwner, const AJADeviceOptions& InDevice, const AJAInputOutputChannelOptions& InOptions);`
- L45 _public prototype_ `virtual ~InputChannelThread();`
- L47 _public prototype_ `virtual void DeviceThread_Destroy(DeviceConnection::CommandList& InCommandList) override;`
- L50 _protected prototype_ `virtual bool DeviceThread_ConfigureAnc(DeviceConnection::CommandList& InCommandList) override;`
- L51 _protected prototype_ `virtual bool DeviceThread_ConfigureAudio(DeviceConnection::CommandList& InCommandList) override;`
- L52 _protected prototype_ `virtual bool DeviceThread_ConfigureVideo(DeviceConnection::CommandList& InCommandList) override;`
- L54 _protected prototype_ `virtual bool DeviceThread_ConfigureAutoCirculate(DeviceConnection::CommandList& InCommandList) override;`
- L55 _protected prototype_ `virtual bool DeviceThread_ConfigurePingPong(DeviceConnection::CommandList& InCommandList) override;`
- L57 _protected prototype_ `virtual void Thread_AutoCirculateLoop() override;`
- L58 _protected prototype_ `virtual void Thread_PingPongLoop() override;`
- L60 _protected member_ `uint8_t* AncBuffer;`
- L61 _protected member_ `uint8_t* AncF2Buffer;`
- L62 _protected member_ `uint8_t* AudioBuffer;`
- L63 _protected member_ `uint8_t* VideoBuffer;`
- L65 _protected member_ `uint32_t PingPongDropCount;`
- L75 _private prototype_ `EVerifyFormatResult VerifyFormat();`
- L78 _private member_ `InputChannel* Owner = nullptr;`

#### enum `AJA::Private::InputChannelThread::EVerifyFormatResult`  
`enum class EVerifyFormatResult : uint8_t`  
_L68-73_
- L70 _public enumerator_ `Failure`
- L71 _public enumerator_ `Success`
- L72 _public enumerator_ `FormatChange`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace AJA`
- L10 _namespace_ `namespace Private` (scope `AJA`)

### `Plugins/Media/AjaMedia/Source/Aja/Private/OutputChannel.h` (Private)


#### class `AJA::Private::OutputChannel`  
`class OutputChannel`  
_L22-50_
- desc: OutputChannel definition
- L25 _public prototype_ `OutputChannel() = default;`
- L26 _public prototype_ `OutputChannel(const OutputChannel&) = delete;`
- L27 _public prototype_ `OutputChannel& operator=(const OutputChannel&) = delete;`
- L29 _public prototype_ `bool Initialize(const AJADeviceOptions& InDevice, const AJAInputOutputChannelOptions& Options);`
- L30 _public prototype_ `void Uninitialize(TPromise<void> CompletionPromise);`
- L32 _public prototype_ `bool SetAncillaryFrameData(const AJAOutputFrameBufferData& InFrameData, uint8_t* AncillaryBuffer, uint32_t AncillaryBufferSize);`
- L33 _public prototype_ `bool SetAudioFrameData(const AJAOutputFrameBufferData& InFrameData, uint8_t* InAudioBuffer, uint32_t InAudioBufferSize);`
- L34 _public prototype_ `bool SetVideoFrameData(const AJAOutputFrameBufferData& InFrameData, uint8_t* InVideoBuffer, uint32_t InVideoBufferSize);`
- L35 _public prototype_ `bool DMAWriteAudio(const uint8_t* InAudioBuffer, int32_t InAudioBufferSize);`
- L36 _public prototype_ `bool SetVideoFrameData(const AJAOutputFrameBufferData& InFrameData, FRHITexture* RHITexture);`
- L37 _public prototype_ `bool ShouldCaptureThisFrame(::FTimecode Timeocode, uint32 SourceFrameNumber);`
- L38 _public prototype_ `bool GetOutputDimension(uint32_t& OutWidth, uint32_t& OutHeight) const;`
- L39 _public prototype_ `int32_t GetNumAudioSamplesPerFrame(const AJAOutputFrameBufferData& InFrameData) const;`
- L42 _private member_ `std::shared_ptr<OutputChannelThread> ChannelThread;`
- L43 _private member_ `std::shared_ptr<DeviceConnection> Device;`
- L45 _private member_ `uint32 BufferFreeIndex[2] = { 0, 0 };` — VBI Buffer count where [x] will be done transferring on the wire.
- L47 _private member_ `uint32 BufferFrameIdMapping[2] = { 0, 0 };` — Debug information used to map a VBI event to a UE frame number.
- L48 _private member_ `std::weak_ptr<IOChannelInitialize_DeviceCommand> InitializeCommand;`
- L49 _private member_ `uint32_t CurrentOutFrame = 0;`

#### class `AJA::Private::OutputChannelThread`  
`class OutputChannelThread : public ChannelThreadBase`  
_L54-182_
- inherits: `ChannelThreadBase`
- desc: OutputChannel OutputChannelThread
- L57 _private typedef_ `using Super = ChannelThreadBase;`
- L59 _public prototype_ `OutputChannelThread(const AJADeviceOptions& InDevice, const AJAInputOutputChannelOptions& InOptions);`
- L60 _public prototype_ `~OutputChannelThread();`
- L62 _public prototype_ `virtual bool CanInitialize() const override;`
- L63 _public prototype_ `virtual void Uninitialize() override;`
- L64 _public prototype_ `virtual void DeviceThread_Destroy(DeviceConnection::CommandList& InCommandList) override;`
- L66 _public prototype_ `bool SetAncillaryFrameData(const AJAOutputFrameBufferData& InFrameData, uint8_t* AncillaryBuffer, uint32_t AncillaryBufferSize);`
- L67 _public prototype_ `bool SetAudioFrameData(const AJAOutputFrameBufferData& InFrameData, uint8_t* AudioBuffer, uint32_t AudioBufferSize);`
- L68 _public prototype_ `bool SetVideoFrameData(const AJAOutputFrameBufferData& InFrameData, uint8_t* VideoBuffer, uint32_t VideoBufferSize);`
- L69 _public prototype_ `bool SetVideoFrameData(const AJAOutputFrameBufferData& InFrameData, FRHITexture* RHITexture);`
- L70 _public prototype_ `bool ShouldCaptureThisFrame(::FTimecode Timecode, uint32 SourceFrameNumber);`
- L71 _public prototype_ `bool DMAWriteAudio(const uint8_t* InAudioBuffer, int32_t BufferSize);`
- L74 _protected prototype_ `virtual bool DeviceThread_ConfigureAnc(DeviceConnection::CommandList& InCommandList) override;`
- L75 _protected prototype_ `virtual bool DeviceThread_ConfigureAudio(DeviceConnection::CommandList& InCommandList) override;`
- L76 _protected prototype_ `virtual bool DeviceThread_ConfigureVideo(DeviceConnection::CommandList& InCommandList) override;`
- L78 _protected prototype_ `virtual bool DeviceThread_ConfigureAutoCirculate(DeviceConnection::CommandList& InCommandList) override;`
- L79 _protected prototype_ `virtual bool DeviceThread_ConfigurePingPong(DeviceConnection::CommandList& InCommandList) override;`
- L81 _protected prototype_ `virtual void Thread_AutoCirculateLoop() override;`
- L82 _protected prototype_ `virtual void Thread_PingPongLoop() override;`
- L85 _private prototype_ `bool IsFrameReadyToBeRead(Frame* InFrame);`
- L86 _private prototype_ `void PushWhenFrameReady(Frame* InFrame);`
- L87 _private prototype_ `Frame* FetchAvailableWritingFrame(const AJAOutputFrameBufferData& InFrameData);`
- L88 _private prototype_ `Frame* Thread_FetchAvailableReadingFrame();`
- L89 _private prototype_ `void Thread_TestInterlacedOutput(Frame* InFrame);`
- L91 _private prototype_ `void Thread_PushAvailableReadingFrame(Frame* InCurrentReadingFrame);`
- L92 _private prototype_ `void ThreadLock_PingPongOutputLoop_Memset0(Frame* InCurrentReadingFrame);`
- L95 _private prototype_ `bool Thread_GetAudioOffset(int32& OutAudioOffset);` — Get the number of bytes separating the audio write and play head.
- L96 _private prototype_ `bool Thread_GetAudioOffsetInSeconds(double& OutAudioOffset);`
- L97 _private prototype_ `bool Thread_GetAudioOffsetInSamples(int32& OutAudioOffset);`
- L98 _private prototype_ `bool Thread_TransferAudioBuffer(const uint8* InBuffer, int32 InBufferSize);`
- L99 _private prototype_ `bool Thread_HandleAudio(const FString& OutputMethod, Frame* AvailableReadingFrame);`
- L100 _private prototype_ `bool Thread_HandleLostFrameAudio();`
- L101 _private prototype_ `bool Thread_ShouldPauseAudioOutput();`
- L104 _private prototype_ `void OnVerticalInterrupt(uint32 SyncCount) const;` — Callback on the vertical interrupt used to keep track of which buffers are currently outputting and to trace debug information.
- L136 _private member_ `uint32_t PingPongDropCount;`
- L137 _private member_ `uint32_t LostFrameCounter;`
- L139 _private member_ `AJALock FrameLock;` — to lock the transfer of frame ptr
- L140 _private member_ `std::vector<Frame*> AllFrames;`
- L141 _private member_ `std::vector<Frame*> FrameReadyToRead;` — Ready to be copied on the AJA
- L142 _private member_ `std::vector<Frame*> FrameReadyToWrite;` — Ready to be used by Unreal Engine
- L145 _private member_ `bool bIsSSE2Available;`
- L146 _private member_ `bool bIsFieldAEven;`
- L147 _private member_ `bool bIsFirstFetch;`
- L150 _private member_ `bool bOutputWithReduceWaiting = false;` — Enabled through Aja.PingPongVersion 1, will wait on a frame received event before falling back on a WaitForVerticalInterrupt call.
- L152 _private member_ `bool bTraceDebugMarkers = false;` — Indicates if OutputChannel should trace debug information. (Disabled by default to avoid cluttering Insights Traces).
- L154 _private member_ `bool bInterlacedTest_ExpectFirstLineToBeWhite;`
- L155 _private member_ `uint32_t InterlacedTest_FrameCounter;`
- L157 _private member_ `bool bDMABuffersRegistered = false;`
- L159 _private member_ `std::atomic<ULWord> CurrentAudioWriteOffset = 0;`
- L160 _private member_ `int32_t NumSamplesPerFrame = 0;`
- L161 _private member_ `std::atomic<ULWord> AudioPlayheadLastPosition = 0;`
- L164 _private member_ `FCriticalSection DeviceCriticalSection;` — Used to protect access to the device when accessed by the audio thread.
- L166 _private member_ `UE::GPUTextureTransfer::TextureTransferPtr TextureTransfer = nullptr;`
- L169 _private member_ `uint32 BufferFreeIndex[2] = { 0, 0 };` — VBI count where BufferFreeIndex[x] will be done transferring on the wire.
- L172 _private member_ `uint32 BufferFrameIdMapping[2] = { 0, 0 };` — Debug information used to map a VBI event to a UE frame number.
- L175 _private member_ `FEvent* FrameAvailableEvent = nullptr;` — Event triggered whenever a frame is pushed by Unreal to the FrameReadyToRead queue.
- L178 _private member_ `FFrameRate FrameRate;` — Output framerate.
- L181 _private member_ `FDelegateHandle InterruptEventHandle;` — Handle to the delegate that's triggered when a card emits a vertical interrupt event.

#### struct `AJA::Private::OutputChannelThread::Frame`  
`struct Frame`  
_L106-134_
- L108 _public prototype_ `Frame();`
- L109 _public prototype_ `~Frame();`
- L110 _public prototype_ `Frame(const Frame&) = delete;`
- L111 _public prototype_ `Frame& operator=(const Frame&) = delete;`
- L113 _public member_ `uint8_t* AncBuffer;`
- L114 _public member_ `uint8_t* AncF2Buffer;`
- L115 _public member_ `uint8_t* AudioBuffer;`
- L116 _public member_ `uint8_t* VideoBuffer;`
- L117 _public member_ `uint32_t CopiedAncBufferSize;`
- L118 _public member_ `uint32_t CopiedAncF2BufferSize;`
- L119 _public member_ `uint32_t CopiedAudioBufferSize;`
- L120 _public member_ `uint32_t CopiedVideoBufferSize;`
- L122 _public member_ `uint32_t FrameIdentifier;`
- L123 _public member_ `uint32_t FrameIdentifierF2;` — used in interlaced
- L124 _public member_ `FTimecode Timecode;`
- L125 _public member_ `FTimecode Timecode2;`
- L127 _public member_ `bool bAncLineFilled;`
- L128 _public member_ `bool bAncF2LineFilled;` — used in interlaced
- L129 _public member_ `bool bAudioLineFilled;`
- L130 _public member_ `bool bVideoLineFilled;`
- L131 _public member_ `bool bVideoF2LineFilled;` — used in interlaced
- L133 _public prototype_ `void Clear();`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace AJA`
- L15 _namespace_ `namespace Private` (scope `AJA`)

### `Plugins/Media/AjaMedia/Source/Aja/Private/SSE2MemCpy.h` (Private)


#### Free symbols / members of external scopes

- L3 _namespace_ `namespace AJA`
- L5 _namespace_ `namespace Private` (scope `AJA`)
- L7 _prototype_ `bool IsSSE2Available();` (scope `AJA::Private`)
- L8 _prototype_ `bool IsCorrectlyAlignedForSSE2MemCpy(const void* InDst, const void* InSrc, unsigned int InSize);` (scope `AJA::Private`)
- L9 _prototype_ `void SSE2MemCpy(const void* InDst, const void* InSrc, unsigned int InSize);` (scope `AJA::Private`)

### `Plugins/Media/AjaMedia/Source/Aja/Private/SyncChannel.h` (Private)


#### class `AJA::Private::SyncChannel`  
`class SyncChannel`  
_L21-40_
- desc: SyncChannel definition
- L24 _public prototype_ `SyncChannel() = default;`
- L25 _public prototype_ `SyncChannel(const SyncChannel&) = delete;`
- L26 _public prototype_ `SyncChannel& operator=(const SyncChannel&) = delete;`
- L28 _public prototype_ `bool Initialize(const AJADeviceOptions& InDevice, const AJASyncChannelOptions& InOptions);`
- L29 _public prototype_ `void Uninitialize();`
- L31 _public prototype_ `bool WaitForSync();`
- L32 _public prototype_ `bool GetTimecode(FTimecode& OutTimecode);`
- L33 _public prototype_ `bool GetSyncCount(uint32_t& OutCount) const;`
- L34 _public prototype_ `bool GetVideoFormat(NTV2VideoFormat& OutVideoFormat);`
- L37 _private member_ `std::shared_ptr<SyncChannelImpl> SyncImplementation;`
- L38 _private member_ `std::shared_ptr<DeviceConnection> Device;`
- L39 _private member_ `std::weak_ptr<SyncChannelInitialize_DeviceCommand> InitializeCommand;`

#### struct `AJA::Private::SyncChannelInitialize_DeviceCommand`  
`struct SyncChannelInitialize_DeviceCommand : DeviceCommand`  
_L44-51_
- inherits: `DeviceCommand`
- desc: SyncChannelInitialize_DeviceCommand definition
- L46 _public prototype_ `SyncChannelInitialize_DeviceCommand(const std::shared_ptr<DeviceConnection>& InConnection, const std::weak_ptr<SyncChannelImpl>& InChannel);`
- L48 _public prototype_ `virtual void Execute(DeviceConnection::CommandList& InCommandList) override;`
- L50 _public member_ `std::weak_ptr<SyncChannelImpl> SyncImplementation;`

#### struct `AJA::Private::SyncChannelUninitialize_DeviceCommand`  
`struct SyncChannelUninitialize_DeviceCommand : DeviceCommand`  
_L55-62_
- inherits: `DeviceCommand`
- desc: SyncChannelUninitialize_DeviceCommand definition
- L57 _public prototype_ `SyncChannelUninitialize_DeviceCommand(const std::shared_ptr<DeviceConnection>& InConnection, const std::weak_ptr<SyncChannelImpl>& InChannel);`
- L59 _public prototype_ `virtual void Execute(DeviceConnection::CommandList& InCommandList) override;`
- L61 _public member_ `std::shared_ptr<SyncChannelImpl> SyncImplementation;`

#### class `AJA::Private::SyncChannelImpl`  
`class SyncChannelImpl`  
_L67-118_
- desc: SyncChannelImpl definition
- L70 _public prototype_ `SyncChannelImpl() = delete;`
- L71 _public prototype_ `SyncChannelImpl(const AJADeviceOptions& InDevice, const AJASyncChannelOptions& InOptions);`
- L72 _public prototype_ `SyncChannelImpl(const SyncChannelImpl&) = delete;`
- L73 _public prototype_ `SyncChannelImpl& operator=(const SyncChannelImpl&) = delete;`
- L74 _public prototype_ `virtual ~SyncChannelImpl();`
- L76 _public prototype_ `bool CanInitialize() const;`
- L77 _public prototype_ `bool Thread_Initialize(DeviceConnection::CommandList& InCommandList);`
- L78 _public prototype_ `void Uninitialize();`
- L79 _public prototype_ `void Thread_Destroy(DeviceConnection::CommandList& InCommandList);`
- L81 _public prototype_ `bool WaitForSync();`
- L82 _public prototype_ `bool GetTimecode(FTimecode& OutTimecode);`
- L83 _public prototype_ `bool GetSyncCount(uint32_t& OutCount) const;`
- L84 _public prototype_ `bool GetVideoFormat(NTV2VideoFormat& OutVideoFormat);`
- L87 _private function_ `CNTV2Card& GetDevice()`
- L92 _private member_ `AJALock Lock;` — for callback
- L93 _private member_ `AJADeviceOptions DeviceOption;`
- L94 _private member_ `AJASyncChannelOptions SyncOption;`
- L96 _private member_ `std::shared_ptr<DeviceConnection> Device;`
- L99 _private member_ `NTV2Channel Channel;`
- L100 _private member_ `NTV2InputSource InputSource;`
- L101 _private member_ `NTV2VideoFormat DesiredVideoFormat;`
- L103 _private member_ `uint32_t BaseFrameIndex;`
- L105 _private member_ `bool bRegisterChannel;`
- L106 _private member_ `bool bRegisterReference;`
- L107 _private member_ `bool bHaveTimecodeIssue;`
- L108 _private member_ `FTimecode PreviousTimecode;`
- L109 _private member_ `ULWord PreviousVerticalInterruptCount;`
- L113 _private prototype_ `bool Thread_Configure(DeviceConnection::CommandList& InCommandList);`
- L114 _private prototype_ `void Thread_OnInitializationCompleted(bool bSucceed);`
- L117 _private member_ `volatile bool bStopRequested;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace AJA`
- L12 _namespace_ `namespace Private` (scope `AJA`)

### `Plugins/Media/AjaMedia/Source/Aja/Private/ThreadSafeQueue.h` (Private)


#### class `AJA::Private::ThreadSafeQueue`  
`template<class T> class ThreadSafeQueue`  
_L16-55_
- L19 _public function_ `void Push(const T& InValue)`
- L25 _public function_ `bool Pop(T& OutValue)`
- L37 _public function_ `void Erase(const T& InValue)`
- L47 _public function_ `size_t Size() const`
- L53 _private member_ `AJALock Lock;`
- L54 _private member_ `std::vector<T> List;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace AJA`
- L13 _namespace_ `namespace Private` (scope `AJA`)

### `Plugins/Media/AjaMedia/Source/Aja/Private/TimecodeChannel.h` (Private)


#### class `AJA::Private::TimecodeChannel`  
`class TimecodeChannel`  
_L23-39_
- desc: TimecodeChannel definition
- L26 _public prototype_ `TimecodeChannel() = default;`
- L27 _public prototype_ `TimecodeChannel(const TimecodeChannel&) = delete;`
- L28 _public prototype_ `TimecodeChannel& operator=(const TimecodeChannel&) = delete;`
- L30 _public prototype_ `bool Initialize(const AJADeviceOptions& InDevice, const AJATimecodeChannelOptions& InOptions);`
- L31 _public prototype_ `void Uninitialize();`
- L33 _public prototype_ `bool GetTimecode(FTimecode& OutTimecode);`
- L36 _private member_ `std::shared_ptr<TimecodeChannelImpl> TimecodeImplementation;`
- L37 _private member_ `std::shared_ptr<DeviceConnection> Device;`
- L38 _private member_ `std::weak_ptr<TimecodeChannelInitialize_DeviceCommand> InitializeCommand;`

#### struct `AJA::Private::TimecodeChannelInitialize_DeviceCommand`  
`struct TimecodeChannelInitialize_DeviceCommand : DeviceCommand`  
_L43-50_
- inherits: `DeviceCommand`
- desc: TimecodeChannelInitialize_DeviceCommand definition
- L45 _public prototype_ `TimecodeChannelInitialize_DeviceCommand(const std::shared_ptr<DeviceConnection>& InConnection, const std::weak_ptr<TimecodeChannelImpl>& InChannel);`
- L47 _public prototype_ `virtual void Execute(DeviceConnection::CommandList& InCommandList) override;`
- L49 _public member_ `std::weak_ptr<TimecodeChannelImpl> TimecodeImplementation;`

#### struct `AJA::Private::TimecodeChannelUninitialize_DeviceCommand`  
`struct TimecodeChannelUninitialize_DeviceCommand : DeviceCommand`  
_L54-61_
- inherits: `DeviceCommand`
- desc: TimecodeChannelUninitialize_DeviceCommand definition
- L56 _public prototype_ `TimecodeChannelUninitialize_DeviceCommand(const std::shared_ptr<DeviceConnection>& InConnection, const std::weak_ptr<TimecodeChannelImpl>& InChannel);`
- L58 _public prototype_ `virtual void Execute(DeviceConnection::CommandList& InCommandList) override;`
- L60 _public member_ `std::shared_ptr<TimecodeChannelImpl> TimecodeImplementation;`

#### class `AJA::Private::TimecodeChannelImpl`  
`class TimecodeChannelImpl`  
_L66-117_
- desc: TimecodeChannelImpl definition
- L69 _public prototype_ `TimecodeChannelImpl() = delete;`
- L70 _public prototype_ `TimecodeChannelImpl(const AJADeviceOptions& InDevice, const AJATimecodeChannelOptions& InOptions);`
- L71 _public prototype_ `TimecodeChannelImpl(const TimecodeChannelImpl&) = delete;`
- L72 _public prototype_ `TimecodeChannelImpl& operator=(const TimecodeChannelImpl&) = delete;`
- L73 _public prototype_ `virtual ~TimecodeChannelImpl();`
- L75 _public prototype_ `bool CanInitialize() const;`
- L76 _public prototype_ `bool Thread_Initialize(DeviceConnection::CommandList& InCommandList);`
- L77 _public prototype_ `void Uninitialize();`
- L78 _public prototype_ `void Thread_Destroy(DeviceConnection::CommandList& InCommandList);`
- L80 _public prototype_ `bool GetTimecode(FTimecode& OutTimecode);`
- L83 _private function_ `CNTV2Card& GetDevice()`
- L88 _private member_ `AJALock Lock;` — for callback
- L89 _private member_ `AJADeviceOptions DeviceOption;`
- L90 _private member_ `AJATimecodeChannelOptions TimecodeOption;`
- L92 _private member_ `std::shared_ptr<DeviceConnection> Device;`
- L95 _private member_ `NTV2Channel Channel;`
- L96 _private member_ `NTV2InputSource InputSource;`
- L97 _private member_ `NTV2VideoFormat DesiredVideoFormat;`
- L99 _private member_ `bool bRegisteredDedicatedLTC;`
- L100 _private member_ `bool bRegisteredReferenceLTC;`
- L101 _private member_ `bool bRegisteredChannel;`
- L102 _private member_ `bool bHaveTimecodeIssue;`
- L103 _private member_ `FTimecode PreviousTimecode;`
- L104 _private member_ `ULWord PreviousVerticalInterruptCount;`
- L108 _private prototype_ `bool Thread_Configure(DeviceConnection::CommandList& InCommandList);`
- L109 _private prototype_ `void Thread_OnInitializationCompleted(bool bSucceed);`
- L112 _private member_ `volatile bool bStopRequested;`
- L113 _private member_ `std::chrono::system_clock::time_point LastLogTime;`
- L114 _private member_ `std::chrono::duration<double> SecondsBetweenLogs = std::chrono::duration<double>(5.0);`
- L115 _private member_ `bool bLogTimecodeError = true;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace AJA`
- L14 _namespace_ `namespace Private` (scope `AJA`)

### `Plugins/Media/AjaMedia/Source/Aja/Private/VideoFormats.h` (Private)


#### class `AJA::Private::VideoFormatsScanner`  
`class VideoFormatsScanner`  
_L16-24_
- desc: VideoFormatsScanner definition
- L19 _public prototype_ `VideoFormatsScanner(int32_t InDeviceId);`
- L21 _public prototype_ `static AJAVideoFormats::VideoFormatDescriptor GetVideoFormat(FAJAVideoFormat InAjaVideoFormat);`
- L23 _public member_ `std::vector<AJAVideoFormats::VideoFormatDescriptor> FormatList;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace AJA`
- L12 _namespace_ `namespace Private` (scope `AJA`)

### `Plugins/Media/AjaMedia/Source/Aja/Public/AJALib.h` (Public)


#### enum `AJA::EPixelFormat`  
`enum struct EPixelFormat`  
_L36-42_
- desc: Pixel formats supported
- L38 _public enumerator_ `PF_8BIT_YCBCR` — As Input/Output
- L39 _public enumerator_ `PF_8BIT_ARGB` — As Input/Output
- L40 _public enumerator_ `PF_10BIT_RGB` — As Input/Output
- L41 _public enumerator_ `PF_10BIT_YCBCR` — As Input/Output

#### enum `AJA::ETransportType`  
`enum class ETransportType`  
_L46-55_
- desc: SDI transport type
- L48 _public enumerator_ `TT_SdiSingle`
- L49 _public enumerator_ `TT_SdiSingle4kTSI`
- L50 _public enumerator_ `TT_SdiDual`
- L51 _public enumerator_ `TT_SdiQuadSQ`
- L52 _public enumerator_ `TT_SdiQuadTSI`
- L53 _public enumerator_ `TT_Hdmi`
- L54 _public enumerator_ `TT_Hdmi4kTSI`

#### struct `AJA::FTimecode`  
`struct FTimecode`  
_L60-70_
- desc: Timecode
- L62 _public prototype_ `FTimecode();`
- L63 _public prototype_ `bool operator== (const FTimecode& Other) const;`
- L65 _public member_ `uint32_t Hours;`
- L66 _public member_ `uint32_t Minutes;`
- L67 _public member_ `uint32_t Seconds;`
- L68 _public member_ `uint32_t Frames;`
- L69 _public member_ `bool bDropFrame;`

#### enum `AJA::ETimecodeFormat`  
`enum struct ETimecodeFormat`  
_L72-77_
- L74 _public enumerator_ `TCF_None`
- L75 _public enumerator_ `TCF_LTC`
- L76 _public enumerator_ `TCF_VITC1`

#### class `AJA::AJADeviceScanner`  
`class AJADeviceScanner`  
_L92-141_
- desc: AJADeviceScanner definition
- L95 _public member_ `const static int32_t FormatedTextSize = 64;`
- L96 _public typedef_ `using FormatedTextType = TCHAR[FormatedTextSize];`
- L129 _public prototype_ `AJADeviceScanner();`
- L130 _public prototype_ `~AJADeviceScanner();`
- L132 _public prototype_ `AJADeviceScanner(const AJADeviceScanner&) = delete;`
- L133 _public prototype_ `AJADeviceScanner& operator=(const AJADeviceScanner&) = delete;`
- L135 _public prototype_ `int32_t GetNumDevices() const;`
- L136 _public prototype_ `bool GetDeviceTextId(int32_t InDeviceIndex, FormatedTextType& OutTextId) const;`
- L137 _public prototype_ `bool GetDeviceInfo(int32_t InDeviceIndex, DeviceInfo& OutDeviceInfo) const;`
- L140 _private member_ `Private::DeviceScanner* Scanner;`

#### struct `AJA::AJADeviceScanner::DeviceInfo`  
`struct DeviceInfo`  
_L98-127_
- L100 _public member_ `bool bIsSupported;`
- L102 _public member_ `bool bCanFrameStore1DoPlayback;`
- L103 _public member_ `bool bCanDoDualLink;`
- L104 _public member_ `bool bCanDo2K;`
- L105 _public member_ `bool bCanDo4K;`
- L106 _public member_ `bool bCanDo12GSdi;`
- L107 _public member_ `bool bCanDo12GRouting;`
- L108 _public member_ `bool bCanDoMultiFormat;`
- L109 _public member_ `bool bCanDoAlpha;`
- L110 _public member_ `bool bCanDo3GLevelConversion;`
- L111 _public member_ `bool bCanDoCustomAnc;`
- L112 _public member_ `bool bCanDoLtc;`
- L113 _public member_ `bool bCanDoLtcInRefPort;`
- L114 _public member_ `bool bCanDoTSI;`
- L115 _public member_ `bool bSupportPixelFormat8bitYCBCR;`
- L116 _public member_ `bool bSupportPixelFormat8bitARGB;`
- L117 _public member_ `bool bSupportPixelFormat10bitRGB;`
- L118 _public member_ `bool bSupportPixelFormat10bitYCBCR;`
- L120 _public member_ `uint32_t NumberOfLtcInput;`
- L121 _public member_ `uint32_t NumberOfLtcOutput;`
- L123 _public member_ `int32_t NumSdiInput;`
- L124 _public member_ `int32_t NumSdiOutput;`
- L125 _public member_ `int32_t NumHdmiInput;`
- L126 _public member_ `int32_t NumHdmiOutput;`

#### struct `AJA::AJAVideoFormats`  
`struct AJAVideoFormats`  
_L145-184_
- desc: AJAVideoFormats definition
- L170 _public prototype_ `AJAVideoFormats(int32_t InDeviceId);`
- L171 _public prototype_ `~AJAVideoFormats();`
- L173 _public prototype_ `AJAVideoFormats(const AJAVideoFormats&) = delete;`
- L174 _public prototype_ `AJAVideoFormats& operator=(const AJAVideoFormats&) = delete;`
- L176 _public prototype_ `int32_t GetNumSupportedFormat() const;`
- L177 _public prototype_ `VideoFormatDescriptor GetSupportedFormat(int32_t InIndex) const;`
- L178 _public prototype_ `static VideoFormatDescriptor GetVideoFormat(FAJAVideoFormat InVideoFormatIndex);`
- L179 _public prototype_ `static std::string VideoFormatToString(FAJAVideoFormat InVideoFormatIndex);`
- L180 _public prototype_ `static bool VideoFormatToString(FAJAVideoFormat InVideoFormatIndex, char* OutCStr, uint32_t MaxLen);`
- L183 _private member_ `Private::VideoFormatsScanner* Formats;`

#### struct `AJA::AJAVideoFormats::VideoFormatDescriptor`  
`struct VideoFormatDescriptor`  
_L147-168_
- L149 _public prototype_ `VideoFormatDescriptor();`
- L151 _public member_ `FAJAVideoFormat VideoFormatIndex;`
- L152 _public member_ `uint32_t FrameRateNumerator;`
- L153 _public member_ `uint32_t FrameRateDenominator;`
- L154 _public member_ `uint32_t ResolutionWidth;`
- L155 _public member_ `uint32_t ResolutionHeight;`
- L156 _public member_ `bool bIsProgressiveStandard;`
- L157 _public member_ `bool bIsInterlacedStandard;`
- L158 _public member_ `bool bIsPsfStandard;`
- L159 _public member_ `bool bIsVideoFormatA;`
- L160 _public member_ `bool bIsVideoFormatB;`
- L161 _public member_ `bool bIs372DualLink;`
- L162 _public member_ `bool bIsSD;`
- L163 _public member_ `bool bIsHD;`
- L164 _public member_ `bool bIs2K;`
- L165 _public member_ `bool bIs4K;`
- L167 _public member_ `bool bIsValid;`

#### struct `AJA::AJADeviceOptions`  
`struct AJADeviceOptions`  
_L188-197_
- desc: AJADeviceOptions definition
- L190 _public function_ `AJADeviceOptions(uint32_t InChannelIndex) : DeviceIndex(InChannelIndex) , bWantMultiFormatMode(true)`
- L195 _public member_ `uint32_t DeviceIndex;`
- L196 _public member_ `bool bWantMultiFormatMode;`

#### struct `AJA::IAJASyncChannelCallbackInterface`  
`struct IAJASyncChannelCallbackInterface`  
_L201-207_
- desc: AJASyncChannel definition
- L203 _public prototype_ `IAJASyncChannelCallbackInterface();`
- L204 _public prototype_ `virtual ~IAJASyncChannelCallbackInterface();`
- L206 _public prototype_ `virtual void OnInitializationCompleted(bool bSucceed) = 0;`

#### struct `AJA::AJASyncChannelOptions`  
`struct AJASyncChannelOptions`  
_L209-223_
- L211 _public prototype_ `AJASyncChannelOptions(const TCHAR* DebugName);`
- L213 _public member_ `IAJASyncChannelCallbackInterface* CallbackInterface;`
- L215 _public member_ `ETransportType TransportType;`
- L216 _public member_ `uint32_t ChannelIndex;` — [1...x]
- L217 _public member_ `FAJAVideoFormat VideoFormatIndex;`
- L218 _public member_ `ETimecodeFormat TimecodeFormat;`
- L219 _public member_ `bool bOutput;` — port is output
- L220 _public member_ `bool bWaitForFrameToBeReady;` — port is input and we want to wait for the image to be sent to Unreal Engine before ticking
- L221 _public member_ `bool bAutoDetectFormat;`
- L222 _public member_ `bool bStopOnCardTimeout = true;` — Stop sync channel whenever we timeout while waiting for a vertical interrupt from the card (Default: true)

#### class `AJA::AJASyncChannel`  
`class AJASyncChannel`  
_L225-246_
- L228 _public prototype_ `AJASyncChannel(AJASyncChannel&) = delete;`
- L229 _public prototype_ `AJASyncChannel& operator=(AJASyncChannel&) = delete;`
- L231 _public prototype_ `AJASyncChannel();`
- L232 _public prototype_ `~AJASyncChannel();`
- L235 _public prototype_ `bool Initialize(const AJADeviceOptions& InDevice, const AJASyncChannelOptions& InOption);`
- L236 _public prototype_ `void Uninitialize();`
- L239 _public prototype_ `bool WaitForSync() const;` — Only available if the initialization succeeded
- L240 _public prototype_ `bool GetTimecode(FTimecode& OutTimecode) const;`
- L241 _public prototype_ `bool GetSyncCount(uint32_t& OutCount) const;`
- L242 _public prototype_ `bool GetVideoFormat(FAJAVideoFormat& OutVideoFormat);`
- L245 _private member_ `Private::SyncChannel* Channel;`

#### struct `AJA::IAJATimecodeChannelCallbackInterface`  
`struct IAJATimecodeChannelCallbackInterface`  
_L250-256_
- desc: AJATimecodeChannel definition
- L252 _public prototype_ `IAJATimecodeChannelCallbackInterface();`
- L253 _public prototype_ `virtual ~IAJATimecodeChannelCallbackInterface();`
- L255 _public prototype_ `virtual void OnInitializationCompleted(bool bSucceed) = 0;`

#### struct `AJA::AJATimecodeChannelOptions`  
`struct AJATimecodeChannelOptions`  
_L258-278_
- L260 _public prototype_ `AJATimecodeChannelOptions(const TCHAR* DebugName);`
- L262 _public member_ `IAJATimecodeChannelCallbackInterface* CallbackInterface;`
- L264 _public member_ `bool bUseDedicatedPin;`
- L267 _public member_ `bool bReadTimecodeFromReferenceIn;` — Timecode read from dedicated pin
- L268 _public member_ `uint32_t LTCSourceIndex;` — [1...x]
- L269 _public member_ `uint32_t LTCFrameRateNumerator;`
- L270 _public member_ `uint32_t LTCFrameRateDenominator;`
- L273 _public member_ `ETransportType TransportType;` — Timecode read from input channels
- L274 _public member_ `uint32_t ChannelIndex;` — [1...x]
- L275 _public member_ `FAJAVideoFormat VideoFormatIndex;`
- L276 _public member_ `ETimecodeFormat TimecodeFormat;`
- L277 _public member_ `bool bAutoDetectFormat;`

#### class `AJA::AJATimecodeChannel`  
`class AJATimecodeChannel`  
_L280-298_
- L283 _public prototype_ `AJATimecodeChannel(AJATimecodeChannel&) = delete;`
- L284 _public prototype_ `AJATimecodeChannel& operator=(AJATimecodeChannel&) = delete;`
- L286 _public prototype_ `AJATimecodeChannel();`
- L287 _public prototype_ `~AJATimecodeChannel();`
- L290 _public prototype_ `bool Initialize(const AJADeviceOptions& InDevice, const AJATimecodeChannelOptions& InOption);`
- L291 _public prototype_ `void Uninitialize();`
- L294 _public prototype_ `bool GetTimecode(FTimecode& OutTimecode) const;` — Only available if the initialization succeeded
- L297 _private member_ `Private::TimecodeChannel* Channel;`

#### enum `AJA::EAjaHDRMetadataEOTF`  
`enum class EAjaHDRMetadataEOTF : uint8`  
_L304-310_
- desc: HDR Transfer function.
- L306 _public enumerator_ `SDR`
- L307 _public enumerator_ `HLG`
- L308 _public enumerator_ `PQ`
- L309 _public enumerator_ `Unspecified`

#### enum `AJA::EAjaHDRMetadataGamut`  
`enum class EAjaHDRMetadataGamut : uint8`  
_L315-320_
- desc: HDR Color Gamut.
- L317 _public enumerator_ `Rec709`
- L318 _public enumerator_ `Rec2020`
- L319 _public enumerator_ `Invalid`

#### enum `AJA::EAjaHDRMetadataLuminance`  
`enum class EAjaHDRMetadataLuminance : uint8`  
_L325-329_
- desc: HDR Luminance.
- L327 _public enumerator_ `YCbCr`
- L328 _public enumerator_ `ICtCp`

#### struct `AJA::FAjaHDROptions`  
`struct FAjaHDROptions`  
_L334-344_
- desc: Set of metadata describing a HDR video signal.
- L337 _public member_ `EAjaHDRMetadataEOTF EOTF = EAjaHDRMetadataEOTF::SDR;` — Transfer function to use for converting the video signal to an optical signal.
- L340 _public member_ `EAjaHDRMetadataGamut Gamut = EAjaHDRMetadataGamut::Rec709;` — The color gamut of the video signal.
- L343 _public member_ `EAjaHDRMetadataLuminance Luminance = EAjaHDRMetadataLuminance::YCbCr;` — Color representation format of the video signal.

#### struct `AJA::AJAInputFrameData`  
`struct AJAInputFrameData`  
_L348-354_
- desc: AJAInputFrameData definition
- L350 _public prototype_ `AJAInputFrameData();`
- L352 _public member_ `FTimecode Timecode;`
- L353 _public member_ `uint32_t FramesDropped;` — frame dropped by the AJA

#### struct `AJA::AJAOutputFrameData`  
`struct AJAOutputFrameData : AJAInputFrameData`  
_L356-361_
- inherits: `AJAInputFrameData`
- L358 _public prototype_ `AJAOutputFrameData();`
- L360 _public member_ `uint32_t FramesLost;` — frame ready by the game but not sent to AJA

#### struct `AJA::AJAAncillaryFrameData`  
`struct AJAAncillaryFrameData`  
_L363-371_
- L365 _public prototype_ `AJAAncillaryFrameData();`
- L367 _public member_ `uint8_t* AncBuffer;`
- L368 _public member_ `uint32_t AncBufferSize;`
- L369 _public member_ `uint8_t* AncF2Buffer;`
- L370 _public member_ `uint32_t AncF2BufferSize;`

#### struct `AJA::AJAAudioFrameData`  
`struct AJAAudioFrameData`  
_L373-382_
- L375 _public prototype_ `AJAAudioFrameData();`
- L377 _public member_ `uint8_t* AudioBuffer;`
- L378 _public member_ `uint32_t AudioBufferSize;`
- L379 _public member_ `uint32_t NumChannels;`
- L380 _public member_ `uint32_t AudioRate;`
- L381 _public member_ `uint32_t NumSamples;`

#### struct `AJA::AJAVideoFrameData`  
`struct AJAVideoFrameData`  
_L384-396_
- L386 _public prototype_ `AJAVideoFrameData();`
- L387 _public member_ `FAJAVideoFormat VideoFormatIndex;`
- L388 _public member_ `uint8_t* VideoBuffer;`
- L389 _public member_ `uint32_t VideoBufferSize;`
- L390 _public member_ `uint32_t Stride;`
- L391 _public member_ `uint32_t Width;`
- L392 _public member_ `uint32_t Height;`
- L393 _public member_ `EPixelFormat PixelFormat;`
- L394 _public member_ `bool bIsProgressivePicture;`
- L395 _public member_ `FAjaHDROptions HDROptions;`

#### struct `AJA::AJARequestInputBufferData`  
`struct AJARequestInputBufferData`  
_L398-406_
- L400 _public prototype_ `AJARequestInputBufferData();`
- L401 _public member_ `bool bIsProgressivePicture;`
- L402 _public member_ `uint32_t AncBufferSize;`
- L403 _public member_ `uint32_t AncF2BufferSize;`
- L404 _public member_ `uint32_t AudioBufferSize;`
- L405 _public member_ `uint32_t VideoBufferSize;`

#### struct `AJA::AJARequestedInputBufferData`  
`struct AJARequestedInputBufferData`  
_L408-415_
- L410 _public prototype_ `AJARequestedInputBufferData();`
- L411 _public member_ `uint8_t* AncBuffer;`
- L412 _public member_ `uint8_t* AncF2Buffer;`
- L413 _public member_ `uint8_t* AudioBuffer;`
- L414 _public member_ `uint8_t* VideoBuffer;`

#### struct `AJA::IAJAInputOutputChannelCallbackInterface`  
`struct IAJAInputOutputChannelCallbackInterface : IAJASyncChannelCallbackInterface`  
_L417-427_
- inherits: `IAJASyncChannelCallbackInterface`
- L419 _public prototype_ `IAJAInputOutputChannelCallbackInterface();`
- L421 _public prototype_ `virtual bool OnRequestInputBuffer(const AJARequestInputBufferData& RequestBuffer, AJARequestedInputBufferData& OutRequestedBuffer) = 0;`
- L422 _public prototype_ `virtual bool OnInputFrameReceived(const AJAInputFrameData& InFrameData, const AJAAncillaryFrameData& InAncillaryFrame, const AJAAudioFrameData& InAudioFrame, const AJAVideoFrameData& InVideoFrame) = 0;`
- L423 _public function_ `virtual void OnOutputFrameStarted()`
- L424 _public prototype_ `virtual bool OnOutputFrameCopied(const AJAOutputFrameData& InFrameData) = 0;`
- L425 _public prototype_ `virtual void OnCompletion(bool bSucceed) = 0;`
- L426 _public function_ `virtual void OnFormatChange(FAJAVideoFormat VideoFormat)`

#### enum `AJA::EAJAReferenceType`  
`enum class EAJAReferenceType`  
_L431-436_
- desc: AJAInputOutputChannelOptions definition
- L433 _public enumerator_ `EAJA_REFERENCETYPE_EXTERNAL`
- L434 _public enumerator_ `EAJA_REFERENCETYPE_FREERUN`
- L435 _public enumerator_ `EAJA_REFERENCETYPE_INPUT`

#### struct `AJA::AJAInputOutputChannelOptions`  
`struct AJAInputOutputChannelOptions`  
_L438-481_
- L440 _public prototype_ `AJAInputOutputChannelOptions(const TCHAR* DebugName, uint32_t InChannelIndex);`
- L442 _public member_ `IAJAInputOutputChannelCallbackInterface* CallbackInterface;`
- L444 _public member_ `uint32_t NumberOfAudioChannel;`
- L445 _public member_ `ETransportType TransportType;`
- L446 _public member_ `uint32_t ChannelIndex;` — [1...x]
- L447 _public member_ `uint32_t SynchronizeChannelIndex;` — [1...x]
- L448 _public member_ `uint32_t KeyChannelIndex;` — [1...x] for output
- L449 _public member_ `uint32_t OutputNumberOfBuffers;` — [1...x] supported but not suggested (min of 2 is suggested)
- L450 _public member_ `FAJAVideoFormat VideoFormatIndex;`
- L451 _public member_ `EPixelFormat PixelFormat;`
- L452 _public member_ `FAjaHDROptions HDROptions;`
- L453 _public member_ `ETimecodeFormat TimecodeFormat;`
- L454 _public member_ `EAJAReferenceType OutputReferenceType;`
- L455 _public member_ `uint32_t BurnTimecodePercentY;`

#### union `AJA::AJAInputOutputChannelOptions::(anonymous)`  
``  
_L458-480_

#### struct `AJA::AJAInputOutputChannelOptions::__anon9ee41833010a::(anonymous)`  
``  
_L460-478_

#### class `AJA::AJAInputChannel`  
`class AJAInputChannel`  
_L485-505_
- desc: AJAInputChannel definition
- L488 _public prototype_ `AJAInputChannel(AJAInputChannel&) = delete;`
- L489 _public prototype_ `AJAInputChannel& operator=(AJAInputChannel&) = delete;`
- L491 _public prototype_ `AJAInputChannel();`
- L492 _public prototype_ `virtual ~AJAInputChannel();`
- L495 _public prototype_ `bool Initialize(const AJADeviceOptions& InDevice, const AJAInputOutputChannelOptions& Options);`
- L496 _public prototype_ `void Uninitialize();`
- L499 _public prototype_ `uint32_t GetFrameDropCount() const;` — Only available if the initialization succeeded
- L500 _public prototype_ `const AJAInputOutputChannelOptions& GetOptions() const;`
- L501 _public prototype_ `const AJADeviceOptions& GetDeviceOptions() const;`
- L504 _private member_ `Private::InputChannel* Channel;`

#### struct `AJA::AJAOutputFrameBufferData`  
`struct AJAOutputFrameBufferData`  
_L509-518_
- desc: AJAOutputFrameBufferData definition
- L511 _public prototype_ `AJAOutputFrameBufferData();`
- L513 _public member_ `static const uint32_t InvalidFrameIdentifier;`
- L515 _public member_ `FTimecode Timecode;`
- L516 _public member_ `uint32_t FrameIdentifier;`
- L517 _public member_ `bool bEvenFrame;`

#### class `AJA::AJAOutputChannel`  
`class AJAOutputChannel`  
_L522-555_
- desc: AJAOutputChannel definition
- L525 _public prototype_ `AJAOutputChannel(AJAOutputChannel&) = delete;`
- L526 _public prototype_ `AJAOutputChannel& operator=(AJAOutputChannel&) = delete;`
- L528 _public prototype_ `AJAOutputChannel();`
- L529 _public prototype_ `virtual ~AJAOutputChannel();`
- L532 _public prototype_ `bool Initialize(const AJADeviceOptions& InDevice, const AJAInputOutputChannelOptions& Options);`
- L538 _public prototype_ `void Uninitialize(TPromise<void> Promise = {});` — Clean up card connections for this channel. (Asynchronous) @param Promise Used to inform when the uninitialization is complete.
- L541 _public prototype_ `bool SetAncillaryFrameData(const AJAOutputFrameBufferData& InFrameData, uint8_t* AncillaryBuffer, uint32_t AncillaryBufferSize);` — Set a new buffer that will be copied to the AJA.
- L542 _public prototype_ `bool SetAudioFrameData(const AJAOutputFrameBufferData& InFrameData, uint8_t* AudioBuffer, uint32_t AudioBufferSize);`
- L543 _public prototype_ `bool SetVideoFrameData(const AJAOutputFrameBufferData& InFrameData, uint8_t* VideoBuffer, uint32_t VideoBufferSize);`
- L544 _public prototype_ `bool SetVideoFrameData(const AJAOutputFrameBufferData& InFrameData, FRHITexture* RHITexture);`
- L545 _public prototype_ `bool DMAWriteAudio(const uint8* Buffer, int32 BufferSize);`
- L548 _public prototype_ `bool ShouldCaptureThisFrame(::FTimecode Timecode, uint32 SourceFrameNumber);` — Return whether to capture or discard a frame based on its timecode and frame number.
- L550 _public prototype_ `bool GetOutputDimension(uint32_t& OutWidth, uint32_t& OutHeight) const;`
- L551 _public prototype_ `int32_t GetNumAudioSamplesPerFrame(const AJAOutputFrameBufferData& InFrameData) const;`
- L554 _private member_ `Private::OutputChannel* Channel;`

#### struct `AJA::IAJAAutoDetectCallbackInterface`  
`struct IAJAAutoDetectCallbackInterface`  
_L560-566_
- desc: AJAAutoDetectChannelCallbackInterface definition
- L562 _public prototype_ `IAJAAutoDetectCallbackInterface();`
- L563 _public prototype_ `virtual ~IAJAAutoDetectCallbackInterface();`
- L565 _public prototype_ `virtual void OnCompletion(bool bSucceed) = 0;`

#### class `AJA::AJAAutoDetectChannel`  
`class AJAAutoDetectChannel`  
_L570-599_
- desc: AJAAutoDetectChannel definition
- L584 _public prototype_ `AJAAutoDetectChannel(AJAAutoDetectChannel&) = delete;`
- L585 _public prototype_ `AJAAutoDetectChannel& operator=(AJAAutoDetectChannel&) = delete;`
- L587 _public prototype_ `AJAAutoDetectChannel();`
- L588 _public prototype_ `virtual ~AJAAutoDetectChannel();`
- L591 _public prototype_ `bool Initialize(IAJAAutoDetectCallbackInterface* InCallbackInterface);`
- L592 _public prototype_ `void Uninitialize();`
- L594 _public prototype_ `int32_t GetNumOfChannelData() const;`
- L595 _public prototype_ `AutoDetectChannelData GetChannelData(int32_t Index) const;`
- L598 _private member_ `Private::AutoDetectChannel* AutoChannel;`

#### struct `AJA::AJAAutoDetectChannel::AutoDetectChannelData`  
`struct AutoDetectChannelData`  
_L573-581_
- L575 _public prototype_ `AutoDetectChannelData();`
- L577 _public member_ `FAJAVideoFormat DetectedVideoFormat;`
- L578 _public member_ `uint32_t DeviceIndex;` — [0...x]
- L579 _public member_ `uint32_t ChannelIndex;` — [1...x]
- L580 _public member_ `ETimecodeFormat TimecodeFormat;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace GPUTextureTransfer` (scope `UE`)
- L21 _namespace_ `namespace AJA`
- L25 _typedef_ `typedef void* FDeviceScanner;` (scope `AJA`) — Types provided from the interface
- L26 _typedef_ `typedef void* FDeviceInfo;` (scope `AJA`)
- L27 _typedef_ `typedef void* FAJADevice;` (scope `AJA`)
- L28 _typedef_ `typedef uint32_t FAJAVideoFormat;` (scope `AJA`)
- L32 _typedef_ `using LoggingCallbackPtr = void(*)(const TCHAR* Format, ...);` (scope `AJA`) — Logging Callbacks
- L79 _namespace_ `namespace Private` (scope `AJA`)
- L461 _member_ `uint32_t bUseAutoCirculating : 1;` (scope `AJA::AJAInputOutputChannelOptions::__anon9ee41833010a::__anon9ee418330208`)
- L462 _member_ `uint32_t bOutput : 1;` (scope `AJA::AJAInputOutputChannelOptions::__anon9ee41833010a::__anon9ee418330208`) — port is output
- L463 _member_ `uint32_t bUseKey : 1;` (scope `AJA::AJAInputOutputChannelOptions::__anon9ee41833010a::__anon9ee418330208`) — output will also sent the key on OutputKeyPortIndex
- L464 _member_ `uint32_t bOutputInterlacedFieldsTimecodeNeedToMatch : 1;` (scope `AJA::AJAInputOutputChannelOptions::__anon9ee41833010a::__anon9ee418330208`) — when trying to find the odd field that correspond to the even field, the 2 timecode need to match
- L465 _member_ `uint32_t bOutputInterlaceAsProgressive : 1;` (scope `AJA::AJAInputOutputChannelOptions::__anon9ee41833010a::__anon9ee418330208`) — whether to treat outgoing interlace frames as progressive.
- L466 _member_ `uint32_t bOutputInterlaceOnEvenFrames : 1;` (scope `AJA::AJAInputOutputChannelOptions::__anon9ee41833010a::__anon9ee418330208`) — whether to force output interlace on even timecode frames.
- L467 _member_ `uint32_t bUseAncillary : 1;` (scope `AJA::AJAInputOutputChannelOptions::__anon9ee41833010a::__anon9ee418330208`) — enable ANC system
- L468 _member_ `uint32_t bUseAudio : 1;` (scope `AJA::AJAInputOutputChannelOptions::__anon9ee41833010a::__anon9ee418330208`) — enable audio input/output
- L469 _member_ `uint32_t bUseVideo : 1;` (scope `AJA::AJAInputOutputChannelOptions::__anon9ee41833010a::__anon9ee418330208`) — enable video input/output
- L470 _member_ `uint32_t bBurnTimecode : 1;` (scope `AJA::AJAInputOutputChannelOptions::__anon9ee41833010a::__anon9ee418330208`) — burn the timecode to the input or output image
- L471 _member_ `uint32_t bDisplayWarningIfDropFrames : 1;` (scope `AJA::AJAInputOutputChannelOptions::__anon9ee41833010a::__anon9ee418330208`)
- L472 _member_ `uint32_t bConvertOutputLevelAToB : 1;` (scope `AJA::AJAInputOutputChannelOptions::__anon9ee41833010a::__anon9ee418330208`) — enable video output 3G level A to convert it to 3G level B
- L473 _member_ `uint32_t bTEST_OutputInterlaced : 1;` (scope `AJA::AJAInputOutputChannelOptions::__anon9ee41833010a::__anon9ee418330208`) — when outputting, warn if the field 1 and field 2 are the same color. It except one of the line to be white and the other line to be not white
- L474 _member_ `uint32_t bUseGPUDMA : 1;` (scope `AJA::AJAInputOutputChannelOptions::__anon9ee41833010a::__anon9ee418330208`) — Whether to use GPU Direct when outputting.
- L475 _member_ `uint32_t bAutoDetectFormat : 1;` (scope `AJA::AJAInputOutputChannelOptions::__anon9ee41833010a::__anon9ee418330208`) — Whether to autodetect format on input.
- L476 _member_ `uint32_t bDirectlyWriteAudio : 1;` (scope `AJA::AJAInputOutputChannelOptions::__anon9ee41833010a::__anon9ee418330208`) — Experimental mode to set audio from the audio thread directly.
- L477 _member_ `uint32_t bStopOnTimeout : 1;` (scope `AJA::AJAInputOutputChannelOptions::__anon9ee41833010a::__anon9ee418330208`) — Stop input/output whenever we timeout while waiting for a vertical interrupt from the card.
- L479 _member_ `uint32_t Options;` (scope `AJA::AJAInputOutputChannelOptions::__anon9ee41833010a`)

### `Plugins/Media/AjaMedia/Source/Aja/Public/AjaCoreModule.h` (Public)


#### class `FAjaCoreModule`  
`class FAjaCoreModule : public IModuleInterface`  
_L10-12_
- inherits: `IModuleInterface`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAjaCore, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAjaCore, Log, All);`
