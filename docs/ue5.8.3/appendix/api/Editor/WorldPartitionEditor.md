# Editor / WorldPartitionEditor

- module root: `Source/Editor/WorldPartitionEditor`
- headers: 44; symbols: 863
- symbol kinds: class=46, delegate=4, enum=2, enumerator=5, function=103, macro=11, member=232, prototype=432, struct=16, typedef=12
- DynamicallyLoadedModuleNames: AssetTools
- PrivateDependencyModuleNames: ApplicationCore, CommonMenuExtensions, ContentBrowser, ContentBrowserData, Core, CoreUObject, DataLayerEditor, DeveloperSettings, EditorFramework, EditorSubsystem, EditorWidgets, Engine, ImageCore, InputCore, Json, LevelEditor, MainFrame, PropertyEditor, RHI, RenderCore, Renderer, SceneOutliner, Slate, SlateCore, ToolMenus, UnrealEd, WorldBrowser
- PrivateIncludePathModuleNames: WorkspaceMenuStructure

### `Source/Editor/WorldPartitionEditor/Private/WorldPartition/Customizations/ExternalDataLayerUIDStructCustomization.h` (Private)


#### class `FExternalDataLayerUIDStructCustomization`  
`class FExternalDataLayerUIDStructCustomization : public IPropertyTypeCustomization`  
_L7-24_
- inherits: `IPropertyTypeCustomization`
- L16 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()` — Creates a new instance. @return A new struct customization for ExternalDataLayerUID.
- L22 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L23 _public function_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`

### `Source/Editor/WorldPartitionEditor/Private/WorldPartition/Customizations/WorldDataLayersActorDetails.h` (Private)


#### class `FWorldDataLayersActorDetails`  
`class FWorldDataLayersActorDetails : public IDetailCustomization`  
_L12-25_
- inherits: `IDetailCustomization`
- L16 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L19 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface
- L22 _private prototype_ `bool UseExternalPackageDataLayerInstancesEnabled(AWorldDataLayers* WorldDataLayers) const;`
- L23 _private prototype_ `ECheckBoxState IsUseExternalPackageDataLayerInstancesChecked(AWorldDataLayers* WorldDataLayers) const;`
- L24 _private prototype_ `void OnUseExternalPackageDataLayerInstancesChanged(ECheckBoxState BoxState, AWorldDataLayers* WorldDataLayers);`

### `Source/Editor/WorldPartitionEditor/Private/WorldPartition/Customizations/WorldPartitionDetailsCustomization.h` (Private)


#### class `FWorldPartitionDetails`  
`class FWorldPartitionDetails : public IDetailCustomization`  
_L14-37_
- inherits: `IDetailCustomization`
- L18 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L21 _protected function_ `FWorldPartitionDetails()`
- L26 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;` — IDetailCustomization interface
- L29 _private prototype_ `void HandleWorldPartitionEnableStreamingChanged(ECheckBoxState InCheckState);` — Callback for changes in the world partition enable streaming.
- L32 _private prototype_ `void HandleWorldPartitionRuntimeHashClassChanged(const UClass* InRuntimeHashClass);` — Callback for changes in the world partition runtime hash class.
- L34 _private member_ `IDetailLayoutBuilder* DetailBuilder;`
- L35 _private member_ `TWeakObjectPtr<UWorldPartition> WorldPartition;`
- L36 _private member_ `const UClass* RuntimeHashClass;`

### `Source/Editor/WorldPartitionEditor/Private/WorldPartition/Customizations/WorldPartitionEditorPerProjectUserSettingsDetails.h` (Private)


#### class `FWorldPartitionEditorPerProjectUserSettingsCustomization`  
`class FWorldPartitionEditorPerProjectUserSettingsCustomization : public IDetailCustomization`  
_L9-23_
- inherits: `IDetailCustomization`
- L13 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L16 _protected function_ `FWorldPartitionEditorPerProjectUserSettingsCustomization()`
- L18 _protected prototype_ `FReply OnClearPerWorldSettings();`
- L22 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder);` — IDetailCustomization interface

### `Source/Editor/WorldPartitionEditor/Private/WorldPartition/Customizations/WorldPartitionHLODDetailsCustomization.h` (Private)


#### class `FWorldPartitionHLODDetailsCustomization`  
`class FWorldPartitionHLODDetailsCustomization : public IDetailCustomization`  
_L12-42_
- inherits: `IDetailCustomization`
- L16 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L19 _protected function_ `FWorldPartitionHLODDetailsCustomization()`
- L24 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;` — IDetailCustomization interface
- L26 _private prototype_ `TArray<AWorldPartitionHLOD*> GetSelectedHLODActors() const;`
- L28 _private prototype_ `bool CanBuildHLOD() const;`
- L29 _private prototype_ `FReply OnBuildHLOD();`
- L30 _private prototype_ `FReply OnForceBuildHLOD();`
- L31 _private prototype_ `FReply OnBuildHLODInternal(bool bForceBuild);`
- L33 _private prototype_ `static bool CanExportHLODAssets(const AWorldPartitionHLOD* HLODActor);`
- L34 _private prototype_ `bool CanExportAssets() const;`
- L35 _private prototype_ `FReply OnExportAssets();`
- L37 _private prototype_ `bool CanCompareHLOD() const;`
- L38 _private prototype_ `FReply OnCompareHLOD();`
- L41 _private member_ `TArray<TWeakObjectPtr<UObject>> SelectedObjects;`

### `Source/Editor/WorldPartitionEditor/Private/WorldPartition/Customizations/WorldPartitionHLODLayerDetailsCustomization.h` (Private)


#### class `FWorldPartitionHLODLayerDetailsCustomization`  
`class FWorldPartitionHLODLayerDetailsCustomization : public IDetailCustomization`  
_L12-28_
- inherits: `IDetailCustomization`
- L16 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L18 _public prototype_ `~FWorldPartitionHLODLayerDetailsCustomization();`
- L22 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailLayoutBuilder) override;` — IDetailCustomization interface
- L23 _private prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& InDetailLayoutBuilder) override;`
- L24 _private prototype_ `void OnWorldPartitionChanged(UWorld* InWorld);`
- L25 _private prototype_ `void ForceRefreshLayout();`
- L27 _private member_ `TWeakPtr<IDetailLayoutBuilder> DetailLayoutBuilderWeakPtr;`

### `Source/Editor/WorldPartitionEditor/Private/WorldPartition/Customizations/WorldPartitionRuntimeHashSetDetailsCustomization.h` (Private)


#### class `FRuntimePartitionHLODSetupDetails`  
`class FRuntimePartitionHLODSetupDetails : public IPropertyTypeCustomization`  
_L12-34_
- inherits: `IPropertyTypeCustomization`
- L16 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L19 _protected function_ `FRuntimePartitionHLODSetupDetails()`
- L25 _private prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IDetailCustomization interface
- L29 _private prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L33 _private member_ `FRuntimePartitionHLODSetup* RuntimePartitionHLODSetup;`

### `Source/Editor/WorldPartitionEditor/Private/WorldPartition/Customizations/WorldPartitionRuntimeSpatialHashDetailsCustomization.h` (Private)


#### class `FWorldPartitionRuntimeSpatialHashDetails`  
`class FWorldPartitionRuntimeSpatialHashDetails : public IDetailCustomization`  
_L14-29_
- inherits: `IDetailCustomization`
- L18 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L21 _protected function_ `FWorldPartitionRuntimeSpatialHashDetails()`
- L26 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L28 _private member_ `UWorldPartitionRuntimeSpatialHash* WorldPartitionRuntimeSpatialHash;`

### `Source/Editor/WorldPartitionEditor/Private/WorldPartition/HLOD/HLODCompareCommands.h` (Private)


#### class `FHLODCompareCommands`  
`class FHLODCompareCommands : public TCommands<FHLODCompareCommands>`  
_L9-27_
- inherits: `TCommands<FHLODCompareCommands>`
- L12 _public function_ `FHLODCompareCommands() : TCommands<FHLODCompareCommands>(TEXT("HLODCompare"), NSLOCTEXT("Contexts", "HLODCompare", "HLOD Compare"), NAME_None, FAppStyle::GetAppStyleSetName())`
- L17 _public prototype_ `virtual void RegisterCommands() override;`
- L19 _public member_ `TSharedPtr<FUICommandInfo> ViewModeLit;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> ViewModeWireframe;`
- L21 _public member_ `TSharedPtr<FUICommandInfo> ViewModeBaseColor;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> ViewModeMetallic;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> ViewModeRoughness;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> ViewModeSpecular;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> ViewModeWorldNormal;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> GoToHLODDistance;`

### `Source/Editor/WorldPartitionEditor/Private/WorldPartition/HLOD/HLODCompareViewportClient.h` (Private)


#### class `FHLODCompareViewportClient`  
`class FHLODCompareViewportClient : public FEditorViewportClient`  
_L11-31_
- inherits: `FEditorViewportClient`
- L14 _public prototype_ `FHLODCompareViewportClient(FPreviewScene* InPreviewScene, const TSharedRef<SEditorViewport>& InEditorViewportWidget, TWeakPtr<SHLODCompareWindow> InCompareWindow);`
- L17 _public prototype_ `virtual void PerspectiveCameraMoved() override;` — FEditorViewportClient interface
- L18 _public prototype_ `virtual void SetViewMode(EViewModeIndex InViewModeIndex) override;`
- L19 _public prototype_ `virtual void Draw(FViewport* InViewport, FCanvas* Canvas) override;`
- L21 _public prototype_ `void SyncCameraFrom(const FHLODCompareViewportClient& Other);`
- L22 _public prototype_ `void SyncViewModeFrom(const FHLODCompareViewportClient& Other);`
- L25 _public function_ `void SetSiblingClient(TWeakPtr<FHLODCompareViewportClient> InSibling)` — Set a sibling viewport client to sync buffer visualization mode from before each draw.
- L28 _private member_ `TWeakPtr<SHLODCompareWindow> CompareWindow;`
- L29 _private member_ `TWeakPtr<FHLODCompareViewportClient> SiblingClient;`
- L30 _private member_ `bool bIsSyncing = false;`

### `Source/Editor/WorldPartitionEditor/Private/WorldPartition/HLOD/HLODEditorData.h` (Private)


#### struct `FHLODSceneNode`  
`struct FHLODSceneNode`  
_L13-26_
- desc: Represent an HLOD actor in the editor, loaded or not
- L15 _public prototype_ `void UpdateVisibility(const FVector& InCameraLocation, double InMinDrawDistance, double InMaxDrawDistance, bool bInForceHidden, bool bInForceVisibilityUpdate, int32 InLastStateUpdate);`
- L17 _public member_ `FHLODSceneNode* ParentHLOD = nullptr;`
- L18 _public member_ `TArray<FHLODSceneNode*> ChildrenHLODs;`
- L21 _public member_ `FBoxSphereBounds Bounds;`
- L22 _public member_ `bool bCachedIsVisible = true;`
- L23 _public member_ `AWorldPartitionHLOD* HLODActor = nullptr;`
- L25 _public member_ `int32 HasIntersectingLoadedRegion = INDEX_NONE;`

#### struct `FWorldPartitionHLODEditorData`  
`struct FWorldPartitionHLODEditorData`  
_L29-75_
- desc: Editor state of HLODs for a given World Partition
- L32 _public prototype_ `FWorldPartitionHLODEditorData(UWorldPartition* InWorldPartition);`
- L33 _public prototype_ `~FWorldPartitionHLODEditorData();`
- L35 _public prototype_ `bool IsLoadedActorsStateInitialized() const;`
- L36 _public prototype_ `void ClearLoadedActorsState();`
- L37 _public prototype_ `void UpdateLoadedActorsState();`
- L38 _public prototype_ `void UpdateVisibility(const FVector& InCameraLocation, double InMinDrawDistance, double InMaxDrawDistance, bool bForceVisibilityUpdate);`
- L41 _public prototype_ `bool SetHLODLoadingState(bool bInShouldBeLoaded);` — Returns true if the loading state changed.
- L43 _public prototype_ `void RegisterHLODActor(AWorldPartitionHLOD* Actor, bool bInHideActor);`
- L44 _public prototype_ `void UnregisterHLODActor(AWorldPartitionHLOD* Actor);`
- L45 _public prototype_ `void UpdateHLODActor(AWorldPartitionHLOD* Actor);`
- L48 _private prototype_ `void OnActorDescContainerInstanceRegistered(UActorDescContainerInstance* InContainerInstance);`
- L49 _private prototype_ `void OnActorDescContainerInstanceUnregistered(UActorDescContainerInstance* InContainerInstance);`
- L51 _private prototype_ `FHLODSceneNode* FindHLODActorNode(const FGuid& InActorGuid) const;`
- L52 _private prototype_ `void RemoveFromTopLevelHLODActorNodes(FHLODSceneNode* InHLODSceneNode);`
- L61 _private member_ `UWorldPartition* WorldPartition;`
- L62 _private member_ `TMap<UActorDescContainerInstance*, FContainerInstanceHLODActorData> PerContainerInstanceHLODActorDataMap;`
- L63 _private member_ `TUniquePtr<FLoaderAdapterHLOD> HLODActorsLoader;`
- L64 _private member_ `int32 LastStateUpdate;`
- L73 _private typedef_ `using FExternalDirtyActorsTracker = TExternalDirtyActorsTracker<FExternalDirtyActorTrackerGuid>;`
- L74 _private member_ `TUniquePtr<FExternalDirtyActorsTracker> ExternalDirtyActorsTracker;`

#### struct `FWorldPartitionHLODEditorData::FContainerInstanceHLODActorData`  
`struct FContainerInstanceHLODActorData`  
_L55-59_
- L57 _public member_ `TMap<FGuid, TUniquePtr<FHLODSceneNode>> HLODActorNodes;`
- L58 _public member_ `TArray<FHLODSceneNode*> TopLevelHLODActorNodes;`

#### struct `FWorldPartitionHLODEditorData::FExternalDirtyActorTrackerGuid`  
`struct FExternalDirtyActorTrackerGuid`  
_L66-71_
- L68 _public typedef_ `using Type = FGuid;`
- L69 _public typedef_ `using OwnerType = FWorldPartitionHLODEditorData;`
- L70 _public function_ `static FGuid Store(FWorldPartitionHLODEditorData* InOwner, AActor* InActor)`

### `Source/Editor/WorldPartitionEditor/Private/WorldPartition/HLOD/SHLODClipWrapper.h` (Private)


#### class `SHLODClipWrapper`  
`class SHLODClipWrapper : public SCompoundWidget`  
_L13-54_
- inherits: `SCompoundWidget`
- desc: A simple compound widget that clips its single child to show only the portion right of a dynamic wipe position. Used for the HLOD compare wipe overlay.
- L16 _public function_ `SLATE_BEGIN_ARGS(SHLODClipWrapper) : _WipePosition(0.5f)`
- L19 _public function_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_ATTRIBUTE(float, WipePosition) SLATE_END_ARGS() void Construct(const FArguments& InArgs)`
- L35 _public function_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override`
- L53 _private member_ `TAttribute<float> WipePosition;`

### `Source/Editor/WorldPartitionEditor/Private/WorldPartition/HLOD/SHLODCompareViewport.h` (Private)


#### class `SHLODCompareViewport`  
`class SHLODCompareViewport : public SEditorViewport`  
_L11-39_
- inherits: `SEditorViewport`
- L14 _public function_ `SLATE_BEGIN_ARGS(SHLODCompareViewport)`
- L15 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FPreviewScene>, PreviewScene) SLATE_ARGUMENT(TWeakPtr<SHLODCompareWindow>, CompareWindow) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L21 _public function_ `TSharedPtr<FHLODCompareViewportClient> GetCompareViewportClient() const`
- L24 _public prototype_ `TSharedRef<SWidget> BuildExternalViewModeToolbar(const TSharedPtr<FUICommandList>& InCommandList);` — Build a standalone view mode toolbar widget for this viewport (used by SHLODCompareWindow).
- L27 _public function_ `void SetPriorityCommandList(const TSharedPtr<FUICommandList>& InCommandList)` — Set the priority command list that is checked before the viewport's own commands.
- L30 _protected prototype_ `virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;`
- L31 _protected function_ `virtual TSharedPtr<SWidget> BuildViewportToolbar() override`
- L32 _protected prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L35 _private member_ `TSharedPtr<FPreviewScene> PreviewScene;`
- L36 _private member_ `TWeakPtr<SHLODCompareWindow> CompareWindow;`
- L37 _private member_ `TSharedPtr<FHLODCompareViewportClient> CompareViewportClient;`
- L38 _private member_ `TSharedPtr<FUICommandList> PriorityCommandList;`

### `Source/Editor/WorldPartitionEditor/Private/WorldPartition/HLOD/SHLODCompareWindow.h` (Private)


#### class `SHLODCompareWindow`  
`class SHLODCompareWindow : public SCompoundWidget`  
_L20-77_
- inherits: `SCompoundWidget`
- L23 _public function_ `SLATE_BEGIN_ARGS(SHLODCompareWindow)`
- L24 _public prototype_ `SLATE_ARGUMENT(TArray<TWeakObjectPtr<AWorldPartitionHLOD>>, HLODActors) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L28 _public prototype_ `~SHLODCompareWindow();`
- L30 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L31 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L33 _public prototype_ `void OnCameraMoved(FHLODCompareViewportClient* Source);`
- L34 _public prototype_ `void OnViewModeChanged(FHLODCompareViewportClient* Source);`
- L37 _private prototype_ `void BindCommands();`
- L38 _private prototype_ `void SetCompareViewMode(EViewModeIndex ViewMode, FName BufferVizMode = NAME_None);`
- L39 _private prototype_ `bool PopulateSourceScene();`
- L40 _private prototype_ `bool PopulateHLODScene();`
- L41 _private prototype_ `void FocusCamerasOnContent();`
- L42 _private prototype_ `void CopyWorldLighting();`
- L43 _private prototype_ `void OnWipePositionChanged(float NewPosition);`
- L44 _private prototype_ `FReply OnGoToMinVisibleDistance();`
- L45 _private prototype_ `void RequestCloseWindow();`
- L46 _private prototype_ `void OnMapChanged(UWorld* World, EMapChangeType ChangeType);`
- L47 _private prototype_ `void OnEditorPreExit();`
- L49 _private member_ `TArray<TWeakObjectPtr<AWorldPartitionHLOD>> HLODActors;`
- L51 _private member_ `TSharedPtr<FPreviewScene> SourcePreviewScene;`
- L52 _private member_ `TSharedPtr<FPreviewScene> HLODPreviewScene;`
- L54 _private member_ `TSharedPtr<SHLODCompareViewport> SourceViewport;`
- L55 _private member_ `TSharedPtr<SHLODCompareViewport> HLODViewport;`
- L57 _private member_ `TArray<UActorComponent*> SourceSceneComponents;`
- L58 _private member_ `TArray<UActorComponent*> HLODSceneComponents;`
- L60 _private prototype_ `float GetCameraDistanceToBounds() const;`
- L61 _private prototype_ `float GetSourceMinDrawDistance() const;`
- L62 _private prototype_ `float GetHLODMinVisibleDistance() const;`
- L63 _private prototype_ `FString GetSourceZoneLabel() const;`
- L64 _private prototype_ `FString GetHLODZoneLabel() const;`
- L66 _private member_ `TSharedPtr<STextBlock> StatusText;`
- L68 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L71 _private member_ `float WipePosition = 0.5f;` — Wipe overlay
- L72 _private member_ `TSharedPtr<SHLODClipWrapper> ClipWrapper;`
- L73 _private member_ `TSharedPtr<SBox> ViewModeToolbarContainer;`
- L75 _private member_ `FDelegateHandle OnMapChangedHandle;`
- L76 _private member_ `FDelegateHandle OnEditorPreExitHandle;`

### `Source/Editor/WorldPartitionEditor/Private/WorldPartition/HLOD/SHLODDistanceRuler.h` (Private)


#### class `SHLODDistanceRuler`  
`class SHLODDistanceRuler : public SLeafWidget`  
_L15-44_
- inherits: `SLeafWidget`
- desc: A horizontal ruler showing camera distance relative to source actors and HLOD transition. Layout: |--- Source visible ---|- gap -|--- HLOD visible ---| 0    SourceMinDraw     ^       HLODMinVisible       far "Actors"          camera  "HLOD1 (128.0m)"
- L18 _public function_ `SLATE_BEGIN_ARGS(SHLODDistanceRuler) : _SourceMinDrawDistance(0.0f) , _HLODMinVisibleDistance(0.0f) , _CameraDistance(0.0f)`
- L23 _public prototype_ `SLATE_ATTRIBUTE(float, SourceMinDrawDistance) SLATE_ATTRIBUTE(float, HLODMinVisibleDistance) SLATE_ATTRIBUTE(float, CameraDistance) SLATE_ATTRIBUTE(FString, SourceZoneLabel) SLATE_ATTRIBUTE(FString, HLODZoneLabel) SLATE_ATTRIBUTE(float, WorldToMeters) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L34 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;` — SWidget interface
- L35 _public prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L38 _private member_ `TAttribute<float> SourceMinDrawDistance;`
- L39 _private member_ `TAttribute<float> HLODMinVisibleDistance;`
- L40 _private member_ `TAttribute<float> CameraDistance;`
- L41 _private member_ `TAttribute<FString> SourceZoneLabel;`
- L42 _private member_ `TAttribute<FString> HLODZoneLabel;`
- L43 _private member_ `TAttribute<float> WorldToMeters;`

### `Source/Editor/WorldPartitionEditor/Private/WorldPartition/HLOD/SHLODWipeHandle.h` (Private)


#### class `SHLODWipeHandle`  
`class SHLODWipeHandle : public SLeafWidget`  
_L13-33_
- inherits: `SLeafWidget`
- desc: A draggable vertical wipe handle for the HLOD compare overlay. Draws a thin vertical line and handles mouse drag to update wipe position.
- L16 _public function_ `SLATE_BEGIN_ARGS(SHLODWipeHandle)`
- L17 _public prototype_ `SLATE_EVENT(FOnWipePositionChanged, OnWipePositionChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L23 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;` — SWidget interface
- L24 _public prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L25 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L26 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L27 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L28 _public prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L31 _private member_ `FOnWipePositionChanged OnWipePositionChanged;`
- L32 _private member_ `bool bDragging = false;`

#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_DELEGATE_OneParam(FOnWipePositionChanged, float);`
- L7 _prototype_ `DECLARE_DELEGATE_OneParam(FOnWipePositionChanged, float);`

### `Source/Editor/WorldPartitionEditor/Private/WorldPartition/HLOD/SWorldPartitionBuildHLODsDialog.h` (Private)


#### class `SWorldPartitionBuildHLODsDialog`  
`class SWorldPartitionBuildHLODsDialog : public SCompoundWidget`  
_L16-55_
- inherits: `SCompoundWidget`
- L26 _public function_ `SLATE_BEGIN_ARGS(SWorldPartitionBuildHLODsDialog)`
- L28 _public prototype_ `SLATE_ATTRIBUTE(TSharedPtr<SWindow>, ParentWindow) SLATE_END_ARGS() ~SWorldPartitionBuildHLODsDialog() = default;` — A pointer to the parent window
- L39 _public prototype_ `void Construct(const FArguments& InArgs);` — Construct this widget.  Called by the SNew() Slate macro. @param	InArgs				Declaration used by the SNew() macro to construct this widget @param	InViewModel			The UI logic not specific to slate
- L41 _public member_ `static const FVector2D DEFAULT_WINDOW_SIZE;`
- L43 _public function_ `DialogResult GetDialogResult() const`
- L46 _private prototype_ `FReply OnBuildClicked();`
- L47 _private prototype_ `FReply OnDeleteClicked();`
- L48 _private prototype_ `FReply OnCancelClicked();`
- L51 _private member_ `TWeakPtr<SWindow> ParentWindowPtr;` — Pointer to the parent window, so we know to destroy it when done
- L54 _private member_ `DialogResult Result;` — Dialog Result

#### enum `SWorldPartitionBuildHLODsDialog::DialogResult`  
`enum DialogResult`  
_L19-24_
- L21 _public enumerator_ `BuildHLODs`
- L22 _public enumerator_ `DeleteHLODs`
- L23 _public enumerator_ `Cancel`

### `Source/Editor/WorldPartitionEditor/Private/WorldPartition/SWorldPartitionConvertDialog.h` (Private)


#### class `SWorldPartitionConvertDialog`  
`class SWorldPartitionConvertDialog : public SCompoundWidget`  
_L18-57_
- inherits: `SCompoundWidget`
- L22 _public function_ `SLATE_BEGIN_ARGS(SWorldPartitionConvertDialog)`
- L24 _public prototype_ `SLATE_ATTRIBUTE(TSharedPtr<SWindow>, ParentWindow) SLATE_ATTRIBUTE(UWorldPartitionConvertOptions*, ConvertOptions) SLATE_END_ARGS() ~SWorldPartitionConvertDialog() = default;` — A pointer to the parent window
- L36 _public prototype_ `void Construct(const FArguments& InArgs);` — Construct this widget.  Called by the SNew() Slate macro. @param	InArgs				Declaration used by the SNew() macro to construct this widget @param	InViewModel			The UI logic not specific to slate
- L38 _public member_ `static const FVector2D DEFAULT_WINDOW_SIZE;`
- L40 _public function_ `bool ClickedOk() const`
- L43 _private prototype_ `FReply OnOkClicked();`
- L44 _private prototype_ `bool IsOkEnabled() const;`
- L46 _private prototype_ `FReply OnCancelClicked();`
- L49 _private member_ `TWeakPtr<SWindow> ParentWindowPtr;` — Pointer to the parent window, so we know to destroy it when done
- L50 _private member_ `TWeakObjectPtr<UWorldPartitionConvertOptions> ConvertOptions;`
- L53 _private member_ `TSharedPtr<class IDetailsView> DetailsView;` — Detailsview used to display SettingsObjects, and allowing user to change options
- L56 _private member_ `bool bClickedOk;` — Dialog Result

### `Source/Editor/WorldPartitionEditor/Public/WorldPartition/ContentBundle/ContentBundleEditorSubsystem.h` (Public)


#### class `UContentBundleEditorSubsystemModule`  
`class UContentBundleEditorSubsystemModule : public UObject`  
_L20-42_
- reflection: `UCLASS(Within = ContentBundleEditorSubsystem)`
- inherits: `UObject`
- L26 _public function_ `virtual void BeginDestroy() override`
- L29 _public function_ `void Initialize()`
- L30 _public function_ `void Deinitialize()`
- L32 _public function_ `bool IsInitialize() const`
- L34 _public function_ `UContentBundleEditorSubsystem* GetSubsystem() const`
- L37 _protected function_ `virtual void DoInitialize()`
- L38 _protected function_ `virtual void DoDenitialize()`
- L41 _private member_ `bool bIsInitialized = false;`

#### class `UActorEditorContextContentBundleState`  
`class UActorEditorContextContentBundleState : public UActorEditorContextClientState`  
_L45-52_
- reflection: `UCLASS()`
- inherits: `UActorEditorContextClientState`
- L51 _public member_ `FGuid ContentBundleGuid;` — `UPROPERTY(VisibleAnywhere, Category = "Content Bundle")`

#### class `UContentBundleEditingSubmodule`  
`class UContentBundleEditingSubmodule : public UContentBundleEditorSubsystemModule, public IActorEditorContextClient`  
_L55-105_
- reflection: `UCLASS()`
- inherits: `UContentBundleEditorSubsystemModule,IActorEditorContextClient`
- L63 _public prototype_ `virtual void OnExecuteActorEditorContextAction(UWorld* InWorld, const EActorEditorContextAction& InType, AActor* InActor = nullptr) override;`
- L64 _public prototype_ `virtual void CaptureActorEditorContextState(UWorld* InWorld, UActorEditorContextStateCollection* InStateCollection) const override;`
- L65 _public prototype_ `virtual void RestoreActorEditorContextState(UWorld* InWorld, const UActorEditorContextStateCollection* InStateCollection) override;`
- L66 _public prototype_ `virtual bool GetActorEditorContextDisplayInfo(UWorld* InWorld, FActorEditorContextClientDisplayInfo& OutDiplayInfo) const override;`
- L67 _public function_ `virtual bool CanResetContext(UWorld* InWorld) const override`
- L68 _public prototype_ `virtual TSharedRef<SWidget> GetActorEditorContextWidget(UWorld* InWorld) const override;`
- L69 _public function_ `virtual FOnActorEditorContextClientChanged& GetOnActorEditorContextClientChanged() override`
- L72 _public prototype_ `bool ActivateContentBundleEditing(TSharedPtr<FContentBundleEditor>& ContentBundleEditor);`
- L73 _public prototype_ `bool DeactivateContentBundleEditing(TSharedPtr<FContentBundleEditor>& ContentBundleEditor);`
- L74 _public prototype_ `bool DeactivateCurrentContentBundleEditing();`
- L75 _public prototype_ `bool IsEditingContentBundle() const;`
- L76 _public prototype_ `bool IsEditingContentBundle(const TSharedPtr<FContentBundleEditor>& ContentBundleEditor) const;`
- L77 _public prototype_ `bool IsEditingContentBundle(const FGuid& ContentBundleGuid) const;`
- L78 _public prototype_ `TSharedPtr<FContentBundleEditor> GetEditorContentBundle(const FGuid& ContentBundleGuid) const;`
- L82 _protected prototype_ `virtual void DoInitialize() override;`
- L83 _protected prototype_ `virtual void DoDenitialize() override;`
- L87 _private prototype_ `void PushContentBundleEditing(bool bDuplicateContext);`
- L88 _private prototype_ `void PopContentBundleEditing();`
- L89 _private prototype_ `void StartEditing(TSharedPtr<FContentBundleEditor>& ContentBundleEditor);`
- L90 _private prototype_ `void StopEditing(TSharedPtr<FContentBundleEditor>& ContentBundleEditor);`
- L91 _private prototype_ `void ApplyContext(AActor* InActor);`
- L92 _private prototype_ `virtual void PreEditUndo() override;`
- L93 _private prototype_ `virtual void PostEditUndo() override;`
- L96 _private member_ `TArray<FGuid> EditingContentBundlesStack;` — `UPROPERTY()`
- L99 _private member_ `FGuid EditingContentBundleGuid;` — `UPROPERTY()`
- L102 _private member_ `FGuid PreUndoRedoEditingContentBundleGuid;` — Used for undo/redo
- L104 _private member_ `FOnActorEditorContextClientChanged ActorEditorContextClientChanged;`

#### class `UContentBundleEditorSubsystem`  
`class UContentBundleEditorSubsystem : public UEditorSubsystem, public IContentBundleEditorSubsystemInterface`  
_L108-165_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem,IContentBundleEditorSubsystemInterface`
- L113 _public function_ `static UContentBundleEditorSubsystem* Get()`
- L115 _public function_ `UContentBundleEditorSubsystem()`
- L118 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L119 _public prototype_ `virtual void Deinitialize() override;`
- L123 _public function_ `virtual void NotifyContentBundleAdded(const FContentBundleEditor* ContentBundle) override`
- L124 _public function_ `virtual void NotifyContentBundleRemoved(const FContentBundleEditor* ContentBundle) override`
- L125 _public prototype_ `virtual void NotifyContentBundleInjectedContent(const FContentBundleEditor* ContentBundle) override;`
- L126 _public prototype_ `virtual void NotifyContentBundleRemovedContent(const FContentBundleEditor* ContentBundle) override;`
- L127 _public function_ `virtual void NotifyContentBundleChanged(const FContentBundleEditor* ContentBundle) override`
- L130 _public prototype_ `UWorld* GetWorld() const;`
- L132 _public function_ `UContentBundleEditingSubmodule* GetEditingSubmodule()`
- L134 _public prototype_ `TSharedPtr<FContentBundleEditor> GetEditorContentBundleForActor(const AActor* Actor);`
- L136 _public prototype_ `TArray<TSharedPtr<FContentBundleEditor>> GetEditorContentBundles();`
- L137 _public prototype_ `TSharedPtr<FContentBundleEditor> GetEditorContentBundle(const UContentBundleDescriptor* ContentBundleDescriptor) const;`
- L138 _public prototype_ `TSharedPtr<FContentBundleEditor> GetEditorContentBundle(const FGuid& ContentBundleGuid) const override;`
- L140 _public prototype_ `void SelectActors(FContentBundleEditor& EditorContentBundle);`
- L141 _public prototype_ `void DeselectActors(FContentBundleEditor& EditorContentBundle);`
- L143 _public prototype_ `void ReferenceAllActors(FContentBundleEditor& EditorContentBundle);`
- L144 _public prototype_ `void UnreferenceAllActors(FContentBundleEditor& EditorContentBundle);`
- L146 _public prototype_ `bool IsEditingContentBundle() const override;`
- L147 _public prototype_ `bool IsEditingContentBundle(const FGuid& ContentBundleGuid) const;`
- L148 _public prototype_ `bool ActivateContentBundleEditing(TSharedPtr<FContentBundleEditor>& ContentBundleEditor) const override;`
- L149 _public prototype_ `bool DeactivateContentBundleEditing(TSharedPtr<FContentBundleEditor>& ContentBundleEditor) const override;`
- L150 _public prototype_ `virtual bool DeactivateCurrentContentBundleEditing() const override;`
- L151 _public prototype_ `bool IsContentBundleEditingActivated(TSharedPtr<FContentBundleEditor>& ContentBundleEditor) const;`
- L153 _public prototype_ `virtual void PushContentBundleEditing(bool bDuplicateContext) override;`
- L154 _public prototype_ `virtual void PopContentBundleEditing() override;`
- L158 _private member_ `FDelegateHandle LevelExternalActorsPathsProviderDelegateHandle;`
- L159 _private prototype_ `void OnGetLevelExternalActorsPaths(const FString& InLevelPackageName, const FString& InPackageShortName, TArray<FString>& OutExternalActorsPaths);`
- L161 _private prototype_ `void SelectActorsInternal(FContentBundleEditor& EditorContentBundle, bool bSelect);`
- L164 _private member_ `TObjectPtr<UContentBundleEditingSubmodule> ContentBundleEditingSubModule;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API WORLDPARTITIONEDITOR_API`

### `Source/Editor/WorldPartitionEditor/Public/WorldPartition/ContentBundle/Outliner/ContentBundleActorCountColumn.h` (Public)


#### class `FContentBundleOutlinerActorCountColumn`  
`template<typename ItemType> class STableRow;`  
_L13-31_
- inherits: `ISceneOutlinerColumn`
- L16 _public function_ `FContentBundleOutlinerActorCountColumn(ISceneOutliner& SceneOutliner) : WeakSceneOutliner(StaticCastSharedRef<ISceneOutliner>(SceneOutliner.AsShared()))`
- L17 _public prototype_ `virtual ~FContentBundleOutlinerActorCountColumn() = default;`
- L18 _public prototype_ `static FName GetID();`
- L22 _public function_ `virtual FName GetColumnID() override`
- L23 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L24 _public prototype_ `virtual const TSharedRef<SWidget> ConstructRowWidget(FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row) override;`
- L25 _public function_ `virtual bool SupportsSorting() const override`
- L30 _private member_ `TWeakPtr<ISceneOutliner> WeakSceneOutliner;`

### `Source/Editor/WorldPartitionEditor/Public/WorldPartition/ContentBundle/Outliner/ContentBundleClientColumn.h` (Public)


#### class `FContentBundleOutlinerClientColumn`  
`template<typename ItemType> class STableRow;`  
_L15-36_
- inherits: `ISceneOutlinerColumn`
- L18 _public function_ `FContentBundleOutlinerClientColumn(ISceneOutliner& SceneOutliner) : WeakSceneOutliner(StaticCastSharedRef<ISceneOutliner>(SceneOutliner.AsShared()))`
- L19 _public prototype_ `virtual ~FContentBundleOutlinerClientColumn() = default;`
- L20 _public prototype_ `static FName GetID();`
- L24 _public function_ `virtual FName GetColumnID() override`
- L25 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L26 _public prototype_ `virtual const TSharedRef<SWidget> ConstructRowWidget(FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row) override;`
- L27 _public function_ `virtual bool SupportsSorting() const override`
- L28 _public prototype_ `virtual void SortItems(TArray<FSceneOutlinerTreeItemPtr>& OutItems, const EColumnSortMode::Type SortMode) const override;`
- L33 _private prototype_ `FText GetClientDisplayName(const TWeakPtr<FContentBundleEditor>& ContentBundleEditor) const;`
- L35 _private member_ `TWeakPtr<ISceneOutliner> WeakSceneOutliner;`

### `Source/Editor/WorldPartitionEditor/Public/WorldPartition/ContentBundle/Outliner/ContentBundleEditingColumn.h` (Public)


#### class `FContentBundleOutlinerEditingColumn`  
`template<typename ItemType> class STableRow;`  
_L13-31_
- inherits: `ISceneOutlinerColumn`
- L16 _public function_ `FContentBundleOutlinerEditingColumn(ISceneOutliner& SceneOutliner) : WeakSceneOutliner(StaticCastSharedRef<ISceneOutliner>(SceneOutliner.AsShared()))`
- L17 _public prototype_ `virtual ~FContentBundleOutlinerEditingColumn() = default;`
- L18 _public prototype_ `static FName GetID();`
- L22 _public function_ `virtual FName GetColumnID() override`
- L23 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L24 _public prototype_ `virtual const TSharedRef<SWidget> ConstructRowWidget(FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row) override;`
- L25 _public function_ `virtual bool SupportsSorting() const override`
- L30 _private member_ `TWeakPtr<ISceneOutliner> WeakSceneOutliner;`

### `Source/Editor/WorldPartitionEditor/Public/WorldPartition/ContentBundle/Outliner/ContentBundleHierarchy.h` (Public)


#### class `FContentBundleHiearchy`  
`class FContentBundleHiearchy : public ISceneOutlinerHierarchy`  
_L11-30_
- inherits: `ISceneOutlinerHierarchy`
- L14 _public prototype_ `static TUniquePtr<FContentBundleHiearchy> Create(FContentBundleMode* Mode);`
- L16 _public prototype_ `virtual ~FContentBundleHiearchy();`
- L19 _public prototype_ `virtual void CreateItems(TArray<FSceneOutlinerTreeItemPtr>& OutItems) const override;`
- L20 _public prototype_ `virtual void CreateChildren(const FSceneOutlinerTreeItemPtr& Item, TArray<FSceneOutlinerTreeItemPtr>& OutChildren) const override;`
- L21 _public prototype_ `virtual FSceneOutlinerTreeItemPtr FindOrCreateParentItem(const ISceneOutlinerTreeItem& Item, const TMap<FSceneOutlinerTreeItemID, FSceneOutlinerTreeItemPtr>& Items, bool bCreate = false) override;`
- L25 _private prototype_ `void OnContentBundleChanged(const FContentBundleEditor* ContentBundle);`
- L26 _private prototype_ `void OnContentBundleAdded(const FContentBundleEditor* ContentBundle);`
- L27 _private prototype_ `void OnContentBundleRemoved(const FContentBundleEditor* ContentBundle);`
- L29 _private prototype_ `FContentBundleHiearchy(FContentBundleMode* Mode);`

### `Source/Editor/WorldPartitionEditor/Public/WorldPartition/ContentBundle/Outliner/ContentBundleMode.h` (Public)


#### struct `FContentBundleModeCreationParams`  
`struct FContentBundleModeCreationParams`  
_L12-19_
- L14 _public function_ `FContentBundleModeCreationParams(SSceneOutliner* InSceneOutliner) :SceneOutliner(InSceneOutliner)`
- L18 _public member_ `SSceneOutliner* SceneOutliner;`

#### class `FContentBundleMode`  
`class FContentBundleMode : public ISceneOutlinerMode`  
_L22-59_
- inherits: `ISceneOutlinerMode`
- L25 _public prototype_ `FContentBundleMode(const FContentBundleModeCreationParams& Params);`
- L26 _public prototype_ `~FContentBundleMode();`
- L29 _public prototype_ `virtual void Rebuild() override;`
- L30 _public prototype_ `virtual TSharedPtr<SWidget> CreateContextMenu() override;`
- L32 _public prototype_ `virtual void OnItemDoubleClick(FSceneOutlinerTreeItemPtr Item) override;`
- L33 _public prototype_ `virtual FReply OnKeyDown(const FKeyEvent& InKeyEvent) override;`
- L36 _public prototype_ `UWorld* GetEditingWorld() const;`
- L40 _protected prototype_ `virtual TUniquePtr<ISceneOutlinerHierarchy> CreateHierarchy() override;`
- L43 _protected prototype_ `TWeakPtr<FContentBundleEditor> GetSelectedContentBundle(SSceneOutliner* InSceneOutliner) const;`
- L44 _protected prototype_ `TSharedPtr<FContentBundleEditor> GetSelectedContentBundlePin(SSceneOutliner* InSceneOutliner) const;`
- L45 _protected prototype_ `void ToggleContentBundleActivation(const TWeakPtr<FContentBundleEditor>& ContentBundle);`
- L47 _protected prototype_ `void RegisterContextMenu();`
- L48 _protected prototype_ `void UnregisterContextMenu();`
- L53 _private prototype_ `void FindInContentBrowser();` — Delegate to handle "Find in Content Browser" context menu option
- L56 _private prototype_ `bool CanFindInContentBrowser() const;` — Delegate to handle enabling the "Find in Content Browser" context menu option
- L58 _private member_ `TSharedPtr<FUICommandList> Commands;`

### `Source/Editor/WorldPartitionEditor/Public/WorldPartition/ContentBundle/Outliner/ContentBundleStatusColumn.h` (Public)


#### class `FContentBundleOutlinerStatusColumn`  
`template<typename ItemType> class STableRow;`  
_L13-31_
- inherits: `ISceneOutlinerColumn`
- L16 _public function_ `FContentBundleOutlinerStatusColumn(ISceneOutliner& SceneOutliner) : WeakSceneOutliner(StaticCastSharedRef<ISceneOutliner>(SceneOutliner.AsShared()))`
- L17 _public prototype_ `virtual ~FContentBundleOutlinerStatusColumn() = default;`
- L18 _public prototype_ `static FName GetID();`
- L22 _public function_ `virtual FName GetColumnID() override`
- L23 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L24 _public prototype_ `virtual const TSharedRef<SWidget> ConstructRowWidget(FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row) override;`
- L25 _public function_ `virtual bool SupportsSorting() const override`
- L30 _private member_ `TWeakPtr<ISceneOutliner> WeakSceneOutliner;`

### `Source/Editor/WorldPartitionEditor/Public/WorldPartition/ContentBundle/Outliner/ContentBundleTreeItem.h` (Public)


#### struct `FContentBundleTreeItem`  
`struct FContentBundleTreeItem : ISceneOutlinerTreeItem`  
_L13-62_
- inherits: `ISceneOutlinerTreeItem`
- L29 _public prototype_ `FContentBundleTreeItem(const FInitializationValues& InitializationValues);`
- L30 _public function_ `TWeakPtr<FContentBundleEditor> GetContentBundleEditor() const`
- L31 _public function_ `TSharedPtr<FContentBundleEditor> GetContentBundleEditorPin() const`
- L34 _public prototype_ `virtual bool IsValid() const override;` — Begin ISceneOutlinerTreeItem Implementation
- L35 _public prototype_ `virtual FSceneOutlinerTreeItemID GetID() const override;`
- L36 _public prototype_ `virtual FString GetDisplayString() const override;`
- L37 _public prototype_ `virtual bool CanInteract() const override;`
- L38 _public prototype_ `virtual TSharedRef<SWidget> GenerateLabelWidget(ISceneOutliner& Outliner, const STableRow<FSceneOutlinerTreeItemPtr>& InRow) override;`
- L41 _public member_ `static const FSceneOutlinerTreeItemType Type;`
- L43 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FFilterPredicate, const FContentBundleEditor*);`
- L44 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FInteractivePredicate, const FContentBundleEditor*);`
- L46 _public function_ `bool Filter(FFilterPredicate Pred) const`
- L51 _public function_ `bool GetInteractiveState(FInteractivePredicate Pred) const`
- L56 _public prototype_ `FSlateColor GetItemColor() const;`
- L59 _private member_ `TWeakPtr<FContentBundleEditor> ContentBundleEditor;`
- L61 _private member_ `const FContentBundleMode& Mode;`

#### struct `FContentBundleTreeItem::FInitializationValues`  
`struct FInitializationValues`  
_L16-27_
- L18 _public function_ `FInitializationValues(const TWeakPtr<FContentBundleEditor>& InContentBundleEditor, const FContentBundleMode& InMode) :ContentBundleEditor(InContentBundleEditor), Mode(InMode)`
- L25 _public member_ `const TWeakPtr<FContentBundleEditor> ContentBundleEditor;`
- L26 _public member_ `const FContentBundleMode& Mode;`

#### Free symbols / members of external scopes

- L43 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FFilterPredicate, const FContentBundleEditor*);`
- L44 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FInteractivePredicate, const FContentBundleEditor*);`

### `Source/Editor/WorldPartitionEditor/Public/WorldPartition/ContentBundle/Outliner/SContentBundleOutliner.h` (Public)


#### class `SContentBundleOutliner`  
`class SContentBundleOutliner : public SSceneOutliner`  
_L10-22_
- inherits: `SSceneOutliner`
- L13 _public function_ `void Construct(const FArguments& InArgs, const FSceneOutlinerInitializationOptions& InitOptions)`
- L18 _public function_ `SContentBundleOutliner()`
- L19 _public prototype_ `virtual ~SContentBundleOutliner() = default;`
- L21 _public prototype_ `void SelectContentBundle(const TWeakPtr<FContentBundleEditor>& ContentBundle);`

### `Source/Editor/WorldPartitionEditor/Public/WorldPartition/ContentBundle/SContentBundleBrowser.h` (Public)


#### class `SContentBundleBrowser`  
`class SContentBundleBrowser : public SCompoundWidget`  
_L11-25_
- inherits: `SCompoundWidget`
- L15 _public function_ `SLATE_BEGIN_ARGS(SContentBundleBrowser)`
- L16 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L20 _public prototype_ `void SelectContentBundle(const TWeakPtr<FContentBundleEditor>& ContentBundle);`
- L23 _private member_ `TSharedPtr<SContentBundleOutliner> ContentBundleOutliner;`
- L24 _private member_ `TSharedPtr<SVerticalBox> ContentAreaBox;`

### `Source/Editor/WorldPartitionEditor/Public/WorldPartition/Filter/WorldPartitionActorFilterColumn.h` (Public)


#### class `FWorldPartitionActorFilterColumn`  
`template<typename ItemType> class STableRow;`  
_L12-31_
- inherits: `ISceneOutlinerColumn`
- L15 _public function_ `FWorldPartitionActorFilterColumn(ISceneOutliner& SceneOutliner) : WeakSceneOutliner(StaticCastSharedRef<ISceneOutliner>(SceneOutliner.AsShared()))`
- L16 _public prototype_ `virtual ~FWorldPartitionActorFilterColumn() = default;`
- L17 _public prototype_ `static FName GetID();`
- L21 _public function_ `virtual FName GetColumnID() override`
- L22 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L23 _public prototype_ `virtual const TSharedRef<SWidget> ConstructRowWidget(FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row) override;`
- L24 _public function_ `virtual bool SupportsSorting() const override`
- L28 _public member_ `static FName ID;`
- L30 _private member_ `TWeakPtr<ISceneOutliner> WeakSceneOutliner;`

### `Source/Editor/WorldPartitionEditor/Public/WorldPartition/Filter/WorldPartitionActorFilterHierarchy.h` (Public)


#### class `FWorldPartitionActorFilterHierarchy`  
`class FWorldPartitionActorFilterHierarchy : public ISceneOutlinerHierarchy`  
_L10-26_
- inherits: `ISceneOutlinerHierarchy`
- L13 _public prototype_ `static TUniquePtr<FWorldPartitionActorFilterHierarchy> Create(FWorldPartitionActorFilterMode* Mode);`
- L15 _public prototype_ `virtual ~FWorldPartitionActorFilterHierarchy();`
- L18 _public prototype_ `virtual void CreateItems(TArray<FSceneOutlinerTreeItemPtr>& OutItems) const override;`
- L19 _public prototype_ `virtual void CreateChildren(const FSceneOutlinerTreeItemPtr& Item, TArray<FSceneOutlinerTreeItemPtr>& OutItems) const override;`
- L20 _public prototype_ `virtual FSceneOutlinerTreeItemPtr FindOrCreateParentItem(const ISceneOutlinerTreeItem& Item, const TMap<FSceneOutlinerTreeItemID, FSceneOutlinerTreeItemPtr>& Items, bool bCreate = false) override;`
- L24 _private prototype_ `virtual void CreateChildren(const FSceneOutlinerTreeItemPtr& Item, TArray<FSceneOutlinerTreeItemPtr>& OutItems, bool bRecursive) const;`
- L25 _private prototype_ `FWorldPartitionActorFilterHierarchy(FWorldPartitionActorFilterMode* Mode);`

### `Source/Editor/WorldPartitionEditor/Public/WorldPartition/Filter/WorldPartitionActorFilterMode.h` (Public)


#### class `FWorldPartitionActorFilterMode`  
`class FWorldPartitionActorFilterMode : public ISceneOutlinerMode`  
_L15-75_
- inherits: `ISceneOutlinerMode`
- L49 _public prototype_ `FWorldPartitionActorFilterMode(SSceneOutliner* InSceneOutliner, TSharedPtr<FFilter> InFilter);`
- L52 _public prototype_ `virtual void Rebuild() override;`
- L53 _public prototype_ `virtual int32 GetTypeSortPriority(const ISceneOutlinerTreeItem& Item) const override;`
- L56 _public prototype_ `void Apply(FWorldPartitionActorFilter& InOutResult) const;`
- L58 _public function_ `FFilter::FDataLayerFilters& FindChecked(const FWorldPartitionActorFilter* InFilter) const`
- L63 _public function_ `const FWorldPartitionActorFilter* GetFilter() const`
- L70 _protected prototype_ `virtual TUniquePtr<ISceneOutlinerHierarchy> CreateHierarchy() override;`
- L74 _private member_ `TSharedPtr<FFilter> Filter;`

#### class `FWorldPartitionActorFilterMode::FFilter`  
`class FFilter`  
_L19-47_
- desc: struct holding multi selection values that might be null if they differ between actors
- L22 _public prototype_ `FFilter(TSharedPtr<FWorldPartitionActorFilter> LevelFilter, const TArray<const FWorldPartitionActorFilter*>& SelectedFilters);`
- L24 _public prototype_ `void Apply(FWorldPartitionActorFilter* Result) const;`
- L35 _public typedef_ `using FDataLayerFilters = TMap<FSoftObjectPath, FDataLayerFilter>;`
- L37 _private prototype_ `void Initialize(const FWorldPartitionActorFilter* Filter);`
- L38 _private prototype_ `void Override(const FWorldPartitionActorFilter* Other);`
- L39 _private prototype_ `void Merge(const FWorldPartitionActorFilter* Other);`
- L42 _private member_ `TSharedPtr<FWorldPartitionActorFilter> LevelFilter;` — Unmodified Reference Level Filter
- L44 _private member_ `TMap<const FWorldPartitionActorFilter*, FDataLayerFilters> FilterValues;` — Current values for Filter based Selection

#### struct `FWorldPartitionActorFilterMode::FFilter::FDataLayerFilter`  
`struct FDataLayerFilter`  
_L26-33_
- L28 _public function_ `FDataLayerFilter()`
- L29 _public function_ `FDataLayerFilter(bool bInOverride, bool bInIncluded) : bOverride(bInOverride), bIncluded(bInIncluded)`
- L31 _public member_ `TOptional<bool> bOverride;`
- L32 _public member_ `TOptional<bool> bIncluded;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API WORLDPARTITIONEDITOR_API`

### `Source/Editor/WorldPartitionEditor/Public/WorldPartition/Filter/WorldPartitionActorFilterPropertyTypeCustomization.h` (Public)


#### struct `FWorldPartitionActorFilterPropertyTypeCustomization`  
`struct FWorldPartitionActorFilterPropertyTypeCustomization : public IPropertyTypeCustomization`  
_L19-33_
- inherits: `IPropertyTypeCustomization`
- desc: Registered (FLevelInstanceEditorModule::StartupModule) Property Customization for properties of type FWorldPartitionActorFilter
- L22 _public prototype_ `~FWorldPartitionActorFilterPropertyTypeCustomization();`
- L24 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L25 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`
- L28 _private prototype_ `virtual TSharedPtr<FWorldPartitionActorFilterMode::FFilter> CreateModeFilter(TArray<UObject*> OuterObjects) = 0;`
- L29 _private prototype_ `virtual void ApplyFilter(TSharedRef<IPropertyHandle> PropertyHandle, const FWorldPartitionActorFilterMode& Mode) = 0;`
- L31 _private member_ `FDelegateHandle WorldPartitionActorFilterChangedHandle;`
- L32 _private member_ `TSharedPtr<ISceneOutliner> SceneOutliner;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API WORLDPARTITIONEDITOR_API`

### `Source/Editor/WorldPartitionEditor/Public/WorldPartition/Filter/WorldPartitionActorFilterTreeItems.h` (Public)


#### struct `FWorldPartitionActorFilterItemBase`  
`struct FWorldPartitionActorFilterItemBase : ISceneOutlinerTreeItem`  
_L13-21_
- inherits: `ISceneOutlinerTreeItem`
- L15 _public function_ `FWorldPartitionActorFilterItemBase(FSceneOutlinerTreeItemType InType) : ISceneOutlinerTreeItem(InType)`
- L16 _public prototype_ `virtual UClass* GetIconClass() const = 0;`
- L17 _public prototype_ `virtual TSharedRef<SWidget> GenerateLabelWidget(ISceneOutliner& Outliner, const STableRow<FSceneOutlinerTreeItemPtr>& InRow) override;`
- L18 _public function_ `virtual bool CanInteract() const override`
- L20 _public member_ `static const FSceneOutlinerTreeItemType Type;`

#### struct `FWorldPartitionActorFilterItem`  
`struct FWorldPartitionActorFilterItem : FWorldPartitionActorFilterItemBase`  
_L23-51_
- inherits: `FWorldPartitionActorFilterItemBase`
- L35 _public prototype_ `FWorldPartitionActorFilterItem(const FTreeItemData& InData);`
- L37 _public prototype_ `static FSceneOutlinerTreeItemID ComputeTreeItemID(const FWorldPartitionActorFilterItem::FTreeItemData& InData);`
- L40 _public function_ `virtual bool IsValid() const override` — Begin ISceneOutlinerTreeItem Implementation
- L41 _public prototype_ `virtual FSceneOutlinerTreeItemID GetID() const override;`
- L42 _public prototype_ `virtual FString GetDisplayString() const override;`
- L45 _public prototype_ `virtual UClass* GetIconClass() const override;`
- L46 _public function_ `const FWorldPartitionActorFilter* GetFilter() const`
- L48 _public member_ `static const FSceneOutlinerTreeItemType Type;`
- L50 _private member_ `FTreeItemData Data;`

#### struct `FWorldPartitionActorFilterItem::FTreeItemData`  
`struct FTreeItemData`  
_L26-33_
- L28 _public function_ `FTreeItemData(const FWorldPartitionActorFilter* InFilter) : Filter(InFilter)`
- L32 _public member_ `const FWorldPartitionActorFilter* Filter;`

#### struct `FWorldPartitionActorFilterDataLayerItem`  
`struct FWorldPartitionActorFilterDataLayerItem : FWorldPartitionActorFilterItemBase`  
_L53-84_
- inherits: `FWorldPartitionActorFilterItemBase`
- L66 _public prototype_ `FWorldPartitionActorFilterDataLayerItem(const FTreeItemData& InData);`
- L68 _public prototype_ `static FSceneOutlinerTreeItemID ComputeTreeItemID(const FWorldPartitionActorFilterDataLayerItem::FTreeItemData& InData);`
- L71 _public function_ `virtual bool IsValid() const override` — Begin ISceneOutlinerTreeItem Implementation
- L72 _public prototype_ `virtual FSceneOutlinerTreeItemID GetID() const override;`
- L73 _public prototype_ `virtual FString GetDisplayString() const override;`
- L76 _public prototype_ `virtual UClass* GetIconClass() const override;`
- L77 _public function_ `const FWorldPartitionActorFilter* GetFilter() const`
- L78 _public function_ `const FSoftObjectPath& GetAssetPath() const`
- L79 _public prototype_ `bool GetDefaultValue() const;`
- L81 _public member_ `static const FSceneOutlinerTreeItemType Type;`
- L83 _private member_ `FTreeItemData Data;`

#### struct `FWorldPartitionActorFilterDataLayerItem::FTreeItemData`  
`struct FTreeItemData`  
_L56-64_
- L58 _public function_ `FTreeItemData(const FWorldPartitionActorFilter* InFilter, const FSoftObjectPath& InAssetPath) : Filter(InFilter), AssetPath(InAssetPath)`
- L62 _public member_ `const FWorldPartitionActorFilter* Filter;`
- L63 _public member_ `const FSoftObjectPath AssetPath;`

### `Source/Editor/WorldPartitionEditor/Public/WorldPartition/HLOD/HLODEditorSubsystem.h` (Public)


#### enum `EHLODSettingsVisibility`  
`enum class EHLODSettingsVisibility : uint8`  
_L28-32_
- desc: Visibility level for HLOD settings By default, settings are classified in the "AllSettings" category
- L30 _public enumerator_ `BasicSettings`
- L31 _public enumerator_ `AllSettings`

#### class `UWorldPartitionHLODEditorSubsystem`  
`class UWorldPartitionHLODEditorSubsystem : public UEditorSubsystem, public FTickableGameObject`  
_L39-108_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem,FTickableGameObject`
- desc: UWorldPartitionHLODEditorSubsystem
- L44 _public prototype_ `UWorldPartitionHLODEditorSubsystem();`
- L45 _public prototype_ `virtual ~UWorldPartitionHLODEditorSubsystem();`
- L48 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L49 _public prototype_ `virtual void Deinitialize() override;`
- L53 _public prototype_ `virtual bool IsTickable() const override;`
- L54 _public function_ `virtual bool IsTickableInEditor() const override`
- L55 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L56 _public prototype_ `virtual TStatId GetStatId() const override;`
- L59 _public prototype_ `static bool WriteHLODStats(const IWorldPartitionEditorModule::FWriteHLODStatsParams& Params);`
- L61 _public prototype_ `static void AddHLODSettingsFilter(EHLODSettingsVisibility InSettingsVisibility, TSoftObjectPtr<UStruct> InStruct, FName InPropertyName);`
- L63 _public prototype_ `void ForceHLODVisibilityUpdate();`
- L66 _private prototype_ `bool IsHLODInEditorEnabled();`
- L67 _private prototype_ `void SetHLODInEditorEnabled(bool bInEnable);`
- L69 _private prototype_ `void OnWorldPartitionInitialized(UWorldPartition* InWorldPartition);`
- L70 _private prototype_ `void OnWorldPartitionUninitialized(UWorldPartition* InWorldPartition);`
- L72 _private prototype_ `void OnLoaderAdapterStateChanged(const IWorldPartitionActorLoaderInterface::ILoaderAdapter* LoaderAdapter);`
- L74 _private prototype_ `void ForceHLODStateUpdate();`
- L76 _private prototype_ `static bool WriteHLODStats(UWorld* InWorld, const FString& InFilename);`
- L77 _private prototype_ `static bool WriteHLODInputStats(UWorld* InWorld, const FString& InFilename);`
- L79 _private prototype_ `void OnWorldPartitionEditorSettingsChanged(const FName& PropertyName, const UWorldPartitionEditorSettings& WorldPartitionEditorSettings);`
- L80 _private prototype_ `void ApplyHLODSettingsFiltering();`
- L82 _private prototype_ `void OnColorHandlerPropertyChangedEvent(UObject* InObject, FPropertyChangedEvent& InPropertyChangedEvent);`
- L84 _private prototype_ `void OnHLODActorRegistered(AWorldPartitionHLOD* Actor);`
- L85 _private prototype_ `void OnHLODActorUnregistered(AWorldPartitionHLOD* Actor);`
- L87 _private prototype_ `void OnLevelEditorCreated(TSharedPtr<ILevelEditor> InLevelEditor);`
- L88 _private prototype_ `void ExtendShowFlagsMenu();`
- L90 _private prototype_ `void OnPostWorldInitialization(UWorld* InWorld, const UWorld::InitializationValues InIVS);`
- L93 _private member_ `FDelegateHandle HLODActorEditorRegisteredHandle;`
- L94 _private member_ `FDelegateHandle HLODActorEditorUnregisteredHandle;`
- L96 _private member_ `FVector CachedCameraLocation;`
- L97 _private member_ `double CachedHLODMinDrawDistance;`
- L98 _private member_ `double CachedHLODMaxDrawDistance;`
- L99 _private member_ `bool bCachedShowHLODsOverLoadedRegions;`
- L100 _private member_ `bool bForceHLODStateUpdate;`
- L101 _private member_ `bool bForceHLODVisibilityUpdate;`
- L102 _private member_ `bool bHLODSettingsFilteringActive;`
- L104 _private member_ `TMap<TObjectKey<UWorldPartition>, TPimplPtr<FWorldPartitionHLODEditorData>> WorldPartitionsHLODEditorData;`
- L106 _private typedef_ `typedef TMap<TSoftObjectPtr<UStruct>, TSet<FName>> FStructsPropertiesMap;`
- L107 _private member_ `static TMap<EHLODSettingsVisibility, FStructsPropertiesMap> StructsPropertiesVisibility;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API WORLDPARTITIONEDITOR_API`
- L112 _macro_ `#define HLOD_ADD_CLASS_SETTING_FILTER_NAME(SettingsLevel, TypeIdentifier, PropertyName) \` — Macros to simplify registration of HLOD settings filtering
- L115 _macro_ `#define HLOD_ADD_STRUCT_SETTING_FILTER_NAME(SettingsLevel, TypeIdentifier, PropertyName) \`
- L118 _macro_ `#define HLOD_ADD_CLASS_SETTING_FILTER(SettingsLevel, TypeIdentifier, PropertyIdentifier) \`
- L121 _macro_ `#define HLOD_ADD_STRUCT_SETTING_FILTER(SettingsLevel, TypeIdentifier, PropertyIdentifier) \`

### `Source/Editor/WorldPartitionEditor/Public/WorldPartition/HLOD/HLODLayerFactory.h` (Public)


#### class `UHLODLayerFactory`  
`class UHLODLayerFactory : public UFactory`  
_L18-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L23 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API WORLDPARTITIONEDITOR_API`

### `Source/Editor/WorldPartitionEditor/Public/WorldPartition/HLOD/HLODLoaderAdapter.h` (Public)


#### class `FLoaderAdapterHLOD`  
`class FLoaderAdapterHLOD : public IWorldPartitionActorLoaderInterface::ILoaderAdapter`  
_L9-19_
- inherits: `IWorldPartitionActorLoaderInterface::ILoaderAdapter`
- L12 _public prototype_ `FLoaderAdapterHLOD(UWorld* InWorld);`
- L16 _protected prototype_ `virtual void ForEachActor(TFunctionRef<void(const FWorldPartitionHandle&)> InOperation) const override;`
- L17 _protected prototype_ `virtual bool PassActorDescFilter(const FWorldPartitionHandle& ActorHandle) const override;`

### `Source/Editor/WorldPartitionEditor/Public/WorldPartition/SWorldPartitionEditor.h` (Public)


#### class `SWorldPartitionEditor`  
`class SWorldPartitionEditor : public SCompoundWidget, public IWorldPartitionEditor`  
_L10-38_
- inherits: `SCompoundWidget,IWorldPartitionEditor`
- L13 _public function_ `SLATE_BEGIN_ARGS(SWorldPartitionEditor) :_InWorld(nullptr)`
- L16 _public prototype_ `SLATE_ARGUMENT(UWorld*, InWorld) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L21 _public prototype_ `~SWorldPartitionEditor();`
- L24 _public prototype_ `virtual void Refresh() override;` — IWorldPartitionEditor interface
- L25 _public prototype_ `virtual void Reconstruct() override;`
- L26 _public prototype_ `virtual void FocusBox(const FBox& Box) const override;`
- L29 _private prototype_ `void OnBrowseWorld(UWorld* InWorld);`
- L31 _private prototype_ `TSharedRef<SWidget> ConstructContentWidget();`
- L33 _private prototype_ `FText GetMouseLocationText() const;`
- L35 _private member_ `TSharedPtr<SBorder> ContentParent;`
- L36 _private member_ `TSharedPtr<class SWorldPartitionEditorGrid> GridView;`
- L37 _private member_ `TWeakObjectPtr<UWorld> World;`

### `Source/Editor/WorldPartitionEditor/Public/WorldPartition/SWorldPartitionEditorGrid.h` (Public)


#### class `SWorldPartitionEditorGrid`  
`class SWorldPartitionEditorGrid : public SCompoundWidget`  
_L25-83_
- inherits: `SCompoundWidget`
- desc: Base class for world partition editors (goes hand in hand with corresponding UWorldPartition class via GetWorldPartitionEditorName)
- L29 _private typedef_ `typedef TFunction<TSharedRef<SWorldPartitionEditorGrid> (TSharedPtr<SWorldPartitionEditorGrid>&, UWorld*)> PartitionEditorGridCreateInstanceFunc;`
- L32 _public prototype_ `WORLD_PARTITION_EDITOR_IMPL(SWorldPartitionEditorGrid);`
- L34 _public function_ `SWorldPartitionEditorGrid() : World(nullptr)`
- L38 _public prototype_ `void Construct(const FArguments& InArgs);`
- L41 _public prototype_ `static void RegisterPartitionEditorGridCreateInstanceFunc(FName Name, PartitionEditorGridCreateInstanceFunc CreateFunc);` — Interface to register world partition editors
- L42 _public prototype_ `static PartitionEditorGridCreateInstanceFunc GetPartitionEditorGridCreateInstanceFunc(FName Name);`
- L45 _public function_ `virtual void OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const override` — SPanel interface
- L53 _public function_ `virtual FVector2D ComputeDesiredSize(float Scale) const override`
- L58 _public function_ `virtual FChildren* GetChildren() override`
- L63 _public prototype_ `bool GetPlayerView(FVector& Location, FRotator& Rotation) const;`
- L64 _public prototype_ `bool GetObserverView(FVector& Location, FRotator& Rotation) const;`
- L66 _public prototype_ `void Refresh();`
- L67 _public function_ `virtual void FocusBox(const FBox& Box) const`
- L69 _public function_ `inline UWorld* GetWorld()`
- L70 _public function_ `inline const UWorld* GetWorld() const`
- L72 _public function_ `inline UWorldPartition* GetWorldPartition()`
- L73 _public function_ `inline const UWorldPartition* GetWorldPartition() const`
- L76 _protected member_ `static TMap<FName, PartitionEditorGridCreateInstanceFunc> PartitionEditorGridCreateInstanceFactory;`
- L79 _private prototype_ `bool IsDisabled() const;`
- L81 _private member_ `TWeakObjectPtr<UWorld> World;`
- L82 _private member_ `TWeakObjectPtr<UWorldPartition> WorldPartition;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define WORLD_PARTITION_EDITOR_IMPL(Type) \`

### `Source/Editor/WorldPartitionEditor/Public/WorldPartition/SWorldPartitionEditorGrid2D.h` (Public)


#### class `SWorldPartitionEditorGrid2D`  
`class SWorldPartitionEditorGrid2D : public SWorldPartitionEditorGrid`  
_L19-257_
- inherits: `SWorldPartitionEditorGrid`
- L90 _public prototype_ `SWorldPartitionEditorGrid2D();`
- L91 _public prototype_ `~SWorldPartitionEditorGrid2D();`
- L94 _protected prototype_ `void Construct(const FArguments& InArgs);`
- L95 _protected prototype_ `void BindCommands();`
- L97 _protected prototype_ `void CreateRegionFromSelection();`
- L98 _protected prototype_ `void BuildHLODsForSelection();`
- L99 _protected prototype_ `void BuildHLODsForSelectedRegions();`
- L100 _protected prototype_ `void LoadSelectedRegions();`
- L101 _protected prototype_ `void UnloadSelectedRegions();`
- L102 _protected prototype_ `void ConvertSelectedRegionsToActors();`
- L104 _protected prototype_ `void MoveCameraHere();`
- L105 _protected prototype_ `void PlayFromHere();`
- L106 _protected prototype_ `void LoadFromHere();`
- L107 _protected prototype_ `void BugItHere();`
- L109 _protected prototype_ `bool IsFollowPlayerInPIE() const;`
- L110 _protected prototype_ `bool IsInteractive() const;`
- L112 _protected prototype_ `virtual int64 GetSelectionSnap() const;`
- L114 _protected prototype_ `TSharedRef<SWidget> GenerateContextualMenu() const;`
- L116 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L117 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L118 _protected prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L119 _protected prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L120 _protected prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L121 _protected prototype_ `virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L122 _protected prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L124 _protected prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L125 _protected prototype_ `virtual int32 PaintGrid(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId) const;`
- L126 _protected prototype_ `virtual uint32 PaintActors(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, uint32 LayerId) const;`
- L127 _protected prototype_ `virtual uint32 PaintTextInfo(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, uint32 LayerId) const;`
- L128 _protected prototype_ `virtual uint32 PaintViewer(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, uint32 LayerId) const;`
- L129 _protected prototype_ `virtual uint32 PaintSelection(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, uint32 LayerId) const;`
- L130 _protected prototype_ `virtual int32 PaintMinimap(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId) const;`
- L131 _protected prototype_ `virtual int32 PaintMeasureTool(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId) const;`
- L133 _protected prototype_ `int32 DrawTextLabel(FSlateWindowElementList& OutDrawElements, int32 LayerId, const FGeometry& AllottedGeometry, const FString& Label, const FVector2D& Pos, const FLinearColor& Color, const FSlateFontInfo& Font) const;`
- L135 _protected prototype_ `void FocusSelection();`
- L136 _protected prototype_ `void FocusLoadedRegions();`
- L137 _protected prototype_ `void FocusWorld();`
- L139 _protected prototype_ `void UpdateTransform() const;`
- L140 _protected prototype_ `void UpdateSelectionBox(bool bSnap);`
- L141 _protected prototype_ `void ClearSelection();`
- L143 _protected prototype_ `bool ShouldShowActorBounds(AActor* InActor) const;`
- L144 _protected prototype_ `bool ShouldShowActorBounds(FWorldPartitionActorDescInstance* ActorDescInstance) const;`
- L146 _protected member_ `const TSharedRef<FUICommandList> CommandList;`
- L148 _protected member_ `FSingleWidgetChildrenWithBasicLayoutSlot ChildSlot;`
- L150 _protected function_ `FChildren* GetChildren()`
- L155 _protected function_ `void OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const`
- L160 _protected prototype_ `virtual void FocusBox(const FBox& Box) const override;`
- L162 _protected member_ `mutable float Scale;`
- L163 _protected member_ `mutable FVector2D Trans;`
- L165 _protected member_ `mutable FBox2D ScreenRect;`
- L166 _protected member_ `mutable FTransform2d WorldToScreen;`
- L167 _protected member_ `mutable FTransform2d ScreenToWorld;`
- L169 _protected member_ `bool bIsDragSelecting;`
- L170 _protected member_ `bool bIsPanning;`
- L171 _protected member_ `bool bIsMeasuring;`
- L172 _protected member_ `bool bShowActors;`
- L173 _protected member_ `bool bShowHLODActors;`
- L174 _protected member_ `bool bShowGrid;`
- L175 _protected member_ `bool bShowLoadingRegions;`
- L176 _protected member_ `bool bShowMiniMap;`
- L177 _protected member_ `bool bShowMouseCoords;`
- L178 _protected member_ `bool bFollowPlayerInPIE;`
- L179 _protected member_ `FVector2D MouseCursorPos;`
- L180 _protected member_ `FVector2D MouseCursorPosWorld;`
- L181 _protected member_ `FVector2D LastMouseCursorPosWorldDrag;`
- L182 _protected member_ `FVector2D SelectionStart;`
- L183 _protected member_ `FVector2D SelectionEnd;`
- L184 _protected member_ `FVector2D MeasureStart;`
- L185 _protected member_ `FVector2D MeasureEnd;`
- L186 _protected member_ `FBox SelectBox;`
- L187 _protected member_ `FBox SelectBoxGridSnapped;`
- L188 _protected member_ `FSlateFontInfo SmallLayoutFont;`
- L189 _protected member_ `float TotalMouseDelta;`
- L209 _protected typedef_ `using FLoaderInterface = TWeakInterfacePtr<IWorldPartitionActorLoaderInterface>;`
- L210 _protected typedef_ `using FLoaderInterfaceSet = TSet<FLoaderInterface, FKeyFuncs>;`
- L211 _protected typedef_ `using FLoaderInterfaceStack = TArray<FLoaderInterface>;`
- L213 _protected member_ `FLoaderInterfaceSet SelectedLoaderInterfaces;`
- L216 _protected member_ `TSet<FGuid> ShownActorGuids;` — Updated every tick
- L217 _protected member_ `TSet<FGuid> DirtyActorGuids;`
- L218 _protected member_ `TSet<FGuid> SelectedActorGuids;`
- L219 _protected member_ `FLoaderInterfaceSet ShownLoaderInterfaces;`
- L220 _protected member_ `FLoaderInterfaceSet HoveredLoaderInterfaces;`
- L221 _protected member_ `FLoaderInterfaceStack HoveredLoaderInterfacesStack;`
- L222 _protected member_ `FLoaderInterface HoveredLoaderInterface;`
- L225 _protected member_ `FBox ViewRectWorldCache;` — Shown actors cache
- L226 _protected member_ `TSet<FGuid> ShownActorGuidsCache;`
- L227 _protected member_ `FLoaderInterfaceSet ShownLoaderInterfacesCache;`
- L228 _protected function_ `void InvalidateShownActorsCache()`
- L231 _protected prototype_ `void UpdateWorldMiniMapDetails();` — Minimap
- L232 _protected prototype_ `void SaveMiniMapUnloadedOpacityUserSetting();`
- L233 _protected prototype_ `bool IsMiniMapUnloadedOpacityEnabled() const;`
- L234 _protected function_ `float GetMiniMapUnloadedOpacity() const`
- L235 _protected function_ `void SetMiniMapUnloadedOpacity(float InOpacity)`
- L236 _protected member_ `float MiniMapUnloadedOpacity;`
- L237 _protected member_ `FBox2D WorldMiniMapBounds;`
- L238 _protected member_ `FSlateBrush WorldMiniMapBrush;`
- L241 _protected member_ `mutable double TickTime;` — Profiling
- L242 _protected member_ `mutable double PaintTime;`
- L244 _protected member_ `TSharedPtr<SWorldPartitionViewportWidget> ViewportWidget;`
- L245 _protected member_ `TSharedPtr<STextBlock> TextWorldBoundsInKMWidget;`
- L246 _protected member_ `TSharedPtr<STextBlock> TextRulerWidget;`
- L255 _protected typedef_ `using FExternalDirtyActorsTracker = TExternalDirtyActorsTracker<FExternalDirtyActorTrackerGuid>;`
- L256 _protected member_ `TUniquePtr<FExternalDirtyActorsTracker> ExternalDirtyActorsTracker;`

#### class `SWorldPartitionEditorGrid2D::FEditorCommands`  
`class FEditorCommands : public TCommands<FEditorCommands>`  
_L22-63_
- inherits: `TCommands<FEditorCommands>`
- L25 _public prototype_ `FEditorCommands();`
- L28 _public member_ `TSharedPtr<FUICommandInfo> CreateRegionFromSelection;` — Context Menu
- L29 _public member_ `TSharedPtr<FUICommandInfo> BuildHLODsForSelection;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> BuildHLODsForSelectedRegions;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> LoadSelectedRegions;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> UnloadSelectedRegions;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> UnloadHoveredRegion;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> ConvertSelectedRegionsToActors;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> MoveCameraHere;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> PlayFromHere;`
- L37 _public member_ `TSharedPtr<FUICommandInfo> LoadFromHere;`
- L38 _public member_ `TSharedPtr<FUICommandInfo> BugItHere;`
- L42 _public member_ `TSharedPtr<FUICommandInfo> FollowPlayerInPIE;` — Toolbar Options
- L43 _public member_ `TSharedPtr<FUICommandInfo> BugItGoLoadRegion;`
- L46 _public member_ `TSharedPtr<FUICommandInfo> ShowActors;` — Show toggles
- L47 _public member_ `TSharedPtr<FUICommandInfo> ShowHLODActors;`
- L48 _public member_ `TSharedPtr<FUICommandInfo> ShowGrid;`
- L49 _public member_ `TSharedPtr<FUICommandInfo> ShowMiniMap;`
- L50 _public member_ `TSharedPtr<FUICommandInfo> ShowCoords;`
- L51 _public member_ `TSharedPtr<FUICommandInfo> ShowMouseCoords;`
- L52 _public member_ `TSharedPtr<FUICommandInfo> ShowLoadingRegions;`
- L55 _public member_ `TSharedPtr<FUICommandInfo> FocusSelection;` — Quick Actions
- L56 _public member_ `TSharedPtr<FUICommandInfo> FocusLoadedRegions;`
- L57 _public member_ `TSharedPtr<FUICommandInfo> FocusWorld;`
- L62 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

#### class `SWorldPartitionEditorGrid2D::SToolBar`  
`class SToolBar : public SViewportToolBar`  
_L66-86_
- inherits: `SViewportToolBar`
- desc: In-viewport toolbar widget used in the world partition editor
- L69 _public function_ `SLATE_BEGIN_ARGS(SToolBar)`
- L70 _public prototype_ `SLATE_ARGUMENT(SWorldPartitionEditorGrid2D*, WPEditorGrid2D) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L76 _private prototype_ `EVisibility IsOptionsMenuVisible() const;`
- L78 _private prototype_ `TSharedRef<SWidget> GenerateUnloadedOpacitySlider() const;`
- L80 _private prototype_ `TSharedRef<SWidget> GenerateOptionsMenu() const;`
- L81 _private prototype_ `TSharedRef<SWidget> GenerateShowMenu() const;`
- L82 _private prototype_ `TSharedRef<SWidget> GenerateBuildMenu() const;`
- L84 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L85 _private member_ `SWorldPartitionEditorGrid2D* WPEditorGrid2D;`

#### struct `SWorldPartitionEditorGrid2D::FKeyFuncs`  
`struct FKeyFuncs : public BaseKeyFuncs<TWeakInterfacePtr<IWorldPartitionActorLoaderInterface>, TWeakInterfacePtr<IWorldPartitionActorLoaderInterface>, false>`  
_L191-207_
- inherits: `BaseKeyFuncs<TWeakInterfacePtr<IWorldPartitionActorLoaderInterface>,TWeakInterfacePtr<IWorldPartitionActorLoaderInterface>,false>`
- L193 _public function_ `static KeyInitType GetSetKey(ElementInitType Entry)`
- L198 _public function_ `static bool Matches(KeyInitType A, KeyInitType B)`
- L203 _public function_ `static uint32 GetKeyHash(KeyInitType Key)`

#### struct `SWorldPartitionEditorGrid2D::FExternalDirtyActorTrackerGuid`  
`struct FExternalDirtyActorTrackerGuid`  
_L248-253_
- L250 _public typedef_ `using Type = FGuid;`
- L251 _public typedef_ `using OwnerType = SWorldPartitionEditorGrid2D;`
- L252 _public function_ `static FGuid Store(SWorldPartitionEditorGrid2D* InOwner, AActor* InActor)`

### `Source/Editor/WorldPartitionEditor/Public/WorldPartition/SWorldPartitionEditorGridSpatialHash.h` (Public)


#### class `SWorldPartitionEditorGridSpatialHash`  
`class SWorldPartitionEditorGridSpatialHash : public SWorldPartitionEditorGrid2D`  
_L7-21_
- inherits: `SWorldPartitionEditorGrid2D`
- L10 _public prototype_ `WORLD_PARTITION_EDITOR_IMPL(SWorldPartitionEditorGridSpatialHash);`
- L12 _public prototype_ `void Construct(const FArguments& InArgs);`
- L14 _public prototype_ `virtual int64 GetSelectionSnap() const override;`
- L15 _public prototype_ `virtual int32 PaintGrid(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId) const override;`
- L18 _private prototype_ `int64 GetSelectionSnap(float& FadeRatio, float& CellScreenSize) const;`
- L20 _private member_ `inline static float WantedCellScreenSize = 64.0f;`

### `Source/Editor/WorldPartitionEditor/Public/WorldPartition/WorldPartitionConvertOptions.h` (Public)


#### class `UWorldPartitionConvertOptions`  
`class UWorldPartitionConvertOptions : public UObject`  
_L10-45_
- reflection: `UCLASS()`
- inherits: `UObject`
- L15 _public prototype_ `FString ToCommandletArgs() const;`
- L18 _public member_ `TSubclassOf<UWorldPartitionConvertCommandlet> CommandletClass;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category=Convert)`
- L21 _public member_ `bool bInPlace;` — `UPROPERTY(EditAnywhere, Category=Convert, meta = (ToolTip = "Wether the conversion should create a new map with a _WP suffix or overwrite the source map"))`
- L24 _public member_ `bool bDeleteSourceLevels;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = Convert)`
- L27 _public member_ `bool bGenerateIni;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = Convert)`
- L30 _public member_ `bool bReportOnly;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = Convert)`
- L33 _public member_ `bool bVerbose;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = Convert)`
- L36 _public member_ `bool bSkipStableGUIDValidation;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = Convert)`
- L39 _public member_ `bool bOnlyMergeSubLevels;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = Convert)`
- L42 _public member_ `bool bSaveFoliageTypeToContentFolder = true;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = Convert)`
- L44 _public member_ `FString LongPackageName;`

### `Source/Editor/WorldPartitionEditor/Public/WorldPartition/WorldPartitionEditorSettings.h` (Public)


#### class `UWorldPartitionEditorSettings`  
`class UWorldPartitionEditorSettings : public UDeveloperSettings`  
_L13-121_
- reflection: `UCLASS(MinimalAPI, config = EditorSettings, meta = (DisplayName = "World Partition"))`
- inherits: `UDeveloperSettings`
- L18 _public prototype_ `UWorldPartitionEditorSettings();`
- L20 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnWorldPartitionEditorSettingsChanged, const FName&, const UWorldPartitionEditorSettings&);`
- L21 _public prototype_ `static FOnWorldPartitionEditorSettingsChanged& OnSettingsChanged();`
- L23 _public prototype_ `static FName GetEnableLoadingInEditorPropertyName();`
- L24 _public prototype_ `static FName GetEnableAdvancedHLODSettingsPropertyName();`
- L26 _public prototype_ `TSubclassOf<UWorldPartitionConvertCommandlet> GetCommandletClass() const;`
- L27 _public prototype_ `void SetCommandletClass(const TSubclassOf<UWorldPartitionConvertCommandlet>& InCommandletClass);`
- L29 _public prototype_ `int32 GetInstancedFoliageGridSize() const;`
- L30 _public prototype_ `void SetInstancedFoliageGridSize(int32 InInstancedFoliageGridSize);`
- L32 _public prototype_ `int32 GetMinimapLowQualityWorldUnitsPerPixelThreshold() const;`
- L33 _public prototype_ `void SetMinimapLowQualityWorldUnitsPerPixelThreshold(int32 InMinimapLowQualityWorldUnitsPerPixelThreshold);`
- L35 _public prototype_ `bool GetEnableLoadingInEditor() const;`
- L36 _public prototype_ `void SetEnableLoadingInEditor(bool bInEnableLoadingInEditor);`
- L38 _public prototype_ `bool GetEnableStreamingGenerationLogOnPIE() const;`
- L39 _public prototype_ `void SetEnableStreamingGenerationLogOnPIE(bool bInEnableStreamingGenerationLogOnPIE);`
- L41 _public prototype_ `bool GetShowHLODsInEditor() const;`
- L42 _public prototype_ `void SetShowHLODsInEditor(bool bInShowHLODsInEditor);`
- L44 _public prototype_ `bool GetShowHLODsOverLoadedRegions() const;`
- L45 _public prototype_ `void SetShowHLODsOverLoadedRegions(bool bInShowHLODsOverLoadedRegions);`
- L47 _public prototype_ `bool GetEnableAdvancedHLODSettings() const;`
- L48 _public prototype_ `void SetEnableAdvancedHLODSettings(bool bInEnableAdvancedHLODSettings);`
- L50 _public prototype_ `double GetHLODMinDrawDistance() const;`
- L51 _public prototype_ `void SetHLODMinDrawDistance(double bInHLODMinDrawDistance);`
- L53 _public prototype_ `double GetHLODMaxDrawDistance() const;`
- L54 _public prototype_ `void SetHLODMaxDrawDistance(double bInHLODMaxDrawDistance);`
- L56 _public prototype_ `bool GetDisableBugIt() const;`
- L57 _public prototype_ `void SetDisableBugIt(bool bInEnableBugIt);`
- L59 _public prototype_ `bool GetDisablePIE() const;`
- L60 _public prototype_ `void SetDisablePIE(bool bInEnablePIE);`
- L62 _public prototype_ `bool GetAdvancedMode() const;`
- L63 _public prototype_ `void SetAdvancedMode(bool bInAdvancedMode);`
- L68 _public member_ `TSubclassOf<UWorldPartitionConvertCommandlet> CommandletClass;` — `UE_DEPRECATED(5.5, "Use Get/SetCommandletClass()")` — `UPROPERTY(Config, EditAnywhere, Category = MapConversion, Meta = (ToolTip = "Commandlet class to use for World Partition conversion"))`
- L72 _public member_ `int32 InstancedFoliageGridSize;` — `UE_DEPRECATED(5.5, "Use Get/SetInstancedFoliageGridSize()")` — `UPROPERTY(Config, EditAnywhere, Category = Foliage, Meta = (ClampMin = 3200, ToolTip = "Editor grid size used for instance foliage actors in World Partition worlds"))`
- L76 _public member_ `int32 MinimapLowQualityWorldUnitsPerPixelThreshold;` — `UE_DEPRECATED(5.5, "Use Get/SetMinimapLowQualityWorldUnitsPerPixelThreshold()")` — `UPROPERTY(Config, EditAnywhere, Category = MiniMap, Meta = (ClampMin = 100, ToolTip = "Threshold from which minimap generates a warning if its WorldUnitsPerPixel is above this value"))`
- L80 _public member_ `bool bEnableLoadingInEditor;` — `UE_DEPRECATED(5.5, "Use Get/SetEnableLoadingInEditor()")` — `UPROPERTY(Config, EditAnywhere, Category = WorldPartition, Meta = (ToolTip = "Whether to enable dynamic loading in the editor through loading regions"))`
- L84 _public member_ `bool bEnableStreamingGenerationLogOnPIE;` — `UE_DEPRECATED(5.5, "Use Get/SetEnableStreamingGenerationLogOnPIE()")` — `UPROPERTY(Config, EditAnywhere, Category = WorldPartition, Meta = (ToolTip = "Whether to enable streaming generation log on PIE"))`
- L88 _public member_ `bool bShowHLODsInEditor;` — `UE_DEPRECATED(5.5, "Use Get/SetShowHLODsInEditor()")` — `UPROPERTY(Config, EditAnywhere, Category = HLOD, Meta = (ToolTip = "Whether to show HLODs in the editor"))`
- L92 _public member_ `bool bShowHLODsOverLoadedRegions;` — `UE_DEPRECATED(5.5, "Use Get/SetShowHLODsOverLoadedRegions()")` — `UPROPERTY(Config, EditAnywhere, Category = HLOD, Meta = (ToolTip = "Control display of HLODs in case actors are loaded"))`
- L96 _public member_ `bool bEnableAdvancedHLODSettings;` — `UE_DEPRECATED(5.5, "Use Get/SetEnableAdvancedHLODSettings()")` — `UPROPERTY(Config, AdvancedDisplay, Meta = (DisplayName = "Enable Advanced HLOD Settings", ToolTip = "Enable advanced HLODs settings"))`
- L100 _public member_ `double HLODMinDrawDistance;` — `UE_DEPRECATED(5.5, "Use Get/SetHLODMinDrawDistance()")` — `UPROPERTY(Config, EditAnywhere, Category = HLOD, Meta = (UIMin = 0, UIMax = 1638400, DisplayName = "HLOD Min Draw Distance", ToolTip = "Minimum distance at which HLODs should be displayed in editor"))`
- L104 _public member_ `double HLODMaxDrawDistance;` — `UE_DEPRECATED(5.5, "Use Get/SetHLODMaxDrawDistance()")` — `UPROPERTY(Config, EditAnywhere, Category = HLOD, Meta = (UIMin = 0, UIMax = 1638400, DisplayName = "HLOD Max Draw Distance", ToolTip = "Maximum distance at which HLODs should be displayed in editor"))`
- L107 _public member_ `bool bDisableBugIt;` — `UE_DEPRECATED(5.5, "Use Get/SetDisableBugIt()")`
- L110 _public member_ `bool bDisablePIE;` — `UE_DEPRECATED(5.5, "Use Get/SetDisablePIE()")`
- L113 _public member_ `bool bAdvancedMode;` — `UE_DEPRECATED(5.5, "Use Get/SetAdvancedMode()")`
- L116 _protected member_ `FOnWorldPartitionEditorSettingsChanged SettingsChangedDelegate;`
- L118 _protected prototype_ `void TriggerPropertyChangeEvent(FName PropertyName);`
- L119 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API WORLDPARTITIONEDITOR_API`
- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnWorldPartitionEditorSettingsChanged, const FName&, const UWorldPartitionEditorSettings&);`

### `Source/Editor/WorldPartitionEditor/Public/WorldPartition/WorldPartitionEditorState.h` (Public)


#### class `UWorldPartitionEditorState`  
`class UWorldPartitionEditorState : public UWorldDependantEditorState`  
_L9-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWorldDependantEditorState`
- L14 _private prototype_ `virtual FText GetCategoryText() const override;`
- L16 _private prototype_ `virtual FOperationResult CaptureState() override;`
- L17 _private prototype_ `virtual FOperationResult RestoreState() const override;`
- L22 _private member_ `TArray<FBox> LoadedEditorRegions;` — `UPROPERTY(EditAnywhere, Category = WorldState)`
- L25 _private member_ `TArray<FName> LoadedEditorLocationVolumes;` — `UPROPERTY(EditAnywhere, Category = WorldState)`

### `Source/Editor/WorldPartitionEditor/Public/WorldPartitionEditorModule.h` (Public)


#### class `FWorldPartitionEditorModule`  
`class FWorldPartitionEditorModule : public IWorldPartitionEditorModule`  
_L19-193_
- inherits: `IWorldPartitionEditorModule`
- desc: The module holding all of the UI related pieces for SubLevels management
- L25 _public prototype_ `virtual void StartupModule() override;` — Called right after the module DLL has been loaded and the module object has been created
- L30 _public prototype_ `virtual void ShutdownModule() override;` — Called before the module is unloaded, right before the module object is destroyed.
- L35 _public prototype_ `virtual TSharedRef<class SWidget> CreateWorldPartitionEditor();` — Creates a world partition widget
- L40 _public prototype_ `virtual int32 GetPlacementGridSize() const override;` — Returns placement grid size setting that should be assigned to new AWorldSettings actors.
- L45 _public prototype_ `virtual int32 GetInstancedFoliageGridSize() const override;` — Returns foliage grid size setting that should be assigned to new AWorldSettings actors.
- L50 _public prototype_ `virtual int32 GetMinimapLowQualityWorldUnitsPerPixelThreshold() const override;` — Returns the threshold from which minimap generates a warning if its WorldUnitsPerPixel is above this value.
- L55 _public prototype_ `virtual bool GetEnableLoadingInEditor() const override;` — Returns if loading in the editor is enabled or not.
- L56 _public prototype_ `virtual void SetEnableLoadingInEditor(bool bInEnableLoadingInEditor) override;`
- L61 _public prototype_ `virtual bool GetEnableStreamingGenerationLogOnPIE() const override;` — Returns if streaming generation log on PIE is enabled or not.
- L62 _public prototype_ `virtual void SetEnableStreamingGenerationLogOnPIE(bool bInEnableLoadingInEditor) override;`
- L67 _public prototype_ `virtual bool GetDisablePIE() const override;` — Returns if pie is disabled or not.
- L68 _public prototype_ `virtual void SetDisablePIE(bool bInDisablePIE) override;`
- L73 _public prototype_ `virtual bool GetDisableBugIt() const override;` — Returns if bugit command in the editor is disabled or not.
- L74 _public prototype_ `virtual void SetDisableBugIt(bool bInDisableBugIt) override;`
- L79 _public prototype_ `virtual bool GetAdvancedMode() const override;` — Returns if world partition is in advanced mode or not.
- L80 _public prototype_ `virtual void SetAdvancedMode(bool bInAdvancedMode) override;`
- L82 _public prototype_ `virtual bool GetRequireExplicitHLODLayerPartitionAssignation() const override;`
- L83 _public prototype_ `virtual void SetRequireExplicitHLODLayerPartitionAssignation(bool bInRequireExplicitHLODLayerPartitionAssignation) override;`
- L85 _public prototype_ `virtual bool GetShowHLODsInEditor() const override;`
- L86 _public prototype_ `virtual void SetShowHLODsInEditor(bool bInShowHLODsInEditor) override;`
- L88 _public prototype_ `virtual bool GetShowHLODsOverLoadedRegions() const override;`
- L89 _public prototype_ `virtual void SetShowHLODsOverLoadedRegions(bool bInShowHLODsOverLoadedRegions) override;`
- L91 _public prototype_ `virtual double GetHLODInEditorMinDrawDistance() const override;`
- L92 _public prototype_ `virtual void SetHLODInEditorMinDrawDistance(double InMinDrawDistance) override;`
- L94 _public prototype_ `virtual double GetHLODInEditorMaxDrawDistance() const override;`
- L95 _public prototype_ `virtual void SetHLODInEditorMaxDrawDistance(double InMaxDrawDistance) override;`
- L97 _public prototype_ `virtual bool IsHLODInEditorAllowed(UWorld* InWorld, FText* OutDisallowedReason) const override;`
- L99 _public prototype_ `virtual bool HasErrors(UWorld* World) const override;`
- L100 _public prototype_ `virtual void RepairErrors(UWorld* World) override;`
- L105 _public prototype_ `virtual bool WriteHLODStats(const FWriteHLODStatsParams& Params) const override;` — Writes various HLOD stats to a file.
- L110 _public prototype_ `virtual bool ConvertMap(const FString& InLongPackageName) override;` — Convert the specified map to a world partition map.
- L115 _public prototype_ `virtual bool RunBuilder(const FRunBuilderParams& InParams) override;` — Run a world partition builder for the current map. Will display a dialog to specify options for the generation.
- L118 _public function_ `virtual FWorldPartitionCreated& OnWorldPartitionCreated() override` — Return the world added event.
- L121 _public function_ `virtual FOnPreExecuteCommandlet& OnPreExecuteCommandlet() override` — Return the commandlet pre-execution event
- L124 _public function_ `virtual FOnExecuteCommandlet& OnExecuteCommandlet() override` — Return the commandlet execution event
- L127 _public function_ `virtual FOnPostExecuteCommandlet& OnPostExecuteCommandlet() override` — Return the commandlet post-execution event
- L133 _public prototype_ `TSharedRef<class SWidget> CreateContentBundleBrowser();` — Creates a Content Bundle Browser widget
- L138 _public prototype_ `bool IsEditingContentBundle() const;` — Returns if there's a content bundle in editing mode.
- L143 _public prototype_ `bool IsEditingContentBundle(const FGuid& ContentBundleGuid) const;` — Returns if the content bundle is in editing mode.
- L148 _public prototype_ `static bool GetActiveLevelViewportCameraInfo(FVector& CameraLocation, FRotator& CameraRotation);` — Get the camera location & rotation from the active level viewport.
- L152 _private prototype_ `void RegisterMenus();` — Register menus
- L155 _private prototype_ `void RegisterWorldPartitionTabs(TSharedPtr<FTabManager> InTabManager);` — Registers world partition tabs spawners with the level editor
- L158 _private prototype_ `void RegisterWorldPartitionLayout(FLayoutExtender& Extender);` — Inserts world partition tabs into the level editor layout
- L161 _private prototype_ `TSharedRef<SDockTab> SpawnWorldPartitionTab(const FSpawnTabArgs& Args);` — Spawns the world partition tab
- L164 _private prototype_ `TSharedRef<SDockTab> SpawnContentBundleTab(const FSpawnTabArgs& Args);` — Spawns the content bundle tab
- L166 _private prototype_ `bool Build(const FRunBuilderParams& InParams);`
- L167 _private prototype_ `bool BuildMinimap(const FRunBuilderParams& InParams);`
- L168 _private prototype_ `bool BuildHLODs(const FRunBuilderParams& InParams);`
- L169 _private prototype_ `bool BuildLandscapeSplineMeshes(UWorld* InWorld);`
- L172 _private prototype_ `void RunCommandletAsExternalProcess(const FString& InCommandletArgs, const FText& InOperationDescription, int32& OutResult, bool& bOutCancelled);`
- L173 _private prototype_ `void OnConvertMap();`
- L174 _private prototype_ `bool OnIsCrossPluginReferenceAllowed(const FAssetData& ReferencingAssetData, const FAssetData& ReferencedAssetData);`
- L175 _private prototype_ `void OnCreateActorBrowserColumns(FSceneOutlinerInitializationOptions& InitOptions, UWorld* World);`
- L177 _private member_ `FDelegateHandle EditorInitializedHandle;`
- L178 _private member_ `FDelegateHandle EditorCloseHandle;`
- L179 _private member_ `FDelegateHandle LevelEditorExtenderDelegateHandle;`
- L181 _private member_ `TWeakPtr<SDockTab> WorldPartitionTab;`
- L182 _private member_ `TWeakPtr<SDockTab> ContentBundleTab;`
- L184 _private member_ `TWeakPtr<SContentBundleBrowser> ContentBundleBrowser;`
- L186 _private member_ `FWorldPartitionCreated WorldPartitionCreatedEvent;`
- L188 _private member_ `FOnPreExecuteCommandlet OnPreExecuteCommandletEvent;`
- L189 _private member_ `FOnExecuteCommandlet OnExecuteCommandletEvent;`
- L190 _private member_ `FOnPostExecuteCommandlet OnPostExecuteCommandletEvent;`
- L192 _private member_ `bool bRequireExplicitHLODLayerPartitionAssignation;`
