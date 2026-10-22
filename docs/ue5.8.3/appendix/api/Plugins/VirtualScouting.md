# Plugins / VirtualScouting

- module root: `Plugins/VirtualProduction/VirtualScouting/Source/VirtualScouting`
- headers: 3; symbols: 24
- symbol kinds: class=3, delegate=1, member=13, prototype=7
- PrivateDependencyModuleNames: ConcertSyncClient, ConcertSyncCore, CoreUObject, DeveloperSettings, Engine, EnhancedInput, HeadMountedDisplay, InputCore, InputEditor, InteractiveToolsFramework, LevelEditor, LevelSequence, MultiUserClient, RenderCore, Slate, SlateCore, TypedElementFramework, TypedElementRuntime, UMG, UnrealEd, VREditor
- PublicDependencyModuleNames: CommonUI, Core, XRCreative

### `Plugins/VirtualProduction/VirtualScouting/Source/VirtualScouting/Private/Module.h` (Private)


#### class `FVirtualScoutingModule`  
`class FVirtualScoutingModule : public IModuleInterface`  
_L8-13_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;`
- L12 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/VirtualProduction/VirtualScouting/Source/VirtualScouting/Private/VirtualScoutingLog.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogVirtualScouting, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVirtualScouting, Log, All);`

### `Plugins/VirtualProduction/VirtualScouting/Source/VirtualScouting/Public/VirtualScoutingSettings.h` (Public)


#### class `UVirtualScoutingSettings`  
`class UVirtualScoutingSettings : public UDeveloperSettings`  
_L13-48_
- reflection: `UCLASS(Config=VirtualScoutingSettings, DefaultConfig, DisplayName="Virtual Scouting")`
- inherits: `UDeveloperSettings`
- desc: Per project settings for Virtual Scouting.
- L19 _public prototype_ `virtual FName GetCategoryName() const override;`
- L23 _public prototype_ `static UVirtualScoutingSettings* GetVirtualScoutingSettings();` — `UFUNCTION(BlueprintPure, Category="Virtual Scouting", DisplayName="Virtual Scouting Settings")`
- L26 _public member_ `bool bUseImperial = false;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Virtual Scouting", meta=(DisplayName="Show Measurements in Imperial Units"))`
- L29 _public member_ `bool bViewfinderUseExposure = false;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Virtual Scouting", meta=(DisplayName="Viewfinder Use AutoExposure"))`
- L32 _public member_ `bool bSwapToGrabToolOnSpawnNewActor = true;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Virtual Scouting", meta=(DisplayName="Swap to Grab on Spawn Actor"))`
- L35 _public member_ `float ViewfinderExposureCompensation = 1;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Virtual Scouting", meta=(DisplayName="Viewfinder ExposureCompensation", ClampMin=-15, ClampMax=15))`
- L38 _public member_ `TArray<float> ViewfinderApertureArray = {1.2f, 2.0f, 2.8f, 4.0f, 5.6f, 8.0f, 11.0f, 16.0f, 22.0f};` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Virtual Scouting", meta=(DisplayName="Viewfinder Apertures"))`
- L41 _public member_ `TArray<float> ViewfinderMaskArray = {1.33f, 1.66f, 1.78f, 2.0f, 2.35f, 2.39f };` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Virtual Scouting", meta=(DisplayName="Viewfinder Monitor Masks"))`
- L44 _public member_ `FName SequenceToolCollection;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Virtual Scouting", meta=(DisplayName="Sequence Tool Collection"))`
- L47 _public member_ `FName PlacementToolCollection;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Virtual Scouting", meta = (DisplayName = "Placement Tool Collection"))`

#### class `UVirtualScoutingEditorSettings`  
`class UVirtualScoutingEditorSettings : public UDeveloperSettings`  
_L54-80_
- reflection: `UCLASS(Config=EditorPerProjectUserSettings, DisplayName="Virtual Scouting Editor")`
- inherits: `UDeveloperSettings`
- desc: Per user settings for Virtual Scouting Editor.
- L60 _public prototype_ `virtual FName GetCategoryName() const override;`
- L64 _public prototype_ `static UVirtualScoutingEditorSettings* GetVirtualScoutingEditorSettings();` — `UFUNCTION(BlueprintPure, Category="Virtual Scouting Editor")`
- L67 _public member_ `float FlightSpeed = 4.0f;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Virtual Scouting User", meta=(DisplayName= "Flight Speed", ToolTip="Avatar flying speed. Default is 4.0", ClampMin=1.0f, ClampMax=10.0f))`
- L70 _public member_ `float DragSpeed = 0.7f;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Virtual Scouting User", meta=(DisplayName= "Drag Speed", ToolTip="Speed of movement when you drag-move. Default is 0.7", ClampMin=0.1f, ClampMax=2.0f))`
- L73 _public member_ `bool bEnableTooltips = true;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Virtual Scouting User", meta=(DisplayName= "Show Tooltips", ToolTip="Show Tooltips when in VR. These appear when motioncontroller is brought near to HMD"))`
- L76 _public member_ `bool bUseSmoothRotation = false;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Virtual Scouting User", meta=(DisplayName= "Use Smooth Rotation", ToolTip="True = Rotate smoothly. False = Flick Rotate. Default is Flick Rotate"))`
- L79 _public member_ `bool bUseTeleportRotation = false;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category="Virtual Scouting User", meta=(DisplayName= "Use Teleport Rotation", ToolTip="Use the forward axis roll from the motion controller to define and adjust teleport rotation"))`
