# Programs / TraceTrimmer

- module root: `Source/Programs/TraceTrimmer`
- headers: 5; symbols: 37
- symbol kinds: delegate=1, function=12, macro=3, member=1, namespace=8, prototype=8, struct=1, typedef=2, variable=1
- PrivateDependencyModuleNames: Core, Projects, TraceAnalysis, TraceServices
- PublicIncludePathModuleNames: Launch

### `Source/Programs/TraceTrimmer/Private/Common.h` (Private)


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

### `Source/Programs/TraceTrimmer/Private/Io.h` (Private)


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

### `Source/Programs/TraceTrimmer/Private/TraceReferenceTests.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Trace` (scope `UE`)
- L7 _namespace_ `namespace Tests` (scope `UE::Trace`)
- L10 _prototype_ `void TraceTestReferences(const TCHAR* TraceFile);` (scope `UE::Trace::Tests`)

### `Source/Programs/TraceTrimmer/Private/TraceTrimmer.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTraceTrimmer, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTraceTrimmer, Log, All);`
- L10 _macro_ `#define LogTraceTrimmerError(Format, ...) \`
- L15 _macro_ `#define LogTraceTrimmerWarning(Format, ...) \`
- L20 _macro_ `#define LogTraceTrimmerMessage(Format, ...) \`

### `Source/Programs/TraceTrimmer/Private/TraceWriterTests.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Trace` (scope `UE`)
- L7 _namespace_ `namespace Tests` (scope `UE::Trace`)
- L10 _prototype_ `void TraceWriterTest0(const TCHAR* TraceFile);` (scope `UE::Trace::Tests`)
- L11 _prototype_ `void TraceWriterTest1(const TCHAR* TraceFile);` (scope `UE::Trace::Tests`)
- L12 _prototype_ `void TraceWriterTest2a(const TCHAR* TraceFile);` (scope `UE::Trace::Tests`)
- L13 _prototype_ `void TraceWriterTest2b(const TCHAR* TraceFile);` (scope `UE::Trace::Tests`)
- L14 _prototype_ `void TraceWriterTest3(const TCHAR* TraceFile);` (scope `UE::Trace::Tests`)
- L15 _prototype_ `void TraceWriterTestCpuProfiler(const TCHAR* TraceFile);` (scope `UE::Trace::Tests`)
