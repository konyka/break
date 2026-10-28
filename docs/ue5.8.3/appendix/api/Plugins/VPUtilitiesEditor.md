# Plugins / VPUtilitiesEditor

- module root: `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilitiesEditor`
- headers: 13; symbols: 168
- symbol kinds: class=16, delegate=1, enum=1, enumerator=7, function=10, member=37, prototype=96
- PrivateDependencyModuleNames: CinematicCamera, EditorFramework, EditorStyle, GameplayTags, InputCore, LevelEditor, OSC, PlacementMode, Settings, TimeManagement, UMG, UMGEditor, UnrealEd, VPBookmark, VPRoles, VPSettings, WorkspaceMenuStructure
- PublicDependencyModuleNames: Blutility, Core, CoreUObject, EditorSubsystem, Engine, Slate, SlateCore, VPUtilities, VREditor

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilitiesEditor/Private/SGenlockProvider.h` (Private)


#### class `SGenlockProvider`  
`class SGenlockProvider : public SCompoundWidget, public FTickableEditorObject`  
_L16-54_
- inherits: `SCompoundWidget,FTickableEditorObject`
- desc: This widget display the current state of a genlock setup witch is also know as the Custom TimeStep
- L20 _public function_ `SLATE_BEGIN_ARGS(SGenlockProvider)`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L32 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L35 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L36 _public prototype_ `virtual TStatId GetStatId() const override;`
- L41 _private member_ `double AvgIdleTime;`
- L42 _private member_ `bool bIsAvgIdleTimeValid;`
- L44 _private prototype_ `TSharedRef<SWidget> ConstructDesiredFPS() const;`
- L45 _private prototype_ `TSharedRef<SWidget> ConstructStateDisplay() const;`
- L47 _private prototype_ `FText HandleStateText() const;`
- L48 _private prototype_ `FSlateColor HandleStateColorAndOpacity() const;`
- L49 _private prototype_ `FText HandleDesiredFPSText() const;`
- L50 _private prototype_ `FText HandleGenlockSourceText() const;`
- L51 _private prototype_ `TOptional<float> GetFPSFraction() const;`
- L52 _private prototype_ `EVisibility HandleDesiredFPSVisibility() const;`
- L53 _private prototype_ `FText GetFPSTooltip() const;`

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilitiesEditor/Private/SGenlockProviderTab.h` (Private)


#### class `SGenlockProviderTab`  
`class SGenlockProviderTab : public SCompoundWidget`  
_L15-29_
- inherits: `SCompoundWidget`
- desc: SGenlockProviderTab
- L18 _public prototype_ `static void RegisterNomadTabSpawner(TSharedRef<FWorkspaceItem> InWorkspaceItem);`
- L19 _public prototype_ `static void UnregisterNomadTabSpawner();`
- L22 _public function_ `SLATE_BEGIN_ARGS(SGenlockProviderTab)`
- L23 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L28 _private prototype_ `TSharedRef<SWidget> OnGetMenuContent();`

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilitiesEditor/Private/STimecodeProviderTab.h` (Private)


#### class `STimecodeProviderTab`  
`class STimecodeProviderTab : public SCompoundWidget`  
_L16-34_
- inherits: `SCompoundWidget`
- desc: STimecodeProviderTab
- L19 _public prototype_ `static void RegisterNomadTabSpawner();`
- L20 _public prototype_ `static void UnregisterNomadTabSpawner();`
- L23 _public function_ `SLATE_BEGIN_ARGS(STimecodeProviderTab)`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L29 _private prototype_ `float GetFrameDelay() const;`
- L30 _private prototype_ `void SetFrameDelay(float, ETextCommit::Type);`
- L33 _private prototype_ `TSharedRef<SWidget> OnGetMenuContent();`

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilitiesEditor/Private/VPUtilitiesEditorModule.h` (Private)


#### class `FVPUtilitiesEditorModule`  
`class FVPUtilitiesEditorModule : public IVPUtilitiesEditorModule`  
_L14-53_
- inherits: `IVPUtilitiesEditorModule`
- L18 _public prototype_ `virtual void StartupModule() override;`
- L19 _public prototype_ `virtual void ShutdownModule() override;`
- L25 _public prototype_ `virtual UOSCServer* GetOSCServer() const override;` — Get an OSC server that can be started at the module's startup.
- L31 _public prototype_ `virtual const FPlacementCategoryInfo* GetVirtualProductionPlacementCategoryInfo() const override;` — Returns the Placement Mode Info for the Virtual Production category. The category will be registered if it has not already been.
- L35 _private prototype_ `void RegisterSettings();` — Register VPUtilities settings.
- L38 _private prototype_ `void UnregisterSettings();` — Unregister VPUtilities settings
- L41 _private prototype_ `void InitializeOSCServer();` — Start an OSC server and bind a an OSC listener to it.
- L44 _private prototype_ `bool OnSettingsModified();` — Handler for when VP utilities settings are changed.
- L48 _private member_ `TStrongObjectPtr<UOSCServer> OSCServer;` — The default OSC server.
- L51 _private member_ `static const FName VPRoleNotificationBarIdentifier;` — Virtual production role identifier for the notification bar.

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogVPUtilitiesEditor, Log, Log);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVPUtilitiesEditor, Log, Log);`

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilitiesEditor/Private/VPUtilitiesEditorStyle.h` (Private)


#### class `FVPUtilitiesEditorStyle`  
`class FVPUtilitiesEditorStyle`  
_L12-21_
- L15 _public prototype_ `static void Register();`
- L16 _public prototype_ `static void Unregister();`
- L18 _public prototype_ `static FName GetStyleSetName();`
- L20 _public prototype_ `static const ISlateStyle& Get();`

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilitiesEditor/Public/IVPUtilitiesEditorModule.h` (Public)


#### class `IVPUtilitiesEditorModule`  
`class IVPUtilitiesEditorModule : public IModuleInterface`  
_L12-37_
- inherits: `IModuleInterface`
- L21 _public function_ `static IVPUtilitiesEditorModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L30 _public prototype_ `virtual UOSCServer* GetOSCServer() const = 0;` — Get an OSC server that can be started at the module's startup.
- L36 _public prototype_ `virtual const FPlacementCategoryInfo* GetVirtualProductionPlacementCategoryInfo() const = 0;` — Returns the Placement Mode Info for the Virtual Production category. The category will be registered if it has not already been.

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilitiesEditor/Public/STimecodeProvider.h` (Public)


#### class `STimecodeProvider`  
`class STimecodeProvider : public SCompoundWidget`  
_L20-80_
- inherits: `SCompoundWidget`
- L23 _public function_ `SLATE_BEGIN_ARGS(STimecodeProvider) : _TimecodeProviderColor(FLinearColor::Gray) , _DisplayFrameRate(true) , _DisplaySynchronizationState(true) , _TimecodeColor(FLinearColor::White) , _DisplayLabel(false) , _LabelColor(FLinearColor::Gray)`
- L41 _public prototype_ `SLATE_ATTRIBUTE(FSlateFontInfo, TimecodeProviderFont) SLATE_ATTRIBUTE(FSlateColor, TimecodeProviderColor) SLATE_ARGUMENT(bool, DisplayFrameRate) SLATE_ARGUMENT(bool, DisplaySynchronizationState) SLATE_ATTRIBUTE(TWeakObjectPtr<UTimecodeProvider>, OverrideTimecodeProvider) SLATE_ATTRIBUTE(FSlateFontInfo, TimecodeFont) SLATE_ATTRIBUTE(FSlateColor, TimecodeColor) SLATE_ATTRIBUTE(bool, DisplayLabel) SLATE_ATTRIBUTE(FSlateFontInfo, LabelFont) SLATE_ATTRIBUTE(FSlateColor, LabelColor) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The font for this TimecodeProvider text
- L73 _private prototype_ `const UTimecodeProvider* GetTimecodeProvider() const;`
- L74 _private prototype_ `FSlateColor HandleIconColorAndOpacity() const;`
- L75 _private prototype_ `FText HandleStateText() const;`
- L79 _private member_ `TAttribute<TWeakObjectPtr<UTimecodeProvider>> OverrideTimecodeProvider;`

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilitiesEditor/Public/VPEditorTickableActorBase.h` (Public)


#### class `AVPEditorTickableActorBase`  
`class AVPEditorTickableActorBase : public AVPViewportTickableActorBase`  
_L10-13_
- reflection: `UCLASS(Abstract)`
- inherits: `AVPViewportTickableActorBase`
- desc: Actor that tick in the Editor viewport with the event EditorTick.

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilitiesEditor/Public/VPScoutingSubsystem.h` (Public)


#### enum `EVProdPanelIDs`  
`enum class EVProdPanelIDs : uint8`  
_L15-24_
- reflection: `UENUM(BlueprintType)`
- L17 _public enumerator_ `Main`
- L18 _public enumerator_ `Left`
- L19 _public enumerator_ `Right`
- L20 _public enumerator_ `Context`
- L21 _public enumerator_ `Timeline`
- L22 _public enumerator_ `Measure`
- L23 _public enumerator_ `Gaffer`

#### class `UVPScoutingSubsystemHelpersBase`  
`class UE_DEPRECATED(5.5,"Code will be removed from UE5.7") UVPScoutingSubsystemHelpersBase : public UObject`  
_L32-35_
- reflection: `UCLASS(Abstract, Blueprintable, MinimalAPI, meta = (ShowWorldContextPin))`
- inherits: `UObject`

#### class `UVPScoutingSubsystemGestureManagerBase`  
`class UE_DEPRECATED(5.5,"This class will be removed from UE5.7") UVPScoutingSubsystemGestureManagerBase : public UObject, public FTickableEditorObject`  
_L43-76_
- reflection: `UCLASS(NotPlaceable, Blueprintable, MinimalAPI, meta = (ShowWorldContextPin))`
- inherits: `UObject,FTickableEditorObject`
- L48 _public prototype_ `UVPScoutingSubsystemGestureManagerBase();`
- L52 _public prototype_ `void EditorTick(float DeltaSeconds);` — `UE_DEPRECATED(5.5,"Code will be removed from UE5.7")` — `UFUNCTION(BlueprintNativeEvent, CallInEditor, BlueprintCallable, Category = "Tick", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))`
- L56 _public prototype_ `void OnVREditingModeEnter();` — `UE_DEPRECATED(5.5,"Code will be removed from UE5.7")` — `UFUNCTION(BlueprintNativeEvent, CallInEditor, BlueprintCallable, Category = "VR", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))`
- L60 _public prototype_ `void OnVREditingModeExit();` — `UE_DEPRECATED(5.5,"Code will be removed from UE5.7")` — `UFUNCTION(BlueprintNativeEvent, CallInEditor, BlueprintCallable, Category = "VR", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))`
- L63 _public prototype_ `virtual void BeginDestroy() override;`
- L67 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L68 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L69 _public prototype_ `virtual bool IsTickable() const override;`
- L70 _public prototype_ `virtual TStatId GetStatId() const override;`
- L74 _private prototype_ `void OnVREditingModeEnterCallback();`
- L75 _private prototype_ `void OnVREditingModeExitCallback();`

#### class `UVPScoutingSubsystem`  
`class UE_DEPRECATED(5.5,"This class will be removed from UE5.7") UVPScoutingSubsystem : public UEditorSubsystem`  
_L85-298_
- reflection: `UCLASS()`
- inherits: `UEditorSubsystem`
- L90 _public prototype_ `UVPScoutingSubsystem();`
- L92 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L93 _public prototype_ `virtual void Deinitialize() override;`
- L98 _public member_ `TObjectPtr<UVPScoutingSubsystemHelpersBase> VPSubsystemHelpers;` — `UE_DEPRECATED(5.5,"Property will be removed from UE5.7")` — `UPROPERTY(Transient, BlueprintReadOnly, Category = "Virtual Production", meta=(DeprecatedProperty, DeprecationMessage="This property is deprecated"))` — Subsystems can't have any Blueprint implementations, so we attach this class for any BP logic that we to provide.
- L103 _public member_ `TObjectPtr<UVPScoutingSubsystemGestureManagerBase> GestureManager;` — `UE_DEPRECATED(5.5,"Property will be removed from UE5.7")` — `UPROPERTY(Transient, BlueprintReadOnly, Category = "Virtual Production", meta=(DeprecatedProperty, DeprecationMessage="This property is deprecated"))` — GestureManager that manage some user input in VR editor.
- L108 _public member_ `bool IsSettingsMenuOpen;` — `UE_DEPRECATED(5.5,"Property will be removed from UE5.7")` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Menu", meta=(DeprecatedProperty, DeprecationMessage="This property is deprecated"))` — bool to keep track of whether the settings menu panel in the main menu is open
- L113 _public member_ `float GripNavSpeedCoeff;` — `UE_DEPRECATED(5.5,"Property will be removed from UE5.7")` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Virtual Production", meta=(DeprecatedProperty, DeprecationMessage="This property is deprecated"))` — This is a multiplier for grip nav speed so we can keep the grip nav value in the range 0-1 and increase this variable if we need a bigger range
- L119 _public prototype_ `void ToggleVRScoutingUI(UPARAM(ref) FVREditorFloatingUICreationContext& CreationContext);` — `UE_DEPRECATED(5.5,"Function will be removed from UE5.7")` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))` — Open a widget UI in front of the user. Opens default VProd UI (defined via the 'Virtual Scouting User Interface' setting) if null.
- L124 _public prototype_ `void HideInfoDisplayPanel();` — `UE_DEPRECATED(5.5,"Function will be removed from UE5.7")` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))` — Hide VR Sequencer Window
- L129 _public prototype_ `bool IsVRScoutingUIOpen(const FName& PanelID);` — `UE_DEPRECATED(5.5,"Function will be removed from UE5.7")` — `UFUNCTION(BlueprintPure, Category = "Virtual Production", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))` — Check whether a widget UI is open
- L134 _public prototype_ `AVREditorFloatingUI* GetPanelActor(const FName& PanelID) const;` — `UE_DEPRECATED(5.5,"Function will be removed from UE5.7")` — `UFUNCTION(BlueprintPure, Category = "Virtual Production", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))` — Get UI panel Actor from the passed ID
- L139 _public prototype_ `UUserWidget* GetPanelWidget(const FName& PanelID) const;` — `UE_DEPRECATED(5.5,"Function will be removed from UE5.7")` — `UFUNCTION(BlueprintPure, Category = "Virtual Production", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))` — Get UI panel widget from the passed ID
- L143 _public prototype_ `static TArray<UVREditorInteractor*> GetActiveEditorVRControllers();` — `UE_DEPRECATED(5.5,"Function will be removed from UE5.7")` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))`
- L147 _public function_ `static const FName GetVProdPanelID(const EVProdPanelIDs Panel)` — `UE_DEPRECATED(5.5,"Function will be removed from UE5.7")` — `UFUNCTION(BlueprintPure, Category = "Virtual Production", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))`
- L172 _public prototype_ `static FString GetDirectorName();` — `UE_DEPRECATED(5.5,"Function will be removed from UE5.7")` — `UFUNCTION(BlueprintPure, Category = "Virtual Production", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))`
- L176 _public prototype_ `static FString GetShowName();` — `UE_DEPRECATED(5.5,"Function will be removed from UE5.7")` — `UFUNCTION(BlueprintPure, Category = "Virtual Production", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))`
- L182 _public prototype_ `static bool IsUsingMetricSystem();` — `UE_DEPRECATED(5.5,"Function will be removed from UE5.7")` — `UFUNCTION(BlueprintPure, Category = "Virtual Production", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))` — Whether the VR user wants to use the metric system instead of imperial
- L187 _public prototype_ `static void SetIsUsingMetricSystem(const bool bInUseMetricSystem);` — `UE_DEPRECATED(5.5,"Function will be removed from UE5.7")` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))` — Set whether the VR user wants to use the metric system instead of imperial
- L192 _public prototype_ `static bool IsUsingTransformGizmo();` — `UE_DEPRECATED(5.5,"Function will be removed from UE5.7")` — `UFUNCTION(BlueprintPure, Category = "Virtual Production", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))` — Whether the VR user wants to have the transform gizmo enabled
- L197 _public prototype_ `static void SetIsUsingTransformGizmo(const bool bInIsUsingTransformGizmo);` — `UE_DEPRECATED(5.5,"Function will be removed from UE5.7")` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))` — Set whether the VR user wants to have the transform gizmo enabled
- L202 _public prototype_ `static void SetShowTransformGizmoCVar(const bool bInShowTransformGizmoCVar);` — `UE_DEPRECATED(5.5,"Function will be removed from UE5.7")` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))` — Set value of cvar "VI.ShowTransformGizmo"
- L207 _public prototype_ `static float GetFlightSpeed();` — `UE_DEPRECATED(5.5,"Function will be removed from UE5.7")` — `UFUNCTION(BlueprintPure, Category = "Virtual Production", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))` — Get flight speed for scouting in VR
- L212 _public prototype_ `static void SetFlightSpeed(const float InFlightSpeed);` — `UE_DEPRECATED(5.5,"Function will be removed from UE5.7")` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))` — Set flight speed for scouting in VR
- L217 _public prototype_ `static float GetGripNavSpeed();` — `UE_DEPRECATED(5.5,"Function will be removed from UE5.7")` — `UFUNCTION(BlueprintPure, Category = "Virtual Production", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))` — Get grip nav speed for scouting in VR
- L222 _public prototype_ `static void SetGripNavSpeed(const float InGripNavSpeed);` — `UE_DEPRECATED(5.5,"Function will be removed from UE5.7")` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))` — Set grip nav speed for scouting in VR
- L227 _public prototype_ `static bool IsUsingInertiaDamping();` — `UE_DEPRECATED(5.5,"Function will be removed from UE5.7")` — `UFUNCTION(BlueprintPure, Category = "Virtual Production", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))` — Whether grip nav inertia is enabled when scouting in VR
- L232 _public prototype_ `static void SetIsUsingInertiaDamping(const bool bInIsUsingInertiaDamping);` — `UE_DEPRECATED(5.5,"Function will be removed from UE5.7")` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))` — Set whether grip nav inertia is enabled when scouting in VR
- L237 _public prototype_ `static void SetInertiaDampingCVar(const float InInertiaDamping);` — `UE_DEPRECATED(5.5,"Function will be removed from UE5.7")` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))` — Set value of cvar "VI.HighSpeedInertiaDamping"
- L242 _public prototype_ `static bool IsHelperSystemEnabled();` — `UE_DEPRECATED(5.5,"Function will be removed from UE5.7")` — `UFUNCTION(BlueprintPure, Category = "Virtual Production", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))` — Whether the helper system on the controllers is enabled
- L247 _public prototype_ `static void SetIsHelperSystemEnabled(const bool bInIsHelperSystemEnabled);` — `UE_DEPRECATED(5.5,"Function will be removed from UE5.7")` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))` — Set whether the helper system on the controllers is enabled
- L252 _public prototype_ `static UVREditorMode* GetVREditorMode();` — `UE_DEPRECATED(5.5,"Function will be removed from UE5.7")` — `UFUNCTION(BlueprintPure, Category = "Virtual Production", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))` — Get VR Editor Mode object
- L257 _public prototype_ `static bool EnterVRMode();` — `UE_DEPRECATED(5.5,"Function will be removed from UE5.7")` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))` — Enter VR Mode
- L262 _public prototype_ `static void ExitVRMode();` — `UE_DEPRECATED(5.5,"Function will be removed from UE5.7")` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))` — Exit VR Mode
- L267 _public prototype_ `static bool IsLocationGridSnappingEnabled();` — `UE_DEPRECATED(5.5,"Function will be removed from UE5.7")` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))` — Whether location grid snapping is enabled
- L272 _public prototype_ `static void ToggleLocationGridSnapping();` — `UE_DEPRECATED(5.5,"Function will be removed from UE5.7")` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))` — Toggle location grid snapping
- L277 _public prototype_ `static bool IsRotationGridSnappingEnabled();` — `UE_DEPRECATED(5.5,"Function will be removed from UE5.7")` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))` — Whether rotation grid snapping is enabled
- L282 _public prototype_ `static void ToggleRotationGridSnapping();` — `UE_DEPRECATED(5.5,"Function will be removed from UE5.7")` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))` — Toggle rotation grid snapping
- L286 _private member_ `FDelegateHandle EngineInitCompleteDelegate;`
- L288 _private prototype_ `void OnEngineInitComplete();`
- L291 _private member_ `static const FName VProdPanelID;` — Static IDs when submitting open/close requests for the VProd main menu panels. VREditorUISystem uses FNames to manage its panels, so these should be used for consistency.
- L292 _private member_ `static const FName VProdPanelLeftID;`
- L293 _private member_ `static const FName VProdPanelRightID;`
- L294 _private member_ `static const FName VProdPanelContextID;`
- L295 _private member_ `static const FName VProdPanelTimelineID;`
- L296 _private member_ `static const FName VProdPanelMeasureID;`
- L297 _private member_ `static const FName VProdPanelGafferID;`

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilitiesEditor/Public/VPTransientEditorTickableActorBase.h` (Public)


#### class `AVPTransientEditorTickableActorBase`  
`class AVPTransientEditorTickableActorBase : public AVPEditorTickableActorBase`  
_L13-16_
- reflection: `UCLASS(Abstract, Transient)`
- inherits: `AVPEditorTickableActorBase`
- desc: Specific VPEditorTickableActor explicitely marked as Transient

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilitiesEditor/Public/VPUtilitiesEditorBlueprintLibrary.h` (Public)


#### class `UVPUtilitiesEditorBlueprintLibrary`  
`class UVPUtilitiesEditorBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L13-41_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L24 _public prototype_ `static AVPEditorTickableActorBase* SpawnVPEditorTickableActor(UObject* ContextObject, const TSubclassOf<AVPEditorTickableActorBase> ActorClass, const FVector Location, const FRotator Rotation);` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production")` — Spawn an editor-only virtual production tickable actor @note Actors based on the non-transient AVPEditorTickableActorBase will be saved in the level. @note Being non-transient also means that transactions happening on them will be replicated on other connected multi-user machines
- L32 _public prototype_ `static AVPTransientEditorTickableActorBase* SpawnVPTransientEditorTickableActor(UObject* ContextObject, const TSubclassOf<AVPTransientEditorTickableActorBase> ActorClass, const FVector Location, const FRotator Rotation);` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production")` — Spawn an editor-only transient virtual production tickable actor @note Actors based on the transient AVPTransientEditorTickableActorBase will NOT be saved in the level. @note Being transient also means that transactions happening on them will NOT be replicated on other connected multi-user machines
- L36 _public prototype_ `static UTexture* ImportSnapshotTexture(FString FileName, FString SubFolderName, FString AbsolutePathPackage);` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production")` — Imports Image file into VirtualProduction/Snapshots/ folder
- L40 _public prototype_ `static class UOSCServer* GetDefaultOSCServer();` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production")` — Get the default OSC server.

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilitiesEditor/Public/VPUtilitiesEditorSettings.h` (Public)


#### class `UVPUtilitiesEditorSettings`  
`class UVPUtilitiesEditorSettings : public UObject`  
_L19-100_
- reflection: `UCLASS(config=VirtualProductionUtilities)`
- inherits: `UObject`
- desc: Virtual Production utilities settings for editor
- L24 _public prototype_ `UVPUtilitiesEditorSettings();`
- L29 _public member_ `TSoftClassPtr<UEditorUtilityWidget> VirtualScoutingUI;` — `UE_DEPRECATED(5.5,"This property will be removed from UE5.7")` — `UPROPERTY(EditAnywhere, config, Category = "Legacy Virtual Scouting", meta = (DisplayName = "Virtual Scouting User Interface", DeprecatedProperty, DeprecationMessage="This property is deprecated"))` — The default user interface that we'll use for virtual scouting
- L34 _public member_ `float FlightSpeed = 0.5f;` — `UE_DEPRECATED(5.5,"This property will be removed from UE5.7")` — `UPROPERTY(EditAnywhere, config, Category = "Legacy Virtual Scouting", meta = (ClampMin = "0.0", ClampMax = "1.0", DisplayName = "Virtual Scouting Flight Speed", DeprecatedProperty, DeprecationMessage="This property is deprecated"))` — Speed when flying in VR
- L39 _public member_ `float GripNavSpeed = 0.25f;` — `UE_DEPRECATED(5.5,"This property will be removed from UE5.7")` — `UPROPERTY(EditAnywhere, config, Category = "Legacy Virtual Scouting", meta = (ClampMin = "0.0", ClampMax = "1.0", DisplayName = "Virtual Scouting Grip Nav Speed", DeprecatedProperty, DeprecationMessage="This property is deprecated"))` — Speed when using grip nav in VR
- L44 _public member_ `bool bUseMetric = false;` — `UE_DEPRECATED(5.5,"This property will be removed from UE5.7")` — `UPROPERTY(EditAnywhere, config, Category = "Legacy Virtual Scouting", meta = (DisplayName = "Show Measurements In Metric Units", DeprecatedProperty, DeprecationMessage="This property is deprecated"))` — Whether to use the metric system or imperial for measurements
- L49 _public member_ `bool bUseTransformGizmo = false;` — `UE_DEPRECATED(5.5,"This property will be removed from UE5.7")` — `UPROPERTY(EditAnywhere, config, Category = "Legacy Virtual Scouting", meta = (DisplayName = "Enable Transform Gizmo In VR", DeprecatedProperty, DeprecationMessage="This property is deprecated"))` — Whether to enable or disable the transform gizmo
- L54 _public member_ `bool bUseGripInertiaDamping = true;` — `UE_DEPRECATED(5.5,"This property will be removed from UE5.7")` — `UPROPERTY(EditAnywhere, config, Category = "Legacy Virtual Scouting", meta = (DisplayName = "Use Grip Inertia Damping", DeprecatedProperty, DeprecationMessage="This property is deprecated"))` — If true, the user will use inertia damping to stop after grip nav. Otherwise the user will just stop immediately
- L59 _public member_ `float InertiaDamping = 0.95f;` — `UE_DEPRECATED(5.5,"This property will be removed from UE5.7")` — `UPROPERTY(EditAnywhere, config, Category = "Legacy Virtual Scouting", meta = (ClampMin = "0.0", ClampMax = "1.0", DisplayName = "Inertia Damping", DeprecatedProperty, DeprecationMessage="This property is deprecated"))` — Damping applied to inertia
- L64 _public member_ `bool bIsHelperSystemEnabled = true;` — `UE_DEPRECATED(5.5,"Code will be removed from UE5.7")` — `UPROPERTY(EditAnywhere, config, Category = "Legacy Virtual Scouting", meta = (DisplayName = "Helper System Enabled ", DeprecatedProperty, DeprecationMessage="This property is deprecated"))` — Whether the helper system on the controllers is enabled
- L68 _public member_ `bool bStartOSCServerAtLaunch;` — `UPROPERTY(config, EditAnywhere, Category = "OSC", DisplayName = "Start an OSC Server when the editor launches")` — When enabled, an OSC server will automatically start on launch.
- L72 _public member_ `FString OSCServerAddress;` — `UPROPERTY(config, EditAnywhere, Category = "OSC", DisplayName = "OSC Server Address")` — The OSC server's address.
- L76 _public member_ `uint16 OSCServerPort;` — `UPROPERTY(config, EditAnywhere, Category = "OSC", DisplayName = "OSC Server Port")` — The OSC server's port.
- L80 _public member_ `TArray<FSoftObjectPath> StartupOSCListeners;` — `UPROPERTY(config, EditAnywhere, Category = "OSC", meta = (AllowedClasses = "/Script/Blutility.EditorUtilityBlueprint", DisplayName = "OSC Listeners"))` — What EditorUtilityObject should be ran on editor launch.
- L85 _public member_ `FSoftClassPath ScoutingSubsystemEditorUtilityClassPath;` — `UE_DEPRECATED(5.5,"Code will be removed from UE5.7")` — `UPROPERTY(config, meta = (MetaClass = "/Script/VPUtilitiesEditor.VPScoutingSubsystemHelpersBase"))` — ScoutingSubsystem class to use for Blueprint helpers
- L90 _public member_ `FSoftClassPath GestureManagerEditorUtilityClassPath;` — `UE_DEPRECATED(5.5,"Code will be removed from UE5.7")` — `UPROPERTY(config, meta = (MetaClass = "/Script/VPUtilitiesEditor.VPScoutingSubsystemGestureManagerBase"))` — GestureManager class to use by the ScoutingSubsystem
- L95 _public member_ `TArray<FSoftClassPath> AdditionnalClassToLoad;` — `UE_DEPRECATED(5.5,"Code will be removed from UE5.7")` — `UPROPERTY(config)` — GestureManager class to use by the ScoutingSubsystem
- L99 _public member_ `FSoftObjectPath VPSplinePreviewMeshPath;` — `UE_DEPRECATED(5.5,"Code will be removed from UE5.7")` — `UPROPERTY(config, meta = (AllowedClasses = "/Script/Engine.StaticMesh"))`

#### class `UVPUtilitiesEditorUserSettings`  
`class UVPUtilitiesEditorUserSettings : public UObject`  
_L104-141_
- reflection: `UCLASS(MinimalAPI, config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: Per-User editor settings for Virtual Production utilities.
- L109 _public function_ `virtual void PostInitProperties() override`
- L132 _public member_ `FString OverrideOSCServerAddress;` — `UPROPERTY(config, EditAnywhere, Category = "OSC", DisplayName = "OSC Server Address")` — If provided, this address will override the OSC server address provided in the project settings. Can also be specified on the command line through -VPOSCServerAddress=<Address>
- L139 _public member_ `uint16 OverrideOSCServerPort;` — `UPROPERTY(config, EditAnywhere, Category = "OSC", DisplayName = "OSC Server Port")` — If provided, this port will override the OSC server port provided in the project settings. Can also be specified on the command line through -VPOSCServerPort=<Port>

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilitiesEditor/Public/VRTool.h` (Public)


#### class `AVRTool`  
`class UE_DEPRECATED(5.5,"This class will be removed from UE5.7") AVRTool : public AVPTransientEditorTickableActorBase`  
_L14-56_
- reflection: `UCLASS()`
- inherits: `AVPTransientEditorTickableActorBase`
- L18 _private prototype_ `AVRTool(const FObjectInitializer& ObjectInitializer);`
- L20 _private prototype_ `virtual void OnConstruction(const FTransform& Transform) override;`
- L22 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L27 _private function_ `UInputComponent* GetInputComponent() const` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Input|Editor")` — Returns the current InputComponent on this utility actor. This will be NULL unless bReceivesEditorInput is set to true.
- L33 _private prototype_ `void SetReceivesEditorInput(bool bInValue);` — `UFUNCTION(BlueprintSetter, Category = "Input|Editor")`
- L36 _private function_ `bool GetReceivesEditorInput() const` — `UFUNCTION(BlueprintGetter, BlueprintPure, Category = "Input|Editor")`
- L44 _private prototype_ `void CreateEditorInput();` — Creates the EditorOnlyInputComponent if it does not already exist and registers all subobject callbacks to it
- L47 _private prototype_ `void RemoveEditorInput();` — Removes the EditorOnlyInputComponent from this utility actor
- L50 _private member_ `TObjectPtr<UInputComponent> EditorOnlyInputComponent;` — `UPROPERTY(Transient, DuplicateTransient, meta=(DeprecatedProperty, DeprecationMessage="This is deprecated"))`
- L54 _private member_ `bool bReceivesEditorInput = false;` — `UPROPERTY(EditAnywhere, Category = "Input|Editor", BlueprintSetter = SetReceivesEditorInput, BlueprintGetter = GetReceivesEditorInput, meta=(DeprecatedProperty, DeprecationMessage="This is deprecated"))` — If set to true, then this actor will be able to recieve input delegate callbacks when in the editor.
