# Developer / CrashDebugHelper

- module root: `Source/Developer/CrashDebugHelper`
- headers: 9; symbols: 126
- symbol kinds: class=12, delegate=1, enum=2, enumerator=5, function=3, member=57, prototype=39, struct=2, typedef=5
- PrivateIncludePathModuleNames: PLCrashReporter
- PublicDependencyModuleNames: Core

### `Source/Developer/CrashDebugHelper/Private/Android/CrashDebugHelperAndroid.h` (Private)


#### class `FCrashDebugHelperAndroid`  
`class FCrashDebugHelperAndroid : public ICrashDebugHelper`  
_L10-21_
- inherits: `ICrashDebugHelper`
- L20 _public prototype_ `virtual bool CreateMinidumpDiagnosticReport( const FString& InCrashDumpName ) override;` — Parse the given crash dump, and generate a report. @param	InCrashDumpName		The crash dump file to process @return	bool				true if successful, false if not

#### Free symbols / members of external scopes

- L23 _typedef_ `typedef FCrashDebugHelperAndroid FCrashDebugHelper;`

### `Source/Developer/CrashDebugHelper/Private/CrashDebugHelperPrivate.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN( LogCrashDebugHelper, Log, All );`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN( LogCrashDebugHelper, Log, All );`

### `Source/Developer/CrashDebugHelper/Private/IOS/CrashDebugHelperIOS.h` (Private)


#### class `FCrashDebugHelperIOS`  
`class FCrashDebugHelperIOS : public ICrashDebugHelper`  
_L7-32_
- inherits: `ICrashDebugHelper`
- L10 _public prototype_ `FCrashDebugHelperIOS();`
- L11 _public prototype_ `virtual ~FCrashDebugHelperIOS();`
- L21 _public prototype_ `virtual bool ParseCrashDump(const FString& InCrashDumpName, FCrashDebugInfo& OutCrashDebugInfo) override;` — Parse the given crash dump, determining EngineVersion of the build that produced it - if possible. @param	InCrashDumpName		The crash dump file to process @param	OutCrashDebugInfo	The crash dump info extracted from the file @return	bool				true if successful, false if not
- L31 _public prototype_ `virtual bool CreateMinidumpDiagnosticReport( const FString& InCrashDumpName ) override;` — Parse the given crash dump, and generate a report. @param	InCrashDumpName		The crash dump file to process @return	bool				true if successful, false if not

#### Free symbols / members of external scopes

- L34 _typedef_ `typedef FCrashDebugHelperIOS FCrashDebugHelper;`

### `Source/Developer/CrashDebugHelper/Private/Linux/CrashDebugHelperLinux.h` (Private)


#### class `FCrashDebugHelperLinux`  
`class FCrashDebugHelperLinux : public ICrashDebugHelper`  
_L10-21_
- inherits: `ICrashDebugHelper`
- L20 _public prototype_ `virtual bool CreateMinidumpDiagnosticReport( const FString& InCrashDumpName ) override;` — Parse the given crash dump, and generate a report. @param	InCrashDumpName		The crash dump file to process @return	bool				true if successful, false if not

#### Free symbols / members of external scopes

- L23 _typedef_ `typedef FCrashDebugHelperLinux FCrashDebugHelper;`

### `Source/Developer/CrashDebugHelper/Private/Mac/CrashDebugHelperMac.h` (Private)


#### class `FCrashDebugHelperMac`  
`class FCrashDebugHelperMac : public ICrashDebugHelper`  
_L7-32_
- inherits: `ICrashDebugHelper`
- L10 _public prototype_ `FCrashDebugHelperMac();`
- L11 _public prototype_ `virtual ~FCrashDebugHelperMac();`
- L21 _public prototype_ `virtual bool ParseCrashDump(const FString& InCrashDumpName, FCrashDebugInfo& OutCrashDebugInfo) override;` — Parse the given crash dump, determining EngineVersion of the build that produced it - if possible. @param	InCrashDumpName		The crash dump file to process @param	OutCrashDebugInfo	The crash dump info extracted from the file @return	bool				true if successful, false if not
- L31 _public prototype_ `virtual bool CreateMinidumpDiagnosticReport( const FString& InCrashDumpName ) override;` — Parse the given crash dump, and generate a report. @param	InCrashDumpName		The crash dump file to process @return	bool				true if successful, false if not

#### Free symbols / members of external scopes

- L34 _typedef_ `typedef FCrashDebugHelperMac FCrashDebugHelper;`

### `Source/Developer/CrashDebugHelper/Private/Windows/CrashDebugHelperWindows.h` (Private)


#### class `FCrashDebugHelperWindows`  
`class FCrashDebugHelperWindows : public ICrashDebugHelper`  
_L7-18_
- inherits: `ICrashDebugHelper`
- L17 _public prototype_ `virtual bool CreateMinidumpDiagnosticReport( const FString& InCrashDumpName ) override;` — Parse the given crash dump, and generate a report. @param	InCrashDumpName		The crash dump file to process @return	bool				true if successful, false if not

#### Free symbols / members of external scopes

- L20 _typedef_ `typedef FCrashDebugHelperWindows FCrashDebugHelper;`

### `Source/Developer/CrashDebugHelper/Private/Windows/WindowsPlatformStackWalkExt.h` (Private)


#### struct `FWindowsPlatformStackWalkExt`  
`struct FWindowsPlatformStackWalkExt`  
_L13-66_
- desc: Windows implementation of stack walking using the COM interface IDebugClient5.
- L16 _public prototype_ `FWindowsPlatformStackWalkExt( FCrashInfo& InCrashInfo );` — Default constructor.
- L19 _public prototype_ `~FWindowsPlatformStackWalkExt();` — Destructor.
- L22 _public prototype_ `bool InitStackWalking();` — Initializes the COM interface to grab stacks.
- L25 _public prototype_ `void ShutdownStackWalking();` — Shutdowns COM.
- L28 _public prototype_ `void InitSymbols();` — Sets the options we want for symbol lookup.
- L31 _public prototype_ `static FString ExtractRelativePath( const TCHAR* BaseName, TCHAR* FullName );` — Grabs the branch relative path of the binary.
- L34 _public prototype_ `void GetExeFileVersionAndModuleList( FCrashModuleInfo& out_ExeFileVersion );` — Gets the exe file versions and lists all modules.
- L37 _public prototype_ `void SetSymbolPathsFromModules();` — Set the symbol paths based on the module paths.
- L40 _public prototype_ `void GetModuleInfoDetailed();` — Gets detailed info about each module.
- L43 _public prototype_ `bool IsOffsetWithinModules( uint64 Offset );` — Check to see if the stack address resides within one of the loaded modules i.e. is it valid?.
- L46 _public prototype_ `void GetSystemInfo();` — Extract the system info of the crash from the minidump.
- L49 _public function_ `void GetThreadInfo()` — Extracts the thread info from the minidump.
- L52 _public prototype_ `void GetExceptionInfo();` — Extracts info about the exception that caused the crash.
- L55 _public prototype_ `void GetCallstacks();` — Gets the callstack of the crash.
- L58 _public prototype_ `bool OpenDumpFile( const FString& DumpFileName );` — Opens a minidump as a new session.
- L62 _protected member_ `FCrashInfo& CrashInfo;` — Reference to the crash info.
- L65 _protected member_ `TArray<FString> SystemModuleNames;` — List of modules that are not from the engine.

### `Source/Developer/CrashDebugHelper/Public/CrashDebugHelper.h` (Public)


#### enum `EProcessorArchitecture`  
`enum EProcessorArchitecture`  
_L13-19_
- L15 _public enumerator_ `PA_UNKNOWN`
- L16 _public enumerator_ `PA_ARM`
- L17 _public enumerator_ `PA_X86`
- L18 _public enumerator_ `PA_X64`

#### class `FCrashModuleInfo`  
`class FCrashModuleInfo`  
_L24-37_
- desc: Details of a module from a crash dump
- L27 _public member_ `FString Report;`
- L29 _public member_ `FString Name;`
- L30 _public member_ `FString Extension;`
- L31 _public member_ `uint64 BaseOfImage = 0;`
- L32 _public member_ `uint32 SizeOfImage = 0;`
- L33 _public member_ `uint16 Major = 0;`
- L34 _public member_ `uint16 Minor = 0;`
- L35 _public member_ `uint16 Patch = 0;`
- L36 _public member_ `uint16 Revision = 0;`

#### class `FCrashThreadInfo`  
`class FCrashThreadInfo`  
_L42-54_
- desc: Details about a thread from a crash dump
- L45 _public member_ `FString Report;`
- L46 _public member_ `FString ThreadName;`
- L48 _public member_ `uint32 ThreadId = 0;`
- L49 _public member_ `uint32 SuspendCount = 0;`
- L50 _public member_ `bool IsCrashing = false;`
- L52 _public member_ `TArray<uint64> CallStack;`
- L53 _public member_ `FString PortableCallStackString;`

#### class `FCrashExceptionInfo`  
`class FCrashExceptionInfo`  
_L59-71_
- desc: Details about the exception in the crash dump
- L62 _public member_ `FString Report;`
- L64 _public member_ `uint32 ProcessId = 0;`
- L65 _public member_ `uint32 ThreadId = 0;`
- L66 _public member_ `uint32 Code = 0;`
- L67 _public member_ `FString ExceptionString;`
- L69 _public member_ `TArray<FString> CallStackString;`
- L70 _public member_ `TArray<FString> PortableCallStackString;`

#### class `FCrashSystemInfo`  
`class FCrashSystemInfo`  
_L76-88_
- desc: Details about the system the crash dump occurred on
- L79 _public member_ `FString Report;`
- L81 _public member_ `EProcessorArchitecture ProcessorArchitecture = PA_UNKNOWN;`
- L82 _public member_ `uint32 ProcessorCount = 0;`
- L84 _public member_ `uint16 OSMajor = 0;`
- L85 _public member_ `uint16 OSMinor = 0;`
- L86 _public member_ `uint16 OSBuild = 0;`
- L87 _public member_ `uint16 OSRevision = 0;`

#### class `FCrashInfo`  
`class FCrashInfo`  
_L92-161_
- desc: A platform independent representation of a crash
- L102 _public member_ `FString Report;` — Report log.
- L105 _public member_ `FString DepotName;` — The depot name, indicate where the executables and symbols are stored.
- L108 _public member_ `FString EngineVersion;` — Product version, based on FEngineVersion.
- L111 _public member_ `FString BuildVersion;` — Build version string.
- L114 _public member_ `int32 BuiltFromCL = INVALID_CHANGELIST;` — CL built from.
- L117 _public member_ `FString LabelName;` — The label the describes the executables and symbols.
- L120 _public member_ `FString ExecutablesPath;` — The network path where the executables are stored.
- L123 _public member_ `FString SymbolsPath;` — The network path where the symbols are stored.
- L125 _public member_ `FString SourceFile;`
- L126 _public member_ `uint32 SourceLineNumber = 0;`
- L127 _public member_ `TArray<FString> SourceContext;`
- L130 _public member_ `TArray<FString> ModuleNames;` — Only modules names, retrieved from the minidump file.
- L132 _public member_ `FCrashSystemInfo SystemInfo;`
- L133 _public member_ `FCrashExceptionInfo Exception;`
- L134 _public member_ `TArray<FCrashThreadInfo> Threads;`
- L135 _public member_ `TArray<FCrashModuleInfo> Modules;`
- L137 _public member_ `FString PlatformName;`
- L138 _public member_ `FString PlatformVariantName;`
- L143 _public prototype_ `void GenerateReport( const FString& DiagnosticsPath );` — Generate a report for the crash in the requested path
- L148 _public prototype_ `void Log( FString Line );` — Handle logging
- L154 _private prototype_ `static const TCHAR* GetProcessorArchitecture( EProcessorArchitecture PA );` — Convert the processor architecture to a human readable string
- L159 _private prototype_ `static void WriteLine(FArchive* ReportFile, const TCHAR* Line = nullptr);` — Write a line as UTF-8 to a file
- L160 _private prototype_ `static void WriteLine(FArchive* ReportFile, const FString& Line);`

#### enum `FCrashInfo::(anonymous)`  
``  
_L96-99_

#### struct `FCrashDebugInfo`  
`struct FCrashDebugInfo`  
_L164-174_
- desc: Helper structure for tracking crash debug information
- L167 _public member_ `FString CrashDumpName;` — The name of the crash dump file
- L169 _public member_ `int32 EngineVersion;` — The engine version of the crash dump build
- L171 _public member_ `FString PlatformName;` — The platform of the crash dump build
- L173 _public member_ `FString SourceControlLabel;` — The source control label of the crash dump build

#### class `ICrashDebugHelper`  
`class ICrashDebugHelper`  
_L177-240_
- desc: The public interface for the crash dump handler singleton.
- L181 _public prototype_ `virtual ~ICrashDebugHelper() = default;` — Virtual destructor
- L188 _public prototype_ `virtual bool Init();` — Initialize the helper @return	bool		true if successful, false if not
- L200 _public function_ `virtual bool ParseCrashDump(const FString& InCrashDumpName, FCrashDebugInfo& OutCrashDebugInfo)` — Parse the given crash dump, determining EngineVersion of the build that produced it - if possible. @param	InCrashDumpName		The crash dump file to process @param	OutCrashDebugInfo	The crash dump info extracted from the file @return	bool				true if successful, false if not Only used by Mac, to be removed.
- L212 _public function_ `virtual bool CreateMinidumpDiagnosticReport( const FString& InCrashDumpName )` — Parse the given crash dump, and generate a report. @param	InCrashDumpName		The crash dump file to process @return	bool				true if successful, false if not
- L220 _public prototype_ `virtual void AddSourceToReport();` — Extract lines from a source file, and add to the crash report.
- L231 _protected prototype_ `bool ReadSourceFile( TArray<FString>& OutStrings );` — Load the given ANSI text file to an array of strings - one FString per line of the file. Intended for use in simple text parsing actions @param	OutStrings			The array of FStrings to fill in @return	bool				true if successful, false if not
- L235 _public member_ `FCrashInfo CrashInfo;` — A platform independent representation of a crash
- L239 _protected member_ `bool bInitialized = false;` — Indicates that the crash handler is ready to do work

#### Free symbols / members of external scopes

- L98 _enumerator_ `INVALID_CHANGELIST = -1` (scope `FCrashInfo::__anon7ed0bd4e0103`) — An invalid changelist, something went wrong.

### `Source/Developer/CrashDebugHelper/Public/CrashDebugHelperModule.h` (Public)


#### class `FCrashDebugHelperModule`  
`class FCrashDebugHelperModule : public IModuleInterface`  
_L10-24_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule();`
- L14 _public prototype_ `virtual void ShutdownModule();`
- L17 _public prototype_ `ICrashDebugHelper* Get();` — Gets the crash debug helper singleton or returns NULL
- L20 _public prototype_ `ICrashDebugHelper* GetNew();` — Gets a new crash debug helper singleton for use with multiple report sending
- L23 _private member_ `class ICrashDebugHelper* CrashDebugHelper;`
