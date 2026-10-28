# Plugins / DisplayClusterMultiUser

- module root: `Plugins/Runtime/nDisplay/Source/DisplayClusterMultiUser`
- headers: 4; symbols: 24
- symbol kinds: class=3, delegate=1, member=6, prototype=13, struct=1
- PrivateDependencyModuleNames: ConcertSyncClient, Core, CoreUObject, DisplayClusterConfiguration, Engine, MediaAssets

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMultiUser/Private/DisplayClusterMultiUserLog.h` (Private)


#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterMultiUser, Log, All);` — Module-wide log categories
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterMultiUser, Log, All);` — Module-wide log categories

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMultiUser/Private/DisplayClusterMultiUserManager.h` (Private)


#### class `FDisplayClusterMultiUserManager`  
`class FDisplayClusterMultiUserManager`  
_L14-23_
- desc: Manager for handling multi user transactions in nDisplay.
- L17 _public prototype_ `FDisplayClusterMultiUserManager();`
- L18 _public prototype_ `virtual ~FDisplayClusterMultiUserManager();`
- L21 _private prototype_ `void OnApplyRemoteTransaction(ETransactionNotification Notification, const bool bIsSnapshot);`
- L22 _private prototype_ `ETransactionFilterResult ShouldObjectBeTransacted(const FConcertTransactionFilterArgs& FilterArgs);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMultiUser/Private/DisplayClusterMultiUserModule.h` (Private)


#### class `FDisplayClusterMultiUserModule`  
`class FDisplayClusterMultiUserModule : public IModuleInterface`  
_L12-27_
- inherits: `IModuleInterface`
- L17 _public prototype_ `virtual void StartupModule() override;`
- L18 _public prototype_ `virtual void ShutdownModule() override;`
- L22 _private member_ `TUniquePtr<FDisplayClusterMultiUserManager> MultiUserManager;` — Manager for multi user connections.
- L25 _private member_ `TUniquePtr<FMediaAssetMultiUserManager> MediaAssetMUManager;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMultiUser/Private/MediaAssetMultiUserManager.h` (Private)


#### struct `FConcertMediaStateChangedEvent`  
`struct FConcertMediaStateChangedEvent`  
_L18-30_
- reflection: `USTRUCT()`
- desc: The event that is transfered over MU.
- L25 _public member_ `TArray<FString> ActorsPathNames;` — `UPROPERTY()` — Name used to find the object on the other side of MU.
- L29 _public member_ `uint8 State;` — `UPROPERTY()` — State to replicate on the other side.

#### class `FMediaAssetMultiUserManager`  
`class FMediaAssetMultiUserManager`  
_L35-68_
- desc: Reacts to state changes in Media Plates and transfers state change information to remote endpoints.
- L39 _public prototype_ `FMediaAssetMultiUserManager();`
- L41 _public prototype_ `virtual ~FMediaAssetMultiUserManager();`
- L46 _public prototype_ `void Register(TSharedRef<IConcertClientSession> InSession);` — Subscribes to the relevant Concert Sync events.
- L51 _public prototype_ `void Unregister(TSharedRef<IConcertClientSession> InSession);` — Unsubscribes from concert sync events.
- L56 _public prototype_ `void OnStateChangedEvent(const FConcertSessionContext& InConcertSessionContext, const FConcertMediaStateChangedEvent& InEvent);` — Reacts to changes in Media Plate from remove endpoints and forwards it to local Media Plates.
- L62 _public prototype_ `void OnMediaPlateStateChanged(const TArray<FString>& InNameId, uint8 InEnumState, bool bRemoteBroadcast);` — Called when Media Plate broadcasts state change events and sends a custom event to remote endpoints. bRemoteBroadcast identifies if event came from the remote endpoint or broadcasted locally.
- L66 _private member_ `TWeakPtr<IConcertClientSession> ConcertSession;`
- L67 _private member_ `FDelegateHandle OnMediaPlateStateChangedHandle;`
