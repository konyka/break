# Developer / LiveCoding

- module root: `Source/Developer/Windows/LiveCoding`
- headers: 59; symbols: 1635
- symbol kinds: class=25, delegate=2, enum=20, enumerator=62, externvar=7, function=184, macro=263, member=420, namespace=38, prototype=463, struct=90, typedef=43, union=5, variable=13
- PrivateDependencyModuleNames: BuildSettings, Core, CoreUObject, Engine, OodleDataCompression, Settings, Slate, UnrealEd

### `Source/Developer/Windows/LiveCoding/Private/External/LC_API.h` (Private)


#### Free symbols / members of external scopes

- L16 _macro_ `#define LPP_DLL_API(_rv) _rv __cdecl` — external Live++ API exported into DLL BEGIN EPIC MOD - Internalizing API

### `Source/Developer/Windows/LiveCoding/Private/External/LC_Assert.h` (Private)


#### Free symbols / members of external scopes

- L15 _macro_ `# define LC_ASSERT_BREAKPOINT() (Debugger::IsConnected()) ? LC_DEBUGGER_BREAKPOINT() : (void)true`
- L16 _macro_ `# define LC_ASSERT(_condition, _msg) (_condition) ? (void)true : (LC_ERROR_DEV("%s", _msg), LC_ASSERT_BREAKPOINT())`
- L18 _macro_ `# define LC_BREAKPOINT() (void)true`
- L19 _macro_ `# define LC_ASSERT(_condition, _msg) LC_UNUSED(_condition)`

### `Source/Developer/Windows/LiveCoding/Private/External/LC_Atomic_Windows.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Atomic`
- L14 _prototype_ `void IncrementConsistent(volatile int32_t* value);` (scope `Atomic`) — Increments a value atomically, guaranteeing sequential consistency.
- L17 _prototype_ `void DecrementConsistent(volatile int32_t* value);` (scope `Atomic`) — Decrements a value atomically, guaranteeing sequential consistency.

### `Source/Developer/Windows/LiveCoding/Private/External/LC_BitUtil.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace bitUtil`
- L16 _function_ `template <typename T> inline T RoundUpToMultiple(T numToRound, T multipleOf)` (scope `bitUtil`)
- L25 _function_ `template <typename T> inline bool IsPowerOfTwo(T value)` (scope `bitUtil`) — http://www.graphics.stanford.edu/~seander/bithacks.html#DetermineIfPowerOf2
- L33 _function_ `inline uint32_t BitScanReverse(uint32_t value)` (scope `bitUtil`) — Finds the first set bit, searching from MSB to LSB. Can be used to determine the log2 of integers that are powers of two.

### `Source/Developer/Windows/LiveCoding/Private/External/LC_ClientCommandActions.h` (Private)


#### Free symbols / members of external scopes

- L15 _namespace_ `namespace actions`
- L17 _macro_ `#define DECLARE_ACTION(_name) \`
- L24 _prototype_ `DECLARE_ACTION(RegisterProcessFinished);` (scope `actions`)
- L25 _prototype_ `DECLARE_ACTION(EnableModulesFinished);` (scope `actions`)
- L26 _prototype_ `DECLARE_ACTION(DisableModulesFinished);` (scope `actions`)
- L27 _prototype_ `DECLARE_ACTION(EnterSyncPoint);` (scope `actions`)
- L28 _prototype_ `DECLARE_ACTION(LeaveSyncPoint);` (scope `actions`)
- L29 _prototype_ `DECLARE_ACTION(CallHooks);` (scope `actions`)
- L30 _prototype_ `DECLARE_ACTION(LoadPatch);` (scope `actions`)
- L31 _prototype_ `DECLARE_ACTION(UnloadPatch);` (scope `actions`)
- L32 _prototype_ `DECLARE_ACTION(CallEntryPoint);` (scope `actions`)
- L33 _prototype_ `DECLARE_ACTION(LogOutput);` (scope `actions`)
- L34 _prototype_ `DECLARE_ACTION(CompilationFinished);` (scope `actions`)
- L35 _prototype_ `DECLARE_ACTION(HandleExceptionFinished);` (scope `actions`)
- L37 _prototype_ `DECLARE_ACTION(PreCompile);` (scope `actions`) — BEGIN EPIC MOD
- L38 _prototype_ `DECLARE_ACTION(PostCompile);` (scope `actions`)
- L39 _prototype_ `DECLARE_ACTION(TriggerReload);` (scope `actions`)

### `Source/Developer/Windows/LiveCoding/Private/External/LC_ClientCommandThread.h` (Private)


#### class `ClientCommandThread`  
`class ClientCommandThread`  
_L21-39_
- desc: handles incoming commands from the Live++ server
- L24 _public prototype_ `explicit ClientCommandThread(DuplexPipeClient* pipeClient);`
- L25 _public prototype_ `~ClientCommandThread(void);`
- L29 _public prototype_ `Thread::Id Start(const std::wstring& processGroupName, Event* compilationEvent, Event* waitForStartEvent, CriticalSection* pipeAccessCS);` — Starts the thread that takes care of handling incoming commands on the pipe. Returns the thread ID.
- L32 _public prototype_ `void Join(void);` — Joins this thread.
- L35 _private prototype_ `Thread::ReturnValue ThreadFunction(const std::wstring& processGroupName, Event* compilationEvent, Event* waitForStartEvent, CriticalSection* pipeAccessCS);`
- L37 _private member_ `Thread::Handle m_thread;`
- L38 _private member_ `DuplexPipeClient* m_pipe;`

### `Source/Developer/Windows/LiveCoding/Private/External/LC_ClientStartupThread.h` (Private)


#### class `ClientStartupThread`  
`class ClientStartupThread`  
_L25-125_
- L28 _public prototype_ `ClientStartupThread(void);`
- L29 _public prototype_ `~ClientStartupThread(void);`
- L32 _public prototype_ `void Start(const char* const groupName, RunMode::Enum runMode);` — Spawns a thread that runs client initialization
- L35 _public prototype_ `void Join(void);` — Joins the thread, waiting for initialization to finish
- L37 _public prototype_ `void* EnableModule(const wchar_t* nameOfExeOrDll);`
- L38 _public prototype_ `void* EnableModules(const wchar_t* namesOfExeOrDll[], unsigned int count);`
- L39 _public prototype_ `void* EnableAllModules(const wchar_t* nameOfExeOrDll);`
- L41 _public prototype_ `void* DisableModule(const wchar_t* nameOfExeOrDll);`
- L42 _public prototype_ `void* DisableModules(const wchar_t* namesOfExeOrDll[], unsigned int count);`
- L43 _public prototype_ `void* DisableAllModules(const wchar_t* nameOfExeOrDll);`
- L46 _public prototype_ `bool TryWaitForToken(void* token);` — BEGIN EPIC MOD - Adding TryWaitForToken
- L49 _public prototype_ `void WaitForToken(void* token);`
- L50 _public prototype_ `void TriggerRecompile(void);`
- L51 _public prototype_ `void LogMessage(const wchar_t* message);`
- L52 _public prototype_ `void BuildPatch(const wchar_t* moduleNames[], const wchar_t* objPaths[], const wchar_t* amalgamatedObjPaths[], unsigned int count);`
- L54 _public prototype_ `void InstallExceptionHandler(void);`
- L56 _public prototype_ `void TriggerRestart(void);`
- L58 _public prototype_ `void ApplySettingBool(const char* settingName, int value);`
- L59 _public prototype_ `void ApplySettingInt(const char* settingName, int value);`
- L60 _public prototype_ `void ApplySettingString(const char* settingName, const wchar_t* value);`
- L63 _public prototype_ `void ShowConsole();` — BEGIN EPIC MOD - Adding ShowConsole command
- L67 _public prototype_ `void SetVisible(bool visible);` — BEGIN EPIC MOD - Adding SetVisible command
- L71 _public prototype_ `void SetActive(bool active);` — BEGIN EPIC MOD - Adding SetActive command
- L75 _public prototype_ `void SetBuildArguments(const wchar_t* arguments);` — BEGIN EPIC MOD - Adding SetBuildArguments command
- L79 _public prototype_ `void* EnableLazyLoadedModule(const wchar_t* fileName, Windows::HMODULE moduleBase);` — BEGIN EPIC MOD - Support for lazy-loading modules
- L83 _public prototype_ `void SetReinstancingFlow(bool Enable);` — BEGIN EPIC MOD
- L87 _public prototype_ `void DisableCompileFinishNotification();` — BEGIN EPIC MOD
- L91 _public prototype_ `void* EnableModulesEx(const wchar_t* moduleNames[], unsigned int moduleCount, const wchar_t* lazyLoadModuleNames[], unsigned int lazyLoadModuleCount, const uintptr_t* reservedPages, unsigned int reservedPagesCount);` — BEGIN EPIC MOD
- L95 _private prototype_ `Thread::ReturnValue ThreadFunction(const std::wstring& groupName, RunMode::Enum runMode);`
- L97 _private member_ `Thread::Handle m_thread;`
- L100 _private member_ `HANDLE m_job;` — job object for associating spawned processes with main process the DLL is loaded into
- L103 _private member_ `Process::NamedSharedMemory* m_sharedMemory;` — named shared memory for sharing the Live++ process ID between processes
- L106 _private member_ `Process::Context* m_mainProcessContext;` — main Live++ process. context may be empty in case we connected to an existing Live++ process
- L107 _private member_ `Process::Handle m_processHandle;`
- L109 _private member_ `bool m_successfulInit;`
- L112 _private member_ `DuplexPipeClient* m_pipeClient;` — pipe used for interprocess communication
- L113 _private member_ `DuplexPipeClient* m_exceptionPipeClient;`
- L114 _private member_ `CriticalSection* m_pipeClientCS;`
- L117 _private member_ `ClientCommandThread* m_commandThread;` — helper threads taking care of communication with the Live++ server and user code
- L118 _private member_ `ClientUserCommandThread* m_userCommandThread;`
- L121 _private member_ `Event* m_startEvent;` — manual-reset start event that signals to the helper threads that they can start talking to the pipe
- L124 _private member_ `Event* m_compilationEvent;` — process-wide event that is signaled by the Live++ server when compilation is about to begin

### `Source/Developer/Windows/LiveCoding/Private/External/LC_ClientUserCommandThread.h` (Private)


#### class `ClientUserCommandThread`  
`class ClientUserCommandThread`  
_L24-136_
- desc: handles incoming commands from the host (the executable that loaded the Live++ DLL)
- L49 _public prototype_ `ClientUserCommandThread(DuplexPipeClient* pipeClient, DuplexPipeClient* exceptionPipeClient);`
- L50 _public prototype_ `~ClientUserCommandThread(void);`
- L53 _public prototype_ `Thread::Id Start(const std::wstring& processGroupName, Event* waitForStartEvent, CriticalSection* pipeAccessCS);` — Starts the thread that takes care of handling incoming commands on the pipe.
- L56 _public prototype_ `void Join(void);` — Joins this thread.
- L58 _public prototype_ `void* EnableModule(const wchar_t* nameOfExeOrDll);`
- L59 _public prototype_ `void* EnableModules(const wchar_t* namesOfExeOrDll[], unsigned int count);`
- L60 _public prototype_ `void* EnableAllModules(const wchar_t* nameOfExeOrDll);`
- L62 _public prototype_ `void* DisableModule(const wchar_t* nameOfExeOrDll);`
- L63 _public prototype_ `void* DisableModules(const wchar_t* namesOfExeOrDll[], unsigned int count);`
- L64 _public prototype_ `void* DisableAllModules(const wchar_t* nameOfExeOrDll);`
- L67 _public prototype_ `bool TryWaitForToken(void* token);` — BEGIN EPIC MOD - Adding TryWaitForToken
- L70 _public prototype_ `void WaitForToken(void* token);`
- L71 _public prototype_ `void TriggerRecompile(void);`
- L72 _public prototype_ `void LogMessage(const wchar_t* message);`
- L73 _public prototype_ `void BuildPatch(const wchar_t* moduleNames[], const wchar_t* objPaths[], const wchar_t* amalgamatedObjPaths[], unsigned int count);`
- L75 _public prototype_ `void TriggerRestart(void);`
- L78 _public prototype_ `void ShowConsole();` — BEGIN EPIC MOD - Adding ShowConsole command
- L82 _public prototype_ `void SetVisible(bool visible);` — BEGIN EPIC MOD - Adding SetVisible command
- L86 _public prototype_ `void SetActive(bool active);` — BEGIN EPIC MOD - Adding SetActive command
- L90 _public prototype_ `void SetBuildArguments(const wchar_t* arguments);` — BEGIN EPIC MOD - Adding SetBuildArguments command
- L94 _public prototype_ `void* EnableLazyLoadedModule(const wchar_t* fileName, Windows::HMODULE moduleBase);` — BEGIN EPIC MOD - Support for lazy-loading modules
- L98 _public prototype_ `void SetReinstancingFlow(bool enable);` — BEGIN EPIC MOD
- L102 _public prototype_ `void DisableCompileFinishNotification();` — BEGIN EPIC MOD
- L106 _public prototype_ `void* EnableModulesEx(const wchar_t* moduleNames[], unsigned int moduleCount, const wchar_t* lazyLoadModuleNames[], unsigned int lazyLoadModuleCount, const uintptr_t* reservedPages, unsigned int reservedPagesCount);` — BEGIN EPIC MOD
- L109 _public prototype_ `void ApplySettingBool(const char* settingName, int value);`
- L110 _public prototype_ `void ApplySettingInt(const char* settingName, int value);`
- L111 _public prototype_ `void ApplySettingString(const char* settingName, const wchar_t* value);`
- L113 _public prototype_ `void InstallExceptionHandler(void);`
- L114 _public prototype_ `ExceptionResult HandleException(EXCEPTION_RECORD* exception, CONTEXT* context, Thread::Id threadId);`
- L115 _public prototype_ `void End(void);`
- L119 _private prototype_ `void PushUserCommand(BaseCommand* command);` — pushes a user command into the command queue
- L123 _private prototype_ `BaseCommand* PopUserCommand(void);` — pops a user command from the command queue. blocks until a command becomes available.
- L125 _private prototype_ `Thread::ReturnValue ThreadFunction(Event* waitForStartEvent, CriticalSection* pipeAccessCS);`
- L127 _private member_ `Thread::Handle m_thread;`
- L128 _private member_ `std::wstring m_processGroupName;`
- L129 _private member_ `DuplexPipeClient* m_pipe;`
- L130 _private member_ `DuplexPipeClient* m_exceptionPipe;`
- L133 _private member_ `std::deque<BaseCommand*> m_userCommandQueue;` — queue for working on commands received by user code
- L134 _private member_ `CriticalSection m_userCommandQueueCS;`
- L135 _private member_ `Semaphore m_userCommandQueueSema;`

#### class `ClientUserCommandThread::BaseCommand`  
`class BaseCommand`  
_L27-39_
- L30 _public prototype_ `explicit BaseCommand(bool expectResponse);`
- L31 _public prototype_ `virtual ~BaseCommand(void);`
- L33 _public prototype_ `virtual void Execute(DuplexPipe* pipe) = 0;`
- L35 _public prototype_ `bool ExpectsResponse(void) const;`
- L38 _private member_ `bool m_expectResponse;`

#### struct `ClientUserCommandThread::ExceptionResult`  
`struct ExceptionResult`  
_L41-47_
- L43 _public member_ `const void* returnAddress;`
- L44 _public member_ `const void* framePointer;`
- L45 _public member_ `const void* stackPointer;`
- L46 _public member_ `bool continueExecution;`

### `Source/Developer/Windows/LiveCoding/Private/External/LC_CommandMap.h` (Private)


#### class `CommandMap`  
`class CommandMap`  
_L17-51_
- L20 _private function_ `template <class T> static bool ReceiveAndCallAction(const DuplexPipe* pipe, void* context, void* payload, size_t payloadSize)`
- L36 _public typedef_ `typedef bool (*Action)(const DuplexPipe*, void*, void*, size_t);` — an action returns whether execution should continue
- L38 _public prototype_ `CommandMap(void);`
- L39 _public prototype_ `~CommandMap(void);`
- L42 _public function_ `template <class T> void RegisterAction(void)`
- L47 _public prototype_ `bool HandleCommands(const DuplexPipe* pipe, void* context);`
- L50 _private member_ `Action m_actions[commands::COUNT];`

### `Source/Developer/Windows/LiveCoding/Private/External/LC_Commands.h` (Private)


#### struct `commands::Header`  
`struct Header`  
_L18-22_
- L20 _public member_ `uint32_t commandId;`
- L21 _public member_ `uint32_t payloadSize;`

#### struct `commands::ModuleData`  
`struct ModuleData`  
_L24-30_
- L26 _public member_ `void* base;`
- L28 _public member_ `wchar_t path[WINDOWS_MAX_PATH];` — BEGIN EPIC MOD

#### struct `commands::Acknowledge`  
`struct Acknowledge`  
_L33-38_
- desc: acknowledge that a command has been received
- L36 _public member_ `static const uint32_t ID = 100;` — BEGIN EPIC MOD

#### struct `commands::RegisterProcess`  
`struct RegisterProcess`  
_L41-57_
- desc: register a process with Live++
- L43 _public member_ `static const uint32_t ID = Acknowledge::ID + 1u;`
- L45 _public member_ `void* processBase;`
- L46 _public member_ `Process::Id processId;` — current process ID
- L47 _public member_ `Process::Id restartedProcessId;` — process ID of the previous, restarted process. 0 if non-existent
- L48 _public member_ `Thread::Id threadId;` — thread ID of Live++ thread running in host
- L49 _public member_ `const void* jumpToSelf;` — address of jump-to-self instruction in host
- L51 _public member_ `size_t imagePathSize;`
- L52 _public member_ `size_t commandLineSize;`
- L53 _public member_ `size_t workingDirectorySize;`
- L54 _public member_ `size_t environmentSize;`

#### struct `commands::RegisterProcessFinished`  
`struct RegisterProcessFinished`  
_L60-65_
- desc: tell the DLL that registration has finished
- L62 _public member_ `static const uint32_t ID = RegisterProcess::ID + 1u;`
- L64 _public member_ `bool success;`

#### struct `commands::EnableModules`  
`struct EnableModules`  
_L68-77_
- desc: tell Live++ to enable modules for live coding
- L70 _public member_ `static const uint32_t ID = RegisterProcessFinished::ID + 1u;`
- L72 _public member_ `Process::Id processId;`
- L73 _public member_ `unsigned int moduleCount;`
- L74 _public member_ `void* token;`

#### struct `commands::EnableModulesFinished`  
`struct EnableModulesFinished`  
_L80-85_
- desc: tell the DLL that enabling modules has finished
- L82 _public member_ `static const uint32_t ID = EnableModules::ID + 1u;`
- L84 _public member_ `void* token;`

#### struct `commands::DisableModules`  
`struct DisableModules`  
_L88-97_
- desc: tell Live++ to disable modules for live coding
- L90 _public member_ `static const uint32_t ID = EnableModulesFinished::ID + 1u;`
- L92 _public member_ `Process::Id processId;`
- L93 _public member_ `unsigned int moduleCount;`
- L94 _public member_ `void* token;`

#### struct `commands::DisableModulesFinished`  
`struct DisableModulesFinished`  
_L100-105_
- desc: tell the DLL that disabling a module has finished
- L102 _public member_ `static const uint32_t ID = DisableModules::ID + 1u;`
- L104 _public member_ `void* token;`

#### struct `commands::EnterSyncPoint`  
`struct EnterSyncPoint`  
_L108-111_
- desc: tell the DLL to enter the synchronization point
- L110 _public member_ `static const uint32_t ID = DisableModulesFinished::ID + 1u;`

#### struct `commands::LeaveSyncPoint`  
`struct LeaveSyncPoint`  
_L114-117_
- desc: tell the DLL to leave the synchronization point
- L116 _public member_ `static const uint32_t ID = EnterSyncPoint::ID + 1u;`

#### struct `commands::CallHooks`  
`struct CallHooks`  
_L120-127_
- desc: tell the DLL to call hooks
- L122 _public member_ `static const uint32_t ID = LeaveSyncPoint::ID + 1u;`
- L124 _public member_ `hook::Type::Enum type;`
- L125 _public member_ `const void* rangeBegin;`
- L126 _public member_ `const void* rangeEnd;`

#### struct `commands::LoadPatch`  
`struct LoadPatch`  
_L130-137_
- desc: tell the DLL to load a DLL
- L132 _public member_ `static const uint32_t ID = CallHooks::ID + 1u;`
- L135 _public member_ `wchar_t path[WINDOWS_MAX_PATH];` — BEGIN EPIC MOD

#### struct `commands::LoadPatchInfo`  
`struct LoadPatchInfo`  
_L140-147_
- desc: returns info about a loaded DLL to Live++
- L142 _public member_ `static const uint32_t ID = LoadPatch::ID + 1u;`
- L145 _public member_ `Windows::HMODULE module;` — BEGIN EPIC MOD

#### struct `commands::UnloadPatch`  
`struct UnloadPatch`  
_L150-157_
- desc: tell the DLL to unload a DLL
- L152 _public member_ `static const uint32_t ID = LoadPatchInfo::ID + 1u;`
- L155 _public member_ `Windows::HMODULE module;` — BEGIN EPIC MOD

#### struct `commands::CallEntryPoint`  
`struct CallEntryPoint`  
_L160-166_
- desc: tell the DLL to call the entry point of a DLL
- L162 _public member_ `static const uint32_t ID = UnloadPatch::ID + 1u;`
- L164 _public member_ `void* moduleBase;`
- L165 _public member_ `uint32_t entryPointRva;`

#### struct `commands::LogOutput`  
`struct LogOutput`  
_L169-172_
- desc: tell the DLL to log output
- L171 _public member_ `static const uint32_t ID = CallEntryPoint::ID + 1u;`

#### struct `commands::ReadyForCompilation`  
`struct ReadyForCompilation`  
_L175-178_
- desc: tell Live++ server we're ready for compilation
- L177 _public member_ `static const uint32_t ID = LogOutput::ID + 1u;`

#### struct `commands::CompilationFinished`  
`struct CompilationFinished`  
_L181-184_
- desc: tell the DLL that compilation has finished
- L183 _public member_ `static const uint32_t ID = ReadyForCompilation::ID + 1u;`

#### struct `commands::DisconnectClient`  
`struct DisconnectClient`  
_L187-190_
- desc: tell Live++ server that a client is about to disconnect
- L189 _public member_ `static const uint32_t ID = CompilationFinished::ID + 1u;`

#### struct `commands::TriggerRecompile`  
`struct TriggerRecompile`  
_L193-196_
- desc: tell Live++ to trigger a recompile
- L195 _public member_ `static const uint32_t ID = DisconnectClient::ID + 1u;`

#### struct `commands::TriggerRestart`  
`struct TriggerRestart`  
_L199-202_
- desc: tell Live++ to trigger a restart
- L201 _public member_ `static const uint32_t ID = TriggerRecompile::ID + 1u;`

#### struct `commands::LogMessage`  
`struct LogMessage`  
_L205-208_
- desc: tell Live++ to log a message
- L207 _public member_ `static const uint32_t ID = TriggerRestart::ID + 1u;`

#### struct `commands::BuildPatch`  
`struct BuildPatch`  
_L211-224_
- desc: tell Live++ to build a patch using an array of object files
- L213 _public member_ `static const uint32_t ID = LogMessage::ID + 1u;`
- L215 _public member_ `unsigned int fileCount;`

#### struct `commands::BuildPatch::PatchData`  
`struct PatchData`  
_L218-223_
- desc: this command always contains an array of 'PatchData x fileCount' as payload
- L220 _public member_ `wchar_t moduleName[MAX_PATH];`
- L221 _public member_ `wchar_t objPath[MAX_PATH];`
- L222 _public member_ `wchar_t amalgamatedObjPath[MAX_PATH];`

#### struct `commands::HandleException`  
`struct HandleException`  
_L227-236_
- desc: tell Live++ to handle an exception
- L229 _public member_ `static const uint32_t ID = BuildPatch::ID + 1u;`
- L231 _public member_ `Process::Id processId;`
- L232 _public member_ `Thread::Id threadId;`
- L233 _public member_ `EXCEPTION_RECORD exception;`
- L234 _public member_ `CONTEXT context;`
- L235 _public member_ `CONTEXT* clientContextPtr;`

#### struct `commands::HandleExceptionFinished`  
`struct HandleExceptionFinished`  
_L239-247_
- desc: tell the DLL that handling an exception has finished
- L241 _public member_ `static const uint32_t ID = HandleException::ID + 1u;`
- L243 _public member_ `const void* returnAddress;`
- L244 _public member_ `const void* framePointer;`
- L245 _public member_ `const void* stackPointer;`
- L246 _public member_ `bool continueExecution;`

#### struct `commands::ApplySettingBool`  
`struct ApplySettingBool`  
_L250-256_
- desc: tell the EXE that a bool setting needs to be changed
- L252 _public member_ `static const uint32_t ID = HandleExceptionFinished::ID + 1u;`
- L254 _public member_ `char settingName[256];`
- L255 _public member_ `int settingValue;`

#### struct `commands::ApplySettingInt`  
`struct ApplySettingInt`  
_L259-265_
- desc: tell the EXE that a int setting needs to be changed
- L261 _public member_ `static const uint32_t ID = ApplySettingBool::ID + 1u;`
- L263 _public member_ `char settingName[256];`
- L264 _public member_ `int settingValue;`

#### struct `commands::ApplySettingString`  
`struct ApplySettingString`  
_L268-274_
- desc: tell the EXE that a bool setting needs to be changed
- L270 _public member_ `static const uint32_t ID = ApplySettingInt::ID + 1u;`
- L272 _public member_ `char settingName[256];`
- L273 _public member_ `wchar_t settingValue[256];`

#### struct `commands::ShowConsole`  
`struct ShowConsole`  
_L277-280_
- desc: BEGIN EPIC MOD
- L279 _public member_ `static const uint32_t ID = ApplySettingString::ID + 1u;`

#### struct `commands::SetVisible`  
`struct SetVisible`  
_L282-287_
- L284 _public member_ `static const uint32_t ID = ShowConsole::ID + 1u;`
- L286 _public member_ `bool visible;`

#### struct `commands::SetActive`  
`struct SetActive`  
_L289-294_
- L291 _public member_ `static const uint32_t ID = SetVisible::ID + 1u;`
- L293 _public member_ `bool active;`

#### struct `commands::SetBuildArguments`  
`struct SetBuildArguments`  
_L296-302_
- L298 _public member_ `static const uint32_t ID = SetActive::ID + 1u;`
- L300 _public member_ `Process::Id processId;`
- L301 _public member_ `wchar_t arguments[1024];`

#### struct `commands::EnableLazyLoadedModule`  
`struct EnableLazyLoadedModule`  
_L304-312_
- L306 _public member_ `static const uint32_t ID = SetBuildArguments::ID + 1u;`
- L308 _public member_ `Process::Id processId;`
- L309 _public member_ `wchar_t fileName[260];`
- L310 _public member_ `Windows::HMODULE moduleBase;`
- L311 _public member_ `void* token;`

#### struct `commands::FinishedLazyLoadingModules`  
`struct FinishedLazyLoadingModules`  
_L314-317_
- L316 _public member_ `static const uint32_t ID = EnableLazyLoadedModule::ID + 1u;`

#### struct `commands::PreCompile`  
`struct PreCompile`  
_L319-322_
- L321 _public member_ `static const uint32_t ID = FinishedLazyLoadingModules::ID + 1u;`

#### enum `commands::PostCompileResult`  
`enum class PostCompileResult : unsigned char`  
_L324-330_
- L326 _public enumerator_ `Success`
- L327 _public enumerator_ `NoChanges`
- L328 _public enumerator_ `Failure`
- L329 _public enumerator_ `Cancelled`

#### struct `commands::PostCompile`  
`struct PostCompile`  
_L332-336_
- L334 _public member_ `static const uint32_t ID = PreCompile::ID + 1u;`
- L335 _public member_ `PostCompileResult postCompileResult = PostCompileResult::Success;`

#### struct `commands::TriggerReload`  
`struct TriggerReload`  
_L338-341_
- L340 _public member_ `static const uint32_t ID = PostCompile::ID + 1u;`

#### struct `commands::SetReinstancingFlow`  
`struct SetReinstancingFlow`  
_L343-349_
- L345 _public member_ `static const uint32_t ID = TriggerReload::ID + 1u;`
- L347 _public member_ `Process::Id processId;`
- L348 _public member_ `bool enable;`

#### struct `commands::DisableCompileFinishNotification`  
`struct DisableCompileFinishNotification`  
_L351-356_
- L353 _public member_ `static const uint32_t ID = SetReinstancingFlow::ID + 1u;`
- L355 _public member_ `Process::Id processId;`

#### struct `commands::EnableModulesEx`  
`struct EnableModulesEx`  
_L359-370_
- desc: This is a version of EnableModules that includes support for lazy modules and pre-reserved page addresses.
- L361 _public member_ `static const uint32_t ID = DisableCompileFinishNotification::ID + 1u;`
- L363 _public member_ `Process::Id processId;`
- L364 _public member_ `unsigned int moduleCount;`
- L365 _public member_ `unsigned int lazyLoadModuleCount;`
- L366 _public member_ `unsigned int reservedPagesCount;`
- L367 _public member_ `void* token;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace commands`
- L372 _variable_ `static const uint32_t COUNT = EnableModulesEx::ID + 1u;` (scope `commands`)

### `Source/Developer/Windows/LiveCoding/Private/External/LC_CriticalSection.h` (Private)


#### class `CriticalSection`  
`class CriticalSection`  
_L14-50_
- L17 _public prototype_ `CriticalSection(void);`
- L18 _public prototype_ `~CriticalSection(void);`
- L20 _public prototype_ `void Enter(void);`
- L21 _public prototype_ `void Leave(void);`
- L48 _private member_ `Windows::CRITICAL_SECTION m_cs;` — BEGIN EPIC MOD

#### class `CriticalSection::ScopedLock`  
`class ScopedLock`  
_L23-44_
- L26 _public function_ `explicit ScopedLock(CriticalSection* cs) : m_cs(cs)`
- L32 _public function_ `~ScopedLock(void)`
- L38 _private prototype_ `LC_DISABLE_COPY(ScopedLock);`
- L39 _private prototype_ `LC_DISABLE_MOVE(ScopedLock);`
- L40 _private prototype_ `LC_DISABLE_ASSIGNMENT(ScopedLock);`
- L41 _private prototype_ `LC_DISABLE_MOVE_ASSIGNMENT(ScopedLock);`
- L43 _private member_ `CriticalSection* m_cs;`

### `Source/Developer/Windows/LiveCoding/Private/External/LC_Debugger_Windows.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Debugger`
- L13 _prototype_ `bool IsConnected(void);` (scope `Debugger`)
- L17 _macro_ `#define LC_DEBUGGER_BREAKPOINT() __debugbreak()`

### `Source/Developer/Windows/LiveCoding/Private/External/LC_DuplexPipe.h` (Private)


#### class `DuplexPipe`  
`class DuplexPipe`  
_L16-76_
- L19 _public prototype_ `DuplexPipe(void);`
- L20 _public prototype_ `~DuplexPipe(void);`
- L22 _public prototype_ `void Close(void);`
- L23 _public prototype_ `bool IsValid(void) const volatile;`
- L27 _public function_ `template <typename T> void SendCommandAndWaitForAck(const T& command, const void* payload, size_t payloadSize) const` — send command, synchronous
- L45 _public prototype_ `bool ReceiveHeader(commands::Header* header) const;` — receive command header
- L49 _public function_ `template <typename T> bool ReceiveCommand(T* command, void* payload, size_t payloadSize) const` — receive any command
- L64 _public function_ `void SendAck(void) const` — send acknowledge command
- L71 _protected member_ `HANDLE m_pipe;`
- L74 _private prototype_ `void Send(const void* buffer, size_t size) const;`
- L75 _private prototype_ `bool Read(void* buffer, size_t size) const;`

### `Source/Developer/Windows/LiveCoding/Private/External/LC_DuplexPipeClient.h` (Private)


#### class `DuplexPipeClient`  
`class DuplexPipeClient : public DuplexPipe`  
_L13-17_
- inherits: `DuplexPipe`
- L16 _public prototype_ `bool Connect(const wchar_t* name);`

### `Source/Developer/Windows/LiveCoding/Private/External/LC_EntryPoint.h` (Private)


#### Free symbols / members of external scopes

- L10 _prototype_ `void Startup(Windows::HINSTANCE hInstance);`
- L11 _prototype_ `void Shutdown();`

### `Source/Developer/Windows/LiveCoding/Private/External/LC_Environment.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace environment`
- L15 _prototype_ `void RemoveVariable(const wchar_t* variable);` (scope `environment`) — Removes a variable from the environment of the calling process.
- L18 _prototype_ `void SetVariable(const wchar_t* variable, const wchar_t* value);` (scope `environment`) — Sets a variable in the environment of the calling process.
- L21 _prototype_ `std::wstring GetVariable(const wchar_t* variable, const wchar_t* defaultValue);` (scope `environment`) — Gets a variable from the environment of the calling process.

### `Source/Developer/Windows/LiveCoding/Private/External/LC_Event.h` (Private)


#### class `Event`  
`class Event`  
_L14-49_
- desc: named/unnamed event. acts process-wide if given a name.
- L26 _public prototype_ `Event(const wchar_t* name, Type::Enum type);`
- L27 _public prototype_ `~Event(void);`
- L30 _public prototype_ `void Reset(void);` — Resets the event.
- L33 _public prototype_ `void Signal(void);` — Signals the event.
- L36 _public prototype_ `bool Wait(void);` — Waits until the event becomes signaled, blocking.
- L40 _public prototype_ `bool WaitTimeout(unsigned int milliSeconds);` — Waits until the event becomes signaled, blocking until the timeout is reached. Returns whether the event was signaled.
- L43 _public prototype_ `bool TryWait(void);` — Returns whether the event was signaled, non-blocking.
- L47 _private member_ `Windows::HANDLE m_event;` — BEGIN EPIC MOD

#### struct `Event::Type`  
`struct Type`  
_L17-24_

#### enum `Event::Type::Enum`  
`enum Enum`  
_L19-23_
- L21 _public enumerator_ `MANUAL_RESET`
- L22 _public enumerator_ `AUTO_RESET`

### `Source/Developer/Windows/LiveCoding/Private/External/LC_Executable.h` (Private)


#### struct `executable::Header`  
`struct Header`  
_L26-31_
- L28 _public member_ `uint64_t sizeOnDisk;`
- L29 _public member_ `IMAGE_FILE_HEADER imageHeader;`
- L30 _public member_ `IMAGE_OPTIONAL_HEADER optionalHeader;`

#### struct `executable::ImageSection`  
`struct ImageSection`  
_L35-41_
- L37 _public member_ `uint32_t rva;`
- L38 _public member_ `uint32_t size;`
- L39 _public member_ `uint32_t rawDataRva;`
- L40 _public member_ `uint32_t rawDataSize;`

#### struct `executable::ImageSectionDB`  
`struct ImageSectionDB`  
_L43-46_
- L45 _public member_ `std::vector<ImageSection> sections;`

#### struct `executable::ImportModule`  
`struct ImportModule`  
_L48-51_
- L50 _public member_ `char path[MAX_PATH];`

#### struct `executable::ImportModuleDB`  
`struct ImportModuleDB`  
_L53-56_
- L55 _public member_ `std::vector<ImportModule> modules;`

#### struct `executable::PdbInfo`  
`struct PdbInfo`  
_L58-63_
- L60 _public member_ `char path[MAX_PATH];` — can be an absolute or relative path
- L61 _public member_ `GUID guid;`
- L62 _public member_ `uint32_t age;`

#### struct `std::hash`  
`template <> struct hash<executable::Header>`  
_L129-138_
- L131 _public function_ `inline std::size_t operator()(const executable::Header& header) const`

#### struct `std::equal_to`  
`template <> struct equal_to<executable::Header>`  
_L141-163_
- L143 _public function_ `inline bool operator()(const executable::Header& lhs, const executable::Header& rhs) const`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace executable`
- L21 _typedef_ `typedef uint64_t PreferredBase;` (scope `executable`)
- L33 _typedef_ `typedef Filesystem::MemoryMappedFile Image;` (scope `executable`)
- L66 _prototype_ `Image* OpenImage(const wchar_t* filename, Filesystem::OpenMode::Enum openMode);` (scope `executable`)
- L67 _prototype_ `void CloseImage(Image*& image);` (scope `executable`)
- L69 _prototype_ `void RebaseImage(Image* image, PreferredBase preferredBase);` (scope `executable`)
- L72 _prototype_ `ImageSectionDB* GatherImageSectionDB(const Image* image);` (scope `executable`)
- L73 _prototype_ `void DestroyImageSectionDB(ImageSectionDB* database);` (scope `executable`)
- L75 _prototype_ `ImportModuleDB* GatherImportModuleDB(const Image* image, const ImageSectionDB* imageSections);` (scope `executable`)
- L76 _prototype_ `void DestroyImportModuleDB(ImportModuleDB* database);` (scope `executable`)
- L79 _prototype_ `PdbInfo* GatherPdbInfo(const Image* image, const ImageSectionDB* imageSections);` (scope `executable`) — reads the PDB info stored in the image's debug directories (if available)
- L80 _prototype_ `void DestroyPdbInfo(PdbInfo* pdbInfo);` (scope `executable`)
- L85 _prototype_ `uint32_t GetEntryPointRva(const Image* image);` (scope `executable`) — returns the RVA of the entry point of the image when loaded into memory
- L88 _prototype_ `PreferredBase GetPreferredBase(const Image* image);` (scope `executable`) — returns the preferred address at which the image is to be loaded into memory
- L91 _prototype_ `Header GetHeader(const Image* image);` (scope `executable`) — returns the image's header
- L94 _prototype_ `bool IsValidHeader(const Header& header);` (scope `executable`) — checks whether a header is valid
- L97 _prototype_ `uint32_t GetSize(const Image* image);` (scope `executable`) — returns the size of the image when loaded into memory
- L100 _prototype_ `uint32_t RvaToFileOffset(const ImageSectionDB* database, uint32_t rva);` (scope `executable`) — helper functions
- L102 _prototype_ `void ReadFromFileOffset(const Image* file, uint32_t offset, void* destination, size_t byteCount);` (scope `executable`)
- L103 _prototype_ `void WriteToFileOffset(Image* file, uint32_t offset, const void* source, size_t byteCount);` (scope `executable`)
- L108 _function_ `template <typename T> inline T ReadFromImage(const Image* image, const ImageSectionDB* database, uint32_t rva)` (scope `executable`) — helper function to directly read from an RVA in the given image
- L121 _prototype_ `void CallDllEntryPoint(void* moduleBase, uint32_t entryPointRva);` (scope `executable`)
- L126 _namespace_ `namespace std`

### `Source/Developer/Windows/LiveCoding/Private/External/LC_FilesystemTypes.h` (Private)


#### struct `Filesystem::OpenMode`  
`struct OpenMode`  
_L12-19_

#### enum `Filesystem::OpenMode::Enum`  
`enum Enum`  
_L14-18_
- L16 _public enumerator_ `READ = 0`
- L17 _public enumerator_ `READ_WRITE = 1`

#### struct `Filesystem::DriveType`  
`struct DriveType`  
_L21-32_

#### enum `Filesystem::DriveType::Enum`  
`enum Enum`  
_L23-31_
- L25 _public enumerator_ `UNKNOWN = 0`
- L26 _public enumerator_ `REMOVABLE`
- L27 _public enumerator_ `FIXED`
- L28 _public enumerator_ `REMOTE`
- L29 _public enumerator_ `OPTICAL`
- L30 _public enumerator_ `RAMDISK`

#### struct `Filesystem::PathAttributes`  
`struct PathAttributes`  
_L34-39_
- L36 _public member_ `uint64_t size;`
- L37 _public member_ `uint64_t lastModificationTime;`
- L38 _public member_ `uint32_t flags;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Filesystem`
- L41 _typedef_ `typedef FixedSizeString<wchar_t, MAX_PATH> Path;` (scope `Filesystem`)

### `Source/Developer/Windows/LiveCoding/Private/External/LC_FixedSizeString.h` (Private)


#### class `FixedSizeString`  
`template <typename T, unsigned int N> class FixedSizeString`  
_L13-45_
- L16 _public member_ `static const unsigned int CAPACITY = N;`
- L18 _public prototype_ `FixedSizeString(void);`
- L19 _public prototype_ `explicit FixedSizeString(const T* other);`
- L20 _public prototype_ `FixedSizeString(const FixedSizeString<T, N>& other);`
- L21 _public prototype_ `FixedSizeString(const T* other, unsigned int length);`
- L23 _public prototype_ `FixedSizeString<T, N>& operator=(const FixedSizeString<T, N>& other);`
- L24 _public prototype_ `FixedSizeString<T, N>& operator=(const T* other);`
- L26 _public prototype_ `FixedSizeString<T, N>& operator+=(const FixedSizeString<T, N>& other);`
- L27 _public prototype_ `FixedSizeString<T, N>& operator+=(const T* other);`
- L29 _public prototype_ `FixedSizeString<T, N> ToLower(void) const LC_RESTRICT;`
- L30 _public prototype_ `FixedSizeString<T, N> ToUpper(void) const LC_RESTRICT;`
- L32 _public function_ `inline unsigned int GetLength(void) const`
- L37 _public function_ `inline const T* GetString(void) const`
- L43 _private member_ `unsigned int m_length;`
- L44 _private member_ `T m_data[N];`

### `Source/Developer/Windows/LiveCoding/Private/External/LC_Foundation_Windows.h` (Private)


#### Free symbols / members of external scopes

- L13 _macro_ `#define LC_FILE __FILE__`
- L14 _macro_ `#define LC_LINE __LINE__`
- L15 _macro_ `#define LC_FUNCTION_NAME __FUNCTION__`
- L16 _macro_ `#define LC_FUNCTION_SIGNATURE __FUNCSIG__`
- L18 _macro_ `#define LC_DISABLE_COPY(_name) _name(const _name&) = delete`
- L19 _macro_ `#define LC_DISABLE_MOVE(_name) _name(_name&&) = delete`
- L20 _macro_ `#define LC_DISABLE_ASSIGNMENT(_name) _name& operator=(const _name&) = delete`
- L21 _macro_ `#define LC_DISABLE_MOVE_ASSIGNMENT(_name) _name& operator=(_name&&) = delete`
- L23 _macro_ `#define LC_ALWAYS_INLINE __forceinline`
- L24 _macro_ `#define LC_NEVER_INLINE __declspec(noinline)`
- L26 _macro_ `#define LC_RESTRICT __restrict`
- L27 _macro_ `#define LC_UNUSED(_value) (void)(_value)`
- L30 _macro_ `#define LC_COMPILER_FENCE std::atomic_signal_fence(std::memory_order_acq_rel)` — BEGIN EPIC MOD
- L31 _macro_ `#define LC_MEMORY_FENCE std::atomic_thread_fence(std::memory_order_acq_rel)`

### `Source/Developer/Windows/LiveCoding/Private/External/LC_Hashing.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Hashing`
- L15 _function_ `LC_ALWAYS_INLINE uint32_t Hash32(const void* input, size_t length, uint32_t seed)` (scope `Hashing`)

### `Source/Developer/Windows/LiveCoding/Private/External/LC_HeartBeat.h` (Private)


#### class `HeartBeat`  
`class HeartBeat`  
_L18-35_
- desc: used for communicating heart beats between client and server. can be used by several processes.
- L21 _public prototype_ `HeartBeat(const wchar_t* const processGroupName, Process::Id processId);`
- L22 _public prototype_ `~HeartBeat(void);`
- L25 _public prototype_ `void Store(void);` — stores the current UTC time as heart beat
- L28 _public prototype_ `uint64_t ReadBeatDelta(void) const;` — reads the last stored heart beat and compares it against the current UTC time
- L31 _private prototype_ `uint64_t ReadBeat(void) const;`
- L33 _private member_ `InterprocessMutex* m_mutex;`
- L34 _private member_ `Process::NamedSharedMemory* m_memory;`

### `Source/Developer/Windows/LiveCoding/Private/External/LC_InterprocessMutex.h` (Private)


#### class `InterprocessMutex`  
`class InterprocessMutex`  
_L13-49_
- L16 _public prototype_ `explicit InterprocessMutex(const wchar_t* name);`
- L17 _public prototype_ `~InterprocessMutex(void);`
- L19 _public prototype_ `void Lock(void);`
- L20 _public prototype_ `void Unlock(void);`
- L47 _private member_ `Windows::HANDLE m_mutex;` — BEGIN EPIC MOD

#### class `InterprocessMutex::ScopedLock`  
`class ScopedLock`  
_L22-43_
- L25 _public function_ `explicit ScopedLock(InterprocessMutex* mutex) : m_mutex(mutex)`
- L31 _public function_ `~ScopedLock(void)`
- L37 _private prototype_ `LC_DISABLE_COPY(ScopedLock);`
- L38 _private prototype_ `LC_DISABLE_MOVE(ScopedLock);`
- L39 _private prototype_ `LC_DISABLE_ASSIGNMENT(ScopedLock);`
- L40 _private prototype_ `LC_DISABLE_MOVE_ASSIGNMENT(ScopedLock);`
- L42 _private member_ `InterprocessMutex* m_mutex;`

### `Source/Developer/Windows/LiveCoding/Private/External/LC_Logging.h` (Private)


#### struct `Logging::Channel`  
`struct Channel`  
_L15-25_
- L24 _public member_ `static const unsigned int COUNT = 3u;`

#### enum `Logging::Channel::Enum`  
`enum Enum`  
_L17-22_
- L19 _public enumerator_ `USER`
- L20 _public enumerator_ `DEV`
- L21 _public enumerator_ `TELEMETRY`

#### struct `Logging::Type`  
`struct Type`  
_L27-36_

#### enum `Logging::Type::Enum`  
`enum Enum`  
_L29-35_
- L31 _public enumerator_ `LOG_INFO`
- L32 _public enumerator_ `LOG_WARNING`
- L33 _public enumerator_ `LOG_ERROR`
- L34 _public enumerator_ `LOG_SUCCESS`

#### class `Logging::Indent`  
`class Indent`  
_L40-48_
- desc: RAII helper class for indentation
- L43 _public prototype_ `explicit Indent(Channel::Enum channel);`
- L44 _public prototype_ `~Indent(void);`
- L47 _private member_ `Channel::Enum m_channel;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Logging`
- L50 _prototype_ `void IncrementIndentation(Channel::Enum channel);` (scope `Logging`)
- L51 _prototype_ `void DecrementIndentation(Channel::Enum channel);` (scope `Logging`)
- L52 _prototype_ `const char* GetIndentation(Channel::Enum channel);` (scope `Logging`)
- L55 _prototype_ `template <int Channel, typename T> void LogNoFormat(const T* const buffer);` (scope `Logging`) — logs without any formatting.
- L59 _prototype_ `template <> void LogNoFormat<Channel::Enum::USER>(const wchar_t* const buffer);` (scope `Logging`) — template specializations. USER channel takes wchar_t*, DEV takes char*.
- L62 _prototype_ `void Log(Channel::Enum channel, Type::Enum type, const char* const format, ...);` (scope `Logging`)
- L65 _typedef_ `typedef void (*OutputHandlerType)(Channel::Enum channel, Type::Enum type, const wchar_t* const text);` (scope `Logging`) — BEGIN EPIC MOD - Redirecting log output
- L66 _prototype_ `void SetOutputHandler(OutputHandlerType handler);` (scope `Logging`)
- L70 _prototype_ `void EnableChannel(Channel::Enum channel, bool enabled);` (scope `Logging`) — BEGIN EPIC MOD - Explicit API for log channels
- L74 _macro_ `#define LC_LOG_INDENT_USER const Logging::Indent LC_PP_UNIQUE_NAME(autoIndentUser)(Logging::Channel::USER)`
- L75 _macro_ `#define LC_LOG_INDENT_DEV const Logging::Indent LC_PP_UNIQUE_NAME(autoIndentDev)(Logging::Channel::DEV)`
- L76 _macro_ `#define LC_LOG_INDENT_TELEMETRY const Logging::Indent LC_PP_UNIQUE_NAME(autoIndentTelemetry)(Logging::Channel::TELEMETRY)`
- L79 _macro_ `#define LC_LOG_USER(_format, ...) Logging::Log(Logging::Channel::USER, Logging::Type::LOG_INFO, "%s" _format "\n", Logging::GetIndentation(Logging::Channel::USER), ##__VA_ARGS__)` — BEGIN EPIC MOD - __VA_ARGS__ -> ##__VA_ARGS__
- L80 _macro_ `#define LC_LOG_DEV(_format, ...) Logging::Log(Logging::Channel::DEV, Logging::Type::LOG_INFO, "%s" _format "\n", Logging::GetIndentation(Logging::Channel::DEV), ##__VA_ARGS__)`
- L81 _macro_ `#define LC_LOG_TELEMETRY(_format, ...) Logging::Log(Logging::Channel::TELEMETRY, Logging::Type::LOG_INFO, "%s" _format "\n", Logging::GetIndentation(Logging::Channel::TELEMETRY), ##__VA_ARGS__)`
- L83 _macro_ `#define LC_WARNING_USER(_format, ...) Logging::Log(Logging::Channel::USER, Logging::Type::LOG_WARNING, "%s" _format "\n", Logging::GetIndentation(Logging::Channel::USER), ##__VA_ARGS__)`
- L84 _macro_ `#define LC_WARNING_DEV(_format, ...) Logging::Log(Logging::Channel::DEV, Logging::Type::LOG_WARNING, "WARNING: %s" _format "\n", Logging::GetIndentation(Logging::Channel::DEV), ##__VA_ARGS__)`
- L85 _macro_ `#define LC_WARNING_TELEMETRY(_format, ...) Logging::Log(Logging::Channel::TELEMETRY, Logging::Type::LOG_WARNING, "WARNING: %s" _format "\n", Logging::GetIndentation(Logging::Channel::TELEMETRY), ##__VA_ARGS__)`
- L87 _macro_ `#define LC_ERROR_USER(_format, ...) Logging::Log(Logging::Channel::USER, Logging::Type::LOG_ERROR, "%s" _format "\n", Logging::GetIndentation(Logging::Channel::USER), ##__VA_ARGS__)`
- L88 _macro_ `#define LC_ERROR_DEV(_format, ...) Logging::Log(Logging::Channel::DEV, Logging::Type::LOG_ERROR, "ERROR: %s" _format "\n", Logging::GetIndentation(Logging::Channel::DEV), ##__VA_ARGS__)`
- L89 _macro_ `#define LC_ERROR_TELEMETRY(_format, ...) Logging::Log(Logging::Channel::TELEMETRY, Logging::Type::LOG_ERROR, "ERROR: %s" _format "\n", Logging::GetIndentation(Logging::Channel::TELEMETRY), ##__VA_ARGS__)`
- L91 _macro_ `#define LC_SUCCESS_USER(_format, ...) Logging::Log(Logging::Channel::USER, Logging::Type::LOG_SUCCESS, "%s" _format "\n", Logging::GetIndentation(Logging::Channel::USER), ##__VA_ARGS__)`

### `Source/Developer/Windows/LiveCoding/Private/External/LC_Memory.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace memory`
- L14 _function_ `template <typename T> inline void ReleaseAndNull(T*& instance)` (scope `memory`)
- L25 _function_ `template <typename T> inline void DeleteAndNull(T*& instance)` (scope `memory`)
- L33 _function_ `template <typename T> inline void DeleteAndNullArray(T*& instance)` (scope `memory`)
- L41 _function_ `template <typename T, size_t N> bool Matches(const T(&mem1)[N], const T(&mem2)[N])` (scope `memory`)

### `Source/Developer/Windows/LiveCoding/Private/External/LC_MemoryMappedFile.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Filesystem`
- L15 _prototype_ `MemoryMappedFile* OpenMemoryMappedFile(const wchar_t* path, OpenMode::Enum openMode, bool checkIfCompressed = false);` (scope `Filesystem`)
- L16 _prototype_ `void CloseMemoryMappedFile(MemoryMappedFile*& file);` (scope `Filesystem`)
- L18 _prototype_ `void* GetMemoryMappedFileData(MemoryMappedFile* file);` (scope `Filesystem`)
- L19 _prototype_ `const void* GetMemoryMappedFileData(const MemoryMappedFile* file);` (scope `Filesystem`)
- L21 _prototype_ `uint64_t GetMemoryMappedSize(const MemoryMappedFile* file);` (scope `Filesystem`)
- L22 _prototype_ `uint64_t GetMemoryMappedFileSizeOnDisk(const MemoryMappedFile* file);` (scope `Filesystem`)

### `Source/Developer/Windows/LiveCoding/Private/External/LC_MemoryStream.h` (Private)


#### class `memoryStream::Reader`  
`class Reader`  
_L15-41_
- L18 _public prototype_ `Reader(const void* data, size_t capacity);`
- L20 _public prototype_ `void Read(void* data, size_t size);`
- L23 _public function_ `template <typename T> inline T Read(void)`
- L30 _public prototype_ `void Seek(size_t offset);`
- L33 _private member_ `const void* m_data;`
- L34 _private member_ `size_t m_capacity;`
- L35 _private member_ `size_t m_offset;`
- L37 _private prototype_ `LC_DISABLE_COPY(Reader);`
- L38 _private prototype_ `LC_DISABLE_MOVE(Reader);`
- L39 _private prototype_ `LC_DISABLE_ASSIGNMENT(Reader);`
- L40 _private prototype_ `LC_DISABLE_MOVE_ASSIGNMENT(Reader);`

#### class `memoryStream::Writer`  
`class Writer`  
_L44-77_
- L47 _public prototype_ `explicit Writer(size_t capacity);`
- L48 _public prototype_ `~Writer(void);`
- L50 _public prototype_ `void Write(const void* data, size_t size);`
- L53 _public function_ `template <typename T> inline void Write(const T& data)`
- L58 _public function_ `inline const void* GetData(void) const`
- L63 _public function_ `inline size_t GetSize(void) const`
- L69 _private member_ `char* m_data;`
- L70 _private member_ `size_t m_capacity;`
- L71 _private member_ `size_t m_offset;`
- L73 _private prototype_ `LC_DISABLE_COPY(Writer);`
- L74 _private prototype_ `LC_DISABLE_MOVE(Writer);`
- L75 _private prototype_ `LC_DISABLE_ASSIGNMENT(Writer);`
- L76 _private prototype_ `LC_DISABLE_MOVE_ASSIGNMENT(Writer);`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace memoryStream`

### `Source/Developer/Windows/LiveCoding/Private/External/LC_NamedSharedMemory.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Process`
- L17 _namespace_ `namespace Current` (scope `Process`)
- L20 _prototype_ `bool DoesOwnNamedSharedMemory(const NamedSharedMemory* memory);` (scope `Process::Current`) — Returns whether the named shared memory is owned by the calling process.
- L24 _prototype_ `NamedSharedMemory* CreateNamedSharedMemory(const wchar_t* name, size_t size);` (scope `Process`) — Creates named shared memory.
- L27 _prototype_ `void DestroyNamedSharedMemory(NamedSharedMemory*& memory);` (scope `Process`) — Destroys named shared memory.
- L30 _prototype_ `void ReadNamedSharedMemory(const NamedSharedMemory* memory, void* buffer, size_t size);` (scope `Process`) — Reads from named shared memory into the given buffer.
- L33 _prototype_ `void WriteNamedSharedMemory(NamedSharedMemory* memory, const void* buffer, size_t size);` (scope `Process`) — Writes from the given buffer into named shared memory.
- L37 _function_ `template <typename T> T ReadNamedSharedMemory(const NamedSharedMemory* memory)` (scope `Process`) — Convenience function for reading a value of a certain type from named shared memory.
- L47 _function_ `template <typename T> void WriteNamedSharedMemory(NamedSharedMemory* memory, const T& value)` (scope `Process`) — Convenience function for writing a value of a certain type to named shared memory.

### `Source/Developer/Windows/LiveCoding/Private/External/LC_NamedSharedMemoryTypes.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Process`

### `Source/Developer/Windows/LiveCoding/Private/External/LC_Platform.h` (Private)


#### Free symbols / members of external scopes

- L19 _macro_ `# define LC_64_BIT 1` — 64-bit
- L20 _macro_ `# define LC_32_BIT 0`
- L23 _macro_ `# define LC_64_BIT 0` — 32-bit
- L24 _macro_ `# define LC_32_BIT 1`
- L26 _macro_ `# define LC_PLATFORM_SUFFIX _Windows.h`
- L31 _macro_ `# define LC_PLATFORM_SUFFIX _Orbis.h`
- L44 _macro_ `# define LC_IDENTIFIER(_name) _name`
- L46 _macro_ `# define LC_IDENTIFIER(_name) "_" _name`

### `Source/Developer/Windows/LiveCoding/Private/External/LC_PointerUtil.h` (Private)


#### union `pointer::AlignBottom::(anonymous)`  
``  
_L45-48_

#### union `pointer::AlignTop::(anonymous)`  
``  
_L79-82_

#### union `pointer::As::(anonymous)`  
``  
_L119-122_

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace pointer`
- L17 _prototype_ `template <typename T> T As(void* anyPointer);` (scope `pointer`) — BEGIN EPIC MOD
- L20 _prototype_ `template <typename T> T As(const void* anyPointer);` (scope `pointer`)
- L24 _function_ `template <typename T> T AsInteger(const void* anyPointer)` (scope `pointer`)
- L34 _function_ `template <typename To, typename From> To FromInteger(From integer)` (scope `pointer`)
- L42 _function_ `template <typename T> T AlignBottom(void* anyPointer, size_t alignment)` (scope `pointer`)
- L46 _member_ `void* as_void;` (scope `pointer::AlignBottom::__anonddd8ed57010a`)
- L47 _member_ `uintptr_t as_uintptr_t;` (scope `pointer::AlignBottom::__anonddd8ed57010a`)
- L59 _function_ `template <typename T> T AlignBottom(const void* anyPointer, size_t alignment)` (scope `pointer`)
- L63 _member_ `const void* as_void;` (scope `pointer::AlignBottom::__anonddd8ed57020a`)
- L64 _member_ `uintptr_t as_uintptr_t;` (scope `pointer::AlignBottom::__anonddd8ed57020a`)
- L76 _function_ `template <typename T> T AlignTop(void* anyPointer, size_t alignment)` (scope `pointer`)
- L80 _member_ `void* as_void;` (scope `pointer::AlignTop::__anonddd8ed57030a`)
- L81 _member_ `uintptr_t as_uintptr_t;` (scope `pointer::AlignTop::__anonddd8ed57030a`)
- L94 _function_ `template <typename T> T AlignTop(const void* anyPointer, size_t alignment)` (scope `pointer`)
- L98 _member_ `const void* as_void;` (scope `pointer::AlignTop::__anonddd8ed57040a`)
- L99 _member_ `uintptr_t as_uintptr_t;` (scope `pointer::AlignTop::__anonddd8ed57040a`)
- L112 _function_ `template <typename T> T As(void* anyPointer)` (scope `pointer`)
- L120 _member_ `void* as_void;` (scope `pointer::As::__anonddd8ed57050a`)
- L121 _member_ `T as_T;` (scope `pointer::As::__anonddd8ed57050a`)
- L130 _function_ `template <typename T> T As(const void* anyPointer)` (scope `pointer`)
- L139 _member_ `const void* as_void;` (scope `pointer::As::__anonddd8ed57060a`)
- L140 _member_ `T as_T;` (scope `pointer::As::__anonddd8ed57060a`)
- L149 _function_ `template <typename T, typename U> T Offset(void* anyPointer, U howManyBytes)` (scope `pointer`)
- L158 _function_ `template <typename T, typename U> T Offset(const void* anyPointer, U howManyBytes)` (scope `pointer`)
- L167 _function_ `template <typename T> T Displacement(const void* from, const void* to)` (scope `pointer`)

### `Source/Developer/Windows/LiveCoding/Private/External/LC_Preprocessor.h` (Private)


#### Free symbols / members of external scopes

- L8 _macro_ `#define LC_PP_JOIN_HELPER_HELPER(_0, _1) _0##_1` — joins two tokens, even when the tokens are macros
- L9 _macro_ `#define LC_PP_JOIN_HELPER(_0, _1) LC_PP_JOIN_HELPER_HELPER(_0, _1)`
- L10 _macro_ `#define LC_PP_JOIN(_0, _1) LC_PP_JOIN_HELPER(_0, _1)`
- L13 _macro_ `#define LC_PP_STRINGIFY_HELPER(_0) #_0` — stringifies a token, even when the token is a macro
- L14 _macro_ `#define LC_PP_STRINGIFY(_0) LC_PP_STRINGIFY_HELPER(_0)`
- L17 _macro_ `#define LC_PP_UNIQUE_NAME(_name) LC_PP_JOIN(_name, __COUNTER__)` — generates a unique name

### `Source/Developer/Windows/LiveCoding/Private/External/LC_PrimitiveNames.h` (Private)


#### Free symbols / members of external scopes

- L16 _namespace_ `namespace primitiveNames`
- L19 _prototype_ `std::wstring JobGroup(const std::wstring& processGroupName);` (scope `primitiveNames`) — client
- L20 _prototype_ `std::wstring StartupMutex(const std::wstring& processGroupName);` (scope `primitiveNames`)
- L21 _prototype_ `std::wstring StartupNamedSharedMemory(const std::wstring& processGroupName);` (scope `primitiveNames`)
- L24 _prototype_ `std::wstring ServerReadyEvent(const std::wstring& processGroupName);` (scope `primitiveNames`) — server
- L25 _prototype_ `std::wstring CompilationEvent(const std::wstring& processGroupName);` (scope `primitiveNames`)
- L28 _prototype_ `std::wstring Pipe(const std::wstring& processGroupName);` (scope `primitiveNames`) — pipes
- L29 _prototype_ `std::wstring ExceptionPipe(const std::wstring& processGroupName);` (scope `primitiveNames`)
- L32 _prototype_ `std::wstring HeartBeatMutex(const std::wstring& processGroupName, Process::Id processId);` (scope `primitiveNames`) — heart beat
- L33 _prototype_ `std::wstring HeartBeatNamedSharedMemory(const std::wstring& processGroupName, Process::Id processId);` (scope `primitiveNames`)
- L36 _prototype_ `std::wstring RequestRestart(Process::Id processId);` (scope `primitiveNames`) — restart
- L37 _prototype_ `std::wstring PreparedRestart(Process::Id processId);` (scope `primitiveNames`)
- L38 _prototype_ `std::wstring Restart(Process::Id processId);` (scope `primitiveNames`)

### `Source/Developer/Windows/LiveCoding/Private/External/LC_Process.h` (Private)


#### Free symbols / members of external scopes

- L18 _namespace_ `namespace Process`
- L24 _namespace_ `namespace Current` (scope `Process`)
- L27 _prototype_ `void* GetBase(void);` (scope `Process::Current`) — Returns the base address of the image of the calling process.
- L30 _prototype_ `Handle GetHandle(void);` (scope `Process::Current`) — Returns the process handle of the calling process.
- L33 _prototype_ `Id GetId(void);` (scope `Process::Current`) — Returns the process Id of the calling process.
- L36 _prototype_ `Filesystem::Path GetImagePath(void);` (scope `Process::Current`) — Returns the path to the executable image of the calling process.
- L39 _prototype_ `Filesystem::Path GetWorkingDirectory(void);` (scope `Process::Current`) — returns the working directory of the calling process.
- L42 _prototype_ `std::wstring GetCommandLine(void);` (scope `Process::Current`) — Returns the command line of the calling process.
- L46 _prototype_ `Id GetId(const Context* context);` (scope `Process`) — Returns the underlying process Id for a process identified by the given context.
- L49 _prototype_ `Handle GetHandle(const Context* context);` (scope `Process`) — Returns the underlying process handle for a process identified by the given context.
- L52 _prototype_ `std::wstring GetStdOutData(const Context* context);` (scope `Process`) — Returns the underlying stdout data for a process identified by the given context.
- L56 _prototype_ `Context* Spawn(const wchar_t* exePath, const wchar_t* workingDirectory, const wchar_t* commandLine, const void* environmentBlock, uint32_t flags);` (scope `Process`) — Spawns a new process.
- L59 _prototype_ `void Destroy(Context*& context);` (scope `Process`) — Destroys a spawned process.
- L62 _prototype_ `void ResumeMainThread(Context* context);` (scope `Process`) — Resumes a process that was spawned in a suspended state.
- L65 _prototype_ `unsigned int Wait(Context* context);` (scope `Process`) — Waits until a spawned process has exited.
- L68 _prototype_ `unsigned int Wait(Handle handle);` (scope `Process`) — Waits until the given process has exited.
- L71 _prototype_ `void Terminate(Context* context);` (scope `Process`) — Terminates a spawned process.
- L74 _prototype_ `void Terminate(Handle handle);` (scope `Process`) — Terminates the given process.
- L78 _prototype_ `Handle Open(Id processId);` (scope `Process`) — Opens a process with the given Id for full access.
- L81 _prototype_ `void Close(Handle& handle);` (scope `Process`) — Closes an opened process.
- L85 _prototype_ `void Suspend(Context* context);` (scope `Process`) — Suspends a process.
- L88 _prototype_ `void Suspend(Handle handle);` (scope `Process`) — Suspends a process.
- L91 _prototype_ `void Resume(Context* context);` (scope `Process`) — Resumes a suspended process.
- L94 _prototype_ `void Resume(Handle handle);` (scope `Process`) — Resumes a suspended process.
- L97 _prototype_ `bool IsActive(Handle handle);` (scope `Process`) — Returns whether the given process is still active.
- L100 _prototype_ `bool IsWoW64(Handle handle);` (scope `Process`) — Returns whether the given process runs under Wow64 (32-bit emulation on 64-bit versions of Windows).
- L103 _prototype_ `void ReadProcessMemory(Handle handle, const void* srcAddress, void* destBuffer, size_t size);` (scope `Process`) — Reads from process memory.
- L106 _prototype_ `void WriteProcessMemory(Handle handle, void* destAddress, const void* srcBuffer, size_t size);` (scope `Process`) — Writes to process memory.
- L110 _function_ `template <typename T> T ReadProcessMemory(Handle handle, const void* srcAddress)` (scope `Process`) — Convenience function for reading a value of a certain type from process memory.
- L120 _function_ `template <typename T> void WriteProcessMemory(Handle handle, void* destAddress, const T& value)` (scope `Process`) — Convenience function for writing a value of a certain type to process memory.
- L126 _prototype_ `void* ScanMemoryRange(Handle handle, const void* lowerBound, const void* upperBound, size_t size, size_t alignment);` (scope `Process`) — Scans a region of memory in the given process until a free block of a given size is found. Will only consider blocks at addresses with the given alignment.
- L129 _prototype_ `uint32_t ConvertPageProtectionToExecutableProtection(uint32_t protection);` (scope `Process`) — Converts any combination of page protection flags (e.g. PAGE_NOACCESS, PAGE_GUARD, ...) to protection flags that specify an executable page (e.g. PAGE_EXECUTE).
- L132 _prototype_ `void MakePagesExecutable(Handle handle, void* address, size_t size);` (scope `Process`) — Makes the memory pages in the given region executable (in case they aren't already), while keeping other protection flags intact.
- L135 _prototype_ `void FlushInstructionCache(Handle handle, void* address, size_t size);` (scope `Process`) — Flushes a process's instruction cache.
- L139 _prototype_ `Environment CreateEnvironment(Handle handle);` (scope `Process`) — Reads and reads the environment of a given process.
- L142 _prototype_ `Environment CreateEnvironment(Context* context);` (scope `Process`) — Reads the environment of a process identified by the given context.
- L145 _prototype_ `void DestroyEnvironment(Environment& environment);` (scope `Process`) — Destroys an environment.
- L150 _prototype_ `std::vector<Thread::Id> EnumerateThreads(Id processId);` (scope `Process`) — Enumerates all threads of a process. Only call on suspended processes. BEGIN EPIC MOD
- L155 _prototype_ `std::vector<Module> EnumerateModules(Handle handle);` (scope `Process`) — Enumerates all modules of a process. Only call on suspended processes. BEGIN EPIC MOD
- L159 _prototype_ `Filesystem::Path GetImagePath(Handle handle);` (scope `Process`) — Returns the full path of a process's image, e.g. "C:\Directory\Application.exe".
- L162 _prototype_ `uint32_t GetModuleSize(Handle handle, void* moduleBase);` (scope `Process`) — Returns the size of a module loaded into the virtual address space of a given process.
- L166 _prototype_ `void DumpMemory(Handle handle, const void* address, size_t size);` (scope `Process`) — Dumps any process's memory.
- L169 _prototype_ `Environment* CreateEnvironmentFromMap(const TMap<FString, FString>& Pairs);` (scope `Process`) — BEGIN EPIC MOD - Allow passing environment block for linker

### `Source/Developer/Windows/LiveCoding/Private/External/LC_ProcessTypes.h` (Private)


#### struct `Process::Module`  
`struct Module`  
_L14-19_
- L16 _public member_ `Filesystem::Path fullPath;`
- L17 _public member_ `void* baseAddress;`
- L18 _public member_ `uint32_t sizeOfImage;`

#### struct `Process::Environment`  
`struct Environment`  
_L21-25_
- L23 _public member_ `size_t size;`
- L24 _public member_ `void* data;`

#### struct `Process::SpawnFlags`  
`struct SpawnFlags`  
_L27-36_

#### enum `Process::SpawnFlags::Enum`  
`enum Enum : uint32_t`  
_L29-35_
- L31 _public enumerator_ `NONE = 0u`
- L32 _public enumerator_ `REDIRECT_STDOUT = 1u << 0u`
- L33 _public enumerator_ `NO_WINDOW = 1u << 1u`
- L34 _public enumerator_ `SUSPENDED = 1u << 2u`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Process`
- L38 _typedef_ `typedef StrongTypedef<HANDLE> Handle;` (scope `Process`)
- L39 _typedef_ `typedef StrongTypedef<DWORD> Id;` (scope `Process`)
- L41 _variable_ `static const Handle INVALID_HANDLE = Handle(INVALID_HANDLE_VALUE);` (scope `Process`)

### `Source/Developer/Windows/LiveCoding/Private/External/LC_Restart.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace restart`
- L12 _prototype_ `void Startup(void);` (scope `restart`)
- L13 _prototype_ `void Shutdown(void);` (scope `restart`)
- L15 _prototype_ `int WasRequested(void);` (scope `restart`)
- L16 _prototype_ `void Execute(lpp::RestartBehaviour behaviour, unsigned int exitCode);` (scope `restart`)

### `Source/Developer/Windows/LiveCoding/Private/External/LC_RunMode.h` (Private)


#### struct `RunMode`  
`struct RunMode`  
_L7-16_

#### enum `RunMode::Enum`  
`enum Enum`  
_L9-15_
- L11 _public enumerator_ `DEFAULT`
- L12 _public enumerator_ `EXTERNAL_BUILD_SYSTEM`
- L14 _public enumerator_ `INVALID`

### `Source/Developer/Windows/LiveCoding/Private/External/LC_Semaphore.h` (Private)


#### class `Semaphore`  
`class Semaphore`  
_L11-34_
- L14 _public prototype_ `Semaphore(unsigned int initialValue, unsigned int maximumValue);`
- L15 _public prototype_ `~Semaphore(void);`
- L18 _public prototype_ `void Signal(void);` — Signals the semaphore.
- L21 _public prototype_ `bool Wait(void);` — Waits until the semaphore becomes signaled, blocking.
- L25 _public prototype_ `bool WaitTimeout(unsigned int milliSeconds);` — Waits until the semaphore becomes signaled, blocking until the timeout is reached. Returns whether the semaphore was signaled.
- L28 _public prototype_ `bool TryWait(void);` — Returns whether the semaphore was signaled, non-blocking.
- L32 _private member_ `Windows::HANDLE m_sema;` — BEGIN EPIC MOD

### `Source/Developer/Windows/LiveCoding/Private/External/LC_Shortcut.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace shortcut`
- L14 _prototype_ `int ConvertKeysToShortcut(bool control, bool alt, bool shift, unsigned int virtualKey);` (scope `shortcut`)
- L15 _prototype_ `bool ContainsControl(int shortcutValue);` (scope `shortcut`)
- L16 _prototype_ `bool ContainsAlt(int shortcutValue);` (scope `shortcut`)
- L17 _prototype_ `bool ContainsShift(int shortcutValue);` (scope `shortcut`)
- L18 _prototype_ `int GetVirtualKeyCode(int shortcutValue);` (scope `shortcut`)
- L19 _prototype_ `std::wstring ConvertShortcutToText(int shortcutValue);` (scope `shortcut`)

### `Source/Developer/Windows/LiveCoding/Private/External/LC_StringUtil.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace string`
- L14 _prototype_ `std::wstring ToWideString(const char* utf8Str);` (scope `string`)
- L15 _prototype_ `std::wstring ToWideString(const char* utf8Str, size_t count);` (scope `string`)
- L16 _prototype_ `std::wstring ToWideString(const std::string& str);` (scope `string`)
- L18 _prototype_ `std::string Replace(const std::string& str, const std::string& from, const std::string& to);` (scope `string`)
- L19 _prototype_ `std::wstring Replace(const std::wstring& str, const std::wstring& from, const std::wstring& to);` (scope `string`)
- L20 _prototype_ `std::string ReplaceAll(const std::string& str, const std::string& from, const std::string& to);` (scope `string`)
- L21 _prototype_ `std::wstring ReplaceAll(const std::wstring& str, const std::wstring& from, const std::wstring& to);` (scope `string`)
- L23 _prototype_ `std::string EraseAll(const std::string& str, const std::string& subString);` (scope `string`)
- L24 _prototype_ `std::wstring EraseAll(const std::wstring& str, const std::wstring& subString);` (scope `string`)
- L26 _prototype_ `char* Find(char* str, const char* subString);` (scope `string`)
- L27 _prototype_ `wchar_t* Find(wchar_t* str, const wchar_t* subString);` (scope `string`)
- L29 _prototype_ `const char* Find(const char* str, const char* subString);` (scope `string`)
- L30 _prototype_ `const wchar_t* Find(const wchar_t* str, const wchar_t* subString);` (scope `string`)
- L31 _prototype_ `const wchar_t* Find(const wchar_t* str, size_t strLength, const wchar_t* subString, size_t subStringLength);` (scope `string`)
- L33 _prototype_ `bool Matches(const char* str1, const char* str2);` (scope `string`)
- L34 _prototype_ `bool Matches(const wchar_t* str1, const wchar_t* str2);` (scope `string`)
- L36 _prototype_ `bool Contains(const char* str, const char* subString);` (scope `string`)
- L37 _prototype_ `bool Contains(const wchar_t* str, const wchar_t* subString);` (scope `string`)
- L39 _prototype_ `bool StartsWith(const char* str, const char* subString);` (scope `string`)
- L40 _prototype_ `bool StartsWith(const wchar_t* str, const wchar_t* subString);` (scope `string`)
- L43 _prototype_ `const char* StartsWithEx(const char* str, const char* subString);` (scope `string`) — BEGIN EPIC MOD
- L44 _prototype_ `const wchar_t* StartsWithEx(const wchar_t* str, const wchar_t* subString);` (scope `string`)
- L46 _prototype_ `bool MatchWildcard(const char* target, const char* wildcard);` (scope `string`)
- L47 _prototype_ `bool MatchWildcard(const wchar_t* target, const wchar_t* wildcard);` (scope `string`)
- L50 _function_ `inline char ToLower(char c)` (scope `string`)
- L55 _function_ `inline wchar_t ToLower(wchar_t c)` (scope `string`)
- L60 _function_ `inline char ToUpper(char c)` (scope `string`)
- L65 _function_ `inline wchar_t ToUpper(wchar_t c)` (scope `string`)
- L71 _prototype_ `std::string ToUpper(const char* str);` (scope `string`)
- L72 _prototype_ `std::string ToUpper(const std::string& str);` (scope `string`)
- L73 _prototype_ `std::wstring ToUpper(const wchar_t* str);` (scope `string`)
- L74 _prototype_ `std::wstring ToUpper(const std::wstring& str);` (scope `string`)
- L76 _prototype_ `std::wstring ToLower(const wchar_t* str);` (scope `string`)
- L77 _prototype_ `std::wstring ToLower(const std::wstring& str);` (scope `string`)
- L80 _prototype_ `std::wstring MakeSafeName(const std::wstring& name);` (scope `string`) — Turns invalid characters (\ / : * ? " < > | : ; , .) in file names, names for OS objects, etc. into underscores
- L83 _function_ `inline size_t GetLength(const char* str)` (scope `string`) — Returns the length of the given string without null terminator
- L89 _function_ `inline size_t GetLength(const wchar_t* str)` (scope `string`) — Returns the length of the given string without null terminator
- L97 _function_ `template <typename T> inline T StringToInt(const wchar_t* str)` (scope `string`)
- L103 _function_ `template <typename T> inline std::wstring IntToString(T value)` (scope `string`)

### `Source/Developer/Windows/LiveCoding/Private/External/LC_StrongTypedef.h` (Private)


#### class `StrongTypedef`  
`template <typename T, int TAG = 0> class StrongTypedef`  
_L13-76_
- desc: the tag can be used to create distinct, non-convertible types, even though the underlying type might be compatible.
- L17 _public typedef_ `typedef T Type;` — Typedef to make the underlying type accessible.
- L20 _public function_ `inline StrongTypedef(void) : m_value()` — Default constructor, default initialization.
- L26 _public function_ `inline explicit StrongTypedef(T value) : m_value(value)` — Constructor.
- L32 _public function_ `inline explicit operator T(void) const` — Allows static_cast to value of underlying type.
- L38 _public function_ `inline T operator+(void) const` — Unary promotion operator, similar to built-in types.
- L44 _public function_ `inline bool operator==(StrongTypedef<T> other) const` — Comparison operator.
- L50 _public function_ `inline bool operator!=(StrongTypedef<T> other) const` — Comparison operator.
- L56 _public function_ `inline StrongTypedef<T>& operator=(T value)` — Assignment operator to allow assignment from a value of underlying type.
- L63 _public function_ `T* Access(void)` — Provides read-write access to the underlying value.
- L69 _public function_ `const T* Access(void) const` — Provides read access to the underlying value.
- L75 _private member_ `T m_value;`

#### struct `std::hash`  
`template <typename T> struct hash<StrongTypedef<T>>`  
_L84-90_
- L86 _public function_ `inline std::size_t operator()(StrongTypedef<T> value) const`

#### struct `std::equal_to`  
`template <typename T> struct equal_to<StrongTypedef<T>>`  
_L93-99_
- L95 _public function_ `inline bool operator()(StrongTypedef<T> lhs, StrongTypedef<T> rhs) const`

#### Free symbols / members of external scopes

- L81 _namespace_ `namespace std`

### `Source/Developer/Windows/LiveCoding/Private/External/LC_SyncPoint.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace syncPoint`
- L14 _prototype_ `void Enter(void);` (scope `syncPoint`) — Called when a host process wants to enter the sync point
- L17 _prototype_ `void Leave(void);` (scope `syncPoint`) — Called when a host process wants to leave the sync point
- L20 _prototype_ `void EnterTarget(void);` (scope `syncPoint`) — Called by the LPP API when user code in a target process wants to enter the sync point

### `Source/Developer/Windows/LiveCoding/Private/External/LC_Thread.h` (Private)


#### Free symbols / members of external scopes

- L16 _namespace_ `namespace Thread`
- L19 _namespace_ `namespace Current` (scope `Thread`)
- L22 _prototype_ `void SetName(const char* name);` (scope `Thread::Current`) — Sets the name of the calling thread.
- L25 _prototype_ `void SleepSeconds(unsigned int seconds);` (scope `Thread::Current`) — Sleeps the calling thread for the given number of seconds.
- L28 _prototype_ `void SleepMilliSeconds(unsigned int milliSeconds);` (scope `Thread::Current`) — Sleeps the calling thread for the given number of milliseconds.
- L31 _prototype_ `void Yield(void);` (scope `Thread::Current`) — Yields the calling thread.
- L34 _prototype_ `Id GetId(void);` (scope `Thread::Current`) — Returns the thread Id of the calling thread.
- L38 _prototype_ `Handle Create(unsigned int stackSize, Function function, void* context);` (scope `Thread`) — Creates a raw thread.
- L42 _prototype_ `template <typename F, typename... Args> inline Handle CreateFromFunction(const char* threadName, unsigned int stackSize, F ptrToFunction, Args&&... args);` (scope `Thread`) — Creates a thread from a given function and provided arguments.
- L46 _prototype_ `template <class C, typename F, typename... Args> inline Handle CreateFromMemberFunction(const char* threadName, unsigned int stackSize, C* instance, F ptrToMemberFunction, Args&&... args);` (scope `Thread`) — Creates a thread from a given member function, instance and provided arguments.
- L49 _prototype_ `void Join(Handle handle);` (scope `Thread`) — Joins the given thread.
- L52 _prototype_ `void Terminate(Handle handle);` (scope `Thread`) — Terminates the given thread.
- L56 _prototype_ `Handle Open(Id threadId);` (scope `Thread`) — Opens a thread with the given Id for full access.
- L59 _prototype_ `void Close(Handle& handle);` (scope `Thread`) — Closes a created or opened thread.
- L63 _prototype_ `void Suspend(Handle handle);` (scope `Thread`) — Suspends a thread.
- L66 _prototype_ `void Resume(Handle handle);` (scope `Thread`) — Resumes a suspended thread.
- L69 _prototype_ `void SetPriority(Handle handle, int priority);` (scope `Thread`) — Sets a thread's priority.
- L72 _prototype_ `int GetPriority(Handle handle);` (scope `Thread`) — Returns a thread's priority.
- L75 _prototype_ `void SetContext(Handle handle, const Context* context);` (scope `Thread`) — Sets a thread's context. Only call on suspended threads.
- L78 _prototype_ `Context GetContext(Handle handle);` (scope `Thread`) — Returns a thread's context. Only call on suspended threads.
- L81 _prototype_ `const void* ReadInstructionPointer(const Context* context);` (scope `Thread`) — Reads a thread context's instruction pointer.
- L84 _prototype_ `void WriteInstructionPointer(Context* context, const void* ip);` (scope `Thread`) — Writes a thread context's instruction pointer.
- L88 _prototype_ `Id GetId(Handle handle);` (scope `Thread`) — Returns the thread Id of the given thread.
- L93 _function_ `template <typename F, typename... Args> inline Thread::Handle Thread::CreateFromFunction(const char* threadName, unsigned int stackSize, F ptrToFunction, Args&&... args)` (scope `Thread`)
- L100 _function_ `` (scope `Thread::CreateFromFunction`)
- L107 _typedef_ `typedef decltype(captureLambda) CaptureLambdaType;` (scope `Thread::CreateFromFunction`) — helper to make the following easier to read
- L133 _function_ `template <class C, typename F, typename... Args> inline Thread::Handle Thread::CreateFromMemberFunction(const char* threadName, unsigned int stackSize, C* instance, F ptrToMemberFunction, Args&&... args)` (scope `Thread`)
- L140 _function_ `` (scope `Thread::CreateFromMemberFunction`)
- L147 _typedef_ `typedef decltype(captureLambda) CaptureLambdaType;` (scope `Thread::CreateFromMemberFunction`) — helper to make the following easier to read

### `Source/Developer/Windows/LiveCoding/Private/External/LC_ThreadTypes.h` (Private)


#### Free symbols / members of external scopes

- L16 _namespace_ `namespace Thread`
- L19 _typedef_ `typedef StrongTypedef<Windows::HANDLE> Handle;` (scope `Thread`) — BEGIN EPIC MOD
- L21 _typedef_ `typedef StrongTypedef<DWORD> Id;` (scope `Thread`) — END EPIC MOD
- L22 _typedef_ `typedef StrongTypedef<CONTEXT> Context;` (scope `Thread`)
- L23 _typedef_ `typedef StrongTypedef<unsigned int> ReturnValue;` (scope `Thread`)
- L26 _typedef_ `typedef unsigned int (__stdcall *Function)(void*);` (scope `Thread`) — used internally
- L28 _variable_ `static const Handle INVALID_HANDLE = Handle(INVALID_HANDLE_VALUE);` (scope `Thread`)

### `Source/Developer/Windows/LiveCoding/Private/External/LC_UtcTime.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace utcTime`
- L14 _prototype_ `uint64_t GetCurrent(void);` (scope `utcTime`)

### `Source/Developer/Windows/LiveCoding/Private/External/LC_Vfs.h` (Private)


#### struct `Filesystem::VfsEntry`  
`struct VfsEntry`  
_L14-18_
- L16 _public member_ `std::wstring virtualPath;`
- L17 _public member_ `std::wstring localPath;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Filesystem`
- L19 _prototype_ `void AddVfsEntry(const wchar_t* virtualPath, const wchar_t* localPath);` (scope `Filesystem`)
- L21 _prototype_ `const types::vector<VfsEntry>& GetVfsEntries();` (scope `Filesystem`)
- L23 _prototype_ `std::wstring Devirtualize(const std::wstring& path);` (scope `Filesystem`)
- L25 _prototype_ `const wchar_t* Devirtualize(const wchar_t* path, Path& temp);` (scope `Filesystem`)

### `Source/Developer/Windows/LiveCoding/Private/External/LC_VirtualMemory.h` (Private)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace VirtualMemory`
- L17 _prototype_ `void* Allocate(size_t size);` (scope `VirtualMemory`) — Allocates virtual memory.
- L20 _prototype_ `void Free(void* ptr);` (scope `VirtualMemory`) — Frees virtual memory.
- L23 _prototype_ `void* Allocate(Process::Handle handle, size_t size, PageType::Enum pageType);` (scope `VirtualMemory`) — Allocates virtual memory in the given process.
- L26 _prototype_ `void Free(Process::Handle handle, void* ptr);` (scope `VirtualMemory`) — Frees virtual memory in the given process.
- L30 _prototype_ `uint32_t GetAllocationGranularity(void);` (scope `VirtualMemory`) — Returns the allocation granularity of the virtual memory system.
- L33 _prototype_ `uint32_t GetPageSize(void);` (scope `VirtualMemory`) — Returns the page size used by the virtual memory system.

### `Source/Developer/Windows/LiveCoding/Private/External/LC_VirtualMemoryTypes.h` (Private)


#### struct `VirtualMemory::PageType`  
`struct PageType`  
_L13-20_

#### enum `VirtualMemory::PageType::Enum`  
`enum Enum`  
_L15-19_
- L17 _public enumerator_ `READ_WRITE = PAGE_READWRITE`
- L18 _public enumerator_ `EXECUTE_READ_WRITE = PAGE_EXECUTE_READWRITE`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace VirtualMemory`

### `Source/Developer/Windows/LiveCoding/Private/External/LC_WindowsInternalFunctions.h` (Private)


#### class `WindowsInternals::Function`  
`template <typename T> class Function`  
_L17-17_
- desc: Helper class that allows us to call any function in any Windows DLL, as long as it is exported and we know its signature. Base template.
- L23 _private typedef_ `typedef R (NTAPI *PtrToFunction)(Args...);`
- L26 _public prototype_ `inline Function(const char* moduleName, const char* functionName);`
- L28 _public prototype_ `inline R operator()(Args... args) const;`
- L31 _public prototype_ `inline R ExecNoResultCheck(Args... args) const;` — BEGIN EPIC MODS
- L37 _public function_ `template <typename T> inline void CheckResult(T) const` — Helper for letting us check the result for arbitrary return types. Base template.
- L41 _public function_ `template <> inline void CheckResult(NTSTATUS result) const` — Explicit specialization for NTSTATUS return values.
- L53 _private member_ `const char* m_moduleName;`
- L54 _private member_ `const char* m_functionName;`
- L55 _private member_ `PtrToFunction m_function;`
- L61 _function_ `template <typename R, typename... Args> inline WindowsInternals::Function<R (Args...)>::Function(const char* moduleName, const char* functionName) : m_moduleName(moduleName) , m_functionName(functionName) , m_function(nullptr)`
- L82 _function_ `template <typename R, typename... Args> inline R WindowsInternals::Function<R (Args...)>::operator()(Args... args) const`
- L92 _function_ `template <typename R, typename... Args> inline R WindowsInternals::Function<R(Args...)>::ExecNoResultCheck(Args... args) const` — BEGIN EPIC MODS

#### class `WindowsInternals::Function`  
`template <typename R, typename... Args> class Function<R (Args...)>`  
_L21-56_
- desc: Partial specialization for matching any function signature.
- L23 _private typedef_ `typedef R (NTAPI *PtrToFunction)(Args...);`
- L26 _public prototype_ `inline Function(const char* moduleName, const char* functionName);`
- L28 _public prototype_ `inline R operator()(Args... args) const;`
- L31 _public prototype_ `inline R ExecNoResultCheck(Args... args) const;` — BEGIN EPIC MODS
- L37 _public function_ `template <typename T> inline void CheckResult(T) const` — Helper for letting us check the result for arbitrary return types. Base template.
- L41 _public function_ `template <> inline void CheckResult(NTSTATUS result) const` — Explicit specialization for NTSTATUS return values.
- L53 _private member_ `const char* m_moduleName;`
- L54 _private member_ `const char* m_functionName;`
- L55 _private member_ `PtrToFunction m_function;`
- L61 _function_ `template <typename R, typename... Args> inline WindowsInternals::Function<R (Args...)>::Function(const char* moduleName, const char* functionName) : m_moduleName(moduleName) , m_functionName(functionName) , m_function(nullptr)`
- L82 _function_ `template <typename R, typename... Args> inline R WindowsInternals::Function<R (Args...)>::operator()(Args... args) const`
- L92 _function_ `template <typename R, typename... Args> inline R WindowsInternals::Function<R(Args...)>::ExecNoResultCheck(Args... args) const` — BEGIN EPIC MODS

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace WindowsInternals`
- L102 _prototype_ `extern "C" WindowsInternals::NTSTATUS NtSuspendProcess(HANDLE ProcessHandle)` — These are undocumented functions found in ntdll.dll. We don't call them directly, but use them for "extracting" their signature using decltype.
- L103 _prototype_ `extern "C" WindowsInternals::NTSTATUS NtResumeProcess(HANDLE ProcessHandle)`
- L104 _prototype_ `extern "C" WindowsInternals::NTSTATUS NtReadVirtualMemory(HANDLE ProcessHandle, PVOID BaseAddress, PVOID Buffer, ULONG NumberOfBytesToRead, PULONG NumberOfBytesRead)`
- L105 _prototype_ `extern "C" WindowsInternals::NTSTATUS NtWriteVirtualMemory(HANDLE ProcessHandle, PVOID BaseAddress, PVOID Buffer, ULONG NumberOfBytesToWrite, PULONG NumberOfBytesWritten)`
- L106 _prototype_ `extern "C" WindowsInternals::NTSTATUS NtQuerySystemInformation(WindowsInternals::NT_SYSTEM_INFORMATION_CLASS SystemInformationClass, PVOID SystemInformation, ULONG SystemInformationLength, PULONG ReturnLength)`
- L107 _prototype_ `extern "C" WindowsInternals::NTSTATUS NtQueryInformationProcess(HANDLE ProcessHandle, WindowsInternals::NT_PROCESS_INFORMATION_CLASS ProcessInformationClass, PVOID ProcessInformation, ULONG ProcessInformationLength, PULONG ReturnLength)`
- L108 _prototype_ `extern "C" WindowsInternals::NTSTATUS NtContinue(CONTEXT* ThreadContext, BOOLEAN RaiseAlert)`
- L112 _namespace_ `namespace WindowsInternals`
- L114 _externvar_ `extern Function<decltype(NtSuspendProcess)> NtSuspendProcess;` (scope `WindowsInternals`)
- L115 _externvar_ `extern Function<decltype(NtResumeProcess)> NtResumeProcess;` (scope `WindowsInternals`)
- L116 _externvar_ `extern Function<decltype(NtReadVirtualMemory)> NtReadVirtualMemory;` (scope `WindowsInternals`)
- L117 _externvar_ `extern Function<decltype(NtWriteVirtualMemory)> NtWriteVirtualMemory;` (scope `WindowsInternals`)
- L118 _externvar_ `extern Function<decltype(NtQuerySystemInformation)> NtQuerySystemInformation;` (scope `WindowsInternals`)
- L119 _externvar_ `extern Function<decltype(NtQueryInformationProcess)> NtQueryInformationProcess;` (scope `WindowsInternals`)
- L120 _externvar_ `extern Function<decltype(NtContinue)> NtContinue;` (scope `WindowsInternals`)

### `Source/Developer/Windows/LiveCoding/Private/External/LC_WindowsInternals.h` (Private)


#### enum `WindowsInternals::NT_SYSTEM_INFORMATION_CLASS`  
`enum NT_SYSTEM_INFORMATION_CLASS`  
_L30-33_
- desc: https://www.geoffchappell.com/studies/windows/km/ntoskrnl/api/ex/sysinfo/class.htm found in <winternl.h>
- L32 _public enumerator_ `SystemProcessInformation = 5`

#### struct `WindowsInternals::NT_CLIENT_ID`  
`struct NT_CLIENT_ID`  
_L37-41_
- desc: https://docs.microsoft.com/en-us/openspecs/windows_protocols/ms-tsts/a11e7129-685b-4535-8d37-21d4596ac057 found in <wdm.h> in WDK
- L39 _public member_ `HANDLE UniqueProcess;`
- L40 _public member_ `HANDLE UniqueThread;`

#### struct `WindowsInternals::NT_SYSTEM_THREAD_INFORMATION`  
`struct NT_SYSTEM_THREAD_INFORMATION`  
_L44-57_
- desc: https://docs.microsoft.com/en-us/openspecs/windows_protocols/ms-tsts/e82d73e4-cedb-4077-9099-d58f3459722f
- L46 _public member_ `LARGE_INTEGER KernelTime;`
- L47 _public member_ `LARGE_INTEGER UserTime;`
- L48 _public member_ `LARGE_INTEGER CreateTime;`
- L49 _public member_ `ULONG WaitTime;`
- L50 _public member_ `PVOID StartAddress;`
- L51 _public member_ `NT_CLIENT_ID ClientId;`
- L52 _public member_ `LONG Priority;`
- L53 _public member_ `LONG BasePriority;`
- L54 _public member_ `ULONG ContextSwitches;`
- L55 _public member_ `ULONG ThreadState;`
- L56 _public member_ `ULONG WaitReason;`

#### struct `WindowsInternals::NT_UNICODE_STRING`  
`struct NT_UNICODE_STRING`  
_L61-66_
- desc: https://docs.microsoft.com/en-us/openspecs/windows_protocols/ms-tsts/c90753f2-f9f9-490d-846d-6bdd41eae7f8 found in <winternl.h>
- L63 _public member_ `USHORT Length;`
- L64 _public member_ `USHORT MaximumLength;`
- L65 _public member_ `PWSTR Buffer;`

#### struct `WindowsInternals::NT_UNICODE_STRING32`  
`struct NT_UNICODE_STRING32`  
_L69-74_
- desc: BEGIN EPIC MOD
- L71 _public member_ `USHORT Length;`
- L72 _public member_ `USHORT MaximumLength;`
- L73 _public member_ `ULONG Buffer;`

#### struct `WindowsInternals::NT_ANSI_STRING`  
`struct NT_ANSI_STRING`  
_L76-81_
- L78 _public member_ `USHORT Length;`
- L79 _public member_ `USHORT MaximumLength;`
- L80 _public member_ `PSTR Buffer;`

#### struct `WindowsInternals::NT_ANSI_STRING32`  
`struct NT_ANSI_STRING32`  
_L83-88_
- L85 _public member_ `USHORT Length;`
- L86 _public member_ `USHORT MaximumLength;`
- L87 _public member_ `ULONG Buffer;`

#### struct `WindowsInternals::NT_SYSTEM_PROCESS_INFORMATION`  
`struct NT_SYSTEM_PROCESS_INFORMATION`  
_L93-130_
- desc: https://www.geoffchappell.com/studies/windows/km/ntoskrnl/api/ex/sysinfo/process.htm found in <winternl.h>
- L95 _public member_ `ULONG NextEntryOffset;`
- L96 _public member_ `ULONG NumberOfThreads;`
- L97 _public member_ `LARGE_INTEGER WorkingSetPrivateSize;`
- L98 _public member_ `ULONG HardFaultCount;`
- L99 _public member_ `ULONG NumberOfThreadsHighWatermark;`
- L100 _public member_ `ULONGLONG CycleTime;`
- L101 _public member_ `LARGE_INTEGER CreateTime;`
- L102 _public member_ `LARGE_INTEGER UserTime;`
- L103 _public member_ `LARGE_INTEGER KernelTime;`
- L104 _public member_ `NT_UNICODE_STRING ImageName;`
- L105 _public member_ `LONG BasePriority;`
- L106 _public member_ `PVOID UniqueProcessId;`
- L107 _public member_ `PVOID InheritedFromUniqueProcessId;`
- L108 _public member_ `ULONG HandleCount;`
- L109 _public member_ `ULONG SessionId;`
- L110 _public member_ `ULONG_PTR UniqueProcessKey;`
- L111 _public member_ `ULONG_PTR PeakVirtualSize;`
- L112 _public member_ `ULONG_PTR VirtualSize;`
- L113 _public member_ `ULONG PageFaultCount;`
- L114 _public member_ `ULONG_PTR PeakWorkingSetSize;`
- L115 _public member_ `ULONG_PTR WorkingSetSize;`
- L116 _public member_ `ULONG_PTR QuotaPeakPagedPoolUsage;`
- L117 _public member_ `ULONG_PTR QuotaPagedPoolUsage;`
- L118 _public member_ `ULONG_PTR QuotaPeakNonPagedPoolUsage;`
- L119 _public member_ `ULONG_PTR QuotaNonPagedPoolUsage;`
- L120 _public member_ `ULONG_PTR PagefileUsage;`
- L121 _public member_ `ULONG_PTR PeakPagefileUsage;`
- L122 _public member_ `ULONG_PTR PrivatePageCount;`
- L123 _public member_ `LARGE_INTEGER ReadOperationCount;`
- L124 _public member_ `LARGE_INTEGER WriteOperationCount;`
- L125 _public member_ `LARGE_INTEGER OtherOperationCount;`
- L126 _public member_ `LARGE_INTEGER ReadTransferCount;`
- L127 _public member_ `LARGE_INTEGER WriteTransferCount;`
- L128 _public member_ `LARGE_INTEGER OtherTransferCount;`
- L129 _public member_ `NT_SYSTEM_THREAD_INFORMATION Threads[1];` — variable size data

#### enum `WindowsInternals::NT_PROCESS_INFORMATION_CLASS`  
`enum NT_PROCESS_INFORMATION_CLASS`  
_L133-137_
- desc: https://docs.microsoft.com/en-us/windows/desktop/api/winternl/nf-winternl-ntqueryinformationprocess
- L135 _public enumerator_ `ProcessBasicInformation = 0`
- L136 _public enumerator_ `ProcessWow64Information = 26`

#### struct `WindowsInternals::RLT_DRIVE_LETTER_CURDIR`  
`struct RLT_DRIVE_LETTER_CURDIR`  
_L140-146_
- desc: BEGIN EPIC MOD
- L142 _public member_ `WORD Flags;`
- L143 _public member_ `WORD Length;`
- L144 _public member_ `ULONG TimeStemp;`
- L145 _public member_ `NT_ANSI_STRING DosPath;`

#### struct `WindowsInternals::RLT_DRIVE_LETTER_CURDIR32`  
`struct RLT_DRIVE_LETTER_CURDIR32`  
_L148-154_
- L150 _public member_ `WORD Flags;`
- L151 _public member_ `WORD Length;`
- L152 _public member_ `ULONG TimeStemp;`
- L153 _public member_ `NT_ANSI_STRING32 DosPath;`

#### struct `WindowsInternals::RTL_USER_PROCESS_PARAMETERS`  
`struct RTL_USER_PROCESS_PARAMETERS`  
_L160-173_
- desc: https://docs.microsoft.com/en-us/windows/desktop/api/winternl/ns-winternl-_rtl_user_process_parameters https://www.nirsoft.net/kernel_struct/vista/RTL_USER_PROCESS_PARAMETERS.html found in <winternl.h>
- L162 _public member_ `BYTE Reserved1[16];`
- L163 _public member_ `PVOID Reserved2[10];`
- L164 _public member_ `NT_UNICODE_STRING ImagePathName;`
- L165 _public member_ `NT_UNICODE_STRING CommandLine;`
- L166 _public member_ `PWSTR Environment;`
- L168 _public member_ `ULONG Reserved3[9];` — EPIC BEGIN MOD
- L169 _public member_ `NT_UNICODE_STRING Reserved4[4];`
- L170 _public member_ `RLT_DRIVE_LETTER_CURDIR CurrentDirectories[32];`
- L171 _public member_ `ULONG EnvironmentSize;`

#### struct `WindowsInternals::RTL_USER_PROCESS_PARAMETERS32`  
`struct RTL_USER_PROCESS_PARAMETERS32`  
_L176-186_
- desc: similar to RTL_USER_PROCESS_PARAMETERS, altered to behave as a struct containing 32-bit pointers in a 64-bit environment
- L178 _public member_ `char Reserved[72];`
- L179 _public member_ `ULONG Environment;`
- L181 _public member_ `ULONG Reserved3[9];` — EPIC BEGIN MOD
- L182 _public member_ `NT_UNICODE_STRING32 Reserved4[4];`
- L183 _public member_ `RLT_DRIVE_LETTER_CURDIR32 CurrentDirectories[32];`
- L184 _public member_ `ULONG EnvironmentSize;`

#### struct `WindowsInternals::NT_LDR_DATA_TABLE_ENTRY`  
`struct NT_LDR_DATA_TABLE_ENTRY`  
_L190-205_
- desc: https://www.geoffchappell.com/studies/windows/win32/ntdll/structs/ldr_data_table_entry.htm found in <winternl.h>
- L192 _public member_ `LIST_ENTRY InLoadOrderLinks;`
- L193 _public member_ `LIST_ENTRY InMemoryOrderLinks;`
- L194 _public member_ `LIST_ENTRY InInitializationOrderLinks;`
- L195 _public member_ `PVOID DllBase;`
- L196 _public member_ `PVOID EntryPoint;`
- L197 _public member_ `ULONG SizeOfImage;`
- L198 _public member_ `NT_UNICODE_STRING FullDllName;`
- L199 _public member_ `NT_UNICODE_STRING BaseDllName;`
- L200 _public member_ `ULONG Flags;`
- L201 _public member_ `USHORT LoadCount;`
- L202 _public member_ `USHORT ObsoleteLoadCount;`
- L203 _public member_ `USHORT TlsIndex;`
- L204 _public member_ `LIST_ENTRY HashLinks;`

#### struct `WindowsInternals::NT_PEB_LDR_DATA`  
`struct NT_PEB_LDR_DATA`  
_L209-220_
- desc: https://docs.microsoft.com/en-us/windows/desktop/api/winternl/ns-winternl-_peb_ldr_data https://www.geoffchappell.com/studies/windows/win32/ntdll/structs/peb_ldr_data.htm
- L211 _public member_ `ULONG Length;`
- L212 _public member_ `BOOLEAN Initialized;`
- L213 _public member_ `PVOID SsHandle;`
- L214 _public member_ `LIST_ENTRY InLoadOrderModuleList;`
- L215 _public member_ `LIST_ENTRY InMemoryOrderModuleList;`
- L216 _public member_ `LIST_ENTRY InInitializationOrderModuleList;`
- L217 _public member_ `PVOID EntryInProgress;`
- L218 _public member_ `BOOLEAN ShutdownInProgress;`
- L219 _public member_ `HANDLE ShutdownThreadId;`

#### struct `WindowsInternals::NT_PEB`  
`struct NT_PEB`  
_L226-247_
- desc: https://docs.microsoft.com/en-us/windows/desktop/api/winternl/ns-winternl-_peb
- L228 _public member_ `BYTE Reserved1[2];`
- L229 _public member_ `BYTE BeingDebugged;`
- L230 _public member_ `BYTE Reserved2[1];`
- L231 _public member_ `PVOID Reserved3[2];`
- L232 _public member_ `NT_PEB_LDR_DATA* Ldr;`
- L233 _public member_ `RTL_USER_PROCESS_PARAMETERS* ProcessParameters;`
- L234 _public member_ `PVOID Reserved4[3];`
- L235 _public member_ `PVOID AtlThunkSListPtr;`
- L236 _public member_ `PVOID Reserved5;`
- L237 _public member_ `ULONG Reserved6;`
- L238 _public member_ `PVOID Reserved7;`
- L239 _public member_ `ULONG Reserved8;`
- L240 _public member_ `ULONG AtlThunkSListPtr32;`
- L241 _public member_ `PVOID Reserved9[45];`
- L242 _public member_ `BYTE Reserved10[96];`
- L243 _public member_ `NT_PS_POST_PROCESS_INIT_ROUTINE* PostProcessInitRoutine;`
- L244 _public member_ `BYTE Reserved11[128];`
- L245 _public member_ `PVOID Reserved12[1];`
- L246 _public member_ `ULONG SessionId;`

#### struct `WindowsInternals::NT_PEB32`  
`struct NT_PEB32`  
_L250-254_
- desc: similar to NT_PEB, altered to behave as a struct containing 32-bit pointers in a 64-bit environment
- L252 _public member_ `char Reserved[16];`
- L253 _public member_ `ULONG ProcessParameters32;`

#### struct `WindowsInternals::NT_PROCESS_BASIC_INFORMATION`  
`struct NT_PROCESS_BASIC_INFORMATION`  
_L257-264_
- desc: https://docs.microsoft.com/en-us/windows/desktop/api/winternl/nf-winternl-ntqueryinformationprocess
- L259 _public member_ `PVOID Reserved1;`
- L260 _public member_ `NT_PEB* PebBaseAddress;`
- L261 _public member_ `PVOID Reserved2[2];`
- L262 _public member_ `ULONG_PTR UniqueProcessId;`
- L263 _public member_ `PVOID Reserved3;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define STATUS_INFO_LENGTH_MISMATCH ((WindowsInternals::NTSTATUS)0xC0000004L)` — https://docs.microsoft.com/en-us/openspecs/windows_protocols/ms-erref/87fba13e-bf06-450e-83b1-9241dc81e781 found in <ntstatus.h>
- L16 _macro_ `#define NT_SUCCESS(Status) ((WindowsInternals::NTSTATUS)(Status) >= 0)` — found in <winternl.h>
- L19 _namespace_ `namespace WindowsInternals`
- L26 _typedef_ `typedef LONG NTSTATUS;` (scope `WindowsInternals`) — https://docs.microsoft.com/en-us/openspecs/windows_protocols/ms-erref/87fba13e-bf06-450e-83b1-9241dc81e781
- L223 _typedef_ `typedef VOID (NTAPI *NT_PS_POST_PROCESS_INIT_ROUTINE)(VOID);` (scope `WindowsInternals`) — found in <winternl.h>

### `Source/Developer/Windows/LiveCoding/Private/External/LPP_API.h` (Private)


#### enum `RestartBehaviour`  
`enum RestartBehaviour`  
_L226-235_
- L229 _public enumerator_ `LPP_RESTART_BEHAVIOR_REQUEST_EXIT` — BEGIN EPIC MODS - Use UE codepath for termination to ensure logs are flushed and session analytics are sent
- L231 _public enumerator_ `LPP_RESTART_BEHAVIOUR_DEFAULT_EXIT` — END EPIC MODS
- L232 _public enumerator_ `LPP_RESTART_BEHAVIOUR_EXIT_WITH_FLUSH` — exit()
- L233 _public enumerator_ `LPP_RESTART_BEHAVIOUR_EXIT` — _Exit()
- L234 _public enumerator_ `LPP_RESTART_BEHAVIOUR_INSTANT_TERMINATION` — TerminateProcess

#### Free symbols / members of external scopes

- L12 _macro_ `#define LPP_CONCATENATE_HELPER_HELPER(_a, _b) _a##_b` — concatenates two preprocessor tokens, even when the tokens themselves are macros
- L13 _macro_ `#define LPP_CONCATENATE_HELPER(_a, _b) LPP_CONCATENATE_HELPER_HELPER(_a, _b)`
- L14 _macro_ `#define LPP_CONCATENATE(_a, _b) LPP_CONCATENATE_HELPER(_a, _b)`
- L17 _macro_ `#define LPP_IDENTIFIER(_identifier) LPP_CONCATENATE(_identifier, __LINE__)` — generates a unique identifier inside a translation unit
- L20 _macro_ `#define LPP_PREPATCH_SECTION ".lpp_prepatch_hooks"` — custom section names for hooks
- L21 _macro_ `#define LPP_POSTPATCH_SECTION ".lpp_postpatch_hooks"`
- L22 _macro_ `#define LPP_COMPILE_START_SECTION ".lpp_compile_start_hooks"`
- L23 _macro_ `#define LPP_COMPILE_SUCCESS_SECTION ".lpp_compile_success_hooks"`
- L24 _macro_ `#define LPP_COMPILE_ERROR_SECTION ".lpp_compile_error_hooks"`
- L25 _macro_ `#define LPP_COMPILE_ERROR_MESSAGE_SECTION ".lpp_compile_error_message_hooks"`
- L27 _macro_ `#define LPP_PRECOMPILE_SECTION ".lpp_precompile_hooks"` — BEGIN EPIC MOD - Add the ability for pre and post compile notifications
- L28 _macro_ `#define LPP_POSTCOMPILE_SECTION ".lpp_postcompile_hooks"`
- L32 _macro_ `#define LPP_PREPATCH_HOOK(_function) \` — register a pre-patch hook in a custom section
- L37 _macro_ `#define LPP_POSTPATCH_HOOK(_function) \` — register a post-patch hook in a custom section
- L42 _macro_ `#define LPP_COMPILE_START_HOOK(_function) \` — register a compile start hook in a custom section
- L47 _macro_ `#define LPP_COMPILE_SUCCESS_HOOK(_function) \` — register a compile success hook in a custom section
- L52 _macro_ `#define LPP_COMPILE_ERROR_HOOK(_function) \` — register a compile error hook in a custom section
- L57 _macro_ `#define LPP_COMPILE_ERROR_MESSAGE_HOOK(_function) \` — register a compile error message hook in a custom section
- L64 _macro_ `#define LPP_PRECOMPILE_HOOK(_function) \` — BEGIN EPIC MOD - Add the ability for pre and post compile notifications register a pre-compile hook in a custom section
- L69 _macro_ `#define LPP_POSTCOMPILE_HOOK(_function) \` — register a post-compile hook in a custom section
- L79 _macro_ `# define LPP_NS_BEGIN namespace lpp {`
- L80 _macro_ `# define LPP_NS_END }`
- L81 _macro_ `# define LPP_API inline`
- L82 _macro_ `# define LPP_CAST(_type) reinterpret_cast<_type>`
- L83 _macro_ `# define LPP_NULL nullptr`
- L85 _macro_ `# define LPP_NS_BEGIN`
- L86 _macro_ `# define LPP_NS_END`
- L87 _macro_ `# define LPP_API static inline`
- L88 _macro_ `# define LPP_CAST(_type) (_type)`
- L89 _macro_ `# define LPP_NULL NULL`
- L93 _macro_ `#define LPP_CALL1(_module, _functionName, _returnType, _args1) (LPP_CAST(_returnType (__cdecl*)(_args1))(LPP_CAST(uintptr_t)(GetProcAddress(_module, _functionName))))` — helper macros to call a function in a DLL with an arbitrary signature without a compiler warning
- L94 _macro_ `#define LPP_CALL2(_module, _functionName, _returnType, _args1, _args2) (LPP_CAST(_returnType (__cdecl*)(_args1, _args2))(LPP_CAST(uintptr_t)(GetProcAddress(_module, _functionName))))`
- L95 _macro_ `#define LPP_CALL3(_module, _functionName, _returnType, _args1, _args2, _args3) (LPP_CAST(_returnType (__cdecl*)(_args1, _args2, _args3))(LPP_CAST(uintptr_t)(GetProcAddress(_module, _functionName))))`
- L96 _macro_ `#define LPP_CALL4(_module, _functionName, _returnType, _args1, _args2, _args3, _args4) (LPP_CAST(_returnType (__cdecl*)(_args1, _args2, _args3, _args4))(LPP_CAST(uintptr_t)(GetProcAddress(_module, _functionName))))`
- L109 _macro_ `#define LPP_VERSION "1.6.10"` — version string
- L113 _macro_ `# define LPP_ENABLE_OPTIMIZATIONS _Pragma("clang optimize on")`
- L114 _macro_ `# define LPP_DISABLE_OPTIMIZATIONS _Pragma("clang optimize off")`
- L116 _macro_ `# define LPP_ENABLE_OPTIMIZATIONS __pragma(optimize("", on))`
- L117 _macro_ `# define LPP_DISABLE_OPTIMIZATIONS __pragma(optimize("", off))`

### `Source/Developer/Windows/LiveCoding/Private/External/xxh3.h` (Private)


#### enum `(anonymous)`  
`typedef enum`  
_L896-896_

#### Free symbols / members of external scopes

- L44 _macro_ `#define XXH3_H_1397135465`
- L50 _macro_ `# define XXH_INLINE_ALL` — #  undef XXH_INLINE_ALL     avoid redefinition
- L58 _macro_ `# define XXH_RESTRICT restrict` — #if defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L     >= C99
- L61 _macro_ `# define XXH_RESTRICT /* disable */` — Note: it might be useful to define __restrict or __restrict__ for some C++ compilers
- L67 _macro_ `# define XXH_likely(x) __builtin_expect(x, 1)`
- L68 _macro_ `# define XXH_unlikely(x) __builtin_expect(x, 0)`
- L70 _macro_ `# define XXH_likely(x) (x)`
- L71 _macro_ `# define XXH_unlikely(x) (x)`
- L80 _macro_ `# define inline __inline__ /* clang bug */`
- L161 _macro_ `#define XXH_SCALAR 0 /* Portable scalar version */` — Vectorization detection
- L162 _macro_ `#define XXH_SSE2 1 /* SSE2 for Pentium 4 and all x86_64 */` — #define XXH_SCALAR 0   Portable scalar version
- L163 _macro_ `#define XXH_AVX2 2 /* AVX2 for Haswell and Bulldozer */` — #define XXH_SSE2   1   SSE2 for Pentium 4 and all x86_64
- L164 _macro_ `#define XXH_NEON 3 /* NEON for most ARMv7-A and all AArch64 */` — #define XXH_AVX2   2   AVX2 for Haswell and Bulldozer
- L165 _macro_ `#define XXH_VSX 4 /* VSX and ZVector for POWER8/z13 */` — #define XXH_NEON   3   NEON for most ARMv7-A and all AArch64
- L169 _macro_ `# define XXH_VECTOR XXH_AVX2`
- L171 _macro_ `# define XXH_VECTOR XXH_SSE2`
- L176 _macro_ `# define XXH_VECTOR XXH_NEON`
- L180 _macro_ `# define XXH_VECTOR XXH_VSX` — && defined(__GNUC__)   TODO: IBM XL
- L182 _macro_ `# define XXH_VECTOR XXH_SCALAR`
- L192 _macro_ `# define XXH_ACC_ALIGN 8` — #  if XXH_VECTOR == XXH_SCALAR    scalar
- L194 _macro_ `# define XXH_ACC_ALIGN 16` — #  elif XXH_VECTOR == XXH_SSE2    sse2
- L196 _macro_ `# define XXH_ACC_ALIGN 32` — #  elif XXH_VECTOR == XXH_AVX2    avx2
- L317 _macro_ `# define XXH_SPLIT_IN_PLACE(in, outLo, outHi) \`
- L352 _typedef_ `typedef __vector unsigned long long xxh_u64x2;`
- L353 _typedef_ `typedef __vector unsigned char xxh_u8x16;`
- L354 _typedef_ `typedef __vector unsigned xxh_u32x4;`
- L359 _macro_ `# define XXH_VSX_BE 1`
- L364 _macro_ `# define XXH_VSX_BE 0`
- L371 _macro_ `# define XXH_vec_revb vec_revb`
- L373 _function_ `XXH_FORCE_INLINE xxh_u64x2 XXH_vec_revb(xxh_u64x2 val)`
- L385 _function_ `XXH_FORCE_INLINE xxh_u64x2 XXH_vec_loadu(const void *ptr)` — Performs an unaligned load and byte swaps it on big endian.
- L403 _macro_ `# define XXH_vec_mulo vec_mulo` — s390x is always big endian, no issue on this platform
- L404 _macro_ `# define XXH_vec_mule vec_mule`
- L407 _macro_ `# define XXH_vec_mulo __builtin_altivec_vmulouw` — Clang has a better way to control this, we can just use the builtin which doesn't swap.
- L408 _macro_ `# define XXH_vec_mule __builtin_altivec_vmuleuw`
- L412 _function_ `XXH_FORCE_INLINE xxh_u64x2 XXH_vec_mulo(xxh_u32x4 a, xxh_u32x4 b)` — Adapted from https://github.com/google/highwayhash/blob/master/highwayhash/hh_vsx.h.
- L418 _function_ `XXH_FORCE_INLINE xxh_u64x2 XXH_vec_mule(xxh_u32x4 a, xxh_u32x4 b)`
- L431 _macro_ `# define XXH_PREFETCH(ptr) (void)(ptr) /* disabled */`
- L435 _macro_ `# define XXH_PREFETCH(ptr) _mm_prefetch((const char*)(ptr), _MM_HINT_T0)` — #    include <mmintrin.h>     https://msdn.microsoft.com/fr-fr/library/84szxsww(v=vs.90).aspx
- L437 _macro_ `# define XXH_PREFETCH(ptr) __builtin_prefetch((ptr), 0 /* rw==read */, 3 /* locality */)`
- L448 _macro_ `#define XXH_SECRET_DEFAULT_SIZE 192 /* minimum XXH3_SECRET_SIZE_MIN */`
- L489 _macro_ `# define XXH_mult32to64(x, y) __emulu((unsigned)(x), (unsigned)(y))`
- L498 _macro_ `# define XXH_mult32to64(x, y) ((xxh_u64)(xxh_u32)(x) * (xxh_u64)(xxh_u32)(y))` — Downcast + upcast is usually better than masking on older compilers like GCC 4.2 (especially 32-bit ones), all without affecting newer compilers. The other method, (x & 0xFFFFFFFF) * (y & 0xFFFFFFFF), will AND both operands and perform a full 64x64 multiply -- entirely redundant on 32-bit.
- L507 _function_ `XXH_mult64to128(xxh_u64 lhs, xxh_u64 rhs)`
- L616 _function_ `XXH3_mul128_fold64(xxh_u64 lhs, xxh_u64 rhs)`
- L623 _function_ `XXH_FORCE_INLINE xxh_u64 XXH_xorshift64(xxh_u64 v64, int shift)` — Seems to produce slightly better code on GCC for some reason.
- L634 _function_ `static XXH64_hash_t XXH3_avalanche(xxh_u64 h64)` — We don't need to (or want to) mix as much as XXH64. Short hashes are more evenly distributed, so it isn't necessary.
- L677 _function_ `XXH3_len_1to3_64b(const xxh_u8* input, size_t len, const xxh_u8* secret, XXH64_hash_t seed)`
- L699 _function_ `XXH3_len_4to8_64b(const xxh_u8* input, size_t len, const xxh_u8* secret, XXH64_hash_t seed)`
- L720 _function_ `XXH3_len_9to16_64b(const xxh_u8* input, size_t len, const xxh_u8* secret, XXH64_hash_t seed)`
- L737 _function_ `XXH3_len_0to16_64b(const xxh_u8* input, size_t len, const xxh_u8* secret, XXH64_hash_t seed)`
- L773 _function_ `XXH_FORCE_INLINE xxh_u64 XXH3_mix16B(const xxh_u8* XXH_RESTRICT input, const xxh_u8* XXH_RESTRICT secret, xxh_u64 seed64)` — DISCLAIMER: There are known *seed-dependent* multicollisions here due to multiplication by zero, affecting hashes of lengths 17 to 240. However, they are very unlikely. Keep this in mind when using the unseeded XXH3_64bits() variant: As with all unseeded non-cryptographic hashes, it does not attempt to defend itself against specially crafted inputs, only random inputs. Compared to classic UMAC where a 1 in 2^31 chance of 4 consecutive bytes cancelling out the secret is taken an arbitrary number of times (addressed in XXH3_accumulate_512), this collision is very unlikely with random inputs and/or proper seeding: This only has a 1 in 2^63 chance of 8 consecutive bytes cancelling out, in a function that is only called up to 16 times per hash with up to 240 bytes of input. This is not too bad for a non-cryptographic hash function, especially with only 64 bit outputs. The 128-bit variant (which trades some speed for strength) is NOT affected by this, although it is always a good idea to use a proper seed if you care about strength.
- L807 _function_ `XXH3_len_17to128_64b(const xxh_u8* XXH_RESTRICT input, size_t len, const xxh_u8* XXH_RESTRICT secret, size_t secretSize, XXH64_hash_t seed)`
- L834 _macro_ `#define XXH3_MIDSIZE_MAX 240`
- L837 _function_ `XXH3_len_129to240_64b(const xxh_u8* XXH_RESTRICT input, size_t len, const xxh_u8* XXH_RESTRICT secret, size_t secretSize, XXH64_hash_t seed)`
- L844 _macro_ `#define XXH3_MIDSIZE_STARTOFFSET 3`
- L845 _macro_ `#define XXH3_MIDSIZE_LASTOFFSET 17`
- L892 _macro_ `#define STRIPE_LEN 64`
- L893 _macro_ `#define XXH_SECRET_CONSUME_RATE 8 /* nb of secret bytes consumed at each accumulation */`
- L894 _macro_ `#define ACC_NB (STRIPE_LEN / sizeof(xxh_u64))` — #define XXH_SECRET_CONSUME_RATE 8     nb of secret bytes consumed at each accumulation
- L896 _enumerator_ `typedef enum { XXH3_acc_64bits, XXH3_acc_128bits } XXH3_accWidth_e; /* * XXH3_accumulate_512 is the tightest loop for long inputs` (scope `__anon6185ba150103`)
- L896 _enumerator_ `typedef enum { XXH3_acc_64bits, XXH3_acc_128bits } XXH3_accWidth_e; /* * XXH3_accumulate_512 is the tightest loop for long inputs` (scope `__anon6185ba150103`)
- L896 _typedef_ `typedef enum { XXH3_acc_64bits, XXH3_acc_128bits } XXH3_accWidth_e;`
- L921 _function_ `XXH3_accumulate_512( void* XXH_RESTRICT acc, const void* XXH_RESTRICT input, const void* XXH_RESTRICT secret, XXH3_accWidth_e accWidth)`
- L1111 _function_ `XXH3_scrambleAcc(void* XXH_RESTRICT acc, const void* XXH_RESTRICT secret)`
- L1264 _macro_ `#define XXH_PREFETCH_DIST 384`
- L1272 _function_ `XXH3_accumulate( xxh_u64* XXH_RESTRICT acc, const xxh_u8* XXH_RESTRICT input, const xxh_u8* XXH_RESTRICT secret, size_t nbStripes, XXH3_accWidth_e accWidth)`
- L1290 _function_ `XXH3_hashLong_internal_loop( xxh_u64* XXH_RESTRICT acc, const xxh_u8* XXH_RESTRICT input, size_t len, const xxh_u8* XXH_RESTRICT secret, size_t secretSize, XXH3_accWidth_e accWidth)`
- L1318 _macro_ `#define XXH_SECRET_LASTACC_START 7` — Do not align on 8, so that the secret is different from the scrambler
- L1324 _function_ `XXH3_mix2Accs(const xxh_u64* XXH_RESTRICT acc, const xxh_u8* XXH_RESTRICT secret)`
- L1332 _function_ `XXH3_mergeAccs(const xxh_u64* XXH_RESTRICT acc, const xxh_u8* XXH_RESTRICT secret, xxh_u64 start)`
- L1344 _macro_ `#define XXH3_INIT_ACC { PRIME32_3, PRIME64_1, PRIME64_2, PRIME64_3, \`
- L1348 _function_ `XXH3_hashLong_internal(const xxh_u8* XXH_RESTRICT input, size_t len, const xxh_u8* XXH_RESTRICT secret, size_t secretSize)`
- L1358 _macro_ `#define XXH_SECRET_MERGEACCS_START 11` — do not align on 8, so that the secret is different from the accumulator
- L1368 _function_ `XXH3_hashLong_64b_defaultSecret(const xxh_u8* XXH_RESTRICT input, size_t len)`
- L1378 _function_ `XXH3_hashLong_64b_withSecret(const xxh_u8* XXH_RESTRICT input, size_t len, const xxh_u8* XXH_RESTRICT secret, size_t secretSize)`
- L1385 _function_ `XXH_FORCE_INLINE void XXH_writeLE64(void* dst, xxh_u64 v64)`
- L1394 _function_ `XXH_FORCE_INLINE void XXH3_initCustomSecret(xxh_u8* customSecret, xxh_u64 seed64)` — XXH3_initCustomSecret() : destination `customSecret` is presumed allocated and same size as `kSecret`.
- L1420 _function_ `XXH3_hashLong_64b_withSeed(const xxh_u8* input, size_t len, XXH64_hash_t seed)`
- L1430 _function_ `XXH64_hash_t XXH3_64bits(const void* input, size_t len)`
- L1439 _function_ `XXH3_64bits_withSecret(const void* input, size_t len, const void* secret, size_t secretSize)`
- L1455 _function_ `XXH3_64bits_withSeed(const void* input, size_t len, XXH64_hash_t seed)`
- L1465 _function_ `XXH3_state_t* XXH3_createState(void)`
- L1470 _function_ `XXH_errorcode XXH3_freeState(XXH3_state_t* statePtr)`
- L1477 _function_ `XXH3_copyState(XXH3_state_t* dst_state, const XXH3_state_t* src_state)`
- L1483 _function_ `XXH3_64bits_reset_internal(XXH3_state_t* statePtr, XXH64_hash_t seed, const xxh_u8* secret, size_t secretSize)`
- L1506 _function_ `XXH3_64bits_reset(XXH3_state_t* statePtr)`
- L1514 _function_ `XXH3_64bits_reset_withSecret(XXH3_state_t* statePtr, const void* secret, size_t secretSize)`
- L1524 _function_ `XXH3_64bits_reset_withSeed(XXH3_state_t* statePtr, XXH64_hash_t seed)`
- L1534 _function_ `XXH3_consumeStripes( xxh_u64* acc, XXH32_hash_t* nbStripesSoFarPtr, XXH32_hash_t nbStripesPerBlock, const xxh_u8* input, size_t totalStripes, const xxh_u8* secret, size_t secretLimit, XXH3_accWidth_e accWidth)`
- L1558 _function_ `XXH3_update(XXH3_state_t* state, const xxh_u8* input, size_t len, XXH3_accWidth_e accWidth)`
- L1578 _macro_ `#define XXH3_INTERNALBUFFER_STRIPES (XXH3_INTERNALBUFFER_SIZE / STRIPE_LEN)`
- L1620 _function_ `XXH3_64bits_update(XXH3_state_t* state, const void* input, size_t len)`
- L1627 _function_ `XXH3_digest_long (XXH64_hash_t* acc, const XXH3_state_t* state, XXH3_accWidth_e accWidth)`
- L1661 _function_ `XXH64_hash_t XXH3_64bits_digest (const XXH3_state_t* state)`
- L1679 _function_ `XXH3_len_1to3_128b(const xxh_u8* input, size_t len, const xxh_u8* secret, XXH64_hash_t seed)`
- L1706 _function_ `XXH3_len_4to8_128b(const xxh_u8* input, size_t len, const xxh_u8* secret, XXH64_hash_t seed)`
- L1733 _function_ `XXH3_len_9to16_128b(const xxh_u8* input, size_t len, const xxh_u8* secret, XXH64_hash_t seed)`
- L1807 _function_ `XXH3_len_0to16_128b(const xxh_u8* input, size_t len, const xxh_u8* secret, XXH64_hash_t seed)`
- L1826 _function_ `XXH128_mix32B(XXH128_hash_t acc, const xxh_u8* input_1, const xxh_u8* input_2, const xxh_u8* secret, XXH64_hash_t seed)`
- L1837 _function_ `XXH3_len_17to128_128b(const xxh_u8* XXH_RESTRICT input, size_t len, const xxh_u8* XXH_RESTRICT secret, size_t secretSize, XXH64_hash_t seed)`
- L1866 _function_ `XXH3_len_129to240_128b(const xxh_u8* XXH_RESTRICT input, size_t len, const xxh_u8* XXH_RESTRICT secret, size_t secretSize, XXH64_hash_t seed)`
- L1899 _function_ `XXH3_hashLong_128b_internal(const xxh_u8* XXH_RESTRICT input, size_t len, const xxh_u8* XXH_RESTRICT secret, size_t secretSize)`
- L1921 _function_ `XXH3_hashLong_128b_defaultSecret(const xxh_u8* input, size_t len)`
- L1931 _function_ `XXH3_hashLong_128b_withSecret(const xxh_u8* input, size_t len, const xxh_u8* secret, size_t secretSize)`
- L1942 _function_ `XXH3_hashLong_128b_withSeed(const xxh_u8* input, size_t len, XXH64_hash_t seed)`
- L1951 _function_ `XXH128_hash_t XXH3_128bits(const void* input, size_t len)`
- L1960 _function_ `XXH3_128bits_withSecret(const void* input, size_t len, const void* secret, size_t secretSize)`
- L1976 _function_ `XXH3_128bits_withSeed(const void* input, size_t len, XXH64_hash_t seed)`
- L1985 _function_ `XXH128(const void* input, size_t len, XXH64_hash_t seed)`
- L1998 _function_ `XXH3_128bits_reset_internal(XXH3_state_t* statePtr, XXH64_hash_t seed, const xxh_u8* secret, size_t secretSize)`
- L2006 _function_ `XXH3_128bits_reset(XXH3_state_t* statePtr)`
- L2014 _function_ `XXH3_128bits_reset_withSecret(XXH3_state_t* statePtr, const void* secret, size_t secretSize)`
- L2024 _function_ `XXH3_128bits_reset_withSeed(XXH3_state_t* statePtr, XXH64_hash_t seed)`
- L2034 _function_ `XXH3_128bits_update(XXH3_state_t* state, const void* input, size_t len)`
- L2039 _function_ `XXH128_hash_t XXH3_128bits_digest (const XXH3_state_t* state)`
- L2062 _function_ `int XXH128_isEqual(XXH128_hash_t h1, XXH128_hash_t h2)` — return : 1 is equal, 0 if different
- L2072 _function_ `int XXH128_cmp(const void* h128_1, const void* h128_2)` — This prototype is compatible with stdlib's qsort(). return : >0 if *h128_1  > *h128_2 <0 if *h128_1  < *h128_2 =0 if *h128_1 == *h128_2
- L2085 _function_ `XXH128_canonicalFromHash(XXH128_canonical_t* dst, XXH128_hash_t hash)`
- L2097 _function_ `XXH128_hashFromCanonical(const XXH128_canonical_t* src)`

### `Source/Developer/Windows/LiveCoding/Private/External/xxhash.h` (Private)


#### enum `(anonymous)`  
`typedef enum`  
_L239-239_
- desc: #include <stddef.h>     size_t

#### struct `(anonymous)`  
`typedef struct`  
_L327-327_

#### struct `(anonymous)`  
`typedef struct`  
_L367-367_
- desc: Canonical representation

#### struct `XXH32_state_s`  
`struct XXH32_state_s`  
_L394-404_
- L395 _public member_ `XXH32_hash_t total_len_32;`
- L396 _public member_ `XXH32_hash_t large_len;`
- L397 _public member_ `XXH32_hash_t v1;`
- L398 _public member_ `XXH32_hash_t v2;`
- L399 _public member_ `XXH32_hash_t v3;`
- L400 _public member_ `XXH32_hash_t v4;`
- L401 _public member_ `XXH32_hash_t mem32[4];`
- L402 _public member_ `XXH32_hash_t memsize;`
- L403 _public member_ `XXH32_hash_t reserved;`

#### struct `XXH64_state_s`  
`struct XXH64_state_s`  
_L409-419_
- L410 _public member_ `XXH64_hash_t total_len;`
- L411 _public member_ `XXH64_hash_t v1;`
- L412 _public member_ `XXH64_hash_t v2;`
- L413 _public member_ `XXH64_hash_t v3;`
- L414 _public member_ `XXH64_hash_t v4;`
- L415 _public member_ `XXH64_hash_t mem64[4];`
- L416 _public member_ `XXH32_hash_t memsize;`
- L417 _public member_ `XXH32_hash_t reserved32;`
- L418 _public member_ `XXH64_hash_t reserved64;` — XXH32_hash_t reserved32;    required for padding anyway

#### struct `XXH3_state_s`  
`struct XXH3_state_s`  
_L544-561_
- L550 _public member_ `XXH32_hash_t bufferedSize;`
- L551 _public member_ `XXH32_hash_t nbStripesPerBlock;`
- L552 _public member_ `XXH32_hash_t nbStripesSoFar;`
- L553 _public member_ `XXH32_hash_t secretLimit;`
- L554 _public member_ `XXH32_hash_t reserved32;`
- L555 _public member_ `XXH32_hash_t reserved32_2;`
- L556 _public member_ `XXH64_hash_t totalLen;`
- L557 _public member_ `XXH64_hash_t seed;`
- L558 _public member_ `XXH64_hash_t reserved64;`
- L560 _public member_ `const unsigned char* secret;` — note: there is some padding after due to alignment on 64 bytes

#### struct `(anonymous)`  
`typedef struct`  
_L620-623_

#### struct `(anonymous)`  
`typedef struct`  
_L659-659_
- desc: Canonical representation

#### union `(anonymous)`  
`typedef union`  
_L924-924_
- desc: __pack instructions are safer but compiler specific, hence potentially problematic for some compilers. Currently only defined for GCC and ICC.

#### enum `(anonymous)`  
`typedef enum`  
_L944-944_
- desc: Endianess   ***

#### union `XXH_isLittleEndian::(anonymous)`  
`const union`  
_L973-973_
- desc: Nonstandard, but well-defined behavior in practice. Don't use static: it is detrimental to performance.

#### enum `(anonymous)`  
`typedef enum`  
_L1023-1023_
- desc: Memory reads

#### Free symbols / members of external scopes

- L75 _macro_ `#define XXH_FORCE_MEMORY_ACCESS 2` — MM: tuning
- L76 _macro_ `#define XXH_FORCE_ALIGN_CHECK 0`
- L77 _macro_ `#define XXH_CPU_LITTLE_ENDIAN 1`
- L78 _macro_ `#define XXH_INLINE_ALL`
- L106 _macro_ `# define XXH_INLINE_ALL_31684351384` — this section should be traversed only once
- L109 _macro_ `# define XXH_STATIC_LINKING_ONLY` — #  undef XXH_STATIC_LINKING_ONLY     avoid macro redef
- L113 _macro_ `# define XXH_PUBLIC_API static __inline __attribute__((unused))`
- L139 _macro_ `# define XXH_NAMESPACE XXH_INLINE_`
- L147 _macro_ `# define XXH_IPREF(Id) XXH_INLINE_ ## Id` — Some identifiers (enums, type names) are not symbols, but they must still be renamed to avoid redeclaration. Alternative solution: do not redeclare them. However, this requires some #ifdefs, and is a more dispersed action. Meanwhile, renaming can be achieved in a single block
- L148 _macro_ `# define XXH_OK XXH_IPREF(XXH_OK)`
- L149 _macro_ `# define XXH_ERROR XXH_IPREF(XXH_ERROR)`
- L150 _macro_ `# define XXH_errorcode XXH_IPREF(XXH_errorcode)`
- L151 _macro_ `# define XXH32_canonical_t XXH_IPREF(XXH32_canonical_t)`
- L152 _macro_ `# define XXH64_canonical_t XXH_IPREF(XXH64_canonical_t)`
- L153 _macro_ `# define XXH128_canonical_t XXH_IPREF(XXH128_canonical_t)`
- L154 _macro_ `# define XXH32_state_s XXH_IPREF(XXH32_state_s)`
- L155 _macro_ `# define XXH32_state_t XXH_IPREF(XXH32_state_t)`
- L156 _macro_ `# define XXH64_state_s XXH_IPREF(XXH64_state_s)`
- L157 _macro_ `# define XXH64_state_t XXH_IPREF(XXH64_state_t)`
- L158 _macro_ `# define XXH3_state_s XXH_IPREF(XXH3_state_s)`
- L159 _macro_ `# define XXH3_state_t XXH_IPREF(XXH3_state_t)`
- L160 _macro_ `# define XXH128_hash_t XXH_IPREF(XXH128_hash_t)`
- L172 _macro_ `#define XXHASH_H_5627135585666179 1`
- L178 _macro_ `# define XXH_PUBLIC_API __declspec(dllexport)`
- L201 _macro_ `# define XXH_CAT(A,B) A##B`
- L202 _macro_ `# define XXH_NAME2(A,B) XXH_CAT(A,B)`
- L203 _macro_ `# define XXH_versionNumber XXH_NAME2(XXH_NAMESPACE, XXH_versionNumber)`
- L204 _macro_ `# define XXH32 XXH_NAME2(XXH_NAMESPACE, XXH32)`
- L205 _macro_ `# define XXH32_createState XXH_NAME2(XXH_NAMESPACE, XXH32_createState)`
- L206 _macro_ `# define XXH32_freeState XXH_NAME2(XXH_NAMESPACE, XXH32_freeState)`
- L207 _macro_ `# define XXH32_reset XXH_NAME2(XXH_NAMESPACE, XXH32_reset)`
- L208 _macro_ `# define XXH32_update XXH_NAME2(XXH_NAMESPACE, XXH32_update)`
- L209 _macro_ `# define XXH32_digest XXH_NAME2(XXH_NAMESPACE, XXH32_digest)`
- L210 _macro_ `# define XXH32_copyState XXH_NAME2(XXH_NAMESPACE, XXH32_copyState)`
- L211 _macro_ `# define XXH32_canonicalFromHash XXH_NAME2(XXH_NAMESPACE, XXH32_canonicalFromHash)`
- L212 _macro_ `# define XXH32_hashFromCanonical XXH_NAME2(XXH_NAMESPACE, XXH32_hashFromCanonical)`
- L213 _macro_ `# define XXH64 XXH_NAME2(XXH_NAMESPACE, XXH64)`
- L214 _macro_ `# define XXH64_createState XXH_NAME2(XXH_NAMESPACE, XXH64_createState)`
- L215 _macro_ `# define XXH64_freeState XXH_NAME2(XXH_NAMESPACE, XXH64_freeState)`
- L216 _macro_ `# define XXH64_reset XXH_NAME2(XXH_NAMESPACE, XXH64_reset)`
- L217 _macro_ `# define XXH64_update XXH_NAME2(XXH_NAMESPACE, XXH64_update)`
- L218 _macro_ `# define XXH64_digest XXH_NAME2(XXH_NAMESPACE, XXH64_digest)`
- L219 _macro_ `# define XXH64_copyState XXH_NAME2(XXH_NAMESPACE, XXH64_copyState)`
- L220 _macro_ `# define XXH64_canonicalFromHash XXH_NAME2(XXH_NAMESPACE, XXH64_canonicalFromHash)`
- L221 _macro_ `# define XXH64_hashFromCanonical XXH_NAME2(XXH_NAMESPACE, XXH64_hashFromCanonical)`
- L228 _macro_ `#define XXH_VERSION_MAJOR 0` — Version
- L229 _macro_ `#define XXH_VERSION_MINOR 7`
- L230 _macro_ `#define XXH_VERSION_RELEASE 3`
- L231 _macro_ `#define XXH_VERSION_NUMBER (XXH_VERSION_MAJOR *100*100 + XXH_VERSION_MINOR *100 + XXH_VERSION_RELEASE)`
- L232 _prototype_ `unsigned XXH_versionNumber (void);`
- L239 _enumerator_ `typedef enum { XXH_OK=0, XXH_ERROR } XXH_errorcode; /*-********************************************************************** * 32-bit hash ************************************************************************/ #if !defined (__VMS) \ && (defined (__cplusplus) \` (scope `__anondd42d6fe0103`) — #include <stddef.h>     size_t
- L239 _enumerator_ `typedef enum { XXH_OK=0, XXH_ERROR } XXH_errorcode; /*-********************************************************************** * 32-bit hash ************************************************************************/ #if !defined (__VMS) \ && (defined (__cplusplus) \` (scope `__anondd42d6fe0103`) — #include <stddef.h>     size_t
- L239 _typedef_ `typedef enum { XXH_OK=0, XXH_ERROR } XXH_errorcode;` — #include <stddef.h>     size_t
- L249 _typedef_ `typedef uint32_t XXH32_hash_t;`
- L253 _typedef_ `typedef unsigned int XXH32_hash_t;`
- L256 _typedef_ `typedef unsigned long XXH32_hash_t;`
- L270 _prototype_ `XXH32_hash_t XXH32 (const void* input, size_t length, XXH32_hash_t seed);` — XXH32(): Calculate the 32-bit hash of sequence "length" bytes stored at memory address "input". The memory between input & input+length must be valid (allocated and read-accessible). "seed" can be used to alter the result predictably. Speed on Core 2 Duo @ 3 GHz (single thread, SMHasher benchmark): 5.4 GB/s
- L297 _typedef_ `typedef struct XXH32_state_s XXH32_state_t;`
- L298 _prototype_ `XXH32_state_t* XXH32_createState(void);` — typedef struct XXH32_state_s XXH32_state_t;     incomplete type
- L299 _prototype_ `XXH_errorcode XXH32_freeState(XXH32_state_t* statePtr);`
- L300 _prototype_ `void XXH32_copyState(XXH32_state_t* dst_state, const XXH32_state_t* src_state);`
- L302 _prototype_ `XXH_errorcode XXH32_reset (XXH32_state_t* statePtr, XXH32_hash_t seed);`
- L303 _prototype_ `XXH_errorcode XXH32_update (XXH32_state_t* statePtr, const void* input, size_t length);`
- L304 _prototype_ `XXH32_hash_t XXH32_digest (const XXH32_state_t* statePtr);`
- L327 _member_ `typedef struct { unsigned char digest[4]; } XXH32_canonical_t;` (scope `__anondd42d6fe0208`)
- L327 _typedef_ `typedef struct { unsigned char digest[4]; } XXH32_canonical_t;`
- L328 _prototype_ `void XXH32_canonicalFromHash(XXH32_canonical_t* dst, XXH32_hash_t hash);`
- L329 _prototype_ `XXH32_hash_t XXH32_hashFromCanonical(const XXH32_canonical_t* src);`
- L340 _typedef_ `typedef uint64_t XXH64_hash_t;`
- L343 _typedef_ `typedef unsigned long long XXH64_hash_t;` — the following type must have a width of 64-bit
- L354 _prototype_ `XXH64_hash_t XXH64 (const void* input, size_t length, XXH64_hash_t seed);` — XXH64(): Returns the 64-bit hash of sequence of length @length stored at memory address @input. @seed can be used to alter the result predictably. This function usually runs faster on 64-bit systems, but slower on 32-bit systems (see benchmark).
- L357 _typedef_ `typedef struct XXH64_state_s XXH64_state_t;` — Streaming
- L358 _prototype_ `XXH64_state_t* XXH64_createState(void);` — typedef struct XXH64_state_s XXH64_state_t;     incomplete type
- L359 _prototype_ `XXH_errorcode XXH64_freeState(XXH64_state_t* statePtr);`
- L360 _prototype_ `void XXH64_copyState(XXH64_state_t* dst_state, const XXH64_state_t* src_state);`
- L362 _prototype_ `XXH_errorcode XXH64_reset (XXH64_state_t* statePtr, XXH64_hash_t seed);`
- L363 _prototype_ `XXH_errorcode XXH64_update (XXH64_state_t* statePtr, const void* input, size_t length);`
- L364 _prototype_ `XXH64_hash_t XXH64_digest (const XXH64_state_t* statePtr);`
- L367 _member_ `typedef struct { unsigned char digest[8]; } XXH64_canonical_t;` (scope `__anondd42d6fe0308`) — Canonical representation
- L367 _typedef_ `typedef struct { unsigned char digest[8]; } XXH64_canonical_t;` — Canonical representation
- L368 _prototype_ `void XXH64_canonicalFromHash(XXH64_canonical_t* dst, XXH64_hash_t hash);`
- L369 _prototype_ `XXH64_hash_t XXH64_hashFromCanonical(const XXH64_canonical_t* src);`
- L379 _macro_ `#define XXHASH_H_STATIC_13879238742`
- L475 _macro_ `# define XXH3_64bits XXH_NAME2(XXH_NAMESPACE, XXH3_64bits)`
- L476 _macro_ `# define XXH3_64bits_withSecret XXH_NAME2(XXH_NAMESPACE, XXH3_64bits_withSecret)`
- L477 _macro_ `# define XXH3_64bits_withSeed XXH_NAME2(XXH_NAMESPACE, XXH3_64bits_withSeed)`
- L479 _macro_ `# define XXH3_createState XXH_NAME2(XXH_NAMESPACE, XXH3_createState)`
- L480 _macro_ `# define XXH3_freeState XXH_NAME2(XXH_NAMESPACE, XXH3_freeState)`
- L481 _macro_ `# define XXH3_copyState XXH_NAME2(XXH_NAMESPACE, XXH3_copyState)`
- L483 _macro_ `# define XXH3_64bits_reset XXH_NAME2(XXH_NAMESPACE, XXH3_64bits_reset)`
- L484 _macro_ `# define XXH3_64bits_reset_withSeed XXH_NAME2(XXH_NAMESPACE, XXH3_64bits_reset_withSeed)`
- L485 _macro_ `# define XXH3_64bits_reset_withSecret XXH_NAME2(XXH_NAMESPACE, XXH3_64bits_reset_withSecret)`
- L486 _macro_ `# define XXH3_64bits_update XXH_NAME2(XXH_NAMESPACE, XXH3_64bits_update)`
- L487 _macro_ `# define XXH3_64bits_digest XXH_NAME2(XXH_NAMESPACE, XXH3_64bits_digest)`
- L493 _prototype_ `XXH64_hash_t XXH3_64bits(const void* data, size_t len);` — XXH3_64bits(): default 64-bit variant, using default secret and default seed of 0. It's the fastest variant.
- L506 _macro_ `#define XXH3_SECRET_SIZE_MIN 136` — XXH3_64bits_withSecret(): It's possible to provide any blob of bytes as a "secret" to generate the hash. This makes it more difficult for an external actor to prepare an intentional collision. The secret *must* be large enough (>= XXH3_SECRET_SIZE_MIN). It should consist of random bytes. Avoid trivial sequences, such as repeating sequences and especially '\0', as this can cancel out itself. Failure to respect these conditions will result in a poor quality hash.
- L507 _prototype_ `XXH64_hash_t XXH3_64bits_withSecret(const void* data, size_t len, const void* secret, size_t secretSize);`
- L516 _prototype_ `XXH64_hash_t XXH3_64bits_withSeed(const void* data, size_t len, XXH64_hash_t seed);` — XXH3_64bits_withSeed(): This variant generates a custom secret on the fly based on the default secret, altered using the `seed` value. While this operation is decently fast, note that it's not completely free. Note: seed==0 produces the same results as XXH3_64bits().
- L523 _macro_ `# define XXH_ALIGN(n) alignas(n)`
- L525 _macro_ `# define XXH_ALIGN(n) __attribute__ ((aligned(n)))`
- L527 _macro_ `# define XXH_ALIGN(n) __declspec(align(n))`
- L529 _macro_ `# define XXH_ALIGN(n) /* disabled */`
- L535 _macro_ `# define XXH_ALIGN_MEMBER(align, type) type XXH_ALIGN(align)`
- L537 _macro_ `# define XXH_ALIGN_MEMBER(align, type) XXH_ALIGN(align) type`
- L540 _typedef_ `typedef struct XXH3_state_s XXH3_state_t;`
- L542 _macro_ `#define XXH3_SECRET_DEFAULT_SIZE 192 /* minimum XXH3_SECRET_SIZE_MIN */`
- L543 _macro_ `#define XXH3_INTERNALBUFFER_SIZE 256` — #define XXH3_SECRET_DEFAULT_SIZE 192     minimum XXH3_SECRET_SIZE_MIN
- L571 _prototype_ `XXH3_state_t* XXH3_createState(void);` — Streaming requires state maintenance. This operation costs memory and CPU. As a consequence, streaming is slower than one-shot hashing. For better performance, prefer one-shot functions whenever possible.
- L572 _prototype_ `XXH_errorcode XXH3_freeState(XXH3_state_t* statePtr);`
- L573 _prototype_ `void XXH3_copyState(XXH3_state_t* dst_state, const XXH3_state_t* src_state);`
- L581 _prototype_ `XXH_errorcode XXH3_64bits_reset(XXH3_state_t* statePtr);` — XXH3_64bits_reset(): Initialize with the default parameters. The result will be equivalent to `XXH3_64bits()`.
- L587 _prototype_ `XXH_errorcode XXH3_64bits_reset_withSeed(XXH3_state_t* statePtr, XXH64_hash_t seed);` — XXH3_64bits_reset_withSeed(): Generate a custom secret from `seed`, and store it into `statePtr`. digest will be equivalent to `XXH3_64bits_withSeed()`.
- L594 _prototype_ `XXH_errorcode XXH3_64bits_reset_withSecret(XXH3_state_t* statePtr, const void* secret, size_t secretSize);` — XXH3_64bits_reset_withSecret(): `secret` is referenced, and must outlive the hash streaming session, so be careful when using stack arrays. `secretSize` must be >= `XXH3_SECRET_SIZE_MIN`.
- L596 _prototype_ `XXH_errorcode XXH3_64bits_update (XXH3_state_t* statePtr, const void* input, size_t length);`
- L597 _prototype_ `XXH64_hash_t XXH3_64bits_digest (const XXH3_state_t* statePtr);`
- L603 _macro_ `# define XXH128 XXH_NAME2(XXH_NAMESPACE, XXH128)`
- L604 _macro_ `# define XXH3_128bits XXH_NAME2(XXH_NAMESPACE, XXH3_128bits)`
- L605 _macro_ `# define XXH3_128bits_withSeed XXH_NAME2(XXH_NAMESPACE, XXH3_128bits_withSeed)`
- L606 _macro_ `# define XXH3_128bits_withSecret XXH_NAME2(XXH_NAMESPACE, XXH3_128bits_withSecret)`
- L608 _macro_ `# define XXH3_128bits_reset XXH_NAME2(XXH_NAMESPACE, XXH3_128bits_reset)`
- L609 _macro_ `# define XXH3_128bits_reset_withSeed XXH_NAME2(XXH_NAMESPACE, XXH3_128bits_reset_withSeed)`
- L610 _macro_ `# define XXH3_128bits_reset_withSecret XXH_NAME2(XXH_NAMESPACE, XXH3_128bits_reset_withSecret)`
- L611 _macro_ `# define XXH3_128bits_update XXH_NAME2(XXH_NAMESPACE, XXH3_128bits_update)`
- L612 _macro_ `# define XXH3_128bits_digest XXH_NAME2(XXH_NAMESPACE, XXH3_128bits_digest)`
- L614 _macro_ `# define XXH128_isEqual XXH_NAME2(XXH_NAMESPACE, XXH128_isEqual)`
- L615 _macro_ `# define XXH128_cmp XXH_NAME2(XXH_NAMESPACE, XXH128_cmp)`
- L616 _macro_ `# define XXH128_canonicalFromHash XXH_NAME2(XXH_NAMESPACE, XXH128_canonicalFromHash)`
- L617 _macro_ `# define XXH128_hashFromCanonical XXH_NAME2(XXH_NAMESPACE, XXH128_hashFromCanonical)`
- L621 _member_ `XXH64_hash_t low64;` (scope `__anondd42d6fe0408`)
- L622 _member_ `XXH64_hash_t high64;` (scope `__anondd42d6fe0408`)
- L623 _typedef_ `} XXH128_hash_t;`
- L625 _prototype_ `XXH128_hash_t XXH128(const void* data, size_t len, XXH64_hash_t seed);`
- L626 _prototype_ `XXH128_hash_t XXH3_128bits(const void* data, size_t len);`
- L627 _prototype_ `XXH128_hash_t XXH3_128bits_withSeed(const void* data, size_t len, XXH64_hash_t seed);`
- L628 _prototype_ `XXH128_hash_t XXH3_128bits_withSecret(const void* data, size_t len, const void* secret, size_t secretSize);` — XXH_PUBLIC_API XXH128_hash_t XXH3_128bits_withSeed(const void* data, size_t len, XXH64_hash_t seed);    == XXH128()
- L630 _prototype_ `XXH_errorcode XXH3_128bits_reset(XXH3_state_t* statePtr);`
- L631 _prototype_ `XXH_errorcode XXH3_128bits_reset_withSeed(XXH3_state_t* statePtr, XXH64_hash_t seed);`
- L632 _prototype_ `XXH_errorcode XXH3_128bits_reset_withSecret(XXH3_state_t* statePtr, const void* secret, size_t secretSize);`
- L634 _prototype_ `XXH_errorcode XXH3_128bits_update (XXH3_state_t* statePtr, const void* input, size_t length);`
- L635 _prototype_ `XXH128_hash_t XXH3_128bits_digest (const XXH3_state_t* statePtr);`
- L644 _prototype_ `int XXH128_isEqual(XXH128_hash_t h1, XXH128_hash_t h2);` — XXH128_isEqual(): Return: 1 if `h1` and `h2` are equal, 0 if they are not.
- L655 _prototype_ `int XXH128_cmp(const void* h128_1, const void* h128_2);` — XXH128_cmp(): This comparator is compatible with stdlib's `qsort()`/`bsearch()`. return: >0 if *h128_1  > *h128_2 <0 if *h128_1  < *h128_2 =0 if *h128_1 == *h128_2
- L659 _member_ `typedef struct { unsigned char digest[16]; } XXH128_canonical_t;` (scope `__anondd42d6fe0508`) — Canonical representation
- L659 _typedef_ `typedef struct { unsigned char digest[16]; } XXH128_canonical_t;` — Canonical representation
- L660 _prototype_ `void XXH128_canonicalFromHash(XXH128_canonical_t* dst, XXH128_hash_t hash);`
- L661 _prototype_ `XXH128_hash_t XXH128_hashFromCanonical(const XXH128_canonical_t* src);`
- L667 _macro_ `# define XXH_IMPLEMENTATION`
- L696 _macro_ `# define XXH_IMPLEM_13a8737387`
- L737 _macro_ `# define XXH_FORCE_MEMORY_ACCESS 1`
- L749 _macro_ `# define XXH_ACCEPT_NULL_INPUT_POINTER 0` — #ifndef XXH_ACCEPT_NULL_INPUT_POINTER     can be defined externally
- L766 _macro_ `# define XXH_FORCE_ALIGN_CHECK 1`
- L792 _macro_ `# define XXH_NO_INLINE_HINTS 1` — || defined(__NO_INLINE__)       -O0, -fno-inline
- L794 _macro_ `# define XXH_NO_INLINE_HINTS 0`
- L807 _macro_ `# define XXH_REROLL 1`
- L809 _macro_ `# define XXH_REROLL 0`
- L822 _function_ `static void* XXH_malloc(size_t s)`
- L823 _function_ `static void XXH_free (void* p)`
- L826 _function_ `static void* XXH_memcpy(void* dest, const void* src, size_t size)`
- L842 _macro_ `# define XXH_FORCE_INLINE static` — #if XXH_NO_INLINE_HINTS   disable inlining hints
- L843 _macro_ `# define XXH_NO_INLINE static`
- L845 _macro_ `# define XXH_FORCE_INLINE static __forceinline` — #elif defined(_MSC_VER)      Visual Studio
- L846 _macro_ `# define XXH_NO_INLINE static __declspec(noinline)`
- L851 _macro_ `# define XXH_FORCE_INLINE static inline __attribute__((always_inline))`
- L852 _macro_ `# define XXH_NO_INLINE static __attribute__((noinline))`
- L854 _macro_ `# define XXH_FORCE_INLINE static inline`
- L873 _macro_ `# define DEBUGLEVEL 0`
- L878 _macro_ `# define XXH_ASSERT(c) assert(c)` — #  include <assert.h>     note: can still be disabled with NDEBUG
- L880 _macro_ `# define XXH_ASSERT(c) ((void)0)`
- L884 _macro_ `#define XXH_STATIC_ASSERT(c) { enum { XXH_sa = 1/(int)(!!(c)) }; }` — note: use after variable declarations
- L894 _typedef_ `typedef uint8_t xxh_u8;`
- L896 _typedef_ `typedef unsigned char xxh_u8;`
- L898 _typedef_ `typedef XXH32_hash_t xxh_u32;`
- L914 _function_ `static xxh_u32 XXH_read32(const void* memPtr)` — Force direct memory access. Only works on CPU which support unaligned memory access in hardware.
- L924 _member_ `typedef union { xxh_u32 u32; } __attribute__((packed)) unalign;` (scope `__anondd42d6fe060a`) — __pack instructions are safer but compiler specific, hence potentially problematic for some compilers. Currently only defined for GCC and ICC.
- L924 _typedef_ `typedef union { xxh_u32 u32; } __attribute__((packed)) unalign;` — __pack instructions are safer but compiler specific, hence potentially problematic for some compilers. Currently only defined for GCC and ICC.
- L925 _function_ `static xxh_u32 XXH_read32(const void* ptr)`
- L944 _enumerator_ `typedef enum { XXH_bigEndian=0, XXH_littleEndian=1 } XXH_endianess; /*! * XXH_CPU_LITTLE_ENDIAN: * Defined to 1 if the target is little endian` (scope `__anondd42d6fe0703`) — Endianess   ***
- L944 _enumerator_ `typedef enum { XXH_bigEndian=0, XXH_littleEndian=1 } XXH_endianess; /*! * XXH_CPU_LITTLE_ENDIAN: * Defined to 1 if the target is little endian` (scope `__anondd42d6fe0703`) — Endianess   ***
- L944 _typedef_ `typedef enum { XXH_bigEndian=0, XXH_littleEndian=1 } XXH_endianess;` — Endianess   ***
- L965 _macro_ `# define XXH_CPU_LITTLE_ENDIAN 0`
- L967 _function_ `static int XXH_isLittleEndian(void)`
- L973 _member_ `const union { xxh_u32 u; xxh_u8 c[4]; } one = { 1 };` (scope `XXH_isLittleEndian::__anondd42d6fe080a`) — Nonstandard, but well-defined behavior in practice. Don't use static: it is detrimental to performance.
- L973 _member_ `const union { xxh_u32 u; xxh_u8 c[4]; } one = { 1 };` (scope `XXH_isLittleEndian::__anondd42d6fe080a`) — Nonstandard, but well-defined behavior in practice. Don't use static: it is detrimental to performance.
- L976 _macro_ `# define XXH_CPU_LITTLE_ENDIAN XXH_isLittleEndian()`
- L986 _macro_ `#define XXH_GCC_VERSION (__GNUC__ * 100 + __GNUC_MINOR__)` — Compiler-specific Functions and Macros
- L989 _macro_ `# define __has_builtin(x) 0`
- L994 _macro_ `# define XXH_rotl32 __builtin_rotateleft32`
- L995 _macro_ `# define XXH_rotl64 __builtin_rotateleft64`
- L998 _macro_ `# define XXH_rotl32(x,r) _rotl(x,r)`
- L999 _macro_ `# define XXH_rotl64(x,r) _rotl64(x,r)`
- L1001 _macro_ `# define XXH_rotl32(x,r) (((x) << (r)) | ((x) >> (32 - (r))))`
- L1002 _macro_ `# define XXH_rotl64(x,r) (((x) << (r)) | ((x) >> (64 - (r))))`
- L1006 _macro_ `# define XXH_swap32 _byteswap_ulong` — #if defined(_MSC_VER)       Visual Studio
- L1008 _macro_ `# define XXH_swap32 __builtin_bswap32`
- L1010 _function_ `static xxh_u32 XXH_swap32 (xxh_u32 x)`
- L1023 _enumerator_ `typedef enum { XXH_aligned, XXH_unaligned } XXH_alignment; /* * XXH_FORCE_MEMORY_ACCESS==3 is an endian-independent byteshift load. * * This is ideal for older compilers which don't inline memcpy. */ #if (defined(XXH_FORCE_MEMORY_ACCESS) && (XXH_FORCE_MEMORY_ACCESS==3))` (scope `__anondd42d6fe0903`) — Memory reads
- L1023 _enumerator_ `typedef enum { XXH_aligned, XXH_unaligned } XXH_alignment; /* * XXH_FORCE_MEMORY_ACCESS==3 is an endian-independent byteshift load. * * This is ideal for older compilers which don't inline memcpy. */ #if (defined(XXH_FORCE_MEMORY_ACCESS) && (XXH_FORCE_MEMORY_ACCESS==3))` (scope `__anondd42d6fe0903`) — Memory reads
- L1023 _typedef_ `typedef enum { XXH_aligned, XXH_unaligned } XXH_alignment;` — Memory reads
- L1032 _function_ `XXH_FORCE_INLINE xxh_u32 XXH_readLE32(const void* memPtr)`
- L1041 _function_ `XXH_FORCE_INLINE xxh_u32 XXH_readBE32(const void* memPtr)`
- L1051 _function_ `XXH_FORCE_INLINE xxh_u32 XXH_readLE32(const void* ptr)`
- L1056 _function_ `static xxh_u32 XXH_readBE32(const void* ptr)`
- L1063 _function_ `XXH_readLE32_align(const void* ptr, XXH_alignment align)`
- L1076 _function_ `unsigned XXH_versionNumber (void)` — Misc
- L1082 _variable_ `static const xxh_u32 PRIME32_1 = 0x9E3779B1U;` — 32-bit hash functions
- L1083 _variable_ `static const xxh_u32 PRIME32_2 = 0x85EBCA77U;` — static const xxh_u32 PRIME32_1 = 0x9E3779B1U;     0b10011110001101110111100110110001
- L1084 _variable_ `static const xxh_u32 PRIME32_3 = 0xC2B2AE3DU;` — static const xxh_u32 PRIME32_2 = 0x85EBCA77U;     0b10000101111010111100101001110111
- L1085 _variable_ `static const xxh_u32 PRIME32_4 = 0x27D4EB2FU;` — static const xxh_u32 PRIME32_3 = 0xC2B2AE3DU;     0b11000010101100101010111000111101
- L1086 _variable_ `static const xxh_u32 PRIME32_5 = 0x165667B1U;` — static const xxh_u32 PRIME32_4 = 0x27D4EB2FU;     0b00100111110101001110101100101111
- L1088 _function_ `static xxh_u32 XXH32_round(xxh_u32 acc, xxh_u32 input)`
- L1145 _function_ `static xxh_u32 XXH32_avalanche(xxh_u32 h32)` — mix all bits
- L1155 _macro_ `#define XXH_get32bits(p) XXH_readLE32_align(p, align)`
- L1158 _function_ `XXH32_finalize(xxh_u32 h32, const xxh_u8* ptr, size_t len, XXH_alignment align)`
- L1160 _macro_ `#define PROCESS1 \`
- L1164 _macro_ `#define PROCESS4 \`
- L1227 _function_ `XXH32_endian_align(const xxh_u8* input, size_t len, xxh_u32 seed, XXH_alignment align)`
- L1265 _function_ `XXH32_hash_t XXH32 (const void* input, size_t len, XXH32_hash_t seed)`
- L1289 _function_ `XXH32_state_t* XXH32_createState(void)`
- L1293 _function_ `XXH_errorcode XXH32_freeState(XXH32_state_t* statePtr)`
- L1299 _function_ `void XXH32_copyState(XXH32_state_t* dstState, const XXH32_state_t* srcState)`
- L1304 _function_ `XXH_errorcode XXH32_reset(XXH32_state_t* statePtr, XXH32_hash_t seed)`
- L1321 _function_ `XXH32_update(XXH32_state_t* state, const void* input, size_t len)`
- L1384 _function_ `XXH32_hash_t XXH32_digest (const XXH32_state_t* state)`
- L1418 _function_ `void XXH32_canonicalFromHash(XXH32_canonical_t* dst, XXH32_hash_t hash)` — The default return values from XXH functions are unsigned 32 and 64 bit integers. The canonical representation uses big endian convention, the same convention as human-readable numbers (large digits first). This way, hash values can be written into a file or buffer, remaining comparable across different systems. The following functions allow transformation of hash values to and from their canonical format.
- L1425 _function_ `XXH32_hash_t XXH32_hashFromCanonical(const XXH32_canonical_t* src)`
- L1439 _typedef_ `typedef XXH64_hash_t xxh_u64;`
- L1465 _macro_ `# define XXH_REROLL_XXH64 1` — || (!defined(SIZE_MAX) || SIZE_MAX < ULLONG_MAX)   check limits
- L1467 _macro_ `# define XXH_REROLL_XXH64 0`
- L1479 _function_ `static xxh_u64 XXH_read64(const void* memPtr)` — Force direct memory access. Only works on CPU which support unaligned memory access in hardware
- L1489 _member_ `typedef union { xxh_u32 u32; xxh_u64 u64; } __attribute__((packed)) unalign64;` (scope `__anondd42d6fe0a0a`) — __pack instructions are safer, but compiler specific, hence potentially problematic for some compilers. Currently only defined for GCC and ICC.
- L1489 _member_ `typedef union { xxh_u32 u32; xxh_u64 u64; } __attribute__((packed)) unalign64;` (scope `__anondd42d6fe0a0a`) — __pack instructions are safer, but compiler specific, hence potentially problematic for some compilers. Currently only defined for GCC and ICC.
- L1489 _typedef_ `typedef union { xxh_u32 u32; xxh_u64 u64; } __attribute__((packed)) unalign64;` — __pack instructions are safer, but compiler specific, hence potentially problematic for some compilers. Currently only defined for GCC and ICC.
- L1490 _function_ `static xxh_u64 XXH_read64(const void* ptr)`
- L1508 _macro_ `# define XXH_swap64 _byteswap_uint64` — #if defined(_MSC_VER)       Visual Studio
- L1510 _macro_ `# define XXH_swap64 __builtin_bswap64`
- L1512 _function_ `static xxh_u64 XXH_swap64 (xxh_u64 x)`
- L1529 _function_ `XXH_FORCE_INLINE xxh_u64 XXH_readLE64(const void* memPtr)`
- L1542 _function_ `XXH_FORCE_INLINE xxh_u64 XXH_readBE64(const void* memPtr)`
- L1556 _function_ `XXH_FORCE_INLINE xxh_u64 XXH_readLE64(const void* ptr)`
- L1561 _function_ `static xxh_u64 XXH_readBE64(const void* ptr)`
- L1568 _function_ `XXH_readLE64_align(const void* ptr, XXH_alignment align)`
- L1579 _variable_ `static const xxh_u64 PRIME64_1 = 0x9E3779B185EBCA87ULL;`
- L1580 _variable_ `static const xxh_u64 PRIME64_2 = 0xC2B2AE3D27D4EB4FULL;` — static const xxh_u64 PRIME64_1 = 0x9E3779B185EBCA87ULL;     0b1001111000110111011110011011000110000101111010111100101010000111
- L1581 _variable_ `static const xxh_u64 PRIME64_3 = 0x165667B19E3779F9ULL;` — static const xxh_u64 PRIME64_2 = 0xC2B2AE3D27D4EB4FULL;     0b1100001010110010101011100011110100100111110101001110101101001111
- L1582 _variable_ `static const xxh_u64 PRIME64_4 = 0x85EBCA77C2B2AE63ULL;` — static const xxh_u64 PRIME64_3 = 0x165667B19E3779F9ULL;     0b0001011001010110011001111011000110011110001101110111100111111001
- L1583 _variable_ `static const xxh_u64 PRIME64_5 = 0x27D4EB2F165667C5ULL;` — static const xxh_u64 PRIME64_4 = 0x85EBCA77C2B2AE63ULL;     0b1000010111101011110010100111011111000010101100101010111001100011
- L1585 _function_ `static xxh_u64 XXH64_round(xxh_u64 acc, xxh_u64 input)`
- L1593 _function_ `static xxh_u64 XXH64_mergeRound(xxh_u64 acc, xxh_u64 val)`
- L1601 _function_ `static xxh_u64 XXH64_avalanche(xxh_u64 h64)`
- L1612 _macro_ `#define XXH_get64bits(p) XXH_readLE64_align(p, align)`
- L1615 _function_ `XXH64_finalize(xxh_u64 h64, const xxh_u8* ptr, size_t len, XXH_alignment align)`
- L1617 _macro_ `#define PROCESS1_64 \`
- L1621 _macro_ `#define PROCESS4_64 \`
- L1626 _macro_ `#define PROCESS8_64 { \`
- L1738 _function_ `XXH64_endian_align(const xxh_u8* input, size_t len, xxh_u64 seed, XXH_alignment align)`
- L1780 _function_ `XXH64_hash_t XXH64 (const void* input, size_t len, XXH64_hash_t seed)`
- L1803 _function_ `XXH64_state_t* XXH64_createState(void)`
- L1807 _function_ `XXH_errorcode XXH64_freeState(XXH64_state_t* statePtr)`
- L1813 _function_ `void XXH64_copyState(XXH64_state_t* dstState, const XXH64_state_t* srcState)`
- L1818 _function_ `XXH_errorcode XXH64_reset(XXH64_state_t* statePtr, XXH64_hash_t seed)`
- L1834 _function_ `XXH64_update (XXH64_state_t* state, const void* input, size_t len)`
- L1894 _function_ `XXH64_hash_t XXH64_digest (const XXH64_state_t* state)`
- L1921 _function_ `void XXH64_canonicalFromHash(XXH64_canonical_t* dst, XXH64_hash_t hash)`
- L1928 _function_ `XXH64_hash_t XXH64_hashFromCanonical(const XXH64_canonical_t* src)`

### `Source/Developer/Windows/LiveCoding/Private/LiveCodingLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveCoding, Display, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveCoding, Display, All);`

### `Source/Developer/Windows/LiveCoding/Private/LiveCodingModule.h` (Private)


#### class `FLiveCodingModule`  
`class FLiveCodingModule final : public ILiveCodingModule`  
_L30-153_
- inherits: `ILiveCodingModule`
- L33 _public prototype_ `FLiveCodingModule();`
- L34 _public prototype_ `~FLiveCodingModule();`
- L37 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L38 _public prototype_ `virtual void ShutdownModule() override;`
- L41 _public prototype_ `virtual void EnableByDefault(bool bInEnabled) override;` — ILiveCodingModule implementation
- L42 _public prototype_ `virtual bool IsEnabledByDefault() const override;`
- L43 _public prototype_ `virtual void EnableForSession(bool bInEnabled) override;`
- L44 _public prototype_ `virtual bool IsEnabledForSession() const override;`
- L45 _public prototype_ `virtual const FText& GetEnableErrorText() const override;`
- L46 _public prototype_ `virtual bool AutomaticallyCompileNewClasses() const override;`
- L47 _public prototype_ `virtual bool CanEnableForSession() const override;`
- L48 _public prototype_ `virtual bool HasStarted() const override;`
- L49 _public prototype_ `virtual void ShowConsole() override;`
- L50 _public prototype_ `virtual void Compile() override;`
- L51 _public prototype_ `virtual bool Compile(ELiveCodingCompileFlags CompileFlags, ELiveCodingCompileResult* Result) override;`
- L52 _public prototype_ `virtual bool IsCompiling() const override;`
- L53 _public prototype_ `virtual void Tick() override;`
- L54 _public prototype_ `virtual FOnPatchCompleteDelegate& GetOnPatchCompleteDelegate() override;`
- L56 _public prototype_ `static void BeginReload();`
- L59 _private prototype_ `void AttemptSyncLivePatching();`
- L60 _private prototype_ `static void OnDllNotification(unsigned int Reason, const void* DataPtr, void* Context);`
- L61 _private prototype_ `void OnDllLoaded(const FString& FullPath);`
- L62 _private prototype_ `void OnDllUnloaded(const FString& FullPath);`
- L63 _private prototype_ `bool IsUEDll(const FString& FullPath);`
- L64 _private prototype_ `bool IsPatchDll(const FString& FullPath);`
- L65 _private prototype_ `void HideConsole();`
- L66 _private prototype_ `void EnableConsoleCommand(FOutputDevice& out);`
- L67 _private prototype_ `void StartLiveCodingAsync(ELiveCodingStartupMode StartupMode);`
- L68 _private prototype_ `bool SetupConsolePath();`
- L69 _private prototype_ `bool StartLiveCoding(ELiveCodingStartupMode StartupMode);`
- L70 _private prototype_ `void StopLiveCoding();`
- L71 _private prototype_ `void OnModulesChanged(FName ModuleName, EModuleChangeReason Reason);`
- L72 _private prototype_ `void UpdateModules(bool bAllowStarting);`
- L73 _private prototype_ `bool ShouldPreloadModule(const TSet<FName>& PreloadedFileNames, const FString& FullFilePath) const;`
- L74 _private prototype_ `bool IsReinstancingEnabled() const;`
- L75 _private prototype_ `void WaitForStartup();`
- L76 _private prototype_ `bool HasStarted(bool bAllowStarting) const;`
- L77 _private prototype_ `void ShowConsole(bool bAllowStarting);`
- L78 _private prototype_ `void SetBuildArguments();`
- L93 _private prototype_ `static ReservePagesGlobalData& GetReservePagesGlobalData();`
- L94 _private prototype_ `static void ReservePagesTask();`
- L97 _private prototype_ `void ShowNotification(bool Success, const FText& Title, const FText* SubText);`
- L109 _private member_ `ULiveCodingSettings* Settings;`
- L110 _private member_ `TSharedPtr<ISettingsSection> SettingsSection;`
- L111 _private member_ `bool bSettingsEnabledLastTick = false;`
- L112 _private member_ `bool bEnableReinstancingLastTick = false;`
- L113 _private member_ `bool bBuildArgumentsSet = false;`
- L114 _private member_ `std::atomic<EState> State = EState::NotRunning;`
- L115 _private member_ `std::atomic<bool> bUpdateModulesInTick = false;`
- L116 _private member_ `bool bHasReinstancingOccurred = false;`
- L117 _private member_ `bool bHasPatchBeenLoaded = false;`
- L118 _private member_ `ELiveCodingCompileResult LastResults = ELiveCodingCompileResult::Success;`
- L119 _private member_ `TSet<FName> ConfiguredModules;`
- L120 _private member_ `TArray<void*> LppPendingTokens;`
- L121 _private member_ `void* CallbackCookie = nullptr;`
- L122 _private member_ `FString LastKnownTargetName = FString();`
- L124 _private member_ `FText EnableErrorText;`
- L126 _private member_ `const FString FullEngineDir;`
- L127 _private member_ `const FString FullEnginePluginsDir;`
- L128 _private member_ `const FString FullProjectDir;`
- L129 _private member_ `const FString FullProjectPluginsDir;`
- L130 _private member_ `FString FullEngineDirFromExecutable;`
- L131 _private member_ `FString FullEnginePluginsDirFromExecutable;`
- L132 _private member_ `FString FullProjectDirFromExecutable;`
- L133 _private member_ `FString FullProjectPluginsDirFromExecutable;`
- L135 _private member_ `IConsoleCommand* EnableCommand;`
- L136 _private member_ `IConsoleCommand* CompileCommand;`
- L137 _private member_ `IConsoleCommand* CompileSyncCommand;`
- L138 _private member_ `IConsoleVariable* ConsolePathVariable;`
- L139 _private member_ `IConsoleVariable* SourceProjectVariable;`
- L140 _private member_ `FDelegateHandle EndFrameDelegateHandle;`
- L141 _private member_ `FDelegateHandle ModulesChangedDelegateHandle;`
- L142 _private member_ `FOnPatchCompleteDelegate OnPatchCompleteDelegate;`
- L144 _private member_ `FCriticalSection SetBuildArgumentsCs;`
- L147 _private member_ `TUniquePtr<FReload> Reload;`
- L149 _private member_ `TUniquePtr<FNullReload> Reload;`
- L152 _private member_ `void* GlobalMutex = NULL;`

#### struct `FLiveCodingModule::ModuleChange`  
`struct ModuleChange`  
_L80-84_
- L82 _public member_ `FName FullName;`
- L83 _public member_ `bool bLoaded;`

#### struct `FLiveCodingModule::ReservePagesGlobalData`  
`struct ReservePagesGlobalData`  
_L85-92_
- L87 _public member_ `FCriticalSection ModuleChangeCs;`
- L88 _public member_ `TArray<ModuleChange> ModuleChanges;`
- L89 _public member_ `TArray<uintptr_t> ReservedPages;`
- L90 _public member_ `int LastReservePagesModuleCount = 0;`
- L91 _public member_ `FGraphEventRef ReservePagesTaskRef;`

#### enum `FLiveCodingModule::EState`  
`enum class EState`  
_L101-107_
- L103 _public enumerator_ `NotRunning`
- L104 _public enumerator_ `Starting`
- L105 _public enumerator_ `Running`
- L106 _public enumerator_ `RunningAndEnabled`

### `Source/Developer/Windows/LiveCoding/Private/LiveCodingModule2.h` (Private)


#### class `FLiveCodingModule`  
`class FLiveCodingModule final : public ILiveCodingModule`  
_L19-59_
- inherits: `ILiveCodingModule`
- L22 _public prototype_ `FLiveCodingModule();`
- L23 _public prototype_ `~FLiveCodingModule();`
- L26 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L27 _public prototype_ `virtual void ShutdownModule() override;`
- L30 _public prototype_ `virtual void EnableByDefault(bool bInEnabled) override;` — ILiveCodingModule implementation
- L31 _public prototype_ `virtual bool IsEnabledByDefault() const override;`
- L32 _public prototype_ `virtual void EnableForSession(bool bInEnabled) override;`
- L33 _public prototype_ `virtual bool IsEnabledForSession() const override;`
- L34 _public prototype_ `virtual const FText& GetEnableErrorText() const override;`
- L35 _public prototype_ `virtual bool AutomaticallyCompileNewClasses() const override;`
- L36 _public prototype_ `virtual bool CanEnableForSession() const override;`
- L37 _public prototype_ `virtual bool HasStarted() const override;`
- L38 _public prototype_ `virtual void ShowConsole() override;`
- L39 _public prototype_ `virtual void Compile() override;`
- L40 _public prototype_ `virtual bool Compile(ELiveCodingCompileFlags CompileFlags, ELiveCodingCompileResult* Result) override;`
- L41 _public prototype_ `virtual bool IsCompiling() const override;`
- L42 _public prototype_ `virtual void Tick() override;`
- L43 _public prototype_ `virtual FOnPatchCompleteDelegate& GetOnPatchCompleteDelegate() override;`
- L45 _public prototype_ `void OnHotKeyPressed(uint32 BrokerPid);`
- L47 _private prototype_ `bool CreateAgent();`
- L49 _private member_ `FText EnableErrorText;`
- L50 _private member_ `FDelegateHandle EndFrameDelegateHandle;`
- L51 _private member_ `FOnPatchCompleteDelegate OnPatchCompleteDelegate;`
- L52 _private member_ `TAtomic<uint32> LastSeenBrokerPid = 0;`
- L53 _private member_ `TAtomic<bool> HotReloadRequested = false;`
- L55 _private member_ `uint32 AgentBrokerPid = 0;`
- L56 _private member_ `lpp::LppSynchronizedAgent* Agent = nullptr;`
- L58 _private member_ `void* ListenKeyPressThread = nullptr;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace lpp`

### `Source/Developer/Windows/LiveCoding/Private/LiveCodingSettings.h` (Private)


#### enum `ELiveCodingStartupMode`  
`enum class ELiveCodingStartupMode : uint8`  
_L10-15_
- reflection: `UENUM()`
- L12 _public enumerator_ `Automatic UMETA(DisplayName = "Start automatically and show console")`
- L13 _public enumerator_ `AutomaticButHidden UMETA(DisplayName = "Start automatically but hide console until summoned")`
- L14 _public enumerator_ `Manual UMETA(DisplayName = "Manual")`

#### class `ULiveCodingSettings`  
`class ULiveCodingSettings : public UObject`  
_L18-51_
- reflection: `UCLASS(config=EditorPerProjectUserSettings, meta=(DisplayName="Live Coding"))`
- inherits: `UObject`
- L24 _public member_ `bool bEnabled;` — `UPROPERTY(config, EditAnywhere, Category=General, Meta=(ConfigRestartRequired=false, DisplayName="Enable Live Coding"))`
- L27 _public member_ `ELiveCodingStartupMode Startup;` — `UPROPERTY(config, EditAnywhere, Category=General, Meta=(ConfigRestartRequired=true, EditCondition="bEnabled"))`
- L30 _public member_ `bool bEnableReinstancing;` — `UPROPERTY(config, EditAnywhere, Category=General, Meta=(EditCondition="bEnabled"))`
- L33 _public member_ `bool bAutomaticallyCompileNewClasses;` — `UPROPERTY(config, EditAnywhere, Category=General, Meta=(EditCondition="bEnabled", DisplayName="Automatically Compile Newly Added C++ Classes"))`
- L36 _public member_ `bool bPreloadEngineModules;` — `UPROPERTY(config, EditAnywhere, Category=Modules, Meta=(ConfigRestartRequired=true, EditCondition="bEnabled"))`
- L39 _public member_ `bool bPreloadEnginePluginModules;` — `UPROPERTY(config, EditAnywhere, Category=Modules, Meta=(ConfigRestartRequired=true, EditCondition="bEnabled"))`
- L42 _public member_ `bool bPreloadProjectModules;` — `UPROPERTY(config, EditAnywhere, Category=Modules, Meta=(ConfigRestartRequired=true, EditCondition="bEnabled"))`
- L45 _public member_ `bool bPreloadProjectPluginModules;` — `UPROPERTY(config, EditAnywhere, Category=Modules, Meta=(ConfigRestartRequired=true, EditCondition="bEnabled"))`
- L48 _public member_ `TArray<FName> PreloadNamedModules;` — `UPROPERTY(config, EditAnywhere, Category=Modules, Meta=(ConfigRestartRequired=true, EditCondition="bEnabled", DisplayName="Names of modules, without target prefix, to always preload. Wildcards are supported"))`
- L50 _public prototype_ `ULiveCodingSettings(const FObjectInitializer& Initializer);`

### `Source/Developer/Windows/LiveCoding/Public/ILiveCodingModule.h` (Public)


#### enum `ELiveCodingCompileFlags`  
`enum class ELiveCodingCompileFlags : uint8`  
_L13-17_
- L15 _public enumerator_ `None = 0`
- L16 _public enumerator_ `WaitForCompletion = 1 << 0`

#### enum `ELiveCodingCompileResult`  
`enum class ELiveCodingCompileResult : uint8`  
_L20-29_
- L22 _public enumerator_ `Success` — Compile completed and there were changes
- L23 _public enumerator_ `NoChanges` — Compile completed and there were no changes
- L24 _public enumerator_ `InProgress` — Compile started but wait for completion was not specified
- L25 _public enumerator_ `CompileStillActive` — A prior compile request is still active
- L26 _public enumerator_ `NotStarted` — Live coding monitor could not be started
- L27 _public enumerator_ `Failure` — Complete completed but there was an error
- L28 _public enumerator_ `Cancelled` — Compile was cancelled

#### class `ILiveCodingModule`  
`class ILiveCodingModule : public IModuleInterface`  
_L31-68_
- inherits: `IModuleInterface`
- L38 _public prototype_ `virtual void EnableByDefault(bool bEnabled) = 0;` — Enable by default tracks the value in the live coding settings. If enabled by default and the startup mode is one of the automatic settings, then live coding console will be started when the module is started.
- L39 _public prototype_ `virtual bool IsEnabledByDefault() const = 0;`
- L52 _public prototype_ `virtual bool HasStarted() const = 0;` — The enabled for session state and started state are NOT independent states. If a request is made to enabled live coding (automatically or manually) and live coding hasn't already been started, then it is started.  If and only if the console starts will both the started state and the enabled for session state will be true. If enable for session is set to false, the console isn't stopped so the started state will remain true. Started = false, Enabled = false => no request to enable has ever been made or it failed to start Started = true, Enabled = true => a request to enable was made and it started properly Started = true, Enabled = false => has been started but later disabled Started = false, Enabled = true => impossible state.
- L53 _public prototype_ `virtual void EnableForSession(bool bEnabled) = 0;`
- L54 _public prototype_ `virtual bool IsEnabledForSession() const = 0;`
- L55 _public prototype_ `virtual bool CanEnableForSession() const = 0;`
- L57 _public prototype_ `virtual const FText& GetEnableErrorText() const = 0;`
- L58 _public prototype_ `virtual bool AutomaticallyCompileNewClasses() const = 0;`
- L60 _public prototype_ `virtual void ShowConsole() = 0;`
- L61 _public prototype_ `virtual void Compile() = 0;`
- L62 _public prototype_ `virtual bool Compile(ELiveCodingCompileFlags CompileFlags, ELiveCodingCompileResult* Result) = 0;`
- L63 _public prototype_ `virtual bool IsCompiling() const = 0;`
- L64 _public prototype_ `virtual void Tick() = 0;`
- L66 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnPatchCompleteDelegate);`
- L67 _public prototype_ `virtual FOnPatchCompleteDelegate& GetOnPatchCompleteDelegate() = 0;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define LIVE_CODING_MODULE_NAME "LiveCoding"`
- L66 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnPatchCompleteDelegate);`
