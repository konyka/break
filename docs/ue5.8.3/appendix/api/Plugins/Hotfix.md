# Plugins / Hotfix

- module root: `Plugins/Online/OnlineFramework/Source/Hotfix`
- headers: 4; symbols: 336
- symbol kinds: class=4, delegate=10, enum=5, enumerator=28, function=34, macro=3, member=100, prototype=135, struct=7, typedef=10
- PrivateDependencyModuleNames: AssetRegistry, Core, CoreUObject, Engine, Json, MoviePlayerProxy, OnlineSubsystemUtils
- PublicDependencyModuleNames: InstallBundleManager, OnlineSubsystem, PatchCheck

### `Plugins/Online/OnlineFramework/Source/Hotfix/Public/AssetHotfixRegistry.h` (Public)


#### enum `EHotfixOperation`  
`enum class EHotfixOperation : uint8`  
_L19-25_
- reflection: `UENUM(MinimalAPI)`
- L21 _public enumerator_ `RowUpdate`
- L22 _public enumerator_ `AddRow`
- L23 _public enumerator_ `TableUpdate`
- L24 _public enumerator_ `CurveUpdate`

#### struct `FPendingAssetHotfix`  
`struct FPendingAssetHotfix`  
_L27-48_
- L29 _public member_ `FName AssetClassName;`
- L30 _public member_ `FName RowName;`
- L31 _public member_ `FString ColumnOrData;`
- L32 _public member_ `FString Value;`
- L33 _public member_ `FName SourceTag;`
- L34 _public member_ `EHotfixOperation Operation = EHotfixOperation::RowUpdate;`
- L40 _public function_ `bool operator==(const FPendingAssetHotfix& Other) const` — Value is intentionally excluded from comparison. Two hotfix entries that target the same asset, row, and column represent the same logical hotfix regardless of the value being applied. This allows later entries to replace earlier ones when deduplicating via TArray::AddUnique.

#### struct `FPendingAssetHotfixEntries`  
`struct FPendingAssetHotfixEntries`  
_L50-53_
- L52 _public member_ `TArray<FPendingAssetHotfix> Entries;`

#### struct `FAssetHotfixRegistry`  
`struct FAssetHotfixRegistry`  
_L55-77_
- L57 _public prototype_ `void Reset();`
- L58 _public prototype_ `TArray<FName> ParseAndStoreHotfixEntries(FName SourceTag, const FConfigSectionMap& AssetHotfixSection);`
- L59 _public prototype_ `TArray<FName> ParseAndStoreFromRawIniData(FName SourceTag, const FString& IniData);`
- L60 _public prototype_ `const FPendingAssetHotfixEntries* FindHotfixesForAsset(FName AssetPath) const;`
- L61 _public prototype_ `void StoreHotfixEntry(FName AssetPath, FPendingAssetHotfix Hotfix);`
- L62 _public prototype_ `bool RemoveEntriesFromSource(FName SourceTag);`
- L64 _public prototype_ `TArray<FName> GetAllPendingPaths() const;`
- L66 _public prototype_ `bool TryApplyHotfixes( UObject* Asset, UOnlineHotfixManager* HotfixManager, bool& bOutEncounteredErrors, TSet<class UDataTable*>* ChangedDataTables = nullptr, TSet<class UCurveTable*>* ChangedCurveTables = nullptr) const;`
- L73 _public function_ `bool HasPendingHotfixes() const`
- L76 _private member_ `TMap<FName, FPendingAssetHotfixEntries> PendingAssetHotfixes;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API HOTFIX_API`

### `Plugins/Online/OnlineFramework/Source/Hotfix/Public/HotfixModule.h` (Public)


#### class `FHotfixModule`  
`class FHotfixModule : public IModuleInterface`  
_L10-17_
- inherits: `IModuleInterface`
- desc: Module for Hotfix base implementation
- L15 _private prototype_ `virtual void StartupModule() override;` — IModuleInterface
- L16 _private prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Online/OnlineFramework/Source/Hotfix/Public/OnlineHotfixManager.h` (Public)


#### enum `EHotfixResult`  
`enum class EHotfixResult : uint8`  
_L20-32_
- reflection: `UENUM()`
- L23 _public enumerator_ `Failed` — Failed to apply the hotfix
- L25 _public enumerator_ `Success` — Hotfix succeeded and is ready to go
- L27 _public enumerator_ `SuccessNoChange` — Hotfix process succeeded but there were no changes applied
- L29 _public enumerator_ `SuccessNeedsReload` — Hotfix succeeded and requires the current level to be reloaded to take effect
- L31 _public enumerator_ `SuccessNeedsRelaunch` — Hotfix succeeded and requires the process restarted to take effect

#### class `UOnlineHotfixManager`  
`class UOnlineHotfixManager : public UObject`  
_L93-549_
- reflection: `UCLASS(MinimalAPI, Config=Engine)`
- inherits: `UObject`
- desc: This class manages the downloading and application of hotfix data Hotfix data is a set of non-executable files downloaded and applied to the game. The base implementation knows how to handle INI, PAK, and locres files. NOTE: Each INI/PAK file must be prefixed by the platform name they are targeted at
- L101 _public member_ `static constexpr bool bAlwaysReapplyHotfixes = false;`
- L108 _protected member_ `IOnlineTitleFilePtr OnlineTitleFile;` — The online interface to use for downloading the hotfix files
- L111 _protected member_ `FOnEnumerateFilesCompleteDelegate OnEnumerateFilesCompleteDelegate;` — Callbacks for when the title file interface is done
- L112 _protected member_ `FOnReadFileProgressDelegate OnReadFileProgressDelegate;`
- L113 _protected member_ `FOnReadFileCompleteDelegate OnReadFileCompleteDelegate;`
- L114 _protected member_ `FDelegateHandle OnEnumerateFilesCompleteDelegateHandle;`
- L115 _protected member_ `FDelegateHandle OnEnumerateFilesForAvailabilityCompleteDelegateHandle;`
- L116 _protected member_ `FDelegateHandle OnReadFileProgressDelegateHandle;`
- L117 _protected member_ `FDelegateHandle OnReadFileCompleteDelegateHandle;`
- L120 _protected member_ `FDelegateHandle OnHotfixableAssetLoadedHandle;` — Callback from FCoreUObjectDelegates when hotfixable asset is loaded
- L127 _protected prototype_ `DEFINE_ONLINE_DELEGATE_ONE_PARAM(OnHotfixComplete, EHotfixResult);` — Delegate fired when the hotfix process has completed @param status of the hotfix process
- L132 _protected prototype_ `DEFINE_ONLINE_DELEGATE_FOUR_PARAM(OnHotfixProgress, uint32, uint32, uint64, uint64);` — Delegate fired as the hotfix files are read
- L137 _protected prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnHotfixProcessedFile, const FString&, const FString&);` — Delegate fired for each new/updated file after it is applied
- L142 _protected prototype_ `DEFINE_ONLINE_DELEGATE_ONE_PARAM(OnHotfixRemovedFile, const FString&);` — Delegate fired for each removed file
- L147 _protected prototype_ `DEFINE_ONLINE_DELEGATE_TWO_PARAM(OnHotfixUpdatedFile, const FString&, const TArray<uint8>&);` — Delegate fired for each added/updated file
- L170 _protected member_ `TMap<FString, FPendingFileDLProgress> PendingHotfixFiles;` — Holds which files are pending download
- L172 _protected member_ `TArray<FCloudFileHeader> HotfixFileList;` — The filtered list of files that are part of the hotfix
- L174 _protected member_ `TArray<FCloudFileHeader> LastHotfixFileList;` — The last set of hotfix files that was applied so we can determine whether we are up to date or not
- L176 _protected member_ `TArray<FCloudFileHeader> ChangedHotfixFileList;` — The set of hotfix files that have changed from the last time we applied them
- L178 _protected member_ `TArray<FCloudFileHeader> RemovedHotfixFileList;` — The set of hotfix files that have been removed from the last time we applied them
- L180 _protected member_ `TArray<FString> MountedPakFiles;` — Holds which files have been mounted for unmounting
- L182 _protected member_ `TArray<FConfigFileBackup> IniBackups;` — Backup copies of INI files that change during hotfixing so they can be undone afterward
- L184 _protected member_ `FString PlatformPrefix;` — Used to match any PAK files for this platform
- L186 _protected member_ `FString ServerPrefix;` — Used to match any server-only hotfixes
- L188 _protected member_ `FString CustomConfigPrefix;` — Used to match any custom config hotfixes
- L190 _protected member_ `FString DefaultPrefix;` — Normally will be "Default" but could be different if we have a debug prefix
- L192 _protected member_ `FString GameContentPath;` — Holds a chunk of string that will be swapped for Game during processing pak files (MyGame/Content/Maps -> /Game/Maps)
- L194 _protected member_ `uint32 TotalFiles;` — Tracks how many files are being processed as part of the hotfix
- L195 _protected member_ `uint32 NumDownloaded;`
- L197 _protected member_ `uint64 TotalBytes;` — Tracks the size of the files being processed as part of the hotfix
- L198 _protected member_ `uint64 NumBytes;`
- L200 _protected member_ `bool bHotfixingInProgress;` — Some title file interfaces aren't re-entrant so handle it ourselves
- L202 _protected member_ `TUniquePtr<FAsyncLoadingFlushContext> AsyncFlushContext;` — Asynchronously flush async loading before starting the hotfixing process.
- L204 _protected member_ `bool bHotfixNeedsMapReload;` — Set to true if any PAK file contains an update to a level that is currently loaded
- L207 _protected member_ `bool bLogMountedPakContents;` — Whether we want to log all of the files that are in a mounted pak file or not
- L213 _protected member_ `uint32 ChangedOrRemovedPakCount;` — If we have removed or changed a currently mounted PAK file, then we'll need to restart the app because there's no simple undo for objects that were loaded and possibly rooted
- L215 _protected member_ `TWeakObjectPtr<UWorld> OwnerWorld;` — Our passed-in World
- L218 _protected member_ `TMap<FName, TArray<TPair<FString, FString>>> DynamicHotfixContents;` — Loaded hotfix contents that were not mapped to any known branch, but might be loaded later. The key used here is a plugin tag + branch name, such as "PluginEngine" for example.
- L220 _protected prototype_ `virtual void Init();`
- L221 _protected prototype_ `virtual void Cleanup();`
- L223 _protected prototype_ `EHotfixResult ApplyHotfix();` — Looks at each file returned via the hotfix and processes them
- L226 _protected function_ `void TriggerHotfixComplete(EHotfixResult HotfixResult)` — `UE_DEPRECATED(5.8, "Renamed to FinalizeHotfixProcess")` — Cleans up and fires the delegate indicating it's done
- L228 _protected prototype_ `void FinalizeHotfixProcess(EHotfixResult HotfixResult);` — Finalizes the hotfix process. Handles asset hotfixing and fires delegates when complete.
- L230 _protected prototype_ `void FilterHotfixFiles();` — Checks each file listed to see if it is a hotfix file to process
- L232 _protected prototype_ `void ReadHotfixFiles();` — Starts the async reading process for the hotfix files
- L234 _protected prototype_ `void UnmountHotfixFiles();` — Unmounts any changed PAK files so they can be re-mounted after downloading
- L236 _protected prototype_ `FConfigFileBackup& BackupIniFile(const FString& IniName, const FConfigFile* ConfigFile);` — Stores off the INI file for restoration later
- L238 _protected prototype_ `void RestoreBackupIniFiles();` — Restores any changed INI files to their default loaded state
- L240 _protected prototype_ `void BuildHotfixFileListDeltas();` — Builds the list of files that are different between two runs of the hotfix process
- L243 _protected prototype_ `void OnEnumerateFilesComplete(bool bWasSuccessful, const FString& ErrorStr);` — Called once the list of hotfix files has been retrieved
- L245 _protected prototype_ `void OnEnumerateFilesForAvailabilityComplete(bool bWasSuccessful, const FString& ErrorStr, FOnHotfixAvailableComplete InCompletionDelegate);` — Called once the list of hotfix files has been retrieved and we only want to see if a hotfix is necessary
- L247 _protected prototype_ `void OnReadFileComplete(bool bWasSuccessful, const FString& FileName);` — Called as files are downloaded to determine when to apply the hotfix data
- L249 _protected prototype_ `void OnReadFileProgress(const FString& FileName, uint64 BytesRead);` — Called as files are downloaded to provide progress notifications
- L252 _protected prototype_ `FConfigFile* GetConfigFile(const FString& IniName);` — @return the config file entry for the ini file name in question
- L253 _protected prototype_ `FConfigBranch* GetBranch(const FString& IniName);`
- L256 _protected prototype_ `FString BuildConfigCacheKey(const FString& IniName);` — @return the config cache key used to associate ini file entries within the config cache
- L258 _protected prototype_ `virtual FString GetStrippedConfigFileName(const FString& IniName);` — @return the config file name after stripping any extra info (platform, debug prefix, etc.)
- L261 _protected prototype_ `const FString GetFriendlyNameFromDLName(const FString& DLName) const;` — @return the human readable name of the file
- L263 _protected prototype_ `virtual void PostInitProperties() override;`
- L264 _protected prototype_ `virtual void BeginDestroy() override;`
- L266 _protected prototype_ `bool IsMapLoaded(const FString& MapName);`
- L269 _protected prototype_ `UWorld* GetWorld() const override;` — @return our current world
- L272 _protected prototype_ `void StopTrackingInvalidHotfixedAssets();` — Stop tracking hotfixed assets marked as garbage
- L275 _protected prototype_ `void HotfixDynamicBranch(const FName& Tag, const FName& Branch, class FConfigModificationTracker* ModificationTracker);` — Hotfix a dynamic config branch that was just loaded
- L278 _protected prototype_ `void RemoveHotfixesFromDynamicBranch(const FName& Tag);` — Remove asset hotfix entries for a plugin whose dynamic config branch is being removed
- L283 _protected function_ `virtual void OnDynamicHotfixesRemoved(FName SourceTag)` — Called after a tag's asset hotfix entries have been removed from the registry.
- L286 _protected prototype_ `void RegisterAssetHotfixEntry(FName AssetPath, FPendingAssetHotfix Hotfix);` — Store a single hotfix entry in the registry. Used by subclasses that build entries outside the INI parse path.
- L289 _protected prototype_ `void ApplyRegisteredHotfixesForAsset(UObject* Asset);` — Apply all registered hotfixes for an already-loaded asset, firing table change notifications.
- L292 _protected prototype_ `static void BroadcastTableChanges(const TSet<class UDataTable*>& ChangedDataTables, const TSet<class UCurveTable*>& ChangedCurveTables);` — Fires HandleDataTableChanged / OnCurveTableChanged for all modified tables.
- L304 _protected prototype_ `bool IsCompatibleHotfixFile(const FString& InFilename, FString& OutFilename);` — Is this hotfix file compatible with the current build If the file has version information it is compared with compatibility If the file has NO version information it is assumed compatible @param InFilename name of the file to check @param OutFilename name of file with version information stripped @return true if file is compatible, false otherwise
- L313 _protected prototype_ `virtual bool ApplyHotfixProcessing(const FCloudFileHeader& FileHeader);` — Called when a file needs custom processing (see above). Override this to provide your own processing methods @param FileHeader - the header information for the file in question @return whether the file was successfully processed
- L322 _protected function_ `virtual bool PreProcessDownloadedFileData(const FCloudFileHeader& FileHeader, TArray<uint8>& FileData) const` — Called prior to reading the file data. @param FileHeader - the header information for the file in question @param FileData - byte data of the hotfix file. Intentionally not const, so the array is modifiable as part of preprocessing. @return whether the file was successfully preprocessed
- L331 _protected prototype_ `virtual bool HotfixIniFile(const FString& FileName, const FString& IniData);` — Override this to change the default INI file handling (merge delta INI changes into the config cache) @param FileName - the name of the INI being merged into the config cache @param IniData - the contents of the INI file (expected to be delta contents not a whole file) @return whether the merging was successful or not
- L341 _protected prototype_ `virtual bool HotfixPakFile(const FCloudFileHeader& FileHeader);` — Override this to change the default PAK file handling: - mount PAK file immediately - Scan for any INI files contained within the PAK file and merge those in @param FileName - the name of the PAK file being mounted @return whether the mounting of the PAK file was successful or not
- L349 _protected prototype_ `virtual bool HotfixPakIniFile(const FString& FileName);` — Override this to change the default INI file handling (merge whole INI files into the config cache) @param FileName - the name of the INI being merged into the config cache @return whether the merging was successful or not
- L356 _protected function_ `virtual FString GetCachedDirectory()` — Override this to change the default caching directory @return the default caching directory
- L362 _protected prototype_ `virtual void OnHotfixableAssetLoaded(UObject* Asset);` — Fired by FCoreUObjectDelegates when a hotfixable asset is loaded
- L365 _protected prototype_ `virtual void OnHotfixAvailablityCheck(const TArray<FCloudFileHeader>& PendingChangedFiles, const TArray<FCloudFileHeader>& PendingRemoveFiles);` — Notify used by CheckAvailability()
- L368 _protected prototype_ `FCloudFileHeader* GetFileHeaderFromDLName(const FString& FileName);` — Finds the header associated with the file name
- L371 _protected prototype_ `void UpdateProgress(uint32 FileCount, uint64 UpdateSize);` — Fires the progress delegate with our updated progress
- L373 _protected function_ `virtual bool ShouldWarnAboutMissingWhenPatchingFromIni(const FString& AssetPath) const`
- L376 _protected prototype_ `virtual void PatchAssetsFromIniFiles();` — Called after any hotfixes are applied to apply last-second changes to certain asset types from .ini file data
- L379 _protected prototype_ `virtual void ParseAssetHotfixes();` — Called instead of PatchAssetsFromIniFiles when hotfix-on-load is enabled
- L382 _protected prototype_ `virtual void ApplyHotfixesToLoadedAssets();` — Called immediately after ParseAssetHotfixes to patch assets already in memory
- L385 _protected prototype_ `void ApplyHotfixesToLoadedAssets(TConstArrayView<FName> AssetPaths);` — Apply registered hotfixes only to the given asset paths.
- L388 _protected prototype_ `virtual void ReloadConfigsFromIniFiles();` — Called after any hotfixes are applied to apply last-second changes to Config properties from .ini file data
- L393 _protected prototype_ `void HotfixRowUpdate( UObject* Asset, const FString& AssetPath, const FString& RowName, const FString& ColumnName, const FString& NewValue, TArray<FString>& ProblemStrings, TSet<class UDataTable*>* ChangedDataTables = nullptr, TSet<class UCurveTable*>* ChangedCurveTables = nullptr, FName SourceTag = NAME_None);` — Used in PatchAssetsFromIniFiles to hotfix only a row in a table. If ChangedTables is not null then HandleDataTableChanged will not be called and the caller should call it on the data tables in ChangedTables when they're ready to
- L407 _protected prototype_ `void HotfixAddRow( UObject* Asset, const FString& AssetPath, const FString& JsonData, TArray<FString>& ProblemStrings, TSet<class UDataTable*>* ChangedDataTables = nullptr);` — Used in PatchAssetsFromIniFiles to hotfix a new row in a table. If ChangedTables is not null then HandleDataTableChanged will not be called and the caller should call it on the data tables in ChangedTables when they're ready to
- L415 _protected function_ `virtual void OnHotfixTableAddRow(UObject& Asset, const FName RowName)` — Called after adding table row by HotfixAddRow()
- L418 _protected prototype_ `void HotfixTableUpdate(UObject* Asset, const FString& AssetPath, const FString& JsonData, TArray<FString>& ProblemStrings);` — Used in PatchAssetsFromIniFiles to hotfix an entire table.
- L425 _protected function_ `virtual void OnHotfixTableValueInt64(UObject& Asset, const FString& RowName, const FString& ColumnName, const int64& OldValue, const int64& NewValue)` — `UE_DEPRECATED(5.8, "Override OnHotfixTableValueInt64WithSource instead.")` — Called after modifying table values by HotfixRowUpdate(). @deprecated Override the WithSource variants instead.
- L427 _protected function_ `virtual void OnHotfixTableValueDouble(UObject& Asset, const FString& RowName, const FString& ColumnName, const double& OldValue, const double& NewValue)` — `UE_DEPRECATED(5.8, "Override OnHotfixTableValueDoubleWithSource instead.")`
- L429 _protected function_ `virtual void OnHotfixTableValueFloat(UObject& Asset, const FString& RowName, const FString& ColumnName, const float& OldValue, const float& NewValue)` — `UE_DEPRECATED(5.8, "Override OnHotfixTableValueFloatWithSource instead.")`
- L431 _protected function_ `virtual void OnHotfixTableValueString(UObject& Asset, const FString& RowName, const FString& ColumnName, const FString& OldValue, const FString& NewValue)` — `UE_DEPRECATED(5.8, "Override OnHotfixTableValueStringWithSource instead.")`
- L433 _protected function_ `virtual void OnHotfixTableValueName(UObject& Asset, const FString& RowName, const FString& ColumnName, const FName& OldValue, const FName& NewValue)` — `UE_DEPRECATED(5.8, "Override OnHotfixTableValueNameWithSource instead.")`
- L435 _protected function_ `virtual void OnHotfixTableValueObject(UObject& Asset, const FString& RowName, const FString& ColumnName, const UObject* OldValue, const UObject* NewValue)` — `UE_DEPRECATED(5.8, "Override OnHotfixTableValueObjectWithSource instead.")`
- L437 _protected function_ `virtual void OnHotfixTableValueSoftObject(UObject& Asset, const FString& RowName, const FString& ColumnName, const FSoftObjectPtr& OldValue, const FSoftObjectPtr& NewValue)` — `UE_DEPRECATED(5.8, "Override OnHotfixTableValueSoftObjectWithSource instead.")`
- L441 _protected function_ `virtual void OnHotfixTableValueInt64WithSource(UObject& Asset, const FString& RowName, const FString& ColumnName, const int64& OldValue, const int64& NewValue, FName SourceTag)` — Called when a table row value is patched, with the source tag identifying which hotfix applied the change. Override to track or respond to patches per source.
- L442 _protected function_ `virtual void OnHotfixTableValueDoubleWithSource(UObject& Asset, const FString& RowName, const FString& ColumnName, const double& OldValue, const double& NewValue, FName SourceTag)`
- L443 _protected function_ `virtual void OnHotfixTableValueFloatWithSource(UObject& Asset, const FString& RowName, const FString& ColumnName, const float& OldValue, const float& NewValue, FName SourceTag)`
- L444 _protected function_ `virtual void OnHotfixTableValueStringWithSource(UObject& Asset, const FString& RowName, const FString& ColumnName, const FString& OldValue, const FString& NewValue, FName SourceTag)`
- L445 _protected function_ `virtual void OnHotfixTableValueNameWithSource(UObject& Asset, const FString& RowName, const FString& ColumnName, const FName& OldValue, const FName& NewValue, FName SourceTag)`
- L446 _protected function_ `virtual void OnHotfixTableValueObjectWithSource(UObject& Asset, const FString& RowName, const FString& ColumnName, const UObject* OldValue, const UObject* NewValue, FName SourceTag)`
- L447 _protected function_ `virtual void OnHotfixTableValueSoftObjectWithSource(UObject& Asset, const FString& RowName, const FString& ColumnName, const FSoftObjectPtr& OldValue, const FSoftObjectPtr& NewValue, FName SourceTag)`
- L450 _protected prototype_ `virtual bool ShouldPerformHotfix();`
- L453 _protected prototype_ `virtual FString GetDedicatedServerPrefix() const;` — Allow the application to override the dedicated server filename prefix.
- L456 _protected prototype_ `virtual bool ShouldHotfixAsset(const FString& AssetPath) const;` — Allow child classes to determine if specific assets should be hotfixed or not
- L460 _protected prototype_ `void ApplyLocalTestHotfix(FString Filename);` — Test function that applies a local file as if it were a hotfix.
- L464 _public prototype_ `UOnlineHotfixManager();`
- L465 _public prototype_ `UOnlineHotfixManager(FVTableHelper& Helper);`
- L466 _public prototype_ `virtual ~UOnlineHotfixManager();`
- L476 _public prototype_ `virtual bool WantsHotfixProcessing(const FCloudFileHeader& FileHeader);` — Override this method to look at the file information for any game specific hotfix processing NOTE: Make sure to call Super to get default handling of files @param FileHeader - the information about the file to determine if it needs custom processing @return true if the file needs some kind of processing, false to have hotfixing ignore the file
- L480 _public member_ `FString OSSName;` — `UPROPERTY(Config)` — Tells the hotfix manager which OSS to use. Uses the default if empty
- L484 _public member_ `FString HotfixManagerClassName;` — `UPROPERTY(Config)` — Tells the factory method which class to contruct
- L488 _public member_ `FString DebugPrefix;` — `UPROPERTY(Config)` — Used to prevent development work from interfering with playtests, etc.
- L492 _public member_ `TArray<FSoftClassPath> HotfixableAssetClasses;` — `UPROPERTY(Config)` — List of classes that can be hotfixed with [AssetHotfix] from ini files
- L496 _public prototype_ `virtual void StartHotfixProcess();` — `UFUNCTION(BlueprintCallable, Category="Hotfix")` — Starts the fetching of hotfix data from the OnlineTitleFileInterface that is registered for this game
- L499 _public prototype_ `virtual void OnHotfixProcessSkipped();` — Called when the hotfix process is skipped entirely.
- L504 _public member_ `TArray<TObjectPtr<UObject>> AssetsHotfixedFromIniFiles;` — `UPROPERTY(Transient)` — Array of objects that we're forcing to remain resident because we've applied live hotfixes and won't get an opportunity to reapply changes if the object is evicted from memory.
- L511 _public prototype_ `virtual void CheckAvailability(FOnHotfixAvailableComplete& InCompletionDelegate);` — Check for available hotfix files (but do not apply them) @param InCompletionDelegate delegate to fire when the check is complete
- L513 _public prototype_ `static UClass* GetConfiguredHotfixManagerClass();`
- L516 _public prototype_ `static UOnlineHotfixManager* Get(UWorld* World);` — Factory method that returns the configured hotfix manager
- L518 _public prototype_ `static void ReloadObjectsAffectedByConfigFile(const FString& IniDataFileName, const FString& IniData, const FString& ConfigFilename, TArray<FString>& ReloadedClassesPathNames, bool bUseLoadConfig);`
- L521 _public function_ `bool IsHotfixOnLoadEnabled() const` — Whether hotfix-on-load is active (delegates bound, asset classes registered).
- L525 _private member_ `TArray<TObjectPtr<UClass>> ResolvedHotfixableAssetClasses;` — `UPROPERTY(Transient)`
- L527 _private member_ `FAssetHotfixRegistry AssetHotfixRegistry;`
- L531 _private prototype_ `void ConfigureHotfixOnLoad();` — Evaluates the hotfix-on-load CVar and configures if enabled. Latched to run once.
- L534 _private prototype_ `void TeardownHotfixOnLoad();` — Tears down hotfix-on-load (unregisters asset classes, unbinds delegate). Idempotent.
- L537 _private member_ `bool bConfiguredHotfixOnLoad = false;` — True after ConfigureHotfixOnLoad() has evaluated the CVar. Prevents re-evaluation on subsequent hotfix passes.
- L540 _private member_ `bool bHotfixOnLoadEnabled = false;` — True when hotfix-on-load is active (delegates bound, asset classes registered).
- L543 _private member_ `bool bHasAppliedHotfixesToLoadedAssets = false;` — True after the first ApplyHotfixesToLoadedAssets() pass
- L547 _private prototype_ `void ValidateHotfixableAssetClasses(TConstArrayView<FName> AssetPaths);` — Validates that hotfix asset paths resolve to registered hotfixable classes in the asset registry.

#### struct `UOnlineHotfixManager::FPendingFileDLProgress`  
`struct FPendingFileDLProgress`  
_L149-157_
- L151 _public member_ `uint64 Progress;`
- L153 _public function_ `FPendingFileDLProgress()`

#### struct `UOnlineHotfixManager::FConfigFileBackup`  
`struct FConfigFileBackup`  
_L159-167_
- L162 _public member_ `FString IniName;` — Name of the ini file backed up
- L164 _public member_ `FConfigFile ConfigData;` — Previous ini data backed up
- L166 _public member_ `TArray<FString> ClassesReloaded;` — UClasses reloaded as a result of the current ini

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API HOTFIX_API`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogHotfixManager, Display, All);`
- L39 _delegate_ `DECLARE_DELEGATE_OneParam(FOnHotfixAvailableComplete, EHotfixResult);` — Delegate fired when a check for hotfix files (but not application) completes @param EHotfixResult status on what happened
- L39 _prototype_ `DECLARE_DELEGATE_OneParam(FOnHotfixAvailableComplete, EHotfixResult);` — Delegate fired when a check for hotfix files (but not application) completes @param EHotfixResult status on what happened
- L46 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnHotfixComplete, EHotfixResult);` — Delegate fired when the hotfix process has completed @param EHotfixResult status on what happened
- L46 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnHotfixComplete, EHotfixResult);` — Delegate fired when the hotfix process has completed @param EHotfixResult status on what happened
- L47 _typedef_ `typedef FOnHotfixComplete::FDelegate FOnHotfixCompleteDelegate;`
- L57 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnHotfixProgress, uint32, uint32, uint64, uint64);` — Delegate fired as progress of hotfix file reading happens @param NumDownloaded the number of files downloaded so far @param TotalFiles the total number of files part of the hotfix @param NumBytes the number of bytes processed so far @param TotalBytes the total size of the hotfix data
- L57 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnHotfixProgress, uint32, uint32, uint64, uint64);` — Delegate fired as progress of hotfix file reading happens @param NumDownloaded the number of files downloaded so far @param TotalFiles the total number of files part of the hotfix @param NumBytes the number of bytes processed so far @param TotalBytes the total size of the hotfix data
- L58 _typedef_ `typedef FOnHotfixProgress::FDelegate FOnHotfixProgressDelegate;`
- L66 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHotfixProcessedFile, const FString&, const FString&);` — Delegate fired for each new/updated file after it is applied @param FriendlyName the human readable version of the file name (DefaultEngine.ini) @param CachedFileName the full path to the file on disk
- L66 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHotfixProcessedFile, const FString&, const FString&);` — Delegate fired for each new/updated file after it is applied @param FriendlyName the human readable version of the file name (DefaultEngine.ini) @param CachedFileName the full path to the file on disk
- L67 _typedef_ `typedef FOnHotfixProcessedFile::FDelegate FOnHotfixProcessedFileDelegate;`
- L74 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnHotfixRemovedFile, const FString&);` — Delegate fired for each removed file @param FriendlyName the human readable version of the file name (DefaultEngine.ini)
- L74 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnHotfixRemovedFile, const FString&);` — Delegate fired for each removed file @param FriendlyName the human readable version of the file name (DefaultEngine.ini)
- L75 _typedef_ `typedef FOnHotfixRemovedFile::FDelegate FOnHotfixRemovedFileDelegate;`
- L83 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHotfixUpdatedFile, const FString&, const TArray<uint8>&);` — Delegate fired for each added/updated file @param FriendlyName the human readable version of the file name (DefaultEngine.ini) @param FileContents the preprocessed contents of the file.
- L83 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHotfixUpdatedFile, const FString&, const TArray<uint8>&);` — Delegate fired for each added/updated file @param FriendlyName the human readable version of the file name (DefaultEngine.ini) @param FileContents the preprocessed contents of the file.
- L84 _typedef_ `typedef FOnHotfixUpdatedFile::FDelegate FOnHotfixUpdatedFileDelegate;`

### `Plugins/Online/OnlineFramework/Source/Hotfix/Public/UpdateManager.h` (Public)


#### enum `EUpdateState`  
`enum class EUpdateState : uint8`  
_L24-40_
- reflection: `UENUM(BlueprintType)`
- desc: Various states the update manager flows through as it checks for patches/hotfixes
- L27 _public enumerator_ `UpdateIdle` — No updates in progress
- L29 _public enumerator_ `UpdatePending` — An update is waiting to be triggered at the right time
- L31 _public enumerator_ `CheckingForPatch` — Checking for an available patch
- L33 _public enumerator_ `CheckingForHotfix` — Checking with hotfix for available updates
- L35 _public enumerator_ `WaitingOnInitialLoad` — Waiting for the async loading / preloading to complete
- L37 _public enumerator_ `InitialLoadComplete` — Preloading complete
- L39 _public enumerator_ `UpdateComplete` — Last update check completed successfully

#### enum `EUpdateCompletionStatus`  
`enum class EUpdateCompletionStatus : uint8`  
_L46-66_
- reflection: `UENUM(BlueprintType)`
- desc: Possible outcomes at the end of an update check
- L49 _public enumerator_ `UpdateUnknown` — Unknown update completion
- L51 _public enumerator_ `UpdateSuccess` — Update completed successfully, some changes applied
- L53 _public enumerator_ `UpdateSuccess_NoChange` — Update completed successfully, no changed needed
- L55 _public enumerator_ `UpdateSuccess_NeedsReload` — Update completed successfully, need to reload the map
- L57 _public enumerator_ `UpdateSuccess_NeedsRelaunch` — Update completed successfully, need to relaunch the game
- L59 _public enumerator_ `UpdateSuccess_NeedsPatch` — Update completed successfully, a patch must be download to continue
- L61 _public enumerator_ `UpdateFailure_PatchCheck` — Update failed in the patch check
- L63 _public enumerator_ `UpdateFailure_HotfixCheck` — Update failed in the hotfix check
- L65 _public enumerator_ `UpdateFailure_NotLoggedIn` — Update failed due to not being logged in

#### struct `FUpdateContextDefinition`  
`struct FUpdateContextDefinition`  
_L112-131_
- reflection: `USTRUCT()`
- desc: Update context definition loaded from config. Defines the behavior to use during an update check.
- L118 _public member_ `FString Name;` — `UPROPERTY(Config)` — The name used to lookup the context definition.
- L121 _public member_ `bool bEnabled = true;` — `UPROPERTY(Config)` — Whether to perform any checks.
- L124 _public member_ `bool bCheckAvailabilityOnly = false;` — `UPROPERTY(Config)` — Whether to perform an update, or to only check for the presence of an update.
- L127 _public member_ `bool bPatchCheckEnabled = true;` — `UPROPERTY(Config)` — Whether to check for patches during the update process.
- L130 _public member_ `TSet<FString> AdditionalTags;` — `UPROPERTY(Config)` — Additional tags for extensibility.

#### class `IUpdateManagerStatsCollector`  
`class IUpdateManagerStatsCollector`  
_L138-163_
- desc: Collector for aggregating stats related to the update check process. Implement collector and pass into RegisterStatsCollector to receive stats.
- L141 _public prototype_ `virtual ~IUpdateManagerStatsCollector() = default;`
- L153 _public prototype_ `virtual void OnCheckStarted(FCheckStartedParams&& Params) = 0;` — Overall process/
- L154 _public prototype_ `virtual void OnCheckComplete(EUpdateCompletionStatus Result) = 0;`
- L157 _public prototype_ `virtual void OnCheckStep_PatchCheckStarted() = 0;` — Individual stages.
- L158 _public prototype_ `virtual void OnCheckStep_PatchCheckComplete(EInstallBundleManagerPatchCheckResult PatchResult) = 0;`
- L159 _public prototype_ `virtual void OnCheckStep_HotfixCheckStarted() = 0;`
- L160 _public prototype_ `virtual void OnCheckStep_HotfixCheckComplete(EHotfixResult Result) = 0;`
- L161 _public prototype_ `virtual void OnCheckStep_InitialPreloadStarted() = 0;`
- L162 _public prototype_ `virtual void OnCheckStep_InitialPreloadComplete() = 0;`

#### struct `IUpdateManagerStatsCollector::FCheckStartedParams`  
`struct FCheckStartedParams`  
_L143-150_
- L145 _public member_ `FString ContextName;`
- L146 _public member_ `bool bEnabled = true;`
- L147 _public member_ `bool bCheckAvailabilityOnly = false;`
- L148 _public member_ `bool bCachedResponse = false;`
- L149 _public member_ `double CacheExpiration = 0.0;`

#### class `UUpdateManager`  
`class UUpdateManager : public UObject`  
_L175-499_
- reflection: `UCLASS(MinimalAPI, Config=Engine)`
- inherits: `UObject`
- desc: Update manager Checks the system and/or backend for the possibility of a patch and hotfix Will not apply a hotfix if a pending patch is available Notifies the game of the result of the check - possibly requires UI to prevent user from playing if a patch is available - possibly requires UI to prevent user from player if a hotfix requires a reload of existing data
- L182 _private member_ `FOnUpdateStatusChanged UpdateStatusChangedDelegates;` — Status update listeners
- L184 _private member_ `FOnUpdateCheckComplete UpdateCheckCompleteDelegates;` — Check completion listeners
- L186 _private member_ `FOnUpdateHotfixProgress UpdateHotfixProgressDelegate;` — Hotfix download progress listeners
- L188 _private member_ `FOnUpdateHotfixProcessedFile UpdateHotfixProcessedFile;` — Hotfix application process listeners
- L192 _public prototype_ `UUpdateManager();`
- L193 _public prototype_ `virtual ~UUpdateManager();`
- L198 _public prototype_ `virtual void Reset();` — Reset so you can call StartCheck again
- L206 _public prototype_ `virtual void StartCheck(bool bInCheckHotfixOnly = false);` — `UE_DEPRECATED_FORGAME(5.1, "UUpdateManager::StartCheck is deprecated, please use StartUpdateCheck instead.")` — Start an patch and hotfix check @param bInCheckHotfixOnly check for the availability of a hotfix only (does not apply)
- L213 _public prototype_ `void StartUpdateCheck(const FString& ContextName);` — Start an update check using properties defined by context. @param ContextName The context definitions to use when updating.
- L218 _public prototype_ `float GetLoadProgress() const;` — @return the load progress (0..1)
- L223 _public prototype_ `bool IsHotfixingEnabled() const;` — @return true if hotfixing is enabled
- L228 _public prototype_ `bool IsBlockingForInitialLoadEnabled() const;` — @return true if blocking for initial load is enabled
- L233 _public prototype_ `void SetPending();` — Put the update manager in a pending state so it can alert the game that a check is imminent
- L238 _public function_ `bool HasCompletedInitialUpdate() const` — @return true if at least one update been completed
- L243 _public function_ `bool IsUpdating() const` — @return true if the update manager is actively checking or about to
- L248 _public function_ `bool IsActivelyUpdating() const` — @return true if the update manager is actively checking
- L253 _public prototype_ `void RegisterStatsCollector(const TSharedPtr<IUpdateManagerStatsCollector>& InStatsCollector);` — Register a collector for acquiring stats related to the update check process.
- L258 _public function_ `EUpdateState GetUpdateState() const` — @return the current state of the update check process
- L263 _public function_ `EUpdateCompletionStatus GetCompletionResult() const` — @return the last result of the update manager
- L268 _public function_ `FOnUpdateStatusChanged& OnUpdateStatusChanged()` — @return delegate triggered when update status has changed
- L273 _public function_ `FOnUpdateCheckComplete& OnUpdateCheckComplete()` — @return delegate triggered when update check is complete
- L278 _public function_ `FOnUpdateHotfixProgress& OnUpdateHotfixProgress()` — @return delegate triggered when hotfix file download progress has been made
- L283 _public function_ `FOnUpdateHotfixProcessedFile& OnUpdateHotfixProcessedFile()` — @return delegate triggered when hotfix file is applied
- L298 _protected prototype_ `virtual bool ChecksEnabled() const;` — @return true if update checks are enabled
- L301 _protected prototype_ `virtual bool EnvironmentWantsPatchCheck() const;` — `UE_DEPRECATED_FORGAME(4.25, "UUpdateManager::EnvironmentWantsPatchCheck is deprecated, please override FPatchCheck::EnvironmentWantsPatchCheck instead.")` — @return true if the backend environment requires update checks
- L309 _protected prototype_ `virtual EUpdateStartResult StartCheckInternal(bool bInCheckHotfixOnly);` — `UE_DEPRECATED_FORGAME(5.1, "UUpdateManager::StartCheckInternal is deprecated, please override StartCheckUpdateInternal instead.")` — Internal call for StartCheck @return whether or not the check started, returned a cached value, or did nothing (already in progress)
- L316 _protected prototype_ `virtual EUpdateStartResult StartUpdateCheckInternal(const FUpdateContextDefinition& ContextDefinition);` — Internal call for StartUpdateCheck @return whether or not the check started, returned a cached value, or did nothing (already in progress)
- L319 _protected prototype_ `virtual bool Tick(float DeltaTime);` — Tick function during initial preload
- L321 _protected prototype_ `virtual void PostInitProperties() override;`
- L322 _protected prototype_ `virtual void PostReloadConfig(FProperty* PropertyThatWasLoaded) override;`
- L326 _protected member_ `float UpdateCheckStartDelay;` — `UPROPERTY(Config)` — Amount of time to wait before starting an update check.
- L329 _protected member_ `float UpdateCheckCachedResponseDelay;` — `UPROPERTY(Config)` — Amount of time to wait before returning a cached response when updates are started.
- L332 _protected member_ `float HotfixCheckCompleteDelay;` — `UPROPERTY(Config)` — Amount of time to wait between the internal hotfix check completing and advancing to the next stage
- L335 _protected member_ `float UpdateCheckCompleteDelay;` — `UPROPERTY(Config)` — Amount of time to wait at the end of the entire check before notifying listening entities
- L338 _protected member_ `float HotfixAvailabilityCheckCompleteDelay;` — `UPROPERTY(Config)` — Amount of time to wait between the internal hotfix availability check completing and advancing to the next stage
- L341 _protected member_ `float UpdateCheckAvailabilityCompleteDelay;` — `UPROPERTY(Config)` — Amount of time to wait at the end of the entire check before notifying listening entities (availability check only)
- L345 _protected member_ `bool bCheckPlatformOSSForUpdate;` — `UE_DEPRECATED(4.25, "Set FPatchCheck::bCheckPlatformOSSForUpdate using section [PatchCheck] instead.")` — Check the platform OSS for an update
- L348 _protected member_ `bool bCheckOSSForUpdate;` — `UE_DEPRECATED(4.25, "Set FPatchCheck::bCheckOSSForUpdate using section [PatchCheck] instead.")` — Check the default OSS for an update
- L353 _protected prototype_ `virtual void StartPatchCheck();` — Patch check
- L354 _protected prototype_ `void InstallBundlePatchCheckComplete(EInstallBundleManagerPatchCheckResult PatchResult);`
- L355 _protected prototype_ `void PatchCheckComplete(EPatchCheckResult PatchResult);`
- L360 _protected prototype_ `virtual void StartHotfixCheck();` — Hotfix check
- L361 _protected prototype_ `virtual void OnHotfixProgress(uint32 NumDownloaded, uint32 TotalFiles, uint64 NumBytes, uint64 TotalBytes);`
- L362 _protected prototype_ `virtual void OnHotfixProcessedFile(const FString& FriendlyName, const FString& CachedName);`
- L363 _protected prototype_ `virtual void OnHotfixCheckComplete(EHotfixResult Result);`
- L366 _protected prototype_ `virtual void StartHotfixAvailabilityCheck();` — Check for the availability of changed hotfix files only
- L368 _protected prototype_ `virtual void HotfixAvailabilityCheckComplete(EHotfixResult Result);` — Availability check complete
- L373 _protected prototype_ `virtual void StartInitialPreload();` — Preload game assets after patch/hotfix check is complete but before game is alerted
- L378 _protected prototype_ `virtual void InitialPreloadComplete();` — Initial preload of assets is complete
- L386 _protected prototype_ `virtual void CheckComplete(EUpdateCompletionStatus Result, bool bUpdateTimestamp = true);` — Announce that the update check has completed @param Result result of the entire update check (patch/hotfix/etc) @param bUpdateTimestamp whether or not to update the cache timer
- L389 _protected prototype_ `virtual void SetUpdateState(EUpdateState NewState);` — Change the state of the update manager
- L393 _protected member_ `int32 AppSuspendedUpdateCheckTimeSeconds;` — `UPROPERTY(Config)` — If application is suspended longer than this, trigger an update check when resuming
- L396 _protected member_ `FDateTime DeactivatedTime;` — Time when application was deactivated
- L399 _protected prototype_ `void RegisterDelegates();` — Register deactivate/reactivate delegates
- L401 _protected prototype_ `void UnregisterDelegates();` — Unregister deactivate/reactivate delegates
- L404 _protected prototype_ `virtual void OnApplicationWillDeactivate();` — Called when application is about to be deactivated
- L406 _protected prototype_ `virtual void OnApplicationHasReactivated();` — Called when application has been reactivated
- L411 _protected member_ `bool bInitialUpdateFinished;` — `UPROPERTY()` — Has the first update completed
- L415 _protected member_ `bool bCheckHotfixAvailabilityOnly;` — `UPROPERTY()` — Is this run only checking and not applying
- L419 _protected member_ `EUpdateState CurrentUpdateState;` — `UPROPERTY()` — Current state of the update
- L423 _protected member_ `int32 WorstNumFilesPendingLoadViewed;` — `UPROPERTY()` — What was the maximum number of pending async loads we've seen so far
- L426 _protected member_ `EInstallBundleManagerPatchCheckResult LastPatchCheckResult;` — Result of the last patch check
- L430 _protected member_ `EHotfixResult LastHotfixResult;` — `UPROPERTY()` — Result of the last hotfix
- L432 _protected member_ `FDelegateHandle HotfixCompleteDelegateHandle;` — Delegates to hotfix updates
- L433 _protected member_ `FDelegateHandle HotfixProgressDelegateHandle;`
- L434 _protected member_ `FDelegateHandle HotfixProcessedFileDelegateHandle;`
- L437 _protected member_ `double LoadStartTime;` — The time at which we started the initial load after updates completed
- L441 _protected member_ `FDateTime LastUpdateCheck[2];` — `UPROPERTY()` — Timestamp of last update check (0:normal, 1:availability only)
- L444 _protected member_ `EUpdateCompletionStatus LastCompletionResult[2];` — `UPROPERTY()` — Last update check result (0:normal, 1:availability only)
- L446 _protected member_ `FTSTicker::FDelegateHandle TickerHandle;`
- L447 _protected member_ `FTSTicker::FDelegateHandle StartCheckInternalTimerHandle;`
- L449 _protected member_ `TWeakPtr<IUpdateManagerStatsCollector> StatsCollector;`
- L459 _private member_ `TObjectPtr<UEnum> UpdateStateEnum;` — `UPROPERTY()` — String output
- L461 _private member_ `TObjectPtr<UEnum> UpdateCompletionEnum;` — `UPROPERTY()`
- L464 _private typedef_ `typedef TFunction<void(void)> DelayCb;` — Fire a delegate after a given amount of time
- L465 _private prototype_ `FTSTicker::FDelegateHandle DelayResponse(DelayCb&& Delegate, float Delay);`
- L470 _private prototype_ `void PopulateContextDefinitions();`
- L471 _private prototype_ `const FUpdateContextDefinition& GetContextDefinition(const FString& ContextName) const;`
- L475 _private member_ `FUpdateContextDefinition UpdateContextDefinitionUnknown;` — `UPROPERTY(Config)` — Definition to use when a context lookup fails.
- L479 _private member_ `TArray<FUpdateContextDefinition> UpdateContextDefinitions;` — `UPROPERTY(Config)` — Definitions for update behavior.
- L482 _private member_ `TMap<FString, FUpdateContextDefinition> ProcessedUpdateContextDefinitions;` — Update context definitions which have been processed following a config update.
- L484 _private member_ `bool bCurrentUpdatePatchCheckEnabled = true;`
- L489 _protected function_ `template< typename THotfixManager > THotfixManager* GetHotfixManager() const` — @return a pointer to the hotfix manager
- L495 _protected prototype_ `UWorld* GetWorld() const;` — @return a pointer to the world
- L498 _protected prototype_ `UGameInstance* GetGameInstance() const;` — @return a pointer to the game instance

#### enum `UUpdateManager::EUpdateStartResult`  
`enum class EUpdateStartResult : uint8`  
_L287-295_
- L290 _public enumerator_ `None` — Update did not start
- L292 _public enumerator_ `UpdateStarted` — Update has started
- L294 _public enumerator_ `UpdateCached` — Cached result is going to be returned

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API HOTFIX_API`
- L68 _prototype_ `FString LexToString(EUpdateCompletionStatus Status);`
- L75 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdateStatusChanged, EUpdateState ) typedef FOnUpdateStatusChanged::FDelegate FOnUpdateStatusChangedDelegate;` — Delegate fired when changes to the update progress have been made @param NewState newest state change while an update check is in progress
- L76 _typedef_ `typedef FOnUpdateStatusChanged::FDelegate FOnUpdateStatusChangedDelegate;`
- L83 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdateCheckComplete, EUpdateCompletionStatus ) typedef FOnUpdateCheckComplete::FDelegate FOnUpdateCheckCompleteDelegate;` — Delegate fired when a single update check has completed @param Result result of the update check operation
- L84 _typedef_ `typedef FOnUpdateCheckComplete::FDelegate FOnUpdateCheckCompleteDelegate;`
- L94 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnUpdateHotfixProgress, uint32 , uint32 , uint64 , uint64 ) typedef FOnUpdateHotfixProgress::FDelegate FOnUpdateHotfixProgressDelegate;` — Delegate fired when progress on a hotfix download is made @param NumDownloaded the number of files downloaded so far @param TotalFiles the total number of files part of the hotfix @param NumBytes the number of bytes processed so far @param TotalBytes the total size of the hotfix data
- L95 _typedef_ `typedef FOnUpdateHotfixProgress::FDelegate FOnUpdateHotfixProgressDelegate;`
- L103 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnUpdateHotfixProcessedFile, const FString& , const FString& );` — Delegate fired when a single file hotfix is applied @param FriendlyName the human readable version of the file name (DefaultEngine.ini) @param CachedFileName the full path to the file on disk
- L103 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnUpdateHotfixProcessedFile, const FString& , const FString& );` — Delegate fired when a single file hotfix is applied @param FriendlyName the human readable version of the file name (DefaultEngine.ini) @param CachedFileName the full path to the file on disk
- L104 _typedef_ `typedef FOnUpdateHotfixProcessedFile::FDelegate FOnUpdateHotfixProcessedFileDelegate;`
