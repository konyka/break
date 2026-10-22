# Runtime / BuildPatchServices

- module root: `Source/Runtime/Online/BuildPatchServices`
- headers: 102; symbols: 3033
- symbol kinds: class=162, delegate=28, enum=35, enumerator=220, function=274, macro=27, member=794, namespace=116, prototype=1159, struct=96, typedef=60, variable=62
- PrivateDependencyModuleNames: Analytics, AnalyticsET, CoreUObject, HTTP, Json
- PrivateIncludePathModuleNames: HTTP
- PublicDependencyModuleNames: Core

### `Source/Runtime/Online/BuildPatchServices/Private/BuildPatchFileConstructor.h` (Private)


#### enum `BuildPatchServices::EConstructorChunkLocation`  
`enum EConstructorChunkLocation : uint8`  
_L31-40_
- L33 _public enumerator_ `Install`
- L34 _public enumerator_ `ChunkDb`
- L35 _public enumerator_ `Memory`
- L36 _public enumerator_ `DiskOverflow`
- L37 _public enumerator_ `Cloud`
- L38 _public enumerator_ `Retired`
- L39 _public enumerator_ `COUNT`

#### struct `BuildPatchServices::FFileConstructorConfig`  
`struct FFileConstructorConfig`  
_L60-109_
- desc: A struct containing the configuration values for a file constructor.
- L63 _public member_ `IBuildManifestSet* ManifestSet;` — The manifest set class for details on the installation files.
- L66 _public member_ `FString InstallDirectory;` — The location for the installation.
- L69 _public member_ `FString StagingDirectory;` — The location where new installation files will be constructed.
- L72 _public member_ `FString MetaDirectory;` — The location where temporary files for tracking can be stored.
- L75 _public member_ `TArray<FString> ConstructList;` — The list of files to be constructed, filename paths should match those contained in manifest.
- L78 _public member_ `EInstallMode InstallMode;` — The install mode used for this installation.
- L80 _public member_ `bool bUseSHA1StageFilenames;` — Whether we are needing to use SHA1 hash string value as filename for temp staging files.
- L83 _public member_ `bool bRejectSymlinks = false;` — If true, fail the installation if the manifest contains a symlink.
- L86 _public member_ `FString BackingStoreDirectory;` — The location where memory overflow will get written to.
- L89 _public member_ `const TMap<FString, FString>* PerFileSubdirectories = nullptr;` — Overrides for file locations.
- L91 _public member_ `IBuildInstallerSharedContext* SharedContext = nullptr;`
- L94 _public member_ `bool bInstallToMemory = false;` — See comments in installer config (FBuildInstallerConfiguration)
- L95 _public member_ `bool bConstructInMemory = false;`
- L96 _public member_ `bool bSkipInitialDiskSizeCheck = false;`
- L98 _public member_ `bool bDeleteChunkDBFilesAfterUse = false;`
- L100 _public member_ `static const bool bDefaultSpawnAdditionalIOThreads = true;`
- L101 _public member_ `static const int32 DefaultIOBatchSizeMB = 10;`
- L102 _public member_ `static const int32 DefaultIOBufferSizeMB = 64;`
- L104 _public member_ `TOptional<bool> SpawnAdditionalIOThreads;`
- L105 _public member_ `TOptional<int32> IOBatchSizeMB;`
- L106 _public member_ `TOptional<int32> IOBufferSizeMB;`
- L107 _public member_ `TOptional<bool> StallWhenFileSystemThrottled;`
- L108 _public member_ `TOptional<int32> DisableResumeBelowMB;`

#### class `BuildPatchServices::FBuildPatchFileConstructor`  
`class FBuildPatchFileConstructor : public IControllable`  
_L115-418_
- inherits: `IControllable`
- desc: FBuildPatchFileConstructor This class controls a thread that constructs files from a file list, given install details, and chunk availability notifications
- L130 _public prototype_ `FBuildPatchFileConstructor( FFileConstructorConfig Configuration, IFileSystem* FileSystem, IConstructorChunkDbChunkSource* ChunkDbChunkSource, IConstructorCloudChunkSource* CloudChunkSource, IConstructorInstallChunkSource* InstallChunkSource, IChunkReferenceTracker* ChunkReferenceTracker, IInstallerError* InstallerError, IInstallerAnalytics* InstallerAnalytics, IMessagePump* MessagePump, IFileConstructorStat* FileConstructorStat, TMap<FGuid, EConstructorChunkLocation>&& ChunkLocations);` — Constructor @param Configuration             The configuration for the constructor. @param FileSystem                The service used to open files. @param ChunkSource               Pointer to the chunk source. @param ChunkReferenceTracker     Pointer to the chunk reference tracker. @param InstallerError            Pointer to the installer error class for reporting fatal errors. @param InstallerAnalytics        Pointer to the installer analytics handler for reporting events. @param FileConstructorStat       Pointer to the stat class for receiving updates.
- L139 _public prototype_ `~FBuildPatchFileConstructor();` — Default Destructor, will delete the allocated Thread
- L141 _public prototype_ `void Run();`
- L144 _public prototype_ `virtual void SetPaused(bool bInIsPaused) override;` — IControllable interface begin.
- L145 _public prototype_ `virtual void Abort() override;`
- L147 _public function_ `virtual void Reset() override`
- L154 _public prototype_ `void WakeUpDispatch();`
- L164 _public prototype_ `uint64 GetRequiredDiskSpace();` — Get the disk space that was required to perform the installation. This can change over time and indicates the required space to _finish_ the installation from the current state. It is not initialized until after resume is processed and returns zero until that time. Note that since this and GetAvailableDiskSpace are separate accessors there's no guarantee that they match - e.g. if you call GetRequiredDiskSpace and then GetAvailableDiskSpace immediately afterwards, it's possible the Available Disk Space value is from a later call. This is highly unlikely due to how rare these updates are, but it's possible. Use these for UI purposes only.
- L171 _public prototype_ `uint64 GetAvailableDiskSpace();` — Get the disk space that was available when last updating RequiredDiskSpace. See notes with GetRequiredDiskSpace. It's possible for this to return 0 due to the underlying operating system being unable to report a value in cases of e.g. the drive being disconnected.
- L177 _public prototype_ `bool HasCorruptFiles() const;` — Gets flag indicating that at least one file is corrupt due to invalid hash sum. @return	true if at least one file is corrupt.
- L183 _public prototype_ `DECLARE_EVENT_OneParam(FBuildPatchFileConstructor, FOnBeforeDeleteFile, const FString& );` — Broadcasts with full filepath to file that the constructor is about to delete in order to free up space. @return	Reference to the event object.
- L184 _public prototype_ `FOnBeforeDeleteFile& OnBeforeDeleteFile();`
- L190 _public prototype_ `DECLARE_EVENT_OneParam(FBuildPatchFileConstructor, FOnFileIsStaged, const FString& );` — Broadcasts with the build relative path for a file that has finished being staged (including by a previous incomplete installation). @return	Reference to the event object.
- L191 _public prototype_ `FOnFileIsStaged& OnFileIsStaged();`
- L193 _public function_ `void GrabFilesInstalledToMemory(TMap<FString, TArray64<uint8>>& OutFilesInstalledToMemory)`
- L200 _private prototype_ `void SetChunkLocation(const FGuid& InGuid, EConstructorChunkLocation InNewLocation);`
- L206 _private prototype_ `void CountBytesProcessed(const int64& ByteCount);` — Count additional bytes processed, and set new install progress value @param ByteCount		Number of bytes to increment by
- L211 _private prototype_ `int64 GetRemainingBytes();` — @return the total bytes size of files not yet started construction
- L219 _private prototype_ `uint64 CalculateInProgressDiskSpaceRequired(const FFileManifest& InProgressFileManifest, uint64 InProgressFileSize);` — Calculates the minimum required disk space for the remaining work to be completed, based on a current file, and the list of files left in ConstructionStack. @param InProgressFileManifest	The manifest for the file currently being constructed. @param InProgressFileSize		The remaining size required for the file currently being constructed. @return the number of bytes required on disk to complete the installation.
- L226 _private prototype_ `uint64 CalculateDiskSpaceRequirementsWithDeleteDuringInstall(int64 InProgressFileSize);` — Calculates the amount of disk space we need to finish the install, needs to be called on file boundaries on the construct thread. @param InProgressFileSize		The remaining size required for the file currently being constructed. @return Number of bytes needed to complete the installation, or zero if space will be freed by removing chunks.
- L232 _private prototype_ `void ConstructFiles(FResumeData& ResumeData);` — Sequentially build the files required, potentially skipping already created files or resuming partial files.
- L236 _private member_ `const FFileConstructorConfig Configuration;` — The configuration for the constructor.
- L239 _private member_ `bool bIsRunning;` — A flag marking that we a running.
- L242 _private member_ `bool bIsInited;` — A flag marking that we initialized correctly.
- L245 _private member_ `bool bInitFailed;` — A flag marking that our init returned a failure (true means failed).
- L248 _private member_ `bool bIsDownloadStarted;` — A flag marking that we told the chunk cache to queue required downloads.
- L251 _private member_ `bool bInitialDiskSizeCheck;` — A flag marking that we have made the initial disk space check following resume logic complete.
- L254 _private member_ `bool bHasChunkDbSource = false;` — If true, the chunkdb source has chunks to provide
- L257 _private member_ `bool bStallWhenFileSystemThrottled = false;` — Our local resolved copy of the cvar with overrides applied.
- L260 _private member_ `FThreadSafeBool bIsPaused;` — A flag marking whether we should be paused.
- L263 _private member_ `FThreadSafeBool bShouldAbort;` — A flag marking whether we should abort operations and exit. Always call Abort() to set this.
- L267 _private member_ `std::atomic_int32_t NextIndexToConstruct = 0;` — Indexes in to ConstructionList and associated parallel arrays. This is the next file that will start construction when dependencies are met.
- L283 _private member_ `TArray<FFileToConstruct> ConstructionList;` — The in-oder list of files to construct. The array is parallel with Configuration.ConstructList.
- L286 _private member_ `IFileSystem* FileSystem;` — Pointer to the file system.
- L288 _private member_ `IConstructorChunkDbChunkSource* ChunkDbSource;` — can be null if not using.
- L289 _private member_ `IConstructorInstallChunkSource* InstallSource;`
- L290 _private member_ `IConstructorCloudChunkSource* CloudSource;`
- L293 _private member_ `TMap<FString, TArray64<uint8>> MemoryOutputFiles;` — Keyed off of the filename relative to the install directory.
- L299 _private member_ `FRWLock ChunkLocationsLock;` — We always want to know exactly where we think a chunk should be. If it's not there, we update this list to where it can be found (i.e. cloud) This is almost always read only after initialization, but in rare situations can be updated (chunk failures, file resume) and is multi threaded access.
- L300 _private member_ `TMap<FGuid, EConstructorChunkLocation> ChunkLocations;`
- L302 _private member_ `uint64 DownloadRequirement = 0;` — Track how much data we expect to have to download. This is protected by the ChunkLocationsLock since they are in sync.
- L305 _private member_ `IChunkReferenceTracker* ChunkReferenceTracker;` — Pointer to the chunk reference tracker.
- L307 _private member_ `std::atomic<int32> RemainingChunkCount = TNumericLimits<int32>::Max();`
- L310 _private member_ `IInstallerError* InstallerError;` — Pointer to the installer error class.
- L313 _private member_ `IInstallerAnalytics* InstallerAnalytics;` — Pointer to the installer analytics handler.
- L315 _private member_ `IMessagePump* MessagePump = nullptr;`
- L318 _private member_ `IFileConstructorStat* FileConstructorStat;` — Pointer to the stat class.
- L320 _private member_ `bool bAllowMultipleFilesInFlight = true;`
- L322 _private member_ `bool bShouldLogNextDependencyWait = true;`
- L325 _private member_ `uint32 ExpectedChunkSize = 0;` — The size we expect for chunks. This should be used for estimation purposes, not anything requiring hard limits.
- L328 _private member_ `int64 TotalJobSize;` — Total job size for tracking progress.
- L331 _private member_ `int64 ByteProcessed;` — Byte processed so far for tracking progress.
- L333 _private member_ `uint32 MaxWriteBatchSize = 0;`
- L334 _private member_ `uint32 IOBufferSize = 0;`
- L336 _private member_ `int32 WriteCount = 0;`
- L339 _private member_ `std::atomic_uint64_t RequiredDiskSpace;` — The amount of disk space requirement that was calculated when beginning the process. 0 if the install process was not started, or no additional space was needed.
- L342 _private member_ `std::atomic_uint64_t AvailableDiskSpace;` — The amount of disk space available when beginning the process. 0 if the install process was not started.
- L345 _private member_ `FOnBeforeDeleteFile BeforeDeleteFileEvent;` — Event executed before deleting an old installation file.
- L347 _private member_ `FOnFileIsStaged FileIsStagedEvent;` — Event executed when a file has now been staged or was previously staged.
- L350 _private member_ `TArray<FEvent*> ThreadWakeups;`
- L351 _private member_ `TArray<TArray<IConstructorChunkSource::FRequestProcessFn>> ThreadJobPostings;`
- L352 _private member_ `TArray<UE::FMutex> ThreadJobPostingLocks;`
- L353 _private member_ `TArray<FEvent*> ThreadCompleteEvents;`
- L354 _private member_ `TArray<IBuildInstallerThread*> Threads;`
- L356 _private prototype_ `void QueueGenericThreadTask(int32 ThreadIndex, TUniqueFunction<void(bool)>&& Task);`
- L357 _private prototype_ `void GenericThreadFn(int32 ThreadIndex);`
- L358 _private member_ `int8 ThreadAssignments[EConstructorChunkLocation::COUNT];`
- L359 _private member_ `int8 WriteThreadIndex = -1;`
- L361 _private member_ `TUniquePtr<FChunkBackingStore> BackingStore;`
- L364 _private member_ `FEvent* WakeUpDispatchThreadEvent = nullptr;` — Fire this to wake up the main thread to process completed tasks.
- L366 _private prototype_ `IConstructorChunkSource::FRequestProcessFn CreateWriteRequest(FArchive* File, FBatchState& Batch);`
- L369 _private member_ `TArray<int32> FileCompletionPositions;` — Where we are in the chunk consumption list after each file.
- L371 _private prototype_ `void StartReadBatch(FFileConstructionState& CurrentFile, FBatchState& Buffer);`
- L372 _private prototype_ `void CompleteReadBatch(const FFileManifest& FileManifest, FBatchState& Buffer);`
- L373 _private prototype_ `void RequestCompletedFn(const FGuid& Guid, bool bAborted, bool bFailedToRead, void* UserPtr);`
- L375 _private prototype_ `void ChunkHarvestCompletedFn(const FGuid& Guid, bool bAborted, bool bFailedToRead, void* UserPtr);`
- L377 _private prototype_ `void StartFile(FFileConstructionState& CurrentFile, const FResumeData& ResumeData);`
- L378 _private prototype_ `void ResumeFile(FFileConstructionState& FileToResume);`
- L379 _private prototype_ `void OpenFileToConstruct(FFileConstructionState& CurrentFile);`
- L380 _private prototype_ `bool HandleInitialDiskSizeCheck(const FFileManifest& CurrentFileManifest, int64 BytesInToCurrentFile);`
- L381 _private prototype_ `bool HarvestChunksForCompletedFile(const FString& InstallationDirectory, const FString& FilenameInManifest);`
- L383 _private prototype_ `void StartTruncateChunkDbForCompletedBatch(const FBatchState& Batch);` — Starts an asynchronous truncation task in the chunk reading thread, which guarantees single-threaded access to chunkdb.
- L385 _private prototype_ `void CompleteConstructedFile(FFileConstructionState& CurrentFile, FResumeData& ResumeData);`
- L388 _private prototype_ `EFileStage GetFileStage(const FFileConstructionState& CurrentFile, const FResumeData& ResumeData) const;` — Determine and return the file stage based on its existence and file size.
- L391 _private prototype_ `void InitFile(FFileConstructionState& CurrentFile, const FResumeData& ResumeData);` — Initialize and validate.
- L394 _private prototype_ `void RemoveUnnecessaryStagedFiles(const FString& StagingDirectory) const;` — Removes staged files that are no longer required for the current operation.
- L397 _private member_ `TSet<FString> CorruptFiles;` — Set of files considered corrupt due to an invalid hash sum.
- L411 _public function_ `FBackingStoreStats GetBackingStoreStats()` — This isn't safe to call during operations as values are changing on other threads.
- L417 _private member_ `FBackingStoreStats BackingStoreStats;`

#### struct `BuildPatchServices::FBuildPatchFileConstructor::FFileToConstruct`  
`struct FFileToConstruct`  
_L269-280_
- L271 _public member_ `const FFileManifest* FileManifest = nullptr;`
- L277 _public member_ `int32 LatestDependentInstallSource = -1;` — When using an install source with multiple files in flight, we can't start this file until all of the install sources it needs have been harvested. Since files are constructed in order, we only track the file that will be harvested last. If this file has no dependencies this is -1
- L279 _public member_ `FString StagingFilename;` — Name of the staging file. It may be obfuscated if bUseSHA1StageFilenames is true.

#### struct `BuildPatchServices::FBuildPatchFileConstructor::FBackingStoreStats`  
`struct FBackingStoreStats`  
_L400-408_
- L402 _public member_ `uint64 DiskPeakUsageBytes=0;`
- L403 _public member_ `uint64 MemoryPeakUsageBytes=0;`
- L404 _public member_ `uint64 MemoryLimitBytes=0;`
- L405 _public member_ `uint32 DiskLoadFailureCount=0;`
- L406 _public member_ `uint32 DiskLostChunkCount=0;`
- L407 _public member_ `uint32 DiskChunkLoadCount=0;`

#### class `BuildPatchServices::IFileConstructorStat`  
`class IFileConstructorStat`  
_L424-515_
- desc: This interface defines the statistics class required by the file constructor. It should be implemented in order to collect desired information which is being broadcast by the system.
- L427 _public prototype_ `virtual ~IFileConstructorStat() = default;`
- L432 _public prototype_ `virtual void OnResumeStarted() = 0;` — Called when the resume process begins.
- L437 _public prototype_ `virtual void OnResumeCompleted() = 0;` — Called when the resume process completes.
- L443 _public prototype_ `virtual void OnChunkGet(const FGuid& ChunkId) = 0;` — Called for each Get made to the chunk source. @param ChunkId       The id for the chunk required.
- L450 _public prototype_ `virtual void OnFileStarted(const FString& Filename, int64 FileSize) = 0;` — Called when a file construction has started. @param Filename      The filename of the file. @param FileSize      The size of the file being constructed.
- L457 _public prototype_ `virtual void OnFileProgress(const FString& Filename, int64 TotalBytes) = 0;` — Called during a file construction with the current progress. @param Filename      The filename of the file. @param TotalBytes    The number of bytes processed so far.
- L464 _public prototype_ `virtual void OnFileCompleted(const FString& Filename, bool bSuccess) = 0;` — Called when a file construction has completed. @param Filename      The filename of the file. @param bSuccess      True if the file construction succeeded.
- L469 _public prototype_ `virtual void OnConstructionCompleted() = 0;` — Called when the construction process completes.
- L475 _public prototype_ `virtual void OnProcessedDataUpdated(int64 TotalBytes) = 0;` — Called to update the total amount of bytes which have been constructed. @param TotalBytes    The number of bytes constructed so far.
- L481 _public prototype_ `virtual void OnTotalRequiredUpdated(int64 TotalBytes) = 0;` — Called to update the total number of bytes to be constructed. @param TotalBytes    The total number of bytes to be constructed.
- L486 _public prototype_ `virtual void OnBeforeAdminister() = 0;` — Called when we are beginning a file administration, such as open, close, seek.
- L492 _public prototype_ `virtual void OnAfterAdminister(const ISpeedRecorder::FRecord& Record) = 0;` — Called upon completing an admin operation, with activity recording. @param Record        The activity record.
- L497 _public prototype_ `virtual void OnBeforeRead() = 0;` — Called when we are beginning a read operation.
- L503 _public prototype_ `virtual void OnAfterRead(const ISpeedRecorder::FRecord& Record) = 0;` — Called upon completing a read operation, with activity recording. @param Record        The activity record.
- L508 _public prototype_ `virtual void OnBeforeWrite() = 0;` — Called when we are beginning a write operation.
- L514 _public prototype_ `virtual void OnAfterWrite(const ISpeedRecorder::FRecord& Record) = 0;` — Called upon completing a write operation, with activity recording. @param Record        The activity record.

#### struct `FileConstructorHelpers::FDiskSpaceInfo`  
`struct FDiskSpaceInfo`  
_L524-528_
- L526 _public member_ `uint64 AvailableDiskSpace = 0;`
- L527 _public member_ `bool bHaveSufficientFreeSpace = false;`

#### Free symbols / members of external scopes

- L29 _namespace_ `namespace BuildPatchServices`
- L183 _delegate_ `DECLARE_EVENT_OneParam(FBuildPatchFileConstructor, FOnBeforeDeleteFile, const FString& );` — Broadcasts with full filepath to file that the constructor is about to delete in order to free up space. @return	Reference to the event object.
- L190 _delegate_ `DECLARE_EVENT_OneParam(FBuildPatchFileConstructor, FOnFileIsStaged, const FString& );` — Broadcasts with the build relative path for a file that has finished being staged (including by a previous incomplete installation). @return	Reference to the event object.
- L521 _namespace_ `namespace FileConstructorHelpers`
- L523 _prototype_ `uint64 CalculateRequiredDiskSpace(const FBuildPatchAppManifestPtr& CurrentManifest, const FBuildPatchAppManifestRef& BuildManifest, const BuildPatchServices::EInstallMode& InstallMode, const TSet<FString>& InstallTags);` (scope `FileConstructorHelpers`)
- L529 _prototype_ `TOptional<FDiskSpaceInfo> GetRemainingDiskSpace(const FString& InstallDirectory, uint64 RemainingBytesRequired);` (scope `FileConstructorHelpers`)

### `Source/Runtime/Online/BuildPatchServices/Private/BuildPatchGeneration.h` (Private)


#### class `BuildPatchServices::FDirectoryChunkerFactory`  
`class FDirectoryChunkerFactory`  
_L11-15_
- L14 _public prototype_ `static IDirectoryChunker* Create(FDirectoryChunkerConfiguration Configuration);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/BuildPatchHash.h` (Private)


#### struct `FRollingHashConst`  
`struct FRollingHashConst`  
_L22-31_
- desc: A static struct containing 64bit polynomial constant and hash table lookup for use with FRollingHash.
- L25 _public member_ `static uint64 HashTable[ 256 ];` — The lookup hash table
- L30 _public prototype_ `static void Init();` — Builds the hash table for use when hashing. Must be called before using FRollingHash.

#### class `FRollingHash`  
`class FRollingHash`  
_L36-112_
- desc: A class that performs a rolling hash
- L39 _private typedef_ `typedef TRingBuffer< uint8 > HashRingBuffer;` — A typedef for our data ring buffer
- L45 _public prototype_ `FRollingHash(uint32 WindowSize);` — Constructor
- L51 _public prototype_ `void ConsumeByte( const uint8& NewByte );` — Pass this function the initial data set to start the Rolling Hash with. @param NewByte		The byte to add to the hash state
- L58 _public prototype_ `void ConsumeBytes( const uint8* NewBytes, const uint32& NumBytes );` — Helper to consume from a byte array @param NewBytes		The byte array @param NumBytes		The number of bytes to consume
- L64 _public prototype_ `void RollForward( const uint8& NewByte );` — Rolls the window by one byte forwards. @param NewByte		The byte that will be added to the front of the window
- L69 _public prototype_ `void Clear();` — Clears all data ready for a new entire data set
- L75 _public prototype_ `const uint64 GetWindowHash() const;` — Get the HashState for the current window @return		The hash state
- L81 _public prototype_ `const HashRingBuffer& GetWindowData() const;` — Get the Ring Buffer for the current window @return		The ring buffer
- L87 _public prototype_ `const uint32 GetNumDataNeeded() const;` — Get how many DataValueType values we still need to consume until our window is full @return		The number of DataValueType we still need
- L92 _public prototype_ `const uint32 GetWindowSize() const;` — @return the size of our window
- L100 _public prototype_ `static uint64 GetHashForDataSet( const uint8* DataSet, uint32 WindowSize );` — Static function to simply return the hash for a given data range. @param DataSet     The buffer to the data. @param WindowSize  The buffer of length. @return The hash state for the provided data
- L103 _private prototype_ `FRollingHash();`
- L105 _private member_ `const uint32 WindowSize = 0;` — The data size that we roll over.
- L107 _private member_ `uint64 HashState = 0;` — The current hash value
- L109 _private member_ `uint32 NumBytesConsumed = 0;` — The number of bytes we have consumed so far, used in hash function and to check validity of calls
- L111 _private member_ `HashRingBuffer WindowData = 0;` — Store the data to make access and rolling easier

#### Free symbols / members of external scopes

- L17 _macro_ `#define ROTLEFT_64B( Value, Shifts ) Value = ( ( ( Value ) << ( ( Shifts ) % 64 ) ) | ( ( Value ) >> ( ( 64 - ( ( Shifts ) % 64 ) ) % 64 ) ) )` — A macro for barrel rolling a 64 bit value n times to the left. @param Value		The value to shift @param Shifts	The number of times to shift
- L117 _function_ `static bool CheckRollingHashAlgorithm()` — A static function to perform sanity checks on the rolling hash class.

### `Source/Runtime/Online/BuildPatchServices/Private/BuildPatchInstaller.h` (Private)


#### class `BuildPatchServices::FBuildPatchInstaller`  
`class FBuildPatchInstaller : public IBuildInstaller , public FRunnable , public TSharedFromThis<FBuildPatchInstaller, ESPMode::ThreadSafe>`  
_L62-514_
- inherits: `IBuildInstaller,FRunnable,TSharedFromThis<FBuildPatchInstaller,ESPMode::ThreadSafe>`
- desc: FBuildPatchInstaller This class controls a thread that wraps the code to install/patch an app from manifests.
- L69 _private member_ `const FBuildInstallerConfiguration Configuration;` — The installer configuration.
- L72 _private member_ `const FGuid SessionId;` — Simple unique installer guid to help logging functions have context.
- L75 _private member_ `const FBuildPatchInstallerDelegate StartDelegate;` — The delegates that we will be calling when started.
- L78 _private member_ `const FBuildPatchInstallerDelegate CompleteDelegate;` — The delegates that we will be calling on complete.
- L82 _private member_ `TArray<FBuildPatchInstallerAction> InstallerActions;` — The Configuration.InstallerActions array converted into private class type. Cannot be const due to Delta Optimisation modifying the manifests.
- L85 _private member_ `const FString DataStagingDir;` — The directory created in staging, to store local patch data.
- L88 _private member_ `const FString InstallStagingDir;` — The directory created in staging to construct install files to.
- L91 _private member_ `const FString MetaStagingDir;` — The directory created in staging to store any required meta, such as resume info.
- L94 _private member_ `const FString PreviousMoveMarker;` — The filename used to mark a previous install that did not complete but moved staged files into the install directory.
- L97 _private member_ `const FString HddSpaceReservationFile;` — The filename used to reserve diskspace when preloading.
- L100 _private member_ `const TMultiMap<FString, FBuildPatchAppManifestRef> InstallationInfo;` — Map of registered installations.
- L103 _private member_ `mutable FCriticalSection ThreadLock;` — A critical section to protect variables.
- L106 _private member_ `IBuildInstallerThread* Thread;` — Hold a pointer to my thread for easier deleting.
- L109 _private member_ `std::atomic<bool> bSuccess;` — A flag storing whether the process was a success.
- L112 _private member_ `std::atomic<bool> bIsRunning;` — A flag marking that we a running.
- L115 _private member_ `std::atomic<bool> bIsInited;` — A flag marking that we initialized correctly.
- L118 _private member_ `std::atomic<bool> bFirstInstallIteration;` — A flag that stores whether we are on the first install iteration.
- L121 _private member_ `std::atomic<bool> bLastInstallIteration = false;` — A flag that indicates whether we are on the last install iteration.
- L124 _private member_ `std::atomic<int64> PreviousTotalDownloadRequired;` — Tracks required download data between install retries.
- L127 _private member_ `std::atomic<bool> bAreResultsEncrypted;` — Tracks if any results of the file construction are encrypted. If they are, we'll be staging only, and no point verifying.
- L130 _private member_ `FBuildInstallStats BuildStats;` — Keep track of build stats.
- L133 _private member_ `FBuildPatchProgress BuildProgress;` — Keep track of install progress.
- L136 _private member_ `bool bIsPaused;` — Whether we are currently paused.
- L139 _private member_ `bool bShouldAbort;` — Whether we are needing to abort.
- L142 _private member_ `TArray<FString> FilesInstalled;` — Holds a list of files that have been placed into the install directory.
- L145 _private member_ `TSet<FString> TaggedFiles;` — Holds the files which are all required.
- L148 _private member_ `TSet<FString> OutdatedFiles;` — Holds the files which are outdated.
- L151 _private member_ `TSet<FString> FilesToConstruct;` — The files to be constructed in the current install attempt.
- L154 _private member_ `TSet<FString> OldFilesRemovedBySystem;` — The files that were removed during installation due to destructive patch behavior.
- L157 _private member_ `TMap<FString, TArray64<uint8>> FilesInstalledToMemory;` — With bInstallToMemory, files end up here after construction.
- L161 _private member_ `TMap<FString, FString> OldPerFileSubdirectories;` — Keyed off the file manifest filename, value is appended to the installation directory. Where to find the files in the installation when patching.
- L163 _private member_ `TMap<FString, FString> NewPerFileSubdirectories;` — Where to put the files in the new installation.
- L166 _private member_ `FString LocalMachineConfigFile;` — The file which contains per machine configuration information.
- L169 _private member_ `TSharedPtr<IHttpManager> HttpManager;` — HTTP manager used to make requests for download data.
- L172 _private member_ `TSharedPtr<IFileSystem> FileSystem;` — File systems for classes requiring disk access.
- L175 _private member_ `TUniquePtr<ICrypto> Crypto;` — File systems for classes requiring crypto.
- L178 _private member_ `TUniquePtr<IPlatform> Platform;` — Platform abstraction.
- L181 _private member_ `TUniquePtr<IInstallerError> InstallerError;` — Installer error tracking system.
- L184 _private member_ `TSharedPtr<IAnalyticsProvider> Analytics;` — The analytics provider interface.
- L187 _private member_ `TSharedPtr<IInstallerAnalytics> InstallerAnalytics;` — Installer analytics handler.
- L190 _private member_ `TUniquePtr<IInstallActionStatistics> InstallActionStatistics;` — Installer statistics tracking.
- L191 _private member_ `TUniquePtr<IFileOperationTracker> FileOperationTracker;`
- L192 _private member_ `TSharedPtr<ISpeedRecorder> DownloadSpeedRecorder;`
- L193 _private member_ `TSharedPtr<ISpeedRecorder> DiskReadSpeedRecorder;`
- L194 _private member_ `TSharedPtr<ISpeedRecorder> DiskWriteSpeedRecorder;`
- L195 _private member_ `TSharedPtr<IChunkDataSizeProvider> ChunkDataSizeProvider;`
- L196 _private member_ `TSharedPtr<IDownloadServiceStatistics> DownloadServiceStatistics;`
- L197 _private member_ `TUniquePtr<IChunkDbChunkSourceStatistics> ChunkDbChunkSourceStatistics;`
- L198 _private member_ `TUniquePtr<IInstallChunkSourceStatistics> InstallChunkSourceStatistics;`
- L199 _private member_ `TUniquePtr<ICloudChunkSourceStatistics> CloudChunkSourceStatistics;`
- L200 _private member_ `TUniquePtr<IFileConstructorStatistics> FileConstructorStatistics;`
- L201 _private member_ `TUniquePtr<IVerifierStatistics> VerifierStatistics;`
- L204 _private member_ `TUniquePtr<IDownloadService> DownloadService;` — Download service.
- L207 _private member_ `TUniquePtr<IMessagePump> MessagePump;` — The message pump controller.
- L210 _private member_ `TUniquePtr<IBuildManifestSet> ManifestSet;` — The interface for manifest data aggregation.
- L213 _private member_ `TUniquePtr<IVerifier> Verifier;` — The interface for verification of files built.
- L216 _private member_ `TArray<IControllable*> Controllables;` — List of controllable classes that have been constructed.
- L223 _private member_ `UE::FMutex DownloadRateLimitLock;` — Download rate limit in Bytes per second, 0 is unlimited. Since we can get a change on any thread and we may need to pipe it to the file constructor, rather than poll the rate we register a function that gets called. The function must be set within the mutex and will be called holding the mutex.
- L224 _private member_ `uint64 DownloadRateLimitBps;`
- L225 _private member_ `TUniqueFunction<void(uint64 NewRate)> DownloadRateUpdatedFn;`
- L228 _private member_ `TArray<FMessageHandler*> MessageHandlers;` — List of message handlers that have been registered.
- L231 _private member_ `FProcessTimer InitializeTimer;` — Stage timers for build stats.
- L232 _private member_ `FProcessTimer ConstructTimer;`
- L233 _private member_ `FProcessTimer UninstallActionTimer;`
- L234 _private member_ `FProcessTimer MoveFromStageTimer;`
- L235 _private member_ `FProcessTimer FileAttributesTimer;`
- L236 _private member_ `FProcessTimer VerifyTimer;`
- L237 _private member_ `FProcessTimer CleanUpTimer;`
- L238 _private member_ `FProcessTimer PrereqTimer;`
- L239 _private member_ `FProcessTimer ProcessPausedTimer;`
- L240 _private member_ `FProcessTimer ProcessActiveTimer;`
- L241 _private member_ `FProcessTimer ProcessExecuteTimer;`
- L244 _private member_ `TMap<BuildPatchServices::EVerifyError, int32> CachedVerifyErrorCounts;` — Caches verification errors encountered each run.
- L256 _public prototype_ `FBuildPatchInstaller(FBuildInstallerConfiguration Configuration, TMultiMap<FString, FBuildPatchAppManifestRef> InstallationInfo, const FString& LocalMachineConfigFile, TSharedPtr<IAnalyticsProvider> Analytics, FBuildPatchInstallerDelegate StartDelegate, FBuildPatchInstallerDelegate CompleteDelegate);` — Constructor takes configuration and dependencies. @param Configuration             The installer configuration structure. @param InstallationInfo          Map of locally installed apps for use as chunk sources. @param LocalMachineConfigFile    Filename for the local machine's config. This is used for per-machine configuration rather than shipped or user config. @param Analytics                 Optionally valid ptr to an analytics provider for sending events. @param StartDelegate             Delegate for when the process has started. @param CompleteDelegate          Delegate for when the process has completed.
- L261 _public prototype_ `~FBuildPatchInstaller();` — Default Destructor, will delete the allocated Thread.
- L264 _public prototype_ `uint32 Run() override;` — FRunnable interface begin.
- L268 _public prototype_ `virtual bool StartInstallation() override;` — IBuildInstaller interface begin.
- L269 _public prototype_ `virtual bool IsComplete() const override;`
- L270 _public prototype_ `virtual bool IsCanceled() const override;`
- L271 _public prototype_ `virtual bool IsPaused() const override;`
- L272 _public prototype_ `virtual bool IsResumable() const override;`
- L273 _public prototype_ `virtual bool IsUpdate() const override;`
- L274 _public prototype_ `virtual bool IsRepair() const override;`
- L275 _public prototype_ `virtual bool IsVerifyOnly() const override;`
- L276 _public prototype_ `virtual bool IsUninstall() const override;`
- L277 _public prototype_ `virtual bool CompletedSuccessfully() const override;`
- L278 _public prototype_ `virtual bool HasError() const override;`
- L279 _public prototype_ `virtual EBuildPatchInstallError GetErrorType() const override;`
- L280 _public prototype_ `virtual FString GetErrorCode() const override;`
- L282 _public prototype_ `virtual FText GetPercentageText() const override;` — @todo this is deprecated and shouldn't be used anymore [6/4/2014 justin.sargent]
- L284 _public prototype_ `virtual FText GetDownloadSpeedText() const override;` — @todo this is deprecated and shouldn't be used anymore [6/4/2014 justin.sargent]
- L285 _public prototype_ `virtual double GetDownloadSpeed() const override;`
- L286 _public prototype_ `virtual int64 GetTotalDownloadRequired() const override;`
- L287 _public prototype_ `virtual int64 GetTotalDownloaded() const override;`
- L288 _public prototype_ `virtual EBuildPatchState GetState() const override;`
- L289 _public prototype_ `virtual FText GetStatusText() const override;`
- L290 _public prototype_ `virtual float GetUpdateProgress() const override;`
- L291 _public prototype_ `virtual FBuildInstallStats GetBuildStatistics() const override;`
- L292 _public prototype_ `virtual EBuildPatchDownloadHealth GetDownloadHealth() const override;`
- L293 _public prototype_ `virtual FText GetErrorText() const override;`
- L294 _public prototype_ `virtual void CancelInstall() override;`
- L295 _public prototype_ `virtual bool TogglePauseInstall() override;`
- L296 _public prototype_ `virtual void RegisterMessageHandler(FMessageHandler* MessageHandler) override;`
- L297 _public prototype_ `virtual void UnregisterMessageHandler(FMessageHandler* MessageHandler) override;`
- L298 _public prototype_ `virtual const FBuildInstallerConfiguration& GetConfiguration() const override;`
- L299 _public prototype_ `virtual void SetDownloadBytesPerSecondLimit(uint64 InDownloadRateLimitBps) override;`
- L300 _public prototype_ `virtual uint64 GetDownloadBytesPerSecondLimit() const override;`
- L302 _public prototype_ `virtual void GetDebugText(TArray<FString>& Output) override;`
- L304 _public prototype_ `virtual TMap<FString, TArray64<uint8>>& GetFilesInstalledToMemory() override;`
- L305 _public prototype_ `virtual void SetPerFileSubdirectories(TMap<FString, FString>&& InOldPerFileSubdirectories, TMap<FString, FString>&& InNewPerFileSubdirectories) override;`
- L311 _public prototype_ `bool Tick();` — Tick function called from the module to give us game thread time.
- L316 _public prototype_ `void PreExit();` — Called by the module during shutdown.
- L321 _public prototype_ `const IFileOperationTracker* GetFileOperationTracker() const;` — @return the file operation tracker for granular data progress states.
- L326 _public prototype_ `const ISpeedRecorder* GetDownloadSpeedRecorder() const;` — @return the speed recorder for download speed.
- L331 _public prototype_ `const ISpeedRecorder* GetDiskReadSpeedRecorder() const;` — @return the speed recorder for disk read speed.
- L336 _public prototype_ `const ISpeedRecorder* GetDiskWriteSpeedRecorder() const;` — @return the speed recorder for disk write speed.
- L341 _public prototype_ `const IDownloadServiceStatistics* GetDownloadServiceStatistics() const;` — @return the download service statistics interface.
- L346 _public prototype_ `const IInstallChunkSourceStatistics* GetInstallChunkSourceStatistics() const;` — @return the install chunk source statistics interface.
- L351 _public prototype_ `const ICloudChunkSourceStatistics* GetCloudChunkSourceStatistics() const;` — @return the cloud chunk source statistics interface.
- L356 _public prototype_ `const IFileConstructorStatistics* GetFileConstructorStatistics() const;` — @return the file constructor statistics interface.
- L358 _public prototype_ `const IChunkDbChunkSourceStatistics* GetChunkDbChunkSourceStatistics() const;`
- L363 _public prototype_ `const IVerifierStatistics* GetVerifierStatistics() const;` — @return the verifier statistics interface.
- L372 _private prototype_ `bool Initialize();` — Initialize the installer. @return Whether initialization was successful.
- L378 _private prototype_ `void ExecuteCompleteDelegate();` — Executes the on complete delegate. This should only be called when completed, and is separated out to allow control to make this call on the main thread.
- L383 _private prototype_ `void PumpMessages();` — Pumps all queued messages to registered handlers.
- L392 _private prototype_ `bool CheckForExternallyInstalledFiles(const TSet<FString>& FilesToCheck);` — Checks the installation directory for any already existing files of the correct size, with may account for manual installation. Should be used for new installation detecting existing files. NB: Not useful for patches, where we'd expect existing files anyway. @param FilesToCheck      The list of files that we would expect to not exist yet. @return    Returns true if there were potentially already installed files.
- L399 _private prototype_ `bool RunInstallation(TArray<FString>& CorruptFiles);` — Runs the installation process. @param   CorruptFiles    A list of files that were corrupt, to only install those. @return  Returns true if there were no errors blocking installation.
- L405 _private prototype_ `bool RunPreload();` — Runs the preload download process. @return  Returns true if there were no errors blocking the preload.
- L410 _private prototype_ `bool RunPrerequisites();` — Runs the prerequisite installation process.
- L415 _private prototype_ `void SetFinalInstallStats();` — Sets installation stats from various systems.
- L421 _private prototype_ `bool RunCustomUninstallAction();` — Runs the custom uninstall action if specified. @return    Returns true if there were no errors.
- L427 _private prototype_ `bool RunBackupAndMove();` — Runs the backup process for locally changed files, and then moves new files into installation directory. @return    Returns true if there were no errors.
- L433 _private prototype_ `bool RunFileAttributes();` — Runs the process to setup all file attributes required. @return    Returns true if there were no errors.
- L440 _private prototype_ `bool RunVerification(TArray<FString>& CorruptFiles);` — Runs the verification process. @param CorruptFiles  OUT     Receives the list of files that failed verification. @return    Returns true if there were no corrupt files.
- L449 _private prototype_ `bool BackupFileIfNecessary(const FString& Filename, const TMap<FString, FString>& PerFileSubdirectories, bool bDiscoveredByVerification = false);` — Checks a particular file in the install directory to see if it needs backing up, and does so if necessary. @param Filename                      The filename to check, which should match a filename in a manifest. @param PerFileSubdirectories         Per-file subdirectory mapping to use when resolving paths @param bDiscoveredByVerification     Optional, whether the file was detected changed already by verification stage. Default: false. @return    Returns true if there were no errors.
- L455 _private prototype_ `void CleanupEmptyDirectories(const FString& RootDirectory);` — Delete empty directories from an installation. @param RootDirectory     Root Directory for search.
- L464 _private prototype_ `void FilterToExistingFiles(const FString& RootDirectory, const TMap<FString, FString>& PerFileSubdirectories, TSet<FString>& Files, bool bResolveInstallationFileName);` — Remove from the set any files that do not exist. @param RootDirectory             Root Directory for search. @param PerFileSubdirectories     Per-file subdirectory mapping to use when resolving paths @param Files                     Set of files to filter. @param bResolveInstallationFileName If true, instead of appending the RootDirectory / FilesName, call ResolveInstallationFileName on the file.
- L472 _private prototype_ `bool RemoveFileWithRetries(const FString& FullFilename, uint32& ErrorCode);` — Attempt to remove a file, using configured retries. @param FullFilename      The full filename to remove. @param ErrorCode     OUT The error code if failed. @return true if the file was removed.
- L482 _private prototype_ `bool RelocateFileWithRetries(const FString& ToFullFilename, const FString& FromFullFilename, uint32& RenameErrorCode, uint32& CopyErrorCode);` — Attempt to relocate a file by move or copy, using configured retries @param ToFullFilename          The full filename of the destination. @param FromFullFilename        The full filename of the source. @param RenameErrorCode     OUT The move/rename error code if failed. @param CopyErrorCode       OUT The copy error code if failed. @return true if the file was relocated.
- L491 _private prototype_ `bool CopyFileWithRetries(const FString& ToFullFilename, const FString& FromFullFilename, uint32& CopyErrorCode);` — Attempt to copy a file using configured retries @param ToFullFilename          The full filename of the destination. @param FromFullFilename        The full filename of the source. @param CopyErrorCode       OUT The copy error code if failed. @return true if the file was copied.
- L496 _private prototype_ `FCloudSourceConfig BuildCloudSourceConfig();` — Builds the cloud source configuration struct.
- L501 _private prototype_ `FDownloadConnectionCountConfig BuildConnectionCountConfig();` — Builds the cloud source configuration struct.
- L508 _private prototype_ `FString GetSHA1Filename(const FFileManifest& FileManifest);` — Get the filename as SHA string value. @param FileManifest    The FFileManifest for the file. @return filename as SHA string value.
- L513 _private prototype_ `void CleanupThread();` — Destroys the internal worker thread

#### Free symbols / members of external scopes

- L32 _namespace_ `namespace BuildPatchServices`
- L519 _typedef_ `typedef TSharedPtr< BuildPatchServices::FBuildPatchInstaller, ESPMode::ThreadSafe > FBuildPatchInstallerPtr;`
- L520 _typedef_ `typedef TSharedRef< BuildPatchServices::FBuildPatchInstaller, ESPMode::ThreadSafe > FBuildPatchInstallerRef;`
- L521 _typedef_ `typedef TWeakPtr< BuildPatchServices::FBuildPatchInstaller, ESPMode::ThreadSafe > FBuildPatchInstallerWeakPtr;`

### `Source/Runtime/Online/BuildPatchServices/Private/BuildPatchManifest.h` (Private)


#### class `FBuildPatchCustomField`  
`class FBuildPatchCustomField : public IManifestField`  
_L23-47_
- inherits: `IManifestField`
- desc: Declare the FBuildPatchCustomField object class, which is the implementation of the object we return to clients of the module
- L30 _public prototype_ `FBuildPatchCustomField(const FString& Value);` — Constructor taking the custom value
- L33 _public prototype_ `virtual FString AsString() const override;` — START IBuildManifest Interface
- L34 _public prototype_ `virtual double AsDouble() const override;`
- L35 _public prototype_ `virtual int64 AsInteger() const override;`
- L42 _private function_ `FBuildPatchCustomField()` — Hide the default constructor
- L46 _private member_ `FString CustomValue;` — Holds the underlying value

#### class `FBuildPatchAppManifest`  
`class FBuildPatchAppManifest : public IBuildManifest`  
_L63-419_
- inherits: `IBuildManifest`
- desc: Declare the FBuildPatchAppManifest object class. This holds the UObject data, and the implemented build manifest functionality
- L83 _public prototype_ `FBuildPatchAppManifest();` — Default constructor
- L88 _public prototype_ `FBuildPatchAppManifest(const uint32& InAppID, const FString& AppName);` — Basic details constructor
- L93 _public prototype_ `FBuildPatchAppManifest(const FBuildPatchAppManifest& Other);` — Copy constructor
- L98 _public prototype_ `~FBuildPatchAppManifest();` — Default destructor
- L101 _public prototype_ `virtual BuildPatchServices::EFeatureLevel GetFeatureLevel() const override;` — START IBuildManifest Interface
- L102 _public prototype_ `virtual uint32 GetAppID() const override;`
- L103 _public prototype_ `virtual const FString& GetAppName() const override;`
- L104 _public prototype_ `virtual const FString& GetVersionString() const override;`
- L105 _public prototype_ `virtual const FString& GetUniqueBuildId() const override;`
- L106 _public prototype_ `virtual const FGuid& GetEncryptionSecretId(bool* bOutIsManifestEncrypted = nullptr) const override;`
- L107 _public prototype_ `virtual bool IsManifestEncrypted() const override;`
- L108 _public prototype_ `virtual bool IsOriginallyFullyEncrypted() const override;`
- L109 _public prototype_ `virtual TSet<FGuid> GetNecessaryEncryptionSecretIds() const override;`
- L110 _public prototype_ `virtual const FString& GetLaunchExe() const override;`
- L111 _public prototype_ `virtual const FString& GetLaunchCommand() const override;`
- L112 _public prototype_ `virtual const TSet<FString>& GetPrereqIds() const override;`
- L113 _public prototype_ `virtual const FString& GetPrereqName() const override;`
- L114 _public prototype_ `virtual const FString& GetPrereqPath() const override;`
- L115 _public prototype_ `virtual const FString& GetPrereqArgs() const override;`
- L116 _public prototype_ `virtual const FString& GetUninstallActionPath() const override;`
- L117 _public prototype_ `virtual const FString& GetUninstallActionArgs() const override;`
- L118 _public prototype_ `virtual int64 GetDownloadSize() const override;`
- L119 _public prototype_ `virtual int64 GetDownloadSize(const TSet<FString>& Tags) const override;`
- L120 _public prototype_ `virtual int64 GetDownloadSize(const TSet<const BuildPatchServices::FFileManifest*>& TaggedFiles) const;`
- L121 _public prototype_ `virtual int64 GetDeltaDownloadSize(const TSet<FString>& Tags, const IBuildManifestRef& PreviousVersion) const override;`
- L122 _public prototype_ `virtual int64 GetDeltaDownloadSize(const TSet<FString>& Tags, const IBuildManifestRef& PreviousVersion, const TSet<FString>& PreviousTags) const override;`
- L123 _public prototype_ `virtual int64 GetDeltaDownloadSize(const TSet<const BuildPatchServices::FFileManifest*>& InTaggedManifests, const IBuildManifestRef& InPreviousVersion, const TSet<FString>& InFilesInstalled, const TSet<FGuid>& InChunksInstalled) const;`
- L124 _public prototype_ `virtual int64 GetDeltaDownloadSize(const TSet<FString>& AllTaggedFiles, const IBuildManifestRef& InPreviousVersion, const TSet<FString>& InFilesInstalled, const TSet<FGuid>& InChunksInstalled) const;`
- L125 _public prototype_ `virtual int64 GetBuildSize() const override;`
- L126 _public prototype_ `virtual int64 GetBuildSize(const TSet<FString>& Tags) const override;`
- L127 _public prototype_ `virtual int64 GetBuildSize(const TSet<const BuildPatchServices::FFileManifest*>& TaggedFiles) const;`
- L128 _public prototype_ `virtual TArray<FString> GetBuildFileList() const override;`
- L129 _public prototype_ `virtual TArray<FStringView> GetBuildFileListView() const override;`
- L130 _public prototype_ `virtual TArray<FString> GetBuildFileList(const TSet<FString>& Tags) const override;`
- L131 _public prototype_ `virtual TArray<FStringView> GetBuildFileListView(const TSet<FString>& Tags) const override;`
- L132 _public prototype_ `virtual int64 GetFileSize(FStringView Filename) const override;`
- L133 _public prototype_ `virtual int64 GetFileSize(const TArray<FString>& Filenames) const override;`
- L134 _public prototype_ `virtual int64 GetFileSize(const TSet <FString>& Filenames) const override;`
- L135 _public prototype_ `virtual EFileMetaFlags GetFileMetaFlags(const FString& Filename) const override;`
- L136 _public prototype_ `virtual const FMD5Hash* GetFileMD5Hash(const FString& Filename) const override;`
- L137 _public prototype_ `virtual const FSHAHash* GetFileSHA1Hash(const FString& Filename) const override;`
- L138 _public prototype_ `virtual const FSHA256Signature* GetFileSHA256Hash(const FString& Filename) const override;`
- L139 _public prototype_ `virtual const FString* GetFileMIMEType(const FString& Filename) const override;`
- L140 _public prototype_ `virtual TSet<FString> GetFileTagList() const override;`
- L141 _public prototype_ `virtual void GetFileTagList(TSet<FString>& Tags) const override;`
- L142 _public prototype_ `virtual void GetOutdatedFiles(const IBuildManifestRef& OldManifest, TSet<FString>& OutdatedFiles) const override;`
- L143 _public prototype_ `virtual void GetRemovableFiles(const IBuildManifestRef& OldManifest, TArray<FString>& RemovableFiles) const override;`
- L144 _public prototype_ `virtual void GetRemovableFiles(const TCHAR* InstallPath, TArray<FString>& RemovableFiles) const override;`
- L145 _public prototype_ `virtual void GetChunksRequiredForFiles(const TSet<FString>& Filenames, TSet<FGuid>& RequiredChunks) const override;`
- L146 _public prototype_ `virtual int64 GetDataSize(const FGuid& DataGuid) const override;`
- L147 _public prototype_ `virtual bool GetChunkShaHash(const FGuid& ChunkGuid, FSHAHash& OutHash) const override;`
- L148 _public prototype_ `virtual bool GetChunkEncryptionSecretId(const FGuid& ChunkGuid, FGuid& OutEncryptionSecretId) const override;`
- L149 _public prototype_ `virtual bool NeedsResaving() const override;`
- L150 _public prototype_ `virtual void CopyCustomFields(const IBuildManifestRef& Other, bool bClobber) override;`
- L151 _public prototype_ `virtual TArray<FString> GetCustomFieldNames() const override;`
- L152 _public prototype_ `virtual const IManifestFieldPtr GetCustomField(const FString& FieldName) const override;`
- L153 _public prototype_ `virtual const IManifestFieldPtr SetCustomField(const FString& FieldName, const FString& Value) override;`
- L154 _public prototype_ `virtual const IManifestFieldPtr SetCustomField(const FString& FieldName, const double& Value) override;`
- L155 _public prototype_ `virtual const IManifestFieldPtr SetCustomField(const FString& FieldName, const int64& Value) override;`
- L156 _public prototype_ `virtual void RemoveCustomField(const FString& FieldName) override;`
- L157 _public prototype_ `virtual IBuildManifestRef Duplicate() const override;`
- L163 _public prototype_ `virtual const FString& GetBuildId() const;` — @return The unique build id of this manifest.
- L170 _public prototype_ `virtual bool LoadFromFile(const FString& Filename);` — Sets up the internal map from a file @param Filename		The file to load JSON from @return		True if successful.
- L177 _public prototype_ `virtual bool DeserializeFromData(const TArray<uint8>& DataInput);` — Sets up the object from the passed in data @param DataInput		The data to deserialize from @return		True if successful.
- L184 _public prototype_ `virtual bool DeserializeFromJSON(const FString& JSONInput);` — Sets up the object from the passed in JSON string @param JSONInput		The JSON string to deserialize from @return		True if successful.
- L195 _public prototype_ `virtual bool SaveToFile(const FString& Filename, BuildPatchServices::EFeatureLevel SaveFormat, FSHAHash* OutSHA1Hash = nullptr, FMD5Hash* OutMD5Hash = nullptr);` — Saves out the manifest information. @param Filename      IN   The file to save to. @param SaveFormat    IN   The feature level that the intended client has support for, which the manifest will need saving as. A manifest file cannot be downgraded, the function will fail if the provided value is less than GetFeatureLevel(). @param OutSHA1Hash   OUT  An output variable which will be populated with the SHA1 hash of the written manifest. @param OutMD5Hash    OUT  An output variable which will be populated with the MD5 hash of the written manifest. @return True if successful.
- L201 _public prototype_ `virtual void SerializeToJSON(FString& JSONOutput);` — Creates the object in JSON format @param JSONOutput		A string to receive the JSON representation
- L208 _public prototype_ `virtual uint32 GetNumberOfChunkReferences(const FGuid& ChunkGuid) const;` — Get the number of times a chunks is referenced in this manifest @param ChunkGuid		The chunk GUID @return	The number of references to this chunk
- L215 _public prototype_ `virtual int64 GetDataSize(const TArray<FGuid>& DataGuids) const;` — Returns the total size of all data files in it's list. @param DataGuids		The GUID array for the data @return		Total file size, or 0 if none of this data is in the manifest.
- L216 _public prototype_ `virtual int64 GetDataSize(const TSet <FGuid>& DataGuids) const;`
- L222 _public prototype_ `virtual uint32 GetNumFiles() const;` — Returns the number of files in this build. @return		The number of files.
- L228 _public prototype_ `virtual void GetFileList(TArray<FString>& Filenames) const;` — Get the list of files described by this manifest @param Filenames		OUT		Receives the list of files.
- L229 _public prototype_ `virtual void GetFileList(TArray<FStringView>& Filenames) const;`
- L230 _public prototype_ `virtual void GetFileList(TSet <FString>& Filenames) const;`
- L237 _public prototype_ `virtual void GetTaggedFileList(const TSet<FString>& Tags, TArray<FString>& TaggedFiles) const;` — Get the list of files that are tagged with the provided tags @param Tags					The tags for the required file groups. @param TaggedFiles	OUT		Receives the tagged files.
- L238 _public prototype_ `virtual void GetTaggedFileList(const TSet<FString>& Tags, TArray<FStringView>& TaggedFiles) const;`
- L239 _public prototype_ `virtual void GetTaggedFileList(const TSet<FString>& Tags, TSet<FString>& TaggedFiles) const;`
- L246 _public prototype_ `virtual TSet<const BuildPatchServices::FFileManifest*> GetTaggedFileManifests(const TSet<FString>& Tags) const;` — Get the set of manifests that are tagged with the provided tags @param Tags					The tags for the required file groups. @return The set of tagged file manifests.
- L252 _public prototype_ `virtual void GetDataList(TArray<FGuid>& DataGuids) const;` — Get the list of Guids for all chunks referenced by this manifest @param DataGuids		OUT		Receives the array of Guids.
- L253 _public prototype_ `virtual void GetDataList(TSet <FGuid>& DataGuids) const;`
- L260 _public prototype_ `virtual const BuildPatchServices::FFileManifest* GetFileManifest(const FString& Filename) const;` — Returns the manifest for a particular file in the app, nullptr if non-existing @param Filename	The filename. @return	The file manifest, or invalid ptr
- L266 _public prototype_ `virtual TArray<BuildPatchServices::FFileManifest>::TConstIterator GetFileManifestIterator() const;` — @return a const iterator for the containing file manifests.
- L272 _public prototype_ `virtual bool IsFileDataManifest() const;` — Gets whether this manifest is made up of file data instead of chunk data @return	True if the build is made from file data. False if the build is constructed from chunk data.
- L280 _public prototype_ `virtual bool GetChunkHash(const FGuid& ChunkGuid, uint64& OutHash) const;` — Gets the chunk hash for a given chunk @param ChunkGuid		IN		The guid of the chunk to get hash for @param OutHash		OUT		Receives the hash value if found @return	true if we had the hash for this chunk
- L287 _public prototype_ `virtual const BuildPatchServices::FChunkInfo* GetChunkInfo(const FGuid& ChunkGuid) const;` — Gets the FChunkInfo for a given chunk. @param ChunkGuid     The guid of the chunk to get hash for. @return ptr to the FChunkInfo or nullptr if not found.
- L295 _public prototype_ `virtual bool GetFileHash(const FGuid& FileGuid, FSHAHash& OutHash) const;` — Gets the file hash for given file data @param FileGuid		IN		The guid of the file data to get hash for @param OutHash		OUT		Receives the hash value if found @return	true if we had the hash for this file
- L303 _public prototype_ `virtual bool GetFileHash(const FString& Filename, FSHAHash& OutHash) const;` — Gets the file hash for a given file @param Filename		IN		The filename in the build @param OutHash		OUT		Receives the hash value if found @return	true if we had the hash for this file
- L311 _public prototype_ `virtual bool GetFilePartHash(const FGuid& FilePartGuid, uint64& OutHash) const;` — Gets the file hash for given file data. Valid for non-chunked manifest @param FileGuid		IN		The guid of the file data to get hash for @param OutHash		OUT		Receives the hash value if found @return	true if we had the hash for this file
- L321 _public prototype_ `virtual int32 EnumerateProducibleChunks(const TSet<FString>& TagSet, const TSet<FGuid>& ChunksRequired, TSet<FGuid>& ChunksAvailable) const;` — Populates an array of chunks that should be producible from a local build, given the tagset that is expected to be installed. @param TagSet           IN   The tagset identifying files expected to be installed. @param ChunksRequired   IN   A list of chunks that are needed. @param ChunksAvailable  OUT  A list to receive the chunks from ChunksRequired that could be constructed locally. @return the number of chunks added to the ChunksAvailable set.
- L322 _public prototype_ `virtual int32 EnumerateProducibleChunks(const TSet<const BuildPatchServices::FFileManifest*>& TaggedFiles, const TSet<FGuid>& ChunksRequired, TSet<FGuid>& ChunksAvailable) const;`
- L330 _public prototype_ `virtual void GetOutdatedFiles(const FBuildPatchAppManifestPtr& OldManifest, const FString& InstallDirectory, TSet<FString>& OutDatedFiles) const;` — Gets a list of files that have changed or are new in the this manifest, compared to those in the old manifest, or are missing from disk. @param OldManifest		IN		The Build Manifest that is currently installed. Shared Ptr - Can be invalid. @param InstallDirectory	IN		The Build installation directory, so that it can be checked for missing files. @param OutDatedFiles		OUT		The files that changed hash, are new, are wrong size, or missing on disk.
- L331 _public prototype_ `virtual void GetOutdatedFiles(const FBuildPatchAppManifest* OldManifest, const FString& InstallDirectory, TSet<FString>& OutDatedFiles) const;`
- L332 _public prototype_ `virtual void GetOutdatedFiles(const FBuildPatchAppManifest* OldManifest, const FString& InstallDirectory, const TSet<FString>& FilesToCheck, TSet<FString>& OutDatedFiles) const;`
- L340 _public prototype_ `virtual void GetMissedFiles(const FString& InstallDirectory, const TSet<FString>& FilesToCheck, TSet<FString>& OutMissedFiles) const;` — Gets a list of files mentioned in the manifest that are missing from disk. @param InstallDirectory [in]  The build installation directory to check for missing files. @param FilesToCheck     [in]  The list of files to check. @param OutMissedFiles   [out] The files that are missing from disk.
- L347 _public prototype_ `virtual bool IsFileOutdated(const FBuildPatchAppManifestRef& OldManifest, const FString& Filename) const;` — Check a single file to see if it will be effected by patching from a previous version. @param OldManifest		The Build Manifest that is currently installed. Shared Ref - Implicitly valid. @param Filename			The Build installation directory, so that it can be checked for missing files.
- L348 _public prototype_ `virtual bool IsFileOutdated(const FBuildPatchAppManifest& OldManifest, const FString& Filename) const;`
- L355 _public prototype_ `virtual void GetRemovableFiles(const FBuildPatchAppManifest& OldManifest, TArray<FString>& RemovableFiles) const;` — Gets a list of files that were installed with the Old Manifest, but no longer required by this Manifest. @param OldManifest		IN		The Build Manifest that is currently installed. @param RemovableFiles	OUT		A list to receive the files that may be removed.
- L359 _public prototype_ `virtual bool HasFileAttributes() const;` — @return True if any files in this manifest have file attributes to be set
- L361 _public prototype_ `bool EncryptData(const FGuid& InEncryptionSecretId, const TArray<uint8>& InEncryptionSecretKey);`
- L363 _public prototype_ `bool DecryptData(const TMap<FGuid, TArray<uint8>>& AvailableEncryptionSecrets);`
- L369 _private prototype_ `void DestroyData();` — Destroys any memory we have allocated and clears out ready for generation of a new manifest
- L371 _private prototype_ `bool SerialiseSensitiveFields(FArchive& Ar);`
- L372 _private prototype_ `void ObfuscateSensitiveFields();`
- L378 _protected prototype_ `void InitLookups();` — Setups the lookup maps that optimize data access, should be called when Data changes
- L384 _private prototype_ `int32 EnumerateProducibleChunks_Internal(const TFunction<bool(const FString&)>& FileAccessChecker, const TSet<FGuid>& ChunksRequired, TSet<FGuid>& ChunksAvailable) const;` — Helper for the public EnumerateProducibleChunks functions.
- L389 _protected member_ `BuildPatchServices::FManifestMeta ManifestMeta;`
- L390 _protected member_ `BuildPatchServices::FChunkDataList ChunkDataList;`
- L391 _protected member_ `BuildPatchServices::FFileManifestList FileManifestList;`
- L392 _protected member_ `BuildPatchServices::FCustomFields CustomFields;`
- L393 _protected member_ `BuildPatchServices::FEncryptedData EncryptedData;`
- L398 _private member_ `FGuid EncryptionSecretId;` — The encryption secret ID and hash used for this manifest, if encrypted. These are serialised with the manifest header, not the main data.
- L399 _private member_ `BuildPatchServices::FAESAuthTag EncryptionAuthTag;`
- L402 _private member_ `bool bIsManifestEncrypted = false;` — Whether the manifest is currently encrypted.
- L405 _private member_ `FDelegateHandle OnPreExitHandle;` — Holds the handle to our PreExit delegate
- L408 _private member_ `TMap<FGuid, const FString*> FileNameLookup;` — Some lookups to optimize data access
- L409 _private member_ `TMap<FStringView, const BuildPatchServices::FFileManifest*> FileManifestLookup;`
- L410 _private member_ `TMap<FString, TArray<const BuildPatchServices::FFileManifest*>> TaggedFilesLookup;`
- L411 _private member_ `TMap<FGuid, const BuildPatchServices::FChunkInfo*> ChunkInfoLookup;`
- L414 _private member_ `int64 TotalBuildSize;` — Holds the total build size in bytes
- L415 _private member_ `int64 TotalDownloadSize;`
- L418 _private member_ `bool bNeedsResaving;` — Flag marked true if we loaded from disk as an old manifest version that should be updated

#### Free symbols / members of external scopes

- L14 _typedef_ `typedef TSharedPtr< class FBuildPatchCustomField, ESPMode::ThreadSafe > FBuildPatchCustomFieldPtr;`
- L15 _typedef_ `typedef TSharedRef< class FBuildPatchCustomField, ESPMode::ThreadSafe > FBuildPatchCustomFieldRef;`
- L16 _typedef_ `typedef TSharedPtr< class FBuildPatchAppManifest, ESPMode::ThreadSafe > FBuildPatchAppManifestPtr;`
- L17 _typedef_ `typedef TSharedRef< class FBuildPatchAppManifest, ESPMode::ThreadSafe > FBuildPatchAppManifestRef;`
- L50 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/BuildPatchMergeManifests.h` (Private)


#### class `FBuildMergeManifests`  
`class FBuildMergeManifests`  
_L7-15_
- L10 _public prototype_ `static bool MergeManifests(const FString& ManifestFilePathA, const FString& ManifestFilePathB, const FString& ManifestFilePathC, const FString& NewVersionString, const FString& SelectionDetailFilePath, const TMap<FGuid, TArray<uint8>>& AvailableEncryptionSecrets);`
- L12 _public prototype_ `static IBuildManifestPtr MergeManifests(const IBuildManifestRef& ManifestA, const IBuildManifestRef& ManifestB, const FString& NewVersionString, const TSet<FString>& FilesFromA, const TSet<FString>& FilesFromB);`
- L14 _public prototype_ `static FBuildPatchAppManifestPtr MergeDeltaManifest(const FBuildPatchAppManifest& Manifest, const FBuildPatchAppManifest& Delta);`

### `Source/Runtime/Online/BuildPatchServices/Private/BuildPatchProgress.h` (Private)


#### struct `BuildPatchServices::FBuildPatchProgress`  
`struct FBuildPatchProgress : public IControllable`  
_L20-154_
- inherits: `IControllable`
- desc: A struct to hold patch progress tracking
- L28 _public prototype_ `FBuildPatchProgress();` — Default constructor
- L31 _public prototype_ `virtual void SetPaused(bool bIsPaused) override;` — IControllable interface begin.
- L32 _public prototype_ `virtual void Abort() override;`
- L33 _public prototype_ `virtual void Reset() override;`
- L41 _public prototype_ `virtual void SetStateProgress(const EBuildPatchState& State, const float& Value);` — Sets the progress value for a particular state @param State		The state to set progress for @param Value		The progress value
- L48 _public prototype_ `virtual void SetStateWeight(const EBuildPatchState& State, const float& Value);` — Sets the progress weight for a particular state @param State		The state to set weight for @param Value		The weight value
- L54 _public prototype_ `virtual EBuildPatchState GetState() const;` — Gets the current progress state @return The current progress state
- L60 _public prototype_ `virtual float GetProgress() const;` — Gets the current overall progress @return The current progress value. Range 0 to 1. -1 indicates undetermined, i.e. show a marquee style bar.
- L66 _public prototype_ `virtual float GetProgressNoMarquee() const;` — Gets the current overall progress regardless of current state using marquee @return The current progress value. Range 0 to 1.
- L73 _public prototype_ `virtual float GetStateProgress(const EBuildPatchState& State) const;` — Gets the progress value for a particular state @param State		The state to get progress for @return The state progress value. Range 0 to 1.
- L80 _public prototype_ `virtual float GetStateWeight(const EBuildPatchState& State) const;` — Gets the weight value for a particular state @param State		The state to get weight for @return The state weight value.
- L86 _public prototype_ `virtual bool TogglePauseState();` — Toggles the pause state @return Whether the current state is now paused
- L92 _public prototype_ `virtual double WaitWhilePaused() const;` — Blocks calling thread while the progress is paused @return How long we paused for, in seconds
- L98 _public prototype_ `virtual bool GetPauseState() const;` — Gets the pause state @return Whether the current state is paused
- L104 _public prototype_ `virtual void SetIsDownloading(bool bIsDownloading);` — Set the set state of whether the system is currently downloading data. @param bIsDownloading	Whether the system is currently downloading data.
- L111 _private prototype_ `void UpdateProgressInfo();` — Updates the current state and progress values
- L116 _private prototype_ `void UpdateCachedValues();` — Updates the cached values
- L122 _private member_ `static const bool bHasProgressValue[static_cast<int32>(EBuildPatchState::NUM_PROGRESS_STATES)];` — Defines whether each state displays progress percent or is designed for a "please wait" or marquee style progress bar This is predefined and constant.
- L126 _private member_ `static const bool bCountsTowardsProgress[static_cast<int32>(EBuildPatchState::NUM_PROGRESS_STATES)];` — Defines whether each state should count towards the overall progress This is predefined and constant.
- L130 _private member_ `float StateProgressValues[static_cast<int32>(EBuildPatchState::NUM_PROGRESS_STATES)];` — Holds the current percentage complete for each state, this will decide the "current" state, being the first that is not complete. Range 0 to 1.
- L134 _private member_ `float StateProgressWeights[static_cast<int32>(EBuildPatchState::NUM_PROGRESS_STATES)];` — Holds the weight that each stage has on overall progress. Range 0 to 1.
- L137 _private member_ `float TotalWeight;` — Cached total weight value for progress calculation
- L140 _private member_ `bool bIsDownloading;` — Externally set variable to say if the system is currently making download requests
- L143 _private member_ `EBuildPatchState CurrentState;` — The current state value for UI polling
- L146 _private member_ `float CurrentProgress;` — The current progress value for UI polling
- L149 _private member_ `FThreadSafeBool bShouldAbort;` — Thread safe bool for whether the process should abort
- L152 _private member_ `mutable FCriticalSection ThreadLock;` — Critical section to protect variable access

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/BuildPatchServicesModule.h` (Private)


#### enum `(anonymous)`  
``  
_L18-22_

#### class `FBuildPatchServicesModule`  
`class FBuildPatchServicesModule : public IBuildPatchServicesModule`  
_L28-171_
- inherits: `IBuildPatchServicesModule`
- desc: Implements the BuildPatchServicesModule.
- L34 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface begin.
- L35 _public prototype_ `virtual void ShutdownModule() override;`
- L39 _public prototype_ `virtual IBuildInstallerRef CreateBuildInstaller(BuildPatchServices::FBuildInstallerConfiguration Configuration, FBuildPatchInstallerDelegate OnComplete) const override;` — IBuildPatchServicesModule interface begin.
- L40 _public prototype_ `virtual IBuildInstallerSharedContextRef CreateBuildInstallerSharedContext(const TCHAR* DebugName) const override;`
- L41 _public prototype_ `virtual BuildPatchServices::IBuildStatisticsRef CreateBuildStatistics(const IBuildInstallerRef& Installer) const override;`
- L42 _public prototype_ `virtual BuildPatchServices::IDirectoryChunkerRef CreateDirectoryChunker(BuildPatchServices::FDirectoryChunkerConfiguration Configuration) const override;`
- L43 _public prototype_ `virtual BuildPatchServices::IPatchDataEnumerationRef CreatePatchDataEnumeration(BuildPatchServices::FPatchDataEnumerationConfiguration Configuration) const override;`
- L44 _public prototype_ `virtual BuildPatchServices::IChunkDeltaOptimiserRef CreateChunkDeltaOptimiser(BuildPatchServices::FChunkDeltaOptimiserConfiguration Configuration) const override;`
- L45 _public prototype_ `virtual BuildPatchServices::IChunkHarvesterRef CreateChunkHarvester(BuildPatchServices::FChunkHarvesterConfiguration Configuration) const override;`
- L46 _public prototype_ `virtual IBuildManifestPtr LoadManifestFromFile(const FString& Filename) override;`
- L47 _public prototype_ `virtual IBuildManifestPtr MakeManifestFromData(const TArray<uint8>& ManifestData) override;`
- L48 _public prototype_ `virtual bool SaveManifestToFile(const FString& Filename, IBuildManifestRef Manifest) override;`
- L49 _public prototype_ `virtual TSet<FString> GetInstalledPrereqIds() const override;`
- L50 _public prototype_ `virtual const TArray<IBuildInstallerRef>& GetInstallers() const override;`
- L51 _public prototype_ `virtual void SetStagingDirectory(const FString& StagingDir) override;`
- L52 _public prototype_ `virtual void SetCloudDirectory(FString CloudDir) override;`
- L53 _public prototype_ `virtual void SetCloudDirectories(TArray<FString> CloudDirs) override;`
- L54 _public prototype_ `virtual void SetBackupDirectory(const FString& BackupDir) override;`
- L55 _public prototype_ `virtual void SetAnalyticsProvider(TSharedPtr< IAnalyticsProvider > AnalyticsProvider) override;`
- L56 _public prototype_ `virtual void RegisterAppInstallation(IBuildManifestRef AppManifest, const FString AppInstallDirectory) override;`
- L57 _public prototype_ `virtual bool UnregisterAppInstallation(const FString AppInstallDirectory) override;`
- L58 _public prototype_ `virtual void RegisterEncryptionSecret(const FGuid& EncryptionSecretId, TArray<uint8> EncryptionSecretKey) override;`
- L59 _public prototype_ `virtual bool UnregisterEncryptionSecret(const FGuid& EncryptionSecretId) override;`
- L60 _public prototype_ `virtual bool CreateRandomBytes(const TArrayView<uint8> OutData) override;`
- L61 _public prototype_ `virtual void CancelAllInstallers(bool WaitForThreads) override;`
- L62 _public prototype_ `virtual bool CompactifyCloudDirectory(const BuildPatchServices::FCompactifyConfiguration& Configuration) override;`
- L63 _public prototype_ `virtual bool VerifyChunkData(const FString& SearchPath, const FString& OutputFile) override;`
- L64 _public prototype_ `virtual bool PackageChunkData(const BuildPatchServices::FPackageChunksConfiguration& Configuration) override;`
- L65 _public prototype_ `virtual bool MergeManifests(const FString& ManifestFilePathA, const FString& ManifestFilePathB, const FString& ManifestFilePathC, const FString& NewVersionString, const FString& SelectionDetailFilePath) override;`
- L66 _public prototype_ `virtual IBuildManifestPtr MergeManifests(const IBuildManifestRef& ManifestA, const IBuildManifestRef& ManifestB, const FString& NewVersionString, const TSet<FString>& FilesFromA, const TSet<FString>& FilesFromB) override;`
- L67 _public prototype_ `virtual bool DiffManifests(const BuildPatchServices::FDiffManifestsConfiguration& Configuration) override;`
- L68 _public prototype_ `virtual FSimpleEvent& OnStartBuildInstall() override;`
- L69 _public prototype_ `virtual IBuildManifestPtr MakeManifestFromJSON(const FString& ManifestJSON) override;`
- L76 _public prototype_ `static const FString& GetStagingDirectory();` — Gets the directory used for staging intermediate files. @return	The staging directory
- L83 _public prototype_ `static FString GetCloudDirectory(int32 CloudIdx = 0);` — Gets the cloud directory where chunks and manifests will be pulled from. @param CloudIdx    Optional override for which cloud directory to get. This value will wrap within the range of available cloud directories. @return	The cloud directory
- L89 _public prototype_ `static TArray<FString> GetCloudDirectories();` — Gets the cloud directories where chunks and manifests will be pulled from. @return	The cloud directories
- L95 _public prototype_ `static const FString& GetBackupDirectory();` — Gets the backup directory for saving files clobbered by repair/patch. @return	The backup directory
- L103 _private prototype_ `bool Tick(float Delta);` — Tick function to monitor installers for completion, so that we can call delegates on the main thread @param		Delta	Time since last tick @return	Whether to continue ticking
- L108 _private prototype_ `void PreExit();` — This will get called when core PreExits. Make sure any running installers are canceled out.
- L113 _private prototype_ `void FixupLegacyConfig();` — Called during init to perform any fix up required to new configuration.
- L118 _private prototype_ `void NormalizeCloudPaths(TArray<FString>& InOutCloudPaths);` — Helper function to normalize the provided directory list.
- L121 _private prototype_ `TOptional<TArray<uint8>> FindEncryptionSecret(const FGuid& EncryptionSecretId) const;` — Get the encryption secret by the specified secret ID.
- L124 _private prototype_ `TMap<FGuid, TArray<uint8>> GetEncryptionSecrets() const;` — Get all registered encryption secrets.
- L127 _private prototype_ `void DecryptManifestIfNecessary(FBuildPatchAppManifest& Manifest) const;` — Decrypt manifest when the manifest's encryption secret is available
- L131 _private member_ `static TSharedPtr<IAnalyticsProvider> Analytics;` — The analytics provider interface
- L134 _private member_ `static TArray<FString> CloudDirectories;` — Holds the cloud directories where chunks should belong
- L137 _private member_ `static FString StagingDirectory;` — Holds the staging directory where we can perform any temporary work
- L140 _private member_ `static FString BackupDirectory;` — Holds the backup directory where we can move files that will be clobbered by repair or patch
- L143 _private member_ `FString LocalMachineConfigFile;` — Holds the filename for local machine config. This is instead of shipped or user config, to track machine installation config.
- L146 _private member_ `bool bForceSkipPrereqs;` — A flag specifying whether prerequisites install should be skipped
- L149 _private member_ `TArray<FBuildPatchInstallerRef> BuildPatchInstallers;` — Array of running installers
- L152 _private member_ `TArray<IBuildInstallerRef> BuildPatchInstallerInterfaces;` — Array of running installers as exposable interface refs
- L155 _private member_ `TMultiMap<FString, FBuildPatchAppManifestRef> AvailableInstallations;` — Holds available installations used for recycling install data
- L158 _private member_ `mutable FCriticalSection AvailableEncryptionSecretsCS;` — Critical section for multi-threaded access to AvailableEncryptionSecrets
- L161 _private member_ `TMap<FGuid, TArray<uint8>> AvailableEncryptionSecrets;` — Holds available encryption secrets used for decrypting installation data
- L164 _private member_ `FTSTicker::FDelegateHandle TickDelegateHandle;` — Handle to the registered Tick delegate
- L167 _private member_ `FBuildPatchInstallerDelegate InstallerStartDelegate;` — Delegate to give to installers so we know when they have been started.
- L170 _private member_ `FSimpleEvent OnStartBuildInstallEvent;` — Event broadcast upon a new build install

#### Free symbols / members of external scopes

- L20 _enumerator_ `FileBufferSize = 1024*1024*4` (scope `__anon29a1d57a0103`) — Sizes
- L21 _enumerator_ `StreamBufferSize = FileBufferSize*4` (scope `__anon29a1d57a0103`) — When reading from build data stream, how much to buffer.

### `Source/Runtime/Online/BuildPatchServices/Private/BuildPatchServicesPrivate.h` (Private)


#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogBuildPatchServices, Log, All);`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogBuildPatchServices, Log, All);`

### `Source/Runtime/Online/BuildPatchServices/Private/BuildPatchUtil.h` (Private)


#### enum `EBuildPatchDataType`  
`enum class EBuildPatchDataType`  
_L21-27_
- L24 _public enumerator_ `ChunkData = 0` — Represents data produced by the chunked patch generation mode.
- L26 _public enumerator_ `FileData = 1` — Represents data produced by the nochunks patch generation mode, which has deprecated.

#### struct `FBuildPatchUtils`  
`struct FBuildPatchUtils`  
_L48-184_
- desc: Some utility functions
- L56 _public prototype_ `static FString GetChunkNewFilename(BuildPatchServices::EFeatureLevel FeatureLevel, const BuildPatchServices::FChunkInfo& Chunk);` — Gets the relative cloud filename for a chunk in the newest format. @param FeatureLevel   The manifest version that references this chunk. @param Chunk          The chunk we need a path for @return the chunk path.
- L57 _public prototype_ `static FString GetChunkNewFilename(BuildPatchServices::EFeatureLevel FeatureLevel, const BuildPatchServices::FChunkHeader& Chunk);`
- L66 _public prototype_ `static FString GetFileNewFilename(BuildPatchServices::EFeatureLevel FeatureLevel, const FGuid& FileGUID, const FSHAHash& FileHash);` — Gets the the relative cloud filename for a file chunk generated from it's GUID and Hash, which is the new format. @param FeatureLevel   The manifest version that references this file. @param FileGUID       The file chunk Guid. @param FileHash       The file hash value. @return the file chunk path.
- L67 _public prototype_ `static FString GetFileNewFilename(BuildPatchServices::EFeatureLevel FeatureLevel, const FGuid& FileGUID, const uint64& FilePartHash);`
- L74 _public prototype_ `static FString GetChunkOldFilename(const FGuid& ChunkGUID);` — Gets the the relative cloud filename for a chunk generated from it's GUID @param ChunkGuid			The chunk Guid @return	the chunk path
- L81 _public prototype_ `static FString GetFileOldFilename(const FGuid& FileGUID);` — Gets the the relative cloud filename for a file data part generated from it's GUID @param FileGUID			The file part Guid @return	The file data path
- L89 _public prototype_ `static FString GetDataTypeOldFilename(EBuildPatchDataType DataType, const FGuid& Guid);` — Gets the filename for a specific data part type from it's GUID @param DataType			The type of data @param DataGUID			The data Guid @return	the data part path
- L97 _public prototype_ `static FString GetDataFilename(const FBuildPatchAppManifestRef& Manifest, const FGuid& DataGUID);` — Gets the relative cloud filename for any data part. Wraps the choice between all of the above @param Manifest			The manifest referencing this data @param DataGUID			The data Guid @return	the data part path
- L98 _public prototype_ `static FString GetDataFilename(const FBuildPatchAppManifest& Manifest, const FGuid& DataGUID);`
- L106 _public prototype_ `static bool GetGUIDFromFilename(const FString& DataFilename, FGuid& DataGUID);` — Gets the GUID for a data file according to it's filename (new or old) @param DataFilename		IN		The data filename, or URL @param DataGUID			OUT		Receives the GUID of the data @return  True if successful, false otherwise
- L112 _public prototype_ `static FString GenerateNewBuildId();` — Generates a new BuildId for a manifest. This should be used only when creating new builds, and thus saving out brand new manifests rather than copies of manifests. @return the generated id.
- L120 _public prototype_ `static FString GetBackwardsCompatibleBuildId(const BuildPatchServices::FManifestMeta& ManifestMeta);` — Creates a deterministic BuildId for use with a manifest that is at EFeatureLevel::UsesRuntimeGeneratedBuildId or older. The id is created based on the meta data, which itself should be unique per build created. @param ManifestMeta     The meta for the old manifest. @return the id for this manifest.
- L127 _public prototype_ `static FString GetChunkDeltaDirectory(const FBuildPatchAppManifest& DestinationManifest);` — Based on the destination manifest, get the directory that will contains the deltas for getting to it from other builds. @param DestinationManifest   The destination manifest. @return the CloudDir relative delta directory.
- L136 _public prototype_ `static FString GetChunkDeltaFilename(const FBuildPatchAppManifest& SourceManifest, const FBuildPatchAppManifest& DestinationManifest, const FString& FilenameTrailer);` — Based on the source and destination manifests, get the filename for the delta that optimises patching from source to destination. @param SourceManifest        The source manifest. @param DestinationManifest   The destination manifest. @param FilenameTrailer       This is an optional parameter to allow for multiple optimized deltas for the same build pairing. If unneeded, leave as "". @return the CloudDir relative delta filename.
- L150 _public prototype_ `static uint8 VerifyFile(BuildPatchServices::IFileSystem* FileSystem, const FString& FileToVerify, const FSHAHash& Hash1, const FSHAHash& Hash2, FBuildPatchFloatDelegate ProgressDelegate, FBuildPatchBoolRetDelegate ShouldPauseDelegate, FBuildPatchBoolRetDelegate ShouldAbortDelegate);` — Checks a file against SHA1 hashes. The function takes two so that it can return no match, match with Hash1, or match with Hash2, that way we can check the file for being the same as an old manifest or new manifest NOTE: This function is blocking and will not return until finished. Don't run on main thread. @param FileSystem			IN		Interface to disk access. @param FileToVerify			IN		The file to analyze. @param Hash1					IN		A Hash to match against the file @param Hash2					IN		A second Hash to match against the file @param ProgressDelegate		IN		Delegate to receive progress updates in the form of a float range 0.0f to 1.0f @param ShouldPauseDelegate	IN		Delegate that returns a bool, which if true will pause the process @param ShouldAbortDelegate	IN		Delegate that returns a bool, which if true will abort the process @return		0 if no match, 1 for match with Hash1, and 2 for match with Hash2
- L161 _public prototype_ `static uint8 VerifyFile(BuildPatchServices::IFileSystem* FileSystem, const FString& FileToVerify, const FSHAHash& Hash1, const FSHAHash& Hash2);` — Checks a file against SHA1 hashes. The function takes two so that it can return no match, match with Hash1, or match with Hash2, that way we can check the file for being the same as an old manifest or new manifest NOTE: This function is blocking and will not return until finished. Don't run on main thread. This allows the above function to be easily called without delegates @param FileSystem			IN		Interface to disk access. @param FileToVerify			IN		The file to analyze. @param Hash1					IN		A Hash to match against the file @param Hash2					IN		A second Hash to match against the file @return		0 if no match, 1 for match with Hash1, and 2 for match with Hash2
- L168 _public prototype_ `static void SHAToBase32(const FSHAHash& SHA, FString& OutString);` — Encodes SHA hash to base32 and convert its to out string @param SHA					IN		SHA hash to encode @param OutString				OUT		String with base32 encoded value
- L170 _public prototype_ `static uint64 CalculateDiskSpaceRequirementsWithDeleteDuringInstall( const TArray<FString>& InFilesToConstruct, int32 InCompletedFileCount, int64 InProgressFileSize, BuildPatchServices::IBuildManifestSet* InManifestSet, const TArray<uint64>& InChunkDbSizesAtPosition, const FString& InstallDirectory, BuildPatchServices::EInstallMode mode);`
- L183 _public prototype_ `static FString ResolveInstallationFileName(const FString& BaseInstallationDirectory, const TMap<FString, FString>& PerFileSubdirectories, const FString& BuildFilename);` — Generates the path to the file we're installing by adjusting the path for per file subdirectories. Currently this does not handle installation subdirectories which are appended as part of the manifest set.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace BuildPatchServices`
- L31 _delegate_ `DECLARE_DELEGATE_OneParam(FBuildPatchFloatDelegate, float);` — A delegate taking a float. Used to receive progress.
- L31 _prototype_ `DECLARE_DELEGATE_OneParam(FBuildPatchFloatDelegate, float);` — A delegate taking a float. Used to receive progress.
- L34 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FBuildPatchBoolRetDelegate);` — A delegate returning a bool. Used to pass a paused state.
- L34 _prototype_ `DECLARE_DELEGATE_RetVal(bool, FBuildPatchBoolRetDelegate);` — A delegate returning a bool. Used to pass a paused state.
- L39 _namespace_ `namespace BuildPatchConstants`
- L42 _variable_ `static const int32 SHAToBase32StringLength = 32;` (scope `BuildPatchConstants`) — Result of converting SHA1 to base32 string value length

### `Source/Runtime/Online/BuildPatchServices/Private/BuildPatchVerifyChunkData.h` (Private)


#### class `FBuildVerifyChunkData`  
`class FBuildVerifyChunkData`  
_L6-10_
- L9 _public prototype_ `static bool VerifyChunkData(const FString& SearchPath, const FString& OutputFile);`

### `Source/Runtime/Online/BuildPatchServices/Private/Common/ChunkDataSizeProvider.h` (Private)


#### class `BuildPatchServices::IChunkDataSizeProvider`  
`class IChunkDataSizeProvider : public IDataSizeProvider`  
_L10-16_
- inherits: `IDataSizeProvider`
- L14 _public prototype_ `virtual void AddManifestData(FBuildPatchAppManifestPtr Manifest) = 0;`
- L15 _public prototype_ `virtual void AddManifestData(TConstArrayView<FBuildPatchAppManifestPtr> Manifests) = 0;`

#### class `BuildPatchServices::FChunkDataSizeProviderFactory`  
`class FChunkDataSizeProviderFactory`  
_L18-22_
- L21 _public prototype_ `static IChunkDataSizeProvider* Create(const TArray<FBuildPatchAppManifestPtr>& InitialManifests);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Common/Crypto.h` (Private)


#### struct `BuildPatchServices::FAESAuthTag`  
`struct FAESAuthTag`  
_L13-21_
- L16 _public member_ `alignas(uint32) uint8 AuthTag[AES256_GCM_AuthTagSizeInBytes] = { 0 };`
- L17 _public function_ `void Reset()`

#### class `BuildPatchServices::ICrypto`  
`class ICrypto`  
_L27-44_
- desc: This Crypto class for the time being takes code from other engine locations such as plugins, which unfortunately cannot be relied on. We are going to entirely use OpenSSL implementations, so it will only be available on platforms supporting this.
- L30 _public function_ `virtual ~ICrypto()`
- L33 _public function_ `virtual bool IsAvailable() const`
- L37 _public prototype_ `virtual bool IsValidKey_AES_256_GCM(const TArrayView<const uint8> Key) const = 0;`
- L39 _public prototype_ `virtual TArray<uint8> Encrypt_AES_256_GCM(const TArrayView<const uint8> Plaintext, const TArrayView<const uint8> Key, const TArrayView<const uint8> InitializationVector, TArray<uint8>& OutAuthTag, bool& OutResult) const = 0;`
- L41 _public prototype_ `virtual TArray<uint8> Decrypt_AES_256_GCM(const TArrayView<const uint8> Ciphertext, const TArrayView<const uint8> Key, const TArrayView<const uint8> InitializationVector, const TArrayView<const uint8> AuthTag, bool& OutResult) const = 0;`
- L43 _public prototype_ `virtual bool CreateRandomBytes(const TArrayView<uint8> OutData) const = 0;`

#### class `BuildPatchServices::FCryptoFactory`  
`class FCryptoFactory`  
_L49-57_
- desc: A factory for creating an ICrypto instance.
- L56 _public prototype_ `static ICrypto* Create();` — Creates an implementation which wraps use of OpenSLL crypto functionality, or is not available on platforms without OpenSSL. @return the new ICrypto instance created.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace BuildPatchServices`
- L9 _variable_ `constexpr int AES256_GCM_InitializationVectorSizeInBytes = 12;` (scope `BuildPatchServices`)
- L10 _variable_ `constexpr int AES256_GCM_AuthTagSizeInBytes = 16;` (scope `BuildPatchServices`)
- L11 _variable_ `constexpr int AES256_GCM_KeySizeInBytes = 32;` (scope `BuildPatchServices`)

### `Source/Runtime/Online/BuildPatchServices/Private/Common/DataSizeProvider.h` (Private)


#### class `BuildPatchServices::IDataSizeProvider`  
`class IDataSizeProvider`  
_L9-16_
- L12 _public prototype_ `virtual ~IDataSizeProvider() = default;`
- L14 _public prototype_ `virtual uint64 GetDownloadSize(const FString& Uri) const = 0;`
- L15 _public prototype_ `virtual void GetDownloadSize(TConstArrayView<FString> InUris, TArray<uint64>& OutSizes) const = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Common/FileSystem.h` (Private)


#### enum `BuildPatchServices::EAttributeFlags`  
`enum class EAttributeFlags : uint32`  
_L11-23_
- L14 _public enumerator_ `None = 0` — Value for no attributes.
- L16 _public enumerator_ `Exists = 1 << 0` — Whether the file exists on the storage volume.
- L18 _public enumerator_ `ReadOnly = 1 << 1` — Whether the file is readonly.
- L20 _public enumerator_ `Compressed = 1 << 2` — Whether the file is compressed.
- L22 _public enumerator_ `Executable = 1 << 3` — Whether the file is executable.

#### enum `BuildPatchServices::EWriteFlags`  
`enum class EWriteFlags : uint32`  
_L26-34_
- L28 _public enumerator_ `None = 0`
- L29 _public enumerator_ `NoFail = 1 << 0`
- L30 _public enumerator_ `NoReplaceExisting = 1 << 1`
- L31 _public enumerator_ `EvenIfReadOnly = 1 << 2`
- L32 _public enumerator_ `Append = 1 << 3`
- L33 _public enumerator_ `AllowRead = 1 << 4`

#### enum `BuildPatchServices::EReadFlags`  
`enum class EReadFlags : uint32`  
_L37-43_
- L39 _public enumerator_ `None = 0`
- L40 _public enumerator_ `NoFail = 1 << 0`
- L41 _public enumerator_ `Silent = 1 << 1`
- L42 _public enumerator_ `AllowWrite = 1 << 2`

#### class `BuildPatchServices::IFileSystem`  
`class IFileSystem`  
_L59-273_
- desc: The File System class is used for classes which require file access. It wraps Core IFileManager, and IPlatformFile. Also provides additional functionality missing from these classes at the time of writing. Using this wrapper allows dependants to be easily testable.
- L62 _public prototype_ `virtual ~IFileSystem() = default;`
- L69 _public prototype_ `virtual bool DirectoryExists(const TCHAR* DirectoryPath) const = 0;` — Checks whether a directory exists. @param DirectoryPath     The directory to check. @return true if directory exists.
- L76 _public prototype_ `virtual bool MakeDirectory(const TCHAR* DirectoryPath) const = 0;` — Create a directory path. @param DirectoryPath     The directory path to create. @return true if successful.
- L83 _public prototype_ `virtual bool DeleteDirectoryRecursively(const TCHAR* DirectoryPath) const = 0;` — Delete a directory path including all containing files and folders. @param DirectoryPath     The directory path to delete. @return true if successful.
- L91 _public prototype_ `virtual bool GetFileSize(const TCHAR* Filename, int64& FileSize) const = 0;` — Get the size of a file. @param Filename          The filename for the request. @param FileSize          Receives the file size in bytes or INDEX_NONE if the file didn't exist. @return true if successful.
- L99 _public prototype_ `virtual bool GetAttributes(const TCHAR* Filename, EAttributeFlags& Attributes) const = 0;` — Get the attributes for a file. @param Filename          The filename for the request. @param Attributes        Receives the attribute flags if successful. @return true if successful.
- L107 _public prototype_ `virtual bool GetTimeStamp(const TCHAR* Filename, FDateTime& TimeStamp) const = 0;` — Get modification time of a file. @param Filename          The filename for the request. @param TimeStamp         Receives the time stamp if successful. @return true if successful.
- L115 _public prototype_ `virtual bool SetReadOnly(const TCHAR* Filename, bool bIsReadOnly) const = 0;` — Set whether the file is readonly. @param Filename          The filename for the request. @param bIsReadOnly       The state to set. @return true if successful.
- L123 _public prototype_ `virtual bool SetCompressed(const TCHAR* Filename, bool bIsCompressed) const = 0;` — Set whether the file is compressed. @param Filename          The filename for the request. @param bIsCompressed     The state to set. @return true if successful.
- L131 _public prototype_ `virtual bool SetExecutable(const TCHAR* Filename, bool bIsExecutable) const = 0;` — Set whether the file is executable. @param Filename          The filename for the request. @param bIsExecutable     The state to set. @return true if successful.
- L139 _public prototype_ `virtual bool SetFileSize(const TCHAR* Filename, int64 FileSize) const = 0;` — Sets the size of a file, can increase or decrease, and will also create a file that does not exist.. @param Filename          The filename for the request. @param FileSize          The desired size in bytes. @return true if successful.
- L147 _public prototype_ `virtual TUniquePtr<FArchive> CreateFileReader(const TCHAR* Filename, EReadFlags ReadFlags = EReadFlags::None) const = 0;` — Creates file reader archive. @param Filename          The filename for the request. @param ReadFlags         The file open flags. @return unique pointer to the created archive, invalid if failed to open the file.
- L156 _public prototype_ `virtual TUniquePtr<FArchive> CreateFileReaderEx(const TCHAR* Filename, EReadFlags ReadFlags, IFileHandle** OutHandle) const = 0;` — Creates file reader archive. @param Filename          The filename for the request. @param ReadFlags         The file open flags. @param OutHandle			Pointer to the file handler used by the archive. The returned FArchive owns the instance of OutHandle and controls its lifetime. @return unique pointer to the created archive, invalid if failed to open the file.
- L164 _public prototype_ `virtual TUniquePtr<FArchive> CreateFileWriter(const TCHAR* Filename, EWriteFlags WriteFlags = EWriteFlags::None) const = 0;` — Creates file writer archive. @param Filename          The filename for the request. @param WriteFlags        The file open flags. @return unique pointer to the created archive, invalid if failed to open the file.
- L172 _public prototype_ `virtual bool LoadFileToString(const TCHAR* Filename, FString& Contents) const = 0;` — Load a file on disk into string. @param Filename          The filename for the request. @param Contents          The contents of the file if successful. @return true if successful.
- L180 _public prototype_ `virtual bool SaveStringToFile(const TCHAR* Filename, const FString& Contents) const = 0;` — Save a string to file on disk. @param Filename          The filename for the request. @param Contents          The string to save. @return true if successful.
- L188 _public prototype_ `virtual bool LoadFileToArray(const TCHAR* Filename, TArray<uint8>& Contents) const = 0;` — Load a file on disk into a byte array. @param Filename          The filename for the request. @param Contents          The contents of the file if successful. @return true if successful.
- L196 _public prototype_ `virtual bool SaveArrayToFile(const TCHAR* Filename, const TArray<uint8>& Contents) const = 0;` — Save a byte array to file on disk. @param Filename          The filename for the request. @param Contents          The string to save. @return true if successful.
- L203 _public prototype_ `virtual bool DeleteFile(const TCHAR* Filename) const = 0;` — Delete a file. @param Filename          The file to delete. @return true if the file was deleted or did not exist.
- L212 _public prototype_ `virtual bool MoveFile(const TCHAR* FileDest, const TCHAR* FileSource, bool bDoNotRetryOrError = true) const = 0;` — Move or rename a file. @param FileDest          The destination file path. @param FileSource        The source file path. @param bDoNotRetryOrError Do not try to repeat failed move operation. @return true if the file was moved/renamed successfully.
- L220 _public prototype_ `virtual bool CopyFile(const TCHAR* FileDest, const TCHAR* FileSource) const = 0;` — Copy a file. @param FileDest          The destination file path. @param FileSource        The source file path. @return true if the file was copied successfully.
- L227 _public prototype_ `virtual bool FileExists(const TCHAR* Filename) const = 0;` — Checks whether a file exists. @param Filename          The file to check. @return true if file exists.
- L235 _public prototype_ `virtual void FindFiles(TArray<FString>& FoundFiles, const TCHAR* Directory, const TCHAR* FileExtension = nullptr) const = 0;` — Finds all the files within the given directory, with optional file extension filter. @param FoundFiles        Receives the files that matched the optional FileExtension filter, or all files if none was specified. @param Directory         The directory to iterate the contents of. @param FileExtension     The extension to filter by, in the form of TEXT(".ext"). If null or empty string, all files are found.
- L244 _public prototype_ `virtual void FindFilesRecursively(TArray<FString>& FoundFiles, const TCHAR* Directory, const TCHAR* FileExtension = nullptr, bool bFollowSymlinks = true) const = 0;` — Finds all the files within the given directory tree, with optional file extension filter. @param FoundFiles        Receives the files that matched the optional FileExtension filter, or all files if none was specified. @param Directory         The directory to iterate the contents of. This function explores subdirectories. @param FileExtension     The extension to filter by, in the form of TEXT(".ext"). If null or empty string, all files are found. @param bFollowSymlinks   Whether symlinks to directories should be followed and enumerated, or added as a file.
- L255 _public prototype_ `virtual void ParallelFindFilesRecursively(TArray<FString>& FoundFiles, const TCHAR* Directory, const TCHAR* FileExtension = nullptr, EAsyncExecution AsyncExecution = EAsyncExecution::ThreadPool, bool bFollowSymlinks = true) const = 0;` — Finds all the files within the given directory tree, with optional file extension filter. This version places each directory found on separate threads to improve large enumeration times. @param FoundFiles        Receives the files that matched the optional FileExtension filter, or all files if none was specified. @param Directory         The directory to iterate the contents of. This function explores subdirectories. @param FileExtension     The extension to filter by, in the form of TEXT(".ext"). If null or empty string, all files are found. @param AsyncExecution    The threaded execution method to use, i.e. on Task Graph, Thread Pool, or a new thread per directory. @param bFollowSymlinks   Whether symlinks to directories should be followed and enumerated, or added as a file.
- L262 _public prototype_ `virtual FFileStatData GetStatData(const TCHAR* FilenameOrDirectory) const = 0;` — Return the stat data for the given file or directory. Check the FFileStatData::bIsValid member before using the returned data. @param Filename          The filename or directory for the request. @return resulted stat data of the requested file or dir.
- L272 _public prototype_ `virtual int64 GetAllowedBytesToWriteThrottledStorage(const TCHAR* DestinationPath = nullptr) const = 0;` — Returns the number of bytes that are currently allowed to be written to throttled write storage (if the platform has such restrictions) @param DestinationPath	If specified, the file system can optionally take into account the destination of the file to determine the current limit @returns					The number of bytes that are allowed to be written to write throttled storage. If there is no limit, INT64_MAX is returned

#### class `BuildPatchServices::FFileSystemFactory`  
`class FFileSystemFactory`  
_L278-286_
- desc: A factory for creating an IFileSystem instance.
- L285 _public prototype_ `static IFileSystem* Create();` — Creates an implementation which wraps use of IFileManager, and implements additional functionality. @return the new IFileSystem instance created.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace BuildPatchServices`
- L24 _prototype_ `ENUM_CLASS_FLAGS(EAttributeFlags);` (scope `BuildPatchServices`)
- L35 _prototype_ `ENUM_CLASS_FLAGS(EWriteFlags);` (scope `BuildPatchServices`)
- L44 _prototype_ `ENUM_CLASS_FLAGS(EReadFlags);` (scope `BuildPatchServices`)
- L52 _prototype_ `TMap<FString, int64> ParallelGetFileSizes(const TSet<FString>& FilesToCheck, const FString& RootDirectory);` (scope `BuildPatchServices`) — A static helper function to parallelise retrieving file sizes for performance on large sets of files. @param FilesToCheck    The set of files to lookup the filesize for @param RootDirectory   The root directory of the files. Empty string can be passed if FilesToCheck has full file paths. @return a map of string from FilesToCheck to size on disk. INDEX_NONE if the file does not exist.

### `Source/Runtime/Online/BuildPatchServices/Private/Common/HttpManager.h` (Private)


#### class `BuildPatchServices::IHttpManager`  
`class IHttpManager`  
_L14-25_
- desc: The HTTP manager is used for classes which require HTTP access. Using this wrapper allows those classes to be easily testable.
- L17 _public prototype_ `virtual ~IHttpManager() = default;`
- L24 _public prototype_ `virtual TSharedRef<IHttpRequest, ESPMode::ThreadSafe> CreateRequest() = 0;` — Instantiates a new Http request for the current platform @return new Http request instance

#### class `BuildPatchServices::FHttpManagerFactory`  
`class FHttpManagerFactory`  
_L30-38_
- desc: A factory for creating an IHttpManager instance.
- L37 _public prototype_ `static IHttpManager* Create();` — Creates an implementation which wraps use of FHttpModule. @return the new IHttpManager instance created.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Common/SpeedRecorder.h` (Private)


#### class `BuildPatchServices::ISpeedRecorder`  
`class ISpeedRecorder`  
_L11-50_
- desc: A helper implementation for recording unit speeds.
- L29 _public prototype_ `virtual ~ISpeedRecorder() = default;`
- L35 _public prototype_ `virtual void AddRecord(const FRecord& Record) = 0;` — Adds a record to the recorder. @param Record    The record to add.
- L43 _public prototype_ `virtual double GetAverageSpeed(float Seconds, bool bIncludeInactiveTime = false) const = 0;` — Get the current average speed achieved over the last X seconds. @param Seconds   The time in seconds to take the reading over. Use TNumericLimits<float>::Max() to get the average over all readings. @param bIncludeInactiveTime   If True speed will be averaged over the entire Seconds period. Default is to only average over periods of active download within the Seconds period. @return the average speed over the past given seconds.
- L49 _public prototype_ `virtual double GetPeakSpeed() const = 0;` — Get the peak speed achieved so far. @return the peak speed achieved so far.

#### struct `BuildPatchServices::ISpeedRecorder::FRecord`  
`struct FRecord`  
_L17-26_
- desc: A struct for holding a single activity record.
- L20 _public prototype_ `FRecord();`
- L23 _public member_ `uint64 CyclesStart;`
- L24 _public member_ `uint64 CyclesEnd;`
- L25 _public member_ `uint64 Size;`

#### class `BuildPatchServices::FSpeedRecorderFactory`  
`class FSpeedRecorderFactory`  
_L55-59_
- desc: A factory for creating an ISpeedRecorder instance.
- L58 _public prototype_ `static ISpeedRecorder* Create();`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Common/StatsCollector.h` (Private)


#### enum `BuildPatchServices::EStatFormat`  
`enum class EStatFormat : uint8`  
_L8-20_
- L11 _public enumerator_ `Timer` — Using the AccumulateTimeBegin and End functions, measured in cycles
- L13 _public enumerator_ `DataSize` — Value measured in Bytes
- L15 _public enumerator_ `DataSpeed` — Value measured in Bytes per second
- L17 _public enumerator_ `Percentage` — Uses percentage printing, the returned stat should only be used with the percentage helpers
- L19 _public enumerator_ `Value` — Generic int64 output

#### class `BuildPatchServices::FStatsCollector`  
`class FStatsCollector`  
_L22-43_
- L25 _public typedef_ `typedef int64 FAtomicValue;`
- L28 _public prototype_ `virtual ~FStatsCollector() = default;`
- L29 _public prototype_ `virtual volatile FAtomicValue* CreateStat(const FString& Name, EStatFormat Type, FAtomicValue InitialValue = 0) = 0;`
- L30 _public prototype_ `virtual bool LogStats(float TimeBetweenLogs = 0.0f) = 0;`
- L33 _public prototype_ `static uint64 GetCycles();`
- L34 _public prototype_ `static double GetSeconds();`
- L35 _public prototype_ `static double CyclesToSeconds(uint64 Cycles);`
- L36 _public prototype_ `static uint64 SecondsToCycles(double Seconds);`
- L37 _public prototype_ `static void AccumulateTimeBegin(uint64& TempValue);`
- L38 _public prototype_ `static void AccumulateTimeEnd(volatile FAtomicValue* Stat, uint64& TempValue);`
- L39 _public prototype_ `static void Accumulate(volatile FAtomicValue* Stat, int64 Amount);`
- L40 _public prototype_ `static void Set(volatile FAtomicValue* Stat, int64 Value);`
- L41 _public prototype_ `static void SetAsPercentage(volatile FAtomicValue* Stat, double Value);`
- L42 _public prototype_ `static double GetAsPercentage(volatile FAtomicValue* Stat);`

#### class `BuildPatchServices::FStatsCollectorFactory`  
`class FStatsCollectorFactory`  
_L45-49_
- L48 _public prototype_ `static FStatsCollector* Create();`

#### class `BuildPatchServices::FStatsScopedCounter`  
`class FStatsScopedCounter`  
_L51-66_
- L54 _public function_ `FStatsScopedCounter(volatile FStatsCollector::FAtomicValue* InStat) : Stat(InStat)`
- L59 _public function_ `~FStatsScopedCounter()`
- L65 _private member_ `volatile FStatsCollector::FAtomicValue* Stat;`

#### class `BuildPatchServices::FStatsScopedTimer`  
`class FStatsScopedTimer`  
_L68-84_
- L71 _public function_ `FStatsScopedTimer(volatile FStatsCollector::FAtomicValue* InStat) : Stat(InStat)`
- L76 _public function_ `~FStatsScopedTimer()`
- L82 _private member_ `uint64 TempTime;`
- L83 _private member_ `volatile FStatsCollector::FAtomicValue* Stat;`

#### class `BuildPatchServices::FStatsParallelScopeTimer`  
`class FStatsParallelScopeTimer`  
_L86-118_
- L89 _public function_ `FStatsParallelScopeTimer(volatile FStatsCollector::FAtomicValue* InStaticTempValue, volatile FStatsCollector::FAtomicValue* InTimerStat, volatile FStatsCollector::FAtomicValue* InCounterStat) : TempTime(InStaticTempValue) , TimerStat(InTimerStat) , CounterStat(InCounterStat)`
- L100 _public function_ `~FStatsParallelScopeTimer()`
- L109 _public function_ `FStatsCollector::FAtomicValue GetCurrentTime() const`
- L115 _private member_ `volatile FStatsCollector::FAtomicValue* TempTime;`
- L116 _private member_ `volatile FStatsCollector::FAtomicValue* TimerStat;`
- L117 _private member_ `volatile FStatsCollector::FAtomicValue* CounterStat;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Compactify/PatchDataCompactifier.h` (Private)


#### class `BuildPatchServices::IPatchDataCompactifier`  
`class IPatchDataCompactifier`  
_L10-15_
- L13 _public prototype_ `virtual ~IPatchDataCompactifier() = default;`
- L14 _public prototype_ `virtual bool Run() = 0;`

#### class `BuildPatchServices::FPatchDataCompactifierFactory`  
`class FPatchDataCompactifierFactory`  
_L17-21_
- L20 _public prototype_ `static IPatchDataCompactifier* Create(const FCompactifyConfiguration& Configuration);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Core/AsyncHelpers.h` (Private)


#### struct `BuildPatchServices::TTaskSchedulerTraits`  
`template<typename TResultType> struct TTaskSchedulerTraits`  
_L112-115_
- L114 _public typedef_ `using FOnCompleteFunction = TFunction<void(TResultType)>;`
- L120 _public typedef_ `using FOnCompleteFunction = TFunction<void()>;`

#### struct `BuildPatchServices::TTaskSchedulerTraits`  
`template<> struct TTaskSchedulerTraits<void>`  
_L118-121_
- L114 _public typedef_ `using FOnCompleteFunction = TFunction<void(TResultType)>;`
- L120 _public typedef_ `using FOnCompleteFunction = TFunction<void()>;`

#### class `BuildPatchServices::FTaskScheduler`  
`template<typename TResultType, int32 CompileTimeMaxTasks = 64> class FTaskScheduler`  
_L129-233_
- desc: A helper class for scheduling a large amount of tasks on the thread pool while conserving event handles. The class itself should be called into entirely from one single thread only. For multiple threads with tasks, use separate FTaskScheduler instances.
- L132 _public typedef_ `using FOnCompleteCb = typename TTaskSchedulerTraits<TResultType>::FOnCompleteFunction;`
- L134 _public prototype_ `FTaskScheduler() = default;`
- L139 _public function_ `explicit FTaskScheduler(int32 InRuntimeLimitation): FTaskScheduler(EAsyncExecution::ThreadPool, InRuntimeLimitation)` — @param InRuntimeLimitation Runtime limitaion on a number of concurrent tasks
- L148 _public function_ `FTaskScheduler(EAsyncExecution InExecutionType, int32 InRuntimeLimitation = CompileTimeMaxTasks) : ExecutionType(InExecutionType) , MaxScheduledTasks(FMath::Clamp(InRuntimeLimitation, 1, CompileTimeMaxTasks))` — @param InRuntimeLimitation Runtime limitaion on a number of concurrent tasks @param InExecutionType	 The execution method to use, i.e. on Task Graph or in a separate thread.
- L161 _public function_ `void ScheduleTask(TFunction<TResultType()>&& Task, FOnCompleteCb&& OnComplete = nullptr)` — Adds a scheduled task to the queue. If the queue is full, will wait for a slot to become available, calling the OnComplete for the task being replaced. @param Task        The function to be ran asynchronously on the thread pool. @param OnComplete  The function to be called with completed task result. OnComplete will be executed from within ScheduleTask(..) or WaitAll().
- L194 _public function_ `void WaitAll()` — Waits and completes all remaining tasks in the queue. Must always be called to ensure that no OnComplete calls are missed.
- L207 _private function_ `template<typename TTaskResultType, int32 Tasks> void CompleteTask(FTaskScheduler<TTaskResultType, Tasks>& Scheduler, int32 Idx)`
- L217 _private function_ `template<int32 Tasks> void CompleteTask(FTaskScheduler<void, Tasks>& Scheduler, int32 Idx)`
- L228 _private member_ `EAsyncExecution ExecutionType = EAsyncExecution::ThreadPool;`
- L229 _private member_ `int32 MaxScheduledTasks = CompileTimeMaxTasks;`
- L230 _private member_ `TArray<TFuture<TResultType>, TFixedAllocator<CompileTimeMaxTasks>> TaskFutures;`
- L231 _private member_ `TArray<FOnCompleteCb, TFixedAllocator<CompileTimeMaxTasks>> TaskCompleteFuncs;`
- L232 _private member_ `int32 SlotSearchCount = 0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace BuildPatchServices`
- L15 _namespace_ `namespace AsyncHelpers` (scope `BuildPatchServices`)
- L18 _function_ `template<typename ResultType, typename... Args> static TFunction<void()> MakePromiseKeeper(const TSharedRef<TPromise<ResultType>, ESPMode::ThreadSafe>& Promise, const TFunction<ResultType(Args...)>& Function, Args... FuncArgs)` (scope `BuildPatchServices::AsyncHelpers`)
- L21 _function_ `` (scope `BuildPatchServices::AsyncHelpers::MakePromiseKeeper`)
- L27 _function_ `template<typename... Args> static TFunction<void()> MakePromiseKeeper(const TSharedRef<TPromise<void>, ESPMode::ThreadSafe>& Promise, const TFunction<void(Args...)>& Function, Args... FuncArgs)` (scope `BuildPatchServices::AsyncHelpers`)
- L37 _function_ `template<typename ResultType, typename... Args> static TFuture<ResultType> ExecuteOnGameThread(const TFunction<ResultType(Args...)>& Function, Args... FuncArgs)` (scope `BuildPatchServices::AsyncHelpers`)
- L53 _function_ `template<typename ResultType> static TFuture<ResultType> ExecuteOnGameThread(const TFunction<ResultType()>& Function)` (scope `BuildPatchServices::AsyncHelpers`)
- L69 _function_ `template<typename ResultType> static TFuture<ResultType> ExecuteOnCustomThread(const TFunction<ResultType()>& Function, TQueue<TFunction<void()>, EQueueMode::Spsc>& CustomThreadQueue)` (scope `BuildPatchServices::AsyncHelpers`)
- L88 _namespace_ `namespace AsyncHelpers` (scope `BuildPatchServices`)
- L97 _function_ `template<typename IntegerType> void LockFreePeak(volatile IntegerType* PeakValue, IntegerType NewSample)` (scope `BuildPatchServices::AsyncHelpers`) — LockFreePeak will set the destination value, to NewSample, if NewSample is higher. This works by spinning on InterlockedCompareExchange. For other usage examples see reference code in GenericPlatformAtomics.h @param PeakValue     The destination variable to set. @param NewSample     The sample to set with if higher.
- L235 _variable_ `constexpr int32 TaskCoresSchedulerThreadsLimitation = 128;` (scope `BuildPatchServices`)
- L238 _typedef_ `template<typename ResultType> using FTaskCoresScheduler = FTaskScheduler<ResultType, TaskCoresSchedulerThreadsLimitation>;` (scope `BuildPatchServices`)
- L241 _function_ `template<typename ResultType = void, int32 MaxThreads = TaskCoresSchedulerThreadsLimitation> static FTaskCoresScheduler<ResultType> CreateTaskSchedulerLimitedByCoresNumber(EAsyncExecution ExecutionType = EAsyncExecution::ThreadPool)` (scope `BuildPatchServices`)
- L247 _typedef_ `typedef FThreadSafeCounter64 FThreadSafeInt64;` (scope `BuildPatchServices`)
- L248 _typedef_ `typedef FThreadSafeCounter FThreadSafeInt32;` (scope `BuildPatchServices`)

### `Source/Runtime/Online/BuildPatchServices/Private/Core/BlockData.h` (Private)


#### struct `BuildPatchServices::TBlockData`  
`template<typename ElementType> struct TBlockData`  
_L12-128_
- L25 _public function_ `int32 GetDataCount() const`
- L30 _public function_ `uint32 GetAllocatedSize() const`
- L35 _public function_ `void CopyTo(TArray<ElementType>& OutData, const FBlockStructure& Structure) const`
- L50 _public function_ `void AddData(const FBlockStructure& NewStructure, const TArray<ElementType>& NewData)`
- L55 _public function_ `void AddData(const FBlockStructure& NewStructure, const ElementType* NewData, const int32 NewDataCount)`
- L101 _public function_ `void RemoveData(const FBlockStructure& Structure)`
- L126 _private member_ `FBlockStructure DataStructure;`
- L127 _private member_ `TArray<ElementType> Data;`

#### struct `BuildPatchServices::TBlockData::FBlockToCopy`  
`struct FBlockToCopy`  
_L15-21_
- L18 _public member_ `uint64 SortOffset;`
- L19 _public member_ `FBlockRange CopyBlockRange;`
- L20 _public member_ `const ElementType* DataPtr;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace BuildPatchServices`
- L91 _function_ `Algo::SortBy(BlocksToCopy, [] (const FBlockToCopy& BlockToCopy) { return BlockToCopy.SortOffset; });` (scope `BuildPatchServices::TBlockData::AddData`)

### `Source/Runtime/Online/BuildPatchServices/Private/Core/BlockRange.h` (Private)


#### struct `BuildPatchServices::FBlockRange`  
`struct FBlockRange`  
_L12-84_
- L15 _public function_ `uint64 GetFirst() const`
- L21 _public function_ `uint64 GetLast() const`
- L27 _public function_ `uint64 GetSize() const`
- L32 _public function_ `bool Overlaps(const FBlockRange& Other) const`
- L37 _public function_ `bool Touches(const FBlockRange& Other) const`
- L42 _public function_ `static FBlockRange FromFirstAndSize(uint64 InFirst, uint64 InSize)`
- L51 _public function_ `static FBlockRange FromFirstAndLast(uint64 InFirst, uint64 InLast)`
- L57 _public function_ `static FBlockRange FromIntersection(const FBlockRange& RangeA, const FBlockRange& RangeB)`
- L63 _public function_ `static FBlockRange FromMerge(const FBlockRange& RangeA, const FBlockRange& RangeB)`
- L75 _private function_ `FBlockRange() : First(0) , Size(0)`
- L82 _private member_ `uint64 First;`
- L83 _private member_ `uint64 Size;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace BuildPatchServices`
- L69 _function_ `friend bool operator==(const FBlockRange& Lhs, const FBlockRange& Rhs)` (scope `BuildPatchServices`)

### `Source/Runtime/Online/BuildPatchServices/Private/Core/BlockStructure.h` (Private)


#### struct `BuildPatchServices::FBlockEntry`  
`struct FBlockEntry`  
_L9-34_
- L13 _public prototype_ `FBlockEntry(uint64 InOffset, uint64 InSize);`
- L14 _public prototype_ `~FBlockEntry();`
- L16 _public prototype_ `uint64 GetOffset() const;`
- L17 _public prototype_ `uint64 GetSize() const;`
- L18 _public prototype_ `const FBlockEntry* GetNext() const;`
- L19 _public prototype_ `const FBlockEntry* GetPrevious() const;`
- L20 _public function_ `FBlockRange AsRange() const`
- L23 _private prototype_ `void InsertBefore(FBlockEntry* NewEntry, FBlockEntry** Head);`
- L24 _private prototype_ `void InsertAfter(FBlockEntry* NewEntry, FBlockEntry** Tail);`
- L25 _private prototype_ `void Unlink(FBlockEntry** Head, FBlockEntry** Tail);`
- L26 _private prototype_ `void Merge(uint64 InOffset, uint64 InSize);`
- L27 _private prototype_ `void Chop(uint64 InOffset, uint64 InSize, FBlockEntry** Head, FBlockEntry** Tail);`
- L30 _private member_ `uint64 Offset;`
- L31 _private member_ `uint64 Size;`
- L32 _private member_ `FBlockEntry* Prev;`
- L33 _private member_ `FBlockEntry* Next;`

#### class `BuildPatchServices::FBlockStructure`  
`class FBlockStructure`  
_L36-145_
- L39 _public prototype_ `FBlockStructure();`
- L40 _public prototype_ `FBlockStructure(uint64 Offset, uint64 Size);`
- L41 _public prototype_ `FBlockStructure(const FBlockStructure&);`
- L42 _public prototype_ `FBlockStructure(FBlockStructure&&);`
- L43 _public prototype_ `~FBlockStructure();`
- L44 _public prototype_ `FBlockStructure& operator=(const FBlockStructure&);`
- L45 _public prototype_ `FBlockStructure& operator=(FBlockStructure&&);`
- L47 _public prototype_ `const FBlockEntry* GetHead() const;`
- L48 _public prototype_ `const FBlockEntry* GetTail() const;`
- L53 _public prototype_ `void Empty();` — Empty the structure of all blocks.
- L62 _public prototype_ `void Add(uint64 Offset, uint64 Size, ESearchDir::Type SearchDir = ESearchDir::FromStart);` — Add a block to this structure. Any overlap will be merged, growing existing blocks where necessary. @param   Offset      The offset of the block. @param   Size        The size of the block. @param   SearchDir   The direction in which to search, default FromStart. If you know which is faster then specify this explicitly.
- L70 _public prototype_ `void Add(const FBlockRange& BlockRange, ESearchDir::Type SearchDir = ESearchDir::FromStart);` — Add a block to this structure. Any overlap will be merged, growing existing blocks where necessary. @param   BlockRange  The range of the block. @param   SearchDir   The direction in which to search, default FromStart. If you know which is faster then specify this explicitly.
- L78 _public prototype_ `void Add(const FBlockStructure& OtherStructure, ESearchDir::Type SearchDir = ESearchDir::FromStart);` — Add another structure to this structure. Any overlap will be merged, growing existing blocks where necessary. @param   OtherStructure      The other structure. @param   SearchDir           The direction in which to search, default FromStart. If you know which is faster then specify this explicitly.
- L87 _public prototype_ `void Remove(uint64 Offset, uint64 Size, ESearchDir::Type SearchDir = ESearchDir::FromStart);` — Remove a block from this structure. Any overlap will shrink existing blocks, or remove where necessary. @param   Offset      The offset of the block. @param   Size        The size of the block. @param   SearchDir   The direction in which to search, default FromStart. If you know which is faster then specify this explicitly.
- L95 _public prototype_ `void Remove(const FBlockRange& BlockRange, ESearchDir::Type SearchDir = ESearchDir::FromStart);` — Remove a block from this structure. Any overlap will shrink existing blocks, or remove where necessary. @param   BlockRange  The range of the block. @param   SearchDir   The direction in which to search, default FromStart. If you know which is faster then specify this explicitly.
- L103 _public prototype_ `void Remove(const FBlockStructure& OtherStructure, ESearchDir::Type SearchDir = ESearchDir::FromStart);` — Remove another structure from this structure. Any overlap will shrink existing blocks, or remove where necessary. @param   OtherStructure      The other structure. @param   SearchDir           The direction in which to search, default FromStart. If you know which is faster then specify this explicitly.
- L116 _public prototype_ `uint64 SelectSerialBytes(uint64 FirstByte, uint64 Count, FBlockStructure& OutputStructure) const;` — Starting from the nth byte in the structure, not including gaps, select a number of bytes into the provided structure. e.g for the structure [Offset, Size] MyStructure: [ 0,10]-[20,10]-[40,10] MyStructure.SelectSerialBytes(15, 10, SerialStruct); would result in SerialStruct representing [25, 5]-[40, 5] @param   FirstByte           The first byte to select, zero indexed. @param   Count               The number of bytes to provide. @param   OutputStructure     The structure receiving the blocks. @return the number of bytes selected.
- L128 _public prototype_ `FBlockStructure Intersect(const FBlockStructure& OtherStructure) const;` — Get the intersection of this block structure and another. e.g for the structures [Offset, Size] MyStructure: [ 0,10]-[20,10]-[40,10] and OtherStructure: [25,10]-[45,10]-[50,10] Intersection = MyStructure.Intersect(OtherStructure); would result in Intersection representing [25, 5]-[45, 5] @param   OtherStructure      The structure to intersect with. @return structure of blocks representing the overlap between this and other.
- L139 _public prototype_ `FString ToString(uint64 BlockCountLimit = 20) const;` — Get a string representation of this block structure, with ability to limit the number of blocks to stringify. The string is formatted "[Offset,Size]-[Offset,Size].. %d more." e.g. "[0,10]-[20,10]-[40,10]." "[0,10]-[20,10]-[40,10].. 300 more." @param   BlockCountLimit     The maximum number of blocks to include in the string. @return a string representation of this block structure.
- L142 _private member_ `FBlockEntry* Head;`
- L143 _private member_ `FBlockEntry* Tail;`
- L144 _private prototype_ `void CollectOverlaps(FBlockEntry* First, ESearchDir::Type SearchDir);`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace BuildPatchServices`
- L147 _namespace_ `namespace BlockStructureHelpers` (scope `BuildPatchServices`)
- L149 _prototype_ `uint64 CountSize(const FBlockStructure& Structure);` (scope `BuildPatchServices::BlockStructureHelpers`)
- L150 _prototype_ `bool HasIntersection(const FBlockStructure& ByteStructure, const FBlockStructure& Intersection);` (scope `BuildPatchServices::BlockStructureHelpers`)
- L151 _prototype_ `FBlockStructure SerializeIntersection(const FBlockStructure& ByteStructure, const FBlockStructure& Intersection);` (scope `BuildPatchServices::BlockStructureHelpers`)

### `Source/Runtime/Online/BuildPatchServices/Private/Core/Factory.h` (Private)


#### class `BuildPatchServices::TFactory`  
`template<typename Product, typename... DependencyTypes> class TFactory`  
_L33-37_
- desc: Templated factory interface declaration. This allows a system to declare the factory it requires a consumer to provide. For code readability, you should only use well defined types. For example, declare a config struct, use other IClassDependancies, or typedef a generic tye to name it. Example use: struct FClassConfig { uint32 RetryCount; uint32 TimeoutSeconds; }; typedef TArray<FString> FUriListToLoad; typedef TFactory<IClass, const FClassConfig&, FUriListToLoad, IUriHandlerClass*> IMyClassFactory; A consumer would then implement the factory: class FMyClassFactory : public IMyClassFactory { virtual IClass* Create(const FClassConfig& ClassConfig, FUriListToLoad UriListToLoad, IUriHandlerClass* UriHandlerClass) override { FClass* Class = new FClass(UriHandlerClass); Class->SetRetires(ClassConfig.RetryCount); Class->SetTimeout(ClassConfig.TimeoutSeconds); Class->LoadAll(UriListToLoad); return Class; } };
- L36 _public prototype_ `virtual Product* Create(DependencyTypes... Dependencies) = 0;`

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Core/FileSpan.h` (Private)


#### struct `BuildPatchServices::FFileSpan`  
`struct FFileSpan`  
_L9-92_
- L12 _public function_ `FFileSpan(const FString& InFilename, uint64 InSize, uint64 InStartIdx, bool InIsUnixExecutable, const FString& InSymlinkTarget) : Filename(InFilename) , Size(InSize) , StartIdx(InStartIdx) , IsUnixExecutable(InIsUnixExecutable) , SymlinkTarget(InSymlinkTarget)`
- L21 _public function_ `FFileSpan(const FFileSpan& CopyFrom) : Filename(CopyFrom.Filename) , Size(CopyFrom.Size) , StartIdx(CopyFrom.StartIdx) , MD5Hash(CopyFrom.MD5Hash) , SHA1Hash(CopyFrom.SHA1Hash) , SHA256Hash(CopyFrom.SHA256Hash) , MIMEType(CopyFrom.MIMEType) , IsUnixExecutable(CopyFrom.IsUnixExecutable) , SymlinkTarget(CopyFrom.SymlinkTarget)`
- L34 _public function_ `FFileSpan(FFileSpan&& MoveFrom) : Filename(MoveTemp(MoveFrom.Filename)) , Size(MoveTemp(MoveFrom.Size)) , StartIdx(MoveTemp(MoveFrom.StartIdx)) , MD5Hash(MoveTemp(MoveFrom.MD5Hash)) , SHA1Hash(MoveTemp(MoveFrom.SHA1Hash)) , SHA256Hash(MoveTemp(MoveFrom.SHA256Hash)) , MIMEType(MoveTemp(MoveFrom.MIMEType)) , IsUnixExecutable(MoveTemp(MoveFrom.IsUnixExecutable)) , SymlinkTarget(MoveTemp(MoveFrom.SymlinkTarget))`
- L47 _public function_ `FFileSpan() : Size(0) , StartIdx(0) , IsUnixExecutable(false)`
- L54 _public function_ `FORCEINLINE FFileSpan& operator=(const FFileSpan& CopyFrom)`
- L68 _public function_ `FORCEINLINE FFileSpan& operator=(FFileSpan&& MoveFrom)`
- L83 _public member_ `FString Filename;`
- L84 _public member_ `uint64 Size;`
- L85 _public member_ `uint64 StartIdx;`
- L86 _public member_ `FMD5Hash MD5Hash;`
- L87 _public member_ `FSHAHash SHA1Hash;`
- L88 _public member_ `FSHA256Signature SHA256Hash;`
- L89 _public member_ `FString MIMEType;`
- L90 _public member_ `bool IsUnixExecutable;`
- L91 _public member_ `FString SymlinkTarget;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Core/MeanValue.h` (Private)


#### class `BuildPatchServices::FMeanValue`  
`class FMeanValue`  
_L12-72_
- desc: A class that can be used to monitor the average value and standard deviation, without storing full history.
- L16 _public function_ `FMeanValue() : ReliabilityCount(10) , Count(0) , Total(0) , TotalSqs(0)`
- L23 _public function_ `FMeanValue(uint64 InReliabilityCount) : ReliabilityCount(InReliabilityCount) , Count(0) , Total(0) , TotalSqs(0)`
- L30 _public function_ `void Reset()`
- L37 _public function_ `bool IsReliable() const`
- L42 _public function_ `void GetValues(double& Mean, double& Std) const`
- L48 _public function_ `void AddSample(double Sample)`
- L56 _private function_ `double GetMean() const`
- L62 _private function_ `double GetStd(double Mean) const`
- L68 _private member_ `const uint64 ReliabilityCount;`
- L69 _private member_ `uint64 Count;`
- L70 _private member_ `double Total;`
- L71 _private member_ `double TotalSqs;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Core/Platform.h` (Private)


#### class `BuildPatchServices::IPlatform`  
`class IPlatform`  
_L15-40_
- desc: Class for wrapping platform functionality. We implement this using a template class, so that the class with platform dependency can easily be provided an implementation, and can still be nicely tested. Under normal circumstances, use FPlatform, which is a typedef below, and/or FPlatformFactory::Create.
- L18 _public prototype_ `virtual ~IPlatform() = default;`
- L28 _public prototype_ `virtual bool ExecElevatedProcess(const TCHAR* URL, const TCHAR* Params, int32* OutReturnCode) = 0;` — Executes a process as administrator, requesting elevation as necessary. This call blocks until the process has returned. @param URL             IN  The URL of the process to execute, typically the path to an executable file @param Params          IN  The params to pass to the invoked process @param OutReturnCode   OUT Will be set to the return code of the executed process @return true if the execution was successful.
- L34 _public prototype_ `virtual void Sleep(float Seconds) = 0;` — Sleep this thread for Seconds. 0.0 means release the current time slice to let other threads get some attention. @param Seconds         The time in seconds to sleep for.
- L39 _public prototype_ `virtual uint32 GetLastError() = 0;` — @return The error value for last platform error that occurred.

#### class `BuildPatchServices::TPlatform`  
`template <typename FPlatformProcessImpl, typename FPlatformMiscImpl> class TPlatform : public IPlatform`  
_L43-64_
- inherits: `IPlatform`
- L49 _public function_ `virtual bool ExecElevatedProcess(const TCHAR* URL, const TCHAR* Params, int32* OutReturnCode) override` — IPlatform interface begin.
- L54 _public function_ `virtual void Sleep(float Seconds) override`
- L59 _public function_ `virtual uint32 GetLastError() override`

#### class `BuildPatchServices::FPlatformFactory`  
`class FPlatformFactory`  
_L72-83_
- desc: A factory for creating an IPlatform instance.
- L79 _public function_ `static IPlatform* Create()` — Creates an implementation of IPlatform. @return the new IPlatform instance created.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace BuildPatchServices`
- L67 _typedef_ `typedef TPlatform<FPlatformProcess, FPlatformMisc> FPlatform;` (scope `BuildPatchServices`) — A typedef for the standard use platform type instantiation.

### `Source/Runtime/Online/BuildPatchServices/Private/Core/ProcessTimer.h` (Private)


#### class `BuildPatchServices::TProcessTimer`  
`template<typename FCyclesProvider, bool bThreadSafe = true> class TProcessTimer`  
_L15-160_
- desc: Class for wrapping timing functionality with pause feature. The class is thread safe. We template the dependency for cycles so that the class can be nicely tested. Under normal circumstances, use FProcessTimer, which is a typedef below.
- L21 _public function_ `TProcessTimer() : ThreadLock() , StartCycles(0) , Cycles(0) , bIsRunning(false) , bIsPaused(false)` — Default constructor zeros members.
- L34 _public function_ `double GetSeconds()` — Gets the currently accumulated time in seconds, accounting for any time paused. @return the seconds currently accumulated by the timer.
- L55 _public function_ `void Start()` — Start timing. Repeated calls before a Stop() are ignored.
- L78 _public function_ `void Stop()` — Stop timing and accumulate the recording. Repeated calls before a Start() are ignored.
- L102 _public function_ `void SetPause(bool bPause)` — Set whether the process being timed is paused. Automatically adjusts timer results for paused durations. @param bPause    Whether the process is currently paused.
- L133 _public function_ `void Reset()`
- L151 _private member_ `FCriticalSection ThreadLock;` — Thread lock for multi-threaded use.
- L153 _private member_ `uint64 StartCycles;` — The cycle count when we started timing.
- L155 _private member_ `uint64 Cycles;` — The total accumulated cycles between Start and Stop calls.
- L157 _private member_ `bool bIsRunning;` — Whether the timer is currently running.
- L159 _private member_ `bool bIsPaused;` — Whether the timer is in pause state.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace BuildPatchServices`
- L161 _typedef_ `typedef TProcessTimer<class FStatsCollector> FProcessTimer;` (scope `BuildPatchServices`)

### `Source/Runtime/Online/BuildPatchServices/Private/Core/RingBuffer.h` (Private)


#### class `TRingBuffer`  
`template< typename DataType > class TRingBuffer`  
_L8-165_
- L14 _public prototype_ `TRingBuffer(uint32 BufferDataSize);` — Constructor
- L19 _public prototype_ `~TRingBuffer();` — Default Destructor
- L24 _public prototype_ `void Empty();` — Clears memory and indexes
- L30 _public prototype_ `void Enqueue(const DataType& Val);` — Pushes a data word to the end of the FIFO. WILL OVERWRITE OLDEST if full. @param Val	The data word to push
- L37 _public prototype_ `void Enqueue(const DataType* ValBuf, const uint32& BufLen);` — Pushes a buffer of data words to the end of the FIFO. WILL OVERWRITE OLDEST if full. @param ValBuf		The buffer pointer @param BufLen		The length to copy
- L44 _public prototype_ `bool Dequeue(DataType& ValOut);` — Take the next data word from the FIFO buffer. @param OUT	ValOut	The variable to receive the data word @return	true if the buffer was not empty, false otherwise.
- L52 _public prototype_ `uint32 Dequeue(DataType* ValBuf, const uint32& BufLen);` — Take the next set of data words from the FIFO buffer. @param ValBuf		The buffer to receive the data @param BufLen		The number of words requested @return	the number of words actually copied
- L59 _public prototype_ `bool Peek(DataType& ValOut) const;` — Get the next data word from the FIFO buffer without removing it. @param OUT	ValOut	The variable to receive the data word @return	true if the buffer was not empty, false otherwise.
- L67 _public prototype_ `uint32 Peek(DataType* ValBuf, const uint32& BufLen) const;` — Get the next set of data words from the FIFO buffer without removing them. @param ValBuf		The buffer to receive the data @param BufLen		The number of words requested @return	the number of words actually copied
- L75 _public prototype_ `int32 SerialCompare(const DataType* SerialBuffer, uint32 CompareLen) const;` — Compare the memory in the FIFO to the memory in the given buffer @param SerialBuffer	The buffer containing data to compare @param CompareLen		The number of words to compare @return	< 0 if data < SerialBuffer.. 0 if data == SerialBuffer... > 0 if data > SerialBuffer
- L81 _public prototype_ `void GetShaHash(FSHAHash& OutHash) const;` — Get the SHA1 hash for the data currently in the FIFO @param OutHash	Receives the SHA hash
- L87 _public prototype_ `void Serialize(DataType* SerialBuffer) const;` — Serializes the internal buffer into the given buffer @param SerialBuffer	A preallocated buffer to copy data into
- L94 _public prototype_ `FORCEINLINE const DataType& operator[](const int32& Index) const;` — Square bracket operators for accessing data in the buffer by FIFO index. [0] returns the next entry in the FIFO that would get provided by Dequeue or Peek. @param Index	The index into the FIFO buffer @return	The data word
- L95 _public prototype_ `FORCEINLINE DataType& operator[](const int32& Index);`
- L101 _public prototype_ `FORCEINLINE const DataType& Top() const;` — Gets the last data word in the FIFO (i.e. most recently pushed). @return	The last data word
- L102 _public prototype_ `FORCEINLINE DataType& Top();`
- L108 _public prototype_ `FORCEINLINE const DataType& Bottom() const;` — Gets the first data word in the FIFO (i.e. oldest). @return	The first data word
- L109 _public prototype_ `FORCEINLINE DataType& Bottom();`
- L115 _public prototype_ `FORCEINLINE uint32 TopIndex() const;` — Gets the buffer index that the last data word is stored in. @return	The index of Top()
- L121 _public prototype_ `FORCEINLINE uint32 BottomIndex() const;` — Gets the buffer index that the first data word is stored in. @return	The index of Bottom()
- L127 _public prototype_ `FORCEINLINE uint32 NextIndex() const;` — Gets the buffer index that the next enqueued word will get stored in. @return	The index that the next enqueued word will have
- L133 _public prototype_ `FORCEINLINE uint32 RingDataSize() const;` — Gets the size of the data buffer. @return	Template arg BufferDataSize
- L139 _public prototype_ `FORCEINLINE uint32 RingDataUsage() const;` — Gets the number of words currently in the FIFO. @return	data size
- L145 _public prototype_ `FORCEINLINE uint64 TotalDataPushed() const;` — Gets the total number of words that have been pushed through this buffer since clearing @return	total length of data passed through
- L149 _private prototype_ `TRingBuffer() = delete;`
- L152 _private member_ `const uint32 BufferDataSize;` — Buffer size
- L155 _private member_ `DataType* Data;` — The data memory
- L158 _private member_ `uint32 NumDataAvailable;` — Value keeping track of free space
- L161 _private member_ `uint32 DataIndex;` — Value keeping track of the next data index
- L164 _private member_ `uint64 TotalNumDataPushed;` — Value to keep track of total amount of data Enqueued
- L170 _function_ `template< typename DataType > TRingBuffer< DataType >::TRingBuffer(uint32 InBufferDataSize) : BufferDataSize(InBufferDataSize)` — TRingBuffer implementation
- L178 _function_ `template< typename DataType > TRingBuffer< DataType >::~TRingBuffer()`
- L184 _function_ `template< typename DataType > void TRingBuffer< DataType >::Empty()`
- L193 _function_ `template< typename DataType > void TRingBuffer< DataType >::Enqueue(const DataType& Val)`
- L207 _function_ `template< typename DataType > void TRingBuffer< DataType >::Enqueue(const DataType* ValBuf, const uint32& BufLen)`
- L226 _function_ `template< typename DataType > bool TRingBuffer< DataType >::Dequeue(DataType& ValOut)`
- L240 _function_ `template< typename DataType > uint32 TRingBuffer< DataType >::Dequeue(DataType* ValBuf, const uint32& BufLen)`
- L248 _function_ `template< typename DataType > bool TRingBuffer< DataType >::Peek(DataType& ValOut) const`
- L262 _function_ `template< typename DataType > uint32 TRingBuffer< DataType >::Peek(DataType* ValBuf, const uint32& BufLen) const`
- L276 _function_ `template< typename DataType > int32 TRingBuffer< DataType >::SerialCompare(const DataType* SerialBuffer, uint32 CompareLen) const`
- L289 _function_ `template< typename DataType > void TRingBuffer< DataType >::GetShaHash(FSHAHash& OutHash) const`
- L303 _function_ `template< typename DataType > void TRingBuffer< DataType >::Serialize(DataType* SerialBuffer) const`
- L312 _function_ `template< typename DataType > FORCEINLINE const DataType& TRingBuffer< DataType >::operator[](const int32& Index) const`
- L318 _function_ `template< typename DataType > FORCEINLINE DataType& TRingBuffer< DataType >::operator[](const int32& Index)`
- L324 _function_ `template< typename DataType > FORCEINLINE const DataType& TRingBuffer< DataType >::Top() const`
- L330 _function_ `template< typename DataType > FORCEINLINE DataType& TRingBuffer< DataType >::Top()`
- L336 _function_ `template< typename DataType > FORCEINLINE const DataType& TRingBuffer< DataType >::Bottom() const`
- L342 _function_ `template< typename DataType > FORCEINLINE DataType& TRingBuffer< DataType >::Bottom()`
- L348 _function_ `template< typename DataType > FORCEINLINE uint32 TRingBuffer< DataType >::TopIndex() const`
- L354 _function_ `template< typename DataType > FORCEINLINE uint32 TRingBuffer< DataType >::BottomIndex() const`
- L360 _function_ `template< typename DataType > FORCEINLINE uint32 TRingBuffer< DataType >::NextIndex() const`
- L366 _function_ `template< typename DataType > FORCEINLINE uint32 TRingBuffer< DataType >::RingDataSize() const`
- L372 _function_ `template< typename DataType > FORCEINLINE uint32 TRingBuffer< DataType >::RingDataUsage() const`
- L378 _function_ `template< typename DataType > FORCEINLINE uint64 TRingBuffer< DataType >::TotalDataPushed() const`

### `Source/Runtime/Online/BuildPatchServices/Private/Data/ChunkData.h` (Private)


#### enum `BuildPatchServices::EChunkStorageFlags`  
`enum class EChunkStorageFlags : uint8`  
_L23-32_
- desc: Declares flags for chunk headers which specify storage types.
- L25 _public enumerator_ `RawData = 0x00`
- L28 _public enumerator_ `Compressed = 0x01` — Flag for compressed data.
- L31 _public enumerator_ `Encrypted = 0x02` — Flag for encrypted. If also compressed, decrypt first. Encryption will ruin compressibility.

#### enum `BuildPatchServices::EChunkHashFlags`  
`enum class EChunkHashFlags : uint8`  
_L38-50_
- desc: Declares flags for chunk headers which specify storage types.
- L40 _public enumerator_ `None = 0x00`
- L43 _public enumerator_ `RollingPoly64 = 0x01` — Flag for FRollingHash class used, stored in RollingHash on header.
- L46 _public enumerator_ `Sha1 = 0x02` — Flag for FSHA1 class used, stored in SHAHash on header.
- L49 _public enumerator_ `AesAuthTag = 0x02` — Flag for AES AuthTag being present in header header.

#### enum `BuildPatchServices::EChunkLoadResult`  
`enum class EChunkLoadResult : uint8`  
_L56-99_
- desc: Enum which describes success, or the reason for failure when loading a chunk.
- L58 _public enumerator_ `Success = 0`
- L61 _public enumerator_ `OpenFileFail` — Failed to open the file to load the chunk.
- L64 _public enumerator_ `BadArchive` — Could not serialize due to wrong archive type.
- L67 _public enumerator_ `CorruptHeader` — The header in the loaded chunk was invalid.
- L70 _public enumerator_ `IncorrectFileSize` — The expected file size in the header did not match the size of the file.
- L73 _public enumerator_ `UnsupportedStorage` — The storage type of the chunk is not one which we support.
- L76 _public enumerator_ `MissingHashInfo` — The hash information was missing.
- L79 _public enumerator_ `SerializationError` — The serialized data was not successfully understood.
- L82 _public enumerator_ `DecompressFailure` — The data was saved compressed but decompression failed.
- L85 _public enumerator_ `HashCheckFailed` — The expected data hash in the header did not match the hash of the data.
- L88 _public enumerator_ `FileSizeTooBig` — The size of the file is too big to handle
- L92 _public enumerator_ `MissingSecretKey` — If the decryption key necessary has not been provided, this result is given. It is up to the calling code to tell whether this is acceptable (expected preloading for example).
- L95 _public enumerator_ `DecryptionFailure` — The data was saved encrypted, and we had the secret key, but decryption failed.
- L98 _public enumerator_ `Aborted` — The operation was aborted.

#### enum `BuildPatchServices::EChunkSaveResult`  
`enum class EChunkSaveResult : uint8`  
_L109-129_
- desc: Enum which describes success, or the reason for failure when saving a chunk.
- L111 _public enumerator_ `Success = 0`
- L114 _public enumerator_ `FileCreateFail` — Failed to create the file for the chunk.
- L117 _public enumerator_ `BadArchive` — Could not serialize due to wrong archive type.
- L120 _public enumerator_ `SerializationError` — There was a serialization problem when writing to the chunk file.
- L123 _public enumerator_ `MissingEncryptionKey` — If we were asked to encrypted saved out chunks but did not get the key, we cannot save at all.
- L126 _public enumerator_ `EncryptionFail` — If the crypto interface returns an error.
- L128 _public enumerator_ `InvalidOrMax`

#### struct `BuildPatchServices::FChunkHeader`  
`struct FChunkHeader`  
_L139-171_
- desc: Declares a struct to store the info for a chunk header.
- L141 _public prototype_ `FChunkHeader();`
- L150 _public member_ `uint32 Version;` — The version of this header data.
- L152 _public member_ `uint32 HeaderSize;` — The size of this header.
- L154 _public member_ `FGuid Guid;` — The GUID for this data.
- L156 _public member_ `FGuid EncryptionSecretId;` — An ID that identifies the encryption secret required to decrypt this chunk. This is blank if the chunk is not encrypted.
- L158 _public member_ `uint32 DataSizeCompressed;` — The size of this data compressed.
- L160 _public member_ `uint32 DataSizeUncompressed;` — The size of this data uncompressed.
- L162 _public member_ `EChunkStorageFlags StoredAs;` — How the chunk data is stored.
- L164 _public member_ `EChunkHashFlags HashType;` — What type of hash we are using.
- L166 _public member_ `uint64 RollingHash;` — The FRollingHash hashed value for this chunk data.
- L168 _public member_ `FSHAHash SHAHash;` — The FSHA hashed value for this chunk data.
- L170 _public member_ `FAESAuthTag AESAuthTag;` — The 16 byte AuthTag space used for AES encryption, which is an additional integrity check value.

#### struct `BuildPatchServices::FChunkPart`  
`struct FChunkPart`  
_L212-247_
- desc: A data structure describing the part of a chunk used to construct a file
- L214 _public prototype_ `FChunkPart();`
- L215 _public prototype_ `FChunkPart(const FGuid& Guid, const uint32 Offset, const uint32 Size);`
- L227 _public function_ `bool IsPadding() const` — Get whether this chunk part refers to a special cased padding chunk. @return true if this chunk is padding only.
- L235 _public function_ `uint8 GetPaddingByte() const` — For padding chunks, returns the byte that is padded with. @return the byte used to pad data.
- L240 _public member_ `FGuid Guid;` — The GUID of the chunk containing this part.
- L242 _public member_ `uint32 Offset;` — The offset of the first byte into the chunk.
- L244 _public member_ `uint32 Size;` — The size of this part.
- L246 _public member_ `bool bChunkFromDelta = false;` — Determine whether the chunk is from delta file or manifest (default).

#### struct `BuildPatchServices::FFileChunkPart`  
`struct FFileChunkPart`  
_L252-261_
- desc: Declares a struct to store the info about a piece of a chunk that is inside a file
- L254 _public prototype_ `FFileChunkPart();`
- L256 _public member_ `FString Filename;` — The file containing this piece
- L258 _public member_ `uint64 FileOffset;` — The offset into the file of this piece
- L260 _public member_ `FChunkPart ChunkPart;` — The FChunkPart that can be salvaged from this file

#### struct `BuildPatchServices::FChunkInfo`  
`struct FChunkInfo`  
_L266-288_
- desc: A data structure describing a chunk file
- L269 _public member_ `FGuid Guid;` — The GUID for this data.
- L271 _public member_ `uint64 Hash = 0;` — The FRollingHash hashed value for this chunk data.
- L273 _public member_ `FSHAHash ShaHash;` — The FSHA hashed value for this chunk data.
- L275 _public member_ `uint8 GroupNumber = 0;` — The group number this chunk divides into.
- L277 _public member_ `uint32 DataSizeCompressed = 0;` — The size of this data compressed.
- L279 _public member_ `uint32 DataSizeUncompressed = 1048576;` — The size of this data uncompressed (also known as window size in older algorithms).
- L281 _public member_ `int64 FileSize = 0;` — The file download size for this chunk.
- L283 _public member_ `FGuid EncryptionSecretId;` — The ID of the encryption secret key used by this chunk.
- L285 _public member_ `FAESAuthTag AESAuthTag;` — The 16 byte AuthTag space used for AES encryption, which is an additional integrity check value.
- L287 _public member_ `bool bChunkFromDelta = false;` — Determine whether the chunk is from delta file or manifest (default).

#### struct `BuildPatchServices::FChunkLocation`  
`struct FChunkLocation`  
_L293-298_
- desc: Declares a struct holding variables to identify chunk and location.
- L295 _public member_ `FGuid ChunkId;`
- L296 _public member_ `uint64 ByteStart;`
- L297 _public member_ `uint32 ByteSize;`

#### struct `BuildPatchServices::FChunkDatabaseHeader`  
`struct FChunkDatabaseHeader`  
_L303-321_
- desc: Declares a struct to store the info for a chunk database header.
- L305 _public prototype_ `FChunkDatabaseHeader();`
- L314 _public member_ `uint32 Version;` — The version of this header data.
- L316 _public member_ `uint32 HeaderSize;` — The size of this header.
- L318 _public member_ `uint64 DataSize;` — The size of the following data.
- L320 _public member_ `TArray<FChunkLocation> Contents;` — The table of contents.

#### class `BuildPatchServices::IChunkDataAccess`  
`class IChunkDataAccess`  
_L326-343_
- desc: An interface providing locked access to chunk data.
- L329 _public prototype_ `virtual ~IChunkDataAccess() = default;`
- L336 _public prototype_ `virtual void GetDataLock(const uint8** OutChunkData, const FChunkHeader** OutChunkHeader) const = 0;` — Gets the thread lock on the data, must call ReleaseDataLock when finished with data. @param OutChunkData      Receives the pointer to chunk data. @param OutChunkHeader    Receives the pointer to header.
- L337 _public prototype_ `virtual void GetDataLock( uint8** OutChunkData, FChunkHeader** OutChunkHeader) = 0;`
- L342 _public prototype_ `virtual void ReleaseDataLock() const = 0;` — Releases access to the data to allow other threads to use.

#### class `BuildPatchServices::FChunkDataAccessFactory`  
`class FChunkDataAccessFactory`  
_L348-357_
- desc: A factory for creating an IChunkDataAccess instance with allocated data.
- L356 _public prototype_ `static IChunkDataAccess* Create(uint32 DataSize);` — Creates a chunk data access class. @param DataSize  The size of the data to be held in bytes. @return the new IChunkDataAccess instance created.

#### struct `BuildPatchServices::FScopeLockedChunkData`  
`struct FScopeLockedChunkData`  
_L363-386_
- desc: Provides simple access to the header and data in an IChunkDataAccess, whilst obtaining and releasing the data lock within the current scope.
- L366 _public prototype_ `FScopeLockedChunkData(IChunkDataAccess* ChunkDataAccess);`
- L367 _public prototype_ `~FScopeLockedChunkData();`
- L372 _public prototype_ `FChunkHeader* GetHeader() const;` — @return the pointer to the chunk header.
- L377 _public prototype_ `uint8* GetData() const;` — @return the pointer to the chunk data.
- L381 _private member_ `IChunkDataAccess* ChunkDataAccess;` — The provided IChunkDataAccess which we lock and release.
- L383 _private member_ `FChunkHeader* ChunkHeader;` — Pointer to the header data.
- L385 _private member_ `uint8* ChunkData;` — Pointer to the chunk data.

#### class `BuildPatchServices::IChunkDataSerialization`  
`class IChunkDataSerialization`  
_L391-464_
- desc: An interface providing serialization for chunk data.
- L394 _public prototype_ `virtual ~IChunkDataSerialization() = default;`
- L402 _public prototype_ `virtual IChunkDataAccess* LoadFromFile(const FString& Filename, EChunkLoadResult& OutLoadResult) const = 0;` — Loads a chunk from a file on disk or network. @param Filename          The full file path to the file. @param OutLoadResult     Receives the result, indicating the error reason if return value is nullptr. @return ptr to an allocated IChunkDataAccess holding the data, nullptr if failed to load.
- L410 _public prototype_ `virtual IChunkDataAccess* LoadFromMemory(const TArray<uint8>& Memory, EChunkLoadResult& OutLoadResult) const = 0;` — Loads a chunk from memory. @param Memory            The memory array. @param OutLoadResult     Receives the result, indicating the error reason if return value is nullptr. @return ptr to an allocated IChunkDataAccess holding the data, nullptr if failed to load.
- L418 _public prototype_ `virtual IChunkDataAccess* LoadFromArchive(FArchive& Archive, EChunkLoadResult& OutLoadResult) const = 0;` — Loads a chunk from an archive. @param Archive           The archive. @param OutLoadResult     Receives the result, indicating the error reason if return value is nullptr. @return ptr to an allocated IChunkDataAccess holding the data, nullptr if failed to load.
- L426 _public prototype_ `virtual EChunkSaveResult SaveToFile(const FString& Filename, IChunkDataAccess* ChunkDataAccess) const = 0;` — Saves a chunk to a file on disk or network. @param Filename          The full file path to the file. @param ChunkDataAccess   Ptr to the chunk data to save. The header will be updated with relevant changes. @return the result, EChunkSaveResult::Success if successful.
- L434 _public prototype_ `virtual EChunkSaveResult SaveToMemory(TArray<uint8>& Memory, IChunkDataAccess* ChunkDataAccess) const = 0;` — Saves a chunk to memory. @param Memory            The memory array. @param ChunkDataAccess   Ptr to the chunk data to save. The header will be updated with relevant changes. @return the result, EChunkSaveResult::Success if successful.
- L442 _public prototype_ `virtual EChunkSaveResult SaveToArchive(FArchive& Archive, IChunkDataAccess* ChunkDataAccess) const = 0;` — Saves a chunk to an archive. @param Archive           The archive. @param ChunkDataAccess   Ptr to the chunk data to save. The header will be updated with relevant changes. @return the result, EChunkSaveResult::Success if successful.
- L445 _public function_ `virtual EChunkSaveResult SaveToArchiveUncompressed(FArchive& Archive, IChunkDataAccess* ChunkDataAccess) const` — In performance sensitive situations, can request the serializer to save uncompressed if implemented
- L452 _public prototype_ `virtual bool ValidateAndRead(FArchive& InArchive, FMutableMemoryView InDestinationBuffer, FChunkHeader& OutHeader, FUniqueBuffer& OutCompressedBuffer) const = 0;` — Read the header from the archive, make sure it's sane, and set up to decompress/hash in a separate call. This is to allow the IO to be on a separate thread from decompression/hashing.
- L455 _public prototype_ `virtual bool DecompressAndDecryptValidatedRead(const FChunkHeader& InHeader, FMutableMemoryView InDestionationBuffer, const FUniqueBuffer& InCompressedBuffer) const = 0;` — Take the output of ValidateAndRead and process it in to an actual output chunk.
- L463 _public prototype_ `virtual bool InjectShaToChunkData(TArray<uint8>& Memory, const FSHAHash& ShaHashData) const = 0;` — Injects an SHA hash for the data into the structure of a serialized chunk. @param Memory            The memory array containing the serialized chunk. @param ShaHashData       The SHA hash to inject. @return true if ShaHashData was successfully injected into memory, false otherwise.

#### struct `BuildPatchServices::FChunkDataSerializationConfig`  
`struct FChunkDataSerializationConfig`  
_L466-472_
- L468 _public member_ `EFeatureLevel FeatureLevel = EFeatureLevel::Latest;`
- L469 _public member_ `TMap<FGuid,TArray<uint8>> EncryptionSecrets;`
- L470 _public member_ `FGuid WriteEncryptionSecretId;`

#### class `BuildPatchServices::FChunkDataSerializationFactory`  
`class FChunkDataSerializationFactory`  
_L477-481_
- desc: A factory for creating an IChunkDataSerialization instance.
- L480 _public prototype_ `static IChunkDataSerialization* Create(IFileSystem* FileSystem, ICrypto* Crypto, FChunkDataSerializationConfig Config);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace BuildPatchServices`
- L18 _variable_ `static const uint32 LegacyFixedChunkWindow = 1024 * 1024;` (scope `BuildPatchServices`) — Constant for the legacy fixed chunk window size, which was 1MiB.
- L33 _prototype_ `ENUM_CLASS_FLAGS(EChunkStorageFlags);` (scope `BuildPatchServices`)
- L51 _prototype_ `ENUM_CLASS_FLAGS(EChunkHashFlags);` (scope `BuildPatchServices`)
- L104 _prototype_ `const TCHAR* ToString(const EChunkLoadResult& ChunkLoadResult);` (scope `BuildPatchServices`) — A ToString implementation for EChunkLoadResult.
- L134 _prototype_ `const TCHAR* ToString(const EChunkSaveResult& ChunkSaveResult);` (scope `BuildPatchServices`) — A ToString implementation for EChunkSaveResult.
- L174 _namespace_ `namespace PaddingChunk` (scope `BuildPatchServices`)
- L177 _variable_ `static const int32 ChunkIdA = 0x00000001;` (scope `BuildPatchServices::PaddingChunk`) — The A, B, and C components of a chunk Guid indicating that this is a padding chunk. D would be the actual byte padded with.
- L178 _variable_ `static const int32 ChunkIdB = 0x00000000;` (scope `BuildPatchServices::PaddingChunk`)
- L179 _variable_ `static const int32 ChunkIdC = 0x00000000;` (scope `BuildPatchServices::PaddingChunk`)
- L181 _variable_ `static const uint32 ChunkSize = LegacyFixedChunkWindow;` (scope `BuildPatchServices::PaddingChunk`) — The size of the chunk we use to save out, which would allow a legacy client to actually use one.
- L186 _function_ `FORCEINLINE bool IsPadding(const FGuid& Guid)` (scope `BuildPatchServices::PaddingChunk`) — Get whether this chunk part refers to a special cased padding chunk. @return true if this chunk is padding only.
- L194 _function_ `FORCEINLINE uint8 GetPaddingByte(const FGuid& Guid)` (scope `BuildPatchServices::PaddingChunk`) — For padding chunks, returns the byte that is padded with. @return the byte used to pad data.
- L203 _function_ `FORCEINLINE FGuid MakePaddingGuid(uint8 Byte)` (scope `BuildPatchServices::PaddingChunk`) — For padding chunks, returns the byte that is padded with. @return the byte used to pad data.

### `Source/Runtime/Online/BuildPatchServices/Private/Data/ManifestData.h` (Private)


#### enum `BuildPatchServices::EManifestStorageFlags`  
`enum class EManifestStorageFlags : uint8`  
_L21-30_
- desc: Declares flags for manifest headers which specify storage types.
- L23 _public enumerator_ `RawData = 0x00`
- L26 _public enumerator_ `Compressed = 0x01` — Flag for compressed data.
- L29 _public enumerator_ `Encrypted = 0x02` — Flag for encrypted. If also compressed, decrypt first. Encryption will ruin compressibility.

#### struct `BuildPatchServices::FManifestHeader`  
`struct FManifestHeader`  
_L63-89_
- L65 _public prototype_ `FManifestHeader();`
- L74 _public member_ `EFeatureLevel Version;` — The version of this header and manifest data format, driven by the feature level.
- L76 _public member_ `uint32 HeaderSize;` — The size of this header.
- L78 _public member_ `uint32 DataSizeCompressed;` — The size of this data compressed.
- L80 _public member_ `uint32 DataSizeUncompressed;` — The size of this data uncompressed.
- L82 _public member_ `EManifestStorageFlags StoredAs;` — How the chunk data is stored.
- L84 _public member_ `FSHAHash SHAHash;` — The SHA1 hash for the manifest data that follows.
- L87 _public member_ `FGuid EncryptionSecretId;` — An ID that identifies the encryption secret required to decrypt certain manifest fields. Without having the associated key, only chunk use, file hashes, and sizes can be understood.
- L88 _public member_ `uint8 EncryptionAuthTag[AES256_GCM_AuthTagSizeInBytes];`

#### struct `BuildPatchServices::FManifestMeta`  
`struct FManifestMeta`  
_L91-137_
- L93 _public prototype_ `FManifestMeta();`
- L102 _public member_ `EFeatureLevel FeatureLevel;` — The feature level support this build was created with, regardless of the serialised format.
- L104 _public member_ `bool bIsFileData;` — Whether this is a legacy 'nochunks' build.
- L106 _public member_ `uint32 AppID;` — The app id provided at generation.
- L108 _public member_ `FString AppName;` — The app name string provided at generation.
- L110 _public member_ `FString BuildVersion;` — The build version string provided at generation.
- L113 _public member_ `FString LaunchExe;` — The file in this manifest designated the application executable of the build. Can be an obfuscated string for encrypted manifests.
- L116 _public member_ `FString LaunchCommand;` — The command line required when launching the application executable. Can be an obfuscated string for encrypted manifests.
- L119 _public member_ `TSet<FString> PrereqIds;` — The set of prerequisite ids for dependencies that this build's prerequisite installer will apply. Can be an obfuscated strings for encrypted manifests.
- L122 _public member_ `FString PrereqName;` — A display string for the prerequisite provided at generation. Can be an obfuscated string for encrypted manifests.
- L125 _public member_ `FString PrereqPath;` — The file in this manifest designated the launch executable of the prerequisite installer. Can be an obfuscated string for encrypted manifests.
- L128 _public member_ `FString PrereqArgs;` — The command line required when launching the prerequisite installer. Can be an obfuscated string for encrypted manifests.
- L131 _public member_ `FString UninstallActionPath;` — The path to the uninstall custom action executable. Can be an obfuscated string for encrypted manifests.
- L134 _public member_ `FString UninstallActionArgs;` — The arguments to the uninstall custom action executable. Can be an obfuscated string for encrypted manifests.
- L136 _public member_ `FString BuildId;` — A unique build id generated at original chunking time to identify an exact build.

#### struct `BuildPatchServices::FChunkDataList`  
`struct FChunkDataList`  
_L139-153_
- L141 _public prototype_ `FChunkDataList();`
- L150 _public member_ `EFeatureLevel FeatureLevel;` — The feature level support this build was created with, regardless of the serialised format.
- L152 _public member_ `TArray<FChunkInfo> ChunkList;` — The list of chunks.

#### struct `BuildPatchServices::FFileManifest`  
`struct FFileManifest`  
_L155-180_
- L157 _public prototype_ `FFileManifest();`
- L160 _public member_ `FString Filename;` — The build relative filename. Can be an obfuscated string for encrypted manifests.
- L163 _public member_ `FString SymlinkTarget;` — Whether this is a symlink to another file. Can be an obfuscated string for encrypted manifests.
- L165 _public member_ `FMD5Hash MD5Hash;` — The file MD5.
- L167 _public member_ `FSHAHash SHA1Hash;` — The file SHA1.
- L169 _public member_ `FSHA256Signature SHA256Hash;` — The file SHA256.
- L171 _public member_ `FString MIMEType;` — The calculated MIME type for the file.
- L173 _public member_ `EFileMetaFlags FileMetaFlags;` — The flags for this file.
- L175 _public member_ `TArray<FString> InstallTags;` — The install tags for this file.
- L177 _public member_ `TArray<FChunkPart> ChunkParts;` — The list of chunk parts to stitch.
- L179 _public member_ `uint64 FileSize;` — The size of this file.

#### struct `BuildPatchServices::FFileManifestList`  
`struct FFileManifestList`  
_L182-200_
- L184 _public prototype_ `FFileManifestList();`
- L193 _public member_ `EFeatureLevel FeatureLevel;` — The feature level support this build was created with, regardless of the serialised format.
- L197 _public prototype_ `void OnPostLoad();` — Helper to sort and calculate file sizes after loading.
- L199 _public member_ `TArray<FFileManifest> FileList;` — The list of files.

#### struct `BuildPatchServices::FCustomFields`  
`struct FCustomFields`  
_L202-216_
- L204 _public prototype_ `FCustomFields();`
- L213 _public member_ `EFeatureLevel FeatureLevel;` — The feature level support this build was created with, regardless of the serialised format.
- L215 _public member_ `TMap<FString, FString> Fields;` — The map of field name to field data.

#### struct `BuildPatchServices::FEncryptedData`  
`struct FEncryptedData`  
_L218-232_
- L220 _public prototype_ `FEncryptedData();`
- L229 _public member_ `EFeatureLevel FeatureLevel;` — The feature level support this build was created with, regardless of the serialised format.
- L231 _public member_ `TArray<uint8> Data;` — The raw ciphertext.

#### class `BuildPatchServices::FManifestData`  
`class FManifestData`  
_L234-239_
- L237 _public prototype_ `static void Init();`
- L238 _public prototype_ `static bool Serialize(FArchive& Ar, FBuildPatchAppManifest& AppManifest, BuildPatchServices::EFeatureLevel SaveFormat = BuildPatchServices::EFeatureLevel::Latest);`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace BuildPatchServices`
- L31 _prototype_ `ENUM_CLASS_FLAGS(EManifestStorageFlags);` (scope `BuildPatchServices`)
- L36 _namespace_ `namespace ManifestVersionHelpers` (scope `BuildPatchServices`)
- L43 _prototype_ `const TCHAR* GetChunkSubdir(EFeatureLevel FeatureLevel);` (scope `BuildPatchServices::ManifestVersionHelpers`) — Get the chunk subdirectory for used for a specific manifest version, e.g. Chunks, ChunksV2 etc. @param FeatureLevel   The version of the manifest. @return the subdirectory name that this manifest version will access.
- L50 _prototype_ `const TCHAR* GetFileSubdir(EFeatureLevel FeatureLevel);` (scope `BuildPatchServices::ManifestVersionHelpers`) — Get the file data subdirectory for used for a specific manifest version, e.g. Files, FilesV2 etc. @param FeatureLevel   The version of the manifest. @return the subdirectory name that this manifest version will access.
- L53 _namespace_ `namespace ManifestDataHelpers` (scope `BuildPatchServices`)
- L55 _prototype_ `EManifestStorageFlags CompressManifestMemory(TArray<uint8>& Data);` (scope `BuildPatchServices::ManifestDataHelpers`)
- L56 _prototype_ `bool UncompressManifestMemory(TArray<uint8>& Data, uint32 DataSizeUncompressed);` (scope `BuildPatchServices::ManifestDataHelpers`)
- L57 _prototype_ `FString ObfuscateString(const FString& String);` (scope `BuildPatchServices::ManifestDataHelpers`)
- L58 _prototype_ `TArray<FString> ObfuscateStrings(const TArray<FString>& String);` (scope `BuildPatchServices::ManifestDataHelpers`)
- L59 _prototype_ `TSet<FString> ObfuscateStrings(const TSet<FString>& Strings);` (scope `BuildPatchServices::ManifestDataHelpers`)
- L242 _prototype_ `ENUM_RANGE_BY_FIRST_AND_LAST(BuildPatchServices::EFeatureLevel, BuildPatchServices::EFeatureLevel::Original, BuildPatchServices::EFeatureLevel::Latest);`

### `Source/Runtime/Online/BuildPatchServices/Private/Data/ManifestUObject.h` (Private)


#### struct `FCustomFieldData`  
`struct FCustomFieldData`  
_L23-36_
- reflection: `USTRUCT()`
- L27 _public prototype_ `FCustomFieldData();`
- L28 _public prototype_ `FCustomFieldData(const FString& Key, const FString& Value);`
- L32 _public member_ `FString Key;` — `UPROPERTY()`
- L35 _public member_ `FString Value;` — `UPROPERTY()`

#### struct `FSHAHashData`  
`struct FSHAHashData`  
_L39-49_
- reflection: `USTRUCT()`
- L43 _public prototype_ `FSHAHashData();`
- L47 _public member_ `uint8 Hash[FSHA1::DigestSize];` — `UPROPERTY()`

#### struct `FChunkInfoData`  
`struct FChunkInfoData`  
_L53-74_
- reflection: `USTRUCT()`
- L57 _public prototype_ `FChunkInfoData();`
- L61 _public member_ `FGuid Guid;` — `UPROPERTY()`
- L64 _public member_ `uint64 Hash;` — `UPROPERTY()`
- L67 _public member_ `FSHAHashData ShaHash;` — `UPROPERTY()`
- L70 _public member_ `int64 FileSize;` — `UPROPERTY()`
- L73 _public member_ `uint8 GroupNumber;` — `UPROPERTY()`

#### struct `FChunkPartData`  
`struct FChunkPartData`  
_L77-92_
- reflection: `USTRUCT()`
- L81 _public prototype_ `FChunkPartData();`
- L85 _public member_ `FGuid Guid;` — `UPROPERTY()`
- L88 _public member_ `uint32 Offset;` — `UPROPERTY()`
- L91 _public member_ `uint32 Size;` — `UPROPERTY()`

#### struct `FFileManifestData`  
`struct FFileManifestData`  
_L95-125_
- reflection: `USTRUCT()`
- L99 _public prototype_ `FFileManifestData();`
- L103 _public member_ `FString Filename;` — `UPROPERTY()`
- L106 _public member_ `FSHAHashData FileHash;` — `UPROPERTY()`
- L109 _public member_ `TArray<FChunkPartData> FileChunkParts;` — `UPROPERTY()`
- L112 _public member_ `TArray<FString> InstallTags;` — `UPROPERTY()`
- L115 _public member_ `bool bIsUnixExecutable;` — `UPROPERTY()`
- L118 _public member_ `FString SymlinkTarget;` — `UPROPERTY()`
- L121 _public member_ `bool bIsReadOnly;` — `UPROPERTY()`
- L124 _public member_ `bool bIsCompressed;` — `UPROPERTY()`

#### class `UBuildPatchManifest`  
`class UBuildPatchManifest : public UObject`  
_L128-176_
- reflection: `UCLASS()`
- inherits: `UObject`
- L132 _public prototype_ `~UBuildPatchManifest();`
- L136 _public member_ `uint8 ManifestFileVersion;` — `UPROPERTY()`
- L139 _public member_ `bool bIsFileData;` — `UPROPERTY()`
- L142 _public member_ `uint32 AppID;` — `UPROPERTY()`
- L145 _public member_ `FString AppName;` — `UPROPERTY()`
- L148 _public member_ `FString BuildVersion;` — `UPROPERTY()`
- L151 _public member_ `FString LaunchExe;` — `UPROPERTY()`
- L154 _public member_ `FString LaunchCommand;` — `UPROPERTY()`
- L157 _public member_ `TSet<FString> PrereqIds;` — `UPROPERTY()`
- L160 _public member_ `FString PrereqName;` — `UPROPERTY()`
- L163 _public member_ `FString PrereqPath;` — `UPROPERTY()`
- L166 _public member_ `FString PrereqArgs;` — `UPROPERTY()`
- L169 _public member_ `TArray<FFileManifestData> FileManifestList;` — `UPROPERTY()`
- L172 _public member_ `TArray<FChunkInfoData> ChunkList;` — `UPROPERTY()`
- L175 _public member_ `TArray<FCustomFieldData> CustomFields;` — `UPROPERTY()`

#### class `FManifestUObject`  
`class FManifestUObject`  
_L178-188_
- L181 _public prototype_ `static void Init();`
- L182 _public prototype_ `static bool LoadFromMemory(const TArray<uint8>& DataInput, FBuildPatchAppManifest& AppManifest);`
- L183 _public prototype_ `static bool SaveToArchive(FArchive& Ar, const FBuildPatchAppManifest& AppManifest);`
- L186 _private prototype_ `static bool LoadInternal(FArchive& Ar, FBuildPatchAppManifest& AppManifest);`
- L187 _private prototype_ `static bool SaveInternal(FArchive& Ar, const FBuildPatchAppManifest& AppManifest);`

#### Free symbols / members of external scopes

- L17 _macro_ `#define BUILDPATCHSERVICES_NOUOBJECT 0`

### `Source/Runtime/Online/BuildPatchServices/Private/Diffing/DiffManifests.h` (Private)


#### class `BuildPatchServices::IDiffManifests`  
`class IDiffManifests`  
_L10-15_
- L13 _public prototype_ `virtual ~IDiffManifests()= default;`
- L14 _public prototype_ `virtual bool Run() = 0;`

#### class `BuildPatchServices::FDiffManifestsFactory`  
`class FDiffManifestsFactory`  
_L17-21_
- L20 _public prototype_ `static IDiffManifests* Create(const FDiffManifestsConfiguration& Configuration);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Enumeration/PatchDataEnumeration.h` (Private)


#### class `BuildPatchServices::FPatchDataEnumerationFactory`  
`class FPatchDataEnumerationFactory`  
_L13-17_
- L16 _public prototype_ `static IPatchDataEnumeration* Create(FPatchDataEnumerationConfiguration Configuration);`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDataEnumeration, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDataEnumeration, Log, All);`
- L11 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Generation/BuildDataVerifier.h` (Private)


#### class `BuildPatchServices::FBuildDataVerifier`  
`class FBuildDataVerifier`  
_L21-369_
- desc: This is a build data verification class that is not used for production code, but can be used to verify scan and other processing results to help test code while in development.
- L24 _public function_ `FBuildDataVerifier(IFileSystem* InFileSystem, IChunkDataSerialization* InChunkDataSerialization, const FString& InBuildLocation, const FString& InOtherBuildLocation, const FString& InCloudDir, const FBuildPatchAppManifest& InManifest, const FBuildPatchAppManifest& InOtherManifest) : FileSystem(InFileSystem) , ChunkDataSerialization(InChunkDataSerialization) , BuildLocation(InBuildLocation) , OtherBuildLocation(InOtherBuildLocation) , CloudDir(InCloudDir) , Manifest(InManifest) , OtherManifest(InOtherManifest) , BuildFiles(ListHelpers::GetFileList(Manifest)) , OtherBuildFiles(ListHelpers::GetFileList(OtherManifest))`
- L37 _public function_ `FArchive* LoadFile(const FString& BuildFile, bool bUseOther)`
- L49 _public function_ `void GetChunkData(const FChunkPart& ChunkPart, TArray<uint8>& OutData, FParallelChunkWriterSummaries* ChunkWriterSummaries = nullptr)`
- L78 _public function_ `void GetFileData(const FString& BuildFilename, const FBlockRange& BlockRange, TArray<uint8>& OutData, bool bUseOther = false)`
- L88 _public function_ `void GetBuildData(const FBlockRange& BlockRange, TArray<uint8>& OutData, bool bUseOther = false)`
- L123 _public function_ `void GetBuildData(const FBlockStructure& BlockStructure, TArray<uint8>& OutData, bool bUseOther = false)`
- L136 _public function_ `void CheckDataAndAssert(const FBlockStructure& BlockStructure, const uint8* Data)`
- L147 _public function_ `void CheckDataAndAssert(const FBlockStructure& BlockStructure, const FSHAHash& SHAHash)`
- L158 _public function_ `void CheckDataAndAssert(const IDeltaChunkEnumeration* DeltaChunkEnumeration, const FChunkBuildReference& ChunkBuildReference)`
- L179 _public function_ `void CheckDataAndAssert(const FBlockStructure& BlockStructure, const FBlockStructure& OtherBlockStructure)`
- L193 _public function_ `void CheckDataAndAssert(const FFileManifestList& FileManifestList, FParallelChunkWriterSummaries* ChunkWriterSummaries = nullptr)`
- L221 _public function_ `void CheckDataAndAssert(const FBlockStructure& BlockStructure, const FChunkPart& ChunkPart, bool bUseOther = false)`
- L242 _public function_ `void CheckDataAndAssert(FChunkSearcher::FChunkDList& ChunkDList, bool bUseOther = false)`
- L270 _public function_ `void CheckDataAndAssert(const FScannerFilesList& ChunkDList, const IDeltaChunkEnumeration* DeltaChunkEnumeration, const TArray<uint8>& ScannerData, bool bUseOther = false)`
- L295 _public function_ `void FindDifferences(const FFileManifestList& FileManifestList, FChunkSearcher::FFileDListNode* FileHead)`
- L322 _public function_ `void FindDifferences(const FFileManifestList& FileManifestListA, const FFileManifestList& FileManifestListB)`
- L357 _private member_ `IFileSystem* const FileSystem;`
- L358 _private member_ `IChunkDataSerialization* const ChunkDataSerialization;`
- L359 _private member_ `const FString BuildLocation;`
- L360 _private member_ `const FString OtherBuildLocation;`
- L361 _private member_ `const FString CloudDir;`
- L362 _private member_ `const FBuildPatchAppManifest& Manifest;`
- L363 _private member_ `const FBuildPatchAppManifest& OtherManifest;`
- L364 _private member_ `const TArray<FString> BuildFiles;`
- L365 _private member_ `const TArray<FString> OtherBuildFiles;`
- L366 _private member_ `TMap<FString, TUniquePtr<FArchive>> LoadedFiles;`
- L367 _private member_ `TMap<FGuid, TUniquePtr<IChunkDataAccess>> LoadedChunks;`
- L368 _private member_ `TArray<uint8> TestBuffer;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Generation/BuildStreamer.h` (Private)


#### class `BuildPatchServices::IBuildStreamer`  
`class IBuildStreamer`  
_L17-36_
- L20 _public prototype_ `virtual ~IBuildStreamer() = default;`
- L29 _public prototype_ `virtual uint32 DequeueData(uint8* Buffer, uint32 ReqSize, bool WaitForData = true) = 0;` — Fetches some data from the buffer, also removing it. @param   IN  Buffer          Pointer to buffer to receive the data. @param   IN  ReqSize         The amount of data to attempt to retrieve. @param   IN  WaitForData     Optional: Default true. Whether to wait until there is enough data in the buffer. @return the amount of data retrieved.
- L35 _public prototype_ `virtual bool IsEndOfData() const = 0;` — Whether there is any more data available to dequeue from the buffer. @return true if there is no more data coming in, and the internal buffer is also empty.

#### class `BuildPatchServices::IDirectoryBuildStreamer`  
`class IDirectoryBuildStreamer : public IBuildStreamer`  
_L38-61_
- inherits: `IBuildStreamer`
- L47 _public prototype_ `virtual uint64 GetBuildSize() const = 0;` — Get the total build size that was streamed. MUST be called only after IsEndOfData returns true. @return the number of bytes in the streamed build.
- L54 _public prototype_ `virtual TArray<FFileSpan> GetAllFiles() const = 0;` — Get the list of file spans for each file in the build, including empty files. MUST be called only after IsEndOfData returns true. @return the list of files in the build and their details.
- L60 _public prototype_ `virtual bool HasAborted() const = 0;` — Gets if the streamer has aborted and is no longer streaming data @return True if it has aborted

#### class `BuildPatchServices::IManifestBuildStreamer`  
`class IManifestBuildStreamer : public IBuildStreamer`  
_L63-77_
- inherits: `IBuildStreamer`
- L68 _public typedef_ `typedef TArray<FGuid> FCustomChunkReferences;` — Declares types for expected factory dependencies.
- L69 _public typedef_ `typedef TFactory<IChunkReferenceTracker, FCustomChunkReferences> IChunkReferenceTrackerFactory;`
- L70 _public typedef_ `typedef TFactory<ICloudChunkSource, IChunkReferenceTracker*> ICloudChunkSourceFactory;`
- L76 _public prototype_ `virtual const FBlockStructure& GetBlockStructure() const = 0;` — Gets the block structure that this streamer was configured with. @return the configured DesiredBytes block structure.

#### struct `BuildPatchServices::FDirectoryBuildStreamerConfig`  
`struct FDirectoryBuildStreamerConfig`  
_L80-89_
- desc: Configuration for constructing a directory build streamer.
- L83 _public member_ `const FString BuildRoot;`
- L84 _public member_ `const TArray<FString> BuildFiles;`
- L85 _public member_ `const bool bFollowSymlinks = false;`
- L86 _public member_ `const bool bDetectMimeType = true;`
- L87 _public member_ `const bool bCalculateMD5 = true;`
- L88 _public member_ `const bool bCalculateSHA256 = true;`

#### struct `BuildPatchServices::FDirectoryBuildStreamerDependencies`  
`struct FDirectoryBuildStreamerDependencies`  
_L92-97_
- desc: Holds all dependencies for constructing a directory build streamer.
- L95 _public member_ `FStatsCollector* const StatsCollector;`
- L96 _public member_ `IFileSystem* const FileSystem;`

#### struct `BuildPatchServices::FManifestBuildStreamerConfig`  
`struct FManifestBuildStreamerConfig`  
_L100-105_
- desc: Configuration for constructing a manifest build streamer.
- L103 _public member_ `TArray<FString> CloudDirectories;`
- L104 _public member_ `FBlockStructure DesiredBytes;`

#### struct `BuildPatchServices::FManifestBuildStreamerDependencies`  
`struct FManifestBuildStreamerDependencies`  
_L108-115_
- desc: Holds all dependencies for constructing a manifest build streamer.
- L111 _public member_ `IManifestBuildStreamer::IChunkReferenceTrackerFactory* const ChunkReferenceTrackerFactory;`
- L112 _public member_ `IManifestBuildStreamer::ICloudChunkSourceFactory* const CloudChunkSourceFactory;`
- L113 _public member_ `FStatsCollector* const StatsCollector;`
- L114 _public member_ `FBuildPatchAppManifest* const Manifest;`

#### class `BuildPatchServices::FBuildStreamerFactory`  
`class FBuildStreamerFactory`  
_L117-135_
- L126 _public prototype_ `static IDirectoryBuildStreamer* Create(FDirectoryBuildStreamerConfig Config, FDirectoryBuildStreamerDependencies Dependencies);` — Factory for constructing a build streamer based on a directory of files. @param Config        The configuration struct. @param Dependencies  The dependencies struct. @return the constructed build streamer.
- L134 _public prototype_ `static IManifestBuildStreamer* Create(FManifestBuildStreamerConfig Config, FManifestBuildStreamerDependencies Dependencies);` — Factory for constructing a build streamer based on an existing manifest and block ranges. @param Config        The configuration struct. @param Dependencies  The dependencies struct. @return the constructed build streamer.

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Generation/ChunkDatabaseWriter.h` (Private)


#### struct `BuildPatchServices::FChunkDatabaseFile`  
`struct FChunkDatabaseFile`  
_L16-20_
- L18 _public member_ `FString DatabaseFilename;`
- L19 _public member_ `TArray<FGuid> DataList;`

#### class `BuildPatchServices::IChunkDatabaseWriter`  
`class IChunkDatabaseWriter : public IControllable`  
_L26-31_
- inherits: `IControllable`
- desc: An interface providing providing access to a system which writes chunk database files, given a chunk source and details of the chunks to put into databases.
- L30 _public prototype_ `virtual ~IChunkDatabaseWriter() = default;`

#### struct `BuildPatchServices::FChunkDbWriterConfig`  
`struct FChunkDbWriterConfig`  
_L36-63_
- desc: A struct containing the configuration values for a chunkdb writer.
- L39 _public member_ `TArray<FChunkDatabaseFile> ChunkDatabaseList;` — The array of chunk database files to create and the chunks to place in them.
- L41 _public member_ `int32 BufferEnqueueMax = 100;` — The max threaded messages to wait on in case of HDD write is slower that chunk fetch.
- L44 _public member_ `bool bUseTempFile = true;` — Whether to use temp file when building, this is safer against failures, but if false, can support resuming. It is advised to use true when generating for cloud upload, and false if producing for local use only on a client for later consumption.
- L46 _public member_ `float HeaderUpdateFrequency = 0.0f;` — If more than 0, the header will be updated every X seconds to minimise loss of data if the process is cancelled.
- L49 _public member_ `bool bReserialise = true;` — If true, will potentially re-encrypt and/or re-compress on save to chumdb. If false, the chunk will be stored as deserialised, and thus decrypted/decompressed where it was possible.
- L51 _public member_ `bool bDeleteFilesOnFailure = true;` — If true, will delete created files upon a failure, otherwise will leave potentially unfinished files on disk.
- L53 _public member_ `bool bCallbackOnMainThread = true;` — If set to false, the progress and complete callbacks will be executed on the worker threads.
- L59 _public function_ `FChunkDbWriterConfig(TArray<FChunkDatabaseFile> InChunkDatabaseList) : ChunkDatabaseList(MoveTemp(InChunkDatabaseList))` — Constructor which sets usual defaults, and takes params for values that cannot use a default. @param InChunkDatabaseList    The chunkdb filename array.

#### class `BuildPatchServices::FChunkDatabaseWriterFactory`  
`class FChunkDatabaseWriterFactory`  
_L68-94_
- desc: A factory for creating an IChunkDatabaseWriter instance.
- L84 _public prototype_ `static IChunkDatabaseWriter* Create( FChunkDbWriterConfig Configuration, IChunkSource* ChunkSource, IFileSystem* FileSystem, IInstallerError* InstallerError, IChunkReferenceTracker* ChunkReferenceTracker, IChunkDataSerialization* ChunkDataSerialization, IFileConstructorStat* InFileConstructorStat, TFunction<void(float)> OnProgress, TFunction<void(bool)> OnComplete);` — This implementation returns a chunk database writer that immediately kicks off the work and calls a provided callback when complete. @param Configuration             The configuration struct for this source. @param ChunkSource               A chunk source for pulling required chunks from. @param FileSystem                A files system interface for writing out the chunkdb files. @param InstallerError            The error interface for aborting on other errors or registering our own. @param ChunkReferenceTracker     Chunk reference tracker to keep up to date. @param ChunkDataSerialization    Chunk data serialization implementation. @param InFileConstructorStat     A file constructor stats class to track HDD activity. @param OnProgress                Function to call with a progress, 0->1. Called on main thread. @param OnComplete                Function to call when the database files have been created. Called on main thread. @return the new IChunkDatabaseWriter.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Generation/ChunkDeltaOptimiser.h` (Private)


#### class `BuildPatchServices::FChunkDeltaOptimiserFactory`  
`class FChunkDeltaOptimiserFactory`  
_L11-15_
- L14 _public prototype_ `static IChunkDeltaOptimiser* Create(FChunkDeltaOptimiserConfiguration Configuration);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Generation/ChunkHarvester.h` (Private)


#### class `BuildPatchServices::FChunkHarvesterFactory`  
`class FChunkHarvesterFactory`  
_L11-15_
- L14 _public prototype_ `static IChunkHarvester* Create(FChunkHarvesterConfiguration Configuration);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Generation/ChunkMatchProcessor.h` (Private)


#### struct `BuildPatchServices::FMatchEntry`  
`struct FMatchEntry`  
_L13-17_
- L15 _public member_ `FChunkMatch ChunkMatch;`
- L16 _public member_ `FBlockStructure BlockStructure;`

#### class `BuildPatchServices::IChunkMatchProcessor`  
`class IChunkMatchProcessor`  
_L19-26_
- L22 _public prototype_ `virtual ~IChunkMatchProcessor() = default;`
- L23 _public prototype_ `virtual void ProcessMatch(const int32 Layer, const FChunkMatch& Match, FBlockStructure BuildSpace) = 0;`
- L24 _public prototype_ `virtual void FlushLayer(const int32 Layer, const uint64 UpToByteOffset) = 0;`
- L25 _public prototype_ `virtual FBlockRange CollectLayer(const int32 Layer, TArray<FMatchEntry>& OutData) = 0;`

#### class `BuildPatchServices::FChunkMatchProcessorFactory`  
`class FChunkMatchProcessorFactory`  
_L28-32_
- L31 _public prototype_ `static IChunkMatchProcessor* Create();`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Generation/ChunkSearch.h` (Private)


#### class `BuildPatchServices::FChunkSearcher`  
`class FChunkSearcher`  
_L69-270_
- L90 _public typedef_ `typedef TDoubleLinkedList<FChunkNode> FChunkDList;`
- L91 _public typedef_ `typedef FChunkDList::TDoubleLinkedListNode FChunkDListNode;`
- L113 _public typedef_ `typedef TDoubleLinkedList<FFileNode> FFileDList;`
- L114 _public typedef_ `typedef FFileDList::TDoubleLinkedListNode FFileDListNode;`
- L117 _public function_ `template<typename InitType> FChunkSearcher(const InitType& InitClass)`
- L134 _public function_ `void ForEachOverlap(const FBlockStructure& BlockStructure, const TFunction<void(const FBlockRange&, FFileDListNode*, FChunkDListNode*)>& Handler)`
- L144 _public function_ `void ForEachOverlap(const FBlockRange& BlockRange, const TFunction<void(const FBlockRange&, FFileDListNode*, FChunkDListNode*)>& Handler)`
- L198 _public function_ `FFileDListNode* GetHead()`
- L203 _public function_ `FFileManifestList BuildNewFileManifestList()`
- L220 _private function_ `void SetStart()`
- L227 _private function_ `template<typename ListType, typename ListNodeType> ListNodeType* FindFirst(ListType* List, ListNodeType* Current, const FBlockRange& BlockRange)`
- L267 _private member_ `FFileDList FileLinkedList;`
- L268 _private member_ `FFileDListNode* CurrFile;`
- L269 _private member_ `FChunkDListNode* CurrChunk;`

#### struct `BuildPatchServices::FChunkSearcher::FChunkNode`  
`struct FChunkNode`  
_L72-89_
- L75 _public function_ `FChunkNode(const FChunkPart& InChunkPart, const FBlockRange& InBuildRange) : BuildRange(InBuildRange) , ChunkPart(InChunkPart)`
- L80 _public function_ `FChunkNode(const FChunkNode& CopyFrom) : BuildRange(CopyFrom.BuildRange) , ChunkPart(CopyFrom.ChunkPart)`
- L87 _public member_ `FBlockRange BuildRange;`
- L88 _public member_ `FChunkPart ChunkPart;`

#### struct `BuildPatchServices::FChunkSearcher::FFileNode`  
`struct FFileNode`  
_L93-112_
- L96 _public function_ `FFileNode(const FFileManifest *const InManifest, const FBlockRange& InBuildRange) : Manifest(InManifest) , BuildRange(InBuildRange)`
- L101 _public function_ `FFileNode(const FFileNode& CopyFrom) : Manifest(CopyFrom.Manifest) , BuildRange(CopyFrom.BuildRange)`
- L109 _public member_ `const FFileManifest *const Manifest;`
- L110 _public member_ `const FBlockRange BuildRange;`
- L111 _public member_ `FChunkDList ChunkParts;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace BuildPatchServices`
- L14 _namespace_ `namespace ListHelpers` (scope `BuildPatchServices`)
- L17 _function_ `template <typename ElementType> FORCEINLINE void Copy(const TDoubleLinkedList<ElementType>& CopyFrom, TDoubleLinkedList<ElementType>& CopyTo)` (scope `BuildPatchServices::ListHelpers`)
- L26 _function_ `template <typename ListType, typename NodeType, typename ElementType> FORCEINLINE void InsertBefore(const ElementType& NewNode, ListType& List, NodeType* Node)` (scope `BuildPatchServices::ListHelpers`)
- L32 _function_ `template <typename ListType, typename NodeType, typename ElementType> FORCEINLINE void InsertAfter(const ElementType& NewNode, ListType& List, NodeType* Node)` (scope `BuildPatchServices::ListHelpers`)
- L45 _function_ `FORCEINLINE TArray<FString> GetFileList(const FBuildPatchAppManifest& Manifest)` (scope `BuildPatchServices::ListHelpers`)
- L52 _function_ `FORCEINLINE void ForEach(const FBuildPatchAppManifest& Manifest, const TFunction<void(const FFileManifest&)>& Func)` (scope `BuildPatchServices::ListHelpers`)
- L60 _function_ `FORCEINLINE void ForEach(const FFileManifestList& FileManifestList, const TFunction<void(const FFileManifest&)>& Func)` (scope `BuildPatchServices::ListHelpers`)
- L121 _function_ `` (scope `BuildPatchServices::FChunkSearcher::FChunkSearcher`)

### `Source/Runtime/Online/BuildPatchServices/Private/Generation/ChunkWriter.h` (Private)


#### struct `BuildPatchServices::FParallelChunkWriterConfig`  
`struct FParallelChunkWriterConfig`  
_L17-26_
- L19 _public member_ `int32 OperationRetryCount;`
- L20 _public member_ `float OperationRetryTime;`
- L21 _public member_ `int32 MaxQueueSize;`
- L22 _public member_ `int32 NumberOfThreads;`
- L23 _public member_ `bool bResaveExistingChunks;`
- L24 _public member_ `FString ChunkDirectory;`
- L25 _public member_ `EFeatureLevel FeatureLevel;`

#### struct `BuildPatchServices::FParallelChunkWriterSummaries`  
`struct FParallelChunkWriterSummaries`  
_L28-37_
- L30 _public member_ `EFeatureLevel FeatureLevel;`
- L31 _public member_ `TMap<FGuid, int64> ChunkOutputCompressedSizes;`
- L32 _public member_ `TMap<FGuid, int64> ChunkOutputFileSizes;`
- L33 _public member_ `TMap<FGuid, uint64> ChunkOutputHashes;`
- L34 _public member_ `TMap<FGuid, FSHAHash> ChunkOutputShas;`
- L35 _public member_ `TMap<FGuid, FGuid> ChunkOutputSecretIds;`
- L36 _public member_ `TMap<FGuid, FAESAuthTag> ChunkOutputAuthTags;`

#### class `BuildPatchServices::IParallelChunkWriter`  
`class IParallelChunkWriter`  
_L39-108_
- L42 _public prototype_ `virtual ~IParallelChunkWriter() = default;`
- L51 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FOnChunkFileWritten, const FString& , const FMD5Hash& , const FSHAHash& );` — Declares an event type exposed on this class for when chunks have been saved to the cloud directory. The event offers two types of hash of the filedata saved out. @param FullFilePath   The full file path on disk for the file saved. @param MD5Hash        The MD5 checksum for the file data. @param SHA1Hash       The SHA1 checksum for the file data. This is not the ChunkSha, it is the serialized file SHA1.
- L58 _public prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnChunkFileWriteFailed, const FString& );` — Declares an event type exposed on this class for when chunks have failed to be saved to the cloud directory. The event offers an error message of happened error. @param FullFilePath   The full file path on disk for for the file that failed.
- L63 _public prototype_ `virtual FOnChunkFileWritten& OnChunkFileWritten() = 0;` — @return a delegate that will broadcast when a chunk was written to the cloud directory.
- L68 _public prototype_ `virtual FOnChunkFileWriteFailed& OnChunkFileWriteFailed() = 0;` — @return a delegate that will broadcast when a chunk failed to be written to the cloud directory.
- L74 _public prototype_ `virtual void PumpEvents() = 0;` — Must be called periodically to flush events, from the desired receiving thread. If this is not called the OnChunkFileWritten() will never broadcast, and GetInFlightChunkCount() can remain high.
- L84 _public prototype_ `virtual bool AddChunkData(TArray<uint8> ChunkData, const FGuid& ChunkGuid, const uint64& ChunkHash, const FSHAHash& ChunkSha) = 0;` — Queues up serialization for a chunk file. @param ChunkData      The raw chunk data from the build. @param ChunkGuid      The identifier for the chunk. @param ChunkHash      The rolling hash for the chunk. @param ChunkSha       The SHA1 hash for the chunk. @return true if queued up successfully.
- L89 _public prototype_ `virtual int32 GetInFlightChunkCount() = 0;` — @return the number of chunk writes still outstanding.
- L95 _public prototype_ `virtual FParallelChunkWriterSummaries OnProcessComplete() = 0;` — Gets the summary data for the process. The function will not return until all threads have completed. @return the summary data upon completion of the process.
- L100 _public prototype_ `virtual void Abort() = 0;` — Aborts current operations and no longer accepts new chunks.
- L106 _public prototype_ `virtual bool HasAborted() const = 0;` — Gets if the writer has aborted @return True if it has aborted

#### class `BuildPatchServices::FParallelChunkWriterFactory`  
`class FParallelChunkWriterFactory`  
_L110-114_
- L113 _public prototype_ `static IParallelChunkWriter* Create(FParallelChunkWriterConfig Config, IFileSystem* FileSystem, IChunkDataSerialization* ChunkDataSerialization, FStatsCollector* StatsCollector);`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace BuildPatchServices`
- L51 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FOnChunkFileWritten, const FString& , const FMD5Hash& , const FSHAHash& );` — Declares an event type exposed on this class for when chunks have been saved to the cloud directory. The event offers two types of hash of the filedata saved out. @param FullFilePath   The full file path on disk for the file saved. @param MD5Hash        The MD5 checksum for the file data. @param SHA1Hash       The SHA1 checksum for the file data. This is not the ChunkSha, it is the serialized file SHA1.
- L58 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnChunkFileWriteFailed, const FString& );` — Declares an event type exposed on this class for when chunks have failed to be saved to the cloud directory. The event offers an error message of happened error. @param FullFilePath   The full file path on disk for for the file that failed.

### `Source/Runtime/Online/BuildPatchServices/Private/Generation/CloudEnumeration.h` (Private)


#### class `BuildPatchServices::ICloudEnumeration`  
`class ICloudEnumeration`  
_L15-34_
- L18 _public prototype_ `virtual ~ICloudEnumeration()= default;`
- L19 _public prototype_ `virtual bool IsComplete() const = 0;`
- L20 _public prototype_ `virtual const TSet<uint32>& GetUniqueWindowSizes() const = 0;`
- L21 _public prototype_ `virtual const TMap<uint64, TSet<FGuid>>& GetChunkInventory() const = 0;`
- L22 _public prototype_ `virtual const TMap<FGuid, int64>& GetChunkFileSizes() const = 0;`
- L23 _public prototype_ `virtual const TMap<FGuid, int64>& GetChunkCompressedSizes() const = 0;`
- L24 _public prototype_ `virtual const TMap<FGuid, FSHAHash>& GetChunkShaHashes() const = 0;`
- L25 _public prototype_ `virtual const TMap<FGuid, FAESAuthTag>& GetChunkAESAuthTags() const = 0;`
- L26 _public prototype_ `virtual const TMap<FGuid, uint32>& GetChunkWindowSizes() const = 0;`
- L27 _public prototype_ `virtual const TMap<FGuid, FGuid>& GetChunkSecretIds() const = 0;`
- L28 _public prototype_ `virtual bool IsChunkFeatureLevelMatch(const FGuid& ChunkId) const = 0;`
- L29 _public prototype_ `virtual const uint64& GetChunkHash(const FGuid& ChunkId) const = 0;`
- L30 _public prototype_ `virtual const FSHAHash& GetChunkShaHash(const FGuid& ChunkId) const = 0;`
- L31 _public prototype_ `virtual const TMap<FSHAHash, TSet<FGuid>>& GetIdenticalChunks() const = 0;`
- L33 _public prototype_ `virtual const TArray<FString>& GetUnsupportedFeatureLevelBuilds() const = 0;` — Returns the versions of build which generated with Feature Level greater than EFeatureLevel::Last.

#### class `BuildPatchServices::FCloudEnumerationFactory`  
`class FCloudEnumerationFactory`  
_L36-51_
- L50 _public prototype_ `static ICloudEnumeration* Create(const FString& CloudDirectory, const FDateTime& ManifestAgeThreshold, const TFunction<bool(const IBuildManifest&)>& Predicate, const EFeatureLevel& OutputFeatureLevel, FStatsCollector* StatsCollector);` — Creates an instance of ICloudEnumeration for managing cloud uploaded chunks. The predicate allows to filter manifests based on custom logic. @param CloudDirectory The cloud root directory. @param ManifestAgeThreshold The threshold age for manifest files; files older than this will be ignored. @param Predicate A callable that takes a const reference to an IBuildManifest and returns true to include the manifest, or false to ignore it. @param OutputFeatureLevel The desired feature level for enumerated output. @param StatsCollector A pointer to the statistics collector for recording related data. @return A pointer to the created ICloudEnumeration instance.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Generation/DataScanner.h` (Private)


#### struct `BuildPatchServices::FChunkMatch`  
`struct FChunkMatch`  
_L16-30_
- L18 _public function_ `FChunkMatch(const uint64& InDataOffset, const FGuid& InChunkGuid, const uint32& InWindowSize) : DataOffset(InDataOffset) , ChunkGuid(InChunkGuid) , WindowSize(InWindowSize)`
- L25 _public member_ `uint64 DataOffset;` — Offset into provided data.
- L27 _public member_ `FGuid ChunkGuid;` — The chunk matched.
- L29 _public member_ `uint32 WindowSize;` — The window size.

#### struct `BuildPatchServices::FScannerFileElement`  
`struct FScannerFileElement`  
_L32-38_
- L34 _public member_ `FBlockRange FileScannerRange;`
- L35 _public member_ `FFilenameId ScanFilename;`
- L36 _public member_ `TSet<FString> ScanTagSet;`
- L37 _public member_ `uint64 ScannerFileLocation;`

#### class `BuildPatchServices::IDataScanner`  
`class IDataScanner`  
_L43-52_
- L46 _public prototype_ `virtual ~IDataScanner() = default;`
- L47 _public prototype_ `virtual bool IsComplete() = 0;`
- L48 _public prototype_ `virtual TArray<FChunkMatch> GetResultWhenComplete() = 0;`
- L49 _public prototype_ `virtual double GetTimeRunning() = 0;`
- L50 _public prototype_ `virtual bool SupportsFork() = 0;`
- L51 _public prototype_ `virtual FBlockRange Fork() = 0;`

#### class `BuildPatchServices::FDataScannerCounter`  
`class FDataScannerCounter`  
_L54-63_
- L57 _public prototype_ `static int32 GetNumIncompleteScanners();`
- L58 _public prototype_ `static int32 GetNumRunningScanners();`
- L59 _public prototype_ `static void IncrementIncomplete();`
- L60 _public prototype_ `static void DecrementIncomplete();`
- L61 _public prototype_ `static void IncrementRunning();`
- L62 _public prototype_ `static void DecrementRunning();`

#### class `BuildPatchServices::FDataScannerFactory`  
`class FDataScannerFactory`  
_L65-69_
- L68 _public prototype_ `static IDataScanner* Create(const TArray<uint32>& ChunkWindowSizes, const TArray<uint8>& Data, const ICloudEnumeration* CloudEnumeration, FStatsCollector* StatsCollector, uint64 DataOffset);`

#### class `BuildPatchServices::FDeltaScannerFactory`  
`class FDeltaScannerFactory`  
_L71-75_
- L74 _public prototype_ `static IDataScanner* Create(const uint32 WindowSize, const TArray<uint8>& Data, const FScannerFilesList& FilesList, const IDeltaChunkEnumeration* CloudEnumeration, FStatsCollector* StatsCollector);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace BuildPatchServices`
- L40 _typedef_ `typedef TDoubleLinkedList<FScannerFileElement> FScannerFilesList;` (scope `BuildPatchServices`)
- L41 _typedef_ `typedef FScannerFilesList::TDoubleLinkedListNode FScannerFilesListNode;` (scope `BuildPatchServices`)

### `Source/Runtime/Online/BuildPatchServices/Private/Generation/DeltaEnumeration.h` (Private)


#### struct `BuildPatchServices::FChunkBuildReferenceSourceFile`  
`struct FChunkBuildReferenceSourceFile`  
_L23-28_
- L25 _public member_ `FFilenameId Filename;`
- L26 _public member_ `TSet<FString> Tagset;`
- L27 _public member_ `uint64 Location;`

#### struct `BuildPatchServices::FChunkBuildReference`  
`struct FChunkBuildReference`  
_L30-34_
- L32 _public member_ `TArray<FChunkPart> ChunkParts;`
- L33 _public member_ `TArray<FChunkBuildReferenceSourceFile> FileReferences;`

#### class `BuildPatchServices::IDeltaChunkEnumeration`  
`class IDeltaChunkEnumeration`  
_L36-55_
- L39 _public prototype_ `virtual ~IDeltaChunkEnumeration() = default;`
- L40 _public prototype_ `virtual void Run() = 0;`
- L41 _public prototype_ `virtual bool IsComplete() const = 0;`
- L42 _public prototype_ `virtual bool IsSuccess() const = 0;`
- L43 _public prototype_ `virtual const TMap<uint64, TSet<FDeltaChunkId>>& GetChunkInventory() const = 0;`
- L44 _public prototype_ `virtual const TMap<FDeltaChunkId, FShaId>& GetChunkShaHashes() const = 0;`
- L45 _public prototype_ `virtual const TMap<FDeltaChunkId, FChunkBuildReference>& GetChunkBuildReferences() const = 0;`
- L46 _public prototype_ `virtual const TMap<FShaId, TSet<FDeltaChunkId>>& GetIdenticalChunks() const = 0;`
- L47 _public prototype_ `virtual const uint64& GetChunkHash(const FDeltaChunkId& ChunkId) const = 0;`
- L48 _public prototype_ `virtual const FSHAHash& GetChunkShaHash(const FDeltaChunkId& ChunkId) const = 0;`
- L49 _public prototype_ `virtual FFilenameId MakeFilenameId(const FString& Filename) = 0;`
- L50 _public prototype_ `virtual FShaId MakeShaId(const FSHAHash& SHAHash) = 0;`
- L51 _public prototype_ `virtual FFilenameId GetFilenameId(const FString& Filename) const = 0;`
- L52 _public prototype_ `virtual FShaId GetShaId(const FSHAHash& SHAHash) const = 0;`
- L53 _public prototype_ `virtual const FString& GetFilename(const FFilenameId& Filename) const = 0;`
- L54 _public prototype_ `virtual const FSHAHash& GetSha(const FShaId& SHAHash) const = 0;`

#### class `BuildPatchServices::FDeltaChunkEnumerationFactory`  
`class FDeltaChunkEnumerationFactory`  
_L57-61_
- L60 _public prototype_ `static IDeltaChunkEnumeration* Create(IManifestBuildStreamer* Streamer, FStatsCollector* StatsCollector, const FBuildPatchAppManifest& Manifest, const uint32 WindowSize, const TMap<FString, FString>& InAliasedTags, const TSet<FString>& InIgnoredTags);`

#### Free symbols / members of external scopes

- L9 _function_ `inline uint32 GetTypeHash(const FSetElementId A)`
- L14 _namespace_ `namespace BuildPatchServices`
- L19 _typedef_ `typedef FGuid FDeltaChunkId;` (scope `BuildPatchServices`)
- L20 _typedef_ `typedef FSetElementId FFilenameId;` (scope `BuildPatchServices`)
- L21 _typedef_ `typedef FSetElementId FShaId;` (scope `BuildPatchServices`)

### `Source/Runtime/Online/BuildPatchServices/Private/Generation/FileAttributesParser.h` (Private)


#### struct `BuildPatchServices::FFileAttributes`  
`struct FFileAttributes`  
_L11-17_
- L13 _public member_ `bool bReadOnly = false;`
- L14 _public member_ `bool bCompressed = false;`
- L15 _public member_ `bool bUnixExecutable = false;`
- L16 _public member_ `TSet<FString> InstallTags;`

#### class `BuildPatchServices::FFileAttributesMap`  
`class FFileAttributesMap`  
_L19-89_
- L22 _public prototype_ `FFileAttributesMap() = default;`
- L24 _public function_ `FFileAttributesMap(TMap<FString, FFileAttributes> ExtMap)`
- L29 _public function_ `void Emplace(TMap<FString, FFileAttributes> ExtMap)`
- L35 _public function_ `const TMap<FString, FFileAttributes>& Raw() const`
- L40 _public function_ `const TMap<FString, FFileAttributes>& RawPatterns() const`
- L45 _public function_ `FFileAttributes& FindExactOrAdd(const FString& Name)`
- L50 _public function_ `FFileAttributes Find(const FString& Name) const`
- L69 _private function_ `void SortPatterns()`
- L87 _private member_ `TMap<FString, FFileAttributes> Map;`
- L88 _private member_ `TMap<FString, FFileAttributes> PatternMap;`

#### class `BuildPatchServices::FFileAttributesParser`  
`class FFileAttributesParser`  
_L91-101_
- L100 _public prototype_ `virtual bool ParseFileAttributes(const FString& MetaFilename, TMap<FString, FFileAttributes>& FileAttributes) = 0;` — Loads in the file attributes meta file and populates the given map. @param   MetaFilename        The amount of data to attempt to retrieve. @param   FileAttributes      The map to populate with the attributes @return  True if the file existed and parsed successfully

#### class `BuildPatchServices::FFileAttributesParserFactory`  
`class FFileAttributesParserFactory`  
_L106-110_
- L109 _public prototype_ `static FFileAttributesParserRef Create(IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile());`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace BuildPatchServices`
- L103 _typedef_ `typedef TSharedRef<FFileAttributesParser, ESPMode::ThreadSafe> FFileAttributesParserRef;` (scope `BuildPatchServices`)
- L104 _typedef_ `typedef TSharedPtr<FFileAttributesParser, ESPMode::ThreadSafe> FFileAttributesParserPtr;` (scope `BuildPatchServices`)

### `Source/Runtime/Online/BuildPatchServices/Private/Generation/ManifestBuilder.h` (Private)


#### struct `BuildPatchServices::FManifestDetails`  
`struct FManifestDetails`  
_L13-48_
- L17 _public member_ `EFeatureLevel FeatureLevel;` — The feature level support the manifest should be serialised as.
- L19 _public member_ `uint32 AppId;` — The ID of the app of this build
- L21 _public member_ `FString AppName;` — The name of the app of this build
- L23 _public member_ `FString BuildVersion;` — The version string for this build
- L25 _public member_ `FString LaunchExe;` — The local exe path that would launch this build
- L27 _public member_ `FString LaunchCommand;` — The command line that would launch this build
- L29 _public member_ `TSet<FString> PrereqIds;` — The set of identifiers which the prerequisites satisfy
- L31 _public member_ `FString PrereqName;` — The display name of the prerequisites installer
- L33 _public member_ `FString PrereqPath;` — The path to the prerequisites installer
- L35 _public member_ `FString PrereqArgs;` — The command line arguments for the prerequisites installer
- L37 _public member_ `FString UninstallActionPath;` — The path to the uninstall custom action executable.
- L39 _public member_ `FString UninstallActionArgs;` — The arguments to the uninstall custom action executable.
- L41 _public member_ `TMap<FString, FVariant> CustomFields;` — Map of custom fields to add to the manifest
- L43 _public member_ `FFileAttributesMap FileAttributesMap;` — Map of file attributes
- L45 _public member_ `TArray<uint8> EncryptionSecretKey;` — The encryption secret key to use for this manifest.
- L47 _public member_ `FGuid EncryptionSecretId;` — The ID of the encryption secret key used by this manifest.

#### struct `BuildPatchServices::FManifestBuilderConfig`  
`struct FManifestBuilderConfig`  
_L50-61_
- L56 _public prototype_ `FManifestBuilderConfig();` — Default constructor. Initializes all members with default behavior values.
- L60 _public member_ `bool bAllowEmptyBuilds;` — Whether or not we should allow build manifests with no data.

#### class `BuildPatchServices::IManifestBuilder`  
`class IManifestBuilder`  
_L63-71_
- L66 _public prototype_ `virtual ~IManifestBuilder() = default;`
- L67 _public prototype_ `virtual void AddChunkMatch(const FGuid& ChunkGuid, const FBlockStructure& Structure) = 0;`
- L68 _public prototype_ `virtual bool FinalizeData(const TArray<FFileSpan>& FileSpans, TArray<FChunkInfo> ChunkInfo) = 0;`
- L69 _public prototype_ `virtual bool SaveToFile(const FString& Filename, FSHAHash* OutSHA1Hash, FMD5Hash* OutMD5Hash) = 0;`
- L70 _public prototype_ `virtual FBuildPatchAppManifest& GetManifest() const = 0;`

#### class `BuildPatchServices::FManifestBuilderFactory`  
`class FManifestBuilderFactory`  
_L76-80_
- L79 _public prototype_ `static IManifestBuilderRef Create(IFileSystem* FileSystem, const FManifestBuilderConfig& Config, const FManifestDetails& Details);`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace BuildPatchServices`
- L73 _typedef_ `typedef TSharedRef<IManifestBuilder> IManifestBuilderRef;` (scope `BuildPatchServices`)
- L74 _typedef_ `typedef TSharedPtr<IManifestBuilder> IManifestBuilderPtr;` (scope `BuildPatchServices`)

### `Source/Runtime/Online/BuildPatchServices/Private/Generation/PackageChunkData.h` (Private)


#### class `BuildPatchServices::IPackageChunks`  
`class IPackageChunks`  
_L16-21_
- L19 _public prototype_ `virtual ~IPackageChunks() = default;`
- L20 _public prototype_ `virtual bool Run() = 0;`

#### class `BuildPatchServices::FPackageChunksFactory`  
`class FPackageChunksFactory`  
_L23-27_
- L26 _public prototype_ `static IPackageChunks* Create(const FPackageChunksConfiguration& Configuration);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace BuildPatchServices`
- L10 _namespace_ `namespace ChunkDbHelpers` (scope `BuildPatchServices`)
- L12 _prototype_ `uint32 GetChunkDbHeaderSize();` (scope `BuildPatchServices::ChunkDbHelpers`)
- L13 _prototype_ `uint32 GetPerChunkEntryHeaderSize();` (scope `BuildPatchServices::ChunkDbHelpers`)

### `Source/Runtime/Online/BuildPatchServices/Private/Generation/RegexFind.h` (Private)


#### struct `BuildPatchServices::TMatchingType`  
`template<typename T> struct TMatchingType`  
_L15-48_
- L17 _public function_ `static const FString& GetIdentification()`
- L23 _public function_ `static bool StartsWithIdentification(const FString& String)`
- L28 _public function_ `static bool EndsWithQuote(const FString& String)`
- L33 _public function_ `static bool IsPattern(const FString& String)`
- L38 _public function_ `static FString ExtractPattern(const FString& String)`
- L43 _public function_ `static bool Match(const FString& Pattern, const FString& Value)`

#### struct `BuildPatchServices::FRegexPatternType`  
`struct FRegexPatternType : TMatchingType<FRegexPatternType>`  
_L50-60_
- inherits: `TMatchingType<FRegexPatternType>`
- L52 _public member_ `static constexpr const TCHAR* CharIdentification = TEXT("R\"`
- L54 _public function_ `static bool PatternMatch(const FString& Pattern, const FString& Value)`

#### struct `BuildPatchServices::FWildcardPatternType`  
`struct FWildcardPatternType : TMatchingType<FWildcardPatternType>`  
_L62-71_
- inherits: `TMatchingType<FWildcardPatternType>`
- L64 _public member_ `static constexpr const TCHAR* CharIdentification = TEXT("W\"`
- L66 _public function_ `static bool PatternMatch(const FString& Pattern, const FString& Value)`

#### struct `BuildPatchServices::FRegexFinder`  
`struct FRegexFinder`  
_L73-109_
- L75 _public function_ `static bool StartsLikePattern(const FString& Pattern)`
- L80 _public function_ `static bool EndsWithQuote(const FString& Pattern)`
- L85 _public function_ `static bool IsPattern(const FString& Pattern)`
- L90 _public function_ `static bool Match(const FString& Pattern, const FString& Value)`
- L105 _public function_ `static bool Match(const FString& Pattern, const TSet<FString>& Set)`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace BuildPatchServices`
- L107 _function_ `return Algo::AnyOf(Set, [&Pattern](const FString& Item) { return Match(Item, Pattern); });` (scope `BuildPatchServices::FRegexFinder::Match`)
- L112 _function_ `template<typename T> TArray<const T*> RegexFind(const FString& Name, const TMap<FString, T>& Map)` (scope `BuildPatchServices`)

### `Source/Runtime/Online/BuildPatchServices/Private/IBuildManifestSet.h` (Private)


#### struct `BuildPatchServices::FPreReqInfo`  
`struct FPreReqInfo`  
_L12-21_
- L14 _public member_ `TSet<FString> IdSet;`
- L15 _public member_ `FString Name;`
- L16 _public member_ `FString Path;`
- L17 _public member_ `FString Args;`
- L18 _public member_ `FString AppName;`
- L19 _public member_ `FString VersionString;`
- L20 _public member_ `bool bIsRepair;`

#### struct `BuildPatchServices::FUninstallActionInfo`  
`struct FUninstallActionInfo`  
_L23-27_
- L25 _public member_ `FString Path;`
- L26 _public member_ `FString Args;`

#### struct `BuildPatchServices::FBuildPatchInstallerAction`  
`struct FBuildPatchInstallerAction`  
_L34-95_
- desc: FBuildPatchInstallerAction This class decorates an FInstallerAction instance with downcasted functions for internal manifest implementation. It also allows editing of the install manifest in the case a more optimal version was produced from a delta download.
- L37 _public function_ `FBuildPatchInstallerAction(const FInstallerAction& InInstallerAction) : InstallerAction(InInstallerAction) , CurrentManifest(StaticCastSharedPtr<FBuildPatchAppManifest>(InstallerAction.TryGetCurrentManifest())) , InstallManifest(StaticCastSharedPtr<FBuildPatchAppManifest>(InstallerAction.TryGetInstallManifest()))`
- L58 _public function_ `bool IsInstall() const`
- L59 _public function_ `bool IsUpdate() const`
- L60 _public function_ `bool IsRepair() const`
- L61 _public function_ `bool IsVerifyOnly() const`
- L62 _public function_ `bool IsUninstall() const`
- L63 _public function_ `const TSet<FString>& GetInstallTags() const`
- L64 _public function_ `const FString& GetInstallSubdirectory() const`
- L65 _public function_ `const FString& GetCloudSubdirectory() const`
- L66 _public function_ `FString GetUniqueBuildId() const`
- L67 _public function_ `const FBuildPatchAppManifest& GetCurrentManifest() const`
- L68 _public function_ `const FBuildPatchAppManifest& GetInstallManifest() const`
- L69 _public function_ `const FBuildPatchAppManifest* TryGetCurrentManifest() const`
- L70 _public function_ `const FBuildPatchAppManifest* TryGetInstallManifest() const`
- L71 _public function_ `const FBuildPatchAppManifest& GetCurrentOrInstallManifest() const`
- L72 _public function_ `const FBuildPatchAppManifest& GetInstallOrCurrentManifest() const`
- L73 _public function_ `const FBuildPatchAppManifestRef GetSharedCurrentManifest() const`
- L74 _public function_ `const FBuildPatchAppManifestRef GetSharedInstallManifest() const`
- L75 _public function_ `const FBuildPatchAppManifestPtr TryGetSharedCurrentManifest() const`
- L76 _public function_ `const FBuildPatchAppManifestPtr TryGetSharedInstallManifest() const`
- L77 _public function_ `const FBuildPatchAppManifestRef GetSharedCurrentOrInstallManifest() const`
- L78 _public function_ `const FBuildPatchAppManifestRef GetSharedInstallOrCurrentManifest() const`
- L80 _public function_ `void SetDeltaManifest(const FBuildPatchAppManifestRef& DeltaManifest)`
- L86 _private function_ `const TSet<FString>& GetTaggedFiles() const`
- L87 _private function_ `void SetTaggedFiles(TSet<FString> OverrideTaggedFiles)`
- L90 _private member_ `const FInstallerAction InstallerAction;`
- L91 _private member_ `FBuildPatchAppManifestPtr CurrentManifest;`
- L92 _private member_ `FBuildPatchAppManifestPtr InstallManifest;`
- L93 _private member_ `TSet<FString> InstallTags;`
- L94 _private member_ `TSet<FString> TaggedFiles;`

#### class `BuildPatchServices::IBuildManifestSet`  
`class IBuildManifestSet`  
_L97-143_
- L100 _public prototype_ `virtual ~IBuildManifestSet() = default;`
- L103 _public prototype_ `virtual void GetInstallResumeIds(TSet<FString>& ResumeIds, bool bIncludeLegacy) const = 0;` — Manifest info
- L104 _public prototype_ `virtual void GetInstallResumeIdsForFile(const FString& BuildFile, TSet<FString>& ResumeIds, bool bIncludeLegacy) const = 0;`
- L107 _public prototype_ `virtual void GetReferencedChunks(TSet<FGuid>& DataGuids) const = 0;` — Data enumeration
- L108 _public prototype_ `virtual void GetReferencedChunks(TArray<FGuid>& DataGuids) const = 0;`
- L109 _public prototype_ `virtual uint64 GetDownloadSize(const FGuid& DataGuid) const = 0;`
- L110 _public prototype_ `virtual uint64 GetDownloadSize(const TSet<FGuid>& DataGuids) const = 0;`
- L111 _public prototype_ `virtual FChunkInfo const* GetChunkInfo(const FGuid& DataGuid) const = 0;`
- L112 _public prototype_ `virtual bool GetChunkShaHash(const FGuid& ChunkGuid, FSHAHash& OutHash) const = 0;`
- L113 _public prototype_ `virtual FGuid GetDataSecretId(const FGuid& DataGuid) const = 0;`
- L114 _public prototype_ `virtual FString GetChunkCloudSubdirectory(const FGuid& DataGuid) const = 0;`
- L115 _public prototype_ `virtual FString GetChunkFilename(const FGuid& DataGuid) const = 0;`
- L116 _public prototype_ `virtual FString GetChunkFilenameWithCloudSubdirectory(const FGuid& DataGuid) const = 0;`
- L117 _public prototype_ `virtual FString GetChunkUniqueBuildId(const FGuid& DataGuid) const = 0;`
- L118 _public prototype_ `virtual bool GetChunkFromDeltaStatus(const FGuid& DataGuid) const = 0;`
- L121 _public prototype_ `virtual int32 GetNumExpectedFiles() const = 0;` — File enumeration
- L122 _public prototype_ `virtual void GetExpectedFiles(TSet<FString>& Filenames) const = 0;`
- L123 _public prototype_ `virtual void GetOutdatedFiles(const FString& InstallDirectory, TSet<FString>& OutdatedFiles) const = 0;`
- L125 _public prototype_ `virtual void GetMissedFiles(const FString& InstallDirectory, TSet<FString>& OutMissedFiles) const = 0;` — Gets files from the current manifest that are missing from disk.
- L126 _public prototype_ `virtual void GetRemovableFiles(TSet<FString>& FilesToRemove) const = 0;`
- L127 _public prototype_ `virtual const FFileManifest* GetCurrentFileManifest(const FString& BuildFile) const = 0;`
- L128 _public prototype_ `virtual const FFileManifest* GetNewFileManifest(const FString& BuildFile) const = 0;`
- L129 _public prototype_ `virtual uint64 GetTotalNewFileSize(const TArray<FString>& Filenames) const = 0;`
- L130 _public prototype_ `virtual uint64 GetTotalNewFileSize(const TSet<FString>& Filenames) const = 0;`
- L131 _public prototype_ `virtual void GetFilesTaggedForRepair(TSet<FString>& Filenames) const = 0;`
- L132 _public prototype_ `virtual bool IsFileRepairAction(const FString& Filename) const = 0;`
- L135 _public prototype_ `virtual bool ContainsUpdate() const = 0;` — Misc actions
- L136 _public prototype_ `virtual bool IsExclusivelyRepairing() const = 0;`
- L137 _public prototype_ `virtual bool HasFileAttributes() const = 0;`
- L138 _public prototype_ `virtual bool IsExclusivelyVerifying() const = 0;`
- L141 _public prototype_ `virtual void GetPreReqInfo(TArray<FPreReqInfo>& PreReqInfo) const = 0;` — Custom install support
- L142 _public prototype_ `virtual void GetUninstallActionInfo(TArray<FUninstallActionInfo>& UninstallActionsInfo) const = 0;`

#### class `BuildPatchServices::FBuildManifestSetFactory`  
`class FBuildManifestSetFactory`  
_L145-149_
- L148 _public prototype_ `static IBuildManifestSet* Create(TArray<FBuildPatchInstallerAction> InstallerActions);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Installer/BuildStatistics.h` (Private)


#### class `BuildPatchServices::FBuildStatisticsFactory`  
`class FBuildStatisticsFactory`  
_L12-16_
- desc: A factory for creating an IBuildStatistics instance.
- L15 _public prototype_ `static IBuildStatistics* Create(FBuildPatchInstallerRef Installer);`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Installer/ChunkDbChunkSource.h` (Private)


#### struct `BuildPatchServices::FChunkDbSourceConfig`  
`struct FChunkDbSourceConfig`  
_L23-42_
- desc: A struct containing the configuration values for a chunkdb chunk source.
- L26 _public member_ `TArray<FString> ChunkDbFiles;` — An array of chunkdb full file paths.
- L29 _public member_ `bool bDeleteChunkDBAfterUse = false;` — If true, once we complete a file we delete all the chunkdbs used to create it.
- L33 _public member_ `bool bTruncateChunkDbs = false;` — If we are loading from a chunkDB, in reverse order, we can truncate the chunkDB files as we go if desired. This is for preload support.
- L39 _public function_ `FChunkDbSourceConfig(TArray<FString> InChunkDbFiles) : ChunkDbFiles(MoveTemp(InChunkDbFiles))` — Constructor which sets usual defaults, and takes params for values that cannot use a default. @param InChunkDbFiles    The chunkdb filename array.

#### class `BuildPatchServices::IConstructorChunkDbChunkSource`  
`class IConstructorChunkDbChunkSource : public IConstructorChunkSource`  
_L47-70_
- inherits: `IConstructorChunkSource`
- desc: The interface for a chunkdb chunk source, which provides access to chunk data retrieved from chunkdb files.
- L50 _public prototype_ `virtual ~IConstructorChunkDbChunkSource() = default;`
- L56 _public prototype_ `virtual const TSet<FGuid>& GetAvailableChunks() const = 0;` — Get the set of chunks available in the chunkdbs which were provided to the source. @return the set of chunks available.
- L60 _public prototype_ `static uint64 GetChunkDbSizesAtIndexes(const TArray<FString>& ChunkDbFiles, IFileSystem* FileSystem, const TArray<FGuid>& ChunkAccessOrderedList, const TArray<int32>& FileCompletionIndexes, TArray<uint64>& OutChunkDbSizesAtCompletion);` — Fill out how many bytes of chunkdbs are left if we delete all the ones that are no longer necessary at the given FileCompletionIndexes in to ChunkAccessOrderedList
- L63 _public prototype_ `virtual uint64 GetChunkDbSizesAtIndexes(const TArray<int32>& FileCompletionIndexes, TArray<uint64>& OutChunkDbSizesAtCompletion) const = 0;` — As above, except use the remaining open chunkdbs for progressive disk space checking.
- L65 _public prototype_ `virtual void ReportFileCompletion(int32 RemainingChunkCount) =0;`
- L66 _public prototype_ `virtual void TryTruncateFiles(int32 RemainingChunkCount) =0;`
- L68 _public prototype_ `static IConstructorChunkDbChunkSource* CreateChunkDbSource(FChunkDbSourceConfig&& Configuration, IFileSystem* FileSystem, const TArray<FGuid>& ChunkAccessOrderList, IChunkDataSerialization* ChunkDataSerialization, IChunkDbChunkSourceStat* ChunkDbChunkSourceStat);`

#### class `BuildPatchServices::IChunkDbChunkSourceStat`  
`class IChunkDbChunkSourceStat`  
_L76-128_
- desc: This interface defines the statistics class required by the chunkdb chunk source. It should be implemented in order to collect desired information which is being broadcast by the system.
- L104 _public prototype_ `virtual ~IChunkDbChunkSourceStat() = default;`
- L111 _public function_ `virtual void OnBatchStarted(const TArray<FGuid>& ChunkIds)` — `UE_DEPRECATED(5.6, "No longer batch loaded")` — Called when a batch of chunks are going to be loaded. @param ChunkIds  The ids of each chunk.
- L117 _public prototype_ `virtual void OnLoadStarted(const FGuid& ChunkId) = 0;` — Called each time a chunk load begins. @param ChunkId   The id of the chunk.
- L124 _public prototype_ `virtual void OnLoadComplete(const FGuid& ChunkId, ELoadResult Result) = 0;` — Called each time a chunk load completes. @param ChunkId   The id of the chunk. @param Result    The load result.
- L127 _public prototype_ `virtual void OnReadComplete(const ISpeedRecorder::FRecord& Record) = 0;` — Called when the read for the load is complete and we're moving on to decompression/hashing.

#### enum `BuildPatchServices::IChunkDbChunkSourceStat::ELoadResult`  
`enum class ELoadResult : uint8`  
_L82-101_
- desc: Enum which describes success, or the reason for failure when loading a chunk.
- L84 _public enumerator_ `Success = 0`
- L87 _public enumerator_ `MissingHashInfo_DEPRECATED` — The hash information was missing.
- L90 _public enumerator_ `HashCheckFailed_DEPRECATED` — The expected data hash for the chunk did not match.
- L93 _public enumerator_ `LocationOutOfBounds_DEPRECATED` — The chunkdb header specified an invalid chunk location offset or size.
- L97 _public enumerator_ `SerializationError` — An unexpected error during serialization. This includes header validation checks like whether the hash is present.
- L100 _public enumerator_ `CorruptedData` — Either the hash didn't match or the decompression call failed.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace BuildPatchServices`
- L133 _prototype_ `const TCHAR* ToString(const IChunkDbChunkSourceStat::ELoadResult& LoadResult);` (scope `BuildPatchServices`) — A ToString implementation for IChunkDbChunkSourceStat::ELoadResult.

### `Source/Runtime/Online/BuildPatchServices/Private/Installer/ChunkEvictionPolicy.h` (Private)


#### class `BuildPatchServices::IChunkEvictionPolicy`  
`class IChunkEvictionPolicy`  
_L15-29_
- desc: An interface providing decisions for cleaning and booting chunk data from stores.
- L18 _public prototype_ `virtual ~IChunkEvictionPolicy() = default;`
- L28 _public prototype_ `virtual void Query(const TMap<FGuid, TUniquePtr<IChunkDataAccess>>& CurrentMap, int32 DesiredMax, TSet<FGuid>& OutCleanable, TSet<FGuid>& OutBootable) const = 0;` — Query which chunks in a given set can be removed, or if necessary booted, in order to achieve the desired max count. It is possible to receive a decision of not evicting any data and thus expanding the data set past the desired max. @param CurrentMap    Reference to the full set of data to be considered. @param DesiredMax    The maximum number of chunks desired for the set of data. @param OutCleanable  Receives IDs for chunks which should be abandoned as they are no longer required. @param OutBootable   Receives IDs for chunks which would be preferable to remove, but are still required later.

#### class `BuildPatchServices::FChunkEvictionPolicyFactory`  
`class FChunkEvictionPolicyFactory`  
_L34-44_
- desc: A factory for creating an IChunkEvictionPolicy instance.
- L43 _public prototype_ `static IChunkEvictionPolicy* Create(IChunkReferenceTracker* ChunkReferenceTracker);` — This implementation uses a chunk reference tracker in order to make decisions about cleaning up unreferenced chunks, and booting out chunks that are not required for the longest time. @param ChunkReferenceTracker     Required ptr to a chunk reference tracker which will be used to make decisions. @return the new IChunkEvictionPolicy created.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Installer/ChunkReferenceTracker.h` (Private)


#### class `BuildPatchServices::IChunkReferenceTracker`  
`class IChunkReferenceTracker`  
_L14-89_
- desc: An interface for tracking references to chunks used throughout an installation. It is used to share across systems the chunks that are still required and when.
- L24 _public prototype_ `virtual ~IChunkReferenceTracker() = default;`
- L33 _public prototype_ `virtual TSet<FGuid> GetReferencedChunks() const = 0;` — Gets a set of all chunks referenced by the installation this tracker refers to. This returns the _remaining_ referenced chunks! Note that this does NOT return chunks in usage order anymore! If you were tacitly relying on the enumeration order of an unordered TSet, this likely broke! Use CopyOutOrderedUseList. @return set of GUID containing every chunk used.
- L40 _public prototype_ `virtual int32 GetReferenceCount(const FGuid& ChunkId) const = 0;` — Gets the number of times a specific chunk is still referenced for the associated installation. @param ChunkId           The id for the chunk in question. @return the number of references remaining.
- L47 _public prototype_ `virtual void SortByUseOrder(TArray<FGuid>& ChunkList, ESortDirection Direction) const = 0;` — Sorts a given array of chunk ids by the order in which they are required for the installation. @param ChunkList         The array to be sorted. @param Direction         The direction of sort. Ascending places soonest required chunk first.
- L55 _public prototype_ `virtual TArray<FGuid> GetNextReferences(int32 Count, const TFunction<bool(const FGuid&)>& SelectPredicate) const = 0;` — Find the next X chunk references that match the provided predicate. @param Count             The number of chunk entries that are desired. @param SelectPredicate   The predicate used to select each chunk. @return an array of unique chunk id entries, in the order in which they are required.
- L63 _public prototype_ `virtual TArray<FGuid> SelectFromNextReferences(int32 Count, const TFunction<bool(const FGuid&)>& SelectPredicate) const = 0;` — Select from the next X chunk references, entries that match the provided predicate. @param Count             The number of chunk entries to search through. @param SelectPredicate   The predicate used to select each chunk. @return an array of unique chunk id entries, in the order in which they are required.
- L75 _public prototype_ `virtual bool PopReference(const FGuid& ChunkId) = 0;` — Poorly named - Should be named "DoneWithChunk". The expectation is that we finish with chunks in the expected use order. Pop the top reference from the tracker, indicating that operation has been performed. It is not valid to pop anything but the top guid, so it must be provided for verification of behavior. @param ChunkId           The id of the top chunk, this is used to verify behavior. @return true if the correct guid was provided and the reference was popped, false if the wrong guid was provided and thus no change was made.
- L78 _public prototype_ `virtual int32 GetRemainingChunkCount() const = 0;` — Return how many chunks are left to process.
- L82 _public prototype_ `virtual void CopyOutOrderedUseList(TArray<FGuid>& OutUseList) const = 0;` — Return the ordered list we are consuming. copies the _remaining_ items!
- L86 _public prototype_ `virtual int32 GetNextUsageForChunk(const FGuid& ChunkId, int32& OutLastUsageIndex) const = 0;` — Returns the next usage index in _advancing order_ for the chunkid, or -1 if it won't be used again.
- L88 _public prototype_ `virtual int32 GetCurrentUsageIndex() const = 0;`

#### enum `BuildPatchServices::IChunkReferenceTracker::ESortDirection`  
`enum class ESortDirection : uint8`  
_L17-21_
- L19 _public enumerator_ `Ascending = 0`
- L20 _public enumerator_ `Descending`

#### class `BuildPatchServices::FChunkReferenceTrackerFactory`  
`class FChunkReferenceTrackerFactory`  
_L94-113_
- desc: A factory for creating an IChunkReferenceTracker instance.
- L104 _public prototype_ `static IChunkReferenceTracker* Create(const IBuildManifestSet* Manifest, const TSet<FString>& FilesToConstruct);` — This implementation takes the install manifest and generates the internal data and chunk reference tracking based off of a set of files that will be constructed. @param InstallManifest   The install manifest to enumerate references from. @param FilesToConstruct  The set of files to be installed, other files will not be considered. @return the new IChunkReferenceTracker instance created.
- L112 _public prototype_ `static IChunkReferenceTracker* Create(TArray<FGuid> CustomChunkReferences);` — This implementation takes custom chunk references to track. The array should be every chunk reference, including duplicates, in order of use. See namespace CustomChunkReferencesHelpers for common setup examples to use. @param CustomChunkReferences    The custom chunk references to track. @return the new IChunkReferenceTracker instance created.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace BuildPatchServices`
- L119 _namespace_ `namespace CustomChunkReferencesHelpers` (scope `BuildPatchServices`)
- L127 _function_ `FORCEINLINE TArray<FGuid> OrderedUniqueReferences(const FBuildPatchAppManifestRef& InstallManifest)` (scope `BuildPatchServices::CustomChunkReferencesHelpers`) — This implementation takes the install manifest and generates the CustomChunkReferences needed for a chunk reference tracker based on caching data and so using each chunk once in the order that would be required to install the build. @param InstallManifest   The install manifest to enumerate references from. @return the chunk use references for FChunkReferenceTrackerFactory::Create.
- L161 _function_ `FORCEINLINE TArray<FGuid> OrderedUniquePatchReferences(const FBuildPatchAppManifestRef& InstallManifest, const FBuildPatchAppManifestRef& CurrentManifest)` (scope `BuildPatchServices::CustomChunkReferencesHelpers`) — This implementation takes a new install manifest and a current manifest. It generates the CustomChunkReferences needed for a chunk reference tracker based on caching data for a patch only, and so using the chunks in InstallManifest, which are not in CurrentManifest, once each in the order that they would be required to patch the build. @param InstallManifest   The install manifest to enumerate chunk references from. @param CurrentManifest   The current manifest to exclude chunk references from. @return the chunk use references for FChunkReferenceTrackerFactory::Create.
- L200 _function_ `FORCEINLINE TArray<FGuid> OrderedUniqueReferencesTagged(const FBuildPatchAppManifestRef& InstallManifest, const TSet<FString>& InstallTagSet)` (scope `BuildPatchServices::CustomChunkReferencesHelpers`) — This implementation takes the install manifest and a tagset. It generates the CustomChunkReferences needed for a chunk reference tracker based on caching data and so using each chunk once in the order that would be required to install the build when using the same tagset provided. @param InstallManifest   The install manifest to enumerate references from. @param InstallTagSet     The tagset that would be used with install manifest, this will filter down required file list and thus required chunk list. @return the chunk use references for FChunkReferenceTrackerFactory::Create.
- L237 _function_ `FORCEINLINE TArray<FGuid> OrderedUniquePatchReferencesTagged(const FBuildPatchAppManifestRef& InstallManifest, const TSet<FString>& InstallTagSet, const FBuildPatchAppManifestRef& CurrentManifest, const TSet<FString>& CurrentTagSet)` (scope `BuildPatchServices::CustomChunkReferencesHelpers`) — This implementation takes a new install manifest, a current manifest, and a tagset for each. It generates the CustomChunkReferences needed for a chunk reference tracker based on caching data for a patch only, and so using the chunks in InstallManifest, which are not in CurrentManifest, once each in the order that would be required to patch the build when using the tagsets provided. @param InstallManifest   The install manifest to enumerate chunk references from. @param InstallTagSet     The tagset that would be used with install manifest, this will filter down required file list and thus required chunk list. @param CurrentManifest   The current manifest if considering an update, which reduces the number of chunks required. @param CurrentTagSet     The tagset filtering files from CurrentManifest, so that chunks would not be ignored for files not present on disk. This would often be the same as InstallTagSet unless InstallManifest changed the file tag names, or you are calling for purpose of adding/removing tags. @return the chunk use references for FChunkReferenceTrackerFactory::Create.

### `Source/Runtime/Online/BuildPatchServices/Private/Installer/ChunkSource.h` (Private)


#### class `BuildPatchServices::IConstructorChunkSource`  
`class IConstructorChunkSource`  
_L15-28_
- desc: This class is for providing chunks to a threaded file constructor that manages its own backing store.
- L18 _public prototype_ `virtual ~IConstructorChunkSource() = default;`
- L20 _public prototype_ `DECLARE_DELEGATE_FourParams(FChunkRequestCompleteDelegate, const FGuid& DataId, bool bAborted, bool bFailedToRead, void* UserPtr);`
- L22 _public typedef_ `typedef TUniqueFunction<void(bool bIsAborted)> FRequestProcessFn;`
- L24 _public prototype_ `virtual FRequestProcessFn CreateRequest(const FGuid& DataId, FMutableMemoryView DestinationBuffer, void* UserPtr, FChunkRequestCompleteDelegate CompleteFn) = 0;`
- L27 _public prototype_ `virtual int32 GetChunkUnavailableAt(const FGuid& DataId) const = 0;` — Return the reference index at which we can no longer get this data id from this source.

#### class `BuildPatchServices::IChunkSource`  
`class IChunkSource`  
_L33-66_
- desc: An interface providing basic access to retrieving chunk data.
- L36 _public prototype_ `virtual ~IChunkSource() = default;`
- L43 _public prototype_ `virtual IChunkDataAccess* Get(const FGuid& DataId) = 0;` — Gets the chunk data for the given id if this source has that chunk. @param DataId    The id for the chunk. @return pointer to the chunk data. or nullptr if this source does not contain the requested chunk.
- L51 _public prototype_ `virtual TSet<FGuid> AddRuntimeRequirements(TSet<FGuid> NewRequirements) = 0;` — Adds additional chunk requirements to the source, the implementation will return the resulting set of chunks that could not be accessed via this source. @param NewRequirements   The set of chunks that are now additionally desired. @return the set of chunks provided which can not be acquired via this chunk.
- L59 _public prototype_ `virtual bool AddRepeatRequirement(const FGuid& RepeatRequirement) = 0;` — Adds a requirement to reacquire a chunk that may have already been acquired before by this source. This allows the source implementation to to support forward reading of chunks, and track which it would not need to request. @param RepeatRequirement     The chunk that needs reacquiring. @return true if the chunk provided can be acquired by this source.
- L65 _public prototype_ `virtual void SetUnavailableChunksCallback(TFunction<void(TSet<FGuid>)> Callback) = 0;` — Sets a callback to be used when chunks that are being fetched by this source are no longer available. @param Callback          The function to call with the set of chunks no longer still available.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace BuildPatchServices`
- L20 _delegate_ `DECLARE_DELEGATE_FourParams(FChunkRequestCompleteDelegate, const FGuid& DataId, bool bAborted, bool bFailedToRead, void* UserPtr);`

### `Source/Runtime/Online/BuildPatchServices/Private/Installer/ChunkStore.h` (Private)


#### class `BuildPatchServices::IChunkStore`  
`class IChunkStore`  
_L14-61_
- desc: An interface providing access to storage of chunk data instances.
- L17 _public prototype_ `virtual ~IChunkStore() = default;`
- L27 _public prototype_ `virtual void Put(const FGuid& DataId, TUniquePtr<IChunkDataAccess> ChunkData) = 0;` — Put chunk data into this store. Chunk data unique ptr must be moved in, the store becomes the owner of the memory and its lifetime. Whether or not the call involves actually storing the data provided is implementation specific. It is possible to implement readonly/null IChunkStore. @param DataId    The GUID for the data. @param ChunkData The instance of the data. This must be moved in.
- L35 _public prototype_ `virtual IChunkDataAccess* Get(const FGuid& DataId) = 0;` — Get access to chunk data contained in this store. The returned data ptr is only valid until the next Get call, or a remove call for the same data. @param DataId    The GUID for the data. @return ptr to the data instance, or nullptr if this GUID was not in the store.
- L44 _public prototype_ `virtual TUniquePtr<IChunkDataAccess> Remove(const FGuid& DataId) = 0;` — Remove chunk data from this store. The data access is returned, this will cause destruction once out of scope. Whether or not the call involves actual data destruction is implementation specific. It is possible to implement readonly/null IChunkStore. @param DataId    The GUID for the data. @return the data instance referred to, or invalid if this GUID was not in the store.
- L50 _public prototype_ `virtual int32 GetSize() const = 0;` — Get the number of chunks this store can hold. For unsized stores, it is expected to return max int32 value. @return the store size.
- L60 _public prototype_ `virtual void SetLostChunkCallback(TFunction<void(const FGuid&)> Callback) = 0;` — Sets a callback to be used when chunks which have been Put, are lost. Examples of why this may occur: An eviction policy instructs the store to boot a chunk, but this store has no overflow store provided. (see IChunkEvictionPolicy::Query). The system backing this store (e.g. a file on disk storage) experiences a failure and the chunk could not be held. NB: The callback is not executed for a standard Clean instruction from an eviction policy. @param Callback  The function to call with the chunk that is no longer available.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Installer/CloudChunkSource.h` (Private)


#### struct `BuildPatchServices::FConstructorCloudChunkSourceConfig`  
`struct FConstructorCloudChunkSourceConfig`  
_L26-57_
- L29 _public member_ `TArray<FString> CloudRoots;` — An array of cloud root paths, supporting HTTP(s) and file access. HTTP(s) roots must begin with the protocol.
- L32 _public member_ `int32 MaxRetryCount = 6;` — The maximum number of times that a single chunk should retry, before registering a fatal error. Infinite can be specified as < 0.
- L35 _public member_ `TArray<float> RetryDelayTimes;` — Array of times in seconds, representing the time between each retry upon failure. The last entry will be used indefinitely once it is reached.
- L38 _public member_ `TArray<float> HealthPercentages;` — Configures what success rate values apply to which EBuildPatchDownloadHealth value, there should be EBuildPatchDownloadHealth::NUM_Values entries in this array.
- L40 _public member_ `float DisconnectedDelay = 5.0f;` — When all requests are failing, how many seconds before a success until we determine the state as disconnected.
- L44 _public member_ `uint64 DownloadRateLimitBps = 0;` — Maximum download speed in bytes per second. Infinite can be specified as 0.
- L46 _public function_ `FConstructorCloudChunkSourceConfig(const TArray<FString>& InCloudRoots) : CloudRoots(InCloudRoots)`

#### class `BuildPatchServices::IConstructorCloudChunkSource`  
`class IConstructorCloudChunkSource : public IConstructorChunkSource`  
_L59-80_
- inherits: `IConstructorChunkSource`
- L62 _public prototype_ `virtual ~IConstructorCloudChunkSource() = default;`
- L65 _public prototype_ `virtual void Abort() = 0;`
- L67 _public prototype_ `virtual void Tick(bool bStartNewDownloads, uint32& OutTimeToNextTickMs, uint32 InMaxDownloads) = 0;`
- L70 _public prototype_ `virtual void SetWakeupFunction(TUniqueFunction<void()>&& WakeupMainThreadFn) = 0;` — When downloads are complete we need a way to alert the main thread.
- L73 _public prototype_ `virtual void PostRequiredByteCount(uint64 InDownloadExpected) = 0;` — Pass in total download requirements for the install (including already completed downloads)
- L75 _public prototype_ `virtual void SetDownloadBytesPerSecondLimit(uint64 BytesPerSecondLimit) = 0;`
- L77 _public prototype_ `static IConstructorCloudChunkSource* CreateCloudSource(FConstructorCloudChunkSourceConfig&& Configuration, IDownloadService* InDownloadService, IChunkDataSerialization* InChunkDataSerialization, IDownloadConnectionCount* InDownloadCount, IMessagePump* InMessagePump, ICloudChunkSourceStat* InCloudChunkSourceStat, IBuildManifestSet* InManifestSet);`

#### class `BuildPatchServices::ICloudChunkSource`  
`class ICloudChunkSource : public IChunkSource , public IControllable`  
_L85-103_
- inherits: `IChunkSource,IControllable`
- desc: The interface for a cloud chunk source, which provides access to chunk data retrieved from provided cloud roots.
- L90 _public prototype_ `virtual ~ICloudChunkSource() = default;`
- L96 _public prototype_ `virtual void SetDownloadBytesPerSecondLimit(uint64 InDownloadRateLimitBps) = 0;` — Update the download rate limit. @param InDownloadRateLimitBps    The new maximum download rate in bytes per second. Infinite can be specified as 0.
- L102 _public prototype_ `virtual void ThreadRun() = 0;` — Should be called from the desired thread if bRunOwnThread is false. It will block until until aborted by the owning system.

#### struct `BuildPatchServices::FCloudSourceConfig`  
`struct FCloudSourceConfig`  
_L108-160_
- desc: A struct containing the configuration values for a cloud chunk source.
- L111 _public member_ `TArray<FString> CloudRoots;` — An array of cloud root paths, supporting HTTP(s) and file access. HTTP(s) roots must begin with the protocol.
- L114 _public member_ `int32 MaxRetryCount = 6;` — The maximum number of times that a single chunk should retry, before registering a fatal error. Infinite can be specified as < 0.
- L116 _public member_ `int32 RetriesToEnableVerbose;` — Number of retries to enable logging of http warnings.
- L118 _public member_ `int32 PreFetchMinimum = 16;` — The minimum number of chunks to request ahead of what is required, depending on store slack.
- L122 _public member_ `int32 PreFetchMaximum = 32;` — The maximum number of chunks to request ahead of what is required, depending on store slack. This shouldn't be too much because we'll queue too many on the same CDN which might not be good and we have to chew though a ton of requests before we swap over, and we only really want there to be one queued + one ready to go per connection anyway.
- L125 _public member_ `uint64 DownloadRateLimitBps = 0;` — Maximum download speed in bytes per second. Infinite can be specified as 0.
- L128 _public member_ `TArray<float> RetryDelayTimes;` — Array of times in seconds, representing the time between each retry upon failure. The last entry will be used indefinitely once it is reached.
- L131 _public member_ `TArray<float> HealthPercentages;` — Configures what success rate values apply to which EBuildPatchDownloadHealth value, there should be EBuildPatchDownloadHealth::NUM_Values entries in this array.
- L133 _public member_ `float DisconnectedDelay = 5.0f;` — When all requests are failing, how many seconds before a success until we determine the state as disconnected.
- L136 _public member_ `bool bBeginDownloadsOnFirstGet = true;` — If true, the downloads will not begin until the first Get request is made. It is fairly fundamental to stop downloads of chunks until resume data is processed, but can be special case disabled.
- L138 _public member_ `float TcpZeroWindowMinimumSeconds = 20.0f;` — The minimum time to allow a http download before assessing it as affected by TCP zero window issue.
- L140 _public member_ `IBuildInstallerSharedContext* SharedContext = nullptr;` — The context for allocating shared resources.
- L142 _public member_ `bool bRunOwnThread = true;` — Whether cloud source should run its own thread. If true, SharedContext is required.
- L148 _public function_ `FCloudSourceConfig(const TArray<FString>& InCloudRoots) : CloudRoots(InCloudRoots) , RetriesToEnableVerbose(MaxRetryCount - 1)` — Constructor which sets usual defaults, and takes params for values that cannot use a default. @param InCloudRoots  The cloud roots array

#### class `BuildPatchServices::FCloudChunkSourceFactory`  
`class FCloudChunkSourceFactory`  
_L165-199_
- desc: A factory for creating an ICloudChunkSource instance.
- L187 _public prototype_ `static ICloudChunkSource* Create(FCloudSourceConfig Configuration, IPlatform* Platform, IChunkStore* ChunkStore, IDownloadService* DownloadService, IChunkReferenceTracker* ChunkReferenceTracker, IChunkDataSerialization* ChunkDataSerialization, IMessagePump* MessagePump, IInstallerError* InstallerError, IDownloadConnectionCount* InConnectionCount, ICloudChunkSourceStat* CloudChunkSourceStat, IBuildManifestSet* ManifestSet, TSet<FGuid> InitialDownloadSet);` — This implementation requests chunks from a list of cloud sources, which is iterated as failures occur. It supports a configurable number of simultaneous requests, pre-fetching of chunks which are required next, depending on store slack, and tracking of success rates. A chunk can be requested which was not in the initial set, and it will be downloaded as a priority. @param Configuration             The configuration struct for this cloud source. @param Platform                  The platform access interface. @param ChunkStore                The chunk store where received chunks will be put. @param DownloadService           The service used to request each chunk via url. @param ChunkReferenceTracker     The reference tracker for the installation, used to decide which chunks to fetch and when. @param ChunkDataSerialization    Chunk data serialization implementation for converting downloaded bytes into chunk data. @param MessagePump               The message pump to receive messages about source events. @param InstallerError            Error tracker where fatal errors will be reported. @param ConnectionCount           The class that provides an approximately optimal number of simultaneous download connections @param CloudChunkSourceStat      The class to receive statistics and event information. @param InstallManifest           The manifest that chunks are required for. @param InitialDownloadSet        The initial set of chunks to be sourced from cloud. @return the new ICloudChun

#### class `BuildPatchServices::ICloudChunkSourceStat`  
`class ICloudChunkSourceStat`  
_L205-310_
- desc: This interface defines the statistics class required by the cloud source. It should be implemented in order to collect desired information which is being broadcast by the system.
- L208 _public prototype_ `virtual ~ICloudChunkSourceStat() = default;`
- L214 _public prototype_ `virtual void OnDownloadRequested(const FGuid& ChunkId) = 0;` — Called whenever a chunk download request is made. @param ChunkId           The id of the chunk.
- L220 _public prototype_ `virtual void OnDownloadSuccess(const FGuid& ChunkId) = 0;` — Called whenever a chunk download request has succeeded. @param ChunkId           The id of the chunk.
- L227 _public prototype_ `virtual void OnDownloadFailed(const FGuid& ChunkId, const FString& Url) = 0;` — Called whenever a chunk download request has failed. @param ChunkId           The id of the chunk. @param Url               The url used to request the chunk.
- L235 _public prototype_ `virtual void OnDownloadCorrupt(const FGuid& ChunkId, const FString& Url, EChunkLoadResult LoadResult) = 0;` — Called whenever a chunk download request succeeded but the data was not valid. @param ChunkId           The id of the chunk. @param Url               The url used to request the chunk. @param LoadResult        The result from attempting to serialize the downloaded data.
- L246 _public prototype_ `virtual void OnDownloadAborted(const FGuid& ChunkId, const FString& Url, double DownloadTimeMean, double DownloadTimeStd, double DownloadTime, double BreakingPoint) = 0;` — Called whenever a chunk was aborted because it was determined as taking too long. @param ChunkId           The id of the chunk. @param Url               The url used to request the chunk. @param DownloadTimeMean  The current mean time for chunk downloads when this abort was made. @param DownloadTimeStd   The current standard deviation for chunk download times when this abort was made. @param DownloadTime      The time this request had been running for. @param BreakingPoint     The calculated breaking point which this request has overran.
- L252 _public prototype_ `virtual void OnReceivedDataUpdated(int64 TotalBytes) = 0;` — Called to update the amount of bytes which have been downloaded. @param TotalBytes        The number of bytes downloaded so far.
- L259 _public prototype_ `virtual void OnRequiredDataUpdated(int64 TotalBytes) = 0;` — Called whenever the total number of bytes intended to download updates. This can occur after initialization if a chunk is requested which was not in the original list. @param TotalBytes        The number of bytes downloaded so far.
- L265 _public prototype_ `virtual void OnDownloadHealthUpdated(EBuildPatchDownloadHealth DownloadHealth) = 0;` — Called whenever the perceived download health changes, according to the provided configuration. @param DownloadHealth    The new download health value.
- L272 _public prototype_ `virtual void OnSuccessRateUpdated(float SuccessRate) = 0;` — Called whenever the success rate of requests has been updated. @param SuccessRate       The new success rate value, when 1.0 is all requests made so far have been successful, and 0.0 is all requests failed so far.
- L278 _public prototype_ `virtual void OnActiveRequestCountUpdated(uint32 RequestCount) = 0;` — Called whenever the current number of active requests updates. @param RequestCount      The number of currently active requests, this will range between 0 and NumSimultaneousDownloads config.
- L284 _public prototype_ `virtual void OnActiveRequestCountAvgUpdated(int32 AverageRequestCount) = 0;` — Called once per second whenever there has been an active request. @param AverageRequestCount      The average number of active requests that there has currently been.
- L290 _public prototype_ `virtual void OnAcceptedNewRequirements(const TSet<FGuid>& ChunkIds) = 0;` — Called when a batch of chunks are added and accepted via IChunkSource::AddRuntimeRequirements. @param ChunkIds  The ids of each chunk.
- L296 _public prototype_ `virtual void OnChunkDecrypted(uint64 DecryptionCycles) = 0;` — Called when a chunk is decrypted. @param DecryptionCycles  The amount of cycles spent on decryption a chunk.
- L303 _public prototype_ `virtual void OnCloudDirectoryDataReceived(const FString& CloudDirectory, uint64 ReceivedData) = 0;` — Called when new data has been received from the given cloud directory. @param CloudDirectory  The identifier for this cloud directory, e.g. base URL. @param ReceivedData    The number of bytes received from this cloud directory.
- L309 _public prototype_ `virtual void OnCloudDirectoryError(const FString& CloudDirectory) = 0;` — Called when a download from the given cloud directory has failed. @param CloudDirectory  The identifier for this cloud directory, e.g. base URL.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Installer/Controllable.h` (Private)


#### class `BuildPatchServices::IControllable`  
`class IControllable`  
_L9-29_
- desc: Defines the interface to be implemented by any controllable class.
- L12 _public prototype_ `virtual ~IControllable() = default;`
- L18 _public prototype_ `virtual void SetPaused(bool bIsPaused) = 0;` — Sets whether the class should pause current activities and wait. @param bIsPaused     True if the class should pause.
- L23 _public prototype_ `virtual void Abort() = 0;` — Called to instruct the class to cease all activity, and perform any shutdown.
- L28 _public prototype_ `virtual void Reset() = 0;` — Return to default state without destructing the object.

#### Free symbols / members of external scopes

- L4 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Installer/CustomUninstallAction.h` (Private)


#### class `BuildPatchServices::ICustomUninstallAction`  
`class ICustomUninstallAction`  
_L17-33_
- L21 _public function_ `virtual ~ICustomUninstallAction()`
- L32 _public prototype_ `virtual bool RunAction(const IBuildManifestSet* ManifestSet, const FBuildInstallerConfiguration& Configuration, const FString& InstallStagingDir, FBuildPatchProgress& BuildProgress) const = 0;` — ICustomUninstallAction - RunAction Runs custom uninstall action associated with the installation. @param BuildManifest       The manifest containing details of the installer. @param Configuration       The installer configuration structure. @param InstallStagingDir   The directory within staging to construct install files to. @param BuildProgress       Used to keep track of install progress. @return                    Returns true if the custom uninstall action executable succeeded, false otherwise.

#### class `BuildPatchServices::FCustomUninstallActionFactory`  
`class FCustomUninstallActionFactory`  
_L35-47_
- L46 _public prototype_ `static ICustomUninstallAction* Create(IInstallerError* InstallerError, IFileSystem* FileSystem, IPlatform* Platform);` — FCustomUninstallActionFactory - Create Creates an instance of ICustomUninstallAction. @param InstallerError          The error handling implementation which any installation errors will be reported to. @param FileSystem              An abstraction representing the filesystem. @param Platform                An abstraction providing access to platform operations. @return the new ICustomUninstallAction instance created.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Installer/DownloadConnectionCount.h` (Private)


#### class `BuildPatchServices::IDownloadConnectionCount`  
`class IDownloadConnectionCount`  
_L16-34_
- desc: An interface for scaling the number of simultaneous download connections
- L25 _public prototype_ `virtual uint32 GetAdjustedCount(uint32 NumProcessing, EBuildPatchDownloadHealth CurrentHealth) = 0;` — Get the number of simultaneous download connections @param NumProcessing -- the current number of downloads in-flight @param CurrentHealth -- percentage of downloads that have failed since last call to this function, in terms of "health" @return number of connections that should be approximately optimal.
- L31 _public prototype_ `virtual void SetConnectionScaling(bool bEnableScaling) = 0;` — Set whether connection scaling is enabled. @param bEnableScaling -- Enables download scaling, true to enable.
- L33 _public prototype_ `virtual ~IDownloadConnectionCount() = default;`

#### struct `BuildPatchServices::FDownloadConnectionCountConfig`  
`struct FDownloadConnectionCountConfig`  
_L37-87_
- L40 _public member_ `uint32 MaxLimit;` — Maximum number of simultaneous connections to be used.
- L42 _public member_ `uint32 MinLimit;` — Minimum number of connections to be used.
- L44 _public member_ `uint32 NegativeHysteresis;` — How many consecutive decreases in speed must be encountered before the count is changed.
- L46 _public member_ `uint32 AverageSpeedMinCount;` — Minimum number of samples needed that constitutes a useful average speed.
- L48 _public member_ `uint32 PositiveHysteresis;` — How many consecutive increases in speed must be encountered before the count is changed.
- L50 _public member_ `double HighBandwidthFactor;` — Percentage of highest seen speed that must be exceeded before the count is changed
- L52 _public member_ `double LowBandwidthFactor;` — Percentage of highest seen speed that must be fallen short of before the count is changed
- L54 _public member_ `bool bDisableConnectionScaling;` — Enable or disable download scaling.
- L56 _public member_ `uint32 FallbackCount;` — The number of connections to allow when dynamic scaling is disabled
- L58 _public member_ `uint32 HealthHysteresis;` — How many consecutive poor download health status checks must be encountered before the count is changed.
- L60 _public function_ `FDownloadConnectionCountConfig() : MaxLimit(100U) , MinLimit(8U) , NegativeHysteresis(8U) , AverageSpeedMinCount(8U) , PositiveHysteresis(4U) , HighBandwidthFactor(0.85L) , LowBandwidthFactor(0.65L) , bDisableConnectionScaling(false) , FallbackCount(16) , HealthHysteresis(8)`
- L73 _public function_ `FDownloadConnectionCountConfig(const FDownloadConnectionCountConfig& CopyThis) : MaxLimit(CopyThis.MaxLimit) , MinLimit(CopyThis.MinLimit) , NegativeHysteresis(CopyThis.NegativeHysteresis) , AverageSpeedMinCount(CopyThis.AverageSpeedMinCount) , PositiveHysteresis(CopyThis.PositiveHysteresis) , HighBandwidthFactor(CopyThis.HighBandwidthFactor) , LowBandwidthFactor(CopyThis.LowBandwidthFactor) , bDisableConnectionScaling(CopyThis.bDisableConnectionScaling) , FallbackCount(CopyThis.FallbackCount) , HealthHysteresis(CopyThis.HealthHysteresis)`

#### class `BuildPatchServices::FDownloadConnectionCountFactory`  
`class FDownloadConnectionCountFactory`  
_L89-98_
- L97 _public prototype_ `static IDownloadConnectionCount* Create(FDownloadConnectionCountConfig Configuration, IDownloadServiceStatistics* InDownloadStatistics);` — Create a download connection count calculator. @param Configuration -- configuration values. @param InDownloadStatistics -- A download statistics object. Can be null. If null, the object will use an implementation that does not take into account download speed changes.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Installer/DownloadService.h` (Private)


#### class `BuildPatchServices::IDownload`  
`class IDownload`  
_L19-47_
- desc: An interface providing access to the result of a download.
- L22 _public prototype_ `virtual ~IDownload() = default;`
- L28 _public prototype_ `virtual bool RequestSuccessful() const = 0;` — Gets whether the request was successfully made. @return true for success.
- L34 _public prototype_ `virtual bool ResponseSuccessful() const = 0;` — Gets whether the response was received and indicated good status. @return true for success.
- L40 _public prototype_ `virtual int32 GetResponseCode() const = 0;` — Gets the response code, or INDEX_NONE if response failed. @return the response code.
- L46 _public prototype_ `virtual const TArray<uint8>& GetData() const = 0;` — Get a reference to the downloaded data held by this class. @return reference to downloaded bytes.

#### class `BuildPatchServices::IDownloadService`  
`class IDownloadService`  
_L67-96_
- desc: An interface providing access to download files, supporting http(s) and network protocols.
- L70 _public prototype_ `virtual ~IDownloadService() = default;`
- L80 _public prototype_ `virtual bool RequestFile(const FString& FileUri, const FDownloadCompleteDelegate& OnCompleteDelegate, const FDownloadProgressDelegate& OnProgressDelegate, int32* OutRequestId = nullptr) = 0;` — Starts a new request for a file. @param FileUri               The uri for the file request. For http(s), this should begin with the protocol. @param OnCompleteDelegate    The delegate that will be called with the completed download. @param OnProgressDelegate    The delegate that will be called with updates to the ongoing download. @param OutRequestId          The request id for this download, which will match that provided to the delegates. @return if the request was queued successfully.
- L83 _public prototype_ `virtual bool RequestFileWithHeaders(const FString& FileUri, const TMap<FString, FString>& RequestHeaders, const FDownloadCompleteDelegate& OnCompleteDelegate, const FDownloadProgressDelegate& OnProgressDelegate, int32* OutRequestId = nullptr) = 0;` — As per RequestFile, except adds the given headers to the request as a <Name, Value> pair.
- L89 _public prototype_ `virtual void RequestCancel(int32 RequestId) = 0;` — Requests the cancellation of a requested file. @param RequestId             The id that was returned by the call to RequestFile which should be canceled.
- L95 _public prototype_ `virtual void RequestAbandon(int32 RequestId) = 0;` — Requests the abandoning of a requested file (cancelling without calling complete/progress handlers) @param RequestId             The id that was returned by the call to RequestFile which should be canceled.

#### class `BuildPatchServices::FDownloadServiceFactory`  
`class FDownloadServiceFactory`  
_L101-113_
- desc: A factory for creating the default implementation of IDownloadService.
- L112 _public prototype_ `static IDownloadService* Create(TSharedPtr<IHttpManager> HttpManager, TSharedPtr<IFileSystem> FileSystem, TSharedPtr<IDownloadServiceStat> DownloadServiceStat, TSharedPtr<IInstallerAnalytics> InstallerAnalytics);` — Instantiates an instance of an IDownloadService, using the HTTP module, and platform file API. @param HttpManager           The HTTP manager interface for making HTTP(s) requests. @param FileSystem            The file system interface for network and disk file loading. @param DownloadServiceStat   The class to receive statistics and event information. @param InstallerAnalytics    The analytics implementation for tracking HTTP requests. @return the new IDownloadService instance created.

#### class `BuildPatchServices::IDownloadServiceStat`  
`class IDownloadServiceStat`  
_L119-162_
- desc: This interface defines the statistics class required by the download service. It should be implemented in order to collect desired information which is being broadcast by the system.
- L122 _public prototype_ `virtual ~IDownloadServiceStat() = default;`
- L148 _public prototype_ `virtual void OnDownloadStarted(int32 RequestId, const FString& Uri) = 0;` — Called as each request has started. @param RequestId             The id for the request. @param Uri                   The uri for the request.
- L155 _public prototype_ `virtual void OnDownloadProgress(int32 RequestId, uint64 BytesReceived) = 0;` — Called for each request completion. @param RequestId             The id for the request. @param BytesReceived         The bytes received so far.
- L161 _public prototype_ `virtual void OnDownloadComplete(const FDownloadRecord& DownloadRecord) = 0;` — Called for each request completion. @param DownloadRecord        The struct containing the stats for this request.

#### struct `BuildPatchServices::IDownloadServiceStat::FDownloadRecord`  
`struct FDownloadRecord`  
_L127-141_
- desc: A struct containing the information about a completed request.
- L130 _public member_ `int32 RequestId;` — The id for the request that was made.
- L132 _public member_ `FString Uri;` — The uri used when making the request.
- L134 _public member_ `bool bSuccess;` — Whether the request completed successfully.
- L136 _public member_ `int32 ResponseCode;` — The response code for the request.
- L138 _public member_ `ISpeedRecorder::FRecord SpeedRecord;` — The timing record.
- L140 _public member_ `EHttpFailureReason FailureReason;` — If failed, the reason why the request failed

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace BuildPatchServices`
- L48 _typedef_ `typedef TSharedRef<IDownload, ESPMode::ThreadSafe> FDownloadRef;` (scope `BuildPatchServices`)
- L55 _delegate_ `DECLARE_DELEGATE_TwoParams(FDownloadProgressDelegate, int32 , uint64 );` — Delegate called for download progress updates. @param RequestId     The id that was returned by RequestFile(..). @param BytesSoFar    The number of bytes received so far.
- L55 _prototype_ `DECLARE_DELEGATE_TwoParams(FDownloadProgressDelegate, int32 , uint64 );` (scope `BuildPatchServices`) — Delegate called for download progress updates. @param RequestId     The id that was returned by RequestFile(..). @param BytesSoFar    The number of bytes received so far.
- L62 _delegate_ `DECLARE_DELEGATE_TwoParams(FDownloadCompleteDelegate, int32 , const FDownloadRef& );` — Delegate called for download complete. @param RequestId     The id that was returned by RequestFile(..). @param Download      The complete download instance.
- L62 _prototype_ `DECLARE_DELEGATE_TwoParams(FDownloadCompleteDelegate, int32 , const FDownloadRef& );` (scope `BuildPatchServices`) — Delegate called for download complete. @param RequestId     The id that was returned by RequestFile(..). @param Download      The complete download instance.

### `Source/Runtime/Online/BuildPatchServices/Private/Installer/FileAttribution.h` (Private)


#### class `BuildPatchServices::IFileAttribution`  
`class IFileAttribution : public IControllable`  
_L15-24_
- inherits: `IControllable`
- L23 _public prototype_ `virtual bool ApplyAttributes() = 0;` — Applies the attributes to the files in the Staging directory, or installation directory. @return true is successful.

#### class `BuildPatchServices::FFileAttributionFactory`  
`class FFileAttributionFactory`  
_L26-44_
- L42 _public prototype_ `static IFileAttribution* Create(IFileSystem* FileSystem, IBuildManifestSet* ManifestSet, TSet<FString> TouchedFiles, const FString& InstallDirectory, const FString& StagedFileDirectory, FBuildPatchProgress* BuildProgress, const TMap<FString, FString>& PerFileSubdirectories);` — Creates a file attribute class that can be used to setup file attributes that are contained in the build manifest, optionally taking account of a staging directory where alternative files are. @param FileSystem            The file system interface. @param NewManifest           The manifest describing the build data. @param OldManifest           The manifest describing the build data. @param TouchedFiles          The set of files that were touched by the installation, these will filter the list of actions performed when not forcing. @param InstallDirectory      The directory to analyze. @param StagedFileDirectory   A stage directory for updated files, ignored if empty string. If a file exists here, it will be checked instead of the one in InstallDirectory. @param BuildProgress         The build progress class to update with progress information. @return     Ref of an object that can be used to perform the operation.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Installer/InstallChunkSource.h` (Private)


#### class `BuildPatchServices::IConstructorInstallChunkSource`  
`class IConstructorInstallChunkSource : public IConstructorChunkSource`  
_L24-57_
- inherits: `IConstructorChunkSource`
- desc: The interface for an installation chunk source, which provides access to chunk data retrieved from known local installations.
- L27 _public prototype_ `virtual ~IConstructorInstallChunkSource() = default;`
- L30 _public prototype_ `virtual const TSet<FGuid>& GetAvailableChunks() const = 0;` — Return the chunks this source can provide.
- L33 _public prototype_ `virtual void OnBeforeDeleteFile(const FString& FilePath) = 0;` — Notification that a file is about to be deleted so we need to clear out any references.
- L37 _public prototype_ `virtual void GetChunksForFile(const FString& InstallationDirectory, const FString& FilenameInManifest, TSet<FGuid>& OutChunks) const = 0;` — Return the list of chunks for a file so that the constructor can harvest them before the file is deleted
- L40 _public prototype_ `virtual void EnumerateFilesForChunk(const FGuid& DataId, TUniqueFunction<void(const FString& NormalizedInstallDirectory, const FString& NormalizedFileName)>&& Callback) const = 0;` — Call the lambda on each file the chunk needs to load bits from.
- L44 _public prototype_ `virtual void SetFileRetirementPositions(TMap<FString, int32>&& FileRetirementPositions) = 0;` — Tell the install source when files will be going away so we can report when chunks are unavailable. This should be the ChunkReferenceTracker->GetCurrentUsageIndex at which the files will get deleted.
- L50 _public prototype_ `static IConstructorInstallChunkSource* CreateInstallSource( IFileSystem* FileSystem, IInstallChunkSourceStat* InstallChunkSourceStat, const TMultiMap<FString, FBuildPatchAppManifestRef>& InstallationSources, const TSet<FGuid>& ChunksThatWillBeNeeded, bool bAllowLoadingAnyChunk, const TMap<FString, FString>& InPerFileSubdirectories);` — InstallationSources is the install manifest for each installed app that we can pull from. This is expected to be a single entry. LONGTERM question -- how does this work during delta generation? It is expected that all apps are installed and chunks are pulled from everything?

#### class `BuildPatchServices::IInstallChunkSourceStat`  
`class IInstallChunkSourceStat`  
_L63-125_
- desc: This interface defines the statistics class required by the install chunk source. It should be implemented in order to collect desired information which is being broadcast by the system.
- L96 _public prototype_ `virtual ~IInstallChunkSourceStat() = default;`
- L103 _public function_ `virtual void OnBatchStarted(const TArray<FGuid>& ChunkIds)` — `UE_DEPRECATED(5.6, "No longer batch loaded")` — Called when a batch of chunks are going to be loaded. @param ChunkIds  The ids of each chunk.
- L109 _public prototype_ `virtual void OnLoadStarted(const FGuid& ChunkId) = 0;` — Called each time a chunk load begins. @param ChunkId   The id of the chunk.
- L117 _public prototype_ `virtual void OnLoadComplete(const FGuid& ChunkId, const ELoadResult& Result, const ISpeedRecorder::FRecord& Record) = 0;` — Called each time a chunk load completes. @param ChunkId   The id of the chunk. @param Result    The load result. @param Record    The recording for the received data.
- L124 _public function_ `virtual void OnAcceptedNewRequirements(const TSet<FGuid>& ChunkIds)` — `UE_DEPRECATED(5.6, "No longer batch loaded")` — Called when a batch of chunks are added and accepted via IChunkSource::AddRuntimeRequirements. @param ChunkIds  The ids of each chunk.

#### enum `BuildPatchServices::IInstallChunkSourceStat::ELoadResult`  
`enum class ELoadResult : uint8`  
_L69-93_
- desc: Enum which describes success, or the reason for failure when loading a chunk.
- L71 _public enumerator_ `Success = 0`
- L74 _public enumerator_ `MissingHashInfo` — The hash information was missing.
- L77 _public enumerator_ `MissingPartInfo` — Chunk part information was missing.
- L80 _public enumerator_ `OpenFileFail` — Failed to open a source file.
- L83 _public enumerator_ `IncorrectFileSize_DEPRECATED` — The expected source file size was not matched.
- L86 _public enumerator_ `HashCheckFailed` — The expected data hash for the chunk did not match.
- L89 _public enumerator_ `Aborted` — The process has been aborted.
- L92 _public enumerator_ `InvalidChunkParts` — Invalid assemble structure (i.e. overlapping chunk parts)

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace BuildPatchServices`
- L130 _prototype_ `const TCHAR* ToString(const IInstallChunkSourceStat::ELoadResult& LoadResult);` (scope `BuildPatchServices`) — A ToString implementation for IInstallChunkSourceStat::ELoadResult.

### `Source/Runtime/Online/BuildPatchServices/Private/Installer/InstallerAnalytics.h` (Private)


#### class `BuildPatchServices::IInstallerAnalytics`  
`class IInstallerAnalytics`  
_L16-145_
- desc: An interface to event recording implementation.
- L19 _public prototype_ `virtual ~IInstallerAnalytics() = default;`
- L34 _public prototype_ `virtual void RecordChunkDownloadError(const FString& ChunkUrl, int32 ResponseCode, const FString& ErrorString) = 0;` — @EventName Patcher.Error.Download @Trigger Fires for the first 20 chunk download errors that occur. Deprecated: Not recommended for use. @Type Client @EventParam ChunkURL     (string) The url used to request the chunk. @EventParam ResponseCode (int32)  The HTTP response code received, or OS error code for file operation. @EventParam ErrorString  (string) The stage at which the chunk was deemed error. "Download Fail", "Uncompress Fail", "Verify Fail", or "SaveToDisk Fail". @Owner Portal Team
- L48 _public prototype_ `virtual void RecordMissingDelta(const FString& DeltaUrl, const FString& BaseVersion, const FString& PatchVersion) = 0;` — @EventName Patcher.Error.Delta @Trigger Fires for delta files that return 403/404 http response codes @Type Client @EventParam DeltaUrl		(string) The url used to request the delta file @EventParam BaseVersion	(string) The base (installed) version of the app @EventParam PatchVersion	(string) The version of the app that is being upgraded to @Owner Portal Team
- L65 _public prototype_ `virtual void RecordChunkDownloadAborted(const FString& ChunkUrl, double ChunkTime, double ChunkMean, double ChunkStd, double BreakingPoint) = 0;` — @EventName Patcher.Warning.ChunkAborted @Trigger Fires for chunks that were aborted as deemed failing. This is a prediction that the chunk is suffering from 0-byte TCP window issue. Deprecated: Not recommended for use. @Type Client @EventParam ChunkURL      (string) The url used to request the chunk. @EventParam ChunkTime     (double) The amount of time the chunk has been downloading for in seconds. @EventParam ChunkMean     (double) The current mean average chunk download time in seconds. @EventParam ChunkStd      (double) The current standard deviation of chunk download times. @EventParam BreakingPoint (double) The time at which a chunk will be aborted based on the current mean and std. @Owner Portal Team
- L82 _public prototype_ `virtual void RecordChunkCacheError(const FGuid& ChunkGuid, const FString& Filename, int32 LastError, const FString& SystemName, const FString& ErrorString) = 0;` — @EventName Patcher.Error.Cache @Trigger Fires for the first 20 chunks which experienced a cache error. Deprecated: Not recommended for use. @Type Client @EventParam ChunkGuid   (string) The guid of the effected chunk. @EventParam Filename    (string) The filename used if appropriate, or -1. @EventParam LastError   (int32)  The OS error code if appropriate. @EventParam SystemName  (string) The cache sub-system that is reporting this. "ChunkBooting", "ChunkRecycle", "DriveCache". @EventParam ErrorString (string) The stage at which the chunk was deemed error. "Hash Check Failed", "Incorrect File Size", "Datasize/Hashtype Mismatch", "Corrupt Header", "Open File Fail", "Source File Missing", "Source File Too Small", "Chunk Hash Fail", or "Chunk Save Failed". @Owner Portal Team
- L97 _public prototype_ `virtual void RecordConstructionError(const FString& Filename, int32 LastError, const FString& ErrorString) = 0;` — @EventName Patcher.Error.Construction @Trigger Fires for the first 20 errors experienced while constructing an installation file. Deprecated: Not recommended for use. @Type Client @EventParam Filename    (string) The filename of the installation file. @EventParam LastError   (int32)  The OS error code if appropriate, or -1. @EventParam ErrorString (string) The reason the error occurred. "Missing Chunk", "Not Enough Disk Space", "Could Not Create File", "Missing File Manifest", "Serialised Verify Fail", "File Data Missing", "File Data Uncompress Fail", "File Data Verify Fail", "File Data GUID Mismatch", "File Data Part OOB", "File Data Unknown Storage", or "Failed To Move". @Owner Portal Team
- L115 _public prototype_ `virtual void RecordPrereqInstallationError(const FString& AppName, const FString& AppVersion, const FString& Filename, const FString& CommandLine, int32 ErrorCode, const FString& ErrorString) = 0;` — @EventName Patcher.Error.Prerequisites @Trigger Fires for errors experienced while installing prerequisites. Deprecated: Not recommended for use. @Type Client @EventParam AppName     (string) The app name for the installation that is running. @EventParam AppVersion  (string) The app version for the installation that is running. @EventParam Filename    (string) The filename used when running prerequisites. @EventParam CommandLine (string) The command line used when running prerequisites. @EventParam ReturnCode  (int32)  The error or return code from running the prerequisite. @EventParam ErrorString (string) The action that failed. "Failed to start installer", or "Failed to install". @Owner Portal Team
- L139 _public prototype_ `virtual void TrackRequest(const FHttpRequestPtr& Request) = 0;` — @EventName CDN.Chunk @Trigger Fires aggregate events for HTTP requests made for BuildPatchServices installers. @Type Dynamic @EventParam Code-XXX                  (int32)  The count for this HTTP response code, where XXX in the event name is the code. @EventParam DomainName                (string) The domain name used for the requests in this aggregate. @EventParam SuccessCount              (int32)  The count of request successes. @EventParam FailCount                 (int32)  The count of request failures. @EventParam DownloadBytesSuccessTotal (int64)  The number of bytes received by successful responses. @EventParam DownloadBytesFailTotal    (int64)  The number of bytes received by failed responses. @EventParam ElapsedTimeSuccessTotal   (float)  The total seconds elapsed for successful requests in this aggregate. @EventParam ElapsedTimeSuccessMin     (float)  The minimum seconds elapsed for successful request in this aggregate. @EventParam ElapsedTimeSuccessMax     (float)  The maximum seconds elapsed for successful request in this aggregate. @EventParam ElapsedTimeFailTotal      (float)  The total seconds elapsed for failed requests in this aggregate. @EventParam ElapsedTimeFailMin        (float)  The minimum seconds elapsed for failed request in this aggregate. @EventParam ElapsedTimeFailMax        (float)  The maximum seconds elapsed for failed request in this aggregate. @Owner Portal Team
- L144 _public prototype_ `virtual void Flush() = 0;` — Ensures that any queued analytics are sent immediately.

#### class `BuildPatchServices::FInstallerAnalyticsFactory`  
`class FInstallerAnalyticsFactory`  
_L150-159_
- desc: A factory for creating an IInstallerAnalytics instance.
- L158 _public prototype_ `static IInstallerAnalytics* Create(IAnalyticsProvider* AnalyticsProvider);` — Creates an instance of an installer analytics handler, for use by other classes which report the events. @param AnalyticsProvider The analytics provider interface. @return the new IInstallerAnalytics instance created.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Installer/InstallerError.h` (Private)


#### class `BuildPatchServices::IInstallerError`  
`class IInstallerError`  
_L156-227_
- desc: An interface to fatal error implementation used to report an error or get informed of other errors occurring.
- L159 _public typedef_ `typedef TFunction<void()> FOnErrorDelegate;`
- L162 _public prototype_ `virtual ~IInstallerError() = default;`
- L168 _public prototype_ `virtual bool HasError() const = 0;` — Get if there has been a fatal error reported. @return true if a fatal error has been set.
- L174 _public prototype_ `virtual bool IsCancelled() const = 0;` — Get whether an error reported is a cancellation request. @return true if the error which is set is a cancellation.
- L180 _public prototype_ `virtual bool CanRetry() const = 0;` — Get whether the reported error is one which should be capable of recovering with an installation retry. @return true if the installation can retry.
- L186 _public prototype_ `virtual EBuildPatchInstallError GetErrorType() const = 0;` — Get the enum value for the error which has been reported. @return the reported enum value.
- L192 _public prototype_ `virtual FString GetErrorCode() const = 0;` — Get the error code string for the error which has been reported. @return the reported error code string.
- L198 _public prototype_ `virtual FText GetErrorText() const = 0;` — Get the default display text for the error which has been reported. @return the reported error's default display text.
- L207 _public prototype_ `virtual void SetError(EBuildPatchInstallError ErrorType, const TCHAR* ErrorSubType, uint32 ErrorCode = 0, FText ErrorText = FText::GetEmpty()) = 0;` — Report a fatal error that has occurred which should cause other systems to abort. @param ErrorType     The enum value for the error. @param ErrorSubType  The error sub type string for the error. @param ErrorCode     The error code for the error. 0 means no additional information. @param ErrorText     Optional specific error display text to use instead of the standard generic one.
- L213 _public prototype_ `virtual void ResetError(bool bPreserveCancelled) = 0;` — Resets the current error state without unregistering delegates added by RegisterForErrors. @param bPreserveCancelled	If true the canceled error state is preserved instead of being reset.
- L220 _public prototype_ `virtual int32 RegisterForErrors(FOnErrorDelegate Delegate) = 0;` — Register a delegate to be called upon an error occurring. @param Delegate      The delegate to be executed on error. @return a handle for this registration, used to unregister.
- L226 _public prototype_ `virtual void UnregisterForErrors(int32 Handle) = 0;` — Unregister a delegate from being called upon an error occurring. @param Handle        The value that was returned RegisterForErrors for the delegate to be removed.

#### class `BuildPatchServices::FInstallerErrorFactory`  
`class FInstallerErrorFactory`  
_L232-241_
- desc: A factory for creating an IInstallerError instance.
- L240 _public prototype_ `static IInstallerError* Create();` — Creates an instance of an error class which should be shared between all systems created for the same installation. @return the new IInstallerError instance created.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace BuildPatchServices`
- L13 _namespace_ `namespace InitializationErrorCodes` (scope `BuildPatchServices`)
- L15 _variable_ `static const TCHAR* MissingStageDirectory = TEXT("01"` (scope `BuildPatchServices::InitializationErrorCodes`)
- L16 _variable_ `static const TCHAR* MissingInstallDirectory = TEXT("02"` (scope `BuildPatchServices::InitializationErrorCodes`)
- L17 _variable_ `static const TCHAR* MissingCompleteDelegate = TEXT("03"` (scope `BuildPatchServices::InitializationErrorCodes`)
- L18 _variable_ `static const TCHAR* InvalidInstallTags = TEXT("04"` (scope `BuildPatchServices::InitializationErrorCodes`)
- L19 _variable_ `static const TCHAR* ChunkReferenceTracking = TEXT("05"` (scope `BuildPatchServices::InitializationErrorCodes`)
- L20 _variable_ `static const TCHAR* MissingPrereqForPrereqOnlyInstall = TEXT("06"` (scope `BuildPatchServices::InitializationErrorCodes`)
- L21 _variable_ `static const TCHAR* InvalidDataInManifest = TEXT("07"` (scope `BuildPatchServices::InitializationErrorCodes`)
- L22 _variable_ `static const TCHAR* EmptyCloudDirectories = TEXT("08"` (scope `BuildPatchServices::InitializationErrorCodes`)
- L23 _variable_ `static const TCHAR* VerifyOnlyActionMixedWithOtherActions = TEXT("09"` (scope `BuildPatchServices::InitializationErrorCodes`)
- L24 _variable_ `static const TCHAR* MissingEncryptionKeyForNonPreload = TEXT("10"` (scope `BuildPatchServices::InitializationErrorCodes`)
- L25 _variable_ `static const TCHAR* InvalidEncryptionKeyForNonPreload = TEXT("11"` (scope `BuildPatchServices::InitializationErrorCodes`)
- L26 _variable_ `static const TCHAR* InvalidInstallToMemory = TEXT("11"` (scope `BuildPatchServices::InitializationErrorCodes`)
- L27 _variable_ `static const TCHAR* InvalidMemoryConstructionConfig = TEXT("12"` (scope `BuildPatchServices::InitializationErrorCodes`)
- L33 _namespace_ `namespace DiskSpaceErrorCodes` (scope `BuildPatchServices`)
- L35 _variable_ `static const TCHAR* InitialSpaceCheck = TEXT("01"` (scope `BuildPatchServices::DiskSpaceErrorCodes`)
- L36 _variable_ `static const TCHAR* DuringInstallation = TEXT("02"` (scope `BuildPatchServices::DiskSpaceErrorCodes`)
- L42 _namespace_ `namespace PathLengthErrorCodes` (scope `BuildPatchServices`)
- L44 _variable_ `static const TCHAR* StagingDirectory = TEXT("01"` (scope `BuildPatchServices::PathLengthErrorCodes`)
- L45 _variable_ `static const TCHAR* InstallDirectory = TEXT("02"` (scope `BuildPatchServices::PathLengthErrorCodes`)
- L51 _namespace_ `namespace DownloadErrorCodes` (scope `BuildPatchServices`)
- L53 _variable_ `static const TCHAR* OutOfChunkRetries = TEXT("01"` (scope `BuildPatchServices::DownloadErrorCodes`)
- L54 _variable_ `static const TCHAR* MissingDeltaFile = TEXT("02"` (scope `BuildPatchServices::DownloadErrorCodes`)
- L55 _variable_ `static const TCHAR* UnserialisableDeltaFile = TEXT("03"` (scope `BuildPatchServices::DownloadErrorCodes`)
- L56 _variable_ `static const TCHAR* RejectedDeltaFile = TEXT("04"` (scope `BuildPatchServices::DownloadErrorCodes`)
- L57 _variable_ `static const TCHAR* FailedUriRequest = TEXT("05"` (scope `BuildPatchServices::DownloadErrorCodes`)
- L63 _namespace_ `namespace ConstructionErrorCodes` (scope `BuildPatchServices`)
- L65 _variable_ `static const TCHAR* UnknownFail = TEXT("01"` (scope `BuildPatchServices::ConstructionErrorCodes`)
- L66 _variable_ `static const TCHAR* FileCreateFail = TEXT("02"` (scope `BuildPatchServices::ConstructionErrorCodes`)
- L67 _variable_ `static const TCHAR* MissingChunkData = TEXT("03"` (scope `BuildPatchServices::ConstructionErrorCodes`)
- L68 _variable_ `static const TCHAR* MissingFileInfo = TEXT("04"` (scope `BuildPatchServices::ConstructionErrorCodes`)
- L69 _variable_ `static const TCHAR* OutboundCorrupt = TEXT("05"` (scope `BuildPatchServices::ConstructionErrorCodes`)
- L70 _variable_ `static const TCHAR* SerializationError = TEXT("06"` (scope `BuildPatchServices::ConstructionErrorCodes`)
- L71 _variable_ `static const TCHAR* TrackingError = TEXT("07"` (scope `BuildPatchServices::ConstructionErrorCodes`)
- L72 _variable_ `static const TCHAR* InternalConsistencyFailure = TEXT("08"` (scope `BuildPatchServices::ConstructionErrorCodes`)
- L73 _variable_ `static const TCHAR* SymlinkCreateFail = TEXT("09"` (scope `BuildPatchServices::ConstructionErrorCodes`)
- L74 _variable_ `static const TCHAR* SymlinkCreateForbidden = TEXT("10"` (scope `BuildPatchServices::ConstructionErrorCodes`)
- L75 _variable_ `static const TCHAR* CloseFileError = TEXT("11"` (scope `BuildPatchServices::ConstructionErrorCodes`)
- L81 _namespace_ `namespace MoveErrorCodes` (scope `BuildPatchServices`)
- L83 _variable_ `static const TCHAR* StageToInstall = TEXT("01"` (scope `BuildPatchServices::MoveErrorCodes`)
- L84 _variable_ `static const TCHAR* DeletePrevFileFailed = TEXT("02"` (scope `BuildPatchServices::MoveErrorCodes`)
- L85 _variable_ `static const TCHAR* DeleteOldFileFailed = TEXT("03"` (scope `BuildPatchServices::MoveErrorCodes`)
- L91 _namespace_ `namespace VerifyErrorCodes` (scope `BuildPatchServices`)
- L93 _variable_ `static const TCHAR* UnknownFail = TEXT("01"` (scope `BuildPatchServices::VerifyErrorCodes`)
- L94 _variable_ `static const TCHAR* FileMissing = TEXT("02"` (scope `BuildPatchServices::VerifyErrorCodes`)
- L95 _variable_ `static const TCHAR* OpenFileFailed = TEXT("03"` (scope `BuildPatchServices::VerifyErrorCodes`)
- L96 _variable_ `static const TCHAR* HashCheckFailed = TEXT("04"` (scope `BuildPatchServices::VerifyErrorCodes`)
- L97 _variable_ `static const TCHAR* FileSizeFailed = TEXT("05"` (scope `BuildPatchServices::VerifyErrorCodes`)
- L98 _variable_ `static const TCHAR* DeleteCorruptedFileFailed = TEXT("06"` (scope `BuildPatchServices::VerifyErrorCodes`)
- L104 _namespace_ `namespace UserCancelErrorCodes` (scope `BuildPatchServices`)
- L106 _variable_ `static const TCHAR* UserRequested = TEXT("01"` (scope `BuildPatchServices::UserCancelErrorCodes`)
- L112 _namespace_ `namespace ApplicationClosedErrorCodes` (scope `BuildPatchServices`)
- L114 _variable_ `static const TCHAR* ApplicationClosed = TEXT("01"` (scope `BuildPatchServices::ApplicationClosedErrorCodes`)
- L120 _namespace_ `namespace UninstallCustomActionErrorPrefixes` (scope `BuildPatchServices`)
- L122 _variable_ `static const TCHAR* ExecuteCode = TEXT("E")` (scope `BuildPatchServices::UninstallCustomActionErrorPrefixes`)
- L123 _variable_ `static const TCHAR* ReturnCode = TEXT("R")` (scope `BuildPatchServices::UninstallCustomActionErrorPrefixes`)
- L129 _namespace_ `namespace PrerequisiteErrorPrefixes` (scope `BuildPatchServices`)
- L131 _variable_ `static const TCHAR* ExecuteCode = TEXT("E")` (scope `BuildPatchServices::PrerequisiteErrorPrefixes`)
- L132 _variable_ `static const TCHAR* ReturnCode = TEXT("R")` (scope `BuildPatchServices::PrerequisiteErrorPrefixes`)
- L133 _variable_ `static const TCHAR* NotFoundCode = TEXT("01"` (scope `BuildPatchServices::PrerequisiteErrorPrefixes`)
- L141 _prototype_ `FText GetStandardErrorText(EBuildPatchInstallError ErrorType);` (scope `BuildPatchServices`) — Get the standard error message for an error type. @param ErrorType     The enum value for the error. @return the displayable text for the error type.
- L151 _prototype_ `FText GetDiskSpaceMessage(const FString& Location, uint64 RequiredBytes, uint64 AvailableBytes, const FNumberFormattingOptions* FormatOptions = nullptr);` (scope `BuildPatchServices`) — Get the standard error message for for a disk space issue. @param Location          The disk path requiring more space. @param RequiredBytes     The number of bytes required for the installation. @param AvailableBytes    The number of bytes available on the drive. @param FormatOptions     Optionally override the default number formatting. @return the displayable text for the out of space error.

### `Source/Runtime/Online/BuildPatchServices/Private/Installer/InstallerSharedContext.h` (Private)


#### class `BuildPatchServices::FBuildInstallerThread`  
`class FBuildInstallerThread : public IBuildInstallerThread , public FRunnable`  
_L14-56_
- inherits: `IBuildInstallerThread,FRunnable`
- desc: The concrete implementation of IBuildInstallerThread
- L24 _private prototype_ `FRIEND_ENUM_CLASS_FLAGS(EMsg);`
- L39 _public prototype_ `~FBuildInstallerThread();`
- L41 _public prototype_ `bool StartThread(const TCHAR* DebugName);`
- L44 _public prototype_ `virtual void RunTask(TUniqueFunction<void()> Task) override;` — IBuildInstallerThread interface begin
- L48 _public prototype_ `virtual uint32 Run() override;` — FRunnable interface begin
- L49 _public prototype_ `virtual void Stop() override;`
- L53 _private member_ `FEvent* DoWorkEvent = nullptr;`
- L54 _private member_ `FRunnableThread* Thread = nullptr;`
- L55 _private member_ `TMpscQueue<FMsg> MsgQueue;`

#### enum `BuildPatchServices::FBuildInstallerThread::EMsg`  
`enum class EMsg : uint8`  
_L18-23_
- L20 _public enumerator_ `None = 0`
- L21 _public enumerator_ `RunTask = (1 << 0)`
- L22 _public enumerator_ `Exit = (1 << 1)`

#### struct `BuildPatchServices::FBuildInstallerThread::FMsg`  
`struct FMsg`  
_L26-36_
- L28 _public prototype_ `FMsg() = default;`
- L29 _public function_ `FMsg(TUniqueFunction<void()> InTask, EMsg InMsg) : Task(MoveTemp(InTask)) , Msg(InMsg)`
- L34 _public member_ `TUniqueFunction<void()> Task;`
- L35 _public member_ `EMsg Msg = EMsg::None;`

#### class `BuildPatchServices::FBuildInstallerSharedContext`  
`class FBuildInstallerSharedContext : public IBuildInstallerSharedContext`  
_L61-83_
- inherits: `IBuildInstallerSharedContext`
- desc: The concrete implementation of IBuildInstallerSharedContext
- L64 _public function_ `FBuildInstallerSharedContext(const TCHAR* InDebugName) : DebugName(InDebugName)`
- L65 _public prototype_ `~FBuildInstallerSharedContext();`
- L68 _public prototype_ `virtual IBuildInstallerThread* CreateThread() override;` — IBuildInstallerSharedContext interface begin
- L69 _public prototype_ `virtual void ReleaseThread(IBuildInstallerThread* Thread) override;`
- L70 _public prototype_ `virtual void PreallocateThreads(uint32 NumThreads) override;`
- L71 _public prototype_ `virtual uint32 NumThreadsPerInstaller(bool bUseChunkDBs, bool bHasInstallSource) const override;`
- L75 _private prototype_ `IBuildInstallerThread* CreateThreadInternal();`
- L78 _private member_ `TArray<IBuildInstallerThread*> ThreadFreeList;`
- L79 _private member_ `FCriticalSection ThreadFreeListCS;`
- L80 _private member_ `const TCHAR* DebugName;`
- L81 _private member_ `uint32 ThreadCount = 0;`
- L82 _private member_ `bool bWarnOnCreateThread = false;`

#### class `BuildPatchServices::FBuildInstallerSharedContextFactory`  
`class FBuildInstallerSharedContextFactory`  
_L88-96_
- desc: A factory for creating an IBuildInstallerSharedContext instance.
- L95 _public prototype_ `static IBuildInstallerSharedContextRef Create(const TCHAR* DebugName);` — @param DebugName          Used to tag resources allocated with the shared context. @return an instance of an IBuildInstallerSharedContex implementation.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Installer/MachineConfig.h` (Private)


#### class `BuildPatchServices::IMachineConfig`  
`class IMachineConfig`  
_L8-27_
- L14 _public prototype_ `virtual ~IMachineConfig() = default;` — Virtual destructor.
- L20 _public prototype_ `virtual TSet<FString> LoadInstalledPrereqIds() = 0;` — Loads the list of installed prereq ids whose corresponding prerequisites are installed on this computer. @return         A set containing the prerequisite ids which are installed on this computer.
- L26 _public prototype_ `virtual void SaveInstalledPrereqIds(const TSet<FString>& InstalledPrereqIds) = 0;` — Saves updated list of installed prereqs to the configuration file. @param InstalledPrereqIds       A set of all installed prerequisites to save to configuration.

#### class `BuildPatchServices::FMachineConfigFactory`  
`class FMachineConfigFactory`  
_L32-42_
- desc: A factory for creating an IMachineConfig instance.
- L41 _public prototype_ `static IMachineConfig* Create(const FString& LocalMachineConfigFile, bool bAlwaysFlushChanges);` — Creates an instance of IMachineConfig. @param LocalMachineConfigFile   The path to an ini file which should contain the per machine configuration data. @param bAlwaysFlushChanges      If true, then we'll always flush changes straight to disk after saving values. @return a pointer to the new IMachineConfig instance created.

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Installer/MemoryChunkStore.h` (Private)


#### class `BuildPatchServices::IMemoryChunkStore`  
`class IMemoryChunkStore : public IChunkStore`  
_L15-26_
- inherits: `IChunkStore`
- desc: An interface providing access to chunk data instances which are stored in memory.
- L18 _public prototype_ `virtual ~IMemoryChunkStore() = default;`
- L25 _public prototype_ `virtual void DumpToOverflow() = 0;` — Dumps all chunks contained in this store into the overflow provided at construction, removing all chunks from this store in the process. This function will also invalidate data ptr previously returned by Get().

#### class `BuildPatchServices::FMemoryChunkStoreFactory`  
`class FMemoryChunkStoreFactory`  
_L31-48_
- desc: A factory for creating an IMemoryChunkStore instance.
- L47 _public prototype_ `static IMemoryChunkStore* Create(int32 ChunkCount, IChunkEvictionPolicy* EvictionPolicy, IChunkStore* OverflowStore, IMemoryChunkStoreStat* MemoryChunkStoreStat, IChunkReferenceTracker* InOptionalChunkReferenceTracker);` — Creates an instance of a chunk store class that stores chunks in memory. When Put() is called and the store has >= ChunkCount entries, the EvictionPolicy will be used to select chunks which should be Put() into the OverflowStore instance, and removed from this store. If the EvictionPolicy allows it, the store will grow larger than ChunkCount. When Get() is called on a chunk that is not in this store, Remove() will be attempted on the OverflowStore instance, and the chunk will enter the memory store if it was successful. @param ChunkCount                The size of the store, at which point chunks will start being evicted based on the policy provided. @param EvictionPolicy            Required ptr to an eviction policy that will be used to clean out the store, and evict data when full. @param OverflowStore             Required ptr to an IChunkStore which will be used as an overflow for evicted chunks. @param MemoryChunkStoreStat      Required ptr to the statistics class. @return the new IMemoryChunkStore instance created.

#### class `BuildPatchServices::IMemoryChunkStoreStat`  
`class IMemoryChunkStoreStat`  
_L54-88_
- desc: This interface defines the statistics class required by the memory chunk store. It should be implemented in order to collect desired information which is being broadcast by the system.
- L57 _public prototype_ `virtual ~IMemoryChunkStoreStat() = default;`
- L63 _public prototype_ `virtual void OnChunkStored(const FGuid& ChunkId) = 0;` — Called whenever a new chunk has been put into the store. @param ChunkId           The id of the chunk.
- L69 _public prototype_ `virtual void OnChunkReleased(const FGuid& ChunkId) = 0;` — Called whenever a chunk has been release from the store as it was no longer referenced. @param ChunkId           The id of the chunk.
- L75 _public prototype_ `virtual void OnChunkBooted(const FGuid& ChunkId) = 0;` — Called whenever a chunk has been booted from the store because a new one was added that is required sooner. @param ChunkId           The id of the chunk.
- L81 _public prototype_ `virtual void OnStoreUseUpdated(int32 ChunkCount) = 0;` — Called whenever the number of chunks in the store is updated. @param ChunkCount        The number of chunks now contained in the store.
- L87 _public prototype_ `virtual void OnStoreSizeUpdated(int32 Size) = 0;` — Called whenever the total size allotted for the store is updated. @param Size              The total number of chunks that can be stored.

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Installer/MessagePump.h` (Private)


#### class `BuildPatchServices::IMessagePump`  
`class IMessagePump`  
_L12-84_
- desc: Interface for a message pump which allows systems to bubble up event information to the Installer's public API.
- L18 _public prototype_ `virtual ~IMessagePump() = default;` — Virtual destructor.
- L24 _public prototype_ `virtual void SendMessage(FChunkSourceEvent Message) = 0;` — Sends a chunk source event message. @param Message   The message to be sent.
- L27 _public prototype_ `virtual void SendMessage(FGenericMessage Message) = 0;` — See FGenericMessage for types of messages.
- L33 _public prototype_ `virtual void SendMessage(FInstallationFileAction Message) = 0;` — Sends an installation file action message. @param Message   The message to be sent.
- L54 _public prototype_ `virtual bool SendRequest(FChunkUriRequest Request, TFunction<void(FChunkUriResponse)> OnResponse) = 0;` — Sends out a request to resolve the uri to the chunk location @param Request   Request for the chunk location @param OnResponse   A delegate to call with the chunk location and any potential headers to add to the http request. Note that while this function supports asynchronous processing, the calling code does not support cancelation of the requests under abort scenarios, potentially leading to crashes. As as result, incomplete shutdown of the installation requires waiting for all outstanding requests to return before shutdown can complete. For user initiated cancellations it is recommended that you abort any async uri request handling and call OnResponse with FChunkUriResponse::bFailed to true after calling CancelInstall(). This will prevent the default URL concatenation from occuring and allow the shutdown logic to complete in a timely fashion. For internally initiated cancellations (due to errors) there's nothing to be done; shutdown just waits for the requests to all complete. As a result, it's highly advisable to make this as immediate as possible, e.g. caching auth tokens up front before installation launch.
- L61 _public prototype_ `virtual void SendRequest(FDeltaUriRequest Request, TFunction<void(FExpiratedUrisResponse)> OnResponse) = 0;` — Sends out a request to resolve the uri to the delta file location @param Request   Request for the delta file location @param OnResponse   A delegate to call with a response to delta location
- L68 _public prototype_ `virtual void PumpMessages(const TArray<FMessageHandler*>& Handlers) = 0;` — Dequeues received messages, pushing them to the provided handlers. NOTE: PumpMessages, RegisterMessageHandler, and UnregisterMessageHandler MUST all be called from the same thread. @param Handlers      The array of handlers.
- L69 _public prototype_ `virtual void PumpMessages() = 0;`
- L76 _public prototype_ `virtual void RegisterMessageHandler(FMessageHandler* MessageHandler) = 0;` — Registers a message handler. @param MessageHandler    Ptr to the message handler to add. Must not be null. NOTE: PumpMessages, RegisterMessageHandler, and UnregisterMessageHandler MUST all be called from the same thread.
- L83 _public prototype_ `virtual void UnregisterMessageHandler(FMessageHandler* MessageHandler) = 0;` — Unregisters a message handler. @param MessageHandler    Ptr to the message handler to remove. NOTE: PumpMessages, RegisterMessageHandler, and UnregisterMessageHandler MUST all be called from the same thread.

#### class `BuildPatchServices::FMessagePumpFactory`  
`class FMessagePumpFactory`  
_L89-97_
- desc: A factory for creating an IMessagePump instance.
- L96 _public prototype_ `static IMessagePump* Create();` — Creates an instance of IMessagePump. @return a pointer to the new IMessagePump instance created.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Installer/OptimisedDelta.h` (Private)


#### class `BuildPatchServices::IOptimisedDelta`  
`class IOptimisedDelta`  
_L16-47_
- desc: An interface providing access for retrieving the optimised delta manifest used to patch from a specific source to a specific destination.
- L19 _public prototype_ `virtual ~IOptimisedDelta() = default;`
- L20 _public typedef_ `typedef TValueOrError<FBuildPatchAppManifestPtr, FString> FResultValueOrError;`
- L28 _public prototype_ `virtual const IOptimisedDelta::FResultValueOrError& GetResult() const = 0;` — Gets the manifest that should be used as the destination manifest, or the error instead if there was one. If DeltaPolicy configuration is EDeltaPolicy::TryFetchContinueWithout then the result is guarenteed to always contain a valid manifest, which may equal the original DestinationManifest provided. @return the destination manifest.
- L34 _public prototype_ `virtual int32 GetMetaDownloadSize() const = 0;` — Gets the size of the metadata downloaded to create the optimised manifest. @return the downloaded size in bytes.
- L40 _public prototype_ `virtual bool IsReady() const = 0;` — Checks if manifest returned by GetResult() is ready to be provided immediately. @return true if result can be obtained.
- L46 _public prototype_ `virtual int32 GetDownloadResponseCode() const = 0;` — Gets the response code from the download of the optimised delta file. @return the response code, or 0 if no download was attempted.

#### struct `BuildPatchServices::FOptimisedDeltaConfiguration`  
`struct FOptimisedDeltaConfiguration`  
_L52-75_
- desc: Defines a list of configuration details required for the IOptimisedDelta construction.
- L58 _public prototype_ `FOptimisedDeltaConfiguration(FBuildPatchAppManifestRef DestinationManifest);` — Construct with destination manifest, this is a required param.
- L62 _public member_ `FBuildPatchAppManifestPtr SourceManifest;` — The installation provided source manifest.
- L64 _public member_ `FBuildPatchAppManifestRef DestinationManifest;` — The installation provided destination manifest.
- L66 _public member_ `EDeltaPolicy DeltaPolicy;` — The policy to follow for requesting an optimised delta.
- L68 _public member_ `EInstallMode InstallMode;` — The mode for installation.
- L70 _public member_ `int32_t RetriesNumber = 0;` — A minimal number of retries for delta file download.
- L74 _public member_ `FString DeltaFilenameTrailer;` — This is an identifier that we append to the optimized delta filename in order to facilitate multiple optimized deltas for the same build pairing.

#### struct `BuildPatchServices::FOptimisedDeltaDependencies`  
`struct FOptimisedDeltaDependencies`  
_L80-95_
- desc: Defines a list of dependencies required for the IOptimisedDelta construction.
- L86 _public prototype_ `FOptimisedDeltaDependencies(TSharedRef<IUriProvider, ESPMode::ThreadSafe> InUriProvider);` — Constructor setting up default values.
- L90 _public member_ `TSharedRef<IUriProvider, ESPMode::ThreadSafe> UriProvider;` — A URI provider instance.
- L92 _public member_ `IDownloadService* DownloadService = nullptr;` — A download service instance.
- L94 _public function_ `TUniqueFunction<void(const IOptimisedDelta::FResultValueOrError&)> OnComplete = [](const IOptimisedDelta::FResultValueOrError&)` — Function to call once the destination manifest has been selected. Receives manifest or error.
- L94 _public member_ `TUniqueFunction<void(const IOptimisedDelta::FResultValueOrError&)> OnComplete = [](const IOptimisedDelta::FResultValueOrError&) {};` — Function to call once the destination manifest has been selected. Receives manifest or error.

#### class `BuildPatchServices::FOptimisedDeltaFactory`  
`class FOptimisedDeltaFactory`  
_L97-101_
- L100 _public prototype_ `static TSharedRef<IOptimisedDelta> Create(const FOptimisedDeltaConfiguration& Configuration, FOptimisedDeltaDependencies Dependencies);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Installer/Prerequisites.h` (Private)


#### class `BuildPatchServices::IPrerequisites`  
`class IPrerequisites`  
_L19-36_
- L25 _public prototype_ `virtual ~IPrerequisites() = default;` — Virtual destructor.
- L35 _public prototype_ `virtual bool RunPrereqs(const IBuildManifestSet* ManifestSet, const FBuildInstallerConfiguration& Configuration, const FString& InstallStagingDir, FBuildPatchProgress& BuildProgress) = 0;` — Runs any prerequisites associated with the installation. @param BuildManifest       The manifest containing details of the prerequisite installer. @param Configuration       The installer configuration structure. @param InstallStagingDir   The directory within staging to construct install files to. @param BuildProgress       Used to keep track of install progress. @return                    Returns true if the prerequisites installer succeeded, false otherwise.

#### class `BuildPatchServices::FPrerequisitesFactory`  
`class FPrerequisitesFactory`  
_L41-54_
- desc: A factory for creating an IPrerequisites instance.
- L53 _public prototype_ `static IPrerequisites* Create(IMachineConfig* MachineConfig, IInstallerAnalytics* InstallerAnalytics, IInstallerError* InstallerError, IFileSystem* FileSystem, IPlatform* Platform);` — Creates an instance of IPrerequisites. @param MachineConfig           A class responsible for loading and saving per machine configuration data. @param InstallerAnalytics      The analytics implementation for reporting the installer events. @param InstallerError          The error handling implementation which any installation errors will be reported to. @param FileSystem              An abstraction representing the filesystem. @param Platform                An abstraction providing access to platform operations. @return the new IPrerequisites instance created.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Installer/Statistics/ChunkDbChunkSourceStatistics.h` (Private)


#### class `BuildPatchServices::IChunkDbChunkSourceStatistics`  
`class IChunkDbChunkSourceStatistics : public IChunkDbChunkSourceStat`  
_L14-29_
- inherits: `IChunkDbChunkSourceStat`
- desc: Interface to the statistics class which provides access to tracked values from a chunkdb chunk source stat.
- L21 _public prototype_ `virtual int32 GetNumSuccessfulLoads() const = 0;` — @return the number of chunks successfully read from chunkdbs.
- L26 _public prototype_ `virtual int32 GetNumFailedLoads() const = 0;` — @return the number of chunks which failed to load from provided chunkdbs.
- L28 _public prototype_ `virtual bool IsCurrentlyReading() const = 0;`

#### class `BuildPatchServices::FChunkDbChunkSourceStatisticsFactory`  
`class FChunkDbChunkSourceStatisticsFactory`  
_L34-44_
- desc: A factory for creating an IChunkDbChunkSourceStatistics instance.
- L43 _public prototype_ `static IChunkDbChunkSourceStatistics* Create(ISpeedRecorder* SpeedRecorder, IFileOperationTracker* FileOperationTracker);` — Creates the chunkdb chunk source's dependency interface and exposes additional information. @param SpeedRecorder         The speed recorder instance that we send activity records to. @param FileOperationTracker  The file operation tracker which will be used to update data states. @return the new IChunkDbChunkSourceStatistics instance created.

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Installer/Statistics/CloudChunkSourceStat.h` (Private)


#### class `BuildPatchServices::FCloudChunkSourceStatFactory`  
`class FCloudChunkSourceStatFactory`  
_L12-21_
- desc: A factory for creating an ICloudChunkSourceStat instance.
- L20 _public prototype_ `static ICloudChunkSourceStat* Create(FStatsCollector* InStatsCollector);` — Creates the cloud source stat dependency interface and exposes wraps stats collector. @param InStatsCollector    The stats collector which will be used to collect statistics on cloud source events. @return the new ICloudChunkSourceStat instance created.

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Installer/Statistics/CloudChunkSourceStatistics.h` (Private)


#### class `BuildPatchServices::ICloudChunkSourceStatistics`  
`class ICloudChunkSourceStatistics : public ICloudChunkSourceStat`  
_L15-83_
- inherits: `ICloudChunkSourceStat`
- desc: Interface to the statistics class which provides access to tracked values from a cloud chunk source stat.
- L22 _public prototype_ `virtual uint64 GetRequiredDownloadSize() const = 0;` — @return the number of bytes that the installation required from cloud sources.
- L27 _public prototype_ `virtual uint64 GetDownloadedBytes() const = 0;` — @return the number of bytes received so far.
- L32 _public prototype_ `virtual uint64 GetNumCorruptChunkDownloads() const = 0;` — @return the number of successful chunk downloads which had invalid data.
- L37 _public prototype_ `virtual uint64 GetNumAbortedChunkDownloads() const = 0;` — @return the number of chunk downloads which were aborted, having been determined as lagging.
- L42 _public prototype_ `virtual float GetDownloadSuccessRate() const = 0;` — @return the rate of success for chunks download requests, 1.0 being 100%.
- L47 _public prototype_ `virtual EBuildPatchDownloadHealth GetDownloadHealth() const = 0;` — @return the EBuildPatchDownloadHealth value which the success rate applies to according to the configured ranges.
- L52 _public prototype_ `virtual TArray<float> GetDownloadHealthTimers() const = 0;` — @return an array of seconds spent in each download health range, indexable by EBuildPatchDownloadHealth.
- L57 _public prototype_ `virtual uint32 GetCurrentRequestCount() const = 0;` — @return the current number of download requests.
- L62 _public prototype_ `virtual uint32 GetPeakRequestCount() const = 0;` — @return the peak number of download requests.
- L67 _public prototype_ `virtual uint32 GetAvgRequestCount() const = 0;` — @return the avg number of download requests.
- L72 _public prototype_ `virtual const TCHAR* GetExperimentVariant() const = 0;` — @return the A/B Experiment if applicable
- L77 _public prototype_ `virtual double GetTotalDecryptTime() const = 0;` — @return the total time in seconds spent on chunks decryption.
- L82 _public prototype_ `virtual const TArray<FCloudDirectoryStats>& GetCloudDirectoryStats() const = 0;` — @return the stats collected for each cloud directory.

#### class `BuildPatchServices::FCloudChunkSourceStatisticsFactory`  
`class FCloudChunkSourceStatisticsFactory`  
_L88-99_
- desc: A factory for creating an ICloudChunkSourceStatistics instance.
- L98 _public prototype_ `static ICloudChunkSourceStatistics* Create(IInstallerAnalytics* InstallerAnalytics, FBuildPatchProgress* BuildProgress, IFileOperationTracker* FileOperationTracker);` — Creates the cloud chunk source's dependency interface and exposes additional information. @param InstallerAnalytics    The analytics implementation for reporting the cloud source events. @param BuildProgress         The legacy progress implementation to bridge the system stats to. @param FileOperationTracker  The file operation tracker which will be used to update data states. @return the new ICloudChunkSourceStatistics instance created.

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Installer/Statistics/DownloadServiceStatistics.h` (Private)


#### class `BuildPatchServices::IDownloadServiceStatistics`  
`class IDownloadServiceStatistics : public IDownloadServiceStat`  
_L19-61_
- inherits: `IDownloadServiceStat`
- desc: Interface to the statistics class which provides access to tracked values from a download service stat.
- L26 _public prototype_ `virtual uint64 GetBytesDownloaded() const = 0;` — @return the total number of bytes downloaded.
- L31 _public prototype_ `virtual int32 GetNumSuccessfulChunkDownloads() const = 0;` — @return the number of successfully downloaded chunks.
- L36 _public prototype_ `virtual int32 GetNumFailedChunkDownloads() const = 0;` — @return the number of chunk requests that failed.
- L41 _public prototype_ `virtual int32 GetNumCurrentDownloads() const = 0;` — @return the number of current requests.
- L46 _public prototype_ `virtual TArray<FDownload> GetCurrentDownloads() const = 0;` — @return an array of current request info.
- L55 _public prototype_ `virtual TPair<double, uint32> GetImmediateAverageSpeedPerRequest(uint32 MinCount) = 0;` — Calculates the average speed per request since the last time this function was called. NOT A CUMULATIVE AVERAGE @param MinCount -- The smallest number of samples that will be used for calculating an average; if the minimum count isn't met, the same value as the previous call is returned, and the samples will continue to accumulate. @return A pair containing an average of the per-request download speed SINCE THIS FUNCTION WAS LAST CALLED and the count of requests completed since the last call.
- L60 _public prototype_ `virtual void Reset() = 0;` — Resets all internal statistics.

#### class `BuildPatchServices::FDownloadServiceStatisticsFactory`  
`class FDownloadServiceStatisticsFactory`  
_L66-77_
- desc: A factory for creating an IDownloadServiceStatistics instance.
- L76 _public prototype_ `static IDownloadServiceStatistics* Create(const TSharedPtr<ISpeedRecorder>& SpeedRecorder, const TSharedPtr<IDataSizeProvider>& DataSizeProvider, const TSharedPtr<IInstallerAnalytics>& InstallerAnalytics);` — Creates the download service's dependency interface and exposes additional information. @param SpeedRecorder         The speed recorder instance that we send activity records to. @param DataSizeProvider      The data size provider for looking up the file size of each downloadable chunk. @param InstallerAnalytics    The analytics implementation for reporting the download service events. @return the new IDownloadServiceStatistics instance created.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Installer/Statistics/Experiments.h` (Private)


#### class `BuildPatchServices::Experiments`  
`class Experiments`  
_L8-41_
- L33 _public prototype_ `static const FString GetVariant(const Experiment& Experiment, const FString& UserId);` — If a user is in an experiment, choose the variant of the experiment they are in. returns the variant, or if they are not in the experiment returns nullptr
- L37 _public prototype_ `static const Experiment& DownloadSpeed();` — Download Speed Experiment This experiment will be used to test various methods for improving the download speed for users in the launcher
- L40 _private prototype_ `Experiments();`

#### enum `BuildPatchServices::Experiments::EExperiment`  
`enum class EExperiment : uint32`  
_L11-14_
- L13 _public enumerator_ `DownloadSpeed = 1u`

#### struct `BuildPatchServices::Experiments::Variant`  
`struct Variant`  
_L16-22_
- L18 _public member_ `FString VariantId;`
- L19 _public member_ `unsigned RolloutPercent;`
- L20 _public function_ `Variant() : VariantId(), RolloutPercent(0u)`
- L21 _public function_ `Variant(const FString& Id, unsigned Percent) : VariantId(Id), RolloutPercent(Percent)`

#### struct `BuildPatchServices::Experiments::Experiment`  
`struct Experiment`  
_L24-29_
- L26 _public member_ `EExperiment Id;`
- L27 _public member_ `FString ExperimentName;`
- L28 _public member_ `TArray<Variant> Variants;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace BuildPatchServices`
- L44 _function_ `inline const TCHAR* LexToString(BuildPatchServices::Experiments::EExperiment Value)`

### `Source/Runtime/Online/BuildPatchServices/Private/Installer/Statistics/FileConstructorStatistics.h` (Private)


#### class `BuildPatchServices::IFileConstructorStatistics`  
`class IFileConstructorStatistics : public IFileConstructorStat`  
_L15-63_
- inherits: `IFileConstructorStat`
- desc: Interface to the statistics class which provides access to tracked values from a file constructor stat.
- L22 _public prototype_ `virtual int64 GetRequiredConstructSize() const = 0;` — @return the number of bytes to construct to complete the installation.
- L27 _public prototype_ `virtual uint64 GetBytesConstructed() const = 0;` — @return the total number of bytes constructed.
- L32 _public prototype_ `virtual uint64 GetFilesConstructed() const = 0;` — @return the total number of files constructed.
- L37 _public prototype_ `virtual FGuid GetCurrentChunk() const = 0;` — @return the current chunk data is being serialized from.
- L42 _public prototype_ `virtual FString GetCurrentFile() const = 0;` — @return the current file data is being serialized to.
- L47 _public prototype_ `virtual float GetCurrentFileProgress() const = 0;` — @return the current file progress.
- L52 _public prototype_ `virtual bool IsCurrentlyWriting() const = 0;` — @return true if currently writing disk data.
- L57 _public prototype_ `virtual bool IsCurrentlyReading() const = 0;` — @return true if currently reading disk data.
- L62 _public prototype_ `virtual bool IsCurrentlyAdministering() const = 0;` — @return true if currently administering files.

#### class `BuildPatchServices::FFileConstructorStatisticsFactory`  
`class FFileConstructorStatisticsFactory`  
_L68-80_
- desc: A factory for creating an IFileConstructorStatistics instance.
- L79 _public prototype_ `static IFileConstructorStatistics* Create(ISpeedRecorder* ReadSpeedRecorder, ISpeedRecorder* WriteSpeedRecorder, FBuildPatchProgress* BuildProgress, IFileOperationTracker* FileOperationTracker);` — Creates the file constructor's dependency interface and exposes additional information. @param ReadSpeedRecorder     The read speed recorder instance that we send activity records to. @param WriteSpeedRecorder    The write speed recorder instance that we send activity records to. @param BuildProgress         The legacy progress implementation to bridge the system stats to. @param FileOperationTracker  The file operation tracker which will be used to update data states. @return the new IFileConstructorStatistics instance created.

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Installer/Statistics/FileOperationTracker.h` (Private)


#### class `BuildPatchServices::IFileOperationTracker`  
`class IFileOperationTracker`  
_L18-84_
- desc: An interface for tracking and querying states of granular file operations.
- L21 _public prototype_ `virtual ~IFileOperationTracker() = default;`
- L26 _public prototype_ `virtual const TArray<FFileOperation>& GetStates() const = 0;` — @return the array of states for each file operation performed by the installation.
- L33 _public prototype_ `virtual void OnManifestSelection(IBuildManifestSet* ManifestSet) = 0;` — Called when manifest selection occurs. This will clear out internal states resetting them built from the provided manifest. All subsequent state updates must refer to data from within the provided manifest. @param Manifest  The manifest to be used to build up internal operation states.
- L40 _public prototype_ `virtual void OnDataStateUpdate(const FGuid& DataId, EFileOperationState State) = 0;` — Called when state is updated for chunk data. @param DataId    Chunk to update state of. @param State     New state of the data.
- L47 _public prototype_ `virtual void OnDataStateUpdate(const TSet<FGuid>& DataIds, EFileOperationState State) = 0;` — Called when state is updated for chunk data. @param DataIds   Chunk set to update state of. @param State     New state of the data.
- L54 _public prototype_ `virtual void OnDataStateUpdate(const TArray<FGuid>& DataIds, EFileOperationState State) = 0;` — Called when state is updated for chunk data. @param DataId    Chunk array to update state of. @param State     New state of the data.
- L61 _public prototype_ `virtual void OnFileStateUpdate(const FString& Filename, EFileOperationState State) = 0;` — Called when state is updated for file data. @param Filename  File to update state of. @param State     New state of the data.
- L68 _public prototype_ `virtual void OnFileStateUpdate(const TSet<FString>& Filenames, EFileOperationState State) = 0;` — Called when state is updated for file data. @param Filename  File set to update state of. @param State     New state of the data.
- L75 _public prototype_ `virtual void OnFileStateUpdate(const TArray<FString>& Filenames, EFileOperationState State) = 0;` — Called when state is updated for file data. @param Filename  File array to update state of. @param State     New state of the data.
- L83 _public prototype_ `virtual void OnFileByteRangeStateUpdate(const FString& Filename, FByteRange ByteRange, EFileOperationState State) = 0;` — Called when state is updated for file data byte range. @param Filename  File to update state of. @param ByteRange The byte range of the file to include. @param State     New state of the data.

#### class `BuildPatchServices::FFileOperationTrackerFactory`  
`class FFileOperationTrackerFactory`  
_L89-107_
- desc: A factory for creating an IFileOperationTracker instance.
- L98 _public prototype_ `static IFileOperationTracker* Create(FTSTicker& Ticker);` — Creates the implementation of a file operation tracker which serves as the dependency for for systems providing these updates. @param   Ticker      The ticker to register for main thread ticks with. @param   Manifest    The manifest for the build being installed. @return the new IFileOperationTracker instance created.
- L106 _public prototype_ `static IFileOperationTracker* CreateNull();` — Creates a null implementation of a file operation tracker which serves as the dependency for for systems providing these updates. @param   Ticker      The ticker to register for main thread ticks with. @param   Manifest    The manifest for the build being installed. @return the new IFileOperationTracker instance created.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace BuildPatchServices`
- L13 _typedef_ `typedef TTuple<uint64, uint64> FByteRange;` (scope `BuildPatchServices`)

### `Source/Runtime/Online/BuildPatchServices/Private/Installer/Statistics/InstallActionStatistics.h` (Private)


#### class `BuildPatchServices::IInstallActionStatistics`  
`class IInstallActionStatistics`  
_L11-62_
- L14 _public prototype_ `virtual ~IInstallActionStatistics() = default;`
- L20 _public prototype_ `virtual TArray<FInstallActionStats> GetAllStats() const = 0;` — Get all installer actions stats. Order matches the order of installer actions in configuration. @return The list of installer actions stats.
- L27 _public prototype_ `virtual FInstallActionStats GetActionStats(const FBuildPatchInstallerAction& InstallerAction) const = 0;` — Return statistics for one action. @param InstallerAction The installer action to query. @return The statistics for queried action.
- L34 _public prototype_ `virtual void CalculateChunkStatistics(const TSet<FGuid>& InstallChunksAvailable) = 0;` — Calculate expected and available statistics for all actions, based on action manifests and chunks available from chunk source. @param InstallChunksAvailable The list of chunks available.
- L41 _public prototype_ `virtual void OnUsedOptimizedDelta(const FBuildPatchInstallerAction& InstallerAction, bool bInUsedOptimizedDelta, uint64 InHTTPResponseCode) = 0;` — Set whether the action successfully downloaded and used delta optimization file. @param InstallerAction The installer action to set. @param bInUsedOptimizedDelta The optimized delta flag.
- L48 _public prototype_ `virtual void OnNumLocalChunksExpected(const FBuildPatchInstallerAction& InstallerAction, uint64 InNumLocalChunksExpected) = 0;` — Set the number of local chunks expected for the action. @param InstallerAction The installer action to set. @param InNumLocalChunksExpected The number of local chunks expected.
- L55 _public prototype_ `virtual void OnNumLocalChunksAvailable(const FBuildPatchInstallerAction& InstallerAction, uint64 InNumLocalChunksAvailable) = 0;` — Set the number of local chunks available for the action. @param InstallerAction The installer action to set. @param InNumLocalChunksAvailable The number of local chunks available.
- L61 _public prototype_ `virtual void OnChunkRecycleFailure(const FGuid& ChunkId) = 0;` — Increment the number of chunks that failed to recycle. @param ChunkId The id of a chunk that was not recycled.

#### class `BuildPatchServices::FInstallActionStatisticsFactory`  
`class FInstallActionStatisticsFactory`  
_L64-72_
- L71 _public prototype_ `static IInstallActionStatistics* Create(const TArray<FBuildPatchInstallerAction> &InstallerActions);` — Create an install action statistics instance. @return The created instance.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Installer/Statistics/InstallChunkSourceStatistics.h` (Private)


#### class `BuildPatchServices::IInstallChunkSourceStatistics`  
`class IInstallChunkSourceStatistics : public IInstallChunkSourceStat`  
_L16-39_
- inherits: `IInstallChunkSourceStat`
- desc: Interface to the statistics class which provides access to tracked values from an install chunk source stat.
- L23 _public prototype_ `virtual uint64 GetBytesRead() const = 0;` — @return the total number of bytes read.
- L28 _public prototype_ `virtual int32 GetNumSuccessfulChunkRecycles() const = 0;` — @return the number of chunks which were successfully loaded from local installations.
- L33 _public prototype_ `virtual int32 GetNumFailedChunkRecycles() const = 0;` — @return the number of chunks which failed to load from local installations.
- L38 _public prototype_ `virtual bool IsCurrentlyReading() const = 0;` — @return true if currently reading disk data.

#### class `BuildPatchServices::FInstallChunkSourceStatisticsFactory`  
`class FInstallChunkSourceStatisticsFactory`  
_L44-55_
- desc: A factory for creating an IInstallChunkSourceStatistics instance.
- L54 _public prototype_ `static IInstallChunkSourceStatistics* Create(ISpeedRecorder* SpeedRecorder, IInstallerAnalytics* InstallerAnalytics, IInstallActionStatistics* InInstallerActionStatistics, IFileOperationTracker* FileOperationTracker);` — Creates the install chunk source's dependency interface and exposes additional information. @param SpeedRecorder         The speed recorder instance that we send activity records to. @param InstallerAnalytics    The analytics implementation for reporting the cloud source events. @param FileOperationTracker  The file operation tracker which will be used to update data states. @return the new IInstallChunkSourceStatistics instance created.

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Installer/Statistics/MemoryChunkStoreStatistics.h` (Private)


#### class `BuildPatchServices::IMemoryChunkStoreStatistics`  
`class IMemoryChunkStoreStatistics : public IMemoryChunkStoreStat`  
_L14-63_
- inherits: `IMemoryChunkStoreStat`
- desc: Interface to the statistics class which provides access to tracked values from a memory chunk store stat.
- L21 _public prototype_ `virtual int32 GetStoreUse() const = 0;` — @return the number of chunks held.
- L26 _public prototype_ `virtual int32 GetStoreRetained() const = 0;` — @return the number of chunks held which are retained due to multiple references.
- L31 _public prototype_ `virtual int32 GetNumBooted() const = 0;` — @return the number of chunks which have been booted.
- L36 _public prototype_ `virtual int32 GetStoreSize() const = 0;` — @return the maximum number of chunks which can be held.
- L41 _public prototype_ `virtual float GetAverageStoreUse() const = 0;` — @return the average number of chunks held.
- L46 _public prototype_ `virtual int32 GetPeakStoreUse() const = 0;` — @return the peak number of chunks held.
- L51 _public prototype_ `virtual float GetAverageStoreRetained() const = 0;` — @return the average number of chunks held which are retained due to multiple references.
- L56 _public prototype_ `virtual int32 GetPeakStoreRetained() const = 0;` — @return the peak number of chunks held which are retained due to multiple references.
- L62 _public prototype_ `virtual void SetMultipleReferencedChunk(TSet<FGuid> MultipleReferencedChunks) = 0;` — Sets the chunks that are referenced multiple times in order to track retained. @param MultipleReferencedChunks For retained stats, the set of chunks which have multiple references.

#### class `BuildPatchServices::FMemoryChunkStoreStatisticsFactory`  
`class FMemoryChunkStoreStatisticsFactory`  
_L68-77_
- desc: A factory for creating an IMemoryChunkStoreStatistics instance.
- L76 _public prototype_ `static IMemoryChunkStoreStatistics* Create(IFileOperationTracker* FileOperationTracker);` — Creates a statistics interface for getting access to store usage stats, and also forwards information to update the file operation tracker. @param FileOperationTracker          The file operation tracker which will be used to update data states. @return the new IMemoryChunkStoreStatistics instance created.

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Installer/Statistics/VerifierStatistics.h` (Private)


#### class `BuildPatchServices::IVerifierStatistics`  
`class IVerifierStatistics : public IVerifierStat`  
_L16-44_
- inherits: `IVerifierStat`
- desc: Interface to the statistics class which provides access to tracked values from a verifier stat.
- L23 _public prototype_ `virtual uint64 GetBytesVerified() const = 0;` — @return the total number of bytes verified.
- L28 _public prototype_ `virtual int32 GetNumSuccessfulFilesVerified() const = 0;` — @return the number of file which were successfully verified.
- L33 _public prototype_ `virtual int32 GetNumFailedFilesVerified() const = 0;` — @return the number of files which failed verification.
- L38 _public prototype_ `virtual TMap<EVerifyError, int32> GetVerifyErrorCounts() const = 0;` — @return the map of error result to count.
- L43 _public prototype_ `virtual bool IsCurrentlyReading() const = 0;` — @return true if currently reading disk data.

#### class `BuildPatchServices::FVerifierStatisticsFactory`  
`class FVerifierStatisticsFactory`  
_L49-60_
- desc: A factory for creating an IVerifierStatistics instance.
- L59 _public prototype_ `static IVerifierStatistics* Create(ISpeedRecorder* SpeedRecorder, FBuildPatchProgress* BuildProgress, IFileOperationTracker* FileOperationTracker);` — Creates the verifier's dependency interface and exposes additional information. @param SpeedRecorder         The speed recorder instance that we send activity records to. @param BuildProgress         The legacy progress implementation to bridge the system stats to. @param FileOperationTracker  The file operation tracker which will be used to update data states. @return the new IVerifierStatistics instance created.

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace BuildPatchServices`

### `Source/Runtime/Online/BuildPatchServices/Private/Installer/UriProvider.h` (Private)


#### class `BuildPatchServices::IUriProvider`  
`class IUriProvider`  
_L23-37_
- desc: An interface providing the ability to retrieve a URI for files downloading. Comparing to SignedUriProvider this interface is more general and hides MessagePump-related implementation inside. Methods of this class should be called from the same thread and this class doesn't support two concurrent requests.
- L27 _public function_ `virtual ~IUriProvider()`
- L36 _public prototype_ `virtual void RequestUri(const FString& DeltaId, const FString& BuildId, FUriProviderCompleteDelegate& OnCompleteDelegate) = 0;` — Starts a new request to obtain a URI for delta file. If there is another request in flight, this method will call OnCompleteDelegate delegate with false result immediately. @param DeltaId               The ID of the delta file for which it is needed to obtain a URI. @param BuildId               Build ID for the corresponding delta file. @param OnCompleteDelegate    The delegate that will be called when the URI will be ready.

#### class `BuildPatchServices::FUriProviderFactory`  
`class FUriProviderFactory`  
_L42-52_
- desc: A factory for creating the default implementation of IUriProvider.
- L51 _public prototype_ `static TSharedRef<IUriProvider, ESPMode::ThreadSafe> Create(IMessagePump* MessagePump, TArray<FString> CloudDirectories);` — Instantiates an instance of an IUriProvider, using the MessagePump. @param MessagePump      The message pump object that will be used for URIs obtaining. @param CloudDirectores  A list of cloud directories that can be used for generating a URI. @return the new IUriProvider instance created.

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace BuildPatchServices`
- L16 _delegate_ `DECLARE_DELEGATE_ThreeParams(FUriProviderCompleteDelegate, bool , const FString& , bool );` — Delegate called when URI is ready. @param bSuccessful     Status of the request, true means success. @param Uri             The URI itself that can be used for downloading the file. @param bNeedRerty      Flag that allows a retry to be used if the URI cannot be obtained.
- L16 _prototype_ `DECLARE_DELEGATE_ThreeParams(FUriProviderCompleteDelegate, bool , const FString& , bool );` (scope `BuildPatchServices`) — Delegate called when URI is ready. @param bSuccessful     Status of the request, true means success. @param Uri             The URI itself that can be used for downloading the file. @param bNeedRerty      Flag that allows a retry to be used if the URI cannot be obtained.

### `Source/Runtime/Online/BuildPatchServices/Private/Installer/Verifier.h` (Private)


#### enum `BuildPatchServices::EVerifyResult`  
`enum class EVerifyResult : uint32`  
_L19-37_
- desc: An enum defining the result of a verification process.
- L21 _public enumerator_ `Success = 0`
- L24 _public enumerator_ `Aborted` — If the process was ended due to an external cancel.
- L27 _public enumerator_ `FileMissing` — The verify failed due to a missing file.
- L30 _public enumerator_ `OpenFileFailed` — The verify failed due to a file failing to open.
- L33 _public enumerator_ `HashCheckFailed` — The expected data hash for a file did not match.
- L36 _public enumerator_ `FileSizeFailed` — A file did not match the expected size.

#### class `BuildPatchServices::IVerifier`  
`class IVerifier : public IControllable`  
_L58-76_
- inherits: `IControllable`
- desc: An interface providing the functionality to verify a local installation.
- L69 _public prototype_ `virtual EVerifyResult Verify(TArray<FString>& CorruptFiles) = 0;` — Verifies a local directory structure against a given manifest. NOTE: This function is blocking and will not return until finished. Don't run on main thread. @param CorruptFiles     OUT  The array of files that do not match or are locally missing. @return    EVerifiyResult::Success if no file errors occurred AND the verification was successful. Otherwise it will return the first error encountered during verification.
- L75 _public prototype_ `virtual void AddTouchedFiles(const TSet<FString>& TouchedFiles) = 0;` — Register any files that have been built so that they are verified in addition to any marked for repair when Verify is ran. @param TouchedFiles          The array of files that have been created or edited.

#### class `BuildPatchServices::FVerifierFactory`  
`class FVerifierFactory`  
_L78-92_
- L89 _public prototype_ `static IVerifier* Create(IFileSystem* FileSystem, IVerifierStat* VerifierStat, EVerifyMode VerifyMode, IBuildInstallerSharedContextPtr SharedContext, IBuildManifestSet* ManifestSet, FString VerifyDirectory, FString StagedFileDirectory, bool bUseSHA1StageFilenames, const TMap<FString, FString>& PerFileSubdirectories);` — Creates a verifier class that will verify a local directory structure against a given manifest, optionally taking account of a staging directory where alternative files are used. @param StagedFileDirectory    A stage directory for updated files, ignored if empty string. If a file exists here, it will be checked instead of the one in VerifyDirectory. @param bUseSHA1StageFilenames A boolean value to indicate that we use hashes instead of real file names. @param PerFileSubdirectories  A map of path adjustments to use keyed off the manifest filename, leave empty if unneeded. @return The verifier object. Delete when complete. See IVerifier class for usage.

#### class `BuildPatchServices::IVerifierStat`  
`class IVerifierStat`  
_L98-141_
- desc: This interface defines the statistics class required by the verifier system. It should be implemented in order to collect desired information which is being broadcast by the system.
- L101 _public prototype_ `virtual ~IVerifierStat() = default;`
- L108 _public prototype_ `virtual void OnFileStarted(const FString& Filename, int64 FileSize) = 0;` — Called each time a file is going to be verified. @param Filename      The filename of the file. @param FileSize      The size of the file being verified.
- L115 _public prototype_ `virtual void OnFileProgress(const FString& Filename, int64 TotalBytes) = 0;` — Called during a file verification with the current progress. @param Filename      The filename of the file. @param TotalBytes    The number of bytes processed so far.
- L122 _public prototype_ `virtual void OnFileCompleted(const FString& Filename, EVerifyResult VerifyResult) = 0;` — Called each time a file has finished being verified. @param Filename      The filename of the file. @param VerifyResult  The result of the file's verify test.
- L128 _public prototype_ `virtual void OnFileRead(const ISpeedRecorder::FRecord& Record) = 0;` — Called each time a read operation is made. @param Record        The details for the operation.
- L134 _public prototype_ `virtual void OnProcessedDataUpdated(int64 TotalBytes) = 0;` — Called to update the total amount of bytes which have been processed. @param TotalBytes    The number of bytes processed so far.
- L140 _public prototype_ `virtual void OnTotalRequiredUpdated(int64 TotalBytes) = 0;` — Called to update the total number of bytes to be processed. @param TotalBytes    The total number of bytes to be processed.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace BuildPatchServices`
- L45 _prototype_ `bool TryConvertToVerifyResult(EVerifyError InVerifyError, EVerifyResult& OutVerifyResult);` (scope `BuildPatchServices`) — Used to convert a EVerifyError to a EVerifyResult. @param InVerifyError   - Error to convert. @param OutVerifyResult - Reference to completed. @return true if successful.
- L53 _prototype_ `bool TryConvertToVerifyError(EVerifyResult InVerifyResult, EVerifyError& OutVerifyError);` (scope `BuildPatchServices`) — Used to convert a EVerifyResult to a EVerifyError. @param InVerifyResult - Result to convert. @param OutVerifyError - Reference to complete. @return true if successful.

### `Source/Runtime/Online/BuildPatchServices/Public/BuildPatchDelta.h` (Public)


#### enum `BuildPatchServices::EDeltaPolicy`  
`enum class EDeltaPolicy : uint32`  
_L14-26_
- desc: An enum defining the desired policy for requesting an optimised delta.
- L17 _public enumerator_ `TryFetchContinueWithout = 0` — Try to fetch, but continue without if request fail.
- L20 _public enumerator_ `Expect` — Expect the delta to exist, hard fail the installation if it could not be retrieved.
- L23 _public enumerator_ `Skip` — Expect the delta to not exist, skipping any attempt to use one.
- L25 _public enumerator_ `InvalidOrMax`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace BuildPatchServices`
- L35 _prototype_ `FString GetChunkDeltaFilename(const IBuildManifestRef& SourceManifest, const IBuildManifestRef& DestinationManifest, const FString& FilenameTrailer);` (scope `BuildPatchServices`) — Based on the source and destination manifests, get the filename for the delta that optimises patching from source to destination. @param SourceManifest        The source manifest. @param DestinationManifest   The destination manifest. @param FilenameTrailer       This is an optional parameter to allow for multiple optimized deltas for the same build pairing. If unneeded, leave as "". @return the CloudDir relative delta filename.
- L37 _prototype_ `IBuildManifestPtr MergeDeltaManifest(const IBuildManifestRef& Manifest, const IBuildManifestRef& Delta);` (scope `BuildPatchServices`)
- L42 _function_ `inline const TCHAR* LexToString(BuildPatchServices::EDeltaPolicy DeltaPolicy)`
- L44 _macro_ `#define CASE_ENUM_TO_STR(Value) case BuildPatchServices::EDeltaPolicy::Value: return TEXT(#Value)`
- L55 _function_ `inline void LexFromString(BuildPatchServices::EDeltaPolicy& DeltaPolicy, const TCHAR* Buffer)`
- L57 _macro_ `#define RETURN_IF_EQUAL(Value) if (FCString::Stricmp(Buffer, TEXT(#Value)) == 0) { DeltaPolicy = BuildPatchServices::EDeltaPolicy::Value; return; }`

### `Source/Runtime/Online/BuildPatchServices/Public/BuildPatchFeatureLevel.h` (Public)


#### enum `BuildPatchServices::EFeatureLevel`  
`enum class EFeatureLevel : int32`  
_L11-88_
- desc: An enum type to describe supported features of a certain manifest.
- L14 _public enumerator_ `Original = 0` — The original version.
- L16 _public enumerator_ `CustomFields` — Support for custom fields.
- L18 _public enumerator_ `StartStoringVersion` — Started storing the version number.
- L20 _public enumerator_ `DataFileRenames` — Made after data files where renamed to include the hash value, these chunks now go to ChunksV2.
- L22 _public enumerator_ `StoresIfChunkOrFileData` — Manifest stores whether build was constructed with chunk or file data.
- L24 _public enumerator_ `StoresDataGroupNumbers` — Manifest stores group number for each chunk/file data for reference so that external readers don't need to know how to calculate them.
- L26 _public enumerator_ `ChunkCompressionSupport` — Added support for chunk compression, these chunks now go to ChunksV3. NB: Not File Data Compression yet.
- L28 _public enumerator_ `StoresPrerequisitesInfo` — Manifest stores product prerequisites info.
- L30 _public enumerator_ `StoresChunkFileSizes` — Manifest stores chunk download sizes.
- L32 _public enumerator_ `StoredAsCompressedUClass` — Manifest can optionally be stored using UObject serialization and compressed.
- L34 _public enumerator_ `UNUSED_0` — These two features were removed and never used.
- L35 _public enumerator_ `UNUSED_1`
- L37 _public enumerator_ `StoresChunkDataShaHashes` — Manifest stores chunk data SHA1 hash to use in place of data compare, for faster generation.
- L39 _public enumerator_ `StoresPrerequisiteIds` — Manifest stores Prerequisite Ids.
- L41 _public enumerator_ `StoredAsBinaryData` — The first minimal binary format was added. UObject classes will no longer be saved out when binary selected.
- L43 _public enumerator_ `VariableSizeChunksWithoutWindowSizeChunkInfo` — Temporary level where manifest can reference chunks with dynamic window size, but did not serialize them. Chunks from here onwards are stored in ChunksV4.
- L45 _public enumerator_ `VariableSizeChunks` — Manifest can reference chunks with dynamic window size, and also serializes them.
- L47 _public enumerator_ `UsesRuntimeGeneratedBuildId` — Manifest uses a build id generated from its metadata.
- L49 _public enumerator_ `UsesBuildTimeGeneratedBuildId` — Manifest uses a build id generated unique at build time, and stored in manifest.
- L51 _public enumerator_ `StoresFileMD5HashesAndMIMEType` — Manifests generated with this feature level onwards will store the MD5 hash and the calculated MIME type of each file.
- L53 _public enumerator_ `StoresFileSHA256Hashes` — Manifests generated with this feature level onwards will store the SHA256 hash of each file.
- L55 _public enumerator_ `StoresUninstallActions` — Added support for Uninstall Actions.
- L58 _public enumerator_ `ChunkEncryptionSupport` — Added full support for chunk encryption, additionally stores encyption secrets, as well as the CompressedDataSize and AuthTag for each chunk. Chunks from here onwards are stored in ChunksV5.
- L60 _public enumerator_ `ChunksStoredBySecret` — Added the secretID as part of the chunk pathing within a CloudDir
- L63 _public enumerator_ `ManifestEncryptionSupport` — Completed full support for BPS data encryption, if a manifest got encrypted, it will additionally store encryption data and most fields will have been replaced by empty or functional but not accurate data.
- L66 _public enumerator_ `LatestPlusOne` — !! Always after the latest version entry, signifies the latest version plus 1 to allow the following Latest alias.
- L68 _public enumerator_ `Latest = (LatestPlusOne - 1)` — An alias for the actual latest version value.
- L70 _public enumerator_ `LatestNoChunks = StoresChunkFileSizes` — An alias to provide the latest version of a manifest supported by file data (nochunks).
- L72 _public enumerator_ `LatestJson = StoresPrerequisiteIds` — An alias to provide the latest version of a manifest supported by a json serialized format.
- L74 _public enumerator_ `LatestNoOpenSSL = StoresFileMD5HashesAndMIMEType` — An alias to provide the latest version of a manifest supported by generation runs on platforms without OpenSSL module support.
- L76 _public enumerator_ `LatestUnencryptedChunks = StoresUninstallActions` — An alias to provide the latest version of a manifest with unencrypted chunks.
- L78 _public enumerator_ `FirstOptimisedDelta = UsesRuntimeGeneratedBuildId` — An alias to provide the first available version of optimised delta manifest saving.
- L81 _public enumerator_ `StoresUniqueBuildId = UsesRuntimeGeneratedBuildId` — More aliases, but this time for values that have been renamed
- L85 _public enumerator_ `BrokenJsonVersion = 255` — JSON manifests were stored with a version of 255 during a certain CL range due to a bug. We will treat this as being StoresChunkFileSizes in code.
- L87 _public enumerator_ `Invalid = -1` — This is for UObject default, so that we always serialize it.

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace BuildPatchServices`
- L91 _function_ `inline const TCHAR* LexToString(BuildPatchServices::EFeatureLevel FeatureLevel)`
- L94 _macro_ `#define CASE_ENUM_TO_STR(Value) case BuildPatchServices::EFeatureLevel::Value: return TEXT(#Value)`
- L128 _function_ `inline void LexFromString(BuildPatchServices::EFeatureLevel& FeatureLevel, const TCHAR* Buffer)`
- L131 _macro_ `#define RETURN_IF_EQUAL(Value) if (FCString::Stricmp(Buffer, TEXT(#Value)) == 0) { FeatureLevel = BuildPatchServices::EFeatureLevel::Value; return; }`

### `Source/Runtime/Online/BuildPatchServices/Public/BuildPatchInstall.h` (Public)


#### enum `BuildPatchServices::EInstallMode`  
`enum class EInstallMode : uint32`  
_L15-33_
- desc: An enum defining the installation mode that should be used.
- L18 _public enumerator_ `StageFiles = 0` — Construct all required files, but only stage them ready to be completed later.
- L21 _public enumerator_ `DestructiveInstall` — Full installation, allowing immediate changes to be made to existing files. The installation is unusable until complete.
- L24 _public enumerator_ `NonDestructiveInstall` — Full installation, staging all required files before moving them all into place in a final step. The installation is still usable if canceled before the moving staging begins.
- L27 _public enumerator_ `PrereqOnly` — Execute the prerequisite installer only, downloading it first if necessary. If the specified manifest has no prerequisites, this will result in an error.
- L30 _public enumerator_ `Preload` — Download chunk data to file only, to be unpacked as a later process. Chunk data will not be decrypted or decompressed.
- L32 _public enumerator_ `InvalidOrMax`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace BuildPatchServices`
- L35 _prototype_ `uint64 CalculateRequiredDiskSpace(const IBuildManifestPtr& CurrentManifest, const IBuildManifestRef& BuildManifest, const EInstallMode& InstallMode, const TSet<FString>& InstallTags);` (scope `BuildPatchServices`)
- L40 _function_ `inline const TCHAR* LexToString(BuildPatchServices::EInstallMode InstallMode)`
- L42 _macro_ `#define CASE_ENUM_TO_STR(Value) case BuildPatchServices::EInstallMode::Value: return TEXT(#Value)`
- L55 _function_ `inline void LexFromString(BuildPatchServices::EInstallMode& InstallMode, const TCHAR* Buffer)`
- L57 _macro_ `#define RETURN_IF_EQUAL(Value) if (FCString::Stricmp(Buffer, TEXT(#Value)) == 0) { InstallMode = BuildPatchServices::EInstallMode::Value; return; }`

### `Source/Runtime/Online/BuildPatchServices/Public/BuildPatchMessage.h` (Public)


#### struct `BuildPatchServices::FChunkSourceEvent`  
`struct FChunkSourceEvent`  
_L14-34_
- desc: A message describing an event that occurred for a chunk source.
- L31 _public member_ `EType Event;` — The type of event that occurred.
- L33 _public member_ `FString Location;` — The location context for the source, could be cloud root, install location, chunkdb file etc.

#### enum `BuildPatchServices::FChunkSourceEvent::EType`  
`enum class EType : uint32`  
_L17-28_
- desc: Describes the event type.
- L20 _public enumerator_ `AccessLost = 0` — Access was lost to the source.
- L22 _public enumerator_ `AccessRegained` — Access has been regained after being lost.
- L24 _public enumerator_ `HttpRequestFailed` — HTTP request failed
- L25 _public enumerator_ `Retired`
- L27 _public enumerator_ `InvalidOrMax`

#### struct `BuildPatchServices::FInstallationFileAction`  
`struct FInstallationFileAction`  
_L39-60_
- desc: A message describing an action taken to an installation file.
- L57 _public member_ `EType Action;` — The type of action that occurred.
- L59 _public member_ `FString Filename;` — The filename affected, relative to the install location.

#### enum `BuildPatchServices::FInstallationFileAction::EType`  
`enum class EType : uint32`  
_L42-54_
- desc: Describes the action type.
- L45 _public enumerator_ `Staged = 0` — The file was completed in the staging location.
- L47 _public enumerator_ `Added` — The file was added to the final install location.
- L49 _public enumerator_ `Updated` — The file was updated in the final install location.
- L51 _public enumerator_ `Removed` — The file was removed from the final install location.
- L53 _public enumerator_ `InvalidOrMax`

#### struct `BuildPatchServices::FChunkUriRequest`  
`struct FChunkUriRequest`  
_L65-72_
- desc: A Request for a chunk
- L67 _public member_ `FString CloudDirectory;`
- L68 _public member_ `FString ChunkCloudSubdirectory;`
- L69 _public member_ `FString ChunkPath;`
- L70 _public member_ `FString UniqueBuildId;`
- L71 _public member_ `bool bChunkFromDelta = false;`

#### struct `BuildPatchServices::FDeltaUriRequest`  
`struct FDeltaUriRequest`  
_L77-83_
- desc: A Request for a delta file
- L79 _public member_ `FString CloudDirectory;`
- L80 _public member_ `FString DeltaCloudSubdirectory;`
- L81 _public member_ `FString DeltaPath;`
- L82 _public member_ `FString UniqueBuildId;`

#### struct `BuildPatchServices::FChunkUriResponse`  
`struct FChunkUriResponse`  
_L88-97_
- desc: A Response containing the actual location of the chunk
- L92 _public member_ `bool bFailed = false;` — Set this to true if the response can not be fulfilled. This will fail the chunk requests and subsequently the installation.
- L93 _public member_ `FString Uri;`
- L96 _public member_ `TMap<FString, FString> AdditionalHeaders;` — These headers <name, value> will be added to the HTTP request.

#### struct `BuildPatchServices::FGenericMessage`  
`struct FGenericMessage`  
_L99-120_
- L117 _public member_ `EType Type;`
- L118 _public member_ `FGuid ChunkId;`
- L119 _public member_ `FString Payload1, Payload2;`
- L119 _public member_ `FString Payload1, Payload2;`

#### enum `BuildPatchServices::FGenericMessage::EType`  
`enum class EType : uint32`  
_L103-115_
- desc: Set of informational messages the installer can send to the client to update UI or otherwise react.
- L109 _public enumerator_ `CloudSourceUsed` — Posted when a chunk is requested of the cloud source ONLY WHEN CHUNKDBS ARE PRESENT. This is useful if the installer is not expected to be downloading anything independently and you want to log this case. Note that even when chunks are fully provided, cancellation and resumption can lose "harvested" chunks that were resident only in non-persistent backing store causing a download
- L114 _public enumerator_ `CDNDownloadFailed` — Posted when a CDN/CloudDir has failed a download and is dropped in priority. Payload1 = CDN that failed, Payload2 = CDN that is considered "best" after this failure.

#### enum `BuildPatchServices::EMessageRequests`  
`enum class EMessageRequests : uint32`  
_L124-132_
- desc: Flag for which Requests a message handler expects to receive, allows for internal implementation optimisation.
- L127 _public enumerator_ `None = 0` — Does not respond to any requests - message listener only.
- L129 _public enumerator_ `ChunkUriRequest = 0x1` — Will respond to chunk URI requests.

#### struct `BuildPatchServices::FExpiratedUriResponse`  
`struct FExpiratedUriResponse`  
_L138-142_
- desc: A Response containing the actual location of the file and URI's expiration time
- L140 _public member_ `FString Uri;`
- L141 _public member_ `FString SignatureExpiration;`

#### struct `BuildPatchServices::FExpiratedUrisResponse`  
`struct FExpiratedUrisResponse`  
_L147-151_
- desc: A Response containing an array of expirated URIs (e.g. different CDNs)
- L149 _public member_ `TArray<FExpiratedUriResponse> ExpiratedUri;`
- L150 _public member_ `bool bNeedRetry = true;`

#### class `BuildPatchServices::FMessageHandler`  
`class FMessageHandler`  
_L156-206_
- desc: Base class of a message handler, this should be inherited from and passed to an installer to receive messages that you want to handle.
- L159 _public function_ `FMessageHandler(EMessageRequests InMessageRequests) : MessageRequests(InMessageRequests)`
- L163 _public prototype_ `virtual ~FMessageHandler() = default;`
- L170 _public function_ `virtual void HandleMessage(const FGenericMessage& Message)` — Handle generic information posting. This can be called from any thread and should not take appreciable time as it blocks further installation. See FGenericMessage for payload contents and types
- L176 _public function_ `virtual void HandleMessage(const FChunkSourceEvent& Message)` — Handles a chunk source event message. @param Message   The message to be handled.
- L182 _public function_ `virtual void HandleMessage(const FInstallationFileAction& Message)` — Handles an installation file action message. @param Message   The message to be handled.
- L190 _public function_ `virtual bool HandleRequest(const FChunkUriRequest& Request, TFunction<void(FChunkUriResponse)> OnResponse)` — Handles responding to a chunk Uri request @param Request   The request for a chunk @param OnResponse   The function to callback once the chunk has been found @return true if request is handled successfully
- L197 _public function_ `virtual bool HandleRequest(const FDeltaUriRequest& Request, TFunction<void(FExpiratedUrisResponse)> OnResponse)` — Handles responding to a delta Uri request @param Request   The request for a delta Uri @param OnResponse   The function to callback once the Uri has been found
- L202 _public function_ `EMessageRequests GetMessageRequests() const` — @return the message request flags.
- L205 _private member_ `const EMessageRequests MessageRequests;`

#### class `BuildPatchServices::FDefaultMessageHandler`  
`class FDefaultMessageHandler : public FMessageHandler`  
_L208-235_
- inherits: `FMessageHandler`
- L213 _public function_ `FDefaultMessageHandler() : FMessageHandler(static_cast<EMessageRequests>(0xFFFFFFFF))` — Default constructor passes flags to always support all requests
- L219 _public function_ `virtual bool HandleRequest(const FChunkUriRequest& Request, TFunction<void(FChunkUriResponse)> OnResponse) override` — This gets called if all registered handlers return false to HandleRequest. If there are _no_ handlers then this is entirely sidestepped in the cloud chunk source.
- L227 _public function_ `virtual bool HandleRequest(const FDeltaUriRequest& Request, TFunction<void(FExpiratedUrisResponse)> OnResponse) override`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace BuildPatchServices`
- L133 _prototype_ `ENUM_CLASS_FLAGS(EMessageRequests);` (scope `BuildPatchServices`)
- L239 _function_ `inline const TCHAR* LexToString(BuildPatchServices::FChunkSourceEvent::EType ChunkSourceEventType)`
- L241 _macro_ `#define CASE_ENUM_TO_STR(Value) case BuildPatchServices::FChunkSourceEvent::EType::Value: return TEXT(#Value)`
- L253 _function_ `inline void LexFromString(BuildPatchServices::FChunkSourceEvent::EType& ChunkSourceEventType, const TCHAR* Buffer)`
- L255 _macro_ `#define RETURN_IF_EQUAL(Value) if (FCString::Stricmp(Buffer, TEXT(#Value)) == 0) { ChunkSourceEventType = BuildPatchServices::FChunkSourceEvent::EType::Value; return; }`
- L271 _function_ `inline const TCHAR* LexToString(BuildPatchServices::FInstallationFileAction::EType InstallationFileActionType)`
- L273 _macro_ `#define CASE_ENUM_TO_STR(Value) case BuildPatchServices::FInstallationFileAction::EType::Value: return TEXT(#Value)`
- L286 _function_ `inline void LexFromString(BuildPatchServices::FInstallationFileAction::EType& InstallationFileActionType, const TCHAR* Buffer)`
- L288 _macro_ `#define RETURN_IF_EQUAL(Value) if (FCString::Stricmp(Buffer, TEXT(#Value)) == 0) { InstallationFileActionType = BuildPatchServices::FInstallationFileAction::EType::Value; return; }`

### `Source/Runtime/Online/BuildPatchServices/Public/BuildPatchServices.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/Online/BuildPatchServices/Public/BuildPatchServicesSingleton.h` (Public)


#### class `FBuildPatchServices`  
`class FBuildPatchServices`  
_L10-53_
- L13 _public function_ `static bool IsAvailable()`
- L18 _public function_ `static IBuildPatchServicesModule& Get()`
- L23 _public function_ `static const BuildPatchServices::FBuildPatchServicesInitSettings& GetSettings()`
- L28 _public function_ `static void Set( const FName& Value, const BuildPatchServices::FBuildPatchServicesInitSettings& BuildPatchServicesInitSettings = BuildPatchServices::FBuildPatchServicesInitSettings())`
- L41 _public function_ `static void Shutdown()`
- L51 _private member_ `static FName ModuleName;`
- L52 _private member_ `static BuildPatchServices::FBuildPatchServicesInitSettings InitSettings;`

### `Source/Runtime/Online/BuildPatchServices/Public/BuildPatchSettings.h` (Public)


#### enum `BuildPatchServices::EFileSortOrder`  
`enum class EFileSortOrder : uint8`  
_L35-41_
- desc: An enum defining the method of sorting files in a build.
- L37 _public enumerator_ `AlphabeticalFilename = 0`
- L38 _public enumerator_ `AlphabeticalTagThenFilename`
- L40 _public enumerator_ `InvalidOrMax`

#### struct `BuildPatchServices::FBuildPatchServicesInitSettings`  
`struct FBuildPatchServicesInitSettings`  
_L46-61_
- desc: Defines a list of all build patch services initialization settings, can be used to override default init behaviors.
- L52 _public prototype_ `FBuildPatchServicesInitSettings();` — Default constructor. Initializes all members with default behavior values.
- L56 _public member_ `FString ApplicationSettingsDir;` — The application settings directory.
- L58 _public member_ `FString ProjectName;` — The application project name.
- L60 _public member_ `FString LocalMachineConfigFileName;` — The local machine config file name.

#### struct `BuildPatchServices::FInstallerAction`  
`struct FInstallerAction`  
_L63-243_
- L75 _public prototype_ `static FInstallerAction MakeInstall(const IBuildManifestRef& Manifest, TSet<FString> InstallTags = TSet<FString>(), FString InstallSubdirectory = FString(), FString CloudSubdirectory = FString());` — Creates an install action. @param Manifest          The manifest for the build to be installed. @param InstallTags       The install tags to use if selectively installing files. If empty set, all files will be installed. @param InstallSubdirectory  The subdirectory to install this data to inside of the main install directory. @param CloudSubdirectory    The subdirectory of the cloud distribution root that this patch data should be sourced. @return the action setup for performing an installation.
- L86 _public prototype_ `static FInstallerAction MakeUpdate(const IBuildManifestRef& CurrentManifest, const IBuildManifestRef& InstallManifest, TSet<FString> InstallTags = TSet<FString>(), FString InstallSubdirectory = FString(), FString CloudSubdirectory = FString());` — Creates an update action. @param CurrentManifest   The manifest for the build currently installed. @param InstallManifest   The manifest for the build to be installed. @param InstallTags       The install tags to use if selectively installing files. If empty set, all files will be updated, or added if missing. @param InstallSubdirectory  The subdirectory to install this data to inside of the main install directory. @param CloudSubdirectory    The subdirectory of the cloud distribution root that this patch data should be sourced. @return the action setup for performing an update.
- L96 _public prototype_ `static FInstallerAction MakeRepair(const IBuildManifestRef& Manifest, TSet<FString> InstallTags = TSet<FString>(), FString InstallSubdirectory = FString(), FString CloudSubdirectory = FString());` — Creates a verify and repair action. @param Manifest          The manifest for the build being repaired. @param InstallTags       The install tags to use if selectively installing files. If empty set, all files will be repaired. @param InstallSubdirectory  The subdirectory to install this data to inside of the main install directory. @param CloudSubdirectory    The subdirectory of the cloud distribution root that this patch data should be sourced. @return the action setup forcing an SHA check, and repair of all tagged files.
- L107 _public prototype_ `static FInstallerAction MakeVerifyOnly(const IBuildManifestRef& Manifest, TSet<FString> InstallTags = TSet<FString>(), FString InstallSubdirectory = FString(), FString CloudSubdirectory = FString());` — Creates a verify only action. Note that MakeRepair should be used usually, which will verify and try to repair any issues right away. This action will only check integrity and fail or succeed based on results. @param Manifest          The manifest for the build being verified. @param InstallTags       The install tags to use if selectively installing files. If empty set, all files will be repaired. @param InstallSubdirectory  The subdirectory to install this data to inside of the main install directory. @param CloudSubdirectory    The subdirectory of the cloud distribution root that this patch data should be sourced. @return the action setup forcing an SHA check, and repair of all tagged files.
- L116 _public prototype_ `static FInstallerAction MakeUninstall(const IBuildManifestRef& Manifest, FString InstallSubdirectory = FString(), FString CloudSubdirectory = FString());` — Creates an uninstall action. @param Manifest          The manifest for the build currently installed. @param InstallSubdirectory  The subdirectory to install this data to inside of the main install directory. @param CloudSubdirectory    The subdirectory of the cloud distribution root that this patch data should be sourced. @return the action setup for performing an uninstall, deleting all files referenced by the manifest.
- L127 _public function_ `static FInstallerAction MakeInstallOrUpdate(const IBuildManifestPtr& CurrentManifest, const IBuildManifestRef& InstallManifest, TSet<FString> InstallTags = TSet<FString>(), FString InstallSubdirectory = FString(), FString CloudSubdirectory = FString())` — Helper for creating an install action or update action based on validity of CurrentManifest. @param CurrentManifest   The manifest for the build currently installed, invalid if no build installed. @param InstallManifest   The manifest for the build to be installed. @param InstallTags       The install tags to use if selectively installing files. If empty set, all files will be installed/updated, or added if missing. @param InstallSubdirectory  The subdirectory to install this data to inside of the main install directory. @param CloudSubdirectory    The subdirectory of the cloud distribution root that this patch data should be sourced. @return the action setup for performing an install or update.
- L143 _public prototype_ `bool IsInstall() const;` — @return true if this action intent is to perform a fresh installation.
- L148 _public prototype_ `bool IsUpdate() const;` — @return true if this action intent is to update an existing installation.
- L153 _public prototype_ `bool IsRepair() const;` — @return true if this action intent is to repair an existing installation.
- L158 _public prototype_ `bool IsVerifyOnly() const;` — @return true if this action intent is to only verify an existing installation, without repair or modification.
- L163 _public prototype_ `bool IsUninstall() const;` — @return true if this action intent is to uninstall an installation.
- L168 _public prototype_ `const TSet<FString>& GetInstallTags() const;` — @return the install tags for the action.
- L173 _public prototype_ `const FString& GetInstallSubdirectory() const;` — @return the install subdirectory for the action.
- L178 _public prototype_ `const FString& GetCloudSubdirectory() const;` — @return the cloud subdirectory for the action.
- L183 _public prototype_ `IBuildManifestRef GetCurrentManifest() const;` — @return the manifest for the current installation, this will runtime assert if called invalidly (see TryGetCurrentManifest).
- L188 _public prototype_ `IBuildManifestRef GetInstallManifest() const;` — @return the manifest for the desired installation, this will runtime assert if called invalidly (see TryGetInstallManifest).
- L195 _public function_ `IBuildManifestPtr TryGetCurrentManifest() const` — Helper for getting the current manifest if nullable is preferred. @return the manifest for the current installation, if valid.
- L208 _public function_ `IBuildManifestPtr TryGetInstallManifest() const` — Helper for getting the install manifest if nullable is preferred. @return the manifest for the new installation, if valid.
- L221 _public function_ `IBuildManifestRef GetCurrentOrInstallManifest() const` — Helper for getting the current manifest, or install manifest if no current manifest. One will always be valid. @return the current, or the install manifest, based on validity respectively.
- L230 _public function_ `IBuildManifestRef GetInstallOrCurrentManifest() const` — Helper for getting the install manifest, or current manifest if no install manifest. One will always be valid. @return the install, or the current manifest, based on validity respectively.
- L236 _private prototype_ `FInstallerAction();`
- L237 _private member_ `IBuildManifestPtr CurrentManifest;`
- L238 _private member_ `IBuildManifestPtr InstallManifest;`
- L239 _private member_ `TSet<FString> InstallTags;`
- L240 _private member_ `FString InstallSubdirectory;`
- L241 _private member_ `FString CloudSubdirectory;`
- L242 _private member_ `EInstallActionIntent ActionIntent;`

#### struct `BuildPatchServices::FInstallerConfiguration`  
`struct FInstallerConfiguration`  
_L248-269_
- desc: DEPRECATED STRUCT. Please use FBuildInstallerConfiguration.
- L250 _public prototype_ `FInstallerConfiguration(const IBuildManifestRef& InInstallManifest);`
- L251 _public prototype_ `FInstallerConfiguration(const FInstallerConfiguration& CopyFrom);`
- L252 _public prototype_ `FInstallerConfiguration(FInstallerConfiguration&& MoveFrom);`
- L255 _public member_ `IBuildManifestRef InstallManifest;`
- L256 _public member_ `IBuildManifestPtr CurrentManifest = nullptr;`
- L257 _public member_ `FString InstallDirectory;`
- L258 _public member_ `FString StagingDirectory;`
- L259 _public member_ `FString BackupDirectory;`
- L260 _public member_ `TArray<FString> ChunkDatabaseFiles;`
- L261 _public member_ `TArray<FString> CloudDirectories;`
- L262 _public member_ `TSet<FString> InstallTags;`
- L263 _public member_ `EInstallMode InstallMode = EInstallMode::NonDestructiveInstall;`
- L264 _public member_ `EVerifyMode VerifyMode = EVerifyMode::ShaVerifyAllFiles;`
- L265 _public member_ `EDeltaPolicy DeltaPolicy = EDeltaPolicy::Skip;`
- L266 _public member_ `bool bIsRepair = false;`
- L267 _public member_ `bool bRunRequiredPrereqs = true;`
- L268 _public member_ `bool bAllowConcurrentExecution = false;`

#### struct `BuildPatchServices::FBuildInstallerConfiguration`  
`struct FBuildInstallerConfiguration`  
_L274-378_
- desc: Defines a list of all the options of an installation task.
- L279 _public prototype_ `FBuildInstallerConfiguration(TArray<FInstallerAction> InstallerActions);` — Construct with an array of action objects
- L283 _public member_ `TArray<FInstallerAction> InstallerActions;` — The array of intended actions to perform.
- L285 _public member_ `IBuildInstallerSharedContextPtr SharedContext;` — The context for allocating shared resources.
- L287 _public member_ `FString InstallDirectory;` — The directory to install to.
- L289 _public member_ `FString StagingDirectory;` — The directory for storing the intermediate files. This would usually be inside the InstallDirectory. Empty string will use module's global setting.
- L291 _public member_ `FString BackupDirectory;` — The directory for placing files that are believed to have local changes, before we overwrite them. Empty string will use module's global setting. If both empty, the feature disables.
- L293 _public member_ `TArray<FString> ChunkDatabaseFiles;` — The list of chunk database filenames that will be used to pull patch data from. These must be local (i.e. no URLs)
- L295 _public member_ `bool bDeleteChunkDbFilesAfterUse = false;` — If set, when we've read everything we're going to read from a chunkdb file, we delete it to minimize required disk space for install/patch.
- L298 _public member_ `bool bTruncateChunkDbFilesAsUsed = false;` — If set, as we use chunks from a chunkdb file, we reduce it's size on disk to minimize required disk space for install/patch. This is only effective if the ChunkDB files are produced with reverse chunk ordering.
- L302 _public member_ `bool bCalculateDeleteChunkDbMaxDiskSpaceAndExit = false;` — If set, don't actually do an installation, just figure out how much disk space is required if we are using entirely chunkdbs and we delete them as we go.
- L306 _public member_ `TArray<FString> CloudDirectories;` — The list of cloud directory roots that will be used to pull patch data from. Empty array will use module's global setting. This is only hit if a chunk can not be satisfied by other sources (i.e. chunkdbs or install directory for patches). If the chunk can not be serviced from here, it's a failure.
- L309 _public member_ `TMap<FGuid, TArray<uint8>> EncryptionSecrets;` — Map of available encryption secrets.
- L312 _public member_ `EInstallMode InstallMode = EInstallMode::NonDestructiveInstall;` — The mode for installation.
- L314 _public member_ `EVerifyMode VerifyMode = EVerifyMode::ShaVerifyAllFiles;` — The mode for verification. This will be overridden for any files referenced by a repair action.
- L316 _public member_ `EDeltaPolicy DeltaPolicy = EDeltaPolicy::Skip;` — The policy to follow for requesting an optimised delta.
- L318 _public member_ `FString DeltaFilenameTrailer;` — Optional specification for non-standard optimized delta
- L320 _public member_ `bool bRunRequiredPrereqs = true;` — Whether to run the prerequisite installer provided if it hasn't been ran before on this machine.
- L322 _public member_ `bool bSkipPrereqIfAlreadyRan = true;` — Whether to skip the prerequisite installer provided if it already ran.
- L324 _public member_ `bool bAllowConcurrentExecution = false;` — Whether to allow this installation to run concurrently with any existing installations.
- L326 _public member_ `uint64 DownloadRateLimitBps = 0;` — Download rate limit in bytes per second. (0 means unlimited)
- L328 _public member_ `bool bStageWithRawFilenames = false;` — Use raw filenames for staging files
- L330 _public member_ `bool bRejectSymlinks = false;` — If true, fail the installation if the manifest contains a symlink.
- L332 _public member_ `bool bSkipCustomUninstallAction = false;` — Whether to run the custom uninstall action or not
- L334 _public member_ `bool bTrackFileOperations = false;` — Whether to gather individual file operation statistics during install
- L338 _public member_ `TOptional<bool> ConstructorSpawnAdditionalIOThreads;` — Whether the file constructor is allowed to spawn multiple threads for IO read/write servicing. Unset uses Engine.ini value [Portal.BuildPatch]ConstructorSpawnAdditionalIOThreads if present, FFileConstructorConfig::bDefaultSpawnAdditionalIOThreads otherwise.
- L341 _public member_ `TOptional<int32> ConstructorIOBatchSizeMB;` — File constructor batch size, in MB. File will attempt to fill/write this chunk size to disk. Unset uses Engine.ini value [Portal.BuildPatch]ConstructorIOBatchSizeMB if present, FFileConstructorConfig::DefaultIOBatchSizeMB otherwise.
- L348 _public member_ `TOptional<int32> ConstructorIOBufferSizeMB;` — File constructor buffer size, in MB. This affects constructor performance heavily and must be at least big enough to fit a batch. For purely disk->disk installs, this can be relatively small - even 2x batch size will facilitate multiple GB/s installations. However for cloud/download installs this needs to be fairly large to mitigate the effect of out of order download completion. When bConstructFilesInMemory or bInstallToMemory is set, this is used to determine how many active files can be in flight. Unset uses Engine.ini value [Portal.BuildPatch]ConstructorIOBufferSizeMB if present, FFileConstructorConfig::DefaultIOBufferSizeMB otherwise.
- L354 _public member_ `TOptional<bool> ConstructorStallWhenFileSystemThrottled;` — Whether the file construction should adhere to file system write limits. If a write limit is hit, writing will stall until sufficient quota exists for the write. Inheritance for this property is: CVar BuildPatchFileConstructor.bStallWhenFileSystemThrottled, which defaults to true. if set, this member.
- L360 _public member_ `TOptional<int32> ConstructorDisableResumeBelowMB;` — Whether to disable resume on clean installs below a given threshold, in megabytes. 0 means "never disable". Inheritance: CVar BuildPatchFileConstructor.DisableResumeBelowMB, which defaults to 0. if set, this member
- L370 _public member_ `bool bConstructFilesInMemory = false;` — If set, files will be built entirely in memory - requiring at least the largest file's size worth of memory. IO batch and buffer sizes are ignored as operations operate directly on the output memory buffer. If allowing multiple files in flight, this causes the size of the entire installation to be allocated as there's no IO buffer size limiting the number of in flight requests. Once the file completes construction it is written to disk in the normal place defined by InstallMode. This occurs after the old file is deleted for Destructive installations in order to manage peak disk space usage. This mode does not support resuming mid-file.
- L374 _public member_ `bool bInstallToMemory = false;` — As bConstructFilesInMemory, except the file is never written to disk and is instead made available after via GetFilesInstalledToMemory
- L377 _public member_ `bool bSkipInitialDiskSizeCheck = false;` — If set, no initial size check will be performed prior to starting the installation. Running out of disk space during installation is unchanged.

#### struct `BuildPatchServices::FDirectoryChunkerConfiguration`  
`struct FDirectoryChunkerConfiguration`  
_L383-453_
- desc: Defines a list of all options for the build chunking task.
- L387 _public member_ `EFeatureLevel FeatureLevel = EFeatureLevel::Latest;` — The client feature level to output data for.
- L389 _public member_ `FString RootDirectory;` — The directory to analyze.
- L391 _public member_ `uint32 AppId = 0;` — The ID of the app of this build.
- L393 _public member_ `FString AppName;` — The name of the app of this build.
- L395 _public member_ `FString BuildVersion;` — The version string for this build.
- L397 _public member_ `FString LaunchExe;` — The local exe path that would launch this build.
- L399 _public member_ `FString LaunchCommand;` — The command line that would launch this build.
- L401 _public member_ `FString InputListFile;` — The path to a file containing a \r\n separated list of RootDirectory relative files to read.
- L403 _public member_ `FString IgnoreListFile;` — The path to a file containing a \r\n separated list of RootDirectory relative files to ignore.
- L405 _public member_ `FString AttributeListFile;` — The path to a file containing a \r\n separated list of RootDirectory relative files followed by attribute keywords.
- L407 _public member_ `EFileSortOrder FileSortOrder = EFileSortOrder::AlphabeticalTagThenFilename;` — The order in which to stream the build files.
- L409 _public member_ `TSet<FString> PrereqIds;` — The set of identifiers which the prerequisites satisfy.
- L411 _public member_ `FString PrereqName;` — The display name of the prerequisites installer.
- L413 _public member_ `FString PrereqPath;` — The path to the prerequisites installer.
- L415 _public member_ `FString PrereqArgs;` — The command line arguments for the prerequisites installer.
- L417 _public member_ `FString UninstallActionPath;` — The path to the uninstall custom action executable.
- L419 _public member_ `FString UninstallActionArgs;` — The command line arguments for the uninstall custom action executable.
- L421 _public member_ `float DataAgeThreshold = TNumericLimits<float>::Max();` — The maximum age (in days) of existing data files which can be reused in this build.
- L424 _public member_ `bool bShouldHonorReuseThreshold = false;` — Indicates whether data age threshold should be honored. If false, ALL data files can be reused taking into account the ReuseManifestPredicate.
- L427 _public function_ `TFunction<bool(const IBuildManifest&)> ReuseManifestPredicate = [](const IBuildManifest&)` — A callable that takes a const reference to an IBuildManifest and returns true to reuse the manifest and its chunks, or false to fully ignore it.
- L427 _public member_ `TFunction<bool(const IBuildManifest&)> ReuseManifestPredicate = [](const IBuildManifest&) { return true; };` — A callable that takes a const reference to an IBuildManifest and returns true to reuse the manifest and its chunks, or false to fully ignore it.
- L429 _public member_ `uint32 OutputChunkWindowSize = 1024 * 1024;` — The chunk window size to be used when saving out new data.
- L431 _public member_ `bool bShouldMatchAnyWindowSize = true;` — Indicates whether any window size chunks should be matched, rather than just out output window size.
- L433 _public member_ `bool bResaveExistingChunks = false;` — Indicates that if a chunk was already found in the cloud directory, to resave it anyway.
- L435 _public member_ `bool bResaveKnownChunks = false;` — Indicates that if a chunk was matched from a previous build, to resave it anyway.
- L437 _public member_ `TArray<uint8> EncryptionSecretKey;` — The encryption secret key to use for newly created chunk files, and the manifest itself.
- L439 _public member_ `FGuid EncryptionSecretId;` — An ID that identifies the secret key above, used to know which secrets are required for each manifest & chunk.
- L441 _public member_ `TMap<FString, FVariant> CustomFields;` — Map of custom fields to add to the manifest.
- L443 _public member_ `FString CloudDirectory;` — The cloud directory that all patch data will be saved to. An empty value will use module's global setting.
- L445 _public member_ `FString OutputFilename;` — The output manifest filename.
- L447 _public member_ `bool bAllowEmptyBuild = false;` — Allow Manifest Creation for builds with no data
- L450 _public member_ `bool bFollowSymlinks = false;` — Whether to follow symlinks, or if false, replicate them. True would process the build as if all links were actual files and directories. Note that this currently only affects mac and linux systems.
- L452 _public member_ `bool bSHA1Only = false;` — SHA256 and MD5 are expensive and can slow down the chunking process, set this true to skip calculation and save as zeroed values.

#### enum `BuildPatchServices::EDiffAbortThresholdUnits`  
`enum class EDiffAbortThresholdUnits : uint8`  
_L462-466_
- desc: An enum defining the units of DiffAbortThreshold value.
- L464 _public enumerator_ `Absolute = 0`
- L465 _public enumerator_ `Percentage`

#### struct `BuildPatchServices::FDiffAbortThreshold`  
`struct FDiffAbortThreshold`  
_L471-480_
- desc: Defines the threshold for the original delta size, for which we would abort and not process.
- L476 _public member_ `uint64 Value = 0ULL;` — A threshold for the original delta size, for which we would abort and not process.
- L479 _public member_ `EDiffAbortThresholdUnits Unit = EDiffAbortThresholdUnits::Absolute;` — A units of measurement for Value field.

#### struct `BuildPatchServices::FChunkDeltaOptimiserConfiguration`  
`struct FChunkDeltaOptimiserConfiguration`  
_L497-544_
- desc: Defines a list of all options for the chunk delta optimisation task.
- L503 _public prototype_ `FChunkDeltaOptimiserConfiguration();` — Default constructor
- L507 _public member_ `FString ManifestAUri;` — A full file or http path for the manifest to be used as the source build.
- L509 _public member_ `FString ManifestBUri;` — A full file or http path for the manifest to be used as the destination build.
- L511 _public member_ `FString OutputCloudDirectory;` — The cloud directory that all patch data will be saved to. An empty value will use ManifestB's directory.
- L513 _public member_ `TArray<FString> DownloadCloudDirectories;` — The cloud directories that existing patch data can be downloaded from. An empty array will use ManifestB's directory.
- L515 _public member_ `uint32 ScanWindowSize;` — The window size to use for find new matches.
- L517 _public member_ `uint32 OutputChunkSize;` — The chunk size to use for saving new diff data.
- L519 _public member_ `bool bResaveExistingChunks;` — Indicates that if a chunk was already found in the cloud directory, to resave it anyway.
- L521 _public member_ `TOptional<FDiffAbortThreshold> DiffAbortThreshold;` — A threshold for the original delta size, for which we would abort and not process.
- L523 _public member_ `TMap<FGuid, TArray<uint8>> EncryptionSecrets;` — Map of available encryption secrets, if any are missing, the process will fail.
- L525 _public member_ `TArray<FMessageHandler*> MessageHandlersA;` — Array of message handlers to provide signed URLs for source build chunks downloads.
- L527 _public member_ `TArray<FMessageHandler*> MessageHandlersB;` — Array of message handlers to provide signed URLs for destination build chunks and delta file downloads.
- L533 _public member_ `TMap<FString, FString> ManifestATagAliases;` — The old and new build aliases. Tags in the old and new build will be wholesale replaced by any aliases in these maps, allowing for control over what data is available for the patching system to match from. By default matches are only allowed from the same tag, with this one can virtually replace a set of tags with the same tag, allowing the patcher to select matches from all of the aliased tags.
- L534 _public member_ `TMap<FString, FString> ManifestBTagAliases;`
- L535 _public member_ `TSet<FString> ManifestAIgnoreTags;`
- L536 _public member_ `TSet<FString> ManifestBIgnoreTags;`
- L540 _public member_ `FString DeltaFilenameTrailer;` — The custom optimized delta filename to use for generating this optimized delta. If used, all BPS modes that request an optimized delta will need the same trailer passed in.
- L543 _public member_ `FString SourceDetailsLogFilename;` — If specified, the source information for where each chunk matches from will be output to this file.

#### struct `BuildPatchServices::FPatchDataEnumerationConfiguration`  
`struct FPatchDataEnumerationConfiguration`  
_L549-564_
- desc: Defines a list of all options for the patch data enumeration task.
- L555 _public prototype_ `FPatchDataEnumerationConfiguration();` — Default constructor
- L559 _public member_ `FString InputFile;` — A full file path for the manifest or chunkdb to enumerate referenced data for.
- L561 _public member_ `FString OutputFile;` — A full file path to a file where the list will be saved out to.
- L563 _public member_ `bool bIncludeSizes;` — Whether to include files sizes.

#### struct `BuildPatchServices::FDiffManifestsConfiguration`  
`struct FDiffManifestsConfiguration`  
_L569-609_
- desc: Defines a list of all options for the diff manifests task.
- L573 _public member_ `FString ManifestAUri;` — A full file or http path for the manifest to be used as the source build.
- L575 _public member_ `FString ManifestBUri;` — A full file or http path for the manifest to be used as the destination build.
- L577 _public member_ `TArray<FString> CloudDirs;` — List of directories or http paths that can be used to request patch data. If empty, then path to ManifestA will be used.
- L579 _public member_ `TSet<FString> TagSetA;` — The tag set to use to filter desired files from ManifestA.
- L581 _public member_ `TSet<FString> TagSetB;` — The tag set to use to filter desired files from ManifestB.
- L584 _public member_ `TArray<TSet<FString>> CompareTagSetsA;` — Tag sets that will be used to calculate additional differential size statistics between manifests. They must all be a subset of anything used in TagSetA.
- L587 _public member_ `TArray<TSet<FString>> CompareTagSetsB;` — If set, the tagset comparison will use these as the new tags and CompareTagSets will be the old installed tags, to allow for comparing the diff when the installed set of tags changes.
- L589 _public member_ `FString OutputFilePath;` — A full file path where a JSON object will be saved for the diff details.Empty string if not desired.
- L591 _public member_ `TArray<FMessageHandler*> MessageHandlers;` — Array of message handlers to provide signed URIs for delta file.
- L595 _public member_ `FString OutputPatchDescriptorPath;` — A destination base directory to use for writing out patch description files for the patch between the two manifest.
- L599 _public member_ `bool bRequireOptimizedDelta = false;` — By default, DiffManifest will use TryFetchContinueWithout and will, as a result, show large patches. If your workflows are such that you always expect an optimized delta, set this to cause DiffManifest to fail instead of show irrelevant data.
- L602 _public member_ `bool bOnlyPatchDescriptors = false;` — If true, only emit patch descriptors and not the entirety of the diff manifests output.
- L605 _public member_ `bool bSimulateInstallTimes = false;` — If true, emit simulated installation time estimations
- L608 _public member_ `FString DeltaFilenameTrailer;` — The custom optimized delta filename to use, if desired.

#### struct `BuildPatchServices::FCompactifyConfiguration`  
`struct FCompactifyConfiguration`  
_L614-631_
- desc: Defines a list of all options for the cloud directory compactifier task.
- L620 _public prototype_ `FCompactifyConfiguration();` — Default constructor
- L624 _public member_ `FString CloudDirectory;` — The path to the directory to compactify.
- L626 _public member_ `float DataAgeThreshold;` — Chunks which are not referenced by a valid manifest, and which are older than this age(in days), will be deleted.
- L628 _public member_ `FString DeletedChunkLogFile;` — The full path to a file to which a list of all chunk files deleted by compactify will be written.The output filenames will be relative to the cloud directory.
- L630 _public member_ `bool bRunPreview;` — If ran in preview mode, then the process will run in logging mode only - no files will be deleted.

#### struct `BuildPatchServices::FPackageChunksConfiguration`  
`struct FPackageChunksConfiguration`  
_L636-670_
- desc: Defines a list of all options for the chunk packaging task.
- L642 _public prototype_ `FPackageChunksConfiguration();` — Default constructor
- L646 _public member_ `EFeatureLevel FeatureLevel;` — The client feature level to output data for.
- L648 _public member_ `FString ManifestFilePath;` — A full file path to the manifest to enumerate chunks from.
- L650 _public member_ `FString PrevManifestFilePath;` — A full file path to a manifest describing a previous build, which will filter out saved chunks for patch only chunkdbs.
- L652 _public member_ `TArray<TSet<FString>> TagSetArray;` — Optional list of tagsets to split chunkdb files on. Empty array will include all data as normal.
- L654 _public member_ `TSet<FString> PrevTagSet;` — Optional tagset to filter the files used from PrevManifestFilePath, potentially increasing the number of chunks saved.
- L656 _public member_ `FString OutputFile;` — A full file path to the chunkdb file to save. Extension of .chunkdb will be added if not present.
- L658 _public member_ `FString CloudDir;` — Cloud directory where chunks to be packaged can be found.
- L660 _public member_ `uint64 MaxOutputFileSize;` — The maximum desired size for each chunkdb file.
- L662 _public member_ `FString ResultDataFilePath;` — A full file path to use when saving the json output data.
- L664 _public member_ `bool bIgnoreManifestFileInvalidTags;` — Optional flag for ignoring manifest file invalid tags
- L666 _public member_ `bool bIgnorePrevManifestFileInvalidTags;` — Optional flag for ignoring manifest describing a previous build file invalid tags
- L669 _public member_ `FString DeltaFilenameTrailer;` — Optional specification for non-standard optimized delta

#### struct `BuildPatchServices::FChunkHarvesterConfiguration`  
`struct FChunkHarvesterConfiguration`  
_L675-694_
- desc: Defines a list of all options for the chunk harvesting task.
- L681 _public prototype_ `FChunkHarvesterConfiguration();` — Default constructor
- L685 _public member_ `EFeatureLevel FeatureLevelOverride;` — Set an override feature level to output newer format.
- L687 _public member_ `FString ManifestFilePath;` — A full file path to the manifest to enumerate chunks from.
- L689 _public member_ `FString BuildRoot;` — The directory containing the binary image to be read.
- L691 _public member_ `FString CloudDir;` — The directory where existing data will be recognized from, and new data added to.
- L693 _public member_ `bool bResaveExistingChunks;` — Indicates that if a chunk was already found in the cloud directory, to resave it anyway.

#### Free symbols / members of external scopes

- L25 _namespace_ `namespace BuildPatchServices`
- L30 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FChunkBuildBooleanDelegate);` — A delegate returning a bool.
- L30 _prototype_ `DECLARE_DELEGATE_RetVal(bool, FChunkBuildBooleanDelegate);` (scope `BuildPatchServices`) — A delegate returning a bool.
- L31 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FChunkBuildFilesEnumeratedDelegate, const TArray<FString>& );`
- L31 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FChunkBuildFilesEnumeratedDelegate, const TArray<FString>& );` (scope `BuildPatchServices`)
- L456 _typedef_ `typedef FDirectoryChunkerConfiguration FGenerationConfiguration;` (scope `BuildPatchServices`) — Temporary for use with deprecated module functions.
- L457 _typedef_ `typedef FDirectoryChunkerConfiguration FChunkBuildConfiguration;` (scope `BuildPatchServices`)
- L485 _namespace_ `namespace DiffAbortThresholdLimits` (scope `BuildPatchServices`)
- L488 _variable_ `constexpr uint64 MinPercentage = 1ULL;` (scope `BuildPatchServices::DiffAbortThresholdLimits`) — Minimum threshold value limit, expressed as a percentage
- L491 _variable_ `constexpr uint64 MinAbsolute = 1000ULL * 1000ULL * 1000ULL;` (scope `BuildPatchServices::DiffAbortThresholdLimits`) — Minimum threshold value limit, expressed in absolute units.
- L699 _function_ `inline const TCHAR* LexToString(BuildPatchServices::EFileSortOrder FileSortOrder)`
- L701 _macro_ `#define CASE_ENUM_TO_STR(Value) case BuildPatchServices::EFileSortOrder::Value: return TEXT(#Value)`
- L711 _function_ `inline void LexFromString(BuildPatchServices::EFileSortOrder& FileSortOrder, const TCHAR* Buffer)`
- L713 _macro_ `#define RETURN_IF_EQUAL(Value) if (FCString::Stricmp(Buffer, TEXT(#Value)) == 0) { FileSortOrder = BuildPatchServices::EFileSortOrder::Value; return; }`
- L726 _function_ `inline FString LexToString(const TOptional<BuildPatchServices::FDiffAbortThreshold>& DiffAbortThreshold)`
- L748 _function_ `inline FString LexToString(BuildPatchServices::EDiffAbortThresholdUnits Unit)`
- L750 _macro_ `#define CASE_ENUM_TO_STR(Value) case BuildPatchServices::EDiffAbortThresholdUnits::Value: return TEXT(#Value)`

### `Source/Runtime/Online/BuildPatchServices/Public/BuildPatchState.h` (Public)


#### enum `BuildPatchServices::EBuildPatchState`  
`enum class EBuildPatchState : uint32`  
_L15-58_
- desc: Namespace to declares the progress type enum
- L18 _public enumerator_ `Queued = 0` — The patch process is waiting for other installs
- L21 _public enumerator_ `Initializing` — The patch process is initializing
- L24 _public enumerator_ `Resuming` — The patch process is enumerating existing staged data
- L27 _public enumerator_ `Downloading` — The patch process is downloading patch data
- L30 _public enumerator_ `Installing` — The patch process is installing files
- L33 _public enumerator_ `RunningCustomUninstallAction` — The patch process is running custom uninstall action
- L36 _public enumerator_ `MovingToInstall` — The patch process is moving staged files to the install
- L39 _public enumerator_ `SettingAttributes` — The patch process is setting up attributes on the build
- L42 _public enumerator_ `BuildVerification` — The patch process is verifying the build
- L45 _public enumerator_ `CleanUp` — The patch process is cleaning temp files
- L48 _public enumerator_ `PrerequisitesInstall` — The patch process is installing prerequisites
- L51 _public enumerator_ `Completed` — A state to catch the UI when progress is 100% but UI still being displayed
- L54 _public enumerator_ `Paused` — The process has been set paused
- L57 _public enumerator_ `NUM_PROGRESS_STATES` — Holds the number of states, for array sizes

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace BuildPatchServices`
- L66 _prototype_ `const FText& StateToText(const EBuildPatchState& State);` (scope `BuildPatchServices`) — `UE_DEPRECATED(4.21, "BuildPatchServices::StateToText(const EBuildPatchState& State) has been deprecated. It will no longer be supported by BuildPatchServices in the future.")` — Returns the FText representation of the specified EBuildPatchState value. Used for displaying to the user. @param State - The error type value. @return The display text associated with the progress step.
- L71 _function_ `inline const TCHAR* LexToString(BuildPatchServices::EBuildPatchState State)`
- L73 _macro_ `#define CASE_ENUM_TO_STR(Value) case BuildPatchServices::EBuildPatchState::Value: return TEXT(#Value)`
- L94 _function_ `inline void LexFromString(BuildPatchServices::EBuildPatchState& Error, const TCHAR* Buffer)`
- L96 _macro_ `#define RETURN_IF_EQUAL(Value) if (FCString::Stricmp(Buffer, TEXT(#Value)) == 0) { Error = BuildPatchServices::EBuildPatchState::Value; return; }`

### `Source/Runtime/Online/BuildPatchServices/Public/BuildPatchVerify.h` (Public)


#### enum `BuildPatchServices::EVerifyMode`  
`enum class EVerifyMode : uint32`  
_L12-27_
- desc: An enum defining the verification mode that should be used.
- L15 _public enumerator_ `ShaVerifyAllFiles = 0` — Fully SHA checks all files in the build.
- L18 _public enumerator_ `ShaVerifyTouchedFiles` — Fully SHA checks only files touched by the install/patch process.
- L21 _public enumerator_ `FileSizeCheckAllFiles` — Checks just the existence and file size of all files in the build.
- L24 _public enumerator_ `FileSizeCheckTouchedFiles` — Checks just the existence and file size of only files touched by the install/patch process.
- L26 _public enumerator_ `InvalidOrMax`

#### enum `BuildPatchServices::EVerifyError`  
`enum class EVerifyError : uint32`  
_L32-47_
- desc: An enum defining the possible causes for a verification failure.
- L35 _public enumerator_ `FileMissing = 0` — The file was not found.
- L38 _public enumerator_ `OpenFileFailed` — The file failed to open.
- L41 _public enumerator_ `HashCheckFailed` — The file failed its hash check.
- L44 _public enumerator_ `FileSizeFailed` — The file was not the expected size.
- L46 _public enumerator_ `InvalidOrMax`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace BuildPatchServices`
- L50 _prototype_ `ENUM_RANGE_BY_FIRST_AND_LAST(BuildPatchServices::EVerifyError, BuildPatchServices::EVerifyError::FileMissing, BuildPatchServices::EVerifyError::FileSizeFailed) static_assert((uint32)BuildPatchServices::EVerifyMode::InvalidOrMax == 4, "Ple`
- L54 _function_ `inline const TCHAR* LexToString(BuildPatchServices::EVerifyMode VerifyMode)`
- L56 _macro_ `#define CASE_ENUM_TO_STR(Value) case BuildPatchServices::EVerifyMode::Value: return TEXT(#Value)`
- L68 _function_ `inline void LexFromString(BuildPatchServices::EVerifyMode& VerifyMode, const TCHAR* Buffer)`
- L70 _macro_ `#define RETURN_IF_EQUAL(Value) if (FCString::Stricmp(Buffer, TEXT(#Value)) == 0) { VerifyMode = BuildPatchServices::EVerifyMode::Value; return; }`
- L88 _function_ `inline const TCHAR* LexToString(BuildPatchServices::EVerifyError VerifyError)`
- L90 _macro_ `#define CASE_ENUM_TO_STR(Value) case BuildPatchServices::EVerifyError::Value: return TEXT(#Value)`
- L102 _function_ `inline void LexFromString(BuildPatchServices::EVerifyError& VerifyError, const TCHAR* Buffer)`
- L104 _macro_ `#define RETURN_IF_EQUAL(Value) if (FCString::Stricmp(Buffer, TEXT(#Value)) == 0) { VerifyError = BuildPatchServices::EVerifyError::Value; return; }`

### `Source/Runtime/Online/BuildPatchServices/Public/Interfaces/IBuildInstaller.h` (Public)


#### enum `EBuildPatchInstallError`  
`enum class EBuildPatchInstallError`  
_L22-67_
- desc: Declares the error type enum for use with the error system
- L25 _public enumerator_ `NoError = 0` — There has been no registered error
- L28 _public enumerator_ `DownloadError = 1` — A download request failed and ran out of allowed retries
- L31 _public enumerator_ `FileConstructionFail = 2` — A file failed to construct properly
- L34 _public enumerator_ `MoveFileToInstall = 3` — An error occurred trying to move the file to the install location
- L37 _public enumerator_ `BuildVerifyFail = 4` — The installed build failed to verify
- L40 _public enumerator_ `ApplicationClosing = 5` — The user or some process has closed the application
- L43 _public enumerator_ `ApplicationError = 6` — An application error, such as module fail to load.
- L46 _public enumerator_ `UserCanceled = 7` — User canceled download
- L49 _public enumerator_ `PrerequisiteError = 8` — A prerequisites installer failed
- L52 _public enumerator_ `InitializationError = 9` — An initialization error
- L55 _public enumerator_ `PathLengthExceeded = 10` — An error occurred creating a file due to excessive path length
- L58 _public enumerator_ `OutOfDiskSpace = 11` — An error occurred creating a file due to their not being enough space left on the disk
- L61 _public enumerator_ `CustomUninstallActionError = 12` — The custom uninstall action failed
- L64 _public enumerator_ `InvalidOrMax` — Used to help verify logic
- L66 _public enumerator_ `NumInstallErrors = InvalidOrMax` — Deprecated value. Use InvalidOrMax instad of NumInstallErrors

#### enum `EBuildPatchDownloadHealth`  
`enum class EBuildPatchDownloadHealth`  
_L93-108_
- desc: Enum describing download health. The actual percentage values used are configurable in the engine ini.
- L96 _public enumerator_ `Disconnected = 0` — All requests are in the retrying state. No progress currently. Possibly disconnected.
- L98 _public enumerator_ `Poor` — More than 10% of requests are failing.
- L100 _public enumerator_ `OK` — 10% or fewer requests are failing.
- L102 _public enumerator_ `Good` — 1% or fewer requests are failing.
- L104 _public enumerator_ `Excellent` — No requests are failing.
- L107 _public enumerator_ `NUM_Values` — Must be last value, only used for value counts.

#### struct `FCloudDirectoryStats`  
`struct FCloudDirectoryStats`  
_L113-123_
- desc: Tracks install stats for a given cloud directory.
- L116 _public member_ `FString CloudDirectory;` — The identifier for this cloud directory, e.g. base URL.
- L119 _public member_ `uint64 TotalReceivedData = 0;` — Total number of bytes downloaded from this cloud directory.
- L122 _public member_ `uint32 ErrorCount = 0;` — Total number of errors encountered from this cloud directory.

#### struct `FInstallActionStats`  
`struct FInstallActionStats`  
_L128-136_
- desc: A struct to hold stats for a single install action.
- L131 _public member_ `bool UsedOptimizedDelta = false;`
- L132 _public member_ `uint64 OptimizedDeltaHTTPResponseCode = 0;`
- L133 _public member_ `uint64 NumLocalChunksExpected = 0;`
- L134 _public member_ `uint64 NumLocalChunksAvailable = 0;`
- L135 _public member_ `uint64 NumChunksRecycleFailures = 0;`

#### struct `FBuildInstallStats`  
`struct FBuildInstallStats`  
_L141-345_
- desc: A struct to hold stats for the build process.
- L144 _public function_ `FBuildInstallStats() : NumFilesInBuild(0) , NumFilesOutdated(0) , NumFilesToRemove(0) , NumChunksRequired(0) , ChunksQueuedForDownload(0) , ChunksLocallyAvailable(0) , ChunksInChunkDbs(0) , NumChunksDownloaded(0) , NumChunksRecycled(0) , NumChunksReadFromChunkDbs(0) , NumFailedDownloads(0) , NumBadDownloads(0) , NumAbortedDownloads(0) , NumRecycleFailures(0) , NumDriveStoreChunkLoads(0) , NumDriveStoreLoadFailures(0) , NumChunkDbChunksFailed(0) , TotalDownloadedData(0) , ActiveRequestCountPeak(0) , AverageDownloadSpeed(0.0) , PeakDownloadSpeed(0.0) , FinalDownloadSpeed(-1.0) , TheoreticalDownloadTime(0.0f) , TotalReadData(0) , AverageDiskReadSpeed(0.0) , PeakDiskReadSpeed(0.0) , TotalWrittenData(0) , AverageDiskWriteSpeed(0.0) , PeakDiskWriteSpeed(0.0) , NumFilesConstructed(0) , InitializeTime(0.0f) , ConstructTime(0.0f) , UninstallActionTime(0.0f) , MoveFromStageTime(0.0f) , FileAttributesTime(0.0f) , VerifyTime(0.0f) , CleanUpTime(0.0f) , PrereqTime(0.0f) , ProcessPausedTime(0.0f)` — Constructor
- L207 _public member_ `uint32 NumFilesInBuild;` — The total number of files in the build.
- L209 _public member_ `uint32 NumFilesOutdated;` — The total number of files outdated.
- L211 _public member_ `uint32 NumFilesToRemove;` — The total number of files in the previous build that can be deleted.
- L213 _public member_ `uint32 NumChunksRequired;` — The total number of chunks making up those files.
- L215 _public member_ `uint32 ChunksQueuedForDownload;` — The number of required chunks queued for download.
- L217 _public member_ `uint32 ChunksLocallyAvailable;` — The number of chunks locally available in the build.
- L219 _public member_ `uint32 ChunksInChunkDbs;` — The number of chunks available in chunkdb files.
- L221 _public member_ `uint32 NumChunksDownloaded;` — The total number of chunks that were downloaded.
- L223 _public member_ `uint32 NumChunksRecycled;` — The number of chunks successfully recycled.
- L225 _public member_ `uint32 NumChunksReadFromChunkDbs;` — The number of chunks successfully read from chunkdbs.
- L227 _public member_ `uint32 NumFailedDownloads;` — The number of chunks we did not successfully receive.
- L229 _public member_ `uint32 NumBadDownloads;` — The number of chunks we received but were determined bad data.
- L231 _public member_ `uint32 NumAbortedDownloads;` — The number of chunks we aborted as they were determined as taking too long.
- L233 _public member_ `uint32 NumRecycleFailures;` — The number of chunks that failed to be recycled from existing build.
- L235 _public member_ `uint32 NumDriveStoreChunkLoads;` — The number of chunks that had to be loaded from the drive store.
- L237 _public member_ `uint32 NumDriveStoreLoadFailures;` — The number of chunks that failed to load from the drive store.
- L239 _public member_ `uint32 DriveStorePeakBytes = 0;` — The max disk space used by the drive store
- L241 _public member_ `uint32 NumDriveStoreLostChunks = 0;` — The number of chunks that were lost due to drive space limits
- L243 _public member_ `uint32 NumChunkDbChunksFailed;` — The number of chunks that were not successfully loaded from provided chunkdbs.
- L245 _public member_ `uint64 TotalDownloadedData;` — The total number of bytes downloaded.
- L247 _public member_ `uint32 ActiveRequestCountPeak;` — The peak number of simultaneous download requests
- L249 _public member_ `uint32 ActiveRequestCountAvg;` — The average number of simultaneous download requests
- L251 _public member_ `FString ExperimentName;` — The Experiment name if applicable for A/B Testing
- L253 _public member_ `FString ExerimentVariantName;` — The Variant of the Experiment if applicable for A/B Testing
- L255 _public member_ `double AverageDownloadSpeed;` — The average chunk download speed.
- L257 _public member_ `double PeakDownloadSpeed;` — The peak chunk download speed.
- L259 _public member_ `double FinalDownloadSpeed;` — The download speed registered at the end of the installation.
- L261 _public member_ `float TheoreticalDownloadTime;` — The theoretical download time (data/speed).
- L263 _public member_ `uint64 TotalReadData;` — The total number of bytes read to disk.
- L265 _public member_ `double AverageDiskReadSpeed;` — The average disk read speed.
- L267 _public member_ `double PeakDiskReadSpeed;` — The peak disk read speed.
- L269 _public member_ `uint64 TotalWrittenData;` — The total number of bytes written to disk.
- L271 _public member_ `double AverageDiskWriteSpeed;` — The average disk write speed.
- L273 _public member_ `double PeakDiskWriteSpeed;` — The peak disk write speed.
- L275 _public member_ `uint32 NumFilesConstructed;` — The total number of files constructed.
- L279 _public member_ `uint64 MaxDiskSpaceNeededWhenDeletingChunkDbsIfRequested = 0;` — We don't actually do any installation when requesting this value, we just start up an installer, compute it, then bail. See bCalculateDeleteChunkDbMaxDiskSpaceAndExit in the installer configuration. Will be zero all other times.
- L282 _public member_ `float InitializeTime;` — The time spent during the initialization stage.
- L284 _public member_ `float ConstructTime;` — The time spent during the construction stage.
- L286 _public member_ `uint64 TotalDecryptTime;` — The time spent on chunks decryption.
- L288 _public member_ `float UninstallActionTime;` — The time spent during the custom uninstall actiion run.
- L290 _public member_ `float MoveFromStageTime;` — The time spent moving staged files into the installation location.
- L292 _public member_ `float FileAttributesTime;` — The time spent during the file attribution stage.
- L294 _public member_ `float VerifyTime;` — The time spent during the verification stage.
- L296 _public member_ `float CleanUpTime;` — The time spent during the clean up stage.
- L298 _public member_ `float PrereqTime;` — The time spent during the prerequisite stage.
- L300 _public member_ `float ProcessPausedTime;` — The amount of time that was spent paused.
- L302 _public member_ `float ProcessActiveTime;` — The amount of time that was spent active (un-paused).
- L304 _public member_ `float ProcessExecuteTime;` — The total time that the install process took to complete.
- L306 _public member_ `bool ProcessSuccess;` — Whether the process was successful.
- L308 _public member_ `uint32 NumInstallRetries;` — The number of times the system looped to retry.
- L310 _public member_ `EBuildPatchInstallError FailureType;` — The failure type for the install.
- L312 _public member_ `TArray<EBuildPatchInstallError> RetryFailureTypes;` — If NumInstallRetries > 0, this will contain the list of retry reasons for retrying.
- L314 _public member_ `FString ErrorCode;` — The error code. No error results in 'OK'.
- L316 _public member_ `TArray<FString> RetryErrorCodes;` — If NumInstallRetries > 0, this will contain the list of error codes for each retry.
- L318 _public member_ `FText FailureReasonText;` — The localized, more generic failure reason.
- L320 _public member_ `float FinalProgress;` — Final progress state, this is the progress of the current retry attempt.
- L322 _public member_ `float OverallRequestSuccessRate;` — The overall rate of success for download requests.
- L324 _public member_ `float ExcellentDownloadHealthTime;` — The amount of time that was spent with Excellent download health.
- L326 _public member_ `float GoodDownloadHealthTime;` — The amount of time that was spent with Good download health.
- L328 _public member_ `float OkDownloadHealthTime;` — The amount of time that was spent with OK download health.
- L330 _public member_ `float PoorDownloadHealthTime;` — The amount of time that was spent with Poor download health.
- L332 _public member_ `float DisconnectedDownloadHealthTime;` — The amount of time that was spent with Disconnected download health.
- L334 _public member_ `uint64 MemoryStoreSizePeakBytes = 0;` — Max memory usage for the memory store.
- L336 _public member_ `uint64 MemoryStoreSizeLimitBytes = 0;` — Memory limit for the memory backing store
- L338 _public member_ `uint64 ProcessRequiredDiskSpace;` — The total number of bytes required to start the installation.
- L340 _public member_ `uint64 ProcessAvailableDiskSpace;` — The total number of bytes available at the time of checking ProcessRequiredDiskSpace.
- L342 _public member_ `TArray<FCloudDirectoryStats> CloudDirectoryStats;` — Stats tracked per cloud directory.
- L344 _public member_ `TArray<FInstallActionStats> ActionsStats;` — Stats tracked per action. Array order matches actions order in configuration.

#### class `IBuildInstaller`  
`class IBuildInstaller`  
_L355-564_
- desc: Interface to a Build Installer, exposes installation control, progress, and state information.
- L361 _public prototype_ `virtual ~IBuildInstaller() = default;` — Virtual destructor.
- L367 _public prototype_ `virtual bool StartInstallation() = 0;` — Begin the installation process. @return true if the installation started successfully, or is already running.
- L373 _public prototype_ `virtual bool IsComplete() const = 0;` — Get whether the install has complete @return	true if the thread completed
- L379 _public prototype_ `virtual bool IsCanceled() const = 0;` — Get whether the install was canceled. Only valid if complete. @return	true if installation was canceled
- L385 _public prototype_ `virtual bool IsPaused() const = 0;` — Get whether the install is currently paused. @return	true if installation is paused
- L391 _public prototype_ `virtual bool IsResumable() const = 0;` — Get whether the install can be resumed. @return	true if installation is resumable
- L397 _public prototype_ `virtual bool IsUpdate() const = 0;` — Get whether the install is performing an update of an existing install. @return	true if installation is an update
- L403 _public prototype_ `virtual bool IsRepair() const = 0;` — Get whether the install is performing a repair of an existing install. @return	true if installation is a repair
- L409 _public prototype_ `virtual bool IsVerifyOnly() const = 0;` — Get whether the install is performing a verify only of an existing install, without repair. @return	true if installation is a verify only.
- L415 _public prototype_ `virtual bool IsUninstall() const = 0;` — Get whether the install is actually uninstalling instead. @return	true if installation is actually an uninstallation
- L421 _public prototype_ `virtual bool CompletedSuccessfully() const = 0;` — Get whether the process was successfully complete, meaning no errors, and was not cancelled. Only valid if complete. @return	true if installation process completed successfully.
- L427 _public prototype_ `virtual bool HasError() const = 0;` — Get whether the install failed. Only valid if complete. @return	true if installation was a failure
- L433 _public prototype_ `virtual EBuildPatchInstallError GetErrorType() const = 0;` — Get the type of error for a failure that has occurred. @return	the enum representing the type of error
- L436 _public prototype_ `virtual FText GetPercentageText() const = 0;` — `UE_DEPRECATED(4.21, "GetPercentageText has been deprecated. It will no longer be supported in the future.")`
- L439 _public prototype_ `virtual FText GetDownloadSpeedText() const = 0;` — `UE_DEPRECATED(4.21, "GetDownloadSpeedText has been deprecated. It will no longer be supported in the future.")`
- L445 _public prototype_ `virtual double GetDownloadSpeed() const = 0;` — Get the download speed for the current process @return	download speed progress
- L448 _public function_ `virtual int64 GetInitialDownloadSize() const` — `UE_DEPRECATED(4.21, "GetInitialDownloadSize has been deprecated. Please use GetTotalDownloadRequired instead.")`
- L454 _public prototype_ `virtual int64 GetTotalDownloadRequired() const = 0;` — Get the total download bytes required to complete @return	the total required bytes
- L460 _public prototype_ `virtual int64 GetTotalDownloaded() const = 0;` — Get the total bytes downloaded @return	the total bytes downloaded
- L466 _public prototype_ `virtual BuildPatchServices::EBuildPatchState GetState() const = 0;` — Get the status of the install process. @return Status of the install process.
- L469 _public prototype_ `virtual FText GetStatusText() const = 0;` — `UE_DEPRECATED(4.21, "GetStatusText has been deprecated. It will no longer be supported in the future.")`
- L475 _public prototype_ `virtual float GetUpdateProgress() const = 0;` — Get the update progress @return	A float describing progress: Between 0 and 1 for known progress, or less than 0 for unknown progress.
- L481 _public prototype_ `virtual FBuildInstallStats GetBuildStatistics() const = 0;` — Get the build stats for the process. This should only be called after the install has completed @return	A struct containing information about the build
- L487 _public prototype_ `virtual EBuildPatchDownloadHealth GetDownloadHealth() const = 0;` — Get the current download health rating. @return	the enum representing the download health
- L493 _public prototype_ `virtual FText GetErrorText() const = 0;` — Get the display text for the error that occurred. Only valid to call after completion @return	display error text
- L500 _public prototype_ `virtual FString GetErrorCode() const = 0;` — Get the installation error code. This includes the failure type as well as specific code associated. The value is alphanumeric. This is only guaranteed to be set once the installation has completed. @returns the code as a string.
- L505 _public prototype_ `virtual void CancelInstall() = 0;` — Cancel the current install
- L511 _public prototype_ `virtual bool TogglePauseInstall() = 0;` — Toggle the install paused state @return true if the installer is now paused
- L517 _public prototype_ `virtual void RegisterMessageHandler(BuildPatchServices::FMessageHandler* MessageHandler) = 0;` — Registers a message handler with the installer. @param MessageHandler    Ptr to the message handler to add. Must not be null.
- L523 _public prototype_ `virtual void UnregisterMessageHandler(BuildPatchServices::FMessageHandler* MessageHandler) = 0;` — Unregisters a message handler, will no longer receive HandleMessage calls. @param MessageHandler    Ptr to the message handler to remove.
- L530 _public prototype_ `virtual const BuildPatchServices::FBuildInstallerConfiguration& GetConfiguration() const = 0;` — Get the installation configuration object @returns a const reference to the configuration
- L536 _public prototype_ `virtual void SetDownloadBytesPerSecondLimit(uint64 InDownloadRateLimitBps) = 0;` — Sets the download rate limit in Bytes per second. This throttles the download rate to the specified value. @param InDownloadRateLimitBps    throttle value in bytes per second.
- L542 _public prototype_ `virtual uint64 GetDownloadBytesPerSecondLimit() const = 0;` — Gets the download rate limit in Bytes per second. @return the current download rate limit.
- L547 _public function_ `virtual void GetDebugText(TArray<FString>& Output)` — Returns debug text for download screen to help troubleshoot download issues
- L555 _public prototype_ `virtual TMap<FString, TArray64<uint8>>& GetFilesInstalledToMemory() = 0;` — Get the completed files when installing to memory. This must not be called before installation completes, and is non-const so that clients can Move the memory as needed. Once installation is complete the installer does not touch this other than to delete it on destruction.
- L563 _public prototype_ `virtual void SetPerFileSubdirectories(TMap<FString, FString>&& InOldPerFileSubdirectories, TMap<FString, FString>&& InNewPerFileSubdirectories) = 0;` — [Experimental] Pass the installation folder on a per file basis. This path will be appended to the installation directory passed in the FBuildInstallerConfiguration::InstallDirectory member. The old version is used for patch source data, the new for everything else.

#### Free symbols / members of external scopes

- L15 _typedef_ `typedef TSharedPtr<IBuildInstaller, ESPMode::ThreadSafe> IBuildInstallerPtr;`
- L16 _typedef_ `typedef TSharedRef<IBuildInstaller, ESPMode::ThreadSafe> IBuildInstallerRef;`
- L17 _typedef_ `typedef TWeakPtr<IBuildInstaller, ESPMode::ThreadSafe> IBuildInstallerWeakPtr;`
- L72 _namespace_ `namespace InstallErrorPrefixes`
- L74 _variable_ `static const TCHAR* ErrorTypeStrings[] = { TEXT("OK"),` (scope `InstallErrorPrefixes`)
- L347 _namespace_ `namespace BuildPatchServices`
- L568 _function_ `inline const TCHAR* LexToString(EBuildPatchInstallError Error)`
- L570 _macro_ `#define CASE_ENUM_TO_STR(Value) case EBuildPatchInstallError::Value: return TEXT(#Value)`
- L591 _function_ `inline void LexFromString(EBuildPatchInstallError& Error, const TCHAR* Buffer)`
- L593 _macro_ `#define RETURN_IF_EQUAL(Value) if (FCString::Stricmp(Buffer, TEXT(#Value)) == 0) { Error = EBuildPatchInstallError::Value; return; }`
- L621 _function_ `inline const TCHAR* LexToString(EBuildPatchDownloadHealth Error)`
- L623 _macro_ `#define CASE_ENUM_TO_STR(Value) case EBuildPatchDownloadHealth::Value: return TEXT(#Value)`
- L636 _function_ `inline void LexFromString(EBuildPatchDownloadHealth& Error, const TCHAR* Buffer)`
- L638 _macro_ `#define RETURN_IF_EQUAL(Value) if (FCString::Stricmp(Buffer, TEXT(#Value)) == 0) { Error = EBuildPatchDownloadHealth::Value; return; }`

### `Source/Runtime/Online/BuildPatchServices/Public/Interfaces/IBuildInstallerSharedContext.h` (Public)


#### class `BuildPatchServices::IBuildInstallerThread`  
`class IBuildInstallerThread`  
_L13-26_
- desc: Interface for a re-usable thread
- L19 _protected prototype_ `virtual ~IBuildInstallerThread() = default;` — Virtual destructor.
- L25 _public prototype_ `virtual void RunTask(TUniqueFunction<void()> Task) = 0;` — Adds a task to the thread's queue

#### class `IBuildInstallerSharedContext`  
`class IBuildInstallerSharedContext`  
_L32-61_
- desc: An interface for sharing threads and components between multiple BPS installers
- L38 _public prototype_ `virtual ~IBuildInstallerSharedContext() = default;` — Virtual destructor.
- L44 _public prototype_ `virtual BuildPatchServices::IBuildInstallerThread* CreateThread() = 0;` — Return an existing free thread or allocate one. @return an IBuildInstallerThread
- L49 _public prototype_ `virtual void ReleaseThread(BuildPatchServices::IBuildInstallerThread* Thread) = 0;` — Relinquish the thread and add to the free list. It should not be used again after this.
- L55 _public prototype_ `virtual void PreallocateThreads(uint32 NumThreads) = 0;` — Preallocate thread free list with NumThreads. If more than NumThreads are required, a warning will be logged.
- L60 _public prototype_ `virtual uint32 NumThreadsPerInstaller(bool bUseChunkDBs, bool bHasInstallSource) const = 0;` — @return The number of threads required per installer

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace BuildPatchServices`
- L63 _typedef_ `using IBuildInstallerSharedContextRef = TSharedRef<IBuildInstallerSharedContext>;`
- L64 _typedef_ `using IBuildInstallerSharedContextPtr = TSharedPtr<IBuildInstallerSharedContext>;`
- L65 _typedef_ `using IBuildInstallerSharedContextWeakPtr = TWeakPtr<IBuildInstallerSharedContext>;`

### `Source/Runtime/Online/BuildPatchServices/Public/Interfaces/IBuildManifest.h` (Public)


#### enum `EFileMetaFlags`  
`enum class EFileMetaFlags : uint8`  
_L26-35_
- desc: Declares flags for meta or attributes associated with a file.
- L28 _public enumerator_ `None = 0`
- L30 _public enumerator_ `ReadOnly = 1` — Flag for readonly file.
- L32 _public enumerator_ `Compressed = 1 << 1` — Flag for natively compressed.
- L34 _public enumerator_ `UnixExecutable = 1 << 2` — Flag for unix executable.

#### class `IManifestField`  
`class IManifestField`  
_L41-66_
- desc: Interface to a manifest field, which is used for accessing custom fields in the manifest
- L47 _public prototype_ `virtual ~IManifestField() = default;` — Virtual destructor.
- L53 _public prototype_ `virtual FString AsString() const = 0;` — Get the fields value as an FString. @return	The string value.
- L59 _public prototype_ `virtual double AsDouble() const = 0;` — Get the fields value as a double. @return	The double value.
- L65 _public prototype_ `virtual int64 AsInteger() const = 0;` — Get the fields value as an int. @return	The int value.

#### class `IBuildManifest`  
`class IBuildManifest`  
_L71-420_
- desc: Interface to a Build Manifest.
- L77 _public prototype_ `virtual ~IBuildManifest() = default;` — Virtual destructor.
- L83 _public prototype_ `virtual BuildPatchServices::EFeatureLevel GetFeatureLevel() const = 0;` — Gets the manifest feature level @return		the feature level this manifest was built with
- L89 _public prototype_ `virtual uint32 GetAppID() const = 0;` — Get the App ID that this manifest belongs to @return		the app ID
- L95 _public prototype_ `virtual const FString& GetAppName() const = 0;` — Get the name of the App that this manifest belongs to @return		the app name
- L101 _public prototype_ `virtual const FString& GetVersionString() const = 0;` — Get the string App version that this manifest describes @return		the version string
- L107 _public prototype_ `virtual const FString& GetUniqueBuildId() const = 0;` — Get the unique string generated when producing the manifest @return		the unique build id string
- L114 _public prototype_ `virtual const FGuid& GetEncryptionSecretId(bool* bOutIsManifestEncrypted = nullptr) const = 0;` — If this manifest is or was encrypted, returns the GUID that identifies the secret key required for decryption. @param OUT	If the manifest in memory is currently encrypted. @return		the secret id
- L120 _public prototype_ `virtual bool IsManifestEncrypted() const = 0;` — Regardless of whether the manifest was ever encrypted, returns whether the manifest is currently encrypted. @return		If the manifest in memory is currently encrypted
- L127 _public prototype_ `virtual bool IsOriginallyFullyEncrypted() const = 0;` — Returns whether the manifest and all it chunks were originally encrypted when first loaded. This returns true even if the manifest has since been decrypted in memory. @return    true if the manifest was originally encrypted
- L133 _public prototype_ `virtual TSet<FGuid> GetNecessaryEncryptionSecretIds() const = 0;` — Get all necessary secret key IDs. @return		full set of necessary secret ids
- L139 _public prototype_ `virtual const FString& GetLaunchExe() const = 0;` — Get the local install path to the exe that launches the App @return		local path to the launch exe
- L145 _public prototype_ `virtual const FString& GetLaunchCommand() const = 0;` — Get the command line arguments that the launch exe should be ran with @return		the launch command line
- L151 _public prototype_ `virtual const TSet<FString>& GetPrereqIds() const = 0;` — Get the list of prereq ids that the prereq installer of this manifest satisfies @return		the set containing the prereq ids.
- L157 _public prototype_ `virtual const FString& GetPrereqName() const = 0;` — Get the name of the prerequisites installer for the app @return		the prerequisites installer name
- L163 _public prototype_ `virtual const FString& GetPrereqPath() const = 0;` — Get the path to the prerequisites installer exe @return		local path to the prerequisites installer
- L169 _public prototype_ `virtual const FString& GetPrereqArgs() const = 0;` — Get the command line arguments that should be passed to the prerequisites installer @return		the prerequisites installer command line arguments
- L175 _public prototype_ `virtual const FString& GetUninstallActionPath() const = 0;` — Get the path to the custom uninstall action exe @return		local path to the custom uninstall action exe
- L181 _public prototype_ `virtual const FString& GetUninstallActionArgs() const = 0;` — Get the command line arguments that should be passed to the custom uninstall action exe @return		the custom uninstall action command line arguments
- L187 _public prototype_ `virtual int64 GetDownloadSize() const = 0;` — Get the size of this download, assuming fresh install @return		the total download size in bytes
- L194 _public prototype_ `virtual int64 GetDownloadSize(const TSet<FString>& Tags) const = 0;` — Get the size of the download of this set of tags @param Tags	IN	A list of the tags we want to know the size of @return		the download size of the tags in bytes
- L202 _public prototype_ `virtual int64 GetDeltaDownloadSize(const TSet<FString>& Tags, const IBuildManifestRef& PreviousVersion) const = 0;` — Get the size of the download of this set of tags @param Tags              IN  The tags used for installation, will be applied to both manifests @param PreviousVersion   IN  The manifest for previous version to compare against @return the minimum download size required in bytes
- L211 _public prototype_ `virtual int64 GetDeltaDownloadSize(const TSet<FString>& Tags, const IBuildManifestRef& PreviousVersion, const TSet<FString>& PreviousTags) const = 0;` — Get the size of the download of this set of tags @param Tags              IN  The tags used for installation @param PreviousVersion   IN  The manifest for previous version to compare against @param PreviousTags      IN  The tags used for previous installation @return the minimum download size required in bytes
- L217 _public prototype_ `virtual int64 GetBuildSize() const = 0;` — Get the size of this build @return		the build size in bytes
- L224 _public prototype_ `virtual int64 GetBuildSize(const TSet<FString>& Tags) const = 0;` — Get the size of the build of this set of tags @param Tags	IN	A list of the tags we want to know the size of @return		the build size of the tags in bytes
- L230 _public prototype_ `virtual TArray<FString> GetBuildFileList() const = 0;` — Get the list of files in this build. Filenames are all relative to an install directory @return an array containing build files
- L237 _public prototype_ `virtual TArray<FStringView> GetBuildFileListView() const = 0;` — Get the list of files in this build. Filenames are all relative to an install directory. Filenames returned are a view over memory owned by the BuildManifest @return an array containing build files
- L244 _public prototype_ `virtual TArray<FString> GetBuildFileList(const TSet<FString>& Tags) const = 0;` — Get the list of files in this build which match a tag from a given set. Filenames are all relative to an install directory @param		Tags	The set of tags to query @return an array containing build files
- L251 _public prototype_ `virtual TArray<FStringView> GetBuildFileListView(const TSet<FString>& Tags) const = 0;` — Get the list of files in this build which match a tag from a given set. Filenames are all relative to an install directory Filenames returned are a view over memory owned by the BuildManifest @return an array containing build files
- L258 _public prototype_ `virtual int64 GetFileSize(FStringView Filename) const = 0;` — Returns the size of a particular file in the build @param Filename      The file. @return the file size.
- L265 _public prototype_ `virtual int64 GetFileSize(const TArray<FString>& Filenames) const = 0;` — Returns the total size of all files in the array @param Filenames     The array of files. @return the total size of files in array.
- L272 _public prototype_ `virtual int64 GetFileSize(const TSet<FString>& Filenames) const = 0;` — Returns the total size of all files in the set @param Filenames     The set of files. @return the total size of files in set.
- L279 _public prototype_ `virtual EFileMetaFlags GetFileMetaFlags(const FString& Filename) const = 0;` — Get the file meta flags assigned to a particular file in the build. @param Filename      The file. @return		the file meta flags
- L286 _public prototype_ `virtual const FMD5Hash* GetFileMD5Hash(const FString& Filename) const = 0;` — Gets the MD5 hash for a given file @param Filename      The file. @return ptr to the MD5 for the given file. Nullptr if not found.
- L293 _public prototype_ `virtual const FSHAHash* GetFileSHA1Hash(const FString& Filename) const = 0;` — Gets the SHA1 hash for a given file @param Filename      The file. @return ptr to the SHA1 for the given file. Nullptr if not found.
- L300 _public prototype_ `virtual const FSHA256Signature* GetFileSHA256Hash(const FString& Filename) const = 0;` — Gets the SHA256 hash for a given file @param Filename      The file. @return ptr to the SHA256 for the given file. Nullptr if not found.
- L307 _public prototype_ `virtual const FString* GetFileMIMEType(const FString& Filename) const = 0;` — Gets the MIME type calculated for a given file @param Filename      The file. @return ptr to the MIME type string for the given file. Nullptr if not found.
- L313 _public prototype_ `virtual TSet<FString> GetFileTagList() const = 0;` — Get the list of install tags in this manifest @return the tags referenced.
- L319 _public prototype_ `virtual void GetFileTagList(TSet<FString>& Tags) const = 0;` — Get the list of install tags in this manifest @param Tags			OUT		Receives the tags referenced.
- L326 _public prototype_ `virtual void GetOutdatedFiles(const IBuildManifestRef& OldManifest, TSet<FString>& OutdatedFiles) const = 0;` — Gets a list of files that were installed with the Old Manifest, but no longer required by this Manifest. @param OldManifest     IN    The Build Manifest that is currently installed. @param RemovableFiles  OUT   A list to receive the files that may be removed.
- L333 _public prototype_ `virtual void GetRemovableFiles(const IBuildManifestRef& OldManifest, TArray<FString>& RemovableFiles) const = 0;` — Gets a list of files that were installed with the Old Manifest, but no longer required by this Manifest. @param OldManifest     IN    The Build Manifest that is currently installed. @param RemovableFiles  OUT   A list to receive the files that may be removed.
- L340 _public prototype_ `virtual void GetRemovableFiles(const TCHAR* InstallPath, TArray<FString>& RemovableFiles) const = 0;` — Gets a list of files that are installed in InstallPath, but no longer required by this Manifest. @param InstallPath     IN    The path to the currently installed files. @param RemovableFiles  OUT   A list to receive the files that may be removed.
- L347 _public prototype_ `virtual void GetChunksRequiredForFiles(const TSet<FString>& Filenames, TSet<FGuid>& RequiredChunks) const = 0;` — Provides the set of chunks required to produce the given files. @param Filenames         IN      The set of files. @param RequiredChunks    OUT     The set of chunk GUIDs needed for those files.
- L354 _public prototype_ `virtual int64 GetDataSize(const FGuid& DataGuid) const = 0;` — Returns the size of a particular data file by it's GUID. @param DataGuid		The GUID for the data @return		File size, or 0 if this data is not in the manifest.
- L362 _public prototype_ `virtual bool GetChunkShaHash(const FGuid& ChunkGuid, FSHAHash& OutHash) const = 0;` — Gets the SHA1 hash for a given chunk @param ChunkGuid		IN		The guid of the chunk to get hash for @param OutHash		OUT		Receives the hash value if found @return	true if we had the hash for this chunk
- L370 _public prototype_ `virtual bool GetChunkEncryptionSecretId(const FGuid& ChunkGuid, FGuid& OutEncryptionSecretId) const = 0;` — Gets the secret ID of the chunk @param ChunkGuid					IN		The guid of the chunk to get secret ID for @param OutEncryptionSecretId		OUT		The guid value of chunk's secret ID if found @return true the chunk has encryption secret
- L376 _public prototype_ `virtual bool NeedsResaving() const = 0;` — Checks the manifest format version to see if this manifest was loaded from latest data @return True if the manifest was created from the latest format
- L383 _public prototype_ `virtual void CopyCustomFields(const IBuildManifestRef& Other, bool bClobber) = 0;` — Copy the custom fields from another manifest into this one. If this manifest has custom fields, matching keys will be overwritten but extras will remain @param Other		The manifest to copy from @param bClobber	Whether to overwrite any already existing fields
- L389 _public prototype_ `virtual TArray<FString> GetCustomFieldNames() const = 0;` — Get the list of custom field names in this manifest @return an array containing custom field names
- L396 _public prototype_ `virtual const IManifestFieldPtr GetCustomField(const FString& FieldName) const = 0;` — Get a custom field from the manifest @param	FieldName	The name of the custom field @return An interface to the field
- L404 _public prototype_ `virtual const IManifestFieldPtr SetCustomField(const FString& FieldName, const FString& Value) = 0;` — Various functions for setting a custom field in the manifest @param	FieldName	The name of the custom field @param	Value		The value for the field @return An interface to the field that was created
- L405 _public prototype_ `virtual const IManifestFieldPtr SetCustomField(const FString& FieldName, const double& Value) = 0;`
- L406 _public prototype_ `virtual const IManifestFieldPtr SetCustomField(const FString& FieldName, const int64& Value) = 0;`
- L412 _public prototype_ `virtual void RemoveCustomField(const FString& FieldName) = 0;` — Remove a custom field from the manifest @param	FieldName	The name of the custom field
- L419 _public prototype_ `virtual IBuildManifestRef Duplicate() const = 0;` — Duplicated this manifest to create a copy. Should be used if storing a received manifest as an installed manifest which would then be unique @return A shared ref to the new manifest

#### Free symbols / members of external scopes

- L18 _typedef_ `typedef TSharedPtr< class IManifestField, ESPMode::ThreadSafe > IManifestFieldPtr;`
- L19 _typedef_ `typedef TSharedRef< class IManifestField, ESPMode::ThreadSafe > IManifestFieldRef;`
- L20 _typedef_ `typedef TSharedPtr< class IBuildManifest, ESPMode::ThreadSafe > IBuildManifestPtr;`
- L21 _typedef_ `typedef TSharedRef< class IBuildManifest, ESPMode::ThreadSafe > IBuildManifestRef;`
- L36 _prototype_ `ENUM_CLASS_FLAGS(EFileMetaFlags);`

### `Source/Runtime/Online/BuildPatchServices/Public/Interfaces/IBuildPatchServicesModule.h` (Public)


#### enum `ECompactifyMode::Type`  
`enum Type`  
_L26-30_
- L28 _public enumerator_ `Preview`
- L29 _public enumerator_ `Full`

#### class `IBuildPatchServicesModule`  
`class IBuildPatchServicesModule : public IModuleInterface`  
_L36-370_
- inherits: `IModuleInterface`
- desc: Interface for the services manager.
- L43 _public prototype_ `virtual ~IBuildPatchServicesModule() = default;` — Virtual destructor.
- L51 _public prototype_ `virtual IBuildInstallerRef CreateBuildInstaller(BuildPatchServices::FBuildInstallerConfiguration Configuration, FBuildPatchInstallerDelegate OnComplete) const = 0;` — Factory providing construction of a build installer class. @param Configuration     The configuration for the installer. @param OnComplete        The delegate that will be called when the installer completes. @return an instance of an IBuildInstaller implementation.
- L58 _public prototype_ `virtual IBuildInstallerSharedContextRef CreateBuildInstallerSharedContext(const TCHAR* DebugName) const = 0;` — Factory providing construction of a build installer shared context class. @param DebugName          Used to tag resources allocated with the shared context. @return an instance of an IBuildInstallerSharedContex implementation.
- L65 _public prototype_ `virtual BuildPatchServices::IBuildStatisticsRef CreateBuildStatistics(const IBuildInstallerRef& Installer) const = 0;` — Factory providing construction of a build statistics class. @param Installer     The installer to create a build statistics for. @return an instance of an IBuildStatistics implementation.
- L72 _public prototype_ `virtual BuildPatchServices::IDirectoryChunkerRef CreateDirectoryChunker(BuildPatchServices::FDirectoryChunkerConfiguration Configuration) const = 0;` — Factory providing construction of a directory chunker class. @param Configuration         Specifies the settings for the operation.  See BuildPatchServices::FDirectoryChunkerConfiguration comments. @return an instance of an IDirectoryChunker implementation.
- L79 _public prototype_ `virtual BuildPatchServices::IPatchDataEnumerationRef CreatePatchDataEnumeration(BuildPatchServices::FPatchDataEnumerationConfiguration Configuration) const = 0;` — Factory providing construction of a patch data enumeration class. @param Configuration         Specifies the settings for the operation.  See BuildPatchServices::FPatchDataEnumerationConfiguration comments. @return an instance of an IPatchDataEnumeration implementation.
- L86 _public prototype_ `virtual BuildPatchServices::IChunkDeltaOptimiserRef CreateChunkDeltaOptimiser(BuildPatchServices::FChunkDeltaOptimiserConfiguration Configuration) const = 0;` — Factory providing construction of a chunk delta optimiser class. @param Configuration         Specifies the settings for the operation.  See BuildPatchServices::FChunkDeltaOptimiserConfiguration comments. @return an instance of an IChunkDeltaOptimiser implementation.
- L93 _public prototype_ `virtual BuildPatchServices::IChunkHarvesterRef CreateChunkHarvester(BuildPatchServices::FChunkHarvesterConfiguration Configuration) const = 0;` — Factory providing construction of a chunk harvester class. @param Configuration         Specifies the settings for the operation.  See BuildPatchServices::FChunkHarvesterConfiguration comments. @return an instance of an IChunkHarvester implementation.
- L100 _public prototype_ `virtual IBuildManifestPtr LoadManifestFromFile( const FString& Filename ) = 0;` — Loads a Build Manifest from file and returns the interface @param Filename		The file to load from @return		a shared pointer to the manifest, which will be invalid if load failed.
- L107 _public prototype_ `virtual IBuildManifestPtr MakeManifestFromData( const TArray<uint8>& ManifestData ) = 0;` — Constructs a Build Manifest from a data @param ManifestData		The data received from a web api @return		a shared pointer to the manifest, which will be invalid if creation failed.
- L115 _public prototype_ `virtual bool SaveManifestToFile(const FString& Filename, IBuildManifestRef Manifest) = 0;` — Saves a Build Manifest to file @param Filename		The file to save to @param Manifest		The manifest to save out @return		If the save was successful.
- L121 _public prototype_ `virtual TSet<FString> GetInstalledPrereqIds() const = 0;` — Gets an array of prerequisite identifiers that are registered as installed on this system. @return a set containing all installed prerequisite identifiers.
- L127 _public prototype_ `virtual const TArray<IBuildInstallerRef>& GetInstallers() const = 0;` — Gets a list of currently active installers @return all installers that are currently active.
- L133 _public prototype_ `virtual void SetStagingDirectory( const FString& StagingDir ) = 0;` — Sets the directory used for staging intermediate files. @param StagingDir	The staging directory
- L139 _public prototype_ `virtual void SetCloudDirectory( FString CloudDir ) = 0;` — Sets the cloud directory where chunks and manifests will be pulled from and saved to. @param CloudDir		The cloud directory
- L146 _public prototype_ `virtual void SetCloudDirectories( TArray<FString> CloudDirs ) = 0;` — Sets the cloud directory list where chunks and manifests will be pulled from and saved to. When downloading, if we get a failure, we move on to the next cloud option for that request. @param CloudDirs		The cloud directory list
- L152 _public prototype_ `virtual void SetBackupDirectory( const FString& BackupDir ) = 0;` — Sets the backup directory where files that are being clobbered by repair/patch will be placed. @param BackupDir		The backup directory
- L158 _public prototype_ `virtual void SetAnalyticsProvider( TSharedPtr< IAnalyticsProvider > AnalyticsProvider ) = 0;` — Sets the Analytics provider that will be used to register errors with patch/build installs @param AnalyticsProvider		Shared ptr to an analytics interface to use. If NULL analytics will be disabled.
- L165 _public prototype_ `virtual void RegisterAppInstallation(IBuildManifestRef AppManifest, const FString AppInstallDirectory) = 0;` — Registers an installation on this machine. This information is used to gather a list of install locations that can be used as chunk sources. @param AppManifest			Ref to the manifest for this installation @param AppInstallDirectory	The install location
- L172 _public prototype_ `virtual bool UnregisterAppInstallation(const FString AppInstallDirectory) = 0;` — Unregisters an installation on this machine @param AppInstallDirectory	The install location which RegisterAppInstallation was executed with @return returns true if successfully removed installation directory
- L179 _public prototype_ `virtual void RegisterEncryptionSecret(const FGuid& EncryptionSecretId, TArray<uint8> EncryptionSecretKey) = 0;` — Registers an encryption secret. This information is used by installers to decrypt patch data that references this secret. @param EncryptionSecretId    The ID for the secret key. @param EncryptionSecretKey   The secret key.
- L186 _public prototype_ `virtual bool UnregisterEncryptionSecret(const FGuid& EncryptionSecretId) = 0;` — Unregisters an encryption secret. @param EncryptionSecretId    The ID for the secret key. @return returns true if the secret existed and was removed.
- L193 _public prototype_ `virtual bool CreateRandomBytes(const TArrayView<uint8> OutData) = 0;` — Generates random data via OpenSSL. @param OutData    The object to fill with random data. @return returns true if OpenSSL was able to generate random data.
- L199 _public prototype_ `virtual void CancelAllInstallers(bool WaitForThreads) = 0;` — Call to force the exit out of all current installers, optionally blocks until threads have exited and complete delegates are called. @param WaitForThreads		If true, will block on threads exit and completion delegates
- L207 _public prototype_ `virtual bool CompactifyCloudDirectory(const BuildPatchServices::FCompactifyConfiguration& Configuration) = 0;` — Processes a Cloud Directory to identify and delete any orphaned chunks or files. NOTE: THIS function is blocking and will not return until finished. @param Configuration         Specifies the settings for the operation. See BuildPatchServices::FCompactifyConfiguration comments. @return true if successful.
- L216 _public prototype_ `virtual bool VerifyChunkData(const FString& SearchPath, const FString& OutputFile) = 0;` — Searches a given directory for chunk and chunkdb files, and verifies their integrity uses the hashes in the files. NOTE: THIS function is blocking and will not return until finished. Don't run on main thread. @param SearchPath            A full file path for the directory to search. @param OutputFile            A full file path where to save the output text. @return true if successful and no corruptions detected.
- L224 _public prototype_ `virtual bool PackageChunkData(const BuildPatchServices::FPackageChunksConfiguration& Configuration) = 0;` — Packages data referenced by a manifest file into chunkdb files, supporting a maximum filesize per chunkdb. NOTE: THIS function is blocking and will not return until finished. Don't run on main thread. @param Configuration         Specifies the settings for the operation. See BuildPatchServices::FPackageChunksConfiguration comments. @return true if successful.
- L239 _public prototype_ `virtual bool MergeManifests(const FString& ManifestFilePathA, const FString& ManifestFilePathB, const FString& ManifestFilePathC, const FString& NewVersionString, const FString& SelectionDetailFilePath) = 0;` — Takes two manifests as input, in order to merge together producing a new manifest containing all files. NOTE: THIS function is blocking and will not return until finished. Don't run on main thread. @param ManifestFilePathA         A full file path for the base manifest to be loaded. @param ManifestFilePathB         A full file path for the merge manifest to be loaded, by default files in B will stomp over A. @param ManifestFilePathC         A full file path for the manifest to be output. @param NewVersionString          The new version string for the build, all other meta will be copied from B. @param SelectionDetailFilePath   Optional full file path to a text file listing each build relative file required, followed by A or B to select which manifest to pull from. The format should be \r\n separated lines of filename \t A|B. Example: File/in/build1	A File/in/build2	B @return true if successful.
- L251 _public prototype_ `virtual IBuildManifestPtr MergeManifests(const IBuildManifestRef& ManifestA, const IBuildManifestRef& ManifestB, const FString& NewVersionString, const TSet<FString>& FilesFromA, const TSet<FString>& FilesFromB) = 0;` — Takes two manifests as input, in order to merge together producing a new manifest containing all files. NOTE: THIS function is blocking and will not return until finished. Don't run on main thread. @param ManifestFilePathA         A full file path for the base manifest to be loaded. @param ManifestFilePathB         A full file path for the merge manifest to be loaded, by default files in B will stomp over A. @param NewVersionString          The new version string for the build, all other meta will be copied from B. @param FilesFromA                A set containing the files that should be kept from ManifestA. @param FilesFromB                A set containing the files that should be kept from ManifestB. @return resulting manifest if successful.
- L259 _public prototype_ `virtual bool DiffManifests(const BuildPatchServices::FDiffManifestsConfiguration& Configuration) = 0;` — Takes two manifests as input and outputs the details of the patch. NOTE: THIS function is blocking and will not return until finished. Don't run on main thread. @param Configuration         Specifies the settings for the operation. See BuildPatchServices::FDiffManifestsConfiguration comments. @return true if successful.
- L264 _public prototype_ `DECLARE_EVENT(IBuildPatchServicesModule, FSimpleEvent) virtual FSimpleEvent& OnStartBuildInstall() = 0;` — Returns an event which fires when we start a new build install.
- L271 _public prototype_ `virtual IBuildManifestPtr MakeManifestFromJSON(const FString& ManifestJSON) = 0;` — `UE_DEPRECATED(4.21, "MakeManifestFromJSON(const FString& ManifestJSON) has been deprecated. Please use MakeManifestFromData(const TArray<uint8>& ManifestData) instead.")`
- L274 _public function_ `virtual bool EnumerateManifestData(const FString& ManifestFilePath, const FString& OutputFile, bool bIncludeSizes)` — `UE_DEPRECATED(4.16, "EnumerateManifestData(const FString& ManifestFilePath, const FString& OutputFile, bool bIncludeSizes) has been deprecated. Please use CreatePatchDataEnumeration(BuildPatchServices::FPatchDataEnumerationConfiguration Configuration) instead.")`
- L285 _public function_ `virtual bool ChunkBuildDirectory(const BuildPatchServices::FChunkBuildConfiguration& Configuration)` — `UE_DEPRECATED(4.23, "ChunkBuildDirectory(const BuildPatchServices::FChunkBuildConfiguration& Configuration) has been deprecated. Please use CreateDirectoryChunker(BuildPatchServices::FDirectoryChunkerConfiguration Configuration) instead.")`
- L292 _public function_ `virtual bool EnumeratePatchData(const BuildPatchServices::FPatchDataEnumerationConfiguration& Configuration)` — `UE_DEPRECATED(4.23, "EnumeratePatchData(const BuildPatchServices::FPatchDataEnumerationConfiguration& Configuration) has been deprecated. Please use CreatePatchDataEnumeration(BuildPatchServices::FPatchDataEnumerationConfiguration Configuration) instead.")`
- L299 _public function_ `virtual bool OptimiseChunkDelta(const BuildPatchServices::FChunkDeltaOptimiserConfiguration& Configuration)` — `UE_DEPRECATED(4.23, "OptimiseChunkDelta(const BuildPatchServices::FChunkDeltaOptimiserConfiguration& Configuration) has been deprecated. Please use CreateChunkDeltaOptimiser(BuildPatchServices::FChunkDeltaOptimiserConfiguration Configuration) instead.")`
- L306 _public function_ `virtual bool GenerateChunksManifestFromDirectory(const BuildPatchServices::FGenerationConfiguration& Configuration)` — `UE_DEPRECATED(4.21, "GenerateChunksManifestFromDirectory(const BuildPatchServices::FGenerationConfiguration& Configuration) has been deprecated. Please use CreateDirectoryChunker(BuildPatchServices::FDirectoryChunkerConfiguration Configuration) instead.")`
- L313 _public function_ `IBuildInstallerPtr StartBuildInstall(IBuildManifestPtr CurrentManifest, IBuildManifestPtr InstallManifest, const FString& InstallDirectory, FBuildPatchBoolManifestDelegate OnCompleteDelegate, bool bIsRepair = false, TSet<FString> InstallTags = TSet<FString>())` — `UE_DEPRECATED(4.23, "StartBuildInstall(IBuildManifestPtr, IBuildManifestPtr, const FString&, FBuildPatchBoolManifestDelegate, bool, TSet<FString>) has been deprecated. Please use CreateBuildInstaller(BuildPatchServices::FBuildInstallerConfiguration, FBuildPatchInstallerDelegate) instead, followed by IBuildInstaller::StartInstallation.")`
- L326 _public function_ `IBuildInstallerPtr StartBuildInstallStageOnly(IBuildManifestPtr CurrentManifest, IBuildManifestPtr InstallManifest, const FString& InstallDirectory, FBuildPatchBoolManifestDelegate OnCompleteDelegate, bool bIsRepair = false, TSet<FString> InstallTags = TSet<FString>())` — `UE_DEPRECATED(4.23, "StartBuildInstallStageOnly(IBuildManifestPtr, IBuildManifestPtr, const FString&, FBuildPatchBoolManifestDelegate, bool, TSet<FString>) has been deprecated. Please use CreateBuildInstaller(BuildPatchServices::FBuildInstallerConfiguration, FBuildPatchInstallerDelegate) instead, followed by IBuildInstaller::StartInstallation.")`
- L340 _public function_ `IBuildInstallerRef StartBuildInstall(BuildPatchServices::FInstallerConfiguration Configuration, FBuildPatchBoolManifestDelegate OnCompleteDelegate)` — `UE_DEPRECATED(4.23, "StartBuildInstall(BuildPatchServices::FInstallerConfiguration, FBuildPatchBoolManifestDelegate) has been deprecated. Please use CreateBuildInstaller(BuildPatchServices::FBuildInstallerConfiguration, FBuildPatchInstallerDelegate) instead, followed by IBuildInstaller::StartInstallation.")`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FBuildPatchInstallerDelegate, const IBuildInstallerRef&);` — Delegates that will be accepted and fired off by the implementation.
- L19 _prototype_ `DECLARE_DELEGATE_OneParam(FBuildPatchInstallerDelegate, const IBuildInstallerRef&);` — Delegates that will be accepted and fired off by the implementation.
- L20 _delegate_ `DECLARE_DELEGATE_TwoParams(FBuildPatchBoolManifestDelegate, bool, IBuildManifestRef);`
- L20 _prototype_ `DECLARE_DELEGATE_TwoParams(FBuildPatchBoolManifestDelegate, bool, IBuildManifestRef);`
- L21 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FSingleChunkWrittenDelegate, FString , FString );`
- L21 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FSingleChunkWrittenDelegate, FString , FString );`
- L22 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FManifestCreatedDelegate, FString , FString , FString );`
- L22 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FManifestCreatedDelegate, FString , FString , FString );`
- L24 _namespace_ `namespace ECompactifyMode`
- L264 _delegate_ `DECLARE_EVENT(IBuildPatchServicesModule, FSimpleEvent) virtual FSimpleEvent& OnStartBuildInstall() = 0;` — Returns an event which fires when we start a new build install.
- L317 _function_ `` (scope `IBuildPatchServicesModule::StartBuildInstall`)
- L331 _function_ `` (scope `IBuildPatchServicesModule::StartBuildInstallStageOnly`)

### `Source/Runtime/Online/BuildPatchServices/Public/Interfaces/IBuildStatistics.h` (Public)


#### enum `BuildPatchServices::EFileOperationState`  
`enum class EFileOperationState : int32`  
_L15-65_
- desc: An enum describing the current state of the data for a file operation that has or will be processed.
- L18 _public enumerator_ `Unknown = 0` — Not yet evaluated.
- L21 _public enumerator_ `PendingLocalChunkDbData` — The data for this operation has not yet been requested (from a local chunkdb source).
- L24 _public enumerator_ `RetrievingLocalChunkDbData` — The data is being acquired (from a local chunkdb source).
- L27 _public enumerator_ `PendingLocalInstallData` — The data for this operation has not yet been requested (from a local install source).
- L30 _public enumerator_ `RetrievingLocalInstallData` — The data is being acquired (from a local install source).
- L33 _public enumerator_ `PendingRemoteCloudData` — The data for this operation has not yet been requested (from a remote cloud source).
- L36 _public enumerator_ `RetrievingRemoteCloudData` — The data is being acquired (from a remote cloud source).
- L39 _public enumerator_ `PendingLocalDataStore` — The data is in a local store to be loaded later.
- L42 _public enumerator_ `RetrievingLocalDataStore` — The data is being acquired (from a local store).
- L45 _public enumerator_ `DataInMemoryStore` — The data is in a memory chunk store ready for use.
- L48 _public enumerator_ `Staged` — The file operation has been written to the staging location.
- L51 _public enumerator_ `Installed` — The file operation has been written to the destination install location.
- L54 _public enumerator_ `Verifying` — The file operation is being verified.
- L57 _public enumerator_ `VerifiedFail` — The file operation has been verified and is corrupt.
- L60 _public enumerator_ `VerifiedSuccess` — The file operation has been verified and successful.
- L63 _public enumerator_ `NUM_States` — Helpers.
- L64 _public enumerator_ `Complete = NUM_States - 1`

#### struct `BuildPatchServices::FFileOperation`  
`struct FFileOperation`  
_L70-87_
- desc: A struct representing a file operation to be completed.
- L73 _public prototype_ `FFileOperation(FString Filename, const FGuid& DataId, uint64 Offest, uint64 Size, EFileOperationState CurrentState);`
- L74 _public prototype_ `~FFileOperation();`
- L78 _public member_ `FString Filename;` — The build filename where this data section goes.
- L80 _public member_ `FGuid DataId;` — The idea of the chunk where the data is taken from.
- L82 _public member_ `uint64 Offest;` — The offset into the file.
- L84 _public member_ `uint64 Size;` — The size of the data to write.
- L86 _public member_ `EFileOperationState CurrentState;` — The current state of this operation.

#### struct `BuildPatchServices::FDownload`  
`struct FDownload`  
_L92-100_
- desc: A struct representing a download.
- L95 _public member_ `FString Data;` — The uri for the download.
- L97 _public member_ `int64 Size;` — The size of the download.
- L99 _public member_ `int64 Received;` — The amount of data received so far.

#### class `BuildPatchServices::IBuildStatistics`  
`class IBuildStatistics`  
_L105-238_
- desc: An interface for accessing runtime statistical information about an installer.
- L111 _public prototype_ `virtual ~IBuildStatistics() = default;` — Virtual destructor.
- L116 _public prototype_ `virtual const FBuildInstallerConfiguration& GetConfiguration() const = 0;` — @return the configuration used when constructing the installer.
- L121 _public prototype_ `virtual int64 GetDownloadSize() const = 0;` — @return the total download size for the installation.
- L126 _public prototype_ `virtual int64 GetBuildSize() const = 0;` — @return the total install size for the installation.
- L131 _public function_ `virtual int32 GetMemoryChunkStoreSize() const` — @return the size in chunks of the memory store.
- L136 _public function_ `virtual int32 GetMemoryChunksInStore() const` — @return the number of chunks currently in the memory store.
- L141 _public function_ `virtual int32 GetMemoryChunksBooted() const` — @return the number of chunks that have been booted from the memory store.
- L146 _public function_ `virtual int32 GetMemoryChunksRetained() const` — @return the number of chunks currently in the memory store which are held due to multiple referencing.
- L151 _public prototype_ `virtual FString GetCurrentWorkingFileName() const = 0;` — @return the filename of the file currently being worked on.
- L156 _public prototype_ `virtual float GetCurrentWorkingFileProgress() const = 0;` — @return the progress of the file currently being worked on.
- L161 _public prototype_ `virtual FGuid GetCurrentWorkingData() const = 0;` — @return the chunk ID currently being used to write the current file.
- L166 _public prototype_ `virtual TArray<FDownload> GetCurrentDownloads() const = 0;` — @return an array of currently active downloads.
- L171 _public prototype_ `virtual bool IsDownloadActive() const = 0;` — @return true if there are downloads currently active.
- L176 _public prototype_ `virtual bool IsHardDiskActiveAdministering() const = 0;` — @return true if the current operation is creating or opening files.
- L181 _public prototype_ `virtual bool IsHardDiskActiveWrite() const = 0;` — @return true if currently writing data to disk.
- L186 _public prototype_ `virtual bool IsHardDiskActiveRead() const = 0;` — @return true if currently reading data from disk.
- L191 _public prototype_ `virtual const TArray<FFileOperation>& GetFileOperationStates() const = 0;` — @return an array containing the states for all file write operations being performed by this installation.
- L196 _public prototype_ `virtual double GetDownloadByteSpeed() const = 0;` — @return the current download speed in bytes per second.
- L201 _public prototype_ `virtual double GetDiskReadByteSpeed() const = 0;` — @return the current disk read speed in bytes per second.
- L207 _public function_ `double GetChunkDbReadByteSpeed() const` — `UE_DEPRECATED(5.6, "Chunk db read speeds now included in DiskReadByteSpeed")` — @return the current chunkdb read speed in bytes per second.
- L212 _public prototype_ `virtual double GetDiskWriteByteSpeed() const = 0;` — @return the current disk write speed in bytes per second.
- L217 _public prototype_ `virtual int64 GetDownloadedBytes() const = 0;` — @return the number of bytes downloaded so far.
- L222 _public prototype_ `virtual int64 GetDiskReadBytes() const = 0;` — @return the number of bytes read so far.
- L227 _public prototype_ `virtual int64 GetDiskWrittenBytes() const = 0;` — @return the number of bytes written so far.
- L232 _public prototype_ `virtual int32 GetNumVerifyErrors() const = 0;` — @return the total number of verify errors experienced during this installation.
- L237 _public prototype_ `virtual TMap<EVerifyError, int32> GetVerifyErrorCounts() const = 0;` — @return the verify error counts per error type experienced during this installation.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace BuildPatchServices`
- L240 _typedef_ `typedef TSharedPtr<IBuildStatistics> IBuildStatisticsPtr;` (scope `BuildPatchServices`)
- L241 _typedef_ `typedef TSharedRef<IBuildStatistics> IBuildStatisticsRef;` (scope `BuildPatchServices`)
- L244 _function_ `inline const TCHAR* LexToString(BuildPatchServices::EFileOperationState Value)`
- L248 _macro_ `#define CASE_ENUM_TO_STR(_X_) case EFileOperationState::_X_: return TEXT(#_X_)`
- L272 _function_ `inline void LexFromString(BuildPatchServices::EFileOperationState& Value, const TCHAR* Buffer)`
- L276 _macro_ `#define RETURN_IF_EQUAL(_X_) if (FCString::Stricmp(Buffer, TEXT(#_X_)) == 0) { Value = EFileOperationState::_X_; return; }`

### `Source/Runtime/Online/BuildPatchServices/Public/Interfaces/IChunkDeltaOptimiser.h` (Public)


#### class `BuildPatchServices::IChunkDeltaOptimiser`  
`class IChunkDeltaOptimiser`  
_L9-47_
- L12 _public function_ `virtual ~IChunkDeltaOptimiser()`
- L20 _public prototype_ `DECLARE_EVENT_TwoParams(IChunkDeltaOptimiser, FOnChunkFileWritten, const FString& , const FMD5Hash& );` — Declares an event type exposed on this class for when files have been saved to the cloud directory. The event offers an MD5 hash of the file. @param FullFilePath   The full file path on disk for the file saved. @param MD5Hash        The MD5 checksum for the file.
- L29 _public prototype_ `DECLARE_EVENT_ThreeParams(IChunkDeltaOptimiser, FOnDeltaFileWritten, const FString& , const FMD5Hash& , const FSHAHash& );` — Declares an event type exposed on this class for when files have been saved to the cloud directory. The event offers two types of hash of the file. @param FullFilePath   The full file path on disk for the file saved. @param MD5Hash        The MD5 checksum for the file. @param SHA1Hash       The SHA1 checksum for the file.
- L34 _public prototype_ `virtual FOnChunkFileWritten& OnChunkFileWritten() = 0;` — @return a delegate that will broadcast when a chunk was written to the cloud directory.
- L39 _public prototype_ `virtual FOnDeltaFileWritten& OnDeltaFileWritten() = 0;` — @return a delegate that will broadcast when the delta file was written to the cloud directory.
- L46 _public prototype_ `virtual bool Run() = 0;` — Executes the delta optimization. The process takes a pair of manifests to produce additional delta data which reduces the download size to patch directly between them. NOTE: This function is blocking and will not return until finished. @return true if successful.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace BuildPatchServices`
- L20 _delegate_ `DECLARE_EVENT_TwoParams(IChunkDeltaOptimiser, FOnChunkFileWritten, const FString& , const FMD5Hash& );` — Declares an event type exposed on this class for when files have been saved to the cloud directory. The event offers an MD5 hash of the file. @param FullFilePath   The full file path on disk for the file saved. @param MD5Hash        The MD5 checksum for the file.
- L29 _delegate_ `DECLARE_EVENT_ThreeParams(IChunkDeltaOptimiser, FOnDeltaFileWritten, const FString& , const FMD5Hash& , const FSHAHash& );` — Declares an event type exposed on this class for when files have been saved to the cloud directory. The event offers two types of hash of the file. @param FullFilePath   The full file path on disk for the file saved. @param MD5Hash        The MD5 checksum for the file. @param SHA1Hash       The SHA1 checksum for the file.
- L49 _typedef_ `typedef TSharedPtr<IChunkDeltaOptimiser> IChunkDeltaOptimiserPtr;` (scope `BuildPatchServices`)
- L50 _typedef_ `typedef TSharedRef<IChunkDeltaOptimiser> IChunkDeltaOptimiserRef;` (scope `BuildPatchServices`)

### `Source/Runtime/Online/BuildPatchServices/Public/Interfaces/IChunkHarvester.h` (Public)


#### class `BuildPatchServices::IChunkHarvester`  
`class IChunkHarvester`  
_L10-50_
- L13 _public function_ `virtual ~IChunkHarvester()`
- L21 _public prototype_ `DECLARE_EVENT_TwoParams(IChunkHarvester, FOnChunkFileWritten, const FString& , const FMD5Hash& );` — Declares an event type exposed on this class for when data files have been saved to the cloud directory. The event offers an MD5 hash of the file. @param FullFilePath   The full file path on disk for the file saved. @param MD5Hash        The MD5 checksum for the file.
- L27 _public prototype_ `DECLARE_EVENT_OneParam(IChunkHarvester, FOnManifestLoaded, const IBuildManifest& );` — Declares an event type exposed to this class when the manifest has been loaded, providing the result. @param Manifest        The loaded manifest.
- L32 _public prototype_ `virtual FOnChunkFileWritten& OnChunkFileWritten() = 0;` — @return a delegate that will broadcast when a chunk was written to the cloud directory.
- L37 _public prototype_ `virtual FOnManifestLoaded& OnManifestLoaded() = 0;` — @return a delegate that will broadcast when a chunk was written to the cloud directory.
- L44 _public prototype_ `virtual bool Run() = 0;` — Uses the manifest file to rebuild the cloud directory from the orignal build data. NOTE: This function is blocking and will not return until finished. @return Success
- L49 _public prototype_ `virtual void Abort() = 0;` — Signal to the process that it should abort.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace BuildPatchServices`
- L21 _delegate_ `DECLARE_EVENT_TwoParams(IChunkHarvester, FOnChunkFileWritten, const FString& , const FMD5Hash& );` — Declares an event type exposed on this class for when data files have been saved to the cloud directory. The event offers an MD5 hash of the file. @param FullFilePath   The full file path on disk for the file saved. @param MD5Hash        The MD5 checksum for the file.
- L27 _delegate_ `DECLARE_EVENT_OneParam(IChunkHarvester, FOnManifestLoaded, const IBuildManifest& );` — Declares an event type exposed to this class when the manifest has been loaded, providing the result. @param Manifest        The loaded manifest.
- L52 _typedef_ `typedef TSharedPtr<IChunkHarvester> IChunkHarvesterPtr;` (scope `BuildPatchServices`)
- L53 _typedef_ `typedef TSharedRef<IChunkHarvester> IChunkHarvesterRef;` (scope `BuildPatchServices`)

### `Source/Runtime/Online/BuildPatchServices/Public/Interfaces/IDirectoryChunker.h` (Public)


#### class `BuildPatchServices::IDirectoryChunker`  
`class IDirectoryChunker`  
_L11-92_
- L14 _public function_ `virtual ~IDirectoryChunker()`
- L20 _public prototype_ `DECLARE_EVENT_OneParam(IDirectoryChunker, FOnBuildFilesEnumerated, const TArray<FString>& ) DECLARE_EVENT_TwoParams(IDirectoryChunker, FOnChunkFileWritten, const FString& , const FMD5Hash& );` — Declares an event type exposed on this class for when the files from the build root have been enumerated. @param BuildFiles     The files enumerated for chunking.
- L34 _public prototype_ `DECLARE_EVENT_OneParam(IDirectoryChunker, FOnChunkMatch, const FGuid& );` — Declares an event type exposed to this class when a chunk has been matched with the already existing one. @param ChunkGuid        The unique identifier of the chunk.
- L40 _public prototype_ `DECLARE_EVENT_OneParam(IDirectoryChunker, FOnManifestGenerated, const IBuildManifest& );` — Declares an event type exposed on this class for when the manifest has been finalized. @param AppManifest		The ref to resulted manifest.
- L49 _public prototype_ `DECLARE_EVENT_ThreeParams(IDirectoryChunker, FOnManifestFileWritten, const FString& , const FMD5Hash& , const FSHAHash& );` — Declares an event type exposed on this class for when the manifest has been saved to the cloud directory. The event offers two types of hash of the file. @param FullFilePath   The full file path on disk for the file saved. @param MD5Hash        The MD5 checksum for the file. @param SHA1Hash       The SHA1 checksum for the file.
- L54 _public prototype_ `virtual FOnBuildFilesEnumerated& OnBuildFilesEnumerated() = 0;` — @return a delegate that will broadcast when the files from the build root have been enumerated.
- L59 _public prototype_ `virtual FOnChunkFileWritten& OnChunkFileWritten() = 0;` — @return a delegate that will broadcast when a chunk was written to the cloud directory.
- L64 _public prototype_ `virtual FOnChunkMatch& OnChunkMatch() = 0;` — @return a delegate that will broadcast when a chunk was matched with an already existing one.
- L69 _public prototype_ `virtual FOnManifestGenerated& OnManifestGenerated() = 0;` — @return a delegate that will broadcast when the manifest file was finilazed.
- L74 _public prototype_ `virtual FOnManifestGenerated& OnManifestGeneratedDecrypted() = 0;` — @return a delegate that will broadcast after the manifest has been saved, and so could be decrypted.
- L79 _public prototype_ `virtual FOnManifestFileWritten& OnManifestFileWritten() = 0;` — @return a delegate that will broadcast when the manifest file was written to the cloud directory.
- L86 _public prototype_ `virtual bool Run() = 0;` — Processes the directory to create chunks for new data and produce a manifest, saved to the cloud directory. NOTE: This function is blocking and will not return until finished. @return true if successful.
- L91 _public prototype_ `virtual void Abort() = 0;` — Signal to the process that it should abort.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace BuildPatchServices`
- L20 _delegate_ `DECLARE_EVENT_OneParam(IDirectoryChunker, FOnBuildFilesEnumerated, const TArray<FString>& ) DECLARE_EVENT_TwoParams(IDirectoryChunker, FOnChunkFileWritten, const FString& , const FMD5Hash& );` — Declares an event type exposed on this class for when the files from the build root have been enumerated. @param BuildFiles     The files enumerated for chunking.
- L28 _delegate_ `DECLARE_EVENT_TwoParams(IDirectoryChunker, FOnChunkFileWritten, const FString& , const FMD5Hash& );` — Declares an event type exposed on this class for when data files have been saved to the cloud directory. The event offers an MD5 hash of the file. @param FullFilePath   The full file path on disk for the file saved. @param MD5Hash        The MD5 checksum for the file.
- L34 _delegate_ `DECLARE_EVENT_OneParam(IDirectoryChunker, FOnChunkMatch, const FGuid& );` — Declares an event type exposed to this class when a chunk has been matched with the already existing one. @param ChunkGuid        The unique identifier of the chunk.
- L40 _delegate_ `DECLARE_EVENT_OneParam(IDirectoryChunker, FOnManifestGenerated, const IBuildManifest& );` — Declares an event type exposed on this class for when the manifest has been finalized. @param AppManifest		The ref to resulted manifest.
- L49 _delegate_ `DECLARE_EVENT_ThreeParams(IDirectoryChunker, FOnManifestFileWritten, const FString& , const FMD5Hash& , const FSHAHash& );` — Declares an event type exposed on this class for when the manifest has been saved to the cloud directory. The event offers two types of hash of the file. @param FullFilePath   The full file path on disk for the file saved. @param MD5Hash        The MD5 checksum for the file. @param SHA1Hash       The SHA1 checksum for the file.
- L94 _typedef_ `typedef TSharedPtr<IDirectoryChunker> IDirectoryChunkerPtr;` (scope `BuildPatchServices`)
- L95 _typedef_ `typedef TSharedRef<IDirectoryChunker> IDirectoryChunkerRef;` (scope `BuildPatchServices`)

### `Source/Runtime/Online/BuildPatchServices/Public/Interfaces/IPatchDataEnumeration.h` (Public)


#### class `BuildPatchServices::IPatchDataEnumeration`  
`class IPatchDataEnumeration`  
_L8-27_
- L11 _public prototype_ `virtual ~IPatchDataEnumeration() = default;`
- L18 _public prototype_ `virtual bool Run() = 0;` — Enumerates the data files used and outputs them to the OutputFile specified in the configuration NOTE: THIS function is blocking and will not return until finished. @return Success
- L26 _public prototype_ `virtual bool Run(TArray<FString>& OutFiles) = 0;` — Enumerates the data files used and outputs them into the array provided NOTE: THIS function is blocking and will not return until finished. @param OutFiles		OUT Array of enumerated files @return Success

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace BuildPatchServices`
- L29 _typedef_ `typedef TSharedPtr<IPatchDataEnumeration> IPatchDataEnumerationPtr;` (scope `BuildPatchServices`)
- L30 _typedef_ `typedef TSharedRef<IPatchDataEnumeration> IPatchDataEnumerationRef;` (scope `BuildPatchServices`)
