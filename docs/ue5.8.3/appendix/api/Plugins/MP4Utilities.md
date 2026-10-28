# Plugins / MP4Utilities

- module root: `Plugins/Media/MP4Utilities/Source/MP4Utilities`
- headers: 4; symbols: 116
- symbol kinds: class=7, delegate=2, enum=2, enumerator=6, function=28, macro=3, member=17, namespace=3, prototype=46, struct=2
- PrivateDependencyModuleNames: Core, Media

### `Plugins/Media/MP4Utilities/Source/MP4Utilities/Private/MP4UtilitiesModule.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMP4Utilities, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMP4Utilities, Log, All);`

### `Plugins/Media/MP4Utilities/Source/MP4Utilities/Public/MP4DataReader.h` (Public)


#### class `MP4Utilities::IMP4DataReaderBase`  
`class IMP4DataReaderBase`  
_L20-78_
- desc: Abstract base class to read data from an mp4 file.
- L23 _public prototype_ `virtual ~IMP4DataReaderBase() = default;`
- L36 _public prototype_ `DECLARE_DELEGATE_RetVal(bool, FCancellationCheckDelegate);` — A delegate passed into the read methods through which the reader implementation can call into to see if the read request has been canceled.
- L50 _public prototype_ `virtual int64 ReadData(void* InOutBuffer, int64 InNumBytes, int64 InFromOffset, FCancellationCheckDelegate InCheckCancellationDelegate) = 0;` — This method reads data into the provided buffer from the specified absolute offset. The number of bytes to read should be retrieved unless the end of the file is reached where returning fewer bytes than requested is permitted. Reading more bytes than requested is forbidden since the read buffer may not be large enough to accommodate more bytes than asked for. Negative return values to indicate a problem are defined in `EResult` `EResult::Canceled` may be returned even if the provided cancellation delegate does not indicate cancelation, but the reader implementation has been canceled by other means (like application shutdown, or in case of an implementation reading from the network some other condition).
- L57 _public prototype_ `virtual int64 GetTotalFileSize() = 0;` — This method shall return the total size of the file. If the size is only known after performing the first read, -1 may be returned until the size is known. If the file is unbounded -1 may be returned at all times.
- L64 _public prototype_ `virtual int64 GetCurrentFileOffset() = 0;` — This method shall return the current file offset, which is initially zero unless the file has been opened such that the initial position for this reader is not zero. The return value is the absolute file position the next read would occur at.
- L71 _public prototype_ `virtual bool HasReachedEOF() = 0;` — A convenience method to return `true` when all data has been read. There is no requirement that `GetTotalFileSize()` returns a positive value. This method must return `true` when `ReadData()` would return `EResult::ReachedEOF`.
- L77 _public prototype_ `virtual FString GetLastError() = 0;` — If a read error occurred and `ReadData()` returns `EResult::ReadError` a human-readable message of what caused the error should be returned.

#### enum `MP4Utilities::IMP4DataReaderBase::EResult`  
`enum EResult : int64`  
_L25-30_
- L27 _public enumerator_ `ReadError = -1`
- L28 _public enumerator_ `ReachedEOF = -2`
- L29 _public enumerator_ `Canceled = -3`

#### class `MP4Utilities::FMP4FileDataReader`  
`class FMP4FileDataReader : public IMP4DataReaderBase`  
_L82-88_
- inherits: `IMP4DataReaderBase`
- L85 _public prototype_ `static TSharedPtr<FMP4FileDataReader, ESPMode::ThreadSafe> Create();`
- L86 _public prototype_ `virtual ~FMP4FileDataReader() = default;`
- L87 _public prototype_ `virtual bool Open(const FString& InFilename) = 0;`

#### class `MP4Utilities::FMP4BufferDataReader`  
`class FMP4BufferDataReader : public IMP4DataReaderBase`  
_L92-97_
- inherits: `IMP4DataReaderBase`
- L95 _public prototype_ `static TSharedPtr<FMP4BufferDataReader, ESPMode::ThreadSafe> Create(TConstArrayView<const uint8> InData);`
- L96 _public prototype_ `virtual ~FMP4BufferDataReader() = default;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MP4UTILITIES_API`
- L14 _namespace_ `namespace MP4Utilities`
- L36 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FCancellationCheckDelegate);` — A delegate passed into the read methods through which the reader implementation can call into to see if the read request has been canceled.

### `Plugins/Media/MP4Utilities/Source/MP4Utilities/Public/MP4Metadata.h` (Public)


#### class `MP4Utilities::FMP4MetadataParser`  
`class FMP4MetadataParser`  
_L24-51_
- desc: This class parses metadata embedded in an ISO/IEC 14496-12 file. Presently only the structure as used and defined by Apple iTunes is supported.
- L27 _public prototype_ `FMP4MetadataParser();`
- L34 _public prototype_ `EResult Parse(uint32 InHandler, uint32 InHandlerReserved0, const TArray<FMP4BoxInfo>& InBoxes);`
- L35 _public prototype_ `bool IsDifferentFrom(const FMP4MetadataParser& Other);`
- L36 _public prototype_ `FString GetAsJSON() const;`
- L37 _public prototype_ `TSharedPtr<TMap<FString, TArray<TUniquePtr<IMediaMetadataItem>>>, ESPMode::ThreadSafe> GetMediaStreamMetadata() const;`
- L39 _public prototype_ `void AddItem(const FString& InType, const FString& InValue);`
- L40 _public prototype_ `void AddItem(const FString& InType, const FString& InMimeType, const TArray<uint8>& InValue);`
- L44 _private prototype_ `FString PrintableBoxAtom(const uint32 InAtom);`
- L45 _private prototype_ `void Parse(const FMP4BoxInfo& InBox);`
- L46 _private prototype_ `void ParseBoxDataList(const FString& AsCategory, TConstArrayView<uint8> InBoxData);`
- L47 _private prototype_ `void ParseBoxDataiTunes(TConstArrayView<uint8> InBoxData);`
- L49 _private member_ `TSharedPtr<TMap<FString, TArray<TUniquePtr<IMediaMetadataItem>>>, ESPMode::ThreadSafe> Items;`
- L50 _private member_ `uint32 NumTotalItems = 0;`

#### enum `MP4Utilities::FMP4MetadataParser::EResult`  
`enum class EResult`  
_L28-33_
- L30 _public enumerator_ `Success`
- L31 _public enumerator_ `NotSupported`
- L32 _public enumerator_ `MissingBox`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API MP4UTILITIES_API`
- L18 _namespace_ `namespace MP4Utilities`

### `Plugins/Media/MP4Utilities/Source/MP4Utilities/Public/MP4Utilities.h` (Public)


#### struct `MP4Utilities::FMP4BoxInfo`  
`struct FMP4BoxInfo`  
_L85-106_
- L87 _public member_ `TConstArrayView<uint8> Data;`
- L88 _public member_ `uint8 UUID[16] {};`
- L89 _public member_ `int64 Size = 0;`
- L90 _public member_ `int64 Offset = 0;`
- L91 _public member_ `uint32 Type = 0;`
- L92 _public member_ `uint32 DataOffset = 0;`
- L94 _public member_ `char Name[5]{0};`
- L96 _public function_ `TArray<uint8> GetBoxDataRAW() const`

#### struct `MP4Utilities::FMP4BoxData`  
`struct FMP4BoxData : public FMP4BoxInfo`  
_L112-115_
- inherits: `FMP4BoxInfo`
- desc: Box information along with the actual box data to be retained in memory.
- L114 _public member_ `TArray<uint8> DataBuffer;`

#### class `MP4Utilities::FMP4AtomReader`  
`class FMP4AtomReader`  
_L123-171_
- L126 _public prototype_ `FMP4AtomReader(const TConstArrayView<uint8>& InData);`
- L128 _public prototype_ `bool ParseIntoBoxInfo(FMP4BoxInfo& OutBoxInfo, int64 InAtFileOffset);`
- L130 _public prototype_ `int64 GetCurrentOffset() const;`
- L131 _public prototype_ `int64 GetNumBytesRemaining() const;`
- L132 _public prototype_ `const uint8* GetCurrentDataPointer() const;`
- L133 _public prototype_ `void SetCurrentOffset(int64 InNewOffset);`
- L136 _public function_ `template <typename T> bool Read(T& OutValue)`
- L148 _public prototype_ `bool ReadVersionAndFlags(uint8& OutVersion, uint32& OutFlags);`
- L149 _public prototype_ `bool ReadString(FString& OutString, uint16 InNumBytes);`
- L150 _public prototype_ `bool ReadStringUTF8(FString& OutString, int32 InNumBytes);`
- L151 _public prototype_ `bool ReadStringUTF16(FString& OutString, int32 InNumBytes);`
- L152 _public prototype_ `bool ReadNullTerminatedStringUTF8(FString& OutString);`
- L153 _public prototype_ `bool ReadBytes(void* OutBuffer, int32 InNumBytes);`
- L154 _public prototype_ `bool ReadAsNumber(int64& OutValue, int32 InNumBytes);`
- L155 _public prototype_ `bool ReadAsNumber(uint64& OutValue, int32 InNumBytes);`
- L156 _public prototype_ `bool ReadAsNumber(float& OutValue);`
- L157 _public prototype_ `bool ReadAsNumber(double& OutValue);`
- L158 _public function_ `bool SkipBytes(int32 InNumBytes)`
- L164 _private function_ `template <typename T> T ValueFromBigEndian(const T value)`
- L166 _private prototype_ `int32 ReadData(void* IntoBuffer, int32 NumBytesToRead);`
- L168 _private member_ `const uint8* DataPtr = nullptr;`
- L169 _private member_ `int64 DataSize = 0;`
- L170 _private member_ `int64 CurrentOffset = 0;`

#### class `MP4Utilities::FMP4BoxLocator`  
`class FMP4BoxLocator`  
_L174-193_
- L177 _public prototype_ `FMP4BoxLocator() = default;`
- L178 _public prototype_ `~FMP4BoxLocator() = default;`
- L180 _public function_ `bool LocateAndReadRootBoxes(TArray<TSharedPtr<FMP4BoxData, ESPMode::ThreadSafe>>& OutBoxInfos, const TSharedPtr<IMP4DataReaderBase, ESPMode::ThreadSafe>& InDataReader, const TArray<uint32>& InFirstBoxes, const TArray<uint32>& InStopAfterBoxes, bool bStopWithMDAT, const TArray<uint32>& InReadDataOfBoxes, IMP4DataReaderBase::FCancellationCheckDelegate InCheckCancellationDelegate)`
- L182 _public function_ `FString GetLastError() const`
- L185 _public function_ `static bool LocateAndReadRootBoxesFromBuffer(TArray<TSharedPtr<FMP4BoxData, ESPMode::ThreadSafe>>& OutBoxInfos, TConstArrayView<const uint8> InData)`
- L187 _public function_ `static bool LocateAndReadBoxesFromBuffer(TArray<TSharedPtr<FMP4BoxData, ESPMode::ThreadSafe>>& OutBoxInfos, TConstArrayView<const uint8> InData)`
- L190 _private prototype_ `bool LocateAndReadRootBoxesInternal(TArray<TSharedPtr<FMP4BoxData, ESPMode::ThreadSafe>>& OutBoxInfos, const TSharedPtr<IMP4DataReaderBase, ESPMode::ThreadSafe>& InDataReader, const TArray<uint32>& InFirstBoxes, const TArray<uint32>& InStopAfterBoxes, bool bStopWithMDAT, bool bCheckWellKnown, const TArray<uint32>& InReadDataOfBoxes, IMP4DataReaderBase::FCancellationCheckDelegate InCheckCancellationDelegate);`
- L191 _private member_ `FString LastError;`
- L192 _private member_ `int64 CurrentOffset = 0;`

#### class `MP4Utilities::FFractionalTime`  
`class FFractionalTime`  
_L225-251_
- L228 _public prototype_ `FFractionalTime() = default;`
- L229 _public function_ `FFractionalTime(int64 n, uint32 d) : Numerator(n), Denominator(d)`
- L231 _public function_ `void SetFromND(int64 InNumerator, uint32 InDenominator)`
- L236 _public function_ `bool IsValid() const`
- L238 _public function_ `int64 GetNumerator() const`
- L240 _public function_ `uint32 GetDenominator() const`
- L242 _public function_ `void SetNumerator(int64 InNumerator)`
- L244 _public function_ `FTimespan GetAsTimespan() const`
- L246 _public function_ `int64 GetAsTimebase(uint32 CustomTimebase) const`
- L249 _private member_ `int64 Numerator = 0;`
- L250 _private member_ `uint32 Denominator = 0;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API MP4UTILITIES_API`
- L17 _namespace_ `namespace MP4Utilities`
- L20 _function_ `static constexpr uint8 GetFromBigEndian(uint8 value)` (scope `MP4Utilities`)
- L21 _function_ `static constexpr int8 GetFromBigEndian(int8 value)` (scope `MP4Utilities`)
- L22 _function_ `static constexpr uint16 GetFromBigEndian(uint16 value)` (scope `MP4Utilities`)
- L23 _function_ `static constexpr int16 GetFromBigEndian(int16 value)` (scope `MP4Utilities`)
- L24 _function_ `static constexpr int32 GetFromBigEndian(int32 value)` (scope `MP4Utilities`)
- L25 _function_ `static constexpr uint32 GetFromBigEndian(uint32 value)` (scope `MP4Utilities`)
- L26 _function_ `static constexpr int64 GetFromBigEndian(int64 value)` (scope `MP4Utilities`)
- L27 _function_ `static constexpr uint64 GetFromBigEndian(uint64 value)` (scope `MP4Utilities`)
- L46 _function_ `static constexpr uint32 MakeBoxAtom(const uint8 A, const uint8 B, const uint8 C, const uint8 D)` (scope `MP4Utilities`)
- L51 _function_ `static FString GetPrintableBoxAtom(uint32 InAtom)` (scope `MP4Utilities`)
- L65 _function_ `static FString Printable4CC(const uint32 In4CC)` (scope `MP4Utilities`)
- L120 _prototype_ `TSharedPtr<FMP4BoxData, ESPMode::ThreadSafe> CreateBoxDataFromBuffer(TConstArrayView<uint8> InBoxDataBuffer, int64 InBoxDataFileOffset);` (scope `MP4Utilities`) — Create an FMP4BoxData from a transient data buffer. The data is copied into the FMP4BoxData. If the box data fails to be recognized as an mp4 box a nullptr is returned.
- L199 _function_ `static int64 ConvertToTimescale(uint32 InTargetDenominator, int64 InSourceNumerator, uint32 InSourceDenominator)` (scope `MP4Utilities`)
