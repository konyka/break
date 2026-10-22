# Developer / SourceControlViewport

- module root: `Source/Developer/SourceControlViewport`
- headers: 5; symbols: 71
- symbol kinds: class=4, enum=1, enumerator=4, function=3, member=19, namespace=1, prototype=39
- PrivateDependencyModuleNames: Core, Engine, InputCore, LevelEditor, Slate, SlateCore, SourceControl, ToolMenus, UnrealEd
- PublicDependencyModuleNames: CoreUObject, DeveloperSettings

### `Source/Developer/SourceControlViewport/Private/SourceControlViewportMenu.h` (Private)


#### class `FSourceControlViewportMenu`  
`class FSourceControlViewportMenu : public TSharedFromThis<FSourceControlViewportMenu, ESPMode::ThreadSafe>`  
_L15-44_
- inherits: `TSharedFromThis<FSourceControlViewportMenu,ESPMode::ThreadSafe>`
- desc: Adds an options menu to the Viewport's SHOW pill.
- L18 _public prototype_ `FSourceControlViewportMenu();`
- L19 _public prototype_ `~FSourceControlViewportMenu();`
- L22 _public prototype_ `void Init();`
- L23 _public prototype_ `void SetEnabled(bool bInEnabled);`
- L26 _private prototype_ `void InsertViewportMenu();`
- L27 _private prototype_ `void PopulateViewportMenu(UToolMenu* InMenu);`
- L28 _private prototype_ `void PopulateRevisionControlMenu(UToolMenu* InMenu);`
- L29 _private prototype_ `void RemoveViewportMenu();`
- L32 _private prototype_ `void ShowAll(TWeakPtr<SLevelViewport> Viewport);`
- L33 _private prototype_ `void HideAll(TWeakPtr<SLevelViewport> Viewport);`
- L35 _private prototype_ `void ToggleHighlight(TWeakPtr<SLevelViewport> Viewport, ESourceControlStatus Status);`
- L36 _private prototype_ `bool IsHighlighted(TWeakPtr<SLevelViewport> Viewport, ESourceControlStatus Status) const;`
- L38 _private prototype_ `void OnOpacityCommitted(uint8 NewValue, ETextCommit::Type CommitType, TWeakPtr<SLevelViewport> Viewport);`
- L39 _private prototype_ `void SetOpacityValue(uint8 NewValue, TWeakPtr<SLevelViewport> Viewport);`
- L40 _private prototype_ `uint8 GetOpacityValue(TWeakPtr<SLevelViewport> Viewport) const;`
- L43 _private prototype_ `void RecordToggleEvent(const FString& Param, bool bEnabled) const;`

### `Source/Developer/SourceControlViewport/Private/SourceControlViewportModule.h` (Private)


#### class `FSourceControlViewportModule`  
`class FSourceControlViewportModule : public IModuleInterface`  
_L11-42_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L23 _public function_ `static FSourceControlViewportModule& Get()` — Gets a reference to the source control viewport module instance. @return A reference to the source control viewport module.
- L29 _public function_ `static FSourceControlViewportModule* TryGet()`
- L36 _private prototype_ `void HandleCVarChanged(IConsoleVariable* Variable);`
- L37 _private prototype_ `void UpdateSettings();`
- L40 _private member_ `TSharedPtr<FSourceControlViewportMenu> ViewportMenu;`
- L41 _private member_ `TSharedPtr<FSourceControlViewportToolTips> ViewportToolTips;`

### `Source/Developer/SourceControlViewport/Private/SourceControlViewportToolTips.h` (Private)


#### class `FSourceControlViewportToolTips`  
`class FSourceControlViewportToolTips : public TSharedFromThis<FSourceControlViewportToolTips, ESPMode::ThreadSafe>`  
_L15-65_
- inherits: `TSharedFromThis<FSourceControlViewportToolTips,ESPMode::ThreadSafe>`
- desc: Adds a tooltip widget to the viewport.
- L18 _public prototype_ `FSourceControlViewportToolTips();`
- L19 _public prototype_ `~FSourceControlViewportToolTips();`
- L22 _public prototype_ `void Init();`
- L23 _public prototype_ `void SetEnabled(bool bInEnabled);`
- L25 _public prototype_ `bool Tick(float DeltaTime);`
- L28 _private prototype_ `void UpdateCanvas(float DeltaTime);`
- L29 _private prototype_ `void UpdateToolTip();`
- L31 _private prototype_ `void InsertCanvas();`
- L32 _private prototype_ `void RemoveCanvas();`
- L34 _private prototype_ `FVector2D GetToolTipSize() const;`
- L35 _private prototype_ `FVector2D GetToolTipPosition() const;`
- L39 _private member_ `FTSTicker::FDelegateHandle TickHandle;` — The ticker handle
- L42 _private member_ `TSharedPtr<SCanvas> CanvasWidget;` — The canvas widget
- L45 _private member_ `TSharedPtr<SToolTip> ToolTipWidget;` — The tooltip widget that'll be positioned on the canvas
- L48 _private member_ `TWeakPtr<SLevelViewport> ViewportWidget;` — The viewport in which the canvas widget is added
- L51 _private member_ `TWeakObjectPtr<AActor> Actor;` — The actor in the viewport that's currently hovered
- L54 _private member_ `FText ToolTipText;` — The tooltip text determined for the actor
- L57 _private member_ `int32 ActorMouseX = 0;` — The previous mouse coordinates
- L58 _private member_ `int32 ActorMouseY = 0;`
- L61 _private member_ `float DelayTime = 0;` — The time since the actor became relevant
- L64 _private member_ `bool bEnabled = false;` — The enabled state of the tooltips

### `Source/Developer/SourceControlViewport/Private/SourceControlViewportUtils.h` (Private)


#### enum `ESourceControlStatus`  
`enum class ESourceControlStatus : uint8`  
_L12-25_
- reflection: `UENUM()`
- L15 _public enumerator_ `CheckedOutByOtherUser` — The file is checked out by another user
- L18 _public enumerator_ `NotAtHeadRevision` — The file is not at the latest revision
- L21 _public enumerator_ `CheckedOut` — The file is checked out by self
- L24 _public enumerator_ `OpenForAdd` — The file is added by self

#### Free symbols / members of external scopes

- L27 _namespace_ `namespace SourceControlViewportUtils`
- L31 _prototype_ `bool GetFeedbackEnabled(FViewportClient* ViewportClient, ESourceControlStatus Status);` (scope `SourceControlViewportUtils`) — Helper method to get the viewport feedback value from the viewport.
- L34 _prototype_ `void SetFeedbackEnabled(FViewportClient* ViewportClient, ESourceControlStatus Status, bool bEnabled);` (scope `SourceControlViewportUtils`) — Helper method to set the viewport feedback on or off on the viewport.
- L37 _prototype_ `uint8 GetFeedbackOpacity(FViewportClient* ViewportClient);` (scope `SourceControlViewportUtils`) — Helper method to get the opacity value.
- L40 _prototype_ `void SetFeedbackOpacity(FViewportClient* ViewportClient, uint8 Opacity);` (scope `SourceControlViewportUtils`) — Helper method to set the opacity value. Refreshes the viewport but does not persist; call SaveFeedbackSettings when the user commits.
- L43 _prototype_ `void SaveFeedbackSettings();` (scope `SourceControlViewportUtils`) — Persist current overlay settings to ini.

### `Source/Developer/SourceControlViewport/Public/RevisionControlOverlaySettings.h` (Public)


#### class `URevisionControlOverlaySettings`  
`class URevisionControlOverlaySettings : public UDeveloperSettings`  
_L13-44_
- reflection: `UCLASS(MinimalAPI, config=EditorPerProjectUserSettings, defaultconfig, meta=(DisplayName="Revision Control Overlays"))`
- inherits: `UDeveloperSettings`
- desc: User preferences for the viewport revision control overlays.
- L18 _public function_ `virtual FName GetCategoryName() const override`
- L21 _public member_ `bool bShowCheckedOutByOtherUser = true;` — `UPROPERTY(config, EditAnywhere, Category="Viewport Overlays")`
- L24 _public member_ `bool bShowNotAtHeadRevision = true;` — `UPROPERTY(config, EditAnywhere, Category="Viewport Overlays")`
- L27 _public member_ `bool bShowCheckedOut = false;` — `UPROPERTY(config, EditAnywhere, Category="Viewport Overlays")`
- L30 _public member_ `bool bShowOpenForAdd = false;` — `UPROPERTY(config, EditAnywhere, Category="Viewport Overlays")`
- L33 _public member_ `int32 OverlayAlpha = 20;` — `UPROPERTY(config, EditAnywhere, Category="Viewport Overlays", meta=(ClampMin=0, ClampMax=100, UIMin=0, UIMax=100))`
- L35 _public member_ `static FSimpleMulticastDelegate OnOverlayStatesChanged;`
- L36 _public member_ `static FSimpleMulticastDelegate OnOverlayColorsChanged;`
- L38 _public prototype_ `static void NotifyOverlayStatesChanged();`
- L39 _public prototype_ `static void NotifyOverlayColorsChanged();`
- L42 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
