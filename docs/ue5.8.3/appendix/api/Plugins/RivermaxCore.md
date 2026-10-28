# Plugins / RivermaxCore

- module root: `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxCore`
- headers: 28; symbols: 1243
- symbol kinds: class=33, delegate=7, enum=9, enumerator=43, function=49, macro=4, member=531, namespace=73, prototype=308, struct=45, typedef=135, union=1, variable=5
- PrivateDependencyModuleNames: D3D12RHI, Engine, Json, Networking, RenderCore, Slate, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, DeveloperSettings, MediaAssets, RHI, RivermaxLib, TimeManagement

### `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxCore/Private/RTPHeader.h` (Private)


#### struct `UE::RivermaxCore::Private::FRawRTPHeader`  
`struct FRawRTPHeader`  
_L47-62_
- desc: Total size should be 14 octets.
- L49 _public member_ `uint8 ContributingSourceCount : 4;`
- L50 _public member_ `uint8 ExtensionBit : 1;`
- L51 _public member_ `uint8 PaddingBit : 1;`
- L52 _public member_ `uint8 Version : 2;`
- L53 _public member_ `uint8 PayloadType : 7;`
- L54 _public member_ `uint8 MarkerBit : 1;`
- L55 _public member_ `uint16 SequenceNumber : 16;`
- L56 _public member_ `uint32 Timestamp : 32;`
- L57 _public member_ `uint32 SynchronizationSource : 32;`
- L58 _public member_ `uint16 ExtendedSequenceNumber : 16;`
- L61 _public member_ `static constexpr uint32 VideoSynchronizationSource = 0x0eb51dbf;` — The base value is 0x0eb51dbf which will be used for video. Anc is VideoSyncSource + 1.

#### struct `UE::RivermaxCore::Private::FRawSRD`  
`struct FRawSRD`  
_L75-103_
- desc: SRD Header. Total packed size should be 6 octets. 0                   1                   2                   3 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ |           SRD Length          |F|     SRD Row Number          | +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ |C|         SRD Offset          | +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
- L77 _public member_ `uint16 Length : 16;`
- L79 _public member_ `uint8 RowNumberHigh : 7;`
- L81 _public member_ `uint8 FieldIdentification : 1;`
- L83 _public member_ `uint8 RowNumberLow : 8;`
- L85 _public member_ `uint8 OffsetHigh : 7;`
- L88 _public member_ `uint8 ContinuationBit : 1;` — If set indicates that there is another SRD following this one.
- L89 _public member_ `uint8 OffsetLow : 8;`
- L93 _public prototype_ `uint16 GetRowNumber() const;` — Returns SRD associated row number
- L96 _public prototype_ `void SetRowNumber(uint16 RowNumber);` — Sets SRD associated row number
- L99 _public prototype_ `uint16 GetOffset() const;` — Returns SRD pixel offset in its associated row
- L102 _public prototype_ `void SetOffset(uint16 Offset);` — Sets SRD pixel offset in its associated row

#### struct `UE::RivermaxCore::Private::FVideoRTPHeader`  
`struct FVideoRTPHeader`  
_L106-117_
- desc: Total size should be 26 octets.
- L108 _public member_ `FRawRTPHeader RTPHeader;`
- L110 _public member_ `FRawSRD SRD1;` — 48
- L112 _public member_ `FRawSRD SRD2;` — 48
- L115 _public member_ `static constexpr uint32 OneSRDSize = 20;` — Size of RTP representation whether it has one or two SRDs
- L116 _public member_ `static constexpr uint32 TwoSRDSize = 26;`

#### struct `UE::RivermaxCore::Private::FSRDHeader`  
`struct FSRDHeader`  
_L123-139_
- L126 _public member_ `uint16 Length = 0;` — Length of payload. Is a multiple of pgroup (see pixel formats)
- L129 _public member_ `bool bIsFieldOne = false;` — False if progressive or first field of interlace. True if second field of interlace
- L132 _public member_ `uint16 RowNumber = 0;` — Video line number, starts at 0
- L135 _public member_ `bool bHasContinuation = false;` — Whether another SRD is following this one
- L138 _public member_ `uint16 DataOffset = 0;` — Location of the first pixel in payload, in pixel

#### struct `UE::RivermaxCore::Private::FRTPHeader`  
`struct FRTPHeader`  
_L142-177_
- desc: RTP header built from network representation not requiring any byte swapping
- L144 _public prototype_ `FRTPHeader() = default;`
- L145 _public prototype_ `FRTPHeader(const FVideoRTPHeader& VideoRTP);`
- L148 _public prototype_ `uint16 GetTotalPayloadSize() const;` — Returns the total payload of this RTP
- L151 _public prototype_ `uint16 GetLastPayloadSize() const;` — Returns the payload size of the last SRD in this RTP
- L154 _public prototype_ `uint16 GetLastRowOffset() const;` — Returns the row offset of the last SRD in this RTP
- L157 _public prototype_ `uint16 GetLastRowNumber() const;` — Returns the row number of the last SRD in this RTP
- L160 _public member_ `uint32 SequenceNumber = 0;` — Sequence number including extension if present
- L163 _public member_ `uint32 Timestamp = 0;` — Timestamp of frame in the specified clock resolution. Video is typically 90kHz
- L166 _public member_ `uint32 SyncSouceId = 0;` — Identification of this stream
- L169 _public member_ `bool bHasExtension = false;` — Whether extensions (SRD headers) are present
- L172 _public member_ `bool bIsMarkerBit = false;` — True if RTP packet is last of video stream
- L175 _public member_ `FSRDHeader SRD1;` — Only supports 2 SRD for now. Adjust if needed
- L176 _public member_ `FSRDHeader SRD2;`

#### class `UE::RivermaxCore::Private::FBigEndianHeaderPacker`  
`class FBigEndianHeaderPacker`  
_L192-457_
- desc: A class that helps with packet creation and endianness conversion. The main purpose of this is to first pack bits, second is to handle endianness.
- L196 _private member_ `TArrayView<uint8> Data;` — All bytes containing fields in big endian ready for network.
- L199 _private member_ `int32 CurrentByte;` — Counting elements in the array.
- L202 _private member_ `int32 RemainingBitsInCurrentByte = 0;` — Bits used in the current byte.
- L205 _private member_ `bool bFinalized = false;` — Once packet is finalized certain actions are no longer possible.
- L224 _public member_ `TArray<FFieldInfo> Fields;`
- L233 _private member_ `TArray<TArray<FFieldInfo>> FieldsInOrder;` — Used only in debug mode. These are processed field bits as they appear in the packet. Can be accessed to output into an external file or general debugging.
- L242 _public function_ `FBigEndianHeaderPacker(uint8* BufferToFill, int32 MaxSize, bool bClearExisting = true) : Data(BufferToFill, MaxSize) , CurrentByte(0)` — Users responsible for specifying a vaild memory address for data to be packed into with enough memory. If existing data must be cleared bClearExisting must be set to true.
- L266 _public function_ `FORCEINLINE void AddField(uint32 InFieldData, int32 InNumBits, const FString& DebugString)`
- L275 _public function_ `FORCEINLINE void AddField(uint32 InFieldData, int32 InNumBits)`
- L285 _public function_ `FORCEINLINE void UpdateField(uint32 InFieldData, int32 InNumBits, int32 FieldPositionInBits, const FString& DebugString) #else FORCEINLINE void UpdateField(uint32 InFieldData, int32 InNumBits, int32 FieldPositionInBits) #endif`
- L313 _public function_ `FORCEINLINE void WordAlign(const int32 InWorldAlign)` — WordAlign - the word size in bytes to be aligned to. For example Anc packets need to be aligned to the nearest 32 bit word
- L336 _public function_ `FORCEINLINE void Finalize()` — Cleanup and pad the memory if it is necessary. If packet debugging is enabled, convert it into proper packet.
- L359 _public function_ `FORCEINLINE int32 CountFieldBits()`
- L374 _public function_ `FORCEINLINE int64 CountBytes()` — Size in bytes.
- L381 _public function_ `const TArray<TArray<FFieldInfo>>& GetFieldsInOrderByRef()`
- L391 _private function_ `void AddFieldInternal(uint32 InFieldData, int32 InNumBits, bool bClear, const FString& DebugString) #else FORCEINLINE void AddFieldInternal(uint32 InFieldData, int32 InNumBits, bool bClear) #endif`

#### struct `UE::RivermaxCore::Private::FBigEndianHeaderPacker::FFieldInfo`  
`struct FFieldInfo`  
_L213-222_
- desc: Debug struct that is used for storing field information.
- L220 _public member_ `int32 NumBits;`
- L221 _public member_ `FString FieldName;`

#### union `UE::RivermaxCore::Private::FBigEndianHeaderPacker::FFieldInfo::(anonymous)`  
``  
_L216-219_

#### class `UE::RivermaxCore::Private::FBigEndianHeaderUnpacker`  
`class FBigEndianHeaderUnpacker`  
_L462-519_
- desc: Counterpart to FBigEndianHeaderPacker. Reads fields from a big-endian Most significant byte first packed
- L465 _public function_ `FBigEndianHeaderUnpacker(const uint8* InBuffer, int32 InMaxSize) : Data(InBuffer, InMaxSize)`
- L471 _public function_ `FORCEINLINE uint32 GetNextField(int32 InNumBits)`
- L487 _public function_ `FORCEINLINE void SkipBits(int32 InNumBits)` — Skip InNumBits without reading.
- L496 _public function_ `FORCEINLINE void WordAlign(int32 InWordSizeByte)` — Advance to the next InWordSizeByte boundary.
- L508 _public function_ `FORCEINLINE bool CanRead(int32 InNumBits) const` — Returns true if at least InNumBits remain in the buffer.
- L514 _public function_ `FORCEINLINE int32 GetBitPosition() const` — Current bit cursor position.
- L517 _private member_ `TArrayView<const uint8> Data;`
- L518 _private member_ `int32 CurrentBit = 0;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define RIVERMAX_PACKET_DEBUG 1`
- L12 _macro_ `#define RIVERMAX_PACKET_DEBUG 0`
- L16 _macro_ `#define RIVERMAX_DEBUG_FIELD_NAME(...) , __VA_ARGS__`
- L18 _macro_ `#define RIVERMAX_DEBUG_FIELD_NAME(...)`
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace RivermaxCore` (scope `UE`)
- L22 _namespace_ `namespace Private` (scope `UE::RivermaxCore`)
- L185 _prototype_ `const uint8* GetRTPHeaderPointerVideo(const uint8* InHeader);` (scope `UE::RivermaxCore::Private`) — Returns RTPHeader pointer from a raw ethernet packet skipping 802, IP, UDP headers. This only works for IPv4 2110-20 video single SRD or Two-srd RTP packets. Will not work correctly for audio, ANC, or non-standard RTP packets. Assumes InHeader has at least 14 bytes; no bounds checking is performed.
- L217 _member_ `uint32 Data;` (scope `UE::RivermaxCore::Private::FBigEndianHeaderPacker::FFieldInfo::__anon8a98e20c010a`)
- L218 _member_ `int32 BitPosition;` (scope `UE::RivermaxCore::Private::FBigEndianHeaderPacker::FFieldInfo::__anon8a98e20c010a`)

### `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxCore/Private/RivermaxBoundaryMonitor.h` (Private)


#### class `UE::RivermaxCore::FBoundaryMonitor`  
`class FBoundaryMonitor : public FRunnable`  
_L17-40_
- inherits: `FRunnable`
- desc: Monitor running its own thread to add trace bookmarks at frame boundary for a given frame rate
- L20 _public prototype_ `FBoundaryMonitor(const FFrameRate& Rate);`
- L21 _public prototype_ `virtual ~FBoundaryMonitor();`
- L24 _public prototype_ `virtual uint32 Run() override;`
- L30 _protected member_ `TUniquePtr<FRunnableThread> WorkingThread;` — Thread responsible to watch for frame boundaries
- L33 _protected member_ `FFrameRate Rate;` — Frame rate at which we add markups
- L36 _protected member_ `TSharedPtr<IRivermaxManager> RivermaxManager;` — Cached pointer to rivermax manager
- L39 _protected member_ `std::atomic<bool> bIsEnabled = false;` — Whether thread should be running

#### class `UE::RivermaxCore::FRivermaxBoundaryMonitor`  
`class FRivermaxBoundaryMonitor : public IRivermaxBoundaryMonitor`  
_L46-76_
- inherits: `IRivermaxBoundaryMonitor`
- desc: Monitoring manager of frame boundary based on ST-2059 / PTP formulae Used to add trace bookmarks at each boundary for any frame rate monitored
- L49 _public prototype_ `virtual ~FRivermaxBoundaryMonitor();`
- L53 _public prototype_ `virtual void EnableMonitoring(bool bEnable) override;`
- L54 _public prototype_ `virtual FGuid StartMonitoring(const FFrameRate& FrameRate) override;`
- L55 _public prototype_ `virtual void StopMonitoring(const FGuid& Requester, const FFrameRate& FrameRate) override;`
- L61 _protected prototype_ `void StartMonitor(const FFrameRate& FrameRate);` — Starts monitoring a given frame rate
- L64 _protected prototype_ `void StopMonitor(const FFrameRate& FrameRate);` — Stops monitoring a given frame rate
- L69 _private member_ `bool bIsEnabled = false;` — Whether frame boundary monitor is enabled
- L72 _private member_ `TMap<FFrameRate, TUniquePtr<FBoundaryMonitor>> MonitorMap;` — Maps of monitor to a given frame rate
- L75 _private member_ `TMap<FFrameRate, TArray<FGuid>> ListenersMap;` — Maps from a given frame rate to listeners ID

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace RivermaxCore` (scope `UE`)

### `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxCore/Private/RivermaxCoreModule.h` (Private)


#### class `FRivermaxCoreModule`  
`class FRivermaxCoreModule : public IRivermaxCoreModule`  
_L15-43_
- inherits: `IRivermaxCoreModule`
- desc: Implementation of the IRivermaxCoreModule managing Rivermax library and stream creation
- L20 _public prototype_ `virtual void StartupModule() override;`
- L21 _public prototype_ `virtual void ShutdownModule() override;`
- L25 _public prototype_ `virtual TUniquePtr<UE::RivermaxCore::IRivermaxInputStream> CreateInputStream(UE::RivermaxCore::ERivermaxStreamType, const TArray<char>& InSDPDescription) override;`
- L26 _public prototype_ `virtual TUniquePtr<UE::RivermaxCore::IRivermaxOutputStream> CreateOutputStream(UE::RivermaxCore::ERivermaxStreamType, const TArray<char>& InSDPDescription) override;`
- L27 _public prototype_ `virtual TSharedPtr<UE::RivermaxCore::IRivermaxManager> GetRivermaxManager() override;`
- L28 _public prototype_ `virtual UE::RivermaxCore::IRivermaxBoundaryMonitor& GetRivermaxBoundaryMonitor() override;`
- L34 _private prototype_ `void OnRivermaxManagerInitialized();` — Called when manager has finished initializing
- L39 _private member_ `TSharedPtr<UE::RivermaxCore::IRivermaxManager> RivermaxManager;` — Manager handling library initialization
- L42 _private member_ `TUniquePtr<UE::RivermaxCore::IRivermaxBoundaryMonitor> BoundaryMonitor;` — Boundary monitor used to add trace information for frame boundaries at different frame rates

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace RivermaxCore` (scope `UE`)

### `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxCore/Private/RivermaxDeviceFinder.h` (Private)


#### class `UE::RivermaxCore::Private::FRivermaxDeviceFinder`  
`class FRivermaxDeviceFinder`  
_L13-72_
- L16 _public prototype_ `FRivermaxDeviceFinder();`
- L19 _public prototype_ `bool IsValidIP(const FString& SourceIP) const;` — Tests whether provided string is a valid IP, containing 4 numeric values or wildcard (*) separated by dots.
- L22 _public prototype_ `bool ResolveIP(const FString& SourceIP, FString& OutDeviceIP) const;` — Resolves IP to a found Rivermax device interface.
- L25 _public prototype_ `TConstArrayView<FRivermaxDeviceInfo> GetDevices() const;` — Returns list of found devices that can be used
- L30 _private prototype_ `void FindDevices();` — Find all interfaces available
- L65 _private member_ `mutable TMap<uint32, FQueriedIPInfo> QueriesCache;` — Cache of IPs that were queried to see which were valid / resolved
- L68 _private member_ `mutable TMap<uint32, FDeviceInfo> DevicesCache;` — Cache of found Rivermax devices with useful representation of its IP
- L71 _private member_ `TArray<FRivermaxDeviceInfo> Devices;` — List of found Rivermax devices

#### struct `UE::RivermaxCore::Private::FRivermaxDeviceFinder::FQueriedIPInfo`  
`struct FQueriedIPInfo`  
_L34-47_
- L37 _public member_ `bool bIsValidIP = false;` — Whether or not this IP was found as valid
- L40 _public member_ `FString SourceIP;` — String representation of the IP
- L43 _public member_ `TArray<FString> Tokens;` — String representation of IP component separated by '.'
- L46 _public member_ `TOptional<uint32> ResolvedDeviceIPHash;` — Hash of the matching found resolved device IP used to quickly find association

#### struct `UE::RivermaxCore::Private::FRivermaxDeviceFinder::FDeviceInfo`  
`struct FDeviceInfo`  
_L49-62_
- L52 _public member_ `FString DeviceIP;` — String representation of the IP
- L55 _public member_ `TArray<FString> Tokens;` — String representation of IP component separated by '.'
- L58 _public member_ `FIPv4Address Address;` — IPv4 representation of the IP with numerical tokens
- L61 _public member_ `uint8 AddressTokens[4];` — Array representation of IP in numerical tokens to iterate over

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace RivermaxCore` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::RivermaxCore`)

### `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxCore/Private/RivermaxFrameAllocator.h` (Private)


#### struct `UE::RivermaxCore::Private::FBaseDataCopySideCar`  
`struct FBaseDataCopySideCar`  
_L21-24_
- desc: Sidecar base struct given back to callback after data has been copied
- L23 _public prototype_ `virtual ~FBaseDataCopySideCar() = default;`

#### struct `UE::RivermaxCore::Private::FCopyArgs`  
`struct FCopyArgs`  
_L27-43_
- desc: Arguments describing memcopy operation required from allocator
- L30 _public member_ `FBufferRHIRef RHISourceMemory;` — RHI source memory that will be mapped to cuda
- L33 _public member_ `void* SourceMemory = nullptr;` — Source memory that doesn't need to be mapped since it's in the same space as destination
- L36 _public member_ `void* DestinationMemory = nullptr;` — Destination memory where data has to be copied
- L39 _public member_ `SIZE_T SizeToCopy = 0;` — Bytes needed to be copied
- L42 _public member_ `TSharedPtr<FBaseDataCopySideCar> SideCar;` — Sidecar to be re-provided on callback after memory has been copied

#### class `UE::RivermaxCore::Private::FBaseFrameAllocator`  
`class FBaseFrameAllocator`  
_L51-79_
- desc: Base class for frame allocation. Currently supports GPU allocation using CUDA and System memory
- L54 _public prototype_ `FBaseFrameAllocator(int32 InDesiredFrameSize, FOnFrameDataCopiedDelegate InOnDataCopiedDelegate);`
- L55 _public prototype_ `virtual ~FBaseFrameAllocator() = default;`
- L61 _public prototype_ `virtual bool Allocate(int32 FrameCount, bool bAlignFrameMemory) = 0;` — Allocates memory to hold FrameCount frames. If bAlignFrameMemory is true, aligns each frame memory size to allocator alignment If not, aligns entire memory block instead
- L64 _public prototype_ `virtual void Deallocate() = 0;` — Deallocate memory
- L67 _public prototype_ `virtual bool CopyData(const FCopyArgs& Args) = 0;` — Initiate a copy into a given frame using Args description of the operation
- L70 _public prototype_ `virtual void* GetFrameAddress(int32 FrameIndex) const = 0;` — Returns buffer address of a given frame
- L75 _protected member_ `int32 DesiredFrameSize = 0;` — Total desired size of a frame
- L78 _protected member_ `FOnFrameDataCopiedDelegate OnDataCopiedDelegate;` — Delegate callbacked when data has been copied. Depending on allocator, memcopy can be async.

#### class `UE::RivermaxCore::Private::FGPUAllocator`  
`class FGPUAllocator : public FBaseFrameAllocator`  
_L82-124_
- inherits: `FBaseFrameAllocator`
- L84 _private typedef_ `using Super = FBaseFrameAllocator;`
- L87 _public prototype_ `FGPUAllocator(int32 InDesiredFrameSize, FOnFrameDataCopiedDelegate InOnDataCopiedDelegate);`
- L90 _public prototype_ `virtual bool Allocate(int32 FrameCount, bool bAlignFrameMemory) override;`
- L91 _public prototype_ `virtual void Deallocate() override;`
- L92 _public prototype_ `virtual bool CopyData(const FCopyArgs& Args) override;`
- L93 _public prototype_ `virtual void* GetFrameAddress(int32 FrameIndex) const override;`
- L100 _private prototype_ `void* GetMappedAddress(const FBufferRHIRef& InBuffer);` — Get mapped address in cuda space for a given buffer. Cache will be updated if not found
- L105 _private member_ `int32 AllocatedFrameCount = 0;` — Number of frames that was allocated
- L108 _private member_ `size_t AllocatedFrameSize = 0;` — Allocated size of a frame
- L111 _private member_ `void* CudaAllocatedMemoryBaseAddress = nullptr;` — Allocated memory base address used when it's time to free
- L114 _private member_ `int32 CudaAllocatedMemory = 0;` — Total allocated gpu memory.
- L117 _private member_ `void* GPUStream = nullptr;` — Cuda stream used for our operations
- L120 _private member_ `TMap<FBufferRHIRef, void*> BufferCudaMemoryMap;` — Map between buffer we are sending and their mapped address in gpu space
- L123 _private member_ `TSpscQueue<TSharedPtr<FBaseDataCopySideCar>> PendingCopies;` — Sidecar for data copied callback that are waiting for a cuda memcopy. Will be dequeued when our cuda task has completed

#### class `UE::RivermaxCore::Private::FSystemAllocator`  
`class FSystemAllocator : public FBaseFrameAllocator`  
_L127-160_
- inherits: `FBaseFrameAllocator`
- L129 _private typedef_ `using Super = FBaseFrameAllocator;`
- L132 _public prototype_ `FSystemAllocator(int32 InDesiredFrameSize, FOnFrameDataCopiedDelegate InOnDataCopiedDelegate);`
- L135 _public prototype_ `virtual bool Allocate(int32 FrameCount, bool bAlignFrameMemory) override;`
- L136 _public prototype_ `virtual void Deallocate() override;`
- L137 _public prototype_ `virtual bool CopyData(const FCopyArgs& Args) override;`
- L138 _public prototype_ `virtual void* GetFrameAddress(int32 FrameIndex) const override;`
- L144 _private member_ `int32 AllocatedFrameCount = 0;` — Number of frames that was allocated
- L147 _private member_ `size_t AllocatedFrameSize = 0;` — Size of a frame that was allocated
- L150 _private member_ `size_t SystemAllocatedMemory = 0;` — Total memory allocated to hold all frames
- L153 _private member_ `void* SystemMemoryBaseAddress = nullptr;` — Allocated memory base address used when it's time to free
- L156 _private member_ `bool bUseParallelFor = false;` — Cached value for cvar controlling whether parallelfor is used to memcopy
- L159 _private member_ `int32 ParallelForThreadCount = 4;` — Cached value for cvar controlling number of threads to use when doing parallelfor memcopy

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace RivermaxCore` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace RivermaxCore` (scope `UE`)
- L18 _namespace_ `namespace Private` (scope `UE::RivermaxCore`)
- L48 _delegate_ `DECLARE_DELEGATE_OneParam(FOnFrameDataCopiedDelegate, const TSharedPtr<FBaseDataCopySideCar>&);` — Delegate triggered when data has been copied into a given frame
- L48 _prototype_ `DECLARE_DELEGATE_OneParam(FOnFrameDataCopiedDelegate, const TSharedPtr<FBaseDataCopySideCar>&);` (scope `UE::RivermaxCore::Private`) — Delegate triggered when data has been copied into a given frame

### `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxCore/Private/RivermaxFrameManager.h` (Private)


#### enum `UE::RivermaxCore::Private::EFrameMemoryLocation`  
`enum class EFrameMemoryLocation : uint8`  
_L25-35_
- desc: Where frame memory is allocated
- L28 _public enumerator_ `None` — No memory was allocated
- L31 _public enumerator_ `System` — Memory allocated in system memory
- L34 _public enumerator_ `GPU` — Memory allocated on GPU. Cuda space is used at the moment.

#### struct `UE::RivermaxCore::Private::FFrameManagerSetupArgs`  
`struct FFrameManagerSetupArgs`  
_L43-74_
- desc: Holds arguments to configure frame manager during initialization
- L46 _public member_ `FIntPoint Resolution = FIntPoint::ZeroValue;` — Resolution of video frames to allocate
- L49 _public member_ `uint32 Stride = 0;` — Stride of a line of video frame
- L52 _public member_ `uint32 FrameDesiredSize = 0;` — Desired size for a frame. Can be greater than what is needed to align with Rivermax's chunks
- L55 _public member_ `bool bAlignEachFrameAlloc = false;` — Whether allocator will align each frame to desired alignment or the entire block
- L58 _public member_ `uint8 NumberOfFrames = 0;` — Number of video frames required
- L61 _public member_ `bool bTryGPUAllocation = true;` — Whether we should try allocating on GPU
- L64 _public member_ `FOnFreeFrameDelegate OnFreeFrameDelegate;` — Delegate called when a frame is now free to use
- L67 _public member_ `FOnPreFrameReadyDelegate OnPreFrameReadyDelegate;` — Delegate triggered just before a frame is enqueued to be sent
- L70 _public member_ `FOnFrameReadyDelegate OnFrameReadyDelegate;` — Delegate called when a frame is now ready to be sent
- L73 _public member_ `FOnCriticalErrorDelegate OnCriticalErrorDelegate;` — Delegate called when a critical has happened and stream should shut down

#### class `UE::RivermaxCore::Private::FRivermaxOutputFramePool`  
`class FRivermaxOutputFramePool : public TMediaObjectPool<FRivermaxOutputFrame>`  
_L81-81_
- inherits: `TMediaObjectPool<FRivermaxOutputFrame>`
- desc: Media object pool responsible for managing shared pointers. Pointers allocated by this class are returned to the pending pool where it is checked via IsReadyToBeUsed if it is ready to be used again. It reduces manual thread/frame management required.

#### class `UE::RivermaxCore::Private::FFrameManager`  
`class FFrameManager`  
_L104-177_
- desc: Class managing frames that we output over network Handles memory allocation and state tracking States of a frame Free :	Frame can be used by the capture system. Pending:	Frame is being used by the capture system. Data isn't ready to be sent out yet but it's reserved for a given identifier. Ready:	Frame is ready to be sent. Data has been copied into it. Sending: Frame is being actively sent out the wire. Can't modify it until next frame boundary Frame rate control Sending a frame out takes a full frame interval so if capture system goes faster than output rate Free frames list will get depleted. If frame locking mode is used, getting the next free frame will block until a new one is available which will happen at next frame boundary Rendering and capturing the next frame might be quick but when ready to present it, it will get stalled. This will cause the engine's frame rate to match the output frame rate.
- L107 _public prototype_ `virtual ~FFrameManager();`
- L110 _public prototype_ `EFrameMemoryLocation Initialize(const FFrameManagerSetupArgs& Args);` — Initializes frame manager with a set of options. Returns where frames were allocated.
- L113 _public prototype_ `void Cleanup();` — Requests cleanup of allocated memory
- L116 _public prototype_ `TSharedPtr<FRivermaxOutputFrame> GetFreeFrame();` — Returns a frame not being used
- L119 _public prototype_ `TSharedPtr<FRivermaxOutputFrame> DequeueFrameToSend();` — Returns next frame ready to be sent. Can be null.
- L122 _public prototype_ `void EnqueFrameToSend(const TSharedPtr<FRivermaxOutputFrame>& Frame);` — Mark a frame as being ready to be sent
- L125 _public prototype_ `bool IsFrameAvailableToSend();` — Returns next frame ready to be sent. Can be null.
- L128 _public prototype_ `void FrameSentEvent();` — Mark a frame as sent
- L131 _public prototype_ `bool SetFrameData(TSharedPtr<FRivermaxOutputInfoVideo> NewFrame, TSharedPtr<FRivermaxOutputFrame> ReservedFrame);` — Initiates memory copy for a given frame
- L136 _private prototype_ `void OnDataCopied(const TSharedPtr<FBaseDataCopySideCar>& Sidecar);` — Called back when copy request was completed by allocator
- L141 _private member_ `FIntPoint FrameResolution = FIntPoint::ZeroValue;` — Resolution of video frames
- L144 _private member_ `uint32 TotalFrameCount = 0;` — Number of frames allocated
- L147 _private member_ `EFrameMemoryLocation MemoryLocation = EFrameMemoryLocation::None;` — Location of memory allocated
- L150 _private member_ `FCriticalSection ContainersCritSec;` — Critical section to protect various frame containers
- L153 _private member_ `TUniquePtr<FBaseFrameAllocator> FrameAllocator;` — Frame allocator dealing with memory operation
- L158 _private member_ `TUniquePtr<FRivermaxOutputFramePool> FramePool;` — Pool of allocated frames. Thread safe allocation. All items allocated via AcquireShared are returned back to the pool automatically.
- L161 _private member_ `TQueue<TSharedPtr<FRivermaxOutputFrame>> FramesToBeSent;` — Queue of frames that are ready to be sent. First in, first out.
- L164 _private member_ `FOnFreeFrameDelegate OnFreeFrameDelegate;` — Delegate triggered when a frame is free to use
- L167 _private member_ `FOnPreFrameReadyDelegate OnPreFrameReadyDelegate;` — Delegate triggered just before a frame is enqueued to be sent
- L170 _private member_ `FOnFrameReadyDelegate OnFrameReadyDelegate;` — Delegate triggered when a frame is ready to be sent (video data has been copied)
- L173 _private member_ `FOnCriticalErrorDelegate OnCriticalErrorDelegate;` — Delegate triggered when a critical error has happened and stream should shut down
- L176 _private member_ `TSharedPtr<IRivermaxManager> RivermaxManager;` — Quick access to rivermax manager

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace RivermaxCore` (scope `UE`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace RivermaxCore` (scope `UE`)
- L19 _namespace_ `namespace Private` (scope `UE::RivermaxCore`)
- L37 _delegate_ `DECLARE_DELEGATE(FOnFrameReadyDelegate);`
- L37 _prototype_ `DECLARE_DELEGATE(FOnFrameReadyDelegate);` (scope `UE::RivermaxCore::Private`)
- L38 _delegate_ `DECLARE_DELEGATE(FOnPreFrameReadyDelegate);`
- L38 _prototype_ `DECLARE_DELEGATE(FOnPreFrameReadyDelegate);` (scope `UE::RivermaxCore::Private`)
- L39 _delegate_ `DECLARE_DELEGATE(FOnFreeFrameDelegate);`
- L39 _prototype_ `DECLARE_DELEGATE(FOnFreeFrameDelegate);` (scope `UE::RivermaxCore::Private`)
- L40 _delegate_ `DECLARE_DELEGATE(FOnCriticalErrorDelegate);`
- L40 _prototype_ `DECLARE_DELEGATE(FOnCriticalErrorDelegate);` (scope `UE::RivermaxCore::Private`)

### `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxCore/Private/RivermaxLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogRivermax, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRivermax, Log, All);`

### `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxCore/Private/RivermaxManager.h` (Private)


#### class `UE::RivermaxCore::Private::FRivermaxManager`  
`class FRivermaxManager : public UE::RivermaxCore::IRivermaxManager`  
_L12-99_
- inherits: `UE::RivermaxCore::IRivermaxManager`
- L15 _public prototype_ `FRivermaxManager();`
- L16 _public prototype_ `~FRivermaxManager();`
- L20 _public prototype_ `virtual bool IsManagerInitialized() const override;`
- L21 _public prototype_ `virtual bool IsLibraryInitialized() const override;`
- L22 _public prototype_ `virtual bool ValidateLibraryIsLoaded() const override;`
- L23 _public prototype_ `virtual const RIVERMAX_API_FUNCTION_LIST* GetApi() const override;`
- L24 _public prototype_ `virtual FOnPostRivermaxManagerInit& OnPostRivermaxManagerInit() override;`
- L25 _public prototype_ `virtual uint64 GetTime() const override;`
- L26 _public prototype_ `virtual ERivermaxTimeSource GetTimeSource() const override;`
- L27 _public prototype_ `virtual TConstArrayView<FRivermaxDeviceInfo> GetDevices() const override;`
- L28 _public prototype_ `virtual bool GetMatchingDevice(const FString& InSourceIP, FString& OutDeviceIP) const override;`
- L29 _public prototype_ `virtual bool IsValidIP(const FString& InSourceIP) const override;`
- L30 _public prototype_ `virtual bool IsGPUDirectSupported() const override;`
- L31 _public prototype_ `virtual bool IsGPUDirectInputSupported() const override;`
- L32 _public prototype_ `virtual bool IsGPUDirectOutputSupported() const override;`
- L33 _public prototype_ `virtual bool EnableDynamicHeaderSupport(const FString& Interface) override;`
- L34 _public prototype_ `virtual void DisableDynamicHeaderSupport(const FString& Interface) override;`
- L40 _private prototype_ `bool LoadRivermaxLibrary();` — Loads the rivermax dll shipping with engine
- L43 _private prototype_ `bool LoadRivermaxFunctions();` — Load function pointers from the DLL.
- L46 _private prototype_ `void InitializeLibrary();` — Initializes rivermax library
- L49 _private prototype_ `void SetCPUAffinity(int32 CpuCore);` — Sets CPU affinity for Rivermax
- L52 _private prototype_ `void VerifyGPUDirectCapability();` — Verify if system is capable of doing GPUDirect
- L55 _private prototype_ `bool InitializeClock(ERivermaxTimeSource DesiredTimeSource);` — Initializes clock used by Rivermax internals
- L58 _private prototype_ `bool VerifyPrerequesites();` — Verify if all prerequesites to go through Rivermax initialization have been met
- L61 _private prototype_ `void InitializeTraceMarkupStrings();` — Initializes maps of strings used in various trace events to avoid allocating them continuously
- L65 _private member_ `bool bIsInitialized = false;` — True when manager has been initialized
- L68 _private member_ `bool bIsLibraryInitialized = false;` — True when library is usable
- L71 _private member_ `bool bIsLibraryLoaded = false;` — True when library function pointers are available.
- L74 _private member_ `bool bIsCleanupRequired = false;` — Whether library was initialized but failed along the way and needs to be cleaned up on exit
- L77 _private member_ `void* LibraryHandle = nullptr;` — Handle pointer to the loaded library
- L80 _private member_ `bool bIsGPUDirectSupported = false;` — Whether GPU direct is supported globally for rivermax. Currently means Cuda is present with RDMA support
- L83 _private member_ `ERivermaxTimeSource TimeSource = ERivermaxTimeSource::PTP;` — Current time source
- L86 _private member_ `TUniquePtr<FRivermaxDeviceFinder> DeviceFinder;` — Rivermax device finder listing all usable interfaces
- L89 _private member_ `FOnPostRivermaxManagerInit PostInitDelegate;` — Delegate triggered when initialization has completed
- L92 _private member_ `TMap<FString, uint32> DynamicHeaderUsers;` — Streams using dynamic header size per users. When last one is removing itself, it will be disabled
- L95 _private member_ `RIVERMAX_API_FUNCTION_LIST FuncList;` — List of function pointers to the rivermax DLL.
- L98 _private member_ `FDelegateHandle InitHandle;` — Delegate handle. Used to remove the delegate from subscribed module initialization delegate collection.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace RivermaxCore` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::RivermaxCore`)

### `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxCore/Private/RivermaxOutputFrame.h` (Private)


#### class `UE::RivermaxCore::Private::FRivermaxOutputFrame`  
`class FRivermaxOutputFrame : public IMediaPoolable`  
_L16-99_
- inherits: `IMediaPoolable`
- desc: Output frame descriptor. Contains data to be sent on the wire and packetization tracking
- L19 _public prototype_ `FRivermaxOutputFrame();`
- L20 _public prototype_ `FRivermaxOutputFrame(const FRivermaxOutputFrame&) = delete;`
- L21 _public prototype_ `FRivermaxOutputFrame& operator=(const FRivermaxOutputFrame&) = delete;`
- L24 _public prototype_ `void Clear();` — Reset internal counters to make it resendable
- L27 _public prototype_ `void Reset();` — Reset identifier and internal counters to make it available
- L37 _public member_ `void* Buffer = nullptr;` — Buffer where we copy our data. In Case of Video stream this is where we copy texture to be sent out If using GPUDirect, memory will be allocated in cuda space In case of ANCILLARY this will contain our ancillary
- L40 _public member_ `FTimecode Timecode;` — Timecode at which this frame was captured
- L43 _public member_ `uint32 PacketCounter = 0;` — Variables about progress of packetization of the frame
- L44 _public member_ `uint32 LineNumber = 0;`
- L45 _public member_ `uint16 SRDOffset = 0;`
- L46 _public member_ `uint32 ChunkNumber = 0;`
- L49 _public member_ `uint32 MediaTimestamp = 0;` — Timestamp of this frame used for RTP headers
- L52 _public member_ `void* PayloadPtr = nullptr;` — Payload (data) pointer retrieved from Rivermax for the next chunk
- L55 _public member_ `void* HeaderPtr = nullptr;` — Header pointer retrieved from Rivermax for the next chunk
- L58 _public member_ `void* FrameStartPtr = nullptr;` — Cached address of beginning of frame in Rivermax's memblock. Used when using intermediate buffer/
- L61 _public member_ `SIZE_T Offset = 0;` — Offset in the frame where we are at to copy next block of data
- L64 _public member_ `bool bCaughtTimingIssue = false;` — Whether timing issues were detected while sending frame out. If yes, we skip the next frame boundary
- L70 _public function_ `void SetFrameCounter(uint64 InFrameCounter)` — Set frame counter .
- L78 _public function_ `uint64 GetFrameCounter()` — Returns frame counter corresponding to the data captured by Media Capture.
- L86 _public function_ `virtual bool IsReadyForReuse()` — Used to check if returned object is ready for reuse right away
- L94 _public function_ `virtual void ShutdownPoolable()` — Used to check if returned object is ready for reuse right away
- L98 _private member_ `uint64 FrameCounter;` — Number corresponding to the engine frame counter of the frame captured by Media Capture.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace RivermaxCore` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::RivermaxCore`)

### `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxCore/Private/RivermaxUtils.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace RivermaxCore` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::RivermaxCore`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace RivermaxCore` (scope `UE`)
- L20 _namespace_ `namespace Private` (scope `UE::RivermaxCore`)
- L20 _namespace_ `namespace Utils` (scope `UE::RivermaxCore::Private`)
- L24 _variable_ `static constexpr uint32 FullHDHeight = 1080;` (scope `UE::RivermaxCore::Private::Utils`)
- L25 _variable_ `static constexpr uint32 FullHDWidth = 1920;` (scope `UE::RivermaxCore::Private::Utils`)
- L28 _variable_ `static constexpr double MediaClockSampleRate = 90000.0;` (scope `UE::RivermaxCore::Private::Utils`) — SMTPE 2110-10.The Media Clock and RTP Clock rate for streams compliant to this standard shall be 90 kHz.
- L31 _variable_ `static constexpr float SleepTimeSeconds = 50 * 1E-6f;` (scope `UE::RivermaxCore::Private::Utils`) — Common sleep time used in places where we are waiting for something to complete
- L37 _prototype_ `uint32 TimestampToFrameNumber(uint32 Timestamp, const FFrameRate& FrameRate);` (scope `UE::RivermaxCore::Private::Utils`) — Converts a timestamp in MediaClock period units to a frame number for a given frame rate 2110-20 streams uses a standard media clock rate of 90kHz
- L40 _prototype_ `uint32 GetTimestampFromTime(uint64 InTimeNanosec, double InMediaClockRate);` (scope `UE::RivermaxCore::Private::Utils`) — Returns a mediaclock timestamp, for rtp, based on a clock time
- L43 _prototype_ `FTimecode GetTimecodeFromTime(uint64 InTimeNanosec, double InMediaClockRate, const FFrameRate& FrameRate);` (scope `UE::RivermaxCore::Private::Utils`) — Convert PTP time to timecode.
- L52 _function_ `inline uint16 MakeDataIdentificationWord(uint8 byte8)` (scope `UE::RivermaxCore::Private::Utils`) — Creates a Data Identification Word (DID, SDID). Both DID and SDID need to comply with ST291-1 standard: bits b7 (MSB) through b0 (LSB) shall define the 8-bit SDID word (00h through FFh) bit b8 shall be even parity for bits b7 through b0 bit b9 = NOT b8.
- L64 _prototype_ `TArray<uint16> TimecodeToAtcUDW10(const FTimecode& Tc, const FFrameRate& Rate);` (scope `UE::RivermaxCore::Private::Utils`) — Packs the timecode into user data words (UDW) according to ST 12-2 and returns an array of UDWs already ready to be put into RTP packet.
- L70 _prototype_ `uint16 ComputeAncChecksum(uint16 DID, uint16 SDID, uint16 DataCount, const TArray<uint16>& UDWs);` (scope `UE::RivermaxCore::Private::Utils`) — Computes the 10-bit RFC8331 ANC checksum over DID, SDID, DataCount, and UDWs. Only the low 9 bits of each word are summed; bit 9 of the result is NOT b8. Used by both output (packing) and input (verification).
- L101 _prototype_ `void GenerateRtpHeaderWithFields(const FString& JsonFilePath, const FString& OutputJsonPath);` (scope `UE::RivermaxCore::Private::Utils`) — A helper function that reads a json file with a packet information and its bitfields and outputs json with alignment in platform endianness. This function is only usable for debugging purposes and works only when RIVERMAX_PACKET_DEBUG is set. Sample Input: { "Fields": [ { "Field": "V",  "Bits":  2 }, { "Field": "P",  "Bits":  1 }, { "Field": "X",  "Bits":  1 }, { "Field": "CC", "Bits":  4 }, { "Field": "M",  "Bits":  1 }, { "Field": "PT", "Bits":  7 } ] } Sample Output: { "Fields": [ {"Field": "CC", "Bits": 4}, {"Field": "X",  "Bits": 1}, {"Field": "P",  "Bits": 1}, {"Field": "V",  "Bits": 2}, {"Field": "PT", "Bits": 7}, {"Field": "M",  "Bits": 1} ] }

### `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxCore/Private/RivermaxWrapper.h` (Private)


#### struct `UE::RivermaxCore::Private::RIVERMAX_API_FUNCTION_LIST`  
`struct RIVERMAX_API_FUNCTION_LIST`  
_L148-284_
- L150 _public member_ `PFNRMX_GET_VERSION_NUMBERS rmx_get_version_numbers;`
- L151 _public member_ `PFNRMX_GET_VERSION_STRING rmx_get_version_string;`
- L152 _public member_ `PFNRMX_SET_CPU_AFFINITY rmx_set_cpu_affinity;`
- L153 _public member_ `PFNRMX_ENABLE_SYSTEM_SIGNAL_HANDLING rmx_enable_system_signal_handling;`
- L154 _public member_ `PFNRMX_INIT_LIB_PARAM rmx_init_lib_param;`
- L155 _public member_ `PFNRMX_SET_LIB_PARAM_NAME rmx_set_lib_param_name;`
- L156 _public member_ `PFNRMX_SET_LIB_PARAM_VALUE rmx_set_lib_param_value;`
- L157 _public member_ `PFNRMX_SET_LIB_PARAM_FORCED rmx_set_lib_param_forced;`
- L158 _public member_ `PFNRMX_APPLY_LIB_PARAM rmx_apply_lib_param;`
- L159 _public member_ `PFN_RMX_INIT _rmx_init;`
- L160 _public member_ `PFNRMX_CLEANUP rmx_cleanup;`
- L161 _public member_ `PFNRMX_GET_DEVICE_LIST rmx_get_device_list;`
- L162 _public member_ `PFNRMX_FREE_DEVICE_LIST rmx_free_device_list;`
- L163 _public member_ `PFNRMX_GET_DEVICE_COUNT rmx_get_device_count;`
- L164 _public member_ `PFNRMX_GET_DEVICE rmx_get_device;`
- L165 _public member_ `PFNRMX_GET_DEVICE_INTERFACE_NAME rmx_get_device_interface_name;`
- L166 _public member_ `PFNRMX_GET_DEVICE_IP_COUNT rmx_get_device_ip_count;`
- L167 _public member_ `PFNRMX_GET_DEVICE_IP_ADDRESS rmx_get_device_ip_address;`
- L168 _public member_ `PFNRMX_GET_DEVICE_MAC_ADDRESS rmx_get_device_mac_address;`
- L169 _public member_ `PFNRMX_GET_DEVICE_ID rmx_get_device_id;`
- L170 _public member_ `PFNRMX_GET_DEVICE_SERIAL_NUMBER rmx_get_device_serial_number;`
- L171 _public member_ `PFNRMX_RETRIEVE_DEVICE_IFACE rmx_retrieve_device_iface;`
- L172 _public member_ `PFNRMX_CLEAR_DEVICE_CAPABILITIES_ENQUIRY rmx_clear_device_capabilities_enquiry;`
- L173 _public member_ `PFNRMX_ENQUIRE_DEVICE_CAPABILITIES rmx_enquire_device_capabilities;`
- L174 _public member_ `PFNRMX_APPLY_DEVICE_CONFIG rmx_apply_device_config;`
- L175 _public member_ `PFNRMX_REVERT_DEVICE_CONFIG rmx_revert_device_config;`
- L176 _public member_ `PFNRMX_INIT_USER_CLOCK rmx_init_user_clock;`
- L177 _public member_ `PFNRMX_SET_USER_CLOCK_HANDLER rmx_set_user_clock_handler;`
- L178 _public member_ `PFNRMX_SET_USER_CLOCK_CONTEXT rmx_set_user_clock_context;`
- L179 _public member_ `PFNRMX_USE_USER_CLOCK rmx_use_user_clock;`
- L180 _public member_ `PFNRMX_INIT_PTP_CLOCK rmx_init_ptp_clock;`
- L181 _public member_ `PFNRMX_SET_PTP_CLOCK_DEVICE rmx_set_ptp_clock_device;`
- L182 _public member_ `PFNRMX_USE_PTP_CLOCK rmx_use_ptp_clock;`
- L183 _public member_ `PFNRMX_CHECK_CLOCK_STEADY rmx_check_clock_steady;`
- L184 _public member_ `PFNRMX_GET_TIME rmx_get_time;`
- L185 _public member_ `PFNRMX_INIT_SOCKADDR_IN rmx_init_sockaddr_in;`
- L186 _public member_ `PFNRMX_RESOLVE_SOCKADDR rmx_resolve_sockaddr;`
- L187 _public member_ `PFNRMX_SOCKADDR_TO_STD_SOCKADDR rmx_sockaddr_to_std_sockaddr;`
- L188 _public member_ `PFNRMX_INIT_EVENT_CHANNEL rmx_init_event_channel;`
- L189 _public member_ `PFNRMX_SET_EVENT_CHANNEL_HANDLE rmx_set_event_channel_handle;`
- L190 _public member_ `PFNRMX_ESTABLISH_EVENT_CHANNEL rmx_establish_event_channel;`
- L191 _public member_ `PFNRMX_INIT_NOTIFICATION rmx_init_notification;`
- L193 _public member_ `PFNRMX_SET_NOTIFICATION_OVERLAPPED rmx_set_notification_overlapped;`
- L195 _public member_ `PFNRMX_REQUEST_NOTIFICATION rmx_request_notification;`
- L196 _public member_ `PFNRMX_INIT_MEM_REGISTRY rmx_init_mem_registry;`
- L197 _public member_ `PFNRMX_SET_MEM_REGISTRY_OPTION rmx_set_mem_registry_option;`
- L198 _public member_ `PFNRMX_REGISTER_MEMORY rmx_register_memory;`
- L199 _public member_ `PFNRMX_DEREGISTER_MEMORY rmx_deregister_memory;`
- L200 _public member_ `PFNRMX_INPUT_INIT_STREAM rmx_input_init_stream;`
- L201 _public member_ `PFNRMX_INPUT_SET_MEM_CAPACITY_IN_PACKETS rmx_input_set_mem_capacity_in_packets;`
- L202 _public member_ `PFNRMX_INPUT_SET_STREAM_NIC_ADDRESS rmx_input_set_stream_nic_address;`
- L203 _public member_ `PFNRMX_INPUT_ENABLE_STREAM_OPTION rmx_input_enable_stream_option;`
- L204 _public member_ `PFNRMX_INPUT_SET_MEM_SUB_BLOCK_COUNT rmx_input_set_mem_sub_block_count;`
- L205 _public member_ `PFNRMX_INPUT_SET_ENTRY_SIZE_RANGE rmx_input_set_entry_size_range;`
- L206 _public member_ `PFNRMX_INPUT_DETERMINE_MEM_LAYOUT rmx_input_determine_mem_layout;`
- L207 _public member_ `PFNRMX_INPUT_GET_MEM_CAPACITY_IN_PACKETS rmx_input_get_mem_capacity_in_packets;`
- L208 _public member_ `PFNRMX_INPUT_GET_MEM_BLOCK_BUFFER rmx_input_get_mem_block_buffer;`
- L209 _public member_ `PFNRMX_INPUT_GET_STRIDE_SIZE rmx_input_get_stride_size;`
- L210 _public member_ `PFNRMX_INPUT_SET_TIMESTAMP_FORMAT rmx_input_set_timestamp_format;`
- L211 _public member_ `PFNRMX_INPUT_CREATE_STREAM rmx_input_create_stream;`
- L212 _public member_ `PFNRMX_INPUT_DESTROY_STREAM rmx_input_destroy_stream;`
- L213 _public member_ `PFNRMX_INPUT_INIT_FLOW rmx_input_init_flow;`
- L214 _public member_ `PFNRMX_INPUT_SET_FLOW_LOCAL_ADDR rmx_input_set_flow_local_addr;`
- L215 _public member_ `PFNRMX_INPUT_SET_FLOW_REMOTE_ADDR rmx_input_set_flow_remote_addr;`
- L216 _public member_ `PFNRMX_INPUT_SET_FLOW_TAG rmx_input_set_flow_tag;`
- L217 _public member_ `PFNRMX_INPUT_ATTACH_FLOW rmx_input_attach_flow;`
- L218 _public member_ `PFNRMX_INPUT_DETACH_FLOW rmx_input_detach_flow;`
- L219 _public member_ `PFNRMX_INPUT_SET_COMPLETION_MODERATION rmx_input_set_completion_moderation;`
- L220 _public member_ `PFNRMX_INPUT_INIT_CHUNK_HANDLE rmx_input_init_chunk_handle;`
- L221 _public member_ `PFNRMX_INPUT_GET_NEXT_CHUNK rmx_input_get_next_chunk;`
- L222 _public member_ `PFNRMX_INPUT_GET_CHUNK_COMPLETION rmx_input_get_chunk_completion;`
- L223 _public member_ `PFNRMX_INPUT_GET_PACKET_INFO rmx_input_get_packet_info;`
- L224 _public member_ `PFNRMX_OUTPUT_MEDIA_INIT rmx_output_media_init;`
- L225 _public member_ `PFNRMX_OUTPUT_MEDIA_SET_SDP rmx_output_media_set_sdp;`
- L226 _public member_ `PFNRMX_OUTPUT_MEDIA_SET_IDX_IN_SDP rmx_output_media_set_idx_in_sdp;`
- L227 _public member_ `PFNRMX_OUTPUT_MEDIA_SET_PACKETS_PER_FRAME rmx_output_media_set_packets_per_frame;`
- L228 _public member_ `PFNRMX_OUTPUT_MEDIA_SET_SOURCE_PORTS rmx_output_media_set_source_ports;`
- L229 _public member_ `PFNRMX_OUTPUT_MEDIA_SET_TX_ADAPTIVE_SCHEDULING_FACTOR rmx_output_media_set_tx_adaptive_scheduling_factor;`
- L230 _public member_ `PFNRMX_OUTPUT_MEDIA_SET_PCP rmx_output_media_set_pcp;`
- L231 _public member_ `PFNRMX_OUTPUT_MEDIA_SET_DSCP rmx_output_media_set_dscp;`
- L232 _public member_ `PFNRMX_OUTPUT_MEDIA_SET_ECN rmx_output_media_set_ecn;`
- L233 _public member_ `PFNRMX_OUTPUT_MEDIA_INIT_MEM_BLOCKS rmx_output_media_init_mem_blocks;`
- L234 _public member_ `PFNRMX_OUTPUT_MEDIA_SET_CHUNK_COUNT rmx_output_media_set_chunk_count;`
- L235 _public member_ `PFNRMX_OUTPUT_MEDIA_SET_SUB_BLOCK_COUNT rmx_output_media_set_sub_block_count;`
- L236 _public member_ `PFNRMX_OUTPUT_MEDIA_GET_SUB_BLOCK rmx_output_media_get_sub_block;`
- L237 _public member_ `PFNRMX_OUTPUT_MEDIA_GET_DUP_SUB_BLOCK rmx_output_media_get_dup_sub_block;`
- L238 _public member_ `PFNRMX_OUTPUT_MEDIA_SET_PACKET_LAYOUT rmx_output_media_set_packet_layout;`
- L239 _public member_ `PFNRMX_OUTPUT_MEDIA_ASSIGN_MEM_BLOCKS rmx_output_media_assign_mem_blocks;`
- L240 _public member_ `PFNRMX_OUTPUT_MEDIA_SET_PACKETS_PER_CHUNK rmx_output_media_set_packets_per_chunk;`
- L241 _public member_ `PFNRMX_OUTPUT_MEDIA_SET_STRIDE_SIZE rmx_output_media_set_stride_size;`
- L242 _public member_ `PFNRMX_OUTPUT_MEDIA_CREATE_STREAM rmx_output_media_create_stream;`
- L243 _public member_ `PFNRMX_OUTPUT_MEDIA_DESTROY_STREAM rmx_output_media_destroy_stream;`
- L244 _public member_ `PFNRMX_OUTPUT_MEDIA_INIT_CONTEXT rmx_output_media_init_context;`
- L245 _public member_ `PFNRMX_OUTPUT_MEDIA_SET_CONTEXT_BLOCK rmx_output_media_set_context_block;`
- L246 _public member_ `PFNRMX_OUTPUT_MEDIA_GET_LOCAL_ADDRESS rmx_output_media_get_local_address;`
- L247 _public member_ `PFNRMX_OUTPUT_MEDIA_GET_REMOTE_ADDRESS rmx_output_media_get_remote_address;`
- L248 _public member_ `PFNRMX_OUTPUT_MEDIA_INIT_CHUNK_HANDLE rmx_output_media_init_chunk_handle;`
- L249 _public member_ `PFNRMX_OUTPUT_MEDIA_SET_CHUNK_PACKET_COUNT rmx_output_media_set_chunk_packet_count;`
- L250 _public member_ `PFNRMX_OUTPUT_MEDIA_GET_NEXT_CHUNK rmx_output_media_get_next_chunk;`
- L251 _public member_ `PFNRMX_OUTPUT_MEDIA_MARK_CHUNK_FOR_TRACKING rmx_output_media_mark_chunk_for_tracking;`
- L252 _public member_ `PFNRMX_OUTPUT_MEDIA_COMMIT_CHUNK rmx_output_media_commit_chunk;`
- L253 _public member_ `PFNRMX_OUTPUT_MEDIA_POLL_FOR_COMPLETION rmx_output_media_poll_for_completion;`
- L254 _public member_ `PFNRMX_OUTPUT_MEDIA_GET_LAST_COMPLETION rmx_output_media_get_last_completion;`
- L255 _public member_ `PFNRMX_OUTPUT_MEDIA_CANCEL_UNSENT_CHUNKS rmx_output_media_cancel_unsent_chunks;`
- L256 _public member_ `PFNRMX_OUTPUT_MEDIA_SKIP_CHUNKS rmx_output_media_skip_chunks;`
- L257 _public member_ `PFNRMX_OUTPUT_GEN_INIT_STREAM rmx_output_gen_init_stream;`
- L258 _public member_ `PFNRMX_OUTPUT_GEN_SET_PACKETS_PER_CHUNK rmx_output_gen_set_packets_per_chunk;`
- L259 _public member_ `PFNRMX_OUTPUT_GEN_SET_LOCAL_ADDR rmx_output_gen_set_local_addr;`
- L260 _public member_ `PFNRMX_OUTPUT_GEN_SET_REMOTE_ADDR rmx_output_gen_set_remote_addr;`
- L261 _public member_ `PFNRMX_OUTPUT_GEN_SET_MAX_SUB_BLOCKS rmx_output_gen_set_max_sub_blocks;`
- L262 _public member_ `PFNRMX_OUTPUT_GEN_SET_PCP rmx_output_gen_set_pcp;`
- L263 _public member_ `PFNRMX_OUTPUT_GEN_SET_DSCP rmx_output_gen_set_dscp;`
- L264 _public member_ `PFNRMX_OUTPUT_GEN_SET_ECN rmx_output_gen_set_ecn;`
- L265 _public member_ `PFNRMX_OUTPUT_GEN_SET_RATE rmx_output_gen_set_rate;`
- L266 _public member_ `PFNRMX_OUTPUT_GEN_CREATE_STREAM rmx_output_gen_create_stream;`
- L267 _public member_ `PFNRMX_OUTPUT_GEN_DESTROY_STREAM rmx_output_gen_destroy_stream;`
- L268 _public member_ `PFNRMX_OUTPUT_GEN_INIT_RATE rmx_output_gen_init_rate;`
- L269 _public member_ `PFNRMX_OUTPUT_GEN_SET_RATE_MAX_BURST rmx_output_gen_set_rate_max_burst;`
- L270 _public member_ `PFNRMX_OUTPUT_GEN_SET_RATE_TYPICAL_PACKET_SIZE rmx_output_gen_set_rate_typical_packet_size;`
- L271 _public member_ `PFNRMX_OUTPUT_GEN_UPDATE_RATE rmx_output_gen_update_rate;`
- L272 _public member_ `PFNRMX_OUTPUT_GEN_UPDATE_REMOTE_ADDR rmx_output_gen_update_remote_addr;`
- L273 _public member_ `PFNRMX_OUTPUT_GEN_INIT_CHUNK_HANDLE rmx_output_gen_init_chunk_handle;`
- L274 _public member_ `PFNRMX_OUTPUT_GEN_GET_NEXT_CHUNK rmx_output_gen_get_next_chunk;`
- L275 _public member_ `PFNRMX_OUTPUT_GEN_SET_CHUNK_REMOTE_ADDR rmx_output_gen_set_chunk_remote_addr;`
- L276 _public member_ `PFNRMX_OUTPUT_GEN_APPEND_PACKET_TO_CHUNK rmx_output_gen_append_packet_to_chunk;`
- L277 _public member_ `PFNRMX_OUTPUT_GEN_MARK_CHUNK_FOR_TRACKING rmx_output_gen_mark_chunk_for_tracking;`
- L278 _public member_ `PFNRMX_OUTPUT_GEN_COMMIT_CHUNK rmx_output_gen_commit_chunk;`
- L279 _public member_ `PFNRMX_OUTPUT_GEN_POLL_FOR_COMPLETION rmx_output_gen_poll_for_completion;`
- L280 _public member_ `PFNRMX_OUTPUT_GEN_GET_LAST_COMPLETION rmx_output_gen_get_last_completion;`
- L281 _public member_ `PFNRMX_OUTPUT_GET_CHUNK_COUNT rmx_output_get_chunk_count;`
- L282 _public member_ `PFNRMX_OUTPUT_UPDATE_DSCP rmx_output_update_dscp;`
- L283 _public member_ `PFNRMX_OUTPUT_UPDATE_ECN rmx_output_update_ecn;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace RivermaxCore` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::RivermaxCore`)
- L12 _typedef_ `typedef const rmx_version * (*PFNRMX_GET_VERSION_NUMBERS)(void);` (scope `UE::RivermaxCore::Private`)
- L13 _typedef_ `typedef const char * (*PFNRMX_GET_VERSION_STRING)(void);` (scope `UE::RivermaxCore::Private`)
- L14 _typedef_ `typedef rmx_status (*PFNRMX_SET_CPU_AFFINITY)(const uint64_t * bitmask, size_t core_count);` (scope `UE::RivermaxCore::Private`)
- L15 _typedef_ `typedef rmx_status (*PFNRMX_ENABLE_SYSTEM_SIGNAL_HANDLING)(void);` (scope `UE::RivermaxCore::Private`)
- L16 _typedef_ `typedef void (*PFNRMX_INIT_LIB_PARAM)(rmx_lib_param * descriptor);` (scope `UE::RivermaxCore::Private`)
- L17 _typedef_ `typedef void (*PFNRMX_SET_LIB_PARAM_NAME)(rmx_lib_param * descriptor, const char * name);` (scope `UE::RivermaxCore::Private`)
- L18 _typedef_ `typedef void (*PFNRMX_SET_LIB_PARAM_VALUE)(rmx_lib_param * descriptor, const char * value);` (scope `UE::RivermaxCore::Private`)
- L19 _typedef_ `typedef void (*PFNRMX_SET_LIB_PARAM_FORCED)(rmx_lib_param * descriptor);` (scope `UE::RivermaxCore::Private`)
- L20 _typedef_ `typedef rmx_status (*PFNRMX_APPLY_LIB_PARAM)(rmx_lib_param * descriptor);` (scope `UE::RivermaxCore::Private`)
- L21 _typedef_ `typedef rmx_status (*PFN_RMX_INIT)(const rmx_version * policy);` (scope `UE::RivermaxCore::Private`)
- L22 _typedef_ `typedef rmx_status (*PFNRMX_CLEANUP)(void);` (scope `UE::RivermaxCore::Private`)
- L23 _typedef_ `typedef size_t (*PFNRMX_GET_DEVICE_LIST)(rmx_device_list ** list);` (scope `UE::RivermaxCore::Private`)
- L24 _typedef_ `typedef void (*PFNRMX_FREE_DEVICE_LIST)(rmx_device_list * list);` (scope `UE::RivermaxCore::Private`)
- L25 _typedef_ `typedef size_t (*PFNRMX_GET_DEVICE_COUNT)(const rmx_device_list * list);` (scope `UE::RivermaxCore::Private`)
- L26 _typedef_ `typedef const rmx_device * (*PFNRMX_GET_DEVICE)(const rmx_device_list * list, size_t index);` (scope `UE::RivermaxCore::Private`)
- L27 _typedef_ `typedef const char * (*PFNRMX_GET_DEVICE_INTERFACE_NAME)(const rmx_device * device);` (scope `UE::RivermaxCore::Private`)
- L28 _typedef_ `typedef size_t (*PFNRMX_GET_DEVICE_IP_COUNT)(const rmx_device * device);` (scope `UE::RivermaxCore::Private`)
- L29 _typedef_ `typedef const rmx_ip_addr * (*PFNRMX_GET_DEVICE_IP_ADDRESS)(const rmx_device * device, size_t index);` (scope `UE::RivermaxCore::Private`)
- L30 _typedef_ `typedef const uint8_t * (*PFNRMX_GET_DEVICE_MAC_ADDRESS)(const rmx_device * device);` (scope `UE::RivermaxCore::Private`)
- L31 _typedef_ `typedef uint32_t (*PFNRMX_GET_DEVICE_ID)(const rmx_device * device);` (scope `UE::RivermaxCore::Private`)
- L32 _typedef_ `typedef const char * (*PFNRMX_GET_DEVICE_SERIAL_NUMBER)(const rmx_device * device);` (scope `UE::RivermaxCore::Private`)
- L33 _typedef_ `typedef rmx_status (*PFNRMX_RETRIEVE_DEVICE_IFACE)(rmx_device_iface * device_iface, const rmx_ip_addr * ip);` (scope `UE::RivermaxCore::Private`)
- L34 _typedef_ `typedef void (*PFNRMX_CLEAR_DEVICE_CAPABILITIES_ENQUIRY)(rmx_device_capabilities * caps);` (scope `UE::RivermaxCore::Private`)
- L35 _typedef_ `typedef rmx_status (*PFNRMX_ENQUIRE_DEVICE_CAPABILITIES)(const rmx_device_iface * device_iface, rmx_device_capabilities * caps);` (scope `UE::RivermaxCore::Private`)
- L36 _typedef_ `typedef rmx_status (*PFNRMX_APPLY_DEVICE_CONFIG)(const rmx_device_iface * device_iface, rmx_device_config * config);` (scope `UE::RivermaxCore::Private`)
- L37 _typedef_ `typedef rmx_status (*PFNRMX_REVERT_DEVICE_CONFIG)(const rmx_device_iface * device_iface, rmx_device_config * config);` (scope `UE::RivermaxCore::Private`)
- L38 _typedef_ `typedef void (*PFNRMX_INIT_USER_CLOCK)(rmx_user_clock_params * params);` (scope `UE::RivermaxCore::Private`)
- L39 _typedef_ `typedef void (*PFNRMX_SET_USER_CLOCK_HANDLER)(rmx_user_clock_params * params, rmx_user_clock_handler handler);` (scope `UE::RivermaxCore::Private`)
- L40 _typedef_ `typedef void (*PFNRMX_SET_USER_CLOCK_CONTEXT)(rmx_user_clock_params * params, void * ctx);` (scope `UE::RivermaxCore::Private`)
- L41 _typedef_ `typedef rmx_status (*PFNRMX_USE_USER_CLOCK)(const rmx_user_clock_params * params);` (scope `UE::RivermaxCore::Private`)
- L42 _typedef_ `typedef void (*PFNRMX_INIT_PTP_CLOCK)(rmx_ptp_clock_params * params);` (scope `UE::RivermaxCore::Private`)
- L43 _typedef_ `typedef void (*PFNRMX_SET_PTP_CLOCK_DEVICE)(rmx_ptp_clock_params * params, const rmx_device_iface * device_iface);` (scope `UE::RivermaxCore::Private`)
- L44 _typedef_ `typedef rmx_status (*PFNRMX_USE_PTP_CLOCK)(const rmx_ptp_clock_params * params);` (scope `UE::RivermaxCore::Private`)
- L45 _typedef_ `typedef rmx_status (*PFNRMX_CHECK_CLOCK_STEADY)(void);` (scope `UE::RivermaxCore::Private`)
- L46 _typedef_ `typedef rmx_status (*PFNRMX_GET_TIME)(rmx_time_type type, uint64_t * time);` (scope `UE::RivermaxCore::Private`)
- L47 _typedef_ `typedef rmx_status (*PFNRMX_INIT_SOCKADDR_IN)(rmx_sockaddr * addr, const struct sockaddr_in * src);` (scope `UE::RivermaxCore::Private`)
- L48 _typedef_ `typedef rmx_status (*PFNRMX_RESOLVE_SOCKADDR)(rmx_sockaddr * addr, const rmx_device_iface * device_iface);` (scope `UE::RivermaxCore::Private`)
- L49 _typedef_ `typedef rmx_status (*PFNRMX_SOCKADDR_TO_STD_SOCKADDR)(struct sockaddr * dst, const rmx_sockaddr * src);` (scope `UE::RivermaxCore::Private`)
- L50 _typedef_ `typedef void (*PFNRMX_INIT_EVENT_CHANNEL)(rmx_event_channel_params * params, rmx_stream_id id);` (scope `UE::RivermaxCore::Private`)
- L51 _typedef_ `typedef void (*PFNRMX_SET_EVENT_CHANNEL_HANDLE)(rmx_event_channel_params * params, rmx_event_channel_handle * handle);` (scope `UE::RivermaxCore::Private`)
- L52 _typedef_ `typedef rmx_status (*PFNRMX_ESTABLISH_EVENT_CHANNEL)(rmx_event_channel_params * params);` (scope `UE::RivermaxCore::Private`)
- L53 _typedef_ `typedef void (*PFNRMX_INIT_NOTIFICATION)(rmx_notification_params * params, rmx_stream_id id);` (scope `UE::RivermaxCore::Private`)
- L55 _typedef_ `typedef void (*PFNRMX_SET_NOTIFICATION_OVERLAPPED)(rmx_notification_params * params, OVERLAPPED * overlapped);` (scope `UE::RivermaxCore::Private`)
- L57 _typedef_ `typedef rmx_status (*PFNRMX_REQUEST_NOTIFICATION)(rmx_notification_params * params);` (scope `UE::RivermaxCore::Private`)
- L58 _typedef_ `typedef void (*PFNRMX_INIT_MEM_REGISTRY)(rmx_mem_reg_params * params, const rmx_device_iface * device_iface);` (scope `UE::RivermaxCore::Private`)
- L59 _typedef_ `typedef void (*PFNRMX_SET_MEM_REGISTRY_OPTION)(rmx_mem_reg_params * params, rmx_mem_reg_params_option option);` (scope `UE::RivermaxCore::Private`)
- L60 _typedef_ `typedef rmx_status (*PFNRMX_REGISTER_MEMORY)(rmx_mem_region * mem, const rmx_mem_reg_params * params);` (scope `UE::RivermaxCore::Private`)
- L61 _typedef_ `typedef rmx_status (*PFNRMX_DEREGISTER_MEMORY)(const rmx_mem_region * mem, const rmx_device_iface * device_iface);` (scope `UE::RivermaxCore::Private`)
- L62 _typedef_ `typedef void (*PFNRMX_INPUT_INIT_STREAM)(rmx_input_stream_params * params, rmx_input_stream_params_type type);` (scope `UE::RivermaxCore::Private`)
- L63 _typedef_ `typedef void (*PFNRMX_INPUT_SET_MEM_CAPACITY_IN_PACKETS)(rmx_input_stream_params * params, size_t count);` (scope `UE::RivermaxCore::Private`)
- L64 _typedef_ `typedef void (*PFNRMX_INPUT_SET_STREAM_NIC_ADDRESS)(rmx_input_stream_params * params, const struct sockaddr * nic_address);` (scope `UE::RivermaxCore::Private`)
- L65 _typedef_ `typedef void (*PFNRMX_INPUT_ENABLE_STREAM_OPTION)(rmx_input_stream_params * params, rmx_input_option option);` (scope `UE::RivermaxCore::Private`)
- L66 _typedef_ `typedef void (*PFNRMX_INPUT_SET_MEM_SUB_BLOCK_COUNT)(rmx_input_stream_params * params, size_t count);` (scope `UE::RivermaxCore::Private`)
- L67 _typedef_ `typedef void (*PFNRMX_INPUT_SET_ENTRY_SIZE_RANGE)(rmx_input_stream_params * params, size_t sub_block_id, size_t min_size, size_t max_size);` (scope `UE::RivermaxCore::Private`)
- L68 _typedef_ `typedef rmx_status (*PFNRMX_INPUT_DETERMINE_MEM_LAYOUT)(rmx_input_stream_params * params);` (scope `UE::RivermaxCore::Private`)
- L69 _typedef_ `typedef size_t (*PFNRMX_INPUT_GET_MEM_CAPACITY_IN_PACKETS)(const rmx_input_stream_params * params);` (scope `UE::RivermaxCore::Private`)
- L70 _typedef_ `typedef rmx_mem_region * (*PFNRMX_INPUT_GET_MEM_BLOCK_BUFFER)(rmx_input_stream_params * params, size_t sub_block_id);` (scope `UE::RivermaxCore::Private`)
- L71 _typedef_ `typedef size_t (*PFNRMX_INPUT_GET_STRIDE_SIZE)(const rmx_input_stream_params * params, size_t sub_block_id);` (scope `UE::RivermaxCore::Private`)
- L72 _typedef_ `typedef void (*PFNRMX_INPUT_SET_TIMESTAMP_FORMAT)(rmx_input_stream_params * params, rmx_input_timestamp_format format);` (scope `UE::RivermaxCore::Private`)
- L73 _typedef_ `typedef rmx_status (*PFNRMX_INPUT_CREATE_STREAM)(rmx_input_stream_params * params, rmx_stream_id * id);` (scope `UE::RivermaxCore::Private`)
- L74 _typedef_ `typedef rmx_status (*PFNRMX_INPUT_DESTROY_STREAM)(rmx_stream_id id);` (scope `UE::RivermaxCore::Private`)
- L75 _typedef_ `typedef void (*PFNRMX_INPUT_INIT_FLOW)(rmx_input_flow * flow);` (scope `UE::RivermaxCore::Private`)
- L76 _typedef_ `typedef void (*PFNRMX_INPUT_SET_FLOW_LOCAL_ADDR)(rmx_input_flow * flow, const struct sockaddr * local);` (scope `UE::RivermaxCore::Private`)
- L77 _typedef_ `typedef void (*PFNRMX_INPUT_SET_FLOW_REMOTE_ADDR)(rmx_input_flow * flow, const struct sockaddr * remote);` (scope `UE::RivermaxCore::Private`)
- L78 _typedef_ `typedef void (*PFNRMX_INPUT_SET_FLOW_TAG)(rmx_input_flow * flow, uint32_t tag);` (scope `UE::RivermaxCore::Private`)
- L79 _typedef_ `typedef rmx_status (*PFNRMX_INPUT_ATTACH_FLOW)(rmx_stream_id id, const rmx_input_flow * flow);` (scope `UE::RivermaxCore::Private`)
- L80 _typedef_ `typedef rmx_status (*PFNRMX_INPUT_DETACH_FLOW)(rmx_stream_id id, const rmx_input_flow * flow);` (scope `UE::RivermaxCore::Private`)
- L81 _typedef_ `typedef rmx_status (*PFNRMX_INPUT_SET_COMPLETION_MODERATION)(rmx_stream_id id, size_t min_count, size_t max_count, int timeout_usec);` (scope `UE::RivermaxCore::Private`)
- L82 _typedef_ `typedef void (*PFNRMX_INPUT_INIT_CHUNK_HANDLE)(rmx_input_chunk_handle * handle, rmx_stream_id id);` (scope `UE::RivermaxCore::Private`)
- L83 _typedef_ `typedef rmx_status (*PFNRMX_INPUT_GET_NEXT_CHUNK)(rmx_input_chunk_handle * handle);` (scope `UE::RivermaxCore::Private`)
- L84 _typedef_ `typedef const rmx_input_completion * (*PFNRMX_INPUT_GET_CHUNK_COMPLETION)(rmx_input_chunk_handle * handle);` (scope `UE::RivermaxCore::Private`)
- L85 _typedef_ `typedef const rmx_input_packet_info * (*PFNRMX_INPUT_GET_PACKET_INFO)(rmx_input_chunk_handle * handle, size_t packet_id);` (scope `UE::RivermaxCore::Private`)
- L86 _typedef_ `typedef void (*PFNRMX_OUTPUT_MEDIA_INIT)(rmx_output_media_stream_params * params);` (scope `UE::RivermaxCore::Private`)
- L87 _typedef_ `typedef void (*PFNRMX_OUTPUT_MEDIA_SET_SDP)(rmx_output_media_stream_params * params, const char * sdp);` (scope `UE::RivermaxCore::Private`)
- L88 _typedef_ `typedef void (*PFNRMX_OUTPUT_MEDIA_SET_IDX_IN_SDP)(rmx_output_media_stream_params * params, size_t media_block_idx);` (scope `UE::RivermaxCore::Private`)
- L89 _typedef_ `typedef void (*PFNRMX_OUTPUT_MEDIA_SET_PACKETS_PER_FRAME)(rmx_output_media_stream_params * params, size_t count);` (scope `UE::RivermaxCore::Private`)
- L90 _typedef_ `typedef void (*PFNRMX_OUTPUT_MEDIA_SET_SOURCE_PORTS)(rmx_output_media_stream_params * params, const uint16_t * ports, size_t count);` (scope `UE::RivermaxCore::Private`)
- L91 _typedef_ `typedef void (*PFNRMX_OUTPUT_MEDIA_SET_TX_ADAPTIVE_SCHEDULING_FACTOR)(rmx_output_media_stream_params * params, double tx_adaptive_scheduling_factor);` (scope `UE::RivermaxCore::Private`)
- L92 _typedef_ `typedef void (*PFNRMX_OUTPUT_MEDIA_SET_PCP)(rmx_output_media_stream_params * params, uint8_t pcp);` (scope `UE::RivermaxCore::Private`)
- L93 _typedef_ `typedef void (*PFNRMX_OUTPUT_MEDIA_SET_DSCP)(rmx_output_media_stream_params * params, uint8_t dscp);` (scope `UE::RivermaxCore::Private`)
- L94 _typedef_ `typedef void (*PFNRMX_OUTPUT_MEDIA_SET_ECN)(rmx_output_media_stream_params * params, uint8_t ecn);` (scope `UE::RivermaxCore::Private`)
- L95 _typedef_ `typedef void (*PFNRMX_OUTPUT_MEDIA_INIT_MEM_BLOCKS)(rmx_output_media_mem_block * mem_blocks, size_t count);` (scope `UE::RivermaxCore::Private`)
- L96 _typedef_ `typedef void (*PFNRMX_OUTPUT_MEDIA_SET_CHUNK_COUNT)(rmx_output_media_mem_block * mem_block, size_t count);` (scope `UE::RivermaxCore::Private`)
- L97 _typedef_ `typedef void (*PFNRMX_OUTPUT_MEDIA_SET_SUB_BLOCK_COUNT)(rmx_output_media_mem_block * mem_block, size_t count);` (scope `UE::RivermaxCore::Private`)
- L98 _typedef_ `typedef rmx_mem_region * (*PFNRMX_OUTPUT_MEDIA_GET_SUB_BLOCK)(rmx_output_media_mem_block * mem_block, size_t sub_block_id);` (scope `UE::RivermaxCore::Private`)
- L99 _typedef_ `typedef rmx_mem_multi_key_region * (*PFNRMX_OUTPUT_MEDIA_GET_DUP_SUB_BLOCK)(rmx_output_media_mem_block * mem_block, size_t sub_block_id);` (scope `UE::RivermaxCore::Private`)
- L100 _typedef_ `typedef void (*PFNRMX_OUTPUT_MEDIA_SET_PACKET_LAYOUT)(rmx_output_media_mem_block * mem_block, size_t sub_block_id, const uint16_t * packet_sizes);` (scope `UE::RivermaxCore::Private`)
- L101 _typedef_ `typedef void (*PFNRMX_OUTPUT_MEDIA_ASSIGN_MEM_BLOCKS)(rmx_output_media_stream_params * params, rmx_output_media_mem_block * mem_blocks, size_t count);` (scope `UE::RivermaxCore::Private`)
- L102 _typedef_ `typedef void (*PFNRMX_OUTPUT_MEDIA_SET_PACKETS_PER_CHUNK)(rmx_output_media_stream_params * params, size_t packets_per_chunk);` (scope `UE::RivermaxCore::Private`)
- L103 _typedef_ `typedef void (*PFNRMX_OUTPUT_MEDIA_SET_STRIDE_SIZE)(rmx_output_media_stream_params * params, size_t sub_block_id, const size_t stride_size);` (scope `UE::RivermaxCore::Private`)
- L104 _typedef_ `typedef rmx_status (*PFNRMX_OUTPUT_MEDIA_CREATE_STREAM)(rmx_output_media_stream_params * params, rmx_stream_id * id);` (scope `UE::RivermaxCore::Private`)
- L105 _typedef_ `typedef rmx_status (*PFNRMX_OUTPUT_MEDIA_DESTROY_STREAM)(rmx_stream_id id);` (scope `UE::RivermaxCore::Private`)
- L106 _typedef_ `typedef void (*PFNRMX_OUTPUT_MEDIA_INIT_CONTEXT)(rmx_output_media_context * context, rmx_stream_id id);` (scope `UE::RivermaxCore::Private`)
- L107 _typedef_ `typedef void (*PFNRMX_OUTPUT_MEDIA_SET_CONTEXT_BLOCK)(rmx_output_media_context * context, size_t id);` (scope `UE::RivermaxCore::Private`)
- L108 _typedef_ `typedef rmx_status (*PFNRMX_OUTPUT_MEDIA_GET_LOCAL_ADDRESS)(const rmx_output_media_context * context, struct sockaddr * address);` (scope `UE::RivermaxCore::Private`)
- L109 _typedef_ `typedef rmx_status (*PFNRMX_OUTPUT_MEDIA_GET_REMOTE_ADDRESS)(const rmx_output_media_context * context, struct sockaddr * address);` (scope `UE::RivermaxCore::Private`)
- L110 _typedef_ `typedef void (*PFNRMX_OUTPUT_MEDIA_INIT_CHUNK_HANDLE)(rmx_output_media_chunk_handle * handle, rmx_stream_id id);` (scope `UE::RivermaxCore::Private`)
- L111 _typedef_ `typedef void (*PFNRMX_OUTPUT_MEDIA_SET_CHUNK_PACKET_COUNT)(rmx_output_media_chunk_handle * handle, size_t packets_in_chunk);` (scope `UE::RivermaxCore::Private`)
- L112 _typedef_ `typedef rmx_status (*PFNRMX_OUTPUT_MEDIA_GET_NEXT_CHUNK)(rmx_output_media_chunk_handle * handle);` (scope `UE::RivermaxCore::Private`)
- L113 _typedef_ `typedef rmx_status (*PFNRMX_OUTPUT_MEDIA_MARK_CHUNK_FOR_TRACKING)(const rmx_output_media_chunk_handle * handle, uint64_t token);` (scope `UE::RivermaxCore::Private`)
- L114 _typedef_ `typedef rmx_status (*PFNRMX_OUTPUT_MEDIA_COMMIT_CHUNK)(const rmx_output_media_chunk_handle * handle, uint64_t time);` (scope `UE::RivermaxCore::Private`)
- L115 _typedef_ `typedef rmx_status (*PFNRMX_OUTPUT_MEDIA_POLL_FOR_COMPLETION)(const rmx_output_media_chunk_handle * handle);` (scope `UE::RivermaxCore::Private`)
- L116 _typedef_ `typedef const rmx_output_chunk_completion * (*PFNRMX_OUTPUT_MEDIA_GET_LAST_COMPLETION)(const rmx_output_media_chunk_handle * handle);` (scope `UE::RivermaxCore::Private`)
- L117 _typedef_ `typedef rmx_status (*PFNRMX_OUTPUT_MEDIA_CANCEL_UNSENT_CHUNKS)(const rmx_output_media_chunk_handle * handle);` (scope `UE::RivermaxCore::Private`)
- L118 _typedef_ `typedef rmx_status (*PFNRMX_OUTPUT_MEDIA_SKIP_CHUNKS)(const rmx_output_media_chunk_handle * handle, size_t chunks_count);` (scope `UE::RivermaxCore::Private`)
- L119 _typedef_ `typedef void (*PFNRMX_OUTPUT_GEN_INIT_STREAM)(rmx_output_gen_stream_params * params);` (scope `UE::RivermaxCore::Private`)
- L120 _typedef_ `typedef void (*PFNRMX_OUTPUT_GEN_SET_PACKETS_PER_CHUNK)(rmx_output_gen_stream_params * params, size_t max_packet_count);` (scope `UE::RivermaxCore::Private`)
- L121 _typedef_ `typedef void (*PFNRMX_OUTPUT_GEN_SET_LOCAL_ADDR)(rmx_output_gen_stream_params * params, const struct sockaddr * addr);` (scope `UE::RivermaxCore::Private`)
- L122 _typedef_ `typedef void (*PFNRMX_OUTPUT_GEN_SET_REMOTE_ADDR)(rmx_output_gen_stream_params * params, const struct sockaddr * addr);` (scope `UE::RivermaxCore::Private`)
- L123 _typedef_ `typedef void (*PFNRMX_OUTPUT_GEN_SET_MAX_SUB_BLOCKS)(rmx_output_gen_stream_params * params, size_t sub_blocks_per_packet);` (scope `UE::RivermaxCore::Private`)
- L124 _typedef_ `typedef void (*PFNRMX_OUTPUT_GEN_SET_PCP)(rmx_output_gen_stream_params * params, uint8_t pcp);` (scope `UE::RivermaxCore::Private`)
- L125 _typedef_ `typedef void (*PFNRMX_OUTPUT_GEN_SET_DSCP)(rmx_output_gen_stream_params * params, uint8_t dscp);` (scope `UE::RivermaxCore::Private`)
- L126 _typedef_ `typedef void (*PFNRMX_OUTPUT_GEN_SET_ECN)(rmx_output_gen_stream_params * params, uint8_t ecn);` (scope `UE::RivermaxCore::Private`)
- L127 _typedef_ `typedef void (*PFNRMX_OUTPUT_GEN_SET_RATE)(rmx_output_gen_stream_params * params, const rmx_output_gen_rate * rate);` (scope `UE::RivermaxCore::Private`)
- L128 _typedef_ `typedef rmx_status (*PFNRMX_OUTPUT_GEN_CREATE_STREAM)(rmx_output_gen_stream_params * params, rmx_stream_id * id);` (scope `UE::RivermaxCore::Private`)
- L129 _typedef_ `typedef rmx_status (*PFNRMX_OUTPUT_GEN_DESTROY_STREAM)(rmx_stream_id id);` (scope `UE::RivermaxCore::Private`)
- L130 _typedef_ `typedef void (*PFNRMX_OUTPUT_GEN_INIT_RATE)(rmx_output_gen_rate * rate, uint64_t bps);` (scope `UE::RivermaxCore::Private`)
- L131 _typedef_ `typedef void (*PFNRMX_OUTPUT_GEN_SET_RATE_MAX_BURST)(rmx_output_gen_rate * rate, size_t packet_count);` (scope `UE::RivermaxCore::Private`)
- L132 _typedef_ `typedef void (*PFNRMX_OUTPUT_GEN_SET_RATE_TYPICAL_PACKET_SIZE)(rmx_output_gen_rate * rate, size_t size_in_bytes);` (scope `UE::RivermaxCore::Private`)
- L133 _typedef_ `typedef rmx_status (*PFNRMX_OUTPUT_GEN_UPDATE_RATE)(rmx_stream_id id, const rmx_output_gen_rate * rate);` (scope `UE::RivermaxCore::Private`)
- L134 _typedef_ `typedef rmx_status (*PFNRMX_OUTPUT_GEN_UPDATE_REMOTE_ADDR)(rmx_stream_id id, const struct sockaddr * addr);` (scope `UE::RivermaxCore::Private`)
- L135 _typedef_ `typedef void (*PFNRMX_OUTPUT_GEN_INIT_CHUNK_HANDLE)(rmx_output_gen_chunk_handle * handle, rmx_stream_id id);` (scope `UE::RivermaxCore::Private`)
- L136 _typedef_ `typedef rmx_status (*PFNRMX_OUTPUT_GEN_GET_NEXT_CHUNK)(rmx_output_gen_chunk_handle * handle);` (scope `UE::RivermaxCore::Private`)
- L137 _typedef_ `typedef void (*PFNRMX_OUTPUT_GEN_SET_CHUNK_REMOTE_ADDR)(rmx_output_gen_chunk_handle * handle, const struct sockaddr * addr);` (scope `UE::RivermaxCore::Private`)
- L138 _typedef_ `typedef rmx_status (*PFNRMX_OUTPUT_GEN_APPEND_PACKET_TO_CHUNK)(rmx_output_gen_chunk_handle * handle, const rmx_mem_region * sub_blocks, size_t count);` (scope `UE::RivermaxCore::Private`)
- L139 _typedef_ `typedef rmx_status (*PFNRMX_OUTPUT_GEN_MARK_CHUNK_FOR_TRACKING)(const rmx_output_gen_chunk_handle * handle, uint64_t token);` (scope `UE::RivermaxCore::Private`)
- L140 _typedef_ `typedef rmx_status (*PFNRMX_OUTPUT_GEN_COMMIT_CHUNK)(rmx_output_gen_chunk_handle * handle, uint64_t time);` (scope `UE::RivermaxCore::Private`)
- L141 _typedef_ `typedef rmx_status (*PFNRMX_OUTPUT_GEN_POLL_FOR_COMPLETION)(const rmx_output_gen_chunk_handle * handle);` (scope `UE::RivermaxCore::Private`)
- L142 _typedef_ `typedef const rmx_output_chunk_completion * (*PFNRMX_OUTPUT_GEN_GET_LAST_COMPLETION)(const rmx_output_gen_chunk_handle * handle);` (scope `UE::RivermaxCore::Private`)
- L143 _typedef_ `typedef rmx_status (*PFNRMX_OUTPUT_GET_CHUNK_COUNT)(rmx_stream_id id, size_t * count);` (scope `UE::RivermaxCore::Private`)
- L144 _typedef_ `typedef rmx_status (*PFNRMX_OUTPUT_UPDATE_DSCP)(rmx_stream_id id, uint8_t dscp);` (scope `UE::RivermaxCore::Private`)
- L145 _typedef_ `typedef rmx_status (*PFNRMX_OUTPUT_UPDATE_ECN)(rmx_stream_id id, uint8_t ecn);` (scope `UE::RivermaxCore::Private`)
- L146 _typedef_ `typedef uint64_t (*PFNRMX_OUTPUT_GET_COMPLETION_TIMESTAMP)(const rmx_output_chunk_completion * completion);` (scope `UE::RivermaxCore::Private`)
- L286 _prototype_ `bool LoadLibraryFunctions(RIVERMAX_API_FUNCTION_LIST *FunctionList, void *LibraryHandle);` (scope `UE::RivermaxCore::Private`)

### `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxCore/Private/Streams/RivermaxInAncStream.h` (Private)


#### struct `UE::RivermaxCore::Private::FInputAncStreamBufferConfiguration`  
`struct FInputAncStreamBufferConfiguration`  
_L9-19_
- L11 _public member_ `size_t PayloadSize = 0;`
- L13 _public member_ `const uint16 PayloadExpectedSize = 1500;`
- L15 _public member_ `const uint8 DataBlockID = 0;`
- L17 _public member_ `rmx_mem_region* DataMemory = nullptr;`
- L18 _public member_ `size_t DataStride = 0;`

#### struct `UE::RivermaxCore::Private::FInputAncStreamStats`  
`struct FInputAncStreamStats`  
_L21-30_
- L23 _public member_ `uint64 PacketsReceived = 0;`
- L24 _public member_ `uint64 AncPacketsReceived = 0;`
- L25 _public member_ `uint64 BytesReceived = 0;`
- L26 _public member_ `uint64 ChecksumErrors = 0;`
- L27 _public member_ `uint64 ParsingErrors = 0;`
- L28 _public member_ `uint64 InvalidHeaderCount = 0;`
- L29 _public member_ `uint64 EmptyCompletionCount = 0;`

#### class `UE::RivermaxCore::Private::FRivermaxInputAncStream`  
`class FRivermaxInputAncStream : public FRivermaxInStream`  
_L33-70_
- inherits: `FRivermaxInStream`
- desc: Rivermax input stream for ST2110-40 ANC\.
- L36 _public prototype_ `FRivermaxInputAncStream();`
- L37 _public prototype_ `virtual ~FRivermaxInputAncStream();`
- L41 _protected prototype_ `virtual FString GetThreadName() const override;`
- L42 _protected prototype_ `virtual bool InitializeStreamParameters(FString& OutErrorMessage) override;`
- L43 _protected prototype_ `virtual void OnStreamCreated() override;`
- L44 _protected prototype_ `virtual size_t GetMaxCompletionChunkSize() const override;`
- L45 _protected prototype_ `virtual void DeallocateBuffers() override;`
- L46 _protected prototype_ `virtual void ParseChunks(const rmx_input_completion* Completion) override;`
- L47 _protected prototype_ `virtual void PrintStats() override;`
- L48 _protected prototype_ `virtual void LogStreamDescriptionOnCreation() const override;`
- L55 _private prototype_ `void ParseAncPacket(const uint8* DataPtr, size_t DataSize);` — Parses a single RFC8331 ANC RTP packet.
- L58 _private prototype_ `static uint8 DecodeDataCount(uint16 EncodedDataCount);` — Returns the lower 8 bits of a parity-encoded 10-bit Data_Count word (the actual UDW count).
- L63 _private prototype_ `static bool VerifyChecksum(uint16 DID, uint16 SDID, uint16 DataCount, const TArray<uint16>& UDWs, uint16 ReceivedChecksum);` — Verifies the 10 bit RFC8331 checksum against DID, SDID, DataCount, and UDWs.
- L65 _private prototype_ `void AllocateBuffers();`
- L68 _private member_ `FInputAncStreamBufferConfiguration BufferConfiguration;`
- L69 _private member_ `FInputAncStreamStats StreamStats;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace RivermaxCore` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::RivermaxCore`)

### `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxCore/Private/Streams/RivermaxInStream.h` (Private)


#### struct `UE::RivermaxCore::Private::FNetworkSettings`  
`struct FNetworkSettings`  
_L22-28_
- desc: Network settings for all input stream types. Video and ANC use identical fields.
- L24 _public member_ `sockaddr_in DeviceInterface;`
- L25 _public member_ `rmx_device_iface RMXDeviceInterface;`
- L26 _public member_ `rmx_ip_addr DeviceAddress;`
- L27 _public member_ `sockaddr_in DestinationAddress;`

#### class `UE::RivermaxCore::Private::FRivermaxInStream`  
`class FRivermaxInStream : public IRivermaxInputStream, public FRunnable`  
_L35-153_
- inherits: `IRivermaxInputStream,FRunnable`
- desc: Base class for all Rivermax input streams. Holds shared infrastructure: thread lifecycle, async init, network setup, reception loop, stream teardown. Subclasses implement stream-specific behavior via pure virtual hooks.
- L38 _public prototype_ `FRivermaxInStream();`
- L39 _public prototype_ `virtual ~FRivermaxInStream();`
- L43 _public prototype_ `virtual bool Initialize(const FRivermaxInputStreamOptions& InOptions, IRivermaxInputStreamListener& InListener) override;`
- L44 _public prototype_ `virtual void Uninitialize() override;`
- L47 _public prototype_ `void Process_AnyThread();`
- L50 _public prototype_ `virtual bool Init() override;`
- L51 _public prototype_ `virtual uint32 Run() override;`
- L52 _public prototype_ `virtual void Stop() override;`
- L53 _public prototype_ `virtual void Exit() override;`
- L58 _protected function_ `virtual void OnPreInitialize(IRivermaxCoreModule& RivermaxModule)` — Called before the async init task. Override for subclass-specific synchronous setup (e.g. cvar reads, HDS enable).
- L61 _protected function_ `virtual void OnPreThreadStop()` — Called after init-task wait, before the reception thread is stopped. Override for operations that must precede thread teardown (e.g. CUDA stream sync).
- L64 _protected function_ `virtual void OnPostThreadStop()` — Called after the reception thread is stopped, before DeallocateBuffers. Override for post-stop cleanup (e.g. disable dynamic header support).
- L67 _protected prototype_ `virtual FString GetThreadName() const = 0;` — Name used for the reception thread.
- L70 _protected function_ `virtual bool GetGPUDirectSupported() const` — Whether this stream instance supports GPUDirect. Queried after initialization completes.
- L73 _protected prototype_ `bool InitializeNetworkSettings(FNetworkSettings& OutSettings, FString& OutErrorMessage);` — Resolves interface/stream IP addresses and configures the NIC address on StreamParameters.
- L76 _protected prototype_ `virtual bool InitializeStreamParameters(FString& OutErrorMessage) = 0;` — Configures sub-block count, memory layout, and triggers buffer allocation.
- L79 _protected prototype_ `bool FinalizeStreamCreation(const FNetworkSettings& NetworkSettings, FString& OutErrorMessage);` — Creates the Rivermax stream, sets up completion moderation, chunk handle, and attaches flow.
- L82 _protected prototype_ `virtual void OnStreamCreated() = 0;` — Called immediately after rmx_input_create_stream succeeds. Override to retrieve strides from StreamParameters into the subclass buffer config.
- L85 _protected prototype_ `virtual size_t GetMaxCompletionChunkSize() const = 0;` — Returns the max chunk size passed to rmx_input_set_completion_moderation.
- L88 _protected function_ `virtual void ConfigureFlowParameters(rmx_input_flow& InFlow)` — Called before rmx_input_attach_flow. Override to set stream-specific flow parameters.
- L91 _protected prototype_ `virtual void DeallocateBuffers() = 0;` — Frees all allocated buffers. Called from Uninitialize after thread teardown.
- L94 _protected prototype_ `virtual void ParseChunks(const rmx_input_completion* Completion) = 0;` — Processes all packets in the completion chunk. Called each reception loop iteration.
- L97 _protected prototype_ `virtual void PrintStats() = 0;` — Logs stream-specific reception stats. Called every second by LogStats.
- L100 _protected prototype_ `virtual void LogStreamDescriptionOnCreation() const = 0;` — Logs a human-readable description of the stream after successful creation.
- L103 _private prototype_ `void LogStats();`
- L107 _protected member_ `FRivermaxInputStreamOptions Options;` — Options used for this stream, such has resolution, frame rate etc...
- L110 _protected member_ `IRivermaxInputStreamListener* Listener = nullptr;` — Listener to be notified of stream events
- L113 _protected member_ `rmx_stream_id StreamId = 0;` — Stream id given back by rivermax
- L116 _protected member_ `rmx_input_stream_params StreamParameters;` — Holding stream configuration data
- L119 _protected member_ `rmx_input_flow FlowAttribute;` — Flow attributes used at stream creation. Used to compare incoming data to our flow and detect mismatches
- L122 _protected member_ `uint32 FlowTag = 0;` — Flow identification. Used to verify if packets belong to expected stream
- L125 _protected member_ `ERivermaxStreamType RivermaxStreamType = ERivermaxStreamType::ST2110_20;` — Type of stream being received
- L128 _protected member_ `rmx_input_chunk_handle ChunkHandle;` — Chunk handle shared between Process_AnyThread (base) and ParseChunks (subclass).
- L131 _protected member_ `FRunnableThread* RivermaxThread = nullptr;` — Thread on which reception is handled
- L134 _protected member_ `std::atomic<bool> bIsActive = false;` — Whether reception thread should keep running
- L137 _protected member_ `std::atomic<bool> bIsShuttingDown = false;` — Whether stream is in the process of shutting down
- L140 _protected member_ `TFuture<void> InitTaskFuture;` — Future holding the async initialization task
- L143 _protected member_ `double LastLoggingTimestamp = 0.0;` — Last time stats were logged
- L146 _protected member_ `const RIVERMAX_API_FUNCTION_LIST* CachedAPI = nullptr;` — Cached pointer to the Rivermax API function list
- L149 _protected member_ `uint32 ConsecutiveChunkFailures = 0;` — Number of consecutive rmx_input_get_next_chunk failures. Resets on any success.
- L152 _protected member_ `static constexpr uint32 MaxConsecutiveChunkFailures = 1000;` — After this many consecutive chunk failures the stream calls OnStreamError and stops.

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace RivermaxCore` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::RivermaxCore`)

### `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxCore/Private/Streams/RivermaxInputVideoStream.h` (Private)


#### struct `UE::RivermaxCore::Private::FInputStreamBufferConfiguration`  
`struct FInputStreamBufferConfiguration`  
_L19-43_
- L21 _public member_ `size_t PayloadSize = 0;`
- L22 _public member_ `size_t HeaderSize = 0;`
- L23 _public member_ `uint16 PayloadExpectedSize = 1500;`
- L24 _public member_ `uint16 HeaderExpectedSize = 32;`
- L27 _public member_ `const uint8 HeaderBlockID = 0;` — Data Sub block ID
- L30 _public member_ `const uint8 DataBlockID = 1;` — Data Sub block ID
- L33 _public member_ `rmx_mem_region* DataMemory = nullptr;` — Memory region used to store incoming payloads
- L36 _public member_ `size_t DataStride = 0;` — Payload stride in bytes for input stream
- L39 _public member_ `rmx_mem_region* HeaderMemory = nullptr;` — Memory region used to store incoming headers
- L42 _public member_ `size_t HeaderStride = 0;` — Header stride in bytes for input stream

#### struct `UE::RivermaxCore::Private::FInputStreamStats`  
`struct FInputStreamStats`  
_L45-61_
- L47 _public member_ `uint64 InvalidHeadercount = 0;`
- L48 _public member_ `uint64 FramePacketLossCount = 0;`
- L49 _public member_ `uint64 TotalPacketLossCount = 0;`
- L50 _public member_ `uint64 BiggerFramesCount = 0;`
- L51 _public member_ `uint64 InvalidFramesCount = 0;`
- L52 _public member_ `uint64 BytesReceived = 0;`
- L53 _public member_ `uint64 FramesReceived = 0;`
- L54 _public member_ `uint64 ChunksReceived = 0;`
- L55 _public member_ `uint64 EndOfFrameReceived = 0;`
- L56 _public member_ `uint64 EmptyCompletionCount = 0;`
- L57 _public member_ `uint64 MinFirstPacketIntervalNS = TNumericLimits<uint64>::Max();`
- L58 _public member_ `uint64 MaxFirstPacketIntervalNS = TNumericLimits<uint64>::Min();`
- L59 _public member_ `uint64 FirstPacketIntervalAccumulatorNS = 0;`
- L60 _public member_ `uint64 FirstPacketIntervalStatsCount = 0;`

#### struct `UE::RivermaxCore::Private::FInputStreamData`  
`struct FInputStreamData`  
_L63-79_
- L65 _public member_ `uint64 LastSequenceNumber = 0;`
- L66 _public member_ `void* CurrentFrameVideoBuffer = nullptr;`
- L67 _public member_ `uint32 WritingOffset = 0;`
- L68 _public member_ `uint32 ReceivedSize = 0;`
- L69 _public member_ `uint32 ExpectedSize = 0;`
- L72 _public member_ `const void* DeviceWritePointerOne = nullptr;` — GPUDirect data handling. Rivermax uses a cyclic buffer so we might have part of the frame at the end of the first buffer and the rest on the second part.
- L73 _public member_ `const void* DeviceWritePointerTwo = nullptr;`
- L74 _public member_ `uint32 SizeToWriteOne = 0;`
- L75 _public member_ `uint32 SizeToWriteTwo = 0;`
- L78 _public member_ `TMap<IRivermaxSample::ESampleType, TSharedPtr<IRivermaxSample>> CurrentSamples;` — A map of samples for the current frame.

#### struct `UE::RivermaxCore::Private::FFrameDescriptionTrackingData`  
`struct FFrameDescriptionTrackingData`  
_L82-118_
- desc: Incoming frame description tracker. Used to detect variable SRD length across a frame for now but should be used to help auto detect incoming frame
- L87 _public prototype_ `void ResetSingleFrameTracking();` — Resets data related to current frame being tracked
- L90 _public prototype_ `void EvaluateNewRTP(const FRTPHeader& NewHeader);` — Look at new RTP and extract info to estimate frame description
- L93 _public prototype_ `bool HasDetectedValidResolution() const;` — Whether a valid resolution was detected during the last frame
- L98 _private prototype_ `void UpdateResolutionDetection(const FRTPHeader& NewHeader);` — Updates current resolution detection using new RTP header.
- L101 _private prototype_ `void UpdatePayloadSizeTracking(const FRTPHeader& NewHeader);` — Updates payload sizes encountered throughout a frame
- L105 _public member_ `TMap<uint32, uint32> PayloadSizeReceived;` — Used to track different payload sizes received. GPUDirect can't work if different payload sizes are received across the frame except the last one
- L108 _public member_ `int16 CommonPayloadSize = -1;` — Payload size used across a frame. -1 if multi SRD except last one are received.
- L111 _public member_ `FIntPoint DetectedResolution = FIntPoint::ZeroValue;` — Last resolution detected
- L114 _public member_ `ESamplingType ExpectedSamplingType = ESamplingType::RGB_10bit;` — Sampling type we are expecting as setup by the user. We could also auto detect it but some sampling types would collide so left manual for now.
- L117 _public member_ `bool bHasLoggedSamplingWarning = false;` — Used to log sampling type warning once until a good frame type is received

#### class `UE::RivermaxCore::Private::FRivermaxInputVideoStream`  
`class FRivermaxInputVideoStream : public FRivermaxInStream`  
_L120-258_
- inherits: `FRivermaxInStream`
- L123 _public prototype_ `FRivermaxInputVideoStream();`
- L124 _public prototype_ `virtual ~FRivermaxInputVideoStream();`
- L128 _protected prototype_ `virtual void OnPreInitialize(IRivermaxCoreModule& RivermaxModule) override;`
- L129 _protected prototype_ `virtual void OnPreThreadStop() override;`
- L130 _protected prototype_ `virtual void OnPostThreadStop() override;`
- L131 _protected prototype_ `virtual FString GetThreadName() const override;`
- L132 _protected prototype_ `virtual bool GetGPUDirectSupported() const override;`
- L133 _protected prototype_ `virtual bool InitializeStreamParameters(FString& OutErrorMessage) override;`
- L134 _protected prototype_ `virtual void OnStreamCreated() override;`
- L135 _protected prototype_ `virtual size_t GetMaxCompletionChunkSize() const override;`
- L136 _protected prototype_ `virtual void DeallocateBuffers() override;`
- L137 _protected prototype_ `virtual void ParseChunks(const rmx_input_completion* Completion) override;`
- L138 _protected prototype_ `virtual void PrintStats() override;`
- L139 _protected prototype_ `virtual void LogStreamDescriptionOnCreation() const override;`
- L145 _private prototype_ `void FrameReceptionState(const FRTPHeader& RTPHeader, const uint8* DataPtr, TSharedPtr<IRivermaxSample> InSample);` — Process reception state. i.e Extract RTP, tracks data received, etc...
- L148 _private prototype_ `void WaitForMarkerState(const FRTPHeader& RTPHeader);` — State where we just wait to receive an end of frame in RTP. Used to align for the first frame and when an error occurs during reception
- L154 _private prototype_ `void FrameErrorState(const FRTPHeader& RTPHeader);` — State we go in when an error was detected during the reception of a frame. Once the end of frame is received, will go back to frame reception state.
- L157 _private prototype_ `void ProcessSRD(const FRTPHeader& RTPHeader, const uint8* DataPtr);` — Process a SRD / packet by copying data associated to it into output buffer or tracking memory received for gpudirect
- L160 _private prototype_ `void ProcessLastSRD(const FRTPHeader& RTPHeader, const uint8* DataPtr, TSharedPtr<IRivermaxSample> InSample);` — Handles wrapping up of a frame when marker bit is detected (last SRD). Will notify listener of a new frame received
- L163 _private prototype_ `TSharedPtr<IRivermaxVideoSample> GetVideoSampleForReception(const FRTPHeader& RTPHeader);` — Requests a new frame from our listener. If it fails, it will fall in error state waiting for the next one
- L166 _private prototype_ `void AllocateBuffers();` — Allocates system or GPU memory buffer used for reception
- L169 _private prototype_ `bool AllocateGPUBuffers();` — Allocates gpu memory buffer used for reception and used by rivermax
- L172 _private prototype_ `void* GetMappedBuffer(const FBufferRHIRef& InBuffer);` — Gets the mapped gpu buffer for the incoming RHI buffer. Caching will occur if a new buffer is given
- L175 _private prototype_ `void UpdateFrameTracking(const FRTPHeader& NewRTPHeader);` — Updates frame information tracking using RTP header
- L180 _private member_ `FInputStreamBufferConfiguration BufferConfiguration;` — Memory configuration used for this stream.
- L183 _private member_ `bool bIsFirstPacketReceived = false;` — Used to know when the first packet of a frame has been received. Used mostly for visualization in insights
- L186 _private member_ `FInputStreamData StreamData;` — Information about the incoming frame we are receiving and general sequence numbering we are using for packet loss
- L189 _private member_ `FInputStreamStats StreamStats;` — Various stats kept for this stream
- L192 _private member_ `FVideoFormatInfo FormatInfo;` — Info about the video format that was selected such as pixel group, group size etc
- L195 _private member_ `bool bIsUsingGPUDirect = false;` — Whether gpudirect is used for this stream. Even though listener requests it, doesn't mean it will/can be used
- L198 _private member_ `bool bIsDynamicHeaderEnabled = false;` — Whether this stream has dynamic header data split enabled. Need to disable it on shutdown
- L201 _private member_ `int32 GPUDeviceIndex = 0;` — GPU device index to use when mapping to cuda. Will be needed for mgpu support
- L204 _private member_ `void* GPUAllocatedMemoryBaseAddress = nullptr;` — Allocated memory base address used when it's time to free
- L207 _private member_ `size_t GPUAllocatedMemorySize = 0;` — Total allocated gpu memory.
- L220 _private member_ `TMap<FRHIBuffer*, FCudaExternalBufferMapping> BufferGPUMemoryMap;` — Map between buffer we are writing to and their mapped address in cuda space
- L227 _private member_ `TSharedPtr<FCallbackPayload> CallbackPayload;`
- L230 _private member_ `void* GPUStream = nullptr;` — Cuda stream used for our operations
- L233 _private member_ `uint32 ExpectedPayloadSize = 1500;` — Payload size used to initialize rivermax stream and know differences between received SRD and config
- L251 _private member_ `EReceptionState State = EReceptionState::WaitingForMarker;` — Starts stream waiting for a marker to align ourselves with a full frame
- L254 _private member_ `FFrameDescriptionTrackingData FrameDescriptionTracking;` — Track incoming frame description to infer resolution, pixel type.
- L257 _private member_ `FIntPoint StreamResolution = FIntPoint::ZeroValue;` — Resolution being used by this stream. Can either be auto detected or enforced by owner

#### struct `UE::RivermaxCore::Private::FRivermaxInputVideoStream::FCudaExternalBufferMapping`  
`struct FCudaExternalBufferMapping`  
_L210-217_
- desc: Used to store all the required information for mapping GPU buffers
- L213 _public member_ `void* ExternalMemory = nullptr;` — External memory handle created from RHI buffer to be mapped with cuda.
- L216 _public member_ `void* MappedPtr = nullptr;` — Pointer (CUdeviceptr) to mapped external memory.

#### struct `UE::RivermaxCore::Private::FRivermaxInputVideoStream::FCallbackPayload`  
`struct FCallbackPayload`  
_L223-226_
- desc: Used to wait for a frame to be copied from gpu to gpu memory
- L225 _public member_ `std::atomic<bool> bIsWaitingForPendingCopy = false;`

#### enum `UE::RivermaxCore::Private::FRivermaxInputVideoStream::EReceptionState`  
`enum class EReceptionState`  
_L238-248_
- desc: States used to track reception of a frame
- L241 _public enumerator_ `WaitingForMarker` — Used for the first frame receptionand when an error happened while receiving to detect reception of the end of frame
- L244 _public enumerator_ `Receiving` — Used while receiving a frame and processing each SampleRowData
- L247 _public enumerator_ `FrameError` — Used when an error is detected during reception. Will wait for the end of frame detection before moving back to Receiving

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace RivermaxCore` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::RivermaxCore`)

### `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxCore/Private/Streams/RivermaxOutAncStream.h` (Private)


#### class `UE::RivermaxCore::Private::FRivermaxOutputStreamAnc`  
`class FRivermaxOutputStreamAnc : public FRivermaxOutStream`  
_L24-57_
- inherits: `FRivermaxOutStream`
- desc: Generic ANC.
- L27 _public prototype_ `FRivermaxOutputStreamAnc(const TArray<char>& SDPDescription);`
- L32 _public prototype_ `virtual bool PushFrame(TSharedPtr<IRivermaxOutputInfo> FrameInfo) override;`
- L33 _public prototype_ `virtual bool ReserveFrame(uint64 FrameCounter) const override;`
- L39 _protected prototype_ `virtual bool IsFrameAvailableToSend();`
- L40 _protected prototype_ `virtual bool InitializeStreamMemoryConfig();`
- L41 _protected prototype_ `virtual bool CopyFrameData(const TSharedPtr<FRivermaxOutputFrame>& SourceFrame, uint8* DestinationBase);`
- L42 _protected prototype_ `virtual bool SetupFrameManagement();`
- L43 _protected prototype_ `virtual void CleanupFrameManagement() override;`
- L44 _protected prototype_ `virtual void CompleteCurrentFrame(bool bReleaseFrame) override;`
- L45 _protected prototype_ `virtual void SetupRTPHeadersForChunk() override;`
- L46 _protected prototype_ `virtual void LogStreamDescriptionOnCreation() const override;`
- L47 _protected prototype_ `virtual TSharedPtr<FRivermaxOutputFrame> GetNextFrameToSend(bool bWait = false);`
- L53 _private member_ `TSharedPtr<FRivermaxOutputInfoAnc> FrameInfoToSend;` — All the information required for ANC data to be sent.
- L56 _private member_ `TSharedPtr<FRivermaxOutputFrame> NextFrameToSend;` — Next frame to send.

#### class `UE::RivermaxCore::Private::FRivermaxOutputStreamAncTimecode`  
`class FRivermaxOutputStreamAncTimecode : public FRivermaxOutputStreamAnc`  
_L60-69_
- inherits: `FRivermaxOutputStreamAnc`
- desc: Ancillary Timecode.
- L63 _public prototype_ `FRivermaxOutputStreamAncTimecode(const TArray<char>& SDPDescription);`
- L67 _public prototype_ `virtual bool PushFrame(TSharedPtr<IRivermaxOutputInfo> FrameInfo) override;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace RivermaxCore` (scope `UE`)
- L19 _namespace_ `namespace Private` (scope `UE::RivermaxCore`)

### `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxCore/Private/Streams/RivermaxOutStream.h` (Private)


#### struct `UE::RivermaxCore::Private::FRivermaxOutputStreamMemory`  
`struct FRivermaxOutputStreamMemory`  
_L30-113_
- desc: Struct holding configuration information with regards to stream memory and packetization
- L36 _public member_ `uint16 PayloadSize = 0;` — Size of each data payload packet that will be used. In case of single SRD this payload size will be aligned to equally divisible parts of image line width.
- L39 _public member_ `uint32 PixelGroupPerPacket = 0;` — Number of pixel group per packet
- L42 _public member_ `uint32 PixelsPerPacket = 0;` — Number of pixels per packet
- L45 _public member_ `uint32 PixelsPerFrame = 0;` — Number of pixels per frame
- L48 _public member_ `uint32 HeaderStrideSize = 20;` — Stride of RTP header data.
- L51 _public member_ `uint32 LinesInChunk = 4;` — Number of lines packed inside a chunk. Can be controlled with cvar
- L54 _public member_ `uint32 PacketsInLine = 0;` — Number of packets per line.
- L57 _public member_ `uint32 PacketsPerChunk = 0;` — Number of packets per chunk. Depends on LinesInChunk
- L60 _public member_ `uint32 FramesFieldPerMemoryBlock = 0;` — Number of frames per memory block.
- L63 _public member_ `uint32 PacketsPerFrame = 0;` — Number of packets per frame
- L66 _public member_ `uint32 PacketsPerMemoryBlock = 0;` — Number of packets per memory block
- L69 _public member_ `uint32 ChunksPerFrameField = 0;` — Number of chunks per frame
- L72 _public member_ `uint32 ChunksPerMemoryBlock = 0;` — Number of chunks per memory block
- L75 _public member_ `uint32 MemoryBlockCount = 0;` — Number of memory block
- L78 _public member_ `bool bUseIntermediateBuffer = false;` — Whether intermediate buffer is used and captured frame has to be copied over again.
- L81 _public member_ `uint32 FrameMemorySliceCount = 1;` — Number of slices we split frame data into when copying it into intermediate buffer
- L84 _public member_ `uint32 ChunkSpacingBetweenMemcopies = 1;` — Chunk committed between each memcopy of frame data. Helps respect timing.
- L87 _public member_ `TArray<rmx_output_media_mem_block> MemoryBlocks;` — Memory blocks allocated by Rivermax which is where packet data is stored.
- L93 _public member_ `uint8 HeaderBlockID = 0;` — Data Sub block ID. When Number of sub blocks is more than one (which is the case if dynamic header split is used), the first sub block is reserved for headers as per API docs.
- L96 _public member_ `uint8 DataBlockID = 1;` — Data Sub block ID. For ANC we don't need headers to be split, so DataBlockID will be set 0.
- L99 _public member_ `TArray<uint16_t> PayloadSizes;` — Array with each packet size
- L102 _public member_ `TArray<uint16_t> HeaderSizes;` — Array with each RTP header size
- L109 _public member_ `TArray<TSharedPtr<uint8>> RTPHeaders;` — Contains raw memory intialized to contain RTP headers for each packet per memory block. For example for Video this will store an array of FVideoRTPHeader's for each packet per memory block. The exact stride for each header is represented by HeaderStrideSize.
- L112 _public member_ `TArray<void*> BufferAddresses;` — Start addresses of each buffer in memblock

#### class `UE::RivermaxCore::Private::FRivermaxChunkCompletionTracker`  
`class FRivermaxChunkCompletionTracker`  
_L118-193_
- desc: A helper class keeping track of chunks marked for completion tracking.
- L121 _public function_ `FRivermaxChunkCompletionTracker(const RIVERMAX_API_FUNCTION_LIST* InCachedAPI, bool bInIsActive) : bIsActive(bInIsActive) , CachedAPI(InCachedAPI)`
- L139 _public prototype_ `void MarkChunkForTracking(const FString& ChunkId, const rmx_output_media_chunk_handle& ChunkMarkedForCompletion, uint64 NextScheduleTimeNanosec, uint64 DeltaTimePerChunkNs, uint32 ChunkNumber);` — Adds a chunk to the list of tracked chunks. ChunkId is a string used for human identification. ChunkMarkedForCompletion is Rivermax internal handle. NextScheduleTimeNanosec is the time when the first packet of the frame is supposed to be on the wire. DeltaTimePerChunk is predicted inter-chunk completion time based on frame rate and number of chunks (FrameRate/NumberOfChunks). In Nanosecs ChunkNumber is the sequential number of the chunk in the frame. Notes: If you mark chunk for tracking keep in mind that last chunk is completed at TRoffset from the next alignment point due to how it is setup in Rivermax. In ideal case scenario the last chunk will complete when the next alignment point starts, so if CVarRivermaxOutputCommitChunksOffsetPercent is used the chunk completion polling will eliminate the commit offset by waiting until the next alignment point.
- L147 _public prototype_ `void PollAndReportCompletionOfTrackedChunks();` — Processes all chunks that are marked for completion and outputs. Should be called at the end of the frame. Logs the time when chunks were completed (put on the wire) and delta between when the first packet is supposed to be on the wire and all packets in the first chunk were actually on the wire.
- L177 _private member_ `uint64 LastTimeStamp = 0;` — Timestamp of the last polled chunk. Used for making sure that chunks are completed in order.
- L180 _private member_ `bool bIsActive = false;` — Is chunk tracking active.
- L185 _private member_ `TArray<FTrackedChunkInfo> TrackedChunks;` — Chunk handle information to keep track of.
- L190 _private member_ `TSet<FString> TrackedChunksIds;` — This set is for fast look up if the chunk is already in the list based on the string ID provided when chunk is added for tracking.
- L192 _private member_ `const RIVERMAX_API_FUNCTION_LIST* CachedAPI;`

#### struct `UE::RivermaxCore::Private::FRivermaxChunkCompletionTracker::FTrackedChunkInfo`  
`struct FTrackedChunkInfo`  
_L152-174_
- desc: Struct containing all the required information to track the chunk and make sure it is completed on time.
- L155 _public member_ `FString HumanReadableString;` — String that is used to create a unique token for tracking in rivermax API. Also used for logging. Must be unique.
- L158 _public member_ `uint64 GeneratedToken;` — Token used for tracking the chunk. Generated from the provided string.
- L161 _public member_ `rmx_output_media_chunk_handle ChunkHandle;` — Chunk handle to keep track of.
- L167 _public member_ `uint64 FrameScheduledTimeNs;` — The scheduled time for the first packet of the frame (Alignment point + TRoffset + user specified offset if set). In Nanoseconds.
- L173 _public member_ `uint64 ExpectedCompletionTime;` — Time in nanoseconds when this chunk is expected to be completed. This measurement based on calculated interchunk timing and isn't precise, therefore has a small margin added to it.

#### struct `UE::RivermaxCore::Private::FRivermaxOutputStreamStats`  
`struct FRivermaxOutputStreamStats`  
_L195-223_
- L198 _public member_ `uint32 TotalChunkRetries = 0;` — Chunk retries that were required since stream was started
- L201 _public member_ `uint32 LastFrameChunkRetries = 0;` — Chunk retries that happened during last frame
- L204 _public member_ `uint32 ChunkSkippingRetries = 0;` — Chunk skipping retries that happened since stream was started
- L207 _public member_ `uint32 TotalPacketSent = 0;` — Total packets that have been sent since stream was started
- L210 _public member_ `uint32 CommitRetries = 0;` — Number of retries that were required when committing and queue was full since stream was started
- L213 _public member_ `uint32 CommitImmediate = 0;` — Immediate commits that were done because we got there too close to scheduling time
- L216 _public member_ `uint64 FramesSentCounter = 0;` — Number of frames that were sent since stream was started
- L219 _public member_ `uint64 TimingIssueCount = 0;` — Frames that had timing issues since stream was started
- L222 _public member_ `TSharedPtr<FRivermaxChunkCompletionTracker> ChunkCompletionTracker = nullptr;` — A helper that manages completion tracking of Rivermax chunks. Enabled with a CVarRivermaxOutputTrackChunkCompletion.

#### struct `UE::RivermaxCore::Private::FRivermaxOutputStreamData`  
`struct FRivermaxOutputStreamData`  
_L225-262_
- L228 _public member_ `rmx_output_media_chunk_handle ChunkHandle;` — Handle used to retrieve chunks associated with output stream
- L231 _public member_ `uint32 SequenceNumber = 0;` — Current sequence number being done
- L234 _public member_ `uint32 SynchronizationSource = FRawRTPHeader::VideoSynchronizationSource;` — The SynchronizationSource (SSRC) field in the RTP header is a 32-bit identifier used to group RTP packets into a single stream.
- L237 _public member_ `double FrameFieldTimeIntervalNs = 0.0;` — Time interval between frames in nanoseconds.
- L240 _public member_ `uint64 NextAlignmentPointNanosec = 0;` — Next alignment point based on PTP standard
- L243 _public member_ `uint64 NextScheduleTimeNanosec = 0;` — Next schedule time using 2110 gapped model timing and controllable offset
- L246 _public member_ `bool bHasValidNextFrameNumber = false;` — Whether next alignment frame number is deemed valid or not to detect missed frames.
- L249 _public member_ `uint64 NextAlignmentPointFrameNumber = 0;` — Next alignment point frame number treated to detect missed frames
- L252 _public member_ `uint64 LastAlignmentPointFrameNumber = 0;` — Last alignment point frame number we have processed
- L255 _public member_ `uint64 LastSendStartTimeNanoSec = 0;` — Timestamp at which we started commiting a frame
- L258 _public member_ `uint64 LastSleepTimeNanoSec = 0;` — Keeping track of how much time was slept last round.
- L261 _public member_ `uint64 DeltaTimePerChunkNs = 0;` — How long is it expected to transmit all packets in the chunk.

#### struct `UE::RivermaxCore::Private::FOutputStreamCachedCVars`  
`struct FOutputStreamCachedCVars`  
_L265-297_
- desc: Struct holding various cached cvar values that can't be changed once stream has been created and to avoid calling anythread getters continuously
- L268 _public member_ `bool bEnableCommitTimeProtection = true;` — Whether timing protection is active and next frame interval is skipped if it happens
- L271 _public member_ `uint64 SkipSchedulingTimeNanosec = 0;` — Time padding from scheduling time required to avoid skipping it
- L278 _public member_ `uint64 ForceCommitImmediateTimeNanosec = 0;` — Time from scheduling required to not commit it immediately Rivermax sdk will throw an error if time is in the past when it gets to actually comitting it.
- L281 _public member_ `bool bUseSingleMemblock = true;` — Tentative optimization recommended for SDK where a single big memblock is allocated. When false, a memblock per frame is configured.
- L284 _public member_ `bool bEnableTimeCriticalThread = true;` — Whether to bump output thread priority to time critical
- L287 _public member_ `bool bShowOutputStats = false;` — Whether to show output stats at regular interval in logs
- L290 _public member_ `float ShowOutputStatsIntervalSeconds = 1.0f;` — Interval in seconds at which to display output stats
- L293 _public member_ `bool bPrefillRTPHeaders = true;` — Whether to prefill RTP header memory with known data at initialization time instead of during sending
- L296 _public member_ `bool bTrackChunkCompletion = false;` — Whether the stream should track and report when certain chunks (such as first chunk) were put on the wire.

#### class `UE::RivermaxCore::Private::FRivermaxOutStream`  
`class FRivermaxOutStream : public UE::RivermaxCore::IRivermaxOutputStream, public FRunnable`  
_L300-538_
- inherits: `UE::RivermaxCore::IRivermaxOutputStream,FRunnable`
- desc: The base class for all Rivermax stream types.
- L303 _public prototype_ `FRivermaxOutStream(const TArray<char>& SDPDescription);`
- L304 _public prototype_ `virtual ~FRivermaxOutStream();`
- L309 _public prototype_ `virtual bool Initialize(const FRivermaxOutputOptions& Options, IRivermaxOutputStreamListener& InListener) override;`
- L310 _public prototype_ `virtual void Uninitialize() override;`
- L312 _public prototype_ `virtual bool IsGPUDirectSupported() const override;`
- L313 _public prototype_ `virtual bool ReserveFrame(uint64 FrameCounter) const override;`
- L314 _public prototype_ `virtual void GetLastPresentedFrame(FPresentedFrameInfo& OutFrameInfo) const override;`
- L317 _public prototype_ `virtual void Process_AnyThread();`
- L320 _public prototype_ `virtual bool Init() override;`
- L321 _public prototype_ `virtual uint32 Run() override;`
- L322 _public prototype_ `virtual void Stop() override;`
- L323 _public prototype_ `virtual void Exit() override;`
- L329 _protected prototype_ `virtual bool InitializeStreamMemoryConfig() = 0;` — Configures chunks, packetizing, memory blocks of the stream
- L332 _protected prototype_ `void InitializeNextFrame(const TSharedPtr<FRivermaxOutputFrame>& NextFrame);` — Resets NextFrame to be ready to send it out
- L335 _protected prototype_ `virtual bool IsFrameAvailableToSend() = 0;` — Indicates that there is some data that is ready to be sent
- L338 _protected prototype_ `virtual void GetNextChunk();` — Query rivermax library for the next chunk to work with
- L341 _protected prototype_ `virtual void SetupRTPHeadersForChunk() = 0;` — Fills RTP header for all packets to be sent for this chunk
- L344 _protected prototype_ `virtual bool CopyFrameData(const TSharedPtr<FRivermaxOutputFrame>& SourceFrame, uint8* DestinationBase) = 0;` — Copies part of frame memory in next memblock's chunk to be sent out
- L347 _protected prototype_ `virtual void CommitNextChunks();` — Commits chunk to rivermax so they are scheduled to be sent
- L350 _protected prototype_ `virtual void PrepareNextFrame();` — Fetches next frame to send and prepares it for sending
- L353 _protected prototype_ `virtual TSharedPtr<FRivermaxOutputFrame> GetNextFrameToSend(bool bWait = false) = 0;` — Get next frame to be sent, stream type agnostic. Should wait until the frame is available if bWait.
- L356 _protected prototype_ `virtual void PrepareNextFrame_FrameCreation();` — Returns next frame to send for frame creation alignment
- L359 _protected prototype_ `virtual void PrepareNextFrame_AlignmentPoint();` — Returns next frame to send for alignement point method. Can return nullptr
- L362 _protected prototype_ `virtual bool SetupFrameManagement() = 0;` — Sets up frame management taking care of allocation, special cuda handling, etc...
- L365 _protected prototype_ `virtual void CleanupFrameManagement();` — Clean up frames
- L368 _protected prototype_ `virtual void DestroyStream();` — Destroys rivermax stream. Will wait until it's ready to be destroyed
- L371 _protected prototype_ `virtual void CompleteCurrentFrame(bool bReleaseFrame);` — When a frame has been sent (after frame interval), we update last presented frame tracking and optionally release it in the presentation queue
- L374 _protected prototype_ `virtual bool WaitForNextRound();` — Waits for the next point in time to send out a new frame. Returns true if it exited earlier with the next frame ready to be processed
- L377 _protected prototype_ `virtual void PreprocessNextFrame();` — Uses time before next frame interval to copy data from next ready frame to intermediate buffer
- L380 _protected prototype_ `virtual void InitializeStreamTimingSettings();` — Initializes timing setup for this stream. TRO, frame interval etc...
- L383 _protected prototype_ `virtual const FFrameRate& GetFrameRate() const;` — Get frame rate according to the SDP file.
- L388 _protected prototype_ `virtual const FString& GetStreamAddress() const;` — Get stream address according to the SDP file.
- L391 _protected prototype_ `virtual const FString& GetInterfaceAddress() const;` — Get Interface Address (Physical Port address).
- L394 _protected prototype_ `virtual uint32 GetPort() const;` — Get Port Number according to the SDP file.
- L397 _protected prototype_ `virtual uint64 GetStreamIndexSDP() const;` — Get Stream Index as it is ordered in the SDP file.
- L400 _protected prototype_ `virtual void LogStreamDescriptionOnCreation() const = 0;` — When stream creation is successful this should log all relevant information.
- L405 _protected prototype_ `void CalculateNextScheduleTime_AlignementPoints(uint64 CurrentClockTimeNanosec, uint64 CurrentFrameNumber);` — Calculate next frame scheduling time for alignment points mode
- L408 _protected prototype_ `void CalculateNextScheduleTime_FrameCreation(uint64 CurrentClockTimeNanosec, uint64 CurrentFrameNumber);` — Calculate next frame scheduling time for frame creation mode
- L411 _protected prototype_ `bool IsChunkOnTime() const;` — Validates timing on every commit to see if we are respecting alignment
- L414 _protected prototype_ `bool IsChunkOnTime_FrameCreation() const;` — Validates timing for frame creation alignment which always returns true.
- L419 _protected prototype_ `bool IsChunkOnTime_AlignmentPoints() const;` — Validates timing to make sure chunk to be committed are on time. Once a chunk is late, timings are at risk and next frame will be skipped
- L422 _protected prototype_ `void ShowStats();` — If enabled, print stats related to this stream
- L425 _protected prototype_ `void OnPreFrameReadyToBeSent();` — Used to notify the listener that a frame is ready to be enqueued for transmission
- L428 _protected prototype_ `void OnFrameReadyToBeSent();` — Used to detect when a frame is now ready to be sent
- L431 _protected prototype_ `void OnFrameReadyToBeUsed();` — Used to know when a frame is ready to be used and receive new data
- L434 _protected prototype_ `void OnFrameManagerCriticalError();` — Used to detect when the frame manager has caught a critical error
- L437 _protected prototype_ `void CacheCVarValues();` — Used to cache cvars at initialization
- L440 _protected prototype_ `void OnMemoryChunksCopied(const TSharedPtr<FBaseDataCopySideCar>& Sidecar);` — Called back when copy request was completed by allocator
- L443 _protected prototype_ `void OnCVarRandomDelayChanged(IConsoleVariable* Var);` — Called when delay request cvar has been changed
- L446 _protected prototype_ `void OnCVarTriggerTimingIssueChanged(IConsoleVariable* Var);` — Called when Trigger Timing issue cvar value has been changed
- L449 _protected prototype_ `void CalculateFrameTimestamp();` — Update frame's timestamp to be used when setting every RTP headers
- L452 _protected prototype_ `void SkipChunks(uint64 ChunkCount);` — Tells Rivermax to skip a certain number of chunks in memory. Can be zero to just reset internals
- L455 _protected prototype_ `void SendFrame();` — Go through all chunks of current frame and commit them to Rivermax to send them at the next desired time
- L460 _protected member_ `FRivermaxOutputStreamMemory StreamMemory;` — Rivermax memory configuration. i.e. memblock, chunks
- L463 _protected member_ `FRivermaxOutputOptions Options;` — Options related to this stream. i.e resolution, frame rate, etc...
- L466 _protected member_ `FRivermaxOutputStreamStats Stats;` — Various stats collected by this stream
- L469 _protected member_ `FRivermaxOutputStreamData StreamData;` — State of various piece for this stream. Alignment points, schedule number, etc...
- L472 _protected member_ `rmx_stream_id StreamId = 0;` — Stream id returned by rmax library
- L475 _protected member_ `TSharedPtr<FRivermaxOutputFrame> CurrentFrame;` — Current frame being sent
- L481 _protected member_ `mutable TMap<uint64, TSharedPtr<FRivermaxOutputFrame>> ReservedFrames;` — Frames reserved when Media Capture texture is about to be converted into Buffer to be sent. Key is frame counter
- L484 _protected member_ `TUniquePtr<FRunnableThread> RivermaxThread;` — Thread scheduling frame output
- L487 _protected member_ `std::atomic<bool> bIsActive;` — Whether stream is active or not
- L490 _protected member_ `FEventRef FrameReadyToSendSignal = FEventRef(EEventMode::AutoReset);` — Event used to let scheduler that a frame is ready to be sent
- L493 _protected member_ `FEventRef FrameAvailableSignal = FEventRef(EEventMode::AutoReset);` — Event used to unblock frame reservation as soon as one is free
- L496 _protected member_ `IRivermaxOutputStreamListener* Listener = nullptr;` — Listener for this stream events
- L499 _protected member_ `ERivermaxStreamType StreamType = ERivermaxStreamType::ST2110_20;` — Type of stream created.
- L502 _protected member_ `uint64 TransmitOffsetNanosec = 0;` — TRoffset time calculated based on ST2110 - 21 Gapped(for now) method. This is added to next alignment point
- L505 _protected member_ `double LastStatsShownTimestamp = 0.0;` — Timestamp at which we logged stats
- L508 _protected member_ `bool bUseGPUDirect = false;` — Whether stream is using gpudirect to host memory consumed by Rivermax
- L511 _protected member_ `IRivermaxCoreModule* RivermaxModule = nullptr;` — Our own module pointer kept for ease of use
- L515 _protected member_ `FGuid MonitoringGuid;` — TODO: There must be a better place for this.
- L518 _protected member_ `FOutputStreamCachedCVars CachedCVars;` — Cached cvar values
- L521 _protected member_ `const RIVERMAX_API_FUNCTION_LIST* CachedAPI = nullptr;` — Pointer to the rivermax API to avoid virtual calls in a hot loop.
- L524 _protected member_ `bool bTriggerRandomDelay = false;` — Whether to trigger a delay in the output thread loop next time it ticks
- L527 _protected member_ `mutable FCriticalSection PresentedFrameCS;` — Critical section to access data of last presented frame
- L530 _protected member_ `FPresentedFrameInfo LastPresentedFrame;` — Info of last presented frame
- L533 _protected member_ `TArray<char> SDPDescription;` — An actual string of the SDP file.
- L537 _private member_ `double ScheduledTimeForArtificialTimingIssue = 0.0;` — Used for debugging Rivermax streams when frame needs to be skipped after a certain period.

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace RivermaxCore` (scope `UE`)
- L19 _namespace_ `namespace Private` (scope `UE::RivermaxCore`)

### `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxCore/Private/Streams/RivermaxOutVideoStream.h` (Private)


#### class `UE::RivermaxCore::Private::FRivermaxOutputStreamVideo`  
`class FRivermaxOutputStreamVideo : public FRivermaxOutStream`  
_L26-70_
- inherits: `FRivermaxOutStream`
- L29 _public prototype_ `FRivermaxOutputStreamVideo(const TArray<char>& SDPDescription);`
- L34 _public prototype_ `virtual bool PushFrame(TSharedPtr<IRivermaxOutputInfo> FrameInfo) override;`
- L35 _public prototype_ `virtual bool ReserveFrame(uint64 FrameIdentifier) const override;`
- L41 _protected prototype_ `virtual bool IsFrameAvailableToSend();`
- L42 _protected prototype_ `virtual bool InitializeStreamMemoryConfig();`
- L43 _protected prototype_ `virtual bool CopyFrameData(const TSharedPtr<FRivermaxOutputFrame>& SourceFrame, uint8* DestinationBase);`
- L44 _protected prototype_ `virtual bool SetupFrameManagement();`
- L45 _protected prototype_ `virtual void SetupRTPHeadersForChunk() override;`
- L46 _protected prototype_ `virtual void CleanupFrameManagement() override;`
- L47 _protected prototype_ `virtual void CompleteCurrentFrame(bool bReleaseFrame) override;`
- L48 _protected prototype_ `virtual void LogStreamDescriptionOnCreation() const override;`
- L49 _protected prototype_ `virtual TSharedPtr<FRivermaxOutputFrame> GetNextFrameToSend(bool bWait = false);`
- L55 _private prototype_ `SIZE_T GetRowSizeInBytes() const;` — Get row stride for the current stream configuration
- L60 _private member_ `TUniquePtr<FFrameManager> FrameManager;` — Manages allocation and memory manipulation of video frames
- L63 _private member_ `TUniquePtr<FBaseFrameAllocator> Allocator;` — Manages allocation of memory for rivermax memblocks
- L66 _private member_ `FVideoFormatInfo FormatInfo;` — Format info for the active stream

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace RivermaxCore` (scope `UE`)
- L19 _namespace_ `namespace Private` (scope `UE::RivermaxCore`)

### `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxCore/Public/IRivermaxBoundaryMonitor.h` (Public)


#### class `UE::RivermaxCore::IRivermaxBoundaryMonitor`  
`class IRivermaxBoundaryMonitor`  
_L17-30_
- desc: Frame boundary monitor interface used to add trace bookmarks for monitored frame rates. Boundaries are calculated using ST-2059 formula.
- L20 _public prototype_ `virtual ~IRivermaxBoundaryMonitor() = default;`
- L23 _public prototype_ `virtual void EnableMonitoring(bool bEnable) = 0;` — Global enable / disable of monitoring thread
- L26 _public prototype_ `virtual FGuid StartMonitoring(const FFrameRate& FrameRate) = 0;` — Asks to start monitoring a particular frame rate
- L29 _public prototype_ `virtual void StopMonitoring(const FGuid& Requester, const FFrameRate& FrameRate) = 0;` — Removes a listener for a particular frame rate

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace RivermaxCore` (scope `UE`)

### `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxCore/Public/IRivermaxCoreModule.h` (Public)


#### class `IRivermaxCoreModule`  
`class IRivermaxCoreModule : public IModuleInterface`  
_L24-54_
- inherits: `IModuleInterface`
- desc: Core module for Rivermax access from the engine. Users can create different stream types that are exposed to get data flow ongoing.
- L27 _public function_ `static inline IRivermaxCoreModule& Get()`
- L32 _public function_ `static inline bool IsAvailable()`
- L38 _public function_ `virtual TUniquePtr<UE::RivermaxCore::IRivermaxInputStream> CreateInputStream()` — `UE_DEPRECATED(5.6, "Please use CreateInputStream that takes stream type as a parameter.")`
- L41 _public function_ `virtual TUniquePtr<UE::RivermaxCore::IRivermaxOutputStream> CreateOutputStream()` — `UE_DEPRECATED(5.6, "Please use CreateOutputStream that takes stream type as a parameter.")`
- L44 _public prototype_ `virtual TUniquePtr<UE::RivermaxCore::IRivermaxInputStream> CreateInputStream(UE::RivermaxCore::ERivermaxStreamType, const TArray<char>& InSDPDescription) = 0;` — Create input stream managing receiving data from rivermax
- L47 _public prototype_ `virtual TUniquePtr<UE::RivermaxCore::IRivermaxOutputStream> CreateOutputStream(UE::RivermaxCore::ERivermaxStreamType, const TArray<char>& InSDPDescription) = 0;` — Create output stream managing sending data to rivermax
- L50 _public prototype_ `virtual TSharedPtr<UE::RivermaxCore::IRivermaxManager> GetRivermaxManager() = 0;` — Returns Rivermax manager singleton to query for stats, status, etc...
- L53 _public prototype_ `virtual UE::RivermaxCore::IRivermaxBoundaryMonitor& GetRivermaxBoundaryMonitor() = 0;` — Returns frame boundary monitor

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace RivermaxCore` (scope `UE`)

### `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxCore/Public/IRivermaxInputStream.h` (Public)


#### struct `UE::RivermaxCore::FRivermaxInputInitializationResult`  
`struct FRivermaxInputInitializationResult`  
_L15-22_
- L18 _public member_ `bool bHasSucceed = false;` — Whether initialization suceeded
- L21 _public member_ `bool bIsGPUDirectSupported = false;` — Whether gpudirect can be used, if requested in the first place

#### struct `UE::RivermaxCore::FRivermaxInputVideoFrameDescriptor`  
`struct FRivermaxInputVideoFrameDescriptor`  
_L24-43_
- L27 _public member_ `uint32 Height = 0;` — Height of the received frame
- L30 _public member_ `uint32 Width = 0;` — Width of the received frame
- L33 _public member_ `uint32 VideoBufferSize = 0;` — Total size of the video frame
- L36 _public member_ `uint32 Timestamp = 0;` — Timestamp, in media clock realm, marked by the sender
- L39 _public member_ `uint32 FrameNumber = 0;` — Frame number derived from timestamp and frame rate
- L42 _public member_ `ESamplingType PixelFormat = ESamplingType::RGB_10bit;` — Pixel format of the frame

#### struct `UE::RivermaxCore::FRivermaxInputVideoFormatChangedInfo`  
`struct FRivermaxInputVideoFormatChangedInfo`  
_L45-55_
- L48 _public member_ `uint32 Height = 0;` — Detected height in pixel of the video stream
- L51 _public member_ `uint32 Width = 0;` — Detected width in pixel of the video stream
- L54 _public member_ `ESamplingType PixelFormat = ESamplingType::RGB_10bit;` — Detected sampling type of the video stream

#### struct `UE::RivermaxCore::FRivermaxInputVideoFrameRequest`  
`struct FRivermaxInputVideoFrameRequest`  
_L57-64_
- L60 _public member_ `uint8* VideoBuffer = nullptr;` — Buffer pointer in RAM where to write incoming frame
- L63 _public member_ `FRHIBuffer* GPUBuffer = nullptr;` — Buffer pointer in GPU to be mapped to cuda and where to write incoming frame

#### struct `UE::RivermaxCore::FRivermaxInputVideoFrameReception`  
`struct FRivermaxInputVideoFrameReception`  
_L66-69_
- L68 _public member_ `uint8* VideoBuffer = nullptr;`

#### class `UE::RivermaxCore::IRivermaxSample`  
`class IRivermaxSample`  
_L74-150_
- desc: All types of streams write into corresponding sample types. All sample types should inherit from this class so it can be correctly cast and identified.
- L77 _public function_ `virtual ~IRivermaxSample()`
- L126 _public function_ `virtual void SetReceptionState(ESampleState State)` — Sets the state of the reception for this sample.
- L135 _public function_ `virtual ESampleState GetReceptionState()` — Gets reception state of this sample.
- L143 _protected member_ `std::atomic<ESampleState> SampleState = ESampleState::ReadyForReception;` — State of this sample.
- L146 _protected member_ `std::atomic<ESampleType> SampleType = ESampleType::Video;` — Type of the sample.
- L149 _protected member_ `mutable FCriticalSection StateChangeCriticalSecion;` — Critical section used when manipulating the received/skipped/rendered and other states in this or the inheriting classes.

#### enum `UE::RivermaxCore::IRivermaxSample::ESampleState`  
`enum class ESampleState : uint8`  
_L81-98_
- L84 _public enumerator_ `Idle` — Sample hasn't started receiving and is awaiting to be used. In this state it contains the data previously written into it.
- L87 _public enumerator_ `ReadyForReception` — Sample is ready to be written into.
- L90 _public enumerator_ `Received` — Sample has received the data. And ready to be used for rendering.
- L93 _public enumerator_ `ReceptionError` — Error receiving sample. Used at the same point as Received state.
- L97 _public enumerator_ `Rendering` — After sample is received and is ready to be rendered and until the GPU is done with the sample this is the state the sample is in. Currently only used for debugging purposes.

#### enum `UE::RivermaxCore::IRivermaxSample::ESampleType`  
`enum class ESampleType : uint8`  
_L103-119_
- desc: Enum that identifies the type of this sample such as Video or Audio so that it can be handled accordingly.
- L106 _public enumerator_ `Video` — 2110-20
- L109 _public enumerator_ `Audio` — 2110-30
- L112 _public enumerator_ `Anc` — 2110-40
- L115 _public enumerator_ `KeyAndFill` — 2110-20 Sub raster.
- L118 _public enumerator_ `MAX` — Stub for itteration.

#### class `UE::RivermaxCore::IRivermaxVideoSample`  
`class IRivermaxVideoSample : public IRivermaxSample`  
_L155-164_
- inherits: `IRivermaxSample`
- desc: 2110-20 sample type interface.
- L160 _public prototype_ `virtual TRefCountPtr<FRDGPooledBuffer> GetGPUBuffer() const = 0;` — Returns RDG allocated buffer
- L163 _public prototype_ `virtual uint8* GetVideoBufferRawPtr(uint32 VideoBufferSize) = 0;` — Returns a pointer to the CPU accessible buffer for writing streams into.

#### class `UE::RivermaxCore::IRivermaxAncSample`  
`class IRivermaxAncSample : public IRivermaxSample`  
_L169-176_
- inherits: `IRivermaxSample`
- desc: 2110-40 ANC sample type interface.
- L172 _public prototype_ `virtual void SetAncData(uint16 DID, uint16 SDID, const TArray<uint16>& UDWs) = 0;`
- L173 _public prototype_ `virtual uint16 GetDID() const = 0;`
- L174 _public prototype_ `virtual uint16 GetSDID() const = 0;`
- L175 _public prototype_ `virtual const TArray<uint16>& GetUserDataWords() const = 0;`

#### struct `UE::RivermaxCore::FRivermaxInputAncFrameDescriptor`  
`struct FRivermaxInputAncFrameDescriptor`  
_L179-187_
- desc: Descriptor filled during ANC packet reception, passed to OnAncFrameRequested.
- L181 _public member_ `uint32 Timestamp = 0;`
- L182 _public member_ `uint32 FrameNumber = 0;`
- L183 _public member_ `uint16 DID = 0;`
- L184 _public member_ `uint16 SDID = 0;`
- L185 _public member_ `uint16 LineNumber = 0;`
- L186 _public member_ `uint16 HorizontalOffset = 0;`

#### class `UE::RivermaxCore::IRivermaxInputStreamListener`  
`class IRivermaxInputStreamListener`  
_L192-228_
- desc: A type of interface that is able to provide samples for data to be written into and react to stream events such as completion of the reception.
- L196 _public prototype_ `virtual void OnInitializationCompleted(const FRivermaxInputInitializationResult& Result) = 0;` — Initialization completion callback with result
- L199 _public prototype_ `virtual TSharedPtr<IRivermaxVideoSample> OnVideoFrameRequested(const FRivermaxInputVideoFrameDescriptor& FrameInfo) = 0;` — Called when stream is ready to fill the next frame. Returns true if a frame was successfully requested
- L202 _public prototype_ `virtual void OnVideoFrameReceived(TSharedPtr<IRivermaxVideoSample> InReceivedVideoFrame) = 0;` — Called when a frame has been received
- L205 _public function_ `virtual void OnVideoFrameReceptionError(TSharedPtr<IRivermaxVideoSample> InVideoFrameSample)` — Called when an error was encountered during frame reception
- L208 _public prototype_ `virtual void OnStreamError() = 0;` — Called when stream has encountered an error and has to stop
- L211 _public prototype_ `virtual void OnVideoFormatChanged(const FRivermaxInputVideoFormatChangedInfo& NewFormatInfo) = 0;` — Called when stream has detected a change in the video format
- L214 _public function_ `virtual TSharedPtr<IRivermaxAncSample> OnAncFrameRequested(const FRivermaxInputAncFrameDescriptor& FrameInfo)` — Called when an ANC stream is ready to receive a packet. Return a valid sample to accept it.
- L220 _public function_ `virtual void OnAncFrameReceived(TSharedPtr<IRivermaxAncSample> InReceivedAncFrame)` — Called when an ANC packet has been fully received and parsed into InReceivedAncFrame.
- L225 _public function_ `virtual void OnAncFrameReceptionError()` — Called when a received ANC packet could not be parsed (checksum error, truncated packet, etc.).

#### class `UE::RivermaxCore::IRivermaxInputStream`  
`class IRivermaxInputStream`  
_L233-241_
- desc: Interface for initializing input stream from media player.
- L236 _public prototype_ `virtual ~IRivermaxInputStream() = default;`
- L239 _public prototype_ `virtual bool Initialize(const FRivermaxInputStreamOptions& InOptions, IRivermaxInputStreamListener& InListener) = 0;`
- L240 _public prototype_ `virtual void Uninitialize() = 0;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace RivermaxCore` (scope `UE`)

### `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxCore/Public/IRivermaxManager.h` (Public)


#### struct `UE::RivermaxCore::FRivermaxDeviceInfo`  
`struct FRivermaxDeviceInfo`  
_L11-15_
- L13 _public member_ `FString Description;`
- L14 _public member_ `FString InterfaceAddress;`

#### class `UE::RivermaxCore::IRivermaxManager`  
`class IRivermaxManager`  
_L29-84_
- desc: Not doing much at the moment but should be used as a central point to register every stream created and keep track of stats. Also manages initialization of the library.
- L32 _public prototype_ `virtual ~IRivermaxManager() = default;`
- L37 _public prototype_ `virtual bool IsManagerInitialized() const = 0;` — Returns true if RivermaxManager has been initialized
- L40 _public prototype_ `virtual bool IsLibraryInitialized() const = 0;` — Returns true if Rivermax library has been initialized and is usable
- L43 _public prototype_ `virtual bool ValidateLibraryIsLoaded() const = 0;` — Returns true if Rivermax library has been initialized and is usable, but also warns the user with a toast notification if it's not.
- L46 _public prototype_ `virtual const Private::RIVERMAX_API_FUNCTION_LIST* GetApi() const = 0;` — Return the Rivermax API.
- L49 _public prototype_ `virtual FOnPostRivermaxManagerInit& OnPostRivermaxManagerInit() = 0;` — Delegate triggered after manager has been initialized and library tried to be loaded
- L56 _public prototype_ `virtual uint64 GetTime() const = 0;` — Returns current time in nanoseconds for Rivermax If PTP is available, it will be used If not, FPlatform::Seconds will be used
- L59 _public prototype_ `virtual ERivermaxTimeSource GetTimeSource() const = 0;` — Returns where time is coming from
- L62 _public prototype_ `virtual TConstArrayView<FRivermaxDeviceInfo> GetDevices() const = 0;` — Returns list of found devices that can be used
- L65 _public prototype_ `virtual bool GetMatchingDevice(const FString& InSourceIP, FString& OutDeviceIP) const = 0;` — Returns a matching device interface address for the provided source IP
- L68 _public prototype_ `virtual bool IsValidIP(const FString& InSourceIP) const = 0;` — Returns true if provided IP string is in a valid format
- L71 _public prototype_ `virtual bool IsGPUDirectSupported() const = 0;` — Whether gpudirect is supported on this platform. At the moment, we rely on CUDA to handle it.
- L74 _public prototype_ `virtual bool IsGPUDirectInputSupported() const = 0;` — Whether gpudirect is enabled for input streams.
- L77 _public prototype_ `virtual bool IsGPUDirectOutputSupported() const = 0;` — Whether gpudirect is enabled for output streams.
- L80 _public prototype_ `virtual bool EnableDynamicHeaderSupport(const FString& Interface) = 0;` — Enables dynamic header support for a particular Rivermax device.
- L83 _public prototype_ `virtual void DisableDynamicHeaderSupport(const FString& Interface) = 0;` — If it's the last user of that interface, we disable dynamic header

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace RivermaxCore` (scope `UE`)
- L17 _namespace_ `namespace Private` (scope `UE::RivermaxCore`)
- L23 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnPostRivermaxManagerInit) class IRivermaxManager { public: virtual ~IRivermaxManager() = default; public: virtual bool IsManagerInitialized() const = 0; virtual bool IsLibraryInitialized() const = 0; virtual bool ValidateLibraryIsLoaded() const = 0; virtual const Private::RIVERMAX_API_FUNCTION_LIST* GetApi() const = 0; virtual FOnPostRivermaxManagerInit& OnPostRivermaxManagerInit() = 0; virtual uint64 GetTime() const = 0; virtual ERivermaxTimeSource GetTimeSource() const = 0; virtual TConstArrayView<FRivermaxDeviceInfo> GetDevices() const = 0;` — Delegate called when rivermax manager has been initialized and library tried to be loaded

### `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxCore/Public/IRivermaxOutputStream.h` (Public)


#### struct `UE::RivermaxCore::IRivermaxOutputInfo`  
`struct IRivermaxOutputInfo`  
_L16-28_
- desc: Base struct with description of the frame to be captured, required by all stream types.
- L19 _public member_ `uint64 FrameIdentifier = 0;` — Incremental number identifying frame. Usually GFrameCounter
- L22 _public member_ `uint32 Height = 0;` — Height of the frame
- L25 _public member_ `uint32 Width = 0;` — Width of the frame
- L27 _public function_ `virtual ~IRivermaxOutputInfo()`

#### struct `UE::RivermaxCore::FRivermaxOutputInfoVideo`  
`struct FRivermaxOutputInfoVideo : public IRivermaxOutputInfo`  
_L31-41_
- inherits: `IRivermaxOutputInfo`
- desc: Description of video frame to be captured.
- L34 _public member_ `void* CPUBuffer = nullptr;` — Video frame data location in system memory
- L37 _public member_ `FBufferRHIRef GPUBuffer;` — Video frame data location when using GPUDirect
- L40 _public member_ `uint32 Stride = 0;` — Stride of a line

#### struct `UE::RivermaxCore::FRivermaxOutputInfoAnc`  
`struct FRivermaxOutputInfoAnc : public IRivermaxOutputInfo`  
_L43-47_
- inherits: `IRivermaxOutputInfo`
- L46 _public member_ `TArray<uint16> UDWs;` — User data words to be put on the wire.

#### struct `UE::RivermaxCore::FRivermaxOutputInfoAncTimecode`  
`struct FRivermaxOutputInfoAncTimecode : public FRivermaxOutputInfoAnc`  
_L50-57_
- inherits: `FRivermaxOutputInfoAnc`
- desc: Description of Anc timecode frame to be captured.
- L53 _public member_ `FFrameRate FrameRate;` — Stream frame rate.
- L56 _public member_ `FTimecode Timecode;` — Frame's timecode.

#### struct `UE::RivermaxCore::FPresentedFrameInfo`  
`struct FPresentedFrameInfo`  
_L60-67_
- desc: Information about the last frame that was presented by the stream
- L63 _public member_ `uint64 PresentedFrameBoundaryNumber = 0;` — Frame boundary at which the RenderedFrameNumber has been presented
- L66 _public member_ `uint32 RenderedFrameNumber = 0;` — Last engine's FrameNumber that was presented.

#### class `UE::RivermaxCore::IRivermaxOutputStreamListener`  
`class IRivermaxOutputStreamListener`  
_L69-81_
- L74 _public prototype_ `virtual void OnInitializationCompleted(bool bHasSucceed) = 0;` — Initialization completion callback with result
- L77 _public prototype_ `virtual void OnStreamError() = 0;` — Called when stream has encountered an error and has to stop
- L80 _public prototype_ `virtual void OnPreFrameEnqueue() = 0;` — Called when stream is about to enqueue new frame

#### class `UE::RivermaxCore::IRivermaxOutputStream`  
`class IRivermaxOutputStream`  
_L83-118_
- L86 _public prototype_ `virtual ~IRivermaxOutputStream() = default;`
- L94 _public prototype_ `virtual bool Initialize(const FRivermaxOutputOptions& Options, IRivermaxOutputStreamListener& InListener) = 0;` — Initializes stream using input options. Returns false if stream creation has failed. Initialization is completed when OnInitializationCompletion has been called with result.
- L97 _public prototype_ `virtual void Uninitialize() = 0;` — Uninitializes current stream
- L101 _public function_ `virtual bool PushVideoFrame(const FRivermaxOutputInfoVideo& NewFrame)` — `UE_DEPRECATED(5.6, "This method is deprecated. Please use the PushFrame.")` — Pushes new video frame to the stream. Returns false if frame couldn't be pushed.
- L104 _public prototype_ `virtual bool PushFrame(TSharedPtr<IRivermaxOutputInfo> FrameInfo) = 0;` — Pushes new frame to the stream. Returns false if frame couldn't be pushed.
- L107 _public prototype_ `virtual bool IsGPUDirectSupported() const = 0;` — Returns true if GPUDirect is supported
- L114 _public prototype_ `virtual bool ReserveFrame(uint64 FrameCounter) const = 0;` — Tries to reserve a frame for the next capture If FRivermaxOutputOptions::FrameLockingMode equals BlockOnReservation, this method will block until a free frame is found.
- L117 _public prototype_ `virtual void GetLastPresentedFrame(FPresentedFrameInfo& OutFrameInfo) const = 0;` — Returns information about the last frame that was presented on the wire

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace RivermaxCore` (scope `UE`)

### `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxCore/Public/RivermaxFormats.h` (Public)


#### enum `UE::RivermaxCore::ESamplingType`  
`enum class ESamplingType : uint8`  
_L11-28_
- L13 _public enumerator_ `YUV422_8bit`
- L14 _public enumerator_ ``
- L15 _public enumerator_ ``
- L16 _public enumerator_ ``
- L17 _public enumerator_ ``
- L18 _public enumerator_ ``
- L19 _public enumerator_ ``
- L20 _public enumerator_ ``
- L21 _public enumerator_ ``
- L22 _public enumerator_ ``
- L23 _public enumerator_ ``
- L24 _public enumerator_ ``
- L25 _public enumerator_ ``
- L26 _public enumerator_ ``
- L27 _public enumerator_ ``

#### struct `UE::RivermaxCore::FVideoFormatInfo`  
`struct FVideoFormatInfo`  
_L105-118_
- L108 _public member_ `ESamplingType Sampling = ESamplingType::RGB_10bit;` — Sampling type of this format
- L111 _public member_ `uint16 BitDepth = 0;` — Bit depth for this format (i.e 8,10,12,16)
- L114 _public member_ `uint16 PixelGroupSize = 0;` — Pixel Group (pgroup) size in bytes
- L117 _public member_ `uint16 PixelGroupCoverage = 0;` — Pixel Group coverage (pgroup coverage) in pixels

#### struct `UE::RivermaxCore::FStandardVideoFormat`  
`struct FStandardVideoFormat`  
_L120-130_
- L122 _public prototype_ `static FVideoFormatInfo GetVideoFormatInfo(ESamplingType SamplingType);`
- L123 _public prototype_ `static bool IsRGB(ESamplingType SamplingType);`
- L124 _public prototype_ `static bool IsYUV(ESamplingType SamplingType);`
- L125 _public prototype_ `static bool IsYUV422(ESamplingType SamplingType);`
- L126 _public prototype_ `static bool IsYUV444(ESamplingType SamplingType);`
- L129 _private member_ `static const TArray<FVideoFormatInfo> AllSamplingTypes;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace RivermaxCore` (scope `UE`)
- L30 _function_ `inline const TCHAR* LexToString(ESamplingType InType)` (scope `UE::RivermaxCore`)

### `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxCore/Public/RivermaxHeader.h` (Public)
_(no declarations extracted)_

### `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxCore/Public/RivermaxPTPUtils.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace RivermaxCore` (scope `UE`)
- L17 _prototype_ `uint64 GetNextAlignmentPoint(const uint64 InPTPTimeNanosec, const FFrameRate& InRate);` (scope `UE::RivermaxCore`) — Returns next alignment point in nanosecond based on incoming PTP time and frame rate. Follows ST2059 standard for alignment
- L22 _prototype_ `uint64 GetAlignmentPointFromFrameNumber(const uint64 InFrameNumber, const FFrameRate& InRate);` (scope `UE::RivermaxCore`) — Returns alignment point in nanosecond based on incoming frame number and frame rate.
- L27 _prototype_ `uint64 GetFrameNumber(const uint64 InPTPTimeNanosec, const FFrameRate& InRate);` (scope `UE::RivermaxCore`) — Returns current frame number for the incoming PTP time for the given frame rate.
- L30 _prototype_ `FTimecode AtcUDW10ToTimecode(const TArray<uint16>& UDWs);` (scope `UE::RivermaxCore`) — Decodes 16 ATC LTC UDWs (produced by TimecodeToAtcUDW10) back to FTimecode.

### `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxCore/Public/RivermaxSettings.h` (Public)


#### enum `ERivermaxTimeSource`  
`enum class ERivermaxTimeSource`  
_L11-16_
- reflection: `UENUM()`
- L13 _public enumerator_ `PTP`
- L14 _public enumerator_ `Engine`
- L15 _public enumerator_ `System`

#### class `URivermaxSettings`  
`class URivermaxSettings : public UDeveloperSettings`  
_L22-43_
- reflection: `UCLASS(config=Engine)`
- inherits: `UDeveloperSettings`
- desc: Settings for Rivermax core plugin.
- L28 _public prototype_ `virtual FName GetCategoryName() const;`
- L30 _public prototype_ `virtual FText GetSectionText() const override;`
- L38 _public member_ `ERivermaxTimeSource TimeSource = ERivermaxTimeSource::PTP;` — `UPROPERTY(config, EditAnywhere, Category = "Settings", meta=(ConfigRestartRequired = true))` — Timing souce to be used by Rivermax scheduler
- L42 _public member_ `FString PTPInterfaceAddress = TEXT("*.*` — `UPROPERTY(config, EditAnywhere, Category = "Settings", meta = (EditCondition = "TimeSource == ERivermaxTimeSource::PTP", ConfigRestartRequired = true))` — Interface to use when Rivermax timing is configured to use PTP

### `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxCore/Public/RivermaxTracingUtils.h` (Public)


#### class `UE::RivermaxCore::FRivermaxTracingUtils`  
`class FRivermaxTracingUtils`  
_L11-34_
- L15 _public member_ `static TMap<uint8, FString> RmaxOutMediaCapturePipeTraceEvents;` — Media capture tracing string used to track a specific frame number being captured
- L18 _public member_ `static TMap<uint8, FString> RmaxOutSendingFrameTraceEvents;` — Rivermax output stream sending markup
- L21 _public member_ `static TMap<uint8, FString> RmaxOutFrameReadyTraceEvents;` — Rivermax frame capture is ready markup
- L24 _public member_ `static TMap<uint8, FString> RmaxInStartingFrameTraceEvents;` — Rivermax input stream starting to receive a frame markup
- L27 _public member_ `static TMap<uint8, FString> RmaxInReceivedFrameTraceEvents;` — Rivermax input stream frame received markup
- L30 _public member_ `static TMap<uint8, FString> RmaxInSelectedFrameTraceEvents;` — Rivermax player frame selected markup
- L33 _public member_ `static TMap<uint8, FString> RmaxOutAncSendingFrameTraceEvents;` — Rivermax ANC output stream sending markup

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace RivermaxCore` (scope `UE`)

### `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxCore/Public/RivermaxTypes.h` (Public)


#### enum `UE::RivermaxCore::ERivermaxAlignmentMode`  
`enum class ERivermaxAlignmentMode`  
_L17-24_
- L20 _public enumerator_ `AlignmentPoint` — Aligns scheduling with ST2059 frame boundary formula
- L23 _public enumerator_ `FrameCreation` — Aligns scheduling with frame creation

#### enum `UE::RivermaxCore::EFrameLockingMode`  
`enum class EFrameLockingMode : uint8`  
_L47-54_
- L50 _public enumerator_ `FreeRun` — If no frame available, continue
- L53 _public enumerator_ `BlockOnReservation` — Blocks when reserving a frame slot.

#### struct `UE::RivermaxCore::FRivermaxInputStreamOptions`  
`struct FRivermaxInputStreamOptions`  
_L77-105_
- L80 _public member_ `FFrameRate FrameRate = { 24,1 };` — Stream FrameRate
- L83 _public member_ `FString InterfaceAddress;` — Interface IP to bind to
- L86 _public member_ `FString StreamAddress = DefaultStreamAddress;` — IP of the stream. Defaults to multicast group IP.
- L89 _public member_ `uint32 Port = 50000;` — Port to be used by stream
- L92 _public member_ `ESamplingType PixelFormat = ESamplingType::RGB_10bit;` — Desired stream pixel format
- L95 _public member_ `int32 NumberOfBuffers = 2;` — Sample count to buffer.
- L98 _public member_ `bool bEnforceVideoFormat = false;` — If true, don't use auto detected video format
- L101 _public member_ `FIntPoint EnforcedResolution = FIntPoint::ZeroValue;` — Enforced resolution aligning with pgroup of sampling type
- L104 _public member_ `bool bUseGPUDirect = true;` — Whether to leverage GPUDirect (Cuda) capability to transfer memory to NIC if available

#### struct `UE::RivermaxCore::FRivermaxOutputStreamOptions`  
`struct FRivermaxOutputStreamOptions`  
_L107-123_
- L110 _public member_ `FFrameRate FrameRate = { 24,1 };` — Stream FrameRate
- L113 _public member_ `FString InterfaceAddress;` — Interface IP to bind to
- L116 _public member_ `FString StreamAddress = DefaultStreamAddress;` — IP of the stream. Defaults to multicast group IP.
- L119 _public member_ `uint32 Port = 50000;` — Port to be used by stream
- L122 _public member_ `uint64 StreamIndex = 0;` — Used by RivermaxOutStream when it calls to the library to assign Media Block Index in SDP.

#### struct `UE::RivermaxCore::FRivermaxVideoOutputOptions`  
`struct FRivermaxVideoOutputOptions : public FRivermaxOutputStreamOptions`  
_L125-138_
- inherits: `FRivermaxOutputStreamOptions`
- L128 _public member_ `FIntPoint Resolution = { 1920, 1080 };` — Desired stream resolution
- L131 _public member_ `ESamplingType PixelFormat = ESamplingType::RGB_10bit;` — Desired stream pixel format
- L134 _public member_ `FIntPoint AlignedResolution = FIntPoint::ZeroValue;` — Resolution aligning with pgroup of sampling type
- L137 _public member_ `bool bUseGPUDirect = true;` — Whether to leverage GPUDirect (Cuda) capability to transfer memory to NIC if available

#### struct `UE::RivermaxCore::FRivermaxAncOutputOptions`  
`struct FRivermaxAncOutputOptions : public FRivermaxOutputStreamOptions`  
_L140-176_
- inherits: `FRivermaxOutputStreamOptions`
- L143 _public prototype_ `FRivermaxAncOutputOptions(uint8 InDID, uint8 InSDID);` — This constructor is required to process and store DID and SDID according to ST291 standard to be ready to be used in RTP packet.
- L146 _public function_ `uint16 GetDID() const` — returns parity wrapped 10 bit DID value.
- L149 _public function_ `uint16 GetSDID() const` — returns parity wrapped 10 bit SDID value.
- L152 _public function_ `uint8 GetDIDRaw() const` — returns raw DID value.
- L155 _public function_ `uint8 GetSDIDRaw() const` — returns raw SDID value.
- L162 _private member_ `uint8 DIDRaw = 0;` — User readable DID value as specified by ST291 https://www.smpte-ra.org/smpte-ancillary-data-smpte-st-291
- L167 _private member_ `uint8 SDIDRaw = 0;` — User readable SDID value as specified by ST291 https://www.smpte-ra.org/smpte-ancillary-data-smpte-st-291
- L172 _private member_ `uint16 DID = 0;` — DID value with Parity. For more information see MakeDataIdentificationWord.
- L175 _private member_ `uint16 SDID = 0;` — SDID value with Parity. For more information see MakeDataIdentificationWord.

#### enum `UE::RivermaxCore::ERivermaxStreamType`  
`enum ERivermaxStreamType : uint8`  
_L178-189_
- L181 _public enumerator_ `ST2110_20` — Video.
- L183 _public enumerator_ `ST2110_30` — Audio.
- L185 _public enumerator_ `ST2110_40` — General Anc.
- L187 _public enumerator_ `ST2110_40_TC` — Timecode Anc.
- L188 _public enumerator_ `MAX`

#### struct `UE::RivermaxCore::FRivermaxOutputOptions`  
`struct FRivermaxOutputOptions`  
_L191-222_
- L194 _public member_ `TStaticArray<TSharedPtr<FRivermaxOutputStreamOptions>, static_cast<uint32>(ERivermaxStreamType::MAX)> StreamOptions;` — Contains a stream option for each ERivermaxStreamType.
- L197 _public member_ `int32 NumberOfBuffers = 2;` — Sample count to buffer.
- L200 _public member_ `ERivermaxAlignmentMode AlignmentMode = ERivermaxAlignmentMode::AlignmentPoint;` — Method used to align output stream
- L203 _public member_ `EFrameLockingMode FrameLockingMode = EFrameLockingMode::FreeRun;` — Defines how frame requests are handled. Whether they can block or not.
- L206 _public member_ `bool bDoContinuousOutput = true;` — Whether the stream will output a frame at every frame interval, repeating last frame if no new one provided
- L209 _public member_ `bool bDoFrameCounterTimestamping = true;` — Whether to use frame's frame number instead of standard timestamping
- L213 _public function_ `template <typename T> TSharedPtr<T> GetStreamOptions(ERivermaxStreamType InStreamType)` — Returns stream options for this stream.
- L218 _public function_ `TSharedPtr<FRivermaxOutputStreamOptions> GetStreamOptions(ERivermaxStreamType InStreamType)`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace RivermaxCore` (scope `UE`)
- L14 _variable_ `constexpr TCHAR DefaultStreamAddress[] = TEXT("228` (scope `UE::RivermaxCore`)
- L26 _function_ `inline const TCHAR* LexToString(ERivermaxAlignmentMode InValue)` (scope `UE::RivermaxCore`)
- L56 _function_ `inline const TCHAR* LexToString(EFrameLockingMode InValue)` (scope `UE::RivermaxCore`)
