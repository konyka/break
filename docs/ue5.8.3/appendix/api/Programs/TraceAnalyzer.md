# Programs / TraceAnalyzer

- module root: `Source/Programs/TraceAnalyzer`
- headers: 5; symbols: 120
- symbol kinds: class=3, delegate=1, function=62, macro=3, member=13, namespace=6, prototype=27, struct=2, typedef=2, variable=1
- PrivateDependencyModuleNames: Core, Projects, TraceAnalysis
- PublicIncludePathModuleNames: Launch

### `Source/Programs/TraceAnalyzer/Private/Command.h` (Private)


#### struct `UE::TraceAnalyzer::FCommand`  
`struct FCommand`  
_L12-17_
- L14 _public member_ `const TCHAR* Name;`
- L15 _public member_ `const TCHAR* Description;`
- L16 _public member_ `int32 (*Main)(int32, TCHAR const* const*);`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L9 _namespace_ `namespace TraceAnalyzer` (scope `UE`)

### `Source/Programs/TraceAnalyzer/Private/Common.h` (Private)


#### struct `UE::TraceAnalyzer::FFileDataStream`  
`struct FFileDataStream : public UE::Trace::IInDataStream`  
_L21-34_
- inherits: `UE::Trace::IInDataStream`
- L23 _public function_ `~FFileDataStream()`
- L28 _public function_ `virtual int32 Read(void* Data, uint32 Size) override`
- L33 _public member_ `FileHandle Handle;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L16 _namespace_ `namespace TraceAnalyzer` (scope `UE`)
- L38 _function_ `inline TUniquePtr<UE::Trace::IInDataStream> GetDataStream(int ArgC, TCHAR const* const* ArgV)` (scope `UE::TraceAnalyzer`)

### `Source/Programs/TraceAnalyzer/Private/Io.h` (Private)


#### Free symbols / members of external scopes

- L17 _typedef_ `typedef PTRINT FileHandle;`
- L18 _variable_ `constexpr FileHandle InvalidFileHandle = FileHandle(-1);`
- L22 _function_ `inline bool IsValidFileHandle(FileHandle Handle)`
- L29 _function_ `inline FileHandle GetStdOut()`
- L36 _function_ `inline FileHandle GetStdIn()`
- L43 _function_ `inline FileHandle GetStdErr()`
- L50 _function_ `inline bool IsTty(FileHandle Handle)`
- L57 _function_ `inline int32 FileRead(FileHandle Handle, void* Data, int Size)`
- L69 _function_ `inline int FileWrite(FileHandle Handle, const void* Data, int32 Size)`
- L81 _function_ `inline FileHandle OpenFile(const TCHAR* Path, bool Writeable)`
- L94 _function_ `inline void CloseFile(FileHandle Handle)`
- L110 _typedef_ `typedef int FileHandle;`

### `Source/Programs/TraceAnalyzer/Private/TextSerializer.h` (Private)


#### class `UE::TraceAnalyzer::FTextSerializer`  
`class FTextSerializer`  
_L20-245_
- L23 _public prototype_ `FTextSerializer();`
- L24 _public prototype_ `virtual ~FTextSerializer();`
- L26 _public prototype_ `virtual void AppendChar(const ANSICHAR Value) = 0;`
- L27 _public prototype_ `virtual void Append(const ANSICHAR* Text, int32 Len) = 0;`
- L28 _public prototype_ `virtual void Append(const ANSICHAR* Text) = 0;`
- L29 _public prototype_ `virtual void Appendf(const char* Format, ...) = 0;`
- L30 _public prototype_ `virtual bool Commit() = 0;`
- L35 _public function_ `void BeginAttributeSet()`
- L40 _public function_ `void BeginAttribute()`
- L53 _public function_ `void EndAttribute()`
- L60 _public function_ `void BeginNewEventHeader()`
- L78 _public function_ `void EndNewEventHeader()`
- L86 _public function_ `void BeginNewEventFields()`
- L89 _public function_ `void BeginField()`
- L100 _public function_ `void EndField()`
- L104 _public function_ `void EndNewEventFields()`
- L113 _public function_ `bool IsWriteEventHeaderEnabled() const`
- L115 _public function_ `void BeginEvent(uint32 CtxThreadId)`
- L134 _public function_ `void WriteEventName(const char* LoggerName, const char* Name)`
- L144 _public function_ `void EndEvent()`
- L155 _public function_ `void BeginArray()`
- L160 _public function_ `void NextArrayElement()`
- L165 _public function_ `void EndArray()`
- L173 _public function_ `void WriteValueString(const char* Value)`
- L179 _public function_ `void WriteValueString(const char* Value, uint32 Len)`
- L186 _public function_ `void WriteValueReference(const UE::Trace::FEventRef8& Value)`
- L187 _public function_ `void WriteValueReference(const UE::Trace::FEventRef16& Value)`
- L188 _public function_ `void WriteValueReference(const UE::Trace::FEventRef32& Value)`
- L189 _public function_ `void WriteValueReference(const UE::Trace::FEventRef64& Value)`
- L191 _public function_ `void WriteValueBool(bool Value)`
- L193 _public function_ `void WriteValueInt8(int8 Value)`
- L194 _public function_ `void WriteValueInt16(int16 Value)`
- L195 _public function_ `void WriteValueInt32(int32 Value)`
- L196 _public function_ `void WriteValueInt64(int64 Value)`
- L198 _public function_ `void WriteValueUInt8(uint8 Value)`
- L199 _public function_ `void WriteValueUInt16(uint16 Value)`
- L200 _public function_ `void WriteValueUInt32(uint32 Value)`
- L201 _public function_ `void WriteValueUInt64(uint64 Value)`
- L203 _public function_ `void WriteValueHex8(uint8 Value)`
- L204 _public function_ `void WriteValueHex16(uint16 Value)`
- L205 _public function_ `void WriteValueHex32(uint32 Value)`
- L206 _public function_ `void WriteValueHex64(uint64 Value)`
- L208 _public prototype_ `void WriteValueInt64Auto(int64 Value);`
- L209 _public prototype_ `void WriteValueUInt64Auto(uint64 Value);`
- L211 _public function_ `void WriteValueFloat(float Value)`
- L212 _public function_ `void WriteValueDouble(double Value)`
- L214 _public prototype_ `void WriteValueFloatAuto(float Value);`
- L215 _public prototype_ `void WriteValueDoubleAuto(double Value);`
- L217 _public function_ `void WriteValueTime(double Time)`
- L218 _public function_ `void WriteValueNull()`
- L220 _public prototype_ `void WriteValueBinary(const void* Data, uint32 Size);`
- L225 _public function_ `void WriteKey(const ANSICHAR* Name)`
- L231 _public function_ `void WriteAttributeString(const ANSICHAR* Name, const ANSICHAR* Value)`
- L232 _public function_ `void WriteAttributeString(const ANSICHAR* Name, const ANSICHAR* Value, uint32 Len)`
- L233 _public function_ `void WriteAttributeBool(const ANSICHAR* Name, bool Value)`
- L234 _public function_ `void WriteAttributeInteger(const ANSICHAR* Name, int64 Value)`
- L235 _public function_ `void WriteAttributeIntegerHex(const ANSICHAR* Name, int64 Value)`
- L236 _public function_ `void WriteAttributeFloat(const ANSICHAR* Name, float Value)`
- L237 _public function_ `void WriteAttributeDouble(const ANSICHAR* Name, double Value)`
- L238 _public function_ `void WriteAttributeNull(const ANSICHAR* Name)`
- L239 _public function_ `void WriteAttributeBinary(const ANSICHAR* Name, const void* Data, uint32 Size)`
- L242 _protected member_ `bool bWriteEventHeader = true;`
- L243 _protected member_ `bool bLastWasNewEvent = false;`
- L244 _protected member_ `uint32 AttributeCount = 0;`

#### class `UE::TraceAnalyzer::FStdoutTextSerializer`  
`class FStdoutTextSerializer : public FTextSerializer`  
_L249-260_
- inherits: `FTextSerializer`
- L252 _public prototype_ `FStdoutTextSerializer();`
- L253 _public function_ `virtual ~FStdoutTextSerializer()`
- L255 _public prototype_ `virtual void AppendChar(const ANSICHAR Value) override;`
- L256 _public prototype_ `virtual void Append(const ANSICHAR* Text, int32 Len) override;`
- L257 _public prototype_ `virtual void Append(const ANSICHAR* Text) override;`
- L258 _public prototype_ `virtual void Appendf(const char* Format, ...) override;`
- L259 _public prototype_ `virtual bool Commit() override;`

#### class `UE::TraceAnalyzer::FFileTextSerializer`  
`class FFileTextSerializer : public FTextSerializer`  
_L264-286_
- inherits: `FTextSerializer`
- L267 _public prototype_ `FFileTextSerializer(FileHandle InHandle);`
- L268 _public prototype_ `virtual ~FFileTextSerializer();`
- L270 _public prototype_ `virtual void AppendChar(const ANSICHAR Value) override;`
- L271 _public prototype_ `virtual void Append(const ANSICHAR* Text, int32 Len) override;`
- L272 _public prototype_ `virtual void Append(const ANSICHAR* Text) override;`
- L273 _public prototype_ `virtual void Appendf(const char* Format, ...) override;`
- L274 _public prototype_ `virtual bool Commit() override;`
- L277 _private prototype_ `void* GetPointer(uint32 RequiredSize);`
- L280 _private member_ `FileHandle Handle = -1;`
- L281 _private member_ `static constexpr int BufferSize = 1024 * 1024;`
- L282 _private member_ `void* Buffer = nullptr;`
- L283 _private member_ `static constexpr int FormatBufferSize = 64 * 1024;`
- L284 _private member_ `void* FormatBuffer = nullptr;`
- L285 _private member_ `uint32 Used = 0;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace TraceAnalyzer` (scope `UE`)

### `Source/Programs/TraceAnalyzer/Private/TraceAnalyzer.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTraceAnalyzer, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTraceAnalyzer, Log, All);`
- L10 _macro_ `#define LogTraceAnalyzerError(Format, ...) \`
- L15 _macro_ `#define LogTraceAnalyzerWarning(Format, ...) \`
- L20 _macro_ `#define LogTraceAnalyzerMessage(Format, ...) \`
