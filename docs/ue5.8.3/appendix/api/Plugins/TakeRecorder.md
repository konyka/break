# Plugins / TakeRecorder

- module root: `Plugins/VirtualProduction/Takes/Source/TakeRecorder`
- headers: 19; symbols: 682
- symbol kinds: class=16, delegate=42, enum=3, enumerator=13, function=20, macro=8, member=155, namespace=7, prototype=409, struct=9
- PrivateDependencyModuleNames: Analytics, AppFramework, AssetDefinition, AssetRegistry, ClassViewer, ContentBrowser, Core, CoreUObject, EditorFramework, EditorStyle, EditorWidgets, Engine, InputCore, LevelEditor, LevelSequence, MovieScene, MovieSceneTools, NamingTokens, NamingTokensUI, PropertyEditor, SequencerCore, Slate, SlateCore, TakeMovieScene, TakesCore, TimeManagement, ToolMenus, ToolWidgets, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: EditorSubsystem, Sequencer, SerializedRecorderInterface, TakeTrackRecorders, TraceLog, UMG
- PublicIncludePathModuleNames: TakeRecorderNamingTokens

### `Plugins/VirtualProduction/Takes/Source/TakeRecorder/Private/Misc/GuardCVar.h` (Private)


#### class `UE::TakeRecorder::TGuardCVar`  
`template<typename TCVarType> class TGuardCVar`  
_L12-50_
- desc: Guard around saving/restoring a console variable value.
- L16 _public function_ `[[nodiscard]] TGuardCVar(const TCHAR* Name, const TCVarType& NewValue) : ConsoleVariable(IConsoleManager::Get().FindConsoleVariable(Name)) , ValueToRestore([this, &NewValue] { if (ensure(ConsoleVariable)) { TCVarType OldValue; ConsoleVariable->GetValue(OldValue); if (OldValue != NewValue) { return TOptional<TCVarType>(OldValue); } } return TOptional<TCVarType>(); }())`
- L19 _public function_ ``
- L38 _public function_ `~TGuardCVar()`
- L48 _private member_ `IConsoleVariable* const ConsoleVariable = nullptr;`
- L49 _private member_ `const TOptional<TCVarType> ValueToRestore;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace TakeRecorder` (scope `UE`)

### `Plugins/VirtualProduction/Takes/Source/TakeRecorder/Private/Recorder/TakeRecorderSubsystemImplementation.h` (Private)


#### class `UTakeRecorderSubsystemImplementation`  
`class UTakeRecorderSubsystemImplementation final : public UObject, public ITakeRecorderSubsystemInterface, public FTickableGameObject`  
_L18-197_
- reflection: `UCLASS()`
- inherits: `UObject,ITakeRecorderSubsystemInterface,FTickableGameObject`
- L24 _public prototype_ `virtual ETickableTickType GetTickableTickType() const override;`
- L25 _public prototype_ `virtual UWorld* GetTickableGameObjectWorld() const override;`
- L26 _public prototype_ `virtual bool IsTickable() const override;`
- L27 _public prototype_ `virtual bool IsTickableWhenPaused() const override;`
- L28 _public prototype_ `virtual bool IsTickableInEditor() const override;`
- L29 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L30 _public prototype_ `virtual TStatId GetStatId() const override;`
- L34 _public prototype_ `void InitializeImplementation(UTakeRecorderSubsystem* OwningSubsystem);` — Perform implementation specific initialization.
- L37 _public prototype_ `void DeinitializeImplementation();` — Perform implementation specific shutdown.
- L40 _public prototype_ `virtual void SetTargetSequence(const FTakeRecorderSequenceParameters& InData = FTakeRecorderSequenceParameters()) override;`
- L41 _public prototype_ `virtual void SetRecordIntoLevelSequence(ULevelSequence* LevelSequence) override;`
- L42 _public prototype_ `virtual bool CanReviewLastRecording() const override;`
- L43 _public prototype_ `virtual bool ReviewLastRecording() override;`
- L44 _public prototype_ `virtual bool StartRecording(bool bOpenSequencer = true, bool bShowErrorMessage = true) override;`
- L45 _public prototype_ `virtual void StopRecording() override;`
- L46 _public prototype_ `virtual void CancelRecording(bool bShowConfirmMessage = true) override;`
- L47 _public prototype_ `virtual void ResetToPendingTake() override;`
- L48 _public prototype_ `virtual void ClearPendingTake() override;`
- L49 _public prototype_ `virtual UTakePreset* GetPendingTake() const override;`
- L50 _public prototype_ `virtual void RevertChanges() override;`
- L51 _public prototype_ `virtual bool IsRecordingUsingExistingSequence() const override;`
- L52 _public prototype_ `virtual UTakeRecorderSource* AddSource(const TSubclassOf<UTakeRecorderSource> InSourceClass) override;`
- L53 _public prototype_ `virtual void RemoveSource(UTakeRecorderSource* InSource) override;`
- L54 _public prototype_ `virtual void ClearSources() override;`
- L55 _public prototype_ `virtual UTakeRecorderSources* GetSources() const override;`
- L56 _public prototype_ `virtual TArrayView<UTakeRecorderSource* const> GetAllSources() const override;`
- L57 _public prototype_ `virtual TArray<UTakeRecorderSource*> GetAllSourcesCopy() const override;`
- L58 _public prototype_ `virtual UTakeRecorderSource* GetSourceByClass(const TSubclassOf<UTakeRecorderSource> InSourceClass) const override;`
- L59 _public prototype_ `virtual void AddSourceForActor(AActor* InActor, bool bReduceKeys = true, bool bShowProgress = true) override;`
- L60 _public prototype_ `virtual void RemoveActorFromSources(AActor* InActor) override;`
- L61 _public prototype_ `virtual AActor* GetSourceActor(UTakeRecorderSource* InSource) const override;`
- L62 _public prototype_ `virtual ETakeRecorderState GetState() const override;`
- L63 _public prototype_ `virtual void SetTakeNumber(int32 InNewTakeNumber, bool bEmitChanged = true) override;`
- L64 _public prototype_ `virtual int32 GetNextTakeNumber(const FString& InSlate) const override;`
- L65 _public prototype_ `virtual void GetNumberOfTakes(const FString& InSlate, int32& OutMaxTake, int32& OutNumTakes) const override;`
- L66 _public prototype_ `virtual void IncrementTakeNumber() override;`
- L67 _public prototype_ `virtual TArray<FAssetData> GetSlates(FName InPackagePath = NAME_None) const override;`
- L68 _public prototype_ `virtual void SetSlateName(const FString& InSlateName, bool bEmitChanged = true) override;`
- L69 _public prototype_ `virtual bool MarkFrame() override;`
- L70 _public prototype_ `virtual FFrameRate GetFrameRate() const override;`
- L71 _public prototype_ `virtual void SetFrameRate(FFrameRate InFrameRate) override;`
- L72 _public prototype_ `virtual void SetFrameRateFromTimecode() override;`
- L73 _public prototype_ `virtual void ImportPreset(const FAssetData& InPreset) override;`
- L74 _public prototype_ `virtual bool IsReviewing() const override;`
- L75 _public prototype_ `virtual bool IsRecording() const override;`
- L76 _public prototype_ `virtual bool TryGetSequenceCountdown(float& OutValue) const override;`
- L77 _public prototype_ `virtual void SetSequenceCountdown(float InSeconds) override;`
- L78 _public prototype_ `virtual TArray<UObject*> GetSourceRecordSettings(UTakeRecorderSource* InSource) const override;`
- L79 _public prototype_ `virtual FTakeRecorderParameters GetGlobalRecordSettings() const override;`
- L80 _public prototype_ `virtual void SetGlobalRecordSettings(const FTakeRecorderParameters& InParameters) override;`
- L81 _public prototype_ `virtual UTakeMetaData* GetTakeMetaData() const override;`
- L82 _public prototype_ `virtual ULevelSequence* GetLevelSequence() const override;`
- L83 _public prototype_ `virtual ULevelSequence* GetSuppliedLevelSequence() const override;`
- L84 _public prototype_ `virtual ULevelSequence* GetRecordingLevelSequence() const override;`
- L85 _public prototype_ `virtual ULevelSequence* GetRecordIntoLevelSequence() const override;`
- L86 _public prototype_ `virtual ULevelSequence* GetLastRecordedLevelSequence() const override;`
- L87 _public prototype_ `virtual UTakePreset* GetTransientPreset() const override;`
- L88 _public prototype_ `virtual ETakeRecorderMode GetTakeRecorderMode() const override;`
- L89 _public prototype_ `virtual UTakeRecorderNamingTokensData* GetNamingTokensData() const override;`
- L90 _public prototype_ `virtual bool HasPendingChanges() const override;`
- L91 _public prototype_ `virtual UClass* GetPresetTargetRecordClass() const override;`
- L92 _public prototype_ `virtual void SetPresetTargetRecordClass(const TSubclassOf<ULevelSequence> InClass) override;`
- L99 _private prototype_ `static UTakePreset* AllocateTransientPreset();` — Allocate the preset required for interacting with this subsystem. Re-uses an existing preset if necessary.
- L102 _private prototype_ `void CacheMetaData();` — Cache the current available metadata.
- L105 _private prototype_ `void UpdateTransientDefaultSlateName();` — Update our transient slate data with the current default slate name.
- L108 _private prototype_ `void SetFrameRateImpl(const FFrameRate& InFrameRate, bool bFromTimecode);` — Sets the frame rate.
- L110 _private prototype_ `void OnAssetRegistryFilesLoaded();`
- L111 _private prototype_ `void OnRecordingInitialized(UTakeRecorder* Recorder);`
- L112 _private prototype_ `void OnRecordingStarted(UTakeRecorder* Recorder);`
- L113 _private prototype_ `void OnRecordingStopped(UTakeRecorder* Recorder);`
- L114 _private prototype_ `void OnRecordingFinished(UTakeRecorder* Recorder);`
- L115 _private prototype_ `void OnRecordingCancelled(UTakeRecorder* Recorder);`
- L116 _private prototype_ `void OnTakeSlateChanged(const FString& InSlate, UTakeMetaData* InTakeMetaData);`
- L117 _private prototype_ `void OnTakeNumberChanged(int32 InTakeNumber, UTakeMetaData* InTakeMetaData);`
- L120 _private prototype_ `void SetLastLevelSequence(ULevelSequence *InSequence);` — Update the last level sequence.
- L123 _private prototype_ `void OnSourceAdded(UTakeRecorderSource* Source);` — Callback when any source is added.
- L126 _private prototype_ `void OnSourceRemoved(UTakeRecorderSource* Source);` — Callback when any source is removed.
- L129 _private prototype_ `void OnSourceModified(UTakeRecorderSource* Source);` — Callback when any sources is modified.
- L132 _private prototype_ `void BindToNamingTokenEvents();` — Setup bindings to our naming tokens.
- L135 _private prototype_ `void UnbindNamingTokensEvents();` — Remove bindings to our naming tokens.
- L138 _private prototype_ `void OnTakeRecorderNamingTokensPreEvaluate(const FNamingTokensEvaluationData& InEvaluationData);` — Called before our naming tokens class evaluates. Used to populate naming token data with our custom token definitions.
- L141 _private prototype_ `void OnTakePresetSettingsChanged();` — Handles the UTakePresetSettings::RecordTargetClass changing: Recreates the transient level sequence if recording a transaction.
- L144 _private prototype_ `void OnPreForceDeleteObjects(const TArray<UObject*>& InObjects);` — Callback when the engine is attempting to force delete objects.
- L148 _private member_ `TWeakObjectPtr<UTakeRecorderSubsystem> OwningSubsystemWeakPtr;` — The public facing engine subsystem we are implementing.
- L151 _private member_ `FTakeRecorderSequenceParameters TargetSequenceData;` — Last data used for initialization.
- L155 _private member_ `TObjectPtr<UTakePreset> TransientPreset;` — `UPROPERTY(Transient)` — A transient preset available for the subsystem.
- L159 _private member_ `TObjectPtr<ULevelSequence> SuppliedLevelSequence;` — `UPROPERTY()` — Current supplied level sequence.
- L163 _private member_ `TObjectPtr<ULevelSequence> RecordIntoLevelSequence;` — `UPROPERTY()` — Current record into level sequence.
- L167 _private member_ `TObjectPtr<ULevelSequence> RecordingLevelSequence;` — `UPROPERTY()` — Current recording level sequence.
- L171 _private member_ `TWeakObjectPtr<ULevelSequence> LastRecordedLevelSequence;` — `UPROPERTY()` — The last recorded level sequence.
- L175 _private member_ `TObjectPtr<UTakeMetaData> TakeMetaData;` — `UPROPERTY()` — Take meta-data cached from the level sequence if it exists.
- L179 _private member_ `TObjectPtr<UTakeMetaData> TransientTakeMetaData;` — `UPROPERTY(Transient)` — Transient take meta-data owned by this subsystem. Only used if none exists on the level sequence already.
- L183 _private member_ `TObjectPtr<UTakeRecorderNamingTokensData> NamingTokensData;` — `UPROPERTY(Transient)` — Stored data relevant to our naming tokens. Managed as UObject for transactions.
- L185 _private member_ `FDelegateHandle OnAssetRegistryFilesLoadedHandle;`
- L186 _private member_ `FDelegateHandle OnRecordingInitializedHandle, OnRecordingStoppedHandle, OnRecordingFinishedHandle, OnRecordingCancelledHandle;`
- L186 _private member_ `FDelegateHandle OnRecordingInitializedHandle, OnRecordingStoppedHandle, OnRecordingFinishedHandle, OnRecordingCancelledHandle;`
- L186 _private member_ `FDelegateHandle OnRecordingInitializedHandle, OnRecordingStoppedHandle, OnRecordingFinishedHandle, OnRecordingCancelledHandle;`
- L186 _private member_ `FDelegateHandle OnRecordingInitializedHandle, OnRecordingStoppedHandle, OnRecordingFinishedHandle, OnRecordingCancelledHandle;`
- L187 _private member_ `FDelegateHandle OnPreForceDeleteObjectsHandle;`
- L190 _private member_ `bool bAutoApplyTakeNumber = false;` — Whether we should auto apply the next available take number when asset discovery has finished or not
- L193 _private member_ `bool bHasTargetSequenceBeenSet = false;` — If SetTargetSequence has been called, and we're fully initialized.
- L196 _private member_ `bool bRecordingUsingExistingSequence = false;` — Helps determine if we are recording into an existing take or using one as a base.

### `Plugins/VirtualProduction/Takes/Source/TakeRecorder/Private/TakeRecorderDirectoryHelpers.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace TakeRecorder` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::TakeRecorder`)
- L10 _prototype_ `bool IsValidPath(const FString& InPathBase);` (scope `UE::TakeRecorder::Private`) — Returns if the provided path is valid for the project
- L13 _prototype_ `FString GetDefaultProjectPath();` (scope `UE::TakeRecorder::Private`) — Return the current default project path.
- L16 _prototype_ `FString ResolvePathToProject(const FString& InPath);` (scope `UE::TakeRecorder::Private`) — Resolve a path relative to the current project.
- L19 _prototype_ `FString RemoveProjectFromPath(const FString& InPath);` (scope `UE::TakeRecorder::Private`) — Remove the /Game or /Project part of the path.

### `Plugins/VirtualProduction/Takes/Source/TakeRecorder/Private/TakeRecorderModule.h` (Private)


#### class `FTakeRecorderModule`  
`class FTakeRecorderModule : public ITakeRecorderModule`  
_L18-84_
- inherits: `ITakeRecorderModule`
- L22 _public prototype_ `virtual void StartupModule() override;`
- L23 _public prototype_ `virtual void ShutdownModule() override;`
- L27 _public prototype_ `virtual void PopulateSourcesMenu(TSharedRef<FExtender> InExtender, UTakeRecorderSources* InSources) const override;`
- L28 _public prototype_ `virtual UTakePreset* GetPendingTake() const override;`
- L29 _public function_ `virtual FOnGenerateWidgetExtensions& GetToolbarExtensionGenerators() override`
- L30 _public function_ `virtual FOnGenerateWidgetExtensions& GetRecordButtonExtensionGenerators() override`
- L31 _public function_ `virtual FOnExternalObjectAddRemoveEvent& GetExternalObjectAddRemoveEventDelegate() override`
- L32 _public function_ `virtual FOnRecordErrorCheck& GetRecordErrorCheckGenerator() override`
- L33 _public function_ `virtual TArray<TWeakObjectPtr<>>& GetExternalObjects() override`
- L34 _public function_ `virtual FLastRecordedLevelSequenceProvider& GetLastLevelSequenceProvider() override`
- L35 _public function_ `virtual FCanReviewLastRecordedLevelSequence& GetCanReviewLastRecordedLevelSequenceDelegate() override`
- L36 _public prototype_ `virtual void RegisterExternalObject(UObject* InExternalObject) override;`
- L37 _public prototype_ `virtual void UnregisterExternalObject(UObject* InExternalObject) override;`
- L38 _public function_ `virtual FOnForceSaveAsPreset& OnForceSaveAsPreset() override`
- L39 _public prototype_ `virtual FDelegateHandle RegisterSourcesMenuExtension(const FOnExtendSourcesMenu& InExtension) override;`
- L40 _public prototype_ `virtual void RegisterSourcesExtension(const FSourceExtensionData& InData) override;`
- L41 _public prototype_ `virtual void UnregisterSourcesExtension() override;`
- L42 _public prototype_ `virtual void UnregisterSourcesMenuExtension(FDelegateHandle Handle) override;`
- L43 _public prototype_ `virtual void RegisterSettingsObject(UObject* InSettingsObject) override;`
- L44 _public function_ `virtual FSourceExtensionData& GetSourcesExtensionData() override`
- L49 _private prototype_ `void RegisterSettings();`
- L51 _private prototype_ `void RegisterSerializedRecorder();`
- L52 _private prototype_ `void UnregisterSerializedRecorder() const;`
- L54 _private prototype_ `void OnEditorClose();`
- L58 _private prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnExtendSourcesMenuEvent, TSharedRef<FExtender>, UTakeRecorderSources*);`
- L60 _private member_ `FOnExtendSourcesMenuEvent SourcesMenuExtenderEvent;`
- L61 _private member_ `FOnGenerateWidgetExtensions ToolbarExtensionGenerators;`
- L62 _private member_ `FOnGenerateWidgetExtensions ButtonExtensionGenerators;`
- L63 _private member_ `FLastRecordedLevelSequenceProvider LastLevelSequenceProvider;`
- L64 _private member_ `FCanReviewLastRecordedLevelSequence CanReviewLastRecordedSequence;`
- L66 _private member_ `FOnExternalObjectAddRemoveEvent ExternalObjectAddRemoveEvent;`
- L67 _private member_ `FOnForceSaveAsPreset ForceSaveAsPresetEvent;`
- L68 _private member_ `FOnRecordErrorCheck RecordErrorCheck;`
- L70 _private member_ `FDelegateHandle LevelEditorLayoutExtensionHandle;`
- L71 _private member_ `FDelegateHandle LevelEditorTabManagerChangedHandle;`
- L72 _private member_ `FDelegateHandle ModulesChangedHandle;`
- L74 _private member_ `TSharedPtr<FSerializedRecorder> SerializedRecorder;`
- L77 _private member_ `TArray<TWeakObjectPtr<>> ExternalObjects;` — Extra class default objects that should appear in the Take Recorder panel.
- L83 _private member_ `FSourceExtensionData SourceExtensionData;` — Registered extensions for the source module. We only use a single struct rather than container as only the source module should be utilizing this.

#### Free symbols / members of external scopes

- L58 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnExtendSourcesMenuEvent, TSharedRef<FExtender>, UTakeRecorderSources*);`

### `Plugins/VirtualProduction/Takes/Source/TakeRecorder/Public/ITakeRecorderDropHandler.h` (Public)


#### struct `ITakeRecorderDropHandler`  
`struct ITakeRecorderDropHandler : public IModularFeature`  
_L14-45_
- inherits: `IModularFeature`
- desc: Interface registerable through IModularFeatures for extendig drag/drop support for the take recorder sources panel
- L17 _public member_ `static FName ModularFeatureName;` — The feature name under which all ITakeRecorderDropHandlers should be registered
- L22 _public prototype_ `static TArray<ITakeRecorderDropHandler*> GetDropHandlers();` — Get all the currently registered drop handlers
- L26 _public prototype_ `virtual ~ITakeRecorderDropHandler() = default;`
- L35 _public prototype_ `virtual void HandleOperation(TSharedPtr<FDragDropOperation> InOperation, UTakeRecorderSources* Sources) = 0;` — Handle a drag drop operation for the specified sources. @param InOperation      The drag drop operation to be handled @param Sources          The sources to add any dropped items to
- L44 _public prototype_ `virtual bool CanHandleOperation(TSharedPtr<FDragDropOperation> InOperation, UTakeRecorderSources* Sources) = 0;` — Determine whether this drop handler can handle the specified operation @param InOperation      The drag drop operation to be handled @param Sources          The sources to add any dropped items to

### `Plugins/VirtualProduction/Takes/Source/TakeRecorder/Public/ITakeRecorderModule.h` (Public)


#### class `ITakeRecorderModule`  
`class ITakeRecorderModule : public IModuleInterface`  
_L54-201_
- inherits: `IModuleInterface`
- desc: Public module interface for the Take Recorder module
- L61 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnExternalObjectAddRemoveEvent, UObject *, bool);` — Delegate called when an external object is registered for the take recorder panel. The boolean parameter indicates if the object was added. It is true if added and false if removed.
- L92 _public member_ `static FName TakeRecorderTabName;` — The name under which the take recorder tab is registered and invoked
- L95 _public member_ `static FText TakeRecorderTabLabel;` — The default label for the take recorder tab
- L98 _public member_ `static FName TakesBrowserTabName;` — The tab name for the takes browser tab
- L101 _public member_ `static FText TakesBrowserTabLabel;` — The default label for the takes browser
- L104 _public member_ `static FName TakesBrowserInstanceName;` — The Takes Browser Content Browser Instance Name
- L106 _public function_ `static inline ITakeRecorderModule& Get()`
- L111 _public function_ `static inline bool IsAvailable()`
- L116 _public prototype_ `virtual void PopulateSourcesMenu(TSharedRef<FExtender> InExtender, UTakeRecorderSources* InSources) const = 0;`
- L119 _public prototype_ `virtual UTakePreset* GetPendingTake() const = 0;` — Get the current pending take.
- L124 _public prototype_ `virtual FDelegateHandle RegisterSourcesMenuExtension(const FOnExtendSourcesMenu& InExtension) = 0;` — Register a new extension callback for the 'Add Source' menu
- L129 _public prototype_ `virtual void RegisterSourcesExtension(const FSourceExtensionData& InData) = 0;` — Register generic extensions for sources. We only allow one extension as this should be handled by the sources module.
- L134 _public prototype_ `virtual void UnregisterSourcesExtension() = 0;` — Unregister the source extension.
- L139 _public prototype_ `virtual FOnForceSaveAsPreset& OnForceSaveAsPreset() = 0;` — Get the delegate for handling saving of preset data.
- L144 _public prototype_ `virtual FLastRecordedLevelSequenceProvider& GetLastLevelSequenceProvider() = 0;` — Get the delegate for providing the current level sequence to the take recorder panel.
- L149 _public prototype_ `virtual FCanReviewLastRecordedLevelSequence& GetCanReviewLastRecordedLevelSequenceDelegate() = 0;` — Provides the take recorder panel state of review last recording.
- L154 _public prototype_ `virtual void UnregisterSourcesMenuExtension(FDelegateHandle Handle) = 0;` — Unregister a previously registered extension callback for the 'Add Source' menu
- L160 _public prototype_ `virtual void RegisterSettingsObject(UObject* InSettingsObject) = 0;` — Register a new class default object that should appear on the take recorder project settings
- L166 _public prototype_ `virtual void RegisterExternalObject(UObject* InExternalObject) = 0;` — Register a new class default object that should appear on the take recorder panel.
- L171 _public prototype_ `virtual void UnregisterExternalObject(UObject* InExternalObject) = 0;` — Unregister a new class default object that should appear on the take recorder panel.
- L177 _public prototype_ `virtual FOnGenerateWidgetExtensions& GetToolbarExtensionGenerators() = 0;` — Get the toolbar extension generators. Usage: Bind a handler that adds a widget to the out array parameter.
- L183 _public prototype_ `virtual FOnGenerateWidgetExtensions& GetRecordButtonExtensionGenerators() = 0;` — Get the toolbar extension generators. Usage: Bind a handler that adds a widget to the out array parameter.
- L188 _public prototype_ `virtual FOnRecordErrorCheck& GetRecordErrorCheckGenerator() = 0;` — Get the delegate for reporting any error conditions in recording state.
- L193 _public prototype_ `virtual FOnExternalObjectAddRemoveEvent& GetExternalObjectAddRemoveEventDelegate() = 0;` — Get the event notifier when an external object has been added or removed.
- L198 _public prototype_ `virtual TArray<TWeakObjectPtr<>>& GetExternalObjects() = 0;` — Get the take external objects registered to the take recorder.
- L200 _public prototype_ `virtual FSourceExtensionData& GetSourcesExtensionData() = 0;`

#### struct `ITakeRecorderModule::FSourceExtensionData`  
`struct FSourceExtensionData`  
_L64-89_
- desc: Relevant data for the sources module.
- L69 _public prototype_ `DECLARE_DELEGATE_FourParams(FAddActorSource, UTakeRecorderSources* TakeRecorderSources, TArrayView<AActor* const> ActorsToRecord, bool bReduceKeys, bool bShowProgress);` — Delegate for sources module to bind to when adding an actor.
- L74 _public prototype_ `DECLARE_DELEGATE_TwoParams(FRemoveActorSource, UTakeRecorderSources* TakeRecorderSources, TArrayView<AActor* const> ActorsToRemove);` — Delegate for sources module to bind to when removing an actor.
- L79 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(AActor*, FGetSourceActor, UTakeRecorderSource* Source);` — Delegate to retrieve the actor of a source.
- L82 _public member_ `FAddActorSource OnAddActorSource;` — An actor is being added as a source.
- L85 _public member_ `FRemoveActorSource OnRemoveActorSource;` — An actor is being removed as a source.
- L88 _public member_ `FGetSourceActor OnGetSourceActor;` — The actor belonging to a source should be retrieved.

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnExtendSourcesMenu, TSharedRef<FExtender>, UTakeRecorderSources*) DECLARE_MULTICAST_DELEGATE_OneParam(FOnGenerateWidgetExtensions, TArray<TSharedRef<class SWidget>>& );`
- L18 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnExtendSourcesMenu, TSharedRef<FExtender>, UTakeRecorderSources*) DECLARE_MULTICAST_DELEGATE_OneParam(FOnGenerateWidgetExtensions, TArray<TSharedRef<class SWidget>>& );`
- L24 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGenerateWidgetExtensions, TArray<TSharedRef<class SWidget>>& );` — Delegate called to add extensions to the take recorder toolbar. Usage: Bind a handler that adds a widget to the out array parameter.
- L32 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRecordErrorCheck, FText &);` — Delegate called to to validate if recording can take place. Usage: Bind a handler that will supply a FText string when Take Recorder is in an invalid condition. The text will be displayed the user. If there is no error condition then the FText string must be empty.
- L32 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRecordErrorCheck, FText &);` — Delegate called to to validate if recording can take place. Usage: Bind a handler that will supply a FText string when Take Recorder is in an invalid condition. The text will be displayed the user. If there is no error condition then the FText string must be empty.
- L38 _delegate_ `DECLARE_DELEGATE(FOnForceSaveAsPreset);` — Delegate to request preset save.  Note this is only a temporary workaround until Concert plugin supports instanced properties.
- L38 _prototype_ `DECLARE_DELEGATE(FOnForceSaveAsPreset);` — Delegate to request preset save.  Note this is only a temporary workaround until Concert plugin supports instanced properties.
- L44 _delegate_ `DECLARE_DELEGATE_OneParam(FLastRecordedLevelSequenceProvider, ULevelSequence*);` — Delegate to provide last recorded level sequence.
- L44 _prototype_ `DECLARE_DELEGATE_OneParam(FLastRecordedLevelSequenceProvider, ULevelSequence*);` — Delegate to provide last recorded level sequence.
- L49 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FCanReviewLastRecordedLevelSequence);` — Delegate to indicate if it is safe to review the last recorded level sequence.
- L49 _prototype_ `DECLARE_DELEGATE_RetVal(bool, FCanReviewLastRecordedLevelSequence);` — Delegate to indicate if it is safe to review the last recorded level sequence.
- L61 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnExternalObjectAddRemoveEvent, UObject *, bool);` — Delegate called when an external object is registered for the take recorder panel. The boolean parameter indicates if the object was added. It is true if added and false if removed.
- L69 _delegate_ `DECLARE_DELEGATE_FourParams(FAddActorSource, UTakeRecorderSources* TakeRecorderSources, TArrayView<AActor* const> ActorsToRecord, bool bReduceKeys, bool bShowProgress);` — Delegate for sources module to bind to when adding an actor.
- L74 _delegate_ `DECLARE_DELEGATE_TwoParams(FRemoveActorSource, UTakeRecorderSources* TakeRecorderSources, TArrayView<AActor* const> ActorsToRemove);` — Delegate for sources module to bind to when removing an actor.
- L79 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(AActor*, FGetSourceActor, UTakeRecorderSource* Source);` — Delegate to retrieve the actor of a source.

### `Plugins/VirtualProduction/Takes/Source/TakeRecorder/Public/ITakeRecorderTabContent.h` (Public)


#### class `ITakeRecorderTabContent`  
`class ITakeRecorderTabContent : public SCompoundWidget`  
_L23-154_
- inherits: `SCompoundWidget`
- desc: Interface for the Take Recorder tab's top-level content widget.
- L27 _public function_ `SLATE_BEGIN_ARGS(ITakeRecorderTabContent)`
- L30 _public prototype_ `virtual ~ITakeRecorderTabContent() override = default;`
- L33 _public prototype_ `virtual FText GetTitle() const = 0;` — Returns the display title shown in the tab.
- L36 _public prototype_ `virtual const FSlateBrush* GetIcon() const = 0;` — Returns the icon brush shown in the tab.
- L42 _public prototype_ `virtual TOptional<ETakeRecorderPanelMode> GetMode() const = 0;` — Returns the current panel mode, or an unset optional when no child widget has been constructed yet (e.g. during the one-tick deferred initialization).
- L48 _public prototype_ `virtual void SetupForRecording(ULevelSequence* LevelSequenceAsset) = 0;` — Replaces the tab content with a new STakeRecorderPanel configured for recording, using the provided level sequence as the base sequence.
- L55 _public prototype_ `virtual void SetupForRecording(UTakePreset* BasePreset) = 0;` — Replaces the tab content with a new STakeRecorderPanel configured for recording, using the provided take preset as the starting configuration. Pass nullptr to use the default recording setup.
- L62 _public prototype_ `virtual void SetupForRecordingInto(ULevelSequence* LevelSequenceAsset) = 0;` — Replaces the tab content with a new STakeRecorderPanel that will record directly into the provided existing level sequence, appending new data rather than creating a fresh take.
- L67 _public prototype_ `virtual void SetupForEditing(UTakePreset* Preset) = 0;` — Opens the provided take preset for editing in an STakePresetAssetEditor.
- L74 _public prototype_ `virtual void SetupForEditing(TSharedPtr<FTakePresetToolkit> InToolkit) = 0;` — Replaces the tab content with an STakePresetAssetEditor driven by the provided toolkit.
- L81 _public prototype_ `virtual void SetupForViewing(ULevelSequence* LevelSequence) = 0;` — Replaces the tab content with a read-only STakeRecorderPanel showing the provided level sequence.
- L87 _public prototype_ `virtual ULevelSequence* GetLevelSequence() const = 0;` — Returns the level sequence currently active in the panel or asset editor, or nullptr if neither is valid.
- L93 _public prototype_ `virtual ULevelSequence* GetLastRecordedLevelSequence() const = 0;` — Returns the level sequence produced by the most recent completed recording, or nullptr if no recording has completed or no panel is active.
- L100 _public prototype_ `virtual UTakeMetaData* GetTakeMetaData() const = 0;` — Returns the take metadata for the active level sequence, sourced from either the asset editor's sequence or the recorder panel. Returns nullptr if no metadata exists or no child widget is active.
- L106 _public prototype_ `virtual FFrameRate GetFrameRate() const = 0;` — Returns the current recording frame rate as reported by the cockpit widget. Returns a default-constructed FFrameRate if no panel or cockpit is available.
- L112 _public prototype_ `virtual void SetFrameRate(FFrameRate InFrameRate) = 0;` — Sets the recording frame rate on the cockpit widget. Has no effect if no panel or cockpit is currently active.
- L118 _public prototype_ `virtual void SetFrameRateFromTimecode(bool bInFromTimecode) = 0;` — Configures the cockpit to derive its frame rate from the current timecode source when bInFromTimecode is true. Has no effect if no panel or cockpit is currently active.
- L124 _public prototype_ `virtual UTakeRecorderSources* GetSources() const = 0;` — Returns the UTakeRecorderSources associated with the active level sequence, looked up via ITakeRecorderSourcesManager. Returns nullptr if no level sequence is active.
- L131 _public prototype_ `virtual void StartRecording() const = 0;` — Starts a recording session via the cockpit widget. Does nothing if the cockpit is unavailable, a recording is already in progress, the panel is in review mode, or CanStartRecording returns false.
- L137 _public prototype_ `virtual void StopRecording() const = 0;` — Stops the active recording session via the cockpit widget. Does nothing if the cockpit is unavailable or no recording is in progress.
- L143 _public prototype_ `virtual void ClearPendingTake() = 0;` — Clears any pending take state from the active recorder panel. Has no effect if no panel is currently active.
- L150 _public prototype_ `virtual bool CanStartRecording(FText& ErrorText) const = 0;` — Returns whether a recording can be started, delegating to the cockpit widget. Populates ErrorText with a human-readable reason when returning false. Returns false with an appropriate message if no panel or cockpit is available.
- L153 _public prototype_ `virtual const TWeakPtr<STakeRecorderPanel>& GetTakeRecorderPanel() const = 0;` — Returns a weak pointer to the active STakeRecorderPanel, or an invalid pointer if the asset editor is showing instead.

### `Plugins/VirtualProduction/Takes/Source/TakeRecorder/Public/Recorder/ITakeRecorderSubsystemInterface.h` (Public)


#### class `UTakeRecorderSubsystemInterface`  
`class UTakeRecorderSubsystemInterface : public UInterface`  
_L18-21_
- reflection: `UINTERFACE(MinimalAPI, NotBlueprintable)`
- inherits: `UInterface`

#### class `ITakeRecorderSubsystemInterface`  
`class ITakeRecorderSubsystemInterface`  
_L24-86_
- desc: Interface for the public Take Recorder Subsystem and the private implementation.
- L29 _public prototype_ `virtual void SetTargetSequence(const FTakeRecorderSequenceParameters& InData = FTakeRecorderSequenceParameters()) = 0;`
- L30 _public prototype_ `virtual void SetRecordIntoLevelSequence(ULevelSequence* LevelSequence) = 0;`
- L31 _public prototype_ `virtual bool CanReviewLastRecording() const = 0;`
- L32 _public prototype_ `virtual bool ReviewLastRecording() = 0;`
- L33 _public prototype_ `virtual bool StartRecording(bool bOpenSequencer = true, bool bShowErrorMessage = true) = 0;`
- L34 _public prototype_ `virtual void StopRecording() = 0;`
- L35 _public prototype_ `virtual void CancelRecording(bool bShowConfirmMessage = true) = 0;`
- L36 _public prototype_ `virtual void ResetToPendingTake() = 0;`
- L37 _public prototype_ `virtual void ClearPendingTake() = 0;`
- L38 _public prototype_ `virtual UTakePreset* GetPendingTake() const = 0;`
- L39 _public prototype_ `virtual void RevertChanges() = 0;`
- L40 _public prototype_ `virtual bool IsRecordingUsingExistingSequence() const = 0;`
- L43 _public prototype_ `virtual UTakeRecorderSource* AddSource(const TSubclassOf<UTakeRecorderSource> InSourceClass) = 0;`
- L44 _public prototype_ `virtual void RemoveSource(UTakeRecorderSource* InSource) = 0;`
- L45 _public prototype_ `virtual void ClearSources() = 0;`
- L46 _public prototype_ `virtual UTakeRecorderSources* GetSources() const = 0;`
- L47 _public prototype_ `virtual TArrayView<UTakeRecorderSource* const> GetAllSources() const = 0;`
- L48 _public prototype_ `virtual TArray<UTakeRecorderSource*> GetAllSourcesCopy() const = 0;`
- L49 _public prototype_ `virtual UTakeRecorderSource* GetSourceByClass(const TSubclassOf<UTakeRecorderSource> InSourceClass) const = 0;`
- L50 _public prototype_ `virtual void AddSourceForActor(AActor* InActor, bool bReduceKeys = true, bool bShowProgress = true) = 0;`
- L51 _public prototype_ `virtual void RemoveActorFromSources(AActor* InActor) = 0;`
- L52 _public prototype_ `virtual AActor* GetSourceActor(UTakeRecorderSource* InSource) const = 0;`
- L55 _public prototype_ `virtual ETakeRecorderState GetState() const = 0;`
- L56 _public prototype_ `virtual void SetTakeNumber(int32 InNewTakeNumber, bool bEmitChanged = true) = 0;`
- L57 _public prototype_ `virtual int32 GetNextTakeNumber(const FString& InSlate) const = 0;`
- L58 _public prototype_ `virtual void GetNumberOfTakes(const FString& InSlate, int32& OutMaxTake, int32& OutNumTakes) const = 0;`
- L59 _public prototype_ `virtual void IncrementTakeNumber() = 0;`
- L60 _public prototype_ `virtual TArray<FAssetData> GetSlates(FName InPackagePath = NAME_None) const = 0;`
- L61 _public prototype_ `virtual void SetSlateName(const FString& InSlateName, bool bEmitChanged = true) = 0;`
- L62 _public prototype_ `virtual bool MarkFrame() = 0;`
- L63 _public prototype_ `virtual FFrameRate GetFrameRate() const = 0;`
- L64 _public prototype_ `virtual void SetFrameRate(FFrameRate InFrameRate) = 0;`
- L65 _public prototype_ `virtual void SetFrameRateFromTimecode() = 0;`
- L66 _public prototype_ `virtual void ImportPreset(const FAssetData& InPreset) = 0;`
- L67 _public prototype_ `virtual bool IsReviewing() const = 0;`
- L68 _public prototype_ `virtual bool IsRecording() const = 0;`
- L69 _public prototype_ `virtual bool TryGetSequenceCountdown(float& OutValue) const = 0;`
- L70 _public prototype_ `virtual void SetSequenceCountdown(float InSeconds) = 0;`
- L71 _public prototype_ `virtual TArray<UObject*> GetSourceRecordSettings(UTakeRecorderSource* InSource) const = 0;`
- L72 _public prototype_ `virtual FTakeRecorderParameters GetGlobalRecordSettings() const = 0;`
- L73 _public prototype_ `virtual void SetGlobalRecordSettings(const FTakeRecorderParameters& InParameters) = 0;`
- L74 _public prototype_ `virtual UTakeMetaData* GetTakeMetaData() const = 0;`
- L75 _public prototype_ `virtual ULevelSequence* GetLevelSequence() const = 0;`
- L76 _public prototype_ `virtual ULevelSequence* GetSuppliedLevelSequence() const = 0;`
- L77 _public prototype_ `virtual ULevelSequence* GetRecordingLevelSequence() const = 0;`
- L78 _public prototype_ `virtual ULevelSequence* GetRecordIntoLevelSequence() const = 0;`
- L79 _public prototype_ `virtual ULevelSequence* GetLastRecordedLevelSequence() const = 0;`
- L80 _public prototype_ `virtual UTakePreset* GetTransientPreset() const = 0;`
- L81 _public prototype_ `virtual ETakeRecorderMode GetTakeRecorderMode() const = 0;`
- L82 _public prototype_ `virtual UTakeRecorderNamingTokensData* GetNamingTokensData() const = 0;`
- L83 _public prototype_ `virtual bool HasPendingChanges() const = 0;`
- L84 _public prototype_ `virtual UClass* GetPresetTargetRecordClass() const = 0;`
- L85 _public prototype_ `virtual void SetPresetTargetRecordClass(const TSubclassOf<ULevelSequence> InClass) = 0;`

### `Plugins/VirtualProduction/Takes/Source/TakeRecorder/Public/Recorder/TakeRecorder.h` (Public)


#### enum `ETakeRecorderState`  
`enum class ETakeRecorderState : uint8`  
_L37-46_
- reflection: `UENUM(BlueprintType)`
- L39 _public enumerator_ `PreInitialization`
- L40 _public enumerator_ `CountingDown`
- L41 _public enumerator_ `PreRecord`
- L42 _public enumerator_ `TickingAfterPre`
- L43 _public enumerator_ `Started`
- L44 _public enumerator_ `Stopped`
- L45 _public enumerator_ `Cancelled`

#### struct `FTakeRecorderParameterOverride`  
`struct FTakeRecorderParameterOverride`  
_L60-66_
- L62 _public prototype_ `void RegisterHandler(FName OverrideName, FTakeRecorderParameterDelegate Delegate);`
- L63 _public prototype_ `void UnregisterHandler(FName OverrideName);`
- L65 _public member_ `TMap<FName, FTakeRecorderParameterDelegate> Delegates;`

#### class `UTakeRecorder`  
`class UTakeRecorder : public UObject`  
_L71-352_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L77 _public prototype_ `UTakeRecorder(const FObjectInitializer& ObjInit);`
- L84 _public prototype_ `static UTakeRecorder* GetActiveRecorder();` — Retrieve the currently active take recorder instance
- L89 _public prototype_ `static FOnTakeRecordingInitialized& OnRecordingInitialized();` — Retrieve a multi-cast delegate that is triggered when a new recording begins
- L95 _public prototype_ `static FTakeRecorderParameterOverride& TakeInitializeParameterOverride();` — On take initialization overrides provide a mechanism to adjust parameter values when a new take is initialized.
- L103 _public function_ `float GetCountdownSeconds() const` — `UFUNCTION(BlueprintCallable, Category="Take Recorder")` — Access the number of seconds remaining before this recording will start
- L112 _public prototype_ `void SetCountdown(float InSeconds);` — `UFUNCTION(BlueprintCallable, Category="Take Recorder")` — Sets the current countdown time in seconds.
- L118 _public function_ `ULevelSequence* GetSequence() const` — `UFUNCTION(BlueprintCallable, Category="Take Recorder")` — Access the sequence asset that this recorder is recording into
- L127 _public function_ `ETakeRecorderState GetState() const` — `UFUNCTION(BlueprintCallable, Category="Take Recorder")` — Get the current state of this recorder
- L135 _public prototype_ `void SetDisableSaveTick( bool );` — Disable saving data on tick event. This make the TakeRecord a no-op.
- L149 _public prototype_ `bool Initialize(ULevelSequence* LevelSequenceBase, UTakeRecorderSources* Sources, UTakeMetaData* MetaData, const FTakeRecorderParameters& InParameters, FText* OutError = nullptr);` — Initialize a new recording with the specified parameters. Fails if another recording is currently in progress. @param LevelSequenceBase   A level sequence to use as a base set-up for the take @param Sources             The sources to record from @param MetaData            Meta data to store on the recorded level sequence asset for this take @param InParameters        Configurable parameters for this instance of the recorder @param OutError            Error string to receive for context @return True if the recording process was successfully initialized, false otherwise
- L154 _public prototype_ `void Stop();` — Called to stop the recording
- L159 _public prototype_ `void Cancel();` — Called to cancel the recording
- L164 _public prototype_ `FOnTakeRecordingPreInitialize& OnRecordingPreInitialize();` — Retrieve a multi-cast delegate that is triggered before initialization occurs (ie. when the recording button is pressed and before the countdown starts)
- L169 _public prototype_ `FOnTakeRecordingStarted& OnRecordingStarted();` — Retrieve a multi-cast delegate that is triggered when this recording starts
- L174 _public prototype_ `FOnTakeRecordingStopped& OnRecordingStopped();` — Retrieve a multi-cast delegate that is triggered when this recording is stopped
- L179 _public prototype_ `FOnTakeRecordingFinished& OnRecordingFinished();` — Retrieve a multi-cast delegate that is triggered when this recording finishes
- L184 _public prototype_ `FOnTakeRecordingCancelled& OnRecordingCancelled();` — Retrieve a multi-cast delegate that is triggered when this recording is cancelled
- L189 _public prototype_ `FOnStartPlayFrameModified& OnStartPlayFrameModified();` — Retrieve a multi-cast delegate that is triggered when a delta time has been applied to the Movie Scene
- L194 _public prototype_ `FOnTickRecording& OnTickRecording();` — Retrieve a multi-cast delegate that is triggered when this recording ticks
- L201 _private prototype_ `void PreRecord();` — Called after the countdown to PreRecord
- L206 _private prototype_ `void Start();` — Called after PreRecord To Start
- L211 _private prototype_ `void StopInternal(const bool bCancelled);` — Stop or cancel
- L216 _private prototype_ `void Tick(float DeltaTime);` — Ticked by a tickable game object to performe any necessary time-sliced logic
- L222 _private prototype_ `void HandlePIE(bool bIsSimulating);` — Called if we're currently recording a PIE world that has been shut down or if we start PIE in a non-PIE world. Bound in Initialize, and unbound in Stop.
- L228 _private prototype_ `bool CreateDestinationAsset(const TCHAR* AssetPathFormat, ULevelSequence* LevelSequenceBase, UTakeRecorderSources* Sources, UTakeMetaData* MetaData, FText* OutError, bool bOpenSequencer = true);` — Create a new destination asset to record into based on the parameters
- L233 _private prototype_ `bool SetupDestinationAsset(const FTakeRecorderParameters& InParameters, ULevelSequence* LevelSequenceBase, UTakeRecorderSources* Sources, UTakeMetaData* MetaData, FText* OutError, bool bOpenSequencer = true);` — Setup a existing asset to record into based on the parameters
- L238 _private prototype_ `void DiscoverSourceWorld();` — Discovers the source world to record from, and initializes it for recording
- L243 _private prototype_ `void InitializeFromParameters();` — Called to perform any initialization based on the user-provided parameters
- L249 _private prototype_ `bool ShouldShowNotifications();` — Returns true if notification widgets should be shown when recording. It takes into account TakeRecorder project settings, the command line, and global unattended settings.
- L254 _private prototype_ `FQualifiedFrameTime GetRecordTime() const;` — The time at which to record. Taken from the Sequencer global time, otherwise based on timecode
- L257 _private prototype_ `void InternalTick(float DeltaTime);` — Called by Tick and Start to make sure we record at start
- L259 _private prototype_ `virtual UWorld* GetWorld() const override;`
- L264 _private member_ `float CountdownSeconds;` — The number of seconds remaining before Start() should be called
- L267 _private member_ `ETakeRecorderState State;` — The state of this recorder instance
- L270 _private member_ `FFrameTime CurrentFrameTime;` — FFrameTime in MovieScene Resolution we are at
- L273 _private member_ `FTimecode TimecodeAtStart;` — Timecode at the start of recording
- L276 _private member_ `TOptional<FFrameNumber> StopRecordingFrame;` — Optional frame to stop recording at
- L280 _private member_ `TObjectPtr<ULevelSequence> SequenceAsset;` — `UPROPERTY(transient)` — The asset that we should output recorded data into
- L284 _private member_ `TObjectPtr<UTakeRecorderOverlayWidget> OverlayWidget;` — `UPROPERTY(transient)` — The overlay widget for this recording
- L288 _private member_ `TWeakObjectPtr<UWorld> WeakWorld;` — `UPROPERTY(transient)` — The world that we are recording within
- L292 _private member_ `FTakeRecorderParameters Parameters;` — `UPROPERTY()` — Parameters for the recorder - marked up as a uproperty to support reference collection
- L295 _private member_ `TArray<TFunction<void()>> OnStopCleanup;` — Anonymous array of cleanup functions to perform when a recording has finished
- L298 _private member_ `FOnTakeRecordingPreInitialize OnRecordingPreInitializeEvent;` — Triggered before the recorder is initialized
- L301 _private member_ `FOnTakeRecordingStarted OnRecordingStartedEvent;` — Triggered when this recorder starts
- L304 _private member_ `FOnTakeRecordingStopped OnRecordingStoppedEvent;` — Triggered when this recorder is stopped
- L307 _private member_ `FOnTakeRecordingFinished OnRecordingFinishedEvent;` — Triggered when this recorder finishes
- L310 _private member_ `FOnTakeRecordingCancelled OnRecordingCancelledEvent;` — Triggered when this recorder is cancelled
- L313 _private member_ `FOnStartPlayFrameModified OnFrameModifiedEvent;` — Triggered when the movie scene is adjusted.
- L316 _private member_ `FOnTickRecording OnTickRecordingEvent;` — Triggered when this recorder ticks
- L320 _private member_ `TWeakPtr<ISequencer> WeakSequencer;` — Sequencer ptr that controls playback of the destination asset during the recording
- L324 _private member_ `int32 NumberOfTicksAfterPre;` — Due a few ticks after the pre so we are set up with asset creation
- L333 _private prototype_ `static bool SetActiveRecorder(UTakeRecorder* NewActiveRecorder);` — Set the currently active take recorder instance
- L336 _private member_ `static FOnTakeRecordingInitialized OnRecordingInitializedEvent;` — Event to trigger when a new recording is initialized
- L340 _private member_ `FManifestSerializer ManifestSerializer;`
- L343 _private member_ `EAllowEditsMode CachedAllowEditsMode;`
- L344 _private member_ `EAutoChangeMode CachedAutoChangeMode;`
- L347 _private member_ `EUpdateClockSource CachedClockSource;`
- L349 _private member_ `TRange<FFrameNumber> CachedPlaybackRange;`
- L351 _private member_ `TUniquePtr<UE::MovieScene::FScopedVolatilityManagerSuppression> CompileSuppression;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API TAKERECORDER_API`
- L31 _namespace_ `namespace UE`
- L31 _namespace_ `namespace MovieScene` (scope `UE`)
- L48 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTakeRecordingPreInitialize, UTakeRecorder*);`
- L48 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTakeRecordingPreInitialize, UTakeRecorder*);`
- L49 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTakeRecordingInitialized, UTakeRecorder*);`
- L49 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTakeRecordingInitialized, UTakeRecorder*);`
- L50 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTakeRecordingStarted, UTakeRecorder*);`
- L50 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTakeRecordingStarted, UTakeRecorder*);`
- L51 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTakeRecordingStopped, UTakeRecorder*);`
- L51 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTakeRecordingStopped, UTakeRecorder*);`
- L52 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTakeRecordingFinished, UTakeRecorder*);`
- L52 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTakeRecordingFinished, UTakeRecorder*);`
- L53 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTakeRecordingCancelled, UTakeRecorder*);`
- L53 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTakeRecordingCancelled, UTakeRecorder*);`
- L54 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStartPlayFrameModified, UTakeRecorder*, const FFrameNumber& StartFrame);`
- L54 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStartPlayFrameModified, UTakeRecorder*, const FFrameNumber& StartFrame);`
- L55 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTickRecording, UTakeRecorder*, const FQualifiedFrameTime&);`
- L55 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTickRecording, UTakeRecorder*, const FQualifiedFrameTime&);`
- L56 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnPendingTakeCleared);`
- L56 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnPendingTakeCleared);`
- L58 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FTakeRecorderParameters, FTakeRecorderParameterDelegate,const FTakeRecorderParameters&);`
- L58 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FTakeRecorderParameters, FTakeRecorderParameterDelegate,const FTakeRecorderParameters&);`
- L68 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(ManifestSerialization, Verbose, All);`
- L68 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(ManifestSerialization, Verbose, All);`

### `Plugins/VirtualProduction/Takes/Source/TakeRecorder/Public/Recorder/TakeRecorderBlueprintLibrary.h` (Public)


#### class `UTakeRecorderBlueprintLibrary`  
`class UTakeRecorderBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L25-146_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L36 _public prototype_ `static bool IsTakeRecorderEnabled();` — `UFUNCTION(BlueprintPure, Category="Take Recorder")` — Is the Take Recorder enabled in the build
- L48 _public prototype_ `static UTakeRecorder* StartRecording(ULevelSequence* LevelSequence, UTakeRecorderSources* Sources, UTakeMetaData* MetaData, const FTakeRecorderParameters& Parameters);` — `UFUNCTION(BlueprintCallable, Category="Take Recorder")` — Start a new recording using the specified parameters. Will fail if a recording is currently in progress @param LevelSequence         The base level sequence to use for the recording. Will be played back during the recording and duplicated to create the starting point for the resulting asset. @param Sources               The sources to use for the recording @param MetaData              Meta-data pertaining to this recording, duplicated into the resulting recorded sequence @param Parameters            Configurable parameters for this recorder instance @return The recorder responsible for the recording, or None if a a recording could not be started
- L55 _public prototype_ `static FTakeRecorderParameters GetDefaultParameters();` — `UFUNCTION(BlueprintCallable, Category="Take Recorder")` — Get the default recorder parameters according to the project and user settings
- L62 _public prototype_ `static void SetDefaultParameters(const FTakeRecorderParameters& DefaultParameters);` — `UFUNCTION(BlueprintCallable, Category = "Take Recorder")` — Set the default recorder parameters
- L68 _public prototype_ `static bool IsRecording();` — `UFUNCTION(BlueprintPure, Category="Take Recorder")` — Check whether a recording is currently active
- L75 _public prototype_ `static UTakeRecorder* GetActiveRecorder();` — `UFUNCTION(BlueprintPure, Category="Take Recorder")` — Retrieve the currently active recorder, or None if there none are active
- L82 _public prototype_ `static void StopRecording();` — `UFUNCTION(BlueprintCallable, Category="Take Recorder")` — Stop recording if there is a recorder currently active
- L89 _public prototype_ `static void CancelRecording();` — `UFUNCTION(BlueprintCallable, Category="Take Recorder")` — Cancel recording if there is a recorder currently active
- L96 _public prototype_ `static UTakeRecorderPanel* GetTakeRecorderPanel();` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category="Take Recorder")` — Get the currently open take recorder panel, if one is open
- L103 _public prototype_ `static UTakeRecorderPanel* OpenTakeRecorderPanel();` — `UFUNCTION(BlueprintCallable, Category="Take Recorder")` — Get the currently open take recorder panel, if one is open, opening a new one if not
- L108 _public prototype_ `static void SetOnTakeRecorderPanelChanged(FOnTakeRecorderPanelChanged OnTakeRecorderPanelChanged);` — `UFUNCTION(BlueprintCallable, Category="Take Recorder", meta=(DisplayName="Set On Take Recorder Panel Changed"))` — Called when a Take Panel is constructed or destroyed.
- L112 _public prototype_ `static void SetOnTakeRecorderPreInitialize(FOnTakeRecorderPreInitialize OnTakeRecorderPreInitialize);` — `UE_DEPRECATED(5.4, "Please use TakeRecorderSubsystem::TakeRecorderPreInitialize")` — `UFUNCTION(BlueprintCallable, Category = "Take Recorder", meta = (DeprecatedFunction, DeprecationMessage = "Please use TakeRecorderSubsystem::TakeRecorderPreInitialize"))`
- L116 _public prototype_ `static void SetOnTakeRecorderStarted(FOnTakeRecorderStarted OnTakeRecorderStarted);` — `UE_DEPRECATED(5.4, "Please use TakeRecorderSubsystem::TakeRecorderStarted")` — `UFUNCTION(BlueprintCallable, Category = "Take Recorder", meta = (DeprecatedFunction, DeprecationMessage = "Please use TakeRecorderSubsystem::TakeRecorderStarted"))`
- L120 _public prototype_ `static void SetOnTakeRecorderStopped(FOnTakeRecorderStopped OnTakeRecorderStopped);` — `UE_DEPRECATED(5.4, "Please use TakeRecorderSubsystem::TakeRecorderStopped")` — `UFUNCTION(BlueprintCallable, Category = "Take Recorder", meta = (DeprecatedFunction, DeprecationMessage = "Please use TakeRecorderSubsystem::TakeRecorderStopped"))`
- L124 _public prototype_ `static void SetOnTakeRecorderFinished(FOnTakeRecorderFinished OnTakeRecorderFinished);` — `UE_DEPRECATED(5.4, "Please use TakeRecorderSubsystem::TakeRecorderFinished")` — `UFUNCTION(BlueprintCallable, Category = "Take Recorder", meta = (DeprecatedFunction, DeprecationMessage = "Please use TakeRecorderSubsystem::TakeRecorderFinished"))`
- L128 _public prototype_ `static void SetOnTakeRecorderCancelled(FOnTakeRecorderCancelled OnTakeRecorderCancelled);` — `UE_DEPRECATED(5.4, "Please use TakeRecorderSubsystem::TakeRecorderCancelled")` — `UFUNCTION(BlueprintCallable, Category = "Take Recorder", meta = (DeprecatedFunction, DeprecationMessage = "Please use TakeRecorderSubsystem::TakeRecorderCancelled"))`
- L132 _public prototype_ `static void SetOnTakeRecorderMarkedFrameAdded(FOnTakeRecorderMarkedFrameAdded OnTakeRecorderMarkedFrameAdded);` — `UE_DEPRECATED(5.4, "Please use TakeRecorderSubsystem::TakeRecorderMarkedFrameAdded")` — `UFUNCTION(BlueprintCallable, Category = "Take Recorder", meta = (DeprecatedFunction, DeprecationMessage = "Please use TakeRecorderSubsystem::TakeRecorderMarkedFrameAdded"))`
- L134 _public prototype_ `static void OnTakeRecorderPreInitialize();`
- L135 _public prototype_ `static void OnTakeRecorderStarted();`
- L136 _public prototype_ `static void OnTakeRecorderStopped();`
- L137 _public prototype_ `static void OnTakeRecorderFinished(ULevelSequence* InSequenceAsset);`
- L138 _public prototype_ `static void OnTakeRecorderCancelled();`
- L139 _public prototype_ `static void OnTakeRecorderMarkedFrameAdded(const FMovieSceneMarkedFrame& InMarkedFrame);`
- L145 _public prototype_ `static void SetTakeRecorderPanel(UTakeRecorderPanel* InNewPanel);` — Internal function to assign a new take recorder panel singleton. NOTE: Only to be called by STakeRecorderTabContent::Construct.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TAKERECORDER_API`
- L16 _delegate_ `DECLARE_DYNAMIC_DELEGATE( FOnTakeRecorderPanelChanged );`
- L16 _prototype_ `DECLARE_DYNAMIC_DELEGATE( FOnTakeRecorderPanelChanged );`
- L17 _delegate_ `DECLARE_DYNAMIC_DELEGATE( FOnTakeRecorderPreInitialize );`
- L17 _prototype_ `DECLARE_DYNAMIC_DELEGATE( FOnTakeRecorderPreInitialize );`
- L18 _delegate_ `DECLARE_DYNAMIC_DELEGATE( FOnTakeRecorderStarted );`
- L18 _prototype_ `DECLARE_DYNAMIC_DELEGATE( FOnTakeRecorderStarted );`
- L19 _delegate_ `DECLARE_DYNAMIC_DELEGATE( FOnTakeRecorderStopped );`
- L19 _prototype_ `DECLARE_DYNAMIC_DELEGATE( FOnTakeRecorderStopped );`
- L20 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam( FOnTakeRecorderFinished, ULevelSequence*, SequenceAsset );`
- L20 _prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam( FOnTakeRecorderFinished, ULevelSequence*, SequenceAsset );`
- L21 _delegate_ `DECLARE_DYNAMIC_DELEGATE( FOnTakeRecorderCancelled );`
- L21 _prototype_ `DECLARE_DYNAMIC_DELEGATE( FOnTakeRecorderCancelled );`
- L22 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam( FOnTakeRecorderMarkedFrameAdded, const FMovieSceneMarkedFrame&, MarkedFrame );`
- L22 _prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam( FOnTakeRecorderMarkedFrameAdded, const FMovieSceneMarkedFrame&, MarkedFrame );`

### `Plugins/VirtualProduction/Takes/Source/TakeRecorder/Public/Recorder/TakeRecorderHitchProtectionParameters.h` (Public)


#### struct `FTakeRecorderHitchProtectionParameters`  
`struct FTakeRecorderHitchProtectionParameters`  
_L10-50_
- reflection: `USTRUCT(BlueprintType)`
- L19 _public member_ `bool bEnableHitchProtection = true;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Take Recorder")` — Attempt to prevent hitches in recorded data. If a frame were to be dropped, Take Recorder will instead slow its evaluation and attempt to catch up. This is achieved by using a fixed delta time time-step, which will use the FPS value set in Take Recorder.
- L34 _public member_ `float RegressionBufferSizeInSeconds = 1.f;` — `UPROPERTY(Config, AdvancedDisplay, EditAnywhere, BlueprintReadWrite, Category = "Take Recorder", meta = (EditCondition = "bEnableHitchProtection", EditConditionHides, ClampMin = 0.01666, ClampMax = 10))` — Determines the number of frames in the buffer used by linear regression. The final number of frames is FPS * RegressionBufferSizeInSeconds. Without hitch protection, each frame is marked with the timecode reported by UTimecodeProvider; when a hitch occurs, the timecode hitches by the same amount. With hitch protection is enabled, the engine is set up with a fixed delta time step. Every frame, the timecode is sampled from the timecode provider, stamped with the current physical time, and placed in the buffer. When frame n takes longer to evaluate than expected ("hitches"), the phyiscal time will have moved by a certain amount but the world's simulation time will have remained the same (as simulation time advances only when the engine ticks). Then, frame n+1 uses the world's simulation time to perform linear regression on what the frame's timecode should be.
- L38 _public member_ `TSoftClassPtr<UCatchupFixedRateCustomTimeStep> CustomTimestep = UCatchupFixedRateCustomTimeStep::StaticClass();` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Take Recorder", meta=(EditCondition = "bEnableHitchProtection", EditConditionHides, AllowAbstract = "false"))` — The custom engine timestep class to use. Allows you to customize the behavior.
- L49 _public member_ `double MaxCatchupSeconds = 8.f;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Take Recorder", meta = (EditCondition = "bEnableHitchProtection", EditConditionHides))` — Maximum allowed delay when Take Recorder is attempting to catch up during protection. If Take Recorder falls behind further than this value, it will not accrue additional delay and will drop frames. The result is that the next frame immediately jumps to the target timecode in order to attempt to catch up. Larger values will allow for jumps in timecode in the final data but will also result in possible larger delays in evaluation.

### `Plugins/VirtualProduction/Takes/Source/TakeRecorder/Public/Recorder/TakeRecorderPanel.h` (Public)


#### enum `ETakeRecorderPanelMode`  
`enum class ETakeRecorderPanelMode : uint8`  
_L18-28_
- reflection: `UENUM()`
- L21 _public enumerator_ `NewRecording` — The panel is setting up a new recording
- L23 _public enumerator_ `RecordingInto` — The panel is setting up recording into an existing level sequence
- L25 _public enumerator_ `EditingPreset` — The panel is editing a Take Preset asset
- L27 _public enumerator_ `ReviewingRecording` — The panel is reviewing a previously recorded take

#### class `UTakeRecorderPanel`  
`class UTakeRecorderPanel : public UObject`  
_L34-177_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Take recorder UI panel interop object
- L44 _public prototype_ `ETakeRecorderPanelMode GetMode() const;` — `UFUNCTION(BlueprintCallable, Category="Take Recorder|Panel")` — Get the mode that the panel is currently in
- L51 _public prototype_ `void SetupForRecording_TakePreset(UTakePreset* TakePresetAsset);` — `UFUNCTION(BlueprintCallable, Category="Take Recorder|Panel", DisplayName="Set Mode (Recording w/ Take Preset)")` — Setup this panel such that it is ready to start recording using the specified take preset as a template for the recording.
- L58 _public prototype_ `void SetupForRecording_LevelSequence(ULevelSequence* LevelSequenceAsset);` — `UFUNCTION(BlueprintCallable, Category="Take Recorder|Panel", DisplayName="Set Mode (Recording w/ Level Sequence)")` — Setup this panel such that it is ready to start recording using the specified level sequence asset as a template for the recording.
- L65 _public prototype_ `void SetupForRecordingInto_LevelSequence(ULevelSequence* LevelSequenceAsset);` — `UFUNCTION(BlueprintCallable, Category="Take Recorder|Panel", DisplayName="Set Mode (Recording into Level Sequence)")` — Setup this panel such that it is ready to start recording using the specified level sequence asset to record into.
- L71 _public prototype_ `void SetupForEditing(UTakePreset* TakePreset);` — `UFUNCTION(BlueprintCallable, Category="Take Recorder|Panel", DisplayName="Set Mode (Editing Take Preset)")` — Setup this panel as an editor for the specified take preset asset.
- L77 _public prototype_ `void SetupForViewing(ULevelSequence* LevelSequenceAsset);` — `UFUNCTION(BlueprintCallable, Category="Take Recorder|Panel", DisplayName="Set Mode (Read-Only Level Sequence)")` — Setup this panel as a viewer for a previously recorded take.
- L83 _public prototype_ `void ClearPendingTake();` — `UFUNCTION(BlueprintCallable, Category = "Take Recorder|Panel", DisplayName = "Clear Pending Take")` — Clear the pending take level sequence
- L89 _public prototype_ `ULevelSequence* GetLevelSequence() const;` — `UFUNCTION(BlueprintCallable, Category="Take Recorder|Panel")` — Access the level sequence for this take
- L96 _public prototype_ `ULevelSequence* GetLastRecordedLevelSequence() const;` — `UFUNCTION(BlueprintCallable, Category="Take Recorder|Panel")` — Access the last level sequence that was recorded
- L103 _public prototype_ `UTakeMetaData* GetTakeMetaData() const;` — `UFUNCTION(BlueprintCallable, Category="Take Recorder|Panel")` — Access take meta data for this take
- L110 _public prototype_ `FFrameRate GetFrameRate() const;` — `UFUNCTION(BlueprintCallable, Category="Take Recorder|Panel")` — Access the frame rate for this take
- L117 _public prototype_ `void SetFrameRate(FFrameRate InFrameRate);` — `UFUNCTION(BlueprintCallable, Category = "Take Recorder|Panel")` — Set the frame rate for this take
- L124 _public prototype_ `void SetFrameRateFromTimecode(bool bInFromTimecode);` — `UFUNCTION(BlueprintCallable, Category = "Take Recorder|Panel")` — Set if the frame rate is set from the Timecode frame rate
- L131 _public prototype_ `UTakeRecorderSources* GetSources() const;` — `UFUNCTION(BlueprintCallable, Category="Take Recorder|Panel")` — Access the sources that are to be (or were) used for recording this take
- L138 _public prototype_ `void StartRecording() const;` — `UFUNCTION(BlueprintCallable, Category="Take Recorder|Panel")` — Start recording with the current take
- L145 _public prototype_ `void StopRecording() const;` — `UFUNCTION(BlueprintCallable, Category="Take Recorder|Panel")` — Stop recording with the current take
- L151 _public prototype_ `bool CanStartRecording(FText& OutErrorText) const;` — `UFUNCTION(BlueprintCallable, Category="Take Recorder|Panel")` — Whether the panel is ready to start recording
- L160 _public prototype_ `void InitializePanel(TWeakPtr<ITakeRecorderTabContent> InTabContent);` — Initialize this object with a weak pointer to the tab content from which all the UI state can be retrieved
- L165 _public prototype_ `bool IsPanelOpen() const;` — Check whether this panel is still open or not
- L170 _public prototype_ `void ClosePanel();` — Invalidate this object by reporting that it is no longer open. Any subsequent scripting interactions will result in an error
- L174 _private prototype_ `bool ValidateTabContent() const;`
- L176 _private member_ `TWeakPtr<ITakeRecorderTabContent> WeakTabContent;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TAKERECORDER_API`

### `Plugins/VirtualProduction/Takes/Source/TakeRecorder/Public/Recorder/TakeRecorderParameters.h` (Public)


#### struct `FTakeRecorderUserParameters`  
`struct FTakeRecorderUserParameters`  
_L18-70_
- reflection: `USTRUCT(BlueprintType)`
- L22 _public prototype_ `FTakeRecorderUserParameters();`
- L26 _public member_ `bool bMaximizeViewport;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category="User Settings")` — Whether to maximize the viewport (enter Immersive Mode) when recording
- L30 _public member_ `float CountdownSeconds;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category="User Settings", DisplayName="Countdown", meta=(Units=s, ClampMin="0.0", UIMin="0.0", ClampMax="60.0", UIMax="60.0"))` — Delay that we will use before starting recording
- L34 _public member_ `float EngineTimeDilation;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category="User Settings", meta=(Units=Multiplier, ClampMin="0.00001", UIMin="0.00001"))` — The engine time dilation to apply during the recording
- L38 _public member_ `bool bResetPlayhead;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "User Settings")` — Reset playhead to beginning of the playback range when starting recording
- L42 _public member_ `bool bStopAtPlaybackEnd;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "User Settings")` — Automatically stop recording when reaching the end of the playback range
- L49 _public member_ `bool bStopOnRollover;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "User Settings")` — Automatically stop recording when the current time code value loops over to before the start timecode value, e.g. when a rollover happens (23:59:59 -> 00:00:00:01), or if you started recording at 18:39:12:01 and timecode later jumps to 18:35:00:01.
- L53 _public member_ `bool bRemoveRedundantTracks;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category="User Settings")` — Recommended for use with recorded spawnables. Beware that changes to actor instances in the map after recording may alter the recording when played back
- L57 _public member_ `float ReduceKeysTolerance;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category="User Settings")` — Tolerance to use when reducing keys
- L61 _public member_ `bool bSaveRecordedAssets;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "User Settings")` — Whether to save recorded level sequences and assets when done recording
- L65 _public member_ `bool bAutoLock;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "User Settings")` — Whether to lock the level sequence when done recording
- L69 _public member_ `bool bAutoSerialize;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "User Settings")` — Whether to incrementally serialize and store some data while recording

#### struct `FTakeRecorderProjectParameters`  
`struct FTakeRecorderProjectParameters`  
_L73-168_
- reflection: `USTRUCT(BlueprintType)`
- L77 _public prototype_ `FTakeRecorderProjectParameters();`
- L80 _public prototype_ `FString GetResolvedRootTakeSaveDir() const;` — Get the resolved root take save dir. The is the path that considers both the /Game and /Plugin based directories.
- L84 _public prototype_ `FString GetTakeAssetPath() const;` — The take asset path, composed of the TakeRootSaveDir and the TakeSaveDir
- L88 _public member_ `FDirectoryPath RootTakeSaveDir;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Take Recorder", meta = (ContentDir, NamingTokens, ForceShowPluginContent))` — The root of the directory in which to save recorded takes.
- L102 _public member_ `FString TakeSaveDir;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Take Recorder", meta = (NamingTokens))` — The name of the directory in which to save recorded takes. Supports any of the following format specifiers that will be substituted when a take is recorded: {day}       - The day of the timestamp for the start of the recording. {month}     - The month of the timestamp for the start of the recording. {year}      - The year of the timestamp for the start of the recording. {hour}      - The hour of the timestamp for the start of the recording. {minute}    - The minute of the timestamp for the start of the recording. {second}    - The second of the timestamp for the start of the recording. {take}      - The take number. {slate}     - The slate string.
- L108 _public member_ `FString SubSequenceDirectory;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Take Recorder", meta = (NamingTokens))` — The directory to record subscenes into.
- L114 _public member_ `FString DefaultSlate;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Take Recorder")` — The default name to use for the Slate information
- L120 _public member_ `EUpdateClockSource RecordingClockSource;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Take Recorder")` — The clock source to use when recording
- L126 _public member_ `bool bStartAtCurrentTimecode;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Take Recorder")` — If enabled, track sections will start at the current timecode. Otherwise, 0.
- L132 _public member_ `bool bRecordTimecode;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Take Recorder")` — If enabled, timecode will be recorded into each actor track
- L140 _public member_ `bool bRecordSourcesIntoSubSequences;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Take Recorder")` — If enabled, each Source will be recorded into a separate Sequence and embedded in the Root Sequence will link to them via Subscenes track. If disabled, all Sources will be recorded into the Root Sequence, and you will not be able to swap between various takes of specific source using the Sequencer Take ui. This can still be done via copying and pasting between sequences if needed.
- L147 _public member_ `bool bRecordToPossessable;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Take Recorder")` — If enabled, all recorded actors will be recorded to possessable object bindings in Sequencer. If disabled, all recorded actors will be recorded to spawnable object bindings in Sequencer. This can be overridden per actor source.
- L151 _public member_ `ETakeRecorderSpawnableOverwriteBehavior SpawnableOverwriteBehavior;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Take Recorder", meta = (ValidEnumValues = "OverwriteLegacy, CreateNew"))` — If spawnables should be overwritten during record.
- L155 _public member_ `ETakeRecorderAttachRecordBehaviour AttachRecordBehaviour;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Take Recorder", meta = (ValidEnumValues = "None, Attachments, Hierarchy"))` — The record behaviour of attachments and hierarchies.
- L159 _public member_ `TArray<FTakeRecorderTrackSettings> DefaultTracks;` — `UPROPERTY(config, EditAnywhere, Category = "Take Recorder")` — List of property names for which movie scene tracks will always record.
- L163 _public member_ `bool bShowNotifications;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Take Recorder")` — Whether to show notification windows or not when recording
- L167 _public member_ `bool bRecordWithSimpleSequencerView = false;` — `UPROPERTY(config, BlueprintReadWrite, EditAnywhere, Category = "Take Recorder")` — Whether to switch to the simple sequencer view whilst recording.

#### enum `ETakeRecorderMode`  
`enum class ETakeRecorderMode : uint8`  
_L171-178_
- reflection: `UENUM(BlueprintType)`
- L174 _public enumerator_ `RecordNewSequence` — Record into a new sequence
- L177 _public enumerator_ `RecordIntoSequence` — Record into an existing sequence

#### struct `FTakeRecorderParameters`  
`struct FTakeRecorderParameters`  
_L184-215_
- reflection: `USTRUCT(BlueprintType)`
- desc: Structure housing all configurable parameters for a take recorder instance
- L188 _public prototype_ `FTakeRecorderParameters();`
- L191 _public member_ `FTakeRecorderUserParameters User;` — `UPROPERTY(BlueprintReadWrite, Category="Take Recorder")`
- L194 _public member_ `FTakeRecorderProjectParameters Project;` — `UPROPERTY(BlueprintReadWrite, Category="Take Recorder")`
- L197 _public member_ `FTakeRecorderHitchProtectionParameters HitchProtection;` — `UPROPERTY(BlueprintReadWrite, Category="Take Recorder")`
- L200 _public member_ `ETakeRecorderMode TakeRecorderMode;` — `UPROPERTY(BlueprintReadWrite, Category="Take Recorder")`
- L203 _public member_ `FFrameNumber StartFrame;` — `UPROPERTY(BlueprintReadWrite, Category = "Take Recorder")`
- L210 _public member_ `bool bDisableRecordingAndSave = false;` — `UPROPERTY(Transient)` — Option to disable recording and saving of data. This can be used in a scenario where multiple clients are running take recorder, but only certain ones are set to process and save the data.
- L214 _public member_ `bool bOpenSequencer = true;` — `UPROPERTY(BlueprintReadWrite, Category = "Take Recorder")` — If sequencer should open when starting a recording.

#### struct `FTakeRecorderSequenceParameters`  
`struct FTakeRecorderSequenceParameters`  
_L221-246_
- reflection: `USTRUCT(Blueprintable)`
- desc: Parameters for initializing a new sequence.
- L227 _public member_ `TObjectPtr<UTakePreset> BasePreset;` — `UPROPERTY(BlueprintReadWrite, Category = TakeRecorder)` — A preset asset to base the recording off
- L231 _public member_ `TObjectPtr<ULevelSequence> BaseSequence;` — `UPROPERTY(BlueprintReadWrite, Category = TakeRecorder)` — A level sequence asset to base the recording off
- L235 _public member_ `TObjectPtr<ULevelSequence> RecordIntoSequence;` — `UPROPERTY(BlueprintReadWrite, Category = TakeRecorder)` — A level sequence asset to record into
- L239 _public member_ `TObjectPtr<ULevelSequence> SequenceToView;` — `UPROPERTY(BlueprintReadWrite, Category = TakeRecorder)` — A sequence that should be shown directly on the take recorder UI
- L242 _public prototype_ `bool IsValid() const;` — Checks whether we have any valid data present.
- L244 _public prototype_ `bool operator==(const FTakeRecorderSequenceParameters& Other) const;`
- L245 _public prototype_ `bool operator!=(const FTakeRecorderSequenceParameters& Other) const;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API TAKERECORDER_API`

### `Plugins/VirtualProduction/Takes/Source/TakeRecorder/Public/Recorder/TakeRecorderSubsystem.h` (Public)


#### class `UTakeRecorderSubsystem`  
`class UTakeRecorderSubsystem final : public UEngineSubsystem, public ITakeRecorderSubsystemInterface`  
_L45-454_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEngineSubsystem,ITakeRecorderSubsystemInterface`
- desc: UTakeRecorderSubsystem Subsystem for Take Recorder. SetTargetSequence() needs to be called at least once prior to use. This will perform additional initialization and register the subsystem as tickable currently required to cache level metadata.
- L51 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L52 _public prototype_ `virtual void Deinitialize() override;`
- L63 _public prototype_ `virtual void SetTargetSequence(const FTakeRecorderSequenceParameters& InData = FTakeRecorderSequenceParameters()) override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder, meta=(AutoCreateRefTerm="InData"))` — Provide sequence data for this take recorder. This will also perform initialization of the subsystem. This must be called prior to any usage. @param InData The sequence parameters, which are mutually exclusive. They can all be null.
- L66 _public prototype_ `virtual void SetRecordIntoLevelSequence(ULevelSequence* LevelSequence) override;` — Set the record into level sequence.
- L70 _public prototype_ `virtual bool CanReviewLastRecording() const override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — Can we review the last recording?
- L77 _public prototype_ `virtual bool ReviewLastRecording() override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — Supply the last recording if it exists. @return true if it can be reviewed, false if it there isn't a recording to review.
- L86 _public prototype_ `virtual bool StartRecording(bool bOpenSequencer = true, bool bShowErrorMessage = true) override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — Begin a new recording. @param bOpenSequencer If sequencer should open when starting the recording. @param bShowErrorMessage If an error message should be displayed on failure. @return true if the recording was started successfully.
- L92 _public prototype_ `virtual void StopRecording() override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — Stop an existing recording.
- L98 _public prototype_ `virtual void CancelRecording(bool bShowConfirmMessage = true) override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — Cancel an in-progress recording.
- L104 _public prototype_ `virtual void ResetToPendingTake() override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — Reset to the pending take.
- L110 _public prototype_ `virtual void ClearPendingTake() override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — Clear the pending take.
- L114 _public prototype_ `virtual UTakePreset* GetPendingTake() const override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — Retrieve the pending take. This may be null.
- L118 _public prototype_ `virtual void RevertChanges() override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — Revert any changes restoring the preset origin.
- L122 _public prototype_ `virtual bool IsRecordingUsingExistingSequence() const override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — If we are using an existing sequence as a base or recording into an existing one.
- L127 _public prototype_ `virtual UTakeRecorderSource* AddSource(const TSubclassOf<UTakeRecorderSource> InSourceClass) override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder, meta = (DeterminesOutputType = "InSourceClass"))` — Add a source by a source class.
- L131 _public prototype_ `virtual void RemoveSource(UTakeRecorderSource* InSource) override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — Remove a given source.
- L135 _public prototype_ `virtual void ClearSources() override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — Remove all sources from the current sequence.
- L139 _public prototype_ `virtual UTakeRecorderSources* GetSources() const override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — Retrieve the sources.
- L142 _public prototype_ `virtual TArrayView<UTakeRecorderSource* const> GetAllSources() const override;` — Retrieve all sources for the current sequence.
- L150 _public prototype_ `virtual TArray<UTakeRecorderSource*> GetAllSourcesCopy() const override;` — `UFUNCTION(BlueprintPure, DisplayName = "Get Sources (Copy)", Category = TakeRecorder)` — Retrieves a copy of the list of sources that are being recorded. This is intended for Blueprint usages which cannot use TArrayView. DO NOT MODIFY THIS ARRAY, modifications will be lost.
- L154 _public prototype_ `virtual UTakeRecorderSource* GetSourceByClass(const TSubclassOf<UTakeRecorderSource> InSourceClass) const override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder, meta = (DeterminesOutputType = "InSourceClass"))` — Retrieve the first source of the given class.
- L164 _public prototype_ `virtual void AddSourceForActor(AActor* InActor, bool bReduceKeys = true, bool bShowProgress = true) override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — Add an actor as a source. @param InActor The actor that should be added to Sources. Note that this can include ALevelSequenceActors. @param bReduceKeys Enable/disable key reduction on all the sources registered @param bShowProgress Enable/disable the dialog box showing progress for the potentially slow parts of finalizing the take
- L170 _public prototype_ `virtual void RemoveActorFromSources(AActor* InActor) override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — Remove an actor from available sources.
- L174 _public prototype_ `virtual AActor* GetSourceActor(UTakeRecorderSource* InSource) const override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — Retrieve the actor from a source, if applicable.
- L179 _public prototype_ `virtual ETakeRecorderState GetState() const override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — Retrieve the current take recorder state.
- L187 _public prototype_ `virtual void SetTakeNumber(int32 InNewTakeNumber, bool bEmitChanged = true) override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — Directly set the take number. @param InNewTakeNumber The new take number to set. @param bEmitChanged Whether to broadcast events signaling the take number has changed.
- L191 _public prototype_ `virtual int32 GetNextTakeNumber(const FString& InSlate) const override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — Compute the next take number given a slate.
- L195 _public prototype_ `virtual void GetNumberOfTakes(const FString& InSlate, int32& OutMaxTake, int32& OutNumTakes) const override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — Find both the current maximum take value and the total number of takes for a given slate.
- L199 _public prototype_ `virtual void IncrementTakeNumber() override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — Calculate and apply the next take number.
- L206 _public prototype_ `virtual TArray<FAssetData> GetSlates(FName InPackagePath = NAME_None) const override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — Retrieve all slates. @param InPackagePath [Optional] Scope the search to a specific folder, recursively.
- L214 _public prototype_ `virtual void SetSlateName(const FString& InSlateName, bool bEmitChanged = true) override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — Directly set the slate name. @param InSlateName The new slate name to set. @param bEmitChanged Whether to broadcast events signaling the slate name has changed.
- L218 _public prototype_ `virtual bool MarkFrame() override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — Mark the current frame.
- L224 _public prototype_ `virtual FFrameRate GetFrameRate() const override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — Access the frame rate for this take
- L230 _public prototype_ `virtual void SetFrameRate(FFrameRate InFrameRate) override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — Set the frame rate for this take
- L236 _public prototype_ `virtual void SetFrameRateFromTimecode() override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — Set if the frame rate is set from the Timecode frame rate
- L239 _public prototype_ `virtual void ImportPreset(const FAssetData& InPreset) override;` — Import a preset to the transient preset.
- L243 _public prototype_ `virtual bool IsReviewing() const override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — If Take Recorder is currently reviewing.
- L247 _public prototype_ `virtual bool IsRecording() const override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — If Take Recorder is currently recording.
- L255 _public prototype_ `virtual bool TryGetSequenceCountdown(float& OutValue) const override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — Retrieve the current sequence's countdown. @param OutValue The current value of the countdown. @return True if we are in a countdown sequence, false otherwise.
- L262 _public prototype_ `virtual void SetSequenceCountdown(float InSeconds) override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — Sets the current sequence's countdown. @param InSeconds Time in seconds.
- L266 _public prototype_ `virtual TArray<UObject*> GetSourceRecordSettings(UTakeRecorderSource* InSource) const override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — Retrieve additional settings objects from a source.
- L270 _public prototype_ `virtual FTakeRecorderParameters GetGlobalRecordSettings() const override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — Retrieve the global take recorder settings.
- L274 _public prototype_ `virtual void SetGlobalRecordSettings(const FTakeRecorderParameters& InParameters) override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — Set the global take recorder settings.
- L278 _public prototype_ `virtual UTakeMetaData* GetTakeMetaData() const override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — Retrieve the current meta data.
- L282 _public prototype_ `virtual ULevelSequence* GetLevelSequence() const override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — Return the level sequence we are using.
- L285 _public prototype_ `virtual ULevelSequence* GetSuppliedLevelSequence() const override;` — Retrieve the Supplied Level Sequence if it exists.
- L288 _public prototype_ `virtual ULevelSequence* GetRecordingLevelSequence() const override;` — Retrieve the Recording Level Sequence if it exists.
- L291 _public prototype_ `virtual ULevelSequence* GetRecordIntoLevelSequence() const override;` — Retrieve the Record Into Level Sequence if it exists.
- L295 _public prototype_ `virtual ULevelSequence* GetLastRecordedLevelSequence() const override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — Retrieve the Last Recorded Level Sequence if it exists.
- L298 _public prototype_ `virtual UTakePreset* GetTransientPreset() const override;` — Retrieve the transient preset the subsystem is using.
- L302 _public prototype_ `virtual ETakeRecorderMode GetTakeRecorderMode() const override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — The current take recorder mode.
- L305 _public prototype_ `virtual UTakeRecorderNamingTokensData* GetNamingTokensData() const override;` — Retrieve relevant Naming Tokens data for Take Recorder.
- L308 _public prototype_ `virtual bool HasPendingChanges() const override;` — @return Whether there are any pending changes, which ClearPendingTake would discard.
- L312 _public prototype_ `virtual UClass* GetPresetTargetRecordClass() const override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — Retrieve the target record class of the Take Preset.
- L316 _public prototype_ `virtual void SetPresetTargetRecordClass(const TSubclassOf<ULevelSequence> InClass) override;` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder)` — Set the target record class of the Take Preset.
- L323 _public prototype_ `UObject* GetAdditionalSettings(TSubclassOf<UObject> SettingsType);` — `UFUNCTION(BlueprintCallable, Category = TakeRecorder, meta = (DeterminesOutputType="SettingsType"))` — Retrieve Additional Settings Objects - eg. The Audio Input Device to access Microphone Recorder settings.
- L328 _public prototype_ `FOnTakeRecordingInitialized& GetOnRecordingPreInitializedEvent();` — Retrieve a multi-cast delegate that is triggered when a recording pre-initializes
- L332 _public prototype_ `FOnTakeRecordingInitialized& GetOnRecordingInitializedEvent();` — Retrieve a multi-cast delegate that is triggered when a recording initializes
- L336 _public prototype_ `FOnTakeRecordingStarted& GetOnRecordingStartedEvent();` — Retrieve a multi-cast delegate that is triggered when a recording starts
- L340 _public prototype_ `FOnTakeRecordingStopped& GetOnRecordingStoppedEvent();` — Retrieve a multi-cast delegate that is triggered when a recording is stopped
- L344 _public prototype_ `FOnTakeRecordingFinished& GetOnRecordingFinishedEvent();` — Retrieve a multi-cast delegate that is triggered when a recording finishes
- L348 _public prototype_ `FOnTakeRecordingCancelled& GetOnRecordingCancelledEvent();` — Retrieve a multi-cast delegate that is triggered when a recording is cancelled.
- L352 _public prototype_ `UTakeRecorderSources::FOnSourceAdded& GetOnRecordingSourceAddedEvent();` — Retrieve a multi-cast delegate that is triggered when a source is added.
- L356 _public prototype_ `UTakeRecorderSources::FOnSourceRemoved& GetOnRecordingSourceRemovedEvent();` — Retrieve a multi-cast delegate that is triggered when a source is removed.
- L360 _public prototype_ `UTakeRecorderSources::FOnSourceModified& GetOnRecordingSourceModifiedEvent();` — Retrieve a multi-cast delegate that is triggered when a source is modified.
- L365 _public prototype_ `FOnPendingTakeCleared& GetOnPendingTakeClearedEvent();` — Retrieve a multi-cast delegate that is triggered when the pending take is cleared.
- L373 _private member_ `TScriptInterface<ITakeRecorderSubsystemInterface> Implementation;` — `UPROPERTY()` — The actual Take Recorder Subsystem implementation.
- L382 _private member_ `FOnTakeRecordingPreInitialize OnRecordingPreInitializeEvent;` — Multicast delegate when recording is pre-initialized. For native binding.
- L384 _private member_ `FOnTakeRecordingInitialized ORecordingInitializedEvent;` — Multicast delegate when recording is initialized. For native binding.
- L386 _private member_ `FOnTakeRecordingStarted OnRecordingStartedEvent;` — Multicast delegate for when a recording is started. For native binding.
- L388 _private member_ `FOnTakeRecordingStopped OnRecordingStoppedEvent;` — Multicast delegate for when a recording has stopped. For native binding.
- L390 _private member_ `FOnTakeRecordingFinished OnRecordingFinishedEvent;` — Multicast delegate for when a recording has finished. For native binding.
- L392 _private member_ `FOnTakeRecordingCancelled OnRecordingCancelledEvent;` — Multicast delegate for when a recording has been cancelled. For native binding.
- L394 _private member_ `UTakeRecorderSources::FOnSourceAdded OnRecordingSourceAddedEvent;` — Multicast delegate when any source has been added. For native binding.
- L396 _private member_ `UTakeRecorderSources::FOnSourceRemoved OnRecordingSourceRemovedEvent;` — Multicast delegate when any source has been added. For native binding.
- L398 _private member_ `UTakeRecorderSources::FOnSourceModified OnRecordingSourceModifiedEvent;` — Multicast delegate when any source has been modified. For native binding.
- L400 _private member_ `FOnPendingTakeCleared OnPendingTakeClearedEvent;` — Multi-cast delegate when the pending take is cleared. For native binding.
- L405 _public member_ `FTakeRecorderPreInitialize TakeRecorderPreInitialize;` — `UPROPERTY(BlueprintAssignable, Category=TakeRecorder)` — Called before initialization occurs (ie. when the recording button is pressed and before the countdown starts)
- L409 _public member_ `FTakeRecorderInitialized TakeRecorderInitialized;` — `UPROPERTY(BlueprintAssignable, Category=TakeRecorder)` — called when take recorder is initializing.
- L413 _public member_ `FTakeRecorderStarted TakeRecorderStarted;` — `UPROPERTY(BlueprintAssignable, Category=TakeRecorder)` — Called when take recorder is started
- L417 _public member_ `FTakeRecorderStopped TakeRecorderStopped;` — `UPROPERTY(BlueprintAssignable, Category=TakeRecorder)` — Called when take recorder is stopped
- L421 _public member_ `FTakeRecorderFinished TakeRecorderFinished;` — `UPROPERTY(BlueprintAssignable, Category=TakeRecorder)` — Called when take recorder has finished
- L425 _public member_ `FTakeRecorderCancelled TakeRecorderCancelled;` — `UPROPERTY(BlueprintAssignable, Category=TakeRecorder)` — Called when take recorder is cancelled
- L429 _public member_ `FTakeRecorderMarkedFrameAdded TakeRecorderMarkedFrameAdded;` — `UPROPERTY(BlueprintAssignable, Category=TakeRecorder)` — Called when a marked frame is added to take recorder
- L433 _public member_ `FTakeRecorderSlateChanged TakeRecorderSlateChanged;` — `UPROPERTY(BlueprintAssignable, Category=TakeRecorder)` — Called when a take recorder slate changes.
- L437 _public member_ `FTakeRecorderTakeNumberChanged TakeRecorderTakeNumberChanged;` — `UPROPERTY(BlueprintAssignable, Category=TakeRecorder)` — Called when a take recorder take number changes.
- L441 _public member_ `FOnTakeRecorderSourceAddedDynamic TakeRecorderSourceAdded;` — `UPROPERTY(BlueprintAssignable, Category=TakeRecorder)` — Multicast delegate when any source has been added.
- L445 _public member_ `FOnTakeRecorderSourceRemovedDynamic TakeRecorderSourceRemoved;` — `UPROPERTY(BlueprintAssignable, Category=TakeRecorder)` — Multicast delegate when any source has been removed.
- L449 _public member_ `FOnTakeRecorderSourceModifiedDynamic TakeRecorderSourceModified;` — `UPROPERTY(BlueprintAssignable, Category=TakeRecorder)` — Multicast delegate when any source has been modified.
- L453 _public member_ `FPendingTakeCleared PendingTakeCleared;` — `UPROPERTY(BlueprintAssignable, Category=TakeRecorder)` — Multicast delegate when the pending take is cleared.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TAKERECORDER_API`
- L18 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTakeRecorderPreInitialize);`
- L18 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTakeRecorderPreInitialize);`
- L19 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTakeRecorderInitialized);`
- L19 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTakeRecorderInitialized);`
- L20 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTakeRecorderStarted);`
- L20 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTakeRecorderStarted);`
- L21 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTakeRecorderStopped);`
- L21 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTakeRecorderStopped);`
- L22 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTakeRecorderFinished, ULevelSequence*, SequenceAsset);`
- L22 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTakeRecorderFinished, ULevelSequence*, SequenceAsset);`
- L23 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTakeRecorderCancelled);`
- L23 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTakeRecorderCancelled);`
- L24 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTakeRecorderMarkedFrameAdded, const FMovieSceneMarkedFrame&, MarkedFrame);`
- L24 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTakeRecorderMarkedFrameAdded, const FMovieSceneMarkedFrame&, MarkedFrame);`
- L25 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPendingTakeCleared);`
- L25 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPendingTakeCleared);`
- L27 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTakeRecorderSlateChanged, const FString&, Slate, UTakeMetaData*, TakeMetaData);`
- L27 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTakeRecorderSlateChanged, const FString&, Slate, UTakeMetaData*, TakeMetaData);`
- L28 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTakeRecorderTakeNumberChanged, int32, TakeNumber, UTakeMetaData*, TakeMetaData);`
- L28 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTakeRecorderTakeNumberChanged, int32, TakeNumber, UTakeMetaData*, TakeMetaData);`
- L35 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTakeRecorderSourceAddedDynamic, UTakeRecorderSource*, Source);` — Dynamic delegates for source modification. These are reproductions of static ones declared under UTakeRecorderSource. We do this so we can successfully leverage static delegates within the TakesCore module, firing when any change is made for any source owner. We define new ones here so they can be blueprint assignable.
- L35 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTakeRecorderSourceAddedDynamic, UTakeRecorderSource*, Source);` — Dynamic delegates for source modification. These are reproductions of static ones declared under UTakeRecorderSource. We do this so we can successfully leverage static delegates within the TakesCore module, firing when any change is made for any source owner. We define new ones here so they can be blueprint assignable.
- L36 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTakeRecorderSourceRemovedDynamic, UTakeRecorderSource*, Source);`
- L36 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTakeRecorderSourceRemovedDynamic, UTakeRecorderSource*, Source);`
- L37 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTakeRecorderSourceModifiedDynamic, UTakeRecorderSource*, Source);`
- L37 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTakeRecorderSourceModifiedDynamic, UTakeRecorderSource*, Source);`

### `Plugins/VirtualProduction/Takes/Source/TakeRecorder/Public/SerializedRecorder.h` (Public)


#### class `FSerializedRecorder`  
`class FSerializedRecorder: public ISerializedRecorder`  
_L16-41_
- inherits: `ISerializedRecorder`
- L19 _public function_ `FSerializedRecorder() : bLoadSequenceFile(false)`
- L20 _public prototype_ `~FSerializedRecorder() = default;`
- L22 _public prototype_ `virtual bool LoadRecordedSequencerFile(UMovieSceneSequence* InMovieSceneSequence, UWorld *PlaybackContext, const FString& InFileName, TFunction<void()> InCompletionCallback) override;`
- L25 _public prototype_ `AActor GetActorFromGuid(const FGuid& InGuid);` — this is only valid during LoadSequenceFile or LoadActorFile
- L28 _private prototype_ `bool LoadSequenceFile(UMovieSceneSequence* InMovieSceneSequence, UWorld *PlaybackContext, const FString& InFileName, TFunction<void()> InCompletionCallback);`
- L29 _private prototype_ `bool LoadActorFile(UMovieSceneSequence* InMovieSceneSequence, UWorld *PlaybackContext, const FString& InFileName, TFunction<void()> InCompletionCallback);`
- L30 _private prototype_ `bool LoadPropertyFile(UMovieSceneSequence* InMovieSceneSequence, UWorld *PlaybackContext, const FString& InFileName, TFunction<void()> InCompletionCallback);`
- L31 _private prototype_ `bool LoadSubSequenceFile(UMovieSceneSequence* InMovieSceneSequence, UWorld *PlaybackContext, const FString& InFileName, TFunction<void()> InCompletionCallback);`
- L33 _private prototype_ `AActor* SetActorPossesableOrSpawnable(UMovieSceneSequence* InMovieSceneSequence, UWorld *PlaybackContext, const FActorFileHeader& ActorHeader);`
- L34 _private prototype_ `void SetComponentPossessable(UMovieSceneSequence* InMovieSceneSequence, UWorld *PlaybackContext, AActor* Actor, const FActorFileHeader& ActorHeader, const FActorProperty& ActorProperty);`
- L38 _private member_ `TMap<FGuid, AActor*> ActorGuidToActorMap;`
- L39 _private member_ `bool bLoadSequenceFile;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TAKERECORDER_API`

### `Plugins/VirtualProduction/Takes/Source/TakeRecorder/Public/TakeRecorderNamingTokensData.h` (Public)


#### struct `FTakeRecorderNamingTokensFieldMapping`  
`struct FTakeRecorderNamingTokensFieldMapping`  
_L13-24_
- reflection: `USTRUCT()`
- L19 _public member_ `FString FieldName;` — `UPROPERTY()` — Name of the property field.
- L23 _public member_ `TArray<FString> UndefinedKeys;` — `UPROPERTY()` — All undefined keys with this field.

#### class `UTakeRecorderNamingTokensData`  
`class UTakeRecorderNamingTokensData : public UObject`  
_L30-66_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Data container object for Take Recorder Naming Tokens. Kept as UObject to assist with transactions.
- L35 _public member_ `FGuid NamingTokensExternalGuid;` — Guid to our managed tokens.
- L42 _public member_ `TMap<FNamingTokenData, FText> UserDefinedTokens;` — `UPROPERTY()` — Custom tokens entered in by the user, mapped to a user defined value. We use FNamingTokenData rather than an FString for the key so we can support case sensitivity in our map.
- L48 _public member_ `TSet<FString, FLocKeySetFuncs> VisibleUserTokens;` — User tokens that are currently visible. Kept as a separate property from UsedDefinedTokens we can persist user values between selected sources that have different token entries in their fields.
- L52 _public member_ `TArray<FTakeRecorderNamingTokensFieldMapping> FieldToUndefinedKeys;` — `UPROPERTY(NonTransactional)` — Ordered array of FieldName to undefined token keys. These are present if a token evaluation failed to identify them.
- L56 _public member_ `FText EvaluatedTextValue;` — `UPROPERTY()` — Evaluated text to serve as an example.
- L59 _public member_ `TWeakObjectPtr<UNamingTokens> TakeRecorderNamingTokens;` — Pointer to our naming tokens object.
- L62 _public prototype_ `TArray<FString>& FindOrAddTokenKeysForField(const FString& InFieldName);` — Find or add an array given a field name. The array will be a list of token keys for this specific field.
- L65 _public prototype_ `bool IsTokenKeyUndefined(const FString& InTokenKey) const;` — Checks if a token key is in our undefined list.

### `Plugins/VirtualProduction/Takes/Source/TakeRecorder/Public/TakeRecorderOverlayWidget.h` (Public)


#### class `UTakeRecorderOverlayWidget`  
`class UTakeRecorderOverlayWidget : public UUserWidget`  
_L13-34_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType)`
- inherits: `UUserWidget`
- L19 _public prototype_ `UTakeRecorderOverlayWidget(const FObjectInitializer& ObjectInitializer);`
- L24 _public function_ `void SetRecorder(UTakeRecorder* InRecorder)` — Set the recorder that this overlay is reflecting
- L33 _protected member_ `TObjectPtr<UTakeRecorder> Recorder;` — `UPROPERTY(BlueprintReadOnly, Category="Take Recorder")` — The recorder that this overlay is reflecting

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TAKERECORDER_API`

### `Plugins/VirtualProduction/Takes/Source/TakeRecorder/Public/TakeRecorderSettings.h` (Public)


#### class `UTakeRecorderUserSettings`  
`class UTakeRecorderUserSettings : public UObject`  
_L16-52_
- reflection: `UCLASS(config=EditorPerProjectUserSettings, MinimalAPI)`
- inherits: `UObject`
- desc: Universal take recorder settings that apply to a whole take
- L21 _public prototype_ `UTakeRecorderUserSettings();`
- L24 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L28 _public prototype_ `FString GetResolvedPresetSaveDir() const;` — Return the PresetSaveDir path relative to the project.
- L31 _public prototype_ `void SetPresetSaveDir(const FString& InPath);` — Sets the default location for the present saved directory.
- L35 _public member_ `FTakeRecorderUserParameters Settings;` — `UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category="User Settings", meta=(ShowOnlyInnerProperties))` — User settings that should be passed to a recorder instance
- L39 _public member_ `FDirectoryPath PresetSaveDir;` — `UPROPERTY(config, EditAnywhere, Category="User Settings", DisplayName="Preset Save Location", meta = (ContentDir, NamingTokens))` — The default location in which to save take presets
- L43 _public member_ `TSoftObjectPtr<UTakePreset> LastOpenedPreset;` — `UPROPERTY(config)` — Soft reference to the preset last opened on the take recording UI
- L47 _public member_ `bool bIsSequenceOpen;` — `UPROPERTY(config)` — Whether the sequence editor is open for the take recorder
- L51 _public member_ `bool bShowUserSettingsOnUI;` — `UPROPERTY(config)` — Whether the sequence editor is open for the take recorder

#### class `UTakeRecorderProjectSettings`  
`class UTakeRecorderProjectSettings : public UObject`  
_L58-90_
- reflection: `UCLASS(config=EditorSettings, MinimalAPI)`
- inherits: `UObject`
- desc: Universal take recorder settings that apply to a whole take
- L63 _public prototype_ `UTakeRecorderProjectSettings();`
- L66 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L71 _public member_ `FTakeRecorderProjectParameters Settings;` — `UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category="Take Recorder", meta=(ShowOnlyInnerProperties))` — General take recorder settings
- L86 _public member_ `FTakeRecorderHitchProtectionParameters HitchProtectionSettings;` — `UPROPERTY(config, EditAnywhere, Category="Hitch Protection")` — Controls the behaviour for hitch protection. On a high level, it achieves even key spacing in recorded data even when the engine freezes on a frame ("hitches"). When a frames takes longer, the simulation continues to advance at the same fixed time step and assigned to the timecode the frame would have had, if they hitch hadn't occured. Example: frame n at 17:56:12:02 freezes for 1s. In physical time, once the hitches finishes, timecode will have advanced by 1s to 17:56:13:02. However, hitch protection annotates frame n+1 with timecode 17:56:12:03. The subsequent frames continue to be ticked at the same rate, e.g. 1/24s; as long as it takes less CPU time to run the simulation (i.e. CPU time to simulate is less than 1/24s), the simulation time eventually catches up with physical time.
- L89 _public member_ `TArray<TWeakObjectPtr<UObject>> AdditionalSettings;` — Array of externally supplied CDOs that should be displayed on the take recorder project settings

### `Plugins/VirtualProduction/Takes/Source/TakeRecorder/Public/TakeRecorderTracing.h` (Public)


#### Free symbols / members of external scopes

- L9 _macro_ `#define SCOPED_TAKERECORDER_TRACE(TraceName) TRACE_CPUPROFILER_EVENT_SCOPE_ON_CHANNEL(TraceName, TakeRecorderChannel)`
