# Plugins / HTTPChunkInstaller

- module root: `Plugins/Runtime/HTTPChunkInstaller/Source`
- headers: 7; symbols: 235
- symbol kinds: class=9, delegate=4, enum=2, enumerator=18, function=49, macro=9, member=92, namespace=1, prototype=43, struct=3, typedef=5
- PrivateDependencyModuleNames: ApplicationCore, BuildPatchServices, Core, Engine, HTTP, Json, PakFile

### `Plugins/Runtime/HTTPChunkInstaller/Source/Public/ChunkInstall.h` (Public)


#### class `FChunkInstallTask`  
`class FChunkInstallTask : public FRunnable`  
_L18-161_
- inherits: `FRunnable`
- L22 _public member_ `FString ManifestPath;` — Input parameters
- L23 _public member_ `FString HoldingManifestPath;`
- L24 _public member_ `FString SrcDir;`
- L25 _public member_ `FString DestDir;`
- L26 _public member_ `IBuildPatchServicesModule* BPSModule;`
- L27 _public member_ `IBuildManifestPtr BuildManifest;`
- L28 _public member_ `bool bCopy;`
- L29 _public member_ `const TArray<FString>* CurrentMountPaks;`
- L30 _public member_ `FEvent* CompleteEvent;`
- L32 _public member_ `TArray<FString> MountedPaks;` — Output
- L34 _public function_ `FChunkInstallTask()`
- L39 _public function_ `~FChunkInstallTask()`
- L45 _public function_ `void SetupWork(FString InManifestPath, FString InHoldingManifestPath, FString InSrcDir, FString InDestDir, IBuildPatchServicesModule* InBPSModule, IBuildManifestRef InBuildManifest, const TArray<FString>& InCurrentMountedPaks, bool bInCopy)`
- L60 _public function_ `void DoWork()`
- L141 _public function_ `uint32 Run()`
- L147 _public function_ `bool IsDone()`
- L152 _public function_ `static const TCHAR *Name()`
- L157 _public function_ `inline TStatId GetStatId() const`

#### class `FChunkInstallTask::DoWork::FPakSearchVisitor`  
`class FPakSearchVisitor : public IPlatformFile::FDirectoryVisitor`  
_L63-82_
- inherits: `IPlatformFile::FDirectoryVisitor`
- desc: Helper class to find all pak files.
- L65 _private member_ `TArray<FString>& FoundPakFiles;`
- L67 _public function_ `FPakSearchVisitor(TArray<FString>& InFoundPakFiles) : FoundPakFiles(InFoundPakFiles)`
- L70 _public function_ `virtual bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory)`

### `Plugins/Runtime/HTTPChunkInstaller/Source/Public/ChunkSetup.h` (Public)


#### class `FFileSearchVisitor`  
`class FFileSearchVisitor : public IPlatformFile::FDirectoryVisitor`  
_L17-38_
- inherits: `IPlatformFile::FDirectoryVisitor`
- desc: Helper class to find all pak/mainfests files.
- L19 _private member_ `FString FileWildcard;`
- L20 _private member_ `TArray<FString>& FoundFiles;`
- L22 _public function_ `FFileSearchVisitor(FString InFileWildcard, TArray<FString>& InFoundFiles) : FileWildcard(InFileWildcard) , FoundFiles(InFoundFiles)`
- L26 _public function_ `virtual bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory)`

#### class `FChunkSetupTask`  
`class FChunkSetupTask : public FRunnable, public IPlatformFile::FDirectoryVisitor`  
_L42-197_
- inherits: `FRunnable,IPlatformFile::FDirectoryVisitor`
- L46 _public member_ `IBuildPatchServicesModule* BPSModule;` — Input parameters
- L47 _public member_ `FString InstallDir;` — Intermediate directory where installed chunks may be waiting
- L48 _public member_ `FString ContentDir;` — Directory where installed chunks need to live to be mounted
- L49 _public member_ `FString HoldingDir;` — Directory where manifest for chunks that are out of date and can be use for updates but not mounted.
- L50 _public member_ `const TArray<FString>* CurrentMountPaks;` — Array of already mounted Paks
- L52 _public member_ `FEvent* CompleteEvent;` — Output
- L53 _public member_ `TArray<FString> MountedPaks;`
- L54 _public member_ `TMultiMap<uint32, IBuildManifestPtr> InstalledChunks;`
- L55 _public member_ `TMultiMap<uint32, IBuildManifestPtr> HoldingChunks;`
- L57 _public member_ `TArray<FString> FoundPaks;` — Working
- L58 _public member_ `TArray<FString> FoundManifests;`
- L59 _public member_ `FFileSearchVisitor PakVisitor;`
- L60 _public member_ `FFileSearchVisitor ManifestVisitor;`
- L61 _public member_ `TArray<FString> ManifestsToRemove;`
- L62 _public member_ `uint32 Pass;`
- L64 _public function_ `FChunkSetupTask() : BPSModule(nullptr) , CurrentMountPaks(nullptr) , PakVisitor(TEXT("*.pak"), FoundPaks) , ManifestVisitor(TEXT("*.manifest"), FoundManifests)`
- L73 _public function_ `virtual ~FChunkSetupTask()`
- L78 _public function_ `void SetupWork(IBuildPatchServicesModule* InBPSModule, FString InInstallDir, FString InContentDir, FString InHoldingDir, const TArray<FString>& InCurrentMountedPaks)`
- L96 _public function_ `void DoWork()`
- L111 _public function_ `bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory) override`
- L177 _public function_ `static const TCHAR *Name()`
- L182 _public function_ `inline TStatId GetStatId() const`
- L187 _public function_ `uint32 Run()`
- L193 _public function_ `bool IsDone()`

#### class `FChunkMountTask`  
`class FChunkMountTask : public FRunnable, public IPlatformFile::FDirectoryVisitor`  
_L199-350_
- inherits: `FRunnable,IPlatformFile::FDirectoryVisitor`
- L203 _public member_ `IBuildPatchServicesModule* BPSModule;` — Input parameters
- L204 _public member_ `FString ContentDir;` — Directory where installed chunks need to live to be mounted
- L205 _public member_ `const TArray<FString>* CurrentMountPaks;` — Array of already mounted Paks
- L206 _public member_ `const TSet<uint32>* ExpectedChunks;` — Manifests expected to be seen. Chunks not in this list are deleted
- L208 _public member_ `FEvent* CompleteEvent;` — Output
- L209 _public member_ `TArray<FString> MountedPaks;`
- L211 _public member_ `TArray<FString> FoundPaks;` — Working
- L212 _public member_ `TArray<FString> FoundManifests;`
- L213 _public member_ `TArray<FString> ChunkInstallToDestroy;`
- L214 _public member_ `FFileSearchVisitor PakVisitor;`
- L215 _public member_ `FFileSearchVisitor ManifestVisitor;`
- L217 _public function_ `FChunkMountTask() : BPSModule(nullptr) , CurrentMountPaks(nullptr) , PakVisitor(TEXT("*.pak"), FoundPaks) , ManifestVisitor(TEXT("*.manifest"), FoundManifests)`
- L226 _public function_ `~FChunkMountTask()`
- L231 _public function_ `void SetupWork(IBuildPatchServicesModule* InBPSModule, FString InContentDir, const TArray<FString>& InCurrentMountedPaks, const TSet<uint32>& InExpectedChunks)`
- L246 _public function_ `void DoWork()`
- L257 _public function_ `bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory) override`
- L330 _public function_ `static const TCHAR *Name()`
- L335 _public function_ `inline TStatId GetStatId() const`
- L340 _public function_ `uint32 Run()`
- L346 _public function_ `bool IsDone()`

### `Plugins/Runtime/HTTPChunkInstaller/Source/Public/CloudDelegateMacros.h` (Public)


#### Free symbols / members of external scopes

- L7 _macro_ `#define DEFINE_CLOUD_DELEGATE_BASE(DelegateName) \`
- L22 _macro_ `#define DEFINE_CLOUD_DELEGATE(DelegateName) \`
- L29 _macro_ `#define DEFINE_CLOUD_DELEGATE_ONE_PARAM(DelegateName, Param1Type) \`
- L36 _macro_ `#define DEFINE_CLOUD_DELEGATE_TWO_PARAM(DelegateName, Param1Type, Param2Type) \`
- L43 _macro_ `#define DEFINE_CLOUD_DELEGATE_THREE_PARAM(DelegateName, Param1Type, Param2Type, Param3Type) \`
- L50 _macro_ `#define DEFINE_CLOUD_DELEGATE_FOUR_PARAM(DelegateName, Param1Type, Param2Type, Param3Type, Param4Type) \`
- L57 _macro_ `#define DEFINE_CLOUD_DELEGATE_FIVE_PARAM(DelegateName, Param1Type, Param2Type, Param3Type, Param4Type, Param5Type) \`
- L64 _macro_ `#define DEFINE_CLOUD_DELEGATE_SIX_PARAM(DelegateName, Param1Type, Param2Type, Param3Type, Param4Type, Param5Type, Param6Type) \`
- L71 _macro_ `#define DEFINE_CLOUD_DELEGATE_SEVEN_PARAM(DelegateName, Param1Type, Param2Type, Param3Type, Param4Type, Param5Type, Param6Type, Param7Type) \`

### `Plugins/Runtime/HTTPChunkInstaller/Source/Public/CloudTitleFileInterface.h` (Public)


#### class `FCloudPagedQuery`  
`class FCloudPagedQuery`  
_L11-29_
- desc: Paging info needed for a request that can return paged results
- L14 _public function_ `FCloudPagedQuery(int32 InStart = 0, int32 InCount = -1) : Start(InStart) , Count(InCount)`
- L20 _public function_ `bool IsValidRange() const` — @return true if valid range
- L26 _public member_ `int32 Start;` — first entry to fetch
- L28 _public member_ `int32 Count;` — total entries to fetch. -1 means ALL

#### struct `FCloudHeader`  
`struct FCloudHeader`  
_L32-77_
- desc: Holds metadata about a given downloadable file
- L35 _public member_ `FString Hash;` — Hash value, if applicable, of the given file contents
- L37 _public member_ `FName HashType;` — The hash algorithm used to sign this file
- L39 _public member_ `FString DLName;` — Filename as downloaded
- L41 _public member_ `FString FileName;` — Logical filename, maps to the downloaded filename
- L43 _public member_ `int32 FileSize;` — File size
- L45 _public member_ `FString URL;` — The full URL to download the file if it is stored in a CDN or separate host site
- L47 _public member_ `uint32 ChunkID;` — The chunk id this file represents
- L50 _public function_ `FCloudHeader() : FileSize(0), ChunkID(0)` — Constructors
- L55 _public function_ `FCloudHeader(const FString& InFileName, const FString& InDLName, int32 InFileSize) : DLName(InDLName), FileName(InFileName), FileSize(InFileSize), ChunkID(0)`
- L62 _public function_ `bool operator==(const FCloudHeader& Other) const`
- L73 _public function_ `bool operator<(const FCloudHeader& Other) const`

#### enum `ECloudAsyncTaskState::Type`  
`enum Type`  
_L82-92_
- L85 _public enumerator_ `NotStarted` — The task has not been started
- L87 _public enumerator_ `InProgress` — The task is currently being processed
- L89 _public enumerator_ `Done` — The task has completed successfully
- L91 _public enumerator_ `Failed` — The task failed to complete

#### struct `FCloudEntry`  
`struct FCloudEntry`  
_L121-143_
- desc: Holds the data used in downloading a file asynchronously from the online service
- L124 _public member_ `FString FileName;` — The name of the file as requested
- L126 _public member_ `ECloudAsyncTaskState::Type AsyncState;` — The async state the file download is in
- L128 _public member_ `TArray<uint8> Data;` — The buffer of data for the file
- L131 _public function_ `FCloudEntry() : AsyncState(ECloudAsyncTaskState::NotStarted)` — Constructors
- L136 _public function_ `FCloudEntry(const FString& InFileName) : FileName(InFileName), AsyncState(ECloudAsyncTaskState::NotStarted)`
- L142 _public function_ `virtual ~FCloudEntry()`

#### class `ICloudTitleFile`  
`class ICloudTitleFile`  
_L173-264_
- L176 _protected function_ `ICloudTitleFile()`
- L179 _public function_ `virtual ~ICloudTitleFile()`
- L189 _public prototype_ `virtual bool GetFileContents(const FString& FileName, TArray<uint8>& FileContents) = 0;` — Copies the file data into the specified buffer for the specified file @param FileName the name of the file to read @param FileContents the out buffer to copy the data into @return true if the data was copied, false otherwise
- L196 _public prototype_ `virtual bool ClearFiles() = 0;` — Empties the set of downloaded files if possible (no async tasks outstanding) @return true if they could be deleted, false if they could not
- L205 _public prototype_ `virtual bool ClearFile(const FString& FileName) = 0;` — Empties the cached data for this file if it is not being downloaded currently @param FileName the name of the file to remove from the cache @return true if it could be deleted, false if it could not
- L212 _public prototype_ `virtual void DeleteCachedFiles(bool bSkipEnumerated) = 0;` — Delete cached files on disk @param bSkipEnumerated if true then only non-enumerated files are deleted
- L221 _public prototype_ `virtual bool EnumerateFiles(const FCloudPagedQuery& Page = FCloudPagedQuery()) = 0;` — Requests a list of available files from the network store @param Page paging info to use for query @return true if the request has started, false if not
- L229 _public prototype_ `DEFINE_CLOUD_DELEGATE_ONE_PARAM(OnEnumerateFilesComplete, bool);` — Delegate fired when the list of files has been returned from the network store @param bWasSuccessful whether the file list was successful or not
- L237 _public prototype_ `virtual void GetFileList(TArray<FCloudHeader>& Files) = 0;` — Returns the list of files that was returned by the network store @param Files out array of file metadata
- L246 _public prototype_ `virtual bool ReadFile(const FString& FileName) = 0;` — Starts an asynchronous read of the specified file from the network platform's file store @param FileToRead the name of the file to read @return true if the calls starts successfully, false otherwise
- L255 _public prototype_ `DEFINE_CLOUD_DELEGATE_TWO_PARAM(OnReadFileComplete, bool, const FString&);` — Delegate fired when a file read from the network platform's storage is complete @param bWasSuccessful whether the file read was successful or not @param FileName the name of the file this was for
- L263 _public prototype_ `DEFINE_CLOUD_DELEGATE_TWO_PARAM(OnReadFileProgress, const FString&, uint64);` — Delegate fired when as file read from the network platform's storage progresses @param FileName the name of the file this was for @param NumBytes the number of bytes read so far

#### Free symbols / members of external scopes

- L80 _namespace_ `namespace ECloudAsyncTaskState`
- L95 _function_ `inline const TCHAR* ToString(ECloudAsyncTaskState::Type EnumVal)` (scope `ECloudAsyncTaskState`) — @return the stringified version of the enum passed in
- L151 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnEnumerateFilesComplete, bool);` — Delegate fired when the list of files has been returned from the network store @param bWasSuccessful whether the file list was successful or not
- L151 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnEnumerateFilesComplete, bool);` — Delegate fired when the list of files has been returned from the network store @param bWasSuccessful whether the file list was successful or not
- L152 _typedef_ `typedef FOnEnumerateFilesComplete::FDelegate FOnEnumerateFilesCompleteDelegate;`
- L160 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnReadFileProgress, const FString&, uint64);` — Delegate fired when as file read from the network platform's storage progresses @param FileName the name of the file this was for @param NumBytes the number of bytes read so far
- L160 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnReadFileProgress, const FString&, uint64);` — Delegate fired when as file read from the network platform's storage progresses @param FileName the name of the file this was for @param NumBytes the number of bytes read so far
- L161 _typedef_ `typedef FOnReadFileProgress::FDelegate FOnReadFileProgressDelegate;`
- L170 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnReadFileComplete, bool, const FString&);` — Delegate fired when a file read from the network platform's storage is complete @param bWasSuccessful whether the file read was successful or not @param FileName the name of the file this was for
- L170 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnReadFileComplete, bool, const FString&);` — Delegate fired when a file read from the network platform's storage is complete @param bWasSuccessful whether the file read was successful or not @param FileName the name of the file this was for
- L171 _typedef_ `typedef FOnReadFileComplete::FDelegate FOnReadFileCompleteDelegate;`
- L266 _typedef_ `typedef TSharedPtr<ICloudTitleFile, ESPMode::ThreadSafe> ICloudTitleFilePtr;`
- L267 _typedef_ `typedef TSharedRef<ICloudTitleFile, ESPMode::ThreadSafe> ICloudTitleFileRef;`

### `Plugins/Runtime/HTTPChunkInstaller/Source/Public/HTTPChunkInstaller.h` (Public)


#### class `FHTTPChunkInstall`  
`class FHTTPChunkInstall : public FGenericPlatformChunkInstall, public FTSTickerObjectBase`  
_L15-162_
- inherits: `FGenericPlatformChunkInstall,FTSTickerObjectBase`
- desc: HTTP based implementation of chunk based install
- L18 _public prototype_ `FHTTPChunkInstall();`
- L19 _public prototype_ `~FHTTPChunkInstall();`
- L21 _public function_ `virtual bool GetProgressReportingTypeSupported(EChunkProgressReportingType::Type ReportType) override`
- L31 _public prototype_ `virtual float GetChunkProgress( uint32 ChunkID, EChunkProgressReportingType::Type ReportType ) override;`
- L33 _public function_ `virtual EChunkInstallSpeed::Type GetInstallSpeed() override`
- L38 _public function_ `virtual bool SetInstallSpeed( EChunkInstallSpeed::Type InInstallSpeed ) override`
- L52 _public prototype_ `virtual bool PrioritizeChunk( uint32 ChunkID, EChunkPriority::Type Priority ) override;`
- L54 _public function_ `virtual bool DebugStartNextChunk()`
- L61 _public prototype_ `bool Tick(float DeltaSeconds) override;`
- L63 _public prototype_ `void EndInstall();`
- L67 _private prototype_ `void InitialiseSystem();`
- L68 _private prototype_ `bool AddDataToFileCache(const FString& ManifestHash,const TArray<uint8>& Data);`
- L69 _private prototype_ `bool IsDataInFileCache(const FString& ManifestHash);`
- L70 _private prototype_ `bool GetDataFromFileCache(const FString& ManifestHash,TArray<uint8>& Data);`
- L71 _private prototype_ `bool RemoveDataFromFileCache(const FString& ManifestHash);`
- L72 _private prototype_ `void UpdatePendingInstallQueue();`
- L73 _private prototype_ `IBuildManifestPtr FindPreviousInstallManifest(const IBuildManifestPtr& ChunkManifest);`
- L74 _private prototype_ `void BeginChunkInstall(uint32 NextChunkID,IBuildManifestPtr ChunkManifest, IBuildManifestPtr PrevInstallChunkManifest);`
- L75 _private prototype_ `void ParseTitleFileManifest(const FString& ManifestFileHash);`
- L76 _private prototype_ `bool BuildChunkFolderName(IBuildManifestRef Manifest, FString& ChunkFdrName, FString& ManifestName, uint32& ChunkID, bool& bIsPatch);`
- L77 _private prototype_ `void OSSEnumerateFilesComplete(bool bSuccess);`
- L78 _private prototype_ `void OSSReadFileComplete(bool bSuccess, const FString& Filename);`
- L79 _private prototype_ `void OSSInstallComplete(const IBuildInstallerRef& Installer);`
- L81 _private prototype_ `virtual EChunkLocation::Type GetChunkLocation(uint32 ChunkID) override;`
- L124 _private member_ `FChunkInstallTask ChunkCopyInstall;`
- L125 _private member_ `TUniquePtr<FRunnableThread> ChunkCopyInstallThread;`
- L126 _private member_ `FChunkSetupTask ChunkSetupTask;`
- L127 _private member_ `TUniquePtr<FRunnableThread> ChunkSetupTaskThread;`
- L128 _private member_ `FChunkMountTask ChunkMountTask;`
- L129 _private member_ `TUniquePtr<FRunnableThread> ChunkMountTaskThread;`
- L130 _private member_ `TMultiMap<uint32, IBuildManifestPtr> InstalledManifests;`
- L131 _private member_ `TMultiMap<uint32, IBuildManifestPtr> PrevInstallManifests;`
- L132 _private member_ `TMultiMap<uint32, IBuildManifestPtr> RemoteManifests;`
- L133 _private member_ `TSet<FString> ManifestsInMemory;`
- L134 _private member_ `TSet<uint32> ExpectedChunks;`
- L135 _private member_ `TArray<FCloudHeader> TitleFilesToRead;`
- L136 _private member_ `TArray<uint8> FileContentBuffer;`
- L137 _private member_ `TArray<FChunkPrio> PriorityQueue;`
- L138 _private member_ `TArray<FString> MountedPaks;`
- L139 _private member_ `ICloudTitleFilePtr OnlineTitleFile;`
- L140 _private member_ `ICloudTitleFilePtr OnlineTitleFileHttp;`
- L141 _private member_ `IBuildInstallerPtr InstallService;`
- L142 _private member_ `IBuildManifestPtr InstallingChunkManifest;`
- L143 _private member_ `FDelegateHandle EnumFilesCompleteHandle;`
- L144 _private member_ `FDelegateHandle ReadFileCompleteHandle;`
- L145 _private member_ `FString CloudDir;`
- L146 _private member_ `FString CloudDirectory;`
- L147 _private member_ `FString StageDir;`
- L148 _private member_ `FString InstallDir;`
- L149 _private member_ `FString BackupDir;`
- L150 _private member_ `FString ContentDir;`
- L151 _private member_ `FString CacheDir;`
- L152 _private member_ `FString HoldingDir;`
- L153 _private member_ `IBuildPatchServicesModule* BPSModule;`
- L154 _private member_ `uint32 InstallingChunkID;`
- L155 _private member_ `ChunkInstallState InstallerState;`
- L156 _private member_ `EChunkInstallSpeed::Type InstallSpeed;`
- L157 _private member_ `bool bFirstRun;`
- L158 _private member_ `bool bSystemInitialised;`
- L160 _private member_ `bool bDebugNoInstalledRequired;`

#### enum `FHTTPChunkInstall::ChunkInstallState`  
`enum struct ChunkInstallState`  
_L83-99_
- L85 _public enumerator_ `Setup`
- L86 _public enumerator_ `SetupWait`
- L87 _public enumerator_ `QueryRemoteManifests`
- L88 _public enumerator_ `EnterOfflineMode`
- L89 _public enumerator_ `MoveInstalledChunks`
- L90 _public enumerator_ `RequestingTitleFiles`
- L91 _public enumerator_ `SearchTitleFiles`
- L92 _public enumerator_ `ReadTitleFiles`
- L93 _public enumerator_ `WaitingOnRead`
- L94 _public enumerator_ `ReadComplete`
- L95 _public enumerator_ `PostSetup`
- L96 _public enumerator_ `Idle`
- L97 _public enumerator_ `Installing`
- L98 _public enumerator_ `CopyToContent`

#### struct `FHTTPChunkInstall::FChunkPrio`  
`struct FChunkPrio`  
_L101-122_
- L103 _public function_ `FChunkPrio(uint32 InChunkID, EChunkPriority::Type InChunkPrio) : ChunkID(InChunkID) , ChunkPrio(InChunkPrio)`
- L110 _public member_ `uint32 ChunkID;`
- L111 _public member_ `EChunkPriority::Type ChunkPrio;`
- L113 _public function_ `bool operator == (const FChunkPrio& RHS) const`
- L118 _public function_ `bool operator < (const FChunkPrio& RHS) const`

### `Plugins/Runtime/HTTPChunkInstaller/Source/Public/HTTPChunkInstallerLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogHTTPChunkInstaller, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogHTTPChunkInstaller, Log, All);`

### `Plugins/Runtime/HTTPChunkInstaller/Source/Public/LocalTitleFile.h` (Public)


#### class `FLocalTitleFile`  
`class FLocalTitleFile : public ICloudTitleFile`  
_L7-32_
- inherits: `ICloudTitleFile`
- L11 _public prototype_ `FLocalTitleFile(const FString& InRootDirectory);`
- L15 _public prototype_ `virtual bool GetFileContents(const FString& DLName, TArray<uint8>& FileContents) override;`
- L16 _public prototype_ `virtual bool ClearFiles() override;`
- L17 _public prototype_ `virtual bool ClearFile(const FString& DLName) override;`
- L18 _public prototype_ `virtual void DeleteCachedFiles(bool bSkipEnumerated) override;`
- L19 _public prototype_ `virtual bool EnumerateFiles(const FCloudPagedQuery& Page = FCloudPagedQuery()) override;`
- L20 _public prototype_ `virtual void GetFileList(TArray<FCloudHeader>& InFileHeaders) override;`
- L21 _public prototype_ `virtual bool ReadFile(const FString& DLName) override;`
- L25 _protected prototype_ `FString GetFileNameFromDLName(const FString& DLName) const;`
- L29 _private member_ `FString RootDirectory;`
- L30 _private member_ `TArray<FCloudHeader> FileHeaders;`
- L31 _private member_ `TMap< FString, TArray<uint8> > DLNameToFileContents;`
