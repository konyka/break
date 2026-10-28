# Plugins / ConcertSyncClient

- module root: `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient`
- headers: 57; symbols: 1466
- symbol kinds: class=51, delegate=31, enum=11, enumerator=33, externvar=11, function=138, macro=2, member=331, namespace=81, prototype=737, struct=33, typedef=7
- DynamicallyLoadedModuleNames: DirectoryWatcher
- PrivateDependencyModuleNames: AssetRegistry, ConcertTransport, EditorFramework, EditorStyle, EngineSettings, FileSandboxCore, HeadMountedDisplay, InputCore, JsonUtilities, LevelEditor, LevelSequence, MovieScene, RenderCore, Sequencer, Serialization, Slate, SlateCore, SourceControl, TimeManagement, TraceLog, TypedElementFramework, TypedElementRuntime, UnrealEd, VREditor, ViewportInteraction
- PrivateIncludePathModuleNames: DirectoryWatcher
- PublicDependencyModuleNames: Concert, ConcertClient, ConcertSyncCore, Core, CoreUObject, Engine

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Private/ConcertAssetContainer.h` (Private)


#### class `UConcertAssetContainer`  
`class UConcertAssetContainer : public UDataAsset`  
_L22-77_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDataAsset`
- desc: Asset container for VREditor.
- L33 _public member_ `TObjectPtr<UStaticMesh> GenericDesktopMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L36 _public member_ `TObjectPtr<UStaticMesh> GenericHMDMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L39 _public member_ `TObjectPtr<UStaticMesh> VivePreControllerMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L42 _public member_ `TObjectPtr<UStaticMesh> OculusControllerMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L45 _public member_ `TObjectPtr<UStaticMesh> GenericControllerMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L48 _public member_ `TObjectPtr<UStaticMesh> LaserPointerMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L51 _public member_ `TObjectPtr<UStaticMesh> LaserPointerEndMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L54 _public member_ `TObjectPtr<UStaticMesh> LaserPointerStartMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L61 _public member_ `TObjectPtr<UMaterialInterface> PresenceMaterial;` — `UPROPERTY(EditAnywhere, Category = Material)`
- L64 _public member_ `TObjectPtr<UMaterialInterface> TextMaterial;` — `UPROPERTY(EditAnywhere, Category = Material)`
- L67 _public member_ `TObjectPtr<UMaterialInterface> HeadMaterial;` — `UPROPERTY(EditAnywhere, Category = Desktop)`
- L70 _public member_ `TObjectPtr<UMaterialInterface> LaserCoreMaterial;` — `UPROPERTY(EditAnywhere, Category = Material)`
- L73 _public member_ `TObjectPtr<UMaterialInterface> LaserMaterial;` — `UPROPERTY(EditAnywhere, Category = Material)`
- L76 _public member_ `TObjectPtr<UMaterialInterface> PresenceFadeMaterial;` — `UPROPERTY(EditAnywhere, Category = Material)`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Private/ConcertBridges.h` (Private)


#### struct `UE::ConcertSyncClient::FConcertBridges`  
`struct FConcertBridges`  
_L11-21_
- L14 _public member_ `IConcertClientPackageBridge* PackageBridge;` — Package bridge used by sessions of this client
- L16 _public member_ `IConcertClientTransactionBridge* TransactionBridge;` — Transaction bridge used by sessions of this client
- L18 _public member_ `IConcertClientReplicationBridge* ReplicationBridge;` — Replication bridge used by sessions of this client
- L20 _public function_ `bool IsValid() const`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ConcertSyncClient` (scope `UE`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Private/ConcertClientDataStore.h` (Private)


#### class `FConcertClientDataStore`  
`class FConcertClientDataStore : public IConcertClientDataStore`  
_L19-59_
- inherits: `IConcertClientDataStore`
- desc: Stores key/value pairs in a data structure shared by all clients in the same Concert session. @remarks The implementation is thread safe, enabling clients to call from any thread.
- L26 _public prototype_ `FConcertClientDataStore(TSharedRef<FConcertSyncClientLiveSession> InLiveSession);` — Constructs a data store on the client side. @param InSession The session owning this store and used to send requests and receive responses or events.
- L27 _public prototype_ `virtual ~FConcertClientDataStore();`
- L31 _protected prototype_ `virtual TFuture<FConcertDataStoreResult> InternalFetchOrAdd(const FName& Key, const UScriptStruct* Type, const FName& TypeName, const void* Payload) override;`
- L32 _protected prototype_ `virtual TFuture<FConcertDataStoreResult> InternalFetchAs(const FName& Key, const UScriptStruct* Type, const FName& TypeName) const override;`
- L33 _protected prototype_ `virtual TFuture<FConcertDataStoreResult> InternalCompareExchange(const FName& Key, const UScriptStruct* Type, const FName& TypeName, const void* Expected, const void* Desired) override;`
- L34 _protected prototype_ `virtual void InternalRegisterChangeNotificationHandler(const FName& Key, const FName& TypeName, const FChangeNotificationHandler& Handler, EConcertDataStoreChangeNotificationOptions Options) override;`
- L35 _protected prototype_ `virtual void InternalUnregisterChangeNotificationHandler(const FName& Key) override;`
- L38 _protected prototype_ `FConcertDataStoreResult HandleResponse(const FName& SentKey, const FName& SentValueTypeName, const FConcertSessionSerializedPayload& SentValue, const FConcertDataStore_Response& Response);`
- L41 _protected prototype_ `FConcertDataStoreValueConstPtr GetCachedValue(const FName& Key, const FName& TypeName) const;` — Returns the data store cache, enabling derived classes to read it. Useful for testing purpose.
- L42 _protected prototype_ `int32 GetCacheSize() const;`
- L46 _private prototype_ `void OnReplicationEvent(const FConcertSessionContext& Context, const FConcertDataStore_ReplicateEvent& Event);` — Handle replication events sent by the Concert data store server.
- L49 _private member_ `TSharedRef<FConcertSyncClientLiveSession> LiveSession;` — The session used to dispatch requests.
- L52 _private member_ `mutable FCriticalSection CritSection;` — Critical section to support clients calling from multiple threads.
- L55 _private member_ `FConcertDataStore LocalCache;` — A replicated cache of the server store. Not thread safe by itself. Ensure to lock CritSection before usage.
- L58 _private member_ `TMap<FName, FChangeNotificationHandler> ChangeNotificationHandlers;` — Map the keys observed by the client to its change notification handlers. Ensure to lock CritSection before usage.

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Private/ConcertClientLiveTransactionAuthors.h` (Private)


#### class `FConcertClientLiveTransactionAuthors`  
`class FConcertClientLiveTransactionAuthors`  
_L54-98_
- desc: Tracks which client authored which package using the set of transactions that haven't been saved to disk yet, also known as 'Live Transactions'. The purpose of this class is to answer the question "has anybody, other than this client, modified a package?". This is useful when multiple clients are concurrently editing the same package in the same session. When someone is about to save, it might be important to know if somebody else has modified the package and if so, review the other people changes. This feature is integrated in the editor to visually mark the assets modified by other clients. @par User authentication The UE Editor doesn't use a mechanism like login/password to authenticate a user. To uniquely identify a user, Concert generates a unique GUID for each UE Editor instance. The same person may open/close the editor several times or run multiple instances in parallel. Each editor instance will get a new unique GUID. When the same user runs the editor in parallel, the user will be recognized as two different people. When a user exits the editor (or crash), then rejoins a session from a new editor instance, the implementation will try to match its new identity to its previous one and then assign all live transactions performed using the previous identity to the new identity, if the user name, display name, machine name, ... match. @par Thread-safety This class is currently called form the UI and Concert network layer, both running in the game thread. For this reason,
- L60 _public prototype_ `FConcertClientLiveTransactionAuthors(TSharedRef<FConcertSyncClientLiveSession> InLiveSession);` — Constructor. @param Session This local client session, used to identify this client against other clients connected to the session.
- L63 _public prototype_ `~FConcertClientLiveTransactionAuthors();` — Destructor.
- L70 _public prototype_ `void AddLiveTransactionActivity(const FGuid& EndpointId, TArrayView<const FName> ModifiedPackages);` — Adds live transaction activity @param EndpointId The ID of the endpoint that made the transaction. @param ModifiedPackages The packages that were modified by the transaction.
- L75 _public prototype_ `void ResolveLiveTransactionAuthorsForPackage(const FName& PackageName);` — Gets all live transactions for the given package and processes the author of each transaction to see if they were made by other clients
- L85 _public prototype_ `bool IsPackageAuthoredByOtherClients(const FName& PackageName, int32* OutOtherClientsWithModifNum = nullptr, TArray<FConcertClientInfo>* OutOtherClientsWithModifInfo = nullptr, int32 OtherClientsWithModifMaxFetchNum = 0) const;` — Returns true if the specified packages has live transaction(s) from any other client(s) than the one corresponding to the client session passed at construction and possibly returns information about the other clients. @param[in] PackageName The package name. @param[out] OutOtherClientsWithModifNum If not null, will contain how many other client(s) have modified the specified package. @param[out] OutOtherClientsWithModifInfo If not null, will contain the other client who modified the packages, up to OtherClientsWithModifMaxFetchNum. @param[in] OtherClientsWithModifMaxFetchNum The maximum number of client info to store in OutOtherClientsWithModifInfo if the latter is not null.
- L91 _private prototype_ `void ResolveLiveTransactionAuthors();` — Gets all live transactions and processes the author of each transaction to see if they were made by other clients
- L94 _private member_ `TSharedRef<FConcertSyncClientLiveSession> LiveSession;` — The client session.
- L97 _private member_ `TMap<FName, TArray<FGuid>> OtherEndpointsWithLiveTransactionsMap;` — Maps package names to the list of endpoints (other than this one) that have live transactions on a package.

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Private/ConcertClientLockManager.h` (Private)


#### class `FConcertClientLockManager`  
`class FConcertClientLockManager`  
_L17-91_
- L20 _public prototype_ `explicit FConcertClientLockManager(TSharedRef<FConcertSyncClientLiveSession> InLiveSession);`
- L21 _public prototype_ `~FConcertClientLockManager();`
- L26 _public prototype_ `FGuid GetWorkspaceLockId() const;` — @return the client id this workspace uses to lock resources.
- L31 _public prototype_ `FGuid GetResourceLockId(const FName InResourceName) const;` — @return a valid client id of the owner of this resource lock or an invalid id if unlocked
- L40 _public prototype_ `bool AreResourcesLockedBy(TArrayView<const FName> ResourceNames, const FGuid& ClientId);` — Verify if resources are locked by a particular client @param ResourceNames list of resources path to verify @param ClientId the client id to verify @return true if all resources in ResourceNames are locked by ClientId @note passing an invalid client id will return true if all resources are unlocked
- L47 _public prototype_ `TFuture<FConcertResourceLockResponse> LockResources(TArray<FName> InResourceNames);` — Attempt to lock the given resource. @note Passing force will always assign the lock to the given endpoint, even if currently locked by another. @return True if the resource was locked (or already locked by the given endpoint), false otherwise.
- L54 _public prototype_ `TFuture<FConcertResourceLockResponse> UnlockResources(TArray<FName> InResourceNames);` — Attempt to unlock the given resource. @note Passing force will always clear, even if currently locked by another endpoint. @return True if the resource was unlocked, false otherwise.
- L59 _public prototype_ `void SetLockedResources(const TMap<FName, FGuid>& InLockedResources);` — Set the set of locked resources (resource ID -> endpoint ID).
- L65 _private prototype_ `bool CanSavePackage(UPackage* InPackage, const FString& InFilename, FOutputDevice* ErrorLog);` — Called prior to saving a package to see whether the save should be allowed to proceed.
- L70 _private prototype_ `void CanDeleteAssets(const TArray<UObject*>& InAssetsToDelete, FCanDeleteAssetResult& CanDeleteResult);` — Called prior to deleting a package asset to see whether the delete should be allowed to proceed.
- L75 _private prototype_ `void HandleResourceLockEvent(const FConcertSessionContext& Context, const FConcertResourceLockEvent& Event);` — Called to handle a resource being locked or unlocked by the server.
- L80 _private member_ `TSharedPtr<FConcertSyncClientLiveSession> LiveSession;` — Session instance this package manager was created for.
- L85 _private member_ `TMap<FName, FGuid> LockedResources;` — Tracks locked resources from the server (resource ID -> endpoint ID).
- L89 _private member_ `FCoreUObjectDelegates::FIsPackageOKToSaveDelegate OkToSaveBackupDelegate;`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Private/ConcertClientPackageBridge.h` (Private)


#### class `FConcertClientPackageBridge`  
`class FConcertClientPackageBridge : public IConcertClientPackageBridge`  
_L18-89_
- inherits: `IConcertClientPackageBridge`
- L21 _public prototype_ `FConcertClientPackageBridge();`
- L22 _public prototype_ `virtual ~FConcertClientPackageBridge();`
- L25 _public prototype_ `virtual FOnConcertClientLocalPackageEvent& OnLocalPackageEvent() override;`
- L26 _public prototype_ `virtual FOnConcertClientLocalPackageDiscarded& OnLocalPackageDiscarded() override;`
- L27 _public prototype_ `virtual bool& GetIgnoreLocalSaveRef() override;`
- L28 _public prototype_ `virtual bool& GetIgnoreLocalDiscardRef() override;`
- L30 _public prototype_ `virtual void RegisterPackageHotReloadHint(FName PackageReloadHintName, FPackageHotReloadHintDelegate FilterHandle) override;`
- L31 _public prototype_ `virtual bool CanSkipHotReload(const FConcertPackageInfo& PackageInfo) const override;`
- L32 _public prototype_ `virtual void UnregisterPackageHotReloadHint(FName PackageReloadHintName) override;`
- L34 _public prototype_ `virtual void RegisterPackageFilter(FName FilterName, FPackageFilterDelegate FilterHandle) override;`
- L35 _public prototype_ `virtual void UnregisterPackageFilter(FName FilterName) override;`
- L36 _public prototype_ `virtual EPackageFilterResult IsPackageFiltered(const FConcertPackageInfo& PackageInfo) const override;`
- L42 _private prototype_ `void OnEndFrame();` — Handle any deferred tasks that should be run on the game thread.
- L45 _private prototype_ `void HandlePackagePreSave(UPackage* Package, FObjectPreSaveContext ObjectSavecontext);` — Called prior to a package being saved to disk
- L48 _private prototype_ `void HandlePackageSaved(const FString& PackageFilename, UPackage* Package, FObjectPostSaveContext ObjectSaveContext);` — Called after a package has been saved to disk
- L51 _private prototype_ `void HandleAssetAdded(UObject *Object);` — Called when a new asset is added
- L54 _private prototype_ `void HandleAssetDeleted(UObject *Object);` — Called when an existing asset is deleted
- L57 _private prototype_ `void HandleAssetRenamed(const FAssetData& Data, const FString& OldName);` — Called when an existing asset is renamed
- L60 _private prototype_ `void HandleAssetReload(const EPackageReloadPhase InPackageReloadPhase, FPackageReloadedEvent* InPackageReloadedEvent);` — Called when an asset is hot-reloaded
- L63 _private prototype_ `void HandleMapChanged(UWorld* InWorld, EMapChangeType InMapChangeType);` — Called when the editor map is changed
- L67 _private member_ `FOnConcertClientLocalPackageEvent OnLocalPackageEventDelegate;` — Called when a local package event happens
- L70 _private member_ `FOnConcertClientLocalPackageDiscarded OnLocalPackageDiscardedDelegate;` — Called when a local package discard happens
- L73 _private member_ `TMap<FName, FPackageFilterDelegate> PackageFilters;` — Map of named packages filters that can override what is included / excluded by package bridge
- L76 _private member_ `TMap<FName, FPackageHotReloadHintDelegate> HotReloadHints;` — Map of named hot reload delegates that can provide hints on if packages can skip hot reload, e.g. take records.
- L79 _private member_ `bool bIgnoreLocalSave;` — Flag to ignore package change events, used when we do not want to record package changes we generate ourselves
- L82 _private member_ `bool bIgnoreLocalDiscard;` — Flag to ignore package discards, used when we do not want to record package changes we generate ourselves
- L85 _private member_ `TMap<FName, FName> PackagesBeingRenamed;` — Map of packages that are in the process of being renamed
- L87 _private typedef_ `using FConcertPackageInfoTuple = TTuple<FConcertPackageInfo, FString>;`
- L88 _private member_ `TArray<FConcertPackageInfoTuple> PendingPackageInfos;`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Private/ConcertClientPackageManager.h` (Private)


#### class `FConcertClientPackageManager`  
`class FConcertClientPackageManager`  
_L35-270_
- L45 _public prototype_ `FConcertClientPackageManager( const TSharedRef<FConcertSyncClientLiveSession>& InLiveSession, IConcertClientPackageBridge* InPackageBridge, TSharedPtr<IConcertFileSharingService> InFileSharingService, const FString& InClientRole );` — Construct the package manager for the specified session. @param InLiveSession The session for which the package manager will be used. @param InPackageBridge The package bridge (used by the package manager to register itself for package events) @param InFileSharingService Optional service (can be null) used by the client to exchange very large packages with the server. @param InClientRole Role of the client. Used by sandbox system to generate lock reason text.
- L51 _public prototype_ `~FConcertClientPackageManager();`
- L57 _public prototype_ `bool ShouldIgnorePackageDirtyEvent(class UPackage* InPackage) const;` — Verify if a package dirty event should be ignored, mainly for the purpose of locking @return true if dirty even should be ignored for InPackage
- L62 _public prototype_ `void QueueDirtyPackagesForReload();` — Discard dirty packages changes by queuing them for hot reload
- L67 _public prototype_ `void SynchronizeInMemoryPackages();` — Synchronize any pending updates to in-memory packages (hot-reloads or purges) to keep them up-to-date with the on-disk state.
- L72 _public prototype_ `void HandlePackageDiscarded(UPackage* InPackage);` — Called to handle a local package having its changes discarded.
- L77 _public prototype_ `void HandleRemotePackage(const FGuid& InSourceEndpointId, const int64 InPackageEventId, const bool bApply);` — Called to handle a remote package being received.
- L82 _public prototype_ `void ApplyAllHeadPackageData();` — Called to apply the head revision data for all packages.
- L89 _public prototype_ `bool PassesPackageFilters(UPackage* InPackage) const;` — Run Package filters @param InPackage The package to run the filters on @return true if the package passes the filters (Is not filtered out)
- L95 _public prototype_ `bool HasSessionChanges() const;` — Tell if package changes happened during this session. @return True if the session contains package changes.
- L100 _public prototype_ `TOptional<FString> GetValidPackageSessionPath(FName PackageName) const;` — Returns the full path to the package if it is valid.
- L105 _public prototype_ `FPersistResult PersistSessionChanges(FPersistParameters InParam);` — Persist the session changes from the package name list and prepare it for source control submission.
- L110 _public function_ `FOnConcertClientPackageTooLargeError& OnConcertClientPackageTooLargeError()` — Called when a package is too big to be handled by the system.
- L115 _public prototype_ `bool IsReloadingPackage(FName PackageName) const;` — Returns true if the named package is participating in a package reload.
- L118 _public function_ `void EnqueueHotReload(FName InPackageName)` — Enqueues a package for hot reload.
- L120 _public function_ `void EnqueuePurge(FName InPackageName)` — Enqueues a package for purge.
- L126 _private prototype_ `bool IsFileSharingEnabled() const;` — Is file sharing enabled.
- L131 _private prototype_ `TOptional<FString> GetDeletedPackagePath(FName PackageName) const;` — Returns a full path for given package name if it was deleted and exists on the non-sandbox area.
- L137 _private prototype_ `bool ApplyPackageFilters(const FConcertPackageInfo& InPackageInfo) const;` — Apply the package filters on the package info @return true if the package info passes the filter.
- L142 _private prototype_ `void ApplyPackageUpdate(const FConcertPackageInfo& InPackageInfo, FConcertPackageDataStream& InPackageDataStream);` — Apply the data in the given package to disk and update the in-memory state.
- L147 _private prototype_ `void HandlePackageRejectedEvent(const FConcertSessionContext& InEventContext, const FConcertPackageRejectedEvent& InEvent);` — Handle a rejected package event, those are sent by the server when a package update is refused.
- L153 _private prototype_ `void HandlePackageDirtyStateChanged(UPackage* InPackage);` — Called when the dirty state of a package changed. Used to track currently dirty packages for hot-reload when discarding the manager.
- L158 _private prototype_ `void HandleLocalPackageEvent(const FConcertPackageInfo& PackageInfo, const FString& PackagePathname);` — Called to handle a local package event.
- L164 _private prototype_ `void HandleDuplicateActorsBegin();` — Handle begin event when a duplicate actor is added to the level.
- L169 _private prototype_ `void HandleDuplicateActorsEnd();` — Handle end event when a duplicate actor is added to the level.
- L175 _private prototype_ `void SavePackageFile(const FConcertPackageInfo& PackageInfo, FConcertPackageDataStream& InPackageDataStream);` — Utility to save new package data to disk, and also queue if for hot-reload.
- L180 _private prototype_ `void DeletePackageFile(const FConcertPackageInfo& PackageInfo);` — Utility to remove existing package data from disk, and also queue if for purging.
- L186 _private prototype_ `bool CanHotReloadOrPurge() const;` — Can we currently perform content hot-reloads or purges? True if we are neither suspended nor unable to perform a blocking action, false otherwise.
- L191 _private prototype_ `void HotReloadPendingPackages();` — Hot-reload any pending in-memory packages to keep them up-to-date with the on-disk state.
- L196 _private prototype_ `void PurgePendingPackages();` — Purge any pending in-memory packages to keep them up-to-date with the on-disk state.
- L201 _private prototype_ `bool CanExchangePackageDataAsByteArray(int64 PackageDataSize) const;` — Whether the package data is small enough to be exchanged using a single TArray<> data structure.
- L206 _private prototype_ `void AddPendingReloadForNewExternalMaps(const FConcertPackageInfo& PackageInfo, const FString& PackagePathname);` — World partition nodes need to perform a map reload on initial save but only after all actors have been saved.
- L210 _private member_ `TUniquePtr<UE::ConcertSyncClient::FConcertPackageSandbox> SandboxManager;` — Sandbox for storing package changes to disk within a Concert session.
- L216 _private member_ `TSharedPtr<FConcertSyncClientLiveSession> LiveSession;` — Session instance this package manager was created for.
- L221 _private member_ `IConcertClientPackageBridge* PackageBridge;` — Package bridge used by this manager.
- L227 _private member_ `bool bPromptWhenAddingToLevelBeforeCheckout = false;` — Value of the CurrentWorld()->GetCurrentLevel()->bPromptWhenAddingToLevelBeforeCheckout on the level. We suppress this for sandbox sessions.  This value is only relevant between begin / end delegate on duplicate actors event.
- L232 _private member_ `bool bHotReloading = false;` — Indicates if we are currently hot reloading.
- L237 _private member_ `bool bIgnorePackageDirtyEvent;` — Flag to indicate package dirty event should be ignored.
- L244 _private member_ `TSet<FName> DirtyPackages;` — Set of package names that are currently dirty. Only used to properly track packages that need hot-reloading when discarding the manager but currently escape the sandbox and live transaction tracking.
- L249 _private member_ `TArray<FName> PackagesPendingHotReload;` — Array of package names that are pending a content hot-reload.
- L254 _private member_ `TArray<FName> PackagesPendingPurge;` — Array of package names that are pending an in-memory purge.
- L259 _private member_ `FOnConcertClientPackageTooLargeError OnPackageTooLargeErrorDelegate;` — Called when a package is too large to be handled by the system.
- L264 _private member_ `TSharedPtr<IConcertFileSharingService> FileSharingService;` — Optional side channel to exchange large blobs (package data) with the server in a scalable way (ex. the request/response transport layer is not designed and doesn't support exchanging 3GB packages).
- L269 _private member_ `TSet<FName> EmittedPristinePackages;` — Keep the list of package for which the pristine state was sent. Used if the session doesn't support live sync.

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace ConcertSyncClient` (scope `UE`)
- L33 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnConcertClientPackageTooLargeError, const FConcertPackageInfo& , int64 , int64 );` — Invoked when a package is too large to be sent to the server if the transport protocol doesn't support large file.
- L33 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnConcertClientPackageTooLargeError, const FConcertPackageInfo& , int64 , int64 );` — Invoked when a package is too large to be sent to the server if the transport protocol doesn't support large file.

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Private/ConcertClientPresenceManager.h` (Private)


#### struct `FConcertClientPresenceStateEntry`  
`struct FConcertClientPresenceStateEntry`  
_L24-33_
- desc: Remote client event items
- L26 _public prototype_ `FConcertClientPresenceStateEntry(TSharedRef<FConcertClientPresenceEventBase> InPresenceEvent);`
- L29 _public member_ `TSharedRef<FConcertClientPresenceEventBase> PresenceEvent;` — Presence state
- L32 _public member_ `bool bSyncPending;` — Whether state needs to be synchronized to actor

#### struct `FConcertClientPresenceState`  
`struct FConcertClientPresenceState`  
_L36-63_
- desc: State for remote clients associated with client id
- L38 _public prototype_ `FConcertClientPresenceState();`
- L41 _public member_ `TMap<UScriptStruct*, FConcertClientPresenceStateEntry> EventStateMap;` — State map
- L44 _public member_ `FString DisplayName;` — Display name
- L47 _public member_ `FLinearColor AvatarColor;` — Avatar color.
- L50 _public member_ `bool bIsConnected;` — Whether client is connected
- L53 _public member_ `EEditorPlayMode EditorPlayMode;` — The editor play mode (PIE/SIE/None).
- L56 _public member_ `bool bVisible;` — Whether client is visible
- L59 _public member_ `FName VRDevice;` — Whether client is using a VRDevice
- L62 _public member_ `TWeakObjectPtr<AConcertClientPresenceActor> PresenceActor;` — Presence actor

#### struct `FConcertClientPresencePersistentState`  
`struct FConcertClientPresencePersistentState`  
_L66-75_
- desc: State that persists beyond remote client sessions, associated with display name
- L68 _public prototype_ `FConcertClientPresencePersistentState();`
- L71 _public member_ `bool bVisible;` — Whether client is visible
- L74 _public member_ `bool bPropagateToAll;` — Whether the visibility of this client should be propagated to others?

#### class `FConcertClientPresenceManager`  
`class FConcertClientPresenceManager : public TSharedFromThis<FConcertClientPresenceManager>, public FGCObject, public IConcertClientPresenceManager`  
_L77-285_
- inherits: `TSharedFromThis<FConcertClientPresenceManager>,FGCObject,IConcertClientPresenceManager`
- L80 _public prototype_ `FConcertClientPresenceManager(TSharedRef<IConcertClientSession> InSession);`
- L81 _public prototype_ `~FConcertClientPresenceManager();`
- L84 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L85 _public function_ `virtual FString GetReferencerName() const override`
- L91 _public prototype_ `const class UConcertAssetContainer& GetAssetContainer() const;` — Gets the container for all the assets of Concert clients.
- L94 _public prototype_ `bool IsInGame() const;` — Returns true if current session is in Game (i.e. !GIsEditor)
- L97 _public prototype_ `bool IsInPIE() const;` — Returns true if current session is in PIE
- L100 _public prototype_ `bool IsInSIE() const;` — Returns true if current session is in SIE
- L107 _public prototype_ `UWorld* GetWorld(bool bIgnorePIE = false) const;` — Get the current world @param bIgnorePIE if bIgnorePIE is true will still return the editor world even if an PIE world exists. @return the current world
- L110 _public prototype_ `FLevelEditorViewportClient * GetPerspectiveViewport() const;` — Get the active perspective viewport
- L113 _public prototype_ `virtual void SetPresenceModeFactory(TSharedRef<IConcertClientPresenceModeFactory> InFactory) override;` — Set the presence mode factory.
- L116 _public prototype_ `virtual void SetPresenceEnabled(const bool bIsEnabled = true) override;` — Set whether presence is currently enabled and should be shown (unless hidden by other settings)
- L119 _public prototype_ `virtual void SetPresenceVisibility(const FString& InDisplayName, bool bVisibility, bool bPropagateToAll = false) override;` — Set presence visibility by name
- L122 _public prototype_ `virtual void SetPresenceVisibility(const FGuid& EndpointId, bool bVisibility, bool bPropagateToAll = false) override;` — Set Presence visibility by client id.
- L125 _public prototype_ `virtual FTransform GetPresenceTransform(const FGuid& EndpointId) const override;` — Get the presence transform
- L128 _public prototype_ `virtual void InitiateJumpToPresence(const FGuid& InEndpointId, const FTransform& InTransformOffset = FTransform::Identity) override;` — Jump (teleport) to another presence
- L131 _public prototype_ `static double GetLocationUpdateFrequency();` — Get location update frequency
- L144 _public prototype_ `virtual FString GetPresenceWorldPath(const FGuid& InEndpointId, EEditorPlayMode& OutEditorPlayMode) const override;` — Returns the path to the UWorld object opened in the editor of the specified client endpoint. The information may be unavailable if the client was disconnected, the information hasn't replicated yet or the code was not compiled as part of the UE Editor. This function always returns the editor context world path, never the PIE/SIE context world path (which contains a UEDPIE_%d_ decoration embedded) even if the user is in PIE or SIE. For example, the PIE/SIE context world path would look like '/Game/UEDPIE_10_FooMap.FooMap' while the editor context world returned by this function looks like '/Game/FooMap.FooMap'. @param[in] EndpointId The end point of a clients connected to the session (local or remote). @param[out] OutEditorPlayMode Indicates if the client corresponding to the end point is in PIE, SIE or simply editing. @return The path to the world being opened in the specified end point editor or an empty string if the information is not available.
- L151 _public prototype_ `void GetPresenceClientActions(const FConcertSessionClientInfo& InClientInfo, TArray<FConcertActionDefinition>& OutActions);` — Returns presence action specific that can be performed with the specified client, like jumping to this client presence. @param InClientInfo The client for which the actions must be defined. @param OutActions The available action for this client.
- L156 _private prototype_ `void Register();` — Register event and delegate handlers
- L159 _private prototype_ `void Unregister();` — Unregister event and delegate handlers
- L162 _private prototype_ `bool IsPresenceVisible(const FConcertClientPresenceState& InPresenceState) const;` — Is presence visible for the given state?
- L165 _private prototype_ `bool IsPIEPresenceEnabled(const FConcertClientPresenceState& InPresenceState) const;` — Return if PIE presence is potentially visible for a state.
- L168 _private prototype_ `bool IsPresenceVisible(const FGuid& InEndpointId) const;` — Is presence visible for the given endpoint id?
- L171 _private prototype_ `void OnEndFrame();` — Handles end-of-frame updates
- L174 _private prototype_ `void SynchronizePresenceState();` — Synchronize presence state
- L177 _private prototype_ `const TSharedPtr<FConcertClientPresenceDataUpdateEvent> GetCachedPresenceState(const FConcertClientPresenceState& InPresenceState) const;` — Get cached presence state for given endpoint id
- L180 _private prototype_ `const TSharedPtr<FConcertClientPresenceDataUpdateEvent> GetCachedPresenceState(const FGuid& InEndpointId) const;` — Get cached presence state for given endpoint id
- L184 _private prototype_ `template<class PresenceActorClass, typename PresenceUpdateEventType> void UpdatePresence(AConcertClientPresenceActor* InPresenceActor, const PresenceUpdateEventType& InEvent);` — Update existing presence with event data
- L188 _private prototype_ `template<typename PresenceUpdateEventType> void HandleConcertClientPresenceUpdateEvent(const FConcertSessionContext& InSessionContext, const PresenceUpdateEventType& InEvent);` — Handle a presence data update from another client session
- L191 _private prototype_ `void HandleConcertClientPresenceVisibilityUpdateEvent(const FConcertSessionContext& InSessionContext, const FConcertClientPresenceVisibilityUpdateEvent& InEvent);` — Handle a presence visibility update from another client session
- L194 _private prototype_ `bool ShouldProcessPresenceEvent(const FConcertSessionContext& InSessionContext, const UStruct* InEventType, const FConcertClientPresenceEventBase& InEvent) const;` — Returns true if presence event was not received out-of-order
- L197 _private prototype_ `AConcertClientPresenceActor* CreatePresenceActor(const FConcertClientInfo& InClientInfo, FName VRDevice);` — Create a new presence actor
- L200 _private prototype_ `AConcertClientPresenceActor* SpawnPresenceActor(const FConcertClientInfo& InClientInfo, FName VRDevice);` — Spawn a presence actor
- L203 _private prototype_ `void ClearPresenceActor(const FGuid& InEndpointId);` — Clear presence
- L206 _private prototype_ `void DestroyPresenceActor(TWeakObjectPtr<AConcertClientPresenceActor> PresenceActor);` — Destroy a presence
- L209 _private prototype_ `void ClearAllPresenceState();` — Clear all presence
- L212 _private prototype_ `void HandleConcertPlaySessionEvent(const FConcertSessionContext& InSessionContext, const FConcertPlaySessionEvent &InEvent);` — Handle a play session update from another client session
- L215 _private prototype_ `void OnSessionClientChanged(IConcertClientSession& InSession, EConcertClientStatus InClientStatus, const FConcertSessionClientInfo& InClientInfo);` — Handle a client session disconnect
- L218 _private prototype_ `void SendPresenceInVREvent(const FGuid* InEndpointId = nullptr);` — Notifies other clients to update avatar for this client
- L221 _private prototype_ `void HandleConcertClientPresenceInVREvent(const FConcertSessionContext& InSessionContext, const FConcertClientPresenceInVREvent& InEvent);` — Handle a presence in VR update from another client session
- L224 _private prototype_ `void UpdatePresenceAvatar(const FGuid& InEndpointId, FName VRDevice);` — Updates presence avatar for remote client by invalidating current presence actor
- L227 _private prototype_ `void TogglePresenceVisibility(const FGuid& InEndpointId, bool bPropagateToAll = false);` — Toggle presence visibility
- L230 _private prototype_ `FConcertClientPresenceState& EnsurePresenceState(const FGuid& InEndpointId);` — Ensure presence state info for client session
- L233 _private prototype_ `bool IsJumpToPresenceEnabled(FGuid InEndpointId) const;` — Is the jump-to button enabled for the given endpoint?
- L236 _private prototype_ `void OnJumpToPresence(FGuid InEndpointId, FTransform InTransformOffset);` — Handle the show/hide button being clicked for the given endpoint
- L239 _private prototype_ `bool IsShowHidePresenceEnabled(FGuid InEndpointId) const;` — Is the show/hide button enabled for the given endpoint?
- L242 _private prototype_ `FText GetShowHidePresenceText(FGuid InEndpointId) const;` — Get the correct show/hide text for the given endpoint
- L245 _private prototype_ `FName GetShowHidePresenceIconStyle(FGuid InEndpointId) const;` — Get the correct show/hide icon style for the given endpoint
- L248 _private prototype_ `FText GetShowHidePresenceToolTip(FGuid InEndpointId) const;` — Get the correct show/hide tooltip for the given endpoint
- L251 _private prototype_ `void OnShowHidePresence(FGuid InEndpointId);` — Handle the show/hide button being clicked for the given endpoint
- L254 _private member_ `TSharedRef<IConcertClientSession> Session;` — Session Pointer
- L257 _private member_ `TSharedPtr<IConcertClientPresenceModeFactory> PresenceModeFactory;` — Factory in charge of creating presence mode and avatar.
- L260 _private member_ `TUniquePtr<IConcertClientBasePresenceMode> CurrentAvatarMode;` — Presence avatar mode for this client
- L263 _private member_ `static const TCHAR* AssetContainerPath;` — The asset container path
- L266 _private member_ `TObjectPtr<class UConcertAssetContainer> AssetContainer;` — Container of assets
- L269 _private member_ `bool bIsPresenceEnabled;` — True if presence is currently enabled and should be shown (unless hidden by other settings)
- L272 _private member_ `TMap<FString, TObjectPtr<UClass>> OthersAvatarClasses;` — The list of loaded classes representing remote clients avatar.
- L275 _private member_ `TMap<FGuid, FConcertClientPresenceState> PresenceStateMap;` — Presence state associated with remote client id
- L278 _private member_ `TMap<FString, FConcertClientPresencePersistentState> PresencePersistentStateMap;` — Presence state associated with client display name
- L281 _private member_ `double PreviousEndFrameTime;` — Time of previous call to OnEndFrame
- L284 _private member_ `double SecondsSinceLastLocationUpdate;` — Time since last location update for this client

#### class `FConcertClientDefaultPresenceModeFactory`  
`class FConcertClientDefaultPresenceModeFactory : public IConcertClientPresenceModeFactory`  
_L290-317_
- inherits: `IConcertClientPresenceModeFactory`
- desc: Implementation for the default PresenceMode factory
- L293 _public prototype_ `FConcertClientDefaultPresenceModeFactory(FConcertClientPresenceManager* InManager);`
- L294 _public prototype_ `virtual ~FConcertClientDefaultPresenceModeFactory();`
- L296 _public prototype_ `virtual bool ShouldResetPresenceMode() const override;`
- L297 _public prototype_ `virtual TUniquePtr<IConcertClientBasePresenceMode> CreatePresenceMode() override;`
- L298 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L301 _private prototype_ `void OnVREditingModeEnter();` — Handle entering VR
- L304 _private prototype_ `void OnVREditingModeExit();` — Handle exiting VR
- L307 _private prototype_ `void QueryVRDeviceType();` — Determine new value for VRDeviceType based on current mode
- L310 _private member_ `FConcertClientPresenceManager* Manager;` — Holds the manager.
- L313 _private member_ `FName VRDeviceType;` — Holds the vr device type, NAME_None if not in VR.
- L316 _private member_ `bool bShouldResetPresenceMode;` — Flag to indicate the presence mode should be recreated from the factory.

#### class `FConcertClientPresenceManager`  
`class FConcertClientPresenceManager`  
_L321-325_
- L80 _public prototype_ `FConcertClientPresenceManager(TSharedRef<IConcertClientSession> InSession);`
- L81 _public prototype_ `~FConcertClientPresenceManager();`
- L84 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L85 _public function_ `virtual FString GetReferencerName() const override`
- L91 _public prototype_ `const class UConcertAssetContainer& GetAssetContainer() const;` — Gets the container for all the assets of Concert clients.
- L94 _public prototype_ `bool IsInGame() const;` — Returns true if current session is in Game (i.e. !GIsEditor)
- L97 _public prototype_ `bool IsInPIE() const;` — Returns true if current session is in PIE
- L100 _public prototype_ `bool IsInSIE() const;` — Returns true if current session is in SIE
- L107 _public prototype_ `UWorld* GetWorld(bool bIgnorePIE = false) const;` — Get the current world @param bIgnorePIE if bIgnorePIE is true will still return the editor world even if an PIE world exists. @return the current world
- L110 _public prototype_ `FLevelEditorViewportClient * GetPerspectiveViewport() const;` — Get the active perspective viewport
- L113 _public prototype_ `virtual void SetPresenceModeFactory(TSharedRef<IConcertClientPresenceModeFactory> InFactory) override;` — Set the presence mode factory.
- L116 _public prototype_ `virtual void SetPresenceEnabled(const bool bIsEnabled = true) override;` — Set whether presence is currently enabled and should be shown (unless hidden by other settings)
- L119 _public prototype_ `virtual void SetPresenceVisibility(const FString& InDisplayName, bool bVisibility, bool bPropagateToAll = false) override;` — Set presence visibility by name
- L122 _public prototype_ `virtual void SetPresenceVisibility(const FGuid& EndpointId, bool bVisibility, bool bPropagateToAll = false) override;` — Set Presence visibility by client id.
- L125 _public prototype_ `virtual FTransform GetPresenceTransform(const FGuid& EndpointId) const override;` — Get the presence transform
- L128 _public prototype_ `virtual void InitiateJumpToPresence(const FGuid& InEndpointId, const FTransform& InTransformOffset = FTransform::Identity) override;` — Jump (teleport) to another presence
- L131 _public prototype_ `static double GetLocationUpdateFrequency();` — Get location update frequency
- L144 _public prototype_ `virtual FString GetPresenceWorldPath(const FGuid& InEndpointId, EEditorPlayMode& OutEditorPlayMode) const override;` — Returns the path to the UWorld object opened in the editor of the specified client endpoint. The information may be unavailable if the client was disconnected, the information hasn't replicated yet or the code was not compiled as part of the UE Editor. This function always returns the editor context world path, never the PIE/SIE context world path (which contains a UEDPIE_%d_ decoration embedded) even if the user is in PIE or SIE. For example, the PIE/SIE context world path would look like '/Game/UEDPIE_10_FooMap.FooMap' while the editor context world returned by this function looks like '/Game/FooMap.FooMap'. @param[in] EndpointId The end point of a clients connected to the session (local or remote). @param[out] OutEditorPlayMode Indicates if the client corresponding to the end point is in PIE, SIE or simply editing. @return The path to the world being opened in the specified end point editor or an empty string if the information is not available.
- L151 _public prototype_ `void GetPresenceClientActions(const FConcertSessionClientInfo& InClientInfo, TArray<FConcertActionDefinition>& OutActions);` — Returns presence action specific that can be performed with the specified client, like jumping to this client presence. @param InClientInfo The client for which the actions must be defined. @param OutActions The available action for this client.
- L156 _private prototype_ `void Register();` — Register event and delegate handlers
- L159 _private prototype_ `void Unregister();` — Unregister event and delegate handlers
- L162 _private prototype_ `bool IsPresenceVisible(const FConcertClientPresenceState& InPresenceState) const;` — Is presence visible for the given state?
- L165 _private prototype_ `bool IsPIEPresenceEnabled(const FConcertClientPresenceState& InPresenceState) const;` — Return if PIE presence is potentially visible for a state.
- L168 _private prototype_ `bool IsPresenceVisible(const FGuid& InEndpointId) const;` — Is presence visible for the given endpoint id?
- L171 _private prototype_ `void OnEndFrame();` — Handles end-of-frame updates
- L174 _private prototype_ `void SynchronizePresenceState();` — Synchronize presence state
- L177 _private prototype_ `const TSharedPtr<FConcertClientPresenceDataUpdateEvent> GetCachedPresenceState(const FConcertClientPresenceState& InPresenceState) const;` — Get cached presence state for given endpoint id
- L180 _private prototype_ `const TSharedPtr<FConcertClientPresenceDataUpdateEvent> GetCachedPresenceState(const FGuid& InEndpointId) const;` — Get cached presence state for given endpoint id
- L184 _private prototype_ `template<class PresenceActorClass, typename PresenceUpdateEventType> void UpdatePresence(AConcertClientPresenceActor* InPresenceActor, const PresenceUpdateEventType& InEvent);` — Update existing presence with event data
- L188 _private prototype_ `template<typename PresenceUpdateEventType> void HandleConcertClientPresenceUpdateEvent(const FConcertSessionContext& InSessionContext, const PresenceUpdateEventType& InEvent);` — Handle a presence data update from another client session
- L191 _private prototype_ `void HandleConcertClientPresenceVisibilityUpdateEvent(const FConcertSessionContext& InSessionContext, const FConcertClientPresenceVisibilityUpdateEvent& InEvent);` — Handle a presence visibility update from another client session
- L194 _private prototype_ `bool ShouldProcessPresenceEvent(const FConcertSessionContext& InSessionContext, const UStruct* InEventType, const FConcertClientPresenceEventBase& InEvent) const;` — Returns true if presence event was not received out-of-order
- L197 _private prototype_ `AConcertClientPresenceActor* CreatePresenceActor(const FConcertClientInfo& InClientInfo, FName VRDevice);` — Create a new presence actor
- L200 _private prototype_ `AConcertClientPresenceActor* SpawnPresenceActor(const FConcertClientInfo& InClientInfo, FName VRDevice);` — Spawn a presence actor
- L203 _private prototype_ `void ClearPresenceActor(const FGuid& InEndpointId);` — Clear presence
- L206 _private prototype_ `void DestroyPresenceActor(TWeakObjectPtr<AConcertClientPresenceActor> PresenceActor);` — Destroy a presence
- L209 _private prototype_ `void ClearAllPresenceState();` — Clear all presence
- L212 _private prototype_ `void HandleConcertPlaySessionEvent(const FConcertSessionContext& InSessionContext, const FConcertPlaySessionEvent &InEvent);` — Handle a play session update from another client session
- L215 _private prototype_ `void OnSessionClientChanged(IConcertClientSession& InSession, EConcertClientStatus InClientStatus, const FConcertSessionClientInfo& InClientInfo);` — Handle a client session disconnect
- L218 _private prototype_ `void SendPresenceInVREvent(const FGuid* InEndpointId = nullptr);` — Notifies other clients to update avatar for this client
- L221 _private prototype_ `void HandleConcertClientPresenceInVREvent(const FConcertSessionContext& InSessionContext, const FConcertClientPresenceInVREvent& InEvent);` — Handle a presence in VR update from another client session
- L224 _private prototype_ `void UpdatePresenceAvatar(const FGuid& InEndpointId, FName VRDevice);` — Updates presence avatar for remote client by invalidating current presence actor
- L227 _private prototype_ `void TogglePresenceVisibility(const FGuid& InEndpointId, bool bPropagateToAll = false);` — Toggle presence visibility
- L230 _private prototype_ `FConcertClientPresenceState& EnsurePresenceState(const FGuid& InEndpointId);` — Ensure presence state info for client session
- L233 _private prototype_ `bool IsJumpToPresenceEnabled(FGuid InEndpointId) const;` — Is the jump-to button enabled for the given endpoint?
- L236 _private prototype_ `void OnJumpToPresence(FGuid InEndpointId, FTransform InTransformOffset);` — Handle the show/hide button being clicked for the given endpoint
- L239 _private prototype_ `bool IsShowHidePresenceEnabled(FGuid InEndpointId) const;` — Is the show/hide button enabled for the given endpoint?
- L242 _private prototype_ `FText GetShowHidePresenceText(FGuid InEndpointId) const;` — Get the correct show/hide text for the given endpoint
- L245 _private prototype_ `FName GetShowHidePresenceIconStyle(FGuid InEndpointId) const;` — Get the correct show/hide icon style for the given endpoint
- L248 _private prototype_ `FText GetShowHidePresenceToolTip(FGuid InEndpointId) const;` — Get the correct show/hide tooltip for the given endpoint
- L251 _private prototype_ `void OnShowHidePresence(FGuid InEndpointId);` — Handle the show/hide button being clicked for the given endpoint
- L254 _private member_ `TSharedRef<IConcertClientSession> Session;` — Session Pointer
- L257 _private member_ `TSharedPtr<IConcertClientPresenceModeFactory> PresenceModeFactory;` — Factory in charge of creating presence mode and avatar.
- L260 _private member_ `TUniquePtr<IConcertClientBasePresenceMode> CurrentAvatarMode;` — Presence avatar mode for this client
- L263 _private member_ `static const TCHAR* AssetContainerPath;` — The asset container path
- L266 _private member_ `TObjectPtr<class UConcertAssetContainer> AssetContainer;` — Container of assets
- L269 _private member_ `bool bIsPresenceEnabled;` — True if presence is currently enabled and should be shown (unless hidden by other settings)
- L272 _private member_ `TMap<FString, TObjectPtr<UClass>> OthersAvatarClasses;` — The list of loaded classes representing remote clients avatar.
- L275 _private member_ `TMap<FGuid, FConcertClientPresenceState> PresenceStateMap;` — Presence state associated with remote client id
- L278 _private member_ `TMap<FString, FConcertClientPresencePersistentState> PresencePersistentStateMap;` — Presence state associated with client display name
- L281 _private member_ `double PreviousEndFrameTime;` — Time of previous call to OnEndFrame
- L284 _private member_ `double SecondsSinceLastLocationUpdate;` — Time since last location update for this client

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Private/ConcertClientPresenceMode.h` (Private)


#### class `FConcertClientBasePresenceMode`  
`class FConcertClientBasePresenceMode : public IConcertClientBasePresenceMode`  
_L21-57_
- inherits: `IConcertClientBasePresenceMode`
- desc: Implementation of the Base Presence Mode
- L24 _public function_ `explicit FConcertClientBasePresenceMode(class FConcertClientPresenceManager* InManager, FName InVRDeviceType) : LastHeadTransform(FTransform::Identity) , ParentManager(InManager) , VRDeviceType(InVRDeviceType)`
- L29 _public prototype_ `virtual ~FConcertClientBasePresenceMode() = default;`
- L32 _public prototype_ `virtual void SendEvents(IConcertClientSession& Session) override;` — IConcertClientBasePresenceMode implementation
- L33 _public prototype_ `virtual FTransform GetTransform() override;`
- L34 _public function_ `virtual FName GetVRDeviceType() const override`
- L38 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override`
- L42 _protected prototype_ `void SetUpdateIndex(IConcertClientSession& Session, const FName& InEventName, FConcertClientPresenceEventBase& OutEvent);` — Set event update index on an event, used for out-of-order event handling
- L44 _protected function_ `class FConcertClientPresenceManager* GetManager() const`
- L50 _protected member_ `FTransform LastHeadTransform;` — Last head transform returned.
- L53 _protected member_ `class FConcertClientPresenceManager* ParentManager;` — Parent manager
- L56 _protected member_ `FName VRDeviceType;` — Holds the vr device type name, if any.

#### class `FConcertClientDesktopPresenceMode`  
`class FConcertClientDesktopPresenceMode : public FConcertClientBasePresenceMode`  
_L59-72_
- inherits: `FConcertClientBasePresenceMode`
- L62 _public function_ `explicit FConcertClientDesktopPresenceMode(class FConcertClientPresenceManager* InManager) : FConcertClientBasePresenceMode(InManager, NAME_None)`
- L64 _public prototype_ `virtual ~FConcertClientDesktopPresenceMode() = default;`
- L67 _public prototype_ `virtual void SendEvents(IConcertClientSession& Session) override;` — Send events for this presence mode
- L71 _protected member_ `FIntPoint CachedDesktopCursorLocation;` — Cached desktop cursor location to avoid resending changes when mouse did not move

#### class `FConcertClientVRPresenceMode`  
`class FConcertClientVRPresenceMode : public FConcertClientBasePresenceMode`  
_L74-91_
- inherits: `FConcertClientBasePresenceMode`
- L77 _public function_ `explicit FConcertClientVRPresenceMode(class FConcertClientPresenceManager* InManager, FName InVRDeviceType) : FConcertClientBasePresenceMode(InManager, MoveTemp(InVRDeviceType)) , LastRoomTransform(FTransform::Identity)`
- L80 _public prototype_ `virtual ~FConcertClientVRPresenceMode() = default;`
- L83 _public prototype_ `virtual void SendEvents(IConcertClientSession& Session) override;` — Send events for this presence mode
- L87 _protected prototype_ `FTransform GetRoomTransform();` — Get the current room transformation
- L90 _protected member_ `FTransform LastRoomTransform;` — Last room transform returned.

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Private/ConcertClientSequencerManager.h` (Private)


#### class `FConcertClientSequencerManager`  
`class FConcertClientSequencerManager : public FGCObject, public IConcertClientSequencerManager`  
_L33-424_
- inherits: `FGCObject,IConcertClientSequencerManager`
- desc: Sequencer manager that is held by the client sync module that keeps track of open sequencer UIs, regardless of whether a session is open or not Events are registered to client sessions that will then operate on any tracked sequencer UIs
- L39 _public prototype_ `explicit FConcertClientSequencerManager(IConcertSyncClient* InOwnerSyncClient);` — Constructor - registers OnSequencerCreated handler with the sequencer module
- L44 _public prototype_ `virtual ~FConcertClientSequencerManager();` — Destructor - unregisters OnSequencerCreated handler from the sequencer module
- L51 _public prototype_ `void Register(TSharedRef<IConcertClientSession> InSession);` — Register all custom sequencer events for the specified client session @param InSession       The client session to register custom events with
- L59 _public prototype_ `void Unregister(TSharedRef<IConcertClientSession> InSession);` — Unregister previously registered custom sequencer events from the specified client session @param InSession       The client session to unregister custom events from
- L64 _public prototype_ `virtual bool IsSequencerPlaybackSyncEnabled() const override;` — @return true if playback syncing across opened sequencer is enabled
- L71 _public prototype_ `virtual void SetSequencerPlaybackSync(bool bEnable) override;` — Set the playback syncing option in Multi-User which syncs playback across user for opened sequencer. @param bEnable The value to set for playback syncing of opened sequencer
- L76 _public prototype_ `virtual bool IsUnrelatedSequencerTimelineSyncEnabled() const override;` — @return true if unrelated timeline syncing across opened sequencer is enabled
- L83 _public prototype_ `virtual void SetUnrelatedSequencerTimelineSync(bool bEnable) override;` — Set the unrelated timeline syncing option in Multi-User which syncs time from any remote sequence. @param bEnable The value to set for unrelated timeline syncing.
- L88 _public prototype_ `virtual bool IsSequencerRemoteOpenEnabled() const override;` — @return true if the remote open option is enabled.
- L93 _public prototype_ `virtual bool IsSequencerRemoteCloseEnabled() const override;` — @return true if the remote close option is enabled.
- L98 _public prototype_ `virtual bool IsSequencerPacingEnabled() const override;` — @return true if the sequencer pacer is enabled.
- L103 _public prototype_ `virtual float SequencerPacingDuration() const override;` — @return the current duration for the sequencer pacer.
- L110 _public prototype_ `bool ShouldAlwaysCloseGameSequencerPlayer() const;` — Checks the CVar to see if we are allowed to forcefully close the player on game instances. @return true if we should always close a sequence player on a -game instance.
- L118 _public prototype_ `virtual void SetSequencerRemoteOpen(bool bEnable) override;` — Set the remote open option in Multi-User which opens Sequencer for other users when this option is enabled on both user machines. @param bEnable The value to set for the remote open option
- L126 _public prototype_ `virtual void SetSequencerRemoteClose(bool bEnable) override;` — Set the remote close option in Multi-User which closes Sequencer for this user when the sequence is closed by a remote user. @param bEnable The value to set for the remote close option
- L133 _public prototype_ `virtual void SetSequencerPacingEnabled(bool bEnable) override;` — Specifies the sequencer pacing behavior while in a session.  This will set Concert.SequencerStatePacingEnabled console variable. @param bValue The value to be set for the sequencer pacing option
- L140 _public prototype_ `virtual void SetSequencerPacingDuration(float Duration) override;` — Sets the sequencer pacing duration if pacing is enabled. This will set Concert.SequencerStatePacingDuration console variable. @param Duration The spacing between state event messages.  The default value is 1.0
- L145 _public prototype_ `virtual void SuspendSequencerPacing() override;` — Temporarily suspend sequencer pacing on this client.
- L150 _public prototype_ `virtual void ResumeSequencerPacing() override;` — Resume sequencer pacing on this client if the console variable is enabled.
- L153 _public prototype_ `void SetActiveWorkspace(TSharedPtr<FConcertClientWorkspace> Workspace);` — Assign the current active workspace to this sequencer.
- L190 _private prototype_ `bool CanSendSequencerEvent(const FString& ObjectPath) const;` — Returns true if we can send the provided sequencer event onto the server.
- L196 _private prototype_ `void HandleAssetReload(const EPackageReloadPhase InPackageReloadPhase, FPackageReloadedEvent* InPackageReloadedEvent);` — Delegate function called when we have entered into a reload state. We need to know when we are in a asset reload so that we can properly reload the sequence player.
- L203 _private prototype_ `void OnSequencerClosed(TSharedRef<ISequencer> InSequencer);` — Called when a sequencer closes. @param InSequencer The sequencer that closed.
- L211 _private prototype_ `void OnTransportEvent(const FConcertSessionContext&, const FConcertSequencerStateEvent& InEvent);` — Called on receipt of an external transport event from another client @param InEventContext              The context for the current client session @param InEvent                     The sequencer transport event received from the client
- L219 _private prototype_ `void OnCloseEvent(const FConcertSessionContext&, const FConcertSequencerCloseEvent& InEvent);` — Called on receipt of an external close event from the server @param InEventContext              The context for the current client session @param InEvent                     The sequencer close event received from the server
- L227 _private prototype_ `void OnOpenEvent(const FConcertSessionContext&, const FConcertSequencerOpenEvent& InEvent);` — Called on receipt of an external open event from the server @param InEventContext              The context for the current client session @param InEvent                     The sequencer open event received from the server
- L235 _private prototype_ `void OnStateSyncEvent(const FConcertSessionContext& InEventContext, const FConcertSequencerStateSyncEvent& InEvent);` — Called on receipt of an external state sync event from the server @param InEventContext              The context for the current client session @param InEvent                     The sequencer state sync event received from the server
- L242 _private prototype_ `void OnTimeAdjustmentEvent(const FConcertSessionContext& InEventContext, const FConcertSequencerTimeAdjustmentEvent& InEvent);` — Called on receipt of an external time adjustment event from the server @param InEventContext             The context for the current session. @param InEvent                    The sequencer time adjustment event.
- L249 _private prototype_ `void OnSequencerTimeChanged(TWeakPtr<ISequencer> InSequencer);` — Called when the global time has been changed for the specified Sequencer @param InSequencer                 The sequencer that has just updated its time
- L256 _private prototype_ `void OnSequencerCreated(TSharedRef<ISequencer> InSequencer);` — Handle the creation of a newly opened sequencer instance @param InSequencer                 The sequencer that has just been created. Should not hold persistent shared references.
- L265 _private prototype_ `void OnWorkspaceEndFrameCompleted();` — Handle the end of frame callback to apply pending sequencer events. Note that this is called through a delegate on the workspace instead of being called directly by a core engine delegate. This is to ensure that all workspace operations have completed first.
- L272 _private prototype_ `void ApplyOpenEvent(const FConcertSequencerOpenEvent& InOpenEvent);` — Apply a Sequencer open event @param SequenceObjectPath	The sequence to open
- L279 _private prototype_ `void CreateNewSequencePlayerIfNotExists(const FString& SequenceObjectPath);` — Create a new sequence player to be used in -game instances. @param SequenceObjectPath	The object path for the Level Sequence object we are creating.
- L286 _private prototype_ `void ApplyTransportEvent(const FConcertSequencerState& PendingState);` — Apply a Sequencer event @param PendingState	The pending state to apply
- L293 _private prototype_ `void ApplyEventToSequencers(const FConcertSequencerState& PendingState);` — Apply a Sequencer event to opened Sequencers @param PendingState	The pending state to apply
- L300 _private prototype_ `void ApplyEventToPlayers(const FConcertSequencerState& PendingState);` — Apply a Sequencer event to SequencePlayers @param PendingState	The pending state to apply
- L309 _private prototype_ `void ApplyCloseEventToPlayers(const FConcertSequencerCloseEvent& CloseEvent);` — Apply a Sequencer close event to open players. This is a helper function called by ApplyCloseEvent(). @param CloseEvent  The close event state
- L316 _private prototype_ `void ApplyCloseEvent(const FConcertSequencerCloseEvent& CloseEvent);` — Apply a Sequencer close event to open Sequencers and players. @param CloseEvent  The close event state
- L323 _private prototype_ `void ApplyTimeAdjustmentEvent(const FConcertSequencerTimeAdjustmentEvent& TimeAdjustmentEvent);` — Apply a sequencer time adjustment event. @param TimeAdjustmentEvent  The time adjustment event state
- L330 _private prototype_ `void ApplyTimeAdjustmentToPlayers(const FConcertSequencerTimeAdjustmentEvent& TimeAdjustmentEvent);` — Apply a sequencer time adjustment to players. @param TimeAdjustmentEvent  The time adjustment event state
- L337 _private prototype_ `void ApplyTimeAdjustmentToSequencers(const FConcertSequencerTimeAdjustmentEvent& TimeAdjustmentEvent);` — Apply a sequencer time adjustment to sequencers. @param TimeAdjustmentEvent  The time adjustment event state
- L345 _private prototype_ `TArray<FOpenSequencerData*, TInlineAllocator<1>> GatherRootSequencersByState(const FString& InSequenceObjectPath);` — Gather all the currently open sequencer UIs that have the specified path as their root sequence @param InSequenceObjectPath        The full path to the root asset to gather sequences for @return An array containing all the entries that apply to the supplied sequence path
- L350 _private prototype_ `float GetLatencyCompensationMs() const;` — Get the amount of latency compensation to apply to time-synchronization sensitive interactions
- L353 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L354 _private function_ `virtual FString GetReferencerName() const override`
- L366 _private prototype_ `ETransactionFilterResult ShouldObjectBeTransacted(const FConcertTransactionFilterArgs& FilterArgs);` — Delegate to provide a hint to the transaction bridge that the given object should be transacted.  We special case LevelSequences and allow any transaction that has a level sequence as an outermost object to be included because there are many object types in level sequence transactions that do not share UMovieSceneSignedObject as a base class, which is used by the default transaction filters.
- L369 _private prototype_ `void DestroyPlayer(ALevelSequenceActor* LevelSequenceActor);` — Destroy the given sequence player with corresponding actor.
- L372 _private prototype_ `bool CanClose(const FConcertSequencerCloseEvent& InEvent) const;` — Indicates if this sequence player can be closed.
- L375 _private member_ `IConcertSyncClient* OwnerSyncClient;` — Pointer to the sync client that owns us.
- L378 _private member_ `TArray<FConcertSequencerState> PendingSequencerEvents;` — List of pending sequencer events to apply at end of frame.
- L381 _private member_ `TArray<FConcertSequencerOpenEvent> PendingSequenceOpenEvents;` — List of pending sequencer open events to apply at end of frame.
- L384 _private member_ `TArray<FConcertSequencerCloseEvent> PendingSequenceCloseEvents;` — List of pending sequencer open events to apply at end of frame.
- L387 _private member_ `TArray<FConcertSequencerTimeAdjustmentEvent> PendingTimeAdjustmentEvents;` — List of pending time adjustment events.
- L394 _private member_ `TArray<TTuple<FName,FString>> PendingDestroy;` — List of pending sequence players that are scheduled for destruction. The first member of the tuple is the key / level sequence player we a removing.  The second member tuple is the soft object path name of the replacement level sequence when it is recreated.
- L397 _private member_ `TArray<FString> PendingCreate;` — List of pending sequence players that are scheduled for creation.
- L400 _private member_ `TMap<FName, FConcertSequencerState> SequencerStates;` — Map of all currently opened Root Sequence State in a session, locally opened or not.
- L403 _private member_ `TArray<FOpenSequencerData> OpenSequencers;` — List of all locally opened sequencer.
- L406 _private member_ `TMap<FName, TObjectPtr<ALevelSequenceActor>> SequencePlayers;` — Map of opened sequence players, if not in editor mode.
- L409 _private member_ `TSharedRef<FConcertClientSequencePreloader> Preloader;` — Handle preload requests from the server, asynchronously loading and maintaining GC references to sequence assets.
- L412 _private member_ `bool bRespondingToTransportEvent;` — Boolean that is set when we are handling any transport event to prevent re-entrancy
- L415 _private member_ `FDelegateHandle OnSequencerCreatedHandle;` — Delegate handle for the global sequencer created event registered with the sequencer module
- L418 _private member_ `TWeakPtr<IConcertClientSession> WeakSession;` — Weak pointer to the client session with which to send events. May be null or stale.
- L421 _private member_ `TWeakPtr<FConcertClientWorkspace> Workspace;` — Weak pointer to the active workspace.

#### enum `FConcertClientSequencerManager::EPlaybackMode`  
`enum class EPlaybackMode`  
_L157-165_
- desc: Enum signifying how a sequencer UI is currently playing. Necessary to prevent transport event contention.
- L160 _public enumerator_ `Controller` — This sequencer's time should be propagated to the collaboration server
- L162 _public enumerator_ `Agent` — This sequencer's time should be updated in response to an event from the collaboration server
- L164 _public enumerator_ `Undefined` — To our knowledge, no sequencer is playing back, and this sequencer will both send and receive transport events

#### struct `FConcertClientSequencerManager::FOpenSequencerData`  
`struct FOpenSequencerData`  
_L168-184_
- desc: Struct containing the Open Sequencer data
- L171 _public member_ `EPlaybackMode PlaybackMode;` — Enum that signifies whether to send/receive transport events.
- L174 _public member_ `TWeakPtr<ISequencer> WeakSequencer;` — Weak pointer to the sequencer itself, if locally opened.
- L177 _public member_ `FDelegateHandle OnGlobalTimeChangedHandle;` — Delegate handle to the Global Time Changed event for the sequencer, if locally opened.
- L180 _public member_ `FDelegateHandle OnCloseEventHandle;` — Delegate handle to the Close event for the sequencer, if locally opened.
- L183 _public member_ `TPimplPtr<FConcertClientSequencerStateEventPacer> StateEventPacer;` — Pointer event pacer for state events. This class will pace state events so that we do not overwhelm the connection with too many.

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Private/ConcertClientTransactionBridge.h` (Private)


#### class `FConcertClientTransactionBridge`  
`class FConcertClientTransactionBridge : public IConcertClientTransactionBridge`  
_L14-116_
- inherits: `IConcertClientTransactionBridge`
- L17 _public prototype_ `FConcertClientTransactionBridge();`
- L18 _public prototype_ `virtual ~FConcertClientTransactionBridge();`
- L21 _public prototype_ `virtual void SetIncludeEditorOnlyProperties(const bool InIncludeEditorOnlyProperties) override;`
- L22 _public prototype_ `virtual void SetIncludeNonPropertyObjectData(const bool InIncludeNonPropertyObjectData) override;`
- L23 _public prototype_ `virtual void SetIncludeAnnotationObjectChanges(const bool InIncludeAnnotationObjectChanges) override;`
- L24 _public prototype_ `virtual FOnConcertClientLocalTransactionSnapshot& OnLocalTransactionSnapshot() override;`
- L25 _public prototype_ `virtual FOnConcertClientLocalTransactionFinalized& OnLocalTransactionFinalized() override;`
- L26 _public prototype_ `virtual bool CanApplyRemoteTransaction() const override;`
- L27 _public prototype_ `virtual FOnApplyTransaction& OnApplyTransaction() override;`
- L28 _public prototype_ `virtual FOnConcertConflictResolutionForPendingSend& OnConflictResolutionForPendingSend() override;`
- L30 _public prototype_ `virtual void ApplyRemoteTransaction(const FConcertTransactionEventBase& InEvent, const FConcertSessionVersionInfo* InVersionInfo, const TArray<FName>& InPackagesToProcess, const FConcertLocalIdentifierTable* InLocalIdentifierTablePtr, const bool bIsSnapshot, FRemoteTransactionResult* ResultInfo = nullptr) override;`
- L32 _public prototype_ `virtual bool& GetIgnoreLocalTransactionsRef() override;`
- L34 _public prototype_ `virtual void RegisterTransactionFilter(FName FilterName, FOnFilterTransactionDelegate FilterDelegate) override;`
- L35 _public prototype_ `virtual void UnregisterTransactionFilter(FName FilterName) override;`
- L37 _public prototype_ `virtual void StartBridge() final;`
- L38 _public prototype_ `virtual void StopBridge() final;`
- L42 _private prototype_ `void HandleTransactionStateChanged(const FTransactionContext& InTransactionContext, const ETransactionStateEventType InTransactionState);` — Called to handle a transaction state change
- L45 _private prototype_ `bool CanHandleObjectTransacted(UObject *InObject, const FTransactionObjectEvent& InTransactionEvent) const;` — Confirms that we can handle the transaction event.
- L48 _private prototype_ `void HandleObjectTransacted(UObject* InObject, const FTransactionObjectEvent& InTransactionEvent);` — Called to handle an object being transacted
- L51 _private prototype_ `void ConditionalBindUnderlyingLocalTransactionEvents();` — Attempt to bind to the underlying local transaction events, if they are available and have not yet been bound
- L54 _private prototype_ `void OnEngineInitComplete();` — Called once Engine initialization has finished, to bind to the underlying local transaction events
- L57 _private prototype_ `void OnEndFrame();` — Called at the end of the frame to notify of any transaction updates
- L80 _private member_ `TArray<FGuid> OngoingTransactionsOrder;` — Array of transaction IDs in the order they should be notified (maps to OngoingTransactions, although canceled transactions may be missing from the map)
- L83 _private member_ `TMap<FGuid, FOngoingTransaction> OngoingTransactions;` — Map of transaction IDs to the transaction that may be notified in the future
- L86 _private member_ `TMap<FName, FOnFilterTransactionDelegate> TransactionFilters;` — Map of named transaction filters that can override what is included / excluded by transaction bridge
- L89 _private member_ `FOnConcertClientLocalTransactionSnapshot OnLocalTransactionSnapshotDelegate;` — Called when an ongoing transaction is updated via a snapshot
- L92 _private member_ `FOnConcertClientLocalTransactionFinalized OnLocalTransactionFinalizedDelegate;` — Called when an transaction is finalized
- L95 _private member_ `FOnConcertConflictResolutionForPendingSend OnConflictResolutionForPendingSendDelegate;` — Delegeate called when a inbound transaction conflicts with a pending transaction to send.
- L98 _private member_ `FOnApplyTransaction OnApplyTransactionDelegate;` — Called when we are about to apply a transaction.
- L101 _private member_ `bool bHasBoundUnderlyingLocalTransactionEvents;` — True if we have managed to bind to the underlying local transaction events, as they may not have been ready when this instance was started
- L104 _private member_ `bool bIgnoreLocalTransactions;` — Flag to ignore transaction state change event, used when we do not want to record transaction we generate ourselves
- L107 _private member_ `bool bIncludeEditorOnlyProperties;` — Include non-cooked properties in object serialization
- L110 _private member_ `bool bIncludeNonPropertyObjectData;` — Include non-property object data in updates
- L113 _private member_ `bool bIncludeAnnotationObjectChanges;` — Include object changes that have been generated via a transaction annotation (where possible)
- L115 _private member_ `FConcertSyncWorldRemapper WorldRemapper = FConcertSyncWorldRemapper();`

#### struct `FConcertClientTransactionBridge::FOngoingTransaction`  
`struct FOngoingTransaction`  
_L59-75_
- L61 _public function_ `FOngoingTransaction(const FText InTransactionTitle, const FGuid& InTransactionId, const FGuid& InOperationId, UObject* InPrimaryObject) : CommonData(InTransactionTitle, InTransactionId, InOperationId, InPrimaryObject)`
- L66 _public member_ `FConcertClientLocalTransactionCommonData CommonData;`
- L67 _public member_ `FConcertClientLocalTransactionSnapshotData SnapshotData;`
- L68 _public member_ `FConcertClientLocalTransactionFinalizedData FinalizedData;`
- L70 _public typedef_ `using FTransactedObjectStatePtr = TPimplPtr<ConcertClientTransactionBridgeUtil::FTransactedObjectState>;`
- L71 _public member_ `TMap<FConcertObjectId, FTransactedObjectStatePtr> TransactedStatePtrs;`
- L73 _public member_ `bool bIsFinalized = false;`
- L74 _public member_ `bool bHasNotifiedSnapshot = false;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ConcertClientTransactionBridgeUtil`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Private/ConcertClientTransactionManager.h` (Private)


#### struct `FConcertConflictDescriptionAggregate`  
`struct FConcertConflictDescriptionAggregate : public FConcertConflictDescriptionBase`  
_L18-35_
- inherits: `FConcertConflictDescriptionBase`
- L20 _public prototype_ `virtual ~FConcertConflictDescriptionAggregate() override = default;`
- L21 _public prototype_ `virtual FText GetConflictDetails() const override;`
- L22 _public prototype_ `virtual FText GetConflictTitle() const override;`
- L24 _public prototype_ `void AddObjectRemoved(const FConcertObjectId& ObjectIdRemoved);`
- L25 _public prototype_ `void AddObjectRenamed(const FConcertObjectId& OldObjectId, const FConcertObjectId& NewObjectId);`
- L27 _public function_ `bool HasAnyResults() const`
- L33 _private member_ `TArray<FConcertObjectId> ObjectsRemoved;`
- L34 _private member_ `TArray<TPair<FConcertObjectId, FConcertObjectId>> ObjectsRenamed;`

#### class `FConcertClientTransactionManager`  
`class FConcertClientTransactionManager`  
_L37-293_
- L40 _public prototype_ `FConcertClientTransactionManager(TSharedRef<FConcertSyncClientLiveSession> InLiveSession, IConcertClientTransactionBridge* InTransactionBridge);`
- L41 _public prototype_ `~FConcertClientTransactionManager();`
- L46 _public prototype_ `bool HasSessionChanges() const;` — @return true if there are any packages with live transactions right now.
- L55 _public prototype_ `bool HasLiveTransactionSupport(class UPackage* InPackage) const;` — Indicate if a particular package is supported for live transactions based on transaction filters. @param InPackage The package to check for support. @return true if the package support live transactions.
- L60 _public prototype_ `void ReplayAllTransactions();` — Called to replay any live transactions for all packages.
- L65 _public prototype_ `void ReplayTransactions(const FName InPackageName);` — Called to replay live transactions for the given package.
- L70 _public prototype_ `void HandleRemoteTransaction(const FGuid& InSourceEndpointId, const int64 InTransactionEventId, const bool bApply);` — Called to handle a remote transaction being received.
- L75 _public prototype_ `void ProcessPending();` — Called to process any pending transaction events (sending or receiving).
- L152 _private prototype_ `template <typename EventType> void HandleTransactionEvent(const FConcertSessionContext& InEventContext, const EventType& InEvent);` — Handle a transaction event by queueing it for processing at the end of the current frame.
- L157 _private prototype_ `void HandleTransactionRejectedEvent(const FConcertSessionContext& InEventContext, const FConcertTransactionRejectedEvent& InEvent);` — Handle a rejected transaction event, those are sent by the server when a transaction is refused.
- L163 _private prototype_ `bool CanProcessTransactionEvent() const;` — Can we currently process transaction events? True if we are neither suspended nor unable to perform a blocking action, false otherwise.
- L168 _private prototype_ `bool CanSendTransactionEvents() const;` — Can we send transaction events to remote clients.
- L173 _private prototype_ `void ProcessTransactionEvent(const FPendingTransactionToProcessContext& InContext, const FStructOnScope& InEvent);` — Process a transaction event.
- L178 _private prototype_ `void ProcessTransactionFinalizedEvent(const FPendingTransactionToProcessContext& InContext, const FConcertTransactionFinalizedEvent& InEvent);` — Process a transaction finalized event.
- L183 _private prototype_ `void ProcessTransactionSnapshotEvent(const FPendingTransactionToProcessContext& InContext, const FConcertTransactionSnapshotEvent& InEvent);` — Process a transaction snapshot event.
- L188 _private prototype_ `FPendingTransactionToSend& HandleLocalTransactionCommon(const FConcertClientLocalTransactionCommonData& InCommonData, const TArray<FConcertExportedObject>& ObjectUpdates);` — Handle a local transaction, ensuring that there is a pending entry to be sent.
- L193 _private prototype_ `void HandleLocalTransactionSnapshot(const FConcertClientLocalTransactionCommonData& InCommonData, const FConcertClientLocalTransactionSnapshotData& InSnapshotData);` — Handle a local transaction being snapshot, queueing it for send later.
- L198 _private prototype_ `void HandleLocalTransactionFinalized(const FConcertClientLocalTransactionCommonData& InCommonData, const FConcertClientLocalTransactionFinalizedData& InFinalizedData);` — Handle a local transaction being finalized, queueing it for send later.
- L203 _private prototype_ `void SendTransactionFinalizedEvent(const FGuid& InTransactionId, const FGuid& InOperationId, UObject* InPrimaryObject, const TArray<FName>& InModifiedPackages, const TArray<FConcertExportedObject>& InObjectUpdates, const FConcertLocalIdentifierTable& InLocalIdentifierTable, const FConcertSequencedCustomEvent& SequenceId, const FText& InTitle);` — Send a transaction finalized event.
- L208 _private prototype_ `void SendTransactionSnapshotEvent(const FGuid& InTransactionId, const FGuid& InOperationId, UObject* InPrimaryObject, const TArray<FName>& InModifiedPackages, const TArray<FConcertExportedObject>& InObjectUpdates);` — Send a transaction snapshot event.
- L213 _private prototype_ `void SendPendingTransactionEvents();` — Send any pending transaction events that qualify.
- L219 _private prototype_ `void CheckEventForSendConflicts(const FConcertTransactionFinalizedEvent& InEvent);` — Check the inbound transaction event for conflicts in the pending send. If we are receive only and a conflict is detected then we have to remove pending send object.
- L229 _private prototype_ `void FixupObjectIdsInPendingSend(const FConcertObjectId& OldObjectId, const FConcertObjectId& NewObjectId, FConcertConflictDescriptionAggregate& ConflictAggregate);` — Fixup any objects from the old ObjectId a given new ObjectId.  The routine will check that the given object ids are valid. @param OldObjectId to search. @param NewObjectId to replace. @param Aggregate for conflict information.
- L234 _private prototype_ `void RemovePendingToSend(const FConcertClientLocalTransactionCommonData& InCommonData);` — Remove the given pending to send object.
- L239 _private prototype_ `void RemovePendingToSend(const FGuid& InCommonData);` — Remove the given pending to send object by Guid.
- L244 _private prototype_ `FPendingTransactionToSend& AddPendingToSend(const FConcertClientLocalTransactionCommonData& InCommonData, const TArray<FConcertExportedObject>& ObjectUpdates);` — Remove the given pending to send object.
- L249 _private prototype_ `bool ShouldProcessTransactionEvent(const FConcertTransactionEventBase& InEvent, const bool InIsRequired) const;` — Should process this transaction event?
- L254 _private prototype_ `void FillTransactionEvent(const FGuid& InTransactionId, const FGuid& InOperationId, const TArray<FName>& InModifiedPackages, FConcertTransactionEventBase& OutEvent) const;` — Fill in the transaction event based on the given GUID.
- L259 _private prototype_ `void NotifyUserOfSendConflict(const FConcertConflictDescriptionBase& ConflictDescription);` — Notify externally that a transaction conflict has occurred.
- L264 _private member_ `TSharedPtr<FConcertSyncClientLiveSession> LiveSession;` — Session instance this transaction manager was created for.
- L269 _private member_ `IConcertClientTransactionBridge* TransactionBridge;` — Transaction bridge used by this manager.
- L276 _private member_ `TArray<FPendingTransactionToProcess> PendingTransactionsToProcess;` — Array of pending transaction events in the order they were received. Events are queued in this array while the session is suspended or the user is interacting, and any queued transactions will be processed on the next Tick.
- L281 _private member_ `TArray<FGuid> PendingTransactionsToSendOrder;` — Array of transaction IDs in the order they should be sent (maps to PendingTransactionsToSend, although canceled transactions may be missing from the map).
- L286 _private member_ `TMap<FGuid, FPendingTransactionToSend> PendingTransactionsToSend;` — Map of transaction IDs to the pending transaction that may be sent in the future (when finalized).
- L292 _private member_ `TMap<FConcertObjectId, TSet<FGuid>, FDefaultSetAllocator, FConcertObjectIdFuncs> NameLookupForPendingTransactionsToSend;` — Named lookup for pending transactions to send.  This is so we can cross check the pending for send against remote transactions that may conflict.

#### struct `FConcertClientTransactionManager::FPendingTransactionToProcessContext`  
`struct FPendingTransactionToProcessContext`  
_L81-88_
- desc: Context object for transactions that are to be processed.
- L84 _public member_ `bool bIsRequired = false;` — Is this transaction required?
- L87 _public member_ `TArray<FName> PackagesToProcess;` — Optional list of packages to process transactions for, or empty to process transactions for all packages

#### struct `FConcertClientTransactionManager::FConcertObjectIdFuncs`  
`struct FConcertObjectIdFuncs : public TDefaultMapKeyFuncs<FConcertObjectId, TSet<FGuid>, false>`  
_L91-102_
- inherits: `TDefaultMapKeyFuncs<FConcertObjectId,TSet<FGuid>,false>`
- desc: Lookup set key functions.
- L93 _public function_ `FORCEINLINE static bool Matches(KeyInitType A, KeyInitType B)`
- L98 _public function_ `FORCEINLINE static uint32 GetKeyHash(KeyInitType InObjectId)`

#### struct `FConcertClientTransactionManager::FPendingTransactionToProcess`  
`struct FPendingTransactionToProcess`  
_L107-125_
- desc: A received pending transaction event that was queued for processing later.
- L109 _public function_ `FPendingTransactionToProcess(const FPendingTransactionToProcessContext& InContext, const UScriptStruct* InEventStruct, const void* InEventData) : Context(InContext) , EventData(InEventStruct)`
- L116 _public function_ `FPendingTransactionToProcess(const FPendingTransactionToProcessContext& InContext, FStructOnScope&& InEvent) : Context(InContext) , EventData(MoveTemp(InEvent))`
- L123 _public member_ `FPendingTransactionToProcessContext Context;`
- L124 _public member_ `FStructOnScope EventData;`

#### struct `FConcertClientTransactionManager::FPendingTransactionToSend`  
`struct FPendingTransactionToSend`  
_L130-146_
- desc: A pending transaction that may be sent in the future (when finalized).
- L132 _public function_ `explicit FPendingTransactionToSend(const FConcertClientLocalTransactionCommonData& InCommonData) : CommonData(InCommonData)`
- L137 _public member_ `FConcertClientLocalTransactionCommonData CommonData;`
- L138 _public member_ `FConcertClientLocalTransactionSnapshotData SnapshotData;`
- L139 _public member_ `FConcertClientLocalTransactionFinalizedData FinalizedData;`
- L142 _public member_ `FConcertSequencedCustomEvent SequencedEvent;` — Sequencing id for this pending transaction.
- L144 _public member_ `bool bIsFinalized = false;`
- L145 _public member_ `double LastSnapshotTimeSeconds = 0.0;`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Private/ConcertClientWorkspace.h` (Private)


#### struct `UE::ConcertSyncClient::FSessionBindArgs`  
`struct FSessionBindArgs`  
_L30-36_
- L32 _public member_ `TSharedPtr<FConcertSyncClientLiveSession> LiveSession;`
- L33 _public member_ `FConcertBridges Bridges;`
- L35 _public function_ `bool IsValid() const`

#### class `FConcertClientWorkspace`  
`class FConcertClientWorkspace : public IConcertClientWorkspace`  
_L44-280_
- inherits: `IConcertClientWorkspace`
- L47 _public prototype_ `FConcertClientWorkspace(const UE::ConcertSyncClient::FSessionBindArgs& SessionBindArgs, TSharedPtr<IConcertFileSharingService> InFileSharingService, IConcertSyncClient* InOwnerSyncClient);`
- L48 _public prototype_ `virtual ~FConcertClientWorkspace();`
- L51 _public prototype_ `virtual IConcertClientSession& GetSession() const override;` — IConcertClientWorkspace interface
- L52 _public prototype_ `virtual FGuid GetWorkspaceLockId() const override;`
- L53 _public prototype_ `virtual FGuid GetResourceLockId(const FName InResourceName) const override;`
- L54 _public prototype_ `virtual bool AreResourcesLockedBy(TArrayView<const FName> ResourceNames, const FGuid& ClientId) override;`
- L55 _public prototype_ `virtual TFuture<FConcertResourceLockResponse> LockResources(TArray<FName> InResourceNames) override;`
- L56 _public prototype_ `virtual TFuture<FConcertResourceLockResponse> UnlockResources(TArray<FName> InResourceNames) override;`
- L57 _public prototype_ `virtual bool HasSessionChanges() const override;`
- L58 _public prototype_ `virtual TArray<FName> GatherSessionChanges(bool IgnorePersisted = true) override;`
- L59 _public prototype_ `virtual TOptional<FString> GetValidPackageSessionPath(FName PackageName) const override;`
- L60 _public prototype_ `virtual FPersistResult PersistSessionChanges(FPersistParameters InParam) override;`
- L61 _public prototype_ `virtual bool HasLiveTransactionSupport(UPackage* InPackage) const override;`
- L62 _public prototype_ `virtual bool ShouldIgnorePackageDirtyEvent(class UPackage* InPackage) const override;`
- L63 _public prototype_ `virtual bool FindTransactionEvent(const int64 TransactionEventId, FConcertSyncTransactionEvent& OutTransactionEvent, const bool bMetaDataOnly) const override;`
- L64 _public prototype_ `virtual TFuture<TOptional<FConcertSyncTransactionEvent>> FindOrRequestTransactionEvent(const int64 TransactionEventId, const bool bMetaDataOnly) override;`
- L65 _public prototype_ `virtual bool FindPackageEvent(const int64 PackageEventId, FConcertSyncPackageEventMetaData& OutPackageEvent) const override;`
- L66 _public prototype_ `virtual bool FindReplicationEvent(const int64 ReplicationEventId, FConcertSyncReplicationEvent& OutReplicationEvent) const override;`
- L67 _public prototype_ `virtual void GetActivities(const int64 FirstActivityIdToFetch, const int64 MaxNumActivities, TMap<FGuid, FConcertClientInfo>& OutEndpointClientInfoMap, TArray<FConcertSessionActivity>& OutActivities) const override;`
- L68 _public prototype_ `virtual int64 GetLastActivityId() const override;`
- L69 _public prototype_ `virtual FOnActivityAddedOrUpdated& OnActivityAddedOrUpdated() override;`
- L70 _public prototype_ `virtual FOnWorkspaceSynchronized& OnWorkspaceSynchronized() override;`
- L71 _public prototype_ `virtual FOnFinalizeWorkspaceSyncCompleted& OnFinalizeWorkspaceSyncCompleted() override;`
- L73 _public prototype_ `virtual IConcertClientDataStore& GetDataStore() override;`
- L74 _public prototype_ `virtual bool IsAssetModifiedByOtherClients(const FName& AssetName, int32* OutOtherClientsWithModifNum, TArray<FConcertClientInfo>* OutOtherClientsWithModifInfo, int32 OtherClientsWithModifMaxFetchNum) const override;`
- L75 _public prototype_ `virtual void SetIgnoreOnRestoreFlagForEmittedActivities(bool bIgnore) override;`
- L77 _public prototype_ `virtual void AddWorkspaceFinalizeDelegate(FName InDelegateName, FCanFinalizeWorkspaceDelegate InDelegate) override;`
- L78 _public prototype_ `virtual void RemoveWorkspaceFinalizeDelegate(FName InDelegateName) override;`
- L80 _public prototype_ `virtual void AddWorkspaceCanProcessPackagesDelegate(FName InDelegateName, FCanProcessPendingPackages Delegate) override;`
- L81 _public prototype_ `virtual void RemoveWorkspaceCanProcessPackagesDelegate(FName InDelegateName) override;`
- L83 _public prototype_ `virtual bool IsReloadingPackage(FName PackageName) const override;`
- L86 _public prototype_ `bool CanProcessPendingPackages() const;` — Indicates if we can process any pending package updates.
- L89 _public prototype_ `bool CanFinalize() const;` — Indicates if we can finalize activity sync.
- L92 _public prototype_ `FOnWorkspaceEndFrameCompleted& OnWorkspaceEndFrameCompleted();` — Gets the delegate called after the workspace has completed its handling at the end of an engine frame.
- L97 _private prototype_ `void BindSession(const UE::ConcertSyncClient::FSessionBindArgs& SessionBindArgs);` — Bind the workspace to this session.
- L100 _private prototype_ `void UnbindSession();` — Unbind the workspace to its bound session.
- L105 _private prototype_ `void LoadSessionData();` — Load client side info associated with this session if any. (i.e already persisted files)
- L110 _private prototype_ `void SaveSessionData();` — Save client side info associated with this session if any. (i.e already persisted files)
- L113 _private prototype_ `void HandleConnectionChanged(IConcertClientSession& InSession, EConcertConnectionStatus Status);`
- L119 _private prototype_ `void SaveLiveTransactionsToPackages();` — Save all live transactions to packages.
- L124 _private prototype_ `void SaveLiveTransactionsToPackage(const FName PackageName);` — Save live transactions, if any, to the specified packages, adding a client side dummy package event to the db
- L127 _private prototype_ `void HandleAssetLoaded(UObject* InAsset);`
- L130 _private prototype_ `void HandlePackageDiscarded(UPackage* InPackage);`
- L133 _private prototype_ `void HandlePostPIEStarted(const bool InIsSimulating);`
- L136 _private prototype_ `void HandleSwitchBeginPIEAndSIE(const bool InIsSimulating);`
- L139 _private prototype_ `void HandleEndPIE(const bool InIsSimulating);`
- L143 _private prototype_ `void OnEndFrame();`
- L146 _private prototype_ `void HandleWorkspaceSyncEndpointEvent(const FConcertSessionContext& Context, const FConcertWorkspaceSyncEndpointEvent& Event);`
- L149 _private prototype_ `void HandleWorkspaceSyncActivityEvent(const FConcertSessionContext& Context, const FConcertWorkspaceSyncActivityEvent& Event);`
- L152 _private prototype_ `void HandleWorkspaceSyncLockEvent(const FConcertSessionContext& Context, const FConcertWorkspaceSyncLockEvent& Event);`
- L155 _private prototype_ `void HandleWorkspaceSyncCompletedEvent(const FConcertSessionContext& Context, const FConcertWorkspaceSyncCompletedEvent& Event);`
- L163 _private prototype_ `void SetEndpoint(const FGuid& InEndpointId, const FConcertSyncEndpointData& InEndpointData);` — Set an endpoint in the session database, creating or replacing it. @param InEndpointId				The ID of the endpoint to set. @param InEndpointData			The endpoint data to set.
- L171 _private prototype_ `void SetConnectionActivity(const FConcertSyncConnectionActivity& InConnectionActivity);` — Set a connection activity in the session database, creating or replacing it. @note The endpoint ID referenced by the activity must exist in the database (@see SetEndpoint). @param InConnectionActivity		The connection activity to set.
- L179 _private prototype_ `void SetLockActivity(const FConcertSyncLockActivity& InLockActivity);` — Set a lock activity in the session database, creating or replacing it. @note The endpoint ID referenced by the activity must exist in the database (@see SetEndpoint). @param InLockActivity			The lock activity to set.
- L187 _private prototype_ `void SetTransactionActivity(const FConcertSyncTransactionActivity& InTransactionActivity);` — Set a transaction activity in the session database, creating or replacing it. @note The endpoint ID referenced by the activity must exist in the database (@see SetEndpoint). @param InTransactionActivity		The transaction activity to set.
- L195 _private prototype_ `void SetPackageActivity(const FConcertSyncPackageActivity& InPackageActivity);` — Set a package activity in the session database, creating or replacing it. @note The endpoint ID referenced by the activity must exist in the database (@see SetEndpoint). @param InPackageActivity		The package activity to set.
- L203 _private prototype_ `void SetReplicationActivity(const FConcertSyncReplicationActivity& InReplicationActivity);` — Set a replication activity in the session database, creating or replacing it. @note The endpoint ID referenced by the activity must exist in the database (@see SetEndpoint). @param InReplicationActivity		The replication activity to set.
- L210 _private prototype_ `void PostActivityUpdated(const FConcertSyncActivity& InActivity);` — Called after any updated in the session database. @param InActivity			The activity that was updated.
- L217 _private prototype_ `bool IsTransactionEventPartiallySynced(const FConcertSyncTransactionEvent& TransactionEvent) const;` — Check whether a transaction activity is partially synced, i.e. that only the meta data was synced because the activity event was superseded by another one and the transaction data wasn't required to reconstruct the state of a level.
- L220 _private member_ `TMap<FName, FCanProcessPendingPackages> CanProcessPendingDelegates;` — A hash map of delegates that provide true/false value for applying pendings during the current end of frame.
- L223 _private member_ `TMap<FName, FCanFinalizeWorkspaceDelegate> CanFinalizeDelegates;` — A hash map of delegates that provide true/false value for finalizing an activity sync during the current end of frame.
- L226 _private member_ `TUniquePtr<FConcertClientTransactionManager> TransactionManager;`
- L229 _private member_ `TUniquePtr<FConcertClientPackageManager> PackageManager;`
- L232 _private member_ `TUniquePtr<FConcertClientLockManager> LockManager;`
- L237 _private member_ `TUniquePtr<FConcertClientLiveTransactionAuthors> LiveTransactionAuthors;` — Tracks the clients that have live transactions on any given packages.
- L240 _private member_ `IConcertClientPackageBridge* PackageBridge;`
- L243 _private member_ `IConcertSyncClient *OwnerSyncClient;` — The sync client that owns the workspace.
- L246 _private member_ `TSharedPtr<FConcertSyncClientLiveSession> LiveSession;`
- L249 _private member_ `FConcertClientWorkspaceData SessionData;` — Persistent client workspace data associated with this workspaces session.
- L252 _private member_ `bool bHasSyncedWorkspace;` — True if this client has performed its initial sync with the server session
- L255 _private member_ `bool bFinalizeWorkspaceSyncRequested;` — True if a request to finalize a workspace sync has been requested
- L258 _private member_ `TUniquePtr<FScopedSlowTask> InitialSyncSlowTask;` — Slow task used during the initial sync of this workspace
- L261 _private member_ `FOnActivityAddedOrUpdated OnActivityAddedOrUpdatedDelegate;` — The delegate called every time activity is added to or updated in this session.
- L264 _private member_ `FOnWorkspaceSynchronized OnWorkspaceSyncedDelegate;` — The delegate called every time the workspace is synced.
- L267 _private member_ `FOnFinalizeWorkspaceSyncCompleted OnFinalizeWorkspaceSyncCompletedDelegate;` — The delegate called after the workspace has been synced and finalized.
- L270 _private member_ `FOnWorkspaceEndFrameCompleted OnWorkspaceEndFrameCompletedDelegate;` — The delegate called after the workspace has completed its handling at the end of an engine frame.
- L273 _private member_ `TUniquePtr<FConcertClientDataStore> DataStore;` — The session key/value store proxy. The real store is held by the server and shared across all clients.
- L276 _private member_ `bool bPendingStopIgnoringActivityOnRestore = false;` — True if the client has marked the further transaction as 'non-ignored'. This is sent at the end of the frame.
- L279 _private member_ `TSharedPtr<IConcertFileSharingService> FileSharingService;` — Optional side channel to exchange large blobs (package data) with the server in a scalable way (ex. the request/response transport layer is not designed and doesn't support exchanging 3GB packages).

#### Free symbols / members of external scopes

- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace ConcertSyncClient` (scope `UE`)
- L42 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnWorkspaceEndFrameCompleted);`
- L42 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnWorkspaceEndFrameCompleted);`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Private/ConcertClientWorkspaceData.h` (Private)


#### struct `FConcertClientWorkspaceData`  
`struct FConcertClientWorkspaceData`  
_L13-20_
- reflection: `USTRUCT()`
- desc: Client workspace data associated with a specific session that persist between connections.
- L19 _public member_ `FGuid SessionIdentifier;` — `UPROPERTY()` — The session identifier that this client data is associated with.

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Private/ConcertSyncClient.h` (Private)


#### class `FConcertSyncClient`  
`class FConcertSyncClient : public IConcertSyncClient`  
_L26-100_
- inherits: `IConcertSyncClient`
- desc: Implementation for a Concert Sync Client.
- L29 _public prototype_ `FConcertSyncClient(const FString& InRole, const UE::ConcertSyncClient::FConcertBridges& InBridges);`
- L30 _public prototype_ `virtual ~FConcertSyncClient();`
- L33 _public prototype_ `virtual void Startup(const UConcertClientConfig* InClientConfig, const EConcertSyncSessionFlags InSessionFlags) override;`
- L34 _public prototype_ `virtual void Shutdown() override;`
- L35 _public prototype_ `virtual IConcertClientRef GetConcertClient() const override;`
- L36 _public prototype_ `virtual TSharedPtr<IConcertClientWorkspace> GetWorkspace() const override;`
- L37 _public prototype_ `virtual IConcertClientPresenceManager* GetPresenceManager() const override;`
- L38 _public prototype_ `virtual IConcertClientSequencerManager* GetSequencerManager() const override;`
- L39 _public prototype_ `virtual IConcertClientReplicationManager* GetReplicationManager() const override;`
- L41 _public prototype_ `virtual FOnConcertClientWorkspaceStartupOrShutdown& OnWorkspaceStartup() override;`
- L42 _public prototype_ `virtual FOnConcertClientWorkspaceStartupOrShutdown& OnWorkspaceShutdown() override;`
- L44 _public prototype_ `virtual FOnConcertClientSyncSessionStartupOrShutdown& OnSyncSessionStartup() override;`
- L45 _public prototype_ `virtual FOnConcertClientSyncSessionStartupOrShutdown& OnSyncSessionShutdown() override;`
- L47 _public prototype_ `virtual void PersistSpecificChanges(TArrayView<const FName> InPackages) override;`
- L48 _public prototype_ `virtual void PersistAllSessionChanges() override;`
- L49 _public prototype_ `virtual void GetSessionClientActions(const FConcertSessionClientInfo& InClientInfo, TArray<FConcertActionDefinition>& OutActions) const override;`
- L51 _public prototype_ `virtual void SetFileSharingService(TSharedPtr<IConcertFileSharingService> InFileSharingService) override;`
- L52 _public prototype_ `virtual IConcertClientTransactionBridge* GetTransactionBridge() const override;`
- L53 _public prototype_ `virtual IConcertClientPackageBridge* GetPackageBridge() const override;`
- L54 _public prototype_ `virtual IConcertClientReplicationBridge* GetReplicationBridge() const override;`
- L57 _private prototype_ `void CreateWorkspace(const TSharedRef<FConcertSyncClientLiveSession>& InLiveSession);`
- L58 _private prototype_ `void DestroyWorkspace();`
- L60 _private prototype_ `void RegisterConcertSyncHandlers(TSharedRef<IConcertClientSession> InSession);`
- L61 _private prototype_ `void UnregisterConcertSyncHandlers(TSharedRef<IConcertClientSession> InSession);`
- L64 _private member_ `IConcertClientRef ConcertClient;` — Client for Concert
- L67 _private member_ `EConcertSyncSessionFlags SessionFlags;` — Flags controlling what features are enabled for sessions within this client
- L70 _private member_ `const UE::ConcertSyncClient::FConcertBridges Bridges;` — Pointers to Concert Bridges used by this client.
- L73 _private member_ `TSharedPtr<FConcertSyncClientLiveSession> LiveSession;` — Live session data for the current session.
- L76 _private member_ `TSharedPtr<FConcertClientWorkspace> Workspace;` — Client workspace for the current session.
- L79 _private member_ `FOnConcertClientWorkspaceStartupOrShutdown OnWorkspaceStartupDelegate;` — Delegate called on every workspace startup.
- L82 _private member_ `FOnConcertClientWorkspaceStartupOrShutdown OnWorkspaceShutdownDelegate;` — Delegate called on every workspace shutdown.
- L85 _private member_ `FOnConcertClientSyncSessionStartupOrShutdown OnSyncSessionStartupDelegate;` — Delegate called just before the workspace get created.
- L88 _private member_ `FOnConcertClientSyncSessionStartupOrShutdown OnSyncSessionShutdownDelegate;` — Delegate called just after the workspace was deleted.
- L91 _private member_ `TUniquePtr<UE::ConcertSyncClient::Replication::FReplicationManager> ReplicationManager;` — Manages the client's replication system. Can be used to join & leave replication sessions.
- L95 _private member_ `TSharedPtr<FConcertClientPresenceManager> PresenceManager;` — Presence manager for the current session.
- L98 _private member_ `TUniquePtr<FConcertClientSequencerManager> SequencerManager;` — Sequencer event manager for Concert session.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ConcertSyncClient` (scope `UE`)
- L8 _namespace_ `namespace Replication` (scope `UE::ConcertSyncClient`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Private/ConcertSyncClientLiveSession.h` (Private)


#### class `FConcertSyncClientLiveSession`  
`class FConcertSyncClientLiveSession`  
_L12-66_
- L15 _public prototype_ `FConcertSyncClientLiveSession(const TSharedRef<IConcertClientSession>& InSession, const EConcertSyncSessionFlags InSessionFlags);`
- L16 _public prototype_ `~FConcertSyncClientLiveSession();`
- L18 _public prototype_ `FConcertSyncClientLiveSession(const FConcertSyncClientLiveSession&) = delete;`
- L19 _public prototype_ `FConcertSyncClientLiveSession& operator=(const FConcertSyncClientLiveSession&) = delete;`
- L21 _public prototype_ `FConcertSyncClientLiveSession(FConcertSyncClientLiveSession&&) = delete;`
- L22 _public prototype_ `FConcertSyncClientLiveSession& operator=(FConcertSyncClientLiveSession&&) = delete;`
- L25 _public prototype_ `bool IsValidSession() const;` — Is this a valid session? (ie, has been successfully opened)
- L28 _public function_ `IConcertClientSession& GetSession()` — Get the underlying live session (if IsValidSession)
- L34 _public function_ `const IConcertClientSession& GetSession() const` — Get the underlying live session (if IsValidSession)
- L40 _public function_ `EConcertSyncSessionFlags GetSessionFlags() const` — Get the flags controlling what features are enabled for this live session
- L46 _public function_ `FConcertSyncSessionDatabase& GetSessionDatabase()` — Get the database for this live session (if IsValidSession)
- L52 _public function_ `const FConcertSyncSessionDatabase& GetSessionDatabase() const` — Get the database for this live session (if IsValidSession)
- L59 _private member_ `TSharedRef<IConcertClientSession> Session;` — The underlying live session
- L62 _private member_ `EConcertSyncSessionFlags SessionFlags;` — Flags controlling what features are enabled for this live session
- L65 _private member_ `TUniquePtr<FConcertSyncSessionDatabase> SessionDatabase;` — Database for this live session

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Private/ConcertSyncClientUtil.h` (Private)


#### enum `ConcertSyncClientUtil::EGetObjectResultFlags`  
`enum class EGetObjectResultFlags : uint8`  
_L35-40_
- L37 _public enumerator_ `None = 0`
- L38 _public enumerator_ `NeedsGC = 1<<0`
- L39 _public enumerator_ `NewlyCreated = 1<<1`

#### struct `ConcertSyncClientUtil::FGetObjectResult`  
`struct FGetObjectResult`  
_L43-73_
- L45 _public prototype_ `FGetObjectResult() = default;`
- L47 _public function_ `explicit FGetObjectResult(UObject* InObj, const EGetObjectResultFlags InFlags = EGetObjectResultFlags::None) : Obj(InObj) , Flags(InFlags)`
- L53 _public function_ `explicit FGetObjectResult(UObject* InObj, const UConcertClientObjectFactory* InFactory, const EGetObjectResultFlags InFlags) : Obj(InObj) , Factory(InFactory) , Flags(InFlags)`
- L60 _public function_ `bool NeedsGC() const`
- L65 _public function_ `bool NewlyCreated() const`
- L70 _public member_ `UObject* Obj = nullptr;`
- L71 _public member_ `const UConcertClientObjectFactory* Factory = nullptr;`
- L72 _public member_ `EGetObjectResultFlags Flags = EGetObjectResultFlags::None;`

#### Free symbols / members of external scopes

- L33 _namespace_ `namespace ConcertSyncClientUtil`
- L41 _prototype_ `ENUM_CLASS_FLAGS(EGetObjectResultFlags);` (scope `ConcertSyncClientUtil`)
- L75 _prototype_ `bool IsUserEditing();` (scope `ConcertSyncClientUtil`)
- L77 _prototype_ `bool ShouldDelayTransaction();` (scope `ConcertSyncClientUtil`)
- L79 _prototype_ `bool CanPerformBlockingAction(const bool bBlockDuringInteraction = true);` (scope `ConcertSyncClientUtil`)
- L81 _prototype_ `void UpdatePendingKillState(UObject* InObj, const bool bIsPendingKill);` (scope `ConcertSyncClientUtil`)
- L83 _prototype_ `void AddActorToOwnerLevel(AActor* InActor);` (scope `ConcertSyncClientUtil`)
- L85 _prototype_ `bool ObjectIdsMatch(const FConcertObjectId& One, const FConcertObjectId& Two);` (scope `ConcertSyncClientUtil`)
- L87 _prototype_ `int32 GetObjectPathDepth(UObject* InObjToTest);` (scope `ConcertSyncClientUtil`)
- L89 _prototype_ `FGetObjectResult GetObject(const FConcertObjectId& InObjectId, const FName InNewName, const FName InNewOuterPath, const FName InNewPackageName, const FSoftObjectPath& InSourceObject, const bool bAllowCreate);` (scope `ConcertSyncClientUtil`)
- L91 _prototype_ `TArray<const FProperty*> GetExportedProperties(const UStruct* InStruct, const TArray<FName>& InPropertyNames, const bool InIncludeEditorOnlyData);` (scope `ConcertSyncClientUtil`)
- L93 _prototype_ `const FProperty* GetExportedProperty(const UStruct* InStruct, const FName InPropertyName, const bool InIncludeEditorOnlyData);` (scope `ConcertSyncClientUtil`)
- L95 _prototype_ `void SerializeProperties(FConcertLocalIdentifierTable* InLocalIdentifierTable, const UObject* InObject, const TArray<const FProperty*>& InProperties, const bool InIncludeEditorOnlyData, TArray<FConcertSerializedPropertyData>& OutPropertyDatas);` (scope `ConcertSyncClientUtil`)
- L97 _prototype_ `void SerializeProperty(FConcertLocalIdentifierTable* InLocalIdentifierTable, const UObject* InObject, const FProperty* InProperty, const bool InIncludeEditorOnlyData, TArray<uint8>& OutSerializedData);` (scope `ConcertSyncClientUtil`)
- L99 _prototype_ `void SerializeObject(FConcertLocalIdentifierTable* InLocalIdentifierTable, const UObject* InObject, const TArray<const FProperty*>* InProperties, const bool InIncludeEditorOnlyData, TArray<uint8>& OutSerializedData);` (scope `ConcertSyncClientUtil`)
- L101 _prototype_ `void FlushPackageLoading(const FName InPackageName);` (scope `ConcertSyncClientUtil`)
- L103 _prototype_ `void FlushPackageLoading(const FString& InPackageName, bool bForceBulkDataLoad = true);` (scope `ConcertSyncClientUtil`)
- L112 _prototype_ `FDirectoryWatcherModule& GetDirectoryWatcherModule();` (scope `ConcertSyncClientUtil`) — Gets the DirectoryWatcher module. The module will be loaded if it is not currently loaded. @return: the DirectoryWatcher module
- L118 _prototype_ `FDirectoryWatcherModule* GetDirectoryWatcherModuleIfLoaded();` (scope `ConcertSyncClientUtil`) — Gets the DirectoryWatcher module if it is currently loaded. @return: a pointer to the DirectoryWatcher module if is currently loaded, or nullptr otherwise
- L126 _prototype_ `IDirectoryWatcher* GetDirectoryWatcher();` (scope `ConcertSyncClientUtil`) — Gets the directory watcher. The DirectoryWatcher module will be loaded if it is not currently loaded. @return: the directory watcher if the platform supports directory watching, or nullptr otherwise
- L132 _prototype_ `IDirectoryWatcher* GetDirectoryWatcherIfLoaded();` (scope `ConcertSyncClientUtil`) — Gets the directory watcher if the DirectoryWatcher module is currently loaded. @return: the directory watcher if the DirectoryWatcher module is currently loaded and the platform supports directory watching, or nullptr otherwise
- L140 _prototype_ `void SynchronizeAssetRegistry();` (scope `ConcertSyncClientUtil`) — Synchronizes the Asset Registry. This ensures that any pending file changes are completed and that the Asset Registry is updated to correctly reflect those changes.
- L142 _prototype_ `void HotReloadPackages(TArrayView<const FName> InPackageNames);` (scope `ConcertSyncClientUtil`)
- L144 _prototype_ `void PurgePackages(TArrayView<const FName> InPackageNames);` (scope `ConcertSyncClientUtil`)
- L146 _prototype_ `UWorld* GetCurrentWorld();` (scope `ConcertSyncClientUtil`)
- L149 _prototype_ `ULevel* GetExternalPersistentWorld();` (scope `ConcertSyncClientUtil`) — Return the Persistent Level if it is currently using external objects, i.e. one file per actor for world partitioning.
- L152 _prototype_ `bool IsWorldPartitionWorld();` (scope `ConcertSyncClientUtil`) — Return true if we are in a world partition world.
- L154 _prototype_ `FConcertPackageInfo FillPackageInfo(UPackage* InPackage, UObject* InAsset, const EConcertPackageUpdateType InPackageUpdateType);` (scope `ConcertSyncClientUtil`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Private/Replication/ConcertClientReplicationBridge.h` (Private)


#### class `UE::ConcertSyncClient::Replication::FConcertClientReplicationBridge`  
`class FConcertClientReplicationBridge : public IConcertClientReplicationBridge`  
_L20-73_
- inherits: `IConcertClientReplicationBridge`
- L24 _public prototype_ `FConcertClientReplicationBridge();`
- L28 _public prototype_ `virtual void PushTrackedObjects(TArrayView<const FSoftObjectPath> InTrackedObjects) override;`
- L29 _public prototype_ `virtual void PopTrackedObjects(TArrayView<const FSoftObjectPath> InTrackedObjects) override;`
- L30 _public prototype_ `virtual bool IsObjectAvailable(const FSoftObjectPath& Path) override;`
- L31 _public prototype_ `virtual UObject* FindObjectIfAvailable(const FSoftObjectPath& Path) override;`
- L32 _public function_ `virtual FConcertClientReplicationBridgeObjectEvent& OnObjectDiscovered() override`
- L33 _public function_ `virtual FConcertClientReplicationBridgeObjectPathEvent& OnObjectHidden() override`
- L47 _private member_ `TMap<FSoftObjectPath, FTrackedObjectInfo> TrackedObjects;` — The objects that wish to be tracked.
- L50 _private member_ `TSet<TWeakObjectPtr<UWorld>> LoadedWorlds;` — The set of worlds currently open on this client.
- L52 _private member_ `FConcertClientReplicationBridgeObjectEvent OnObjectDiscoveredDelegate;`
- L53 _private member_ `FConcertClientReplicationBridgeObjectPathEvent OnObjectRemovedDelegate;`
- L56 _private prototype_ `void SetupEngineDelegates();` — Setting up delegates for worlds
- L57 _private prototype_ `void SetupWorld(UWorld* World);`
- L58 _private prototype_ `void CleanupWorld(UWorld* World);`
- L61 _private prototype_ `void DiscoverTrackedObjectsInWorld(UWorld& World);` — Searching everything in world
- L62 _private prototype_ `void RemoveDiscoveredObjectsInWorld(UWorld& World);`
- L65 _private prototype_ `void DiscoverTrackedObjectsIn(UObject* AnalysedObject);` — Searching a specific object
- L66 _private prototype_ `void RemoveDiscoveredObjectsIn(UObject* Object);`
- L67 _private prototype_ `void DiscoverTrackedObjectsInActor(AActor* Actor);`
- L68 _private prototype_ `void RemoveDiscoveredObjectsInActor(AActor* Actor);`
- L71 _private prototype_ `void MarkAsDiscovered(TConstArrayView<TWeakObjectPtr<UObject>> DeferredDiscoveredObjects);` — Util for formally marking objects as discovered
- L72 _private prototype_ `void MarkAsUndiscovered(TConstArrayView<FSoftObjectPath> DeferredHiddenObjects);`

#### struct `UE::ConcertSyncClient::Replication::FConcertClientReplicationBridge::FTrackedObjectInfo`  
`struct FTrackedObjectInfo`  
_L38-44_
- L41 _public member_ `int32 TrackCounter = 0;` — Tracks the number of PushTrackedObjects calls. This entry is removed upon reaching 0.
- L43 _public member_ `TWeakObjectPtr<UObject> ResolvedObject;` — Cached object pointer to avoid constant resolving of the soft object ptr.

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace ConcertSyncClient` (scope `UE`)
- L18 _namespace_ `namespace Replication` (scope `UE::ConcertSyncClient`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Private/Replication/Manager/ReplicationManager.h` (Private)


#### class `UE::ConcertSyncClient::Replication::FReplicationManager`  
`class FReplicationManager : public IConcertClientReplicationManager`  
_L17-75_
- inherits: `IConcertClientReplicationManager`
- L22 _public prototype_ `FReplicationManager( TSharedRef<IConcertClientSession> InLiveSession, IConcertClientReplicationBridge& InBridge UE_LIFETIMEBOUND, EConcertSyncSessionFlags SessionFlags );`
- L30 _public prototype_ `void StartAcceptingJoinRequests();` — Starts accepting join requests. Must be called separately from constructor because of TSharedFromThis asserting if SharedThis is called in constructor.
- L33 _public prototype_ `virtual TFuture<FJoinReplicatedSessionResult> JoinReplicationSession(FJoinReplicatedSessionArgs Args) override;`
- L34 _public prototype_ `virtual void LeaveReplicationSession() override;`
- L35 _public prototype_ `virtual bool CanJoin() override;`
- L36 _public prototype_ `virtual bool IsConnectedToReplicationSession() override;`
- L37 _public prototype_ `virtual EStreamEnumerationResult ForEachRegisteredStream(TFunctionRef<EBreakBehavior(const FConcertReplicationStream& Stream)> Callback) const override;`
- L38 _public prototype_ `virtual TFuture<FConcertReplication_ChangeAuthority_Response> RequestAuthorityChange(FConcertReplication_ChangeAuthority_Request Args) override;`
- L39 _public prototype_ `virtual TFuture<FConcertReplication_QueryReplicationInfo_Response> QueryClientInfo(FConcertReplication_QueryReplicationInfo_Request Args) override;`
- L40 _public prototype_ `virtual TFuture<FConcertReplication_ChangeStream_Response> ChangeStream(FConcertReplication_ChangeStream_Request Args) override;`
- L41 _public prototype_ `virtual EAuthorityEnumerationResult ForEachClientOwnedObject(TFunctionRef<EBreakBehavior(const FSoftObjectPath& Object, TSet<FGuid>&& OwningStreams)>) const override;`
- L42 _public prototype_ `virtual TSet<FGuid> GetClientOwnedStreamsForObject(const FSoftObjectPath& ObjectPath) const override;`
- L43 _public prototype_ `virtual bool HasAuthorityOver(const FSoftObjectPath& ObjectPath) const override;`
- L44 _public prototype_ `virtual ESyncControlEnumerationResult ForEachSyncControlledObject(TFunctionRef<EBreakBehavior(const FConcertObjectInStreamID& Object)> Callback) const override;`
- L45 _public prototype_ `virtual uint32 NumSyncControlledObjects() const override;`
- L46 _public prototype_ `virtual bool HasSyncControl(const FConcertObjectInStreamID& Object) const override;`
- L47 _public prototype_ `virtual TFuture<FConcertReplication_ChangeMuteState_Response> ChangeMuteState(FConcertReplication_ChangeMuteState_Request Request) override;`
- L48 _public prototype_ `virtual TFuture<FConcertReplication_QueryMuteState_Response> QueryMuteState(FConcertReplication_QueryMuteState_Request Request) override;`
- L49 _public prototype_ `virtual TFuture<FConcertReplication_RestoreContent_Response> RestoreContent(FConcertReplication_RestoreContent_Request Request) override;`
- L50 _public prototype_ `virtual TFuture<FConcertReplication_PutState_Response> PutClientState(FConcertReplication_PutState_Request Request) override;`
- L51 _public prototype_ `virtual FOnPreStreamsChanged& OnPreStreamsChanged() override;`
- L52 _public prototype_ `virtual FOnPostStreamsChanged& OnPostStreamsChanged() override;`
- L53 _public prototype_ `virtual FOnPreAuthorityChanged& OnPreAuthorityChanged() override;`
- L54 _public prototype_ `virtual FOnPostAuthorityChanged& OnPostAuthorityChanged() override;`
- L55 _public prototype_ `virtual FSyncControlChanged& OnPreSyncControlChanged() override;`
- L56 _public prototype_ `virtual FSyncControlChanged& OnPostSyncControlChanged() override;`
- L57 _public prototype_ `virtual FOnRemoteEditApplied& OnPreRemoteEditApplied() override;`
- L58 _public prototype_ `virtual FOnRemoteEditApplied& OnPostRemoteEditApplied() override;`
- L64 _private member_ `TSharedRef<IConcertClientSession> Session;` — Session instance this manager was created for.
- L66 _private member_ `IConcertClientReplicationBridge& Bridge;` — The replication bridge is responsible for applying received data and generating data to send.
- L68 _private member_ `const EConcertSyncSessionFlags SessionFlags;` — These flags are passed along to all the states.
- L71 _private member_ `TSharedPtr<FReplicationManagerState> CurrentState;` — The current state this manager is in, e.g. waiting for connection request, connecting, connected, etc.
- L74 _private prototype_ `void OnChangeState(TSharedRef<FReplicationManagerState> NewState);` — Called by FReplicationManagerState to change the state.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ConcertSyncClient` (scope `UE`)
- L13 _namespace_ `namespace Replication` (scope `UE::ConcertSyncClient`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Private/Replication/Manager/ReplicationManagerState.h` (Private)


#### class `UE::ConcertSyncClient::Replication::FReplicationManagerState`  
`class FReplicationManagerState : public IConcertClientReplicationManager, public TSharedFromThis<FReplicationManagerState>`  
_L19-83_
- inherits: `IConcertClientReplicationManager,TSharedFromThis<FReplicationManagerState>`
- desc: Implements the State design pattern (see GOF) for FConcertClientReplicationManager. Depending on the handshake state, the replication manager will react differently to the implemented IConcertClientReplicationManager functions.
- L23 _public prototype_ `FReplicationManagerState(FReplicationManager& Owner);`
- L28 _public function_ `virtual EStreamEnumerationResult ForEachRegisteredStream(TFunctionRef<EBreakBehavior(const FConcertReplicationStream& Stream)> Callback) const override`
- L29 _public function_ `virtual TFuture<FConcertReplication_ChangeAuthority_Response> RequestAuthorityChange(FConcertReplication_ChangeAuthority_Request Args) override`
- L30 _public function_ `virtual TFuture<FConcertReplication_QueryReplicationInfo_Response> QueryClientInfo(FConcertReplication_QueryReplicationInfo_Request Args) override`
- L31 _public function_ `virtual TFuture<FConcertReplication_ChangeStream_Response> ChangeStream(FConcertReplication_ChangeStream_Request Args) override`
- L32 _public function_ `virtual EAuthorityEnumerationResult ForEachClientOwnedObject(TFunctionRef<EBreakBehavior(const FSoftObjectPath& Object, TSet<FGuid>&& OwningStreams)> Callback) const override`
- L33 _public function_ `virtual TSet<FGuid> GetClientOwnedStreamsForObject(const FSoftObjectPath& ObjectPath) const override`
- L34 _public function_ `virtual bool HasAuthorityOver(const FSoftObjectPath& ObjectPath) const override`
- L35 _public function_ `virtual ESyncControlEnumerationResult ForEachSyncControlledObject(TFunctionRef<EBreakBehavior(const FConcertObjectInStreamID& Object)> Callback) const override`
- L36 _public function_ `virtual uint32 NumSyncControlledObjects() const override`
- L37 _public function_ `virtual bool HasSyncControl(const FConcertObjectInStreamID& Object) const override`
- L38 _public function_ `virtual TFuture<FConcertReplication_ChangeMuteState_Response> ChangeMuteState(FConcertReplication_ChangeMuteState_Request) override`
- L39 _public function_ `virtual TFuture<FConcertReplication_QueryMuteState_Response> QueryMuteState(FConcertReplication_QueryMuteState_Request Request) override`
- L40 _public function_ `virtual TFuture<FConcertReplication_RestoreContent_Response> RestoreContent(FConcertReplication_RestoreContent_Request Request) override`
- L41 _public function_ `virtual TFuture<FConcertReplication_PutState_Response> PutClientState(FConcertReplication_PutState_Request Request) override`
- L42 _public function_ `virtual FOnPreStreamsChanged& OnPreStreamsChanged() override`
- L43 _public function_ `virtual FOnPostStreamsChanged& OnPostStreamsChanged() override`
- L44 _public function_ `virtual FOnPreAuthorityChanged& OnPreAuthorityChanged() override`
- L45 _public function_ `virtual FOnPostAuthorityChanged& OnPostAuthorityChanged() override`
- L46 _public function_ `virtual FSyncControlChanged& OnPreSyncControlChanged() override`
- L47 _public function_ `virtual FSyncControlChanged& OnPostSyncControlChanged() override`
- L48 _public function_ `virtual FOnRemoteEditApplied& OnPreRemoteEditApplied() override`
- L49 _public function_ `virtual FOnRemoteEditApplied& OnPostRemoteEditApplied() override`
- L54 _protected member_ `FOnPreStreamsChanged OnPreStreamsChangedDelegate;`
- L55 _protected member_ `FOnPostStreamsChanged OnPostStreamsChangedDelegate;`
- L56 _protected member_ `FOnPreAuthorityChanged OnPreAuthorityChangedDelegate;`
- L57 _protected member_ `FOnPostAuthorityChanged OnPostAuthorityChangedDelegate;`
- L58 _protected member_ `FSyncControlChanged OnPreSyncControlChangedDelegate;`
- L59 _protected member_ `FSyncControlChanged OnPostSyncControlChangedDelegate;`
- L60 _protected member_ `FOnRemoteEditApplied OnPreRemoteEditAppliedDelegate;`
- L61 _protected member_ `FOnRemoteEditApplied OnPostRemoteEditAppliedDelegate;`
- L67 _protected prototype_ `void ChangeState(TSharedRef<FReplicationManagerState> NewState);` — Subclasses can change the state with this function. Important: This decrements the reference count so it may destroy your state unless you keep it alive manually!
- L69 _protected function_ `const FReplicationManager& GetOwner() const`
- L70 _protected function_ `FReplicationManager& GetOwner()`
- L75 _private member_ `FReplicationManager& Owner;` — Used to change the state on the owning manager.
- L82 _private function_ `virtual void OnEnterState()` — Do any logic for entering state here instead of constructor. Important to handle "recursive" calls to ChangState and also constructor does not have access to SharedThis.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertSyncClient` (scope `UE`)
- L11 _namespace_ `namespace Replication` (scope `UE::ConcertSyncClient`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Private/Replication/Manager/ReplicationManagerState_Connected.h` (Private)


#### struct `UE::ConcertSyncClient::Replication::FChangeStreamPredictedChange`  
`struct FChangeStreamPredictedChange`  
_L26-30_
- L28 _public member_ `TMap<FSoftObjectPath, TArray<FGuid>> ObjectsRemovedFromStream;`
- L29 _public member_ `TMap<FSoftObjectPath, TArray<FGuid>> AuthorityRemovedFromStreams;`

#### class `UE::ConcertSyncClient::Replication::FReplicationManagerState_Connected`  
`class FReplicationManagerState_Connected : public FReplicationManagerState`  
_L39-158_
- inherits: `FReplicationManagerState`
- desc: State for when the client has successfully completed a replication handshake. Every tick this state tries to - collect data and sends it to the server - process received data and applies it
- L43 _public prototype_ `FReplicationManagerState_Connected( TSharedRef<IConcertClientSession> InLiveSession, IConcertClientReplicationBridge& ReplicationBridge UE_LIFETIMEBOUND, FReplicationManager& Owner UE_LIFETIMEBOUND, EConcertSyncSessionFlags SessionFlags, TArray<FConcertReplicationStream> InitialStreams, const FConcertReplication_ChangeSyncControl& InitialSyncControl );`
- L54 _public prototype_ `virtual TFuture<FJoinReplicatedSessionResult> JoinReplicationSession(FJoinReplicatedSessionArgs Args) override;`
- L55 _public prototype_ `virtual void LeaveReplicationSession() override;`
- L56 _public function_ `virtual bool CanJoin() override`
- L57 _public function_ `virtual bool IsConnectedToReplicationSession() override`
- L58 _public prototype_ `virtual EStreamEnumerationResult ForEachRegisteredStream(TFunctionRef<EBreakBehavior(const FConcertReplicationStream& Stream)> Callback) const override;`
- L59 _public prototype_ `virtual TFuture<FConcertReplication_ChangeAuthority_Response> RequestAuthorityChange(FConcertReplication_ChangeAuthority_Request Args) override;`
- L60 _public prototype_ `virtual TFuture<FConcertReplication_QueryReplicationInfo_Response> QueryClientInfo(FConcertReplication_QueryReplicationInfo_Request Args) override;`
- L61 _public prototype_ `virtual TFuture<FConcertReplication_ChangeStream_Response> ChangeStream(FConcertReplication_ChangeStream_Request Args) override;`
- L62 _public prototype_ `virtual EAuthorityEnumerationResult ForEachClientOwnedObject(TFunctionRef<EBreakBehavior(const FSoftObjectPath& Object, TSet<FGuid>&& OwningStreams)> Callback) const override;`
- L63 _public prototype_ `virtual TSet<FGuid> GetClientOwnedStreamsForObject(const FSoftObjectPath& ObjectPath) const override;`
- L64 _public prototype_ `virtual bool HasAuthorityOver(const FSoftObjectPath& ObjectPath) const override;`
- L65 _public prototype_ `virtual ESyncControlEnumerationResult ForEachSyncControlledObject(TFunctionRef<EBreakBehavior(const FConcertObjectInStreamID& Object)> Callback) const override;`
- L66 _public function_ `virtual uint32 NumSyncControlledObjects() const override`
- L67 _public function_ `virtual bool HasSyncControl(const FConcertObjectInStreamID& Object) const override`
- L68 _public prototype_ `virtual TFuture<FConcertReplication_ChangeMuteState_Response> ChangeMuteState(FConcertReplication_ChangeMuteState_Request) override;`
- L69 _public prototype_ `virtual TFuture<FConcertReplication_QueryMuteState_Response> QueryMuteState(FConcertReplication_QueryMuteState_Request Request) override;`
- L70 _public prototype_ `virtual TFuture<FConcertReplication_RestoreContent_Response> RestoreContent(FConcertReplication_RestoreContent_Request Request) override;`
- L71 _public prototype_ `virtual TFuture<FConcertReplication_PutState_Response> PutClientState(FConcertReplication_PutState_Request Request) override;`
- L77 _private member_ `const TSharedRef<IConcertClientSession> LiveSession;` — Passed to FReplicationManagerState_Disconnected
- L79 _private member_ `IConcertClientReplicationBridge& ReplicationBridge;` — Passed to FReplicationManagerState_Disconnected
- L81 _private member_ `const EConcertSyncSessionFlags SessionFlags;` — Passed to FReplicationManagerState_Disconnected and used to determine whether certain operations are supported by the server.
- L83 _private member_ `TArray<FConcertReplicationStream> RegisteredStreams;` — The streams this client has registered with the server.
- L86 _private member_ `const TUniquePtr<ConcertSyncCore::IObjectReplicationFormat> ReplicationFormat;` — The format this client will use for sending & receiving data.
- L90 _private member_ `FLocalSyncControl SyncControl;` — Decides whether an object should be replicated.
- L92 _private member_ `FClientReplicationDataCollector ReplicationDataSource;` — Used as source of replication data.
- L95 _private typedef_ `using FDataRelayThrottledByFrequency = ConcertSyncCore::TObjectProcessorProxy_Frequency<ConcertSyncCore::FObjectReplicationSender>;` — Sends to remote endpoint and makes sure the objects are replicated at the specified frequency settings.
- L97 _private member_ `FDataRelayThrottledByFrequency Sender;` — Sends data collected by ReplicationDataSource to the server.
- L101 _private member_ `const TSharedRef<ConcertSyncCore::FObjectReplicationCache> ReceivedDataCache;` — Stores data received by Receiver until it is consumed by ReceivedReplicationQueuer.
- L103 _private member_ `ConcertSyncCore::FObjectReplicationReceiver Receiver;` — Receives data from remote endpoints via message bus.
- L105 _private member_ `const TSharedRef<FClientReplicationDataQueuer> ReceivedReplicationQueuer;` — Queues data until is can be processed. Shared because FObjectReplicationCache API expects it.
- L107 _private member_ `FObjectReplicationApplierProcessor ReplicationApplier;` — Processes data from ReceivedReplicationQueuer once we tick.
- L110 _private prototype_ `virtual void OnEnterState() override;`
- L123 _private prototype_ `void Tick(IConcertClientSession& Session, float DeltaTime);` — Ticks this client. This processes: - data that is to be sent - data that was received The tasks have a time budget so that the frame rate remains stable. It is configured in the project settings TODO: Add config
- L126 _private prototype_ `void HandleChangeClientEvent(const FConcertSessionContext& Context, const FConcertReplication_ChangeClientEvent& Event);` — Handle the server telling us that our state has changed.
- L129 _private prototype_ `FChangeStreamPredictedChange PredictAndApplyStreamChangeRemovedObjects(const FConcertReplication_ChangeStream_Request& Request);` — Changes the local state assuming that Request will succeed.
- L131 _private prototype_ `void RevertPredictedStreamChangeRemovedObjects(const FChangeStreamPredictedChange& PredictedChange);` — Reverts changes previously made by PredictStreamChangeRemovedObjects.
- L133 _private prototype_ `void FinalizePredictedStreamChange(const FConcertReplication_ChangeStream_Request& StreamChange);` — Applies stream changes that we previously predicted using PredictStreamChangeRemovedObjects.
- L135 _private prototype_ `void UpdateReplicatedObjectsAfterStreamChange(const FConcertReplication_ChangeStream_Request& Request);` — Updates replicated objects affected by the change request.
- L138 _private prototype_ `TMap<FSoftObjectPath, TArray<FGuid>> ApplyAuthorityChangeRemovedObjects(const FConcertReplication_ChangeAuthority_Request& Request);` — Changes the local state assuming that Request will succeed.
- L140 _private prototype_ `void RevertAuthorityChangeReleasedObjects(const TMap<FSoftObjectPath, TArray<FGuid>>& PredictedChange);` — Reverts changes previously made by PredictAuthorityChangeReleasedObjects.
- L142 _private prototype_ `void FinalizePredictedAuthorityChange(const FConcertReplication_ChangeAuthority_Request& AuthorityChange, const TMap<FSoftObjectPath, FConcertStreamArray>& RejectedObjects, const FConcertReplication_ChangeSyncControl& SyncControlChange);` — Applies authority changes that we previously predicted using PredictAuthorityChangeReleasedObjects.
- L144 _private prototype_ `void UpdateReplicatedObjectsAfterAuthorityChange(const FConcertReplication_ChangeAuthority_Request& Request, const TMap<FSoftObjectPath, FConcertStreamArray>& RejectedObjects);` — Updates the objects which should be replicated after changing authority.
- L154 _private prototype_ `void UpdateReplicatedObjectAfterServerSideChange(const FConcertQueriedClientInfo& NewState);` — Updates the objects which should be replicated after they have been reset to a completely new state (e.g. when restoring session content manually).
- L157 _private prototype_ `FConcertObjectReplicationSettings GetObjectFrequencySettings(const FConcertReplicatedObjectId& Object) const;` — Callback to Sender for obtaining an object's frequency settings.

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace ConcertSyncClient` (scope `UE`)
- L24 _namespace_ `namespace Replication` (scope `UE::ConcertSyncClient`)
- L161 _namespace_ `namespace UE`
- L161 _namespace_ `namespace ConcertSyncClient` (scope `UE`)
- L161 _namespace_ `namespace Replication` (scope `UE::ConcertSyncClient`)
- L173 _prototype_ `OnPreAuthorityChangedDelegate.Broadcast();` (scope `UE::ConcertSyncClient::Replication`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Private/Replication/Manager/ReplicationManagerState_Disconnected.h` (Private)


#### class `UE::ConcertSyncClient::Replication::FReplicationManagerState_Disconnected`  
`class FReplicationManagerState_Disconnected : public FReplicationManagerState`  
_L14-40_
- inherits: `FReplicationManagerState`
- desc: Initial state: waiting for a call to JoinReplicationSession to join replication session.
- L18 _public prototype_ `FReplicationManagerState_Disconnected( TSharedRef<IConcertClientSession> LiveSession, IConcertClientReplicationBridge& ReplicationBridge UE_LIFETIMEBOUND, FReplicationManager& Owner UE_LIFETIMEBOUND, EConcertSyncSessionFlags SessionFlags );`
- L26 _public prototype_ `virtual TFuture<FJoinReplicatedSessionResult> JoinReplicationSession(FJoinReplicatedSessionArgs Args) override;`
- L27 _public prototype_ `virtual void LeaveReplicationSession() override;`
- L28 _public function_ `virtual bool CanJoin() override`
- L29 _public function_ `virtual bool IsConnectedToReplicationSession() override`
- L35 _private member_ `TSharedRef<IConcertClientSession> LiveSession;` — Passed to FReplicationManagerState_Handshaking
- L37 _private member_ `IConcertClientReplicationBridge& ReplicationBridge;` — Passed to FReplicationManagerState_Handshaking
- L39 _private member_ `const EConcertSyncSessionFlags SessionFlags;` — Passed to FReplicationManagerState_Handshaking

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertSyncClient` (scope `UE`)
- L11 _namespace_ `namespace Replication` (scope `UE::ConcertSyncClient`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Private/Replication/Manager/ReplicationManagerState_Handshaking.h` (Private)


#### class `UE::ConcertSyncClient::Replication::FReplicationManagerState_Handshaking`  
`class FReplicationManagerState_Handshaking : public FReplicationManagerState`  
_L14-55_
- inherits: `FReplicationManagerState`
- desc: Initial state: waiting for a call to JoinReplicationSession to join replication session.
- L18 _public prototype_ `FReplicationManagerState_Handshaking( FJoinReplicatedSessionArgs RequestArgs, TPromise<FJoinReplicatedSessionResult> JoinSessionPromise, TSharedRef<IConcertClientSession> LiveSession, IConcertClientReplicationBridge& ReplicationBridge UE_LIFETIMEBOUND, FReplicationManager& Owner UE_LIFETIMEBOUND, EConcertSyncSessionFlags SessionFlags );`
- L29 _public prototype_ `virtual TFuture<FJoinReplicatedSessionResult> JoinReplicationSession(FJoinReplicatedSessionArgs Args) override;`
- L30 _public prototype_ `virtual void LeaveReplicationSession() override;`
- L31 _public function_ `virtual bool CanJoin() override`
- L32 _public function_ `virtual bool IsConnectedToReplicationSession() override`
- L37 _private member_ `FJoinReplicatedSessionArgs RequestArgs;`
- L40 _private member_ `TPromise<FJoinReplicatedSessionResult> JoinSessionPromise;` — Promise for finishing the handshake.
- L41 _private member_ `bool bFulfilledPromise = false;`
- L44 _private member_ `TSharedRef<IConcertClientSession> LiveSession;` — Passed to FReplicationManagerState_Handshaking
- L46 _private member_ `IConcertClientReplicationBridge& ReplicationBridge;` — Passed to FReplicationManagerState_Handshaking
- L48 _private member_ `const EConcertSyncSessionFlags SessionFlags;` — Passed to FReplicationManagerState_Handshaking
- L51 _private prototype_ `virtual void OnEnterState() override;`
- L54 _private prototype_ `void ReturnToDisconnectedState();`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertSyncClient` (scope `UE`)
- L11 _namespace_ `namespace Replication` (scope `UE::ConcertSyncClient`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Private/Replication/Manager/Utils/AuthorityRemovalPrediction.h` (Private)


#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace ConcertSyncClient` (scope `UE`)
- L17 _namespace_ `namespace Replication` (scope `UE::ConcertSyncClient`)
- L23 _prototype_ `template<typename TStreamArrayType, typename TProjectStreamArray> requires std::is_invocable_r_v<const TArray<FGuid>&, TProjectStreamArray, const TStreamArrayType&> TMap<FSoftObjectPath, TArray<FGuid>> RemoveObjectsAndTrackRemovedAuthorityGeneric( FClientReplicationDataCollector& ReplicationDataSource, const TMap<FSoftObjectPath, TStreamArrayType>& ObjectsToRemove, TProjectStreamArray&& Project );` (scope `UE::ConcertSyncClient::Replication`) — Removes ObjectsToRemove and returns the authority that was actually removed, possibly to be reverted later.
- L31 _prototype_ `template<typename TStreamArrayType, typename TProjectStreamArray> requires std::is_invocable_r_v<const TArray<FGuid>&, TProjectStreamArray, const TStreamArrayType&> bool HasAuthorityChangesGeneric( FClientReplicationDataCollector& ReplicationDataSource, const TMap<FSoftObjectPath, TStreamArrayType>& ObjectsToRemove, TProjectStreamArray&& Project );` (scope `UE::ConcertSyncClient::Replication`) — @return Whether RemoveObjectsAndTrackRemovedAuthority would make any changes. This is useful for avoiding broadcasting change events.
- L38 _prototype_ `TMap<FSoftObjectPath, TArray<FGuid>> RemoveObjectsAndTrackRemovedAuthority( FClientReplicationDataCollector& ReplicationDataSource, const TMap<FSoftObjectPath, FConcertStreamArray>& ObjectsToRemove );` (scope `UE::ConcertSyncClient::Replication`) — Inline version for FConcertStreamArray & TArray<FGuid>
- L41 _prototype_ `TMap<FSoftObjectPath, TArray<FGuid>> RemoveObjectsAndTrackRemovedAuthority( FClientReplicationDataCollector& ReplicationDataSource, const TMap<FSoftObjectPath, TArray<FGuid>>& ObjectsToRemove );` (scope `UE::ConcertSyncClient::Replication`)
- L44 _prototype_ `bool HasAuthorityChanges(FClientReplicationDataCollector& ReplicationDataSource, const TMap<FSoftObjectPath, TArray<FGuid>>& ObjectsToRemove);` (scope `UE::ConcertSyncClient::Replication`)
- L45 _prototype_ `bool HasAuthorityChanges(FClientReplicationDataCollector& ReplicationDataSource, const TMap<FSoftObjectPath, FConcertStreamArray>& ObjectsToRemove);` (scope `UE::ConcertSyncClient::Replication`)
- L48 _namespace_ `namespace UE`
- L48 _namespace_ `namespace ConcertSyncClient` (scope `UE`)
- L48 _namespace_ `namespace Replication` (scope `UE::ConcertSyncClient`)
- L52 _function_ `template<typename TStreamArrayType, typename TProjectStreamArray> requires std::is_invocable_r_v<const TArray<FGuid>&, TProjectStreamArray, const TStreamArrayType&> TMap<FSoftObjectPath, TArray<FGuid>> RemoveObjectsAndTrackRemovedAuthorityGeneric( FClientReplicationDataCollector& ReplicationDataSource, const TMap<FSoftObjectPath, TStreamArrayType>& ObjectsToRemove, TProjectStreamArray&& Project )` (scope `UE::ConcertSyncClient::Replication`) — Removes ObjectsToRemove and returns the authority that was actually removed, possibly to be reverted later.
- L67 _function_ `` (scope `UE::ConcertSyncClient::Replication::RemoveObjectsAndTrackRemovedAuthorityGeneric`)
- L79 _function_ `template<typename TStreamArrayType, typename TProjectStreamArray> requires std::is_invocable_r_v<const TArray<FGuid>&, TProjectStreamArray, const TStreamArrayType&> bool HasAuthorityChangesGeneric( FClientReplicationDataCollector& ReplicationDataSource, const TMap<FSoftObjectPath, TStreamArrayType>& ObjectsToRemove, TProjectStreamArray&& Project )` (scope `UE::ConcertSyncClient::Replication`) — @return Whether RemoveObjectsAndTrackRemovedAuthority would make any changes. This is useful for avoiding broadcasting change events.
- L86 _function_ `` (scope `UE::ConcertSyncClient::Replication::HasAuthorityChangesGeneric`)
- L89 _function_ `` (scope `UE::ConcertSyncClient::Replication::HasAuthorityChangesGeneric::__anon7b5368e80202`)
- L95 _function_ `inline TMap<FSoftObjectPath, TArray<FGuid>> RemoveObjectsAndTrackRemovedAuthority( FClientReplicationDataCollector& ReplicationDataSource, const TMap<FSoftObjectPath, FConcertStreamArray>& ObjectsToRemove )` (scope `UE::ConcertSyncClient::Replication`)
- L102 _function_ `ReplicationDataSource, ObjectsToRemove, [](const FConcertStreamArray& StreamArray)-> const TArray<FGuid>&` (scope `UE::ConcertSyncClient::Replication::RemoveObjectsAndTrackRemovedAuthority`)
- L106 _function_ `inline TMap<FSoftObjectPath, TArray<FGuid>> RemoveObjectsAndTrackRemovedAuthority( FClientReplicationDataCollector& ReplicationDataSource, const TMap<FSoftObjectPath, TArray<FGuid>>& ObjectsToRemove )` (scope `UE::ConcertSyncClient::Replication`)
- L113 _function_ `ReplicationDataSource, ObjectsToRemove, [](const TArray<FGuid>& StreamArray)-> const TArray<FGuid>&` (scope `UE::ConcertSyncClient::Replication::RemoveObjectsAndTrackRemovedAuthority`)
- L117 _function_ `inline bool HasAuthorityChanges(FClientReplicationDataCollector& ReplicationDataSource, const TMap<FSoftObjectPath, TArray<FGuid>>& ObjectsToRemove)` (scope `UE::ConcertSyncClient::Replication`)
- L120 _function_ `return HasAuthorityChangesGeneric<TArray<FGuid>>(ReplicationDataSource, ObjectsToRemove, [](const TArray<FGuid>& StreamArray)-> const TArray<FGuid>& { return StreamArray; } );` (scope `UE::ConcertSyncClient::Replication::HasAuthorityChanges`)
- L124 _function_ `inline bool HasAuthorityChanges(FClientReplicationDataCollector& ReplicationDataSource, const TMap<FSoftObjectPath, FConcertStreamArray>& ObjectsToRemove)` (scope `UE::ConcertSyncClient::Replication`)
- L127 _function_ `return HasAuthorityChangesGeneric<FConcertStreamArray>(ReplicationDataSource, ObjectsToRemove, [](const FConcertStreamArray& StreamArray)-> const TArray<FGuid>& { return StreamArray.StreamIds; } );` (scope `UE::ConcertSyncClient::Replication::HasAuthorityChanges`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Private/Replication/Manager/Utils/ContentComparisionUtils.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertSyncClient` (scope `UE`)
- L11 _namespace_ `namespace Replication` (scope `UE::ConcertSyncClient`)
- L16 _prototype_ `bool AreStreamsEquivalent(TConstArrayView<FConcertBaseStreamInfo> NewStreams, TConstArrayView<FConcertReplicationStream> RegisteredStreams);` (scope `UE::ConcertSyncClient::Replication`) — @return Whether NewStreams would change nothing about RegisteredStreams if replaced.
- L19 _prototype_ `bool IsAuthorityEquivalent(TConstArrayView<FConcertAuthorityClientInfo> NewAuthority, const FClientReplicationDataCollector& Replicator);` (scope `UE::ConcertSyncClient::Replication`) — @return Whether assigning NewAuthority to Replicator would change any authority.

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Private/Replication/Manager/Utils/LocalSyncControl.h` (Private)


#### class `UE::ConcertSyncClient::Replication::FLocalSyncControl`  
`class FLocalSyncControl : public FNoncopyable , ConcertSyncCore::Replication::FSyncControlState`  
_L20-173_
- inherits: `FNoncopyable,ConcertSyncCore::Replication::FSyncControlState`
- desc: Receives network messages that explicitly and implicitly change sync control. Those network messages are fed into FSyncControlState, which parses the messages. Sync control is the set of objects this client is allowed to replicate.
- L24 _private typedef_ `using Detail = FSyncControlState;`
- L27 _public function_ `explicit FLocalSyncControl(IConcertSession& InSession UE_LIFETIMEBOUND) : Session(InSession)`
- L33 _public function_ `~FLocalSyncControl()`
- L42 _public typedef_ `using FPredictedObjectRemoval = FSyncControlState::FPredictedObjectRemoval;`
- L46 _public function_ `void ProcessSyncControlChange(const FConcertReplication_ChangeSyncControl& Event)` — Stores the given change in this data structure.
- L54 _public function_ `void ProcessAuthorityChange(const FConcertReplication_ChangeAuthority_Request& Request, const FConcertReplication_ChangeSyncControl& Response)` — Applies implicit and explicit changes to the client's sync control resulting from a completed authority change request and response.
- L65 _public function_ `void ProcessStreamChange(const FConcertReplication_ChangeStream_Request& Request)` — Applies implicit changes to the client's sync control resulting from losing authority from objects removed from the stream. You must validate that the request has also been accepted by the server!
- L76 _public function_ `FPredictedObjectRemoval PredictAndApplyMuteChanges(const FConcertReplication_ChangeMuteState_Request& Request)` — Applies the implicit changes made by the request assuming the request will be accepted. @return The removed objects to be passed to ApplyOrRevertMuteResponse.
- L96 _public function_ `void ApplyOrRevertMuteResponse(const FPredictedObjectRemoval& RemovedByRequest, const FConcertReplication_ChangeMuteState_Response& Response)` — Either reverts previous changes made if the request was rejected, or applies the sync control returned by the server otherwise.
- L118 _public function_ `FPredictedObjectRemoval PredictAndApplyRestoreContentChanges(const FConcertReplication_RestoreContent_Request& Request)` — Applies the implicit changes made by the request assuming the request will be accepted. @return The removed objects to be passed to ApplyOrRevertRestoreContentResponse.
- L138 _public function_ `void ApplyOrRevertRestoreContentResponse(const FPredictedObjectRemoval& RemovedByRequest, const FConcertReplication_RestoreContent_Response& Response)` — Either reverts previous changes made if the request was rejected, or applies the sync control returned by the server otherwise.
- L157 _public prototype_ `void PredictAndApplyPutStateChanges(const FConcertReplication_RestoreContent_Request& Request);`
- L160 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FSyncControlChanged);`
- L161 _public function_ `FSyncControlChanged& OnPreSyncControlChanged()`
- L162 _public function_ `FSyncControlChanged& OnPostSyncControlChanged()`
- L167 _private member_ `IConcertSession& Session;` — The session to receive sync control changes on.
- L169 _private member_ `FSyncControlChanged OnPreSyncControlChangedDelegate;`
- L170 _private member_ `FSyncControlChanged OnPostSyncControlChangedDelegate;`
- L172 _private function_ `void OnChangeSyncControl(const FConcertSessionContext&, const FConcertReplication_ChangeSyncControl& Event)`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ConcertSyncClient` (scope `UE`)
- L12 _namespace_ `namespace Replication` (scope `UE::ConcertSyncClient`)
- L80 _function_ `` (scope `UE::ConcertSyncClient::Replication::FLocalSyncControl::PredictAndApplyMuteChanges`)
- L100 _function_ `` (scope `UE::ConcertSyncClient::Replication::FLocalSyncControl::ApplyOrRevertMuteResponse`)
- L122 _function_ `` (scope `UE::ConcertSyncClient::Replication::FLocalSyncControl::PredictAndApplyRestoreContentChanges`)
- L142 _function_ `` (scope `UE::ConcertSyncClient::Replication::FLocalSyncControl::ApplyOrRevertRestoreContentResponse`)
- L160 _delegate_ `DECLARE_MULTICAST_DELEGATE(FSyncControlChanged);`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Private/Replication/Manager/Utils/NetworkMessageLogging.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertSyncClient` (scope `UE`)
- L11 _namespace_ `namespace Replication` (scope `UE::ConcertSyncClient`)
- L13 _externvar_ `extern TAutoConsoleVariable<bool> CVarSimulateAuthorityTimeouts;` (scope `UE::ConcertSyncClient::Replication`)
- L15 _externvar_ `extern TAutoConsoleVariable<bool> CVarSimulateQueryTimeouts;` (scope `UE::ConcertSyncClient::Replication`) — Whether the client should pretend that query requests timed out instead of sending to the server.
- L17 _externvar_ `extern TAutoConsoleVariable<bool> CVarSimulateStreamChangeTimeouts;` (scope `UE::ConcertSyncClient::Replication`) — Whether the client should pretend that stream change requests timed out instead of sending to the server.
- L20 _externvar_ `extern TAutoConsoleVariable<bool> CVarSimulateAuthorityRejection;` (scope `UE::ConcertSyncClient::Replication`) — Whether the client should pretend that authority change requests were rejected.
- L22 _externvar_ `extern TAutoConsoleVariable<bool> CVarSimulateMuteRequestRejection;` (scope `UE::ConcertSyncClient::Replication`) — Whether the client should pretend that mute change requests were rejected.
- L25 _externvar_ `extern TAutoConsoleVariable<bool> CVarLogStreamRequestsAndResponsesOnClient;` (scope `UE::ConcertSyncClient::Replication`) — Whether to log changes to streams.
- L27 _externvar_ `extern TAutoConsoleVariable<bool> CVarLogAuthorityRequestsAndResponsesOnClient;` (scope `UE::ConcertSyncClient::Replication`) — Whether to log changes to authority.
- L29 _externvar_ `extern TAutoConsoleVariable<bool> CVarLogMuteRequestsAndResponsesOnClient;` (scope `UE::ConcertSyncClient::Replication`) — Whether to log changes to the mute state.
- L31 _externvar_ `extern TAutoConsoleVariable<bool> CVarLogRestoreContentRequestsAndResponsesOnClient;` (scope `UE::ConcertSyncClient::Replication`) — Whether to log restore content requests and responses.
- L33 _externvar_ `extern TAutoConsoleVariable<bool> CVarLogChangeClientsRequestsAndResponsesOnClient;` (scope `UE::ConcertSyncClient::Replication`) — Whether to log requests and responses that change multiple clients in one go.
- L35 _externvar_ `extern TAutoConsoleVariable<bool> CVarLogChangeClientEventsOnClient;` (scope `UE::ConcertSyncClient::Replication`) — Whether to log messages from the server that notify us that the client's content has changed.
- L38 _function_ `template<typename TMessage> static void LogNetworkMessage(const TAutoConsoleVariable<bool>& ShouldLog, const TMessage& Message)` (scope `UE::ConcertSyncClient::Replication`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Private/Replication/Manager/Utils/ReplicationManagerUtils.h` (Private)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ConcertSyncClient` (scope `UE`)
- L12 _namespace_ `namespace Replication` (scope `UE::ConcertSyncClient`)
- L15 _prototype_ `TFuture<FConcertReplication_ChangeAuthority_Response> RejectAll(FConcertReplication_ChangeAuthority_Request&& Args);` (scope `UE::ConcertSyncClient::Replication`) — Creates a fulfilled future which rejects all items in FConcertChangeAuthority_Request::TakeAuthority.
- L18 _prototype_ `TMap<FSoftObjectPath, TArray<FGuid>> ComputeRemovedObjects( const TConstArrayView<FConcertReplicationStream> RegisteredStreams, const FConcertReplication_ChangeStream_Request& Request );` (scope `UE::ConcertSyncClient::Replication`) — Enumerates the objects that will be removed by Request.

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Private/Replication/Processing/ClientReplicationDataCollector.h` (Private)


#### class `UE::ConcertSyncClient::Replication::FClientReplicationDataCollector`  
`class FClientReplicationDataCollector : public ConcertSyncCore::IReplicationDataSource`  
_L36-118_
- inherits: `ConcertSyncCore::IReplicationDataSource`
- desc: Exposes UObject instances to an FObjectReplicationProcessor. IConcertClientReplicationBridge tracks UObject lifetime, this class exposes them.
- L40 _public prototype_ `DECLARE_DELEGATE_RetVal(const TArray<FConcertReplicationStream>*, FGetClientStreams);`
- L42 _public prototype_ `FClientReplicationDataCollector( IConcertClientReplicationBridge& InReplicationBridge UE_LIFETIMEBOUND, ConcertSyncCore::IObjectReplicationFormat& InReplicationFormat UE_LIFETIMEBOUND, const FLocalSyncControl& SyncControl UE_LIFETIMEBOUND, FGetClientStreams InGetStreamsDelegate, const FGuid& InClientId );`
- L56 _public prototype_ `void AddReplicatedObjectStreams(const FSoftObjectPath& Object, TArrayView<const FGuid> AddedStreams);` — Indicates that this object should start replicating for the given streams. @param Object The object that should start replicating @param AddedStreams The streams determine which properties are to be replicated
- L62 _public prototype_ `void RemoveReplicatedObjectStreams(const FSoftObjectPath& Object, TArrayView<const FGuid> RemovedStreams);` — Indicates that certain properties of an object should no longer be replicated. @param Object The object that should is affected by the stream change @param RemovedStreams The properties in these streams will no longer be replicated
- L68 _public prototype_ `void OnObjectStreamModified(const FSoftObjectPath& Object, TArrayView<const FGuid> PutStreams);` — Called when the client modifies pre-existing object. Adjusts any inflight replication if needed. @param Object The object that should start replicating @param PutStreams The streams determine which properties are to be replicated
- L71 _public prototype_ `void ClearReplicatedObjects();` — Clears all currently replicated objects.
- L75 _public prototype_ `template<typename TCallback> requires std::is_invocable_r_v<EBreakBehavior, TCallback, const FSoftObjectPath&> void ForEachOwnedObject(TCallback&& Callback) const;` — Iterates every object for which there is at least one owning stream.
- L78 _public prototype_ `template<typename TCallback> requires std::is_invocable_r_v<EBreakBehavior, TCallback, const FSoftObjectPath&, const FGuid&> void ForEachOwnedObjectAndStream(TCallback&& Callback) const;` — Iterates every object and stream assigned to it.
- L80 _public prototype_ `void AppendOwningStreamsForObject(const FSoftObjectPath& ObjectPath, TSet<FGuid>& Paths) const;` — Writes all owning streams for ObjectPath into Paths.
- L83 _public prototype_ `bool OwnsObjectInStream(const FSoftObjectPath& ObjectPath, const FGuid& StreamId) const;` — @return Whether ObjectPath is owned with StreamId.
- L85 _public prototype_ `bool OwnsObjectInAnyStream(const FSoftObjectPath& ObjectPath) const;` — @return Whether ObjectPath owns ObjectPath in any stream.
- L88 _public prototype_ `TArray<FGuid> GetStreamsOwningObject(const FSoftObjectPath& ObjectPath) const;` — @return All streams containing ObjectPath that we have authority over within that stream.
- L91 _public prototype_ `virtual void ConsumePendingObjects(TFunctionRef<void(const ConcertSyncCore::FPendingObjectReplicationInfo& Info, ConcertSyncCore::IReplicationDataItem& Item)> InProcess) override;`
- L97 _private member_ `IConcertClientReplicationBridge& Bridge;` — Gets and tracks replicated objects
- L99 _private member_ `ConcertSyncCore::IObjectReplicationFormat& ReplicationFormat;` — Used to create the replication data sent to the server.
- L102 _private member_ `const FLocalSyncControl& SyncControl;` — Tells us whether we're allowed to replicate an object in a stream.
- L105 _private member_ `const FGetClientStreams GetStreamsDelegate;` — Gets the stream of the managed client.
- L108 _private member_ `const FGuid ClientId;` — Endpoint ID of the client
- L111 _private member_ `TMap<FSoftObjectPath, TArray<FObjectInfo>> ObjectsToReplicate;` — The objects and their properties to replicate
- L113 _private member_ `int32 NumTrackedObjects = 0;` — Cached number of FObjectInfo in ObjectsToReplicate that have a valid FObjectInfo::ObjectCache.
- L116 _private prototype_ `void StartTrackingObject(UObject& Object);` — Handle events from bridge
- L117 _private prototype_ `void StopTrackingObject(const FSoftObjectPath& ObjectPath);`
- L121 _function_ `template <typename TCallback> requires std::is_invocable_r_v<EBreakBehavior, TCallback, const FSoftObjectPath&> void FClientReplicationDataCollector::ForEachOwnedObject(TCallback&& Callback) const`
- L133 _function_ `template <typename TCallback> requires std::is_invocable_r_v<EBreakBehavior, TCallback, const FSoftObjectPath&, const FGuid&> void FClientReplicationDataCollector::ForEachOwnedObjectAndStream(TCallback&& Callback) const`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace ConcertSyncCore` (scope `UE`)
- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace ConcertSyncClient` (scope `UE`)
- L28 _namespace_ `namespace Replication` (scope `UE::ConcertSyncClient`)
- L40 _delegate_ `DECLARE_DELEGATE_RetVal(const TArray<FConcertReplicationStream>*, FGetClientStreams);`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Private/Replication/Processing/ClientReplicationDataQueuer.h` (Private)


#### class `UE::ConcertSyncClient::Replication::FClientReplicationDataQueuer`  
`class FClientReplicationDataQueuer : public ConcertSyncCore::FReplicationDataQueuer`  
_L13-31_
- inherits: `ConcertSyncCore::FReplicationDataQueuer`
- desc: Queues events received from the server.
- L19 _public prototype_ `static TSharedRef<FClientReplicationDataQueuer> Make(IConcertClientReplicationBridge& ReplicationBridge UE_LIFETIMEBOUND, ConcertSyncCore::FObjectReplicationCache& InReplicationCache UE_LIFETIMEBOUND);`
- L22 _public prototype_ `virtual bool WantsToAcceptObject(const FConcertReplicatedObjectId& Object) const override;`
- L27 _private prototype_ `FClientReplicationDataQueuer(IConcertClientReplicationBridge& ReplicationBridge UE_LIFETIMEBOUND);`
- L30 _private member_ `IConcertClientReplicationBridge& ReplicationBridge;` — Used to determine whether the object is currently alive.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ConcertSyncClient` (scope `UE`)
- L10 _namespace_ `namespace Replication` (scope `UE::ConcertSyncClient`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Private/Replication/Processing/ObjectInfo.h` (Private)


#### struct `UE::ConcertSyncClient::FObjectInfo`  
`struct FObjectInfo`  
_L11-20_
- L14 _public member_ `FGuid StreamId;` — The replication stream producing this object's data
- L16 _public member_ `FConcertPropertySelection SelectedProperties;` — The properties to replicate
- L19 _public member_ `ConcertSyncCore::FSequenceId ReplicationSequenceId = 0;` — Incremented every time replication data is sent out. Used for performance tracing.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ConcertSyncClient` (scope `UE`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Private/Replication/Processing/ObjectReplicationApplierProcessor.h` (Private)


#### class `UE::ConcertSyncClient::Replication::FObjectReplicationApplierProcessor`  
`class FObjectReplicationApplierProcessor : public ConcertSyncCore::FObjectReplicationProcessor`  
_L14-37_
- inherits: `ConcertSyncCore::FObjectReplicationProcessor`
- desc: Applies replication data to the object is is meant for.
- L18 _public prototype_ `explicit FObjectReplicationApplierProcessor( IConcertClientReplicationBridge& ReplicationBridge UE_LIFETIMEBOUND, ConcertSyncCore::IObjectReplicationFormat& ReplicationFormat UE_LIFETIMEBOUND, ConcertSyncCore::IReplicationDataSource& DataSource UE_LIFETIMEBOUND );`
- L27 _protected prototype_ `virtual void ProcessObject(const FObjectProcessArgs& Args) override;`
- L33 _private member_ `IConcertClientReplicationBridge& ReplicationBridge;` — Retrieves objects for applying replication data to.
- L36 _private member_ `ConcertSyncCore::IObjectReplicationFormat& ReplicationFormat;` — Unpacks replication data and applies it to an UObject instance.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertSyncClient` (scope `UE`)
- L11 _namespace_ `namespace Replication` (scope `UE::ConcertSyncClient`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Private/Sandbox/ConcertPackageReloadHandler.h` (Private)


#### class `UE::ConcertSyncClient::FConcertPackageReloadHandler`  
`class FConcertPackageReloadHandler : public FileSandboxCore::FDefaultPackageReloadHandler`  
_L16-69_
- inherits: `FileSandboxCore::FDefaultPackageReloadHandler`
- desc: Enqueues packages for hot-reload and purge when the sandbox is being shutdown.
- L18 _private typedef_ `using Super = FDefaultPackageReloadHandler;`
- L21 _public function_ `explicit FConcertPackageReloadHandler(FConcertClientPackageManager& InPackageManager UE_LIFETIMEBOUND) : PackageManager(InPackageManager)`
- L25 _public function_ `virtual void PurgePackages(const FileSandboxCore::FPurgePackageArgs& InArgs) override`
- L45 _public function_ `virtual void HotReloadPackages(const FileSandboxCore::FHotReloadPackageArgs& InArgs) override`
- L68 _private member_ `FConcertClientPackageManager& PackageManager;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ConcertSyncClient` (scope `UE`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Private/Sandbox/ConcertPackageSandbox.h` (Private)


#### class `UE::ConcertSyncClient::FConcertPackageSandbox`  
`class FConcertPackageSandbox : public FNoncopyable, public IConcertSandbox`  
_L21-43_
- inherits: `FNoncopyable,IConcertSandbox`
- desc: Handles sandboxing changes made to files while in a Concert session.
- L26 _public prototype_ `static TUniquePtr<FConcertPackageSandbox> CreateOrLoad( FConcertClientPackageManager& InPackageManager UE_LIFETIMEBOUND, const TSharedRef<FConcertSyncClientLiveSession>& InLiveSession, const FString& InClientRole );` — Creates a file sandbox.
- L31 _public prototype_ `explicit FConcertPackageSandbox(const TSharedRef<FConcertSandboxLock> InLock);`
- L35 _public prototype_ `virtual FPersistResult PersistSandbox(TArrayView<const FString> InFiles, FPersistParameters InParams) override;`
- L36 _public prototype_ `virtual bool DeletedPackageExistsInNonSandbox(FString InFilename) const override;`
- L42 _private member_ `const TSharedRef<FConcertSandboxLock> Lock;` — Interacts with the sandbox system to prevent sandbox from being left while in Concert session.

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace FileSandboxCore` (scope `UE`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace ConcertSyncClient` (scope `UE`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Private/Sandbox/ConcertSandboxLock.h` (Private)


#### class `UE::ConcertSyncClient::FConcertSandboxLock`  
`class FConcertSandboxLock : public FileSandboxCore::ISandboxLock`  
_L14-36_
- inherits: `FileSandboxCore::ISandboxLock`
- desc: Prevents the sandbox system from leaving the current sandbox for as long as Concert is in a session.
- L18 _public prototype_ `explicit FConcertSandboxLock(const FString& InClientRole);`
- L21 _public prototype_ `void ReleaseLock();` — Lifts the lock. Called when the session stops.
- L24 _public prototype_ `virtual bool CanLeaveSandbox(FText* OutReason) const override;`
- L25 _public prototype_ `virtual bool RequestLiftLock(FText* OutReason) override;`
- L26 _public prototype_ `virtual bool SupportsLiftingLock() const override;`
- L32 _private member_ `const FString ClientRole;` — The client role. Relevant for lock reason generation.
- L35 _private member_ `bool bIsLocked = true;` — Whether the sandbox is currently locked.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ConcertSyncClient` (scope `UE`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Private/Sandbox/IConcertSandbox.h` (Private)


#### class `UE::ConcertSyncClient::IConcertSandbox`  
`class IConcertSandbox`  
_L16-34_
- L28 _public prototype_ `virtual FPersistResult PersistSandbox(TArrayView<const FString> InFiles, FPersistParameters InParams) = 0;` — Persist the file list from the sandbox state onto the real files Will mark files for which the operation was succesful as persisted. @param InFiles	List of files names to persist as full paths. @param InParams	Parameters controlling the persist options specified by the user. @return Returns a persist result object that contains result status.
- L31 _public prototype_ `virtual bool DeletedPackageExistsInNonSandbox(FString InFilename) const = 0;` — @return true if the given package file exists on non sandbox path.
- L33 _public prototype_ `virtual ~IConcertSandbox() = default;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace ConcertSyncClient` (scope `UE`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Public/ConcertActionDefinition.h` (Public)


#### enum `EConcertActionType`  
`enum class EConcertActionType : uint8`  
_L11-20_
- desc: Defines the possible type of actions this module can provide. The type of action can be used to map a button type/color by the UI.
- L13 _public enumerator_ `Normal`
- L14 _public enumerator_ `Primary`
- L15 _public enumerator_ `Info`
- L16 _public enumerator_ `Success`
- L17 _public enumerator_ `Warning`
- L18 _public enumerator_ `Danger`
- L19 _public enumerator_ `NUM`

#### struct `FConcertActionDefinition`  
`struct FConcertActionDefinition`  
_L26-36_
- desc: Defines actions for a given context. The actions are usually bound to UI buttons. This allows the module to expose contextual functionalities without exposing some private part of the API.
- L28 _public function_ `FConcertActionDefinition() : IsVisible(true), IsEnabled(true)`
- L29 _public member_ `EConcertActionType Type = EConcertActionType::Normal;`
- L30 _public member_ `TAttribute<bool> IsVisible;` — If the action should be displayed or not.
- L31 _public member_ `TAttribute<bool> IsEnabled;` — If the action is enabled or not.
- L32 _public member_ `TAttribute<FText> Text;` — The action name. Usually correspond to a button caption in UI.
- L33 _public member_ `TAttribute<FText> ToolTipText;` — The action tooltip. Usually correspond to a button tooltip.
- L34 _public member_ `FOnExecuteAction OnExecute;` — The function to call to execute the action.
- L35 _public member_ `TAttribute<FName> IconStyle;` — The icon brush style name (if set, it replaces the text).

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_DELEGATE(FOnExecuteAction);`
- L8 _prototype_ `DECLARE_DELEGATE(FOnExecuteAction);`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Public/ConcertActivityStream.h` (Public)


#### class `FConcertActivityStream`  
`class FConcertActivityStream`  
_L17-66_
- desc: Streams an archived session activities asynchronously and caches them until the client poll and consume them synchronously. The streams also caches the corresponding client info for lookup.
- L29 _public prototype_ `FConcertActivityStream(TWeakPtr<IConcertClient, ESPMode::ThreadSafe> InConcertClient, const FGuid& InAdminEndpointId, const FGuid& InSessionId, bool bInIncludeActivityDetails, uint32 InBufferSize = 1024);` — Construct a input activity stream used to read a Concert session activities from the most recent to the oldest. @param InConcertClient The client used to request the session to the server. @param InAdminEndpointId The server hosting the session from which the activities should be streamed. @param InSessionId The session ID from which the activity should be streamed. @param bInIncludeActivityDetails Includes extra information to inspect the activity. If true, the FConcertClientSessionActivity::EventPayload field will be set for transaction and package activity. @param InBufferSize The stream buffer cache size. The stream will fill its buffer and stop pulling them from the server until some activities are consumed. @see FConcertClientSessionActivity
- L40 _public prototype_ `bool Read(TArray<TSharedPtr<FConcertSessionActivity>>& InOutActivities, int32& OutReadCount, FText& OutErrorMsg);` — Reads all buffered activities. Call this function periodically (between frames, not in a tight loop). Every times this function is called, all buffered activities are consumed (appended to InOutActivities buffer) and a new request is fired to refill the internal buffer. The activities are streamed from the most recent to the oldest. @param InOutActivities The array to which the activities should be appended. @param OutReadCount The number of activities consumed and appended to InOutActivities. Can be 0 if consumed faster than received form the server. @param OutErrorMsg Contains the last error message, if any or an empty text. @return True if all activities were consumed, false otherwise.
- L43 _public function_ `const FConcertClientInfo* GetActivityClientInfo(const FGuid& ActivityEndpointId) const` — Returns the client info corresponding to an activities. The stream maintains this state as an optimization.
- L47 _private prototype_ `void Fetch(int64 ActivityCount);` — Run asynchronous requests in background and caches the activities until consumed.
- L50 _private function_ `constexpr int64 GetRequestBatchSize()` — Returns how many activities should be requested per request.
- L53 _private member_ `TWeakPtr<IConcertClient, ESPMode::ThreadSafe> WeakConcertClient;`
- L54 _private member_ `FGuid AdminEndpointId;`
- L55 _private member_ `FGuid SessionId;`
- L56 _private member_ `int64 LowestFetchedActivityId = 0;` — The next Activity ID to fetch. Activity IDs are 1-based.
- L57 _private member_ `int64 TotalActivityCount = 0;`
- L58 _private member_ `TArray<TSharedPtr<FConcertSessionActivity>> AvailableActivities;` — Activities currently cached and ready for consumption.
- L59 _private member_ `TMap<FGuid, FConcertClientInfo> EndpointClientInfoMap;`
- L60 _private member_ `TSharedPtr<uint8, ESPMode::ThreadSafe> FetchRequestContinuationToken;` — Used to disarm TFuture continuation.
- L61 _private member_ `FText LastErrorMsg;`
- L62 _private member_ `uint32 BufferSize;`
- L63 _private member_ `bool bAllActivitiesFetched = false;`
- L64 _private member_ `bool bFetching = false;`
- L65 _private member_ `bool bIncludeActivityDetails = false;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CONCERTSYNCCLIENT_API`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Public/ConcertClientDesktopPresenceActor.h` (Public)


#### class `AConcertClientDesktopPresenceActor`  
`class AConcertClientDesktopPresenceActor : public AConcertClientPresenceActor`  
_L20-82_
- reflection: `UCLASS(Abstract, Transient, NotPlaceable, Blueprintable)`
- inherits: `AConcertClientPresenceActor`
- desc: A AConcertClientDesktopPresenceActor is a child of AConcertClientPresenceActor that is used to represent users in desktop
- L26 _public prototype_ `virtual void BeginDestroy() override;` — UObject interface
- L29 _public prototype_ `virtual void SetPresenceColor(const FLinearColor& InColor) override;` — Set color of presence mesh
- L32 _public prototype_ `virtual void InitPresence(const class UConcertAssetContainer& InAssetContainer, FName DeviceType) override;` — AConcertClientPresenceActor Interface
- L35 _public prototype_ `virtual void HandleEvent(const FStructOnScope& InEvent) override;` — Handle presence update events
- L37 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L39 _public prototype_ `void HideLaser();`
- L40 _public prototype_ `void ShowLaser();`
- L44 _private prototype_ `void SetLaserTimer(FTimerManager& InTimerManager, bool bLaserShouldShow);`
- L48 _private member_ `TObjectPtr<UStaticMeshComponent> DesktopMeshComponent;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Rendering", meta = (AllowPrivateAccess = "true"))` — The camera mesh component to show visually where the camera is placed
- L52 _private member_ `TObjectPtr<USplineMeshComponent> LaserPointer;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Rendering", meta = (AllowPrivateAccess = "true"))` — Spline mesh representing laser
- L56 _private member_ `TObjectPtr<UMaterialInstanceDynamic> LaserMid;` — `UPROPERTY()` — Dynamic material for the laser
- L60 _private member_ `TObjectPtr<UMaterialInstanceDynamic> LaserCoreMid;` — `UPROPERTY()` — Dynamic material for the laser
- L63 _private member_ `bool bMovingCamera;` — `UPROPERTY()`
- L66 _private member_ `FVector LastEndPoint;` — `UPROPERTY()`
- L69 _private member_ `bool bIsLaserVisible;` — `UPROPERTY()`
- L72 _private member_ `FTimerHandle LaserTimerHandle;` — Handle for efficient management of laser timer
- L75 _private member_ `bool bLastKnownMovingCamera;` — Most recently received value of bMovingCamera
- L78 _private member_ `TOptional<FConcertClientMovement> LaserStartMovement;` — Movement smoothing for laser start
- L81 _private member_ `TOptional<FConcertClientMovement> LaserEndMovement;` — Movement smoothing for laser start

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Public/ConcertClientLocalDataStore.h` (Public)


#### class `FConcertClientLocalDataStore`  
`class FConcertClientLocalDataStore`  
_L36-154_
- desc: Maintains a type-safe key/value local map where the values are USTRUCT() struct or a supported basic types (int8, uint8, int16, uint16, int32, uint32, int64, uint64, float, double, bool, FName, FText, FString). This class is meant to be used as a local/private client store where the IConcertClientDataStore interface is meant to be used in a client(s)/server scenario. <b>Usage example</b> @code FConcertClientLocalDataStore MyStore; FName MyKey(TEXT("MyKey1")); uint64 MyValue = 100ull; if (auto Stored = MyStore.FetchOrAdd(MyKey, MyValue)) { if (Stored = MyStore.Store(MyKey, Stored.GetValue() + 10)) { check(MyStore.FetchAs<uint64>(MyKey).GetValue() == MyValue + 10); if (Stored = MyStore.CompareExchange(MyKey, MyValue + 10, MyValue + 20)) { check(MyStore.FetchAs<uint64>(MyKey).GetValue() == MyValue + 20); } } } check(MyStore.FetchAs<uint64>(MyKey).GetValue() == MyValue + 20); @endcode
- L40 _public prototype_ `FConcertClientLocalDataStore();` — Constructs the data store map.
- L58 _public function_ `template<typename T> TConcertDataStoreResult<T> FetchOrAdd(const FName& Key, const T& InitialValue)` — Searches the store for the specified key, if not found, adds a new key/value pair, otherwise, if the stored value type matches the initial value type, fetches the stored value. The function accepts a USTRUCT() type or a supported basic type directly. To store complex types such as TArray<> TMap<> or TSet<>, wrap the type in a USTRUCT(). @tparam T Any USTRUCT() struct or a supported basic types (int8, uint8, int16, uint16, int32, uint32, int64, uint64, float, double, bool, FName, FText, FString). @param Key The value name to fetch or add. @param InitialValue The value to store if the key doesn't already exist. @return The operation result. The possible result codes are: - EConcertDataStoreResultCode::Added if the key/value was added. The result holds a pointer on the newly added value. - EConcertDataStoreResultCode::Fetched if the key was already taken and type matched. The result holds a pointer on the fetched value. - EConcertDataStoreResultCode::TypeMismatch if the key was already taken but the types did not match. The result holds a null pointer. @see [The class documentation for an example.](@ref FConcertClientLocalDataStore)
- L83 _public function_ `template<typename T> TConcertDataStoreResult<T> FetchAs(const FName& Key) const` — Looks up the specified key, if found and type matches, fetches the corresponding value. If the key is not found or the requested type doesn't match the stored type, the operation fails. @tparam T Any USTRUCT() struct or a supported basic types (int8, uint8, int16, uint16, int32, uint32, int64, uint64, float, double, bool, FName, FText, FString). @param Key The value name to lookup. @return The operation result. The possible result codes are: - EConcertDataStoreResultCode::Fetched if the key value was retrieved. The result holds a pointer on the fetched value. - EConcertDataStoreResultCode::NotFound if the key could not be found. The result holds a null pointer. - EConcertDataStoreResultCode::TypeMismatch if the key was found, but the requested type did not match the stored type. The result holds a null pointer. @see [The class documentation for an example.](@ref FConcertClientLocalDataStore)
- L103 _public function_ `template<typename T> TConcertDataStoreResult<T> Store(const FName& Key, const T& Value)` — Looks up the specified key, if it doesn't exist yet, adds new key/value pair at version 1, else if the stored value type matched the specified value type, overwrites the value and increment its version by one, otherwise, the operation fails. @tparam T Any USTRUCT() struct or a supported basic types (int8, uint8, int16, uint16, int32, uint32, int64, uint64, float, double, bool, FName, FText, FString). @param Key The value name to store. @param Value The value to store. @return The operation result. The possible result codes are: - EConcertDataStoreResultCode::Added if the key/value was added. The result holds a pointer on the newly added value. - EConcertDataStoreResultCode::Exchanged if the existing key value was updated. The result holds a pointer on the latest stored value. - EConcertDataStoreResultCode::TypeMismatch if the key was already taken but the value types did not match. The result holds a null pointer. @see [The class documentation for an example.](@ref FConcertClientLocalDataStore)
- L127 _public function_ `template<typename T> TConcertDataStoreResult<T> CompareExchange(const FName& Key, const T& Expected, const T& Desired)` — Exchanges the stored value to \a Desired if a stored value corresponding to \a Key exists, has the same type and its value is equal to \a Expected, otherwise, the operation fails. @tparam T Any USTRUCT() struct or a supported basic types (int8, uint8, int16, uint16, int32, uint32, int64, uint64, float, double, bool, FName, FText, FString). @param Key The value name. @param Expected The value the caller expects to be stored. @param Desired The value the caller wants to store. @return The operation result. The possible result codes are: - EConcertDataStoreResultCode::Exchanged if the desired value was sucessfully exchanged and stored. The result holds a pointer on the newly stored value. - EConcertDataStoreResultCode::Fetched if the stored value was not the expected one. The stored value was fetched instead. The result holds a pointer on the fetched value. - EConcertDataStoreResultCode::NotFound if the key could not be found. The result holds a null pointer. - EConcertDataStoreResultCode::TypeMismatch if the stored data type did not match the expected/desired type. The result holds a null pointer. @see [The class documentation for an example.](@ref FConcertClientLocalDataStore)
- L149 _private prototype_ `FConcertDataStoreResult InternalFetch(const FName& Key, const FName& TypeName) const;` — Wraps calls to FConcertDataStore to avoid leaking the type publicly.
- L150 _private prototype_ `FConcertDataStoreResult InternalStore(const FName& Key, const FName& TypeName, const FConcertSessionSerializedPayload& Value);`
- L153 _private member_ `TUniquePtr<FConcertDataStore> DataStore;` — Maps keyName/keyValue.

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Public/ConcertClientMovement.h` (Public)


#### class `FConcertClientMovement`  
`class FConcertClientMovement`  
_L7-63_
- L12 _public prototype_ `FConcertClientMovement(double InUpdateFrequencyTimeSeconds, double InCurrentTimestamp, const FVector& InPosition);` — Constructor
- L15 _public prototype_ `FConcertClientMovement(double InUpdateFrequencyTimeSeconds, double InCurrentTimestamp, const FVector& InPosition, const FQuat& InOrientation);` — Constructor
- L18 _public prototype_ `~FConcertClientMovement();` — Destructor
- L27 _public prototype_ `void MoveSmooth(double InDeltaTimeSeconds, FVector& OutPosition, FQuat* OutOrientation = nullptr);` — Move smoothly over time based on previous and last known positions. @param InDeltaTimeSeconds:	Time passed since previous call to MoveSmooth. @param OutPosition:			New position after moving @param OutOrientation:		New orientation after moving
- L30 _public prototype_ `void UpdateLastKnownLocation(double InUpdateTimestampSeconds, const FVector& InPosition, const FQuat* InOrientation = nullptr);` — Update last known location.
- L35 _private member_ `FVector PreviousPosition;` — Previous actual position.
- L38 _private member_ `FQuat PreviousOrientation;` — Previous actual orientation.
- L41 _private member_ `FVector LastKnownPosition;` — Last known position
- L44 _private member_ `FQuat LastKnownOrientation;` — Last known orientation
- L47 _private member_ `FVector CurrentPosition;` — Most recent position computed by MoveSmooth
- L50 _private member_ `FQuat CurrentOrientation;` — Most recent orientation computed by MoveSmooth
- L53 _private member_ `double TimeSecondsSinceLastKnownUpdate;` — Delta since last known location was updated
- L56 _private member_ `double LastKnownUpdateTimestampSeconds;` — Time stamp of last known location update
- L59 _private member_ `double UpdateFrequencyTimeSeconds;` — How frequently last known position is updated
- L62 _private member_ `bool bHasOrientation;` — Has orientation

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Public/ConcertClientObjectFactory.h` (Public)


#### class `UConcertClientObjectFactory`  
`class UConcertClientObjectFactory : public UObject`  
_L15-90_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- desc: Factory API that can be implemented to extend the set of objects that Concert understands how to create/destroy. @note This API is const as it operates on CDOs, which also means that a factory implementation cannot store any additional state.
- L21 _public prototype_ `virtual void PostInitProperties() override;`
- L22 _public prototype_ `virtual void BeginDestroy() override;`
- L28 _public prototype_ `static const UConcertClientObjectFactory* FindFactoryForClass(const UClass* Class);` — Attempt to find a factory that supports the given class. @note If multiple factories support the given class then the result isn't guaranteed to be deterministic.
- L33 _public function_ `virtual bool SupportsClass(const UClass* Class) const` — Does this factory support creating/destroying objects of the given class?
- L42 _public function_ `virtual bool CreateOuter(UObject*& OutOuter, const FString& OuterPathName) const` — Attempt to create a new outer from the given arguments, and fill in OutOuter. @return True if this function handled the creation attempt (this doesn't mean that OutOuter isn't null!).
- L51 _public function_ `virtual bool CreateObject(UObject*& OutObject, UObject* Outer, const UClass* Class, const FName Name, const EObjectFlags Flags) const` — Attempt to create a new object from the given arguments, and fill in OutObject. @return True if this function handled the creation attempt (this doesn't mean that OutObject isn't null!), or false if we should fallback to using NewObject.
- L60 _public function_ `virtual bool DuplicateObject(UObject*& OutObject, const UObject* SourceObject, UObject* Outer, const UClass* Class, const FName Name, const EObjectFlags Flags) const` — Attempt to create a new object from the given source object, and fill in OutObject. @return True if this function handled the creation attempt (this doesn't mean that OutObject isn't null!), or false if we should fallback to using StaticDuplicateObject.
- L69 _public function_ `virtual bool ShouldInitializeObjectsBefore(const UConcertClientObjectFactory* OtherFactory) const` — Should this factory run InitializeObjects before OtherFactory? @return True if this factory needs to run its InitializeObjects before OtherFactory (to control initialization order between factories), or false if it doesn't matter which order they run.
- L78 _public function_ `virtual void InitializeObjects(TArrayView<UObject* const> Objects) const` — Perform any additional initialization on the given objects. @note This is called after CreateObject/DuplicateObject has been called for every object in the transaction, and can be used for delayed initialization of interdependent objects.
- L86 _public function_ `virtual bool DestroyObject(UObject* Object) const` — Attempt to destroy the given object. @return True if this function handled the destruction attempt, or false if we should fallback to using MarkAsGarbage.

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Public/ConcertClientPersistData.h` (Public)


#### struct `FPersistParameters`  
`struct FPersistParameters`  
_L12-19_
- desc: Input parameters for persistance of an existing session.
- L15 _public member_ `TArrayView<const FName> PackagesToPersist;` — Name of the packages to persist.
- L18 _public member_ `bool bShouldMakeWritableIfNoSourceControl = false;` — Boolean to control if we will force the file writable when no source control provider is active.

#### enum `EPersistStatus`  
`enum class EPersistStatus`  
_L22-30_
- desc: Possible outcomes from a session persist.
- L25 _public enumerator_ `Success` — The packages were persisted correctly.
- L27 _public enumerator_ `Failure` — We failed to persist the packages.
- L29 _public enumerator_ `NotAllowed` — We are not allowed to persist.

#### struct `FPersistResult`  
`struct FPersistResult`  
_L33-40_
- desc: Result of a persist.
- L36 _public member_ `TArray<FText> FailureReasons;` — List of reasons for persist failure.
- L39 _public member_ `EPersistStatus PersistStatus = EPersistStatus::NotAllowed;` — Success or failure of the session persist.

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Public/ConcertClientPresenceActor.h` (Public)


#### class `AConcertClientPresenceActor`  
`class AConcertClientPresenceActor : public AActor`  
_L22-103_
- reflection: `UCLASS(Abstract, Transient, NotPlaceable, Blueprintable)`
- inherits: `AActor`
- desc: A ConcertClientPresenceActor is a transient actor representing other client presences during a concert client session.
- L27 _public prototype_ `AConcertClientPresenceActor(const FObjectInitializer& ObjectInitializer);`
- L30 _public prototype_ `virtual bool IsEditorOnly() const override final;` — AActor interface
- L33 _public function_ `virtual bool IsSelectable() const override final`
- L38 _public function_ `virtual bool IsListedInSceneOutliner() const override final`
- L49 _public prototype_ `virtual void SetPresenceName(const FString& InName);` — Set the presence name. Called by the presence manager to set the display name of the client on the actor. @param InName the display name of the client represented by this actor.
- L56 _public prototype_ `virtual void SetPresenceColor(const FLinearColor& InColor);` — Set the presence color. Called by the presence manager to set the color of the client on the actor. @param InColor the color of the client represented by this actor.
- L62 _public prototype_ `virtual void HandleEvent(const FStructOnScope& InEvent);` — Handle presence event received from the session for this actor @param InEvent a concert presence event
- L70 _public prototype_ `virtual void InitPresence(const class UConcertAssetContainer& InAssetContainer, FName DeviceType);` — Initialize the presence actor from a set of assets representing HMD, controllers and desktops @param InAssetContainer the asset container for controller, HMD and laser meshes @param DeviceType The device type this actor is representing.
- L72 _public prototype_ `virtual bool ShouldTickIfViewportsOnly() const override;`
- L74 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L79 _protected member_ `FName PresenceDeviceType;` — `UPROPERTY(BlueprintReadOnly, Category = "Rendering", meta = (AllowPrivateAccess = "true"))` — The device type that this presence represent (i.e Oculus, Vive, Desktop)
- L83 _protected member_ `TObjectPtr<UStaticMeshComponent> PresenceMeshComponent;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Rendering", meta = (AllowPrivateAccess = "true"))` — The camera mesh component to show visually where the camera is placed
- L87 _protected member_ `TObjectPtr<UTextRenderComponent> PresenceTextComponent;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Rendering", meta = (AllowPrivateAccess = "true"))` — The text render component to display the associated client's name
- L91 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> PresenceMID;` — `UPROPERTY()` — Dynamic material for the presence actor
- L95 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> TextMID;` — `UPROPERTY()` — Dynamic material for the presence text
- L98 _protected member_ `TOptional<FConcertClientMovement> PresenceMovement;` — Movement object to interpolate presence movement between update events.
- L101 _private prototype_ `void UpdateVisibleInGameState();`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Public/ConcertClientVRPresenceActor.h` (Public)


#### class `AConcertClientVRPresenceActor`  
`class AConcertClientVRPresenceActor : public AConcertClientPresenceActor`  
_L19-112_
- reflection: `UCLASS(Abstract, Transient, NotPlaceable, Blueprintable)`
- inherits: `AConcertClientPresenceActor`
- desc: A ConcertClientVRPresenceActor is a child of AConcertClientPresenceActor that is used to represent users in VR
- L24 _public prototype_ `virtual void HandleEvent(const FStructOnScope& InEvent) override;`
- L26 _public prototype_ `virtual void InitPresence(const class UConcertAssetContainer& InAssetContainer, FName DeviceType) override;`
- L28 _public prototype_ `virtual void SetPresenceColor(const FLinearColor& InColor) override;`
- L30 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L34 _public member_ `TObjectPtr<UStaticMeshComponent> LeftControllerMeshComponent;` — `UPROPERTY()` — The left controller mesh
- L38 _public member_ `TObjectPtr<UStaticMeshComponent> RightControllerMeshComponent;` — `UPROPERTY()` — The right controller mesh
- L42 _public member_ `TObjectPtr<UMaterialInstanceDynamic> LaserMid;` — `UPROPERTY()` — Dynamic material for the laser
- L46 _public member_ `TObjectPtr<UMaterialInstanceDynamic> LaserCoreMid;` — `UPROPERTY()` — Dynamic material for the laser
- L49 _public member_ `float LaserThickness = 0.5f;` — `UPROPERTY(BlueprintReadWrite, Category="Laser")`
- L53 _private prototype_ `void UpdateSplineLaser(class USplineComponent* LaserSplineComponent, const TArray<class USplineMeshComponent*>& LaserSplineMeshComponents, const FVector& InStartLocation, const FVector& InEndLocation);` — Updates all the segments of the curved laser
- L55 _private prototype_ `void HideLeftController();`
- L56 _private prototype_ `void ShowLeftController();`
- L58 _private prototype_ `void HideRightController();`
- L59 _private prototype_ `void ShowRightController();`
- L61 _private prototype_ `void HideLeftLaser();`
- L62 _private prototype_ `void ShowLeftLaser();`
- L64 _private prototype_ `void HideRightLaser();`
- L65 _private prototype_ `void ShowRightLaser();`
- L69 _private member_ `TObjectPtr<USplineComponent> LeftLaserSplineComponent;` — `UPROPERTY()` — Spline for the left laser pointer, if any
- L73 _private member_ `TArray<TObjectPtr<USplineMeshComponent>> LeftLaserSplineMeshComponents;` — `UPROPERTY()` — Spline meshes for the left curved laser, if any
- L77 _private member_ `TObjectPtr<USplineComponent> RightLaserSplineComponent;` — `UPROPERTY()` — Spline for the right laser pointer, if any
- L81 _private member_ `TArray<TObjectPtr<USplineMeshComponent>> RightLaserSplineMeshComponents;` — `UPROPERTY()` — Spline meshes for the right curved laser, if any
- L84 _private member_ `bool bIsLeftControllerVisible;` — `UPROPERTY()`
- L87 _private member_ `bool bIsRightControllerVisible;` — `UPROPERTY()`
- L90 _private member_ `bool bIsLeftLaserVisible;` — `UPROPERTY()`
- L93 _private member_ `bool bIsRightLaserVisible;` — `UPROPERTY()`
- L96 _private member_ `TOptional<FConcertClientMovement> LeftControllerMovement;` — Movement smoothing for left controller
- L99 _private member_ `TOptional<FConcertClientMovement> RightControllerMovement;` — Movement smoothing for right controller
- L102 _private member_ `TOptional<FConcertClientMovement> LeftLaserStartMovement;` — Movement smoothing for lasers start
- L105 _private member_ `TOptional<FConcertClientMovement> LeftLaserEndMovement;` — Movement smoothing for laser end
- L108 _private member_ `TOptional<FConcertClientMovement> RightLaserStartMovement;` — Movement smoothing for lasers start
- L111 _private member_ `TOptional<FConcertClientMovement> RightLaserEndMovement;` — Movement smoothing for laser end

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Public/IConcertClientDataStore.h` (Public)


#### enum `EConcertDataStoreChangeNotificationOptions`  
`enum class EConcertDataStoreChangeNotificationOptions : uint8`  
_L10-20_
- desc: The options flags used to register a key/value handler.
- L13 _public enumerator_ `None = 0` — No special options.
- L16 _public enumerator_ `NotifyOnInitialValue = 1 << 0` — If the key value already exists, immediately call the handler. This is recommended to avoid calling the Fetch/Register operations in the wrong order.
- L19 _public enumerator_ `NotifyOnTypeMismatch = 1 << 1` — If the register handler declares a value type that doesn't match the stored value type, still call the observer, but the reported value (TOptional<>) will not be set.

#### class `IConcertClientDataStore`  
`class IConcertClientDataStore`  
_L127-316_
- desc: Interacts with a key/value store shared by one or more clients connected to a Concert session. The store is like a TMap<FName, Blob>. The implementation requires the 'Blob' to be defined as a USTRUCT() structure, which provides the serialization mechanism. The system automatically wraps primitive types like integers, floating, bool and strings into USTRUCT() for you. If you need to store container types like TArray<>, TMap<> or TSet<> or custom types, you will need to put them into a USTRUCT() struct similare to the example below showing how to use custom types. The store is type safe, in the sense that a client cannot transmute the type of a stored value into another type. For example if the value "foo" is an integer, it cannot be transformed into a double later one. The store is used to share variables with other clients. For example, it can be used for to manage a distributed counter like "cameraId" to uniquely number cameras created concurrently by multiple users while editing a level. The store API returns TFuture to implement asynchronous or blocking operations. While is far more easier to use the blocking operations model, i.e. waiting on future to gets its result (TFuture::Get()) in the caller thread, it is recommended to use the asynchronous API and use continuations. Since the store implies network operation, expect latency and avoid waiting the response in a thread like the game thread. To implement a sequence of operations using the store asynchronously inside a s
- L131 _public prototype_ `virtual ~IConcertClientDataStore() = default;` — Destructor.
- L149 _public function_ `template<typename T> TFuture<TConcertDataStoreResult<T>> FetchOrAdd(const FName& Key, const T& InitialValue)` — Searches the store for the specified key, if not found, adds a new key/value pair, otherwise, if the stored value type matches the initial value type, fetches the stored value. The function accepts a USTRUCT() type or a supported basic type directly. To store complex types such as TArray<> TMap<> or TSet<>, wrap the type(s) in a USTRUCT(). @tparam T Any USTRUCT() struct or a supported basic types (int8, uint8, int16, uint16, int32, uint32, int64, uint64, float, double, bool, FName, FText, FString). @param Key The value name to fetch or add. @param InitialValue The property value to store if the key doesn't already exist. @return Whether or not the key/value pair was added, fetched or the operation failed. The result code can be: - EConcertDataStoreResultCode::Added if the key/value was inserted. - EConcertDataStoreResultCode::Fetched if the key was already taken and type matched. - EConcertDataStoreResultCode::TypeMismatch if the key was already taken but the value types did not match. @see TConcertDataStoreResult<T>::GetValue()
- L172 _public function_ `template<typename T> TFuture<TConcertDataStoreResult<T>> FetchAs(const FName& Key) const` — Looks up the specified key, if found and types match, fetches the corresponding value. If the key is not found or the requested types doesn't match the stored type, the operation fails. @tparam T Any USTRUCT() struct or a supported basic types (int8, uint8, int16, uint16, int32, uint32, int64, uint64, float, double, bool, FName, FText, FString). @param Key The value name to lookup. @return The operation result, as a future. The result code can be: - EConcertDataStoreResultCode::Fetched if the key value was retrieved. - EConcertDataStoreResultCode::NotFound if the key could not be found. - EConcertDataStoreResultCode::TypeMismatch if the key was found, but the requested type did not match the stored type. @see TConcertDataStoreResult<T>::GetValue()
- L196 _public function_ `template<typename T> TFuture<TConcertDataStoreResult<T>> CompareExchange(const FName& Key, const T& Expected, const T& Desired)` — Exchanges the stored value to \a Desired if a stored value corresponding to \a Key exists, has the same type and its value is equal to \a Expected, otherwise, the operation fails. @tparam T Any USTRUCT() struct or a supported basic types (int8, uint8, int16, uint16, int32, uint32, int64, uint64, float, double, bool, FName, FText, FString). @param Key The value name. @param Expected The value the caller expects to be stored. @param Desired The value the caller wants to store. @return Whether or not the key value was exchanged, as a future. The result code can be: - EConcertDataStoreResultCode::Exchanged if the desired value was sucessfully exchanged and stored. - EConcertDataStoreResultCode::Fetched if the stored value was not the expected one. The stored value was fetched instead. - EConcertDataStoreResultCode::NotFound if the key could not be found. - EConcertDataStoreResultCode::TypeMismatch if the stored data type did not match the expected/desired type. @see TConcertDataStoreResult<T>::GetValue()
- L220 _public function_ `template<typename T> void RegisterChangeNotificationHandler(const FName& InKey, const TFunction<void(const FName&, TOptional<T>)>& Handler, EConcertDataStoreChangeNotificationOptions Options = EConcertDataStoreChangeNotificationOptions::NotifyOnInitialValue | EConcertDataStoreChangeNotificationOptions::NotifyOnTypeMismatch)` — Registers(or replaces) a handler invoked every time another client successfully adds or updates the specified key. The server pushes a notification for the added/updated key to all clients except the one that performed the change. By default, the data store immediately calls back the client if the key value is known. This is recommended to prevent calling FetchAs() and RegisterChangeNotificationHandler() in a non-safe order where a key/value could be missed if it appears between a failed fetch and the successful registration of a handler. By default, the handler will be called even if the key type expected by the client doesn't match the stored type. In such case, the handler optional value is not set. @param InKey The key to observe. @param Handler The function to call back with the latest value. See the EChangeNotificationOptions flags. @param Options A set of EChangeNotificationOptions flags.
- L245 _public function_ `void UnregisterChangeNotificationHander(const FName& Key)` — Unregisters the function callback corresponding to the specified key (if any) to stop receiving the key change notifications. @param Key The key for which the handler should be removed.
- L252 _protected typedef_ `typedef TFunction<void(const FName&, const FConcertDataStore_StoreValue*)> FChangeNotificationHandler;` — The function called back when the data store is updated by another client.
- L262 _protected prototype_ `virtual TFuture<FConcertDataStoreResult> InternalFetchOrAdd(const FName& Key, const UScriptStruct* Type, const FName& TypeName, const void* Payload) = 0;` — Fetches or adds a key/value in the store. @param Key The value name. @param Type The value type. @param TypeName The value type name as returned by TConcertDataStoreType<T>::GetFName(). @param Payload The USTRUCT structure pointer. @see IConcertClientDataStore::FetchOrAdd()
- L271 _protected prototype_ `virtual TFuture<FConcertDataStoreResult> InternalFetchAs(const FName& Key,const UScriptStruct* Type, const FName& TypeName) const = 0;` — Fetches a key value from the store. @param Key The value name. @param Type The value type to read. @param TypeName The value type name as returned by TConcertDataStoreType<T>::GetFName(). @see IConcertClientDataStore::FetchAs()
- L282 _protected prototype_ `virtual TFuture<FConcertDataStoreResult> InternalCompareExchange(const FName& Key, const UScriptStruct* Type, const FName& TypeName, const void* Expected, const void* Desired) = 0;` — Compares and exchanges a key value from the store. @param Key The value name. @param Type The value type. @param TypeName The value type name as returned by TConcertDataStoreType<T>::GetFName(). @param Expected The USTRUCT structure pointer containing the expected value. @param Desired The USTRUCT structure pointer containing the desired value. @see IConcertClientDataStore::CompareExchange()
- L292 _protected prototype_ `virtual void InternalRegisterChangeNotificationHandler(const FName& Key, const FName& TypeName, const FChangeNotificationHandler& Handler, EConcertDataStoreChangeNotificationOptions Options) = 0;` — Registers a delegate invoked when the specified key is added or modified. @param Key The name of the value to observe. @param TypeName The value type name as returned by TConcertDataStoreType<T>::GetFName(). @param Handler The delegate function invoked when the specified key is added or modified. @param Options A set of options controlling if handler should be called or not in special situation. @see IConcertClientDataStore::RegisterChangeNotificationHandler()
- L298 _protected prototype_ `virtual void InternalUnregisterChangeNotificationHandler(const FName& Key) = 0;` — Unregisters the delegate corresponding to the specified key (if any) to stop receiving the key change notifications. @param Key The key for which the handler should be removed.
- L302 _private function_ `template<typename T> TFuture<FConcertDataStoreResult> InternalFetchOrAdd(const FName& Key, const typename TConcertDataStoreType<T>::StructType& InitialValue)`
- L310 _private function_ `template<typename T> TFuture<FConcertDataStoreResult> InternalCompareExchange(const FName& Key, const typename TConcertDataStoreType<T>::StructType& Expected, const typename TConcertDataStoreType<T>::StructType& Desired)`

#### Free symbols / members of external scopes

- L154 _function_ `` (scope `IConcertClientDataStore::FetchOrAdd`)
- L175 _function_ `` (scope `IConcertClientDataStore::FetchAs`)
- L201 _function_ `` (scope `IConcertClientDataStore::CompareExchange`)
- L225 _function_ `` (scope `IConcertClientDataStore::RegisterChangeNotificationHandler`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Public/IConcertClientPackageBridge.h` (Public)


#### enum `EPackageFilterResult`  
`enum class EPackageFilterResult : uint8`  
_L14-19_
- L16 _public enumerator_ `Include`
- L17 _public enumerator_ `Exclude`
- L18 _public enumerator_ `UseDefault`

#### class `IConcertClientPackageBridge`  
`class IConcertClientPackageBridge`  
_L28-91_
- desc: Bridge between the editor package events and Concert. Deals with converting package update events to Concert package data.
- L49 _public prototype_ `virtual ~IConcertClientPackageBridge() = default;`
- L54 _public prototype_ `virtual FOnConcertClientLocalPackageEvent& OnLocalPackageEvent() = 0;` — Called when a local package event happens.
- L59 _public prototype_ `virtual FOnConcertClientLocalPackageDiscarded& OnLocalPackageDiscarded() = 0;` — Called when a local package is discarded.
- L62 _public prototype_ `virtual void RegisterPackageHotReloadHint(FName PackageReloadHintName, FPackageHotReloadHintDelegate FilterHandle) = 0;` — Register a pending package hot reload hint package payloads.
- L65 _public prototype_ `virtual bool CanSkipHotReload(const FConcertPackageInfo& PackageInfo) const = 0;` — Returns true if the package can be skipped for hot reload on client nodes.
- L68 _public prototype_ `virtual void UnregisterPackageHotReloadHint(FName PackageReloadHintName) = 0;` — Unregister package hot reload hint handler.
- L71 _public prototype_ `virtual void RegisterPackageFilter(FName FilterName, FPackageFilterDelegate FilterHandle) = 0;` — Register a package filter to exclude/include certain packagins from the session.
- L74 _public prototype_ `virtual EPackageFilterResult IsPackageFiltered(const FConcertPackageInfo& PackageInfo) const = 0;` — Returns true if the package should be filtered from the local sandbox.
- L77 _public prototype_ `virtual void UnregisterPackageFilter(FName FilterName) = 0;` — Unregister package filter for handling package filtering.
- L84 _protected prototype_ `virtual bool& GetIgnoreLocalSaveRef() = 0;` — Function to access the internal bool controlling whether local saves are currently being tracked. @note Exists to implement FScopedIgnoreLocalSave.
- L90 _protected prototype_ `virtual bool& GetIgnoreLocalDiscardRef() = 0;` — Function to access the internal bool controlling whether local discards are currently being tracked. @note Exists to implement FScopedIgnoreLocalDiscard.

#### struct `IConcertClientPackageBridge::FScopedIgnoreLocalSave`  
`struct FScopedIgnoreLocalSave : private TGuardValue<bool>`  
_L32-38_
- inherits: `TGuardValue<bool>`
- desc: Scoped struct to ignore a local save
- L34 _public function_ `FScopedIgnoreLocalSave(IConcertClientPackageBridge& InPackageBridge) : TGuardValue(InPackageBridge.GetIgnoreLocalSaveRef(), true)`

#### struct `IConcertClientPackageBridge::FScopedIgnoreLocalDiscard`  
`struct FScopedIgnoreLocalDiscard : private TGuardValue<bool>`  
_L41-47_
- inherits: `TGuardValue<bool>`
- desc: Scoped struct to ignore a local discard
- L43 _public function_ `FScopedIgnoreLocalDiscard(IConcertClientPackageBridge& InPackageBridge) : TGuardValue(InPackageBridge.GetIgnoreLocalDiscardRef(), true)`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnConcertClientLocalPackageEvent, const FConcertPackageInfo&, const FString&);`
- L11 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnConcertClientLocalPackageEvent, const FConcertPackageInfo&, const FString&);`
- L12 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnConcertClientLocalPackageDiscarded, UPackage*);`
- L12 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnConcertClientLocalPackageDiscarded, UPackage*);`
- L21 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(EPackageFilterResult, FPackageFilterDelegate, const FConcertPackageInfo&);`
- L21 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(EPackageFilterResult, FPackageFilterDelegate, const FConcertPackageInfo&);`
- L22 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FPackageHotReloadHintDelegate, const FConcertPackageInfo&);`
- L22 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FPackageHotReloadHintDelegate, const FConcertPackageInfo&);`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Public/IConcertClientPresenceManager.h` (Public)


#### class `IConcertClientPresenceManager`  
`class IConcertClientPresenceManager`  
_L11-70_
- L14 _public prototype_ `virtual ~IConcertClientPresenceManager() = default;`
- L21 _public prototype_ `virtual void SetPresenceModeFactory(TSharedRef<IConcertClientPresenceModeFactory> InFactory) = 0;` — Set the presence mode factory The factory creates the presence mode for the manager @param InFactory the factory to use
- L26 _public prototype_ `virtual void SetPresenceEnabled(const bool bIsEnabled = true) = 0;` — Set whether presence is currently enabled and should be shown (unless hidden by other settings)
- L35 _public prototype_ `virtual void SetPresenceVisibility(const FString& InDisplayName, bool bVisibility, bool bPropagateToAll = false) = 0;` — Set presence visibility by name @param InDisplayName The display name of the presences we want to set the visibility on @param bVisibility The visibility flag to set @param bPropagateToAll Propagate the visibility change to other user. @note setting presence by name will persist through connection of client using this display name
- L43 _public prototype_ `virtual void SetPresenceVisibility(const FGuid& EndpointId, bool bVisibility, bool bPropagateToAll = false) = 0;` — Set presence visibility of the specified client endpoint id @param EndpointId the endpoint id of the client we we want to set the visibility on @param bVisibility The visibility flag to set @param bPropagateToAll Propagate the visibility change to other user.
- L50 _public prototype_ `virtual FTransform GetPresenceTransform(const FGuid& EndpointId) const = 0;` — Get the presence actor transform for the specified client endpoint id @param EndpointId the endpoint id of the client we we want to retrieve the presence transform @return the transform of the client or the identity transform if the client wasn't found.
- L56 _public prototype_ `virtual void InitiateJumpToPresence(const FGuid& InEndpointId, const FTransform& InTransformOffet = FTransform::Identity) = 0;` — Jump (teleport) to another presence @param InEndpointId The presence client endpoint id
- L69 _public prototype_ `virtual FString GetPresenceWorldPath(const FGuid& EndpointId, EEditorPlayMode& OutEditorPlayMode) const = 0;` — Returns the path to the UWorld object opened in the editor of the specified client endpoint. The information may be unavailable if the client was disconnected, the information hasn't replicated yet or the code was not compiled as part of the UE Editor. This function always returns the editor context world path, never the PIE/SIE context world path (which contains a UEDPIE_%d_ decoration embedded) even if the user is in PIE or SIE. For example, the PIE/SIE context world path would look like '/Game/UEDPIE_10_FooMap.FooMap' while the editor context world returned by this function looks like '/Game/FooMap.FooMap'. @param[in] EndpointId The endpoint of a client connected to the session (local or remote). @param[out] OutEditorPlayMode Indicates if the client corresponding to the end point is in PIE, SIE or simply editing. @return The path to the world being opened in the specified end point editor or an empty string if the information is not available.

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Public/IConcertClientPresenceMode.h` (Public)


#### class `IConcertClientBasePresenceMode`  
`class IConcertClientBasePresenceMode`  
_L23-53_
- desc: Base class for Multi-User PresenceMode. PresenceMode are used to send avatar-specific presence events and cache avatar-related state for the current client. Adding a new presence avatar type requires the following: 1) Add a presence mode class inherited from IConcertClientBasePresenceMode to send events and cache state, if needed, for the current client. 2) Add a presence actor class to handle events and display the avatar for remote clients.
- L26 _public prototype_ `virtual ~IConcertClientBasePresenceMode() = default;`
- L33 _public prototype_ `virtual void SendEvents(IConcertClientSession& Session) = 0;` — Send events for this presence mode This will be called by the presence manager during tick. @param Session the session to send the mode events on.
- L39 _public prototype_ `virtual FTransform GetTransform() = 0;` — Get the current presence transform @return the presence mode transform
- L46 _public prototype_ `virtual FName GetVRDeviceType() const = 0;` — Get the VR device type represented by this presence mode. NAME_None for desktop or non vr presence mode. @return the vr device type
- L52 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) = 0;` — Collects any reference to UObject the mode may have Called by the presence manager in its own AddReferencedObjects

#### class `IConcertClientPresenceModeFactory`  
`class IConcertClientPresenceModeFactory`  
_L61-86_
- desc: Interface for the presence mode factory The presence manager uses a default implementation but it is possible to change the factory to get different presence mode behavior than the default one. @see IConcertClientPresenceManager
- L64 _public prototype_ `virtual ~IConcertClientPresenceModeFactory() = default;`
- L71 _public prototype_ `virtual bool ShouldResetPresenceMode() const = 0;` — Indicate if the presence mode should be reset for recreation Called by the presence manager on end frame tick. @return true if the current presence mode in the presence manager should be reset
- L79 _public prototype_ `virtual TUniquePtr<IConcertClientBasePresenceMode> CreatePresenceMode() = 0;` — Create a presence mode. Called by the presence manager on end frame tick after resetting the presence mode if `ShouldResetPresenceMode` returned true. @return a unique pointer to a IConcertClientBasePresenceMode presence mode. @see ShouldResetPresenceMode
- L85 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) = 0;` — Collects any reference to UObject the factory may have Called by the presence manager in its own AddReferencedObjects

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Public/IConcertClientSequencerManager.h` (Public)


#### class `IConcertClientSequencerManager`  
`class IConcertClientSequencerManager`  
_L9-97_
- desc: Sequencer manager that is held by the client sync module that keeps track of open sequencer UIs, regardless of whether a session is open or not Events are registered to client sessions that will then operate on any tracked sequencer UIs
- L12 _public prototype_ `virtual ~IConcertClientSequencerManager() = default;`
- L17 _public prototype_ `virtual bool IsSequencerPlaybackSyncEnabled() const = 0;` — @return true if playback syncing across opened sequencer is enabled
- L24 _public prototype_ `virtual void SetSequencerPlaybackSync(bool bEnable) = 0;` — Set the playback syncing option in Multi-User which syncs playback across user for opened sequencer. @param bEnable The value to set for playback syncing of opened sequencer
- L29 _public prototype_ `virtual bool IsUnrelatedSequencerTimelineSyncEnabled() const = 0;` — @return true if unrelated timeline syncing across opened sequencer is enabled
- L36 _public prototype_ `virtual void SetUnrelatedSequencerTimelineSync(bool bEnable) = 0;` — Set the unrelated timeline syncing option in Multi-User which syncs time from any remote sequence. @param bEnable The value to set for unrelated timeline syncing.
- L41 _public prototype_ `virtual bool IsSequencerRemoteOpenEnabled() const = 0;` — @return true if the remote open option is enabled.
- L46 _public prototype_ `virtual bool IsSequencerRemoteCloseEnabled() const = 0;` — @return true if the remote close option is enabled.
- L51 _public prototype_ `virtual bool IsSequencerPacingEnabled() const = 0;` — @return true if the sequencer pacer is enabled.
- L56 _public prototype_ `virtual float SequencerPacingDuration() const = 0;` — @return the current duration for the sequencer pacer.
- L64 _public prototype_ `virtual void SetSequencerRemoteOpen(bool bEnable) = 0;` — Set the remote open option in Multi-User which opens Sequencer for other users when this option is enabled on both user machines. @param bEnable The value to set for the remote open option
- L72 _public prototype_ `virtual void SetSequencerRemoteClose(bool bEnable) = 0;` — Set the remote close option in Multi-User which closes Sequencer for this user when the sequence is closed by a remote user. @param bEnable The value to set for the remote close option
- L77 _public prototype_ `virtual void SuspendSequencerPacing() = 0;` — Temporarily suspend sequencer pacing on this client.
- L82 _public prototype_ `virtual void ResumeSequencerPacing() = 0;` — Resume sequencer pacing on this client if the console variable is enabled.
- L89 _public prototype_ `virtual void SetSequencerPacingEnabled(bool bEnable) = 0;` — Specifies the sequencer pacing behavior while in a session. @param bValue The value to be set for the sequencer pacing option
- L96 _public prototype_ `virtual void SetSequencerPacingDuration(float Duration) = 0;` — Sets the sequencer pacing duration value. @param Duration The spacing between state event messages.

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Public/IConcertClientTransactionBridge.h` (Public)


#### struct `FConcertClientLocalTransactionCommonData`  
`struct FConcertClientLocalTransactionCommonData`  
_L18-35_
- desc: Common data for a transaction.
- L20 _public function_ `FConcertClientLocalTransactionCommonData(const FText InTransactionTitle, const FGuid& InTransactionId, const FGuid& InOperationId, UObject* InPrimaryObject) : TransactionTitle(InTransactionTitle) , TransactionId(InTransactionId) , OperationId(InOperationId) , PrimaryObject(InPrimaryObject)`
- L28 _public member_ `FText TransactionTitle;`
- L29 _public member_ `FGuid TransactionId;`
- L30 _public member_ `FGuid OperationId;`
- L31 _public member_ `FWeakObjectPtr PrimaryObject;`
- L32 _public member_ `TArray<FName> ModifiedPackages;`
- L33 _public member_ `TArray<FConcertObjectId> ExcludedObjectUpdates;`
- L34 _public member_ `bool bIsExcluded = false;`

#### struct `FConcertClientLocalTransactionSnapshotData`  
`struct FConcertClientLocalTransactionSnapshotData`  
_L40-43_
- desc: Snapshot data for a transaction.
- L42 _public member_ `TArray<FConcertExportedObject> SnapshotObjectUpdates;`

#### struct `FConcertClientLocalTransactionFinalizedData`  
`struct FConcertClientLocalTransactionFinalizedData`  
_L48-53_
- desc: Finalized data for a transaction.
- L50 _public member_ `FConcertLocalIdentifierTable FinalizedLocalIdentifierTable;`
- L51 _public member_ `TArray<FConcertExportedObject> FinalizedObjectUpdates;`
- L52 _public member_ `bool bWasCanceled = false;`

#### enum `ETransactionNotification`  
`enum class ETransactionNotification`  
_L55-59_
- L57 _public enumerator_ `Begin`
- L58 _public enumerator_ `End`

#### struct `FConcertConflictDescriptionBase`  
`struct FConcertConflictDescriptionBase`  
_L64-77_
- desc: Data holding information about conflict that occurred while processing an inbound transaction.
- L66 _public prototype_ `FConcertConflictDescriptionBase() = default;`
- L67 _public prototype_ `virtual ~FConcertConflictDescriptionBase() = default;`
- L69 _public function_ `virtual FText GetConflictDetails() const`
- L73 _public function_ `virtual FText GetConflictTitle() const`

#### struct `FConcertTransactionFilterArgs`  
`struct FConcertTransactionFilterArgs`  
_L79-90_
- L81 _public member_ `UObject* ObjectToFilter;`
- L82 _public member_ `UPackage* Package;`
- L83 _public member_ `const FTransactionObjectEvent& TransactionEvent;`
- L85 _public function_ `FConcertTransactionFilterArgs(UObject* InObjectToFilter, UPackage* InPackage, const FTransactionObjectEvent& InTransactionEvent) : ObjectToFilter(InObjectToFilter) , Package(InPackage) , TransactionEvent(InTransactionEvent)`

#### class `IConcertClientTransactionBridge`  
`class IConcertClientTransactionBridge`  
_L105-245_
- desc: Bridge between the editor transaction system and Concert. Deals with converting local ongoing transactions to Concert transaction data, and applying remote Concert transaction data onto this local instance.
- L111 _public prototype_ `static TUniquePtr<IConcertClientTransactionBridge> NewInstance();` — Create a new instance of the concrete implementation of this class.
- L122 _public prototype_ `virtual ~IConcertClientTransactionBridge() = default;`
- L128 _public prototype_ `virtual void SetIncludeEditorOnlyProperties(const bool InIncludeEditorOnlyProperties) = 0;` — Set whether or not to include editor-only properties when serializing object and property changes. @note This is set to true by default.
- L134 _public prototype_ `virtual void SetIncludeNonPropertyObjectData(const bool InIncludeNonPropertyObjectData) = 0;` — Set whether to include non-property object data in updates, or whether to only include property changes. @note This is set to true by default.
- L141 _public prototype_ `virtual void SetIncludeAnnotationObjectChanges(const bool InIncludeAnnotationObjectChanges) = 0;` — Set whether to include object changes that have been generated via a transaction annotation (where possible), or whether to send the entire transaction annotation blob instead. @note This is set to UConcertSyncConfig::bIncludeAnnotationObjectChanges by default.
- L147 _public prototype_ `virtual FOnConcertClientLocalTransactionSnapshot& OnLocalTransactionSnapshot() = 0;` — Called when an ongoing transaction is updated via a snapshot. @note This is called during end-frame processing.
- L153 _public prototype_ `virtual FOnConcertClientLocalTransactionFinalized& OnLocalTransactionFinalized() = 0;` — Called when an transaction is finalized. @note This is called during end-frame processing.
- L156 _public prototype_ `virtual FOnConcertConflictResolutionForPendingSend& OnConflictResolutionForPendingSend() = 0;` — Callback when a conflict occurs on pending transactions.
- L162 _public prototype_ `virtual bool CanApplyRemoteTransaction() const = 0;` — Can we currently apply a remote transaction event to this local instance? @return True if we can apply a remote transaction, false otherwise.
- L168 _public prototype_ `virtual FOnApplyTransaction& OnApplyTransaction() = 0;` — Notification of an application of a transaction. This will tell the user if the transaction originates as a snapshot or is a finalized snapshot message.
- L198 _public prototype_ `virtual void ApplyRemoteTransaction(const FConcertTransactionEventBase& InEvent, const FConcertSessionVersionInfo* InVersionInfo, const TArray<FName>& InPackagesToProcess, const FConcertLocalIdentifierTable* InLocalIdentifierTablePtr, const bool bIsSnapshot, FRemoteTransactionResult* ResultInfo = nullptr) = 0;` — Apply a remote transaction event to this local instance. @param InEvent					The event to apply. @param InVersionInfo				The version information for the serialized data in the event, or null if the event should be serialized using the compiled in version info. @param InPackagesToProcess		The list of packages to apply changes for, or an empty array to apply all changes. @param InLocalIdentifierTablePtr The local identifier table for the event data (if any). @param bIsSnapshot				True if this transaction event was a snapshot rather than a finalized transaction. @param ResultInfo				Optional extended result information to fill.
- L214 _public prototype_ `void RegisterTransactionFilter( FName FilterName, PRAGMA_DISABLE_DEPRECATION_WARNINGS FTransactionFilterDelegate FilterHandle PRAGMA_ENABLE_DEPRECATION_WARNINGS );` — `UE_DEPRECATED(5.5, "Use the version of RegisterTransactionFilter accepting FOnFilterTransactionDelegate instead.")` — Callback to register delegate for handling transaction events
- L221 _public prototype_ `virtual void RegisterTransactionFilter(FName FilterName, FOnFilterTransactionDelegate FilterDelegate) = 0;` — Callback to register delegate for handling transaction events
- L224 _public prototype_ `virtual void UnregisterTransactionFilter(FName FilterName) = 0;` — Callback to register delegate for handling transaction events
- L231 _public prototype_ `virtual void StartBridge() = 0;` — Bind to the transaction system to receive transaction events.  In past versions of IConcertClientTransactionBridge, this binding happened automatically.  To prevent possible performance impact from handling editor transactions when the bridge is not needed, users now have to indicate when they want to start the bridge which binds to the underlying transaction system.
- L237 _public prototype_ `virtual void StopBridge() = 0;` — Stop briding the transaction system.  After this call the bridge will unbind from any handlers to the underlying transaction system and transaction events will not be processed.
- L244 _protected prototype_ `virtual bool& GetIgnoreLocalTransactionsRef() = 0;` — Function to access the internal bool controlling whether local transactions are currently being tracked. @note Exists to implement FScopedIgnoreLocalTransaction.
- L248 _function_ `inline void IConcertClientTransactionBridge::RegisterTransactionFilter( FName FilterName, FTransactionFilterDelegate FilterHandle )`

#### struct `IConcertClientTransactionBridge::FScopedIgnoreLocalTransaction`  
`struct FScopedIgnoreLocalTransaction : private TGuardValue<bool>`  
_L114-120_
- inherits: `TGuardValue<bool>`
- desc: Scoped struct to ignore a local transaction
- L116 _public function_ `FScopedIgnoreLocalTransaction(IConcertClientTransactionBridge& InTransactionBridge) : TGuardValue(InTransactionBridge.GetIgnoreLocalTransactionsRef(), true)`

#### struct `IConcertClientTransactionBridge::FRemoteTransactionObjectResult`  
`struct FRemoteTransactionObjectResult`  
_L171-181_
- desc: Extended information that describes what changed for a single object within a remote transaction
- L174 _public member_ `FSoftObjectPath ObjectPath;` — Final path of the object after the given remote transaction was applied to it
- L177 _public member_ `int32 ObjectIndex = INDEX_NONE;` — Index into the FConcertTransactionEventBase::ExportedObjects array in the remote transaction that was applied to this object
- L180 _public member_ `bool bNewlyCreated : 1 = false;` — True if the object was created by this remote transaction, or false if it already existed

#### struct `IConcertClientTransactionBridge::FRemoteTransactionResult`  
`struct FRemoteTransactionResult`  
_L184-187_
- desc: Extended information that describes what changed after applying a remote transaction
- L186 _public member_ `TArray<FRemoteTransactionObjectResult> Objects;`

#### Free symbols / members of external scopes

- L92 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnApplyTransaction, ETransactionNotification, const bool bIsSnapshot);`
- L92 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnApplyTransaction, ETransactionNotification, const bool bIsSnapshot);`
- L94 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(ETransactionFilterResult, FTransactionFilterDelegate, UObject*, UPackage*);`
- L94 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(ETransactionFilterResult, FTransactionFilterDelegate, UObject*, UPackage*);` — `UE_DEPRECATED(5.5, "Use FOnFilterTransactionDelegate instead.")`
- L95 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(ETransactionFilterResult, FOnFilterTransactionDelegate, const FConcertTransactionFilterArgs&);`
- L95 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(ETransactionFilterResult, FOnFilterTransactionDelegate, const FConcertTransactionFilterArgs&);`
- L96 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnConcertClientLocalTransactionSnapshot, const FConcertClientLocalTransactionCommonData&, const FConcertClientLocalTransactionSnapshotData&);`
- L96 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnConcertClientLocalTransactionSnapshot, const FConcertClientLocalTransactionCommonData&, const FConcertClientLocalTransactionSnapshotData&);`
- L97 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnConcertClientLocalTransactionFinalized, const FConcertClientLocalTransactionCommonData&, const FConcertClientLocalTransactionFinalizedData&);`
- L97 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnConcertClientLocalTransactionFinalized, const FConcertClientLocalTransactionCommonData&, const FConcertClientLocalTransactionFinalizedData&);`
- L98 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnConcertConflictResolutionForPendingSend, const FConcertConflictDescriptionBase& ConflictDescription);`
- L98 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnConcertConflictResolutionForPendingSend, const FConcertConflictDescriptionBase& ConflictDescription);`
- L254 _function_ `` (scope `IConcertClientTransactionBridge::RegisterTransactionFilter`)

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Public/IConcertClientWorkspace.h` (Public)


#### class `IConcertClientWorkspace`  
`class IConcertClientWorkspace`  
_L26-233_
- L32 _public prototype_ `virtual IConcertClientSession& GetSession() const = 0;` — Get the associated session.
- L37 _public prototype_ `virtual FGuid GetWorkspaceLockId() const = 0;` — @return the client id this workspace uses to lock resources.
- L42 _public prototype_ `virtual FGuid GetResourceLockId(const FName InResourceName) const = 0;` — @return a valid client id of the owner of this resource lock or an invalid id if unlocked
- L51 _public prototype_ `virtual bool AreResourcesLockedBy(TArrayView<const FName> ResourceNames, const FGuid& ClientId) = 0;` — Verify if resources are locked by a particular client @param ResourceNames list of resources path to verify @param ClientId the client id to verify @return true if all resources in ResourceNames are locked by ClientId @note passing an invalid client id will return true if all resources are unlocked
- L58 _public prototype_ `virtual TFuture<FConcertResourceLockResponse> LockResources(TArray<FName> InResourceName) = 0;` — Attempt to lock the given resource. @note Passing force will always assign the lock to the given endpoint, even if currently locked by another. @return True if the resource was locked (or already locked by the given endpoint), false otherwise.
- L65 _public prototype_ `virtual TFuture<FConcertResourceLockResponse> UnlockResources(TArray<FName> InResourceName) = 0;` — Attempt to unlock the given resource. @note Passing force will always clear, even if currently locked by another endpoint. @return True if the resource was unlocked, false otherwise.
- L71 _public prototype_ `virtual bool HasSessionChanges() const = 0;` — Tell if a workspace contains session changes. @return True if the session contains any changes.
- L78 _public prototype_ `virtual TArray<FName> GatherSessionChanges(bool IgnorePersisted = true) = 0;` — Gather assets changes that happened on the workspace in this session. @param IgnorePersisted if true will not return packages which have already been persisted in their current state. @return a list of package names that were modified during the session.
- L85 _public prototype_ `virtual TOptional<FString> GetValidPackageSessionPath(FName PackageName) const = 0;` — Returns the full path to the package if it is a valid package session change. @param PackageName the package to check. @return the full path to the package if it is valid.
- L88 _public prototype_ `virtual FPersistResult PersistSessionChanges(FPersistParameters InParam) = 0;` — Persist the session changes from the package list and prepare it for source control submission
- L97 _public prototype_ `virtual void GetActivities(const int64 FirstActivityIdToFetch, const int64 MaxNumActivities, TMap<FGuid, FConcertClientInfo>& OutEndpointClientInfoMap, TArray<FConcertSessionActivity>& OutActivities) const = 0;` — Get Activities from the session. @param FirstActivityIdToFetch The ID at which to start fetching activities. @param MaxNumActivities The maximum number of activities to fetch. @param OutEndpointClientInfoMap The client info for the activities fetched. @param OutActivities the activities fetched.
- L102 _public prototype_ `virtual int64 GetLastActivityId() const = 0;` — Get the ID of the last activity in the session.
- L107 _public prototype_ `virtual FOnActivityAddedOrUpdated& OnActivityAddedOrUpdated() = 0;` — @return the delegate called every time an activity is added to or updated in the session.
- L115 _public prototype_ `virtual bool HasLiveTransactionSupport(class UPackage* InPackage) const = 0;` — Indicate if an asset package is supported for live transactions. @param InAssetPackage The package to check @return true if we support live transactions for objects inside the package
- L122 _public prototype_ `virtual bool ShouldIgnorePackageDirtyEvent(class UPackage* InPackage) const = 0;` — Indicate if package dirty event should be ignored for a package @param InPackage The package to check @return true if dirty event should be ignored for said package.
- L134 _public prototype_ `virtual bool FindTransactionEvent(const int64 TransactionEventId, FConcertSyncTransactionEvent& OutTransactionEvent, const bool bMetaDataOnly) const = 0;` — Lookup the specified transaction event. @param[in] TransactionEventId ID of the transaction to look for. @param[out] OutTransactionEvent The transaction corresponding to TransactionEventId if found. @param[in] bMetaDataOnly True to extract the event meta-data only (title, ids, etc), false to get the full transaction data (to reapply/inspect it). @return Whether the transaction event was found and requested data available. If bMetaDataOnly is false and the event was partially synced (because it was superseded by another one), the function returns false. @see FindOrRequestTransactionEvent() if the full transaction data is required. @note This function is more efficient to use if only the meta data is required.
- L145 _public prototype_ `virtual TFuture<TOptional<FConcertSyncTransactionEvent>> FindOrRequestTransactionEvent(const int64 TransactionEventId, const bool bMetaDataOnly) = 0;` — Lookup the specified transaction events. By default, some transaction activities are partially synced (only the summary) when the system detects that the transaction was superseded by another one. @param[in] TransactionEventId ID of the transaction to look for. @param[in] bMetaDataOnly True to extract the event meta-data only (title, IDs, etc), false to get the full transaction data (to reapply/inspect it). @return A future containing the event, if found. If bMetaDataOnly is false and the event was partially synced (because it was superseded by another one) the function will perform an asynchronous server request to get the transaction data. @note If only the meta data is required, consider using FindTransactionEvent() as it is more efficient.
- L153 _public prototype_ `virtual bool FindPackageEvent(const int64 PackageEventId, FConcertSyncPackageEventMetaData& OutPackageEvent) const = 0;` — Lookup the specified package event. @param[in] PackageEventId ID of the package to look for. @param[out] OutPackageEvent Information about the package except the package data itself. @return Whether the package event meta data was found.
- L161 _public prototype_ `virtual bool FindReplicationEvent(const int64 ReplicationEventId, FConcertSyncReplicationEvent& OutReplicationEvent) const = 0;` — Lookup the specified replication event. @param[in] ReplicationEventId ID of the replication event to look for. @param[out] OutReplicationEvent The replication event corresponding to ReplicationEventId if found. @return Whether the replication event was found and requested data available.
- L167 _public prototype_ `virtual FOnWorkspaceSynchronized& OnWorkspaceSynchronized() = 0;` — @return the delegate called every time the workspace is synced. This is when the server has indicated that all activities have been sent and ready to be finalized in the current workspace.
- L172 _public prototype_ `virtual FOnFinalizeWorkspaceSyncCompleted& OnFinalizeWorkspaceSyncCompleted() = 0;` — @return The delegate called after a workspace has been completely synced and finalized.  All transactions are posted and packages have been loaded.
- L182 _public prototype_ `virtual void AddWorkspaceFinalizeDelegate(FName InDelegateName, FCanFinalizeWorkspaceDelegate InDelegate) = 0;` — This delegate allows user to defer the finalization of a sync workspace. This is for situtations where multiple client nodes need to be finalized at the same point in time.  The delegate function should return true when workspace synchronization is allowed and it will be called on OnEndFrame() of the tick loop. @param InDelegateName the identifier for the provided delegate. @param InDelegate the delegate to use to query if finalize workspace
- L188 _public prototype_ `virtual void RemoveWorkspaceFinalizeDelegate(FName InDelegateName) = 0;` — Remove the attached named delegate for workspace finalization. @param InDelegateName identifying name for the delegate.
- L198 _public prototype_ `virtual void AddWorkspaceCanProcessPackagesDelegate(FName InDelegateName, FCanProcessPendingPackages Delegate) = 0;` — This delegate allows user to defer the finalization of a package updates. This is for situtations where multiple client nodes need finalize their package updates together. The delegate function should return true when workspace synchronization is allowed and it will be called on OnEndFrame() of the tick loop. @param InDelegateName the identifier for the provided delegate. @param InDelegate the delegate to use to query.
- L204 _public prototype_ `virtual void RemoveWorkspaceCanProcessPackagesDelegate(FName InDelegateName) = 0;` — Remove the attached named delegate for package synchronization. @param InDelegateName identifying name for the delegate.
- L209 _public prototype_ `virtual bool IsReloadingPackage(FName PackageName) const = 0;` — Returns true if the current named package is being reloaded by the package manager.
- L214 _public prototype_ `virtual IConcertClientDataStore& GetDataStore() = 0;` — @return the key/value store shared by all clients.
- L224 _public prototype_ `virtual bool IsAssetModifiedByOtherClients(const FName& AssetName, int32* OutOtherClientsWithModifNum = nullptr, TArray<FConcertClientInfo>* OutOtherClientsWithModifInfo = nullptr, int32 OtherClientsWithModifMaxFetchNum = 0) const = 0;` — Returns true if the specified asset has unsaved modifications from any other client than the one corresponding to this workspace client and possibly returns more information about those other clients. @param[in] AssetName The asset name. @param[out] OutOtherClientsWithModifNum If not null, will contain how many other client(s) have modified the specified package. @param[out] OutOtherClientsWithModifInfo If not null, will contain the other client(s) who modified the packages, up to OtherClientsWithModifMaxFetchNum. @param[in] OtherClientsWithModifMaxFetchNum The maximum number of client info to store in OutOtherClientsWithModifInfo if the latter is not null.
- L232 _public prototype_ `virtual void SetIgnoreOnRestoreFlagForEmittedActivities(bool bIgnore) = 0;` — Controls whether the activities emitted to the server through this workspace are marked as 'ignored on restore'. By default, all activities are marked as 'restorable'. When the workspace 'ignore' state is true, the events emitted are recorded by the server, but are marked as 'should not restore'. Non-restorable activities are used for inspection. @note This was implemented to prevent multi-users transactions from being restored by disaster recovery in case of a crash during as multi-user session. @param bIgnore Whether all further events emitted are marked as 'ignored on restore'.

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FCanFinalizeWorkspaceDelegate);`
- L19 _prototype_ `DECLARE_DELEGATE_RetVal(bool, FCanFinalizeWorkspaceDelegate);`
- L20 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FCanProcessPendingPackages);`
- L20 _prototype_ `DECLARE_DELEGATE_RetVal(bool, FCanProcessPendingPackages);`
- L22 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnWorkspaceSynchronized);`
- L22 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnWorkspaceSynchronized);`
- L23 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnFinalizeWorkspaceSyncCompleted);`
- L23 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnFinalizeWorkspaceSyncCompleted);`
- L24 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnActivityAddedOrUpdated, const FConcertClientInfo& , const FConcertSyncActivity& , const FStructOnScope& );`
- L24 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnActivityAddedOrUpdated, const FConcertClientInfo& , const FConcertSyncActivity& , const FStructOnScope& );`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Public/IConcertSyncClient.h` (Public)


#### enum `EEditorPlayMode`  
`enum class EEditorPlayMode : uint8`  
_L28-38_
- desc: Defines the supported editor play modes.
- L31 _public enumerator_ `None` — The editor is not in any play mode.
- L34 _public enumerator_ `PIE` — The editor is in "Play In Editor" play mode.
- L37 _public enumerator_ `SIE` — The editor is in "Simulate In Editor" play mode.

#### class `IConcertSyncClient`  
`class IConcertSyncClient`  
_L43-123_
- desc: Interface for a Concert Sync Client.
- L46 _public prototype_ `virtual ~IConcertSyncClient() = default;`
- L49 _public prototype_ `virtual void Startup(const UConcertClientConfig* InClientConfig, const EConcertSyncSessionFlags InSessionFlags) = 0;` — Start this Concert Sync Client using the given config
- L52 _public prototype_ `virtual void Shutdown() = 0;` — Stop this Concert Sync Client
- L55 _public prototype_ `virtual IConcertClientRef GetConcertClient() const = 0;` — Get the current client
- L58 _public prototype_ `virtual TSharedPtr<IConcertClientWorkspace> GetWorkspace() const = 0;` — Get the current session client workspace, if any.
- L66 _public prototype_ `virtual IConcertClientPresenceManager* GetPresenceManager() const = 0;` — Get the current session presence manager, if any. @note that pointer shouldn't be stored and always accessed through this client.
- L72 _public prototype_ `virtual IConcertClientSequencerManager* GetSequencerManager() const = 0;` — Get the current session sequencer manager, if any. @note that pointer shouldn't be stored and always accessed through this client.
- L78 _public prototype_ `virtual IConcertClientReplicationManager* GetReplicationManager() const = 0;` — Get the current session replication manager, if any. @note that pointer shouldn't be stored and always accessed through this client.
- L83 _public prototype_ `virtual FOnConcertClientWorkspaceStartupOrShutdown& OnWorkspaceStartup() = 0;` — Get the delegate called on every workspace startup.
- L86 _public prototype_ `virtual FOnConcertClientWorkspaceStartupOrShutdown& OnWorkspaceShutdown() = 0;` — Get the delegate called on every workspace shutdown.
- L89 _public prototype_ `virtual FOnConcertClientSyncSessionStartupOrShutdown& OnSyncSessionStartup() = 0;` — Get the delegate called just before the workspace gets created.
- L92 _public prototype_ `virtual FOnConcertClientSyncSessionStartupOrShutdown& OnSyncSessionShutdown() = 0;` — Get the delegate called just after the workspace gets deleted.
- L97 _public prototype_ `virtual void PersistSpecificChanges(TArrayView<const FName> Packages) = 0;` — Persist specific packages
- L100 _public prototype_ `virtual void PersistAllSessionChanges() = 0;` — Persist all session changes and prepare the files for source control submission.
- L108 _public prototype_ `virtual void GetSessionClientActions(const FConcertSessionClientInfo& InClientInfo, TArray<FConcertActionDefinition>& OutActions) const = 0;` — Queries the list of opaque actions that could be performed on the specified client session, like turning the client presence visibily on/off in the map. The actions are usually mapped to buttons and are a way to provide extra functionalities while keeping the implementation hidden. @param InClientInfo The client for which the actions are queried. @param OutActions The available actions, if any.
- L111 _public prototype_ `virtual void SetFileSharingService(TSharedPtr<IConcertFileSharingService> InFileSharingService) = 0;` — Set the file sharing service, enabling the server to work with large files. The client and the server must use compatible sharing services. The service must be set prior establishing a connection.
- L116 _public prototype_ `virtual IConcertClientTransactionBridge* GetTransactionBridge() const = 0;` — Get the current transaction bridge for this client
- L119 _public prototype_ `virtual IConcertClientPackageBridge* GetPackageBridge() const = 0;` — Get the current package bridge for this client.
- L122 _public prototype_ `virtual IConcertClientReplicationBridge* GetReplicationBridge() const = 0;` — Get the current replication bridge for this client.

#### Free symbols / members of external scopes

- L24 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnConcertClientWorkspaceStartupOrShutdown, const TSharedPtr<IConcertClientWorkspace>& );`
- L24 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnConcertClientWorkspaceStartupOrShutdown, const TSharedPtr<IConcertClientWorkspace>& );`
- L25 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnConcertClientSyncSessionStartupOrShutdown, const IConcertSyncClient* );`
- L25 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnConcertClientSyncSessionStartupOrShutdown, const IConcertSyncClient* );`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Public/IConcertSyncClientModule.h` (Public)


#### class `IConcertSyncClientModule`  
`class IConcertSyncClientModule : public IModuleInterface`  
_L22-79_
- inherits: `IModuleInterface`
- desc: Interface for the Concert Sync Client module.
- L31 _public function_ `static inline IConcertSyncClientModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L42 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() during shutdown if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L53 _public prototype_ `virtual UConcertClientConfig* ParseClientSettings(const TCHAR* CommandLine) = 0;` — Parse command line client settings and apply them @param CommandLine the application command line arguments @return The client settings, modified or not by the command line
- L60 _public prototype_ `virtual TSharedRef<IConcertSyncClient> CreateClient(const FString& InRole) = 0;` — Create a sync client that will perform a certain role (eg, MultiUser, DisasterRecovery, etc) @param InRole The role to create @return The client
- L63 _public prototype_ `virtual IConcertClientPackageBridge& GetPackageBridge() = 0;` — Get the bridge between the editor package system and Concert.
- L66 _public prototype_ `virtual IConcertClientTransactionBridge& GetTransactionBridge() = 0;` — Get the bridge between the editor transaction system and Concert.
- L69 _public prototype_ `virtual IConcertClientReplicationBridge& GetReplicationBridge() = 0;` — Gets the bridge between the editor UObjects and Concert.
- L72 _public prototype_ `virtual TArray<TSharedRef<IConcertSyncClient>> GetClients() const = 0;` — Returns the list of active clients.
- L75 _public prototype_ `virtual TSharedPtr<IConcertSyncClient> GetClient(const FString& InRole) const = 0;` — Find a concert sync client.
- L78 _public prototype_ `virtual FOnConcertClientCreated& OnClientCreated() = 0;` — Delegate invoked when a new concert sync client is created.

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnConcertClientCreated, TSharedRef<IConcertSyncClient>);`
- L15 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnConcertClientCreated, TSharedRef<IConcertSyncClient>);`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Public/Replication/IConcertClientReplicationBridge.h` (Public)


#### class `IConcertClientReplicationBridge`  
`class IConcertClientReplicationBridge`  
_L34-82_
- desc: A session-independent object bridging Unreal Engine with Concert. Responsible for tracking the lifetime of replicated objects, i.e. level (un)load, etc. An UObject is called "available" if it is in a state suitable for replicating; otherwise it is "unavailable". It is "tracked" if this bridge is keep track of whether is available; otherwise is is "untracked". The moment a tracked object is determined to be available it is said to "have been discovered". The moment is determined to be unavailable, it is said to "have become hidden". In the editor an UObject should be considered - available: - in an UWorld the client currently has open, - in an active data layer, - unavailable - in a non-loaded UWorld, - in an unloaded or loaded data layer (remember that loaded means not visible), - does not have an UWorld as outer (TODO: in the future this restriction could be lifted - there is no technical reason for it - VP workflows just do not need it right now)
- L38 _public prototype_ `virtual ~IConcertClientReplicationBridge() = default;`
- L46 _public prototype_ `virtual void PushTrackedObjects(TArrayView<const FSoftObjectPath> TrackedObjects) = 0;` — Starts tracking a list of objects, possibly triggering OnObjectDiscovered immediately. Increments a tracking counter for how often this object was requested to be tracked; there may be multiple independent systems requiring tracking.
- L52 _public prototype_ `virtual void PopTrackedObjects(TArrayView<const FSoftObjectPath> TrackedObjects) = 0;` — Stops tracking a list of objects, possibly triggering OnObjectRemoved immediately. Decrements the tracking counter. If it reaches 0, the object is no longer tracked; there may be multiple independent systems requiring tracking.
- L65 _public prototype_ `virtual bool IsObjectAvailable(const FSoftObjectPath& Path) = 0;` — More lightweight version of FindObjectIfAvailable which does not force the UObject to be loaded, if it is determined to be available. This function should be called instead of FindAndTrackObjectIfAvailable if the UObject instance is not needed. This function will not discover nor hide any UObject (that means broadcast OnObjectDiscovered or OnObjectHidden), unless it is tracked, in which case it can. @param Path The object to find @return Whether a call to FindObjectIfAvailable would return a valid object.
- L76 _public prototype_ `virtual UObject* FindObjectIfAvailable(const FSoftObjectPath& Path) = 0;` — Obtains the object if it is available. This does not load the object. This function will not discover nor hide any UObject (that means broadcast OnObjectDiscovered or OnObjectHidden), unless it is tracked, in which case it can. @param Path The object to find @return The object if it was valid or nullptr
- L79 _public prototype_ `virtual FConcertClientReplicationBridgeObjectEvent& OnObjectDiscovered() = 0;` — Event for when a replicatable object becomes available, e.g. because its level is loaded.
- L81 _public prototype_ `virtual FConcertClientReplicationBridgeObjectPathEvent& OnObjectHidden() = 0;` — Event for when an object that was previously discovered becomes unavailable, e.g. because it is unloaded.

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FConcertClientReplicationBridgeObjectEvent, UObject&);`
- L13 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FConcertClientReplicationBridgeObjectEvent, UObject&);`
- L14 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FConcertClientReplicationBridgeObjectPathEvent, const FSoftObjectPath&);`
- L14 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FConcertClientReplicationBridgeObjectPathEvent, const FSoftObjectPath&);`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Public/Replication/IConcertClientReplicationManager.h` (Public)


#### struct `UE::ConcertSyncClient::Replication::FJoinReplicatedSessionArgs`  
`struct FJoinReplicatedSessionArgs`  
_L25-29_
- L28 _public member_ `TArray<FConcertReplicationStream> Streams;` — The streams this client offers.

#### struct `UE::ConcertSyncClient::Replication::FJoinReplicatedSessionResult`  
`struct FJoinReplicatedSessionResult`  
_L31-42_
- L34 _public member_ `EJoinReplicationErrorCode ErrorCode;` — Error code sent by the server.
- L36 _public member_ `FString DetailedErrorMessage;` — Optional error message to help human user resolve the error.
- L38 _public function_ `FJoinReplicatedSessionResult(EJoinReplicationErrorCode ErrorCode, FString DetailedErrorMessage = TEXT("")) : ErrorCode(ErrorCode) , DetailedErrorMessage(MoveTemp(DetailedErrorMessage))`

#### struct `UE::ConcertSyncClient::Replication::FRemoteEditEvent`  
`struct FRemoteEditEvent`  
_L44-48_
- L46 _public member_ `const EConcertReplicationChangeClientReason Reason;`
- L47 _public member_ `const FConcertReplication_ClientChangeData& ChangeData;`

#### class `IConcertClientReplicationManager`  
`class IConcertClientReplicationManager`  
_L57-193_
- desc: Handles all communication with the server regarding replication. Keeps a list of properties to send along with their send rules. Tells the server which properties this client is interested in receiving.
- L66 _public prototype_ `virtual TFuture<UE::ConcertSyncClient::Replication::FJoinReplicatedSessionResult> JoinReplicationSession(UE::ConcertSyncClient::Replication::FJoinReplicatedSessionArgs Args) = 0;` — Joins a replication session. Subsequent calls to JoinReplicationSession will fail until either the resulting TFuture returns or LeaveReplicationSession is called. @note This future can finish on any thread (e.g. when message endpoint times out); usually it finishes on the game thread.
- L68 _public prototype_ `virtual void LeaveReplicationSession() = 0;` — Leaves the current replication session.
- L74 _public prototype_ `virtual bool CanJoin() = 0;` — Whether it is valid to call JoinReplicationSession right now. Returns false if it was called and its future has not yet concluded. If this returns true, you can call JoinReplicationSession to attempt joining the session.
- L76 _public prototype_ `virtual bool IsConnectedToReplicationSession() = 0;` — Whether JoinReplicationSession completed successfully and LeaveReplicationSession has not yet been called.
- L85 _public prototype_ `virtual EStreamEnumerationResult ForEachRegisteredStream(TFunctionRef<EBreakBehavior(const FConcertReplicationStream& Stream)> Callback) const = 0;` — Iterates the streams the client has registered with the server. It only makes sense to call this function the manager has joined a replication session. @return Whether this manager is connected to a session (Iterated) or not (NoRegisteredStreams). @note This future can finish on any thread (e.g. when message endpoint times out); usually it finishes on the game thread.
- L87 _public prototype_ `bool HasRegisteredStreams() const;` — @return Whether this manager has any registered streams (basically whether ForEachRegisteredStream returns EStreamEnumerationResult::Iterated).
- L89 _public prototype_ `TArray<FConcertReplicationStream> GetRegisteredStreams() const;` — @return The streams registered with the server.
- L95 _public prototype_ `virtual TFuture<FConcertReplication_ChangeAuthority_Response> RequestAuthorityChange(FConcertReplication_ChangeAuthority_Request Args) = 0;` — Requests from the server to change the authority over some objects. @note This future can finish on any thread (e.g. when message endpoint times out); usually it finishes on the game thread.
- L97 _public prototype_ `TFuture<FConcertReplication_ChangeAuthority_Response> TakeAuthorityOver(TConstArrayView<FSoftObjectPath> Objects);` — Util function that will request authority for all streams for the given objects.
- L99 _public prototype_ `TFuture<FConcertReplication_ChangeAuthority_Response> ReleaseAuthorityOf(TConstArrayView<FSoftObjectPath> Objects);` — Util function that will let go over all authority of the given objects.
- L106 _public prototype_ `virtual EAuthorityEnumerationResult ForEachClientOwnedObject(TFunctionRef<EBreakBehavior(const FSoftObjectPath& Object, TSet<FGuid>&& OwningStreams)> Callback) const = 0;` — Iterates through all objects that this client has authority over. @return Whether this manager is connected to a session (Iterated) or not (NoAuthorityAvailable)
- L108 _public prototype_ `virtual TSet<FGuid> GetClientOwnedStreamsForObject(const FSoftObjectPath& ObjectPath) const = 0;` — @return All the streams this client has registered that have authority for the given ObjectPath.
- L110 _public prototype_ `virtual bool HasAuthorityOver(const FSoftObjectPath& ObjectPath) const = 0;` — @return Whether this client has authority over ObjectPath for some stream.
- L112 _public prototype_ `TMap<FSoftObjectPath, TSet<FGuid>> GetClientOwnedObjects() const;` — @return All owned objects and associated owning streams.
- L116 _public prototype_ `virtual ESyncControlEnumerationResult ForEachSyncControlledObject(TFunctionRef<EBreakBehavior(const FConcertObjectInStreamID& Object)> Callback) const = 0;` — Iterates through all objects the server told the client to replicate, which happens when this client has taken authority and another client wants to receive the data.
- L118 _public prototype_ `virtual uint32 NumSyncControlledObjects() const = 0;` — @return Number of items ForEachSyncControlledObject would iterate.
- L120 _public prototype_ `virtual bool HasSyncControl(const FConcertObjectInStreamID& Object) const = 0;` — @return Whether this client has sync control for a specific object in a stream.
- L122 _public prototype_ `TSet<FConcertObjectInStreamID> GetSyncControlledObjects() const;` — Util for converting all sync controlled objects into a TSet.
- L128 _public prototype_ `virtual TFuture<FConcertReplication_QueryReplicationInfo_Response> QueryClientInfo(FConcertReplication_QueryReplicationInfo_Request Args) = 0;` — Requests replication info about other clients, including the streams registered and which objects they have authority over (i.e. are sending). @note This future can finish on any thread (e.g. when message endpoint times out); usually it finishes on the game thread.
- L134 _public prototype_ `virtual TFuture<FConcertReplication_ChangeStream_Response> ChangeStream(FConcertReplication_ChangeStream_Request Args) = 0;` — Requests to change the client's registered stream. @note This future can finish on any thread (e.g. when message endpoint times out); usually it finishes on the game thread.
- L140 _public prototype_ `virtual TFuture<FConcertReplication_ChangeMuteState_Response> ChangeMuteState(FConcertReplication_ChangeMuteState_Request Request) = 0;` — Requests to change the global mute state of objects. Can only be done if the session has the EConcertSyncSessionFlags::ShouldAllowGlobalMuting flag.
- L142 _public prototype_ `TFuture<FConcertReplication_ChangeMuteState_Response> MuteObjects(TConstArrayView<FSoftObjectPath> Objects, EConcertReplicationMuteOption Flags = EConcertReplicationMuteOption::ObjectAndSubobjects);` — Util function that will mute all of Objects.
- L144 _public prototype_ `TFuture<FConcertReplication_ChangeMuteState_Response> UnmuteObjects(TSet<FSoftObjectPath> Objects, EConcertReplicationMuteOption Flags = EConcertReplicationMuteOption::ObjectAndSubobjects);` — Util function that will unmute all of Objects.
- L146 _public prototype_ `virtual TFuture<FConcertReplication_QueryMuteState_Response> QueryMuteState(FConcertReplication_QueryMuteState_Request Request = {}) = 0;` — Gets the global mute state.
- L147 _public prototype_ `TFuture<FConcertReplication_QueryMuteState_Response> QueryMuteState(TSet<FSoftObjectPath> Objects);`
- L150 _public prototype_ `virtual TFuture<FConcertReplication_RestoreContent_Response> RestoreContent(FConcertReplication_RestoreContent_Request Request = {}) = 0;` — Restore this client's stream content and authority to what a client had when they left. Only works if session has EConcertSyncSessionFlags::ShouldEnableReplicationActivities set.
- L156 _public prototype_ `virtual TFuture<FConcertReplication_PutState_Response> PutClientState(FConcertReplication_PutState_Request Request) = 0;` — Changes multiple clients' stream, authority, and optionally the global mute state. Useful for applying a preset. Only works if session has EConcertSyncSessionFlags::ShouldEnableRemoteEditing set.
- L158 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnPreStreamsChanged);`
- L160 _public prototype_ `virtual FOnPreStreamsChanged& OnPreStreamsChanged() = 0;` — Called right before the result of GetRegisteredStreams changes.
- L162 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnPostStreamsChanged);`
- L164 _public prototype_ `virtual FOnPostStreamsChanged& OnPostStreamsChanged() = 0;` — Called right after the result of GetRegisteredStreams has changed.
- L166 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnPreAuthorityChanged);`
- L168 _public prototype_ `virtual FOnPreAuthorityChanged& OnPreAuthorityChanged() = 0;` — Called right before GetClientOwnedObjects changes.
- L170 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnPostAuthorityChanged);`
- L172 _public prototype_ `virtual FOnPostAuthorityChanged& OnPostAuthorityChanged() = 0;` — Called right after GetClientOwnedObjects has changed.
- L174 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FSyncControlChanged);`
- L176 _public prototype_ `virtual FSyncControlChanged& OnPreSyncControlChanged() = 0;` — Called just before sync control change is applied.
- L178 _public prototype_ `virtual FSyncControlChanged& OnPostSyncControlChanged() = 0;` — Called just after sync control change is applied.
- L180 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRemoteEditApplied, const UE::ConcertSyncClient::Replication::FRemoteEditEvent&);`
- L185 _public prototype_ `virtual FOnRemoteEditApplied& OnPreRemoteEditApplied() = 0;` — Called before updating any local state in response to the server notifying us that the local client's content was remotely edited. This executes before OnPreStreamsChanged, OnPreAuthorityChanged, and OnPreSyncControlChanged, which may also get triggered depending on the change.
- L190 _public prototype_ `virtual FOnRemoteEditApplied& OnPostRemoteEditApplied() = 0;` — Called after updating any local state in response to the server notifying us that the local client's content was remotely edited. This executes after OnPreStreamsChanged, OnPreAuthorityChanged, and OnPreSyncControlChanged, which may also get triggered depending on the change.
- L192 _public prototype_ `virtual ~IConcertClientReplicationManager() = default;`

#### enum `IConcertClientReplicationManager::EStreamEnumerationResult`  
`enum class EStreamEnumerationResult`  
_L78-78_
- L78 _public enumerator_ `enum class EStreamEnumerationResult { NoRegisteredStreams, Iterated }; /** * Iterates the streams the client has registered with the server. * It only makes sense to call this function the manager has joined a replication session. * @return Whether this manager is connected to a session (Iterated) or not (NoRegisteredStreams). * @note This future can finish on any thread (e.g. when message endpoint times out); usually it finishes on the game thread. */ virtual EStreamEnumerationResult ForEachRegisteredStream(TFunctionRef<EBreakBehavior(const FConcertReplicationStream& Stream)> Callback) const = 0;`
- L78 _public enumerator_ `enum class EStreamEnumerationResult { NoRegisteredStreams, Iterated }; /** * Iterates the streams the client has registered with the server. * It only makes sense to call this function the manager has joined a replication session. * @return Whether this manager is connected to a session (Iterated) or not (NoRegisteredStreams). * @note This future can finish on any thread (e.g. when message endpoint times out); usually it finishes on the game thread. */ virtual EStreamEnumerationResult ForEachRegisteredStream(TFunctionRef<EBreakBehavior(const FConcertReplicationStream& Stream)> Callback) const = 0;`

#### enum `IConcertClientReplicationManager::EAuthorityEnumerationResult`  
`enum class EAuthorityEnumerationResult`  
_L101-101_
- L101 _public enumerator_ `enum class EAuthorityEnumerationResult { NoAuthorityAvailable, Iterated }; /** * Iterates through all objects that this client has authority over. * @return Whether this manager is connected to a session (Iterated) or not (NoAuthorityAvailable) */ virtual EAuthorityEnumerationResult ForEachClientOwnedObject(TFunctionRef<EBreakBehavior(const FSoftObjectPath& Object, TSet<FGuid>&& OwningStreams)> Callback) const = 0; virtual TSet<FGuid> GetClientOwnedStreamsForObject(const FSoftObjectPath& ObjectPath) const = 0;`
- L101 _public enumerator_ `enum class EAuthorityEnumerationResult { NoAuthorityAvailable, Iterated }; /** * Iterates through all objects that this client has authority over. * @return Whether this manager is connected to a session (Iterated) or not (NoAuthorityAvailable) */ virtual EAuthorityEnumerationResult ForEachClientOwnedObject(TFunctionRef<EBreakBehavior(const FSoftObjectPath& Object, TSet<FGuid>&& OwningStreams)> Callback) const = 0; virtual TSet<FGuid> GetClientOwnedStreamsForObject(const FSoftObjectPath& ObjectPath) const = 0;`

#### enum `IConcertClientReplicationManager::ESyncControlEnumerationResult`  
`enum class ESyncControlEnumerationResult`  
_L114-114_
- L114 _public enumerator_ `enum class ESyncControlEnumerationResult { NoneAvailable, Iterated }; virtual ESyncControlEnumerationResult ForEachSyncControlledObject(TFunctionRef<EBreakBehavior(const FConcertObjectInStreamID& Object)> Callback) const = 0; virtual uint32 NumSyncControlledObjects() const = 0; virtual bool HasSyncControl(const FConcertObjectInStreamID& Object) const = 0;`
- L114 _public enumerator_ `enum class ESyncControlEnumerationResult { NoneAvailable, Iterated }; virtual ESyncControlEnumerationResult ForEachSyncControlledObject(TFunctionRef<EBreakBehavior(const FConcertObjectInStreamID& Object)> Callback) const = 0; virtual uint32 NumSyncControlledObjects() const = 0; virtual bool HasSyncControl(const FConcertObjectInStreamID& Object) const = 0;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API CONCERTSYNCCLIENT_API`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace ConcertSyncClient` (scope `UE`)
- L23 _namespace_ `namespace Replication` (scope `UE::ConcertSyncClient`)
- L158 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnPreStreamsChanged);`
- L162 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnPostStreamsChanged);`
- L166 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnPreAuthorityChanged);`
- L170 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnPostAuthorityChanged);`
- L174 _delegate_ `DECLARE_MULTICAST_DELEGATE(FSyncControlChanged);`
- L180 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRemoteEditApplied, const UE::ConcertSyncClient::Replication::FRemoteEditEvent&);`

### `Plugins/Developer/Concert/ConcertSync/ConcertSyncClient/Source/ConcertSyncClient/Public/Replication/Misc/ClientPredictionUtils.h` (Public)


#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace ConcertSyncClient` (scope `UE`)
- L16 _namespace_ `namespace Replication` (scope `UE::ConcertSyncClient`)
- L31 _prototype_ `TOptional<int64> IncrementalBacktrackActivityHistoryForActivityThatSetsContent( const IConcertClientWorkspace& Workspace, const FConcertClientInfo& ClientInfo, TArray<FConcertBaseStreamInfo>& OutStreams, TArray<FConcertObjectInStreamID>& OutAuthority, int64 MaxToFetch = 50, int64 MinActivityIdCutoff = 1 );` (scope `UE::ConcertSyncClient::Replication`) — Leverages IConcertClientWorkspace::GetActivities to get chunks from the back of the activity history and passes them to BacktrackActivityHistoryForSettingActivities until an activity is found that sets the specified client's stream and authority content. @param Workspace The workspace to retrieve the activity history chunks from @param ClientInfo Only activities produced by clients that are logically equivalent to this info are considered (@see AreLogicallySameClients) @param OutStreams The streams the client had, if successful @param OutAuthority The authority the client had, if successful @param MaxToFetch Maximum number of activities to fetch with each IConcertClientWorkspace::GetActivities call @param MinActivityIdCutoff This is the min activity id an activity must have to be considered. Activities before this are not considered. @return The activity ID that contained the state. Unset if not found.
