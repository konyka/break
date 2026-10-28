# Plugins / CameraShakePreviewer

- module root: `Plugins/Cameras/CameraShakePreviewer/Source/CameraShakePreviewer`
- headers: 2; symbols: 74
- symbol kinds: class=3, delegate=1, function=5, member=17, namespace=1, prototype=45, struct=2
- PrivateDependencyModuleNames: AppFramework, ApplicationCore, EditorFramework, GameplayCameras, LevelEditor, MovieScene, MovieSceneTracks, PropertyEditor, Slate, SlateCore, ToolMenus, UnrealEd
- PrivateIncludePathModuleNames: WorkspaceMenuStructure
- PublicDependencyModuleNames: Core, CoreUObject, Engine, InputCore

### `Plugins/Cameras/CameraShakePreviewer/Source/CameraShakePreviewer/Private/SCameraShakePreviewer.h` (Private)


#### class `FCameraShakePreviewUpdater`  
`class FCameraShakePreviewUpdater : public FTickableEditorObject`  
_L40-61_
- inherits: `FTickableEditorObject`
- desc: Wrapper for the shake previewer that will tick it with the editor.
- L43 _public prototype_ `FCameraShakePreviewUpdater(UWorld* InWorld);`
- L44 _public prototype_ `virtual ~FCameraShakePreviewUpdater();`
- L47 _public function_ `virtual ETickableTickType GetTickableTickType() const` — FTickableObject Interface
- L48 _public function_ `virtual TStatId GetStatId() const override`
- L49 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L51 _public prototype_ `UCameraShakeBase* AddCameraShake(TSubclassOf<UCameraShakeBase> ShakeClass, const FAddCameraShakeParams& Params);`
- L52 _public prototype_ `void GetActiveCameraShakes(TArray<FActiveCameraShakeInfo>& ActiveCameraShakes) const;`
- L53 _public prototype_ `void RemoveCameraShake(UCameraShakeBase* ShakeInstance);`
- L54 _public prototype_ `void RemoveAllCameraShakesFromSource(const UCameraShakeSourceComponent* SourceComponent);`
- L55 _public prototype_ `void RemoveAllCameraShakes();`
- L57 _public function_ `FCameraShakePreviewer& GetPreviewer()`
- L60 _private member_ `FCameraShakePreviewer Previewer;`

#### class `SCameraShakePreviewer`  
`class SCameraShakePreviewer : public SCompoundWidget, public FEditorUndoClient`  
_L66-123_
- inherits: `SCompoundWidget,FEditorUndoClient`
- desc: Camera shake preview panel.
- L69 _public function_ `SLATE_BEGIN_ARGS(SCameraShakePreviewer)`
- L70 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L73 _public prototype_ `~SCameraShakePreviewer();`
- L76 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface
- L79 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient Interface
- L80 _public function_ `virtual void PostRedo(bool bSuccess) override`
- L83 _private prototype_ `void Populate();`
- L84 _private prototype_ `void Refresh();`
- L85 _private prototype_ `void UpdateActiveViewportAndWorld();`
- L87 _private prototype_ `void OnTogglePreviewCameraShakes(const FTogglePreviewCameraShakesParams& Params);`
- L89 _private prototype_ `TSharedRef<ITableRow> OnCameraShakesListGenerateRowWidget(TSharedPtr<FCameraShakeData> Entry, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L90 _private prototype_ `void OnCameraShakesListSectionChanged(TSharedPtr<FCameraShakeData> Entry, ESelectInfo::Type SelectInfo) const;`
- L91 _private prototype_ `FText GetActiveViewportName() const;`
- L92 _private prototype_ `FText GetActiveViewportWarnings() const;`
- L94 _private prototype_ `FReply OnPlayStopAllShakes();`
- L95 _private prototype_ `FReply OnPlayStopSelectedShake();`
- L96 _private prototype_ `void PlayCameraShake(TSharedPtr<FCameraShakeData> CameraShake);`
- L98 _private prototype_ `void OnLevelViewportClientListChanged();`
- L99 _private prototype_ `void OnLevelAdded(ULevel* InLevel, UWorld* InWorld);`
- L100 _private prototype_ `void OnLevelRemoved(ULevel* InLevel, UWorld* InWorld);`
- L101 _private prototype_ `void OnLevelActorsAdded(AActor* InActor);`
- L102 _private prototype_ `void OnLevelActorsRemoved(AActor* InActor);`
- L103 _private prototype_ `void OnLevelActorListChanged();`
- L104 _private prototype_ `void OnMapChange(uint32 MapFlags);`
- L105 _private prototype_ `void OnNewCurrentLevel();`
- L106 _private prototype_ `void OnMapLoaded(const FString& Filename, bool bAsTemplate);`
- L109 _private member_ `TArray<TSharedPtr<FCameraShakeData>> CameraShakes;`
- L110 _private member_ `TUniquePtr<FCameraShakePreviewUpdater> CameraShakePreviewUpdater;`
- L112 _private member_ `TSharedPtr<SListView<TSharedPtr<FCameraShakeData>>> CameraShakesListView;`
- L113 _private member_ `TSharedPtr<SButton> PlayStopSelectedButton;`
- L115 _private member_ `FCameraShakePreviewerModule* CameraShakePreviewerModule;`
- L117 _private member_ `FLevelEditorViewportClient* ActiveViewportClient;`
- L118 _private member_ `int32 ActiveViewportIndex;`
- L120 _private member_ `TWeakObjectPtr<UWorld> WeakCurrentWorld;`
- L122 _private member_ `bool bNeedsRefresh;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace ESelectInfo`

### `Plugins/Cameras/CameraShakePreviewer/Source/CameraShakePreviewer/Public/CameraShakePreviewerModule.h` (Public)


#### struct `FTogglePreviewCameraShakesParams`  
`struct FTogglePreviewCameraShakesParams`  
_L15-19_
- L17 _public member_ `FLevelEditorViewportClient* ViewportClient = nullptr;`
- L18 _public member_ `bool bPreviewCameraShakes = false;`

#### class `FCameraShakePreviewerModule`  
`class FCameraShakePreviewerModule : public IModuleInterface`  
_L26-65_
- inherits: `IModuleInterface`
- desc: Module for managing the camera shake previewer tool.
- L30 _public prototype_ `virtual void StartupModule();` — IModuleInterface interface
- L31 _public prototype_ `virtual void ShutdownModule();`
- L34 _public prototype_ `void ToggleCameraShakesPreview(FLevelEditorViewportClient* ViewportClient);` — Toggles whether the given viewport should show camera shakes.
- L36 _public prototype_ `bool HasCameraShakesPreview(FLevelEditorViewportClient* ViewportClient) const;` — Gets whether the given viewport is supporting camera shakes.
- L40 _public member_ `FOnTogglePreviewCameraShakes OnTogglePreviewCameraShakes;` — Callback for when a viewport's ability to show camera shakes is toggled.
- L43 _private prototype_ `static TSharedRef<SDockTab> CreateCameraShakePreviewerTab(const FSpawnTabArgs& Args);`
- L45 _private prototype_ `void RegisterEditorTab();`
- L46 _private prototype_ `void RegisterViewportOptionMenuExtender();`
- L48 _private prototype_ `void UnregisterEditorTab();`
- L49 _private prototype_ `void UnregisterViewportOptionMenuExtender();`
- L51 _private prototype_ `TSharedRef<FExtender> OnExtendLevelViewportOptionMenu(const TSharedRef<FUICommandList> CommandList);`
- L52 _private prototype_ `void OnLevelViewportClientListChanged();`
- L54 _private prototype_ `void CreateCameraShakeToggleOption(FMenuBuilder& InMenuBuilder);`
- L57 _private member_ `FDelegateHandle LevelEditorTabManagerChangedHandle;`
- L58 _private member_ `FDelegateHandle ViewportOptionsMenuExtenderHandle;`
- L64 _private member_ `TMap<FLevelEditorViewportClient*, FViewportInfo> ViewportInfos;`

#### struct `FCameraShakePreviewerModule::FViewportInfo`  
`struct FViewportInfo`  
_L60-63_
- L62 _public member_ `bool bPreviewCameraShakes = false;`

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTogglePreviewCameraShakes, const FTogglePreviewCameraShakesParams&);`
- L21 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTogglePreviewCameraShakes, const FTogglePreviewCameraShakesParams&);`
