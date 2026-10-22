# Developer / Virtualization

- module root: `Source/Developer/Virtualization`
- headers: 13; symbols: 292
- symbol kinds: class=9, enum=9, enumerator=23, function=17, macro=4, member=73, namespace=32, prototype=121, struct=2, typedef=2
- PrivateDependencyModuleNames: Core, CoreUObject, DerivedDataCache, MessageLog, Projects, Slate, SlateCore, SourceControl
- PrivateIncludePathModuleNames: Analytics

### `Source/Developer/Virtualization/Internal/VirtualizationExperimentalUtilities.h` (Internal)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Virtualization` (scope `UE`)
- L11 _namespace_ `namespace Utils` (scope `UE::Virtualization`)
- L29 _prototype_ `EPayloadFilterReason FixFilterFlags(FStringView PackagePath, uint64 SizeOnDisk, EPayloadFilterReason CurrentFilterFlags);` (scope `UE::Virtualization::Utils`) — Adds filter reasons for a package that would only be calculated during the virtualization process and not stored in the payload trailer Currently this is used to fix up reporting in our commandlets and console commands so that it is easier for users to see why payloads have not been virtualized. This is only required because some filters are applied at package save time (when we know the owning asset type) and others at submit time. The two stage filtering does need fixing properly but I am not sure which way we want to do it, this is why we have an experimental utility to fix the reporting as I do not want to commit to an API change while still unsure on the direction we should take. NOTE: Only works if the "Default" virtualization system is used. @param PackagePath			Used to check for EPayloadFilterReason::Path @param SizeOnDisk			Used to check for EPayloadFilterReason::MinSize @param CurrentFilterFlags	The filters for the payload stored in the payload trailer. @return						The final filter reason used by the payload during the virtualization process.

### `Source/Developer/Virtualization/Private/PackageRehydrationProcess.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Virtualization` (scope `UE`)
- L19 _prototype_ `void RehydratePackages(TConstArrayView<FString> PackagePaths, ERehydrationOptions Options, FRehydrationResult& OutResult);` (scope `UE::Virtualization`) — This version will rehydrate a package and replace it on disk
- L22 _prototype_ `void RehydratePackages(TConstArrayView<FString> PackagePaths, uint64 PaddingAlignment, TArray<FText>& OutErrors, TArray<FSharedBuffer>& OutPackages, TArray<FRehydrationInfo>* OutInfo);` (scope `UE::Virtualization`) — This version will rehydrate a package but to a memory buffer, the original package on disk will remain untouched

### `Source/Developer/Virtualization/Private/PackageUtils.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Virtualization` (scope `UE`)
- L28 _prototype_ `bool ValidatePackage(const FString& PackagePath, TArray<FText>& OutErrors);` (scope `UE::Virtualization`) — Check that the given package ends with PACKAGE_FILE_TAG. Intended to be used to make sure that we have truncated a package correctly when removing the trailers. @param PackagePath	The path of the package that should be checked @param Errors [out] 	Errors created by the function will be added here @return	True if the package is correctly terminated with a PACKAGE_FILE_TAG, false if the tag was not found or if we were unable to read the file's contents.
- L31 _prototype_ `bool CanWriteToFile(const FString& FilePath);` (scope `UE::Virtualization`) — Tests if we would be able to write to the given file if we wanted to
- L47 _prototype_ `bool TryCopyPackageWithoutTrailer(const FString& SourcePath, const FString& DstPath, int64 TrailerLength, TArray<FText>& OutErrors);` (scope `UE::Virtualization`) — Creates a copy of the given package but the copy will not include the FPackageTrailer. @param SourcePath	The absolute path of the package to copy @param DstPath		The path where the copy should be created @param TrailerLength	The length of the trailer to be removed @param Errors [out]	Errors created by the function will be added here @return Returns true if the package was copied correctly, false otherwise. Note even when returning false a file might have been created at 'CopyPath'
- L59 _prototype_ `FString DuplicatePackageWithUpdatedTrailer(const FString& AbsolutePackagePath, const FPackageTrailer& Trailer, TArray<FText>& OutErrors);` (scope `UE::Virtualization`) — Create a copy of an existing package but replace the trailer with an updated version of the original trailer. The copy will be to a tmp file under the 'Saved' directory. @param AbsolutePackagePath	The path of the package to duplicate @param Tailer				The original trailer in the package, which has been updated with calls to UpdatePayloadAsVirtualized @param OutErrors				An array that will contain any errors encountered @return The path of the duplicated package file, if the duplicate was not created due to errors then the path returns will be empty
- L72 _prototype_ `FString DuplicatePackageWithNewTrailer(const FString& AbsolutePackagePath, const FPackageTrailer& Trailer, const FPackageTrailerBuilder& Builder, TArray<FText>& OutErrors);` (scope `UE::Virtualization`) — Create a copy of an existing package but replace the trailer with an updated version of the original trailer. The copy will be to a tmp file under the 'Saved' directory. @param AbsolutePackagePath	The path of the package to duplicate @param Tailer				The original trailer in the package @param Builder				A builder filled with the data required to make the new package trailer @param OutErrors				An array that will contain any errors encountered @return The path of the duplicated package file, if the duplicate was not created due to errors then the path returns will be empty

### `Source/Developer/Virtualization/Private/PackageVirtualizationProcess.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Virtualization` (scope `UE`)
- L15 _prototype_ `void VirtualizePackages(TConstArrayView<FString> PackagePaths, EVirtualizationOptions Options, FVirtualizationResult& OutResultInfo);` (scope `UE::Virtualization`)

### `Source/Developer/Virtualization/Private/SVirtualizationRevisionControlConnectionDialog.h` (Private)


#### class `UE::Virtualization::SRevisionControlConnectionDialog`  
`class SRevisionControlConnectionDialog : public SCompoundWidget`  
_L16-90_
- inherits: `SCompoundWidget`
- L40 _public prototype_ `static FResult RunDialog(FStringView RevisionControlName, FStringView ConfigSectionName, FStringView CurrentPort, FStringView CurrentUsername, const FText& ErrorMessage);`
- L42 _public function_ `SLATE_BEGIN_ARGS(SRevisionControlConnectionDialog)`
- L43 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SWindow>, Window) SLATE_END_ARGS() void Construct(const FArguments& InArgs, FStringView RevisionControlName, FStringView ConfigSectionName, FStringView CurrentPort, FStringView CurrentUsername, const FText& ErrorMessage);`
- L54 _public function_ `EResult GetResult() const`
- L59 _public function_ `const FString& GetPort() const`
- L64 _public function_ `const FString& GetUserName() const`
- L71 _private prototype_ `void CloseModalDialog();`
- L73 _private prototype_ `FReply OnResetToDefaults();`
- L74 _private prototype_ `FReply OnRetryConnection();`
- L75 _private prototype_ `FReply OnSkip();`
- L77 _private prototype_ `void OnUrlClicked() const;`
- L79 _private member_ `TWeakPtr<SWindow> WindowWidget;`
- L81 _private member_ `TSharedPtr<SEditableTextBox> PortTextWidget;`
- L82 _private member_ `TSharedPtr<SEditableTextBox> UsernameTextWidget;`
- L84 _private member_ `EResult Result = EResult::Skip;`
- L86 _private member_ `FString ConfigSectionName;`
- L88 _private member_ `FString Port;`
- L89 _private member_ `FString UserName;`

#### struct `UE::Virtualization::SRevisionControlConnectionDialog::FResult`  
`struct FResult`  
_L19-38_
- L22 _public prototype_ `FResult() = default;`
- L23 _public function_ `FResult(const FString& InPort, const FString& InUserName) : bShouldRetry(true) , Port(InPort) , UserName(InUserName)`
- L31 _public prototype_ `~FResult() = default;`
- L34 _public member_ `bool bShouldRetry = false;`
- L36 _public member_ `FString Port;`
- L37 _public member_ `FString UserName;`

#### enum `UE::Virtualization::SRevisionControlConnectionDialog::EResult`  
`enum class EResult : uint8`  
_L48-52_
- L50 _public enumerator_ `Retry`
- L51 _public enumerator_ `Skip`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Virtualization` (scope `UE`)

### `Source/Developer/Virtualization/Private/VirtualizationDDCBackend.h` (Private)


#### class `UE::Virtualization::FDDCBackend`  
`class FDDCBackend final : public IVirtualizationBackend`  
_L28-57_
- inherits: `IVirtualizationBackend`
- desc: A backend that uses the DDC2 as it's storage mechanism. It is intended to be used as a local caching system to speed up operations rather than for use as persistent storage. Ini file setup: 'Name'=(Type=DDCBackend, Bucket="XXX", LocalStorage=True/False, RemoteStorage=True/False) Required Values: 'Name': The backend name in the hierarchy. Optional Values: Bucket: An alphanumeric identifier used to group the payloads together in storage. [Default="BulkData"] LocalStorage: When set to true, the payloads can be stored locally. [Default=true] RemoteStorage: When set to true, the payloads can be stored remotely. [Default=true]
- L31 _public prototype_ `explicit FDDCBackend(FStringView ProjectName, FStringView ConfigName, FStringView InDebugName);`
- L32 _public prototype_ `virtual ~FDDCBackend() = default;`
- L37 _private prototype_ `virtual bool Initialize(const FString& ConfigEntry) override;`
- L39 _private prototype_ `virtual EConnectionStatus OnConnect() override;`
- L41 _private prototype_ `virtual bool PushData(TArrayView<FPushRequest> Requests, EPushFlags Flags) override;`
- L42 _private prototype_ `virtual bool PullData(TArrayView<FPullRequest> Requests, EPullFlags Flags, FText& OutErrors) override;`
- L44 _private prototype_ `virtual bool DoesPayloadExist(const FIoHash& Id) override;`
- L48 _private member_ `FString BucketName;` — The bucket being used to group together the virtualized payloads in storage
- L51 _private member_ `UE::DerivedData::FCacheBucket Bucket;` — The FCacheBucket used with the DDC, cached to avoid recreating it for each request
- L54 _private member_ `UE::DerivedData::ECachePolicy TransferPolicy;` — The policy to use when uploading or downloading data from the cache
- L56 _private member_ `UE::DerivedData::ECachePolicy QueryPolicy;` — The policy to use when querying the cache for information

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace DerivedData` (scope `UE`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Virtualization` (scope `UE`)

### `Source/Developer/Virtualization/Private/VirtualizationFileBackend.h` (Private)


#### class `UE::Virtualization::FFileSystemBackend`  
`class FFileSystemBackend final : public IVirtualizationBackend`  
_L34-65_
- inherits: `IVirtualizationBackend`
- desc: A basic backend based on the file system. This can be used to access/store virtualization data either on a local disk or a network share. It is intended to be used as a caching system to speed up operations (running a local cache or a shared cache for a site) rather than as the proper backend solution. Ini file setup: 'Name'=(Type=FileSystem, Path="XXX", RetryCount=X, RetryWaitTime=X) Required Values: 'Name': The backend name in the hierarchy. 'Type': The backend will be of type 'FFileSystemBackend'. 'Path': The root directory where the files are stored. Optional Values: RetryCount:		How many times we should try to open a payload file for read before giving up with an error. Useful when many threads/processes can be pushing/pulling from the same path/ [Default=10] RetryWaitTime:	The length of time the process should wait between each read attempt in milliseconds. Remember that the max length of time that the process can stall attempting to read a payload file is RetryCount * RetryWaitTime; [Default=100ms] EnvPathOverride: The name of the environment variable that the user can set to override 'Path'. This should only ever be set if you wish for the users to be able to choose where the payloads are being stored and do not rely on 'Path' always being used. [Default=""]
- L37 _public prototype_ `explicit FFileSystemBackend(FStringView ProjectName, FStringView ConfigName, FStringView DebugName);`
- L38 _public prototype_ `virtual ~FFileSystemBackend() = default;`
- L43 _private prototype_ `virtual bool Initialize(const FString& ConfigEntry) override;`
- L45 _private prototype_ `virtual EConnectionStatus OnConnect() override;`
- L47 _private prototype_ `virtual bool PushData(TArrayView<FPushRequest> Requests, EPushFlags Flags) override;`
- L48 _private prototype_ `virtual bool PullData(TArrayView<FPullRequest> Requests, EPullFlags Flags, FText& OutErrors) override;`
- L50 _private prototype_ `virtual bool DoesPayloadExist(const FIoHash& Id) override;`
- L54 _private prototype_ `void CreateFilePath(const FIoHash& PayloadId, FStringBuilderBase& OutPath);`
- L56 _private prototype_ `TUniquePtr<FArchive> OpenFileForReading(const TCHAR* FilePath);`
- L59 _private member_ `FString RootDirectory;` — The root directory where the payload files should be located.
- L62 _private member_ `int32 RetryCount = 10;` — The number of times to retry opening a payload file for read
- L64 _private member_ `int32 RetryWaitTimeMS = 100;` — The length of time (in milliseconds) to wait after each attempt before retrying.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Virtualization` (scope `UE`)

### `Source/Developer/Virtualization/Private/VirtualizationFilterSettings.h` (Private)


#### class `UVirtualizationFilterSettings`  
`class UVirtualizationFilterSettings : public UObject`  
_L13-34_
- reflection: `UCLASS(config = Engine)`
- inherits: `UObject`
- desc: Settings to use when determining if a package should be included/excluded from the content virtualization process.
- L24 _private member_ `TArray<FString> ExcludePackagePaths;` — `UPROPERTY(Config)` — A list of package paths that we should always prevent being virtualized . Each path can either be a full package path to a specific package or it can be a path to a directory, in which case all packages under that directory (and subdirectories) will be excluded from the virtualization process.
- L33 _private member_ `TArray<FString> IncludePackagePaths;` — `UPROPERTY(Config)` — A list of package paths that we should always attempt to virtualize. Each path can either be a full package path to a specific package or it can be a path to a directory, in which case all packages under that directory (and subdirectories) will be included in the virtualization process.

### `Source/Developer/Virtualization/Private/VirtualizationManager.h` (Private)


#### enum `UE::Virtualization::EPackageFilterMode`  
`enum class EPackageFilterMode : uint8`  
_L159-165_
- desc: The default mode of filtering to use with package paths that do not match entries in UVirtualizationFilterSettings
- L162 _public enumerator_ `OptOut = 0` — Packages will be virtualized by default and must be opted out by the use of UVirtualizationFilterSettings::ExcludePackagePaths
- L164 _public enumerator_ `OptIn` — Packages will not be virtualized by default and must be opted in by the user of UVirtualizationFilterSettings::IncludePackagePaths

#### class `UE::Virtualization::FVirtualizationManager`  
`class FVirtualizationManager final : public IVirtualizationSystem`  
_L172-434_
- inherits: `IVirtualizationSystem`
- desc: This is used as a wrapper around the various potential back end implementations. The calling code shouldn't need to care about which back ends are actually in use.
- L175 _public typedef_ `using FRegistedFactories = TMap<FName, IVirtualizationBackendFactory*>;`
- L176 _public typedef_ `using FBackendArray = TArray<IVirtualizationBackend*>;`
- L178 _public prototype_ `FVirtualizationManager();`
- L179 _public prototype_ `virtual ~FVirtualizationManager();`
- L184 _private prototype_ `virtual bool Initialize(const FInitParams& InitParams) override;`
- L186 _private prototype_ `virtual bool IsEnabled() const override;`
- L187 _private prototype_ `virtual bool IsPushingEnabled(EStorageType StorageType) const override;`
- L189 _private prototype_ `virtual EPayloadFilterReason FilterPayload(const UObject* Owner) const override;`
- L191 _private prototype_ `virtual bool AllowSubmitIfVirtualizationFailed() const override;`
- L193 _private prototype_ `virtual bool PushData(TArrayView<FPushRequest> Requests, EStorageType StorageType) override;`
- L194 _private prototype_ `virtual bool PullData(TArrayView<FPullRequest> Requests) override;`
- L196 _private prototype_ `virtual EQueryResult QueryPayloadStatuses(TArrayView<const FIoHash> Ids, EStorageType StorageType, TArray<EPayloadStatus>& OutStatuses) override;`
- L198 _private prototype_ `virtual FVirtualizationResult TryVirtualizePackages(TConstArrayView<FString> PackagePaths, EVirtualizationOptions Options) override;`
- L200 _private prototype_ `virtual FRehydrationResult TryRehydratePackages(TConstArrayView<FString> PackagePaths, ERehydrationOptions Options) override;`
- L201 _private prototype_ `virtual ERehydrationResult TryRehydratePackages(TConstArrayView<FString> PackagePaths, uint64 PaddingAlignment, TArray<FText>& OutErrors, TArray<FSharedBuffer>& OutPackages, TArray<FRehydrationInfo>* OutInfo) override;`
- L203 _private prototype_ `virtual void DumpStats() const override;`
- L205 _private prototype_ `virtual FPayloadActivityInfo GetSystemStatistics() const override;`
- L207 _private prototype_ `virtual TArray<FBackendStats> GetBackendStatistics() const override;`
- L209 _private prototype_ `virtual void GatherAnalytics(TArray<FAnalyticsEventAttribute>& Attributes) const override;`
- L211 _private function_ `virtual FOnNotification& GetNotificationEvent() override`
- L218 _public prototype_ `EPayloadFilterReason FixFilterFlags(FStringView PackagePath, uint64 SizeOnDisk, EPayloadFilterReason CurrentFilterFlags);` — @see UE::Virtualization::Utils::FixFilterFlags
- L222 _private prototype_ `void ApplySettingsFromConfigFiles(const FConfigFile& ConfigFile);`
- L223 _private prototype_ `void ApplySettingsFromFromCmdline();`
- L224 _private prototype_ `void ApplySettingsFromCVar();`
- L226 _private prototype_ `void ApplyDebugSettingsFromFromCmdline();`
- L228 _private prototype_ `void RegisterConsoleCommands();`
- L230 _private prototype_ `void OnUpdateDebugMissBackendsFromConsole(const TArray<FString>& Args, FOutputDevice& OutputDevice);`
- L231 _private prototype_ `void OnUpdateDebugMissChanceFromConsole(const TArray<FString>& Args, FOutputDevice& OutputDevice);`
- L232 _private prototype_ `void OnUpdateDebugMissCountFromConsole(const TArray<FString>& Args, FOutputDevice& OutputDevice);`
- L233 _private prototype_ `void UpdateBackendDebugState();`
- L235 _private prototype_ `bool ShouldDebugDisablePulling(FStringView BackendConfigName) const;`
- L236 _private prototype_ `bool ShouldDebugFailPulling();`
- L238 _private prototype_ `void MountBackends(const FConfigFile& ConfigFile);`
- L239 _private prototype_ `void ParseHierarchy(const FConfigFile& ConfigFile, const TCHAR* GraphName, const TCHAR* HierarchyKey, const TCHAR* LegacyHierarchyKey, const FRegistedFactories& FactoryLookupTable, FBackendArray& PushArray);`
- L240 _private prototype_ `bool CreateBackend(const FConfigFile& ConfigFile, const TCHAR* GraphName, const FString& ConfigEntryName, const FRegistedFactories& FactoryLookupTable, FBackendArray& PushArray);`
- L242 _private prototype_ `void AddBackend(TUniquePtr<IVirtualizationBackend> Backend, FBackendArray& PushArray);`
- L244 _private prototype_ `bool IsPersistentBackend(IVirtualizationBackend& Backend);`
- L246 _private prototype_ `void CachePayloads(TArrayView<FPushRequest> Requests, const IVirtualizationBackend* BackendSource, IVirtualizationBackend::EPushFlags Flags);`
- L248 _private prototype_ `bool TryCacheDataToBackend(IVirtualizationBackend& Backend, TArrayView<FPushRequest> Requests, IVirtualizationBackend::EPushFlags Flags);`
- L249 _private prototype_ `bool TryPushDataToBackend(IVirtualizationBackend& Backend, TArrayView<FPushRequest> Requests);`
- L251 _private prototype_ `void PullDataFromAllBackends(TArrayView<FPullRequest> Requests);`
- L252 _private prototype_ `void PullDataFromBackend(IVirtualizationBackend& Backend, TArrayView<FPullRequest> Requests, FText& OutErrors);`
- L262 _private prototype_ `ErrorHandlingResult OnPayloadPullError(const FPullRequestCollection& Requests, FStringView BackendErrors) const;`
- L264 _private prototype_ `bool ShouldVirtualizeAsset(const UObject* Owner) const;`
- L277 _private prototype_ `bool ShouldVirtualizePackage(const FPackagePath& PackagePath) const;` — Determines if a package path should be virtualized or not based on any exclusion/inclusion patterns that might have been set in UVirtualizationFilterSettings. If the path does not match any pattern set in UVirtualizationFilterSettings then use the default FilterMode to determine if the payload should be virtualized or not. @param PackagePath	The path of the package to check. This can be empty which would indicate that a payload is not owned by a specific package. @return				True if the package should be virtualized and false if the package path is excluded by the projects current filter set up.
- L288 _private prototype_ `bool ShouldVirtualize(FStringView Context) const;` — Determines if a package should be virtualized or not based on the given content. If the context can be turned into a package path then ::ShouldVirtualizePackage will be used instead. If the context is not a package path then we use the default FilterMode to determine if the payload should be virtualized or not. @return True if the context should be virtualized and false if not.
- L291 _private prototype_ `bool ShouldVirtualizeAsDefault() const;` — Determines if the default filtering behavior is to virtualize a payload or not
- L294 _private prototype_ `bool ShouldRetryWhenUnattended() const;` — Returns if the process will attempt to retry a failed pull when the process is unattended mode
- L296 _private prototype_ `void BroadcastEvent(TConstArrayView<FPullRequest> Ids, ENotification Event);`
- L302 _private member_ `bool bAllowPackageVirtualization;` — Are packages allowed to be virtualized when submitted to source control. Defaults to true.
- L316 _private prototype_ `FRIEND_ENUM_CLASS_FLAGS(ECachingPolicy);`
- L319 _private member_ `ECachingPolicy CachingPolicy;` — A bitfield describing when we push payloads to cached storage.
- L322 _private member_ `int64 MinPayloadLength;` — The minimum length for a payload to be considered for virtualization. Defaults to 0 bytes.
- L325 _private member_ `FString BackendGraphName;` — The name of the backend graph to load from the config ini file that will describe the backend hierarchy
- L328 _private member_ `FString VirtualizationProcessTag;` — The tag that will be returned when the virtualization process has run, commonly used to post fix changelist descriptions
- L331 _private member_ `EPackageFilterMode FilteringMode;` — The default filtering mode to apply if a payload is not matched with an option in UVirtualizationFilterSettings
- L334 _private member_ `bool bFilterMapContent;` — Should payloads in .umap files (or associated _BuildData files) be filtered out and never virtualized
- L337 _private member_ `bool bAllowSubmitIfVirtualizationFailed;` — Should file submits be allowed to continue if a call to TryVirtualizePackages fails
- L340 _private member_ `bool bLazyInitConnections;` — Should backends defer connecting to their services until first use
- L343 _private member_ `bool bUseLegacyErrorHandling;` — When true we do not display an error dialog on failed payload pulling and rely on the caller handling it
- L346 _private member_ `bool bForceCachingOnPull;` — When true IVirtualizationBackend::EPushFlags::Force will be passed to backends that need to cache payloads when pulling
- L349 _private member_ `bool bAllowBackendReconnection;` — When true backends will be able to try to reconnect to their service's if previous connection attempts failed
- L352 _private member_ `FString PullErrorAdditionalMsg;` — An additional error message to display when pulling payloads fails
- L355 _private member_ `static FString ConnectionHelpUrl;` — Optional url used to augment connection failure error messages
- L358 _private member_ `int32 UnattendedRetryCount = 0;` — The number of times to retry pulling when errors are encountered in an unattended process, values <0 disable the system
- L361 _private member_ `int32 UnattendedRetryTimer = 0;` — The how long (in seconds) to wait after payload pulling errors before retrying. Does nothing if 'UnattendedRetryCount' is disabled
- L366 _private member_ `FString ProjectName;` — The name of the current project
- L369 _private member_ `TSet<FName> DisabledAssetTypes;` — The names of all asset types that should not virtualize. See @IsDisabledForObject
- L372 _private member_ `TArray<TUniquePtr<IVirtualizationBackend>> AllBackends;` — All of the backends that were mounted during graph creation
- L375 _private member_ `FBackendArray CacheStorageBackends;` — Backends used for caching operations (must support push operations).
- L378 _private member_ `FBackendArray PersistentStorageBackends;` — Backends used for persistent storage operations (must support push operations).
- L384 _private member_ `FBackendArray PullEnabledBackends;` — The hierarchy of backends to pull from, this is assumed to be ordered from fastest to slowest and can contain a mixture of local cacheable and persistent backends
- L387 _private member_ `FOnNotification NotificationEvent;` — Our notification Event
- L390 _private member_ `mutable std::atomic<int32> UnattendedFailureMsgCount = 0;` — Track how many times we've displayed a message about failed payload pulls since the last successful pull (only used in unattended mode)
- L426 _private member_ `} DebugValues;`
- L433 _public prototype_ `static FString GetConnectionHelpUrl();` — Temp accessor for backends until we add a better system for connection failure notification. Note that this is not exposed outside of the module so that we can change/remove this easily in the future.

#### enum `UE::Virtualization::FVirtualizationManager::ErrorHandlingResult`  
`enum class ErrorHandlingResult`  
_L254-260_
- L257 _public enumerator_ `Retry = 0` — We should try to pull the failed payloads again
- L259 _public enumerator_ `AcceptFailedPayloads` — We should accept that some of the payloads failed and leave it to the calling system to handle

#### enum `UE::Virtualization::FVirtualizationManager::ECachingPolicy`  
`enum ECachingPolicy`  
_L304-314_
- L307 _public enumerator_ `None = 0` — Never push payloads to cached storage
- L309 _public enumerator_ `CacheOnPull = 1 << 0` — Cache payloads after they have been pulled from persistent storage
- L311 _public enumerator_ `CacheOnPush = 1 << 1` — Cache payloads right before they are pushed to persistent storage
- L313 _public enumerator_ `AlwaysCache = CacheOnPull | CacheOnPush`

#### struct `UE::Virtualization::FVirtualizationManager::FDebugValues`  
`struct FDebugValues`  
_L394-426_
- L397 _public member_ `TArray<IConsoleObject*> ConsoleObjects;` — All of the console commands/variables that we register, so they can be unregistered when the manager is destroyed
- L404 _public member_ `TArray<TPair<IConsoleVariable*, FDelegateHandle>> ConsoleDelegateHandles;` — Contains all of the delegate handles that we have bound to IConsoleVariable::OnChangedDelegate and need to be removed before it is safe to destroy the manager. Most likely due to having bound a lambda to the delegate that captured the FVirtualizationManager this pointer.
- L407 _public member_ `FCriticalSection ForceSingleThreadedCS;` — The critical section used to force single threaded access if bForceSingleThreaded is true
- L410 _public member_ `bool bSingleThreaded = false;` — When enabled all public operations will be performed as single threaded
- L416 _public member_ `bool bValidateAfterPush = false;` — When enabled we will immediately 'pull' each payload after it has been pushed to either local or persistent storage and compare it to the original payload source to make sure that it was uploaded correctly
- L419 _public member_ `TArray<FString> MissBackends;` — Array of backend names that should have their pull operation disabled
- L422 _public member_ `float MissChance;` — The chance that a payload pull can just 'fail' to allow for testing
- L425 _public member_ `std::atomic<int32> MissCount = 0;` — The number of upcoming payload pulls that should be failed

#### Free symbols / members of external scopes

- L154 _namespace_ `namespace UE`
- L154 _namespace_ `namespace Virtualization` (scope `UE`)
- L168 _prototype_ `bool LexTryParseString(EPackageFilterMode& OutValue, FStringView Buffer);` (scope `UE::Virtualization`) — Attempt to convert a string buffer to EPackageFilterMode

### `Source/Developer/Virtualization/Private/VirtualizationSourceControlBackend.h` (Private)


#### class `UE::Virtualization::FSourceControlBackend`  
`class FSourceControlBackend final : public IVirtualizationBackend`  
_L120-196_
- inherits: `IVirtualizationBackend`
- desc: This backend can be used to access payloads stored in source control. The backend doesn't 'check out' a payload file but instead will just download the payload as a binary blob. It is assumed that the files are stored with the same path convention as the file system backend, found in Utils::PayloadIdToPath. Ini file setup: 'Name'=(Type=P4SourceControl) Where 'Name' is the backend name in the hierarchy Required Values: DepotPath [string]				The path (in depot format) to the location where virtualized payloads are stored. [Default=""] ClientStream [string]:			Used when the payloads are stored in a stream based depot. It should contain the stream name to use when creating a workspace for payload submission. [Default=""] If the payloads are being stored in a depot with type 'stream' them config value 'ClientStream' must be set to a valid stream. The 'DepotPath' value can still be set to choose a specific location within that stream or when the stream name is not a valid depot path (such as virtual streams) If the payloads are not being stored in a 'stream' depot then only 'DepotPath' is required. Optional Values: Server [string]:					When set the backend will use this server address to connect to. When not set the backend will use the environment defaults. [Default=""] UsePartitionedClient [bool]:		When true the temporary workspace client created to submit payloads from will be created as a partitioned workspace which is less overhead on the source control server. If your server 
- L123 _public prototype_ `explicit FSourceControlBackend(FStringView ProjectName, FStringView ConfigName, FStringView InDebugName);`
- L124 _public prototype_ `virtual ~FSourceControlBackend() = default;`
- L129 _private prototype_ `virtual bool Initialize(const FString& ConfigEntry) override;`
- L131 _private prototype_ `virtual EConnectionStatus OnConnect() override;`
- L132 _private prototype_ `IVirtualizationBackend::EConnectionStatus OnConnectInternal(FString& InOutPort, FString& InOutUsername, bool bSaveConnectionSettings, FText& OutErrorMessage);`
- L134 _private prototype_ `virtual bool PushData(TArrayView<FPushRequest> Requests, EPushFlags Flags) override;`
- L135 _private prototype_ `virtual bool PullData(TArrayView<FPullRequest> Requests, EPullFlags Flags, FText& OutErrors) override;`
- L137 _private prototype_ `virtual bool DoesPayloadExist(const FIoHash& Id) override;`
- L139 _private prototype_ `virtual bool DoPayloadsExist(TArrayView<const FIoHash> PayloadIds, TArray<bool>& OutResults) override;`
- L143 _private prototype_ `bool TryApplySettingsFromConfigFiles(const FString& ConfigEntry);`
- L145 _private prototype_ `void CreateDepotPath(const FIoHash& PayloadId, FStringBuilderBase& OutPath);`
- L147 _private prototype_ `bool FindSubmissionWorkingDir(const FString& ConfigEntry);`
- L150 _private prototype_ `void OnConnectionError(FText ErrorMessage);` — Will display a FMessage notification to the user on the next valid engine tick to try and keep them aware of connection failures
- L153 _private member_ `TUniquePtr<ISourceControlProvider> SCCProvider;` — A source control connection owned by the backend
- L156 _private member_ `FString ProjectName;` — The name of the current project
- L159 _private member_ `FString DepotPathRoot;` — The path (in depot format) to where the virtualized payloads are stored in source control
- L162 _private member_ `FString ServerAddress;` — Address of the server to connect to
- L165 _private member_ `FString ClientStream;` — The stream containing the DepotRoot where the virtualized payloads are stored in source control
- L168 _private member_ `FString SubmissionRootDir;` — The root directory from which payloads are submitted.
- L171 _private member_ `FString IgnoreFileName = TEXT(".p4` — The name to use for the p4 ignore file
- L174 _private member_ `bool bUsePartitionedClient = true;` — Should we try to make the temp client partitioned or not?
- L177 _private member_ `bool bSuppressNotifications = false;` — When true, the backend will not raise a pop up notification on connection error
- L180 _private member_ `int32 MaxBatchCount = 100;` — The maximum number of files to send in a single source control operation
- L183 _private member_ `TUniquePtr<UE::Virtualization::FSemaphore> ConcurrentConnectionLimit;` — A counted semaphore that will limit the number of concurrent connections that we can make
- L186 _private member_ `int32 RetryCount = 2;` — The number of times to retry pulling a payload from the depot
- L189 _private member_ `int32 RetryWaitTimeMS = 100;` — The length of time (in milliseconds) to wait after each pull attempt before retrying.
- L192 _private member_ `bool bUseLocalIniFileSettings = true;` — When true we allow the revision control provider to read settings from the users local SourceControlSettings.ini file
- L195 _private member_ `bool bUseRetryConnectionDialog = false;` — When true, if the initial connection to the revision control provider fails we will show a slate dialog (if possible) to the user prompting for correct settings

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Virtualization` (scope `UE`)

### `Source/Developer/Virtualization/Private/VirtualizationSourceControlUtilities.h` (Private)


#### class `UE::Virtualization::Experimental::FVirtualizationSourceControlUtilities`  
`class FVirtualizationSourceControlUtilities : public IVirtualizationSourceControlUtilities`  
_L29-44_
- inherits: `IVirtualizationSourceControlUtilities`
- L32 _public prototype_ `FVirtualizationSourceControlUtilities() = default;`
- L33 _public prototype_ `~FVirtualizationSourceControlUtilities() = default;`
- L40 _private prototype_ `virtual bool SyncPayloadSidecarFile(const FPackagePath& PackagePath) override;` — Wrapper call around SyncPayloadSidecarFileInternal which will either call it directly or attempt to marshal it to the main thread if needed
- L43 _private prototype_ `bool SyncPayloadSidecarFileInternal(const FPackagePath& PackagePath);` — Effectively the override of IVirtualizationSourceControlUtilities::SyncPayloadSidecarFile

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Virtualization` (scope `UE`)
- L22 _prototype_ `bool TryCheckoutFiles(const TArray<FString>& FilesToCheckout, TArray<FText>& OutErrors, TArray<FString>* OutFilesCheckedOut);` (scope `UE::Virtualization`) — Utility function to make it easier to check out a number of files from revision control. Note that the function does not do anything to files that are already checked out. @param FilesToCheckout		A list of files to check out of revision control @param OutErrors				The function will place any errors encountered here @param OutFilesCheckedOut	An optional array, which if provided will be filled in with the list of files that were actually checked out from revision control. @return	True if the files were checked our OR revision control is not enabled. If revision control was enabled and we encountered errors, then the function will return false.
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Virtualization` (scope `UE`)
- L26 _namespace_ `namespace Experimental` (scope `UE::Virtualization`)

### `Source/Developer/Virtualization/Public/IVirtualizationBackend.h` (Public)


#### class `UE::Virtualization::IVirtualizationBackend`  
`class IVirtualizationBackend`  
_L28-290_
- desc: The interface to derive from to create a new backend implementation. Note that virtualization backends are instantiated FVirtualizationManager via IVirtualizationBackendFactory so each new backend derived from IVirtualizationBackend will also need a factory derived from IVirtualizationBackendFactory. You can either do this manually or use the helper macro 'UE_REGISTER_VIRTUALIZATION_BACKEND_FACTORY' to generate the code for you.
- L42 _public prototype_ `FRIEND_ENUM_CLASS_FLAGS(EOperations);`
- L63 _public prototype_ `FRIEND_ENUM_CLASS_FLAGS(EPushFlags);`
- L71 _public prototype_ `FRIEND_ENUM_CLASS_FLAGS(EPullFlags);`
- L75 _protected function_ `IVirtualizationBackend(FStringView InConfigName, FStringView InDebugName, EOperations InSupportedOperations) : ConfigName(InConfigName) , DebugName(InDebugName) , SupportedOperations(InSupportedOperations) , DebugDisabledOperations(EOperations::None)`
- L85 _public prototype_ `virtual ~IVirtualizationBackend() = default;`
- L99 _public prototype_ `virtual bool Initialize(const FString& ConfigEntry) = 0;` — This will be called during the setup of the backend hierarchy. The entry config file entry that caused the backend to be created will be passed to the method so that any additional settings may be parsed from it. Take care to clearly log any error that occurs so that the end user has a clear way to fix them. @param ConfigEntry	The entry for the backend from the config ini file that may contain additional settings. @return				Returning false indicates that initialization failed in a way that the backend will not be able to function correctly.
- L103 _public function_ `virtual void Connect() final` — `UE_DEPRECATED(5.6, "Call IVirtualizationBackend::TryConnect instead")`
- L118 _public function_ `EConnectionStatus TryConnect(bool bAllowReconnect)` — Attempt to connect the backend to its services if not already connected. @praram bAllowReconnect	When true the backend will attempt to connect to it's services even if it has previously failed to do so. When false the backend will only ever attempt to connect a single time with that result being final. @return The current connection status of the backend. @see EConnectionStatus
- L137 _public function_ `EConnectionStatus GetConnectionStatus() const` — Returns the connection status of the backend @return @see EConnectionStatus
- L146 _public prototype_ `virtual bool PushData(TArrayView<FPushRequest> Requests, EPushFlags Flags) = 0;` — @return True if all of the requests succeeded, false if one of more failed
- L171 _public prototype_ `virtual bool PullData(TArrayView<FPullRequest> Requests, EPullFlags Flags, FText& OutErrors) = 0;` — Assume that the array only has unique requests Will set request error value if there is a problem with loading it Returns false on critical error, otherwise true
- L180 _public prototype_ `virtual bool DoesPayloadExist(const FIoHash& Id) = 0;` — Checks if a payload exists in the backends storage. @param	Id	The identifier of the payload to check @return True if the backend storage already contains the payload, otherwise false
- L192 _public function_ `virtual bool DoPayloadsExist(TArrayView<const FIoHash> PayloadIds, TArray<bool>& OutResults)` — Checks if a number of payload exists in the backends storage. @param[in]	PayloadIds	An array of FIoHash that should be checked @param[out]	OutResults	An array to contain the result, true if the payload exists in the backends storage, false if not. This array will be resized to match the size of PayloadIds. @return True if the operation completed without error, otherwise false
- L216 _public function_ `bool DisableOperation(EOperations Operation)` — Disables operations on the backend @param Operation	The operation(s) to be disabled @return	True if at least one previously enabled operation was disabled by the call False if there was no change.
- L229 _public function_ `bool IsOperationSupported(EOperations Operation) const` — Returns true if the given operation is supported, this is set when the backend is created and should not change over it's life time.
- L235 _public function_ `void SetOperationDebugState(EOperations Operation, bool bIsDisabled)` — Enable or disable the given operation based on the 'bIsDisabled' parameter
- L249 _public function_ `bool IsOperationDebugDisabled(EOperations Operation) const` — Returns true if the given operation is disabled for debugging purposes
- L255 _public function_ `const FString& GetConfigName() const` — Returns a string containing the name of the backend as it appears in the virtualization graph in the config file
- L261 _public function_ `const FString& GetDebugName() const` — Returns a string that can be used to identify the backend for debugging and logging purposes
- L269 _private prototype_ `virtual EConnectionStatus OnConnect() = 0;` — Override to implement the backends connection code
- L274 _private member_ `FString ConfigName;` — The name assigned to the backend by the virtualization graph
- L277 _private member_ `FString DebugName;` — Combination of the backend type and the name used to create it in the virtualization graph
- L280 _private member_ `mutable UE::FMutex ConnectionMutex;` — Protects threaded access to 'ConnectionStatus'
- L283 _private member_ `EConnectionStatus ConnectionStatus = EConnectionStatus::None;` — The status of the connection to the backends service
- L286 _private member_ `EOperations SupportedOperations;` — The operations that this backend supports
- L289 _private member_ `EOperations DebugDisabledOperations;` — The operations that have been disabled for debugging purposes

#### enum `UE::Virtualization::IVirtualizationBackend::EOperations`  
`enum class EOperations : uint8`  
_L32-40_
- desc: Enum detailing which operations a backend can support
- L35 _public enumerator_ `None = 0` — Supports no operations, this should only occur when debug settings are applied
- L37 _public enumerator_ `Push = 1 << 0` — Supports only push operations
- L39 _public enumerator_ `Pull = 1 << 1` — Supports only pull operations

#### enum `UE::Virtualization::IVirtualizationBackend::EConnectionStatus`  
`enum class EConnectionStatus : uint8`  
_L45-53_
- desc: Status of the backends connection to its services
- L48 _public enumerator_ `None` — No connection attempt has been made
- L50 _public enumerator_ `Error` — The previous connection attempt ended with an error
- L52 _public enumerator_ `Connected` — The connection has been made successfully

#### enum `UE::Virtualization::IVirtualizationBackend::EPushFlags`  
`enum class EPushFlags : uint32`  
_L56-61_
- desc: Specialize pushing behavior, @See IVirtualizationBackend::PushData
- L58 _public enumerator_ `None = 0`
- L60 _public enumerator_ `Force = 1 << 0` — Backends should not test payloads for existence and just assume that they need re-uploading

#### enum `UE::Virtualization::IVirtualizationBackend::EPullFlags`  
`enum class EPullFlags : uint32`  
_L66-69_
- desc: Specialize pulling behavior, @See IVirtualizationBackend::PullData
- L68 _public enumerator_ `None = 0`

#### class `UE::Virtualization::IVirtualizationBackendFactory`  
`class IVirtualizationBackendFactory : public IModularFeature`  
_L300-314_
- inherits: `IModularFeature`
- desc: Derive from this interface to implement a factory to return a backend type. An instance of the factory should be created and then registered to IModularFeatures with the feature name "VirtualizationBackendFactory" to give 'FVirtualizationManager' access to it. The macro 'UE_REGISTER_VIRTUALIZATION_BACKEND_FACTORY' can be used to create a factory easily if you do not want to specialize the behavior.
- L310 _public prototype_ `virtual TUniquePtr<IVirtualizationBackend> CreateInstance(FStringView ProjectName, FStringView ConfigName) = 0;` — Creates a new backend instance. @param ProjectName	The name of the current project @param ConfigName	The name given to the back end in the config ini file @return A new backend instance
- L313 _public prototype_ `virtual FName GetName() = 0;` — Returns the name used to identify the type in config ini files

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Virtualization` (scope `UE`)
- L316 _prototype_ `ENUM_CLASS_FLAGS(IVirtualizationBackend::EOperations);` (scope `UE::Virtualization`)
- L327 _macro_ `#define UE_REGISTER_VIRTUALIZATION_BACKEND_FACTORY(BackendClass, ConfigName) \` — This macro is used to generate a backend factories boilerplate code if you do not need anything more than the default behavior. As well as creating the class, a single instance will be created which will register the factory with 'IModularFeatures' so that it is ready for use. @param BackendClass The name of the class derived from 'IVirtualizationBackend' that the factory should create @param The name used in config ini files to reference this backend type.
- L342 _macro_ `#define UE_REGISTER_VIRTUALIZATION_BACKEND_FACTORY_LEGACY_IMPL(FactoryName, BackendClass, LegacyConfigName, ConfigName) \`
- L371 _macro_ `#define UE_REGISTER_VIRTUALIZATION_BACKEND_FACTORY_LEGACY(BackendClass, LegacyConfigName, ConfigName) \` — This macro can be used to change the config name used to create backends while allowing older config file entries to continue working. If this factory is used to instantiate a backend then we will log a warning to the user so that they can update their config file. @param BackendClass		The name of the class derived from 'IVirtualizationBackend' that the factory should create. @param LegacyConfigName	The old name that 'ConfigName' is now replacing. @param ConfigName		The name used in config ini files to reference this backend type.

### `Source/Developer/Virtualization/Public/VirtualizationUtilities.h` (Public)


#### enum `UE::Virtualization::Utils::ETrailerFailedReason`  
`enum class ETrailerFailedReason : uint8`  
_L56-66_
- L59 _public enumerator_ `NotFound` — Could not open the package for reading
- L61 _public enumerator_ `InvalidSummary` — The header of the package (summary) could not be read or was otherwise corrupted
- L63 _public enumerator_ `OutOfDate` — The package predates package version 1002 in which the package trailer was introduced
- L65 _public enumerator_ `Unknown` — The reason for the missing package trailer could not be determined

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API VIRTUALIZATION_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Virtualization` (scope `UE`)
- L15 _namespace_ `namespace Utils` (scope `UE::Virtualization`)
- L34 _prototype_ `void PayloadIdToPath(const FIoHash& Id, FStringBuilderBase& OutPath);` (scope `UE::Virtualization::Utils`) — Converts a FIoHash into a file path. This utility will take an FIoHash and return a file path that is 3 directories deep. The first six characters of the id will be used to create the directory names, with each directory using two characters. The remaining thirty four characters will be used as the file name. Lastly the extension '.payload' will be applied to complete the path/ Example: FIoHash 0139d6d5d477e32dfd2abd3c5bc8ea8507e8eef8 becomes 01/39/d6/d5d477e32dfd2abd3c5bc8ea8507e8eef8.payload' @param	Id The payload identifier used to create the file path. @param	OutPath Will be reset and then assigned the resulting file path. The string builder must have a capacity of at least 52 characters to avoid reallocation.
- L44 _prototype_ `FString PayloadIdToPath(const FIoHash& Id);` (scope `UE::Virtualization::Utils`) — Converts a FIoHash into a file path. See above for further details @param	Id The payload identifier used to create the file path. @return	The resulting file path.
- L53 _prototype_ `void GetFormattedSystemError(FStringBuilderBase& SystemErrorMessage);` (scope `UE::Virtualization::Utils`) — Fill in the given string builder with the human readable message of the current system code, followed by the code value itself. In the system value is currently 0, then we assume that it was cleared before this was able to be called and write that the error is unknown instead of assuming that the operation was a success.
- L74 _prototype_ `ETrailerFailedReason FindTrailerFailedReason(const FPackagePath& PackagePath);` (scope `UE::Virtualization::Utils`) — Utility that returns the reason why a given package does not have a package trailer. Note that it does not actually try to load the trailer or validate that the trailer is in fact missing and assumes that the caller previously attempted to a call to load a trailer from the package but it failed.
- L81 _prototype_ `bool ExpandEnvironmentVariables(FStringView InputPath, FStringBuilderBase& OutExpandedPath);` (scope `UE::Virtualization::Utils`) — Parse the given path and expand any environment variables found with the format $(EnvVarName). If the variable cannot be found the function will return false and OutExpandedPath will be reset.
- L87 _prototype_ `bool IsProcessInteractive();` (scope `UE::Virtualization::Utils`) — Returns true if the process is interactive and we should display error dialogs to the user.
- L100 _prototype_ `bool TryFindProject(const FString& PackagePath, const FString& ProjectExtension, FString& OutProjectFilePath, FString& OutPluginFilePath);` (scope `UE::Virtualization::Utils`) — Find the project file for the project that contains the provided package file. Note that this only intended to work for package files as it makes several assumptions about the path conventions in order to speed up the search. @PackagePath			Path of a package file to start searching from. The file must be stored under a /content/ directory to be considered valid. @ProjectExtension	The extension that the project file may have. @OutProjectFilePath	The project path will be written to this string if found. @OutPluginFilePath	If the package is stored in a plugin then the path to it's '.uplugin' file will be written to this string. @return				True if a project file is found otherwise it will return false.
- L113 _prototype_ `bool TryFindProject(const FString& PackagePath, TConstArrayView<FString> ProjectExtensions, FString& OutProjectFilePath, FString& OutPluginFilePath);` (scope `UE::Virtualization::Utils`) — Find the project file for the project that contains the provided package file. Note that this only intended to work for package files as it makes several assumptions about the path conventions in order to speed up the search. @PackagePath			Path of a package file to start searching from. The file must be stored under a /content/ directory to be considered valid. @ProjectExtensions	An array of potential extensions that the project file may have. @OutProjectFilePath	The project path will be written to this string if found. @OutPluginFilePath	If the package is stored in a plugin then the path to it's '.uplugin' file will be written to this string. @return				True if a project file is found otherwise it will return false.
