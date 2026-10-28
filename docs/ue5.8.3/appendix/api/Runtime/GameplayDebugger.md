# Runtime / GameplayDebugger

- module root: `Source/Runtime/GameplayDebugger`
- headers: 15; symbols: 672
- symbol kinds: class=17, delegate=11, enum=7, enumerator=28, externvar=7, function=77, member=221, namespace=2, prototype=282, struct=18, typedef=2
- PrivateDependencyModuleNames: DeveloperSettings, DrawPrimitiveDebugger, InputCore, LevelEditor, RenderCore, Slate, UnrealEd
- PrivateIncludePathModuleNames: Settings
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Source/Runtime/GameplayDebugger/Public/GameplayDebugger.h` (Public)


#### enum `EGameplayDebuggerCategoryState`  
`enum class EGameplayDebuggerCategoryState : uint8`  
_L41-48_
- L43 _public enumerator_ `EnabledInGameAndSimulate`
- L44 _public enumerator_ `EnabledInGame`
- L45 _public enumerator_ `EnabledInSimulate`
- L46 _public enumerator_ `Disabled`
- L47 _public enumerator_ `Hidden`

#### class `IGameplayDebugger`  
`class IGameplayDebugger : public IModuleInterface`  
_L50-84_
- inherits: `IModuleInterface`
- L54 _public prototype_ `DECLARE_DELEGATE_RetVal(TSharedRef<class FGameplayDebuggerCategory>, FOnGetCategory);`
- L55 _public prototype_ `DECLARE_DELEGATE_RetVal(TSharedRef<class FGameplayDebuggerExtension>, FOnGetExtension);`
- L63 _public function_ `static inline IGameplayDebugger& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L73 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L78 _public prototype_ `virtual void RegisterCategory(FName CategoryName, FOnGetCategory MakeInstanceDelegate, EGameplayDebuggerCategoryState CategoryState = EGameplayDebuggerCategoryState::Disabled, int32 SlotIdx = INDEX_NONE) = 0;`
- L79 _public prototype_ `virtual void UnregisterCategory(FName CategoryName) = 0;`
- L80 _public prototype_ `virtual void NotifyCategoriesChanged() = 0;`
- L81 _public prototype_ `virtual void RegisterExtension(FName ExtensionName, FOnGetExtension MakeInstanceDelegate) = 0;`
- L82 _public prototype_ `virtual void UnregisterExtension(FName ExtensionName) = 0;`
- L83 _public prototype_ `virtual void NotifyExtensionsChanged() = 0;`

#### Free symbols / members of external scopes

- L54 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedRef<class FGameplayDebuggerCategory>, FOnGetCategory);`
- L55 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedRef<class FGameplayDebuggerExtension>, FOnGetExtension);`

### `Source/Runtime/GameplayDebugger/Public/GameplayDebuggerAddonBase.h` (Public)


#### class `FGameplayDebuggerAddonBase`  
`class FGameplayDebuggerAddonBase : public TSharedFromThis<FGameplayDebuggerAddonBase>`  
_L13-108_
- inherits: `TSharedFromThis<FGameplayDebuggerAddonBase>`
- L17 _public prototype_ `virtual ~FGameplayDebuggerAddonBase() = default;`
- L19 _public function_ `int32 GetNumInputHandlers() const`
- L20 _public function_ `FGameplayDebuggerInputHandler& GetInputHandler(int32 HandlerId)`
- L21 _public prototype_ `FString GetInputHandlerDescription(int32 HandlerId) const;`
- L22 _public prototype_ `UWorld* GetWorldFromReplicator() const;`
- L24 _public prototype_ `UWorld* GetDataWorld(const APlayerController* OwnerPC, const AActor* DebugActor) const;` — Returns the first non-null world associated with, in order: OwnerPC, DebugActor, AGameplayDebuggerCategoryReplicator owner
- L27 _public prototype_ `virtual void OnGameplayDebuggerActivated();` — [ALL] called when gameplay debugger is activated
- L30 _public prototype_ `virtual void OnGameplayDebuggerDeactivated();` — [ALL] called when gameplay debugger is deactivated
- L33 _public prototype_ `static bool IsSimulateInEditor();` — check if simulate in editor mode is active
- L38 _protected prototype_ `AActor* FindLocalDebugActor() const;` — tries to find selected actor in local world
- L41 _protected prototype_ `AGameplayDebuggerCategoryReplicator* GetReplicator() const;` — returns replicator actor
- L45 _protected function_ `template<class UserClass> bool BindKeyPress(FName KeyName, UserClass* KeyHandlerObject, typename FGameplayDebuggerInputHandler::FHandler::TMethodPtr< UserClass > KeyHandlerFunc, EGameplayDebuggerInputMode InputMode = EGameplayDebuggerInputMode::Local)` — creates new key binding handler: single key press
- L63 _protected function_ `template<class UserClass> bool BindKeyPress(FName KeyName, FGameplayDebuggerInputModifier KeyModifer, UserClass* KeyHandlerObject, typename FGameplayDebuggerInputHandler::FHandler::TMethodPtr< UserClass > KeyHandlerFunc, EGameplayDebuggerInputMode InputMode = EGameplayDebuggerInputMode::Local)` — creates new key binding handler: key press with modifiers
- L82 _protected function_ `template<class UserClass> bool BindKeyPress(const FGameplayDebuggerInputHandlerConfig& InputConfig, UserClass* KeyHandlerObject, typename FGameplayDebuggerInputHandler::FHandler::TMethodPtr< UserClass > KeyHandlerFunc, EGameplayDebuggerInputMode InputMode = EGameplayDebuggerInputMode::Local)` — creates new key binding handler: customizable key press, stored in config files
- L104 _private member_ `TArray<FGameplayDebuggerInputHandler> InputHandlers;` — list of input handlers
- L107 _private member_ `TWeakObjectPtr<AGameplayDebuggerCategoryReplicator> RepOwner;` — replicator actor

### `Source/Runtime/GameplayDebugger/Public/GameplayDebuggerAddonManager.h` (Public)


#### struct `FGameplayDebuggerCategoryInfo`  
`struct FGameplayDebuggerCategoryInfo`  
_L17-23_
- L19 _public member_ `IGameplayDebugger::FOnGetCategory MakeInstanceDelegate;`
- L20 _public member_ `EGameplayDebuggerCategoryState DefaultCategoryState;`
- L21 _public member_ `EGameplayDebuggerCategoryState CategoryState;`
- L22 _public member_ `int32 SlotIdx;`

#### struct `FGameplayDebuggerExtensionInfo`  
`struct FGameplayDebuggerExtensionInfo`  
_L25-30_
- L27 _public member_ `IGameplayDebugger::FOnGetExtension MakeInstanceDelegate;`
- L28 _public member_ `uint32 bDefaultEnabled : 1;`
- L29 _public member_ `uint32 bEnabled : 1;`

#### class `FGameplayDebuggerAddonManager`  
`class FGameplayDebuggerAddonManager`  
_L32-97_
- L35 _public prototype_ `FGameplayDebuggerAddonManager();`
- L38 _public prototype_ `void RegisterCategory(FName CategoryName, IGameplayDebugger::FOnGetCategory MakeInstanceDelegate, EGameplayDebuggerCategoryState CategoryState, int32 SlotIdx);` — adds new category to managed collection
- L41 _public prototype_ `void UnregisterCategory(FName CategoryName);` — removes category from managed collection
- L44 _public prototype_ `void NotifyCategoriesChanged();` — notify about change in known categories
- L47 _public prototype_ `void CreateCategories(AGameplayDebuggerCategoryReplicator& Owner, TArray<TSharedRef<FGameplayDebuggerCategory> >& CategoryObjects);` — creates new category objects for all known types
- L50 _public prototype_ `void RegisterExtension(FName ExtensionName, IGameplayDebugger::FOnGetExtension MakeInstanceDelegate);` — adds new extension to managed collection
- L53 _public prototype_ `void UnregisterExtension(FName ExtensionName);` — removes extension from managed collection
- L56 _public prototype_ `void NotifyExtensionsChanged();` — notify about change in known extensions
- L59 _public prototype_ `void CreateExtensions(AGameplayDebuggerCategoryReplicator& Replicator, TArray<TSharedRef<FGameplayDebuggerExtension> >& ExtensionObjects);` — creates new extension objects for all known types
- L62 _public prototype_ `void UpdateFromConfig();` — refresh category and extension data from config
- L65 _public function_ `const TArray<TArray<int32> >& GetSlotMap() const` — get slot-Id map
- L68 _public function_ `const TArray<FString>& GetSlotNames() const` — get slot-Name map
- L71 _public function_ `int32 GetNumVisibleCategories() const` — get number of visible categories
- L74 _public prototype_ `static FGameplayDebuggerAddonManager& GetCurrent();` — singleton accessor
- L77 _public member_ `FOnGameplayDebuggerAddonEvent OnCategoriesChanged;` — event called when CategoryMap changes
- L80 _public member_ `FOnGameplayDebuggerAddonEvent OnExtensionsChanged;` — event called when ExtensionMap changes
- L84 _private member_ `TMap<FName, FGameplayDebuggerExtensionInfo> ExtensionMap;` — map of all known extensions indexed by their names
- L87 _private member_ `TMap<FName, FGameplayDebuggerCategoryInfo> CategoryMap;` — map of all known categories indexed by their names
- L90 _private member_ `TArray<TArray<int32> > SlotMap;` — list of all slots and their categories Ids
- L93 _private member_ `TArray<FString> SlotNames;` — list of slot names
- L96 _private member_ `int32 NumVisibleCategories;` — number of categories, excluding hidden ones

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnGameplayDebuggerAddonEvent);`
- L12 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnGameplayDebuggerAddonEvent);`

### `Source/Runtime/GameplayDebugger/Public/GameplayDebuggerCategory.h` (Public)


#### class `FGameplayDebuggerCategory`  
`class FGameplayDebuggerCategory : public FGameplayDebuggerAddonBase`  
_L48-212_
- inherits: `FGameplayDebuggerAddonBase`
- desc: Single category of visual debugger tool
- L52 _public prototype_ `FGameplayDebuggerCategory();`
- L53 _public prototype_ `virtual ~FGameplayDebuggerCategory();`
- L56 _public prototype_ `virtual void CollectData(APlayerController* OwnerPC, AActor* DebugActor);` — [AUTH] gather data for replication
- L59 _public prototype_ `virtual void DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext);` — [LOCAL] draw collected data
- L62 _public prototype_ `virtual FDebugRenderSceneProxy* CreateDebugSceneProxy(const UPrimitiveComponent* InComponent, FDebugDrawDelegateHelper*& OutDelegateHelper);` — [LOCAL] creates a scene proxy for more advanced debug rendering
- L65 _public prototype_ `virtual void OnDataPackReplicated(int32 DataPackId);` — [LOCAL] called after successful replication of entire data pack to client
- L68 _public prototype_ `void AddTextLine(const FString& TextLine);` — [AUTH] adds line of text tagged with {color} to replicated data
- L71 _public prototype_ `void AddShape(const FGameplayDebuggerShape& Shape);` — [AUTH] adds shape to replicated data
- L74 _public prototype_ `void DrawCategory(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext);` — [LOCAL] draw category
- L77 _public function_ `bool ShouldDrawCategory(bool bHasDebugActor) const` — [LOCAL] check if category should be drawn
- L80 _public function_ `bool ShouldDrawReplicationStatus() const` — [LOCAL] check if data pack replication status
- L83 _public function_ `FName GetCategoryName() const` — [ALL] get name of category
- L86 _public function_ `bool IsCategoryHeaderVisible() const` — [ALL] check if category header should be drawn
- L89 _public function_ `bool IsCategoryEnabled() const` — [ALL] check if category is enabled
- L92 _public function_ `bool IsCategoryLocal() const` — [ALL] check if category is local (present data)
- L95 _public function_ `bool IsCategoryAuth() const` — [ALL] check if category has authority (collects data)
- L98 _public function_ `bool ShouldCollectDataOnClient() const` — [LOCAL]
- L100 _public function_ `int32 GetNumDataPacks() const`
- L101 _public function_ `float GetDataPackProgress(int32 DataPackId) const`
- L102 _public function_ `bool IsDataPackReplicating(int32 DataPackId) const`
- L103 _public function_ `FGameplayDebuggerDataPack::FHeader GetDataPackHeaderCopy(int32 DataPackId) const`
- L106 _public function_ `TArray<FString> GetReplicatedLinesCopy() const` — temporary functions for compatibility, will be removed soon
- L107 _public function_ `TArray<FGameplayDebuggerShape> GetReplicatedShapesCopy() const`
- L118 _protected prototype_ `bool GetViewPoint(const APlayerController* OwnerPC, FVector& OutViewLocation, FVector& OutViewDirection) const;` — Returns view location and direction from replicated data if available or will extract it from the provided player controller. The replicated data is used first since it might be provided from a detached camera. @return whether OutViewLocation and OutViewDirection were assigned to valid values @note Method is expected to always return valid outputs if valid controller is provided. Otherwise it depends if the view information has been replicated before the methods gets called.
- L124 _protected prototype_ `static bool IsLocationInViewCone(const FVector& ViewLocation, const FVector& ViewDirection, const FVector& TargetLocation);` — Indicates if a given location is within a vision cone built from provided view location and direction based on MaxViewDistance and MaxViewAngle from GameplayDebuggerUserSettings
- L127 _protected prototype_ `void MarkDataPackDirty(int32 DataPackId);` — [AUTH] marks data pack as needing replication
- L130 _protected prototype_ `void MarkRenderStateDirty();` — [LOCAL] requests new scene proxy
- L133 _protected prototype_ `FString GetSceneProxyViewFlag() const;` — [LOCAL] preferred view flag for creating scene proxy
- L139 _protected function_ `template<typename T> int32 SetDataPackReplication(T* DataPackAddr, EGameplayDebuggerDataPack Flags = EGameplayDebuggerDataPack::ResetOnTick)` — [ALL] sets up DataPack replication, needs address of property holding data, DataPack's struct must define Serialize(FArchive& Ar) function returns DataPackId
- L152 _protected function_ `void ForceImmediateCollect()` — [AUTH] force data collection on next update
- L155 _protected prototype_ `void ResetReplicatedData();` — [ALL] Clears out accumulated replicated data.
- L158 _protected member_ `float CollectDataInterval;` — update interval, 0 = each tick
- L161 _protected member_ `uint32 bShowDataPackReplication : 1;` — include data pack replication details in drawn messages
- L164 _protected member_ `uint32 bShowUpdateTimer : 1;` — include remaining time to next data collection in drawn messages
- L167 _protected member_ `uint32 bShowCategoryName : 1;` — include category name in drawn messages
- L170 _protected member_ `uint32 bShowOnlyWithDebugActor : 1;` — draw category only when DebugActor is present
- L178 _protected member_ `uint32 bAllowLocalDataCollection : 1;` — False by default. If set to True will make data collection functions work on Local categories as well. Note that in client-server setting the data is still being replicated over from the server as well, and data collection on the client can also be used to annotate the incoming data. If this is undesired you need to call ResetReplicatedData before gathering the client-side data.
- L187 _private member_ `uint32 bIsLocal : 1;` — if set, this category object can display data
- L190 _private member_ `uint32 bHasAuthority : 1;` — if set, this category object can collect data
- L193 _private member_ `uint32 bIsEnabled : 1;` — if set, this category object is enabled in debugger
- L196 _private member_ `int32 CategoryId;` — Id number assigned to this category object
- L199 _private member_ `double LastCollectDataTime;` — timestamp of last update
- L202 _private member_ `FName CategoryName;` — name of debugger category (auto assigned during category registration)
- L205 _private member_ `TArray<FString> ReplicatedLines;` — list of replicated text lines, will be reset before CollectData call on AUTH
- L208 _private member_ `TArray<FGameplayDebuggerShape> ReplicatedShapes;` — list of replicated shapes, will be reset before CollectData call on AUTH
- L211 _private member_ `TArray<FGameplayDebuggerDataPack> ReplicatedDataPacks;` — list of replicated data packs

#### Free symbols / members of external scopes

- L145 _function_ `NewDataPack.ResetDelegate.BindLambda([=] { *DataPackAddr = T(); });` (scope `FGameplayDebuggerCategory::SetDataPackReplication`)

### `Source/Runtime/GameplayDebugger/Public/GameplayDebuggerCategoryReplicator.h` (Public)


#### struct `FGameplayDebuggerDataPackRPCParams`  
`struct FGameplayDebuggerDataPackRPCParams`  
_L21-36_
- reflection: `USTRUCT()`
- desc: Struct used to send the DataPackPackets as RPC`s instead of using the CustomDeltaNetSerializer.
- L26 _public member_ `FName CategoryName;` — `UPROPERTY()`
- L29 _public member_ `int32 DataPackIdx = 0;` — `UPROPERTY()`
- L32 _public member_ `FGameplayDebuggerDataPackHeader Header;` — `UPROPERTY()`
- L35 _public member_ `TArray<uint8> Data;` — `UPROPERTY()`

#### struct `FGameplayDebuggerCategoryData`  
`struct FGameplayDebuggerCategoryData`  
_L39-58_
- reflection: `USTRUCT()`
- L44 _public member_ `FName CategoryName;` — `UPROPERTY()`
- L47 _public member_ `TArray<FString> TextLines;` — `UPROPERTY()`
- L50 _public member_ `TArray<FGameplayDebuggerShape> Shapes;` — `UPROPERTY()`
- L54 _public member_ `TArray<FGameplayDebuggerDataPackHeader> DataPacks;` — `UPROPERTY(NotReplicated)` — Either replicated using the NetDeltaSerialize or alternatively as regular RPC`s
- L57 _public member_ `bool bIsEnabled = false;` — `UPROPERTY()`

#### struct `FGameplayDebuggerNetPack`  
`struct FGameplayDebuggerNetPack`  
_L61-81_
- reflection: `USTRUCT()`
- L66 _public member_ `TObjectPtr<AGameplayDebuggerCategoryReplicator> Owner;` — `UPROPERTY(NotReplicated)`
- L68 _public function_ `FGameplayDebuggerNetPack() : Owner(nullptr)`
- L70 _public prototype_ `bool NetDeltaSerialize(FNetDeltaSerializeInfo & DeltaParms);`
- L71 _public prototype_ `void OnCategoriesChanged();`
- L75 _public prototype_ `void PopulateFromOwner();` — When using Iris we cannot use the same appoach as the current NetSerializeDelta as it does polling of data and also modifies data outside of the replicated state during serialization which is not allowed when using iris. Therefore we need explicit methods to populate the state from the owner and to apply it to the owner which can be invoked before and after serialization as needed.
- L76 _public prototype_ `void ApplyToOwner();`
- L80 _private member_ `TArray<FGameplayDebuggerCategoryData> SavedData;` — `UPROPERTY()`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FGameplayDebuggerNetPack> : public TStructOpsTypeTraitsBase2<FGameplayDebuggerNetPack>`  
_L84-90_
- inherits: `TStructOpsTypeTraitsBase2<FGameplayDebuggerNetPack>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L87-89_

#### struct `FGameplayDebuggerDebugActor`  
`struct FGameplayDebuggerDebugActor`  
_L93-105_
- reflection: `USTRUCT()`
- L98 _public member_ `TWeakObjectPtr<AActor> Actor;` — `UPROPERTY()`
- L101 _public member_ `FName ActorName;` — `UPROPERTY()`
- L104 _public member_ `int16 SyncCounter = 0;` — `UPROPERTY()`

#### struct `FGameplayDebuggerVisLogSync`  
`struct FGameplayDebuggerVisLogSync`  
_L108-114_
- reflection: `USTRUCT()`
- L113 _public member_ `FString DeviceIDs;` — `UPROPERTY()`

#### class `AGameplayDebuggerCategoryReplicator`  
`class AGameplayDebuggerCategoryReplicator : public AActor`  
_L119-317_
- reflection: `UCLASS(NotBlueprintable, NotBlueprintType, notplaceable, noteditinlinenew, hidedropdown, Transient, MinimalAPI)`
- inherits: `AActor`
- L123 _private prototype_ `virtual class UNetConnection* GetNetConnection() const override;`
- L124 _private prototype_ `virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;`
- L127 _protected prototype_ `virtual void BeginPlay() override;`
- L129 _protected prototype_ `virtual void OnReplicationStartedForIris(const FOnReplicationStartedParams&) override;`
- L131 _protected prototype_ `virtual const AActor* GetNetOwner() const override;`
- L132 _protected prototype_ `virtual UPlayer* GetNetOwningPlayer() override;`
- L133 _protected prototype_ `virtual UPlayer* GetNetOwningPlayerAnyRole() override;`
- L136 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L137 _public prototype_ `virtual void TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;`
- L138 _public prototype_ `virtual void PostNetReceive() override;`
- L140 _public prototype_ `virtual void PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker) override;`
- L143 _public prototype_ `void SetReplicatorOwner(APlayerController* InOwnerPC);` — [AUTH] set new owner
- L144 _public member_ `static FNotifyGameplayDebuggerOwnerChange NotifyDebuggerOwnerChange;`
- L147 _public prototype_ `void SetEnabled(bool bEnable);` — [ALL] set replicator state
- L150 _public prototype_ `void SetCategoryEnabled(int32 CategoryId, bool bEnable);` — [ALL] set category state
- L153 _public prototype_ `void SetDebugActor(AActor* Actor, bool bSelectInEditor = false);` — [ALL] set actor for debugging
- L156 _public prototype_ `void SetViewPoint(const FVector& InViewLocation, const FVector& InViewDirection);` — [ALL] set view matrix that should be used for culling and picking instead of the associated controller view point
- L159 _public function_ `bool IsViewPointSet() const` — Indicates that a view matrix has been set for culling and picking instead of the associated controller view point
- L162 _public prototype_ `void ResetViewPoint();` — [ALL] reset view matrix that should be used for culling and picking to revert on the associated controller view point
- L165 _public prototype_ `void SendCategoryInputEvent(int32 CategoryId, int32 HandlerId);` — [ALL] send input event to category
- L168 _public prototype_ `void SendExtensionInputEvent(int32 ExtensionId, int32 HandlerId);` — [ALL] send input event to extension
- L171 _public prototype_ `void CollectCategoryData(bool bForce = false);` — [AUTH] starts data collection
- L174 _public function_ `AActor* GetDebugActor() const` — get current debug actor
- L177 _public function_ `FName GetDebugActorName() const` — get name of debug actor
- L180 _public function_ `int16 GetDebugActorCounter() const` — get sync counter, increased with every change of DebugActor
- L183 _public prototype_ `bool GetViewPoint(FVector& OutViewLocation, FVector& OutViewDirection) const;` — get view point information
- L185 _public function_ `const FGameplayDebuggerVisLogSync& GetVisLogSyncData() const`
- L188 _public function_ `TObjectPtr<APlayerController> GetReplicationOwner() const` — get player controller owning this replicator
- L191 _public function_ `bool IsEnabled() const` — get replicator state
- L194 _public function_ `bool IsEditorWorldReplicator() const` — returns true if this replicator has been created for an editor world
- L197 _public prototype_ `bool IsCategoryEnabled(int32 CategoryId) const;` — get category state
- L200 _public function_ `bool HasDebugActor() const` — check if debug actor was selected
- L203 _public function_ `int32 GetNumCategories() const` — get category count
- L206 _public function_ `int32 GetNumExtensions() const` — get extension count
- L209 _public function_ `TSharedRef<FGameplayDebuggerCategory> GetCategory(int32 CategoryId) const` — get category object
- L212 _public function_ `TSharedRef<FGameplayDebuggerExtension> GetExtension(int32 ExtensionId) const` — get category object
- L215 _public function_ `bool IsLocal() const` — returns true if object was created for local player (client / standalone)
- L218 _public prototype_ `void InitForEditor();`
- L223 _protected prototype_ `void OnRep_ReplicatedData();` — `UFUNCTION()`
- L229 _protected member_ `TObjectPtr<APlayerController> OwnerPC;` — `UPROPERTY(Replicated)`
- L232 _protected member_ `bool bIsEnabled;` — `UPROPERTY(Replicated)`
- L235 _protected member_ `FGameplayDebuggerNetPack ReplicatedData;` — `UPROPERTY(Replicated, ReplicatedUsing=OnRep_ReplicatedData)`
- L238 _protected member_ `FGameplayDebuggerDebugActor DebugActor;` — `UPROPERTY(Replicated)`
- L241 _protected member_ `FGameplayDebuggerVisLogSync VisLogSync;` — `UPROPERTY(Replicated)`
- L245 _protected member_ `TObjectPtr<UGameplayDebuggerRenderingComponent> RenderingComp;` — `UPROPERTY()` — rendering component needs to attached to some actor, and this is as good as any
- L248 _protected member_ `TArray<TSharedRef<FGameplayDebuggerCategory> > Categories;` — category objects
- L251 _protected member_ `TArray<TSharedRef<FGameplayDebuggerExtension> > Extensions;` — extension objects
- L253 _protected member_ `TOptional<FVector> ViewLocation;`
- L254 _protected member_ `TOptional<FVector> ViewDirection;`
- L256 _protected member_ `uint32 bIsEnabledLocal : 1;`
- L257 _protected member_ `uint32 bHasAuthority : 1;`
- L258 _protected member_ `uint32 bIsLocal : 1;`
- L259 _protected member_ `uint32 bIsEditorWorldReplicator : 1;`
- L260 _protected member_ `uint32 bSendDataPacksUsingRPC : 1;`
- L263 _protected prototype_ `void OnCategoriesChanged();` — notify about changes in known category set
- L266 _protected prototype_ `void OnExtensionsChanged();` — notify about changes in known extensions set
- L269 _protected prototype_ `void NotifyCategoriesToolState(bool bIsActive);` — send notifies to all categories about current tool state
- L272 _protected prototype_ `void NotifyExtensionsToolState(bool bIsActive);` — send notifies to all categories about current tool state
- L275 _protected prototype_ `void ServerSetEnabled(bool bEnable);` — `UFUNCTION(Server, Reliable, WithValidation, meta = (CallInEditor = "true"))`
- L278 _protected prototype_ `void ServerSetDebugActor(AActor* Actor, bool bSelectInEditor);` — `UFUNCTION(Server, Reliable, WithValidation, meta = (CallInEditor = "true"))`
- L281 _protected prototype_ `void ServerSetViewPoint(const FVector& InViewLocation, const FVector& InViewDirection);` — `UFUNCTION(Server, Reliable, WithValidation, meta = (CallInEditor = "true"))`
- L284 _protected prototype_ `void ServerResetViewPoint();` — `UFUNCTION(Server, Reliable, WithValidation, meta = (CallInEditor = "true"))`
- L288 _protected prototype_ `void ServerSetCategoryEnabled(int32 CategoryId, bool bEnable);` — `UE_DEPRECATED(5.8, "ServerSetCategoryEnabled by CategoryId does not work when server/client mismatch indices, use ServerSetCategoryNameEnabled")` — `UFUNCTION(Server, Reliable, WithValidation, meta = (CallInEditor = "true"))`
- L291 _protected prototype_ `void ServerSetCategoryNameEnabled(FName CategoryName, bool bEnable);` — `UFUNCTION(Server, Reliable, WithValidation, meta = (CallInEditor = "true"))`
- L296 _protected prototype_ `void ServerSendCategoryInputEvent(int32 CategoryId, int32 HandlerId);` — `UE_DEPRECATED(5.8, "ServerSendCategoryInputEvent by CategoryId does not work when server/client mismatch indices, use ServerSendCategoryNameInputEvent")` — `UFUNCTION(Server, Reliable, WithValidation, meta = (CallInEditor = "true"))` — helper function for replicating input for category handlers
- L299 _protected prototype_ `void ServerSendCategoryNameInputEvent(FName CategoryName, int32 HandlerId);` — `UFUNCTION(Server, Reliable, WithValidation, meta = (CallInEditor = "true"))`
- L303 _protected prototype_ `void ServerSendExtensionInputEvent(int32 ExtensionId, int32 HandlerId);` — `UFUNCTION(Server, Reliable, WithValidation, meta = (CallInEditor = "true"))` — helper function for replicating input for extension handlers
- L307 _protected prototype_ `void ClientDataPackPacket(const FGameplayDebuggerDataPackRPCParams& Params);` — `UFUNCTION(Client, Reliable)` — helper function for optionally sending DataPackPackets as RPC's
- L310 _protected prototype_ `void OnReceivedDataPackPacket(int32 CategoryId, int32 DataPackId, const FGameplayDebuggerDataPack& DataPacket);` — [LOCAL] notify from CategoryData replication
- L313 _protected prototype_ `void Init();` — called both from BeginPlay and InitForEditor to setup instance's internal
- L316 _private prototype_ `void SendDataPackPacket(FName CategoryName, int32 DataPackIdx, FGameplayDebuggerDataPack& DataPack);`

#### Free symbols / members of external scopes

- L88 _enumerator_ `WithNetDeltaSerializer = true` (scope `TStructOpsTypeTraits::__anona2d0ecf90103`)
- L116 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FNotifyGameplayDebuggerOwnerChange, AGameplayDebuggerCategoryReplicator*, APlayerController* );`
- L116 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FNotifyGameplayDebuggerOwnerChange, AGameplayDebuggerCategoryReplicator*, APlayerController* );`

### `Source/Runtime/GameplayDebugger/Public/GameplayDebuggerCompat.h` (Public)


#### class `FGameplayDebuggerCompat`  
`class FGameplayDebuggerCompat : public FSelfRegisteringExec, public GameplayDebugger`  
_L16-74_
- inherits: `FSelfRegisteringExec,GameplayDebugger`
- L20 _public prototype_ `virtual void StartupModule() override;`
- L21 _public prototype_ `virtual void ShutdownModule() override;`
- L24 _public prototype_ `void WorldAdded(UWorld* InWorld);`
- L25 _public prototype_ `void WorldDestroyed(UWorld* InWorld);`
- L27 _public prototype_ `void OnLevelActorAdded(AActor* InActor);`
- L28 _public prototype_ `void OnLevelActorDeleted(AActor* InActor);`
- L29 _public prototype_ `TSharedRef<FExtender> OnExtendLevelEditorViewMenu(const TSharedRef<FUICommandList> CommandList);`
- L30 _public prototype_ `void CreateSnappingOptionsMenu(FMenuBuilder& Builder);`
- L31 _public prototype_ `void CreateSettingSubMenu(FMenuBuilder& Builder);`
- L32 _public prototype_ `void HandleSettingChanged(FName PropertyName);`
- L35 _public prototype_ `TArray<TWeakObjectPtr<AGameplayDebuggingReplicator> >& GetAllReplicators(UWorld* InWorld);`
- L36 _public prototype_ `void AddReplicator(UWorld* InWorld, AGameplayDebuggingReplicator* InReplicator);`
- L37 _public prototype_ `void RemoveReplicator(UWorld* InWorld, AGameplayDebuggingReplicator* InReplicator);`
- L40 _public prototype_ `virtual bool Exec(UWorld* Inworld, const TCHAR* Cmd, FOutputDevice& Ar) override;`
- L44 _private prototype_ `virtual bool CreateGameplayDebuggerForPlayerController(APlayerController* PlayerController) override;`
- L45 _private prototype_ `virtual bool IsGameplayDebuggerActiveForPlayerController(APlayerController* PlayerController) override;`
- L47 _private prototype_ `bool DoesGameplayDebuggingReplicatorExistForPlayerController(APlayerController* PlayerController);`
- L49 _private member_ `TMap<TWeakObjectPtr<UWorld>, TArray<TWeakObjectPtr<AGameplayDebuggingReplicator> > > AllReplicatorsPerWorlds;`
- L52 _public prototype_ `virtual void RegisterCategory(FName CategoryName, FOnGetCategory MakeInstanceDelegate, EGameplayDebuggerCategoryState CategoryState = EGameplayDebuggerCategoryState::Disabled, int32 SlotIdx = INDEX_NONE);`
- L53 _public prototype_ `virtual void UnregisterCategory(FName CategoryName);`
- L54 _public prototype_ `virtual void NotifyCategoriesChanged();`
- L55 _public prototype_ `virtual void RegisterExtension(FName ExtensionName, IGameplayDebugger::FOnGetExtension MakeInstanceDelegate);`
- L56 _public prototype_ `virtual void UnregisterExtension(FName ExtensionName);`
- L57 _public prototype_ `virtual void NotifyExtensionsChanged();`
- L58 _public prototype_ `virtual void UseNewGameplayDebugger();`
- L60 _public prototype_ `void StartupNewDebugger();`
- L61 _public prototype_ `void ShutdownNewDebugger();`
- L62 _public prototype_ `AGameplayDebuggerPlayerManager& GetPlayerManager(UWorld* World);`
- L63 _public prototype_ `void OnWorldInitialized(UWorld* World, const UWorld::InitializationValues IVS);`
- L65 _public member_ `bool bNewDebuggerEnabled;`
- L66 _public member_ `FGameplayDebuggerAddonManager AddonManager;`
- L67 _public member_ `TMap<TWeakObjectPtr<UWorld>, TWeakObjectPtr<AGameplayDebuggerPlayerManager>> PlayerManagers;`
- L72 _private member_ `FLevelEditorModule::FLevelEditorMenuExtender ViewMenuExtender;`

### `Source/Runtime/GameplayDebugger/Public/GameplayDebuggerConfig.h` (Public)


#### enum `EGameplayDebuggerOverrideMode`  
`enum class EGameplayDebuggerOverrideMode : uint8`  
_L23-28_
- reflection: `UENUM()`
- L25 _public enumerator_ `Enable`
- L26 _public enumerator_ `Disable`
- L27 _public enumerator_ `UseDefault`

#### struct `FGameplayDebuggerInputConfig`  
`struct FGameplayDebuggerInputConfig`  
_L31-58_
- reflection: `USTRUCT()`
- L35 _public function_ `FGameplayDebuggerInputConfig() : bModShift(false) , bModCtrl(false) , bModAlt(false) , bModCmd(false)`
- L42 _public member_ `FString ConfigName;` — `UPROPERTY(VisibleAnywhere, Category = Input)`
- L45 _public member_ `FKey Key;` — `UPROPERTY(EditAnywhere, Category = Input)`
- L48 _public member_ `uint32 bModShift : 1;` — `UPROPERTY(EditAnywhere, Category = Input)`
- L51 _public member_ `uint32 bModCtrl : 1;` — `UPROPERTY(EditAnywhere, Category = Input)`
- L54 _public member_ `uint32 bModAlt : 1;` — `UPROPERTY(EditAnywhere, Category = Input)`
- L57 _public member_ `uint32 bModCmd : 1;` — `UPROPERTY(EditAnywhere, Category = Input)`

#### struct `FGameplayDebuggerCategoryConfig`  
`struct FGameplayDebuggerCategoryConfig`  
_L61-93_
- reflection: `USTRUCT()`
- L66 _public member_ `FString CategoryName;` — `UPROPERTY(VisibleAnywhere, Category = Settings)`
- L69 _public member_ `int32 SlotIdx;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (EditCondition = "bOverrideSlotIdx", ClampMin = -1, ClampMax = 9, UIMin = -1, UIMax = 9))`
- L72 _public member_ `EGameplayDebuggerOverrideMode ActiveInGame;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L75 _public member_ `EGameplayDebuggerOverrideMode ActiveInSimulate;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L78 _public member_ `EGameplayDebuggerOverrideMode Hidden;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L81 _public member_ `uint32 bOverrideSlotIdx : 1;` — `UPROPERTY(EditAnywhere, Category = Settings, AdvancedDisplay)`
- L84 _public member_ `TArray<FGameplayDebuggerInputConfig> InputHandlers;` — `UPROPERTY(EditAnywhere, Category = Settings, EditFixedSize)`
- L86 _public function_ `FGameplayDebuggerCategoryConfig() : SlotIdx(0) , ActiveInGame(EGameplayDebuggerOverrideMode::UseDefault) , ActiveInSimulate(EGameplayDebuggerOverrideMode::UseDefault) , Hidden(EGameplayDebuggerOverrideMode::UseDefault) , bOverrideSlotIdx(false)`

#### struct `FGameplayDebuggerExtensionConfig`  
`struct FGameplayDebuggerExtensionConfig`  
_L96-110_
- reflection: `USTRUCT()`
- L101 _public member_ `FString ExtensionName;` — `UPROPERTY(VisibleAnywhere, Category = Settings)`
- L104 _public member_ `EGameplayDebuggerOverrideMode UseExtension;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L107 _public member_ `TArray<FGameplayDebuggerInputConfig> InputHandlers;` — `UPROPERTY(EditAnywhere, Category = Settings, EditFixedSize)`
- L109 _public function_ `FGameplayDebuggerExtensionConfig() : UseExtension(EGameplayDebuggerOverrideMode::UseDefault)`

#### class `UGameplayDebuggerConfig`  
`class UGameplayDebuggerConfig : public UObject`  
_L113-222_
- reflection: `UCLASS(config = Engine, defaultconfig, MinimalAPI)`
- inherits: `UObject`
- L119 _private member_ `FKey ActivationKey;` — `UPROPERTY(config, EditAnywhere, Category = Input)` — key used to activate visual debugger tool
- L123 _private member_ `FKey CategoryRowNextKey;` — `UPROPERTY(config, EditAnywhere, Category = Input)` — select next category row
- L127 _private member_ `FKey CategoryRowPrevKey;` — `UPROPERTY(config, EditAnywhere, Category = Input)` — select previous category row
- L131 _private member_ `FKey CategorySlot0;` — `UPROPERTY(config, EditAnywhere, Category = Input)` — select category slot 0
- L135 _private member_ `FKey CategorySlot1;` — `UPROPERTY(config, EditAnywhere, Category = Input)` — select category slot 1
- L139 _private member_ `FKey CategorySlot2;` — `UPROPERTY(config, EditAnywhere, Category = Input)` — select category slot 2
- L143 _private member_ `FKey CategorySlot3;` — `UPROPERTY(config, EditAnywhere, Category = Input)` — select category slot 3
- L147 _private member_ `FKey CategorySlot4;` — `UPROPERTY(config, EditAnywhere, Category = Input)` — select category slot 4
- L151 _private member_ `FKey CategorySlot5;` — `UPROPERTY(config, EditAnywhere, Category = Input)` — select category slot 5
- L155 _private member_ `FKey CategorySlot6;` — `UPROPERTY(config, EditAnywhere, Category = Input)` — select category slot 6
- L159 _private member_ `FKey CategorySlot7;` — `UPROPERTY(config, EditAnywhere, Category = Input)` — select category slot 7
- L163 _private member_ `FKey CategorySlot8;` — `UPROPERTY(config, EditAnywhere, Category = Input)` — select category slot 8
- L167 _private member_ `FKey CategorySlot9;` — `UPROPERTY(config, EditAnywhere, Category = Input)` — select category slot 9
- L171 _private member_ `float DebugCanvasPaddingLeft;` — `UPROPERTY(config, EditAnywhere, Category = Display)` — additional canvas padding: left
- L175 _private member_ `float DebugCanvasPaddingRight;` — `UPROPERTY(config, EditAnywhere, Category = Display)` — additional canvas padding: right
- L179 _private member_ `float DebugCanvasPaddingTop;` — `UPROPERTY(config, EditAnywhere, Category = Display)` — additional canvas padding: top
- L183 _private member_ `float DebugCanvasPaddingBottom;` — `UPROPERTY(config, EditAnywhere, Category = Display)` — additional canvas padding: bottom
- L187 _private member_ `bool bDebugCanvasEnableTextShadow;` — `UPROPERTY(config, EditAnywhere, Category = Display)` — enable text shadow by default
- L190 _private member_ `TArray<FGameplayDebuggerCategoryConfig> Categories;` — `UPROPERTY(config, EditAnywhere, Category = AddOns, EditFixedSize)`
- L193 _private member_ `TArray<FGameplayDebuggerExtensionConfig> Extensions;` — `UPROPERTY(config, EditAnywhere, Category = AddOns, EditFixedSize)`
- L196 _private prototype_ `void UpdateCategoryConfig(const FName CategoryName, int32& SlotIdx, uint8& CategoryState);` — updates entry in Categories array and modifies category creation params
- L199 _private prototype_ `void UpdateCategoryInputConfig(const FName CategoryName, const FName InputName, FName& KeyName, FGameplayDebuggerInputModifier& KeyModifier);` — updates entry in Categories array and modifies input binding params
- L202 _private prototype_ `void UpdateExtensionConfig(const FName ExtensionName, uint8& UseExtension);` — updates entry in Extensions array and modifies extension creation params
- L205 _private prototype_ `void UpdateExtensionInputConfig(const FName ExtensionName, const FName InputName, FName& KeyName, FGameplayDebuggerInputModifier& KeyModifier);` — updates entry in Categories array and modifies input binding params
- L208 _private prototype_ `void RemoveUnknownConfigs();` — remove all category and extension data from unknown sources (outdated entries)
- L210 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L212 _private prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L218 _private member_ `TArray<FName> KnownCategoryNames;` — used for cleanup
- L219 _private member_ `TArray<FName> KnownExtensionNames;`
- L220 _private member_ `TMultiMap<FName, FName> KnownCategoryInputNames;`
- L221 _private member_ `TMultiMap<FName, FName> KnownExtensionInputNames;`

#### class `UGameplayDebuggerUserSettings`  
`class UGameplayDebuggerUserSettings : public UDeveloperSettings`  
_L226-265_
- reflection: `UCLASS(config = EditorPerProjectUserSettings, meta = (DisplayName = "Gameplay Debugger"), MinimalAPI)`
- inherits: `UDeveloperSettings`
- L230 _protected function_ `virtual FName GetCategoryName() const override`
- L233 _public function_ `static int32 GetFontSize()`
- L234 _public prototype_ `static void SetFontSize(const int32 InFontSize);`
- L239 _public member_ `uint32 bEnableGameplayDebuggerInEditor : 1;` — `UPROPERTY(config, EditAnywhere, Category = GameplayDebugger)` — Controls whether GameplayDebugger will be available in pure editor mode. @Note that you need to reload the map for the changes to this property to take effect
- L246 _public member_ `float MaxViewDistance = 25000.0f;` — `UPROPERTY(config, EditAnywhere, Category = GameplayDebugger)` — Distance from view location under which actors can be selected This distance can also be used by some categories to apply culling.
- L253 _public member_ `float MaxViewAngle = 45.f;` — `UPROPERTY(config, EditAnywhere, Category = GameplayDebugger, meta = (UIMin = 0, ClampMin = 0, UIMax = 180, ClampMax = 180, Units = deg))` — Angle from view direction under which actors can be selected This angle can also be used by some categories to apply culling.
- L259 _public member_ `TSet<FName> EnabledCategories;` — `UPROPERTY(config, EditAnywhere, Category = GameplayDebugger)` — Persist which categories are enabled across editor sessions. Saved to disk as names since index is unstable.
- L264 _protected member_ `int32 FontSize = 10;` — `UPROPERTY(config, EditAnywhere, Category = GameplayDebugger)` — Font Size used by Gameplay Debugger

### `Source/Runtime/GameplayDebugger/Public/GameplayDebuggerExtension.h` (Public)


#### class `FGameplayDebuggerExtension`  
`class FGameplayDebuggerExtension : public FGameplayDebuggerAddonBase`  
_L25-49_
- inherits: `FGameplayDebuggerAddonBase`
- L29 _public prototype_ `virtual ~FGameplayDebuggerExtension() = default;`
- L30 _public prototype_ `virtual void OnGameplayDebuggerActivated() override;`
- L31 _public prototype_ `virtual void OnGameplayDebuggerDeactivated() override;`
- L34 _public prototype_ `virtual FString GetDescription() const;` — [LOCAL] description for gameplay debugger's header row, newline character is ignored
- L37 _public prototype_ `virtual void OnActivated();` — [LOCAL] called when added to debugger tool or tool is activated
- L40 _public prototype_ `virtual void OnDeactivated();` — [LOCAL] called when removed from debugger tool or tool is deactivated
- L43 _public prototype_ `bool IsLocal() const;` — check if extension is created for local player
- L48 _protected prototype_ `APlayerController* GetPlayerController() const;` — get player controller owning gameplay debugger tool

### `Source/Runtime/GameplayDebugger/Public/GameplayDebuggerExtension_HUD.h` (Public)


#### class `FGameplayDebuggerExtension_HUD`  
`class FGameplayDebuggerExtension_HUD : public FGameplayDebuggerExtension`  
_L8-37_
- inherits: `FGameplayDebuggerExtension`
- L12 _public prototype_ `FGameplayDebuggerExtension_HUD();`
- L14 _public prototype_ `virtual void OnActivated() override;`
- L15 _public prototype_ `virtual void OnDeactivated() override;`
- L16 _public prototype_ `virtual FString GetDescription() const override;`
- L18 _public prototype_ `static TSharedRef<FGameplayDebuggerExtension> MakeInstance();`
- L22 _protected prototype_ `void ToggleGameHUD();`
- L23 _protected prototype_ `void ToggleDebugMessages();`
- L24 _protected prototype_ `void SetGameHUDEnabled(bool bEnable);`
- L25 _protected prototype_ `void SetDebugMessagesEnabled(bool bEnable);`
- L27 _protected member_ `uint32 bWantsHUDEnabled : 1;`
- L28 _protected member_ `uint32 bIsGameHUDEnabled : 1;`
- L29 _protected member_ `uint32 bAreDebugMessagesEnabled : 1;`
- L30 _protected member_ `uint32 bPrevDebugMessagesEnabled : 1;`
- L31 _protected member_ `mutable uint32 bIsCachedDescriptionValid : 1;`
- L33 _protected member_ `int32 HudBindingIdx;`
- L34 _protected member_ `int32 MessagesBindingIdx;`
- L36 _protected member_ `mutable FString CachedDescription;`

### `Source/Runtime/GameplayDebugger/Public/GameplayDebuggerExtension_Spectator.h` (Public)


#### class `FGameplayDebuggerExtension_Spectator`  
`class FGameplayDebuggerExtension_Spectator : public FGameplayDebuggerExtension`  
_L10-29_
- inherits: `FGameplayDebuggerExtension`
- L14 _public prototype_ `FGameplayDebuggerExtension_Spectator();`
- L16 _public prototype_ `virtual void OnDeactivated() override;`
- L17 _public prototype_ `virtual FString GetDescription() const override;`
- L19 _public prototype_ `static TSharedRef<FGameplayDebuggerExtension> MakeInstance();`
- L23 _protected prototype_ `void ToggleSpectatorMode();`
- L25 _protected member_ `uint32 bHasInputBinding : 1;`
- L26 _protected member_ `mutable uint32 bIsCachedDescriptionValid : 1;`
- L27 _protected member_ `mutable FString CachedDescription;`
- L28 _protected member_ `TWeakObjectPtr<ADebugCameraController> SpectatorController;`

### `Source/Runtime/GameplayDebugger/Public/GameplayDebuggerLocalController.h` (Public)


#### class `UGameplayDebuggerLocalController`  
`class UGameplayDebuggerLocalController : public UObject`  
_L21-174_
- reflection: `UCLASS(NotBlueprintable, NotBlueprintType, noteditinlinenew, hidedropdown, Transient)`
- inherits: `UObject`
- L25 _private prototype_ `virtual void BeginDestroy() override;`
- L28 _private prototype_ `void Initialize(AGameplayDebuggerCategoryReplicator& Replicator, AGameplayDebuggerPlayerManager& Manager);` — initialize controller with replicator owner
- L31 _private prototype_ `void Cleanup();` — remove from world
- L35 _private function_ `void SetDebugDrawEnabled(const bool bInDebugDrawEnabled)` — Whether the Debug Draw rendering is allowed for this replicator
- L38 _private prototype_ `void OnDebugDraw(class UCanvas* Canvas, class APlayerController* PC);` — drawing event
- L41 _private prototype_ `void BindInput(UInputComponent& InputComponent);` — binds input actions
- L44 _private prototype_ `bool IsKeyBound(const FName KeyName) const;` — checks if key is bound by any action
- L46 _private function_ `static void SetConsoleCommandsEnabled(const bool bEnabled)`
- L50 _protected member_ `TObjectPtr<AGameplayDebuggerCategoryReplicator> CachedReplicator;` — `UPROPERTY()`
- L53 _protected member_ `TObjectPtr<AGameplayDebuggerPlayerManager> CachedPlayerManager;` — `UPROPERTY()`
- L56 _protected member_ `TObjectPtr<AActor> DebugActorCandidate;` — `UPROPERTY()`
- L59 _protected member_ `TObjectPtr<UFont> HUDFont;` — `UPROPERTY()`
- L61 _protected member_ `TArray<TArray<int32> > DataPackMap;`
- L62 _protected member_ `TArray<TArray<int32> > SlotCategoryIds;`
- L63 _protected member_ `TArray<FString> SlotNames;`
- L65 _protected member_ `uint32 bSimulateMode : 1;`
- L66 _protected member_ `uint32 bNeedsCleanup : 1;`
- L67 _protected member_ `uint32 bIsSelectingActor : 1;`
- L68 _protected member_ `uint32 bIsLocallyEnabled : 1;`
- L69 _protected member_ `uint32 bPrevLocallyEnabled : 1;`
- L70 _protected member_ `uint32 bEnableTextShadow : 1;`
- L71 _protected member_ `uint32 bPrevScreenMessagesEnabled : 1;`
- L73 _protected member_ `uint32 bActivateOnPIEEnd : 1;`
- L75 _protected member_ `int32 NumCategorySlots;`
- L76 _protected member_ `int32 NumCategories;`
- L78 _protected member_ `static bool bConsoleCommandsEnabled;`
- L83 _protected member_ `TSet<FName> UsedBindings;`
- L85 _protected member_ `FString ActivationKeyDesc;`
- L86 _protected member_ `FString RowUpKeyDesc;`
- L87 _protected member_ `FString RowDownKeyDesc;`
- L88 _protected member_ `FString CategoryKeysDesc;`
- L90 _protected member_ `int32 ActiveRowIdx;`
- L91 _protected member_ `static constexpr int32 NumCategoriesPerRow = 10;`
- L93 _protected member_ `float PaddingLeft;`
- L94 _protected member_ `float PaddingRight;`
- L95 _protected member_ `float PaddingTop;`
- L96 _protected member_ `float PaddingBottom;`
- L98 _protected member_ `FTimerHandle StartSelectingActorHandle;`
- L99 _protected member_ `FTimerHandle SelectActorTickHandle;`
- L101 _protected member_ `bool bDebugDrawEnabled = true;`
- L103 _protected prototype_ `void OnActivationPressed();`
- L104 _protected prototype_ `void OnActivationPressedWithModifier();`
- L105 _protected prototype_ `void OnActivationReleased();`
- L106 _protected prototype_ `void OnActivationReleasedWithModifier();`
- L107 _protected prototype_ `void OnCategory0Pressed();`
- L108 _protected prototype_ `void OnCategory1Pressed();`
- L109 _protected prototype_ `void OnCategory2Pressed();`
- L110 _protected prototype_ `void OnCategory3Pressed();`
- L111 _protected prototype_ `void OnCategory4Pressed();`
- L112 _protected prototype_ `void OnCategory5Pressed();`
- L113 _protected prototype_ `void OnCategory6Pressed();`
- L114 _protected prototype_ `void OnCategory7Pressed();`
- L115 _protected prototype_ `void OnCategory8Pressed();`
- L116 _protected prototype_ `void OnCategory9Pressed();`
- L117 _protected prototype_ `void OnCategoryRowUpPressed();`
- L118 _protected prototype_ `void OnCategoryRowDownPressed();`
- L119 _protected prototype_ `void OnCategoryBindingEvent(int32 CategoryId, int32 HandlerId);`
- L120 _protected prototype_ `void OnExtensionBindingEvent(int32 ExtensionId, int32 HandlerId);`
- L129 _protected prototype_ `void OnStartSelectingLocalPlayer();` — called short time after activation key was pressed and hold with 'Shift'
- L132 _protected prototype_ `void OnSelectLocalPlayer();` — sets the local player as the new debug actor
- L135 _protected prototype_ `void OnStartSelectingActor();` — called short time after activation key was pressed and hold
- L138 _protected prototype_ `void OnSelectActorTick();` — called in tick during actor selection
- L140 _protected prototype_ `void OnStartSelecting(ESelectionMode SelectionMode);`
- L143 _protected prototype_ `void ToggleSlotState(int32 SlotIdx);` — toggle state of categories in given slot
- L146 _protected prototype_ `void ToggleActivation(ESelectionMode SelectionMode = ESelectionMode::BestPawnCandidate);` — toggle debugger on/off
- L149 _protected prototype_ `void DrawHeader(FGameplayDebuggerCanvasContext& CanvasContext);` — draw header row
- L152 _protected prototype_ `void DrawCategoryHeader(int32 CategoryId, TSharedRef<FGameplayDebuggerCategory> Category, FGameplayDebuggerCanvasContext& CanvasContext);` — draw header for category
- L156 _protected prototype_ `void OnSelectionChanged(UObject* Object);` — event for simulate in editor mode
- L157 _protected prototype_ `void OnSelectedObject(UObject* Object);`
- L158 _protected prototype_ `void OnBeginPIE(const bool bIsSimulating);`
- L159 _protected prototype_ `void OnEndPIE(const bool bIsSimulating);`
- L162 _protected prototype_ `FString GetKeyDescriptionShort(const FKey& KeyBind) const;`
- L163 _protected prototype_ `FString GetKeyDescriptionLong(const FKey& KeyBind) const;`
- L166 _protected prototype_ `void RebuildDataPackMap();` — build DataPackMap for replication details
- L170 _protected prototype_ `void OnCategoriesChanged();` — called when known category set has changed
- L173 _protected prototype_ `void RestoreCategories();` — restore enabled categories from last session

#### enum `UGameplayDebuggerLocalController::ESelectionMode`  
`enum class ESelectionMode : uint8`  
_L122-126_
- L124 _public enumerator_ `BestPawnCandidate`
- L125 _public enumerator_ `LocalPlayer`

### `Source/Runtime/GameplayDebugger/Public/GameplayDebuggerModule.h` (Public)


#### class `FGameplayDebuggerModule`  
`class FGameplayDebuggerModule : public IGameplayDebugger`  
_L17-41_
- inherits: `IGameplayDebugger`
- L20 _public prototype_ `virtual void StartupModule() override;`
- L21 _public prototype_ `virtual void ShutdownModule() override;`
- L23 _public prototype_ `virtual void RegisterCategory(FName CategoryName, IGameplayDebugger::FOnGetCategory MakeInstanceDelegate, EGameplayDebuggerCategoryState CategoryState, int32 SlotIdx) override;`
- L24 _public prototype_ `virtual void UnregisterCategory(FName CategoryName) override;`
- L25 _public prototype_ `virtual void NotifyCategoriesChanged() override;`
- L26 _public prototype_ `virtual void RegisterExtension(FName ExtensionName, IGameplayDebugger::FOnGetExtension MakeInstanceDelegate) override;`
- L27 _public prototype_ `virtual void UnregisterExtension(FName ExtensionName) override;`
- L28 _public prototype_ `virtual void NotifyExtensionsChanged() override;`
- L30 _public prototype_ `AGameplayDebuggerPlayerManager& GetPlayerManager(UWorld* World);`
- L31 _public prototype_ `void OnWorldInitialized(UWorld* World, const UWorld::InitializationValues IVS);`
- L33 _public member_ `FGameplayDebuggerAddonManager AddonManager;`
- L34 _public member_ `TMap<TWeakObjectPtr<UWorld>, TWeakObjectPtr<AGameplayDebuggerPlayerManager>> PlayerManagers;`
- L36 _public member_ `static FOnLocalControllerInitialized OnLocalControllerInitialized;`
- L37 _public member_ `static FOnLocalControllerUninitialized OnLocalControllerUninitialized;`
- L39 _public member_ `static FOnDebuggerEdMode OnDebuggerEdModeActivation;`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnLocalControllerInitialized) DECLARE_MULTICAST_DELEGATE(FOnLocalControllerUninitialized) DECLARE_MULTICAST_DELEGATE(FOnDebuggerEdMode) class FGameplayDebuggerModule : public IGameplayDebugger { public: virtual void StartupModule() override; virtual void ShutdownModule() override; virtual void RegisterCategory(FName CategoryName, IGameplayDebugger::FOnGetCategory MakeInstanceDelegate, EGameplayDebuggerCategoryState CategoryState, int32 SlotIdx) override; virtual void UnregisterCategory(FName CategoryName) override; virtual void NotifyCategoriesChanged() override; virtual void RegisterExtension(FName ExtensionName, IGameplayDebugger::FOnGetExtension MakeInstanceDelegate) override; virtual void UnregisterExtension(FName ExtensionName) override; virtual void NotifyExtensionsChanged() override; AGameplayDebuggerPlayerManager& GetPlayerManager(UWorld* World); void OnWorldInitialized(UWorld* World, const UWorld::InitializationValues IVS); FGameplayDebuggerAddonManager AddonManager; TMap<TWeakObjectPtr<UWorld>, TWeakObjectPtr<AGameplayDebuggerPlayerManager>> PlayerManagers; static FOnLocalControllerInitialized OnLocalControllerInitialized; static FOnLocalControllerUninitialized OnLocalControllerUninitialized; #if WITH_EDITOR static FOnDebuggerEdMode OnDebuggerEdModeActivation; #endif`
- L14 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnLocalControllerUninitialized) DECLARE_MULTICAST_DELEGATE(FOnDebuggerEdMode) class FGameplayDebuggerModule : public IGameplayDebugger { public: virtual void StartupModule() override; virtual void ShutdownModule() override; virtual void RegisterCategory(FName CategoryName, IGameplayDebugger::FOnGetCategory MakeInstanceDelegate, EGameplayDebuggerCategoryState CategoryState, int32 SlotIdx) override; virtual void UnregisterCategory(FName CategoryName) override; virtual void NotifyCategoriesChanged() override; virtual void RegisterExtension(FName ExtensionName, IGameplayDebugger::FOnGetExtension MakeInstanceDelegate) override; virtual void UnregisterExtension(FName ExtensionName) override; virtual void NotifyExtensionsChanged() override; AGameplayDebuggerPlayerManager& GetPlayerManager(UWorld* World); void OnWorldInitialized(UWorld* World, const UWorld::InitializationValues IVS); FGameplayDebuggerAddonManager AddonManager; TMap<TWeakObjectPtr<UWorld>, TWeakObjectPtr<AGameplayDebuggerPlayerManager>> PlayerManagers; static FOnLocalControllerInitialized OnLocalControllerInitialized; static FOnLocalControllerUninitialized OnLocalControllerUninitialized; #if WITH_EDITOR static FOnDebuggerEdMode OnDebuggerEdModeActivation; #endif`
- L15 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnDebuggerEdMode) class FGameplayDebuggerModule : public IGameplayDebugger { public: virtual void StartupModule() override; virtual void ShutdownModule() override; virtual void RegisterCategory(FName CategoryName, IGameplayDebugger::FOnGetCategory MakeInstanceDelegate, EGameplayDebuggerCategoryState CategoryState, int32 SlotIdx) override; virtual void UnregisterCategory(FName CategoryName) override; virtual void NotifyCategoriesChanged() override; virtual void RegisterExtension(FName ExtensionName, IGameplayDebugger::FOnGetExtension MakeInstanceDelegate) override; virtual void UnregisterExtension(FName ExtensionName) override; virtual void NotifyExtensionsChanged() override; AGameplayDebuggerPlayerManager& GetPlayerManager(UWorld* World); void OnWorldInitialized(UWorld* World, const UWorld::InitializationValues IVS); FGameplayDebuggerAddonManager AddonManager; TMap<TWeakObjectPtr<UWorld>, TWeakObjectPtr<AGameplayDebuggerPlayerManager>> PlayerManagers; static FOnLocalControllerInitialized OnLocalControllerInitialized; static FOnLocalControllerUninitialized OnLocalControllerUninitialized; #if WITH_EDITOR static FOnDebuggerEdMode OnDebuggerEdModeActivation; #endif`

### `Source/Runtime/GameplayDebugger/Public/GameplayDebuggerPlayerManager.h` (Public)


#### struct `FGameplayDebuggerPlayerData`  
`struct FGameplayDebuggerPlayerData`  
_L18-30_
- reflection: `USTRUCT()`
- L23 _public member_ `TObjectPtr<UGameplayDebuggerLocalController> Controller = nullptr;` — `UPROPERTY()`
- L26 _public member_ `TObjectPtr<UInputComponent> InputComponent = nullptr;` — `UPROPERTY()`
- L29 _public member_ `TObjectPtr<AGameplayDebuggerCategoryReplicator> Replicator = nullptr;` — `UPROPERTY()`

#### class `AGameplayDebuggerPlayerManager`  
`class AGameplayDebuggerPlayerManager : public AActor, public FTickableGameObject`  
_L33-98_
- reflection: `UCLASS(NotBlueprintable, NotBlueprintType, notplaceable, noteditinlinenew, hidedropdown, Transient, MinimalAPI)`
- inherits: `AActor,FTickableGameObject`
- L37 _private prototype_ `virtual void TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;`
- L41 _private function_ `virtual UWorld* GetTickableGameObjectWorld() const override` — we're ticking only the manager only when in editor FTickableGameObject begin
- L42 _private prototype_ `virtual void Tick(float DeltaTime) override;`
- L43 _private prototype_ `virtual ETickableTickType GetTickableTickType() const override;`
- L44 _private prototype_ `virtual TStatId GetStatId() const override;`
- L45 _private function_ `virtual bool IsTickableInEditor() const override`
- L47 _private function_ `virtual bool IsTickable() const override` — results in this instance not being ticked in any of the game worlds
- L50 _private prototype_ `virtual void PostInitProperties() override;`
- L53 _protected prototype_ `virtual void BeginPlay() override;`
- L55 _protected prototype_ `void OnReplayScrubTeardown(UWorld* InWorld);`
- L56 _protected prototype_ `void OnGameModeLogout(AGameModeBase* GameMode, AController* Exiting);`
- L59 _public prototype_ `virtual void BeginDestroy() override;`
- L60 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type Reason) override;`
- L61 _public prototype_ `void Init();`
- L63 _public prototype_ `void UpdateAuthReplicators();`
- L64 _public prototype_ `void RegisterReplicator(AGameplayDebuggerCategoryReplicator& Replicator);`
- L65 _public prototype_ `void RefreshInputBindings(AGameplayDebuggerCategoryReplicator& Replicator);`
- L67 _public prototype_ `AGameplayDebuggerCategoryReplicator* GetReplicator(const APlayerController& OwnerPC) const;`
- L68 _public prototype_ `UInputComponent* GetInputComponent(const APlayerController& OwnerPC) const;`
- L69 _public prototype_ `UGameplayDebuggerLocalController* GetLocalController(const APlayerController& OwnerPC) const;`
- L71 _public function_ `UGameplayDebuggerLocalController* GetEditorController() const`
- L74 _public prototype_ `const FGameplayDebuggerPlayerData* GetPlayerData(const APlayerController& OwnerPC) const;`
- L76 _public prototype_ `static AGameplayDebuggerPlayerManager& GetCurrent(UWorld* World);`
- L79 _public prototype_ `static void GetViewPoint(const APlayerController& OwnerPC, FVector& OutViewLocation, FVector& OutViewDirection);` — extracts view location and direction from a player controller that can be used for picking
- L84 _protected member_ `TArray<FGameplayDebuggerPlayerData> PlayerData;` — `UPROPERTY()`
- L87 _protected member_ `TArray<TObjectPtr<AGameplayDebuggerCategoryReplicator>> PendingRegistrations;` — `UPROPERTY()`
- L91 _protected member_ `FGameplayDebuggerPlayerData EditorWorldData;` — `UPROPERTY()`
- L94 _protected member_ `uint8 bEditorTimeTick : 1;`
- L95 _protected member_ `uint32 bHasAuthority : 1;`
- L96 _protected member_ `uint32 bIsLocal : 1;`
- L97 _protected member_ `uint32 bInitialized : 1;`

### `Source/Runtime/GameplayDebugger/Public/GameplayDebuggerRenderingComponent.h` (Public)


#### class `FGameplayDebuggerDebugDrawDelegateHelper`  
`class FGameplayDebuggerDebugDrawDelegateHelper : public FDebugDrawDelegateHelper`  
_L11-31_
- inherits: `FDebugDrawDelegateHelper`
- L13 _private typedef_ `typedef FDebugDrawDelegateHelper Super;`
- L16 _public function_ `virtual ~FGameplayDebuggerDebugDrawDelegateHelper() override`
- L21 _public prototype_ `void Reset();`
- L23 _public prototype_ `void AddDelegateHelper(FDebugDrawDelegateHelper* InDebugDrawDelegateHelper);`
- L26 _protected prototype_ `virtual void RegisterDebugDrawDelegateInternal() override;`
- L27 _protected prototype_ `virtual void UnregisterDebugDrawDelegate() override;`
- L30 _private member_ `TArray<FDebugDrawDelegateHelper*> DebugDrawDelegateHelpers;`

#### class `UGameplayDebuggerRenderingComponent`  
`class UGameplayDebuggerRenderingComponent : public UDebugDrawComponent`  
_L36-47_
- reflection: `UCLASS(ClassGroup = Debug, NotBlueprintable, NotBlueprintType, noteditinlinenew, hidedropdown, Transient)`
- inherits: `UDebugDrawComponent`
- L41 _protected prototype_ `virtual FDebugRenderSceneProxy* CreateDebugSceneProxy() override;`
- L42 _protected function_ `virtual FDebugDrawDelegateHelper& GetDebugDrawDelegateHelper() override`
- L43 _protected prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform &LocalToWorld) const override;`
- L46 _private member_ `FGameplayDebuggerDebugDrawDelegateHelper GameplayDebuggerDebugDrawDelegateHelper;`

### `Source/Runtime/GameplayDebugger/Public/GameplayDebuggerTypes.h` (Public)


#### class `FGameplayDebuggerCanvasContext`  
`class FGameplayDebuggerCanvasContext`  
_L29-148_
- L33 _public member_ `TWeakObjectPtr<UCanvas> Canvas;` — canvas used for drawing
- L36 _public member_ `TWeakObjectPtr<UFont> Font;` — current text font
- L39 _public member_ `TWeakObjectPtr<APlayerController> PlayerController;` — the player controller associated with this debugger context
- L42 _public member_ `TWeakObjectPtr<UWorld> World;` — the world associated with this debugger context
- L45 _public member_ `FFontRenderInfo FontRenderInfo;` — font render data
- L48 _public member_ `float CursorX, CursorY;` — position of cursor
- L48 _public member_ `float CursorX, CursorY;` — position of cursor
- L51 _public member_ `float DefaultX, DefaultY;` — default position of cursor
- L51 _public member_ `float DefaultX, DefaultY;` — default position of cursor
- L53 _public function_ `FGameplayDebuggerCanvasContext()`
- L54 _public prototype_ `FGameplayDebuggerCanvasContext(UCanvas* InCanvas, UFont* InFont);`
- L57 _public prototype_ `void Print(const FString& String);` — print string on canvas
- L58 _public prototype_ `void Print(const FColor& Color, const FString& String);`
- L59 _public prototype_ `void Print(const FColor& Color, const float Alpha, const FString& String);`
- L60 _public prototype_ `void PrintAt(float PosX, float PosY, const FString& String);`
- L61 _public prototype_ `void PrintAt(float PosX, float PosY, const FColor& Color, const FString& String);`
- L62 _public prototype_ `void PrintAt(float PosX, float PosY, const FColor& Color, const float Alpha, const FString& String);`
- L66 _public function_ `template <typename FmtType, typename... Types> void Printf(const FmtType& Fmt, Types... Args)` — print formatted string on canvas
- L75 _public function_ `template <typename FmtType, typename... Types> void Printf(const FColor& Color, const FmtType& Fmt, Types... Args)`
- L84 _public function_ `template <typename FmtType, typename... Types> void Printf(const FColor& Color, const float Alpha, const FmtType& Fmt, Types... Args)`
- L93 _public function_ `template <typename FmtType, typename... Types> void PrintfAt(float PosX, float PosY, const FmtType& Fmt, Types... Args)`
- L102 _public function_ `template <typename FmtType, typename... Types> void PrintfAt(float PosX, float PosY, const FColor& Color, const FmtType& Fmt, Types... Args)`
- L111 _public function_ `template <typename FmtType, typename... Types> void PrintfAt(float PosX, float PosY, const FColor& Color, const float Alpha, const FmtType& Fmt, Types... Args)`
- L120 _private prototype_ `void VARARGS PrintfImpl(const FColor& Color, const float Alpha, const TCHAR* Args, ...);`
- L121 _private prototype_ `void VARARGS PrintfAtImpl(float PosX, float PosY, const FColor& Color, const float Alpha, const TCHAR* Args, ...);`
- L125 _public prototype_ `void MoveToNewLine();` — moves cursor to new line
- L128 _public prototype_ `void MeasureString(const FString& String, float& OutSizeX, float& OutSizeY) const;` — calculate size of string
- L131 _public prototype_ `float GetLineHeight() const;` — get height of single line text
- L134 _public prototype_ `FVector2D ProjectLocation(const FVector& Location) const;` — project world location on canvas
- L137 _public prototype_ `bool IsLocationVisible(const FVector& Location) const;` — check if world location is visible in current view
- L140 _public prototype_ `void DrawItem(FCanvasItem& Item, float PosX, float PosY);` — draw item on canvas
- L143 _public prototype_ `void DrawIcon(const FColor& Color, const FCanvasIcon& Icon, float PosX, float PosY, float Scale = 1.f);` — draw icon on canvas
- L147 _public prototype_ `UWorld* GetWorld() const;` — fetches the World associated with this context. Will use the World member variable, if set, and PlayerController's world otherwise. Note that it can still be null and needs to be tested.

#### enum `EGameplayDebuggerShape`  
`enum class EGameplayDebuggerShape : uint8`  
_L163-177_
- reflection: `UENUM()`
- L165 _public enumerator_ `Invalid`
- L166 _public enumerator_ `Point`
- L167 _public enumerator_ `Segment`
- L168 _public enumerator_ `Box`
- L169 _public enumerator_ `Cone`
- L170 _public enumerator_ `Cylinder`
- L171 _public enumerator_ `Circle`
- L172 _public enumerator_ `Rectangle`
- L173 _public enumerator_ `Capsule`
- L174 _public enumerator_ `Polygon`
- L175 _public enumerator_ `Polyline`
- L176 _public enumerator_ `Arrow`

#### struct `FGameplayDebuggerShape`  
`struct FGameplayDebuggerShape`  
_L180-232_
- reflection: `USTRUCT()`
- L186 _public member_ `TArray<FVector> ShapeData;` — `UPROPERTY()` — points defining shape
- L190 _public member_ `FString Description;` — `UPROPERTY()` — description of shape
- L194 _public member_ `FColor Color;` — `UPROPERTY()` — color of shape
- L198 _public member_ `EGameplayDebuggerShape Type;` — `UPROPERTY()` — type of shape
- L200 _public function_ `FGameplayDebuggerShape() : Color(EForceInit::ForceInit), Type(EGameplayDebuggerShape::Invalid)`
- L202 _public function_ `bool operator==(const FGameplayDebuggerShape& Other) const`
- L207 _public prototype_ `static FGameplayDebuggerShape MakePoint(const FVector& Location, const float Radius, const FColor& Color, const FString& Description = FString());`
- L208 _public prototype_ `static FGameplayDebuggerShape MakeSegment(const FVector& StartLocation, const FVector& EndLocation, const float Thickness, const FColor& Color, const FString& Description = FString());`
- L209 _public prototype_ `static FGameplayDebuggerShape MakeSegment(const FVector& StartLocation, const FVector& EndLocation, const FColor& Color, const FString& Description = FString());`
- L210 _public prototype_ `static FGameplayDebuggerShape MakeArrow(const FVector& StartLocation, const FVector& EndLocation, const float HeadSize, const float Thickness, const FColor& Color, const FString& Description = FString());`
- L211 _public prototype_ `static FGameplayDebuggerShape MakeBox(const FVector& Center, const FVector& Extent, const FColor& Color, const FString& Description = FString());`
- L212 _public prototype_ `static FGameplayDebuggerShape MakeBox(const FVector& Center, const FVector& Extent, const float Thickness, const FColor& Color, const FString& Description = FString());`
- L213 _public prototype_ `static FGameplayDebuggerShape MakeBox(const FVector& Center, const FRotator& Rotation, const FVector& Extent, const FColor& Color, const FString& Description = FString());`
- L214 _public prototype_ `static FGameplayDebuggerShape MakeBox(const FVector& Center, const FRotator& Rotation, const FVector& Extent, const float Thickness, const FColor& Color, const FString& Description = FString());`
- L215 _public prototype_ `static FGameplayDebuggerShape MakeCone(const FVector& Location, const FVector& Direction, const float Length, const FColor& Color, const FString& Description = FString());`
- L216 _public prototype_ `static FGameplayDebuggerShape MakeCylinder(const FVector& Center, const float Radius, const float HalfHeight, const FColor& Color, const FString& Description = FString());`
- L217 _public prototype_ `static FGameplayDebuggerShape MakeCircle(const FVector& Center, const FVector& Up, const float Radius, const FColor& Color, const FString& Description = FString());`
- L218 _public prototype_ `static FGameplayDebuggerShape MakeCircle(const FVector& Center, const FVector& Up, const float Radius, const float Thickness, const FColor& Color, const FString& Description = FString());`
- L219 _public prototype_ `static FGameplayDebuggerShape MakeCircle(const FVector& Center, const FVector& WidthAxis, const FVector& HeightAxis, const float Radius, const FColor& Color, const FString& Description = FString());`
- L220 _public prototype_ `static FGameplayDebuggerShape MakeCircle(const FVector& Center, const FVector& WidthAxis, const FVector& HeightAxis, const float Radius, const float Thickness, const FColor& Color, const FString& Description = FString());`
- L221 _public prototype_ `static FGameplayDebuggerShape MakeRectangle(const FVector& Center, const FVector& WidthAxis, const FVector& HeightAxis, const float Width, const float Height, const FColor& Color, const FString& Description = FString());`
- L222 _public prototype_ `static FGameplayDebuggerShape MakeRectangle(const FVector& Center, const FVector& WidthAxis, const FVector& HeightAxis, const float Width, const float Height, const float Thickness, const FColor& Color, const FString& Description = FString());`
- L223 _public prototype_ `static FGameplayDebuggerShape MakeCapsule(const FVector& Center, const float Radius, const float HalfHeight, const FColor& Color, const FString& Description = FString());`
- L224 _public prototype_ `static FGameplayDebuggerShape MakeCapsule(const FVector& Center, const FRotator& Rotation, const float Radius, const float HalfHeight, const FColor& Color, const FString& Description = FString());`
- L225 _public prototype_ `static FGameplayDebuggerShape MakePolygon(TConstArrayView<FVector> Verts, const FColor& Color, const FString& Description = FString());`
- L226 _public prototype_ `static FGameplayDebuggerShape MakePolyline(const TConstArrayView<FVector> Verts, const float Thickness, const FColor& Color, const FString& Description = FString());`
- L227 _public prototype_ `static FGameplayDebuggerShape MakePolyline(const TConstArrayView<FVector> Verts, const FColor& Color, const FString& Description = FString());`
- L228 _public prototype_ `static FGameplayDebuggerShape MakeSegmentList(const TConstArrayView<FVector> Verts, const float Thickness, const FColor& Color, const FString& Description = FString());`
- L229 _public prototype_ `static FGameplayDebuggerShape MakeSegmentList(const TConstArrayView<FVector> Verts, const FColor& Color, const FString& Description = FString());`
- L231 _public prototype_ `void Draw(UWorld* World, FGameplayDebuggerCanvasContext& Context);`

#### enum `EGameplayDebuggerDataPack`  
`enum class EGameplayDebuggerDataPack : uint8`  
_L236-241_
- L238 _public enumerator_ `Persistent`
- L239 _public enumerator_ `ResetOnActorChange`
- L240 _public enumerator_ `ResetOnTick`

#### struct `FGameplayDebuggerDataPackHeader`  
`struct FGameplayDebuggerDataPackHeader`  
_L244-284_
- reflection: `USTRUCT()`
- L250 _public member_ `int16 DataVersion;` — `UPROPERTY()` — version, increased every time new Data is requested
- L254 _public member_ `int16 SyncCounter;` — `UPROPERTY()` — debug actor sync counter
- L258 _public member_ `int32 DataSize;` — `UPROPERTY()` — size of Data array
- L262 _public member_ `int32 DataOffset;` — `UPROPERTY()` — offset to currently replicated portion of data
- L266 _public member_ `uint32 bIsCompressed : 1;` — `UPROPERTY()` — is data compressed?
- L268 _public function_ `FGameplayDebuggerDataPackHeader() : DataVersion(0), SyncCounter(0), DataSize(0), DataOffset(0), bIsCompressed(false)`
- L270 _public function_ `inline bool Equals(const FGameplayDebuggerDataPackHeader& Other) const`
- L275 _public function_ `inline bool operator==(const FGameplayDebuggerDataPackHeader& Other) const`
- L280 _public function_ `inline bool operator!=(const FGameplayDebuggerDataPackHeader& Other) const`

#### struct `FGameplayDebuggerDataPack`  
`struct FGameplayDebuggerDataPack`  
_L286-349_
- L288 _public typedef_ `using FHeader = FGameplayDebuggerDataPackHeader;`
- L290 _public prototype_ `DECLARE_DELEGATE(FOnReset);`
- L291 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnSerialize, FArchive&);`
- L293 _public function_ `FGameplayDebuggerDataPack() : PackId(0), DataCRC(0), bIsDirty(false), bNeedsConfirmation(false), bReceived(false), Flags(EGameplayDebuggerDataPack::ResetOnTick)`
- L299 _public member_ `TArray<uint8> Data;` — data being replicated
- L302 _public member_ `FHeader Header;` — minimal header used for DataPack state comparison
- L305 _public member_ `int32 PackId;` — auto assigned Id of pack
- L308 _public member_ `uint32 DataCRC;` — CRC used to test changes in Data array
- L311 _public member_ `uint32 bIsDirty : 1;` — force net replication, regardless DataCRC
- L314 _public member_ `uint32 bNeedsConfirmation : 1;` — if set, replication must be confirmed by client before sending next update
- L317 _public member_ `uint32 bReceived : 1;` — set when client receives complete data pack
- L320 _public member_ `EGameplayDebuggerDataPack Flags;` — data pack flags
- L322 _public member_ `FOnReset ResetDelegate;`
- L323 _public member_ `FOnSerialize SerializeDelegate;`
- L325 _public member_ `static int32 PacketSize;`
- L327 _public prototype_ `bool CheckDirtyAndUpdate();`
- L328 _public prototype_ `bool RequestReplication(int16 SyncCounter);`
- L330 _public prototype_ `void OnReplicated();`
- L331 _public prototype_ `void OnPacketRequest(int16 DataVersion, int32 DataOffset);`
- L334 _public function_ `inline float GetProgress() const` — get replication progress in (0..1) range
- L340 _public function_ `inline bool IsInProgress() const` — is replication in progress?
- L345 _public function_ `static bool IsMultiPacket(int32 TestSize)`

#### enum `EGameplayDebuggerInputMode`  
`enum class EGameplayDebuggerInputMode : uint8`  
_L351-358_
- L354 _public enumerator_ `Local` — input handler is called on local category
- L357 _public enumerator_ `Replicated` — input handler is replicated to authority category and called there

#### struct `FGameplayDebuggerInputModifier`  
`struct FGameplayDebuggerInputModifier`  
_L360-382_
- L362 _public member_ `uint32 bShift : 1;`
- L363 _public member_ `uint32 bCtrl : 1;`
- L364 _public member_ `uint32 bAlt : 1;`
- L365 _public member_ `uint32 bCmd : 1;`
- L366 _public member_ `uint32 bPressed : 1;`
- L367 _public member_ `uint32 bReleased : 1;`
- L369 _public function_ `FGameplayDebuggerInputModifier() : bShift(false), bCtrl(false), bAlt(false), bCmd(false), bPressed(true), bReleased(false)`
- L370 _public function_ `FGameplayDebuggerInputModifier(bool bInShift, bool bInCtrl, bool bInAlt, bool bInCmd) : bShift(bInShift), bCtrl(bInCtrl), bAlt(bInAlt), bCmd(bInCmd), bPressed(true), bReleased(false)`
- L372 _public function_ `FGameplayDebuggerInputModifier operator+(const FGameplayDebuggerInputModifier& Other) const`
- L377 _public member_ `static FGameplayDebuggerInputModifier Shift;`
- L378 _public member_ `static FGameplayDebuggerInputModifier Ctrl;`
- L379 _public member_ `static FGameplayDebuggerInputModifier Alt;`
- L380 _public member_ `static FGameplayDebuggerInputModifier Cmd;`
- L381 _public member_ `static FGameplayDebuggerInputModifier None;`

#### struct `FGameplayDebuggerInputHandler`  
`struct FGameplayDebuggerInputHandler`  
_L384-397_
- L386 _public prototype_ `DECLARE_DELEGATE(FHandler);`
- L388 _public member_ `FName KeyName;`
- L389 _public member_ `FGameplayDebuggerInputModifier Modifier;`
- L390 _public member_ `FHandler Delegate;`
- L391 _public member_ `EGameplayDebuggerInputMode Mode;`
- L393 _public function_ `FGameplayDebuggerInputHandler() : KeyName(NAME_None), Mode(EGameplayDebuggerInputMode::Local)`
- L395 _public prototype_ `bool IsValid() const;`
- L396 _public prototype_ `FString ToString() const;`

#### struct `FGameplayDebuggerInputHandlerConfig`  
`struct FGameplayDebuggerInputHandlerConfig`  
_L404-418_
- desc: Customizable key binding used by FGameplayDebuggerAddonBase (both categories and extensions) Intended to use only from addon's constructor! Check example in FGameplayDebuggerExtension_Spectator::FGameplayDebuggerExtension_Spectator() for details
- L406 _public member_ `FName KeyName;`
- L407 _public member_ `FGameplayDebuggerInputModifier Modifier;`
- L409 _public function_ `FGameplayDebuggerInputHandlerConfig() : KeyName(NAME_None)`
- L410 _public prototype_ `FGameplayDebuggerInputHandlerConfig(const FName ConfigName, const FName DefaultKeyName);`
- L411 _public prototype_ `FGameplayDebuggerInputHandlerConfig(const FName ConfigName, const FName DefaultKeyName, const FGameplayDebuggerInputModifier& DefaultModifier);`
- L413 _public member_ `static FName CurrentCategoryName;`
- L414 _public member_ `static FName CurrentExtensionName;`
- L417 _private prototype_ `void UpdateConfig(const FName ConfigName);`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogGameplayDebug, Log, All);`
- L19 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGameplayDebug, Log, All);`
- L24 _namespace_ `namespace FGameplayDebuggerUtils`
- L26 _prototype_ `bool IsAuthority(UWorld* World);` (scope `FGameplayDebuggerUtils`)
- L150 _namespace_ `namespace FGameplayDebuggerCanvasStrings`
- L152 _externvar_ `extern FString ColorNameInput;` (scope `FGameplayDebuggerCanvasStrings`)
- L153 _externvar_ `extern FString ColorNameEnabled;` (scope `FGameplayDebuggerCanvasStrings`)
- L154 _externvar_ `extern FString ColorNameDisabled;` (scope `FGameplayDebuggerCanvasStrings`)
- L155 _externvar_ `extern FString ColorNameEnabledActiveRow;` (scope `FGameplayDebuggerCanvasStrings`)
- L156 _externvar_ `extern FString ColorNameDisabledActiveRow;` (scope `FGameplayDebuggerCanvasStrings`)
- L158 _externvar_ `extern FString Separator;` (scope `FGameplayDebuggerCanvasStrings`)
- L159 _externvar_ `extern FString SeparatorSpace;` (scope `FGameplayDebuggerCanvasStrings`)
- L234 _prototype_ `FArchive& operator<<(FArchive& Ar, FGameplayDebuggerShape& Shape);`
- L290 _delegate_ `DECLARE_DELEGATE(FOnReset);`
- L291 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSerialize, FArchive&);`
- L386 _delegate_ `DECLARE_DELEGATE(FHandler);`
