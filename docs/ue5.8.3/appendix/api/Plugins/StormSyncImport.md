# Plugins / StormSyncImport

- module root: `Plugins/VirtualProduction/StormSync/Source/StormSyncImport`
- headers: 6; symbols: 54
- symbol kinds: class=5, delegate=1, function=2, member=11, prototype=34, struct=1
- PrivateDependencyModuleNames: Core, CoreUObject, EditorFramework, Engine, MessageLog, RenderCore, Slate, SlateCore, SourceControl, StormSyncCore, StormSyncEditor, StormSyncTransportCore, UnrealEd

### `Plugins/VirtualProduction/StormSync/Source/StormSyncImport/Private/StormSyncImportLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogStormSyncImport, Display, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogStormSyncImport, Display, All);`

### `Plugins/VirtualProduction/StormSync/Source/StormSyncImport/Private/Subsystems/StormSyncImportSubsystem.h` (Private)


#### struct `FStormSyncEditorFileReport`  
`struct FStormSyncEditorFileReport`  
_L17-29_
- desc: Holds information about extraction process for a given file
- L20 _public member_ `bool bSuccess = true;` — Whether the extraction was successful or not
- L23 _public member_ `FName PackageName;` — Original package name
- L26 _public member_ `FString DestFilepath;` — Fully qualified path we tried to extract to
- L28 _public prototype_ `FStormSyncEditorFileReport() = default;`

#### class `UStormSyncImportSubsystem`  
`class UStormSyncImportSubsystem final : public UEngineSubsystem`  
_L39-184_
- reflection: `UCLASS()`
- inherits: `UEngineSubsystem`
- desc: UStormSyncImportSubsystem Subsystem for importing assets in the editor extracted from a local exported storm sync buffer, or coming from a network request. Contains utility functions and callbacks for hooking into importing.
- L45 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L46 _public prototype_ `virtual void Deinitialize() override;`
- L50 _public prototype_ `static UStormSyncImportSubsystem& Get();` — Static Convenience method to return storm sync import subsystem
- L59 _public prototype_ `bool EnqueueImportTask(const TSharedPtr<IStormSyncImportSubsystemTask>& InImportTask, const UWorld* InWorld);` — Enqueue an import task (and handle on next tick) only if no pending existing task already exist @param InImportTask Task to enqueue @param InWorld World to get the timer manager from @return true if the task was added, false otherwise.
- L71 _public prototype_ `static bool PerformFileImport(const FString& InFilename);` — Takes an absolute filename (a storm sync pak) and begins extraction process Comparison between file coming from buffer and current file state in local file system is done to figure out the list of files that needs to be extracted and updated in this editor instance. @param InFilename Absolute path name for the storm sync archive to import @return Operation status, true if successful
- L84 _public prototype_ `static bool PerformBufferImport(const FStormSyncPackageDescriptor& InPackageDescriptor, const FStormSyncArchivePtr& InArchive);` — Takes a raw buffer (a storm sync pak) and begins extraction process Comparison between file coming from buffer and current file state in local file system is done to figure out the list of files that needs to be extracted and updated in this editor instance. @param InPackageDescriptor The package descriptor for this buffer extraction. Only used for UI message logs. @param InBuffer Raw buffer we'd like to extract files from to local project @return Operation status, true if successful
- L99 _public prototype_ `static bool PerformImport(const FStormSyncPackageDescriptor& InPackageDescriptor, const FStormSyncArchivePtr& InArchive, bool bShowWizard = false, bool bDryRun = false);` — Takes a raw buffer (a storm sync pak) and begins extraction process Comparison between file coming from buffer and current file state in local file system is done to figure out the list of files that needs to be extracted and updated in this editor instance. @param InPackageDescriptor The package descriptor for this buffer extraction. Only used for UI message logs. @param InArchive Source archive to be parsed to extract content @param bShowWizard Whether or not to show the import wizard @param bDryRun Whether we should proceed to extraction or simply log to console buffer content @return Operation status, true if successful
- L108 _private prototype_ `static bool ParsePak(const FStormSyncArchivePtr& InArchive, TArray<FStormSyncImportFileInfo>& OutFileInfos);` — Parse the buffer to extract all the file information (but skip content) @param InArchive Source archive of the pak @param OutFileInfos File info in the pak. @return true if parsing was successful.
- L112 _private member_ `static constexpr const TCHAR* LogName = TEXT("Sto` — The name of the message output log we will send messages to
- L114 _private member_ `FTSTicker::FDelegateHandle NextTickHandler;`
- L117 _private member_ `TQueue<TSharedPtr<IStormSyncImportSubsystemTask>> PendingTasks;` — Tasks waiting to be run next tick
- L120 _private member_ `TArray<FString> ClosedPackageNames;` — Store closed assets to reopen during extraction process
- L123 _private member_ `TArray<FStormSyncEditorFileReport> ExtractedFileReports;` — Store extraction process data
- L126 _private prototype_ `bool HandleNextTick(float InDeltaTime);` — Run deferred logic waiting to be run next tick
- L134 _private prototype_ `static bool ShouldFileBeImported(FStormSyncImportFileInfo& InFileInfo);` — Checks local project file for diff against provided file info and dest path. If a change is detected (either missing locally or mismatched file size / hash), OutFilesToImport is filled with a new file info indicating that the file needs an import.
- L137 _private prototype_ `void HandlePakPreExtract(const FStormSyncPackageDescriptor& InPackageDescriptor, int32 FileCount);` — Event handler for core delegate when a pak extraction starts
- L140 _private prototype_ `void HandlePakPostExtract(const FStormSyncPackageDescriptor& InPackageDescriptor, int32 FileCount) const;` — Event handler for core delegate when a pak extraction is ended
- L143 _private prototype_ `void HandleExistingAssetsPreExtract(TConstArrayView<const FStormSyncImportFileInfo*> InExistingFiles, bool bInShowPrompt);` — Event handler for existing asset checkout prior to extracting the new overwriting assets
- L146 _private prototype_ `bool HandleNewAssetsPostExtract(TConstArrayView<const FStormSyncImportFileInfo*> InNewFiles, bool bInShowPrompt);` — Event handler for auto-adding new assets post extracting them
- L149 _private prototype_ `bool HandlePakAssetPreExtract(const FStormSyncImportFileInfo& InFileInfo);` — Event handler for when a file is about to be extracted from an incoming pak
- L152 _private prototype_ `void HandlePakAssetPostExtract(const FStormSyncImportFileInfo& InFileInfo, bool bInFileWritten);` — Event handler for when a file has been extracted from an incoming pak
- L155 _private prototype_ `static void CloseEditors(const TArray<FAssetData>& InAssets, TArray<FAssetData>& OutClosedAssets);` — Checks if given asset is currently being edited, and if so, closes the editor (required prior to file deletion)
- L158 _private prototype_ `static void OpenClosedEditors(const TArray<FString>& ClosedPackageNames);` — Takes a list of package names to ask the Asset Editor subsystem to open
- L168 _private prototype_ `static bool DeleteAssets(const TArray<FAssetData>& AssetsToDelete, bool bShowConfirmation = false);` — Our own custom version of ObjectTools::DeleteAssets We want to force delete the file, to allow assets with on disk references (for things like Textures in a Motion Design asset) to be properly overwritten, if referenced in memory, opened in editor etc. ObjectTools::DeleteAssets will only succeed if the AssetDeleteModel doesn't have on disk references (see CanDelete / CanForceDelete)
- L171 _private prototype_ `static int32 MakePackagesWriteable(TConstArrayView<UPackage*> InPackages);` — Makes the given packages writeable. Should only be used if Source Control is disabled. Returns number of packages that succeeded
- L174 _private prototype_ `static bool IsAssetCurrentlyBeingEdited(const TSharedPtr<IToolkit>& InAssetEditor, const UObject* InAsset);` — Checks if given UObject asset is currently being edited by an Asset Editor (is it opened in editor right now?)
- L177 _private prototype_ `static bool WriteFile(const FString& DestFilepath, const uint64& FileSize, uint8* FileBuffer);` — Write file buffer to destination filepath
- L180 _private prototype_ `static void FlushPackageLoading(const FString& InPackageName, bool bInForceBulkDataLoad = true);` — Blocks till all pending package/ linker requests are fulfilled.
- L183 _private prototype_ `static void HotReloadPackages(const TArray<FStormSyncEditorFileReport>& InExtractedFileReports, bool bInInteractiveHotReload);` — Attempts to reload the specified top-level packages.

### `Plugins/VirtualProduction/StormSync/Source/StormSyncImport/Private/Subsystems/StormSyncImportWorldSubsystem.h` (Private)


#### class `UStormSyncImportWorldSubsystem`  
`class UStormSyncImportWorldSubsystem : public UWorldSubsystem`  
_L20-30_
- reflection: `UCLASS()`
- inherits: `UWorldSubsystem`
- L25 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L26 _public prototype_ `virtual void Deinitialize() override;`
- L28 _public prototype_ `void HandleImportFile(const FString& InFilename) const;`
- L29 _public prototype_ `void HandleImportBuffer(const FStormSyncPackageDescriptor& InPackageDescriptor, const FStormSyncArchivePtr& InArchive) const;`

### `Plugins/VirtualProduction/StormSync/Source/StormSyncImport/Private/Tasks/IStormSyncImportTask.h` (Private)


#### class `IStormSyncImportSubsystemTask`  
`class IStormSyncImportSubsystemTask`  
_L6-12_
- desc: Interface for tasks that need delayed execution
- L9 _public prototype_ `virtual ~IStormSyncImportSubsystemTask() = default;`
- L11 _public prototype_ `virtual void Run() = 0;`

### `Plugins/VirtualProduction/StormSync/Source/StormSyncImport/Private/Tasks/StormSyncImportBufferTask.h` (Private)


#### class `FStormSyncImportBufferTask`  
`class FStormSyncImportBufferTask final : public IStormSyncImportSubsystemTask`  
_L10-27_
- inherits: `IStormSyncImportSubsystemTask`
- desc: Import files from Buffer implementation for tasks that need delayed execution
- L13 _public function_ `explicit FStormSyncImportBufferTask(const FStormSyncPackageDescriptor& InPackageDescriptor, const FStormSyncArchivePtr& InArchive) : PackageDescriptor(InPackageDescriptor) , Archive(InArchive)`
- L19 _public prototype_ `virtual void Run() override;`
- L23 _private member_ `FStormSyncPackageDescriptor PackageDescriptor;` — Metadata info about buffer being extracted
- L26 _private member_ `FStormSyncArchivePtr Archive;` — Archive to import

### `Plugins/VirtualProduction/StormSync/Source/StormSyncImport/Private/Tasks/StormSyncImportFilesTask.h` (Private)


#### class `FStormSyncImportFilesTask`  
`class FStormSyncImportFilesTask final : public IStormSyncImportSubsystemTask`  
_L9-21_
- inherits: `IStormSyncImportSubsystemTask`
- desc: Import files from local exported buffer implementation for tasks that need delayed execution
- L12 _public function_ `explicit FStormSyncImportFilesTask(const FString& InFilename) : Filename(InFilename)`
- L17 _public prototype_ `virtual void Run() override;`
- L20 _private member_ `FString Filename;`
