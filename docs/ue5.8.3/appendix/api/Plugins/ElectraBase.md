# Plugins / ElectraBase

- module root: `Plugins/Media/ElectraUtil/Source/ElectraBase`
- headers: 31; symbols: 1057
- symbol kinds: class=42, delegate=3, enum=10, enumerator=48, function=375, macro=19, member=233, namespace=26, prototype=227, struct=28, typedef=21, union=1, variable=24
- PublicDependencyModuleNames: Core, Engine

### `Plugins/Media/ElectraUtil/Source/ElectraBase/Private/ElectraBaseModule.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogElectraBase, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogElectraBase, Log, All);`

### `Plugins/Media/ElectraUtil/Source/ElectraBase/Public/CodecTypeFormat.h` (Public)


#### struct `Electra::FCodecTypeFormat`  
`struct FCodecTypeFormat`  
_L25-149_
- desc: This structure contains codec format related information. Only information pertaining to the codec that can be derived from the container, the RFC6381 format string or a media stream playlist should be stored here.
- L136 _public member_ `TVariant<FEmptyVariantState,FVideo,FAudio,FSubtitle,FTMCDTimecode> Properties;`
- L137 _public member_ `BCP47::FLanguageTag LanguageTag;`
- L138 _public member_ `FString HumanReadableFormatInfo;`
- L139 _public member_ `FString RFC6381;`
- L140 _public member_ `FString MimeType;`
- L141 _public member_ `TMap<uint32, TArray<uint8>> ExtraBoxes;`
- L142 _public member_ `TArray<uint8> DCR;`
- L143 _public member_ `TArray<uint8> CSD;`
- L144 _public member_ `EType Type = EType::Invalid;`
- L145 _public member_ `EKeyframeMode KeyframeMode = EKeyframeMode::Unknown;`
- L146 _public member_ `uint32 FourCC = 0;`
- L147 _public member_ `uint32 Bitrate = 0;`
- L148 _public member_ `uint32 AverageBitrate = 0;`

#### enum `Electra::FCodecTypeFormat::EType`  
`enum class EType`  
_L27-35_
- L29 _public enumerator_ `Video`
- L30 _public enumerator_ `Audio`
- L31 _public enumerator_ `Subtitle`
- L32 _public enumerator_ `Timecode`
- L33 _public enumerator_ `Invalid`
- L34 _public enumerator_ `MAX = Invalid`

#### enum `Electra::FCodecTypeFormat::EKeyframeMode`  
`enum class EKeyframeMode`  
_L36-41_
- L38 _public enumerator_ `Unknown`
- L39 _public enumerator_ `OnlyKeyframes`
- L40 _public enumerator_ `DeltaFrames`

#### struct `Electra::FCodecTypeFormat::FVideo`  
`struct FVideo`  
_L42-79_
- L71 _public member_ `FFrameRate FrameRate {0, 0};`
- L72 _public member_ `uint32 Width = 0;`
- L73 _public member_ `uint32 Height = 0;`
- L74 _public member_ `uint32 BitDepth = 0;`
- L75 _public member_ `uint32 AspectRatioW = 1;`
- L76 _public member_ `uint32 AspectRatioH = 1;`
- L77 _public member_ `FProfile Profile;`
- L78 _public member_ `TOptional<FColorInfo> OptColorInfo;`

#### struct `Electra::FCodecTypeFormat::FVideo::FProfile`  
`struct FProfile`  
_L45-53_
- desc: Codec specific profile, level, etc.
- L47 _public member_ `uint32 Tier = 0;`
- L48 _public member_ `uint32 ProfileSpace = 0;`
- L49 _public member_ `uint32 Profile = 0;`
- L50 _public member_ `uint32 Level = 0;`
- L51 _public member_ `uint64 Constraints = 0;`
- L52 _public member_ `uint64 CompatibilityFlags = 0;`

#### struct `Electra::FCodecTypeFormat::FVideo::FColorInfo`  
`struct FColorInfo`  
_L55-70_
- desc: Codec specific color information. These do not necessarily correspond to MPEG definitions!
- L57 _public member_ `uint8 colourPrimaries = 0;`
- L58 _public member_ `uint8 transferCharacteristics = 0;`
- L59 _public member_ `uint8 matrixCoefficients = 0;`
- L60 _public member_ `uint8 videoFullRangeFlag = 0;`
- L61 _public member_ `uint8 chromaSubsampling = 0;`
- L69 _public member_ `TOptional<FChromaInfo> ChromaInfo;`

#### struct `Electra::FCodecTypeFormat::FVideo::FColorInfo::FChromaInfo`  
`struct FChromaInfo`  
_L62-68_
- L64 _public member_ `uint8 monochrome = 0;`
- L65 _public member_ `uint8 chromaSubsamplingX = 0;`
- L66 _public member_ `uint8 chromaSubsamplingY = 0;`
- L67 _public member_ `uint8 chromaSamplingPosition = 0;`

#### struct `Electra::FCodecTypeFormat::FAudio`  
`struct FAudio`  
_L80-94_
- L90 _public member_ `uint32 NumChannels = 0;`
- L91 _public member_ `uint32 ChannelConfiguration = 0;`
- L92 _public member_ `uint32 SampleRate = 0;`
- L93 _public member_ `TVariant<FEmptyVariantState, FMPEGObjectType> ObjectType;`

#### struct `Electra::FCodecTypeFormat::FAudio::FMPEGObjectType`  
`struct FMPEGObjectType`  
_L82-88_
- L84 _public member_ `uint32 ObjectType = 0;`
- L85 _public member_ `uint32 AudioObjectType = 0;`
- L86 _public member_ `uint8 MPEG = 0;`
- L87 _public member_ `uint8 Layer = 0;`

#### struct `Electra::FCodecTypeFormat::FSubtitle`  
`struct FSubtitle`  
_L95-97_

#### struct `Electra::FCodecTypeFormat::FTMCDTimecode`  
`struct FTMCDTimecode`  
_L98-135_
- L109 _public member_ `uint32 Flags = 0;`
- L110 _public member_ `uint32 Timescale = 0;`
- L111 _public member_ `uint32 FrameDuration = 0;`
- L112 _public member_ `uint32 NumberOfFrames = 0;`
- L114 _public function_ `bool IsDropFrame() const`
- L117 _public function_ `bool WrapsAfter24Hours() const`
- L120 _public function_ `bool SupportsNegativeTime() const`
- L123 _public function_ `FFrameRate GetFrameRate() const`
- L126 _public function_ `FTimecode ConvertToTimecode(uint32 InSampleTimecode) const`

#### enum `Electra::FCodecTypeFormat::FTMCDTimecode::EFlags`  
`enum EFlags : uint32`  
_L101-107_
- desc: See: https://developer.apple.com/documentation/quicktime-file-format/timecode_sample_description/flags
- L103 _public enumerator_ `DropFrame = 0x0001` — Indicates whether the timecode is drop frame. Set it to 1 if the timecode is drop frame.
- L104 _public enumerator_ `Max24Hour = 0x0002` — Indicates whether the timecode wraps after 24 hours. Set it to 1 if the timecode wraps.
- L105 _public enumerator_ `AllowNegativeTimes = 0x0004` — Indicates whether negative time values are allowed. Set it to 1 if the timecode supports negative values.
- L106 _public enumerator_ `Counter = 0x0008` — Indicates whether the time value corresponds to a tape counter value. Set it to 1 if the timecode values are tape counter values.

#### struct `Electra::FDRMTypeFormat`  
`struct FDRMTypeFormat`  
_L155-192_
- desc: Encryption information of a track.
- L189 _public member_ `TVariant<FNullEncryptionInfo, FISOEncryptionInfo> EncryptionInfo;`
- L190 _public function_ `bool IsEncrypted() const`

#### struct `Electra::FDRMTypeFormat::FNullEncryptionInfo`  
`struct FNullEncryptionInfo`  
_L157-159_

#### struct `Electra::FDRMTypeFormat::FISOEncryptionInfo`  
`struct FISOEncryptionInfo`  
_L162-187_
- desc: As defined by ISO/IEC 14496-12 Section 8.12 and ISO/IEC 23001-7
- L165 _public member_ `uint32 Scheme = 0;` — Set by `schm` box, if it exists.
- L166 _public member_ `uint32 SchemeVersion = 0;`
- L174 _public member_ `TArray<uint8> DefaultKID;`
- L175 _public member_ `TArray<uint8> DefaultIV;`
- L176 _public member_ `TOptional<FBlockPattern> BlockPattern;`
- L177 _public member_ `int32 DefaultIVSize = 0;`
- L186 _public member_ `TArray<FCDMInfo> CDMInfos;`

#### struct `Electra::FDRMTypeFormat::FISOEncryptionInfo::FBlockPattern`  
`struct FBlockPattern`  
_L169-173_
- desc: Set by `tenc` box, if it exists.
- L171 _public member_ `uint8 CryptByteBlock = 0;`
- L172 _public member_ `uint8 SkipByteBlock = 0;`

#### struct `Electra::FDRMTypeFormat::FISOEncryptionInfo::FCDMInfo`  
`struct FCDMInfo`  
_L180-185_
- desc: Set by `pssh` boxes, if they exist.
- L182 _public member_ `TArray<uint8> SystemID;`
- L183 _public member_ `TArray<TArray<uint8>> KIDs;`
- L184 _public member_ `TArray<uint8> Data;`

#### struct `Electra::FDecoderInformation`  
`struct FDecoderInformation`  
_L194-205_
- L196 _public member_ `bool bIsDecodable = true;`
- L204 _public member_ `FProviderInfo ProviderInfo;`

#### struct `Electra::FDecoderInformation::FProviderInfo`  
`struct FProviderInfo`  
_L197-203_
- L199 _public member_ `FString Name;`
- L200 _public member_ `FString Version;`
- L201 _public member_ `FString Implementation;`
- L202 _public member_ `FString Vendor;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API ELECTRABASE_API`
- L16 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraUtil/Source/ElectraBase/Public/Core/MediaEventSignal.h` (Public)


#### class `FMediaEvent`  
`class FMediaEvent : private TMediaNoncopyable<FMediaEvent>`  
_L11-90_
- inherits: `TMediaNoncopyable<FMediaEvent>`
- L14 _public function_ `FMediaEvent() : Event(FPlatformProcess::GetSynchEventFromPool(true))`
- L17 _public function_ `~FMediaEvent()`
- L26 _public function_ `void Wait()` — Waits for the event signal to get set. If already set, this function returns immediately.
- L34 _public function_ `void WaitAndReset()` — Waits for the event signal to get set and clears it immediately. If already set, this function returns immediately.
- L43 _public function_ `void Signal()` — Signals the event to be set. If already set, this does nothing.
- L51 _public function_ `void Reset()` — Clears the signal. Threads will now wait again until the signal is set once more.
- L59 _public function_ `bool IsSignaled() const` — Returns state of the signal.
- L68 _public function_ `bool WaitTimeout(int64 MicroSeconds)` — Waits for the event signal to get set within the given time limit. If already set, this function returns immediately. Returns true when event was set, false when wait timed out.
- L77 _public function_ `bool WaitTimeoutAndReset(int64 MicroSeconds)` — Waits for the event signal to get set within the given time limit and clears it immediately. If already set, this function returns immediately. Returns true when event was set, false when wait timed out.
- L89 _private member_ `mutable FEvent* Event;`

### `Plugins/Media/ElectraUtil/Source/ElectraBase/Public/Core/MediaInterlocked.h` (Public)


#### Free symbols / members of external scopes

- L10 _function_ `inline uint32 FMediaInterlockedRead(uint32 volatile& variable)`
- L15 _function_ `inline uint32 FMediaInterlockedIncrement(uint32 volatile& variable)`
- L21 _function_ `inline uint32 FMediaInterlockedDecrement(uint32 volatile& variable)`
- L27 _function_ `inline uint32 FMediaInterlockedAdd(uint32 volatile& variable, uint32 value)`
- L32 _function_ `inline uint32 FMediaInterlockedExchange(uint32 volatile& variable, uint32 exchangeValue)`
- L37 _function_ `inline void* FMediaInterlockedExchangePointerVoid(void* volatile& variable, void* pExchangeValue)`
- L42 _function_ `inline uint32 FMediaInterlockedCompareExchange(uint32 volatile& variable, uint32 exchangeValue, uint32 compareValue)`
- L47 _function_ `inline void* FMediaInterlockedCompareExchangePointer(void* volatile& variable, void* pExchangeValue, void* pCompareValue)`
- L52 _function_ `inline uint64 FMediaInterlockedRead64(uint64 volatile& variable)`
- L57 _function_ `inline uint64 FMediaInterlockedAdd64(uint64 volatile& variable, uint64 value)`
- L62 _function_ `inline int32 FMediaInterlockedRead(int32 volatile& variable)`
- L67 _function_ `inline int32 FMediaInterlockedIncrement(int32 volatile& variable)`
- L73 _function_ `inline int32 FMediaInterlockedDecrement(int32 volatile& variable)`
- L79 _function_ `inline int32 FMediaInterlockedAdd(int32 volatile& variable, int32 value)`
- L84 _function_ `inline int32 FMediaInterlockedExchange(int32 volatile& variable, int32 exchangeValue)`
- L89 _function_ `inline int32 FMediaInterlockedCompareExchange(int32 volatile& variable, int32 exchangeValue, int32 compareValue)`
- L95 _function_ `template <typename T, typename X> inline T* TMediaInterlockedExchangePointer(T* volatile& variable, X* pExchangeValue)`

### `Plugins/Media/ElectraUtil/Source/ElectraBase/Public/Core/MediaLock.h` (Public)


#### class `FMediaLockNone`  
`class FMediaLockNone : private TMediaNoncopyable<FMediaLockNone>`  
_L12-28_
- inherits: `TMediaNoncopyable<FMediaLockNone>`
- desc: Empty lock class.
- L15 _public function_ `inline void Lock() const`
- L16 _public function_ `void Unlock() const`

#### class `FMediaLockNone::ScopedLock`  
`class ScopedLock : private TMediaNoncopyable<ScopedLock>`  
_L18-27_
- inherits: `TMediaNoncopyable<ScopedLock>`
- L21 _public function_ `explicit ScopedLock(const FMediaLockNone& lock) : LockToUse(lock)`
- L23 _public prototype_ `~ScopedLock() = default;`
- L25 _private prototype_ `ScopedLock();`
- L26 _private member_ `const FMediaLockNone& LockToUse;`

#### class `FMediaLockCriticalSection`  
`class FMediaLockCriticalSection : private TMediaNoncopyable<FMediaLockCriticalSection>`  
_L35-70_
- inherits: `TMediaNoncopyable<FMediaLockCriticalSection>`
- desc: Lock class for generic container classes requiring mutual exclusion access.
- L38 _public function_ `FMediaLockCriticalSection()`
- L44 _public function_ `void Lock() const`
- L48 _public function_ `void Unlock() const`
- L69 _private member_ `mutable FCriticalSection CriticalSection;`

#### class `FMediaLockCriticalSection::ScopedLock`  
`class ScopedLock : private TMediaNoncopyable<ScopedLock>`  
_L53-67_
- inherits: `TMediaNoncopyable<ScopedLock>`
- L56 _public function_ `explicit ScopedLock(const FMediaLockCriticalSection& lock) : LockToUse(lock)`
- L60 _public function_ `~ScopedLock()`
- L65 _private prototype_ `ScopedLock();`
- L66 _private member_ `const FMediaLockCriticalSection& LockToUse;`

### `Plugins/Media/ElectraUtil/Source/ElectraBase/Public/Core/MediaMacros.h` (Public)


#### Free symbols / members of external scopes

- L12 _macro_ `#define FMEDIA_STATIC_ARRAY_COUNT(array) (SIZE_T)(sizeof((array)) / sizeof((array)[0]))` — Array convenience macros Evaluates to the number of elements in a statically defined array.
- L18 _function_ `static inline uint16 MEDIA_ENDIAN_SWAP(uint16 value)` — Endian swapping
- L23 _function_ `static inline int16 MEDIA_ENDIAN_SWAP(int16 value)`
- L28 _function_ `static inline uint32 MEDIA_ENDIAN_SWAP(uint32 value)`
- L33 _function_ `static inline int32 MEDIA_ENDIAN_SWAP(int32 value)`
- L38 _function_ `static inline uint64 MEDIA_ENDIAN_SWAP(uint64 value)`
- L43 _function_ `static inline int64 MEDIA_ENDIAN_SWAP(int64 value)`
- L50 _function_ `static inline uint8 MEDIA_TO_BIG_ENDIAN(uint8 value)` — Yes, there's no endian swapping with 8 bit values. We put them here so templated functions can be used with these types.
- L51 _function_ `static inline int8 MEDIA_TO_BIG_ENDIAN(int8 value)`
- L52 _function_ `static inline uint8 MEDIA_TO_LITTLE_ENDIAN(uint8 value)`
- L53 _function_ `static inline int8 MEDIA_TO_LITTLE_ENDIAN(int8 value)`
- L54 _function_ `static inline uint8 MEDIA_FROM_BIG_ENDIAN(uint8 value)`
- L55 _function_ `static inline int8 MEDIA_FROM_BIG_ENDIAN(int8 value)`
- L56 _function_ `static inline uint8 MEDIA_FROM_LITTLE_ENDIAN(uint8 value)`
- L57 _function_ `static inline int8 MEDIA_FROM_LITTLE_ENDIAN(int8 value)`
- L62 _function_ `static inline uint16 MEDIA_TO_BIG_ENDIAN(uint16 value)` — Convert a native value to big endian
- L63 _function_ `static inline int16 MEDIA_TO_BIG_ENDIAN(int16 value)`
- L64 _function_ `static inline int32 MEDIA_TO_BIG_ENDIAN(int32 value)`
- L65 _function_ `static inline uint32 MEDIA_TO_BIG_ENDIAN(uint32 value)`
- L66 _function_ `static inline int64 MEDIA_TO_BIG_ENDIAN(int64 value)`
- L67 _function_ `static inline uint64 MEDIA_TO_BIG_ENDIAN(uint64 value)`
- L69 _function_ `static inline uint16 MEDIA_TO_LITTLE_ENDIAN(uint16 value)` — Convert a native value to little endian
- L70 _function_ `static inline int16 MEDIA_TO_LITTLE_ENDIAN(int16 value)`
- L71 _function_ `static inline int32 MEDIA_TO_LITTLE_ENDIAN(int32 value)`
- L72 _function_ `static inline uint32 MEDIA_TO_LITTLE_ENDIAN(uint32 value)`
- L73 _function_ `static inline int64 MEDIA_TO_LITTLE_ENDIAN(int64 value)`
- L74 _function_ `static inline uint64 MEDIA_TO_LITTLE_ENDIAN(uint64 value)`
- L76 _function_ `static inline uint16 MEDIA_FROM_BIG_ENDIAN(uint16 value)` — Convert a big endian value to native
- L77 _function_ `static inline int16 MEDIA_FROM_BIG_ENDIAN(int16 value)`
- L78 _function_ `static inline int32 MEDIA_FROM_BIG_ENDIAN(int32 value)`
- L79 _function_ `static inline uint32 MEDIA_FROM_BIG_ENDIAN(uint32 value)`
- L80 _function_ `static inline int64 MEDIA_FROM_BIG_ENDIAN(int64 value)`
- L81 _function_ `static inline uint64 MEDIA_FROM_BIG_ENDIAN(uint64 value)`
- L83 _function_ `static inline uint16 MEDIA_FROM_LITTLE_ENDIAN(uint16 value)` — Convert a little endian value to native
- L84 _function_ `static inline int16 MEDIA_FROM_LITTLE_ENDIAN(int16 value)`
- L85 _function_ `static inline int32 MEDIA_FROM_LITTLE_ENDIAN(int32 value)`
- L86 _function_ `static inline uint32 MEDIA_FROM_LITTLE_ENDIAN(uint32 value)`
- L87 _function_ `static inline int64 MEDIA_FROM_LITTLE_ENDIAN(int64 value)`
- L88 _function_ `static inline uint64 MEDIA_FROM_LITTLE_ENDIAN(uint64 value)`

### `Plugins/Media/ElectraUtil/Source/ElectraBase/Public/Core/MediaMessageQueue.h` (Public)


#### class `TMediaMessageQueueNoTimeout`  
`template <typename T> class TMediaMessageQueueNoTimeout`  
_L21-154_
- desc: Generic message queue WITHOUT timeout support. Conceptually a message queue is a multiple-sender, single-receiver object, so use it only in that way! This version supports only a maximum number of messages that needs to be specified in the constructor or by calling Resize() before first use.
- L28 _public function_ `TMediaMessageQueueNoTimeout(SIZE_T MaxMessages = 0) : Messages(MaxMessages) , AvailSema(MaxMessages)` — Constructor.
- L40 _public function_ `T ReceiveMessage()` — Waits indefinitely for a message to arrive. @return Received message
- L56 _public function_ `bool ReceiveMessage(T& Message)` — Receives a message if one is already pending in the queue. @param message Receives the message if true is returned, unchanged otherwise @return true if message received and stored in 'message', false if no message received.
- L78 _public function_ `bool SendMessage(const T& Message, bool bWaitIfFull = true)` — Sends a message. @param message Message to send @param bWaitIfFull true to wait for the queue to have room if it's full, false to return immediately. @return true if message sent successfully, false if queue is full and bWaitIfFull was false.
- L99 _public function_ `bool JamMessage(const T& Message, bool bWaitIfFull = true)` — Jams a message to the front of the queue. @param message Message to send @param bWaitIfFull true to wait for the queue to have room if it's full, false to return immediately. @return true if message sent successfully, false if queue is full and bWaitIfFull was false.
- L117 _public function_ `bool HaveMessage() const` — Checks if there are pending messages. @return true if there are pending messages, false if not.
- L128 _public function_ `SIZE_T NumWaitingMessages() const` — Queries the number of messages in the queue. @return Number of enqueued messages.
- L143 _public function_ `void Resize(SIZE_T MaxMessages)` — Resizes the message queue, discarding any messages it may hold. Should only be used after the queue was created, but before it gets used! @param maxMessages New message queue size. @return none
- L151 _private member_ `TMediaQueue<T, FMediaLockCriticalSection> Messages;`
- L152 _private member_ `FMediaSemaphore AvailSema;`
- L153 _private member_ `FMediaSemaphore ReadySema;`

#### class `TMediaMessageQueueWithTimeout`  
`template <typename T> class TMediaMessageQueueWithTimeout`  
_L168-324_
- desc: Generic message queue WITH timeout support. Conceptually a message queue is a multiple-sender, single-receiver object, so use it only in that way! This version supports only a maximum number of messages that needs to be specified in the constructor or by calling Resize() before first use.
- L175 _public function_ `TMediaMessageQueueWithTimeout(SIZE_T MaxMessages = 0) : Messages(MaxMessages) , AvailSema(MaxMessages)` — Constructor.
- L187 _public function_ `T ReceiveMessage()` — Waits indefinitely for a message to arrive. @return Received message
- L203 _public function_ `bool ReceiveMessage(T& Message)` — Receives a message if one is already pending in the queue. @param message Receives the message if true is returned, unchanged otherwise @return true if message received and stored in 'message', false if no message received.
- L225 _public function_ `bool ReceiveMessage(T& Message, int64 MaxWaitMicroseconds)` — Waits a maximum amount of time for a message to arrive. @param message Receives the message if true is returned, unchanged otherwise @param maxWaitMicroseconds Maximum wait time in microseconds @return true if message received and stored in 'message', false if no message received.
- L248 _public function_ `bool SendMessage(const T& Message, bool bWaitIfFull = true)` — Sends a message. @param message Message to send @param bWaitIfFull true to wait for the queue to have room if it's full, false to return immediately. @return true if message sent successfully, false if queue is full and bWaitIfFull was false.
- L269 _public function_ `bool JamMessage(const T& Message, bool bWaitIfFull = true)` — Jams a message to the front of the queue. @param message Message to send @param bWaitIfFull true to wait for the queue to have room if it's full, false to return immediately. @return true if message sent successfully, false if queue is full and bWaitIfFull was false.
- L287 _public function_ `bool HaveMessage() const` — Checks if there are pending messages. @return true if there are pending messages, false if not.
- L298 _public function_ `SIZE_T NumWaitingMessages() const` — Queries the number of messages in the queue. @return Number of enqueued messages.
- L313 _public function_ `void Resize(SIZE_T MaxMessages)` — Resizes the message queue, discarding any messages it may hold. Should only be used after the queue was created, but before it gets used! @param maxMessages New message queue size. @return none
- L321 _private member_ `TMediaQueue<T, FMediaLockCriticalSection> Messages;`
- L322 _private member_ `FMediaSemaphore AvailSema;`
- L323 _private member_ `FMediaSemaphore ReadySema;`

#### class `TMediaMessageQueueStaticNoTimeout`  
`template <typename T, SIZE_T CAPACITY> class TMediaMessageQueueStaticNoTimeout : public TMediaMessageQueueNoTimeout<T>`  
_L338-349_
- inherits: `TMediaMessageQueueNoTimeout<T>`
- desc: Generic message queue WITHOUT timeout support. Conceptually a message queue is a multiple-sender, single-receiver object, so use it only in that way! This version uses a template argument to define the initial size.
- L345 _public function_ `TMediaMessageQueueStaticNoTimeout() : TMediaMessageQueueNoTimeout<T>(CAPACITY)` — Constructor.

#### class `TMediaMessageQueueStaticWithTimeout`  
`template <typename T, SIZE_T CAPACITY> class TMediaMessageQueueStaticWithTimeout : public TMediaMessageQueueWithTimeout<T>`  
_L360-371_
- inherits: `TMediaMessageQueueWithTimeout<T>`
- desc: Generic message queue WITH timeout support. Conceptually a message queue is a multiple-sender, single-receiver object, so use it only in that way! This version uses a template argument to define the initial size.
- L367 _public function_ `TMediaMessageQueueStaticWithTimeout() : TMediaMessageQueueWithTimeout<T>(CAPACITY)` — Constructor.

#### class `TMediaMessageQueueDynamicNoTimeout`  
`template <typename T> class TMediaMessageQueueDynamicNoTimeout`  
_L392-507_
- desc: Generic message queue WITHOUT timeout support. Conceptually a message queue is a multiple-sender, single-receiver object, so use it only in that way! This version supports an unlimited number of messages (we limit it to 2^31-1) Sending a message can therefore never block. We keep the interface identical to TMediaMessageQueueNoTimeout::SendMessage for compatibility.
- L399 _public function_ `TMediaMessageQueueDynamicNoTimeout() : AvailSema(0x7fffffff)` — Constructor.
- L410 _public function_ `T ReceiveMessage()` — Waits indefinitely for a message to arrive. @return		Received message
- L426 _public function_ `bool ReceiveMessage(T& Message)` — Receives a message if one is already pending in the queue. @param		message     Receives the message if true is returned, unchanged otherwise @return		true if message received and stored in 'message', false if no message received.
- L448 _public function_ `bool SendMessage(const T& Message, bool bWaitIfFull = true)` — Sends a message. @param		message         Message to send @param		bWaitIfFull     true to wait for the queue to have room if it's full, false to return immediately. @return		true if message sent successfully, false if queue is full and bWaitIfFull was false.
- L469 _public function_ `bool JamMessage(const T& Message, bool bWaitIfFull = true)` — Jams a message to the front of the queue. @param		message         Message to send @param		bWaitIfFull     true to wait for the queue to have room if it's full, false to return immediately. @return		true if message sent successfully, false if queue is full and bWaitIfFull was false.
- L487 _public function_ `bool HaveMessage() const` — Checks if there are pending messages. @return		true if there are pending messages, false if not.
- L498 _public function_ `SIZE_T NumWaitingMessages() const` — Queries the number of messages in the queue. @return		Number of enqueued messages.
- L504 _private member_ `TMediaQueueDynamic<T> Messages;`
- L505 _private member_ `FMediaSemaphore AvailSema;`
- L506 _private member_ `FMediaSemaphore ReadySema;`

#### class `TMediaMessageQueueDynamicWithTimeout`  
`template <typename T> class TMediaMessageQueueDynamicWithTimeout`  
_L524-662_
- desc: Generic message queue WITH timeout support. Conceptually a message queue is a multiple-sender, single-receiver object, so use it only in that way! This version supports an unlimited number of messages (we limit it to 2^31-1) Sending a message can therefore never block. We keep the interface identical to TMediaMessageQueueNoTimeout::SendMessage for compatibility.
- L531 _public function_ `TMediaMessageQueueDynamicWithTimeout() : AvailSema(0x7fffffff)` — Constructor.
- L542 _public function_ `T ReceiveMessage()` — Waits indefinitely for a message to arrive. @return		Received message
- L558 _public function_ `bool ReceiveMessage(T& Message)` — Receives a message if one is already pending in the queue. @param		message     Receives the message if true is returned, unchanged otherwise @return		true if message received and stored in 'message', false if no message received.
- L580 _public function_ `bool ReceiveMessage(T& Message, int64 MaxWaitMicroseconds)` — Waits a maximum amount of time for a message to arrive. @param		message                 Receives the message if true is returned, unchanged otherwise @param		maxWaitMicroseconds     Maximum wait time in microseconds @return		true if message received and stored in 'message', false if no message received.
- L603 _public function_ `bool SendMessage(const T& Message, bool bWaitIfFull = true)` — Sends a message. @param		message         Message to send @param		bWaitIfFull     true to wait for the queue to have room if it's full, false to return immediately. @return		true if message sent successfully, false if queue is full and bWaitIfFull was false.
- L624 _public function_ `bool JamMessage(const T& Message, bool bWaitIfFull = true)` — Jams a message to the front of the queue. @param		message         Message to send @param		bWaitIfFull     true to wait for the queue to have room if it's full, false to return immediately. @return		true if message sent successfully, false if queue is full and bWaitIfFull was false.
- L642 _public function_ `bool HaveMessage() const` — Checks if there are pending messages. @return		true if there are pending messages, false if not.
- L653 _public function_ `SIZE_T NumWaitingMessages() const` — Queries the number of messages in the queue. @return		Number of enqueued messages.
- L659 _private member_ `TMediaQueueDynamic<T> Messages;`
- L660 _private member_ `FMediaSemaphore AvailSema;`
- L661 _private member_ `FMediaSemaphore ReadySema;`

### `Plugins/Media/ElectraUtil/Source/ElectraBase/Public/Core/MediaNoncopyable.h` (Public)


#### class `TMediaNoncopyable`  
`template<typename T> class TMediaNoncopyable`  
_L6-14_
- L9 _protected prototype_ `TMediaNoncopyable() = default;`
- L10 _protected prototype_ `~TMediaNoncopyable() = default;`
- L12 _private prototype_ `TMediaNoncopyable(const TMediaNoncopyable&) = delete;`
- L13 _private prototype_ `TMediaNoncopyable& operator = (const TMediaNoncopyable&) = delete;`

### `Plugins/Media/ElectraUtil/Source/ElectraBase/Public/Core/MediaQueue.h` (Public)


#### class `TMediaQueueAllocator`  
`template <typename T> class TMediaQueueAllocator`  
_L16-30_
- desc: Default memory allocator.
- L19 _public function_ `static T* Allocate(uint32 NumElements)`
- L23 _public function_ `static void Deallocate(T* Address)`

#### class `TMediaQueue`  
`template <typename T, typename L = FMediaLockNone, typename M = TMediaQueueAllocator<T> > class TMediaQueue : public L`  
_L49-212_
- inherits: `L`
- desc: Object safe queue class. Implements by-value methods only to avoid working with references. Methods like T& Push() T& operator[](int32) T& Front() are dangerous when used in a multi-threaded environment since the elements cannot be protected by an internal mutex. If you are using an external mutex to ensure object safety you may add such functions, but please derive a new class for this!!!
- L52 _public typedef_ `using MyType = TMediaQueue<T, L, M>;`
- L53 _public typedef_ `using ElementType = T;`
- L55 _public function_ `TMediaQueue(int32 InitialCapacity = 0)`
- L61 _public prototype_ `TMediaQueue(const MyType& rhs) = delete;` — Not copyable (for now) because of the possible mutex class.
- L62 _public prototype_ `MyType& operator = (const MyType& rhs) = delete;`
- L64 _public function_ `~TMediaQueue()`
- L69 _public function_ `void Clear()`
- L84 _public function_ `void Resize(int32 newCapacity)`
- L104 _public function_ `void Swap(MyType& rhs)`
- L128 _public function_ `int32 Capacity() const`
- L133 _public function_ `int32 Num() const`
- L138 _public function_ `bool IsEmpty() const`
- L143 _public function_ `bool IsFull() const`
- L148 _public function_ `void Push(const T& Element)`
- L163 _public function_ `void PushFront(const T& Element)`
- L182 _public function_ `T Pop()`
- L197 _public function_ `T Front() const`
- L207 _protected member_ `T* Elements = nullptr;`
- L208 _protected member_ `int32 MaxNum = 0;`
- L209 _protected member_ `int32 NumIn = 0;`
- L210 _protected member_ `int32 IdxIn = 0;`
- L211 _protected member_ `int32 IdxOut = 0;`

#### class `TMediaQueueNoLock`  
`template <typename T, typename M = TMediaQueueAllocator<T> > class TMediaQueueNoLock : public TMediaQueue<T, FMediaLockNone, M>`  
_L224-362_
- inherits: `TMediaQueue<T,FMediaLockNone,M>`
- desc: A mutex-less version of TMediaQueue to enable working with references. Since this is not thread-safe you must ensure access with an external mutex.
- L227 _public typedef_ `using MyType = TMediaQueueNoLock<T, M>;`
- L228 _public typedef_ `using ElementType = T;`
- L229 _public typedef_ `typedef TMediaQueue<T, FMediaLockNone, M> B;`
- L231 _public function_ `TMediaQueueNoLock() : B()`
- L232 _public prototype_ `~TMediaQueueNoLock() = default;`
- L234 _public function_ `T& PushRef()`
- L247 _public function_ `const T& FrontRef() const`
- L253 _public function_ `T& FrontRef()`
- L259 _public function_ `const T& BackRef() const`
- L265 _public function_ `T& BackRef()`
- L271 _public function_ `void Erase(int32 i)`
- L298 _public function_ `const T& operator[](int32 i) const`
- L310 _public function_ `T& operator[](int32 i)`
- L322 _public function_ `void AppendFirstElements(const MyType& FromOther, int32 MaxElements = ~int32(0))`
- L342 _public function_ `void AppendLastElements(const MyType& FromOther, int32 MaxElements = ~int32(0))`

#### class `TMediaQueueFixedStatic`  
`template <typename T, uint32 CAPACITY, typename L = FMediaLockCriticalSection > class TMediaQueueFixedStatic : public L`  
_L384-503_
- inherits: `L`
- desc: Object safe queue class. Implements by-value methods only to avoid working with references. Methods like T& Push() T& operator[](int32) T& Front() are dangerous when used in a multi-threaded environment since the elements cannot be protected by an internal mutex. If you are using an external mutex to ensure object safety you may add such functions, but please derive a new class for this!!! (or use the one below)
- L387 _public typedef_ `using MyType = TMediaQueueFixedStatic<T, CAPACITY, L>;`
- L388 _public typedef_ `using ElementType = T;`
- L390 _public prototype_ `TMediaQueueFixedStatic() = default;`
- L393 _public prototype_ `TMediaQueueFixedStatic(const MyType& rhs) = delete;` — Not copyable (for now) because of the possible mutex class.
- L394 _public prototype_ `MyType& operator = (const MyType& rhs) = delete;`
- L396 _public function_ `~TMediaQueueFixedStatic()`
- L401 _public function_ `void Clear()`
- L416 _public function_ `int32 Capacity() const`
- L421 _public function_ `int32 Num() const`
- L426 _public function_ `bool IsEmpty() const`
- L431 _public function_ `bool IsFull() const`
- L436 _public function_ `void Push(const T& element)`
- L451 _public function_ `void PushFront(const T& element)`
- L470 _public function_ `T Pop()`
- L485 _public function_ `T Front() const`
- L497 _protected member_ `uint8 FixedElements[CAPACITY * sizeof(T)] GCC_ALIGN(16);`
- L499 _protected member_ `T* Elements = (T*)FixedElements;`
- L500 _protected member_ `int32 NumIn = 0;`
- L501 _protected member_ `int32 IdxIn = 0;`
- L502 _protected member_ `int32 IdxOut = 0;`

#### class `TMediaQueueFixedStaticNoLock`  
`template <typename T, uint32 CAPACITY> class TMediaQueueFixedStaticNoLock : public TMediaQueueFixedStatic<T, CAPACITY, FMediaLockNone>`  
_L508-605_
- inherits: `TMediaQueueFixedStatic<T,CAPACITY,FMediaLockNone>`
- L511 _public typedef_ `using MyType = TMediaQueueFixedStaticNoLock<T, CAPACITY>;`
- L512 _public typedef_ `using ElementType = T;`
- L513 _public typedef_ `typedef TMediaQueueFixedStatic<T, CAPACITY, FMediaLockNone> B;`
- L515 _public function_ `TMediaQueueFixedStaticNoLock() : B()`
- L516 _public prototype_ `~TMediaQueueFixedStaticNoLock() = default;`
- L518 _public function_ `T& PushRef()`
- L531 _public function_ `const T& FrontRef() const`
- L537 _public function_ `T& FrontRef()`
- L543 _public function_ `const T& BackRef() const`
- L549 _public function_ `T& BackRef()`
- L555 _public function_ `void Erase(int32 i)`
- L582 _public function_ `const T& operator[](int32 i) const`
- L594 _public function_ `T& operator[](int32 i)`

#### class `TMediaQueueDynamic`  
`template <typename T, typename L = FMediaLockCriticalSection, typename M = TMediaQueueAllocator<T> > class TMediaQueueDynamic : public L, private TMediaNoncopyable<TMediaQueueDynamic<T> >`  
_L618-788_
- inherits: `L,TMediaNoncopyable<TMediaQueueDynamic<T>>`
- desc: Dynamically sized queue. Will grow when capacity is reached. Therefore a lock is REQUIRED! Never use this with a null-mutex unless you know what you're doing.
- L621 _public typedef_ `using MyType = TMediaQueueDynamic<T, L, M>;`
- L622 _public typedef_ `using ElementType = T;`
- L624 _public function_ `TMediaQueueDynamic(int32 initialCapacity = 0, int32 increment = 32) : IncrementBy(increment)`
- L630 _public function_ `~TMediaQueueDynamic()`
- L637 _public function_ `void SetIncrement(int32 newIncrement)`
- L644 _public function_ `void Clear()`
- L659 _public function_ `void Resize(int32 newCapacity)`
- L692 _public function_ `int32 Increment() const`
- L697 _public function_ `int32 Capacity() const`
- L702 _public function_ `int32 Num() const`
- L707 _public function_ `bool IsEmpty() const`
- L712 _public function_ `bool IsFull() const`
- L717 _public function_ `void Push(const T& element)`
- L735 _public function_ `void PushFront(const T& element)`
- L757 _public function_ `T Pop()`
- L772 _public function_ `T Front() const`
- L782 _protected member_ `T* Elements = nullptr;`
- L783 _protected member_ `int32 MaxNum = 0;`
- L784 _protected member_ `int32 NumIn = 0;`
- L785 _protected member_ `int32 IdxIn = 0;`
- L786 _protected member_ `int32 IdxOut = 0;`
- L787 _protected member_ `int32 IncrementBy = 32;`

#### class `TMediaQueueDynamicNoLock`  
`template <typename T, typename M = TMediaQueueAllocator<T> > class TMediaQueueDynamicNoLock : public TMediaQueueDynamic<T, FMediaLockNone, M>`  
_L795-852_
- inherits: `TMediaQueueDynamic<T,FMediaLockNone,M>`
- L798 _public typedef_ `using MyType = TMediaQueueDynamicNoLock<T, M>;`
- L799 _public typedef_ `using ElementType = T;`
- L800 _public typedef_ `typedef TMediaQueueDynamic<T, FMediaLockNone, M> B;`
- L802 _public function_ `TMediaQueueDynamicNoLock() : B()`
- L803 _public prototype_ `~TMediaQueueDynamicNoLock() = default;`
- L805 _public function_ `const T& FrontRef() const`
- L811 _public function_ `T& FrontRef()`
- L817 _public function_ `const T& BackRef() const`
- L823 _public function_ `T& BackRef()`
- L829 _public function_ `const T& operator[](int32 i) const`
- L841 _public function_ `T& operator[](int32 i)`

### `Plugins/Media/ElectraUtil/Source/ElectraBase/Public/Core/MediaSemaphore.h` (Public)


#### class `FMediaSemaphore`  
`class FMediaSemaphore : private TMediaNoncopyable<FMediaSemaphore>`  
_L13-139_
- inherits: `TMediaNoncopyable<FMediaSemaphore>`
- L16 _public function_ `FMediaSemaphore(int32 InitialCount = 0) : Event(FPlatformProcess::GetSynchEventFromPool(true)) , Count(InitialCount)`
- L21 _public function_ `~FMediaSemaphore()`
- L31 _public function_ `bool Obtain()`
- L57 _public function_ `bool Obtain(int64 WaitMicroSeconds)`
- L103 _public function_ `bool TryToObtain()`
- L116 _public function_ `void Release()`
- L123 _public function_ `int32 CurrentCount() const`
- L129 _public function_ `void SetCount(int32 NewCurrentCount)`
- L136 _private member_ `mutable FCriticalSection CriticalSection;`
- L137 _private member_ `mutable FEvent* Event;`
- L138 _private member_ `int32 Count;`

### `Plugins/Media/ElectraUtil/Source/ElectraBase/Public/Core/MediaThreads.h` (Public)


#### class `FMediaRunnable`  
`class FMediaRunnable : private TMediaNoncopyable<FMediaRunnable>, public FRunnable`  
_L24-103_
- inherits: `TMediaNoncopyable<FMediaRunnable>,FRunnable`
- L27 _public prototype_ `DECLARE_DELEGATE(FStartDelegate);`
- L40 _public prototype_ `static void Startup();`
- L41 _public prototype_ `static void Shutdown();`
- L42 _public prototype_ `static void EnqueueAsyncTask(TFunction<void()>&& InFunctionToExecuteOnAsyncThread);`
- L44 _public prototype_ `static FMediaRunnable* Create(int32 CoreAffinityMask, EThreadPriority Priority, uint32 StackSize, const FString& InThreadName);`
- L45 _public prototype_ `static void Destroy(FMediaRunnable* Thread);`
- L47 _public prototype_ `void Start(FStartDelegate Entry, bool bWaitRunning = false);`
- L49 _public prototype_ `void SetDoneSignal(FMediaEvent* DoneSignal);`
- L51 _public prototype_ `void SetName(const FString& InThreadName);`
- L53 _public prototype_ `EThreadPriority ChangePriority(EThreadPriority NewPriority);`
- L55 _public function_ `EThreadPriority PriorityGet() const`
- L60 _public function_ `uint32 StackSizeGet() const`
- L65 _public function_ `static uint32 StackSizeGetDefault()`
- L70 _public function_ `static void SleepSeconds(uint32 Seconds)`
- L75 _public function_ `static void SleepMilliseconds(uint32 Milliseconds)`
- L80 _public function_ `static void SleepMicroseconds(uint32 Microseconds)`
- L86 _private member_ `FCriticalSection StateAccessMutex;`
- L87 _private member_ `FStartDelegate EntryFunction;`
- L88 _private member_ `FString ThreadName;`
- L89 _private member_ `FRunnableThread* MediaThreadRunnable = nullptr;`
- L90 _private member_ `FEvent* SignalRunning = nullptr;`
- L91 _private member_ `FMediaEvent* DoneSignal = nullptr;`
- L92 _private member_ `EThreadPriority ThreadPriority = TPri_Normal;`
- L93 _private member_ `uint64 InitialCoreAffinity = 0;`
- L94 _private member_ `uint32 StackSize = 0;`
- L95 _private member_ `bool bIsStarted = false;`
- L97 _private prototype_ `FMediaRunnable();`
- L98 _private prototype_ `~FMediaRunnable();`
- L100 _private prototype_ `void StartInternal();`
- L101 _private prototype_ `uint32 Run() override;`
- L102 _private prototype_ `void Exit() override;`

#### struct `FMediaRunnable::Param`  
`struct Param`  
_L32-38_
- desc: Common thread configuration parameters.
- L35 _public member_ `EThreadPriority Priority = TPri_Normal;` — Set some standard values as defaults.
- L36 _public member_ `uint32 StackSize = 65536;`
- L37 _public member_ `int32 CoreAffinity = -1;`

#### class `FMediaThread`  
`class FMediaThread : private TMediaNoncopyable<FMediaThread>`  
_L124-168_
- inherits: `TMediaNoncopyable<FMediaThread>`
- desc: A thread base class to either inherit from or use as a variable. Thread parameters are given to constructor but can be changed before starting the thread with the ThreadSet..() functions. This allows the constructor to use system default values so an instance of this class can be used as a member variable of some class. To start the thread on some function of type void(*)(void) call ThreadStart() with an appropriate delegate. IMPORTANT: If used as a member variable you have to ensure for your class to stay alive i.e. not be destroyed before the thread function has finished. Otherwise your function will most likely crash. Either wait for thread completion by calling ThreadWaitDone() *OR* have the destructor wait for the thread itself by calling ThreadWaitDoneOnDelete(true) at some point prior to destruction - preferably before starting the thread.
- L127 _public prototype_ `virtual ~FMediaThread();`
- L130 _public prototype_ `FMediaThread(const char* AnsiName = nullptr);` — Default constructor. Uses system defaults if no values given.
- L133 _public prototype_ `void ThreadSetPriority(EThreadPriority Priority);` — Set a thread priority other than the one given to the constructor before starting the thread.
- L136 _public prototype_ `void ThreadSetCoreAffinity(int32 CoreAffinity);` — Set a core affinity before starting the thread. Defaults to -1 for no affinity (run on any core).
- L139 _public prototype_ `void ThreadSetStackSize(uint32 StackSize);` — Set a thread stack size other than the one given to the constructor before starting the thread.
- L142 _public prototype_ `void ThreadSetName(const char* InAnsiThreadName);` — Set a thread name other than the one given to the constructor before starting the thread.
- L145 _public prototype_ `void ThreadRename(const char* InAnsiThreadName);` — Sets a new thread name once the thread is running.
- L148 _public prototype_ `void ThreadWaitDoneOnDelete(bool bWait);` — Sets whether or not the destructor needs to wait for the thread to have finished. Defaults to false. Useful when using this as a member variable.
- L151 _public prototype_ `void ThreadWaitDone();` — Waits for the thread to have finished.
- L154 _public prototype_ `void ThreadStart(FMediaRunnable::FStartDelegate EntryFunction);` — Starts the thread at the given function void(*)(void)
- L157 _public prototype_ `void ThreadReset();` — Resets the thread to be started again. Must have waited for thread termination using ThreadWaitDone() first!
- L160 _private member_ `FMediaEvent SigDone;`
- L161 _private member_ `FString ThreadName;`
- L162 _private member_ `FMediaRunnable* MediaRunnable = nullptr;`
- L163 _private member_ `EThreadPriority Priority = TPri_Normal;`
- L164 _private member_ `uint32 StackSize = 0;`
- L165 _private member_ `int32 CoreAffinity = 0;`
- L166 _private member_ `bool bIsStarted = false;`
- L167 _private member_ `bool bWaitDoneOnDelete = false;`

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API ELECTRABASE_API`
- L27 _delegate_ `DECLARE_DELEGATE(FStartDelegate);`

### `Plugins/Media/ElectraUtil/Source/ElectraBase/Public/Core/MediaTypes.h` (Public)


#### Free symbols / members of external scopes

- L15 _typedef_ `typedef uint32 UEMediaError;`
- L17 _macro_ `#define UEMEDIA_ERROR_OK (0)`
- L18 _macro_ `#define UEMEDIA_ERROR_DETAIL (1)`
- L19 _macro_ `#define UEMEDIA_ERROR_INTERNAL (2)`
- L20 _macro_ `#define UEMEDIA_ERROR_NOT_IMPLEMENTED (3)`
- L21 _macro_ `#define UEMEDIA_ERROR_ABORTED (4)`
- L22 _macro_ `#define UEMEDIA_ERROR_END_OF_STREAM (5)`
- L23 _macro_ `#define UEMEDIA_ERROR_INSUFFICIENT_DATA (6)`
- L24 _macro_ `#define UEMEDIA_ERROR_READ_ERROR (7)`
- L25 _macro_ `#define UEMEDIA_ERROR_FORMAT_ERROR (8)`
- L26 _macro_ `#define UEMEDIA_ERROR_NOT_SUPPORTED (9)`
- L27 _macro_ `#define UEMEDIA_ERROR_TRY_AGAIN (100)`
- L28 _macro_ `#define UEMEDIA_ERROR_OOM (0x80000000U)`
- L29 _macro_ `#define UEMEDIA_ERROR_BAD_ARGUMENTS (0x80000001U)`
- L31 _namespace_ `namespace Electra`
- L34 _typedef_ `template <typename T> using TSharedPtrTS = TSharedPtr<T, ESPMode::ThreadSafe>;` (scope `Electra`)
- L37 _typedef_ `template <typename T> using TWeakPtrTS = TWeakPtr<T, ESPMode::ThreadSafe>;` (scope `Electra`)
- L40 _function_ `template<typename T, typename... ArgTypes> TSharedRef<T, ESPMode::ThreadSafe> MakeSharedTS(ArgTypes&&... Args)` (scope `Electra`)

### `Plugins/Media/ElectraUtil/Source/ElectraBase/Public/IElectraBaseModule.h` (Public)


#### class `IElectraBaseModule`  
`class IElectraBaseModule : public IModuleInterface`  
_L11-19_
- inherits: `IModuleInterface`
- desc: Interface for the `ElectraBase` module.
- L16 _public prototype_ `virtual ~IElectraBaseModule() = default;`

### `Plugins/Media/ElectraUtil/Source/ElectraBase/Public/MediaAudioDecoderOutput.h` (Public)
_(no declarations extracted)_

### `Plugins/Media/ElectraUtil/Source/ElectraBase/Public/MediaDecoderOutput.h` (Public)


#### struct `FDecoderTimeStamp`  
`struct FDecoderTimeStamp`  
_L8-15_
- L10 _public function_ `FDecoderTimeStamp()`
- L11 _public function_ `FDecoderTimeStamp(FTimespan InTime, int64 InSequenceIndex) : Time(InTime), SequenceIndex(InSequenceIndex)`
- L13 _public member_ `FTimespan Time;`
- L14 _public member_ `int64 SequenceIndex;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace IDecoderOutputOptionNames`
- L20 _variable_ `static const FName PTS(TEXT("pts"` (scope `IDecoderOutputOptionNames`)
- L21 _variable_ `static const FName Duration(TEXT("dura` (scope `IDecoderOutputOptionNames`)
- L22 _variable_ `static const FName Width(TEXT("widt` (scope `IDecoderOutputOptionNames`)
- L23 _variable_ `static const FName Height(TEXT("heig` (scope `IDecoderOutputOptionNames`)
- L24 _variable_ `static const FName Pitch(TEXT("pitc` (scope `IDecoderOutputOptionNames`)
- L25 _variable_ `static const FName AspectRatio(TEXT("aspe` (scope `IDecoderOutputOptionNames`)
- L26 _variable_ `static const FName CropLeft(TEXT("crop` (scope `IDecoderOutputOptionNames`)
- L27 _variable_ `static const FName CropTop(TEXT("crop` (scope `IDecoderOutputOptionNames`)
- L28 _variable_ `static const FName CropRight(TEXT("crop` (scope `IDecoderOutputOptionNames`)
- L29 _variable_ `static const FName CropBottom(TEXT("crop` (scope `IDecoderOutputOptionNames`)
- L30 _variable_ `static const FName PixelFormat(TEXT("pixe` (scope `IDecoderOutputOptionNames`)
- L31 _variable_ `static const FName PixelEncoding(TEXT("pixe` (scope `IDecoderOutputOptionNames`)
- L32 _variable_ `static const FName Orientation(TEXT("orie` (scope `IDecoderOutputOptionNames`)
- L33 _variable_ `static const FName BitsPerComponent(TEXT("bits` (scope `IDecoderOutputOptionNames`)
- L34 _variable_ `static const FName HDRInfo(TEXT("hdr_` (scope `IDecoderOutputOptionNames`)
- L35 _variable_ `static const FName Colorimetry(TEXT("colo` (scope `IDecoderOutputOptionNames`)
- L36 _variable_ `static const FName AspectW(TEXT("aspe` (scope `IDecoderOutputOptionNames`)
- L37 _variable_ `static const FName AspectH(TEXT("aspe` (scope `IDecoderOutputOptionNames`)
- L38 _variable_ `static const FName FPSNumerator(TEXT("fps_` (scope `IDecoderOutputOptionNames`)
- L39 _variable_ `static const FName FPSDenominator(TEXT("fps_` (scope `IDecoderOutputOptionNames`)
- L40 _variable_ `static const FName PixelDataScale(TEXT("pix_` (scope `IDecoderOutputOptionNames`)
- L41 _variable_ `static const FName Timecode(TEXT("time` (scope `IDecoderOutputOptionNames`)
- L42 _variable_ `static const FName TMCDTimecode(TEXT("tmcd` (scope `IDecoderOutputOptionNames`)
- L43 _variable_ `static const FName TMCDFramerate(TEXT("tmcd` (scope `IDecoderOutputOptionNames`)

### `Plugins/Media/ElectraUtil/Source/ElectraBase/Public/MediaMetaDataDecoderOutput.h` (Public)


#### class `IMetaDataDecoderOutput`  
`class IMetaDataDecoderOutput`  
_L10-53_
- L13 _public prototype_ `virtual ~IMetaDataDecoderOutput() = default;`
- L15 _public prototype_ `virtual const void* GetData() = 0;`
- L16 _public prototype_ `virtual FTimespan GetDuration() const = 0;`
- L17 _public prototype_ `virtual uint32 GetSize() const = 0;`
- L18 _public prototype_ `virtual FDecoderTimeStamp GetTime() const = 0;`
- L34 _public prototype_ `virtual EOrigin GetOrigin() const = 0;` — Returns where the event originated from.
- L37 _public prototype_ `virtual EDispatchedMode GetDispatchedMode() const = 0;` — Returns the type with which this event was dispatched.
- L40 _public prototype_ `virtual const FString& GetSchemeIdUri() const = 0;` — Returns the event's scheme id URI
- L43 _public prototype_ `virtual const FString& GetValue() const = 0;` — Returns the event's value.
- L46 _public prototype_ `virtual const FString& GetID() const = 0;` — Returns the event's ID.
- L50 _public prototype_ `virtual TOptional<FDecoderTimeStamp> GetTrackBaseTime() const = 0;` — Returns the base time (the "zero point") of the track, if available, to calculate the relative time of this metadata from GetTime() if this is based on some non-zero anchor.
- L52 _public prototype_ `virtual void SetTime(FDecoderTimeStamp& InTime) = 0;`

#### enum `IMetaDataDecoderOutput::EOrigin`  
`enum class EOrigin`  
_L20-25_
- L22 _public enumerator_ `EventStream`
- L23 _public enumerator_ `InbandEventStream`
- L24 _public enumerator_ `TimedMetadata`

#### enum `IMetaDataDecoderOutput::EDispatchedMode`  
`enum class EDispatchedMode`  
_L27-31_
- L29 _public enumerator_ `OnReceive`
- L30 _public enumerator_ `OnStart`

#### Free symbols / members of external scopes

- L55 _typedef_ `using IMetaDataDecoderOutputPtr = TSharedPtr<IMetaDataDecoderOutput, ESPMode::ThreadSafe>;`

### `Plugins/Media/ElectraUtil/Source/ElectraBase/Public/MediaSubtitleDecoderOutput.h` (Public)


#### class `ISubtitleDecoderOutput`  
`class ISubtitleDecoderOutput`  
_L10-23_
- L13 _public prototype_ `virtual ~ISubtitleDecoderOutput() = default;`
- L15 _public prototype_ `virtual const TArray<uint8>& GetData() = 0;`
- L16 _public prototype_ `virtual FDecoderTimeStamp GetTime() const = 0;`
- L17 _public prototype_ `virtual FTimespan GetDuration() const = 0;`
- L19 _public prototype_ `virtual const FString& GetFormat() const = 0;`
- L20 _public prototype_ `virtual const FString& GetID() const = 0;`
- L22 _public prototype_ `virtual void SetTime(FDecoderTimeStamp& InTime) = 0;`

#### Free symbols / members of external scopes

- L25 _typedef_ `using ISubtitleDecoderOutputPtr = TSharedPtr<ISubtitleDecoderOutput, ESPMode::ThreadSafe>;`

### `Plugins/Media/ElectraUtil/Source/ElectraBase/Public/MediaURLType.h` (Public)


#### struct `Electra::FMediaURL`  
`struct FMediaURL`  
_L17-46_
- desc: This struct describes a URL used in media streaming. It describes the URL only, along with CDN and priority for content steering, but it DOES NOT and MUST NOT include anything request related, like a content byte range, headers, cookies and so on.
- L22 _public member_ `FString URL;` — The URL itself
- L31 _public member_ `FString CDN;` — The "CDN" this URL is hosted on, if known DASH: @serviceLocation attribute HLS: PATHWAY-ID attribute other: not used
- L36 _public member_ `int32 DVBweight = 1;` — DVB DASH prioritization attributes.
- L37 _public member_ `int32 DVBpriority = 1;`
- L39 _public function_ `void Empty()`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraUtil/Source/ElectraBase/Public/MediaVideoDecoderOutput.h` (Public)


#### class `IVideoDecoderTimecode`  
`class IVideoDecoderTimecode : public TSharedFromThis<IVideoDecoderTimecode, ESPMode::ThreadSafe>`  
_L9-39_
- inherits: `TSharedFromThis<IVideoDecoderTimecode,ESPMode::ThreadSafe>`
- L37 _public prototype_ `virtual ~IVideoDecoderTimecode() = default;`
- L38 _public prototype_ `virtual FMPEGDefinition const* GetMPEGDefinition() const = 0;`

#### struct `IVideoDecoderTimecode::FMPEGDefinition`  
`struct FMPEGDefinition`  
_L12-35_
- L17 _public member_ `int64 clockTimestamp = 0;` — Calculated value as per: clockTimestamp = ( ( hH * 60 + mM ) * 60 + sS ) * time_scale + nFrames * ( num_units_in_tick * ( 1 + nuit_field_based_flag ) ) + tOffset, can only be valid when there is timing information.
- L19 _public member_ `uint32 num_units_in_tick = 0;` — Values from a pic_timing() SEI in H.264 or from a time_code() SEI in H.265
- L20 _public member_ `uint32 time_scale = 0;` — from the SPS
- L21 _public member_ `int32 time_offset = 0;`
- L22 _public member_ `uint16 n_frames = 0;`
- L23 _public member_ `uint8 timing_info_present_flag = 0;` — from the SPS
- L24 _public member_ `uint8 clock_timestamp_flag = 0;`
- L25 _public member_ `uint8 ct_type = 0;`
- L26 _public member_ `uint8 nuit_field_based_flag = 0;`
- L27 _public member_ `uint8 counting_type = 0;`
- L28 _public member_ `uint8 full_timestamp_flag = 0;`
- L29 _public member_ `uint8 discontinuity_flag = 0;`
- L30 _public member_ `uint8 cnt_dropped_flag = 0;`
- L31 _public member_ `uint8 seconds_value = 0;`
- L32 _public member_ `uint8 minutes_value = 0;`
- L33 _public member_ `uint8 hours_value = 0;`
- L34 _public member_ `uint8 FromH26x = 0;` — last digit of the codec this comes from. 4=H.264, 5=H.265, etc. In case values need different interpretation.

#### class `IVideoDecoderColorimetry`  
`class IVideoDecoderColorimetry : public TSharedFromThis<IVideoDecoderColorimetry, ESPMode::ThreadSafe>`  
_L43-57_
- inherits: `TSharedFromThis<IVideoDecoderColorimetry,ESPMode::ThreadSafe>`
- L55 _public prototype_ `virtual ~IVideoDecoderColorimetry() = default;`
- L56 _public prototype_ `virtual FMPEGDefinition const* GetMPEGDefinition() const = 0;`

#### struct `IVideoDecoderColorimetry::FMPEGDefinition`  
`struct FMPEGDefinition`  
_L46-53_
- L48 _public member_ `uint8 ColourPrimaries = 2;`
- L49 _public member_ `uint8 TransferCharacteristics = 2;`
- L50 _public member_ `uint8 MatrixCoefficients = 2;`
- L51 _public member_ `uint8 VideoFullRangeFlag = 0;`
- L52 _public member_ `uint8 VideoFormat = 5;`

#### struct `FVideoDecoderHDRMetadata_mastering_display_colour_volume`  
`struct FVideoDecoderHDRMetadata_mastering_display_colour_volume`  
_L61-70_
- L64 _public member_ `float display_primaries_x[3];` — Index 0=red, 1=green, 2=blue
- L65 _public member_ `float display_primaries_y[3];`
- L66 _public member_ `float white_point_x;`
- L67 _public member_ `float white_point_y;`
- L68 _public member_ `float max_display_mastering_luminance;`
- L69 _public member_ `float min_display_mastering_luminance;`

#### struct `FVideoDecoderHDRMetadata_content_light_level_info`  
`struct FVideoDecoderHDRMetadata_content_light_level_info`  
_L72-76_
- L74 _public member_ `uint16 max_content_light_level = 0;` — MaxCLL
- L75 _public member_ `uint16 max_pic_average_light_level = 0;` — MaxFALL

#### class `IVideoDecoderHDRInformation`  
`class IVideoDecoderHDRInformation : public TSharedFromThis<IVideoDecoderHDRInformation, ESPMode::ThreadSafe>`  
_L80-101_
- inherits: `TSharedFromThis<IVideoDecoderHDRInformation,ESPMode::ThreadSafe>`
- L91 _public prototype_ `virtual ~IVideoDecoderHDRInformation() = default;`
- L94 _public prototype_ `virtual EType GetHDRType() const = 0;` — Returns the type of HDR in use.
- L97 _public prototype_ `virtual const FVideoDecoderHDRMetadata_mastering_display_colour_volume* GetMasteringDisplayColourVolume() const = 0;` — Get mastering display colour volume if available. Returns nullptr if information is not available.
- L100 _public prototype_ `virtual const FVideoDecoderHDRMetadata_content_light_level_info* GetContentLightLevelInfo() const = 0;` — Get content light level info if available. Returns nullptr if information is not available.

#### enum `IVideoDecoderHDRInformation::EType`  
`enum class EType`  
_L83-89_
- L85 _public enumerator_ `Unknown`
- L86 _public enumerator_ `PQ10` — 10 bit HDR, no metadata.
- L87 _public enumerator_ `HDR10` — 10 bit HDR, static metadata (mastering display colour volume + content light level info)
- L88 _public enumerator_ `HLG10` — 10 bit HDR, static metadata (mastering display colour volume + content light level info) (HLG transfer characteristics)

### `Plugins/Media/ElectraUtil/Source/ElectraBase/Public/ParameterDictionary.h` (Public)


#### class `Electra::FVariantValue`  
`class FVariantValue`  
_L21-177_
- L48 _public prototype_ `FVariantValue();`
- L49 _public prototype_ `~FVariantValue();`
- L50 _public prototype_ `FVariantValue(const FVariantValue& rhs);`
- L51 _public prototype_ `FVariantValue& operator=(const FVariantValue& rhs);`
- L53 _public prototype_ `explicit FVariantValue(const FString& StringValue);`
- L54 _public prototype_ `explicit FVariantValue(double DoubleValue);`
- L55 _public prototype_ `explicit FVariantValue(int64 Int64Value);`
- L56 _public prototype_ `explicit FVariantValue(bool BoolValue);`
- L57 _public prototype_ `explicit FVariantValue(const FTimeValue& TimeValue);`
- L58 _public prototype_ `explicit FVariantValue(const FTimespan& TimespanValue);`
- L59 _public prototype_ `explicit FVariantValue(const FTimecode& TimecodeValue);`
- L60 _public prototype_ `explicit FVariantValue(const FFrameRate& FramerateValue);`
- L61 _public prototype_ `explicit FVariantValue(void* PointerValue);`
- L62 _public function_ `template<typename T> explicit FVariantValue(const TSharedPtr<T, ESPMode::ThreadSafe>& PointerValue) : DataType(EDataType::TypeUninitialized)`
- L67 _public prototype_ `explicit FVariantValue(const TArray<uint8>& ArrayValue);`
- L69 _public prototype_ `FVariantValue& Set(const FString& StringValue);`
- L70 _public prototype_ `FVariantValue& Set(double DoubleValue);`
- L71 _public prototype_ `FVariantValue& Set(int64 Int64Value);`
- L72 _public prototype_ `FVariantValue& Set(bool BoolValue);`
- L73 _public prototype_ `FVariantValue& Set(const FTimeValue& TimeValue);`
- L74 _public prototype_ `FVariantValue& Set(const FTimespan& TimespanValue);`
- L75 _public prototype_ `FVariantValue& Set(const FTimecode& TimecodeValue);`
- L76 _public prototype_ `FVariantValue& Set(const FFrameRate& FramerateValue);`
- L77 _public prototype_ `FVariantValue& Set(void* PointerValue);`
- L78 _public function_ `template <typename T> FVariantValue& Set(const TSharedPtr<T, ESPMode::ThreadSafe>& PointerValue)`
- L85 _public prototype_ `FVariantValue& Set(const TArray<uint8>& ArrayValue);`
- L88 _public prototype_ `const FString& GetFString() const;` — Returns variant value. Type *must* match. Otherwise an empty/zero value is returned.
- L89 _public prototype_ `const double& GetDouble() const;`
- L90 _public prototype_ `const int64& GetInt64() const;`
- L91 _public prototype_ `const bool& GetBool() const;`
- L92 _public prototype_ `const FTimeValue& GetTimeValue() const;`
- L93 _public prototype_ `const FTimespan& GetTimespan() const;`
- L94 _public prototype_ `const FTimecode& GetTimecode() const;`
- L95 _public prototype_ `const FFrameRate& GetFramerate() const;`
- L96 _public prototype_ `void* const & GetPointer() const;`
- L97 _public function_ `template<typename T> TSharedPtr<T, ESPMode::ThreadSafe> GetSharedPointer() const`
- L109 _public prototype_ `const TArray<uint8>& GetArray() const;`
- L112 _public prototype_ `const FString& SafeGetFString(const FString& Default = FString()) const;` — Returns variant value. If type does not match the specified default will be returned.
- L113 _public prototype_ `double SafeGetDouble(double Default=0.0) const;`
- L114 _public prototype_ `int64 SafeGetInt64(int64 Default=0) const;`
- L115 _public prototype_ `bool SafeGetBool(bool Default=false) const;`
- L116 _public prototype_ `FTimeValue SafeGetTimeValue(const FTimeValue& Default=FTimeValue()) const;`
- L117 _public prototype_ `FTimespan SafeGetTimespan(const FTimespan& Default=FTimespan()) const;`
- L118 _public prototype_ `FTimecode SafeGetTimecode(const FTimecode& Default=FTimecode()) const;`
- L119 _public prototype_ `FFrameRate SafeGetFramerate(const FFrameRate& Default=FFrameRate()) const;`
- L120 _public prototype_ `void* SafeGetPointer(void* Default=nullptr) const;`
- L121 _public prototype_ `const TArray<uint8>& SafeGetArray() const;`
- L138 _public function_ `EDataType GetDataType() const`
- L143 _public function_ `bool IsValid() const`
- L148 _public function_ `bool IsType(EDataType type) const`
- L153 _public prototype_ `FVariant ToFVariant() const;`
- L172 _private prototype_ `void Clear();`
- L173 _private prototype_ `void CopyInternal(const FVariantValue& FromOther);`
- L175 _private member_ `TAlignedBytes<sizeof(FUnionLayout), 16> DataBuffer;`
- L176 _private member_ `EDataType DataType;`

#### class `Electra::FVariantValue::FSharedPtrHolderBase`  
`class FSharedPtrHolderBase`  
_L23-28_
- L26 _public prototype_ `virtual ~FSharedPtrHolderBase() = default;`
- L27 _public prototype_ `virtual void SetValueOn(FSharedPtrHolderBase* Dst) const = 0;`

#### class `Electra::FVariantValue::TSharedPtrHolder`  
`template<typename T> class TSharedPtrHolder : public FSharedPtrHolderBase`  
_L30-45_
- inherits: `FSharedPtrHolderBase`
- L32 _private typedef_ `using SharedPtrType = TSharedPtr<T, ESPMode::ThreadSafe>;`
- L35 _public function_ `TSharedPtrHolder(const SharedPtrType & InPointer) : Pointer(InPointer)`
- L39 _public member_ `SharedPtrType Pointer;`
- L41 _public function_ `virtual void SetValueOn(FSharedPtrHolderBase* Dst) const override`

#### enum `Electra::FVariantValue::EDataType`  
`enum class EDataType`  
_L123-137_
- L125 _public enumerator_ `TypeUninitialized`
- L126 _public enumerator_ `TypeFString`
- L127 _public enumerator_ `TypeDouble`
- L128 _public enumerator_ `TypeInt64`
- L129 _public enumerator_ `TypeBoolean`
- L130 _public enumerator_ `TypeTimeValue`
- L131 _public enumerator_ `TypeTimespanValue`
- L132 _public enumerator_ `TypeTimecodeValue`
- L133 _public enumerator_ `TypeFramerateValue`
- L134 _public enumerator_ `TypeVoidPointer`
- L135 _public enumerator_ `TypeSharedPointer`
- L136 _public enumerator_ `TypeU8Array`

#### union `Electra::FVariantValue::FUnionLayout`  
`union FUnionLayout`  
_L157-170_
- L159 _public member_ `uint8 MemSizeFString[sizeof(FString)];`
- L160 _public member_ `uint8 MemSizeDouble[sizeof(double)];`
- L161 _public member_ `uint8 MemSizeInt64[sizeof(int64)];`
- L162 _public member_ `uint8 MemSizeVoidPtr[sizeof(void*)];`
- L163 _public member_ `uint8 MemSizeBoolean[sizeof(bool)];`
- L164 _public member_ `uint8 MemSizeTimeValue[sizeof(FTimeValue)];`
- L165 _public member_ `uint8 MemSizeTimespan[sizeof(FTimespan)];`
- L166 _public member_ `uint8 MemSizeTimecode[sizeof(FTimecode)];`
- L167 _public member_ `uint8 MemSizeFramerate[sizeof(FFrameRate)];`
- L168 _public member_ `uint8 MemSizeSharedPtrValue[sizeof(TSharedPtrHolder<uint8>)];`
- L169 _public member_ `uint8 MemSizeTArray[sizeof(TArray<uint8>)];`

#### class `Electra::FParamDict`  
`class FParamDict`  
_L181-202_
- L184 _public function_ `FParamDict()`
- L185 _public prototype_ `FParamDict(const FParamDict& Other);`
- L186 _public prototype_ `FParamDict& operator=(const FParamDict& Other);`
- L187 _public prototype_ `~FParamDict() = default;`
- L188 _public prototype_ `void Clear();`
- L189 _public prototype_ `void Set(const FName& Key, const FVariantValue& Value);`
- L190 _public prototype_ `void Set(const FName& Key, FVariantValue&& Value);`
- L191 _public prototype_ `void GetKeys(TArray<FName>& OutKeys) const;`
- L192 _public prototype_ `bool HaveKey(const FName& Key) const;`
- L193 _public prototype_ `FVariantValue GetValue(const FName& Key) const;`
- L194 _public prototype_ `void Remove(const FName& Key);`
- L195 _public prototype_ `bool SetValueFrom(FName InKey, const FParamDict& InOther);`
- L197 _public prototype_ `void ConvertTo(TMap<FString, FVariant>& OutVariantMap, const FString& InAddPrefixToKey) const;`
- L198 _public prototype_ `void ConvertKeysStartingWithTo(TMap<FString, FVariant>& OutVariantMap, const FString& InKeyStartsWith, const FString& InAddPrefixToKey) const;`
- L200 _private prototype_ `void InternalCopy(const FParamDict& Other);`
- L201 _private member_ `TMap<FName, FVariantValue> Dictionary;`

#### class `Electra::FParamDictTS`  
`class FParamDictTS`  
_L204-289_
- L207 _public function_ `FParamDictTS()`
- L208 _public function_ `FParamDictTS(const FParamDictTS& Other)`
- L212 _public function_ `FParamDictTS& operator=(const FParamDictTS& Other)`
- L221 _public function_ `FParamDictTS& operator=(const FParamDict& Other)`
- L228 _public prototype_ `~FParamDictTS() = default;`
- L230 _public function_ `FParamDict GetDictionary() const`
- L236 _public function_ `void Clear()`
- L241 _public function_ `void Set(const FName& Key, const FVariantValue& Value)`
- L246 _public function_ `void Set(const FName& Key, FVariantValue&& Value)`
- L251 _public function_ `void GetKeys(TArray<FName>& OutKeys) const`
- L256 _public function_ `bool HaveKey(const FName& Key) const`
- L261 _public function_ `FVariantValue GetValue(const FName& Key) const`
- L266 _public function_ `void Remove(const FName& Key)`
- L271 _public function_ `bool SetValueFrom(FName InKey, const FParamDict& InOther)`
- L276 _public function_ `void ConvertTo(TMap<FString, FVariant>& OutVariantMap, const FString& InAddPrefixToKey) const`
- L281 _public function_ `void ConvertKeysStartingWithTo(TMap<FString, FVariant>& OutVariantMap, const FString& InKeyStartsWith, const FString& InAddPrefixToKey) const`
- L287 _private member_ `mutable FCriticalSection Lock;`
- L288 _private member_ `FParamDict Dictionary;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API ELECTRABASE_API`
- L18 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraUtil/Source/ElectraBase/Public/PlayerTime.h` (Public)


#### class `Electra::FTimeValue`  
`class FTimeValue`  
_L16-561_
- desc: Keeps a time value in hundred nanoseconds (HNS).
- L19 _public function_ `static FTimeValue GetInvalid()`
- L25 _public function_ `static FTimeValue GetZero()`
- L31 _public function_ `static FTimeValue GetPositiveInfinity()`
- L37 _public function_ `static FTimeValue GetNegativeInfinity()`
- L43 _public function_ `static int64 MillisecondsToHNS(int64 InMilliseconds)`
- L48 _public function_ `static int64 MicrosecondsToHNS(int64 InMicroseconds)`
- L53 _public function_ `static int64 NinetykHzToHNS(int64 In90kHz)`
- L58 _public function_ `FTimeValue() : HNS(0) , SequenceIndex(0) , bIsValid(false) , bIsInfinity(false)`
- L66 _public function_ `FTimeValue(const FTimeValue& rhs) : HNS(rhs.HNS) , SequenceIndex(rhs.SequenceIndex) , bIsValid(rhs.bIsValid) , bIsInfinity(rhs.bIsInfinity)`
- L74 _public function_ `FTimeValue& operator=(const FTimeValue& rhs)`
- L83 _public function_ `explicit FTimeValue(int64 InHNS, int64 InSequenceIndex=0) : HNS(InHNS), SequenceIndex(InSequenceIndex), bIsValid(true), bIsInfinity(false)`
- L86 _public function_ `explicit FTimeValue(double Seconds, int64 InSequenceIndex=0)`
- L90 _public function_ `explicit FTimeValue(int64 Numerator, uint32 Denominator, int64 InSequenceIndex=0)`
- L95 _public function_ `bool IsValid() const`
- L100 _public function_ `bool IsZero() const`
- L105 _public function_ `bool IsInfinity() const`
- L110 _public function_ `bool IsPositiveInfinity() const`
- L115 _public function_ `bool IsNegativeInfinity() const`
- L121 _public function_ `double GetAsSeconds(double DefaultIfInvalid=0.0) const`
- L126 _public function_ `int64 GetAsMilliseconds(int64 DefaultIfInvalid=0) const`
- L131 _public function_ `int64 GetAsMicroseconds(int64 DefaultIfInvalid=0) const`
- L136 _public function_ `int64 GetAsHNS(int64 DefaultIfInvalid=0) const`
- L141 _public function_ `int64 GetAs90kHz(int64 DefaultIfInvalid=0) const`
- L147 _public prototype_ `int64 GetAsTimebase(uint32 CustomTimebase) const;` — Returns this time value in a custom timebase. Requires internal bigint conversion and is therefor SLOW!
- L149 _public function_ `FTimespan GetAsTimespan() const`
- L162 _public function_ `FTimeValue& SetToInvalid()`
- L171 _public function_ `FTimeValue& SetToZero(int64 InSequenceIndex=0)`
- L180 _public function_ `FTimeValue& SetToPositiveInfinity(int64 InSequenceIndex=0)`
- L189 _public function_ `FTimeValue& SetToNegativeInfinity(int64 InSequenceIndex=0)`
- L198 _public function_ `FTimeValue& SetFromSeconds(double Seconds, int64 InSequenceIndex=0)`
- L222 _public function_ `FTimeValue& SetFromMilliseconds(int64 Milliseconds, int64 InSequenceIndex=0)`
- L238 _public function_ `FTimeValue& SetFromMicroseconds(int64 Microseconds, int64 InSequenceIndex=0)`
- L254 _public function_ `FTimeValue& SetFromHNS(int64 InHNS, int64 InSequenceIndex=0)`
- L263 _public function_ `FTimeValue& SetFrom90kHz(int64 Ticks, int64 InSequenceIndex=0)`
- L272 _public prototype_ `FTimeValue& SetFromND(int64 Numerator, uint32 Denominator, int64 InSequenceIndex=0);`
- L274 _public prototype_ `FTimeValue& SetFromTimeFraction(const FTimeFraction& TimeFraction, int64 InSequenceIndex=0);`
- L277 _public function_ `FTimeValue& SetFromTimespan(const FTimespan& InTimespan, int64 InSequenceIndex=0)`
- L294 _public function_ `void SetSequenceIndex(int64 InSequenceIndex)`
- L299 _public function_ `int64 GetSequenceIndex() const`
- L313 _public function_ `bool operator == (const FTimeValue& rhs) const`
- L318 _public function_ `bool operator != (const FTimeValue& rhs) const`
- L323 _public function_ `bool operator < (const FTimeValue& rhs) const`
- L339 _public function_ `bool operator <= (const FTimeValue& rhs) const`
- L344 _public function_ `bool operator > (const FTimeValue &rhs) const`
- L349 _public function_ `bool operator >= (const FTimeValue &rhs) const`
- L354 _public function_ `inline FTimeValue& operator += (const FTimeValue& rhs)`
- L380 _public function_ `inline FTimeValue& operator -= (const FTimeValue& rhs)`
- L403 _public function_ `inline FTimeValue& operator /= (int32 Scale)`
- L419 _public function_ `inline FTimeValue& operator *= (int32 Scale)`
- L429 _public function_ `inline FTimeValue operator + (const FTimeValue& rhs) const`
- L450 _public function_ `inline FTimeValue operator - (const FTimeValue& rhs) const`
- L468 _public function_ `inline FTimeValue operator << (int32 Shift) const`
- L485 _public function_ `inline FTimeValue operator >> (int32 Shift) const`
- L502 _public function_ `inline FTimeValue operator * (int32 Scale) const`
- L519 _public function_ `inline FTimeValue operator / (int32 Scale) const`
- L533 _public function_ `inline FTimeValue operator - () const`
- L540 _public function_ `inline FTimeValue Abs() const`
- L551 _private function_ `static inline bool WillOverflow(int64& OutTemp, const int64 InA, const int64 InB)`
- L557 _private member_ `int64 HNS;`
- L558 _private member_ `int64 SequenceIndex;`
- L559 _private member_ `bool bIsValid;`
- L560 _private member_ `bool bIsInfinity;`

#### struct `Electra::FTimeRange`  
`struct FTimeRange`  
_L565-589_
- L567 _public function_ `void Reset()`
- L572 _public function_ `bool IsValid() const`
- L577 _public function_ `bool Contains(const FTimeValue& Value)`
- L582 _public function_ `bool Overlaps(const FTimeRange& OtherRange)`
- L587 _public member_ `FTimeValue Start;`
- L588 _public member_ `FTimeValue End;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraUtil/Source/ElectraBase/Public/TimeFraction.h` (Public)


#### class `Electra::FTimeFraction`  
`class FTimeFraction`  
_L15-143_
- desc: Keeps a time value as a fractional.
- L18 _public function_ `static const FTimeFraction& GetInvalid()`
- L24 _public function_ `static const FTimeFraction& GetZero()`
- L30 _public function_ `static const FTimeFraction& GetPositiveInfinity()`
- L36 _public prototype_ `FTimeFraction() = default;`
- L38 _public function_ `FTimeFraction(int64 n, uint32 d) : Numerator(n), Denominator(d), bIsValid(true)`
- L41 _public function_ `FTimeFraction(const FTimeFraction& rhs) : Numerator(rhs.Numerator), Denominator(rhs.Denominator), bIsValid(rhs.bIsValid)`
- L44 _public function_ `FTimeFraction(const FTimespan& tv)`
- L49 _public function_ `FTimeFraction& operator=(const FTimeFraction& rhs)`
- L57 _public function_ `bool IsValid() const`
- L62 _public function_ `bool IsPositiveInfinity() const`
- L67 _public function_ `int64 GetNumerator() const`
- L72 _public function_ `uint32 GetDenominator() const`
- L77 _public function_ `double GetAsDouble() const`
- L83 _public prototype_ `int64 GetAsTimebase(uint32 CustomTimebase) const;` — Returns this time value in a custom timebase. Requires internal bigint conversion and is therefor slow!
- L86 _public prototype_ `FTimespan GetAsTimespan() const;` — Returns this time value as a FTimespan. Requires internal bigint conversion and is therefor slow!
- L88 _public function_ `FTimeFraction& SetFromND(int64 InNumerator, uint32 InDenominator)`
- L96 _public function_ `FTimeFraction& SetNumerator(int64 InNumerator)`
- L103 _public function_ `FTimeFraction& SetDenominator(uint32 InDenominator)`
- L110 _public function_ `FTimeFraction& SetToPositiveInfinity()`
- L118 _public function_ `FTimeFraction& SetFromTimespan(const FTimespan& tv)`
- L126 _public prototype_ `FTimeFraction& SetFromFloatString(const FString& In);`
- L129 _public function_ `bool operator == (const FTimeFraction& rhs) const`
- L134 _public function_ `bool operator != (const FTimeFraction& rhs) const`
- L140 _private member_ `int64 Numerator = 0;`
- L141 _private member_ `uint32 Denominator = 0;`
- L142 _private member_ `bool bIsValid = false;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraUtil/Source/ElectraBase/Public/Utilities/BCP47-Helpers.h` (Public)


#### struct `Electra::BCP47::FLanguageTag`  
`struct FLanguageTag`  
_L17-94_
- desc: A parsed RFC-5646 language tag.
- L20 _public member_ `FString FullLanguage;` — The full language string if it consists of more than just the primary language.
- L22 _public member_ `FString PrimaryLanguage;` — The primary language only.
- L24 _public member_ `FString ExtendedLanguage;` — Any extended language sub parts (up to three) separated by hyphens.
- L26 _public member_ `FString Script;` — The script sub part, if given.
- L28 _public member_ `FString Region;` — The region sub part, if given.
- L30 _public member_ `TArray<FString> Variants;` — The variant sub parts, if given.
- L32 _public member_ `TArray<FString> Extensions;` — The extension sub parts, if given.
- L34 _public member_ `FString PrivateUse;` — The private use part, if given.
- L36 _public function_ `void Empty()`
- L48 _public function_ `FString Get(bool bAddExtended, bool bAddScript, bool bAddRegion, bool bAddVariants, bool bAddExtensions, bool bAddPrivateUse) const`
- L90 _public function_ `FString Get() const`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Electra`
- L11 _namespace_ `namespace BCP47` (scope `Electra`)
- L102 _prototype_ `bool ParseRFC5646Tag(FLanguageTag& OutTag, const FString& InRFC5646);` (scope `Electra::BCP47`) — Parse a single RFC-5646 language tag into its components. This will change the language code to the shorter 2 letter ISO-639-1 code if possible and change the capitalization of the elements to their recommended case. It does NOT canonicalize the tag.
- L129 _prototype_ `TArray<int32> FindExtendedFilteringMatch(const TArray<FLanguageTag>& InTagsToCheck, const FString& InRFC4647Ranges);` (scope `Electra::BCP47`) — Checks an RFC-4647 language priority list for a match against the given language tags through RFC-4647 section 3.3.2 "extended filtering". Returns the indices into the given language tags that match the language priority list. If this filtering produces no match, "lookup" is performed (see RFC-4647 section 3.4) with the following differences: - only language ranges not containing a '*' wildcard are considered because the language range must be parseable as a language tag for element-wise comparison. - instead of progressibely truncating the language range from the end the search is performed forward and stops on the first mismatch. - variants, extensions and private use tags are NOT considered! - there is no "default" value to fall back on. The result list will be empty if lookup fails to produce a match. The point of performing an additional "lookup" step is to return a better-than-nothing result if the language range is over-specified with regard to the given language tags. For example, if the language tag is "es" a filter search with only "es-419" will not return a match. The search should be "es-419,es-*,es" but constructing this is sometimes difficult. This is why a lookup is performed because searching "es-419" will match "es". May be an empty list if there are no matches.

### `Plugins/Media/ElectraUtil/Source/ElectraBase/Public/Utilities/ElectraBitstream.h` (Public)


#### class `Electra::FBitstreamReader`  
`class FBitstreamReader`  
_L15-220_
- L18 _public prototype_ `FBitstreamReader() = default;`
- L20 _public function_ `FBitstreamReader(const void* InData, uint64 InDataSize, uint64 StartBytePosition = 0, uint32 StartBitPosition = 0)`
- L25 _public function_ `FBitstreamReader(const FBitstreamReader& rhs)`
- L33 _public function_ `FBitstreamReader& operator = (const FBitstreamReader& rhs)`
- L42 _public function_ `void SetData(const void* InData, uint64 InDataSize, uint64 StartBytePosition = 0, uint32 StartBitPosition = 0)`
- L51 _public function_ `bool IsByteAligned() const`
- L56 _public function_ `const void* GetRemainingData() const`
- L61 _public function_ `uint64 GetRemainingByteLength() const`
- L66 _public function_ `uint32 GetBytePosition() const`
- L71 _public function_ `uint32 GetBitPosition() const`
- L76 _public function_ `uint64 GetRemainingBits() const`
- L81 _public function_ `bool GetAlignedBytes(uint8* To, uint64 nBytes)`
- L93 _public function_ `void SkipBytes(uint64 nBytes)`
- L102 _public function_ `void SkipBits(uint64 nBits)`
- L108 _public function_ `uint32 GetBits(uint64 nBits)`
- L130 _public function_ `uint32 PeekBits(uint64 nBits)`
- L201 _public function_ `uint64 GetBits64(uint64 nBits)`
- L216 _protected member_ `const uint8* Data = nullptr;`
- L217 _protected member_ `uint64 DataSize = 0;`
- L218 _protected member_ `uint64 BytePosition = 0;`
- L219 _protected member_ `uint32 BitPosition = 0;`

#### struct `Electra::FElectraByteReader`  
`struct FElectraByteReader`  
_L226-277_
- L228 _public function_ `FElectraByteReader(const void* InData, int64 DataSize) : Data((const uint8*)InData) , NumBytesToGo(DataSize)`
- L233 _public function_ `bool ReadByte(uint8& To)`
- L244 _public function_ `bool ReadByte(uint16& To)`
- L257 _public function_ `bool ReadBytes(uint8* To, int64 num)`
- L269 _public function_ `int64 BytesRemaining() const`
- L275 _private member_ `const uint8* Data = nullptr;`
- L276 _private member_ `int64 NumBytesToGo = 0;`

#### class `Electra::FBitstreamWriter`  
`class FBitstreamWriter`  
_L280-357_
- L283 _public function_ `FBitstreamWriter()`
- L287 _public function_ `void PutBits(uint32 InValue, uint32 InNumBits)`
- L298 _public function_ `void PutBits64(uint64 InValue, uint32 InNumBits)`
- L310 _public function_ `void AlignToBytes(uint32 InFillBitsWith)`
- L320 _public function_ `uint32 GetNumBits() const`
- L324 _public function_ `uint32 GetNumBytesUsed() const`
- L328 _public function_ `bool IsByteAligned() const`
- L332 _public function_ `void GetArray(TArray<uint8>& OutArray)`
- L340 _private function_ `void PutBit(uint32 InBit)`
- L354 _private member_ `TArray<uint8> Buffer;`
- L355 _private member_ `uint32 BytePosition = 0;`
- L356 _private member_ `uint32 BitPosition = 0;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraUtil/Source/ElectraBase/Public/Utilities/IElectraBaseDataReader.h` (Public)


#### class `Electra::IBaseDataReader`  
`class IBaseDataReader`  
_L15-73_
- desc: Abstract base class to pass into
- L18 _public prototype_ `virtual ~IBaseDataReader() = default;`
- L31 _public prototype_ `DECLARE_DELEGATE_RetVal(bool, FCancellationCheckDelegate);` — A delegate passed into the read methods through which the reader implementation can call into to see if the read request has been canceled.
- L45 _public prototype_ `virtual int64 ReadData(void* InOutBuffer, int64 InNumBytes, int64 InFromOffset, FCancellationCheckDelegate InCheckCancellationDelegate) = 0;` — This method reads data into the provided buffer from the specified absolute offset. The number of bytes to read should be retrieved unless the end of the file is reached where returning fewer bytes than requested is permitted. Reading more bytes than requested is forbidden since the read buffer may not be large enough to accommodate more bytes than asked for. Negative return values to indicate a problem are defined in `EResult` `EResult::Canceled` may be returned even if the provided cancellation delegate does not indicate cancelation, but the reader implementation has been canceled by other means (like application shutdown, or in case of an implementation reading from the network some other condition).
- L52 _public prototype_ `virtual int64 GetTotalFileSize() = 0;` — This method shall return the total size of the file. If the size is only known after performing the first read, -1 may be returned until the size is known. If the file is unbounded -1 may be returned at all times.
- L59 _public prototype_ `virtual int64 GetCurrentFileOffset() = 0;` — This method shall return the current file offset, which is initially zero unless the file has been opened such that the initial position for this reader is not zero. The return value is the absolute file position the next read would occur at.
- L66 _public prototype_ `virtual bool HasReachedEOF() = 0;` — A convenience method to return `true` when all data has been read. There is no requirement that `GetTotalFileSize()` returns a positive value. This method must return `true` when `ReadData()` would return `EResult::ReachedEOF`.
- L72 _public prototype_ `virtual FString GetLastError() = 0;` — If a read error occurred and `ReadData()` returns `EResult::ReadError` a human-readable message of what caused the error should be returned.

#### enum `Electra::IBaseDataReader::EResult`  
`enum EResult : int64`  
_L20-25_
- L22 _public enumerator_ `ReadError = -1`
- L23 _public enumerator_ `ReachedEOF = -2`
- L24 _public enumerator_ `Canceled = -3`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Electra`
- L31 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FCancellationCheckDelegate);` — A delegate passed into the read methods through which the reader implementation can call into to see if the read request has been canceled.

### `Plugins/Media/ElectraUtil/Source/ElectraBase/Public/Utilities/ISO639-Map.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Electra`
- L11 _namespace_ `namespace ISO639` (scope `Electra`)
- L13 _prototype_ `const TCHAR* Get639_1(const FString& InFrom639_1_2_3);` (scope `Electra::ISO639`)
- L14 _prototype_ `FString MapTo639_1(const FString& InFrom639_1_2_3);` (scope `Electra::ISO639`)
- L16 _prototype_ `FString RFC5646To639_1(const FString& InFromRFC5646);` (scope `Electra::ISO639`)

### `Plugins/Media/ElectraUtil/Source/ElectraBase/Public/Utilities/StringHelpers.h` (Public)


#### class `Electra::StringHelpers::FStringIterator`  
`class FStringIterator`  
_L43-152_
- desc: There is a known anomaly in the FString::TConstIterator. It iterates all TCHARs in the string *including* the terminating zero character. This is not the behaviour we want and setup some helper iterator here which is not including the terminating zero.
- L46 _public function_ `FStringIterator(const FString& InString, int32 StartIndex = 0) : StringToIterate(InString) , Index(StartIndex)`
- L53 _public function_ `FStringIterator& operator++()` — Advances iterator to the next element in the container.
- L58 _public function_ `FStringIterator operator++(int)`
- L66 _public function_ `FStringIterator& operator--()` — Moves iterator to the previous element in the container.
- L71 _public function_ `FStringIterator operator--(int)`
- L79 _public function_ `FStringIterator& operator+=(int32 Offset)` — iterator arithmetic support
- L85 _public function_ `FStringIterator operator+(int32 Offset) const`
- L91 _public function_ `FStringIterator& operator-=(int32 Offset)`
- L96 _public function_ `FStringIterator operator-(int32 Offset) const`
- L102 _public function_ `const TCHAR& operator* () const`
- L107 _public function_ `const TCHAR* operator->() const`
- L113 _public function_ `FORCEINLINE explicit operator bool() const` — conversion to "bool" returning true if the iterator has not reached the last element.
- L118 _public function_ `const TCHAR* GetRemainder() const`
- L123 _public function_ `int32 GetRemainingLength() const`
- L129 _public function_ `int32 GetIndex() const` — Returns an index to the current element.
- L135 _public function_ `void Reset()` — Resets the iterator to the first element.
- L141 _public function_ `void SetToEnd()` — Sets iterator to the last element.
- L150 _private member_ `const FString& StringToIterate;`
- L151 _private member_ `int32 Index;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Electra`
- L11 _function_ `inline void LexFromStringHex(int32& OutValue, const TCHAR* Buffer)` (scope `Electra`)
- L12 _function_ `inline void LexFromStringHex64(int64& OutValue, const TCHAR* Buffer)` (scope `Electra`)
- L13 _function_ `inline void LexFromStringHexU64(uint64& OutValue, const TCHAR* Buffer)` (scope `Electra`)
- L15 _namespace_ `namespace StringHelpers` (scope `Electra`)
- L17 _prototype_ `FString ISO_8859_1_ToFString(const uint8* InStringToConvert, int32 InNumCharsToConvert=-1);` (scope `Electra::StringHelpers`)
- L19 _prototype_ `int32 FindFirstOf(const FString& InString, const FString& SplitAt, int32 FirstPos = 0);` (scope `Electra::StringHelpers`)
- L21 _prototype_ `int32 FindFirstNotOf(const FString& InString, const FString& InNotOfChars, int32 FirstPos = 0);` (scope `Electra::StringHelpers`)
- L23 _prototype_ `int32 FindLastNotOf(const FString& InString, const FString& InNotOfChars, int32 StartPos = MAX_int32);` (scope `Electra::StringHelpers`)
- L25 _prototype_ `void SplitByDelimiter(TArray<FString>& OutSplits, const FString& InString, const FString& SplitAt);` (scope `Electra::StringHelpers`)
- L27 _prototype_ `bool StringEquals(const TCHAR * const s1, const TCHAR * const s2);` (scope `Electra::StringHelpers`)
- L29 _prototype_ `bool StringStartsWith(const TCHAR * const s1, const TCHAR * const s2, SIZE_T n);` (scope `Electra::StringHelpers`)
- L31 _prototype_ `void StringToArray(TArray<uint8>& OutArray, const FString& InString);` (scope `Electra::StringHelpers`)
- L33 _prototype_ `FString ArrayToString(const TArray<uint8>& InArray);` (scope `Electra::StringHelpers`)
- L35 _prototype_ `bool ArrayToString(FString& OutString, const TConstArrayView<const uint8>& InArray);` (scope `Electra::StringHelpers`)
- L37 _prototype_ `FString GetLongestCommonPrefix(TArray<FString>& InOutTempArrayOfInputs);` (scope `Electra::StringHelpers`)
- L146 _function_ `FORCEINLINE friend bool operator==(const FStringIterator& Lhs, const FStringIterator& Rhs)` (scope `Electra::StringHelpers`)
- L147 _function_ `FORCEINLINE friend bool operator!=(const FStringIterator& Lhs, const FStringIterator& Rhs)` (scope `Electra::StringHelpers`)

### `Plugins/Media/ElectraUtil/Source/ElectraBase/Public/Utilities/TimeUtilities.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Electra`
- L12 _namespace_ `namespace ISO8601` (scope `Electra`)
- L14 _prototype_ `bool ParseDateTime(FTimeValue& OutTimeValue, const FString& DateTime);` (scope `Electra::ISO8601`)
- L15 _prototype_ `bool ParseDuration(FTimeValue& OutTimeValue, const TCHAR* InDuration);` (scope `Electra::ISO8601`)
- L18 _namespace_ `namespace RFC7231` (scope `Electra`)
- L20 _prototype_ `bool ParseDateTime(FTimeValue& OutTimeValue, const FString& DateTime);` (scope `Electra::RFC7231`)
- L23 _namespace_ `namespace RFC2326` (scope `Electra`)
- L25 _prototype_ `bool ParseNPTTime(FTimeValue& OutTimeValue, const FString& NPTtime);` (scope `Electra::RFC2326`)
- L28 _namespace_ `namespace UnixEpoch` (scope `Electra`)
- L30 _prototype_ `bool ParseFloatString(FTimeValue& OutTimeValue, const FString& Seconds);` (scope `Electra::UnixEpoch`)
- L33 _namespace_ `namespace RFC5905` (scope `Electra`)
- L35 _prototype_ `bool ParseNTPTime(FTimeValue& OutTimeValue, uint64 NtpTimestampFormat);` (scope `Electra::RFC5905`)

### `Plugins/Media/ElectraUtil/Source/ElectraBase/Public/Utilities/URLParser.h` (Public)


#### class `Electra::FURL_RFC3986`  
`class FURL_RFC3986`  
_L16-132_
- L20 _public prototype_ `bool Parse(const FString& InURL);` — Parses the given URL.
- L22 _public prototype_ `FString GetScheme() const;` — Returns the scheme, if present. Does not include the :// sequence.
- L24 _public prototype_ `FString GetHost() const;` — Returns the host, if present.
- L26 _public prototype_ `FString GetPort() const;` — Returns the port, if present.
- L28 _public prototype_ `FString GetPath() const;` — Returns the path. Escape sequences will already be decoded.
- L30 _public prototype_ `FString GetQuery() const;` — Returns the entire query string, if any, without the leading '?'. Escape sequences will still be present!
- L32 _public prototype_ `FString GetFragment() const;` — Returns the fragment, if any, without the leading '#'. Escape sequences will already be decoded.
- L34 _public prototype_ `FString Get(bool bIncludeQuery=true, bool bIncludeFragment=true);` — Returns the full URL with or without query and fragment parts. Characters will be escaped if necessary.
- L36 _public prototype_ `FString GetPath(bool bIncludeQuery, bool bIncludeFragment);` — Returns the path (no scheme or host) with or without query and fragment parts. Characters will be escaped if necessary.
- L38 _public prototype_ `bool IsAbsolute() const;` — Returns whether or not this URL is absolute (the scheme not being empty).
- L40 _public prototype_ `bool GetPathComponents(TArray<FString>& OutPathComponents) const;` — Returns the path as individual components. Like GetPath() the components will have escape sequences already decoded.
- L42 _public prototype_ `FString GetLastPathComponent() const;` — Returns the last path component (the "filename").
- L44 _public prototype_ `void ResolveWith(const FURL_RFC3986& Other);` — Resolves the given (relative) URL against this one, which will be modified.
- L46 _public prototype_ `FURL_RFC3986& ResolveWith(const FString& InChildURL);` — Resolves a relative URL against this one.
- L48 _public prototype_ `FURL_RFC3986& ResolveAgainst(const FString& InParentURL);` — Resolves this URL (which should be relative) against the specified URL.
- L51 _public prototype_ `bool MakeRelativePath(FString& OutRelativePath, const FString& InAbsoluteURLToMakeRelativeToThis) const;` — Attempts to make an absolute URL relative to this one.
- L53 _public prototype_ `void SetScheme(const FString& InNewScheme);`
- L54 _public prototype_ `void SetHost(const FString& InNewHost);`
- L55 _public prototype_ `void SetPort(const FString& InNewPort);`
- L56 _public prototype_ `void SetPath(const FString& InNewPath);`
- L57 _public prototype_ `void SetQuery(const FString& InNewQuery);`
- L58 _public prototype_ `void SetFragment(const FString& InNewFragment);`
- L61 _public prototype_ `bool HasSameOriginAs(const FURL_RFC3986& Other);` — Returns if this URL has the same origin as another one as per RFC 6454.
- L69 _public prototype_ `void GetQueryParams(TArray<FQueryParam>& OutQueryParams, bool bPerformUrlDecoding, bool bSameNameReplacesValue=true);` — Returns the query parameters as a list of name/value pairs.
- L72 _public prototype_ `static void GetQueryParams(TArray<FQueryParam>& OutQueryParams, const FString& InQueryParameters, bool bPerformUrlDecoding, bool bSameNameReplacesValue=true);` — Returns the given query parameter string as a list of name/value pairs. The parameter string MUST NOT start with a '?'.
- L75 _public prototype_ `void SetQueryParams(const TArray<FQueryParam>& InQueryParams);` — Replaces query parameters in the URL.
- L78 _public prototype_ `void AddOrUpdateQueryParams(const TArray<FQueryParam>& InQueryParams);` — Updates existing parameters with new value or adds new parameters.
- L79 _public prototype_ `void AddOrUpdateQueryParams(const FString& InQueryParameters);`
- L82 _public prototype_ `static bool UrlDecode(FString& OutResult, const FString& InUrlToDecode);` — Decodes %XX escaped sequences into their original characters. Appends to the output. Hence in and out must not be the same.
- L86 _public prototype_ `static bool UrlEncode(FString& OutResult, const FString& InUrlToEncode, const FString& InCharsToKeep);` — Encodes characters not permitted in a URL into %XX escaped sequences. Appends to the output. Hence in and out must not be the same. A list of characters that should NOT be escaped, even if they normally would, can be passed. These characters must be strictly ASCII characters only. This is useful to prevent '/' path delimiters to be escaped if the string to be encoded represents a path.
- L89 _public prototype_ `static FString GetStandardPortForScheme(const FString& InScheme, bool bIgnoreCase=true);` — Returns the standard port for the given scheme. An empty string is returned if none is known.
- L93 _public prototype_ `static FString GetUrlEncodeSubDelimsChars();` — Returns a string containing the "sub-delims" chars that are permitted in the query string that do not need to be escaped.
- L96 _private member_ `FString Scheme;`
- L97 _private member_ `FString UserInfo;`
- L98 _private member_ `FString Host;`
- L99 _private member_ `FString Port;`
- L100 _private member_ `FString Path;`
- L101 _private member_ `FString Query;`
- L102 _private member_ `FString Fragment;`
- L103 _private member_ `bool bIsFile = false;`
- L104 _private member_ `bool bIsData = false;`
- L106 _private prototype_ `static void GetPathComponents(TArray<FString>& OutPathComponents, const FString& InPath);`
- L108 _private prototype_ `void Empty();`
- L109 _private prototype_ `void Swap(FURL_RFC3986& Other);`
- L110 _private function_ `inline bool IsColonSeparator(TCHAR c)`
- L112 _private function_ `inline bool IsPathSeparator(TCHAR c)`
- L114 _private function_ `inline bool IsQuerySeparator(TCHAR c)`
- L116 _private function_ `inline bool IsFragmentSeparator(TCHAR c)`
- L118 _private function_ `inline bool IsQueryOrFragmentSeparator(TCHAR c)`
- L121 _private prototype_ `bool ParseAuthority(StringHelpers::FStringIterator& it);`
- L122 _private prototype_ `bool ParseHostAndPort(StringHelpers::FStringIterator& it);`
- L123 _private prototype_ `bool ParsePathAndQueryFragment(StringHelpers::FStringIterator& it);`
- L124 _private prototype_ `bool ParsePath(StringHelpers::FStringIterator& it);`
- L125 _private prototype_ `bool ParseQuery(StringHelpers::FStringIterator& it);`
- L126 _private prototype_ `bool ParseFragment(StringHelpers::FStringIterator& it);`
- L128 _private prototype_ `FString GetAuthority() const;`
- L129 _private prototype_ `void BuildPathFromSegments(const TArray<FString>& Components, bool bAddLeadingSlash, bool bAddTrailingSlash);`
- L130 _private prototype_ `void MergePath(const FString& InPathToMerge);`
- L131 _private prototype_ `void RemoveDotSegments();`

#### struct `Electra::FURL_RFC3986::FQueryParam`  
`struct FQueryParam`  
_L63-67_
- L65 _public member_ `FString Name;`
- L66 _public member_ `FString Value;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ELECTRABASE_API`
- L13 _namespace_ `namespace Electra`

### `Plugins/Media/ElectraUtil/Source/ElectraBase/Public/Utilities/Utilities.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Electra`
- L11 _function_ `template <typename T, typename C> T AdvancePointer(T pPointer, C numBytes)` (scope `Electra`) — Advance a pointer by a number of bytes.
- L16 _namespace_ `namespace Utils` (scope `Electra`)
- L19 _function_ `template <typename T> inline T AbsoluteValue(T Value)` (scope `Electra::Utils`)
- L25 _function_ `template <typename T> inline T Min(T a, T b)` (scope `Electra::Utils`)
- L31 _function_ `template <typename T> inline T Max(T a, T b)` (scope `Electra::Utils`)
- L36 _function_ `inline uint32 BitReverse32(uint32 InValue)` (scope `Electra::Utils`)
- L47 _function_ `inline uint16 EndianSwap(uint16 value)` (scope `Electra::Utils`)
- L51 _function_ `inline int16 EndianSwap(int16 value)` (scope `Electra::Utils`)
- L55 _function_ `inline uint32 EndianSwap(uint32 value)` (scope `Electra::Utils`)
- L59 _function_ `inline int32 EndianSwap(int32 value)` (scope `Electra::Utils`)
- L63 _function_ `inline uint64 EndianSwap(uint64 value)` (scope `Electra::Utils`)
- L67 _function_ `inline int64 EndianSwap(int64 value)` (scope `Electra::Utils`)
- L72 _function_ `inline constexpr uint32 Make4CC(const uint8 A, const uint8 B, const uint8 C, const uint8 D)` (scope `Electra::Utils`)

### `Plugins/Media/ElectraUtil/Source/ElectraBase/Public/Utilities/UtilsMPEG.h` (Public)


#### class `Electra::MPEG::FESDescriptor`  
`class FESDescriptor`  
_L14-82_
- L17 _public prototype_ `FESDescriptor();`
- L18 _public prototype_ `void SetRawData(const void* Data, int64 Size);`
- L19 _public prototype_ `const TArray<uint8>& GetRawData() const;`
- L21 _public prototype_ `bool Parse();`
- L23 _public prototype_ `const TArray<uint8>& GetCodecSpecificData() const;`
- L25 _public function_ `uint32 GetBufferSize() const`
- L30 _public function_ `uint32 GetMaxBitrate() const`
- L35 _public function_ `uint32 GetAvgBitrate() const`
- L59 _public function_ `FObjectTypeID GetObjectTypeID() const`
- L64 _public function_ `FStreamType GetStreamType() const`
- L70 _private member_ `TArray<uint8> RawData;`
- L72 _private member_ `TArray<uint8> CodecSpecificData;`
- L73 _private member_ `FObjectTypeID ObjectTypeID;`
- L74 _private member_ `FStreamType StreamTypeID;`
- L75 _private member_ `uint32 BufferSize;`
- L76 _private member_ `uint32 MaxBitrate;`
- L77 _private member_ `uint32 AvgBitrate;`
- L78 _private member_ `uint16 ESID;`
- L79 _private member_ `uint16 DependsOnStreamESID;`
- L80 _private member_ `uint8 StreamPriority;`
- L81 _private member_ `bool bDependsOnStream;`

#### enum `Electra::MPEG::FESDescriptor::FObjectTypeID`  
`enum class FObjectTypeID`  
_L41-51_
- desc: See http://mp4ra.org/#/object_types
- L43 _public enumerator_ `Unknown = 0`
- L44 _public enumerator_ `Text_Stream = 8`
- L45 _public enumerator_ `MPEG4_Video = 0x20`
- L46 _public enumerator_ `H264 = 0x21`
- L47 _public enumerator_ `H264_ParameterSets = 0x22`
- L48 _public enumerator_ `H265 = 0x23`
- L49 _public enumerator_ `MPEG4_Audio = 0x40`
- L50 _public enumerator_ `MPEG1_Audio = 0x6b`

#### enum `Electra::MPEG::FESDescriptor::FStreamType`  
`enum class FStreamType`  
_L52-57_
- L54 _public enumerator_ `Unknown = 0`
- L55 _public enumerator_ `VisualStream = 4`
- L56 _public enumerator_ `AudioStream = 5`

#### class `Electra::MPEG::FID3V2Metadata`  
`class FID3V2Metadata`  
_L86-106_
- L97 _public prototype_ `bool Parse(const uint8* InData, int64 InDataSize);`
- L98 _public prototype_ `bool HaveTag(uint32 InTag);`
- L99 _public prototype_ `bool GetTag(FItem& OutValue, uint32 InTag);`
- L100 _public prototype_ `const TMap<uint32, FItem>& GetTags() const;`
- L101 _public prototype_ `TMap<uint32, FItem>& GetTags();`
- L102 _public prototype_ `const TArray<FItem>& GetPrivateItems() const;`
- L104 _private member_ `TMap<uint32, FItem> Tags;`
- L105 _private member_ `TArray<FItem> PrivateItems;`

#### struct `Electra::MPEG::FID3V2Metadata::FItem`  
`struct FItem`  
_L89-95_
- L91 _public member_ `FString Language;` — ISO 639-2; if not set (all zero) the default entry for all languages
- L92 _public member_ `FString MimeType;` — Mime type or Owner ID for private item.
- L93 _public member_ `FVariant Value;`
- L94 _public member_ `int32 ItemType = -1;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ELECTRABASE_API`
- L10 _namespace_ `namespace Electra`
- L12 _namespace_ `namespace MPEG` (scope `Electra`)
