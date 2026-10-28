# Runtime / CrashReportCore

- module root: `Source/Runtime/CrashReportCore`
- headers: 15; symbols: 354
- symbol kinds: class=15, delegate=1, enum=2, enumerator=16, function=64, macro=2, member=119, prototype=121, struct=8, typedef=6
- PublicDependencyModuleNames: Analytics, AnalyticsET, Core, CrashDebugHelper, HTTP, Json, XmlParser

### `Source/Runtime/CrashReportCore/Private/CrashReportUtil.h` (Private)


#### class `FunctorDirectoryVisitor`  
`template <class FunctorType> class FunctorDirectoryVisitor : public IPlatformFile::FDirectoryVisitor`  
_L13-38_
- inherits: `IPlatformFile::FDirectoryVisitor`
- desc: Helper class for MakeDirectoryVisitor
- L22 _public function_ `virtual bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory) override` — Pass a directory or filename on to the user-provided functor @param FilenameOrDirectory Full path to a file or directory @param bIsDirectory Whether the path refers to a file or directory @return Whether to carry on iterating
- L30 _public function_ `FunctorDirectoryVisitor(FunctorType&& FunctorInstance) : Functor(MoveTemp(FunctorInstance))` — Move the provided functor into this object
- L37 _private member_ `FunctorType Functor;` — User-provided functor

#### Free symbols / members of external scopes

- L46 _function_ `template <class Functor> FunctorDirectoryVisitor<Functor> MakeDirectoryVisitor(Functor&& FunctorInstance)` — Convert a C++ functor into a IPlatformFile visitor object @param FunctorInstance Function object to call for each directory item @return Visitor object to be passed to platform directory visiting functions

### `Source/Runtime/CrashReportCore/Private/PendingReports.h` (Private)


#### class `FPendingReports`  
`class FPendingReports`  
_L11-64_
- desc: Manager for reports that weren't able to be sent on previous runs of the tool
- L17 _public prototype_ `FPendingReports();` — Load the list of reports
- L23 _public prototype_ `void Add(const FString& Path);` — Add a pending report directory @Path Full path to the directory containing the report
- L29 _public prototype_ `void Forget(const FString& ReportDirectoryName);` — Remove a pending report directory if present @ReportDirectoryName Leaf name of report directory to remove
- L34 _public function_ `void Clear()` — Clear out the list of reports
- L42 _public prototype_ `void Save() const;` — Save out the list of reports to the user's application settings folder
- L48 _public prototype_ `const TArray<FString>& GetReportDirectories() const;` — Access to report directories @return Full paths to all pending report directories
- L54 _private prototype_ `void Load();` — Load the list of reports from the user's application settings folder
- L60 _private prototype_ `static FString GetPendingReportsJsonFilepath();` — Get the application settings location of the pending reports file @return Full path to the file
- L63 _private member_ `TArray<FString> Reports;` — Full paths to reports not yet submitted

### `Source/Runtime/CrashReportCore/Public/Android/AndroidErrorReport.h` (Public)


#### class `FAndroidErrorReport`  
`class FAndroidErrorReport : public FGenericErrorReport`  
_L15-79_
- inherits: `FGenericErrorReport`
- desc: Helper that works with Android Error Reports
- L21 _public function_ `FAndroidErrorReport()` — Default constructor: creates a report with no files
- L29 _public prototype_ `explicit FAndroidErrorReport(const FString& Directory);` — Discover all files in the crash report directory @param Directory Full path to directory containing the report
- L34 _public prototype_ `static void Init();` — Load helper modules
- L39 _public prototype_ `static void ShutDown();` — Unload helper modules
- L43 _public prototype_ `FText DiagnoseReport() const;`
- L49 _public function_ `static void FindMostRecentErrorReports(TArray<FString>& ErrorReportPaths, const FTimespan& MaxCrashReportAge)` — Do nothing - shouldn't be called on Android @return Empty string
- L57 _public function_ `FString FindCrashedAppPath() const` — Get the full path of the crashed app from the report
- L78 _protected member_ `TArray<FMergeInfo> MergeSources;` — Filenames and merge info type of mergeable source files.

#### class `FAndroidErrorReport::FMergeInfo`  
`class FMergeInfo`  
_L64-74_
- L66 _private prototype_ `FMergeInfo();`
- L69 _public function_ `FMergeInfo(FString MergeNameIn, EMergeType MergeTypeIn) : MergeName(MergeNameIn), MergeType(MergeTypeIn)`
- L72 _public member_ `EMergeType MergeType;`
- L73 _public member_ `FString MergeName;`

#### enum `FAndroidErrorReport::FMergeInfo::EMergeType`  
`enum class EMergeType`  
_L68-68_
- L68 _public enumerator_ `enum class EMergeType { Threads, PlatformProperties }; FMergeInfo(FString MergeNameIn, EMergeType MergeTypeIn) : MergeName(MergeNameIn)`
- L68 _public enumerator_ `enum class EMergeType { Threads, PlatformProperties }; FMergeInfo(FString MergeNameIn, EMergeType MergeTypeIn) : MergeName(MergeNameIn)`

### `Source/Runtime/CrashReportCore/Public/CrashDescription.h` (Public)


#### struct `FCrashProperty`  
`struct FCrashProperty`  
_L106-153_
- desc: Simple crash property. Only for string values.
- L112 _protected prototype_ `FCrashProperty( const FString& InMainCategory, const FString& InSecondCategory, FPrimaryCrashProperties* InOwner );` — Initialization constructor.
- L116 _public prototype_ `FCrashProperty& operator=(const FString& NewValue);` — Assignment operator for string.
- L119 _public prototype_ `FCrashProperty& operator=(const TCHAR* NewValue);` — Assignment operator for TCHAR*.
- L122 _public prototype_ `FCrashProperty& operator=(const TArray<FString>& NewValue);` — Assignment operator for arrays.
- L125 _public prototype_ `FCrashProperty& operator=(const bool NewValue);` — Assignment operator for bool.
- L128 _public prototype_ `FCrashProperty& operator=(const int64 NewValue);` — Assignment operator for int64.
- L131 _public prototype_ `const FString& AsString() const;` — Getter for string, default.
- L134 _public prototype_ `bool AsBool() const;` — Getter for bool.
- L137 _public prototype_ `int64 AsInt64() const;` — Getter for int64.
- L141 _protected member_ `FPrimaryCrashProperties* Owner;` — Owner of the property.
- L144 _protected member_ `mutable FString CachedValue;` — Cached value of the property.
- L147 _protected member_ `FString MainCategory;` — Main category in the crash context.
- L150 _protected member_ `FString SecondCategory;` — Second category in the crash context.
- L152 _protected member_ `mutable bool bSet;`

#### struct `FCrashPropertyXmlNode`  
`struct FCrashPropertyXmlNode`  
_L155-181_
- L159 _public prototype_ `FCrashPropertyXmlNode& operator=(const FXmlNode* Node);` — Assignment operator for .
- L163 _public prototype_ `FCrashPropertyXmlNode& operator=(const TArray<FCrashThreadInfo>& ThreadsInfo);` — Assignment operator for converting ThreadsInfo into xml nodes
- L168 _protected prototype_ `FCrashPropertyXmlNode(const FString& InMainCategory, const FString& InSecondCategory, FPrimaryCrashProperties* InOwner);` — Initialization constructor.
- L172 _protected member_ `FPrimaryCrashProperties* Owner;` — Owner of the property.
- L175 _protected member_ `FString MainCategory;` — Main category in the crash context.
- L178 _protected member_ `FString SecondCategory;` — Second category in the crash context.
- L180 _protected member_ `mutable bool bSet;`

#### struct `FPrimaryCrashProperties`  
`struct FPrimaryCrashProperties`  
_L184-641_
- desc: Primary crash properties required by the crash report system.
- L190 _public member_ `ECrashDescVersions CrashVersion;` — Version.
- L193 _public member_ `ECrashDumpMode CrashDumpMode;` — Crash dump mode.
- L196 _public member_ `FString CrashGUID;` — An unique report name that this crash belongs to. Folder name.
- L204 _public member_ `FString GameName;` — The name of the game that crashed. (AppID) @GameName	varchar(64) FApp::GetProjectName()
- L210 _public member_ `FString ExecutableName;` — The name of the exe that crashed. (AppID) @GameName	varchar(64)
- L218 _public member_ `FString EngineMode;` — The mode the game was in e.g. editor. @EngineMode	varchar(64) FPlatformMisc::GetEngineMode()
- L224 _public member_ `FString DeploymentName;` — Deployment (also known as "EpicApp"), e.g. DevPlaytest, PublicTest, Live @DeploymentName varchar(64)
- L230 _public member_ `FCrashProperty EngineModeEx;` — EngineModeEx e.g. Unset, Dirty, Vanilla @DeploymentName varchar(64)
- L238 _public member_ `FCrashProperty PlatformFullName;` — The platform that crashed e.g. Win64. @PlatformName	varchar(64) Last path of the directory
- L249 _public member_ `FEngineVersion EngineVersion;` — Encoded engine version. (AppVersion) E.g. 4.3.0.0-2215663+UE-Releases+4.3 BuildVersion-BuiltFromCL-BranchName @EngineVersion	varchar(64) FEngineVersion::Current().ToString() ENGINE_VERSION_STRING
- L257 _public member_ `FCrashProperty CommandLine;` — The command line of the application that crashed. @CommandLine varchar(512) FCommandLine::Get()
- L265 _public member_ `FString BaseDir;` — The base directory where the app was running. @BaseDir varchar(512) FPlatformProcess::BaseDir()
- L273 _public member_ `FString AppDefaultLocale;` — The language ID the application that crashed. @LanguageExt varchar(64) FPlatformMisc::GetDefaultLocale()
- L281 _public member_ `FCrashProperty UserName;` — The name of the user that caused this crash. @UserName varchar(64) FString( FPlatformProcess::UserName() ).Replace( TEXT( "." ), TEXT( "" ) )
- L289 _public member_ `FCrashProperty LoginId;` — The unique ID used to identify the machine the crash occurred on. @ComputerName varchar(64) FPlatformMisc::GetLoginId()
- L297 _public member_ `FCrashProperty EpicAccountId;` — The Epic account ID for the user who last used the Launcher. @EpicAccountId	varchar(64) FPlatformMisc::GetEpicAccountId()
- L304 _public member_ `FCrashProperty GameSessionID;` — The last game session id set by the application. Application specific meaning. Some might not set this. @EpicAccountId	varchar(64)
- L311 _public member_ `FString PCallStackHash;` — A hash representing a unique id for a portable callstack. These will be specific to the CL version of the application @PCallStackHash	varchar(160)
- L316 _public member_ `int32 CrashSignal;` — The signal that was raised to enter the crash handler
- L321 _public member_ `int32 NumMinidumpFramesToIgnore;` — Specifies the number of stack frames in the callstack to ignore when symbolicating from a minidump.
- L328 _public member_ `FCrashProperty CallStack;` — An array of FStrings representing the callstack of the crash. @RawCallStack	varchar(MAX)
- L334 _public member_ `FCrashProperty PCallStack;` — An array of FStrings representing the portable callstack of the crash.
- L340 _public member_ `FCrashProperty PCallStackHashProperty;` — The hash of PCallStack
- L347 _public member_ `FCrashProperty SourceContext;` — An array of FStrings showing the source code around the crash. @SourceContext varchar(max)
- L353 _public member_ `FCrashProperty Modules;` — An array of module's name used by the game that crashed.
- L360 _public member_ `FCrashProperty UserDescription;` — An array of FStrings representing the user description of the crash. @Description	varchar(512)
- L367 _public member_ `FCrashProperty UserActivityHint;` — An FString representing the user activity, if known, when the error occurred. @UserActivityHint varchar(512)
- L375 _public member_ `FCrashProperty ErrorMessage;` — The error message, can be assertion message, ensure message or message from the fatal error. @Summary	varchar(512) GErrorMessage
- L378 _public member_ `FCrashProperty FullCrashDumpLocation;` — Location of full crash dump. Displayed in the crash report frontend.
- L386 _public member_ `FCrashProperty TimeOfCrash;` — The UTC time the crash occurred. @TimeOfCrash	datetime FDateTime::UtcNow().GetTicks()
- L393 _public member_ `FCrashProperty bAllowToBeContacted;` — Whether the user allowed us to be contacted. If true the following properties are retrieved from the system: UserName (for non-launcher build) and EpicAccountID. Otherwise they will be empty.
- L399 _public member_ `FCrashProperty CrashReporterMessage;` — Rich text string (should be localized by the crashing application) that will be displayed in the main CRC dialog Can be empty and the CRC's default text will be shown.
- L404 _public member_ `FCrashProperty PlatformCallbackResult;` — Platform-specific UE Core value (integer).
- L409 _public member_ `FCrashProperty CrashReportClientVersion;` — CRC sets this to the current version of the software.
- L415 _public member_ `bool bHasMiniDumpFile;` — Whether this crash has a minidump file. @HasMiniDumpFile bit
- L421 _public member_ `bool bHasLogFile;` — Whether this crash has a log file. @HasLogFile bit
- L424 _public member_ `bool bHasPrimaryData;` — Whether this crash contains primary usable data.
- L429 _public member_ `FString RestartCommandLine;` — Copy of CommandLine that isn't anonymized so it can be used to restart the process
- L434 _public member_ `bool bIsEnsure;` — Whether the report comes from a non-fatal event such as an ensure
- L439 _public member_ `FString CrashType;` — The type of crash being reported, e.g. Assert, Ensure, Hang
- L444 _public member_ `FCrashProperty CPUBrand;` — The cpu brand of the device, e.g. Intel, iPhone6, etc.
- L449 _public member_ `FCrashPropertyXmlNode Threads;` — Thread contexts, XML elements containing info specific to an active thread, e.g. callstacks
- L454 _public member_ `FCrashPropertyXmlNode PlatformPropertiesExtras;` — Optional additional data for platform properties
- L459 _public member_ `bool bIsOOM;` — Whether it was an OOM or not
- L464 _public member_ `bool bLowMemoryWarning;` — Whether we got a low memory warning or not
- L469 _public member_ `bool bInBackground;` — Whether we were in the background when the crash happened
- L474 _public member_ `bool bIsRequestingExit;` — Whether we crashed during shutdown
- L479 _public member_ `uint32 CrashScreenshotWidth = 0;` — Width and height of the crash screenshot, if present
- L480 _public member_ `uint32 CrashScreenshotHeight = 0;`
- L484 _protected prototype_ `FPrimaryCrashProperties();` — Default constructor.
- L487 _protected function_ `~FPrimaryCrashProperties()` — Destructor.
- L494 _public function_ `static void Set( FPrimaryCrashProperties* NewInstance )` — Sets new instance as the global.
- L502 _public function_ `static FPrimaryCrashProperties* Get()` — @return global instance of the primary crash properties for the currently processed/displayed crash
- L510 _public function_ `static bool IsValid()` — @return false, if there is no crash
- L516 _public prototype_ `static void Shutdown();` — Shutdowns the global instance.
- L519 _public function_ `bool HasProcessedData() const` — Whether this crash contains callstack, error message and source context thus it means that crash is complete.
- L525 _public prototype_ `void UpdateIDs();` — Updates following properties: UserName, LoginID and EpicAccountID.
- L528 _public prototype_ `void SendPreUploadAnalytics();` — Sends this crash for analytics (before upload).
- L531 _public prototype_ `void SendPostUploadAnalytics(double Duration, bool bResult, int32 ResponseCode, uint32 PayloadSize, uint32 ReportCount);` — Sends this crash for analytics (after upload) with additional stats about the upload.
- L534 _public prototype_ `void Save();` — Saves the data.
- L537 _public function_ `const FString& GetXmlFilepath()` — Gets the FilePath of the XML File.
- L541 _protected prototype_ `void ReadXML( const FString& CrashContextFilepath, const TCHAR* Buffer = nullptr );` — Reads previously set XML file. Optionally give a buffer to parse from. Any changes will be stored to CrashContextFilePath.
- L544 _protected prototype_ `void UpdateDefaults();` — Sets the TimeOfCrash and calls UpdateIDs if the XMLFile is valid
- L547 _protected prototype_ `void SetCrashGUID( const FString& Filepath );` — Sets the CrashGUID based on the report's path.
- L551 _protected function_ `template <typename Type> void GetCrashProperty( Type& out_ReadValue, const FString& MainCategory, const FString& SecondCategory ) const` — Gets a crash property from the XML file.
- L569 _protected function_ `template <typename Type> void SetCrashProperty( const FString& MainCategory, const FString& SecondCategory, const Type& Value )` — Sets a crash property to a new value.
- L575 _protected function_ `void SetCrashProperty( const FString& MainCategory, const FString& SecondCategory, const FString& NewValue )` — Sets a crash property to a new value.
- L598 _protected function_ `void SetCrashProperty(const FString& MainCategory, const FString& SecondCategory, const FXmlNode* NewNode)` — Sets a crash property to a new value.
- L629 _protected prototype_ `FString EncodeArrayStringAsXMLString( const TArray<FString>& ArrayString ) const;` — Encodes multi line property to be saved as single line.
- L631 _protected prototype_ `void MakeCrashEventAttributes(TArray<FAnalyticsEventAttribute>& OutCrashAttributes) const;`
- L634 _protected member_ `FXmlFile* XmlFile;` — Reader for the xml file.
- L637 _protected member_ `FString XmlFilepath;` — Cached filepath.
- L640 _protected member_ `static FPrimaryCrashProperties* Singleton;` — Global instance.

#### struct `FCrashContext`  
`struct FCrashContext : public FPrimaryCrashProperties`  
_L651-669_
- inherits: `FPrimaryCrashProperties`
- desc: Describes a unified crash, should be used by all platforms. Based on FGenericCrashContext, reads all saved properties, accessed by looking into read XML. Still lacks some of the properties, they will be added later. Must contain the same properties as ...\CrashReportServer\CrashReportCommon\CrashDescription.cs. Contains all usable information about the crash.
- L654 _public function_ `explicit FCrashContext( const FString& CrashContextFilepath, bool bIsReadOnly = false ) : FCrashContext(CrashContextFilepath, nullptr, bIsReadOnly)` — Initializes instance based on specified Crash Context filepath.
- L660 _public prototype_ `FCrashContext(const FString& CrashContextFilepath, const TCHAR* Buffer, bool bIsReadOnly = false);` — Initializes an instance based on a in memory buffer.
- L662 _public prototype_ `FCrashContext(const FCrashContext&) = delete;`
- L663 _public prototype_ `FCrashContext& operator=(const FCrashContext&) = delete;`
- L668 _private prototype_ `void SetupPrimaryCrashProperties();` — Initializes the primary crash property fields from the xml file

#### struct `FCrashWERContext`  
`struct FCrashWERContext : public FPrimaryCrashProperties`  
_L672-682_
- inherits: `FPrimaryCrashProperties`
- desc: Crash context based on the Window Error Reporting WER files, obsolete, only for backward compatibility.
- L675 _public prototype_ `explicit FCrashWERContext( const FString& WERXMLFilepath, bool bIsReadOnly = false );` — Initializes instance based on specified WER XML filepath.
- L677 _public prototype_ `FCrashWERContext(const FCrashWERContext&) = delete;`
- L678 _public prototype_ `FCrashWERContext& operator=(const FCrashWERContext&) = delete;`
- L681 _public prototype_ `void InitializeEngineVersion( const FString& BuildVersion, const FString& BranchName, uint32 BuiltFromCL );` — Initializes engine version from the separate components.

#### Free symbols / members of external scopes

- L90 _function_ `inline void LexFromString( ECrashDescVersions& OutValue, const TCHAR* Buffer )`
- L95 _function_ `inline void LexFromString( ECrashDumpMode& OutValue, const TCHAR* Buffer )`
- L100 _function_ `inline void LexFromString( FEngineVersion& OutValue, const TCHAR* Buffer )`
- L612 _function_ `` (scope `FPrimaryCrashProperties::SetCrashProperty`)

### `Source/Runtime/CrashReportCore/Public/CrashReportAnalytics.h` (Public)


#### class `FCrashReportAnalytics`  
`class FCrashReportAnalytics : FNoncopyable`  
_L18-39_
- inherits: `FNoncopyable`
- desc: The public interface for the analytics provider singleton. For Epic builds, this will point to epic's internal analytics provider. For licensee builds, it will be NULL by default unless they provide their own configuration.
- L25 _public prototype_ `static IAnalyticsProviderET& GetProvider();` — Return the provider instance. Not valid outside of Initialize/Shutdown calls. Note: must check IsAvailable() first else this code will assert if the provider is not valid.
- L27 _public function_ `static bool IsAvailable()` — Helper function to determine if the provider is valid.
- L32 _public prototype_ `static void Initialize(const FString& EpicAccountId = FString());` — Called to initialize the singleton.
- L34 _public prototype_ `static void Shutdown();` — Called to shut down the singleton
- L37 _private member_ `static bool bIsInitialized;`
- L38 _private member_ `static TSharedPtr<IAnalyticsProviderET> Analytics;`

### `Source/Runtime/CrashReportCore/Public/CrashReportCoreConfig.h` (Public)


#### struct `FFullCrashDumpEntry`  
`struct FFullCrashDumpEntry`  
_L27-48_
- desc: Holds FullCrashDump properties from the config. FullCrashDump_0_Branch=UE FullCrashDump_0_Location=\\epicgames.net\root\Builds\UE FullCrashDump_1_Branch=... ...
- L30 _public function_ `FFullCrashDumpEntry( const FString& InBranchName, const FString& InLocation, const bool bInExactMatch ) : BranchName( InBranchName ) , Location( InLocation ) , bExactMatch( bInExactMatch )` — Initialization constructor.
- L38 _public member_ `const FString BranchName;` — Partial branch name.
- L41 _public member_ `const FString Location;` — Location where the full crash dump will be copied. Usually a network share.
- L47 _public member_ `const bool bExactMatch;` — Branch=UE means exact match Branch=UE* means contain match

#### struct `FCrashReportCoreConfig`  
`struct FCrashReportCoreConfig`  
_L51-227_
- desc: Holds basic configuration for the crash report client.
- L54 _public function_ `static FCrashReportCoreConfig& Get()` — Accesses the singleton.
- L61 _public prototype_ `FCrashReportCoreConfig();` — Initialization constructor.
- L63 _public function_ `const FString& GetVersion() const`
- L68 _public function_ `const FString& GetReceiverAddress() const`
- L73 _public function_ `const FString& GetDataRouterURL() const`
- L78 _public function_ `const FString& GetDataRouterUnixSocket() const`
- L83 _public function_ `const FString& GetDiagnosticsFilename() const`
- L88 _public function_ `bool GetAllowToBeContacted() const`
- L93 _public function_ `bool GetHideAllowToBeContactedOption() const`
- L98 _public function_ `bool GetSendLogFile() const`
- L103 _public function_ `bool GetHideLogFilesOption() const`
- L108 _public function_ `bool GetHideRestartOption() const`
- L113 _public function_ `bool IsAllowedToCloseWithoutSending() const`
- L118 _public function_ `bool IsAllowedToSendWithoutDetailedInfo() const`
- L123 _public function_ `bool GetShowEndpointInTooltip() const`
- L128 _public function_ `const FString& GetCompanyName() const`
- L134 _public function_ `bool IsAllowedToCopyFilesToClipboard() const`
- L140 _public function_ `int GetUserCommentSizeLimit() const`
- L145 _public prototype_ `void SetAllowToBeContacted( bool bNewValue );`
- L146 _public prototype_ `void SetSendLogFile( bool bNewValue );`
- L149 _public prototype_ `void ApplyProjectOverrides(const FString& ConfigFilePath);`
- L152 _public prototype_ `void SetProjectConfigOverrides(const FConfigFile& InConfigFile);` — Set config values that are determined by the crashing application saving a config file to the crash folder
- L157 _public prototype_ `FString GetFullCrashDumpLocationForBranch(const FString& BranchName) const;` — @return location for full crash dump for the specified branch.
- L162 _public prototype_ `void PrintSettingsToLog() const;` — Prints the current settings to the log. Call once all applicable overrides has been applied.
- L166 _protected prototype_ `void ReadFullCrashDumpConfigurations();` — Reads FFullCrashDumpEntry config entries.
- L169 _protected member_ `FString CrashReportClientVersion;` — Client version (two digit licensee built e.g. "1.0" - three digits for Epic builds e.g. "1.0.0")
- L172 _protected member_ `FString CrashReportReceiverIP;` — IP address of crash report receiver.
- L175 _protected member_ `FString DataRouterUrl;` — URL of Data Router service
- L178 _protected member_ `FString DataRouterUnixSocket;` — Local Unix Socket to use for Data Router service
- L181 _protected member_ `FString DiagnosticsFilename;` — Filename to use when saving diagnostics report, if generated locally.
- L184 _protected member_ `FString SectionName;` — Section for crash report client configuration.
- L187 _protected member_ `TArray<FFullCrashDumpEntry> FullCrashDumpConfigurations;` — Configuration used for copying full dump crashes.
- L194 _protected member_ `bool bAllowToBeContacted;` — Whether the user allowed us to be contacted. If true the following properties are retrieved from the system: UserName (for non-launcher build) and EpicAccountID. Otherwise they will be empty.
- L197 _protected member_ `bool bHideAllowToBeContactedOption;` — Whether the user is shown the option to be contacted.
- L200 _protected member_ `bool bSendLogFile;` — Whether the user allowed us to send the log file.
- L203 _protected member_ `bool bHideLogFilesOption;` — Whether the user is shown the option to enable/disable sending the log file.
- L206 _protected member_ `bool bHideRestartOption;` — Whether the user is shown the option to restart the crashed application
- L209 _protected member_ `bool bIsAllowedToCloseWithoutSending;` — Whether the user is allowed to close the crash reporter without sending a report
- L212 _protected member_ `bool bIsAllowedToSendWithoutDetailedInfo;` — Whether the user is allowed to send the crash without providing detailed information about the crash
- L215 _protected member_ `FString CompanyName;` — Optional string displayed in the "allow to be contacted" text.
- L218 _protected member_ `bool bShowEndpointInTooltip;` — Whether to show the endpoint (reciever or datarouter url)
- L222 _protected member_ `bool bIsAllowedToCopyFilesToClipboard;` — Whether the user is allowed to copy the report files to the clipboard
- L226 _protected member_ `int UserCommentSizeLimit;` — Size limit for the description of multi-line text

#### Free symbols / members of external scopes

- L12 _macro_ `#define FORCE_CRASH_REPORT_UNATTENDED 0`
- L15 _macro_ `#define CRASH_REPORT_UNATTENDED_ONLY FORCE_CRASH_REPORT_UNATTENDED`

### `Source/Runtime/CrashReportCore/Public/CrashReportCoreModule.h` (Public)


#### class `FCrashReportCoreModule`  
`class FCrashReportCoreModule : public IModuleInterface`  
_L11-18_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule();`
- L15 _public prototype_ `virtual void ShutdownModule();`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(CrashReportCoreLog, Log, All) class FCrashReportCoreModule : public IModuleInterface { public: virtual void StartupModule(); virtual void ShutdownModule(); private: };`

### `Source/Runtime/CrashReportCore/Public/CrashReportCoreUnattended.h` (Public)


#### class `FCrashReportCoreUnattended`  
`class FCrashReportCoreUnattended`  
_L12-50_
- desc: Implementation of the crash report client used for unattended uploads
- L19 _public prototype_ `explicit FCrashReportCoreUnattended(FPlatformErrorReport& InErrorReport, bool InExitWhenComplete = true);` — Set up uploader object @param ErrorReport Error report to upload
- L21 _public function_ `bool IsUploadComplete()`
- L29 _private prototype_ `bool Tick(float DeltaTime);` — Update received every second @param DeltaTime Time since last update, unused @return Whether the updates should continue
- L34 _private prototype_ `void StartTicker();` — Begin calling Tick once a second
- L37 _private member_ `FCrashUploadToReceiver ReceiverUploader;` — Object that uploads report files to the server
- L40 _private member_ `FCrashUploadToDataRouter DataRouterUploader;` — Object that uploads report files to the server
- L43 _private member_ `FPlatformErrorReport ErrorReport;` — Platform code for accessing the report
- L46 _private member_ `bool bUploadComplete;` — upload is complete
- L49 _private member_ `bool bExitWhenComplete;` — exit when complete

### `Source/Runtime/CrashReportCore/Public/CrashUpload.h` (Public)


#### class `FCrashUploadBase`  
`class FCrashUploadBase`  
_L18-151_
- L21 _public prototype_ `FCrashUploadBase();`
- L23 _public prototype_ `virtual ~FCrashUploadBase();`
- L28 _public function_ `bool IsEnabled() const` — Is this uploader enabled or disabled?
- L33 _public function_ `bool IsUploadCalled() const` — Has BeginUpload been called?
- L38 _public function_ `const FText& GetStatusText() const` — Provide progress or error information for the UI
- L44 _public function_ `bool IsFinished() const` — Determine whether the upload has finished (successfully or otherwise) @return Whether the upload has finished
- L52 _public function_ `bool IsFinishedSuccessfully() const` — Determine whether the upload has finished successfully.
- L57 _public function_ `void Cancel()`
- L62 _public function_ `static bool IsInitialized()`
- L64 _public prototype_ `static void StaticInitialize(const FPlatformErrorReport& PlatformErrorReport);`
- L66 _public prototype_ `static void StaticShutdown();`
- L94 _protected prototype_ `static bool CompressData(const TArray<FString>& InPendingFiles, struct FCompressedData& OutCompressedData, TArray<uint8>& OutPostData, struct FCompressedHeader* OptionalHeader = nullptr);`
- L101 _protected prototype_ `static const TCHAR* ToString(EUploadState::Type InState);` — Get a string representation of the state, for logging purposes @param State Value to stringize @return Literal string value
- L107 _protected prototype_ `void SetCurrentState(EUploadState::Type InState);` — Set the current state, also updating the status text where necessary @param State State the uploader is now in
- L112 _protected prototype_ `void AddReportToFailedList() const;` — When failed, add the report to a file list containing reports to upload next time
- L118 _protected prototype_ `void CleanCrashReportDirectory(const FString& CrashReportDirectory);` — Removes crash report folder once submitted to the crash reporting backend, as to not fill up server -CleanCrashReports must be specified on the crash report client command line
- L121 _protected member_ `bool bUploadCalled;`
- L124 _protected member_ `EUploadState::Type State;` — What this class is currently doing
- L127 _protected member_ `FText UploadStateText;` — Status of upload to display
- L130 _protected member_ `EUploadState::Type PauseState;` — State to pause at until confirmation has been received to continue
- L133 _protected member_ `TArray<FString> PendingFiles;` — Full paths of files still to be uploaded
- L136 _protected member_ `FPlatformErrorReport ErrorReport;` — Error report being processed
- L139 _protected member_ `TArray<uint8> PostData;` — Buffer to keep reusing for file content and other messages
- L141 _protected member_ `int32 PendingReportDirectoryIndex;`
- L144 _protected member_ `static bool bInitialized;`
- L147 _protected member_ `static TArray<FString> PendingReportDirectories;` — Full paths of reports from previous runs still to be uploaded
- L150 _protected member_ `static TArray<FString> FailedReportDirectories;` — Full paths of reports from this run that did not upload

#### struct `FCrashUploadBase::EUploadState`  
`struct EUploadState`  
_L70-92_
- desc: State enum to keep track of what the uploader is doing

#### enum `FCrashUploadBase::EUploadState::Type`  
`enum Type`  
_L72-91_
- L74 _public enumerator_ `NotSet`
- L76 _public enumerator_ `PingingServer`
- L77 _public enumerator_ `Ready`
- L78 _public enumerator_ `CheckingReport`
- L79 _public enumerator_ `CheckingReportDetail`
- L80 _public enumerator_ `CompressAndSendData`
- L81 _public enumerator_ `WaitingToPostReportComplete`
- L82 _public enumerator_ `PostingReportComplete`
- L83 _public enumerator_ `Finished`
- L85 _public enumerator_ `ServerNotAvailable`
- L86 _public enumerator_ `UploadError`
- L87 _public enumerator_ `Cancelled`
- L88 _public enumerator_ `Disabled`
- L90 _public enumerator_ `FirstCompletedState = Finished`

#### class `FCrashUploadToReceiver`  
`class FCrashUploadToReceiver : public FCrashUploadBase`  
_L157-250_
- inherits: `FCrashUploadBase`
- desc: Handles uploading files to the crash report server
- L164 _public prototype_ `explicit FCrashUploadToReceiver(const FString& InReceiverAddress);` — Constructor: pings server @param ServerAddress Host IP of the crash report server
- L169 _public prototype_ `virtual ~FCrashUploadToReceiver();` — Destructor for logging
- L175 _public prototype_ `void BeginUpload(const FPlatformErrorReport& PlatformErrorReport);` — Commence upload when ready @param PlatformErrorReport Error report to upload files from
- L182 _private prototype_ `bool SendCheckReportRequest();` — Send a request to see if the server will accept this report @return Whether request was successfully sent
- L187 _private prototype_ `void CompressAndSendData();` — Compresses all crash report files and sends one compressed file.
- L192 _private prototype_ `void AssignReportIdToPostDataBuffer();` — Convert the report name to single byte non-zero-terminated HTTP post data
- L197 _private prototype_ `void PostReportComplete();` — Send a POST request to the server indicating that all the files for the current report have been sent
- L205 _private prototype_ `void OnProcessRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);` — Callback from HTTP library when a request has completed @param HttpRequest The request object @param HttpResponse The response from the server @param bSucceeded Whether a response was successfully received
- L210 _private prototype_ `void OnPingSuccess();` — Start uploading if BeginUpload has been called
- L218 _private prototype_ `bool PingTimeout(float DeltaTime);` — Callback a set amount of time after ping request was sent @note Gets fired no matter whether ping response was received @param Unused time since last call @return Always returns false, meaning one-shot
- L223 _private prototype_ `void CheckPendingReportsForFilesToUpload();` — If there a no pending files, look through pending reports for files to upload
- L228 _private prototype_ `void BeginUploadImpl();` — Start uploading files, either when user presses Submit or Ping request succeeds, whichever is later
- L233 _private prototype_ `TSharedRef<IHttpRequest, ESPMode::ThreadSafe> CreateHttpRequest();` — Create a request object and bind this class's response handler to it
- L238 _private prototype_ `void SendPingRequest();` — Send a ping request to the server
- L246 _private prototype_ `static bool ParseServerResponse(FHttpResponsePtr Response, bool& OutValidReport);` — Parse an XML response from the server for the success field @param Response			Response to get message to parse from @param OutValidReport	Answer from the server on whether to continue with this report upload @return					Whether a valid response was received from the server
- L249 _private member_ `FString UrlPrefix;` — Host, port and common prefix of all requests to the server

#### class `FCrashUploadToDataRouter`  
`class FCrashUploadToDataRouter : public FCrashUploadBase`  
_L255-325_
- inherits: `FCrashUploadBase`
- desc: Handles uploading files to the data router
- L262 _public prototype_ `explicit FCrashUploadToDataRouter(const FString& InDataRouterUrl, const FString& InOptionalDataRouterUnixSocket);` — Constructor: pings server @param ServerAddress Host IP of the crash report server
- L267 _public prototype_ `virtual ~FCrashUploadToDataRouter();` — Destructor for logging
- L269 _public prototype_ `void BeginUpload(const FPlatformErrorReport& PlatformErrorReport);`
- L275 _public prototype_ `void BeginUploadOptionalAttachments(const FPlatformErrorReport& PlatformErrorReport);` — Compresses all optional attachments files and sends one compressed file. Requires the base report to have been already sent (via BeginUpload).
- L280 _public prototype_ `void CompressAndSendData();` — Compresses all crash report files and sends one compressed file.
- L285 _public prototype_ `TSharedRef<IHttpRequest, ESPMode::ThreadSafe> CreateHttpRequest();` — Create a request object and bind this class's response handler to it
- L293 _public prototype_ `void OnProcessRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);` — Callback from HTTP library when a request has completed @param HttpRequest The request object @param HttpResponse The response from the server @param bSucceeded Whether a response was successfully received
- L299 _private prototype_ `void CheckPendingReportsForFilesToUpload();` — If there a no pending files, look through pending reports for files to upload
- L303 _private member_ `FString DataRouterUrl;` — Url for data router requests
- L306 _private member_ `FString DataRouterUnixSocket;` — Local Unix Socket for data router
- L309 _private member_ `bool bResult = false;` — HTTP request result
- L312 _private member_ `int32 ResponseCode = 0;` — HTTP response code
- L315 _private member_ `uint32 PayloadSize = 0;` — Payload size
- L318 _private member_ `uint32 ReportCount = 0;` — Reports uploaded
- L321 _private member_ `double Duration = 0.0;` — Duration of compression + upload
- L324 _private member_ `FDurationTimer Timer;` — Timer

### `Source/Runtime/CrashReportCore/Public/GenericErrorReport.h` (Public)


#### class `FGenericErrorReport`  
`class FGenericErrorReport`  
_L19-150_
- desc: Helper that works with Windows Error Reports
- L25 _public function_ `FGenericErrorReport()` — Default constructor: creates a report with no files
- L33 _public prototype_ `explicit FGenericErrorReport(const FString& Directory);` — Discover all files in the crash report directory @param Directory Full path to directory containing the report
- L38 _public function_ `static void Init()` — One-time initialisation: does nothing by default
- L45 _public function_ `static void ShutDown()` — One-time clean-up: does nothing by default
- L54 _public prototype_ `bool SetUserComment(const FText& UserComment);` — Write the provided comment into the error report @param UserComment Information provided by the user to add to the report @return Whether the comment was successfully written to the report
- L57 _public prototype_ `void SetPrimaryCrashProperties( FPrimaryCrashProperties& out_PrimaryCrashProperties );` — Sets properties specific to the processed crash. Used to convert the old data into the crash context format.
- L60 _public prototype_ `void SetCrashReportClientVersion(const FString& InVersion);` — Sets the version string in the error report and saves the change
- L66 _public prototype_ `TArray<FString> GetFilesToUpload() const;` — Provide full paths to all the report files @return List of paths
- L72 _public prototype_ `TArray<FString> GetOptionalAttachmentsToUpload() const;` — Provide full paths to all the report's optional attachment files @return List of paths
- L81 _public prototype_ `bool LoadWindowsReportXmlFile( FString& OutString ) const;` — Load the WER XML file for this report @note This is Windows specific and so shouldn't really be part of the public interface, but currently the server is Windows-specific in its checking of reports, so this is needed. @param OutString String to load the file into @return Whether finding and loading the file succeeded
- L86 _public prototype_ `bool TryReadDiagnosticsFile();` — @return Whether the file was found and successfully read
- L91 _public function_ `FString GetReportDirectory() const` — Provide the full path of the error report directory
- L99 _public function_ `FString GetReportDirectoryLeafName() const` — Provide the name of the error report directory
- L108 _public prototype_ `FString FindCrashedAppName() const;` — Get the name of the crashed app from the report
- L113 _public prototype_ `FString FindCrashedAppPath() const;` — Get the full path of the crashed app from the report
- L118 _public function_ `bool HasFilesToUpload() const` — Is there anything to upload?
- L128 _public prototype_ `bool FindFirstReportFileWithExtension(FString& OutFilename, const TCHAR* Extension) const;` — Look thought the list of report files to find one with the given extension @return Whether a file with the extension was found
- L133 _public prototype_ `void DeleteFiles();` — Delete files from disk
- L137 _protected member_ `FString ReportDirectory;` — Full path to the directory the report files are in
- L140 _protected member_ `TArray<FString> ReportFilenames;` — List of leaf filenames of all the files in the report folder
- L143 _protected member_ `FString OptionalAttachmentsDirectory;` — Full path to the directory the report's optional attachment files are in
- L146 _protected member_ `TArray<FString> OptionalAttachmentsFilenames;` — List of leaf filenames of all the files in the report's optional attachments folder
- L149 _protected member_ `mutable bool bValidCallstack;` — Whether the error report generated an valid callstack.

### `Source/Runtime/CrashReportCore/Public/IOS/IOSErrorReport.h` (Public)


#### class `FIOSErrorReport`  
`class FIOSErrorReport : public FGenericErrorReport`  
_L10-52_
- inherits: `FGenericErrorReport`
- desc: Helper that works with Mac Error Reports
- L16 _public function_ `FIOSErrorReport()` — Default constructor: creates a report with no files
- L23 _public prototype_ `static void Init();` — Load helper modules
- L28 _public prototype_ `static void ShutDown();` — Unload helper modules
- L34 _public prototype_ `explicit FIOSErrorReport(const FString& Directory);` — Discover all files in the crash report directory @param Directory Full path to directory containing the report
- L40 _public prototype_ `FText DiagnoseReport() const;` — Parse the callstack from the Apple-style crash report log @return UE crash diagnosis text
- L45 _public prototype_ `FString FindCrashedAppPath() const;` — Get the full path of the crashed app from the report (hides implementation in FGenericErrorReport)
- L51 _public prototype_ `static void FindMostRecentErrorReports(TArray<FString>& ErrorReportPaths, const FTimespan& MaxCrashReportAge);` — Look for the most recent Mac Error Report @return Full path to the most recent report, or an empty string if none found

### `Source/Runtime/CrashReportCore/Public/Linux/LinuxErrorReport.h` (Public)


#### class `FLinuxErrorReport`  
`class FLinuxErrorReport : public FGenericErrorReport`  
_L15-60_
- inherits: `FGenericErrorReport`
- desc: Helper that works with Linux Error Reports
- L21 _public function_ `FLinuxErrorReport()` — Default constructor: creates a report with no files
- L29 _public function_ `explicit FLinuxErrorReport(const FString& Directory) : FGenericErrorReport(Directory)` — Discover all files in the crash report directory @param Directory Full path to directory containing the report
- L38 _public function_ `FText DiagnoseReport() const` — Do nothing - shouldn't be called on Linux @return Dummy text
- L47 _public function_ `static void FindMostRecentErrorReports(TArray<FString>& ErrorReportPaths, const FTimespan& MaxCrashReportAge)` — Do nothing - shouldn't be called on Linux @return Empty string
- L55 _public function_ `FString FindCrashedAppPath() const` — Get the full path of the crashed app from the report

### `Source/Runtime/CrashReportCore/Public/Mac/MacErrorReport.h` (Public)


#### class `FMacErrorReport`  
`class FMacErrorReport : public FGenericErrorReport`  
_L10-52_
- inherits: `FGenericErrorReport`
- desc: Helper that works with Mac Error Reports
- L16 _public function_ `FMacErrorReport()` — Default constructor: creates a report with no files
- L23 _public prototype_ `static void Init();` — Load helper modules
- L28 _public prototype_ `static void ShutDown();` — Unload helper modules
- L34 _public prototype_ `explicit FMacErrorReport(const FString& Directory);` — Discover all files in the crash report directory @param Directory Full path to directory containing the report
- L40 _public prototype_ `FText DiagnoseReport() const;` — Parse the callstack from the Apple-style crash report log @return UE crash diagnosis text
- L45 _public prototype_ `FString FindCrashedAppPath() const;` — Get the full path of the crashed app from the report (hides implementation in FGenericErrorReport)
- L51 _public prototype_ `static void FindMostRecentErrorReports(TArray<FString>& ErrorReportPaths, const FTimespan& MaxCrashReportAge);` — Look for the most recent Mac Error Report @return Full path to the most recent report, or an empty string if none found

### `Source/Runtime/CrashReportCore/Public/PlatformErrorReport.h` (Public)


#### Free symbols / members of external scopes

- L11 _typedef_ `typedef FWindowsErrorReport FPlatformErrorReport;`
- L17 _typedef_ `typedef FLinuxErrorReport FPlatformErrorReport;`
- L23 _typedef_ `typedef FMacErrorReport FPlatformErrorReport;`
- L29 _typedef_ `typedef FIOSErrorReport FPlatformErrorReport;`
- L35 _typedef_ `typedef FAndroidErrorReport FPlatformErrorReport;`
- L39 _typedef_ `typedef FGenericErrorReport FPlatformErrorReport;`

### `Source/Runtime/CrashReportCore/Public/Windows/WindowsErrorReport.h` (Public)


#### class `FWindowsErrorReport`  
`class FWindowsErrorReport : public FGenericErrorReport`  
_L10-52_
- inherits: `FGenericErrorReport`
- desc: Helper that works with Windows Error Reports
- L16 _public function_ `FWindowsErrorReport()` — Default constructor: creates a report with no files
- L23 _public prototype_ `static void Init();` — Load helper modules
- L28 _public prototype_ `static void ShutDown();` — Unload helper modules
- L34 _public prototype_ `explicit FWindowsErrorReport(const FString& Directory);` — Discover all files in the crash report directory @param Directory Full path to directory containing the report
- L40 _public prototype_ `FText DiagnoseReport() const;` — Provide the exception and a call-stack as plain text if possible @note This can take quite a long time
- L45 _public prototype_ `FString FindCrashedAppPath() const;` — Get the full path of the crashed app from the report
- L51 _public prototype_ `static void FindMostRecentErrorReports(TArray<FString>& ErrorReportPaths, const FTimespan& MaxCrashReportAge);` — Look for the most recent Windows Error Reports @return Full path to the most recent report, or an empty string if none found
