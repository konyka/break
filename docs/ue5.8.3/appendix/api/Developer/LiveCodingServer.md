# Developer / LiveCodingServer

- module root: `Source/Developer/Windows/LiveCodingServer`
- headers: 61; symbols: 1597
- symbol kinds: class=45, delegate=9, enum=20, enumerator=99, externvar=101, function=84, macro=8, member=423, namespace=39, prototype=645, struct=88, typedef=34, union=2
- PrivateDependencyModuleNames: Core, DiaSdk, Json, LiveCoding, VisualStudioDTE

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_AllocatorStats.h` (Private)


#### class `AllocatorStats`  
`class AllocatorStats`  
_L13-31_
- desc: thread-safe
- L16 _public prototype_ `AllocatorStats(void);`
- L18 _public prototype_ `void RegisterAllocation(size_t size);`
- L19 _public prototype_ `void UnregisterAllocation(size_t size);`
- L21 _public prototype_ `void Merge(const AllocatorStats& stats);`
- L23 _public prototype_ `void Print(const char* name) const;`
- L25 _public prototype_ `uint64_t GetAllocationCount(void) const;`
- L26 _public prototype_ `uint64_t GetMemorySize(void) const;`
- L29 _private member_ `uint64_t m_allocationCount;`
- L30 _private member_ `uint64_t m_memorySize;`

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_Allocators.h` (Private)


#### Free symbols / members of external scopes

- L15 _namespace_ `namespace memory`
- L18 _function_ `template <typename T> inline void Destruct(T* ptr)` (scope `memory`)
- L27 _function_ `template <typename Allocator, typename T> inline void Free(Allocator* allocator, T* ptr, size_t size)` (scope `memory`)
- L33 _function_ `template <typename Allocator, typename T> inline void Delete(Allocator* allocator, T* ptr, size_t size)` (scope `memory`)
- L44 _macro_ `#define LC_ALLOC(_allocator, _size, _alignment) (_allocator)->Allocate((_size), (_alignment))` — raw allocations
- L45 _macro_ `#define LC_FREE(_allocator, _ptr, _size) (_allocator)->Free((_ptr), (_size))`
- L48 _macro_ `#define LC_NEW_ALIGNED(_allocator, _type, _alignment) new (LC_ALLOC(_allocator, sizeof(_type), _alignment)) _type` — new & delete replacements
- L49 _macro_ `#define LC_NEW(_allocator, _type) LC_NEW_ALIGNED(_allocator, _type, alignof(_type))`
- L50 _macro_ `#define LC_DELETE(_allocator, _ptr, _size) memory::Delete((_allocator), (_ptr), (_size))`
- L53 _externvar_ `extern PoolAllocator<PoolAllocatorMultiThreadPolicy> g_symbolAllocator;` — special allocators
- L54 _externvar_ `extern MicroAllocator g_immutableStringAllocator;`
- L55 _externvar_ `extern PoolAllocator<PoolAllocatorMultiThreadPolicy> g_contributionAllocator;`
- L56 _externvar_ `extern PoolAllocator<PoolAllocatorMultiThreadPolicy> g_compilandAllocator;`
- L57 _externvar_ `extern PoolAllocator<PoolAllocatorMultiThreadPolicy> g_amalgamatedCompilandAllocator;`
- L58 _externvar_ `extern PoolAllocator<PoolAllocatorMultiThreadPolicy> g_dependencyAllocator;`
- L59 _externvar_ `extern PoolAllocator<PoolAllocatorMultiThreadPolicy> g_directoryAllocator;`
- L60 _externvar_ `extern Mallocator g_objFileAllocator;`
- L61 _externvar_ `extern Mallocator g_rawCoffAllocator;`
- L62 _externvar_ `extern Mallocator g_rawElfAllocator;`
- L63 _externvar_ `extern Mallocator g_relocatableFileAllocator;`
- L64 _externvar_ `extern Mallocator g_executableFileAllocator;`
- L65 _externvar_ `extern Mallocator g_tlogFileAllocator;`

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_Amalgamation.h` (Private)


#### Free symbols / members of external scopes

- L15 _namespace_ `namespace amalgamation`
- L17 _prototype_ `bool IsPartOfAmalgamation(const char* normalizedObjPath);` (scope `amalgamation`)
- L18 _prototype_ `bool IsPartOfAmalgamation(const wchar_t* normalizedObjPath);` (scope `amalgamation`)
- L22 _prototype_ `std::wstring CreateObjPart(const std::wstring& normalizedFilename);` (scope `amalgamation`) — creates part of the .obj file for .cpp files that are part of an amalgamation, e.g. turns C:\AbsoluteDir\SourceFile.cpp into .lpp_part.SourceFile.obj
- L26 _prototype_ `std::wstring CreateObjPath(const std::wstring& normalizedAmalgamatedObjPath, const std::wstring& objPart);` (scope `amalgamation`) — creates a full .obj path for single .obj files that are part of an amalgamation, e.g. turns C:\AbsoluteDir\Amalgamated.obj into C:\AbsoluteDir\Amalgamated.lpp_part.SourceFile.obj
- L29 _prototype_ `void SplitAmalgamatedCompilands( unsigned int splitAmalgamatedFilesThreshold, symbols::CompilandDB* compilandDb, symbols::Compiland* compiland, const types::vector<std::wstring>& includeFiles, const wchar_t* diaCompilandPath, const std::wstring& compilandPath, FileAttributeCache& fileCache, bool generateLogs, symbols::TimeStamp moduleLastModificationTime);` (scope `amalgamation`)
- L44 _prototype_ `bool ReadAndCompareDatabase(const symbols::ObjPath& objPath, const std::wstring& compilerPath, const symbols::Compiland* compiland, const std::wstring& additionalCompilerOptions);` (scope `amalgamation`) — reads a database from disk and compares it against the compiland's data. returns true if the database was read correctly and no change was detected.
- L47 _prototype_ `void WriteDatabase(const symbols::ObjPath& objPath, const std::wstring& compilerPath, const symbols::Compiland* compiland, const std::wstring& additionalCompilerOptions);` (scope `amalgamation`) — writes a compiland's dependency database to disk
- L50 _prototype_ `void DeleteDatabase(const symbols::ObjPath& objPath);` (scope `amalgamation`) — deletes a compiland's dependency database from disk

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_AppSettings.h` (Private)


#### struct `appSettings::FocusOnRecompile`  
`struct FocusOnRecompile`  
_L15-24_

#### enum `appSettings::FocusOnRecompile::Enum`  
`enum Enum`  
_L17-23_
- L19 _public enumerator_ `ON_ERROR`
- L20 _public enumerator_ `ON_SUCCESS`
- L21 _public enumerator_ `ON_SHORTCUT`
- L22 _public enumerator_ `NEVER`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace appSettings`
- L26 _prototype_ `void Startup(const wchar_t* group);` (scope `appSettings`)
- L27 _prototype_ `void Shutdown(void);` (scope `appSettings`)
- L30 _prototype_ `std::wstring GetLppDirectory(void);` (scope `appSettings`) — returns a directory where Live++-related files are saved, e.g. %LocalAppData%\Live++
- L33 _prototype_ `std::wstring GetSymbolsDirectory(void);` (scope `appSettings`) — returns a path where symbols can be stored
- L36 _prototype_ `std::wstring GetUserSettingsPath(void);` (scope `appSettings`) — returns a path where user settings can be stored
- L39 _prototype_ `std::wstring GetProjectSettingsPath(void);` (scope `appSettings`) — returns a path where project settings can be stored
- L42 _prototype_ `std::wstring GetCompilerPath(void);` (scope `appSettings`) — returns the overridden compiler path
- L45 _prototype_ `std::wstring GetLinkerPath(void);` (scope `appSettings`) — returns the overridden linker path
- L48 _prototype_ `const types::vector<std::wstring>& GetAmalgamatedCppFileExtensions(void);` (scope `appSettings`) — returns an array of file extensions to treat as C++ files when splitting amalgamated files
- L50 _prototype_ `void UpdateCompilerPathCache(void);` (scope `appSettings`)
- L51 _prototype_ `void UpdateLinkerPathCache(void);` (scope `appSettings`)
- L52 _prototype_ `void UpdatePathCache(void);` (scope `appSettings`)
- L54 _prototype_ `void UpdateAmalgamatedCppFileExtensions(void);` (scope `appSettings`)
- L57 _prototype_ `void ApplySettingBool(const char* const settingName, bool value);` (scope `appSettings`) — apply a new value to any of the boolean settings
- L60 _prototype_ `void ApplySettingInt(const char* const settingName, int value);` (scope `appSettings`) — apply a new value to any of the int settings
- L63 _prototype_ `void ApplySettingString(const char* const settingName, const wchar_t* const value);` (scope `appSettings`) — apply a new value to any of the string settings
- L67 _externvar_ `extern SettingInt* g_initialWindowMode;` (scope `appSettings`) — appearance
- L68 _externvar_ `extern SettingIntProxy* g_initialWindowModeProxy;` (scope `appSettings`)
- L69 _externvar_ `extern SettingBool* g_showFullPathInTitle;` (scope `appSettings`)
- L70 _externvar_ `extern SettingBool* g_showPathFirstInTitle;` (scope `appSettings`)
- L73 _externvar_ `extern SettingInt* g_receiveFocusOnRecompile;` (scope `appSettings`) — behaviour
- L74 _externvar_ `extern SettingIntProxy* g_receiveFocusOnRecompileProxy;` (scope `appSettings`)
- L75 _externvar_ `extern SettingBool* g_showNotificationOnRecompile;` (scope `appSettings`)
- L76 _externvar_ `extern SettingBool* g_clearLogOnRecompile;` (scope `appSettings`)
- L77 _externvar_ `extern SettingBool* g_minimizeOnClose;` (scope `appSettings`)
- L78 _externvar_ `extern SettingBool* g_keepTrayIcon;` (scope `appSettings`)
- L79 _externvar_ `extern SettingString* g_playSoundOnSuccess;` (scope `appSettings`)
- L80 _externvar_ `extern SettingString* g_playSoundOnError;` (scope `appSettings`)
- L81 _externvar_ `extern SettingShortcut* g_compileShortcut;` (scope `appSettings`)
- L82 _externvar_ `extern SettingInt* g_prewarmTimeout;` (scope `appSettings`)
- L85 _externvar_ `extern SettingBool* g_showUndecoratedNames;` (scope `appSettings`) — logging
- L86 _externvar_ `extern SettingBool* g_showTimestamps;` (scope `appSettings`)
- L87 _externvar_ `extern SettingBool* g_wordWrapOutput;` (scope `appSettings`)
- L88 _externvar_ `extern SettingBool* g_enableDevLog;` (scope `appSettings`)
- L89 _externvar_ `extern SettingBool* g_enableTelemetryLog;` (scope `appSettings`)
- L90 _externvar_ `extern SettingBool* g_enableDevLogCompilands;` (scope `appSettings`)
- L93 _externvar_ `extern SettingString* g_compilerPath;` (scope `appSettings`) — compiler
- L94 _externvar_ `extern SettingBool* g_useCompilerOverrideAsFallback;` (scope `appSettings`)
- L95 _externvar_ `extern SettingBool* g_useCompilerEnvironment;` (scope `appSettings`)
- L96 _externvar_ `extern SettingString* g_compilerOptions;` (scope `appSettings`)
- L97 _externvar_ `extern SettingBool* g_compilerForcePchPdbs;` (scope `appSettings`)
- L100 _externvar_ `extern SettingString* g_linkerPath;` (scope `appSettings`) — linker
- L101 _externvar_ `extern SettingBool* g_useLinkerOverrideAsFallback;` (scope `appSettings`)
- L102 _externvar_ `extern SettingBool* g_useLinkerEnvironment;` (scope `appSettings`)
- L103 _externvar_ `extern SettingString* g_linkerOptions;` (scope `appSettings`)
- L106 _externvar_ `extern SettingBool* g_continuousCompilationEnabled;` (scope `appSettings`) — continuous compilation
- L107 _externvar_ `extern SettingString* g_continuousCompilationPath;` (scope `appSettings`)
- L108 _externvar_ `extern SettingInt* g_continuousCompilationTimeout;` (scope `appSettings`)
- L111 _externvar_ `extern SettingString* g_virtualDriveLetter;` (scope `appSettings`) — virtual drive
- L112 _externvar_ `extern SettingString* g_virtualDrivePath;` (scope `appSettings`)
- L115 _externvar_ `extern SettingBool* g_installCompiledPatchesMultiProcess;` (scope `appSettings`) — multi-process editing
- L118 _externvar_ `extern SettingBool* g_amalgamationSplitIntoSingleParts;` (scope `appSettings`) — amalgamated/unity builds
- L119 _externvar_ `extern SettingInt* g_amalgamationSplitMinCppCount;` (scope `appSettings`)
- L120 _externvar_ `extern SettingString* g_amalgamationCppFileExtensions;` (scope `appSettings`) — DO NOT USE directly, use GetAmalgamatedCppFileExtensions instead!
- L123 _externvar_ `extern SettingBool* g_ue4EnableNatVisSupport;` (scope `appSettings`) — UE4-specific
- L126 _externvar_ `extern SettingString* g_fastBuildDatabasePath;` (scope `appSettings`) — FASTBuild-specific
- L127 _externvar_ `extern SettingString* g_fastBuildDllName;` (scope `appSettings`)

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_Assembler.h` (Private)


#### enum `Assembler::InstructionSize::Enum`  
`enum Enum : uint8_t`  
_L53-77_
- L55 _public enumerator_ `NOP1 = sizeof(Opcode::NOP1)`
- L56 _public enumerator_ `NOP2 = sizeof(Opcode::NOP2)`
- L57 _public enumerator_ `NOP3 = sizeof(Opcode::NOP3)`
- L58 _public enumerator_ `NOP4 = sizeof(Opcode::NOP4)`
- L59 _public enumerator_ `NOP5 = sizeof(Opcode::NOP5)`
- L60 _public enumerator_ `NOP6 = sizeof(Opcode::NOP6)`
- L61 _public enumerator_ `NOP7 = sizeof(Opcode::NOP7)`
- L62 _public enumerator_ `NOP8 = sizeof(Opcode::NOP8)`
- L63 _public enumerator_ `NOP9 = sizeof(Opcode::NOP9)`
- L64 _public enumerator_ `NOP10 = sizeof(Opcode::NOP10)`
- L65 _public enumerator_ `NOP11 = sizeof(Opcode::NOP11)`
- L66 _public enumerator_ `NOP12 = sizeof(Opcode::NOP12)`
- L67 _public enumerator_ `NOP13 = sizeof(Opcode::NOP13)`
- L68 _public enumerator_ `NOP14 = sizeof(Opcode::NOP14)`
- L69 _public enumerator_ `NOP15 = sizeof(Opcode::NOP15)`
- L70 _public enumerator_ `RET = sizeof(Opcode::RET)`
- L71 _public enumerator_ `JMP_REL8 = sizeof(Opcode::JMP_REL8) + 1u` — 1-byte offset
- L72 _public enumerator_ `JMP_REL32 = sizeof(Opcode::JMP_REL32) + 4u` — 4-byte offset
- L73 _public enumerator_ `JMP_INDIRECT_RIP32 = sizeof(Opcode::JMP_INDIRECT_RIP32) + 4u` — 4-byte offset
- L74 _public enumerator_ `CALL_INDIRECT_RIP32 = sizeof(Opcode::CALL_INDIRECT_RIP32) + 4u` — 4-byte offset
- L75 _public enumerator_ `MOV_RAX_TCB = sizeof(Opcode::MOV_RAX_TCB)`
- L76 _public enumerator_ `ADD_RAX_INDIRECT_RIP32 = sizeof(Opcode::ADD_RAX_INDIRECT_RIP32) + 4u` — 4-byte offset

#### struct `Assembler::Instruction`  
`struct Instruction`  
_L80-87_
- L83 _public member_ `static const unsigned int MAXIMUM_LENGTH = 15u;` — From the Intel® 64 and IA-32 Architectures Software Developer's Manual: The maximum length of an Intel 64 and IA-32 instruction remains 15 bytes.
- L85 _public member_ `uint8_t size;`
- L86 _public member_ `uint8_t machineCode[MAXIMUM_LENGTH];`

#### struct `Assembler::SizedInstruction`  
`template <uint8_t N> struct SizedInstruction`  
_L90-93_
- L92 _public member_ `uint8_t machineCode[N];`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Assembler`
- L14 _namespace_ `namespace Opcode` (scope `Assembler`)
- L17 _externvar_ `extern const uint8_t NOP1[1u];` (scope `Assembler::Opcode`) — NOP - No Operation
- L18 _externvar_ `extern const uint8_t NOP2[2u];` (scope `Assembler::Opcode`)
- L19 _externvar_ `extern const uint8_t NOP3[3u];` (scope `Assembler::Opcode`)
- L20 _externvar_ `extern const uint8_t NOP4[4u];` (scope `Assembler::Opcode`)
- L21 _externvar_ `extern const uint8_t NOP5[5u];` (scope `Assembler::Opcode`)
- L22 _externvar_ `extern const uint8_t NOP6[6u];` (scope `Assembler::Opcode`)
- L23 _externvar_ `extern const uint8_t NOP7[7u];` (scope `Assembler::Opcode`)
- L24 _externvar_ `extern const uint8_t NOP8[8u];` (scope `Assembler::Opcode`)
- L25 _externvar_ `extern const uint8_t NOP9[9u];` (scope `Assembler::Opcode`)
- L26 _externvar_ `extern const uint8_t NOP10[10u];` (scope `Assembler::Opcode`)
- L27 _externvar_ `extern const uint8_t NOP11[11u];` (scope `Assembler::Opcode`)
- L28 _externvar_ `extern const uint8_t NOP12[12u];` (scope `Assembler::Opcode`)
- L29 _externvar_ `extern const uint8_t NOP13[13u];` (scope `Assembler::Opcode`)
- L30 _externvar_ `extern const uint8_t NOP14[14u];` (scope `Assembler::Opcode`)
- L31 _externvar_ `extern const uint8_t NOP15[15u];` (scope `Assembler::Opcode`)
- L34 _externvar_ `extern const uint8_t RET[1u];` (scope `Assembler::Opcode`) — RET - Return
- L37 _externvar_ `extern const uint8_t JMP_REL8[1u];` (scope `Assembler::Opcode`) — JMP - Jump
- L38 _externvar_ `extern const uint8_t JMP_REL32[1u];` (scope `Assembler::Opcode`)
- L39 _externvar_ `extern const uint8_t JMP_INDIRECT_RIP32[2u];` (scope `Assembler::Opcode`)
- L42 _externvar_ `extern const uint8_t CALL_INDIRECT_RIP32[2u];` (scope `Assembler::Opcode`) — CALL - Call Procedure
- L45 _externvar_ `extern const uint8_t MOV_RAX_TCB[9u];` (scope `Assembler::Opcode`) — MOV - Move
- L48 _externvar_ `extern const uint8_t ADD_RAX_INDIRECT_RIP32[3u];` (scope `Assembler::Opcode`) — ADD - Addition
- L51 _namespace_ `namespace InstructionSize` (scope `Assembler`)
- L96 _prototype_ `Instruction MakeNOP(uint8_t size);` (scope `Assembler`) — Generates a NOP instruction of a certain size, making use of multi-byte NOPs.
- L99 _prototype_ `SizedInstruction<InstructionSize::RET> MakeRET(void);` (scope `Assembler`) — Generates a RET instruction.
- L102 _prototype_ `SizedInstruction<InstructionSize::JMP_REL8> MakeJMP8Relative(int8_t displacement);` (scope `Assembler`) — Generates a short jump using an 8-bit displacement.
- L105 _prototype_ `SizedInstruction<InstructionSize::JMP_REL32> MakeJMP32Relative(int32_t displacement);` (scope `Assembler`) — Generates a near jump using a 32-bit displacement.
- L108 _prototype_ `SizedInstruction<InstructionSize::JMP_INDIRECT_RIP32> MakeJMP32IndirectRIPRelative(int32_t ripOffset);` (scope `Assembler`) — Generates an indirect RIP-relative near jump using a 32-bit offset.
- L111 _prototype_ `SizedInstruction<InstructionSize::CALL_INDIRECT_RIP32> MakeCALL32IndirectRIPRelative(int32_t ripOffset);` (scope `Assembler`) — Generates an indirect RIP-relative near call using a 32-bit offset.
- L114 _prototype_ `SizedInstruction<InstructionSize::MOV_RAX_TCB> MakeMOVLoadTCB(void);` (scope `Assembler`) — Generates a MOV that loads the address of the thread control block into RAX.
- L117 _prototype_ `SizedInstruction<InstructionSize::ADD_RAX_INDIRECT_RIP32> MakeADD32IndirectRIPRelative(int32_t ripOffset);` (scope `Assembler`) — Generates an indirect RIP-relative ADD using a 32-bit offset.

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_COMThread.h` (Private)


#### class `COMThread`  
`class COMThread`  
_L16-86_
- desc: helper class that is the only one calling COM-related functions and methods. this is needed because most of the COM VS automation interfaces only can be called from a single thread.
- L28 _public prototype_ `COMThread(void);`
- L29 _public prototype_ `~COMThread(void);`
- L34 _public function_ `template <typename F, typename... Args> inline std::invoke_result_t<F, Args...> CallInThread(F ptrToFunction, Args&&... args)` — helper function that runs any given function in the internal COM thread and waits until execution has finished BEGIN EPIC MOD
- L79 _private prototype_ `Thread::ReturnValue ThreadFunction(void);`
- L81 _private member_ `COMFunction m_function;`
- L82 _private member_ `Event m_functionAvailableEvent;`
- L83 _private member_ `Event m_functionFinishedExecutingEvent;`
- L84 _private member_ `Event m_leaveThreadEvent;`
- L85 _private member_ `Thread::Handle m_internalThread;`

#### struct `COMThread::COMFunction`  
`struct COMFunction`  
_L18-25_
- L20 _public typedef_ `typedef void (FunctionType)(void*, void*);`
- L22 _public member_ `FunctionType* function;`
- L23 _public member_ `void* context;`
- L24 _public member_ `void* returnValueAddr;`

#### Free symbols / members of external scopes

- L38 _typedef_ `typedef std::invoke_result_t<F, Args...> ReturnValue;` (scope `COMThread::CallInThread`) — BEGIN EPIC MOD
- L46 _function_ `` (scope `COMThread::CallInThread`)
- L51 _typedef_ `typedef decltype(captureLambda) CaptureLambdaType;` (scope `COMThread::CallInThread`) — helper to make the following easier to read

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_ChangeNotification.h` (Private)


#### class `ChangeNotification`  
`class ChangeNotification`  
_L12-31_
- L15 _public prototype_ `ChangeNotification(void);`
- L16 _public prototype_ `~ChangeNotification(void);`
- L18 _public prototype_ `void Create(const wchar_t* path);`
- L19 _public prototype_ `void Destroy(void);`
- L21 _public prototype_ `bool Check(unsigned int timeoutMs);`
- L22 _public prototype_ `bool CheckOnce(void);`
- L23 _public prototype_ `void CheckNext(unsigned int timeoutMs);`
- L26 _private prototype_ `bool WaitForNotification(unsigned int timeoutMs);`
- L29 _private member_ `Windows::HANDLE m_handle;` — BEGIN EPIC MOD

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_CodeCave.h` (Private)


#### class `CodeCave`  
`class CodeCave`  
_L18-41_
- desc: nifty helper to let all threads of a process except one make "progress" by being held inside a jump-to-self cave.
- L22 _public prototype_ `CodeCave(Process::Handle processHandle, Process::Id processId, Thread::Id commandThreadId, const void* jumpToSelf);` — the jump-to-self code needs to be available in the address space of the given process
- L24 _public prototype_ `void Install(void);`
- L25 _public prototype_ `void Uninstall(void);`
- L28 _private member_ `Process::Handle m_processHandle;`
- L29 _private member_ `Process::Id m_processId;`
- L30 _private member_ `Thread::Id m_commandThreadId;`
- L31 _private member_ `const void* m_jumpToSelf;`
- L40 _private member_ `types::vector<PerThreadData> m_perThreadData;`

#### struct `CodeCave::PerThreadData`  
`struct PerThreadData`  
_L33-38_
- L35 _public member_ `Thread::Id id;`
- L36 _public member_ `const void* originalIp;`
- L37 _public member_ `int priority;`

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_Coff.h` (Private)


#### struct `coff::ObjFile`  
`struct ObjFile`  
_L27-33_
- L29 _public member_ `ImmutableString filename;`
- L30 _public member_ `Filesystem::MemoryMappedFile* memoryFile;`
- L32 _public prototype_ `LC_DISABLE_ASSIGNMENT(ObjFile);`

#### struct `coff::SymbolType`  
`struct SymbolType`  
_L35-46_

#### enum `coff::SymbolType::Enum`  
`enum Enum : uint8_t`  
_L37-45_
- L39 _public enumerator_ `EXTERNAL_DATA`
- L40 _public enumerator_ `EXTERNAL_FUNCTION`
- L41 _public enumerator_ `STATIC_DATA`
- L42 _public enumerator_ `STATIC_FUNCTION`
- L43 _public enumerator_ `UNKNOWN_DATA`
- L44 _public enumerator_ `UNKNOWN_FUNCTION`

#### struct `coff::Relocation`  
`struct Relocation`  
_L48-198_
- L189 _public member_ `uint32_t dstSymbolNameIndex;` — name of the symbol that the relocation points to
- L190 _public member_ `uint32_t srcRva;` — relative to start of source symbol
- L191 _public member_ `uint32_t dstOffset;` — the offset to the destination symbol to which the relocation is applied
- L193 _public member_ `int32_t dstSectionIndex;` — e.g. a write to a 64-bit integer has two relocations: both to the same symbol, but one at offset 0, the other at offset 4
- L194 _public member_ `Type::Enum type;` — type of the relocation
- L195 _public member_ `SymbolType::Enum srcSymbolType;` — symbol type of the source symbol, cached (does not increase struct size)
- L196 _public member_ `SymbolType::Enum dstSymbolType;` — symbol type of the destination symbol, cached (does not increase struct size)
- L197 _public member_ `bool dstIsSection;` — true if this relocation points to a section

#### struct `coff::Relocation::Type`  
`struct Type`  
_L50-187_
- L127 _public function_ `static const char* ToString(Enum value)`
- L152 _public function_ `static uint32_t GetByteDistance(Enum type)` — returns the byte distance to the position of where the relocation should be applied

#### enum `coff::Relocation::Type::Enum`  
`enum Enum : uint8_t`  
_L52-125_
- L83 _public enumerator_ `RELATIVE = IMAGE_REL_AMD64_REL32` — also used in 32-bit
- L84 _public enumerator_ `SECTION_RELATIVE = IMAGE_REL_AMD64_SECREL`
- L85 _public enumerator_ `VA_32 = IMAGE_REL_AMD64_ADDR32`
- L86 _public enumerator_ `RVA_32 = IMAGE_REL_AMD64_ADDR32NB`
- L89 _public enumerator_ `RELATIVE_OFFSET_1 = IMAGE_REL_AMD64_REL32_1` — 64-bit only
- L90 _public enumerator_ `RELATIVE_OFFSET_2 = IMAGE_REL_AMD64_REL32_2`
- L91 _public enumerator_ `RELATIVE_OFFSET_3 = IMAGE_REL_AMD64_REL32_3`
- L92 _public enumerator_ `RELATIVE_OFFSET_4 = IMAGE_REL_AMD64_REL32_4`
- L93 _public enumerator_ `RELATIVE_OFFSET_5 = IMAGE_REL_AMD64_REL32_5`
- L94 _public enumerator_ `VA_64 = IMAGE_REL_AMD64_ADDR64`
- L124 _public enumerator_ `UNKNOWN = 0xFFu`

#### struct `coff::Symbol`  
`struct Symbol`  
_L200-207_
- L202 _public member_ `uint32_t nameIndex;`
- L203 _public member_ `uint32_t rva;`
- L204 _public member_ `uint32_t sectionIndex;`
- L205 _public member_ `SymbolType::Enum type;`
- L206 _public member_ `types::vector<Relocation*> relocations;`

#### struct `coff::Section`  
`struct Section`  
_L209-218_
- L211 _public member_ `ImmutableString name;`
- L212 _public member_ `uint32_t rawDataSize;`
- L213 _public member_ `uint32_t rawDataRva;`
- L214 _public member_ `uint32_t characteristics;` — TODO: can save memory by putting characteristics and selection into bitfields
- L215 _public member_ `uint8_t comdatSelection;` — COMDAT selection specification, if any (0 means this is not a COMDAT section)
- L217 _public prototype_ `LC_DISABLE_ASSIGNMENT(Section);`

#### struct `coff::CrtSection`  
`struct CrtSection`  
_L220-228_
- L222 _public member_ `ImmutableString name;`
- L223 _public member_ `uint32_t rawDataSize;`
- L224 _public member_ `uint32_t rawDataRva;`
- L225 _public member_ `types::vector<Symbol*> symbols;` — no symbol ownership
- L227 _public prototype_ `LC_DISABLE_ASSIGNMENT(CrtSection);`

#### struct `coff::CoffDB`  
`struct CoffDB`  
_L230-252_
- L233 _public member_ `types::vector<ImmutableString> stringTable;` — the string table
- L236 _public member_ `types::vector<Section> sections;` — an array of all sections
- L240 _public member_ `types::vector<Symbol*> symbols;` — an array of all symbols. symbol ownership.
- L244 _public member_ `types::vector<Symbol*> indexToSymbol;` — lookup-table from name index to corresponding Symbol*. no symbol ownership.
- L247 _public member_ `types::vector<CrtSection> crtSections;` — C/C++ runtime sections
- L250 _public member_ `PoolAllocator<PoolAllocatorSingleThreadPolicy>* symbolAllocator;` — allocators
- L251 _public member_ `PoolAllocator<PoolAllocatorSingleThreadPolicy>* relocationAllocator;`

#### struct `coff::LibEntry`  
`struct LibEntry`  
_L254-260_
- L256 _public member_ `ImmutableString objPath;` — path of the .obj file stored in the archive
- L257 _public member_ `uint64_t offset;` — offset into the file at which the COFF is stored
- L259 _public prototype_ `LC_DISABLE_ASSIGNMENT(LibEntry);`

#### struct `coff::UnresolvedSymbolDB`  
`struct UnresolvedSymbolDB`  
_L262-266_
- L264 _public member_ `types::vector<ImmutableString> symbols;`
- L265 _public member_ `types::vector<uint32_t> symbolIndex;`

#### struct `coff::ExternalSymbolDB`  
`struct ExternalSymbolDB`  
_L268-272_
- L270 _public member_ `types::vector<ImmutableString> symbols;`
- L271 _public member_ `types::vector<SymbolType::Enum> types;`

#### struct `coff::RawSection`  
`struct RawSection`  
_L276-310_
- L278 _public member_ `IMAGE_SECTION_HEADER header;`
- L279 _public member_ `void* data;`
- L280 _public member_ `types::vector<IMAGE_RELOCATION> relocations;`
- L281 _public member_ `types::vector<IMAGE_LINENUMBER> lineNumbers;`
- L282 _public member_ `bool wasRemoved;`
- L283 _public member_ `bool isSelectAnyComdat;`
- L285 _public function_ `RawSection(void) : header() , data(nullptr) , relocations() , lineNumbers() , wasRemoved(false) , isSelectAnyComdat(false)`
- L296 _public function_ `RawSection(RawSection&& other) : header(std::move(other.header)) , data(std::move(other.data)) , relocations(std::move(other.relocations)) , lineNumbers(std::move(other.lineNumbers)) , wasRemoved(std::move(other.wasRemoved)) , isSelectAnyComdat(std::move(other.isSelectAnyComdat))` — move constructor
- L307 _public prototype_ `LC_DISABLE_COPY(RawSection);`
- L308 _public prototype_ `LC_DISABLE_ASSIGNMENT(RawSection);`
- L309 _public prototype_ `LC_DISABLE_MOVE_ASSIGNMENT(RawSection);`

#### struct `coff::RawStringTable`  
`struct RawStringTable`  
_L312-316_
- L314 _public member_ `char* data;`
- L315 _public member_ `uint32_t size;`

#### struct `coff::RawCoff`  
`struct RawCoff`  
_L318-329_
- L320 _public member_ `types::vector<RawSection> sections;`
- L321 _public member_ `types::vector<ImmutableString> stringTable;`
- L324 _public member_ `types::unordered_map<uint32_t, types::vector<uint32_t>> associatedComdatSections;` — indexed by section index, gives all section indices of COMDAT sections which are associated with this section
- L326 _public member_ `RawStringTable rawStringTable;`
- L327 _public member_ `uint64_t size;`
- L328 _public member_ `uint32_t type;`

#### struct `coff::RawCoffRegular`  
`struct RawCoffRegular : public RawCoff`  
_L331-337_
- inherits: `RawCoff`
- L333 _public member_ `static const uint32_t TYPE = 0u;`
- L335 _public member_ `IMAGE_FILE_HEADER header;`
- L336 _public member_ `types::vector<IMAGE_SYMBOL> symbols;`

#### struct `coff::RawCoffBigObj`  
`struct RawCoffBigObj : public RawCoff`  
_L339-345_
- inherits: `RawCoff`
- L341 _public member_ `static const uint32_t TYPE = 1u;`
- L343 _public member_ `ANON_OBJECT_HEADER_BIGOBJ header;`
- L344 _public member_ `types::vector<IMAGE_SYMBOL_EX> symbols;`

#### struct `coff::SymbolRemovalStrategy`  
`struct SymbolRemovalStrategy`  
_L348-355_

#### enum `coff::SymbolRemovalStrategy::Enum`  
`enum Enum : SHORT`  
_L350-354_
- L352 _public enumerator_ `MSVC_COMPATIBLE = IMAGE_SYM_DEBUG`
- L353 _public enumerator_ `LLD_COMPATIBLE = IMAGE_SYM_ABSOLUTE`

#### Free symbols / members of external scopes

- L25 _namespace_ `namespace coff`
- L359 _prototype_ `ObjFile* OpenObj(const wchar_t* filename);` (scope `coff`) — LIFETIME
- L360 _prototype_ `void CloseObj(ObjFile*& file);` (scope `coff`)
- L364 _prototype_ `RawCoff* ReadRaw(ObjFile* file, uint32_t uniqueId);` (scope `coff`) — UPDATE
- L365 _prototype_ `void WriteRaw(const wchar_t* filename, const RawCoff* rawCoff, SymbolRemovalStrategy::Enum removalStrategy);` (scope `coff`)
- L366 _prototype_ `void DestroyRaw(RawCoff* rawCoff);` (scope `coff`)
- L369 _prototype_ `size_t GetSymbolCount(const RawCoff* rawCoff);` (scope `coff`)
- L370 _prototype_ `size_t GetSectionCount(const RawCoff* rawCoff);` (scope `coff`)
- L372 _prototype_ `size_t GetAuxSymbolCount(const RawCoff* rawCoff, size_t symbolIndex);` (scope `coff`)
- L373 _prototype_ `SymbolType::Enum GetSymbolType(const RawCoff* rawCoff, size_t index);` (scope `coff`)
- L374 _prototype_ `const ImmutableString& GetSymbolName(const RawCoff* rawCoff, size_t index);` (scope `coff`)
- L375 _prototype_ `ImmutableString GetSectionName(const RawCoff* rawCoff, size_t index);` (scope `coff`)
- L376 _prototype_ `uint32_t GetSymbolSectionIndex(const RawCoff* rawCoff, size_t index);` (scope `coff`)
- L378 _prototype_ `bool IsAbsoluteSymbol(const RawCoff* rawCoff, size_t index);` (scope `coff`)
- L379 _prototype_ `bool IsDebugSymbol(const RawCoff* rawCoff, size_t index);` (scope `coff`)
- L380 _prototype_ `bool IsSectionSymbol(const RawCoff* rawCoff, size_t index);` (scope `coff`)
- L381 _prototype_ `bool IsUndefinedSymbol(const RawCoff* rawCoff, size_t index);` (scope `coff`)
- L382 _prototype_ `bool IsRemovedSymbol(const RawCoff* rawCoff, size_t index, SymbolRemovalStrategy::Enum removalStrategy);` (scope `coff`)
- L384 _prototype_ `bool IsSelectAnyComdatSection(const RawCoff* rawCoff, size_t sectionIndex);` (scope `coff`)
- L388 _prototype_ `types::vector<std::string> ExtractLinkerDirectives(const ObjFile* file);` (scope `coff`) — extracts directives from a COFF file
- L391 _prototype_ `types::vector<std::string> ExtractLinkerDirectives(const RawCoff* rawCoff);` (scope `coff`) — extracts directives from a raw COFF file
- L394 _prototype_ `void ReplaceLinkerDirectives(RawCoff* rawCoff, const types::vector<std::string>& directives);` (scope `coff`) — replaces linker directives in the raw COFF file
- L398 _prototype_ `void PatchFunctionSymbol(RawCoff* rawCoff, size_t symbolIndex, uint32_t sectionIndex);` (scope `coff`) — patches a function symbol to return immediately
- L401 _prototype_ `void RemoveSymbol(RawCoff* rawCoff, size_t symbolIndex, SymbolRemovalStrategy::Enum removalStrategy);` (scope `coff`) — removes a symbol
- L404 _prototype_ `void RemoveRelocations(RawCoff* rawCoff, size_t symbolIndex);` (scope `coff`) — remove all relocations to the symbol with the given index
- L407 _prototype_ `void RemoveSection(RawCoff* rawCoff, size_t sectionIndex);` (scope `coff`) — removes a section with the given index
- L412 _prototype_ `void RemoveAssociatedComdatSections(RawCoff* rawCoff, size_t sectionIndex);` (scope `coff`) — removes all COMDAT sections that have the given section index as their associated section. (e.g. a COMDAT section with associative section 0x5 only needs to become part of the image if section 5 is also part of the image).
- L416 _prototype_ `UnresolvedSymbolDB* GatherUnresolvedSymbolDatabase(ObjFile* file, uint32_t uniqueId);` (scope `coff`) — unique ID must uniquely identify this ObjFile. each obj file with a unique name must have a unique ID
- L417 _prototype_ `void DestroyDatabase(UnresolvedSymbolDB* db);` (scope `coff`)
- L420 _prototype_ `ExternalSymbolDB* GatherExternalSymbolDatabase(ObjFile* file, uint32_t uniqueId);` (scope `coff`) — unique ID must uniquely identify this ObjFile. each obj file with a unique name must have a unique ID
- L421 _prototype_ `void DestroyDatabase(ExternalSymbolDB* db);` (scope `coff`)
- L425 _prototype_ `CoffDB* GatherDatabase(ObjFile* file, uint32_t uniqueId);` (scope `coff`) — unique ID must uniquely identify this ObjFile. each obj file with a unique name must have a unique ID
- L426 _prototype_ `void DestroyDatabase(CoffDB* db);` (scope `coff`)
- L429 _prototype_ `size_t GetIndexCount(const CoffDB* coffDb);` (scope `coff`)
- L430 _prototype_ `const Symbol* GetSymbolByIndex(const CoffDB* coffDb, size_t index);` (scope `coff`)
- L432 _prototype_ `const ImmutableString& GetSymbolName(const CoffDB* coffDb, const Symbol* symbol);` (scope `coff`)
- L433 _prototype_ `const ImmutableString& GetRelocationDstSymbolName(const CoffDB* coffDb, const Relocation* relocation);` (scope `coff`)
- L434 _prototype_ `const ImmutableString& GetUnresolvedSymbolName(const CoffDB* coffDb, size_t unresolvedSymbolIndex);` (scope `coff`)
- L436 _prototype_ `SymbolType::Enum GetRelocationSrcSymbolType(const Relocation* relocation);` (scope `coff`)
- L437 _prototype_ `SymbolType::Enum GetRelocationDstSymbolType(const Relocation* relocation);` (scope `coff`)
- L441 _prototype_ `const CrtSection* FindCrtSection(const CoffDB* coffDb, const ImmutableString& sectionName, uint32_t sectionSize);` (scope `coff`) — finds a CRT section with the given name and size. returns nullptr if not found or ambiguous
- L444 _prototype_ `std::vector<const CrtSection*> FindMatchingCrtSections(const CoffDB* coffDb, const ImmutableString& sectionName, uint32_t sectionSize);` (scope `coff`) — finds all matching CRT sections
- L447 _prototype_ `uint32_t FindCoffSuffix(const ImmutableString& symbolName);` (scope `coff`)
- L451 _prototype_ `uint32_t GetRelocationDestinationSectionCharacteristics(const coff::CoffDB* coffDb, const coff::Relocation* relocation);` (scope `coff`) — returns 0 if the relocation destination section is invalid
- L455 _prototype_ `const void* GetBaseAddress(const ObjFile* file);` (scope `coff`) — ACCESS
- L457 _prototype_ `bool IsFunctionSymbol(SymbolType::Enum type);` (scope `coff`)
- L459 _prototype_ `char GetCoffSuffix(void);` (scope `coff`)
- L460 _prototype_ `wchar_t GetWideCoffSuffix(void);` (scope `coff`)
- L462 _prototype_ `const ImmutableString& GetTlsSectionName(void);` (scope `coff`)
- L465 _prototype_ `bool IsInterestingSymbol(const ImmutableString& name);` (scope `coff`)
- L466 _prototype_ `bool IsMSVCJustMyCodeSection(const char* sectionName);` (scope `coff`)

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_CoffCache.h` (Private)


#### class `CoffCache`  
`template <typename T> class CoffCache`  
_L15-36_
- L18 _public prototype_ `CoffCache(void);`
- L19 _public prototype_ `~CoffCache(void);`
- L24 _public prototype_ `void Update(const ImmutableString& coffIdentifier, T* database);` — updates an entry in the cache. if it already exists, the existing one will be deleted. takes ownership over the database. thread-safe.
- L27 _public prototype_ `const T* Lookup(const ImmutableString& coffIdentifier) const;` — returns a database associated with a certain COFF id.
- L29 _public prototype_ `bool Contains(const ImmutableString& coffIdentifier) const;`
- L32 _private member_ `mutable CriticalSection m_cs;`
- L34 _private typedef_ `typedef types::StringMap<T*> Cache;`
- L35 _private member_ `Cache m_cache;`

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_CoffDetail.h` (Private)


#### struct `coffDetail::CoffType`  
`struct CoffType`  
_L19-48_

#### enum `coffDetail::CoffType::Enum`  
`enum Enum`  
_L21-27_
- L23 _public enumerator_ `COFF` — regular COFF/OBJ files
- L24 _public enumerator_ `BIGOBJ` — OBJ files compiled with /bigobj
- L25 _public enumerator_ `IMPORT_LIBRARY` — import libraries (DLL stubs)
- L26 _public enumerator_ `UNKNOWN`

#### struct `coffDetail::CoffType::TypeMap`  
`template <Enum> struct TypeMap`  
_L31-31_
- desc: template helper to map from CoffType::Enum values to types
- L36 _public typedef_ `typedef IMAGE_FILE_HEADER HeaderType;`
- L37 _public typedef_ `typedef IMAGE_SYMBOL SymbolType;`
- L38 _public typedef_ `typedef IMAGE_AUX_SYMBOL AuxSymbolType;`
- L44 _public typedef_ `typedef ANON_OBJECT_HEADER_BIGOBJ HeaderType;`
- L45 _public typedef_ `typedef IMAGE_SYMBOL_EX SymbolType;`
- L46 _public typedef_ `typedef IMAGE_AUX_SYMBOL_EX AuxSymbolType;`

#### struct `coffDetail::CoffType::TypeMap`  
`template <> struct TypeMap<Enum::COFF>`  
_L34-39_
- L36 _public typedef_ `typedef IMAGE_FILE_HEADER HeaderType;`
- L37 _public typedef_ `typedef IMAGE_SYMBOL SymbolType;`
- L38 _public typedef_ `typedef IMAGE_AUX_SYMBOL AuxSymbolType;`
- L44 _public typedef_ `typedef ANON_OBJECT_HEADER_BIGOBJ HeaderType;`
- L45 _public typedef_ `typedef IMAGE_SYMBOL_EX SymbolType;`
- L46 _public typedef_ `typedef IMAGE_AUX_SYMBOL_EX AuxSymbolType;`

#### struct `coffDetail::CoffType::TypeMap`  
`template <> struct TypeMap<Enum::BIGOBJ>`  
_L42-47_
- L36 _public typedef_ `typedef IMAGE_FILE_HEADER HeaderType;`
- L37 _public typedef_ `typedef IMAGE_SYMBOL SymbolType;`
- L38 _public typedef_ `typedef IMAGE_AUX_SYMBOL AuxSymbolType;`
- L44 _public typedef_ `typedef ANON_OBJECT_HEADER_BIGOBJ HeaderType;`
- L45 _public typedef_ `typedef IMAGE_SYMBOL_EX SymbolType;`
- L46 _public typedef_ `typedef IMAGE_AUX_SYMBOL_EX AuxSymbolType;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace coffDetail`
- L50 _prototype_ `CoffType::Enum GetCoffType(const void* imageBase);` (scope `coffDetail`)
- L53 _prototype_ `unsigned int GetRelocationCount(const void* imageBase, const IMAGE_SECTION_HEADER* section);` (scope `coffDetail`) — returns the number of relocations
- L57 _function_ `template <typename SymbolType> inline uint32_t GetSectionIndex(const SymbolType* symbol)` (scope `coffDetail`)
- L66 _typedef_ `typedef typename std::make_unsigned<decltype(symbol->SectionNumber)>::type UnsignedSectionNumberType;` (scope `coffDetail::GetSectionIndex`) — according to COFF spec, section number is a one-based (because zero is taken by UNDEFINED symbols) signed integer, and signed values like 0, -1 and -2 have special meaning. note that in cases where the index is a negative value that does not correspond to any of the special values, the section number *must* be treated as an unsigned value, which is not stated in the spec. e.g. some non-bigobj COFF files that have more than 32767 sections will have symbols with section numbers like 0x8000, 0x8001, etc. which need to be treated as unsigned values.
- L75 _prototype_ `uint32_t GetAssociatedComdatSectionIndex(const AuxSymbolType* symbol);` (scope `coffDetail`) — BEGIN EPIC MOD
- L79 _function_ `template <> inline uint32_t GetAssociatedComdatSectionIndex(const IMAGE_AUX_SYMBOL* symbol)` (scope `coffDetail`)
- L81 _typedef_ `typedef std::make_unsigned<decltype(symbol->Section.Number)>::type UnsignedSectionNumberType;` (scope `coffDetail::GetAssociatedComdatSectionIndex`)
- L87 _function_ `template <> inline uint32_t GetAssociatedComdatSectionIndex(const IMAGE_AUX_SYMBOL_EX* symbol)` (scope `coffDetail`)
- L90 _typedef_ `typedef std::make_unsigned<decltype(symbol->Section.HighNumber)>::type UnsignedHighSectionNumberType;` (scope `coffDetail::GetAssociatedComdatSectionIndex`)
- L102 _function_ `template <typename SymbolType> inline bool IsFunctionSymbol(const SymbolType* symbol)` (scope `coffDetail`)
- L125 _function_ `template <typename SymbolType> inline bool IsUndefinedSymbol(const SymbolType* symbol)` (scope `coffDetail`)
- L131 _function_ `template <typename SymbolType> inline bool IsAbsoluteSymbol(const SymbolType* symbol)` (scope `coffDetail`)
- L137 _function_ `template <typename SymbolType> inline bool IsDebugSymbol(const SymbolType* symbol)` (scope `coffDetail`)
- L144 _function_ `template <typename SymbolType> inline bool IsSectionSymbol(const SymbolType* symbol)` (scope `coffDetail`)
- L169 _function_ `template <typename SymbolType> inline bool IsLabelSymbol(const SymbolType* symbol)` (scope `coffDetail`)
- L187 _function_ `inline bool IsDebugRelocation(const IMAGE_RELOCATION* relocation)` (scope `coffDetail`) — From the COFF spec: 5.2.1 Type Indicators
- L200 _function_ `inline bool IsDiscardableSection(const IMAGE_SECTION_HEADER* section)` (scope `coffDetail`) — From the COFF spec: 4.1 Section Flags
- L205 _function_ `inline bool IsPartOfImage(const IMAGE_SECTION_HEADER* section)` (scope `coffDetail`)
- L211 _function_ `inline bool IsComdatSection(const IMAGE_SECTION_HEADER* section)` (scope `coffDetail`)
- L216 _function_ `inline bool IsDirectiveSection(const IMAGE_SECTION_HEADER* section)` (scope `coffDetail`)
- L223 _function_ `inline bool IsCodeSection(uint32_t characteristics)` (scope `coffDetail`)
- L228 _function_ `inline bool IsReadSection(uint32_t characteristics)` (scope `coffDetail`)
- L233 _function_ `inline bool IsWriteSection(uint32_t characteristics)` (scope `coffDetail`)
- L240 _function_ `template <typename HeaderType> inline uint32_t GetNumberOfSections(const void* imageBase)` (scope `coffDetail`)
- L248 _function_ `template <typename HeaderType> inline uint32_t GetNumberOfSymbols(const void* imageBase)` (scope `coffDetail`)
- L256 _function_ `template <typename HeaderType> inline const IMAGE_SECTION_HEADER* GetSectionHeader(const void* imageBase)` (scope `coffDetail`)
- L263 _function_ `template <typename HeaderType> inline const void* GetSymbolTable(const void* imageBase)` (scope `coffDetail`)
- L271 _function_ `template <typename SymbolType> inline const char* GetStringTable(const void* symbolTable, uint32_t symbolCount)` (scope `coffDetail`)
- L279 _function_ `template <typename SymbolType> inline const SymbolType* GetSymbol(const void* symbolTable, size_t index)` (scope `coffDetail`)
- L286 _function_ `inline uint32_t GetArchiveMemberSize(const IMAGE_ARCHIVE_MEMBER_HEADER* header)` (scope `coffDetail`) — archives/libraries
- L297 _function_ `inline uint32_t PadArchiveMemberSize(uint32_t size)` (scope `coffDetail`)

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_Compiler.h` (Private)


#### struct `compiler::CompilerType`  
`struct CompilerType`  
_L31-38_

#### enum `compiler::CompilerType::Enum`  
`enum Enum`  
_L33-37_
- L35 _public enumerator_ `CL` — MSVC
- L36 _public enumerator_ `CLANG` — LLVM/Clang

#### struct `compiler::LinkerType`  
`struct LinkerType`  
_L40-47_

#### enum `compiler::LinkerType::Enum`  
`enum Enum`  
_L42-46_
- L44 _public enumerator_ `LINK` — MSVC
- L45 _public enumerator_ `LLD` — LLVM/LLD

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace compiler`
- L17 _prototype_ `Process::Environment CreateEnvironmentCacheEntry(const wchar_t* absolutePathToCompilerExe);` (scope `compiler`) — creates a new entry in the cache for the given compiler .exe, and returns it
- L21 _prototype_ `Process::Environment GetEnvironmentFromCache(const wchar_t* absolutePathToCompilerExe);` (scope `compiler`) — gets the environment for a given compiler .exe from the cache. returns nullptr if the environment is not yet in the cache.
- L25 _prototype_ `Process::Environment UpdateEnvironmentCache(const wchar_t* absolutePathToCompilerExe);` (scope `compiler`) — helper function that either creates a new entry in the cache if none exists yet, or returns the one found in the cache.
- L28 _prototype_ `void AddEnvironmentToCache(const wchar_t* absolutePathToCompilerExe, Process::Environment* environment);` (scope `compiler`) — BEGIN EPIC MOD - Allow overriding environment block for tools
- L49 _prototype_ `CompilerType::Enum DetermineCompilerType(const wchar_t* compilerPath);` (scope `compiler`)
- L51 _prototype_ `LinkerType::Enum DetermineLinkerType(const wchar_t* linkerPath);` (scope `compiler`)

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_CompilerOptions.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace compilerOptions`
- L14 _prototype_ `bool CreatesPrecompiledHeader(const char* options);` (scope `compilerOptions`)
- L15 _prototype_ `bool UsesPrecompiledHeader(const char* options);` (scope `compilerOptions`)
- L16 _prototype_ `std::string GetPrecompiledHeaderPath(const char* options);` (scope `compilerOptions`)
- L18 _prototype_ `bool UsesC7DebugFormat(const char* options);` (scope `compilerOptions`)
- L19 _prototype_ `bool UsesMinimalRebuild(const char* options);` (scope `compilerOptions`)

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_DiaSymbolName.h` (Private)


#### class `dia::SymbolName`  
`class SymbolName`  
_L18-38_
- desc: simple wrapper, does not allocate, does not deep copy
- L21 _public prototype_ `explicit SymbolName(BSTR str);`
- L22 _public prototype_ `~SymbolName(void);`
- L25 _public prototype_ `SymbolName(SymbolName&& other);` — symbol names can only be moved, never be copied
- L27 _public function_ `inline const wchar_t* GetString(void) const`
- L33 _private member_ `BSTR m_name;`
- L35 _private prototype_ `LC_DISABLE_COPY(SymbolName);`
- L36 _private prototype_ `LC_DISABLE_ASSIGNMENT(SymbolName);`
- L37 _private prototype_ `LC_DISABLE_MOVE_ASSIGNMENT(SymbolName);`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace dia`

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_DiaUtil.h` (Private)


#### Free symbols / members of external scopes

- L17 _namespace_ `namespace dia`
- L19 _prototype_ `SymbolName GetSymbolName(IDiaSymbol* symbol);` (scope `dia`)
- L20 _prototype_ `SymbolName GetSymbolUndecoratedName(IDiaSymbol* symbol);` (scope `dia`)
- L21 _prototype_ `SymbolName GetSymbolLibraryName(IDiaSymbol* symbol);` (scope `dia`)
- L22 _prototype_ `SymbolName GetSymbolFilename(IDiaSourceFile* symbol);` (scope `dia`)
- L24 _prototype_ `Variant GetSymbolEnvironmentOption(IDiaSymbol* environment);` (scope `dia`)
- L26 _prototype_ `uint32_t GetSymbolRVA(IDiaSymbol* symbol);` (scope `dia`)
- L27 _prototype_ `uint32_t GetSymbolSize(IDiaSymbol* symbol);` (scope `dia`)
- L28 _prototype_ `uint32_t GetSymbolOffset(IDiaSymbol* symbol);` (scope `dia`)
- L30 _prototype_ `bool IsFunction(IDiaSymbol* symbol);` (scope `dia`)
- L32 _prototype_ `IDiaSymbol* GetTypeSymbol(IDiaSymbol* symbol);` (scope `dia`)
- L33 _prototype_ `IDiaSymbol* GetParent(IDiaSymbol* symbol);` (scope `dia`)
- L34 _prototype_ `IDiaSymbol* GetSymbolById(IDiaSession* session, uint32_t id);` (scope `dia`)
- L36 _prototype_ `bool WasCompiledWithLTCG(IDiaSymbol* compilandDetail);` (scope `dia`)
- L37 _prototype_ `bool WasCompiledWithHotpatch(IDiaSymbol* compilandDetail);` (scope `dia`)
- L39 _prototype_ `types::vector<IDiaSymbol*> GatherChildSymbols(IDiaSymbol* parent, enum SymTagEnum symTag);` (scope `dia`)
- L40 _prototype_ `types::vector<IDiaSourceFile*> GatherCompilandFiles(IDiaSession* session, IDiaSymbol* compiland);` (scope `dia`)
- L42 _prototype_ `IDiaEnumSectionContribs* FindSectionContributionsEnumerator(IDiaSession* session);` (scope `dia`)
- L43 _prototype_ `IDiaSymbol* FindSymbolByRVA(IDiaSession* session, uint32_t rva);` (scope `dia`)
- L44 _prototype_ `IDiaSymbol* FindFunctionByRva(IDiaSession* session, uint32_t rva);` (scope `dia`)
- L45 _prototype_ `IDiaSymbol* FindLabelByRva(IDiaSession* session, uint32_t rva);` (scope `dia`)
- L47 _prototype_ `uint32_t FindLineNumberByRVA(IDiaSession* session, uint32_t rva);` (scope `dia`)
- L48 _prototype_ `SymbolName FindSourceFileByRVA(IDiaSession* session, uint32_t rva);` (scope `dia`)

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_DiaVariant.h` (Private)


#### class `dia::Variant`  
`class Variant`  
_L18-39_
- desc: simple wrapper, does not allocate, does not deep copy
- L21 _public prototype_ `explicit Variant(IDiaSymbol* symbol);`
- L22 _public prototype_ `~Variant(void);`
- L25 _public prototype_ `Variant(Variant&& other);` — variants can only be moved, never be copied
- L27 _public function_ `inline const wchar_t* GetString(void) const`
- L33 _private member_ `VARIANT m_var;`
- L34 _private member_ `BSTR m_str;`
- L36 _private prototype_ `LC_DISABLE_COPY(Variant);`
- L37 _private prototype_ `LC_DISABLE_ASSIGNMENT(Variant);`
- L38 _private prototype_ `LC_DISABLE_MOVE_ASSIGNMENT(Variant);`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace dia`

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_DirectoryCache.h` (Private)


#### class `DirectoryCache`  
`class DirectoryCache`  
_L14-32_
- L23 _public prototype_ `explicit DirectoryCache(size_t expectedDirectoryCount);`
- L24 _public prototype_ `~DirectoryCache(void);`
- L26 _public prototype_ `Directory* AddDirectory(const std::wstring& directory);`
- L27 _public prototype_ `void PrimeNotifications(void);`
- L28 _public prototype_ `void RestartNotifications(void);`
- L31 _private member_ `types::unordered_map<std::wstring, Directory*> m_directories;`

#### struct `DirectoryCache::Directory`  
`struct Directory`  
_L17-21_
- L19 _public member_ `ChangeNotification changeNotification;`
- L20 _public member_ `bool hadChange;`

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_Disassembler.h` (Private)


#### class `Disassembler::Stream`  
`class Stream`  
_L25-40_

#### struct `Disassembler::Stream::Instruction`  
`struct Instruction`  
_L28-39_
- L33 _public member_ `static const unsigned int MAXIMUM_LENGTH = 15u;` — BEGIN EPIC MOD - removed copy non-ascii character From the Intel 64 and IA-32 Architectures Software Developer's Manual: The maximum length of an Intel 64 and IA-32 instruction remains 15 bytes. END EPIC MOD
- L35 _public member_ `uint8_t machineCode[MAXIMUM_LENGTH];`
- L36 _public member_ `uint8_t size;`
- L37 _public member_ `uint64_t address;`
- L38 _public member_ `uint16_t opcode;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Disassembler`
- L16 _prototype_ `uint8_t FindInstructionSize(Process::Handle processHandle, const void* address);` (scope `Disassembler`) — Returns the size of the first instruction found at the given address.
- L19 _prototype_ `bool IsMOV(uint16_t opcode);` (scope `Disassembler`) — Returns whether the given instruction opcode is a MOV of any kind.
- L22 _prototype_ `bool IsLEA(uint16_t opcode);` (scope `Disassembler`) — Returns whether the given instruction opcode is a LEA of any kind.

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_DuplexPipeServer.h` (Private)


#### class `DuplexPipeServer`  
`class DuplexPipeServer : public DuplexPipe`  
_L13-19_
- inherits: `DuplexPipe`
- L16 _public prototype_ `bool Create(const wchar_t* name);`
- L17 _public prototype_ `bool WaitForClient(void);`
- L18 _public prototype_ `void Disconnect(void);`

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_ExecutablePatcher.h` (Private)


#### class `ExecutablePatcher`  
`class ExecutablePatcher`  
_L14-47_
- L18 _public member_ `static const size_t INJECTED_CODE_SIZE = 3u;`
- L24 _public prototype_ `ExecutablePatcher(executable::Image* image, executable::ImageSectionDB* imageSections);` — reads the original entry point code from the executable
- L27 _public prototype_ `explicit ExecutablePatcher(const uint8_t* entryPointCode);` — uses the given entry point code
- L31 _public prototype_ `uint32_t DisableEntryPointInImage(executable::Image* image, executable::ImageSectionDB* imageSections);` — disables the entry point directly in the image file, and returns the RVA of the entry point
- L34 _public prototype_ `void DisableEntryPoint(Process::Handle processHandle, void* moduleBase, uint32_t entryPointRva);` — disables the entry point in memory
- L37 _public prototype_ `void RestoreEntryPoint(Process::Handle processHandle, void* moduleBase, uint32_t entryPointRva);` — restores the entry point of a loaded image that previously had its entry point disabled
- L40 _public function_ `inline const uint8_t* GetEntryPointCode(void) const`
- L46 _private member_ `uint8_t m_originalCode[INJECTED_CODE_SIZE] = {};`

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_FileAttributeCache.h` (Private)


#### class `FileAttributeCache`  
`class FileAttributeCache`  
_L14-39_
- L31 _public prototype_ `FileAttributeCache(void);`
- L32 _public prototype_ `Data UpdateCacheData(const std::wstring& path);`
- L34 _public prototype_ `size_t GetEntryCount(void) const;`
- L37 _private typedef_ `typedef types::unordered_map_with_hash<std::wstring, Data, Hasher> Cache;`
- L38 _private member_ `Cache m_data;`

#### struct `FileAttributeCache::Hasher`  
`struct Hasher`  
_L16-22_
- L18 _public function_ `inline size_t operator()(const std::wstring& key) const`

#### struct `FileAttributeCache::Data`  
`struct Data`  
_L25-29_
- L27 _public member_ `uint64_t lastModificationTime;`
- L28 _public member_ `bool exists;`

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_Filesystem.h` (Private)


#### Free symbols / members of external scopes

- L15 _namespace_ `namespace Filesystem`
- L17 _prototype_ `void Startup(void);` (scope `Filesystem`)
- L18 _prototype_ `void Shutdown(void);` (scope `Filesystem`)
- L21 _prototype_ `DriveType::Enum GetDriveType(const wchar_t* path);` (scope `Filesystem`) — Returns the type of a drive. Drive letters can be both lower-case or upper-case.
- L24 _prototype_ `PathAttributes GetAttributes(const wchar_t* path);` (scope `Filesystem`) — Retrieves a path's attributes. The given path can point to any file or directory in the file system.
- L27 _prototype_ `uint64_t GetSize(const PathAttributes& attributes);` (scope `Filesystem`) — Returns the size of the file or directory that corresponds to the given attributes.
- L30 _prototype_ `uint64_t GetLastModificationTime(const PathAttributes& attributes);` (scope `Filesystem`) — Returns the last modification time for any path's attributes.
- L33 _prototype_ `bool DoesExist(const PathAttributes& attributes);` (scope `Filesystem`) — Returns whether a path exists.
- L36 _prototype_ `bool IsDirectory(const PathAttributes& attributes);` (scope `Filesystem`) — Returns whether given attributes correspond to a directory.
- L39 _prototype_ `bool IsRelativePath(const wchar_t* path);` (scope `Filesystem`) — Returns whether the given path is a relative path.
- L42 _prototype_ `void Copy(const wchar_t* srcPath, const wchar_t* destPath);` (scope `Filesystem`) — Copies a file from source to destination.
- L45 _prototype_ `void Move(const wchar_t* currentPath, const wchar_t* movedToPath);` (scope `Filesystem`) — Moves a file from source to destination.
- L48 _prototype_ `void Delete(const wchar_t* path);` (scope `Filesystem`) — Deletes a file, reports an error if the file cannot be deleted.
- L51 _prototype_ `bool DeleteIfExists(const wchar_t* path);` (scope `Filesystem`) — Deletes a file only if it exists, without reporting an error.
- L55 _prototype_ `Path GenerateTempFilename(void);` (scope `Filesystem`) — Creates a unique, temporary absolute filename, e.g. C:\Users\JohnDoe\AppData\Local\Temp\ABCD.tmp
- L58 _prototype_ `Path GetDirectory(const wchar_t* path);` (scope `Filesystem`) — Returns the directory part of a given path, e.g. GetDirectory("C:\Directory\File.txt") returns "C:\Directory".
- L61 _prototype_ `Path GetFilename(const wchar_t* path);` (scope `Filesystem`) — Returns the file part of a given path, e.g. GetFilename("C:\Directory\File.txt") returns "File.txt".
- L64 _prototype_ `Path GetExtension(const wchar_t* path);` (scope `Filesystem`) — Returns the extension part of a given path, e.g. GetExtension("C:\Directory\File.txt") returns ".txt".
- L67 _prototype_ `Path RemoveExtension(const wchar_t* path);` (scope `Filesystem`) — Returns the given path without any file extensions, e.g. RemoveExtension("C:\Directory\File.internal.txt") returns "C:\Directory\File".
- L70 _prototype_ `Path NormalizePath(const wchar_t* path);` (scope `Filesystem`) — Canonicalizes/normalizes any given path.
- L74 _prototype_ `Path NormalizePathWithoutResolvingLinks(const wchar_t* path);` (scope `Filesystem`) — Canonicalizes/normalizes any given path without resolving any symbolic links/virtual drives. NOTE: This is not cached internally and should only be used for cosmetic purposes.
- L78 _prototype_ `bool CreateFileWithData(const wchar_t* path, const void* data, size_t size);` (scope `Filesystem`) — Creates a file, storing the given data.
- L82 _prototype_ `types::vector<Path> EnumerateFiles(const wchar_t* directory);` (scope `Filesystem`) — Recursively enumerates all files in a directory. Returns an array of filenames relative to the given directory, e.g. file1.txt, file2.txt, dir\file.txt, dir\subDir\file.txt.

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_FunctionPatcher.h` (Private)


#### struct `functions::Record`  
`struct Record`  
_L17-24_
- L19 _public member_ `const symbols::ThunkDB* thunkDb;`
- L20 _public member_ `uint32_t functionRva;`
- L21 _public member_ `uint32_t patchFunctionRva;`
- L22 _public member_ `uint16_t patchIndex;`
- L23 _public member_ `uint8_t directJumpInstructionSize;`

#### struct `functions::LibraryRecord`  
`struct LibraryRecord`  
_L26-32_
- L28 _public member_ `uint32_t srcRva;`
- L29 _public member_ `uint32_t destRva;`
- L30 _public member_ `uint16_t patchIndex;`
- L31 _public member_ `uint16_t wholeInstructionSize;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace functions`
- L34 _prototype_ `Record PatchFunction ( char* originalAddress, char* patchAddress, uint32_t functionRva, uint32_t patchFunctionRva, const symbols::ThunkDB* thunkDb, const symbols::Contribution* contribution, Process::Handle processHandle, void* moduleBase, uint16_t moduleIndex, types::unordered_set<const void*>& patchedAddresses, const types::vector<const void*>& threadIPs,` (scope `functions`)
- L53 _prototype_ `LibraryRecord PatchLibraryFunction ( char* srcAddress, char* destAddress, uint32_t srcRva, uint32_t destRva, const symbols::Contribution* contribution, Process::Handle processHandle, uint16_t moduleIndex );` (scope `functions`)
- L64 _prototype_ `void PatchFunction ( const Record& record, Process::Handle processHandle, void* processModuleBases[], void* newModuleBase, types::unordered_set<const void*>& patchedAddresses, const types::vector<const void*>& threadIPs );` (scope `functions`)
- L74 _prototype_ `void PatchLibraryFunction ( const LibraryRecord& record, Process::Handle processHandle, void* processModuleBases[], void* newModuleBase );` (scope `functions`)
- L82 _prototype_ `bool IsValidRecord(const Record& record);` (scope `functions`)
- L83 _prototype_ `bool IsValidRecord(const LibraryRecord& record);` (scope `functions`)

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_GrowingMemoryBlock.h` (Private)


#### class `GrowingMemoryBlock`  
`class GrowingMemoryBlock`  
_L13-40_
- L16 _public prototype_ `explicit GrowingMemoryBlock(size_t initialCapacity);`
- L17 _public prototype_ `~GrowingMemoryBlock(void);`
- L19 _public prototype_ `bool Insert(const void* data, size_t size);`
- L21 _public function_ `inline const void* GetData(void) const`
- L26 _public function_ `inline size_t GetSize(void) const`
- L32 _private member_ `size_t m_capacity;`
- L33 _private member_ `size_t m_size;`
- L34 _private member_ `uint8_t* m_data;`
- L36 _private prototype_ `LC_DISABLE_COPY(GrowingMemoryBlock);`
- L37 _private prototype_ `LC_DISABLE_MOVE(GrowingMemoryBlock);`
- L38 _private prototype_ `LC_DISABLE_ASSIGNMENT(GrowingMemoryBlock);`
- L39 _private prototype_ `LC_DISABLE_MOVE_ASSIGNMENT(GrowingMemoryBlock);`

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_Hook.h` (Private)


#### struct `hook::Type`  
`struct Type`  
_L22-33_

#### enum `hook::Type::Enum`  
`enum Enum`  
_L24-32_
- L26 _public enumerator_ `PREPATCH = 0`
- L27 _public enumerator_ `POSTPATCH`
- L28 _public enumerator_ `COMPILE_START`
- L29 _public enumerator_ `COMPILE_SUCCESS`
- L30 _public enumerator_ `COMPILE_ERROR`
- L31 _public enumerator_ `COMPILE_ERROR_MESSAGE`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace symbols`
- L20 _namespace_ `namespace hook`
- L35 _typedef_ `typedef void (*PrepatchFunction)(void);` (scope `hook`)
- L36 _typedef_ `typedef void (*PostpatchFunction)(void);` (scope `hook`)
- L38 _typedef_ `typedef void (*CompileStartFunction)(void);` (scope `hook`)
- L39 _typedef_ `typedef void (*CompileSuccessFunction)(void);` (scope `hook`)
- L40 _typedef_ `typedef void (*CompileErrorFunction)(void);` (scope `hook`)
- L41 _typedef_ `typedef void (*CompileErrorMessageFunction)(const wchar_t*);` (scope `hook`)
- L43 _prototype_ `uint32_t FindFirstInSection(const symbols::ImageSectionDB* imageSectionDb, const ImmutableString& sectionName);` (scope `hook`)
- L44 _prototype_ `uint32_t FindLastInSection(const symbols::ImageSectionDB* imageSectionDb, const ImmutableString& sectionName);` (scope `hook`)
- L49 _function_ `template <typename T, typename... Args> void CallHooksInRange(const void* rangeBegin, const void* rangeEnd, Args&&... args)` (scope `hook`) — calls arbitrary hooks in a given range

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_ImmutableString.h` (Private)


#### class `ImmutableString`  
`class ImmutableString`  
_L31-188_
- L34 _public member_ `static const uint32_t NOT_FOUND = 0xFFFFFFFFu;`
- L52 _public function_ `inline bool operator==(const ImmutableString& rhs) const`
- L79 _public function_ `inline bool operator!=(const ImmutableString& rhs) const`
- L85 _public prototype_ `ImmutableString(void);` — leaves the string empty, does not allocate anything
- L88 _public prototype_ `explicit ImmutableString(const char* str);` — copy and hash
- L91 _public prototype_ `ImmutableString(const char* str, size_t length);` — copy and hash
- L94 _public prototype_ `ImmutableString(const ImmutableString& other);` — copy
- L97 _public prototype_ `ImmutableString(ImmutableString&& other);` — move constructor
- L100 _public prototype_ `ImmutableString& operator=(const ImmutableString& other) = delete;` — disallow assignment operator
- L103 _public prototype_ `ImmutableString& operator=(ImmutableString&& other);` — move assignment operator
- L106 _public prototype_ `~ImmutableString(void);` — destructor
- L108 _public prototype_ `uint32_t Find(char character) const;`
- L110 _public function_ `inline uint32_t GetHash(void) const`
- L115 _public function_ `inline uint32_t GetLength(void) const`
- L128 _public function_ `inline const char* c_str(void) const`
- L145 _private function_ `static inline bool FitsIntoShortString(size_t lengthWithoutNullTerminator)` — short string optimization: the layout of the long string is chosen so that we can store extra information in the first byte of length, assuming that no string will ever be longer than 2^24-1 characters. NOTE: on little-endian architectures, LongString::length conincides with the memory address of ShortString::length
- L150 _private function_ `inline bool IsShortString(void) const`
- L156 _private prototype_ `void Free(void);`
- L187 _private member_ `Data m_data;`

#### struct `ImmutableString::Hasher`  
`struct Hasher`  
_L36-42_
- L38 _public function_ `LC_ALWAYS_INLINE size_t operator()(const ImmutableString& key) const`

#### struct `ImmutableString::Comparator`  
`struct Comparator`  
_L44-50_
- L46 _public function_ `LC_ALWAYS_INLINE bool operator()(const ImmutableString& lhs, const ImmutableString& rhs) const`

#### struct `ImmutableString::LongString`  
`struct LongString`  
_L160-165_
- desc: layout of a long string: 4/8 bytes pointer to string, 3 byte length, 1 zero byte, 4 byte hash
- L162 _public member_ `const char* str;`
- L163 _public member_ `uint32_t length;`
- L164 _public member_ `uint32_t hash;`

#### struct `ImmutableString::ShortString`  
`struct ShortString`  
_L169-177_
- desc: layout of a short string: the actual string data (including the null terminator), 1 byte storing the length of the short string, 4 byte hash
- L171 _public member_ `static const uint8_t MSB_SET_MASK = 0x80u;` — mask for setting the MSB
- L172 _public member_ `static const uint8_t MSB_CLEAR_MASK = 0x7Fu;` — mask for clearing the MSB
- L174 _public member_ `char str[sizeof(const char*) + sizeof(uint32_t) - 1];`
- L175 _public member_ `uint8_t length;`
- L176 _public member_ `uint32_t hash;`

#### union `ImmutableString::Data`  
`union Data`  
_L181-185_
- L183 _public member_ `LongString longString;`
- L184 _public member_ `ShortString shortString;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace string`
- L22 _prototype_ `ImmutableString ToUtf8String(const wchar_t* str);` (scope `string`)
- L23 _prototype_ `ImmutableString ToUtf8String(const wchar_t* str, size_t count);` (scope `string`)
- L24 _prototype_ `ImmutableString ToUtf8String(const std::wstring& str);` (scope `string`)
- L26 _prototype_ `std::string ToAnsiString(const ImmutableString& utf8Str);` (scope `string`)
- L27 _prototype_ `std::wstring ToWideString(const ImmutableString& utf8Str);` (scope `string`)

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_Key.h` (Private)


#### class `input::Key`  
`class Key`  
_L13-29_
- L16 _public prototype_ `explicit Key(int vkCode);`
- L18 _public prototype_ `void AssignCode(int vkCode);`
- L20 _public prototype_ `void Clear(void);`
- L21 _public prototype_ `void Update(void);`
- L22 _public prototype_ `bool IsPressed(void) const;`
- L23 _public prototype_ `bool WentDown(void) const;`
- L26 _private member_ `int m_vkCode;`
- L27 _private member_ `bool m_isPressed;`
- L28 _private member_ `bool m_wasPressed;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace input`

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_LiveModule.h` (Private)


#### class `LiveModule`  
`class LiveModule`  
_L27-160_
- L65 _public prototype_ `LiveModule(const wchar_t* moduleName, const executable::Header& imageHeader, RunMode::Enum runMode);`
- L66 _public prototype_ `~LiveModule(void);`
- L68 _public prototype_ `void Load(symbols::Provider* provider, symbols::DiaCompilandDB* diaCompilandDb);`
- L71 _public prototype_ `void Unload(void);` — unloads all patches that have been loaded into all processes so far
- L73 _public prototype_ `void RegisterProcess(LiveProcess* liveProcess, void* moduleBase, const std::wstring& modulePath);`
- L74 _public prototype_ `void UnregisterProcess(LiveProcess* liveProcess);`
- L76 _public prototype_ `void DisableControlFlowGuard(LiveProcess* liveProcess, void* moduleBase);`
- L78 _public prototype_ `void UpdateDirectoryCache(DirectoryCache* cache);`
- L85 _public prototype_ `ErrorType::Enum Update(FileAttributeCache* fileCache, DirectoryCache* directoryCache, UpdateType::Enum updateType, const types::vector<symbols::ModifiedObjFile>& modifiedOrNewObjFiles, const types::vector<std::wstring>& additionalLibraries);` — builds a patch for this module according to changed files. in DEFAULT mode, this checks for file modifications, compiles files automatically, builds a patch containing changes, and loads them into the host application. in EXTERNAL_BUILD_SYSTEM mode, this does not compile files but builds a patch containing modified .objs, loading the patch into the host application. optionally, an array of modified or new .objs can be given in this mode, which builds a patch containing these files, not checking for any other modifications. BEGIN EPIC MOD
- L87 _public prototype_ `bool InstallCompiledPatches(LiveProcess* liveProcess, void* originalModuleBase);` — END EPIC MOD
- L89 _public prototype_ `const std::wstring& GetModuleName(void) const;`
- L90 _public prototype_ `const executable::Header& GetImageHeader(void) const;`
- L92 _public prototype_ `const symbols::CompilandDB* GetCompilandDatabase(void) const;`
- L93 _public prototype_ `const symbols::LinkerDB* GetLinkerDatabase(void) const;`
- L95 _public prototype_ `bool HasInstalledPatches(void) const;`
- L98 _public prototype_ `bool IsModifiedSource(const wchar_t* sourceFile) const;` — BEGIN EPIC MOD
- L102 _private prototype_ `void UpdateDirectoryCache(const ImmutableString& path, symbols::Dependency* dependency, DirectoryCache* cache);`
- L104 _private prototype_ `void OnCompiledFile(const symbols::ObjPath& objPath, symbols::Compiland* compiland, const CompileResult& compileResult, double compileTime, bool forceAmalgamationPartsLinkage);`
- L122 _private member_ `std::wstring m_moduleName;`
- L123 _private member_ `executable::Header m_imageHeader;`
- L124 _private member_ `RunMode::Enum m_runMode;`
- L125 _private member_ `size_t m_mainModuleToken = 0u;`
- L128 _private member_ `types::vector<PerProcessData> m_perProcessData;` — data that stores which processes loaded this module at which address originally
- L131 _private member_ `CoffCache<coff::CoffDB>* m_coffCache = nullptr;` — caches
- L132 _private member_ `ModuleCache* m_moduleCache = nullptr;`
- L133 _private member_ `types::StringSet m_reconstructedCompilands;`
- L136 _private member_ `symbols::SymbolDB* m_symbolDB = nullptr;` — main databases
- L137 _private member_ `symbols::ContributionDB* m_contributionDB = nullptr;`
- L138 _private member_ `symbols::CompilandDB* m_compilandDB = nullptr;`
- L139 _private member_ `symbols::LibraryDB* m_libraryDB = nullptr;`
- L140 _private member_ `symbols::LinkerDB* m_linkerDB = nullptr;`
- L141 _private member_ `symbols::ThunkDB* m_thunkDB = nullptr;`
- L142 _private member_ `symbols::ImageSectionDB* m_imageSectionDB = nullptr;`
- L143 _private member_ `types::StringMap<types::vector<const symbols::Symbol*>> m_externalSymbolsPerCompilandCache;`
- L144 _private member_ `types::StringMap<ImmutableString> m_pchSymbolToCompilandName;`
- L147 _private member_ `types::unordered_map<Process::Id, types::unordered_set<const void*>> m_patchedAddressesPerProcess;` — patch data
- L148 _private member_ `unsigned int m_patchCounter = 0u;`
- L151 _private member_ `types::StringSet m_modifiedFiles;` — data pertaining to the next patch
- L152 _private member_ `types::StringMap<symbols::Compiland*> m_compiledCompilands;`
- L155 _private member_ `types::vector<ModulePatch*> m_compiledModulePatches;` — all patches loaded so far along with recorded data how to load them into other processes
- L158 _private member_ `types::StringMap<uint32_t> m_objFileToCompilandId;` — BEGIN EPIC MOD - Allow mapping from object files to their unity object file

#### struct `LiveModule::PerProcessData`  
`struct PerProcessData`  
_L30-35_
- L32 _public member_ `LiveProcess* liveProcess;`
- L33 _public member_ `void* originalModuleBase;`
- L34 _public member_ `std::wstring modulePath;`

#### struct `LiveModule::ErrorType`  
`struct ErrorType`  
_L37-48_

#### enum `LiveModule::ErrorType::Enum`  
`enum Enum`  
_L39-47_
- L41 _public enumerator_ `NO_CHANGE`
- L42 _public enumerator_ `COMPILE_ERROR`
- L43 _public enumerator_ `LINK_ERROR`
- L44 _public enumerator_ `LOAD_PATCH_ERROR`
- L45 _public enumerator_ `ACTIVATE_PATCH_ERROR`
- L46 _public enumerator_ `SUCCESS`

#### struct `LiveModule::UpdateType`  
`struct UpdateType`  
_L50-57_

#### enum `LiveModule::UpdateType::Enum`  
`enum Enum`  
_L52-56_
- L54 _public enumerator_ `DEFAULT`
- L55 _public enumerator_ `NO_CLIENT_COMMUNICATION`

#### struct `LiveModule::CompileResult`  
`struct CompileResult`  
_L59-63_
- L61 _public member_ `unsigned int exitCode;`
- L62 _public member_ `bool wasCompiled;`

#### struct `LiveModule::actions`  
`struct actions`  
_L107-119_
- desc: actions
- L116 _public prototype_ `DECLARE_ACTION(LoadPatchInfo);`

#### Free symbols / members of external scopes

- L109 _macro_ `#define DECLARE_ACTION(_name) \`

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_LiveProcess.h` (Private)


#### class `LiveProcess`  
`class LiveProcess`  
_L21-207_
- L24 _public prototype_ `LiveProcess(Process::Handle processHandle, Process::Id processId, Thread::Id commandThreadId, const void* jumpToSelf, const DuplexPipe* pipe, const wchar_t* imagePath, const wchar_t* commandLine, const wchar_t* workingDirectory, const void* environment, size_t environmentSize);`
- L27 _public prototype_ `void ReadHeartBeatDelta(const wchar_t* const processGroupName);`
- L30 _public prototype_ `bool MadeProgress(void) const;` — returns whether this process made some progress, based on the heart beat received from the client
- L33 _public prototype_ `void HandleDebuggingPreCompile(void);` — handles any debugging mechanism that might currently debug our process before we compile changes
- L36 _public prototype_ `void HandleDebuggingPostCompile(void);` — handles any debugging mechanism that might currently debug our process after we compiled changes
- L38 _public prototype_ `void InstallCodeCave(void);`
- L39 _public prototype_ `void UninstallCodeCave(void);`
- L41 _public prototype_ `void AddLoadedImage(const executable::Header& imageHeader);`
- L42 _public prototype_ `void RemoveLoadedImage(const executable::Header& imageHeader);`
- L43 _public prototype_ `bool TriedToLoadImage(const executable::Header& imageHeader) const;`
- L46 _public prototype_ `bool PrepareForRestart(void);`
- L47 _public prototype_ `void WaitForExitBeforeRestart(void);`
- L49 _public prototype_ `void Restart(void* restartJob);` — BEGIN EPIC MOD
- L51 _public prototype_ `bool WasSuccessfulRestart(void) const;` — END EPIC MOD
- L54 _public prototype_ `void ReserveVirtualMemoryPages(void* moduleBase);`
- L55 _public prototype_ `void FreeVirtualMemoryPages(void* moduleBase);`
- L58 _public function_ `inline Process::Handle GetProcessHandle(void) const`
- L63 _public function_ `inline Process::Id GetProcessId(void) const`
- L68 _public function_ `inline Thread::Id GetCommandThreadId(void) const`
- L73 _public function_ `inline const void* GetJumpToSelf(void) const`
- L78 _public function_ `inline const DuplexPipe* GetPipe(void) const`
- L84 _public function_ `inline void SetBuildArguments(const wchar_t* buildArguments)` — BEGIN EPIC MOD - Add build arguments
- L89 _public function_ `inline const wchar_t* GetBuildArguments()`
- L102 _public prototype_ `void AddLazyLoadedModule(const std::wstring moduleName, Windows::HMODULE moduleBase);`
- L103 _public prototype_ `void SetLazyLoadedModuleAsLoaded(const std::wstring moduleName);`
- L104 _public prototype_ `bool IsPendingLazyLoadedModule(const std::wstring& moduleName) const;`
- L105 _public function_ `const types::unordered_map<std::wstring, LazyLoadedModule>& GetLazyLoadedModules() const`
- L106 _public prototype_ `Windows::HMODULE GetLazyLoadedModuleBase(const std::wstring& moduleName) const;`
- L110 _public function_ `void SetReinstancingFlow(bool enable)` — BEGIN EPIC MOD
- L114 _public function_ `bool IsReinstancingFlowEnabled() const`
- L121 _public function_ `void DisableCompileFinishNotification()` — BEGIN EPIC MOD
- L125 _public function_ `bool IsDisableCompileFinishNotification()`
- L132 _public function_ `void AddPage(void *page)` — BEGIN EPIC MOD
- L139 _private member_ `Process::Handle m_processHandle;`
- L140 _private member_ `Process::Id m_processId;`
- L141 _private member_ `Thread::Id m_commandThreadId;`
- L142 _private member_ `const void* m_jumpToSelf;`
- L143 _private member_ `const DuplexPipe* m_pipe;`
- L145 _private member_ `std::wstring m_imagePath;`
- L146 _private member_ `std::wstring m_commandLine;`
- L147 _private member_ `std::wstring m_workingDirectory;`
- L148 _private member_ `MemoryBlock m_environment;`
- L151 _private member_ `std::wstring m_buildArguments;` — BEGIN EPIC MOD - Add build arguments
- L155 _private member_ `types::unordered_map<std::wstring, LazyLoadedModule> m_lazyLoadedModules;` — BEGIN EPIC MOD - Allow lazy-loading modules
- L159 _private member_ `bool m_reinstancingFlow = false;` — BEGIN EPIC MOD
- L163 _private member_ `bool m_disableCompileFinishNotification = false;` — BEGIN EPIC MOD
- L169 _private member_ `types::unordered_set<executable::Header> m_imagesTriedToLoad;` — loaded modules are not identified by their full path, but by their executable image header. we do this to ensure that the same executable loaded from a different path is not treated as a different executable.
- L171 _private member_ `uint64_t m_heartBeatDelta;`
- L177 _private member_ `EnvDTE::DebuggerPtr m_vsDebugger;` — END EPIC MOD for handling communication with the VS debugger
- L178 _private member_ `types::vector<EnvDTE::ThreadPtr> m_vsDebuggerThreads;`
- L184 _private member_ `CodeCave* m_codeCave;` — fallback in case communication with the VS debugger is not possible
- L199 _private member_ `RestartState::Enum m_restartState;`
- L201 _private member_ `VirtualMemoryRange m_virtualMemoryRange;`
- L203 _private prototype_ `LC_DISABLE_COPY(LiveProcess);`
- L204 _private prototype_ `LC_DISABLE_MOVE(LiveProcess);`
- L205 _private prototype_ `LC_DISABLE_ASSIGNMENT(LiveProcess);`
- L206 _private prototype_ `LC_DISABLE_MOVE_ASSIGNMENT(LiveProcess);`

#### struct `LiveProcess::LazyLoadedModule`  
`struct LazyLoadedModule`  
_L96-100_
- desc: BEGIN EPIC MOD - Allow lazy-loading modules
- L98 _public member_ `Windows::HMODULE m_moduleBase;`
- L99 _public member_ `bool m_loaded;`

#### struct `LiveProcess::RestartState`  
`struct RestartState`  
_L187-197_
- desc: restart

#### enum `LiveProcess::RestartState::Enum`  
`enum Enum`  
_L189-196_
- L191 _public enumerator_ `DEFAULT`
- L192 _public enumerator_ `FAILED_PREPARE`
- L193 _public enumerator_ `SUCCESSFUL_PREPARE`
- L194 _public enumerator_ `SUCCESSFUL_EXIT`
- L195 _public enumerator_ `SUCCESSFUL_RESTART`

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_Mallocator.h` (Private)


#### class `Mallocator`  
`class Mallocator`  
_L15-34_
- desc: thread-safe
- L18 _public prototype_ `Mallocator(const char* name, size_t alignment);`
- L20 _public prototype_ `void* Allocate(size_t size, size_t alignment);`
- L21 _public prototype_ `void Free(void* ptr, size_t size);`
- L23 _public prototype_ `void PrintStats(void) const;`
- L25 _public prototype_ `const AllocatorStats& GetStats(void) const;`
- L29 _private member_ `Windows::HANDLE m_heap;` — BEGIN EPIC MOD
- L31 _private member_ `const char* m_name;` — END EPIC MOD
- L32 _private member_ `size_t m_alignment;`
- L33 _private member_ `AllocatorStats m_stats;`

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_MemoryBlock.h` (Private)


#### class `MemoryBlock`  
`class MemoryBlock`  
_L13-37_
- L16 _public prototype_ `MemoryBlock(const void* data, size_t size);`
- L17 _public prototype_ `~MemoryBlock(void);`
- L19 _public function_ `inline const void* GetData(void) const`
- L24 _public function_ `inline size_t GetSize(void) const`
- L30 _private member_ `void* m_data;`
- L31 _private member_ `size_t m_size;`
- L33 _private prototype_ `LC_DISABLE_COPY(MemoryBlock);`
- L34 _private prototype_ `LC_DISABLE_MOVE(MemoryBlock);`
- L35 _private prototype_ `LC_DISABLE_ASSIGNMENT(MemoryBlock);`
- L36 _private prototype_ `LC_DISABLE_MOVE_ASSIGNMENT(MemoryBlock);`

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_MicroAllocator.h` (Private)


#### class `MicroAllocator`  
`class MicroAllocator`  
_L18-36_
- desc: thread-safe
- L20 _private member_ `static const size_t POOL_ALLOCATOR_COUNT = 1024u;`
- L21 _private member_ `static const size_t ELEMENT_COUNT_PER_POOL_GROWTH = 128u;`
- L24 _public prototype_ `MicroAllocator(const char* name, size_t alignment);`
- L25 _public prototype_ `~MicroAllocator(void);`
- L27 _public prototype_ `void* Allocate(size_t size, size_t alignment);`
- L28 _public prototype_ `void Free(void* ptr, size_t size);`
- L30 _public prototype_ `void PrintStats(void) const;`
- L33 _private member_ `PoolAllocator<PoolAllocatorMultiThreadPolicy>* m_poolAllocators[POOL_ALLOCATOR_COUNT + 1u];`
- L34 _private member_ `Mallocator m_blockAllocator;`
- L35 _private member_ `const char* m_name;`

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_ModuleCache.h` (Private)


#### class `ModuleCache`  
`class ModuleCache`  
_L20-108_
- desc: thread-safe
- L23 _public member_ `static const size_t SEARCH_ALL_MODULES = static_cast<size_t>(-1);`
- L64 _public prototype_ `ModuleCache(void);`
- L70 _public prototype_ `size_t Insert(const symbols::SymbolDB* symbolDb, const symbols::ContributionDB* contributionDb, const symbols::CompilandDB* compilandDb, const symbols::ThunkDB* thunkDb, const symbols::ImageSectionDB* imageSectionDb, uint64_t lastModicationTime);` — adds an entry to the cache. does not take ownership of the databases. returns a token for registering a process associated with this entry. BEGIN EPIC MOD
- L74 _public prototype_ `void RegisterProcess(size_t token, LiveProcess* liveProcess, void* moduleBase);` — associates a process with an entry identified by a previously returned token.
- L77 _public prototype_ `void UnregisterProcess(LiveProcess* liveProcess);` — removes a process from all entries
- L81 _public prototype_ `FindSymbolData FindSymbolByName(size_t ignoreToken, const ImmutableString& symbolName) const;` — tries finding a symbol by name, starting from the first module, walking to the latest, excluding the module with the given token
- L85 _public prototype_ `FindSymbolData FindSymbolByNameBackwards(size_t ignoreToken, const ImmutableString& symbolName) const;` — BEGIN EPIC MOD tries finding a symbol by name, starting from the last module, walking to the first, excluding the module with the given token
- L89 _public prototype_ `FindHookData FindHooksInSectionBackwards(size_t ignoreToken, const ImmutableString& sectionName) const;` — tries finding the first and last hook in a given section, starting from the newest module, walking to the first, excluding the module with the given token
- L92 _public prototype_ `types::vector<void*> GatherModuleBases(Process::Id processId) const;`
- L95 _public function_ `inline size_t GetSize(void) const`
- L100 _public function_ `inline const Data& GetEntry(size_t i) const`
- L106 _private member_ `mutable CriticalSection m_cs;`
- L107 _private member_ `types::vector<Data> m_cache;`

#### struct `ModuleCache::ProcessData`  
`struct ProcessData`  
_L25-34_
- L29 _public member_ `Process::Id processId;` — all data except moduleBase is redundant and stored per cache entry, but this doesn't increase memory requirements by much. we'd rather have all information accessible fast.
- L30 _public member_ `Process::Handle processHandle;`
- L31 _public member_ `const DuplexPipe* pipe;`
- L33 _public member_ `void* moduleBase;`

#### struct `ModuleCache::Data`  
`struct Data`  
_L36-49_
- L38 _public member_ `uint16_t index;` — index of the patch corresponding to the data (0 = original executable)
- L39 _public member_ `const symbols::SymbolDB* symbolDb;`
- L40 _public member_ `const symbols::ContributionDB* contributionDb;`
- L41 _public member_ `const symbols::CompilandDB* compilandDb;`
- L42 _public member_ `const symbols::ThunkDB* thunkDb;`
- L43 _public member_ `const symbols::ImageSectionDB* imageSectionDb;`
- L45 _public member_ `uint64_t lastModificationTime;` — BEGIN EPIC MOD
- L48 _public member_ `types::vector<ProcessData> processes;` — all processes that this patch is loaded into

#### struct `ModuleCache::FindSymbolData`  
`struct FindSymbolData`  
_L51-55_
- L53 _public member_ `const Data* data;`
- L54 _public member_ `const symbols::Symbol* symbol;`

#### struct `ModuleCache::FindHookData`  
`struct FindHookData`  
_L57-62_
- L59 _public member_ `const Data* data;`
- L60 _public member_ `uint32_t firstRva;`
- L61 _public member_ `uint32_t lastRva;`

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_ModulePatch.h` (Private)


#### class `ModulePatch`  
`class ModulePatch`  
_L15-87_
- L51 _public prototype_ `ModulePatch(const std::wstring& exePath, const std::wstring& pdbPath, size_t token);`
- L53 _public prototype_ `void RegisterEntryPointCode(const uint8_t* code);`
- L55 _public prototype_ `void RegisterPrePatchHooks(uint16_t moduleIndex, uint32_t firstRva, uint32_t lastRva);`
- L56 _public prototype_ `void RegisterPostPatchHooks(uint16_t moduleIndex, uint32_t firstRva, uint32_t lastRva);`
- L59 _public prototype_ `void RegisterSecurityCookie(uint32_t originalRva, uint32_t patchRva);` — Security cookie
- L62 _public prototype_ `void RegisterUe4NameTable(uint32_t originalRva, uint32_t patchRva);` — UE4-specific
- L63 _public prototype_ `void RegisterUe4ObjectArray(uint32_t originalRva, uint32_t patchRva);`
- L65 _public prototype_ `void RegisterDllMain(uint32_t rva);`
- L67 _public prototype_ `void RegisterPreEntryPointRelocation(const relocations::Record& record);`
- L68 _public prototype_ `void RegisterPostEntryPointRelocation(const relocations::Record& record);`
- L70 _public prototype_ `void RegisterPatchedDynamicInitializer(uint32_t rva);`
- L72 _public prototype_ `void RegisterFunctionPatch(const functions::Record& record);`
- L73 _public prototype_ `void RegisterLibraryFunctionPatch(const functions::LibraryRecord& record);`
- L75 _public prototype_ `const std::wstring& GetExePath(void) const;`
- L76 _public prototype_ `const std::wstring& GetPdbPath(void) const;`
- L77 _public prototype_ `size_t GetToken(void) const;`
- L79 _public prototype_ `const Data& GetData(void) const;`
- L82 _private member_ `std::wstring m_exePath;`
- L83 _private member_ `std::wstring m_pdbPath;`
- L84 _private member_ `size_t m_token;`
- L86 _private member_ `Data m_data;`

#### struct `ModulePatch::Data`  
`struct Data`  
_L18-49_
- L20 _public member_ `uint8_t entryPointCode[ExecutablePatcher::INJECTED_CODE_SIZE];`
- L22 _public member_ `uint16_t prePatchHookModuleIndex;`
- L23 _public member_ `uint32_t firstPrePatchHook;`
- L24 _public member_ `uint32_t lastPrePatchHook;`
- L26 _public member_ `uint16_t postPatchHookModuleIndex;`
- L27 _public member_ `uint32_t firstPostPatchHook;`
- L28 _public member_ `uint32_t lastPostPatchHook;`
- L31 _public member_ `uint32_t originalCookieRva;` — security cookie
- L32 _public member_ `uint32_t patchCookieRva;`
- L35 _public member_ `uint32_t originalUe4NameTableRva;` — UE4-specific
- L36 _public member_ `uint32_t patchUe4NameTableRva;`
- L37 _public member_ `uint32_t originalUe4ObjectArrayRva;`
- L38 _public member_ `uint32_t patchUe4ObjectArrayRva;`
- L40 _public member_ `uint32_t dllMainRva;`
- L42 _public member_ `types::vector<relocations::Record> preEntryPointRelocations;`
- L43 _public member_ `types::vector<relocations::Record> postEntryPointRelocations;`
- L45 _public member_ `types::vector<uint32_t> patchedInitializers;`
- L47 _public member_ `types::vector<functions::Record> functionPatches;`
- L48 _public member_ `types::vector<functions::LibraryRecord> libraryFunctionPatches;`

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_NameMangling.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace nameMangling`
- L33 _prototype_ `std::string UndecorateSymbol(const char* symbolName, uint16_t flags);` (scope `nameMangling`) — 0x0001	Remove leading underscores from Microsoft extended keywords 0x0002	Disable expansion of Microsoft extended keywords 0x0004	Disable expansion of return type for primary declaration 0x0008	Disable expansion of the declaration model 0x0010	Disable expansion of the declaration language specifier 0x0060	Disable all modifiers on the 'this' type 0x0080	Disable expansion of access specifiers for members 0x0100	Disable expansion of 'throw-signatures' for functions and pointers to functions 0x0200	Disable expansion of 'static' or 'virtual'ness of members 0x0400	Disable expansion of Microsoft model for UDT returns 0x0800	Undecorate 32 - bit decorated names 0x1000	Crack only the name for primary declaration return just[scope::]name. Does expand template params 0x2000	Input is just a type encoding; compose an abstract declarator 0x8000	Disable enum / class / struct / union prefix 0x20000	Disable expansion of __ptr64 keyword -> this cannot be used because it doesn't fit into 16-bit flags
- L34 _prototype_ `std::wstring UndecorateSymbolWide(const char* symbolName, uint16_t flags);` (scope `nameMangling`)

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_OutputFile.h` (Private)


#### class `OutputFile`  
`class OutputFile`  
_L12-26_
- L15 _public prototype_ `explicit OutputFile(const wchar_t* logFilePath);`
- L16 _public prototype_ `~OutputFile(void);`
- L18 _public prototype_ `void Log(const char* msg);`
- L21 _private prototype_ `void WriteToFile(const char* text);`
- L24 _private member_ `Windows::HANDLE m_logFile;` — BEGIN EPIC MOD

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_Patch.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace patch`
- L15 _prototype_ `void InstallNOPs(Process::Handle processHandle, void* address, uint8_t size);` (scope `patch`)
- L16 _prototype_ `void InstallJumpToSelf(Process::Handle processHandle, void* address);` (scope `patch`)
- L18 _prototype_ `void InstallRelativeShortJump(Process::Handle processHandle, void* address, void* destination);` (scope `patch`)
- L19 _prototype_ `void InstallRelativeNearJump(Process::Handle processHandle, void* address, void* destination);` (scope `patch`)

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_PoolAllocator.h` (Private)


#### struct `PoolAllocatorSingleThreadPolicy`  
`struct PoolAllocatorSingleThreadPolicy`  
_L14-18_
- L16 _public function_ `inline void Enter(void)`
- L17 _public function_ `inline void Leave(void)`

#### class `PoolAllocatorMultiThreadPolicy`  
`class PoolAllocatorMultiThreadPolicy`  
_L20-35_
- L23 _public function_ `inline void Enter(void)`
- L28 _public function_ `inline void Leave(void)`
- L34 _private member_ `CriticalSection m_cs;`

#### class `PoolAllocator`  
`template <typename T> class PoolAllocator`  
_L40-71_
- desc: thread-safe when used with a thread-safe policy
- L43 _public prototype_ `PoolAllocator(const char* name, size_t maxElementSize, size_t maxAlignment, size_t growSize);`
- L44 _public prototype_ `~PoolAllocator(void);`
- L46 _public prototype_ `void* Allocate(size_t size, size_t alignment);`
- L47 _public prototype_ `void Free(void* ptr, size_t size);`
- L49 _public prototype_ `void Purge(void);`
- L51 _public prototype_ `void PrintStats(void) const;`
- L53 _public prototype_ `const AllocatorStats& GetStats(void) const;`
- L61 _private member_ `void* m_freeList;`
- L62 _private member_ `T m_threadPolicy;`
- L63 _private member_ `size_t m_maxSize;`
- L64 _private member_ `size_t m_maxAlignment;`
- L65 _private member_ `size_t m_growSize;`
- L66 _private member_ `const char* m_name;`
- L67 _private member_ `AllocatorStats m_stats;`
- L70 _private member_ `BlockHeader* m_blockList;` — intrusive linked list

#### struct `PoolAllocator::BlockHeader`  
`struct BlockHeader`  
_L56-59_
- L58 _public member_ `BlockHeader* next;`

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_RelocationPatcher.h` (Private)


#### struct `relocations::Record`  
`struct Record`  
_L18-51_
- L20 _public member_ `coff::Relocation::Type::Enum relocationType;`
- L21 _public member_ `uint16_t patchIndex;`
- L22 _public member_ `uint32_t newModuleRva;`
- L50 _public member_ `} data;`

#### union `relocations::Record::Data`  
`union Data`  
_L24-50_
- L29 _public member_ `} relativeRelocation;`
- L34 _public member_ `} sectionRelativeRelocation;`
- L39 _public member_ `} va32Relocation;`
- L44 _public member_ `} rva32Relocation;`
- L49 _public member_ `} va64Relocation;`

#### struct `relocations::Record::Data::RelativeRelocation`  
`struct RelativeRelocation`  
_L26-29_
- L28 _public member_ `uint32_t originalModuleRva;`

#### struct `relocations::Record::Data::SectionRelativeRelocation`  
`struct SectionRelativeRelocation`  
_L31-34_
- L33 _public member_ `uint32_t sectionRelativeRva;`

#### struct `relocations::Record::Data::VA32Relocation`  
`struct VA32Relocation`  
_L36-39_
- L38 _public member_ `uint32_t originalModuleRva;`

#### struct `relocations::Record::Data::RVA32Relocation`  
`struct RVA32Relocation`  
_L41-44_
- L43 _public member_ `uint32_t originalModuleRva;`

#### struct `relocations::Record::Data::VA64Relocation`  
`struct VA64Relocation`  
_L46-49_
- L48 _public member_ `uint32_t originalModuleRva;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace relocations`
- L53 _prototype_ `bool WouldPatchRelocation(const ImmutableString& dstSymbolName);` (scope `relocations`)
- L55 _prototype_ `bool WouldPatchRelocation ( const coff::Relocation* relocation, const coff::CoffDB* coffDb, const ImmutableString& srcSymbolName, const ModuleCache::FindSymbolData& originalData );` (scope `relocations`)
- L63 _prototype_ `Record PatchRelocation ( const coff::Relocation* relocation, const coff::CoffDB* coffDb, const types::StringSet& forceRelocationSymbols, const ModuleCache* moduleCache, const ImmutableString& srcSymbolName, const ImmutableString& dstSymbolName, const symbols::Symbol* srcSymbol, size_t newModuleIndex, void* newModuleBases[]` (scope `relocations`)
- L79 _prototype_ `void PatchRelocation ( const Record& record, Process::Handle processHandle, void* processModuleBases[], void* newModuleBase );` (scope `relocations`)
- L87 _prototype_ `bool IsValidRecord(const Record& record);` (scope `relocations`)

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_Scheduler.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace scheduler`
- L15 _prototype_ `void Startup(void);` (scope `scheduler`)
- L16 _prototype_ `void Shutdown(void);` (scope `scheduler`)
- L21 _function_ `template <typename F> Task<std::invoke_result_t<F>>* CreateTask(F&& function)` (scope `scheduler`) — BEGIN EPIC MOD creates a new task from any function
- L28 _function_ `template <typename F> Task<std::invoke_result_t<F>>* CreateTask(TaskBase* parent, F&& function)` (scope `scheduler`) — creates a new task from any function as child of a parent task
- L35 _prototype_ `TaskBase* CreateEmptyTask(void);` (scope `scheduler`) — creates an empty task
- L38 _prototype_ `void DestroyTask(TaskBase* task);` (scope `scheduler`) — destroys a task
- L42 _function_ `template <typename T> void DestroyTasks(const T& container)` (scope `scheduler`) — destroys a container of tasks
- L52 _prototype_ `void RunTask(TaskBase* task);` (scope `scheduler`)
- L54 _prototype_ `void WaitForTask(TaskBase* task);` (scope `scheduler`)

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_SchedulerQueue.h` (Private)


#### class `scheduler::TaskQueue`  
`class TaskQueue`  
_L22-48_
- desc: simple multi-producer, multi-consumer queue
- L25 _private member_ `static const unsigned int TASK_COUNT = 4096u;` — BEGIN EPIC MOD - Increasing task count due to hangs when enabling for all editor modules
- L27 _private member_ `static const unsigned int ACCESS_MASK = TASK_COUNT - 1u;` — END EPIC MOD
- L30 _public prototype_ `TaskQueue(void);`
- L33 _public prototype_ `void PushTask(TaskBase* task);` — blocks when there is no more room for a task
- L36 _public prototype_ `TaskBase* PopTask(void);` — blocks when there is no task in the queue
- L39 _public prototype_ `TaskBase* TryPopTask(void);` — does not block
- L42 _private member_ `TaskBase* m_tasks[TASK_COUNT];`
- L43 _private member_ `uint64_t m_readIndex;`
- L44 _private member_ `uint64_t m_writeIndex;`
- L45 _private member_ `Semaphore m_producerSema;`
- L46 _private member_ `Semaphore m_consumerSema;`
- L47 _private member_ `CriticalSection m_cs;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace scheduler`

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_SchedulerTask.h` (Private)


#### class `scheduler::TaskBase`  
`class TaskBase`  
_L19-42_
- L22 _public prototype_ `explicit TaskBase(TaskBase* parent);`
- L23 _public prototype_ `virtual ~TaskBase(void);`
- L25 _public prototype_ `void Execute(void);`
- L26 _public prototype_ `bool IsFinished(void) const;`
- L29 _private prototype_ `virtual void DoExecute(void) = 0;`
- L31 _private prototype_ `void OnChildAttach(void);`
- L32 _private prototype_ `void OnChildDetach(void);`
- L34 _private member_ `TaskBase* const m_parent;`
- L35 _private member_ `unsigned int m_openTasks;`
- L36 _private member_ `mutable CriticalSection m_taskCS;`
- L38 _private prototype_ `LC_DISABLE_COPY(TaskBase);`
- L39 _private prototype_ `LC_DISABLE_ASSIGNMENT(TaskBase);`
- L40 _private prototype_ `LC_DISABLE_MOVE(TaskBase);`
- L41 _private prototype_ `LC_DISABLE_MOVE_ASSIGNMENT(TaskBase);`

#### class `scheduler::Task`  
`template <typename R> class Task : public TaskBase`  
_L46-85_
- inherits: `TaskBase`
- L50 _public function_ `template <typename F> Task(TaskBase* parent, const F& function) : TaskBase(parent) , m_function(function) , m_result()`
- L58 _public function_ `template <typename F> Task(const F& function) : TaskBase(nullptr) , m_function(function) , m_result()`
- L65 _public function_ `virtual ~Task(void)`
- L67 _public function_ `R GetResult(void) const`
- L73 _private function_ `virtual void DoExecute(void) override`
- L78 _private member_ `std::function<R (void)> m_function;`
- L79 _private member_ `R m_result;`
- L81 _private prototype_ `LC_DISABLE_COPY(Task);`
- L82 _private prototype_ `LC_DISABLE_ASSIGNMENT(Task);`
- L83 _private prototype_ `LC_DISABLE_MOVE(Task);`
- L84 _private prototype_ `LC_DISABLE_MOVE_ASSIGNMENT(Task);`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace scheduler`

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_SchedulerWorkerThread.h` (Private)


#### class `scheduler::WorkerThread`  
`class WorkerThread`  
_L18-28_
- L21 _public prototype_ `explicit WorkerThread(TaskQueue* queue);`
- L22 _public prototype_ `~WorkerThread(void);`
- L25 _private prototype_ `Thread::ReturnValue ThreadFunction(TaskQueue* queue);`
- L27 _private member_ `Thread::Handle m_thread;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace scheduler`

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_ServerCommandThread.h` (Private)


#### class `ServerCommandThread`  
`class ServerCommandThread`  
_L30-209_
- L33 _public prototype_ `ServerCommandThread(MainFrame* mainFrame, const wchar_t* const processGroupName, RunMode::Enum runMode);`
- L34 _public prototype_ `~ServerCommandThread(void);`
- L36 _public prototype_ `void RestartTargets(void);`
- L37 _public prototype_ `void CompileChanges(void);`
- L39 _public prototype_ `std::wstring GetProcessImagePath(void) const;`
- L42 _public prototype_ `bool HasReinstancingProcess();` — BEGIN EPIC MOD
- L46 _public prototype_ `bool ShowCompileFinishNotification();` — BEGIN EPIC MOD
- L50 _private prototype_ `scheduler::Task<LiveModule*>* LoadModule(Process::Id processId, void* moduleBase, const wchar_t* modulePath, scheduler::TaskBase* taskRoot);`
- L51 _private prototype_ `bool UnloadModule(Process::Id processId, const wchar_t* modulePath);`
- L53 _private prototype_ `void PrewarmCompilerEnvironmentCache(void);`
- L55 _private prototype_ `Thread::ReturnValue ServerThread(void);`
- L56 _private prototype_ `Thread::ReturnValue CompileThread(void);`
- L59 _private prototype_ `void CallPrecompileHooks(bool didAllProcessesMakeProgress);` — BEGIN EPIC MOD - Add the ability for pre and post compile notifications
- L60 _private prototype_ `void CallPostcompileHooks(bool didAllProcessesMakeProgress, commands::PostCompileResult postCompileResult);`
- L73 _private prototype_ `Thread::ReturnValue CommandThread(DuplexPipeServer* pipe, Event* readyEvent);`
- L74 _private prototype_ `Thread::ReturnValue ExceptionCommandThread(DuplexPipeServer* exceptionPipe);`
- L76 _private prototype_ `void RemoveCommandThread(const DuplexPipe* pipe);`
- L78 _private prototype_ `LiveProcess* FindProcessById(Process::Id processId);`
- L81 _private prototype_ `void CompileChanges(bool didAllProcessesMakeProgress, commands::PostCompileResult& postCompileResult);` — BEGIN EPIC MOD
- L147 _private member_ `std::wstring m_processGroupName;`
- L148 _private member_ `RunMode::Enum m_runMode;`
- L150 _private member_ `MainFrame* m_mainFrame;`
- L151 _private member_ `Thread::Handle m_serverThread;`
- L152 _private member_ `Thread::Handle m_compileThread;`
- L154 _private member_ `types::vector<LiveModule*> m_liveModules;`
- L155 _private member_ `types::vector<LiveProcess*> m_liveProcesses;`
- L156 _private member_ `types::unordered_map<executable::Header, LiveModule*> m_imageHeaderToLiveModule;`
- L158 _private member_ `CriticalSection m_actionCS;`
- L159 _private member_ `CriticalSection m_exceptionCS;`
- L160 _private member_ `Event m_inExceptionHandlerEvent;`
- L161 _private member_ `Event m_handleCommandsEvent;`
- L164 _private member_ `DirectoryCache* m_directoryCache;` — directory cache for all modules combined
- L167 _private member_ `CriticalSection m_connectionCS;` — keeping track of the client connections
- L168 _private member_ `types::vector<CommandThreadContext*> m_commandThreads;`
- L171 _private member_ `std::atomic<unsigned int> m_reinstancingProcessCount = 0;` — BEGIN EPIC MOD
- L175 _private member_ `std::atomic<unsigned int> m_disableCompileFinishNotificationProcessCount = 0;` — BEGIN EPIC MOD
- L179 _private member_ `std::vector<std::pair<std::wstring, std::wstring>> m_restoreFiles;` — BEGIN EPIC MOD - Non-destructive compile
- L183 _private member_ `bool m_active = true;` — BEGIN EPIC MOD - Adding SetActive command
- L187 _private prototype_ `bool EnableRequiredModules(const TArray<FString>& RequiredModules);` — BEGIN EPIC MOD - Lazy loading modules
- L191 _private member_ `bool m_manualRecompileTriggered;` — for triggering recompiles using the API
- L192 _private member_ `types::unordered_map<std::wstring, types::vector<symbols::ModifiedObjFile>> m_liveModuleToModifiedOrNewObjFiles;`
- L195 _private member_ `types::unordered_map<std::wstring, types::vector<std::wstring>> m_liveModuleToAdditionalLibraries;` — BEGIN EPIC MOD
- L199 _private member_ `CriticalSection m_restartCS;` — restart mechanism
- L200 _private member_ `void* m_restartJob;`
- L201 _private member_ `unsigned int m_restartedProcessCount;`
- L205 _private member_ `types::unordered_map<unsigned int, EnvDTE::DebuggerPtr> m_restartedProcessIdToDebugger;` — END EPIC MOD

#### struct `ServerCommandThread::CommandThreadContext`  
`struct CommandThreadContext`  
_L63-71_
- L65 _public member_ `DuplexPipeServer pipe;`
- L66 _public member_ `Event* readyEvent;`
- L67 _public member_ `Thread::Handle commandThread;`
- L69 _public member_ `DuplexPipeServer exceptionPipe;`
- L70 _public member_ `Thread::Handle exceptionCommandThread;`

#### struct `ServerCommandThread::actions`  
`struct actions`  
_L85-144_
- desc: actions
- L94 _public prototype_ `DECLARE_ACTION(TriggerRecompile);`
- L95 _public prototype_ `DECLARE_ACTION(TriggerRestart);`
- L96 _public prototype_ `DECLARE_ACTION(LogMessage);`
- L97 _public prototype_ `DECLARE_ACTION(BuildPatch);`
- L98 _public prototype_ `DECLARE_ACTION(HandleException);`
- L99 _public prototype_ `DECLARE_ACTION(ReadyForCompilation);`
- L100 _public prototype_ `DECLARE_ACTION(DisconnectClient);`
- L101 _public prototype_ `DECLARE_ACTION(RegisterProcess);`
- L103 _public prototype_ `DECLARE_ACTION(EnableModules);`
- L104 _public prototype_ `DECLARE_ACTION(DisableModules);`
- L106 _public prototype_ `DECLARE_ACTION(ApplySettingBool);`
- L107 _public prototype_ `DECLARE_ACTION(ApplySettingInt);`
- L108 _public prototype_ `DECLARE_ACTION(ApplySettingString);`
- L111 _public prototype_ `DECLARE_ACTION(ShowConsole);` — BEGIN EPIC MOD - Adding ShowConsole command
- L115 _public prototype_ `DECLARE_ACTION(SetVisible);` — BEGIN EPIC MOD - Adding ShowConsole command
- L119 _public prototype_ `DECLARE_ACTION(SetActive);` — BEGIN EPIC MOD - Adding SetActive command
- L123 _public prototype_ `DECLARE_ACTION(SetBuildArguments);` — BEGIN EPIC MOD - Adding SetBuildArguments command
- L127 _public prototype_ `DECLARE_ACTION(EnableLazyLoadedModule);` — BEGIN EPIC MOD - Adding support for lazy-loading modules
- L128 _public prototype_ `DECLARE_ACTION(FinishedLazyLoadingModules);`
- L132 _public prototype_ `DECLARE_ACTION(SetReinstancingFlow);` — BEGIN EPIC MOD
- L136 _public prototype_ `DECLARE_ACTION(DisableCompileFinishNotification);` — BEGIN EPIC MOD
- L140 _public prototype_ `DECLARE_ACTION(EnableModulesEx);` — BEGIN EPIC MOD

#### Free symbols / members of external scopes

- L87 _macro_ `#define DECLARE_ACTION(_name) \`

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_Settings.h` (Private)


#### class `Setting`  
`class Setting`  
_L21-44_
- desc: base
- L36 _public prototype_ `explicit Setting(Type::Enum type);`
- L37 _public prototype_ `LC_DISABLE_COPY(Setting);`
- L38 _public prototype_ `LC_DISABLE_ASSIGNMENT(Setting);`
- L40 _public prototype_ `Type::Enum GetType(void) const;`
- L43 _private member_ `const Type::Enum m_type;`

#### struct `Setting::Type`  
`struct Type`  
_L24-34_

#### enum `Setting::Type::Enum`  
`enum Enum`  
_L26-33_
- L28 _public enumerator_ `BOOLEAN`
- L29 _public enumerator_ `INTEGER`
- L30 _public enumerator_ `INTEGER_PROXY`
- L31 _public enumerator_ `STRING`
- L32 _public enumerator_ `SHORTCUT`

#### class `SettingBool`  
`class SettingBool : public Setting`  
_L48-73_
- inherits: `Setting`
- desc: real settings
- L51 _public prototype_ `SettingBool(const wchar_t* group, const wchar_t* name, const wchar_t* shortDescription, const wchar_t* description, bool initialValue);`
- L52 _public prototype_ `LC_DISABLE_COPY(SettingBool);`
- L53 _public prototype_ `LC_DISABLE_ASSIGNMENT(SettingBool);`
- L55 _public prototype_ `void SetValue(bool value);`
- L56 _public prototype_ `void SetValueWithoutSaving(bool value);`
- L58 _public prototype_ `const wchar_t* GetName(void) const;`
- L59 _public prototype_ `const wchar_t* GetShortDescription(void) const;`
- L60 _public prototype_ `const wchar_t* GetDescription(void) const;`
- L61 _public prototype_ `bool GetValue(void) const;`
- L62 _public prototype_ `bool GetPreviousValue(void) const;`
- L63 _public prototype_ `bool GetInitialValue(void) const;`
- L66 _private member_ `const wchar_t* m_group;`
- L67 _private member_ `const wchar_t* m_name;`
- L68 _private member_ `const wchar_t* m_shortDescription;`
- L69 _private member_ `const wchar_t* m_description;`
- L70 _private member_ `bool m_value;`
- L71 _private member_ `bool m_previousValue;`
- L72 _private member_ `bool m_initialValue;`

#### class `SettingInt`  
`class SettingInt : public Setting`  
_L76-101_
- inherits: `Setting`
- L79 _public prototype_ `SettingInt(const wchar_t* group, const wchar_t* name, const wchar_t* shortDescription, const wchar_t* description, int initialValue);`
- L80 _public prototype_ `LC_DISABLE_COPY(SettingInt);`
- L81 _public prototype_ `LC_DISABLE_ASSIGNMENT(SettingInt);`
- L83 _public prototype_ `void SetValue(int value);`
- L84 _public prototype_ `void SetValueWithoutSaving(int value);`
- L86 _public prototype_ `const wchar_t* GetName(void) const;`
- L87 _public prototype_ `const wchar_t* GetShortDescription(void) const;`
- L88 _public prototype_ `const wchar_t* GetDescription(void) const;`
- L89 _public prototype_ `int GetValue(void) const;`
- L90 _public prototype_ `int GetPreviousValue(void) const;`
- L91 _public prototype_ `int GetInitialValue(void) const;`
- L94 _private member_ `const wchar_t* m_group;`
- L95 _private member_ `const wchar_t* m_name;`
- L96 _private member_ `const wchar_t* m_shortDescription;`
- L97 _private member_ `const wchar_t* m_description;`
- L98 _private member_ `int m_value;`
- L99 _private member_ `int m_previousValue;`
- L100 _private member_ `int m_initialValue;`

#### class `SettingString`  
`class SettingString : public Setting`  
_L104-127_
- inherits: `Setting`
- L107 _public prototype_ `SettingString(const wchar_t* group, const wchar_t* name, const wchar_t* shortDescription, const wchar_t* description, const wchar_t* initialValue);`
- L108 _public prototype_ `LC_DISABLE_COPY(SettingString);`
- L109 _public prototype_ `LC_DISABLE_ASSIGNMENT(SettingString);`
- L111 _public prototype_ `void SetValue(const wchar_t* value);`
- L112 _public prototype_ `void SetValueWithoutSaving(const wchar_t* value);`
- L114 _public prototype_ `const wchar_t* GetName(void) const;`
- L115 _public prototype_ `const wchar_t* GetShortDescription(void) const;`
- L116 _public prototype_ `const wchar_t* GetDescription(void) const;`
- L117 _public prototype_ `const wchar_t* GetValue(void) const;`
- L118 _public prototype_ `const wchar_t* GetPreviousValue(void) const;`
- L121 _private member_ `const wchar_t* m_group;`
- L122 _private member_ `const wchar_t* m_name;`
- L123 _private member_ `const wchar_t* m_shortDescription;`
- L124 _private member_ `const wchar_t* m_description;`
- L125 _private member_ `std::wstring m_value;`
- L126 _private member_ `std::wstring m_previousValue;`

#### class `SettingIntProxy`  
`class SettingIntProxy : public Setting`  
_L131-157_
- inherits: `Setting`
- desc: proxy settings
- L140 _public prototype_ `explicit SettingIntProxy(SettingInt* setting);`
- L141 _public prototype_ `LC_DISABLE_COPY(SettingIntProxy);`
- L142 _public prototype_ `LC_DISABLE_ASSIGNMENT(SettingIntProxy);`
- L144 _public prototype_ `SettingIntProxy& AddMapping(const wchar_t* str, int value);`
- L145 _public prototype_ `const wchar_t* MapIntToString(int value) const;`
- L146 _public prototype_ `int MapStringToInt(const wchar_t* str) const;`
- L148 _public prototype_ `SettingInt* GetSetting(void);`
- L150 _public prototype_ `size_t GetMappingCount(void) const;`
- L151 _public prototype_ `const wchar_t* GetMappingString(size_t index) const;`
- L152 _public prototype_ `int GetMappingInt(size_t index) const;`
- L155 _private member_ `SettingInt* m_setting;`
- L156 _private member_ `types::vector<Mapping> m_mappings;`

#### struct `SettingIntProxy::Mapping`  
`struct Mapping`  
_L133-137_
- L135 _public member_ `std::wstring str;`
- L136 _public member_ `int value;`

#### class `SettingShortcut`  
`class SettingShortcut : public Setting`  
_L160-181_
- inherits: `Setting`
- L163 _public prototype_ `SettingShortcut(const wchar_t* group, const wchar_t* name, const wchar_t* shortDescription, const wchar_t* description, int initialValue);`
- L164 _public prototype_ `LC_DISABLE_COPY(SettingShortcut);`
- L165 _public prototype_ `LC_DISABLE_ASSIGNMENT(SettingShortcut);`
- L167 _public prototype_ `void SetValue(int value);`
- L168 _public prototype_ `void SetValueWithoutSaving(int value);`
- L170 _public prototype_ `const wchar_t* GetName(void) const;`
- L171 _public prototype_ `const wchar_t* GetShortDescription(void) const;`
- L172 _public prototype_ `const wchar_t* GetDescription(void) const;`
- L173 _public prototype_ `int GetValue(void) const;`
- L176 _private member_ `const wchar_t* m_group;`
- L177 _private member_ `const wchar_t* m_name;`
- L178 _private member_ `const wchar_t* m_shortDescription;`
- L179 _private member_ `const wchar_t* m_description;`
- L180 _private member_ `int m_value;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace settings`
- L15 _prototype_ `unsigned int GetLoadedUserSettingsCount(void);` (scope `settings`)
- L16 _prototype_ `unsigned int GetLoadedProjectSettingsCount(void);` (scope `settings`)

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_SymbolInfo.h` (Private)


#### class `SymbolInfo`  
`class SymbolInfo`  
_L13-41_
- L16 _public prototype_ `SymbolInfo(const char* const function, const char* const filename, unsigned int line);`
- L18 _public function_ `inline const char* GetFunction(void) const`
- L23 _public function_ `inline const char* GetFilename(void) const`
- L28 _public function_ `inline unsigned int GetLine(void) const`
- L34 _private prototype_ `LC_DISABLE_ASSIGNMENT(SymbolInfo);`
- L36 _private member_ `char m_function[512u];`
- L38 _private member_ `char m_filename[WINDOWS_MAX_PATH];` — BEGIN EPIC MOD
- L40 _private member_ `unsigned int m_line;` — END EPIC MOD

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_SymbolPatterns.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace symbolPatterns`
- L14 _externvar_ `extern const char* const PCH_SYMBOL_PATTERNS[1];` (scope `symbolPatterns`)
- L16 _externvar_ `extern const char* const VTABLE_PATTERNS[3];` (scope `symbolPatterns`)
- L17 _externvar_ `extern const char* const RTTI_OBJECT_LOCATOR_PATTERNS[1];` (scope `symbolPatterns`)
- L18 _externvar_ `extern const char* const DYNAMIC_INITIALIZER_PATTERNS[1];` (scope `symbolPatterns`)
- L19 _externvar_ `extern const char* const DYNAMIC_ATEXIT_DESTRUCTORS[1];` (scope `symbolPatterns`)
- L20 _externvar_ `extern const char* const POINTER_TO_DYNAMIC_INITIALIZER_PATTERNS[1];` (scope `symbolPatterns`)
- L21 _externvar_ `extern const char* const STRING_LITERAL_PATTERNS[2];` (scope `symbolPatterns`)
- L22 _externvar_ `extern const char* const LINE_NUMBER_PATTERNS[1];` (scope `symbolPatterns`)
- L23 _externvar_ `extern const char* const FLOATING_POINT_CONSTANT_PATTERNS[4];` (scope `symbolPatterns`)
- L26 _externvar_ `extern const char* const EXCEPTION_RELATED_PATTERNS[17];` (scope `symbolPatterns`)
- L28 _externvar_ `extern const char* const EXCEPTION_RELATED_PATTERNS[11];` (scope `symbolPatterns`)
- L30 _externvar_ `extern const char* const EXCEPTION_UNWIND_PATTERNS[1];` (scope `symbolPatterns`)
- L32 _externvar_ `extern const char* const EXCEPTION_CLAUSE_PATTERNS[2];` (scope `symbolPatterns`)
- L34 _externvar_ `extern const char* const RTC_PATTERNS[8];` (scope `symbolPatterns`)
- L35 _externvar_ `extern const char* const SDL_CHECK_PATTERNS[2];` (scope `symbolPatterns`)
- L36 _externvar_ `extern const char* const CFG_PATTERNS[1];` (scope `symbolPatterns`)
- L38 _externvar_ `extern const char* const IMAGE_BASE_PATTERNS[1];` (scope `symbolPatterns`)
- L40 _externvar_ `extern const char* const TLS_ARRAY_PATTERNS[1];` (scope `symbolPatterns`)
- L41 _externvar_ `extern const char* const TLS_INDEX_PATTERNS[1];` (scope `symbolPatterns`)
- L42 _externvar_ `extern const char* const TLS_INIT_PATTERNS[3];` (scope `symbolPatterns`)
- L43 _externvar_ `extern const char* const TLS_STATICS_PATTERNS[1];` (scope `symbolPatterns`)
- L45 _externvar_ `extern const char* const ANONYMOUS_NAMESPACE_PATTERN;` (scope `symbolPatterns`)
- L48 _externvar_ `extern const char* const UE_STATICS_BLOCK_PATTERNS[7];` (scope `symbolPatterns`) — BEGIN EPIC MOD
- L49 _externvar_ `extern const char* const UE_REGISTER_PATTERNS[6];` (scope `symbolPatterns`)

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_SymbolReconstruction.h` (Private)


#### Free symbols / members of external scopes

- L15 _namespace_ `namespace symbols`
- L17 _prototype_ `void ReconstructFromExecutableCoff ( const symbols::Provider* provider, const executable::Image* image, const executable::ImageSectionDB* imageSections, const coff::CoffDB* coffDb, const types::StringSet& strippedSymbols, const symbols::ObjPath& objPath, const symbols::ContributionDB* contributionDb, const symbols::ThunkDB* thunkDb, const symbols::ImageSectionDB* imageSectionDb, symbols::SymbolDB* symbolDB );` (scope `symbols`)

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_SymbolResolution.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace symbolResolution`
- L13 _prototype_ `SymbolInfo ResolveSymbolsForAddress(const void* const address);` (scope `symbolResolution`) — Resolves the symbol information for a given address

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_Symbols.h` (Private)


#### struct `symbols::Symbol`  
`struct Symbol`  
_L30-41_
- L32 _public member_ `ImmutableString name;`
- L33 _public member_ `uint32_t rva;`
- L36 _public function_ `Symbol(ImmutableString _name, uint32_t _rva) : name(_name), rva(_rva)` — BEGIN EPIC MOD
- L39 _public prototype_ `LC_DISABLE_ASSIGNMENT(Symbol);`
- L40 _public prototype_ `LC_DISABLE_COPY(Symbol);`

#### struct `symbols::SymbolDB`  
`struct SymbolDB`  
_L43-57_
- L46 _public member_ `types::StringMap<Symbol*> symbolsByName;` — symbols accessibly by name or RVA
- L47 _public member_ `types::unordered_map<uint32_t, Symbol*> symbolsByRva;`
- L50 _public member_ `types::StringSet symbolsWithoutRva;` — a set of symbols that need to be ignored upon reconstruction
- L53 _public member_ `types::vector<Symbol*> patchableFunctionSymbols;` — public function symbols that can be patched
- L56 _public member_ `types::vector<Symbol*> ansSymbols;` — symbols that contain an anonymous namespace in their mangled name

#### struct `symbols::Contribution`  
`struct Contribution`  
_L59-65_
- L62 _public member_ `uint32_t compilandNameIndex;` — index of the name of the compiland (.obj file) that contributed this
- L63 _public member_ `uint32_t rva;`
- L64 _public member_ `uint32_t size;`

#### struct `symbols::ContributionDB`  
`struct ContributionDB`  
_L67-89_
- L72 _public member_ `types::vector<ImmutableString> originalStringTable;` — string table that stores the name of a compiland (.obj file). indexed by a contribution's compiland name index. this is loaded initially when gathering contributions.
- L77 _public member_ `types::vector<ImmutableString> objOnDiskStringTable;` — string table that stores the name of an .obj file on disk. indexed by a contribution's compiland name index. this is filled after both contributions and compilands have been loaded.
- L80 _public member_ `types::vector<Contribution*> contributions;` — stores all contributions gathered from a .PDB file, ordered by ascending RVA
- L84 _public typedef_ `typedef types::vector<Contribution*> ContributionsPerCompiland;` — array of all contributions per compiland name index, each ordered by ascending RVA. indexed by a contribution's compiland name index.
- L85 _public member_ `types::vector<ContributionsPerCompiland> contributionsPerCompilandNameIndex;`
- L88 _public member_ `types::StringMap<uint32_t> compilandNameToCompilandNameIndex;` — lookup-table from compiland name to corresponding compiland name index

#### struct `symbols::CompilandSourceFiles`  
`struct CompilandSourceFiles`  
_L91-95_
- L94 _public member_ `types::vector<ImmutableString> files;` — source files used by compilands

#### struct `symbols::Compiland`  
`struct Compiland`  
_L97-131_
- L109 _public member_ `ImmutableString originalObjPath;` — full path to the original, non-normalized .obj file
- L110 _public member_ `ImmutableString srcPath;` — full path to source file
- L111 _public member_ `ImmutableString pdbPath;` — full path to .pdb file
- L112 _public member_ `ImmutableString compilerPath;` — full path to compiler used to compile the compiland
- L113 _public member_ `ImmutableString commandLine;` — command line arguments passed to the compiler
- L114 _public member_ `ImmutableString workingDirectory;` — full path to working directory
- L115 _public member_ `ImmutableString amalgamationPath;` — full path to the amalgamation .obj in case this is part of an amalgamation
- L116 _public member_ `CompilandSourceFiles* sourceFiles;`
- L117 _public member_ `uint32_t uniqueId;`
- L118 _public member_ `Type::Enum type;`
- L119 _public member_ `bool isPartOfLibrary;`
- L120 _public member_ `bool wasRecompiled;`
- L123 _public function_ `Compiland(ImmutableString _originalObjPath, ImmutableString _srcPath, ImmutableString _pdbPath, ImmutableString _compilerPath, ImmutableString _commandLine, ImmutableString _workingDirectory, ImmutableString _amalgamationPath, CompilandSourceFiles* _sourceFiles, uint32_t _uniqueId, Type::Enum _type, bool _isPartOfLibrary, bool _wasRecompiled) : originalObjPath(_originalObjPath), srcPath(_srcPath), pdbPath(_pdbPath), compilerPath(_compilerPath), commandLine(_commandLine), workingDirectory(_workingDirectory), amalgamationPath(_amalgamationPath), sourceFiles(_sourceFiles), uniqueId(_uniqueId), type(_type), isPartOfLibrary(_isPartOfLibrary), wasRecompiled(_wasRecompiled)` — BEGIN EPIC MOD
- L129 _public prototype_ `LC_DISABLE_ASSIGNMENT(Compiland);`
- L130 _public prototype_ `LC_DISABLE_COPY(Compiland);`

#### struct `symbols::Compiland::Type`  
`struct Type`  
_L99-107_

#### enum `symbols::Compiland::Type::Enum`  
`enum Enum : uint8_t`  
_L101-106_
- L103 _public enumerator_ `SINGLE_FILE`
- L104 _public enumerator_ `AMALGAMATION`
- L105 _public enumerator_ `PART_OF_AMALGAMATION`

#### struct `symbols::AmalgamatedCompiland`  
`struct AmalgamatedCompiland`  
_L133-137_
- L135 _public member_ `types::vector<ImmutableString> singleParts;` — .obj of the single files that make up an amalgamation
- L136 _public member_ `bool isSplit;`

#### struct `symbols::ModifiedObjFile`  
`struct ModifiedObjFile`  
_L139-143_
- L141 _public member_ `std::wstring objPath;`
- L142 _public member_ `std::wstring amalgamatedObjPath;` — optional

#### struct `symbols::Dependency`  
`struct Dependency`  
_L154-160_
- L156 _public member_ `DirectoryCache::Directory* parentDirectory;`
- L157 _public member_ `TimeStamp lastModification;`
- L158 _public member_ `types::vector<ObjPath> objPaths;`
- L159 _public member_ `bool hadInitialChange;`

#### struct `symbols::CompilandDB`  
`struct CompilandDB`  
_L162-177_
- L165 _public member_ `types::StringMap<Compiland*> compilands;` — stores a compiland for each .obj file that contributed to a module and has its source available
- L168 _public member_ `types::StringMap<AmalgamatedCompiland*> amalgamatedCompilands;` — stores an array of .obj files which are part of amalgamated compilands
- L171 _public member_ `types::StringMap<Dependency*> dependencies;` — stores an array of .obj files that need to be recompiled when a certain file changes
- L176 _public member_ `types::StringMap<ImmutableString> compilandNameToObjOnDisk;` — stores the real name of the .obj on disk for each original DIA compiland name. this lookup table is needed because DIA compilands coming from static libraries often don't contain the full path, but a path that is relative to the project instead, e.g. obj\x64\Debug\SimpleFunction.obj

#### struct `symbols::DiaCompilandDB`  
`struct DiaCompilandDB`  
_L179-182_
- L181 _public member_ `types::vector<IDiaSymbol*> symbols;`

#### struct `symbols::ModuleDB`  
`struct ModuleDB`  
_L184-187_
- L186 _public member_ `types::vector<std::wstring> modules;` — relative path to .exe or .dll

#### struct `symbols::LibraryDB`  
`struct LibraryDB`  
_L189-193_
- L192 _public member_ `types::vector<FilePath> libraries;` — full path to all .lib files that need to be used for linking

#### struct `symbols::LinkerDB`  
`struct LinkerDB`  
_L195-203_
- L197 _public member_ `ImmutableString pdbPath;` — full path to .pdb file
- L198 _public member_ `ImmutableString linkerPath;` — full path to linker used to link the executable
- L199 _public member_ `ImmutableString commandLine;` — command line arguments passed to the linker (emitted by VS2015 and later)
- L200 _public member_ `ImmutableString workingDirectory;` — full path to working directory
- L202 _public prototype_ `LC_DISABLE_ASSIGNMENT(LinkerDB);`

#### struct `symbols::ThunkDB`  
`struct ThunkDB`  
_L205-213_
- L208 _public member_ `types::unordered_map<uint32_t, uint32_t> thunksFromTableEntryToTarget;` — stores thunks from table entry RVA to target RVA.
- L212 _public member_ `types::unordered_map<uint32_t, types::vector<uint32_t>> thunksFromTargetToTableEntries;` — stores thunks from target RVA to table entry RVA there can be several different thunks referring to the same RVA!

#### struct `symbols::ImageSection`  
`struct ImageSection`  
_L215-220_
- L217 _public member_ `uint32_t nameIndex;`
- L218 _public member_ `uint32_t rva;`
- L219 _public member_ `uint32_t size;`

#### struct `symbols::ImageSectionDB`  
`struct ImageSectionDB`  
_L222-227_
- L224 _public member_ `types::vector<ImmutableString> sectionNames;`
- L225 _public member_ `types::vector<ImageSection> sections;` — sorted by RVA
- L226 _public member_ `types::StringMap<ImageSection> sectionsByName;`

#### struct `symbols::Provider`  
`struct Provider`  
_L229-235_
- L231 _public member_ `IDiaDataSource* diaDataSource;`
- L232 _public member_ `IDiaSession* diaSession;`
- L233 _public member_ `IDiaSymbol* globalScope;`
- L234 _public member_ `TimeStamp lastModificationTime;`

#### struct `symbols::DynamicInitializerDB`  
`struct DynamicInitializerDB`  
_L237-241_
- L240 _public member_ `types::vector<const Symbol*> dynamicInitializers;` — no symbol ownership

#### struct `symbols::UserDefinedTypesDB`  
`struct UserDefinedTypesDB`  
_L243-246_
- L245 _public member_ `types::unordered_set<uint32_t> typeIds;`

#### struct `symbols::OpenOptions`  
`struct OpenOptions`  
_L250-258_
- desc: LIFETIME

#### enum `symbols::OpenOptions::Enum`  
`enum Enum : uint32_t`  
_L252-257_
- L254 _public enumerator_ `NONE = 0u`
- L255 _public enumerator_ `ACCUMULATE_SIZE = 1u << 0u`
- L256 _public enumerator_ `USE_SYMBOL_SERVER = 1u << 1u`

#### struct `symbols::CompilandOptions`  
`struct CompilandOptions`  
_L291-300_

#### enum `symbols::CompilandOptions::Enum`  
`enum Enum : uint32_t`  
_L293-299_
- L295 _public enumerator_ `NONE = 0u`
- L296 _public enumerator_ `GENERATE_LOGS = 1u << 0u`
- L297 _public enumerator_ `FORCE_PCH_PDBS = 1u << 1u`
- L298 _public enumerator_ `TRACK_OBJ_ONLY = 1u << 2u`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace coff`
- L28 _namespace_ `namespace symbols`
- L147 _typedef_ `typedef ImmutableString ObjPath;` (scope `symbols`) — full path to .obj file
- L150 _typedef_ `typedef ImmutableString FilePath;` (scope `symbols`) — full path to any file
- L152 _typedef_ `typedef uint64_t TimeStamp;` (scope `symbols`)
- L262 _prototype_ `Symbol* CreateNewSymbol(const ImmutableString& name, uint32_t rva, SymbolDB* db);` (scope `symbols`) — TODO: helper function to make fixing and refactoring easier for now
- L265 _prototype_ `Provider* OpenEXE(const wchar_t* filename, uint32_t openOptions);` (scope `symbols`)
- L266 _prototype_ `void Close(Provider* provider);` (scope `symbols`)
- L269 _prototype_ `void ResetCachedUnityManifests();` (scope `symbols`) — BEGIN EPIC MOD - Static grouping of compilands by unity blobs
- L270 _prototype_ `bool TryGetCompilandIdFromUnityManifest(const std::wstring& objPath, uint32_t& compilandId);` (scope `symbols`)
- L271 _prototype_ `uint32_t GetCompilandIdFromPath(const std::wstring& objPath);` (scope `symbols`)
- L278 _prototype_ `SymbolDB* GatherSymbols(Provider* provider);` (scope `symbols`) — CACHE: must be kept per module
- L281 _prototype_ `ContributionDB* GatherContributions(Provider* provider);` (scope `symbols`) — CACHE: must be kept per module
- L285 _prototype_ `void FinalizeContributions(const CompilandDB* compilandDb, ContributionDB* db);` (scope `symbols`) — converts the string table of .obj files to a string table of real .obj files on disk, and builds a per-compiland array of contributions.
- L288 _prototype_ `DiaCompilandDB* GatherDiaCompilands(Provider* provider);` (scope `symbols`) — CACHE: temporary, throw away after use
- L303 _prototype_ `CompilandDB* GatherCompilands(const Provider* provider, const DiaCompilandDB* diaCompilandDb, unsigned int splitAmalgamatedFilesThreshold, uint32_t compilandOptions);` (scope `symbols`) — CACHE: stored only ONCE, after initial load, cannot change
- L306 _prototype_ `LibraryDB* GatherLibraries(const DiaCompilandDB* diaCompilandDb);` (scope `symbols`) — CACHE: stored only ONCE, after initial load, cannot change
- L310 _prototype_ `IDiaSymbol* FindLinkerSymbol(const DiaCompilandDB* diaCompilandDb);` (scope `symbols`) — CACHE: temporary, throw away after use
- L313 _prototype_ `LinkerDB* GatherLinker(IDiaSymbol* linkerSymbol);` (scope `symbols`) — CACHE: stored only ONCE, after initial load, cannot change
- L316 _prototype_ `ThunkDB* GatherThunks(IDiaSymbol* linkerSymbol);` (scope `symbols`) — CACHE: must be kept per module
- L319 _prototype_ `ImageSectionDB* GatherImageSections(IDiaSymbol* linkerSymbol);` (scope `symbols`) — CACHE: must be kept per module
- L322 _prototype_ `DynamicInitializerDB GatherDynamicInitializers(const Provider* provider, const executable::Image* image, const executable::ImageSectionDB* imageSections, const ImageSectionDB* imageSectionDb, const ContributionDB* contributionDb, const CompilandDB* compilandDb, const CoffCache<coff::CoffDB>* coffCache, SymbolDB* symbolDb);` (scope `symbols`) — CACHE: must be kept per module, stores symbols directly into the given symbol database
- L326 _prototype_ `void DestroyLinkerSymbol(IDiaSymbol* symbol);` (scope `symbols`)
- L328 _prototype_ `void DestroyDiaCompilandDB(DiaCompilandDB* db);` (scope `symbols`)
- L329 _prototype_ `void DestroyModuleDB(ModuleDB* db);` (scope `symbols`)
- L331 _prototype_ `void DestroyCompilandDB(CompilandDB* db);` (scope `symbols`)
- L333 _prototype_ `void MergeCompilandsAndDependencies(CompilandDB* existingDb, CompilandDB* mergedDb);` (scope `symbols`)
- L337 _prototype_ `void MarkCompilandAsRecompiled(Compiland* compiland);` (scope `symbols`)
- L338 _prototype_ `void ClearCompilandAsRecompiled(Compiland* compiland);` (scope `symbols`)
- L340 _prototype_ `bool IsCompilandRecompiled(const Compiland* compiland);` (scope `symbols`)
- L344 _prototype_ `Compiland* FindCompiland(CompilandDB* db, const ObjPath& objPath);` (scope `symbols`) — ACCESS
- L345 _prototype_ `const Compiland* FindCompiland(const CompilandDB* db, const ObjPath& objPath);` (scope `symbols`)
- L346 _prototype_ `AmalgamatedCompiland* FindAmalgamatedCompiland(CompilandDB* db, const ObjPath& objPath);` (scope `symbols`)
- L347 _prototype_ `const AmalgamatedCompiland* FindAmalgamatedCompiland(const CompilandDB* db, const ObjPath& objPath);` (scope `symbols`)
- L349 _prototype_ `bool IsAmalgamation(const Compiland* compiland);` (scope `symbols`)
- L350 _prototype_ `bool IsPartOfAmalgamation(const Compiland* compiland);` (scope `symbols`)
- L353 _prototype_ `const Symbol* FindSymbolByName(const SymbolDB* db, const ImmutableString& name);` (scope `symbols`) — finds a symbol by name. must match exactly
- L354 _prototype_ `const Symbol* FindSymbolByRVA(const SymbolDB* db, uint32_t rva);` (scope `symbols`)
- L357 _prototype_ `const ImageSection* FindImageSectionByName(const ImageSectionDB* db, const ImmutableString& name);` (scope `symbols`) — finds a section by name. must match exactly
- L360 _prototype_ `const ImageSection* FindImageSectionByRVA(const ImageSectionDB* db, uint32_t rva);` (scope `symbols`) — finds a section by RVA, binary search. RVA need not be exact, only must lie inside any of the sections
- L363 _prototype_ `uint32_t FindThunkTargetByRVA(const ThunkDB* db, uint32_t tableEntryRva);` (scope `symbols`) — finds a thunk using the table entry RVA, returns the target RVA
- L366 _prototype_ `types::vector<uint32_t> FindThunkTableEntriesByRVA(const ThunkDB* db, uint32_t targetRva);` (scope `symbols`) — finds thunks using the target RVA, returns all thunks that point to the target RVA
- L370 _prototype_ `std::string UndecorateSymbolName(const ImmutableString& symbolName);` (scope `symbols`) — takes into account that symbol names might contain COFF suffixes
- L374 _prototype_ `const Contribution* FindContributionByRVA(const ContributionDB* db, uint32_t rva);` (scope `symbols`) — finds a contribution by RVA, binary search. RVA need not be exact, only must lie inside any of the contributions
- L377 _prototype_ `ImmutableString GetContributionCompilandName(const ContributionDB* db, const Contribution* contribution);` (scope `symbols`) — returns the compiland name of a given contribution
- L380 _prototype_ `const ContributionDB::ContributionsPerCompiland* GetContributionsForCompilandName(const ContributionDB* db, const ImmutableString& compilandName);` (scope `symbols`) — returns all contributions for a certain compiland name
- L383 _prototype_ `const ContributionDB::ContributionsPerCompiland* GetContributionsForCompilandNameIndex(const ContributionDB* db, uint32_t compilandNameIndex);` (scope `symbols`) — returns all contributions for a certain compiland name index
- L385 _prototype_ `const ImmutableString& GetImageSectionName(const ImageSectionDB* db, const ImageSection* imageSection);` (scope `symbols`)
- L392 _prototype_ `uint32_t GetCompilandId(const Compiland* compiland, const wchar_t* const objPath, const types::vector<ModifiedObjFile>& modifiedObjFiles);` (scope `symbols`) — helper function that returns or generates the unique ID of an optional compiland. for files split off from amalgamated files, we need to use the original object path of the amalgamated file here, otherwise names of symbols would differ, leading to constructors of global instances being called again.
- L394 _prototype_ `ImmutableString TransformAnonymousNamespacePattern(const ImmutableString& immutableString, uint32_t uniqueId);` (scope `symbols`)
- L396 _prototype_ `void TransformAnonymousNamespaceSymbols(SymbolDB* symbolDb, ContributionDB* contributionDb, CompilandDB* compilandDb, const types::vector<ModifiedObjFile>& modifiedObjFiles);` (scope `symbols`)
- L399 _prototype_ `bool IsPchSymbol(const ImmutableString& symbolName);` (scope `symbols`)
- L401 _prototype_ `bool IsVTable(const ImmutableString& symbolName);` (scope `symbols`)
- L402 _prototype_ `bool IsRttiObjectLocator(const ImmutableString& symbolName);` (scope `symbols`)
- L404 _prototype_ `bool IsDynamicInitializer(const ImmutableString& functionSymbolName);` (scope `symbols`)
- L405 _prototype_ `bool IsDynamicAtexitDestructor(const ImmutableString& functionSymbolName);` (scope `symbols`)
- L406 _prototype_ `bool IsPointerToDynamicInitializer(const ImmutableString& symbolName);` (scope `symbols`)
- L408 _prototype_ `bool IsStringLiteral(const ImmutableString& symbolName);` (scope `symbols`)
- L409 _prototype_ `bool IsLineNumber(const ImmutableString& symbolName);` (scope `symbols`)
- L411 _prototype_ `bool IsFloatingPointSseAvxConstant(const ImmutableString& symbolName);` (scope `symbols`)
- L413 _prototype_ `bool IsExceptionRelatedSymbol(const ImmutableString& symbolName);` (scope `symbols`)
- L414 _prototype_ `bool IsExceptionClauseSymbol(const ImmutableString& symbolName);` (scope `symbols`)
- L415 _prototype_ `bool IsExceptionUnwindSymbolForDynamicInitializer(const ImmutableString& symbolName);` (scope `symbols`)
- L417 _prototype_ `bool IsRuntimeCheckRelatedSymbol(const ImmutableString& symbolName);` (scope `symbols`)
- L418 _prototype_ `bool IsSdlCheckRelatedSymbol(const ImmutableString& symbolName);` (scope `symbols`)
- L419 _prototype_ `bool IsControlFlowGuardRelatedSymbol(const ImmutableString& symbolName);` (scope `symbols`)
- L421 _prototype_ `bool IsImageBaseRelatedSymbol(const ImmutableString& symbolName);` (scope `symbols`)
- L422 _prototype_ `bool IsTlsArrayRelatedSymbol(const ImmutableString& symbolName);` (scope `symbols`)
- L423 _prototype_ `bool IsTlsIndexRelatedSymbol(const ImmutableString& symbolName);` (scope `symbols`)
- L424 _prototype_ `bool IsTlsInitRelatedSymbol(const ImmutableString& symbolName);` (scope `symbols`)
- L425 _prototype_ `bool IsTlsStaticsRelatedSymbol(const ImmutableString& symbolName);` (scope `symbols`)
- L427 _prototype_ `bool IsSectionSymbol(const ImmutableString& symbolName);` (scope `symbols`)
- L430 _prototype_ `bool IsUERegisterSymbol(const ImmutableString& symbolName, const char*& name, size_t& nameLength);` (scope `symbols`) — BEGIN EPIC MOD
- L431 _prototype_ `bool IsUERegisterSymbol(const ImmutableString& symbolName);` (scope `symbols`)
- L432 _prototype_ `bool IsUENoStripSymbol(const ImmutableString& symbolName);` (scope `symbols`)
- L433 _prototype_ `bool IsUEInitializerSymbol(const ImmutableString& symbolName);` (scope `symbols`)
- L434 _prototype_ `bool IsUEReversePatchSymbol(const ImmutableString& symbolName);` (scope `symbols`)
- L435 _prototype_ `bool IsUEStaticsSymbol(const ImmutableString& symbolName);` (scope `symbols`)

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_Telemetry.h` (Private)


#### class `telemetry::Scope`  
`class Scope`  
_L18-34_
- desc: scoped timing information
- L21 _public prototype_ `explicit Scope(const char* name);`
- L22 _public prototype_ `~Scope(void);`
- L24 _public prototype_ `double ReadSeconds(void) const;`
- L25 _public prototype_ `double ReadMilliSeconds(void) const;`
- L26 _public prototype_ `double ReadMicroSeconds(void) const;`
- L27 _public prototype_ `void Restart(void);`
- L28 _public prototype_ `void End(void);`
- L31 _private member_ `const char* m_name;`
- L32 _private member_ `uint64_t m_start;`
- L33 _private member_ `CriticalSection m_cs;`

#### class `telemetry::Accumulator`  
`class Accumulator`  
_L37-54_
- L40 _public prototype_ `explicit Accumulator(const char* name);`
- L42 _public prototype_ `void Accumulate(uint64_t value);`
- L43 _public prototype_ `void ResetCurrent(void);`
- L45 _public prototype_ `uint64_t ReadCurrent(void) const;`
- L46 _public prototype_ `uint64_t ReadAccumulated(void) const;`
- L48 _public prototype_ `void Print(void);`
- L51 _private member_ `const char* m_name;`
- L52 _private member_ `uint64_t m_current;`
- L53 _private member_ `uint64_t m_accumulated;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace telemetry`

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_TimeDate.h` (Private)


#### class `TimeDate`  
`class TimeDate`  
_L8-36_
- L12 _public typedef_ `typedef char TimeDescription[14];` — A type representing the time format: extended ISO (ISO 8601) hh:mm:ss,mmmm plus a null terminator.
- L15 _public typedef_ `typedef char DateDescription[11];` — A type representing the date format: ISO (ISO 8601) YYYY-MM-DD plus a null terminator.
- L17 _public prototype_ `TimeDate(unsigned short year, unsigned char month, unsigned char day, unsigned char hour, unsigned char minute, unsigned char second, unsigned short milliSecond);`
- L20 _public prototype_ `static TimeDate GetCurrent(void);` — Returns the current time and date in local time.
- L23 _public prototype_ `const char* ToTimeString(TimeDescription& desc) const;` — Converts the time into the extended ISO 8601 format, and returns a pointer to the description string.
- L26 _public prototype_ `const char* ToDateString(DateDescription& desc) const;` — Converts the date into the standard ISO 8601 format, and returns a pointer to the description string.
- L29 _private member_ `unsigned short m_year;`
- L30 _private member_ `unsigned char m_month;`
- L31 _private member_ `unsigned char m_day;`
- L32 _private member_ `unsigned char m_hour;`
- L33 _private member_ `unsigned char m_minute;`
- L34 _private member_ `unsigned char m_second;`
- L35 _private member_ `unsigned short m_milliSecond;`

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_TimeStamp.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace timeStamp`
- L13 _prototype_ `void Startup(void);` (scope `timeStamp`)
- L14 _prototype_ `void Shutdown(void);` (scope `timeStamp`)
- L19 _prototype_ `uint64_t Get(void);` (scope `timeStamp`) — Returns the current value of the high-resolution performance counter. This is not the same as actual CPU cycles.
- L22 _prototype_ `double ToSeconds(uint64_t count);` (scope `timeStamp`) — Converts counts returned by Get() into seconds.
- L25 _prototype_ `double ToMilliSeconds(uint64_t count);` (scope `timeStamp`) — Converts counts returned by Get() into milliseconds.
- L28 _prototype_ `double ToMicroSeconds(uint64_t count);` (scope `timeStamp`) — Converts counts returned by Get() into microseconds.

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_Types.h` (Private)


#### Free symbols / members of external scopes

- L16 _namespace_ `namespace types`
- L20 _typedef_ `template <typename T> using Allocator = std::allocator<T>;` (scope `types`) — using these types allows us to quickly switch allocators for STL data structures if we want to
- L23 _typedef_ `template <typename T> using StringMap = std::unordered_map < ImmutableString, T, ImmutableString::Hasher, ImmutableString::Comparator, Allocator<std::pair<const ImmutableString, T>> >;` (scope `types`)
- L32 _typedef_ `using StringSet = std::unordered_set < ImmutableString, ImmutableString::Hasher, ImmutableString::Comparator, Allocator<ImmutableString> >;` (scope `types`)
- L41 _typedef_ `template <typename T> using vector = std::vector < T, Allocator<T> >;` (scope `types`)
- L48 _typedef_ `template <typename Key, typename Value> using unordered_map = std::unordered_map < Key, Value, std::hash<Key>, std::equal_to<Key>, Allocator<std::pair<const Key, Value>> >;` (scope `types`)
- L58 _typedef_ `template <typename Key, typename Value, typename Hash> using unordered_map_with_hash = std::unordered_map < Key, Value, Hash, std::equal_to<Key>, Allocator<std::pair<const Key, Value>> >;` (scope `types`)
- L68 _typedef_ `template <typename Key> using unordered_set = std::unordered_set < Key, std::hash<Key>, std::equal_to<Key>, Allocator<Key> >;` (scope `types`)

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_UniqueId.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace uniqueId`
- L14 _prototype_ `void Startup(void);` (scope `uniqueId`)
- L15 _prototype_ `void Shutdown(void);` (scope `uniqueId`)
- L17 _prototype_ `uint32_t Generate(const std::wstring& path);` (scope `uniqueId`)

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_VirtualDrive.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace virtualDrive`
- L13 _prototype_ `void Add(const wchar_t* driveLetterPlusColon, const wchar_t* path);` (scope `virtualDrive`)
- L14 _prototype_ `void Remove(const wchar_t* driveLetterPlusColon, const wchar_t* path);` (scope `virtualDrive`)

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_VirtualMemoryRange.h` (Private)


#### class `VirtualMemoryRange`  
`class VirtualMemoryRange`  
_L17-39_
- L20 _public prototype_ `explicit VirtualMemoryRange(Process::Handle processHandle);`
- L21 _public prototype_ `~VirtualMemoryRange(void);`
- L23 _public prototype_ `void ReservePages(const void* addressStart, const void* addressEnd, size_t alignment);`
- L24 _public prototype_ `void FreePages(const void* addressStart, const void* addressEnd);`
- L27 _public prototype_ `void AddPage(void* page);` — BEGIN EPIC MOD
- L36 _private member_ `Process::Handle m_processHandle;`
- L37 _private member_ `types::vector<PageData> m_pageData;`
- L38 _private member_ `CriticalSection m_cs;`

#### struct `VirtualMemoryRange::PageData`  
`struct PageData`  
_L31-34_
- L33 _public member_ `void* address;`

### `Source/Developer/Windows/LiveCodingServer/Private/External/LC_VisualStudioAutomation.h` (Private)


#### Free symbols / members of external scopes

- L16 _namespace_ `namespace visualStudio`
- L18 _prototype_ `void Startup(void);` (scope `visualStudio`)
- L19 _prototype_ `void Shutdown(void);` (scope `visualStudio`)
- L23 _prototype_ `EnvDTE::DebuggerPtr FindDebuggerAttachedToProcess(Process::Id processId);` (scope `visualStudio`) — Finds a Visual Studio debugger instance currently attached to the process with the given ID
- L26 _prototype_ `EnvDTE::DebuggerPtr FindDebuggerForProcess(Process::Id processId);` (scope `visualStudio`) — Finds a Visual Studio debugger instance currently debugging the process with the given ID
- L29 _prototype_ `bool AttachToProcess(const EnvDTE::DebuggerPtr& debugger, Process::Id processId);` (scope `visualStudio`) — Attaches a Visual Studio debugger instance to the process with the given ID
- L32 _prototype_ `types::vector<EnvDTE::ThreadPtr> EnumerateThreads(const EnvDTE::DebuggerPtr& debugger);` (scope `visualStudio`) — Enumerates all threads of a debugger instance
- L35 _prototype_ `bool FreezeThreads(const EnvDTE::DebuggerPtr& debugger, const types::vector<EnvDTE::ThreadPtr>& threads);` (scope `visualStudio`) — Freezes all given threads
- L38 _prototype_ `bool FreezeThread(const EnvDTE::DebuggerPtr& debugger, const types::vector<EnvDTE::ThreadPtr>& threads, Thread::Id threadId);` (scope `visualStudio`) — Freezes a single thread with the given thread ID
- L41 _prototype_ `bool ThawThreads(const EnvDTE::DebuggerPtr& debugger, const types::vector<EnvDTE::ThreadPtr>& threads);` (scope `visualStudio`) — Thaws all given threads
- L44 _prototype_ `bool ThawThread(const EnvDTE::DebuggerPtr& debugger, const types::vector<EnvDTE::ThreadPtr>& threads, Thread::Id threadId);` (scope `visualStudio`) — Thaws a single thread with the given thread ID
- L47 _prototype_ `bool Resume(const EnvDTE::DebuggerPtr& debugger);` (scope `visualStudio`) — Resumes the process in the debugger
- L50 _prototype_ `bool Break(const EnvDTE::DebuggerPtr& debugger);` (scope `visualStudio`) — Breaks the process in the debugger

### `Source/Developer/Windows/LiveCodingServer/Private/LiveCodingServer.h` (Private)


#### class `FLiveCodingServer`  
`class FLiveCodingServer final : public ILiveCodingServer`  
_L12-51_
- inherits: `ILiveCodingServer`
- L15 _public prototype_ `FLiveCodingServer();`
- L16 _public prototype_ `virtual ~FLiveCodingServer();`
- L18 _public prototype_ `virtual void Start(const wchar_t* ProcessGroupName) override;`
- L19 _public prototype_ `virtual void Stop() override;`
- L21 _public prototype_ `virtual void RestartTargets() override;`
- L23 _public prototype_ `virtual void SetLinkerPath(const wchar_t* LinkerPath, const TMap<FString, FString>& LinkerEnvironment) override;`
- L26 _public prototype_ `virtual FBringToFrontDelegate& GetBringToFrontDelegate() override final;` — ILiveCodingServer implementation
- L27 _public prototype_ `virtual FClearOutputDelegate& GetClearOutputDelegate() override final;`
- L28 _public prototype_ `virtual FStatusChangeDelegate& GetStatusChangeDelegate() override final;`
- L29 _public prototype_ `virtual FLogOutputDelegate& GetLogOutputDelegate() override final;`
- L30 _public prototype_ `virtual FCompileDelegate& GetCompileDelegate() override final;`
- L31 _public prototype_ `virtual FCompileStartedDelegate& GetCompileStartedDelegate() override final;`
- L32 _public prototype_ `virtual FCompileFinishedDelegate& GetCompileFinishedDelegate() override final;`
- L33 _public prototype_ `virtual FShowConsoleDelegate& GetShowConsoleDelegate() override final;`
- L34 _public prototype_ `virtual FSetVisibleDelegate& GetSetVisibleDelegate() override final;`
- L35 _public prototype_ `virtual bool HasReinstancingProcess() override final;`
- L36 _public prototype_ `virtual bool ShowCompileFinishNotification() override final;`
- L39 _private member_ `std::wstring ProcessGroupName;`
- L40 _private member_ `ServerCommandThread* CommandThread;`
- L42 _private member_ `FBringToFrontDelegate BringToFrontDelegate;`
- L43 _private member_ `FClearOutputDelegate ClearOutputDelegate;`
- L44 _private member_ `FStatusChangeDelegate StatusChangeDelegate;`
- L45 _private member_ `FLogOutputDelegate LogOutputDelegate;`
- L46 _private member_ `FCompileDelegate CompileDelegate;`
- L47 _private member_ `FCompileStartedDelegate CompileStartedDelegate;`
- L48 _private member_ `FCompileFinishedDelegate CompileFinishedDelegate;`
- L49 _private member_ `FShowConsoleDelegate ShowConsoleDelegate;`
- L50 _private member_ `FSetVisibleDelegate SetVisibleDelegate;`

#### Free symbols / members of external scopes

- L53 _externvar_ `extern FLiveCodingServer *GLiveCodingServer;`

### `Source/Developer/Windows/LiveCodingServer/Private/LiveCodingServerModule.h` (Private)


#### class `FLiveCodingServerModule`  
`class FLiveCodingServerModule : public ILiveCodingServerModule`  
_L8-14_
- inherits: `ILiveCodingServerModule`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Source/Developer/Windows/LiveCodingServer/Public/ILiveCodingServer.h` (Public)


#### enum `ELiveCodingResult`  
`enum class ELiveCodingResult`  
_L13-17_
- L15 _public enumerator_ `Success`
- L16 _public enumerator_ `Error`

#### enum `ELiveCodingLogVerbosity`  
`enum class ELiveCodingLogVerbosity`  
_L19-25_
- L21 _public enumerator_ `Info`
- L22 _public enumerator_ `Success`
- L23 _public enumerator_ `Warning`
- L24 _public enumerator_ `Failure`

#### enum `ELiveCodingCompileReason`  
`enum class ELiveCodingCompileReason`  
_L27-31_
- L29 _public enumerator_ `Initial`
- L30 _public enumerator_ `Retry`

#### enum `ELiveCodingCompileResult`  
`enum class ELiveCodingCompileResult`  
_L33-39_
- L35 _public enumerator_ `Success`
- L36 _public enumerator_ `Canceled`
- L37 _public enumerator_ `Failure`
- L38 _public enumerator_ `Retry`

#### class `ILiveCodingServerModule`  
`class ILiveCodingServerModule : public IModuleInterface`  
_L41-47_
- inherits: `IModuleInterface`
- L45 _public prototype_ `virtual void StartupModule() override = 0;` — IModuleInterface implementation
- L46 _public prototype_ `virtual void ShutdownModule() override = 0;`

#### struct `FModuleFiles`  
`struct FModuleFiles`  
_L49-53_
- L51 _public member_ `TArray<FString> Objects;`
- L52 _public member_ `TArray<FString> Libraries;`

#### class `ILiveCodingServer`  
`class ILiveCodingServer : public IModularFeature`  
_L56-96_
- inherits: `IModularFeature`
- L59 _public prototype_ `virtual void Start(const wchar_t* ProcessGroupName) = 0;`
- L60 _public prototype_ `virtual void Stop() = 0;`
- L62 _public prototype_ `virtual void RestartTargets() = 0;`
- L64 _public prototype_ `virtual void SetLinkerPath(const wchar_t* LinkerPath, const TMap<FString, FString>& LinkerEnvironment) = 0;`
- L66 _public prototype_ `DECLARE_DELEGATE(FBringToFrontDelegate);`
- L67 _public prototype_ `virtual FBringToFrontDelegate& GetBringToFrontDelegate() = 0;`
- L69 _public prototype_ `DECLARE_DELEGATE(FClearOutputDelegate);`
- L70 _public prototype_ `virtual FClearOutputDelegate& GetClearOutputDelegate() = 0;`
- L72 _public prototype_ `DECLARE_DELEGATE_OneParam(FStatusChangeDelegate, const wchar_t*);`
- L73 _public prototype_ `virtual FStatusChangeDelegate& GetStatusChangeDelegate() = 0;`
- L75 _public prototype_ `DECLARE_DELEGATE_TwoParams(FLogOutputDelegate, ELiveCodingLogVerbosity, const wchar_t*);`
- L76 _public prototype_ `virtual FLogOutputDelegate& GetLogOutputDelegate() = 0;`
- L78 _public prototype_ `DECLARE_DELEGATE_RetVal_SixParams(ELiveCodingCompileResult, FCompileDelegate, const TArray<FString>&, const TArray<FString>&, const TSet<FString>&, TArray<FString>&, FModuleToModuleFiles&, ELiveCodingCompileReason);`
- L79 _public prototype_ `virtual FCompileDelegate& GetCompileDelegate() = 0;`
- L81 _public prototype_ `DECLARE_DELEGATE(FCompileStartedDelegate);`
- L82 _public prototype_ `virtual FCompileStartedDelegate& GetCompileStartedDelegate() = 0;`
- L84 _public prototype_ `DECLARE_DELEGATE_TwoParams(FCompileFinishedDelegate, ELiveCodingResult, const wchar_t*);`
- L85 _public prototype_ `virtual FCompileFinishedDelegate& GetCompileFinishedDelegate() = 0;`
- L87 _public prototype_ `DECLARE_DELEGATE(FShowConsoleDelegate);`
- L88 _public prototype_ `virtual FShowConsoleDelegate& GetShowConsoleDelegate() = 0;`
- L90 _public prototype_ `DECLARE_DELEGATE_OneParam(FSetVisibleDelegate, bool);`
- L91 _public prototype_ `virtual FSetVisibleDelegate& GetSetVisibleDelegate() = 0;`
- L93 _public prototype_ `virtual bool HasReinstancingProcess() = 0;`
- L95 _public prototype_ `virtual bool ShowCompileFinishNotification() = 0;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define LIVE_CODING_SERVER_FEATURE_NAME "LiveCodingServer"`
- L54 _typedef_ `typedef TMap<FString, FModuleFiles> FModuleToModuleFiles;`
- L66 _delegate_ `DECLARE_DELEGATE(FBringToFrontDelegate);`
- L69 _delegate_ `DECLARE_DELEGATE(FClearOutputDelegate);`
- L72 _delegate_ `DECLARE_DELEGATE_OneParam(FStatusChangeDelegate, const wchar_t*);`
- L75 _delegate_ `DECLARE_DELEGATE_TwoParams(FLogOutputDelegate, ELiveCodingLogVerbosity, const wchar_t*);`
- L78 _delegate_ `DECLARE_DELEGATE_RetVal_SixParams(ELiveCodingCompileResult, FCompileDelegate, const TArray<FString>&, const TArray<FString>&, const TSet<FString>&, TArray<FString>&, FModuleToModuleFiles&, ELiveCodingCompileReason);`
- L81 _delegate_ `DECLARE_DELEGATE(FCompileStartedDelegate);`
- L84 _delegate_ `DECLARE_DELEGATE_TwoParams(FCompileFinishedDelegate, ELiveCodingResult, const wchar_t*);`
- L87 _delegate_ `DECLARE_DELEGATE(FShowConsoleDelegate);`
- L90 _delegate_ `DECLARE_DELEGATE_OneParam(FSetVisibleDelegate, bool);`
