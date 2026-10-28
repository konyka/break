# Plugins / ConcertTakeRecorder

- module root: `Plugins/VirtualProduction/MultiUserTakes/Source/ConcertTakeRecorder`
- headers: 7; symbols: 144
- symbol kinds: class=8, delegate=3, function=11, macro=1, member=40, namespace=2, prototype=68, struct=9, typedef=2
- PrivateDependencyModuleNames: Concert, ConcertSyncClient, ConcertSyncCore, ConcertTransport, EditorStyle, Engine, InputCore, LevelSequence, Projects, Slate, SlateCore, TakeRecorder, TakesCore, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/VirtualProduction/MultiUserTakes/Source/ConcertTakeRecorder/Private/ConcertTakeRecorderClientSessionCustomization.h` (Private)


#### class `FConcertTakeRecorderClientSessionCustomization`  
`class FConcertTakeRecorderClientSessionCustomization : public IDetailCustomization`  
_L14-46_
- inherits: `IDetailCustomization`
- L16 _private typedef_ `using SListViewClientRecordSetting = SListView<TSharedPtr<FConcertClientRecordSetting>>;`
- L20 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;`
- L24 _public prototype_ `void UpdateClientSettings(EConcertClientStatus Status, const FConcertClientRecordSetting& RecordSetting);` — Updates the internal list of client data. Called whenever an external change is made (e.g. from remote client).
- L26 _public prototype_ `void PopulateClientList();` — Resets the Clients list. Creates an entry for every client in the session.
- L29 _public prototype_ `const FConcertClientRecordSetting* FindClientSettings(const FGuid& EndpointSettings) const;` — @return The settings saved for the client or nullptr
- L31 _public function_ `FOnConcertRecordSettingChanged& OnRecordSettingChanged()`
- L35 _private member_ `FOnConcertRecordSettingChanged OnRecordSettingDelegate;`
- L38 _private member_ `TArray<TSharedPtr<FConcertClientRecordSetting>> Clients;` — State of the local and remote clients. Updated externally by UpdateClientSettings. Remote clients trigger networked events when they change the settings.
- L39 _private member_ `TWeakPtr<SListViewClientRecordSetting> ClientsListViewWeak;`
- L42 _private prototype_ `void RecordSettingChange(const FConcertClientRecordSetting &RecordSetting);` — Called when a setting is changed by the customization
- L45 _private prototype_ `int32 InternalFindClientSettingsIndex(const FGuid& ClientEndpointId) const;` — @return The settings saved for the client or nullptr

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnConcertRecordSettingChanged, const FConcertClientRecordSetting&);`
- L12 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnConcertRecordSettingChanged, const FConcertClientRecordSetting&);`

### `Plugins/VirtualProduction/MultiUserTakes/Source/ConcertTakeRecorder/Private/ConcertTakeRecorderManager.h` (Private)


#### class `FConcertTakeRecorderManager`  
`class FConcertTakeRecorderManager : public FGCObject`  
_L45-183_
- inherits: `FGCObject`
- desc: Take Recorder manager that is held by the client sync module that keeps track of when a take is started, stopped or cancelled. Events are registered to client sessions that will then operate on the Take Recorder UIs
- L50 _public prototype_ `FConcertTakeRecorderManager();` — Registers TakeRecorderInitialized handler with the take recorder module
- L59 _public prototype_ `void Register(TSharedRef<IConcertClientSession> InSession);` — Register all custom take recorder events for the specified client session @param InSession	The client session to register custom events with
- L65 _public prototype_ `void Unregister(TSharedRef<IConcertClientSession> InSession);` — Unregister previously registered custom take recorder events from the specified client session @param InSession The client session to unregister custom events from
- L68 _public prototype_ `const FConcertClientRecordSetting* FindClientRecorderSetting(const FGuid& EndpointId) const;` — Attempts the client recorder settings for the given client. The other clients inform us when they are changed so they are somewhat in sync. Nullptr if the client is unknown.
- L73 _public prototype_ `bool EditClientSettings( const FGuid& EndpointId, TFunctionRef<void(FTakeRecordSettings& Settings)> ModifierFunc, TOptional<TFunctionRef<bool(const FTakeRecordSettings& Settings)>> Predicate = {} );` — Modifies the settings of a client, if the client exists. Subsequently updates all the relevant systems of the change. @return Whether the client was found.
- L81 _private prototype_ `void OnTakeRecorderInitialized(UTakeRecorder* TakeRecorder);`
- L82 _private prototype_ `void OnRecordingFinished(UTakeRecorder* TakeRecorder);`
- L83 _private prototype_ `void OnRecordingCancelled(UTakeRecorder* TakeRecorder);`
- L84 _private prototype_ `void OnTakeRecorderStarted(UTakeRecorder* TakeRecorder);`
- L85 _private prototype_ `void OnTakeRecorderStopped(UTakeRecorder* TakeRecorder);`
- L87 _private prototype_ `void OnFrameAdjustment(UTakeRecorder* TakeRecorder, const FFrameNumber& InPlaybackStartFrame);`
- L90 _private prototype_ `void OnTakeInitializedEvent(const FConcertSessionContext&, const FConcertTakeInitializedEvent& InEvent);`
- L91 _private prototype_ `void OnRecordingFinishedEvent(const FConcertSessionContext&, const FConcertRecordingFinishedEvent&);`
- L92 _private prototype_ `void OnRecordingCancelledEvent(const FConcertSessionContext&, const FConcertRecordingCancelledEvent&);`
- L94 _private prototype_ `void OnRecordSettingsChangeEvent(const FConcertSessionContext&, const FConcertRecordSettingsChangeEvent&);`
- L95 _private prototype_ `void OnMultiUserSyncChangeEvent(const FConcertSessionContext&, const FConcertMultiUserSyncChangeEvent&);`
- L97 _private prototype_ `void OnNamedLevelSequenceEvent(const FConcertSessionContext&, const FConcertRecordingNamedLevelSequenceEvent&);`
- L99 _private prototype_ `void OnSessionClientChanged(IConcertClientSession&, EConcertClientStatus ClientStatus, const FConcertSessionClientInfo& InClientInfo);`
- L100 _private prototype_ `void OnSessionConnectionChanged(IConcertClientSession&, EConcertConnectionStatus ConnectionStatus);`
- L103 _private prototype_ `void RegisterExtensions();`
- L104 _private prototype_ `void UnregisterExtensions();`
- L106 _private prototype_ `void CreateExtensionWidget(TArray<TSharedRef<class SWidget>>& OutExtensions);`
- L107 _private prototype_ `void CreateRecordButtonOverlay(TArray<TSharedRef<SWidget>>& OutExtensions);`
- L109 _private prototype_ `SIZE_T RemoteRecorders() const;`
- L110 _private prototype_ `bool ShouldIconBeVisible() const;`
- L111 _private prototype_ `EVisibility GetMultiUserIconVisibility() const;`
- L113 _private prototype_ `bool IsTakeSyncEnabled() const;`
- L114 _private prototype_ `ECheckBoxState IsTakeSyncChecked() const;`
- L115 _private prototype_ `void HandleTakeSyncCheckBox(ECheckBoxState State) const;`
- L116 _private prototype_ `EVisibility HandleTakeSyncButtonVisibility() const;`
- L118 _private prototype_ `void UpdateSessionClientList();`
- L119 _private prototype_ `void DisconnectFromSession();`
- L120 _private prototype_ `void ConnectToSession(IConcertClientSession&);`
- L122 _private prototype_ `ETransactionFilterResult ShouldObjectBeTransacted(const FConcertTransactionFilterArgs& FilterArgs);`
- L123 _private prototype_ `EPackageFilterResult ShouldPackageBeFiltered(const FConcertPackageInfo& InPackage);`
- L124 _private prototype_ `bool CanSkipHotReload(const FConcertPackageInfo& InPackage);`
- L126 _private prototype_ `FTakeRecorderParameters SetupTakeParametersForMultiuser(const FTakeRecorderParameters& Input);`
- L128 _private function_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override`
- L134 _private function_ `virtual FString GetReferencerName() const override`
- L139 _private prototype_ `void ReportRecordingError(FText &);`
- L140 _private prototype_ `bool CanRecord() const;`
- L141 _private prototype_ `bool CanAnyRecord() const;`
- L143 _private prototype_ `void SendInitialState(IConcertClientSession&);`
- L144 _private prototype_ `void OnTakeSyncPropertyChange(bool Value);`
- L146 _private prototype_ `void RecordSettingChange(const FConcertClientRecordSetting& RecordSetting);`
- L147 _private prototype_ `void AddRemoteClient(const FConcertSessionClientInfo& ClientInfo);`
- L149 _private prototype_ `bool CanReviewLastRecordedSequence() const;`
- L152 _private member_ `TWeakPtr<IConcertClientSession> WeakSession;` — Weak pointer to the client session with which to send events. May be null or stale.
- L161 _private member_ `} TakeRecorderState;`
- L163 _private member_ `TObjectPtr<UTakePreset> Preset = nullptr;`
- L165 _private member_ `mutable TObjectPtr<ULevelSequence> LastLevelSequence = nullptr;`
- L166 _private member_ `mutable FString LastLevelSequencePath;`
- L168 _private member_ `TSharedPtr<FConcertTakeRecorderClientSessionCustomization> Customization;`
- L171 _private member_ `FDelegateHandle ClientChangeDelegate;` — Delegate for any changes in client state.
- L174 _private member_ `FDelegateHandle TakeSyncDelegate;` — Delegate for any changes take sync status.
- L179 _private member_ `bool bIsRecording = false;` — Denotes if we are currently in recording mode.
- L182 _private member_ `bool bHaveWarned = false;` — Indicates if we have warned the user about multiple recorders.

#### struct `FConcertTakeRecorderManager::FTakeRecorderState`  
`struct FTakeRecorderState`  
_L157-161_
- desc: Used to prevent sending out events that were just received by this client.
- L159 _public member_ `FString LastStartedTake;`
- L160 _public member_ `FString LastStoppedTake;`

#### Free symbols / members of external scopes

- L39 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogConcertTakeRecorder, Log, All);`
- L39 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogConcertTakeRecorder, Log, All);`

### `Plugins/VirtualProduction/MultiUserTakes/Source/ConcertTakeRecorder/Private/ConcertTakeRecorderMessages.h` (Private)


#### class `UConcertTakeSynchronization`  
`class UConcertTakeSynchronization : public UObject`  
_L12-22_
- reflection: `UCLASS(config=Engine, DisplayName="Multi-user Take Synchronization")`
- inherits: `UObject`
- L18 _public member_ `bool bSyncTakeRecordingTransactions = true;` — `UPROPERTY(config,EditAnywhere,BlueprintReadWrite,Category="Multi-user Take Synchronization",DisplayName="Synchronize Take Recorder Transactions")`
- L21 _public member_ `bool bTransactTakeMetadata = true;` — `UPROPERTY(config,EditAnywhere,BlueprintReadWrite,Category="Multi-user Take Synchronization")`

#### struct `FTakeRecordSettings`  
`struct FTakeRecordSettings`  
_L25-34_
- reflection: `USTRUCT()`
- L30 _public member_ `bool bRecordOnClient = false;` — `UPROPERTY(config,EditAnywhere,Category="Multi-user Client Record Settings")`
- L33 _public member_ `bool bTransactSources = true;` — `UPROPERTY(config,EditAnywhere,Category="Multi-user Client Record Settings")`

#### struct `FConcertClientRecordSetting`  
`struct FConcertClientRecordSetting`  
_L37-49_
- reflection: `USTRUCT()`
- L42 _public member_ `FConcertSessionClientInfo Details;` — `UPROPERTY()`
- L45 _public member_ `bool bTakeSyncEnabled = true;` — `UPROPERTY()`
- L48 _public member_ `FTakeRecordSettings Settings;` — `UPROPERTY()`

#### class `UConcertSessionRecordSettings`  
`class UConcertSessionRecordSettings : public UObject`  
_L52-62_
- reflection: `UCLASS(config=Engine, DisplayName="Multi-user Client Record Settings")`
- inherits: `UObject`
- L58 _public member_ `FTakeRecordSettings LocalSettings;` — `UPROPERTY(config,EditAnywhere,Category="Multi-user Client Record Settings")`
- L61 _public member_ `TArray<FConcertClientRecordSetting> RemoteSettings;` — `UPROPERTY(Transient,EditAnywhere,Category="Multi-user Client Record Settings")`

#### struct `FConcertRecordSettingsChangeEvent`  
`struct FConcertRecordSettingsChangeEvent`  
_L65-74_
- reflection: `USTRUCT()`
- L70 _public member_ `FGuid EndpointId;` — `UPROPERTY()`
- L73 _public member_ `FTakeRecordSettings Settings;` — `UPROPERTY()`

#### struct `FConcertMultiUserSyncChangeEvent`  
`struct FConcertMultiUserSyncChangeEvent`  
_L77-86_
- reflection: `USTRUCT()`
- L82 _public member_ `FGuid EndpointId;` — `UPROPERTY()`
- L85 _public member_ `bool bSyncTakeRecordingTransactions = true;` — `UPROPERTY()`

#### struct `FConcertTakeInitializedEvent`  
`struct FConcertTakeInitializedEvent`  
_L90-114_
- reflection: `USTRUCT()`
- L95 _public member_ `FString TakePresetPath;` — `UPROPERTY()`
- L98 _public member_ `FString TakeName;` — `UPROPERTY()`
- L101 _public member_ `TArray<uint8> TakeData;` — `UPROPERTY()`
- L104 _public member_ `FString TakeMetaDataPath;` — `UPROPERTY()`
- L107 _public member_ `FConcertLocalIdentifierState IdentifierState;` — `UPROPERTY()`
- L110 _public member_ `FTakeRecorderUserParameters Settings;` — `UPROPERTY()`
- L113 _public member_ `FTakeRecorderProjectParameters Project;` — `UPROPERTY()`

#### struct `FConcertRecordingFinishedEvent`  
`struct FConcertRecordingFinishedEvent`  
_L117-123_
- reflection: `USTRUCT()`
- L122 _public member_ `FString TakeName;` — `UPROPERTY()`

#### struct `FConcertRecordingNamedLevelSequenceEvent`  
`struct FConcertRecordingNamedLevelSequenceEvent`  
_L126-132_
- reflection: `USTRUCT()`
- L131 _public member_ `FString LevelSequencePath;` — `UPROPERTY()`

#### struct `FConcertRecordingCancelledEvent`  
`struct FConcertRecordingCancelledEvent`  
_L135-141_
- reflection: `USTRUCT()`
- L140 _public member_ `FString TakeName;` — `UPROPERTY()`

### `Plugins/VirtualProduction/MultiUserTakes/Source/ConcertTakeRecorder/Private/ConcertTakeRecorderModule.h` (Private)


#### class `UE::ConcertTakeRecorder::FConcertTakeRecorderModule`  
`class FConcertTakeRecorderModule : public IModuleInterface`  
_L12-39_
- inherits: `IModuleInterface`
- desc: Module that adds multi user synchronization to take recorder.
- L22 _public function_ `static inline FConcertTakeRecorderModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L29 _public prototype_ `virtual void StartupModule() override;`
- L30 _public prototype_ `virtual void ShutdownModule() override;`
- L33 _public function_ `FConcertTakeRecorderManager* GetTakeRecorderManager() const`
- L38 _private member_ `TUniquePtr<FConcertTakeRecorderManager> ConcertManager;` — Synchronizes takes across clients. Valid for the lifetime of the module.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ConcertTakeRecorder` (scope `UE`)

### `Plugins/VirtualProduction/MultiUserTakes/Source/ConcertTakeRecorder/Private/ConcertTakeRecorderStyle.h` (Private)


#### class `FConcertTakeRecorderStyle`  
`class FConcertTakeRecorderStyle`  
_L7-22_
- L10 _public prototype_ `static void Initialize();`
- L12 _public prototype_ `static void Shutdown();`
- L14 _public prototype_ `static TSharedPtr< class ISlateStyle > Get();`
- L16 _public prototype_ `static FName GetStyleSetName();`
- L18 _private prototype_ `static FString InContent(const FString& RelativePath, const ANSICHAR* Extension);`
- L21 _private member_ `static TSharedPtr< class FSlateStyleSet > StyleSet;`

### `Plugins/VirtualProduction/MultiUserTakes/Source/ConcertTakeRecorder/Private/ConcertTakeRecorderSynchronizationCustomization.h` (Private)


#### class `FConcertTakeRecorderSynchronizationCustomization`  
`class FConcertTakeRecorderSynchronizationCustomization : public IDetailCustomization`  
_L22-103_
- inherits: `IDetailCustomization`
- L25 _public typedef_ `using ThisType = FConcertTakeRecorderSynchronizationCustomization;`
- L26 _public function_ `static void OpenMultiUserExcludeProperty()`
- L31 _public function_ `static FOnSyncPropertyValueChanged& OnSyncPropertyValueChanged()`
- L37 _public function_ `void TakeMetaPropertyChanged()`
- L43 _public function_ `void SyncPropertyChanged()`
- L49 _public function_ `void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override`

#### Free symbols / members of external scopes

- L18 _macro_ `#define LOCTEXT_NAMESPACE "ConcertTakeRecorderCustomization"`
- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSyncPropertyValueChanged, bool);`
- L20 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSyncPropertyValueChanged, bool);`
- L96 _function_ `.OnNavigate(FSimpleDelegate::CreateLambda([](){OpenMultiUserExcludeProperty();})) .Text((LOCTEXT("SetExclusionFilter","Set Exclusion Filters"))) .ToolTipText(LOCTEXT("SetExclusionFilterToolTip","Click to edit transaction exclusion filter for MultiUser")) ] ];` (scope `FConcertTakeRecorderSynchronizationCustomization::CustomizeDetails`)

### `Plugins/VirtualProduction/MultiUserTakes/Source/ConcertTakeRecorder/Public/MultiUserTakesFunctionLibrary.h` (Public)


#### class `UMultiUserTakesFunctionLibrary`  
`class UMultiUserTakesFunctionLibrary : public UBlueprintFunctionLibrary`  
_L10-70_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Exposes some of the recorder settings to Blueprints to allow for more editor scripting capabilities.
- L20 _public prototype_ `static bool GetRecordOnClientLocal();` — `UFUNCTION(BlueprintPure, Category = "Multi User Takes")` — Gets the checkbox value in the "Record On Client" column in the settings displayed at the bottom of the "Take Recorder" tab. This is an utility for getting the local client's value; GetRecordOnClient can also be used.
- L27 _public prototype_ `static void SetRecordOnClientLocal(bool bNewValue);` — `UFUNCTION(BlueprintCallable, Category = "Multi User Takes")` — Sets the checkbox value in the "Record On Client" column in the settings displayed at the bottom of the "Take Recorder" tab. This is an utility for setting the local client's value; SetRecordOnClient can also be used.
- L36 _public prototype_ `static bool GetRecordOnClient(const FGuid& ClientEndpointId);` — `UFUNCTION(BlueprintPure, Category = "Multi User Takes")` — Gets the checkbox value in the "Record On Client" column in the settings displayed at the bottom of the "Take Recorder" tab. This function queries the state of any connected client. For the local client, you can also use GetRecordOnClientLocal. @param ClientEndpointId ID of the client. You can get this by using e.g.UMultiUserSubsystem::GetRemoteClientIds or UMultiUserSubsystem::GetLocalClientId.
- L46 _public prototype_ `static void SetRecordOnClient(const FGuid& ClientEndpointId, bool bNewValue);` — `UFUNCTION(BlueprintCallable, Category = "Multi User Takes")` — Sets the checkbox value in the "Record On Client" column in the settings displayed at the bottom of the "Take Recorder" tab. This function queries the state of any connected client. For the local client, you can also use SetRecordOnClientLocal. @param ClientEndpointId ID of the client. You can get this by using e.g.UMultiUserSubsystem::GetRemoteClientIds or UMultiUserSubsystem::GetLocalClientId. @param bNewValue The new value to set
- L53 _public prototype_ `static bool GetSynchronizeTakeRecorderTransactionsLocal();` — `UFUNCTION(BlueprintPure, Category = "Multi User Takes")` — Gets the value of the "SynchronizeTakeRecorderTransactions" checkbox in the settings displayed at the bottom of the "Take Recorder" tab. This is an utility for getting the local client's value; GetSynchronizeTakeRecorderTransactions can also be used.
- L62 _public prototype_ `static bool GetSynchronizeTakeRecorderTransactions(const FGuid& ClientEndpointId);` — `UFUNCTION(BlueprintPure, Category = "Multi User Takes")` — Gets the value of the "SynchronizeTakeRecorderTransactions" checkbox in the settings displayed at the bottom of the "Take Recorder" tab. This function queries the state of any connected client. For the local client, you can also use GetSynchronizeTakeRecorderTransactionsLocal. @param ClientEndpointId ID of the client. You can get this by using e.g.UMultiUserSubsystem::GetRemoteClientIds or UMultiUserSubsystem::GetLocalClientId.
- L69 _public prototype_ `static void SetSynchronizeTakeRecorderTransactionsLocal(bool bNewValue);` — `UFUNCTION(BlueprintCallable, Category = "Multi User Takes")` — Sets the value of the "SynchronizeTakeRecorderTransactions" checkbox in the settings displayed at the bottom of the "Take Recorder" tab. @note Only the value of the local client can be set. Setting of remote clients is not implemented (no technical reason - there just never was a use-case).
