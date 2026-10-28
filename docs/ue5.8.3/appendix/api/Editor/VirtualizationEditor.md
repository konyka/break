# Editor / VirtualizationEditor

- module root: `Source/Editor/VirtualizationEditor`
- headers: 12; symbols: 114
- symbol kinds: class=10, enum=3, enumerator=10, function=1, member=20, namespace=13, prototype=56, typedef=1
- PrivateDependencyModuleNames: ContentBrowserData, Core, CoreUObject, Engine, Slate, SlateCore, SourceControl, ToolMenus, UnrealEd, Virtualization
- PrivateIncludePathModuleNames: WorkspaceMenuStructure

### `Source/Editor/VirtualizationEditor/Private/CheckForVirtualizedContentCommandlet.h` (Private)


#### class `UCheckForVirtualizedContentCommandlet`  
`class UCheckForVirtualizedContentCommandlet : public UCommandlet`  
_L35-55_
- reflection: `UCLASS()`
- inherits: `UCommandlet`
- desc: Used to validate that content does not contain virtualized payloads. The current cmdline options are: -CheckEngine Checks all packages currently mounted in the engine -CheckProject Checks all packages currently mounted in the current project -CheckDir=XYZ (XYZ is the path to the directory, use '+' as the delimiter if supplying more than one path) Checks packages in the given directory and all subdirectories any or all of which can be passed to the commandlet. -OutputPaths Report virtualized packages by path rather than package name. If virtualized payloads are found then the package path (or file path if CheckDir indicates a directory that is not currently mounted by the project) is logged as an error and the commandlet will eventually return 1 as a failure value. Because the commandlet is the VirtualizationEditor module it needs to be invoked with the command line: -run="VirtualizationEditor.CheckForVirtualizedContent" Followed by
- L41 _private prototype_ `virtual int32 Main(const FString& Params) override;`
- L44 _private prototype_ `static int32 StaticMain(const FString& Params);`
- L48 _private prototype_ `TArray<FString> FindVirtualizedPackages(const TArray<FString>& PackagePaths);`
- L50 _private prototype_ `bool TryValidateContent(const TCHAR* DebugName, const TArray<FString>& Packages);`
- L51 _private prototype_ `bool TryValidateDirectory(const FString& Directory);`
- L53 _private member_ `bool bOutputPackageNames = true;`

### `Source/Editor/VirtualizationEditor/Private/CommandletUtils.h` (Private)


#### enum `UE::Virtualization::EFindPackageFlags`  
`enum EFindPackageFlags`  
_L32-37_
- desc: Used to customize package discovery behavior
- L34 _public enumerator_ `None = 0`
- L36 _public enumerator_ `ExcludeEngineContent = 1 << 0` — Do not return packages mounted to the engine or engine plugins

#### class `UE::Virtualization::FWorkQueue`  
`class FWorkQueue`  
_L91-117_
- desc: Takes a list of FIoHashs and breaks them into smaller jobs based on the JobSize. These jobs (in the form of an TArrayView) can then be requested one at a time until there are no more jobs left. The intended use is to make it easier to divide up the FIoHash list into smaller units to be pushed to the taskgraph system.
- L94 _public typedef_ `using FJob = TArrayView<const FIoHash>;`
- L96 _public prototype_ `FWorkQueue(TConstArrayView<FIoHash> InWork, int32 JobSize);`
- L97 _public prototype_ `FWorkQueue(TArray<FIoHash>&& InWork, int32 JobSize);`
- L98 _public prototype_ `~FWorkQueue() = default;`
- L106 _public prototype_ `FJob GetJob();` — Returns a FJob containing FIoHashes to be processed. If there is no more work to be done then empty jobs will be returned NOTE: That FJob is only valid for the lifespan of the FWorkQueue
- L109 _public prototype_ `bool IsEmpty() const;` — Returns true if there is no more work to done
- L113 _private prototype_ `void CreateJobs(int32 JobSize);`
- L115 _private member_ `TArray<FIoHash> Work;`
- L116 _private member_ `TArray<FJob> Jobs;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Virtualization` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Virtualization` (scope `UE`)
- L29 _prototype_ `bool PullPayloadsThreaded(TConstArrayView<FIoHash> PayloadIds, int32 BatchSize, const TCHAR* ProgressString, TUniqueFunction<void(const UE::Virtualization::FPullRequest& Response)>&& Callback);` (scope `UE::Virtualization`) — Utility to pull payloads in batches from many threads at once which can be much faster than pulling from a single thread in a single batch. The provided callback will be invoked each time that a request is completed. Every 30 seconds an update will be printed to the log showing how many payloads have been processed so that the user does not think that the process has stalled. @param PayloadIds		The payloads that should be pulled @param BatchSize			The max number of payload ids that should be in each batch @param ProgressString	An optional string to be printed as part of the status shown every 30 seconds, can be nullptr. @param Callback			Called on every request once it has been processed. @ return True if all requests succeeded, false if there were failures.
- L43 _prototype_ `TArray<FString> FindPackages(EFindPackageFlags Flags);` (scope `UE::Virtualization`) — Parse all of the active mount points for the current project and returns the packages found.
- L46 _prototype_ `TArray<FString> FindPackagesInDirectory(const FString& DirectoryToSearch);` (scope `UE::Virtualization`) — Finds all of the packages under a given directory including its subdirectories
- L59 _prototype_ `TArray<FString> DiscoverPackages(const FString& CmdlineParams, EFindPackageFlags Flags);` (scope `UE::Virtualization`) — Finds all of the packages under a the directory given by the provided command line. If no commandline switch can be found then the function will return all available packages. Valid commandline switches: '-PackageDir=...' '-PackageFolder=...' @param CmdlineParams A string containing the command line @return An array with the file path for each package found
- L62 _prototype_ `TArray<FIoHash> FindVirtualizedPayloads(const TArray<FString>& PackageNames);` (scope `UE::Virtualization`) — Returns a combined list of unique virtualized payload ids from the given list of packages
- L73 _prototype_ `void FindVirtualizedPayloadsAndTrailers(const TArray<FString>& PackagePaths, TMap<FString, UE::FPackageTrailer>& OutPackages, TSet<FIoHash>& OutPayloads);` (scope `UE::Virtualization`) — Load and parse the package trailers for the given packages. We return a map of all of the packages that contain virtualized payloads and a unique set of all the virtualized payloads referenced. Note that packages can reference the same payload if they re-use assets. @param PackagePaths	A list of packages to check @param OutPackages	A map of package paths to package trailers @param OutPayloads	A unique set of all the virtualized payloads referenced by the packages
- L76 _prototype_ `TArray<FPullRequest> ToRequestArray(TConstArrayView<FIoHash> IdentifierArray);` (scope `UE::Virtualization`) — Utility to turn an array of FIoHash into an array of FPullRequest
- L81 _namespace_ `namespace UE`
- L81 _namespace_ `namespace Virtualization` (scope `UE`)

### `Source/Editor/VirtualizationEditor/Private/ConsoleCommandUtils.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Virtualization` (scope `UE`)
- L14 _prototype_ `TArray<TPair<FString, UE::FPackageTrailer>> LoadPackageTrailerFromArgs(const TArray<FString>& Args);` (scope `UE::Virtualization`)
- L16 _prototype_ `void LogPackageTrailerLoadingError(const FPackagePath& Path);` (scope `UE::Virtualization`)
- L17 _prototype_ `void LogPackageTrailerLoadingError(const FString& Path);` (scope `UE::Virtualization`)

### `Source/Editor/VirtualizationEditor/Private/GenerateMountPointPayloadManifestCommandlet.h` (Private)


#### enum `EByteFormatting`  
`enum class EByteFormatting`  
_L10-15_
- L12 _public enumerator_ `Bytes = 0`
- L13 _public enumerator_ `MiB`
- L14 _public enumerator_ `GiB`

#### class `UGenerateMountPointPayloadManifestCommandlet`  
`class UGenerateMountPointPayloadManifestCommandlet : public UCommandlet`  
_L43-65_
- reflection: `UCLASS()`
- inherits: `UCommandlet`
- desc: Because the commandlet is the VirtualizationEditor module it needs to be invoked with the command line: -run="VirtualizationEditor.GenerateMountPointPayloadManifestCommandlet" By default the final output will be written to: <project root>/saved/PayloadManifest/mountpoints.csv Additional args: -DetailedFilterReasons This switch will provide a breakdown of how much content per mount point is prevented from being virtualized by a specific filter. -NoPaths This switch will prevent the relative path of the mount point being written to the output. -ByteFormat=Bytes/MiB/GiB This value allows the caller to set how bytes should be formatted to the csv file. The default is to output raw bytes. -OutputPath="" The full path (including filename and extension) of where to write the final output. -OutputName="" The file name (including extension) of where to write the final output. Note that the file will be written to the default output directory.
- L49 _private prototype_ `virtual int32 Main(const FString& Params) override;`
- L52 _private prototype_ `static int32 StaticMain(const FString& Params);`
- L56 _private prototype_ `bool TryParseCmdline(const FString& Params);`
- L57 _private prototype_ `bool TryParseOutputPathFromCmdline(const FString& Params);`
- L59 _private member_ `FString OutputFilePath;`
- L61 _private member_ `bool bDetailedFilterReasons = false;`
- L62 _private member_ `bool bOutputPaths = true;`
- L64 _private member_ `EByteFormatting ByteFormat = EByteFormatting::Bytes;`

### `Source/Editor/VirtualizationEditor/Private/GeneratePayloadManifestCommandlet.h` (Private)


#### class `UGeneratePayloadManifestCommandlet`  
`class UGeneratePayloadManifestCommandlet : public UCommandlet`  
_L36-66_
- reflection: `UCLASS()`
- inherits: `UCommandlet`
- desc: Creates a csv file containing info about all of the payloads in a set of packages. By default the commandlet will parse the payloads of all packages in the current project but this can be overridden with the cmdline switch -PackageDir=XYZ which will allow the commandlet to parse the payloads of the packages in a given directory. Because the commandlet is the VirtualizationEditor module it needs to be invoked with the command line: -run="VirtualizationEditor.GeneratePayloadManifest" By default the final output will be written to: <project root>/saved/PayloadManifest/sheet1.csv note that if the csv file is large enough it will be split over several files. Additional args: -LocalOnly Only output payloads that are stored locally on disk. -PendingOnly Only output payloads that are stored locally on disk but could be virtualized. -FilteredOnly Only output payloads that are stored locally on disk but would never be virtualized due to one or more filters. -VirtualizedOnly Only output payloads that have been virtualized.
- L42 _private prototype_ `virtual int32 Main(const FString& Params) override;`
- L45 _private prototype_ `static int32 StaticMain(const FString& Params);`
- L49 _private prototype_ `bool ParseCmdline(const FString& Params);`
- L63 _private prototype_ `FRIEND_ENUM_CLASS_FLAGS(EPayloadFilter);`
- L65 _private member_ `EPayloadFilter Filter = EPayloadFilter::None;`

#### enum `UGeneratePayloadManifestCommandlet::EPayloadFilter`  
`enum class EPayloadFilter`  
_L51-62_
- L53 _public enumerator_ `None = 0`
- L55 _public enumerator_ `LocalOnly = 1 << 0` — All locally stored payloads
- L57 _public enumerator_ `PendingOnly = (1 << 1) | LocalOnly` — Locally stored payloads that could be virtualized
- L59 _public enumerator_ `FilteredOnly = (1 << 2) | LocalOnly` — Local payloads that are filtered from the virtualization process.
- L61 _public enumerator_ `VirtualizedOnly = (1 << 3)` — Virtualized payloads

### `Source/Editor/VirtualizationEditor/Private/PrecachePayloadsCommandlet.h` (Private)


#### class `UPrecachePayloadsCommandlet`  
`class UPrecachePayloadsCommandlet : public UCommandlet`  
_L23-33_
- reflection: `UCLASS()`
- inherits: `UCommandlet`
- desc: Attempts to pull all virtualized content in the current project. Since the virtualization system will push any payloads pulled from persistent storage to cached storage this has the side effect of making sure that all payloads are stored in cached storage. This can be used to reduce the cost of virtualized payload access for a user at the cost of disk space. Because the commandlet is the VirtualizationEditor module it needs to be invoked with the command line: -run="VirtualizationEditor.PrecachePayloads"
- L29 _private prototype_ `virtual int32 Main(const FString& Params) override;`
- L32 _private prototype_ `static int32 StaticMain(const FString& Params);`

### `Source/Editor/VirtualizationEditor/Private/RehydrateProjectCommandlet.h` (Private)


#### class `URehydrateProjectCommandlet`  
`class URehydrateProjectCommandlet : public UCommandlet`  
_L19-37_
- reflection: `UCLASS()`
- inherits: `UCommandlet`
- desc: Finds all packages in the project and attempts to rehydrate them. If revision control is enabled then the commandlet will attempt to checkout the packages that need modification. Because the commandlet is the VirtualizationEditor module it needs to be invoked with the command line: -run="VirtualizationEditor.RehydrateProject"
- L27 _private prototype_ `virtual int32 Main(const FString& Params) override;`
- L30 _private prototype_ `static int32 StaticMain(const FString& Params);`
- L32 _private prototype_ `bool ParseCmdline(const FString& Params);`
- L36 _private member_ `bool bAutoCheckIn = false;`

### `Source/Editor/VirtualizationEditor/Private/RehydrationMenuEntry.h` (Private)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace Virtualization` (scope `UE`)
- L9 _prototype_ `void SetupRehydrationContentMenuEntry();` (scope `UE::Virtualization`) — Adds an option to rehydrate packages under the asset context menu

### `Source/Editor/VirtualizationEditor/Private/SVirtualAssetsStatistics.h` (Private)


#### class `SVirtualAssetsStatisticsDialog`  
`class SVirtualAssetsStatisticsDialog : public SCompoundWidget`  
_L19-54_
- inherits: `SCompoundWidget`
- L21 _private function_ `SLATE_BEGIN_ARGS(SVirtualAssetsStatisticsDialog)`
- L22 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L26 _private prototype_ `SVirtualAssetsStatisticsDialog();`
- L27 _private prototype_ `virtual ~SVirtualAssetsStatisticsDialog();`
- L31 _private prototype_ `TSharedRef<SWidget> GetGridPanel();`
- L33 _private prototype_ `EActiveTimerReturnType UpdateGridPanels(double InCurrentTime, float InDeltaTime);`
- L35 _private prototype_ `FText GetNotificationText() const;`
- L37 _private prototype_ `void OnNotificationEvent(UE::Virtualization::IVirtualizationSystem::ENotification Notification, const FIoHash& PayloadId);`
- L38 _private prototype_ `void OnWarningReasonOk();`
- L39 _private prototype_ `void OnWarningReasonIgnore();`
- L41 _private member_ `SVerticalBox::FSlot* GridSlot = nullptr;`
- L43 _private member_ `FCriticalSection NotificationCS;`
- L45 _private member_ `TSharedPtr<SNotificationItem> PullRequestNotificationItem;`
- L46 _private member_ `TSharedPtr<SNotificationItem> PullRequestFailedNotificationItem;`
- L48 _private member_ `TSharedPtr<class SScrollBox> ScrollBox;`
- L50 _private member_ `bool IsPulling = false;`
- L51 _private member_ `float PullNotificationTimer = 0.0f;`
- L52 _private member_ `uint32 NumPullRequests = 0;`
- L53 _private member_ `uint32 NumPullRequestFailures = 0;`

### `Source/Editor/VirtualizationEditor/Private/ValidateVirtualizedContentCommandlet.h` (Private)


#### class `UValidateVirtualizedContentCommandlet`  
`class UValidateVirtualizedContentCommandlet : public UCommandlet`  
_L34-49_
- reflection: `UCLASS()`
- inherits: `UCommandlet`
- desc: Iterates over all of the packages in a project and identifies which packages contain references to virtualized payloads. The commandlet will then check that all virtualized payloads can be found in persistent storage. Error messages will be logged for packages that contain virtualized payloads that cannot be found in one or more persistent storage backend. Because the commandlet is the VirtualizationEditor module it needs to be invoked with the command line: -run="VirtualizationEditor.ValidateVirtualizedContent" Optional Args: bValidateContent:	When this switch is set each payload will be pulled from persistent storage and additional validations will be run to make sure that the payload is not corrupted. This is much slower than just checking that the payload exists.
- L41 _private prototype_ `virtual int32 Main(const FString& Params) override;`
- L44 _private prototype_ `static int32 StaticMain(const FString& Params);`
- L46 _private prototype_ `int32 ValidatePayloadsExists(const TMap<FString, UE::FPackageTrailer>& Packages, const TSet<FIoHash>& Payloads);`
- L48 _private prototype_ `int32 ValidatePayloadContent(const TMap<FString, UE::FPackageTrailer>& Packages, const TSet<FIoHash>& Payloads, const UE::FIoHashToPackagesLookup& PkgLookupTable);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UE`

### `Source/Editor/VirtualizationEditor/Private/VirtualizeProjectCommandlet.h` (Private)


#### class `UVirtualizeProjectCommandlet`  
`class UVirtualizeProjectCommandlet : public UCommandlet`  
_L19-37_
- reflection: `UCLASS()`
- inherits: `UCommandlet`
- desc: Finds all packages in the project and attempts to virtualize their content. If revision control is enabled then the commandlet will attempt to checkout the packages that need modification. Because the commandlet is the VirtualizationEditor module it needs to be invoked with the command line: -run="VirtualizationEditor.VirtualizeProject"
- L27 _private prototype_ `virtual int32 Main(const FString& Params) override;`
- L30 _private prototype_ `static int32 StaticMain(const FString& Params);`
- L32 _private prototype_ `bool ParseCmdline(const FString& Params);`
- L36 _private member_ `bool bAutoCheckIn = false;`

### `Source/Editor/VirtualizationEditor/Public/VirtualizationEditorModule.h` (Public)


#### class `FVirtualizationEditorModule`  
`class FVirtualizationEditorModule : public IModuleInterface`  
_L15-28_
- inherits: `IModuleInterface`
- desc: The module holding all of the UI related pieces for the Virtualization module
- L19 _private prototype_ `virtual void StartupModule() override;`
- L20 _private prototype_ `virtual void ShutdownModule() override;`
- L22 _private prototype_ `void ShowVirtualAssetsStatisticsTab();`
- L24 _private prototype_ `TSharedPtr<SWidget> CreateVirtualAssetsStatisticsDialog();`
- L25 _private prototype_ `TSharedRef<SDockTab> CreateVirtualAssetsStatisticsTab(const FSpawnTabArgs& Args);`
- L27 _private member_ `TWeakPtr<SDockTab> VirtualAssetsStatisticsTab;`
