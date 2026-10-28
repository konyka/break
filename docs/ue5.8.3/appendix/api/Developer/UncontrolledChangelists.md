# Developer / UncontrolledChangelists

- module root: `Source/Developer/UncontrolledChangelists`
- headers: 3; symbols: 142
- symbol kinds: class=3, delegate=1, enum=1, enumerator=4, function=9, macro=3, member=32, prototype=83, struct=1, typedef=5
- PrivateDependencyModuleNames: AssetRegistry, EditorFramework, Engine, Json, PackagesDialog, SourceControl
- PublicDependencyModuleNames: Core, CoreUObject, InputCore, SlateCore

### `Source/Developer/UncontrolledChangelists/Public/UncontrolledChangelist.h` (Public)


#### class `FUncontrolledChangelist`  
`class FUncontrolledChangelist : public TSharedFromThis<FUncontrolledChangelist, ESPMode::ThreadSafe>`  
_L16-67_
- inherits: `TSharedFromThis<FUncontrolledChangelist,ESPMode::ThreadSafe>`
- L19 _public member_ `static constexpr const TCHAR* GUID_NAME = TEXT("gui`
- L20 _public member_ `static const FGuid DEFAULT_UNCONTROLLED_CHANGELIST_GUID;`
- L23 _public prototype_ `FUncontrolledChangelist();`
- L25 _public prototype_ `FUncontrolledChangelist(const FGuid& InGuid);`
- L27 _public function_ `bool operator==(const FUncontrolledChangelist& InOther) const`
- L32 _public function_ `bool operator!=(const FUncontrolledChangelist& InOther) const`
- L37 _public function_ `bool IsDefault() const`
- L47 _public function_ `FString ToString() const`
- L56 _public prototype_ `void Serialize(TSharedRef<class FJsonObject> OutJsonObject) const;` — Serialize the Uncontrolled Changelist to a Json Object. @param	OutJsonObject	The Json Object used to serialize.
- L63 _public prototype_ `bool Deserialize(const TSharedRef<class FJsonObject> InJsonValue);` — Deserialize the Uncontrolled Changelist from a Json Object. @param 	InJsonValue 	The Json Object to read from. @return 	True if Deserialization succeeded.
- L66 _private member_ `FGuid Guid;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UNCONTROLLEDCHANGELISTS_API`
- L42 _function_ `friend FORCEINLINE uint32 GetTypeHash(const FUncontrolledChangelist& PerforceUncontrolledChangelist)`
- L69 _typedef_ `typedef TSharedPtr<FUncontrolledChangelist, ESPMode::ThreadSafe> FUncontrolledChangelistPtr;`
- L70 _typedef_ `typedef TSharedRef<FUncontrolledChangelist, ESPMode::ThreadSafe> FUncontrolledChangelistRef;`

### `Source/Developer/UncontrolledChangelists/Public/UncontrolledChangelistState.h` (Public)


#### class `FUncontrolledChangelistState`  
`class FUncontrolledChangelistState : public TSharedFromThis<FUncontrolledChangelistState, ESPMode::ThreadSafe>`  
_L25-183_
- inherits: `TSharedFromThis<FUncontrolledChangelistState,ESPMode::ThreadSafe>`
- L28 _public member_ `static constexpr const TCHAR* FILES_NAME = TEXT("fil`
- L29 _public member_ `static constexpr const TCHAR* NAME_NAME = TEXT("nam`
- L30 _public member_ `static constexpr const TCHAR* DESCRIPTION_NAME = TEXT("des`
- L31 _public member_ `static const FText DEFAULT_UNCONTROLLED_CHANGELIST_DESCRIPTION;`
- L50 _public prototype_ `FUncontrolledChangelistState() = delete;` — An FUncontrolledChangelistState should always reference a given Changelist (with a valid GUID).
- L52 _public prototype_ `FUncontrolledChangelistState(const FUncontrolledChangelist& InUncontrolledChangelist);`
- L54 _public prototype_ `FUncontrolledChangelistState(const FUncontrolledChangelist& InUncontrolledChangelist, const FText& InDescription);`
- L57 _public prototype_ `FUncontrolledChangelistState(const FUncontrolledChangelistState& InUncontrolledChangelistState) = delete;` — Uncontrolled Changelist states are unique and non-copyable, should always be used by reference to preserve cache coherence.
- L58 _public prototype_ `FUncontrolledChangelistState& operator=(const FUncontrolledChangelistState& InUncontrolledChangelistState) = delete;`
- L64 _public prototype_ `FName GetIconName() const;` — Get the name of the icon graphic we should use to display the state in a UI. @returns the name of the icon to display
- L70 _public prototype_ `FName GetSmallIconName() const;` — Get the name of the small icon graphic we should use to display the state in a UI. @returns the name of the icon to display
- L76 _public prototype_ `const FText& GetDisplayText() const;` — Get a text representation of the state @returns	the text to display for this state
- L82 _public prototype_ `const FText& GetDescriptionText() const;` — Get a text representation of the state @returns	the text to display for this state
- L88 _public prototype_ `FText GetDisplayTooltip() const;` — Get a tooltip to describe this state @returns	the text to display for this states tooltip
- L94 _public prototype_ `const FDateTime& GetTimeStamp() const;` — Get the timestamp of the last update that was made to this state. @returns	the timestamp of the last update
- L96 _public prototype_ `const TSet<FSourceControlStateRef>& GetFilesStates() const;`
- L98 _public prototype_ `const TSet<FString>& GetOfflineFiles() const;`
- L100 _public prototype_ `const TSet<FString>& GetDeletedOfflineFiles() const;`
- L105 _public prototype_ `int32 GetFileCount() const;` — Get the number of files in the CL. (Includes file states and offline files)
- L110 _public prototype_ `TArray<FString> GetFilenames() const;` — Get the filenames in the CL. (Includes file states and offline files)
- L115 _public prototype_ `bool ContainsFilename(const FString& PackageFilename) const;` — Check whether a file exists in the file states or offline files
- L122 _public prototype_ `void Serialize(TSharedRef<class FJsonObject> OutJsonObject, const TFunction<bool(const FString&)>& FilenameFilter = nullptr) const;` — Serialize the state of the Uncontrolled Changelist to a Json Object, optionally filtering the files. @param 	OutJsonObject 	The Json object used to serialize. @param	FilenameFilter	An optional filter to control while filenames are included in the serialized JSON.
- L129 _public prototype_ `bool Deserialize(const TSharedRef<FJsonObject> InJsonValue);` — Deserialize the state of the Uncontrolled Changelist from a Json Object. @param 	InJsonValue 	The Json Object to read from. @return 	True if Deserialization succeeded.
- L137 _public prototype_ `bool AddFiles(const TArray<FString>& InFilenames, const ECheckFlags InCheckFlags);` — Adds files to this Uncontrolled Changelist State. @param 	InFilenames		The files to be added. @param 	InCheckFlags 	Tells which checks have to pass to add a file. @return 	True if a change has been performed in the Uncontrolled Changelist State.
- L144 _public prototype_ `bool RemoveFiles(const TArray<FSourceControlStateRef>& InFileStates);` — Removes files from this Uncontrolled Changelist State if present. @param 	InFileStates 	The files to be removed. @return 	True if a change has been performed in the Uncontrolled Changelist State.
- L151 _public prototype_ `bool RemoveFiles(const TArray<FString>& InFilenames);` — Removes the given filenames from the file states or offline files. @param 	InFilenames 	The filenames to be removed. @return 	True if a change has been performed in the Uncontrolled Changelist State.
- L157 _public prototype_ `bool UpdateStatus();` — Updates the status of all files contained in this changelist. @return 	True if the state has been modified.
- L163 _public prototype_ `void RemoveDuplicates(TSet<FString>& InOutAddedAssets);` — Removes files present both in the Uncontrolled Changelist and the provided set. @param 	InOutAddedAssets 	A Set representing Added Assets to check against.
- L169 _public prototype_ `void SetDescription(const FText& InDescription);` — Sets a new description for this Uncontrolled Changelist @param	InDescription	The new description to set.
- L172 _public prototype_ `bool ContainsFiles() const;` — Returns true if the Uncontrolled Changelists contains either Files or OfflineFiles.
- L175 _public member_ `FUncontrolledChangelist Changelist;`
- L176 _public member_ `FText Description;`
- L177 _public member_ `TSet<FSourceControlStateRef> Files;`
- L178 _public member_ `TSet<FString> OfflineFiles;`
- L179 _public member_ `TSet<FString> DeletedOfflineFiles;`
- L182 _public member_ `FDateTime TimeStamp;` — The timestamp of the last update

#### enum `FUncontrolledChangelistState::ECheckFlags`  
`enum class ECheckFlags`  
_L33-46_
- L36 _public enumerator_ `None = 0` — No Check
- L39 _public enumerator_ `Modified = 1` — File has been modified
- L42 _public enumerator_ `NotCheckedOut = 1 << 1` — File is not checked out
- L45 _public enumerator_ `All = Modified | NotCheckedOut` — All the above checks

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API UNCONTROLLEDCHANGELISTS_API`
- L185 _prototype_ `ENUM_CLASS_FLAGS(FUncontrolledChangelistState::ECheckFlags);`
- L186 _typedef_ `typedef TSharedPtr<FUncontrolledChangelistState, ESPMode::ThreadSafe> FUncontrolledChangelistStatePtr;`
- L187 _typedef_ `typedef TSharedRef<FUncontrolledChangelistState, ESPMode::ThreadSafe> FUncontrolledChangelistStateRef;`

### `Source/Developer/UncontrolledChangelists/Public/UncontrolledChangelistsModule.h` (Public)


#### class `FUncontrolledChangelistsModule`  
`class FUncontrolledChangelistsModule : public IModuleInterface`  
_L24-378_
- inherits: `IModuleInterface`
- desc: Interface for talking to Uncontrolled Changelists
- L26 _private typedef_ `typedef TMap<FUncontrolledChangelist, FUncontrolledChangelistStateRef> FUncontrolledChangelistsStateCache;`
- L29 _public member_ `static constexpr const TCHAR* VERSION_NAME = TEXT("ver`
- L30 _public member_ `static constexpr const TCHAR* CHANGELISTS_NAME = TEXT("cha`
- L31 _public member_ `static constexpr uint32 VERSION_NUMBER = 1;`
- L34 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnUncontrolledChangelistModuleChanged);` — Callback called when the state of the Uncontrolled Changelist Module (or any Uncontrolled Changelist) changed
- L35 _public member_ `FOnUncontrolledChangelistModuleChanged OnUncontrolledChangelistModuleChanged;`
- L38 _public prototype_ `FUncontrolledChangelistsModule();`
- L39 _public prototype_ `~FUncontrolledChangelistsModule();`
- L42 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L43 _public prototype_ `virtual void ShutdownModule() override;`
- L48 _public prototype_ `bool IsEnabled() const;` — Check whether uncontrolled changelist module is enabled.
- L53 _public prototype_ `TArray<FUncontrolledChangelistStateRef> GetChangelistStates() const;` — Get the changelist state of each cached Uncontrolled Changelist.
- L58 _public prototype_ `FUncontrolledChangelistStatePtr GetChangelistState(const FUncontrolledChangelist& InUncontrolledChangelist) const;` — Get the changelist state of the given Uncontrolled Changelist.
- L63 _public prototype_ `FUncontrolledChangelistStatePtr GetDefaultChangelistState() const;` — Get the changelist state of the default Uncontrolled Changelist.
- L68 _public prototype_ `void HandleChangelistStateModified();` — Called if the state of any Uncontrolled Changelist is modified externally, eg, via the mutable accessors above.
- L75 _public prototype_ `bool OnMakeWritable(const FString& InFilename);` — Called when file has been made writable. Adds the file to the reconcile list because we don't know yet if it will change. @param	InFilename		The file to be reconciled. @return True if the file have been handled by the Uncontrolled module.
- L82 _public prototype_ `bool OnSaveWritable(const FString& InFilename);` — Called when file has been saved without an available Provider. Adds the file to the Default Uncontrolled Changelist @param	InFilename		The file to be added. @return	True if the file have been handled by the Uncontrolled module.
- L89 _public prototype_ `bool OnDeleteWritable(const FString& InFilename);` — Called when file has been deleted without an available Provider. Adds the file to the Default Uncontrolled Changelist @param	InFilename		The file to be added. @return	True if the file have been handled by the Uncontrolled module.
- L96 _public prototype_ `bool OnNewFilesAdded(const TArray<FString>& InFilenames);` — Called when files should have been marked for add without an available Provider. Adds the files to the Default Uncontrolled Changelist @param	InFilenames		The files to be added. @return	True if the files have been handled by the Uncontrolled module.
- L101 _public prototype_ `void UpdateStatus();` — Updates the status of Uncontrolled Changelists and files.
- L107 _public function_ `static inline FUncontrolledChangelistsModule& Get()` — Gets a reference to the UncontrolledChangelists module @return A reference to the UncontrolledChangelists module.
- L116 _public function_ `static inline FUncontrolledChangelistsModule* GetPtr()` — Gets a pointer to the UncontrolledChangelists module, if loaded @return A pointer to the UncontrolledChangelists module.
- L126 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L131 _public function_ `static FName GetModuleName()`
- L141 _public prototype_ `FText GetReconcileStatus() const;` — Gets a message indicating the status of SCC coherence. @return 	A text representing the status of SCC.
- L147 _public prototype_ `bool OnReconcileAssets();` — Called when "Reconcile assets" button is clicked. Checks for uncontrolled modifications in previously added assets. Adds modified files to Uncontrolled Changelists @return True if new modifications found
- L153 _public prototype_ `void OnAssetAdded(const FAssetData& AssetData);` — Delegate callback called when assets are added to AssetRegistry. @param 	AssetData 	The asset just added.
- L159 _public prototype_ `bool OnRevert(const TArray<FString>& InFilenames);` — Called when "Revert files" button is clicked. Reverts modified files and deletes new ones. @param	InFilenames		The files to be reverted @return true if the provided files were reverted.
- L166 _public prototype_ `void OnObjectPreSaved(UObject* InObject, FObjectPreSaveContext InPreSaveContext);` — Delegate callback called before an asset has been written to disk. @param 	InObject 			The saved object. @param 	InPreSaveContext 	Interface used to access saved parameters.
- L174 _public prototype_ `void MoveFilesToUncontrolledChangelist(const TArray<FSourceControlStateRef>& InControlledFileStates, const TArray<FSourceControlStateRef>& InUncontrolledFileStates, const FUncontrolledChangelist& InUncontrolledChangelist);` — Moves files to an Uncontrolled Changelist. @param 	InControlledFileStates 		The Controlled files to move. @param 	InUncontrolledFileStates 	The Uncontrolled files to move. @param 	InUncontrolledChangelist 	The Uncontrolled Changelist where to move the files.
- L181 _public prototype_ `void MoveFilesToUncontrolledChangelist(const TArray<FString>& InControlledFiles, const FUncontrolledChangelist& InUncontrolledChangelist);` — Moves files to an Uncontrolled Changelist. @param 	InControlledFileStates 		The Controlled files to move. @param 	InUncontrolledChangelist 	The Uncontrolled Changelist where to move the files.
- L189 _public prototype_ `void MoveFilesToControlledChangelist(const TArray<FSourceControlStateRef>& InUncontrolledFileStates, const FSourceControlChangelistPtr& InChangelist, TFunctionRef<bool(const TArray<FSourceControlStateRef>&)> InOpenConflictDialog);` — Moves files to a Controlled Changelist. @param 	InUncontrolledFileStates 	The files to move. @param 	InChangelist 				The Controlled Changelist where to move the files. @param 	InOpenConflictDialog 		A callback to be used by the method when file conflicts are detected. The callback should display the files and ask the user if they should proceed.
- L197 _public prototype_ `void MoveFilesToControlledChangelist(const TArray<FString>& InUncontrolledFiles, const FSourceControlChangelistPtr& InChangelist, TFunctionRef<bool(const TArray<FSourceControlStateRef>&)> InOpenConflictDialog);` — Moves files to a Controlled Changelist. @param 	InUncontrolledFiles 	The files to move. @param 	InChangelist 			The Controlled Changelist where to move the files. @param 	InOpenConflictDialog 	A callback to be used by the method when file conflicts are detected. The callback should display the files and ask the user if they should proceed.
- L205 _public prototype_ `TOptional<FUncontrolledChangelist> CreateUncontrolledChangelist(const FText& InDescription, const TOptional<FUncontrolledChangelist>& InUncontrolledChangelist = TOptional<FUncontrolledChangelist>());` — Creates a new Uncontrolled Changelist. @param	InDescription				The description of the newly created Uncontrolled Changelist. @param	InUncontrolledChangelist	An optional Uncontrolled Changelist to create (or find) via its ID. Should not be the default Uncontrolled Changelist. return	TOptional<FUncontrolledChangelist> set with the new Uncontrolled Changelist key if succeeded.
- L212 _public prototype_ `void EditUncontrolledChangelist(const FUncontrolledChangelist& InUncontrolledChangelist, const FText& InNewDescription);` — Edits an Uncontrolled Changelist's description @param	InUncontrolledChangelist	The Uncontrolled Changelist to modify. Should not be the default Uncontrolled Changelist. @param	InNewDescription			The description to set.
- L218 _public prototype_ `void DeleteUncontrolledChangelist(const FUncontrolledChangelist& InUncontrolledChangelist);` — Deletes an Uncontrolled Changelist. @param	InUncontrolledChangelist	The Uncontrolled Changelist to delete. Should not be the default Uncontrolled Changelist and should not contain files.
- L228 _private prototype_ `void OnAssetAddedInternal(const FAssetData& InAssetData, TSet<FString>& InAddedAssetsCache, bool bInDiscoveryTask);` — Helper use by asset discovery task and OnAssetLoaded delegate. @param 	InAssetData 		The asset just added. @param  	InAddedAssetsCache 	The cache to add the asset to. @param	bInDiscoveryTask	If true, this asset was added from the asset discovery task.
- L233 _private prototype_ `bool AddToUncontrolledChangelist(const TArray<FString>& InFilenames);` — Add files to Uncontrolled Changelist. Also adds them to files to reconcile.
- L239 _private prototype_ `bool RemoveFromUncontrolledChangelist(const TArray<FString>& InFilenames);` — Removes the given files from their associated Uncontrolled Changelist, if any.  Also removes them from files to reconcile. @return true if any of the given files are removed.
- L245 _private prototype_ `void GroupFilesByUncontrolledChangelist(TArray<FString>&& InFilenames, TMap<FUncontrolledChangelist, TArray<FString>>& OutUncontrolledChangelistToFilenames) const;` — Groups the given files by their associated Uncontrolled Changelist and returns the groupings in the given map. Any of the files that are not already associated with an Uncontrolled Changelist will be added to the default Uncontrolled Changelist's group.
- L250 _private prototype_ `bool HasCustomProjectFilter() const;` — True if we have custom projects and calling DoesFilePassCustomProjectFilter could ever return something aside from true.
- L255 _private prototype_ `bool DoesFilePassCustomProjectFilter(const FString& InFilename) const;` — Run the given file through the filter for all known custom projects.
- L260 _private prototype_ `static bool DoesFilePassCustomProjectFilter(const FString& InFilename, const FSourceControlProjectInfo& Project);` — Run the given file through the filter for the given custom project.
- L265 _private prototype_ `void SaveState();` — Saves the state of UncontrolledChangelists to Json for persistency.
- L270 _private prototype_ `void LoadState();` — Restores the previously saved state from Json.
- L275 _private prototype_ `void RequestReloadState();` — Request that ReloadState be called at the end of the current frame.
- L280 _private prototype_ `void ReloadState();` — Reload the state of the UncontrolledChangelists when ISourceControlModule::GetCustomProjects changes.
- L285 _private prototype_ `void SanitizeState();` — Removes any duplicated files across changelists
- L290 _private prototype_ `void OnEndFrame();` — Called on End of frame. Calls SaveState if needed.
- L295 _private prototype_ `void OnEnabled();` — Called when the uncontrolled changelist feature switches to an enabled state.
- L300 _private prototype_ `void OnDisabled();` — Called when the uncontrolled changelist feature switches to a disabled state.
- L306 _private prototype_ `void StartAssetDiscovery();` — Start a new DiscoverAssetsTask for the current state. @note InitialScanEvent must be null before calling this, and there shouldn't be any existing DiscoverAssetsTask running.
- L311 _private prototype_ `void StopAssetDiscovery();` — Stop the current DiscoverAssetsTask, if any.
- L316 _private prototype_ `bool IsStopAssetDiscoveryRequested() const;` — Used by the task to query whether we're waiting for it to finish in StopAssetDiscovery.
- L322 _private prototype_ `FString GetPersistentFilePath(const FString& SubProjectName) const;` — Helper returning the location of the file used for persistency. @return 	A string containing the filepath.
- L325 _private prototype_ `void OnStateChanged();` — Called when a state changed either in the module or an Uncontrolled Changelist.
- L328 _private prototype_ `void CleanAssetsCaches();` — Removes from asset caches files already present in Uncontrolled Changelists
- L337 _private prototype_ `bool AddFilesToUncontrolledChangelist(const FUncontrolledChangelist& InUncontrolledChangelist, const TArray<FString>& InFilenames, const FUncontrolledChangelistState::ECheckFlags InCheckFlags);` — Try to add the provided filenames to the given Uncontrolled Changelist. @param	InUncontrolledChangelist	The Uncontrolled Changelist to add to. @param	InFilenames 				The files to add. @param	InCheckFlags 				The required checks to check the file against before adding. @return	True files have been added.
- L345 _private prototype_ `bool RemoveFilesFromUncontrolledChangelist(const FUncontrolledChangelist& InUncontrolledChangelist, const TArray<FString>& InFilenames);` — Try to remove the provided filenames from the given Uncontrolled Changelist. @param	InUncontrolledChangelist	The Uncontrolled Changelist to remove from. @param	InFilenames 				The files to remove. @return	True files have been removed.
- L348 _private prototype_ `FUncontrolledChangelistStateRef GetDefaultUncontrolledChangelistState();` — Returns the default Uncontrolled Changelist state, creates it if it does not exist.
- L355 _private prototype_ `FUncontrolledChangelistStatePtr GetUncontrolledChangelistState(const FUncontrolledChangelist& InUncontrolledChangelist);` — Returns the given Uncontrolled Changelist state if it exists. If the given Uncontrolled Changelist is the default one and it does not exist, then it will be created and returned. Otherwise, if not the default Uncontrolled Changelist, then nullptr will be returned if it does not exist.
- L362 _private member_ `TSharedPtr<FInitialScanEvent> InitialScanEvent;`
- L364 _private member_ `TPimplPtr<FAsyncTask<FUncontrolledChangelistsDiscoverAssetsTask>> DiscoverAssetsTask;`
- L365 _private member_ `FUncontrolledChangelistsStateCache UncontrolledChangelistsStateCache;`
- L366 _private member_ `TArray<FSourceControlProjectInfo> LoadedCustomProjects;`
- L367 _private member_ `TSet<FString> AddedAssetsCache;`
- L368 _private member_ `FDelegateHandle OnEnginePreExitDelegateHandle;`
- L369 _private member_ `FDelegateHandle OnAssetAddedDelegateHandle;`
- L370 _private member_ `FDelegateHandle OnObjectPreSavedDelegateHandle;`
- L371 _private member_ `FDelegateHandle OnCustomProjectsChangedDelegateHandle;`
- L372 _private member_ `FDelegateHandle OnEndFrameDelegateHandle;`
- L373 _private member_ `std::atomic<bool> bStopAssetDiscoveryRequested = false;`
- L374 _private member_ `bool bIsEnabled = false;`
- L375 _private member_ `bool bWasEnabledLastFrame = false;`
- L376 _private member_ `bool bIsStateDirty = false;`
- L377 _private member_ `bool bPendingReloadState = false;`

#### struct `FUncontrolledChangelistsModule::FInitialScanEvent`  
`struct FInitialScanEvent : public TSharedFromThis<FInitialScanEvent>`  
_L361-361_
- inherits: `TSharedFromThis<FInitialScanEvent>`
- desc: Used to determine if the initial Asset Registry scan was completed or the module was shutdown

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API UNCONTROLLEDCHANGELISTS_API`
- L34 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnUncontrolledChangelistModuleChanged);` — Callback called when the state of the Uncontrolled Changelist Module (or any Uncontrolled Changelist) changed
