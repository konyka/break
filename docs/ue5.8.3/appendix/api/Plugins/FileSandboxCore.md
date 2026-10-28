# Plugins / FileSandboxCore

- module root: `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore`
- headers: 80; symbols: 945
- symbol kinds: class=25, delegate=8, enum=16, enumerator=61, function=210, macro=9, member=144, namespace=147, prototype=271, struct=41, typedef=12, variable=1
- PrivateDependencyModuleNames: AssetRegistry, DirectoryWatcher, Engine, EngineSettings, FileUtilities, Json, JsonUtilities, RenderCore, SlateCore, SourceControl, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Private/Data/AbsoluteFilePathArray.h` (Private)


#### struct `FFileSandboxCore_AbsoluteFilePathArray`  
`struct FFileSandboxCore_AbsoluteFilePathArray`  
_L10-41_
- reflection: `USTRUCT()`
- desc: Keeps an array of absolute file paths. Each path is unique.
- L14 _public function_ `const TArray<FString>& GetFiles() const`
- L17 _public function_ `bool Add(const FString& InPath)` — @return Whether the path was added, i.e. was not already present.
- L25 _public function_ `bool Remove(const FString& InPath)` — @return Whether anything was removed.
- L31 _public function_ `void Empty()`
- L40 _private member_ `TArray<FString> Files;` — `UPROPERTY()` — Absolute file paths.

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Private/Data/ManifestData.h` (Private)


#### struct `FFileSandboxCore_ManifestData`  
`struct FFileSandboxCore_ManifestData`  
_L16-68_
- reflection: `USTRUCT()`
- desc: Internal bookkeeping data for the sandbox logic. This data is owned by the sandbox system and should not be directly modified via public API.
- L25 _public member_ `FFileSandboxCore_TimedAbsoluteFilePathArray DeletedFiles;` — `UPROPERTY()` — Absolute non-sandbox paths to files deleted in sandbox. Also saved the timestamp of the remove operation.
- L29 _public member_ `FFileSandboxCore_AbsoluteFilePathArray ModifiedFiles;` — `UPROPERTY()` — Absolute non-sandbox paths to files modified in sandbox.
- L33 _public member_ `FFileSandboxCore_AbsoluteFilePathArray AddedFiles;` — `UPROPERTY()` — Absolute non-sandbox paths to files added in sandbox.
- L46 _public member_ `FFileSandboxCore_VersionInfo VersionInfo;` — `UPROPERTY()` — Version info when this sandbox was created. Holds info about the file version, engine version, and custom versions (for FArchives). This information is saved in the manifest to minimize the risk of API users directly editing and corrupting it. It could also have been saved in the metadata file but that has API for mutating it (= risk of corruption / mutation via API). May be needed to parse the content in FFileSandboxCore_SandboxMetaData. TODO UE-350242: This information can also be used to reject loading a sandbox with newer version info than the current engine version.
- L54 _public member_ `FFileSandboxCore_MountPointsInfo MountPoints;` — `UPROPERTY()` — The mount points that were referenced by either DeletedFiles, ModifiedFiles, or AddedFiles when the manifest was last saved. This information is used to migrate file paths when a sandbox instance is created in case a mount point location changes, e.g. when importing a sandbox or if the user changes the location of the underlying uproject.
- L56 _public function_ `void Empty()`
- L63 _public function_ `void Initialize()`

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Private/Data/MountPointInfo.h` (Private)


#### struct `FFileSandboxCore_MountPoint`  
`struct FFileSandboxCore_MountPoint`  
_L11-25_
- reflection: `USTRUCT()`
- desc: Describes a single mount point.
- L17 _public member_ `FString MountName;` — `UPROPERTY()` — Logical name of the mount point, e.g. "/Game/"
- L21 _public member_ `FString RootPath;` — `UPROPERTY()` — Absolute path to the root of the mount point. e.g. "C:/MyProject/Content"
- L23 _public prototype_ `FFileSandboxCore_MountPoint() = default;`
- L24 _public function_ `FFileSandboxCore_MountPoint(FString InMountName, FString InRootPath) : MountName(MoveTemp(InMountName)), RootPath(MoveTemp(InRootPath))`

#### struct `FFileSandboxCore_MountPointsInfo`  
`struct FFileSandboxCore_MountPointsInfo`  
_L29-38_
- reflection: `USTRUCT()`
- desc: Holds mount points the engine has.
- L34 _public member_ `TArray<FFileSandboxCore_MountPoint> MountPoints;` — `UPROPERTY()`
- L37 _public prototype_ `void Initialize();` — Adds all mount points currently active to MountPoints.

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Private/Data/TimedAbsoluteFilePathArray.h` (Private)


#### struct `FFileSandboxCore_TimedAbsoluteFilePathArray`  
`struct FFileSandboxCore_TimedAbsoluteFilePathArray`  
_L11-83_
- reflection: `USTRUCT()`
- desc: Keeps an array of absolute file paths and their respective timestamps. Each path is unique.
- L15 _public function_ `const TArray<FString>& GetFiles() const`
- L17 _public function_ `const TArray<FDateTime>& GetTimestamps() const`
- L18 _public function_ `bool AreTimestampsValid() const`
- L21 _public function_ `TOptional<FDateTime> GetTimestamp(const FString& InPath) const` — @return The timestamp of the file, or unset.
- L29 _public function_ `bool Add(const FString& InPath, const FDateTime& InTimestamp = FDateTime::UtcNow())` — @return Whether the path was added, i.e. was not already present.
- L44 _public function_ `bool Remove(const FString& InPath)` — @return Whether anything was removed.
- L63 _public function_ `void Empty()`
- L73 _private member_ `TArray<FString> Files;` — `UPROPERTY()` — Absolute file paths.
- L82 _private member_ `TArray<FDateTime> Timestamps;` — `UPROPERTY()` — The times that the files were changed in local time. Under normal circumstances, this is equal length to Files. Keep in mind that the user may have edited the file in the manifest, in which case the values in this array are useless.

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Private/FileSandboxCoreModule.h` (Private)


#### class `UE::FileSandboxCore::FFileSandboxCoreModule`  
`class FFileSandboxCoreModule : public IFileSandboxCoreModule`  
_L10-31_
- inherits: `IFileSandboxCoreModule`
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L20 _public function_ `virtual ISandboxManager& GetSandboxManager() override`
- L21 _public function_ `virtual ISandboxRepository& GetDefaultSandboxRepository() override`
- L27 _private member_ `TUniquePtr<FSandboxManager> SandboxManager;` — Public API for interacting with the sandbox instance.
- L30 _private member_ `TUniquePtr<ISandboxRepository> DefaultRepository;` — Caches the sandboxes in the default sandbox directory.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Private/LogFileSandbox.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogFileSandbox, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogFileSandbox, Log, All);`

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Private/Repository/NaiveSandboxRepository.h` (Private)


#### class `UE::FileSandboxCore::FNaiveSandboxRepository`  
`class FNaiveSandboxRepository : public ISandboxRepository, public FNoncopyable`  
_L20-50_
- inherits: `ISandboxRepository,FNoncopyable`
- desc: Naive implementation that always reads the disk and does no caching. Never invokes OnSandboxMetaDataChanged. Used when directory watching is not possible.
- L24 _public prototype_ `explicit FNaiveSandboxRepository(FString InBaseDirectory, ISandboxManager& InManager UE_LIFETIMEBOUND);`
- L25 _public prototype_ `~FNaiveSandboxRepository();`
- L28 _public prototype_ `virtual void ForEachSandbox(TFunctionRef<EBreakBehavior(const FString& InRootPath, const FSandboxMetaInfo&)> InProcessSandboxes) override;`
- L29 _public prototype_ `virtual int32 NumSandboxes() const override;`
- L30 _public prototype_ `virtual bool ReadMetaData(const FString& InRootPath, TFunctionRef<void(const FSandboxMetaInfo&)> InProcessMetadata) override;`
- L31 _public function_ `virtual FOnSandboxesChanged& OnSandboxesChanged() override`
- L32 _public function_ `virtual FOnSandboxMetaDataChanged& OnSandboxMetaDataChanged() override`
- L38 _private member_ `const FString BaseDirectory;` — The base directory in which to look for sandboxes. Only looks at the top-level, i.e. not recursively.
- L41 _private member_ `ISandboxManager& Manager;` — Sandbox manager. Used to detect when a sandbox is created.
- L44 _private member_ `FOnSandboxesChanged OnSandboxesChangedDelegate;` — Invoked when the known sandboxes changes (removed, discovered, etc.)
- L46 _private member_ `FOnSandboxMetaDataChanged OnSandboxMetaDataChangedDelegate;` — Invoked when a sandbox's metadata changes.
- L49 _private prototype_ `void OnSandboxStartup(ISandboxInstance& SandboxInstance) const;` — Callback when a sandbox is started.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Private/Repository/WatchedSandboxRepository.h` (Private)


#### class `UE::FileSandboxCore::FWatchedSandboxRepository`  
`class FWatchedSandboxRepository : public ISandboxRepository, public FNoncopyable`  
_L20-94_
- inherits: `ISandboxRepository,FNoncopyable`
- desc: Simple directory watcher that detects when sandboxes are added, removed, and metadata file edited.
- L24 _public prototype_ `explicit FWatchedSandboxRepository(FString InBaseDirectory, ISandboxManager& InSandboxManager UE_LIFETIMEBOUND);`
- L28 _public prototype_ `virtual void ForEachSandbox(TFunctionRef<EBreakBehavior(const FString& InRootPath, const FSandboxMetaInfo& MetaData)> InProcessSandboxes) override;`
- L29 _public function_ `virtual int32 NumSandboxes() const override`
- L30 _public prototype_ `virtual bool ReadMetaData(const FString& InRootPath, TFunctionRef<void(const FSandboxMetaInfo&)> InProcessMetadata) override;`
- L31 _public function_ `virtual FOnSandboxesChanged& OnSandboxesChanged() override`
- L32 _public function_ `virtual FOnSandboxMetaDataChanged& OnSandboxMetaDataChanged() override`
- L38 _private member_ `const FString BaseDirectory;` — The base directory in which to look for sandboxes. Only looks at the top-level, i.e. not recursively.
- L41 _private member_ `ISandboxManager& SandboxManager;` — Used to be notified when a sandbox directory is created since the sandbox watcher may not always fire immediately.
- L52 _private member_ `TArray<FSandboxData> CachedSandboxData;` — Cached sandbox data. Updated whenever info changes on disk.
- L55 _private member_ `const FScopedWatchedDirectory WatchedBaseDirectory;` — Watcher for BaseDirectory
- L60 _private member_ `TArray<FScopedWatchedDirectory> WatchedSubDirectories;` — Sub-directories were watching in WatchedBaseDirectory. All directories in the base directory are always watched so we can detect when a new sandbox is created there.
- L62 _private member_ `TArray<FScopedWatchedDirectory> PendingDirectoryWatchersToUnregister;` — The directory that are supposed to be unregistered at end of frame.
- L65 _private member_ `FOnSandboxesChanged OnSandboxesChangedDelegate;` — Invoked when the known sandboxes changes (removed, discovered, etc.)
- L67 _private member_ `FOnSandboxMetaDataChanged OnSandboxMetaDataChangedDelegate;` — Invoked when a sandbox's metadata changes.
- L70 _private prototype_ `void RescanBaseDirectory();` — Fully rebuilds all directory data, analzying all directory, parsing all metadata files, etc.
- L72 _private prototype_ `void AddSandboxIfExists(const FString& InDirectory);` — Adds CachedSandboxData entry if it contains a sandbox. Also starts listening for file changes.
- L75 _private prototype_ `int32 IndexOf(const FString& InDirectory) const;` — @return Index to CachedSandboxData entry that contains the InDirectory (relative or absolute).
- L78 _private prototype_ `void OnBaseDirectoryChanged(const TArray<FFileChangeData>& InChanges);` — Invoked when a change is made in the base directory.
- L80 _private prototype_ `void UpdateCacheFromChangedBaseDirectory(const TArray<FFileChangeData>& InChanges);` — Checks all reported changes made to directories with the goal of detecting added or removed sandboxes.
- L82 _private prototype_ `void UpdateWatchedDirectories();` — Ensures all direct sub-directories in the base directory have a directory watcher set up.
- L85 _private prototype_ `void OnSandboxDirectoryChanged(const TArray<FFileChangeData>& InChanges, FString InSandboxPath);` — Invoked when a change is made in any of the sandbox directories. Used to update metadata.
- L87 _private prototype_ `bool DetectMetaDataFileChange(int32 InSandboxIndex, const TArray<FFileChangeData>& InChanges, const FString& InSandboxPath);` — Checks whether a change has been reported on the metadata file.
- L89 _private prototype_ `bool DetectManifestFileChange(int32 InSandboxIndex, const TArray<FFileChangeData>& InChanges, const FString& InSandboxPath);` — Checks whether a change has been reported for the manifest file.
- L92 _private prototype_ `void OnSandboxStartup(ISandboxInstance& SandboxInstance);` — Handles a sandbox being created.
- L93 _private prototype_ `void OnEndOfFrame();`

#### struct `UE::FileSandboxCore::FWatchedSandboxRepository::FSandboxData`  
`struct FSandboxData`  
_L43-50_
- L46 _public member_ `FString AbsPath;` — Absolute path to the sandbox root directory, i.e. the directory containing the metadata file.
- L49 _public member_ `FSandboxMetaInfo CachedData;` — Cached info about the sandbox, such as of the sandbox metadata file (to avoid constant JSON parsing, file loading, etc.)

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Private/Sandbox/Persist/DiffUtils.h` (Private)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L19 _typedef_ `using FHandleFilePathSignature = EBreakBehavior(const FSandboxedPlatformFilePath& InPath);` (scope `UE::FileSandboxCore`)
- L31 _prototype_ `void AnalyzeFilesMarkedRemoved( IPlatformFile& InPlatformFile, const TSet<FNonSandboxPath>& InFilesMarkedForRemove, TFunctionRef<EBreakBehavior(const FNonSandboxPath&)> InHandleRemovedFile );` (scope `UE::FileSandboxCore`) — Analyzes the file action the sandbox system would perform on files previously marked for remove. This compares whether the non-sandbox path still exists, i.e. whether the file was already removed (externally). This is useful if you're the state from the manifest file and need to compare against the current disk state. @param InPlatformFile The lower level platform file, i.e. the one that FSandboxPlatformFile wraps. @param InFilesMarkedForRemove The files to analyze. @param InHandleRemovedFile Invoked for each file that still should be marked as removed.
- L36 _prototype_ `void AnalyzeFilesMarkedRemoved( IPlatformFile& InPlatformFile, const TConstArrayView<FNonSandboxPath>& InFilesMarkedForRemove, TFunctionRef<EBreakBehavior(const FNonSandboxPath&)> InHandleRemovedFile );` (scope `UE::FileSandboxCore`)
- L53 _prototype_ `void ScanForEditedOrAddedFiles( IPlatformFile& InPlatformFile, const FSandboxedPlatformFilePath& InSandboxMountPoint, TFunctionRef<FHandleFilePathSignature> InHandleEditedFile, TFunctionRef<FHandleFilePathSignature> InHandleAddedFile );` (scope `UE::FileSandboxCore`) — Recursively iterates the files in the mount point and determines whether the present files would be - editing the non-sandbox counterpart, or - adding a new file to the non-sandbox. This is useful if you're the state from the manifest file and need to compare against the current disk state. @param InPlatformFile The lower level platform file, i.e. the one that FSandboxPlatformFile wraps. @param InSandboxMountPoint The sandbox mountpoint @param InHandleEditedFile Invoked for each file that should be marked as edited. @param InHandleAddedFile Invoked for each file that should be marked as added.
- L61 _prototype_ `void ScanForEditedOrAddedFiles( IPlatformFile& InPlatformFile, TConstArrayView<FSandboxMountPoint> InSandboxMountPoints, TFunctionRef<FHandleFilePathSignature> InHandleEditedFile, TFunctionRef<FHandleFilePathSignature> InHandleAddedFile );` (scope `UE::FileSandboxCore`) — Utility overload for FSandboxPlatformFile to pass in all of its mount points.
- L73 _prototype_ `void EnumerateFileChanges( IPlatformFile& InPlatformFile, const FString& InSandboxRootPath, const FFileSandboxCore_ManifestData& InManifest, TFunctionRef<EBreakBehavior(const FSandboxedFileChangeInfo& InFileInfo)> InProcess, EFileEnumerationFlags InFlags = EFileEnumerationFlags::All );` (scope `UE::FileSandboxCore`) — Shared logic for determining the effective file changes. @see ISandboxInstance::EnumerateFileChanges. @see ISandboxManager::EnumerateFileChanges.

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Private/Sandbox/Persist/DiscardUtils.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L20 _prototype_ `void DiscardAddedAndModifiedPaths( TConstArrayView<FString> InFilesToDiscard, TConstArrayView<FSandboxMountPoint> InMountPoints, IPlatformFile& InLowerLevel, TArray<FName>& OutPackagesPendingHotReload, TArray<FName>& OutPackagesPendingPurge, TFunctionRef<void(const FSandboxedPlatformFilePath& Path, EFileChangeAction Action)> InProcessFileChangeCallback = [](const FSandboxedPlatformFilePath&, EFileChangeAction){} );` (scope `UE::FileSandboxCore`) — Discards files that have been added or edited in the sandbox. @param InFilesToDiscard Relative or absolute non-sandbox paths. If left empty, revert all files.
- L24 _function_ `TConstArrayView<FString> InFilesToDiscard, TConstArrayView<FSandboxMountPoint> InMountPoints, IPlatformFile& InLowerLevel, TArray<FName>& OutPackagesPendingHotReload, TArray<FName>& OutPackagesPendingPurge, TFunctionRef<void(const FSandboxedPlatformFilePath& Path, EFileChangeAction Action)> InProcessFileChangeCallback = [](const FSandboxedPlatformFilePath&, EFileChangeAction)` (scope `UE::FileSandboxCore`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Private/Sandbox/Persist/LogPersistFeedback.h` (Private)


#### class `UE::FileSandboxCore::FLogPersistFeedback`  
`class FLogPersistFeedback : public IPersistFeedback`  
_L12-70_
- inherits: `IPersistFeedback`
- L17 _public function_ `virtual void StartFile(const TCHAR* InFilename) override`
- L21 _public function_ `virtual void HandleSuccess(const TCHAR* InFilename) override`
- L25 _public function_ `virtual void HandleError_CheckoutNotAllowed(const TCHAR* InFilename) override`
- L29 _public function_ `virtual void HandleError_Checkout(const TCHAR* InFilename) override`
- L33 _public function_ `virtual void HandleError_Revert(const TCHAR* InFilename) override`
- L37 _public function_ `virtual void HandleError_MarkForAdd(const TCHAR* InFilename) override`
- L41 _public function_ `virtual void HandleError_DeleteSCC(const TCHAR* InFilename) override`
- L45 _public function_ `virtual void HandleError_MakeWritable(const TCHAR* InFilename) override`
- L49 _public function_ `virtual void HandleError_MoveFile(const TCHAR* InToFilename, const TCHAR* InFromFilename) override`
- L54 _public function_ `virtual void HandleError_DeleteFile(const TCHAR* InFilename) override`
- L63 _private function_ `static FString GetErrorMessage()`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Private/Sandbox/Persist/PersistUtils.h` (Private)


#### enum `UE::FileSandboxCore::EPersistFlags`  
`enum class EPersistFlags : uint8`  
_L18-27_
- L20 _public enumerator_ `None`
- L26 _public enumerator_ `RetainChangedFiles = 1 << 0` — If set, added & edited files are retained in the sandbox directory on persist, i.e. sandboxed files are copied to the non-sandbox files. If unset, added & edited files are removed from the sandbox directory on persist, i.e. sandboxed files are moved to the non-sandbox files.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L28 _prototype_ `ENUM_CLASS_FLAGS(EPersistFlags);` (scope `UE::FileSandboxCore`)
- L31 _prototype_ `bool AddFileWithSCC( IPlatformFile& InPlatformFile, ISourceControlProvider& InSourceControlProvider, IPersistFeedback& InErrorHandler, const TCHAR* InToFilename, const TCHAR* InFromFilename, EPersistFlags InFlags = EPersistFlags::None );` (scope `UE::FileSandboxCore`) — Persists a file that is missing from the non-sandbox but exists in the sandbox. Registers the changes with Source Control if enabled.
- L37 _prototype_ `bool EditFileWithSCC( IPlatformFile& InPlatformFile, ISourceControlProvider& InSourceControlProvider, IPersistFeedback& InErrorHandler, const TCHAR* InToFilename, const TCHAR* InFromFilename, bool bMarkWriteable, EPersistFlags InFlags = EPersistFlags::None );` (scope `UE::FileSandboxCore`) — Persists a file that exists in both the non-sandbox and sandbox. Registers the changes with Source Control if enabled.
- L44 _prototype_ `bool DeleteFileWithSCC( IPlatformFile& InPlatformFile, ISourceControlProvider& InSourceControlProvider, IPersistFeedback& InErrorHandler, const TCHAR* InFilename );` (scope `UE::FileSandboxCore`) — Persists a file that exists in non-sandbox but was removed in the sandbox. Registers the changes with Source Control if enabled.
- L55 _prototype_ `bool MoveSandboxFileToNonSandbox( IPlatformFile& PlatformFile, IPersistFeedback& InErrorHandler, const TCHAR* InToFilename, const TCHAR* InFromFilename, EPersistFlags InFlags = EPersistFlags::None );` (scope `UE::FileSandboxCore`) — Moves InFromFilename to InToFileName. After successful operation, InToFileName has the file content that InFromFilename previously had. Depending on the flags InFromFilename stays in the sandbox, and continues to be tracked as change, or is removed.

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Private/Sandbox/Platform/SanboxedFilePathUtils.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L14 _prototype_ `bool IsFileInMountPoint(const FString& InNonSandboxFilePath, const FSandboxedPlatformFilePath& InMountPointRoot);` (scope `UE::FileSandboxCore`) — @return Whether InNonSandboxFilePath is a file path to InMountPointRoot
- L17 _prototype_ `TOptional<FSandboxedPlatformFilePath> MakeSandboxedFilePathIfInMountPoint( const FString& InNonSandboxFilePath, const FSandboxedPlatformFilePath& InMountPointRoot );` (scope `UE::FileSandboxCore`) — @return Sandboxed file path if InNonSandboxFilePath is under InMountPointRoot.

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Private/Sandbox/Platform/SandboxMountPoint.h` (Private)


#### struct `UE::FileSandboxCore::FSandboxMountPoint`  
`struct FSandboxMountPoint`  
_L10-17_
- L13 _public member_ `FSandboxedPlatformFilePath Path;` — Sandbox path
- L16 _public member_ `FDelegateHandle OnDirectoryChangedHandle;` — Sandbox directory watcher delegate handle (if any)

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Private/Sandbox/Platform/SandboxPlatformFile.h` (Private)


#### class `UE::FileSandboxCore::FSandboxPlatformFile`  
`class FSandboxPlatformFile : public IPlatformFile`  
_L33-259_
- inherits: `IPlatformFile`
- L37 _public prototype_ `explicit FSandboxPlatformFile(const FString& InSandboxRootPath);`
- L45 _public prototype_ `virtual void SetSandboxEnabled(bool bInEnabled) override;`
- L46 _public prototype_ `virtual bool IsSandboxEnabled() const override;`
- L47 _public prototype_ `virtual bool Initialize(IPlatformFile* Inner, const TCHAR* CmdLine) override;`
- L48 _public prototype_ `virtual void Tick() override;`
- L49 _public prototype_ `virtual IPlatformFile* GetLowerLevel() override;`
- L50 _public prototype_ `virtual void SetLowerLevel(IPlatformFile* NewLowerLevel) override;`
- L51 _public prototype_ `virtual const TCHAR* GetName() const override;`
- L52 _public prototype_ `virtual bool FileExists(const TCHAR* Filename) override;`
- L53 _public prototype_ `virtual int64 FileSize(const TCHAR* Filename) override;`
- L54 _public prototype_ `virtual bool DeleteFile(const TCHAR* Filename) override;`
- L55 _public prototype_ `virtual bool IsReadOnly(const TCHAR* Filename) override;`
- L56 _public prototype_ `virtual bool SetReadOnly(const TCHAR* Filename, bool bNewReadOnlyValue) override;`
- L57 _public prototype_ `virtual bool MoveFile(const TCHAR* To, const TCHAR* From) override;`
- L58 _public prototype_ `virtual FDateTime GetTimeStamp(const TCHAR* Filename) override;`
- L59 _public prototype_ `virtual void SetTimeStamp(const TCHAR* Filename, FDateTime DateTime) override;`
- L60 _public prototype_ `virtual FDateTime GetAccessTimeStamp(const TCHAR* Filename) override;`
- L61 _public prototype_ `virtual FString GetFilenameOnDisk(const TCHAR* Filename) override;`
- L62 _public prototype_ `virtual IFileHandle* OpenRead(const TCHAR* Filename, bool bAllowWrite = false) override;`
- L63 _public prototype_ `virtual IFileHandle* OpenReadNoBuffering(const TCHAR* Filename, bool bAllowWrite = false) override;`
- L64 _public prototype_ `virtual IFileHandle* OpenWrite(const TCHAR* Filename, bool bAppend = false, bool bAllowRead = false) override;`
- L65 _public prototype_ `virtual bool DirectoryExists(const TCHAR* Directory) override;`
- L66 _public prototype_ `virtual bool CreateDirectory(const TCHAR* Directory) override;`
- L67 _public prototype_ `virtual bool DeleteDirectory(const TCHAR* Directory) override;`
- L68 _public prototype_ `virtual FFileStatData GetStatData(const TCHAR* FilenameOrDirectory) override;`
- L69 _public prototype_ `virtual bool IterateDirectory(const TCHAR* Directory, FDirectoryVisitor& Visitor) override;`
- L70 _public prototype_ `virtual bool IterateDirectoryStat(const TCHAR* Directory, FDirectoryStatVisitor& Visitor) override;`
- L71 _public prototype_ `virtual IAsyncReadFileHandle* OpenAsyncRead(const TCHAR* Filename, bool bAllowWrite = false) override;`
- L72 _public prototype_ `virtual void SetAsyncMinimumPriority(EAsyncIOPriorityAndFlags MinPriority) override;`
- L73 _public prototype_ `virtual FString ConvertToAbsolutePathForExternalAppForRead(const TCHAR* Filename) override;`
- L74 _public prototype_ `virtual FString ConvertToAbsolutePathForExternalAppForWrite(const TCHAR* Filename) override;`
- L86 _public prototype_ `bool PersistSandbox( ISourceControlProvider& InSourceControlProvider, const FPersistArgs& InParams, TFunctionRef<void(const FSandboxedPlatformFilePath&, ESandboxFileChange)> InOnPersistFile, IPersistFeedback& InPersistFeedback );` — Persist the file list from the sandbox state onto the real files Will mark files for which the operation was successful as persisted. @param InSourceControlProvider The source control provider to register the changes with @param InParams	Parameters controlling the persist options specified by the user. @param InOnPersistFile Invoked for each file successfully persisted. @param InPersistFeedback Handles any errors that occur during persist @return Whether the persist operation succeeded completely. False if there were errors.
- L107 _public prototype_ `void DiscardAll( TArray<FName>& OutPackagesPendingHotReload, TArray<FName>& OutPackagesPendingPurge, TFunctionRef<void(const FFileChange&)> InProcessFileChangeCallback = [](const FFileChange&){} );` — Brings all files back to the state they had before the sandbox: - notifies the asset registry of the file change - unloads any FLinker instances that may depend on it - you'll have to manually hot-reload and purge packages. This function is useful if the user is leaving the sandbox so when the sandbox is reloaded removed, added & edited files are retained. @see RevertSandbox: The difference to RevertSandbox is that added and edited files remain in the sandbox-internal file system, e.g. Intermediate/Sandboxes. This means the next time this sandbox is reloaded, the changes can be discovered. @param OutPackagesPendingHotReload Packages that need to be hot reloaded. @param OutPackagesPendingPurge Packages that need to be purged. @param InProcessFileChangeCallback Invoked on non-sandbox paths, and with the file action that reverts the sandbox action. E.g. a file removed in sandbox would be EFileChangeAction::Added.
- L109 _public function_ `TArray<FName>& OutPackagesPendingHotReload, TArray<FName>& OutPackagesPendingPurge, TFunctionRef<void(const FFileChange&)> InProcessFileChangeCallback = [](const FFileChange&)`
- L128 _public prototype_ `void RevertSandbox( TConstArrayView<FString> InFilesToRevert, TArray<FName>& OutPackagesPendingHotReload, TArray<FName>& OutPackagesPendingPurge, TFunctionRef<void(const FFileChange&)> InProcessFileChangeCallback = [](const FFileChange&){} );` — Brings all files back to the state they had before the sandbox: - notifies the asset registry of the file change - unloads any FLinker instances that may depend on it - you'll have to manually hot-reload and purge packages. This function is useful if the user remains in the sandbox and wants to undo a file action. @see DiscardAll: The difference to DiscardAll is that added and edited files are removed from the sandbox-internal file system, e.g. Intermediate/Sandboxes. This means the next time this sandbox is reloaded, the changes will NOT be discovered. @param InFilesToRevert Absolute or relative non-sandbox paths. If empty, discard all changes. @param OutPackagesPendingHotReload Packages that need to be hot reloaded. @param OutPackagesPendingPurge Packages that need to be purged. @param InProcessFileChangeCallback Invoked on non-sandbox paths, and with the file action that reverts the sandbox action. E.g. a file removed in sandbox would be EFileChangeAction::Added.
- L131 _public function_ `TConstArrayView<FString> InFilesToRevert, TArray<FName>& OutPackagesPendingHotReload, TArray<FName>& OutPackagesPendingPurge, TFunctionRef<void(const FFileChange&)> InProcessFileChangeCallback = [](const FFileChange&)`
- L135 _public prototype_ `bool DeletedPackageExistsInNonSandbox(FString InFilename) const;` — @return Whether the given package file was deleted and exists on non sandbox path.
- L138 _public function_ `FFileStateChangeDelegate& OnFileStateChanged()` — Invoked when the file action of a file changes.
- L160 _private prototype_ `void DiscardSandboxInternal( TArray<FName>& OutPackagesPendingHotReload, TArray<FName>& OutPackagesPendingPurge, TFunctionRef<void(const FFileChange&)> InProcessRemoved = [](const FFileChange&){}, TFunctionRef<void(const FSandboxedPlatformFilePath& Path, EFileChangeAction Action)> InProcessAddedOrEdited = [](const FSandboxedPlatformFilePath&, EFileChangeAction){}, TConstArrayView<FString> InFilesToDiscard = {} );` — Brings all files back to the state they had before the sandbox: - notifies the asset registry of the file change - unloads any FLinker instances that may depend on it - you'll have to manually hot-reload and purge packages. @param OutPackagesPendingHotReload Packages that need to be hot reloaded. @param OutPackagesPendingPurge Packages that need to be purged. @param InProcessRemoved Invoked on non-sandbox paths, and with the file action that reverts the sandbox action. @param InProcessAddedOrEdited Invoked with the file action that reverts the sandbox action. @param InFilesToDiscard Absolute or relative non-sandbox paths to discard. If empty, discard all files.
- L162 _private function_ `TArray<FName>& OutPackagesPendingHotReload, TArray<FName>& OutPackagesPendingPurge, TFunctionRef<void(const FFileChange&)> InProcessRemoved = [](const FFileChange&)`
- L168 _private prototype_ `void DiscardRemoved( TConstArrayView<FString> InFilesToDiscard, TArray<FName>& OutPackagesPendingPurge, TFunctionRef<void(const FString&)> InProcessRemoved = [](const FString&){} );` — Utility for discarding files marked as removed.
- L171 _private function_ `TConstArrayView<FString> InFilesToDiscard, TArray<FName>& OutPackagesPendingPurge, TFunctionRef<void(const FString&)> InProcessRemoved = [](const FString&)`
- L175 _private prototype_ `void OnContentPathMounted(const FString& InAssetPath, const FString& InFilesystemPath);` — Callback when a new content path is mounted
- L177 _private prototype_ `void OnContentPathDismounted(const FString& InAssetPath, const FString& InFilesystemPath);` — Callback when an existing content path is unmounted
- L180 _private prototype_ `void RegisterContentMountPath(const FString& InAssetPath, const FString& InFilesystemPath);` — Register a mount path from a source content path
- L182 _private prototype_ `void UnregisterContentMountPath(const FString& InAssetPath, const FString& InFilesystemPath);` — Unregister a mount path from a source content path
- L185 _private prototype_ `FSandboxedPlatformFilePath ToSandboxPath(FString InFilename, const bool bEvenIfDisabled = false) const;` — Resolve the given path to its sandbox path (if any)
- L187 _private prototype_ `FSandboxedPlatformFilePath ToSandboxPath_Absolute(FString InFilename, const bool bEvenIfDisabled = false) const;` — Resolve the given path to its sandbox path (if any) from an absolute filename
- L189 _private prototype_ `FSandboxedPlatformFilePath FromSandboxPath(FString InFilename) const;` — Resolve the given path to its non-sandbox path (if any)
- L191 _private prototype_ `FSandboxedPlatformFilePath FromSandboxPath_Absolute(FString InFilename) const;` — Resolve the given path to its non-sandbox path (if any) from an absolute filename
- L194 _private prototype_ `bool IsPathDeleted(const FSandboxedPlatformFilePath& InPath) const;` — @return Whether a file or directory that existed in the non-sandbox has been explicitly deleted by the sandbox.
- L196 _private prototype_ `void MarkPathDeleted(const FSandboxedPlatformFilePath& InPath);` — Set that the non-sandbox file or directory is explicitly deleted by the sandbox.
- L198 _private prototype_ `void ClearPathDeleted(const FSandboxedPlatformFilePath& InPath, bool bBroadcast = true);` — Clears the deletion state. The file or directory is no longer explicitly deleted by the sandbox.
- L201 _private prototype_ `void NotifyFileDeleted(const FSandboxedPlatformFilePath& InPath);` — Notify that a file has been explicitly deleted from the sandbox
- L204 _private prototype_ `void MigrateFileToSandbox(const FSandboxedPlatformFilePath& InPath) const;` — Helper function to ensure that a sandbox contains a copy of the non-sandbox file (eg, prior to opening an existing file for writing) - does nothing if the sandbox already has the file, or if there is no non-sandbox file to copy
- L207 _private prototype_ `TArray<FDirectoryItem> GetDirectoryContents(const FSandboxedPlatformFilePath& InPath, const TCHAR* InDirBase) const;` — Helper function to get the contents of a directory, taking into account the sandbox state - paths are returned relative to InDirBase
- L211 _private prototype_ `void OnSandboxDirectoryChanged(const TArray<FFileChangeData>& FileChanges, FSandboxedPlatformFilePath MountPath);` — Called when a file in a sandbox directory changes on disk
- L215 _private prototype_ `void BroadcastFileChange(const FSandboxedPlatformFilePath& InPath, ESandboxFileChange InOldState, ESandboxFileChange InNewState);` — Broadcasts OnFileStateChangedDelegate and checks invariants.
- L218 _private prototype_ `ESandboxFileChange PersistItem( const FSandboxedPlatformFilePath& InFile, ISourceControlProvider& InSourceControlProvider, const FPersistArgs& InParams, IPersistFeedback& InErrorHandler );` — Attempts to persist the file.
- L223 _private prototype_ `FString GetSandboxRootPath() const;`
- L226 _private member_ `const FString RootPath;` — Root path of this sandbox
- L229 _private member_ `IPlatformFile* LowerLevel;` — Underlying platform file that we're wrapping
- L232 _private member_ `TAtomic<bool> bSandboxEnabled;` — Is this sandbox currently enabled?
- L235 _private member_ `TArray<FSandboxMountPoint> SandboxMountPoints;` — Array of sandbox mount points
- L237 _private member_ `mutable FCriticalSection SandboxMountPointsCS;` — Critical section protecting concurrent access to SandboxMountPoints
- L245 _private member_ `TSet<FNonSandboxPath> DeletedSandboxPaths;` — Set of absolute paths (file or directory) that have been explicitly deleted by the sandbox, i.e. when persisting these files should be deleted from the non-sandbox. This contains the absolute path to the non-sandbox file or directory.
- L247 _private member_ `mutable FCriticalSection DeletedSandboxPathsCS;` — Critical section protecting concurrent access to DeletedSandboxPaths
- L258 _private member_ `FFileStateChangeDelegate OnFileStateChangedDelegate;` — Invoked when a file action changes. Examples: - Adding Foo.uasset: (Foo.uasset, None, Added) - Reverting the addition of Foo.uasset: (Foo.uasset, Added, None) There should never be any permutation of old = None, new = None.

#### struct `UE::FileSandboxCore::FSandboxPlatformFile::FDirectoryItem`  
`struct FDirectoryItem`  
_L142-146_
- L144 _public member_ `FString Path;`
- L145 _public member_ `FFileStatData StatData;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L28 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FDeletionStateChanged, const FSandboxedPlatformFilePath&, bool );`
- L28 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FDeletionStateChanged, const FSandboxedPlatformFilePath&, bool );` (scope `UE::FileSandboxCore`)
- L29 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FSandboxedFilePathDelegate, const FSandboxedPlatformFilePath&);`
- L29 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FSandboxedFilePathDelegate, const FSandboxedPlatformFilePath&);` (scope `UE::FileSandboxCore`)
- L31 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FFileStateChangeDelegate, const FSandboxedPlatformFilePath&, ESandboxFileChange , ESandboxFileChange );`
- L31 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FFileStateChangeDelegate, const FSandboxedPlatformFilePath&, ESandboxFileChange , ESandboxFileChange );` (scope `UE::FileSandboxCore`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Private/Sandbox/Platform/SandboxedPlatformFilePath.h` (Private)


#### class `UE::FileSandboxCore::FSandboxedPlatformFilePath`  
`class FSandboxedPlatformFilePath`  
_L14-122_
- desc: A pair of file paths: a path to the original file and a path to the sandboxed version, if it exists.
- L18 _public function_ `explicit FSandboxedPlatformFilePath(FString&& InNonSandboxPath) : SandboxPath() , NonSandboxPath(MoveTemp(InNonSandboxPath))`
- L24 _public function_ `explicit FSandboxedPlatformFilePath(FString&& InNonSandboxPath, FString&& InSandboxPath) : SandboxPath(MoveTemp(InSandboxPath)) , NonSandboxPath(MoveTemp(InNonSandboxPath))`
- L36 _public function_ `static FSandboxedPlatformFilePath CreateMountPoint( const FString& InSandboxMountPointPath, const FString& InAssetPath, const FString& InFilesystemPath )` — Creates a platform file path that maps from an engine mount point to sandboxed mount point @param InSandboxMountPointPath Directory in the sandbox file structure where mount points are stored, i.e. "MySandbox/Sandbox" @param InAssetPath Name of the mount point, such as "Game", "Engine", "MyPlugin", etc. @param InFilesystemPath Root directory such as "MyProject/Content", "Engine/Content", "MyPlugin/Content", etc.
- L45 _public function_ `static FSandboxedPlatformFilePath CreateSandboxPath(FString&& InNonSandboxPath, const FSandboxedPlatformFilePath& InRootPath)`
- L51 _public function_ `static FSandboxedPlatformFilePath CreateSandboxPath(FString&& InNonSandboxPath, const FString& InRootSandboxPath, const FString& InRootNonSandboxPath)`
- L62 _public function_ `static FSandboxedPlatformFilePath CreateNonSandboxPath(FString&& InSandboxPath, const FSandboxedPlatformFilePath& InRootPath)`
- L68 _public function_ `static FSandboxedPlatformFilePath CreateNonSandboxPath(FString&& InSandboxPath, const FString& InRootSandboxPath, const FString& InRootNonSandboxPath)`
- L80 _public prototype_ `FSandboxedPlatformFilePath(const FSandboxedPlatformFilePath&) = default;` — Copyable
- L81 _public prototype_ `FSandboxedPlatformFilePath& operator=(const FSandboxedPlatformFilePath&) = default;`
- L84 _public prototype_ `FSandboxedPlatformFilePath(FSandboxedPlatformFilePath&&) = default;` — Movable
- L85 _public prototype_ `FSandboxedPlatformFilePath& operator=(FSandboxedPlatformFilePath&&) = default;`
- L87 _public function_ `bool operator==(const FSandboxedPlatformFilePath& Rhs) const`
- L93 _public function_ `bool HasSandboxPath() const` — Do we have a sandbox path set?
- L99 _public function_ `const FSandboxPath& GetSandboxPath() const` — Get the absolute sandbox path
- L105 _public function_ `const FNonSandboxPath& GetNonSandboxPath() const` — Get the absolute non-sandbox path
- L118 _private member_ `FSandboxPath SandboxPath;` — Absolute sandbox path
- L121 _private member_ `FNonSandboxPath NonSandboxPath;` — Absolute non-sandbox path

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L10 _typedef_ `using FNonSandboxPath = FString;` (scope `UE::FileSandboxCore`)
- L11 _typedef_ `using FSandboxPath = FString;` (scope `UE::FileSandboxCore`)
- L110 _function_ `friend uint32 GetTypeHash(const FSandboxedPlatformFilePath& InPath)` (scope `UE::FileSandboxCore`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Private/Sandbox/SandboxInstance.h` (Private)


#### class `UE::FileSandboxCore::FSandboxInstance`  
`class FSandboxInstance : public ISandboxInstance, public FNoncopyable`  
_L18-95_
- inherits: `ISandboxInstance,FNoncopyable`
- L23 _public prototype_ `static TUniquePtr<FSandboxInstance> CreateNewSandbox( FString InRootDirectory, const FSandboxInitArgs& InInitArgs, const FFileSandboxCore_SandboxMetaData& InMetaData );` — Initializes InRootDirectory with a new sandbox.
- L27 _public prototype_ `static TUniquePtr<FSandboxInstance> LoadSandbox(FString InRootDirectory, const FSandboxInitArgs& InInitArgs);` — Loads a preexisting sandbox from InRootDirectory.
- L29 _public prototype_ `explicit FSandboxInstance( FString InRootDirectory, const FSandboxInitArgs& InitArgs, FFileSandboxCore_ManifestData InManifestData, FFileSandboxCore_SandboxMetaData InMetaData );`
- L39 _public function_ `const FFileSandboxCore_ManifestData& GetManifestContent() const`
- L40 _public function_ `IPlatformFile& GetLowerLevelPlatformFile() const`
- L43 _public prototype_ `virtual FPersistResult PersistSandbox(const FPersistArgs& InArgs) override;`
- L44 _public prototype_ `virtual FRevertResult RevertAll() override;`
- L45 _public prototype_ `virtual FRevertResult RevertSpecified(const TConstArrayView<FString>& InFiles) override;`
- L47 _public prototype_ `virtual FRevertResult RevertSandbox(const FRevertArgs& InArgs) override;`
- L49 _public prototype_ `virtual void EnumerateFileChanges(TFunctionRef<FProcessFileChangeSignature> InProcess, EFileEnumerationFlags InFlags) const override;`
- L50 _public prototype_ `virtual TOptional<FDateTime> GetSandboxedFileTimestamp(const FString& InFilePath) const override;`
- L51 _public prototype_ `virtual bool DeletedPackageExistsInNonSandbox(const FString& InFilename) const override;`
- L52 _public function_ `virtual const FFileSandboxCore_SandboxMetaData& GetInitialMetaData() const override`
- L53 _public function_ `virtual const TCHAR* GetRootDirectory() const override`
- L54 _public function_ `virtual FSimpleMulticastDelegate& OnSandboxedFilesChanged() override`
- L60 _private member_ `const FString RootDirectory;` — Root directory in which we save all out content.
- L63 _private member_ `FFileSandboxCore_ManifestData ManifestContent;` — Current manifest data.
- L70 _private member_ `const FFileSandboxCore_SandboxMetaData MetaData;` — Metadata about this sandbox. The sandbox does not actively use the metadata, but we keep it in memory in case anything happens to the file, e.g. the user manually deleting it while in the sandbox. This way we can always guarantee to the API user that there is always valid metadata.
- L73 _private member_ `const TSharedRef<IPackageReloadHandler> PackageReloadHandler;` — External customization for hot-reloading and purging of assets. If nothing was specified, this defaults to FDefaultPackageReloadHandler.
- L76 _private member_ `TUniquePtr<FSandboxPlatformFile> PlatformFile;` — Hooks into the engine's I/O system to redirect saving & loading of files.
- L79 _private member_ `FSandboxedSourceControl SourceControlSandbox;` — Sandboxes source control operations and reroutes them to use instead.
- L82 _private member_ `FSimpleMulticastDelegate OnSandboxedFilesChangedDelegate;` — Delegate invoked when the result of GatherChangedFiles has changed.
- L85 _private member_ `std::atomic<ESandboxRefreshFlags> RefreshFlags = ESandboxRefreshFlags::None;` — Whether any sandboxed file changes have occurred this frame.
- L88 _private prototype_ `void OnFileDeletionStateChanged(const FSandboxedPlatformFilePath& InFile, ESandboxFileChange InOldState, ESandboxFileChange InNewState);` — Marks the file as deleted in the manifest.
- L91 _private prototype_ `bool SaveManifest();` — Saves the manifest file.
- L94 _private prototype_ `void OnEndOfFrame();` — Processes pending work.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Private/Sandbox/SandboxManager.h` (Private)


#### class `UE::FileSandboxCore::FSandboxManager`  
`class FSandboxManager : public ISandboxManager, public FNoncopyable`  
_L12-62_
- inherits: `ISandboxManager,FNoncopyable`
- desc: Manges the sandbox lifetime for the module
- L16 _public prototype_ `FSandboxManager();`
- L20 _public prototype_ `virtual FNewSandboxResult CreateNewSandbox(const FNewSandboxArgs& InArgs) override;`
- L21 _public prototype_ `virtual FLoadSandboxResult LoadSandbox(const FLoadSandboxByDirectoryArgs& InLoadArgs) override;`
- L22 _public prototype_ `virtual FDeleteSandboxResult DeleteSandbox(const FDeleteSandboxByDirectoryArgs& InArgs) override;`
- L23 _public prototype_ `virtual FLeaveSandboxResult LeaveSandbox(const FLeaveSandboxArgs& InLeaveArgs = FLeaveSandboxArgs()) override;`
- L24 _public function_ `virtual ISandboxLock* GetActiveLock() const override`
- L25 _public function_ `virtual ISandboxInstance* GetActiveSandboxInstance() const override`
- L26 _public prototype_ `virtual void EnumerateFileChanges(const FString& InSandboxRootPath, TFunctionRef<FProcessFileChangeSignature> InProcess, EFileEnumerationFlags InFlags) const override;`
- L27 _public prototype_ `virtual TOptional<FDateTime> GetSandboxedFileTimestamp(const FString& InSandboxRootPath, const FString& InFilePath) const override;`
- L28 _public function_ `virtual FSandboxInstanceEvent& OnPostSandboxStartup() override`
- L29 _public function_ `virtual FSandboxInstanceEvent& OnPreSandboxShutdown() override`
- L30 _public function_ `virtual FSandboxShutdownEvent& OnPostSandboxShutdown() override`
- L49 _private member_ `TOptional<FActiveSandboxData> ActiveSandboxData;` — Set while in a sandbox
- L52 _private member_ `FSandboxInstanceEvent OnPostSandboxStartupDelegate;` — Invoked after a sandbox has been successfully created.
- L54 _private member_ `FSandboxInstanceEvent OnPreSandboxShutdownDelegate;` — Invoked when it has been decided, that a sandbox instance will be taken down, but before any core destruction logic runs.
- L56 _private member_ `FSandboxShutdownEvent OnPostSandboxShutdownDelegate;` — Invoked at the end of shutting down a sandbox, i.e. after all core destruction logic has run.
- L59 _private prototype_ `void OnEngineExit();` — Stops the current sandbox.
- L61 _private function_ `FSandboxInstance* GetSandboxInstanceInternal() const`

#### struct `UE::FileSandboxCore::FSandboxManager::FActiveSandboxData`  
`struct FActiveSandboxData`  
_L35-47_
- L38 _public member_ `TUniquePtr<FSandboxInstance> Sandbox;` — Current sandbox. Nullptr if not in any sandbox.
- L41 _public member_ `TSharedPtr<ISandboxLock> Lock;` — Optional. If set, determines whether it is allowed to leave the sandbox.
- L43 _public function_ `explicit FActiveSandboxData(TUniquePtr<FSandboxInstance> Sandbox, TSharedPtr<ISandboxLock> InLock) : Sandbox(MoveTemp(Sandbox)) , Lock(InLock)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Private/Sandbox/SandboxRefreshFlags.h` (Private)


#### enum `UE::FileSandboxCore::ESandboxRefreshFlags`  
`enum class ESandboxRefreshFlags : uint8`  
_L11-19_
- desc: Flags for refreshing the sandbox instance.
- L13 _public enumerator_ `None`
- L16 _public enumerator_ `BroadcastChanges = 1 << 0` — Broadcast that the set of sandboxed file changes has changed.
- L18 _public enumerator_ `UpdateManifest = 1 << 1` — The manifest file needs to be resaved.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L20 _prototype_ `ENUM_CLASS_FLAGS(ESandboxRefreshFlags);` (scope `UE::FileSandboxCore`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Private/SourceControl/Proxy/SandboxSourceControlProviderProxy.h` (Private)


#### class `UE::FileSandboxCore::FSandboxSourceControlProviderProxy`  
`class FSandboxSourceControlProviderProxy : public FBaseSourceControlProviderProxy , public FNoncopyable`  
_L24-55_
- inherits: `FBaseSourceControlProviderProxy,FNoncopyable`
- desc: Intercepts any file changes the engine attempts to make and routes them FSandboxInstance. When set-up with source control, some tools in the engine route I/O operations to the external source control tool instead of to IPlatformFile. The point of this is that the external program handles the I/O operations, e.g. "p4 delete" deletes the file and registers it with a changelist. However, during sandbox we're not supposed to make any external changes - so we'll "swallow" those changes and re-reroute to FSandboxInstance instead. FSandboxInstance will handle re-issuing the source control commands again if the changes are persisted.
- L28 _private typedef_ `using Super = FBaseSourceControlProviderProxy;`
- L31 _public prototype_ `explicit FSandboxSourceControlProviderProxy(FSandboxInstance& InInstance UE_LIFETIMEBOUND, const FSourceControlProxyConfig& InStateProxyConfig);`
- L32 _public prototype_ `~FSandboxSourceControlProviderProxy();`
- L34 _public function_ `void SetUnderlyingSourceControlProvider(ISourceControlProvider* InProvider)`
- L37 _public prototype_ `virtual const FName& GetName() const override;`
- L38 _public prototype_ `virtual ECommandResult::Type Execute( const FSourceControlOperationRef& InOperation, FSourceControlChangelistPtr InChangelist, const TArray<FString>& InFiles, EConcurrency::Type InConcurrency = EConcurrency::Synchronous, const FSourceControlOperationComplete& InOperationCompleteDelegate = FSourceControlOperationComplete() ) override;`
- L43 _public prototype_ `virtual ECommandResult::Type GetState( const TArray<FString>& InFiles, TArray<FSourceControlStateRef>& OutState, EStateCacheUsage::Type InStateCacheUsage ) override;`
- L51 _private member_ `FSandboxInstance& Instance;` — Instance of the sandbox for which we've been created.
- L54 _private member_ `const FSourceControlProxyConfig StateProxyConfig;` — Config to construct the proxy state instances with.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Private/SourceControl/Proxy/SandboxSourceControlStateProxy.h` (Private)


#### class `UE::FileSandboxCore::FSandboxSourceControlStateProxy`  
`class FSandboxSourceControlStateProxy : public FSourceControlStateProxyBase`  
_L14-36_
- inherits: `FSourceControlStateProxyBase`
- desc: The purpose of this proxy state is to force files to optionally be treated as non-local. This achieves that when files are renamed, redirectors are created as well. Some features, such as Multi-User / Concert, require redirectors.
- L16 _private typedef_ `using Super = FSourceControlStateProxyBase;`
- L19 _public function_ `explicit FSandboxSourceControlStateProxy(FSourceControlStatePtr InProxyState, const FSourceControlProxyConfig& InConfig) : FSourceControlStateProxyBase(MoveTemp(InProxyState)) , Config(InConfig)`
- L23 _public function_ `explicit FSandboxSourceControlStateProxy(FString InFilename, const FSourceControlProxyConfig& InConfig) : FSourceControlStateProxyBase(MoveTemp(InFilename)) , Config(InConfig)`
- L29 _public prototype_ `virtual bool IsLocal() const override;`
- L35 _private member_ `const FSourceControlProxyConfig Config;` — Config for our behaviour should override the proxied state.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Private/SourceControl/Proxy/SourceControlProviderProxyBase.h` (Private)


#### class `UE::FileSandboxCore::FBaseSourceControlProviderProxy`  
`class FBaseSourceControlProviderProxy : public ISourceControlProvider`  
_L20-173_
- inherits: `ISourceControlProvider`
- desc: Forwards all calls to an optional, proxied source control provider. Acts as base class to reduce boilerplate when proxying source control classes.
- L24 _public function_ `explicit FBaseSourceControlProviderProxy(ISourceControlProvider* InActualProvider) : UnderlyingProvider(InActualProvider)`
- L29 _public function_ `virtual void Init(bool bForceConnection = true) override`
- L33 _public function_ `virtual void Close() override`
- L37 _public function_ `virtual FText GetStatusText() const override`
- L41 _public function_ `virtual TMap<EStatus, FString> GetStatus() const override`
- L45 _public function_ `virtual bool IsEnabled() const override`
- L49 _public function_ `virtual bool IsAvailable() const override`
- L53 _public function_ `virtual bool QueryStateBranchConfig(const FString& ConfigSrc, const FString& ConfigDest) override`
- L57 _public function_ `virtual void RegisterStateBranches(const TArray<FString>& BranchNames, const FString& ContentRoot) override`
- L61 _public function_ `virtual int32 GetStateBranchIndex(const FString& BranchName) const override`
- L65 _public function_ `virtual bool GetStateBranchAtIndex(int32 BranchIndex, FString& OutBranchName) const override`
- L69 _public function_ `virtual ECommandResult::Type GetState(const TArray<FString>& InFiles, TArray<FSourceControlStateRef>& OutState, EStateCacheUsage::Type InStateCacheUsage) override`
- L73 _public function_ `virtual ECommandResult::Type GetState(const TArray<FSourceControlChangelistRef>& InChangelists, TArray<FSourceControlChangelistStateRef>& OutState, EStateCacheUsage::Type InStateCacheUsage) override`
- L77 _public function_ `virtual TArray<FSourceControlStateRef> GetCachedStateByPredicate(TFunctionRef<bool(const FSourceControlStateRef&)> Predicate) const override`
- L81 _public function_ `virtual FDelegateHandle RegisterSourceControlStateChanged_Handle(const FSourceControlStateChanged::FDelegate& SourceControlStateChanged) override`
- L85 _public function_ `virtual void UnregisterSourceControlStateChanged_Handle(FDelegateHandle Handle) override`
- L89 _public function_ `virtual ECommandResult::Type Execute(const FSourceControlOperationRef& InOperation, FSourceControlChangelistPtr InChangelist, const TArray<FString>& InFiles, EConcurrency::Type InConcurrency = EConcurrency::Synchronous, const FSourceControlOperationComplete& InOperationCompleteDelegate = FSourceControlOperationComplete()) override`
- L93 _public function_ `virtual bool CanExecuteOperation(const FSourceControlOperationRef& InOperation) const override`
- L97 _public function_ `virtual bool CanCancelOperation(const FSourceControlOperationRef& InOperation) const override`
- L101 _public function_ `virtual void CancelOperation(const FSourceControlOperationRef& InOperation) override`
- L105 _public function_ `virtual TArray<TSharedRef<class ISourceControlLabel>> GetLabels(const FString& InMatchingSpec) const override`
- L109 _public function_ `virtual TArray<FSourceControlChangelistRef> GetChangelists(EStateCacheUsage::Type InStateCacheUsage) override`
- L113 _public function_ `virtual bool UsesLocalReadOnlyState() const override`
- L117 _public function_ `virtual bool UsesChangelists() const override`
- L121 _public function_ `virtual bool UsesUncontrolledChangelists() const override`
- L125 _public function_ `virtual bool UsesCheckout() const override`
- L129 _public function_ `virtual bool UsesFileRevisions() const override`
- L133 _public function_ `virtual bool UsesSnapshots() const override`
- L137 _public function_ `virtual bool UsesSoftRevertOnDelete() const override`
- L141 _public function_ `virtual bool AllowsDiffAgainstDepot() const override`
- L145 _public function_ `virtual TOptional<bool> HasChangesToSync() const override`
- L149 _public function_ `virtual TOptional<bool> HasChangesToCheckIn() const override`
- L153 _public function_ `virtual void Tick() override`
- L158 _public function_ `virtual TSharedRef<class SWidget> MakeSettingsWidget() const override`
- L167 _protected member_ `ISourceControlProvider* UnderlyingProvider;`
- L169 _protected function_ `ISourceControlProvider* GetUnderlyingProvider() const`

#### Free symbols / members of external scopes

- L11 _macro_ `#define WRAP(FuncName, ...) if (ISourceControlProvider* Provider = GetUnderlyingProvider()) { Provider->FuncName(__VA_ARGS__); }`
- L12 _macro_ `#define WRAP_RET(Default, FuncName, ...) if (ISourceControlProvider* Provider = GetUnderlyingProvider()) { return Provider->FuncName(__VA_ARGS__); } return Default;`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Private/SourceControl/Proxy/SourceControlProxyConfig.h` (Private)


#### struct `UE::FileSandboxCore::FSourceControlProxyConfig`  
`struct FSourceControlProxyConfig`  
_L10-14_
- L13 _public member_ `TOptional<bool> IsLocalOverride;` — If set, return this value from IsLocal.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L17 _prototype_ `FSourceControlProxyConfig MakeConfigFromInitArgs(const FSandboxInitArgs& InInitArgs);` (scope `UE::FileSandboxCore`) — @return Source control proxy config constructed from the sandbox init args.
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L22 _function_ `inline FSourceControlProxyConfig MakeConfigFromInitArgs(const FSandboxInitArgs& InInitArgs)` (scope `UE::FileSandboxCore`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Private/SourceControl/Proxy/SourceControlStateProxyBase.h` (Private)


#### class `UE::FileSandboxCore::FSourceControlStateProxyBase`  
`class FSourceControlStateProxyBase : public ISourceControlState`  
_L14-170_
- inherits: `ISourceControlState`
- desc: Forwards all calls to an optional, proxied source control state. Acts as base class to reduce boilerplate when proxying source control classes.
- L18 _public function_ `explicit FSourceControlStateProxyBase(FSourceControlStatePtr InProxyState) : ActualState(MoveTemp(InProxyState))`
- L19 _public function_ `explicit FSourceControlStateProxyBase(FString InFilename) : ActualState(nullptr) , CachedFilename(MoveTemp(InFilename)) , CachedTimestamp(IFileManager::Get().GetTimeStamp(*CachedFilename))`
- L26 _public function_ `virtual int32 GetHistorySize() const override`
- L27 _public function_ `virtual TSharedPtr<ISourceControlRevision> GetHistoryItem(int32 HistoryIndex) const override`
- L31 _public function_ `virtual TSharedPtr<ISourceControlRevision> FindHistoryRevision(int32 RevisionNumber) const override`
- L35 _public function_ `virtual TSharedPtr<ISourceControlRevision> FindHistoryRevision(const FString& InRevision) const override`
- L39 _public function_ `virtual TSharedPtr<ISourceControlRevision> GetCurrentRevision() const override`
- L43 _public function_ `virtual FResolveInfo GetResolveInfo() const override`
- L47 _public function_ `virtual FSlateIcon GetIcon() const override`
- L51 _public function_ `virtual FText GetDisplayName() const override`
- L55 _public function_ `virtual FText GetDisplayTooltip() const override`
- L59 _public function_ `virtual const FString& GetFilename() const override`
- L63 _public function_ `virtual const FDateTime& GetTimeStamp() const override`
- L67 _public function_ `virtual bool CanCheckIn() const override`
- L71 _public function_ `virtual bool CanCheckout() const override`
- L75 _public function_ `virtual bool IsCheckedOut() const override`
- L79 _public function_ `virtual bool IsCheckedOutOther(FString* Who = 0) const override`
- L83 _public function_ `virtual bool IsCheckedOutInOtherBranch(const FString& CurrentBranch = FString()) const override`
- L87 _public function_ `virtual bool IsModifiedInOtherBranch(const FString& CurrentBranch = FString()) const override`
- L91 _public function_ `virtual bool IsCheckedOutOrModifiedInOtherBranch(const FString& CurrentBranch = FString()) const override`
- L95 _public function_ `virtual TArray<FString> GetCheckedOutBranches() const override`
- L99 _public function_ `virtual FString GetOtherUserBranchCheckedOuts() const override`
- L103 _public function_ `virtual bool GetOtherBranchHeadModification(FString& HeadBranchOut, FString& ActionOut, int32& HeadChangeListOut) const override`
- L107 _public function_ `virtual bool IsCurrent() const override`
- L111 _public function_ `virtual bool IsSourceControlled() const override`
- L115 _public function_ `virtual bool IsLocal() const override`
- L119 _public function_ `virtual bool IsAdded() const override`
- L123 _public function_ `virtual bool IsDeleted() const override`
- L127 _public function_ `virtual bool IsIgnored() const override`
- L131 _public function_ `virtual bool CanEdit() const override`
- L135 _public function_ `virtual bool CanDelete() const override`
- L139 _public function_ `virtual bool IsUnknown() const override`
- L143 _public function_ `virtual bool IsModified() const override`
- L147 _public function_ `virtual bool CanAdd() const override`
- L151 _public function_ `virtual bool IsConflicted() const override`
- L155 _public function_ `virtual bool CanRevert() const override`
- L164 _protected member_ `FSourceControlStatePtr ActualState;` — The underlying state we proxy through.
- L167 _protected member_ `FString CachedFilename;` — The name of the file we represent (only when ActualState is null)
- L169 _protected member_ `FDateTime CachedTimestamp;` — The timestamp of the file we represent (only when ActualState is null)

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Private/SourceControl/SandboxedSourceControl.h` (Private)


#### class `UE::FileSandboxCore::FSandboxedSourceControl`  
`class FSandboxedSourceControl : public FNoncopyable`  
_L16-35_
- inherits: `FNoncopyable`
- desc: Interface for FSandboxInstance to interact with source control.
- L20 _public prototype_ `explicit FSandboxedSourceControl(FSandboxInstance& InSandboxInstance UE_LIFETIMEBOUND, const FSourceControlProxyConfig& InStateProxyConfig);`
- L23 _public function_ `ISourceControlProvider& GetProxiedSourceControl() const` — @return The real source control provider that we're overriding.
- L28 _private member_ `FSandboxInstance& SandboxInstance;` — Owning sandbox instance with which source control interacts.
- L31 _private member_ `FSandboxSourceControlProviderProxy SourceControlProviderProxy;` — The sandbox proxy that should be active for as long as the sandbox exists.
- L34 _private member_ `FScopedSourceControlOverride Override;` — Sets the global source control and handles it externally changing.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Private/SourceControl/ScopedSourceControlOverride.h` (Private)


#### class `UE::FileSandboxCore::FScopedSourceControlOverride`  
`class FScopedSourceControlOverride : public FNoncopyable`  
_L18-52_
- inherits: `FNoncopyable`
- desc: Forces the global ISourceControlProvider to always be the passed in one, even when the user manually changes the source control provider.
- L22 _public prototype_ `explicit FScopedSourceControlOverride(ISourceControlProvider& InInitialProvider UE_LIFETIMEBOUND);`
- L23 _public prototype_ `~FScopedSourceControlOverride();`
- L26 _public prototype_ `void SetRootProvider(ISourceControlProvider& InNewProvider);` — Changes the root source control provider again, as if ~FScopedSourceControlOverride() and FScopedSourceControlOverride were called again.
- L29 _public function_ `ISourceControlProvider& GetProxiedSourceControlProvider() const` — @return The real source control provider that will be restored to.
- L32 _public function_ `FSourceControlProviderEvent& OnProxiedProviderChanged()` — Invoked when the underlying source control provider changes, e.g. when the user changes the source control settings.
- L37 _private member_ `TNotNull<ISourceControlProvider*> DesiredRootProvider;` — The source control provider that should remain the root source control provider.
- L39 _private member_ `TNotNull<ISourceControlProvider*> ProxiedSourceControlProvider;` — The provider to restore to when the scope ends.
- L42 _private member_ `bool bHandlingProviderChanges = false;` — Reentry guard when handling provider changes.
- L45 _private member_ `const FDelegateHandle ProviderChangedHandle;` — Delegate handle for provider changes.
- L48 _private member_ `FSourceControlProviderEvent OnProxiedProviderChangedDelegate;` — Invoked when the underlying source control provider changes
- L51 _private prototype_ `void HandleProviderChanged(ISourceControlProvider& OldProvider, ISourceControlProvider& NewProvider);` — Delegate to handle provider change and change our underlying provider.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L15 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FSourceControlProviderEvent, ISourceControlProvider&);`
- L15 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FSourceControlProviderEvent, ISourceControlProvider&);` (scope `UE::FileSandboxCore`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Private/Utils/AssetUtils.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L18 _prototype_ `void ReplayChanges( IPackageReloadHandler& InReloaderHandler, TConstArrayView<FString> DeletedFiles, TConstArrayView<FString> ModifiedFiles, TConstArrayView<FString> AddedFiles, ESandboxPackageReloadPhase InPhase = ESandboxPackageReloadPhase::Startup );` (scope `UE::FileSandboxCore`) — Utility for applying changes from manifest file to the current IPlatformFile.
- L25 _prototype_ `void SynchronizeAssetRegistry();` (scope `UE::FileSandboxCore`) — Refreshes the assets registry after making underlying file changes.
- L28 _prototype_ `void FlushPackageLoading(const FString& InPackageName, bool bForceBulkDataLoad = true);` (scope `UE::FileSandboxCore`) — Finishes loading the package, if currently async loading, and detaches the linker.
- L30 _prototype_ `bool FlushPackageFile(const FString& InFilename, FName* OutPackageName = nullptr, bool bForceLoad = true);` (scope `UE::FileSandboxCore`) — Alternate variant that flushes package loading by filename instead.

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Private/Utils/CommandLineUtils.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L10 _prototype_ `void RegisterStartupCommandLineDelegate();` (scope `UE::FileSandboxCore`) — Parses the command line once engine start up is done; this is only done if command line arguments should be parsed, i.e. not running commandlet.
- L13 _prototype_ `void ParseStartupCommandLine();` (scope `UE::FileSandboxCore`) — Parses command line commands that are intended for engine startup.
- L16 _prototype_ `FString ParseDefaultSandboxDirectory();` (scope `UE::FileSandboxCore`) — @return The default sandbox directory set via command line, or empty no (valid) directory is set.

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Private/Utils/FileChange/EFileChangeAction.h` (Private)


#### enum `UE::FileSandboxCore::EFileChangeAction`  
`enum class EFileChangeAction : uint8`  
_L12-17_
- L14 _public enumerator_ `Added`
- L15 _public enumerator_ `Modified`
- L16 _public enumerator_ `Removed`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L21 _prototype_ `FFileChangeData::EFileChangeAction ToDirectoryWatcherAction(EFileChangeAction InAction);` (scope `UE::FileSandboxCore`) — @return Converts the change action to the equivalent IDirectoryWatcher type.
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L28 _function_ `inline FFileChangeData::EFileChangeAction ToDirectoryWatcherAction(EFileChangeAction InAction)` (scope `UE::FileSandboxCore`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Private/Utils/FileChange/FileChange.h` (Private)


#### struct `UE::FileSandboxCore::FFileChange`  
`struct FFileChange`  
_L12-31_
- desc: Describes a file change. This mirrors FFileChangeData from DirectoryWatchers because that module cannot be built in all runtime configurations.
- L14 _public member_ `FString Filename;`
- L15 _public member_ `EFileChangeAction Action;`
- L17 _public function_ `FFileChange(const FString& InFilename, EFileChangeAction InAction) : Filename(InFilename) , Action(InAction)`
- L26 _public function_ `FFileChangeData ToDirectoryWatcherChange() const` — @return Converts this change to the equivalent IDirectoryWatcher type.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Private/Utils/MountPointUtils.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L20 _prototype_ `TOptional<FString> MigrateMountPoint( const FString& InPath, TConstArrayView<FFileSandboxCore_MountPoint> InManifestMountPoints, TConstArrayView<FFileSandboxCore_MountPoint> InCurrentMountPoints );` (scope `UE::FileSandboxCore`) — Matches a path with any of InManifestMountPoints and tries to migrate it based off of InCurrentMountPoints. @param InPath Path that was in the manifest @param InManifestMountPoints The mount points when the path was saved @param InCurrentMountPoints The current mount points @return The migrated file path, or unset if no mount point could be matched.
- L39 _prototype_ `void MigrateMountPoints( TArrayView<FFileSandboxCore_MountPoint> InManifestMountPoints, TConstArrayView<FFileSandboxCore_MountPoint> InCurrentMountPoints );` (scope `UE::FileSandboxCore`) — Updates FFileSandboxCore_MountPoint::RootPath from the current version. For example, if - InManifestMountPoints contains MountName = "/Game/" and RootPath = "C:/MyProject/Content" - InCurrentMountPoints contains MountName = "/Game/" and RootPath = C:/NewLocation/MyProject/Content Then the final RootPath for MountName = "/Game/" is "C:/NewLocation/MyProject/Content". Unmatched mount points are left as they were. @param InManifestMountPoints The mount points to migrate @param InCurrentMountPoints The current mount points
- L55 _prototype_ `void MigrateManifestFilePaths(FFileSandboxCore_ManifestData& InManifest);` (scope `UE::FileSandboxCore`) — Tries to migrate file paths based off of mount points. This is relevant for sandboxes that have been imported or if the user has moved the uproject location since the sandbox was created. Old file paths will be matched to the mount points that existed when the manifest was saved. For example, if - "C:/MyProject/Content/MyBlueprint.uasset" is in the removed files - the uproject has since moved to "D:/NewProjectLocation" Then the removed file will be migrated to "D:/NewProjectLocation/Game/MyBlueprint.uasset"
- L67 _prototype_ `void TrimToReferencedMountPoints(FFileSandboxCore_ManifestData& InManifest);` (scope `UE::FileSandboxCore`) — Removes all mount points that are not being referenced by added, edited, or deleted files. For example, if - MountsPoints contains - MountName = "/Game/" and RootPath = "C:/MyProject/Content" - MountName = "/MyPlugin/" and RootPath = "C:/MyProject/Plugins/MyPlugin/Content" - Removed files contains "C:/MyProject/Content/MyBlueprint.uasset" then the mount point with MountName = "/MyPlugin/" will be removed from the manifest.

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Private/Utils/SandboxFileUtils.h` (Private)


#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L18 _prototype_ `bool SaveManifest(const FFileSandboxCore_ManifestData& InData, const FString& InRootDirectory);` (scope `UE::FileSandboxCore`) — Saves the manifest file.
- L20 _prototype_ `TOptional<FFileSandboxCore_ManifestData> LoadManifest(const FString& InRootDirectory, bool bLogErrorIfNotExist = true);` (scope `UE::FileSandboxCore`) — Loads the manifest file.
- L22 _prototype_ `TOptional<FFileSandboxCore_ManifestData> LoadManifestFromContent(const FString& InFileContent);` (scope `UE::FileSandboxCore`) — Loads the manifest if you already have the file content.
- L25 _prototype_ `TOptional<FFileSandboxCore_SandboxMetaData> LoadMetaDataFromFileContent(const FString& InFileContent);` (scope `UE::FileSandboxCore`) — Reads metadata about a sandbox if you already have the content of the file.
- L28 _prototype_ `FString GetManifestFileName();` (scope `UE::FileSandboxCore`) — @return The name to give the manifest file.
- L30 _prototype_ `FString GetMetadataFileName();` (scope `UE::FileSandboxCore`) — @return The name to give the metadata file.
- L33 _prototype_ `FString GetSandboxMountPointRoot(const FString& InSandboxRootPath);` (scope `UE::FileSandboxCore`) — @return Path to directory in the sandbox file structure where mount points are stored, i.e. "MySandbox/Sandbox"
- L36 _prototype_ `void EnumerateMountPoints(TFunctionRef<EBreakBehavior(const FString& InAssetPath, const FString& InFilesystemPath)> InProcess);` (scope `UE::FileSandboxCore`) — Enumerates all mount points in the engine.
- L39 _prototype_ `TOptional<FDateTime> GetSandboxTimestamp(const FString& InNonSandboxPath, const FString& InRootSandboxPath, const FFileSandboxCore_ManifestData& InManifest);` (scope `UE::FileSandboxCore`) — @return Timestamp in local time when InNonSandboxPath was edited, added, or removed by the sandbox.

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Private/Utils/Watcher/DirectoryWatcherUtils.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L12 _prototype_ `FDirectoryWatcherModule& GetDirectoryWatcherModule();` (scope `UE::FileSandboxCore`)
- L13 _prototype_ `FDirectoryWatcherModule* GetDirectoryWatcherModuleIfLoaded();` (scope `UE::FileSandboxCore`)
- L14 _prototype_ `IDirectoryWatcher* GetDirectoryWatcher();` (scope `UE::FileSandboxCore`)
- L15 _prototype_ `IDirectoryWatcher* GetDirectoryWatcherIfLoaded();` (scope `UE::FileSandboxCore`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Private/Utils/Watcher/ScopedWatchedDirectory.h` (Private)


#### class `UE::FileSandboxCore::FScopedWatchedDirectory`  
`class FScopedWatchedDirectory : public FNoncopyable`  
_L14-30_
- inherits: `FNoncopyable`
- desc: Unregisters IDirectoryWatcher when it goes out of scope.
- L18 _public prototype_ `FScopedWatchedDirectory() = default;`
- L19 _public prototype_ `FScopedWatchedDirectory(FString InDirectory, FDelegateHandle InHandle);`
- L20 _public prototype_ `FScopedWatchedDirectory(FScopedWatchedDirectory&& Old);`
- L21 _public prototype_ `~FScopedWatchedDirectory();`
- L23 _public function_ `const FString& GetWatchedDirectory() const`
- L24 _public function_ `bool IsValid() const`
- L28 _private member_ `FString WatchedDirectory;`
- L29 _private member_ `FDelegateHandle Handle;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Data/InstancedStructMap.h` (Public)


#### struct `FFileSandboxCore_InstancedStructMap`  
`struct FFileSandboxCore_InstancedStructMap`  
_L12-41_
- reflection: `USTRUCT()`
- reflection: `USTRUCT()`
- L17 _public prototype_ `FStructView FindOrAddData(UScriptStruct* InStruct);` — @return The existing struct data, or newly created data.
- L20 _public prototype_ `FStructView FindData(UScriptStruct* InStruct);` — @return The existing struct data, or an empty view if not present.
- L23 _public prototype_ `void Remove(UScriptStruct* InStruct);` — Removes a struct entry.
- L27 _public prototype_ `template<typename T> T& FindOrAddData();` — @return The existing struct data, or newly created data.
- L31 _public prototype_ `template<typename T> T* FindData();` — @return The existing struct data, or an empty view if not present.
- L35 _public prototype_ `template<typename T> void Remove();` — Removes a struct entry.
- L40 _private member_ `TMap<FSoftObjectPath, FInstancedStruct> Data;` — `UPROPERTY()`
- L43 _function_ `inline FStructView FFileSandboxCore_InstancedStructMap::FindOrAddData(UScriptStruct* InStruct)`
- L55 _function_ `inline FStructView FFileSandboxCore_InstancedStructMap::FindData(UScriptStruct* InStruct)`
- L61 _function_ `inline void FFileSandboxCore_InstancedStructMap::Remove(UScriptStruct* InStruct)`
- L67 _function_ `template <typename T> T& FFileSandboxCore_InstancedStructMap::FindOrAddData()`
- L73 _function_ `template <typename T> T* FFileSandboxCore_InstancedStructMap::FindData()`
- L80 _function_ `template <typename T> void FFileSandboxCore_InstancedStructMap::Remove()`

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Data/SandboxMetaData.h` (Public)


#### struct `FFileSandboxCore_SandboxMetaData`  
`struct FFileSandboxCore_SandboxMetaData`  
_L10-35_
- reflection: `USTRUCT()`
- desc: Metadata about a sandbox. This data is not needed for operations of the sandbox itself and is intended to be useful for external systems.
- L16 _public member_ `FString Name;` — `UPROPERTY()` — Name of this sandbox, usually provided by the user.
- L20 _public member_ `FString Description;` — `UPROPERTY()` — Description of this sandbox, usually provided by the user.
- L24 _public member_ `TArray<FName> Tags;` — `UPROPERTY()` — Custom tags that may have been added to this sandbox.
- L28 _public member_ `FFileSandboxCore_InstancedStructMap CustomData;` — `UPROPERTY()` — Custom advanced data that may have been added to this sandbox.
- L30 _public prototype_ `FFileSandboxCore_SandboxMetaData() = default;`
- L31 _public function_ `explicit FFileSandboxCore_SandboxMetaData(FString InName, FString InDescription = {}) : Name(MoveTemp(InName)) , Description(MoveTemp(InDescription))`

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Data/VersionInfo.h` (Public)


#### struct `FFileSandboxCore_FileVersionInfo`  
`struct FFileSandboxCore_FileVersionInfo`  
_L12-28_
- reflection: `USTRUCT()`
- desc: Holds file version information
- L18 _public member_ `int32 FileVersionUE5 = 0;` — `UPROPERTY()` — UE5 File version
- L22 _public member_ `int32 FileVersionLicensee = 0;` — `UPROPERTY()` — Licensee file version
- L25 _public prototype_ `void Initialize();` — Initialize this version info from the compiled in data
- L27 _public prototype_ `FString ToString() const;` — @return File version info as string

#### struct `FFileSandboxCore_EngineVersionInfo`  
`struct FFileSandboxCore_EngineVersionInfo`  
_L32-66_
- reflection: `USTRUCT()`
- desc: Holds engine version information
- L38 _public member_ `uint16 Major = 0;` — `UPROPERTY()` — Major version number
- L42 _public member_ `uint16 Minor = 0;` — `UPROPERTY()` — Minor version number
- L46 _public member_ `uint16 Patch = 0;` — `UPROPERTY()` — Patch version number
- L50 _public member_ `uint32 Changelist = 0;` — `UPROPERTY()` — Changelist number. This is used to arbitrate when Major/Minor/Patch version numbers match
- L53 _public prototype_ `void Initialize(const FEngineVersion& InVersion);` — Initialize this version info from the given version
- L56 _public prototype_ `FString ToString(bool bIncludeChangelist = true) const;` — @return Engine version info as string, e.g. "5.7.1-48893048"
- L65 _public prototype_ `bool IsCompatibleWith(const FFileSandboxCore_EngineVersionInfo& InCurrentVersion) const;` — Check if this version is compatible with the given version. A sandbox version is compatible if it's not newer than the current version. Comparison order: Major > Minor > Patch > Changelist @param InCurrentVersion The current engine version to check against @return true if this version can be loaded in the current version

#### struct `FFileSandboxCore_CustomVersionInfo`  
`struct FFileSandboxCore_CustomVersionInfo`  
_L70-96_
- reflection: `USTRUCT()`
- desc: Holds custom version information
- L84 _public member_ `FName FriendlyName;` — `UPROPERTY()` — Friendly name of the version
- L88 _public member_ `FGuid Key;` — `UPROPERTY()` — Unique custom key
- L92 _public member_ `int32 Version = 0;` — `UPROPERTY()` — Custom version
- L95 _public prototype_ `void Initialize(const FCustomVersion& InVersion);` — Initialize this version info from the given version

#### struct `FFileSandboxCore_VersionInfo`  
`struct FFileSandboxCore_VersionInfo`  
_L100-124_
- reflection: `USTRUCT()`
- desc: Holds version information for a session
- L106 _public member_ `FFileSandboxCore_FileVersionInfo FileVersion;` — `UPROPERTY()` — File version info
- L110 _public member_ `FFileSandboxCore_EngineVersionInfo EngineVersion;` — `UPROPERTY()` — Engine version info
- L114 _public member_ `TArray<FFileSandboxCore_CustomVersionInfo> CustomVersions;` — `UPROPERTY()` — Custom version info
- L117 _public prototype_ `void Initialize();` — Initialize this version info from the compiled in data
- L119 _public prototype_ `bool IsInitialized() const;` — @return Whether any data is set.
- L122 _public prototype_ `FString ToString() const;` — @eturn File and version info as string. Does not include custom versions.

#### Free symbols / members of external scopes

- L74 _function_ `friend FArchive& operator<<(FArchive& Archive, FFileSandboxCore_CustomVersionInfo& VersionInfo)`

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/FileSandboxCoreMinimal.h` (Public)
_(no declarations extracted)_

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/IFileSandboxCoreModule.h` (Public)


#### class `UE::FileSandboxCore::IFileSandboxCoreModule`  
`class IFileSandboxCoreModule : public IModuleInterface`  
_L14-40_
- inherits: `IModuleInterface`
- L24 _public function_ `static IFileSandboxCoreModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L31 _public function_ `static bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() during shutdown if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L34 _public prototype_ `virtual ISandboxManager& GetSandboxManager() = 0;` — @return The API for managing live sandboxes.
- L37 _public prototype_ `virtual ISandboxRepository& GetDefaultSandboxRepository() = 0;` — @return Gets the repository for the default sandbox save location (@see GetBaseSandboxDirectory)

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/ISandboxInstance.h` (Public)


#### class `UE::FileSandboxCore::ISandboxInstance`  
`class ISandboxInstance`  
_L32-107_
- desc: Manages the file sandbox. While this is alive, some engine I/O operations are sandboxed. Only files in mount points (game content, engine content, plugin content) are tracked. Other files, such as those residing in Saved/ or Config/ are not affected.
- L37 _public prototype_ `bool PersistAll();` — Persists all files.
- L44 _public prototype_ `virtual FPersistResult PersistSandbox(const FPersistArgs& InArgs) = 0;` — More advanced version of PersistAll that gives you more control how persisting should occur. @param InArgs	Parameters controlling the persist options specified by the user. @return Returns a persist result object that contains result status.
- L48 _public prototype_ `virtual FRevertResult RevertAll() = 0;` — Reverts all files to the state they had before the sandbox.
- L68 _public prototype_ `FGatheredFileChanges GatherChangedFiles(EFileChangeGatherFlags InFlags = EFileChangeGatherFlags::All) const;` — Enumerates all files that have been changed (added, removed, or edited).
- L74 _public prototype_ `virtual void EnumerateFileChanges( TFunctionRef<FProcessFileChangeSignature> InProcess, EFileEnumerationFlags InFlags = EFileEnumerationFlags::All ) const = 0;` — Invokes InProcess for every effective file change that would be performed if the sandbox was persisted. @see ISandboxManager::EnumerateFileChanges.
- L83 _public prototype_ `bool HasFileChanges() const;` — @return Whether any changes have to any files. @note This does not include packages with in-memory changes only. @see GetDirtyPackages
- L86 _public prototype_ `virtual TOptional<FDateTime> GetSandboxedFileTimestamp(const FString& InFilePath) const = 0;` — @return The timestamp at which the file was last modified by the sandbox, or FDateTime::MinValue().
- L90 _public prototype_ `virtual bool DeletedPackageExistsInNonSandbox(const FString& InFilename) const = 0;` — @return Whether the given package file exists on non sandbox path, i.e. whether the file was deleted in sandbox mode.
- L98 _public prototype_ `virtual const FFileSandboxCore_SandboxMetaData& GetInitialMetaData() const = 0;` — @return Metadata about this sandbox. @note This is the metadata that the sandbox has when it was created / loaded. If the underlying file has changed, this will not return the latest value.
- L101 _public prototype_ `virtual const TCHAR* GetRootDirectory() const = 0;` — @return The root directory of the sandbox.
- L104 _public prototype_ `virtual FSimpleMulticastDelegate& OnSandboxedFilesChanged() = 0;` — @return Delegate invoked when the result of GatherChangedFiles has changed.
- L106 _public prototype_ `virtual ~ISandboxInstance() = default;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API FILESANDBOXCORE_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L23 _typedef_ `using FConsumeFileSignature = EBreakBehavior(const FString&);` (scope `UE::FileSandboxCore`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/ISandboxManager.h` (Public)


#### class `UE::FileSandboxCore::ISandboxManager`  
`class ISandboxManager`  
_L62-164_
- desc: Manages the lifetime of the ISandboxInstance. For now, only one sandbox can be active at any given time and all files in mount points are sandboxed. ===== Overview ===== During sandbox, any I/O operations that modify, delete, or add files in mount points (e.g. /Game/..., /Engine/..., /MyPlugin/..., etc.) will be sandboxed. That means those operations are performed in a separate sandbox file system without changing the underlying files. At any time, you can persist changes, i.e. apply them to the underlying file system where the real files reside. ==== Example ===== 1. The user opens the asset "Game/Levels/MyBlueprint.uasset", changes it, and then clicks save. 2. The contained UObjects are serialized and a low-level I/O operation is triggered (via IPlatformFile). 2.1 Normally, the data would be written "D:/MyProject/Content/Levels/MyBlueprint.uasset", 2.2 But we redirect the data to a sandboxed location, e.g."D:/MyProject/Intermediate/Sandboxes/YourSandbox/Sandbox/Game". Similar behaviour goes for when a file is deleted or added. ==== Persisting ===== Persisting effectively means to apply the changes to the original files. Files marked for delete are deleted from the original location. Added and modified files are copied from the sandbox location to the original location, e.g. a modified file "D:/MyProject/Content/Levels/MyBlueprint.uasset" would be replaced with "D:/MyProject/Intermediate/Sandboxes/YourSandbox/Sandbox/Game". ===== Sandbox file structure ===== By default, sand
- L73 _public prototype_ `virtual FNewSandboxResult CreateNewSandbox(const FNewSandboxArgs& InArgs) = 0;` — Puts the engine into a sandbox: This creates a new environment. Tip: If you don't care about the specifics of potential errors, you can write if (ISandboxInstance* Instance = Manager->CreateNewSandbox(...)). @note Do not keep any raw reference to ISandboxInstance as it turns stale when the sandbox is shutdown. @see FWeakSandboxPtr, GetGlobalSandboxInstance.
- L86 _public prototype_ `FLoadSandboxResult LoadNamedSandbox(const FLoadSandboxByNameArgs& InArgs);` — Puts the engine into a sandbox: applies the state from a pre-existing sandbox to any open assets. Any assets that are currently open / in-memory will be hot-reloaded. Effectively, this means that their file content will be re-loaded but from the sandboxed version of the .uasset file. Tip: If you don't care about the specifics of potential errors, you can write if (ISandboxInstance* Instance = Manager->LoadNamedSandbox(...)). @note Do not keep any raw reference to ISandboxInstance as it turns stale when the sandbox is shutdown. @see FWeakSandboxPtr, GetGlobalSandboxInstance.
- L89 _public prototype_ `virtual FLoadSandboxResult LoadSandbox(const FLoadSandboxByDirectoryArgs& InLoadArgs) = 0;` — Advanced version of LoadNamedSandbox for when you know the specific root directory of a sandbox.
- L93 _public prototype_ `FDeleteSandboxResult DeleteNamedSandbox(const FDeleteSandboxByNameArgs& InArgs);` — Deletes the sandbox with the given name, if found. It is valid to delete a sandbox if it is currently valid.
- L96 _public prototype_ `virtual FDeleteSandboxResult DeleteSandbox(const FDeleteSandboxByDirectoryArgs& InArgs) = 0;` — Advanced version of DeleteNamedSandbox for when you know the specific root directory of a sandbox.
- L100 _public prototype_ `virtual FLeaveSandboxResult LeaveSandbox(const FLeaveSandboxArgs& InLeaveArgs = FLeaveSandboxArgs()) = 0;` — Leaves the current sandbox.
- L107 _public prototype_ `virtual ISandboxLock* GetActiveLock() const = 0;` — More advanced version of CanLeaveSandbox if you want to find out the reason why the sandbox cannot be left. @return Lock object that determines whether the sandbox can be left. @note Do not keep any raw reference to ISandboxLock as it turns stale when the sandbox is shutdown.
- L110 _public function_ `bool CanLeaveSandbox() const` — @return Whether a LeaveSandbox call would be successful.
- L112 _public prototype_ `ELeaveSandboxErrorCode CanLeaveSandboxWithReason() const;` — @return Why a LeaveSandbox call would be (un-)successful.
- L123 _public prototype_ `virtual ISandboxInstance* GetActiveSandboxInstance() const = 0;` — Gets the currently active global sandbox instance. The name “global” sandbox instance was chosen with the idea that, in the future, we may support directory bindings where only specific directories are sandboxed. For now (5.8), there can be at most one sandbox instance. @note Do not keep any raw reference to ISandboxInstance as it turns stale when the sandbox is shutdown. @see FWeakSandboxPtr, GetGlobalSandboxInstance.
- L126 _public function_ `bool HasActiveSandbox() const` — @return Whether the is any active sandbox.
- L141 _public prototype_ `void EnumerateFileChangesByName( const FString& InSandboxName, TFunctionRef<FProcessFileChangeSignature> InProcess, const FString& InBaseDirectory = GetBaseSandboxDirectory() ) const;` — Invokes InProcess for every effective file change that would be performed if the sandbox was persisted. Effective changes can differ from the actual actions performed during sandbox because external changes could have been made to the project outside of sandbox. The implementation respects file changes that have occured since the sandbox the last time the sandbox was active. Examples: Suppose that while the engine is sandboxed file x is - removed: then, outside of sandbox, file x is added. Then X would not be listed (InProcess not invoked). - added: then, outside of sandbox, file x is added. Then X would be reported as edited. - edited: then, outside of sandbox, file x is removed. Then X would be reported as added. If no external changes are made, the file action is reported exactly as it was performed in the sandbox without changes.
- L147 _public prototype_ `virtual void EnumerateFileChanges( const FString& InSandboxRootPath, TFunctionRef<FProcessFileChangeSignature> InProcess, EFileEnumerationFlags InFlags = EFileEnumerationFlags::All ) const = 0;` — Alternative version that uses the sandbox root directory instead.
- L153 _public prototype_ `virtual TOptional<FDateTime> GetSandboxedFileTimestamp(const FString& InSandboxRootPath, const FString& InFilePath) const = 0;` — @return The timestamp at which the file was last modified by the sandbox.
- L156 _public prototype_ `virtual FSandboxInstanceEvent& OnPostSandboxStartup() = 0;` — @return Event invoked after a sandbox has been successfully created.
- L159 _public prototype_ `virtual FSandboxInstanceEvent& OnPreSandboxShutdown() = 0;` — @return Event invoked when it has been decided, that a sandbox instance will be taken down, but before any core destruction logic runs.
- L161 _public prototype_ `virtual FSandboxShutdownEvent& OnPostSandboxShutdown() = 0;` — @return Event invoked at the end of shutting down a sandbox, i.e. after all core destruction logic has run.
- L163 _public prototype_ `virtual ~ISandboxManager() = default;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API FILESANDBOXCORE_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L23 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FSandboxInstanceEvent, ISandboxInstance&);`
- L23 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FSandboxInstanceEvent, ISandboxInstance&);` (scope `UE::FileSandboxCore`)
- L24 _typedef_ `using FSandboxShutdownEvent = FSimpleMulticastDelegate;` (scope `UE::FileSandboxCore`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/ISandboxRepository.h` (Public)


#### class `UE::FileSandboxCore::ISandboxRepository`  
`class ISandboxRepository`  
_L26-56_
- desc: Knows of the sandboxes instances available. You can think of this as a cache that will notify when the sandboxes available changes, and the metadata changes. You should prefer this over manually loading metadata (@see LoadMetaData) whenever possible to avoid excessive file reads, JSON parsing, etc. This is useful for, e.g. UI want to display the available sandboxes.
- L34 _public prototype_ `virtual void ForEachSandbox(TFunctionRef<EBreakBehavior(const FString& InRootPath, const FSandboxMetaInfo& MetaData)> InProcessSandboxes) = 0;` — Enumerates all known sandboxes. InRootPath will be the absolute path to the root sandbox directory, i.e. the one containing the metadata file.
- L37 _public prototype_ `virtual int32 NumSandboxes() const = 0;` — @return Number of distinct sandboxes, i.e. number of times ForEachSandbox would invoke the callback.
- L45 _public prototype_ `virtual bool ReadMetaData(const FString& InRootPath, TFunctionRef<void(const FSandboxMetaInfo&)> InProcessMetadata) = 0;` — @param InRootPath Relative or absolute path to the root directory of the sandbox, i.e. one enumerated by InProcessSandboxes. @param InProcessMetadata Callback invoked if the metadata exists @return Whether the callback was invoked
- L49 _public prototype_ `virtual FOnSandboxesChanged& OnSandboxesChanged() = 0;` — @return Invoked when the known sandboxes changes (removed, discovered, etc.), on game thread.
- L52 _public prototype_ `virtual FOnSandboxMetaDataChanged& OnSandboxMetaDataChanged() = 0;` — @return Invoked when a sandbox's metadata changes, on game thread.
- L55 _public prototype_ `virtual ~ISandboxRepository() = default;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L16 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSandboxesChanged, const FRepositoryChangedEvent&);`
- L16 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSandboxesChanged, const FRepositoryChangedEvent&);` (scope `UE::FileSandboxCore`)
- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSandboxMetaDataChanged, const FString& );`
- L17 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSandboxMetaDataChanged, const FString& );` (scope `UE::FileSandboxCore`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Interface/DefaultPackageReloadHandler.h` (Public)


#### class `UE::FileSandboxCore::FDefaultPackageReloadHandler`  
`class FDefaultPackageReloadHandler : public IPackageReloadHandler`  
_L12-20_
- inherits: `IPackageReloadHandler`
- desc: Default implementation for reloading assets.
- L17 _public prototype_ `virtual void PurgePackages(const FPurgePackageArgs& InArgs) override;`
- L18 _public prototype_ `virtual void HotReloadPackages(const FHotReloadPackageArgs& InArgs) override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API FILESANDBOXCORE_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Interface/Feedback/AggregatePersistFeedback.h` (Public)


#### class `UE::FileSandboxCore::FAggregatePersistFeedback`  
`class FAggregatePersistFeedback : public IPersistFeedback`  
_L12-126_
- inherits: `IPersistFeedback`
- desc: Forwards the errors to other error handlers.
- L16 _public function_ `explicit FAggregatePersistFeedback(TArray<IPersistFeedback*> InErrorHandlers) : ErrorHandlers(MoveTemp(InErrorHandlers))`
- L17 _public function_ `explicit FAggregatePersistFeedback(IPersistFeedback& InErrorHandler) : ErrorHandlers({ &InErrorHandler })`
- L20 _public function_ `virtual void StartFile(const TCHAR* InFilename) override`
- L30 _public function_ `virtual void HandleSuccess(const TCHAR* InFilename) override`
- L40 _public function_ `virtual void HandleError_CheckoutNotAllowed(const TCHAR* InFilename) override`
- L50 _public function_ `virtual void HandleError_Checkout(const TCHAR* InFilename) override`
- L60 _public function_ `virtual void HandleError_Revert(const TCHAR* InFilename) override`
- L70 _public function_ `virtual void HandleError_MarkForAdd(const TCHAR* InFilename) override`
- L80 _public function_ `virtual void HandleError_DeleteSCC(const TCHAR* InFilename) override`
- L90 _public function_ `virtual void HandleError_MakeWritable(const TCHAR* InFilename) override`
- L100 _public function_ `virtual void HandleError_MoveFile(const TCHAR* InToFilename, const TCHAR* InFromFilename) override`
- L110 _public function_ `virtual void HandleError_DeleteFile(const TCHAR* InFilename) override`
- L125 _private member_ `TArray<IPersistFeedback*> ErrorHandlers;` — The error handlers to forward the errors to.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L23 _function_ `` (scope `UE::FileSandboxCore::FAggregatePersistFeedback::StartFile`)
- L33 _function_ `` (scope `UE::FileSandboxCore::FAggregatePersistFeedback::HandleSuccess`)
- L43 _function_ `` (scope `UE::FileSandboxCore::FAggregatePersistFeedback::HandleError_CheckoutNotAllowed`)
- L53 _function_ `` (scope `UE::FileSandboxCore::FAggregatePersistFeedback::HandleError_Checkout`)
- L63 _function_ `` (scope `UE::FileSandboxCore::FAggregatePersistFeedback::HandleError_Revert`)
- L73 _function_ `` (scope `UE::FileSandboxCore::FAggregatePersistFeedback::HandleError_MarkForAdd`)
- L83 _function_ `` (scope `UE::FileSandboxCore::FAggregatePersistFeedback::HandleError_DeleteSCC`)
- L93 _function_ `` (scope `UE::FileSandboxCore::FAggregatePersistFeedback::HandleError_MakeWritable`)
- L103 _function_ `` (scope `UE::FileSandboxCore::FAggregatePersistFeedback::HandleError_MoveFile`)
- L113 _function_ `` (scope `UE::FileSandboxCore::FAggregatePersistFeedback::HandleError_DeleteFile`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Interface/Feedback/AppendTextErrorHandler.h` (Public)


#### class `UE::FileSandboxCore::FAppendTextPersistFeedback`  
`class FAppendTextPersistFeedback : public IPersistFeedback`  
_L13-80_
- inherits: `IPersistFeedback`
- L17 _public member_ `TArray<FText> AllErrors;`
- L20 _public function_ `virtual void StartFile(const TCHAR* InFilename) override`
- L21 _public function_ `virtual void HandleSuccess(const TCHAR* InFilename) override`
- L22 _public function_ `virtual void HandleError_CheckoutNotAllowed(const TCHAR* InFilename) override`
- L29 _public function_ `virtual void HandleError_Checkout(const TCHAR* InFilename) override`
- L36 _public function_ `virtual void HandleError_Revert(const TCHAR* InFilename) override`
- L43 _public function_ `virtual void HandleError_MarkForAdd(const TCHAR* InFilename) override`
- L50 _public function_ `virtual void HandleError_DeleteSCC(const TCHAR* InFilename) override`
- L57 _public function_ `virtual void HandleError_MakeWritable(const TCHAR* InFilename) override`
- L64 _public function_ `virtual void HandleError_MoveFile(const TCHAR* InToFilename, const TCHAR* InFromFilename) override`
- L72 _public function_ `virtual void HandleError_DeleteFile(const TCHAR* InFilename) override`

#### Free symbols / members of external scopes

- L9 _macro_ `#define LOCTEXT_NAMESPACE "FAppendTextPersistErrorHandler"`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Interface/IPackageReloadHandler.h` (Public)


#### class `UE::FileSandboxCore::IPackageReloadHandler`  
`class IPackageReloadHandler`  
_L15-26_
- desc: Interface to customize hot-reloading and purging of assets.
- L20 _public prototype_ `virtual void PurgePackages(const FPurgePackageArgs& InArgs) = 0;` — Handles cleaning up assets that no longer exist.
- L23 _public prototype_ `virtual void HotReloadPackages(const FHotReloadPackageArgs& InArgs) = 0;` — Reloads packages that were modified
- L25 _public prototype_ `virtual ~IPackageReloadHandler() = default;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Interface/IPersistFeedback.h` (Public)


#### class `UE::FileSandboxCore::IPersistFeedback`  
`class IPersistFeedback`  
_L10-29_
- desc: You can implement this to get interactive information about a persist operation.
- L15 _public prototype_ `virtual void StartFile(const TCHAR* InFilename) = 0;` — The file was successfully persisted.
- L16 _public prototype_ `virtual void HandleSuccess(const TCHAR* InFilename) = 0;`
- L18 _public prototype_ `virtual void HandleError_CheckoutNotAllowed(const TCHAR* InFilename) = 0;`
- L19 _public prototype_ `virtual void HandleError_Checkout(const TCHAR* InFilename) = 0;`
- L20 _public prototype_ `virtual void HandleError_Revert(const TCHAR* InFilename) = 0;`
- L21 _public prototype_ `virtual void HandleError_MarkForAdd(const TCHAR* InFilename) = 0;`
- L22 _public prototype_ `virtual void HandleError_DeleteSCC(const TCHAR* InFilename) = 0;`
- L24 _public prototype_ `virtual void HandleError_MakeWritable(const TCHAR* InFilename) = 0;`
- L25 _public prototype_ `virtual void HandleError_MoveFile(const TCHAR* InToFilename, const TCHAR* InFromFilename) = 0;`
- L26 _public prototype_ `virtual void HandleError_DeleteFile(const TCHAR* InFilename) = 0;`
- L28 _public prototype_ `virtual ~IPersistFeedback() = default;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Interface/ISandboxLock.h` (Public)


#### class `UE::FileSandboxCore::ISandboxLock`  
`class ISandboxLock`  
_L10-31_
- desc: Interface to allow module to determine whether a sandbox can be left.
- L18 _public prototype_ `virtual bool CanLeaveSandbox(FText* OutReason = nullptr) const = 0;` — @param OutReason Optional. Reason set why the sandbox cannot be left. @return Whether the sandbox can be left
- L25 _public prototype_ `virtual bool RequestLiftLock(FText* OutReason = nullptr) = 0;` — Asks the lock to be lifted. The request can be rejected. @param OutReason Optional. Reason set when the lock could not be lifted. @return Whether the lock was lifted
- L28 _public prototype_ `virtual bool SupportsLiftingLock() const = 0;` — @return Whether it is supported to call RequestLiftLock.
- L30 _public prototype_ `virtual ~ISandboxLock() = default;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Types/ArgsFwds.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L26 _typedef_ `using FNewSandboxResult = TSandboxCreationResult<FNewSandboxError>;` (scope `UE::FileSandboxCore`)
- L27 _typedef_ `using FLoadSandboxResult = TSandboxCreationResult<FLoadSandboxError>;` (scope `UE::FileSandboxCore`)
- L32 _typedef_ `using FProcessFileChangeSignature = EBreakBehavior(const FSandboxedFileChangeInfo& InFileInfo);` (scope `UE::FileSandboxCore`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Types/EBreakBehavior.h` (Public)


#### enum `UE::FileSandboxCore::EBreakBehavior`  
`enum class EBreakBehavior : uint8`  
_L9-13_
- L11 _public enumerator_ `Continue`
- L12 _public enumerator_ `Break`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Types/GatheredFileChanges.h` (Public)


#### enum `UE::FileSandboxCore::EFileChangeGatherFlags`  
`enum class EFileChangeGatherFlags : uint8`  
_L16-22_
- desc: Specifies what information should be gathered about files
- L18 _public enumerator_ `None`
- L19 _public enumerator_ `IncludeChangeTypes = 1 << 0`
- L20 _public enumerator_ `IncludeTimestamps = 1 << 1`
- L21 _public enumerator_ `All = IncludeChangeTypes | IncludeTimestamps`

#### struct `UE::FileSandboxCore::FGatheredFileChanges`  
`struct FGatheredFileChanges`  
_L26-39_
- desc: Result of ISandboxInstance::GatherChangedFiles.
- L29 _public member_ `TArray<FString> NonSandboxPaths;` — All files changed by the sandbox. The paths are in the non-sandbox.
- L32 _public member_ `TArray<ESandboxFileChange> FileActions;` — The changes made to the file. Equal length to NonSandboxPaths. Only set if EFileChangeGatherFlags::IncludeChangeTypes was set.
- L35 _public member_ `TArray<FDateTime> Timestamps;` — When the change was made, in local time. Only set if EFileChangeGatherFlags::IncludeTimestamps was set.
- L38 _public function_ `bool HasChanges() const` — @return Whether there are any changes.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L23 _prototype_ `ENUM_CLASS_FLAGS(EFileChangeGatherFlags);` (scope `UE::FileSandboxCore`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Types/Manager/DeleteSandboxByDirectoryArgs.h` (Public)


#### struct `UE::FileSandboxCore::FDeleteSandboxByDirectoryArgs`  
`struct FDeleteSandboxByDirectoryArgs`  
_L10-18_
- desc: Args for deleting sandbox by directory.
- L13 _public member_ `FString Directory;` — The root directory of the sandbox (i.e. the one containing the manifest file).
- L15 _public function_ `FDeleteSandboxByDirectoryArgs(FString InDirectory) : Directory(MoveTemp(InDirectory))`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Types/Manager/DeleteSandboxByNameArgs.h` (Public)


#### struct `UE::FileSandboxCore::FDeleteSandboxByNameArgs`  
`struct FDeleteSandboxByNameArgs`  
_L11-25_
- desc: Args for deleting sandbox by name.
- L14 _public member_ `FString Name;` — The name of the sandbox you want to load.
- L17 _public member_ `FString BaseDirectory;` — The directory in which to search for the sandbox.
- L19 _public function_ `explicit FDeleteSandboxByNameArgs(FString InName, FString InBaseDirectory = GetBaseSandboxDirectory()) : Name(MoveTemp(InName)) , BaseDirectory(MoveTemp(InBaseDirectory))`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Types/Manager/DeleteSandboxResult.h` (Public)


#### enum `UE::FileSandboxCore::EDeleteSandboxErrorCode`  
`enum class EDeleteSandboxErrorCode : uint8`  
_L9-28_
- L12 _public enumerator_ `Success` — Sandbox was deleted successfully.
- L15 _public enumerator_ `InvalidName` — Given sandbox name could not be resolved to any sandbox.
- L18 _public enumerator_ `InvalidDirectory` — Given directory does not contain any sandbox.
- L21 _public enumerator_ `IOError` — An I/O error occured, e.g. the directory could not be deleted.
- L27 _public enumerator_ `CannotLeaveSandbox` — Failed to leave the sandbox. Most likely because the sandbox is locked. If you need more info consider calling LeaveSandbox explicitly before.

#### struct `UE::FileSandboxCore::FDeleteSandboxResult`  
`struct FDeleteSandboxResult`  
_L31-41_
- desc: Describes the result of the delete operation, with a reason of why it failed.
- L34 _public member_ `EDeleteSandboxErrorCode ErrorCode = EDeleteSandboxErrorCode::Success;` — Describes the result of the delete operation, with a reason of why it failed.
- L36 _public prototype_ `FDeleteSandboxResult() = default;`
- L37 _public function_ `FDeleteSandboxResult(EDeleteSandboxErrorCode InErrorCode) : ErrorCode(InErrorCode)`
- L40 _public function_ `bool IsSuccess() const` — @return Whether the sandbox was successfully deleted.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Types/Manager/LeaveSandboxArgs.h` (Public)


#### struct `UE::FileSandboxCore::FLeaveSandboxArgs`  
`struct FLeaveSandboxArgs`  
_L11-15_
- desc: Describes how the session is supposed to be left.
- L14 _public member_ `TOptional<FPersistArgs> PersistArgs;` — If set, this specifies the files that are supposed to be persisted, and how.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Types/Manager/LeaveSandboxResult.h` (Public)


#### enum `UE::FileSandboxCore::ELeaveSandboxErrorCode`  
`enum class ELeaveSandboxErrorCode : uint8`  
_L10-20_
- L13 _public enumerator_ `Success` — The sandbox was left successfully, or the engine was not in any sandbox.
- L19 _public enumerator_ `Locked` — The engine is locked to this sandbox. Inspect the ISandboxLock for the reason. @see ISandboxManager::GetActiveLock

#### struct `UE::FileSandboxCore::FLeaveSandboxResult`  
`struct FLeaveSandboxResult`  
_L23-35_
- desc: Describes the result of the leave operation, with a reason of why it failed.
- L26 _public member_ `ELeaveSandboxErrorCode ErrorCode = ELeaveSandboxErrorCode::Success;` — Describes the result of the leave operation, with a reason of why it failed.
- L28 _public prototype_ `FLeaveSandboxResult() = default;`
- L29 _public function_ `FLeaveSandboxResult(ELeaveSandboxErrorCode InErrorCode) : ErrorCode(InErrorCode)`
- L32 _public function_ `bool IsSuccess() const` — @return Whether the sandbox was successfully left.
- L34 _public function_ `operator bool() const` — @return Whether the operation was successful.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Types/Manager/LoadSandboxByDirectoryArgs.h` (Public)


#### struct `UE::FileSandboxCore::FLoadSandboxByDirectoryArgs`  
`struct FLoadSandboxByDirectoryArgs`  
_L11-23_
- desc: Args for loading a pre-existing sandbox.
- L14 _public member_ `FString SandboxRootPath;` — The root directory of the sandbox (i.e. the one containing the manifest file).
- L17 _public member_ `FSandboxInitArgs InitArgs;` — Base arguments for instantiating the sandbox environment.
- L19 _public function_ `explicit FLoadSandboxByDirectoryArgs(FString InSandboxRootPath) : SandboxRootPath(MoveTemp(InSandboxRootPath))`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Types/Manager/LoadSandboxByNameArgs.h` (Public)


#### struct `UE::FileSandboxCore::FLoadSandboxByNameArgs`  
`struct FLoadSandboxByNameArgs`  
_L11-28_
- desc: Args for loading a pre-existing sandbox.
- L14 _public member_ `FString Name;` — The name of the sandbox you want to load.
- L17 _public member_ `FString BaseDirectory;` — The directory in which to search for the sandbox.
- L20 _public member_ `FSandboxInitArgs InitArgs;` — Base arguments for instantiating the sandbox environment.
- L22 _public function_ `explicit FLoadSandboxByNameArgs(FString InName, FString InBaseDirectory = GetBaseSandboxDirectory()) : Name(MoveTemp(InName)) , BaseDirectory(MoveTemp(InBaseDirectory))`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Types/Manager/LoadSandboxError.h` (Public)


#### enum `UE::FileSandboxCore::ELoadSandboxLoadErrorReason`  
`enum class ELoadSandboxLoadErrorReason : uint8`  
_L13-44_
- L16 _public enumerator_ `InvalidDirectory` — The directory does not contain any sandbox
- L18 _public enumerator_ `InvalidName` — The name does not map to any directory.
- L21 _public enumerator_ `IOError` — Some generic IO error occured (e.g. could not write manifest file, etc.)
- L27 _public enumerator_ `CannotLeaveSandbox` — Failed to leave the sandbox. Most likely because the sandbox is locked. If you need more info consider calling LeaveSandbox explicitly before.
- L34 _public enumerator_ `IncompatibleVersion` — The sandbox was created with a newer version of Unreal Engine and cannot be loaded. For example, a 5.8 sandbox cannot be loaded in 5.7, or a sandbox with CL 5819811 cannot be loaded in CL 5719181.
- L37 _public enumerator_ `Unspecified` — Dummy error code for initializing to a deterministic value.
- L43 _public enumerator_ `Count` — ADD NEW MEMBERS ABOVE. Not a real reason.

#### struct `UE::FileSandboxCore::FLoadSandboxError`  
`struct FLoadSandboxError`  
_L47-50_
- desc: Explains why a new sandbox could not be loaded.
- L49 _public member_ `ELoadSandboxLoadErrorReason Reason = ELoadSandboxLoadErrorReason::Unspecified;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L53 _prototype_ `FString LexToString(ELoadSandboxLoadErrorReason InReason);` (scope `UE::FileSandboxCore`) — @return Error reason converted to a string.

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Types/Manager/NewSandboxArgs.h` (Public)


#### struct `UE::FileSandboxCore::FNewSandboxArgs`  
`struct FNewSandboxArgs`  
_L12-38_
- desc: Args for creating a new sandbox.
- L15 _public member_ `FString SandboxBasePath = GetBaseSandboxDirectory();` — Directory in which sandboxes live. A new directory with the sandbox name will be created in this directory.
- L23 _public member_ `FFileSandboxCore_SandboxMetaData MetaData;` — Metadata to set about this new sandbox. The name will be used to create a base directory in the sandbox folder, so it must be non-empty and unique; invalid name leads to failure.
- L26 _public member_ `FSandboxInitArgs InitArgs;` — Base arguments for instantiating the sandbox environment.
- L28 _public function_ `explicit FNewSandboxArgs(FString InName, FString InDescription = {}) : MetaData(MoveTemp(InName), MoveTemp(InDescription))`
- L34 _public function_ `explicit FNewSandboxArgs(FFileSandboxCore_SandboxMetaData InMetaData) : MetaData(MoveTemp(InMetaData))`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Types/Manager/NewSandboxError.h` (Public)


#### enum `UE::FileSandboxCore::ENewSandboxErrorReason`  
`enum class ENewSandboxErrorReason : uint8`  
_L13-35_
- L16 _public enumerator_ `UnsuitablePath` — The specified directory cannot be used as root directory.
- L19 _public enumerator_ `IOError` — Some generic IO error occured (e.g. could not write manifest file, etc.)
- L25 _public enumerator_ `CannotLeaveSandbox` — Failed to leave the sandbox. Most likely because the sandbox is locked. If you need more info consider calling LeaveSandbox explicitly before.
- L28 _public enumerator_ `Unspecified` — Dummy error code for initializing to a deterministic value.
- L34 _public enumerator_ `Count` — ADD NEW MEMBERS ABOVE. Not a real reason.

#### struct `UE::FileSandboxCore::FNewSandboxError`  
`struct FNewSandboxError`  
_L38-41_
- desc: Explains why a new sandbox could not be created.
- L40 _public member_ `ENewSandboxErrorReason Reason = ENewSandboxErrorReason::Unspecified;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L44 _prototype_ `FString LexToString(ENewSandboxErrorReason InReason);` (scope `UE::FileSandboxCore`) — @return Error reason converted to a string.

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Types/Manager/SandboxCreationResult.h` (Public)


#### struct `UE::FileSandboxCore::TSandboxCreationResult`  
`template<typename TErrorType> struct TSandboxCreationResult : TValueOrError<TNotNull<ISandboxInstance*>, TErrorType>`  
_L20-27_
- inherits: `TValueOrError<TNotNull<ISandboxInstance*>,TErrorType>`
- desc: Utility type to allow implicit conversion to ISandboxInstance*, i.e. to allow shorthand semantics such as ISandboxManager* Manager = ...; if (ISandboxInstance* SandboxInstance = Manager->LoadNamedSandbox(...)) { ... }
- L22 _public typedef_ `using Super = TValueOrError<TNotNull<ISandboxInstance*>, TErrorType>;`
- L24 _public function_ `TSandboxCreationResult(TValueOrError<TNotNull<ISandboxInstance*>, TErrorType> Result) : Super(MoveTemp(Result))`
- L26 _public function_ `operator ISandboxInstance*() const`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Types/Manager/SandboxInitArgs.h` (Public)


#### struct `UE::FileSandboxCore::FSandboxInitArgs`  
`struct FSandboxInitArgs`  
_L15-39_
- desc: Arguments for creating a sandbox.
- L21 _public member_ `IPlatformFile* OverridePlatformFile = nullptr;` — System for saving out the sandboxed files. In theory, you could use this to save out the sandboxed files outside of the filesystem, e.g. to the cloud.
- L24 _public member_ `ESandboxInitFlags Flags = ESandboxInitFlags::Default;` — Additional feature flags for the sandbox.
- L32 _public member_ `TSharedPtr<ISandboxLock> Lock;` — Optional. You can use this to force the engine to stay in the sandbox until you return true. Whenever any API call attempts to make the engine leave the sandbox, this is used to check whether the sandbox is allowed to be left. The sandbox system will only keep a reference to this lock for as long as the sandbox is active.
- L35 _public member_ `TSharedPtr<IPackageReloadHandler> ReloadHandler;` — Optional. You can use this if you want to customize how packages are hot reloaded and purged.
- L38 _public function_ `IPlatformFile& GetPlatformFile() const` — @return The platform file to use.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Types/Package/HotReloadPackageArgs.h` (Public)


#### struct `UE::FileSandboxCore::FHotReloadPackageArgs`  
`struct FHotReloadPackageArgs`  
_L17-29_
- desc: Arguments for hot reloading packages. @see IPackageReloadHandler
- L20 _public member_ `ESandboxPackageReloadPhase Phase;` — Provides context for why the packages are being reloaded.
- L23 _public member_ `TConstArrayView<FName> PackageNames;` — The package names being reloaded.
- L25 _public function_ `explicit FHotReloadPackageArgs(ESandboxPackageReloadPhase Phase, const TConstArrayView<FName>& PackageNames) : Phase(Phase) , PackageNames(PackageNames)`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Types/Package/PurgePackageArgs.h` (Public)


#### struct `UE::FileSandboxCore::FPurgePackageArgs`  
`struct FPurgePackageArgs`  
_L17-29_
- desc: Arguments for purging packages. @see IPackageReloadHandler
- L20 _public member_ `ESandboxPackageReloadPhase Phase;` — Provides context for why the packages are being reloaded.
- L23 _public member_ `TConstArrayView<FName> PackageNames;` — The package names being reloaded.
- L25 _public function_ `explicit FPurgePackageArgs(ESandboxPackageReloadPhase Phase, const TConstArrayView<FName>& PackageNames) : Phase(Phase) , PackageNames(PackageNames)`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Types/Package/SandboxPackageReloadPhase.h` (Public)


#### enum `UE::FileSandboxCore::ESandboxPackageReloadPhase`  
`enum class ESandboxPackageReloadPhase : uint8`  
_L10-18_
- desc: Specifies a stage at which packages may be reloaded while sandboxed.
- L13 _public enumerator_ `Startup` — Sandbox is starting up and bringing files into the state of the sandbox.
- L15 _public enumerator_ `Sandboxed` — The engine is sandboxed and reloading files as part of an operation, e.g. reverting a change.
- L17 _public enumerator_ `Shutdown` — Sandbox is shutting down and cleaning up packages.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Types/PersistedFileInfo.h` (Public)


#### struct `UE::FileSandboxCore::FPersistedFileInfo`  
`struct FPersistedFileInfo`  
_L10-17_
- L13 _public member_ `FString FileName;` — File in the original file system (e.g. "D:/MyProject/Content/Levels/Map.umap").
- L16 _public member_ `FDateTime Timestamp;` — Timestamp of when the file was persisted (to detect if the file has been changed again after it was persisted).

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Types/RepositoryChangedEvent.h` (Public)


#### struct `UE::FileSandboxCore::FRepositoryChangedEvent`  
`struct FRepositoryChangedEvent`  
_L11-18_
- desc: Data describing a change in a repository
- L14 _public member_ `TConstArrayView<FString> AddedSandboxPaths;` — Root directories of sandboxes that have been added.
- L17 _public member_ `TConstArrayView<FString> RemovedSandboxPaths;` — Root directories of sandboxes that have been removed.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Types/Sandbox/PersistArgs.h` (Public)


#### struct `UE::FileSandboxCore::FPersistArgs`  
`struct FPersistArgs`  
_L15-31_
- desc: Input arguments for persisting a sandbox.
- L18 _public member_ `TConstArrayView<FString> Files;` — List of files names from the original filesystem, e.g. "D:/MyProject/Content/Levels/MyLevel.umap"
- L21 _public member_ `bool bShouldMakeWritableIfNoSourceControl = false;` — Whether to force the file writable when no source control provider is active.
- L30 _public member_ `IPersistFeedback* Feedback = nullptr;` — You can implement this to get interactive information about a persist operation. Useful for displaying a message about the persist operation or a progress bar. You can aggregate actions. @see FAggregatePersistFeedback

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Types/Sandbox/PersistResult.h` (Public)


#### enum `UE::FileSandboxCore::EPersistStatus`  
`enum class EPersistStatus : uint8`  
_L14-22_
- desc: Possible outcomes from a session persist.
- L17 _public enumerator_ `Success` — The packages were persisted correctly.
- L19 _public enumerator_ `Failure` — We failed to persist the packages.
- L21 _public enumerator_ `NotAllowed` — We are not allowed to persist.

#### struct `UE::FileSandboxCore::FPersistResult`  
`struct FPersistResult`  
_L25-29_
- desc: Result of a persist.
- L28 _public member_ `EPersistStatus PersistStatus = EPersistStatus::NotAllowed;` — Success or failure of the session persist.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Types/Sandbox/RevertArgs.h` (Public)


#### struct `UE::FileSandboxCore::FRevertArgs`  
`struct UE_EXPERIMENTAL(5.8, "Reverting of single files does not yet work for all cases. See UE-368478.") FRevertArgs`  
_L12-27_
- desc: Input arguments for reverting a sandbox.
- L21 _public member_ `TConstArrayView<FString> FilesToRevert;` — Non-sandbox paths to files that should be reverted. If this is left empty, then the operation reverts all file changes. This can be paths to files with any type of change (i.e. removed, edited, added). The path can be absolute or relative.
- L23 _public prototype_ `FRevertArgs() = default;`
- L24 _public function_ `explicit FRevertArgs(TConstArrayView<FString> InFilesToRevert) : FilesToRevert(InFilesToRevert)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Types/Sandbox/RevertResult.h` (Public)


#### struct `UE::FileSandboxCore::FRevertResult`  
`struct FRevertResult`  
_L11-24_
- desc: Result of reverting a sandbox.
- L17 _public member_ `TArray<FName> PackagesPendingHotReload;` — The package names that should be hot reloaded. You must call HotReloadPackages on them.
- L23 _public member_ `TArray<FName> PackagesPendingPurge;` — The package names that should be purged. You must call PurgePackages on them.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Types/SandboxFileChange.h` (Public)


#### enum `UE::FileSandboxCore::ESandboxFileChange`  
`enum class ESandboxFileChange : uint8`  
_L10-23_
- desc: Types of changes the sandbox system may make to a file.
- L13 _public enumerator_ `None` — No changes were made to the file.
- L16 _public enumerator_ `Added` — The file was added.
- L18 _public enumerator_ `Removed` — The file was removed.
- L20 _public enumerator_ `Edited` — The file was edited.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Types/SandboxInitFlags.h` (Public)


#### enum `UE::FileSandboxCore::ESandboxInitFlags`  
`enum class ESandboxInitFlags : uint8`  
_L10-21_
- L12 _public enumerator_ `None`
- L18 _public enumerator_ `ForceRedirectorsOnRenameInSourceControl = 1 << 0` — If the user is using source control, then renaming assets should cause redirectors to be created. Under the hood, it forces ISourceControlState::IsLocal() to return false.
- L20 _public enumerator_ `Default = ForceRedirectorsOnRenameInSourceControl`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L23 _prototype_ `ENUM_CLASS_FLAGS(ESandboxInitFlags);` (scope `UE::FileSandboxCore`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Types/SandboxMetaInfo.h` (Public)


#### struct `UE::FileSandboxCore::FSandboxMetaInfo`  
`struct FSandboxMetaInfo`  
_L11-26_
- L14 _public member_ `FFileSandboxCore_SandboxMetaData UserMetaData;` — User / API-user provided meta data.
- L17 _public member_ `FDateTime LastModified;` — Local time that the sandbox was last modified.
- L19 _public member_ `FFileSandboxCore_VersionInfo VersionInfo;` — Version that the sandbox was created in.
- L21 _public function_ `explicit FSandboxMetaInfo( FFileSandboxCore_SandboxMetaData InMetaData, FDateTime InLastModified, FFileSandboxCore_VersionInfo InVersionInfo ) : UserMetaData(MoveTemp(InMetaData)), LastModified(InLastModified), VersionInfo(MoveTemp(InVersionInfo))`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace FileSandboxCore` (scope `UE`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Types/SandboxedFileChangeInfo.h` (Public)


#### enum `UE::FileSandboxCore::EFileEnumerationFlags`  
`enum class EFileEnumerationFlags : uint8`  
_L18-23_
- desc: Flags enumerating file changes. @see ISandboxManager::EnumerateFileChanges @see ISandboxInstance::EnumerateFileChanges
- L20 _public enumerator_ `None`
- L21 _public enumerator_ `IncludeTimestamps = 1 << 0`
- L22 _public enumerator_ `All = IncludeTimestamps`

#### struct `UE::FileSandboxCore::FSandboxedFileChangeInfo`  
`struct FSandboxedFileChangeInfo`  
_L31-41_
- desc: Info about each file change enumerated. @see ISandboxManager::EnumerateFileChanges @see ISandboxInstance::EnumerateFileChanges
- L34 _public member_ `FString Path;` — Absolute non-sandbox file path.
- L37 _public member_ `ESandboxFileChange Action = ESandboxFileChange::None;` — The action performed on the file
- L40 _public member_ `FDateTime Timestamp = FDateTime::MinValue();` — Only set if EFileEnumerationFlags::IncludeTimestamps was specified

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L24 _prototype_ `ENUM_CLASS_FLAGS(EFileEnumerationFlags);` (scope `UE::FileSandboxCore`)

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Utils/BuiltInTags.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L10 _variable_ `constexpr FLazyName Tag_CommandLineSandbox("Com` (scope `UE::FileSandboxCore`) — Tag added to sandboxes that were created from command line.

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Utils/PackageSandboxUtils.h` (Public)


#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API FILESANDBOXCORE_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L14 _prototype_ `void PurgePackages(const TConstArrayView<FName>& InPackageNames);` (scope `UE::FileSandboxCore`) — Handles cleaning up assets that no longer exist.
- L17 _prototype_ `bool HotReloadPackages(const TConstArrayView<FName>& InPackageNames);` (scope `UE::FileSandboxCore`) — Reloads packages that were modified
- L18 _prototype_ `bool HotReloadPackages(const TConstArrayView<UPackage*>& InPackages);` (scope `UE::FileSandboxCore`)
- L21 _prototype_ `TArray<UPackage*> GetDirtyPackages();` (scope `UE::FileSandboxCore`) — @return Packages with in-memory changes.
- L23 _function_ `inline bool HasDirtyPackages()` (scope `UE::FileSandboxCore`) — @return Whether there are packages with in-memory changes.
- L33 _prototype_ `void AppendExternalPersistentLevelForReload( TArray<FName>& InOutPackagesPendingHotReload, TConstArrayView<FName> InPackagesPendingPurge);` (scope `UE::FileSandboxCore`) — If the current editor world's persistent level uses external objects (i.e. a World Partition level), schedule its package for hot reload. This ensures the full WP state is rebuilt from disk when a sandbox is discarded, clearing any in-memory actors whose per-actor packages only existed in the sandbox. No-op if the package is already scheduled for purge or already in the hot-reload list, or if the current world's persistent level is not using external objects.

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Utils/SandboxDirectoryUtils.h` (Public)


#### enum `UE::FileSandboxCore::ESandboxRenameSuitability`  
`enum class ESandboxRenameSuitability : uint8`  
_L77-92_
- desc: Explains why a sandbox can or cannot be renamed.
- L79 _public enumerator_ `Allowed`
- L82 _public enumerator_ `SandboxDoesNotExist` — The sandbox does not exist
- L84 _public enumerator_ `ActiveSandbox` — You cannot rename an active sandbox
- L87 _public enumerator_ `NameIsSame` — The name is not different from the current name.
- L89 _public enumerator_ `InvalidDirectory` — Sandbox cannot have this name
- L91 _public enumerator_ `EmptyName` — Name cannot be empty

#### enum `UE::FileSandboxCore::EDirectorySuitability`  
`enum class EDirectorySuitability : uint8`  
_L123-131_
- L125 _public enumerator_ `Suitable`
- L126 _public enumerator_ `EmptyName`
- L127 _public enumerator_ `NameTooLong`
- L128 _public enumerator_ `DuplicateName`
- L129 _public enumerator_ `InvalidPath`
- L130 _public enumerator_ `DirectoryAlreadyExists`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API FILESANDBOXCORE_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L19 _typedef_ `using FProcessSandboxDirectorySignature = EBreakBehavior(const FString& InBaseDirectory);` (scope `UE::FileSandboxCore`)
- L22 _prototype_ `FString GetBaseSandboxDirectory();` (scope `UE::FileSandboxCore`) — @return The base directory into which new sandboxes are stored.
- L30 _prototype_ `void ForEachSandbox( TFunctionRef<FProcessSandboxDirectorySignature> InProcessSandbox, const FString& InBaseDirectory = GetBaseSandboxDirectory() );` (scope `UE::FileSandboxCore`) — Enumerates all directories that contain a sandbox. The search only considers the top-level directories. @param InProcessSandbox Invokes for each found sandbox. @param InBaseDirectory Base directory search for. Either absolute or relative to the process BaseDir().
- L36 _prototype_ `bool IsRootSandboxDirectory(const FString& InRootDirectory);` (scope `UE::FileSandboxCore`) — @return Whether this is a path to the root of a sandbox, i.e. whether it contains the manifest and the metadata file.
- L48 _prototype_ `bool SaveMetaData( const FFileSandboxCore_SandboxMetaData& NewMetaData, const FString& InSandboxDirectory );` (scope `UE::FileSandboxCore`) — Writes new metadata for a sandbox. You are allowed to change only the sandbox name. However, it will not rename the sandbox directory. To rename the directory, @see RenameSandboxWithDirectory. @param NewMetaData The new metadata to set for the sandbox. @param InSandboxDirectory Path to the base directory of the sandbox, e.g. what's returned by ForEachSandbox. Either absolute or relative to the process BaseDir().
- L56 _prototype_ `TOptional<FFileSandboxCore_SandboxMetaData> LoadMetaData(const FString& InSandboxDirectory);` (scope `UE::FileSandboxCore`) — Reads metadata about a sandbox. @param InSandboxDirectory Path to the base directory of the sandbox, e.g. what's returned by ForEachSandbox. Either absolute or relative to the process BaseDir().
- L70 _prototype_ `bool RenameSandboxWithDirectory( const FString& InNewName, const FString& InOldName, const FString& InBaseDirectory = GetBaseSandboxDirectory(), const FFileSandboxCore_SandboxMetaData* InNewMetaData = nullptr );` (scope `UE::FileSandboxCore`) — Renames the sandbox located in InBaseDirectory / InOldName. By default, sandboxes are placed in BaseDir / SandboxName. This function renames the containing directory to the new name. This also updates the manifest file with the new name. @param InNewName The new name the sandbox should have @param InOldName The sandbox you want to rename. The sandbox root is located in InBaseDirectory / InOldName directory. @param InBaseDirectory Base directory search for. Either absolute or relative to the process BaseDir(). @param InNewMetaData Optional additional metadata you want to set. Specifying this will avoid loading the metadata from disk first. @return Whether the sandbox was successfully renamed
- L95 _prototype_ `ESandboxRenameSuitability CanRenameSandboxWithDirectory( const FString& InNewName, const FString& InOldName, const FString& InBaseDirectory = GetBaseSandboxDirectory() );` (scope `UE::FileSandboxCore`) — @return Whether InNewName is a valid new name for the sandbox located in InBaseDirectory / InOldName.
- L99 _prototype_ `bool IsAllowedToRenameSandbox(const FString& InSandboxDirectory);` (scope `UE::FileSandboxCore`) — @return Whether the given sandbox can be renamed, i.e. it is not active.
- L103 _prototype_ `FDateTime GetLastModified(const FString& InSandboxDirectory);` (scope `UE::FileSandboxCore`) — @return When the given sandbox was last modified. Returns FDateTime::MinValue() on failure.
- L106 _prototype_ `FFileSandboxCore_VersionInfo LoadVersionInfo(const FString& InSandboxDirectory);` (scope `UE::FileSandboxCore`) — @return Version info for the sandbox saved in this directory. This loads the data from the manifest file. IsInitialized returns false if this fails.
- L116 _prototype_ `TOptional<FString> FindSandboxByName( const FString& InSandboxName, const FString& InBaseDirectory = GetBaseSandboxDirectory() );` (scope `UE::FileSandboxCore`) — Searches for sandboxes with the given name. The search only considers the top-level directories. @param InSandboxName The name of the sandbox @param InBaseDirectory Base directory search for. Either absolute or relative to the process BaseDir(). @return The path to the directory containing the sandbox with the specified name.
- L134 _prototype_ `EDirectorySuitability DetermineDirectorySuitability( const FString& InSandboxName, const FString& InBaseDirectory = GetBaseSandboxDirectory(), FText* OutReason = nullptr );` (scope `UE::FileSandboxCore`) — @return Whether a sandbox directory named InSandboxName can be put into the InBaseDirectory.
- L141 _prototype_ `FText FormatDirectorySuitabilityAsReason( EDirectorySuitability Suitability, const FString& InSandboxName, const FString& InBaseDirectory = GetBaseSandboxDirectory() );` (scope `UE::FileSandboxCore`) — @return EDirectorySuitability explained as reason to the user.
- L155 _prototype_ `TOptional<FString> GetSandboxPathFor(const FString& InSandboxDirectory, const FString& InNonSandboxPath);` (scope `UE::FileSandboxCore`) — Gets the file path to the file that saves the sandboxed state of InNonSandboxPath. This only works for edited and added files. For removed files, this returns nothing. @param InSandboxDirectory Path to the base directory of the sandbox, e.g. what's returned by ForEachSandbox. Either absolute or relative to the process BaseDir(). @param InNonSandboxPath Path to a non-sandbox file of which you want to get the sandbox file. @return Path to sandboxed file corresponding to the non-sandbox file, if the file has a sandboxed edit or add operation. Unset, otherwise.
- L158 _prototype_ `TOptional<FString> GetSandboxName(const FString& InSandboxDirectory);` (scope `UE::FileSandboxCore`) — @return Name of the sandbox if the directory is the root of a sandbox. Unset otherwise.

### `Plugins/Developer/Sandbox/FileSandbox/Source/FileSandboxCore/Public/Utils/ZipTransferUtils.h` (Public)


#### struct `UE::FileSandboxCore::ZipUtils::FImportInspectionResult`  
`struct FImportInspectionResult`  
_L25-45_
- desc: Holds the result for inspecting whether a zip archive is suitable for importing. This also contains data produced as side effects, which can be reused for importing.
- L28 _public member_ `TUniquePtr<FZipArchiveReader> Reader;` — The zip reader that was produced as side effect. You can re-use this for the import operation.
- L30 _public member_ `TArray<FString> AllFileNames;` — All file names in the archive. Produced as side effect.
- L33 _public member_ `FString SandboxName;` — The name of the sandbox contained in the zip. Produced as side effect.
- L35 _public member_ `TArray<uint8> ManifestBytes;` — Manifest file content. Produced as side effect.
- L37 _public member_ `TArray<uint8> MetadataBytes;` — Metadata file content. Produced as side effect.
- L39 _public member_ `TOptional<FFileSandboxCore_SandboxMetaData> MetaData;` — Metadata. Produced as side effect.
- L41 _public prototype_ `explicit FImportInspectionResult(TUniquePtr<FZipArchiveReader> InReader);`
- L44 _public function_ `bool IsValid() const` — @return Whether the zip archive is valid to import from.

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API FILESANDBOXCORE_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L16 _namespace_ `namespace ZipUtils` (scope `UE::FileSandboxCore`)
- L19 _prototype_ `bool ExportSandboxToZip(const FString& InSandboxRoot, const FString& InOutputZipPath);` (scope `UE::FileSandboxCore::ZipUtils`) — Zips up a sandbox and saves it to the destination.
- L55 _prototype_ `TOptional<FImportInspectionResult> InspectFileForImport(const FString& InPathToZip);` (scope `UE::FileSandboxCore::ZipUtils`) — Inspects whether a zip contains a sandbox valid for importing, i.e. - the zip must be valid, - must contain exactly one root directory with the name of the sandbox, - must contain required files (manifest and metadata) @return Result of inspecting the zip. Unset if I/O errors occurs. @note Creates IFileHandle that FZipArchiveReader takes ownership of until destroyed.
- L61 _prototype_ `bool ImportSandboxFromZip(const FImportInspectionResult& InInspection, const FString& InSandboxTargetRoot);` (scope `UE::FileSandboxCore::ZipUtils`) — Unzips a zip and imports it to the sandbox system reusing any data produced during inspection. @note Pre-existing files in the target directory will be deleted.
